#ifndef _FOCALPLANEPARA_H_
#define _FOCALPLANEPARA_H_

class FocalPlanePara{
  
 public:
  FocalPlanePara(){
    zpos_offset = 0.0;
    zpos = 0.0;
    id=-1;
    fpl=-1;
  }
  void SetParameters(Int_t i, Int_t f, Double_t z){
    id = i; fpl=f; zpos=z;
  }
  ~FocalPlanePara(){ }

  Int_t     id;
  Int_t     fpl;
  Double_t  zpos;
  Double_t  zpos_offset;

};

#endif
