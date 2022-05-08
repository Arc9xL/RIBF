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

void effmonplotpla(){
	//gStyle -> SetOptStat(0);
	gStyle -> SetOptFit(0);

  TCanvas *c1 = new TCanvas("c1","c1",900,600);
  c1 -> Divide(3,3);	

  
  TGraph* eff1 = new TGraph("effmon.dat","%lf %lf %*lf %*lf %*lf %*lf %*lf %*lf %*lf","");
  TGraph* eff2 = new TGraph("effmon.dat","%lf %*lf %lf %*lf %*lf %*lf %*lf %*lf %*lf","");
  TGraph* eff3 = new TGraph("effmon.dat","%lf %*lf %*lf %lf %*lf %*lf %*lf %*lf %*lf","");
  TGraph* eff4 = new TGraph("effmon.dat","%lf %*lf %*lf %*lf %lf %*lf %*lf %*lf %*lf","");
  TGraph* eff5 = new TGraph("effmon.dat","%lf %*lf %*lf %*lf %*lf %lf %*lf %*lf %*lf","");
  TGraph* eff6 = new TGraph("effmon.dat","%lf %*lf %*lf %*lf %*lf %*lf %lf %*lf %*lf","");
  TGraph* eff7 = new TGraph("effmon.dat","%lf %*lf %*lf %*lf %*lf %*lf %*lf %lf %*lf","");
  TGraph* eff8 = new TGraph("effmon.dat","%lf %*lf %*lf %*lf %*lf %*lf %*lf %*lf %lf","");
  
 
  c1 -> cd(1);
  eff1 -> SetMarkerStyle(20);
  eff1 -> SetMarkerColor(kRed);
  eff1 -> SetTitle("F3PLA LEFT Efficiency");
  eff1 -> Draw("APL+");
  eff1 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff1 -> GetYaxis() -> SetTitle("Efficiency");
 
  c1 -> cd(2);
  eff2 -> Draw("APL+");
  eff2 -> SetMarkerStyle(20);
  eff2 -> SetMarkerColor(kRed);
  eff2 -> SetTitle("F3PLA RIGHT Efficiency");
  eff2 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff2 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> cd(3);
  eff3 -> Draw("APL+");
  eff3 -> SetMarkerStyle(20);
  eff3 -> SetMarkerColor(kRed);
  eff3 -> SetTitle("F7PLA LEFT Efficiency");
  eff3 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff3 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> cd(4);
  eff4 -> Draw("APL+");
  eff4 -> SetMarkerStyle(20);
  eff4 -> SetMarkerColor(kRed);
  eff4 -> SetTitle("F7PLA RIGHT Efficiency");
  eff4 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff4 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> cd(5);
  eff5 -> Draw("APL+");
  eff5 -> SetMarkerStyle(20);
  eff5 -> SetMarkerColor(kRed);
  eff5 -> SetTitle("F8PLA LEFT Efficiency");
  eff5 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff5 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> cd(6);
  eff6 -> Draw("APL+");
  eff6 -> SetMarkerStyle(20);
  eff6 -> SetMarkerColor(kRed);
  eff6 -> SetTitle("F8PLA RIGHT Efficiency");
  eff6 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff6 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> cd(7);
  eff7 -> Draw("APL+");
  eff7 -> SetMarkerStyle(20);
  eff7 -> SetMarkerColor(kRed);
  eff7 -> SetTitle("F11PLA LEFT Efficiency");
  eff7 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff7 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> cd(8);
  eff8 -> Draw("APL+");
  eff8 -> SetMarkerStyle(20);
  eff8 -> SetMarkerColor(kRed);
  eff8 -> SetTitle("F11PLA RIGHT Efficiency");
  eff8 -> GetXaxis() -> SetTitle("RUN NUMBER");
  eff8 -> GetYaxis() -> SetTitle("Efficiency");

  c1 -> SaveAs("c1_effmon.eps");

}



