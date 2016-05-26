# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: reco --beamspot Nominal5TeVpp2015Collision --mc --eventcontent RECO --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --datatier RECO --conditions 75X_mcRun2_asymptotic_ppAt5TeV_v3 --step SIM,DIGI,L1,DIGI2RAW,HLT:PRef,RAW2DIGI,L1Reco,RECO --no_exec --filein=test.root
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_PRef_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#parse command line arguments
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('analysis')
options.register ('input',
		  '',
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.string,
		  "Input file")
options.register ('output',
		  'Events.root',
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.string,
		  "output file")
options.register ('skipEvents',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.int,
		  "starting event number")
options.parseArguments()

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
process.source = cms.Source("PoolSource",
                            skipEvents=cms.untracked.uint32(options.skipEvents),
                            dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
                            fileNames = cms.untracked.vstring(options.input),
                            inputCommands = cms.untracked.vstring('keep *', 
                                                                  #        'drop *_genParticles_*_*', 
                                                                  #        'drop *_genParticlesForJets_*_*', 
                                                                  #        'drop *_kt4GenJets_*_*', 
                                                                  #        'drop *_kt6GenJets_*_*', 
                                                                  #        'drop *_iterativeCone5GenJets_*_*', 
                                                                  #        'drop *_ak4GenJets_*_*', 
                                                                  #        'drop *_ak7GenJets_*_*', 
                                                                  #        'drop *_ak8GenJets_*_*', 
                                                                  #        'drop *_ak4GenJetsNoNu_*_*', 
                                                                  #        'drop *_ak8GenJetsNoNu_*_*', 
                                                                  #        'drop *_genCandidatesForMET_*_*', 
                                                                  #        'drop *_genParticlesForMETAllVisible_*_*', 
                                                                  #        'drop *_genMetCalo_*_*', 
                                                                  #        'drop *_genMetCaloAndNonPrompt_*_*', 
                                                                  #        'drop *_genMetTrue_*_*', 
                                                                  #        'drop *_genMetIC5GenJs_*_*'
                                                                  ),
                            secondaryFileNames = cms.untracked.vstring()
                            )

process.options = cms.untracked.PSet()

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('reco nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string(options.output),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_asymptotic_ppAt5TeV_v3', '')

# Path and EndPath definitions
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforFullSim 

#call to customisation function customizeHLTforFullSim imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforFullSim(process)

process.MessageLogger.cerr.FwkReport.reportEvery = 50

# End of customisation functions

