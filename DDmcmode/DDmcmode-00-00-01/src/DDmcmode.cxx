#include "DDmcmode/DDmcmode.h"

DDmcmode* DDmcmode::m_pointer = 0;

DDmcmode* DDmcmode::instance() {
  if(!m_pointer) m_pointer = new DDmcmode();
  return m_pointer;
}

void DDmcmode::D0mcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

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
      if(pdgid==90100221)       MctkP = true;
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

void DDmcmode::D0bmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

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
      if(pdgid==90100221)       MctkP = true;
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

void DDmcmode::Dpmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

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
      if(pdgid==90100221)       MctkP = true;
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

void DDmcmode::Dnmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol){

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
      if(pdgid==90100221)       MctkP = true;
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












void DDmcmode::D0mcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();
Vint ksID ,etapID,etaID,omegaID;                             ////////////////////////////////////////////
    ksID.clear();
   etapID.clear();
    etaID.clear();
omegaID.clear();
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
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;
//      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221))      continue;
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
    if((((*iter_mc)->mother()).particleProperty())==310) ksID.push_back(pdgid);          /////////////////////////////////////////////////////// 
    if((((*iter_mc)->mother()).particleProperty())==331) etapID.push_back(pdgid);          /////////////////////////////////////////////////////// 
    if((((*iter_mc)->mother()).particleProperty())==221) etaID.push_back(pdgid);
    if((((*iter_mc)->mother()).particleProperty())==223) omegaID.push_back(pdgid);


      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue;
      if((((*iter_mc)->mother()).particleProperty())==-15) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue;
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;

//      if((((*iter_mc)->mother()).particleProperty())==223) continue;
//      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
//      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
//      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;

      if(pdgid==331)                             okay1 = true;
      if(pdgid==111)                             okay1 = true;
      if(pdgid==310)                             okay1 = true;
      if(pdgid==130)                             okay1 = true;
      if(abs(pdgid)==211)                        okay1 = true;
      if(abs(pdgid)==321)                        okay1 = true;
      if(abs(pdgid)==221)                        okay1 = true;
//      if(abs(pdgid)==223)                        okay1 = true;
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

                                          
    if(ksID.size()>0)                                 ////////////////////////////////
    sort(ksID.begin(),ksID.end(),greater<int>());
    if(etapID.size()>0)
    sort(etapID.begin(),etapID.end(),greater<int>());
   if(etaID.size()>0)
    sort(etaID.begin(),etaID.end(),greater<int>());
   if(omegaID.size()>0)
    sort(omegaID.begin(),omegaID.end(),greater<int>());
 int ksmode = 0;
 int ksmode2 =0;
    if(ksID.size()==2&&ksID[0]==211&&ksID[1]==-211) ksmode = 1;
    if(ksID.size()==4&&ksID[0]==211&&ksID[1]==211&&ksID[2]==-211&&ksID[3]==-211) ksmode2 = 1;

 int etapmode =0;
    if(etapID.size()==3&&etapID[0]==221&&etapID[1]==211&&etapID[2]==-211) etapmode = 1;
    if(etapID.size()==2&&etapID[0]==113&&etapID[1]==22) etapmode = 2;

    int etamode =0;
    if(etaID.size()==2&&etaID[0]==22&&etaID[1]==22) etamode = 1;
    if(etaID.size()==3&&etaID[0]==211&&etaID[1]==111&&etaID[2]==-211) etamode = 2;
    if(etaID.size()==4&&etaID[0]==22&&etaID[1]==22&&etaID[2]==22&&etaID[3]==22) etamode = 3;

 int omegamode =0;
    if(omegaID.size()==3&&omegaID[0]==211&&omegaID[1]==111&&omegaID[2]==-211) omegamode = 1;

      int Ntot = finalID.size();

// Judging the D0 modes by the particles in the final states

    sort(finalID.begin(),finalID.end(),greater<int>());

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
      if(finalID[0]==331&&finalID[1]==310&&ksmode==1&&etapmode==1)  { SelectionValid = true; Mcmodef = 271;}   // D0-->Ks etap(pipieta)
    }

    if(Ntot==3) {
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 102;}   // D0-->K-pi+pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = 106;}   // D0-->KSpi+pi-
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 107;}   // D0-->KSK+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-321&&ksmode==1)  { SelectionValid = true; Mcmodef = 108;}   // D0-->KSK-pi+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 109;}   // D0-->KSK+K-
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 110;}   // D0-->K+K-pi0
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 111;}   // D0-->pi+pi-pi0
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==211)  { SelectionValid = true; Mcmodef = 121;}   // D0-->KSKSpi+
 
      if(finalID[0]==331&&finalID[1]==211&&finalID[2]==-321&&etapmode==1)  { SelectionValid = true; Mcmodef = 33101;}   // D0-->k-pi+ etap
      if(finalID[0]==331&&finalID[1]==211&&finalID[2]==-321&&etapmode==2)  { SelectionValid = true; Mcmodef = 33102;}   // D0-->k-pi+ etap
      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==111&&etapmode==1&&ksmode==1)  { SelectionValid = true; Mcmodef = 33103;}   // D0-->ks pi0 etap  pipieta
      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==111&&etapmode==2&&ksmode==1)  { SelectionValid = true; Mcmodef = 33104;}   // D0-->ks pi0 etap   gamma rho0


      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 66101 ;}   // D0   ->K  K  eta 
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==-211&&etamode==1)  { SelectionValid = true; Mcmodef = 66104 ;}   // D0   ->pi  pi  eta 
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==111&&ksmode2==1)  { SelectionValid = true; Mcmodef = 66105 ;}    // D0b   ->Ks  Ks  pi0 
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==221&&ksmode2==1)  { SelectionValid = true; Mcmodef = 66102 ;}    // D0b   ->Ks  Ks  eta 
      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==221&&ksmode==1)  { SelectionValid = true; Mcmodef = 66103 ;}    // D0b   ->Ks  eta  eta 

      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==-321&&etamode==1)  { SelectionValid = true; Mcmodef = 340 ;}   //D0 ->K- pi+ eta


      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==111&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = 341 ;}   //D0 ->Ks pi0 eta

      if(finalID[0]==221&&finalID[1]==130&&finalID[2]==111&&etamode==1)  { SelectionValid = true; Mcmodef = 347 ;}   //D0 ->Kl pi0 eta      
     if(finalID[0]==223&&finalID[1]==211&&finalID[2]==-321&&omegamode==1)  { SelectionValid = true; Mcmodef = 455 ;}   //D0b ->K pi w 


   }
    if(Ntot==4) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 103;}  // D0-->K-pi+pi+pi-
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 111&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 104;}  // D0-->K-pi+pi0pi0

      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = 112;}  // D0-->pi+pi+pi-pi-
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 113;}  // D0-->K-K+pi+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-211) { SelectionValid = true; Mcmodef = 114;}  // D0-->KSpi+pi-pi0 
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 111&&finalID[3]==-211) { SelectionValid = true; Mcmodef = 115;}  // D0-->KSK+pi-pi0 
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-321) { SelectionValid = true; Mcmodef = 116;}  // D0-->KSK-pi+pi0 

      if(finalID[0]==111&&finalID[1]==12&&finalID[2]== -11&&finalID[3] == -321)  { SelectionValid = true; Mcmodef = 201;}   // D0-->K-pi0e+ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 12&&finalID[3] == -11)  { SelectionValid = true; Mcmodef = 202;}   // D0-->pi-pi0e+ne
      if(finalID[0]==310&&finalID[1]==12&&finalID[2]== -11&&finalID[3] == -211&&ksmode==1)  { SelectionValid = true; Mcmodef = 203;}   // D0-->Kspi-e+ne
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 12&&finalID[3] == -11)  { SelectionValid = true; Mcmodef = 204;}   // D0-->KLpi-e+ne 
      if(finalID[0]==111&&finalID[1]==14&&finalID[2]== -13&&finalID[3] == -321)  { SelectionValid = true; Mcmodef = 205;}   // D0-->K-pi0mu+nmu
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 14&&finalID[3] == -13)  { SelectionValid = true; Mcmodef = 206;}   // D0-->pi-pi0mu+nmu
      if(finalID[0]==310&&finalID[1]==14&&finalID[2]==-13&&finalID[3] == -211&&ksmode ==1)  { SelectionValid = true; Mcmodef = 207;}   // D0-->Kspi-mu+nmu
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 14&&finalID[3] == -13)  { SelectionValid = true; Mcmodef = 208;}   // D0-->KLpi-mu+nmu

      if(finalID[0]==221&&finalID[1]==12&&finalID[2]== -11&&finalID[3] == -321&&etamode==1)  { SelectionValid = true; Mcmodef = 209;}   // D0-->K- eta e+ne
      if(finalID[0]==310&&finalID[1]==221&&finalID[2]== 211&&finalID[3]==-211&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = 270;}   // D0-->KSpi+pi-eta 
    }

    if(Ntot==5) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==111&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 105;}  // D0-->K-pi+pi+pi-pi0 

      if(finalID[0]==321&&finalID[1]==12&&finalID[2]==-11&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 300;}  // D0-->K+ K- pi- e+ nue
  
     if(finalID[0]==310&&finalID[1]==310&&finalID[2]==12&&finalID[3]==-11&&finalID[4]==-211&&ksmode2==1)  { SelectionValid = true; Mcmodef = 301;}  // D0-->Ks Ks pi- e+ nue
  
     if(finalID[0]==310&&finalID[1]==111&&finalID[2]==12&&finalID[3]==-11&&finalID[4]==-321&&ksmode==1)  { SelectionValid = true; Mcmodef = 302;}  // D0-->Ks K- pi0 e+ nue

    }
    if(Ntot==6){
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==12&&finalID[3]==-11&&finalID[4]==-211&&finalID[5]==-211){ SelectionValid = true; Mcmodef = 280;} //D0 ->pi+pi-pi0pi-e+nue
}

  }
}

