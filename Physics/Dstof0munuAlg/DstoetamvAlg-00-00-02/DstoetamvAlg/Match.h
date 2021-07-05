#ifndef MATCH_H
#define MATCH_H
#include <iostream>
#include <vector>
#include "CLHEP/Vector/LorentzVector.h"
using CLHEP::HepLorentzVector;
using namespace std;
class Match {


public:
typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;
Match();
~Match();

inline void InputRec(int charge,
                     Vp4 V4_kp,
                     Vp4 V4_km,
                     Vp4 V4_pip, 
                     Vp4 V4_pim, 
	             Vp4 V4_gam, 
	             Vp4 V4_pi0, 
	             Vp4 V4_eta, 
	             Vp4 V4_e,
	             Vp4 V4_mu){
tagcharge=  charge ;
R4_kp    =  V4_kp  ;
R4_km    =  V4_km  ; 
R4_pip   =  V4_pip ; 
R4_pim   =  V4_pim ;
R4_gam   =  V4_gam ;
R4_pi0   =  V4_pi0 ;
R4_eta   =  V4_eta ;
R4_e     =  V4_e   ;
R4_mu    =  V4_mu  ;
};

inline void InputTruDsp(Vp4 V4_kp,
                        Vp4 V4_km,
                        Vp4 V4_pip, 
                        Vp4 V4_pim, 
	                Vp4 V4_gam, 
	                Vp4 V4_pi0, 
	                Vp4 V4_eta, 
	                Vp4 V4_e,
	                Vp4 V4_mu){
Tp4_kp    =  V4_kp  ;
Tp4_km    =  V4_km  ; 
Tp4_pip   =  V4_pip ; 
Tp4_pim   =  V4_pim ;
Tp4_gam   =  V4_gam ;
Tp4_pi0   =  V4_pi0 ;
Tp4_eta   =  V4_eta ;
Tp4_e    =  V4_e  ;
Tp4_mu   =  V4_mu ;
};

inline void InputTruDsm(Vp4 V4_kp,
                        Vp4 V4_km,
                        Vp4 V4_pip, 
                        Vp4 V4_pim, 
	                Vp4 V4_gam, 
	                Vp4 V4_pi0, 
	                Vp4 V4_eta, 
	                Vp4 V4_e,
	                Vp4 V4_mu){
Tm4_kp    =  V4_kp  ;
Tm4_km    =  V4_km  ; 
Tm4_pip   =  V4_pip ; 
Tm4_pim   =  V4_pim ;
Tm4_gam   =  V4_gam ;
Tm4_pi0   =  V4_pi0 ;
Tm4_eta   =  V4_eta ;
Tm4_e     =  V4_e   ;
Tm4_mu    =  V4_mu  ;
};

double match();

private: 
double MaxAngle(double angle[4][4]);
double compare(double Angle1,double Angle2,double Angle3,double Angle4);
int tagcharge;

Vp4 R4_kp;
Vp4 R4_km;
Vp4 R4_pip;
Vp4 R4_pim;
Vp4 R4_gam;
Vp4 R4_pi0;
Vp4 R4_eta;
Vp4 R4_e;
Vp4 R4_mu;

Vp4 Tp4_kp;
Vp4 Tp4_km;
Vp4 Tp4_pip;
Vp4 Tp4_pim;
Vp4 Tp4_gam;
Vp4 Tp4_pi0;
Vp4 Tp4_eta;
Vp4 Tp4_e;
Vp4 Tp4_mu;

Vp4 Tm4_kp;
Vp4 Tm4_km;
Vp4 Tm4_pip;
Vp4 Tm4_pim;
Vp4 Tm4_gam;
Vp4 Tm4_pi0;
Vp4 Tm4_eta;
Vp4 Tm4_e;
Vp4 Tm4_mu;


};

#endif
