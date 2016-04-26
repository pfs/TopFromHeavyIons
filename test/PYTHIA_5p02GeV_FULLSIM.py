# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: TTbar_8TeV_TuneCUETP8M1_cfi.py --beamspot Nominal5TeVpp2015Collision --mc --eventcontent RECO --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --datatier RECO --conditions 75X_mcRun2_asymptotic_ppAt5TeV_v3 --step GEN,SIM,DIGI,L1,DIGI2RAW,HLT:PRef,RAW2DIGI,L1Reco,RECO --no_exec
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
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedNominal5TeVpp2015Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
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
options.register ('hardProc',
		  'TTbar',
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.string,
		  "Hard process to simulate with PYTHIA6 : TTbar/W/DY,DYlowMass")
options.register ('jobSeed',
		  1,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.int,
		  "Randmo seed to use for the job")
options.parseArguments()


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)


# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('TTbar_8TeV_TuneCUETP8M1_cfi.py nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('Events_%d.root' % options.jobSeed),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_asymptotic_ppAt5TeV_v3', '')


myproc=cms.vstring('Top:qqbar2ttbar=on',
		   'Top:gg2ttbar = on ', 
		   '6:m0 = 172.5 ')
if options.hardProc=='W':
	myproc=cms.vstring( 'WeakSingleBoson:ffbar2W = on',
			    '24:onMode = off',
			    '24:onIfAny = 11 12',
			    '24:onIfAny = 13 14',
			    '24:onIfAny = 15 16')
if options.hardProc=='DY':
	myproc=cms.vstring('WeakSingleBoson:ffbar2gmZ = on',
			   'PhaseSpace:mHatMin = 50.',
			   '23:onMode = off',
			   '23:onIfAny = 11 11',
			   '23:onIfAny = 13 13',
			   '23:onIfAny = 15 15')
if options.hardProc=='DYlowMass':
	myproc=cms.vstring('WeakSingleBoson:ffbar2gmZ = on',
			   'PhaseSpace:mHatMin = 20.',
			   'PhaseSpace:mHatMax = 50.',
			   '23:onMode = off',
			   '23:onIfAny = 11 11',
			   '23:onIfAny = 13 13',
			   '23:onIfAny = 15 15')

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    PythiaParameters = cms.PSet(
		parameterSets = cms.vstring('pythia8CommonSettings', 
					    'pythia8CUEP8M1Settings', 
					    'processParameters'),
		processParameters = myproc,
		pythia8CUEP8M1Settings = cms.vstring('Tune:pp 14', 
						     'Tune:ee 7', 
						     'MultipartonInteractions:pT0Ref=2.4024', 
						     'MultipartonInteractions:ecmPow=0.25208', 
						     'MultipartonInteractions:expPow=1.6'),
		pythia8CommonSettings = cms.vstring('Tune:preferLHAPDF = 2', 
						    'Main:timesAllowErrors = 10000', 
						    'Check:epTolErr = 0.01', 
						    'Beams:setProductionScalesFromLHEF = off', 
						    'SLHA:keepSM = on', 
						    'SLHA:minMassSM = 1000.', 
						    'ParticleDecays:limitTau0 = on', 
						    'ParticleDecays:tau0Max = 10', 
						    'ParticleDecays:allowPhotonRadiation = on')
		),
				 comEnergy = cms.double(5020.0),
				 filterEfficiency = cms.untracked.double(1.0),
				 maxEventsToPrint = cms.untracked.int32(0),
				 pythiaHepMCVerbosity = cms.untracked.bool(False),
				 pythiaPylistVerbosity = cms.untracked.int32(0)
				 )

print process.generator.PythiaParameters.processParameters


process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step])
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforFullSim 

#call to customisation function customizeHLTforFullSim imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforFullSim(process)

process.RandomNumberGeneratorService.generator.initialSeed=cms.untracked.uint32(options.jobSeed)
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

# End of customisation functions

