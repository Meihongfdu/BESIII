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

#include "DsDsmcmode/DsDsmcmode.h"
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
#include "DstoetamvAlg/Dstoetamv.h"

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
const double meta=0.54784;
const double metap= 0.95778;
const double md0 =1.86483;
const double mdp =1.86965;
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
const double xmass[5]={0.000511,0.105658,0.139570,0.493677,0.938272};
double mDs  = 1.96849;
double mDst = 2.112;

int N[10]={0,0,0,0,0,0,0,0,0,0};
//////////////////////////////

/////////////////////////////////////////////////////////////////////////////

Dstoetamv::Dstoetamv(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  declareProperty("GammaAngleCut", m_gammaAngleCut=10.0);//////////share  
  declareProperty("mctag", m_mctag=0);//////////share  
  declareProperty("ReadBeamEFromDB", m_ReadBeamEFromDB = false );
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Dstoetamv::initialize(){
  MsgStream log(msgSvc(), name());


  log << MSG::INFO << "in initialize()" << endmsg;
  
  StatusCode status;

  NTuplePtr nt1(ntupleSvc(), "FILE1/tag");
    if ( nt1 ) m_tuple1 = nt1;
    else {
     m_tuple1 = ntupleSvc()->book ("FILE1/tag", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tuple1)     {
        status = m_tuple1->addItem ("event",                      event_temp1);
        status = m_tuple1->addItem ("run",                          run_temp1);
        status = m_tuple1->addItem ("mcmode1",                  mcmode1_temp1);
        status = m_tuple1->addItem ("mcmode2",                  mcmode2_temp1);
        status = m_tuple1->addItem ("mcmodea",                  mcmodea_temp1);
        status = m_tuple1->addItem ("mcmodeb",                  mcmodeb_temp1);
        status = m_tuple1->addItem ("tagcharge",              tagcharge_temp1);
        status = m_tuple1->addItem ("tagmode",                  tagmode_temp1);
        status = m_tuple1->addItem ("mctag",                      mctag_temp1);
        status = m_tuple1->addItem ("Dstmode1",                Dstmode1_temp1);
        status = m_tuple1->addItem ("Dstmode2",                Dstmode2_temp1);
        status = m_tuple1->addItem ("ecm",                          ecm_temp1);
        status = m_tuple1->addItem ("angle",                   maxangle_temp1);
        
	status = m_tuple1->addItem ("mDs_rec",                  mDs_rec_temp1);
	status = m_tuple1->addItem ("mDs",                      mDs_tag_temp1);
	status = m_tuple1->addItem ("mBC",                      mBC_tag_temp1);

	status = m_tuple1->addItem ("index",                      index_temp1,0, 10);
	status = m_tuple1->addIndexedItem ("V4_1",                index_temp1,  V4_1_temp1);
	status = m_tuple1->addIndexedItem ("V4_2",                index_temp1,  V4_2_temp1);
	status = m_tuple1->addIndexedItem ("V4_3",                index_temp1,  V4_3_temp1);
	status = m_tuple1->addIndexedItem ("V4_4",                index_temp1,  V4_4_temp1);

}
      else    {
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
        return StatusCode::FAILURE;
      }
    }


  NTuplePtr nta(ntupleSvc(), "FILE1/taga");
    if ( nta ) m_tuple0 = nta;
    else {
     m_tuple0 = ntupleSvc()->book ("FILE1/taga", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tuple0)     {
        status = m_tuple0->addItem ("event",                      event_temp0);
        status = m_tuple0->addItem ("run",                          run_temp0);
        status = m_tuple0->addItem ("mcmode1",                  mcmode1_temp0);
        status = m_tuple0->addItem ("mcmode2",                  mcmode2_temp0);
        status = m_tuple0->addItem ("mcmodea",                  mcmodea_temp0);
        status = m_tuple0->addItem ("mcmodeb",                  mcmodeb_temp0);
        status = m_tuple0->addItem ("Dstmode1",                Dstmode1_temp0);
        status = m_tuple0->addItem ("Dstmode2",                Dstmode2_temp0);
        status = m_tuple0->addItem ("ecm",                          ecm_temp0);
        status = m_tuple0->addItem ("delE",                        delE_temp0);
        status = m_tuple0->addItem ("mctag",                      mctag_temp0);
        status = m_tuple0->addItem ("tagmode",                  tagmode_temp0);
        status = m_tuple0->addItem ("tagcharge",              tagcharge_temp0);
        status = m_tuple0->addItem ("gamorpi0",                gamorpi0_temp0);
        status = m_tuple0->addItem ("angle_Dst",              angle_Dst_temp0);
	
	status = m_tuple0->addItem ("index",                      index_temp0,0, 10);
	status = m_tuple0->addIndexedItem ("V4_1",                index_temp0,  V4_1_temp0);
	status = m_tuple0->addIndexedItem ("V4_2",                index_temp0,  V4_2_temp0);
	status = m_tuple0->addIndexedItem ("V4_3",                index_temp0,  V4_3_temp0);
	status = m_tuple0->addIndexedItem ("V4_4",                index_temp0,  V4_4_temp0);
	status = m_tuple0->addIndexedItem ("V4_5",                index_temp0,  V4_5_temp0);
        
}
      else    {
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple0) << endmsg;
        return StatusCode::FAILURE;
      }
    }


/////////////////////////////////////////
  NTuplePtr nt2(ntupleSvc(), "FILE1/signal");
    if ( nt2 ) m_tuple2 = nt2;
    else {
     m_tuple2 = ntupleSvc()->book ("FILE1/signal", CLID_ColumnWiseTuple, "ks N-Tuple example");
      if ( m_tuple2)     {
        
	status = m_tuple2->addItem ("event",                      event_temp2);
        status = m_tuple2->addItem ("run",                          run_temp2);
        status = m_tuple2->addItem ("mcmode1",                  mcmode1_temp2);
        status = m_tuple2->addItem ("mcmode2",                  mcmode2_temp2);
        status = m_tuple2->addItem ("mcmodea",                  mcmodea_temp2);
        status = m_tuple2->addItem ("mcmodeb",                  mcmodeb_temp2);
        status = m_tuple2->addItem ("tagcharge",              tagcharge_temp2);
        status = m_tuple2->addItem ("tagmode",                  tagmode_temp2);
        status = m_tuple2->addItem ("mctag",                      mctag_temp2);
        status = m_tuple2->addItem ("Dstmode1",                Dstmode1_temp2);
        status = m_tuple2->addItem ("Dstmode2",                Dstmode2_temp2);
        status = m_tuple2->addItem ("ecm",                          ecm_temp2);
        
	status = m_tuple2->addItem ("mm2m",                        mm2m_temp2);
	status = m_tuple2->addItem ("mm2mft",                    mm2mft_temp2);
	status = m_tuple2->addItem ("recmode",                  recmode_temp2);
        status = m_tuple2->addItem ("angle_rec",               maxangle_temp2);
        status = m_tuple2->addItem ("angle_tag",           maxangle_tag_temp2);
        status = m_tuple2->addItem ("angle_Dst",              angle_Dst_temp2);
	
	status = m_tuple2->addItem ("mDs_tag",                  mDs_tag_temp2);
	status = m_tuple2->addItem ("mBC_tag",                  mBC_tag_temp2);
	
	status = m_tuple2->addItem ("q2_truth",                q2_truth_temp2);
	
	status = m_tuple2->addItem ("emcmu",                      muemc_temp2);
	status = m_tuple2->addItem ("depthmu",                  mudepth_temp2);
	
	status = m_tuple2->addItem ("gamorpi0",                gamorpi0_temp2);
	status = m_tuple2->addItem ("sgmode",                    sgmode_temp2);
	
	status = m_tuple2->addItem ("npi0",                   extra_pi0_temp2);
	status = m_tuple2->addItem ("nchar",                 extra_char_temp2);
	status = m_tuple2->addItem ("egammax",                  egammax_temp2);
	status = m_tuple2->addItem ("egamsum",                  egamsum_temp2);
	status = m_tuple2->addItem ("delE",                        delE_temp2);
	
	status = m_tuple2->addItem ("q2",                            q2_temp2);
	status = m_tuple2->addItem ("m12",                          m12_temp2);
	status = m_tuple2->addItem ("m13",                          m13_temp2);
	status = m_tuple2->addItem ("m14",                          m14_temp2);
	status = m_tuple2->addItem ("m23",                          m23_temp2);
	status = m_tuple2->addItem ("m24",                          m24_temp2);
	status = m_tuple2->addItem ("m34",                          m34_temp2);
	status = m_tuple2->addItem ("m123",                        m123_temp2);
	status = m_tuple2->addItem ("m124",                        m124_temp2);
	status = m_tuple2->addItem ("m134",                        m134_temp2);
	status = m_tuple2->addItem ("m234",                        m234_temp2);
	
	status = m_tuple2->addItem ("q2ft",                        q2ft_temp2);
	status = m_tuple2->addItem ("m12ft",                      m12ft_temp2);
	status = m_tuple2->addItem ("m13ft",                      m13ft_temp2);
	status = m_tuple2->addItem ("m14ft",                      m14ft_temp2);
	status = m_tuple2->addItem ("m23ft",                      m23ft_temp2);
	status = m_tuple2->addItem ("m24ft",                      m24ft_temp2);
	status = m_tuple2->addItem ("m34ft",                      m34ft_temp2);
	status = m_tuple2->addItem ("m123ft",                    m123ft_temp2);
	status = m_tuple2->addItem ("m124ft",                    m124ft_temp2);
	status = m_tuple2->addItem ("m134ft",                    m134ft_temp2);
	status = m_tuple2->addItem ("m234ft",                    m234ft_temp2);

	status = m_tuple2->addItem ("index",                      index_temp2,0, 10);
	status = m_tuple2->addIndexedItem ("V4_1",                index_temp2,  V4_1_temp2);
	status = m_tuple2->addIndexedItem ("V4_2",                index_temp2,  V4_2_temp2);
	status = m_tuple2->addIndexedItem ("V4_3",                index_temp2,  V4_3_temp2);
	status = m_tuple2->addIndexedItem ("V4_4",                index_temp2,  V4_4_temp2);
	status = m_tuple2->addIndexedItem ("V4_5",                index_temp2,  V4_5_temp2);
	status = m_tuple2->addIndexedItem ("V4_6",                index_temp2,  V4_6_temp2);
	status = m_tuple2->addIndexedItem ("V4_7",                index_temp2,  V4_7_temp2);
	status = m_tuple2->addIndexedItem ("V4_8",                index_temp2,  V4_8_temp2);
	status = m_tuple2->addIndexedItem ("V4_9",                index_temp2,  V4_9_temp2);
	status = m_tuple2->addIndexedItem ("F4_1",                index_temp2,  F4_1_temp2);
	status = m_tuple2->addIndexedItem ("F4_2",                index_temp2,  F4_2_temp2);
	status = m_tuple2->addIndexedItem ("F4_3",                index_temp2,  F4_3_temp2);
	status = m_tuple2->addIndexedItem ("F4_4",                index_temp2,  F4_4_temp2);

     }                                                               
      else    {                                                      
        log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple2) << endmsg;
        return StatusCode::FAILURE;                                  
      }
    }

