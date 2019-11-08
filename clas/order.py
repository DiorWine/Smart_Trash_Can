#!/usr/bin/env python
# coding=utf-8
import os
from move_client import MoveControl

SHOW = False

class Order ():
    # def __init__ (self, ITEM):
    #     print ('\033[7m' + "识别对象：" + self.DirtyWord(ITEM,1))
    #     self.MoveTrash(ITEM,1)
    
    def __init__ (self, dirty, ITEM, INDEX):
        print ('\033c')
        print ('\033[7m' + "识别对象：" + self.DirtyWord(ITEM,INDEX))
        self.MoveTrash(ITEM)

    def DirtyWord(self, item, index):
        if item == 0:
            if index == 0:
                MoveControl(0,0)
                return "易拉罐"
            elif index == 1:
                MoveControl(0,1)
                return "矿泉水瓶"
        elif item == 1:
            MoveControl(1,0)
            return "废电池"
        elif item == 2:
            if index == 0:
                MoveControl(2,0)
                return "水果"
            elif index == 1:
                MoveControl(2,1)
                return "固体食物"
        elif item == 3:
            MoveControl(3,0)
            return "废纸团"

    def MoveTrash (self, index):
        if index == 0:
            print ('\033[32m'+"可回收垃圾")

        elif index == 1:
            print ('\033[31m'+"有害垃圾")

        elif index == 2:
            print ('\033[33m'+"厨余垃圾")

        elif index == 3:
            print ('\033[34m'+"其他垃圾")
