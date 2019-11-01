#include "SerialPort.h"
#include <boost/make_shared.hpp>

#include <iostream>

namespace TRASH
{

void SerialPort::start_a_read()
{
    boost::mutex::scoped_lock lock(m_SerialReadMutex);
    m_pSerialPort->async_read_some(boost::asio::buffer(m_TempBuffer, 128),
        [&](boost::system::error_code ec , std::size_t bytes_transferred){
            boost::mutex::scoped_lock lock(m_BufferDecodeMutex);
            for (int i = 0; i<bytes_transferred; ++i){
                m_Buffer.push_back(m_TempBuffer[i]);
            }
            decode();
            this->start_a_read();
        }
    );
}
// todo
void SerialPort::start_a_write()
{
    boost::mutex::scoped_lock lock(m_SerialWriteMutex);
    if (m_SendDataSeq.empty() == false)
    {
        //std::cout << " frame is ";
        //    for(int i=0;i<17;i++)
        //        std::cout << std::hex << (int)m_SendDataSeq.front()[i] << " ";
        //std::cout << std::endl;
        
        boost::asio::async_write(*m_pSerialPort, boost::asio::buffer(m_SendDataSeq.front()), 
            [&](boost::system::error_code ec , std::size_t bytes_transferred){
                boost::mutex::scoped_lock lock(m_BufferWriteMutex);
                if(m_SendDataSeq.empty() == false){
                    m_SendDataSeq.pop();
                    start_a_write();
                }
            }
        );
    }
}

void SerialPort::encode(Buffer &data, Buffer &frame)
{
    frame.resize(17);//AT(2) ID(4) Len(1) Data(8) /r/n(2)
    int idx, len ;
    len = data.size() ;

    if ( len < 2 )
        return;
    idx = 1 ;

    uint16_t CAN_ID;

    switch(data[0]) {
    case 0x01:
        CAN_ID = 0x301;
        break ;
    default:
        return;
    }

    frame[0]=0x41;
    frame[1]=0x54;
    frame[2]=(uint8_t)(CAN_ID>>3);
    frame[3]=((uint8_t)CAN_ID&0x0007)<<5;
    frame[4]=0x00;
    frame[5]=0x00;
    frame[6]=0x08;
    for ( int i = 7; i < 15; i++ ) {
        frame[i] = data[idx++] ;
    }
    frame[15]=0x0D;
    frame[16]=0x0A;
}

void SerialPort::decode()
{
    while (m_Buffer.size()>16) {
        if (m_Buffer[0]!=0x41) {
            m_Buffer.erase(m_Buffer.begin());
            continue;
        }
        if(m_Buffer[1]!=0x54){
            m_Buffer.erase(m_Buffer.begin());
            continue;
        }
        Buffer::iterator it= m_Buffer.begin();
        Buffer temp = Buffer(it, it+17); // 用vector构造函数赋值时,iterator较其他加一

        bool ret = check_a_frame(temp);
        if (ret)
        {
            decode_a_frame(temp);
            m_Buffer.erase(m_Buffer.begin(), m_Buffer.begin()+17); // 同上面构造函数
        }
        else {
            std::cout << "not a frame" << std::endl;
            m_Buffer.erase(m_Buffer.begin());
            m_Buffer.erase(m_Buffer.begin()); // 包头由两个字节组成AT
        }

    }
}

/**
 * @brief 确定通信串口回传数据是否符合结构.
 * 
 * @param frame 
 * @return true 
 * @return false 
 */
bool SerialPort::check_a_frame(Buffer frame)
{
    if (frame.size()==17 && frame[0]==0x41 && frame[1]==0x54 && frame[15]==0x0D && frame[16]==0x0A &&frame[6]==0x08)
    {
        return true;
    }
    return false;
}

void SerialPort::decode_a_frame(Buffer frame)
{
    unsigned char *temp = &frame[0];
    // transform the canID
    uint8_t tempID[2];
    uint16_t CAN_ID;
    
    tempID[0]=frame[3];
    tempID[1]=frame[2];

    memcpy(&CAN_ID, tempID, sizeof(tempID));
    CAN_ID = CAN_ID >> 5;
    
    switch (CAN_ID) {
    case 0x302:
        // state data loading
        std::copy(frame.begin()+7,frame.begin()+15,_read_state_buffer.begin());
        //for(auto i = _read_gimbal_buffer.begin(); i!=_read_gimbal_buffer.begin()+8;i++)
        //    std::cout << std::hex << (int)*i << " " ;
        // std::cout << "gimbal" << std::endl;
        // std::cout << std::endl;
        break;
    default:
        break;
    }
}

Buffer SerialPort::read_a_frame(void)
{
    Buffer value ;
    boost::mutex::scoped_lock lock(m_BufferReadMutex);

    return _read_state_buffer;
}

bool SerialPort::send_a_frame(Buffer &data)
{
    boost::mutex::scoped_lock lock(m_BufferWriteMutex);
    Buffer frame;
    encode(data,frame);

    try{
        m_SendDataSeq.push(frame);
    }
    catch(std::exception &ex){
        return false;
    }
    if(m_SendDataSeq.size()>5){
        m_SendDataSeq.pop();
    }
    this->start_a_write();
    return true;
}

SerialPort::SerialPort():SerialPort(std::string("/dev/ttyUSB0"))
{

}

SerialPort::SerialPort(const std::string &device)
{
    m_Device = device;
    m_TempBuffer.resize(34,0x00);
    m_Buffer.reserve(512);
    _read_state_buffer.resize(255);
    this -> start_thread();
}

void SerialPort::initCanMode()
{
    Buffer frame;
    frame.resize(7);
    frame[0]=0x41;
    frame[1]=0x54;
    frame[2]=0x2B;
    frame[3]=0x41;
    frame[4]=0x54;
    frame[5]=0x0D;
    frame[6]=0x0A;
    m_SendDataSeq.push(frame);
}

SerialPort::~SerialPort()
{
    stop_thread();
}

void SerialPort::start_thread()
{
    std::cout << "set serial param.\n";
    m_pIOService = boost::make_shared<boost::asio::io_service>();

    m_pSerialPort = boost::make_shared<boost::asio::serial_port>(*m_pIOService, m_Device);

    m_pSerialPort->set_option(boost::asio::serial_port::baud_rate(115200));                         //特率
    m_pSerialPort->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none)); //流量控制
    m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));            //奇偶校验
    m_pSerialPort->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));        //停止位
    m_pSerialPort->set_option(boost::asio::serial_port::character_size(8));                       //数据位

    sp_t = boost::make_shared<boost::thread>(
        [&](){
            start_a_read();
            start_a_write();
            m_pIOService->run();
        }
    );
    std::cout << "thread started.\n";
}

void SerialPort::stop_thread()
{
    m_pIOService->stop();
}

}