void DDmcmode::D0bmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
      IDtk.clear();

Vint ksID ,etapID,etaID,omegaID;                             ////////////////////////////////////////////
    ksID.clear();
   etapID.clear();
etaID.clear();
omegaID.clear();
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

      if(pdgid==-22) continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
  //    if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221)) continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;

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
      
    if((((*iter_mc)->mother()).particleProperty())==310) ksID.push_back(pdgid);          /////////////////////////////////////////////////////// 
    if((((*iter_mc)->mother()).particleProperty())==331) etapID.push_back(pdgid);          /////////////////////////////////////////////////////// 

    if((((*iter_mc)->mother()).particleProperty())==221) etaID.push_back(pdgid);
    if((((*iter_mc)->mother()).particleProperty())==223) omegaID.push_back(pdgid); 

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue;
      if((((*iter_mc)->mother()).particleProperty())==-15) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue;
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;

//      if((((*iter_mc)->mother()).particleProperty())==223) continue;
//      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
//      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
//      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;

      if(pdgid==331)                             okay1 = true;
      if(pdgid==111)    okay1 = true;
      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
//      if(abs(pdgid)==223)    okay1 = true;
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

                                          
    if(ksID.size()>0)                                 ////////////////////////////////
    sort(ksID.begin(),ksID.end(),greater<int>());
    if(etapID.size()>0)
    sort(etapID.begin(),etapID.end(),greater<int>());
