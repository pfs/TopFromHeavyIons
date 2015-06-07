# Top quark production from heavy ion collisions

## Installation

```
cmsrel CMSSW_7_5_0_pre5 
cd CMSSW_7_5_0_pre5/src/
cmsenv
wget -q -O - --no-check-certificate https://raw.github.com/pfs/TopFromHeavyIons/master/TAGS.txt | sh
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
cmsRun test/PYTHIA_2760GeV_GEN_SIM_PU_cfg.py maxEvents=1000 hardProc=pythiaTTbar jobSeed=1
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
These three steps can be run on the batch system, by using the following script.
```
python scripts/submitProduction.py -q 2nw -j 90 -n 100 -p pythiaTTbar -o /store/cmst3/group/top/summer2015/cmssw/PythiaTTbar
```
Other options can be passed. If no queue is given, jobs are sequentially run in the submission machine.

## Tree production

```
TODO
```
Will produce the HI analysis file from a given directory in EOS.
The "common" HI analysis file is called a HIForest file. 
Such a file is a collection of various TTrees, including muon, jet, etc, information. 
More details can be found at https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiForestSetup. 