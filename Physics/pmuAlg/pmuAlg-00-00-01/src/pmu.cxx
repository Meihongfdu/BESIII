#include "GaudiKernel/MsgStream.h"//we write this package to obtain all single channel
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"
#include "DTagTool/DTagTool.h"
#include "McTruth/McParticle.h" //need to add use McTruth in the requirements of cmt

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"
#include "Ecmset/Ecmset.h"
#include "VertexFit/IVertexDbSvc.h"
 #include "VertexFit/SecondVertexFit.h"
 #include "VertexFit/VertexFit.h"
#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::HepLorentzVector;
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
   typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#include "pmuAlg/pmu.h"

#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include <vector>
//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double mpi0 = 0.1349766;
const double md0 =1.86483;
const double mdp =1.86965;
const double msigma =1.18937;
const double mlambda =1.115683;
const double mlambdac=2.2849;
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
const double xmass[5]={0.000511,0.105658,0.139570,0.493677,0.938272};
//////////////////////////////
int npi=0,nk=0,npi0p=0,npi0m=0,ne=0,np=0;
int x1[10]={0,0,0,0,0,0,0,0,0,0};
int x0[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int tot_events=0;
const double ecm=3.097;
//const double ecm=4.009;
//const double ecm=4.178;
//const double ecm=4.600;
typedef std::vector<int> Vint;
typedef std::vector<double> Vdou;
typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<WTrackParameter> Vtrack;

//////////////
bool oksq_4c_2, oksq_4c;
bool mini_delE;
int       T_tagmode,   tagmode_temp, tagcharge_temp,         sigtagcharge,                ncount,                 ncount2;
int      Ncharge_ex,tag_pid_temp,	tag_pi0id1_temp,	tag_pi0id2_temp,  tag_piid_temp;
int tag_pid_temp_2, tag_piid_temp_2, sig_pid_temp_2, sig_eid_temp_2;
int	pipD=0,	pimD=0,	pipD2mu=0,	pimD2mu=0;
double     xinvmass, 	reco_mass, mass_reco_tag,   pdp_rho_temp,   mass_bc_temp, deltaE_temp,  m_pdp_theta, m_pdp_theta_2, m_pdp_phi,   pdp_e_temp;
double     mass_bc_temp_2,  deltaE_temp_2, evp_tag_1, evp_tag_2, evp_sig_1, evp_sig_2, eemc_sig_1, eemc_sig_2;
double      eemc_tag_1,  eemc_tag_2,  p_tag_1,     p_tag_2,     c_tag_1,     c_tag_2,    p_tag, c_tag,    deltaE_cut;
double       angle1,         angle2,         angle3,               angle4,                angle5,                 angle6;
double     T_angle1,       T_angle2,       T_angle3,             T_angle4,              T_angle5;
double 	emce, eemc_sig_mu_svf, eemc_sig_p_svf, evp_sig_mu_svf, evp_sig_p_svf;
double  eemc_sig_mu, eemc_sig_p, evp_sig_mu, evp_sig_p;
double 	eemc_sig_1_4c, eemc_sig_2_4c, evp_sig_1_4c, evp_sig_2_4c;
double p_sig_1,		p_sig_2,	p_sig_3,    p_sig_4,   p_sig_5, p_sig_6, p_sig_7, p_sig_8;
double c_sig_1,		c_sig_2,	c_sig_3;
double p_tag_11,	p_tag_12,	p_tag_13;
double c_tag_11,	c_tag_12,	c_tag_13;
double p_pt_rest_jpsi, 	p_pt_rest_lmd, p_pt_jp_la, p_pt_lp_ja;
double angle_pmu_57_4c_2,	 angle_pmu_57,	 angle_lampmu_58,  pte2_temp,   angle_pi_0616;
double q2_temp, q2_2_temp, q2_truth_temp;
double chi_cut,	tag_mass_bc,	gam_cut,	gam_e1,	gam_emax,	gam_e,           kmfit_chi,  tag_mass,             tag_deltaE;
double ene_gam_sigma0_1, ene_gam_sigma0_2;
double u_miss,	e_miss,	p_miss,	miss_m2,	lam_chi_tag,  lam_len_tag, lam_lenerr_tag;
double esig_V_ebeam, esig_V_ebeam_4c_2, u_miss_4c_2, e_miss_4c_2, p_miss_4c_2, miss_m2_4c_2;
double lam_len_sig, lam_chi_sig, lam_lenerr_sig, mass_lam_tag_4c, mass_lam_sig_4c, chi_4c, chi_4c_2, mass_jpsi, mass_sig_miss_pi_1, mass_sig_miss_pi_2, mass_sig_pmu_temp, mass_reco_lmdmu_temp;
WTrackParameter        S_trk_lam_tag,        S_trk_lam_pi_tag,              S_trk_lam_p_tag,               S_trk_4,                 S_trk_5;
WTrackParameter  sig_trk_lam, sig_trk_mu, sig_trk_p;


///////////





/////////////////////////////////////////////////////////////////////////////

pmu::pmu(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  declareProperty("GammaAngleCut", m_gammaAngleCut=10.0);//////////share  
  declareProperty("mctag", m_mctag=0);//////////share  
  declareProperty("debug", m_debug = false);
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode pmu::initialize(){
  MsgStream log(msgSvc(), name());


  log << MSG::INFO << "in initialize()" << endmsg;
  
  StatusCode status;

  NTuplePtr nt1(ntupleSvc(), "FILE1/single");
    if ( nt1 ) m_tuple1 = nt1;
    else {
     m_tuple1 = ntupleSvc()->book ("FILE1/single", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tuple1)     {
        status = m_tuple1->addItem ("mbc_tag",             mass_bc_temp_1);
        status = m_tuple1->addItem ("delE_tag",           delE_tag_temp_1);
        status = m_tuple1->addItem ("mbc_tag_2",        mass_bc_temp_test);
        status = m_tuple1->addItem ("delE_tag_2",      delE_tag_temp_test);
        status = m_tuple1->addItem ("mass_inv",           mass_inv_temp_1);
        status = m_tuple1->addItem ("mass_reco_tag", mass_reco_tag_temp_1);
        status = m_tuple1->addItem ("pdp_rho",                 pdp_temp_1);
        status = m_tuple1->addItem ("pdp_e",                 pdp_e_temp_1);
        status = m_tuple1->addItem ("event",                      m_irec1);
        status = m_tuple1->addItem ("runNo",                      m_irun1);
        status = m_tuple1->addItem ("tagcharge",         tagcharge_temp_1);
        status = m_tuple1->addItem ("tagmode",             tagmode_temp_1);
        status = m_tuple1->addItem ("cosmicray",         cosmicray_temp_1);
        status = m_tuple1->addItem ("lam_chi",             lam_chi_temp_1);
        status = m_tuple1->addItem ("lam_len",             lam_len_temp_1);
        status = m_tuple1->addItem ("lam_lenerr",       lam_lenerr_temp_1);

        status = m_tuple1->addItem ("c_tag_lam_theta",     p_theta_temp_1);//lambda
        status = m_tuple1->addItem ("p_tag_p",             p_tag_1_temp_1);//p
        status = m_tuple1->addItem ("c_tag_p",             c_tag_1_temp_1);
        status = m_tuple1->addItem ("eemc_tag_p",           eemc_1_temp_1);
        status = m_tuple1->addItem ("evp_tag_p",             evp_1_temp_1);
        status = m_tuple1->addItem ("p_tag_pi",            p_tag_2_temp_1);//pi
        status = m_tuple1->addItem ("c_tag_pi",            c_tag_2_temp_1);
        status = m_tuple1->addItem ("eemc_tag_pi",          eemc_2_temp_1);
        status = m_tuple1->addItem ("evp_tag_pi",            evp_2_temp_1);
        status = m_tuple1->addItem ("p_tag_lmd",             p_tag_temp_1);//lmd
        status = m_tuple1->addItem ("c_tag_lmd",             c_tag_temp_1);

        status = m_tuple1->addItem ("mctag",                 mctag_temp_1);

        status = m_tuple1->addItem ("mdbc1",                      mdbc1_1);
        status = m_tuple1->addItem ("mdbc2",                      mdbc2_1);
        status = m_tuple1->addItem ("mcmode1",                  mcmode1_1);
        status = m_tuple1->addItem ("mcmode2",                  mcmode2_1);
        status = m_tuple1->addItem ("mcmodea",                  mcmodea_1);
        status = m_tuple1->addItem ("mcmodeb",                  mcmodeb_1);

        status = m_tuple1->addItem ("T_angle1",           T_angle1_temp_1);//p
        status = m_tuple1->addItem ("T_angle2",           T_angle2_temp_1);//pi
        status = m_tuple1->addItem ("T_angle3",           T_angle3_temp_1);
        status = m_tuple1->addItem ("T_angle4",           T_angle4_temp_1);
        status = m_tuple1->addItem ("T_angle5",           T_angle5_temp_1);

        status = m_tuple1->addItem ("indexmc",            topo_temp_10,0, 500);
        status = m_tuple1->addIndexedItem ("pdgid",       topo_temp_10,  pdgid_temp_10);
        status = m_tuple1->addIndexedItem ("motheridx",   topo_temp_10,  mcidx_temp_10);

}
      else    {
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
        return StatusCode::FAILURE;
      }
    }
/////////////////////////////////////////
  NTuplePtr nt11(ntupleSvc(), "FILE1/signal");
    if ( nt11 ) m_tuple11 = nt11;
    else {
     m_tuple11 = ntupleSvc()->book ("FILE1/signal", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tuple11)     {
        status = m_tuple11->addItem ("event",                       m_irec_temp_11);
        status = m_tuple11->addItem ("runNo",                       m_irun_temp_11);
        status = m_tuple11->addItem ("mdbc1",                        mdbc1_temp_11);
        status = m_tuple11->addItem ("mdbc2",                        mdbc2_temp_11);
        status = m_tuple11->addItem ("mcmode1",                    mcmode1_temp_11);
        status = m_tuple11->addItem ("mcmode2",                    mcmode2_temp_11);
        status = m_tuple11->addItem ("mcmodea",                    mcmodea_temp_11);
        status = m_tuple11->addItem ("mcmodeb",                    mcmodeb_temp_11);
        status = m_tuple11->addItem ("cosmicray",                cosmicray_temp_11);

        status = m_tuple11->addItem ("pipD",                  pipD_temp_11);//2020.07.31 check the pion decay
        status = m_tuple11->addItem ("pimD",                  pimD_temp_11);
        status = m_tuple11->addItem ("pipD2mu",               pipD2mu_temp_11);
        status = m_tuple11->addItem ("pimD2mu",               pimD2mu_temp_11);

        status = m_tuple11->addItem ("p_pt_jr",               p_pt_rest_jpsi_temp_11);//2020.08.02 proton's transverse momentum
        status = m_tuple11->addItem ("p_pt_lr",               p_pt_rest_lmd_temp_11);
        status = m_tuple11->addItem ("p_pt_jp_la",            p_pt_jp_la_temp_11);
        status = m_tuple11->addItem ("p_pt_lp_ja",            p_pt_lp_ja_temp_11);

        status = m_tuple11->addItem ("mbc_tag",                tag_mass_bc_temp_11);
        status = m_tuple11->addItem ("delE_tag",                tag_deltaE_temp_11);
        status = m_tuple11->addItem ("mass_inv",                  tag_mass_temp_11);
        status = m_tuple11->addItem ("mass_reco",                reco_mass_temp_11);
        status = m_tuple11->addItem ("tagmode",                  T_tagmode_temp_11);
        status = m_tuple11->addItem ("tagcharge",            tag_tagcharge_temp_11);
        status = m_tuple11->addItem ("mctag",                        mctag_temp_11);

        status = m_tuple11->addItem ("q2",                              q2_temp_11);
        status = m_tuple11->addItem ("q2_2",                          q2_2_temp_11);
        status = m_tuple11->addItem ("q2_truth",                  q2_truth_temp_11);
        status = m_tuple11->addItem ("U_miss",                      u_miss_temp_11);
        status = m_tuple11->addItem ("E_miss",                      e_miss_temp_11);
        status = m_tuple11->addItem ("P_miss",                      p_miss_temp_11);
        status = m_tuple11->addItem ("mm2m",                       miss_m2_temp_11);

        status = m_tuple11->addItem ("mass_lam_tag_4c",              mass_lam_tag_4c_temp_11);
        status = m_tuple11->addItem ("mass_lam_sig_4c",              mass_lam_sig_4c_temp_11);
        status = m_tuple11->addItem ("mass_jpsi_4c_2",               mass_jpsi_4c_2_temp_11);
        status = m_tuple11->addItem ("mass_sig_miss_pi_1",           mass_sig_miss_pi_1_temp_11);//=(p_all-pdp_new-p_sig_4c_2).m()
        status = m_tuple11->addItem ("mass_sig_miss_pi_2",           mass_sig_miss_pi_2_temp_11);//=(p_all-pdp_new-Pvector[a]).m()
        status = m_tuple11->addItem ("mass_sig_pmu",                 mass_sig_pmu_temp_11);
        status = m_tuple11->addItem ("mass_reco_lmdmu",              mass_reco_lmdmu_temp_11);

        status = m_tuple11->addItem ("esig_V_ebeam",                 esig_V_ebeam_temp_11);
        status = m_tuple11->addItem ("esig_V_ebeam_4c",              esig_V_ebeam_4c_temp_11);

        status = m_tuple11->addItem ("angle_pmu_57",                 angle_pmu_57_temp_11);
        status = m_tuple11->addItem ("pte2",                         pte2_temp_11);
        status = m_tuple11->addItem ("angle_lampmu_58",              angle_lampmu_58_temp_11);
        status = m_tuple11->addItem ("angle_pi_0616",                angle_pi_0616_temp_11);

        status = m_tuple11->addItem ("evp_svf_p_sig",                evp_1_temp_11);
        status = m_tuple11->addItem ("evp_svf_mu_sig",               evp_2_temp_11);
        status = m_tuple11->addItem ("evp_p_tag",                    evp_3_temp_11);
        status = m_tuple11->addItem ("evp_pi_tag",                   evp_4_temp_11);
        status = m_tuple11->addItem ("evp_p_sig",                    evp_5_temp_11);
        status = m_tuple11->addItem ("evp_mu_sig",                   evp_6_temp_11);

        status = m_tuple11->addItem ("eemc_svf_p_sig",               eemc_1_temp_11);
        status = m_tuple11->addItem ("eemc_svf_mu_sig",              eemc_2_temp_11);
        status = m_tuple11->addItem ("eemc_p_tag",                   eemc_3_temp_11);
        status = m_tuple11->addItem ("eemc_pi_tag",                  eemc_4_temp_11);
        status = m_tuple11->addItem ("eemc_p_sig",                   eemc_5_temp_11);
        status = m_tuple11->addItem ("eemc_mu_sig",                  eemc_6_temp_11);

        status = m_tuple11->addItem ("p_sig_p",                      p_sig_1_temp_11);//p
        status = m_tuple11->addItem ("p_sig_mu",                     p_sig_2_temp_11);//mu
        status = m_tuple11->addItem ("p_sig_pi",                     p_sig_3_temp_11);//miss pi in the Lambda rest frame after 4C_2
        status = m_tuple11->addItem ("p_sig_pi2",                    p_sig_4_temp_11);//miss pi in the Lambda rest frame only reco
        status = m_tuple11->addItem ("p_sig_mu2",                    p_sig_5_temp_11);//mu in the Lambda rest frame after 4C_2
        status = m_tuple11->addItem ("p_sig_mu3",                    p_sig_6_temp_11);//mu in the Lambda rest frame only reco
        status = m_tuple11->addItem ("p_sig_p2",                     p_sig_7_temp_11);//proton in the Lambda rest frame only reco
        status = m_tuple11->addItem ("p_sig_mu4",                    p_sig_8_temp_11);//muon in the pion rest frame only reco
        status = m_tuple11->addItem ("p_tag_p",                      p_tag_1_temp_11);//p
        status = m_tuple11->addItem ("p_tag_pi",                     p_tag_2_temp_11);//pi
 
        status = m_tuple11->addItem ("p_4c_p_sig",                   p_1_4c_temp_11);//p
        status = m_tuple11->addItem ("p_4c_mu_sig",                  p_2_4c_temp_11);//mu
        status = m_tuple11->addItem ("p_4c_p_tag",                   p_3_4c_temp_11);//p
        status = m_tuple11->addItem ("p_4c_pi_tag",                  p_4_4c_temp_11);//pi
                                                    
        status = m_tuple11->addItem ("c_tag_lam_theta",              p_theta_temp_11);//lambda
        status = m_tuple11->addItem ("c_sig_p_theta",                c_sig_1_temp_11);//p
        status = m_tuple11->addItem ("c_sig_mu_theta",               c_sig_2_temp_11);//mu
        status = m_tuple11->addItem ("c_tag_p_theta",                c_tag_1_temp_11);//p
        status = m_tuple11->addItem ("c_tag_pi_theta",               c_tag_2_temp_11);//pi

        status = m_tuple11->addItem ("phi_tag_lam",                  p_phi_temp_11);//lambda
        status = m_tuple11->addItem ("phi_1",                        m_phi_1_11);//p
        status = m_tuple11->addItem ("phi_2",                        m_phi_2_11);//mu
        status = m_tuple11->addItem ("phi_3",                        m_phi_3_11);//p
        status = m_tuple11->addItem ("phi_4",                        m_phi_4_11);//pi

        status = m_tuple11->addItem ("lam_tag_chi",                  lam_tag_chi_temp_11);
        status = m_tuple11->addItem ("lam_tag_len",                  lam_tag_len_temp_11);
        status = m_tuple11->addItem ("lam_tag_lenerr",               lam_tag_lenerr_temp_11);
        status = m_tuple11->addItem ("lam_sig_chi",                  lam_sig_chi_temp_11);
        status = m_tuple11->addItem ("lam_sig_len",                  lam_sig_len_temp_11);
        status = m_tuple11->addItem ("lam_sig_lenerr",               lam_sig_lenerr_temp_11);
                                                        
        status = m_tuple11->addItem ("ngoodtrk",                     m_ngoodtrk_11);
        status = m_tuple11->addItem ("ngoodgam",                     m_ngoodgam_11);
        status = m_tuple11->addItem ("nchartrk",                     m_nchartrk_11);
        status = m_tuple11->addItem ("Ncharge_ex",                   Ncharge_ex_temp_11);
        status = m_tuple11->addItem ("gam_emax",                     gam_emax_temp_11);
        status = m_tuple11->addItem ("gam_e",                        gam_e_temp_11);
        status = m_tuple11->addItem ("ene_gam_sigma0_1",             ene_gam_sigma0_1_temp_11);// in the tag_sigma0 rest frame
        status = m_tuple11->addItem ("ene_gam_sigma0_2",             ene_gam_sigma0_2_temp_11);// in the sig_sigma0 rest frame
        status = m_tuple11->addItem ("chi_4c",                       kmfit_chi_temp_11);
        status = m_tuple11->addItem ("chi_4c_2",                     kmfit_chi_2_temp_11);

        status = m_tuple11->addItem ("angle1",                       angle1_temp_11);//p
        status = m_tuple11->addItem ("angle2",                       angle2_temp_11);//mu
        status = m_tuple11->addItem ("T_angle1",                     T_angle1_temp_11);//p
        status = m_tuple11->addItem ("T_angle2",                     T_angle2_temp_11);//pi

        status = m_tuple11->addItem ("index",                        index_temp_11,0, 100);
        status = m_tuple11->addIndexedItem ("V4_1",                  index_temp_11,  V4_1_temp_11);//p
        status = m_tuple11->addIndexedItem ("V4_2",                  index_temp_11,  V4_2_temp_11);//mu
        status = m_tuple11->addIndexedItem ("V4_3",                  index_temp_11,  V4_3_temp_11);//p
        status = m_tuple11->addIndexedItem ("V4_4",                  index_temp_11,  V4_4_temp_11);//pi
        status = m_tuple11->addIndexedItem ("V4_4c_1",               index_temp_11,  V4_4c_1_temp_11);//p
        status = m_tuple11->addIndexedItem ("V4_4c_2",               index_temp_11,  V4_4c_2_temp_11);//mu
        status = m_tuple11->addIndexedItem ("V4_4c_3",               index_temp_11,  V4_4c_3_temp_11);//p
        status = m_tuple11->addIndexedItem ("V4_4c_4",               index_temp_11,  V4_4c_4_temp_11);//pi

        //vertex distance (1 2 3 4;p mu p pi)
        status = m_tuple11->addItem ("vxy_1",       m_vxy_1_11);
        status = m_tuple11->addItem ("vxy_2",       m_vxy_2_11);
        status = m_tuple11->addItem ("vxy_3",       m_vxy_3_11);
        status = m_tuple11->addItem ("vxy_4",       m_vxy_4_11);
        status = m_tuple11->addItem ("vz_1",        m_vz_1_11);
        status = m_tuple11->addItem ("vz_2",        m_vz_2_11);
        status = m_tuple11->addItem ("vz_3",        m_vz_3_11);
        status = m_tuple11->addItem ("vz_4",        m_vz_4_11);

        //PID information (1 2 3 4;p mu p pi)
        status = m_tuple11->addItem ("probe_1",       m_probe_1_11);
        status = m_tuple11->addItem ("probe_2",       m_probe_2_11);
        status = m_tuple11->addItem ("probe_3",       m_probe_3_11);
        status = m_tuple11->addItem ("probe_4",       m_probe_4_11);
        status = m_tuple11->addItem ("probmu_1",      m_probmu_1_11);
        status = m_tuple11->addItem ("probmu_2",      m_probmu_2_11);
        status = m_tuple11->addItem ("probmu_3",      m_probmu_3_11);
        status = m_tuple11->addItem ("probmu_4",      m_probmu_4_11);
        status = m_tuple11->addItem ("probpi_1",      m_probpi_1_11);
        status = m_tuple11->addItem ("probpi_2",      m_probpi_2_11);
        status = m_tuple11->addItem ("probpi_3",      m_probpi_3_11);
        status = m_tuple11->addItem ("probpi_4",      m_probpi_4_11);
        status = m_tuple11->addItem ("probk_1",       m_probk_1_11);
        status = m_tuple11->addItem ("probk_2",       m_probk_2_11);
        status = m_tuple11->addItem ("probk_3",       m_probk_3_11);
        status = m_tuple11->addItem ("probk_4",       m_probk_4_11);
        status = m_tuple11->addItem ("probp_1",       m_probp_1_11);
        status = m_tuple11->addItem ("probp_2",       m_probp_2_11);
        status = m_tuple11->addItem ("probp_3",       m_probp_3_11);
        status = m_tuple11->addItem ("probp_4",       m_probp_4_11);

        //TOF information (1 2 3 4;p mu p pi)
        status = m_tuple11->addItem ("fgtof_1",       m_fgtof_1_11);
        status = m_tuple11->addItem ("counter_1",     m_counter_1_11);
        status = m_tuple11->addItem ("isbarrel_1",    m_isbarrel_1_11);
        status = m_tuple11->addItem ("layertof_1",    m_layertof_1_11);
        status = m_tuple11->addItem ("iscluster_1",   m_iscluster_1_11);
        status = m_tuple11->addItem ("tof_1",         m_tof_1_11);
        status = m_tuple11->addItem ("texe_1",        m_texe_1_11);
        status = m_tuple11->addItem ("texmu_1",       m_texmu_1_11);
        status = m_tuple11->addItem ("texpi_1",       m_texpi_1_11);
        status = m_tuple11->addItem ("texk_1",        m_texk_1_11);
        status = m_tuple11->addItem ("texp_1",        m_texp_1_11);
        status = m_tuple11->addItem ("dte_1",         m_dte_1_11);
        status = m_tuple11->addItem ("dtmu_1",        m_dtmu_1_11);
        status = m_tuple11->addItem ("dtpi_1",        m_dtpi_1_11);
        status = m_tuple11->addItem ("dtk_1",         m_dtk_1_11);
        status = m_tuple11->addItem ("dtp_1",         m_dtp_1_11);

        status = m_tuple11->addItem ("fgtof_2",       m_fgtof_2_11);
        status = m_tuple11->addItem ("counter_2",     m_counter_2_11);
        status = m_tuple11->addItem ("isbarrel_2",    m_isbarrel_2_11);
        status = m_tuple11->addItem ("layertof_2",    m_layertof_2_11);
        status = m_tuple11->addItem ("iscluster_2",   m_iscluster_2_11);
        status = m_tuple11->addItem ("tof_2",         m_tof_2_11);
        status = m_tuple11->addItem ("texe_2",        m_texe_2_11);
        status = m_tuple11->addItem ("texmu_2",       m_texmu_2_11);
        status = m_tuple11->addItem ("texpi_2",       m_texpi_2_11);
        status = m_tuple11->addItem ("texk_2",        m_texk_2_11);
        status = m_tuple11->addItem ("texp_2",        m_texp_2_11);
        status = m_tuple11->addItem ("dte_2",         m_dte_2_11);
        status = m_tuple11->addItem ("dtmu_2",        m_dtmu_2_11);
        status = m_tuple11->addItem ("dtpi_2",        m_dtpi_2_11);
        status = m_tuple11->addItem ("dtk_2",         m_dtk_2_11);
        status = m_tuple11->addItem ("dtp_2",         m_dtp_2_11);

        status = m_tuple11->addItem ("fgtof_3",       m_fgtof_3_11);
        status = m_tuple11->addItem ("counter_3",     m_counter_3_11);
        status = m_tuple11->addItem ("isbarrel_3",    m_isbarrel_3_11);
        status = m_tuple11->addItem ("layertof_3",    m_layertof_3_11);
        status = m_tuple11->addItem ("iscluster_3",   m_iscluster_3_11);
        status = m_tuple11->addItem ("tof_3",         m_tof_3_11);
        status = m_tuple11->addItem ("texe_3",        m_texe_3_11);
        status = m_tuple11->addItem ("texmu_3",       m_texmu_3_11);
        status = m_tuple11->addItem ("texpi_3",       m_texpi_3_11);
        status = m_tuple11->addItem ("texk_3",        m_texk_3_11);
        status = m_tuple11->addItem ("texp_3",        m_texp_3_11);
        status = m_tuple11->addItem ("dte_3",         m_dte_3_11);
        status = m_tuple11->addItem ("dtmu_3",        m_dtmu_3_11);
        status = m_tuple11->addItem ("dtpi_3",        m_dtpi_3_11);
        status = m_tuple11->addItem ("dtk_3",         m_dtk_3_11);
        status = m_tuple11->addItem ("dtp_3",         m_dtp_3_11);

        status = m_tuple11->addItem ("fgtof_4",       m_fgtof_4_11);
        status = m_tuple11->addItem ("counter_4",     m_counter_4_11);
        status = m_tuple11->addItem ("isbarrel_4",    m_isbarrel_4_11);
        status = m_tuple11->addItem ("layertof_4",    m_layertof_4_11);
        status = m_tuple11->addItem ("iscluster_4",   m_iscluster_4_11);
        status = m_tuple11->addItem ("tof_4",         m_tof_4_11);
        status = m_tuple11->addItem ("texe_4",        m_texe_4_11);
        status = m_tuple11->addItem ("texmu_4",       m_texmu_4_11);
        status = m_tuple11->addItem ("texpi_4",       m_texpi_4_11);
        status = m_tuple11->addItem ("texk_4",        m_texk_4_11);
        status = m_tuple11->addItem ("texp_4",        m_texp_4_11);
        status = m_tuple11->addItem ("dte_4",         m_dte_4_11);
        status = m_tuple11->addItem ("dtmu_4",        m_dtmu_4_11);
        status = m_tuple11->addItem ("dtpi_4",        m_dtpi_4_11);
        status = m_tuple11->addItem ("dtk_4",         m_dtk_4_11);
        status = m_tuple11->addItem ("dtp_4",         m_dtp_4_11);

        //dedx information (1 2 3 4;p mu p pi)
        status = m_tuple11->addItem ("chi_e_1",       m_chi_e_1_11);
        status = m_tuple11->addItem ("chi_mu_1",      m_chi_mu_1_11);
        status = m_tuple11->addItem ("chi_pi_1",      m_chi_pi_1_11);
        status = m_tuple11->addItem ("chi_k_1",       m_chi_k_1_11);
        status = m_tuple11->addItem ("chi_p_1",       m_chi_p_1_11);

        status = m_tuple11->addItem ("chi_e_2",       m_chi_e_2_11);
        status = m_tuple11->addItem ("chi_mu_2",      m_chi_mu_2_11);
        status = m_tuple11->addItem ("chi_pi_2",      m_chi_pi_2_11);
        status = m_tuple11->addItem ("chi_k_2",       m_chi_k_2_11);
        status = m_tuple11->addItem ("chi_p_2",       m_chi_p_2_11);

        status = m_tuple11->addItem ("chi_e_3",       m_chi_e_3_11);
        status = m_tuple11->addItem ("chi_mu_3",      m_chi_mu_3_11);
        status = m_tuple11->addItem ("chi_pi_3",      m_chi_pi_3_11);
        status = m_tuple11->addItem ("chi_k_3",       m_chi_k_3_11);
        status = m_tuple11->addItem ("chi_p_3",       m_chi_p_3_11);

        status = m_tuple11->addItem ("chi_e_4",       m_chi_e_4_11);
        status = m_tuple11->addItem ("chi_mu_4",      m_chi_mu_4_11);
        status = m_tuple11->addItem ("chi_pi_4",      m_chi_pi_4_11);
        status = m_tuple11->addItem ("chi_k_4",       m_chi_k_4_11);
        status = m_tuple11->addItem ("chi_p_4",       m_chi_p_4_11);

	//MUC information (only for signal-side muon)
	status = m_tuple11->addItem("maxhitsinlay_1", m_maxhitsinlay_2_11);
	status = m_tuple11->addItem("numhits_1",      m_numhits_2_11);
	status = m_tuple11->addItem("numlayers_1",    m_numlayers_2_11);
	status = m_tuple11->addItem("depth_1",        m_depth_2_11);
	status = m_tuple11->addItem("mucchi2_1",      m_mucchi2_2_11);

	status = m_tuple11->addItem ("indexmc",                      topo_temp_11,0, 500);
        status = m_tuple11->addIndexedItem ("pdgid",                 topo_temp_11,  pdgid_temp_11);
        status = m_tuple11->addIndexedItem ("motheridx",             topo_temp_11,  mcidx_temp_11);

     }                                                               
      else    {                                                      
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple11) << endmsg;
        return StatusCode::FAILURE;                                  
      }
    }



  NTuplePtr ntb(ntupleSvc(), "FILE1/truth");
    if ( ntb ) m_tupleb = ntb;
    else {
     m_tupleb = ntupleSvc()->book ("FILE1/truth", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tupleb)     {
          //0 from lambda      1 from anti-lambda
        status = m_tupleb->addItem ("lam_DIF_0", lam_DIF_0_temp_b);
        status = m_tupleb->addItem ("lam_DFG_0", lam_DFG_0_temp_b);
        status = m_tupleb->addItem ("lam_DIF_1", lam_DIF_1_temp_b);
        status = m_tupleb->addItem ("lam_DFG_1", lam_DFG_1_temp_b);

        status = m_tupleb->addItem ("lam_leafP_0",  lam_leafP_0_temp_b);
        status = m_tupleb->addItem ("lam_vertex_0", lam_vertex_0_temp_b);
        status = m_tupleb->addItem ("lam_leafP_1",  lam_leafP_1_temp_b);
        status = m_tupleb->addItem ("lam_vertex_1", lam_vertex_1_temp_b);

	status = m_tupleb->addItem ("p_DIF_0",   p_DIF_0_temp_b);
	status = m_tupleb->addItem ("p_DFG_0",   p_DFG_0_temp_b);
	status = m_tupleb->addItem ("p_DIF_1",   p_DIF_1_temp_b);
	status = m_tupleb->addItem ("p_DFG_1",   p_DFG_1_temp_b);

        status = m_tupleb->addItem ("p_leafP_0",  p_leafP_0_temp_b);
        status = m_tupleb->addItem ("p_vertex_0", p_vertex_0_temp_b);
        status = m_tupleb->addItem ("p_leafP_1",  p_leafP_1_temp_b);
        status = m_tupleb->addItem ("p_vertex_1", p_vertex_1_temp_b);

	status = m_tupleb->addItem ("pi_DIF_0", pi_DIF_0_temp_b);
	status = m_tupleb->addItem ("pi_DFG_0", pi_DFG_0_temp_b);
	status = m_tupleb->addItem ("pi_DIF_1", pi_DIF_1_temp_b);
	status = m_tupleb->addItem ("pi_DFG_1", pi_DFG_1_temp_b);

        status = m_tupleb->addItem ("pi_leafP_0",  pi_leafP_0_temp_b);
        status = m_tupleb->addItem ("pi_vertex_0", pi_vertex_0_temp_b);
        status = m_tupleb->addItem ("pi_leafP_1",  pi_leafP_1_temp_b);
        status = m_tupleb->addItem ("pi_vertex_1", pi_vertex_1_temp_b);

	status = m_tupleb->addItem ("mu_DIF_0", mu_DIF_0_temp_b);
	status = m_tupleb->addItem ("mu_DFG_0", mu_DFG_0_temp_b);
	status = m_tupleb->addItem ("mu_DIF_1", mu_DIF_1_temp_b);
	status = m_tupleb->addItem ("mu_DFG_1", mu_DFG_1_temp_b);

        status = m_tupleb->addItem ("mu_leafP_0",  mu_leafP_0_temp_b);
        status = m_tupleb->addItem ("mu_vertex_0", mu_vertex_0_temp_b);
        status = m_tupleb->addItem ("mu_leafP_1",  mu_leafP_1_temp_b);
        status = m_tupleb->addItem ("mu_vertex_1", mu_vertex_1_temp_b);

        status = m_tupleb->addItem ("P_1_0", p_1_0_temp_b);//lam
        status = m_tupleb->addItem ("P_2_0", p_2_0_temp_b);//p
        status = m_tupleb->addItem ("P_3_0", p_3_0_temp_b);//mu
        status = m_tupleb->addItem ("P_4_0", p_4_0_temp_b);//nu
        status = m_tupleb->addItem ("P_5_0", p_5_0_temp_b);//pi

        status = m_tupleb->addItem ("P_1_1", p_1_1_temp_b);//lam
        status = m_tupleb->addItem ("P_2_1", p_2_1_temp_b);//p
        status = m_tupleb->addItem ("P_3_1", p_3_1_temp_b);//mu
        status = m_tupleb->addItem ("P_4_1", p_4_1_temp_b);//nu
        status = m_tupleb->addItem ("P_5_1", p_5_1_temp_b);//pi

        status = m_tupleb->addItem ("index",           index_temp_b,0, 100);
        status = m_tupleb->addIndexedItem ("V4_1_0",     index_temp_b,  V4_1_0_temp_b);//lam
        status = m_tupleb->addIndexedItem ("V4_2_0",     index_temp_b,  V4_2_0_temp_b);//p
        status = m_tupleb->addIndexedItem ("V4_3_0",     index_temp_b,  V4_3_0_temp_b);//mu
        status = m_tupleb->addIndexedItem ("V4_4_0",     index_temp_b,  V4_4_0_temp_b);//nu
        status = m_tupleb->addIndexedItem ("V4_5_0",     index_temp_b,  V4_5_0_temp_b);//pi

        status = m_tupleb->addIndexedItem ("V4_1_1",     index_temp_b,  V4_1_1_temp_b);//lam
        status = m_tupleb->addIndexedItem ("V4_2_1",     index_temp_b,  V4_2_1_temp_b);//p
        status = m_tupleb->addIndexedItem ("V4_3_1",     index_temp_b,  V4_3_1_temp_b);//mu
        status = m_tupleb->addIndexedItem ("V4_4_1",     index_temp_b,  V4_4_1_temp_b);//nu
        status = m_tupleb->addIndexedItem ("V4_5_1",     index_temp_b,  V4_5_1_temp_b);//pi

        status = m_tupleb->addItem ("C_1_0", c_1_0_temp_b);//lam
        status = m_tupleb->addItem ("C_2_0", c_2_0_temp_b);//p
        status = m_tupleb->addItem ("C_3_0", c_3_0_temp_b);//mu
        status = m_tupleb->addItem ("C_4_0", c_4_0_temp_b);//nu
        status = m_tupleb->addItem ("C_5_0", c_5_0_temp_b);//pi

        status = m_tupleb->addItem ("C_1_1", c_1_1_temp_b);//lam
        status = m_tupleb->addItem ("C_2_1", c_2_1_temp_b);//p
        status = m_tupleb->addItem ("C_3_1", c_3_1_temp_b);//mu
        status = m_tupleb->addItem ("C_4_1", c_4_1_temp_b);//nu
        status = m_tupleb->addItem ("C_5_1", c_5_1_temp_b);//pi

        status = m_tupleb->addItem ("event",   event_temp_b  );
        status = m_tupleb->addItem ("runNo",   run_temp_b  );
        status = m_tupleb->addItem ("mcmodea", mcmodea_temp_b  );
        status = m_tupleb->addItem ("mcmodeb", mcmodeb_temp_b  );
        status = m_tupleb->addItem ("mcmode1", mcmode1_temp_b  );
        status = m_tupleb->addItem ("mcmode2", mcmode2_temp_b  );
        status = m_tupleb->addItem ("mctag",       mctag_temp_b);

        status = m_tupleb->addItem ("indexmc",            topo_temp_00,0, 500);
        status = m_tupleb->addIndexedItem ("pdgid",       topo_temp_00,  pdgid_temp_00);
        status = m_tupleb->addIndexedItem ("motheridx",   topo_temp_00,  mcidx_temp_00);

       }
      else    {
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tupleb) << endmsg;
        return StatusCode::FAILURE;
      }
    }





////////////////////////////////////////////////
  NTuplePtr nta(ntupleSvc(), "FILE1/modenum");
    if ( nta ) m_tuplea = nta;
    else {
     m_tuplea = ntupleSvc()->book ("FILE1/modenum", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tuplea)     {
        status = m_tuplea->addItem ("mdbc1", m1_mdbc1  );
        status = m_tuplea->addItem ("mdbc2", m1_mdbc2  );
        status = m_tuplea->addItem ("event", m1_irec );
        status = m_tuplea->addItem ("runNo", m1_irun );
        status = m_tuplea->addItem ("mcmode1", m1_mcmode1);
        status = m_tuplea->addItem ("mcmode2", m1_mcmode2);
        status = m_tuplea->addItem ("mcmodea", m1_mcmodea);
        status = m_tuplea->addItem ("mcmodeb", m1_mcmodeb);
        status = m_tuplea->addItem ("mctag",       m1_mctag);

       }
      else    {
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuplea) << endmsg;
        return StatusCode::FAILURE;
      }
    }


  //--------end of book--------

  //

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;

}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode pmu::execute() {
  MsgStream log(msgSvc(), name());

  log << MSG::INFO << "in execute()" << endreq;

  SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
  int runNo=eventHeader->runNumber();
  int event=eventHeader->eventNumber();
  tot_events++;
  log << MSG::DEBUG <<"run, evtnum = "
      << runNo << " , "
      << event <<endreq;
 if(0 == (tot_events % 100))
	  std::cout << "Run num : " << runNo << ",  Event " << tot_events
		  << ",   Event number online " << event << endl;
//double ecm;
  Ecmset*  ECMSET = Ecmset::instance();
  int  run = abs(runNo);
  ECMSET->EcmSet(run);
//  ecm = ECMSET->ECM();
/////////////
      HepLorentzVector ecms(ecm*0.011,0,0,ecm);
/////////////////
  SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
    log << MSG::DEBUG <<"ncharg, nneu, tottks = "
      << evtRecEvent->totalCharged() << " , "
      << evtRecEvent->totalNeutral() << " , "
      << evtRecEvent->totalTracks() <<endreq;

  int mcmode1=0,mcmode2=0;  int mcmodea=0,mcmodeb=0;
  double pd1 = 0., pd2 = 0., mdbc1 = 0., mdbc2 = 0.;

  Vp4 PD1,PK1,Ptrk1; int charged1=0; Vint IDtrk1;
  Vp4 PD2,PK2,Ptrk2; int charged2=0; Vint IDtrk2;
  Vp4 PDa,PKa,Ptrka; int chargeda=0; Vint IDtrka;
  Vp4 PDb,PKb,Ptrkb; int chargedb=0; Vint IDtrkb;

if(runNo<0) {
   SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
   if(!mcParticleCol)            return StatusCode::FAILURE;

   Vint mdtg11,mdtg12,mdtg21,mdtg22;
   mdtg11.clear(); mdtg12.clear(); mdtg21.clear(); mdtg22.clear();

   Vp4 PD11,PK11,Ptrk11; int charged11=0; Vint IDtrk11;
   Vp4 PD12,PK12,Ptrk12; int charged12=0; Vint IDtrk12;
   Vp4 PD21,PK21,Ptrk21; int charged21=0; Vint IDtrk21;
   Vp4 PD22,PK22,Ptrk22; int charged22=0; Vint IDtrk22;

   DDmcmode* readmode11 = DDmcmode::instance();
   readmode11->D0mcmode(mcParticleCol);
   mdtg11    = readmode11->mcmode();
   PD11      = readmode11->p4d();
   PK11      = readmode11->p4k();
   IDtrk11   = readmode11->idtk();
   Ptrk11    = readmode11->ptk();
   charged11 = readmode11->chargd();
   DDmcmode* readmode12 = DDmcmode::instance();
   readmode12->D0bmcmode(mcParticleCol);
   mdtg12    = readmode12->mcmode();
   PD12      = readmode12->p4d();
   PK12      = readmode12->p4k();
   IDtrk12   = readmode12->idtk();
   Ptrk12    = readmode12->ptk();
   charged12 = readmode12->chargd();

   DDmcmode* readmode21 = DDmcmode::instance();
   readmode21->Dpmcmode(mcParticleCol);
   mdtg21    = readmode21->mcmode();
   PD21      = readmode21->p4d();
   PK21      = readmode21->p4k();
   IDtrk21   = readmode21->idtk();
   charged21 = readmode21->chargd();

   DDmcmode* readmode22 = DDmcmode::instance();
   readmode22->Dnmcmode(mcParticleCol);
   mdtg22    = readmode22->mcmode();
   PD22      = readmode22->p4d();
   PK22      = readmode22->p4k();
   IDtrk22   = readmode22->idtk();
   charged22 = readmode22->chargd();

   if(mdtg11.size()>=1) {
     mcmode1=mdtg11[0];mcmode2=mdtg12[0];
     PD1    = PD11;
     PK1    = PK11;
     IDtrk1 = IDtrk11;
     Ptrk1  = Ptrk11;
     PD2    = PD12;
     PK2    = PK12;
     IDtrk2 = IDtrk12;
     Ptrk2  = Ptrk12;
   }

   if(mdtg21.size()>=1) {
     mcmode1=mdtg21[0];mcmode2=mdtg22[0];
     PD1    = PD21;
     PK1    = PK21;
     IDtrk1 = IDtrk21;
     Ptrk1  = Ptrk21;
     PD2    = PD22;
     PK2    = PK22;
     IDtrk2 = IDtrk22;
     Ptrk2  = Ptrk22;
   }

   int mdtg1a=9999,mdtg1b=9999,mdtg2a=9999,mdtg2b=9999;
   Vp4 PD1a,PK1a,Ptrk1a; int charged1a=0; Vint IDtrk1a;
   Vp4 PD1b,PK1b,Ptrk1b; int charged1b=0; Vint IDtrk1b;
   Vp4 PD2a,PK2a,Ptrk2a; int charged2a=0; Vint IDtrk2a;
   Vp4 PD2b,PK2b,Ptrk2b; int charged2b=0; Vint IDtrk2b;

   DDmcmode* readmode1a = DDmcmode::instance();
   readmode1a->D0mcmodeF(mcParticleCol);
   mdtg1a    = readmode1a->mcmodef();
   PD1a      = readmode1a->p4d();
   PK1a      = readmode1a->p4k();
   IDtrk1a   = readmode1a->idtk();
   Ptrk1a    = readmode1a->ptk();
   charged1a = readmode1a->chargd();

   DDmcmode* readmode1b = DDmcmode::instance();
   readmode1b->D0bmcmodeF(mcParticleCol);
   mdtg1b    = readmode1b->mcmodef();
   PD1b      = readmode1b->p4d();
   PK1b      = readmode1b->p4k();
   IDtrk1b   = readmode1b->idtk();
   Ptrk1b    = readmode1b->ptk();
   charged1b = readmode1b->chargd();

   DDmcmode* readmode2a = DDmcmode::instance();
   readmode2a->DpmcmodeF(mcParticleCol);
   mdtg2a    = readmode2a->mcmodef();
   PD2a      = readmode2a->p4d();
   IDtrk2a   = readmode2a->idtk();
   Ptrk2a    = readmode2a->ptk();
   charged2a = readmode2a->chargd();

   DDmcmode* readmode2b = DDmcmode::instance();
   readmode2b->DnmcmodeF(mcParticleCol);
   mdtg2b    = readmode2b->mcmodef();
   PD2b      = readmode2b->p4d();
   IDtrk2b   = readmode2b->idtk();
   Ptrk2b    = readmode2b->ptk();
   charged2b = readmode2b->chargd();


   if(mdtg1a>0) {
     mcmodea=mdtg1a;mcmodeb=mdtg1b;
     PDa    = PD1a;
     PKa    = PK1a;
     IDtrka = IDtrk1a;
     Ptrka  = Ptrk1a;
     PDb    = PD1b;
     PKb    = PK1b;
     IDtrkb = IDtrk1b;
     Ptrkb  = Ptrk1b;
   }

   if(mdtg2a>0) {
     mcmodea=mdtg2a;mcmodeb=mdtg2b;
     PDa    = PD2a;
     PKa    = PK2a;
     IDtrka = IDtrk2a;
     Ptrka  = Ptrk2a;
     PDb    = PD2b;
     PKb    = PK2b;
     IDtrkb = IDtrk2b;
     Ptrkb  = Ptrk2b;
   }


  if(PD1.size()>=1&&PD2.size()>=1) {

    HepLorentzVector P4d1 = PD1[0].boost(-0.011,0,0);

    HepLorentzVector P4d2 = PD2[0].boost(-0.011,0,0);


    pd1 = P4d1.rho();

    pd2 = P4d2.rho();

///////////////////test
//    double xm1 =  (ecm/2.)- P4d1.e();
//   
//    double xm2 =  (ecm/2.)- P4d2.e();
//    mdbc1=xm1;
//    mdbc2=xm2;
///////////////////

    double xm1 =  (ecm/2.)*(ecm/2.)- pd1*pd1;

    double xm2 =  (ecm/2.)*(ecm/2.)- pd2*pd2;

    if(xm1<0) xm1 = 0.;

    if(xm2<0) xm2 = 0.;

    mdbc1 = sqrt(xm1);

    mdbc2 = sqrt(xm2);
  }

}
m1_irec=event;
m1_irun=runNo;
m1_mdbc1=mdbc1;
m1_mdbc2=mdbc2;
m1_mcmode1=mcmode1;
m1_mcmode2=mcmode2;
m1_mcmodea=mcmodea;
m1_mcmodeb=mcmodeb;

m1_mctag=m_mctag;
   m_tuplea->write();

  DTagTool trk;
  bool cosmic_ok = trk.cosmicandleptonVeto();

///////////////////////////////////////////////topology
int numParticle;
int vpdgid[500], vmotheridx[500];
numParticle = 0;
if(runNo<0) {
   SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
   if(!mcParticleCol)            return StatusCode::FAILURE;

if (!mcParticleCol) {
std::cout << "Could not retrieve McParticleCol" << std::endl;
return StatusCode::FAILURE;
}
 else {
bool Decay = false;
int rootIndex = -1;
int motherid;
int pidx = 999;
Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
for (; iter_mc != mcParticleCol->end(); iter_mc++) {
//pidx = (*iter_mc)->trackIndex();
if (Decay&&(*iter_mc)->primaryParticle()) pidx = (*iter_mc)->trackIndex();
if ((*iter_mc)->primaryParticle()) continue;
if (!(*iter_mc)->decayFromGenerator()) continue;
if ((*iter_mc)->particleProperty()==30443) {
Decay = true;
rootIndex = (*iter_mc)->trackIndex();
motherid = (*iter_mc)->particleProperty();
numParticle = 0;
}
if (!Decay&&((*iter_mc)->mother().particleProperty()==443||(*iter_mc)->mother().particleProperty()==100443)&&motherid!=30443) {
Decay = true;
motherid = (*iter_mc)->mother().particleProperty();
rootIndex = (*iter_mc)->mother().trackIndex();
vpdgid[0] = motherid;
vmotheridx[0] = -1;
numParticle++;
}
if (!Decay) continue;
int mcidx;
if (motherid==30443||motherid==443||motherid==100443) {
mcidx = (((*iter_mc)->mother()).particleProperty()==motherid) ? 0 : ((*iter_mc)->mother()).trackIndex() - rootIndex - 1;
}
else {
mcidx = ((*iter_mc)->mother()).trackIndex()>pidx ? ((*iter_mc)->mother()).trackIndex() - rootIndex - 1 : ((*iter_mc)->mother()).trackIndex() - rootIndex;
}
int pdgid = (*iter_mc)->particleProperty();
vpdgid[numParticle] = pdgid;
vmotheridx[numParticle] = mcidx;
numParticle++;
}
}

}
//////////////////////////////////////////////////////


///////////////////  TRUTH or NO TRUTH ///
HepLorentzVector P4_D,P4_Db;
Vp4   P4_D1_1,          P4_D1_2,          P4_D1_3,          P4_D1_4,          
      P4_D1_5,          P4_D1_6,          P4_D1_7,          P4_D1_8; 
      P4_D1_1.clear();  P4_D1_2.clear();  P4_D1_3.clear();  P4_D1_4.clear();  
      P4_D1_5.clear();  P4_D1_6.clear();  P4_D1_7.clear();  P4_D1_8.clear();
Vp4   P4_D1b_1,          P4_D1b_2,          P4_D1b_3,          P4_D1b_4,          
      P4_D1b_5,          P4_D1b_6,          P4_D1b_7,          P4_D1b_8; 
      P4_D1b_1.clear();  P4_D1b_2.clear();  P4_D1b_3.clear();  P4_D1b_4.clear();  
      P4_D1b_5.clear();  P4_D1b_6.clear();  P4_D1b_7.clear();  P4_D1b_8.clear();

Vp4 T4_sigma_lam,T4_sigma_e,T4_sigma_nu_e,T4_sigma_p,T4_sigma_pi0,T4_sigma_pi;
T4_sigma_lam.clear();  T4_sigma_e.clear();  T4_sigma_nu_e.clear();  T4_sigma_p.clear();  T4_sigma_pi0.clear();  T4_sigma_pi.clear();
Vp4 T4_antisigma_lam,T4_antisigma_e,T4_antisigma_nu_e,T4_antisigma_p,T4_antisigma_pi0,T4_antisigma_pi;
T4_antisigma_lam.clear(); T4_antisigma_e.clear(); T4_antisigma_nu_e.clear(); T4_antisigma_p.clear(); T4_antisigma_pi0.clear(); T4_antisigma_pi.clear();

Vp4 T4_lambda;             T4_lambda.clear();
Vp4 T4_lambda_p;           T4_lambda_p.clear();
Vp4 T4_lambda_pi;          T4_lambda_pi.clear();
Vp4 T4_lambda_mu;          T4_lambda_mu.clear();
Vp4 T4_lambda_nu_mu;       T4_lambda_nu_mu.clear();

Vp4 T4_anti_lambda;        T4_anti_lambda.clear();
Vp4 T4_anti_lambda_p;      T4_anti_lambda_p.clear();
Vp4 T4_anti_lambda_pi;     T4_anti_lambda_pi.clear();
Vp4 T4_anti_lambda_mu;     T4_anti_lambda_mu.clear();
Vp4 T4_anti_lambda_nu_mu;  T4_anti_lambda_nu_mu.clear();

      index_temp_b=4;
if(runNo<0) {
   SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
   if(!mcParticleCol)            return StatusCode::FAILURE;

  if(mcParticleCol){
    Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();

    for (; iter_mc != mcParticleCol->end(); iter_mc++){
      if ((*iter_mc)->primaryParticle())                                   continue;
//      if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int p_mid= ((*iter_mc)->mother()).particleProperty();
      int p_m2id=(((*iter_mc)->mother()).mother()).particleProperty();
      int p_m3id=((((*iter_mc)->mother()).mother()).mother()).particleProperty();
      int p_m4id=(((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty();
      int p_m5id=((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty();
/////////////////////////////Lambda0
if(pdgid==3122||p_mid==3122||p_m2id==3122||p_m3id==3122||p_m4id==3122||p_m5id==3122){//Lambda0 3122
if(pdgid==3122){//Lambda0 3122
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
	      P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      lam_DIF_0_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) lam_DFG_0_temp_b=1;
	      if((*iter_mc)->leafParticle())       lam_leafP_0_temp_b=1;
 	      lam_vertex_0_temp_b=(*iter_mc)->vertexIndex0();

 p_1_0_temp_b=P4_1.rho();
 c_1_0_temp_b=P4_1.cosTheta();
V4_1_0_temp_b[0]=P4_1.px();
V4_1_0_temp_b[1]=P4_1.py();
V4_1_0_temp_b[2]=P4_1.pz();
V4_1_0_temp_b[3]=P4_1.e();

T4_lambda.push_back(P4_1);
 }
if(pdgid==2212){//proton+ 2212
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      p_DIF_0_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) p_DFG_0_temp_b=1;
	      if((*iter_mc)->leafParticle())       p_leafP_0_temp_b=1;
 	      p_vertex_0_temp_b=(*iter_mc)->vertexIndex0();

 p_2_0_temp_b=P4_1.rho();
 c_2_0_temp_b=P4_1.cosTheta();
V4_2_0_temp_b[0]=P4_1.px();
V4_2_0_temp_b[1]=P4_1.py();
V4_2_0_temp_b[2]=P4_1.pz();
V4_2_0_temp_b[3]=P4_1.e();

T4_lambda_p.push_back(P4_1);
 }
if(pdgid==13){//mu- 13
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      mu_DIF_0_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) mu_DFG_0_temp_b=1;
	      if((*iter_mc)->leafParticle())       mu_leafP_0_temp_b=1;
 	      mu_vertex_0_temp_b=(*iter_mc)->vertexIndex0();
	      if(p_mid==-211||p_mid==211) pimD2mu=1;

 p_3_0_temp_b=P4_1.rho();
 c_3_0_temp_b=P4_1.cosTheta();
V4_3_0_temp_b[0]=P4_1.px();
V4_3_0_temp_b[1]=P4_1.py();
V4_3_0_temp_b[2]=P4_1.pz();
V4_3_0_temp_b[3]=P4_1.e();

T4_lambda_mu.push_back(P4_1);
 }
if(pdgid==-14){//anti-nu_mu -14
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
 p_4_0_temp_b=P4_1.rho();
 c_4_0_temp_b=P4_1.cosTheta();
V4_4_0_temp_b[0]=P4_1.px();
V4_4_0_temp_b[1]=P4_1.py();
V4_4_0_temp_b[2]=P4_1.pz();
V4_4_0_temp_b[3]=P4_1.e();

T4_lambda_nu_mu.push_back(P4_1);
 }
if(pdgid==-211){//pi- -211
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      pi_DIF_0_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) pi_DFG_0_temp_b=1;
	      if((*iter_mc)->leafParticle())       pi_leafP_0_temp_b=1;
	      if(!((*iter_mc)->leafParticle()))    pimD=1;
 	      pi_vertex_0_temp_b=(*iter_mc)->vertexIndex0();

 p_5_0_temp_b=P4_1.rho();
 c_5_0_temp_b=P4_1.cosTheta();
V4_5_0_temp_b[0]=P4_1.px();
V4_5_0_temp_b[1]=P4_1.py();
V4_5_0_temp_b[2]=P4_1.pz();
V4_5_0_temp_b[3]=P4_1.e();

T4_lambda_pi.push_back(P4_1);
 }
}

/////////////////////////////anti-Lambda0
if(pdgid==-3122||p_mid==-3122||p_m2id==-3122||p_m3id==-3122||p_m4id==-3122||p_m5id==-3122){//anti-Lambda0 -3122
if(pdgid==-3122){//anti-Lambda0 -3122
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      lam_DIF_1_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) lam_DFG_1_temp_b=1;
	      if((*iter_mc)->leafParticle())       lam_leafP_1_temp_b=1;
 	      lam_vertex_1_temp_b=(*iter_mc)->vertexIndex0();

 p_1_1_temp_b=P4_1.rho();
 c_1_1_temp_b=P4_1.cosTheta();
V4_1_1_temp_b[0]=P4_1.px();
V4_1_1_temp_b[1]=P4_1.py();
V4_1_1_temp_b[2]=P4_1.pz();
V4_1_1_temp_b[3]=P4_1.e();

T4_anti_lambda.push_back(P4_1);
 }
if(pdgid==-2212){//anti-proton- -2212
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      p_DIF_1_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) p_DFG_1_temp_b=1;
	      if((*iter_mc)->leafParticle())       p_leafP_1_temp_b=1;
 	      p_vertex_1_temp_b=(*iter_mc)->vertexIndex0();

 p_2_1_temp_b=P4_1.rho();
 c_2_1_temp_b=P4_1.cosTheta();
V4_2_1_temp_b[0]=P4_1.px();
V4_2_1_temp_b[1]=P4_1.py();
V4_2_1_temp_b[2]=P4_1.pz();
V4_2_1_temp_b[3]=P4_1.e();

T4_anti_lambda_p.push_back(P4_1);
 }
if(pdgid==-13){//mu+ -13
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      mu_DIF_1_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) mu_DFG_1_temp_b=1;
	      if((*iter_mc)->leafParticle())       mu_leafP_1_temp_b=1;
 	      mu_vertex_1_temp_b=(*iter_mc)->vertexIndex0();
	      if(p_mid==211||p_mid==-211) pipD2mu=1;

 p_3_1_temp_b=P4_1.rho();
 c_3_1_temp_b=P4_1.cosTheta();
V4_3_1_temp_b[0]=P4_1.px();
V4_3_1_temp_b[1]=P4_1.py();
V4_3_1_temp_b[2]=P4_1.pz();
V4_3_1_temp_b[3]=P4_1.e();

T4_anti_lambda_mu.push_back(P4_1);
 }
if(pdgid==14){//nu_mu 14
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);

 p_4_1_temp_b=P4_1.rho();
 c_4_1_temp_b=P4_1.cosTheta();
V4_4_1_temp_b[0]=P4_1.px();
V4_4_1_temp_b[1]=P4_1.py();
V4_4_1_temp_b[2]=P4_1.pz();
V4_4_1_temp_b[3]=P4_1.e();

T4_anti_lambda_nu_mu.push_back(P4_1);
 }
if(pdgid==211){//pi+ 211
              HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                                P4_1.boost(-0.011,0,0);
	      if((*iter_mc)->decayInFlight())      pi_DIF_1_temp_b=1;//2020.07.18 check pion decay
	      if((*iter_mc)->decayFromGenerator()) pi_DFG_1_temp_b=1;
	      if((*iter_mc)->leafParticle())       pi_leafP_1_temp_b=1;
	      if(!((*iter_mc)->leafParticle()))    pipD=1;
 	      pi_vertex_1_temp_b=(*iter_mc)->vertexIndex0();

 p_5_1_temp_b=P4_1.rho();
 c_5_1_temp_b=P4_1.cosTheta();
V4_5_1_temp_b[0]=P4_1.px();
V4_5_1_temp_b[1]=P4_1.py();
V4_5_1_temp_b[2]=P4_1.pz();
V4_5_1_temp_b[3]=P4_1.e();

T4_anti_lambda_pi.push_back(P4_1);
 }
}

}////////    for (; iter_mc != mcParticleCol->end(); iter_mc++)
}////////  if(mcParticleCol)
event_temp_b=event;
run_temp_b=runNo;
mcmode1_temp_b=mcmode1;
mcmode2_temp_b=mcmode2;
mcmodea_temp_b=mcmodea;
mcmodeb_temp_b=mcmodeb;

