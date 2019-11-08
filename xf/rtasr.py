#!/usr/bin/env python
# coding=utf-8

import sys
import hashlib
from hashlib import sha1
import hmac
import base64
from socket import *
import json, time, threading
from websocket import create_connection
import websocket
from urllib import quote
import logging

import config

reload(sys)
sys.setdefaultencoding("utf8")
logging.basicConfig()

base_url = config.URL
app_id = config.ID
api_key = config.KEY

file_path = "./output.wav"

end_tag = "{\"end\": true}"

class Client():
    def __init__(self):
        # 生成鉴权参数
        ts = str(int (time.time()))
        tmp = app_id + ts
        hl = hashlib.md5()
        hl.update(tmp.encode(encoding='utf-8'))
        my_sign = hmac.new(api_key,  hl.hexdigest(), sha1).digest()
        signa = base64.b64encode(my_sign)

        self.ANSWER = ''
        self.ws = create_connection(base_url + "?appid=" + app_id + "&ts=" + ts + "&signa=" + quote(signa))
        #self.trecv = threading.Thread(target=self.recv)
        #self.trecv.start()

    def send(self, file_path):
        file_object = open(file_path, 'rb')
        try:
            index = 1
            while True:
                chunk = file_object.read(2000)
                if not chunk:
                    break
                self.ws.send(chunk)

                index += 1
                time.sleep(0.04)
        finally:
            #print str(index) + ", read len:" + str(len(chunk)) + ", file tell:" + str(file_object.tell())
            file_object.close()

        self.ws.send(bytes(end_tag))
        print "send end tag success"

    def recv(self):
        try:
            answer = ''
            while self.ws.connected:
                result = str(self.ws.recv())
                if len(result) == 0:
                    print "receive result end"
                    break
                result_dict = json.loads(result)
                data = json.loads(result)["data"]
                if data != "":
                    rt = json.loads(str(data))["cn"]["st"]["rt"]

                # 解析结果
                if result_dict["action"] == "started":
                    print "handshake success, result: " + result

                if result_dict["action"] == "result":
                    for i in rt:
                        for j in i["ws"]:
                            for cw in j["cw"]:
                                if cw["wp"] == "n":
                                    answer += cw["w"]
                                    print "new line :" + cw["w"]
                    print "rtasr result: " + str(data)

                if result_dict["action"] == "error":
                    print "rtasr error: " + result
                    self.ws.close()
                    return
        except websocket.WebSocketConnectionClosedException:
            print answer
            self.ANSWER = answer.encode('utf-8')
            print "receive result end"
            print '\033c'

    def close(self):
        self.ws.close()
        print "connection closed"
        print '\033c'

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("please input the file path")
        sys.exit(-1)
    else:
        client = Client()
        client.send(sys.argv[1])
        client.recv()
        print (client.ANSWER)

