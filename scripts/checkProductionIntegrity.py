#!/usr/bin/env python

import os,sys
import optparse
import commands
import time

def runMergeFiles(mergeFiles,igroup,opt) :
    outputStr='Events_%d.root'%igroup
    inputStr=''
    for f in mergeFiles : inputStr+=f+','
    inputStr = inputStr[:-1]
    os.system('edmCopyPickMerge inputFiles=%s outputFile=%s'%(inputStr,outputStr))
    os.system('cmsStage %s %s'%(outputStr,opt.dir))
    if opt.deleteOriginal : 
        for f in mergeFiles : 
            os.system('cmsRm %s'%f)

usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-d', '--dir',  dest='dir',            help='input directory', default='')
parser.add_option('-r',           dest='deleteOriginal', help='delete original', action='store_true')
parser.add_option('-m',           dest='mergeOriginal',  help='mere original',    action='store_true')
(opt, args) = parser.parse_args()

from UserCode.TopFromHeavyIons.storeTools_cff import fillFromStore
allFiles=fillFromStore(opt.dir)

totEvts=0
mergeFiles=[]
igroup=0
nremoved=0
for f in allFiles :
    try:
        result=commands.getstatusoutput('edmFileUtil -P %s | grep -ir bytes | awk \'{print $6}\''%f)
        iEvts=int(result[1])
        totEvts+=iEvts
        if opt.mergeOriginal : mergeFiles.append(f)
    except:
        pos = f.find('/store')
        result=commands.getstatusoutput('cmsRm %s'%(f[pos:]))
        nremoved+=1

    if len(mergeFiles)==4 and opt.mergeOriginal: 
        igroup=igroup+1
        runMergeFiles(mergeFiles,igroup,opt)
        mergeFiles=[]

if len(mergeFiles)>1 and opt.mergeOriginal:
    igroup=igroup+1
    runMergeFiles(mergeFiles,igroup,opt) 

print '[ %s ] total events available %d (%d files removed)'%(opt.dir,totEvts,nremoved)
