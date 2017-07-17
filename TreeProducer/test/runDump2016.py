# test reco and dump into a tree

import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()



from Configuration.StandardSequences.Eras import eras

process = cms.Process('AdvancedMultifit', eras.Run2_25ns)

# import of standard configurations
#process.load('Configuration.StandardSequences.Services_cff')
#process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')





process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)

process.TFileService = cms.Service("TFileService",
     fileName = cms.string(options.outputFile)
)

process.options = cms.untracked.PSet(
#    SkipEvent = cms.untracked.vstring('ProductNotFound'),
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('reco nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Other statements
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v12', '')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v4'   # ---> working for 2016

# for 2016 Legacy data
process.GlobalTag.globaltag = '80X_dataRun2_2016LegacyRepro_v3'

#
# activate the Run based
#

process.GlobalTag.toGet = cms.VPSet(

          cms.PSet(record = cms.string("EcalPedestalsRcd"),
                   tag = cms.string("EcalPedestals_Legacy2016_v1"),
                   connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")
                  ),
  
)

    

process.ZeeTreeProducer = cms.EDAnalyzer('ZeeTreeProducer',
                           splitByLumi = cms.untracked.bool(False), # split the above average by lumisections (lumis must be in order in the file)
                           nPedestalSamples = cms.untracked.uint32(3), # number of first samples used to measure the pedestal
                           EBDigiCollection = cms.InputTag("selectDigi","selectedEcalEBDigiCollection"),
                           EEDigiCollection = cms.InputTag("selectDigi","selectedEcalEEDigiCollection"),
                           EleTag           = cms.InputTag("gedGsfElectrons"),
                           )







process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(50)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(options.inputFiles),
                                secondaryFileNames = cms.untracked.vstring()
                                )
                                                    

process.load('RecoLocalCalo.EcalRecProducers.ecalUncalibRecHit_cfi')
process.load('RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi')
process.ecalUncalibRecHit.EBdigiCollection = cms.InputTag("selectDigi","selectedEcalEBDigiCollection")
process.ecalUncalibRecHit.EEdigiCollection = cms.InputTag("selectDigi","selectedEcalEEDigiCollection")
process.ecalMultiFitUncalibRecHit.EBdigiCollection = cms.InputTag("selectDigi","selectedEcalEBDigiCollection")
process.ecalMultiFitUncalibRecHit.EEdigiCollection = cms.InputTag("selectDigi","selectedEcalEEDigiCollection")
process.ecalMultiFitUncalibRecHit.algoPSet.useLumiInfoRunHeader = cms.bool(False)

process.multifit = cms.Path(process.ecalMultiFitUncalibRecHit)
process.weights = cms.Path(process.ecalUncalibRecHit)

process.TreeProducer_step = cms.Path(process.ZeeTreeProducer)
process.endjob_step = cms.EndPath(process.endOfProcess)


process.schedule2 = cms.Schedule( process.multifit, process.weights, process.TreeProducer_step    ,   process.endjob_step)



