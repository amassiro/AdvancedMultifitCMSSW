// -*- C++ -*-
//
// Package:    AdvancedMultifitCMSSW/ZeeTreeProducer
// Class:      ZeeTreeProducer
// 
/**\class ZeeTreeProducer ZeeTreeProducer.cc AdvancedMultifitCMSSW/ZeeTreeProducer/plugins/ZeeTreeProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrea Massironi
//         Created:  Thu, 17 Nov 2016 10:09:05 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"



// ECAL specific

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbService.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbRecord.h"
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/DataRecord/interface/EcalADCToGeVConstantRcd.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstants.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstantsMC.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsMCRcd.h"


#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"



#include "FWCore/Framework/interface/ESHandle.h"



#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"   //     ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"    ----> CLHEP/Geometry/Point3D.h issue
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
// #include "Geometry/EcalAlgo/interface/EcalBarrelGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/EcalAlgo/interface/EcalEndcapGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue




// #include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
// #include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "CondFormats/EcalObjects/interface/EcalMGPAGainRatio.h"
#include "CondFormats/EcalObjects/interface/EcalGainRatios.h"
#include "CondFormats/DataRecord/interface/EcalGainRatiosRcd.h"


#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


#include "TTree.h"




//---- for Zee part
#include "DataFormats/PatCandidates/interface/Electron.h"






//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class ZeeTreeProducer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ZeeTreeProducer(const edm::ParameterSet&);
      ~ZeeTreeProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      void FillDigi(EcalDataFrame digi, const EcalUncalibratedRecHitCollection *rechits, const EcalUncalibratedRecHitCollection *weights_rechits);
      
        
      // ----------member data ---------------------------
      
       
      edm::EDGetTokenT<EBDigiCollection> token_ebdigis_;
      edm::EDGetTokenT<EEDigiCollection> token_eedigis_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> token_ebrechits_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> token_w_ebrechits_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> token_eerechits_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> token_w_eerechits_;
      UInt_t n_pedestal_samples;
      
      TTree *outTree;
      UInt_t _run;
      UShort_t _lumi;
      UShort_t _bx;
      UInt_t _id;
      UInt_t _cmsswindex;
      int _isEB;
      
      float _gainratios[2];
      float _eta;
      float _phi;
      float _pulse[10];
      float _position[10];
      float _gain[10];
      
      float _handmade_pedestal;
      float _handmade_pedestal_rms;
      
      UShort_t _gainmask;
      float _multifit[10];
      float _jitter;
      float _chi2;
      float _amplitudeError;
      float _jitterError;
      UInt_t _recoflags;
      
      
      float _amplitude_simple_multifit;
      float _amplitude_advanced_multifit;
      float _amplitude_weight;
      
      
      float _best_pedestal;
      float _best_chi2;
      float _pedestal;
      
      edm::ESHandle<CaloGeometry> geometry;
      edm::ESHandle<EcalGainRatios> gRatio;
      
      
      
      
      
      
      edm::EDGetTokenT<std::vector<reco::GsfElectron> > token_EleTag_;
      
      TTree *outTreeElectrons;
      float _pt1_simple_multifit;
      float _pt1_advanced_multifit;
      float _pt1_weight;
      
      float _pt2_simple_multifit;
      float _pt2_advanced_multifit;
      float _pt2_weight;
      
      float _eta1_simple_multifit;
      float _eta1_advanced_multifit;
      float _eta1_weight;
      
      float _eta2_simple_multifit;
      float _eta2_advanced_multifit;
      float _eta2_weight;
      
      float _phi1_simple_multifit;
      float _phi1_advanced_multifit;
      float _phi1_weight;
      
      float _phi2_simple_multifit;
      float _phi2_advanced_multifit;
      float _phi2_weight;
      
      float _mee_simple_multifit;
      float _mee_advanced_multifit;
      float _mee_weight;
      
      UInt_t   _evt_run;
      UShort_t _evt_lumi;
      UShort_t _evt_bx;
      
      
      
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ZeeTreeProducer::ZeeTreeProducer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   
   
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   
   n_pedestal_samples = iConfig.getUntrackedParameter<unsigned int>("nPedestalSamples",3);
      
   token_ebdigis_ = consumes<EBDigiCollection>(iConfig.getParameter<edm::InputTag>("EBDigiCollection"));
   token_eedigis_ = consumes<EEDigiCollection>(iConfig.getParameter<edm::InputTag>("EEDigiCollection"));
   
   token_ebrechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"));
   token_w_ebrechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalUncalibRecHit","EcalUncalibRecHitsEB"));
   token_eerechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"));
   token_w_eerechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalUncalibRecHit","EcalUncalibRecHitsEE"));
   
   
   token_EleTag_      = consumes<std::vector<reco::GsfElectron> >( iConfig.getParameter<edm::InputTag>("EleTag") );
   
   
   
   outTree = fs->make<TTree>("pulses","pulses");
   
   outTree->Branch("run",         &_run,      "run/i");
   outTree->Branch("lumi",        &_lumi,     "lumi/s");
   outTree->Branch("bx",          &_bx,       "bx/s");
   outTree->Branch("id",          &_id,       "id/i");
   outTree->Branch("gainratios",  _gainratios,"gainratios[2]/F");
   outTree->Branch("eta",         &_eta,      "eta/F");
   outTree->Branch("phi",         &_phi,      "phi/F");
   outTree->Branch("pulse",       _pulse,     "pulse[10]/F");
   outTree->Branch("position",    _position,  "position[10]/F");
   outTree->Branch("cmsswindex",          &_cmsswindex,       "cmsswindex/i");
   outTree->Branch("isEB",          &_isEB,       "isEB/I");
   
   outTree->Branch("chi2",            &_chi2,           "chi2/F");
   outTree->Branch("jitter",          &_jitter,         "jitter/F");
   outTree->Branch("jitterError",     &_jitterError,    "jitterError/F");
   outTree->Branch("amplitudeError",  &_amplitudeError, "amplitudeError/F");
   outTree->Branch("recoflags",       &_recoflags,      "recoflags/I");
 

   outTree->Branch("gain",          _gain,                   "gain[10]/F");
   outTree->Branch("pedestalHomemade",      &_handmade_pedestal,     "pedestalHomemade/F");
   outTree->Branch("pedestalHomemade_rms",  &_handmade_pedestal_rms, "pedestalHomemade_rms/F");
   outTree->Branch("gainmask",      &_gainmask,              "gainmask/s");
   outTree->Branch("ampl_multifit", _multifit,               "ampl_multifit[10]/F");
   
   
   outTree->Branch("amplitude_simple_multifit",  &_amplitude_simple_multifit,   "amplitude_simple_multifit/F");
   outTree->Branch("amplitude_advanced_multifit",&_amplitude_advanced_multifit, "amplitude_advanced_multifit/F");
   outTree->Branch("amplitude_weight",           &_amplitude_weight,            "amplitude_weight/F");
   
   outTree->Branch("best_chi2",               &_best_chi2,                "best_chi2/F");
   outTree->Branch("best_pedestal",           &_best_pedestal,            "best_pedestal/F");
   outTree->Branch("pedestal",                &_pedestal,                 "pedestal/F");
   
   
   
   outTreeElectrons = fs->make<TTree>("electrons","electrons");

   outTreeElectrons->Branch("run",         &_evt_run,      "run/i");
   outTreeElectrons->Branch("lumi",        &_evt_lumi,     "lumi/s");
   outTreeElectrons->Branch("bx",          &_evt_bx,       "bx/s");
   
   outTreeElectrons->Branch("pt1_simple_multifit",        &_pt1_simple_multifit,     "pt1_simple_multifit/F");
   outTreeElectrons->Branch("pt1_advanced_multifit",      &_pt1_advanced_multifit,   "pt1_advanced_multifit/F");
   outTreeElectrons->Branch("pt1_weight",                 &_pt1_weight,              "pt1_weight/F");
   
   outTreeElectrons->Branch("pt2_simple_multifit",        &_pt2_simple_multifit,     "pt2_simple_multifit/F");
   outTreeElectrons->Branch("pt2_advanced_multifit",      &_pt2_advanced_multifit,   "pt2_advanced_multifit/F");
   outTreeElectrons->Branch("pt2_weight",                 &_pt2_weight,              "pt2_weight/F");
   
   outTreeElectrons->Branch("eta1_simple_multifit",        &_eta1_simple_multifit,     "eta1_simple_multifit/F");
   outTreeElectrons->Branch("eta1_advanced_multifit",      &_eta1_advanced_multifit,   "eta1_advanced_multifit/F");
   outTreeElectrons->Branch("eta1_weight",                 &_eta1_weight,              "eta1_weight/F");
   
   outTreeElectrons->Branch("eta2_simple_multifit",        &_eta2_simple_multifit,     "eta2_simple_multifit/F");
   outTreeElectrons->Branch("eta2_advanced_multifit",      &_eta2_advanced_multifit,   "eta2_advanced_multifit/F");
   outTreeElectrons->Branch("eta2_weight",                 &_eta2_weight,              "eta2_weight/F");
   
   outTreeElectrons->Branch("phi1_simple_multifit",        &_phi1_simple_multifit,     "phi1_simple_multifit/F");
   outTreeElectrons->Branch("phi1_advanced_multifit",      &_phi1_advanced_multifit,   "phi1_advanced_multifit/F");
   outTreeElectrons->Branch("phi1_weight",                 &_phi1_weight,              "phi1_weight/F");
   
   outTreeElectrons->Branch("phi2_simple_multifit",        &_phi2_simple_multifit,     "phi2_simple_multifit/F");
   outTreeElectrons->Branch("phi2_advanced_multifit",      &_phi2_advanced_multifit,   "phi2_advanced_multifit/F");
   outTreeElectrons->Branch("phi2_weight",                 &_phi2_weight,              "phi2_weight/F");

   outTreeElectrons->Branch("mee_simple_multifit",        &_mee_simple_multifit,     "mee_simple_multifit/F");
   outTreeElectrons->Branch("mee_advanced_multifit",      &_mee_advanced_multifit,   "mee_advanced_multifit/F");
   outTreeElectrons->Branch("mee_weight",                 &_mee_weight,              "mee_weight/F");
   

}


ZeeTreeProducer::~ZeeTreeProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ZeeTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  
  iSetup.get<CaloGeometryRecord>().get(geometry);
  iSetup.get<EcalGainRatiosRcd>().get(gRatio);
  
  _run = iEvent.eventAuxiliary().run();
  _lumi = iEvent.eventAuxiliary().luminosityBlock();
  _bx = iEvent.eventAuxiliary().bunchCrossing();
  
  _evt_run  = _run;
  _evt_lumi = _lumi;
  _evt_bx   = _bx;
  
  
  edm::Handle<EBDigiCollection> ebdigihandle;
  edm::Handle<EEDigiCollection> eedigihandle;
  edm::Handle<EcalUncalibratedRecHitCollection> ebrechithandle;
  edm::Handle<EcalUncalibratedRecHitCollection> w_ebrechithandle;
  const EcalUncalibratedRecHitCollection *ebrechits = NULL;
  const EcalUncalibratedRecHitCollection *w_ebrechits = NULL;
  edm::Handle<EcalUncalibratedRecHitCollection> eerechithandle;
  edm::Handle<EcalUncalibratedRecHitCollection> w_eerechithandle;
  const EcalUncalibratedRecHitCollection *eerechits = NULL;
  const EcalUncalibratedRecHitCollection *w_eerechits = NULL;
  
  iEvent.getByToken(token_ebrechits_,ebrechithandle);
  ebrechits = ebrechithandle.product();
  iEvent.getByToken(token_w_ebrechits_,w_ebrechithandle);
  w_ebrechits = w_ebrechithandle.product();
  iEvent.getByToken(token_eerechits_,eerechithandle);
  eerechits = eerechithandle.product();
  iEvent.getByToken(token_w_eerechits_,w_eerechithandle);
  w_eerechits = w_eerechithandle.product();
  
  iEvent.getByToken(token_ebdigis_,ebdigihandle);
  auto ebdigis = ebdigihandle.product();
  for (uint i=0; i<ebdigis->size(); i++) FillDigi((*ebdigis)[i],ebrechits,w_ebrechits);
  iEvent.getByToken(token_eedigis_,eedigihandle);
  auto eedigis = eedigihandle.product();
  for (uint i=0; i<eedigis->size(); i++) FillDigi((*eedigis)[i],eerechits,w_eerechits);
  
  
  
  
  //---- get electrons and save them
  edm::Handle<std::vector <reco::GsfElectron> > electronHandle;
  iEvent.getByToken(token_EleTag_,electronHandle);
  std::vector<reco::GsfElectron> electrons = *electronHandle;

  // First loop over electrons -> pre-loop mll
  //---- the first two are used to build mll
  reco::Candidate::LorentzVector L1;
  reco::Candidate::LorentzVector L2;
  bool found1 = false;
  bool found2 = false;
  _mee_advanced_multifit = -999;
  for ( unsigned int i=0; i<electrons.size(); ++i ){
    reco::GsfElectron  electron = electrons.at(i);
    if (
      electron.p4().pt() > 10
      && fabs(electron.deltaEtaSuperClusterTrackAtVtx()) < 2.5e-3
      && fabs(electron.deltaPhiSuperClusterTrackAtVtx()) < 10e-3
      && electron.dr03EcalRecHitSumEt() < 30
    ) {
      if (found1 == false) {
        L1 = electron.p4();
        _pt1_advanced_multifit = L1.pt();
        _eta1_advanced_multifit = L1.eta();
        _phi1_advanced_multifit = L1.phi();
        found1 = true;
      }
      else if (found2 == false) {
        L2 = electron.p4();
        found2 = true;
        _pt2_advanced_multifit = L2.pt();
        _eta2_advanced_multifit = L2.eta();
        _phi2_advanced_multifit = L2.phi();
        _mee_advanced_multifit = (L1+L2).mass();
      }
    }
  }
  
  
  
  outTreeElectrons->Fill();
  
  
  

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   edm::Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   edm::ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}




void ZeeTreeProducer::FillDigi(EcalDataFrame digi, const EcalUncalibratedRecHitCollection *rechits, const EcalUncalibratedRecHitCollection *weights_rechits){
  
  _id = UInt_t(digi.id());
  _gainmask = 0;
  
  for (int j=0; j<10; j++){ 
    _pulse[j] = float(digi[j]&0xFFF);
    _gain[j] = float((digi[j]>>12)&0x3);
    _gainmask |= 1<<(int(_gain[j]));
    _position[j] = j;
  }
  
  //---- get cmsswIndex
  if( digi.id().subdetId() == EcalBarrel) {
    EBDetId id(digi.id());
    _cmsswindex = id.rawId();
    _isEB = 1;
  } else {
    EEDetId id(digi.id());
    _cmsswindex = id.rawId();
    _isEB = 0;
    }
    
  _handmade_pedestal = 0;
  for (uint j=0; j<n_pedestal_samples; j++) _handmade_pedestal += _pulse[j];
  _handmade_pedestal/=n_pedestal_samples;
  
  _handmade_pedestal_rms = 0;
  
  auto _gr = gRatio.product();
  _gainratios[0]=(*_gr)[_id].gain12Over6();
  _gainratios[1]=_gainratios[0]*(*_gr)[_id].gain6Over1();
  
  
  auto detid = DetId(_id);
  
  for (int j=0; j<10; j++) _multifit[j] = 0;
  _amplitude_weight = 0;
  auto subGeom =  geometry->getSubdetectorGeometry(detid);
  auto cellGeom = subGeom->getGeometry(detid);
  _eta = cellGeom->getPosition().eta();
  _phi = cellGeom->getPosition().phi();
  auto it = rechits->find(detid);
  if (it==rechits->end()) std::cout << "Warning: rechit (multifit) not found" << std::endl;
  else {
   
    for (int j=0; j<10; j++) _multifit[j] = (j==5) ? it->amplitude() : it->outOfTimeAmplitude(j);
    
    _chi2 = it->chi2();
    _jitter = it->jitter();
    _jitterError = it->jitterError();
    _amplitudeError = it->amplitudeError();
    _recoflags = it->flags();
  
    
  }
  
  //    auto    it2 = weights_rechits->find(detid);
  edm::SortedCollection< EcalUncalibratedRecHit >::const_iterator    it2 = weights_rechits->find(detid);
  if (it2==weights_rechits->end()) std::cout << "Warning: rechit (weights) not found" << std::endl;
  else _amplitude_weight = it2->amplitude();
  
  
  //---- FixStandard ----     _amplitude_simple_multifit =  it->amplitude_simple();      
  _amplitude_advanced_multifit = it->amplitude();
  
  
  //---- FixStandard ----     _best_chi2     = it->best_chi2();
  //---- FixStandard ----     _best_pedestal = it->best_pedestal();
  _pedestal = it2->pedestal();
  
  
  //       std::cout << " ZeeTreeProducer:: _amplitude_simple_multifit = " << _amplitude_simple_multifit << "   _amplitude_advanced_multifit = " << _amplitude_advanced_multifit   << " detid = " << _id << std::endl;
  
  
    
    outTree->Fill();

  
}



// ------------ method called once each job just before starting event loop  ------------
void 
ZeeTreeProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ZeeTreeProducer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ZeeTreeProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZeeTreeProducer);
