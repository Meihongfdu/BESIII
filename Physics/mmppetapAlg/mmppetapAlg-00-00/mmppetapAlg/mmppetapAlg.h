#ifndef Physics_Analysis_mmppetapAlg_H
#define Physics_Analysis_mmppetapAlg_H 
//#include <string>

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"
#include "CLHEP/Matrix/Vector.h"
using CLHEP::HepVector;
#ifndef CLHEP_POINT3D_H
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#endif

class mmppetapAlg : public Algorithm {
public:
  mmppetapAlg(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:
  
  //event Num
  int m_nEvtDisp;
  int m_nEvt;

  bool   mctruth();
  bool   m_mctruth;
  double m_cms;
  int    m_cms_id;
  bool   m_test_4C;
	bool   m_test_5C;
  HepPoint3D Get_HelixCenter(HepVector helix);
  double     Get_HelixRadius(HepVector helix);
  HepPoint3D intersections(HepVector helix,double r);
  double Get_Dee(HepVector helixe,HepVector helixp,double r); 
 
 
  NTuple::Tuple*  m_tuple1;   
  
  NTuple::Item<int>       m_run;
  NTuple::Item<int>       m_event;
  
  NTuple::Item<int>       m_idxmc;
  NTuple::Array<int>      m_pdgid;
  NTuple::Array<int>      m_motheridx;

  NTuple::Matrix<double>  m_p4_tru;
  NTuple::Array<double>   m_p_tru;
  NTuple::Array<double>   m_m_tru;
  NTuple::Array<double>   m_cos_tru;
  
  NTuple::Item<double>    m_mctrue_gam_theta;
  NTuple::Item<double>    m_mctruth_mpipietap_phsp;
  NTuple::Array<double>   m_mctrue_gam_pi0;
  NTuple::Array<double>   m_mctrue_ep;
  NTuple::Array<double>   m_mctrue_em;
  NTuple::Array<double>   m_mctrue_pip;
  NTuple::Array<double>   m_mctrue_pim;
  NTuple::Array<double>   m_mctrue_pip_etap_4c;
  NTuple::Array<double>   m_mctrue_pim_etap_4c;
  NTuple::Array<double>   m_mctrue_gam_etap_4c;
  NTuple::Item<double>    m_mctrue_gam_etap_theta;
  NTuple::Item<double>    m_mctrue_mpipietap_4c;
  NTuple::Item<double>    m_mctrue_meppimetap_4c;
  NTuple::Item<double>    m_mctrue_mempipetap_4c;
  NTuple::Item<double>    m_mctrue_meeetap_4c;
  NTuple::Item<double>    m_mctruth_ee_4c;
  NTuple::Item<double>    m_mctruth_epim_4c;
  NTuple::Item<double>    m_mctruth_epip_4c;
  NTuple::Item<double>    m_mctrue_mpipi_4c;
  NTuple::Item<double>    m_mctrue_mrho_4c;
  NTuple::Item<double>    m_mctrue_mpipetap_4c;
  NTuple::Item<double>    m_mctrue_mpimetap_4c;
  NTuple::Item<double>    m_mctruth_ee_5c;
  NTuple::Array<double>   m_mctrue_pip_etap_5c;
  NTuple::Array<double>   m_mctrue_pim_etap_5c;
  NTuple::Array<double>   m_mctrue_gam1_eta_5c;
  NTuple::Array<double>   m_mctrue_gam2_eta_5c;
  NTuple::Array<double>   m_mctruth_ep_4c;
  NTuple::Array<double>   m_mctruth_em_4c;
  NTuple::Array<double>   m_mctruth_pi0gam_4c;
  NTuple::Array<double>   m_mctruth_pi0gam_2_4c;
  NTuple::Array<double>   m_mctruth_m1835;
  NTuple::Item<double>    m1835_mct;
  NTuple::Item<double>    mctr_pep;
  NTuple::Item<double>    mctr_pem;
  NTuple::Item<double>    mctr_gam1;
  NTuple::Item<double>    mctr_gam2;
  NTuple::Item<double>    mctr_Pgam_max;
  NTuple::Item<double>    mctr_Pgam_min;
  NTuple::Item<double>    m_mctrue_mpipietap_5c;
  NTuple::Item<double>    m_mctrue_metap_5c;
  NTuple::Item<double>    m_mctrue_mpipi_5c;
  NTuple::Item<double>    m_mctrue_mpipetap_5c;
  NTuple::Item<double>    m_mctrue_mpimetap_5c;
  
  NTuple::Tuple*  m_tuple2;
  
  NTuple::Item<int>       m_rec_run;
  NTuple::Item<int>       m_rec_event;
  NTuple::Item<int>       m_rec_nchrg;
  NTuple::Item<int>       m_rec_nneu;
  
  NTuple::Item<int>       m_rec_idxmc;
  NTuple::Array<int>      m_rec_pdgid;
  NTuple::Array<int>      m_rec_motheridx;
  
  
  NTuple::Item<int>       m_ngam;
  NTuple::Item<int>       m_nGam;
  NTuple::Array<double>   m_dang;
  NTuple::Array<double>   m_tdc;
  NTuple::Array<double>   m_angle;
  NTuple::Array<double>   m_energy;
  NTuple::Array<double>   m_phopx;
  NTuple::Array<double>   m_phopy;
  NTuple::Array<double>   m_phopz;
	NTuple::Array<double>   m_phoe;
	NTuple::Array<double>   m_eseed ;
	NTuple::Array<double>   m_e3x3 ;
	NTuple::Array<double>   m_e5x5 ;
	NTuple::Array<double>   m_theta ;
	NTuple::Array<double>   m_phi ;
	NTuple::Array<double>   m_secondMoment ;
	NTuple::Array<double>   m_latMoment ;
	NTuple::Array<double>   m_a20Moment ;
	NTuple::Array<double>   m_a42Moment ;
	NTuple::Array<double>   m_eall ;
	NTuple::Array<double>   m_elep ;
	NTuple::Array<double>   m_edel ;
	NTuple::Array<double>   m_ratio_e19 ;
	NTuple::Array<double>   m_ratio_e925 ;
	NTuple::Array<double>   m_ratio_e125 ;  

  NTuple::Item<int>       m_ngpairs;
  NTuple::Array<double>   m_mgg ;
  //NTuple::Item<int>       m_ncomb_pi0_ppe;
  //NTuple::Array<double>   m_mgam0ee_allcomb_5c ;
  NTuple::Item<int>       m_ncomb_5c;
  NTuple::Array<double>   m_etap_allcomb_5c ;
  //NTuple::Item<int>       m_ncomb_pi0_rho;
  //NTuple::Array<double>   m_mgam0ee_allcomb_4c ;
  NTuple::Item<int>       m_ncomb;
  NTuple::Array<double>   m_etap_rho_allcomb_4c ;
  NTuple::Item<int>       m_ncomb_x;
  NTuple::Array<double>   m_pipietap_rho_allcomb_4c ;
  NTuple::Item<int>       m_ncomb_5c_x;
  NTuple::Array<double>   m_pipietap_allcomb_5c ;


  NTuple::Item<double>    m_mpi0_gg;
  NTuple::Item<double>    m_meta_gg;
  NTuple::Item<double>    m_mgamee_eta;
  NTuple::Item<double>    m_mgamee_rho;

  NTuple::Item<int>       m_ngamma;
	NTuple::Array<double>   m_mgameepairs_allcomb_rho;  
	NTuple::Array<double>   m_mgameepairs_eta;  
	NTuple::Array<double>   m_mgameepairs_rho;  
	NTuple::Array<double>   m_mgampipipairs_eta;  
	NTuple::Array<double>   m_mgampipipairs_rho;  

  NTuple::Item<double>    m_elep_pid_prob;
  NTuple::Item<double>    m_elep_pid_probR;
  NTuple::Item<double>    m_elem_pid_prob;
  NTuple::Item<double>    m_elem_pid_probR;

  NTuple::Matrix<double>  m_prob_chp;
  NTuple::Matrix<double>  m_prob_chm;

	NTuple::Matrix<double>  m_p4_wo4_pip;
	NTuple::Matrix<double>  m_p4_wo4_pim;
	NTuple::Matrix<double>  m_p4_wo4_elp;
//	NTuple::Array<double>   m_p4_wo4_elm;
	//NTuple::Array<double>   m_p4_wo4_elp;
	//NTuple::Array<double>   m_p4_wo4_elm;
  NTuple::Matrix<double>  m_trk_info_pip;
  NTuple::Matrix<double>  m_trk_info_pim;
  NTuple::Matrix<double>  m_trk_info_elp;
  //NTuple::Array<double>   m_trk_info_elp;
  //NTuple::Array<double>   m_trk_info_elm;

  NTuple::Array<int>      m_ich;
  NTuple::Array<int>      m_nch;
  NTuple::Array<int>      m_id_track_wo4;
  
  NTuple::Item<int>       m_npion;
  NTuple::Item<double>    E1;
  NTuple::Item<double>    E2;
  NTuple::Item<double>    E3;
  NTuple::Item<double>    E4;
  NTuple::Item<double>    E5;
  NTuple::Item<double>    E6;
  NTuple::Item<double>    ep1;
  NTuple::Item<double>    ep2;
  NTuple::Item<double>    ep3;
  NTuple::Item<double>    ep4;
  NTuple::Item<double>    ep5;
  NTuple::Item<double>    ep6;
  NTuple::Item<double>    trk1p;
  NTuple::Item<double>    trk2p;
  NTuple::Item<double>    trk3p;
  NTuple::Item<double>    trk4p;
  NTuple::Item<double>    trk5p;
  NTuple::Item<double>    trk6p;

   NTuple::Item<double>  m_mu1_Lay;
   NTuple::Item<double>  m_mu2_Lay;
   NTuple::Item<double>  m_mu3_Lay;
   NTuple::Item<double>  m_mu4_Lay;
   NTuple::Item<double>  m_mu5_Lay;
   NTuple::Item<double>  m_mu6_Lay;

   NTuple::Item<double>  m_mu1_Dep;
   NTuple::Item<double>  m_mu2_Dep;
   NTuple::Item<double>  m_mu3_Dep;
   NTuple::Item<double>  m_mu4_Dep;
   NTuple::Item<double>  m_mu5_Dep;
   NTuple::Item<double>  m_mu6_Dep;

   NTuple::Item<double>  m_mu1_Nhits;
   NTuple::Item<double>  m_mu2_Nhits;
   NTuple::Item<double>  m_mu3_Nhits;
   NTuple::Item<double>  m_mu4_Nhits;
   NTuple::Item<double>  m_mu5_Nhits;
   NTuple::Item<double>  m_mu6_Nhits;

   NTuple::Item<double>  m_mu1_LastLay;
   NTuple::Item<double>  m_mu2_LastLay;
   NTuple::Item<double>  m_mu3_LastLay;
   NTuple::Item<double>  m_mu4_LastLay;
   NTuple::Item<double>  m_mu5_LastLay;
   NTuple::Item<double>  m_mu6_LastLay;

   NTuple::Item<double>  m_mu1_maxHitsInLay;
   NTuple::Item<double>  m_mu2_maxHitsInLay;
   NTuple::Item<double>  m_mu3_maxHitsInLay;
   NTuple::Item<double>  m_mu4_maxHitsInLay;
   NTuple::Item<double>  m_mu5_maxHitsInLay;
   NTuple::Item<double>  m_mu6_maxHitsInLay;

  NTuple::Item<double>    m_vxchisq_ee;
  NTuple::Item<double>    m_vxchisq;

  NTuple::Item<double>    Rx_Gam_gamcon;
  NTuple::Item<double>    Ry_Gam_gamcon;
  NTuple::Item<double>    Rvxy_Gam_gamcon;

  NTuple::Item<double>    xconv_gamcon;
  NTuple::Item<double>    yconv_gamcon;
  NTuple::Item<double>    rconv_gamcon;

  NTuple::Item<double>    xconv1_gamcon;
  NTuple::Item<double>    yconv1_gamcon;
  NTuple::Item<double>    rconv1_gamcon;


  NTuple::Item<double>    xconv2_gamcon;
	NTuple::Item<double>    yconv2_gamcon;
	NTuple::Item<double>    rconv2_gamcon;

  NTuple::Item<double>    xconv3_gamcon;
	NTuple::Item<double>    yconv3_gamcon;
	NTuple::Item<double>    rconv3_gamcon;

	NTuple::Item<double>    zconv_gamcon;
	NTuple::Item<double>    Dee_Mdc_gamcon;
  NTuple::Item<double>    Dee_Bp_gamcon;

  NTuple::Item<double>    xiep_gamcon ;
  NTuple::Item<double>    xiep_gamcon_1 ;
  NTuple::Item<double>    xiep_gamcon_2 ;
  NTuple::Item<double>    deltaxy_gamcon;
  NTuple::Item<double>    deltaphi0_ee;
  NTuple::Item<double>    m_costheta_eg;

  NTuple::Item<double>    mconv_gamcon;
  NTuple::Item<double>    econv_gamcon;
  NTuple::Item<double>    thetaconv_gamcon;
  NTuple::Item<double>    costhetaconv_gamcon;
  NTuple::Item<double>    phiconv_gamcon;
  NTuple::Item<double>    angEE_gamcon;



  NTuple::Item<double>    m_chi2_eta_5c;
  NTuple::Item<double>    m_chi2_rho_4c;
  
  //for the channel pi pi eta
  NTuple::Item<double>    m_gam0ee_ppe;
  NTuple::Item<double>    m_ee_5c;
  NTuple::Item<double>    m_eta_5c;
  NTuple::Item<double>    m_etap_5c;
  NTuple::Item<double>    m_pipietap_5c;
	NTuple::Array<double>   m_pipieta_5c ;  

  // four momentum of all sub particles
	NTuple::Array<double>   m_p4_eta_5c ;  
	NTuple::Array<double>   m_p4_ep_5c ;  
	NTuple::Array<double>   m_p4_em_5c ;  
	NTuple::Array<double>   m_p4_pip1_5c ;  
	NTuple::Array<double>   m_p4_pim1_5c ;  
	NTuple::Array<double>   m_p4_pip2_5c ;  
	NTuple::Array<double>   m_p4_pim2_5c ;  
	NTuple::Array<double>   m_gamee_eta_5c ;  

  NTuple::Item<double>    m_ee_kal;
  NTuple::Item<double>    m_eta_kal;
  NTuple::Item<double>    m_etap_kal;
  NTuple::Item<double>    m_pipietap_kal;

  // four momentum of all sub particles
	NTuple::Array<double>   m_p4_eta_kal ;  
	NTuple::Array<double>   m_p4_ep_kal ;  
	NTuple::Array<double>   m_p4_em_kal ;  
	NTuple::Array<double>   m_p4_pip1_kal ;  
	NTuple::Array<double>   m_p4_pim1_kal ;  
	NTuple::Array<double>   m_p4_pip2_kal ;  
	NTuple::Array<double>   m_p4_pim2_kal ;  
	NTuple::Item<double>   m_theta1_kal ;  
	NTuple::Item<double>   m_theta2_kal ;  

  // for the channel gamma pipi

  NTuple::Item<double>    m_gam0ee_rho;
  NTuple::Item<double>    m_ee_rho_4c;
  NTuple::Item<double>    m_epim_rho_4c;
  NTuple::Item<double>    m_epip_rho_4c;
  NTuple::Item<double>    m_ee_rho_4c_rec;
  NTuple::Item<double>    m_ee_rho_rec;
  NTuple::Item<double>    m_pipietap_rho_4c_rec;
  NTuple::Item<double>    m_pipietap_rho_rec;
  NTuple::Item<double>    m_gamee_rho_4c;
  NTuple::Item<double>    m_rho_4c;
  NTuple::Item<double>    m_etap_rho_4c;
  NTuple::Item<double>    m_pipietap_rho_4c;
	NTuple::Array<double>   m_pipi_rho_4c ;  
  NTuple::Item<double>    m_EE_all;
  NTuple::Item<double>    m_Egam0_all;
  NTuple::Item<double>    m_Egam0;
  NTuple::Item<int>       m_nigam0_da;

  // four momentum of all sub particles
	NTuple::Array<double>   m_p4_gam_rho_4c ;  
  NTuple::Item<double>    m_gam_etap_theta_4c;
	NTuple::Array<double>   m_p4_ep_rho_4c ;  
	NTuple::Array<double>   m_p4_em_rho_4c ;  
	NTuple::Array<double>   m_p4_pip1_rho_4c ;  
	NTuple::Array<double>   m_p4_pim1_rho_4c ;  
	NTuple::Array<double>   m_p4_pip2_rho_4c ;  
	NTuple::Array<double>   m_p4_pim2_rho_4c ;  

  NTuple::Item<double>    m_ee_rho_kal;
  NTuple::Item<double>    m_rho_kal;
  NTuple::Item<double>    m_etap_rho_kal;
  NTuple::Item<double>    m_pipietap_rho_kal;

  // four momentum of all sub particles
	NTuple::Array<double>   m_p4_gam_rho_kal ;  
	NTuple::Item<double>   m_theta_rho_kal ;  
	NTuple::Item<double>   m_theta_rho_kal_test ;  
	NTuple::Array<double>   m_p4_ep_rho_kal ;  
	NTuple::Array<double>   m_p4_em_rho_kal ;  
	NTuple::Array<double>   m_p4_pip1_rho_kal ;  
	NTuple::Array<double>   m_p4_pim1_rho_kal ;  
	NTuple::Array<double>   m_p4_pip2_rho_kal ;  
  NTuple::Array<double>   m_p4_pim2_rho_kal ;  
  NTuple::Array<double>   m_mctrue_ppip;
  NTuple::Array<double>   m_mctrue_ppim;
  NTuple::Array<double>   m_mctrue_pgam_etap_4c;
  NTuple::Array<double>   m_mctrue_ppip_etap_4c;
  NTuple::Array<double>   m_mctrue_ppim_etap_4c;
  NTuple::Item<double>    m_mctrue_Ppip;
  NTuple::Item<double>    m_mctrue_Ppim;
  NTuple::Item<double>    m_mctrue_Ppip_etap_4c;
  NTuple::Item<double>    m_mctrue_Ppim_etap_4c;
  NTuple::Item<double>    m_mctrue_Pgam_etap_4c;
  NTuple::Item<double>    m_delta_angle_pgam_etap_4c;
  NTuple::Item<double>    m_delta_angle_ppip_etap_4c;
  NTuple::Item<double>    m_delta_angle_ppim_etap_4c;

  //NTuple::Array<double>   m_mctrue_pgam_etap_4c;
  NTuple::Item<double>    delta_angle;
  NTuple::Item<double>    delta_energy;
  NTuple::Item<double>    m_gampipi_ck;
  NTuple::Item<double>    m_eepipi_ck_rho;
  NTuple::Item<double>    m_eepipi_ck;


  //NTuple::Matrix<double>  m_p4_eta_5c;
  //NTuple::Matrix<double>  m_p4_rho_4c;
  
  //NTuple::Item<int>       m_eta_ig1;
  //NTuple::Item<int>       m_eta_ig2;
  //NTuple::Item<int>       m_rho_ig3;


  NTuple::Item<double>    m_prob_eta_5c;
  NTuple::Item<double>    m_prob_rho_4c;

};
#endif




