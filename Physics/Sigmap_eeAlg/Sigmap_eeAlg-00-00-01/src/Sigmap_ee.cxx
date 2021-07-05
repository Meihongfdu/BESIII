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
#include "DDmcmode/DDmcmode.h"
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
#include "Sigmap_eeAlg/Sigmap_ee.h"

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
const double msigma0 =1.192642;
const double mlambda =1.115683;
const double mxi=1.32171;
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
bool oksq_4c_2, oksq_4c, oksq_3c;
bool mini_delE;
int       T_tagmode,   tagmode_temp, tagcharge_temp,         sigtagcharge,                ncount,                 ncount2;
int      Ncharge_ex,tag_pid_temp,	tag_pi0id1_temp,	tag_pi0id2_temp,  tag_piid_temp,  tag_piid2_temp, sig_gamid;
int tag_pid_temp_2, tag_piid_temp_2, sig_pid_temp_2, sig_eid_temp_2;
double     xinvmass, 	reco_mass,    pdp_rho_temp,   mass_bc_temp,          deltaE_temp,           m_pdp_theta,                 pdp_e_temp;
double     mass_tag_lam_temp, mass_tag_xi, mass_tag_reco_temp, mass_sig_sigma0e, q2;
double     mass_bc_temp_2,  deltaE_temp_2, deltaE_cut;
double                         p_tag_0, c_tag_0, phi_tag_0;
double  eemc_tag_1, evp_tag_1, p_tag_1, c_tag_1, phi_tag_1;
double  eemc_tag_2, evp_tag_2, p_tag_2, c_tag_2, phi_tag_2;
double  eemc_tag_3, evp_tag_3, p_tag_3, c_tag_3, phi_tag_3;
double  eemc_tag_4, evp_tag_4, p_tag_4, c_tag_4, phi_tag_4;
double       angle1,         angle2,         angle3,               angle4,                angle5,    angle6,   angle7;
double     T_angle1,       T_angle2,       T_angle3,             T_angle4,              T_angle5;
double 	emce, eemc_sig_e_svf, eemc_sig_p_svf, evp_sig_e_svf, evp_sig_p_svf;
double  eemc_sig_e1, eemc_sig_p1, evp_sig_e1, evp_sig_p1;
double  eemc_sig_e2, eemc_sig_p2, evp_sig_e2, evp_sig_p2;
double  eemc_sig_pi,evp_sig_pi;
double 	eemc_sig_1_4c, eemc_sig_2_4c, evp_sig_1_4c, evp_sig_2_4c;
double p_sig_1,		p_sig_2,	p_sig_3,    p_sig_4;
double c_sig_1,		c_sig_2,	c_sig_3,    c_sig_4;
double p_tag_11,	p_tag_12,	p_tag_13;
double c_tag_11,	c_tag_12,	c_tag_13;
double angle_lame_57_4c_2,	 angle_lame_57,	 angle_xilame_58,  pte2_temp;

double chi_cut,	tag_mass_bc,	gam_cut,	gam_e1,	gam_emax,	gam_e,           kmfit_chi,  Mee_rec_4c, Mpi0_4c,tag_mass,             tag_deltaE, chi2_min,chi2_pi0;
double u_miss,	e_miss,	p_miss,	miss_m2;
double lam_chi_tag,  lam_len_tag,  lam_lenerr_tag;
double xi_chi_tag,   xi_len_tag,   xi_lenerr_tag;
double esig_V_ebeam, esig_V_ebeam_4c_2, u_miss_4c_2, e_miss_4c_2, p_miss_4c_2, miss_m2_4c_2;
double xi_len_sig, xi_chi_sig, xi_lenerr_sig, mass_xi_tag_4c, mass_xi_sig_4c, chi_4c, chi_4c_2, mass_jpsi, chi_3c;
double lam_sig_chi_temp, lam_sig_len_temp, lam_sig_lenerr_temp;
double recomass_xilam_temp, recomass_xie_temp;

WTrackParameter        S_trk_lam_tag,        S_trk_lam_pi_tag,              S_trk_lam_p_tag,    S_trk_pi_tag,           S_trk_4,                 S_trk_5;
WTrackParameter  sig_trk_lam, sig_trk_e, sig_trk_p, sig_trk_xi;
WTrackParameter  tag_trk_xi;
WTrackParameter  tag_trk_lam;
WTrackParameter  tag_trk_lam_pi;
WTrackParameter  tag_trk_lam_p;
WTrackParameter  tag_trk_pi;
/////////by mh
double i_pi0=99999,i_e1=99999,i_e2=99999;

///////////





/////////////////////////////////////////////////////////////////////////////

