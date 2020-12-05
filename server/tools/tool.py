#!/usr/bin/python
# coding=utf-8

import platform
import os
import shutil
import sys
from xml.dom import minidom, Node

def isWin():
    return 'Windows' in platform.system()

def isLinux():
    return 'Linux' in platform.system()
    
#TODO:Exception
def CreateEnum():
    tempfile = open("./temp.enum", "w")
    doc = minidom.parse('./protobuf.xml')
    protobufs = doc.getElementsByTagName('protobuf')
    count = 0
    for protobufs in protobufs:
        enumName = protobufs.attributes['name'].value
        enumId = protobufs.attributes['id'].value
        writeStr = "    E" + enumName + " = " + enumId + ",\n"
        tempfile.write(writeStr)
        if count % 5 == 0:
            print(".", end="")
        count = count + 1
    return

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("error:use create.sh")
        exit(0)

    argv = sys.argv[1]

    if argv == "CreateEnum":
        CreateEnum()
        exit(0)

