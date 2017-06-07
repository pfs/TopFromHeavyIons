#!/bin/bash

store=${1} #/store/cmst3/group/hintt/Pbp/8_0_26_patch2/POWHEG_ttbar/
inputlhe=${2} #/eos/cms/store/group/phys_top/gkrintir/TopHI/TT_8160GeV/PowHeg/LHAPDF5/NNPDF23/TT_hdamp_pPb_pp_NNPDF23_EPS09NLO_8.16TeV_powhe_hvq/seed_9_cmsgrid_final.lhe

swDir=/afs/cern.ch/user/p/psilva/work/HIN/CMSSW_8_0_26_patch2/src/UserCode/TopFromHeavyIons
cd ${swDir}
eval `scram r -sh`
cd -

echo "Starting GEN-SIM"
cmsDriver.py Configuration/GenProduction/python/HIN-pPb816Spring16GS-00077-fragment.py \
    --fileout file:step0.root \
    --pileup_input "dbs:/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/pPb816Spring16GS-MB_80X_mcRun2_pA_v4-v2/GEN-SIM" \
    --mc --eventcontent RAWSIM --pileup HiMixGEN --customise Configuration/StandardSequences/SimWithCastor_cff.py \
    --datatier GEN-SIM --conditions 80X_mcRun2_pA_v4 --beamspot MatchPbPBoost --step GEN,SIM \
    --scenario HeavyIons --era Run2_2016_pA \
    --pileup_dasoption "--limit 0"

echo "Starting DIGI"
cmsDriver.py step1 --fileout file:step1.root \
    --pileup_input "dbs:/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/pPb816Spring16GS-MB_80X_mcRun2_pA_v4-v2/GEN-SIM" \
    --mc --eventcontent RAWSIM --pileup HiMix --datatier GEN-SIM-RAW \
    --conditions 80X_mcRun2_pA_v4 --step DIGI,L1,DIGI2RAW,HLT:PIon \
    --era Run2_2016_pA \
    --pileup_dasoption "--limit 0"

echo "Starting RECO"
cmsDriver.py step2 --filein file:step1.root --fileout file:step3.root \
    --mc --eventcontent AODSIM --datatier AODSIM --conditions 80X_mcRun2_pA_v4 \
    --customise_commands "process.bunchSpacingProducer.bunchSpacingOverride=cms.uint32(25)\n process.bunchSpacingProducer.overrideBunchSpacing=cms.bool(True)" \
    --step RAW2DIGI,L1Reco,RECO --era Run2_2016_pA

xrdcp step2.root root://eoscms//eos/cms/${store}/Events_${2}.root
rm step*root
