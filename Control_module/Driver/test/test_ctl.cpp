#include <iostream>
#include "TrashControl.h"
#include "Protocol.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <unistd.h>

int main()
{
    std::shared_ptr<TRASH::RobotControl> ctl = std::make_shared<TRASH::RobotControl>();
    
    float x = 0.0 ;
    float y = 0.0 ;
    float yaw = 0.0;

    bool Coor = false;
    
    char c = 'f' ;
    cv::imshow("ctl_window",0);
    while(c != 'c')
    {
        switch(c){
        case 'q':
            ctl->MoveRecyle();
            break;
        case 'w':
            ctl->MoveHarmful();
            break;
        case 'e':
            ctl->MoveKitchen();
            break;
        case 'r':
            ctl->MoveOther();
            break;
        default:
            break ;
        }
        c = 'n' ;
        c = cv::waitKey(2) ;
        usleep(100000);

        switch(ctl->StateReback()){
        case 0:
            std::cout << "Not Finish!!!" << std::endl;
            break;
        case 1:
            std::cout << "Finished!!!" << std::endl;
            break;
        }
        std::cout << std::endl << std::endl;
    }
    return 0;
}
