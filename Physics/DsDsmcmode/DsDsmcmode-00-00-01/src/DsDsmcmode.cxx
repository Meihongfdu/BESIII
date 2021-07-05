#include "DsDsmcmode/DsDsmcmode.h"

DsDsmcmode* DsDsmcmode::m_pointer = 0;

DsDsmcmode* DsDsmcmode::instance() {
  if(!m_pointer) m_pointer = new DsDsmcmode();
  return m_pointer;
}

void DsDsmcmode::D0mcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 421)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 421;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=421) continue;

      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

//      cout<<"TEST D0  mode AAA+:::"<<pdgid<<endl;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid==-321)      NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]==-321) {ChargK = -1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

/*
if(Nint==2) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;
if(Nint==3) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
if(Nint==4) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<endl;
if(Nint==5) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<endl;
if(Nint==6) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<","<<MctkPID[5]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]==    211&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(117);} // K-  pi+                      PHSP;
  if(MctkPID[0]==    310&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(118);} // K_S0   pi0                   PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(119);} // K_L0   pi0                   PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(120);} // anti-K0   eta                PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(121);} // anti-K0   eta'               PHSP;
  if(MctkPID[0]==    223&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(122);} // omega_A anti-K0              SVS;
  if(MctkPID[0]==    221&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(123);} // anti-K*0 eta                 SVS;
  if(MctkPID[0]==    331&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(124);} // anti-K*0 eta'                SVS;
  if(MctkPID[0]==  20213&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(125);} // a_1+ K-                      SVS;
  if(MctkPID[0]==    213&&MctkPID[1]==  -323) { SelectionValid = true; Mcmode.push_back(126);} // K*- rho+                     SVV_HELAMP  0.5 0.0 1.0 0.0 0.5 0.0;
  if(MctkPID[0]==    113&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(127);} // anti-K*0 rho0                SVV_HELAMP  1.0 0.0 0.0 0.0 1.0 0.0;
  if(MctkPID[0]==    223&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(128);} // anti-K*0 omega               SVV_HELAMP  1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    111&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(130);} // K*BR pi0                     SVS;
  if(MctkPID[0]==    211&&MctkPID[1]==-10323) { SelectionValid = true; Mcmode.push_back(131);} // K_1- pi+                     SVS;
  if(MctkPID[0]==    111&&MctkPID[1]==-10313) { SelectionValid = true; Mcmode.push_back(132);} // anti-K_10 pi0                SVS;
  if(MctkPID[0]==  10111&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(154);} // anti-K0 a_00                 PHSP;
  if(MctkPID[0]==  10211&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(155);} // K- a_0+                      PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(161);} // phi anti-K0                  SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(162);} // phi anti-K*0                 SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    333&&MctkPID[1]==   313) { SelectionValid = true; Mcmode.push_back(172);} // phi K*0                      SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    321&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(173);} // K+  K-                       PHSP;
  if(MctkPID[0]==    310&&MctkPID[1]==   310) { SelectionValid = true; Mcmode.push_back(174);} // K_S0 K_S0                    PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]==   130) { SelectionValid = true; Mcmode.push_back(175);} // K_L0 K_L0                    PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(176);} // K*0 anti-K0                  SVS;
  if(MctkPID[0]==    311&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(177);} // anti-K*0 K0                  SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==  -323) { SelectionValid = true; Mcmode.push_back(178);} // K*- K+                       SVS;
  if(MctkPID[0]==    323&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(179);} // K*+ K-                       SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(181);} // phi pi0                      SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(183);} // phi rho0	               SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==  10323&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(193);} // K_1+ K-                      SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==-10323) { SelectionValid = true; Mcmode.push_back(194);} // K_1- K+                      SVS;
  if(MctkPID[0]==  20323&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(195);} // K'_1+ K-                     SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==-20323) { SelectionValid = true; Mcmode.push_back(196);} // K'_1- K+                     SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(198);} // phi eta                      SVS;
  if(MctkPID[0]==    211&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(199);} // pi+ pi-                      PHSP;
  if(MctkPID[0]==    111&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(200);} // pi0 pi0                      PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(201);} // eta pi0                      PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(202);} // eta' pi0                     PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(204);} // eta eta                      PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(205);} // eta eta'                     PHSP;
  if(MctkPID[0]==    213&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(206);} // rho+ pi-                     SVS;
  if(MctkPID[0]==    211&&MctkPID[1]==  -213) { SelectionValid = true; Mcmode.push_back(207);} // rho- pi+                     SVS;
  if(MctkPID[0]==    113&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(208);} // rho0 pi0                     SVS;
  if(MctkPID[0]==    113&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(211);} // rho0 rho0                    SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    213&&MctkPID[1]==  -213) { SelectionValid = true; Mcmode.push_back(214);} // rho+ rho-                    SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    321&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(223);} // pi- K+                       PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]==    22) { SelectionValid = true; Mcmode.push_back(226);} // phi gamma                    HELAMP 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==     22&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(227);} // anti-K*0 gamma               HELAMP 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==  10221&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(229);} // anti-K0 f'_0	               PHSP;
  if(MctkPID[0]==9010221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(230);} // f_0 pi0                      PHSP;
  if(MctkPID[0]==  30213&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(233);} // rho(2S)+ pi-                 PHSP;
  if(MctkPID[0]==  30113&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(234);} // rho(2S)0 pi0                 PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==-30213) { SelectionValid = true; Mcmode.push_back(235);} // rho(2S)- pi+                 PHSP;
  if(MctkPID[0]==  10221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(236);} // f'_0 pi0                     PHSP;
  if(MctkPID[0]==  50221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(237);} // f_0(1500) pi0                PHSP;
  if(MctkPID[0]==    225&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(238);} // f_2 pi0                      PHSP;
  if(MctkPID[0]==  20213&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(239);} // a_1+ pi-                     PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(241);} // K*0 anti-K*0                 PHSP;
 }

 if(Nint==3) {
  if(MctkPID[0]==     12&&MctkPID[1]== -11&&MctkPID[2]==  -323) { SelectionValid = true; Mcmode.push_back(101);} // K*-   e+  nu_e               PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==     12&&MctkPID[1]== -11&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(102);} // K-    e+  nu_e               PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==     12&&MctkPID[1]== -11&&MctkPID[2]==-10323) { SelectionValid = true; Mcmode.push_back(103);} // K_1-  e+  nu_e               PHOTOS   ISGW2;
  if(MctkPID[0]==     12&&MctkPID[1]== -11&&MctkPID[2]==  -325) { SelectionValid = true; Mcmode.push_back(104);} // K_2*- e+  nu_e               PHOTOS   ISGW2;
  if(MctkPID[0]==     12&&MctkPID[1]== -11&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(107);} // pi-   e+  nu_e               PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==     12&&MctkPID[1]== -11&&MctkPID[2]==  -213) { SelectionValid = true; Mcmode.push_back(108);} // rho-  e+  nu_e               PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==     14&&MctkPID[1]== -13&&MctkPID[2]==  -323) { SelectionValid = true; Mcmode.push_back(109);} // K*-   mu+ nu_mu              PHOTOS  SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==     14&&MctkPID[1]== -13&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(110);} // K-    mu+ nu_mu              PHOTOS  SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==     14&&MctkPID[1]== -13&&MctkPID[2]==-10323) { SelectionValid = true; Mcmode.push_back(111);} // K_1-  mu+ nu_mu              PHOTOS  ISGW2;
  if(MctkPID[0]==     14&&MctkPID[1]== -13&&MctkPID[2]==  -325) { SelectionValid = true; Mcmode.push_back(112);} // K_2*- mu+ nu_mu              PHOTOS  ISGW2;
  if(MctkPID[0]==     14&&MctkPID[1]== -13&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(115);} // pi-   mu+ nu_mu              PHOTOS  SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==     14&&MctkPID[1]== -13&&MctkPID[2]==  -213) { SelectionValid = true; Mcmode.push_back(116);} // rho-  mu+ nu_mu              PHOTOS  SLPOLE_Dtorholnu;
  if(MctkPID[0]==    211&&MctkPID[1]== 111&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(129);} // K-  pi+  pi0                 D_DALITZ;
  if(MctkPID[0]==    211&&MctkPID[1]==-211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(133);} // anti-K0   pi+  pi-           D_DALITZ;
  if(MctkPID[0]==    111&&MctkPID[1]== 111&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(134);} // anti-K0   pi0  pi0           PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==-211&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(135);} // anti-K*0 pi+  pi-            PHSP;
  if(MctkPID[0]==    111&&MctkPID[1]== 111&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(136);} // anti-K*0 pi0  pi0            PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]== 111&&MctkPID[2]==  -323) { SelectionValid = true; Mcmode.push_back(137);} // K*- pi+  pi0                 PHSP;
  if(MctkPID[0]==    213&&MctkPID[1]== 111&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(138);} // K-  rho+ pi0                 PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]== 113&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(139);} // K-  pi+  rho0                PHSP;
  if(MctkPID[0]==    223&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(140);} // K-  pi+  omega               PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(141);} // K-  pi+  eta                 PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(142);} // K-  pi+  eta'                PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]== 111&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(143);} // anti-K0 pi0 eta              PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]== 113&&MctkPID[2]==  -323) { SelectionValid = true; Mcmode.push_back(157);} // K*- rho0 pi+                 PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(150);} // K- pi+ phi                   PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-311&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(163);} // anti-K0   K+   K-            PHSP;
  if(MctkPID[0]==    310&&MctkPID[1]== 310&&MctkPID[2]==   310) { SelectionValid = true; Mcmode.push_back(164);} // K_S0 K_S0  K_S0              PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]== 130&&MctkPID[2]==   130) { SelectionValid = true; Mcmode.push_back(165);} // K_L0 K_L0  K_L0              PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-313&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(170);} // K+ K- anti-K*0               PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 111&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(180);} // K+ K- pi0		         PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(182);} // phi pi+  pi-                 PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(187);} // K0 K- pi+                    PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(188);} // anti-K0 K+ pi-               PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(191);} // K*0 K- pi+                   PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-211&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(192);} // anti-K*0 K+ pi-              PHSP;
  if(MctkPID[0]==9010221&&MctkPID[1]== 111&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(209);} // f_0 pi0 pi0                  PHSP;
  if(MctkPID[0]==    111&&MctkPID[1]== 111&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(210);} // pi0  pi0  pi0                PHSP;
  if(MctkPID[0]==    223&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(216);} // omega pi+ pi-                PHSP;
  if(MctkPID[0]==    113&&MctkPID[1]== 113&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(218);} // rho0 rho0 pi0                PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(221);} // pi+ pi- eta	                 PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(222);} // pi+ pi- eta'                 PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 111&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(224);} // pi- K+  pi0                  PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 113&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(231);} // K+ K- rho0                   PHSP;
  if(MctkPID[0]==9010221&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(232);} // f_0 pi+ pi-                  PHSP;
  if(MctkPID[0]==    225&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(240);} // f_2 pi+ pi-                  PHSP;
 }

 if(Nint==4) {
  if(MctkPID[0]==111&&MctkPID[1]== 12&&MctkPID[2]== -11&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(105);} // K-  pi0 e+ nu_e              PHSP;
  if(MctkPID[0]== 12&&MctkPID[1]==-11&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(106);} // anti-K0 pi- e+ nu_e          PHSP;
  if(MctkPID[0]==111&&MctkPID[1]== 14&&MctkPID[2]== -13&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(113);} // K-  pi0 mu+ nu_mu            PHSP;
  if(MctkPID[0]== 14&&MctkPID[1]==-13&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(114);} // anti-K0 pi- mu+ nu_mu        PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(144);} // anti-K0 pi+ pi- eta          PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(145);} // anti-K0 pi0 pi0 eta          PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(146);} // K-  pi+  pi+   pi-           PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(147);} // anti-K0   pi+  pi-   pi0     PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(148);} // K-  pi+  pi0   pi0           PHSP;
  if(MctkPID[0]==111&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(149);} // anti-K0   pi0  pi0   pi0     PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==113&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(156);} // anti-K0 rho0 pi+ pi-         PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-323) { SelectionValid = true; Mcmode.push_back(158);} // K*- pi+ pi+ pi-              PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==130&&MctkPID[2]== 130&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(166);} // K_L0 K_L0 K+ pi-	            PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==130&&MctkPID[2]== 130&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(167);} // K_L0 K_L0 K- pi+	            PHSP;
  if(MctkPID[0]==310&&MctkPID[1]==310&&MctkPID[2]== 211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(168);} // K_S0 K_S0 K- pi+	            PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==310&&MctkPID[2]== 310&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(169);} // K_S0 K_S0 K+ pi-	            PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-321&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(171);} // K+ K- K- pi+                 PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(184);} // K+  K-   pi0  pi0            PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(185);} // anti-K0   K0   pi+  pi-      PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(186);} // anti-K0   K0   pi0  pi0      PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(189);} // anti-K0 K+ pi- pi0           PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(190);} // K0 K- pi+ pi0                PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(203);} // eta pi+ pi- pi0              PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(212);} // pi+  pi+  pi-  pi-           PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(215);} // pi+  pi-  pi0  pi0           PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==113&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(217);} // rho0 pi+ pi- pi0	            PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(225);} // pi- K+ pi- pi+               PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-313) { SelectionValid = true; Mcmode.push_back(228);} // anti-K*0 pi+ pi- pi0         PHSP;
  }

 if(Nint==5) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(160);}  // K-  pi+  pi+   pi-   pi0     PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(151);}  // K-  pi+  pi0   pi0   pi0     PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-311) { SelectionValid = true; Mcmode.push_back(152);}  // anti-K0 pi+ pi- pi0 pi0      PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(197);}  // K+ K- pi+ pi- pi0            PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(219);}  // pi+  pi-  pi0  pi0  pi0      PHSP;
 }																	      
																	      
 if(Nint==6) {																      
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211&&MctkPID[5]==-311) { SelectionValid = true; Mcmode.push_back(153);}  // anti-K0  pi+ pi- pi0 pi0 pi0 PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-211&&MctkPID[5]==-321) { SelectionValid = true; Mcmode.push_back(159);}  // K- pi+ pi+ pi+ pi- pi-       PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(213);}  // pi+ pi+ pi- pi- pi0 pi0      PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(220);}  // pi+ pi+ pi+ pi- pi- pi-      PHSP;
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(1002);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(1003);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(1004);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(1005);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(1006);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(1007);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(1008);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(1009);

}
}

void DsDsmcmode::D0bmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-421)  {ChargD = -1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -421;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=-421) continue;
      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

//      cout<<"TEST D0b mode BBB-:::"<<pdgid<<endl;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid== 321)           NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]== 321) {ChargK =  1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

/*
if(Nint==2) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;
if(Nint==3) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
if(Nint==4) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<endl;
if(Nint==5) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<endl;
if(Nint==6) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<","<<MctkPID[5]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]==    321&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(-117);} // K+  pi-                      PHSP;
  if(MctkPID[0]==    310&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-118);}	// K_S0   pi0                   PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-119);}	// K_L0   pi0                   PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(-120);}	// K0   eta                     PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==   311) { SelectionValid = true; Mcmode.push_back(-121);}	// K0   eta'                    PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]==   223) { SelectionValid = true; Mcmode.push_back(-122);}	// omega_A K0                   SVS;
  if(MctkPID[0]==    313&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(-123);}	// K*0 eta                      SVS;
  if(MctkPID[0]==    331&&MctkPID[1]==   313) { SelectionValid = true; Mcmode.push_back(-124);}	// K*0 eta'                     SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==-20213) { SelectionValid = true; Mcmode.push_back(-125);}	// a_1- K+                      SVS;
  if(MctkPID[0]==    323&&MctkPID[1]==  -213) { SelectionValid = true; Mcmode.push_back(-126);}	// K*+ rho-                     SVV_HELAMP  0.5 0.0 1.0 0.0 0.5 0.0;
  if(MctkPID[0]==    313&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(-127);}	// K*0 rho0                     SVV_HELAMP  1.0 0.0 0.0 0.0 1.0 0.0;
  if(MctkPID[0]==    313&&MctkPID[1]==   223) { SelectionValid = true; Mcmode.push_back(-128);}	// K*0 omega                    SVV_HELAMP  1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    313&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-130);}	// K*0R pi0                     SVS;
  if(MctkPID[0]==  10323&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(-131);}	// K_1+ pi-                     SVS;
  if(MctkPID[0]==  10313&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-132);}	// K_10 pi0                     SVS;
  if(MctkPID[0]==  10111&&MctkPID[1]==   311) { SelectionValid = true; Mcmode.push_back(-154);}	// K0 a_00                      PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-10211) { SelectionValid = true; Mcmode.push_back(-155);}	// K+ a_0-                      PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]==   311) { SelectionValid = true; Mcmode.push_back(-161);}	// phi K0                       SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   313) { SelectionValid = true; Mcmode.push_back(-162);}	// phi K*0                      SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    333&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(-172);}	// phi anti-K*0                 SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    321&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(-173);}	// K-  K+                       PHSP;
  if(MctkPID[0]==    310&&MctkPID[1]==   310) { SelectionValid = true; Mcmode.push_back(-174);}	// K_S0 K_S0                    PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]==   130) { SelectionValid = true; Mcmode.push_back(-175);}	// K_L0 K_L0                    PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(-176);}	// anti-K*0 K0                  SVS;
  if(MctkPID[0]==    313&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(-177);}	// K*0 anti-K0                  SVS;
  if(MctkPID[0]==    323&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(-178);}	// K*+ K-                       SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==  -323) { SelectionValid = true; Mcmode.push_back(-179);}	// K*- K+                       SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-181);}	// phi pi0                      SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(-183);}	// phi rho0                     SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    321&&MctkPID[1]==-10323) { SelectionValid = true; Mcmode.push_back(-193);}	// K_1- K+                      SVS;
  if(MctkPID[0]==  10323&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(-194);}	// K_1+ K-                      SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==-20323) { SelectionValid = true; Mcmode.push_back(-195);}	// K'_1- K+                     SVS;
  if(MctkPID[0]==  20323&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(-196);}	// K'_1+ K-                     SVS;
  if(MctkPID[0]==    333&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(-198);}	// phi eta                      SVS;
  if(MctkPID[0]==    211&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(-199);}	// pi+ pi-                      PHSP;
  if(MctkPID[0]==    111&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-200);}	// pi0 pi0                      PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-201);}	// eta pi0                      PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-202);}	// eta' pi0                     PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(-204);}	// eta eta                      PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(-205);}	// eta eta'                     PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==  -213) { SelectionValid = true; Mcmode.push_back(-206);}	// rho- pi+                     SVS;
  if(MctkPID[0]==    213&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(-207);}	// rho+ pi-                     SVS;
  if(MctkPID[0]==    113&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-208);}	// rho0 pi0                     SVS;
  if(MctkPID[0]==    113&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(-211);}	// rho0 rho0                    SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    213&&MctkPID[1]==  -213) { SelectionValid = true; Mcmode.push_back(-214);}	// rho- rho+                    SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    211&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(-223);}	// pi+ K-                       PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]==    22) { SelectionValid = true; Mcmode.push_back(-226);}	// phi gamma                    HELAMP 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    313&&MctkPID[1]==    22) { SelectionValid = true; Mcmode.push_back(-227);}	// K*0 gamma                    HELAMP 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==  10221&&MctkPID[1]==   311) { SelectionValid = true; Mcmode.push_back(-229);}	// K0 f'_0                      PHSP;
  if(MctkPID[0]==9010221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-230);}	// f_0 pi0                      PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==-30213) { SelectionValid = true; Mcmode.push_back(-233);}	// rho(2S)- pi+                 PHSP;
  if(MctkPID[0]==  30113&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-234);}	// rho(2S)0 pi0                 PHSP;
  if(MctkPID[0]==  30213&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(-235);}	// rho(2S)+ pi-                 PHSP;
  if(MctkPID[0]==  10221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-236);}	// f'_0 pi0                     PHSP;
  if(MctkPID[0]==  50221&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-237);}	// f_0(1500) pi0                PHSP;
  if(MctkPID[0]==    225&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(-238);}	// f_2 pi0                      PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==-20213) { SelectionValid = true; Mcmode.push_back(-239);}	// a_1- pi+                     PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(-241);}	// anti-K*0 K*0                 PHSP;
 }

 if(Nint==3) {
  if(MctkPID[0]==    323&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(-101);} // K*+   e-  anti-nu_e          PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==    321&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(-102);} // K+    e-  anti-nu_e          PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==  10323&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(-103);} // K_1+  e-  anti-nu_e          PHOTOS   ISGW2;
  if(MctkPID[0]==    325&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(-104);} // K_2*+ e-  anti-nu_e          PHOTOS   ISGW2;
  if(MctkPID[0]==    211&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(-107);} // pi+   e-  anti-nu_e          PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==    213&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(-108);} // rho+  e-  anti-nu_e          PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==    323&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(-109);} // K*+   mu- anti-nu_mu         PHOTOS  SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==    321&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(-110);} // K+    mu- anti-nu_mu         PHOTOS  SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==  10323&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(-111);} // K_1+  mu- anti-nu_mu         PHOTOS  ISGW2;
  if(MctkPID[0]==    325&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(-112);} // K_2*+ mu- anti-nu_mu         PHOTOS  ISGW2;
  if(MctkPID[0]==    211&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(-115);} // pi+   mu- anti-nu_mu         PHOTOS  SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==    213&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(-116);} // rho+  mu- anti-nu_mu         PHOTOS  SLPOLE_Dtorholnu;
  if(MctkPID[0]==    321&&MctkPID[1]== 111&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-129);} // K+  pi-  pi0                 D_DALITZ;
  if(MctkPID[0]==    311&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-133);} // K0  pi+  pi-                 D_DALITZ;
  if(MctkPID[0]==    311&&MctkPID[1]== 111&&MctkPID[2]==  111) { SelectionValid = true; Mcmode.push_back(-134);} // K0  pi0  pi0                 PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-135);} // K*0 pi+  pi-                 PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]== 111&&MctkPID[2]==  111) { SelectionValid = true; Mcmode.push_back(-136);} // K*0 pi0  pi0                 PHSP;
  if(MctkPID[0]==    323&&MctkPID[1]== 111&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-137);} // K*+ pi-  pi0                 PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 111&&MctkPID[2]== -213) { SelectionValid = true; Mcmode.push_back(-138);} // K+ rho-  pi0                 PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 113&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-139);} // K+  pi-  rho0                PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 223&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-140);} // K+  pi-  omega               PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 221&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-141);} // K+  pi-  eta                 PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]== 321&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-142);} // K+  pi-  eta'                PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]== 221&&MctkPID[2]==  111) { SelectionValid = true; Mcmode.push_back(-143);} // K0 pi0 eta                   PHSP;
  if(MctkPID[0]==    323&&MctkPID[1]== 113&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-157);} // K*+ rho0 pi-                 PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]== 321&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-150);} // K+ pi- phi                   PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 311&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-163);} // K0   K-   K+                 PHSP;
  if(MctkPID[0]==    310&&MctkPID[1]== 310&&MctkPID[2]==  310) { SelectionValid = true; Mcmode.push_back(-164);} // K_S0 K_S0  K_S0              PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]== 130&&MctkPID[2]==  130) { SelectionValid = true; Mcmode.push_back(-165);} // K_L0 K_L0  K_L0              PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 313&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-170);} // K- K+ K*0                    PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 111&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-180);} // K- K+ pi0  	                 PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-182);} // phi pi-  pi+                 PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-211&&MctkPID[2]== -311) { SelectionValid = true; Mcmode.push_back(-187);} // anti-K0 K+ pi-               PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]== 211&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-188);} // K0 K- pi+                    PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==-211&&MctkPID[2]== -313) { SelectionValid = true; Mcmode.push_back(-191);} // anti-K*0 K+ pi-              PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]== 211&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-192);} // K*0 K- pi+                   PHSP;
  if(MctkPID[0]==9010221&&MctkPID[1]== 111&&MctkPID[2]==  111) { SelectionValid = true; Mcmode.push_back(-209);} // f_0 pi0 pi0                  PHSP;
  if(MctkPID[0]==    111&&MctkPID[1]== 111&&MctkPID[2]==  111) { SelectionValid = true; Mcmode.push_back(-210);} // pi0  pi0  pi0                PHSP;
  if(MctkPID[0]==    223&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-216);} // omega pi- pi+                PHSP;
  if(MctkPID[0]==    113&&MctkPID[1]== 113&&MctkPID[2]==  111) { SelectionValid = true; Mcmode.push_back(-218);} // rho0 rho0 pi0                PHSP;
  if(MctkPID[0]==    221&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-221);} // pi- pi+ eta                  PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-222);} // pi- pi+ eta'                 PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]== 111&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-224);} // pi+ K-  pi0                  PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]== 113&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(-231);} // K- K+ rho0	                 PHSP;
  if(MctkPID[0]==9010221&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-232);} // f_0 pi- pi+                  PHSP;
  if(MctkPID[0]==    225&&MctkPID[1]== 211&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(-240);} // f_2 pi- pi+                  PHSP;
 }

 if(Nint==4) {
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==  11&&MctkPID[3]== -12) { SelectionValid = true; Mcmode.push_back(-105);} // K+ pi0 e-  anti-nu_e         PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==  11&&MctkPID[3]== -12) { SelectionValid = true; Mcmode.push_back(-106);} // K0 pi+ e-  anti-nu_e         PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==  13&&MctkPID[3]== -14) { SelectionValid = true; Mcmode.push_back(-113);} // K+ pi0 mu- anti-nu_mu        PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==  13&&MctkPID[3]== -14) { SelectionValid = true; Mcmode.push_back(-114);} // K0 pi+ mu- anti-nu_mu        PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==221&&MctkPID[2]== 211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-144);} // K0 pi- pi+ eta               PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==221&&MctkPID[2]== 111&&MctkPID[3]== 111) { SelectionValid = true; Mcmode.push_back(-145);} // K0 pi0 pi0 eta               PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-146);} // K+  pi-  pi-   pi+           PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-147);} // K0  pi-  pi+   pi0           PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-148);} // K+  pi-  pi0   pi0           PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]== 111) { SelectionValid = true; Mcmode.push_back(-149);} // K0  pi0  pi0   pi0           PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 113&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-156);} // K0 rho0  pi+   pi-           PHSP;
  if(MctkPID[0]==323&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-158);} // K*+  pi- pi- pi+             PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==130&&MctkPID[2]== 130&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-166);} // K_L0 K_L0 K- pi+	     PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==130&&MctkPID[2]== 130&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-167);} // K_L0 K_L0 K+ pi-             PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==310&&MctkPID[2]== 310&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-168);} // K_S0 K_S0 K+ pi-             PHSP;
  if(MctkPID[0]==310&&MctkPID[1]==310&&MctkPID[2]== 211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-169);} // K_S0 K_S0 K- pi+             PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==321&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-171);} // K-  K+  K+  pi-              PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-184);} // K-  K+ pi0  pi0              PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(-185);} // K0  anti-K0   pi-  pi+       PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(-186);} // K0  anti-K0   pi0  pi0       PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-189);} // K0 K- pi+ pi0                PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(-190);} // anti-K0 K+ pi- pi0           PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-203);} // eta pi- pi+ pi0              PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-212);} // pi+  pi+  pi-  pi-           PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-215);} // pi+  pi-  pi0  pi0           PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==113&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-217);} // rho0 pi+ pi- pi0             PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-225);} // pi+ K- pi+ pi-               PHSP;
  if(MctkPID[0]==313&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-228);} // K*0 pi- pi+ pi0              PHSP;
  }

 if(Nint==5) {
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-160);} // K+  pi-  pi-   pi+   pi0     PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-151);} // K+  pi-  pi0   pi0   pi0     PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-152);} // K0 pi- pi+ pi0 pi0           PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(-197);} // K+ K- pi+ pi- pi0            PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-219);} // pi+  pi-  pi0  pi0  pi0      PHSP;
 }																	      
																	      
 if(Nint==6) {																      
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]== 111&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(-153);} // K0  pi- pi+ pi0 pi0 pi0      PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(-159);} // K+ pi- pi- pi- pi+ pi+       PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(-213);} // pi+ pi+ pi- pi- pi0 pi0      PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(-220);} // pi+ pi+ pi+ pi- pi- pi-      PHSP;
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(-1002);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(-1003);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(-1004);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(-1005);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(-1006);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(-1007);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(-1008);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(-1009);

}
}

void DsDsmcmode::Dpmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 411)  {ChargD = 1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 411;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=411) continue;
      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());
      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

/*
if(Nint==2) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;
if(Nint==3) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
if(Nint==4) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<endl;
if(Nint==5) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<endl;
if(Nint==6) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<","<<MctkPID[5]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]==     14&&MctkPID[1]==   -13) { SelectionValid = true; Mcmode.push_back(501);} // mu+ nu_mu                       PHOTOS   SLN;
  if(MctkPID[0]==     16&&MctkPID[1]==   -15) { SelectionValid = true; Mcmode.push_back(502);} // tau+ nu_tau                     SLN;
  if(MctkPID[0]==    310&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(523);} // K_S0 pi+                        PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==   130) { SelectionValid = true; Mcmode.push_back(524);} // K_L0 pi+                        PHSP;
  if(MctkPID[0]==    213&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(527);} // anti-K*0 rho+                   SVV_HELAMP  1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    211&&MctkPID[1]==-20313) { SelectionValid = true; Mcmode.push_back(529);} // anti-K'_10  pi+                 SVS;
  if(MctkPID[0]==  20213&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(538);} // a_1+ anti-K0                    SVS;
  if(MctkPID[0]==  20213&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(542);} // a_1+ anti-K*0                   SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    211&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(548);} // pi0 pi+                         PHSP;
  if(MctkPID[0]==    211&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(549);} // rho0 pi+                        SVS;
  if(MctkPID[0]==9010221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(551);} // f_0 pi+                         PHSP;
  if(MctkPID[0]==  10221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(552);} // f'_0      pi+                   PHSP;
  if(MctkPID[0]==    225&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(553);} // f_2 pi+                         STS;
  if(MctkPID[0]==  50221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(554);} // f_0(1500) pi+                   PHSP;
  if(MctkPID[0]==    213&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(555);} // rho+ pi0                        SVS;
  if(MctkPID[0]==    213&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(557);} // rho0 rho+                       SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(561);} // eta pi+                         PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(563);} // eta' pi+                        PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(572);} // anti-K0   K+                    PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(573);} // phi pi+                         SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(574);} // anti-K*0  K+                    SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==-10311) { SelectionValid = true; Mcmode.push_back(575);} // anti-K_0*0 K+                   PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==  -315) { SelectionValid = true; Mcmode.push_back(576);} // anti-K_2*0 K+                   STS;
  if(MctkPID[0]==    323&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(581);} // anti-K*0 K*+                    SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    333&&MctkPID[1]==   213) { SelectionValid = true; Mcmode.push_back(585);} // phi rho+                        SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    323&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(587);} // K*+  anti-K0                    SVS;
  if(MctkPID[0]==    321&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(589);} // K+ pi0                          PHSP;
  if(MctkPID[0]==    321&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(590);} // rho0 K+                         SVS;
  if(MctkPID[0]==    313&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(591);} // K*0 pi+                         SVS;
  if(MctkPID[0]==9010221&&MctkPID[1]==   321) { SelectionValid = true; Mcmode.push_back(592);} // K+ f_0                          PHSP;
  if(MctkPID[0]==    315&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(593);} // K_2*0 pi+                       STS;
 }

 if(Nint==3) {
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(503);} // anti-K0    e+  nu_e             PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==-10313) { SelectionValid = true; Mcmode.push_back(504);} // anti-K_10  e+  nu_e             PHOTOS   ISGW2;
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(505);} // anti-K*0   e+  nu_e             PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==  -315) { SelectionValid = true; Mcmode.push_back(506);} // anti-K_2*0 e+  nu_e             PHOTOS   ISGW2;
  if(MctkPID[0]==111&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(508);} // pi0        e+  nu_e             PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==221&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(509);} // eta        e+  nu_e             PHOTOS   SLBKPOLE_Dtoetalnu;
  if(MctkPID[0]==331&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(510);} // eta'       e+  nu_e             PHOTOS   SLBKPOLE_Dtoetaplnu;
  if(MctkPID[0]==113&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(511);} // rho0       e+  nu_e             PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==223&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(512);} // omega      e+  nu_e             PHOTOS   SLPOLE_Dtoomegalnu;
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(513);} // anti-K0    mu+ nu_mu            PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==-10313) { SelectionValid = true; Mcmode.push_back(514);} // anti-K_10  mu+ nu_mu            PHOTOS   ISGW2;
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(515);} // anti-K*0   mu+ nu_mu            PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==  -315) { SelectionValid = true; Mcmode.push_back(516);} // anti-K_2*0 mu+ nu_mu            PHOTOS   ISGW2;
  if(MctkPID[0]==111&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(518);} // pi0        mu+ nu_mu            PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==221&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(519);} // eta        mu+ nu_mu            PHOTOS   SLBKPOLE_Dtoetalnu;
  if(MctkPID[0]==331&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(520);} // eta'       mu+ nu_mu            PHOTOS   SLBKPOLE_Dtoetaplnu;
  if(MctkPID[0]==113&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(521);} // rho0       mu+ nu_mu            PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==223&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(522);} // omega      mu+ nu_mu            PHOTOS   SLPOLE_Dtoomegalnu;
  if(MctkPID[0]==211&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(525);} // K-  pi+  pi+                    D_DALITZ;
  if(MctkPID[0]==211&&MctkPID[1]== 111&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(526);} // anti-K0   pi+  pi0              D_DALITZ;
  if(MctkPID[0]==213&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(528);} // K-  rho+  pi+                   PHSP;
  if(MctkPID[0]==221&&MctkPID[1]== 211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(531);} // anti-K0   eta  pi+              PHSP;
  if(MctkPID[0]==331&&MctkPID[1]== 211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(532);} // anti-K0   eta' pi+              PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 113&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(533);} // anti-K0   rho0  pi+             PHSP;
  if(MctkPID[0]==223&&MctkPID[1]== 211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(534);} // anti-K0   omega  pi+            PHSP;
  if(MctkPID[0]==221&&MctkPID[1]== 211&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(539);} // anti-K*0 eta  pi+               PHSP;
  if(MctkPID[0]==223&&MctkPID[1]== 211&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(540);} // anti-K*0 omega  pi+             PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 113&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(541);} // anti-K*0 rho0  pi+              PHSP;
  if(MctkPID[0]==313&&MctkPID[1]== 211&&MctkPID[2]==   113) { SelectionValid = true; Mcmode.push_back(596);} // anti-K*0 rho0  pi+              PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==-311&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(545);} // anti-K0   anti-K0    K+         PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(550);} // pi+  pi+  pi-                   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 111&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(556);} // pi+  pi0  pi0                   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 113&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(558);} // rho0 pi+ pi0	                PHSP;
  if(MctkPID[0]==213&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(559);} // rho+ pi+ pi-	                PHSP;
  if(MctkPID[0]==221&&MctkPID[1]== 211&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(562);} // eta pi+ pi0                     PHSP;
  if(MctkPID[0]==331&&MctkPID[1]== 211&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(564);} // eta' pi+ pi0	                PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 113&&MctkPID[2]==   113) { SelectionValid = true; Mcmode.push_back(570);} // rho0 rho0 pi+                   PHSP;
  if(MctkPID[0]==321&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(577);} // K+ K- pi+                       PHSP;
  if(MctkPID[0]==311&&MctkPID[1]== 211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(582);} // anti-K0   K0  pi+               PHSP;
  if(MctkPID[0]==333&&MctkPID[1]== 211&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(584);} // phi pi+ pi0                     PHSP;
  if(MctkPID[0]==321&&MctkPID[1]== 321&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(588);} // K+ K+ K-                        PHSP;
 }

 if(Nint==4) {
  if(MctkPID[0]==211&&MctkPID[1]== 12&&MctkPID[2]== -11&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(507);} // K-  pi+    e+  nu_e             PHOTOS   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 14&&MctkPID[2]== -13&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(517);} // K-  pi+    mu+ nu_mu            PHOTOS   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(530);} // anti-K0   pi+  pi+   pi-        PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(535);} // anti-K0   pi+  pi0   pi0        PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]== 113&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(543);} // K- rho0 pi+ pi+                 PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-311&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(546);} // K+ K- anti-K0 pi+               PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]== 111) { SelectionValid = true; Mcmode.push_back(565);} // pi+  pi0  pi0  pi0              PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]== 211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(568);} // eta pi+ pi+ pi-                 PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]== 111) { SelectionValid = true; Mcmode.push_back(569);} // eta pi+ pi0 pi0                 PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]== 113&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(571);} // rho0 pi+ pi+ pi-                PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(578);} // K+ anti-K0 pi+ pi-              PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-311&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(579);} // K- anti-K0 pi+ pi+              PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(583);} // anti-K0 K0 pi+ pi0              PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(586);} // K+ K- pi+ pi0                   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(594);} // K- pi+ pi+ pi0                  PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(595);} // pi+ pi+ pi- pi0                 PHSP;
  }

 if(Nint==5) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-311) { SelectionValid = true; Mcmode.push_back(536);} // anti-K0   pi+  pi+   pi-   pi0  PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-311) { SelectionValid = true; Mcmode.push_back(537);} // anti-K0   pi+  pi0   pi0   pi0  PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(544);} // K-  pi+  pi+   pi+   pi-        PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(547);} // K-  pi+  pi+   pi0   pi0        PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(560);} // pi+ pi+ pi+ pi- pi-             PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 111&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(566);} // pi+ pi+ pi- pi0 pi0	       PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(580);} // K+ K- pi+ pi+ pi-               PHSP;
 }

 if(Nint==6) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==111&&MctkPID[4]==-211&&MctkPID[5]== -211) { SelectionValid = true; Mcmode.push_back(567);} // pi+ pi+ pi+ pi- pi- pi0         PHSP;
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(1102);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(1103);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(1104);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(1105);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(1106);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(1107);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(1108);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(1109);

}
}

void DsDsmcmode::Dnmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-411)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -411;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=-411) continue;
      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

/*
if(Nint==2) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;
if(Nint==3) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
if(Nint==4) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<endl;
if(Nint==5) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<endl;
if(Nint==6) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<","<<MctkPID[5]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]==     13&&MctkPID[1]== -14) { SelectionValid = true; Mcmode.push_back(-501);} // mu- anti-nu_mu             PHOTOS   SLN;
  if(MctkPID[0]==     15&&MctkPID[1]== -16) { SelectionValid = true; Mcmode.push_back(-502);} // tau- anti-nu_tau           SLN;
  if(MctkPID[0]==    310&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-523);} // K_S0 pi-                   PHSP;
  if(MctkPID[0]==    130&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-524);} // K_L0 pi-                   PHSP;
  if(MctkPID[0]==    313&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-527);} // K*0 rho-                   SVV_HELAMP  1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==  20313&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-529);} // K'_10  pi-                 SVS;
  if(MctkPID[0]==  311&&MctkPID[1]==-20213) { SelectionValid = true; Mcmode.push_back(-538);} // a_1- K0                    SVS;
  if(MctkPID[0]==  313&&MctkPID[1]==-20213) { SelectionValid = true; Mcmode.push_back(-542);} // a_1- K*0                   SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    111&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-548);} // pi0 pi-                    PHSP;
  if(MctkPID[0]==    113&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-549);} // rho0 pi-                   SVS;
  if(MctkPID[0]==9010221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-551);} // f_0 pi-                    PHSP;
  if(MctkPID[0]==  10221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-552);} // f'_0  pi-                  PHSP;
  if(MctkPID[0]==    225&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-553);} // f_2 pi-                    STS;
  if(MctkPID[0]==  50221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-554);} // f_0(1500) pi-              PHSP;
  if(MctkPID[0]==    111&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-555);} // rho- pi0                   SVS;
  if(MctkPID[0]==    113&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-557);} // rho0 rho-                  SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-561);} // eta pi-                    PHSP;
  if(MctkPID[0]==    331&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-563);} // eta' pi-                   PHSP;
  if(MctkPID[0]==    311&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-572);} // K0   K-                    PHSP;
  if(MctkPID[0]==    333&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-573);} // phi pi-                    SVS;
  if(MctkPID[0]==    313&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-574);} // K*0  K-                    SVS;
  if(MctkPID[0]==  10311&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-575);} // K_0*0 K-                   PHSP;
  if(MctkPID[0]==    315&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-576);} // K_2*0 K-                   STS;
  if(MctkPID[0]==    313&&MctkPID[1]==-323) { SelectionValid = true; Mcmode.push_back(-581);} // K*0 K*-                    SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    333&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-585);} // phi rho-                   SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0;
  if(MctkPID[0]==    311&&MctkPID[1]==-323) { SelectionValid = true; Mcmode.push_back(-587);} // K*-   K0                   SVS;
  if(MctkPID[0]==    111&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-589);} // K- pi0                     PHSP;
  if(MctkPID[0]==    113&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-590);} // rho0 K-                    SVS;
  if(MctkPID[0]==   -211&&MctkPID[1]==-313) { SelectionValid = true; Mcmode.push_back(-591);} // anti-K*0 pi-               SVS;
  if(MctkPID[0]==9010221&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-592);} // K- f_0                     PHSP;
  if(MctkPID[0]==   -211&&MctkPID[1]==-315) { SelectionValid = true; Mcmode.push_back(-593);} // anti-K_2*0 pi-             STS;
 }

 if(Nint==3) {
  if(MctkPID[0]==  311&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-503);} // K0    e-  anti-nu_e        PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==10313&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-504);} // K_10  e-  anti-nu_e        PHOTOS   ISGW2;
  if(MctkPID[0]==  313&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-505);} // K*0   e-  anti-nu_e        PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==  315&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-506);} // K_2*0 e-  anti-nu_e        PHOTOS   ISGW2;
  if(MctkPID[0]==  111&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-508);} // pi0   e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==  221&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-509);} // eta   e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetalnu;
  if(MctkPID[0]==  331&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-510);} // eta'  e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetaplnu;
  if(MctkPID[0]==  113&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-511);} // rho0  e-  anti-nu_e        PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==  223&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-512);} // omega e-  anti-nu_e        PHOTOS   SLPOLE_Dtoomegalnu;
  if(MctkPID[0]==  311&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-513);} // K0    mu- anti-nu_mu       PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==10313&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-514);} // K_10  mu- anti-nu_mu       PHOTOS   ISGW2;
  if(MctkPID[0]==  313&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-515);} // K*0   mu- anti-nu_mu       PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==  315&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-516);} // K_2*0 mu- anti-nu_mu       PHOTOS   ISGW2;
  if(MctkPID[0]==  111&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-518);} // pi0   mu- anti-nu_mu       PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==  221&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-519);} // eta   mu- anti-nu_mu       PHOTOS   SLBKPOLE_Dtoetalnu;
  if(MctkPID[0]==  331&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-520);} // eta'  mu- anti-nu_mu       PHOTOS   SLBKPOLE_Dtoetaplnu;
  if(MctkPID[0]==  113&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-521);} // rho0  mu- anti-nu_mu       PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==  223&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-522);} // omega mu- anti-nu_mu       PHOTOS   SLPOLE_Dtoomegalnu;
  if(MctkPID[0]==  321&&MctkPID[1]==-211&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-525);} // K+  pi-  pi-               D_DALITZ;
  if(MctkPID[0]==  311&&MctkPID[1]== 111&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-526);} // K0   pi-  pi0              D_DALITZ;
  if(MctkPID[0]==  321&&MctkPID[1]==-211&&MctkPID[2]==-213) { SelectionValid = true; Mcmode.push_back(-528);} // K+  rho-  pi-              PHSP;
  if(MctkPID[0]==  311&&MctkPID[1]== 221&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-531);} // K0   eta  pi-              PHSP;
  if(MctkPID[0]==  331&&MctkPID[1]== 311&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-532);} // K0   eta' pi-              PHSP;
  if(MctkPID[0]==  311&&MctkPID[1]== 113&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-533);} // K0   rho0  pi-             PHSP;
  if(MctkPID[0]==  311&&MctkPID[1]== 223&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-534);} // K0   omega  pi-            PHSP;
  if(MctkPID[0]==  313&&MctkPID[1]== 221&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-539);} // K*0 eta  pi-               PHSP;
  if(MctkPID[0]==  313&&MctkPID[1]== 223&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-540);} // K*0 omega  pi-             PHSP;
  if(MctkPID[0]==  313&&MctkPID[1]== 113&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-541);} // K*0 rho0   pi-             PHSP;
  if(MctkPID[0]==  113&&MctkPID[1]==-211&&MctkPID[2]==-313) { SelectionValid = true; Mcmode.push_back(-596);} // anti-K*0 rho0 pi-          PHSP;
  if(MctkPID[0]==  311&&MctkPID[1]== 311&&MctkPID[2]==-321) { SelectionValid = true; Mcmode.push_back(-545);} // K0   K0    K-              PHSP;
  if(MctkPID[0]==  211&&MctkPID[1]==-211&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-550);} // pi-  pi-  pi+              PHSP;
  if(MctkPID[0]==  111&&MctkPID[1]== 111&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-556);} // pi-  pi0  pi0              PHSP;
  if(MctkPID[0]==  113&&MctkPID[1]== 111&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-558);} // rho0 pi- pi0               PHSP;
  if(MctkPID[0]==  211&&MctkPID[1]==-211&&MctkPID[2]==-213) { SelectionValid = true; Mcmode.push_back(-559);} // rho- pi- pi+               PHSP;
  if(MctkPID[0]==  221&&MctkPID[1]== 111&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-562);} // eta  pi- pi0               PHSP;
  if(MctkPID[0]==  331&&MctkPID[1]== 111&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-564);} // eta' pi- pi0               PHSP;
  if(MctkPID[0]==  113&&MctkPID[1]== 113&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-570);} // rho0 rho0 pi-              PHSP;
  if(MctkPID[0]==  321&&MctkPID[1]==-211&&MctkPID[2]==-321) { SelectionValid = true; Mcmode.push_back(-577);} // K+ K- pi-                  PHSP;
  if(MctkPID[0]==  311&&MctkPID[1]==-211&&MctkPID[2]==-311) { SelectionValid = true; Mcmode.push_back(-582);} // anti-K0   K0  pi-          PHSP;
  if(MctkPID[0]==  333&&MctkPID[1]== 111&&MctkPID[2]==-211) { SelectionValid = true; Mcmode.push_back(-584);} // phi pi- pi0                PHSP;
  if(MctkPID[0]==  321&&MctkPID[1]==-321&&MctkPID[2]==-321) { SelectionValid = true; Mcmode.push_back(-588);} // K- K- K+                   PHSP;
 }

 if(Nint==4) {
  if(MctkPID[0]==321&&MctkPID[1]== 11&&MctkPID[2]== -12&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-507);} // K+  pi-    e-  anti-nu_e   PHOTOS   PHSP;
  if(MctkPID[0]==321&&MctkPID[1]== 13&&MctkPID[2]== -14&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-517);} // K+  pi-    mu- anti-nu_mu  PHOTOS   PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-530);} // K0   pi-  pi-   pi+        PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-535);} // K0   pi-  pi0   pi0        PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==113&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-543);} // K+ rho0 pi- pi-            PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==311&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-546);} // K+ K-   K0 pi-             PHSP;
  if(MctkPID[0]==111&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-565);} // pi-  pi0  pi0  pi0         PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-568);} // eta pi- pi- pi+            PHSP;
  if(MctkPID[0]==221&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-569);} // eta pi- pi0 pi0            PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==113&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-571);} // rho0 pi- pi- pi+           PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-578);} // K- K0 pi- pi+              PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==311&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-579);} // K+ K0 pi- pi-              PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(-583);} // anti-K0 K0 pi- pi0         PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-586);} // K+ K- pi- pi0              PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-594);} // K+ pi- pi- pi0             PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-595);} // pi- pi- pi+ pi0            PHSP;
  }

 if(Nint==5) {
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-536);} // K0  pi-  pi-   pi+   pi0   PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]== 111&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-537);} // K0  pi-  pi0   pi0   pi0   PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-544);} // K+  pi-  pi-   pi-   pi+   PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-547);} // K+  pi-  pi-   pi0   pi0   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-560);} // pi- pi- pi- pi+ pi+        PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 111&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-566);} // pi- pi- pi+ pi0 pi0        PHSP;
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(-580);} // K+ K- pi- pi- pi+          PHSP;
 }
                                                                                                                                             
 if(Nint==6) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-211&&MctkPID[5]== -211) { SelectionValid = true; Mcmode.push_back(-567);} // pi- pi- pi- pi+ pi+ pi0    PHSP;
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(-1102);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(-1103);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(-1104);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(-1105);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(-1106);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(-1107);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(-1108);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(-1109);

}
}












void DsDsmcmode::D0mcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  Vint KsID,EtaID,OmgID,EtapID,PhiID;
      KsID.clear();
      EtaID.clear();
      OmgID.clear();
      EtapID.clear();
      PhiID.clear();
      int IfKs   = 1;
      int IfEta  = 1;
      int IfOmg  = 1;
      int IfEtap = 1;
      int IfPhi  = 1;

      int ifks=0,ifeta=0,ifomg=0,ifetap=0,ifphi=0;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 421)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 421;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay) continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid) continue;

      if(pdgid==310) ifks++;
      if(pdgid==221) ifeta++;
      if(pdgid==223) ifomg++;
      if(pdgid==331) ifetap++;
      if(pdgid==333) ifphi++;

      if(IfKs==1){
       if((((*iter_mc)->mother()).particleProperty())==310) KsID.push_back(pdgid);
      }
      if(IfEta==1){
       if((((*iter_mc)->mother()).particleProperty())==221) EtaID.push_back(pdgid);
      }
      if(IfOmg==1){
       if((((*iter_mc)->mother()).particleProperty())==223) OmgID.push_back(pdgid);
      }
      if(IfEtap==1){
       if((((*iter_mc)->mother()).particleProperty())==331) EtapID.push_back(pdgid);
      }
      if(IfPhi==1){
       if((((*iter_mc)->mother()).particleProperty())==333) PhiID.push_back(pdgid);
      }

      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue;
      if((((*iter_mc)->mother()).particleProperty())==-15) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue;
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;
      if((((*iter_mc)->mother()).particleProperty())==223) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
      if((((*iter_mc)->mother()).particleProperty())==333) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==333) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==333) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==333) continue;

      if(pdgid==111)                             okay1 = true;
      if(pdgid==310)                             okay1 = true;
      if(pdgid==130)                             okay1 = true;
      if(abs(pdgid)==211)                        okay1 = true;
      if(abs(pdgid)==321)                        okay1 = true;
      if(abs(pdgid)==221)                        okay1 = true;
      if(abs(pdgid)==331)    okay1 = true;
      if(abs(pdgid)==223)    okay1 = true;
      if(abs(pdgid)==333)    okay1 = true;
      if(abs(pdgid)==13)                         okay1 = true;
      if(abs(pdgid)==14)                         okay1 = true;
      if(abs(pdgid)==15)                         okay1 = true;
      if(abs(pdgid)==16)                         okay1 = true;
      if(((*iter_mc)->daughterList()).size()==0) okay1 = true;
      if(!okay1) continue;
      finalID.push_back(pdgid);

      IDtk.push_back(pdgid);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid==-321)      NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]==-321) {ChargK = -1; P4K.push_back(Ptk[i]);}
      }

// Judging the Ks, eta, Omg, etap modes by the particles in the final states
    int Ksmode = 0;
    int Etamode = 0;
    int Omgmode = 0;
    int Etapmode = 0;
    int Phimode = 0;

    if(KsID.size()>0)
    sort(KsID.begin(),KsID.end(),greater<int>());
    if(EtaID.size()>0)
    sort(EtaID.begin(),EtaID.end(),greater<int>());
    if(OmgID.size()>0)
    sort(OmgID.begin(),OmgID.end(),greater<int>());
    if(EtapID.size()>0)
    sort(EtapID.begin(),EtapID.end(),greater<int>());
    if(PhiID.size()>0)
    sort(PhiID.begin(),PhiID.end(),greater<int>());

    if(KsID.size()==2&&KsID[0]==211&&KsID[1]==-211) Ksmode = 1;
//    if(KsID.size()==2&&KsID[0]==111&&KsID[1]== 111) Ksmode = 2;

    if(EtaID.size()==2&&EtaID[0]==22&&EtaID[1]==22) Etamode = 1;
    if(EtaID.size()==3&&EtaID[0]==211&&EtaID[1]==111&&EtaID[2]==-211) Etamode = 2;

    if(OmgID.size()==3&&OmgID[0]==211&&OmgID[1]==111&&OmgID[2]==-211) Omgmode = 1;

    if(EtapID.size()==3&&EtapID[0]==221&&EtapID[1]==211&&EtapID[2]==-211) Etapmode = 1;
    if(EtapID.size()==2&&EtapID[0]==113&&EtapID[1]==22) Etapmode = 2;
    if(EtapID.size()==3&&EtapID[0]==211&&EtapID[1]==22&&EtapID[2]==-211) Etapmode = 3;

    if(PhiID.size()==2&&PhiID[0]==321&&PhiID[1]==-321) Phimode = 1;
    if(PhiID.size()==3&&PhiID[0]==211&&PhiID[1]==111&&PhiID[2]==-211) Phimode = 2;

//    cout<<"aaa:"<<Ksmode<<" "<<Etamode<<" "<<Omgmode<<" "<<Etapmode<<endl;
//    cout<<"bbb:"<<ifks<<" "<<ifeta<<" "<<ifomg<<" "<<ifetap<<endl;

      int Ntot = finalID.size();
// Judging the D0 modes by the particles in the final states
    sort(finalID.begin(),finalID.end(),greater<int>());

//    cout<<Ntot<<" "<<finalID[0]<<endl;

/*
if(Ntot==2) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<endl;
if(Ntot==3) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<endl;
if(Ntot==4) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<endl;
if(Ntot==5) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<endl;
if(Ntot==6) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<","<<finalID[5]<<endl;
*/

    if(Ntot==2) Mcmodef = 1002;
    if(Ntot==3) Mcmodef = 1003;
    if(Ntot==4) Mcmodef = 1004;
    if(Ntot==5) Mcmodef = 1005;
    if(Ntot==6) Mcmodef = 1006;
    if(Ntot==7) Mcmodef = 1007;
    if(Ntot==8) Mcmodef = 1008;
    if(Ntot==9) Mcmodef = 1009;
    if(Ntot>9)  Mcmodef = 1010;

    if(Ntot==2) {
      if(finalID[0]==211&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = 101;}   // D0-->K-pi+
      if(finalID[0]==310&&finalID[1]== 310)  { SelectionValid = true; Mcmodef = 301;}   // D0-->KsKs
      if(Etamode==1&&Omgmode==1&&finalID[0]==223&&finalID[1]==221)  { SelectionValid = true; Mcmodef = 316;}   // D0-->omgeta, eta to gammagamma
      if(Phimode==1&&finalID[0]==333&&finalID[1]==111)  { SelectionValid = true; Mcmodef = 317;}   // D0--> phipi0
      if(Phimode==1&&Etamode==1&&finalID[0]==333&&finalID[1]==223)  { SelectionValid = true; Mcmodef = 318;}   // D0--> phieta, eta to gammagamma
      if(Ksmode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223)  { SelectionValid = true; Mcmodef = 401;}   // D0-->Ksomg
      if(Ksmode==1&&Etamode==2&&finalID[0]==310&&finalID[1]==221)  { SelectionValid = true; Mcmodef = 402;}   // D0-->Kseta
      if(Ksmode==1&&Phimode==2&&finalID[0]==333&&finalID[1]==310)  { SelectionValid = true; Mcmodef = 403;}   // D0-->Ksphi
    }

    if(Ntot==3) {
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 102;}   // D0-->K-pi+pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 106;}   // D0-->KSpi+pi-
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 107;}   // D0-->KSK+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 108;}   // D0-->KSK-pi+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 109;}   // D0-->KSK+K-
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 110;}   // D0-->K+K-pi0
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 111;}   // D0-->pi+pi-pi0
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 310)  { SelectionValid = true; Mcmodef = 302;}   // D0-->KsKsKs
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 303;}   // D0-->KsKspi0
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 221)  { SelectionValid = true; Mcmodef = 304;}   // D0-->KsKseta
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 305;}   // D0-->K-pi+eta
      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 306;}   // D0-->K+pi-eta
      if(finalID[0]==223&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 307;}   // D0-->K-pi+omg
      if(finalID[0]==321&&finalID[1]==223&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 308;}   // D0-->K+pi-omg
      if(finalID[0]==331&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 309;}   // D0-->K-pi+etap
      if(finalID[0]==331&&finalID[1]==321&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 310;}   // D0-->K+pi-etap
      if(Ksmode==1&&Etamode==2&&finalID[0]==310&&finalID[1]==221&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 311;}   // D0-->Kspi0eta
      if(Ksmode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 313;}   // D0-->Kspi0omg
      if(Ksmode==1&&Etamode==1&&Etapmode==1&&finalID[0]==331&&finalID[1]==310&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 315;}   // D0-->Kspi0etap
      if(Ksmode==1&&Etamode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223&&finalID[2]== 221)  { SelectionValid = true; Mcmodef = 319;}   // D0-->Ksetaomg
      if(Etamode==1&&Omgmode==1&&finalID[0]==223&&finalID[1]==221&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 320;}   // D0-->pi0etaomg
    }

    if(Ntot==4) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 103;}  // D0-->K-pi+pi+pi-
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 111&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 104;}  // D0-->K-pi+pi0pi0

      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = 112;}  // D0-->pi+pi+pi-pi-
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 113;}  // D0-->K-K+pi+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-211) { SelectionValid = true; Mcmodef = 114;}  // D0-->KSpi+pi-pi0 
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 111&&finalID[3]==-211) { SelectionValid = true; Mcmodef = 115;}  // D0-->KSK+pi-pi0 
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 116;}  // D0-->KSK-pi+pi0 

      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 12&&finalID[3] == -11)  { SelectionValid = true; Mcmodef = 201;}   // D0b-->K-pi0e+ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 12&&finalID[3] == -11)  { SelectionValid = true; Mcmodef = 202;}   // D0b-->pi-pi0e+ne
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 12&&finalID[3] == -11)  { SelectionValid = true; Mcmodef = 203;}   // D0b-->Kspi-e+ne
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 12&&finalID[3] == -11)  { SelectionValid = true; Mcmodef = 204;}   // D0b-->KLpi-e+ne 
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 14&&finalID[3] == -13)  { SelectionValid = true; Mcmodef = 205;}   // D0b-->K-pi0mu+nmu
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 14&&finalID[3] == -13)  { SelectionValid = true; Mcmodef = 206;}   // D0b-->pi-pi0mu+nmu
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 14&&finalID[3] == -13)  { SelectionValid = true; Mcmodef = 207;}   // D0b-->Kspi-mu+nmu
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 14&&finalID[3] == -13)  { SelectionValid = true; Mcmodef = 208;}   // D0b-->KLpi-mu+nmu

    }

    if(Ntot==5) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==111&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 105;}  // D0-->K-pi+pi+pi-pi0 
    }
  }

}