////////////////////////////////////////////////
NTuplePtr nt0(ntupleSvc(), "FILE1/truth");
if ( nt0 ) mctruth_tuple1 = nt0;
else {
	mctruth_tuple1 = ntupleSvc()->book ("FILE1/truth", CLID_ColumnWiseTuple, "track N-Tuple example");
	if ( mctruth_tuple1 )    {
	      status = mctruth_tuple1->addItem ("run",            mctruth_run);
	      status = mctruth_tuple1->addItem ("event",        mctruth_event);
	      status = mctruth_tuple1->addItem ("mcmodea",    mctruth_mcmodea);
	      status = mctruth_tuple1->addItem ("mcmodeb",    mctruth_mcmodeb);
	      status = mctruth_tuple1->addItem ("mcmode1",    mctruth_mcmode1);
	      status = mctruth_tuple1->addItem ("mcmode2",    mctruth_mcmode2);
	      status = mctruth_tuple1->addItem ("mctag",        mctruth_mctag);
	      status = mctruth_tuple1->addItem ("Dstmode1",  mctruth_Dstmode1);
	      status = mctruth_tuple1->addItem ("Dstmode2",  mctruth_Dstmode2);
	      status = mctruth_tuple1->addItem ("q2",              mctruth_q2);
	      status = mctruth_tuple1->addItem ("Pmu",             mctruth_pe);// P mu
	      status = mctruth_tuple1->addItem ("Cmu",             mctruth_ce);// cos mu

	      status = mctruth_tuple1->addItem ("Peta",          mctruth_peta);
	      status = mctruth_tuple1->addItem ("Ceta",          mctruth_ceta);

	      status = mctruth_tuple1->addItem ("Ppi0",          mctruth_ppi0);
	      status = mctruth_tuple1->addItem ("Cpi0",          mctruth_cpi0);

	      status = mctruth_tuple1->addItem ("Ppip",          mctruth_ppip);
	      status = mctruth_tuple1->addItem ("Cpip",          mctruth_cpip);
	      status = mctruth_tuple1->addItem ("Ppim",          mctruth_ppim);
	      status = mctruth_tuple1->addItem ("Cpim",          mctruth_cpim);

	}
	else    {
		log << MSG::ERROR << "    Cannot book N-tuple:" << long(mctruth_tuple1) << endmsg;
		return StatusCode::FAILURE;
	}
}




  //--------end of book--------

  //

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;

}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Dstoetamv::execute() {
  MsgStream log(msgSvc(), name());

  log << MSG::INFO << "in execute()" << endreq;

  SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
  int runNo=eventHeader->runNumber();
  int event=eventHeader->eventNumber();
  log << MSG::DEBUG <<"run, evtnum = "
      << runNo << " , "
      << event <<endreq;
  Ecmset*  ECMSET = Ecmset::instance();
  int  run = abs(runNo);
  ECMSET->EcmSet(run);
  double Ebeam=2.09;

ReadBeamInfFromDb m_dbReader;
if (!m_ReadBeamEFromDB) {
	Ebeam =  ECMSET->ECM()/2.0;
}
else {
		m_dbReader.setcalib(true);
		Ebeam=m_dbReader.getbeamE(run,Ebeam);
}
if(abs(run)>=32239&&abs(run)<=32849)Ebeam=(4320.34-0.00287*abs(run))/1000./2.0;
double ecm=2*Ebeam;
HepLorentzVector ECMS(0,0,0,ecm);
/////////////
      HepLorentzVector ecms(ecm*0.011,0,0,ecm);
/////////////////
  SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
    log << MSG::DEBUG <<"ncharg, nneu, tottks = "
      << evtRecEvent->totalCharged() << " , "
      << evtRecEvent->totalNeutral() << " , "
      << evtRecEvent->totalTracks() <<endreq;

  int MC_particlenumber = 0;
  int mcmode1=0,mcmode2=0;  int mcmodea=0,mcmodeb=0;
  int Dstmode1 = 0, Dstmode2 = 0;
  double q2_truth=999;

  int MC_mode_Dp  = 0;
  int MC_mode_D0  = 0;
  int MC_mode_Dsp = 0;
  int MC_mode_Dn  = 0;
  int MC_mode_D0b = 0;
  int MC_mode_Dsn = 0;
  int MC_mode_Dst = 0;
  Event::McParticle* mcpar_dsp;
  Event::McParticle* mcpar_dsn;

  if(runNo<0) {

	  SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),"/Event/MC/McParticleCol");
	  if(!mcParticleCol) { std::cout<<"Could not retrieve McParticelCol"<<std::endl; }
	  else      {
		  Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
		  for (; iter_mc != mcParticleCol->end(); iter_mc++){
			  MC_particlenumber++;
			  if (!(*iter_mc)->decayFromGenerator()) continue;
			  int pdgid = (*iter_mc)->particleProperty();
			  if (pdgid== 421) MC_mode_D0  = 1;
			  if (pdgid== 411) MC_mode_Dp  = 1;
			  if (pdgid== 431) {MC_mode_Dsp = 1; mcpar_dsp = (*iter_mc);}
			  if (pdgid==-421) MC_mode_D0b = 1;
			  if (pdgid==-411) MC_mode_Dn  = 1;
			  if (pdgid==-431) {MC_mode_Dsn = 1; mcpar_dsn = (*iter_mc);}
			  if (abs(pdgid)==433 || abs(pdgid)==423 || abs(pdgid)==413) MC_mode_Dst = 1;

		  }
	  }

	  if(MC_mode_Dst == 1){
		  Vint mdDst1; mdDst1.clear();
		  Vint mdDst2; mdDst2.clear();
		  DsDsmcmode* readmodeDst1 = DsDsmcmode::instance();
		  readmodeDst1->Dst1mcmode(mcParticleCol);
		  mdDst1    = readmodeDst1->mcmode();
		  DsDsmcmode* readmodeDst2 = DsDsmcmode::instance();
		  readmodeDst2->Dst2mcmode(mcParticleCol);
		  mdDst2    = readmodeDst2->mcmode();

		  if(mdDst1.size()==1){
			  Dstmode1 = mdDst1[0];
		  }
		  if(mdDst2.size()==1){
			  Dstmode2 = mdDst2[0];
		  }
	  }

	  Vint mdtg11,mdtg12,mdtg21,mdtg22,mdtg31,mdtg32;
	  mdtg11.clear(); mdtg12.clear(); mdtg21.clear(); mdtg22.clear(); mdtg31.clear(); mdtg32.clear();

	  if(MC_mode_D0 == 1){
		  DsDsmcmode* readmode11 = DsDsmcmode::instance();
		  readmode11->D0mcmode(mcParticleCol);
		  mdtg11    = readmode11->mcmode();
		  if(mdtg11.size()>=1) mcmode1=mdtg11[0];

		  DsDsmcmode* readmode1a = DsDsmcmode::instance();
		  readmode1a->D0mcmodeF(mcParticleCol);
		  mcmodea   = readmode1a->mcmodef();
	  }

	  if(MC_mode_D0b == 1){
		  DsDsmcmode* readmode12 = DsDsmcmode::instance();
		  readmode12->D0bmcmode(mcParticleCol);
		  mdtg12    = readmode12->mcmode();
		  if(mdtg12.size()>=1) mcmode2=mdtg12[0];

		  DsDsmcmode* readmode1b = DsDsmcmode::instance();
		  readmode1b->D0bmcmodeF(mcParticleCol);
		  mcmodeb   = readmode1b->mcmodef();
	  }

	  if(MC_mode_Dp == 1){
		  DsDsmcmode* readmode21 = DsDsmcmode::instance();
		  readmode21->Dpmcmode(mcParticleCol);
		  mdtg21    = readmode21->mcmode();
		  if(mdtg21.size()>=1) mcmode1=mdtg21[0];

		  DsDsmcmode* readmode2a = DsDsmcmode::instance();
		  readmode2a->DpmcmodeF(mcParticleCol);
		  mcmodea   = readmode2a->mcmodef();
	  }

	  if(MC_mode_Dn == 1){
		  DsDsmcmode* readmode22 = DsDsmcmode::instance();
		  readmode22->Dnmcmode(mcParticleCol);
		  mdtg22    = readmode22->mcmode();
		  if(mdtg22.size()>=1) mcmode2=mdtg22[0];

		  DsDsmcmode* readmode2b = DsDsmcmode::instance();
		  readmode2b->DnmcmodeF(mcParticleCol);
		  mcmodeb   = readmode2b->mcmodef();
	  }

	  if(MC_mode_Dsp == 1){
		  DsDsmcmode* readmode31 = DsDsmcmode::instance();
		  readmode31->Dspmcmode(mcParticleCol);
		  mdtg31    = readmode31->mcmode();
		  if(mdtg31.size()>=1) mcmode1=mdtg31[0];

		  DsDsmcmode* readmode3a = DsDsmcmode::instance();
		  readmode3a->DspmcmodeF(mcParticleCol);
		  mcmodea   = readmode3a->mcmodef();
	  }

	  if(MC_mode_Dsn == 1){
		  DsDsmcmode* readmode32 = DsDsmcmode::instance();
		  readmode32->Dsnmcmode(mcParticleCol);
		  mdtg32    = readmode32->mcmode();
		  if(mdtg32.size()>=1) mcmode2=mdtg32[0];

		  DsDsmcmode* readmode3b = DsDsmcmode::instance();
		  readmode3b->DsnmcmodeF(mcParticleCol);
		  mcmodeb   = readmode3b->mcmodef();
	  }
	  mctruth_run      = runNo   ;
	  mctruth_event    = event   ;
	  mctruth_mcmode1  = mcmode1 ;
	  mctruth_mcmode2  = mcmode2 ;
	  mctruth_mcmodea  = mcmodea ;
	  mctruth_mcmodeb  = mcmodeb ;
	  mctruth_Dstmode1 = Dstmode1;
	  mctruth_Dstmode2 = Dstmode2;
          mctruth_mctag    = m_mctag ;
  }

Vp4 Ta4_1;Ta4_1.clear();//e
Vp4 Ta4_2;Ta4_2.clear();//nu_e
Vp4 Ta4_3;Ta4_3.clear();//mu
Vp4 Ta4_4;Ta4_4.clear();//nu_mu
Vp4 Ta4_5a;Ta4_5a.clear();//K+
Vp4 Ta4_6a;Ta4_6a.clear();//pi+
Vp4 Ta4_5b;Ta4_5b.clear();//K+
Vp4 Ta4_6b;Ta4_6b.clear();//pi+
Vp4 Ta4_7;Ta4_7.clear();//p
Vp4 Ta4_8;Ta4_8.clear();//pi0
Vp4 Ta4_9;Ta4_9.clear();//eta
Vp4 Ta4_10;Ta4_10.clear();//gam

Vp4 Tb4_1;Tb4_1.clear();//e
Vp4 Tb4_2;Tb4_2.clear();//nu_e
Vp4 Tb4_3;Tb4_3.clear();//mu
Vp4 Tb4_4;Tb4_4.clear();//nu_mu
Vp4 Tb4_5a;Tb4_5a.clear();//K+
Vp4 Tb4_6a;Tb4_6a.clear();//pi+
Vp4 Tb4_5b;Tb4_5b.clear();//K-
Vp4 Tb4_6b;Tb4_6b.clear();//pi-
Vp4 Tb4_7;Tb4_7.clear();//p
Vp4 Tb4_8;Tb4_8.clear();//pi0
Vp4 Tb4_9;Tb4_9.clear();//eta
Vp4 Tb4_10;Tb4_10.clear();//gamma

Vp4 T_Dst;T_Dst.clear();//gamma or pi0 from Ds*

if(runNo<0) {
SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
if(!mcParticleCol)            return StatusCode::FAILURE;

if(mcParticleCol){
Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();

for(; iter_mc != mcParticleCol->end(); iter_mc++){
if ((*iter_mc)->primaryParticle())                                   continue;
if (!(*iter_mc)->decayFromGenerator())                               continue;

      int pdgid = (*iter_mc)->particleProperty();
      int p_mid= ((*iter_mc)->mother()).particleProperty();
      int p_m2id=(((*iter_mc)->mother()).mother()).particleProperty();
      int p_m3id=((((*iter_mc)->mother()).mother()).mother()).particleProperty();
      int p_m4id=(((((*iter_mc)->mother()).mother()).mother()).mother()).particleProperty();
      int p_m5id=((((((*iter_mc)->mother()).mother()).mother()).mother()).mother()).particleProperty();

if((pdgid==22||pdgid==111)&&(p_mid==433||p_mid==-433)){
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
T_Dst.push_back(P4_1);
}


if(p_mid==431||p_m2id==431||p_m3id==431||p_m4id==431||p_m5id==431){

if(abs(pdgid)==11){// e
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_1.push_back(P4_1);
mctruth_pe=P4_1.rho();
mctruth_ce=P4_1.cosTheta();
}
if(abs(pdgid)==12){// nu_e
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_2.push_back(P4_1);
}
if(abs(pdgid)==13){// mu
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_3.push_back(P4_1);
mctruth_pe=P4_1.rho();
mctruth_ce=P4_1.cosTheta();
}
if(abs(pdgid)==14){// nu_mu
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_4.push_back(P4_1);
}

if(pdgid==321){// K+
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_5a.push_back(P4_1);
}
if(pdgid==211){// pi+
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_6a.push_back(P4_1);
}
if(pdgid==-321){// K-
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_5b.push_back(P4_1);
}
if(pdgid==-211){// pi-
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_6b.push_back(P4_1);
}

if(pdgid==111){// pi0
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_8.push_back(P4_1);
}
if(pdgid==221){// eta
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_9.push_back(P4_1);
}

if(pdgid==22){// gamma
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Ta4_10.push_back(P4_1);
}

}
if(p_mid==-431||p_m2id==-431||p_m3id==-431||p_m4id==-431||p_m5id==-431){

if(abs(pdgid)==11){// e
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_1.push_back(P4_1);
mctruth_pe=P4_1.rho();
mctruth_ce=P4_1.cosTheta();
}
if(abs(pdgid)==12){// nu_e
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_2.push_back(P4_1);
}
if(abs(pdgid)==13){// mu
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_3.push_back(P4_1);
mctruth_pe=P4_1.rho();
mctruth_ce=P4_1.cosTheta();
}
if(abs(pdgid)==14){// nu_mu
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_4.push_back(P4_1);
}

if(pdgid==321){// K +
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_5a.push_back(P4_1);
}
if(pdgid==211){// pi+
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_6a.push_back(P4_1);
}
if(pdgid==-321){// K-
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_5b.push_back(P4_1);
}
if(pdgid==-211){// pi-
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_6b.push_back(P4_1);
}

if(pdgid==111){// pi0
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_8.push_back(P4_1);
}

if(pdgid==221){// eta
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_9.push_back(P4_1);
}

if(pdgid==22){// gam
HepLorentzVector  P4_1=(*iter_mc)->initialFourMomentum();
P4_1.boost(-0.011,0,0);
Tb4_10.push_back(P4_1);
}

}
}
}

if(Ta4_1.size()==1&&Ta4_2.size()==1){ // q2 -> e nu from Ds+
mctruth_q2=(Ta4_1[0]+Ta4_2[0]).m2();
q2_truth=(Ta4_1[0]+Ta4_2[0]).m2();
}
if(Tb4_1.size()==1&&Tb4_2.size()==1){//q2 -> e nu from Ds-
mctruth_q2=(Tb4_1[0]+Tb4_2[0]).m2();
q2_truth=(Tb4_1[0]+Tb4_2[0]).m2();
}
if(Ta4_3.size()==1&&Ta4_4.size()==1){  // q2 -> mu nu from Ds+
mctruth_q2=(Ta4_3[0]+Ta4_4[0]).m2();
q2_truth=(Ta4_3[0]+Ta4_4[0]).m2();
}
if(Tb4_3.size()==1&&Tb4_4.size()==1){ // q2 -> mu nu from Ds-
mctruth_q2=(Tb4_3[0]+Tb4_4[0]).m2();
q2_truth=(Tb4_3[0]+Tb4_4[0]).m2();
}

if(mcmodea==3088||mcmodea==3089||mcmodea==3090){

if(Ta4_6a.size()==1){//pi+
mctruth_ppip=sqrt(Ta4_6a[0].px()*Ta4_6a[0].px()+Ta4_6a[0].py()*Ta4_6a[0].py());
//mctruth_ppip=Ta4_6a[0].rho();
mctruth_cpip=Ta4_6a[0].cosTheta();
}
if(Ta4_6b.size()==1){//pi-
mctruth_ppim=sqrt(Ta4_6b[0].px()*Ta4_6b[0].px()+Ta4_6b[0].py()*Ta4_6b[0].py());
//mctruth_ppim=Ta4_6b[0].rho();
mctruth_cpim=Ta4_6b[0].cosTheta();
}


if(Ta4_8.size()==1){
mctruth_ppi0=Ta4_8[0].rho();
mctruth_cpi0=Ta4_8[0].cosTheta();
}
if(Ta4_9.size()==1){
mctruth_peta=Ta4_9[0].rho();
mctruth_ceta=Ta4_9[0].cosTheta();
}

}
if(mcmodeb==-3088||mcmodeb==-3089||mcmodeb==-3090){

if(Tb4_6a.size()==1){//pi+
mctruth_ppip=sqrt(Tb4_6a[0].px()*Tb4_6a[0].px()+Tb4_6a[0].py()*Tb4_6a[0].py());
//mctruth_ppip=Tb4_6a[0].rho();
mctruth_cpip=Tb4_6a[0].cosTheta();
}
if(Tb4_6b.size()==1){//pi-
mctruth_ppim=sqrt(Tb4_6b[0].px()*Tb4_6b[0].px()+Tb4_6b[0].py()*Tb4_6b[0].py());
//mctruth_ppim=Tb4_6b[0].rho();
mctruth_cpim=Tb4_6b[0].cosTheta();
}


if(Tb4_8.size()==1){
mctruth_ppi0=Tb4_8[0].rho();
mctruth_cpi0=Tb4_8[0].cosTheta();
}
if(Tb4_9.size()==1){
mctruth_peta=Tb4_9[0].rho();
mctruth_ceta=Tb4_9[0].cosTheta();
}

}



   mctruth_tuple1->write();

}