mctag_temp_b=m_mctag;

topo_temp_00 = numParticle;
for(int i=0;i<numParticle;i++){
   pdgid_temp_00[i] = vpdgid[i];
   mcidx_temp_00[i] = vmotheridx[i];
}

m_tupleb->write();
}/////////   if(runNo<0)


Vdou    Ksolen;                Ksolen.clear();        Vdou    Eprob_pi;             Eprob_pi.clear(); 
Vdou    Trkprobk;              Trkprobk.clear();      Vdou    Kprob_pi;             Kprob_pi.clear();
Vdou    Trkprobpi;             Trkprobpi.clear();     Vdou    Muprob_pi;            Muprob_pi.clear(); 
Vdou    Pi0chi;                Pi0chi.clear();        Vdou    Eprob_k;              Eprob_k.clear();
Vdou    tag_mbc;               tag_mbc.clear();       Vdou    Piprob_k;             Piprob_k.clear();
Vdou    tag_delE;              tag_delE.clear();      Vdou    Muprob_k;             Muprob_k.clear();
Vdou    etachi;                etachi.clear();        Vdou    Eprob_mu;             Eprob_mu.clear(); 
Vdou    kschi;                 kschi.clear();         Vdou    Kprob_mu;             Kprob_mu.clear();
Vdou    Piprob;                Piprob.clear();        Vdou    Piprob_mu;            Piprob_mu.clear();
Vdou    Muprob;                Muprob.clear();        Vdou    Piprob_e;             Piprob_e.clear();
Vdou    Eprob;                 Eprob.clear();         Vdou    Kprob_e;              Kprob_e.clear();
Vdou    Kprob;                 Kprob.clear();         Vdou    Muprob_e;             Muprob_e.clear();
Vdou    Pitag;                 Pitag.clear();         Vdou    Ktag;                 Ktag.clear();
Vdou    sig_m12;               sig_m12.clear();       Vdou    sig_m13;              sig_m13.clear();
Vdou    sig_m14;               sig_m14.clear();       Vdou    sig_m23;              sig_m23.clear();
Vdou    sig_m24;               sig_m24.clear();       Vdou    sig_m34;              sig_m34.clear();
Vdou    tag_angle1;            tag_angle1.clear();    Vdou    tag_angle2;           tag_angle2.clear();
Vdou    tag_angle3;            tag_angle3.clear();    Vdou    tag_angle4;           tag_angle4.clear();
Vdou    tag_angle5;            tag_angle5.clear();        


