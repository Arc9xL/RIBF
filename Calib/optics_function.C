#include <TMath.h>

//-----------------------------------------------------------
// These three functions are used in calib.cc for
// optics analysis with full track information
//-----------------------------------------------------------
// f_delta35(cal->X5, cal->A5, cal->X3, cal->A3);//first dispersive, next achromatic
// f_delta57(cal->X5, cal->A5, cal->X7, cal->A7);//first dispersive, next achromatic
// f_delta911(cal->X9, cal->A9, cal->X11, cal->A11);

//-----------------------------------------------------------
// These functions are used in calib.cc for optics
// analysis with reduced track information
//-----------------------------------------------------------
// corrected_delta35_1110(cal->X5PPAC1, cal->A3, cal->X3);
// corrected_delta35_1101(cal->X5PPAC2, cal->A3, cal->X3);
// corrected_delta35_1011(cal->X5, cal->A5, cal->X3PPAC1);
// corrected_delta35_0111(cal->X5, cal->A5, cal->X3PPAC2);
//
// corrected_delta57_1110(cal->X5, cal->A5, cal->X7PPAC1);
// corrected_delta57_1101(cal->X5, cal->A5, cal->X7PPAC2);
// corrected_delta57_1011(cal->X5PPAC1, cal->A7, cal->X7);
// corrected_delta57_0111(cal->X5PPAC2, cal->A7, cal->X7);
//

//-----------------------------------------------------------
//    with full tracks
double corrected_delta35_1111(double, double, double);
double corrected_delta57_1111(double, double, double);
double corrected_delta911_1111(double, double, double);
double corrected_delta911_2222(double, double, double);
double corrected_delta911_3333(double, double, double);

double f_delta35(double x5in, double a5in, double x3in, double a3in){
  return corrected_delta35_1111(x5in, a5in, x3in);
}
double f_delta57(double x5in, double a5in, double x7in, double a7in){
  return corrected_delta57_1111(x5in, a5in, x7in);
}
double f_delta911(double x9in, double a9in, double x11in, double a11in){
  return corrected_delta911_2222(x9in, a9in, x11in-(a11in*0.292)); // see definition of 2222 in plot_optics_analysis_step1/plot_f9f11_ana3plane.C
}


