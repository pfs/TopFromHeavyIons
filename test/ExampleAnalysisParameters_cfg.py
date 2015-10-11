import FWCore.ParameterSet.Config as cms
from UserCode.TopFromHeavyIons.storeTools_cff import *
import FWCore.ParameterSet.VarParsing as VarParsing

## parse some command line arguments
#options = VarParsing.VarParsing ('analysis')

#options.register ('anaFile',
#                  1, # default value
#                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
#                  VarParsing.VarParsing.varType.int,       # string, int, or float
#                  "Number of files to process (-1 for all)")

#options.anaFile = 1

#options.parseArguments()

#print('anaFile: ',options.anaFile)

tt_PbPb=("ttbar_PbPb.root","/store/cmst3/group/hintt/CMSSW/TT/NTUPLE")
#tt_PbPb=("ttbar_PbPb.root","/store/cmst3/user/psilva/HI/PythiaTTbar/PbPb")
DY_PbPb=("DY_PbPb.root","/store/cmst3/group/hintt/CMSSW/DY/NTUPLE")
centralityRequirements={"inc":[0,200],
                        "0to20":[0,40],
                        "20to50":[40,100],
                        "50to80":[100,160],
                        "80to100":[160,200]}


sample=tt_PbPb
#sample=DY_PbPb

centralityBins=centralityRequirements["inc"]
#centralityBins=centralityRequirements["0to20"]
#centralityBins=centralityRequirements["20to50"]
#centralityBins=centralityRequirements["50to80"]
#centralityBins=centralityRequirements["80to100"]

config = cms.PSet(
    output = cms.string('cen_%dto%d_%s'%(centralityBins[0],centralityBins[1],sample[0])),
    input  = cms.vstring( fillFromStore(sample[1]) ),
    maxEvents = cms.int32(-1),
    minCentrality = cms.int32(centralityBins[0]),
    maxCentrality = cms.int32(centralityBins[1])#,
   # anaFile = cms.int32(options.anaFile)
)
