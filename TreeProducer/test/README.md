Example
====

    cmsRun runRecoPATAndDump.py  inputFiles=file:/eos/cms/store/data/Run2017A/DoubleEG/RAW-RECO/ZElectron-PromptReco-v2/000/296/168/00000/5EC59A07-5A4C-E711-AF4B-02163E01A46D.root
    
    
    Run 283270 --> ~ 400/pb in one run 
    https://cmswbm.cern.ch/cmsdb/servlet/RunSummary?RUN=283270
    /DoubleEG/Run2016H-ZElectron-PromptReco-v2/RAW-RECO
    
    xrdcp root://cms-xrd-global.cern.ch//store/data/Run2016H/DoubleEG/RAW-RECO/ZElectron-PromptReco-v2/000/281/613/00000/6C606673-CE84-E611-A7D4-02163E0126CD.root /tmp/amassiro/
    
    cmsRun runRecoPATAndDump2016.py             inputFiles=file:/tmp/amassiro/6C606673-CE84-E611-A7D4-02163E0126CD.root
    cmsRun runRecoPATAndDump2016floatingPed.py  inputFiles=file:/tmp/amassiro/6C606673-CE84-E611-A7D4-02163E0126CD.root
    
    
plot:

    r00t plotPulse.cxx\(\"output.root\",1\)

    r00t FilterTree.cxx\(\"output.root\",\"outputFilter.root\"\)
    r00t plotPulse.cxx\(\"outputFilter.root\",1\)

    
    r00t FilterTreeZee.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_90.root\",\"outputFilterZee.root\"\)

    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "r00t -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floating/"$2"\\\"\\\)"}'
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floating/"$2"\\\"\\\)"}'  | /bin/sh
    
    
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170707_114845/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/standard/"$2"\\\"\\\)"}'  | /bin/sh
    