# Auto generated configuration file

# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Pyquen_ZeemumuJets_pt10_2760GeV_cfi.py --conditions MCHI2_75_V2 -s GEN,SIM --pileup_input das:/Hydjet_Quenched_MinBias_5020GeV/HiFall14-START71_V1-v2/GEN-SIM -n 10 --eventcontent FEVTDEBUG --scenario HeavyIons --pileup HiMixGEN --datatier GEN-SIM --beamspot MatchHI --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1_HI --magField 38T_PostLS1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('SIM')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.HiMixGEN_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.HiGenCommon.VtxSmearedMatchHI_cff')
process.load('Configuration.StandardSequences.GeneratorMix_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


#parse command line arguments
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('analysis')
options.register ('hardProc',
		  'pythiaTTbar',
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.string,
		  "Hard process to simulate with PYTHIA6 : pythiaTTbar/pythiaZjets")
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
    annotation = cms.untracked.string('PYQUEN Z->mumu and Z->ee (pt-hat > 10 GeV) at sqrt(s) = 2.76TeV'),
    name = cms.untracked.string('$Source: /local/projects/CMSSW/rep/CMSSW/Configuration/Generator/python/Pyquen_ZeemumuJets_pt10_2760GeV_cfi.py,v $'),
    version = cms.untracked.string('$Revision: 1.3 $')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('Events_%d.root' % options.jobSeed),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from UserCode.TopFromHeavyIons.Hydjet_Quenched_MinBias_5020GeV_cfi import getHIMinBiasFileList
process.mix.input.fileNames = getHIMinBiasFileList()
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'MCHI2_75_V2', '')

process.generator = cms.EDFilter("PyquenGeneratorFilter",
				 PythiaParameters = cms.PSet(customProcesses = cms.vstring('MSEL=0   ! User processes'),
							     hydjetPythiaDefault = cms.vstring('MSEL=0   ! user processes', 
											       'CKIN(3)=6.', 
											       'MSTP(81)=0'),
							     kinematics = cms.vstring('CKIN(3)=10', 
										      'CKIN(4)=9999', 
										      'CKIN(7)=-2.', 
										      'CKIN(8)=2.'),
							     myParameters = cms.vstring(),
							     parameterSets = cms.vstring('pythiaUESettings', 
											 'customProcesses', 
											 '%s' % options.hardProc,					  
											 'pythiaZtoLeptons',
											 'kinematics'),
							     ppDefault = cms.vstring('MSEL=1   ! QCD hight pT processes (only jets)', 
										     'CKIN(3)=6.', 
										     'MSTP(81)=0'),
							     ppJets = cms.vstring('MSEL=1   ! QCD hight pT processes'),
							     pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
											    'MSTJ(22)=2     ! Decay those unstable particles', 
											    'PARJ(71)=10 .  ! for which ctau  10 mm', 
											    'MSTP(2)=1      ! which order running alphaS', 
											    'MSTP(33)=0     ! no K factors in hard cross sections', 
											    'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
											    'MSTP(52)=2     ! work with LHAPDF', 
											    'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
											    'MSTP(82)=4     ! Defines the multi-parton model', 
											    'MSTU(21)=1     ! Check on possible errors during program execution', 
											    'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
											    'PARP(89)=1960. ! sqrts for which PARP82 is set', 
											    'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
											    'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
											    'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
											    'PARP(67)=2.5    ! amount of initial-state radiation', 
											    'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
											    'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
											    'PARP(62)=1.25   ! ', 
											    'PARP(64)=0.2    ! ', 
											    'MSTP(91)=1      !', 
											    'PARP(91)=2.1   ! kt distribution', 
											    'PARP(93)=15.0  ! '),
							     pythiaWjets = cms.vstring('MSUB(16)=1', 
										       'MSUB(31)=1'),
							     pythiaZjets = cms.vstring('MSUB(15)=1', 
										       'MSUB(30)=1'),
							     pythiaTTbar = cms.vstring('MSUB(81)  = 1     ! qqbar to QQbar',
										       'MSUB(82)  = 1     ! gg to QQbar',
										       'MSTP(7)   = 6     ! flavor = top',
										       'PMAS(6,1) = 172.5  ! top quark mass'),
							     pythiaZtoLeptons = cms.vstring('MDME(174,1)=0', 
											    'MDME(175,1)=0', 
											    'MDME(176,1)=0', 
											    'MDME(177,1)=0', 
											    'MDME(178,1)=0', 
											    'MDME(179,1)=0', 
											    'MDME(182,1)=1', 
											    'MDME(183,1)=0', 
											    'MDME(184,1)=1', 
											    'MDME(185,1)=0', 
											    'MDME(186,1)=1', 
											    'MDME(187,1)=0'),
							     pythiaWtoLeptons = cms.vstring('MDME(190,1) = 0   !W decay into dbar u',
											    'MDME(191,1) = 0   !W decay into dbar c',
											    'MDME(192,1) = 0   !W decay into dbar t',
											    'MDME(194,1) = 0   !W decay into sbar u',
											    'MDME(195,1) = 0   !W decay into sbar c',
											    'MDME(196,1) = 0   !W decay into sbar t',
											    'MDME(198,1) = 0   !W decay into bbar u',
											    'MDME(199,1) = 0   !W decay into bbar c',
											    'MDME(200,1) = 0   !W decay into bbar t',
											    'MDME(206,1) = 1   !W decay into e+ nu_e',
											    'MDME(207,1) = 1   !W decay into mu+ nu_mu',
											    'MDME(208,1) = 1   !W decay into tau+ nu_tau')
							     ),
				 aBeamTarget = cms.double(208.0),
				 angularSpectrumSelector = cms.int32(0),
				 bFixed = cms.double(0.0),
				 bMax = cms.double(0.0),
				 bMin = cms.double(0.0),
				 backgroundLabel = cms.InputTag("generator"),
				 cFlag = cms.int32(0),
				 comEnergy = cms.double(5020.0),
				 doCollisionalEnLoss = cms.bool(False),
				 doIsospin = cms.bool(True),
				 doQuench = cms.bool(True),
				 doRadiativeEnLoss = cms.bool(True),
				 embeddingMode = cms.bool(False),
				 hadronFreezoutTemperature = cms.double(0.14),
				 numQuarkFlavor = cms.int32(0),
				 qgpInitialTemperature = cms.double(1.0),
				 qgpNumQuarkFlavor = cms.int32(0),
				 qgpProperTimeFormation = cms.double(0.1)
				 )

if options.hardProc == 'pythiaWjets':  
	process.generator.PythiaParameters.parameterSets.append('pythiaWtoLeptons')

process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.FEVTDEBUGoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_HI 

#call to customisation function customisePostLS1_HI imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1_HI(process)

process.RandomNumberGeneratorService.generator.initialSeed=cms.untracked.uint32(options.jobSeed)
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

# End of customisation functions

