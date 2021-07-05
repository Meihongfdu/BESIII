#ifndef __HelAng_h__
#define __HelAng_h__

#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/Rotation.h"

#include <fstream>

class HelAng
{
  public:
    virtual ~HelAng() {};

    HelAng(  TLorentzVector & p4_1, TLorentzVector & p4_2, TLorentzVector & p4_3)
    {
   
p4_2.Boost(- p4_1.BoostVector());
p4_3.Boost(- p4_1.BoostVector());
p4_3.Boost(- p4_2.BoostVector());
double mom_Gamma=0.0;
double mom_Beta=p4_2.Theta();  
double mom_Alpha=p4_2.Phi();  
TLorentzRotation rot1,rot2,rot3,Trans;
rot1.RotateZ(mom_Gamma);
rot2.RotateY(-mom_Beta);
rot3.RotateZ(-mom_Alpha);
Trans=rot1*rot2 * rot3;
p4_1=Trans*p4_1;
p4_2=Trans*p4_2;
p4_3=Trans*p4_3;


_theta=p4_3.Theta();
_phi=p4_3.Phi();
_Arg=p4_3.Angle(p4_2.Vect());
// _phi=rotate(p4p);
	}
    HelAng(const HepLorentzVector & p_1, const HepLorentzVector & p_2, const HepLorentzVector & p_3)
    {
   HepLorentzVector p4_1(p_1), p4_2(p_2), p4_3(p_3);
p4_2.boost(- p4_1.boostVector());
p4_3.boost(- p4_1.boostVector());
p4_3.boost(- p4_2.boostVector());
double mom_Gamma=0.0;
double mom_Beta=p4_2.theta();  
double mom_Alpha=p4_2.phi();  
HepRotation rot1,rot2,rot3,Trans;
rot1.rotateZ(mom_Gamma);
rot2.rotateY(-mom_Beta);
rot3.rotateZ(-mom_Alpha);
Trans=rot1*rot2 * rot3;
p4_1=Trans*p4_1;
p4_2=Trans*p4_2;
p4_3=Trans*p4_3;


_theta=p4_3.theta();
_phi=p4_3.phi();
_Arg=p4_3.angle(p4_2.vect());
// _phi=rotate(p4p);
	}

    double HelTheta() const { return _theta; }
    double HelPhi  () const { return _phi; }
    double HelArg  () const { return _Arg; }


  public:
    TLorentzVector Rotate(TLorentzVector p1)
    {
		return m;
    }
    

  private:

   TLorentzVector _p4parent; // parent momentum in its parent CM system
   TLorentzVector _p4daug;   // daughter momentum in its parent CM system
   TLorentzVector _rotatep4p; // the parent momentum in Hel system by rotation
   TLorentzVector _rotatep4d; // the daughter momentum in Hel. system by rotation

   double _theta;
   double _phi;
   double _Arg;
};

#endif

