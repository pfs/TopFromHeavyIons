#!/usr/bin/env python
import os,sys
import optparse
import commands
import time
import json

"""
"""
def submitJob(n,cfg,options,outF,output,cmsswBase,workBase,jobsBase):

    #create a wrapper for standalone cmssw job
    scriptFile = open('%s/runJob_%d.sh'%(jobsBase,n), 'w')
    scriptFile.write('#!/bin/bash\n')
    scriptFile.write('cd %s/src\n'%cmsswBase)
    scriptFile.write('eval `scram r -sh`\n')
    scriptFile.write('cd -\n')
    scriptFile.write('cmsRun %s/test/%s %s\n' % (workBase,cfg,options))
    scriptFile.write('eos mkdir %s\n'%output)
    scriptFile.write('eos mkdir %s/RECO\n'%output)
    scriptFile.write('xrdcp -f %s root://eoscms//eos/cms/%s/RECO/%s\n' % (outF,output,outF))
    scriptFile.write('rm %s\n'%outF)
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
    



#command line configuration
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-q', '--queue'      ,dest='queue'  ,help='batch queue'          ,default='')
parser.add_option('-j', '--jobs'       ,dest='jobs'   ,help='number of jobs'       ,default=1,    type=int)
parser.add_option('-n', '--nevts'      ,dest='nevts'  ,help='number of evetns/job' ,default=250,  type=int)
parser.add_option('-i', '--input'      ,dest='input'  ,help='input directory with GEN jobs' ,default=None,  type='string')
parser.add_option('-c', '--cfg'        ,dest='cfg'    ,help='cfg to run step' ,default='PYTHIA_5p02GeV_FULLSIM.py')
parser.add_option('-p', '--proc'       ,dest='proc'   ,help='process to generate'  ,default='TTbar')
parser.add_option('-o', '--output'     ,dest='output' ,help='output directory'     ,default='/store/cmst3/group/hintt/CMSSW_7_5_8_patch2/')
(opt, args) = parser.parse_args()

#prepare working directory
cmsswBase=os.environ['CMSSW_BASE']
workBase='%s/src/UserCode/TopFromHeavyIons' % cmsswBase
jobsBase='%s/FARM%s'%(workBase,time.time())
os.system('mkdir -p %s'%jobsBase)

if opt.input:
    from subprocess import Popen, PIPE
    eos_cmd = '/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select'
    data = Popen([eos_cmd, 'ls', '/eos/cms/'+opt.input],stdout=PIPE)
    out,err = data.communicate()
    n=0
    for line in out.split('\n'):
        if '.root' in line:

            data=Popen(['edmFileUtil','-j',opt.input+'/'+line],stdout=PIPE)
            jsonTxt,err=data.communicate()
            fileInfo=json.loads(jsonTxt)[0]
            fName=fileInfo['file']
            nEvts=int(fileInfo['events'])
            nJobs=int(nEvts/opt.nevts)
            if nJobs*opt.nevts<nEvts : njobs+=1
            print fName,'has',nEvts,'events and will be processed by',nJobs,'jobs'

            n+=1
            for j in xrange(0,nJobs):
                
                outF='Events_%d_%d.root'%(n,j)
                submitJob(n=(n*10000+j),
                          cfg=opt.cfg,
                          options='input=%s output=%s skipEvents=%d maxEvents=%d'%(opt.input + '/' + line,outF,j*opt.nevts,opt.nevts),
                          outF=outF,
                          output=opt.output,
                          cmsswBase=cmsswBase,
                          workBase=workBase,
                          jobsBase=jobsBase)
            
else:
    for n in xrange(1,opt.jobs+1):
        outF='Events_%d.root'%n
        submitJob(n=n,
                  cfg=opt.cfg,
                  options='maxEvents=%d hardProc=%s jobSeed=%s\n' % (opt.nevts,opt.proc,n),
                  outF=outF,
                  output=opt.output,
                  cmsswBase=cmsswBase,
                  workBase=workBase,
                  jobsBase=jobsBase)
        
