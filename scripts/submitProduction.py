#!/usr/bin/env python
import os,sys
import optparse
import commands
import time

#command line configuration
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-q', '--queue'      ,dest='queue'  ,help='batch queue'          ,default='')
parser.add_option('-j', '--jobs'       ,dest='jobs'   ,help='number of jobs'       ,default=1,    type=int)
parser.add_option('-n', '--nevts'      ,dest='nevts'  ,help='number of evetns/job' ,default=100,  type=int)
parser.add_option('-c', '--cfg'        ,dest='cfg'    ,help='cfg for the GEN step' ,default='PYQUEN_2760GeV_GEN_SIM_PU_cfg.py')
parser.add_option('-p', '--proc'       ,dest='proc'   ,help='process to generate'  ,default='pythiaTTbar')
parser.add_option(      '--proxy'      ,dest='proxy'  ,help='proxy to be used'     ,default=None, type='string')
parser.add_option('-o', '--output'     ,dest='output' ,help='output directory'     ,default='/store/cmst3/group/hintt/CMSSW/')
parser.add_option(      '--extra'      ,dest='extra'  ,help='extra options to pass',default='', type='string')
(opt, args) = parser.parse_args()

#prepare working directory
cmsswBase=os.environ['CMSSW_BASE']
workBase='%s/src/UserCode/TopFromHeavyIons' % cmsswBase
jobsBase='%s/FARM%s'%(workBase,time.time())
os.system('mkdir -p %s'%jobsBase)

#prepare output
os.system('cmsMkdir %s/NTUPLE'%opt.output)
os.system('cmsMkdir %s/RECO'%opt.output)

#init a new proxy if none has been passed
if opt.proxy is None:
    print 'Initiating a new proxy'
    os.system('voms-proxy-init --voms cms --valid 72:00')
    os.system('cp /tmp/x509up_u`id -u \`whoami\`` %s/proxyforprod' % workBase)
    print 'Production proxy is now available in %s/proxyforprod (valid for 72h)' % workBase

#loop over the required number of jobs
for n in xrange(1,opt.jobs+1):

    #create a wrapper for standalone cmssw job
    scriptFile = open('%s/runJob_%d.sh'%(jobsBase,n), 'w')
    scriptFile.write('#!/bin/bash\n')
    scriptFile.write('export X509_USER_PROXY=%s/proxyforprod\n' % workBase)
    scriptFile.write('cd %s/src\n'%cmsswBase)
    scriptFile.write('eval `scram r -sh`\n')
    scriptFile.write('cd -\n')
    scriptFile.write('cmsRun %s/test/%s maxEvents=%d hardProc=%s jobSeed=%s %s\n' % (workBase,opt.cfg,opt.nevts,opt.proc,n,opt.extra) )
    scriptFile.write('cmsRun %s/test/DIGIStep_cfg.py isPP=False inputFiles=file:Events_%d.root\n' % (workBase,n) )
    scriptFile.write('cmsRun %s/test/RECOStep_cfg.py isPP=False inputFiles=file:Events_%d_DIGI.root\n' % (workBase,n) )
    scriptFile.write('cmsRun %s/test/runHIForest_MC_cfg.py inputFiles=file:Events_%d_DIGI_RECO.root outputFile=HIForest_%s_%d.root\n' % (workBase,n,opt.proc,n)) 
    scriptFile.write('cmsStage Events_%d_DIGI_RECO.root %s/RECO/Events_%d.root\n' % (n,opt.output,n) )
    scriptFile.write('cmsStage HIForest_%s_%d.root %s/NTUPLE/Events_%d.root\n' % (opt.proc,n,opt.output,n) )
    scriptFile.write('rm Events_%d*root\n' % n)
    scriptFile.write('rm HIForest_%s_%d.root\n' % (opt.proc,n))
    scriptFile.close()

    #preare to run it
    os.system('chmod u+rwx %s/runJob_%d.sh'%(jobsBase,n))

    #submit it to the batch or run it locally
    if opt.queue=='':
        print 'Job #%d will run locally' % n
        os.system('%s/runJob_%d.sh' % (jobsBase,n) )
    else:
        print 'Job #%d will run remotely' % n
        os.system("bsub -q %s -R \"swp>1000 && pool>30000\" -J HISIM%d \'%s/runJob_%d.sh\'" % (opt.queue,n,jobsBase,n) )
    
