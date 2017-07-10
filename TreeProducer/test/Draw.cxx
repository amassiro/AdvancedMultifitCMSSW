TH1F * DrawOverflow(TH1F *h) {
  // This function paint the histogram h with an extra bin for overflows
  UInt_t nx = h->GetNbinsX()+1;
  Double_t *xbins= new Double_t[nx+1];
  for (UInt_t i=0;i<nx;i++)
    xbins[i]=h->GetBinLowEdge(i+1);
  xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
  char *tempName= new char[strlen(h->GetName())+10];
  sprintf(tempName,"%swtOverFlow",h->GetName());
  // Book a temporary histogram having ab extra bin for overflows
  TH1F *htmp = new TH1F(tempName, h->GetTitle(), nx, xbins);
  //---- style
  htmp->SetLineColor(h->GetLineColor());
  htmp->SetLineWidth(h->GetLineWidth());
  htmp->SetLineStyle(h->GetLineStyle());
  // Reset the axis labels
  htmp->SetXTitle(h->GetXaxis()->GetTitle());
  htmp->SetYTitle(h->GetYaxis()->GetTitle());
  // Fill the new hitogram including the extra bin for overflows
  for (UInt_t i=1; i<=nx; i++)
    htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
  // Fill the underflows
  htmp->Fill(h->GetBinLowEdge(1)-1, h->GetBinContent(0));
  // Restore the number of entries
  htmp->SetEntries(h->GetEntries());
  // FillStyle and color
  htmp->SetFillStyle(h->GetFillStyle());
  htmp->SetFillColor(h->GetFillColor());
  return htmp;
}

#include "TDRStyle.cc"

void Draw(std::string nameInFileRoot, std::string var = "etaSC", int NBIN = 1000, float MIN = 0, float MAX = 1000, std::string varHR = "", std::string globalCut = "1",  std::string sampleHR = "Data", std::string moreweight = "1") {
  
  globalCut = "(" + globalCut + ")*(" + moreweight + ")";
  std::cout << " globalCut = " << globalCut << std::endl;
  
  
  TDRStyle();
  gStyle->SetTitleYOffset(1.1);
  gStyle->cd();
  
  if (varHR == "") {
    varHR = var;
  }
  gStyle->SetOptStat(0);
  int nSig = 5;
  TFile* f_Sig[100];
  TTree* t_Sig[100];
  TH1F* h_Sig[100];
  std::vector<std::string> vNameSig;
  std::vector<std::string> vNameSigHR;
  std::vector<double> vXsecSig;
  
  vNameSig.push_back(nameInFileRoot); vNameSigHR.push_back(sampleHR);
  vXsecSig.push_back(1.); //---- pb
  
  nSig = vXsecSig.size();
  TString name;
  for (int iSig = 0; iSig < nSig; iSig++) {
    f_Sig[iSig] = new TFile (vNameSig.at(iSig).c_str());
  }
  
  for (int iSig = 0; iSig < nSig; iSig++) {
    t_Sig[iSig] = (TTree*) f_Sig[iSig] -> Get ("ZeeTreeProducer/electrons");
  }
  
  for (int iSig = 0; iSig < nSig; iSig++) {
    name = Form ("hSig_%d",iSig);
    h_Sig[iSig] = new TH1F(name.Data(),vNameSigHR.at(iSig).c_str(),NBIN,MIN,MAX);
  }
  
  TString weight = Form ("1");
  TString toDraw;
  for (int iSig = 0; iSig < nSig; iSig++) {
    toDraw = Form ("%s >> hSig_%d",var.c_str(),iSig);
    weight = Form ("(%s) * %f",globalCut.c_str(),vXsecSig.at(iSig));
    t_Sig[iSig]->Draw(toDraw.Data(),weight.Data(),"goff");
  }
  
  //---- estetica
  for (int iSig = 0; iSig < nSig; iSig++) {
    h_Sig[iSig]->SetMarkerColor (kRed+iSig);
    h_Sig[iSig]->SetLineColor (kRed+iSig);
    h_Sig[iSig]->SetLineWidth(3);
    h_Sig[iSig]->SetLineStyle(1+iSig);
    h_Sig[iSig]->SetMarkerSize (0);
    h_Sig[iSig]->GetXaxis()->SetTitle(varHR.c_str());
  }
  
  TLegend* leg = new TLegend(0.75,0.70,0.90,0.90);
  for (int iSig = 0; iSig < nSig; iSig++) {
    leg->AddEntry(h_Sig[iSig],vNameSigHR.at(iSig).c_str(),"l");
  }
  leg->SetFillStyle(0);
  //---- overflow bin
  //  for (int iSig = 0; iSig < nSig; iSig++) {
  //   h_Sig[iSig] = DrawOverflow(h_Sig[iSig]);
  //  }
  
  
  //---- normalized
  TCanvas* cn = new TCanvas ("cn","cn",800,600);
  for (int iSig = 0; iSig < nSig; iSig++) {
    if (iSig ==0) h_Sig[iSig]->DrawNormalized();
    else h_Sig[iSig]->DrawNormalized("same");
  }
  leg->Draw();
  cn->SetGrid();
  //---- lumi scaled
  TCanvas* cnlumi = new TCanvas ("cnlumi","cnlumi",800,600);
  for (int iSig = 0; iSig < nSig; iSig++) {
    if (iSig ==0) h_Sig[iSig]->Draw();
    else h_Sig[iSig]->Draw("same");
  }
  leg->Draw();
  cnlumi->SetGrid();
  
}

