#include <TMath.h>
#include <iostream>
#include "RIBF132Parameter.h"
#include <TXMLNode.h>
#include <TXMLParser.h>
#include <TDOMParser.h>
#include <TObject.h>
#include <TString.h>

void setup(RIBF132Parameter* para){
  
  //----plastic-----
  para->platdcb3f_ch2ns = 1./40.9609;// /Users/tanaka/anaroot/run/ytanaka/analysis_time_calib
  para->pla_twcoeff[0][0][0] = 0.0;   para->pla_twcoeff[0][0][1] = 0.0; //3L
  para->pla_twcoeff[0][1][0] = 0.0;   para->pla_twcoeff[0][1][1] = 0.0; //3R
  para->pla_twcoeff[1][0][0] = 0.0;   para->pla_twcoeff[1][0][1] = 0.0; //5L
  para->pla_twcoeff[1][1][0] = 0.0;   para->pla_twcoeff[1][1][1] = 0.0; //5R
  para->pla_twcoeff[2][0][0] = 0.0;   para->pla_twcoeff[2][0][1] = 0.0; //7L
  para->pla_twcoeff[2][1][0] = 0.0;   para->pla_twcoeff[2][1][1] = 0.0; //7R
  para->pla_twcoeff[3][0][0] = 0.0;   para->pla_twcoeff[3][0][1] = 0.0; //8L
  para->pla_twcoeff[3][1][0] = 0.0;   para->pla_twcoeff[3][1][1] = 0.0; //8R
  para->pla_twcoeff[4][0][0] = 0.0;   para->pla_twcoeff[4][0][1] = 0.0; //11L
  para->pla_twcoeff[4][1][0] = 0.0;   para->pla_twcoeff[4][1][1] = 0.0; //11R
  para->pla_twcoeff[5][0][0] = 0.0;   para->pla_twcoeff[5][0][1] = 0.0; //11longL
  para->pla_twcoeff[5][1][0] = 0.0;   para->pla_twcoeff[5][1][1] = 0.0; //11longR
  para->pla_twcoeff[6][0][0] = 0.0;   para->pla_twcoeff[6][0][1] = 0.0; //11vetoL
  para->pla_twcoeff[6][1][0] = 0.0;   para->pla_twcoeff[6][1][1] = 0.0; //11longR

  para->plaqdc_pedestal[0][0] = 0.0;  para->plaqdc_pedestal[0][1] = 0.0; //3L3R
  para->plaqdc_pedestal[1][0] = 0.0;  para->plaqdc_pedestal[1][1] = 0.0; //5L5R
  para->plaqdc_pedestal[2][0] = 0.0;  para->plaqdc_pedestal[2][1] = 0.0; //7L7R
  para->plaqdc_pedestal[3][0] = 0.0;  para->plaqdc_pedestal[3][1] = 0.0; //8L8R
  para->plaqdc_pedestal[4][0] = 0.0;  para->plaqdc_pedestal[4][1] = 0.0; //11L11R
  para->plaqdc_pedestal[5][0] = 0.0;  para->plaqdc_pedestal[5][1] = 0.0; //longL longR
  para->plaqdc_pedestal[6][0] = 0.0;  para->plaqdc_pedestal[6][1] = 0.0; //vetoL vetoR

  
  //----tof offset-----
  /// para->offset37_default  = 309.4 + 0.062 - 0.015;//  before 2017Jun
  ///  para->offset811_default = -167.0 - 0.025;//  before 2017Jun

  //para->offset37_default  =  309.458 ;// new macro automatic, 2017 July 6 // for data-set-1 (tof-offset analysis)
  //para->offset811_default = -167.027 ;// new macro automatic, 2017 July 6 // for data-set-1 (tof-offset analysis)

  //para->offset37_default  =  309.455 ;// new macro automatic, 2017 July 6 // for data-set-2 (tof-offset analysis)
  //para->offset811_default = -166.845 ;// new macro automatic, 2017 July 6 // for data-set-2 (tof-offset analysis)
  
  para->offset37_default  =  309.095 ;// new macro automatic, 2017 July 6 // for data-set-3 (tof-offset analysis)
  para->offset811_default = -167.010 ;// new macro automatic, 2017 July 6 // for data-set-3 (tof-offset analysis)

  //para->offset37_default  =  308.987 ;// new macro automatic, 2017 July 6 // for data-set-4 (tof-offset analysis)
  //para->offset811_default = -166.823 ;// new macro automatic, 2017 July 6 // for data-set-4 (tof-offset analysis)

  //para->offset37_default  =  309.567 ;// new macro automatic, 2017 July 6 // for data-set-6 (tof-offset analysis)
  //para->offset811_default = -166.933 ;// new macro automatic, 2017 July 6 // for data-set-6 (tof-offset analysis)
  
  para->clight = 0.299792458; // in m/ns
  para->length37  = 46.978; // in m
  para->length35  = 23.319;
  para->length57  = 23.659;
  para->length811 = 36.983;
  para->length89  = 13.823;
  para->length911 = 23.160;
  
  // added on 27Noiv for DALI doppler correction
  para->length78          = 10.163; // from 20170706_tofoffset... meeting slide
  para->offset78_default  = 80.652;// /Users/tanaka/ribf132analysis/calib/tof_offset_check/tof_offset_check_forF7F8
  
  para->zet7_coeff1  = (1.0/2.55379);
  para->zet7_coeff2  = 0.0;
  para->zet7_coeff3  = 0.0;
  para->zet11_coeff1 = (1.0/2.13795);
  para->zet11_coeff2 = 0.0;
  para->zet11_coeff3 = 0.0;
  
  
  //------IC ADC------
 
  //F7 IC
  para->f7icadc_gain[0] = 1.0;   para->f7icadc_gain[1] = 1.0;
  para->f7icadc_gain[2] = 1.0;   para->f7icadc_gain[3] = 1.0;
  para->f7icadc_gain[4] = 1.0;   para->f7icadc_gain[5] = 1.0;
  
  para->f7icadc_pedestal[0] = 0.0;   para->f7icadc_pedestal[1] = 0.0;
  para->f7icadc_pedestal[2] = 0.0;   para->f7icadc_pedestal[3] = 0.0;
  para->f7icadc_pedestal[4] = 0.0;   para->f7icadc_pedestal[5] = 0.0;
 
  //F11 IC1
  para->f11icadc_gain[0][0] = 0.74;   para->f11icadc_gain[0][1] = 0.95;
  para->f11icadc_gain[0][2] = 0.92;   para->f11icadc_gain[0][3] = 1.11;
  para->f11icadc_gain[0][4] = 1.00;   para->f11icadc_gain[0][5] = 0.96;
  para->f11icadc_gain[0][6] = 1.12;   para->f11icadc_gain[0][7] = 1.15;

  para->f11icadc_pedestal[0][0] = 68.5;    para->f11icadc_pedestal[0][1] = 101.2;
  para->f11icadc_pedestal[0][2] = 105.3;   para->f11icadc_pedestal[0][3] = 118.9;
  para->f11icadc_pedestal[0][4] = 164.1;   para->f11icadc_pedestal[0][5] = 120.0;
  para->f11icadc_pedestal[0][6] = 144.6;   para->f11icadc_pedestal[0][7] = 141.1;

  //F11 IC2
  para->f11icadc_gain[1][0] = 0.78;   para->f11icadc_gain[1][1] = 0.94;
  para->f11icadc_gain[1][2] = 0.94;   para->f11icadc_gain[1][3] = 1.09;
  para->f11icadc_gain[1][4] = 1.00;   para->f11icadc_gain[1][5] = 0.98;
  para->f11icadc_gain[1][6] = 0.97;   para->f11icadc_gain[1][7] = 1.21;

  para->f11icadc_pedestal[1][0] = 99.4;    para->f11icadc_pedestal[1][1] = 105.7;
  para->f11icadc_pedestal[1][2] = 85.5;    para->f11icadc_pedestal[1][3] = 155.8;
  para->f11icadc_pedestal[1][4] = 136.4;   para->f11icadc_pedestal[1][5] = 132.2;
  para->f11icadc_pedestal[1][6] = 161.4;   para->f11icadc_pedestal[1][7] = 67.5;
  

  //------IC F11 TDC------
  //F11IC1 TDC factors
  para->f11ictdc_offset[0][0] = 37.3152;     para->f11ictdc_factor[0][0] = -0.00127176;
  para->f11ictdc_offset[0][1] = 37.6405;     para->f11ictdc_factor[0][1] = -0.00126841;
  para->f11ictdc_offset[0][2] = 36.9662;     para->f11ictdc_factor[0][2] = -0.00126527;
  para->f11ictdc_offset[0][3] = 37.2958;     para->f11ictdc_factor[0][3] = -0.00126497;
  para->f11ictdc_offset[0][4] = 37.4035;     para->f11ictdc_factor[0][4] = -0.00126398;
  para->f11ictdc_offset[0][5] = 36.7904;     para->f11ictdc_factor[0][5] = -0.00126328;
  para->f11ictdc_offset[0][6] = 38.8079;     para->f11ictdc_factor[0][6] = -0.00126454;
  para->f11ictdc_offset[0][7] = 38.6512;     para->f11ictdc_factor[0][7] = -0.00126573;

  para->f11iczposF11ref[0][0] = -19.0;       
  para->f11iczposF11ref[0][1] = 31.0;
  para->f11iczposF11ref[0][2] = 81.0;
  para->f11iczposF11ref[0][3] = 131.0;
  para->f11iczposF11ref[0][4] = 181.0;
  para->f11iczposF11ref[0][5] = 231.0;
  para->f11iczposF11ref[0][6] = 281.0;
  para->f11iczposF11ref[0][7] = 331.0;
                     
                     
  //F11IC2 TDC factors
  para->f11ictdc_offset[1][0] = 33.9180;     para->f11ictdc_factor[1][0] = -0.00137448;
  para->f11ictdc_offset[1][1] = 34.4831;     para->f11ictdc_factor[1][1] = -0.00137219;
  para->f11ictdc_offset[1][2] = 34.9114;     para->f11ictdc_factor[1][2] = -0.0013698;
  para->f11ictdc_offset[1][3] = 34.9066;     para->f11ictdc_factor[1][3] = -0.00136558;
  para->f11ictdc_offset[1][4] = 35.7046;     para->f11ictdc_factor[1][4] = -0.00136317;
  para->f11ictdc_offset[1][5] = 35.7170;     para->f11ictdc_factor[1][5] = -0.001362;
  para->f11ictdc_offset[1][6] = 35.5695;     para->f11ictdc_factor[1][6] = -0.00136063;
  para->f11ictdc_offset[1][7] = 36.5127;     para->f11ictdc_factor[1][7] = -0.00135939;

  para->f11iczposF11ref[1][0] = 629.0;       
  para->f11iczposF11ref[1][1] = 679.0;
  para->f11iczposF11ref[1][2] = 729.0;
  para->f11iczposF11ref[1][3] = 779.0;
  para->f11iczposF11ref[1][4] = 829.0;
  para->f11iczposF11ref[1][5] = 879.0;
  para->f11iczposF11ref[1][6] = 929.0;
  para->f11iczposF11ref[1][7] = 979.0;
  
  
  //---dali ---
  para->dali_adc_factor[0]=(5.415518e+00); para->dali_adc_offset[0]=(-5.024169e+02);
  para->dali_adc_factor[1]=(3.862563e+00); para->dali_adc_offset[1]=(-3.387372e+02);
  para->dali_adc_factor[2]=(3.845935e+00); para->dali_adc_offset[2]=(-2.813245e+02);
  para->dali_adc_factor[3]=(3.719837e+00); para->dali_adc_offset[3]=(-3.781011e+02);
  para->dali_adc_factor[4]=(4.179195e+00); para->dali_adc_offset[4]=(-3.988029e+02);
  para->dali_adc_factor[5]=(3.363022e+00); para->dali_adc_offset[5]=(-2.792751e+02);
  para->dali_adc_factor[6]=(3.628235e+00); para->dali_adc_offset[6]=(-3.968569e+02);
  para->dali_adc_factor[7]=(3.712494e+00); para->dali_adc_offset[7]=(-3.817716e+02);
  para->dali_adc_factor[8]=(3.365862e+00); para->dali_adc_offset[8]=(-3.465610e+02);
  para->dali_adc_factor[9]=(3.916884e+00); para->dali_adc_offset[9]=(-2.886814e+02);
  para->dali_adc_factor[10]=(4.061240e+00); para->dali_adc_offset[10]=(-4.194423e+02);
  para->dali_adc_factor[11]=(3.314850e+00); para->dali_adc_offset[11]=(-3.306078e+02);
  para->dali_adc_factor[12]=(3.207487e+00); para->dali_adc_offset[12]=(-2.863803e+02);
  para->dali_adc_factor[13]=(6.348048e+00); para->dali_adc_offset[13]=(-6.421206e+02);
  para->dali_adc_factor[14]=(3.361650e+00); para->dali_adc_offset[14]=(-3.946769e+02);
  para->dali_adc_factor[15]=(3.317875e+00); para->dali_adc_offset[15]=(-3.054211e+02);
  para->dali_adc_factor[16]=(3.491435e+00); para->dali_adc_offset[16]=(-3.057620e+02);
  para->dali_adc_factor[17]=(3.608992e+00); para->dali_adc_offset[17]=(-2.845859e+02);
  para->dali_adc_factor[18]=(3.514634e+00); para->dali_adc_offset[18]=(-2.819040e+02);
  para->dali_adc_factor[19]=(3.748251e+00); para->dali_adc_offset[19]=(-3.916375e+02);
  para->dali_adc_factor[20]=(3.894455e+00); para->dali_adc_offset[20]=(-3.375416e+02);
  para->dali_adc_factor[21]=(3.377697e+00); para->dali_adc_offset[21]=(-3.539117e+02);
  para->dali_adc_factor[22]=(3.251135e+00); para->dali_adc_offset[22]=(-3.893169e+02);
  para->dali_adc_factor[23]=(3.595758e+00); para->dali_adc_offset[23]=(-2.966107e+02);
  para->dali_adc_factor[24]=(3.336710e+00); para->dali_adc_offset[24]=(-3.378156e+02);
  para->dali_adc_factor[25]=(4.459818e+00); para->dali_adc_offset[25]=(-4.507141e+02);
  para->dali_adc_factor[26]=(3.393412e+00); para->dali_adc_offset[26]=(-3.296636e+02);
  para->dali_adc_factor[27]=(3.307776e+00); para->dali_adc_offset[27]=(-2.638829e+02);
  para->dali_adc_factor[28]=(3.974823e+00); para->dali_adc_offset[28]=(-3.556938e+02);
  para->dali_adc_factor[29]=(3.514003e+00); para->dali_adc_offset[29]=(-3.393389e+02);
  para->dali_adc_factor[30]=(3.512257e+00); para->dali_adc_offset[30]=(-3.832793e+02);
  para->dali_adc_factor[31]=(3.735705e+00); para->dali_adc_offset[31]=(-3.814161e+02);
  para->dali_adc_factor[32]=(3.506423e+00); para->dali_adc_offset[32]=(-3.177167e+02);
  para->dali_adc_factor[33]=(3.430490e+00); para->dali_adc_offset[33]=(-3.088115e+02);
  para->dali_adc_factor[34]=(3.584409e+00); para->dali_adc_offset[34]=(-4.108193e+02);
  para->dali_adc_factor[35]=(3.342156e+00); para->dali_adc_offset[35]=(-3.497394e+02);
  para->dali_adc_factor[36]=(3.483958e+00); para->dali_adc_offset[36]=(-3.186306e+02);
  para->dali_adc_factor[37]=(3.476848e+00); para->dali_adc_offset[37]=(-3.641013e+02);
  para->dali_adc_factor[38]=(3.266667e+00); para->dali_adc_offset[38]=(-3.848811e+02);
  para->dali_adc_factor[39]=(3.254734e+00); para->dali_adc_offset[39]=(-3.599332e+02);
  para->dali_adc_factor[40]=(3.385734e+00); para->dali_adc_offset[40]=(-3.904311e+02);
  para->dali_adc_factor[41]=(4.909527e+00); para->dali_adc_offset[41]=(-3.836065e+02);
  para->dali_adc_factor[42]=(3.525370e+00); para->dali_adc_offset[42]=(-3.334736e+02);
  para->dali_adc_factor[43]=(3.347619e+00); para->dali_adc_offset[43]=(-3.494143e+02);
  para->dali_adc_factor[44]=(3.093617e+00); para->dali_adc_offset[44]=(-3.683549e+02);
  para->dali_adc_factor[45]=(3.545550e+00); para->dali_adc_offset[45]=(-4.002217e+02);
  para->dali_adc_factor[46]=(3.155183e+00); para->dali_adc_offset[46]=(-3.902503e+02);
  para->dali_adc_factor[47]=(3.160516e+00); para->dali_adc_offset[47]=(-2.974149e+02);
  para->dali_adc_factor[48]=(3.075181e+00); para->dali_adc_offset[48]=(-4.160697e+02);
  para->dali_adc_factor[49]=(3.379561e+00); para->dali_adc_offset[49]=(-3.725357e+02);
  para->dali_adc_factor[50]=(3.272647e+00); para->dali_adc_offset[50]=(-3.243504e+02);
  para->dali_adc_factor[51]=(3.208926e+00); para->dali_adc_offset[51]=(-3.820453e+02);
  para->dali_adc_factor[52]=(3.158362e+00); para->dali_adc_offset[52]=(-3.617897e+02);
  para->dali_adc_factor[53]=(3.205929e+00); para->dali_adc_offset[53]=(-3.590279e+02);
  para->dali_adc_factor[54]=(3.473388e+00); para->dali_adc_offset[54]=(-4.077088e+02);
  para->dali_adc_factor[55]=(3.308537e+00); para->dali_adc_offset[55]=(-3.733383e+02);
  para->dali_adc_factor[56]=(3.337501e+00); para->dali_adc_offset[56]=(-3.312329e+02);
  para->dali_adc_factor[57]=(3.277092e+00); para->dali_adc_offset[57]=(-4.119327e+02);
  para->dali_adc_factor[58]=(3.433849e+00); para->dali_adc_offset[58]=(-4.230542e+02);
  para->dali_adc_factor[59]=(3.289313e+00); para->dali_adc_offset[59]=(-4.231520e+02);
  para->dali_adc_factor[60]=(3.439985e+00); para->dali_adc_offset[60]=(-3.707607e+02);
  para->dali_adc_factor[61]=(3.353594e+00); para->dali_adc_offset[61]=(-4.045499e+02);
  para->dali_adc_factor[62]=(3.330840e+00); para->dali_adc_offset[62]=(-2.813716e+02);
  para->dali_adc_factor[63]=(3.315211e+00); para->dali_adc_offset[63]=(-3.866861e+02);
  para->dali_adc_factor[64]=(3.265882e+00); para->dali_adc_offset[64]=(-2.399301e+02);
  para->dali_adc_factor[65]=(3.453480e+00); para->dali_adc_offset[65]=(-3.078822e+02);
  para->dali_adc_factor[66]=(3.152633e+00); para->dali_adc_offset[66]=(-2.736559e+02);
  para->dali_adc_factor[67]=(2.937512e+00); para->dali_adc_offset[67]=(-2.232786e+02);
  para->dali_adc_factor[68]=(3.284520e+00); para->dali_adc_offset[68]=(-3.715675e+02);
  para->dali_adc_factor[69]=(3.172784e+00); para->dali_adc_offset[69]=(-2.826858e+02);
  para->dali_adc_factor[70]=(3.188431e+00); para->dali_adc_offset[70]=(-2.833326e+02);
  para->dali_adc_factor[71]=(3.171439e+00); para->dali_adc_offset[71]=(-2.888863e+02);
  para->dali_adc_factor[72]=(0.000000e+00); para->dali_adc_offset[72]=(-9.999900e+03);
  para->dali_adc_factor[73]=(3.144270e+00); para->dali_adc_offset[73]=(-2.576732e+02);
  para->dali_adc_factor[74]=(3.392895e+00); para->dali_adc_offset[74]=(-2.520771e+02);
  para->dali_adc_factor[75]=(3.330625e+00); para->dali_adc_offset[75]=(-3.043905e+02);
  para->dali_adc_factor[76]=(3.126546e+00); para->dali_adc_offset[76]=(-2.740484e+02);
  para->dali_adc_factor[77]=(3.110472e+00); para->dali_adc_offset[77]=(-2.375428e+02);
  para->dali_adc_factor[78]=(3.166401e+00); para->dali_adc_offset[78]=(-2.524299e+02);
  para->dali_adc_factor[79]=(3.446163e+00); para->dali_adc_offset[79]=(-3.129802e+02);
  para->dali_adc_factor[80]=(3.332798e+00); para->dali_adc_offset[80]=(-3.137937e+02);
  para->dali_adc_factor[81]=(3.150762e+00); para->dali_adc_offset[81]=(-3.476513e+02);
  para->dali_adc_factor[82]=(3.165247e+00); para->dali_adc_offset[82]=(-3.197379e+02);
  para->dali_adc_factor[83]=(3.177539e+00); para->dali_adc_offset[83]=(-3.320090e+02);
  para->dali_adc_factor[84]=(3.029355e+00); para->dali_adc_offset[84]=(-3.463752e+02);
  para->dali_adc_factor[85]=(3.117966e+00); para->dali_adc_offset[85]=(-3.410631e+02);
  para->dali_adc_factor[86]=(3.060235e+00); para->dali_adc_offset[86]=(-2.804197e+02);
  para->dali_adc_factor[87]=(3.290852e+00); para->dali_adc_offset[87]=(-2.992329e+02);
  para->dali_adc_factor[88]=(3.139177e+00); para->dali_adc_offset[88]=(-3.692270e+02);
  para->dali_adc_factor[89]=(3.318762e+00); para->dali_adc_offset[89]=(-2.778694e+02);
  para->dali_adc_factor[90]=(3.234108e+00); para->dali_adc_offset[90]=(-3.217164e+02);
  para->dali_adc_factor[91]=(3.092923e+00); para->dali_adc_offset[91]=(-4.018230e+02);
  para->dali_adc_factor[92]=(3.170521e+00); para->dali_adc_offset[92]=(-2.485671e+02);
  para->dali_adc_factor[93]=(3.090652e+00); para->dali_adc_offset[93]=(-3.177919e+02);
  para->dali_adc_factor[94]=(3.269384e+00); para->dali_adc_offset[94]=(-3.851253e+02);
  para->dali_adc_factor[95]=(3.226659e+00); para->dali_adc_offset[95]=(-3.491940e+02);
  para->dali_adc_factor[96]=(3.216362e+00); para->dali_adc_offset[96]=(-4.066807e+02);
  para->dali_adc_factor[97]=(3.118882e+00); para->dali_adc_offset[97]=(-2.920985e+02);
  para->dali_adc_factor[98]=(3.208446e+00); para->dali_adc_offset[98]=(-2.894006e+02);
  para->dali_adc_factor[99]=(3.260692e+00); para->dali_adc_offset[99]=(-3.564489e+02);
  para->dali_adc_factor[100]=(3.323403e+00); para->dali_adc_offset[100]=(-3.883158e+02);
  para->dali_adc_factor[101]=(3.049559e+00); para->dali_adc_offset[101]=(-2.930204e+02);
  para->dali_adc_factor[102]=(3.172804e+00); para->dali_adc_offset[102]=(-3.528461e+02);
  para->dali_adc_factor[103]=(3.236520e+00); para->dali_adc_offset[103]=(-2.692644e+02);
  para->dali_adc_factor[104]=(3.151813e+00); para->dali_adc_offset[104]=(-3.209100e+02);
  para->dali_adc_factor[105]=(3.290940e+00); para->dali_adc_offset[105]=(-2.609674e+02);
  para->dali_adc_factor[106]=(3.280472e+00); para->dali_adc_offset[106]=(-3.366975e+02);
  para->dali_adc_factor[107]=(3.245418e+00); para->dali_adc_offset[107]=(-2.311828e+02);
  para->dali_adc_factor[108]=(3.247125e+00); para->dali_adc_offset[108]=(-4.311911e+02);
  para->dali_adc_factor[109]=(2.938792e+00); para->dali_adc_offset[109]=(-3.362760e+02);
  para->dali_adc_factor[110]=(3.157320e+00); para->dali_adc_offset[110]=(-2.950403e+02);
  para->dali_adc_factor[111]=(3.045137e+00); para->dali_adc_offset[111]=(-2.330604e+02);
  para->dali_adc_factor[112]=(3.072291e+00); para->dali_adc_offset[112]=(-2.814967e+02);
  para->dali_adc_factor[113]=(3.104654e+00); para->dali_adc_offset[113]=(-2.673880e+02);
  para->dali_adc_factor[114]=(3.372056e+00); para->dali_adc_offset[114]=(-3.991462e+02);
  para->dali_adc_factor[115]=(3.312158e+00); para->dali_adc_offset[115]=(-3.427762e+02);
  para->dali_adc_factor[116]=(2.879299e+00); para->dali_adc_offset[116]=(-2.176149e+02);
  para->dali_adc_factor[117]=(3.299382e+00); para->dali_adc_offset[117]=(-2.650818e+02);
  para->dali_adc_factor[118]=(3.125344e+00); para->dali_adc_offset[118]=(-2.848185e+02);
  para->dali_adc_factor[119]=(3.221028e+00); para->dali_adc_offset[119]=(-2.579465e+02);
  para->dali_adc_factor[120]=(3.096236e+00); para->dali_adc_offset[120]=(-3.928783e+02);
  para->dali_adc_factor[121]=(3.006852e+00); para->dali_adc_offset[121]=(-3.011762e+02);
  para->dali_adc_factor[122]=(3.264885e+00); para->dali_adc_offset[122]=(-4.202108e+02);
  para->dali_adc_factor[123]=(3.244006e+00); para->dali_adc_offset[123]=(-3.187090e+02);
  para->dali_adc_factor[124]=(3.157685e+00); para->dali_adc_offset[124]=(-2.682337e+02);
  para->dali_adc_factor[125]=(3.199416e+00); para->dali_adc_offset[125]=(-2.003017e+02);
  para->dali_adc_factor[126]=(3.523141e+00); para->dali_adc_offset[126]=(-2.733824e+02);
  para->dali_adc_factor[127]=(3.606931e+00); para->dali_adc_offset[127]=(-4.273716e+02);
  para->dali_adc_factor[128]=(3.434688e+00); para->dali_adc_offset[128]=(-3.140113e+02);
  para->dali_adc_factor[129]=(3.247103e+00); para->dali_adc_offset[129]=(-3.237366e+02);
  para->dali_adc_factor[130]=(3.708907e+00); para->dali_adc_offset[130]=(-3.841941e+02);
  para->dali_adc_factor[131]=(3.108918e+00); para->dali_adc_offset[131]=(-3.030208e+02);
  para->dali_adc_factor[132]=(3.252397e+00); para->dali_adc_offset[132]=(-2.746209e+02);
  para->dali_adc_factor[133]=(3.399979e+00); para->dali_adc_offset[133]=(-3.057763e+02);
  para->dali_adc_factor[134]=(3.532442e+00); para->dali_adc_offset[134]=(-3.249564e+02);
  para->dali_adc_factor[135]=(4.973305e+00); para->dali_adc_offset[135]=(-4.823641e+02);
  para->dali_adc_factor[136]=(0.000000e+00); para->dali_adc_offset[136]=(-9.999900e+03);
  para->dali_adc_factor[137]=(3.050609e+00); para->dali_adc_offset[137]=(-3.297061e+02);
  para->dali_adc_factor[138]=(3.043876e+00); para->dali_adc_offset[138]=(-2.097706e+02);
  para->dali_adc_factor[139]=(3.693002e+00); para->dali_adc_offset[139]=(-3.840875e+02);
  para->dali_adc_factor[140]=(3.785705e+00); para->dali_adc_offset[140]=(-3.540886e+02);
  para->dali_adc_factor[141]=(3.547979e+00); para->dali_adc_offset[141]=(-3.318596e+02);
  para->dali_adc_factor[142]=(3.431918e+00); para->dali_adc_offset[142]=(-3.681465e+02);
  para->dali_adc_factor[143]=(3.434609e+00); para->dali_adc_offset[143]=(-4.448767e+02);
  para->dali_adc_factor[144]=(3.426836e+00); para->dali_adc_offset[144]=(-3.196915e+02);
  para->dali_adc_factor[145]=(3.478251e+00); para->dali_adc_offset[145]=(-4.038265e+02);
  para->dali_adc_factor[146]=(3.439046e+00); para->dali_adc_offset[146]=(-3.175414e+02);
  para->dali_adc_factor[147]=(3.210688e+00); para->dali_adc_offset[147]=(-3.806761e+02);
  para->dali_adc_factor[148]=(3.192599e+00); para->dali_adc_offset[148]=(-2.986998e+02);
  para->dali_adc_factor[149]=(3.288989e+00); para->dali_adc_offset[149]=(-4.127178e+02);
  para->dali_adc_factor[150]=(2.920244e+00); para->dali_adc_offset[150]=(-2.901394e+02);
  para->dali_adc_factor[151]=(3.034612e+00); para->dali_adc_offset[151]=(-3.592698e+02);
  para->dali_adc_factor[152]=(3.281777e+00); para->dali_adc_offset[152]=(-3.571844e+02);
  para->dali_adc_factor[153]=(2.945019e+00); para->dali_adc_offset[153]=(-3.034310e+02);
  para->dali_adc_factor[154]=(2.924582e+00); para->dali_adc_offset[154]=(-2.842653e+02);
  para->dali_adc_factor[155]=(2.863606e+00); para->dali_adc_offset[155]=(-3.120981e+02);
  para->dali_adc_factor[156]=(3.022848e+00); para->dali_adc_offset[156]=(-3.093721e+02);
  para->dali_adc_factor[157]=(3.187809e+00); para->dali_adc_offset[157]=(-4.185397e+02);
  para->dali_adc_factor[158]=(3.160556e+00); para->dali_adc_offset[158]=(-4.727005e+02);
  para->dali_adc_factor[159]=(3.129375e+00); para->dali_adc_offset[159]=(-3.421006e+02);
  para->dali_adc_factor[160]=(3.000146e+00); para->dali_adc_offset[160]=(-3.243778e+02);
  para->dali_adc_factor[161]=(3.161140e+00); para->dali_adc_offset[161]=(-3.352431e+02);
  para->dali_adc_factor[162]=(3.198884e+00); para->dali_adc_offset[162]=(-2.952751e+02);
  para->dali_adc_factor[163]=(2.987159e+00); para->dali_adc_offset[163]=(-2.904963e+02);
  para->dali_adc_factor[164]=(2.920627e+00); para->dali_adc_offset[164]=(-2.669650e+02);
  para->dali_adc_factor[165]=(3.061653e+00); para->dali_adc_offset[165]=(-2.739931e+02);
  para->dali_adc_factor[166]=(3.165020e+00); para->dali_adc_offset[166]=(-2.838034e+02);
  para->dali_adc_factor[167]=(3.289967e+00); para->dali_adc_offset[167]=(-3.253690e+02);
  para->dali_adc_factor[168]=(3.093492e+00); para->dali_adc_offset[168]=(-2.469802e+02);
  para->dali_adc_factor[169]=(2.820206e+00); para->dali_adc_offset[169]=(-2.971359e+02);
  para->dali_adc_factor[170]=(3.064676e+00); para->dali_adc_offset[170]=(-3.208597e+02);
  para->dali_adc_factor[171]=(3.158550e+00); para->dali_adc_offset[171]=(-3.619726e+02);
  para->dali_adc_factor[172]=(3.131728e+00); para->dali_adc_offset[172]=(-3.376111e+02);
  para->dali_adc_factor[173]=(3.119350e+00); para->dali_adc_offset[173]=(-3.658306e+02);
  para->dali_adc_factor[174]=(3.081606e+00); para->dali_adc_offset[174]=(-3.182251e+02);
  para->dali_adc_factor[175]=(3.115141e+00); para->dali_adc_offset[175]=(-3.650145e+02);
  para->dali_adc_factor[176]=(3.216349e+00); para->dali_adc_offset[176]=(-3.714971e+02);
  para->dali_adc_factor[177]=(3.060335e+00); para->dali_adc_offset[177]=(-3.251889e+02);
  para->dali_adc_factor[178]=(3.111730e+00); para->dali_adc_offset[178]=(-3.419776e+02);
  para->dali_adc_factor[179]=(3.133218e+00); para->dali_adc_offset[179]=(-4.386956e+02);
  para->dali_adc_factor[180]=(3.135909e+00); para->dali_adc_offset[180]=(-3.355743e+02);
  para->dali_adc_factor[181]=(2.856627e+00); para->dali_adc_offset[181]=(-3.210203e+02);
  para->dali_adc_factor[182]=(2.921594e+00); para->dali_adc_offset[182]=(-3.037118e+02);
  para->dali_adc_factor[183]=(3.028875e+00); para->dali_adc_offset[183]=(-3.789558e+02);
  para->dali_adc_factor[184]=(3.225743e+00); para->dali_adc_offset[184]=(-4.155148e+02);
  para->dali_adc_factor[185]=(3.094025e+00); para->dali_adc_offset[185]=(-3.117100e+02);

  para->dali_time_offset[0]=(5.860939e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[0]=(5.635204e+00);
  para->dali_time_offset[1]=(8.673169e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[1]=(3.882383e+00);
  para->dali_time_offset[2]=(3.944096e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[2]=(3.963046e+00);
  para->dali_time_offset[3]=(4.252979e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[3]=(4.449844e+00);
  para->dali_time_offset[4]=(4.794380e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[4]=(4.210158e+00);
  para->dali_time_offset[5]=(2.321113e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[5]=(4.734564e+00);
  para->dali_time_offset[6]=(7.047618e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[6]=(3.863120e+00);
  para->dali_time_offset[7]=(8.549069e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[7]=(3.797586e+00);
  para->dali_time_offset[8]=(4.088780e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[8]=(3.225137e+00);
  para->dali_time_offset[9]=(4.121066e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[9]=(2.742865e+00);
  para->dali_time_offset[10]=(5.140611e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[10]=(3.164167e+00);
  para->dali_time_offset[11]=(5.276350e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[11]=(3.321358e+00);
  para->dali_time_offset[12]=(5.241355e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[12]=(2.960939e+00);
  para->dali_time_offset[13]=(7.598646e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[13]=(3.078754e+00);
  para->dali_time_offset[14]=(4.977592e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[14]=(3.653995e+00);
  para->dali_time_offset[15]=(2.638806e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[15]=(2.876918e+00);
  para->dali_time_offset[16]=(3.317270e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[16]=(3.544786e+00);
  para->dali_time_offset[17]=(3.338407e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[17]=(3.041041e+00);
  para->dali_time_offset[18]=(2.770114e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[18]=(2.699614e+00);
  para->dali_time_offset[19]=(4.523999e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[19]=(3.034984e+00);
  para->dali_time_offset[20]=(1.525098e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[20]=(3.253598e+00);
  para->dali_time_offset[21]=(2.777501e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[21]=(3.165717e+00);
  para->dali_time_offset[22]=(5.445386e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[22]=(2.426885e+00);
  para->dali_time_offset[23]=(4.400542e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[23]=(2.846384e+00);
  para->dali_time_offset[24]=(4.630725e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[24]=(2.711634e+00);
  para->dali_time_offset[25]=(4.573006e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[25]=(3.000073e+00);
  para->dali_time_offset[26]=(3.564170e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[26]=(2.782845e+00);
  para->dali_time_offset[27]=(6.364305e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[27]=(3.420555e+00);
  para->dali_time_offset[28]=(6.613477e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[28]=(3.683313e+00);
  para->dali_time_offset[29]=(3.732590e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[29]=(3.626538e+00);
  para->dali_time_offset[30]=(4.277039e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[30]=(2.820582e+00);
  para->dali_time_offset[31]=(8.626494e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[31]=(3.292963e+00);
  para->dali_time_offset[32]=(1.734497e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[32]=(3.089016e+00);
  para->dali_time_offset[33]=(1.467213e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[33]=(2.588474e+00);
  para->dali_time_offset[34]=(2.705303e-02);//relative to common offset of 1058.0//
  para->dali_time_sigma[34]=(2.781185e+00);
  para->dali_time_offset[35]=(6.512237e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[35]=(2.954330e+00);
  para->dali_time_offset[36]=(6.702623e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[36]=(2.340536e+00);
  para->dali_time_offset[37]=(3.798186e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[37]=(3.943382e+00);
  para->dali_time_offset[38]=(2.927134e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[38]=(2.616672e+00);
  para->dali_time_offset[39]=(2.966119e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[39]=(2.665154e+00);
  para->dali_time_offset[40]=(3.444564e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[40]=(2.698842e+00);
  para->dali_time_offset[41]=(-3.823858e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[41]=(1.858842e+00);
  para->dali_time_offset[42]=(4.489443e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[42]=(2.415948e+00);
  para->dali_time_offset[43]=(4.415884e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[43]=(2.190776e+00);
  para->dali_time_offset[44]=(4.447743e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[44]=(3.035645e+00);
  para->dali_time_offset[45]=(4.792864e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[45]=(2.254487e+00);
  para->dali_time_offset[46]=(6.831944e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[46]=(2.376454e+00);
  para->dali_time_offset[47]=(5.577052e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[47]=(2.661537e+00);
  para->dali_time_offset[48]=(2.598004e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[48]=(2.748859e+00);
  para->dali_time_offset[49]=(-8.382058e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[49]=(2.652108e+00);
  para->dali_time_offset[50]=(2.081628e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[50]=(2.054954e+00);
  para->dali_time_offset[51]=(2.420525e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[51]=(2.487231e+00);
  para->dali_time_offset[52]=(1.305066e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[52]=(2.163368e+00);
  para->dali_time_offset[53]=(2.680600e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[53]=(3.852517e+00);
  para->dali_time_offset[54]=(4.625884e-02);//relative to common offset of 1058.0//
  para->dali_time_sigma[54]=(2.391267e+00);
  para->dali_time_offset[55]=(3.067284e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[55]=(2.679616e+00);
  para->dali_time_offset[56]=(1.106308e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[56]=(2.376422e+00);
  para->dali_time_offset[57]=(1.491880e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[57]=(3.179233e+00);
  para->dali_time_offset[58]=(6.854875e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[58]=(3.083441e+00);
  para->dali_time_offset[59]=(3.812511e-02);//relative to common offset of 1058.0//
  para->dali_time_sigma[59]=(1.827696e+00);
  para->dali_time_offset[60]=(4.444719e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[60]=(3.953817e+00);
  para->dali_time_offset[61]=(1.889592e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[61]=(2.377380e+00);
  para->dali_time_offset[62]=(2.047757e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[62]=(2.067571e+00);
  para->dali_time_offset[63]=(1.954402e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[63]=(3.330772e+00);
  para->dali_time_offset[64]=(-1.582237e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[64]=(2.611379e+00);
  para->dali_time_offset[65]=(4.390505e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[65]=(3.905028e+00);
  para->dali_time_offset[66]=(-1.896723e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[66]=(4.496881e+00);
  para->dali_time_offset[67]=(-3.060320e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[67]=(3.324789e+00);
  para->dali_time_offset[68]=(-9.205697e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[68]=(2.344038e+00);
  para->dali_time_offset[69]=(-3.021726e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[69]=(2.842831e+00);
  para->dali_time_offset[70]=(-2.485713e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[70]=(2.839879e+00);
  para->dali_time_offset[71]=(-1.999999e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[71]=(2.429524e+00);
  para->dali_time_offset[72]=(0.000000e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[72]=(-9.999000e+02);
  para->dali_time_offset[73]=(-1.401382e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[73]=(2.877895e+00);
  para->dali_time_offset[74]=(-7.163931e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[74]=(3.593369e+00);
  para->dali_time_offset[75]=(-3.637889e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[75]=(3.056231e+00);
  para->dali_time_offset[76]=(-1.555915e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[76]=(3.794843e+00);
  para->dali_time_offset[77]=(-1.878899e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[77]=(3.324485e+00);
  para->dali_time_offset[78]=(-1.867696e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[78]=(2.863844e+00);
  para->dali_time_offset[79]=(1.690464e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[79]=(3.169217e+00);
  para->dali_time_offset[80]=(-2.188084e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[80]=(3.385191e+00);
  para->dali_time_offset[81]=(-2.816335e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[81]=(2.534140e+00);
  para->dali_time_offset[82]=(-1.947945e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[82]=(2.829872e+00);
  para->dali_time_offset[83]=(-3.791885e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[83]=(3.101230e+00);
  para->dali_time_offset[84]=(-5.130737e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[84]=(3.029746e+00);
  para->dali_time_offset[85]=(-5.937180e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[85]=(3.420492e+00);
  para->dali_time_offset[86]=(-4.353065e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[86]=(2.908487e+00);
  para->dali_time_offset[87]=(-8.165024e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[87]=(2.726774e+00);
  para->dali_time_offset[88]=(-9.277650e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[88]=(2.698339e+00);
  para->dali_time_offset[89]=(-1.729638e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[89]=(2.863309e+00);
  para->dali_time_offset[90]=(-2.578698e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[90]=(2.733706e+00);
  para->dali_time_offset[91]=(-1.781926e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[91]=(2.692046e+00);
  para->dali_time_offset[92]=(-2.804201e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[92]=(2.942884e+00);
  para->dali_time_offset[93]=(1.703347e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[93]=(2.938345e+00);
  para->dali_time_offset[94]=(8.120335e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[94]=(2.671583e+00);
  para->dali_time_offset[95]=(-7.141506e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[95]=(2.694704e+00);
  para->dali_time_offset[96]=(-3.079194e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[96]=(3.317439e+00);
  para->dali_time_offset[97]=(-3.036870e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[97]=(2.532859e+00);
  para->dali_time_offset[98]=(-3.579360e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[98]=(2.473422e+00);
  para->dali_time_offset[99]=(-2.301286e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[99]=(2.255350e+00);
  para->dali_time_offset[100]=(-3.612735e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[100]=(2.899931e+00);
  para->dali_time_offset[101]=(-1.149708e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[101]=(2.192237e+00);
  para->dali_time_offset[102]=(-1.607086e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[102]=(2.466226e+00);
  para->dali_time_offset[103]=(-1.918176e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[103]=(2.405913e+00);
  para->dali_time_offset[104]=(-2.363447e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[104]=(2.728486e+00);
  para->dali_time_offset[105]=(-3.210132e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[105]=(2.681172e+00);
  para->dali_time_offset[106]=(1.123050e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[106]=(2.601693e+00);
  para->dali_time_offset[107]=(-1.345532e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[107]=(2.587901e+00);
  para->dali_time_offset[108]=(-2.478857e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[108]=(2.849367e+00);
  para->dali_time_offset[109]=(8.020989e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[109]=(2.956681e+00);
  para->dali_time_offset[110]=(1.046372e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[110]=(2.706065e+00);
  para->dali_time_offset[111]=(4.684934e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[111]=(2.876346e+00);
  para->dali_time_offset[112]=(-2.440650e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[112]=(2.512238e+00);
  para->dali_time_offset[113]=(-3.107784e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[113]=(2.726482e+00);
  para->dali_time_offset[114]=(-1.400493e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[114]=(2.616047e+00);
  para->dali_time_offset[115]=(5.564470e-02);//relative to common offset of 1058.0//
  para->dali_time_sigma[115]=(2.532669e+00);
  para->dali_time_offset[116]=(-6.795905e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[116]=(2.768733e+00);
  para->dali_time_offset[117]=(-1.406068e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[117]=(2.749972e+00);
  para->dali_time_offset[118]=(-5.198453e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[118]=(2.264701e+00);
  para->dali_time_offset[119]=(-1.097397e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[119]=(2.549104e+00);
  para->dali_time_offset[120]=(6.379540e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[120]=(2.098319e+00);
  para->dali_time_offset[121]=(-3.630520e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[121]=(2.321085e+00);
  para->dali_time_offset[122]=(-8.679769e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[122]=(3.476811e+00);
  para->dali_time_offset[123]=(-1.094970e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[123]=(3.852591e+00);
  para->dali_time_offset[124]=(-9.085013e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[124]=(3.045270e+00);
  para->dali_time_offset[125]=(-7.185333e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[125]=(2.502486e+00);
  para->dali_time_offset[126]=(-8.360159e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[126]=(2.349988e+00);
  para->dali_time_offset[127]=(-1.040682e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[127]=(2.862277e+00);
  para->dali_time_offset[128]=(-1.046731e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[128]=(2.623894e+00);
  para->dali_time_offset[129]=(-9.945023e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[129]=(1.842587e+00);
  para->dali_time_offset[130]=(1.592631e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[130]=(4.597950e+00);
  para->dali_time_offset[131]=(-9.153298e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[131]=(3.145408e+00);
  para->dali_time_offset[132]=(-1.054283e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[132]=(1.459606e+00);
  para->dali_time_offset[133]=(-1.081114e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[133]=(1.435315e+00);
  para->dali_time_offset[134]=(1.732650e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[134]=(5.095761e+00);
  para->dali_time_offset[135]=(2.971013e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[135]=(4.616176e+00);
  para->dali_time_offset[136]=(0.000000e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[136]=(-9.999000e+02);
  para->dali_time_offset[137]=(-1.068682e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[137]=(1.686833e+00);
  para->dali_time_offset[138]=(-9.842218e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[138]=(2.450399e+00);
  para->dali_time_offset[139]=(3.697363e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[139]=(4.676693e+00);
  para->dali_time_offset[140]=(3.693422e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[140]=(4.472543e+00);
  para->dali_time_offset[141]=(-1.195150e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[141]=(1.784815e+00);
  para->dali_time_offset[142]=(-1.111397e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[142]=(1.564807e+00);
  para->dali_time_offset[143]=(-9.682017e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[143]=(2.076297e+00);
  para->dali_time_offset[144]=(-3.101153e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[144]=(2.747029e+00);
  para->dali_time_offset[145]=(-3.159373e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[145]=(3.550000e+00);
  para->dali_time_offset[146]=(-1.325242e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[146]=(1.730947e+00);
  para->dali_time_offset[147]=(-1.457144e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[147]=(1.566335e+00);
  para->dali_time_offset[148]=(-1.286333e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[148]=(2.102222e+00);
  para->dali_time_offset[149]=(-3.587062e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[149]=(2.973389e+00);
  para->dali_time_offset[150]=(-2.318245e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[150]=(2.448454e+00);
  para->dali_time_offset[151]=(-1.356066e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[151]=(1.402926e+00);
  para->dali_time_offset[152]=(-1.225883e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[152]=(1.641283e+00);
  para->dali_time_offset[153]=(-3.092584e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[153]=(3.190145e+00);
  para->dali_time_offset[154]=(1.436152e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[154]=(2.572384e+00);
  para->dali_time_offset[155]=(-1.313590e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[155]=(1.511405e+00);
  para->dali_time_offset[156]=(-1.294503e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[156]=(1.396595e+00);
  para->dali_time_offset[157]=(2.025459e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[157]=(2.862719e+00);
  para->dali_time_offset[158]=(-1.130275e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[158]=(2.655920e+00);
  para->dali_time_offset[159]=(-9.748490e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[159]=(1.608961e+00);
  para->dali_time_offset[160]=(-1.695029e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[160]=(1.418210e+00);
  para->dali_time_offset[161]=(-3.611062e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[161]=(2.464623e+00);
  para->dali_time_offset[162]=(-4.248206e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[162]=(2.822330e+00);
  para->dali_time_offset[163]=(-1.202583e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[163]=(1.257001e+00);
  para->dali_time_offset[164]=(-1.648217e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[164]=(1.335364e+00);
  para->dali_time_offset[165]=(-3.786999e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[165]=(2.234717e+00);
  para->dali_time_offset[166]=(-2.929705e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[166]=(2.658780e+00);
  para->dali_time_offset[167]=(-1.279411e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[167]=(1.343855e+00);
  para->dali_time_offset[168]=(-2.781028e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[168]=(2.382554e+00);
  para->dali_time_offset[169]=(-9.155865e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[169]=(2.176234e+00);
  para->dali_time_offset[170]=(-1.231283e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[170]=(1.323081e+00);
  para->dali_time_offset[171]=(-4.050793e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[171]=(2.824912e+00);
  para->dali_time_offset[172]=(-4.457457e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[172]=(2.874449e+00);
  para->dali_time_offset[173]=(-1.330683e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[173]=(1.388221e+00);
  para->dali_time_offset[174]=(-2.064859e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[174]=(2.903714e+00);
  para->dali_time_offset[175]=(-9.605853e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[175]=(2.734606e+00);
  para->dali_time_offset[176]=(-1.648399e+01);//relative to common offset of 1058.0//
  para->dali_time_sigma[176]=(1.357592e+00);
  para->dali_time_offset[177]=(-6.202871e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[177]=(2.892982e+00);
  para->dali_time_offset[178]=(-2.700676e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[178]=(2.475436e+00);
  para->dali_time_offset[179]=(-1.971391e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[179]=(2.369479e+00);
  para->dali_time_offset[180]=(-4.770022e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[180]=(2.510560e+00);
  para->dali_time_offset[181]=(-9.221214e-02);//relative to common offset of 1058.0//
  para->dali_time_sigma[181]=(2.372750e+00);
  para->dali_time_offset[182]=(3.148231e-01);//relative to common offset of 1058.0//
  para->dali_time_sigma[182]=(2.352091e+00);
  para->dali_time_offset[183]=(-4.566894e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[183]=(2.351817e+00);
  para->dali_time_offset[184]=(-4.124911e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[184]=(2.321286e+00);
  para->dali_time_offset[185]=(-2.998937e+00);//relative to common offset of 1058.0//
  para->dali_time_sigma[185]=(3.041006e+00);
   return ;
}
