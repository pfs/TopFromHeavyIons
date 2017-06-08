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
    
    condorName='%s.sub'%g
    with open(condorName,'w') as condor:
        condor.write('executable = {0}/{1}_$(seed).sh\n'.format(cmsswbase,g))
        condor.write('output     = $(seed).$(ClusterId).$(ProcId).out\n')
        condor.write('error      = $(seed).$(ClusterId).$(ProcId).err\n')
        
        for seed in xrange(1,101):

            condor.write('seed=%d\n'%seed)
            condor.write('queue 1\n')

            scriptName='%s_%s.sh'%(g,seed)
            with open(scriptName,'w') as script:
                script.write('#!/bin/bash\n')
                script.write('{0}/runGridpack.sh {1}/{2}.tgz powhegbox_hvq {3}\n'.format(cmsswbase,baseGridpackDir,g,seed))
                script.write('{0}/runEmbedGenerationFromLHE.sh {1}/{2} file:events.lhe {3}\n'.format(cmsswbase,outStore,g,seed))
            os.system('chmod u+x {0}'.format(scriptName))
    
    os.system('condor_submit %s'%condorName)
