#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"



#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
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
#include "Xi_peeAlg/Xi_pee.h"
#include "McTruth/McParticle.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"
#include "VertexFit/SecondVertexFit.h"
#include <vector>
//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double mp  = 0.938272;
const double me  = 0.000511;
const double mlambda = 1.115683;
const double mXi = 1.32171;
const double mXi0 = 2.4709;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<WTrackParameter> Vwpar;

int Ncut0,Ncut1,Ncut2,Ncut3,Ncut4,Ncut5,Ncut6,Ncut7,Ncut8,Ncut9,Ncut10,Ncut11,Ncut12,Ncut13;

/////////////////////////////////////////////////////////////////////////////

Xi_pee::Xi_pee(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  
  //Declare the properties  
  declareProperty("Vr0cut", m_vr0cut=1.0);
  declareProperty("Vz0cut", m_vz0cut=10.0);
  declareProperty("Coscut", m_coscut=0.93);
  declareProperty("ecms",m_ecms = 3.097);
  declareProperty("beamangle",m_beamangle = 0.022);
  declareProperty("mpi0",mpi0 = 0.1349766);
  declareProperty("pi0chisq1ccut", m_pi0chisq1ccut=25.0);
  declareProperty("pi0MassWinHcut",m_pi0mhCut = 0.04);
  declareProperty("pi0MassWinLcut",m_pi0mlCut = 0.06);
  declareProperty("pi0decayanglecut", m_pi0decayanglecut=0.95);
  }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Xi_pee::initialize(){
	MsgStream log(msgSvc(), name());

	log << MSG::INFO << "in initialize()" << endmsg;

	StatusCode status;

	NTuplePtr nt0(ntupleSvc(), "FILE1/mctruth");
	if ( nt0 ) m_tuple0 = nt0;
	else {                  
		m_tuple0 = ntupleSvc()->book ("FILE1/mctruth", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple0 )    {
			status = m_tuple0->addItem ("costheta_sigma_m", m_truth_costheta_sigma_m);
			status = m_tuple0->addItem ("costheta_sigma_p", m_truth_costheta_sigma_p);
			status = m_tuple0->addItem ("costheta_sigma_m_boost", m_truth_costheta_sigma_m_boost);
			status = m_tuple0->addItem ("costheta_sigma_p_boost", m_truth_costheta_sigma_p_boost);
			status = m_tuple0->addItem ("truth_decaylength", m_truth_decaylength);
			status = m_tuple0->addItem ("ppx4" , 2, m_truth_ppx);
			status = m_tuple0->addItem ("ppy4" , 2, m_truth_ppy);
			status = m_tuple0->addItem ("ppz4" , 2, m_truth_ppz);
			status = m_tuple0->addItem ("pe4" ,  2, m_truth_pe);
			status = m_tuple0->addItem ("pipx4" , 2, m_truth_pipx);
			status = m_tuple0->addItem ("pipy4" , 2, m_truth_pipy);
			status = m_tuple0->addItem ("pipz4" , 2, m_truth_pipz);
			status = m_tuple0->addItem ("pie4" ,  2, m_truth_pie);



			status = m_tuple0->addItem ("truth_pip_p", m_truth_pip_p);
			status = m_tuple0->addItem ("truth_pim_p", m_truth_pim_p);
			status = m_tuple0->addItem ("truth_proton_p", m_truth_proton_p);
			status = m_tuple0->addItem ("truth_pbar_p", m_truth_pbar_p);

		}
		else    {       
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple0) << endmsg;
			return StatusCode::FAILURE;
		}
	}        		 




	NTuplePtr nt4(ntupleSvc(), "FILE1/lambda");
	if ( nt4 ) m_tuple4 = nt4;
	else {
		m_tuple4 = ntupleSvc()->book ("FILE1/lambda", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple4 )    {
			status = m_tuple4->addItem ("run",  m_run);
			status = m_tuple4->addItem ("rec",  m_rec);
			status = m_tuple4->addItem ("evttag",  m_evttag);

			status = m_tuple4->addItem ("type",  m_type);
			status = m_tuple4->addItem("indexmc",          m_idxmc, 0, 100);
			status = m_tuple4->addIndexedItem("trkidx",    m_idxmc, m_trkidx);  
			status = m_tuple4->addIndexedItem("pdgid",     m_idxmc, m_pdgid);
			status = m_tuple4->addIndexedItem("motheridx", m_idxmc, m_motheridx);    


			status = m_tuple4->addItem ("ngam" ,   m_ngam);//<=20
			status = m_tuple4->addItem ("npi0",    m_npi0,0,20*4);//ngam*4	

			status = m_tuple4->addIndexedItem ("mpi0" , m_npi0,  m_mpi0);
			status = m_tuple4->addIndexedItem ("chisq1cpi0" , m_npi0,  m_chisq1cpi0);
			status = m_tuple4->addIndexedItem ("ig1pi0" ,   m_npi0, m_ig1pi0);
			status = m_tuple4->addIndexedItem ("ig2pi0" ,   m_npi0, m_ig2pi0);

			status = m_tuple4->addItem ("ppx4" , 2, m_4cppx);
			status = m_tuple4->addItem ("ppy4" , 2, m_4cppy);
			status = m_tuple4->addItem ("ppz4" , 2, m_4cppz);
			status = m_tuple4->addItem ("pe4" ,  2, m_4cpe);

			status = m_tuple4->addItem ("pipx4" , 6, m_4cpipx);
			status = m_tuple4->addItem ("pipy4" , 6, m_4cpipy);
			status = m_tuple4->addItem ("pipz4" , 6, m_4cpipz);
			status = m_tuple4->addItem ("pie4" ,  6, m_4cpie);


			status = m_tuple4->addItem("lambda_px",2, m_4clambda_px);
			status = m_tuple4->addItem("lambda_py",2, m_4clambda_py);
			status = m_tuple4->addItem("lambda_pz",2, m_4clambda_pz);
			status = m_tuple4->addItem("lambda_e",2,  m_4clambda_e);

                        status = m_tuple4->addItem("Xi_px",2, m_4cXi_px);
                        status = m_tuple4->addItem("Xi_py",2, m_4cXi_py);
                        status = m_tuple4->addItem("Xi_pz",2, m_4cXi_pz);
                        status = m_tuple4->addItem("Xi_e",2,  m_4cXi_e);

                        status = m_tuple4->addItem("Xi0_px",2, m_4cXi0_px);
                        status = m_tuple4->addItem("Xi0_py",2, m_4cXi0_py);
                        status = m_tuple4->addItem("Xi0_pz",2, m_4cXi0_pz);
                        status = m_tuple4->addItem("Xi0_e",2,  m_4cXi0_e);

			status = m_tuple4->addItem ("chisq4c" ,  m_chisq4c);
			status = m_tuple4->addItem ("lambda_mass" ,   m_lambda_mass);
			status = m_tuple4->addItem ("lambda_ratio" ,  m_lambda_ratio);
			status = m_tuple4->addItem ("lambda_decayL" , m_lambda_decayL);
			status = m_tuple4->addItem ("lambdabar_mass",    m_lambdabar_mass);
			status = m_tuple4->addItem ("lambdabar_ratio" ,  m_lambdabar_ratio);
			status = m_tuple4->addItem ("lambdabar_decayL" , m_lambdabar_decayL);


			status = m_tuple4->addItem ("costheta_lambda" ,     m_costheta_lambda);
			status = m_tuple4->addItem ("costheta_lambdabar" ,  m_costheta_lambdabar);
			status = m_tuple4->addItem ("costheta_lambda_boost" ,     m_costheta_lambda_boost);
			status = m_tuple4->addItem ("costheta_lambdabar_boost" ,  m_costheta_lambdabar_boost);

                        status = m_tuple4->addItem ("Xi_mass" ,   m_Xi_mass);
                        status = m_tuple4->addItem ("Xi_ratio" ,  m_Xi_ratio);
                        status = m_tuple4->addItem ("Xi_decayL" , m_Xi_decayL);
                        status = m_tuple4->addItem ("Xibar_mass",    m_Xibar_mass);
                        status = m_tuple4->addItem ("Xibar_ratio" ,  m_Xibar_ratio);
                        status = m_tuple4->addItem ("Xibar_decayL" , m_Xibar_decayL);


                        status = m_tuple4->addItem ("costheta_Xi" ,     m_costheta_Xi);
                        status = m_tuple4->addItem ("costheta_Xibar" ,  m_costheta_Xibar);
                        status = m_tuple4->addItem ("costheta_Xi_boost" ,     m_costheta_Xi_boost);
                        status = m_tuple4->addItem ("costheta_Xibar_boost" ,  m_costheta_Xibar_boost);


                        status = m_tuple4->addItem ("Xi0_mass" ,   m_Xi0_mass);
                        status = m_tuple4->addItem ("Xi0_ratio" ,  m_Xi0_ratio);
                        status = m_tuple4->addItem ("Xi0_decayL" , m_Xi0_decayL);
                        status = m_tuple4->addItem ("Xi0bar_mass",    m_Xi0bar_mass);
                        status = m_tuple4->addItem ("Xi0bar_ratio" ,  m_Xi0bar_ratio);
                        status = m_tuple4->addItem ("Xi0bar_decayL" , m_Xi0bar_decayL);
                        status = m_tuple4->addItem ("tag_Xibar_mass" , m_tag_Xibar_mass);
			status = m_tuple4->addItem ("tag_Xibar_energy" , m_tag_Xibar_energy);
			status = m_tuple4->addItem ("tag_rec_Xibar_mass" , m_tag_rec_Xibar_mass);

                        status = m_tuple4->addItem ("costheta_Xi0" ,     m_costheta_Xi0);
                        status = m_tuple4->addItem ("costheta_Xi0bar" ,  m_costheta_Xi0bar);
                        status = m_tuple4->addItem ("costheta_Xi0_boost" ,     m_costheta_Xi0_boost);
                        status = m_tuple4->addItem ("costheta_Xi0bar_boost" ,  m_costheta_Xi0bar_boost);
			status = m_tuple4->addItem ("p_x" ,  m_p_x);
			status = m_tuple4->addItem ("p_y" ,  m_p_y);
			status = m_tuple4->addItem ("p_z" ,  m_p_z);
			status = m_tuple4->addItem ("pbar_x" ,  m_pbar_x);
			status = m_tuple4->addItem ("pbar_y" ,  m_pbar_y);
			status = m_tuple4->addItem ("pbar_z" ,  m_pbar_z);


			status = m_tuple4->addItem ("pppim_mass" ,   m_pppim_mass);
			status = m_tuple4->addItem ("pmpip_mass" ,   m_pmpip_mass);
                        status = m_tuple4->addItem ("lambdapim_mass" ,   m_lambdapim_mass);
                        status = m_tuple4->addItem ("lambdabarpip_mass" ,   m_lambdabarpip_mass);
                        status = m_tuple4->addItem ("Xipip_mass" ,   m_Xipip_mass);
                        status = m_tuple4->addItem ("Xibarpim_mass" ,   m_Xibarpim_mass);

		}
		else    {
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple4) << endmsg;
			return StatusCode::FAILURE;
		}
	}





	//
	//--------end of book--------
	//

	log << MSG::INFO << "successfully return from initialize()" <<endmsg;
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Xi_pee::execute() {
	//const HepLorentzVector p_cms(m_ecms*sin(m_beamangle*0.5),0.0,0.0,m_ecms);
	//	std::cout << "execute()" << std::endl;

	StatusCode sc=StatusCode::SUCCESS;
	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in execute()" << endreq;

	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
	int runNo=eventHeader->runNumber();
	int event=eventHeader->eventNumber();
	m_run = eventHeader->runNumber();
	m_rec = eventHeader->eventNumber();
	m_evttag=eventHeader->eventTag(); 


	log << MSG::DEBUG <<"run, evtnum = "
		<< runNo << " , "
		<< event <<endreq;
	Ncut0++;
	/*
	   int type = 999;
	   if(runNo>=28312&&runNo<=28346) type  = 1;
	   if(runNo>=28347&&runNo<=28381) type  = 2;
	   if(runNo>=28382&&runNo<=28387) type  = 3;
	   if(runNo>=28466&&runNo<=28469) type  = 3;
	   if(runNo>=28241&&runNo<=28266) type  = 4;
	   if(runNo>=28388&&runNo<=28416) type  = 5;
	   if(runNo>=28470&&runNo<=28475) type  = 5;
	   if(runNo>=28417&&runNo<=28453) type  = 6;
	   if(runNo>=28476&&runNo<=28478) type  = 6;
	   if(runNo>=28479&&runNo<=28482) type  = 7;
	   if(runNo>=28487&&runNo<=28489) type  = 8;
	   if(runNo>=28490&&runNo<=28492) type  = 9;
	   if(runNo>=28493&&runNo<=28495) type  = 10;
	   if(runNo>=28496&&runNo<=28498) type  = 11;
	   if(runNo>=28499&&runNo<=28503) type  = 12;
	   if(runNo>=28504&&runNo<=28505) type  = 13;
	   if(runNo>=28506&&runNo<=28509) type  = 14;
	   if(runNo>=28510&&runNo<=28511) type  = 15;
	   if(runNo>=28512&&runNo<=28513) type  = 16;


	   m_type = type;

	   if(type ==  1 )  m_ecms = 3.0500;
	   if(type ==  2 )  m_ecms = 3.0600;
	   if(type ==  3 )  m_ecms = 3.0830;
	   if(type ==  4 )  m_ecms = 3.0856;
	   if(type ==  5 )  m_ecms = 3.0900;
	   if(type ==  6 )  m_ecms = 3.0930;
	   if(type ==  7 )  m_ecms = 3.0943;
	   if(type ==  8 )  m_ecms = 3.0952;
	   if(type ==  9 )  m_ecms = 3.0958;
	   if(type ==  10)  m_ecms = 3.0969;
	   if(type ==  11)  m_ecms = 3.0982;
	   if(type ==  12)  m_ecms = 3.0990;
	   if(type ==  13)  m_ecms = 3.1015;
	   if(type ==  14)  m_ecms = 3.1055;
	   if(type ==  15)  m_ecms = 3.1120;
	   if(type ==  16)  m_ecms = 3.1200;

*/


	const HepLorentzVector p_cms(m_ecms*sin(m_beamangle*0.5),0.0,0.0,m_ecms);
	const Hep3Vector u_cms = -p_cms.boostVector(); 


	Vdouble vgamma_px, vgamma_py, vgamma_pz, vgamma_e;
	vgamma_px.clear();
	vgamma_py.clear();
	vgamma_pz.clear();
	vgamma_e.clear();
	if (eventHeader->runNumber()<0)
	{
		//MC information
		SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

		int m_numParticle = 0;
		if (!mcParticleCol)
		{
			std::cout << "Could not retrieve McParticelCol" << std::endl;
			return StatusCode::FAILURE;
		}

		bool psipDecay = false;
		int rootIndex = -1;

		Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
		HepLorentzVector g1_truth;
		HepLorentzVector g2_truth;
		bool bool_sigma_p, bool_sigma_m;
		bool_sigma_p = 0;
		bool_sigma_m = 0;

		for (; iter_mc != mcParticleCol->end(); iter_mc++)
		{
			HepLorentzVector  mctrue_track = (*iter_mc)->initialFourMomentum();
			HepLorentzVector mctrack_iniposition = (*iter_mc)->initialPosition();
			HepLorentzVector mctrack_finposition = (*iter_mc)->finalPosition();

			if ((*iter_mc)->primaryParticle()) continue;
			if (!(*iter_mc)->decayFromGenerator()) continue;
			int imom=443;
			if(m_ecms<3.2)imom=443;
			else if (m_ecms>3.6)imom=100443;
			if ((*iter_mc)->particleProperty()==imom)  
			{
				psipDecay = true;
				rootIndex = (*iter_mc)->trackIndex();

			}
			if (!psipDecay) continue;
			int trkidx = (*iter_mc)->trackIndex() - rootIndex; 
			int mcidxi=(*iter_mc)->trackIndex() - rootIndex;	
			int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
			int pdgid = (*iter_mc)->particleProperty();
			m_trkidx[m_numParticle] = trkidx;
			m_pdgid[m_numParticle] = pdgid;
			m_motheridx[m_numParticle] = mcidx;
			m_numParticle += 1;

			if((*iter_mc)->particleProperty() == 211) {	
				m_truth_pipx[0] = mctrue_track.px();
				m_truth_pipy[0] = mctrue_track.py();
				m_truth_pipz[0] = mctrue_track.pz();
				m_truth_pie[0] = mctrue_track.e();	
				m_truth_pip_p = mctrue_track.rho();
			}
			if((*iter_mc)->particleProperty() == -211) {
				m_truth_pipx[1] = mctrue_track.px();
				m_truth_pipy[1] = mctrue_track.py();
				m_truth_pipz[1] = mctrue_track.pz();
				m_truth_pie[1] = mctrue_track.e();	
				m_truth_pim_p = mctrue_track.rho();
			}
			if((*iter_mc)->particleProperty() == 2212) {
				m_truth_ppx[0] = mctrue_track.px();
				m_truth_ppy[0] = mctrue_track.py();
				m_truth_ppz[0] = mctrue_track.pz();
				m_truth_pe[0] = mctrue_track.e();	
				m_truth_proton_p = mctrue_track.rho();
			}
			if((*iter_mc)->particleProperty() == -2212){
				m_truth_ppx[1] = mctrue_track.px();
				m_truth_ppy[1] = mctrue_track.py();
				m_truth_ppz[1] = mctrue_track.pz();
				m_truth_pe[1] = mctrue_track.e();	
				m_truth_pbar_p = mctrue_track.rho();
			}

			//			if(((*iter_mc)->particleProperty() == 3222)&&(((*iter_mc)->mother()).particleProperty()==imom) ) {
			//				m_truth_costheta_sigma_p = mctrue_track.cosTheta();
			//				m_truth_sigma_px[0] = mctrue_track.px();
			//				m_truth_sigma_py[0] = mctrue_track.py();
			//				m_truth_sigma_pz[0] = mctrue_track.pz();
			//				m_truth_sigma_e[0] = mctrue_track.e();
			//				HepLorentzVector truth_sigma_p = mctrue_track;	
			//				HepLorentzVector boost_truth_sigma_p = truth_sigma_p.boost(u_cms);
			//				m_truth_costheta_sigma_p_boost = boost_truth_sigma_p.cosTheta();
			//				bool_sigma_p = 1;
			//				//m_truth_decaylength = (mctrack_finposition -  mctrack_iniposition).rho();
			//			}
			//			if(((*iter_mc)->particleProperty() == -3222)&&(((*iter_mc)->mother()).particleProperty()==imom) )  {
			//				m_truth_costheta_sigma_m = mctrue_track.cosTheta();
			//				m_truth_sigma_px[1] = mctrue_track.px();
			//				m_truth_sigma_py[1] = mctrue_track.py();
			//				m_truth_sigma_pz[1] = mctrue_track.pz();
			//				m_truth_sigma_e[1] = mctrue_track.e();
			//				HepLorentzVector truth_sigma_m = mctrue_track;	
			//				HepLorentzVector boost_truth_sigma_m = truth_sigma_m.boost(u_cms);
			//				m_truth_costheta_sigma_m_boost = boost_truth_sigma_m.cosTheta();
			//				bool_sigma_m = 1;
			//			}
			//
			//			if((*iter_mc)->particleProperty() == 2212) {
			//				m_truth_decaylength = mctrack_iniposition.rho();	
			//				m_truth_ppx[0] = mctrue_track.px();
			//				m_truth_ppy[0] = mctrue_track.py();
			//				m_truth_ppz[0] = mctrue_track.pz();
			//				m_truth_pe[0] = mctrue_track.e();
			//
			//			}
			//
			//			if((*iter_mc)->particleProperty() == -2212) {
			//				m_truth_ppx[1] = mctrue_track.px();
			//				m_truth_ppy[1] = mctrue_track.py();
			//				m_truth_ppz[1] = mctrue_track.pz();
			//				m_truth_pe[1] = mctrue_track.e();
			//
			//			}
			//			if(((*iter_mc)->particleProperty() == 22) && (((*iter_mc)->mother()).particleProperty()==111)) {
			//				vgamma_px.push_back(mctrue_track.px());     
			//				vgamma_py.push_back(mctrue_track.py());     
			//				vgamma_pz.push_back(mctrue_track.pz());     
			//				vgamma_e.push_back(mctrue_track.e());     
			//
			//			}
		}
		m_tuple0->write();
		//		if(bool_sigma_p && bool_sigma_m) m_tuple0->write(); 
		m_idxmc = m_numParticle;

	}





	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	//  log << MSG::INFO << "get event tag OK" << endreq;
	log << MSG::DEBUG <<"ncharg, nneu, tottks = " 
		<< evtRecEvent->totalCharged() << " , "
		<< evtRecEvent->totalNeutral() << " , "
		<< evtRecEvent->totalTracks() <<endreq;

	SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
	//
	// check x0, y0, z0, r0
	// suggest cut: |z0|<5 && r0<1
	//
	Vint iGood, ipip, ipim, ipp, ipm, iep, iem;
	iGood.clear();
	ipip.clear();
	ipim.clear();
	ipp.clear();
	ipm.clear();
	int nCharge = 0;

	HepPoint3D vx(0., 0., 0.);
	HepSymMatrix Evx(3, 0);
	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid()){
		double* dbv = vtxsvc->PrimaryVertex(); 
		double*  vv = vtxsvc->SigmaPrimaryVertex(); 
		//  if (m_reader.isRunNumberValid( m_run)) {
		//   HepVector dbv = m_reader.PrimaryVertex( m_run);
		//    HepVector vv = m_reader.SigmaPrimaryVertex( m_run);
		vx.setX(dbv[0]);
		vx.setY(dbv[1]);
		vx.setZ(dbv[2]);
		Evx[0][0]=vv[0]*vv[0];
		//		Evx[0][1]=vv[0]*vv[1];
		Evx[1][1]=vv[1]*vv[1];
		//		Evx[1][2]=vv[1]*vv[2];
		Evx[2][2]=vv[2]*vv[2];
	}
	VertexParameter vx_db;
	vx_db.setVx(vx);
	vx_db.setEvx(Evx);








	for(int i = 0; i < evtRecEvent->totalCharged(); i++){
		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isMdcTrackValid()) continue;
		RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
		double pch=mdcTrk->p();
		double x0=mdcTrk->x();
		double y0=mdcTrk->y();
		double z0=mdcTrk->z();
		double phi0=mdcTrk->helix(1);
		double xv=vx.x();
		double yv=vx.y();
		double zv=vx.z();
		double Rxy=(x0-xv)*cos(phi0)+(y0-yv)*sin(phi0);
		HepVector a = mdcTrk->helix();
		HepSymMatrix Ea = mdcTrk->err();
		HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
		HepPoint3D IP(xv, yv, zv); 
		VFHelix helixip(point0,a,Ea); 
		helixip.pivot(IP);
		HepVector vecipa = helixip.a();
		double  Rvxy0=vecipa[0];  //the nearest distance to IP in xy plane
		double  Rvz0=vecipa[3];         //the nearest distance to IP in z direction
		double  Rvphi0=vecipa[1];

		if(pch > 2.0) continue;	
		double cost = cos(mdcTrk->theta());
		if(fabs(cost) >= m_coscut) continue;
			if(fabs(Rvz0) >= 20.0) continue;      //change by Liang 2018.2 to make the consistence with bes3 common selections
		//	if(fabs(Rvxy0) >= 2.0) continue;

		iGood.push_back(i);
		nCharge += mdcTrk->charge();
	}

	//
	// Finish Good Charged Track Selection
	//
	int nGood = iGood.size();
	log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;
	if(nGood < 3 ){
		return StatusCode::SUCCESS;
	}
	Ncut1++;


	Vwpar Vwv_pip, Vwv_pim, Vwv_proton, Vwv_pbar,Vwv_pim_Xi,Vwv_pip_Xibar,Vwv_pip_Xi0,Vwv_pim_Xi0bar;

	Vwv_pip.clear();
	Vwv_pim.clear();
	Vwv_proton.clear();
	Vwv_pbar.clear();
	Vwv_pim_Xi.clear();
	Vwv_pip_Xibar.clear();
	Vwv_pip_Xi0.clear();
	Vwv_pim_Xi0bar.clear();

	ipip.clear();
	ipim.clear();
	ipp.clear();
	ipm.clear();
        iep.clear();
        iem.clear();

	/*
	for(int i = 0; i < nGood; i++) {
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
		RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack();
		if(!((*itTrk)->isMdcKalTrackValid())) continue;
		if(!(*itTrk)->isMdcTrackValid()) continue;
		if(mdcTrk->charge() >0) {
			if(mdcTrk->p()<0.6){
				ipip.push_back(iGood[i]);
			}else if (mdcTrk->p() > 0.8) {
				ipp.push_back(iGood[i]);
			}
		}
		else {
			if(mdcTrk->p()<0.6){
				ipim.push_back(iGood[i]);
			}else if (mdcTrk->p() > 0.8) {
				ipm.push_back(iGood[i]);
			}
		}
	///////////////pid/////
	



	}

	*/

        ParticleID *pid = ParticleID::instance();

        for(int i = 0; i < nGood; i++) {
                EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
                RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack();//After ParticleID, use RecMdcKalTrack substitute RecMdcTrack
                pid->init();
                pid->setMethod(pid->methodProbability());
                pid->setChiMinCut(4);
                pid->setRecTrack(*itTrk);
                pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTofE()); // use PID sub-system
                pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
                pid->calculate();
                if(!(pid->IsPidInfoValid())) continue;
                if((pid->probProton() > pid->probPion()) && (pid->probProton() > pid->probElectron()) ) {
                        if(mdcTrk->charge() >0) {
                                ipp.push_back(iGood[i]);

                        } else {
                                ipm.push_back(iGood[i]);

                        }
                }
                if((pid->probProton() < pid->probPion()) && (pid->probPion() > pid->probElectron()) ) {
                        if(mdcTrk->charge() >0) {
                                ipip.push_back(iGood[i]);

                        } else {
                                ipim.push_back(iGood[i]);

                        }
                }
                

                if((pid->probElectron() > pid->probProton()) && (pid->probElectron() > pid->probPion()) ) {
                        if(mdcTrk->charge() >0) {
                                iep.push_back(iGood[i]);

                        } else {
                                iem.push_back(iGood[i]);

                        }
                }
        }




	int npip = ipip.size();
	int npim = ipim.size();
	int npp = ipp.size();
	int npm = ipm.size();
        int nep = iep.size();
        int nem = iem.size();
	if(npip < 2) return sc;
	//if(npim < 3) return sc;
	//if(npp < 1)  return sc;
	if(npm < 1)  return sc;

	Ncut2++;

	//
	// Xi_peebar candidates
	//
	int nlambdabar = 0;
	Vwpar wv_lambdabar;
        //WTrackParameter wlambdabar;
	wv_lambdabar.clear();
        Vwpar  wlambdabar;
	wlambdabar.clear();

	Vdouble v_ratio_lambdabar;
	Vdouble v_decayL_lambdabar;
	Vdouble v_mass_lambdabar;

	v_ratio_lambdabar.clear();
	v_decayL_lambdabar.clear();
	v_mass_lambdabar.clear();

	Vint id_pbar, id_pip;
	id_pbar.clear();
	id_pip.clear();
	for (int i = 0; i < npm; i++) {
		RecMdcKalTrack *pbarTrk;
		pbarTrk = (*(evtRecTrkCol->begin()+ipm[i]))->mdcKalTrack();
		WTrackParameter wv_pbar = WTrackParameter(mp, pbarTrk->getZHelixP(),  pbarTrk->getZErrorP());
		for (int j = 0; j < npip; j++) {
			RecMdcKalTrack *pipTrk;
			pipTrk = (*(evtRecTrkCol->begin()+ipip[j]))->mdcKalTrack();
			WTrackParameter wv_pip = WTrackParameter(mpi, pipTrk->getZHelix(),  pipTrk->getZError());
			HepPoint3D vx_lambda(0., 0., 0.);
			HepSymMatrix Evx_lambda(3, 0);
			double bx = 1E+6;
			double by = 1E+6;
			double bz = 1E+6;
			Evx_lambda[0][0] = bx*bx;
			Evx_lambda[1][1] = by*by;
			Evx_lambda[2][2] = bz*bz;
			VertexParameter vxpar;
			vxpar.setVx(vx_lambda);
			vxpar.setEvx(Evx_lambda);	

			VertexFit *vtxfit0 = VertexFit::instance();
			vtxfit0->init();
			vtxfit0->AddTrack(0,wv_pip);
			vtxfit0->AddTrack(1,wv_pbar);
			vtxfit0->AddVertex(0, vxpar, 0, 1);
			if((vtxfit0->Fit(0))) {
				vtxfit0->Swim(0);
				vtxfit0->BuildVirtualParticle(0);
				wlambdabar.push_back(vtxfit0->wVirtualTrack(0));
				VertexParameter vtx_lambdabar = vtxfit0->vpar(0);
				//SecondVertexFit *vtxfit = SecondVertexFit::instance();
				//vtxfit->init();
				//vtxfit->setPrimaryVertex(vx_db); //we use run vertex information instead of events
				//vtxfit->AddTrack(0,wlambdabar);
				//vtxfit->setVpar(vtx_lambdabar);

				//if(vtxfit->Fit()) {
					//double mass = vtxfit0->p4par().m();
					//double ratio = vtxfit0->decayLength()/vtxfit0->decayLengthError();
					//double decayL = vtxfit0->decayLength();
					//double wlambdabar_final = vtxfit0->wVirtualTrack(0);
					// wlambda = vtxfit->wpar();

					//wv_lambdabar.push_back(vtxfit0->wpar());
					//    m_lambda_mass = mass;
					//v_mass_lambdabar.push_back(mass);
					//    m_lambda_ratio = ratio;
					//v_ratio_lambdabar.push_back(ratio);
					//    m_lambda_decayL = decayL;
					//v_decayL_lambdabar.push_back(decayL);
					id_pbar.push_back(i);
					id_pip.push_back(j);
					Vwv_pbar.push_back(wv_pbar);
					Vwv_pip.push_back(wv_pip);
					nlambdabar++;
					
				//}
			}

		} //pim loop
	} //proton loop	

	cout<<"nlambdabar="<<nlambdabar<<endl;
	if(nlambdabar < 1) return SUCCESS;

	Ncut4++;


	int id_lambda = -1;
	int id_lambdabar = -1;

	double cut_diff = 999.0;

	//for(int i = 0; i < nlambda; i++){
		for(int j = 0; j < nlambdabar; j++){
			//double diff_lambda_mass = fabs((wv_lambda[i].p()).m() - mlambda);
			double diff_lambdabar_mass = fabs((wlambdabar[j]).p().m() - mlambda);
			double tmp_total_diff =  diff_lambdabar_mass;
			if(tmp_total_diff < cut_diff) {
				cut_diff = tmp_total_diff;
				//id_lambda = i;
				id_lambdabar = j;

			}

		}
	//}

	//if(id_lambda == -1) return sc;
	if(id_lambdabar == -1) return sc;

	Ncut5++;

	//	WTrackParameter wproton = wv_proton[id_proton[id_lambda]];
	//	WTrackParameter wpim    = wv_pim[id_pim[id_lambda]];
	//	WTrackParameter wpbar   = wv_pbar[id_pbar[id_lambdabar]];
	//	WTrackParameter wpip    = wv_pip[id_pip[id_lambdabar]];

