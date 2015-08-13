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
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.HiGenCommon.VtxSmearedMatchHI_cff')
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
    annotation = cms.untracked.string('PYTHIA at sqrt(s) = 2.76TeV'),
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
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'MCHI2_75_V2', '')

process.generator = cms.EDFilter("Pythia6GeneratorFilter",
                                 ExternalDecays = cms.PSet(Tauola = cms.untracked.PSet(UseTauolaPolarization = cms.bool(True),
                                                                                       InputCards = cms.PSet(mdtau = cms.int32(0),
                                                                                                             pjak2 = cms.int32(0),
                                                                                                             pjak1 = cms.int32(0)
                                                                                                             )
                                                                                       ),
                                                           parameterSets = cms.vstring('Tauola')
                                                           ),
                                 UseExternalGenerators = cms.untracked.bool(True),
                                 pythiaPylistVerbosity = cms.untracked.int32(1),
                                 pythiaHepMCVerbosity = cms.untracked.bool(True),
                                 comEnergy = cms.double(2760.0),
                                 maxEventsToPrint = cms.untracked.int32(0),
                                 crossSection = cms.untracked.double(1),
                                 PythiaParameters = cms.PSet(processParameters = cms.vstring('MSEL=0         ! User defined processes', 
											     'MSUB(81)  = 1     ! qqbar to QQbar',
											     'MSUB(82)  = 1     ! gg to QQbar',
											     'MSTP(7)   = 6     ! flavor = top',
											     'PMAS(5,1)=4.8   ! b quark mass', 
											     'PMAS(6,1)=172.5 ! t quark mass', 
											     'MSTJ(1)=1       ! Fragmentation/hadronization on or off', 
											     'MSTP(61)=1      ! Parton showering on or off'),
							     kinematics = cms.vstring('CKIN(3)=10', 
										      'CKIN(4)=9999', 
										      'CKIN(7)=-2.', 
										      'CKIN(8)=2.'),
							     parameterSets = cms.vstring('pythiaUESettings', 
											 '%s' % options.hardProc,
											 'pythiaWtoLeptons',
											 'pythiaZtoLeptons',
											 'kinematics'),
							     ppDefault = cms.vstring('MSEL=1   ! QCD hight pT processes (only jets)', 
										     'CKIN(3)=6.', 
										     'MSTP(81)=0'),
							     ppJets = cms.vstring('MSEL=1   ! QCD hight pT processes'),
							     pythiaBottomoniumNRQCD = cms.vstring('MSUB(461) = 1', 
												  'MSUB(462) = 1', 
												  'MSUB(463) = 1', 
												  'MSUB(464) = 1', 
												  'MSUB(465) = 1', 
												  'MSUB(466) = 1', 
												  'MSUB(467) = 1', 
												  'MSUB(468) = 1', 
												  'MSUB(469) = 1', 
												  'MSUB(470) = 1', 
												  'MSUB(471) = 1', 
												  'MSUB(472) = 1', 
												  'MSUB(473) = 1', 
												  'MSUB(474) = 1', 
												  'MSUB(475) = 1', 
												  'MSUB(476) = 1', 
												  'MSUB(477) = 1', 
												  'MSUB(478) = 1', 
												  'MSUB(479) = 1'),
							     pythiaCharmoniumNRQCD = cms.vstring('MSUB(421) = 1', 
												 'MSUB(422) = 1', 
												 'MSUB(423) = 1', 
												 'MSUB(424) = 1', 
												 'MSUB(425) = 1', 
												 'MSUB(426) = 1', 
												 'MSUB(427) = 1', 
												 'MSUB(428) = 1', 
												 'MSUB(429) = 1', 
												 'MSUB(430) = 1', 
												 'MSUB(431) = 1', 
												 'MSUB(432) = 1', 
												 'MSUB(433) = 1', 
												 'MSUB(434) = 1', 
												 'MSUB(435) = 1', 
												 'MSUB(436) = 1', 
												 'MSUB(437) = 1', 
												 'MSUB(438) = 1', 
												 'MSUB(439) = 1'),
							     pythiaHirootDefault = cms.vstring('MSEL=0', 
											       'MSTU(21)=1', 
											       'PARU(14)=1.', 
											       'MSTP(81)=0', 
											       'PMAS(5,1)=4.8', 
											       'PMAS(6,1)=175.0', 
											       'CKIN(3)=7.', 
											       'MSTJ(22)=2', 
											       'PARJ(71)=10.', 
											       'PARP(67)=1.', 
											       'PARP(82)=1.9', 
											       'PARP(85)=0.33', 
											       'PARP(86)=0.66', 
											       'PARP(89)=1000.', 
											       'PARP(91)=1.0', 
											       'MSTJ(11)=3', 
											       'MSTJ(22)=2'),
							     pythiaJets = cms.vstring('MSUB(11)=1', 
										      'MSUB(12)=1', 
										      'MSUB(13)=1', 
										      'MSUB(28)=1', 
										      'MSUB(53)=1', 
										      'MSUB(68)=1'),
							     pythiaJpsiToMuons = cms.vstring('BRAT(858) = 0 ', 
											     'BRAT(859) = 1 ', 
											     'BRAT(860) = 0 ', 
											     'MDME(858,1) = 0 ', 
											     'MDME(859,1) = 1 ', 
											     'MDME(860,1) = 0 '),
							     pythiaMuonCandidates = cms.vstring('CKIN(3)=20', 
												'MSTJ(22)=2', 
												'PARJ(71)=40.'),
							     pythiaPromptPhotons = cms.vstring('MSUB(14)=1', 
											       'MSUB(18)=1', 
											       'MSUB(29)=1', 
											       'MSUB(114)=1', 
											       'MSUB(115)=1'),
							     pythiaQuarkoniaSettings = cms.vstring('PARP(141)=1.16', 
												   'PARP(142)=0.0119', 
												   'PARP(143)=0.01', 
												   'PARP(144)=0.01', 
												   'PARP(145)=0.05', 
												   'PARP(146)=9.28', 
												   'PARP(147)=0.15', 
												   'PARP(148)=0.02', 
												   'PARP(149)=0.02', 
												   'PARP(150)=0.085', 
												   'PARJ(13)=0.60', 
												   'PARJ(14)=0.162', 
												   'PARJ(15)=0.018', 
												   'PARJ(16)=0.054', 
												   'MSTP(145)=0', 
												   'MSTP(146)=0', 
												   'MSTP(147)=0', 
												   'MSTP(148)=1', 
												   'MSTP(149)=1', 
												   'BRAT(861)=0.202', 
												   'BRAT(862)=0.798', 
												   'BRAT(1501)=0.013', 
												   'BRAT(1502)=0.987', 
												   'BRAT(1555)=0.356', 
												   'BRAT(1556)=0.644'),
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
							     pythiaUpsilonToMuons = cms.vstring('BRAT(1034) = 0 ', 
												'BRAT(1035) = 1 ', 
												'BRAT(1036) = 0 ', 
												'BRAT(1037) = 0 ', 
												'BRAT(1038) = 0 ', 
												'BRAT(1039) = 0 ', 
												'BRAT(1040) = 0 ', 
												'BRAT(1041) = 0 ', 
												'BRAT(1042) = 0 ', 
												'MDME(1034,1) = 0 ', 
												'MDME(1035,1) = 1 ', 
												'MDME(1036,1) = 0 ', 
												'MDME(1037,1) = 0 ', 
												'MDME(1038,1) = 0 ', 
												'MDME(1039,1) = 0 ', 
												'MDME(1040,1) = 0 ', 
												'MDME(1041,1) = 0 ', 
												'MDME(1042,1) = 0 '),
							     pythiaWeakBosons = cms.vstring('MSUB(1)=1', 
											    'MSUB(2)=1'),
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
											    'MDME(208,1) = 0   !W decay into tau+ nu_tau')
							     )
				 )



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

