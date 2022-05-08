#include <TMath.h>

double corrected_delta35(double, double, double);
double corrected_delta57(double, double, double);
double corrected_delta911(double, double, double);

/// these 3 functions are used in calib.cc

double f_delta35(double x5in, double a5in, double x3in, double a3in){
  return corrected_delta35(x5in, a5in, x3in);
}

double f_delta57(double x5in, double a5in, double x7in, double a7in){
  return corrected_delta57(x5in, a5in, x7in);
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
  
  /*
   // with 7 delta point
   double r00 = (6.304332);
   double r01 = (0.828804);
   double r10 = (-2432.001322);
   double r11 = (-15.151322);
   double r2  = (-8809.397006);
   double s0  = (1.064706);
   double s1  = (-12.875504);
   double s2  = (-1372.540132);
   double t0  = (-0.038859);
   */
  // with 9 delta point
  double r00 = (6.350801);
  double r01 = (0.887600);
  double r10 = (-2420.441343);
  double r11 = (-12.539148);
  double r2  = (-8500.607796);
  double s0  = (1.026567);
  double s1  = (-7.204780);
  double s2  = (-917.682199);
  double t0  = (-0.042999);
  ////
  double coeff_delta0 = -x9 + (r00 + r01 * Xachr) + s0*a9 + t0*a9*a9;
  double coeff_delta1 = (r10 + r11 * Xachr) + s1*a9;
  double coeff_delta2 = r2 + s2*a9;
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  return (-1.0*coeff_delta1 - sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}


double corrected_delta35(double x5, double a5, double x3){
  /// double r00 = ...
  // for pars: r00, r01, r10, r11, r2, s0, s1, s2, t0
  double r00 = (9.607711);
  double r01 = (0.586266);
  double r10 = (3024.091552);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.305264);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.005879);
  ////
  double coeff_delta0 = -x5 + (r00 + r01 * x3) + s0*a5 + t0*a5*a5;
  double coeff_delta1 = (r10 + r11 * x3) + s1*a5;
  double coeff_delta2 = r2 + s2*a5;
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  // return (-1.0*coeff_delta1 - sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
}


double corrected_delta57(double x5, double a5, double x7){
  /// double r00 = ...
  // for pars: r00, r01, r10, r11, r2, s0, s1, s2, t0
  double r00 = (9.095618);
  double r01 = (0.734102);
  double r10 = (3049.363191);
  double r11 = (5.333812);
  double r2  = (0.000000);
  double s0  = (-0.232387);
  double s1  = (-1.320389);
  double s2  = (0.000000);
  double t0  = (0.000000);
  ////
  double coeff_delta0 = -x5 + (r00 + r01 * x7) + s0*a5 + t0*a5*a5;
  double coeff_delta1 = (r10 + r11 * x7) + s1*a5;
  double coeff_delta2 = r2 + s2*a5;
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  // return (-1.0*coeff_delta1 - sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
  return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
}