//////////////////////////////////////////////Xi-bar reconstruction/////////////////////////////////
  int nXibar = 0;
  Vwpar wv_Xibar;
  wv_Xibar.clear();

  Vdouble v_ratio_Xibar;
  Vdouble v_decayL_Xibar;
  Vdouble v_mass_Xibar;

  v_ratio_Xibar.clear();
  v_decayL_Xibar.clear();
  v_mass_Xibar.clear();

  Vint id_proton_Xibar, id_pip_Xibar;
  id_proton_Xibar.clear();
  id_pip_Xibar.clear();

  RecMdcKalTrack *pbarTrk_2;
  pbarTrk_2 = (*(evtRecTrkCol->begin()+ipm[id_pbar[id_lambdabar]]))->mdcKalTrack();
  WTrackParameter wv_pbar_2 = WTrackParameter(mp, pbarTrk_2->getZHelixP(),  pbarTrk_2->getZErrorP());
  RecMdcKalTrack *pipTrk_2;
  pipTrk_2 = (*(evtRecTrkCol->begin()+ipip[id_pip[id_lambdabar]]))->mdcKalTrack();
  WTrackParameter wv_pip_2 = WTrackParameter(mpi, pipTrk_2->getZHelix(),  pipTrk_2->getZError());

  HepPoint3D vx_lam(0., 0., 0.);
  HepSymMatrix Evx_lam(3, 0);
  double bx = 1E+6;
  double by = 1E+6;
  double bz = 1E+6;
  Evx_lam[0][0] = bx*bx;
  Evx_lam[1][1] = by*by;
  Evx_lam[2][2] = bz*bz;

  VertexParameter vxpar;
  vxpar.setVx(vx_lam);
  vxpar.setEvx(Evx_lam);

  VertexFit *vtxfit_2 = VertexFit::instance();
  vtxfit_2->init();
  vtxfit_2->AddTrack(0,wv_pip_2 );
  vtxfit_2->AddTrack(1,wv_pbar_2);
  vtxfit_2->AddVertex(0, vxpar, 0, 1);
  if(!vtxfit_2->Fit(0)) return SUCCESS;
  vtxfit_2->Swim(0);
  vtxfit_2->BuildVirtualParticle(0);
  WTrackParameter wlambdabar_2 = vtxfit_2->wVirtualTrack(0);
  VertexParameter vtxlambdabar_2 = vtxfit_2->vpar(0);
  WTrackParameter wtrkpion1_2 = vtxfit_2->wtrk(0);



  for (int j = 0; j < npip; j++) {
      RecMdcKalTrack *pipTrk;
      pipTrk = (*(evtRecTrkCol->begin()+ipip[j]))->mdcKalTrack();
      WTrackParameter wv_pip = WTrackParameter(mpi, pipTrk->getZHelix(),  pipTrk->getZError());

      HepPoint3D vx_Xi(0., 0., 0.);
      HepSymMatrix Evx_Xi(3, 0);
      double bx = 1E+6;
      double by = 1E+6;
      double bz = 1E+6;
      Evx_Xi[0][0] = bx*bx;
      Evx_Xi[1][1] = by*by;
      Evx_Xi[2][2] = bz*bz;
      VertexParameter vxpar;
      vxpar.setVx(vx_Xi);
      vxpar.setEvx(Evx_Xi);


      VertexFit *vtxfit0 = VertexFit::instance();
      vtxfit0->init();
      vtxfit0->AddTrack(0,wv_pip);
      vtxfit0->AddTrack(1,wlambdabar_2);
      vtxfit0->AddVertex(0, vxpar, 0, 1);
      if((vtxfit0->Fit(0))) {
          vtxfit0->Swim(0);
          vtxfit0->BuildVirtualParticle(0);
          WTrackParameter wXibar = vtxfit0->wVirtualTrack(0);
          VertexParameter vtx_Xibar = vtxfit0->vpar(0);
          SecondVertexFit *vtxfitbar = SecondVertexFit::instance();
          vtxfitbar->init();
          vtxfitbar->setPrimaryVertex(vx_db); //we use run vertex information instead of events
          vtxfitbar->AddTrack(0,wXibar);
          vtxfitbar->setVpar(vtx_Xibar);

          if(vtxfitbar->Fit()) {
              double mass_Xibar = vtxfitbar->p4par().m();
              double ratio_Xibar = vtxfitbar->decayLength()/vtxfitbar->decayLengthError();
              double decayL_Xibar = vtxfitbar->decayLength();
              wv_Xibar.push_back(vtxfitbar->wpar());
              v_mass_Xibar.push_back(mass_Xibar);
              v_ratio_Xibar.push_back(ratio_Xibar);
              v_decayL_Xibar.push_back(decayL_Xibar);
              id_pip_Xibar.push_back(j);
              Vwv_pip_Xibar.push_back(wv_pip);
              nXibar++;
          }
      }

  } //pip loop

  if(nXibar < 1) return SUCCESS;
  Ncut7++;

  int id_Xi = -1;
  int id_Xibar = -1;

  double cut_diff_2 = 999.0;


  //for(int i = 0; i < nXi; i++){
  for(int j = 0; j < nXibar; j++){
      //double diff_Xi_mass = fabs((wv_Xi[i].p()).m() - mXi);
      double diff_Xibar_mass = fabs((wv_Xibar[j]).p().m() - mXi);
      double tmp_total_diff =  diff_Xibar_mass;
      if(tmp_total_diff < cut_diff_2) {
          cut_diff_2 = tmp_total_diff;
          //id_Xi = i;
          id_Xibar = j;

      }

  }
  //}
  //if(id_Xi == -1) return sc;
  if(id_Xibar == -1) return sc;

  m_tag_Xibar_mass = (wv_Xibar[id_Xibar].p()).m();
  m_tag_Xibar_energy = (wv_Xibar[id_Xibar].p()).e();
  m_tag_rec_Xibar_mass = (p_cms - wv_Xibar[id_Xibar].p()).m(); 
  Ncut8++;

  double chisq=999.0;
  double chisq6c=999.0;

  RecMdcKalTrack *em_KalTrk;
  RecMdcKalTrack *em2_KalTrk;
  RecMdcKalTrack *pp_KalTrk;

  WTrackParameter wpp;
  WTrackParameter wem;
  WTrackParameter wem2;

  WTrackParameter wpp_final;
  WTrackParameter wem_final;
  WTrackParameter wem2_final;
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  KalmanKinematicFit* kmfit = KalmanKinematicFit::instance();
  for (int i=0; i<nem-1; i++) {
      if(nem<2) break;
      for(int j=i+1; j<nem; j++){
          em_KalTrk = (*(evtRecTrkCol->begin()+iem[i]))->mdcKalTrack();
          wem = WTrackParameter(me,em_KalTrk->getZHelixE(),em_KalTrk->getZErrorE());
          em2_KalTrk = (*(evtRecTrkCol->begin()+iem[j]))->mdcKalTrack();
          wem2 = WTrackParameter(me,em2_KalTrk->getZHelixE(),em2_KalTrk->getZErrorE());
          for(int k=0;k<npp;k++){
              if(npp<1) break;
              pp_KalTrk = (*(evtRecTrkCol->begin()+ipp[k]))->mdcKalTrack();
              wpp = WTrackParameter(mp,pp_KalTrk->getZHelixP(),pp_KalTrk->getZErrorP());

              kmfit->init();
              kmfit->setBeamPosition(vx);
              kmfit->setVBeamPosition(Evx);

              kmfit->AddTrack(0, wem);
              kmfit->AddTrack(1, wem2);
              kmfit->AddTrack(2, wpp);
              kmfit->AddTrack(3, wv_Xibar[id_Xibar]);
              kmfit->AddFourMomentum(0, p_cms);
              kmfit->AddResonance(1, 1.3217, 0, 1,2);

              bool oksq_4 = kmfit->Fit();

              if(oksq_4){
                  double chi2 = kmfit->chisq();
                  if(chi2 < chisq) {
                      chisq = chi2;
                      wem_final = wem;
                      wem2_final = wem2;
                      wpp_final = wpp;
                  }
              }
          }
      }
  }

  if(chisq < chisq6c) {
      kmfit->init();
      kmfit->setBeamPosition(vx);
      kmfit->setVBeamPosition(Evx);
      kmfit->AddTrack(0, wem_final);
      kmfit->AddTrack(1, wem2_final);
      kmfit->AddTrack(2, wpp_final);
      kmfit->AddTrack(3, wv_Xibar[id_Xibar]);
      kmfit->AddFourMomentum(0, p_cms);
      kmfit->AddResonance(1, 1.3217, 0, 1,2);
      Ncut12++;
      m_chisq4c = kmfit->chisq();
      //HepLorentzVector p4proton = Vwv_proton[id_lambda].p();
      //HepLorentzVector p4pim = Vwv_pim[id_lambda].p();
      HepLorentzVector p4pbar = Vwv_pbar[id_lambdabar].p();
      HepLorentzVector p4pip = Vwv_pip[id_lambdabar].p();

      //HepLorentzVector p4pim_Xi = Vwv_pim[id_Xi].p();
      HepLorentzVector p4pip_Xibar = Vwv_pip[id_Xibar].p();
      //HepLorentzVector p4pip_Xi = Vwv_pip[id_Xi].p();
      //HepLorentzVector p4pim_Xibar = Vwv_pim[id_Xibar].p();

      //		HepLorentzVector p4proton = kmfit->pfit(0);
      //		HepLorentzVector p4pim = kmfit->pfit(1);
      //		HepLorentzVector p4pbar = kmfit->pfit(2);
      //		HepLorentzVector p4pip = kmfit->pfit(3);

      //HepLorentzVector p4_lambda;
      HepLorentzVector p4_lambdabar;

      //p4_lambda = p4proton + p4pim;
      p4_lambdabar = p4pbar + p4pip;

      //		p4_lambda   =  kmfit->pfit(0);
      //		p4_lambdabar = kmfit->pfit(1);
      //m_costheta_lambda = p4_lambda.cosTheta();
      m_costheta_lambdabar = p4_lambdabar.cosTheta();

      //m_pppim_mass = p4_lambda.m();
      m_pmpip_mass = p4_lambdabar.m();

      //m_lambda_mass = kmfit->pfit(0).m();
      //m_lambda_ratio = v_ratio_lambda[id_lambda];
      //m_lambda_decayL = v_decayL_lambda[id_lambda];

      m_lambdabar_mass = kmfit->pfit(1).m();
      //m_lambdabar_ratio = v_ratio_lambdabar[id_lambdabar];
      //m_lambdabar_decayL = v_decayL_lambdabar[id_lambdabar];


      //m_4clambda_px[0] = p4_lambda.px();
      //m_4clambda_py[0] = p4_lambda.py();
      //m_4clambda_pz[0] = p4_lambda.pz();
      //m_4clambda_e[0] =  p4_lambda.e();

      m_4clambda_px[0] = p4_lambdabar.px();
      m_4clambda_py[0] = p4_lambdabar.py();
      m_4clambda_pz[0] = p4_lambdabar.pz();
      m_4clambda_e[0] =  p4_lambdabar.e();


      //HepLorentzVector boost_lambda = p4_lambda.boost(u_cms);
      HepLorentzVector boost_lambdabar = p4_lambdabar.boost(u_cms);

      //m_costheta_lambda_boost = boost_lambda.cosTheta();
      m_costheta_lambdabar_boost = boost_lambdabar.cosTheta();

      //////////////////////////////////////////Xi/////////////////////////////////////////////
      HepLorentzVector p4_Xi = kmfit->pfit(0)+kmfit->pfit(1)+kmfit->pfit(2);
      HepLorentzVector p4_Xibar = kmfit->pfit(3);

      //p4_Xi = p4proton + p4pim;
      p4_Xibar = p4pbar + p4pip;
      //m_costheta_Xi = p4_Xi.cosTheta();
      m_costheta_Xibar = p4_Xibar.cosTheta();

      //m_lambdapim_mass = p4_Xi.m();
      m_lambdabarpip_mass = p4_Xibar.m();

      m_Xi_mass = (kmfit->pfit(0)+kmfit->pfit(1)+kmfit->pfit(2)).m();
      //m_Xi_ratio = v_ratio_Xi[id_Xi];
      //m_Xi_decayL = v_decayL_Xi[id_Xi];

      m_Xibar_mass = kmfit->pfit(3).m();
      m_Xibar_ratio = v_ratio_Xibar[id_Xibar];
      m_Xibar_decayL = v_decayL_Xibar[id_Xibar];


      m_4cXi_px[0] = p4_Xi.px();
      m_4cXi_py[0] = p4_Xi.py();
      m_4cXi_pz[0] = p4_Xi.pz();
      m_4cXi_e[0] =  p4_Xi.e();

      m_4cXi_px[1] = p4_Xibar.px();
      m_4cXi_py[1] = p4_Xibar.py();
      m_4cXi_pz[1] = p4_Xibar.pz();
      m_4cXi_e[1] =  p4_Xibar.e();


      HepLorentzVector boost_Xi = p4_Xi.boost(u_cms);
      HepLorentzVector boost_Xibar = p4_Xibar.boost(u_cms);

      m_costheta_Xi_boost = boost_Xi.cosTheta();
      m_costheta_Xibar_boost = boost_Xibar.cosTheta();




      //m_tuple4->write();
  }  //oksq
  m_tuple4->write();

  return StatusCode::SUCCESS;
  }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	StatusCode Xi_pee::finalize() {
		MsgStream log(msgSvc(), name());
		cout<<"total number:          "<<Ncut0<<endl;
		cout<<"nGood>=3,              "<<Ncut1<<endl;
		cout<<"pid                    "<<Ncut2<<endl;
	//	cout<<"Xi_pee                 "<<Ncut3<<endl;
		cout<<"rec lambdabar          "<<Ncut4<<endl;
		cout<<"select lambdabar       "<<Ncut5<<endl;
                cout<<"rec Xibar              "<<Ncut7<<endl;
             // cout<<"Xibar                  "<<Ncut7<<endl;
                cout<<"select Xibar           "<<Ncut8<<endl;
             //   cout<<"Xi0                    "<<Ncut9<<endl;
             //   cout<<"Xi0bar                 "<<Ncut10<<endl;
               // cout<<"LL_3 candidates        "<<Ncut11<<endl;
		cout<<"fit after kinematic:   "<<Ncut12<<endl;
                cout<<"code_v2:   "<<endl;
		log << MSG::INFO << "in finalize()" << endmsg;
		return StatusCode::SUCCESS;
	}