void DsDsmcmode::D0bmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();
  Vint KsID,EtaID,OmgID,EtapID,PhiID;
      KsID.clear();
      EtaID.clear();
      OmgID.clear();
      EtapID.clear();
      PhiID.clear();
      int IfKs   = 1;
      int IfEta  = 1;
      int IfOmg  = 1;
      int IfEtap = 1;
      int IfPhi  = 1;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle()) continue;
      if (!(*iter_mc)->decayFromGenerator()) continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-421)  {ChargD = -1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -421;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay) continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid) continue;

      if(IfKs==1){
       if((((*iter_mc)->mother()).particleProperty())==310) KsID.push_back(pdgid);
      }
      if(IfEta==1){
       if((((*iter_mc)->mother()).particleProperty())==221) EtaID.push_back(pdgid);
      }
      if(IfOmg==1){
       if((((*iter_mc)->mother()).particleProperty())==223) OmgID.push_back(pdgid);
      }
      if(IfEtap==1){
       if((((*iter_mc)->mother()).particleProperty())==331) EtapID.push_back(pdgid);
      }
      if(IfPhi==1){
       if((((*iter_mc)->mother()).particleProperty())==333) PhiID.push_back(pdgid);
      }

      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
 
      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue;
      if((((*iter_mc)->mother()).particleProperty())==-15) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue;
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;
      if((((*iter_mc)->mother()).particleProperty())==223) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
      if((((*iter_mc)->mother()).particleProperty())==333) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==333) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==333) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==333) continue;

      if(pdgid==111)    okay1 = true;
      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
      if(abs(pdgid)==331)    okay1 = true;
      if(abs(pdgid)==223)    okay1 = true;
      if(abs(pdgid)==333)    okay1 = true;
      if(abs(pdgid)==13)    okay1 = true;
      if(abs(pdgid)==14)    okay1 = true;
      if(abs(pdgid)==15)    okay1 = true;
      if(abs(pdgid)==16)    okay1 = true;
      if(((*iter_mc)->daughterList()).size()==0) okay1 = true;
      if(!okay1) continue;
      finalID.push_back(pdgid);

      IDtk.push_back(pdgid);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid== 321)       NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]== 321) {ChargK =  1; P4K.push_back(Ptk[i]);}
      }

    sort(finalID.begin(),finalID.end(),greater<int>());
    //sort(finalID.begin(),finalID.end(),greater<int>());

