# Top quark production from heavy ion collisions

## Installation

```
cmsrel CMSSW_8_0_26_patch2
cd CMSSW_8_0_26_patch2/src/
cmsenv
git clone git@github.com:pfs/TopFromHeavyIons.git UserCode/TopFromHeavyIons
scram b -j 9
cd UserCode/TopFromHeavyIons/
```

## Sample production
```
voms-proxy-init --voms cms --valid 72:00
```
Will init a proxy, given files used for the mixing will be retrieved with AAA.
The following three commands enables testing production locally.
```
cmsRun test/PYQUEN_2760GeV_GEN_SIM_PU_cfg.py maxEvents=1000 hardProc=pythiaTTbar jobSeed=1
```
Will run the GEN-SIM step for 1000 ttbar events
```
cmsRun test/DIGIStep_cfg.py inputFiles=file:Events_1.root [maxEvents=1000]
```
Will run the DIGI step for the previous set of events
```
cmsRun test/RECOStep_cfg.py inputFiles=file:Events_1_DIGI.root [maxEvents=1000]
```
Will run the RECO step for the previous set events.
```
cmsRun test/runHIForest_MC_cfg.py inputFiles=/store/cmst3/group/top/summer2015/cmssw/PythiaTTbar/
```
Will produce the HI analysis file from a given directory in EOS.
The "common" HI analysis file is called a HIForest file. 
Such a file is a collection of various TTrees, including muon, jet, etc, information. 
More details can be found at https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiForestSetup. 

These four steps can be run on the batch system sequentially, by using the following script.
```
python scripts/submitProduction.py -q 2nw -j 5000 -n 250 -p pythiaZjets -o /store/cmst3/group/hintt/CMSSW/DY
python scripts/submitProduction.py -q 1nw -j 5000 -n 250 -p pythiaWjets -o /store/cmst3/group/hintt/CMSSW/W
python scripts/submitProduction.py -q 1nw -j 5000 -n 250 -p pythiaTTbar -o /store/cmst3/group/hintt/CMSSW/TT --proxy `pwd`/proxyforprod
python scripts/submitProduction.py -q 1nw -j 5000 -n 100000 -p pythiaQCD --cfg PYQUEN_2760GeV_QCDEMenriched_GEN_SIM_PU_cfg.py -o /store/cmst3/group/hintt/CMSSW/QCDEMriched_80to250 --extra "minPtHat=80 maxPtHat=250"
```
Other options can be passed. If no queue is given, jobs are sequentially run in the submission machine.


