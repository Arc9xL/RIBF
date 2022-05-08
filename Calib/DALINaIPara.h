#ifndef _DALINaIPARA_H_
#define _DALINaIPARA_H_

class DALINaIPara
{
public:
  DALINaIPara(){  }
  ~DALINaIPara(){ }
  
  void SetParameters(Int_t i_1origin, Int_t i, TString n, Int_t f, Int_t l, Double_t tc, Double_t to, Double_t qc, Double_t qp, Double_t th, Double_t x, Double_t y, Double_t z, Double_t adcg, Double_t adcc,  Double_t tdcg, Double_t tdcc) {
    id_1origin=i_1origin; id=i; detname=n; fpl=f; layer=l; tcal=tc; toff=to; qcal=qc; qped=qp; theta=th; x_pos=x; y_pos=y; z_pos=z; adc_geo=adcg; adc_ch=adcc; tdc_geo=tdcg; tdc_ch=tdcc;}
  
  Int_t     id_1origin;
  Int_t     id;// 0-origin
  TString   detname;
  Int_t     fpl;
  Int_t     layer;
  Double_t  tcal;
  Double_t  toff;
  Double_t  qcal;
  Double_t  qped;
  //Double_t  pos[3]; // position in mm
  Double_t  theta; // angle w.r.t. target
  Double_t x_pos;
  Double_t y_pos;
  Double_t z_pos;

  Double_t adc_geo;
  Double_t adc_ch;
  Double_t tdc_geo;
  Double_t tdc_ch;
};

#endif
