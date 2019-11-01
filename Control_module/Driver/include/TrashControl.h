#pragma once
#include "../../Transport/include/SerialPort.h"
#include <memory>

namespace TRASH{

class RobotControl
{
public:
    RobotControl() ;

    virtual ~RobotControl() {};

    //move control
    virtual bool MoveRecyle(void);
    virtual bool MoveHarmful(void);
    virtual bool MoveKitchen(void);
    virtual bool MoveOther(void);

    //state reback
    virtual int StateReback(void);

private:
    enum{
        RecyleZone, // recyclable trash
        HarmfulZone, // harmful trash
        KitchenZone, // kitchen trash
        OtherZone  // other trash
    };
    std::shared_ptr<TRASH::SerialPort> canBus ;
};

}