// Judging the Ks, eta, Omg, etap modes by the particles in the final states
    int Ksmode = 0;
    int Etamode = 0;
    int Omgmode = 0;
    int Etapmode = 0;
    int Phimode = 0;

    if(KsID.size()>0)
    sort(KsID.begin(),KsID.end(),greater<int>());
    if(EtaID.size()>0)
    sort(EtaID.begin(),EtaID.end(),greater<int>());
    if(OmgID.size()>0)
    sort(OmgID.begin(),OmgID.end(),greater<int>());
    if(EtapID.size()>0)
    sort(EtapID.begin(),EtapID.end(),greater<int>());
    if(PhiID.size()>0)
    sort(PhiID.begin(),PhiID.end(),greater<int>());

    if(KsID.size()==2&&KsID[0]==211&&KsID[1]==-211) Ksmode = 1;
//    if(KsID.size()==2&&KsID[0]==111&&KsID[1]== 111) Ksmode = 2;

    if(EtaID.size()==2&&EtaID[0]==22&&EtaID[1]==22) Etamode = 1;
    if(EtaID.size()==3&&EtaID[0]==211&&EtaID[1]==111&&EtaID[2]==-211) Etamode = 2;

    if(OmgID.size()==3&&OmgID[0]==211&&OmgID[1]==111&&OmgID[2]==-211) Omgmode = 1;

    if(EtapID.size()==3&&EtapID[0]==221&&EtapID[1]==211&&EtapID[2]==-211) Etapmode = 1;
    if(EtapID.size()==2&&EtapID[0]==113&&EtapID[1]==22) Etapmode = 2;
    if(EtapID.size()==3&&EtapID[0]==211&&EtapID[1]==22&&EtapID[2]==-211) Etapmode = 3;

    if(PhiID.size()==2&&PhiID[0]==321&&PhiID[1]==-321) Phimode = 1;
    if(PhiID.size()==3&&PhiID[0]==211&&PhiID[1]==111&&PhiID[2]==-211) Phimode = 2;

    int Ntot = finalID.size();

    if(Ntot==2) Mcmodef = -1002;
    if(Ntot==3) Mcmodef = -1003;
    if(Ntot==4) Mcmodef = -1004;
    if(Ntot==5) Mcmodef = -1005;
    if(Ntot==6) Mcmodef = -1006;
    if(Ntot==7) Mcmodef = -1007;
    if(Ntot==8) Mcmodef = -1008;
    if(Ntot==9) Mcmodef = -1009;
    if(Ntot>9)  Mcmodef = -1010;

    if(Ntot==2) {
      if(finalID[0]==321&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -101;}  // D0b-->K+pi-
      if(finalID[0]==310&&finalID[1]== 310)  { SelectionValid = true; Mcmodef = -301;}  // D0-->KsKs
      if(Etamode==1&&Omgmode==1&&finalID[0]==223&&finalID[1]==221)  { SelectionValid = true; Mcmodef = -316;}   // D0-->omgeta, eta to gammagamma
      if(Phimode==1&&finalID[0]==333&&finalID[1]==111)  { SelectionValid = true; Mcmodef = -317;}   // D0--> phipi0
      if(Phimode==1&&Etamode==1&&finalID[0]==333&&finalID[1]==223)  { SelectionValid = true; Mcmodef = -318;}   // D0--> phieta, eta to gammagamma
      if(Ksmode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223)  { SelectionValid = true; Mcmodef = -401;}   // D0-->Ksomg
      if(Ksmode==1&&Etamode==2&&finalID[0]==310&&finalID[1]==221)  { SelectionValid = true; Mcmodef = -402;}   // D0-->Kseta
      if(Ksmode==1&&Phimode==2&&finalID[0]==333&&finalID[1]==310)  { SelectionValid = true; Mcmodef = -403;}   // D0-->Ksphi
    }

    if(Ntot==3) {
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -102;}   // D0b-->K+pi-pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -106;}   // D0b-->KSpi+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -107;}   // D0b-->KSK-pi+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -108;}   // D0b-->KSK+pi-
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -109;}   // D0b-->KSK+K-
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -110;}   // D0b-->K+K-pi0
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -111;}   // D0b-->pi+pi-pi0
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 310)  { SelectionValid = true; Mcmodef = -302;}   // D0b-->KsKsKs
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = -303;}   // D0b-->KsKspi0
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 221)  { SelectionValid = true; Mcmodef = -304;}   // D0b-->KsKseta
      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -305;}   // D0b-->K+pi-eta
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -306;}   // D0b-->K-pi+eta
      if(finalID[0]==321&&finalID[1]==223&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -307;}   // D0b-->K+pi-omg
      if(finalID[0]==223&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -308;}   // D0b-->K-pi+omg
      if(finalID[0]==331&&finalID[1]==321&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -309;}   // D0b-->K+pi-etap
      if(finalID[0]==331&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -310;}   // D0b-->K-pi+etap
      if(Ksmode==1&&Etamode==2&&finalID[0]==310&&finalID[1]==221&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = -311;}   // D0b-->Kspi0eta
      if(Ksmode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = -313;}   // D0b-->Kspi0omg
      if(Ksmode==1&&Etamode==1&&Etapmode==1&&finalID[0]==331&&finalID[1]==310&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = -315;}   // D0b-->Kspi0etap
      if(Ksmode==1&&Etamode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223&&finalID[2]== 221)  { SelectionValid = true; Mcmodef = -319;}   // D0b-->Ksetaomg
      if(Etamode==1&&Omgmode==1&&finalID[0]==223&&finalID[1]==221&&finalID[2]== 111)  { SelectionValid = true; Mcmodef =-320;}   // D0b-->pi0etaomg
    }

    if(Ntot==4) {
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -103;}   // D0b-->K+pi+pi-pi-
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 111&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -104;}   // D0b-->K+pi-pi0pi0

      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -112;}   // D0b-->pi+pi-pi+pi-
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -113;}   // D0b-->K-K+pi+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -114;}   // D0b-->KSpi+pi-pi0 
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 111&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -115;}   // D0b-->KSK+pi-pi0 
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -116;}   // D0b-->KSK-pi+pi0 

      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 11&&finalID[3] == -12)  { SelectionValid = true; Mcmodef = -201;}   // D0b-->K+pi0e-ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 11&&finalID[3] == -12)  { SelectionValid = true; Mcmodef = -202;}   // D0b-->pi+pi0e-ne
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 11&&finalID[3] == -12)  { SelectionValid = true; Mcmodef = -203;}   // D0b-->Kspi+e-ne
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 11&&finalID[3] == -12)  { SelectionValid = true; Mcmodef = -204;}   // D0b-->KLpi+e-ne
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -205;}   // D0b-->K+pi0mu-nmu
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -206;}   // D0b-->pi+pi0mu-nmu
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -207;}   // D0b-->Kspi+mu-nmu
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -208;}   // D0b-->KLpi+mu-nmu
    }

    if(Ntot==5) {
       if(finalID[0]==321&&finalID[1]==211&&finalID[2]==111&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -105;}  // D0b-->K+pi+pi-pi-pi0 
    }
  }

}