Match TruthMatch;
/////////////////////// K+      K-     pi+    pi-   gamma pi0   eta   e     mu
TruthMatch.InputTruDsp(Ta4_5a,Ta4_5b,Ta4_6a,Ta4_6b,Ta4_10,Ta4_8,Ta4_9,Ta4_1,Ta4_3);
TruthMatch.InputTruDsm(Tb4_5a,Tb4_5b,Tb4_6a,Tb4_6b,Tb4_10,Tb4_8,Tb4_9,Tb4_1,Tb4_3);

Vdou    Ksolen;                Ksolen.clear();      
Vdou    Pi0chi;                Pi0chi.clear();      
Vdou    etachi;                etachi.clear();   
Vdou    kschi;                 kschi.clear();   

Vdou    Emcmu;                 Emcmu.clear();
Vdou    Emck;                  Emck.clear();
Vdou    Emcpi;                 Emcpi.clear();
Vdou    Emce;                  Emce.clear();

Vdou    Depthmu;               Depthmu.clear();
Vdou    Depthk;                Depthk.clear();
Vdou    Depthpi;               Depthpi.clear();
Vdou    Depthe;                Depthe.clear();


Vint    Kcharge;               Kcharge.clear();        
Vint    Kid;                   Kid.clear();          
Vint    Picharge;              Picharge.clear();      
Vint    Piid;                  Piid.clear(); 
Vint    Gamid;                 Gamid.clear();
Vint    Pi0id1;                Pi0id1.clear();
Vint    Pi0id2;                Pi0id2.clear(); 
Vint    Etaid1;                Etaid1.clear();
Vint    Etaid2;                Etaid2.clear();
Vint    Ksoid1;                Ksoid1.clear();  
Vint    Ksoid2;                Ksoid2.clear();
Vint    Muid;                  Muid.clear();
Vint    Mucharge;              Mucharge.clear();
Vint    Eid;                   Eid.clear();
Vint    Echarge;               Echarge.clear();

Vp4    Kvector;                Kvector.clear();
Vp4    Pivector;               Pivector.clear();
Vp4    Gamvector;              Gamvector.clear();
Vp4    Pi0vector;              Pi0vector.clear();
Vp4    Etavector;              Etavector.clear();
Vp4    Eta2gammavector;        Eta2gammavector.clear();
Vp4    Pi02gammavector;        Pi02gammavector.clear();
Vp4    Ksovector;              Ksovector.clear();
Vp4    Muvector;               Muvector.clear();
Vp4    Evector;                Evector.clear();
Vp4    Ksovector_pip;          Ksovector_pip.clear();
Vp4    Ksovector_pim;          Ksovector_pim.clear();
Vp4    Pi0vector_gam1;         Pi0vector_gam1.clear();
Vp4    Pi0vector_gam2;         Pi0vector_gam2.clear();
Vp4    Etavector_gam1;         Etavector_gam1.clear();
Vp4    Etavector_gam2;         Etavector_gam2.clear();

Vtrack  Trk_k;                 Trk_k.clear();
Vtrack  Trk_pi;                Trk_pi.clear();
Vtrack  Trk_ks;                Trk_ks.clear();
Vtrack  Trk_pi0;               Trk_pi0.clear();
Vtrack  Trk_eta;               Trk_eta.clear();
Vtrack  Trk_mu;                Trk_mu.clear();
Vtrack  Trk_e;                 Trk_e.clear();

  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
  ParticleID *pid = ParticleID::instance();

  Hep3Vector xorigin(0,0,0);
  HepSymMatrix xoriginEx(3,0);
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
  if(vtxsvc->isVertexValid())
  {
    double* dbv = vtxsvc->PrimaryVertex();
    double*  vv = vtxsvc->SigmaPrimaryVertex();
    xorigin.setX(dbv[0]);
    xorigin.setY(dbv[1]);
    xorigin.setZ(dbv[2]);
    xoriginEx[0][0] = vv[0] * vv[0];
    xoriginEx[1][1] = vv[1] * vv[1];
    xoriginEx[2][2] = vv[2] * vv[2];
  }


 HepPoint3D point0(0.,0.,0.);
  HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);

  Vdouble Vrm, Vzm; Vrm.clear(); Vzm.clear();
  Vint iGood; iGood.clear(); int nCharge = 0;
  for(int i = 0; i <  evtRecEvent->totalCharged(); i++){
	  EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;

	  if(!(*itTrk)->isMdcTrackValid()) continue;
	  RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
	  double theta = mdcTrk->theta();
	  double x0=mdcTrk->x();
	  double y0=mdcTrk->y();
	  double z0=mdcTrk->z();
	  double phi0 = mdcTrk->helix(1);

	  double xv=xorigin.x();
	  double yv=xorigin.y();
	  double zv=xorigin.z();

	  double Rxy=(x0-xv)*cos(phi0)+(y0-yv)*sin(phi0);
	  double zm = z0-zv;
	  if(fabs(Rxy) >= 1.0) continue;
	  if(fabs(zm) >= 10.0) continue;
	  if(fabs(cos(theta)) > 0.930) continue;
	  iGood.push_back(i);
	  Vrm.push_back(Rxy); Vzm.push_back(zm);
	  nCharge += mdcTrk->charge();
  }

int nGood = iGood.size();
///////////////////////////////////select all k
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
    pid->usePidSys(pid->useDedx() | pid->useTofCorr());
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

double emck=0,dptk=0;
	if((*itTrk)->isEmcShowerValid()) {
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		emck = emcTrk->energy();
	}
	if ((*itTrk)->isMucTrackValid()){
		RecMucTrack* mucTrk = (*itTrk)->mucTrack();
		dptk = mucTrk->depth();
	}

    Emck.push_back(emck);
    Depthk.push_back(dptk);


 
    Trk_k.push_back(kam);
    Kcharge.push_back(mdcKalTrk->charge());
    Kid.push_back(i);
    Kvector.push_back(P_KAM);
}
int knumber=Kvector.size();
//cout<<"Knumber    "<<knumber<<endl;
//////////////////////////////add
////////////////////////////////select all pi
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
      if (  dr1 >= 1.0) continue;
      if (drz >= 10.0) continue;
      if ( fabs(costheta) >= 0.93) continue;

      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTofCorr() ); // use PID sub-system
      pid->identify(pid->onlyPion() | pid->onlyKaon());    // seperater Pion/Kaon
      pid->calculate();

     if(pid->probPion()<= pid->probKaon()) continue;
      if(pid->probPion() <= 0) continue;
        WTrackParameter pi(xmass[2],mdcKalTrk->getZHelix(),mdcKalTrk->getZError());
        HepVector pip_val = HepVector(7,0);
        pip_val = pi.w();
        HepLorentzVector P_PI(pip_val[0],pip_val[1],pip_val[2],pip_val[3]);
        P_PI.boost(-0.011,0,0);


double emcpi=0,dptpi=0;
	if((*itTrk)->isEmcShowerValid()) {
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		emcpi = emcTrk->energy();
	}
	if ((*itTrk)->isMucTrackValid()){
		RecMucTrack* mucTrk = (*itTrk)->mucTrack();
		dptpi = mucTrk->depth();
	}

    Emcpi.push_back(emcpi);
    Depthpi.push_back(dptpi);



Trk_pi.push_back(pi);
    Picharge.push_back(mdcKalTrk->charge());
    Piid.push_back(j);
    Pivector.push_back(P_PI);
}
int pinumber=Pivector.size();
////////////////////////////////////////////////////////

     for(int i = 0; i < evtRecEvent->totalCharged();i++) {
      EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
      RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
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
      RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
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
     HepVector pip_val = HepVector(7,0);
     HepVector pim_val = HepVector(7,0); 
     pip_val = pip.w();
     pim_val = pim.w();
     HepLorentzVector ptrktagk0(pip_val[0]+pim_val[0],pip_val[1]+pim_val[1],pip_val[2]+pim_val[2],pip_val[3]+pim_val[3]);
     double m_xmtagk0_tem = ptrktagk0.m();
      if(fabs(ptrktagk0.m()-0.498)>0.1) continue;

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
if(svtxfit->chisq() > 200.) continue;
if(svtxfit->decayLength()<0.0) continue;
double len = svtxfit->decayLength();
 double lenerr = svtxfit->decayLengthError();
if ((len/lenerr)<=2) continue;
 HepLorentzVector pks_temp = svtxfit->p4par();
//       if( fabs(pks_temp.m()-0.4977)>0.012) continue;
if(pks_temp.m()<0.487||pks_temp.m()>0.511)continue;
        pks_temp.boost(-0.011,0,0);
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
////////end reconstruct kso

//////select all gamma
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
//cout<<"nGam"<<gamnumber<<endl;
if (gamnumber>100) return StatusCode::SUCCESS;

       for(int x = 0; x < gamnumber - 1; x++){
    for(int y = x+1; y < gamnumber; y++) {

   HepLorentzVector p2g = Gamvector[x] + Gamvector[y];
if (p2g.m()>0.15 ||p2g.m()<0.115) continue;

   HepLorentzVector ppi0;
RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+Gamid[x]))->emcShower();//////////////////
RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+Gamid[y]))->emcShower();////////////
KalmanKinematicFit * kmfit =KalmanKinematicFit::instance();
      kmfit->init();kmfit->setIterNumber(5);
      kmfit->AddTrack(0, 0.0, g1Trk);
      kmfit->AddTrack(1, 0.0, g2Trk);
      kmfit->AddResonance(0, 0.134976, 0, 1);
double pi0chisq(9999);
bool oksq = kmfit->Fit(0);
  if(oksq){
       pi0chisq  = kmfit->chisq(0);
       ppi0 = kmfit->pfit(0)+kmfit->pfit(1);
       ppi0.boost(-0.011,0,0);
  }

       kmfit->BuildVirtualParticle(0);
       WTrackParameter wvpi0 = kmfit->wVirtualTrack(0);
      if(pi0chisq>20. ) continue;
      Pi0vector.push_back(ppi0);
      Pi0id1.push_back(Gamid[x]);
      Pi0id2.push_back(Gamid[y]);
      Pi02gammavector.push_back(p2g);
      Pi0chi.push_back(pi0chisq);