//2020.05.07
Vdou Lamlen;       Lamlen.clear();
Vdou Lamlenerr;    Lamlenerr.clear();
Vdou Lamchi;       Lamchi.clear();
Vdou Lam_p_eemc;   Lam_p_eemc.clear();
Vdou Lam_p_evp;    Lam_p_evp.clear();
Vdou Lam_pi_eemc;  Lam_pi_eemc.clear();
Vdou Lam_pi_evp;   Lam_pi_evp.clear();

Vdou p_eemc;   p_eemc.clear();
Vdou p_evp;    p_evp.clear();
Vdou e_eemc;   e_eemc.clear();
Vdou e_evp;    e_evp.clear();
Vdou mu_eemc;  mu_eemc.clear();
Vdou mu_evp;   mu_evp.clear();

Vdou tag_Lamlen;       tag_Lamlen.clear();
Vdou tag_Lamlenerr;    tag_Lamlenerr.clear();
Vdou tag_Lamchi;       tag_Lamchi.clear();
Vdou tag_Lam_p_eemc;   tag_Lam_p_eemc.clear();
Vdou tag_Lam_p_evp;    tag_Lam_p_evp.clear();
Vdou tag_Lam_pi_eemc;  tag_Lam_pi_eemc.clear();
Vdou tag_Lam_pi_evp;   tag_Lam_pi_evp.clear();

