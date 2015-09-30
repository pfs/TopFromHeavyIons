#!/usr/bin/env python

import os,sys
import optparse
import commands
import time
import sys
import ROOT

usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-d', '--dir',  dest='dir',            help='input directory', default='')
(opt, args) = parser.parse_args()

from UserCode.TopFromHeavyIons.storeTools_cff import fillFromStore

for tier in ['RECO','NTUPLE']:

    allFiles=fillFromStore(opt.dir+'/'+tier)

    totEvts=0
    nremoved=0
    for f in allFiles :
        try:
            tfile = ROOT.TFile.Open(f)
            if tfile.GetSize()<1024 or tfile.TestBit(ROOT.TFile.kRecovered) :
                tfile.Close()
                raise IOError

            iEvts=0
            if tier=='NTUPLE':
                iEvts=tfile.Get('hiEvtAnalyzer/HiTree').GetEntriesFast()
            elif tier=='RECO':
                iEvts=tfile.Get('Events').GetEntriesFast()
            if iEvts==0 : 
                tfile.Close()
                raise IOError
            totEvts+=iEvts
            tfile.Close()
        except:
            pos = f.find('/store')
            result=commands.getstatusoutput('cmsRm %s'%(f[pos:]))
            nremoved+=1

    print '[ %s ] total events available %d (%d files removed in tier %s)'%(opt.dir,totEvts,nremoved,tier)