Pi0vector_gam1.push_back(kmfit->pfit(0));
Pi0vector_gam2.push_back(kmfit->pfit(1));
Trk_pi0.push_back(wvpi0);
//if(T4_D1b_6.size()>0){
//if((ppi0.e()-T4_D1b_6[0].e())>0)npi0p++;
//if((ppi0.e()-T4_D1b_6[0].e())<0)npi0m++;
//}
}
}
int pi0number=Pi0vector.size();

///////////////////////////////////////////pi0
       for(int x = 0; x < gamnumber - 1; x++){
    for(int y = x+1; y < gamnumber; y++) {

   HepLorentzVector p2g = Gamvector[x] + Gamvector[y];
if (p2g.m()<0.500 ||p2g.m()>0.57) continue;

   HepLorentzVector peta;
KalmanKinematicFit * kmfit =KalmanKinematicFit::instance();
RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+Gamid[x]))->emcShower();//////////////////
RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+Gamid[y]))->emcShower();////////////
      kmfit->init();kmfit->setIterNumber(5);
      kmfit->AddTrack(0, 0.0, g1Trk);
      kmfit->AddTrack(1, 0.0, g2Trk);
      kmfit->AddResonance(0, 0.54784, 0, 1);
double etachisq(9999);
bool oksq = kmfit->Fit(0);
  if(oksq){
       etachisq  = kmfit->chisq(0);
       peta = kmfit->pfit(0)+kmfit->pfit(1);
       peta.boost(-0.011,0,0);
  }
       kmfit->BuildVirtualParticle(0);
       WTrackParameter wveta = kmfit->wVirtualTrack(0);
      if(etachisq>=20 ) continue;
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
/////////////////////////////////////////////////////////////////////////////       Mu
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
      if (  dr1 >= 1.0) continue;
      if (drz >= 10.0) continue;
      if ( fabs(costheta) >= 0.93) continue;      
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc()); // use PID sub-system
      pid->identify(pid->onlyMuon() | pid->onlyKaon() | pid->onlyElectron() |pid->onlyPion());   
      pid->calculate();
      if(pid->probMuon()<= pid->probKaon()) continue;
      if(pid->probMuon() <= 0.001) continue;
      if(pid->probMuon()<= pid->probElectron()) continue;                            
        WTrackParameter mu(xmass[1],mdcKalTrk->getZHelixMu(),mdcKalTrk->getZErrorMu());
        HepVector mup_val = HepVector(7,0);
        mup_val = mu.w();
        HepLorentzVector P_MU(mup_val[0],mup_val[1],mup_val[2],mup_val[3]);
        P_MU.boost(-0.011,0,0);

bool temmu=false;
for(int xx=0;xx<iGood.size();xx++){
if(k==iGood[xx])temmu=true;
}
if(!temmu)continue;

double emcmu=0,dptmu=0;
	if((*itTrk)->isEmcShowerValid()) {
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		emcmu = emcTrk->energy();
	}
	if ((*itTrk)->isMucTrackValid()){
		RecMucTrack* mucTrk = (*itTrk)->mucTrack();
		dptmu = mucTrk->depth();
	}
    Emcmu.push_back(emcmu);
    Depthmu.push_back(dptmu);



Trk_mu.push_back(mu);
    Mucharge.push_back(mdcKalTrk->charge());
    Muid.push_back(k);
    Muvector.push_back(P_MU);
}
int munumber=Muvector.size();

//////////////////////////////////////////////////////////////
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
      if (  dr1 >= 1.0) continue;
      if (drz >= 10.0) continue;
      if ( fabs(costheta) >= 0.93) continue;      
      pid->init();
      pid->setMethod(pid->methodProbability());
      pid->setChiMinCut(4);
      pid->setRecTrack(*itTrk);
      pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc()); // use PID sub-system

      pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() | pid->onlyMuon());   
//      pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() );   
      pid->calculate();
      if(pid->probElectron() <= 0.001) continue;
      if((pid->probElectron())<=0.8*((pid->probKaon())+(pid->probElectron())+(pid->probPion()))) continue;
        WTrackParameter e(xmass[0],mdcKalTrk->getZHelixE(),mdcKalTrk->getZErrorE());
        HepVector ep_val = HepVector(7,0);
        ep_val = e.w();
        HepLorentzVector P_E(ep_val[0],ep_val[1],ep_val[2],ep_val[3]);
        P_E.boost(-0.011,0,0);

double emce=0,dpte=0;
	if((*itTrk)->isEmcShowerValid()) {
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		emce = emcTrk->energy();
	}
	if ((*itTrk)->isMucTrackValid()){
		RecMucTrack* mucTrk = (*itTrk)->mucTrack();
		dpte = mucTrk->depth();
	}

    Emce.push_back(emce);
    Depthe.push_back(dpte);

    Echarge.push_back(mdcKalTrk->charge());
    Eid.push_back(i);
    Evector.push_back(P_E);
