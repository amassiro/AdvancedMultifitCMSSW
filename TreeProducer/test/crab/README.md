
Multicrab


    cmsenv
    source /cvmfs/cms.cern.ch/crab3/crab.sh
    


    voms-proxy-init --voms cms
    myproxy-init -v

    python multicrab.py   samples_file.py
    
    
    
    python multicrab.py crab_projects_7Jan2017_localReco     status
    python multicrab.py crab_projects_7Jan2017_localReco     status    --verboseErrors
    
    
    python multicrab.py crab_projects_7Jul2017_oneRun     status
    python multicrab.py crab_projects_7Jul2017_oneRun     status    --verboseErrors
    
    python multicrab.py crab_projects_7Jul2017_oneRun_floatingPedestal     status
    python multicrab.py crab_projects_7Jul2017_oneRun_floatingPedestal     status    --verboseErrors

    python multicrab.py crab_projects_7Jul2017_oneRun_singlePed     status
    python multicrab.py crab_projects_7Jul2017_oneRun_singlePed     status    --verboseErrors

    python multicrab.py crab_projects_7Jul2017_oneRun_increasedNoise     status
    python multicrab.py crab_projects_7Jul2017_oneRun_increasedNoise     status    --verboseErrors

    python multicrab.py crab_projects_28Jul2017_oneRun_increasedNoise     status
    python multicrab.py crab_projects_28Jul2017_oneRun_increasedNoise     status    --verboseErrors

    
    