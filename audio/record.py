#!/usr/bin/env python
# coding=utf-8

import pyaudio
import wave

class WAVE_Recorder():
    CHUNK = 2000
    FORMAT = pyaudio.paInt16
    CHANNELS = 1
    RATE = 8000
    RECORD_SECONDS = 2
    WAVE_OUTPUT_FILENAME = "output.wav"
    
    FRAMES = []

    def WAVE_recode(self):
        p = pyaudio.PyAudio()
        
        stream = p.open(format=self.FORMAT,
                        channels=self.CHANNELS,
                        rate=self.RATE,
                        input=True,
                        frames_per_buffer=self.CHUNK)
        
        print("* recording")
        
        for i in range(0, int(self.RATE / self.CHUNK * self.RECORD_SECONDS)):
            data = stream.read(self.CHUNK)
            self.FRAMES.append(data)
        
        print("* done recording\n----------\n")
        
        stream.stop_stream()
        stream.close()
        p.terminate()

    def WAVE_play(self):
        wf = wave.open(self.WAVE_OUTPUT_FILENAME, 'rb')
        p = pyaudio.PyAudio()
        stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                       channels=wf.getnchannels(),
                       rate=wf.getframerate(),
                       output=True)
        data = wf.readframes(self.CHUNK)
        while data != '':
            stream.write(data)
            data = wf.readframes(self.CHUNK)

        stream.stop_stream()
        stream.close()
        p.terminate()
        print ("Play Done ~\n----------\n")


    def WAVE_Save(self):
        wf = wave.open(self.WAVE_OUTPUT_FILENAME, 'wb')
        wf.setnchannels(self.CHANNELS)
        #wf.setsampwidth(p.get_sample_size(self.FORMAT))
        wf.setsampwidth(pyaudio.PyAudio().get_sample_size(self.FORMAT))
        wf.setframerate(self.RATE)
        wf.writeframes(b''.join(self.FRAMES))
        wf.close()

if __name__ == "__main__":
    recoder = WAVE_Recorder()
    recoder.WAVE_recode()
    recoder.WAVE_Save()
    recoder.WAVE_play()
