import FWCore.ParameterSet.Config as cms
from UserCode.TopFromHeavyIons.storeTools_cff import *

tt_PbPb=("ttbar_PbPb.root","/store/cmst3/group/top/summer2015/cmssw/PythiaTTbar/PbPb")
DY_PbPb=("DY_PbPb.root","/store/cmst3/user/psilva/HI/PythiaZjets/PbPb")

config = cms.PSet(
    output = cms.string(tt_PbPb[0]),
    input  = cms.vstring( fillFromStore(tt_PbPb[1]) ),
    maxEvents = cms.int32(5000)
    )
