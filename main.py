#!/usr/bin/env python
# coding=utf-8
import sys
sys.path.append('/home/wine/WorkSpace/demo/')

from audio.record import WAVE_Recorder
from xf.rtasr import *
from clas.url import Classify

if __name__ == '__main__':
    if len(sys.argv) == 1:

        recoder = WAVE_Recorder()
        recoder.WAVE_recode()
        recoder.WAVE_Save()
        recoder.WAVE_play()

        client = Client()
        client.send(recoder.WAVE_OUTPUT_FILENAME)
        client.recv()
        classClient = Classify(client.ANSWER)
    elif len(sys.argv) == 2:
        client = Client()
        client.send(sys.argv[1])
        client.recv()
        classClient = Classify(client.ANSWER)
    else:
        print("please input the file path or JUST Single CMD")
        sys.exit(-1)