Trk_e.push_back(e);
}
int enumber=Evector.size();
/////////////////////////////////////////////////////////////////////////
int tagcharge=-1;
for(int q=0;q<2;q++){
tagcharge=q*2-1;
for (int tagmode=1; tagmode<15; tagmode++){
////
bool findtag=false;
double massreccut=9999;
double mDs_rec=999;
double mDs_tag=999;
double mBC_tag=999;
double maxangle=999;
HepLorentzVector v4_1,v4_2,v4_3,v4_4,PSTDs;
Vint tagid;tagid.clear();
Vtrack Tag_trk;Tag_trk.clear();
////////////////////
if(tagmode==1){//ds- to k+ k- pi-
for(int i=0;i<knumber;i++){
	if(Kcharge[i]!=tagcharge)continue;
for(int j=0;j<knumber;j++){
	if(Kcharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Kid[i]);
idtemp.push_back(Kid[j]);
idtemp.push_back(Piid[k]);
if(Same(idtemp))continue;

if(Pivector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Kvector[i]+Kvector[j]+Pivector[k];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Kvector[i];
v4_2=Kvector[j];
v4_3=Pivector[k];

tagid.clear();
tagid.push_back(Kid[i]);
tagid.push_back(Kid[j]);
tagid.push_back(Piid[k]);

Tag_trk.clear();
Tag_trk.push_back(Trk_k[i]);
Tag_trk.push_back(Trk_k[j]);
Tag_trk.push_back(Trk_pi[k]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	ka.push_back(Kvector[i]);
	kb.push_back(Kvector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	kb.push_back(Kvector[i]);
	ka.push_back(Kvector[j]);
	pia.push_back(Pivector[k]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////
          findtag=true;
}

}
}
}
}//tagmode==1

if(tagmode==2){//ds- to k+ k- pi- pi0
for(int i=0;i<knumber;i++){
	if(Kcharge[i]!=tagcharge)continue;
for(int j=0;j<knumber;j++){
	if(Kcharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
for(int l=0;l<pi0number;l++){
Vint idtemp;idtemp.clear();
idtemp.push_back(Kid[i]);
idtemp.push_back(Kid[j]);
idtemp.push_back(Piid[k]);
idtemp.push_back(Pi0id1[l]);
idtemp.push_back(Pi0id2[l]);
if(Same(idtemp))continue;

if(Pivector[k].rho()<0.1)continue;
if(Pi0vector[l].rho()<0.1)continue;

        HepLorentzVector pDs = Kvector[i]+Kvector[j]+Pivector[k]+Pi0vector[l];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Kvector[i];
v4_2=Kvector[j];
v4_3=Pivector[k];
v4_4=Pi0vector[l];

tagid.clear();
tagid.push_back(Kid[i]);
tagid.push_back(Kid[j]);
tagid.push_back(Piid[k]);
tagid.push_back(Pi0id1[l]);
tagid.push_back(Pi0id2[l]);

Tag_trk.clear();
Tag_trk.push_back(Trk_k[i]);
Tag_trk.push_back(Trk_k[j]);
Tag_trk.push_back(Trk_pi[k]);
Tag_trk.push_back(Trk_pi0[l]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	ka.push_back(Kvector[i]);
	kb.push_back(Kvector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	kb.push_back(Kvector[i]);
	ka.push_back(Kvector[j]);
	pia.push_back(Pivector[k]);
}
pi0.push_back(Pi0vector[l]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
          findtag=true;
}
}
}
}
}
}//tagmode==2


if(tagmode==3){//ds- to pi+ pi- pi-
for(int i=0;i<pinumber;i++){
	if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
	if(Picharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Piid[k]);
if(Same(idtemp))continue;

if(Pivector[i].rho()<0.1)continue;
if(Pivector[j].rho()<0.1)continue;
if(Pivector[k].rho()<0.1)continue;
if(fabs((Pivector[i]+Pivector[j]).m()-0.498)<0.03)continue;
if(fabs((Pivector[i]+Pivector[k]).m()-0.498)<0.03)continue;

        HepLorentzVector pDs = Pivector[i]+Pivector[j]+Pivector[k];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Pivector[i];
v4_2=Pivector[j];
v4_3=Pivector[k];

tagid.clear();
tagid.push_back(Piid[i]);
tagid.push_back(Piid[j]);
tagid.push_back(Piid[k]);

Tag_trk.clear();
Tag_trk.push_back(Trk_pi[i]);
Tag_trk.push_back(Trk_pi[j]);
Tag_trk.push_back(Trk_pi[k]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
	pia.push_back(Pivector[k]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
          findtag=true;
}

}
}
}
}//tagmode==3


if(tagmode==4){//ds- to ks k-
for(int i=0;i<ksonumber;i++){
for(int j=0;j<knumber;j++){
	if(Kcharge[j]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Ksoid1[i]);
idtemp.push_back(Ksoid2[i]);
idtemp.push_back(Kid[j]);
if(Same(idtemp))continue;

        HepLorentzVector pDs = Ksovector[i]+Kvector[j];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Ksovector[i];
v4_2=Kvector[j];

tagid.clear();
tagid.push_back(Ksoid1[i]);
tagid.push_back(Ksoid2[i]);
tagid.push_back(Kid[j]);

Tag_trk.clear();
Tag_trk.push_back(Trk_ks[i]);
Tag_trk.push_back(Trk_k[j]);
///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	kb.push_back(Kvector[j]);
}
if(tagcharge==-1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	ka.push_back(Kvector[j]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}

}
}
}//tagmode==4


if(tagmode==5){//ds- to ks k- pi0
for(int i=0;i<ksonumber;i++){
for(int j=0;j<knumber;j++){
for(int k=0;k<pi0number;k++){
	if(Kcharge[j]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Ksoid1[i]);
idtemp.push_back(Ksoid2[i]);
idtemp.push_back(Kid[j]);
idtemp.push_back(Pi0id1[k]);
idtemp.push_back(Pi0id2[k]);
if(Same(idtemp))continue;

if(Pi0vector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Ksovector[i]+Kvector[j]+Pi0vector[k];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Ksovector[i];
v4_2=Kvector[j];
v4_3=Pi0vector[k];

tagid.clear();
tagid.push_back(Ksoid1[i]);
tagid.push_back(Ksoid2[i]);
tagid.push_back(Kid[j]);
tagid.push_back(Pi0id1[k]);
tagid.push_back(Pi0id2[k]);

Tag_trk.clear();
Tag_trk.push_back(Trk_ks[i]);
Tag_trk.push_back(Trk_k[j]);
Tag_trk.push_back(Trk_pi0[k]);
///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	kb.push_back(Kvector[j]);
}
if(tagcharge==-1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	ka.push_back(Kvector[j]);
}
pi0.push_back(Pi0vector[k]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}

}
}
}
}//tagmode==5


if(tagmode==6){//ds- to k- pi+ pi-
for(int i=0;i<knumber;i++){
	if(Kcharge[i]==tagcharge)continue;
for(int j=0;j<pinumber;j++){
	if(Picharge[j]!=tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Kid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Piid[k]);
if(Same(idtemp))continue;

if(fabs((Pivector[j]+Pivector[k]).m()-0.498)<0.03)continue;
if(Pivector[j].rho()<0.1)continue;
if(Pivector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Kvector[i]+Pivector[j]+Pivector[k];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Kvector[i];
v4_2=Pivector[j];
v4_3=Pivector[k];

tagid.clear();
tagid.push_back(Kid[i]);
tagid.push_back(Piid[j]);
tagid.push_back(Piid[k]);

Tag_trk.clear();
Tag_trk.push_back(Trk_k[i]);
Tag_trk.push_back(Trk_pi[j]);
Tag_trk.push_back(Trk_pi[k]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	kb.push_back(Kvector[i]);
	pia.push_back(Pivector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	ka.push_back(Kvector[i]);
	pib.push_back(Pivector[j]);
	pia.push_back(Pivector[k]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////
          findtag=true;
}

}
}
}
}//tagmode==6


if(tagmode==7){//ds- to ks ks pi-
for(int i=0;i<ksonumber;i++){
for(int j=0;j<ksonumber;j++){
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Ksoid1[i]);
idtemp.push_back(Ksoid2[i]);
idtemp.push_back(Ksoid1[j]);
idtemp.push_back(Ksoid2[j]);
idtemp.push_back(Piid[k]);
if(Same(idtemp))continue;
if(Pivector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Ksovector[i]+Ksovector[j]+Pivector[k];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Ksovector[i];
v4_2=Ksovector[j];
v4_3=Pivector[k];

tagid.clear();
tagid.push_back(Ksoid1[i]);
tagid.push_back(Ksoid2[i]);
tagid.push_back(Ksoid1[j]);
tagid.push_back(Ksoid2[j]);
tagid.push_back(Piid[k]);

Tag_trk.clear();
Tag_trk.push_back(Trk_ks[i]);
Tag_trk.push_back(Trk_ks[j]);
Tag_trk.push_back(Trk_pi[k]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Ksovector_pip[i]);
	pia.push_back(Ksovector_pip[j]);
	pib.push_back(Ksovector_pim[i]);
	pib.push_back(Ksovector_pim[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	pia.push_back(Ksovector_pip[i]);
	pia.push_back(Ksovector_pip[j]);
	pib.push_back(Ksovector_pim[i]);
	pib.push_back(Ksovector_pim[j]);
	pia.push_back(Pivector[k]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}

}
}
}
}//tagmode==7

if(tagmode==8){//ds- to ks k+ pi- pi-
for(int i=0;i<ksonumber;i++){
for(int j=0;j<knumber;j++){
	if(Kcharge[j]!=tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
for(int l=0;l<pinumber;l++){
	if(Picharge[l]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Ksoid1[i]);
idtemp.push_back(Ksoid2[i]);
idtemp.push_back(Kid[j]);
idtemp.push_back(Piid[k]);
idtemp.push_back(Piid[l]);
if(Same(idtemp))continue;

if(Pivector[k].rho()<0.1)continue;
if(Pivector[l].rho()<0.1)continue;

        HepLorentzVector pDs = Ksovector[i]+Kvector[j]+Pivector[k]+Pivector[l];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Ksovector[i];
v4_2=Kvector[j];
v4_3=Pivector[k];
v4_4=Pivector[l];

tagid.clear();
tagid.push_back(Ksoid1[i]);
tagid.push_back(Ksoid2[i]);
tagid.push_back(Kid[j]);
tagid.push_back(Piid[k]);
tagid.push_back(Piid[l]);

Tag_trk.clear();
Tag_trk.push_back(Trk_ks[i]);
Tag_trk.push_back(Trk_k[j]);
Tag_trk.push_back(Trk_pi[k]);
Tag_trk.push_back(Trk_pi[l]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	ka.push_back(Kvector[j]);
	pib.push_back(Pivector[k]);
	pib.push_back(Pivector[l]);
}
if(tagcharge==-1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	kb.push_back(Kvector[j]);
	pia.push_back(Pivector[k]);
	pia.push_back(Pivector[l]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}
}
}
}
}
}//tagmode==8


if(tagmode==9){//ds- to ks k- pi+ pi-
for(int i=0;i<ksonumber;i++){
for(int j=0;j<knumber;j++){
	if(Kcharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]!=tagcharge)continue;
for(int l=0;l<pinumber;l++){
	if(Picharge[l]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Ksoid1[i]);
idtemp.push_back(Ksoid2[i]);
idtemp.push_back(Kid[j]);
idtemp.push_back(Piid[k]);
idtemp.push_back(Piid[l]);
if(Same(idtemp))continue;

if(Pivector[k].rho()<0.1)continue;
if(Pivector[l].rho()<0.1)continue;

        HepLorentzVector pDs = Ksovector[i]+Kvector[j]+Pivector[k]+Pivector[l];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Ksovector[i];
v4_2=Kvector[j];
v4_3=Pivector[k];
v4_4=Pivector[l];

tagid.clear();
tagid.push_back(Ksoid1[i]);
tagid.push_back(Ksoid2[i]);
tagid.push_back(Kid[j]);
tagid.push_back(Piid[k]);
tagid.push_back(Piid[l]);

Tag_trk.clear();
Tag_trk.push_back(Trk_ks[i]);
Tag_trk.push_back(Trk_k[j]);
Tag_trk.push_back(Trk_pi[k]);
Tag_trk.push_back(Trk_pi[l]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	kb.push_back(Kvector[j]);
	pia.push_back(Pivector[k]);
	pib.push_back(Pivector[l]);
}
if(tagcharge==-1){
	pia.push_back(Ksovector_pip[i]);
	pib.push_back(Ksovector_pim[i]);
	ka.push_back(Kvector[j]);
	pib.push_back(Pivector[k]);
	pia.push_back(Pivector[l]);
}
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}
}
}
}
}
}//tagmode==9


if(tagmode==10){//ds- to eta pi-
for(int i=0;i<etanumber;i++){
for(int j=0;j<pinumber;j++){
	if(Picharge[j]==tagcharge)continue;
Vint idtemp;idtemp.clear();
idtemp.push_back(Etaid1[i]);
idtemp.push_back(Etaid2[i]);
idtemp.push_back(Piid[j]);
if(Same(idtemp))continue;

        HepLorentzVector pDs = Etavector[i]+Pivector[j];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Etavector[i];
v4_2=Pivector[j];

tagid.clear();
tagid.push_back(Etaid1[i]);
tagid.push_back(Etaid2[i]);
tagid.push_back(Piid[j]);

Tag_trk.clear();
Tag_trk.push_back(Trk_eta[i]);
Tag_trk.push_back(Trk_pi[j]);


///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pib.push_back(Pivector[j]);
}
if(tagcharge==-1){
	pia.push_back(Pivector[j]);
}
eta.push_back(Etavector[i]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}

}
}
}//tagmode==10



if(tagmode==11){//ds- to eta(pi+ pi- pi0)pi-
for(int i=0;i<pinumber;i++){
	if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
	if(Picharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
for(int l=0;l<pi0number;l++){
Vint idtemp;idtemp.clear();
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Piid[k]);
idtemp.push_back(Pi0id1[l]);
idtemp.push_back(Pi0id2[l]);
if(Same(idtemp))continue;
if((Pivector[i]+Pivector[j]+Pi0vector[l]).m()<0.53||(Pivector[i]+Pivector[j]+Pi0vector[l]).m()>0.57)continue;
if(Pivector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Pivector[i]+Pivector[j]+Pivector[k]+Pi0vector[l];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Pivector[i];
v4_2=Pivector[j];
v4_3=Pivector[k];
v4_4=Pi0vector[l];

tagid.clear();
tagid.push_back(Piid[i]);
tagid.push_back(Piid[j]);
tagid.push_back(Piid[k]);
tagid.push_back(Pi0id1[l]);
tagid.push_back(Pi0id2[l]);

Tag_trk.clear();
Tag_trk.push_back(Trk_pi[i]);
Tag_trk.push_back(Trk_pi[j]);
Tag_trk.push_back(Trk_pi[k]);
Tag_trk.push_back(Trk_pi0[l]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
	pia.push_back(Pivector[k]);
}
pi0.push_back(Pi0vector[l]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}
}
}
}
}
}//tagmode==11


if(tagmode==12){//ds- to etap(pi+ pi- eta)pi-
for(int i=0;i<pinumber;i++){
	if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
	if(Picharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
for(int l=0;l<etanumber;l++){
Vint idtemp;idtemp.clear();
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Piid[k]);
idtemp.push_back(Etaid1[l]);
idtemp.push_back(Etaid2[l]);
if(Same(idtemp))continue;
if(abs((Pivector[i]+Pivector[j]+Etavector[l]).m()-0.958)>0.012)continue;
if(Pivector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Pivector[i]+Pivector[j]+Pivector[k]+Etavector[l];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Pivector[i];
v4_2=Pivector[j];
v4_3=Pivector[k];
v4_4=Etavector[l];

tagid.clear();
tagid.push_back(Piid[i]);
tagid.push_back(Piid[j]);
tagid.push_back(Piid[k]);
tagid.push_back(Etaid1[l]);
tagid.push_back(Etaid2[l]);

Tag_trk.clear();
Tag_trk.push_back(Trk_pi[i]);
Tag_trk.push_back(Trk_pi[j]);
Tag_trk.push_back(Trk_pi[k]);
Tag_trk.push_back(Trk_eta[l]);


///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
	pia.push_back(Pivector[k]);
}
eta.push_back(Etavector[l]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}
}
}
}
}
}//tagmode==12



if(tagmode==13){//ds- to etap(gamma pi+ pi-)pi-
for(int i=0;i<pinumber;i++){
	if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
	if(Picharge[j]==tagcharge)continue;
for(int k=0;k<pinumber;k++){
	if(Picharge[k]==tagcharge)continue;
for(int l=0;l<gamnumber;l++){
Vint idtemp;idtemp.clear();
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Piid[k]);
idtemp.push_back(Gamid[l]);
if(Same(idtemp))continue;
if((Pivector[i]+Pivector[j]).m()<0.57||(Pivector[i]+Pivector[j]).m()>0.97)continue;
if(abs((Pivector[i]+Pivector[j]+Gamvector[l]).m()-0.958)>0.018)continue;
if(Pivector[i].rho()<0.1)continue;
if(Pivector[j].rho()<0.1)continue;
if(Pivector[k].rho()<0.1)continue;
if(Gamvector[l].rho()<0.1)continue;

        HepLorentzVector pDs = Pivector[i]+Pivector[j]+Pivector[k]+Gamvector[l];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Pivector[i];
v4_2=Pivector[j];
v4_3=Pivector[k];
v4_4=Gamvector[l];

tagid.clear();
tagid.push_back(Piid[i]);
tagid.push_back(Piid[j]);
tagid.push_back(Piid[k]);
tagid.push_back(Gamid[l]);

Tag_trk.clear();
Tag_trk.push_back(Trk_pi[i]);
Tag_trk.push_back(Trk_pi[j]);
Tag_trk.push_back(Trk_pi[k]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
	pib.push_back(Pivector[k]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
	pia.push_back(Pivector[k]);
}
gamma.push_back(Gamvector[l]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////

          findtag=true;
}
}
}
}
}
}//tagmode==13

