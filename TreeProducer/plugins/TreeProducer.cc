// -*- C++ -*-
//
// Package:    AdvancedMultifitCMSSW/TreeProducer
// Class:      TreeProducer
// 
/**\class TreeProducer TreeProducer.cc AdvancedMultifitCMSSW/TreeProducer/plugins/TreeProducer.cc

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





//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TreeProducer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TreeProducer(const edm::ParameterSet&);
      ~TreeProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      void FillDigi(EcalDataFrame digi, const EcalUncalibratedRecHitCollection *rechits, const EcalUncalibratedRecHitCollection *weights_rechits);
      
        
      // ----------member data ---------------------------
      
       
      edm::EDGetTokenT<EBDigiCollection> tok_ebdigis_;
      edm::EDGetTokenT<EEDigiCollection> tok_eedigis_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> tok_ebrechits_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> tok_w_ebrechits_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> tok_eerechits_;
      edm::EDGetTokenT<EcalUncalibratedRecHitCollection> tok_w_eerechits_;
      UInt_t n_pedestal_samples;
      
      TTree *outTree;
      UInt_t _run;
      UShort_t _lumi;
      UShort_t _bx;
      UInt_t _id;
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
TreeProducer::TreeProducer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   
   
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   
   n_pedestal_samples = iConfig.getUntrackedParameter<unsigned int>("nPedestalSamples",3);
      
   tok_ebdigis_ = consumes<EBDigiCollection>(iConfig.getParameter<edm::InputTag>("EBDigiCollection"));
   tok_eedigis_ = consumes<EEDigiCollection>(iConfig.getParameter<edm::InputTag>("EEDigiCollection"));
   
   tok_ebrechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"));
   tok_w_ebrechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalUncalibRecHit","EcalUncalibRecHitsEB"));
   tok_eerechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"));
   tok_w_eerechits_ = consumes<EcalUncalibratedRecHitCollection>(edm::InputTag("ecalUncalibRecHit","EcalUncalibRecHitsEE"));
   
   
   
   
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
   
   

}


TreeProducer::~TreeProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  
  iSetup.get<CaloGeometryRecord>().get(geometry);
  iSetup.get<EcalGainRatiosRcd>().get(gRatio);
  
  _run = iEvent.eventAuxiliary().run();
  _lumi = iEvent.eventAuxiliary().luminosityBlock();
  _bx = iEvent.eventAuxiliary().bunchCrossing();
  
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
  
  iEvent.getByToken(tok_ebrechits_,ebrechithandle);
  ebrechits = ebrechithandle.product();
  iEvent.getByToken(tok_w_ebrechits_,w_ebrechithandle);
  w_ebrechits = w_ebrechithandle.product();
  iEvent.getByToken(tok_eerechits_,eerechithandle);
  eerechits = eerechithandle.product();
  iEvent.getByToken(tok_w_eerechits_,w_eerechithandle);
  w_eerechits = w_eerechithandle.product();
  
  iEvent.getByToken(tok_ebdigis_,ebdigihandle);
  auto ebdigis = ebdigihandle.product();
  for (uint i=0; i<ebdigis->size(); i++) FillDigi((*ebdigis)[i],ebrechits,w_ebrechits);
  iEvent.getByToken(tok_eedigis_,eedigihandle);
  auto eedigis = eedigihandle.product();
  for (uint i=0; i<eedigis->size(); i++) FillDigi((*eedigis)[i],eerechits,w_eerechits);
  
  
  
  
  

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   edm::Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   edm::ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}




void TreeProducer::FillDigi(EcalDataFrame digi, const EcalUncalibratedRecHitCollection *rechits, const EcalUncalibratedRecHitCollection *weights_rechits){
  
  _id = UInt_t(digi.id());
  _gainmask = 0;
  
  for (int j=0; j<10; j++){ 
    _pulse[j] = float(digi[j]&0xFFF);
    _gain[j] = float((digi[j]>>12)&0x3);
    _gainmask |= 1<<(int(_gain[j]));
    _position[j] = j;
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
  
  
  //       std::cout << " TreeProducer:: _amplitude_simple_multifit = " << _amplitude_simple_multifit << "   _amplitude_advanced_multifit = " << _amplitude_advanced_multifit   << " detid = " << _id << std::endl;
  
  
    
    outTree->Fill();

  
}



// ------------ method called once each job just before starting event loop  ------------
void 
TreeProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeProducer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProducer);