Vtrack  Kparam;                Kparam.clear();
Vtrack  Piparam;               Piparam.clear(); 
Vtrack  Trkkparam;             Trkkparam.clear();
Vtrack  Trkpiparam;            Trkpiparam.clear();

Vint    Kcharge;               Kcharge.clear();        
Vint    Kid;                   Kid.clear();          
Vint    Picharge;              Picharge.clear();      Vint    Pi0tag;               Pi0tag.clear();
Vint    Piid;                  Piid.clear(); 
Vint    Gamid;                 Gamid.clear();
Vint    Pi0id1;                Pi0id1.clear();
Vint    Pi0id2;                Pi0id2.clear(); 
Vint    Etaid1;                Etaid1.clear();
Vint    Etaid2;                Etaid2.clear();
Vint    Ksoid1;                Ksoid1.clear();  
Vint    Ksoid2;                Ksoid2.clear();
Vint    Trkcharge;             Trkcharge.clear();
Vint    Trkid;                 Trkid.clear();
Vint    Muid;                  Muid.clear();
Vint    Mucharge;              Mucharge.clear();
Vint    Eid;                   Eid.clear();
Vint    Echarge;               Echarge.clear();
Vint    pi0num1;               pi0num1.clear();
Vint    tag_pi0id1;            tag_pi0id1.clear(); 
Vint    tag_piid;              tag_piid.clear(); 
Vint    tag_pi0id2;            tag_pi0id2.clear();
Vint    sig_piid1;             sig_piid1.clear();
Vint    sig_piid2;             sig_piid2.clear();
Vint    sig_piid3;             sig_piid3.clear();
Vint    tag_pid;               tag_pid.clear();
Vint    Vtagmode;              Vtagmode.clear();
Vint    tag_tagcharge;         tag_tagcharge.clear();
Vint    sig_ksid1;             sig_ksid1.clear();
Vint    sig_ksid2;             sig_ksid2.clear();
Vint    sig_kid1;              sig_kid1.clear();
Vint    sig_kid2;              sig_kid2.clear();
Vint    Pcharge;               Pcharge.clear();
Vint    Pid;                   Pid.clear();
Vint    Lamid_pi;                Lamid_pi.clear();
Vint    Lamid_p;                Lamid_p.clear();
Vint    Lamcharge;             Lamcharge.clear();



Vp4    Kvector;                Kvector.clear();
Vp4    Pivector;               Pivector.clear();
Vp4    Gamvector;              Gamvector.clear();
Vp4    Pi0vector;              Pi0vector.clear();
Vp4    Etavector;              Etavector.clear();
Vp4    Eta2gammavector;        Eta2gammavector.clear();
Vp4    Pi02gammavector;        Pi02gammavector.clear();
Vp4    Ksovector;              Ksovector.clear();
Vp4    Trkkvector;             Trkkvector.clear();
Vp4    Trkpivector;            Trkpivector.clear();
Vp4    Muvector;               Muvector.clear();
Vp4    single_pdp;             single_pdp.clear();
Vp4    Evector;                Evector.clear();
Vp4    Ksovector_pip;          Ksovector_pip.clear();
Vp4    Ksovector_pim;          Ksovector_pim.clear();
Vp4    Pi0vector_gam1;         Pi0vector_gam1.clear();
Vp4    Pi0vector_gam2;         Pi0vector_gam2.clear();
Vp4    Etavector_gam1;         Etavector_gam1.clear();
Vp4    Etavector_gam2;         Etavector_gam2.clear();
Vp4    Pvector;                Pvector.clear();
Vp4    Lamvector;              Lamvector.clear();
Vp4    Lam_pi;                 Lam_pi.clear();
Vp4    Lam_p;                  Lam_p.clear();
Vp4    tag_Lamvector;          tag_Lamvector.clear();
Vp4    tag_Lam_pi;             tag_Lam_pi.clear();
Vp4    tag_Lam_p;              tag_Lam_p.clear();

Vtrack  Trk_k;                 Trk_k.clear();
Vtrack  Trk_pi;                Trk_pi.clear();
Vtrack  Trk_ks;                Trk_ks.clear();
Vtrack  Trk_pi0;               Trk_pi0.clear();
Vtrack  Trk_eta;               Trk_eta.clear();
Vtrack  Trk_mu;                Trk_mu.clear();
Vtrack  Trk_e;                 Trk_e.clear();
Vtrack  Trk_p;                 Trk_p.clear();
Vtrack  Trk_lam;               Trk_lam.clear();
Vtrack  Trk_lam_pi;            Trk_lam_pi.clear();
Vtrack  Trk_lam_p;             Trk_lam_p.clear();
Vtrack  trk_lam_tag;           trk_lam_tag.clear();
Vtrack  trk_lam_pi_tag;        trk_lam_pi_tag.clear();
Vtrack  trk_lam_p_tag;         trk_lam_p_tag.clear();
Vtrack  sig_trk_4;             sig_trk_4.clear();



  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
  ParticleID *pid = ParticleID::instance();

  Hep3Vector xorigin(0,0,0);
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);

  if(vtxsvc->isVertexValid())
  {
    double* dbv = vtxsvc->PrimaryVertex();
    double*  vv = vtxsvc->SigmaPrimaryVertex();
    xorigin.setX(dbv[0]);
    xorigin.setY(dbv[1]);
    xorigin.setZ(dbv[2]);
  }


 HepPoint3D point0(0.,0.,0.);
  HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);


///////////////////////////////////select all kaon
   for(int i = 0; i < evtRecEvent->totalCharged(); i++) {
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
    if(!(*itTrk)->isMdcKalTrackValid()) continue;
    RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);/////////////////////
    if(fabs(mdcKalTrk->charge())!= 1) continue;
    HepVector a1 = mdcKalTrk->getZHelixK();
    HepSymMatrix Ea1 = mdcKalTrk->getZErrorK();
    VFHelix helixip3_1(point0,a1,Ea1);
    helixip3_1.pivot(IP);

    HepVector  vecipa1 = helixip3_1.a();

    double dr1 = fabs(vecipa1[0]);
    double drz = fabs(vecipa1[3]);
    double costheta = cos(mdcKalTrk->theta());
    if (  dr1 >= 1.0) continue;
    if (drz >= 10.0) continue;
    if ( fabs(costheta) >= 0.93) continue;


    pid->init();
    pid->setMethod(pid->methodProbability());
    pid->setChiMinCut(4);
    pid->setRecTrack(*itTrk);
    pid->usePidSys(pid->useDedx() | pid->useTof()); // use PID sub-system

    pid->identify(pid->onlyPion() | pid->onlyKaon() );    // seperater Pion/Kaon

    pid->calculate();
    if(!(pid->IsPidInfoValid())) continue;
    if(pid->probKaon() <= 0) continue;
    if(pid->probKaon()<=pid->probPion() ) continue;

WTrackParameter kam(xmass[3],mdcKalTrk->getZHelixK(),mdcKalTrk->getZErrorK());
        HepVector kam_val = HepVector(7,0);
        kam_val = kam.w();
        HepLorentzVector P_KAM(kam_val[0],kam_val[1],kam_val[2],kam_val[3]);
        P_KAM.boost(-0.011,0,0);
 
    Kprob.push_back(pid->probKaon());
    Piprob_k.push_back(pid->probPion());

Trk_k.push_back(kam);
    Kcharge.push_back(mdcKalTrk->charge());
    Kid.push_back(i);
    Kvector.push_back(P_KAM);
//nk++;
}
int knumber=Kvector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all kaon successfully. " << endl;
////////////////////////////////select all pion
     for(int j = 0; j < evtRecEvent->totalCharged();j++) {

      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + j;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);

      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelix();
      HepSymMatrix Ea2 = mdcKalTrk->getZError();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      double costheta = cos(mdcKalTrk->theta());
//      if (  dr1 >= 1.0) continue;
//      if (drz >= 10.0) continue;
//      if (  dr1 >= 25.0) continue;
//      if (drz >= 25.0) continue;
      if ( fabs(costheta) >= 0.93) continue;

/*
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof() ); // use PID sub-system
      pid->identify(pid->onlyPion() | pid->onlyKaon());    // seperater Pion/Kaon
      pid->calculate();

     if(pid->probPion()<= pid->probKaon()) continue;
      if(pid->probPion() <= 0) continue;
*/
        WTrackParameter pi(xmass[2],mdcKalTrk->getZHelix(),mdcKalTrk->getZError());
        HepVector pip_val = HepVector(7,0);
        pip_val = pi.w();
        HepLorentzVector P_PI(pip_val[0],pip_val[1],pip_val[2],pip_val[3]);
        P_PI.boost(-0.011,0,0);
//    Piprob.push_back(pid->probPion());
//    Kprob_pi.push_back(pid->probKaon());

Trk_pi.push_back(pi);
    Picharge.push_back(mdcKalTrk->charge());
    Piid.push_back(j);
    Pivector.push_back(P_PI);
//if(mdcKalTrk->charge()==1)npi++;
}
int pinumber=Pivector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all pion successfully. " << endl;

////////////////////////////////select all kso
     for(int i = 0; i < evtRecEvent->totalCharged();i++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk1 = (*itTrk)->mdcKalTrack();

      if(mdcKalTrk1->charge() != 1) continue;
        HepVector a1 = mdcKalTrk1->getZHelix();
      HepSymMatrix Ea1 = mdcKalTrk1->getZError();
      VFHelix helixip3_1(point0,a1,Ea1);
      helixip3_1.pivot(IP);

      HepVector  vecipa1 = helixip3_1.a();

      double dr1 = fabs(vecipa1[0]);
      double drz = fabs(vecipa1[3]);
      double costheta = cos(mdcKalTrk1->theta());
      if (drz >= 20.0) continue;
      if ( fabs(costheta) >= 0.93) continue;

     for(int j = 0; j < evtRecEvent->totalCharged();j++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + j;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk2 = (*itTrk)->mdcKalTrack();

      if(mdcKalTrk2->charge() != -1) continue;
        HepVector a2 = mdcKalTrk2->getZHelix();
      HepSymMatrix Ea2 = mdcKalTrk2->getZError();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);

      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      double costheta = cos(mdcKalTrk2->theta());
      if (drz >= 20.0) continue;
      if ( fabs(costheta) >= 0.93) continue;


     WTrackParameter pip(xmass[2],mdcKalTrk1->getZHelix(),mdcKalTrk1->getZError());
     WTrackParameter pim(xmass[2],mdcKalTrk2->getZHelix(),mdcKalTrk2->getZError());


 Hep3Vector ip(0,0,0);
 HepSymMatrix ipEx(3, 0);
 IVertexDbSvc* vtxsvc;
 Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
 if (vtxsvc->isVertexValid())
 {
   double* dbv = vtxsvc->PrimaryVertex();
   double* vv  = vtxsvc->SigmaPrimaryVertex();
   ip.setX(dbv[0]);
   ip.setY(dbv[1]);
   ip.setZ(dbv[2]);
   ipEx[0][0] = vv[0] * vv[0];
   ipEx[1][1] = vv[1] * vv[1];
   ipEx[2][2] = vv[2] * vv[2];
 }
 else{
continue;}

 VertexParameter bs;
 bs.setVx(ip);
 bs.setEvx(ipEx);
 ///////////////////////////////////////////////////////////////////
 //  set a common vertex with huge error
 ///////////////////////////////////////////////////////////////////
 HepPoint3D    vx(0., 0., 0.);
 HepSymMatrix  Evx(3, 0);
 double bx = 1E+6;
 double by = 1E+6;
 double bz = 1E+6;
 Evx[0][0] = bx * bx;
 Evx[1][1] = by * by;
 Evx[2][2] = bz * bz;
 VertexParameter vxpar;
 vxpar.setVx(vx);
 vxpar.setEvx(Evx);
 ///////////////////////////////////////////////////////////////////
 //  do vertex fit
 ///////////////////////////////////////////////////////////////////
 VertexFit *vtxfit = VertexFit::instance();
 vtxfit->init();

 vtxfit->AddTrack(0, pip);
 vtxfit->AddTrack(1, pim);
 vtxfit->AddVertex(0, vxpar, 0, 1);
 if (!(vtxfit->Fit(0))) continue;
 vtxfit->Swim(0);
 vtxfit->BuildVirtualParticle(0);
 WTrackParameter wks_Trk = vtxfit->wVirtualTrack(0);
 double vtx_chisq = vtxfit->chisq(0);
 ///////////////////////////////////////////////////////////////////
 //  do second vertex fit
 ///////////////////////////////////////////////////////////////////
 SecondVertexFit *svtxfit = SecondVertexFit::instance();
 svtxfit->init();
 svtxfit->setPrimaryVertex(bs);
 svtxfit->AddTrack(0, vtxfit->wVirtualTrack(0));
 svtxfit->setVpar(vtxfit->vpar(0));
if (!svtxfit->Fit()) continue;
double len = svtxfit->decayLength();
 double lenerr = svtxfit->decayLengthError();
if ((len/lenerr)<=2) continue;
 HepLorentzVector pks_temp = svtxfit->p4par();
        pks_temp.boost(-0.011,0,0);
       if( fabs(pks_temp.m()-0.4977)>0.012) continue;

    HepVector ks_pip = HepVector(7,0);
    ks_pip = pip.w();
    HepLorentzVector P_pip(ks_pip[0],ks_pip[1],ks_pip[2],ks_pip[3]);
    P_pip.boost(-0.011,0,0);

    HepVector ks_pim = HepVector(7,0);
    ks_pim = pim.w();
    HepLorentzVector P_pim(ks_pim[0],ks_pim[1],ks_pim[2],ks_pim[3]);
    P_pim.boost(-0.011,0,0);

Ksovector_pim.push_back(P_pim);
Ksovector_pip.push_back(P_pip);
Trk_ks.push_back(wks_Trk);

 Ksovector.push_back(pks_temp);
 Ksoid1.push_back(i);
 Ksoid2.push_back(j);
 Ksolen.push_back(len);
      kschi.push_back(vtx_chisq);
}
}
int ksonumber=Ksovector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all kso successfully. " << endl;

////////////////////////////////select all gamma
  for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
    if(!(*itTrk)->isEmcShowerValid()) continue;
    RecEmcShower *emcTrk = (*itTrk)->emcShower();
    Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());
    double dang = 200.;
    for(int j = 0; j < evtRecEvent->totalCharged(); j++) {
      EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
      if(!(*jtTrk)->isExtTrackValid()) continue;
      RecExtTrack *extTrk = (*jtTrk)->extTrack();
      if(extTrk->emcVolumeNumber() == -1) continue;
      Hep3Vector extpos = extTrk->emcPosition();
      double angd = extpos.angle(emcpos);

      if(angd < dang){
        dang = angd;
      }
    }
    if(dang>=200) continue;
    double eraw = emcTrk->energy();
    double phi = emcTrk->phi();
    double the = emcTrk->theta();
    dang = dang * 180 / (CLHEP::pi);
    if(fabs(dang) < m_gammaAngleCut) continue;
    //
    int module = emcTrk->module();
    double Tdc=emcTrk->time();
    if((Tdc<0||Tdc>14))                 continue;

    if(module==1){   if(eraw < 0.025) continue;     }
    if(module==0||module==2) {  if(eraw < 0.05) continue;   }
    //

///////////////////////////////////

    HepLorentzVector ptrk;
    ptrk.setPx(eraw*sin(the)*cos(phi));
    ptrk.setPy(eraw*sin(the)*sin(phi));
    ptrk.setPz(eraw*cos(the));
    ptrk.setE(eraw);
    ptrk.boost(-0.011,0,0);

    Gamid.push_back(i);
    Gamvector.push_back(ptrk);
}
  int gamnumber=Gamvector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all gamma successfully. " << endl;
if (gamnumber>100) return StatusCode::SUCCESS;

////////////////////////////////select all pi0
    for(int x = 0; x < gamnumber - 1; x++){
    for(int y = x+1; y < gamnumber; y++) {

   HepLorentzVector p2g = Gamvector[x] + Gamvector[y];
if (p2g.m()>0.15 ||p2g.m()<0.115) continue;

   HepLorentzVector ppi0;
KalmanKinematicFit * kmfit =KalmanKinematicFit::instance();
RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+Gamid[x]))->emcShower();//////////////////
RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+Gamid[y]))->emcShower();////////////
      kmfit->init();
      kmfit->AddTrack(0, 0.0, g1Trk);
      kmfit->AddTrack(1, 0.0, g2Trk);
      kmfit->AddResonance(0, 0.135, 0, 1);