if(tagmode==14){//ds- to eta rho(pi- pi0)
for(int i=0;i<etanumber;i++){
for(int j=0;j<pinumber;j++){
	if(Picharge[j]==tagcharge)continue;
for(int k=0;k<pi0number;k++){
Vint idtemp;idtemp.clear();
idtemp.push_back(Etaid1[i]);
idtemp.push_back(Etaid2[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Pi0id1[k]);
idtemp.push_back(Pi0id2[k]);
if(Same(idtemp))continue;

if((Pivector[j]+Pi0vector[k]).m()<0.57||(Pivector[j]+Pi0vector[k]).m()>0.97)continue;
if(Pivector[j].rho()<0.1)continue;
if(Pi0vector[k].rho()<0.1)continue;

        HepLorentzVector pDs = Etavector[i]+Pivector[j]+Pi0vector[k];
	double pDstag=pDs.rho();
        double temp1 = (ecm/2)*(ecm/2)-pDstag*pDstag ;
        if(temp1<0) temp1 =0;
        double mass_bc  = sqrt(temp1);
        if(pDs.m()>2.03||pDs.m()<1.89) continue; 
	
	HepLorentzVector PDs_rec_temp = ECMS-pDs;
	double mass_Dsrec = sqrt((ecm-sqrt(1.96849*1.96849+pDstag*pDstag))*(ecm-sqrt(1.96849*1.96849+pDstag*pDstag))-pDstag*pDstag);
	if(mass_bc<2.00||mass_bc>2.1) continue;

                if(abs(mass_Dsrec-2.112)<massreccut){
massreccut=abs(mass_Dsrec-2.112);
mDs_rec=mass_Dsrec;
mDs_tag=pDs.m();
mBC_tag=mass_bc;

PSTDs=pDs;

v4_1=Etavector[i];
v4_2=Pivector[j];
v4_3=Pi0vector[k];

tagid.clear();
tagid.push_back(Etaid1[i]);
tagid.push_back(Etaid2[i]);
tagid.push_back(Piid[j]);
tagid.push_back(Pi0id1[k]);
tagid.push_back(Pi0id2[k]);

Tag_trk.clear();
Tag_trk.push_back(Trk_eta[i]);
Tag_trk.push_back(Trk_pi[j]);
Tag_trk.push_back(Trk_pi0[k]);

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pib.push_back(Pivector[j]);
}
if(tagcharge==-1){
	pia.push_back(Pivector[j]);
}
eta.push_back(Etavector[i]);
pi0.push_back(Pi0vector[k]);
TruthMatch.InputRec(-1*tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle=TruthMatch.match();
////
          findtag=true;
}
}
}
}
}//tagmode==14

///////////////////////
if(findtag) {
     event_temp1             =         event;
       run_temp1             =         runNo;
   mcmode1_temp1             =       mcmode1;
   mcmode2_temp1             =       mcmode2;
   mcmodea_temp1             =       mcmodea;
   mcmodeb_temp1             =       mcmodeb;
 tagcharge_temp1             =     tagcharge;
   tagmode_temp1             =       tagmode;
     mctag_temp1             =       m_mctag;
  Dstmode1_temp1             =      Dstmode1;
  Dstmode2_temp1             =      Dstmode2;
       ecm_temp1             =           ecm;

  maxangle_temp1             =      maxangle;

   mDs_rec_temp1             =       mDs_rec;
   mDs_tag_temp1             =       mDs_tag;
   mBC_tag_temp1             =       mBC_tag;
/*
     index_temp1             =             4;
      V4_1_temp1[0]          =     v4_1.px();
      V4_1_temp1[1]          =     v4_1.py();
      V4_1_temp1[2]          =     v4_1.pz();
      V4_1_temp1[3]          =      v4_1.e();

      V4_2_temp1[0]          =     v4_2.px();
      V4_2_temp1[1]          =     v4_2.py();
      V4_2_temp1[2]          =     v4_2.pz();
      V4_2_temp1[3]          =      v4_2.e();
      
      V4_3_temp1[0]          =     v4_3.px();
      V4_3_temp1[1]          =     v4_3.py();
      V4_3_temp1[2]          =     v4_3.pz();
      V4_3_temp1[3]          =      v4_3.e();
      
      V4_4_temp1[0]          =     v4_4.px();
      V4_4_temp1[1]          =     v4_4.py();
      V4_4_temp1[2]          =     v4_4.pz();
      V4_4_temp1[3]          =      v4_4.e();
*/
m_tuple1->write();
}
if(!findtag)continue;




//find gamma or pi0 from Ds*
double delE_cut=9999;
int gamma_final=999;
bool findgamma=false;
double delE_final=999;
HepLorentzVector Pgtag_final;
HepLorentzVector v4_5;
for(int ga=0;ga<gamnumber+pi0number;ga++){

HepLorentzVector Pgtag;
HepLorentzVector v4_5_tem;
bool tem1=false;
if(ga<gamnumber){//assume Ds*->gamma Ds
Vint idtemp=tagid;
idtemp.push_back(Gamid[ga]);
if(Same(idtemp))continue;
Pgtag=PSTDs+Gamvector[ga];
Pgtag.setE(sqrt(PSTDs.rho()*PSTDs.rho()+1.9685*1.9685)+Gamvector[ga].e());
v4_5_tem=Gamvector[ga];
tem1=true;
}
else {//assume Ds*->gamma Ds
int num=ga-gamnumber;
	Vint idtemp=tagid;
	idtemp.push_back(Pi0id1[num]);
	idtemp.push_back(Pi0id2[num]);
	if(Same(idtemp))continue;
	Pgtag=PSTDs+Pi0vector[num];
	Pgtag.setE(sqrt(PSTDs.rho()*PSTDs.rho()+1.9685*1.9685)+Pi0vector[num].e());
	v4_5_tem=Pi0vector[num];
tem1=true;
}
if(!tem1)continue;
                    HepLorentzVector Prc_gtg = ECMS-Pgtag;

		    double pmiss = Prc_gtg.rho();
		    double Emiss = sqrt(pmiss*pmiss+1.9685*1.9685);

		    double deltaE = ecm - (Pgtag.e()+Emiss);
		    if(fabs(deltaE)<delE_cut){
			    delE_cut = abs(deltaE);
gamma_final=ga;
delE_final=deltaE;
Pgtag_final=Pgtag;
v4_5=v4_5_tem;
findgamma=true;
}
}

if(!findgamma)continue;

double angle_Dst=999;
if(T_Dst.size()==1){
if(gamma_final<gamnumber){
angle_Dst=T_Dst[0].vect().angle(Gamvector[gamma_final].vect())/3.1415926*180.;
}
if(gamma_final>=gamnumber){
angle_Dst=T_Dst[0].vect().angle(Pi0vector[gamma_final-gamnumber].vect())/3.1415926*180.;
}
}


if(findgamma){
    event_temp0             =         event;
      run_temp0             =         runNo;
  mcmode1_temp0             =       mcmode1;
  mcmode2_temp0             =       mcmode2;
  mcmodea_temp0             =       mcmodea;
  mcmodeb_temp0             =       mcmodeb;
 Dstmode1_temp0             =      Dstmode1;
 Dstmode2_temp0             =      Dstmode2;
      ecm_temp0             =           ecm;
     delE_temp0             =    delE_final;
  tagmode_temp0             =       tagmode;
  mctag_temp0               =       m_mctag;
tagcharge_temp0             =     tagcharge;

angle_Dst_temp0             =     angle_Dst;

if(gamma_final<gamnumber)gamorpi0_temp0=-1;
if(gamma_final>=gamnumber)gamorpi0_temp0=1;
/*
index_temp0             =             4;
V4_1_temp0[0]          =     v4_1.px();
V4_1_temp0[1]          =     v4_1.py();
V4_1_temp0[2]          =     v4_1.pz();
V4_1_temp0[3]          =      v4_1.e();

V4_2_temp0[0]          =     v4_2.px();
V4_2_temp0[1]          =     v4_2.py();
V4_2_temp0[2]          =     v4_2.pz();
V4_2_temp0[3]          =      v4_2.e();

V4_3_temp0[0]          =     v4_3.px();
V4_3_temp0[1]          =     v4_3.py();
V4_3_temp0[2]          =     v4_3.pz();
V4_3_temp0[3]          =      v4_3.e();

V4_4_temp0[0]          =     v4_4.px();
V4_4_temp0[1]          =     v4_4.py();
V4_4_temp0[2]          =     v4_4.pz();
V4_4_temp0[3]          =      v4_4.e();

V4_5_temp0[0]          =     v4_5.px();
V4_5_temp0[1]          =     v4_5.py();
V4_5_temp0[2]          =     v4_5.pz();
V4_5_temp0[3]          =      v4_5.e();
*/
m_tuple0->write();
}


Vint Dstid=tagid;
if(gamma_final<gamnumber){
	Dstid.push_back(Gamid[gamma_final]);
}
if(gamma_final>=gamnumber){
	Dstid.push_back(Pi0id1[gamma_final-gamnumber]);
        Dstid.push_back(Pi0id2[gamma_final-gamnumber]);
}

//begin select signal side
//Ds^+ -> eta(gamma gamma) mu nu
for(int recmode=0;recmode<4;recmode++){
//////
double chicut=999.;
bool findsig=false;
double mm2m=999;
double m12=999,m13=999,m14=999,m15=999,m23=999,m24=999,m25=999,m34=999,m35=999,m45=999;
double m123=999,m124=999,m125=999,m134=999,m135=999,m145=999,m234=999,m235=999,m245=999,m345=9999;
double m1234=999,m1235=999,m1245=999,m1345=999,m2345=999;
double q2=999;
double maxangle_rec=999;
double mm2mft=999;
double m12ft=999,m13ft=999,m14ft=999,m15ft=999,m23ft=999,m24ft=999,m25ft=999,m34ft=999,m35ft=999,m45ft=999;
double m123ft=999,m124ft=999,m125ft=999,m134ft=999,m135ft=999,m145ft=999,m234ft=999,m235ft=999,m245ft=999,m345ft=9999;
double m1234ft=999,m1235ft=999,m1245ft=999,m1345ft=999,m2345ft=999;
double q2ft=999;

int sgmode=0;

double muemc=0,mudepth=0;
HepLorentzVector V4_1ft,V4_2ft,V4_3ft,V4_4ft;
HepLorentzVector v4_6,v4_7,v4_8,v4_9;
Vint TotID;TotID.clear();
//////
if(recmode==0){ //Ds+ -> eta(gamma gamma) mu nu

for(int i=0;i<etanumber;i++){
for(int j=0;j<munumber;j++){
if(Mucharge[j]!=tagcharge)continue;

Vint idtemp=Dstid;
idtemp.push_back(Etaid1[i]);
idtemp.push_back(Etaid2[i]);
idtemp.push_back(Muid[j]);
if(Same(idtemp))continue;
if(etachi[i]<=chicut){
chicut=etachi[i];
HepLorentzVector Pmiss=ECMS-Pgtag_final-Etavector[i]-Muvector[j]; 

HepLorentzVector P_nu = Pmiss;
P_nu.setE(Pmiss.rho());
P_nu.setRho(Pmiss.rho());
P_nu.setTheta(Pmiss.theta());
P_nu.setPhi(Pmiss.phi());
mm2m=Pmiss.e()*Pmiss.e()-Pmiss.rho()*Pmiss.rho();
m12=(Etavector[i]+Muvector[j]).m();
m13=(Etavector[i]+P_nu).m();
m23=(Muvector[j]+P_nu).m();

q2=(Muvector[j]+P_nu).m2();

muemc=Emcmu[j];
mudepth=Depthmu[j];

v4_6=Etavector[i];
v4_7=Muvector[i];

/////////all used ID
TotID.clear();
TotID=Dstid;
TotID.push_back(Etaid1[i]);
TotID.push_back(Etaid2[i]);
TotID.push_back(Muid[j]);
//////////

/////gamma or pi0 come from ST
KalmanKinematicFit * kmfit1 = KalmanKinematicFit::instance();
kmfit1->init();
kmfit1->setChisqCut(5000000);
kmfit1->AddTrack(0, Trk_eta[i]);
kmfit1->AddTrack(1, Trk_mu[j]);
kmfit1->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit1->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit1->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit1->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit1->AddTrack(7, 0.0,g_etap);
}
kmfit1->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit1->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(1, mDs, 4,5,6,7,8);

if(Tag_trk.size()==2)kmfit1->AddResonance(2, mDst, 3,4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(2, mDst, 3,4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(2, mDst, 3,4,5,6,7,8);
kmfit1->AddFourMomentum(3, ecms);
kmfit1->Fit();
double   kmfit_chi1=kmfit1->chisq();

HepLorentzVector v1_temp1=kmfit1->pfit(0);//eta
HepLorentzVector v2_temp1=kmfit1->pfit(1);//mu
HepLorentzVector v3_temp1=kmfit1->pfit(2);//nu


/////gamma or pi0 come from DT
KalmanKinematicFit * kmfit2 = KalmanKinematicFit::instance();
kmfit2->init();
kmfit2->setChisqCut(5000000);
kmfit2->AddTrack(0, Trk_eta[i]);
kmfit2->AddTrack(1, Trk_mu[j]);
kmfit2->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit2->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit2->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit2->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit2->AddTrack(7, 0.0,g_etap);
}
kmfit2->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit2->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit2->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit2->AddResonance(1, mDs, 4,5,6,7,8);

kmfit2->AddResonance(2, mDst, 0,1,2,3);
kmfit2->AddFourMomentum(3, ecms);
kmfit2->Fit();
double   kmfit_chi2=kmfit2->chisq();


HepLorentzVector v1_temp2=kmfit2->pfit(0);//eta
HepLorentzVector v2_temp2=kmfit2->pfit(1);//mu
HepLorentzVector v3_temp2=kmfit2->pfit(2);//nu


if(kmfit_chi1<kmfit_chi2){
V4_1ft=v1_temp1;//eta
V4_2ft=v2_temp1;//mu
V4_3ft=v3_temp1;//nv
sgmode=-1;
}
else{
V4_1ft=v1_temp2;//eta
V4_2ft=v2_temp2;//mu
V4_3ft=v3_temp2;//nv
sgmode=1;
}


mm2mft=V4_3ft.e()*V4_3ft.e()-V4_3ft.rho()*V4_3ft.rho();
m12ft=(V4_1ft+V4_2ft).m();
m13ft=(V4_1ft+V4_3ft).m();
m23ft=(V4_2ft+V4_3ft).m();

HepLorentzVector p_nu_temp=V4_3ft;
p_nu_temp.setE(V4_3ft.rho());
q2ft=(V4_2ft+p_nu_temp).m2();

if(kmfit_chi1>9999.&&kmfit_chi2>9999.){
mm2mft=mm2m;
m12ft=m12;
m13ft=m13;
m23ft=m23;
q2ft=q2;
}

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();

eta.push_back(Etavector[i]);
mu.push_back(Muvector[j]);
TruthMatch.InputRec(tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle_rec=TruthMatch.match();
////

findsig=true;

}
}
}
}//recmode==0
//
/////////////////
if(recmode==1){//Ds -> eta(pi+ pi- pi0) mu nu

for(int i=0;i<pinumber;i++){
if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
if(Picharge[j]==tagcharge)continue;
for(int k=0;k<pi0number;k++){
for(int l=0;l<munumber;l++){
if(Mucharge[l]!=tagcharge)continue;

Vint idtemp=Dstid;
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Pi0id1[k]);
idtemp.push_back(Pi0id2[k]);
idtemp.push_back(Muid[l]);
if(Same(idtemp))continue;

if((Pivector[i]+Pivector[j]+Pi0vector[k]).m()<0.53||(Pivector[i]+Pivector[j]+Pi0vector[k]).m()>0.57)continue;

KalmanKinematicFit * kmfita = KalmanKinematicFit::instance();
kmfita->init();
kmfita->setChisqCut(50000);
kmfita->AddTrack(0, Trk_pi[i]);
kmfita->AddTrack(1, Trk_pi[j]);
kmfita->AddTrack(2, Trk_pi0[k]);
kmfita->AddResonance(0, meta, 0, 1, 2);
if(!kmfita->Fit(0)) continue;
kmfita->BuildVirtualParticle(0);
WTrackParameter wveta = kmfita->wVirtualTrack(0);

HepLorentzVector PETA = kmfita->pfit(0)+kmfita->pfit(1)+kmfita->pfit(2);
PETA.boost(-0.011,0,0);
double Ft_chi=kmfita->chisq(0);


if(Ft_chi<=chicut){
chicut=Ft_chi;
HepLorentzVector Peta=Pivector[i]+Pivector[j]+Pi0vector[k];
HepLorentzVector Pmiss=ECMS-Pgtag_final-Peta-Muvector[l]; 

HepLorentzVector P_nu = Pmiss;
P_nu.setE(Pmiss.rho());
P_nu.setRho(Pmiss.rho());
P_nu.setTheta(Pmiss.theta());
P_nu.setPhi(Pmiss.phi());
mm2m=Pmiss.e()*Pmiss.e()-Pmiss.rho()*Pmiss.rho();
m12=(Peta+Muvector[l]).m();
m13=(Peta+P_nu).m();
m23=(Muvector[l]+P_nu).m();

q2=(Muvector[l]+P_nu).m2();

muemc=Emcmu[l];
mudepth=Depthmu[l];


v4_6=Pivector[i];
v4_7=Pivector[j];
v4_8=Pi0vector[k];
v4_9=Muvector[l];
/////////all used ID
TotID.clear();
TotID=Dstid;
TotID.push_back(Piid[i]);
TotID.push_back(Piid[j]);
TotID.push_back(Pi0id1[k]);
TotID.push_back(Pi0id2[k]);
TotID.push_back(Muid[l]);
//////////

/////gamma or pi0 come from ST
KalmanKinematicFit * kmfit1 = KalmanKinematicFit::instance();
kmfit1->init();
kmfit1->setChisqCut(5000000);
kmfit1->AddTrack(0, wveta);
kmfit1->AddTrack(1, Trk_mu[l]);
kmfit1->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit1->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit1->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit1->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit1->AddTrack(7, 0.0,g_etap);
}
kmfit1->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit1->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(1, mDs, 4,5,6,7,8);

if(Tag_trk.size()==2)kmfit1->AddResonance(2, mDst, 3,4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(2, mDst, 3,4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(2, mDst, 3,4,5,6,7,8);
kmfit1->AddFourMomentum(3, ecms);
kmfit1->Fit();
double   kmfit_chi1=kmfit1->chisq();

HepLorentzVector v1_temp1=kmfit1->pfit(0);//eta
HepLorentzVector v2_temp1=kmfit1->pfit(1);//mu
HepLorentzVector v3_temp1=kmfit1->pfit(2);//nu


/////gamma or pi0 come from DT
KalmanKinematicFit * kmfit2 = KalmanKinematicFit::instance();
kmfit2->init();
kmfit2->setChisqCut(5000000);
kmfit2->AddTrack(0, wveta);
kmfit2->AddTrack(1, Trk_mu[l]);
kmfit2->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit2->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit2->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit2->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit2->AddTrack(7, 0.0,g_etap);
}
kmfit2->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit2->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit2->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit2->AddResonance(1, mDs, 4,5,6,7,8);

kmfit2->AddResonance(2, mDst, 0,1,2,3);
kmfit2->AddFourMomentum(3, ecms);
kmfit2->Fit();
double   kmfit_chi2=kmfit2->chisq();


HepLorentzVector v1_temp2=kmfit2->pfit(0);//eta
HepLorentzVector v2_temp2=kmfit2->pfit(1);//mu
HepLorentzVector v3_temp2=kmfit2->pfit(2);//nu


if(kmfit_chi1<kmfit_chi2){
V4_1ft=v1_temp1;//eta
V4_2ft=v2_temp1;//mu
V4_3ft=v3_temp1;//nv
sgmode=-1;
}
else{
V4_1ft=v1_temp2;//eta
V4_2ft=v2_temp2;//mu
V4_3ft=v3_temp2;//nv
sgmode=1;
}


mm2mft=V4_3ft.e()*V4_3ft.e()-V4_3ft.rho()*V4_3ft.rho();
m12ft=(V4_1ft+V4_2ft).m();
m13ft=(V4_1ft+V4_3ft).m();
m23ft=(V4_2ft+V4_3ft).m();

HepLorentzVector p_nu_temp=V4_3ft;
p_nu_temp.setE(V4_3ft.rho());
q2ft=(V4_2ft+p_nu_temp).m2();

if(kmfit_chi1>9999.&&kmfit_chi2>9999.){
mm2mft=mm2m;
m12ft=m12;
m13ft=m13;
m23ft=m23;
q2ft=q2;
}

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
}
pi0.push_back(Pi0vector[k]);
mu.push_back(Muvector[l]);
TruthMatch.InputRec(tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle_rec=TruthMatch.match();
////

findsig=true;

}
}
}
}
}
}//recmode==1

if(recmode==2){//Ds -> etap(pi+ pi- eta) mu nu

for(int i=0;i<pinumber;i++){
if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
if(Picharge[j]==tagcharge)continue;
for(int k=0;k<etanumber;k++){
for(int l=0;l<munumber;l++){
if(Mucharge[l]!=tagcharge)continue;

Vint idtemp=Dstid;
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Etaid1[k]);
idtemp.push_back(Etaid2[k]);
idtemp.push_back(Muid[l]);
if(Same(idtemp))continue;

if((Pivector[i]+Pivector[j]+Etavector[k]).m()<0.946||(Pivector[i]+Pivector[j]+Etavector[k]).m()>0.97)continue;

KalmanKinematicFit * kmfita = KalmanKinematicFit::instance();
kmfita->init();
kmfita->setChisqCut(50000);
kmfita->AddTrack(0, Trk_pi[i]);
kmfita->AddTrack(1, Trk_pi[j]);
kmfita->AddTrack(2, Trk_eta[k]);
kmfita->AddResonance(0, metap, 0, 1, 2);
if(!kmfita->Fit(0)) continue;
kmfita->BuildVirtualParticle(0);
WTrackParameter wveta = kmfita->wVirtualTrack(0);

HepLorentzVector PETA = kmfita->pfit(0)+kmfita->pfit(1)+kmfita->pfit(2);
PETA.boost(-0.011,0,0);
double Ft_chi=kmfita->chisq(0);


if(Ft_chi<=chicut){
chicut=Ft_chi;
HepLorentzVector Peta=Pivector[i]+Pivector[j]+Etavector[k];
HepLorentzVector Pmiss=ECMS-Pgtag_final-Peta-Muvector[l]; 

HepLorentzVector P_nu = Pmiss;
P_nu.setE(Pmiss.rho());
P_nu.setRho(Pmiss.rho());
P_nu.setTheta(Pmiss.theta());
P_nu.setPhi(Pmiss.phi());
mm2m=Pmiss.e()*Pmiss.e()-Pmiss.rho()*Pmiss.rho();
m12=(Peta+Muvector[l]).m();
m13=(Peta+P_nu).m();
m23=(Muvector[l]+P_nu).m();

q2=(Muvector[l]+P_nu).m2();

muemc=Emcmu[l];
mudepth=Depthmu[l];


v4_6=Pivector[i];
v4_7=Pivector[j];
v4_8=Etavector[k];
v4_9=Muvector[l];
/////////all used ID
TotID.clear();
TotID=Dstid;
TotID.push_back(Piid[i]);
TotID.push_back(Piid[j]);
TotID.push_back(Etaid1[k]);
TotID.push_back(Etaid2[k]);
TotID.push_back(Muid[l]);
//////////

/////gamma or pi0 come from ST
KalmanKinematicFit * kmfit1 = KalmanKinematicFit::instance();
kmfit1->init();
kmfit1->setChisqCut(5000000);
kmfit1->AddTrack(0, wveta);
kmfit1->AddTrack(1, Trk_mu[l]);
kmfit1->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit1->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit1->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit1->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit1->AddTrack(7, 0.0,g_etap);
}
kmfit1->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit1->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(1, mDs, 4,5,6,7,8);

if(Tag_trk.size()==2)kmfit1->AddResonance(2, mDst, 3,4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(2, mDst, 3,4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(2, mDst, 3,4,5,6,7,8);
kmfit1->AddFourMomentum(3, ecms);
kmfit1->Fit();
double   kmfit_chi1=kmfit1->chisq();

HepLorentzVector v1_temp1=kmfit1->pfit(0);//eta
HepLorentzVector v2_temp1=kmfit1->pfit(1);//mu
HepLorentzVector v3_temp1=kmfit1->pfit(2);//nu


/////gamma or pi0 come from DT
KalmanKinematicFit * kmfit2 = KalmanKinematicFit::instance();
kmfit2->init();
kmfit2->setChisqCut(5000000);
kmfit2->AddTrack(0, wveta);
kmfit2->AddTrack(1, Trk_mu[l]);
kmfit2->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit2->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit2->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit2->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit2->AddTrack(7, 0.0,g_etap);
}
kmfit2->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit2->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit2->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit2->AddResonance(1, mDs, 4,5,6,7,8);

kmfit2->AddResonance(2, mDst, 0,1,2,3);
kmfit2->AddFourMomentum(3, ecms);
kmfit2->Fit();
double   kmfit_chi2=kmfit2->chisq();


HepLorentzVector v1_temp2=kmfit2->pfit(0);//eta
HepLorentzVector v2_temp2=kmfit2->pfit(1);//mu
HepLorentzVector v3_temp2=kmfit2->pfit(2);//nu


if(kmfit_chi1<kmfit_chi2){
V4_1ft=v1_temp1;//eta
V4_2ft=v2_temp1;//mu
V4_3ft=v3_temp1;//nv
sgmode=-1;
}
else{
V4_1ft=v1_temp2;//eta
V4_2ft=v2_temp2;//mu
V4_3ft=v3_temp2;//nv
sgmode=1;
}


mm2mft=V4_3ft.e()*V4_3ft.e()-V4_3ft.rho()*V4_3ft.rho();
m12ft=(V4_1ft+V4_2ft).m();
m13ft=(V4_1ft+V4_3ft).m();
m23ft=(V4_2ft+V4_3ft).m();

HepLorentzVector p_nu_temp=V4_3ft;
p_nu_temp.setE(V4_3ft.rho());
q2ft=(V4_2ft+p_nu_temp).m2();

if(kmfit_chi1>9999.&&kmfit_chi2>9999.){
mm2mft=mm2m;
m12ft=m12;
m13ft=m13;
m23ft=m23;
q2ft=q2;
}

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
}
eta.push_back(Etavector[k]);
mu.push_back(Muvector[l]);
TruthMatch.InputRec(tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle_rec=TruthMatch.match();
////
findsig=true;

}
}
}
}
}
}//recmode==2

