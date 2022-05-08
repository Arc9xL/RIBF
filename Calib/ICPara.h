#ifndef _ICPARA_H_
#define _ICPARA_H_

class ICPara
{
 public:
  ICPara(){  }
  ~ICPara(){ }

  void SetParameters(Int_t i, TString n, Int_t f, Double_t c2m0, Double_t c2m1, Double_t zc0, Double_t zc1, Double_t zc2, Double_t ip){
    id=i; detname=n; fpl=f; ionpair=ip;
    ch2mev[0] = c2m0; ch2mev[1] = c2m1;
    zcoef[0]  = zc0; zcoef[1]  = zc1; zcoef[2]  = zc2;
  }
  void SetPedestal(Double_t * ped){
    for(Int_t i=0;i<12;i++){ //replaced  NUM_IC_CHANNEL with 12;
      pedestal[i] = ped[i];
    }
  }
  
  Int_t     id;
  TString   detname;
  Int_t     fpl;
  Double_t  ch2mev[2];
  Double_t  zcoef[3];
  Double_t  ionpair;
  Double_t  pedestal[12]; //replaced  NUM_IC_CHANNEL with 12;
 
};

#endif
