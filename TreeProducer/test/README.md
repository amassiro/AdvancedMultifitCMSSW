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

    