if(etaID.size()>0)
    sort(etaID.begin(),etaID.end(),greater<int>());
if(omegaID.size()>0)
    sort(omegaID.begin(),omegaID.end(),greater<int>());
 int ksmode = 0;
 int ksmode2 =0;
    if(ksID.size()==2&&ksID[0]==211&&ksID[1]==-211) ksmode = 1;
    if(ksID.size()==4&&ksID[0]==211&&ksID[1]==211&&ksID[2]==-211&&ksID[3]==-211) ksmode2 = 1;

 int etapmode =0;
    if(etapID.size()==3&&etapID[0]==221&&etapID[1]==211&&etapID[2]==-211) etapmode = 1;
    if(etapID.size()==2&&etapID[0]==113&&etapID[1]==22) etapmode = 2;

int etamode =0;
    if(etaID.size()==2&&etaID[0]==22&&etaID[1]==22) etamode = 1;
    if(etaID.size()==3&&etaID[0]==211&&etaID[1]==111&&etaID[2]==-211) etamode = 2;
    if(etaID.size()==4&&etaID[0]==22&&etaID[1]==22&&etaID[2]==22&&etaID[3]==22) etamode = 3;
 int omegamode =0;
    if(omegaID.size()==3&&omegaID[0]==211&&omegaID[1]==111&&omegaID[2]==-211) omegamode = 1;
    sort(finalID.begin(),finalID.end(),greater<int>());
    //sort(finalID.begin(),finalID.end(),greater<int>());

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
      if(finalID[0]==331&&finalID[1]==310&&ksmode==1&&etapmode==1)  { SelectionValid = true; Mcmodef = -271;}   // D0b-->Ks etap(pipieta)
    }

    if(Ntot==3) {
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -102;}   // D0b-->K+pi-pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = -106;}   // D0b-->KSpi+pi-
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -107;}   // D0b-->KSK-pi+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = -108;}   // D0b-->KSK+pi-
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -109;}   // D0b-->KSK+K-
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -110;}   // D0b-->K+K-pi0
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -111;}   // D0b-->pi+pi-pi0
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -121;}   // D0b-->KSKSpi-

      if(finalID[0]==331&&finalID[1]==321&&finalID[2]==-211&&etapmode==1)  { SelectionValid = true; Mcmodef =- 33101;}   // D0-->k-pi+ etap
      if(finalID[0]==331&&finalID[1]==321&&finalID[2]==-211&&etapmode==2)  { SelectionValid = true; Mcmodef =- 33102;}   // D0-->k-pi+ etap
      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==111&&etapmode==1)  { SelectionValid = true; Mcmodef = - 33103;}   // D0-->ks pi0 etap  pipieta
      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==111&&etapmode==2)  { SelectionValid = true; Mcmodef = - 33104;}   // D0-->ks pi0 etap   gamma rho0

      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -66101 ;}   // D0b   ->K  K  eta 
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==-211&&etamode==1)  { SelectionValid = true; Mcmodef = -66104 ;}   // D0b   ->pi  pi  eta 
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==111&&ksmode2==1)  { SelectionValid = true; Mcmodef = -66105 ;}    // D0b   ->Ks  Ks  pi0 
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==221&&ksmode2==1)  { SelectionValid = true; Mcmodef = -66102 ;}    // D0b   ->Ks  Ks  eta 
      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==221&&ksmode==1)  { SelectionValid = true; Mcmodef = -66103 ;}    // D0b   ->Ks  eta  eta 

     if(finalID[0]==321&&finalID[1]==221&&finalID[2]==-211&&etamode==1)  { SelectionValid = true; Mcmodef = -340 ;}   //D0b ->K+ pi- eta

     if(finalID[0]==310&&finalID[1]==221&&finalID[2]==111&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = -341 ;}   //D0b ->Ks pi0 eta
  
     if(finalID[0]==221&&finalID[1]==130&&finalID[2]==111&&etamode==1)  { SelectionValid = true; Mcmodef = -347 ;}   //D0b ->Kl pi0 eta 

     if(finalID[0]==321&&finalID[1]==223&&finalID[2]==-211&&omegamode==1)  { SelectionValid = true; Mcmodef = -455 ;}   //D0 ->K pi w 





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
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 11&&finalID[3] == -12&&ksmode==1)  { SelectionValid = true; Mcmodef = -203;}   // D0b-->Kspi+e-ne
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 11&&finalID[3] == -12)  { SelectionValid = true; Mcmodef = -204;}   // D0b-->KLpi+e-ne
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -205;}   // D0b-->K+pi0mu-nmu
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -206;}   // D0b-->pi+pi0mu-nmu
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 13&&finalID[3] == -14&&ksmode==1)  { SelectionValid = true; Mcmodef = -207;}   // D0b-->Kspi+mu-nmu
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 13&&finalID[3] == -14)  { SelectionValid = true; Mcmodef = -208;}   // D0b-->KLpi+mu-nmu
      if(finalID[0]==321&&finalID[1]==221&&finalID[2]== 11&&finalID[3] == -12&&etamode==1)  { SelectionValid = true; Mcmodef = -209;}   // D0b-->K+ eta e-ne

      if(finalID[0]==310&&finalID[1]==221&&finalID[2]== 211&&finalID[3]==-211&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = -270;}   // D0b-->KSpi+pi-eta 
    }

    if(Ntot==5) {
       if(finalID[0]==321&&finalID[1]==211&&finalID[2]==111&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -105;}  // D0b-->K+pi+pi-pi-pi0 
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==11&&finalID[3]==-12&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = -300;}  // D0b-->K+ K- pi+ e- anti-nue
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==211&&finalID[3]==11&&finalID[4]==-12&&ksmode2==1)  { SelectionValid = true; Mcmodef = -301;}  // D0b-->Ks Ks pi+ e- anti-nue

      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==111&&finalID[3]==11&&finalID[4]==-12&&ksmode==1)  { SelectionValid = true; Mcmodef = -302;}  // D0b-->Ks K+ pi0 e- anti-nue
    }
    if(Ntot==6){
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==111&&finalID[3]==11&&finalID[4]==-12&&finalID[5]==-211){ SelectionValid = true; Mcmodef = -280;} //D0b ->pi-pi+pi0pi+e-nue
}

  }

}