double pi0chisq(9999);
bool oksq = kmfit->Fit();
  if(oksq){
       pi0chisq  = kmfit->chisq();
       ppi0 = kmfit->pfit(0)+kmfit->pfit(1);
       ppi0.boost(-0.011,0,0);
  }
       kmfit->BuildVirtualParticle(0);
       WTrackParameter wvpi0 = kmfit->wVirtualTrack(0);
      if(pi0chisq>=200 ) continue;
      Pi0vector.push_back(ppi0);
      Pi0id1.push_back(Gamid[x]);
      Pi0id2.push_back(Gamid[y]);
      Pi02gammavector.push_back(p2g);
      Pi0chi.push_back(pi0chisq);

Pi0vector_gam1.push_back(kmfit->pfit(0));
Pi0vector_gam2.push_back(kmfit->pfit(1));

Trk_pi0.push_back(wvpi0);

}
}
int pi0number=Pi0vector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all pi0 successfully. " << endl;

////////////////////////////////select all eta
    for(int x = 0; x < gamnumber - 1; x++){
    for(int y = x+1; y < gamnumber; y++) {

   HepLorentzVector p2g = Gamvector[x] + Gamvector[y];
if (p2g.m()<0.51 ||p2g.m()>0.57) continue;

   HepLorentzVector peta;
KalmanKinematicFit * kmfit =KalmanKinematicFit::instance();
RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+Gamid[x]))->emcShower();//////////////////
RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+Gamid[y]))->emcShower();////////////
      kmfit->init();
      kmfit->AddTrack(0, 0.0, g1Trk);
      kmfit->AddTrack(1, 0.0, g2Trk);
      kmfit->AddResonance(0, 0.548, 0, 1);
double etachisq(9999);
bool oksq = kmfit->Fit();
  if(oksq){
       etachisq  = kmfit->chisq();
       peta = kmfit->pfit(0)+kmfit->pfit(1);
       peta.boost(-0.011,0,0);
  }
       kmfit->BuildVirtualParticle(0);
       WTrackParameter wveta = kmfit->wVirtualTrack(0);
      if(etachisq>=200 ) continue;
      Etavector.push_back(peta);
      Eta2gammavector.push_back(p2g);
      Etaid1.push_back(Gamid[x]);
      Etaid2.push_back(Gamid[y]);
      etachi.push_back(etachisq);
Etavector_gam1.push_back(kmfit->pfit(0));
Etavector_gam2.push_back(kmfit->pfit(1));
Trk_eta.push_back(wveta);
}
}
int etanumber=Etavector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all eta successfully. " << endl;

////////////////////////////////select all muon 
     for(int k = 0; k < evtRecEvent->totalCharged();k++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + k;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::muon);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelixMu();
      HepSymMatrix Ea2 = mdcKalTrk->getZErrorMu();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      double costheta = cos(mdcKalTrk->theta());
//      if (  dr1 >= 1.0) continue;
//      if (drz >= 10.0) continue;
      if ( fabs(costheta) >= 0.93) continue;      

      /*
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof() | pid->useEmc()); // use PID sub-system

//      pid->identify(pid->onlyMuon() | pid->onlyKaon() | pid->onlyElectron() );   
      pid->identify(pid->onlyMuon() | pid->onlyKaon() | pid->onlyElectron() |pid->onlyPion());   
      pid->calculate();
      if(pid->probMuon()<= pid->probKaon()) continue;
      if(pid->probMuon() <= 0.001) continue;
      if(pid->probMuon()<= pid->probElectron()) continue;                            
      */

        WTrackParameter mu(xmass[1],mdcKalTrk->getZHelixMu(),mdcKalTrk->getZErrorMu());
        HepVector mup_val = HepVector(7,0);
        mup_val = mu.w();
        HepLorentzVector P_MU(mup_val[0],mup_val[1],mup_val[2],mup_val[3]);
        P_MU.boost(-0.011,0,0);

        double pmu=P_MU.rho();
        if ( (*itTrk)->isEmcShowerValid() )//mu
        {    
            RecEmcShower* emcTrk = (*itTrk)->emcShower();
            double eemc = emcTrk->energy();
            double evp = eemc/pmu;
            mu_eemc.push_back(eemc);
            mu_evp.push_back(evp);
        }    
        else{
            mu_eemc.push_back(0);
            mu_evp.push_back(0);
        }    

/*
        Muprob.push_back(pid->probMuon());
        Eprob_mu.push_back(pid->probElectron());
        Kprob_mu.push_back(pid->probKaon());
        Piprob_mu.push_back(pid->probPion());
*/

        Trk_mu.push_back(mu);
        Mucharge.push_back(mdcKalTrk->charge());
        Muid.push_back(k);
        Muvector.push_back(P_MU);
}
int munumber=Muvector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all muon successfully. " << endl;

////////////////////////////////select all electron/positron
     for(int i = 0; i < evtRecEvent->totalCharged();i++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
      HepVector a2 = mdcKalTrk->getZHelixE();
      HepSymMatrix Ea2 = mdcKalTrk->getZErrorE();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      double costheta = cos(mdcKalTrk->theta());
//      if (  dr1 >= 25.0) continue;
//      if (drz >= 25.0) continue;
//      if (  dr1 >= 1.0) continue;
//      if (drz >= 10.0) continue;

      if ( fabs(costheta) >= 0.93) continue;      
/*
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof() | pid->useEmc()); // use PID sub-system

      pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() | pid->onlyMuon());   
//      pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() );   
      pid->calculate();
      if(pid->probElectron() <= 0) continue;
      if(pid->probElectron() <= pid->probPion()||pid->probElectron() <= pid->probKaon()) continue;
  //    if((pid->probElectron())<=0.8*((pid->probKaon())+(pid->probElectron())+(pid->probPion()))) continue;
*/ 
        WTrackParameter e(xmass[0],mdcKalTrk->getZHelixE(),mdcKalTrk->getZErrorE());
        HepVector ep_val = HepVector(7,0);
        ep_val = e.w();
        HepLorentzVector P_E(ep_val[0],ep_val[1],ep_val[2],ep_val[3]);
        P_E.boost(-0.011,0,0);

	double pe=P_E.rho();

	if ( (*itTrk)->isEmcShowerValid() )//e
	{    
		RecEmcShower* emcTrk = (*itTrk)->emcShower();
		double eemc = emcTrk->energy();
		double evp = eemc/pe;
		e_eemc.push_back(eemc);
		e_evp.push_back(evp);
	}    
	else{
		e_eemc.push_back(0);
		e_evp.push_back(0);
		}    

/*
    Eprob.push_back(pid->probElectron());
    
    Kprob_e.push_back(pid->probKaon());
    Piprob_e.push_back(pid->probPion());
    Muprob_e.push_back(pid->probMuon());
*/
    Echarge.push_back(mdcKalTrk->charge());
    Eid.push_back(i);
    Evector.push_back(P_E);
    Trk_e.push_back(e);
}
int enumber=Evector.size();

//2020.05.16 good charged trackes ==4
//It is a fatal bug that found on 2020.05.19!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//if(enumber!=4) return StatusCode::SUCCESS;

if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all electron/positron successfully. " << endl;

////////////////////////////////select all proton
     for(int j = 0; j < evtRecEvent->totalCharged();j++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + j;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelixP();
      HepSymMatrix Ea2 = mdcKalTrk->getZErrorP();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      double costheta = cos(mdcKalTrk->theta());
//      if (  dr1 >= 25.0) continue;
//      if (drz >= 25.0) continue;
//      if (  dr1 >= 1.0) continue;
//      if (drz >= 10.0) continue;

      if ( fabs(costheta) >= 0.93) continue;
/*
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);

      pid->usePidSys(pid->useDedx() | pid->useTof() ); // use PID sub-system
      pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());    // seperater Pion/Kaon

      pid->calculate();
     if(pid->probProton()<= pid->probKaon()) continue;
     if(pid->probProton()<= pid->probPion()) continue;
     if(pid->probProton() <= 0) continue;
*/
        WTrackParameter p(xmass[4],mdcKalTrk->getZHelixP(),mdcKalTrk->getZErrorP());
        HepVector pip_val = HepVector(7,0);
        pip_val = p.w();
        HepLorentzVector P_P(pip_val[0],pip_val[1],pip_val[2],pip_val[3]);
	P_P.boost(-0.011,0,0);

	double pp=P_P.rho();

	if ( (*itTrk)->isEmcShowerValid() )//p
	{    
		RecEmcShower* emcTrk = (*itTrk)->emcShower();
		double eemc = emcTrk->energy();
		double evp = eemc/pp;
		p_eemc.push_back(eemc);
		p_evp.push_back(evp);
	}
	else{
		p_eemc.push_back(0);
		p_evp.push_back(0);
		}    

Trk_p.push_back(p);
    Pcharge.push_back(mdcKalTrk->charge());
    Pid.push_back(j);
    Pvector.push_back(P_P);
}
int pnumber=Pvector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all proton successfully. " << endl;

////////////////////////////////select all lambda
     for(int i = 0; i < evtRecEvent->totalCharged();i++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk1 = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);

      if(abs(mdcKalTrk1->charge()) != 1) continue;
        HepVector a1 = mdcKalTrk1->getZHelix();
      HepSymMatrix Ea1 = mdcKalTrk1->getZError();
      VFHelix helixip3_1(point0,a1,Ea1);
      helixip3_1.pivot(IP);

      HepVector  vecipa1 = helixip3_1.a();

      double dr1 = fabs(vecipa1[0]);
      double drz = fabs(vecipa1[3]);
      double costheta = cos(mdcKalTrk1->theta());
//      if (  dr1 >= 25.0) continue;
//      if (drz >= 25.0) continue;
//      if (drz >= 20.0) continue;
      if ( fabs(costheta) >= 0.93) continue;

     for(int j = 0; j < evtRecEvent->totalCharged();j++) {
      EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + j;
      if(!(*itTrk2)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk2 = (*itTrk2)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);

      if((mdcKalTrk2->charge()+mdcKalTrk1->charge())!=0) continue;
      int pcharge=mdcKalTrk2->charge();
        HepVector a2 = mdcKalTrk2->getZHelixP();
      HepSymMatrix Ea2 = mdcKalTrk2->getZErrorP();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);

      HepVector  vecipa2 = helixip3_2.a();

      double dr12 = fabs(vecipa2[0]);
      double drz2 = fabs(vecipa2[3]);
      double costheta2 = cos(mdcKalTrk2->theta());
//     if (  dr12 >= 25.0) continue;
//      if (drz2 >= 25.0) continue;
//      if (  dr12 >= 25.0) continue;
//      if (drz2 >= 20.0) continue;
      if ( fabs(costheta2) >= 0.93) continue;


     WTrackParameter vpi(xmass[2],mdcKalTrk1->getZHelix(),mdcKalTrk1->getZError());
     WTrackParameter vp(xmass[4],mdcKalTrk2->getZHelixP(),mdcKalTrk2->getZErrorP());


 Hep3Vector ip(0,0,0);
 HepSymMatrix ipEx(3, 0);
 IVertexDbSvc* vtxsvc;
 Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
 if (vtxsvc->isVertexValid())
 {
   double* dbv = vtxsvc->PrimaryVertex();
   double* vv  = vtxsvc->SigmaPrimaryVertex();
   ip.setX(dbv[0]);
   ip.setY(dbv[1]);
   ip.setZ(dbv[2]);
   ipEx[0][0] = vv[0] * vv[0];
   ipEx[1][1] = vv[1] * vv[1];
   ipEx[2][2] = vv[2] * vv[2];
 }
 else{
continue;}

 VertexParameter bs;
 bs.setVx(ip);
 bs.setEvx(ipEx);
 ///////////////////////////////////////////////////////////////////
 //  set a common vertex with huge error
 ///////////////////////////////////////////////////////////////////
 HepPoint3D    vx(0., 0., 0.);
 HepSymMatrix  Evx(3, 0);
 double bx = 1E+6;
 double by = 1E+6;
 double bz = 1E+6;
 Evx[0][0] = bx * bx;
 Evx[1][1] = by * by;
 Evx[2][2] = bz * bz;
 VertexParameter vxpar;
 vxpar.setVx(vx);
 vxpar.setEvx(Evx);
 ///////////////////////////////////////////////////////////////////
 //  do vertex fit
 ///////////////////////////////////////////////////////////////////
 VertexFit *vtxfit = VertexFit::instance();
 vtxfit->init();

 vtxfit->AddTrack(0, vpi);
 vtxfit->AddTrack(1, vp);
 vtxfit->AddVertex(0, vxpar, 0, 1);
 if (!(vtxfit->Fit(0))) continue;
 vtxfit->Swim(0);
 vtxfit->BuildVirtualParticle(0);
 double vtx_chisq = vtxfit->chisq(0);
 WTrackParameter wlam_Trk = vtxfit->wVirtualTrack(0);
 WTrackParameter wpi  = vtxfit->wtrk(0);
 WTrackParameter wp  = vtxfit->wtrk(1);
 ///////////////////////////////////////////////////////////////////
 //  do second vertex fit
 ///////////////////////////////////////////////////////////////////
 SecondVertexFit *svtxfit = SecondVertexFit::instance();
 svtxfit->init();
 svtxfit->setPrimaryVertex(bs);
 svtxfit->AddTrack(0, vtxfit->wVirtualTrack(0));
 svtxfit->setVpar(vtxfit->vpar(0));
if (!svtxfit->Fit()) continue;
double len = svtxfit->decayLength();
 double lenerr = svtxfit->decayLengthError();
//if ((len/lenerr)<=2) continue;
 HepLorentzVector plam_temp = svtxfit->p4par();
  WTrackParameter wlam_svt  = svtxfit->wpar();
        plam_temp.boost(-0.011,0,0);
       //if(plam_temp.m()>1.121||plam_temp.m()<1.111) continue;
       if(plam_temp.m()>1.2||plam_temp.m()<1.0) continue;

        HepVector p_pi_val = HepVector(7,0);
        p_pi_val = wpi.w();
        HepLorentzVector L_Pi(p_pi_val[0],p_pi_val[1],p_pi_val[2],p_pi_val[3]);
        L_Pi.boost(-0.011,0,0);

        HepVector p_p_val = HepVector(7,0);
        p_p_val = wp.w();
        HepLorentzVector L_P(p_p_val[0],p_p_val[1],p_p_val[2],p_p_val[3]);
        L_P.boost(-0.011,0,0);

	double pp  = L_P.rho();
	double ppi = L_Pi.rho();

        if ( (*itTrk)->isEmcShowerValid() )//pi
        {
		RecEmcShower* emcTrk = (*itTrk)->emcShower();
		double eemc = emcTrk->energy();
		double evp = eemc/ppi;
		Lam_pi_eemc.push_back(eemc);
		Lam_pi_evp.push_back(evp);
	}
	else{
		Lam_pi_eemc.push_back(0);
		Lam_pi_evp.push_back(0);
	}

	 if ( (*itTrk2)->isEmcShowerValid() )//p
        {
		RecEmcShower* emcTrk = (*itTrk2)->emcShower();
		double eemc = emcTrk->energy();
		double evp = eemc/pp;
		Lam_p_eemc.push_back(eemc);
		Lam_p_evp.push_back(evp);
	}
	else{
		Lam_p_eemc.push_back(0);
		Lam_p_evp.push_back(0);
	}

 x0[5]++;

 Lam_pi.push_back(L_Pi);
 Lam_p.push_back(L_P);
 Lamcharge.push_back(pcharge);
 Lamvector.push_back(plam_temp);
 Lamid_pi.push_back(i);
 Lamid_p.push_back(j);
 Lamlen.push_back(len);
 Lamlenerr.push_back(lenerr);

 Lamchi.push_back(vtx_chisq);
// Trk_lam.push_back(wlam_Trk);
 Trk_lam.push_back(wlam_svt);
 Trk_lam_pi.push_back(wpi);
 Trk_lam_p.push_back(wp);

 }
 }
int lamnumber=Lamvector.size();
if(m_debug)     cout << "/ ------ [ pmuAlg.execute ]: Select all lambda successfully. " << endl;


/////////////////////////////////////////////////////////////////////////
HepLorentzVector P4_tag_p,P4_tag_pi,P4_tag_lam;
HepLorentzVector P4_sig_p,P4_sig_e,P4_sig_lam;
HepLorentzVector P4_sig_p_svf,P4_sig_mu_svf,P4_sig_lam_svf;

HepLorentzVector lam_tag_4c(0.,0.,0.,0.);
HepLorentzVector lam_sig_4c(0.,0.,0.,0.);
HepLorentzVector p_tag_4c_2(0.,0.,0.,0.);
HepLorentzVector pi_tag_4c_2(0.,0.,0.,0.);
HepLorentzVector p_sig_4c_2(0.,0.,0.,0.);
HepLorentzVector mu_sig_4c_2(0.,0.,0.,0.);

HepLorentzVector P_sig_123,P_sig_124,P_sig_234,P_sig_1234,pdp1,P_sig_134,P_sig_125,P_sig_235,P_sig_345,P_sig_135;

