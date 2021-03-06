#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"
#include "McTruth/McParticle.h" //need to add use McTruth in the requirements of cmt
#include "EvTimeEvent/RecEsTime.h"

#include "Identifier/Identifier.h"

#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#include "pipipi0Alg/util/MyIsPID.h"
#include "pipipi0Alg/util/MyUtil.h"
#include "pipipi0Alg/util/MyInitIP.h"
#include "pipipi0Alg/util/MyIsGoodtrack.h"
#include "pipipi0Alg/util/MyTrk.h"

#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"
#include <iomanip>
#include <vector>
#include "VertexFit/BField.h"


#include "/workfs/bes/liumeihong/workarea/boss7.0.3/Reconstruction/GammaConv/GammaConv-00-00-01/GammaConv/GammaConv.h"

#include "pipipi0Alg/pipipi0Alg.h"
#include "HadronInfo/TrackInfo.h"

//#include "DTagAlg/LocalPi0Selector.h"
//#include "DTagAlg/LocalEtatoGGSelector.h"

const double mpi     = 0.13957018;
const double mpi0 = 0.134977;
const double meta = 0.547862;
const double mproton = 0.938272081;
const double me      = 0.000511;
const double metap   = 0.95778;
typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;

int Ncut[10];
////////////:///////////////////////////////////////////////////////////////
pipipi0Alg::pipipi0Alg(const std::string& name, ISvcLocator* pSvcLocator) :
    Algorithm(name, pSvcLocator) {
        m_nEvtDisp = 200;
        m_nEvt = 0;

        declareProperty("MCTruth",       m_mctruth = 1);
        declareProperty("test_4C",       m_test_4C = 1);
        declareProperty("test_5C",       m_test_5C = 1);
        declareProperty("cms",           m_cms     = 3.097);
        declareProperty("cms_id",        m_cms_id  = 443); // J/psi
    }

