# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: UserCode/TopFromHeavyIons/python/Pyquen_TTbar_TuneZ2_8160GeV_pythia6_cfi.py --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions 80X_mcRun2_pA_v4 --beamspot RealisticPPbBoost8TeV2016Collision --step GEN,SIM --era Run2_2016 --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 100
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('SIM',eras.Run2_2016)


from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('analysis')
options.register ('seed',
		  1,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.int,
		  "Random seed to use for the job")
options.parseArguments()





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
process.load('GeneratorInterface.HiGenCommon.VtxSmearedPPb8TeVBoost_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('PYQUEN-Wmunu Tune Z2 at 5.023 TeV'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/GenProduction/python/HI/Pyquen_WToMuNu_TuneZ2_5023GeV_pythia6_cfi.py,v $'),
    version = cms.untracked.string('$Revision: 1.1 $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('step1.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_pA_v4', '')

process.generator = cms.EDFilter("PyquenGeneratorFilter",
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters'),
        processParameters = cms.vstring('MSEL      = 0      !User defined processes', 
            'MSUB(81)  = 1      ! qqbar to QQbar', 
            'MSUB(82)  = 1      ! gg to QQbar', 
            'MSTP(7)   = 6      ! flavour = top', 
            'PMAS(6,1) = 172.5  ! top quark mass', 
	    'MDME(190,1) = 1    !W decay into dbar u', 
            'MDME(191,1) = 1    !W decay into dbar c', 
            'MDME(192,1) = 1    !W decay into dbar t', 
            'MDME(194,1) = 1    !W decay into sbar u', 
            'MDME(195,1) = 1    !W decay into sbar c', 
            'MDME(196,1) = 1    !W decay into sbar t', 
            'MDME(198,1) = 1    !W decay into bbar u', 
            'MDME(199,1) = 1    !W decay into bbar c', 
            'MDME(200,1) = 1    !W decay into bbar t', 
            'MDME(205,1) = 1    !W decay into bbar tp', 
            'MDME(206,1) = 1    !W decay into e+ nu_e', 
            'MDME(207,1) = 1    !W decay into mu+ nu_mu', 
            'MDME(208,1) = 1    !W decay into tau+ nu_tau'),
        pythiaUESettings = cms.vstring('MSTU(21)=1     ! Check on possible errors during program execution', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'PARP(82)=1.832 ! pt cutoff for multiparton interactions', 
            'PARP(89)=1800. ! sqrts for which PARP82 is set', 
            'PARP(90)=0.275 ! Multiple interactions: rescaling power', 
            'MSTP(95)=6     ! CR (color reconnection parameters)', 
            'PARP(77)=1.016 ! CR', 
            'PARP(78)=0.538 ! CR', 
            'PARP(80)=0.1   ! Prob. colored parton from BBR', 
            'PARP(83)=0.356 ! Multiple interactions: matter distribution parameter', 
            'PARP(84)=0.651 ! Multiple interactions: matter distribution parameter', 
            'PARP(62)=1.025 ! ISR cutoff', 
            'MSTP(91)=1     ! Gaussian primordial kT', 
            'PARP(93)=10.0  ! primordial kT-max', 
            'MSTP(81)=21    ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model')
    ),
    aBeamTarget = cms.double(208.0),
    angularSpectrumSelector = cms.int32(0),
    bFixed = cms.double(0.0),
    bMax = cms.double(0.0),
    bMin = cms.double(0.0),
    backgroundLabel = cms.InputTag("generator"),
    cFlag = cms.int32(0),
    comEnergy = cms.double(8160.0),
    doCollisionalEnLoss = cms.bool(False),
    doIsospin = cms.bool(True),
    doQuench = cms.bool(False),
    doRadiativeEnLoss = cms.bool(True),
    embeddingMode = cms.bool(False),
    hadronFreezoutTemperature = cms.double(0.14),
    maxEventsToPrint = cms.untracked.int32(0),
    numQuarkFlavor = cms.int32(0),
    protonSide = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(True),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    qgpInitialTemperature = cms.double(1.0),
    qgpNumQuarkFlavor = cms.int32(0),
    qgpProperTimeFormation = cms.double(0.1)
)


process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

process.RandomNumberGeneratorService.generator.initialSeed=cms.untracked.uint32(options.seed)
process.MessageLogger.cerr.FwkReport.reportEvery = 5000

# End of customisation functions