HepLorentzVector pdp,pdp_2,p_uv,p_ev,p_kpi,p_ku,p_ke,p_kpiu,p_kpie,Muvector_new,p_keta,p_ketae,p_ketau,p_v2_1,p_v3_1,pdp4,pdp5,p_piu,p_kv,p_piv,p_pie,v4_k,v4_pi,v4_u,v4_v,v4_1,v4_2,v4_3,v4_4,v4_5;
HepLorentzVector v4_1_4c(0.,0.,0.,0.);
HepLorentzVector v4_2_4c(0.,0.,0.,0.);
HepLorentzVector v4_3_4c(0.,0.,0.,0.);
HepLorentzVector v4_4_4c(0.,0.,0.,0.);
HepLorentzVector Mu_1,p_v2_2,p_v2_a,pdp_new_a,kpi1,kpi2,kpi3,pi1pi2,pi1pi3,pi2pi3,kpi1pi2,kpi1pi3,kpi2pi3,pi1pi2pi3;
int tagcharge,sig_number=0;
for(int q=0;q<2;q++){
if (q==0){
	 tagcharge=-1;
}
else {
tagcharge=1;
}
for (int tagmode=1; tagmode<2; tagmode++){
////////////////////tagside
/////////////////
set0();
if(tagmode==1){// anti-lambda -> anti-proton pion+
for(int i=0;i<lamnumber;i++){
x0[0]++;
if(Lamcharge[i]!=tagcharge) continue;
x0[1]++;
int s_id[20];for(int ii=0;ii<20;ii++)s_id[ii]=-1;
s_id[0]=Lamid_p[i];
s_id[1]=Lamid_pi[i];
if(same(s_id))continue;
x0[2]++;
//if (Lamchi[i] <= chi_cut)   {
//      chi_cut = Lamchi[i];
        HepLorentzVector pdp_temp = Lamvector[i];
        double temp1 = (ecm/2.)*(ecm/2.)-pdp_temp.rho()*pdp_temp.rho() ;
        if(temp1<0) temp1 =0;
        HepLorentzVector p_all(0,0,0,ecm);
        HepLorentzVector reco_tag=p_all-pdp_temp;
        double mass_bc  = sqrt(temp1);
        if(mass_bc< 1.0 || mass_bc> 1.2)  continue;
//        if(mass_bc<= 2.0)  continue;
        double  delE_tag =(ecm/2.)-pdp_temp.e();
        if(fabs(delE_tag)<=deltaE_cut)   {
          deltaE_cut = fabs(delE_tag);
          deltaE_temp=delE_tag;
         pdp = pdp_temp;
          xinvmass = pdp.m();
          mass_reco_tag=reco_tag.m();
        mass_bc_temp =mass_bc;
        pdp_rho_temp=pdp.rho();
        pdp_e_temp=pdp.e();

        p_tag_1=Lam_p[i].rho();
        c_tag_1=Lam_p[i].cosTheta();

        eemc_tag_1=Lam_p_eemc[i];
        evp_tag_1=Lam_p_evp[i];

        p_tag_2=Lam_pi[i].rho();
        c_tag_2=Lam_pi[i].cosTheta();
        p_tag=Lamvector[i].rho();
        c_tag=Lamvector[i].cosTheta();
        eemc_tag_2=Lam_pi_eemc[i];
        evp_tag_2=Lam_pi_evp[i];
        P4_tag_p=Lam_p[i];
        P4_tag_pi=Lam_pi[i];
        P4_tag_lam=Lamvector[i];

        m_pdp_theta=pdp.cosTheta();
        tag_pid_temp=Lamid_p[i];
        tag_piid_temp=Lamid_pi[i];
        tagmode_temp=tagmode;
        tagcharge_temp=tagcharge;
        lam_chi_tag = Lamchi[i];
        lam_len_tag = Lamlen[i];
        lam_lenerr_tag = Lamlenerr[i];

        S_trk_lam_tag=Trk_lam[i];
        S_trk_lam_pi_tag=Trk_lam_pi[i];
        S_trk_lam_p_tag=Trk_lam_p[i];

        if(runNo<0){
            if(tagcharge==1&&T4_lambda_p.size()>0&&T4_lambda_pi.size()>0){
                T_angle1=((Lam_p[i].vect()).angle(T4_lambda_p[0].vect()))/(CLHEP::pi)*180;
                T_angle2=((Lam_pi[i].vect()).angle(T4_lambda_pi[0].vect()))/(CLHEP::pi)*180;
            }//////////if(tagcharge==1)
            if(tagcharge==-1&&T4_anti_lambda_p.size()>0&&T4_anti_lambda_pi.size()>0){
                T_angle1=((Lam_p[i].vect()).angle(T4_anti_lambda_p[0].vect()))/(CLHEP::pi)*180;
                T_angle2=((Lam_pi[i].vect()).angle(T4_anti_lambda_pi[0].vect()))/(CLHEP::pi)*180;
            }//////////if(tagcharge==-1)
        }////////runNo

        ncount=1;
        }
        //}//if (Lamchi[a] <= chi_cut)
}//for lmd 

}//tagmode==1

///////////////////////
if(ncount>0&&ncount<10){//be used for double tag
    trk_lam_tag.push_back(S_trk_lam_tag);
    trk_lam_pi_tag.push_back(S_trk_lam_pi_tag);
    trk_lam_p_tag.push_back(S_trk_lam_p_tag);

    Vtagmode.push_back(tagmode_temp);
    tag_tagcharge.push_back(tagcharge_temp);
    tag_mbc.push_back(mass_bc_temp);
    tag_delE.push_back(deltaE_temp);
    single_pdp.push_back(pdp);
    tag_piid.push_back(tag_piid_temp);
    tag_pid.push_back(tag_pid_temp);

    //2020.05.07
    tag_Lamlen.push_back(lam_len_tag);
    tag_Lamlenerr.push_back(lam_lenerr_tag);
    tag_Lamchi.push_back(lam_chi_tag);
    tag_Lam_p_eemc.push_back(eemc_tag_1);
    tag_Lam_p_evp.push_back(evp_tag_1);
    tag_Lam_pi_eemc.push_back(eemc_tag_2);
    tag_Lam_pi_evp.push_back(evp_tag_2);

    tag_Lamvector.push_back(P4_tag_lam);
    tag_Lam_pi.push_back(P4_tag_pi);
    tag_Lam_p.push_back(P4_tag_p);

    tag_angle1.push_back(T_angle1);
    tag_angle2.push_back(T_angle2);
    tag_angle3.push_back(T_angle3);
    tag_angle4.push_back(T_angle4);
    tag_angle5.push_back(T_angle5);
}
//////////////////

int cosmicray=0;
if (cosmic_ok) { cosmicray = 1;}
if(ncount>0&&ncount<10  ) {//fill tree

topo_temp_10 = numParticle;
for(int i=0;i<numParticle;i++){
   pdgid_temp_10[i] = vpdgid[i];
   mcidx_temp_10[i] = vmotheridx[i];
}

   T_angle1_temp_1     =      T_angle1;
   T_angle2_temp_1     =      T_angle2;
   T_angle3_temp_1     =      T_angle3;
   T_angle4_temp_1     =      T_angle4;
   T_angle5_temp_1     =      T_angle5;

   mdbc1_1             =         mdbc1;
   mdbc2_1             =         mdbc2;
   mcmode1_1           =       mcmode1;
   mcmode2_1           =       mcmode2;
   mcmodea_1           =       mcmodea;
   mcmodeb_1           =       mcmodeb;
   tagcharge_temp_1    =     tagcharge;
   tagmode_temp_1      =       tagmode;
   m_irec1             =         event;
   m_irun1             =         runNo;
   delE_tag_temp_1     =   deltaE_temp;
   mass_inv_temp_1     =      xinvmass;
   mass_reco_tag_temp_1=      mass_reco_tag;
   pdp_temp_1          =  pdp_rho_temp;
   pdp_e_temp_1        =    pdp_e_temp;
   mass_bc_temp_1      =  mass_bc_temp;
   cosmicray_temp_1    =     cosmicray;
   p_tag_1_temp_1      =       p_tag_1;
   c_tag_1_temp_1      =       c_tag_1;
   p_tag_2_temp_1      =       p_tag_2;
   c_tag_2_temp_1      =       c_tag_2;
   p_tag_temp_1        =       p_tag;
   c_tag_temp_1        =       c_tag;
   p_theta_temp_1      =       m_pdp_theta;
   mctag_temp_1        =       m_mctag;

//2020.05.07
   lam_chi_temp_1      =       lam_chi_tag;
   lam_len_temp_1      =       lam_len_tag;
   lam_lenerr_temp_1   =       lam_lenerr_tag;
   eemc_1_temp_1       =       eemc_tag_1;
   evp_1_temp_1        =       evp_tag_1;
   eemc_2_temp_1       =       eemc_tag_2;
   evp_2_temp_1        =       evp_tag_2;

	
if(mass_bc_temp_1>0.01)   m_tuple1->write();
}//end of fill tree
}//end of all tagmode

}//end of charge conjugate 
sig_number=Vtagmode.size();
/////////////////////////////////////////////////////////////////////////////////////end of tag side

for(int n=0;n<sig_number;n++){
//////////////signalside
set0();
x1[0]++;

//2020.05.19 good charged trackes ==4
if(munumber!=4) return StatusCode::SUCCESS;
x0[6]++;
if(Vtagmode[n]==1){//////////////////////////////////////Lambda0 --> proton pi- +c.c.
int a=-1,b=-1;

//2020.05.16 
for(int a_temp=0;a_temp<pnumber;a_temp++){
x1[1]++;
for(int b_temp=0;b_temp<munumber;b_temp++){
x1[2]++;
if(Pcharge[a_temp]==tag_tagcharge[n])continue;
x1[3]++;
if(Mucharge[b_temp]!=tag_tagcharge[n]) continue;
x1[4]++;

int s_id[20];for(int ii=0;ii<20;ii++)s_id[ii]=-1;
s_id[0]=tag_pid[n]; 
s_id[1]=tag_piid[n];
s_id[2]=Pid[a_temp];
s_id[3]=Muid[b_temp];
if(same(s_id))continue;
x1[5]++;

      a=a_temp;
      b=b_temp;
  }
}

//2020.05.16 
if(a!=-1&&b!=-1){

eemc_sig_p=p_eemc[a];
eemc_sig_mu=mu_eemc[b];
 evp_sig_p=p_evp[a];
 evp_sig_mu=mu_evp[b];

//2020.05.07 second vertex fit for double tag(use PIDtype: p pi)
     if(b!=-1) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Muid[b];//be careful!!  use muon id but assign it to pion type
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk1 = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);//use the pion type

      if(abs(mdcKalTrk1->charge()) != 1) continue;
        HepVector a1 = mdcKalTrk1->getZHelix();
      HepSymMatrix Ea1 = mdcKalTrk1->getZError();
      VFHelix helixip3_1(point0,a1,Ea1);
      helixip3_1.pivot(IP);

      HepVector  vecipa1 = helixip3_1.a();

      double dr1 = fabs(vecipa1[0]);
      double drz = fabs(vecipa1[3]);
      double costheta = cos(mdcKalTrk1->theta());
//      if (  dr1 >= 25.0) continue;
//      if (drz >= 25.0) continue;
      if ( fabs(costheta) >= 0.93) continue;

     if(a!=-1) {
      EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + Pid[a];
      if(!(*itTrk2)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk2 = (*itTrk2)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);

      if((mdcKalTrk2->charge()+mdcKalTrk1->charge())!=0) continue;
      int pcharge=mdcKalTrk2->charge();
        HepVector a2 = mdcKalTrk2->getZHelixP();
      HepSymMatrix Ea2 = mdcKalTrk2->getZErrorP();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);

      HepVector  vecipa2 = helixip3_2.a();

      double dr12 = fabs(vecipa2[0]);
      double drz2 = fabs(vecipa2[3]);
      double costheta2 = cos(mdcKalTrk2->theta());
 //     if (  dr12 >= 25.0) continue;
//      if (drz2 >= 25.0) continue;
      if ( fabs(costheta2) >= 0.93) continue;


     WTrackParameter vmu(xmass[2],mdcKalTrk1->getZHelix(),mdcKalTrk1->getZError());//use the pion type
     WTrackParameter vp(xmass[4],mdcKalTrk2->getZHelixP(),mdcKalTrk2->getZErrorP());


 Hep3Vector ip(0,0,0);
 HepSymMatrix ipEx(3, 0);
 IVertexDbSvc* vtxsvc;
 Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
 if (vtxsvc->isVertexValid())
 {
   double* dbv = vtxsvc->PrimaryVertex();
   double* vv  = vtxsvc->SigmaPrimaryVertex();
   ip.setX(dbv[0]);
   ip.setY(dbv[1]);
   ip.setZ(dbv[2]);
   ipEx[0][0] = vv[0] * vv[0];
   ipEx[1][1] = vv[1] * vv[1];
   ipEx[2][2] = vv[2] * vv[2];
 }
 else{
continue;}

 VertexParameter bs;
 bs.setVx(ip);
 bs.setEvx(ipEx);
 ///////////////////////////////////////////////////////////////////
 //  set a common vertex with huge error
 ///////////////////////////////////////////////////////////////////
 HepPoint3D    vx(0., 0., 0.);
 HepSymMatrix  Evx(3, 0);
 double bx = 1E+6;
 double by = 1E+6;
 double bz = 1E+6;
 Evx[0][0] = bx * bx;
 Evx[1][1] = by * by;
 Evx[2][2] = bz * bz;
 VertexParameter vxpar;
 vxpar.setVx(vx);
 vxpar.setEvx(Evx);
 ///////////////////////////////////////////////////////////////////
 //  do vertex fit
 ///////////////////////////////////////////////////////////////////
 VertexFit *vtxfit = VertexFit::instance();
 vtxfit->init();
 vtxfit->setChisqCut(100000,1.0e-3);

 vtxfit->AddTrack(0, vmu);
 vtxfit->AddTrack(1, vp);
 vtxfit->AddVertex(0, vxpar, 0, 1);
 if (!(vtxfit->Fit(0))) continue;
 vtxfit->Swim(0);
 vtxfit->BuildVirtualParticle(0);
 double vtx_chisq = vtxfit->chisq(0);
 WTrackParameter wlam_Trk = vtxfit->wVirtualTrack(0);
 WTrackParameter wmu_sig  = vtxfit->wtrk(0);
 WTrackParameter wp_sig  = vtxfit->wtrk(1);
 ///////////////////////////////////////////////////////////////////
 //  do second vertex fit
 ///////////////////////////////////////////////////////////////////
 SecondVertexFit *svtxfit = SecondVertexFit::instance();
 svtxfit->init();
 svtxfit->setChisqCut(100000,1.0e-3);
 svtxfit->setPrimaryVertex(bs);
 svtxfit->AddTrack(0, vtxfit->wVirtualTrack(0));
 svtxfit->setVpar(vtxfit->vpar(0));
 if (!svtxfit->Fit()) continue;
 double len = svtxfit->decayLength();
 double lenerr = svtxfit->decayLengthError();
 //if ((len/lenerr)<=2) continue;
 HepLorentzVector plam_temp = svtxfit->p4par();
 WTrackParameter wlam_svt   = svtxfit->wpar();
 plam_temp.boost(-0.011,0,0);
 //if(plam_temp.m()>1.121||plam_temp.m()<1.111) continue;
 //if(plam_temp.m()>1.2||plam_temp.m()<1.0) continue;

        HepVector p_mu_val = HepVector(7,0);
        p_mu_val = wmu_sig.w();
        HepLorentzVector L_MU(p_mu_val[0],p_mu_val[1],p_mu_val[2],p_mu_val[3]);
        L_MU.boost(-0.011,0,0);

        HepVector p_p_val = HepVector(7,0);
        p_p_val = wp_sig.w();
        HepLorentzVector L_P(p_p_val[0],p_p_val[1],p_p_val[2],p_p_val[3]);
        L_P.boost(-0.011,0,0);

        double pp = L_P.rho();
        double pmu = L_MU.rho();

        if ( (*itTrk)->isEmcShowerValid() )//mu
        {
            RecEmcShower* emcTrk = (*itTrk)->emcShower();
            double eemc = emcTrk->energy();
            double evp = eemc/pmu;
            eemc_sig_mu_svf=eemc;
            evp_sig_mu_svf=evp;
        }
        if ( (*itTrk2)->isEmcShowerValid() )//p
        {
            RecEmcShower* emcTrk = (*itTrk2)->emcShower();
            double eemc = emcTrk->energy();
            double evp = eemc/pp;
            eemc_sig_p_svf=eemc;
            evp_sig_p_svf=evp;
        }

        lam_len_sig=len;
        lam_lenerr_sig=lenerr;
        lam_chi_sig=vtx_chisq;
        P4_sig_p_svf=L_P;
        P4_sig_mu_svf=L_MU;
        P4_sig_lam_svf=plam_temp;
        // sig_trk_lam=wlam_Trk;
        sig_trk_lam=wlam_svt;
        sig_trk_p=wp_sig;
        sig_trk_mu=wmu_sig;
     }
}//end of second vertex fit
x0[7]++;
//2020.05.08 4c kinematic fit for lambda and anti-lambda(use PIDtype:: p p pi pi)
KinematicFit * kmfit = KinematicFit::instance(); // define kinematic fitting
kmfit->init(); // initial the pramaters of kinematic fitting  
kmfit->setChisqCut(100000,0.05);
kmfit->AddTrack(0, trk_lam_tag[n]); // add charged particle
kmfit->AddTrack(1, sig_trk_lam);
kmfit->AddFourMomentum(0, ecms); // add 4c constraints
oksq_4c = kmfit->Fit();
if(oksq_4c){
        lam_tag_4c = kmfit->pfit(0); // get the partcle parameters after kinematic fitting in lorentzvector format
        lam_sig_4c = kmfit->pfit(1); 
	double m_chi2  = kmfit->chisq(); // get the chi-square value of kinemtic fitting
	mass_lam_tag_4c=lam_tag_4c.m();	
	mass_lam_sig_4c=lam_sig_4c.m();	
	chi_4c=m_chi2;
	x0[3]++;
}

//2020.05.08 4c kinematic fit for proton anti-proton pion and electron(use PIDtype:: p p pi pi)
KinematicFit * kmfit2 = KinematicFit::instance(); // define kinematic fitting
kmfit2->init(); // initial the pramaters of kinematic fitting  
kmfit2->setChisqCut(100000,0.05);
kmfit2->AddTrack(0, trk_lam_p_tag[n]); // add charged particle
kmfit2->AddTrack(1, trk_lam_pi_tag[n]);
kmfit2->AddTrack(2, sig_trk_p);
kmfit2->AddTrack(3, sig_trk_mu);
kmfit2->AddFourMomentum(0, ecms); // add 4c constraints
oksq_4c_2 = kmfit2->Fit();
if(oksq_4c_2){
        p_tag_4c_2  = kmfit2->pfit(0); 
        pi_tag_4c_2 = kmfit2->pfit(1); 
        p_sig_4c_2  = kmfit2->pfit(2); 
        mu_sig_4c_2  = kmfit2->pfit(3); 
	double m_chi2  = kmfit2->chisq(); // get the chi-square value of kinemtic fitting
	chi_4c_2=m_chi2;
	HepLorentzVector pppimu = p_tag_4c_2+pi_tag_4c_2+p_sig_4c_2+mu_sig_4c_2;
	mass_jpsi=(pppimu).m();
	x0[4]++;
}

Muvector_new=Muvector[b];
//if (Lamchi[a] <= chi_cut)   {
//	chi_cut = Lamchi[a];

//if(fabs(tag_delE[n])<=deltaE_cut)  {
//      deltaE_cut = fabs(tag_delE[n]);
       HepLorentzVector pdp3 = Pvector[a]+Muvector_new;
       esig_V_ebeam=(pdp3.e())/(ecm/2.);
       HepLorentzVector p_all(0,0,0,ecm);
       e_miss=(ecm/2.)-pdp3.e();
//       e_miss=ecm/2- Lamvector[a].e();
       HepLorentzVector pdp_new;
       pdp_new = single_pdp[n];
       pdp_new.setPhi(single_pdp[n].phi());
       pdp_new.setTheta(single_pdp[n].theta());
       pdp_new.setE(ecm/2.);
       double rho_temp=sqrt((ecm/2.)*(ecm/2.)-mlambda*mlambda);
       //double rho_temp=sqrt((ecm/2.)*(ecm/2.)-mlambdac*mlambdac);
       pdp_new.setRho(rho_temp);
       HepLorentzVector p_v3;
       p_v3=p_all-pdp_new-pdp3;
//       p_v3=p_all-single_pdp[n]-pdp3;
//       p_v3=p_all-pdp_new-Muvector_new;
//       p_v3.setE(p_v3.rho());
       p_miss=p_v3.rho();
       u_miss=e_miss-p_miss;
       miss_m2=e_miss * e_miss-p_miss * p_miss;

       //2020.06.18
       if (fabs(u_miss)>0.2) continue;

//2020.05.09
reco_mass=(p_all-pdp_new).m();
angle_lampmu_58=((pdp_new.vect()).angle((Pvector[a]+Pivector[b]).vect()))/(CLHEP::pi)*180;
//angle_lampmu_58=((pdp_new.vect()).angle((p_sig_4c_2+mu_sig_4c_2).vect()))/(CLHEP::pi)*180;

double angle_pmiss_e=((p_v3.vect()).angle(Muvector_new));
pte2_temp=4*fabs(p_miss)*fabs(p_miss)*sin(angle_pmiss_e/2)*sin(angle_pmiss_e/2);

//2020.05.07  boost to sig_lam
Hep3Vector P_sig_lam_4C = lam_sig_4c.boostVector();

//2020.07.31  comments from Steve
//the proton's momentum in signal-side lambda rest frame and the angle between proton and pion/muon in signal-side lambda rest frame
HepLorentzVector sig_lam_57  = p_all-pdp_new;
//HepLorentzVector sig_p_57    = tag_Lam_p[n]; An error found on 2020.08.02
HepLorentzVector sig_p_57    = Pvector[a];
HepLorentzVector sig_mu_57   = Pivector[b];
Hep3Vector P_sig_lam_reco = sig_lam_57.boostVector();
sig_p_57.boost(-P_sig_lam_reco);
sig_mu_57.boost(-P_sig_lam_reco);
p_sig_7=sig_p_57.rho();
angle_pmu_57=((sig_p_57.vect()).angle(sig_mu_57.vect()))/(CLHEP::pi)*180;

//2020.08.11 test for using recoiling pion to obtain such angle
HepLorentzVector sig_pi_reco  = p_all-pdp_new-Pvector[a];
sig_pi_reco.boost(-P_sig_lam_reco);
//angle_pmu_57=((sig_p_57.vect()).angle(sig_pi_reco.vect()))/(CLHEP::pi)*180;


//2020.08.02 comments from Tao Luo
HepLorentzVector sig_lam_0802   = p_all-pdp_new;
//cout<<__LINE__<<"\t"<<sig_lam_0802.px()<<"\t"<< sig_lam_0802.py()<<"\t"<<sig_lam_0802.pz()<<"\t"<<sig_lam_0802.e()<<endl;
Hep3Vector P_sig_lam_0802 = sig_lam_0802.boostVector();

//the proton's transverse momentum with respect to the lambda direction in J/psi rest frame
HepLorentzVector sig_p_0802_jr  = Pvector[a];
double angle_plmd_0802_jr  =  (sig_p_0802_jr.vect()).angle(sig_lam_0802.vect());
p_pt_rest_jpsi  = (sig_p_0802_jr.rho())*sin(angle_plmd_0802_jr);
//cout<<__LINE__<<"\t"<<sig_p_0802_jr.rho()<<"\t"<<angle_plmd_0802_jr<<"\t"<<p_pt_rest_jpsi<<endl;

