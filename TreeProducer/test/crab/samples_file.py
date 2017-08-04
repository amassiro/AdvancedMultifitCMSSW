########
# Data
########

#        CRAB task name          DAS name           
#samples['DoubleEG_Run2016G-23Sep2016-v1']       = ['/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD',    ['outputFile=test.root']]
#samples['DoubleEG_Run2016C-23Sep2016-v1']       = ['/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD',    ['outputFile=test.root']]
#config.Data.useParent = True           # Important!



samples['DoubleEG_Run2016H-OneRun']       = ['/DoubleEG/Run2016H-ZElectron-PromptReco-v2/RAW-RECO',    ['outputFile=test.root']]




########
# Alternative global configuration
########

config.Data.splitting = 'LumiBased'    # FileBased
config.Data.unitsPerJob   = 10
# config.Data.runRange = '251562-254790'

#config.JobType.psetName = '../runRecoPATAndDump.py'
#config.JobType.maxMemoryMB = 2500    # 2.5 GB

#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test07Jan2017/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-282092_13TeV_PromptReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_7Jan2017_localReco'
#config.Data.allowNonValidInputDataset = True
##config.JobType.inputFiles = ['../EBAlign_2015.db','../EEAlign_2015.db']

#hadd /tmp/amassiro/test.root  /tmp/amassiro/eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jan2017/DoubleEG/crab_DoubleEG_Run2016C-23Sep2016-v1/170109_172141/00*/failed/test_*.root



config.JobType.maxMemoryMB = 2500    # 2.5 GB

config.Data.runRange = '283270'

#config.JobType.psetName = '../runRecoPATAndDump2016.py'
#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test07Jul2017-RAW/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_7Jul2017_oneRun'

#hadd /tmp/amassiro/test_legacy.root /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170707_114845/0000/test_*.root


#config.JobType.psetName = '../runRecoPATAndDump2016floatingPed.py'
##config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal-RAW/'
#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test24Jul2017-floatingPedestal-RAW/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_7Jul2017_oneRun_floatingPedestal'


#hadd /tmp/amassiro/test_floating.root /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_*.root



#
# GT modified by hand in the runRecoPATAndDump2016.py code
#

#config.JobType.psetName = '../runRecoPATAndDump2016.py'
#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal-RAW/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_7Jul2017_oneRun_singlePed'


#hadd /tmp/amassiro/test_fixed.root /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170711_092233/0000/test_*.root






##
## increased noise in EB and EE
##

#config.JobType.psetName = '../runRecoPATAndDump2016noiseIncrease.py'
#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test04Aug2017-increasedNoise-RAW/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_04Aug2017_oneRun_increasedNoise'




##
## Floating pedestal
##

#config.JobType.psetName = '../runRecoPATAndDump2016floatingPed.py'
#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_04Aug2017_oneRun_floatingPedestal'



##
## Run based
##

#config.JobType.psetName = '../runRecoPATAndDump2016RunBased.py'
#config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test04Aug2017-RunBased-RAW/'
#config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
#config.General.workArea     = 'crab_projects_04Aug2017_oneRun_RunBased'





#
# Time based
#

config.JobType.psetName = '../runRecoPATAndDump2016.py'
config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test04Aug2017-TimeBased-RAW/'
config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"
config.General.workArea     = 'crab_projects_04Aug2017_oneRun_TimeBased'








