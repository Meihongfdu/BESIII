#include "pipipi0Alg/util/MyUtil.h"

void setV4(NTuple::Array<double>& nt_A4, const HepLorentzVector& V4)
{
  nt_A4[0] = V4.x();
  nt_A4[1] = V4.y();
  nt_A4[2] = V4.z();
  nt_A4[3] = V4.e();
}

void setV4(NTuple::Matrix<double>& nt_M4, const HepLorentzVector& V4, int i)
{
  nt_M4[i][0] = V4.x();
  nt_M4[i][1] = V4.y();
  nt_M4[i][2] = V4.z();
  nt_M4[i][3] = V4.e();
}

HepLorentzVector getV4(RecEmcShower* shower)
{
  double eraw = shower->energy();
  double phi  = shower->phi();
  double the  = shower->theta();
  double vx   = eraw * sin(the) * cos(phi);
  double vy   = eraw * sin(the) * sin(phi);
  double vz   = eraw * cos(phi);

  HepLorentzVector V4(vx, vy, vz, eraw);

  return V4;
}


