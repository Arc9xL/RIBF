#include <TMath.h>

double corrected_delta35(double, double, double);
double corrected_delta57_1111(double, double, double);
double corrected_delta911(double, double, double);

/// these 3 functions are used in calib.cc

double f_delta35(double x5in, double a5in, double x3in, double a3in){
  return corrected_delta35(x5in, a5in, x3in);
}

double f_delta57(double x5in, double a5in, double x7in, double a7in){
  return corrected_delta57_1111(x5in, a5in, x7in);
}

double f_delta911(double x9in, double a9in, double x11in, double a11in){
  return corrected_delta911(x9in, a9in, x11in-(a11in*0.792) );
}

//-----------------------------------------------------------
//tanaka@Yoshiki-no-MacBook-Pro:~/ribf132analysis/calib/optics_analysis $ open xa9plot.C
//tanaka@Yoshiki-no-MacBook-Pro:~/ribf132analysis/calib/optics_analysis $ open xa5plot_f7x.C
//tanaka@Yoshiki-no-MacBook-Pro:~/ribf132analysis/calib/optics_analysis $ open xa5plot_f3x.C

double corrected_delta911(double x9, double a9, double Xachr){ //char xachrname[256]="X11-(A11*0.792)";
  /// double r00 = ...
  // for pars: r00, r01, r10, r11, r2, s0, s1, s2, t0
  

  // update for run30-34 tof analysis + optics analysis
  // 2017/07/07
  // with 8 delta points
  double r00 = (3.033012);
  double r01 = (0.813849);
  double r10 = (-2423.943339);
  double r11 = (-13.394869);
  double r2  = (-8878.719563);
  double s0  = (0.863293);
  double s1  = (-21.918862);
  double s2  = (-959.153791);
  double t0  = (-0.051420);
  
  ////
  double coeff_delta0 = -x9 + (r00 + r01 * Xachr) + s0*a9 + t0*a9*a9;
  double coeff_delta1 = (r10 + r11 * Xachr) + s1*a9;
  double coeff_delta2 = r2 + s2*a9;
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  return (-1.0*coeff_delta1 - sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}


double corrected_delta35(double x5, double a5, double x3){

  // update for run30-34 tof analysis + optics analysis
  // 2017/07/07
  double r00 = (0.814540);
  double r01 = (0.634693);
  double r10 = (3014.331106);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.307578);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.005205);
  ////
  ////
  double coeff_delta0 = -x5 + (r00 + r01 * x3) + s0*a5 + t0*a5*a5;
  double coeff_delta1 = (r10 + r11 * x3) + s1*a5;
  double coeff_delta2 = r2 + s2*a5;
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  // return (-1.0*coeff_delta1 - sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
}


//--- parameter F5-F7 for 1111 ----
/*
double corrected_delta57_1111(double xdisp, double angle, double xachr){
  double r00 = (0.079947);
  double r01 = (0.741685);
  double r10 = (3029.740858);
  double r11 = (6.856346);
  double r2  = (0.000000);
  double s0  = (-0.238740);
  double s1  = (-0.596055);
  double s2  = (72.366820);
  double t0  = (0.000000);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
 */
//----------------------------------
/*
double corrected_delta57(double x5, double a5, double x7){
  /// double r00 = ...
  // for pars: r00, r01, r10, r11, r2, s0, s1, s2, t0
  // update for run30-34 tof analysis + optics analysis
  // 2017/07/07
  double r00 = (0.079947);
  double r01 = (0.741685);
  double r10 = (3029.740858);
  double r11 = (6.856346);
  double r2  = (0.000000);
  double s0  = (-0.238740);
  double s1  = (-0.596055);
  double s2  = (72.366820);
  double t0  = (0.000000);
  ////
  double coeff_delta0 = -x5 + (r00 + r01 * x7) + s0*a5 + t0*a5*a5;
  double coeff_delta1 = (r10 + r11 * x7) + s1*a5;
  double coeff_delta2 = r2 + s2*a5;
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  // return (-1.0*coeff_delta1 - sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
*/



//----------------------------------
//--- parameter F5-F7 for 1110 ----
double corrected_delta57_1110(double xdisp, double angle, double xachr){
  double r00 = (-0.211068);
  double r01 = (0.411972);
  double r10 = (2989.706284);
  double r11 = (0.135670);
  double r2  = (0.000000);
  double s0  = (0.103247);
  double s1  = (0.370504);
  double s2  = (-12.498688);
  double t0  = (0.000000);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F5-F7 for 1101 ----
double corrected_delta57_1101(double xdisp, double angle, double xachr){
  double r00 = (0.245903);
  double r01 = (0.698598);
  double r10 = (3030.053706);
  double r11 = (6.023603);
  double r2  = (0.000000);
  double s0  = (-0.304083);
  double s1  = (-2.133901);
  double s2  = (130.443756);
  double t0  = (0.000000);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F5-F7 for 1011 ----
double corrected_delta57_1011(double xdisp, double angle, double xachr){
  double r00 = (-0.794527);
  double r01 = (0.903374);
  double r10 = (3026.396961);
  double r11 = (8.980290);
  double r2  = (0.000000);
  double s0  = (-0.617043);
  double s1  = (-1.112262);
  double s2  = (114.837758);
  double t0  = (0.000000);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F5-F7 for 0111 ----
double corrected_delta57_0111(double xdisp, double angle, double xachr){
  double r00 = (0.019250);
  double r01 = (0.725407);
  double r10 = (3030.273609);
  double r11 = (4.564218);
  double r2  = (0.000000);
  double s0  = (0.011273);
  double s1  = (-1.214304);
  double s2  = (5.087532);
  double t0  = (0.000000);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F5-F7 for 1111 ----
double corrected_delta57_1111(double xdisp, double angle, double xachr){
  double r00 = (0.079947);
  double r01 = (0.741685);
  double r10 = (3029.740858);
  double r11 = (6.856346);
  double r2  = (0.000000);
  double s0  = (-0.238740);
  double s1  = (-0.596055);
  double s2  = (72.366820);
  double t0  = (0.000000);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
