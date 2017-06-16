#!/bin/bash

store=${1} #/store/cmst3/user/psilva/HI/Powheg/TT_hdamp_pPb_pp_NNPDF23_EPS09NLO_8.16TeV
inputlhe=${2} #/store/group/phys_top/gkrintir/TopHI/TT_8160GeV/PowHeg/LHAPDF5/NNPDF23/TT_hdamp_pPb_pp_NNPDF23_EPS09NLO_8.16TeV_powhe_hvq/seed_9_cmsgrid_final.lhe
seed=${3}
mode=${4}

echo "***************************"
echo "runEmbedGenerationFromLHE.sh"
echo "***************************"


echo "Setting up environment"
swDir=/afs/cern.ch/user/p/psilva/work/HIN/CMSSW_8_0_26_patch2/src
cd ${swDir}
eval `scram r -sh`
cd -
echo "Now @ `pwd`"
export X509_USER_PROXY=${CMSSW_BASE}/src/UserCode/TopFromHeavyIons/test/pPb/proxyforprod

echo "Starting GEN-SIM"
cmsRun $swDir/UserCode/TopFromHeavyIons/test/pPb/TOP-RunIISummer15GS-00033-${mode}-fragment_py_GEN_SIM_PU.py seed=${seed}
#cmsDriver.py UserCode/TopFromHeavyIons/python/TOP-RunIISummer15GS-00033-fragment.py \
#    --filein ${inputlhe} --filetype LHE \
#    --fileout file:step0.root \
#    -n -1 \
#    --pileup_input "dbs:/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/pPb816Spring16GS-MB_80X_mcRun2_pA_v4-v2/GEN-SIM" \
#    --mc --eventcontent RAWSIM --pileup HiMixGEN --customise Configuration/StandardSequences/SimWithCastor_cff.py \
#    --datatier GEN-SIM --conditions 80X_mcRun2_pA_v4 --beamspot MatchPbPBoost --step GEN,SIM \
#    --scenario HeavyIons --era Run2_2016_pA \
#    --pileup_dasoption "--limit 0"

echo "Starting DIGI"
cmsRun $swDir/UserCode/TopFromHeavyIons/test/pPb/step1_DIGI_L1_DIGI2RAW_HLT_PU.py
#cmsDriver.py step1 --filein file:step0.root --fileout file:step1.root \
#    --pileup_input "dbs:/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/pPb816Spring16GS-MB_80X_mcRun2_pA_v4-v2/GEN-SIM" \
#    --mc --eventcontent RAWSIM --pileup HiMix --datatier GEN-SIM-RAW \
#    --conditions 80X_mcRun2_pA_v4 --step DIGI,L1,DIGI2RAW,HLT:PIon \
#    --era Run2_2016_pA \
#    -n -1 \
#    --pileup_dasoption "--limit 0"

echo "Starting RECO"
cmsRun $swDir/UserCode/TopFromHeavyIons/test/pPb/step2_RAW2DIGI_L1Reco_RECO.py
#cmsDriver.py step2 --filein file:step1.root --fileout file:step2.root \
#    --mc --eventcontent AODSIM --datatier AODSIM --conditions 80X_mcRun2_pA_v4 \
#    --customise_commands "process.bunchSpacingProducer.bunchSpacingOverride=cms.uint32(25)\n process.bunchSpacingProducer.overrideBunchSpacing=cms.bool(True)" \
#    -n -1 \
#    --step RAW2DIGI,L1Reco,RECO --era Run2_2016_pA

xrdcp step2.root root://eoscms//eos/cms/${store}/Events_${seed}.root
#rm step*root
