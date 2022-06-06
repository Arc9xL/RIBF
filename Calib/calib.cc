#include <stdio.h>
#include <TMath.h>
#include <TMatrixD.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include "RIBF132Raw.h"
#include "RIBF132CalibOut.h"
#include "RIBF132Parameter.h"
#include "setup.C"
#include "optics_function.C"
#include <TRandom3.h>
#include <TXMLNode.h>
#include <TXMLParser.h>
#include <TDOMParser.h>
#include <TObject.h>
#include <TString.h>

TRandom3 *random3;

//------------------------------------------------------------------

double function_doppler(double energy_lab, double theta_lab, double beta_beam)
{
  // theta_lab = 0 for forward gamma. theta is in deg.

  double theta_rad         = theta_lab*(3.14159265358979312)/180.0;
  double gamma_beam        = 1./TMath::Sqrt(1. - beta_beam*beta_beam);
  double energy_beam_frame = gamma_beam * energy_lab * (1.0 - beta_beam * TMath::Cos(theta_rad));

  return energy_beam_frame;
}

//------------------------------------------------------------------

void EventRaw2Calib(RIBF132Raw* raw, RIBF132CalibOut* cal, RIBF132Parameter *para)
{
  cal -> test_cal_var = raw -> F5X;
  //  std::cout << "raw->F5X" << raw->F5X << std::endl;
  
  for(int i=0; i<7; i++)
  {
    for(int ii=0; ii<4; ii++)
    {
      cal -> test_cal_numhit[i][ii] = raw -> PPACTX2_NumHit[i][ii];

      //std::cout <<raw->PPACTX2_NumHit[i][ii] <<std::endl;
    }
  }
  
  
  //-----PPAC--------
  for(int ippac=0; ippac<7; ippac++)
  {
    for (int j=0; j<4; j++)
    {
      //
      cal -> PPACTSumX[ippac][j]      = -9999.;
      cal -> PPACTDiffX[ippac][j]     = -9999.;
      cal -> PPACTSumY[ippac][j]      = -9999.;
      cal -> PPACTDiffY[ippac][j]     = -9999.;
      cal -> PPACX[ippac][j]          = -9999.;
      cal -> PPACY[ippac][j]          = -9999.;
      cal -> PPACFiredX[ippac][j]     = false;
      cal -> PPACFiredY[ippac][j]     = false;

      //
      cal -> PPACX_online[ippac][j]   = raw -> PPACX[ippac][j];           // copy from online
      cal -> PPACY_online[ippac][j]   = raw -> PPACY[ippac][j];           // copy from online
      cal -> PPACTX1_NumHit[ippac][j] = raw -> PPACTX1_NumHit[ippac][j];
      cal -> PPACTX2_NumHit[ippac][j] = raw -> PPACTX2_NumHit[ippac][j];
      cal -> PPACTY1_NumHit[ippac][j] = raw -> PPACTY1_NumHit[ippac][j];
      cal -> PPACTY2_NumHit[ippac][j] = raw -> PPACTY2_NumHit[ippac][j];
      cal -> PPACTA_NumHit[ippac][j]  = raw -> PPACTA_NumHit[ippac][j];
      cal -> PPACXZpos[ippac][j]      = raw -> PPACXZpos[ippac][j];
      cal -> PPACYZpos[ippac][j]      = raw -> PPACYZpos[ippac][j];

      //
      cal -> PPACResX[ippac][j]       = -9999.;
      cal -> PPACResY[ippac][j]       = -9999.;

      //
      double tx1 = raw -> PPACTX1_s[ippac][j] * (para -> ppac[ippac][j] -> ch2ns_x1);    // TDC calibration factor for x1
      double tx2 = raw -> PPACTX2_s[ippac][j] * (para -> ppac[ippac][j] -> ch2ns_x2);    // TDC calibration factor for x2
      double ty1 = raw -> PPACTY1_s[ippac][j] * (para -> ppac[ippac][j] -> ch2ns_y1);    // TDC calibration factor for y1
      double ty2 = raw -> PPACTY2_s[ippac][j] * (para -> ppac[ippac][j] -> ch2ns_y2);    // TDC calibration factor for y2
      double ta  = raw -> PPACTA_s[ippac][j]  * (para -> ppac[ippac][j] -> ch2ns_a);     // TDC calibration factor for a

      // Added by Divyang to plot Tx1-Tx2 and Ty1-Ty2 correlation
      //
      // Note: Real time is tx1 - ta
      //       means you need to include PPACTA_s
      //       but I just need correlation so inclusion of "ta" will only decrease the count
      //       and that is not what we need.
      //
      if (raw -> PPACTX1_s[ippac][j] == -9999. || raw -> PPACTA_s[ippac][j] == -9999.) {cal -> PPAC_Tx1[ippac][j] = -9999.;} else {cal -> PPAC_Tx1[ippac][j] = tx1 - ta;}
      if (raw -> PPACTX2_s[ippac][j] == -9999. || raw -> PPACTA_s[ippac][j] == -9999.) {cal -> PPAC_Tx2[ippac][j] = -9999.;} else {cal -> PPAC_Tx2[ippac][j] = tx2 - ta;}
      if (raw -> PPACTY1_s[ippac][j] == -9999. || raw -> PPACTA_s[ippac][j] == -9999.) {cal -> PPAC_Ty1[ippac][j] = -9999.;} else {cal -> PPAC_Ty1[ippac][j] = ty1 - ta;}
      if (raw -> PPACTY2_s[ippac][j] == -9999. || raw -> PPACTA_s[ippac][j] == -9999.) {cal -> PPAC_Ty2[ippac][j] = -9999.;} else {cal -> PPAC_Ty2[ippac][j] = ty2 - ta;}

      double tsumx_min    = (para -> ppac[ippac][j] -> txsum_min);    // cut for timing sum. disabled if min>=max 
      double tsumx_max    = (para -> ppac[ippac][j] -> txsum_max);    // cut for timing sum. disabled if min>=max 
      double xdtimeoffset = (para -> ppac[ippac][j] -> xns_off);      // timing offset of x-plane coming from differenct of left hand and right hand side cable length
      double xfactor      = (para -> ppac[ippac][j] -> xfactor);      // ns->mm calibration factor depending on delay line
      double xoffset      = (para -> ppac[ippac][j] -> xoffset);      // geometrical offset of x-plane in x-dir. inside of PPAC
      double xposoffset   = (para -> ppac[ippac][j] -> xpos_off);     // geometrical offset of x-plane in x-dir.
      double tsumy_min    = (para -> ppac[ippac][j] -> tysum_min);    // cut for timing sum. disabled if min>=max 
      double tsumy_max    = (para -> ppac[ippac][j] -> tysum_max);    // cut for timing sum. disabled if min>=max 
      double ydtimeoffset = (para -> ppac[ippac][j] -> yns_off);      // timing offset of y-plane coming from differenct of left hand and right hand side cable length
      double yfactor      = (para -> ppac[ippac][j] -> yfactor);      // ns->mm calibration factor depending on delay line
      double yoffset      = (para -> ppac[ippac][j] -> yoffset);      // geometrical offset of y-plane in y-dir. inside of PPAC
      double yposoffset   = (para -> ppac[ippac][j] -> ypos_off);     // geometrical offset of x-plane in x-dir.
      
      //
      if(0.<tx1 && 0.<tx2 && 0.<ta)
      {
        cal -> PPACTSumX[ippac][j]  = tx1 + tx2 - 2.0*ta; // (tx1 - ta) + (tx2 - ta), we dont need timeoff set for Tsum
        cal -> PPACTDiffX[ippac][j] = tx1 - tx2;          // (tx1 - ta) - (tx2 - ta)
      }

      if(0.<ty1 && 0.<ty2 && 0.< ta)
      {
        // Real time is t = t_cathod - t_anode
        cal -> PPACTSumY[ippac][j]  = ty1 + ty2 - 2.0*ta; // (ty1 - ta) + (ty2 - ta)
        cal -> PPACTDiffY[ippac][j] = ty1 - ty2;          // (ty1 - ta) - (ty2 - ta)
      }


      // Here we do the Tsum selection
      // Calculate the position of an event only if it is within the tsum range
      if(tsumx_min <= cal->PPACTSumX[ippac][j]  && cal->PPACTSumX[ippac][j] <= tsumx_max)
      {
        // timing offset of x-plane coming from difference of left hand and right hand side cable length
        double temp_tdiffx =  cal->PPACTDiffX[ippac][j] - xdtimeoffset;

        // X = Kx* (Tx1 - Tx2) + Xoff
        cal -> PPACX[ippac][j]      = -1.0*(temp_tdiffx * xfactor /2.0 - xoffset - xposoffset ); // sign -1 for optics-definition of x.
        cal -> PPACFiredX[ippac][j] = true;
      }

      if(tsumy_min <= cal->PPACTSumY[ippac][j]  && cal->PPACTSumY[ippac][j] <= tsumy_max)
      {
        // timing offset of y-plane coming from difference of left hand and right hand side cable length
        double temp_tdiffy =  cal->PPACTDiffY[ippac][j] - ydtimeoffset;

        // Y = Ky* (Ty1 - Ty2) + Yoff
        cal -> PPACY[ippac][j]      = 1.0*(temp_tdiffy * yfactor /2.0 - yoffset - yposoffset ); // sign +1 for y
        cal -> PPACFiredY[ippac][j] = true;
      }
      //--------------
    }
  }
  
  ///----------Track-------------
  cal -> X3_online  = raw -> F3X;
  cal -> Y3_online  = raw -> F3Y;
  cal -> A3_online  = raw -> F3A;
  cal -> B3_online  = raw -> F3B;
  cal -> X5_online  = raw -> F5X;
  cal -> Y5_online  = raw -> F5Y;
  cal -> A5_online  = raw -> F5A;
  cal -> B5_online  = raw -> F5B;
  cal -> X7_online  = raw -> F7X;
  cal -> Y7_online  = raw -> F7Y;
  cal -> A7_online  = raw -> F7A;
  cal -> B7_online  = raw -> F7B;
  cal -> X8_online  = raw -> F8X;
  cal -> Y8_online  = raw -> F8Y;
  cal -> A8_online  = raw -> F8A;
  cal -> B8_online  = raw -> F8B;
  cal -> X9_online  = raw -> F9X;
  cal -> Y9_online  = raw -> F9Y;
  cal -> A9_online  = raw -> F9A;
  cal -> B9_online  = raw -> F9B;
  cal -> X11_online = raw -> F11X;
  cal -> Y11_online = raw -> F11Y;
  cal -> A11_online = raw -> F11A;
  cal -> B11_online = raw -> F11B;
  
  cal -> X3 = -9999.;  cal -> X5 = -9999.;  cal -> X7 = -9999.;  cal -> X8 = -9999.;  cal -> X9 = -9999.;  cal -> X11 = -9999.;
  cal -> Y3 = -9999.;  cal -> Y5 = -9999.;  cal -> Y7 = -9999.;  cal -> Y8 = -9999.;  cal -> Y9 = -9999.;  cal -> Y11 = -9999.;
  cal -> A3 = -9999.;  cal -> A5 = -9999.;  cal -> A7 = -9999.;  cal -> A8 = -9999.;  cal -> A9 = -9999.;  cal -> A11 = -9999.;
  cal -> B3 = -9999.;  cal -> B5 = -9999.;  cal -> B7 = -9999.;  cal -> B8 = -9999.;  cal -> B9 = -9999.;  cal -> B11 = -9999.;

  cal -> F3SSRX = -9999.; cal -> F5SSRX = -9999.; cal -> F7SSRX = -9999.; cal -> F8SSRX = -9999.; cal -> F9SSRX = -9999.; cal -> F11SSRX = -9999.;
  cal -> F3SSRY = -9999.; cal -> F5SSRY = -9999.; cal -> F7SSRY = -9999.; cal -> F8SSRY = -9999.; cal -> F9SSRY = -9999.; cal -> F11SSRY = -9999.;
  
  cal -> F3TrackedX  = false;  cal -> F3TrackedY  = false;
  cal -> F5TrackedX  = false;  cal -> F5TrackedY  = false;
  cal -> F7TrackedX  = false;  cal -> F7TrackedY  = false;
  cal -> F8TrackedX  = false;  cal -> F8TrackedY  = false;
  cal -> F9TrackedX  = false;  cal -> F9TrackedY  = false;
  cal -> F11TrackedX = false;  cal -> F11TrackedY = false;
  
  cal -> F3NumFiredPPACX  = 0; for(int j=0; j<4; j++) { (cal -> F3NumFiredPPACX)  += (int)(cal -> PPACFiredX[0][j]); }
  cal -> F5NumFiredPPACX  = 0; for(int j=0; j<4; j++) { (cal -> F5NumFiredPPACX)  += (int)(cal -> PPACFiredX[1][j]); }
  cal -> F7NumFiredPPACX  = 0; for(int j=0; j<4; j++) { (cal -> F7NumFiredPPACX)  += (int)(cal -> PPACFiredX[2][j]); }
  cal -> F8NumFiredPPACX  = 0; for(int j=0; j<4; j++) { (cal -> F8NumFiredPPACX)  += (int)(cal -> PPACFiredX[3][j]); }
  cal -> F9NumFiredPPACX  = 0; for(int j=0; j<4; j++) { (cal -> F9NumFiredPPACX)  += (int)(cal -> PPACFiredX[4][j]); }
  cal -> F11NumFiredPPACX = 0; for(int j=0; j<4; j++) { (cal -> F11NumFiredPPACX) += (int)(cal -> PPACFiredX[6][j]); }
  cal -> F3NumFiredPPACY  = 0; for(int j=0; j<4; j++) { (cal -> F3NumFiredPPACY)  += (int)(cal -> PPACFiredY[0][j]); }
  cal -> F5NumFiredPPACY  = 0; for(int j=0; j<4; j++) { (cal -> F5NumFiredPPACY)  += (int)(cal -> PPACFiredY[1][j]); }
  cal -> F7NumFiredPPACY  = 0; for(int j=0; j<4; j++) { (cal -> F7NumFiredPPACY)  += (int)(cal -> PPACFiredY[2][j]); }
  cal -> F8NumFiredPPACY  = 0; for(int j=0; j<4; j++) { (cal -> F8NumFiredPPACY)  += (int)(cal -> PPACFiredY[3][j]); }
  cal -> F9NumFiredPPACY  = 0; for(int j=0; j<4; j++) { (cal -> F9NumFiredPPACY)  += (int)(cal -> PPACFiredY[4][j]); }
  cal -> F11NumFiredPPACY = 0; for(int j=0; j<4; j++) { (cal -> F11NumFiredPPACY) += (int)(cal -> PPACFiredY[6][j]); }

  //tracking calculation
  double temp_x[7];
  double temp_y[7];
  double temp_a[7];
  double temp_b[7];
  double temp_ssrx[7];  //sum of squared residual
  double temp_ssry[7];  //sum of squared residual
  
  for(int ippac=0; ippac<7; ippac++)
  {
    temp_x[ippac] = -9999.;  temp_a[ippac] = -9999.;  temp_ssrx[ippac] = -9999.;
    temp_y[ippac] = -9999.;  temp_b[ippac] = -9999.;  temp_ssry[ippac] = -9999.;

    TMatrixD xvector(2,1); xvector.Zero();
    TMatrixD yvector(2,1); yvector.Zero();
    TMatrixD xmatrix(2,2); xmatrix.Zero();
    TMatrixD ymatrix(2,2); ymatrix.Zero();

    TMatrixD xvector_solution(2,1); xvector_solution.Zero();
    TMatrixD yvector_solution(2,1); yvector_solution.Zero();

    //---xa reconstruction---

    // Reconstruction for an event is only possible if
    // (1A or 1B) and (2A or 2B) is fired
    // basically: atlease 2 points are required.
    // 3 points = more accuracy
    // 4 points = best accuracy
    if( ((cal->PPACFiredX[ippac][0]) || (cal->PPACFiredX[ippac][1])) && ((cal->PPACFiredX[ippac][2]) || (cal->PPACFiredX[ippac][3])))
    {
      // sum up matrix element and vector for least sq minimization
      for(int j=0; j<4; j++)                                        // loop for all A and B, x position plates
      {
        double z_here = cal -> PPACXZpos[ippac][j];                 // XZpos means Z position for X cathode plate.
        double x_here = cal -> PPACX[ippac][j];                     // this PPACX is what we calculated, PPACX_online is a different variable.

        if(cal->PPACFiredX[ippac][j])                               // only do the sum if PPAC is fired
        {
          xvector(0,0) += x_here;                                   // ( x   )
          xvector(1,0) += x_here * z_here;                          // ( x*z )

          xmatrix(0,0) += 1.0;    xmatrix(0,1) += z_here;           // ( 1  z   )
          xmatrix(1,0) += z_here; xmatrix(1,1) += z_here*z_here;    // ( z  z^2 )
        }
      }// sum up done

      // solve dchi2/dpara=0;
      xvector_solution = xmatrix.Invert()  * xvector ;               // .Invert() means inverse of the matrix
      temp_x[ippac]    = xvector_solution(0,0);
      temp_a[ippac]    = 1000.*TMath::ATan(xvector_solution(1,0));   // x-angle. May be it is in mrad. That's why we are multiplying by 1000
      temp_ssrx[ippac] = 0.0;                                        // initial value before summing up.
      
      //sum up chi2
      for(int j=0; j<4; j++)
      {
        double z_here = cal -> PPACXZpos[ippac][j];
        double x_here = cal -> PPACX[ippac][j];
        if(cal->PPACFiredX[ippac][j])
        {
          temp_ssrx[ippac]+= TMath::Power((temp_x[ippac] + (TMath::Tan(temp_a[ippac]/1000.))*z_here - x_here), 2); // mm^2
	        cal->PPACResX[ippac][j] = (temp_x[ippac] + (TMath::Tan(temp_a[ippac]/1000.))*z_here - x_here);
	        //printf("%f\n",cal->PPACResX[ippac][j]);
        }
      } //sum-up chi2 end
    }//---xa reconstruction end---
    
    //---yb reconstruction---
    if( ((cal->PPACFiredY[ippac][0]) || (cal->PPACFiredY[ippac][1])) && ((cal->PPACFiredY[ippac][2]) || (cal->PPACFiredY[ippac][3])))
    {
      // sum up matrix element and vector for least sq minimization
      for(int j=0; j<4; j++)
      {
        double z_here = cal->PPACYZpos[ippac][j];
        double y_here = cal->PPACY[ippac][j];

        if(cal->PPACFiredY[ippac][j])
        {
          yvector(0,0) += y_here;
          yvector(1,0) += y_here * z_here;
          ymatrix(0,0) += 1.0;    ymatrix(0,1) += z_here;
          ymatrix(1,0) += z_here; ymatrix(1,1) += z_here*z_here;
        }
      }// sum up done

      // solve dchi2/dpara=0;
      yvector_solution = ymatrix.Invert()  * yvector ;
      temp_y[ippac]    = yvector_solution(0,0);
      temp_b[ippac]    = 1000.*TMath::ATan(yvector_solution(1,0));
      temp_ssry[ippac] = 0.0; //initial value before summing up.
      //sum up chi2
      for(int j=0; j<4; j++)
      {
        double z_here = cal->PPACYZpos[ippac][j];
        double y_here = cal->PPACY[ippac][j];

        if(cal->PPACFiredY[ippac][j])
        {
          temp_ssry[ippac]+= TMath::Power((temp_y[ippac] + (TMath::Tan(temp_b[ippac]/1000.))*z_here - y_here), 2); // mm^2
	        cal->PPACResY[ippac][j] = (temp_y[ippac] + (TMath::Tan(temp_b[ippac]/1000.))*z_here - y_here);
        }
      } //sum-up chi2 end

    }//---xa reconstruction end---
    
  }
  //
  if(temp_x[0] > -1000. && temp_a[0] > -1000.){ cal->X3 = temp_x[0]; cal->A3 = temp_a[0];  cal->F3SSRX = temp_ssrx[0];  cal->F3TrackedX = true; }
  if(temp_x[1] > -1000. && temp_a[1] > -1000.){ cal->X5 = temp_x[1]; cal->A5 = temp_a[1];  cal->F5SSRX = temp_ssrx[1];  cal->F5TrackedX = true; }
  if(temp_x[2] > -1000. && temp_a[2] > -1000.){ cal->X7 = temp_x[2]; cal->A7 = temp_a[2];  cal->F7SSRX = temp_ssrx[2];  cal->F7TrackedX = true; }
  if(temp_x[3] > -1000. && temp_a[3] > -1000.){ cal->X8 = temp_x[3]; cal->A8 = temp_a[3];  cal->F8SSRX = temp_ssrx[3];  cal->F8TrackedX = true; }
  if(temp_x[4] > -1000. && temp_a[4] > -1000.){ cal->X9 = temp_x[4]; cal->A9 = temp_a[4];  cal->F9SSRX = temp_ssrx[4];  cal->F9TrackedX = true; }  // [5] is for F10. skip
  if(temp_x[6] > -1000. && temp_a[6] > -1000.){ cal->X11= temp_x[6]; cal->A11= temp_a[6];  cal->F11SSRX= temp_ssrx[6];  cal->F11TrackedX= true; }
  
  if(temp_y[0] > -1000. && temp_b[0] > -1000.){ cal->Y3 = temp_y[0]; cal->B3 = temp_b[0];  cal->F3SSRY = temp_ssry[0];  cal->F3TrackedY = true; }
  if(temp_y[1] > -1000. && temp_b[1] > -1000.){ cal->Y5 = temp_y[1]; cal->B5 = temp_b[1];  cal->F5SSRY = temp_ssry[1];  cal->F5TrackedY = true; }
  if(temp_y[2] > -1000. && temp_b[2] > -1000.){ cal->Y7 = temp_y[2]; cal->B7 = temp_b[2];  cal->F7SSRY = temp_ssry[2];  cal->F7TrackedY = true; }
  if(temp_y[3] > -1000. && temp_b[3] > -1000.){ cal->Y8 = temp_y[3]; cal->B8 = temp_b[3];  cal->F8SSRY = temp_ssry[3];  cal->F8TrackedY = true; }
  if(temp_y[4] > -1000. && temp_b[4] > -1000.){ cal->Y9 = temp_y[4]; cal->B9 = temp_b[4];  cal->F9SSRY = temp_ssry[4];  cal->F9TrackedY = true; }  // [5] is for F10. skip
  if(temp_y[6] > -1000. && temp_b[6] > -1000.){ cal->Y11= temp_y[6]; cal->B11= temp_b[6];  cal->F11SSRY= temp_ssry[6];  cal->F11TrackedY= true; }
  

  //----F8PPAC1-----
  /*
  cal->X8PPAC1 = -9999.;  cal->Y8PPAC1 = -9999.;
  double sum_temp_x8ppac1=0.0;
  int    n_temp_x8ppac1=0;
  double sum_temp_y8ppac1=0.0;
  int    n_temp_y8ppac1=0;
  for(int j=0; j<2; j++){
    if((cal->PPACFiredX[3][j])){  sum_temp_x8ppac1 += cal->PPACX[3][j];   n_temp_x8ppac1++; }
    if((cal->PPACFiredY[3][j])){  sum_temp_y8ppac1 += cal->PPACY[3][j];   n_temp_y8ppac1++; }    
  }
  if(n_temp_x8ppac1>0){
    cal->X8PPAC1 = sum_temp_x8ppac1/((double)n_temp_x8ppac1);
  }
  if(n_temp_y8ppac1>0){
    cal->Y8PPAC1 = sum_temp_y8ppac1/((double)n_temp_y8ppac1);
  }
  */
  
  //-----F3PPAC1 F3PPAC2----------
  cal -> X3PPAC1          = -9999.;
  cal -> X3PPAC2          = -9999.;
  cal -> Y3PPAC1          = -9999.;
  cal -> Y3PPAC2          = -9999.;
  double sum_temp_x3ppac1 = 0.0;
  double sum_temp_x3ppac2 = 0.0;
  double sum_temp_y3ppac1 = 0.0;
  double sum_temp_y3ppac2 = 0.0;
  int    n_temp_x3ppac1   = 0;
  int    n_temp_x3ppac2   = 0;
  int    n_temp_y3ppac1   = 0;
  int    n_temp_y3ppac2   = 0;
  
  for(int j=0; j<2; j++)
  {
    // n_temp will increase if PPAC is fired
    if((cal->PPACFiredX[0][j+0])){  sum_temp_x3ppac1 += cal->PPACX[0][j+0];   n_temp_x3ppac1++; }   // sum of x-position: 1A + 1B
    if((cal->PPACFiredX[0][j+2])){  sum_temp_x3ppac2 += cal->PPACX[0][j+2];   n_temp_x3ppac2++; }   // sum of x-position: 2A + 2B
    if((cal->PPACFiredY[0][j+0])){  sum_temp_y3ppac1 += cal->PPACY[0][j+0];   n_temp_y3ppac1++; }   // sum of y-position: 1A + 1B
    if((cal->PPACFiredY[0][j+2])){  sum_temp_y3ppac2 += cal->PPACY[0][j+2];   n_temp_y3ppac2++; }   // sum of y-position: 2A + 2B
  }
  // Now we are taking an average
  // if n_temp = 2, then equation would be X3PPAC = (X_1A + X_1B)/2
  // if n_temp = 1, means only one plate is fire, say 1A, then the equation would be X3PPAC = X_1A/ 1.0
  if(n_temp_x3ppac1>0){ cal->X3PPAC1 = sum_temp_x3ppac1/((double)n_temp_x3ppac1); }
  if(n_temp_x3ppac2>0){ cal->X3PPAC2 = sum_temp_x3ppac2/((double)n_temp_x3ppac2); }
  if(n_temp_y3ppac1>0){ cal->Y3PPAC1 = sum_temp_y3ppac1/((double)n_temp_y3ppac1); }
  if(n_temp_y3ppac2>0){ cal->Y3PPAC2 = sum_temp_y3ppac2/((double)n_temp_y3ppac2); }

  //-----F5PPAC1 F5PPAC2----------
  cal->X5PPAC1 = -9999.;
  cal->X5PPAC2 = -9999.;
  cal->Y5PPAC1 = -9999.;
  cal->Y5PPAC2 = -9999.;
  double sum_temp_x5ppac1=0.0;
  double sum_temp_x5ppac2=0.0;
  double sum_temp_y5ppac1=0.0;
  double sum_temp_y5ppac2=0.0;
  int    n_temp_x5ppac1=0;
  int    n_temp_x5ppac2=0;
  int    n_temp_y5ppac1=0;
  int    n_temp_y5ppac2=0;
  for(int j=0; j<2; j++){
    if((cal->PPACFiredX[1][j+0])){  sum_temp_x5ppac1 += cal->PPACX[1][j+0];   n_temp_x5ppac1++; }
    if((cal->PPACFiredX[1][j+2])){  sum_temp_x5ppac2 += cal->PPACX[1][j+2];   n_temp_x5ppac2++; }
    if((cal->PPACFiredY[1][j+0])){  sum_temp_y5ppac1 += cal->PPACY[1][j+0];   n_temp_y5ppac1++; }
    if((cal->PPACFiredY[1][j+2])){  sum_temp_y5ppac2 += cal->PPACY[1][j+2];   n_temp_y5ppac2++; }
  }
  if(n_temp_x5ppac1>0){ cal->X5PPAC1 = sum_temp_x5ppac1/((double)n_temp_x5ppac1); }
  if(n_temp_x5ppac2>0){ cal->X5PPAC2 = sum_temp_x5ppac2/((double)n_temp_x5ppac2); }
  if(n_temp_y5ppac1>0){ cal->Y5PPAC1 = sum_temp_y5ppac1/((double)n_temp_y5ppac1); }
  if(n_temp_y5ppac2>0){ cal->Y5PPAC2 = sum_temp_y5ppac2/((double)n_temp_y5ppac2); }
  
  //-----F7PPAC1 F7PPAC2----------
  cal->X7PPAC1 = -9999.;
  cal->X7PPAC2 = -9999.;
  cal->Y7PPAC1 = -9999.;
  cal->Y7PPAC2 = -9999.;
  double sum_temp_x7ppac1=0.0;
  double sum_temp_x7ppac2=0.0;
  double sum_temp_y7ppac1=0.0;
  double sum_temp_y7ppac2=0.0;
  int    n_temp_x7ppac1=0;
  int    n_temp_x7ppac2=0;
  int    n_temp_y7ppac1=0;
  int    n_temp_y7ppac2=0;
  for(int j=0; j<2; j++){
    if((cal->PPACFiredX[2][j+0])){  sum_temp_x7ppac1 += cal->PPACX[2][j+0];   n_temp_x7ppac1++; }
    if((cal->PPACFiredX[2][j+2])){  sum_temp_x7ppac2 += cal->PPACX[2][j+2];   n_temp_x7ppac2++; }
    if((cal->PPACFiredY[2][j+0])){  sum_temp_y7ppac1 += cal->PPACY[2][j+0];   n_temp_y7ppac1++; }
    if((cal->PPACFiredY[2][j+2])){  sum_temp_y7ppac2 += cal->PPACY[2][j+2];   n_temp_y7ppac2++; }
  }
  if(n_temp_x7ppac1>0){ cal->X7PPAC1 = sum_temp_x7ppac1/((double)n_temp_x7ppac1); }
  if(n_temp_x7ppac2>0){ cal->X7PPAC2 = sum_temp_x7ppac2/((double)n_temp_x7ppac2); }
  if(n_temp_y7ppac1>0){ cal->Y7PPAC1 = sum_temp_y7ppac1/((double)n_temp_y7ppac1); }
  if(n_temp_y7ppac2>0){ cal->Y7PPAC2 = sum_temp_y7ppac2/((double)n_temp_y7ppac2); }
  
  //-----F8PPAC1 F8PPAC2----------
  cal->X8PPAC1 = -9999.;
  cal->X8PPAC2 = -9999.;
  cal->Y8PPAC1 = -9999.;
  cal->Y8PPAC2 = -9999.;
  double sum_temp_x8ppac1=0.0;
  double sum_temp_x8ppac2=0.0;
  double sum_temp_y8ppac1=0.0;
  double sum_temp_y8ppac2=0.0;
  int    n_temp_x8ppac1=0;
  int    n_temp_x8ppac2=0;
  int    n_temp_y8ppac1=0;
  int    n_temp_y8ppac2=0;
  for(int j=0; j<2; j++){
    if((cal->PPACFiredX[3][j+0])){  sum_temp_x8ppac1 += cal->PPACX[3][j+0];   n_temp_x8ppac1++; }
    if((cal->PPACFiredX[3][j+2])){  sum_temp_x8ppac2 += cal->PPACX[3][j+2];   n_temp_x8ppac2++; }
    if((cal->PPACFiredY[3][j+0])){  sum_temp_y8ppac1 += cal->PPACY[3][j+0];   n_temp_y8ppac1++; }
    if((cal->PPACFiredY[3][j+2])){  sum_temp_y8ppac2 += cal->PPACY[3][j+2];   n_temp_y8ppac2++; }
  }
  if(n_temp_x8ppac1>0){ cal->X8PPAC1 = sum_temp_x8ppac1/((double)n_temp_x8ppac1); }
  if(n_temp_x8ppac2>0){ cal->X8PPAC2 = sum_temp_x8ppac2/((double)n_temp_x8ppac2); }
  if(n_temp_y8ppac1>0){ cal->Y8PPAC1 = sum_temp_y8ppac1/((double)n_temp_y8ppac1); }
  if(n_temp_y8ppac2>0){ cal->Y8PPAC2 = sum_temp_y8ppac2/((double)n_temp_y8ppac2); }
  

  //-----F9PPAC1 F9PPAC2----------
  cal->X9PPAC1 = -9999.;
  cal->X9PPAC2 = -9999.;
  cal->Y9PPAC1 = -9999.;
  cal->Y9PPAC2 = -9999.;
  double sum_temp_x9ppac1=0.0;
  double sum_temp_x9ppac2=0.0;
  double sum_temp_y9ppac1=0.0;
  double sum_temp_y9ppac2=0.0;
  int    n_temp_x9ppac1=0;
  int    n_temp_x9ppac2=0;
  int    n_temp_y9ppac1=0;
  int    n_temp_y9ppac2=0;
  for(int j=0; j<2; j++){
    if((cal->PPACFiredX[4][j+0])){  sum_temp_x9ppac1 += cal->PPACX[4][j+0];   n_temp_x9ppac1++; }
    if((cal->PPACFiredX[4][j+2])){  sum_temp_x9ppac2 += cal->PPACX[4][j+2];   n_temp_x9ppac2++; }
    if((cal->PPACFiredY[4][j+0])){  sum_temp_y9ppac1 += cal->PPACY[4][j+0];   n_temp_y9ppac1++; }
    if((cal->PPACFiredY[4][j+2])){  sum_temp_y9ppac2 += cal->PPACY[4][j+2];   n_temp_y9ppac2++; }
  }
  if(n_temp_x9ppac1>0){ cal->X9PPAC1 = sum_temp_x9ppac1/((double)n_temp_x9ppac1); }
  if(n_temp_x9ppac2>0){ cal->X9PPAC2 = sum_temp_x9ppac2/((double)n_temp_x9ppac2); }
  if(n_temp_y9ppac1>0){ cal->Y9PPAC1 = sum_temp_y9ppac1/((double)n_temp_y9ppac1); }
  if(n_temp_y9ppac2>0){ cal->Y9PPAC2 = sum_temp_y9ppac2/((double)n_temp_y9ppac2); }

  
  //-----F11PPAC1 F11PPAC2----------
  cal->X11PPAC1 = -9999.;
  cal->X11PPAC2 = -9999.;
  cal->Y11PPAC1 = -9999.;
  cal->Y11PPAC2 = -9999.;
  double sum_temp_x11ppac1=0.0;
  double sum_temp_x11ppac2=0.0;
  double sum_temp_y11ppac1=0.0;
  double sum_temp_y11ppac2=0.0;
  int    n_temp_x11ppac1=0;
  int    n_temp_x11ppac2=0;
  int    n_temp_y11ppac1=0;
  int    n_temp_y11ppac2=0;
  for(int j=0; j<2; j++){
    if((cal->PPACFiredX[6][j+0])){  sum_temp_x11ppac1 += cal->PPACX[6][j+0];   n_temp_x11ppac1++; }
    if((cal->PPACFiredX[6][j+2])){  sum_temp_x11ppac2 += cal->PPACX[6][j+2];   n_temp_x11ppac2++; }
    if((cal->PPACFiredY[6][j+0])){  sum_temp_y11ppac1 += cal->PPACY[6][j+0];   n_temp_y11ppac1++; }
    if((cal->PPACFiredY[6][j+2])){  sum_temp_y11ppac2 += cal->PPACY[6][j+2];   n_temp_y11ppac2++; }
  }
  if(n_temp_x11ppac1>0){ cal->X11PPAC1 = sum_temp_x11ppac1/((double)n_temp_x11ppac1); }
  if(n_temp_x11ppac2>0){ cal->X11PPAC2 = sum_temp_x11ppac2/((double)n_temp_x11ppac2); }
  if(n_temp_y11ppac1>0){ cal->Y11PPAC1 = sum_temp_y11ppac1/((double)n_temp_y11ppac1); }
  if(n_temp_y11ppac2>0){ cal->Y11PPAC2 = sum_temp_y11ppac2/((double)n_temp_y11ppac2); }

  
  
  //-----Plastic-----
  cal->F3PLA_QL   = raw->F3PLA_QL_raw   - (para->plaqdc_pedestal[0][0]); //tdc channel to time in ns
  cal->F3PLA_QR   = raw->F3PLA_QR_raw   - (para->plaqdc_pedestal[0][1]);
  cal->F5PLA_QL   = raw->F5PLA_QL_raw   - (para->plaqdc_pedestal[1][0]);
  cal->F5PLA_QR   = raw->F5PLA_QR_raw   - (para->plaqdc_pedestal[1][1]);
  cal->F7PLA_QL   = raw->F7PLA_QL_raw   - (para->plaqdc_pedestal[2][0]);
  cal->F7PLA_QR   = raw->F7PLA_QR_raw   - (para->plaqdc_pedestal[2][1]);
  cal->F8PLA_QL   = raw->F8PLA_QL_raw   - (para->plaqdc_pedestal[3][0]);
  cal->F8PLA_QR   = raw->F8PLA_QR_raw   - (para->plaqdc_pedestal[3][1]);
  cal->F11PLA_QL  = raw->F11PLA_QL_raw  - (para->plaqdc_pedestal[4][0]);
  cal->F11PLA_QR  = raw->F11PLA_QR_raw  - (para->plaqdc_pedestal[4][1]);
  cal->F11LONG_QL = raw->F11LONG_QL_raw - (para->plaqdc_pedestal[5][0]);
  cal->F11LONG_QR = raw->F11LONG_QR_raw - (para->plaqdc_pedestal[5][1]);
  cal->F11VETO_QL = raw->F11VETO_QL_raw - (para->plaqdc_pedestal[6][0]);
  cal->F11VETO_QR = raw->F11VETO_QR_raw - (para->plaqdc_pedestal[6][1]);
  
  cal->F3PLA_Q   = TMath::Sqrt(std::max(cal->F3PLA_QL,0.0)   * std::max(cal->F3PLA_QR,0.0));
  cal->F5PLA_Q   = TMath::Sqrt(std::max(cal->F5PLA_QL,0.0)   * std::max(cal->F5PLA_QR,0.0));
  cal->F7PLA_Q   = TMath::Sqrt(std::max(cal->F7PLA_QL,0.0)   * std::max(cal->F7PLA_QR,0.0));
  cal->F8PLA_Q   = TMath::Sqrt(std::max(cal->F8PLA_QL,0.0)   * std::max(cal->F8PLA_QR,0.0));
  cal->F11PLA_Q  = TMath::Sqrt(std::max(cal->F11PLA_QL,0.0)  * std::max(cal->F11PLA_QR,0.0));
  cal->F11LONG_Q = TMath::Sqrt(std::max(cal->F11LONG_QL,0.0) * std::max(cal->F11LONG_QR,0.0));
  cal->F11VETO_Q = TMath::Sqrt(std::max(cal->F11VETO_QL,0.0) * std::max(cal->F11VETO_QR,0.0));

  cal->F3PLA_TL_ns   = raw->F3PLA_TL_raw_s   * (para->platdcb3f_ch2ns); //tdc channel to time in ns
  cal->F3PLA_TR_ns   = raw->F3PLA_TR_raw_s   * (para->platdcb3f_ch2ns);
  cal->F5PLA_TL_ns   = raw->F5PLA_TL_raw_s   * (para->platdcb3f_ch2ns);
  cal->F5PLA_TR_ns   = raw->F5PLA_TR_raw_s   * (para->platdcb3f_ch2ns);
  cal->F7PLA_TL_ns   = raw->F7PLA_TL_raw_s   * (para->platdcb3f_ch2ns);
  cal->F7PLA_TR_ns   = raw->F7PLA_TR_raw_s   * (para->platdcb3f_ch2ns);
  cal->F8PLA_TL_ns   = raw->F8PLA_TL_raw_s   * (para->platdcb3f_ch2ns);
  cal->F8PLA_TR_ns   = raw->F8PLA_TR_raw_s   * (para->platdcb3f_ch2ns);
  cal->F11PLA_TL_ns  = raw->F11PLA_TL_raw_s  * (para->platdcb3f_ch2ns);
  cal->F11PLA_TR_ns  = raw->F11PLA_TR_raw_s  * (para->platdcb3f_ch2ns);
  cal->F11LONG_TL_ns = raw->F11LONG_TL_raw_s * (para->platdcb3f_ch2ns);
  cal->F11LONG_TR_ns = raw->F11LONG_TR_raw_s * (para->platdcb3f_ch2ns);
  cal->F11VETO_TL_ns = raw->F11VETO_TL_raw_s * (para->platdcb3f_ch2ns);
  cal->F11VETO_TR_ns = raw->F11VETO_TR_raw_s * (para->platdcb3f_ch2ns);
  
  cal->F3PLA_TL   =  cal->F3PLA_TL_ns   + (para->pla_twcoeff[0][0][0])/TMath::Sqrt(cal->F3PLA_QL) + (para->pla_twcoeff[0][0][1]); //time walk correction
  cal->F3PLA_TR   =  cal->F3PLA_TR_ns   + (para->pla_twcoeff[0][1][0])/TMath::Sqrt(cal->F3PLA_QR) + (para->pla_twcoeff[0][1][1]);
  cal->F5PLA_TL   =  cal->F5PLA_TL_ns   + (para->pla_twcoeff[1][0][0])/TMath::Sqrt(cal->F5PLA_QL) + (para->pla_twcoeff[1][0][1]);
  cal->F5PLA_TR   =  cal->F5PLA_TR_ns   + (para->pla_twcoeff[1][1][0])/TMath::Sqrt(cal->F5PLA_QR) + (para->pla_twcoeff[1][1][1]);
  cal->F7PLA_TL   =  cal->F7PLA_TL_ns   + (para->pla_twcoeff[2][0][0])/TMath::Sqrt(cal->F7PLA_QL) + (para->pla_twcoeff[2][0][1]);
  cal->F7PLA_TR   =  cal->F7PLA_TR_ns   + (para->pla_twcoeff[2][1][0])/TMath::Sqrt(cal->F7PLA_QR) + (para->pla_twcoeff[2][1][1]);
  cal->F8PLA_TL   =  cal->F8PLA_TL_ns   + (para->pla_twcoeff[3][0][0])/TMath::Sqrt(cal->F5PLA_QL) + (para->pla_twcoeff[3][0][1]);
  cal->F8PLA_TR   =  cal->F8PLA_TR_ns   + (para->pla_twcoeff[3][1][0])/TMath::Sqrt(cal->F5PLA_QR) + (para->pla_twcoeff[3][1][1]);
  cal->F11PLA_TL  =  cal->F11PLA_TL_ns  + (para->pla_twcoeff[4][0][0])/TMath::Sqrt(cal->F7PLA_QL) + (para->pla_twcoeff[4][0][1]);
  cal->F11PLA_TR  =  cal->F11PLA_TR_ns  + (para->pla_twcoeff[4][1][0])/TMath::Sqrt(cal->F7PLA_QR) + (para->pla_twcoeff[4][1][1]);
  cal->F11LONG_TL =  cal->F11LONG_TL_ns + (para->pla_twcoeff[5][0][0])/TMath::Sqrt(cal->F5PLA_QL) + (para->pla_twcoeff[5][0][1]);
  cal->F11LONG_TR =  cal->F11LONG_TR_ns + (para->pla_twcoeff[5][1][0])/TMath::Sqrt(cal->F5PLA_QR) + (para->pla_twcoeff[5][1][1]);
  cal->F11VETO_TL =  cal->F11VETO_TL_ns + (para->pla_twcoeff[6][0][0])/TMath::Sqrt(cal->F7PLA_QL) + (para->pla_twcoeff[6][0][1]);
  cal->F11VETO_TR =  cal->F11VETO_TR_ns + (para->pla_twcoeff[6][1][0])/TMath::Sqrt(cal->F7PLA_QR) + (para->pla_twcoeff[6][1][1]);
  
  cal->F3PLA_T   = 0.5*(cal->F3PLA_TL  +  cal->F3PLA_TR); // average left+right
  cal->F5PLA_T   = 0.5*(cal->F5PLA_TL  +  cal->F5PLA_TR);
  cal->F7PLA_T   = 0.5*(cal->F7PLA_TL  +  cal->F7PLA_TR);
  cal->F8PLA_T   = 0.5*(cal->F8PLA_TL  +  cal->F8PLA_TR);
  cal->F11PLA_T  = 0.5*(cal->F11PLA_TL +  cal->F11PLA_TR);
  cal->F11LONG_T = 0.5*(cal->F11LONG_TL+  cal->F11LONG_TR);
  cal->F11VETO_T = 0.5*(cal->F11VETO_TL+  cal->F11VETO_TR);
  
  //----missing in original calib.cc. added on 4th Dec. 2017 in calib_with_dali
  cal->F3PLA_TL_NumHit  = raw->F3PLA_TL_NumHit;  cal->F3PLA_TR_NumHit = raw->F3PLA_TR_NumHit;
  cal->F5PLA_TL_NumHit  = raw->F5PLA_TL_NumHit;  cal->F5PLA_TR_NumHit = raw->F5PLA_TR_NumHit;
  cal->F7PLA_TL_NumHit  = raw->F7PLA_TL_NumHit;  cal->F7PLA_TR_NumHit = raw->F7PLA_TR_NumHit;
  cal->F8PLA_TL_NumHit  = raw->F8PLA_TL_NumHit;  cal->F8PLA_TR_NumHit = raw->F8PLA_TR_NumHit;
  cal->F11PLA_TL_NumHit = raw->F11PLA_TL_NumHit; cal->F11PLA_TR_NumHit= raw->F11PLA_TR_NumHit;
  cal->F11LONG_TL_NumHit = raw->F11LONG_TL_NumHit; cal->F11LONG_TR_NumHit= raw->F11LONG_TR_NumHit;
  cal->F11VETO_TL_NumHit = raw->F11VETO_TL_NumHit; cal->F11VETO_TR_NumHit= raw->F11VETO_TR_NumHit;
  //------

  cal->F3PLA_QL_raw   = raw->F3PLA_QL_raw; // also copy raw
  cal->F3PLA_QR_raw   = raw->F3PLA_QR_raw;
  cal->F5PLA_QL_raw   = raw->F5PLA_QL_raw;
  cal->F5PLA_QR_raw   = raw->F5PLA_QR_raw;
  cal->F7PLA_QL_raw   = raw->F7PLA_QL_raw;
  cal->F7PLA_QR_raw   = raw->F7PLA_QR_raw;
  cal->F8PLA_QL_raw   = raw->F8PLA_QL_raw;
  cal->F8PLA_QR_raw   = raw->F8PLA_QR_raw;
  cal->F11PLA_QL_raw  = raw->F11PLA_QL_raw;
  cal->F11PLA_QR_raw  = raw->F11PLA_QR_raw;
  cal->F11LONG_QL_raw = raw->F11LONG_QL_raw;
  cal->F11LONG_QR_raw = raw->F11LONG_QR_raw;
  cal->F11VETO_QL_raw = raw->F11VETO_QL_raw;
  cal->F11VETO_QR_raw = raw->F11VETO_QR_raw;

  cal->F3PLA_TL_raw   = raw->F3PLA_TL_raw; // also copy raw
  cal->F3PLA_TR_raw   = raw->F3PLA_TR_raw;
  cal->F5PLA_TL_raw   = raw->F5PLA_TL_raw;
  cal->F5PLA_TR_raw   = raw->F5PLA_TR_raw;
  cal->F7PLA_TL_raw   = raw->F7PLA_TL_raw;
  cal->F7PLA_TR_raw   = raw->F7PLA_TR_raw;
  cal->F8PLA_TL_raw   = raw->F8PLA_TL_raw;
  cal->F8PLA_TR_raw   = raw->F8PLA_TR_raw;
  cal->F11PLA_TL_raw  = raw->F11PLA_TL_raw;
  cal->F11PLA_TR_raw  = raw->F11PLA_TR_raw;
  cal->F11LONG_TL_raw = raw->F11LONG_TL_raw;
  cal->F11LONG_TR_raw = raw->F11LONG_TR_raw;
  cal->F11VETO_TL_raw = raw->F11VETO_TL_raw;
  cal->F11VETO_TR_raw = raw->F11VETO_TR_raw;

  cal->F3PLA_TL_raw_s   = raw->F3PLA_TL_raw_s; // also copy raw
  cal->F3PLA_TR_raw_s   = raw->F3PLA_TR_raw_s;
  cal->F5PLA_TL_raw_s   = raw->F5PLA_TL_raw_s;
  cal->F5PLA_TR_raw_s   = raw->F5PLA_TR_raw_s;
  cal->F7PLA_TL_raw_s   = raw->F7PLA_TL_raw_s;
  cal->F7PLA_TR_raw_s   = raw->F7PLA_TR_raw_s;
  cal->F8PLA_TL_raw_s   = raw->F8PLA_TL_raw_s;
  cal->F8PLA_TR_raw_s   = raw->F8PLA_TR_raw_s;
  cal->F11PLA_TL_raw_s  = raw->F11PLA_TL_raw_s;
  cal->F11PLA_TR_raw_s  = raw->F11PLA_TR_raw_s;
  cal->F11LONG_TL_raw_s = raw->F11LONG_TL_raw_s;
  cal->F11LONG_TR_raw_s = raw->F11LONG_TR_raw_s;
  cal->F11VETO_TL_raw_s = raw->F11VETO_TL_raw_s;
  cal->F11VETO_TR_raw_s = raw->F11VETO_TR_raw_s;


  //-----IC------
  
  //----F7 IC-----
  cal->F7ICADCcal[0]   = (raw->F7ICADCraw[0] - para->f7icadc_pedestal[0]) * para->f7icadc_gain[0];
  cal->F7ICADCcal[1]   = (raw->F7ICADCraw[1] - para->f7icadc_pedestal[1]) * para->f7icadc_gain[1];
  cal->F7ICADCcal[2]   = (raw->F7ICADCraw[2] - para->f7icadc_pedestal[2]) * para->f7icadc_gain[2];
  cal->F7ICADCcal[3]   = (raw->F7ICADCraw[3] - para->f7icadc_pedestal[3]) * para->f7icadc_gain[3];
  cal->F7ICADCcal[4]   = (raw->F7ICADCraw[4] - para->f7icadc_pedestal[4]) * para->f7icadc_gain[4];
  cal->F7ICADCcal[5]   = (raw->F7ICADCraw[5] - para->f7icadc_pedestal[5]) * para->f7icadc_gain[5];
  
  cal->F7ICADCraw[0]   = raw->F7ICADCraw[0]; //also copy raw
  cal->F7ICADCraw[1]   = raw->F7ICADCraw[1];
  cal->F7ICADCraw[2]   = raw->F7ICADCraw[2];
  cal->F7ICADCraw[3]   = raw->F7ICADCraw[3];
  cal->F7ICADCraw[4]   = raw->F7ICADCraw[4];
  cal->F7ICADCraw[5]   = raw->F7ICADCraw[5];

  cal->F7ICEnergySqSum_online = raw->F7ICEnergySqSum;
  cal->F7ICEnergyAvSum_online = raw->F7ICEnergyAvSum;

  
  cal->F7ICEnergySqSum_offline =-999.9;//initial value
  cal->F7ICEnergyAvSum_offline =-999.9;//initial value
  
  int f7anodefired = 0;
  Double_t f7_anodes_multiplied=1;
  Double_t f7_anodes_summed = 0;
  
  for (int i=0;i<6;i++){
   if(cal->F7ICADCcal[i]>0){
     f7_anodes_multiplied *= cal->F7ICADCcal[i];
     f7_anodes_summed += cal->F7ICADCcal[i];
     f7anodefired++;
   }
  }

  if (f7_anodes_summed>0 && f7_anodes_multiplied>0 && f7anodefired>0) {
      Float_t power_value = 1.0/f7anodefired;
      cal->F7ICEnergySqSum_offline = TMath::Power(f7_anodes_multiplied,power_value);
      cal->F7ICEnergyAvSum_offline = (f7_anodes_summed/f7anodefired);     
  }


  //----- F11 IC1 ----
  cal->F11IC1ADCcal[0]   = (raw->F11IC1ADCraw[0] - para->f11icadc_pedestal[0][0]) * para->f11icadc_gain[0][0];
  cal->F11IC1ADCcal[1]   = (raw->F11IC1ADCraw[1] - para->f11icadc_pedestal[0][1]) * para->f11icadc_gain[0][1];
  cal->F11IC1ADCcal[2]   = (raw->F11IC1ADCraw[2] - para->f11icadc_pedestal[0][2]) * para->f11icadc_gain[0][2];
  cal->F11IC1ADCcal[3]   = (raw->F11IC1ADCraw[3] - para->f11icadc_pedestal[0][3]) * para->f11icadc_gain[0][3];
  cal->F11IC1ADCcal[4]   = (raw->F11IC1ADCraw[4] - para->f11icadc_pedestal[0][4]) * para->f11icadc_gain[0][4];
  cal->F11IC1ADCcal[5]   = (raw->F11IC1ADCraw[5] - para->f11icadc_pedestal[0][5]) * para->f11icadc_gain[0][5];
  cal->F11IC1ADCcal[6]   = (raw->F11IC1ADCraw[6] - para->f11icadc_pedestal[0][6]) * para->f11icadc_gain[0][6];
  cal->F11IC1ADCcal[7]   = (raw->F11IC1ADCraw[7] - para->f11icadc_pedestal[0][7]) * para->f11icadc_gain[0][7];
  
  cal->F11IC1ADCraw[0]   = raw->F11IC1ADCraw[0]; //also copy raw
  cal->F11IC1ADCraw[1]   = raw->F11IC1ADCraw[1];
  cal->F11IC1ADCraw[2]   = raw->F11IC1ADCraw[2];
  cal->F11IC1ADCraw[3]   = raw->F11IC1ADCraw[3];
  cal->F11IC1ADCraw[4]   = raw->F11IC1ADCraw[4];
  cal->F11IC1ADCraw[5]   = raw->F11IC1ADCraw[5];
  cal->F11IC1ADCraw[6]   = raw->F11IC1ADCraw[6];
  cal->F11IC1ADCraw[7]   = raw->F11IC1ADCraw[7];

  cal->F11IC1EnergySqSum_online = raw->F11IC1EnergySqSum;
  cal->F11IC1EnergyAvSum_online = raw->F11IC1EnergyAvSum;
  
  
  cal->F11IC1EnergySqSum_offline =-999.9;//initial value
  cal->F11IC1EnergyAvSum_offline =-999.9;//initial value
  
  int f11IC1anodefired = 0;
  Double_t f11IC1_anodes_multiplied=1;
  Double_t f11IC1_anodes_summed = 0;
  
  for (int i=0;i<8;i++){
   if(cal->F11IC1ADCcal[i]>0){
     f11IC1_anodes_multiplied *= cal->F11IC1ADCcal[i];
     f11IC1_anodes_summed += cal->F11IC1ADCcal[i];
     f11IC1anodefired++;
   }
  }

  if (f11IC1_anodes_summed>0 && f11IC1_anodes_multiplied>0 && f11IC1anodefired>0) {
      Float_t power_value = 1.0/f11IC1anodefired;
      cal->F11IC1EnergySqSum_offline = TMath::Power(f11IC1_anodes_multiplied,power_value);
      cal->F11IC1EnergyAvSum_offline = (f11IC1_anodes_summed/f11IC1anodefired);     
  }


  //----- F11 IC2 ----
  cal->F11IC2ADCcal[0]   = (raw->F11IC2ADCraw[0] - para->f11icadc_pedestal[1][0]) * para->f11icadc_gain[1][0];
  cal->F11IC2ADCcal[1]   = (raw->F11IC2ADCraw[1] - para->f11icadc_pedestal[1][1]) * para->f11icadc_gain[1][1];
  cal->F11IC2ADCcal[2]   = (raw->F11IC2ADCraw[2] - para->f11icadc_pedestal[1][2]) * para->f11icadc_gain[1][2];
  cal->F11IC2ADCcal[3]   = (raw->F11IC2ADCraw[3] - para->f11icadc_pedestal[1][3]) * para->f11icadc_gain[1][3];
  cal->F11IC2ADCcal[4]   = (raw->F11IC2ADCraw[4] - para->f11icadc_pedestal[1][4]) * para->f11icadc_gain[1][4];
  cal->F11IC2ADCcal[5]   = (raw->F11IC2ADCraw[5] - para->f11icadc_pedestal[1][5]) * para->f11icadc_gain[1][5];
  cal->F11IC2ADCcal[6]   = (raw->F11IC2ADCraw[6] - para->f11icadc_pedestal[1][6]) * para->f11icadc_gain[1][6];
  cal->F11IC2ADCcal[7]   = (raw->F11IC2ADCraw[7] - para->f11icadc_pedestal[1][7]) * para->f11icadc_gain[1][7];

  cal->F11IC2ADCraw[0]   = raw->F11IC2ADCraw[0]; //also copy raw
  cal->F11IC2ADCraw[1]   = raw->F11IC2ADCraw[1];
  cal->F11IC2ADCraw[2]   = raw->F11IC2ADCraw[2];
  cal->F11IC2ADCraw[3]   = raw->F11IC2ADCraw[3];
  cal->F11IC2ADCraw[4]   = raw->F11IC2ADCraw[4];
  cal->F11IC2ADCraw[5]   = raw->F11IC2ADCraw[5];
  cal->F11IC2ADCraw[6]   = raw->F11IC2ADCraw[6];
  cal->F11IC2ADCraw[7]   = raw->F11IC2ADCraw[7];

  cal->F11IC2EnergySqSum_online = raw->F11IC2EnergySqSum; 
  cal->F11IC2EnergyAvSum_online = raw->F11IC2EnergyAvSum;

  cal->F11IC2EnergySqSum_offline =-999.9;//initial value
  cal->F11IC2EnergyAvSum_offline =-999.9;//initial value
  
  int f11IC2anodefired = 0;
  Double_t f11IC2_anodes_multiplied=1;
  Double_t f11IC2_anodes_summed = 0;
  
  for (int i=0;i<8;i++){
   if(cal->F11IC2ADCcal[i]>0){
     f11IC2_anodes_multiplied *= cal->F11IC2ADCcal[i];
     f11IC2_anodes_summed += cal->F11IC2ADCcal[i];
     f11IC2anodefired++;
   }
  }

  if (f11IC2_anodes_summed>0 && f11IC2_anodes_multiplied>0 && f11IC2anodefired>0) {
      Float_t power_value = 1.0/f11IC2anodefired;
      cal->F11IC2EnergySqSum_offline = TMath::Power(f11IC2_anodes_multiplied,power_value);
      cal->F11IC2EnergyAvSum_offline = (f11IC2_anodes_summed/f11IC2anodefired);     
  }
  
  
  //----for drift time analysis, init ---
  for(int ii=0; ii<8; ii++){
    cal->F11IC1Yanode[ii] = -9999.;
    cal->F11IC2Yanode[ii] = -9999.;
  }
  cal->F11YIC1 = -9999.;
  cal->F11BIC1 = -9999.;
  cal->F11YIC2 = -9999.;
  cal->F11BIC2 = -9999.;
  
  //---- calculate each anode position ---
  for(int ii=0; ii<8; ii++){
    double tdc_ic1_anode = raw->F11IC1TDCraw[ii];
    double tdc_ic2_anode = raw->F11IC2TDCraw[ii];
    double tdc_reference = raw->F11TDC_F11PLA_TR_raw;
    if(20000<tdc_reference && tdc_reference<60000 && 20000<tdc_ic1_anode && tdc_ic1_anode<160000){
      cal->F11IC1Yanode[ii] =  (para->f11ictdc_factor[0][ii])*(tdc_ic1_anode - tdc_reference) + (para->f11ictdc_offset[0][ii]);
    }
    if(20000<tdc_reference && tdc_reference<60000 && 20000<tdc_ic2_anode && tdc_ic2_anode<160000){
      cal->F11IC2Yanode[ii] =  (para->f11ictdc_factor[1][ii])*(tdc_ic2_anode - tdc_reference) + (para->f11ictdc_offset[1][ii]);
    }
  }
  
  //---tracking for music1---
  TMatrixD ic1_yvector(2,1); ic1_yvector.Zero();
  TMatrixD ic1_ymatrix(2,2); ic1_ymatrix.Zero();
  TMatrixD ic1_yvector_solution(2,1); ic1_yvector_solution.Zero();
  int ic1_n_anode_tdc = 0;
  for( int i_anode=0; i_anode<8; i_anode++){
    double z_here = (para->f11iczposF11ref[0][i_anode]);
    double y_here = cal->F11IC1Yanode[i_anode];
    if( y_here > -200.0 ){ //not initial value of -9999
      ic1_yvector(0,0) += y_here;
      ic1_yvector(1,0) += y_here * z_here;
      ic1_ymatrix(0,0) += 1.0;    ic1_ymatrix(0,1) += z_here;
      ic1_ymatrix(1,0) += z_here; ic1_ymatrix(1,1) += z_here*z_here;
      ic1_n_anode_tdc ++;
    }
  }
  if(ic1_n_anode_tdc >=2){
    ic1_yvector_solution = ic1_ymatrix.Invert()  * ic1_yvector ;
    cal->F11YIC1  = ic1_yvector_solution(0,0);
    cal->F11BIC1  = 1000.*TMath::ATan(ic1_yvector_solution(1,0));
  }
  
  
  //---tracking for music2---
  TMatrixD ic2_yvector(2,1); ic2_yvector.Zero();
  TMatrixD ic2_ymatrix(2,2); ic2_ymatrix.Zero();
  TMatrixD ic2_yvector_solution(2,1); ic2_yvector_solution.Zero();
  int ic2_n_anode_tdc = 0;
  for( int i_anode=0; i_anode<8; i_anode++){
    double z_here = (para->f11iczposF11ref[1][i_anode]);
    double y_here = cal->F11IC2Yanode[i_anode];
    if( y_here > -200.0 ){ //not initial value of -9999
      ic2_yvector(0,0) += y_here;
      ic2_yvector(1,0) += y_here * z_here;
      ic2_ymatrix(0,0) += 1.0;    ic2_ymatrix(0,1) += z_here;
      ic2_ymatrix(1,0) += z_here; ic2_ymatrix(1,1) += z_here*z_here;
      ic2_n_anode_tdc ++;
    }
  }
  if(ic2_n_anode_tdc >=2){
    ic2_yvector_solution = ic2_ymatrix.Invert()  * ic2_yvector ;
    cal->F11YIC2  = ic2_yvector_solution(0,0);
    cal->F11BIC2  = 1000.*TMath::ATan(ic2_yvector_solution(1,0));
  }

  
  // copy from online reconstructed data
  for(int ii=0; ii<3; ii++){
    cal->tof_online[ii]  = raw->tof[ii];
    cal->beta_online[ii] = raw->beta[ii];
  }
  for(int ii=0; ii<4; ii++){
    cal->delta_online[ii]  = raw->delta[ii];
  }
  for(int ii=0; ii<6; ii++){
    cal->aoq_online[ii]  = raw->aoqc[ii]; // to avoid incomplete events
    cal->zet_online[ii]  = raw->zetc[ii]; //
  }
  
  
  
  ///-------------------------------------
  /// TOF Beta analysis
  
  cal->tof37 = -999.9;
  cal->tof811 = -999.9;
  cal->beta37 = -999.9;
  cal->beta811 = -999.9;
  cal->beta35_dipoleratio  = -999.9;
  cal->beta57_dipoleratio  = -999.9;
  cal->btof37  = false;
  cal->btof811 = false;

  for(int i=0; i<8; i++){ cal->dipolebrho[i]  =  raw->dipolebrho[i]; }
  
  if((cal->F3PLA_T)>0.0 && (cal->F7PLA_T)>0.0){ // from data, real hit must satisfy at least FXPLA_T > 0.0
    cal->btof37 = true;
    cal->tof37  = (cal->F7PLA_T) - (cal->F3PLA_T) + (para->offset37_default);
    cal->beta37 = (para->length37)/(cal->tof37)/(para->clight);
    double temp_ratio =  (cal->dipolebrho[2]) / (cal->dipolebrho[4]); // D3/D5
    
    //double temp_cta = ((para->length37)*(para->clight))/cal->beta37/(para->clight); //changed to test whether beta37 gives the right beta57_dipoleratio (29.08.2018)
    double temp_cta = (cal->tof37) * (para->clight);
    
    double temp_l1  = (para->length35);
    double temp_l2  = (para->length57);

    double par_a = (temp_l1*temp_l1)*(1.0 - 1./(temp_ratio*temp_ratio)) - temp_cta*temp_cta ;
    double par_b = 2.0 * temp_cta * temp_l2;
    double par_c = temp_l1*temp_l1/(temp_ratio*temp_ratio) - temp_l2*temp_l2;
    double beta2_sol1 = (-1.0*par_b + TMath::Sqrt(par_b*par_b - 4.0*par_a*par_c))/(2.0 * par_a) ;
    double beta2_sol2 = (-1.0*par_b - TMath::Sqrt(par_b*par_b - 4.0*par_a*par_c))/(2.0 * par_a) ;
    double beta1_sol1 = temp_l1 / (temp_cta - (temp_l2/beta2_sol1));
    double beta1_sol2 = temp_l1 / (temp_cta - (temp_l2/beta2_sol2));

    //    printf("sol1(beta1,beta2) = %.3f, %.3f\n",beta1_sol1,beta2_sol1);
    //    printf("sol2(beta1,beta2) = %.3f, %.3f\n",beta1_sol2,beta2_sol2);
    // sol2 seems to be correct by checking data. sol1 is negative...
    cal->beta35_dipoleratio = beta1_sol2;
    cal->beta57_dipoleratio = beta2_sol2;
  }
  
  if((cal->F8PLA_T)>0.0 && (cal->F11PLA_T)>0.0){ // from data, real hit must satisfy at least FXPLA_T > 0.0
    cal->btof811 = true;
    cal->tof811  = (cal->F11PLA_T) - (cal->F8PLA_T) + (para->offset811_default);
    cal->beta811 = (para->length811)/(cal->tof811)/(para->clight);
  }
  
  // TOF78 mainly for DALI doppler correction
  cal->tof78 = -999.9;
  cal->beta78 = -999.9;
  cal->btof78 = false;
  if((cal->F8PLA_T)>0.0 && (cal->F7PLA_T)>0.0){ // from data, real hit must satisfy at least FXPLA_T > 0.0
    cal->btof78 = true;
    cal->tof78  = (cal->F8PLA_T) - (cal->F7PLA_T) + (para->offset78_default);
    cal->beta78 = (para->length78)/(cal->tof78)/(para->clight);
  }
  
  
  ///-------------------------------------
  /// Delta (optics) analysis

  cal->delta35  = -999.9;
  cal->delta57  = -999.9;
  cal->delta911 = -999.9;
  cal->bdelta35  = false;
  cal->bdelta57  = false;
  cal->bdelta911 = false;

  if( (cal->F5TrackedX) &&  (cal->F3TrackedX) ){
    cal->bdelta35  = true;
    cal->delta35  = f_delta35(cal->X5, cal->A5, cal->X3, cal->A3);//first dispersive, next achromatic
  }
  if( (cal->F5TrackedX) &&  (cal->F7TrackedX) ){
    cal->bdelta57  = true;
    cal->delta57  = f_delta57(cal->X5, cal->A5, cal->X7, cal->A7);//first dispersive, next achromatic
  }
  if( (cal->F9TrackedX) &&  (cal->F11TrackedX) ){
    cal->bdelta911  = true;
    cal->delta911  = f_delta911(cal->X9, cal->A9, cal->X11, cal->A11);//first dispersive, next achromatic
  }
  
  
  ///------------------------------------------
  /// extended optics analysis (for delta 35)
  
  cal->delta35_1110  = -999.9;
  cal->delta35_1101  = -999.9;
  cal->delta35_1011  = -999.9;
  cal->delta35_0111  = -999.9;
  cal->delta35_ext   = -999.9;
  cal->bdelta35_1110  = false;
  cal->bdelta35_1101  = false;
  cal->bdelta35_1011  = false;
  cal->bdelta35_0111  = false;
  cal->bdelta35_3plane= false;
  cal->bdelta35_ext   = false;
  
  if( (cal->F3TrackedX)  &&  fabs(cal->X5PPAC1)<1000.0 ){ //1110
    cal->delta35_1110  =  corrected_delta35_1110(cal->X5PPAC1, cal->A3, cal->X3);//(double xdisp, double angle, double xachr)
    cal->bdelta35_1110  = true;
  }
  if( (cal->F3TrackedX)  &&  fabs(cal->X5PPAC2)<1000.0){ //1101
    cal->delta35_1101  =  corrected_delta35_1101(cal->X5PPAC2, cal->A3, cal->X3);/////////////
    cal->bdelta35_1101  = true;
  }
  if( fabs(cal->X3PPAC1)<1000.0 && (cal->F5TrackedX) ){ //1011
    cal->delta35_1011  =  corrected_delta35_1011(cal->X5, cal->A5, cal->X3PPAC1);/////////////
    cal->bdelta35_1011  = true;
  }
  if( fabs(cal->X3PPAC2)<1000.0 && (cal->F5TrackedX)  ){ //0111
    cal->delta35_0111  =  corrected_delta35_0111(cal->X5, cal->A5, cal->X3PPAC2);/////////////
    cal->bdelta35_0111  = true;
  }
  cal->bdelta35_3plane = ( (cal->bdelta35_1110) || (cal->bdelta35_1101) || (cal->bdelta35_1011) || (cal->bdelta35_0111));
  
  if( cal->bdelta35 ){
    cal->bdelta35_ext  = true;
    cal->delta35_ext   = cal->delta35 ;
  }else if( cal->bdelta35_3plane ){
    if(cal->bdelta35_1110){  cal->delta35_ext = cal->delta35_1110;  cal->bdelta35_ext  = true; }
    if(cal->bdelta35_1101){  cal->delta35_ext = cal->delta35_1101;  cal->bdelta35_ext  = true; }
    if(cal->bdelta35_1011){  cal->delta35_ext = cal->delta35_1011;  cal->bdelta35_ext  = true; }
    if(cal->bdelta35_0111){  cal->delta35_ext = cal->delta35_0111;  cal->bdelta35_ext  = true; }
  }
  
  ///------------------------------------------
  /// extended optics analysis (for delta 57)

  cal->delta57_1110  = -999.9;
  cal->delta57_1101  = -999.9;
  cal->delta57_1011  = -999.9;
  cal->delta57_0111  = -999.9;
  cal->delta57_ext   = -999.9;
  cal->bdelta57_1110  = false;
  cal->bdelta57_1101  = false;
  cal->bdelta57_1011  = false;
  cal->bdelta57_0111  = false;
  cal->bdelta57_3plane= false;
  cal->bdelta57_ext   = false;

  if( (cal->F5TrackedX)  &&  fabs(cal->X7PPAC1)<1000.0 ){ //1110
     cal->delta57_1110  =  corrected_delta57_1110(cal->X5, cal->A5, cal->X7PPAC1);//(double xdisp, double angle, double xachr)
    cal->bdelta57_1110  = true;
  }
  if( (cal->F5TrackedX)  &&  fabs(cal->X7PPAC2)<1000.0){ //1101
     cal->delta57_1101  =  corrected_delta57_1101(cal->X5, cal->A5, cal->X7PPAC2);/////////////
    cal->bdelta57_1101  = true;
  }
  if( fabs(cal->X5PPAC1)<1000.0 && (cal->F7TrackedX) ){ //1011
     cal->delta57_1011  =  corrected_delta57_1011(cal->X5PPAC1, cal->A7, cal->X7);/////////////
    cal->bdelta57_1011  = true;
  }
  if( fabs(cal->X5PPAC2)<1000.0 && (cal->F7TrackedX)  ){ //0111
     cal->delta57_0111  =  corrected_delta57_0111(cal->X5PPAC2, cal->A7, cal->X7);/////////////
    cal->bdelta57_0111  = true;
  }
  cal->bdelta57_3plane = ( (cal->bdelta57_1110) || (cal->bdelta57_1101) || (cal->bdelta57_1011) || (cal->bdelta57_0111));
  
  if( cal->bdelta57 ){
    cal->bdelta57_ext  = true;
    cal->delta57_ext   = cal->delta57 ;
  }else if( cal->bdelta57_3plane ){
    if(cal->bdelta57_1110){  cal->delta57_ext = cal->delta57_1110;  cal->bdelta57_ext  = true; }
    if(cal->bdelta57_1101){  cal->delta57_ext = cal->delta57_1101;  cal->bdelta57_ext  = true; }
    if(cal->bdelta57_1011){  cal->delta57_ext = cal->delta57_1011;  cal->bdelta57_ext  = true; }
    if(cal->bdelta57_0111){  cal->delta57_ext = cal->delta57_0111;  cal->bdelta57_ext  = true; }
  }

  ///------------------------------------------
  /// extended optics analysis (for delta 911)
  
  cal->delta911_1110  = -999.9;
  cal->delta911_1101  = -999.9;
  cal->delta911_1011  = -999.9;
  cal->delta911_0111  = -999.9;
  cal->delta911_ext   = -999.9;
  cal->bdelta911_1110  = false;
  cal->bdelta911_1101  = false;
  cal->bdelta911_1011  = false;
  cal->bdelta911_0111  = false;
  cal->bdelta911_3plane= false;
  cal->bdelta911_ext   = false;
  
  if( (cal->F9TrackedX)  &&  fabs(cal->X11PPAC1)<1000.0 ){ //1110
    cal->delta911_1110  = corrected_delta911_1110(cal->X9, cal->A9, cal->X11PPAC1);//(double xdisp, double angle, double xachr)
    cal->bdelta911_1110  = true;
  }
  if( (cal->F9TrackedX)  &&  fabs(cal->X11PPAC2)<1000.0){ //1101
    cal->delta911_1101  = corrected_delta911_1101(cal->X9, cal->A9, cal->X11PPAC2);/////////////
    cal->bdelta911_1101  = true;
  }
  if( fabs(cal->X9PPAC1)<1000.0 && (cal->F11TrackedX) ){ //1011
    cal->delta911_1011  = corrected_delta911_1011(cal->X9PPAC1, cal->A11, cal->X11);/////////////
    cal->bdelta911_1011  = true;
  }
  if( fabs(cal->X9PPAC2)<1000.0 && (cal->F11TrackedX)  ){ //0111
    cal->delta911_0111  = corrected_delta911_0111(cal->X9PPAC2, cal->A11, cal->X11);/////////////
    cal->bdelta911_0111  = true;
  }
  cal->bdelta911_3plane = ( (cal->bdelta911_1110) || (cal->bdelta911_1101) || (cal->bdelta911_1011) || (cal->bdelta911_0111));
  
  if( cal->bdelta911 ){
    cal->bdelta911_ext  = true;
    cal->delta911_ext   = cal->delta911 ;
  }else if( cal->bdelta911_3plane ){
    if(cal->bdelta911_1110){  cal->delta911_ext = cal->delta911_1110;  cal->bdelta911_ext  = true; }
    if(cal->bdelta911_1101){  cal->delta911_ext = cal->delta911_1101;  cal->bdelta911_ext  = true; }
    if(cal->bdelta911_1011){  cal->delta911_ext = cal->delta911_1011;  cal->bdelta911_ext  = true; }
    if(cal->bdelta911_0111){  cal->delta911_ext = cal->delta911_0111;  cal->bdelta911_ext  = true; }
  }

  
  ///-------------------------------------
  /// AoQ (optics, beta) analysis
  
  cal->aoq57  = -999.9;
  cal->aoq911 = -999.9;
  cal->baoq57  = false;
  cal->baoq911 = false;
  if( (cal->btof37) &&  (cal->bdelta57) ){
    cal->baoq57  = true;
    double temp_beta  = (cal->beta57_dipoleratio);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[4])*(1.0 + (cal->delta57)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq57 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  if( (cal->btof811) &&  (cal->bdelta911) ){
    cal->baoq911  = true;
    double temp_beta  = (cal->beta811);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[7])*(1.0 + (cal->delta911)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq911 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  ///-------------------------------------
  /// AoQ-extended analysis
  
  cal->aoq57_1110=-999.9;
  cal->aoq57_1101=-999.9;
  cal->aoq57_1011=-999.9;
  cal->aoq57_0111=-999.9;
  cal->aoq57_ext=-999.9;

  cal->baoq57_1110=false;
  cal->baoq57_1101=false;
  cal->baoq57_1011=false;
  cal->baoq57_0111=false;
  cal->baoq57_3plane=false;
  cal->baoq57_ext=false;

  if( (cal->btof37) &&  (cal->bdelta57_1110) ){
    cal->baoq57_1110  = true;
    double temp_beta  = (cal->beta57_dipoleratio);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[4])*(1.0 + (cal->delta57_1110)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq57_1110 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  if( (cal->btof37) &&  (cal->bdelta57_1101) ){
    cal->baoq57_1101  = true;
    double temp_beta  = (cal->beta57_dipoleratio);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[4])*(1.0 + (cal->delta57_1101)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq57_1101 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  if( (cal->btof37) &&  (cal->bdelta57_1011) ){
    cal->baoq57_1011  = true;
    double temp_beta  = (cal->beta57_dipoleratio);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[4])*(1.0 + (cal->delta57_1011)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq57_1011 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  if( (cal->btof37) &&  (cal->bdelta57_0111) ){
    cal->baoq57_0111  = true;
    double temp_beta  = (cal->beta57_dipoleratio);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[4])*(1.0 + (cal->delta57_0111)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq57_0111 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  cal->baoq57_3plane = ( (cal->baoq57_1110) || (cal->baoq57_1101) || (cal->baoq57_1011) || (cal->baoq57_0111));
  
  if( cal->baoq57 ){
    cal->baoq57_ext  = true;
    cal->aoq57_ext   = cal->aoq57 ;
  }else if( cal->baoq57_3plane ){
    if(cal->baoq57_1110){  cal->aoq57_ext = cal->aoq57_1110;  cal->baoq57_ext  = true; }
    if(cal->baoq57_1101){  cal->aoq57_ext = cal->aoq57_1101;  cal->baoq57_ext  = true; }
    if(cal->baoq57_1011){  cal->aoq57_ext = cal->aoq57_1011;  cal->baoq57_ext  = true; }
    if(cal->baoq57_0111){  cal->aoq57_ext = cal->aoq57_0111;  cal->baoq57_ext  = true; }
  }
  
  
  //-----------------------------------------------------------------------------------------
  cal->aoq911_1110=-999.9;
  cal->aoq911_1101=-999.9;
  cal->aoq911_1011=-999.9;
  cal->aoq911_0111=-999.9;
  cal->aoq911_ext=-999.9;
  
  cal->baoq911_1110=false;
  cal->baoq911_1101=false;
  cal->baoq911_1011=false;
  cal->baoq911_0111=false;
  cal->baoq911_3plane=false;
  cal->baoq911_ext=false;
  
  if( (cal->btof811) &&  (cal->bdelta911_1110) ){
    cal->baoq911_1110  = true;
    double temp_beta  = (cal->beta811);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[7])*(1.0 + (cal->delta911_1110)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq911_1110 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  if( (cal->btof811) &&  (cal->bdelta911_1101) ){
    cal->baoq911_1101  = true;
    double temp_beta  = (cal->beta811);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[7])*(1.0 + (cal->delta911_1101)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq911_1101 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  if( (cal->btof811) &&  (cal->bdelta911_1011) ){
    cal->baoq911_1011  = true;
    double temp_beta  = (cal->beta811);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[7])*(1.0 + (cal->delta911_1011)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq911_1011 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  if( (cal->btof811) &&  (cal->bdelta911_0111) ){
    cal->baoq911_0111  = true;
    double temp_beta  = (cal->beta811);
    double temp_gamma = 1./TMath::Sqrt(1.0 - temp_beta*temp_beta);
    double tm_to_MeV = 299.792458; // from definition of c
    double temp_brho = (cal->dipolebrho[7])*(1.0 + (cal->delta911_0111)); // in Tm
    double temp_mu = 931.4940954; // PDG2016
    cal->aoq911_0111 = temp_brho*tm_to_MeV/(temp_mu*temp_beta*temp_gamma);
  }
  
  cal->baoq911_3plane = ( (cal->baoq911_1110) || (cal->baoq911_1101) || (cal->baoq911_1011) || (cal->baoq911_0111));
  
  if( cal->baoq911 ){
    cal->baoq911_ext  = true;
    cal->aoq911_ext   = cal->aoq911 ;
  }else if( cal->baoq911_3plane ){
    if(cal->baoq911_1110){  cal->aoq911_ext = cal->aoq911_1110;  cal->baoq911_ext  = true; }
    if(cal->baoq911_1101){  cal->aoq911_ext = cal->aoq911_1101;  cal->baoq911_ext  = true; }
    if(cal->baoq911_1011){  cal->aoq911_ext = cal->aoq911_1011;  cal->baoq911_ext  = true; }
    if(cal->baoq911_0111){  cal->aoq911_ext = cal->aoq911_0111;  cal->baoq911_ext  = true; }
  }
  
  
  ///-------------------------------------
  /// Zet (from IC and beta) analysis
  cal->zet7  = -999.9;
  cal->zet11  = -999.9;
  cal->bzet7  = false;
  cal->bzet11 = false;
  if( (cal->btof37) &&  (cal->F7ICEnergySqSum_offline)>0.0 ){
    cal->bzet7 = true;
    cal->zet7  = (para->zet7_coeff1) * TMath::Sqrt(cal->F7ICEnergySqSum_offline) * (cal->beta57_dipoleratio); //need detail correction
  }
  if( (cal->btof811) &&  (cal->F11IC1EnergySqSum_offline)>0.0 ){
    cal->bzet11 = true;
    cal->zet11  = (para->zet11_coeff1) * TMath::Sqrt(cal->F11IC1EnergySqSum_offline) * (cal->beta811);//need detail correction
  }
  
  
  ///--------------------------------------
  ///  DALI analysis 2017/11/25

  // init dali
  int nmax_dali_calib = 10;
  cal->DALINum_A  = 0;
  cal->DALINum_AT = 0;
  cal->DALINum    = 0;
  cal->DALINum_n  = 0;
  cal->DALINum_addback  = 0;
  for(int i=0; i<nmax_dali_calib; i++){
    //------check ADC only---------
    cal->DALIADC_A[i] = -999.9;
    cal->DALIE_A[i]   = -999.9;
    cal->DALIT_A[i]   = -999.9;
    cal->DALIID_A[i]  = -99;
    //------check ADCxTDC---------
    cal->DALIADC_AT[i] = -999.9;
    cal->DALIE_AT[i]   = -999.9;
    cal->DALIEdop78_AT[i] = -999.9;
    cal->DALIID_AT[i]  = -99;
    cal->DALITheta_AT[i] = -999.9;
    cal->DALIX_AT[i] = -999.9;
    cal->DALIY_AT[i] = -999.9;
    cal->DALIZ_AT[i] = -999.9;
    cal->DALIT_AT[i] = -999.9;
    //------check ADCxTDCxF8timing--------
    cal->DALIADC[i] = -999.9;
    cal->DALIE[i]   = -999.9;
    cal->DALIEdop78[i]= -999.9;
    cal->DALIEdop811[i]= -999.9;
    cal->DALIEdopave[i]= -999.9;
    cal->DALIID[i]  = -99;
    cal->DALITheta[i] = -999.9;
    cal->DALIX[i] = -999.9;
    cal->DALIY[i] = -999.9;
    cal->DALIZ[i] = -999.9;
    cal->DALIT[i] = -999.9;
    //------check ADCxTDCxF8timing_narrowgate--------
    cal->DALIADC_n[i] = -999.9;
    cal->DALIE_n[i]   = -999.9;
    cal->DALIEdop78_n[i]= -999.9;
    cal->DALIEdop811_n[i]= -999.9;
    cal->DALIEdopave_n[i]= -999.9;
    cal->DALIID_n[i]  = -99;
    cal->DALITheta_n[i] = -999.9;
    cal->DALIX_n[i] = -999.9;
    cal->DALIY_n[i] = -999.9;
    cal->DALIZ_n[i] = -999.9;
    cal->DALIT_n[i] = -999.9;
    //------check ADCxTDCxF8timing_narrowgate--------
    ////    cal->DALIADC_addback[i] = -999.9; // no ADC for Addback
    cal->DALIE_addback[i]   = -999.9;
    cal->DALIEdop78_addback[i]= -999.9;
    cal->DALIEdop811_addback[i]= -999.9;
    cal->DALIEdopave_addback[i]= -999.9;
    cal->DALIID_addback[i]  = -99;
    cal->DALITheta_addback[i] = -999.9;
    cal->DALIX_addback[i] = -999.9;
    cal->DALIY_addback[i] = -999.9;
    cal->DALIZ_addback[i] = -999.9;
    cal->DALIT_addback[i] = -999.9;
    cal->DALIN_addback[i] = 0;
  }
  
  //---temp parameter---
  double tempdali_tdc_to_ns = 0.0977;// common for all according to db.
  double tempdali_tdc_common_offset = 1058.0;// this is fixed. correction will be analyzed relaive to this offset.
  
  //----calculate data for each NaI----
  double tempdaliadc[186];
  double tempdalitdc[186];
  double tempdalitime[186];
  double tempdali_tdc_ref[186];
  double tempdalitdc_ref1 = raw->dalitdc_s[186];
  double tempdalitdc_ref2 = raw->dalitdc_s[187];
  double tempdalienergy[186];
  double tempdali_f8timecheck[186];
  
  
  //----set time ref for each channel---
  for(int i=0; i<186; i++){
    if(6==(para->nai[i]->tdc_geo)){
      tempdali_tdc_ref[i] = tempdalitdc_ref1;
    }else if(8==(para->nai[i]->tdc_geo)){
      tempdali_tdc_ref[i] = tempdalitdc_ref2;
    }else{
      std::cout << "Error in dali analysis (calib), unknown tdc_geo =" << (para->nai[i]->tdc_geo) << " at id =" << i <<std::endl;
      tempdali_tdc_ref[i] = 9999999.9;//
    }
  }
  
  //----calculation for each channel
  for(int i=0; i<186; i++){
    tempdaliadc[i] = raw->daliadc[i] - 0.5 + random3->Uniform(0.0,1.0);
    tempdalienergy[i] = (para->dali_adc_factor[i])*(tempdaliadc[i])+(para->dali_adc_offset[i]);
    tempdalitdc[i] = raw->dalitdc_s[i];
    tempdalitime[i] = tempdali_tdc_to_ns*( tempdalitdc[i]  -  tempdali_tdc_ref[i]) + tempdali_tdc_common_offset + (para->dali_time_offset[i]);
    tempdali_f8timecheck[i] = tempdalitime[i] - (cal->tof78);
  }
  

  //------check ADC only---------
  int dalicount_A = 0;
  for(int i=0; i<186; i++){
    if(0.0<tempdaliadc[i] && tempdaliadc[i]<4095.1){ ////// This is the condition for "check ADC only"
      if(dalicount_A<nmax_dali_calib){
        cal->DALIADC_A[dalicount_A] = tempdaliadc[i];
        cal->DALIE_A[dalicount_A]   = tempdalienergy[i];
        cal->DALIID_A[dalicount_A]  = i;
        cal->DALIT_A[dalicount_A]   = tempdalitime[i];
      }
      dalicount_A++;
      cal->DALINum_A = dalicount_A;
    }
  }
  
  
  //------check ADCxTDCxF8timing---------
  int dalicount_AT = 0;
  for(int i=0; i<186; i++){
    //----- check conditions
    if(0.0<tempdaliadc[i] && tempdaliadc[i]<4095.1 && 0.0<tempdalitdc[i] && 0.0<tempdalitdc_ref1 && 0.0<tempdalitdc_ref2 && (0.4<(cal->beta78) && (cal->beta78)<0.8 ) && -20.0<tempdali_f8timecheck[i]  && tempdali_f8timecheck[i]<60.){
      if(dalicount_AT<nmax_dali_calib){
        cal->DALIADC_AT[dalicount_AT]   = tempdaliadc[i];
        cal->DALIE_AT[dalicount_AT]     = tempdalienergy[i]; /// parameters defined in setup.C for offline analysis, not db.
        cal->DALIID_AT[dalicount_AT]    = i;
        cal->DALITheta_AT[dalicount_AT] = para->nai[i]->theta;
        cal->DALIX_AT[dalicount_AT]     = para->nai[i]->x_pos;
        cal->DALIY_AT[dalicount_AT]     = para->nai[i]->y_pos;
        cal->DALIZ_AT[dalicount_AT]     = para->nai[i]->z_pos;
        cal->DALIT_AT[dalicount_AT]     = tempdalitime[i];
        cal->DALIEdop78_AT[dalicount_AT]= function_doppler(tempdalienergy[i], para->nai[i]->theta, cal->beta78);
      }
      dalicount_AT++;
      cal->DALINum_AT = dalicount_AT;
    }
  }
  
  
  //------check ADCxTDCxF8timingxF11timing---------
  int dalicount_all = 0;
  for(int i=0; i<186; i++){
    //----- check conditions
    if(0.0<tempdaliadc[i] && tempdaliadc[i]<4095.1 && 0.0<tempdalitdc[i] && 0.0<tempdalitdc_ref1 && 0.0<tempdalitdc_ref2 && (0.4<(cal->beta78) && (cal->beta78)<0.8 ) &&  -20.0<tempdali_f8timecheck[i]   && tempdali_f8timecheck[i] <60.0 && (0.4<(cal->beta811) && (cal->beta811)<0.8 )){
      if(dalicount_all<nmax_dali_calib){
        cal->DALIADC[dalicount_all]   = tempdaliadc[i];
        cal->DALIE[dalicount_all]     = tempdalienergy[i]; /// parameters defined in setup.C for offline analysis, not db.
        cal->DALIID[dalicount_all]    = i;
        cal->DALITheta[dalicount_all] = para->nai[i]->theta;
        cal->DALIX[dalicount_all]     = para->nai[i]->x_pos;
        cal->DALIY[dalicount_all]     = para->nai[i]->y_pos;
        cal->DALIZ[dalicount_all]     = para->nai[i]->z_pos;
        cal->DALIT[dalicount_all]     = tempdalitime[i];
        cal->DALIEdop78[dalicount_all]  = function_doppler(tempdalienergy[i], para->nai[i]->theta, cal->beta78);
        cal->DALIEdop811[dalicount_all] = function_doppler(tempdalienergy[i], para->nai[i]->theta, cal->beta811);
        cal->DALIEdopave[dalicount_all] = function_doppler(tempdalienergy[i], para->nai[i]->theta, 0.5*(cal->beta78 + cal->beta811) );
      }
      dalicount_all++;
      cal->DALINum = dalicount_all;
    }
  }
  
  
  //------check ADCxTDCxF8timingxF11timing---------
  int dalicount_all_narrow = 0;
  for(int i=0; i<186; i++){
    //----- check conditions
    if(0.0<tempdaliadc[i] && tempdaliadc[i]<4095.1 && 0.0<tempdalitdc[i] && 0.0<tempdalitdc_ref1 && 0.0<tempdalitdc_ref2 && (0.4<(cal->beta78) && (cal->beta78)<0.8 ) &&  -10.0<tempdali_f8timecheck[i]   && tempdali_f8timecheck[i] <20.0 && (0.4<(cal->beta811) && (cal->beta811)<0.8 )){
      if(dalicount_all_narrow < nmax_dali_calib){
        cal->DALIADC_n[dalicount_all_narrow]     = tempdaliadc[i];
        cal->DALIE_n[dalicount_all_narrow]       = tempdalienergy[i]; /// parameters defined in setup.C for offline analysis, not db.
        cal->DALIID_n[dalicount_all_narrow]      = i;
        cal->DALITheta_n[dalicount_all_narrow]   = para->nai[i]->theta;
        cal->DALIX_n[dalicount_all_narrow]       = para->nai[i]->x_pos;
        cal->DALIY_n[dalicount_all_narrow]       = para->nai[i]->y_pos;
        cal->DALIZ_n[dalicount_all_narrow]       = para->nai[i]->z_pos;
        cal->DALIT_n[dalicount_all_narrow]       = tempdalitime[i];
        cal->DALIEdop78_n[dalicount_all_narrow]  = function_doppler(tempdalienergy[i], para->nai[i]->theta, cal->beta78);
        cal->DALIEdop811_n[dalicount_all_narrow] = function_doppler(tempdalienergy[i], para->nai[i]->theta, cal->beta811);
        cal->DALIEdopave_n[dalicount_all_narrow] = function_doppler(tempdalienergy[i], para->nai[i]->theta, 0.5*(cal->beta78 + cal->beta811) );
      }
      dalicount_all_narrow++;
      cal->DALINum_n = dalicount_all_narrow;
    }
  }
  
  //--------addback----------
  
  int id_desceding[10];
  int check_available[10];
  int n_hit;
  int count_addback=0;
  double temp_array_E[10];
 
  //-------set n_hit, id_descending, check_available------------
  n_hit = cal->DALINum; //wide
  //  n_hit = cal->DALINum_n;//narrow
  if(n_hit>10){ n_hit = 10;}
  for(int i=0; i<10; i++){ check_available[i] = 0; }
  for(int i=0; i<n_hit; i++){ check_available[i] = 1; }
  for(int i=0; i<n_hit; i++){ temp_array_E[i] = cal->DALIE[i]; } //wide
  //  for(int i=0; i<n_hit; i++){ temp_array_E[i] = cal->DALIE_n[i]; } // narrow
  
  for(int i=0; i<n_hit; i++){
    double tempmaxE = -999.9;
    int tempid_maxE = -99;
    for(int j=0; j<n_hit; j++){
      if(temp_array_E[j]>tempmaxE){
        tempmaxE = temp_array_E[j];
        tempid_maxE = j;
      }
    }
    id_desceding[i] = tempid_maxE;
    temp_array_E[tempid_maxE] = -999999.9;
  }
  
  //debug // looked OK.
  if(0){
    if(n_hit>0){
      printf("-------------\n");
    }
    for(int i=0; i<n_hit; i++){
      printf("E(%d) = %f  \n",i, cal->DALIE[i]); //wide
      // printf("E(%d) = %f  \n",i, cal->DALIE_n[i]); //narrow
    }
    for(int i=0; i<n_hit; i++){
      printf("ID_descending = %d  \n",id_desceding[i]);
    }
  }
  //-----------------------------
  
  //
  for(int i=0; i<n_hit; i++){
    if(check_available[i]==1){
      //  cal->DALIE_addback[count_addback] = cal->DALIE_n[id_desceding[i]]; //narrow
      //  cal->DALIID_addback[count_addback] = cal->DALIID_n[id_desceding[i]];
      //  cal->DALITheta_addback[count_addback] = cal->DALITheta_n[id_desceding[i]];
      //  cal->DALIX_addback[count_addback] = cal->DALIX_n[id_desceding[i]];
      //  cal->DALIY_addback[count_addback] = cal->DALIY_n[id_desceding[i]];
      //  cal->DALIZ_addback[count_addback] = cal->DALIZ_n[id_desceding[i]];
      //  cal->DALIT_addback[count_addback] = cal->DALIT_n[id_desceding[i]];
      cal->DALIE_addback[count_addback] = cal->DALIE[id_desceding[i]]; //wide
      cal->DALIID_addback[count_addback] = cal->DALIID[id_desceding[i]];
      cal->DALITheta_addback[count_addback] = cal->DALITheta[id_desceding[i]];
      cal->DALIX_addback[count_addback] = cal->DALIX[id_desceding[i]];
      cal->DALIY_addback[count_addback] = cal->DALIY[id_desceding[i]];
      cal->DALIZ_addback[count_addback] = cal->DALIZ[id_desceding[i]];
      cal->DALIT_addback[count_addback] = cal->DALIT[id_desceding[i]];
      cal->DALIN_addback[count_addback] = 1;
      //------ energy add for near NaI----
      for(int j=i+1; j<n_hit; j++){
        //  double tempx_i = cal->DALIX_n[id_desceding[i]]; //narrow
        //  double tempy_i = cal->DALIY_n[id_desceding[i]];
        //  double tempz_i = cal->DALIZ_n[id_desceding[i]];
        //  double tempx_j = cal->DALIX_n[id_desceding[j]];
        //  double tempy_j = cal->DALIY_n[id_desceding[j]];
        //  double tempz_j = cal->DALIZ_n[id_desceding[j]];
        double tempx_i = cal->DALIX[id_desceding[i]]; //wide
        double tempy_i = cal->DALIY[id_desceding[i]];
        double tempz_i = cal->DALIZ[id_desceding[i]];
        double tempx_j = cal->DALIX[id_desceding[j]];
        double tempy_j = cal->DALIY[id_desceding[j]];
        double tempz_j = cal->DALIZ[id_desceding[j]];
        double temp_dist = TMath::Sqrt((tempx_i - tempx_j)*(tempx_i - tempx_j) + (tempy_i - tempy_j)*(tempy_i - tempy_j) + (tempz_i - tempz_j)*(tempz_i - tempz_j));
        if(check_available[j] ==1 && temp_dist < 15.0){ // then this hit(j) is combined with (i)
          check_available[j] = 0;
          //cal->DALIE_addback[count_addback] += cal->DALIE_n[id_desceding[j]]; //narrow
          cal->DALIE_addback[count_addback] += cal->DALIE[id_desceding[j]]; //wide
          cal->DALIN_addback[count_addback] += 1;
        }
      }
      ///----
      cal->DALIEdop78_addback[count_addback]  = function_doppler(cal->DALIE_addback[count_addback], cal->DALITheta_addback[count_addback], cal->beta78);
      cal->DALIEdop811_addback[count_addback] = function_doppler(cal->DALIE_addback[count_addback], cal->DALITheta_addback[count_addback], cal->beta811);
      cal->DALIEdopave_addback[count_addback] = function_doppler(cal->DALIE_addback[count_addback], cal->DALITheta_addback[count_addback], 0.5*(cal->beta78 + cal->beta811) );
      count_addback ++;
      cal->DALINum_addback = count_addback;
    }
  }
  
  return ;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void SetupParameter(RIBF132Parameter *para)
{  
  //---- load xml files for anaroot ----//
  para -> LoadParameter((char*)"db_calib/BigRIPSPPAC.xml");
  para -> LoadParameter((char*)"db_calib/BigRIPSIC.xml");
  para -> LoadParameter((char*)"db_calib/BigRIPSPlastic.xml");
  para -> LoadParameter((char*)"db_calib/FocalPlane.xml");
  para -> LoadParameter((char*)"db_calib/DALI.xml");          // added
  
  // just to check above loadings
  std::cout << "--parameter check--" << std::endl;
  std::cout << "f7ic     :  " << para -> f7ic   -> detname << ",  " << para -> f7ic   -> zcoef[0]  << ",  " << para -> f7ic   -> zcoef[1]   <<  ",  " << para -> f7ic   -> zcoef[2] << std::endl;
  std::cout << "music1   :  " << para -> music1 -> detname << ",  " << para -> music1 -> zcoef[0]  << ",  " << para -> music1 -> zcoef[1]   <<  ",  " << para -> music1 -> zcoef[2] << std::endl;
  std::cout << "music2   :  " << para -> music2 -> detname << ",  " << para -> music2 -> zcoef[0]  << ",  " << para -> music2 -> zcoef[1]   <<  ",  " << para -> music2 -> zcoef[2] << std::endl;
  std::cout << "plastic0 :  " << para -> pla[0] -> detname << ",  " << para -> pla[0] -> tcal_left << ",  " << para -> pla[0] -> tcal_right << std::endl;
  std::cout << "plastic1 :  " << para -> pla[1] -> detname << ",  " << para -> pla[1] -> tcal_left << ",  " << para -> pla[1] -> tcal_right << std::endl;
  std::cout << "plastic2 :  " << para -> pla[2] -> detname << ",  " << para -> pla[2] -> tcal_left << ",  " << para -> pla[2] -> tcal_right << std::endl;
  std::cout << "plastic3 :  " << para -> pla[3] -> detname << ",  " << para -> pla[3] -> tcal_left << ",  " << para -> pla[3] -> tcal_right << std::endl;
  std::cout << "plastic4 :  " << para -> pla[4] -> detname << ",  " << para -> pla[4] -> tcal_left << ",  " << para -> pla[4] -> tcal_right << std::endl;
  std::cout << "plastic5 :  " << para -> pla[5] -> detname << ",  " << para -> pla[5] -> tcal_left << ",  " << para -> pla[5] -> tcal_right << std::endl;
  std::cout << "plastic6 :  " << para -> pla[6] -> detname << ",  " << para -> pla[6] -> tcal_left << ",  " << para -> pla[6] -> tcal_right << std::endl;
  std::cout << "plastic7 :  " << para -> pla[7] -> detname << ",  " << para -> pla[7] -> tcal_left << ",  " << para -> pla[7] -> tcal_right << std::endl;
  
  std::cout << "PPAC-NAME, FPL, a_ch2ns, x1_ch2ns, y1_ch2ns, x2_ch2ns, y2_ch2ns, xfactor, yfactor, ";
  std::cout << "xoffset, yoffset, xns_off, yns_off, xpos_off, ypos_off, xzpos, yzpos...." << std::endl;

  for(int ii = 0; ii < 7; ii++)
  {
    for(int jj = 0; jj < 4; jj++)
    {
      std::cout << para -> ppac[ii][jj] -> detname << "," << para -> ppac[ii][jj] -> fpl << "," << para -> ppac[ii][jj] -> ch2ns_a << "," << para -> ppac[ii][jj] -> ch2ns_x1 << "," << para -> ppac[ii][jj] ->ch2ns_y1;
      std::cout << "," << para -> ppac[ii][jj] -> ch2ns_x2 << "," << para -> ppac[ii][jj] -> ch2ns_y2 << "," << para -> ppac[ii][jj] -> xfactor << "," << para -> ppac[ii][jj] -> yfactor << "," << para -> ppac[ii][jj] -> xoffset << ",";
      
      std::cout << para -> ppac[ii][jj] -> yoffset << "," << para -> ppac[ii][jj] -> xns_off << "," << para -> ppac[ii][jj] -> yns_off << "," << para -> ppac[ii][jj] -> xpos_off << "," << para -> ppac[ii][jj] -> ypos_off << ",";
      std::cout << para -> ppac[ii][jj] -> xzpos << "," << para -> ppac[ii][jj] -> yzpos << std::endl;
    }
  }

  for(int ii = 0; ii < 12; ii++)
  {
    std::cout << "focalplane(" << ii << "):  id = " << para -> fp[ii] -> id << ",  fpl = " << para -> fp[ii] -> fpl << ",  zpos = " << para -> fp[ii] -> zpos << ",  zpos_offset = " << para -> fp[ii] -> zpos_offset << std::endl;
  }

  for(int ii = 0; ii < 188; ii++)
  {
    std::cout << "DALI NAI (id=" << para -> nai[ii] -> id << "): " << " fpl="  << para -> nai[ii] -> fpl << ", theta = " << para->nai[ii]->theta << ", x_pos = " << para -> nai[ii] -> x_pos << ", y_pos = " << para -> nai[ii] -> y_pos << ", z_pos = " << para -> nai[ii] -> z_pos << ", adc_geo = " << para -> nai[ii] -> adc_geo << ", adc_ch = " << para -> nai[ii] -> adc_ch << para -> nai[ii]-> z_pos << ", tdc_geo = " << para -> nai[ii] -> tdc_geo <<", tdc_ch = " << para -> nai[ii] -> tdc_ch << std::endl;
  }
  
  
  //--- additional setting ---//
  // para->dummy = 123.0 ;  std::cout << para->dummy << std::endl;  // just for test

  // outside this file
  setup(para);          // from setup.C file
  
  return ;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

int main(int argc, char *argv[])
{  
  random3 = new TRandom3(0);
  
  char inputfilename[256];
  char outputfilename[256];
  char ppactripdatafilename[256]; //added on 27.Sep.2017

  // argv[1] is the inputfile name
  // argv[2] is the outputfile name
  // argv[3] is the runnumber

  sprintf(inputfilename,  "%s", argv[1]);
  sprintf(outputfilename, "%s", argv[2]);

  int runnumber = stoi(argv[3]);
  sprintf(ppactripdatafilename, "ppactripdata/run%04d.txt", runnumber);

  // Print input, output, and run number
  cout << "\n Given inputs are..." << endl;
  cout << "Input file name  : " << inputfilename << endl;
  cout << "Output file name : " << outputfilename << endl;
  cout << "Run number       : " << runnumber << "\n" << endl;

  //parameter
  RIBF132Parameter *para = new RIBF132Parameter();
  SetupParameter(para);
  
  TFile *file1 = TFile::Open(inputfilename);
  if((TFile *)nullptr == file1)
  {
    std::cout << "input file (" << inputfilename << ")does not exist... " << std::endl;
    std::cout << "stop.. "<< std::endl;
    return -1;
  }
  
  TTree *tree1 = (TTree*)(file1->Get("tree"));
  if((TTree *)nullptr == tree1)
  {
    std::cout << "input tree (tree) does not exist... "<< std::endl;
    std::cout << "stop.. "<< std::endl;
    return -1;
  }
  
  
  //---------------------
  //  PPAC HV trip data (27Sep2017)
  int ngr_ppactripdata = 0;
  int nev_gr_ppactripdata;
  int iev_first[100000];
  int iev_last[100000];
  int check_ppacstatus[100000][14];
  int inttemp[16];
  
  FILE* fp_ppactripdata;
  if((fp_ppactripdata = fopen(ppactripdatafilename, "r")) == NULL)
  {
    std::cout << "ppac-trip-data file does not exist... " << std::endl;
    std::cout << "stop.. " << std::endl;
    return -1;
  }

  while(fscanf(fp_ppactripdata, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", inttemp+0, inttemp+1, inttemp+2, inttemp+3, inttemp+4, inttemp+5, inttemp+6, inttemp+7, inttemp+8, inttemp+9, inttemp+10, inttemp+11, inttemp+12, inttemp+13, inttemp+14, inttemp+15) != EOF)
  {
    iev_first[ngr_ppactripdata] = inttemp[0];
    iev_last[ngr_ppactripdata]  = inttemp[1];

    for(int iii = 0; iii < 14; iii++) { check_ppacstatus[ngr_ppactripdata][iii] =  inttemp[2+iii]; }

    if(1)
    { 
      //check
      printf("%d %d %d ",ngr_ppactripdata, iev_first[ngr_ppactripdata], iev_last[ngr_ppactripdata]);
      for(int iii = 0; iii < 14; iii++) { printf("%d ", check_ppacstatus[ngr_ppactripdata][iii]); }
      printf("\n");
    }

    ngr_ppactripdata++;
  }
  nev_gr_ppactripdata = iev_last[0] - iev_first[0] + 1;
  fclose(fp_ppactripdata);
  //---------------------
  
  
  //----init----
  //input
  RIBF132Raw *raw = new RIBF132Raw(tree1);

  if(raw -> fChain == 0) return -1;

  Long64_t nentries = raw -> fChain -> GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  
  //output
  TFile *file2 = new TFile(outputfilename,"RECREATE");
  TTree *tree2 = new TTree("cal","cal");
  RIBF132CalibOut *cal = new RIBF132CalibOut(tree2);
  cal -> Init();
  
  
  //----loop for event----
  for(Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    Long64_t ientry = raw -> LoadTree(jentry);
    if (ientry < 0) break;

    nb = raw -> fChain -> GetEntry(jentry);   nbytes += nb;

    // if (Cut(ientry) < 0) continue;
    if(0!=jentry && 0==(jentry % 10000) ) { std::cout << "." << std::flush;       }
    if(0!=jentry && 0==(jentry % 100000)) { std::cout << std::endl << std::flush; }
    
    cal -> ievent = ((int)jentry);

    // Main Program for Each Event
    EventRaw2Calib(raw, cal, para);
    
    //---------------------
    //  PPAC HV trip data (27Sep2017)
    int j_gr = ((int)jentry)/nev_gr_ppactripdata;
    if(jentry<iev_first[j_gr] || iev_last[j_gr]<jentry )
    { //error
      std::cout << "Line mismatch in PPAC HV trip data !!! ... " << std::endl;
    }

    if(1==check_ppacstatus[j_gr][0])  { cal->bF3PPACHVX  = true; } else { cal -> bF3PPACHVX  = false; }
    if(1==check_ppacstatus[j_gr][1])  { cal->bF3PPACHVY  = true; } else { cal -> bF3PPACHVY  = false; }
    if(1==check_ppacstatus[j_gr][2])  { cal->bF5PPACHVX  = true; } else { cal -> bF5PPACHVX  = false; }
    if(1==check_ppacstatus[j_gr][3])  { cal->bF5PPACHVY  = true; } else { cal -> bF5PPACHVY  = false; }
    if(1==check_ppacstatus[j_gr][4])  { cal->bF7PPACHVX  = true; } else { cal -> bF7PPACHVX  = false; }
    if(1==check_ppacstatus[j_gr][5])  { cal->bF7PPACHVY  = true; } else { cal -> bF7PPACHVY  = false; }
    if(1==check_ppacstatus[j_gr][6])  { cal->bF8PPACHVX  = true; } else { cal -> bF8PPACHVX  = false; }
    if(1==check_ppacstatus[j_gr][7])  { cal->bF8PPACHVY  = true; } else { cal -> bF8PPACHVY  = false; }
    if(1==check_ppacstatus[j_gr][8])  { cal->bF9PPACHVX  = true; } else { cal -> bF9PPACHVX  = false; }
    if(1==check_ppacstatus[j_gr][9])  { cal->bF9PPACHVY  = true; } else { cal -> bF9PPACHVY  = false; }
    if(1==check_ppacstatus[j_gr][10]) { cal->bF11PPACHVX = true; } else { cal -> bF11PPACHVX = false; }
    if(1==check_ppacstatus[j_gr][11]) { cal->bF11PPACHVY = true; } else { cal -> bF11PPACHVY = false; }
    if(1==check_ppacstatus[j_gr][12]) { cal->bF8PPAC1HVX = true; } else { cal -> bF8PPAC1HVX = false; }
    if(1==check_ppacstatus[j_gr][13]) { cal->bF8PPAC1HVY = true; } else { cal -> bF8PPAC1HVY = false; }

    if((cal->bF5PPACHVX) && (cal->bF7PPACHVX) && (cal->bF9PPACHVX) && (cal->bF11PPACHVX)) { cal -> bF57911PPACHVX = true; } else { cal -> bF57911PPACHVX = false; }
    if((cal->bF5PPACHVY) && (cal->bF7PPACHVY) && (cal->bF9PPACHVY) && (cal->bF11PPACHVY)) { cal -> bF57911PPACHVY = true; } else { cal -> bF57911PPACHVY = false; }
    
    if((cal->bF57911PPACHVX) && (cal->bF57911PPACHVY)) { cal -> bF57911PPACHV = true; } else { cal -> bF57911PPACHV = false; }
    
    //----------------------
    
    
    cal->Fill();
  }
  //------

  //----end---
  tree2->Write();
  file2->Close();
  file1->Close();
  return 0;
}