void DDmcmode::DpmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
       IDtk.clear();

Vint ksID ,etapID,etaID,omegaID;                             ////////////////////////////////////////////
     ksID.clear();
     etapID.clear();
     etaID.clear();
omegaID.clear();
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
      if(pdgid== 411)  {ChargD =  1; P4D.push_back((*iter_mc)->initialFourMomentum());}

      if(pdgid==-22) continue;
      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
//      if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221)) continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;

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

    if((((*iter_mc)->mother()).particleProperty())==310) ksID.push_back(pdgid);          /////////////////////////////////////////////////////// 
    if((((*iter_mc)->mother()).particleProperty())==331) etapID.push_back(pdgid);          /////////////////////////////////////////////////////// 

     if((((*iter_mc)->mother()).particleProperty())==221) etaID.push_back(pdgid);

     if((((*iter_mc)->mother()).particleProperty())==223) omegaID.push_back(pdgid);

      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue; 
      if((((*iter_mc)->mother()).particleProperty())==-15) continue; 
      if((((*iter_mc)->mother()).mother()).particleProperty()==-15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==-15) continue; 
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==-15) continue; 
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;

//      if((((*iter_mc)->mother()).particleProperty())==223) continue;
//      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
//      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
//      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;
//
      if(pdgid==331)                             okay1 = true;
      if(pdgid==111)    okay1 = true;
      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