void DsDsmcmode::DpmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  Vint KsID,EtaID,OmgID,EtapID,PhiID;
      KsID.clear();
      EtaID.clear();
      OmgID.clear();
      EtapID.clear();
      PhiID.clear();
      int IfKs   = 1;
      int IfEta  = 1;
      int IfOmg  = 1;
      int IfEtap = 1;
      int IfPhi  = 1;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      //if ((*iter_mc)->primaryParticle()) continue;
      if (!(*iter_mc)->decayFromGenerator()) continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 411)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22) continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 411;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay) continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid) continue;

      if(IfKs==1){
       if((((*iter_mc)->mother()).particleProperty())==310) KsID.push_back(pdgid);
      }
      if(IfEta==1){
       if((((*iter_mc)->mother()).particleProperty())==221) EtaID.push_back(pdgid);
      }
      if(IfOmg==1){
       if((((*iter_mc)->mother()).particleProperty())==223) OmgID.push_back(pdgid);
      }
      if(IfEtap==1){
       if((((*iter_mc)->mother()).particleProperty())==331) EtapID.push_back(pdgid);
      }
      if(IfPhi==1){
       if((((*iter_mc)->mother()).particleProperty())==333) PhiID.push_back(pdgid);
      }

      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue; 
      if((((*iter_mc)->mother()).particleProperty())==-15) continue; 
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue; 
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue; 
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;
      if((((*iter_mc)->mother()).particleProperty())==223) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;

      if(pdgid==111)    okay1 = true;
      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
      if(abs(pdgid)==331)    okay1 = true;
      if(abs(pdgid)==223)    okay1 = true;
      if(abs(pdgid)==333)    okay1 = true;
      if(abs(pdgid)==13)    okay1 = true;
      if(abs(pdgid)==14)    okay1 = true;
      if(abs(pdgid)==15)    okay1 = true;
      if(abs(pdgid)==16)    okay1 = true;
      if(((*iter_mc)->daughterList()).size()==0) okay1 = true;
      if(!okay1) continue;
      finalID.push_back(pdgid);
      IDtk.push_back(pdgid);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

    }


// Judging the Ks, eta, Omg, etap modes by the particles in the final states
    int Ksmode = 0;
    int Etamode = 0;
    int Omgmode = 0;
    int Etapmode = 0;
    int Phimode = 0;

    if(KsID.size()>0)
    sort(KsID.begin(),KsID.end(),greater<int>());
    if(EtaID.size()>0)
    sort(EtaID.begin(),EtaID.end(),greater<int>());
    if(OmgID.size()>0)
    sort(OmgID.begin(),OmgID.end(),greater<int>());
    if(EtapID.size()>0)
    sort(EtapID.begin(),EtapID.end(),greater<int>());
    if(PhiID.size()>0)
    sort(PhiID.begin(),PhiID.end(),greater<int>());

    if(KsID.size()==2&&KsID[0]==211&&KsID[1]==-211) Ksmode = 1;
//    if(KsID.size()==2&&KsID[0]==111&&KsID[1]== 111) Ksmode = 2;

    if(EtaID.size()==2&&EtaID[0]==22&&EtaID[1]==22) Etamode = 1;
    if(EtaID.size()==3&&EtaID[0]==211&&EtaID[1]==111&&EtaID[2]==-211) Etamode = 2;

    if(OmgID.size()==3&&OmgID[0]==211&&OmgID[1]==111&&OmgID[2]==-211) Omgmode = 1;

    if(EtapID.size()==3&&EtapID[0]==221&&EtapID[1]==211&&EtapID[2]==-211) Etapmode = 1;
    if(EtapID.size()==2&&EtapID[0]==113&&EtapID[1]==22) Etapmode = 2;
    if(EtapID.size()==3&&EtapID[0]==211&&EtapID[1]==22&&EtapID[2]==-211) Etapmode = 3;

    if(PhiID.size()==2&&PhiID[0]==321&&PhiID[1]==-321) Phimode = 1;

    sort(finalID.begin(),finalID.end(),greater<int>());

    int Ntot = finalID.size();

    if(Ntot==2) Mcmodef = 1102;
    if(Ntot==3) Mcmodef = 1103;
    if(Ntot==4) Mcmodef = 1104;
    if(Ntot==5) Mcmodef = 1105;
    if(Ntot==6) Mcmodef = 1106;
    if(Ntot==7) Mcmodef = 1107;
    if(Ntot==8) Mcmodef = 1108;
    if(Ntot==9) Mcmodef = 1109;
    if(Ntot>9)  Mcmodef = 1110;

/*
if(Ntot==2) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<endl;
if(Ntot==3) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<endl;
if(Ntot==4) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<endl;
if(Ntot==5) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<endl;
if(Ntot==6) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<","<<finalID[5]<<endl;
*/


    if(Ntot==2) {
      if(finalID[0]==310&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 603;} // D+-->KSpi+
      if(finalID[0]==321&&finalID[1]==310)  { SelectionValid = true; Mcmodef = 607;} // D+-->KSK+
      if(finalID[0]==211&&finalID[1]==130)  { SelectionValid = true; Mcmodef = 610;} // D+-->K_L0 pi+
      if(finalID[0]==321&&finalID[1]==130)  { SelectionValid = true; Mcmodef = 611;} // D+-->K_L0 K+
    }

    if(Ntot==3) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 601;} // D+-->K-pi+pi+
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 604;} // D+-->KSpi+pi0
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 606;} // D+-->K+K-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 608;} // D+-->pi+pi+pi-
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 211)  { SelectionValid = true; Mcmodef = 612;} // D+-->KSKSpi+
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 613;} // D+-->K_L0 pi+ pi0
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 310)  { SelectionValid = true; Mcmodef = 620;} // D+-->KSKSK+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 801;} // D+-->KSK+pi0

      if(Ksmode==1&&Etamode==2&&finalID[0]==310&&finalID[1]==221&&finalID[2]== 211)  { SelectionValid = true; Mcmodef = 802;} // D+-->KSpi+eta
      if(Ksmode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223&&finalID[2]== 211)  { SelectionValid = true; Mcmodef = 803;} // D+-->KSpi+omg
      if(Ksmode==1&&Etamode==1&&Etapmode==1&&finalID[0]==331&&finalID[1]==310&&finalID[2]== 211)  { SelectionValid = true; Mcmodef = 804;} // D+-->KSpi+etap
      if(finalID[0]==321&&finalID[1]==221&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 805;} // D+-->K+pi0eta
      if(finalID[0]==321&&finalID[1]==223&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 806;} // D+-->K+pi0omg
      if(finalID[0]==331&&finalID[1]==321&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 807;} // D+-->K+pi0etap
      if(Etamode==1&&Omgmode==1&&finalID[0]==223&&finalID[1]==221&&finalID[2]== 211)  { SelectionValid = true; Mcmodef = 808;} // D+-->omgetapi+

      if(finalID[0]==310&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 701;} // D+-->K_s0e +ne
      if(finalID[0]==130&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 702;} // D+-->K_L0e +ne
      if(finalID[0]==310&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 703;} // D+-->K_S0 mu+nu
      if(finalID[0]==130&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 704;} // D+-->K_L0 mu+nu
      if(finalID[0]==111&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 705;} // D+-->pi0e+ne
      if(finalID[0]==111&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 706;} // D+-->pi0mu+ne
    }

    if(Ntot==4) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 602;} // D+-->K-pi+pi+pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 605;} // D+-->KSpi+pi+pi-
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 614;} // D+-->pi+pi+pi-pi0 
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 615;} // D+-->KSK-pi+pi+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 617;} // D+-->KSK+pi-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 130&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 618;} // D+-->KLK-pi+pi+
      if(finalID[0]==321&&finalID[1]==130&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 619;} // D+-->KLK+pi-pi+

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 711;} // D--->gamma gamma e+ne
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 712;} // D--->pi0 pi0 e+ne
      if(finalID[0]==211&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = 713;} // D--->pi+ pi- e+ne
      if(finalID[0]==321&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 714;} // D--->K+ K- e+ne
      if(finalID[0]==211&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 715;} // D--->K- pi+ e+ne
      if(finalID[0]==321&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 716;} // D--->K+ pi- e+ne
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 717;} // D--->Ks pi0 e+ne
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 718;} // D--->KL pi0 e+ne

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 721;} // D--->gamma gamma mu+nmu
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 722;} // D--->pi0 pi0 mu+nmu
      if(finalID[0]==211&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = 723;} // D--->pi+ pi- mu+nmu
      if(finalID[0]==321&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 724;} // D--->K+ K- mu+nmu
      if(finalID[0]==211&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 725;} // D--->K- pi+ mu+nmu
      if(finalID[0]==321&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 726;} // D--->K+ pi- mu+nmu
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 727;} // D--->Ks pi0 mu+nmu
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 728;} // D--->KL pi0 mu+nmu



    }

    if(Ntot==5) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==211&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 609;} // D+-->K-pi+pi+pi+pi-
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==211&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 616;} // D+-->pi+pi+pi+pi-pi-
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 731;} // D--->pi+pi-pi0 e+ne
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 732;} // D--->pi+pi-eta e+ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 14&&finalID[3]== -13&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 741;} // D--->pi+pi-pi0 mu+nmu
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]== 14&&finalID[3]== -13&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 742;} // D--->pi+pi-eta mu+nmu


    }
  }


}


void DsDsmcmode::DnmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  Vint KsID,EtaID,OmgID,EtapID,PhiID;
      KsID.clear();
      EtaID.clear();
      OmgID.clear();
      EtapID.clear();
      PhiID.clear();
      int IfKs   = 1;
      int IfEta  = 1;
      int IfOmg  = 1;
      int IfEtap = 1;
      int IfPhi  = 1;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle()) continue;
      if (!(*iter_mc)->decayFromGenerator()) continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-411)  {ChargD = -1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22) continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -411;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay) continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid) continue;

      if(IfKs==1){
       if((((*iter_mc)->mother()).particleProperty())==310) KsID.push_back(pdgid);
      }
      if(IfEta==1){
       if((((*iter_mc)->mother()).particleProperty())==221) EtaID.push_back(pdgid);
      }
      if(IfOmg==1){
       if((((*iter_mc)->mother()).particleProperty())==223) OmgID.push_back(pdgid);
      }
      if(IfEtap==1){
       if((((*iter_mc)->mother()).particleProperty())==331) EtapID.push_back(pdgid);
      }
      if(IfPhi==1){
       if((((*iter_mc)->mother()).particleProperty())==333) PhiID.push_back(pdgid);
      }

      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue; 
      if(abs(((*iter_mc)->mother()).particleProperty())==15) continue; 
      if((((*iter_mc)->mother()).mother()).particleProperty()==15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==15) continue; 
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==15) continue; 
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;
      if((((*iter_mc)->mother()).particleProperty())==223) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;

      if(pdgid==111)    okay1 = true;
      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
      if(abs(pdgid)==331)    okay1 = true;
      if(abs(pdgid)==223)    okay1 = true;
      if(abs(pdgid)==333)    okay1 = true;
      if(abs(pdgid)==13)    okay1 = true;
      if(abs(pdgid)==14)    okay1 = true;
      if(abs(pdgid)==15)    okay1 = true;
      if(abs(pdgid)==16)    okay1 = true;
      if(((*iter_mc)->daughterList()).size()==0) okay1 = true;
      if(!okay1) continue;
      finalID.push_back(pdgid);
      IDtk.push_back(pdgid);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

    }

// Judging the Ks, eta, Omg, etap modes by the particles in the final states
    int Ksmode = 0;
    int Etamode = 0;
    int Omgmode = 0;
    int Etapmode = 0;
    int Phimode = 0;

    if(KsID.size()>0)
    sort(KsID.begin(),KsID.end(),greater<int>());
    if(EtaID.size()>0)
    sort(EtaID.begin(),EtaID.end(),greater<int>());
    if(OmgID.size()>0)
    sort(OmgID.begin(),OmgID.end(),greater<int>());
    if(EtapID.size()>0)
    sort(EtapID.begin(),EtapID.end(),greater<int>());
    if(PhiID.size()>0)
    sort(PhiID.begin(),PhiID.end(),greater<int>());

    if(KsID.size()==2&&KsID[0]==211&&KsID[1]==-211) Ksmode = 1;
//    if(KsID.size()==2&&KsID[0]==111&&KsID[1]== 111) Ksmode = 2;

    if(EtaID.size()==2&&EtaID[0]==22&&EtaID[1]==22) Etamode = 1;
    if(EtaID.size()==3&&EtaID[0]==211&&EtaID[1]==111&&EtaID[2]==-211) Etamode = 2;

    if(OmgID.size()==3&&OmgID[0]==211&&OmgID[1]==111&&OmgID[2]==-211) Omgmode = 1;

    if(EtapID.size()==3&&EtapID[0]==221&&EtapID[1]==211&&EtapID[2]==-211) Etapmode = 1;
    if(EtapID.size()==2&&EtapID[0]==113&&EtapID[1]==22) Etapmode = 2;
    if(EtapID.size()==3&&EtapID[0]==211&&EtapID[1]==22&&EtapID[2]==-211) Etapmode = 3;

    if(PhiID.size()==2&&PhiID[0]==321&&PhiID[1]==-321) Phimode = 1;

    sort(finalID.begin(),finalID.end(),greater<int>());

    int Ntot = finalID.size();

    if(Ntot==2) Mcmodef = -1102;
    if(Ntot==3) Mcmodef = -1103;
    if(Ntot==4) Mcmodef = -1104;
    if(Ntot==5) Mcmodef = -1105;
    if(Ntot==6) Mcmodef = -1106;
    if(Ntot==7) Mcmodef = -1107;
    if(Ntot==8) Mcmodef = -1108;
    if(Ntot==9) Mcmodef = -1109;
    if(Ntot>9)  Mcmodef = -1110;

    if(Ntot==2) {
      if(finalID[0]==310&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -603;}  // D--->KSpi-
      if(finalID[0]==310&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -607;}  // D--->KSK-
      if(finalID[0]==130&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -610;}  // D--->K_L0 pi-
      if(finalID[0]==130&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -611;}  // D--->K_L0 K-
    }

    if(Ntot==3) {
      if(finalID[0]==321&&finalID[1]==-211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -601;} // D--->K+pi-pi-
      if(finalID[0]==310&&finalID[1]== 111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -604;} // D--->KSpi-pi0
      if(finalID[0]==321&&finalID[1]==-211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -606;} // D--->K+K-pi-
      if(finalID[0]==211&&finalID[1]==-211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -608;} // D--->pi+pi-pi-
      if(finalID[0]==310&&finalID[1]== 310&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -612;} // D--->KSKSpi-
      if(finalID[0]==130&&finalID[1]== 111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -613;} // D--->K_L0 pi- pi0
      if(finalID[0]==310&&finalID[1]== 310&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -620;} // D--->KSKSK-
      if(finalID[0]==310&&finalID[1]== 111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -801;} // D--->KSK-pi0

      if(Ksmode==1&&Etamode==2&&finalID[0]==310&&finalID[1]==221&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -802;} // D--->KSpi-eta
      if(Ksmode==1&&Omgmode==1&&finalID[0]==310&&finalID[1]==223&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -803;} // D--->KSpi-omg
      if(Ksmode==1&&Etamode==1&&Etapmode==1&&finalID[0]==331&&finalID[1]==310&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -804;} // D--->KSpi-etap
      if(finalID[0]==221&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -805;} // D--->K-pi0eta
      if(finalID[0]==223&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -806;} // D--->K-pi0omg
      if(finalID[0]==331&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -807;} // D--->K-pi0etap
      if(Etamode==1&&Omgmode==1&&finalID[0]==223&&finalID[1]==221&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -808;} // D--->omgetapi-

      if(finalID[0]==310&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -701;} // D--->K_s0e-ne
      if(finalID[0]==130&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -702;} // D--->K_L0e-ne
      if(finalID[0]==310&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -703;} // D--->K_S0 mu-nu
      if(finalID[0]==130&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -704;} // D--->K_L0 mu-nu
      if(finalID[0]==111&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -705;} // D--->pi0e-ne
      if(finalID[0]==111&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -706;} // D--->pi0mu-nmu
    }

    if(Ntot==4) {
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -602;} // D--->K+pi-pi-pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -605;} // D--->KSpi+pi-pi-
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -614;} // D--->pi+pi-pi-pi0
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -615;} // D--->KSK+pi-pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = -617;} // D--->KSK-pi+pi-
      if(finalID[0]==321&&finalID[1]==130&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -618;} // D--->KLK+pi-pi-
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = -619;} // D--->KLK-pi+pi-

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -711;} // D--->gamma gamma e-ne
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -712;} // D--->pi0 pi0 e-ne
      if(finalID[0]==211&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = -713;} // D--->pi+ pi- e-ne
      if(finalID[0]==321&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -714;} // D--->K+ K- e-ne
      if(finalID[0]==321&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -715;} // D--->K+ pi- e-ne
      if(finalID[0]==211&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -716;} // D--->K- pi+ e-ne
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -717;} // D--->Ks pi0 e-ne
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -718;} // D--->KL pi0 e-ne

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -721;} // D--->gamma gamma mu-nmu
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -722;} // D--->pi0 pi0 mu-nmu
      if(finalID[0]==211&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = -723;} // D--->pi+ pi- mu-nmu
      if(finalID[0]==321&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -724;} // D--->K+ K- mu-nmu
      if(finalID[0]==321&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -725;} // D--->K+ pi- mu-nmu
      if(finalID[0]==211&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -726;} // D--->K- pi+ mu-nmu
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -727;} // D--->Ks pi0 mu-nmu
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -728;} // D--->KL pi0 mu-nmu
    }

    if(Ntot==5) {
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -609;} // D--->K+pi-pi-pi-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -616;} // D--->pi+pi+pi-pi-pi-

      if(finalID[0]==211&&finalID[1]==111&&finalID[1]==  11&&finalID[3]== -12&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -731;} // D--->pi+pi-pi0 e-ne
      if(finalID[0]==221&&finalID[1]==211&&finalID[1]==  11&&finalID[3]== -12&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -732;} // D--->pi+pi-eta e-ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[1]==  13&&finalID[3]== -14&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -741;} // D--->pi+pi-pi0 mu-nmu
      if(finalID[0]==221&&finalID[1]==211&&finalID[1]==  13&&finalID[3]== -14&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -742;} // D--->pi+pi-eta mu-nmu
    }
  }

}



