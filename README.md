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

## Production
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
```
Will run the DIGI step for the previous set of events
```
```
Will run the RECO step for the previous set events
