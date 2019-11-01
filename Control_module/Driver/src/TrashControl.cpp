#include "TrashControl.h"

namespace TRASH{
    
RobotControl::RobotControl()
{
    this->canBus = std::make_shared<TRASH::SerialPort>();
}

bool RobotControl::MoveRecyle(void)
{
    MOVPack control_data{};
    Buffer data_to_send{};

    control_data.msg.Move_State = (uint8_t)(0);
    control_data.msg.Move_placeHolder1 = 0;
    control_data.msg.Move_placeHolder2 = 0;
    control_data.msg.Move_placeHolder3 = 0;

    data_to_send.push_back((uint8_t)1);

    for(auto c: control_data.data){
        data_to_send.push_back(c);
    }

    canBus->send_a_frame(data_to_send);
    return true;
}

bool RobotControl::MoveHarmful(void)
{
    MOVPack control_data{};
    Buffer data_to_send{};

    control_data.msg.Move_State = (uint8_t)(1);
    control_data.msg.Move_placeHolder1 = 0;
    control_data.msg.Move_placeHolder2 = 0;
    control_data.msg.Move_placeHolder3 = 0;

    data_to_send.push_back((uint8_t)1);

    for(auto c: control_data.data){
        data_to_send.push_back(c);
    }

    canBus->send_a_frame(data_to_send);
    return true;
}

bool RobotControl::MoveKitchen(void)
{
    MOVPack control_data{};
    Buffer data_to_send{};

    control_data.msg.Move_State = (uint8_t)(2);
    control_data.msg.Move_placeHolder1 = 0;
    control_data.msg.Move_placeHolder2 = 0;
    control_data.msg.Move_placeHolder3 = 0;

    data_to_send.push_back((uint8_t)1);

    for(auto c: control_data.data){
        data_to_send.push_back(c);
    }

    canBus->send_a_frame(data_to_send);
    return true;
}

bool RobotControl::MoveOther(void)
{
    MOVPack control_data{};
    Buffer data_to_send{};

    control_data.msg.Move_State = (uint8_t)(3);
    control_data.msg.Move_placeHolder1 = 0;
    control_data.msg.Move_placeHolder2 = 0;
    control_data.msg.Move_placeHolder3 = 0;

    data_to_send.push_back((uint8_t)1);

    for(auto c: control_data.data){
        data_to_send.push_back(c);
    }

    canBus->send_a_frame(data_to_send);
    return true;
}

int RobotControl::StateReback()
{
    Buffer data_from_read = canBus->read_a_frame();
    return data_from_read[0];
}

}
