//---- plot output of multifit

void plotPulse (std::string nameInputFile = "output.root", int nXtal = 10){
  
  TFile *file = new TFile(nameInputFile.c_str());
  
  TTree* tree = (TTree*) file->Get("ZeeTreeProducer/pulses");
  
  float pulse[10];
  float position[10];
  float ampl_multifit[10];
  float amplitude_weight;
  
  
//   std::vector<float>* pulse    = new std::vector<float>;
//   std::vector<float>* position = new std::vector<float>;
  
  tree->SetBranchAddress("pulse",         &pulse);
  tree->SetBranchAddress("position",      &position);
  tree->SetBranchAddress("ampl_multifit", &ampl_multifit);
  tree->SetBranchAddress("amplitude_weight",   &amplitude_weight);
  
  
  tree->GetEntry(nXtal);
  
  
  TCanvas* ccpulse = new TCanvas ("ccpulse","",800,600);
  TGraph *gr = new TGraph();
  TGraph *gr_reco = new TGraph();
  TGraph *gr_reco_weight = new TGraph();
  for(int i=0; i<10; i++){
    gr      -> SetPoint(i, position[i]*25., pulse[i]);
    gr_reco -> SetPoint(i, position[i]*25., ampl_multifit[i]);
    if (i==5) {
      gr_reco_weight -> SetPoint(i, position[i]*25., amplitude_weight);
      std::cout << " amplitude_weight = " << amplitude_weight << std::endl;
    }
    std::cout << " ampl_multifit[" << i << "] = " << ampl_multifit[i] << std::endl;
  }
  
//   for(int i=0; i<position->size(); i++){
//     gr->SetPoint(i, position->at(i), pulse->at(i));
//   }
  
  gr->Draw("ALP"); 
  gr->SetLineColor(kRed);
  gr->SetLineWidth(2);
  gr->SetLineStyle(2);
  gr->SetMarkerSize(2);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kRed);
  gr->GetXaxis()->SetTitle("time [ns]");
  
  
  gr_reco->Draw("P"); 
  gr_reco->SetLineColor(kBlue);
  gr_reco->SetLineWidth(2);
  gr_reco->SetLineStyle(2);
  gr_reco->SetMarkerSize(2);
  gr_reco->SetMarkerStyle(22);
  gr_reco->SetMarkerColor(kBlue);
  gr_reco->GetXaxis()->SetTitle("time [ns]");
  

  gr_reco_weight->Draw("P"); 
  gr_reco_weight->SetLineColor(kMagenta);
  gr_reco_weight->SetLineWidth(2);
  gr_reco_weight->SetLineStyle(2);
  gr_reco_weight->SetMarkerSize(2);
  gr_reco_weight->SetMarkerStyle(26);
  gr_reco_weight->SetMarkerColor(kMagenta);
  gr_reco_weight->GetXaxis()->SetTitle("time [ns]");
  
  
  ccpulse->SetGrid();
  
  
}


