#ifndef _TARTPPACPARA_H_
#define _TARTPPACPARA_H_

class PPACPara{
public:
  PPACPara(){}
  ~PPACPara(){ }

  void SetPalameters(Int_t i, TString n, Int_t f, 
		     Double_t c2na,
		     Double_t c2nx1, Double_t c2ny1,
		     Double_t c2nx2, Double_t c2ny2,
		     Double_t xkf, Double_t ykf, 
		     Double_t xko, Double_t yko, 
		     Double_t xnso, Double_t ynso, 
		     Double_t xpo, Double_t ypo, 
		     Double_t xzp, Double_t yzp, 
		     Double_t tdc_uf, 
		     Double_t tdc_of, 
		     Double_t txmin, Double_t txmax, 
		     Double_t tymin, Double_t tymax) {
    id=i; detname=n; fpl=f; ch2ns_a=c2na; ch2ns_x1=c2nx1; ch2ns_y1=c2ny1; ch2ns_x2=c2nx2; ch2ns_y2=c2ny2; xfactor=xkf; yfactor=ykf; xoffset=xko; yoffset=yko; xns_off=xnso; yns_off=ynso; xpos_off=xpo; ypos_off=ypo; xzpos=xzp; yzpos=yzp; tdc_underflow=tdc_uf; tdc_overflow=tdc_of; txsum_min=txmin; txsum_max=txmax; tysum_min=tymin; tysum_max=tymax; }

public:
  Int_t     id;
  TString   detname;
  Int_t     fpl;
  Double_t  ch2ns_a;  //  TDC calibration factor for a
  Double_t  ch2ns_x1;  //  TDC calibration factor for x1
  Double_t  ch2ns_y1;  //  TDC calibration factor for y1
  Double_t  ch2ns_x2;  //  TDC calibration factor for x2
  Double_t  ch2ns_y2;  //  TDC calibration factor for y2
  Double_t  xfactor; //  ns->mm calibration factor depending on delay line
  Double_t  yfactor; //  ns->mm calibration factor depending on delay line
  Double_t  xoffset; //  geometrical offset of x-plane in x-dir. inside of PPAC
  Double_t  yoffset; //  geometrical offset of y-plane in y-dir. inside of PPAC
  Double_t  xns_off; // timing offset of x-plane coming from differenct of left hand and right hand side cable length
  Double_t  yns_off; // timing offset of y-plane coming from differenct of left hand and right hand side cable length
  Double_t  xpos_off; // geometrical offset of x-plane in x-dir.
  Double_t  ypos_off; // geometrical offset of y-plane in y-dir.
  Double_t  xzpos; // z-position offset for x-plane wrt fpl position
  Double_t  yzpos; // z-position offset for y-plane wrt fpl position
  Double_t  tdc_underflow; // tdc under flow value
  Double_t  tdc_overflow; // tdc over flow value
  Double_t  txsum_min; // cut for timing sum. disabled if min>=max 
  Double_t  txsum_max; // cut for timing sum. disabled if min>=max 
  Double_t  tysum_min; // cut for timing sum. disabled if min>=max 
  Double_t  tysum_max; // cut for timing sum. disabled if min>=max 

};

#endif
