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
#process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v12'
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v4'




process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('reco_RAW2DIGI_RECO.root'),
    #outputCommands = process.RECOSIMEventContent.outputCommands,
    outputCommands = cms.untracked.vstring("drop *"),
    splitLevel = cms.untracked.int32(0)
)
    
    
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
#process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)


##################################
#### costumization for Stage2 ####

#from HLTrigger.Configuration.customizeHLTforALL import customizeHLTforAll
##process = customizeHLTforAll(process,"GRun",_customInfo)

#from HLTrigger.Configuration.customizeHLTforCMSSW import customizeHLTforCMSSW
#process = customizeHLTforCMSSW(process,"GRun")








#--------------------------
#Define PAT sequence
#--------------------------

## Standard PAT Configuration File
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

#process.patElectrons.addElectronID = cms.bool(False)

## ---- remove MC references ----

#from PhysicsTools.PatAlgos.tools.coreTools import removeMCMatching
##removeMCMatching(process, ['All'], outputModules=[], postfix="")
#process.makePatElectrons.remove(process.electronMatch)
#process.makePatMuons.remove(process.muonMatch)

##process.patCandidates.remove(process.makePatTaus)
#process.makePatTaus.remove(process.tauMatch)
#process.makePatTaus.remove(process.tauGenJets)
#process.makePatTaus.remove(process.tauGenJetsSelectorAllHadrons)
#process.makePatTaus.remove(process.tauGenJetMatch)

#process.cleanPatTaus.preselection = cms.string('tauID("decayModeFinding") > 0.5 & tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 & tauID("againstMuonTight3") > 0.5 ')
    

#process.patMETs.addGenMET = cms.bool(False)


#process.makePatJets.remove(process.patJetPartonMatch)
#process.makePatJets.remove(process.patJetGenJetMatch)
#process.makePatJets.remove(process.patJetFlavourIdLegacy)
#process.makePatJets.remove(process.patJetFlavourId)



#process.makePatPhotons.remove(process.photonMatch)

##process.patJetPartonMatch+process.patJetGenJetMatch+process.patJetFlavourIdLegacy+process.patJetFlavourId

##from PhysicsTools.PatAlgos.tools.coreTools import *
##removeMCMatching(process, names=['All'], outputModules=[])
##process.patMuons.embedGenMatch = cms.bool(False)
##process.makePatElectrons.remove(process.electronMatch)
##process.makePatMuons.remove(process.muonMatch)




#process.options.allowUnscheduled = cms.untracked.bool(False)




























#import EventFilter.EcalRawToDigi.EcalUnpackerData_cfi
#process.ecalDigis = EventFilter.EcalRawToDigi.EcalUnpackerData_cfi.ecalEBunpacker.clone()
#process.ecalDigis.DoRegional = False

#use_raw_dat = False
#make_collections = ['digis']

process.TreeProducer = cms.EDAnalyzer('TreeProducer',
                           splitByLumi = cms.untracked.bool(False), # split the above average by lumisections (lumis must be in order in the file)
                           nPedestalSamples = cms.untracked.uint32(3), # number of first samples used to measure the pedestal
                           EBDigiCollection = cms.InputTag("ecalDigis","ebDigis"),
                           EEDigiCollection = cms.InputTag("ecalDigis","eeDigis"),
                           )


process.ZeeTreeProducer = cms.EDAnalyzer('ZeeTreeProducer',
                           splitByLumi = cms.untracked.bool(False), # split the above average by lumisections (lumis must be in order in the file)
                           nPedestalSamples = cms.untracked.uint32(3), # number of first samples used to measure the pedestal
                           EBDigiCollection = cms.InputTag("ecalDigis","ebDigis"),
                           EEDigiCollection = cms.InputTag("ecalDigis","eeDigis"),
                           EleTag           = cms.InputTag("gedGsfElectrons"),
                           )







process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(50)
##make_collections.remove('digis')   # ----> why?
#make_collections.append('rechits')

#if use_raw_dat:
    #process.source = cms.Source("NewEventStreamFileReader", fileNames = cms.untracked.vstring(options.inputFiles))
#else:
 
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(options.inputFiles),
                                secondaryFileNames = cms.untracked.vstring()
                                )
                                                    

process.load('RecoLocalCalo.EcalRecProducers.ecalUncalibRecHit_cfi')
process.load('RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi')
process.ecalUncalibRecHit.EBdigiCollection = cms.InputTag("ecalDigis","ebDigis")
process.ecalUncalibRecHit.EEdigiCollection = cms.InputTag("ecalDigis","eeDigis")
process.ecalMultiFitUncalibRecHit.EBdigiCollection = cms.InputTag("ecalDigis","ebDigis")
process.ecalMultiFitUncalibRecHit.EEdigiCollection = cms.InputTag("ecalDigis","eeDigis")
process.ecalMultiFitUncalibRecHit.algoPSet.useLumiInfoRunHeader = cms.bool(False)

process.ecalDigis_step = cms.Path(process.ecalDigis)
process.multifit = cms.Path(process.ecalMultiFitUncalibRecHit)
process.weights = cms.Path(process.ecalUncalibRecHit)

process.TreeProducer_step = cms.Path(process.TreeProducer * process.ZeeTreeProducer)
process.endjob_step = cms.EndPath(process.endOfProcess)

#process.dump = cms.EDAnalyzer("EventContentAnalyzer")
#process.dump_step = cms.Path(process.dump)



#process.schedule = cms.Schedule(process.ecalDigis_step, process.multifit, process.weights, process.TreeProducer_step, process.endjob_step)

#process.schedule2 = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step)
process.schedule2 = cms.Schedule(process.raw2digi_step, process.reconstruction_step,  process.ecalDigis_step, process.multifit, process.weights, process.TreeProducer_step    ,   process.endjob_step,process.RECOSIMoutput_step)


#if 'digis' in make_collections and 'rechits' in make_collections:
    #process.schedule = cms.Schedule(process.ecalDigis_step, process.multifit, process.weights, process.TreeProducer_step, process.endjob_step)
#elif 'digis' in make_collections:
    #process.schedule = cms.Schedule(process.ecalDigis_step, process.TreeProducer_step, process.endjob_step)
#elif 'rechits' in make_collections:
    #process.schedule = cms.Schedule(process.multifit, process.weights, process.TreeProducer_step, process.endjob_step)
#else:
    #process.schedule = cms.Schedule(process.TreeProducer_step, process.endjob_step)




# customisation of the process.

## Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
#from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

##call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
#process = customisePostLS1(process)