//      if(abs(pdgid)==223)    okay1 = true;
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

                                          
    if(ksID.size()>0)                                 ////////////////////////////////
    sort(ksID.begin(),ksID.end(),greater<int>());
    if(etapID.size()>0)
    sort(etapID.begin(),etapID.end(),greater<int>());
   if(etaID.size()>0)
    sort(etaID.begin(),etaID.end(),greater<int>());
   if(omegaID.size()>0)
    sort(omegaID.begin(),omegaID.end(),greater<int>());

 int ksmode = 0;
 int ksmode2 =0;
    if(ksID.size()==2&&ksID[0]==211&&ksID[1]==-211) ksmode = 1;
    if(ksID.size()==4&&ksID[0]==211&&ksID[1]==211&&ksID[2]==-211&&ksID[3]==-211) ksmode2 = 1;
 int etapmode =0;
    if(etapID.size()==3&&etapID[0]==221&&etapID[1]==211&&etapID[2]==-211) etapmode = 1;
    if(etapID.size()==2&&etapID[0]==113&&etapID[1]==22) etapmode = 2;

 int etamode =0;
    if(etaID.size()==2&&etaID[0]==22&&etaID[1]==22) etamode = 1;
    if(etaID.size()==4&&etaID[0]==22&&etaID[1]==22&&etaID[2]==22&&etaID[3]==22) etamode = 3;
    if(etaID.size()==3&&etaID[0]==211&&etaID[1]==111&&etaID[2]==-211) etamode = 2;

 int omegamode =0;
    if(omegaID.size()==3&&omegaID[0]==211&&omegaID[1]==111&&omegaID[2]==-211) omegamode = 1;

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
      if(finalID[0]==310&&finalID[1]==211&&ksmode==1)  { SelectionValid = true; Mcmodef = 602;} // D+-->KSpi+
      if(finalID[0]==321&&finalID[1]==310)  { SelectionValid = true; Mcmodef = 607;} // D+-->KSK+
      if(finalID[0]==211&&finalID[1]==130)  { SelectionValid = true; Mcmodef = 610;} // D+-->K_L0 pi+
      if(finalID[0]==321&&finalID[1]==130)  { SelectionValid = true; Mcmodef = 611;} // D+-->K_L0 K+
      if(finalID[0]==321&&finalID[1]==223&&omegamode==1)  { SelectionValid = true; Mcmodef = 777;} // D+-->w K+
    }

    if(Ntot==3) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 601;} // D+-->K-pi+pi+
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&ksmode==1)  { SelectionValid = true; Mcmodef = 604;} // D+-->KSpi+pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 111&&ksmode!=1)  { SelectionValid = true; Mcmodef = 345;} // D+-->KSpi+pi0
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = 606;} // D+-->K+K-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = 608;} // D+-->pi+pi+pi-
      if(finalID[0]==310&&finalID[1]==310&&finalID[2]== 211&&ksmode2==1)  { SelectionValid = true; Mcmodef = 612;} // D+-->KSKSpi+
      if(finalID[0]==211&&finalID[1]==130&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 613;} // D+-->K_L0 pi+ pi0
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 310)  { SelectionValid = true; Mcmodef = 620;} // D+-->KSKSK+
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 111)  { SelectionValid = true; Mcmodef = 366;} // D+--> pi+ pi0 pi0

      if(finalID[0]==310&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 701;} // D+-->K_s0e +ne
      if(finalID[0]==130&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 702;} // D+-->K_L0e +ne
      if(finalID[0]==310&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 703;} // D+-->K_S0 mu+nu
      if(finalID[0]==130&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 704;} // D+-->K_L0 mu+nu
      if(finalID[0]==111&&finalID[1]== 12&&finalID[2]== -11)  { SelectionValid = true; Mcmodef = 705;} // D+-->pi0e+ne
      if(finalID[0]==111&&finalID[1]== 14&&finalID[2]== -13)  { SelectionValid = true; Mcmodef = 706;} // D+-->pi0mu+ne

      if(finalID[0]==221&&finalID[1]==  14&&finalID[2]== -13 &&etamode==1)  { SelectionValid = true; Mcmodef = 900;} // D+--> eta(2gam) mu+ nmu
      if(finalID[0]==221&&finalID[1]==  14&&finalID[2]== -13 &&etamode==2)  { SelectionValid = true; Mcmodef = 904;} // D+--> eta(3pi) mu+ nmu
      if(finalID[0]==331&&finalID[1]==  14&&finalID[2]== -13 &&etapmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = 901;} // D+--> etap(pipieta) mu+ nmu
      if(finalID[0]==331&&finalID[1]==  14&&finalID[2]== -13 &&etapmode==2)  { SelectionValid = true; Mcmodef = 902;} // D+--> etap(gamrho) mu+ nmu
      if(finalID[0]==223&&finalID[1]==  14&&finalID[2]== -13 &&omegamode==1)  { SelectionValid = true; Mcmodef = 903;} // D+--> omega(pipipi0) mu+ nmu

      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==211&&etapmode==1&&ksmode==1)  { SelectionValid = true; Mcmodef =  33105;}   // D+-->ks pi+ etap
      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==211&&etapmode==2&&ksmode==1)  { SelectionValid = true; Mcmodef =  33106;}   // D+-->ks pi+ etap
      if(finalID[0]==331&&finalID[1]==321&&finalID[2]==111&&etapmode==1)  { SelectionValid = true; Mcmodef =  33107;}    // D+-->k pi0 etap  pipieta
      if(finalID[0]==331&&finalID[1]==321&&finalID[2]==111&&etapmode==2)  { SelectionValid = true; Mcmodef =  33108;}    // D+-->k pi0 etap   gamma rho0

      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==221)  { SelectionValid = true; Mcmodef =  66107;}    // D+-->k eta eta
      if(finalID[0]==221&&finalID[1]==221&&finalID[2]==211&&etamode==3)  { SelectionValid = true; Mcmodef =  66108;}    // D+-->pi+ eta eta
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]==111&&etamode==1)  { SelectionValid = true; Mcmodef =  66109;}    // D+-->eta pi+ pi0

//      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==211&&ksmode==1)  { SelectionValid = true; Mcmodef =  342;}    //D+ ->Ks pi+ eta

      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==211&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef =  342;}    //D+ ->Ks pi+ eta
      
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==221&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef =  343;}    //D+ ->Ks k+ eta

      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==111&&etamode==1)  { SelectionValid = true; Mcmodef =  344;}    //D+ ->K+ pi0 eta
           

      if(finalID[0]==321&&finalID[1]==221&&finalID[2]==130&&etamode==1)  { SelectionValid = true; Mcmodef =  346;}    //D+ ->Kl k+ eta

    }

    if(Ntot==4) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 603;} // D+-->K-pi+pi+pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = 605;} // D+-->KSpi+pi+pi-
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 111&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 614;} // D+-->pi+pi+pi-pi0 
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]== 211&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 615;} // D+-->KSK-pi+pi+
      if(finalID[0]==321&&finalID[1]==310&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 617;} // D+-->KSK+pi-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]== 130&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 618;} // D+-->KLK-pi+pi+
      if(finalID[0]==321&&finalID[1]==130&&finalID[2]== 211&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 619;} // D+-->KLK+pi-pi+

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 711;} // D+-->gamma gamma e+ne
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 712;} // D+-->pi0 pi0 e+ne
      if(finalID[0]==211&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = 713;} // D+-->pi+ pi- e+ne
      if(finalID[0]==321&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 714;} // D+-->K+ K- e+ne
      if(finalID[0]==211&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 715;} // D+-->K- pi+ e+ne
      if(finalID[0]==321&&finalID[1]== 12&&finalID[2]== -11&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 716;} // D+-->K+ pi- e+ne
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11&&ksmode==1)  { SelectionValid = true; Mcmodef = 717;} // D+-->Ks pi0 e+ne
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  12&&finalID[3]== -11)  { SelectionValid = true; Mcmodef = 718;} // D+-->KL pi0 e+ne

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 721;} // D+-->gamma gamma mu+nmu
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 722;} // D+-->pi0 pi0 mu+nmu
      if(finalID[0]==211&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = 723;} // D+-->pi+ pi- mu+nmu
      if(finalID[0]==321&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 724;} // D+-->K+ K- mu+nmu
      if(finalID[0]==211&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = 725;} // D+-->K- pi+ mu+nmu
      if(finalID[0]==321&&finalID[1]== 14&&finalID[2]== -13&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = 726;} // D+-->K+ pi- mu+nmu
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13&&ksmode==1)  { SelectionValid = true; Mcmodef = 727;} // D+-->Ks pi0 mu+nmu
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  14&&finalID[3]== -13)  { SelectionValid = true; Mcmodef = 728;} // D+-->KL pi0 mu+nmu

      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==  111&&finalID[3]== 111)  { SelectionValid = true; Mcmodef = 630;} // D+-->Ks pi+ pi0 pi0
      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==  12&&finalID[3]== -11&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = 631;} // D+-->Ks eta e+ ne


    }

    if(Ntot==5) {
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==211&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 609;} // D+-->K-pi+pi+pi+pi-
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==211&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 616;} // D+-->pi+pi+pi+pi-pi-
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 731;} // D+-->pi+pi-pi0 e+ne
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 732;} // D+-->pi+pi-eta e+ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]== 14&&finalID[3]== -13&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 741;} // D+->pi+pi-pi0 mu+nmu
      if(finalID[0]==221&&finalID[1]==211&&finalID[2]== 14&&finalID[3]== -13&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = 742;} // D+-->pi+pi-eta mu+nmu


      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 12&&finalID[3]== -11&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 800;} // D+-->K+K-pi0 e+ne

     if(finalID[0]==310&&finalID[1]==310&&finalID[2]==111&&finalID[3]==12&&finalID[4]==-11&&ksmode2==1)  { SelectionValid = true; Mcmodef = 801;}  // D+-->Ks Ks pi0 e+ nue
  
     if(finalID[0]==310&&finalID[1]==211&&finalID[2]==12&&finalID[3]==-11&&finalID[4]==-321&&ksmode==1)  { SelectionValid = true; Mcmodef = 802;}  // D+-->Ks K- pi+ e+ nue

      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==211&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = 432;} // D+-->K-K+pi+pi+pi-
    }

    if(Ntot==6){
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==111&&finalID[3]==12&&finalID[4]==-11&&finalID[5]==-211){ SelectionValid = true; Mcmodef = 281;} //D+ ->pi+pi-pi0pi0e+nue
}



  }


}