void DsDsmcmode::Taupmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 15)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 15;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=15) continue;

      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid==-321)      NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]==-321) {ChargK = -1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();
// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

 if(Nint==2) {
  if(MctkPID[0]==  16&&MctkPID[1]==  -211) { SelectionValid = true; Mcmode.push_back(101);} //pi-  nu_tau                     TAUSCALARNU;
  if(MctkPID[0]==  16&&MctkPID[1]==  -321) { SelectionValid = true; Mcmode.push_back(102);} //K-  nu_tau                     TAUSCALARNU;
  if(MctkPID[0]==  16&&MctkPID[1]==  -323) { SelectionValid = true; Mcmode.push_back(103);} //K*-  nu_tau                     TAUSCALARNU;
  if(MctkPID[0]==  16&&MctkPID[1]==  -113) { SelectionValid = true; Mcmode.push_back(104);} //rho-  nu_tau                     TAUSCALARNU;
 }

 if(Nint==3) {
  if(MctkPID[0]== 16&&MctkPID[1]==  11&&MctkPID[2]==  -12) { SelectionValid = true; Mcmode.push_back(105);} // e-   anti-nu_e   nu_tau       PHOTOS TAULNUNU;
  if(MctkPID[0]== 16&&MctkPID[1]==  13&&MctkPID[2]==  -14) { SelectionValid = true; Mcmode.push_back(106);} // mu- anti-nu_mu   nu_tau       PHOTOS TAULNUNU;
  if(MctkPID[0]==111&&MctkPID[1]==  16&&MctkPID[2]== -211) { SelectionValid = true; Mcmode.push_back(107);} // pi- pi0  nu_tau
  if(MctkPID[0]==311&&MctkPID[1]==  16&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(108);} // nu_tau  K- K0
  if(MctkPID[0]==223&&MctkPID[1]==  16&&MctkPID[2]== -321) { SelectionValid = true; Mcmode.push_back(109);} // nu_tau  K-  omega  
 }

 if(Nint==4) {
  if(MctkPID[0]==211&&MctkPID[1]==16&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(110);}  // pi- pi- pi+  nu_tau
  if(MctkPID[0]==111&&MctkPID[1]==111&&MctkPID[2]==   16&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(111);} //pi0 pi0 pi-  nu_tau
  if(MctkPID[0]==321&&MctkPID[1]== 16&&MctkPID[2]== -211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(112);} //nu_tau     K- pi-     K+
  if(MctkPID[0]==311&&MctkPID[1]== 16&&MctkPID[2]== -211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(113);} // nu_tau     K0 pi-     anti-K0
  if(MctkPID[0]==311&&MctkPID[1]==111&&MctkPID[2]==16&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(114);} //nu_tau     K-      pi0     K0
  if(MctkPID[0]==111&&MctkPID[1]==111&&MctkPID[2]==16&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(115);} //nu_tau     K-      pi0     pi0
  if(MctkPID[0]==211&&MctkPID[1]== 16&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(116);} //nu_tau     K-      pi+     pi-
  if(MctkPID[0]==111&&MctkPID[1]== 16&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(117);} //nu_tau     pi- anti-K0 pi0
  if(MctkPID[0]==111&&MctkPID[1]== 16&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(118);} //nu_tau     pi-     anti-K0 pi0
  if(MctkPID[0]==221&&MctkPID[1]==111&&MctkPID[2]==  16&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(119);} //nu_tau     eta pi-     pi0
  if(MctkPID[0]==111&&MctkPID[1]== 22&&MctkPID[2]==  16&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(120);} //nu_tau     gamma   pi-     pi0
  if(MctkPID[0]==223&&MctkPID[1]==111&&MctkPID[2]==  16&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(121);} //nu_tau     pi-     omega     pi0
  }

 if(Nint==5) {
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 16&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(122);}  // nu_tau     pi-     pi+     pi-     pi0
  if(MctkPID[0]==111&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 16&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(123);}  // nu_tau     pi-     pi0     pi0     pi0
 }

 if(Nint==6) {																      
 if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 16&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(124);}  // nu_tau     pi-     pi-     pi+  pi0  pi0
 if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]== 16&&MctkPID[4]==-211&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(125);}  // nu_tau     pi-     pi-     pi-  pi+  pi+
 if(MctkPID[0]==111&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]== 16&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(126);}  // nu_tau     pi-     pi0  pi0  pi0  pi0
 }

 if(Nint==7) {
 if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]== 16&&MctkPID[4]==-211&&MctkPID[5]==-211&&MctkPID[6]==-211) { SelectionValid = true; Mcmode.push_back(127);}  // nu_tau     pi-     pi-  pi-  pi+  pi+  pi0
 if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]== 16&&MctkPID[5]==-211&&MctkPID[6]==-211) { SelectionValid = true; Mcmode.push_back(128);}  // nu_tau     pi-     pi-  pi+  pi0  pi0  pi0
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(1002);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(1003);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(1004);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(1005);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(1006);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(1007);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(1008);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(1009);

}
}

void DsDsmcmode::Taunmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-15)  {ChargD = -1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -15;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      //if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=-15) continue;
      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid== 321)           NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]== 321) {ChargK =  1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();
// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

 if(Nint==2) {
  if(MctkPID[0]==211&&MctkPID[1]==-16) { SelectionValid = true; Mcmode.push_back(101);} //pi-  nu_tau                     TAUSCALARNU;
  if(MctkPID[0]==321&&MctkPID[1]==-16) { SelectionValid = true; Mcmode.push_back(102);} //K-  nu_tau                     TAUSCALARNU;
  if(MctkPID[0]==323&&MctkPID[1]==-16) { SelectionValid = true; Mcmode.push_back(103);} //K*-  nu_tau                     TAUSCALARNU;
  if(MctkPID[0]==113&&MctkPID[1]==-16) { SelectionValid = true; Mcmode.push_back(104);} //rho-  nu_tau                     TAUSCALARNU;
 }

 if(Nint==3) {
  if(MctkPID[0]== 12&&MctkPID[1]==-11&&MctkPID[2]==-16) { SelectionValid = true; Mcmode.push_back(105);} // e-   anti-nu_e   nu_tau       PHOTOS TAULNUNU;
  if(MctkPID[0]== 14&&MctkPID[1]==-13&&MctkPID[2]==-16) { SelectionValid = true; Mcmode.push_back(106);} // mu- anti-nu_mu   nu_tau       PHOTOS TAULNUNU;
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==-16) { SelectionValid = true; Mcmode.push_back(107);} // pi- pi0  nu_tau
  if(MctkPID[0]==321&&MctkPID[1]==-16&&MctkPID[2]==-311) { SelectionValid = true; Mcmode.push_back(108);} // nu_tau  K- K0
  if(MctkPID[0]==321&&MctkPID[1]==223&&MctkPID[2]==-16) { SelectionValid = true; Mcmode.push_back(109);} // nu_tau  K-  omega  
 }

 if(Nint==4) {
  if(MctkPID[0]==211&&MctkPID[1]==221&&MctkPID[2]==-16&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(110);}  // pi- pi- pi+  nu_tau
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(111);} //pi0 pi0 pi-  nu_tau
  if(MctkPID[0]==321&&MctkPID[1]==-211&&MctkPID[2]==-16&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(112);} //nu_tau     K- pi-     K+
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==-16&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(113);} // nu_tau     K0 pi-     anti-K0
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==-16&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(114);} //nu_tau     K-      pi0     K0
  if(MctkPID[0]==321&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(115);} //nu_tau     K-      pi0     pi0
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-16&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(116);} //nu_tau     K-      pi+     pi-
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(117);} //nu_tau     pi- anti-K0 pi0
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(118);} //nu_tau     pi-     anti-K0 pi0
  if(MctkPID[0]==221&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(119);} //nu_tau     eta pi-     pi0
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]== 22&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(120);} //nu_tau     gamma   pi-     pi0
  if(MctkPID[0]==223&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-16) { SelectionValid = true; Mcmode.push_back(121);} //nu_tau     pi-     omega     pi0
  }

 if(Nint==5) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-16&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(122);}  // nu_tau     pi-     pi+     pi-     pi0
  if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]==-16) { SelectionValid = true; Mcmode.push_back(123);}  // nu_tau     pi-     pi0     pi0     pi0
 }

 if(Nint==6) {																      
 if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]==-16&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(124);}  // nu_tau     pi-     pi-     pi+  pi0  pi0
 if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]==-16&&MctkPID[5]==-211) { SelectionValid = true; Mcmode.push_back(125);}  // nu_tau     pi-     pi-     pi-  pi+  pi+
 if(MctkPID[0]==211&&MctkPID[1]==111&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]==111&&MctkPID[5]==-16) { SelectionValid = true; Mcmode.push_back(126);}  // nu_tau     pi-     pi0  pi0  pi0  pi0
 }

 if(Nint==7) {
 if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==111&&MctkPID[4]==-16&&MctkPID[5]==-211&&MctkPID[6]==-211) { SelectionValid = true; Mcmode.push_back(127);}  // nu_tau     pi-     pi-  pi-  pi+  pi+  pi0
 if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==111&&MctkPID[4]==111&&MctkPID[5]==-16&&MctkPID[6]==-211) { SelectionValid = true; Mcmode.push_back(128);}  // nu_tau     pi-     pi-  pi+  pi0  pi0  pi0
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(-1002);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(-1003);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(-1004);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(-1005);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(-1006);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(-1007);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(-1008);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(-1009);

}
}

void DsDsmcmode::Dsnmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-431)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -431;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      //if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=-431) continue;
      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)        MctkP = true;
      if(pdgid==20213)          MctkP = true;

//      cout<<"TEST DS mode AAA+:::"<<pdgid<<endl;

      int Idtrk = pdgid;
      if(Idtrk==((*iter_mc)->mother()).particleProperty()) continue;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

/*
if(Nint==2) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;
if(Nint==3) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
if(Nint==4) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<endl;
if(Nint==5) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<endl;
if(Nint==6) cout<<"bbbb"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<","<<MctkPID[5]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]==     13&&MctkPID[1]== -14) { SelectionValid = true; Mcmode.push_back(-201);} //0.0058           mu-  anti-nu_mu        PHOTOS  SLN;           #[0.0061]gamma20
  if(MctkPID[0]==     15&&MctkPID[1]== -16) { SelectionValid = true; Mcmode.push_back(-202);} //0.0600           tau- anti-nu_tau       SLN;                   #[0.0599]gamma21
  if(MctkPID[0]==    311&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-203);} //0.0296           K0 K-        PHSP;       #[0.0293]gamma30
  if(MctkPID[0]==    333&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-204);} //0.02405          phi_A   pi-       SVS;        #[0.0206]gamma33*0.509/0.491
  if(MctkPID[0]==    313&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-205);} //0.013            K- K*0       PHSP;        #gamma34*0.333/0.666=0.013
  if(MctkPID[0]==9010221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-206);} //0.0155           f_0_A   pi-       PHSP;       #[0.0103]gamma35
  if(MctkPID[0]==  10221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-207);} //0.0024           f'_0_A  pi-       PHSP;       #[0.0062]gamma36
  if(MctkPID[0]==  10331&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-208);} //0.00187          f_0(1710)_A pi-     PHSP;       #gamma37*0.5/0.5
  if(MctkPID[0]==  10311&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-209);} //0.00105          K-  K_0*0_A         PHSP;       #gamma38*0.3333/0.6667=0.00105 
  if(MctkPID[0]==    311&&MctkPID[1]==-323) { SelectionValid = true; Mcmode.push_back(-210);} //0.042            K*-    K0         SVS;        #[0.037] gamma 40 5.4-1.2 
  if(MctkPID[0]==    333&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-211);} //0.061            phi     rho-      SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0 ;      #[(K+ K- pi+ pi0)0.0735]gamma42 8.4-2.3 = 6.1
  if(MctkPID[0]==    313&&MctkPID[1]==-323) { SelectionValid = true; Mcmode.push_back(-212);} //0.072            K*0 K*-      PHSP;       #[0.0048]gamma44 7.2-2.6==>4.6+2.6
  if(MctkPID[0]==  333&&MctkPID[1]==-20213) { SelectionValid = true; Mcmode.push_back(-213);} //0.025            phi a_1-          SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0 ;  # [0.0236]gamma50(7.5-1.3)/0.492/0.492
  if(MctkPID[0]==    113&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-214);} //0.0002           rho0 pi-          SVS;          #gamma55
  if(MctkPID[0]==    225&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-215);} //0.002            f_2    pi-        STS;          #gamma60/0.565 = 0.00111/0.565=0.002
  if(MctkPID[0]==  30113&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-216);} //0.00075          rho(2S)0 pi-      SVS;          #[0.0016]gamma61/0.4 = 0.0003/0.4=0.00075 
  if(MctkPID[0]==    221&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-217);} //0.0183           eta     pi-       PHSP;         #[pi+ pi+ pi- pi0=0.0156]gamma 64 ==> 1.83-0.15 = 1.68==>1.68+0.15
  if(MctkPID[0]==    223&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-218);} //0.0025           omega   pi-       PHSP;         #[pi+ pi+ pi- pi0=0.0156]gamma 65
  if(MctkPID[0]==    221&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-219);} //0.081            eta     rho-      PHSP;         #[pi+ pi+ pi- pi0 pi0=0.0288]gamma 68 8.9-0.8
  if(MctkPID[0]==    331&&MctkPID[1]==-211) { SelectionValid = true; Mcmode.push_back(-220);} //0.0394           eta'    pi-       PHSP;         #[0.0367]gamma 73 ==> 3.94-0.33
  if(MctkPID[0]==    331&&MctkPID[1]==-213) { SelectionValid = true; Mcmode.push_back(-221);} //0.12315            rho-    eta'      SVS;          #[(3pi+ 2pi- 2pi0)0.0387]gamma 76 ==> 12.5-2.2 = 10.3==>10.3+2.015
  if(MctkPID[0]==    111&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-222);} //0.00062          K-      pi0       PHSP;         #[0.0007]gamma 78
  if(MctkPID[0]==   -211&&MctkPID[1]==-311) { SelectionValid = true; Mcmode.push_back(-223);} //0.00242          anti-K0      pi-  PHSP;         #[0.0024]gamma 79
  if(MctkPID[0]==    221&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-224);} //0.00175          eta     K-        PHSP;         #[0.0014]gamma 80
  if(MctkPID[0]==    331&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-225);} //0.0018           eta'    K-        PHSP;         #[0.0015]gamma 82
  if(MctkPID[0]==    113&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-226);} //0.0027           rho0    K-        PHSP;         #[0.0026]gamma 84
  if(MctkPID[0]==  30113&&MctkPID[1]==-321) { SelectionValid = true; Mcmode.push_back(-227);} //0.0018           rho(2S)0 K-       SVS;          #[0.0018]gamma 85/0.4=0.00073/0.4=0.0018
  if(MctkPID[0]==   -211&&MctkPID[1]==-313) { SelectionValid = true; Mcmode.push_back(-228);} //0.0023           anti-K*0     pi-  SVS;          #[0.0022]gamma 86/0.6657=0.0015/0.6657=0.0023
  if(MctkPID[0]==-211&&MctkPID[1]==-100313) { SelectionValid = true; Mcmode.push_back(-229);}//0.028            anti-K'*0    pi-  SVS;          #[0.0251]gamma 87/0.0467=0.0013/0.0467=0.028
  if(MctkPID[0]== -211&&MctkPID[1]==-10311) { SelectionValid = true; Mcmode.push_back(-230);} //0.00075          anti-K_0*0   pi-  PHSP;         #gamma 88/0.6667=0.0005/0.6667=0.00075
  if(MctkPID[0]==  2112&&MctkPID[1]==-2212) { SelectionValid = true; Mcmode.push_back(-231);}  // 0.0013           anti-p-   n0      PHSP;         #[0.0014]gamma 98
 }

 if(Nint==3) {
  if(MctkPID[0]==  311&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-301);} // K0    e-  anti-nu_e        PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==10313&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-302);} // K_10  e-  anti-nu_e        PHOTOS   ISGW2;
  if(MctkPID[0]==  313&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-303);} // K*0   e-  anti-nu_e        PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==  315&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-304);} // K_2*0 e-  anti-nu_e        PHOTOS   ISGW2;
  if(MctkPID[0]==  111&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-305);} // pi0   e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==  221&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-306);} // eta   e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetalnu;
  if(MctkPID[0]==  331&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-307);} // eta'  e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetaplnu;
  if(MctkPID[0]==  113&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-308);} // rho0  e-  anti-nu_e        PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==  223&&MctkPID[1]==  11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-309);} // omega e-  anti-nu_e        PHOTOS   SLPOLE_Dtoomegalnu;
  if(MctkPID[0]== 11&&MctkPID[1]== -12&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(-310);} // anti-K0         e-  anti-nu_e 
  if(MctkPID[0]== 11&&MctkPID[1]== -12&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(-311);} // anti-K*0        e-  anti-nu_e 
  if(MctkPID[0]==333&&MctkPID[1]==  11&&MctkPID[2]==   -12) { SelectionValid = true; Mcmode.push_back(-312);} // phi        e-  anti-nu_e 
  if(MctkPID[0]==9010221&&MctkPID[1]== 11&&MctkPID[2]==-12) { SelectionValid = true; Mcmode.push_back(-313);} // f_0    e-  anti-nu_e 
  if(MctkPID[0]==  311&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-314);} // K0    mu- anti-nu_mu       PHOTOS   SLBKPOLE_DtoKlnu;
  if(MctkPID[0]==10313&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-315);} // K_10  mu- anti-nu_mu       PHOTOS   ISGW2;
  if(MctkPID[0]==  313&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-316);} // K*0   mu- anti-nu_mu       PHOTOS   SLPOLE_DtoKstarlnu;
  if(MctkPID[0]==  315&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-317);} // K_2*0 mu- anti-nu_mu       PHOTOS   ISGW2;
  if(MctkPID[0]==  111&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-318);} // pi0   mu- anti-nu_mu       PHOTOS   SLBKPOLE_Dtopilnu;
  if(MctkPID[0]==  221&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-319);} // eta   mu- anti-nu_mu       PHOTOS   SLBKPOLE_Dtoetalnu;
  if(MctkPID[0]==  331&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-320);} // eta'  mu- anti-nu_mu       PHOTOS   SLBKPOLE_Dtoetaplnu;
  if(MctkPID[0]==  113&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-321);} // rho0  mu- anti-nu_mu       PHOTOS   SLPOLE_Dtorholnu;
  if(MctkPID[0]==  223&&MctkPID[1]==  13&&MctkPID[2]== -14) { SelectionValid = true; Mcmode.push_back(-322);} // omega mu- anti-nu_mu       PHOTOS   SLPOLE_Dtoomegalnu;
  if(MctkPID[0]== 11&&MctkPID[1]== -12&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(-323);} // anti-K0         mu- anti-nu_mu 
  if(MctkPID[0]== 11&&MctkPID[1]== -12&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(-324);} // anti-K*0        mu- anti-nu_mu 
  if(MctkPID[0]==333&&MctkPID[1]==  11&&MctkPID[2]==   -12) { SelectionValid = true; Mcmode.push_back(-325);} // phi        mu- anti-nu_mu 
  if(MctkPID[0]==9010221&&MctkPID[1]==11&&MctkPID[2]== -12) { SelectionValid = true; Mcmode.push_back(-326);} // f_0    mu- anti-nu_mu 
  if(MctkPID[0]==321&&MctkPID[1]==-211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(-327);} // K+ K- pi-                       PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==-211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(-328);} // pi+  pi-  pi-                   PHSP;
  if(MctkPID[0]==111&&MctkPID[1]== 111&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(-329);} // pi-  pi0  pi0                   PHSP;
  if(MctkPID[0]==311&&MctkPID[1]== 111&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(-330);} // K0   pi-  pi0                   D_DALITZ;
  if(MctkPID[0]==111&&MctkPID[1]==-211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(-331);} // anti-K0   pi-  pi0              D_DALITZ;
  if(MctkPID[0]==321&&MctkPID[1]==-211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(-332);} // K+  pi-  pi-                    D_DALITZ;
  if(MctkPID[0]==211&&MctkPID[1]==-211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(-333);} // K-  pi-  pi+                    D_DALITZ;
  if(MctkPID[0]==321&&MctkPID[1]==-321&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(-334);} // K+ K- K-                        PHSP;
  if(MctkPID[0]==211&&MctkPID[1]==-321&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(-335);} // K- K- pi+                       PHSP;
  if(MctkPID[0]==311&&MctkPID[1]==-211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(-336);} // anti-K0   K0  pi-               PHSP;
  if(MctkPID[0]==223&&MctkPID[1]== 111&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(-337);} // omega pi-  pi0               PHSP;
  if(MctkPID[0]==310&&MctkPID[1]== 111&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(-338);} //  K- K_S0 pi0               PHSP;
  if(MctkPID[0]==310&&MctkPID[1]== 310&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(-339);} // K_S0 K_S0  pi-               PHSP;
 }

 if(Nint==4) {
  if(MctkPID[0]==321&&MctkPID[1]== 111&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-401);} //0.021            K- K+ pi- pi0     PHSP;       #gamma41-gamma42*0.492 = 5.1-6.1*0.492 = 2.1
  if(MctkPID[0]==321&&MctkPID[1]==-211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(-402);} //0.0008            anti-K0 K+ pi-  pi-    PHSP;       # gamma43(1.64)*2-gamma44(7.2)*0.666*0.666=0.0008
  if(MctkPID[0]==311&&MctkPID[1]== 211&&MctkPID[2]==-211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(-403);} //0.0192           K0  K-  pi-  pi+  PHSP;  #[0.0199]gamma45
  if(MctkPID[0]==333&&MctkPID[1]== 211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-404);} //0.0121           phi  pi- pi- pi+  PHSP;       #gamma 47
  if(MctkPID[0]==223&&MctkPID[1]== 211&&MctkPID[2]==-211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(-405);} //0.011            omega pi- pi- pi+ PHSP;         #gamma 72 ==> 1.6-0.5=1.1
  if(MctkPID[0]==211&&MctkPID[1]==-211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(-406);} //0.0058           anti-K0  pi- pi- pi+   PHSP;         #gamma 91*2
  }

 if(Nint==5) {
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(-501);} // 0.0009           K- K+ pi- pi- pi+ PHSP;       # gamma 51
  if(MctkPID[0]==211&&MctkPID[1]==130&&MctkPID[2]== 130&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-502);} // 0.00083          K_L0 K_L0 pi- pi- pi+  PHSP;  #[0.0005]gamma 52
  if(MctkPID[0]==310&&MctkPID[1]==310&&MctkPID[2]== 211&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-503);} // 0.00083          K_S0 K_S0 pi- pi- pi+  PHSP;  #[0.0005]gamma 52
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(-504);} // 0.008            pi- pi- pi- pi+ pi+  PHSP;      #[0.0067]gamma 66
 }

 if(Nint==6) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==111&&MctkPID[3]==-211&&MctkPID[4]==-211&&MctkPID[5]== -211) { SelectionValid = true; Mcmode.push_back(-601);} // 0.0036           pi- pi- pi- pi+ pi+ pi0 PHSP;   #[0.0177]gamma 71(1.7)-gamma72(1.1)*0.891-gamma73(3.61)*0.445*0.227=0.0036
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(-1102);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(-1103);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(-1104);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(-1105);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(-1106);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(-1107);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(-1108);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(-1109);

}
}



void DsDsmcmode::DspmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  Vint KsID,EtaID,OmgID,EtapID,PhiID,TauID;
      KsID.clear();
      EtaID.clear();
      OmgID.clear();
      EtapID.clear();
      PhiID.clear();
      TauID.clear();
      int IfKs   = 1;
      int IfEta  = 1;
      int IfOmg  = 1;
      int IfEtap = 1;
      int IfPhi  = 1;
      int IfTau  = 1;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      //if ((*iter_mc)->primaryParticle()) continue;
      if (!(*iter_mc)->decayFromGenerator()) continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 431)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22) continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
//2016-9-7 mahl
//      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 431;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      //if (!MotherParticleDecay) continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid) continue;

      if(IfKs==1){
       if((((*iter_mc)->mother()).particleProperty())==310) KsID.push_back(pdgid);
      }

      if(IfEta==1){
       if((((*iter_mc)->mother()).particleProperty())==221) EtaID.push_back(pdgid);
      }
      if(IfOmg==1){
       if((((*iter_mc)->mother()).particleProperty())==223) OmgID.push_back(pdgid);
      }
      if(IfEtap==1){
       if((((*iter_mc)->mother()).particleProperty())==331) EtapID.push_back(pdgid);
      }
      if(IfPhi==1){
       if((((*iter_mc)->mother()).particleProperty())==333) PhiID.push_back(pdgid);
      }
      if(IfTau==1){
       if((((*iter_mc)->mother()).particleProperty())==-15) TauID.push_back(pdgid);
      }

      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue; 
      if((((*iter_mc)->mother()).particleProperty())==-15) continue; 
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue; 
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue; 
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;
      if((((*iter_mc)->mother()).particleProperty())==223) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
//2016-9-9 mahl
/*
      if((((*iter_mc)->mother()).particleProperty())==333) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==333) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==333) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==333) continue;
      if(((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==333) continue;
      if((((*iter_mc)->mother()).particleProperty())==213) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==213) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==213) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==213) continue;
      if(((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==213) continue;
*/
      if((((*iter_mc)->mother()).particleProperty())==-15) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue;

      if(pdgid==111)    okay1 = true;

