# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --filein file:previous_output.root --conditions MCHI2_75_V2 --scenario HeavyIons --pileup_input das:/Hydjet_Quenched_MinBias_5020GeV/HiFall14-START71_V1-v2/GEN-SIM -n 2 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW,HLT:HIon,RAW2DIGI,L1Reco --beamspot RealisticHI2011Collision --datatier GEN-SIM-DIGI-RAW-HLTDEBUG --pileup HiMix --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1_HI --magField 38T_PostLS1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.HiMix_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#parse command line arguments
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('analysis')
options.register ('isPP',
		  False,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Flag if this is a pp simulation")
options.parseArguments()

#prepare output
import os
outputFile=os.path.basename(options.inputFiles[0]).replace('.root','_DIGI.root')
if  len(options.inputFiles)!=1:
    print '[WARNING] I will only digitize 1st file of the ones passed to inputFiles'
print '          output will be %s'%outputFile

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
process.source = cms.Source("PoolSource",
                            dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
                            fileNames = cms.untracked.vstring(options.inputFiles[0]),
                            inputCommands = cms.untracked.vstring('keep *', 
                                                                  #'drop *_genParticles_*_*', 
                                                                  'drop *_genParticlesForJets_*_*', 
                                                                  #'drop *_kt4GenJets_*_*', 
                                                                  'drop *_kt6GenJets_*_*', 
                                                                  'drop *_iterativeCone5GenJets_*_*', 
                                                                  'drop *_ak4GenJets_*_*', 
                                                                  'drop *_ak7GenJets_*_*', 
                                                                  'drop *_ak8GenJets_*_*', 
                                                                  'drop *_ak4GenJetsNoNu_*_*', 
                                                                  'drop *_ak8GenJetsNoNu_*_*', 
                                                                  'drop *_genCandidatesForMET_*_*', 
                                                                  'drop *_genParticlesForMETAllVisible_*_*', 
                                                                  'drop *_genMetCalo_*_*', 
                                                                  'drop *_genMetCaloAndNonPrompt_*_*', 
                                                                  'drop *_genMetTrue_*_*', 
                                                                  'drop *_genMetIC5GenJs_*_*'),
                            secondaryFileNames = cms.untracked.vstring()
                            )

process.options = cms.untracked.PSet(
    )

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:2'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW-HLTDEBUG'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(1048576),
    fileName = cms.untracked.string(outputFile),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from UserCode.TopFromHeavyIons.Hydjet_Quenched_MinBias_5020GeV_cfi import getHIMinBiasFileList
if not options.isPP : process.mix.input.fileNames = getHIMinBiasFileList()
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'MCHI2_75_V2', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.endjob_step,process.FEVTDEBUGHLToutput_step])

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_HI 

#call to customisation function customisePostLS1_HI imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1_HI(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforFullSim 

#call to customisation function customizeHLTforFullSim imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforFullSim(process)

#FORCE BEAMSPOT
from CondCore.DBCommon.CondDBSetup_cfi import *
process.beamspot = cms.ESSource("PoolDBESSource",CondDBSetup,
                                toGet = cms.VPSet(cms.PSet( record = cms.string('BeamSpotObjectsRcd'),
                                                            tag= cms.string('RealisticHICollisions2011_STARTHI50_mc')
                                                            )),
                                connect =cms.string('frontier://FrontierProd/CMS_COND_31X_BEAMSPOT')
                                )
process.es_prefer_beamspot = cms.ESPrefer("PoolDBESSource","beamspot")

process.MessageLogger.cerr.FwkReport.reportEvery = 5000
# End of customisation functions

