
Multicrab


    cmsenv
    source /cvmfs/cms.cern.ch/crab3/crab.sh
    


    voms-proxy-init --voms cms
    myproxy-init -v

    python multicrab.py   samples_file.py
    
    python multicrab.py crab_projects_7Jan2017_localReco     status
