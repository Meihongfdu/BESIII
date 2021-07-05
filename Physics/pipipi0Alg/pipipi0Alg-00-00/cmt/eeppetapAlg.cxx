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

#include "/workfs/bes/hjli/workarea/boss6.6.4p03/Reconstruction/GammaConv/GammaConv-00-00-01/GammaConv/GammaConv.h"

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

            m_tuple2->addItem ("ngam",              m_ngam,      0, 100 );
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

            m_tuple2->addItem ("mpi0_gg",                        m_mpi0_gg );
            m_tuple2->addItem ("meta_gg",                        m_meta_gg );
            m_tuple2->addItem ("mgamee_eta",                     m_mgamee_eta );
            m_tuple2->addItem ("mgamee_rho",                     m_mgamee_rho );

            //combine any gam with e+e-
            m_tuple2->addItem ("mgameepairs_eta",  m_ngam,   m_mgameepairs_eta );
            m_tuple2->addItem ("mgameepairs_rho",  m_ngam,   m_mgameepairs_rho );

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
            m_tuple2->addItem ("deltaxy_gamcon",                 deltaxy_gamcon);

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
            m_tuple2->addItem ("mee_5c",                         m_ee_5c);
            m_tuple2->addItem ("meta_5c",                        m_eta_5c);
            m_tuple2->addItem ("metap_5c",                       m_etap_5c);
            m_tuple2->addItem ("mpipietap_5c",                   m_pipietap_5c);

            m_tuple2->addItem ("mpipieta_5c",      4,            m_pipieta_5c);

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
            m_tuple2->addItem ("chi2_rho_4c",                    m_chi2_rho_4c);
            //m_tuple2->addItem ("p4_rho_4c",    7, 4,             m_p4_rho_4c);
            //m_tuple2->addItem ("rho_ig3",                        m_rho_ig3);
            m_tuple2->addItem ("prob_rho_4c",                    m_prob_rho_4c);

            m_tuple2->addItem ("mee_rho_4c",                     m_ee_rho_4c);
            m_tuple2->addItem ("mrho_4c",                        m_rho_4c);
            m_tuple2->addItem ("metap_rho_4c",                   m_etap_rho_4c);
            m_tuple2->addItem ("mpipietap_rho_4c",               m_pipietap_rho_4c);
            m_tuple2->addItem ("mpipi_rho_4c",      4,           m_pipi_rho_4c);

            m_tuple2->addItem ("p4_gam_rho_4c",     4,           m_p4_gam_rho_4c);
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
        //m_tuple1->write(); 
    }

    // reconstruct 6 good charged tracks, and at least 1 good photons
    // 6 good charged tracks
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
    if(!(nGood == 6 && charge ==0)) return StatusCode::SUCCESS; 
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
    int ichm2 = -1;
    int ichp0 = -1;
    int ichp1 = -1;
    int ichp2 = -1;

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
                } else if (npip ==1 ){
                    //fillChargedTrkInfo(*itTrk, m_p4_wo4_pip, m_trk_info_pip, 2, 1); //suppose is pion, without 4c
                    ichp2 = nchp; 
                }
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
                }else if(npim==1){
                    //fillChargedTrkInfo(*itTrk, m_p4_wo4_pim, m_trk_info_pim, 2, 1); //suppose is pi-, without 4c
                    ichm2 = nchm; 
                }
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
    m_ich[2]    = ichp2;
    m_ich[3]    = ichm0;
    m_ich[4]    = ichm1;
    m_ich[5]    = ichm2;

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


    if(!(nnchp == 3 && nnchm == 3 && nnpip == 2 && nnpim == 2 && nnelp == 1 && nnelm == 1))
        return StatusCode::SUCCESS;
    Ncut[3]++;
    //if (npion < 3)    return StatusCode::SUCCESS;
    m_npion = npion;
    Ncut[4]++;
    //   return StatusCode::SUCCESS;
    m_id_track_wo4[0] = ipip[0]; 
    m_id_track_wo4[1] = ipim[0]; 
    m_id_track_wo4[2] = ipip[1]; 
    m_id_track_wo4[3] = ipim[1]; 
    m_id_track_wo4[4] = ielp[0]; 
    m_id_track_wo4[5] = ielm[0]; 


    // do 4C for gamma gamma p pbar
    WTrackParameter wvpip1Trk,wvpim1Trk, wvpip2Trk,wvpim2Trk,wvelp1Trk,wvelm1Trk;

    RecMdcKalTrack *pip1Trk = (*(evtRecTrkCol->begin()+iGood[ipip[0]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    wvpip1Trk = WTrackParameter(mpi, pip1Trk->getZHelix(), pip1Trk->getZError());

    RecMdcKalTrack *pip2Trk = (*(evtRecTrkCol->begin()+iGood[ipip[1]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    wvpip2Trk = WTrackParameter(mpi, pip2Trk->getZHelix(), pip2Trk->getZError());

    RecMdcKalTrack *pim1Trk = (*(evtRecTrkCol->begin()+iGood[ipim[0]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    wvpim1Trk = WTrackParameter(mpi, pim1Trk->getZHelix(), pim1Trk->getZError());

    RecMdcKalTrack *pim2Trk = (*(evtRecTrkCol->begin()+iGood[ipim[1]]))->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    wvpim2Trk = WTrackParameter(mpi, pim2Trk->getZHelix(), pim2Trk->getZError());

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

    double  mconv    = -100.;
    double  econv    = -100.;
    double  thetaconv= -100.;
    double  phiconv  = -100.;
    double  angEE    = -100.;
    double  costhetaconv= -100.;

    // do vertex fit for the 6 charged tracks
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
    vtxfit->AddTrack(2,  wvpip2Trk);
    vtxfit->AddTrack(3,  wvpim2Trk);
    vtxfit->AddTrack(4,  wvelp1Trk);
    vtxfit->AddTrack(5,  wvelm1Trk);
    vtxfit->AddVertex(0, vxparraw,0, 1, 2, 3, 4, 5);

    if(!vtxfit->Fit(0)) return StatusCode::SUCCESS;
    vtxfit->Swim(0);

    m_vxchisq = vtxfit->chisq(0);
    Ncut[5]++;  

    WTrackParameter wpip1  = vtxfit->wtrk(0);
    WTrackParameter wpim1  = vtxfit->wtrk(1);
    WTrackParameter wpip2  = vtxfit->wtrk(2);
    WTrackParameter wpim2  = vtxfit->wtrk(3);
    WTrackParameter welp1  = vtxfit->wtrk(4);
    WTrackParameter welm1  = vtxfit->wtrk(5);

    HepLorentzVector p4Ep  = welp1.p();
    HepLorentzVector p4Em  = welm1.p();

    HepPoint3D   vx_infit  = vtxfit->vx(0);
    HepSymMatrix Evx_infit = vtxfit->Evx(0);

    Rx_Gam          = vx_infit.x();
    Ry_Gam          = vx_infit.y();
    Rvxy_Gam        = sqrt(Rx_Gam*Rx_Gam + Ry_Gam*Ry_Gam);

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

    Dee_Mdc         = Get_Dee(elp1Trk->helix(),elm1Trk->helix(),5.9);
    Dee_Bp          = Get_Dee(elp1Trk->helix(),elm1Trk->helix(),3.15); 

    mconv           = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).m();
    econv           = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).e();
    thetaconv       = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).theta();
    costhetaconv    = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).cosTheta();
    phiconv         = ( (elp1Trk->p4(me)) + (elm1Trk->p4(me))).phi();

    angEE           = p4Ep.vect().angle(p4Em.vect()); 


    Rx_Gam_gamcon   = Rx_Gam;
    Ry_Gam_gamcon   = Ry_Gam;
    Rvxy_Gam_gamcon = Rvxy_Gam;

    xconv3_gamcon   = xconv;
    yconv3_gamcon   = yconv;
    rconv3_gamcon   = rconv;

    if(xiep<10.) {
        xconv_gamcon  = xconv;
        yconv_gamcon  = yconv;
        rconv_gamcon  = rconv;
        xconv1_gamcon = xconv;
        yconv1_gamcon = yconv;
        rconv1_gamcon = rconv;
    } else {
        xconv_gamcon  = Rx_Gam;
        yconv_gamcon  = Ry_Gam;
        rconv_gamcon  = Rvxy_Gam;
        xconv2_gamcon = Rx_Gam;
        yconv2_gamcon = Ry_Gam;
        rconv2_gamcon = Rvxy_Gam;
    }

    zconv_gamcon    = zconv;
    Dee_Mdc_gamcon  = Dee_Mdc;
    Dee_Bp_gamcon   = Dee_Bp;
    xiep_gamcon     = xiep;
    deltaxy_gamcon  = deltaxy;

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

    int ig1 = -1;
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
                    for (int i=0; i<2; i++) {
                        for (int j=0; j<2; j++) {
                            double metap_5c = (pPip_5c[i]+pPim_5c[j]+peta1_eta_5c).m();
                            if (abs(metap_5c - metap) < abs(metapini - metap)) {
                                metapini = metap_5c;
                                ipip_etap = i;
                                ipim_etap = j;
                            }
                            m_pipieta_5c[ipipieta] = metap_5c;
                            ipipieta++;
                        }
                    }
                    // invariant mass after 5C fit
                    m_ee_5c = (pelp1_eta_5c + pelm1_eta_5c).m();
                    m_eta_5c = peta1_eta_5c.m();
                    m_ee_kal = (pElep_kal + pElem_kal).m();
                    m_eta_kal = (pGam[ig1] + pGam[ig2]).m();
                    if (ipip_etap > -1 && ipim_etap > -1) {
                        m_etap_5c = (pPip_5c[ipip_etap]+pPim_5c[ipim_etap] + peta1_eta_5c).m();
                        m_pipietap_5c = (ppip1_eta_5c + ppim1_eta_5c + ppip2_eta_5c + ppim2_eta_5c + peta1_eta_5c).m();

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

    // do 4C for Case2: eta'-> gamma rho 
    //initialize variables 
    m_ee_rho_4c = 10.0;
    m_rho_4c = 10.0;
    m_etap_rho_4c = 10.0;
    m_pipietap_rho_4c = 10.0;
    for (int i=0; i<4; i++) {
        m_pipi_rho_4c[i] = 10.0;
    }
 
    m_ee_rho_kal = 10.0;
    m_rho_kal = 10.0;
    m_etap_rho_kal = 10.0;
    m_pipietap_rho_kal = 10.0;

    for (int i=0; i<4; i++) {
        m_p4_gam_rho_4c[i] = 10.0;
        m_p4_ep_rho_4c[i] = 10.0;
        m_p4_em_rho_4c[i] = 10.0;
        m_p4_pip1_rho_4c[i] = 10.0;
        m_p4_pim1_rho_4c[i] = 10.0;
        m_p4_pip2_rho_4c[i] = 10.0;
        m_p4_pim2_rho_4c[i] = 10.0;

        m_p4_gam_rho_kal[i] = 10.0;
        m_p4_ep_rho_kal[i] = 10.0;
        m_p4_em_rho_kal[i] = 10.0;
        m_p4_pip1_rho_kal[i] = 10.0;
        m_p4_pim1_rho_kal[i] = 10.0;
        m_p4_pip2_rho_kal[i] = 10.0;
        m_p4_pim2_rho_kal[i] = 10.0;
    }

    double tmp_chi2_rho_4c = 9999.;
    int    ig3 = -1;
    HepLorentzVector ppip1_rho_4c(0., 0., 0., 0.);
    HepLorentzVector ppim1_rho_4c(0., 0., 0., 0.);
    HepLorentzVector ppip2_rho_4c(0., 0., 0., 0.);
    HepLorentzVector ppim2_rho_4c(0., 0., 0., 0.);
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
            kmfit2->AddTrack(2,      wpip2);
            kmfit2->AddTrack(3,      wpim2);
            kmfit2->AddTrack(4,      welp1);
            kmfit2->AddTrack(5,      welm1);
            kmfit2->AddTrack(6, 0.0, g1Trk);
            kmfit2->AddFourMomentum(0, ecms);
            bool oksq = kmfit2->Fit();
            if(oksq) {
                double chi2 = kmfit2->chisq();
                if(chi2 < tmp_chi2_rho_4c) {
                    tmp_chi2_rho_4c    = chi2;
                    ig3 = i;		
                }
            }
        } 
        if(tmp_chi2_rho_4c < 200.){
            RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[ig3]))->emcShower();
            kmfit2->init();
            kmfit2->setBeamPosition(vx_infit);
            kmfit2->setVBeamPosition(Evx_infit);
            kmfit2->AddTrack(0,      wpip1);
            kmfit2->AddTrack(1,      wpim1);
            kmfit2->AddTrack(2,      wpip2);
            kmfit2->AddTrack(3,      wpim2);
            kmfit2->AddTrack(4,      welp1);
            kmfit2->AddTrack(5,      welm1);
            kmfit2->AddTrack(6, 0.0, g1Trk);
            kmfit2->AddFourMomentum(0, ecms);
            bool oksq = kmfit2->Fit();
            if(oksq) {
                ppip1_rho_4c       = kmfit2->pfit(0);
                ppim1_rho_4c       = kmfit2->pfit(1);
                ppip2_rho_4c       = kmfit2->pfit(2);
                ppim2_rho_4c       = kmfit2->pfit(3);
                pelp1_rho_4c       = kmfit2->pfit(4);
                pelm1_rho_4c       = kmfit2->pfit(5);
                pgam1_rho_4c       = kmfit2->pfit(6);	

                Vp4 pPip_4c;
                Vp4 pPim_4c;
                pPip_4c.clear();
                pPim_4c.clear();

                pPip_4c.push_back(ppip1_rho_4c);
                pPip_4c.push_back(ppip2_rho_4c);
                pPim_4c.push_back(ppim1_rho_4c);
                pPim_4c.push_back(ppim2_rho_4c);

                double metapini = -1.0;
                int ipip_etap = -1;
                int ipim_etap = -1;
                int ipipi = 0;
                for (int i=0; i<2; i++) {
                    for (int j=0; j<2; j++) {
                        double metap_4c = (pPip_4c[i]+pPim_4c[j]+pgam1_rho_4c).m();
                        if (abs(metap_4c - metap) < abs(metapini - metap)) {
                            metapini = metap_4c;
                            ipip_etap = i;
                            ipim_etap = j;
                        }
                        m_pipi_rho_4c[ipipi] = (pPip_4c[i]+pPim_4c[j]).m();
                        ipipi++;
                    }
                }
                // invariant mass after 5C fit
                m_ee_rho_4c = (pelp1_rho_4c + pelm1_rho_4c).m();
                m_rho_4c = (pPip_4c[ipip_etap]+pPim_4c[ipim_etap]).m();
                m_ee_rho_kal = (pElep_kal + pElem_kal).m();
                m_rho_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap]).m();

                if (ipip_etap > -1 && ipim_etap > -1) {
                    m_etap_rho_4c = (pPip_4c[ipip_etap]+pPim_4c[ipim_etap] + pgam1_rho_4c).m();
                    m_pipietap_rho_4c = (ppip1_rho_4c + ppim1_rho_4c + ppip2_rho_4c + ppim2_rho_4c + pgam1_rho_4c).m();

                    // four momentum of all particles;
                    m_p4_gam_rho_4c[0] = pgam1_rho_4c.x();
                    m_p4_gam_rho_4c[1] = pgam1_rho_4c.y();
                    m_p4_gam_rho_4c[2] = pgam1_rho_4c.z();
                    m_p4_gam_rho_4c[3] = pgam1_rho_4c.e();

                    m_p4_ep_rho_4c[0] = pelp1_rho_4c.x();
                    m_p4_ep_rho_4c[1] = pelp1_rho_4c.y();
                    m_p4_ep_rho_4c[2] = pelp1_rho_4c.z();
                    m_p4_ep_rho_4c[3] = pelp1_rho_4c.e();

                    m_p4_em_rho_4c[0] = pelm1_rho_4c.x();
                    m_p4_em_rho_4c[1] = pelm1_rho_4c.y();
                    m_p4_em_rho_4c[2] = pelm1_rho_4c.z();
                    m_p4_em_rho_4c[3] = pelm1_rho_4c.e();

                    m_p4_pip1_rho_4c[0] = pPip_4c[1-ipip_etap].x();
                    m_p4_pip1_rho_4c[1] = pPip_4c[1-ipip_etap].y();
                    m_p4_pip1_rho_4c[2] = pPip_4c[1-ipip_etap].z();
                    m_p4_pip1_rho_4c[3] = pPip_4c[1-ipip_etap].e();

                    m_p4_pim1_rho_4c[0] = pPim_4c[1-ipim_etap].x();
                    m_p4_pim1_rho_4c[1] = pPim_4c[1-ipim_etap].y();
                    m_p4_pim1_rho_4c[2] = pPim_4c[1-ipim_etap].z();
                    m_p4_pim1_rho_4c[3] = pPim_4c[1-ipim_etap].e();

                    m_p4_pip2_rho_4c[0] = pPip_4c[ipip_etap].x();
                    m_p4_pip2_rho_4c[1] = pPip_4c[ipip_etap].y();
                    m_p4_pip2_rho_4c[2] = pPip_4c[ipip_etap].z();
                    m_p4_pip2_rho_4c[3] = pPip_4c[ipip_etap].e();

                    m_p4_pim2_rho_4c[0] = pPim_4c[ipim_etap].x();
                    m_p4_pim2_rho_4c[1] = pPim_4c[ipim_etap].y();
                    m_p4_pim2_rho_4c[2] = pPim_4c[ipim_etap].z();
                    m_p4_pim2_rho_4c[3] = pPim_4c[ipim_etap].e();

                    m_etap_rho_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pGam[ig3]).m();
                    m_pipietap_rho_kal = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pPip_kal[1-ipip_etap] + pPim_kal[1-ipim_etap] + pGam[ig3]).m();

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

                    m_p4_pip1_rho_kal[0] = pPip_kal[1-ipip_etap].x();
                    m_p4_pip1_rho_kal[1] = pPip_kal[1-ipip_etap].y();
                    m_p4_pip1_rho_kal[2] = pPip_kal[1-ipip_etap].z();
                    m_p4_pip1_rho_kal[3] = pPip_kal[1-ipip_etap].e();

                    m_p4_pim1_rho_kal[0] = pPim_kal[1-ipim_etap].x();
                    m_p4_pim1_rho_kal[1] = pPim_kal[1-ipim_etap].y();
                    m_p4_pim1_rho_kal[2] = pPim_kal[1-ipim_etap].z();
                    m_p4_pim1_rho_kal[3] = pPim_kal[1-ipim_etap].e();

                    m_p4_pip2_rho_kal[0] = pPip_kal[ipip_etap].x();
                    m_p4_pip2_rho_kal[1] = pPip_kal[ipip_etap].y();
                    m_p4_pip2_rho_kal[2] = pPip_kal[ipip_etap].z();
                    m_p4_pip2_rho_kal[3] = pPip_kal[ipip_etap].e();

                    m_p4_pim2_rho_kal[0] = pPim_kal[ipim_etap].x();
                    m_p4_pim2_rho_kal[1] = pPim_kal[ipim_etap].y();
                    m_p4_pim2_rho_kal[2] = pPim_kal[ipim_etap].z();
                    m_p4_pim2_rho_kal[3] = pPim_kal[ipim_etap].e();

                }
                    double mpi0ini = 10.0;
                    m_mgamee_rho = 0.0;
                    for (int i=0; i<nGam; i++) {
                        double mgamee_i = (pElep_kal + pElem_kal + pGam[i]).m();
                        if (abs(mgamee_i - mpi0) < abs(mpi0ini - mpi0)){
                            mpi0ini = mgamee_i;
                        }
                        m_mgameepairs_rho[i] = mgamee_i;
                        m_mgampipipairs_rho[i] = (pPip_kal[ipip_etap] + pPim_kal[ipim_etap] + pGam[i]).m();
                    }
                    m_mgamee_rho = mpi0ini;
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

    m_chi2_rho_4c = tmp_chi2_rho_4c;
    m_prob_rho_4c = TMath::Prob(tmp_chi2_rho_4c,4);

    if(!(tmp_chi2_eta_5c < 200 || tmp_chi2_rho_4c < 200 )) return StatusCode::SUCCESS;
    Ncut[6]++;

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
                //HepLorentzVector p_mc = (*iter_mc)->initialFourMomentum();
                //if ( (pdgid== m_cms_id) ){ //J/psi
                //    setV4(m_p4_tru, p_mc, 0);
                //    m_p_tru[0]   = p_mc.rho();
                //    m_m_tru[0]   = p_mc.m();
                //    m_cos_tru[0] = p_mc.cosTheta();
                //} 
                //if((pdgid == -11 && ((*iter_mc)->mother()).particleProperty()== m_cms_id )){ //e+ from J/psi -> e+ e- x(1835)
                //    setV4(m_p4_tru, p_mc, 1); 
                //    m_p_tru[1]   = p_mc.rho();
                //    m_m_tru[1]   = p_mc.m();
                //    m_cos_tru[1] = p_mc.cosTheta();
                //}
                //if(pdgid == 11 && ((*iter_mc)->mother()).particleProperty()== m_cms_id){//e- from J/psi -> e+ e- x(1835)
                //    setV4(m_p4_tru, p_mc, 2); 
                //    m_p_tru[2]   = p_mc.rho();
                //    m_m_tru[2]   = p_mc.m();
                //    m_cos_tru[2] = p_mc.cosTheta();
                //} 
                //if(pdgid == 9999999 && ((*iter_mc)->mother()).particleProperty()== m_cms_id){//x(1835) from J/psi -> e+ e- x(1835)
                //    setV4(m_p4_tru, p_mc, 3); 
                //    m_p_tru[3]   = p_mc.rho();
                //    m_m_tru[3]   = p_mc.m();
                //    m_cos_tru[3] = p_mc.cosTheta();
                //} 
                //if(pdgid == 211 && ((*iter_mc)->mother()).particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().particleProperty()==  m_cms_id){//pi+ from x(1835) -> pi+ pi- eta'
                //    setV4(m_p4_tru, p_mc, 4); 
                //    m_p_tru[4]   = p_mc.rho();
                //    m_m_tru[4]   = p_mc.m();
                //    m_cos_tru[4] = p_mc.cosTheta();
                //}
                //// gamma 
                //if(pdgid == -211 && ((*iter_mc)->mother()).particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().particleProperty()== m_cms_id){ // pi- from x(1835) -> pi+ pi- eta'
                //    setV4(m_p4_tru, p_mc, 5); 
                //    m_p_tru[5]   = p_mc.rho();
                //    m_m_tru[5]   = p_mc.m();
                //    m_cos_tru[5] = p_mc.cosTheta();
                //}
                //if(pdgid == 331 && ((*iter_mc)->mother()).particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().particleProperty()== m_cms_id){ // eta' from x(1835) -> pi+ pi- eta'
                //    setV4(m_p4_tru, p_mc, 6); 
                //    m_p_tru[6]   = p_mc.rho();
                //    m_m_tru[6]   = p_mc.m();
                //    m_cos_tru[6] = p_mc.cosTheta();
                //}
                //if(pdgid == 211 && ((*iter_mc)->mother()).particleProperty()== 331 && ((*iter_mc)->mother()).mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().particleProperty()== m_cms_id){ // pi+ from eta' -> pi+ pi- eta 
                //    setV4(m_p4_tru, p_mc, 7); 
                //    m_p_tru[7]   = p_mc.rho();
                //    m_m_tru[7]   = p_mc.m();
                //    m_cos_tru[7] = p_mc.cosTheta();
                //}
                ////proton
                //if(pdgid == -211 && ((*iter_mc)->mother()).particleProperty()== 331 && ((*iter_mc)->mother()).mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().particleProperty()== m_cms_id){ // pi- from eta' -> pi+ pi- eta 
                //    setV4(m_p4_tru, p_mc, 8); 
                //    m_p_tru[8]   = p_mc.rho();
                //    m_m_tru[8]   = p_mc.m();
                //    m_cos_tru[8] = p_mc.cosTheta();
                //}
                //if(pdgid == 221 &&((*iter_mc)->mother()).particleProperty()== 331 && ((*iter_mc)->mother()).mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().particleProperty()== m_cms_id ){ //eta from eta' -> pi+ pi- eta
                //    setV4(m_p4_tru, p_mc, 9); 
                //    m_p_tru[9]   = p_mc.rho();
                //    m_m_tru[9]   = p_mc.m();
                //    m_cos_tru[9] = p_mc.cosTheta();
                //}
                //if(pdgid == 113 &&((*iter_mc)->mother()).particleProperty()== 331 && ((*iter_mc)->mother()).mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().particleProperty()== m_cms_id ){ //rho from eta' -> gamma rho0
                //    setV4(m_p4_tru, p_mc, 10);
                //    m_p_tru[10]   = p_mc.rho();
                //    m_m_tru[10]   = p_mc.m();
                //    m_cos_tru[10] = p_mc.cosTheta();
                //}
                //if(pdgid == 211 &&((*iter_mc)->mother()).particleProperty()== 113 && ((*iter_mc)->mother()).mother().particleProperty()== 331 && ((*iter_mc)->mother()).mother().mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().mother().particleProperty()== m_cms_id ){ //pi+ from rho0, rho0 from eta' -> gamma rho0
                //    setV4(m_p4_tru, p_mc, 11);
                //    m_p_tru[11]   = p_mc.rho(); 
                //    m_m_tru[11]   = p_mc.m(); 
                //    m_cos_tru[11] = p_mc.cosTheta();   
                //}
                //if(pdgid == -211 &&((*iter_mc)->mother()).particleProperty()== 113 && ((*iter_mc)->mother()).mother().particleProperty()== 331 && ((*iter_mc)->mother()).mother().mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().mother().particleProperty()== m_cms_id ){ //pi- from rho0, rho0 from eta' -> gamma rho0
                //    setV4(m_p4_tru, p_mc, 12);
                //    m_p_tru[12]   = p_mc.rho(); 
                //    m_m_tru[12]   = p_mc.m();
                //    m_cos_tru[12] = p_mc.cosTheta();
                //}

                //if(pdgid == 22 && ((*iter_mc)->mother()).particleProperty()== 221  && ((*iter_mc)->mother()).mother().particleProperty()== 331 && ((*iter_mc)->mother()).mother().mother().particleProperty()== 9999999 && ((*iter_mc)->mother()).mother().mother().mother().particleProperty()== m_cms_id  ){
                //    if(!gamma_flag){ 
                //        gamma_flag = true;
                //        setV4(m_p4_tru, p_mc, 13); 
                //        m_p_tru[13]   = p_mc.rho();
                //        m_m_tru[13]   = p_mc.m();
                //        m_cos_tru[13] = p_mc.cosTheta();
                //    }
                //    else{
                //        setV4(m_p4_tru, p_mc, 14); 
                //        m_p_tru[14]   = p_mc.rho();
                //        m_m_tru[14]   = p_mc.m();
                //        m_cos_tru[14] = p_mc.cosTheta();
                //    } 
                //}			
            }
            m_idxmc     = m_numParticle;
            m_rec_idxmc = m_numParticle;
        }
    }
    return true;
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


