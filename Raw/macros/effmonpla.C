#include<iostream>
#include<fstream>
#include<stdlib.h>
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TF1.h"
#include "TString.h"
#include "TSpectrum.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TTree.h"
#include "TLine.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLatex.h"

void effmonpla(Int_t num){
	//gStyle -> SetOptStat(0);
	gStyle -> SetOptFit(0);
  ofstream out("effmon.dat",std::ios::app);

  TCanvas *c1 = new TCanvas("c1","c1",900,600);
  TCanvas *c2 = new TCanvas("c2","c2",900,600);

	TChain *tree = new TChain("tree");
	tree->AddFile(Form("rootmon/run%04d.root",num));

  TH1D *d1 = new TH1D("d1","mon",2000,0,4000);
  TH1D *d2 = new TH1D("d2","mon",2000,0,4000);
  TH1D *d3 = new TH1D("d3","mon",2000,0,4000);
  TH1D *d4 = new TH1D("d4","mon",2000,0,4000);
  TH1D *d5 = new TH1D("d5","mon",2000,0,4000);
  TH1D *d6 = new TH1D("d6","mon",2000,0,4000);
  TH1D *d7 = new TH1D("d7","mon",2000,0,4000);
  TH1D *d8 = new TH1D("d8","mon",2000,0,4000);
  TH1D *d9 = new TH1D("d9","mon",2000,0,4000);
  TH1D *d10 = new TH1D("d10","mon",2000,0,4000);
  TH1D *d11 = new TH1D("d11","mon",2000,0,4000);
  TH1D *d12 = new TH1D("d12","mon",2000,0,4000);
  TH1D *d13 = new TH1D("d13","mon",2000,0,4000);
  TH1D *d14 = new TH1D("d14","mon",2000,0,4000);
  TH1D *d15 = new TH1D("d15","mon",2000,0,4000);
  TH1D *d16 = new TH1D("d16","mon",2000,0,4000);
 

  //status test////////////////////////////////////////////////////////
  tree->Draw("F3PLA_QL>>d1","F11PLA_QL>0&&F11PLA_QL<4000");
  tree->Draw("F3PLA_QL>>d2","");
  Double_t dd1 = d1 -> GetIntegral();
  Double_t dd2 = d2 -> GetIntegral();
  Double_t eff3l = dd1/dd2;

  tree->Draw("F3PLA_QR>>d3","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F3PLA_QR>>d4","");
  Double_t dd3 = d3 -> GetIntegral();
  Double_t dd4 = d4 -> GetIntegral();
  Double_t eff3r = dd3/dd4;
 
  tree->Draw("F7PLA_QL>>d5","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F7PLA_QL>>d6","");
  Double_t dd5 = d5 -> GetIntegral();
  Double_t dd6 = d6 -> GetIntegral();
  Double_t eff7l = dd5/dd6;

  tree->Draw("F7PLA_QR>>d7","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F7PLA_QR>>d8","");
  Double_t dd7 = d7 -> GetIntegral();
  Double_t dd8 = d8 -> GetIntegral();
  Double_t eff7r = dd7/dd8;

  tree->Draw("F8PLA_QL>>d9","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F8PLA_QL>>d10","");
  Double_t dd5 = d9 -> GetIntegral();
  Double_t dd6 = d10 -> GetIntegral();
  Double_t eff8l = dd9/dd10;

  tree->Draw("F8PLA_QR>>d11","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F8PLA_QR>>d12","");
  Double_t dd11 = d11 -> GetIntegral();
  Double_t dd12 = d12 -> GetIntegral();
  Double_t eff8r = dd11/dd12;

  tree->Draw("F11PLA_QL>>d13","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F11PLA_QL>>d14","");
  Double_t dd13 = d13 -> GetIntegral();
  Double_t dd14 = d14 -> GetIntegral();
  Double_t eff11r = dd9/dd10;

  tree->Draw("F11PLA_QR>>d15","F11PLA_QL>&&F11PLA_QL<4000");
  tree->Draw("F11PLA_QR>>d16","");
  Double_t dd15 = d15 -> GetIntegral();
  Double_t dd16 = d16 -> GetIntegral();
  Double_t eff11l = dd15/dd16;

  c2 -> cd();
  TLatex *m1 = new TLatex(0.12,0.8,Form("RUN#%04d PLASTIC Efficiency",num));
  m1 -> SetNDC();
  m1 -> Draw();
  TLatex *m2 = new TLatex(0.12,0.7,"Efficiency = N(F3PLA)/N(F3PPAC1A_X)");
  m2 -> SetNDC();
  m2 -> Draw();
  TLatex *m3 = new TLatex(0.12,0.6,Form("F3PLA LEFT Efficiency = %1.5f",eff3l));
  m3 -> SetNDC();
  m3 -> Draw();
  TLatex *m4 = new TLatex(0.12,0.5,Form("F3PLA RIGHT Efficiency = %1.5f",eff3r));
  m4 -> SetNDC();
  m4 -> Draw();
  TLatex *m5 = new TLatex(0.12,0.4,Form("F7PLA LEFT Efficiency = %1.5f",eff7l));
  m5 -> SetNDC();
  m5 -> Draw();
  TLatex *m6 = new TLatex(0.12,0.3,Form("F7PLA RIGHT Efficiency = %1.5f",eff7r));
  m6 -> SetNDC();
  m6 -> Draw();
  TLatex *m7 = new TLatex(0.12,0.2,Form("F8PLA LEFT Efficiency = %1.5f",eff8l));
  m7 -> SetNDC();
  m7 -> Draw();
  TLatex *m8 = new TLatex(0.12,0.1,Form("F8PLA RIGHT Efficiency = %1.5f",eff8r));
  m8 -> SetNDC();
  m8 -> Draw();
  TLatex *m9 = new TLatex(0.62,0.8,Form("F11PLA LEFT Efficiency = %1.5f",eff11l));
  m9 -> SetNDC();
  m9 -> Draw();
  TLatex *m10 = new TLatex(0.62,0.7,Form("F11PLA RIGHT Efficiency = %1.5f",eff11r));
  m10 -> SetNDC();
  m10 -> Draw();

  c1 -> SaveAs("effmon.eps");

  out << num << " " << eff3l << " " << eff3r << " " << eff7l << " " << eff7r 
<< " " << eff8l << " " << eff8r << " " << eff11l << " " << eff11r << endl;
  out.close();
}