//mahl 2016-9-7
if(pdgid==310){
Vint daughter;
daughter.clear();
int size = ((*iter_mc)->daughterList()).size();
for(int i=0;i<size;i++){ 
if(((*iter_mc)->daughterList())[i]->particleProperty()==-22) continue; 
daughter.push_back(i); 
}
int ndaughter = daughter.size();

if(ndaughter==2&&abs(((*iter_mc)->daughterList())[0]->particleProperty()) == 111)   {
        //okay1 = true;
         pdgid = 3100;
      }

      if(ndaughter==2&&abs(((*iter_mc)->daughterList())[0]->particleProperty()) == 211)   {
        //okay1 = true;
         pdgid = 3101;
      }
}

      if(pdgid==3100)    okay1 = true;
      if(pdgid==3101)    okay1 = true;

      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
      if(abs(pdgid)==331)    okay1 = true;
      if(abs(pdgid)==223)    okay1 = true;

//2016-9-7 mahl
//2016-9-9 mahl
//      if(abs(pdgid)==333)    okay1 = true;

      if(abs(pdgid)==13)    okay1 = true;
      if(abs(pdgid)==14)    okay1 = true;
      if(abs(pdgid)==15)    okay1 = true;
      if(abs(pdgid)==16)    okay1 = true;
      if(((*iter_mc)->daughterList()).size()==0) okay1 = true;
      if(!okay1) continue;
      finalID.push_back(pdgid);
      IDtk.push_back(pdgid);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

    }


// Judging the Ks, eta, Omg, etap modes by the particles in the final states
    int Ksmode = 0;
    int Etamode = 0;
    int Omgmode = 0;
    int Etapmode = 0;
    int Phimode = 0;
    int Taumode = 0;

    if(KsID.size()>0)
    sort(KsID.begin(),KsID.end(),greater<int>());
    if(EtaID.size()>0)
    sort(EtaID.begin(),EtaID.end(),greater<int>());
    if(OmgID.size()>0)
    sort(OmgID.begin(),OmgID.end(),greater<int>());
    if(EtapID.size()>0)
    sort(EtapID.begin(),EtapID.end(),greater<int>());
    if(PhiID.size()>0)
    sort(PhiID.begin(),PhiID.end(),greater<int>());
    if(TauID.size()>0)
    sort(TauID.begin(),TauID.end(),greater<int>());

    if(KsID.size()==2&&KsID[0]==211&&KsID[1]==-211) Ksmode = 1;
//    if(KsID.size()==2&&KsID[0]==111&&KsID[1]== 111) Ksmode = 2;

    if(EtaID.size()==2&&EtaID[0]==22&&EtaID[1]==22) Etamode = 1;
    if(EtaID.size()==3&&EtaID[0]==211&&EtaID[1]==111&&EtaID[2]==-211) Etamode = 2;

    if(OmgID.size()==3&&OmgID[0]==211&&OmgID[1]==111&&OmgID[2]==-211) Omgmode = 1;

    if(EtapID.size()==3&&EtapID[0]==221&&EtapID[1]==211&&EtapID[2]==-211) Etapmode = 1;

    if(EtapID.size()==2&&EtapID[0]==113&&EtapID[1]==22) Etapmode = 2;
    if(EtapID.size()==3&&EtapID[0]==211&&EtapID[1]==22&&EtapID[2]==-211) Etapmode = 3;

    if(PhiID.size()==2&&PhiID[0]==321&&PhiID[1]==-321) Phimode = 1;

    if(TauID.size()==2&&TauID[0]==211&&TauID[1]==-16) Taumode = 1;
    if(TauID.size()==3&&TauID[0]== 12&&TauID[1]==-11&&TauID[2]==-16) Taumode = 2;
    if(TauID.size()==3&&TauID[0]== 14&&TauID[1]==-13&&TauID[2]==-16) Taumode = 3;
    if(TauID.size()==2&&TauID[0]==213&&TauID[1]==-16) Taumode = 4;

//    cout<<"test here::"<<Taumode<<","<<TauID.size()<<endl;

    sort(finalID.begin(),finalID.end(),greater<int>());

    int Ntot = finalID.size();
//if(Ntot==3) cout<<"+  "<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<endl;
    //cout<<" Ntot: "<<Ntot<<endl;
    //for(int ntot=0;ntot<Ntot;ntot++) cout<<finalID[ntot]<<endl;
    if(Ntot==2) Mcmodef = 31102;
    if(Ntot==3) Mcmodef = 31103;
    if(Ntot==4) Mcmodef = 31104;
    if(Ntot==5) Mcmodef = 31105;
    if(Ntot==6) Mcmodef = 31106;
    if(Ntot==7) Mcmodef = 31107;
    if(Ntot==8) Mcmodef = 31108;
    if(Ntot==9) Mcmodef = 31109;
    if(Ntot>9)  Mcmodef = 31110;

/*
if(Ntot==2) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<endl;
if(Ntot==3) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<endl;
if(Ntot==4) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<endl;
if(Ntot==5) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<endl;
if(Ntot==6) cout<<"fbbbbf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<","<<finalID[5]<<endl;
*/

    if(Ntot==2) {
      if(finalID[0]==12&&finalID[1]==-11)  { SelectionValid = true; Mcmodef = 3700;} // D+-->e+v
      if(finalID[0]==14&&finalID[1]==-13)  { SelectionValid = true; Mcmodef = 3701;} // D+-->mu+v
      if(Taumode==1&&finalID[0]==16&&finalID[1]==-15)  { SelectionValid = true; Mcmodef = 37021;} // D+-->tau+v,piv
      if(Taumode==2&&finalID[0]==16&&finalID[1]==-15)  { SelectionValid = true; Mcmodef = 37022;} // D+-->tau+v,evv
      if(Taumode==3&&finalID[0]==16&&finalID[1]==-15)  { SelectionValid = true; Mcmodef = 37023;} // D+-->tau+v,muvv
      if(Taumode==4&&finalID[0]==16&&finalID[1]==-15)  { SelectionValid = true; Mcmodef = 37024;} // D+-->tau+v,rhov

      if(finalID[0]==3100&&finalID[1]==321)  { SelectionValid = true; Mcmodef = 31040;} // D+-->KSK+
      if(finalID[0]==3101&&finalID[1]==321)  { SelectionValid = true; Mcmodef = 3104;} // D+-->KSK+
      if(finalID[0]==3100&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3200;} // D+-->KSpi+ (ks->pi0 pi0)
      if(finalID[0]==3101&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3201;} // D+-->KSpi+ (ks->pi+ pi-)
      if(finalID[0]==321&&finalID[1]==130)  { SelectionValid = true; Mcmodef = 31041;}// D+-->K_L0 K+

      if(Etamode==1&&finalID[0]==221&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3113;}  // D+-->Eta(gg)pi+
      if(Etamode==2&&finalID[0]==221&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3114;} // D+-->Eta(pipipi0)pi+

      if(Etamode==1&&finalID[0]==321&&finalID[1]==221)  { SelectionValid = true; Mcmodef = 3131;}  // D+-->Eta(gg)K+
      if(Etamode==2&&finalID[0]==321&&finalID[1]==221)  { SelectionValid = true; Mcmodef = 3132;} // D+-->Eta(pipipi0)K+

      if(Etapmode==1&&Etamode==1&&finalID[0]==331&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3115;}  // D+-->Etap(pipieta(gg))pi+
      if(Etapmode==2&&finalID[0]==331&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3116;} // D+-->Etap(gamrho)pi+
      if(Etapmode==3&&finalID[0]==331&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 31161;} // D+-->Etap(gamrho)pi+
      if(Etapmode==1&&Etamode==2&&finalID[0]==331&&finalID[1]==211)  { SelectionValid = true; Mcmodef = 3117;}  // D+-->Etap(pipieta(3pi))pi+

      if(Etapmode==1&&finalID[0]==331&&finalID[1]==321)  { SelectionValid = true; Mcmodef = 3133;}  // D+-->Etap(pipieta(gg))K+
      if(Etapmode==2&&finalID[0]==331&&finalID[1]==321)  { SelectionValid = true; Mcmodef = 3134;} // D+-->Etap(gamrho)K+
    }

    if(Ntot==3) {
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 3101;} // D+-->K+K-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 3103;} // D+-->pi+pi+pi-
      if(finalID[0]==3101&&finalID[1]==321&&finalID[2]==111)  { SelectionValid = true; Mcmodef = 3105;} // D+-->KSK+pi0
      if(finalID[0]==3101&&finalID[1]==3101&&finalID[2]== 211)  { SelectionValid = true; Mcmodef = 3109;} // D+-->KSKSpi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 3106;} // D+-->K-pi+pi+
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 3107;} // D+-->K+pi+pi-
      if(finalID[0]==3101&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 3108;} // D+-->KSpi+pi0
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 31081;}// D+-->K_L0 pi+ pi0

      if(Etamode==1&&finalID[0]==  221&&finalID[1]==  12&&finalID[2]== -11) { SelectionValid = true; Mcmodef = 3061;} // eta(2g)   e+  nu_e        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etamode==2&&finalID[0]==  221&&finalID[1]==  12&&finalID[2]== -11) { SelectionValid = true; Mcmodef = 3062;} // eta(pipipi0)   e+  nu_e        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etapmode==1&&Etamode==1&&finalID[0]==  331&&finalID[1]==  12&&finalID[2]== -11) { SelectionValid = true; Mcmodef = 3071;} // eta'(pipieta(gg))  e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetaplnu;
      if(Etapmode==2&&finalID[0]==  331&&finalID[1]==  12&&finalID[2]== -11) { SelectionValid = true; Mcmodef = 3072;} // eta'(gamrho)  e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetaplnu;

      if(Etamode==1&&finalID[0]==  221&&finalID[1]==  14&&finalID[2]== -13) { SelectionValid = true; Mcmodef = 3088;} // eta(2g)   mu+  nu_mu        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etamode==2&&finalID[0]==  221&&finalID[1]==  14&&finalID[2]== -13) { SelectionValid = true; Mcmodef = 3089;} // eta(pipipi0)   mu+  nu_mu        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etapmode==1&&Etamode==1&&finalID[0]==  331&&finalID[1]==  14&&finalID[2]== -13) { SelectionValid = true; Mcmodef = 3090;} // eta'(pipieta(gg))  mu+ nu_mu        PHOTOS   SLBKPOLE_Dtoetaplnu;
      if(Etapmode==2&&finalID[0]==  331&&finalID[1]==  14&&finalID[2]== -13) { SelectionValid = true; Mcmodef = 3091;} // eta'(gamrho)  mu+  nu_mu        PHOTOS   SLBKPOLE_Dtoetaplnu;
      if(Etapmode==3&&finalID[0]==  331&&finalID[1]==  14&&finalID[2]== -13) { SelectionValid = true; Mcmodef = 30911;} // eta'(gamrho)  mu+  nu_mu        PHOTOS   SLBKPOLE_Dtoetaplnu;


      
      if(Etamode==1&&finalID[0]==221&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 3118;} // D+-->etapi+pi0
      if(Etamode==2&&finalID[0]==221&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 31181;} // D+-->etapi+pi0
      if(Etamode==0&&finalID[0]==221&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 31182;} // D+-->etapi+pi0

      if(finalID[0]==331&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 3119;} // D+-->etappi+pi0
      if(Etapmode==1&&Etamode==1&&finalID[0]==331&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 31191;} // D+-->etappi+pi0 &&etap->pipieta
      if(Etapmode==1&&Etamode==2&&finalID[0]==331&&finalID[1]==211&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 31192;} // D+-->etappi+pi0 &&etap->pipieta
      if(finalID[0]==3101&&finalID[1]==3101&&finalID[2]==321)  { SelectionValid = true; Mcmodef = 3130;} // D+-->KSKSK+
      if(finalID[0]==3101&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 32011;} // D+-->K_s0e +ne
      if(finalID[0]==130&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 3202;} // D+-->K_L0e +ne
      if(finalID[0]==3101&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 3203;} // D+-->K_S0 mu+nu
      if(finalID[0]==3101&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 32031;} // D+-->K_S0 mu+nu
      if(finalID[0]==130&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 3204;} // D+-->K_L0 mu+nu
      if(finalID[0]==111&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 3205;} // D+-->pi0e+ne
      if(finalID[0]==111&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 3206;} // D+-->pi0mu+ne
    }

    if(Ntot==4) {
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3102;} // D+-->K-K+pi+pi0
      if(finalID[0]==3101&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3110;} // D+-->KSK-pi+pi+
      if(finalID[0]==3101&&finalID[1]==321&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 31101;}// D+-->KSK+pi-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 130&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3111;} // D+-->KLK-pi+pi+
      if(finalID[0]==321&&finalID[1]==130&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 31111;}// D+-->KLK+pi-pi+
      if(finalID[0]==3101&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 3120;} // D+-->KSpi+pi+pi-
      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 3211;} // D--->gamma gamma e+ne
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 3212;} // D--->pi0 pi0 e+ne
      if(finalID[0]==211&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = 3213;} // D--->pi+ pi- e+ne
      if(finalID[0]==321&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3214;} // D--->K+ K- e+ne
      if(finalID[0]==211&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3215;} // D--->K- pi+ e+ne
      if(finalID[0]==321&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 3216;} // D--->K+ pi- e+ne
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 3217;} // D--->Ks pi0 e+ne
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 32171;} // D--->Ks pi0 e+ne
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 3218;} // D--->KL pi0 e+ne

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 3221;} // D--->gamma gamma mu+nmu
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 3222;} // D--->pi0 pi0 mu+nmu
      if(finalID[0]==211&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 3223;} // D--->pi+ pi- mu+nmu
      //-111->-211
      if(finalID[0]==321&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3224;} // D--->K+ K- mu+nmu
      if(finalID[0]==211&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 3225;} // D--->K- pi+ mu+nmu
      if(finalID[0]==321&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 3226;} // D--->K+ pi- mu+nmu
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 3227;} // D--->Ks pi0 mu+nmu
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 32271;} // D--->Ks pi0 mu+nmu
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 3228;} // D--->KL pi0 mu+nmu



    }

    if(Ntot==5) {
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 3231;} // D--->pi+pi-pi0 e+ne
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 3232;} // D--->pi+pi-eta e+ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 14&&finalID[3]== -13&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 3241;} // D--->pi+pi-pi0 mu+nmu
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]== 14&&finalID[3]== -13&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 3242;} // D--->pi+pi-eta mu+nmu
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-211&&finalID[4]==-321) { SelectionValid = true; Mcmodef = 3112;} // D+-->K-K+pi+pi+pi-

    }
  }


}


void DsDsmcmode::DsnmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  Vint KsID,EtaID,OmgID,EtapID,PhiID,TauID;
      KsID.clear();
      EtaID.clear();
      OmgID.clear();
      EtapID.clear();
      PhiID.clear();
      TauID.clear();
      int IfKs   = 1;
      int IfEta  = 1;
      int IfOmg  = 1;
      int IfEtap = 1;
      int IfPhi  = 1;
      int IfTau  = 1;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      //if ((*iter_mc)->primaryParticle()) continue;
      if (!(*iter_mc)->decayFromGenerator()) continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid==-431)  {ChargD = -1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22) continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
//2016-9-7 mahl
//      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = -431;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      //if (!MotherParticleDecay) continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid) continue;

      if(IfKs==1){
       if((((*iter_mc)->mother()).particleProperty())==310) KsID.push_back(pdgid);
      }
      if(IfEta==1){
       if((((*iter_mc)->mother()).particleProperty())==221) EtaID.push_back(pdgid);
      }
      if(IfOmg==1){
       if((((*iter_mc)->mother()).particleProperty())==223) OmgID.push_back(pdgid);
      }
      if(IfEtap==1){
       if((((*iter_mc)->mother()).particleProperty())==331) EtapID.push_back(pdgid);
      }
      if(IfPhi==1){
       if((((*iter_mc)->mother()).particleProperty())==333) PhiID.push_back(pdgid);
      }

      //if(pdgid==15) cout<<"test bbbb::"<<endl;
//      cout<<"test bbbb::"<<pdgid<<","<<(((*iter_mc)->mother()).particleProperty())<<endl;

      if(IfTau==1){
       if((((*iter_mc)->mother()).particleProperty())==15)  TauID.push_back(pdgid);
//       cout<<"test bbbb::"<<pdgid<<","<<(((*iter_mc)->mother()).particleProperty())<<endl;
      }

      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue; 
      if(abs(((*iter_mc)->mother()).particleProperty())==15) continue; 
      if((((*iter_mc)->mother()).mother()).particleProperty()==15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==15) continue; 
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==15) continue; 
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;
      if((((*iter_mc)->mother()).particleProperty())==223) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
//2016-9-9 mahl
/*
      if((((*iter_mc)->mother()).particleProperty())==333) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==333) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==333) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==333) continue;
      if(((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==333) continue;
      if((((*iter_mc)->mother()).particleProperty())==-213) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==-213) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-213) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-213) continue;
      if(((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==-213) continue;
*/
      if((((*iter_mc)->mother()).particleProperty())==15) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==15) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==15) continue;

      if(pdgid==111)    okay1 = true;

//mahl 2016-9-7
if(pdgid==310){
Vint daughter;
daughter.clear();
int size = ((*iter_mc)->daughterList()).size();
for(int i=0;i<size;i++){ 
if(((*iter_mc)->daughterList())[i]->particleProperty()==-22) continue; 
daughter.push_back(i); 
}
int ndaughter = daughter.size();

if(ndaughter==2&&abs(((*iter_mc)->daughterList())[0]->particleProperty()) == 111)   {
        //okay1 = true;
         pdgid = 3100;
      }

      if(ndaughter==2&&abs(((*iter_mc)->daughterList())[0]->particleProperty()) == 211)   {
        //okay1 = true;
         pdgid = 3101;
      }
}

      if(pdgid==3100)    okay1 = true;
      if(pdgid==3101)    okay1 = true;

//      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
      if(abs(pdgid)==331)    okay1 = true;
      if(abs(pdgid)==223)    okay1 = true;

//2016-9-7 mahl
//2016-9-9 mahl
//      if(abs(pdgid)==333)    okay1 = true;
      if(abs(pdgid)==13)    okay1 = true;
      if(abs(pdgid)==14)    okay1 = true;
      if(abs(pdgid)==15)    okay1 = true;
      if(abs(pdgid)==16)    okay1 = true;

//      cout<<"test aaa::"<< pdgid <<endl;

      if(((*iter_mc)->daughterList()).size()==0) okay1 = true;
      if(!okay1) continue;

//      cout<<"test bbb::"<< pdgid <<endl;

      finalID.push_back(pdgid);
      IDtk.push_back(pdgid);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

    }

// Judging the Ks, eta, Omg, etap modes by the particles in the final states
    int Ksmode = 0;
    int Etamode = 0;
    int Omgmode = 0;
    int Etapmode = 0;
    int Phimode = 0;
    int Taumode = 0;

    if(KsID.size()>0)
    sort(KsID.begin(),KsID.end(),greater<int>());
    if(EtaID.size()>0)
    sort(EtaID.begin(),EtaID.end(),greater<int>());
    if(OmgID.size()>0)
    sort(OmgID.begin(),OmgID.end(),greater<int>());
    if(EtapID.size()>0)
    sort(EtapID.begin(),EtapID.end(),greater<int>());
    if(PhiID.size()>0)
    sort(PhiID.begin(),PhiID.end(),greater<int>());
    if(TauID.size()>0)
    sort(TauID.begin(),TauID.end(),greater<int>());

    if(KsID.size()==2&&KsID[0]==211&&KsID[1]==-211) Ksmode = 1;
//    if(KsID.size()==2&&KsID[0]==111&&KsID[1]== 111) Ksmode = 2;

    if(EtaID.size()==2&&EtaID[0]==22&&EtaID[1]==22) Etamode = 1;
    if(EtaID.size()==3&&EtaID[0]==211&&EtaID[1]==111&&EtaID[2]==-211) Etamode = 2;

    if(OmgID.size()==3&&OmgID[0]==211&&OmgID[1]==111&&OmgID[2]==-211) Omgmode = 1;

    if(EtapID.size()==3&&EtapID[0]==221&&EtapID[1]==211&&EtapID[2]==-211) Etapmode = 1;
    if(EtapID.size()==2&&EtapID[0]==113&&EtapID[1]==22) Etapmode = 2;
    if(EtapID.size()==3&&EtapID[0]==211&&EtapID[1]==22&&EtapID[2]==-211) Etapmode = 3;

    if(PhiID.size()==2&&PhiID[0]==321&&PhiID[1]==-321) Phimode = 1;

    if(TauID.size()==2&&TauID[0]== 16&&TauID[1]==-211) Taumode = 1;
    if(TauID.size()==3&&TauID[0]== 16&&TauID[1]== 11&&TauID[2]==-12) Taumode = 2;
    if(TauID.size()==3&&TauID[0]== 16&&TauID[1]== 13&&TauID[2]==-14) Taumode = 3;
    if(TauID.size()==2&&TauID[0]== 16&&TauID[1]==-213) Taumode = 4;

