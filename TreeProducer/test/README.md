Example
====

    cmsRun runRecoPATAndDump.py  inputFiles=file:/eos/cms/store/data/Run2017A/DoubleEG/RAW-RECO/ZElectron-PromptReco-v2/000/296/168/00000/5EC59A07-5A4C-E711-AF4B-02163E01A46D.root
    
    
    Run 283270 --> ~ 400/pb in one run 
    https://cmswbm.cern.ch/cmsdb/servlet/RunSummary?RUN=283270
    /DoubleEG/Run2016H-ZElectron-PromptReco-v2/RAW-RECO
    
    xrdcp root://cms-xrd-global.cern.ch//store/data/Run2016H/DoubleEG/RAW-RECO/ZElectron-PromptReco-v2/000/281/613/00000/6C606673-CE84-E611-A7D4-02163E0126CD.root /tmp/amassiro/
    
    cmsRun runRecoPATAndDump2016.py             inputFiles=file:/tmp/amassiro/6C606673-CE84-E611-A7D4-02163E0126CD.root
    cmsRun runRecoPATAndDump2016floatingPed.py  inputFiles=file:/tmp/amassiro/6C606673-CE84-E611-A7D4-02163E0126CD.root
    
    
    
    cmsRun runDump2016.py             inputFiles=file:/afs/cern.ch/user/a/askew/public/pickevents_2.root
    cmsRun runDump2016.py             inputFiles=file:/afs/cern.ch/user/a/askew/public/pickevents_3.root
    cmsRun runDump2016.py             inputFiles=file:/afs/cern.ch/user/a/askew/public/pickevents_4.root

    
    
    
    
    
