#!/usr/bin/env python2
# -*- coding : 'utf-8' -*-

__author__ = 'Herixth'

import re, os

patt = ['.h', '.cpp', '.py', '.asm']

def readIgnore():
    with open('D:/Study/procedure(py)/reptile/.ign') as igFile:
        return list(map(lambda elem: elem[:-1], igFile.readlines()))

def judge_str(strs, ignore_):
    for elem in ignore_:
        if elem in strs:
            return False
    return True

def judge(file, dirpath, ignore_):
    return judge_str(dirpath + file, ignore_) and os.path.splitext(file)[1] in patt


def getPath():
    readIgnore()
    print('Current path:\n>>', os.getcwd())
    dirlist = input(
        'Input files\' path: (different path using \'&\' to connect)\n>> ').split('&')
    return map(lambda strss: strss.strip().replace('/', '\\'), dirlist)


def getAllFile(path):
    allFile = []
    ignore_ = readIgnore()
    for dirpath, dirnames, filenames in os.walk(path):
        allFile.extend([os.path.join(dirpath, file) for file in filenames if judge(file, dirpath, ignore_)])
    return allFile


def cntSigPath(sigpath):
    cnt = 0
    for file in sigpath:
        count = len(open(file, 'rb').readlines())
        print(">> file: %s\n   curr: %-d  sum: %-d" % (file, count, cnt + count))
        cnt += count
    return cnt


def countLine(filepaths):
    result = [cntSigPath(sigpath) for sigpath in [getAllFile(sublist) for sublist in filepaths]]
    print('-------------------------------------')
    print(result)
    print('total: %d' % sum(result))
    print('-------------------------------------')


if __name__ == '__main__':
    countLine(getPath())
    paste = input('Enter any key to exit.')
