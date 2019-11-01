#include <iostream>
#include "TrashControl.h"
#include "Protocol.h"
#include <unistd.h>
#include <memory>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "wrong usage!" << std::endl;
        return -1;
    }
    std::shared_ptr<TRASH::RobotControl> ctl = std::make_shared<TRASH::RobotControl>();
    usleep(1000);
    switch (atoi(argv[1]))
    {
    case 0:
        std::cout << "Recyle" << std::endl;
        ctl->MoveRecyle();
        break;
    case 1:
        std::cout << "Harmful" << std::endl;
        ctl->MoveHarmful();
        break;
    case 2:
        std::cout << "Kitchen" << std::endl;
        ctl->MoveKitchen();
        break;
    case 3:
        std::cout << "Other" << std::endl;
        ctl->MoveOther();
        break;
    }
    return 0;
}
