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

    
    
    
    
    Check high eta and MET PD
    xrdcp root://cms-xrd-global.cern.ch//store/data/Run2017F/MET/RAW-RECO/HighMET-PromptReco-v1/000/305/040/00000/5E03A8E9-1BB2-E711-841D-02163E0144CC.root  /tmp/amassiro/
    
    cmsRun runRecoPATAndDump.py   inputFiles=file:/tmp/amassiro/5E03A8E9-1BB2-E711-841D-02163E0144CC.root
    r00t -q FilterTree.cxx\(\"output.root\",\"outputFilter.root\"\)
    r00t plotPulse.cxx\(\"outputFilter.root\",1\)  
    r00t plotPulse.cxx\(\"outputFilter.root\",-1,872439603\)
    
    
    
    
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

    
    

    
    
    
    
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-RunBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080653/0000/test_1.root\",\"/tmp/amassiro/pulse_RunBased.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080454/0000/test_1.root\",\"/tmp/amassiro/pulse_increasedNoise.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-TimeBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080742/0000/test_1.root\",\"/tmp/amassiro/pulse_TimeBased.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_1.root\",\"/tmp/amassiro/pulse_floatingPedestal.root\"\)

    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_1.root\",\"/tmp/amassiro/pulse_floatingPedestal.1.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_10.root\",\"/tmp/amassiro/pulse_floatingPedestal.10.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_20.root\",\"/tmp/amassiro/pulse_floatingPedestal.20.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_30.root\",\"/tmp/amassiro/pulse_floatingPedestal.30.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_40.root\",\"/tmp/amassiro/pulse_floatingPedestal.40.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_100.root\",\"/tmp/amassiro/pulse_floatingPedestal.100.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_110.root\",\"/tmp/amassiro/pulse_floatingPedestal.110.root\"\)
    r00t -q FilterTree.cxx\(\"/eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000//test_140.root\",\"/tmp/amassiro/pulse_floatingPedestal.140.root\"\)
    
    
    
    
    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_RunBased.root\",1\)
    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_increasedNoise.root\",1\)
    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_TimeBased.root\",1\)
    r00t plotPulse.cxx\(\"/tmp/amassiro/pulse_floatingPedestal.root\",1\)

    
    
    root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/ana_ped_v4.root
    /eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/ana_ped_2016-2017.root    
    
    root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/ana_ped_2017_14_08.root
    /eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/ana_ped_2017_14_08.root    
    
    
T rootuple content: 

id --> file number 
run --> run number 
run_type --> 1=collisions, 2=cosmics, 3=circulating, 4=test, 0=other not classified 
seq_id --> within a run is the calibration sequence number (the sweep of the laser over the FEDs, starting from 0 ...)
las_id --> 447 blue laser, 592 green 
fill_num --> if collision run then it is the LHC fill number
run_num_infill -> if in a fill there are several runs then it is the run number 0,1,2,...
run_time --> UTC start of the run time 
run_time_stablebeam --> UTC stable beam run time for that fill (note that even for collision runs, it could be that in a run for a few sequences there are no collisions, so if you want to look only at collision runs where there are collisions, you have to make sure that the time of your data (see time vector below) are after  run_time_stablebeam).
lumi is the initial instantaneous lumi at the start of the fill 
bfield is the magnetic field 
nxt is the number of crystals in the sequence (75848 if the sequence is complete)
time[0,...,54] is the time when the data were taken on the specific FED, the index is #FED-601, for example time[0] is for FED=601.... 

now come the pedestals: 
fed[] is the fed number 
chan[] is the channel number 
ped[] is the pedestal 
pedrms[] is the pedestal rms 

    
    
    
    T->Draw("ped[1] : time[2]", "run==283270", "colz")
    
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-RunBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080653/0000/
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-increasedNoise-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080454/0000/
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-TimeBased-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080742/0000/
    
    /eos/cms/store/user/amassiro/ECAL/LocalReco/test04Aug2017-floatingPedestal-RAW/DoubleEG/crab_DoubleEG_Run2016H-OneRun/170804_080621/0000/
    
    

    
    
    
    RunBased.root
    increasedNoise.root
    TimeBased.root
    floatingPedestal.root

    
    
    r99t Draw.cxx\(\"/tmp/amassiro/RunBased.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/increasedNoise.root\",\"increasedNoise\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/RunBased.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/TimeBased.root\",\"TimeBased\"\)
    r99t Draw.cxx\(\"/tmp/amassiro/RunBased.root\",\"mee_advanced_multifit_raw\",100,70,120,\"m_{ll}\",\"1\",\"RunBased\",\"1\",\"/tmp/amassiro/floatingPedestal.root\",\"floating\"\)
    
    
    
    
    
    
    
    
    
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
    
    
    