void DDmcmode::DnmcmodeF(SmartDataPtr<Event::McParticleCol> mcParticleCol){

  bool SelectionValid = false;
  finalID.clear();
       P4D.clear();
       P4K.clear();
       Ptk.clear();
       IDtk.clear();

Vint ksID ,etapID,etaID,omegaID;                             ////////////////////////////////////////////
     ksID.clear();
     etapID.clear();
    etaID.clear();
    omegaID.clear();
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
  //    if(pdgid==22&&(((*iter_mc)->mother()).particleProperty()==221)) continue;
      if(abs(pdgid)==11&&(((*iter_mc)->mother()).particleProperty()==111)) continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==310))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==311))     continue;
      if(pdgid==111&&(((*iter_mc)->mother()).particleProperty()==-311))     continue;

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

    if((((*iter_mc)->mother()).particleProperty())==310) ksID.push_back(pdgid);          /////////////////////////////////////////////////////// 
    if((((*iter_mc)->mother()).particleProperty())==331) etapID.push_back(pdgid);          /////////////////////////////////////////////////////// 

    if((((*iter_mc)->mother()).particleProperty())==221) etaID.push_back(pdgid);

    if((((*iter_mc)->mother()).particleProperty())==223) omegaID.push_back(pdgid);
      bool okay1=false;
      if(abs(((*iter_mc)->mother()).particleProperty())==211||abs(((*iter_mc)->mother()).particleProperty())==321) continue; 
      if(abs(((*iter_mc)->mother()).particleProperty())==15) continue; 
      if((((*iter_mc)->mother()).mother()).particleProperty()==15) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==15) continue; 
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==15) continue; 
      if(abs(pdgid)==211&&((*iter_mc)->mother()).particleProperty()==310) continue;
      if((((*iter_mc)->mother()).particleProperty())==331) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==331) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==331) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==331) continue;
      if((((*iter_mc)->mother()).particleProperty())==221) continue;
      if((((*iter_mc)->mother()).mother()).particleProperty()==221) continue;
      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==221) continue;
      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==221) continue;

//      if((((*iter_mc)->mother()).particleProperty())==223) continue;
//      if((((*iter_mc)->mother()).mother()).particleProperty()==223) continue;
//      if(((((*iter_mc)->mother()).mother()).mother()).particleProperty()==223) continue;
//      if((((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty()==223) continue;

      if(pdgid==331)     okay1 = true;
      if(pdgid==111)    okay1 = true;
      if(pdgid==310)    okay1 = true;
      if(pdgid==130)    okay1 = true;
      if(abs(pdgid)==211)    okay1 = true;
      if(abs(pdgid)==321)    okay1 = true;
      if(abs(pdgid)==221)    okay1 = true;
