#!/bin/bash

GRIDPACK=${1} #full path to gridpack
PROC=${2}     #powheg processe.g. powhegbox_hvq
SEED=${3}     #seed to use
NEVTS=250

echo "*******************************"
echo "runGridpack.sh"
echo "*******************************"

echo "Creating project"
scram project CMSSW CMSSW_7_1_20
cd CMSSW_7_1_20/src
eval `scram r -sh`

echo "@ `pwd` unpacking gridpack"
cp ${GRIDPACK} ./mygridpack.tgz
gtar xzvf mygridpack.tgz

echo "Generating events"
./runcmsgrid.sh ${NEVTS} ${SEED} 4

echo "Copying to SE"
a=(`ls ${PROC}/*final*.lhe`)
cp ${a[0]} ../../events.lhe

echo "All done, cleaning up"
cd -
rm -rf CMSSW_7_1_20