//the proton's transverse momentum with respect to the lambda direction in signal-side rest frame
HepLorentzVector sig_p_0802_lr  = Pvector[a];
//cout<<__LINE__<<"\t"<<sig_p_0802_lr.px()<<"\t"<< sig_p_0802_lr.py()<<"\t"<<sig_p_0802_lr.pz()<<"\t"<<sig_p_0802_lr.e()<<endl;
sig_p_0802_lr.boost(-P_sig_lam_0802);
//cout<<__LINE__<<"\t"<<sig_p_0802_lr.px()<<"\t"<< sig_p_0802_lr.py()<<"\t"<<sig_p_0802_lr.pz()<<"\t"<<sig_p_0802_lr.e()<<endl;
double angle_plmd_0802_lr  =  (sig_p_0802_lr.vect()).angle(sig_lam_0802.vect());
p_pt_rest_lmd  = (sig_p_0802_lr.rho())*sin(angle_plmd_0802_lr);
//cout<<__LINE__<<"\t"<<sig_p_0802_lr.rho()<<"\t"<<angle_plmd_0802_lr<<"\t"<<p_pt_rest_lmd<<endl;

//2020.08.14 test for different combination of proton's momentum and angle
p_pt_jp_la = (sig_p_0802_jr.rho())*sin(angle_plmd_0802_lr);
p_pt_lp_ja = (sig_p_0802_lr.rho())*sin(angle_plmd_0802_jr);

//2020.06.16 comments from Patrik
HepLorentzVector sig_miss_pi_1;
HepLorentzVector sig_miss_pi_2;
HepLorentzVector sig_miss_pi_3;

  //missing mass of missing pion
sig_miss_pi_1  =  p_all-pdp_new-p_sig_4c_2;
sig_miss_pi_2  =  p_all-pdp_new-Pvector[a];
mass_sig_miss_pi_1  =  sig_miss_pi_1.m();
mass_sig_miss_pi_2  =  sig_miss_pi_2.m();

  //missing momentum of missing pion
sig_miss_pi_3  =  lam_sig_4c-p_sig_4c_2;
sig_miss_pi_3.boost(-P_sig_lam_4C);
sig_miss_pi_2.boost(-P_sig_lam_reco);
p_sig_3  =  sig_miss_pi_3.rho();
p_sig_4  =  sig_miss_pi_2.rho();

HepLorentzVector gam_temp;
double del_sum_e_cut=0.2;
for(int aa=0;aa<gamnumber;aa++){
	HepLorentzVector sum_temp = single_pdp[n]+Pvector[a]+Pivector[b]+Gamvector[aa];
	double del_sum_e=fabs(sum_temp.e()-3.097);
	if(del_sum_e<=del_sum_e_cut)   {
		del_sum_e_cut=del_sum_e;
		gam_temp=Gamvector[aa];
	}
}

if(gamnumber>0){
HepLorentzVector sigma0_1=single_pdp[n]+gam_temp;
HepLorentzVector sigma0_2=p_all-single_pdp[n];
Hep3Vector P_sigma0_1=sigma0_1.boostVector();
Hep3Vector P_sigma0_2=sigma0_2.boostVector();
HepLorentzVector gam_sigma0_1=gam_temp;
HepLorentzVector gam_sigma0_2=gam_temp;
gam_sigma0_1.boost(-P_sigma0_1);
gam_sigma0_2.boost(-P_sigma0_2);
ene_gam_sigma0_1=gam_sigma0_1.e();
ene_gam_sigma0_2=gam_sigma0_2.e();
}

//2020.06.16 comments from Hai-Bo Li
HepLorentzVector Muvector_4c;
HepLorentzVector Muvector_reco;

Muvector_4c   =  mu_sig_4c_2;
Muvector_reco =  Pivector[b];

Muvector_4c.boost(-P_sig_lam_4C);
Muvector_reco.boost(-P_sig_lam_reco);

p_sig_5 = Muvector_4c.rho();
p_sig_6 = Muvector_reco.rho();

Hep3Vector lmd_p=lam_sig_4c.vect().cross(p_sig_4c_2.vect());
angle_pi_0616=mu_sig_4c_2.vect().angle(-lmd_p)/(CLHEP::pi)*180;

//2020.07.07 Inspired by Xi- --> sigma0 e nu
mass_sig_pmu_temp  = (Pvector[a]+Pivector[b]).m();//mass of proton and muon, the muon is set to pion PIDtype
mass_reco_lmdmu_temp = (p_all-pdp_new-Pivector[b]).m();//recoil mass of lambda and muon, the muon is set to pion PIDtype

//2020.08.14 muon's momentum in recoiling tag-side lambda and signal-side proton rest frame
HepLorentzVector sig_miss_pi_4;
sig_miss_pi_4  =  p_all-pdp_new-Pvector[a];
Hep3Vector P_sig_miss_pi_4 = sig_miss_pi_4.boostVector();

HepLorentzVector sig_muon_4;
sig_muon_4 = Muvector[b];
sig_muon_4.boost(-P_sig_miss_pi_4);
p_sig_8=sig_muon_4.rho();

q2_temp=(ecm/2.-Pvector[a].e())*(ecm/2.-Pvector[a].e())-(sig_lam_57-Pvector[a]).rho()*(sig_lam_57-Pvector[a]).rho();

       HepLorentzVector p_nu;
       p_nu=p_v3;
       p_nu.setE(p_nu.rho());
q2_2_temp=(Muvector_new+p_nu).m2();

       p_sig_1         =       Pvector[a].rho();
       c_sig_1         =       Pvector[a].cosTheta();
       p_sig_2         =       Muvector_new.rho();
       c_sig_2         =       Muvector_new.cosTheta();

       p_tag_11        =       tag_Lam_p[n].rho();
       c_tag_11        =       tag_Lam_p[n].cosTheta();
       p_tag_12        =       tag_Lam_pi[n].rho();
       c_tag_12        =       tag_Lam_pi[n].cosTheta();

       m_pdp_theta_2   =       single_pdp[n].cosTheta();
       m_pdp_phi       =       single_pdp[n].phi();
       tag_mass_bc     =       tag_mbc[n];
       tag_deltaE      =       tag_delE[n];
       tag_mass        =       single_pdp[n].m();
       T_tagmode       =       Vtagmode[n];
       sigtagcharge    =       tag_tagcharge[n];

       v4_1            =       Pvector[a];
       v4_2            =       Muvector_new;
       v4_3            =       tag_Lam_p[n];
       v4_4            =       tag_Lam_pi[n];

       v4_1_4c         =       p_sig_4c_2;
       v4_2_4c         =       mu_sig_4c_2;
       v4_3_4c         =       p_tag_4c_2;
       v4_4_4c         =       pi_tag_4c_2;

////////////////////////////////
/*
KalmanKinematicFit * kmfit1 = KalmanKinematicFit::instance();
kmfit1->init();
//        kmfit1->setEspread(0.0015);
//        kmfit1->setCollideangle(0.011);
kmfit1->setChisqCut(5000000);
kmfit1->AddTrack(0, Trk_k[a]);
kmfit1->AddTrack(1, Trk_pi[b]);
kmfit1->AddTrack(2, Trk_pi[c]);
kmfit1->AddTrack(3, Trk_pi0[d]);
kmfit1->AddTrack(4, trk_lam_tag[n]);
kmfit1->AddTrack(5, trk_lam_pi_tag[n]);
if(Vtagmode[n]==4||Vtagmode[n]==6||Vtagmode[n]==7||Vtagmode[n]==8||Vtagmode[n]==9)kmfit1->AddTrack(6, trk_lam_p_tag[n]);
if(Vtagmode[n]==6||Vtagmode[n]==8)kmfit1->AddTrack(7, sig_trk_4[n]);
kmfit1->AddFourMomentum(0, ecms); 
kmfit1->Fit();
kmfit_chi=kmfit1->chisq();
*/
/////////////////////////

if(runNo<0){

	if(T4_lambda_mu.size()>0&&T4_lambda_nu_mu.size()>0)  {
		q2_truth_temp=(T4_lambda_mu[0]+T4_lambda_nu_mu[0]).m2();  
	}

	if(T4_anti_lambda_mu.size()>0&&T4_anti_lambda_nu_mu.size()>0)  {
		q2_truth_temp=(T4_anti_lambda_mu[0]+T4_anti_lambda_nu_mu[0]).m2();
	}

int tep=0,tem=0;
if(tag_tagcharge[n]==-1&&T4_lambda_p.size()>0&&T4_lambda_mu.size()>0&&T4_lambda_nu_mu.size()>0) 
	tep=1;
if(tag_tagcharge[n]==1&&T4_anti_lambda_p.size()>0&&T4_anti_lambda_mu.size()>0&&T4_anti_lambda_nu_mu.size()>0) 
	tem=1;

if(tep==1){
angle1=((Pvector[a].vect()).angle(T4_lambda_p[0].vect()))/(CLHEP::pi)*180;
angle2=((Muvector_new.vect()).angle(T4_lambda_mu[0].vect()))/(CLHEP::pi)*180;
}//////////if(tagcharge==-1)
if(tem==1){
angle1=((Pvector[a].vect()).angle(T4_anti_lambda_p[0].vect()))/(CLHEP::pi)*180;
angle2=((Muvector_new.vect()).angle(T4_anti_lambda_mu[0].vect()))/(CLHEP::pi)*180;
}//////////if(tagcharge==1)
}////////runNo

Ncharge_ex=evtRecEvent->totalCharged()-2-2;



//}//for minimum delE
//}


//2020.05.09, save information of charged tracks in signal side
//save information of proton in signal side
if(a!=-1) {//sig p
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Pid[a];     
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelixP();
      HepSymMatrix Ea2 = mdcKalTrk->getZErrorP();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      m_vxy_1_11 = dr1;
      m_vz_1_11 = drz;
      m_phi_1_11 = mdcKalTrk->phi();

//PID information for the signal proton
      ParticleID *pid = ParticleID::instance();
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() | pid->useEmc() );
      pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
      pid->calculate();
      if(pid->IsPidInfoValid()) {
	      m_probe_1_11  = pid->probElectron();
	      m_probmu_1_11 = pid->probMuon();
	      m_probpi_1_11 = pid->probPion();
	      m_probk_1_11  = pid->probKaon();
	      m_probp_1_11  = pid->probProton();
      } else {
	      m_probe_1_11  = -1.0;
	      m_probmu_1_11 = -1.0;
	      m_probpi_1_11 = -1.0;
	      m_probk_1_11  = -1.0;
	      m_probp_1_11  = -1.0;
}
//Tof information for the signal proton
if ((*itTrk)->isTofTrackValid()) {
	      SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();
	      SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
	      for (;iter_tof != tofTrkCol.end(); iter_tof++ ){
		      TofHitStatus *status = new TofHitStatus;
		      status->setStatus((*iter_tof)->status());
		      m_fgtof_1_11 = 1;
		      m_counter_1_11 = status->is_counter();
		      m_isbarrel_1_11 = status->is_barrel();
		      m_layertof_1_11 = status->layer();
		      m_iscluster_1_11 = status->is_cluster();
		      m_tof_1_11 = (*iter_tof)->tof();
		      m_texe_1_11 = (*iter_tof)->texpElectron();
		      m_texmu_1_11 = (*iter_tof)->texpMuon();
		      m_texpi_1_11 = (*iter_tof)->texpPion();
		      m_texk_1_11 = (*iter_tof)->texpKaon();
		      m_texp_1_11 = (*iter_tof)->texpProton();
		      m_dte_1_11 = m_tof_1_11 - m_texe_1_11;
		      m_dtmu_1_11 = m_tof_1_11 - m_texmu_1_11;
		      m_dtpi_1_11 = m_tof_1_11 - m_texpi_1_11;
		      m_dtk_1_11 = m_tof_1_11 - m_texk_1_11;
		      m_dtp_1_11 = m_tof_1_11 - m_texp_1_11;
	      }
}

//dedx information for signal proton
if ((*itTrk)->isMdcDedxValid())
{
	RecMdcDedx* dedxTrk = (*itTrk)->mdcDedx();
	m_chi_e_1_11  = dedxTrk->chiE();
	m_chi_mu_1_11 = dedxTrk->chiMu();
	m_chi_pi_1_11 = dedxTrk->chiPi();
	m_chi_k_1_11  = dedxTrk->chiK();
	m_chi_p_1_11  = dedxTrk->chiP();
} else {
	m_chi_e_1_11  = -100.;
	m_chi_mu_1_11 = -100.;
	m_chi_pi_1_11 = -100.;
	m_chi_k_1_11  = -100.;
	m_chi_p_1_11  = -100.;
}

}//end save sig p

//save information of muon in signal side
if(b!=-1) {//sig mu
	EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Muid[b];     
	if(!(*itTrk)->isMdcKalTrackValid()) continue;
	RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::muon);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelixMu();
      HepSymMatrix Ea2 = mdcKalTrk->getZErrorMu();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      m_vxy_2_11 = dr1;
      m_vz_2_11 = drz;
      m_phi_2_11 = mdcKalTrk->phi();

//PID information for the signal muon

      ParticleID *pid = ParticleID::instance();
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() | pid->useEmc() );
      pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
      pid->calculate();
      if(pid->IsPidInfoValid()) {
	      m_probe_2_11  = pid->probElectron();
	      m_probmu_2_11 = pid->probMuon();
	      m_probpi_2_11 = pid->probPion();
	      m_probk_2_11  = pid->probKaon();
	      m_probp_2_11  = pid->probProton();

//      if (!( pid->probElectron() > pid->probPion()&& pid->probElectron()>0.001)) continue;
      x0[8]++;

//It is a fatal bug that found on 2020.05.16!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//      if (!( pid->probElectron() > pid->probPion()))
//	       return StatusCode::SUCCESS;
      } else {
	      m_probe_2_11  = -1.0;
	      m_probmu_2_11 = -1.0;
	      m_probpi_2_11 = -1.0;
	      m_probk_2_11  = -1.0;
	      m_probp_2_11  = -1.0;
}

//Tof information for the signal muon
if ((*itTrk)->isTofTrackValid()) {
	      SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();
	      SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
	      for (;iter_tof != tofTrkCol.end(); iter_tof++ ){
		      TofHitStatus *status = new TofHitStatus;
		      status->setStatus((*iter_tof)->status());
		      m_fgtof_2_11 = 1;
		      m_counter_2_11 = status->is_counter();
		      m_isbarrel_2_11 = status->is_barrel();
		      m_layertof_2_11 = status->layer();
		      m_iscluster_2_11 = status->is_cluster();
		      m_tof_2_11 = (*iter_tof)->tof();
		      m_texe_2_11 = (*iter_tof)->texpElectron();
		      m_texmu_2_11 = (*iter_tof)->texpMuon();
		      m_texpi_2_11 = (*iter_tof)->texpPion();
		      m_texk_2_11 = (*iter_tof)->texpKaon();
		      m_texp_2_11 = (*iter_tof)->texpProton();
		      m_dte_2_11 = m_tof_2_11 - m_texe_2_11;
		      m_dtmu_2_11 = m_tof_2_11 - m_texmu_2_11;
		      m_dtpi_2_11 = m_tof_2_11 - m_texpi_2_11;
		      m_dtk_2_11 = m_tof_2_11 - m_texk_2_11;
		      m_dtp_2_11 = m_tof_2_11 - m_texp_2_11;
   }
}

//dedx information for signal muon
if ((*itTrk)->isMdcDedxValid())
{
	RecMdcDedx* dedxTrk = (*itTrk)->mdcDedx();
	m_chi_e_2_11  = dedxTrk->chiE();
	m_chi_mu_2_11 = dedxTrk->chiMu();
	m_chi_pi_2_11 = dedxTrk->chiPi();
	m_chi_k_2_11  = dedxTrk->chiK();
	m_chi_p_2_11  = dedxTrk->chiP();
} else {
	m_chi_e_2_11  = -100.;
	m_chi_mu_2_11 = -100.;
	m_chi_pi_2_11 = -100.;
	m_chi_k_2_11  = -100.;
	m_chi_p_2_11  = -100.;
}

//2020.08.14 MUC information for signal muon
if ( (*itTrk)->isMucTrackValid() )
{
	RecMucTrack* mucTrk = (*itTrk)->mucTrack();
	m_maxhitsinlay_2_11 = mucTrk->maxHitsInLayer();
	m_numhits_2_11 = mucTrk->numHits();
	m_numlayers_2_11 = mucTrk->numLayers();
	m_depth_2_11 = mucTrk->depth();
	m_mucchi2_2_11 = mucTrk->chi2();
} else {
	m_numhits_2_11 = -10;
	m_maxhitsinlay_2_11 = -10;
	m_numlayers_2_11 = -10;
	m_depth_2_11 = -10;
	m_mucchi2_2_11 = 300;
}

}//end save sig muon

//2020.05.09, save information of charged tracks in tag side
//save information of proton in tag side
   if(tag_pid.size()>0) {//tag p
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + tag_pid[n];     
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelixP();
      HepSymMatrix Ea2 = mdcKalTrk->getZErrorP();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      m_vxy_3_11 = dr1;
      m_vz_3_11 = drz;
      m_phi_3_11 = mdcKalTrk->phi();

//PID information for the tag proton
      ParticleID *pid = ParticleID::instance();
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() | pid->useEmc() );
      pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
      pid->calculate();
      if(pid->IsPidInfoValid()) {
	      m_probe_3_11  = pid->probElectron();
	      m_probmu_3_11 = pid->probMuon();
	      m_probpi_3_11 = pid->probPion();
	      m_probk_3_11  = pid->probKaon();
	      m_probp_3_11  = pid->probProton();
      } else {
	      m_probe_3_11  = -1.0;
	      m_probmu_3_11 = -1.0;
	      m_probpi_3_11 = -1.0;
	      m_probk_3_11  = -1.0;
	      m_probp_3_11  = -1.0;
}
//Tof information for the tag proton
if ((*itTrk)->isTofTrackValid()) {
	      SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();
	      SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
	      for (;iter_tof != tofTrkCol.end(); iter_tof++ ){
		      TofHitStatus *status = new TofHitStatus;
		      status->setStatus((*iter_tof)->status());
		      m_fgtof_3_11 = 1;
		      m_counter_3_11 = status->is_counter();
		      m_isbarrel_3_11 = status->is_barrel();
		      m_layertof_3_11 = status->layer();
		      m_iscluster_3_11 = status->is_cluster();
		      m_tof_3_11 = (*iter_tof)->tof();
		      m_texe_3_11 = (*iter_tof)->texpElectron();
		      m_texmu_3_11 = (*iter_tof)->texpMuon();
		      m_texpi_3_11 = (*iter_tof)->texpPion();
		      m_texk_3_11 = (*iter_tof)->texpKaon();
		      m_texp_3_11 = (*iter_tof)->texpProton();
		      m_dte_3_11 = m_tof_3_11 - m_texe_3_11;
		      m_dtmu_3_11 = m_tof_3_11 - m_texmu_3_11;
		      m_dtpi_3_11 = m_tof_3_11 - m_texpi_3_11;
		      m_dtk_3_11 = m_tof_3_11 - m_texk_3_11;
		      m_dtp_3_11 = m_tof_3_11 - m_texp_3_11;
	      }
}

//dedx information for tag proton
if ((*itTrk)->isMdcDedxValid())
{
	RecMdcDedx* dedxTrk = (*itTrk)->mdcDedx();
	m_chi_e_3_11  = dedxTrk->chiE();
	m_chi_mu_3_11 = dedxTrk->chiMu();
	m_chi_pi_3_11 = dedxTrk->chiPi();
	m_chi_k_3_11  = dedxTrk->chiK();
	m_chi_p_3_11  = dedxTrk->chiP();
} else {
	m_chi_e_3_11  = -100.;
	m_chi_mu_3_11 = -100.;
	m_chi_pi_3_11 = -100.;
	m_chi_k_3_11  = -100.;
	m_chi_p_3_11  = -100.;
}

}//end save tag p