//      if(abs(pdgid)==223)    okay1 = true;
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

                                          
    if(ksID.size()>0)                                 ////////////////////////////////
    sort(ksID.begin(),ksID.end(),greater<int>());
    if(etapID.size()>0)
    sort(etapID.begin(),etapID.end(),greater<int>());
    if(etaID.size()>0)
    sort(etaID.begin(),etaID.end(),greater<int>());
    if(omegaID.size()>0)
    sort(omegaID.begin(),omegaID.end(),greater<int>());

    int ksmode = 0;
    int ksmode2 =0;
    if(ksID.size()==2&&ksID[0]==211&&ksID[1]==-211) ksmode = 1;
    if(ksID.size()==4&&ksID[0]==211&&ksID[1]==211&&ksID[2]==-211&&ksID[3]==-211) ksmode2 = 1;
    int etapmode =0;
    if(etapID.size()==3&&etapID[0]==221&&etapID[1]==211&&etapID[2]==-211) etapmode = 1;
    if(etapID.size()==2&&etapID[0]==113&&etapID[1]==22) etapmode = 2;

    int etamode =0;
    if(etaID.size()==2&&etaID[0]==22&&etaID[1]==22) etamode = 1;
    if(etaID.size()==3&&etaID[0]==211&&etaID[1]==111&&etaID[2]==-211) etamode = 2;
    if(etaID.size()==4&&etaID[0]==22&&etaID[1]==22&&etaID[2]==22&&etaID[3]==22) etamode = 3;

 int omegamode =0;
    if(omegaID.size()==3&&omegaID[0]==211&&omegaID[1]==111&&omegaID[2]==-211) omegamode = 1;

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
      if(finalID[0]==310&&finalID[1]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = -602;}  // D--->KSpi-
      if(finalID[0]==310&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -607;}  // D--->KSK-
      if(finalID[0]==130&&finalID[1]==-211)  { SelectionValid = true; Mcmodef = -610;}  // D--->K_L0 pi-
      if(finalID[0]==130&&finalID[1]==-321)  { SelectionValid = true; Mcmodef = -611;}  // D--->K_L0 K-
      if(finalID[0]==223&&finalID[1]==-321&&omegamode==1)  { SelectionValid = true; Mcmodef = -777;} // D--->w K-
    }

    if(Ntot==3) {
      if(finalID[0]==321&&finalID[1]==-211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -601;} // D--->K+pi-pi-
      if(finalID[0]==310&&finalID[1]== 111&&finalID[2]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = -604;} // D--->KSpi-pi0      
      if(finalID[0]==310&&finalID[1]== 111&&finalID[2]==-211&&ksmode!=1)  { SelectionValid = true; Mcmodef = -345;} // D--->KSpi-pi0      
      if(finalID[0]==321&&finalID[1]==-211&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -606;} // D--->K+K-pi-
      if(finalID[0]==211&&finalID[1]==-211&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -608;} // D--->pi+pi-pi-
      if(finalID[0]==310&&finalID[1]== 310&&finalID[2]==-211&&ksmode2==1)  { SelectionValid = true; Mcmodef = -612;} // D--->KSKSpi-
      if(finalID[0]==310&&finalID[1]== 310&&finalID[2]==-211&&ksmode==2)  { SelectionValid = true; Mcmodef = -671;} // D--->KSKSpi-
      if(finalID[0]==130&&finalID[1]== 111&&finalID[2]==-211)  { SelectionValid = true; Mcmodef = -613;} // D--->K_L0 pi- pi0
      if(finalID[0]==310&&finalID[1]== 310&&finalID[2]==-321)  { SelectionValid = true; Mcmodef = -620;} // D--->KSKSK-
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]== -211)  { SelectionValid = true; Mcmodef = -366;} // D---> pi- pi0 pi0

      if(finalID[0]==310&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -701;} // D--->K_s0e-ne
      if(finalID[0]==130&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -702;} // D--->K_L0e-ne
      if(finalID[0]==310&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -703;} // D--->K_S0 mu-nu
      if(finalID[0]==130&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -704;} // D--->K_L0 mu-nu
      if(finalID[0]==111&&finalID[1]==  11&&finalID[2]== -12)  { SelectionValid = true; Mcmodef = -705;} // D--->pi0e-ne
      if(finalID[0]==111&&finalID[1]==  13&&finalID[2]== -14)  { SelectionValid = true; Mcmodef = -706;} // D--->pi0mu-nmu

      if(finalID[0]==221&&finalID[1]==  13&&finalID[2]== -14 &&etamode==1)  { SelectionValid = true; Mcmodef = -900;} // D---> eta(2gam) mu- nmu
      if(finalID[0]==221&&finalID[1]==  13&&finalID[2]== -14 &&etamode==2)  { SelectionValid = true; Mcmodef = -904;} // D---> eta(3pi) mu- nmu
      if(finalID[0]==331&&finalID[1]==  13&&finalID[2]== -14 &&etapmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = -901;} // D---> etap(pipieta) mu- nmu
      if(finalID[0]==331&&finalID[1]==  13&&finalID[2]== -14 &&etapmode==2)  { SelectionValid = true; Mcmodef = -902;} // D---> etap(gamrho) mu- nmu
      if(finalID[0]==223&&finalID[1]==  13&&finalID[2]== -14 &&omegamode==1)  { SelectionValid = true; Mcmodef = -903;} // D---> omega(pipipi0) mu- nmu

      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==-211&&etapmode==1&&ksmode==1)  { SelectionValid = true; Mcmodef = -33105;}   //  D- -->ks pi etap
      if(finalID[0]==331&&finalID[1]==310&&finalID[2]==-211&&etapmode==2&&ksmode==1)  { SelectionValid = true; Mcmodef = -33106;}   //  D- -->ks pi etap
      if(finalID[0]==331&&finalID[1]==111&&finalID[2]==-321&&etapmode==1)  { SelectionValid = true; Mcmodef = -33107;}    // D- -->k pi0 etap  pipieta
      if(finalID[0]==331&&finalID[1]==111&&finalID[2]==-321&&etapmode==2)  { SelectionValid = true; Mcmodef = -33108;}    // D- -->k pi0 etap   gamma rho0

      if(finalID[0]==221&&finalID[1]==221&&finalID[2]==-321)  { SelectionValid = true; Mcmodef =  -66107;}    // D--->k eta eta
      if(finalID[0]==221&&finalID[1]==221&&finalID[2]==-211&&etamode==3)  { SelectionValid = true; Mcmodef =  -66108;}    // D--->pi eta eta
      if(finalID[0]==221&&finalID[1]==111&&finalID[2]==-211&&etamode==1)  { SelectionValid = true; Mcmodef =  -66109;}    // D--->pi pi0 eta

      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==-211&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef =  -342;}    //D- ->Ks pi- eta