//    cout<<"test here::"<<","<<Taumode<<","<<TauID.size()<<","<<TauID[0]<<","<<TauID[1]<<endl;

    sort(finalID.begin(),finalID.end(),greater<int>());

    int Ntot = finalID.size();

//if(Ntot==3) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<endl;
    //cout<<"m Ntot: "<<Ntot<<endl;
    if(Ntot==2) Mcmodef = -31102;
    if(Ntot==3) Mcmodef = -31103;
    if(Ntot==4) Mcmodef = -31104;
    if(Ntot==5) Mcmodef = -31105;
    if(Ntot==6) Mcmodef = -31106;
    if(Ntot==7) Mcmodef = -31107;
    if(Ntot==8) Mcmodef = -31108;
    if(Ntot==9) Mcmodef = -31109;
    if(Ntot>9)  Mcmodef = -31110;

/*
    cout<<"faaaaf"<<Ntot<<endl;

if(Ntot==2) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<endl;
if(Ntot==3) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<endl;
if(Ntot==4) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<endl;
if(Ntot==5) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<endl;
if(Ntot==6) cout<<"faaaaf"<<Ntot<<","<<finalID[0]<<","<<finalID[1]<<","<<finalID[2]<<","<<finalID[3]<<","<<finalID[4]<<","<<finalID[5]<<endl;
*/

    if(Ntot==2) {
      if(finalID[0]==11&&finalID[1]==-12)  { SelectionValid = true; Mcmodef = -3700;} // D+-->e+v
      if(finalID[0]==13&&finalID[1]==-14)  { SelectionValid = true; Mcmodef = -3701;} // D+-->mu+v
      if(Taumode==1&&finalID[0]==15&&finalID[1]==-16)  { SelectionValid = true; Mcmodef = -37021;} // D+-->tau+v,piv
//      if(finalID[0]==15&&finalID[1]==-16)  { SelectionValid = true; Mcmodef = -37021;} // D+-->tau+v,piv
      if(Taumode==2&&finalID[0]==15&&finalID[1]==-16)  { SelectionValid = true; Mcmodef = -37022;} // D+-->tau+v,evv
      if(Taumode==3&&finalID[0]==15&&finalID[1]==-16)  { SelectionValid = true; Mcmodef = -37023;} // D+-->tau+v,muvv
      if(Taumode==4&&finalID[0]==15&&finalID[1]==-16)  { SelectionValid = true; Mcmodef = -37024;} // D+-->tau+v,rhov

      if(finalID[0]==3100&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -31040;}  // D--->KSK-
      if(finalID[0]==3101&&finalID[1]==-321)  { SelectionValid = true; Mcmodef =-3104;}  // D--->KSK-
      if(finalID[0]==3100&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3200;} // D--->KSpi- (ks->pi0 pi0)
      if(finalID[0]==3101&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3201;} // D--->KSpi- (ks->pi+ pi-)
      if(finalID[0]==130&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -31041;} // D--->K_L0 K-

      if(Etamode==1&&finalID[0]==221&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3113;}  // D+-->Eta(gg)pi+
      if(Etamode==2&&finalID[0]==221&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3114;} // D+-->Eta(pipipi0)pi+

      if(Etamode==1&&finalID[0]==221&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -3131;}  // D+-->Eta(gg)K+
      if(Etamode==2&&finalID[0]==221&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -3132;} // D+-->Eta(pipipi0)K+

      if(Etapmode==1&&Etamode==1&&finalID[0]==331&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3115;}  // D+-->Etap(pipieta(gg))pi+
      if(Etapmode==2&&finalID[0]==331&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3116;} // D+-->Etap(gamrho)pi+
      if(Etapmode==3&&finalID[0]==331&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -31161;} // D+-->Etap(gamrho)pi+
      if(Etapmode==1&&Etamode==2&&finalID[0]==331&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -3117;}  // D+-->Etap(pipieta(3pi))pi+

      if(Etapmode==1&&finalID[0]==331&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -3133;}  // D+-->Etap(pipieta(gg))K+
      if(Etapmode==2&&finalID[0]==331&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -3134;} // D+-->Etap(gamrho)K+

    }

    if(Ntot==3) {
      if(finalID[0]==321&&finalID[1]==-211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -3101;} // D--->K+K-pi-
      if(finalID[0]==211&&finalID[1]==-211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -3103;} // D--->pi+pi-pi-
      if(finalID[0]==3101&&finalID[1]== 111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -3105;} // D--->KSK-pi0
      

      if(Etamode==1&&finalID[0]==  221&&finalID[1]==  11&&finalID[2]== -12) { SelectionValid = true; Mcmodef = -3061;} // eta   e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etamode==2&&finalID[0]==  221&&finalID[1]==  11&&finalID[2]== -12) { SelectionValid = true; Mcmodef=-3062;} // eta   e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etapmode==1&&Etamode==1&&finalID[0]==  331&&finalID[1]==  11&&finalID[2]== -12) { SelectionValid = true; Mcmodef = -3071;} // eta'(pipieta(gg))  e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetaplnu;
      if(Etapmode==2&&finalID[0]==  331&&finalID[1]==  11&&finalID[2]== -12) { SelectionValid = true; Mcmodef = -3072;} // eta'(gamrho)  e-  anti-nu_e        PHOTOS   SLBKPOLE_Dtoetaplnu;

      if(Etamode==1&&finalID[0]==  221&&finalID[1]==  13&&finalID[2]== -14) { SelectionValid = true; Mcmodef = -3088;} // eta   mu-  anti-nu_mu        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etamode==2&&finalID[0]==  221&&finalID[1]==  13&&finalID[2]== -14) { SelectionValid = true; Mcmodef=-3089;} // eta   mu-  anti-nu_mu        PHOTOS   SLBKPOLE_Dtoetalnu;
      if(Etapmode==1&&Etamode==1&&finalID[0]==  331&&finalID[1]==  13&&finalID[2]== -14) { SelectionValid = true; Mcmodef = -3090;} // eta'(pipieta(gg))  mu-  anti-nu_mu        PHOTOS   SLBKPOLE_Dtoetaplnu;
      if(Etapmode==2&&finalID[0]==  331&&finalID[1]==  13&&finalID[2]== -14) { SelectionValid = true; Mcmodef = -3091;} // eta'(gamrho)  mu-  anti-nu_mu        PHOTOS   SLBKPOLE_Dtoetaplnu;
      if(Etapmode==3&&finalID[0]==  331&&finalID[1]==  13&&finalID[2]== -14) { SelectionValid = true; Mcmodef = -30911;} // eta'(gamrho)  mu-  anti-nu_mu        PHOTOS   SLBKPOLE_Dtoetaplnu;

      if(finalID[0]==130&&finalID[1]== 111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -31051;}// D--->K_L0 K- pi0
      if(finalID[0]==321&&finalID[1]==-211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -3106;} // D--->K+pi-pi-
      if(finalID[0]==211&&finalID[1]==-211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -3107;} // D--->K-pi-pi+
      if(finalID[0]==3101&&finalID[1]== 111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -3108;} // D--->KSpi-pi0
      if(finalID[0]==130&&finalID[1]== 111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -31081;}// D--->K_L0 pi- pi0
      if(finalID[0]==3101&&finalID[1]== 3101&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -3109;} // D--->KSKSpi-

      if(Etamode==1&&finalID[0]==221&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -3118;} // D--->etapi-pi0
      if(Etamode==2&&finalID[0]==221&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -31181;} // D--->etapi-pi0
      if(Etamode==0&&finalID[0]==221&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -31182;} // D--->etapi-pi0

      if(finalID[0]==331&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -3119;} // D--->etappi-pi0
      if(Etapmode==1&&Etamode==1&&finalID[0]==331&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -31191;} // D--->etappi-pi0&&etap->pipieta
      if(Etapmode==1&&Etamode==2&&finalID[0]==331&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -31192;} // D--->etappi-pi0&&etap->pipieta

      if(finalID[0]==3101&&finalID[1]== 3101&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -3130;} // D--->KSKSK-


      if(finalID[0]==3101&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -32011;} // D--->K_s0e-ne
      if(finalID[0]==130&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -3202;} // D--->K_L0e-ne
      if(finalID[0]==3101&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -3203;} // D--->K_S0 mu-nu
      if(finalID[0]==130&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -3204;} // D--->K_L0 mu-nu
      if(finalID[0]==111&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -3205;} // D--->pi0e-ne
      if(finalID[0]==111&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -3206;} // D--->pi0mu-nmu
    }

    if(Ntot==4) {
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = -3102;} // D--->K+K-pi-pi0

      if(finalID[0]==3101&&finalID[1]==321&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -3110;} // D--->KSK+pi-pi-
      if(finalID[0]==3101&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = -31101;}// D--->KSK-pi+pi-
      if(finalID[0]==321&&finalID[1]==130&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -3111;} // D--->KLK+pi-pi-
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = -31111;}// D--->KLK-pi+pi-
      if(finalID[0]==3101&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -3120;} // D--->KSpi+pi-pi-

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -3211;} // D--->gamma gamma e-ne
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -3212;} // D--->pi0 pi0 e-ne
      if(finalID[0]==211&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = -3213;} // D--->pi+ pi- e-ne
      if(finalID[0]==321&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -3214;} // D--->K+ K- e-ne
      if(finalID[0]==321&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -3215;} // D--->K+ pi- e-ne
      if(finalID[0]==211&&finalID[1]== 11&&finalID[2]== -12&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -3216;} // D--->K- pi+ e-ne
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -3217;} // D--->Ks pi0 e-ne
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -32171;} // D--->Ks pi0 e-ne
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -3218;} // D--->KL pi0 e-ne

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -3221;} // D--->gamma gamma mu-nmu
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -3222;} // D--->pi0 pi0 mu-nmu
      if(finalID[0]==211&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -3223;} // D--->pi+ pi- mu-nmu
      //liumh: -111->-211
      if(finalID[0]==321&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -3224;} // D--->K+ K- mu-nmu
      if(finalID[0]==321&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -3225;} // D--->K+ pi- mu-nmu
      if(finalID[0]==211&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -3226;} // D--->K- pi+ mu-nmu
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -3227;} // D--->Ks pi0 mu-nmu
      if(finalID[0]==3101&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -32271;} // D--->Ks pi0 mu-nmu
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -3228;} // D--->KL pi0 mu-nmu
    }

    if(Ntot==5) {
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -3231;} // D--->pi+pi-pi0 e-ne
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==  11&&finalID[3]== -12&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -3232;} // D--->pi+pi-eta e-ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -3241;} // D--->pi+pi-pi0 mu-nmu
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==  13&&finalID[3]== -14&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -3242;} // D--->pi+pi-eta mu-nmu

      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&finalID[4]==-321) { SelectionValid = true; Mcmodef = -3112;} // D--->K+K-pi-pi-pi+
    }
  }

}


void DsDsmcmode::Psimcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();
  int vpho = 80022;
    Mcmode.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);
    int aa=0,bb=0,cc=0,dd=0,pre=0;
    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      //if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid_mother = ((*iter_mc)->mother()).particleProperty();
      //if(pdgid_mother!=vpho)                                            continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;

      //if(pdgid==-22)                                                       continue;
      //if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      //if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      //
      //if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 431;

//      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
//      }
//      if (!MotherParticleDecay)                                            continue;

      bool DDecayValid = false;

//      cout<<"In mode::"<<pdgid<<","<<pdgid_mother<<endl;
      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

