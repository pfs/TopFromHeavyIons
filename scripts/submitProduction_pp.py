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
parser.add_option('-c', '--cfg'        ,dest='cfg'    ,help='cfg for the GEN step' ,default='PYTHIA_5p02GeV_FULLSIM.py')
parser.add_option('-p', '--proc'       ,dest='proc'   ,help='process to generate'  ,default='TTbar')
parser.add_option('-o', '--output'     ,dest='output' ,help='output directory'     ,default='/store/cmst3/group/hintt/CMSSW_7_5_8_patch2/')
(opt, args) = parser.parse_args()

#prepare working directory
cmsswBase=os.environ['CMSSW_BASE']
workBase='%s/src/UserCode/TopFromHeavyIons' % cmsswBase
jobsBase='%s/FARM%s'%(workBase,time.time())
os.system('mkdir -p %s'%jobsBase)

#prepare output
opt.output='%s/%s/'%(opt.output,opt.proc)
os.system('cmsMkdir %s/RECO'%opt.output)

#loop over the required number of jobs
for n in xrange(1,opt.jobs+1):

    #create a wrapper for standalone cmssw job
    scriptFile = open('%s/runJob_%d.sh'%(jobsBase,n), 'w')
    scriptFile.write('#!/bin/bash\n')
    scriptFile.write('cd %s/src\n'%cmsswBase)
    scriptFile.write('eval `scram r -sh`\n')
    scriptFile.write('cd -\n')
    scriptFile.write('cmsRun %s/test/%s maxEvents=%d hardProc=%s jobSeed=%s\n' % (workBase,opt.cfg,opt.nevts,opt.proc,n) )
    scriptFile.write('xrdcp  -f Events_%d.root root://eoscms//eos/cms/%s/RECO/Events_%d.root\n' % (n,opt.output,n) )
    scriptFile.write('rm Events_%d.root\n' % n)
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
    
