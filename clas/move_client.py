#!/usr/bin/env python
# coding=utf-8
import rospy
from trash_msgs.srv import trash_move

class MoveControl(object):
    def __init__(self, TYPE, ITEM):
        self.move_client = rospy.ServiceProxy("/robot_cmd", trash_move)
        rospy.wait_for_service('/robot_cmd')
        self.move_to(TYPE, ITEM)

    def move_to(self, TYPE, ITEM):
        self.move_client.wait_for_service()
        resp = self.move_client(TYPE, ITEM)

if __name__ == '__main__':
    rospy.init_node('move_control')
    move_cmd = MoveControl(0,1)