//save information of pion in tag side
   if(tag_piid.size()>0) {//tag pi
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + tag_piid[n];     
      if(!(*itTrk)->isMdcKalTrackValid()) continue;
      RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
      RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
      if(fabs(mdcKalTrk->charge()) != 1) continue;
        HepVector a2 = mdcKalTrk->getZHelix();
      HepSymMatrix Ea2 = mdcKalTrk->getZError();
      VFHelix helixip3_2(point0,a2,Ea2);
      helixip3_2.pivot(IP);
      HepVector  vecipa2 = helixip3_2.a();

      double dr1 = fabs(vecipa2[0]);
      double drz = fabs(vecipa2[3]);
      m_vxy_4_11 = dr1;
      m_vz_4_11 = drz;
      m_phi_4_11 = mdcKalTrk->phi();

//PID information for the tag pion
      ParticleID *pid = ParticleID::instance();
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() | pid->useEmc() );
      pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
      pid->calculate();
      if(pid->IsPidInfoValid()) {
	      m_probe_4_11  = pid->probElectron();
	      m_probmu_4_11 = pid->probMuon();
	      m_probpi_4_11 = pid->probPion();
	      m_probk_4_11  = pid->probKaon();
	      m_probp_4_11  = pid->probProton();
      } else {
	      m_probe_4_11  = -1.0;
	      m_probmu_4_11 = -1.0;
	      m_probpi_4_11 = -1.0;
	      m_probk_4_11  = -1.0;
	      m_probp_4_11  = -1.0;
}
//Tof information for the tag pion
if ((*itTrk)->isTofTrackValid()) {
	      SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();
	      SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
	      for (;iter_tof != tofTrkCol.end(); iter_tof++ ){
		      TofHitStatus *status = new TofHitStatus;
		      status->setStatus((*iter_tof)->status());
		      m_fgtof_4_11 = 1;
		      m_counter_4_11 = status->is_counter();
		      m_isbarrel_4_11 = status->is_barrel();
		      m_layertof_4_11 = status->layer();
		      m_iscluster_4_11 = status->is_cluster();
		      m_tof_4_11 = (*iter_tof)->tof();
		      m_texe_4_11 = (*iter_tof)->texpElectron();
		      m_texmu_4_11 = (*iter_tof)->texpMuon();
		      m_texpi_4_11 = (*iter_tof)->texpPion();
		      m_texk_4_11 = (*iter_tof)->texpKaon();
		      m_texp_4_11 = (*iter_tof)->texpProton();
		      m_dte_4_11 = m_tof_4_11 - m_texe_4_11;
		      m_dtmu_4_11 = m_tof_4_11 - m_texmu_4_11;
		      m_dtpi_4_11 = m_tof_4_11 - m_texpi_4_11;
		      m_dtk_4_11 = m_tof_4_11 - m_texk_4_11;
		      m_dtp_4_11 = m_tof_4_11 - m_texp_4_11;
	      }
}

//dedx information for tag pion
if ((*itTrk)->isMdcDedxValid())
{
	RecMdcDedx* dedxTrk = (*itTrk)->mdcDedx();
	m_chi_e_4_11  = dedxTrk->chiE();
	m_chi_mu_4_11 = dedxTrk->chiMu();
	m_chi_pi_4_11 = dedxTrk->chiPi();
	m_chi_k_4_11  = dedxTrk->chiK();
	m_chi_p_4_11  = dedxTrk->chiP();
} else {
	m_chi_e_4_11  = -100.;
	m_chi_mu_4_11 = -100.;
	m_chi_pi_4_11 = -100.;
	m_chi_k_4_11  = -100.;
	m_chi_p_4_11  = -100.;
}

}//end save tag pi

       ncount2 = 1;

}

double gamE=0.;
for(int h=0;h<gamnumber;h++){
double	gam_angle=Gamvector[h].angle(Evector[b]);
	gamE+=Gamvector[h].e();
	gam_e1=Gamvector[h].e();
	if(gam_e1>=gam_cut)   {
		gam_cut = gam_e1;
		gam_emax=gam_e1;
	}
}
gam_e=gamE;

int cosmicray=0;
if (cosmic_ok) { cosmicray = 1;}
if(ncount2==1)
 {
x1[6]++;
   topo_temp_11                      =              numParticle;

for(int i=0;i<numParticle;i++){
   pdgid_temp_11[i]                  =                  vpdgid[i];
   mcidx_temp_11[i]                  =              vmotheridx[i];
}
   angle1_temp_11                    =                     angle1;
   angle2_temp_11                    =                     angle2;

   T_angle1_temp_11                  =              tag_angle1[n];
   T_angle2_temp_11                  =              tag_angle2[n];

   index_temp_11                     =                          4;
   V4_1_temp_11[0]                   =                  v4_1.px();
   V4_1_temp_11[1]                   =                  v4_1.py();
   V4_1_temp_11[2]                   =                  v4_1.pz();
   V4_1_temp_11[3]                   =                  v4_1.e();
                                                    
   V4_2_temp_11[0]                   =                  v4_2.px();
   V4_2_temp_11[1]                   =                  v4_2.py();
   V4_2_temp_11[2]                   =                  v4_2.pz();
   V4_2_temp_11[3]                   =                  v4_2.e();

   V4_3_temp_11[0]                   =                  v4_3.px();
   V4_3_temp_11[1]                   =                  v4_3.py();
   V4_3_temp_11[2]                   =                  v4_3.pz();
   V4_3_temp_11[3]                   =                  v4_3.e();

   V4_4_temp_11[0]                   =                  v4_4.px();
   V4_4_temp_11[1]                   =                  v4_4.py();
   V4_4_temp_11[2]                   =                  v4_4.pz();
   V4_4_temp_11[3]                   =                  v4_4.e();

   p_1_4c_temp_11                    =                  v4_1_4c.rho();
   p_2_4c_temp_11                    =                  v4_2_4c.rho();
   p_3_4c_temp_11                    =                  v4_3_4c.rho();
   p_4_4c_temp_11                    =                  v4_4_4c.rho();

   V4_4c_1_temp_11[0]                =                  v4_1_4c.px();
   V4_4c_1_temp_11[1]                =                  v4_1_4c.py();
   V4_4c_1_temp_11[2]                =                  v4_1_4c.pz();
   V4_4c_1_temp_11[3]                =                  v4_1_4c.e();

   V4_4c_2_temp_11[0]                =                  v4_2_4c.px();
   V4_4c_2_temp_11[1]                =                  v4_2_4c.py();
   V4_4c_2_temp_11[2]                =                  v4_2_4c.pz();
   V4_4c_2_temp_11[3]                =                  v4_2_4c.e();

   V4_4c_3_temp_11[0]                =                  v4_3_4c.px();
   V4_4c_3_temp_11[1]                =                  v4_3_4c.py();
   V4_4c_3_temp_11[2]                =                  v4_3_4c.pz();
   V4_4c_3_temp_11[3]                =                  v4_3_4c.e();

   V4_4c_4_temp_11[0]                =                  v4_4_4c.px();
   V4_4c_4_temp_11[1]                =                  v4_4_4c.py();
   V4_4c_4_temp_11[2]                =                  v4_4_4c.pz();
   V4_4c_4_temp_11[3]                =                  v4_4_4c.e();


   evp_1_temp_11                     =                  evp_sig_p_svf; 
   evp_2_temp_11                     =                  evp_sig_mu_svf;
   evp_3_temp_11                     =                  tag_Lam_p_evp[n];
   evp_4_temp_11                     =                  tag_Lam_pi_evp[n];
   evp_5_temp_11                     =                  evp_sig_p;
   evp_6_temp_11                     =                  evp_sig_mu;
                 
   eemc_1_temp_11                    =                  eemc_sig_p_svf; 
   eemc_2_temp_11                    =                  eemc_sig_mu_svf;
   eemc_3_temp_11                    =                  tag_Lam_p_eemc[n];
   eemc_4_temp_11                    =                  tag_Lam_pi_eemc[n];
   eemc_5_temp_11                    =                  eemc_sig_p;
   eemc_6_temp_11                    =                  eemc_sig_mu;


   kmfit_chi_temp_11                 =                  chi_4c;
   kmfit_chi_2_temp_11               =                  chi_4c_2;
       
   mdbc1_temp_11                     =                      mdbc1;
   mdbc2_temp_11                     =                      mdbc2;
   mcmode1_temp_11                   =                    mcmode1;
   mcmode2_temp_11                   =                    mcmode2;
   mcmodea_temp_11                   =                    mcmodea;
   mcmodeb_temp_11                   =                    mcmodeb;
   m_irec_temp_11                    =                      event;
   m_irun_temp_11                    =                      runNo;
   cosmicray_temp_11                 =                  cosmicray;

   p_sig_1_temp_11                   =                    p_sig_1;
   c_sig_1_temp_11                   =                    c_sig_1;
   p_sig_2_temp_11                   =                    p_sig_2;
   c_sig_2_temp_11                   =                    c_sig_2;
   p_sig_3_temp_11                   =                    p_sig_3;
   p_sig_4_temp_11                   =                    p_sig_4;
   p_sig_5_temp_11                   =                    p_sig_5;
   p_sig_6_temp_11                   =                    p_sig_6;
   p_sig_7_temp_11                   =                    p_sig_7;
   p_sig_8_temp_11                   =                    p_sig_8;

   p_tag_1_temp_11                   =                    p_tag_11;
   c_tag_1_temp_11                   =                    c_tag_11;
   p_tag_2_temp_11                   =                    p_tag_12;
   c_tag_2_temp_11                   =                    c_tag_12;

   tag_mass_bc_temp_11               =                tag_mass_bc;
   tag_deltaE_temp_11                =                 tag_deltaE;
   tag_mass_temp_11                  =                   tag_mass;
   T_tagmode_temp_11                 =                  T_tagmode;
   tag_tagcharge_temp_11             =               sigtagcharge;

   Ncharge_ex_temp_11                =                 Ncharge_ex;

   gam_e_temp_11                     =                      gam_e;
   gam_emax_temp_11                  =                   gam_emax;
   mctag_temp_11                     =                    m_mctag;

   u_miss_temp_11                    =                     u_miss;
   e_miss_temp_11                    =                     e_miss;
   p_miss_temp_11                    =                     p_miss;
   miss_m2_temp_11                   =                    miss_m2;

  esig_V_ebeam_temp_11               =                    esig_V_ebeam;
  esig_V_ebeam_4c_temp_11            =                    esig_V_ebeam_4c_2;
  angle_pmu_57_temp_11               =                    angle_pmu_57;

  lam_tag_chi_temp_11 = tag_Lamchi[n];
  lam_tag_len_temp_11 = tag_Lamlen[n];
  lam_tag_lenerr_temp_11 = tag_Lamlenerr[n];
  lam_sig_chi_temp_11 = lam_chi_sig;
  lam_sig_len_temp_11 = lam_len_sig;
  lam_sig_lenerr_temp_11 = lam_lenerr_sig;
  mass_lam_tag_4c_temp_11 = mass_lam_tag_4c;
  mass_lam_sig_4c_temp_11 = mass_lam_sig_4c;
  mass_jpsi_4c_2_temp_11 = mass_jpsi;
  mass_sig_miss_pi_1_temp_11 = mass_sig_miss_pi_1;
  mass_sig_miss_pi_2_temp_11 = mass_sig_miss_pi_2;
  mass_sig_pmu_temp_11        = mass_sig_pmu_temp;
  mass_reco_lmdmu_temp_11     = mass_reco_lmdmu_temp;

//2020.05.09
  m_ngoodtrk_11 = munumber;
  m_ngoodgam_11 = gamnumber;
  m_nchartrk_11 = evtRecEvent->totalCharged();
  reco_mass_temp_11 = reco_mass;
  angle_lampmu_58_temp_11 = angle_lampmu_58;
  angle_pi_0616_temp_11 = angle_pi_0616;
  pte2_temp_11 = pte2_temp;

//2020.05.12
   p_theta_temp_11 = m_pdp_theta_2;
   p_phi_temp_11   = m_pdp_phi;
      q2_temp_11   = q2_temp;
    q2_2_temp_11   = q2_2_temp;
    q2_truth_temp_11   = q2_truth_temp;
   ene_gam_sigma0_1_temp_11=ene_gam_sigma0_1;
   ene_gam_sigma0_2_temp_11=ene_gam_sigma0_2;

//2020.07.31 check the pion decay
   pipD_temp_11  =  pipD;
   pimD_temp_11  =  pimD;
   pipD2mu_temp_11  =  pipD2mu;
   pimD2mu_temp_11  =  pimD2mu;

//2020.08.02 proton's transverse momentum
  p_pt_rest_jpsi_temp_11  =  p_pt_rest_jpsi;
  p_pt_rest_lmd_temp_11   =  p_pt_rest_lmd;
  p_pt_jp_la_temp_11      =  p_pt_jp_la;
  p_pt_lp_ja_temp_11      =  p_pt_lp_ja;
  
   m_tuple11->write();                              
}                                                  

}//tagmode==1
////////////////////////////////////////////////////////

}//////////sig_num
/////////////////////////////////////////////////////////////////////////////////////end of signal side

/////////////////////////////////////////////////
} /////////////execute


bool pmu::same(int id[20]){
bool sm=false;
for(int i=0;i<20;i++){
for(int j=0;j<20;j++){
if(id[i]==id[j]&&id[i]!=-1&&id[j]!=-1&&i!=j)sm=true;
}
}
return sm;
}

void pmu::set0()
{
//bool
oksq_4c_2=false, oksq_4c=false;
mini_delE=false;
//////int
T_tagmode=0;	tagmode_temp=0;	tagcharge_temp=0;	sigtagcharge=0;	ncount=0;	
ncount2=0;	Ncharge_ex=999;
/////double
p_sig_1=999;	p_sig_2=999;	p_sig_3=999;  p_sig_4=999; p_sig_5=999; p_sig_6=999; p_sig_7=999; p_sig_8=999;
c_sig_1=999;	c_sig_2=999;	c_sig_3=999;
p_tag_11=999;	p_tag_12=999;	p_tag_13=999;
c_tag_11=999;	c_tag_12=999;	c_tag_13=999;
angle_pmu_57_4c_2=999; angle_pmu_57=999; angle_lampmu_58=999; pte2_temp=999; angle_pi_0616=999; q2_temp=0; q2_2_temp=0;q2_truth_temp=0;
xinvmass=0;	 reco_mass=0;	pdp_rho_temp=0;	pdp_e_temp=0.;  mass_bc_temp=0;	deltaE_temp=99; mass_reco_tag=0;
m_pdp_theta=99;	  m_pdp_theta_2=99;deltaE_cut=0.2;  m_pdp_phi=99;
mass_bc_temp_2=0; deltaE_temp_2=99;
p_tag_2=0.;	p_tag_1=0.;	c_tag_2=0.;	c_tag_1=0.;	tag_pid_temp=999;	tag_pi0id1_temp=999;	
eemc_tag_1=0.; eemc_tag_2=0.; evp_tag_1=0.;   evp_tag_2=0.;  eemc_sig_1=0.; eemc_sig_2=0.; evp_sig_1=0.; evp_sig_2=0.;
eemc_sig_mu_svf=0.; eemc_sig_p_svf=0.; evp_sig_mu_svf=0.; evp_sig_p_svf=0.;
eemc_sig_mu=0.; eemc_sig_p=0.; evp_sig_mu=0.; evp_sig_p=0.;
eemc_sig_1_4c=0.; eemc_sig_2_4c=0.; evp_sig_1_4c=0.; evp_sig_2_4c=0.;
p_tag=0.;  c_tag=0.;  tag_pi0id2_temp=999; tag_piid_temp=999;   tag_pid_temp_2=999;      tag_piid_temp_2=999;
sig_pid_temp_2=999; sig_eid_temp_2=999;
angle1=999.;	angle2=999.;	angle3=999.;	angle4=999.;	angle5=999.;	angle6=999.;
T_angle1=999.;	T_angle2=999.;	T_angle3=999.;	T_angle4=999.;	T_angle5=999.;           
emce=0;	chi_cut=999;	tag_mass_bc=0;
u_miss=999;	e_miss=999;	p_miss=999;    miss_m2=999;	esig_V_ebeam=999; 
u_miss_4c_2=999; e_miss_4c_2=999; p_miss_4c_2=999; miss_m2_4c_2=999; esig_V_ebeam_4c_2=999;
lam_chi_tag=999;lam_lenerr_tag=0; lam_len_tag=0; gam_cut=0;
mass_lam_tag_4c=999; mass_lam_sig_4c=999; chi_4c=999; chi_4c_2=999; mass_jpsi=999; mass_sig_miss_pi_1=999;
mass_sig_miss_pi_2=999; mass_sig_pmu_temp=999;  mass_reco_lmdmu_temp=999;
lam_chi_sig=999; lam_len_sig=0; lam_lenerr_sig=0;
gam_e1=999;	gam_emax=0;	gam_e=999;	kmfit_chi=999; ene_gam_sigma0_1=0; ene_gam_sigma0_2=0;
tag_deltaE=999; tag_mass=999;
p_pt_rest_jpsi=999; 	p_pt_rest_lmd=999;   p_pt_jp_la=999;   p_pt_lp_ja=999;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode pmu::finalize() {
MsgStream log(msgSvc(), name());/////////////////////
log << MSG::INFO << "in finalize()" << endmsg;
//cout<<ncut1<<endl;
/*cout<<"K: "<<nk<<endl;
cout<<"pi: "<<npi<<endl;
cout<<"p: "<<np<<endl;
cout<<"e: "<<ne<<endl;
cout<<"pi0 p: "<<npi0p<<endl;
cout<<"pi0 m: "<<npi0m<<endl;*/
/*cout<<"total charged tracks:\t"<<x0[5]<<endl;
cout<<"total charged tracks which MdcKalTrackValid:\t"<<x0[6]<<endl;
cout<<"fabs(charge)==1 with RecMdcKalTrack::electron:\t"<<x0[7]<<endl;
cout<<"costheta < 0.93 with RecMdcKalTrack::electron:\t"<<x0[8]<<endl;
cout<<"cut for mbc_tag:\t"<<x0[9]<<endl;
cout<<"cut for delE_tag:\t"<<x0[10]<<endl;
cout<<"tag -> sig:\t"<<x0[11]<<endl;
cout<<"lambda with VertexValid:\t"<<x0[12]<<endl;
cout<<"VertexFit:\t"<<x0[13]<<endl;
cout<<"SecondVertexFit:\t"<<x0[14]<<endl;
cout<<"mass window of lambda:\t"<<x0[15]<<endl;
cout<<"Vtagmode.size():\t"<<x0[16]<<endl;
cout<<"sig_number:\t"<<x0[17]<<endl;
cout<<"before PID for electron:\t"<<x0[18]<<endl;
cout<<"tagcharge==1:\t"<<x0[19]<<endl;
cout<<"tagcharge==-1:\t"<<x0[20]<<endl;*/
cout<<"***************************** Version(0814) *******************************"<<endl;
cout<<">   the number of lambda selected                             : "<<x0[0]<<endl;
cout<<">   the number of lambda which charge equal to tagcharge      : "<<x0[1]<<endl;
cout<<">   the number of tag events that not reuse the same track    : "<<x0[2]<<endl;
cout<<">   the number of proton                                      : "<<x1[1]<<endl;
cout<<">   the number of electron                                    : "<<x1[2]<<endl;
cout<<">   the number of proton after the tag charge is met          : "<<x1[3]<<endl;
cout<<">   the number of electron after the tag charge is met        : "<<x1[4]<<endl;
cout<<">   the number of signal events that not reuse the same track : "<<x1[5]<<endl;
cout<<">   the number of events which met 4c for lam-lambar          : "<<x0[3]<<endl;
cout<<">   the number of events which met 4c for all tracks          : "<<x0[4]<<endl;
cout<<"**************************** for cut flow *********************************"<<endl;
cout<<">   the number of total events                                : "<<tot_events<<endl;
cout<<">   the number of events which met vertex fit in tag side     : "<<x0[5]<<endl;
cout<<">   the number of all successfully tagged events              : "<<x1[0]<<endl;
cout<<">   the number of events which have 4 good tracks             : "<<x0[6]<<endl;
cout<<">   the number of events which meet vertex fit in sig side    : "<<x0[7]<<endl;
cout<<">   the number of events which meet the PID for electron      : "<<x0[8]<<endl;
cout<<">   the number of signal events after all filtering           : "<<x1[6]<<endl;
cout<<"***************************************************************************"<<endl;
  return StatusCode::SUCCESS;
}
