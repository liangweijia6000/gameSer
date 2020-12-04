#!/usr/bin/python
# coding=utf-8

import platform
import os
import shutil
import sys

def isWin():
    return 'Windows' in platform.system()

def isLinux():
    return 'Linux' in platform.system()
    

def CreateEnum():
    return






if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("use create.sh")
        exit(0)

    argv = sys.argv[1]

    if argv == "CreateEnum":
        CreateEnum()
        exit(0)

