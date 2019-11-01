#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <queue>
#include "Protocol.h"
#include "opencv2/opencv.hpp"

using namespace TRASH;

namespace TRASH
{

class SerialPort
{
private:
    void start_a_read();
    void start_a_write();
    void encode(Buffer &data, Buffer &frame); // 修正格式
    void decode();
    bool check_a_frame(Buffer frame);
    void decode_a_frame(Buffer frame);
    void initCanMode();

public:
    SerialPort();
    SerialPort(const std::string &device);
    ~SerialPort();
    
    void start_thread();
    void serial_io_loop();
    void stop_thread();

    Buffer read_a_frame(void);
    bool send_a_frame(Buffer &data);

private:
    std::string m_Device;
    boost::shared_ptr<boost::asio::io_service> m_pIOService;
    boost::shared_ptr<boost::asio::serial_port> m_pSerialPort;

    boost::shared_ptr<boost::thread> sp_t;

    boost::mutex m_SerialReadMutex;
    boost::mutex m_SerialWriteMutex;
    boost::mutex m_BufferDecodeMutex;
    boost::mutex m_BufferWriteMutex;
    boost::mutex m_BufferReadMutex; // for the Buffer data

    std::queue<Buffer> m_SendDataSeq;
    
    Buffer m_TempBuffer;
    Buffer m_Buffer;

    Buffer          _read_state_buffer{} ;
};

}

#endif // WMJSERIALPORT_H