if(recmode==3){//Ds -> etap(pi+ pi- gamma) mu nu

for(int i=0;i<pinumber;i++){
if(Picharge[i]!=tagcharge)continue;
for(int j=0;j<pinumber;j++){
if(Picharge[j]==tagcharge)continue;
for(int k=0;k<gamnumber;k++){
for(int l=0;l<munumber;l++){
if(Mucharge[l]!=tagcharge)continue;

Vint idtemp=Dstid;
idtemp.push_back(Piid[i]);
idtemp.push_back(Piid[j]);
idtemp.push_back(Gamid[k]);
idtemp.push_back(Muid[l]);
if(Same(idtemp))continue;

if((Pivector[i]+Pivector[j])<0.57||(Pivector[i]+Pivector[j]).m()>0.97)continue;
if((Pivector[i]+Pivector[j]+Gamvector[k])<0.94||(Pivector[i]+Pivector[j]+Gamvector[k]).m()>0.976)continue;

KalmanKinematicFit * kmfita = KalmanKinematicFit::instance();
kmfita->init();
kmfita->setChisqCut(50000);
kmfita->AddTrack(0, Trk_pi[i]);
kmfita->AddTrack(1, Trk_pi[j]);

RecEmcShower     *gam_rec=(*(evtRecTrkCol->begin() + Gamid[k]))->emcShower();
kmfita->AddTrack(2, 0.0,gam_rec);

kmfita->AddResonance(0, metap, 0, 1, 2);
if(!kmfita->Fit(0)) continue;
kmfita->BuildVirtualParticle(0);
WTrackParameter wveta = kmfita->wVirtualTrack(0);

HepLorentzVector PETA = kmfita->pfit(0)+kmfita->pfit(1)+kmfita->pfit(2);
PETA.boost(-0.011,0,0);
double Ft_chi=kmfita->chisq(0);


if(Ft_chi<=chicut){
chicut=Ft_chi;
HepLorentzVector Peta=Pivector[i]+Pivector[j]+Gamvector[k];
HepLorentzVector Pmiss=ECMS-Pgtag_final-Peta-Muvector[l]; 

HepLorentzVector P_nu = Pmiss;
P_nu.setE(Pmiss.rho());
P_nu.setRho(Pmiss.rho());
P_nu.setTheta(Pmiss.theta());
P_nu.setPhi(Pmiss.phi());
mm2m=Pmiss.e()*Pmiss.e()-Pmiss.rho()*Pmiss.rho();
m12=(Peta+Muvector[l]).m();
m13=(Peta+P_nu).m();
m23=(Muvector[l]+P_nu).m();

q2=(Muvector[l]+P_nu).m2();

muemc=Emcmu[l];
mudepth=Depthmu[l];


v4_6=Pivector[i];
v4_7=Pivector[j];
v4_8=Gamvector[k];
v4_9=Muvector[l];
/////////all used ID
TotID.clear();
TotID=Dstid;
TotID.push_back(Piid[i]);
TotID.push_back(Piid[j]);
TotID.push_back(Gamid[k]);
TotID.push_back(Muid[l]);
//////////

/////gamma or pi0 come from ST
KalmanKinematicFit * kmfit1 = KalmanKinematicFit::instance();
kmfit1->init();
kmfit1->setChisqCut(5000000);
kmfit1->AddTrack(0, wveta);
kmfit1->AddTrack(1, Trk_mu[l]);
kmfit1->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit1->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit1->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit1->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit1->AddTrack(7, 0.0,g_etap);
}
kmfit1->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit1->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(1, mDs, 4,5,6,7,8);

if(Tag_trk.size()==2)kmfit1->AddResonance(2, mDst, 3,4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit1->AddResonance(2, mDst, 3,4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==4)kmfit1->AddResonance(2, mDst, 3,4,5,6,7);
if(Tag_trk.size()==5)kmfit1->AddResonance(2, mDst, 3,4,5,6,7,8);
kmfit1->AddFourMomentum(3, ecms);
kmfit1->Fit();
double   kmfit_chi1=kmfit1->chisq();

HepLorentzVector v1_temp1=kmfit1->pfit(0);//eta
HepLorentzVector v2_temp1=kmfit1->pfit(1);//mu
HepLorentzVector v3_temp1=kmfit1->pfit(2);//nu


/////gamma or pi0 come from DT
KalmanKinematicFit * kmfit2 = KalmanKinematicFit::instance();
kmfit2->init();
kmfit2->setChisqCut(5000000);
kmfit2->AddTrack(0, wveta);
kmfit2->AddTrack(1, Trk_mu[l]);
kmfit2->AddMissTrack(2, Pmiss);
if(gamma_final<gamnumber){
RecEmcShower     *gDst_rec=(*(evtRecTrkCol->begin() + Gamid[gamma_final]))->emcShower();
kmfit2->AddTrack(3, 0.0,gDst_rec);
}
else{
kmfit2->AddTrack(3,Trk_pi0[gamma_final-gamnumber]);
}
for(int ntrk=0;ntrk<Tag_trk.size();ntrk++)kmfit2->AddTrack(4+ntrk,Tag_trk[ntrk]);
if(tagmode==13){
RecEmcShower     *g_etap=(*(evtRecTrkCol->begin() + tagid[3]))->emcShower();
kmfit2->AddTrack(7, 0.0,g_etap);
}
kmfit2->AddResonance(0, mDs, 0, 1,2);
if(Tag_trk.size()==2)kmfit2->AddResonance(1, mDs, 4,5);
if(Tag_trk.size()==3&&tagmode!=13)kmfit2->AddResonance(1, mDs, 4,5,6);
if(Tag_trk.size()==3&&tagmode==13)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==4)kmfit2->AddResonance(1, mDs, 4,5,6,7);
if(Tag_trk.size()==5)kmfit2->AddResonance(1, mDs, 4,5,6,7,8);

kmfit2->AddResonance(2, mDst, 0,1,2,3);
kmfit2->AddFourMomentum(3, ecms);
kmfit2->Fit();
double   kmfit_chi2=kmfit2->chisq();


HepLorentzVector v1_temp2=kmfit2->pfit(0);//eta
HepLorentzVector v2_temp2=kmfit2->pfit(1);//mu
HepLorentzVector v3_temp2=kmfit2->pfit(2);//nu


if(kmfit_chi1<kmfit_chi2){
V4_1ft=v1_temp1;//eta
V4_2ft=v2_temp1;//mu
V4_3ft=v3_temp1;//nv
sgmode=-1;
}
else{
V4_1ft=v1_temp2;//eta
V4_2ft=v2_temp2;//mu
V4_3ft=v3_temp2;//nv
sgmode=1;
}


mm2mft=V4_3ft.e()*V4_3ft.e()-V4_3ft.rho()*V4_3ft.rho();
m12ft=(V4_1ft+V4_2ft).m();
m13ft=(V4_1ft+V4_3ft).m();
m23ft=(V4_2ft+V4_3ft).m();

HepLorentzVector p_nu_temp=V4_3ft;
p_nu_temp.setE(V4_3ft.rho());
q2ft=(V4_2ft+p_nu_temp).m2();

if(kmfit_chi1>9999.&&kmfit_chi2>9999.){
mm2mft=mm2m;
m12ft=m12;
m13ft=m13;
m23ft=m23;
q2ft=q2;
}

///truth match
Vp4 ka;ka.clear();
Vp4 kb;kb.clear();
Vp4 pia;pia.clear();
Vp4 pib;pib.clear();
Vp4 gamma;gamma.clear();
Vp4 pi0;pi0.clear();
Vp4 eta;eta.clear();
Vp4 e;e.clear();
Vp4 mu;mu.clear();
if(tagcharge==1){
	pia.push_back(Pivector[i]);
	pib.push_back(Pivector[j]);
}
if(tagcharge==-1){
	pib.push_back(Pivector[i]);
	pia.push_back(Pivector[j]);
}
gamma.push_back(Gamvector[k]);
mu.push_back(Muvector[l]);
TruthMatch.InputRec(tagcharge,ka,kb,pia,pib,gamma,pi0,eta,e,mu);
maxangle_rec=TruthMatch.match();
////
findsig=true;

}
}
}
}
}
}//recmode==3

