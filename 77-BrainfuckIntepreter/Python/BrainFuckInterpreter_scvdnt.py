# -*- coding: utf-8 -*-
"""
Created on Fri Jan  6 10:11:14 2017

I do regognize that InterpreterUncleaned is 100% unoptimised.

@author: scvdnt

"""
import numpy
import sys


def Main():
    pass


def InterpreterUncleaned(source):
    ASCII = '\x00\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0¡¢£¤¥¦§¨©ª«¬\xad®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ'
    iterations = 0
    memory = bytearray(2550)
    bracketlayer = 0
    bracketlayerPrev = 0
    bracketPos = numpy.zeros(2550)
    srcpos = 0
    pos = 0
    srcLength = len(source)
    memLength = len(memory)
    char = ']'

    while ((srcpos < srcLength) & (iterations < 20000000000)):
        char = source[srcpos]
        # print(char)
        if char == '+':
            if memory[pos] == 255:
                memory[pos] = 0
            else:
                memory[pos] += 1
        elif char == '-':
            if memory[pos] == 0:
                memory[pos] = 255
            else:
                memory[pos] -= 1
        elif char == '>':
            if pos < memLength-1:
                pos += 1
            else:
                return 'error >'
        elif char == '.':
            print(ASCII[memory[pos]], end='')
        elif char == ',':
            # memory[pos] = sys.stdin.read(1)
            print(input())
        elif char == '<':
            if pos != 0:
                pos -= 1
            else:
                return 'error <'
        elif char == '[':
            if memory[pos] == 0:
                bracketlayerPrev = bracketlayer
                bracketlayer+=1
                while( (bracketlayer != bracketlayerPrev) & (srcpos<srcLength-1) ):
                    srcpos+=1
                    char = source[srcpos]
                    if char=='[':
                        bracketlayer+=1
                    elif char==']':
                        bracketlayer-=1
                if srcpos==srcLength-1 & bracketlayerPrev<bracketlayer:
                    return 'error ['
            else:
                bracketlayer+=1
                bracketPos[bracketlayer]=srcpos
        elif char==']':
            if memory[pos]==0:
                if bracketlayer==0:
                    return 'error ]'
                bracketlayer-=1
            else:
                srcpos = int(bracketPos[bracketlayer])
        srcpos+=1
    print('')
    return memory
    
def SourceCleaner( source ):
    clean = []
    for c in source:
        if c=='+':
            clean.extend([0])

inp = input("file: ")
file = open(inp, 'r')
string = "".join(file.readlines())
file.close()
InterpreterUncleaned(string)
