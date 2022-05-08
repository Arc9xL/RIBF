#ifndef _PLASTICPARA_H_
#define _PLASTICPARA_H_

class PlasticPara {

 public:
  PlasticPara(){}
  ~PlasticPara(){ }

  void SetPalameters(Int_t i, TString n, Int_t f, 
		     Double_t tcl, Double_t tcr, 
		     Double_t qpedl, Double_t qpedr, 
		     Double_t ts_al, Double_t ts_bl, 
		     Double_t ts_ar, Double_t ts_br, 
		     Double_t tdc_uf, 
		     Double_t tdc_of, 
		     Double_t z){
    id=i; detname=n; fpl=f; 
    tcal_left=tcl; tcal_right=tcr; qped_left=qpedl; qped_right=qpedr; 
    tslew_left_a=ts_al; tslew_left_b=ts_bl; 
    tslew_right_a=ts_ar; tslew_right_b=ts_br; tdc_underflow=tdc_uf; tdc_overflow=tdc_of; zoffset=z; }

  Int_t     id;
  TString   detname;
  Int_t     fpl;
  // calibration value for TDC -> timing
  Double_t  tcal_left;
  Double_t  tcal_right;
  Double_t  qped_left;
  Double_t  qped_right;

  // Slew correction parameters for left, tslew = a/sqrt(t)+b
  // set a=0, b=0 to trun off slewing correction
  Double_t  tslew_left_a;
  Double_t  tslew_left_b;
  // Slew correction parameters for right, tslew = a/sqrt(t)+b
  // set a=0, b=0 to trun off slewing correction
  Double_t  tslew_right_a;
  Double_t  tslew_right_b;
  Double_t  tdc_underflow;
  Double_t  tdc_overflow;
  Double_t  zoffset;
};

#endif