//      if((((*iter_mc)->mother()).particleProperty())!=vpho) continue;


      //if(pdgid==22)             MctkP = true;
      //if(fabs(pdgid)==11)       MctkP = true;
      //if(fabs(pdgid)==12)       MctkP = true;
      //if(fabs(pdgid)==13)       MctkP = true;
      //if(fabs(pdgid)==14)       MctkP = true;
      //if(fabs(pdgid)==15)       MctkP = true;
      //if(fabs(pdgid)==16)       MctkP = true;
      //if(pdgid==111)            MctkP = true;
      //if(pdgid==113)            MctkP = true;
      //if(pdgid==30113)          MctkP = true;
      //if(pdgid==221)            MctkP = true;
      //if(pdgid==331)            MctkP = true;
      //if(pdgid==310)            MctkP = true;
      //if(pdgid==130)            MctkP = true;
      //if(fabs(pdgid)==211)      MctkP = true;
      //if(fabs(pdgid)==213)      MctkP = true;
      //if(fabs(pdgid)==30213)    MctkP = true;
      //if(fabs(pdgid)==223)      MctkP = true;
      //if(fabs(pdgid)==321)      MctkP = true;
      //if(fabs(pdgid)==311)      MctkP = true;
      //if(fabs(pdgid)==313)      MctkP = true;
      //if(fabs(pdgid)==315)      MctkP = true;
      //if(fabs(pdgid)==323)      MctkP = true;
      //if(fabs(pdgid)==325)      MctkP = true;
      //if(fabs(pdgid)==333)      MctkP = true;
      //if(pdgid==10111)          MctkP = true;
      //if(fabs(pdgid)==10211)    MctkP = true;
      //if(fabs(pdgid)==10213)    MctkP = true;
      //if(fabs(pdgid)==10311)    MctkP = true;
      //if(fabs(pdgid)==10313)    MctkP = true;
      //if(fabs(pdgid)==10323)    MctkP = true;
      //if(fabs(pdgid)==20323)    MctkP = true;
      //if(pdgid==10221)          MctkP = true;
      //if(pdgid==50221)          MctkP = true;
      //if(pdgid==9010221)       MctkP = true;
      //if(pdgid==20213)          MctkP = true;
      //
      //if(fabs(pdgid)==411)      MctkP = true;
      //if(fabs(pdgid)==413)      MctkP = true;
      //if(fabs(pdgid)==421)      MctkP = true;
      //if(fabs(pdgid)==423)      MctkP = true;
      //cout<<"pre: "<<pre<<endl;
      if(pdgid_mother==vpho) continue;
      if((fabs(pdgid)==431||fabs(pdgid)==433||fabs(pdgid_mother)==433||fabs(pdgid_mother)==431)&&pre*pdgid_mother<0)      { bb++;MctkP = true;}
      if(fabs(pdgid)==431||fabs(pdgid)==433||fabs(pdgid_mother)==433||fabs(pdgid_mother)==431)      { aa++;MctkP = true;pre=pdgid_mother;}

      if(!MctkP) continue;
      //int Idtrk = pdgid;
      
      int Idtrk = pdgid_mother;
      //if(fabs(pdgid_mother)==80022) Idtrk = pdgid;
      if(cc==0) {if(aa==1) {MctkPID.push_back(Idtrk);cc++;}}
      if(dd==0) {if(bb==1) {MctkPID.push_back(Idtrk);dd++;}}
      
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid==-321)      NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]==-321) {ChargK = -1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();
      //cout<<"Nint:  "<<Nint<<" aa:  "<<aa<<"bb:  "<<bb<<endl;
      //cout<<"Nint:  "<<Nint<<" cc:  "<<cc<<"dd:  "<<dd<<endl;
      //cout<<" N1:  "<<MctkPID[0]<<"  N2:  "<<MctkPID[1]<<endl;
// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

//if(Nint==2) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;

/*if(Nint==3) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]== 421&&MctkPID[1]== -421) { SelectionValid = true; Mcmode.push_back(1);} //D0  anti-D0
  if(MctkPID[0]== 423&&MctkPID[1]== -421) { SelectionValid = true; Mcmode.push_back(2);} //D*0 anti-D0
  if(MctkPID[0]== 421&&MctkPID[1]== -423) { SelectionValid = true; Mcmode.push_back(3);} //anti-D*0 D0
  if(MctkPID[0]== 423&&MctkPID[1]== -423) { SelectionValid = true; Mcmode.push_back(4);} //anti-D*0 D*0
  if(MctkPID[0]== 411&&MctkPID[1]== -411) { SelectionValid = true; Mcmode.push_back(5);} //D+   D-
  if(MctkPID[0]== 413&&MctkPID[1]== -411) { SelectionValid = true; Mcmode.push_back(6);} //D*+  D-
  if(MctkPID[0]== 411&&MctkPID[1]== -413) { SelectionValid = true; Mcmode.push_back(7);} //D+   D*-
  if(MctkPID[0]== 413&&MctkPID[1]== -413) { SelectionValid = true; Mcmode.push_back(8);} //D*+  D*-
  if(MctkPID[0]== 431&&MctkPID[1]== -431) { SelectionValid = true; Mcmode.push_back(9);} //Ds+  Ds-
  if(MctkPID[0]== 433&&MctkPID[1]== -431) { SelectionValid = true; Mcmode.push_back(10);} //Ds*+ Ds-
  if(MctkPID[0]== 431&&MctkPID[1]== -433) { SelectionValid = true; Mcmode.push_back(11);} //Ds+  Ds*-
  if(MctkPID[0]== 433&&MctkPID[1]== -433) { SelectionValid = true; Mcmode.push_back(12);} //Ds*+ Ds*-
 }

 if(Nint==3) {
  if(MctkPID[0]== 421&&MctkPID[1]== 111&&MctkPID[2]== -421) { SelectionValid = true; Mcmode.push_back(13);} //D0 anti-D0  pi0
  if(MctkPID[0]== 423&&MctkPID[1]== 111&&MctkPID[2]== -421) { SelectionValid = true; Mcmode.push_back(14);} //D*0 anti-D0 pi0
  if(MctkPID[0]== 421&&MctkPID[1]== 111&&MctkPID[2]== -423) { SelectionValid = true; Mcmode.push_back(15);} //D0 anti-D*0 pi0
  if(MctkPID[0]== 411&&MctkPID[1]== 111&&MctkPID[2]== -411) { SelectionValid = true; Mcmode.push_back(16);} //D+   D-   pi0
  if(MctkPID[0]== 413&&MctkPID[1]== 111&&MctkPID[2]== -411) { SelectionValid = true; Mcmode.push_back(17);} //D*+  D-   pi0
  if(MctkPID[0]== 411&&MctkPID[1]== 111&&MctkPID[2]== -413) { SelectionValid = true; Mcmode.push_back(18);} //D+   D*-  pi0
  if(MctkPID[0]== 421&&MctkPID[1]== 211&&MctkPID[2]== -411) { SelectionValid = true; Mcmode.push_back(19);} //D0   D-   pi+
  if(MctkPID[0]== 411&&MctkPID[1]==-211&&MctkPID[2]== -421) { SelectionValid = true; Mcmode.push_back(20);} //anti-D0   D+   pi+
  if(MctkPID[0]== 421&&MctkPID[1]== 211&&MctkPID[2]== -413) { SelectionValid = true; Mcmode.push_back(21);} //D0   D*-   pi+
  if(MctkPID[0]== 413&&MctkPID[1]==-211&&MctkPID[2]== -421) { SelectionValid = true; Mcmode.push_back(22);} //anti-D0   D*+   pi-
  if(MctkPID[0]== 423&&MctkPID[1]== 211&&MctkPID[2]== -411) { SelectionValid = true; Mcmode.push_back(23);} //D*0   D-   pi+
  if(MctkPID[0]== 411&&MctkPID[1]==-211&&MctkPID[2]== -423) { SelectionValid = true; Mcmode.push_back(24);} //anti-D*0   D+   pi-
  if(MctkPID[0]== 431&&MctkPID[1]== 111&&MctkPID[2]== -431) { SelectionValid = true; Mcmode.push_back(25);} //Ds+  Ds-  pi0
  if(MctkPID[0]== 433&&MctkPID[1]== 111&&MctkPID[2]== -431) { SelectionValid = true; Mcmode.push_back(26);} //Ds*+ Ds-  pi0
  if(MctkPID[0]== 431&&MctkPID[1]== 111&&MctkPID[2]== -433) { SelectionValid = true; Mcmode.push_back(27);} //Ds+  Ds*- pi0
  if(MctkPID[0]== 431&&MctkPID[1]==-311&&MctkPID[2]== -411) { SelectionValid = true; Mcmode.push_back(28);} //Ds+  D-   anti-K0
  if(MctkPID[0]== 411&&MctkPID[1]==-311&&MctkPID[2]== -431) { SelectionValid = true; Mcmode.push_back(29);} //D+   Ds-  anti-K0
  if(MctkPID[0]== 431&&MctkPID[1]==-321&&MctkPID[2]== -421) { SelectionValid = true; Mcmode.push_back(30);} //Ds+  anti-D0   K-
  if(MctkPID[0]== 421&&MctkPID[1]== 321&&MctkPID[2]== -431) { SelectionValid = true; Mcmode.push_back(31);} //D0   Ds-  K+
 }                                                                                                    
                                                                                                      
                                                                                                      
 if(SelectionValid==false&&Nint==2) Mcmode.push_back(1002);                                           
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(1003);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(1004);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(1005);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(1006);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(1007);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(1008);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(1009);
}

}

void DsDsmcmode::Dst1mcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();

   int ID_mother = 0;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid_mother = ((*iter_mc)->mother()).particleProperty();
      if(pdgid_mother!=433&&pdgid_mother!=423&&pdgid_mother!=413)          continue;

      ID_mother = pdgid_mother;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

      if(fabs(pdgid)==411)      MctkP = true;
      if(fabs(pdgid)==421)      MctkP = true;
      if(fabs(pdgid)==431)      MctkP = true;

//      cout<<"TESTaaa:::"<<pdgid<<","<<pdgid_mother<<endl;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid==-321)      NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]==-321) {ChargK = -1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

 if(ID_mother==433){
 if(Nint==2) {
  if(MctkPID[0]== 431&&MctkPID[1]==  22) { SelectionValid = true; Mcmode.push_back(31);} //Ds+ gamma
  if(MctkPID[0]== 431&&MctkPID[1]== 111) { SelectionValid = true; Mcmode.push_back(32);} //Ds+ pi0
 }

 if(Nint==3) {
  if(MctkPID[0]== 431&&MctkPID[1]==  11&&MctkPID[2]== -11) { SelectionValid = true; Mcmode.push_back(33);} //Ds+ e+ e-
 }                                                                                                    
 }
                                                                                                      
 if(ID_mother==423){
 if(Nint==2) {
  if(MctkPID[0]== 421&&MctkPID[1]== 111) { SelectionValid = true; Mcmode.push_back(21);} //D0 pi0
  if(MctkPID[0]== 421&&MctkPID[1]==  22) { SelectionValid = true; Mcmode.push_back(22);} //D0 gamma 
 }

 }
                                                                                                      
 if(ID_mother==413){
 if(Nint==2) {
  if(MctkPID[0]== 421&&MctkPID[1]== 211) { SelectionValid = true; Mcmode.push_back(11);} //D0 pi+
  if(MctkPID[0]== 411&&MctkPID[1]== 111) { SelectionValid = true; Mcmode.push_back(12);} //D+ pi0
  if(MctkPID[0]== 411&&MctkPID[1]==  22) { SelectionValid = true; Mcmode.push_back(13);} //D+ gamma
 }
 }

}

}

void DsDsmcmode::Dst2mcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();

   int ID_mother = 0;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid_mother = ((*iter_mc)->mother()).particleProperty();
      if(pdgid_mother!=-433&&pdgid_mother!=-423&&pdgid_mother!=-413)          continue;

      ID_mother = pdgid_mother;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;

      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)       MctkP = true;
      if(pdgid==20213)          MctkP = true;

      if(fabs(pdgid)==411)      MctkP = true;
      if(fabs(pdgid)==421)      MctkP = true;
      if(fabs(pdgid)==431)      MctkP = true;

//      cout<<"TESTBBB:::"<<pdgid<<","<<pdgid_mother<<endl;

      int Idtrk = pdgid;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());

      if(pdgid==-321)      NumK++;
      }

      if(NumK==1) {
        for(int i=0;i<IDtk.size();i++)
        if(IDtk[i]==-321) {ChargK = -1; P4K.push_back(Ptk[i]);}
      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());

//  cout<<MctkPID.size()<<endl;

 if(ID_mother==-433){
 if(Nint==2) {
  if(MctkPID[0]==  22&&MctkPID[1]==-431) { SelectionValid = true; Mcmode.push_back(-31);} //Ds+ gamma
  if(MctkPID[0]== 111&&MctkPID[1]==-431) { SelectionValid = true; Mcmode.push_back(-32);} //Ds+ pi0
 }

 if(Nint==3) {
  if(MctkPID[0]== 11&&MctkPID[1]==  -11&&MctkPID[2]== -431) { SelectionValid = true; Mcmode.push_back(-33);} //Ds+ e+ e-
 }                                                                                                    
 }
                                                                                                      
 if(ID_mother==-423){
 if(Nint==2) {
  if(MctkPID[0]== 111&&MctkPID[1]==-421) { SelectionValid = true; Mcmode.push_back(-21);} //D0 pi0
  if(MctkPID[0]==  22&&MctkPID[1]==-421) { SelectionValid = true; Mcmode.push_back(-22);} //D0 gamma 
 }

 }
                                                                                                      
 if(ID_mother==-413){
 if(Nint==2) {
  if(MctkPID[0]== -211&&MctkPID[1]==-421) { SelectionValid = true; Mcmode.push_back(-11);} //D0 pi+
  if(MctkPID[0]== 111&&MctkPID[1]==-411) { SelectionValid = true; Mcmode.push_back(-12);} //D+ pi0
  if(MctkPID[0]==  22&&MctkPID[1]==-411) { SelectionValid = true; Mcmode.push_back(-13);} //D+ gamma
 }
 }

}

}

void DsDsmcmode::Dspmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  MctkPID.clear();

    Mcmode.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    bool MotherParticleDecay(false);
    int rootIndex(-1);

    int Ntrk = 0, NumK = 0;
    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      //if ((*iter_mc)->primaryParticle())                                   continue;
      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
      if(pdgid== 431)  {ChargD = 1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22)                                                       continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111))      continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;

      int motherparticlepdg = 431;

      if(pdgid==motherparticlepdg){
        MotherParticleDecay = true;
        rootIndex = (*iter_mc)->trackIndex();
      }
      //if (!MotherParticleDecay)                                            continue;
      bool DDecayValid = false;

      if( 
          (((*iter_mc)->mother()).particleProperty()==motherparticlepdg ) ||
          ((((*iter_mc)->mother()).mother()).particleProperty()==motherparticlepdg) ||
          (((((*iter_mc)->mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          ((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg) || 
          (((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty()==motherparticlepdg)
        ) { DDecayValid = true;  }

      if(!DDecayValid)                                                     continue;

// Save the information of the intemediate particles directly from the parent particle D0
      bool MctkP                      =  false;

      if((((*iter_mc)->mother()).particleProperty())!=431) continue;
      if(pdgid==22)             MctkP = true;
      if(fabs(pdgid)==11)       MctkP = true;
      if(fabs(pdgid)==12)       MctkP = true;
      if(fabs(pdgid)==13)       MctkP = true;
      if(fabs(pdgid)==14)       MctkP = true;
      if(fabs(pdgid)==15)       MctkP = true;
      if(fabs(pdgid)==16)       MctkP = true;
      if(pdgid==111)            MctkP = true;
      if(pdgid==113)            MctkP = true;
      if(pdgid==30113)          MctkP = true;
      if(pdgid==221)            MctkP = true;
      if(pdgid==331)            MctkP = true;
      if(pdgid==310)            MctkP = true;
      if(pdgid==130)            MctkP = true;
      if(fabs(pdgid)==211)      MctkP = true;
      if(fabs(pdgid)==213)      MctkP = true;
      if(fabs(pdgid)==30213)    MctkP = true;
      if(fabs(pdgid)==223)      MctkP = true;
      if(fabs(pdgid)==321)      MctkP = true;
      if(fabs(pdgid)==311)      MctkP = true;
      if(fabs(pdgid)==313)      MctkP = true;
      if(fabs(pdgid)==315)      MctkP = true;
      if(fabs(pdgid)==323)      MctkP = true;
      if(fabs(pdgid)==325)      MctkP = true;
      if(fabs(pdgid)==333)      MctkP = true;
      if(pdgid==10111)          MctkP = true;
      if(fabs(pdgid)==10211)    MctkP = true;
      if(fabs(pdgid)==10213)    MctkP = true;
      if(fabs(pdgid)==10311)    MctkP = true;
      if(fabs(pdgid)==10313)    MctkP = true;
      if(fabs(pdgid)==10323)    MctkP = true;
      if(fabs(pdgid)==20323)    MctkP = true;
      if(pdgid==10221)          MctkP = true;
      if(pdgid==50221)          MctkP = true;
      if(pdgid==9010221)        MctkP = true;

      if(fabs(pdgid)==20213)    MctkP = true;
      if(fabs(pdgid)==10331)    MctkP = true;
      if(fabs(pdgid)==2212)     MctkP = true;
      if(fabs(pdgid)==2112)     MctkP = true;

//      cout<<"TEST DS mode BBB-:::"<<pdgid<<endl;

      int Idtrk = pdgid;
      if(Idtrk==((*iter_mc)->mother()).particleProperty()) continue;
      MctkPID.push_back(Idtrk);
      IDtk.push_back(Idtrk);
       Ptk.push_back((*iter_mc)->initialFourMomentum());
      }

      int Nint = MctkPID.size();

// Judging the D0 modes by the intemediate particles directly from the parent particle D0

    sort(MctkPID.begin(),MctkPID.end(),greater<int>());
 //   cout<<"//==========//  Event  gap //====================//"<<endl;
 //if(Nint==4) for(int kk=0;kk<Nint;kk++) cout<<Nint<<" | "<<kk<<":  "<<MctkPID[kk]<<endl;
/*
if(Nint==2) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<endl;
if(Nint==3) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<endl;
if(Nint==4) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<endl;
if(Nint==5) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<endl;
if(Nint==6) cout<<"aaaa"<<Nint<<","<<MctkPID[0]<<","<<MctkPID[1]<<","<<MctkPID[2]<<","<<MctkPID[3]<<","<<MctkPID[4]<<","<<MctkPID[5]<<endl;
*/

 if(Nint==2) {
  if(MctkPID[0]==     14&&MctkPID[1]==   -13) { SelectionValid = true; Mcmode.push_back(201);} //0.0058           mu+  nu_mu        PHOTOS  SLN;           #[0.0061]gamma20
  if(MctkPID[0]==     16&&MctkPID[1]==   -15) { SelectionValid = true; Mcmode.push_back(202);} //0.0600           tau+ nu_tau       SLN;                   #[0.0599]gamma21
  if(MctkPID[0]==    321&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(203);} //0.0296           anti-K0 K+        PHSP;       #[0.0293]gamma30
  if(MctkPID[0]==    333&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(204);} //0.02405          phi_A   pi+       SVS;        #[0.0206]gamma33*0.509/0.491
  if(MctkPID[0]==    321&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(205);} //0.013            K+ anti-K*0_A     PHSP;       #gamma34*0.333/0.666=0.013
  if(MctkPID[0]==9010221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(206);} //0.0155           f_0_A   pi+       PHSP;       #[0.0103]gamma35
  if(MctkPID[0]==  10221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(207);} //0.0024           f'_0_A  pi+       PHSP;       #[0.0062]gamma36
  if(MctkPID[0]==  10331&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(208);} //0.00187          f_0(1710)_A pi+   PHSP;       #gamma37*0.5/0.5
  if(MctkPID[0]==    321&&MctkPID[1]==-10311) { SelectionValid = true; Mcmode.push_back(209);} //0.00105          K+ anti-K_0*0_A   PHSP;       #gamma38*0.3333/0.6667=0.00105 
  if(MctkPID[0]==    323&&MctkPID[1]==  -311) { SelectionValid = true; Mcmode.push_back(210);} //0.042            K*+    anti-K0    SVS;        #[0.037] gamma 40 5.4-1.2 
  if(MctkPID[0]==    333&&MctkPID[1]==   213) { SelectionValid = true; Mcmode.push_back(211);} //0.061            phi     rho+      SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0 ;      #[(K+ K- pi+ pi0)0.0735]gamma42 8.4-2.3 = 6.1
  if(MctkPID[0]==    323&&MctkPID[1]==  -313) { SelectionValid = true; Mcmode.push_back(212);} //0.072            anti-K*0 K*+      PHSP;       #[0.0048]gamma44 7.2-2.6+2.6
  if(MctkPID[0]==  20213&&MctkPID[1]==   333) { SelectionValid = true; Mcmode.push_back(213);} //0.025            phi a_1+          SVV_HELAMP 1.0 0.0 1.0 0.0 1.0 0.0 ;  # [0.0236]gamma50(7.5-1.3)/0.492/0.492
  if(MctkPID[0]==    211&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(214);} //0.0002           rho0 pi+          SVS;          #gamma55
  if(MctkPID[0]==    225&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(215);} //0.002		 f_2	pi+	   STS;          #gamma60/0.565 = 0.00111/0.565=0.002
  if(MctkPID[0]==  30113&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(216);} //0.00075		 rho(2S)0 pi+      SVS;          #[0.0016]gamma61/0.4 = 0.0003/0.4=0.00075 
  if(MctkPID[0]==    221&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(217);} //0.0183           eta     pi+       PHSP;         #[pi+ pi+ pi- pi0=0.0156]gamma 64 ==> 1.83-0.15 = 1.68==>1.68+0.15
  if(MctkPID[0]==    223&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(218);} //0.0025           omega   pi+       PHSP;         #[pi+ pi+ pi- pi0=0.0156]gamma 65
  if(MctkPID[0]==    221&&MctkPID[1]==   213) { SelectionValid = true; Mcmode.push_back(219);} //0.081            eta     rho+      PHSP;         #[pi+ pi+ pi- pi0 pi0=0.0288]gamma 68 8.9-0.8
  if(MctkPID[0]==    331&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(220);} //0.0394           eta'    pi+       PHSP;         #[0.0367]gamma 73 ==> 3.94-0.33==>3.61+0.33
  if(MctkPID[0]==    331&&MctkPID[1]==   213) { SelectionValid = true; Mcmode.push_back(221);} //0.12315          rho+    eta'      SVS;          #[(3pi+ 2pi- 2pi0)0.0387]gamma 76 ==> 12.5-2.2 = 10.3==>10.3+2.015
  if(MctkPID[0]==    321&&MctkPID[1]==   111) { SelectionValid = true; Mcmode.push_back(222);} //0.00062          K+      pi0       PHSP;         #[0.0007]gamma 78
  if(MctkPID[0]==    311&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(223);} //0.00242          K0      pi+       PHSP;         #[0.0024]gamma 79
  if(MctkPID[0]==    321&&MctkPID[1]==   221) { SelectionValid = true; Mcmode.push_back(224);} //0.00175          eta     K+        PHSP;         #[0.0014]gamma 80
  if(MctkPID[0]==    331&&MctkPID[1]==   321) { SelectionValid = true; Mcmode.push_back(225);} //0.0018           eta'    K+        PHSP;         #[0.0015]gamma 82
  if(MctkPID[0]==    321&&MctkPID[1]==   113) { SelectionValid = true; Mcmode.push_back(226);} //0.0027           rho0    K+        PHSP;         #[0.0026]gamma 84
  if(MctkPID[0]==  30113&&MctkPID[1]==   321) { SelectionValid = true; Mcmode.push_back(227);} //0.0018           rho(2S)0 K+       SVS;          #[0.0018]gamma 85/0.4=0.00073/0.4=0.0018
  if(MctkPID[0]==    313&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(228);} //0.0023           K*0     pi+       SVS;          #[0.0022]gamma 86/0.6657=0.0015/0.6657=0.0023
  if(MctkPID[0]== 100313&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(229);} //0.028            K'*0    pi+       SVS;          #[0.0251]gamma 87/0.0467=0.0013/0.0467=0.028
  if(MctkPID[0]==  10311&&MctkPID[1]==   211) { SelectionValid = true; Mcmode.push_back(230);} //0.00075          K_0*0   pi+       PHSP;         #gamma 88/0.6667=0.0005/0.6667=0.00075
  if(MctkPID[0]==   2212&&MctkPID[1]== -2112) { SelectionValid = true; Mcmode.push_back(231);} //0.0013           p+ anti-n0        PHSP;         #[0.0014]gamma 98
 }

 if(Nint==3) {
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(301);} // anti-K0    e+  nu_e  
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==-10313) { SelectionValid = true; Mcmode.push_back(302);} // anti-K_10  e+  nu_e  
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(303);} // anti-K*0   e+  nu_e  
  if(MctkPID[0]== 12&&MctkPID[1]== -11&&MctkPID[2]==  -315) { SelectionValid = true; Mcmode.push_back(304);} // anti-K_2*0 e+  nu_e  
  if(MctkPID[0]==111&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(305);} // pi0        e+  nu_e  
  if(MctkPID[0]==221&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(306);} // eta        e+  nu_e  
  if(MctkPID[0]==331&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(307);} // eta'       e+  nu_e  
  if(MctkPID[0]==113&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(308);} // rho0       e+  nu_e  
  if(MctkPID[0]==223&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(309);} // omega      e+  nu_e  
  if(MctkPID[0]==311&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(310);} // K0         e+  nu_e  
  if(MctkPID[0]==313&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(311);} // K*0        e+  nu_e  
  if(MctkPID[0]==333&&MctkPID[1]==  12&&MctkPID[2]==   -11) { SelectionValid = true; Mcmode.push_back(312);} // phi        e+  nu_e  
  if(MctkPID[0]==9010221&&MctkPID[1]== 12&&MctkPID[2]==-11) { SelectionValid = true; Mcmode.push_back(313);} // f_0    e+  nu_e  
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(314);} // anti-K0    mu+ nu_mu 
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==-10313) { SelectionValid = true; Mcmode.push_back(315);} // anti-K_10  mu+ nu_mu 
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==  -313) { SelectionValid = true; Mcmode.push_back(316);} // anti-K*0   mu+ nu_mu 
  if(MctkPID[0]== 14&&MctkPID[1]== -13&&MctkPID[2]==  -315) { SelectionValid = true; Mcmode.push_back(317);} // anti-K_2*0 mu+ nu_mu 
  if(MctkPID[0]==111&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(318);} // pi0        mu+ nu_mu 
  if(MctkPID[0]==221&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(319);} // eta        mu+ nu_mu 
  if(MctkPID[0]==331&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(320);} // eta'       mu+ nu_mu 
  if(MctkPID[0]==113&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(321);} // rho0       mu+ nu_mu 
  if(MctkPID[0]==223&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(322);} // omega      mu+ nu_mu 
  if(MctkPID[0]==311&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(323);} // K0         mu+ nu_mu 
  if(MctkPID[0]==313&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(324);} // K*0        mu+ nu_mu 
  if(MctkPID[0]==333&&MctkPID[1]==  14&&MctkPID[2]==   -13) { SelectionValid = true; Mcmode.push_back(325);} // phi        mu+ nu_mu 
  if(MctkPID[0]==9010221&&MctkPID[1]== 14&&MctkPID[2]==-13) { SelectionValid = true; Mcmode.push_back(326);} // f_0    mu+ nu_mu 
  if(MctkPID[0]==321&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(327);} // K+ K- pi+                       PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(328);} // pi+  pi+  pi-                   PHSP;
  if(MctkPID[0]==211&&MctkPID[1]== 111&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(329);} // pi+  pi0  pi0                   PHSP;
  if(MctkPID[0]==311&&MctkPID[1]== 211&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(330);} // K0   pi+  pi0                   D_DALITZ;
  if(MctkPID[0]==211&&MctkPID[1]== 111&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(331);} // anti-K0   pi+  pi0              D_DALITZ;
  if(MctkPID[0]==211&&MctkPID[1]== 211&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(332);} // K-  pi+  pi+                    D_DALITZ;
  if(MctkPID[0]==321&&MctkPID[1]== 211&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(333);} // K+ pi+  pi-                    D_DALITZ;
  if(MctkPID[0]==321&&MctkPID[1]== 321&&MctkPID[2]==  -321) { SelectionValid = true; Mcmode.push_back(334);} // K+ K+ K-                        PHSP;
  if(MctkPID[0]==321&&MctkPID[1]== 321&&MctkPID[2]==  -211) { SelectionValid = true; Mcmode.push_back(335);} // K+ K+ pi-                       PHSP;
  if(MctkPID[0]==311&&MctkPID[1]== 211&&MctkPID[2]==  -311) { SelectionValid = true; Mcmode.push_back(336);} // anti-K0   K0  pi+               PHSP;
  if(MctkPID[0]==223&&MctkPID[1]== 211&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(337);} // omega pi+  pi0               PHSP;
  if(MctkPID[0]==321&&MctkPID[1]== 310&&MctkPID[2]==   111) { SelectionValid = true; Mcmode.push_back(338);} // K+ K_S0 pi0               PHSP;
  if(MctkPID[0]==310&&MctkPID[1]== 310&&MctkPID[2]==   211) { SelectionValid = true; Mcmode.push_back(339);} // K_S0 K_S0  pi+               PHSP;
 }

 if(Nint==4) {
//mahl 2016-9-6
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]== 111&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(401);} // 0.021            K+ K- pi+ pi0     PHSP;       #gamma41-gamma42*0.492 = 5.1-6.1*0.492 = 2.1
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 211&&MctkPID[3]==-321) { SelectionValid = true; Mcmode.push_back(402);} // 0.0008            K0 K- pi+  pi+    PHSP;       # gamma43(1.64)*2-gamma44(7.2)*0.666*0.666=0.0008
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==-211&&MctkPID[3]==-311) { SelectionValid = true; Mcmode.push_back(403);} // 0.0192           anti-K0  K+  pi+  pi-  PHSP;  #[0.0199]gamma45
  if(MctkPID[0]==333&&MctkPID[1]==211&&MctkPID[2]== 211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(404);} // 0.0121           phi  pi+ pi+ pi-  PHSP;       #gamma 47
  if(MctkPID[0]==223&&MctkPID[1]==211&&MctkPID[2]== 211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(405);} // 0.011            omega pi+ pi+ pi- PHSP;         #gamma 72 ==> 1.6-0.5=1.1
  if(MctkPID[0]==311&&MctkPID[1]==211&&MctkPID[2]== 211&&MctkPID[3]==-211) { SelectionValid = true; Mcmode.push_back(406);} // 0.0058           K0  pi+ pi+ pi-   PHSP;         #gamma 91*2
  }

 if(Nint==5) {
  if(MctkPID[0]==321&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-321) { SelectionValid = true; Mcmode.push_back(501);} // 0.0009           K+ K- pi+ pi+ pi- PHSP;       # gamma 51
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==130&&MctkPID[3]== 130&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(502);} // 0.00083          K_L0 K_L0 pi+ pi+ pi-  PHSP;  #[0.0005]gamma 52
  if(MctkPID[0]==310&&MctkPID[1]==310&&MctkPID[2]==211&&MctkPID[3]== 211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(503);} // 0.00083          K_S0 K_S0 pi+ pi+ pi-  PHSP;  #[0.0005]gamma 52
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==-211&&MctkPID[4]==-211) { SelectionValid = true; Mcmode.push_back(504);} // 0.008            pi+ pi+ pi+ pi- pi-  PHSP;      #[0.0067]gamma 66
 }

 if(Nint==6) {
  if(MctkPID[0]==211&&MctkPID[1]==211&&MctkPID[2]==211&&MctkPID[3]==111&&MctkPID[4]==-211&&MctkPID[5]== -211) { SelectionValid = true; Mcmode.push_back(601);} // pi+ pi+ pi+ pi- pi- pi0         PHSP;
 }

 if(SelectionValid==false&&Nint==2) Mcmode.push_back(1102);
 if(SelectionValid==false&&Nint==3) Mcmode.push_back(1103);
 if(SelectionValid==false&&Nint==4) Mcmode.push_back(1104);
 if(SelectionValid==false&&Nint==5) Mcmode.push_back(1105);
 if(SelectionValid==false&&Nint==6) Mcmode.push_back(1106);
 if(SelectionValid==false&&Nint==7) Mcmode.push_back(1107);
 if(SelectionValid==false&&Nint==8) Mcmode.push_back(1108);
 if(SelectionValid==false&&Nint==9) Mcmode.push_back(1109);

}
}

