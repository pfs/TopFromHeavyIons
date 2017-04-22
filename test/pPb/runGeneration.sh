#!/bin/bash
swDir=/afs/cern.ch/user/p/psilva/work/HIN/CMSSW_8_0_26_patch2/src/UserCode/TopFromHeavyIons
cd ${swDir}
eval `scram r -sh`
cd -
cmsRun ${swDir}/test/pPb/step1_${1}_cfg.py maxEvents=500 seed=${2}
cmsRun ${swDir}/test/pPb/step2_cfg.py
cmsRun ${swDir}/test/pPb/step3_cfg.py
xrdcp step3.root root://eoscms//eos/cms/store/cmst3/group/hintt/Pbp/8_0_26_patch2/PYQUEN_TTbar/${1}/Events_${2}.root
rm step*root