//
if(findsig){

/////extra pi0
int npi0=0; 
for(int x0=0;x0<pi0number;x0++){
bool tem1=false;
for(int tem=0;tem<TotID.size();tem++){
if(Pi0id1[x0]==TotID[tem]||Pi0id2[x0]==TotID[tem])tem1=true;
}
if(tem1)continue;
npi0++;
}
///// extra char
int nchar=0;
for(int x0=0;x0<nGood;x0++){
bool tem1=false;
	for(int tem=0;tem<TotID.size();tem++){
		if(iGood[x0]==TotID[tem])tem1=true;
	}
if(tem1)continue;
		nchar++;
}

/// extra gamma max/sum
double egammax=0,egamsum=0;
double gamcut=0;
for(int x0=0;x0<gamnumber;x0++){
bool tem1=false;
	for(int tem=0;tem<TotID.size();tem++){
		if(Gamid[x0]==TotID[tem])tem1=true;
	}
if(tem1)continue;
egamsum+=Gamvector[x0].e();
if(Gamvector[x0].e()>gamcut){
gamcut=Gamvector[x0].e();
egammax=Gamvector[x0].e();
}
}
////
if(gamma_final<gamnumber)gamorpi0_temp2=-1;
if(gamma_final>=gamnumber)gamorpi0_temp2=1;

    event_temp2             =         event;
      run_temp2             =         runNo;
  mcmode1_temp2             =       mcmode1;
  mcmode2_temp2             =       mcmode2;
  mcmodea_temp2             =       mcmodea;
  mcmodeb_temp2             =       mcmodeb;
tagcharge_temp2             =     tagcharge;
  tagmode_temp2             =       tagmode;
    mctag_temp2             =       m_mctag;
 Dstmode1_temp2             =      Dstmode1;
 Dstmode2_temp2             =      Dstmode2;
      ecm_temp2             =           ecm;

  recmode_temp2             =       recmode;
  maxangle_temp2            =  maxangle_rec;
  maxangle_tag_temp2        =      maxangle;
angle_Dst_temp2             =     angle_Dst;

  mDs_tag_temp2             =       mDs_tag;
  mBC_tag_temp2             =       mBC_tag;

     mm2m_temp2             =          mm2m;
      m12_temp2             =           m12;
      m13_temp2             =           m13;
      m14_temp2             =           m14;
      m23_temp2             =           m23;
      m24_temp2             =           m24;
      m34_temp2             =           m34;
     m123_temp2             =          m123;
     m124_temp2             =          m124;
     m134_temp2             =          m134;
     m234_temp2             =          m234;
       q2_temp2             =            q2;
     
   mm2mft_temp2             =        mm2mft;
    m12ft_temp2             =         m12ft;
    m13ft_temp2             =         m13ft;
    m14ft_temp2             =         m14ft;
    m23ft_temp2             =         m23ft;
    m24ft_temp2             =         m24ft;
    m34ft_temp2             =         m34ft;
   m123ft_temp2             =        m123ft;
   m124ft_temp2             =        m124ft;
   m134ft_temp2             =        m134ft;
   m234ft_temp2             =        m234ft;
     q2ft_temp2             =          q2ft;

 q2_truth_temp2             =      q2_truth;
    muemc_temp2             =         muemc;
  mudepth_temp2             =       mudepth;

extra_pi0_temp2             =          npi0;
extra_char_temp2            =         nchar;
  egammax_temp2             =       egammax;
  egamsum_temp2             =       egamsum;
  
     delE_temp2             =    delE_final;
   sgmode_temp2             =        sgmode;
/*
index_temp2             =             4;
V4_1_temp2[0]          =     v4_1.px();
V4_1_temp2[1]          =     v4_1.py();
V4_1_temp2[2]          =     v4_1.pz();
V4_1_temp2[3]          =      v4_1.e();

V4_2_temp2[0]          =     v4_2.px();
V4_2_temp2[1]          =     v4_2.py();
V4_2_temp2[2]          =     v4_2.pz();
V4_2_temp2[3]          =      v4_2.e();

V4_3_temp2[0]          =     v4_3.px();
V4_3_temp2[1]          =     v4_3.py();
V4_3_temp2[2]          =     v4_3.pz();
V4_3_temp2[3]          =      v4_3.e();

V4_4_temp2[0]          =     v4_4.px();
V4_4_temp2[1]          =     v4_4.py();
V4_4_temp2[2]          =     v4_4.pz();
V4_4_temp2[3]          =      v4_4.e();

V4_5_temp2[0]          =     v4_5.px();
V4_5_temp2[1]          =     v4_5.py();
V4_5_temp2[2]          =     v4_5.pz();
V4_5_temp2[3]          =      v4_5.e();

V4_6_temp2[0]          =     v4_6.px();
V4_6_temp2[1]          =     v4_6.py();
V4_6_temp2[2]          =     v4_6.pz();
V4_6_temp2[3]          =      v4_6.e();

V4_7_temp2[0]          =     v4_7.px();
V4_7_temp2[1]          =     v4_7.py();
V4_7_temp2[2]          =     v4_7.pz();
V4_7_temp2[3]          =      v4_7.e();

V4_8_temp2[0]          =     v4_8.px();
V4_8_temp2[1]          =     v4_8.py();
V4_8_temp2[2]          =     v4_8.pz();
V4_8_temp2[3]          =      v4_8.e();

V4_9_temp2[0]          =     v4_9.px();
V4_9_temp2[1]          =     v4_9.py();
V4_9_temp2[2]          =     v4_9.pz();
V4_9_temp2[3]          =      v4_9.e();

F4_1_temp2[0]          =     V4_1ft.px();
F4_1_temp2[1]          =     V4_1ft.py();
F4_1_temp2[2]          =     V4_1ft.pz();
F4_1_temp2[3]          =      V4_1ft.e();

F4_2_temp2[0]          =     V4_2ft.px();
F4_2_temp2[1]          =     V4_2ft.py();
F4_2_temp2[2]          =     V4_2ft.pz();
F4_2_temp2[3]          =      V4_2ft.e();

F4_3_temp2[0]          =     V4_3ft.px();
F4_3_temp2[1]          =     V4_3ft.py();
F4_3_temp2[2]          =     V4_3ft.pz();
F4_3_temp2[3]          =      V4_3ft.e();

F4_4_temp2[0]          =     V4_4ft.px();
F4_4_temp2[1]          =     V4_4ft.py();
F4_4_temp2[2]          =     V4_4ft.pz();
F4_4_temp2[3]          =      V4_4ft.e();
*/
m_tuple2->write();

}

}//recmode






}//tagmode
}//tagcharge

}//StatusCode Dstoetamv::execute()

void Dstoetamv::set0()
{
}

bool Dstoetamv::Same(Vint totid){
	bool tem=false;
	for(int i=0;i<totid.size()-1;i++){
		for(int j=i+1;j<totid.size();j++){
			if(totid[i]==totid[j])tem=true;
		}
	}
	return tem;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Dstoetamv::finalize() {
MsgStream log(msgSvc(), name());/////////////////////
log << MSG::INFO << "in finalize()" << endmsg;
  return StatusCode::SUCCESS;
}