//      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef =  -342;}    //D- ->Ks pi- eta

      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==-321&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef =  -343;}    //D- ->Ks k- eta

      if(finalID[0]==221&&finalID[1]==111&&finalID[2]==-321&&etamode==1)  { SelectionValid = true; Mcmodef =  -344;}    //D- ->K- pi0 eta


      if(finalID[0]==221&&finalID[1]==130&&finalID[2]==-321&&etamode==1)  { SelectionValid = true; Mcmodef =  -346;}    //D+ ->Kl k- eta

    }

    if(Ntot==4) {
      if(finalID[0]==321&&finalID[1]==111&&finalID[2]==-211&&finalID[3]==-211) { SelectionValid = true; Mcmodef = -603;} // D--->K+pi-pi-pi0
      if(finalID[0]==310&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&ksmode==1) { SelectionValid = true; Mcmodef = -605;} // D--->KSpi+pi-pi-
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
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12&&ksmode==1)  { SelectionValid = true; Mcmodef = -717;} // D--->Ks pi0 e-ne
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  11&&finalID[3]== -12)  { SelectionValid = true; Mcmodef = -718;} // D--->KL pi0 e-ne

      if(finalID[0]== 22&&finalID[1]== 22&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -721;} // D--->gamma gamma mu-nmu
      if(finalID[0]==111&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -722;} // D--->pi0 pi0 mu-nmu
      if(finalID[0]==211&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-111)  { SelectionValid = true; Mcmodef = -723;} // D--->pi+ pi- mu-nmu
      if(finalID[0]==321&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -724;} // D--->K+ K- mu-nmu
      if(finalID[0]==321&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-211)  { SelectionValid = true; Mcmodef = -725;} // D--->K+ pi- mu-nmu
      if(finalID[0]==211&&finalID[1]== 13&&finalID[2]== -14&&finalID[3]==-321)  { SelectionValid = true; Mcmodef = -726;} // D--->K- pi+ mu-nmu
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14&&ksmode==1)  { SelectionValid = true; Mcmodef = -727;} // D--->Ks pi0 mu-nmu
      if(finalID[0]==130&&finalID[1]==111&&finalID[2]==  13&&finalID[3]== -14)  { SelectionValid = true; Mcmodef = -728;} // D--->KL pi0 mu-nmu
      if(finalID[0]==310&&finalID[1]==111&&finalID[2]==  111&&finalID[3]== -211)  { SelectionValid = true; Mcmodef = -630;} // D--->Ks pi- pi0 pi0
      if(finalID[0]==310&&finalID[1]==221&&finalID[2]==  11&&finalID[3]== -12&&ksmode==1&&etamode==1)  { SelectionValid = true; Mcmodef = -631;} // D--->Ks eta e- ne
    }

    if(Ntot==5) {
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -609;} // D--->K+pi-pi-pi-pi+
      if(finalID[0]==211&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -616;} // D--->pi+pi+pi-pi-pi-

      if(finalID[0]==211&&finalID[1]==111&&finalID[1]==  11&&finalID[3]== -12&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -731;} // D--->pi+pi-pi0 e-ne
      if(finalID[0]==221&&finalID[1]==211&&finalID[1]==  11&&finalID[3]== -12&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -732;} // D--->pi+pi-eta e-ne
      if(finalID[0]==211&&finalID[1]==111&&finalID[1]==  13&&finalID[3]== -14&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -741;} // D--->pi+pi-pi0 mu-nmu
      if(finalID[0]==221&&finalID[1]==211&&finalID[1]==  13&&finalID[3]== -14&&finalID[4]==-211)  { SelectionValid = true; Mcmodef = -742;} // D--->pi+pi-eta mu-nmu

      if(finalID[0]==321&&finalID[1]==111&&finalID[2]== 11&&finalID[3]== -12&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = -800;} // D--->K+K-pi0 e- anti-ne

      if(finalID[0]==310&&finalID[1]==310&&finalID[2]==111&&finalID[3]==11&&finalID[4]==-12&&ksmode2==1)  { SelectionValid = true; Mcmodef = -801;}  // D--->Ks Ks pi0 e- anti-nue

      if(finalID[0]==321&&finalID[1]==310&&finalID[2]==11&&finalID[3]==-12&&finalID[4]==-211&&ksmode==1)  { SelectionValid = true; Mcmodef = -802;}  // D--->Ks K+ pi- e- anti-nue
  
      if(finalID[0]==321&&finalID[1]==211&&finalID[2]==-211&&finalID[3]==-211&&finalID[4]==-321)  { SelectionValid = true; Mcmodef = -432;} // D--->K-K+pi+pi-pi-

    }
    if(Ntot==6){
      if(finalID[0]==211&&finalID[1]==111&&finalID[2]==111&&finalID[3]==11&&finalID[4]==-12&&finalID[5]==-211){ SelectionValid = true; Mcmodef = -281;} //D- ->pi-pi+pi0pi0e-nue
}

  }

}





 