plot:

    r00t plotPulse.cxx\(\"output.root\",1\)

    for i in {0..8}; do    echo "r00t -q -b plotPulse.cxx\(\\\"output.root\\\",$i\)"; done
    for i in {0..8}; do    r00t -q -b plotPulse.cxx\(\"output.root\",$i\); done
    
    
    r00t FilterTree.cxx\(\"output.root\",\"outputFilter.root\"\)
    r00t plotPulse.cxx\(\"outputFilter.root\",1\)

    
    
    
    r00t FilterTreeZee.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_90.root\",\"outputFilterZee.root\"\)

    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "r00t -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floating/"$2"\\\"\\\)"}'
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floating/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/floating.root /tmp/amassiro/floating/*.root
    
    cp /tmp/amassiro/floating.root   /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170708_143814/
    
    
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170707_114845/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/standard/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/standard.root /tmp/amassiro/standard/*.root
    
    cp /tmp/amassiro/standard.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170707_114845/
    
    

    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170711_092233/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/oneRun/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/oneRun.root /tmp/amassiro/oneRun/*.root
    
    cp /tmp/amassiro/oneRun.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170711_092233/
    

    
    
    
    
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-RunBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080653/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/RunBased/"$2"\\\"\\\)"}'  | /bin/sh
    hadd /tmp/amassiro/RunBased.root /tmp/amassiro/RunBased/*.root
    cp /tmp/amassiro/RunBased.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-RunBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080653/

    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080454/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/increasedNoise/"$2"\\\"\\\)"}'  | /bin/sh
    hadd /tmp/amassiro/increasedNoise.root /tmp/amassiro/increasedNoise/*.root
    cp /tmp/amassiro/increasedNoise.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080454/

    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-TimeBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080742/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/TimeBased/"$2"\\\"\\\)"}'  | /bin/sh
    hadd /tmp/amassiro/TimeBased.root /tmp/amassiro/TimeBased/*.root
    cp /tmp/amassiro/TimeBased.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-TimeBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080742/

    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floatingPedestal/"$2"\\\"\\\)"}'  | /bin/sh
    hadd /tmp/amassiro/floatingPedestal.root /tmp/amassiro/floatingPedestal/*.root
    cp /tmp/amassiro/floatingPedestal.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/

    
    
    
    
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-RunBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080653/0000/
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080454/0000/
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-TimeBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080742/0000/
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000/
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170713_152400/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floating-RAW/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/floating.root /tmp/amassiro/floating-RAW/*.root
    
    cp /tmp/amassiro/floating.root   /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170713_152400/
    
    
    
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test24Jul2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170725_110542/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/floating-RAW/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/floating.root /tmp/amassiro/floating-RAW/*.root
    
    cp /tmp/amassiro/floating.root   /eos/cms/store/user/amassiro/ECAL/LocalReco/test24Jul2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170725_110542/
    

    
    r00t plotPulse.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test24Jul2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170725_110542/0000/test_8.root\",1\)

    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test24Jul2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170725_110542/0000/test_1.root\",\"/tmp/amassiro/pulse_floatingPedestal.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test28Jul2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170727_143548/0000/test_1.root\",\"/tmp/amassiro/pulse_increasedNoise.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170713_152136/0000/test_1.root\",\"/tmp/amassiro/pulse_singlePed.root\"\)

    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_floatingPedestal.root\",1\)
    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_increasedNoise.root\",1\)
    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_singlePed.root\",1\)
    
    
    
 
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170713_152136/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/oneRun-RAW/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/oneRun.root /tmp/amassiro/oneRun-RAW/*.root
    
    cp /tmp/amassiro/oneRun.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test07Jul2017-singleRunPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170713_152136/
    


    
    
    
    
    
 
    ls /eos/cms/store/user/amassiro/ECAL/LocalReco/test28Jul2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170727_143548/0000/test_*.root | sed -e 's/0000/\ /g'  \
    |  awk '{print "root -l -b -q FilterTreeZee.cxx\\\(\\\""$1"0000"$2"\\\",\\\"/tmp/amassiro/increasedNoise-RAW/"$2"\\\"\\\)"}'  | /bin/sh
    
    hadd /tmp/amassiro/increasedNoise.root /tmp/amassiro/increasedNoise-RAW/*.root
    
    cp /tmp/amassiro/increasedNoise.root  /eos/cms/store/user/amassiro/ECAL/LocalReco/test28Jul2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170727_143548/
    


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}-raw\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}-raw\",\"1\",\"RunBased\",\"eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}-raw\",\"1\",\"RunBased\",\"\!\(eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\)\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    
    
    
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}-raw\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/increasedNoise.root\",\"increasedNoise\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}-raw\",\"1\",\"RunBased\",\"eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\",\"/tmp/amassiro/increasedNoise.root\",\"increasedNoise\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}-raw\",\"1\",\"RunBased\",\"\!\(eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\)\",\"/tmp/amassiro/increasedNoise.root\",\"increasedNoise\"\)
    
    
    
    
    
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/standard.root\",\"standard\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"RunBased\",\"eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\&\&eta1_advanced_multifit\>-1.5\&\&eta2_advanced_multifit\>-1.5\",\"/tmp/amassiro/standard.root\",\"standard\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/oneRun.root\",\"mee_advanced_multifit\",200,70,110,\"m_{ll}\",\"1\",\"RunBased\",\"eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\&\&eta1_advanced_multifit\>-1.5\&\&eta2_advanced_multifit\>-1.5\",\"/tmp/amassiro/standard.root\",\"standard\"\)
    
    
    
    
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"standard\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)

    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"standard\",\"eta1_advanced_multifit\>1.5\&\&eta2_advanced_multifit\>1.5\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"standard\",\"eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"mee_advanced_multifit\",100,70,120,\"m_{ll}\",\"1\",\"standard\",\"eta1_advanced_multifit\<1.5\&\&eta2_advanced_multifit\<1.5\&\&eta1_advanced_multifit\>-1.5\&\&eta2_advanced_multifit\>-1.5\",\"/tmp/amassiro/floating.root\",\"floating\"\)

    
    
    
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"pt1_advanced_multifit\",100,0,200,\"p_{T1}\",\"1\",\"standard\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"eta1_advanced_multifit\",100,-3,3,\"#eta_{1}\",\"1\",\"standard\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)

    
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"pt2_advanced_multifit\",100,0,200,\"p_{T2}\",\"1\",\"standard\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/standard.root\",\"eta2_advanced_multifit\",100,-3,3,\"#eta_{2}\",\"1\",\"standard\",\"1\",\"/tmp/amassiro/floating.root\",\"floating\"\)

    
    
    r99t /tmp/amassiro/standard.root
    tree = (TTree*) _file0 -> Get ("ZeeTreeProducer/electrons");
    tree->Draw("mee_advanced_multifit:lumi", "mee_advanced_multifit>60 && mee_advanced_multifit<120", "colz")
    
    
    r99t /tmp/amassiro/floating.root
    tree = (TTree*) _file0 -> Get ("ZeeTreeProducer/electrons");
    tree->Draw("mee_advanced_multifit:lumi", "mee_advanced_multifit>60 && mee_advanced_multifit<120", "colz")
    
    
    