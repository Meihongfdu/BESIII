#ifndef Physics_Analysis_Jpsdecthreepi_H
#define Physics_Analysis_Jpsdecthreepi_H 

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"

#include "CLHEP/Matrix/Vector.h"
using CLHEP::HepVector;
#ifndef CLHEP_POINT3D_H
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#endif

class Jpsdecthreepi : public Algorithm {

public:
  Jpsdecthreepi(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();  

private:

  HepPoint3D Get_HelixCenter(HepVector helix);
  double     Get_HelixRadius(HepVector helix);
  HepPoint3D intersections(HepVector helix,double r);
  double     Get_Dee(HepVector helixe,HepVector helixp,double r);

  bool m_testMC;
  bool m_testJpsMC;

  double m_energyThreshold1;
  double m_energyThreshold2;
  double m_nGam_cut;
  double m_timedown;
  double m_timeup;
  double m_gammaAngleCut;

  NTuple::Tuple*  m_tuple1;  

  NTuple::Item<double>    m_vx0;
  NTuple::Item<double>    m_vy0;
  NTuple::Item<double>    m_vz0;
  NTuple::Item<double>    m_vr0;
  NTuple::Item<double>    m_rvxy0;
  NTuple::Item<double>    m_rvz0;
  NTuple::Item<double>    m_rvphi0;

  NTuple::Item<int>       m_run;
  NTuple::Item<int>       m_rec;


  NTuple::Item<int>  m_idxmc;
  NTuple::Array<int>  m_trkidx; 
  NTuple::Array<int> m_pdgid;
  NTuple::Array<int> m_motheridx;


 
 // Photons

  NTuple::Item<int>     m_mcnPhoton;

  NTuple::Item<double>  m_mcPhotonInvMass;
  NTuple::Item<double>  m_mcPhotonTheta;
  NTuple::Item<double>  m_mcPhotonPhi;
  NTuple::Item<double>  m_mcPhotonEnergy;



  // Electrons

  NTuple::Item<int>     m_mcnElectron;

  NTuple::Item<double>  m_mcElectronInvMass;
  NTuple::Item<double>  m_mcElectronTheta;
  NTuple::Item<double>  m_mcElectronPhi;
  NTuple::Item<double>  m_mcElectronEnergy;

  NTuple::Item<double>  m_mcElectronX;
  NTuple::Item<double>  m_mcElectronY;
  NTuple::Item<double>  m_mcElectronZ;



  NTuple::Item<int>     m_mcnPositron;

  NTuple::Item<double>  m_mcPositronInvMass;
  NTuple::Item<double>  m_mcPositronTheta;
  NTuple::Item<double>  m_mcPositronPhi;
  NTuple::Item<double>  m_mcPositronEnergy;

  NTuple::Item<double>  m_mcPositronX;
  NTuple::Item<double>  m_mcPositronY;
  NTuple::Item<double>  m_mcPositronZ;


 //pi0
  NTuple::Item<int>     m_mcnPi0;
  NTuple::Item<double>  m_mcPi0InvMass;
  NTuple::Item<double>  m_mcPi0Theta;
  NTuple::Item<double>  m_mcPi0Phi;
  NTuple::Item<double>  m_mcPi0Energy;


 //pi0
  NTuple::Item<int>     m_mcnEta0;
  NTuple::Item<double>  m_mcEta0InvMass;
  NTuple::Item<double>  m_mcEta0Theta;
  NTuple::Item<double>  m_mcEta0Phi;
  NTuple::Item<double>  m_mcEta0Energy;



  // single photons

  NTuple::Item<double>  m_mcPhoton1Energy;
  NTuple::Item<double>  m_mcPhoton1Theta;
  NTuple::Item<double>  m_mcPhoton1Phi;

  NTuple::Item<double>  m_mcPhoton2Energy;
  NTuple::Item<double>  m_mcPhoton2Theta;
  NTuple::Item<double>  m_mcPhoton2Phi;

  NTuple::Item<double>  m_mcPhoton3Energy;
  NTuple::Item<double>  m_mcPhoton3Theta;
  NTuple::Item<double>  m_mcPhoton3Phi;

  NTuple::Item<double>  m_mcPhoton4Energy;
  NTuple::Item<double>  m_mcPhoton4Theta;
  NTuple::Item<double>  m_mcPhoton4Phi;

 
  NTuple::Item<double>  m_mcHighestenergeticPhotonEnergy;
  NTuple::Item<double>  m_mcHighestenergeticPhotonTheta;
  NTuple::Item<double>  m_mcHighestenergeticPhotonPhi;
  NTuple::Item<double>  m_mcHighestenergeticPhotonX;
  NTuple::Item<double>  m_mcHighestenergeticPhotonY;
  NTuple::Item<double>  m_mcHighestenergeticPhotonZ;
 


  /////////////////////////////////////////////////////////////

  NTuple::Item<long>    m_digi_npart;
  NTuple::Item<long>    m_digi_ntheta;
  NTuple::Item<long>    m_digi_nphi;

  NTuple::Item<long>      m_nCharge;
  NTuple::Item<long>      m_nTracks;
  NTuple::Item<long>      m_nNeutral;
  NTuple::Item<int>       m_nGood;
  NTuple::Item<int>       m_nGam;

 // Store the photon related variables in the ntuple

  NTuple::Array<long>     m_numHits; 
  NTuple::Array<long>     m_status;
  NTuple::Array<long>     m_cellId;
  NTuple::Array<long>     m_module;
  NTuple::Array<double>  m_x; 
  NTuple::Array<double>  m_y; 
  NTuple::Array<double>  m_z;
  NTuple::Array<double>  m_theta;
  NTuple::Array<double>  m_phi;
  NTuple::Array<double>  m_dx;
  NTuple::Array<double>  m_dy;
  NTuple::Array<double>  m_dz;
  NTuple::Array<double>  m_dtheta;
  NTuple::Array<double>  m_dphi;
  NTuple::Array<double>  m_energy;
  NTuple::Array<double>  m_dE;
  NTuple::Array<double>  m_eSeed;
  NTuple::Array<double>  m_e3x3;
  NTuple::Array<double>  m_e5x5;
  NTuple::Array<double>  m_secondMoment;
  NTuple::Array<double>  m_latMoment;
  NTuple::Array<double>  m_a20Moment;
  NTuple::Array<double>  m_a42Moment;
  NTuple::Array<double>  m_time;
  NTuple::Array<double>  m_game_barrel;
  NTuple::Array<double>  m_game_endcp;
   
  NTuple::Array<double>  m_emcpos_theta; 
  NTuple::Array<double>  m_emcpos_phi;

  NTuple::Array<double>  m_dthe_ch;
  NTuple::Array<double>  m_dphi_ch;
  NTuple::Array<double>  m_dang_ch;

  NTuple::Array<double>  m_extpos_x; 
  NTuple::Array<double>  m_extpos_y;
  NTuple::Array<double>  m_extpos_z;



  NTuple::Array<double> m_ptrk_pid;
  NTuple::Array<double> m_cost_pid;
  NTuple::Array<double> m_dedx_pid;
  NTuple::Array<double> m_tof1_pid;
  NTuple::Array<double> m_tof2_pid;
  NTuple::Array<double> m_electron_pid;
  NTuple::Array<double> m_pion_pid;
  NTuple::Array<double> m_kaon_pid;


  NTuple::Item<int>  m_nep;
  NTuple::Item<int>  m_nem;

  NTuple::Item<double>    ep_electronPID;
  NTuple::Item<double>    em_electronPID;
  NTuple::Item<double>    ep_kaonPID;
  NTuple::Item<double>    em_kaonPID;
  NTuple::Item<double>    ep_pionPID;
  NTuple::Item<double>    em_pionPID;

  NTuple::Item<double>    pip_electronPID;
  NTuple::Item<double>    pim_electronPID;
  NTuple::Item<double>    pip_kaonPID;
  NTuple::Item<double>    pim_kaonPID;
  NTuple::Item<double>    pip_pionPID;
  NTuple::Item<double>    pim_pionPID;


  NTuple::Item<double>    ep_exttheta;
  NTuple::Item<double>    ep_extphi;
  NTuple::Item<double>    ep_ext_x;
  NTuple::Item<double>    ep_ext_y;
  NTuple::Item<double>    ep_ext_z;

  NTuple::Item<double>    em_exttheta;
  NTuple::Item<double>    em_extphi;
  NTuple::Item<double>    em_ext_x;
  NTuple::Item<double>    em_ext_y;
  NTuple::Item<double>    em_ext_z;


  NTuple::Item<double>    ep_EOP;
  NTuple::Item<double>    em_EOP;
  NTuple::Item<double>   ep_ECAL;
  NTuple::Item<double>   em_ECAL;

  NTuple::Item<double>   ep_A42;
  NTuple::Item<double>   ep_lat;
  NTuple::Item<double>   ep_e3x3;
  NTuple::Item<double>   ep_e5x5;
  NTuple::Item<double>   ep_A20;
  NTuple::Item<double>   ep_secondMoment;
  NTuple::Item<double>   ep_eSeed;
  NTuple::Item<double>   ep_e5divSeed_fromEMC;
  NTuple::Item<double>   ep_e3divSeed_fromEMC;
  NTuple::Item<double>   ep_e5div3_fromEMC;
  NTuple::Item<double>   ep_theta_fromEMC;
  NTuple::Item<double>   ep_phi_fromEMC;
  NTuple::Item<double>   ep_x_fromEMC;
  NTuple::Item<double>   ep_y_fromEMC;
  NTuple::Item<double>   ep_z_fromEMC;
  NTuple::Item<double>   ep_numhits;
 


  NTuple::Item<double>   em_A42;
  NTuple::Item<double>   em_lat;
  NTuple::Item<double>   em_e3x3;
  NTuple::Item<double>   em_e5x5;
  NTuple::Item<double>   em_A20;
  NTuple::Item<double>   em_secondMoment;
  NTuple::Item<double>   em_eSeed;
  NTuple::Item<double>   em_e5divSeed_fromEMC;
  NTuple::Item<double>   em_e3divSeed_fromEMC;
  NTuple::Item<double>   em_e5div3_fromEMC;
  NTuple::Item<double>   em_theta_fromEMC;
  NTuple::Item<double>   em_phi_fromEMC;
  NTuple::Item<double>   em_x_fromEMC;
  NTuple::Item<double>   em_y_fromEMC;
  NTuple::Item<double>   em_z_fromEMC;
  NTuple::Item<double>   em_numhits;


  NTuple::Item<double>   ep_numGoodHits;
  NTuple::Item<double>   ep_numTotalHits;
  NTuple::Item<double>   ep_dedxchi;


  NTuple::Item<double>   em_numGoodHits;
  NTuple::Item<double>   em_numTotalHits;
  NTuple::Item<double>   em_dedxchi;


  NTuple::Item<int>  m_npip;
  NTuple::Item<int>  m_npim;

  NTuple::Item<double>    pip_exttheta;
  NTuple::Item<double>    pip_extphi;
  NTuple::Item<double>    pip_ext_x;
  NTuple::Item<double>    pip_ext_y;
  NTuple::Item<double>    pip_ext_z;

  NTuple::Item<double>    pim_exttheta;
  NTuple::Item<double>    pim_extphi;
  NTuple::Item<double>    pim_ext_x;
  NTuple::Item<double>    pim_ext_y;
  NTuple::Item<double>    pim_ext_z;


  NTuple::Item<double>    pip_EOP;
  NTuple::Item<double>    pim_EOP;
  NTuple::Item<double>   pip_ECAL;
  NTuple::Item<double>   pim_ECAL;


 NTuple::Item<double>   pip_A42;
  NTuple::Item<double>   pip_lat;
  NTuple::Item<double>   pip_e3x3;
  NTuple::Item<double>   pip_e5x5;
  NTuple::Item<double>   pip_A20;
  NTuple::Item<double>   pip_secondMoment;
  NTuple::Item<double>   pip_eSeed;
  NTuple::Item<double>   pip_e5divSeed_fromEMC;
  NTuple::Item<double>   pip_e3divSeed_fromEMC;
  NTuple::Item<double>   pip_e5div3_fromEMC;
  NTuple::Item<double>   pip_theta_fromEMC;
  NTuple::Item<double>   pip_phi_fromEMC;
  NTuple::Item<double>   pip_x_fromEMC;
  NTuple::Item<double>   pip_y_fromEMC;
  NTuple::Item<double>   pip_z_fromEMC;
  NTuple::Item<double>   pip_numhits;


  NTuple::Item<double>   pim_A42;
  NTuple::Item<double>   pim_lat;
  NTuple::Item<double>   pim_e3x3;
  NTuple::Item<double>   pim_e5x5;
  NTuple::Item<double>   pim_A20;
  NTuple::Item<double>   pim_secondMoment;
  NTuple::Item<double>   pim_eSeed;
  NTuple::Item<double>   pim_e5divSeed_fromEMC;
  NTuple::Item<double>   pim_e3divSeed_fromEMC;
  NTuple::Item<double>   pim_e5div3_fromEMC;
  NTuple::Item<double>   pim_theta_fromEMC;
  NTuple::Item<double>   pim_phi_fromEMC;
  NTuple::Item<double>   pim_x_fromEMC;
  NTuple::Item<double>   pim_y_fromEMC;
  NTuple::Item<double>   pim_z_fromEMC;
  NTuple::Item<double>   pim_numhits;

  NTuple::Item<double>   pip_numGoodHits;
  NTuple::Item<double>   pip_numTotalHits;
  NTuple::Item<double>   pip_dedxchi;


  NTuple::Item<double>   pim_numGoodHits;
  NTuple::Item<double>   pim_numTotalHits;
  NTuple::Item<double>   pim_dedxchi;



  NTuple::Item<double>    dipi_vtxfit_chi2;

  NTuple::Item<double>  Dipimass;
  NTuple::Item<double>  Dipipx;
  NTuple::Item<double>  Dipipy;
  NTuple::Item<double>  Dipipz;
  NTuple::Item<double>  Dipie;
  NTuple::Item<double>  Dipitheta;
  NTuple::Item<double>  Dipiphi;
  NTuple::Item<double>  Dipimom;

  NTuple::Item<double>  pipmass;
  NTuple::Item<double>  pippx;
  NTuple::Item<double>  pippy;
  NTuple::Item<double>  pippz;
  NTuple::Item<double>  pipe;
  NTuple::Item<double>  piptheta;
  NTuple::Item<double>  pipphi;
  NTuple::Item<double>  pipmom;


  NTuple::Item<double>  pimmass;
  NTuple::Item<double>  pimpx;
  NTuple::Item<double>  pimpy;
  NTuple::Item<double>  pimpz;
  NTuple::Item<double>  pime;
  NTuple::Item<double>  pimtheta;
  NTuple::Item<double>  pimphi;
  NTuple::Item<double>  pimmom;

  NTuple::Item<double>  Dipi_fit_mass;
  NTuple::Item<double>  Dipi_fit_e;
  NTuple::Item<double>  Dipi_fit_px;
  NTuple::Item<double>  Dipi_fit_py;
  NTuple::Item<double>  Dipi_fit_pz;
  NTuple::Item<double>  Dipi_fit_theta;
  NTuple::Item<double>  Dipi_fit_phi;
  NTuple::Item<double>  Dipi_fit_mom;

  NTuple::Item<double>  pip_fit_mass;
  NTuple::Item<double>  pip_fit_e;
  NTuple::Item<double>  pip_fit_px;
  NTuple::Item<double>  pip_fit_py;
  NTuple::Item<double>  pip_fit_pz;
  NTuple::Item<double>  pip_fit_theta;
  NTuple::Item<double>  pip_fit_phi;
  NTuple::Item<double>  pip_fit_mom;

  NTuple::Item<double>  pim_fit_mass;
  NTuple::Item<double>  pim_fit_e;
  NTuple::Item<double>  pim_fit_px;
  NTuple::Item<double>  pim_fit_py;
  NTuple::Item<double>  pim_fit_pz;
  NTuple::Item<double>  pim_fit_theta;
  NTuple::Item<double>  pim_fit_phi;
  NTuple::Item<double>  pim_fit_mom;


  NTuple::Item<double>   pi0_fit_mass;
  NTuple::Item<double>   pi0_fit_e;
  NTuple::Item<double>   pi0_fit_px;
  NTuple::Item<double>   pi0_fit_py;
  NTuple::Item<double>   pi0_fit_pz;
  NTuple::Item<double>   pi0_fit_theta;
  NTuple::Item<double>   pi0_fit_phi;
  NTuple::Item<double>   pi0_fit_mom;


  NTuple::Item<double>    elect_vtxfit_chi2;


  NTuple::Item<double>  Dielecmass;
  NTuple::Item<double>  Dielecpx;
  NTuple::Item<double>  Dielecpy;
  NTuple::Item<double>  Dielecpz;
  NTuple::Item<double>  Dielece;
  NTuple::Item<double>  Dielectheta;
  NTuple::Item<double>  Dielecphi;



  NTuple::Item<double>  _epmass;
  NTuple::Item<double>  _eppx;
  NTuple::Item<double>  _eppy;
  NTuple::Item<double>  _eppz;
  NTuple::Item<double>  _epe;
  NTuple::Item<double>  _eptheta;
  NTuple::Item<double>  _epphi;


  NTuple::Item<double>  _emmass;
  NTuple::Item<double>  _empx;
  NTuple::Item<double>  _empy;
  NTuple::Item<double>  _empz;
  NTuple::Item<double>  _eme;
  NTuple::Item<double>  _emtheta;
  NTuple::Item<double>  _emphi;



  NTuple::Item<double>    fourCchi2;


  NTuple::Item<double>  Dielec_fit_mass;
  NTuple::Item<double>  Dielec_fit_px;
  NTuple::Item<double>  Dielec_fit_py;
  NTuple::Item<double>  Dielec_fit_pz;
  NTuple::Item<double>  Dielec_fit_e;
  NTuple::Item<double>  Dielec_fit_theta;
  NTuple::Item<double>  Dielec_fit_phi;
  NTuple::Item<double>  Dielec_fit_mom;

  NTuple::Item<double>  epmass;
  NTuple::Item<double>  eppx;
  NTuple::Item<double>  eppy;
  NTuple::Item<double>  eppz;
  NTuple::Item<double>  epe;
  NTuple::Item<double>  eptheta;
  NTuple::Item<double>  epphi;
  NTuple::Item<double>  epmom;


  NTuple::Item<double>  emmass;
  NTuple::Item<double>  empx;
  NTuple::Item<double>  empy;
  NTuple::Item<double>  empz;
  NTuple::Item<double>  eme;
  NTuple::Item<double>  emtheta;
  NTuple::Item<double>  emphi;
  NTuple::Item<double>  emmom;


  NTuple::Item<double>  etamass;
  NTuple::Item<double>  etapx;
  NTuple::Item<double>  etapy;
  NTuple::Item<double>  etapz;
  NTuple::Item<double>  etae;
  NTuple::Item<double>  etatheta;
  NTuple::Item<double>  etaphi;
  NTuple::Item<double>  etamom;


  NTuple::Item<double>  Rx_Gam_gamcon;
  NTuple::Item<double>  Ry_Gam_gamcon;
  NTuple::Item<double>  Rvxy_Gam_gamcon; 
  NTuple::Item<double>  mee_gamcon; 

  NTuple::Item<double>  xconv_gamcon;
  NTuple::Item<double>  yconv_gamcon;
  NTuple::Item<double>  rconv_gamcon;

  NTuple::Item<double>  xconv1_gamcon;
  NTuple::Item<double>  yconv1_gamcon;
  NTuple::Item<double>  rconv1_gamcon;


  NTuple::Item<double>  xconv2_gamcon;
  NTuple::Item<double>  yconv2_gamcon;
  NTuple::Item<double>  rconv2_gamcon;


  NTuple::Item<double>  zconv_gamcon;   
  NTuple::Item<double>  Dee_Mdc_gamcon;
  NTuple::Item<double>  Dee_Bp_gamcon;

  NTuple::Item<double>  xiep_gamcon ;
  NTuple::Item<double>  deltaxy_gamcon;
 
  NTuple::Item<double>  mconv_gamcon;
  NTuple::Item<double>  econv_gamcon;
  NTuple::Item<double>  thetaconv_gamcon; 
  NTuple::Item<double>  costhetaconv_gamcon;
  NTuple::Item<double>  phiconv_gamcon;
  NTuple::Item<double>  angEE_gamcon;

  NTuple::Item<double>    em_time_tof;
  NTuple::Item<double>    em_sigma_tof;
  NTuple::Item<double>    em_expEtof;

  NTuple::Item<double>    ep_time_tof;
  NTuple::Item<double>    ep_sigma_tof;
  NTuple::Item<double>    ep_expEtof;


  NTuple::Array<double>   m_pip_pull;
  NTuple::Array<double>   m_pim_pull;
  NTuple::Array<double>   m_ep_pull;
  NTuple::Array<double>   m_em_pull;

  NTuple::Array<double>   m_pipvert_pull;
  NTuple::Array<double>   m_pimvert_pull;
  NTuple::Array<double>   m_epvert_pull;
  NTuple::Array<double>   m_emvert_pull;


  NTuple::Item<double>    Goodphotlab;


  NTuple::Item<double>  misTrkGammass;
  NTuple::Item<double>  misTrkGampx;
  NTuple::Item<double>  misTrkGampy;
  NTuple::Item<double>  misTrkGampz;
  NTuple::Item<double>  misTrkGame;
  NTuple::Item<double>  misTrkGamtheta;
  NTuple::Item<double>  misTrkGamphi;
  NTuple::Item<double>  misTrkGammom;

  NTuple::Item<double>  game;
  NTuple::Item<double>  gammom;
  NTuple::Item<double>  gamtheta;
  NTuple::Item<double>  gamphi;

  NTuple::Item<double>  _A42;
  NTuple::Item<double>  _lat;
  NTuple::Item<double>  _e3x3;
  NTuple::Item<double>  _e5x5;
  NTuple::Item<double>  _A20;

  NTuple::Item<double>  gamx;
  NTuple::Item<double>  gamy;
  NTuple::Item<double>  gamz;
  NTuple::Item<double>  gamdx;
  NTuple::Item<double>  gamdy;
  NTuple::Item<double>  gamdz;
  NTuple::Item<double>  gamdtheta;
  NTuple::Item<double>  gamdphi;
  NTuple::Item<double>  gamdE;
  NTuple::Item<double>  gameseed;
  NTuple::Item<double>  gamesecondMoment;
  NTuple::Item<double>  gametime;
  NTuple::Item<double>  gamemodule;
  NTuple::Item<double>  gamecellId;
  NTuple::Item<double>  gamestatus;
  NTuple::Item<double>  gamenumHits;

  NTuple::Item<double>  misGamTrkanglephoton;

};

#endif 