Sigmap_ee::Sigmap_ee(const std::string& name, ISvcLocator* pSvcLocator) :
    Algorithm(name, pSvcLocator) {
        declareProperty("GammaAngleCut", m_gammaAngleCut=10.0);//////////share  
        declareProperty("mctag", m_mctag=0);//////////share  
        declareProperty("debug", m_debug = false);
    }
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Sigmap_ee::initialize(){
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
            status = m_tuple1->addItem ("mass_inv",           mass_inv_temp_1);
            status = m_tuple1->addItem ("mass_tag_lam",       mass_tag_lam_temp_1);
            status = m_tuple1->addItem ("mass_tag_reco",      mass_tag_reco_temp_1);
            status = m_tuple1->addItem ("pdp_rho",                 pdp_temp_1);
            status = m_tuple1->addItem ("pdp_e",                 pdp_e_temp_1);
            status = m_tuple1->addItem ("event",                      m_irec1);
            status = m_tuple1->addItem ("runNo",                      m_irun1);
            status = m_tuple1->addItem ("tagcharge",         tagcharge_temp_1);
            status = m_tuple1->addItem ("tagmode",             tagmode_temp_1);
            status = m_tuple1->addItem ("cosmicray",         cosmicray_temp_1);
            status = m_tuple1->addItem ("mctag",                 mctag_temp_1);
            status = m_tuple1->addItem ("delE_gam",           delE_gam_temp_1);

            status = m_tuple1->addItem ("lam_chi",             lam_chi_temp_1);
            status = m_tuple1->addItem ("lam_len",             lam_len_temp_1);
            status = m_tuple1->addItem ("lam_lenerr",       lam_lenerr_temp_1);

            status = m_tuple1->addItem ("xi_chi",               xi_chi_temp_1);
            status = m_tuple1->addItem ("xi_len",               xi_len_temp_1);
            status = m_tuple1->addItem ("xi_lenerr",         xi_lenerr_temp_1);

            status = m_tuple1->addItem ("p_tag_xi",              p_tag_temp_1);
            status = m_tuple1->addItem ("p_tag_p",             p_tag_1_temp_1);
            status = m_tuple1->addItem ("p_tag_pi",            p_tag_2_temp_1);
            status = m_tuple1->addItem ("p_tag_xi_pi",         p_tag_3_temp_1);
            status = m_tuple1->addItem ("p_tag_lam",           p_tag_4_temp_1);

            status = m_tuple1->addItem ("c_tag_xi",              c_tag_temp_1);
            status = m_tuple1->addItem ("c_tag_p",             c_tag_1_temp_1);
            status = m_tuple1->addItem ("c_tag_pi",            c_tag_2_temp_1);
            status = m_tuple1->addItem ("c_tag_xi_pi",         c_tag_3_temp_1);
            status = m_tuple1->addItem ("c_tag_lam",           c_tag_4_temp_1);

            status = m_tuple1->addItem ("phi_tag_xi",          phi_tag_temp_1);
            status = m_tuple1->addItem ("phi_tag_p",         phi_tag_1_temp_1);
            status = m_tuple1->addItem ("phi_tag_pi",        phi_tag_2_temp_1);
            status = m_tuple1->addItem ("phi_tag_xi_pi",     phi_tag_3_temp_1);
            status = m_tuple1->addItem ("phi_tag_lam",       phi_tag_4_temp_1);

            status = m_tuple1->addItem ("eemc_tag_p",           eemc_1_temp_1);
            status = m_tuple1->addItem ("eemc_tag_pi",          eemc_2_temp_1);
            status = m_tuple1->addItem ("eemc_tag_xi_pi",       eemc_3_temp_1);

            status = m_tuple1->addItem ("evp_tag_p",             evp_1_temp_1);
            status = m_tuple1->addItem ("evp_tag_pi",            evp_2_temp_1);
            status = m_tuple1->addItem ("evp_tag_xi_pi",         evp_3_temp_1);

            status = m_tuple1->addItem ("mdbc1",                      mdbc1_1);
            status = m_tuple1->addItem ("mdbc2",                      mdbc2_1);
            status = m_tuple1->addItem ("mcmode1",                  mcmode1_1);
            status = m_tuple1->addItem ("mcmode2",                  mcmode2_1);
            status = m_tuple1->addItem ("mcmodea",                  mcmodea_1);
            status = m_tuple1->addItem ("mcmodeb",                  mcmodeb_1);

            status = m_tuple1->addItem ("T_angle1",           T_angle1_temp_1);//lam_p
            status = m_tuple1->addItem ("T_angle2",           T_angle2_temp_1);//lam_pi
            status = m_tuple1->addItem ("T_angle3",           T_angle3_temp_1);//xi_pi
            status = m_tuple1->addItem ("T_angle4",           T_angle4_temp_1);//lam
            status = m_tuple1->addItem ("T_angle5",           T_angle5_temp_1);//xi

            status = m_tuple1->addItem ("index",              index_temp_1,0, 100);
            status = m_tuple1->addIndexedItem ("V4_1",        index_temp_1,  V4_1_temp_1);//lam_p
            status = m_tuple1->addIndexedItem ("V4_2",        index_temp_1,  V4_2_temp_1);//lam_pi
            status = m_tuple1->addIndexedItem ("V4_3",        index_temp_1,  V4_3_temp_1);//xi_pi
            status = m_tuple1->addIndexedItem ("V4_4",        index_temp_1,  V4_4_temp_1);//lam
            status = m_tuple1->addIndexedItem ("V4_5",        index_temp_1,  V4_5_temp_1);//xi

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

            status = m_tuple11->addItem ("mbc_tag",                tag_mass_bc_temp_11);
            status = m_tuple11->addItem ("delE_tag",                tag_deltaE_temp_11);
            status = m_tuple11->addItem ("tagmode",                  T_tagmode_temp_11);
            status = m_tuple11->addItem ("tagcharge",            tag_tagcharge_temp_11);
            status = m_tuple11->addItem ("mctag",                        mctag_temp_11);

            status = m_tuple11->addItem ("U_miss",                       u_miss_temp_11);
            status = m_tuple11->addItem ("E_miss",                       e_miss_temp_11);
            status = m_tuple11->addItem ("P_miss",                       p_miss_temp_11);
            status = m_tuple11->addItem ("mm2m",                         miss_m2_temp_11);
            status = m_tuple11->addItem ("q2",                           q2_temp_11);

            status = m_tuple11->addItem ("mass_tag_inv",                 tag_mass_temp_11);
            status = m_tuple11->addItem ("mee_rec_4c",                 m_ee_rec_4c);
            status = m_tuple11->addItem ("chi2_pi0",                 m_chi2_pi0);
            status = m_tuple11->addItem ("mass_tag_reco",                reco_mass_temp_11);
            status = m_tuple11->addItem ("mass_reco_xilam",              recomass_xilam_temp_11);
            status = m_tuple11->addItem ("mass_reco_xie",                recomass_xie_temp_11);
            status = m_tuple11->addItem ("mass_tag_lam",                 tag_lam_mass_temp_11);
            status = m_tuple11->addItem ("mass_tag_xi",                  tag_xi_mass_temp_11);
            status = m_tuple11->addItem ("mass_sig_lam",                 sig_lam_mass_temp_11);
            status = m_tuple11->addItem ("mass_sig_sigma0",              sig_sigma0_mass_temp_11);
            status = m_tuple11->addItem ("mass_sig_sigma0e",             mass_sig_sigma0e_temp_11);
            status = m_tuple11->addItem ("mass_xi_tag_4c",               mass_xi_tag_4c_temp_11);
            status = m_tuple11->addItem ("mass_xi_sig_4c",               mass_xi_sig_4c_temp_11);
            status = m_tuple11->addItem ("mass_jpsi_4c",                 mass_jpsi_4c_temp_11);
            status = m_tuple11->addItem ("mass_pi0_sel",                 m_mpi0_4c);

            status = m_tuple11->addItem ("esig_V_ebeam",                 esig_V_ebeam_temp_11);
            status = m_tuple11->addItem ("angle_lame_57",                angle_lame_57_temp_11);
            status = m_tuple11->addItem ("angle_xilame_58",              angle_xilame_58_temp_11);

            status = m_tuple11->addItem ("evp_e_sig",                    evp_2_temp_11);
            status = m_tuple11->addItem ("eemc_e_sig",                   eemc_2_temp_11);
            status = m_tuple11->addItem ("evp_e2_sig",                    evp_3_temp_11);
            status = m_tuple11->addItem ("eemc_e2_sig",                   eemc_3_temp_11);

            status = m_tuple11->addItem ("p_sig_p",                      p_sig_1_temp_11);
            status = m_tuple11->addItem ("p_sig_pi",                     p_sig_2_temp_11);
            status = m_tuple11->addItem ("p_sig_e",                      p_sig_3_temp_11);
            status = m_tuple11->addItem ("p_sig_e2",                     p_sig_4_temp_11);//use pion PidType in the sig-Xi rest frame
            status = m_tuple11->addItem ("p_tag_p",                      p_tag_1_temp_11);
            status = m_tuple11->addItem ("p_tag_pi",                     p_tag_2_temp_11);
            status = m_tuple11->addItem ("p_tag_pi2",                    p_tag_3_temp_11);

            status = m_tuple11->addItem ("c_sig_p_theta",                c_sig_1_temp_11);
            status = m_tuple11->addItem ("c_sig_pi_theta",               c_sig_2_temp_11);
            status = m_tuple11->addItem ("c_sig_e_theta",                c_sig_3_temp_11);
            status = m_tuple11->addItem ("c_tag_p_theta",                c_tag_1_temp_11);
            status = m_tuple11->addItem ("c_tag_pi_theta",               c_tag_2_temp_11);
            status = m_tuple11->addItem ("c_tag_pi2_theta",              c_tag_3_temp_11);
            status = m_tuple11->addItem ("c_tag_xi_theta",               p_theta_temp_11);//tag xi

            status = m_tuple11->addItem ("phi_1",                        m_phi_1_11);//sig lam_p
            status = m_tuple11->addItem ("phi_2",                        m_phi_2_11);//sig lam_pi
            status = m_tuple11->addItem ("phi_3",                        m_phi_3_11);//sig e
            status = m_tuple11->addItem ("phi_4",                        m_phi_4_11);//tag lam_p
            status = m_tuple11->addItem ("phi_5",                        m_phi_5_11);//tag lam_pi
            status = m_tuple11->addItem ("phi_6",                        m_phi_6_11);//tag xi_pi

            status = m_tuple11->addItem ("lam_tag_chi",                  lam_tag_chi_temp_11);
            status = m_tuple11->addItem ("lam_tag_len",                  lam_tag_len_temp_11);
            status = m_tuple11->addItem ("lam_tag_lenerr",               lam_tag_lenerr_temp_11);
            status = m_tuple11->addItem ("xi_tag_chi",                   xi_tag_chi_temp_11);
            status = m_tuple11->addItem ("xi_tag_len",                   xi_tag_len_temp_11);
            status = m_tuple11->addItem ("xi_tag_lenerr",                xi_tag_lenerr_temp_11);

            status = m_tuple11->addItem ("lam_sig_chi",                  lam_sig_chi_temp_11);
            status = m_tuple11->addItem ("lam_sig_len",                  lam_sig_len_temp_11);
            status = m_tuple11->addItem ("lam_sig_lenerr",               lam_sig_lenerr_temp_11);
            status = m_tuple11->addItem ("xi_sig_chi",                   xi_sig_chi_temp_11);
            status = m_tuple11->addItem ("xi_sig_len",                   xi_sig_len_temp_11);
            status = m_tuple11->addItem ("xi_sig_lenerr",                xi_sig_lenerr_temp_11);

            status = m_tuple11->addItem ("ngoodtrk",                     m_ngoodtrk_11);
            status = m_tuple11->addItem ("ngoodgam",                     m_ngoodgam_11);
            status = m_tuple11->addItem ("nchartrk",                     m_nchartrk_11);
            status = m_tuple11->addItem ("Ncharge_ex",                   Ncharge_ex_temp_11);
            status = m_tuple11->addItem ("gam_emax",                     gam_emax_temp_11);
            status = m_tuple11->addItem ("gam_e",                        gam_e_temp_11);
            status = m_tuple11->addItem ("chi_4c",                       kmfit_chi_temp_11);
            status = m_tuple11->addItem ("chi2min",                       m_chi2_min);
            status = m_tuple11->addItem ("chi_3c",                       kmfit_chi2_temp_11);

            status = m_tuple11->addItem ("angle1",                       angle1_temp_11);//sig lam_p
            status = m_tuple11->addItem ("angle2",                       angle2_temp_11);//sig lam_pi
            status = m_tuple11->addItem ("angle3",                       angle3_temp_11);//sig lam
            status = m_tuple11->addItem ("angle4",                       angle4_temp_11);//sig e
            status = m_tuple11->addItem ("angle5",                       angle5_temp_11);//sig nu_e
            status = m_tuple11->addItem ("angle6",                       angle6_temp_11);//sig xi
            status = m_tuple11->addItem ("angle7",                       angle7_temp_11);//sig gam

            status = m_tuple11->addItem ("T_angle1",                     T_angle1_temp_11);//tag lam_p
            status = m_tuple11->addItem ("T_angle2",                     T_angle2_temp_11);//tag lam_pi
            status = m_tuple11->addItem ("T_angle3",                     T_angle3_temp_11);//tag xi_pi
            status = m_tuple11->addItem ("T_angle4",                     T_angle4_temp_11);//tag lam
            status = m_tuple11->addItem ("T_angle5",                     T_angle5_temp_11);//tag xi

            status = m_tuple11->addItem ("index",                        index_temp_11,0, 100);
            status = m_tuple11->addIndexedItem ("V4_0",                  index_temp_11,  V4_0_temp_11);//sig sigma0
            status = m_tuple11->addIndexedItem ("V4_1",                  index_temp_11,  V4_1_temp_11);//sig lam
            status = m_tuple11->addIndexedItem ("V4_2",                  index_temp_11,  V4_2_temp_11);//sig p
            status = m_tuple11->addIndexedItem ("V4_3",                  index_temp_11,  V4_3_temp_11);//sig pi
            status = m_tuple11->addIndexedItem ("V4_4",                  index_temp_11,  V4_4_temp_11);//sig sigma0+e
            status = m_tuple11->addIndexedItem ("V4_5",                  index_temp_11,  V4_5_temp_11);//sig e
            status = m_tuple11->addIndexedItem ("V4_6",                  index_temp_11,  V4_6_temp_11);//sig nu_e
            status = m_tuple11->addIndexedItem ("V4_7",                  index_temp_11,  V4_7_temp_11);//sig nu_e

            status = m_tuple11->addItem ("vxy_1",       m_vxy_1_11);//sig lam_p
            status = m_tuple11->addItem ("vxy_2",       m_vxy_2_11);//sig lam_pi
            status = m_tuple11->addItem ("vxy_3",       m_vxy_3_11);//sig e
            status = m_tuple11->addItem ("vxy_4",       m_vxy_4_11);//tag lam_p
            status = m_tuple11->addItem ("vxy_5",       m_vxy_5_11);//tag lam_pi
            status = m_tuple11->addItem ("vxy_6",       m_vxy_6_11);//tag xi_pi

            status = m_tuple11->addItem ("vz_1",        m_vz_1_11);//sig lam_p
            status = m_tuple11->addItem ("vz_2",        m_vz_2_11);//sig lam_pi
            status = m_tuple11->addItem ("vz_3",        m_vz_3_11);//sig e
            status = m_tuple11->addItem ("vz_4",        m_vz_4_11);//tag lam_p
            status = m_tuple11->addItem ("vz_5",        m_vz_5_11);//tag lam_pi
            status = m_tuple11->addItem ("vz_6",        m_vz_6_11);//tag xi_pi

            status = m_tuple11->addItem ("probe_1",       m_probe_1_11);
            status = m_tuple11->addItem ("probmu_1",      m_probmu_1_11);
            status = m_tuple11->addItem ("probpi_1",      m_probpi_1_11);
            status = m_tuple11->addItem ("probk_1",       m_probk_1_11);
            status = m_tuple11->addItem ("probp_1",       m_probp_1_11);

            status = m_tuple11->addItem ("probe_2",       m_probe_2_11);
            status = m_tuple11->addItem ("probmu_2",      m_probmu_2_11);
            status = m_tuple11->addItem ("probpi_2",      m_probpi_2_11);
            status = m_tuple11->addItem ("probk_2",       m_probk_2_11);
            status = m_tuple11->addItem ("probp_2",       m_probp_2_11);

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
            status = m_tupleb->addItem ("P_1_0", p_1_temp_b_0);//xi
            status = m_tupleb->addItem ("P_2_0", p_2_temp_b_0);//lambda
            status = m_tupleb->addItem ("P_3_0", p_3_temp_b_0);//lambda p
            status = m_tupleb->addItem ("P_4_0", p_4_temp_b_0);//lambda pi
            status = m_tupleb->addItem ("P_5_0", p_5_temp_b_0);//xi pi
            status = m_tupleb->addItem ("P_6_0", p_6_temp_b_0);//e
            status = m_tupleb->addItem ("P_7_0", p_7_temp_b_0);//nue
            status = m_tupleb->addItem ("P_8_0", p_8_temp_b_0);//gamma
            status = m_tupleb->addItem ("P_9_0", p_9_temp_b_0);//nue
            status = m_tupleb->addItem ("P_10_0", p_10_temp_b_0);//gamma

            status = m_tupleb->addItem ("P_1_1", p_1_temp_b_1);//xi
            status = m_tupleb->addItem ("P_2_1", p_2_temp_b_1);//lambda
            status = m_tupleb->addItem ("P_3_1", p_3_temp_b_1);//lambda p
            status = m_tupleb->addItem ("P_4_1", p_4_temp_b_1);//lambda pi
            status = m_tupleb->addItem ("P_5_1", p_5_temp_b_1);//xi pi
            status = m_tupleb->addItem ("P_6_1", p_6_temp_b_1);//e
            status = m_tupleb->addItem ("P_7_1", p_7_temp_b_1);//nue
            status = m_tupleb->addItem ("P_8_1", p_8_temp_b_1);//gamma
            status = m_tupleb->addItem ("P_9_1", p_9_temp_b_1);//nue
            status = m_tupleb->addItem ("P_10_1", p_10_temp_b_1);//gamma

            status = m_tupleb->addItem ("index",           index_temp_b,0, 20);
            status = m_tupleb->addIndexedItem ("V4_1_0",     index_temp_b,  V4_1_temp_b_0);//xi
            status = m_tupleb->addIndexedItem ("V4_2_0",     index_temp_b,  V4_2_temp_b_0);//lambda
            status = m_tupleb->addIndexedItem ("V4_3_0",     index_temp_b,  V4_3_temp_b_0);//lambda p
            status = m_tupleb->addIndexedItem ("V4_4_0",     index_temp_b,  V4_4_temp_b_0);//lambda pi
            status = m_tupleb->addIndexedItem ("V4_5_0",     index_temp_b,  V4_5_temp_b_0);//xi pi
            status = m_tupleb->addIndexedItem ("V4_6_0",     index_temp_b,  V4_6_temp_b_0);//e
            status = m_tupleb->addIndexedItem ("V4_7_0",     index_temp_b,  V4_7_temp_b_0);//sigma+ 
            status = m_tupleb->addIndexedItem ("V4_8_0",     index_temp_b,  V4_8_temp_b_0);//p sigma+
            status = m_tupleb->addIndexedItem ("V4_9_0",     index_temp_b,  V4_9_temp_b_0);//pi0 sigma+
            status = m_tupleb->addIndexedItem ("V4_10_0",    index_temp_b,  V4_10_temp_b_0);//gamma pi0

            status = m_tupleb->addIndexedItem ("V4_1_1",     index_temp_b,  V4_1_temp_b_1);//xi
            status = m_tupleb->addIndexedItem ("V4_2_1",     index_temp_b,  V4_2_temp_b_1);//lambda
            status = m_tupleb->addIndexedItem ("V4_3_1",     index_temp_b,  V4_3_temp_b_1);//lambda p
            status = m_tupleb->addIndexedItem ("V4_4_1",     index_temp_b,  V4_4_temp_b_1);//lambda pi
            status = m_tupleb->addIndexedItem ("V4_5_1",     index_temp_b,  V4_5_temp_b_1);//xi pi
            status = m_tupleb->addIndexedItem ("V4_6_1",     index_temp_b,  V4_6_temp_b_1);//e
            status = m_tupleb->addIndexedItem ("V4_7_1",     index_temp_b,  V4_7_temp_b_1);//sigma+
            status = m_tupleb->addIndexedItem ("V4_8_1",     index_temp_b,  V4_8_temp_b_1);//p sigma+
            status = m_tupleb->addIndexedItem ("V4_9_1",     index_temp_b,  V4_9_temp_b_1);//pi0 sigma+
            status = m_tupleb->addIndexedItem ("V4_10_1",    index_temp_b,  V4_10_temp_b_1);//gamma pi0

            status = m_tupleb->addItem ("C_1_0", c_1_temp_b_0);//xi
            status = m_tupleb->addItem ("C_2_0", c_2_temp_b_0);//lambda
            status = m_tupleb->addItem ("C_3_0", c_3_temp_b_0);//lambda p
            status = m_tupleb->addItem ("C_4_0", c_4_temp_b_0);//lambda pi
            status = m_tupleb->addItem ("C_5_0", c_5_temp_b_0);//xi pi
            status = m_tupleb->addItem ("C_6_0", c_6_temp_b_0);//e
            status = m_tupleb->addItem ("C_7_0", c_7_temp_b_0);//nue
            status = m_tupleb->addItem ("C_8_0", c_8_temp_b_0);//gamma
            status = m_tupleb->addItem ("C_9_0", c_9_temp_b_0);//gamma
            status = m_tupleb->addItem ("C_10_0", c_10_temp_b_0);//gamma

            status = m_tupleb->addItem ("C_1_1", c_1_temp_b_1);//xi
            status = m_tupleb->addItem ("C_2_1", c_2_temp_b_1);//lambda
            status = m_tupleb->addItem ("C_3_1", c_3_temp_b_1);//lambda p
            status = m_tupleb->addItem ("C_4_1", c_4_temp_b_1);//lambda pi
            status = m_tupleb->addItem ("C_5_1", c_5_temp_b_1);//xi pi
            status = m_tupleb->addItem ("C_6_1", c_6_temp_b_1);//e
            status = m_tupleb->addItem ("C_7_1", c_7_temp_b_1);//nue
            status = m_tupleb->addItem ("C_8_1", c_8_temp_b_1);//gamma
            status = m_tupleb->addItem ("C_9_1", c_9_temp_b_1);//gamma
            status = m_tupleb->addItem ("C_10_1", c_10_temp_b_1);//gamma

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
StatusCode Sigmap_ee::execute() {
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
        std::cout << "Run num : " << runNo << ",  total events " << tot_events
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
    }//runNo<0



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

    Vp4 T4_xi;                    T4_xi.clear();
    Vp4 T4_xi_lambda;             T4_xi_lambda.clear();
    Vp4 T4_xi_lambda_p;           T4_xi_lambda_p.clear();
    Vp4 T4_xi_lambda_pi;          T4_xi_lambda_pi.clear();
    Vp4 T4_xi_pi;                 T4_xi_pi.clear();
    Vp4 T4_xi_e;                  T4_xi_e.clear();
    Vp4 T4_xi_sigmap;             T4_xi_sigmap.clear();
    Vp4 T4_xi_sigmap_p;           T4_xi_sigmap_p.clear();
    Vp4 T4_xi_sigmap_pi0;         T4_xi_sigmap_pi0.clear();
    Vp4 T4_xi_sigmap_gam;         T4_xi_sigmap_gam.clear();
    Vp4 T4_xi_gamma;              T4_xi_gamma.clear();//mh dont use ,by wangshun

    Vp4 T4_anti_xi;               T4_anti_xi.clear();
    Vp4 T4_anti_xi_lambda;        T4_anti_xi_lambda.clear();
    Vp4 T4_anti_xi_lambda_p;      T4_anti_xi_lambda_p.clear();
    Vp4 T4_anti_xi_lambda_pi;     T4_anti_xi_lambda_pi.clear();
    Vp4 T4_anti_xi_pi;            T4_anti_xi_pi.clear();
    Vp4 T4_anti_xi_e;             T4_anti_xi_e.clear();
    Vp4 T4_anti_xi_sigma;             T4_anti_xi_sigma.clear();
    Vp4 T4_anti_xi_sigma_p;          T4_anti_xi_sigma_p.clear();
    Vp4 T4_anti_xi_sigma_pi0;          T4_anti_xi_sigma_pi0.clear();
    Vp4 T4_anti_xi_sigma_pi0_gam;          T4_anti_xi_sigma_pi0_gam.clear();
    Vp4 T4_anti_xi_nu_e;          T4_anti_xi_nu_e.clear();//wangshun used
    Vp4 T4_anti_xi_gamma;         T4_anti_xi_gamma.clear();

    index_temp_b=4;

   if(runNo<0) {
        SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
        if(!mcParticleCol)            return StatusCode::FAILURE;

        if(mcParticleCol){
            Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();

            for (; iter_mc != mcParticleCol->end(); iter_mc++){
                if ((*iter_mc)->primaryParticle())                                   continue;
                if (!(*iter_mc)->decayFromGenerator())                               continue;

                int pdgid = (*iter_mc)->particleProperty();
                int p_mid= ((*iter_mc)->mother()).particleProperty();
                int p_m2id=(((*iter_mc)->mother()).mother()).particleProperty();
                int p_m3id=((((*iter_mc)->mother()).mother()).mother()).particleProperty();
                int p_m4id=(((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty();
                int p_m5id=((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty();

                /////////////////////////////Xi-
                if(pdgid==3312||p_mid==3312||p_m2id==3312||p_m3id==3312||p_m4id==3312||p_m5id==3312){//Xi- 3312
                   if(pdgid==3312){//Xi- 3312
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi.push_back(P4_1);

                        p_1_temp_b_1=P4_1.rho();
                        c_1_temp_b_1=P4_1.cosTheta();
                        V4_1_temp_b_1[0]=P4_1.px();
                        V4_1_temp_b_1[1]=P4_1.py();
                        V4_1_temp_b_1[2]=P4_1.pz();
                        V4_1_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==3122){//Lambda0 3122
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_lambda.push_back(P4_1);

                        p_2_temp_b_1=P4_1.rho();
                        c_2_temp_b_1=P4_1.cosTheta();
                        V4_2_temp_b_1[0]=P4_1.px();
                        V4_2_temp_b_1[1]=P4_1.py();
                        V4_2_temp_b_1[2]=P4_1.pz();
                        V4_2_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==2212&&p_mid==3122&&p_m2id==3312){//proton+ 2212
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_lambda_p.push_back(P4_1);

                        p_3_temp_b_1=P4_1.rho();
                        c_3_temp_b_1=P4_1.cosTheta();
                        V4_3_temp_b_1[0]=P4_1.px();
                        V4_3_temp_b_1[1]=P4_1.py();
                        V4_3_temp_b_1[2]=P4_1.pz();
                        V4_3_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==-211&&p_mid==3122&&p_m2id==3312){//pi- -211
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_lambda_pi.push_back(P4_1);

                        p_4_temp_b_1=P4_1.rho();
                        c_4_temp_b_1=P4_1.cosTheta();
                        V4_4_temp_b_1[0]=P4_1.px();
                        V4_4_temp_b_1[1]=P4_1.py();
                        V4_4_temp_b_1[2]=P4_1.pz();
                        V4_4_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==-211&&p_mid==3312){//pi- -211
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_pi.push_back(P4_1);

                        p_5_temp_b_1=P4_1.rho();
                        c_5_temp_b_1=P4_1.cosTheta();
                        V4_5_temp_b_1[0]=P4_1.px();
                        V4_5_temp_b_1[1]=P4_1.py();
                        V4_5_temp_b_1[2]=P4_1.pz();
                        V4_5_temp_b_1[3]=P4_1.e();

                    }

                    if(pdgid==11){//electron 11
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_e.push_back(P4_1);

                        p_6_temp_b_1=P4_1.rho();
                        c_6_temp_b_1=P4_1.cosTheta();
                        V4_6_temp_b_1[0]=P4_1.px();
                        V4_6_temp_b_1[1]=P4_1.py();
                        V4_6_temp_b_1[2]=P4_1.pz();
                        V4_6_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==3222){//sigma+ 3222
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_sigmap.push_back(P4_1);

                        p_7_temp_b_1=P4_1.rho();
                        c_7_temp_b_1=P4_1.cosTheta();
                        V4_7_temp_b_1[0]=P4_1.px();
                        V4_7_temp_b_1[1]=P4_1.py();
                        V4_7_temp_b_1[2]=P4_1.pz();
                        V4_7_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==2212&&p_mid==3312&&p_m2id==3312){//p //sigma+ //xi-
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_sigmap_p.push_back(P4_1);

                        p_8_temp_b_1=P4_1.rho();
                        c_8_temp_b_1=P4_1.cosTheta();
                        V4_8_temp_b_1[0]=P4_1.px();
                        V4_8_temp_b_1[1]=P4_1.py();
                        V4_8_temp_b_1[2]=P4_1.pz();
                        V4_8_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==111&&p_mid==3222){//pi0 111 
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_sigmap_pi0.push_back(P4_1);

                        p_9_temp_b_1=P4_1.rho();
                        c_9_temp_b_1=P4_1.cosTheta();
                        V4_9_temp_b_1[0]=P4_1.px();
                        V4_9_temp_b_1[1]=P4_1.py();
                        V4_9_temp_b_1[2]=P4_1.pz();
                        V4_9_temp_b_1[3]=P4_1.e();

                    }
                    if(pdgid==22&&p_mid==111&&p_m2id==3222){//gamma 22 
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_xi_sigmap_gam.push_back(P4_1);

                        p_10_temp_b_1=P4_1.rho();
                        c_10_temp_b_1=P4_1.cosTheta();
                        V4_10_temp_b_1[0]=P4_1.px();
                        V4_10_temp_b_1[1]=P4_1.py();
                        V4_10_temp_b_1[2]=P4_1.pz();
                        V4_10_temp_b_1[3]=P4_1.e();

                    }

                }

                /////////////////////////////anti-Xi+
                if(pdgid==-3312||p_mid==-3312||p_m2id==-3312||p_m3id==-3312||p_m4id==-3312||p_m5id==-3312){//anti-Xi+ -3312
                    if(pdgid==-3312){//anti-Xi+ -3312
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi.push_back(P4_1);

                        p_1_temp_b_0=P4_1.rho();
                        c_1_temp_b_0=P4_1.cosTheta();
                        V4_1_temp_b_0[0]=P4_1.px();
                        V4_1_temp_b_0[1]=P4_1.py();
                        V4_1_temp_b_0[2]=P4_1.pz();
                        V4_1_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==-3122){//anti-Lambda0 -3122
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_lambda.push_back(P4_1);

                        p_2_temp_b_0=P4_1.rho();
                        c_2_temp_b_0=P4_1.cosTheta();
                        V4_2_temp_b_0[0]=P4_1.px();
                        V4_2_temp_b_0[1]=P4_1.py();
                        V4_2_temp_b_0[2]=P4_1.pz();
                        V4_2_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==-2212&&p_mid==-3122&&p_m2id==-3312){//anti-proton- -2212
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_lambda_p.push_back(P4_1);

                        p_3_temp_b_0=P4_1.rho();
                        c_3_temp_b_0=P4_1.cosTheta();
                        V4_3_temp_b_0[0]=P4_1.px();
                        V4_3_temp_b_0[1]=P4_1.py();
                        V4_3_temp_b_0[2]=P4_1.pz();
                        V4_3_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==211&&p_mid==-3122&&p_m2id==-3312){//pi+ 211 anti-lambda-3122
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_lambda_pi.push_back(P4_1);

                        p_4_temp_b_0=P4_1.rho();
                        c_4_temp_b_0=P4_1.cosTheta();
                        V4_4_temp_b_0[0]=P4_1.px();
                        V4_4_temp_b_0[1]=P4_1.py();
                        V4_4_temp_b_0[2]=P4_1.pz();
                        V4_4_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==211&&p_mid==-3312){//pi+ 211
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_pi.push_back(P4_1);

                        p_5_temp_b_0=P4_1.rho();
                        c_5_temp_b_0=P4_1.cosTheta();
                        V4_5_temp_b_0[0]=P4_1.px();
                        V4_5_temp_b_0[1]=P4_1.py();
                        V4_5_temp_b_0[2]=P4_1.pz();
                        V4_5_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==-11&&p_mid==-3312){//positron -11
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_e.push_back(P4_1);

                        p_6_temp_b_0=P4_1.rho();
                        c_6_temp_b_0=P4_1.cosTheta();
                        V4_6_temp_b_0[0]=P4_1.px();
                        V4_6_temp_b_0[1]=P4_1.py();
                        V4_6_temp_b_0[2]=P4_1.pz();
                        V4_6_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==-3222&&p_mid==-3312){//anti-sigma- -3222
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_sigma.push_back(P4_1);

                        p_7_temp_b_0=P4_1.rho();
                        c_7_temp_b_0=P4_1.cosTheta();
                        V4_7_temp_b_0[0]=P4_1.px();
                        V4_7_temp_b_0[1]=P4_1.py();
                        V4_7_temp_b_0[2]=P4_1.pz();
                        V4_7_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==-2212&&p_mid==-3222&&p_m2id==-3312){//anti-p //anti-sigma- //xi-
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_sigma_p.push_back(P4_1);

                        p_8_temp_b_0=P4_1.rho();
                        c_8_temp_b_0=P4_1.cosTheta();
                        V4_8_temp_b_0[0]=P4_1.px();
                        V4_8_temp_b_0[1]=P4_1.py();
                        V4_8_temp_b_0[2]=P4_1.pz();
                        V4_8_temp_b_0[3]=P4_1.e();

                    }
                    //if(pdgid==-2212&&p_mid==-3222&&p_m2id==-3312){//pi0 111 
                    if(pdgid==111&&p_mid==-3222&&p_m2id==-3312){//pi0 111 
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_sigma_pi0.push_back(P4_1);

                        p_9_temp_b_0=P4_1.rho();
                        c_9_temp_b_0=P4_1.cosTheta();
                        V4_9_temp_b_0[0]=P4_1.px();
                        V4_9_temp_b_0[1]=P4_1.py();
                        V4_9_temp_b_0[2]=P4_1.pz();
                        V4_9_temp_b_0[3]=P4_1.e();

                    }
                    if(pdgid==22&&p_mid==111&&p_m2id==-3222){//gam 22 
                        HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
                        P4_1.boost(-0.011,0,0);
                        T4_anti_xi_sigma_pi0_gam.push_back(P4_1);

                        p_10_temp_b_0=P4_1.rho();
                        c_10_temp_b_0=P4_1.cosTheta();
                        V4_10_temp_b_0[0]=P4_1.px();
                        V4_10_temp_b_0[1]=P4_1.py();
                        V4_10_temp_b_0[2]=P4_1.pz();
                        V4_10_temp_b_0[3]=P4_1.e();

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

    Vdou tag_mass_lam;       tag_mass_lam.clear();
    Vdou tag_mass_reco;      tag_mass_reco.clear();

    Vdou Lamlen;       Lamlen.clear();
    Vdou Lamlenerr;    Lamlenerr.clear();
    Vdou Lamchi;       Lamchi.clear();
    Vdou Xi_Lamlen;    Xi_Lamlen.clear();
    Vdou Xi_Lamlenerr; Xi_Lamlenerr.clear();
    Vdou Xi_Lamchi;    Xi_Lamchi.clear();
    Vdou Xilen;        Xilen.clear();
    Vdou Xilenerr;     Xilenerr.clear();
    Vdou Xichi;        Xichi.clear();
    Vdou Lam_p_eemc;   Lam_p_eemc.clear();
    Vdou Lam_p_evp;    Lam_p_evp.clear();
    Vdou Lam_pi_eemc;  Lam_pi_eemc.clear();
    Vdou Lam_pi_evp;   Lam_pi_evp.clear();
    Vdou Xi_Lam_p_eemc;   Xi_Lam_p_eemc.clear();
    Vdou Xi_Lam_p_evp;    Xi_Lam_p_evp.clear();
    Vdou Xi_Lam_pi_eemc;  Xi_Lam_pi_eemc.clear();
    Vdou Xi_Lam_pi_evp;   Xi_Lam_pi_evp.clear();
    Vdou Xi_pi_eemc;   Xi_pi_eemc.clear();
    Vdou Xi_pi_evp;    Xi_pi_evp.clear();

    Vdou p_eemc;   p_eemc.clear();
    Vdou p_evp;    p_evp.clear();
    Vdou e_eemc;   e_eemc.clear();
    Vdou e_evp;    e_evp.clear();
    Vdou pi_eemc;  pi_eemc.clear();
    Vdou pi_evp;   pi_evp.clear();

    Vdou tag_Lamlen;       tag_Lamlen.clear();
    Vdou tag_Lamlenerr;    tag_Lamlenerr.clear();
    Vdou tag_Lamchi;       tag_Lamchi.clear();
    Vdou tag_Xilen;        tag_Xilen.clear();
    Vdou tag_Xilenerr;     tag_Xilenerr.clear();
    Vdou tag_Xichi;        tag_Xichi.clear();
    Vdou tag_Lam_p_eemc;   tag_Lam_p_eemc.clear();
    Vdou tag_Lam_p_evp;    tag_Lam_p_evp.clear();
    Vdou tag_Lam_pi_eemc;  tag_Lam_pi_eemc.clear();
    Vdou tag_Lam_pi_evp;   tag_Lam_pi_evp.clear();
    Vdou tag_Xi_pi_eemc;   tag_Xi_pi_eemc.clear();
    Vdou tag_Xi_pi_evp;    tag_Xi_pi_evp.clear();

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
    Vint    tag_piid2;             tag_piid2.clear(); 
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
    Vint    Lamid_pi;              Lamid_pi.clear();
    Vint    Lamid_p;               Lamid_p.clear();
    Vint    Lamcharge;             Lamcharge.clear();
    Vint    Xi_Lamid_pi;           Xi_Lamid_pi.clear();
    Vint    Xi_Lamid_p;            Xi_Lamid_p.clear();
    Vint    Xiid_pi;               Xiid_pi.clear();
    Vint    Xi_Lamcharge;          Xi_Lamcharge.clear();
    Vint    Xicharge;              Xicharge.clear();
    Vint    Xi_Picharge;           Xi_Picharge.clear();
    Vint    Xi_Pcharge;            Xi_Pcharge.clear();



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
    Vp4    Xivector;               Xivector.clear();
    Vp4    Xi_Lamvector;           Xi_Lamvector.clear();
    Vp4    Xi_Lam_pi;              Xi_Lam_pi.clear();
    Vp4    Xi_Lam_p;               Xi_Lam_p.clear();
    Vp4    Xi_pi;                  Xi_pi.clear();
    Vp4    tag_Lamvector;          tag_Lamvector.clear();
    Vp4    tag_Xivector;           tag_Xivector.clear();
    Vp4    tag_Lam_pi;             tag_Lam_pi.clear();
    Vp4    tag_Xi_pi;              tag_Xi_pi.clear();
    Vp4    tag_Lam_p;              tag_Lam_p.clear();
    //Vp4    ptag_temp;             ptag_temp.clear();//add by mh 2020.0915

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
    Vtrack  Trk_xi;                Trk_xi.clear();
    Vtrack  Trk_xi_pi;             Trk_xi_pi.clear();
    Vtrack  Trk_xi_lam;            Trk_xi_lam.clear();
    Vtrack  Trk_xi_lam_pi;         Trk_xi_lam_pi.clear();
    Vtrack  Trk_xi_lam_p;          Trk_xi_lam_p.clear();
    Vtrack  Trk_xi_tag;            Trk_xi_tag.clear();
    Vtrack  trk_lam_tag;           trk_lam_tag.clear();
    Vtrack  trk_lam_pi_tag;        trk_lam_pi_tag.clear();
    Vtrack  trk_lam_p_tag;         trk_lam_p_tag.clear();
    Vtrack  trk_pi_tag;            trk_pi_tag.clear();
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
 //       if (  dr1 >= 1.0) continue;
   //     if (drz >= 10.0) continue;
        if ( fabs(costheta) >= 0.93) continue;

     /*   pid->init();
        pid->setMethod(pid->methodProbability());
        pid->setChiMinCut(4);
        pid->setRecTrack(*itTrk);
        pid->usePidSys(pid->useDedx() | pid->useTof()); // use PID sub-system

        pid->identify(pid->onlyPion() | pid->onlyKaon() );    // seperater Pion/Kaon

        pid->calculate();
        if(!(pid->IsPidInfoValid())) continue;
        if(pid->probKaon() <= 0) continue;
        if(pid->probKaon()<=pid->probPion() ) continue;
*/
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
    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all kaon successfully. " << endl;

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
        if ( fabs(costheta) >= 0.93) continue;

        /*
           pid->init();
           pid->setMethod(pid->methodProbability());
           pid->setChiMinCut(4);
           pid->setRecTrack(*itTrk);
           pid->usePidSys(pid->useDedx() | pid->useTof() ); // use PID sub-system
           pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());   
           pid->calculate();

           if(pid->probPion()<= pid->probKaon()) continue;
           if(pid->probPion()<= pid->probProton()) continue;
           if(pid->probPion()<= 0) continue;
           */

        WTrackParameter pi(xmass[2],mdcKalTrk->getZHelix(),mdcKalTrk->getZError());
        HepVector pip_val = HepVector(7,0);
        pip_val = pi.w();
        HepLorentzVector P_PI(pip_val[0],pip_val[1],pip_val[2],pip_val[3]);
        P_PI.boost(-0.011,0,0);

        double ppi=P_PI.rho();

        if ( (*itTrk)->isEmcShowerValid() )//pi
        {    
            RecEmcShower* emcTrk = (*itTrk)->emcShower();
            double eemc = emcTrk->energy();
            double evp = eemc/ppi;
            pi_eemc.push_back(eemc);
            pi_evp.push_back(evp);
        }    
        else{
            pi_eemc.push_back(0);
            pi_evp.push_back(0);
        }    



        //    Piprob.push_back(pid->probPion());
        //    Kprob_pi.push_back(pid->probKaon());

        Trk_pi.push_back(pi);
        Picharge.push_back(mdcKalTrk->charge());
        Piid.push_back(j);
        Pivector.push_back(P_PI);

        x0[0]++;

    }
    int pinumber=Pivector.size();
    if(pinumber<2) return StatusCode::SUCCESS;

    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all pion successfully. " << endl;

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
    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all kso successfully. " << endl;

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
/*
 //writen by wangshun
    //test for reconstruction of gamma
    double test_angle_cut=999;
    int best_gam_id=999;
    int flag_gam=0;
    for (int kk=0;kk<gamnumber;kk++){
        if(!(runNo<0&&T4_xi_gamma.size()>0)) continue;
        double T_angle_test=((Gamvector[kk].vect()).angle(T4_xi_gamma[0].vect()))/(CLHEP::pi)*180;
        if (T_angle_test<test_angle_cut){
            best_gam_id=kk;
            flag_gam=1;
        }
    }

    if(flag_gam==1&&runNo<0&&T4_xi_gamma.size()>0){
        //cout<<"rec_gam:\t"<<Gamvector[best_gam_id].px()<<"\t"<<Gamvector[best_gam_id].py()<<"\t"<<Gamvector[best_gam_id].pz()<<"\t"<<Gamvector[best_gam_id].e()<<endl;
        //cout<<"truth:\t"<<T4_xi_gamma[0].px()<<"\t"<<T4_xi_gamma[0].py()<<"\t"<<T4_xi_gamma[0].pz()<<"\t"<<T4_xi_gamma[0].e()<<endl;
        double delE_gam=Gamvector[best_gam_id].e()-T4_xi_gamma[0].e();
        delE_gam_temp_1=delE_gam;
    }
*/

    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all gamma successfully. " << endl;
    if (gamnumber>100) return StatusCode::SUCCESS;

    ////////////////////////////////select all pi0
    for(int x = 0; x < gamnumber - 1; x++){
        for(int y = x+1; y < gamnumber; y++) {

            HepLorentzVector p2g = Gamvector[x] + Gamvector[y];
            //m_mpi0 = p2g.m();//save by mh 2020.0915
            //if (p2g.m()>0.15 ||p2g.m()<0.115) continue;

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
    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all pi0 successfully. " << endl;

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
    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all eta successfully. " << endl;

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

        Muprob.push_back(pid->probMuon());

        Eprob_mu.push_back(pid->probElectron());
        Kprob_mu.push_back(pid->probKaon());
        Piprob_mu.push_back(pid->probPion());

        Trk_mu.push_back(mu);
        Mucharge.push_back(mdcKalTrk->charge());
        Muid.push_back(k);
        Muvector.push_back(P_MU);
    }
    int munumber=Muvector.size();
    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all muon successfully. " << endl;

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
        //      if (  dr1 >= 1.0) continue;
        //      if (drz >= 10.0) continue;

        if ( fabs(costheta) >= 0.93) continue;      
/*
        
           pid->init();
           pid->setMethod(pid->methodProbability());
           pid->setChiMinCut(4);
           pid->setRecTrack(*itTrk);
           pid->usePidSys(pid->useDedx() | pid->useTof() | pid->useEmc()); // use PID sub-system

           pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() );   
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

        
           Eprob.push_back(pid->probElectron());

           Kprob_e.push_back(pid->probKaon());
           Piprob_e.push_back(pid->probPion());
           Muprob_e.push_back(pid->probMuon());
           
        Echarge.push_back(mdcKalTrk->charge());
        Eid.push_back(i);
        Evector.push_back(P_E);
       Trk_e.push_back(e);
        x0[1]++;
    }
    int enumber=Evector.size();


    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all electron/positron successfully. " << endl;

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
        //if (  dr1 >= 1.0) continue;
        //if (drz >= 10.0) continue;

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

        x0[2]++;
    }
    int pnumber=Pvector.size();
    if(pnumber<1) return StatusCode::SUCCESS;

    if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all proton successfully. " << endl;


   //meihong20201207 
    ////////////////////////////////select the best lambda which has the closest mass with lambda 
    double mini_m_lam=0.2;
    int flag_lam=0;
    int best_lam_pid=-1;
    int best_lam_piid=-1;

    for(int i = 0; i < Pvector.size();i++) { EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Pid[i];
    if(!(*itTrk)->isMdcKalTrackValid()) continue;
    RecMdcKalTrack*  mdcKalTrk1 = (*itTrk)->mdcKalTrack();
    if(abs(mdcKalTrk1->charge()) != 1) continue;


    for(int j = 0; j < Pivector.size();j++) {
    EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + Piid[j];
    if(!(*itTrk2)->isMdcKalTrackValid()) continue;
    RecMdcKalTrack*  mdcKalTrk2 = (*itTrk2)->mdcKalTrack();
    if((mdcKalTrk2->charge()+mdcKalTrk1->charge())!=0) continue;

    WTrackParameter vp=Trk_p[i];
    WTrackParameter vpi=Trk_pi[j];

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

    //****************** vertex fit lambda -> xi **********************

    for(int k = 0; k < Pivector.size();k++) {
        if(Piid[j]==Piid[k]) continue;
        EvtRecTrackIterator itTrk3 = evtRecTrkCol->begin() + Piid[k];
        if(!(*itTrk3)->isMdcKalTrackValid()) continue;
        RecMdcKalTrack*  mdcKalTrk3 = (*itTrk3)->mdcKalTrack();
        if((mdcKalTrk3->charge()+mdcKalTrk1->charge())!=0) continue;
        WTrackParameter vpi2=Trk_pi[k];

        Hep3Vector ip2(0,0,0);
        HepSymMatrix ipEx2(3, 0);
        IVertexDbSvc* vtxsvc2;
        Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc2);
        if (vtxsvc2->isVertexValid())
        {
            double* dbv2 = vtxsvc2->PrimaryVertex();
            double* vv2  = vtxsvc2->SigmaPrimaryVertex();
            ip2.setX(dbv2[0]);
            ip2.setY(dbv2[1]);
            ip2.setZ(dbv2[2]);
            ipEx2[0][0] = vv2[0] * vv2[0];
            ipEx2[1][1] = vv2[1] * vv2[1];
            ipEx2[2][2] = vv2[2] * vv2[2];
        }
        else{
            continue;}

        VertexParameter bs2;
        bs2.setVx(ip2);
        bs2.setEvx(ipEx2);
        ///////////////////////////////////////////////////////////////////
        //  set a common vertex with huge error
        ///////////////////////////////////////////////////////////////////
        HepPoint3D    vx2(0., 0., 0.);
        HepSymMatrix  Evx2(3, 0);
        double bx2 = 1E+6;
        double by2 = 1E+6;
        double bz2 = 1E+6;
        Evx2[0][0] = bx2 * bx2;
        Evx2[1][1] = by2 * by2;
        Evx2[2][2] = bz2 * bz2;
        VertexParameter vxpar2;
        vxpar2.setVx(vx2);
        vxpar2.setEvx(Evx2);
        ///////////////////////////////////////////////////////////////////
        //  do vertex fit
        ///////////////////////////////////////////////////////////////////
        VertexFit *vtxfit2 = VertexFit::instance();
        vtxfit2->init();
        vtxfit2->setChisqCut(100000,1.0e-3);

        vtxfit2->AddTrack(0, vpi2);
        vtxfit2->AddTrack(1, wlam_Trk);
        vtxfit2->AddVertex(0, vxpar2, 0, 1);
        if (!(vtxfit2->Fit(0))) continue;
        vtxfit2->Swim(0);
        vtxfit2->BuildVirtualParticle(0);
        double vtx_chisq2 = vtxfit2->chisq(0);
        WTrackParameter wxi_Trk = vtxfit2->wVirtualTrack(0);
        WTrackParameter wpi2  = vtxfit2->wtrk(0);
        WTrackParameter wlam  = vtxfit2->wtrk(1);

        ///////////////////////////////////////////////////////////////////
        //  do second vertex fit
        ///////////////////////////////////////////////////////////////////
        SecondVertexFit *svtxfit = SecondVertexFit::instance();
        svtxfit->init();
        svtxfit->setChisqCut(100000,1.0e-2);
        // svtxfit->setPrimaryVertex(bs);
        // svtxfit->AddTrack(0, wlam);
        svtxfit->setPrimaryVertex(vtxfit2->vpar(0));
        svtxfit->AddTrack(0, wlam_Trk);
        svtxfit->setVpar(vtxfit->vpar(0));
        if (!svtxfit->Fit()) continue;
        double len = svtxfit->decayLength();
        double lenerr = svtxfit->decayLengthError();
        WTrackParameter wlam_svt=svtxfit->wpar();
        HepLorentzVector plam_temp = svtxfit->p4par();
        plam_temp.boost(-0.011,0,0);
        if(plam_temp.m()>1.3||plam_temp.m()<0.9) continue;
        double del_m_lam=fabs(plam_temp.m()-mlambda);

        if(del_m_lam<mini_m_lam){
            mini_m_lam=del_m_lam;
            best_lam_pid=i;
            best_lam_piid=j;
            flag_lam=1;
        }

    }//for xi-pi loop
}//for lambda-pi loop
}//for lamba-p loop

if(flag_lam==1){
    x0[3]++;
}

//
///////////liumh 0831 read begin///////////
//
////////////////////////////////select all xi
//     if(flag_lam==1) { 
for(int i = 0; i < Pvector.size();i++) {
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Pid[i];
    if(!(*itTrk)->isMdcKalTrackValid()) continue;
    RecMdcKalTrack*  mdcKalTrk1 = (*itTrk)->mdcKalTrack();
    if(abs(mdcKalTrk1->charge()) != 1) continue;

    for(int j = 0; j < Pivector.size();j++) {
        EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + Piid[j];
        if(!(*itTrk2)->isMdcKalTrackValid()) continue;
        RecMdcKalTrack*  mdcKalTrk2 = (*itTrk2)->mdcKalTrack();
        if((mdcKalTrk2->charge()+mdcKalTrk1->charge())!=0) continue;

        WTrackParameter vp=Trk_p[i];
        WTrackParameter vpi=Trk_pi[j];


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

        vtxfit->AddTrack(0, vpi);
        vtxfit->AddTrack(1, vp);
        vtxfit->AddVertex(0, vxpar, 0, 1);
        if (!(vtxfit->Fit(0))) continue;
        vtxfit->Swim(0);
        vtxfit->BuildVirtualParticle(0);
        double vtx_chisq = vtxfit->chisq(0);
        WTrackParameter wlam_Trk = vtxfit->wVirtualTrack(0);////what?
        WTrackParameter wpi  = vtxfit->wtrk(0);
        WTrackParameter wp  = vtxfit->wtrk(1);
        //////mh??////////
        HepVector p_pi_val = HepVector(7,0);//track init
        p_pi_val = wpi.w();///w: get P4
        HepLorentzVector L_Pi(p_pi_val[0],p_pi_val[1],p_pi_val[2],p_pi_val[3]);
        L_Pi.boost(-0.011,0,0);

        HepVector p_p_val = HepVector(7,0);
        p_p_val = wp.w();
        HepLorentzVector L_P(p_p_val[0],p_p_val[1],p_p_val[2],p_p_val[3]);
        L_P.boost(-0.011,0,0);

        double pp  = L_P.rho();
        double ppi = L_Pi.rho();
        double eemc_p=0;
        double evp_p=0;
        double eemc_pi=0;
        double evp_pi=0;


        if ( (*itTrk)->isEmcShowerValid() )//p
        {
            RecEmcShower* emcTrk = (*itTrk)->emcShower();
            eemc_p = emcTrk->energy();
            evp_p = eemc_p/pp;
            Lam_p_eemc.push_back(eemc_p);
            Lam_p_evp.push_back(evp_p);
        }
        else{
            Lam_p_eemc.push_back(0);
            Lam_p_evp.push_back(0);
        }////already selected p from lambda //mh

        if ( (*itTrk2)->isEmcShowerValid() )//pi
        {
            RecEmcShower* emcTrk = (*itTrk2)->emcShower();
            eemc_pi = emcTrk->energy();
            evp_pi = eemc_pi/ppi;
            Lam_pi_eemc.push_back(eemc_pi);
            Lam_pi_evp.push_back(evp_pi);
        }
        else{
            Lam_pi_eemc.push_back(0);
            Lam_pi_evp.push_back(0);
        }////already selected pi from lambda //mh

        //****************** vertex fit lambda -> xi **********************

        for(int k = 0; k < Pivector.size();k++)//take another pi
        {
            if(Piid[j]==Piid[k]) continue;
            EvtRecTrackIterator itTrk3 = evtRecTrkCol->begin() + Piid[k];
            if(!(*itTrk3)->isMdcKalTrackValid()) continue;
            RecMdcKalTrack*  mdcKalTrk3 = (*itTrk3)->mdcKalTrack();
            if((mdcKalTrk3->charge()+mdcKalTrk1->charge())!=0) continue;
            WTrackParameter vpi2=Trk_pi[k];

            Hep3Vector ip2(0,0,0);
            HepSymMatrix ipEx2(3, 0);
            IVertexDbSvc* vtxsvc2;
            Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc2);
            if (vtxsvc2->isVertexValid())
            {
                double* dbv2 = vtxsvc2->PrimaryVertex();
                double* vv2  = vtxsvc2->SigmaPrimaryVertex();
                ip2.setX(dbv2[0]);
                ip2.setY(dbv2[1]);
                ip2.setZ(dbv2[2]);
                ipEx2[0][0] = vv2[0] * vv2[0];
                ipEx2[1][1] = vv2[1] * vv2[1];
                ipEx2[2][2] = vv2[2] * vv2[2];
            }
            else{
                continue;}

            VertexParameter bs2;
            bs2.setVx(ip2);
            bs2.setEvx(ipEx2);
            ///////////////////////////////////////////////////////////////////
            //  set a common vertex with huge error
            ///////////////////////////////////////////////////////////////////
            HepPoint3D    vx2(0., 0., 0.);
            HepSymMatrix  Evx2(3, 0);
            double bx2 = 1E+6;
            double by2 = 1E+6;
            double bz2 = 1E+6;
            Evx2[0][0] = bx2 * bx2;
            Evx2[1][1] = by2 * by2;
            Evx2[2][2] = bz2 * bz2;
            VertexParameter vxpar2;
            vxpar2.setVx(vx2);
            vxpar2.setEvx(Evx2);
            ///////////////////////////////////////////////////////////////////
            //  do vertex fit for lambda and pi -> xi 
            ///////////////////////////////////////////////////////////////////
            VertexFit *vtxfit2 = VertexFit::instance();
            vtxfit2->init();
            vtxfit2->setChisqCut(100000,1.0e-3);

            vtxfit2->AddTrack(0, vpi2);
            vtxfit2->AddTrack(1, wlam_Trk);
            vtxfit2->AddVertex(0, vxpar2, 0, 1);
            if (!(vtxfit2->Fit(0))) continue;
            vtxfit2->Swim(0);
            vtxfit2->BuildVirtualParticle(0);
            double vtx_chisq2 = vtxfit2->chisq(0);
            WTrackParameter wxi_Trk = vtxfit2->wVirtualTrack(0);
            WTrackParameter wpi2  = vtxfit2->wtrk(0);// pi2 from xi
            WTrackParameter wlam  = vtxfit2->wtrk(1);

            ///////////////////////////////////////////////////////////////////
            //  do second vertex fit
            ///////////////////////////////////////////////////////////////////
            SecondVertexFit *svtxfit = SecondVertexFit::instance();
            svtxfit->init();
            svtxfit->setChisqCut(100000,1.0e-2);
            // svtxfit->setPrimaryVertex(bs);
            // svtxfit->AddTrack(0, wlam);
            svtxfit->setPrimaryVertex(vtxfit2->vpar(0));
            svtxfit->AddTrack(0, wlam_Trk);//mh add a track for lamdba
            svtxfit->setVpar(vtxfit->vpar(0));//mh set to first vtx
            //vtxfit is for the vtx get from p an pi (lambda decay place)
            //vtxfit2 is for the vtx2 get from pi and lambda (lambda generate place)->>xi decay place
            //the distance between vtx  and vtx2 is the decay legth of lambda
            if (!svtxfit->Fit()) continue;
            double len = svtxfit->decayLength();
            double lenerr = svtxfit->decayLengthError();
            WTrackParameter wlam_svt=svtxfit->wpar();
            HepLorentzVector plam_temp = svtxfit->p4par();
            plam_temp.boost(-0.011,0,0);
            if(plam_temp.m()>1.3||plam_temp.m()<0.9) continue;
            x0[3]++;

            //****************** second vertex fit lambda -> xi **********************

            SecondVertexFit *svtxfit2 = SecondVertexFit::instance();
            svtxfit2->init();
            svtxfit2->setChisqCut(100000,1.0e-2);
            svtxfit2->setPrimaryVertex(bs2);
            svtxfit2->AddTrack(0, vtxfit2->wVirtualTrack(0));//for xi 
            //vtxfit2 is for the vtx get from pi and lambda ->>xi decay place
            svtxfit2->setVpar(vtxfit2->vpar(0));
            if (!svtxfit2->Fit()) continue;
            double len2 = svtxfit2->decayLength();
            double lenerr2 = svtxfit2->decayLengthError();
            //the decay length of xi
            WTrackParameter wxi_svt=svtxfit2->wpar();
            HepLorentzVector pxi_temp = svtxfit2->p4par();
            pxi_temp.boost(-0.011,0,0);
            if(pxi_temp.m()<1.1||pxi_temp.m()>1.5) continue;


            HepVector p_lam_val = HepVector(7,0);
            p_lam_val = wlam_svt.w();
            HepLorentzVector L_Lam(p_lam_val[0],p_lam_val[1],p_lam_val[2],p_lam_val[3]);
            L_Lam.boost(-0.011,0,0);

            HepVector p_pi2_val = HepVector(7,0);
            p_pi2_val = wpi2.w();//pi2 from xi
            HepLorentzVector L_Pi2(p_pi2_val[0],p_pi2_val[1],p_pi2_val[2],p_pi2_val[3]);
            L_Pi2.boost(-0.011,0,0);

            double ppi2 = L_Pi2.rho();

            if ( (*itTrk3)->isEmcShowerValid() )//xi_pi
            {
                RecEmcShower* emcTrk = (*itTrk3)->emcShower();
                double eemc = emcTrk->energy();
                double evp = eemc/ppi2;
                Xi_pi_eemc.push_back(eemc);
                Xi_pi_evp.push_back(evp);
            }
            else{
                Xi_pi_eemc.push_back(0);
                Xi_pi_evp.push_back(0);
            }

            Xi_Lam_pi.push_back(L_Pi);
            Xi_Lam_p.push_back(L_P);
            Xi_Lamcharge.push_back(Pcharge[i]);
            Xi_Lamvector.push_back(plam_temp);
            Xi_Lamid_p.push_back(Pid[i]);
            Xi_Lamid_pi.push_back(Piid[j]);
            Xi_Lamlen.push_back(len);
            Xi_Lamlenerr.push_back(lenerr);

            Xi_Lamchi.push_back(vtx_chisq);
            Trk_xi_lam.push_back(wlam_svt);
            Trk_xi_lam_pi.push_back(wpi);
            Trk_xi_lam_p.push_back(wp);

            Xi_Lam_p_eemc.push_back(eemc_p);
            Xi_Lam_p_evp.push_back(evp_p);
            Xi_Lam_pi_eemc.push_back(eemc_pi);
            Xi_Lam_pi_evp.push_back(evp_pi);

            Xi_pi.push_back(L_Pi2);
            Xicharge.push_back(Picharge[j]);
            Xi_Picharge.push_back(mdcKalTrk3->charge());
            Xi_Pcharge.push_back(mdcKalTrk1->charge());
            Xivector.push_back(pxi_temp);
            Xiid_pi.push_back(Piid[k]);
            Xilen.push_back(len2);
            Xilenerr.push_back(lenerr2);

            Xichi.push_back(vtx_chisq2);
            Trk_xi.push_back(wxi_svt);
            Trk_xi_pi.push_back(wpi2);

            x0[4]++;

        }//for xi-pi loop
    }//for lam-pi loop
}//for lam-p loop
//}//flag_lam==1
int xinumber=Xivector.size();
if(m_debug)     cout << "/ ------ [ Sigmap_eeAlg.execute ]: Select all lambda and xi successfully. " << endl;


/////////////////////////////////////////////////////////////////////////
HepLorentzVector P4_tag_p,P4_tag_pi,P4_tag_lam;
HepLorentzVector P4_sig_p,P4_sig_pi,pdp_new;
HepLorentzVector P4_tag_lam_p,P4_tag_lam_pi,P4_tag_xi_pi, P4_tag_xi;
HepLorentzVector P4_sig_xi_lam_p,P4_sig_xi_lam_pi,P4_sig_xi_lam,P4_sig_xi_e,P4_sig_xi_ve;
HepLorentzVector P4_sig_e,P4_sig_lam,P4_sig_sigma0;
HepLorentzVector P4_sig_p_svf,P4_sig_e_bkg,P4_sig_lam_svf,P4_sig_lam_bkg;

HepLorentzVector P_sig_123,P_sig_124,P_sig_234,P_sig_1234,pdp1,P_sig_134,P_sig_125,P_sig_235,P_sig_345,P_sig_135;

HepLorentzVector pdp,pdp_2,p_uv,p_ev,p_kpi,p_ku,p_ke,p_kpiu,p_kpie,Evector_new,p_keta,p_ketae,p_ketau,p_v2_1,p_v3_1,pdp4,pdp5,p_piu,p_kv,p_piv,p_pie,v4_k,v4_pi,v4_u,v4_v,v4_0,v4_1,v4_2,v4_3,v4_4,v4_5,v4_6,v4_7;
HepLorentzVector v4_1_4c(0.,0.,0.,0.);
HepLorentzVector v4_2_4c(0.,0.,0.,0.);
HepLorentzVector v4_3_4c(0.,0.,0.,0.);
HepLorentzVector v4_4_4c(0.,0.,0.,0.);
HepLorentzVector v4_5_4c(0.,0.,0.,0.);
HepLorentzVector v4_6_4c(0.,0.,0.,0.);
HepLorentzVector v4_7_4c(0.,0.,0.,0.);

/*HepLorentzVector pi0_sig_4c_2(0.,0.,0.,0.);   
HepLorentzVector P_sig_4c_2(0.,0.,0.,0.);     
HepLorentzVector E1_sig_4c_2(0.,0.,0.,0.);    
HepLorentzVector E2_sig_4c_2(0.,0.,0.,0.);    
HepLorentzVector p_lam_tag_4c_2(0.,0.,0.,0.); 
HepLorentzVector pi_lam_tag_4c_2(0.,0.,0.,0.);
HepLorentzVector pi_tag_4c_2(0.,0.,0.,0.);    
*/

HepLorentzVector Mu_1,p_v2_2,p_v2_a,pdp_new_a,kpi1,kpi2,kpi3,pi1pi2,pi1pi3,pi2pi3,kpi1pi2,kpi1pi3,kpi2pi3,pi1pi2pi3;

int tagcharge,sig_number=0;
for(int q=0;q<2;q++){//charge conjugation
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
        if(tagmode==1){
            //
            // anti-xi+ -> anti-lambda pion+
            //                 |
            //                \|/
            //                 v
            //             anti-lambda -> anti-proton pion+
            //            
            for(int i=0;i<xinumber;i++){
                if(Xicharge[i]==tagcharge) continue;
                x0[5]++;
                if(Xi_Pcharge[i]!=tagcharge) continue;
                x0[6]++;
                if(Xi_Picharge[i]==tagcharge) continue;
                x0[7]++;
                int s_id[20];
                for(int ii=0;ii<20;ii++)s_id[ii]=-1;
                s_id[0]=Xi_Lamid_p[i];
                s_id[1]=Xi_Lamid_pi[i];
                s_id[2]=Xiid_pi[i];
                if(same(s_id))continue;
                x0[8]++;
                HepLorentzVector pdp_temp = Xivector[i];
                double temp1 = (ecm/2.)*(ecm/2.)-pdp_temp.rho()*pdp_temp.rho() ;
                if(temp1<0) temp1 =0;
                double mass_bc  = sqrt(temp1);
                if(mass_bc< 1.1 || mass_bc> 1.5)  continue;
                double  delE_tag =(ecm/2.)-pdp_temp.e();
                double  delmlam_tag =Xi_Lamvector[i].m()-mlambda;
                double  delmxi_tag =Xivector[i].m()-mxi;
                	//double  del_mme=delE_tag*delE_tag+delmlam_tag*delmlam_tag;
             //   double  del_mme=delmlam_tag*delmlam_tag+delmxi_tag*delmxi_tag;

if(fabs(delE_tag)<=deltaE_cut)   {
                //if(del_mme<=deltaE_cut)   {
                   //	deltaE_cut  =  fabs(delE_tag);
                    deltaE_cut  =  delE_tag;
                    //deltaE_cut  =  del_mme;
                    deltaE_temp =  delE_tag;

                    HepLorentzVector p_all(0,0,0,ecm);
                    HepLorentzVector reco_xi=p_all-pdp_temp;//jpsi-xi

                    mass_tag_lam_temp  =  Xi_Lamvector[i].m();//tag side xi mass
                    mass_tag_reco_temp =  reco_xi.m();//mass without xi ->>>>xibar+
                    pdp           =  pdp_temp;//4V xi 
                    xinvmass      =  pdp.m();//mass xi
                    mass_bc_temp  =  mass_bc;
                    pdp_rho_temp  =  pdp.rho();
                    pdp_e_temp    =  pdp.e();

                    p_tag_0     =  pdp.rho();
                    c_tag_0     =  pdp.cosTheta();
                    phi_tag_0   =  pdp.phi();

                    p_tag_1     =  Xi_Lam_p[i].rho();
                    c_tag_1     =  Xi_Lam_p[i].cosTheta();
                    phi_tag_1   =  Xi_Lam_p[i].phi();
                    eemc_tag_1  =  Xi_Lam_p_eemc[i];
                    evp_tag_1   =  Xi_Lam_p_evp[i];

                    p_tag_2     =  Xi_Lam_pi[i].rho();
                    c_tag_2     =  Xi_Lam_pi[i].cosTheta();
                    phi_tag_2   =  Xi_Lam_pi[i].phi();
                    eemc_tag_2  =  Xi_Lam_pi_eemc[i];
                    evp_tag_2   =  Xi_Lam_pi_evp[i];

                    p_tag_3     =  Xi_pi[i].rho();
                    c_tag_3     =  Xi_pi[i].cosTheta();
                    phi_tag_3   =  Xi_pi[i].phi();
                    eemc_tag_3  =  Xi_pi_eemc[i];
                    evp_tag_3   =  Xi_pi_evp[i];

                    p_tag_4     =  Xi_Lamvector[i].rho();
                    c_tag_4     =  Xi_Lamvector[i].cosTheta();
                    phi_tag_4   =  Xi_Lamvector[i].phi();

                    P4_tag_lam_p      =  Xi_Lam_p[i];
                    P4_tag_lam_pi     =  Xi_Lam_pi[i];
                    P4_tag_lam        =  Xi_Lamvector[i];
                    P4_tag_xi_pi      =  Xi_pi[i];
                    P4_tag_xi         =  pdp;

                    tag_pid_temp      =  Xi_Lamid_p[i];
                    tag_piid_temp     =  Xi_Lamid_pi[i];
                    tag_piid2_temp    =  Xiid_pi[i];

                    lam_chi_tag       =  Xi_Lamchi[i];
                    lam_len_tag       =  Xi_Lamlen[i];
                    lam_lenerr_tag    =  Xi_Lamlenerr[i];

                    xi_chi_tag        =  Xichi[i];
                    xi_len_tag        =  Xilen[i];
                    xi_lenerr_tag     =  Xilenerr[i];

                    tagmode_temp      =  tagmode;
                    tagcharge_temp    =  tagcharge;
                    tag_trk_xi        =  Trk_xi[i];

                    tag_trk_lam     = Trk_xi_lam[i];
                    tag_trk_lam_pi  = Trk_xi_lam_pi[i];
                    tag_trk_lam_p   = Trk_xi_lam_p[i];
                    tag_trk_pi      = Trk_xi_pi[i];
                    //S_trk_lam_tag = Trk_xi_lam[i];
                    //S_trk_lam_pi_tag  = Trk_xi_lam_pi[i];
                    ////S_trk_lam_pi_tag  = Trk_lam_pi[i];
                    //S_trk_lam_p_tag = Trk_xi_lam_p[i];
                    //S_trk_pi_tag = Trk_xi_pi[i];


                    if(runNo<0){
                        if(tagcharge==1 && T4_xi_lambda_p.size()>0 && T4_xi_lambda_pi.size()>0 && T4_xi_pi.size()>0 && T4_xi.size()>0 && T4_xi_lambda.size()>0){
                            T_angle1=((Xi_Lam_p[i].vect()).angle(T4_xi_lambda_p[0].vect()))/(CLHEP::pi)*180;
                            T_angle2=((Xi_Lam_pi[i].vect()).angle(T4_xi_lambda_pi[0].vect()))/(CLHEP::pi)*180;
                            T_angle3=((Xi_pi[i].vect()).angle(T4_xi_pi[0].vect()))/(CLHEP::pi)*180;
                            T_angle4=((Xi_Lamvector[i].vect()).angle(T4_xi_lambda[0].vect()))/(CLHEP::pi)*180;
                            T_angle5=((Xivector[i].vect()).angle(T4_xi[0].vect()))/(CLHEP::pi)*180;
                        }
                        if(tagcharge==-1 && T4_anti_xi_lambda_p.size()>0 && T4_anti_xi_lambda_pi.size()>0 && T4_anti_xi_pi.size()>0 && T4_anti_xi.size()>0 && T4_anti_xi_lambda.size()>0){
                            T_angle1=((Xi_Lam_p[i].vect()).angle(T4_anti_xi_lambda_p[0].vect()))/(CLHEP::pi)*180;
                            T_angle2=((Xi_Lam_pi[i].vect()).angle(T4_anti_xi_lambda_pi[0].vect()))/(CLHEP::pi)*180;
                            T_angle3=((Xi_pi[i].vect()).angle(T4_anti_xi_pi[0].vect()))/(CLHEP::pi)*180;
                            T_angle4=((Xi_Lamvector[i].vect()).angle(T4_anti_xi_lambda[0].vect()))/(CLHEP::pi)*180;
                            T_angle5=((Xivector[i].vect()).angle(T4_anti_xi[0].vect()))/(CLHEP::pi)*180;
                        }
                    }////////runNo<0

                    ncount=1;
                }//minimum delE
            }//for xi
        }//tagmode==1

        ///////////////////////
        if(ncount>0&&ncount<10){//be used for double tag

            Trk_xi_tag.push_back(tag_trk_xi);
            Vtagmode.push_back(tagmode_temp);
            tag_tagcharge.push_back(tagcharge_temp);
            tag_mbc.push_back(mass_bc_temp);
            tag_delE.push_back(deltaE_temp);
            single_pdp.push_back(pdp);
            tag_pid.push_back(tag_pid_temp);
            tag_piid.push_back(tag_piid_temp);
            tag_piid2.push_back(tag_piid2_temp);
            tag_mass_lam.push_back(mass_tag_lam_temp);
            tag_mass_reco.push_back(mass_tag_reco_temp);

            tag_Lamlen.push_back(lam_len_tag);
            tag_Lamlenerr.push_back(lam_lenerr_tag);
            tag_Lamchi.push_back(lam_chi_tag);
            tag_Xilen.push_back(xi_len_tag);
            tag_Xilenerr.push_back(xi_lenerr_tag);
            tag_Xichi.push_back(xi_chi_tag);

            tag_Lam_p_eemc.push_back(eemc_tag_1);
            tag_Lam_p_evp.push_back(evp_tag_1);
            tag_Lam_pi_eemc.push_back(eemc_tag_2);
            tag_Lam_pi_evp.push_back(evp_tag_2);
            tag_Xi_pi_eemc.push_back(eemc_tag_3);
            tag_Xi_pi_evp.push_back(evp_tag_3);

            tag_Lamvector.push_back(P4_tag_lam);
            tag_Xivector.push_back(P4_tag_xi);
            tag_Xi_pi.push_back(P4_tag_xi_pi);
            tag_Lam_pi.push_back(P4_tag_lam_pi);
            tag_Lam_p.push_back(P4_tag_lam_p);

            tag_angle1.push_back(T_angle1);
            tag_angle2.push_back(T_angle2);
            tag_angle3.push_back(T_angle3);
            tag_angle4.push_back(T_angle4);
            tag_angle5.push_back(T_angle5);

            S_trk_lam_tag     = tag_trk_lam;    
            S_trk_lam_pi_tag  = tag_trk_lam_pi; 
            S_trk_lam_p_tag   = tag_trk_lam_p;  
            S_trk_pi_tag      = tag_trk_pi;     
            //S_trk_lam_tag = Trk_xi_lam[i];
            //S_trk_lam_pi_tag  = Trk_xi_lam_pi[i];
            ////S_trk_lam_pi_tag  = Trk_lam_pi[i];
            //S_trk_lam_p_tag = Trk_xi_lam_p[i];
            //S_trk_pi_tag = Trk_xi_pi[i];

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

            trk_lam_tag.push_back(S_trk_lam_tag);
            trk_lam_pi_tag.push_back(S_trk_lam_pi_tag);
            trk_lam_p_tag.push_back(S_trk_lam_p_tag);
            trk_pi_tag.push_back(S_trk_pi_tag);

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
            pdp_temp_1          =  pdp_rho_temp;
            pdp_e_temp_1        =    pdp_e_temp;
            mass_bc_temp_1      =  mass_bc_temp;
            mass_tag_lam_temp_1 =  mass_tag_lam_temp;
            mass_tag_reco_temp_1=  mass_tag_reco_temp;
            cosmicray_temp_1    =     cosmicray;
            mctag_temp_1        =       m_mctag;

            p_tag_temp_1        =       p_tag_0;
            p_tag_1_temp_1      =       p_tag_1;
            p_tag_2_temp_1      =       p_tag_2;
            p_tag_3_temp_1      =       p_tag_3;
            p_tag_4_temp_1      =       p_tag_4;

            c_tag_temp_1        =       c_tag_0;
            c_tag_1_temp_1      =       c_tag_1;
            c_tag_2_temp_1      =       c_tag_2;
            c_tag_3_temp_1      =       c_tag_3;
            c_tag_4_temp_1      =       c_tag_4;

            phi_tag_temp_1      =     phi_tag_0;
            phi_tag_1_temp_1    =     phi_tag_1;
            phi_tag_2_temp_1    =     phi_tag_2;
            phi_tag_3_temp_1    =     phi_tag_3;
            phi_tag_4_temp_1    =     phi_tag_4;

            index_temp_1        =             4;
            V4_1_temp_1[0]      =     P4_tag_lam_p.px();
            V4_1_temp_1[1]      =     P4_tag_lam_p.py();
            V4_1_temp_1[2]      =     P4_tag_lam_p.pz();
            V4_1_temp_1[3]      =     P4_tag_lam_p.e();

            V4_2_temp_1[0]      =     P4_tag_lam_pi.px();
            V4_2_temp_1[1]      =     P4_tag_lam_pi.py();
            V4_2_temp_1[2]      =     P4_tag_lam_pi.pz();
            V4_2_temp_1[3]      =     P4_tag_lam_pi.e();

            V4_3_temp_1[0]      =     P4_tag_xi_pi.px();
            V4_3_temp_1[1]      =     P4_tag_xi_pi.py();
            V4_3_temp_1[2]      =     P4_tag_xi_pi.pz();
            V4_3_temp_1[3]      =     P4_tag_xi_pi.e();

            V4_4_temp_1[0]      =     P4_tag_lam.px();
            V4_4_temp_1[1]      =     P4_tag_lam.py();
            V4_4_temp_1[2]      =     P4_tag_lam.pz();
            V4_4_temp_1[3]      =     P4_tag_lam.e();

            V4_5_temp_1[0]      =     P4_tag_xi.px();
            V4_5_temp_1[1]      =     P4_tag_xi.py();
            V4_5_temp_1[2]      =     P4_tag_xi.pz();
            V4_5_temp_1[3]      =     P4_tag_xi.e();

            eemc_1_temp_1       =     eemc_tag_1;
            eemc_2_temp_1       =     eemc_tag_2;
            eemc_3_temp_1       =     eemc_tag_3;

            evp_1_temp_1        =     evp_tag_1;
            evp_2_temp_1        =     evp_tag_2;
            evp_3_temp_1        =     evp_tag_3;

            lam_chi_temp_1      =     lam_chi_tag;
            lam_len_temp_1      =     lam_len_tag;
            lam_lenerr_temp_1   =     lam_lenerr_tag;

            xi_chi_temp_1       =     xi_chi_tag;
            xi_len_temp_1       =     xi_len_tag;
            xi_lenerr_temp_1    =     xi_lenerr_tag;

            if(mass_bc_temp_1>0.01)   m_tuple1->write();
        }//end of fill tree
    }//end of all tagmode
}//end of charge conjugation
sig_number=Vtagmode.size();
    /////////////////////////////////////////////////
    ////////////end of tag side
    /////////////////////////////////////////////////
    for(int n=0;n<sig_number;n++){
    /////////////////////////////////////////////////
    //////////////signalside
    /////////////////////////////////////////////////
        set0();
        x1[0]++;

        //good charged trackes ==6
        if(enumber!=6) return StatusCode::SUCCESS;
        x1[1]++;

        if(Vtagmode[n]==1){ 
            double mlam_sig_cut=0.2;
            //
            // xi-    -> sigma+ electron electron
            //             |
            //            \|/
            //             v
            //             pi0 p
            //             |
            //            \|/
            //             v
            //             pi0 -> gamma gamma 
            //  
            //
            //  final  states : gam gam p e- e-        

            ///Prevent duplication with tag side
            for(int a=0;a<pnumber;a++){
                if(Pcharge[a]==tag_tagcharge[n])continue;
                x0[9]++;
                //for(int b=0;b<pinumber;b++){
                //if(Picharge[b]!=tag_tagcharge[n])continue;
                //x0[11]++;
                for(int b=0;b<enumber;b++){
                    if(Echarge[b]!=tag_tagcharge[n]) continue;
                    x0[10]++;
                    for(int c=0;c<pi0number;c++){
                        x0[11]++;
                        for(int d=0;d<enumber;d++){
                            if(Echarge[d]!=tag_tagcharge[n]) continue;
                            if(d==b) continue;
                            x0[12]++;

                        int s_id[20];for(int ii=0;ii<20;ii++)s_id[ii]=-1;
                        s_id[0]=tag_pid[n]; 
                        s_id[1]=tag_piid[n];
                        s_id[2]=tag_piid2[n];
                        s_id[3]=Pid[a];
                        //s_id[4]=Piid[b];
                        s_id[4]=Eid[b];
                        s_id[5]=Eid[d];//////Qmh1:double e????
                        if(same(s_id))continue;
                        x0[13]++;


                        //second vertex fit for double tag(use PIDtype: p pi pi)
                        //mh:signal side: because of pi0, donot need to do second vertex xi
                        //mh:tag side:  need to do second vertex xi
                        
                        // b and d -> ee may misidentify as pi -> include bkg : xi->lambda pi-
                       //because we dont do pid for charge tracks, the Trk_pi[] and Trk_e[] is the same track (when select all ***,we have already set pid type) 
//                           WTrackParameter vp=Trk_p[a];
//    cout<<__LINE__<<endl;
//                           WTrackParameter vpi=Trk_pi[b];
//    cout<<__LINE__<<endl;
//                           WTrackParameter vpi2=Trk_pi[d];
//    cout<<__LINE__<<endl;
//
//                           Hep3Vector ip(0,0,0);
//                           HepSymMatrix ipEx(3, 0);
//                           IVertexDbSvc* vtxsvc;
//                           Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
//    cout<<__LINE__<<endl;
//                           if (vtxsvc->isVertexValid())
//                           {
//                           double* dbv = vtxsvc->PrimaryVertex();
//                           double* vv  = vtxsvc->SigmaPrimaryVertex();
//                           ip.setX(dbv[0]);
//                           ip.setY(dbv[1]);
//                           ip.setZ(dbv[2]);
//                           ipEx[0][0] = vv[0] * vv[0];
//                           ipEx[1][1] = vv[1] * vv[1];
//                           ipEx[2][2] = vv[2] * vv[2];
//                           }
//                           else{
//    cout<<__LINE__<<endl;
//                           continue;}
//
//                           VertexParameter bs;
//                           bs.setVx(ip);
//                           bs.setEvx(ipEx);
//    cout<<__LINE__<<endl;
//                        ///////////////////////////////////////////////////////////////////
//                        //  set a common vertex with huge error
//                        ///////////////////////////////////////////////////////////////////
//                        HepPoint3D    vx(0., 0., 0.);
//                        HepSymMatrix  Evx(3, 0);
//                        double bx = 1E+6;
//                        double by = 1E+6;
//                        double bz = 1E+6;
//                        Evx[0][0] = bx * bx;
//                        Evx[1][1] = by * by;
//                        Evx[2][2] = bz * bz;
//                        VertexParameter vxpar;
//                        vxpar.setVx(vx);
//                        vxpar.setEvx(Evx);
//                        ///////////////////////////////////////////////////////////////////
//                        //  do vertex fit
//                        ///////////////////////////////////////////////////////////////////
//                        VertexFit *vtxfit = VertexFit::instance();
//                        vtxfit->init();
//                        vtxfit->setChisqCut(1000000000,1.0e-3);
//
//                        vtxfit->AddTrack(0, vpi);
//                        vtxfit->AddTrack(1, vp);
//                        vtxfit->AddVertex(0, vxpar, 0, 1);
//                        if (!(vtxfit->Fit(0))) continue;
//                        vtxfit->Swim(0);
//                        vtxfit->BuildVirtualParticle(0);
//                        double vtx_chisq = vtxfit->chisq(0);
//                        WTrackParameter wlam_Trk = vtxfit->wVirtualTrack(0);
//                        WTrackParameter wpi  = vtxfit->wtrk(0);
//                        WTrackParameter wp  = vtxfit->wtrk(1);
//                        P4_sig_pi = vtxfit->pfit(0);
//                        P4_sig_p  = vtxfit->pfit(1);
//                        P4_sig_pi.boost(-0.011,0,0);
//                        P4_sig_p.boost(-0.011,0,0);
//                        x1[2]++;
//    cout<<__LINE__<<endl;
//                       
//                        ////mh : for bkg xi->lambda pi-
//                        //****************** vertex fit lambda -> xi **********************
//                            /*  EvtRecTrackIterator itTrk3 = evtRecTrkCol->begin() + Eid[c];//!!need to be careful
//                                if(!(*itTrk3)->isMdcKalTrackValid()) continue;
//                                RecMdcKalTrack*  mdcKalTrk3 = (*itTrk3)->mdcKalTrack();
//                                RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);//use pion PidType
//
//                                WTrackParameter vpi2(xmass[2],mdcKalTrk3->getZHelix(),mdcKalTrk3->getZError());
//*/
//                                Hep3Vector ip2(0,0,0);
//                                HepSymMatrix ipEx2(3, 0);
//                                IVertexDbSvc* vtxsvc2;
//                                Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc2);
//                                if (vtxsvc2->isVertexValid())
//                                {
//                                double* dbv2 = vtxsvc2->PrimaryVertex();
//                                double* vv2  = vtxsvc2->SigmaPrimaryVertex();
//                                ip2.setX(dbv2[0]);
//                                ip2.setY(dbv2[1]);
//                                ip2.setZ(dbv2[2]);
//                                ipEx2[0][0] = vv2[0] * vv2[0];
//                                ipEx2[1][1] = vv2[1] * vv2[1];
//                                ipEx2[2][2] = vv2[2] * vv2[2];
//                                }
//                                else{
//                                continue;}
//
//                                VertexParameter bs2;
//                                bs2.setVx(ip2);
//                                bs2.setEvx(ipEx2);
//                        ///////////////////////////////////////////////////////////////////
//                        //  set a common vertex with huge error
//                        ///////////////////////////////////////////////////////////////////
//                        HepPoint3D    vx2(0., 0., 0.);
//                        HepSymMatrix  Evx2(3, 0);
//                        double bx2 = 1E+6;
//                        double by2 = 1E+6;
//                        double bz2 = 1E+6;
//                        Evx2[0][0] = bx2 * bx2;
//                        Evx2[1][1] = by2 * by2;
//                        Evx2[2][2] = bz2 * bz2;
//                        VertexParameter vxpar2;
//                        vxpar2.setVx(vx2);
//                        vxpar2.setEvx(Evx2);
//                        ///////////////////////////////////////////////////////////////////
//                        //  do vertex fit
//                        ///////////////////////////////////////////////////////////////////
//                        VertexFit *vtxfit2 = VertexFit::instance();
//                        vtxfit2->init();
//                        vtxfit2->setChisqCut(1000000000,1.0e-3);
//
//                        vtxfit2->AddTrack(0, vpi2);
//                        vtxfit2->AddTrack(1, wlam_Trk);
//                        vtxfit2->AddVertex(0, vxpar2, 0, 1);
//                        if (!(vtxfit2->Fit(0))) continue;
//                        vtxfit2->Swim(0);
//                        vtxfit2->BuildVirtualParticle(0);
//                        double vtx_chisq2 = vtxfit2->chisq(0);
//                        WTrackParameter wxi_Trk = vtxfit2->wVirtualTrack(0);
//                        WTrackParameter wpi2  = vtxfit2->wtrk(0);
//                        WTrackParameter wlam  = vtxfit2->wtrk(1);
//                        P4_sig_e_bkg = vtxfit2->pfit(0);
//                        P4_sig_e_bkg.boost(-0.011,0,0);
//    cout<<__LINE__<<endl;


                        ///////////////////////////////////////////////////////////////////
                        //  do second vertex fit
                        ///////////////////////////////////////////////////////////////////


                        //*********** for sigma0 reconstruction and signal analysis ***********//
                        //mh: SecondVertexFit for lambda 
                        //mh: do cut for lambda, then save the length message
                        /* SecondVertexFit *svtxfit0 = SecondVertexFit::instance();
                           svtxfit0->init();
                           svtxfit0->setChisqCut(1000000000,1.0e-2);
                           svtxfit0->setPrimaryVertex(bs);
                        // svtxfit0->setPrimaryVertex(vtxfit2->vpar(0));
                        svtxfit0->AddTrack(0, wlam_Trk);//through only vertex fit for lambda
                        svtxfit0->setVpar(vtxfit->vpar(0));
                        if (!svtxfit0->Fit()) continue;
                        double len0 = svtxfit0->decayLength();
                        double lenerr0 = svtxfit0->decayLengthError();
                        WTrackParameter wlam_svt0=svtxfit0->wpar();
                        HepLorentzVector plam_temp0 = svtxfit0->p4par();
                        plam_temp0.boost(-0.011,0,0);
                        if(plam_temp0.m()>1.3||plam_temp0.m()<0.9) continue;
                        P4_sig_lam_svf      =   plam_temp0;
                        lam_sig_chi_temp    =   vtx_chisq;
                        lam_sig_len_temp    =   len0; 
                        lam_sig_lenerr_temp =   lenerr0;
                        x1[3]++;
                        double delmlam_sig=fabs(plam_temp0.m()-mlambda);
                        //        if(delmlam_sig<mlam_sig_cut){
                        mlam_sig_cut=delmlam_sig;

*/
                       //*********** for sigma+ reconstruction and signal analysis ***********//

                        if(a!=-1&&b!=-1&&c!=-1&&d!=-1){////////////0915????requirements

                            KalmanKinematicFit * kmfit =KalmanKinematicFit::instance();
                            RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+Pi0id1[c]))->emcShower();
                            RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+Pi0id2[c]))->emcShower();
                            kmfit->init();
                            kmfit->setChisqCut(100000,0.05);//Qmh2 :0.05?
                            kmfit->AddTrack(0, 0.0, g1Trk);
                            kmfit->AddTrack(1, 0.0, g2Trk);
                            kmfit->AddTrack(2,Trk_p[a]);//
                            kmfit->AddTrack(3,Trk_e[b]);//
                            kmfit->AddTrack(4,Trk_e[d]);//
                            kmfit->AddTrack(5,trk_lam_p_tag[n]);//tag
                            kmfit->AddTrack(6,trk_lam_pi_tag[n]);//tag
                            kmfit->AddTrack(7,trk_pi_tag[n]);//tag
                            kmfit->AddFourMomentum(0, ecms);
                            oksq_4c_2 = kmfit->Fit();
                            if(oksq_4c_2){
                                double m_chi2 = kmfit->chisq();
                                if (m_chi2<chi2_min){
                                    chi2_min=m_chi2;
                                    i_pi0 = c;
                                    i_e1  = b;
                                    i_e2  = d;
                                    sig_gamid = c;

                                    HepLorentzVector Pi0_sig_4c_2     = kmfit->pfit(0)+kmfit->pfit(1);  Pi0_sig_4c_2.boost(-0.011,0,0);
                                    HepLorentzVector P_sig_4c_2       = kmfit->pfit(2);                 P_sig_4c_2.boost(-0.011,0,0);
                                    HepLorentzVector E1_sig_4c_2      = kmfit->pfit(3);                 E1_sig_4c_2.boost(-0.011,0,0);
                                    HepLorentzVector E2_sig_4c_2      = kmfit->pfit(4);                 E2_sig_4c_2.boost(-0.011,0,0);

                                    HepLorentzVector P_lam_tag_4c_2   = kmfit->pfit(5);                 P_lam_tag_4c_2.boost(-0.011,0,0);
                                    HepLorentzVector Pi_lam_tag_4c_2  = kmfit->pfit(6);                 Pi_lam_tag_4c_2.boost(-0.011,0,0);
                                    HepLorentzVector Pi_tag_4c_2      = kmfit->pfit(7);                 Pi_tag_4c_2.boost(-0.011,0,0);

                                    HepLorentzVector gam1_4c = kmfit->pfit(0);         gam1_4c.boost(-0.011,0,0);
                                    HepLorentzVector gam2_4c = kmfit->pfit(1);         gam2_4c.boost(-0.011,0,0);


                                    eemc_sig_e1      =       e_eemc[b];
                                    eemc_sig_e2      =       e_eemc[d];
                                    evp_sig_e1       =       e_evp[b];
                                    evp_sig_e2       =       e_evp[d];

                                    //1 for p; 2 for e1; 3 for e2; 4 for pi0;
                                    p_sig_1         =       P_sig_4c_2.rho();
                                    p_sig_2         =       E1_sig_4c_2.rho();
                                    p_sig_3         =       E2_sig_4c_2.rho();
                                    p_sig_4         =       Pi0_sig_4c_2.rho();

                                    c_sig_1         =       P_sig_4c_2.cosTheta();
                                    c_sig_2         =       E1_sig_4c_2.cosTheta();
                                    c_sig_3         =       E2_sig_4c_2.cosTheta();
                                    c_sig_4         =       Pi0_sig_4c_2.cosTheta();

                                    p_tag_11        =       P_lam_tag_4c_2.rho();
                                    p_tag_12        =       Pi_lam_tag_4c_2.rho();
                                    p_tag_13        =       Pi_tag_4c_2.rho();

                                    c_tag_11        =       P_lam_tag_4c_2.cosTheta();
                                    c_tag_12        =       Pi_lam_tag_4c_2.cosTheta();
                                    c_tag_13        =       Pi_tag_4c_2.cosTheta();

                                    m_pdp_theta     =       single_pdp[n].cosTheta();
                                    tag_mass_bc     =       tag_mbc[n];
                                    tag_deltaE      =       tag_delE[n];
                                    tag_mass        =       single_pdp[n].m();
                                    T_tagmode       =       Vtagmode[n];
                                    sigtagcharge    =       tag_tagcharge[n];
                                    chi2_pi0        =       Pi0chi[i_pi0];

                                    v4_1            =       Pvector[a];
                                    v4_2            =       Evector[i_e1];
                                    v4_3            =       Evector[i_e2];
                                    v4_4            =       Pi0vector[i_pi0];
                                    v4_5            =       tag_Lam_p[n];
                                    v4_6            =       tag_Lam_pi[n];
                                    v4_7            =       tag_Xi_pi[n];


                                    v4_1_4c         =       P_sig_4c_2;
                                    v4_2_4c         =       E1_sig_4c_2;
                                    v4_3_4c         =       E2_sig_4c_2;
                                    v4_4_4c         =       Pi0_sig_4c_2;
                                    v4_5_4c         =       P_lam_tag_4c_2;
                                    v4_6_4c         =       Pi_lam_tag_4c_2;
                                    v4_7_4c         =       Pi_tag_4c_2;
    HepLorentzVector pdp_temp;
    pdp_temp = single_pdp[n];
    pdp_temp.setPhi(single_pdp[n].phi());
    pdp_temp.setTheta(single_pdp[n].theta());
    pdp_temp.setE(ecm/2.);
    double rho_temp=sqrt((ecm/2.)*(ecm/2.)-mxi*mxi);
    pdp_temp.setRho(rho_temp);
    //HepLorentzVector p_v3_temp;
    //p_v3_temp=p_all-pdp_temp-pdp3_temp;
                    HepLorentzVector p_all(0,0,0,ecm);
                                    
                                    HepLorentzVector pee_rec_4c;
                                    pee_rec_4c = p_all - E1_sig_4c_2 - E2_sig_4c_2 - pdp_temp; 
                                    Mee_rec_4c = pee_rec_4c.m();
                                    Mpi0_4c = Pi0_sig_4c_2.m();
                                    /////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/////////////
if(runNo<0){
    int tep=0,tem=0;
    if(tag_tagcharge[n]==1 && T4_xi_e.size()>0 && T4_xi_sigmap.size()>0 && T4_xi_sigmap_p.size()>0 && T4_xi_sigmap_pi0.size()>0 && T4_xi_sigmap_gam.size()>0 && T4_xi.size()>0 && T4_xi_lambda.size()>0 &&T4_xi_lambda_p.size()>0 && T4_xi_lambda_pi.size()>0 && T4_xi_pi.size()>0)
          tep=1;
    if(tag_tagcharge[n]==-1 && T4_anti_xi_e.size()>0 && T4_anti_xi_sigma.size()>0 && T4_anti_xi_sigma_p.size()>0 && T4_anti_xi_sigma_pi0.size()>0 && T4_anti_xi_sigma_pi0_gam.size()>0 && T4_anti_xi.size()>0 && T4_anti_xi_lambda.size()>0 &&T4_anti_xi_lambda_p.size()>0 && T4_anti_xi_lambda_pi.size()>0 && T4_anti_xi_pi.size()>0)
          tem=-1;
    //if(tag_tagcharge[n]==-1 && T4_anti_xi_lambda_p.size()>0 && T4_anti_xi_lambda_pi.size()>0 && T4_anti_xi_lambda.size()>0 && T4_anti_xi_e.size()>0 && T4_anti_xi_nu_e.size()>0 && T4_anti_xi.size()>0 && T4_anti_xi_gamma.size()>0)
          //tep=-1;

    if(tep==1){
        /*angle1=((P4_sig_p.vect()).angle(T4_xi_lambda_p[0].vect()))/(CLHEP::pi)*180;
        angle2=((P4_sig_pi.vect()).angle(T4_xi_lambda_pi[0].vect()))/(CLHEP::pi)*180;
        angle3=((P4_sig_lam_new.vect()).angle(T4_xi_lambda[0].vect()))/(CLHEP::pi)*180;
        angle4=((Evector_new.vect()).angle(T4_xi_e[0].vect()))/(CLHEP::pi)*180;
        angle5=((p_v3.vect()).angle(T4_xi_nu_e[0].vect()))/(CLHEP::pi)*180;
        angle6=(((p_all-pdp_new).vect()).angle(T4_xi[0].vect()))/(CLHEP::pi)*180;
        */if (sig_gamid<999)angle7=((Gamvector[sig_gamid].vect()).angle(T4_xi_gamma[0].vect()))/(CLHEP::pi)*180;
    }//////////if(tagcharge==-1)
    if(tem==1){
       /* angle1=((P4_sig_p.vect()).angle(T4_anti_xi_lambda_p[0].vect()))/(CLHEP::pi)*180;
        angle2=((P4_sig_pi.vect()).angle(T4_anti_xi_lambda_pi[0].vect()))/(CLHEP::pi)*180;
        angle3=((P4_sig_lam_new.vect()).angle(T4_anti_xi_lambda[0].vect()))/(CLHEP::pi)*180;
        angle4=((Evector_new.vect()).angle(T4_anti_xi_e[0].vect()))/(CLHEP::pi)*180;
        angle5=((p_v3.vect()).angle(T4_anti_xi_nu_e[0].vect()))/(CLHEP::pi)*180;
        angle6=(((p_all-pdp_new).vect()).angle(T4_anti_xi[0].vect()))/(CLHEP::pi)*180;
        */if (sig_gamid<999)angle7=((Gamvector[sig_gamid].vect()).angle(T4_anti_xi_gamma[0].vect()))/(CLHEP::pi)*180;
    }//////////if(tagcharge==1)
}////////runNo<0

/////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/////////////

//save information of charged tracks in signal side
if(a!=-1) {//sig sigmap_p
EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Pid[a];
if(!(*itTrk)->isMdcKalTrackValid()) continue;
RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
if(fabs(mdcKalTrk->charge()) != 1) continue;
HepVector a2 = mdcKalTrk->getZHelixP();
HepSymMatrix Ea2 = mdcKalTrk->getZErrorP();
VFHelix helixip3_2(point0,a2,Ea2);//Qmh:?
helixip3_2.pivot(IP);//Qmh:?
HepVector  vecipa2 = helixip3_2.a();//Qmh:?
double dr1 = fabs(vecipa2[0]);
double drz = fabs(vecipa2[3]);
m_vxy_1_11 = dr1;
m_vz_1_11 = drz;
m_phi_1_11 = mdcKalTrk->phi();//Qmh:?
}//end save sig sigmap_p

if(b!=-1) {//sig e1
EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Eid[i_e1];
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
m_vxy_2_11 = dr1;
m_vz_2_11 = drz;
m_phi_2_11 = mdcKalTrk->phi();
/////////mh 2020.0916 set e pid after 4c and so on.
pid->init();
pid->setMethod(pid->methodProbability());
pid->setChiMinCut(4);
pid->setRecTrack(*itTrk);
pid->usePidSys(pid->useDedx() | pid->useTof() | pid->useEmc()); // use PID sub-system
pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() );   
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

//if(pid->probElectron() <= 0) continue;
//if(pid->probElectron() <= pid->probPion()||pid->probElectron() <= pid->probKaon()) continue;
//    if((pid->probElectron())<=0.8*((pid->probKaon())+(pid->probElectron())+(pid->probPion()))) continue;
}
if(d!=-1){//sig e2
EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + Eid[i_e2];
if(!(*itTrk2)->isMdcKalTrackValid()) continue;
RecMdcKalTrack*  mdcKalTrk2 = (*itTrk2)->mdcKalTrack();
RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
if(fabs(mdcKalTrk2->charge()) != 1) continue;
HepVector a2_2 = mdcKalTrk2->getZHelixE();
HepSymMatrix Ea2_2 = mdcKalTrk2->getZErrorE();
VFHelix helixip3_2_2(point0,a2_2,Ea2_2);
helixip3_2_2.pivot(IP);
HepVector  vecipa2_2 = helixip3_2_2.a();
double dr1_2 = fabs(vecipa2_2[0]);
double drz_2 = fabs(vecipa2_2[3]);
m_vxy_3_11 = dr1_2;
m_vz_3_11 = drz_2;
m_phi_3_11 = mdcKalTrk2->phi();
pid->init();
pid->setMethod(pid->methodProbability());
pid->setChiMinCut(4);
pid->setRecTrack(*itTrk2);
pid->usePidSys(pid->useDedx() | pid->useTof() | pid->useEmc()); // use PID sub-system
pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() );
pid->calculate();
if(pid->IsPidInfoValid()) {
    m_probe_2_11  = pid->probElectron();
    m_probmu_2_11 = pid->probMuon();
    m_probpi_2_11 = pid->probPion();
    m_probk_2_11  = pid->probKaon();
    m_probp_2_11  = pid->probProton();
} else {
    m_probe_2_11  = -1.0;
    m_probmu_2_11 = -1.0;
    m_probpi_2_11 = -1.0;
    m_probk_2_11  = -1.0;
    m_probp_2_11  = -1.0;
}

}//end of sig e1 e2

//if(c!=-1) {//sig sigmap_pi0
//KalmanKinematicFit * kmfit =KalmanKinematicFit::instance();
//RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+Pi0id1[i_pi0]))->emcShower();
//RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+Pi0id2[i_pi0]))->emcShower();
//HepLorentzVector Pgam1_pi0 = Pi0vector_gam1[i_pi0];
//HepLorentzVector Pgam2_pi0 = Pi0vector_gam2[i_pi0];

//}//end of sig sigmap_pi0


//save information of charged tracks in tag side
if(tag_pid.size()>0) {//tag lam_p
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
    m_vxy_4_11 = dr1;
    m_vz_4_11 = drz;
    m_phi_4_11 = mdcKalTrk->phi();
}//end save tag lam_p

if(tag_piid.size()>0) {//tag lam_pi
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
    m_vxy_5_11 = dr1;
    m_vz_5_11 = drz;
    m_phi_5_11 = mdcKalTrk->phi();
}//end save tag lam_pi

if(tag_piid2.size()>0) {//tag xi_pi
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + tag_piid2[n];
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
    m_vxy_6_11 = dr1;
    m_vz_6_11 = drz;
    m_phi_6_11 = mdcKalTrk->phi();
}//end save tag xi_pi
//chi2_min_tmp=chi2_min;
}//end of min chi2
}//end of 4c kinematic fit
}//for c=!-1

/*    mPi0_sig_tmp =pi0_sig_4c_2.m();
      mSigmap_sig_tmp = (P_sig_4c_2+pi0_sig_4c_2).m();
      double delm_sgm = fabs(mSigmap_sig_tmp - msigma);
      if (mSigmap_sig_tmp<delm_sgm){delm_sgm=mSigmap_sig_tmp;i_pi0 = c}
      */

//*****************for background analysis****************************//
//mh: for tag side, change vertex message for only vertex fit for lambda || vertex fit ->xi
/*SecondVertexFit *svtxfit = SecondVertexFit::instance();
svtxfit->init();
svtxfit->setChisqCut(1000000000,1.0e-2);
 //svtxfit->setPrimaryVertex(bs);//mh change this item
svtxfit->setPrimaryVertex(vtxfit2->vpar(0));
// svtxfit->AddTrack(0, wlam);//mh change this item
svtxfit->AddTrack(0, wlam_Trk);//through only vertex fit for lambda
svtxfit->setVpar(vtxfit->vpar(0));
if (!svtxfit->Fit()) continue;
double len = svtxfit->decayLength();
double lenerr = svtxfit->decayLengthError();
WTrackParameter wlam_svt=svtxfit->wpar();
HepLorentzVector plam_temp = svtxfit->p4par();
plam_temp.boost(-0.011,0,0);
if(plam_temp.m()>1.3||plam_temp.m()<0.9) continue;
P4_sig_lam_bkg=plam_temp;
*/
//****************** second vertex fit lambda -> xi **********************
/*SecondVertexFit *svtxfit2 = SecondVertexFit::instance();
svtxfit2->init();
svtxfit2->setChisqCut(1000000000,1.0e-2);
svtxfit2->setPrimaryVertex(bs2);
svtxfit2->AddTrack(0, vtxfit2->wVirtualTrack(0));
svtxfit2->setVpar(vtxfit2->vpar(0));
if (!svtxfit2->Fit()) continue;
double len2 = svtxfit2->decayLength();
double lenerr2 = svtxfit2->decayLengthError();
WTrackParameter wxi_svt=svtxfit2->wpar();
HepLorentzVector pxi_temp = svtxfit2->p4par();
pxi_temp.boost(-0.011,0,0);
if(pxi_temp.m()>1.5||pxi_temp.m()<1.1) continue;

xi_len_sig=len2;
xi_lenerr_sig=lenerr2;
xi_chi_sig=vtx_chisq2;
sig_trk_xi=wxi_svt;

*/

//4c kinematic fit for xi and anti-xi(use PIDtype:: anti-xi lambda pi)
KinematicFit * kmfit = KinematicFit::instance(); 
kmfit->init();
kmfit->setChisqCut(100000,0.05);

kmfit->AddTrack(0, Trk_xi_tag[n]);
kmfit->AddTrack(1, sig_trk_xi);
kmfit->AddFourMomentum(0, ecms);
oksq_4c = kmfit->Fit();
if(oksq_4c){
    HepLorentzVector xi_tag = kmfit->pfit(0);
    HepLorentzVector xi_sig = kmfit->pfit(1); 
    double m_chi2  = kmfit->chisq();
    mass_xi_tag_4c=xi_tag.m();	
    mass_xi_sig_4c=xi_sig.m();	
    mass_jpsi=(xi_tag+xi_sig).m();
    chi_4c=m_chi2;
    x1[4]++;
}

//select the best combination
//for gamloop////for (int bb=0;bb<gamnumber;bb++){
//for gamloop////    EvtRecTrackIterator itTrk4=evtRecTrkCol->begin() + Gamid[bb];
//for gamloop////    if(!(*itTrk4)->isEmcShowerValid()) continue;
//for gamloop////    RecEmcShower *gam_sig_temp = (*itTrk4)->emcShower();
//for gamloop////
//for gamloop////    HepLorentzVector pdp3_temp = P4_sig_lam_svf+Gamvector[bb]+Evector[c];
//for gamloop////
//for gamloop////    HepLorentzVector p_all(0,0,0,ecm);
//for gamloop////
//for gamloop////    HepLorentzVector pdp_temp;
//for gamloop////    pdp_temp = single_pdp[n];
//for gamloop////    pdp_temp.setPhi(single_pdp[n].phi());
//for gamloop////    pdp_temp.setTheta(single_pdp[n].theta());
//for gamloop////    pdp_temp.setE(ecm/2.);
//for gamloop////    double rho_temp=sqrt((ecm/2.)*(ecm/2.)-mxi*mxi);
//for gamloop////    pdp_temp.setRho(rho_temp);
//for gamloop////    HepLorentzVector p_v3_temp;
//for gamloop////    p_v3_temp=p_all-pdp_temp-pdp3_temp;
//for gamloop////
//for gamloop////    KalmanKinematicFit * kmfit1 = KalmanKinematicFit::instance();
//for gamloop////    kmfit1->init();
//for gamloop////    kmfit1->setChisqCut(5000000);
//for gamloop////
//for gamloop////    //signal side
//for gamloop////    kmfit1->AddTrack(0, wlam_svt0);//lambda
//for gamloop////    kmfit1->AddTrack(1, 0.0, gam_sig_temp);//gamma
//for gamloop////    kmfit1->AddTrack(2, Trk_e[c]);//e
//for gamloop////    kmfit1->AddMissTrack(3, p_v3_temp);//neutrino
//for gamloop////    //tag side
//for gamloop////    kmfit1->AddTrack(4, Trk_xi_tag[n]);
//for gamloop////
//for gamloop////    kmfit1->AddResonance(0, msigma0, 0, 1);
//for gamloop////    kmfit1->AddResonance(1, mxi, 0, 1, 2,  3);
//for gamloop////    //kmfit1->AddResonance(2, mxi, 4);
//for gamloop////    kmfit1->AddFourMomentum(2, ecms); 
//for gamloop////
//for gamloop////    oksq_3c=kmfit1->Fit();
//for gamloop////    if(oksq_3c&&(kmfit1->chisq()<chi2_min)){
//for gamloop////        chi2_min=kmfit1->chisq();
//for gamloop////        chi_3c=kmfit1->chisq();
//for gamloop////        sig_gamid=bb;
//for gamloop////        HepLorentzVector P4_sig_lam_new=kmfit1->pfit(0);
//for gamloop////        P4_sig_lam_new.boost(-0.011,0,0);
//for gamloop////
//for gamloop////        pdp_new=kmfit1->pfit(4); 
//for gamloop////        pdp_new.boost(-0.011,0,0);
//for gamloop////
//for gamloop////
//for gamloop////        /*
//for gamloop////        //reconstruction of sigma0
//for gamloop////        double m_cut=1;
//for gamloop////        for(int aa=0;aa<gamnumber;aa++){
//for gamloop////        HepLorentzVector sigma0_temp=P4_sig_lam_svf+Gamvector[aa];
//for gamloop////        double delta_m=fabs(sigma0_temp.m()-msigma0);
//for gamloop////        if(delta_m<m_cut) {
//for gamloop////        m_cut = delta_m;
//for gamloop////        P4_sig_sigma0 = sigma0_temp;
//for gamloop////        sig_gamid=aa;
//for gamloop////        }
//for gamloop////        }
//for gamloop////        */
//for gamloop////
//for gamloop////
//for gamloop////        //missing neutrino
//for gamloop////        P4_sig_sigma0=kmfit1->pfit(0)+kmfit1->pfit(1);
//for gamloop////        P4_sig_sigma0.boost(-0.011,0,0);
//for gamloop////
//for gamloop////        Evector_new=kmfit1->pfit(2);
//for gamloop////        Evector_new.boost(-0.011,0,0);
//for gamloop////
//for gamloop////        HepLorentzVector pdp3 = P4_sig_sigma0+Evector_new;
//for gamloop////        esig_V_ebeam=(pdp3.e())/(ecm/2.);
//for gamloop////
//for gamloop////        mass_sig_sigma0e=pdp3.m();
//for gamloop////
//for gamloop////        HepLorentzVector p_v3;
//for gamloop////        p_v3=kmfit1->pfit(3);
//for gamloop////        p_v3.boost(-0.011,0,0);
//for gamloop////
//for gamloop////        p_miss=p_v3.rho();
//for gamloop////        e_miss=p_v3.e();
//for gamloop////        u_miss=e_miss-p_miss;
//for gamloop////        miss_m2=e_miss * e_miss-p_miss * p_miss;
//for gamloop////
//for gamloop////        HepLorentzVector p_nu;
//for gamloop////        p_nu=p_v3;
//for gamloop////        p_nu.setE(p_nu.rho());
//for gamloop////        q2=(Evector_new+p_nu).m2();
//for gamloop////
//for gamloop////        //recoiling mass of Xi-Lambda
//for gamloop////        HepLorentzVector reco_xilam=p_all-pdp_new-P4_sig_lam_bkg;
//for gamloop////        recomass_xilam_temp = reco_xilam.m();
//for gamloop////
//for gamloop////        //recoiling mass of Xi-e
//for gamloop////        HepLorentzVector reco_xie=p_all-pdp_new-P4_sig_e_bkg; 
//for gamloop////        recomass_xie_temp = reco_xie.m();
//for gamloop////
//for gamloop////        //angle for background
//for gamloop////        angle_xilame_58=((pdp_new.vect()).angle((P4_sig_lam_bkg+P4_sig_e_bkg).vect()))/(CLHEP::pi)*180;
//for gamloop////
//for gamloop////        //boost to sig_xi
//for gamloop////        HepLorentzVector sig_xi_57  = p_all-pdp_new;
//for gamloop////        HepLorentzVector sig_lam_57 = P4_sig_lam_bkg;
//for gamloop////        HepLorentzVector sig_e_57 = P4_sig_e_bkg;
//for gamloop////        Hep3Vector P_sig_xi_57 = sig_xi_57.boostVector();
//for gamloop////        sig_lam_57.boost(-P_sig_xi_57);
//for gamloop////        sig_e_57.boost(-P_sig_xi_57);
//for gamloop////        angle_lame_57=((sig_lam_57.vect()).angle(sig_e_57.vect()))/(CLHEP::pi)*180;
//for gamloop////
//for gamloop////        //momentum of electron in the signal side Xi rest frame
//for gamloop////        p_sig_4=sig_e_57.rho();
//for gamloop////
//for gamloop////
//for gamloop////
//for gamloop////        //       if (abs(u_miss)>0.3) continue;
//for gamloop////
//for gamloop////        eemc_sig_e      =       e_eemc[c];
//for gamloop////        evp_sig_e       =       e_evp[c];
//for gamloop////
//for gamloop////        p_sig_1         =       P4_sig_p.rho();
//for gamloop////        p_sig_2         =       P4_sig_pi.rho();
//for gamloop////        p_sig_3         =       Evector_new.rho();
//for gamloop////
//for gamloop////        c_sig_1         =       P4_sig_p.cosTheta();
//for gamloop////        c_sig_2         =       P4_sig_pi.cosTheta();
//for gamloop////        c_sig_3         =       Evector_new.cosTheta();
//for gamloop////
//for gamloop////        p_tag_11        =       tag_Lam_p[n].rho();
//for gamloop////        p_tag_12        =       tag_Lam_pi[n].rho();
//for gamloop////        p_tag_13        =       tag_Xi_pi[n].rho();
//for gamloop////
//for gamloop////        c_tag_11        =       tag_Lam_p[n].cosTheta();
//for gamloop////        c_tag_12        =       tag_Lam_pi[n].cosTheta();
//for gamloop////        c_tag_13        =       tag_Xi_pi[n].cosTheta();
//for gamloop////
//for gamloop////        m_pdp_theta     =       single_pdp[n].cosTheta();
//for gamloop////        tag_mass_bc     =       tag_mbc[n];
//for gamloop////        tag_deltaE      =       tag_delE[n];
//for gamloop////        tag_mass        =       single_pdp[n].m();
//for gamloop////        T_tagmode       =       Vtagmode[n];
//for gamloop////        sigtagcharge    =       tag_tagcharge[n];
//for gamloop////
//for gamloop////        v4_0            =       P4_sig_sigma0;
//for gamloop////        v4_1            =       P4_sig_lam_new;
//for gamloop////        v4_2            =       P4_sig_p;
//for gamloop////        v4_3            =       P4_sig_pi;
//for gamloop////        v4_4            =       pdp3;
//for gamloop////        v4_5            =       Evector_new;
//for gamloop////        v4_6            =       p_v3;
//for gamloop////
//for gamloop////        if(runNo<0){
//for gamloop////            int tep=0,tem=0;
//for gamloop////            if(tag_tagcharge[n]==-1 && T4_xi_lambda_p.size()>0 && T4_xi_lambda_pi.size()>0 && T4_xi_lambda.size()>0 && T4_xi_e.size()>0 && T4_xi_nu_e.size()>0 && T4_xi.size()>0 && T4_xi_gamma.size()>0) 
//for gamloop////                tep=1;
//for gamloop////            if(tag_tagcharge[n]==1 && T4_anti_xi_lambda_p.size()>0 && T4_anti_xi_lambda_pi.size()>0 && T4_anti_xi_lambda.size()>0 && T4_anti_xi_e.size()>0 && T4_anti_xi_nu_e.size()>0 && T4_anti_xi.size()>0 && T4_anti_xi_gamma.size()>0) 
//for gamloop////                tem=1;
//for gamloop////
//for gamloop////            if(tep==1){
//for gamloop////                angle1=((P4_sig_p.vect()).angle(T4_xi_lambda_p[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle2=((P4_sig_pi.vect()).angle(T4_xi_lambda_pi[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle3=((P4_sig_lam_new.vect()).angle(T4_xi_lambda[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle4=((Evector_new.vect()).angle(T4_xi_e[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle5=((p_v3.vect()).angle(T4_xi_nu_e[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle6=(((p_all-pdp_new).vect()).angle(T4_xi[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                if (sig_gamid<999)angle7=((Gamvector[sig_gamid].vect()).angle(T4_xi_gamma[0].vect()))/(CLHEP::pi)*180;
//for gamloop////            }//////////if(tagcharge==-1)
//for gamloop////            if(tem==1){
//for gamloop////                angle1=((P4_sig_p.vect()).angle(T4_anti_xi_lambda_p[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle2=((P4_sig_pi.vect()).angle(T4_anti_xi_lambda_pi[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle3=((P4_sig_lam_new.vect()).angle(T4_anti_xi_lambda[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle4=((Evector_new.vect()).angle(T4_anti_xi_e[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle5=((p_v3.vect()).angle(T4_anti_xi_nu_e[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                angle6=(((p_all-pdp_new).vect()).angle(T4_anti_xi[0].vect()))/(CLHEP::pi)*180;
//for gamloop////                if (sig_gamid<999)angle7=((Gamvector[sig_gamid].vect()).angle(T4_anti_xi_gamma[0].vect()))/(CLHEP::pi)*180;
//for gamloop////            }//////////if(tagcharge==1)
//for gamloop////        }////////runNo<0
//for gamloop////
//for gamloop////        Ncharge_ex=evtRecEvent->totalCharged()-2-2-2;
//for gamloop////
//for gamloop////        //save information of charged tracks in signal side
//for gamloop////        if(a!=-1) {//sig lam_p
//for gamloop////            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Pid[a];     
//for gamloop////            if(!(*itTrk)->isMdcKalTrackValid()) continue;
//for gamloop////            RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
//for gamloop////            RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
//for gamloop////            if(fabs(mdcKalTrk->charge()) != 1) continue;
//for gamloop////            HepVector a2 = mdcKalTrk->getZHelixP();
//for gamloop////            HepSymMatrix Ea2 = mdcKalTrk->getZErrorP();
//for gamloop////            VFHelix helixip3_2(point0,a2,Ea2);
//for gamloop////            helixip3_2.pivot(IP);
//for gamloop////            HepVector  vecipa2 = helixip3_2.a();
//for gamloop////
//for gamloop////            double dr1 = fabs(vecipa2[0]);
//for gamloop////            double drz = fabs(vecipa2[3]);
//for gamloop////            m_vxy_1_11 = dr1;
//for gamloop////            m_vz_1_11 = drz;
//for gamloop////            m_phi_1_11 = mdcKalTrk->phi();
//for gamloop////        }//end save sig lam_p
//for gamloop////
//for gamloop////        if(b!=-1) {//sig lam_pi
//for gamloop////            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Piid[b];     
//for gamloop////            if(!(*itTrk)->isMdcKalTrackValid()) continue;
//for gamloop////            RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
//for gamloop////            RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
//for gamloop////            if(fabs(mdcKalTrk->charge()) != 1) continue;
//for gamloop////            HepVector a2 = mdcKalTrk->getZHelix();
//for gamloop////            HepSymMatrix Ea2 = mdcKalTrk->getZError();
//for gamloop////            VFHelix helixip3_2(point0,a2,Ea2);
//for gamloop////            helixip3_2.pivot(IP);
//for gamloop////            HepVector  vecipa2 = helixip3_2.a();
//for gamloop////
//for gamloop////            double dr1 = fabs(vecipa2[0]);
//for gamloop////            double drz = fabs(vecipa2[3]);
//for gamloop////            m_vxy_2_11 = dr1;
//for gamloop////            m_vz_2_11 = drz;
//for gamloop////            m_phi_2_11 = mdcKalTrk->phi();
//for gamloop////        }//end save sig lam_pi
//for gamloop////
//for gamloop////        if(c!=-1) {//sig xi_e
//for gamloop////            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + Eid[c];     
//for gamloop////            if(!(*itTrk)->isMdcKalTrackValid()) continue;
//for gamloop////            RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
//for gamloop////            RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
//for gamloop////            if(fabs(mdcKalTrk->charge()) != 1) continue;
//for gamloop////            HepVector a2 = mdcKalTrk->getZHelixE();
//for gamloop////            HepSymMatrix Ea2 = mdcKalTrk->getZErrorE();
//for gamloop////            VFHelix helixip3_2(point0,a2,Ea2);
//for gamloop////            helixip3_2.pivot(IP);
//for gamloop////            HepVector  vecipa2 = helixip3_2.a();
//for gamloop////
//for gamloop////            double dr1 = fabs(vecipa2[0]);
//for gamloop////            double drz = fabs(vecipa2[3]);
//for gamloop////            m_vxy_3_11 = dr1;
//for gamloop////            m_vz_3_11 = drz;
//for gamloop////            m_phi_3_11 = mdcKalTrk->phi();
//for gamloop////
//for gamloop////            //PID information for the signal electron
//for gamloop////            ParticleID *pid = ParticleID::instance();
//for gamloop////            pid->init();
//for gamloop////            pid->setMethod(pid->methodProbability());
//for gamloop////            pid->setChiMinCut(4);
//for gamloop////            pid->setRecTrack(*itTrk);
//for gamloop////            pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() | pid->useEmc() );
//for gamloop////            pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
//for gamloop////            pid->calculate();
//for gamloop////            if(pid->IsPidInfoValid()) {
//for gamloop////                m_probe_2_11  = pid->probElectron();
//for gamloop////                m_probmu_2_11 = pid->probMuon();
//for gamloop////                m_probpi_2_11 = pid->probPion();
//for gamloop////                m_probk_2_11  = pid->probKaon();
//for gamloop////                m_probp_2_11  = pid->probProton();
//for gamloop////            } else {
//for gamloop////                m_probe_2_11  = -1.0;
//for gamloop////                m_probmu_2_11 = -1.0;
//for gamloop////                m_probpi_2_11 = -1.0;
//for gamloop////                m_probk_2_11  = -1.0;
//for gamloop////                m_probp_2_11  = -1.0;
//for gamloop////            }
//for gamloop////
//for gamloop////        }//end save sig xi_e
//for gamloop////
//for gamloop////        //save information of charged tracks in tag side
//for gamloop////        if(tag_pid.size()>0) {//tag lam_p
//for gamloop////            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + tag_pid[n];     
//for gamloop////            if(!(*itTrk)->isMdcKalTrackValid()) continue;
//for gamloop////            RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
//for gamloop////            RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
//for gamloop////            if(fabs(mdcKalTrk->charge()) != 1) continue;
//for gamloop////            HepVector a2 = mdcKalTrk->getZHelixP();
//for gamloop////            HepSymMatrix Ea2 = mdcKalTrk->getZErrorP();
//for gamloop////            VFHelix helixip3_2(point0,a2,Ea2);
//for gamloop////            helixip3_2.pivot(IP);
//for gamloop////            HepVector  vecipa2 = helixip3_2.a();
//for gamloop////
//for gamloop////            double dr1 = fabs(vecipa2[0]);
//for gamloop////            double drz = fabs(vecipa2[3]);
//for gamloop////            m_vxy_4_11 = dr1;
//for gamloop////            m_vz_4_11 = drz;
//for gamloop////            m_phi_4_11 = mdcKalTrk->phi();
//for gamloop////        }//end save tag lam_p
//for gamloop////
//for gamloop////        if(tag_piid.size()>0) {//tag lam_pi
//for gamloop////            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + tag_piid[n];     
//for gamloop////            if(!(*itTrk)->isMdcKalTrackValid()) continue;
//for gamloop////            RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
//for gamloop////            RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
//for gamloop////            if(fabs(mdcKalTrk->charge()) != 1) continue;
//for gamloop////            HepVector a2 = mdcKalTrk->getZHelix();
//for gamloop////            HepSymMatrix Ea2 = mdcKalTrk->getZError();
//for gamloop////            VFHelix helixip3_2(point0,a2,Ea2);
//for gamloop////            helixip3_2.pivot(IP);
//for gamloop////            HepVector  vecipa2 = helixip3_2.a();
//for gamloop////
//for gamloop////            double dr1 = fabs(vecipa2[0]);
//for gamloop////            double drz = fabs(vecipa2[3]);
//for gamloop////            m_vxy_5_11 = dr1;
//for gamloop////            m_vz_5_11 = drz;
//for gamloop////            m_phi_5_11 = mdcKalTrk->phi();
//for gamloop////        }//end save tag lam_pi
//for gamloop////
//for gamloop////        if(tag_piid2.size()>0) {//tag xi_pi
//for gamloop////            EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + tag_piid2[n];     
//for gamloop////            if(!(*itTrk)->isMdcKalTrackValid()) continue;
//for gamloop////            RecMdcKalTrack*  mdcKalTrk = (*itTrk)->mdcKalTrack();
//for gamloop////            RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
//for gamloop////            if(fabs(mdcKalTrk->charge()) != 1) continue;
//for gamloop////            HepVector a2 = mdcKalTrk->getZHelix();
//for gamloop////            HepSymMatrix Ea2 = mdcKalTrk->getZError();
//for gamloop////            VFHelix helixip3_2(point0,a2,Ea2);
//for gamloop////            helixip3_2.pivot(IP);
//for gamloop////            HepVector  vecipa2 = helixip3_2.a();
//for gamloop////
//for gamloop////            double dr1 = fabs(vecipa2[0]);
//for gamloop////            double drz = fabs(vecipa2[3]);
//for gamloop////            m_vxy_6_11 = dr1;
//for gamloop////            m_vz_6_11 = drz;
//for gamloop////            m_phi_6_11 = mdcKalTrk->phi();
//for gamloop////        }//end save tag xi_pi
//for gamloop////
//for gamloop////        ncount2 = 1;
//for gamloop////    }//minimum chi2_2c
//for gamloop////}//for gam loop
//    }//minimum delm_lam_sig

}//for e2 loop
}//for pi0 loop
}//for e loop
//}//for pi loop
}//for p loop

double gamE=0.;
for(int h=0;h<gamnumber;h++){ 
    if(sig_gamid==h) continue;
    double	gam_angle=Gamvector[h].angle(Evector_new);
    gamE+=Gamvector[h].e();
    gam_e1=Gamvector[h].e();
    if(gam_e1>=gam_cut)   {
        gam_cut = gam_e1;
        gam_emax=gam_e1;
    }
ncount2 = 1;
}
gam_e=gamE;
int cosmicray=0;
if (cosmic_ok) { cosmicray = 1;}
if(ncount2==1)
{
    topo_temp_11              =  numParticle;

    for(int i=0;i<numParticle;i++){
        pdgid_temp_11[i]          =                vpdgid[i];
        mcidx_temp_11[i]          =            vmotheridx[i];
    }

    x1[5]++;
    //angle1_temp_11            =                   angle1;
    //angle2_temp_11            =                   angle2;
    //angle3_temp_11            =                   angle3;
    //angle4_temp_11            =                   angle4;
    //angle5_temp_11            =                   angle5;
    //angle6_temp_11            =                   angle6;
    //angle7_temp_11            =                   angle7;

    T_angle1_temp_11          =            tag_angle1[n];
    T_angle2_temp_11          =            tag_angle2[n];
    T_angle3_temp_11          =            tag_angle3[n];
    T_angle4_temp_11          =            tag_angle4[n];
    T_angle5_temp_11          =            tag_angle5[n];

    p_sig_1_temp_11           =                  p_sig_1;
    p_sig_2_temp_11           =                  p_sig_2;
    p_sig_3_temp_11           =                  p_sig_3;
    p_sig_4_temp_11           =                  p_sig_4;
    c_sig_1_temp_11           =                  c_sig_1;
    c_sig_2_temp_11           =                  c_sig_2;
    c_sig_3_temp_11           =                  c_sig_3;

    p_tag_1_temp_11           =                  p_tag_11;
    p_tag_2_temp_11           =                  p_tag_12;
    p_tag_3_temp_11           =                  p_tag_13;
    c_tag_1_temp_11           =                  c_tag_11;
    c_tag_2_temp_11           =                  c_tag_12;
    c_tag_3_temp_11           =                  c_tag_13;

    index_temp_11             =                        4;
    //V4_0_temp_11[0]           =                v4_0.px();
    //V4_0_temp_11[1]           =                v4_0.py();
    //V4_0_temp_11[2]           =                v4_0.pz();
    //V4_0_temp_11[3]           =                v4_0.e();

    V4_1_temp_11[0]           =                v4_1_4c.px();
    V4_1_temp_11[1]           =                v4_1_4c.py();
    V4_1_temp_11[2]           =                v4_1_4c.pz();
    V4_1_temp_11[3]           =                v4_1_4c.e();

    V4_2_temp_11[0]           =                v4_2_4c.px();
    V4_2_temp_11[1]           =                v4_2_4c.py();
    V4_2_temp_11[2]           =                v4_2_4c.pz();
    V4_2_temp_11[3]           =                v4_2_4c.e();

    V4_3_temp_11[0]           =                v4_3_4c.px();
    V4_3_temp_11[1]           =                v4_3_4c.py();
    V4_3_temp_11[2]           =                v4_3_4c.pz();
    V4_3_temp_11[3]           =                v4_3_4c.e();

    V4_4_temp_11[0]           =                v4_4_4c.px();
    V4_4_temp_11[1]           =                v4_4_4c.py();
    V4_4_temp_11[2]           =                v4_4_4c.pz();
    V4_4_temp_11[3]           =                v4_4_4c.e();

    V4_5_temp_11[0]           =                v4_5_4c.px();
    V4_5_temp_11[1]           =                v4_5_4c.py();
    V4_5_temp_11[2]           =                v4_5_4c.pz();
    V4_5_temp_11[3]           =                v4_5_4c.e();

    V4_6_temp_11[0]           =                v4_6_4c.px();
    V4_6_temp_11[1]           =                v4_6_4c.py();
    V4_6_temp_11[2]           =                v4_6_4c.pz();
    V4_6_temp_11[3]           =                v4_6_4c.e();

    V4_7_temp_11[0]           =                v4_7_4c.px();
    V4_7_temp_11[1]           =                v4_7_4c.py();
    V4_7_temp_11[2]           =                v4_7_4c.pz();
    V4_7_temp_11[3]           =                v4_7_4c.e();

    evp_2_temp_11             =                evp_sig_e1;
    eemc_2_temp_11            =                eemc_sig_e1; 
    evp_3_temp_11             =               evp_sig_e2;
    eemc_3_temp_11            =               eemc_sig_e2; 

    kmfit_chi_temp_11         =                chi_4c;
    kmfit_chi2_temp_11        =                chi_3c;

    mdbc1_temp_11             =                    mdbc1;
    mdbc2_temp_11             =                    mdbc2;
    mcmode1_temp_11           =                  mcmode1;
    mcmode2_temp_11           =                  mcmode2;
    mcmodea_temp_11           =                  mcmodea;
    mcmodeb_temp_11           =                  mcmodeb;
    m_irec_temp_11            =                    event;
    m_irun_temp_11            =                    runNo;
    cosmicray_temp_11         =                cosmicray;

    tag_mass_bc_temp_11       =              tag_mass_bc;
    tag_deltaE_temp_11        =               tag_deltaE;
    tag_mass_temp_11          =                 tag_mass;
    m_chi2_pi0          =                 chi2_pi0;
    m_chi2_min          =                 chi2_min;
    m_ee_rec_4c          =                 Mee_rec_4c;
    m_mpi0_4c          =                 Mpi0_4c;
    T_tagmode_temp_11         =                T_tagmode;
    tag_tagcharge_temp_11     =             sigtagcharge;
    p_theta_temp_11           =              m_pdp_theta;
    Ncharge_ex_temp_11        =               Ncharge_ex;

    gam_e_temp_11             =                    gam_e;
    gam_emax_temp_11          =                 gam_emax;
    mctag_temp_11             =                  m_mctag;

    u_miss_temp_11            =                   u_miss;
    e_miss_temp_11            =                   e_miss;
    p_miss_temp_11            =                   p_miss;
    miss_m2_temp_11           =                  miss_m2;
    mass_sig_sigma0e_temp_11  =            mass_sig_sigma0e;
    q2_temp_11                =                       q2;

    esig_V_ebeam_temp_11       =             esig_V_ebeam;
    angle_lame_57_temp_11      =            angle_lame_57;
    angle_xilame_58_temp_11    =          angle_xilame_58;

    lam_tag_chi_temp_11    =   tag_Lamchi[n];
    lam_tag_len_temp_11    =   tag_Lamlen[n];
    lam_tag_lenerr_temp_11 =   tag_Lamlenerr[n];
    xi_tag_chi_temp_11     =   tag_Xichi[n];
    xi_tag_len_temp_11     =   tag_Xilen[n];
    xi_tag_lenerr_temp_11  =   tag_Xilenerr[n];

    lam_sig_chi_temp_11    =   lam_sig_chi_temp;
    lam_sig_len_temp_11    =   lam_sig_len_temp;
    lam_sig_lenerr_temp_11 =   lam_sig_lenerr_temp;

    xi_sig_chi_temp_11     =   xi_chi_sig;
    xi_sig_len_temp_11     =   xi_len_sig;
    xi_sig_lenerr_temp_11  =   xi_lenerr_sig;

    mass_xi_tag_4c_temp_11 =   mass_xi_tag_4c;
    mass_xi_sig_4c_temp_11 =   mass_xi_sig_4c;
    mass_jpsi_4c_temp_11   =   mass_jpsi;

    m_ngoodtrk_11          =   munumber;
    m_ngoodgam_11          =   gamnumber;
    m_nchartrk_11          =   evtRecEvent->totalCharged();
    reco_mass_temp_11      =   tag_mass_reco[n];
    tag_lam_mass_temp_11   =   tag_Lamvector[n].m();
    tag_xi_mass_temp_11    =   tag_Xivector[n].m();
    sig_lam_mass_temp_11   =   v4_1.m();
    sig_sigma0_mass_temp_11=   v4_0.m();
    recomass_xilam_temp_11 =   recomass_xilam_temp;
    recomass_xie_temp_11   =   recomass_xie_temp;
    m_tuple11->write();                              
}//fill tree

}//tagmode==1
////////////////////////////////////////////////////////
}//////////sig_num
/////////////////////////////////////////////////////////////////////////////////////end of signal side

/////////////////////////////////////////////////
} /////////////execute

//bool Sigmap_ee::FIndMode(int mode){
//}

bool Sigmap_ee::same(int id[20]){
    bool sm=false;
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            if(id[i]==id[j]&&id[i]!=-1&&id[j]!=-1&&i!=j)sm=true;
        }
    }
    return sm;
}

void Sigmap_ee::set0()
{
    //bool
    oksq_4c_2=false, oksq_4c=false;
    mini_delE=false; oksq_3c=false;
    //////int
    T_tagmode=0;	tagmode_temp=0;	tagcharge_temp=0;	sigtagcharge=0;	ncount=0;	
    ncount2=0;	Ncharge_ex=999;
    /////double
    p_sig_1=999;	p_sig_2=999;	p_sig_3=999;    p_sig_4=999;
    c_sig_1=999;	c_sig_2=999;	c_sig_3=999;
    p_tag_11=999;	p_tag_12=999;	p_tag_13=999;
    c_tag_11=999;	c_tag_12=999;	c_tag_13=999;
    angle_lame_57_4c_2=999; angle_lame_57=999; angle_xilame_58=999; pte2_temp=999;
    xinvmass=0;	 reco_mass=0;	pdp_rho_temp=0;	pdp_e_temp=0.;  mass_bc_temp=0;	deltaE_temp=99;	m_pdp_theta=99;	deltaE_cut=0.2;			
    mass_tag_lam_temp=0;  mass_tag_reco_temp=0; mass_sig_sigma0e=0; q2=999;
    mass_bc_temp_2=0; deltaE_temp_2=99;
    tag_pid_temp=999;	tag_pi0id1_temp=999;	

    p_tag_0=999; c_tag_0=999; phi_tag_0=999;
    eemc_tag_1=0.; evp_tag_1=0.; p_tag_1=999; c_tag_1=999; phi_tag_1=999;
    eemc_tag_2=0.; evp_tag_2=0.; p_tag_2=999; c_tag_2=999; phi_tag_2=999;
    eemc_tag_3=0.; evp_tag_3=0.; p_tag_3=999; c_tag_3=999; phi_tag_3=999;
    eemc_tag_4=0.; evp_tag_4=0.; p_tag_4=999; c_tag_4=999; phi_tag_4=999;

    eemc_sig_e_svf=0.; eemc_sig_p_svf=0.; evp_sig_e_svf=0.; evp_sig_p_svf=0.;
    eemc_sig_e1=0.; eemc_sig_p1=0.; evp_sig_e1=0.; evp_sig_p1=0.;
    eemc_sig_e2=0.; eemc_sig_p2=0.; evp_sig_e2=0.; evp_sig_p2=0.;
    eemc_sig_pi=0.;evp_sig_pi=0.;
    eemc_sig_1_4c=0.; eemc_sig_2_4c=0.; evp_sig_1_4c=0.; evp_sig_2_4c=0.;
    tag_pi0id2_temp=999; tag_piid_temp=999;   tag_pid_temp_2=999;      tag_piid_temp_2=999;
    tag_piid2_temp=999; sig_gamid=999;
    sig_pid_temp_2=999; sig_eid_temp_2=999;
    angle1=999.;	angle2=999.;	angle3=999.;	angle4=999.;	angle5=999.;	angle6=999.; angle7=999.;
    T_angle1=999.;	T_angle2=999.;	T_angle3=999.;	T_angle4=999.;	T_angle5=999.;           
    emce=0;	chi_cut=999;	tag_mass_bc=0;
    u_miss=999;	e_miss=999;	p_miss=999;    miss_m2=999;	esig_V_ebeam=999; 
    u_miss_4c_2=999; e_miss_4c_2=999; p_miss_4c_2=999; miss_m2_4c_2=999; esig_V_ebeam_4c_2=999;
    lam_chi_tag=999;lam_lenerr_tag=0; lam_len_tag=0; gam_cut=0;
    mass_xi_tag_4c=999; mass_xi_sig_4c=999; chi_4c=999; chi_4c_2=999; mass_jpsi=999;
    xi_chi_sig=999; xi_len_sig=0; xi_lenerr_sig=999; chi_3c=999;
    lam_sig_chi_temp=999; lam_sig_len_temp=0; lam_sig_lenerr_temp=0;
    gam_e1=999;	gam_emax=0;	gam_e=999;	kmfit_chi=999;
    tag_deltaE=999; Mee_rec_4c=999; Mpi0_4c=999.;tag_mass=999;chi2_pi0=999 ;recomass_xilam_temp=0; recomass_xie_temp=0; chi2_min=999;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Sigmap_ee::finalize() {
    MsgStream log(msgSvc(), name());/////////////////////
    log << MSG::INFO << "in finalize()" << endmsg;
    cout<<"**************** Version(0630) *******************"<<endl;
    cout<<">    pion selected                   : "<<x0[0]<<endl;
    cout<<">    electron selected               : "<<x0[1]<<endl;
    cout<<">    proton selected                 : "<<x0[2]<<endl;
    cout<<">    lambda selected                 : "<<x0[3]<<endl;
    cout<<">    xi selected                     : "<<x0[4]<<endl;
    cout<<">    tag:xi charge==tagcharge        : "<<x0[5]<<endl;
    cout<<">    tag:xi_p charge!=tagcharge      : "<<x0[6]<<endl;
    cout<<">    tag:xi_pi charge==tagcharge     : "<<x0[7]<<endl;
    cout<<">    tag:no same id                  : "<<x0[8]<<endl;
    cout<<">    sig:p!=tagcharge                : "<<x0[9]<<endl;
    cout<<">    sig:pi==tagcharge               : "<<x0[10]<<endl;
    cout<<">    sig:echarge==tagcharge          : "<<x0[9]<<endl;
    cout<<">    sig:no same id                  : "<<x0[10]<<endl;
    cout<<"*************** for cut flow *********************"<<endl;
    cout<<">    total events                    : "<<tot_events<<endl;
    cout<<">    taged events                    : "<<x1[0]<<endl;
    cout<<">    Good charged tracks == 6        : "<<x1[1]<<endl;
    cout<<">    vertex fit in sig               : "<<x1[2]<<endl;
    cout<<">    second vertex fit in sig        : "<<x1[3]<<endl;
    cout<<">    4C kinematic fit                : "<<x1[4]<<endl;
    cout<<">    signal candidates               : "<<x1[5]<<endl;
    cout<<"**************************************************"<<endl;
    return StatusCode::SUCCESS;
}