//########################################################################
StatusCode pipipi0Alg::initialize(){
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "in initialize()" << endmsg;

    StatusCode status;

    NTuplePtr nt1(ntupleSvc(), "FILE1/mctruth");
    if ( nt1 ) m_tuple1 = nt1;
    else {
        m_tuple1 = ntupleSvc()->book ("FILE1/mctruth", CLID_ColumnWiseTuple, "mctruth");
        if ( m_tuple1 ){
            m_tuple1->addItem ("run",       m_run  );
            m_tuple1->addItem ("event",     m_event);

            m_tuple1->addItem("indexmc",   m_idxmc, 0, 100);
            m_tuple1->addItem("pdgid",     m_idxmc, m_pdgid);
            m_tuple1->addItem("motheridx", m_idxmc, m_motheridx);

            m_tuple1->addItem ("mctrue_gam_pi0",       4,             m_mctrue_gam_pi0);
            m_tuple1->addItem ("mctrue_gam_theta",            m_mctrue_gam_theta);
            m_tuple1->addItem ("mctruth_mpipietap_phsp",            m_mctruth_mpipietap_phsp);
            m_tuple1->addItem ("mctrue_ep",       4,             m_mctrue_ep);
            m_tuple1->addItem ("mctrue_em",       4,             m_mctrue_em);
            m_tuple1->addItem ("mctrue_pip",       4,             m_mctrue_pip);
            m_tuple1->addItem ("mctrue_pim",       4,             m_mctrue_pim);
            m_tuple1->addItem ("mctrue_pip_etap_4c",       4,             m_mctrue_pip_etap_4c);
            m_tuple1->addItem ("mctrue_pim_etap_4c",       4,             m_mctrue_pim_etap_4c);
            m_tuple1->addItem ("mctrue_gam_etap_4c",       4,             m_mctrue_gam_etap_4c);
            m_tuple1->addItem ("mctrue_gam_etap_theta",                   m_mctrue_gam_etap_theta);
            m_tuple1->addItem ("mctrue_mpipietap_4c",                    m_mctrue_mpipietap_4c);
            m_tuple1->addItem ("mctrue_mee_4c",                    m_mctruth_ee_4c);
            m_tuple1->addItem ("mctrue_mpipi_4c",                    m_mctrue_mpipi_4c);
            m_tuple1->addItem ("mctrue_mrho_4c",                    m_mctrue_mrho_4c);
            m_tuple1->addItem ("mctrue_mpipetap_4c",                    m_mctrue_mpipetap_4c);
            m_tuple1->addItem ("mctrue_mpimetap_4c",                    m_mctrue_mpimetap_4c);
            m_tuple1->addItem ("mctrue_mee_5c",                    m_mctruth_ee_5c);
            m_tuple1->addItem ("mctrue_pip_etap_5c",       4,             m_mctrue_pip_etap_5c);
            m_tuple1->addItem ("mctrue_pim_etap_5c",       4,             m_mctrue_pim_etap_5c);
            m_tuple1->addItem ("mctrue_gam1_eta_5c",       4,             m_mctrue_gam1_eta_5c);
            m_tuple1->addItem ("mctrue_gam2_eta_5c",       4,             m_mctrue_gam2_eta_5c);
            m_tuple1->addItem ("mctruth_ep_4c",       4,             m_mctruth_ep_4c);
            m_tuple1->addItem ("mctruth_em_4c",       4,             m_mctruth_em_4c);
            m_tuple1->addItem ("mctruth_pi0gam_4c",       4,          m_mctruth_pi0gam_4c);
            m_tuple1->addItem ("mctruth_pi0gam_2_4c",       4,          m_mctruth_pi0gam_2_4c);
            m_tuple1->addItem ("mctruth_m1835",       4,          m_mctruth_m1835);
            m_tuple1->addItem ("m1835_mct",                 m1835_mct);
            m_tuple1->addItem ("mctr_pep",            mctr_pep);
            m_tuple1->addItem ("mctr_pem",            mctr_pem);
            m_tuple1->addItem ("mctr_gam1",            mctr_gam1);
            m_tuple1->addItem ("mctr_gam2",            mctr_gam2);
            m_tuple1->addItem ("mctr_Pgam_max",            mctr_Pgam_max);
            m_tuple1->addItem ("mctr_Pgam_min",            mctr_Pgam_min);
            m_tuple1->addItem ("mctrue_mpipietap_5c",                    m_mctrue_mpipietap_5c);
            m_tuple1->addItem ("mctrue_metap_5c",                    m_mctrue_metap_5c);
            m_tuple1->addItem ("mctrue_mpipetap_5c",                    m_mctrue_mpipetap_5c);
            m_tuple1->addItem ("mctrue_mpimetap_5c",                    m_mctrue_mpimetap_5c);
            m_tuple1->addItem ("mctrue_mpipi_5c",                    m_mctrue_mpipi_5c);

            //m_tuple1->addItem("p4_tru",   15, 4, m_p4_tru);    
            //m_tuple1->addItem("p_tru" ,   15,    m_p_tru);    
            //m_tuple1->addItem("m_tru" ,   15,    m_m_tru);    
            //m_tuple1->addItem("cos_tru" , 15,    m_cos_tru);    

        }else{
            log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
            return StatusCode::FAILURE;
        }
    }

    NTuplePtr nt2(ntupleSvc(), "FILE1/cccc");
    if ( nt2 ) m_tuple2 = nt2;
    else {
        m_tuple2 = ntupleSvc()->book("FILE1/cccc", CLID_ColumnWiseTuple, " N-Tuple example");
        if ( m_tuple2 ){
            m_tuple2->addItem ("rec_run",       m_rec_run  );
            m_tuple2->addItem ("rec_event",     m_rec_event);
            m_tuple2->addItem ("rec_nchrg",     m_rec_nchrg);
            m_tuple2->addItem ("rec_nneu",      m_rec_nneu);

            m_tuple2->addItem("indexmc",        m_rec_idxmc, 0, 1000);
            m_tuple2->addItem("pdgid",          m_rec_idxmc, m_rec_pdgid);
            m_tuple2->addItem("motheridx",      m_rec_idxmc, m_rec_motheridx);

            m_tuple2->addItem ("ngam",              m_ngam,      0, 1000 );
            m_tuple2->addItem ("nGam",              m_nGam);
            m_tuple2->addItem ("dang",              m_ngam,      m_dang );
            m_tuple2->addItem ("tdc",               m_ngam,      m_tdc  );
            m_tuple2->addItem ("angle",             m_ngam,      m_angle );
            m_tuple2->addItem ("energy",            m_ngam,      m_energy);
            m_tuple2->addItem ("phopx",             m_ngam,      m_phopx );
            m_tuple2->addItem ("phopy",             m_ngam,      m_phopy );
            m_tuple2->addItem ("phopz",             m_ngam,      m_phopz );
            m_tuple2->addItem ("phoe",              m_ngam,      m_phoe );
            m_tuple2->addItem ("eseed",             m_ngam,      m_eseed );
            m_tuple2->addItem ("e3x3",              m_ngam,      m_e3x3 );
            m_tuple2->addItem ("e5x5",              m_ngam,      m_e5x5 );
            m_tuple2->addItem ("theta",             m_ngam,      m_theta );
            m_tuple2->addItem ("phi",               m_ngam,      m_phi );
            m_tuple2->addItem ("secondMoment",      m_ngam,      m_secondMoment );
            m_tuple2->addItem ("latMoment",         m_ngam,      m_latMoment );
            m_tuple2->addItem ("a20Moment",         m_ngam,      m_a20Moment );
            m_tuple2->addItem ("a42Moment",         m_ngam,      m_a42Moment );
            m_tuple2->addItem ("eall",              m_ngam,      m_eall );
            m_tuple2->addItem ("elep",              m_ngam,      m_elep );
            m_tuple2->addItem ("edel",              m_ngam,      m_edel );
            m_tuple2->addItem ("ratio_e19",         m_ngam,      m_ratio_e19 );
            m_tuple2->addItem ("ratio_e925",        m_ngam,      m_ratio_e925 );
            m_tuple2->addItem ("ratio_e125",        m_ngam,      m_ratio_e125 );

            m_tuple2->addItem ("ngampairs",         m_ngpairs,   0, 1000 );
            m_tuple2->addItem ("mgg",               m_ngpairs,   m_mgg );
            m_tuple2->addItem ("ncomb",         m_ncomb,   0, 1000 );
            m_tuple2->addItem ("metap_rho_allcomb_4c",      m_ncomb,  m_etap_rho_allcomb_4c );
            m_tuple2->addItem ("ncomb_pi0_ppe",         m_ncomb_pi0_ppe,   0, 1000 );
            m_tuple2->addItem ("ncomb_pi0_rho",         m_ncomb_pi0_rho,   0, 1000 );
            m_tuple2->addItem ("nigam0_da",         m_nigam0_da,   0, 1000 );
            m_tuple2->addItem ("Egam0_all",                 m_Egam0_all);
            m_tuple2->addItem ("EE_all",                 m_EE_all);
            m_tuple2->addItem ("Egam0",                     m_Egam0);
            m_tuple2->addItem ("mgam0ee_allcomb_5c",      m_ncomb_pi0_ppe,  m_mgam0ee_allcomb_5c );
            //m_tuple2->addItem ("mgam0ee_allcomb_5c",      m_ngam-2,  m_mgam0ee_allcomb_5c );
            //m_tuple2->addItem ("mgam0ee_allcomb_4c",      m_ngam-1,  m_mgam0ee_allcomb_4c );
            m_tuple2->addItem ("mgam0ee_allcomb_4c",      m_ncomb_pi0_rho,  m_mgam0ee_allcomb_4c );
            m_tuple2->addItem ("ncomb_5c",         m_ncomb_5c,   0, 1000 );
            m_tuple2->addItem ("ncomb_x",         m_ncomb_x,   0, 1000 );
            m_tuple2->addItem ("ncomb_5c_x",         m_ncomb_5c_x,   0, 1000 );
            //m_tuple2->addItem ("mgam0ee_allcomb_5c",      m_ncomb_pi0_ppe,  m_mgam0ee_allcomb_5c );
            //m_tuple2->addItem ("mgam0ee_allcomb_4c",      m_ncomb_pi0_rho,  m_mgam0ee_allcomb_4c );
            m_tuple2->addItem ("metap_allcomb_5c",      m_ncomb_5c,  m_etap_allcomb_5c );
            m_tuple2->addItem ("mpipietap_rho_allcomb_4c",      m_ncomb_x,  m_pipietap_rho_allcomb_4c );
            m_tuple2->addItem ("mpipietap_allcomb_5c",      m_ncomb_5c_x,  m_pipietap_allcomb_5c );

            m_tuple2->addItem ("mpi0_gg",                        m_mpi0_gg );
            m_tuple2->addItem ("meta_gg",                        m_meta_gg );
            m_tuple2->addItem ("mgamee_eta",                     m_mgamee_eta );
            m_tuple2->addItem ("mgamee_rho",                     m_mgamee_rho );

            //combine any gam with e+e-
            m_tuple2->addItem ("mgameepairs_eta",  m_ngam,   m_mgameepairs_eta );
            m_tuple2->addItem ("mgameepairs_rho",  m_ngam,   m_mgameepairs_rho );
            m_tuple2->addItem ("ngamma",         m_ngamma,   0, 1000 );
            m_tuple2->addItem ("mgameepairs_allcomb_rho",  m_ngamma,  m_mgameepairs_allcomb_rho );

            //combine any gam with pi+pi- which are decayed from eta'
            m_tuple2->addItem ("mgampipipairs_eta",  m_ngam,   m_mgampipipairs_eta );
            m_tuple2->addItem ("mgampipipairs_rho",  m_ngam,   m_mgampipipairs_rho );

            //m_tuple2->addItem ("prob_chp",       3, 10 ,         m_prob_chp);
            //m_tuple2->addItem ("prob_chm",       3, 10 ,         m_prob_chm);

            //m_tuple2->addItem ("p4_wo4_pip",     2, 4  ,         m_p4_wo4_pip);
            //m_tuple2->addItem ("p4_wo4_pim",     2, 4  ,         m_p4_wo4_pim);
            //m_tuple2->addItem ("p4_wo4_elp",     2, 4  ,         m_p4_wo4_elp);
            //m_tuple2->addItem ("trk_info_pip",   2, 15 ,         m_trk_info_pip);
            //m_tuple2->addItem ("trk_info_pim",   2, 15 ,         m_trk_info_pim);
            //m_tuple2->addItem ("trk_info_elp",   2, 15 ,         m_trk_info_elp);

            m_tuple2->addItem ("elep_pid_prob",                    m_elep_pid_prob );
            m_tuple2->addItem ("elep_pid_probR",                   m_elep_pid_probR );
            m_tuple2->addItem ("elem_pid_prob",                    m_elem_pid_prob );
            m_tuple2->addItem ("elem_pid_probR",                   m_elem_pid_probR );

            m_tuple2->addItem ("ich",                 6,         m_ich);
            m_tuple2->addItem ("nch",                 6,         m_nch);
            m_tuple2->addItem ("id_track_wo4",        6,         m_id_track_wo4);

            m_tuple2->addItem ("numpion",  m_npion);

            m_tuple2->addItem ("vxchisq_ee",  m_vxchisq_ee);
            m_tuple2->addItem ("vxchisq",  m_vxchisq);
            // gamma conversation from Vindy and Yateng's help
            m_tuple2->addItem ("Rx_Gam_gamcon",                  Rx_Gam_gamcon);
            m_tuple2->addItem ("Ry_Gam_gamcon",                  Ry_Gam_gamcon);
            m_tuple2->addItem ("Rvxy_Gam_gamcon",                Rvxy_Gam_gamcon);

            m_tuple2->addItem ("xconv_gamcon",                   xconv_gamcon);
            m_tuple2->addItem ("yconv_gamcon",                   yconv_gamcon);
            m_tuple2->addItem ("rconv_gamcon",                   rconv_gamcon);

            m_tuple2->addItem ("xconv1_gamcon",                  xconv1_gamcon);
            m_tuple2->addItem ("yconv1_gamcon",                  yconv1_gamcon);
            m_tuple2->addItem ("rconv1_gamcon",                  rconv1_gamcon);

            m_tuple2->addItem ("xconv2_gamcon",                  xconv2_gamcon);
            m_tuple2->addItem ("yconv2_gamcon",                  yconv2_gamcon);
            m_tuple2->addItem ("rconv2_gamcon",                  rconv2_gamcon);

            m_tuple2->addItem ("xconv3_gamcon",                  xconv3_gamcon);
            m_tuple2->addItem ("yconv3_gamcon",                  yconv3_gamcon);
            m_tuple2->addItem ("rconv3_gamcon",                  rconv3_gamcon);

            m_tuple2->addItem ("zconv_gamcon",                   zconv_gamcon);
            m_tuple2->addItem ("Dee_Mdc_gamcon",                 Dee_Mdc_gamcon);
            m_tuple2->addItem ("Dee_Bp_gamcon",                  Dee_Bp_gamcon);

            m_tuple2->addItem ("xiep_gamcon",                    xiep_gamcon);
            m_tuple2->addItem ("xiep_gamcon_1",                    xiep_gamcon_1);
            m_tuple2->addItem ("xiep_gamcon_2",                    xiep_gamcon_2);
            m_tuple2->addItem ("deltaxy_gamcon",                 deltaxy_gamcon);
            m_tuple2->addItem ("deltaphi0_ee",                   deltaphi0_ee);

            m_tuple2->addItem ("mconv_gamcon",                   mconv_gamcon);
            m_tuple2->addItem ("econv_gamcon",                   econv_gamcon);
            m_tuple2->addItem ("thetaconv_gamcon",               thetaconv_gamcon);
            m_tuple2->addItem ("costhetaconv_gamcon",            costhetaconv_gamcon);
            m_tuple2->addItem ("phiconv_gamcon",                 phiconv_gamcon);
            m_tuple2->addItem ("angEE_gamcon",                   angEE_gamcon);

            // 5c for Case1 eta' -> pi+ pi- eta, eta-> gamma gamma
            m_tuple2->addItem ("chi2_eta_5c",                    m_chi2_eta_5c);
            m_tuple2->addItem ("prob_eta_5c",                    m_prob_eta_5c);
            //m_tuple2->addItem ("p4_eta_5c",    9, 4,             m_p4_eta_5c);
            //m_tuple2->addItem ("eta_ig1",                        m_eta_ig1);
            //m_tuple2->addItem ("eta_ig2",                        m_eta_ig2);
            m_tuple2->addItem ("mgam0ee_ppe",                    m_gam0ee_ppe);
            m_tuple2->addItem ("mee_5c",                         m_ee_5c);
            m_tuple2->addItem ("meta_5c",                        m_eta_5c);
            m_tuple2->addItem ("metap_5c",                       m_etap_5c);
            m_tuple2->addItem ("mpipietap_5c",                   m_pipietap_5c);

            m_tuple2->addItem ("mpipieta_5c",      4,            m_pipieta_5c);

            m_tuple2->addItem ("mgamee_eta_5c",        2,            m_gamee_eta_5c);
            m_tuple2->addItem ("p4_eta_5c",        4,            m_p4_eta_5c);
            m_tuple2->addItem ("p4_ep_5c",         4,            m_p4_ep_5c);
            m_tuple2->addItem ("p4_em_5c",         4,            m_p4_em_5c);
            m_tuple2->addItem ("p4_pip1_5c",       4,            m_p4_pip1_5c);
            m_tuple2->addItem ("p4_pim1_5c",       4,            m_p4_pim1_5c);
            m_tuple2->addItem ("p4_pip2_5c",       4,            m_p4_pip2_5c);
            m_tuple2->addItem ("p4_pim2_5c",       4,            m_p4_pim2_5c);

            m_tuple2->addItem ("mee_kal",                        m_ee_kal);
            m_tuple2->addItem ("meta_kal",                       m_eta_kal);
            m_tuple2->addItem ("metap_kal",                      m_etap_kal);
            m_tuple2->addItem ("mpipietap_kal",                  m_pipietap_kal);

            m_tuple2->addItem ("p4_eta_kal",       4,            m_p4_eta_kal);
            m_tuple2->addItem ("p4_ep_kal",        4,            m_p4_ep_kal);
            m_tuple2->addItem ("p4_em_kal",        4,            m_p4_em_kal);
            m_tuple2->addItem ("p4_pip1_kal",      4,            m_p4_pip1_kal);
            m_tuple2->addItem ("p4_pim1_kal",      4,            m_p4_pim1_kal);
            m_tuple2->addItem ("p4_pip2_kal",      4,            m_p4_pip2_kal);
            m_tuple2->addItem ("p4_pim2_kal",      4,            m_p4_pim2_kal);

            // 4c for Case2 eta' -> gamm rho, rho -> pi+ pi-
            m_tuple2->addItem ("chi2_rho_4c",                    m_chi2_4c);
            //m_tuple2->addItem ("p4_rho_4c",    7, 4,             m_p4_rho_4c);
            //m_tuple2->addItem ("rho_ig3",                        m_rho_ig3);
            m_tuple2->addItem ("prob_rho_4c",                    m_prob_4c);

            m_tuple2->addItem ("mgam0ee_rho",                    m_gam0ee_rho);
            m_tuple2->addItem ("mgamee_rho_4c",                  m_gamee_rho_4c);
            m_tuple2->addItem ("mpi0_4c",                        m_mpi0_4c);
            m_tuple2->addItem ("mee_rho_4c",                     m_ee_rho_4c);
            m_tuple2->addItem ("mee_rho_4c_rec",                 m_ee_rho_4c_rec);
            m_tuple2->addItem ("mee_rho_rec",                    m_ee_rho_rec);
            m_tuple2->addItem ("mpipietap_rho_4c_rec",           m_pipietap_rho_4c_rec);
            m_tuple2->addItem ("mpipietap_rho_rec",              m_pipietap_rho_rec);
            m_tuple2->addItem ("mrho_4c",                        m_rho_4c);
            m_tuple2->addItem ("metap_rho_4c",                   m_etap_rho_4c);
            m_tuple2->addItem ("mpipietap_rho_4c",               m_pipietap_rho_4c);
            m_tuple2->addItem ("mpipi_rho_4c",      4,           m_pipi_rho_4c);

            m_tuple2->addItem ("p4_gam_rho_4c",     4,           m_p4_gam_rho_4c);
            m_tuple2->addItem ("gam_etap_theta_4c",              m_gam_etap_theta_4c);
            m_tuple2->addItem ("p4_ep_rho_4c",      4,           m_p4_ep_rho_4c);
            m_tuple2->addItem ("p4_em_rho_4c",      4,           m_p4_em_rho_4c);
            m_tuple2->addItem ("p4_pip1_rho_4c",    4,           m_p4_pip1_rho_4c);
            m_tuple2->addItem ("p4_pim1_rho_4c",    4,           m_p4_pim1_rho_4c);
            m_tuple2->addItem ("p4_pip2_rho_4c",    4,           m_p4_pip2_rho_4c);
            m_tuple2->addItem ("p4_pim2_rho_4c",    4,           m_p4_pim2_rho_4c);

            m_tuple2->addItem ("mee_rho_kal",                    m_ee_rho_kal);
            m_tuple2->addItem ("mrho_kal",                       m_rho_kal);
            m_tuple2->addItem ("metap_rho_kal",                  m_etap_rho_kal);
            m_tuple2->addItem ("mpipietap_rho_kal",              m_pipietap_rho_kal);

            m_tuple2->addItem ("p4_gam_rho_kal",    4,           m_p4_gam_rho_kal);
            m_tuple2->addItem ("p4_ep_rho_kal",     4,           m_p4_ep_rho_kal);
            m_tuple2->addItem ("p4_em_rho_kal",     4,           m_p4_em_rho_kal);
            m_tuple2->addItem ("p4_pip1_rho_kal",   4,           m_p4_pip1_rho_kal);
            m_tuple2->addItem ("p4_pim1_rho_kal",   4,           m_p4_pim1_rho_kal);
            m_tuple2->addItem ("p4_pip2_rho_kal",   4,           m_p4_pip2_rho_kal);
            m_tuple2->addItem ("p4_pim2_rho_kal",   4,           m_p4_pim2_rho_kal);
            m_tuple2->addItem ("mctrue_gam_etap_4c",   4,        m_mctrue_pgam_etap_4c);
            m_tuple2->addItem ("mctrue_pip",   4,        m_mctrue_ppip);
            m_tuple2->addItem ("mctrue_pim",   4,        m_mctrue_ppim);
            m_tuple2->addItem ("mctrue_pip_etap_4c",   4,        m_mctrue_ppip_etap_4c);
            m_tuple2->addItem ("mctrue_pip_etap_4c",   4,        m_mctrue_ppip_etap_4c);
            m_tuple2->addItem ("mctrue_pim_etap_4c",   4,        m_mctrue_ppim_etap_4c);
            m_tuple2->addItem ("mctrue_Ppip",        m_mctrue_Ppip);
            m_tuple2->addItem ("mctrue_Ppim",        m_mctrue_Ppim);
            m_tuple2->addItem ("mctrue_Ppip_etap_4c",        m_mctrue_Ppip_etap_4c);
            m_tuple2->addItem ("mctrue_Ppim_etap_4c",        m_mctrue_Ppim_etap_4c);
            m_tuple2->addItem ("mctrue_Pgam_etap_4c",        m_mctrue_Pgam_etap_4c);
            m_tuple2->addItem ("delta_angle_gam_etap_4c",        m_delta_angle_pgam_etap_4c);
            m_tuple2->addItem ("delta_angle_pip_etap_4c",        m_delta_angle_ppip_etap_4c);
            m_tuple2->addItem ("delta_angle_pim_etap_4c",        m_delta_angle_ppim_etap_4c);

            m_tuple2->addItem ("delta_angle",                    delta_angle);
            m_tuple2->addItem ("delta_energy",                   delta_energy);
            m_tuple2->addItem ("gampipi_ck",                     m_gampipi_ck);
            m_tuple2->addItem ("eepipi_ck_rho",                  m_eepipi_ck_rho);
            m_tuple2->addItem ("eepipi_ck",                      m_eepipi_ck);


        }else{
            log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple2) << endmsg;
            return StatusCode::FAILURE;
        }
    }
    log << MSG::INFO << "successfully return from initialize()" <<endmsg;
    return StatusCode::SUCCESS;

}
//************************************************************************
StatusCode pipipi0Alg::execute() {

    MsgStream log(msgSvc(), name());

    SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
    int runNo=eventHeader->runNumber();
    int event=eventHeader->eventNumber();
    Ncut[0]++;
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
    m_run        = runNo;
    m_event      = event;
    m_rec_run    = runNo;
    m_rec_event  = event;
    m_rec_nchrg  = evtRecEvent->totalCharged();
    m_rec_nneu   = evtRecEvent->totalNeutral();

    if(0 == (m_nEvt % m_nEvtDisp))
        std::cout << "Run num : " << runNo << ",  Event " << m_nEvt
            << ",   Event number online " << event << endl;
    m_nEvt++;

    SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
    //first obtain the MC truth generated information
    if(m_mctruth && runNo <0) {
        mctruth(); 
        m_tuple1->write(); 
    }

    // reconstruct 4 good charged tracks, and at least 1 good photons
    // 4 good charged tracks
    Hep3Vector xorigin(0,0,0);
    VertexParameter     m_privxpar;
    MyInitIP myInitIP;
    myInitIP.InitIP(xorigin,m_privxpar);

    vector<int> iGood;
    iGood.clear();
    int charge = 0;
    double costheta = -2;
    for(int i = 0 ; i < evtRecEvent->totalCharged() ; i++){
        EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
        if(isGoodTrack(*itTrk ,xorigin,costheta)){
            iGood.push_back(i);
            RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
            charge   += mdcTrk->charge();
        }
    }
    int nGood = iGood.size();
    if(!(nGood == 4 && charge ==0)) return StatusCode::SUCCESS; 
    Ncut[1]++;
    //nGood photons
    Vint iGam;
    iGam.clear();
    Vp4 pGam;
    pGam.clear();
    int igamma=0;
    for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
        if(i >= evtRecTrkCol->size()) break;
        EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
        if(!(*itTrk)->isEmcShowerValid()) continue;
        RecEmcShower *emcTrk = (*itTrk)->emcShower();
        double emctime = emcTrk->time();
        Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());
        double angle = emcTrk->theta();
        bool barrel_test=false;
        bool endcap_test=false;
        if(emcTrk->energy()>0.05&&fabs(cos(angle))<0.92&&fabs(cos(angle))>0.86) endcap_test=true;
        if(emcTrk->energy()>0.025&&fabs(cos(angle))<0.8) barrel_test=true;
        if(!(barrel_test||endcap_test)) continue;
        if(emctime>14. || emctime<0.) continue;
        // find the nearest charged track
        double dthe = 200.;
        double dphi = 200.;
        double dang = 200.;
        double tmp_dang_proton     = 200.;
        for(int j = 0; j < nGood; j++) {
            EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + iGood[j];
            if(!(*jtTrk)->isExtTrackValid()) continue;// extrapolate(waitui) track
            RecExtTrack *extTrk = (*jtTrk)->extTrack();
            if(extTrk->emcVolumeNumber() == -1) continue;
            RecMdcTrack *mdctrk = (*jtTrk)->mdcTrack();
            Hep3Vector extpos = extTrk->emcPosition();
            double angd = extpos.angle(emcpos);
            double thed = extpos.theta() - emcpos.theta();
            double phid = extpos.deltaPhi(emcpos);
            thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
            phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
            if(angd < tmp_dang_proton){
                tmp_dang_proton = angd;
                dthe = thed;
                dphi = phid;
            }
        }
        if(tmp_dang_proton > 200) continue;
        dthe = dthe * 180 / (CLHEP::pi);
        dphi = dphi * 180 / (CLHEP::pi);
        tmp_dang_proton     = tmp_dang_proton  * 180 / (CLHEP::pi);

        if(fabs(tmp_dang_proton)     < 10) continue;

        double eraw = emcTrk->energy();
        double the  = emcTrk->theta();
        double phi  = emcTrk->phi();

        HepLorentzVector ptrk;
        ptrk.setPx(eraw*sin(the)*cos(phi));
        ptrk.setPy(eraw*sin(the)*sin(phi));
        ptrk.setPz(eraw*cos(the));
        ptrk.setE(eraw);

        pGam.push_back(ptrk);


        m_phopx[igamma]         = ptrk.px();
        m_phopy[igamma]         = ptrk.py();
        m_phopz[igamma]         = ptrk.pz();
        m_phoe[igamma]          = ptrk.e();

        m_dang[igamma]          = tmp_dang_proton;
        m_tdc[igamma]           = emcTrk->time();
        m_angle[igamma]         = emcTrk->theta();
        m_energy[igamma]        = emcTrk->energy();

        m_eseed[igamma]         = emcTrk->eSeed(); 
        m_e3x3[igamma]          = emcTrk->e3x3(); 
        m_e5x5[igamma]          = emcTrk->e5x5(); 
        m_theta[igamma]         = emcTrk->theta();
        m_phi[igamma]           = emcTrk->phi();

        m_secondMoment[igamma]  = emcTrk->secondMoment();
        m_latMoment[igamma]     = emcTrk->latMoment();
        m_a20Moment[igamma]     = emcTrk->a20Moment();
        m_a42Moment[igamma]     = emcTrk->a42Moment();
        m_eall[igamma]          = emcTrk->getEAll();
        m_elep[igamma]          = emcTrk->getELepton();
        m_edel[igamma]          = emcTrk->dE();

        m_ratio_e19[igamma]     = emcTrk->eSeed()/emcTrk->e3x3();
        m_ratio_e925[igamma]    = emcTrk->e3x3()/emcTrk->e5x5();
        m_ratio_e125[igamma]    = emcTrk->eSeed()/emcTrk->e5x5();


        igamma++;

        iGam.push_back(i);
    }
    m_ngam   = igamma;

    int nGam = iGam.size();

    if(!(nGam >0 && nGam < 100)) return StatusCode::SUCCESS;
    Ncut[2]++;
    // loop over all gamma pair to check pi0, eta
    m_mpi0_gg = 0.0;
    m_meta_gg = 0.0;
    if (nGam > 1) {
        int igpairs = 0;

        double mpi0ini = 10.0;
        double metaini = 10.0;

        for(int i = 0; i < nGam - 1; i++){
            for(int j = i+1; j < nGam; j++) {
                HepLorentzVector p2g = pGam[i] + pGam[j];
                m_mgg[igpairs] = p2g.m();
                //find the two gammas most clost to pi0 and eta 
                if (abs(m_mgg[igpairs]-mpi0) < abs(mpi0ini - mpi0)) {
                    mpi0ini = m_mgg[igpairs];
                }
                if (abs(m_mgg[igpairs]-meta) < abs(metaini - meta)) {
                    metaini = m_mgg[igpairs];
                }

                igpairs++;
            }
        }

        m_ngpairs = igpairs;
        m_mpi0_gg = mpi0ini;
        m_meta_gg = metaini;
    }


    // do pid for proton and anti-proton

    Vint ichp;
    Vint ichm;
    Vint ipip;
    Vint ipim;
    Vint ielp;
    Vint ielm;
    ichp.clear();
    ichm.clear();
    ipip.clear();
    ipim.clear();
    ielp.clear();
    ielm.clear();

    Vp4 pPip_kal;
    Vp4 pPim_kal;
    pPip_kal.clear();
    pPim_kal.clear();

    HepLorentzVector pElep_kal(0., 0., 0., 0.);
    HepLorentzVector pElem_kal(0., 0., 0., 0.);

    int nchp = 0;
    int nchm = 0;
    int npip = 0;
    int npim = 0;
    int nelp = 0;
    int nelm = 0;

    int npion = 0;

    int ichm0 = -1;
    int ichm1 = -1;
   // int ichm2 = -1;
    int ichp0 = -1;
    int ichp1 = -1;
   // int ichp2 = -1;

    m_elep_pid_prob = -1.0;
    m_elep_pid_probR = -1.0;

    m_elem_pid_prob = -1.0;
    m_elem_pid_probR = -1.0;

    for(int k=0; k < iGood.size(); k++){
        EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[k];  	
        RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();		
        int  c0  = mdcTrk->charge();
        if(!(*itTrk)->isMdcTrackValid()) continue; 
        ParticleID *pid = ParticleID::instance();
        pid->init();
        pid->setMethod(pid->methodProbability());
        pid->setChiMinCut(4);
        pid->setRecTrack(*itTrk);
        //pid->usePidSys(pid->useDedx() | pid->useTofCorr() |  pid->useEmc() );
        //pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() |  pid->useEmc() );
        pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2());
        pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
        pid->calculate();
        if(!(pid->IsPidInfoValid()))     continue;
        double prob_pion     = -1.;
        double prob_kaon     = -1.;
        double prob_proton     = -1.;
        double prob_electron = -1.;
        double R_electron    = -1.;

        prob_pion     = pid->probPion();
        prob_kaon     = pid->probKaon();
        prob_proton     = pid->probProton();
        prob_electron = pid->probElectron();

        R_electron  =  prob_electron / (prob_electron + prob_pion + prob_kaon) ; 


        if(c0 >0) { 
            //isProton(*itTrk, m_prob_chp, nchp);
            //if(prob_electron > 0.001 && R_electron > 0.8)
            if(prob_electron > prob_pion && prob_electron > prob_kaon)
            {
                m_elep_pid_prob = prob_electron;
                m_elep_pid_probR = R_electron;
                //fillChargedTrkInfo(*itTrk, m_p4_wo4_elp, m_trk_info_elp, 0, 0); //suppose is e+, without 4c
                nelp++;
                ielp.push_back(k);
                ichp0 = nchp; 

                //assign four momentum to electron
                TrackInfo track1Info;
                track1Info.settrack(0, *itTrk);// e, mu, pi, K, p: 0,1,2,3,4;
                pElep_kal = track1Info.p4();
            }else{
                if(npip == 0){			
                    //fillChargedTrkInfo(*itTrk, m_p4_wo4_pip, m_trk_info_pip, 2, 0); //suppose is pion, without 4c
                    ichp1 = nchp; 
                }// else if (npip ==1 ){
                    //fillChargedTrkInfo(*itTrk, m_p4_wo4_pip, m_trk_info_pip, 2, 1); //suppose is pion, without 4c
                 //   ichp2 = nchp; 
               // }
                npip++; 
                ipip.push_back(k);		

                // assign four momentum to pion
                HepLorentzVector p4pion(0, 0, 0, 0);
                TrackInfo track1Info;
                track1Info.settrack(2, *itTrk);// e, mu, pi, K, p: 0,1,2,3,4;
                p4pion = track1Info.p4();

                pPip_kal.push_back(p4pion);

                if (prob_pion > prob_kaon && prob_pion > prob_proton) {
                    npion++;
                }
            }
            nchp++;	
            ichp.push_back(k);		
        }
        else if(c0<0) {
            //isProton(*itTrk, m_prob_chm, nchm);
            //if(prob_electron > 0.001 && R_electron > 0.8)
            if(prob_electron > prob_pion && prob_electron > prob_kaon)
            {
                m_elem_pid_prob = prob_electron;
                m_elem_pid_probR = R_electron;
                //fillChargedTrkInfo(*itTrk, m_p4_wo4_elp, m_trk_info_elp, 0, 1); //suppose is e-, without 4c
                nelm++;
                ielm.push_back(k) ;
                ichm0 = nchm; 

                //assign four momentum to positron
                TrackInfo track1Info;
                track1Info.settrack(0, *itTrk);// e, mu, pi, K, p: 0,1,2,3,4;
                pElem_kal = track1Info.p4();  
            }else {
                if(npim==0){			
                    //fillChargedTrkInfo(*itTrk, m_p4_wo4_pim, m_trk_info_pim, 2, 0); //suppose is pi-, without 4c
                    ichm1 = nchm; 
                }//else if(npim==1){
                    //fillChargedTrkInfo(*itTrk, m_p4_wo4_pim, m_trk_info_pim, 2, 1); //suppose is pi-, without 4c
                 //   ichm2 = nchm; 
               // }
                npim++;
                ipim.push_back(k) ;

                // assign four momentum to pion
                HepLorentzVector p4pion(0, 0, 0, 0);
                TrackInfo track1Info;
                track1Info.settrack(2, *itTrk);// e, mu, pi, K, p: 0,1,2,3,4;
                p4pion = track1Info.p4();

                pPim_kal.push_back(p4pion);

                if (prob_pion > prob_kaon && prob_pion > prob_proton) {
                    npion++;
                }
            }
            nchm++;
            ichm.push_back(k);		
        }

    } 

    m_ich[0]    = ichp0;
    m_ich[1]    = ichp1;
    //m_ich[2]    = ichp2;
    m_ich[2]    = ichm0;
    m_ich[3]    = ichm1;
    //m_ich[5]    = ichm2;

    m_nch[0]    = npip  ;
    m_nch[1]    = npim  ;
    m_nch[2]    = nelp  ;
    m_nch[3]    = nelm  ;
    m_nch[4]    = nchp  ;
    m_nch[5]    = nchm  ;


    int nnchp =0;
    int nnchm =0;
    int nnpip =0;
    int nnpim =0;
    int nnelp =0;
    int nnelm =0;

    nnchp = ichp.size();
    nnchm = ichm.size();
    nnpip = ipip.size();
    nnpim = ipim.size();
    nnelp = ielp.size();
    nnelm = ielm.size();


    if(!(nnchp == 2 && nnchm == 2 && nnpip == 1 && nnpim == 1 && nnelp == 1 && nnelm == 1))
        return StatusCode::SUCCESS;
    Ncut[3]++;
    //if (npion < 3)    return StatusCode::SUCCESS;
    m_npion = npion;
    Ncut[4]++;
    //   return StatusCode::SUCCESS;
    m_id_track_wo4[0] = ipip[0]; 
    m_id_track_wo4[1] = ipim[0]; 
    //m_id_track_wo4[2] = ipip[1]; 
    //m_id_track_wo4[3] = ipim[1]; 
    m_id_track_wo4[2] = ielp[0]; 
    m_id_track_wo4[3] = ielm[0]; 


    // do 4C for gamma gamma p pbar
    WTrackParameter wvpip1Trk,wvpim1Trk,wvelp1Trk,wvelm1Trk;
    //WTrackParameter wvpip1Trk,wvpim1Trk, wvpip2Trk,wvpim2Trk,wvelp1Trk,wvelm1Trk;

    RecMdcKalTrack *pip1Trk = (*(evtRecTrkCol->begin()+iGood[ipip[0]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    wvpip1Trk = WTrackParameter(mpi, pip1Trk->getZHelix(), pip1Trk->getZError());

    //RecMdcKalTrack *pip2Trk = (*(evtRecTrkCol->begin()+iGood[ipip[1]]))->mdcKalTrack();
    //RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    //wvpip2Trk = WTrackParameter(mpi, pip2Trk->getZHelix(), pip2Trk->getZError());

    RecMdcKalTrack *pim1Trk = (*(evtRecTrkCol->begin()+iGood[ipim[0]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    wvpim1Trk = WTrackParameter(mpi, pim1Trk->getZHelix(), pim1Trk->getZError());

    //RecMdcKalTrack *pim2Trk = (*(evtRecTrkCol->begin()+iGood[ipim[1]]))->mdcKalTrack();
    //RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    //wvpim2Trk = WTrackParameter(mpi, pim2Trk->getZHelix(), pim2Trk->getZError());

    RecMdcKalTrack *elp1Trk = (*(evtRecTrkCol->begin()+iGood[ielp[0]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
    wvelp1Trk = WTrackParameter(me, elp1Trk->getZHelixE(), elp1Trk->getZErrorE());

    RecMdcKalTrack *elm1Trk = (*(evtRecTrkCol->begin()+iGood[ielm[0]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
    wvelm1Trk = WTrackParameter(me, elm1Trk->getZHelixE(), elm1Trk->getZErrorE());


    //initial some variable for gamma conversation, from vindy and Yateng's help 
    double  Rx_Gam   = -100.;
    double  Ry_Gam   = -100.;
    double  Rvxy_Gam = -100.;

    double  xconv    = -100. ;
    double  yconv    = -100. ;
    double  zconv    = -100. ;
    double  rconv    = -100. ;

    double  Dee_Mdc  = -100. ;
    double  Dee_Bp   = -100. ;

    double  xiep     = -100. ;
    double  deltaxy  = -100.;
    double  deltaphi0  = -100.;

    double  mconv    = -100.;
    double  econv    = -100.;
    double  thetaconv= -100.;
    double  phiconv  = -100.;
    double  angEE    = -100.;
    double  costhetaconv= -100.;

    HepPoint3D vx_ee(0., 0., 0.);
    HepSymMatrix Evx_ee(3, 0);
    double bx_ee = 1E+6;
    double by_ee = 1E+6;
    double bz_ee = 1E+6;
    Evx_ee[0][0] = bx_ee*bx_ee;
    Evx_ee[1][1] = by_ee*by_ee;
    Evx_ee[2][2] = bz_ee*bz_ee;

    VertexParameter vxparraw_ee;
    vxparraw_ee.setVx(vx_ee);
    vxparraw_ee.setEvx(Evx_ee);

    VertexFit* vtxfit_ee = VertexFit::instance();
    vtxfit_ee->init();

    vtxfit_ee->AddTrack(0,  wvelp1Trk);
    vtxfit_ee->AddTrack(1,  wvelm1Trk);
    vtxfit_ee->AddVertex(0, vxparraw_ee,0, 1);

    if(!vtxfit_ee->Fit(0)) return StatusCode::SUCCESS;
    vtxfit_ee->Swim(0);
    m_vxchisq_ee = vtxfit_ee->chisq(0);

    HepPoint3D   vx_infit_ee  = vtxfit_ee->vx(0);
    HepSymMatrix Evx_infit_ee = vtxfit_ee->Evx(0);
    Rx_Gam          = vx_infit_ee.x();
    Ry_Gam          = vx_infit_ee.y();
    //double Rz_Gam          = vx_infit.z();
    Rvxy_Gam        = sqrt(Rx_Gam*Rx_Gam + Ry_Gam*Ry_Gam);

    // do vertex fit for the 4 charged tracks
    HepPoint3D vx(0., 0., 0.);
    HepSymMatrix Evx(3, 0);
    double bx = 1E+6;
    double by = 1E+6;
    double bz = 1E+6;
    Evx[0][0] = bx*bx;
    Evx[1][1] = by*by;
    Evx[2][2] = bz*bz;

    VertexParameter vxparraw;
    vxparraw.setVx(vx);
    vxparraw.setEvx(Evx);

    VertexFit* vtxfit = VertexFit::instance();
    vtxfit->init();  
    vtxfit->AddTrack(0,  wvpip1Trk);
    vtxfit->AddTrack(1,  wvpim1Trk);
    //vtxfit->AddTrack(2,  wvpip2Trk);
    //vtxfit->AddTrack(3,  wvpim2Trk);
    vtxfit->AddTrack(2,  wvelp1Trk);
    vtxfit->AddTrack(3,  wvelm1Trk);
    vtxfit->AddVertex(0, vxparraw,0, 1, 2, 3);

    if(!vtxfit->Fit(0)) return StatusCode::SUCCESS;
    vtxfit->Swim(0);

    m_vxchisq = vtxfit->chisq(0);
    Ncut[5]++;  

    WTrackParameter wpip1  = vtxfit->wtrk(0);
    WTrackParameter wpim1  = vtxfit->wtrk(1);
    WTrackParameter welp1  = vtxfit->wtrk(2);
    WTrackParameter welm1  = vtxfit->wtrk(3);

    // do vertex fit for the ee tracks

    HepLorentzVector p4Ep  = welp1.p();
    HepLorentzVector p4Em  = welm1.p();

    HepPoint3D   vx_infit  = vtxfit->vx(0);
    HepSymMatrix Evx_infit = vtxfit->Evx(0);

    //Rx_Gam          = vx_infit.x();
    //Ry_Gam          = vx_infit.y();
    //Rvxy_Gam        = sqrt((Rx_Gam-xorigin[0])*(Rx_Gam-xorigin[0]) + (Ry_Gam-xorigin[1])*(Ry_Gam-xorigin[1]));

    //--default IP --in 08 year 
    xorigin.setX(0.1);
    xorigin.setY(-0.255);
    xorigin.setZ(0);

    IVertexDbSvc* vtxsvc;
    Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    if(vtxsvc->isVertexValid()){
        double* vertex = vtxsvc->PrimaryVertex(); 
        double* vertexsigma = vtxsvc->SigmaPrimaryVertex();
        double* dbv = vtxsvc->PrimaryVertex();
        double* vv = vtxsvc->SigmaPrimaryVertex();

        xorigin.setX(dbv[0]);
        xorigin.setY(dbv[1]);
        xorigin.setZ(dbv[2]);

    }

    HepPoint3D IP_Gam(xorigin[0],xorigin[1],xorigin[2]);
    GammaConv gconv = GammaConv(elp1Trk->helix(), elm1Trk->helix(),IP_Gam);

    xconv           = gconv.getRX();
    yconv           = gconv.getRY();
    zconv           = gconv.getRZ();
    rconv           = gconv.getRXY();
    xiep            = gconv.getXiep();
    deltaxy         = gconv.getDeltaXY();
    deltaphi0         = gconv.getDeltaphi0();

    Dee_Mdc         = Get_Dee(elp1Trk->helix(),elm1Trk->helix(),5.9);
    Dee_Bp          = Get_Dee(elp1Trk->helix(),elm1Trk->helix(),3.15); 

    mconv           = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).m();
    econv           = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).e();
    thetaconv       = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).theta();
    costhetaconv    = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).cosTheta();
    phiconv         = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).phi();

    angEE           = p4Ep.vect().angle(p4Em.vect()); 

    double xiep_gamcon_1_tmp = 9999.;
    double xiep_gamcon_2_tmp = 9999.;
    double xconv_gamcon_tmp = 9999.;
    double yconv_gamcon_tmp = 9999.;
    double rconv_gamcon_tmp = 9999.;
    double xconv1_gamcon_tmp = 9999.;
    double yconv1_gamcon_tmp = 9999.;
    double rconv1_gamcon_tmp = 9999.;
    double xconv2_gamcon_tmp = 9999.;
    double yconv2_gamcon_tmp = 9999.;
    double rconv2_gamcon_tmp = 9999.;

    Rx_Gam_gamcon   = Rx_Gam;
    Ry_Gam_gamcon   = Ry_Gam;
    Rvxy_Gam_gamcon = Rvxy_Gam;

    xconv3_gamcon   = xconv;
    yconv3_gamcon   = yconv;
    rconv3_gamcon   = rconv;

    if(xiep<10.) {
        xconv_gamcon_tmp  = xconv;
        yconv_gamcon_tmp  = yconv;
        rconv_gamcon_tmp  = rconv;
        xconv1_gamcon_tmp = xconv;
        yconv1_gamcon_tmp = yconv;
        rconv1_gamcon_tmp = rconv;
        xiep_gamcon_1_tmp     = gconv.getXiep();
    } else {
        xconv_gamcon_tmp  = Rx_Gam;
        yconv_gamcon_tmp  = Ry_Gam;
        rconv_gamcon_tmp  = Rvxy_Gam;
        xconv2_gamcon_tmp = Rx_Gam;
        yconv2_gamcon_tmp = Ry_Gam;
        rconv2_gamcon_tmp = Rvxy_Gam;
        xiep_gamcon_2_tmp     = gconv.getXiep();
    }
    zconv_gamcon    = zconv;
    Dee_Mdc_gamcon  = Dee_Mdc;
    Dee_Bp_gamcon   = Dee_Bp;
    xiep_gamcon     = xiep;
    xiep_gamcon_1     = xiep_gamcon_1_tmp;
    xiep_gamcon_2     = xiep_gamcon_2_tmp;
    rconv_gamcon  = rconv_gamcon_tmp;
    xconv_gamcon  = xconv_gamcon_tmp;
    yconv_gamcon  = yconv_gamcon_tmp;
    rconv1_gamcon  = rconv1_gamcon_tmp;
    rconv2_gamcon  = rconv2_gamcon_tmp;
    deltaxy_gamcon  = deltaxy;
    deltaphi0_ee  = deltaphi0;

    mconv_gamcon    = mconv;
    econv_gamcon    = econv;
    thetaconv_gamcon= thetaconv;
    phiconv_gamcon  = phiconv;
    angEE_gamcon    = angEE;
    costhetaconv_gamcon    = costhetaconv;

    //&&&&&&&&& end of gamma conversation*************************


    HepLorentzVector ecms(0.011*m_cms,0.0,0.0,m_cms);
    // do 5C for Case1: eta'-> pi+ pi- eta, eta -> gamma gamma 
    //initialize variables 
    m_gam0ee_ppe = -1.0;
    m_ee_5c = 10.0;
    m_eta_5c = 10.0;
    m_etap_5c = 10.0;
    for (int i=0; i<4; i++) {
        m_pipieta_5c[i] = 10.0;
    }
    m_pipietap_5c = 10.0;

    m_ee_kal = 10.0;
    m_eta_kal = 10.0;
    m_etap_kal = 10.0;
    m_pipietap_kal = 10.0;
    m_gamee_eta_5c[0] = 10.0;
    m_gamee_eta_5c[1] = 10.0;

    for (int i=0; i<4; i++) {
        m_p4_eta_5c[i] = 10.0;
        m_p4_ep_5c[i] = 10.0;
        m_p4_em_5c[i] = 10.0;
        m_p4_pip1_5c[i] = 10.0;
        m_p4_pim1_5c[i] = 10.0;
        m_p4_pip2_5c[i] = 10.0;
        m_p4_pim2_5c[i] = 10.0;

        m_p4_eta_kal[i] = 10.0;
        m_p4_ep_kal[i] = 10.0;
        m_p4_em_kal[i] = 10.0;
        m_p4_pip1_kal[i] = 10.0;
        m_p4_pim1_kal[i] = 10.0;
        m_p4_pip2_kal[i] = 10.0;
        m_p4_pim2_kal[i] = 10.0;
    }

   /* int ig1 = -1;
    int ig2 = -1;
    double tmp_chi2_eta_5c = 9999.;
    HepLorentzVector ppip1_eta_5c(0., 0., 0., 0.);
    HepLorentzVector ppim1_eta_5c(0., 0., 0., 0.);
    HepLorentzVector ppip2_eta_5c(0., 0., 0., 0.);
    HepLorentzVector ppim2_eta_5c(0., 0., 0., 0.);
    HepLorentzVector pelp1_eta_5c(0., 0., 0., 0.);
    HepLorentzVector pelm1_eta_5c(0., 0., 0., 0.);
    HepLorentzVector pgam1_eta_5c(0., 0., 0., 0.);
    HepLorentzVector pgam2_eta_5c(0., 0., 0., 0.);
    HepLorentzVector peta1_eta_5c(0., 0., 0., 0.);
    if(m_test_5C==1) { //eta' -> pi+ pi- eta
        if(nGam>1){
            KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();
            for(int i = 0; i < nGam-1; i++) {
                RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[i]))->emcShower();
                for(int j = i+1; j < nGam; j++) {
                    RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+iGam[j]))->emcShower();
                    kmfit->init();
                    kmfit->setBeamPosition(vx_infit);
                    kmfit->setVBeamPosition(Evx_infit);
                    kmfit->AddTrack(0,      wpip1);
                    kmfit->AddTrack(1,      wpim1);
                    kmfit->AddTrack(2,      wpip2);
                    kmfit->AddTrack(3,      wpim2);
                    kmfit->AddTrack(4,      welp1);
                    kmfit->AddTrack(5,      welm1);
                    kmfit->AddTrack(6, 0.0, g1Trk);
                    kmfit->AddTrack(7, 0.0, g2Trk);
                    kmfit->AddResonance(0, 0.547862, 6, 7);	
                    kmfit->AddFourMomentum(1, ecms);
                    bool oksq = kmfit->Fit();
                    if(oksq) {
                        double chi2 = kmfit->chisq();
                        if(chi2 < tmp_chi2_eta_5c) {
                            tmp_chi2_eta_5c = chi2;
                            ig1 = i;
                            ig2 = j;
                        }
                    }
                }
            } 
            //m_eta_ig1 = ig1;
            //m_eta_ig2 = ig2;
            if(tmp_chi2_eta_5c < 200.){
                RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[ig1]))->emcShower();
                RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+iGam[ig2]))->emcShower();
                kmfit->init();
                kmfit->setBeamPosition(vx_infit);
                kmfit->setVBeamPosition(Evx_infit);
                kmfit->AddTrack(0,      wpip1);
                kmfit->AddTrack(1,      wpim1);
                kmfit->AddTrack(2,      wpip2);
                kmfit->AddTrack(3,      wpim2);
                kmfit->AddTrack(4,      welp1);
                kmfit->AddTrack(5,      welm1);
                kmfit->AddTrack(6, 0.0, g1Trk);
                kmfit->AddTrack(7, 0.0, g2Trk);
                kmfit->AddResonance(0, 0.547862, 6, 7);	
                kmfit->AddFourMomentum(1, ecms);
                bool oksq = kmfit->Fit();
                if(oksq) {
                    ppip1_eta_5c     = kmfit->pfit(0);
                    ppim1_eta_5c     = kmfit->pfit(1);
                    ppip2_eta_5c     = kmfit->pfit(2);
                    ppim2_eta_5c     = kmfit->pfit(3);
                    pelp1_eta_5c     = kmfit->pfit(4);
                    pelm1_eta_5c     = kmfit->pfit(5);
                    pgam1_eta_5c     = kmfit->pfit(6);
                    pgam2_eta_5c     = kmfit->pfit(7);
                    peta1_eta_5c     = kmfit->pfit(6) + kmfit->pfit(7);
                    //			Ncut[4]++;
                    double mgam0eeini_ppe = -10.0;
                    int igam0_ppe = -1;
                    int ncomb_pi0_ppe = 0;

                    m_ncomb_pi0_ppe = nGam;
                    for(int a = 0; a <nGam ; a++){
                        //if(a == ig1) continue;
                        //if(a == ig2) continue;
                        m_mgam0ee_allcomb_5c[a] = -1.0;
                    }

                    for(int j = 0; j < nGam; j++){
                        m_mgam0ee_allcomb_5c[j] = -1.0;
                        if(j == ig1) continue;
                        if(j == ig2) continue;
                        double mgam0ee_ppe = (pElep_kal + pElem_kal + pGam[j]).m();
                        m_mgam0ee_allcomb_5c[ncomb_pi0_ppe] = mgam0ee_ppe;
                        ncomb_pi0_ppe++;
                        if (abs(mgam0ee_ppe - mpi0) < abs(mgam0eeini_ppe - mpi0)){
                            mgam0eeini_ppe = mgam0ee_ppe;
                            igam0_ppe = j;
                        }
                    }
                    if(igam0_ppe != -1){
                        m_gam0ee_ppe = (pElep_kal + pElem_kal + pGam[igam0_ppe]).m();
                    }

                    // find out which two pion pair is from etap
                    Vp4 pPip_5c;
                    Vp4 pPim_5c;
                    pPip_5c.clear();
                    pPim_5c.clear();

                    pPip_5c.push_back(ppip1_eta_5c);
                    pPip_5c.push_back(ppip2_eta_5c);
                    pPim_5c.push_back(ppim1_eta_5c);
                    pPim_5c.push_back(ppim2_eta_5c);

                    double metapini = -1.0;
                    int ipip_etap = -1;
                    int ipim_etap = -1;
                    int ipipieta = 0;
                    int ncomb_5c = 0;
                    int ncomb_5c_x = 0;
                    for (int i=0; i<2; i++) {
                        for (int j=0; j<2; j++) {
                            double metap_5c = (pPip_5c[i]+pPim_5c[j]+peta1_eta_5c).m();
                            double mpipietap_5c = (pPip_5c[i]+pPim_5c[j]+pPip_5c[1-i]+pPim_5c[1-j]+ peta1_eta_5c).m();
                            if (abs(metap_5c - metap) < abs(metapini - metap)) {
                                metapini = metap_5c;
                                ipip_etap = i;
                                ipim_etap = j;
                            }
                            m_pipieta_5c[ipipieta] = metap_5c;
                            ipipieta++;
                            m_etap_allcomb_5c[ncomb_5c] = metap_5c;
                            ncomb_5c++;
                            m_pipietap_allcomb_5c[ncomb_5c_x] = mpipietap_5c;
                            ncomb_5c_x++;
                        }
                    }
                    m_ncomb_5c = ncomb_5c;
                    m_ncomb_5c_x = ncomb_5c_x;
                    // invariant mass after 5C fit
                    m_ee_5c = (pelp1_eta_5c + pelm1_eta_5c).m();
                    m_eta_5c = peta1_eta_5c.m();
                    m_ee_kal = (pElep_kal + pElem_kal).m();
                    m_eta_kal = (pGam[ig1] + pGam[ig2]).m();
                    if (ipip_etap > -1 && ipim_etap > -1) {
                        m_etap_5c = (pPip_5c[ipip_etap]+pPim_5c[ipim_etap] + peta1_eta_5c).m();
                        m_pipietap_5c = (ppip1_eta_5c + ppim1_eta_5c + ppip2_eta_5c + ppim2_eta_5c + peta1_eta_5c).m();

                        m_gamee_eta_5c[0] = (pElep_kal + pElem_kal + pgam1_eta_5c).m();
                        m_gamee_eta_5c[1] = (pElep_kal + pElem_kal + pgam2_eta_5c).m();

                        // four momentum of all particles;
                        m_p4_eta_5c[0] = peta1_eta_5c.x();
                        m_p4_eta_5c[1] = peta1_eta_5c.y();
                        m_p4_eta_5c[2] = peta1_eta_5c.z();
                        m_p4_eta_5c[3] = peta1_eta_5c.e();

                        m_p4_ep_5c[0] = pelp1_eta_5c.x();
                        m_p4_ep_5c[1] = pelp1_eta_5c.y();
                        m_p4_ep_5c[2] = pelp1_eta_5c.z();
                        m_p4_ep_5c[3] = pelp1_eta_5c.e();

                        m_p4_em_5c[0] = pelm1_eta_5c.x();
                        m_p4_em_5c[1] = pelm1_eta_5c.y();
                        m_p4_em_5c[2] = pelm1_eta_5c.z();
                        m_p4_em_5c[3] = pelm1_eta_5c.e();

                        m_p4_pip1_5c[0] = pPip_5c[1-ipip_etap].x();
                        m_p4_pip1_5c[1] = pPip_5c[1-ipip_etap].y();
                        m_p4_pip1_5c[2] = pPip_5c[1-ipip_etap].z();
                        m_p4_pip1_5c[3] = pPip_5c[1-ipip_etap].e();

                        m_p4_pim1_5c[0] = pPim_5c[1-ipim_etap].x();
                        m_p4_pim1_5c[1] = pPim_5c[1-ipim_etap].y();
                        m_p4_pim1_5c[2] = pPim_5c[1-ipim_etap].z();
                        m_p4_pim1_5c[3] = pPim_5c[1-ipim_etap].e();

                        m_p4_pip2_5c[0] = pPip_5c[ipip_etap].x();
                        m_p4_pip2_5c[1] = pPip_5c[ipip_etap].y();
                        m_p4_pip2_5c[2] = pPip_5c[ipip_etap].z();
                        m_p4_pip2_5c[3] = pPip_5c[ipip_etap].e();

                        m_p4_pim2_5c[0] = pPim_5c[ipim_etap].x();
                        m_p4_pim2_5c[1] = pPim_5c[ipim_etap].y();
                        m_p4_pim2_5c[2] = pPim_5c[ipim_etap].z();
                        m_p4_pim2_5c[3] = pPim_5c[ipim_etap].e();

                        m_etap_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pGam[ig1] + pGam[ig2]).m();
                        m_pipietap_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pPip_kal[1-ipip_etap] + pPim_kal[1-ipim_etap] + pGam[ig1] + pGam[ig2]).m();

                        // four momentum of all particles;
                        m_p4_eta_kal[0] = (pGam[ig1] + pGam[ig2]).x();
                        m_p4_eta_kal[1] = (pGam[ig1] + pGam[ig2]).y();
                        m_p4_eta_kal[2] = (pGam[ig1] + pGam[ig2]).z();
                        m_p4_eta_kal[3] = (pGam[ig1] + pGam[ig2]).e();

                        m_p4_ep_kal[0] = pElep_kal.x();
                        m_p4_ep_kal[1] = pElep_kal.y();
                        m_p4_ep_kal[2] = pElep_kal.z();
                        m_p4_ep_kal[3] = pElep_kal.e();

                        m_p4_em_kal[0] = pElem_kal.x();
                        m_p4_em_kal[1] = pElem_kal.y();
                        m_p4_em_kal[2] = pElem_kal.z();
                        m_p4_em_kal[3] = pElem_kal.e();

                        m_p4_pip1_kal[0] = pPip_kal[1-ipip_etap].x();
                        m_p4_pip1_kal[1] = pPip_kal[1-ipip_etap].y();
                        m_p4_pip1_kal[2] = pPip_kal[1-ipip_etap].z();
                        m_p4_pip1_kal[3] = pPip_kal[1-ipip_etap].e();

                        m_p4_pim1_kal[0] = pPim_kal[1-ipim_etap].x();
                        m_p4_pim1_kal[1] = pPim_kal[1-ipim_etap].y();
                        m_p4_pim1_kal[2] = pPim_kal[1-ipim_etap].z();
                        m_p4_pim1_kal[3] = pPim_kal[1-ipim_etap].e();

                        m_p4_pip2_kal[0] = pPip_kal[ipip_etap].x();
                        m_p4_pip2_kal[1] = pPip_kal[ipip_etap].y();
                        m_p4_pip2_kal[2] = pPip_kal[ipip_etap].z();
                        m_p4_pip2_kal[3] = pPip_kal[ipip_etap].e();

                        m_p4_pim2_kal[0] = pPim_kal[ipim_etap].x();
                        m_p4_pim2_kal[1] = pPim_kal[ipim_etap].y();
                        m_p4_pim2_kal[2] = pPim_kal[ipim_etap].z();
                        m_p4_pim2_kal[3] = pPim_kal[ipim_etap].e();

                    } 

                    double mpi0ini = 10.0;
                    m_mgamee_eta = 0.0;
                    for (int i=0; i<nGam; i++) {
                        double mgamee_i = (pElep_kal + pElem_kal + pGam[i]).m();
                        if (abs(mgamee_i - mpi0) < abs(mpi0ini - mpi0)){
                            mpi0ini = mgamee_i;
                        }
                        m_mgameepairs_eta[i] = mgamee_i;
                        m_mgampipipairs_eta[i] = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pGam[i]).m();
                    }
                    m_mgamee_eta = mpi0ini;
                }
            }
        }
    }


    //setV4(m_p4_eta_5c, ppip1_eta_5c, 0);
    //setV4(m_p4_eta_5c, ppim1_eta_5c, 1);
    //setV4(m_p4_eta_5c, ppip2_eta_5c, 2);
    //setV4(m_p4_eta_5c, ppim2_eta_5c, 3);
    //setV4(m_p4_eta_5c, pelp1_eta_5c, 4);
    //setV4(m_p4_eta_5c, pelm1_eta_5c, 5);
    //setV4(m_p4_eta_5c, pgam1_eta_5c, 6);
    //setV4(m_p4_eta_5c, pgam2_eta_5c, 7);
    //setV4(m_p4_eta_5c, peta1_eta_5c, 8);

    m_chi2_eta_5c = tmp_chi2_eta_5c;
    m_prob_eta_5c = TMath::Prob(tmp_chi2_eta_5c,5);
*/
    // do 4C for jpsi->pipipi0 
    //initialize variables 
    m_gam0ee_rho = -1.0;
    m_ee_rho_4c = 10.0;
    m_rho_4c = 10.0;
    m_etap_rho_4c = 10.0;
    m_pipietap_rho_4c = 10.0;
    for (int i=0; i<4; i++) {
        m_pipi_rho_4c[i] = 10.0;
    }

    m_ee_rho_kal = 10.0;
    //m_rho_kal = 10.0;
    //m_etap_rho_kal = 10.0;
    //m_pipietap_rho_kal = 10.0;

    for (int i=0; i<4; i++) {
        m_p4_gam_rho_4c[i] = 10.0;
        m_p4_ep_rho_4c[i] = 10.0;
        m_p4_em_rho_4c[i] = 10.0;
        m_p4_pip1_rho_4c[i] = 10.0;
        m_p4_pim1_rho_4c[i] = 10.0;

        m_p4_gam_rho_kal[i] = 10.0;
        m_p4_ep_kal[i] = 10.0;
        m_p4_em_kal[i] = 10.0;
        m_p4_pip1_kal[i] = 10.0;
        m_p4_pim1_kal[i] = 10.0;
    }

    m_delta_angle_pgam_etap_4c = 9999.;
    m_delta_angle_ppip_etap_4c = 9999.;
    m_mctrue_Ppip = 99999.;
    m_mctrue_Ppim = 99999.;
    m_mctrue_Ppip_etap_4c = 99999.;
    m_mctrue_Ppim_etap_4c = 99999.;
    m_delta_angle_ppim_etap_4c = 9999.;
    double tmp_chi2_4c = 9999.;
    int    ig3 = -1;
    HepLorentzVector ppip1_rho_4c(0., 0., 0., 0.);
    HepLorentzVector ppim1_rho_4c(0., 0., 0., 0.);
    HepLorentzVector pelp1_rho_4c(0., 0., 0., 0.);
    HepLorentzVector pelm1_rho_4c(0., 0., 0., 0.);
    HepLorentzVector pgam1_rho_4c(0., 0., 0., 0.); 

    if(m_test_4C==1){ // eta' -> rho gamma, rho -> pi+ pi-
        KalmanKinematicFit * kmfit2 = KalmanKinematicFit::instance();
        for(int i = 0; i < nGam; i++) {
            RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[i]))->emcShower();
            kmfit2->init();
            kmfit2->setBeamPosition(vx_infit);
            kmfit2->setVBeamPosition(Evx_infit);
            kmfit2->AddTrack(0,      wpip1);
            kmfit2->AddTrack(1,      wpim1);
            kmfit2->AddTrack(2,      welp1);
            kmfit2->AddTrack(3,      welm1);
            kmfit2->AddTrack(4, 0.0, g1Trk);
            kmfit2->AddFourMomentum(0, ecms);
            bool oksq = kmfit2->Fit();
            if(oksq) {
                double chi2 = kmfit2->chisq();
                if(chi2 < tmp_chi2_4c) {
                    tmp_chi2_4c    = chi2;
                    ig3 = i;		
                }
            }
        } 
        if(tmp_chi2_4c < 200.){
            //cout<<"===after chi2<200==="<<endl;
            //cout<<"ngam               "<<m_ngam<<endl;
            //cout<<"===================="<<endl;
            RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[ig3]))->emcShower();
            kmfit2->init();
            kmfit2->setBeamPosition(vx_infit);
            kmfit2->setVBeamPosition(Evx_infit);
            kmfit2->AddTrack(0,      wpip1);
            kmfit2->AddTrack(1,      wpim1);
            kmfit2->AddTrack(2,      welp1);
            kmfit2->AddTrack(3,      welm1);
            kmfit2->AddTrack(4, 0.0, g1Trk);
            kmfit2->AddFourMomentum(0, ecms);
            bool oksq = kmfit2->Fit();
            if(oksq) {
                //cout<<"====after oksq===="<<endl;
                //cout<<"ngam               "<<m_ngam<<endl;
                //cout<<"===================="<<endl;
                ppip1_rho_4c       = kmfit2->pfit(0);
                ppim1_rho_4c       = kmfit2->pfit(1);
                pelp1_rho_4c       = kmfit2->pfit(2);
                pelm1_rho_4c       = kmfit2->pfit(3);
                pgam1_rho_4c       = kmfit2->pfit(4);	

                double mgam0eeini = -10.0;
                int igam0 = -1;
                int ncomb_pi0_rho = 0;
                int igam0_da = 0;

                m_ncomb_pi0_rho = nGam;
                for(int a = 0; a <nGam; a++){
                    //if(a == ig3) continue;
                    m_mgam0ee_allcomb_4c[a] = -1.0;
                }

                for(int j = 0; j < nGam; j++){
                    if(j == ig3) continue;
                    m_Egam0_all = pGam[j].e();
                    m_EE_all = (pElep_kal + pElem_kal).e();

                    if(m_Egam0_all < 0.1){
                        m_Egam0 = pGam[j].e();
                        igam0_da ++;
                        double mgam0ee = (pElep_kal + pElem_kal + pGam[j]).m();
                        m_mgam0ee_allcomb_4c[ncomb_pi0_rho] = mgam0ee;
                        ncomb_pi0_rho++;
                        if (abs(mgam0ee - mpi0) < abs(mgam0eeini - mpi0)){
                            mgam0eeini = mgam0ee;
                            igam0 = j;
                        }
                    }

                    if(igam0 != -1){
                        m_gam0ee_rho = (pElep_kal + pElem_kal + pGam[igam0]).m();
                    }
                }
                m_nigam0_da = igam0_da;
                Vp4 pPip_4c;
                Vp4 pPim_4c;
                pPip_4c.clear();
                pPim_4c.clear();

                pPip_4c.push_back(ppip1_rho_4c);
                pPim_4c.push_back(ppim1_rho_4c);


               // double metapini = -1.0;
               // int ipip_etap = -1;
               // int ipim_etap = -1;
               // int ipipi = 0;
               // int ncomb = 0;
               // int ncomb_x = 0;
               // for (int i=0; i<2; i++) {
               //     for (int j=0; j<2; j++) {
               //         double metap_4c = (pPip_4c[i]+pPim_4c[j]+pgam1_rho_4c).m();
               //         double mpipietap_4c = (pPip_4c[i]+pPim_4c[j]+pPip_4c[1-i]+pPim_4c[1-j]+pgam1_rho_4c).m();
               //         if (abs(metap_4c - metap) < abs(metapini - metap)) {
               //             metapini = metap_4c;
               //             ipip_etap = i;
               //             ipim_etap = j;
               //         }
               //         m_pipi_rho_4c[ipipi] = (pPip_4c[i]+pPim_4c[j]).m();
               //         ipipi++;
               //         m_etap_rho_allcomb_4c[ncomb] = metap_4c;
               //         ncomb++;
               //         m_pipietap_rho_allcomb_4c[ncomb_x] = mpipietap_4c; 
               //         ncomb_x++;
               //         ///////////////here
               //     }
               // }
               // m_ncomb = ncomb;
               // m_ncomb_x = ncomb_x;
                // invariant mass after 5C fit
                m_ee_rho_4c = (pelp1_rho_4c + pelm1_rho_4c).m();

                m_ee_rho_4c_rec = (ecms - pelp1_rho_4c - pelm1_rho_4c).m();
                m_ee_rho_rec = (ecms - pElep_kal - pElem_kal).m();

                m_gamee_rho_4c = (pElep_kal + pElem_kal + pgam1_rho_4c).m();
                m_mpi0_4c = (pelp1_rho_4c + pelm1_rho_4c + pgam1_rho_4c).m();
                m_ee_rho_kal = (pElep_kal + pElem_kal).m();

               // if (ipip_etap > -1 && ipim_etap > -1) {
                //    m_etap_rho_4c = (pPip_4c[ipip_etap]+pPim_4c[ipim_etap] + pgam1_rho_4c).m();
                //    m_pipietap_rho_4c = (ppip1_rho_4c + ppim1_rho_4c + ppip2_rho_4c + ppim2_rho_4c + pgam1_rho_4c).m();
                //    m_gampipi_ck = (pPip_4c[1-ipip_etap]+pPim_4c[1-ipim_etap] + pgam1_rho_4c).m();
                //    m_eepipi_ck = (pPip_4c[1-ipip_etap]+pPim_4c[1-ipim_etap] + pelp1_rho_4c + pelm1_rho_4c).m();
                //    m_eepipi_ck_rho = (pPip_4c[ipip_etap]+pPim_4c[ipim_etap] + pelp1_rho_4c + pelm1_rho_4c).m();

                    // four momentum of all particles;
                    HepLorentzVector pgam1_rho_4c_tmp = pgam1_rho_4c; 
                    pgam1_rho_4c_tmp = pgam1_rho_4c_tmp.boost(-0.011,0,0);// boost to cms

                    m_p4_gam_rho_4c[0] = pgam1_rho_4c.x();
                    m_p4_gam_rho_4c[1] = pgam1_rho_4c.y();
                    m_p4_gam_rho_4c[2] = pgam1_rho_4c.z();
                    m_p4_gam_rho_4c[3] = pgam1_rho_4c.e();
                    //m_p4_gam_rho_4c[3] = pgam1_rho_4c_tmp.e();
                    m_gam_etap_theta_4c = pgam1_rho_4c.vect().theta();

                    m_p4_ep_rho_4c[0] = pelp1_rho_4c.x();
                    m_p4_ep_rho_4c[1] = pelp1_rho_4c.y();
                    m_p4_ep_rho_4c[2] = pelp1_rho_4c.z();
                    m_p4_ep_rho_4c[3] = pelp1_rho_4c.e();

                    m_p4_em_rho_4c[0] = pelm1_rho_4c.x();
                    m_p4_em_rho_4c[1] = pelm1_rho_4c.y();
                    m_p4_em_rho_4c[2] = pelm1_rho_4c.z();
                    m_p4_em_rho_4c[3] = pelm1_rho_4c.e();

                    m_p4_pip1_rho_4c[0] = ppip1_rho_4c.x();
                    m_p4_pip1_rho_4c[1] = ppip1_rho_4c.y();
                    m_p4_pip1_rho_4c[2] = ppip1_rho_4c.z();
                    m_p4_pip1_rho_4c[3] = ppip1_rho_4c.e();

                    m_p4_pim1_rho_4c[0] = ppim1_rho_4c.x();
                    m_p4_pim1_rho_4c[1] = ppim1_rho_4c.y();
                    m_p4_pim1_rho_4c[2] = ppim1_rho_4c.z();
                    m_p4_pim1_rho_4c[3] = ppim1_rho_4c.e();

                    //m_p4_pip2_rho_4c[0] = pPip_4c[ipip_etap].x();
                    //m_p4_pip2_rho_4c[1] = pPip_4c[ipip_etap].y();
                    //m_p4_pip2_rho_4c[2] = pPip_4c[ipip_etap].z();
                    //m_p4_pip2_rho_4c[3] = pPip_4c[ipip_etap].e();

                    //m_p4_pim2_rho_4c[0] = pPim_4c[ipim_etap].x();
                    //m_p4_pim2_rho_4c[1] = pPim_4c[ipim_etap].y();
                    //m_p4_pim2_rho_4c[2] = pPim_4c[ipim_etap].z();
                    //m_p4_pim2_rho_4c[3] = pPim_4c[ipim_etap].e();

                    //m_etap_rho_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pGam[ig3]).m();
                    //m_pipietap_rho_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pPip_kal[1-ipip_etap] + pPim_kal[1-ipim_etap] + pGam[ig3]).m();
                    // four momentum of all particles;
                    m_p4_gam_rho_kal[0] = pGam[ig3].x();
                    m_p4_gam_rho_kal[1] = pGam[ig3].y();
                    m_p4_gam_rho_kal[2] = pGam[ig3].z();
                    m_p4_gam_rho_kal[3] = pGam[ig3].e();

                    m_p4_ep_rho_kal[0] = pElep_kal.x();
                    m_p4_ep_rho_kal[1] = pElep_kal.y();
                    m_p4_ep_rho_kal[2] = pElep_kal.z();
                    m_p4_ep_rho_kal[3] = pElep_kal.e();

                    m_p4_em_rho_kal[0] = pElem_kal.x();
                    m_p4_em_rho_kal[1] = pElem_kal.y();
                    m_p4_em_rho_kal[2] = pElem_kal.z();
                    m_p4_em_rho_kal[3] = pElem_kal.e();

                   // m_p4_pip1_rho_kal[0] = pPip_kal[1-ipip_etap].x();
                   // m_p4_pip1_rho_kal[1] = pPip_kal[1-ipip_etap].y();
                   // m_p4_pip1_rho_kal[2] = pPip_kal[1-ipip_etap].z();
                   // m_p4_pip1_rho_kal[3] = pPip_kal[1-ipip_etap].e();

                   // m_p4_pim1_rho_kal[0] = pPim_kal[1-ipim_etap].x();
                   // m_p4_pim1_rho_kal[1] = pPim_kal[1-ipim_etap].y();
                   // m_p4_pim1_rho_kal[2] = pPim_kal[1-ipim_etap].z();
                   // m_p4_pim1_rho_kal[3] = pPim_kal[1-ipim_etap].e();

                    //m_p4_pip2_rho_kal[0] = pPip_kal[ipip_etap].x();
                    //m_p4_pip2_rho_kal[1] = pPip_kal[ipip_etap].y();
                    //m_p4_pip2_rho_kal[2] = pPip_kal[ipip_etap].z();
                    //m_p4_pip2_rho_kal[3] = pPip_kal[ipip_etap].e();

                    //m_p4_pim2_rho_kal[0] = pPim_kal[ipim_etap].x();
                    //m_p4_pim2_rho_kal[1] = pPim_kal[ipim_etap].y();
                    //m_p4_pim2_rho_kal[2] = pPim_kal[ipim_etap].z();
                    //m_p4_pim2_rho_kal[3] = pPim_kal[ipim_etap].e();
                    //      ////////////////////////////////truthmatch////////////////////////////////
                    //      SmartDataPtr<Event::EventHeader> Eventheader(eventSvc(),"/Event/EventHeader");
                    //      Vp4 mctrue_ppip , mctrue_ppim , mctrue_ppip_etap_4c , mctrue_ppim_etap_4c , mctrue_pgam_etap_4c;
                    //      mctrue_ppip.clear();
                    //      mctrue_ppim.clear();
                    //      mctrue_ppip_etap_4c.clear();
                    //      mctrue_ppim_etap_4c.clear();
                    //      mctrue_pgam_etap_4c.clear();
                    //      int m_truthRun = Eventheader->runNumber();
                    //      int m_truthEvt = Eventheader->eventNumber();
                    //      if(m_truthRun<0){
                    //          SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),"/Event/MC/McParticleCol");
                    //          SmartDataPtr<Event::McParticle> mcParticle(eventSvc(), "/Event/MC/McParticle");
                    //          if (!mcParticleCol) {
                    //              std::cout << "Could not find McParticle" << std::endl;
                    //              return(StatusCode::FAILURE);
                    //          }else{
                    //              int  m_numParticle= 0;
                    //              bool jpsiDecay    = false;
                    //              bool m_strange    = false;
                    //              bool gamma_flag   = false;
                    //              int  jpsiIndex    = -1;

                    //              Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
                    //              for (; iter_mc != mcParticleCol->end(); iter_mc++) {
                    //                  if ((*iter_mc)->primaryParticle()&&(*iter_mc)->particleProperty()==11&&((*iter_mc)->mother()).particleProperty()== 11){ m_strange=true;}//11 is e+,
                    //                  if ((*iter_mc)->primaryParticle())     continue;//e+e-
                    //                  if (!(*iter_mc)->decayFromGenerator()) continue;
                    //                  if ((*iter_mc)->particleProperty()== m_cms_id){ // J/psi
                    //                      jpsiDecay = true;
                    //                      jpsiIndex = (*iter_mc)->trackIndex();
                    //                  }
                    //                  if (!jpsiDecay) continue;
                    //                  int mcidx = ((*iter_mc)->mother()).trackIndex() - jpsiIndex;
                    //                  int pdgid = (*iter_mc)->particleProperty();

                    //                  if(m_strange&&((*iter_mc)->mother()).particleProperty()!= m_cms_id ) mcidx--;
                    //                  m_pdgid[m_numParticle]         = pdgid;
                    //                  m_motheridx[m_numParticle]     = mcidx;
                    //                  m_rec_pdgid[m_numParticle]     = pdgid;
                    //                  m_rec_motheridx[m_numParticle] = mcidx;

                    //                  m_numParticle += 1;
                    //                  int mctrue_id=
                    //                      (*iter_mc)->particleProperty();
                    //                  int mctrue_mothPID=
                    //                      ((*iter_mc)->mother()).particleProperty();
                    //                  int mctrue_moth_mothPID=
                    //                      ((*iter_mc)->mother().mother()).particleProperty();
                    //                  int mctrue_moth_moth_mothPID=
                    //                      ((*iter_mc)->mother().mother().mother()).particleProperty();
                    //                  int mctrue_moth_moth_moth_mothPID=
                    //                      ((*iter_mc)->mother().mother().mother().mother()).particleProperty();
                    //  //================================================================================================
                    //  if((mctrue_id == 211)&&(mctrue_mothPID==9999999)&&(mctrue_moth_mothPID==m_cms_id)){
                    //      mctrue_ppip.push_back((*iter_mc)->initialFourMomentum());
                    //  }
                    //  //================================================================================================
                    //  if((mctrue_id == -211)&&(mctrue_mothPID==9999999)&&(mctrue_moth_mothPID==m_cms_id)){
                    //      mctrue_ppim.push_back((*iter_mc)->initialFourMomentum());
                    //  }
                    //                  //================================================================================================
                    //                  if((mctrue_id == 211)&&(mctrue_mothPID==113)&&(mctrue_moth_mothPID==331)&&(mctrue_moth_moth_mothPID==9999999)&&(mctrue_moth_moth_moth_mothPID==m_cms_id)){
                    //                      mctrue_ppip_etap_4c.push_back((*iter_mc)->initialFourMomentum());
                    //                  }
                    //                  //================================================================================================
                    //                  if((mctrue_id == -211)&&(mctrue_mothPID==113)&&(mctrue_moth_mothPID==331)&&(mctrue_moth_moth_mothPID==9999999)&&(mctrue_moth_moth_moth_mothPID==m_cms_id)){
                    //                      mctrue_ppim_etap_4c.push_back((*iter_mc)->initialFourMomentum());
                    //                  }
                    //                  //================================================================================================
                    //                  if((mctrue_id ==22)&&(mctrue_mothPID==331)&&(mctrue_moth_mothPID==9999999)&&(mctrue_moth_moth_mothPID==m_cms_id)){
                    //                      mctrue_pgam_etap_4c.push_back((*iter_mc)->initialFourMomentum());
                    //                  }
                    //                  m_idxmc     = m_numParticle;
                    //                  m_rec_idxmc = m_numParticle;
                    //              }
                    //          }
                    //      }
                    //      if(mctrue_ppip.size()==1){
                    //          m_mctrue_ppip[0]=mctrue_ppip[0].px();
                    //          m_mctrue_ppip[1]=mctrue_ppip[0].px();
                    //          m_mctrue_ppip[2]=mctrue_ppip[0].px();
                    //          m_mctrue_ppip[3]=mctrue_ppip[0].px();
                    //          m_mctrue_Ppip=mctrue_ppip[0].rho();
                    //      }
                    //      if(mctrue_ppim.size()==1){
                    //          m_mctrue_ppim[0]=mctrue_ppim[0].px();
                    //          m_mctrue_ppim[1]=mctrue_ppim[0].px();
                    //          m_mctrue_ppim[2]=mctrue_ppim[0].px();
                    //          m_mctrue_ppim[3]=mctrue_ppim[0].px();
                    //          m_mctrue_Ppim=mctrue_ppim[0].rho();
                    //      }
                    //      if(mctrue_ppip_etap_4c.size()==1){
                    //          m_mctrue_ppip_etap_4c[0]=mctrue_ppip_etap_4c[0].px();
                    //          m_mctrue_ppip_etap_4c[1]=mctrue_ppip_etap_4c[0].py();
                    //          m_mctrue_ppip_etap_4c[2]=mctrue_ppip_etap_4c[0].pz();
                    //          m_mctrue_ppip_etap_4c[3]=mctrue_ppip_etap_4c[0].e();
                    //          m_mctrue_Ppip_etap_4c=mctrue_ppip_etap_4c[0].rho();
                    //          m_delta_angle_ppip_etap_4c = (pPip_4c[ipip_etap].vect().angle(mctrue_ppip_etap_4c[0].vect()))*57.3;
                    //      }
                    //      if(mctrue_ppim_etap_4c.size()==1){
                    //          m_mctrue_ppim_etap_4c[0]=mctrue_ppim_etap_4c[0].px();
                    //          m_mctrue_ppim_etap_4c[1]=mctrue_ppim_etap_4c[0].py();
                    //          m_mctrue_ppim_etap_4c[2]=mctrue_ppim_etap_4c[0].pz();
                    //          m_mctrue_ppim_etap_4c[3]=mctrue_ppim_etap_4c[0].e();
                    //          m_mctrue_Ppim_etap_4c=mctrue_ppim_etap_4c[0].rho();
                    //          m_delta_angle_ppim_etap_4c = (pPim_4c[ipim_etap].vect().angle(mctrue_ppim_etap_4c[0].vect()))*57.3;
                    //      }
                    //      if(mctrue_pgam_etap_4c.size()==1){
                    //          m_mctrue_pgam_etap_4c[0]=mctrue_pgam_etap_4c[0].px();
                    //          m_mctrue_pgam_etap_4c[1]=mctrue_pgam_etap_4c[0].py();
                    //          m_mctrue_pgam_etap_4c[2]=mctrue_pgam_etap_4c[0].pz();
                    //          m_mctrue_pgam_etap_4c[3]=mctrue_pgam_etap_4c[0].e();
                    //          //cout<<mctrue_pgam_etap_4c.size()<<endl;
                    //          m_delta_angle_pgam_etap_4c = (pgam1_rho_4c.vect().angle(mctrue_pgam_etap_4c[0].vect()))*57.3;
                    //          m_mctrue_Pgam_etap_4c  =mctrue_pgam_etap_4c[0].rho();
                    //      }

                      //}
                    double mpi0ini = 10.0;
                    m_mgamee_rho = 0.0;
                    int ngamma  = 0;
                    int sum = 0;
                    for (int i=0; i<nGam; i++) {
                        double mgamee_i = (pElep_kal + pElem_kal + pGam[i]).m();
                        if (abs(mgamee_i - mpi0) < abs(mpi0ini - mpi0)){
                            mpi0ini = mgamee_i;
                        }
                        m_mgameepairs_rho[i] = mgamee_i;
                        //int size = sizeof(m_mgameepairs_rho);
                        // sum += size;
                        //cout<<"size          "<<sum<<endl;
                        //cout<<"ngam               "<<m_ngam<<endl;
                        //cout<<"i          "<<i<<endl;
                        //cout<<"-----------------"<<endl;
                        //        cout<<"mgamee               "<<mgamee_i<<endl;
                        // if( m_mgameepairs_rho[i] < 0.001){
                        //     cout<<"mgamee               "<<mgamee_i<<endl;
                        //     cout<<"pElep_kal            "<<pElep_kal<<endl;
                        //     cout<<"pElem_kal            "<<pElem_kal<<endl;
                        //     cout<<"pGam                 "<<pGam[i]<<endl;
                        // }
                        m_mgameepairs_allcomb_rho[ngamma] = (pElep_kal + pElem_kal + pGam[i]).m();
                        //m_mgampipipairs_rho[i] = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pGam[i]).m();
                        ngamma++;
                    }
                    m_mgamee_rho = mpi0ini;
                    m_ngamma = ngamma;
            }
        }
    }
    //m_rho_ig3 = ig3;
    //setV4(m_p4_rho_4c, ppip1_rho_4c, 0);
    //setV4(m_p4_rho_4c, ppim1_rho_4c, 1);
    //setV4(m_p4_rho_4c, ppip2_rho_4c, 2);
    //setV4(m_p4_rho_4c, ppim2_rho_4c, 3);
    //setV4(m_p4_rho_4c, pelp1_rho_4c, 4);
    //setV4(m_p4_rho_4c, pelm1_rho_4c, 5);
    //setV4(m_p4_rho_4c, pgam1_rho_4c, 6);

    m_chi2_4c = tmp_chi2_4c;
    m_prob_4c = TMath::Prob(tmp_chi2_4c,4);

    if(!(tmp_chi2_4c < 200) ) return StatusCode::SUCCESS;
    Ncut[6]++;

    ////////////////////////end of truthmatch ///////////////////////
    ////////////////////////mctruth//////////////////////////////////////////////////////
    //SmartDataPtr<Event::EventHeader> Eventheader(eventSvc(),"/Event/EventHeader");
    //Vp4 mctrue_gam_etap_4c ;
    //mctrue_gam_etap_4c.clear();
    //int m_truthRun = Eventheader->runNumber();
    //int m_truthEvt = Eventheader->eventNumber();
    //if(m_truthRun<0){
    //    SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),"/Event/MC/McParticleCol");
    //    SmartDataPtr<Event::McParticle> mcParticle(eventSvc(), "/Event/MC/McParticle");
    //    if (!mcParticleCol) {
    //        std::cout << "Could not find McParticle" << std::endl;
    //        return(StatusCode::FAILURE);
    //    }else{
    //        int  m_numParticle= 0;
    //        bool jpsiDecay    = false;
    //        bool m_strange    = false;
    //        bool gamma_flag   = false;
    //        int  jpsiIndex    = -1;

    //        Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
    //        for (; iter_mc != mcParticleCol->end(); iter_mc++) {
    //            if ((*iter_mc)->primaryParticle()&&(*iter_mc)->particleProperty()==11&&((*iter_mc)->mother()).particleProperty()== 11){ m_strange=true;}//11 is e+,
    //            if ((*iter_mc)->primaryParticle())     continue;//e+e-
    //            if (!(*iter_mc)->decayFromGenerator()) continue;
    //            if ((*iter_mc)->particleProperty()== m_cms_id){ // J/psi
    //                jpsiDecay = true;
    //                jpsiIndex = (*iter_mc)->trackIndex();
    //            }
    //            if (!jpsiDecay) continue;
    //            int mcidx = ((*iter_mc)->mother()).trackIndex() - jpsiIndex;
    //            int pdgid = (*iter_mc)->particleProperty();

    //            if(m_strange&&((*iter_mc)->mother()).particleProperty()!= m_cms_id ) mcidx--;
    //            m_pdgid[m_numParticle]         = pdgid;
    //            m_motheridx[m_numParticle]     = mcidx;
    //            m_rec_pdgid[m_numParticle]     = pdgid;
    //            m_rec_motheridx[m_numParticle] = mcidx;

    //            m_numParticle += 1;

    //            int mctrue_id=
    //                (*iter_mc)->particleProperty();
    //            int mctrue_mothPID=
    //                ((*iter_mc)->mother()).particleProperty();
    //            int mctrue_moth_mothPID=
    //                ((*iter_mc)->mother().mother()).particleProperty();
    //            int mctrue_moth_moth_mothPID=
    //                ((*iter_mc)->mother().mother().mother()).particleProperty();
    //            int mctrue_moth_moth_moth_mothPID=
    //                ((*iter_mc)->mother().mother().mother().mother()).particleProperty();
    //            //================================================================================================
    //            if((mctrue_id == 22)&&(mctrue_mothPID==331)&&(mctrue_moth_mothPID==9999999)&&(mctrue_moth_moth_mothPID==m_cms_id)){
    //                mctrue_gam_etap_4c.push_back((*iter_mc)->initialFourMomentum());
    //            }
    //            m_idxmc     = m_numParticle;
    //            m_rec_idxmc = m_numParticle;
    //        }
    //    }
    //}
    //                cout<<__LINE__<<endl;
    //if(mctrue_gam_etap_4c.size()==1){
    //    m_mctrue_pgam_etap_4c[0]=mctrue_gam_etap_4c[0].px();
    //    m_mctrue_pgam_etap_4c[1]=mctrue_gam_etap_4c[0].py();
    //    m_mctrue_pgam_etap_4c[2]=mctrue_gam_etap_4c[0].pz();
    //    m_mctrue_pgam_etap_4c[3]=mctrue_gam_etap_4c[0].e();
    //}
    //                cout<<__LINE__<<endl;
    //delta_angle = pgam1_rho_4c.vect().angle(mctrue_gam_etap_4c[0].vect());
    //                cout<<__LINE__<<endl;
    ////double delta_energy = 99999.;
    //if( delta_angle <0.0555){
    //    //cout <<m_mctrue_pgam_etap_4c[3]<<endl;
    //    //cout <<m_p4_gam_rho_4c[3]<<endl;
    //    delta_energy = abs(m_mctrue_pgam_etap_4c[3] - m_p4_gam_rho_4c[3])/(m_mctrue_pgam_etap_4c[3]);
    //    //cout <<delta_energy <<endl;

    //} 

    m_tuple2->write();

    return StatusCode::SUCCESS;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
StatusCode pipipi0Alg::finalize() {
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "in finalize()" << endmsg;
    cout<<"Ntot=             "<<Ncut[0]<<endl;
    cout<<"nGood=            "<<Ncut[1]<<endl;
    cout<<"nGam=             "<<Ncut[2]<<endl;
    cout<<"2 e, nch+=2;nch-=2"<<Ncut[3]<<endl;
    cout<<"At least 3 pion = "<<Ncut[4]<<endl;
    cout<<"vertex fit=       "<<Ncut[5]<<endl;
    cout<<"4C fit=           "<<Ncut[6]<<endl;
    return StatusCode::SUCCESS;
}

bool pipipi0Alg::mctruth(){
    SmartDataPtr<Event::EventHeader> Eventheader(eventSvc(),"/Event/EventHeader");
    double mctr_gam1_value,mctr_gam2_value;
    Vp4 mctrue_gam_pi0;
    Vp4 mctrue_ep,mctrue_em , mctrue_pip , mctrue_pim , mctrue_pip_etap_4c , mctrue_pim_etap_4c , mctrue_gam_etap_4c;
    Vp4 mctrue_pip_etap_5c , mctrue_pim_etap_5c , mctrue_gam1_eta_5c , mctrue_gam2_eta_5c;
    Vp4 mctruth_ep_4c;
    Vp4 mctruth_em_4c;
    Vp4 mctruth_pi0gam_4c;
    Vp4 mctruth_m1835;
    Vp4 mctruth_meta_phsp;
    Vp4 mctruth_mpip_phsp;
    Vp4 mctruth_mpim_phsp;
    mctrue_gam_pi0.clear();
    mctrue_ep.clear();
    mctrue_em.clear();
    mctrue_pip.clear();
    mctrue_pim.clear();
    mctrue_pip_etap_4c.clear();
    mctrue_pim_etap_4c.clear();
    mctrue_gam_etap_4c.clear();
    mctrue_pip_etap_5c.clear();
    mctrue_pim_etap_5c.clear();
    mctrue_gam1_eta_5c.clear();
    mctrue_gam2_eta_5c.clear();
    mctruth_ep_4c.clear();
    mctruth_em_4c.clear();
    mctruth_pi0gam_4c.clear();
    mctruth_meta_phsp.clear();
    mctruth_mpip_phsp.clear();
    mctruth_mpim_phsp.clear();
    mctruth_m1835.clear();
    int m_truthRun = Eventheader->runNumber();
    int m_truthEvt = Eventheader->eventNumber();
    if(m_truthRun<0){
        SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),"/Event/MC/McParticleCol");
        SmartDataPtr<Event::McParticle> mcParticle(eventSvc(), "/Event/MC/McParticle");
        if (!mcParticleCol) {
            std::cout << "Could not find McParticle" << std::endl;
            return(StatusCode::FAILURE);
        }else{
            int  m_numParticle= 0;
            bool jpsiDecay    = false;
            bool m_strange    = false;
            bool gamma_flag   = false;
            int  jpsiIndex    = -1;

            Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
            for (; iter_mc != mcParticleCol->end(); iter_mc++) {
                if ((*iter_mc)->primaryParticle()&&(*iter_mc)->particleProperty()==11&&((*iter_mc)->mother()).particleProperty()== 11){ m_strange=true;}//11 is e+,
                if ((*iter_mc)->primaryParticle())     continue;//e+e-
                if (!(*iter_mc)->decayFromGenerator()) continue;
                if ((*iter_mc)->particleProperty()== m_cms_id){ // J/psi
                    jpsiDecay = true;
                    jpsiIndex = (*iter_mc)->trackIndex();
                }
                if (!jpsiDecay) continue;
                int mcidx = ((*iter_mc)->mother()).trackIndex() - jpsiIndex;
                int pdgid = (*iter_mc)->particleProperty();

                if(m_strange&&((*iter_mc)->mother()).particleProperty()!= m_cms_id ) mcidx--;
                m_pdgid[m_numParticle]         = pdgid;
                m_motheridx[m_numParticle]     = mcidx;

                m_rec_pdgid[m_numParticle]     = pdgid;
                m_rec_motheridx[m_numParticle] = mcidx;

                m_numParticle += 1;
                int mctrue_id=
                    (*iter_mc)->particleProperty();
                int mctrue_mothPID=
                    ((*iter_mc)->mother()).particleProperty();
                int mctrue_moth_mothPID=
                    ((*iter_mc)->mother().mother()).particleProperty();
                int mctrue_moth_moth_mothPID=
                    ((*iter_mc)->mother().mother().mother()).particleProperty();
                int mctrue_moth_moth_moth_mothPID=
                    ((*iter_mc)->mother().mother().mother().mother()).particleProperty();
                //================================================================================================
                //if((mctrue_id == 22)&&(mctrue_mothPID== 111)&&(mctrue_moth_mothPID=m_cms_id)){
                //    mctrue_gam_pi0.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id == -11)&&(mctrue_mothPID==m_cms_id)){
                //    mctrue_ep.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id == 11)&&(mctrue_mothPID==m_cms_id)){
                //    mctrue_em.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id == 211)&&(mctrue_mothPID==9999999)&&(mctrue_moth_mothPID==m_cms_id)){
                //    mctrue_pip.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id == -211)&&(mctrue_mothPID==9999999)&&(mctrue_moth_mothPID==m_cms_id)){
                //    mctrue_pim.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id == 211)&&(mctrue_mothPID==113)&&(mctrue_moth_mothPID==331)&&(mctrue_moth_moth_mothPID==9999999)&&(mctrue_moth_moth_moth_mothPID==m_cms_id)){
                //    mctrue_pip_etap_4c.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id == -211)&&(mctrue_mothPID==113)&&(mctrue_moth_mothPID==331)&&(mctrue_moth_moth_mothPID==9999999)&&(mctrue_moth_moth_moth_mothPID==m_cms_id)){
                //    mctrue_pim_etap_4c.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id ==22)&&(mctrue_mothPID==331)&&(mctrue_moth_mothPID==9999999)&&(mctrue_moth_moth_mothPID==m_cms_id)){
                //    mctrue_gam_etap_4c.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id ==211)&&(mctrue_mothPID==331)&&(mctrue_moth_mothPID==9999999)&&(mctrue_moth_moth_mothPID==m_cms_id)){
                //    mctrue_pip_etap_5c.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id ==-211)&&(mctrue_mothPID==331)&&(mctrue_moth_mothPID==9999999)&&(mctrue_moth_moth_mothPID==m_cms_id)){
                //    mctrue_pim_etap_5c.push_back((*iter_mc)->initialFourMomentum());
                //}
                ////================================================================================================
                //if((mctrue_id ==22)&&(mctrue_mothPID==221)&&(mctrue_moth_mothPID==331)&&(mctrue_moth_moth_mothPID==9999999)&&(mctrue_moth_moth_moth_mothPID==m_cms_id)){
                //    mctrue_gam1_eta_5c.push_back((*iter_mc)->initialFourMomentum());
                //}
                // //================================================================================================
                // if((mctrue_id ==11)&&(mctrue_mothPID==111)&&(mctrue_moth_mothPID==m_cms_id)){
                //    mctruth_ep_4c.push_back((*iter_mc)->initialFourMomentum()); 
                // }
                // if((mctrue_id ==-11)&&(mctrue_mothPID==111)&&(mctrue_moth_mothPID==m_cms_id)){
                //    mctruth_em_4c.push_back((*iter_mc)->initialFourMomentum()); 
                // }
                // if((mctrue_id ==22)&&(mctrue_mothPID==111)&&(mctrue_moth_mothPID==m_cms_id)){
                //    mctruth_pi0gam_4c.push_back((*iter_mc)->initialFourMomentum()); 
                // }
                // 
                // if((mctrue_id ==9999999)&&(mctrue_mothPID == m_cms_id)){
                // mctruth_m1835.push_back((*iter_mc)->initialFourMomentum());
                // }
                // if((mctrue_id ==331)&&(mctrue_mothPID == m_cms_id)){
                // mctruth_meta_phsp.push_back((*iter_mc)->initialFourMomentum());
                // }
                // if((mctrue_id ==211)&&(mctrue_mothPID == m_cms_id)){
                // mctruth_mpip_phsp.push_back((*iter_mc)->initialFourMomentum());
                // }
                // if((mctrue_id ==-211)&&(mctrue_mothPID == m_cms_id)){
                // mctruth_mpim_phsp.push_back((*iter_mc)->initialFourMomentum());
                // }

                m_idxmc     = m_numParticle;
                m_rec_idxmc = m_numParticle;
            }
        }
    }
    //if((mctruth_meta_phsp.size()==1)&&(mctruth_mpip_phsp.size()==1)&&(mctruth_mpim_phsp.size()==1)){
    //m_mctruth_mpipietap_phsp = (mctruth_meta_phsp[0]+mctruth_mpip_phsp[0]+mctruth_mpim_phsp[0]).m();
    //
    //}

    //if(mctrue_gam_pi0.size()==1){
    ////cout<<__LINE__<<endl;
    //    m_mctrue_gam_pi0[0]=mctrue_gam_pi0[0].px();
    //    m_mctrue_gam_pi0[1]=mctrue_gam_pi0[0].py();
    //    m_mctrue_gam_pi0[2]=mctrue_gam_pi0[0].pz();
    //    m_mctrue_gam_pi0[3]=mctrue_gam_pi0[0].e();
    //    m_mctrue_gam_theta = mctrue_gam_pi0[0].vect().theta();
    //    //cout<<m_mctrue_gam_theta<<endl;
    //}
    //if(mctrue_ep.size()==1){
    //    m_mctrue_ep[0]=mctrue_ep[0].px();
    //    m_mctrue_ep[1]=mctrue_ep[0].py();
    //    m_mctrue_ep[2]=mctrue_ep[0].pz();
    //    m_mctrue_ep[3]=mctrue_ep[0].e();
    //}
    //if(mctrue_em.size()==1){
    //    m_mctrue_em[0]=mctrue_em[0].px();
    //    m_mctrue_em[1]=mctrue_em[0].py();
    //    m_mctrue_em[2]=mctrue_em[0].pz();
    //    m_mctrue_em[3]=mctrue_em[0].e();
    //}
    //if(mctrue_pip.size()==1){
    //    m_mctrue_pip[0]=mctrue_pip[0].px();
    //    m_mctrue_pip[1]=mctrue_pip[0].py();
    //    m_mctrue_pip[2]=mctrue_pip[0].pz();
    //    m_mctrue_pip[3]=mctrue_pip[0].e();
    //}
    //if(mctrue_pim.size()==1){
    //    m_mctrue_pim[0]=mctrue_pim[0].px();
    //    m_mctrue_pim[1]=mctrue_pim[0].py();
    //    m_mctrue_pim[2]=mctrue_pim[0].pz();
    //    m_mctrue_pim[3]=mctrue_pim[0].e();
    //}
    //if(mctrue_pip_etap_4c.size()==1){
    //    m_mctrue_pip_etap_4c[0]=mctrue_pip_etap_4c[0].px();
    //    m_mctrue_pip_etap_4c[1]=mctrue_pip_etap_4c[0].py();
    //    m_mctrue_pip_etap_4c[2]=mctrue_pip_etap_4c[0].pz();
    //    m_mctrue_pip_etap_4c[3]=mctrue_pip_etap_4c[0].e();
    //}
    //if(mctrue_pim_etap_4c.size()==1){
    //    m_mctrue_pim_etap_4c[0]=mctrue_pim_etap_4c[0].px();
    //    m_mctrue_pim_etap_4c[1]=mctrue_pim_etap_4c[0].py();
    //    m_mctrue_pim_etap_4c[2]=mctrue_pim_etap_4c[0].pz();
    //    m_mctrue_pim_etap_4c[3]=mctrue_pim_etap_4c[0].e();
    //}
    //if(mctrue_gam_etap_4c.size()==1){
    //    m_mctrue_gam_etap_4c[0]=mctrue_gam_etap_4c[0].px();
    //    m_mctrue_gam_etap_4c[1]=mctrue_gam_etap_4c[0].py();
    //    m_mctrue_gam_etap_4c[2]=mctrue_gam_etap_4c[0].pz();
    //    m_mctrue_gam_etap_4c[3]=mctrue_gam_etap_4c[0].e();
    //    m_mctrue_gam_etap_theta = mctrue_gam_etap_4c[0].vect().theta();
    //}
    //if(mctrue_pip_etap_5c.size()==1){
    //    m_mctrue_pip_etap_5c[0]=mctrue_pip_etap_5c[0].px();
    //    m_mctrue_pip_etap_5c[1]=mctrue_pip_etap_5c[0].py();
    //    m_mctrue_pip_etap_5c[2]=mctrue_pip_etap_5c[0].pz();
    //    m_mctrue_pip_etap_5c[3]=mctrue_pip_etap_5c[0].e();
    //}
    //if(mctrue_pim_etap_5c.size()==1){
    //    m_mctrue_pim_etap_5c[0]=mctrue_pim_etap_5c[0].px();
    //    m_mctrue_pim_etap_5c[1]=mctrue_pim_etap_5c[0].py();
    //    m_mctrue_pim_etap_5c[2]=mctrue_pim_etap_5c[0].pz();
    //    m_mctrue_pim_etap_5c[3]=mctrue_pim_etap_5c[0].e();
    //}
    //if(mctrue_gam1_eta_5c.size()==2){
    //    m_mctrue_gam1_eta_5c[0]=mctrue_gam1_eta_5c[0].px();
    //    m_mctrue_gam1_eta_5c[1]=mctrue_gam1_eta_5c[0].py();
    //    m_mctrue_gam1_eta_5c[2]=mctrue_gam1_eta_5c[0].pz();
    //    m_mctrue_gam1_eta_5c[3]=mctrue_gam1_eta_5c[0].e();
    //}
    //if(mctrue_gam1_eta_5c.size()==2){
    //    m_mctrue_gam1_eta_5c[0]=mctrue_gam1_eta_5c[1].px();
    //    m_mctrue_gam1_eta_5c[1]=mctrue_gam1_eta_5c[1].py();
    //    m_mctrue_gam1_eta_5c[2]=mctrue_gam1_eta_5c[1].pz();
    //    m_mctrue_gam1_eta_5c[3]=mctrue_gam1_eta_5c[1].e();
    //}

    //if(mctruth_ep_4c.size()==1){
    //m_mctruth_ep_4c[0]=mctruth_ep_4c[0].px();
    //m_mctruth_ep_4c[1]=mctruth_ep_4c[0].py();
    //m_mctruth_ep_4c[2]=mctruth_ep_4c[0].pz();
    //m_mctruth_ep_4c[3]=mctruth_ep_4c[0].e();
    ////mctr_pep = sqrt(pow(m_mctruth_ep_4c[0],2)+pow(m_mctruth_ep_4c[1],2)+pow(m_mctruth_ep_4c[2],2));
    //mctr_pep = mctruth_ep_4c[0].rho();
    //}
    //if(mctruth_em_4c.size()==1){
    //m_mctruth_em_4c[0]=mctruth_em_4c[0].px();
    //m_mctruth_em_4c[1]=mctruth_em_4c[0].py();
    //m_mctruth_em_4c[2]=mctruth_em_4c[0].pz();
    //m_mctruth_em_4c[3]=mctruth_em_4c[0].e();
    ////mctr_pep = sqrt(pow(m_mctruth_ep_4c[0],2)+pow(m_mctruth_ep_4c[1],2)+pow(m_mctruth_ep_4c[2],2));
    //mctr_pem = mctruth_em_4c[0].rho();
    //}
    //if(mctruth_pi0gam_4c.size()==2){
    //m_mctruth_pi0gam_4c[0]=mctruth_pi0gam_4c[0].px();
    //m_mctruth_pi0gam_4c[1]=mctruth_pi0gam_4c[0].py();
    //m_mctruth_pi0gam_4c[2]=mctruth_pi0gam_4c[0].pz();
    //m_mctruth_pi0gam_4c[3]=mctruth_pi0gam_4c[0].e();
    //mctr_gam1 = mctruth_pi0gam_4c[0].rho();
    // mctr_gam1_value = mctruth_pi0gam_4c[0].rho();
    //}
    //if(mctruth_pi0gam_4c.size()==2){
    //m_mctruth_pi0gam_2_4c[0]=mctruth_pi0gam_4c[1].px();
    //m_mctruth_pi0gam_2_4c[1]=mctruth_pi0gam_4c[1].py();
    //m_mctruth_pi0gam_2_4c[2]=mctruth_pi0gam_4c[1].pz();
    //m_mctruth_pi0gam_2_4c[3]=mctruth_pi0gam_4c[1].e();
    //mctr_gam2 = mctruth_pi0gam_4c[1].rho();
    // mctr_gam2_value = mctruth_pi0gam_4c[1].rho();
    //}
    //if (mctr_gam1_value>mctr_gam2_value){
    //    mctr_Pgam_max = mctr_gam1_value;
    //    mctr_Pgam_min = mctr_gam2_value;
    //}else{
    //    mctr_Pgam_max = mctr_gam2_value;
    //    mctr_Pgam_min = mctr_gam1_value;
    //}
    /////////////1835/////////
    //if(mctruth_m1835.size()==1){
    //
    //m_mctruth_m1835[0] = mctruth_m1835[0].px();
    //m_mctruth_m1835[1] = mctruth_m1835[0].px();
    //m_mctruth_m1835[2] = mctruth_m1835[0].px();
    //m_mctruth_m1835[3] = mctruth_m1835[0].px();
    //m1835_mct = mctruth_m1835[0].m();

    //}


    /////////////////////////////gamrho////////////////////////////////
    //if(mctrue_pip.size()==1&&mctrue_pim.size()==1&&mctrue_pip_etap_4c.size()==1&&mctrue_pim_etap_4c.size()==1&&mctrue_gam_etap_4c.size()==1){
    //    m_mctrue_mpipietap_4c = (mctrue_pip[0] + mctrue_pim[0] + mctrue_pip_etap_4c[0] + mctrue_pim_etap_4c[0] + mctrue_gam_etap_4c[0]).m();
    //    m_mctruth_ee_4c = (mctrue_ep[0] + mctrue_em[0]).m();
    //}  
    //if(mctrue_pip.size()==1&&mctrue_pim.size()==1){
    //    m_mctrue_mpipi_4c = (mctrue_pip[0] + mctrue_pim[0]).m();
    //}  
    //if(mctrue_pip_etap_4c.size()==1&&mctrue_pim_etap_4c.size()==1){
    //    m_mctrue_mrho_4c = (mctrue_pip_etap_4c[0] + mctrue_pim_etap_4c[0]).m();
    //}  
    //if(mctrue_pip.size()==1&&mctrue_pip_etap_4c.size()==1&&mctrue_pim_etap_4c.size()==1&&mctrue_gam_etap_4c.size()==1){
    //    m_mctrue_mpipetap_4c = (mctrue_pip[0] + mctrue_pip_etap_4c[0] + mctrue_pim_etap_4c[0] + mctrue_gam_etap_4c[0]).m();
    //}  
    //if(mctrue_pim.size()==1&&mctrue_pip_etap_4c.size()==1&&mctrue_pim_etap_4c.size()==1&&mctrue_gam_etap_4c.size()==1){
    //    m_mctrue_mpimetap_4c = (mctrue_pim[0] + mctrue_pip_etap_4c[0] + mctrue_pim_etap_4c[0] + mctrue_gam_etap_4c[0]).m();
    //}  
    //////////////////////////////pipieta////////////////////////////////
    //if(mctrue_pip.size()==1&&mctrue_pim.size()==1&&mctrue_pip_etap_5c.size()==1&&mctrue_pim_etap_5c.size()==1&&mctrue_gam1_eta_5c.size()==2){
    //    m_mctrue_mpipietap_5c = (mctrue_pip[0] + mctrue_pim[0] + mctrue_pip_etap_5c[0] + m_mctrue_pim_etap_5c[0] +  mctrue_gam1_eta_5c[0]+  mctrue_gam1_eta_5c[1]).m();
    //    m_mctruth_ee_5c = (mctrue_ep[0] + mctrue_em[0]).m();
    //}  
    //if(mctrue_pip_etap_5c.size()==1&&mctrue_pim_etap_5c.size()==1&&mctrue_gam1_eta_5c.size()==2){
    //    m_mctrue_metap_5c = (mctrue_pip_etap_5c[0] + m_mctrue_pim_etap_5c[0] +  mctrue_gam1_eta_5c[0]+  mctrue_gam1_eta_5c[1]).m();
    //}

    //if(mctrue_pip_etap_5c.size()==1&&mctrue_pim_etap_5c.size()==1){
    //    m_mctrue_mpipi_5c = ( mctrue_pip_etap_5c[0] + m_mctrue_pim_etap_5c[0]).m();
    //}  
    //if(mctrue_pip.size()==1&&mctrue_pip_etap_5c.size()==1&&mctrue_pim_etap_5c.size()==1&&mctrue_gam1_eta_5c.size()==2){
    //    m_mctrue_mpipetap_5c = (mctrue_pip[0] + mctrue_pip_etap_5c[0] + m_mctrue_pim_etap_5c[0] +  mctrue_gam1_eta_5c[0]+  mctrue_gam1_eta_5c[1]).m();
    //}  
    //if(mctrue_pim.size()==1&&mctrue_pip_etap_5c.size()==1&&mctrue_pim_etap_5c.size()==1&&mctrue_gam1_eta_5c.size()==2){
    //    m_mctrue_mpimetap_5c = (mctrue_pim[0] + mctrue_pip_etap_5c[0] + m_mctrue_pim_etap_5c[0] +  mctrue_gam1_eta_5c[0]+  mctrue_gam1_eta_5c[1]).m();
    //}  

}

double pipipi0Alg::Get_HelixRadius(HepVector helix){
    double bField = VertexFitBField::instance()->getBFieldZ(HepPoint3D(helix[0]*cos(helix[1]), helix[0]*sin(helix[1]), helix[3]));
    int charge = 1;
    const double alpha = -0.00299792458;
    double a = alpha * bField * charge;
    double pxy = charge/helix[2];
    double radius = pxy/a;
    return radius;
}

HepPoint3D pipipi0Alg::Get_HelixCenter(HepVector helix){

    double bField = VertexFitBField::instance()->getBFieldZ(HepPoint3D(helix[0]*cos(helix[1]), helix[0]*sin(helix[1]), helix[3]));
    //  int charge = helix[2] > 0 ? +1: -1;
    int charge = 1;
    const double alpha = -0.00299792458;
    double a = alpha * bField * charge;
    double pxy = charge/helix[2];
    double rad = pxy/a;
    double x = (helix[0] + rad) * cos(helix[1]);
    double y = (helix[0] + rad) * sin(helix[1]);
    double z = 0.0;
    return HepPoint3D(x, y, z);
}

HepPoint3D pipipi0Alg::intersections(HepVector helix,double r){
    double xc, yc,rc;
    xc = Get_HelixCenter(helix).x();
    yc = Get_HelixCenter(helix).y();
    rc = Get_HelixRadius(helix);
    double a,b,c;
    double d0 =helix[0];
    a = r; // radius of Mdc or Beam Pipe 
    b = d0 + rc;
    c = rc;
    double dphi = acos((a*a-b*b-c*c)/(-2.*b*c));
    double fltlen = dphi * rc;
    double phi  = acos((c*c-a*a-b*b)/(-2.*a*b));
    double x    = r*cos(phi+helix[1]);
    double y    = r*sin(phi+helix[1]);
    double z    = helix[3]+fltlen*helix[4];
    return HepPoint3D(x, y, z);
}


double pipipi0Alg::Get_Dee(HepVector helixe,HepVector helixp,double r){
    HepPoint3D Inter_e = intersections(helixe,r);
    HepPoint3D Inter_p = intersections(helixp,r);
    double Dee = sqrt(pow((Inter_e.x()-Inter_p.x()),2)+pow((Inter_e.y()-Inter_p.y()),2));
    return Dee;
}