//-----------------------------------------------------------
// below just copy from generated functions:
//  /Users/tanaka/ribf132analysis/calib_with_dali/optics_analysis_update2017_dec07/extract_optics_analysis_parameter_step2/coefficient_f3_f5x_out.txt
//  /Users/tanaka/ribf132analysis/calib_with_dali/optics_analysis_update2017_dec07/extract_optics_analysis_parameter_step2/coefficient_f5_f7x_out.txt
//
//
//----------------------------------
//--- parameter F3-F5 for 1110 ----
double corrected_delta35_1110(double xdisp, double angle, double xachr){
  double r00 = (3.386991);
  double r01 = (0.370782);
  double r10 = (3040.469268);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.832263);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.003103);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  //if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  //}
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F3-F5 for 1101 ----
double corrected_delta35_1101(double xdisp, double angle, double xachr){
  double r00 = (0.995804);
  double r01 = (0.602934);
  double r10 = (3017.690477);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.057069);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.007336);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  //if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  //}
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F3-F5 for 1011 ----
double corrected_delta35_1011(double xdisp, double angle, double xachr){
  double r00 = (0.709157);
  double r01 = (0.563145);
  double r10 = (3003.184153);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.306062);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.004032);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  //if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  //}
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F3-F5 for 0111 ----
double corrected_delta35_0111(double xdisp, double angle, double xachr){
  double r00 = (0.573392);
  double r01 = (0.068184);
  double r10 = (2967.992408);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.346894);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.002880);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  //if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  //}
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F3-F5 for 1111 ----
double corrected_delta35_1111(double xdisp, double angle, double xachr){
  double r00 = (0.814540);
  double r01 = (0.634693);
  double r10 = (3014.331106);
  double r11 = (0.000000);
  double r2  = (0.000000);
  double s0  = (-0.307578);
  double s1  = (0.000000);
  double s2  = (0.000000);
  double t0  = (-0.005205);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  //if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  //}
  //return (-1.0*coeff_delta1 + sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//
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
  return (-1.0*coeff_delta1 + TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
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
  return (-1.0*coeff_delta1 + TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
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
  return (-1.0*coeff_delta1 + TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
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
  return (-1.0*coeff_delta1 + TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
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
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 + TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------




//----------------------------------
// output of step2
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 1110 ----
double corrected_delta911_1110(double xdisp, double angle, double xachr){
  double r00 = (3.024770);
  double r01 = (0.793007);
  double r10 = (-2424.089961);
  double r11 = (-13.713884);
  double r2  = (-8712.848221);
  double s0  = (0.876618);
  double s1  = (-21.811819);
  double s2  = (-954.686024);
  double t0  = (-0.049923);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 1101 ----
double corrected_delta911_1101(double xdisp, double angle, double xachr){
  double r00 = (2.539571);
  double r01 = (1.024950);
  double r10 = (-2438.530143);
  double r11 = (-16.304202);
  double r2  = (-7014.298369);
  double s0  = (0.679379);
  double s1  = (-3.182437);
  double s2  = (-1280.462808);
  double t0  = (-0.045539);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 1011 ----
double corrected_delta911_1011(double xdisp, double angle, double xachr){
  double r00 = (1.952195);
  double r01 = (1.219233);
  double r10 = (-2435.408078);
  double r11 = (-14.348818);
  double r2  = (-6662.074612);
  double s0  = (0.118665);
  double s1  = (6.713236);
  double s2  = (-770.271621);
  double t0  = (-0.011525);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 0111 ----
double corrected_delta911_0111(double xdisp, double angle, double xachr){
  double r00 = (1.397326);
  double r01 = (1.125385);
  double r10 = (-2437.111736);
  double r11 = (-20.602295);
  double r2  = (-4387.317789);
  double s0  = (0.417350);
  double s1  = (0.934252);
  double s2  = (-776.508553);
  double t0  = (-0.008579);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 1111 ----
double corrected_delta911_1111(double xdisp, double angle, double xachr){
  double r00 = (3.033011);
  double r01 = (0.813850);
  double r10 = (-2423.943484);
  double r11 = (-13.394835);
  double r2  = (-8878.690856);
  double s0  = (0.863294);
  double s1  = (-21.918855);
  double s2  = (-959.155826);
  double t0  = (-0.051419);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 2222 ----
double corrected_delta911_2222(double xdisp, double angle, double xachr){
  double r00 = (2.533538);
  double r01 = (1.024635);
  double r10 = (-2436.473781);
  double r11 = (-16.892185);
  double r2  = (-7117.813296);
  double s0  = (0.672670);
  double s1  = (-5.329864);
  double s2  = (-1373.729317);
  double t0  = (-0.045499);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------
//----------------------------------
//--- parameter F9-F11 for 3333 ----
double corrected_delta911_3333(double xdisp, double angle, double xachr){
  double r00 = (2.132829);
  double r01 = (1.152757);
  double r10 = (-2483.685102);
  double r11 = (-14.133006);
  double r2  = (-3906.932252);
  double s0  = (0.335240);
  double s1  = (5.020839);
  double s2  = (-1213.425563);
  double t0  = (-0.035463);
  double coeff_delta0 = -xdisp + (r00 + r01 * xachr) + s0*angle + t0*angle*angle;
  double coeff_delta1 = (r10 + r11 * xachr) + s1*angle;
  double coeff_delta2 = r2 + s2*angle;
  if(fabs(coeff_delta2) == 0.0){
    return -1.0*coeff_delta0/coeff_delta1; // case of no 2nd order
  }
  return (-1.0*coeff_delta1 - TMath::Sqrt((coeff_delta1)*(coeff_delta1) - 4.0 * coeff_delta0 * coeff_delta2))/(2.0 * coeff_delta2) ;
}
//----------------------------------



