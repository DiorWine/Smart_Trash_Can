#!/usr/bin/env python
# coding=utf-8
import sys
sys.path.append('/home/wine/WorkSpace/demo/')

from audio.record import WAVE_Recorder
from xf.rtasr import *
from clas.url import Classify
from clas.order import Order

if __name__ == '__main__':
    if len(sys.argv) == 1:

        recoder = WAVE_Recorder()
        recoder.WAVE_recode()
        recoder.WAVE_Save()
        # recoder.WAVE_play()

        client = Client()
        client.send(recoder.WAVE_OUTPUT_FILENAME)
        client.recv()
        classClient = Classify(client.ANSWER)
    elif len(sys.argv) == 2:
        recoder = WAVE_Recorder()
        recoder.WAVE_recode()
        recoder.WAVE_Save()

        classClient = Order(True, int(sys.argv[1]), 1)

    elif len(sys.argv) == 3:
        recoder = WAVE_Recorder()
        recoder.WAVE_recode()
        recoder.WAVE_Save()
        recoder.WAVE_play()
        
        classClient = Order(True, int(sys.argv[1]), int(sys.argv[2]))
    else:
        print("please input the file path or JUST Single CMD")
        sys.exit(-1)

