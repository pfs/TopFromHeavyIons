import FWCore.ParameterSet.Config as cms
from UserCode.TopFromHeavyIons.storeTools_cff import *

tt_PbPb=("ttbar_PbPb.root","/store/cmst3/group/top/summer2015/cmssw/PythiaTTbar")

config = cms.PSet(
    output = cms.string(tt_PbPb[0]),
    input  = cms.vstring( fillFromStore(tt_PbPb[1]) )
    )
