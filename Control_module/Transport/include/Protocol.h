#pragma once
#include <iostream>
#include <vector>

namespace TRASH{
    
    typedef std::vector<uint8_t> Buffer;

///////////垃圾桶位置控制//////////
struct MoveMsg {
    uint8_t Move_State;
    uint8_t Move_placeHolder1;
    uint32_t Move_placeHolder2;
    uint16_t Move_placeHolder3;

    MoveMsg()
    :   Move_State{0},
        Move_placeHolder1{0},
        Move_placeHolder2{0},
        Move_placeHolder3{0}
    {}
};

union MOVPack {
    MoveMsg msg;
    uint8_t data[sizeof(msg)];
    MOVPack()
    :   msg{}
    {}
};

}
