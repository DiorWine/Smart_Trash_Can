#!/usr/bin/env python
# coding=utf-8
# -*- coding: utf-8 -*-
import sys, urllib, urllib2, json
import config
import os

class Classify ():
    def __init__ (self, WORD):
        self.key = config.key
        self.word = urllib.quote(WORD)
        self.num = 1
        self.ResultType = [0, 0, 0, 0]
        self.url = 'http://api.tianapi.com/txapi/lajifenlei/?key=%s&word=%s&num=%s' % (self.key,self.word,self.num)
        self.MainRun()


    def TypeName (self, ITEM):
        TYPE = ITEM["type"]
        self.ResultType[TYPE] += 1
        if TYPE == 0:
            print "可回收垃圾"
        elif TYPE == 1:
            print "有害垃圾"
        elif TYPE == 2:
            print "厨余垃圾"
        elif TYPE == 3:
            print "其他垃圾"

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
        if index == 0:
            print ( os.popen('Movetrash 0').readlines() )
        if index == 1:
            print ( os.popen('Movetrash 1').readlines() )
        if index == 2:
            print ( os.popen('Movetrash 2').readlines() )
        if index == 3:
            print ( os.popen('Movetrash 3').readlines() )
        

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
                    self.TypeName(item)
            else:
                print(content)

        self.ResultSum()

if __name__ == '__main__':
    client = Classify("瓶子")
    # client.ResultSum()
