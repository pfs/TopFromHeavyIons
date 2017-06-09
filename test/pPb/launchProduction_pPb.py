#!/usr/bin/env python

import os

outStore='/store/cmst3/user/psilva/HI/Powheg/'
baseGridpackDir='/afs/cern.ch/user/p/psilva/public/forGeorgios'
gridpacks=[ 
    'TT_hdamp_NNPDF23_8p16TeV_hvq',
    'TT_hdamp_pPb_pp_NNPDF23_EPS09NLO_8.16TeV_hvq',
    'TT_hdamp_Pbp_pp_NNPDF23_EPS09NLO_8.16TeV_hvq'
    ]
cmsswbase='{0}/src/UserCode/TopFromHeavyIons/test/pPb/'.format(os.environ['CMSSW_BASE'])

for g in gridpacks:
    os.system('eos mkdir {0}/{1}'.format(outStore,g))
    
    workdir='%s'%g
    os.system('mkdir -p %s'%workdir)
    condorName='%s/%s.sub'%(workdir,g)
    with open(condorName,'w') as condor:
        condor.write('executable = {0}/{1}/$(seed)/job.sh\n'.format(cmsswbase,workdir))
        condor.write('output     = {0}/{1}/$(seed)/output.out\n'.format(cmsswbase,workdir))
        condor.write('error      = {0}/{1}/$(seed)/output.err\n'.format(cmsswbase,workdir))
        
        for seed in xrange(1,201):

            condor.write('seed=%d\n'%seed)
            condor.write('queue 1\n')

            seedDir='%s/%s'%(workdir,seed)
            os.system('mkdir -p %s'%seedDir)
            scriptName='%s/job.sh'%seedDir
            with open(scriptName,'w') as script:
                script.write('#!/bin/bash\n')
                script.write('{0}/runGridpack.sh {1}/{2}.tgz powhegbox_hvq {3}\n'.format(cmsswbase,baseGridpackDir,g,seed))
                script.write('{0}/runEmbedGenerationFromLHE.sh {1}/{2} file:events.lhe {3}\n'.format(cmsswbase,outStore,g,seed))
            os.system('chmod u+x {0}'.format(scriptName))
    
    os.system('condor_submit %s'%condorName)
