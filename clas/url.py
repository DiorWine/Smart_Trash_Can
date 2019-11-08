#!/usr/bin/env python
# coding=utf-8
# -*- coding: utf-8 -*-
import sys, urllib, urllib2, json
from move_client import MoveControl
import config
import os

SHOW = False

class Classify ():
    def __init__ (self, WORD):
        self.key = config.key
        print('\033[7m' + "识别对象：" + WORD)
        self.word = urllib.quote(WORD)
        self.num = 1
        self.ResultType = [0, 0, 0, 0]
        self.url = 'http://api.tianapi.com/txapi/lajifenlei/?key=%s&word=%s&num=%s' % (self.key,self.word,self.num)
        self.PreClas(WORD)
        # if self.PreClas(WORD):
        #     pass
        # else:
        #     self.MainRun()

    def PreClas (self, WORD):
        if WORD == "易拉罐":
            self.PrintTrash(0)
            MoveControl(0,0)
            return True
        elif WORD == "矿泉水瓶":
            self.PrintTrash(0)
            MoveControl(0,1)
            return True

        elif WORD == "固体食物" or WORD == "面包" or WORD == "鸡蛋":
            self.PrintTrash(2)
            MoveControl(2, 0)
            return True
        elif WORD == "水果":
            self.PrintTrash(2)
            MoveControl(2, 1)
            return True

        elif WORD == "废电池":
            self.PrintTrash(1)
            MoveControl(1, 0)
            return True

        elif WORD == "废纸团":
            self.PrintTrash(3)
            MoveControl(3, 0)
            return True

        else:
            self.PrintTrash(-1)
        return False


    def TypeName (self, ITEM):
        TYPE = ITEM["type"]
        self.ResultType[TYPE] += 1
        self.PrintTrash(TYPE)

    def ResultSum (self):
        index = 0
        maxnum = 0
        index_i = 0
        for tmp in self.ResultType:
            if (maxnum < tmp):
                index = index_i
                maxnum = tmp
            index_i += 1
        print (index)
        self.MoveTrash(index)

    # def MoveTrash (self, index):
    #     if index == 0:
    #         if SHOW:
    #             print ( os.popen('Movetrash 0').readlines() )
    #         else:
    #             os.popen('Movetrash 0').readlines()

    #     if index == 1:
    #         if SHOW:
    #             print ( os.popen('Movetrash 1').readlines() )
    #         else:
    #             os.popen('Movetrash 1').readlines()

    #     if index == 2:
    #         if SHOW:
    #             print ( os.popen('Movetrash 2').readlines() )
    #         else:
    #             os.popen('Movetrash 2').readlines()
                
    #     if index == 3:
    #         if SHOW:
    #             print ( os.popen('Movetrash 3').readlines() )
    #         else:
    #             os.popen('Movetrash 3').readlines()

    def PrintTrash (self, index):
        if index == 0:
            print ('\033[32m'+"可回收垃圾")
        elif index == 1:
            print ('\033[31m'+"有害垃圾")
        elif index == 2:
            print ('\033[33m'+"厨余垃圾")
        elif index == 3:
            print ('\033[34m'+"其他垃圾")
        else:
            print ('\033[1m'+"识别失败")

        
    def MainRun (self):
        req = urllib2.Request(self.url)
        
        resp = urllib2.urlopen(req)
        content = resp.read()
        
        if(content):
            result = json.loads(content)["msg"]
            if result == "success":
                newslist = json.loads(content)["newslist"]
                for item in newslist:
                    print "---"
                    print item["name"]
                    print item["tip"]
                    print item["explain"]
                    self.TypeName(item)
            else:
                print(content)
        self.ResultSum()

if __name__ == '__main__':
    client = Classify("水果")
