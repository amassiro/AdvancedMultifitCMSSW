//---- plot output of multifit

void plotPulse (std::string nameInputFile = "output.root", int nXtal = 10){
  
  
  
  
  
  
  TFile *file = new TFile(nameInputFile.c_str());
  
  TTree* tree = (TTree*) file->Get("ZeeTreeProducer/pulses");
  
  float pulse[10];
  float position[10];
  float ampl_multifit[10];
  float amplitude_weight;
  float pedestal;
  float pedestalHomemade;
  
  UInt_t id;
  UInt_t cmsswindex;
  UInt_t isEB;
  
  float eta;
  float phi;
  
  UInt_t run;
  
//   std::vector<float>* pulse    = new std::vector<float>;
//   std::vector<float>* position = new std::vector<float>;
  
  tree->SetBranchAddress("pulse",         &pulse);
  tree->SetBranchAddress("position",      &position);
  tree->SetBranchAddress("ampl_multifit", &ampl_multifit);
  tree->SetBranchAddress("amplitude_weight",   &amplitude_weight);
  tree->SetBranchAddress("pedestal",   &pedestal);
  tree->SetBranchAddress("pedestalHomemade",   &pedestalHomemade);
  
  
  tree->SetBranchAddress("id",   &id);

  tree->SetBranchAddress("cmsswindex",   &cmsswindex);
  tree->SetBranchAddress("isEB",   &isEB);
  tree->SetBranchAddress("eta",      &eta);
  tree->SetBranchAddress("phi",      &phi);
  
  tree->SetBranchAddress("run",   &run);
  
  
  tree->GetEntry(nXtal);
  
  
  
  float f_ix, f_iy, f_iz, f_ieta, f_iphi;
  
  //----
  //---- load pulses from DB
  //----
  
  
  
  double pulse_shape[12];
  
  //----
  //---- load name conventions and ids
  
  const Int_t kGains = 3;
  const Int_t kEBChannels = 61200, kEEChannels = 14648;
  
  // *****************  barrel  *****************
  std::ifstream fEB;
  fEB.open("./EB.txt");
  if (!fEB.is_open()) {
    std::cout << "ERROR : cannot open file EB.txt" << std::endl;
    exit (1);
  }
  std::string pos, dummyLine, bid;
  int cmsswEBId[kEBChannels], dbID, hashedId, iphi[kEBChannels], ieta[kEBChannels], absieta, FED, SM, TT,  iTT, strip, Xtal, phiSM, etaSM;
  getline(fEB, dummyLine);   // skip first line
  for (int iChannel = 0; iChannel < kEBChannels; iChannel++) {
    fEB >> cmsswEBId[iChannel] >> dbID >> hashedId >> iphi[iChannel] >> ieta[iChannel] >> absieta >> pos >> FED >> SM >> TT >>  iTT >> strip >> Xtal >> phiSM >> etaSM;
    
    if (cmsswEBId[iChannel] == cmsswindex) {
      f_ieta =  ieta[iChannel];
      f_iphi =  iphi[iChannel];
      f_ix = -999;
      f_iy = -999;
      f_iz = -999;
    }
    
    if(hashedId != iChannel) {
      cout << "EB,txt strange hash " << hashedId << " while iChannel " << iChannel << endl;
      exit(-1);
    }
  }
  fEB.close();
  
  // ***************** now EE *****************
  std::ifstream fEE;
  fEE.open("./EE.txt");
  if (!fEE.is_open()) {
    std::cout << "ERROR : cannot open file EE.txt" << std::endl;
    exit (1);
  }
  // read also the ring value from Crystal file
  std::ifstream fCrystal;
  fCrystal.open("Crystal");
  if (!fCrystal.is_open()) {
    std::cout << "ERROR : cannot open file Crystal" << std::endl;
    exit (1);
  }
  int cmsswEEId[kEEChannels], iz[kEEChannels], ix[kEEChannels], iy[kEEChannels], SC, iSC, quadrant, ringEE[kEEChannels];
  getline(fEE, dummyLine);   // skip first line
  for (int iChannel = 0; iChannel < 14648; iChannel++) {
    fEE >> cmsswEEId[iChannel] >> dbID >> hashedId >> iz[iChannel] >> ix[iChannel] >> iy[iChannel] >> SC >> iSC >> FED >> pos >> TT >> strip >> Xtal >> quadrant;
    
    if (cmsswEEId[iChannel] == cmsswindex) {
      f_ix =  ix[iChannel];
      f_iy =  iy[iChannel];
      f_iz =  iz[iChannel];
      f_ieta = -999;
      f_iphi = -999;
    }
    
    if (hashedId != iChannel) {
      cout << "EE,txt strange hash " << hashedId << " while iChannel " << iChannel << endl;
      exit(-1);
    }
    fCrystal >> ringEE[iChannel];
    int ring = abs(ringEE[iChannel]) - 1;
    if(ring < 17 || ring > 27) {
      cout << " EE channel " << iChannel << " ring " << ringEE[iChannel] << "\n";
      exit(-1);
    }
  }
  fEE.close();
  
  
  //----
  //---- now load the pulses file, but save only the one corresponding to the correct cmsswindex
  
  std::cout << " cmsswindex = " << cmsswindex << std::endl;
  std::cout << "   isEB = " << isEB << std::endl;
  std::cout << "   eta  = " << eta  << std::endl;
  std::cout << "   phi  = " << phi  << std::endl;
  std::cout << "   ieta = " << f_ieta << std::endl;
  std::cout << "   iphi = " << f_iphi << std::endl;
  std::cout << "   ix   = " << f_ix   << std::endl;
  std::cout << "   iy   = " << f_iy   << std::endl;
  std::cout << "   iz   = " << f_iz   << std::endl;
  
  std::cout << " run = " << run << std::endl;
  
  
  std::cout << " Total #crystals = " << tree->GetEntries() << std::endl;
  
  
  
  
  
  
  std::ifstream filePulseShapes ("/afs/cern.ch/user/e/emanuele/w/public/ecal/pulseshapes_db/template_histograms_ECAL_Run2017_runs_297113_297114.txt"); 
  
  std::string buffer;
  int num;
  unsigned int unum;
  double value;
  
  if (!filePulseShapes.is_open()) {
    std::cerr << "** ERROR: Can't open " << "FILE PULSE SHAPES" << " for input" << std::endl;
    return false;
  }
  
  while (!filePulseShapes.eof()) {
    
    int iDet = 0;
    int detId = 0;
    
     getline(filePulseShapes,buffer);
    if (buffer != ""){ ///---> save from empty line at the end!
      std::stringstream line( buffer );      
      
//       
//       1 838926849       0.015429        0.772277        1.000000        0.881049        0.666307        0.469089        0.316837        0.207594        0.135415        0.089034        0.060015        0.042220        
//       
      
      line >> num; 
      iDet = num;
      
      line >> unum; 
      detId = unum;

      if (detId == cmsswindex) {
        for (int i=0; i<(10+2); i++) {
          line >> value; 
          
          //---- FIX: how on Earth can this be negative???
          if (value<0) value = 0;
          
          pulse_shape[i] = value;
        }
        
        std::cout << " found " << std::endl;
        
        break;
      }
    }
  }
  
  for(int iBX=0; iBX<12; iBX++){
    std::cout << " iBX => " << pulse_shape[iBX] << std::endl;
  }
  
  std::cout << std::endl;
     
  //----
  //---- (end) load pulses from DB
  //----
  
  
  
  std::cout << " ----- " << std::endl;
  std::cout << " pedestalHomemade = " << pedestalHomemade << std::endl;
  std::cout << " pedestal         = " << pedestal << std::endl;
  std::cout << " ----- " << std::endl;
  std::cout << std::endl;
  
  
  
  
  
  
  TCanvas* ccpulse = new TCanvas ("ccpulse","",800,600);
  TGraph *gr = new TGraph();
  
  TGraph *gr_pedestal = new TGraph();
  
  TGraph *gr_reco = new TGraph();
  TGraph *gr_reco_weight = new TGraph();
  
  
  TGraph *gr_reco_pulse = new TGraph();
  TGraph *gr_reco_weight_pulse = new TGraph();

  TGraph *gr_reco_pulse_components[10];
  for(int i=0; i<10; i++){
    gr_reco_pulse_components[i] = new TGraph();
  }
  
  for(int i=0; i<10; i++){
    std::cout << " ampl_multifit[" << i << "] = " << ampl_multifit[i] << std::endl;
  }
  
  for(int i=0; i<10; i++){
    
    std::cout << " [" << i << "] = " << i << std::endl;
    
    gr_pedestal -> SetPoint(i, position[i]*25., pedestal);
    gr      -> SetPoint(i, position[i]*25., pulse[i]);
    gr_reco -> SetPoint(i, position[i]*25., ampl_multifit[i] + pedestal);
    if (i==5) {
      gr_reco_weight -> SetPoint(0, position[i]*25., amplitude_weight + pedestalHomemade);
      std::cout << " >> amplitude_weight = " << amplitude_weight << std::endl;
    }
  
    
    float value_multifit = 0;
    float value_weight   = 0;
    
    for(int iBX=0; iBX<10; iBX++){
      //----    +2 because the the maximum is on the 3rd sample, so everything is shifted by construction
      if ((i - iBX +2) >= 0  &&  (i - iBX +2) < 12) {
//         if (iBX ==5) value_multifit += ampl_multifit[iBX] * pulse_shape[i - iBX +2];
        value_multifit += ampl_multifit[iBX] * pulse_shape[i - iBX +2];
//         std::cout << " filling : " << iBX << std::endl;
      }

      if ((i - iBX +2) >= 0  &&  (i - iBX +2) < 12) {
        if (iBX<=2) gr_reco_pulse_components[iBX]  -> SetPoint(i,          position[i]*25., ampl_multifit[iBX] * pulse_shape[i - iBX +2] + pedestal);
        else        gr_reco_pulse_components[iBX]  -> SetPoint(i - iBX +2, position[i]*25., ampl_multifit[iBX] * pulse_shape[i - iBX +2] + pedestal);
      }
      
    }
    
    if ((i-3) >= 0) {
      value_weight = amplitude_weight * pulse_shape[i-3];  
    }
//     value_weight = amplitude_weight * pulse_shape[i];  
    
    gr_reco_pulse        -> SetPoint(i, position[i]*25., value_multifit + pedestal);
    gr_reco_weight_pulse -> SetPoint(i, position[i]*25., value_weight   + pedestalHomemade);
    
  }
  
//   for(int i=0; i<position->size(); i++){
//     gr->SetPoint(i, position->at(i), pulse->at(i));
//   }
  
  TMultiGraph* mg = new TMultiGraph();
  ccpulse->SetRightMargin(0.3);
  
  TLegend* leg = new TLegend(0.71,0.10,0.99,0.90);
  
//   gr_pedestal->Draw("ALP"); 
  gr_pedestal->SetLineColor(kRed);
  gr_pedestal->SetLineWidth(2);
  gr_pedestal->SetLineStyle(4);
  gr_pedestal->SetMarkerSize(1);
  gr_pedestal->SetMarkerStyle(1);
  gr_pedestal->SetMarkerColor(kRed);
  gr_pedestal->GetXaxis()->SetTitle("time [ns]");
  mg->Add(gr_pedestal);
  leg->AddEntry(gr_pedestal,"pedestal","l");
  
//   gr->Draw("ALP"); 
  gr->SetLineColor(kRed);
  gr->SetLineWidth(2);
  gr->SetLineStyle(2);
  gr->SetMarkerSize(1.2);
  gr->SetMarkerStyle(24);
  gr->SetMarkerColor(kRed);
  gr->GetXaxis()->SetTitle("time [ns]");
  mg->Add(gr);
  leg->AddEntry(gr,"pulse","pl");
  
  
//   gr_reco->Draw("P"); 
  gr_reco->SetLineColor(kBlue);
  gr_reco->SetLineWidth(0);
  gr_reco->SetLineStyle(2);
  gr_reco->SetMarkerSize(2);
  gr_reco->SetMarkerStyle(23);
  gr_reco->SetMarkerColor(kBlue);
  gr_reco->GetXaxis()->SetTitle("time [ns]");
  mg->Add(gr_reco);
  leg->AddEntry(gr_reco,"reconstructed energy","p");
  

//   gr_reco_weight->Draw("P"); 
  gr_reco_weight->SetLineColor(kMagenta);
  gr_reco_weight->SetLineWidth(0);
  gr_reco_weight->SetLineStyle(2);
  gr_reco_weight->SetMarkerSize(2);
  gr_reco_weight->SetMarkerStyle(26);
  gr_reco_weight->SetMarkerColor(kMagenta);
  gr_reco_weight->GetXaxis()->SetTitle("time [ns]");
  mg->Add(gr_reco_weight);
  leg->AddEntry(gr_reco_weight,"reconstructed energy weight","p");
  
  
  
  gr_reco_pulse->SetLineColor(kBlue);
  gr_reco_pulse->SetLineWidth(2);
  gr_reco_pulse->SetLineStyle(1);
  gr_reco_pulse->SetMarkerSize(1);
  gr_reco_pulse->SetMarkerStyle(32);
  gr_reco_pulse->SetMarkerColor(kBlue);
  gr_reco_pulse->GetXaxis()->SetTitle("time [ns]");
  mg->Add(gr_reco_pulse);
  leg->AddEntry(gr_reco_pulse,"reconstructed pulse","p");
  
  
  gr_reco_weight_pulse->SetLineColor(kMagenta);
  gr_reco_weight_pulse->SetLineWidth(2);
  gr_reco_weight_pulse->SetLineStyle(1);
  gr_reco_weight_pulse->SetMarkerSize(1);
  gr_reco_weight_pulse->SetMarkerStyle(22);
  gr_reco_weight_pulse->SetMarkerColor(kMagenta);
  gr_reco_weight_pulse->GetXaxis()->SetTitle("time [ns]");
  mg->Add(gr_reco_weight_pulse);
  leg->AddEntry(gr_reco_weight_pulse,"reconstructed pulse weight","p");
  
  
  
  
  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("time [ns]");
  mg->GetYaxis()->SetTitle("ADC counts");
  
  leg->Draw();
  
  ccpulse->SetGrid();
  
  
  ccpulse->SaveAs(Form("ccpulse__%d_%d.png", nXtal, run));
  
  
  
  
  
  
  
  
  TCanvas* ccpulse_components = new TCanvas ("ccpulse_components","",800,600);
  ccpulse_components->SetRightMargin(0.3);
  
  TMultiGraph* mg_multifit = new TMultiGraph();
  TLegend* leg_components = new TLegend(0.71,0.10,0.99,0.90);
  
  for(int i=0; i<10; i++){
    gr_reco_pulse_components[i]->SetMarkerColor(i+1);
    gr_reco_pulse_components[i]->SetLineColor(i+1);
    mg_multifit->Add(gr_reco_pulse_components[i]);
    std::string name = " BX " + std::to_string(i);
    leg_components->AddEntry(gr_reco_pulse_components[i], name.c_str(), "PL");
  }
  mg_multifit->Add(gr_reco_pulse);
  
  mg_multifit->Draw("APL");
  mg_multifit->GetXaxis()->SetTitle("time [ns]");
  mg_multifit->GetYaxis()->SetTitle("ADC counts");
  
  leg_components->Draw();
  
  ccpulse_components->SetGrid();
  
  
  ccpulse_components->SaveAs(Form("ccpulse_components_%d_%d.png", nXtal, run));
  
  
  
  
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  
}


