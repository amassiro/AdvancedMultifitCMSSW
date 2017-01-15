########
# Data
########

#        CRAB task name          DAS name           
#samples['DoubleEG_Run2016G-23Sep2016-v1']       = ['/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD',    ['outputFile=test.root']]
samples['DoubleEG_Run2016C-23Sep2016-v1']       = ['/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD',    ['outputFile=test.root']]

config.Data.useParent = True           # Important!



########
# Alternative global configuration
########

config.Data.splitting = 'LumiBased'    # FileBased
config.Data.unitsPerJob   = 10
# config.Data.runRange = '251562-254790'

config.JobType.psetName = '../runRecoPATAndDump.py'
config.JobType.maxMemoryMB = 2500    # 2.5 GB

config.Data.outLFNDirBase = '/store/user/amassiro/ECAL/LocalReco/test07Jan2017/'
config.Data.lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-282092_13TeV_PromptReco_Collisions16_JSON.txt"
config.General.workArea     = 'crab_projects_7Jan2017_localReco'
config.Data.allowNonValidInputDataset = True
#config.JobType.inputFiles = ['../EBAlign_2015.db','../EEAlign_2015.db']


#hadd /tmp/amassiro/test.root  /tmp/amassiro/eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jan2017/DoubleEG/crab_DoubleEG_Run2016C-23Sep2016-v1/170109_172141/00*/failed/test_*.root



