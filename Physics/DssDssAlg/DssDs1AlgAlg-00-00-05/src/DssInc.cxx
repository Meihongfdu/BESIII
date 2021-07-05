#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"

#include "McTruth/McParticle.h"
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
typedef HepGeom::Point3D < double >HepPoint3D;
#endif
#include "DssDs1Alg/DssInc.h"
#include "DssDs1Alg/PullCorrection.h"
#include "BeamEnergy.h"
#include "DssDs1Alg/RscanDQ.h"
#include "DssDs1Alg/HelAng.h"

//#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include <vector>
const double PI = 3.1415927;
const double xmass[5] = { 0.000511, 0.105658, 0.139570, 0.493677, 0.938272 };
const double mDs = 1.9685;
const double mDss = 2.1123;
const double mDss2 = 2.3178;
const double mDs1 = 2.4596;
const double mPi0 = 0.1349766;

//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;	// tof path unit in mm
typedef std::vector < int >Vint;
typedef std::vector < double >Vdouble;
typedef std::vector < HepLorentzVector > Vp4;

long Ncutm0, Ncutm1, Ncutm2, Ncutm3, Ncutm4, Ncutm5, Ncutm6, Ncutm7, Ncutm8;
long Ncutm11, Ncutm12, Ncutm13, Ncutm14, Ncutm15, Ncutm21;
long Nsave1, Nsave2, Nsave3, Nsave4, Nsave5, Nsave6, Nsave7;
double energy_runm;

/////////////////////////////////////////////////////////////////////////////

DssInc::DssInc(const std::string & name, ISvcLocator * pSvcLocator): Algorithm(name, pSvcLocator)
{

	//Declare the properties
	declareProperty("Vr0cut", m_vr0cut = 1.0);
	declareProperty("Vz0cut", m_vz0cut = 10.0);
	//for photon
	declareProperty("EnergyBarrelThreshold", m_energyBarrelThreshold = 0.025);
	declareProperty("EnergyEndcapThreshold", m_energyEndcapThreshold = 0.05);
	declareProperty("GammaCosBarrelCut", m_gammaCosBarrelCut = 0.8);
	declareProperty("GammaCosEndcapMin", m_gammaCosEndcapMin = 0.86);
	declareProperty("GammaCosEndcapMax", m_gammaCosEndcapMax = 0.92);
	declareProperty("GammaAngleCut", m_gammaAngleCut = 20.0);
	declareProperty("IfDebug", m_ifdebug = false);
	declareProperty("PullCorrection", m_ifcorrection = true);
	declareProperty("EnergyCms", energycms = 4.600);
	declareProperty("RscanEnergy", ifRscan = false);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
StatusCode DssInc::initialize()
{
	MsgStream log(msgSvc(), name());

	log << MSG::INFO << "in initialize()" << endmsg;

	StatusCode status;
	NTuplePtr nt1(ntupleSvc(), "FILE1/gdsdss");
	if (nt1)
		m_tuple1 = nt1;
	else {
		m_tuple1 =
		    ntupleSvc()->book("FILE1/gdsdss", CLID_ColumnWiseTuple, "ds to k k pi example");
		if (m_tuple1) {
			status = m_tuple1->addItem("run", m_run);
			status = m_tuple1->addItem("cmsenergy", m_cmsenergy);
			status = m_tuple1->addItem("event", m_event);
			status = m_tuple1->addItem("ncharge", m_ncharge);
			status = m_tuple1->addItem("ntrack", m_ntrack);
			status = m_tuple1->addItem("vx0", m_vx0);
			status = m_tuple1->addItem("vy0", m_vy0);
			status = m_tuple1->addItem("vz0", m_vz0);
			status = m_tuple1->addItem("vr0", m_vr0);
			status = m_tuple1->addItem("rvxy0", m_rvxy0);
			status = m_tuple1->addItem("rvz0", m_rvz0);
			status = m_tuple1->addItem("rvphi0", m_rvphi0);
			//MC particle info.
			status = m_tuple1->addItem("indexmc", m_idxmc, 0, 100);
			status = m_tuple1->addIndexedItem("pdgid", m_idxmc, m_pdgid);
			status = m_tuple1->addIndexedItem("motheridx", m_idxmc, m_motheridx);
			//MC truth information
			/*status = m_tuple1->addItem("Pxkp_t", m_pxkp_t);
			status = m_tuple1->addItem("Pykp_t", m_pykp_t);
			status = m_tuple1->addItem("Pzkp_t", m_pzkp_t);
			status = m_tuple1->addItem("Ekp_t",  m_ekp_t);
			status = m_tuple1->addItem("Pxkm_t", m_pxkm_t);
			status = m_tuple1->addItem("Pykm_t", m_pykm_t);
			status = m_tuple1->addItem("Pzkm_t", m_pzkm_t);
			status = m_tuple1->addItem("Ekm_t",  m_ekm_t);
			status = m_tuple1->addItem("Pxpi_t", m_pxpi_t);
			status = m_tuple1->addItem("Pypi_t", m_pypi_t);
			status = m_tuple1->addItem("Pzpi_t", m_pzpi_t);
			status = m_tuple1->addItem("Epi_t",  m_epi_t);*/
			status = m_tuple1->addItem("Mdss_reco_t", m_dss_reco_t);
			status = m_tuple1->addItem("Mdss_t", m_dss_t);
			status = m_tuple1->addItem("Mds1_t", m_ds1_t);
			status = m_tuple1->addItem("Mdssm_t", m_dssm_t);
			status = m_tuple1->addItem("Mdssm_reco_t", m_dssm_reco_t);
			// photon in emc
			status = m_tuple1->addItem("indexemc", m_idxemc, 0, 50);
			status = m_tuple1->addIndexedItem("Egamma_rec", m_idxemc, m_egamma_rec);
			status = m_tuple1->addIndexedItem("costhetagamma_rec", m_idxemc, m_costhetagamma_rec);
			status = m_tuple1->addIndexedItem("phigamma_rec", m_idxemc, m_phigamma_rec);

			status = m_tuple1->addItem("Npi", m_npi);
			status = m_tuple1->addItem("Nkp", m_nkp);
			status = m_tuple1->addItem("Nkm", m_nkm);

			// information for all the Dss
			status = m_tuple1->addItem("Iall", m_iall, 0, 50);
			status = m_tuple1->addIndexedItem("Pi_pm", m_iall, pi_pm);
			status = m_tuple1->addIndexedItem("Ig", m_iall, m_ig);
			status = m_tuple1->addIndexedItem("Mds", m_iall, m_ds);
			status = m_tuple1->addIndexedItem("chisq_ds", m_iall, m_chisq_dss);
			status = m_tuple1->addIndexedItem("Mds0", m_iall, m_ds0);
			status = m_tuple1->addIndexedItem("Mkk", m_iall, m_kk);
			status = m_tuple1->addIndexedItem("Mkpp", m_iall, m_kpp);
			status = m_tuple1->addIndexedItem("Mkmp", m_iall, m_kmp);
			status = m_tuple1->addIndexedItem("Mkpi", m_iall, m_kpi);
			status = m_tuple1->addIndexedItem("Mds_reco", m_iall, m_ds_reco);
			status = m_tuple1->addIndexedItem("Mds_reco_c", m_iall, m_ds_reco_c);
			status = m_tuple1->addIndexedItem("Mdss", m_iall, m_dss);
			status = m_tuple1->addIndexedItem("Mdss_c", m_iall, m_dss_c);
			status = m_tuple1->addIndexedItem("Mdss_reco", m_iall, m_dss_reco);
			status = m_tuple1->addIndexedItem("Mdss_reco_c", m_iall, m_dss_reco_c);
			status = m_tuple1->addIndexedItem("Mg_reco", m_iall, m_g_reco);
			status = m_tuple1->addIndexedItem("Pxkp", m_iall, m_pxkp);
			status = m_tuple1->addIndexedItem("Pxkm", m_iall, m_pxkm);
			status = m_tuple1->addIndexedItem("Pxpi", m_iall, m_pxpi);
			status = m_tuple1->addIndexedItem("Pykp", m_iall, m_pykp);
			status = m_tuple1->addIndexedItem("Pykm", m_iall, m_pykm);
			status = m_tuple1->addIndexedItem("Pypi", m_iall, m_pypi);
			status = m_tuple1->addIndexedItem("Pzkp", m_iall, m_pzkp);
			status = m_tuple1->addIndexedItem("Pzkm", m_iall, m_pzkm);
			status = m_tuple1->addIndexedItem("Pzpi", m_iall, m_pzpi);
			status = m_tuple1->addIndexedItem("Ekp", m_iall, m_ekp);
			status = m_tuple1->addIndexedItem("Ekm", m_iall, m_ekm);
			status = m_tuple1->addIndexedItem("Epi", m_iall, m_epi);
			status = m_tuple1->addIndexedItem("Pxg", m_iall, m_pxg);
			status = m_tuple1->addIndexedItem("Pyg", m_iall, m_pyg);
			status = m_tuple1->addIndexedItem("Pzg", m_iall, m_pzg);
			status = m_tuple1->addIndexedItem("Eg", m_iall, m_eg);
			status = m_tuple1->addIndexedItem("Kinphi_t", m_iall, m_kinphi);
			status = m_tuple1->addIndexedItem("KinKst_t", m_iall, m_kinkst);

			//if found pi0
			status = m_tuple1->addItem("Ipi0", m_ipi0, 0, 50);
			status = m_tuple1->addIndexedItem("chisq_pi0", m_ipi0, m_chisq_pi0);
			status = m_tuple1->addIndexedItem("chisq_pi0_1C", m_ipi0, m_chisq_pi0_1C);
			status = m_tuple1->addIndexedItem("Mpi0", m_ipi0, m_pi0);
			status = m_tuple1->addIndexedItem("Ipi", m_ipi0, m_ipi);
			status = m_tuple1->addIndexedItem("Ipi01", m_ipi0, m_ipi01);
			status = m_tuple1->addIndexedItem("Ipi02", m_ipi0, m_ipi02);
			status = m_tuple1->addIndexedItem("Mpi0_reco", m_ipi0, m_pi0_reco);
			status = m_tuple1->addIndexedItem("Mpi0dss", m_ipi0, m_pi0dss);
			status = m_tuple1->addIndexedItem("Mpi0dss_c", m_ipi0, m_pi0dss_c);
			status = m_tuple1->addIndexedItem("Mpi0dss_cc", m_ipi0, m_pi0dss_cc);
			status = m_tuple1->addIndexedItem("Mpi0_reco_c", m_ipi0, m_pi0_reco_c);
			status = m_tuple1->addIndexedItem("Mpi0dss_reco", m_ipi0, m_pi0dss_reco);
			status = m_tuple1->addIndexedItem("Mpi0dss_reco_c", m_ipi0, m_pi0dss_reco_c);
			status = m_tuple1->addIndexedItem("Mpi0dss_reco_cc", m_ipi0, m_pi0dss_reco_cc);
			status = m_tuple1->addIndexedItem("Pxpi0", m_ipi0, m_pxpi0);
			status = m_tuple1->addIndexedItem("Pypi0", m_ipi0, m_pypi0);
			status = m_tuple1->addIndexedItem("Pzpi0", m_ipi0, m_pzpi0);
			status = m_tuple1->addIndexedItem("Epi0", m_ipi0, m_epi0);



		}
		else {
			log << MSG::ERROR << "    Cannot book N-tuple:" << long (m_tuple1) << endmsg;
			return StatusCode::FAILURE;
		}
	}
	//
	//--------end of book--------
	//
	m_irun = -100;
	//energycms=4.6;

	log << MSG::INFO << "successfully return from initialize()" << endmsg;
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
StatusCode DssInc::execute()
{

	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in execute()" << endreq;

	SmartDataPtr < Event::EventHeader > eventHeader(eventSvc(), "/Event/EventHeader");
	int runNo = eventHeader->runNumber();
	int event = eventHeader->eventNumber();
	log << MSG::DEBUG << "run, evtnum = " << runNo << " , " << event << endreq;
	if (m_ifdebug)
		cout << "event " << event << endl;
	m_run = runNo;
	m_event = event;
	if (m_event % 1000 == 0) {
		cout << "event=" << m_event << endl;
	}
	if (ifRscan) {
		energycms = RscanDQ(m_run).getEbeam() * 2;
	}
	HepLorentzVector ecms(0.011 * energycms, 0, 0, energycms);
	m_cmsenergy=energycms;
	Ncutm0++;
	if (eventHeader->runNumber() < 0) {
		if (m_ifdebug)
			cout << "step 0" << endl;
		SmartDataPtr < Event::McParticleCol > mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

		int m_numParticle = 0;

		if (!mcParticleCol) {
			log << MSG::FATAL << "Could not retrieve McParticelCol" << endreq;
			return StatusCode::FAILURE;
		}
		else {
			if (m_ifdebug)
				cout << "step 01" << endl;
			bool psipDecay = false;
			int rootIndex = -1;
			int mcorigin = 9030443;
			bool strange = false;

			HepLorentzVector p4kp_t, p4km_t, p4pi_t, p4g_t, p4ds_t, p4ds1_t;
			Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
			for (; iter_mc != mcParticleCol->end(); iter_mc++) {
				if ((*iter_mc)->primaryParticle() && (*iter_mc)->particleProperty() == 11 && ((*iter_mc)->mother()).particleProperty() == 11) {
					strange = true;
				}

				if (m_ifdebug)
					cout << "step mcparticle " << (*iter_mc)->particleProperty() << endl;
				if ((*iter_mc)->primaryParticle())
					continue;
				if (!(*iter_mc)->decayFromGenerator())
					continue;
				//if ( ((*iter_mc)->mother()).trackIndex()<3 ) continue;
				if ((*iter_mc)->particleProperty() == mcorigin) {
					psipDecay = true;
					rootIndex = (*iter_mc)->trackIndex();
				}
				if (!psipDecay)
					continue;
				int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
				int pdgid = (*iter_mc)->particleProperty();

				//if (strange && ((*iter_mc)->mother()).particleProperty() != mcorigin)  mcidx--;
				if(!((*iter_mc)->particleProperty()==9030443||((*iter_mc)->mother()).particleProperty()==9030443))
					mcidx--;
				m_pdgid[m_numParticle] = pdgid;
				m_motheridx[m_numParticle] = mcidx;
				if(m_ifdebug)
					cout << pdgid << " " << m_numParticle << " " << m_pdgid[m_numParticle] << " " << mcidx << endl;

				if (pdgid == 433) {
					m_dss_reco_t = (ecms - (*iter_mc)->initialFourMomentum()).m();
					m_dss_t = (*iter_mc)->initialFourMomentum().m();
				}
				else if (pdgid == -433) {
					m_dssm_reco_t = (ecms - (*iter_mc)->initialFourMomentum()).m();
					m_dssm_t = (*iter_mc)->initialFourMomentum().m();
				}
				else if (pdgid == -10433) {
					m_ds1_t = (*iter_mc)->initialFourMomentum().m();
				}
				m_numParticle += 1;
			}						// end of mc particle loop
		}
		m_idxmc = m_numParticle;
	}

	SmartDataPtr < EvtRecEvent > evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	//  log << MSG::INFO << "get event tag OK" << endreq;
	log << MSG::DEBUG << "ncharg, nneu, tottks = "
	    << evtRecEvent->totalCharged() << " , "
	    << evtRecEvent->totalNeutral() << " , " << evtRecEvent->totalTracks() << endreq;

	SmartDataPtr < EvtRecTrackCol > evtRecTrkCol(eventSvc(), EventModel::EvtRec::EvtRecTrackCol);
	//
	// check x0, y0, z0, r0
	// suggest cut: |z0|<5 && r0<1
	//
	Vint iGood, ipi, ikp, ikm;
	iGood.clear();
	ipi.clear();
	ikp.clear();
	ikm.clear();
	Vp4 ppi, pkp, pkm;
	ppi.clear();
	pkp.clear();
	pkm.clear();
	if (m_ifdebug)
		cout << "step 1" << endl;

	int nCharge = 0;

	Hep3Vector xorigin(0, 0, 0);

	IVertexDbSvc *vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if (vtxsvc->isVertexValid()) {
		double *dbv = vtxsvc->PrimaryVertex();
		double *vv = vtxsvc->SigmaPrimaryVertex();
		//    HepVector dbv = m_reader.PrimaryVertex(runNo);
		//    HepVector vv = m_reader.SigmaPrimaryVertex(runNo);
		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
	}

	for (int i = 0; i < evtRecEvent->totalCharged(); i++) {
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
		if (!(*itTrk)->isMdcKalTrackValid())
			continue;
		//RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
		RecMdcKalTrack *mdcTrk = (*itTrk)->mdcKalTrack();
		double pch = mdcTrk->p();
		double x0 = mdcTrk->x();
		double y0 = mdcTrk->y();
		double z0 = mdcTrk->z();
		//double phi0=mdcTrk->helix(1);
		double xv = xorigin.x();
		double yv = xorigin.y();
		//double Rxy=(x0-xv)*cos(phi0)+(y0-yv)*sin(phi0);
		m_vx0 = x0;
		m_vy0 = y0;
		m_vz0 = z0;
		//m_vr0 = Rxy;

		HepVector a = mdcTrk->helix();
		HepSymMatrix Ea = mdcTrk->err();
		HepPoint3D point0(0., 0., 0.);	// the initial point for MDC recosntruction
		HepPoint3D IP(xorigin[0], xorigin[1], xorigin[2]);
		VFHelix helixip(point0, a, Ea);
		helixip.pivot(IP);
		HepVector vecipa = helixip.a();
		double Rvxy0 = fabs(vecipa[0]);	//the nearest distance to IP in xy plane
		double Rvz0 = vecipa[3];	//the nearest distance to IP in z direction
		double Rvphi0 = vecipa[1];
		m_rvxy0 = Rvxy0;
		m_rvz0 = Rvz0;
		//    m_rvphi0=Rvphi0;
		//    if(fabs(z0) >= m_vz0cut) continue;
		//    if(fabs(Rxy) >= m_vr0cut) continue;

		if (fabs(Rvz0) >= 10.0)
			continue;
		if (fabs(Rvxy0) >= 1.0)
			continue;

		iGood.push_back(i);
		nCharge += mdcTrk->charge();
	}
	//
	// Finish Good Charged Track Selection
	//
	int nGood = iGood.size();
	m_ncharge = nCharge;
	m_ntrack = nGood;
	log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;

	if (nGood < 3) {
		//m_tuple1->write();
		Nsave1++;
		return StatusCode::SUCCESS;
	}

	Ncutm1++;
	if (m_ifdebug)
		cout << "step 2" << endl;

	Vint iGamma;
	iGamma.clear();
	Vdouble pTrkNeu;
	pTrkNeu.clear();
	for (int i = evtRecEvent->totalCharged(); i < evtRecEvent->totalTracks(); i++) {
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;

		if (!(*itTrk)->isEmcShowerValid())
			continue;
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

		double emctime = emcTrk->time();

		if (emctime < 0.0 || emctime > 14.0)
			continue;

		double eraw = emcTrk->energy();
		double ecos = cos(emcpos.theta());
		int emcModule = emcTrk->module();	// Module: 0:east endcap; 1:barrel; 2:west endcap

		if (emcModule == 1) {
			if (eraw < m_energyBarrelThreshold || fabs(ecos) > m_gammaCosBarrelCut)
				continue;
		}
		else {
			if (eraw < m_energyEndcapThreshold || fabs(ecos) < m_gammaCosEndcapMin
			        || fabs(ecos) > m_gammaCosEndcapMax)
				continue;
		}

		// find the nearest charged track
		double dang = 200.0;

		for (int j = 0; j < evtRecEvent->totalCharged(); j++) {
			EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;

			if (!(*jtTrk)->isExtTrackValid())
				continue;
			RecExtTrack *extTrk = (*jtTrk)->extTrack();

			if (extTrk->emcVolumeNumber() == -1)
				continue;
			Hep3Vector extpos = extTrk->emcPosition();
			double angd = extpos.angle(emcpos);

			if (angd < dang) {
				dang = angd;
			}
		}
		dang = dang * 180.0 / (CLHEP::pi);
		if (fabs(dang) < m_gammaAngleCut)
			continue;

		pTrkNeu.push_back(eraw);
		iGamma.push_back((*itTrk)->trackId());
	}

	//
	// Finish Good Photon Selection
	//
	int nGamma = iGamma.size();
	m_idxemc = iGamma.size();

	// log << MSG::DEBUG << "num Good Photon " << nGamma  << " , " <<evtRecEvent->totalNeutral()<<endreq;
	if (nGamma < 1 || nGamma > 50) {
		//m_tuple1->write();
		Nsave2++;
		return StatusCode::SUCCESS;
	}
	Ncutm2++;

	DssInc::BubbleSort(pTrkNeu, iGamma);

	//
	// Assign 4-momentum to each photon
	//
	if (m_ifdebug)
		cout << "step 3" << endl;

	Vp4 pGam;
	pGam.clear();
	for (int i = 0; i < nGamma; i++) {
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGamma[i];
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		double eraw = emcTrk->energy();
		double phi = emcTrk->phi();
		double the = emcTrk->theta();
		HepLorentzVector ptrk;
		ptrk.setPx(eraw * sin(the) * cos(phi));
		ptrk.setPy(eraw * sin(the) * sin(phi));
		ptrk.setPz(eraw * cos(the));
		ptrk.setE(eraw);

		//ptrk = ptrk.boost(-0.011,0,0);// boost to cms
		//m_costhetagamma=ptrk.cosTheta();
		//m_phigamma=ptrk.phi();
		m_egamma_rec[i] = eraw;
		m_costhetagamma_rec[i] = ptrk.cosTheta();
		m_phigamma_rec[i] = ptrk.phi();

		pGam.push_back(ptrk);
	}
	//
	// Assign 4-momentum to each charged track
	//
	ParticleID *pid = ParticleID::instance();
	for (int i = 0; i < nGood; i++) {
		double prob_pi = -1;
		double prob_k = -1;
		double prob_e = -1;
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
		//    if(pid) delete pid;
		RecMdcKalTrack *mdcKal = (*itTrk)->mdcKalTrack();	//After ParticleID, use RecMdcKalTrack substitute RecMdcTrack
		pid->init();
		pid->setMethod(pid->methodProbability());
		pid->setChiMinCut(4);
		pid->setRecTrack(*itTrk);
		pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTofE());	// use PID sub-system
		pid->identify(pid->onlyPion() | pid->onlyKaon());	// seperater Pion/Kaon
		pid->calculate();
		if ((pid->IsPidInfoValid())) {
			prob_pi = pid->probPion();
			prob_k = pid->probKaon();
			if (prob_k > prob_pi && prob_k > 0.001) {
				RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);	//PID can set to electron, muon, pion, kaon and proton;The default setting is pion
				if (mdcKal->charge() > 0) {
					ikp.push_back(iGood[i]);
					HepLorentzVector ptrk;
					ptrk.setPx(mdcKal->px());
					ptrk.setPy(mdcKal->py());
					ptrk.setPz(mdcKal->pz());
					double p3 = ptrk.mag();
					ptrk.setE(sqrt(p3 * p3 + xmass[3] * xmass[3]));

					pkp.push_back(ptrk);
				}
				else {
					ikm.push_back(iGood[i]);
					HepLorentzVector ptrk;
					ptrk.setPx(mdcKal->px());
					ptrk.setPy(mdcKal->py());
					ptrk.setPz(mdcKal->pz());
					double p3 = ptrk.mag();
					ptrk.setE(sqrt(p3 * p3 + xmass[3] * xmass[3]));

					pkm.push_back(ptrk);
				}

			}
			//else {
			else if (prob_pi > prob_k && prob_pi > 0.001) {
				RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);	//PID can set to electron, muon, pion, kaon and proton;The default setting is pion
				ipi.push_back(iGood[i]);
				HepLorentzVector ptrk;
				ptrk.setPx(mdcKal->px());
				ptrk.setPy(mdcKal->py());
				ptrk.setPz(mdcKal->pz());
				double p3 = ptrk.mag();
				ptrk.setE(sqrt(p3 * p3 + xmass[2] * xmass[2]));

				ppi.push_back(ptrk);
			}
		}
	}

	if (m_ifdebug)
		cout << "step 4" << endl;

	int npi = ipi.size();
	int nkp = ikp.size();
	int nkm = ikm.size();
	m_npi = npi;
	m_nkp = nkp;
	m_nkm = nkm;
	if (npi < 1 || nkm < 1 || nkp < 1) {
		if (m_ifdebug) {
			cout << m_idxmc << endl;
			for(int i = 0; i < m_idxmc; i++)
				cout << i << " " << m_pdgid[i] << " " << m_motheridx[i] << endl;
			m_tuple1->write();
		}
		Nsave3++;
		return StatusCode::SUCCESS;
	}

	Ncutm3++;

	if (m_ifdebug)
		cout << "step 7" << endl;
	//if (energycms < 4.429)
	//	return StatusCode::SUCCESS;

	if (m_ifdebug)
		cout << "step 5" << endl;

	//
	// Loop all the combinations to find the one with least:
	//((p4ds.m()-mDs)*(p4ds.m()-mDs)+(p4dss.m()-mDss)*(p4dss.m()-mDss)+(p4dss_reco-mDs1)**2),
	//
	KalmanKinematicFit *kmfit = KalmanKinematicFit::instance();
	WTrackParameter wvkpTrk, wvkmTrk, wvpiTrk;
	double m_chisq_tot = 999.;
	int iall = 0;
	int ipi0 = 0;
	m_ipi0 = 0;
	m_iall = 0;
	PullCorrection* pullcor = new PullCorrection();
	for (int ik1 = 0; ik1 < nkp; ik1++) {
		for (int ik2 = 0; ik2 < nkm; ik2++) {
			for (int ipi1 = 0; ipi1 < npi; ipi1++) {
				if (m_ifdebug)
					cout << "step 6" << endl;
				HepLorentzVector p4ds = pkp[ik1] + pkm[ik2] + ppi[ipi1];
				double mp4ds = p4ds.m();
				if (mp4ds < 1.86 || mp4ds > 2.06)
					continue;
				for (int ig0 = 0; ig0 < nGamma; ig0++) {
					if (m_ifdebug)
						cout << "step 7" << endl;
					HepLorentzVector p4dss = p4ds + pGam[ig0];
					double mp4dss = p4dss.m() - mp4ds + mDs;
					RecMdcKalTrack *kpTrk = (*(evtRecTrkCol->begin() + ikp[ik1]))->mdcKalTrack();
					RecMdcKalTrack *kmTrk = (*(evtRecTrkCol->begin() + ikm[ik2]))->mdcKalTrack();
					RecMdcKalTrack *piTrk = (*(evtRecTrkCol->begin() + ipi[ipi1]))->mdcKalTrack();
					if (m_ifcorrection && runNo < 0) {
						HepVector kphelix = pullcor->GetCorrection(0, kpTrk->getZErrorK()) + kpTrk->getZHelixK();
						HepVector kmhelix = pullcor->GetCorrection(1, kmTrk->getZErrorK()) + kmTrk->getZHelixK();
						HepVector pihelix;
						if (piTrk->charge() > 0)
							pihelix = pullcor->GetCorrection(2, piTrk->getZError()) + piTrk->getZHelix();
						else
							pihelix = pullcor->GetCorrection(3, piTrk->getZError()) + piTrk->getZHelix();
						wvkpTrk = WTrackParameter(xmass[3], kphelix, kpTrk->getZErrorK());
						wvkmTrk = WTrackParameter(xmass[3], kmhelix, kmTrk->getZErrorK());
						wvpiTrk = WTrackParameter(xmass[2], pihelix, piTrk->getZError());
					}
					else {
						wvkpTrk = WTrackParameter(xmass[3], kpTrk->getZHelixK(), kpTrk->getZErrorK());
						wvkmTrk = WTrackParameter(xmass[3], kmTrk->getZHelixK(), kmTrk->getZErrorK());
						wvpiTrk = WTrackParameter(xmass[2], piTrk->getZHelix(), piTrk->getZError());
					}
					HepPoint3D vx(0., 0., 0.);
					HepSymMatrix Evx(3, 0);
					double bx = 1E+6;
					double by = 1E+6;
					double bz = 1E+6;
					Evx[0][0] = bx * bx;
					Evx[1][1] = by * by;
					Evx[2][2] = bz * bz;

					VertexParameter vxpar;
					vxpar.setVx(vx);
					vxpar.setEvx(Evx);

					VertexFit *vtxfit = VertexFit::instance();
					vtxfit->init();
					vtxfit->AddTrack(0, wvkpTrk);
					vtxfit->AddTrack(1, wvkmTrk);
					vtxfit->AddTrack(2, wvpiTrk);
					vtxfit->AddVertex(0, vxpar, 0, 1, 2);
					if (!vtxfit->Fit(0))
						continue;
					vtxfit->Swim(0);
					if (m_ifdebug)
						cout << "step 8" << endl;
					WTrackParameter wkp = vtxfit->wtrk(0);
					WTrackParameter wkm = vtxfit->wtrk(1);
					WTrackParameter wpi = vtxfit->wtrk(2);
					RecEmcShower *g0Trk = (*(evtRecTrkCol->begin() + iGamma[ig0]))->emcShower();
					kmfit->init();
					kmfit->AddTrack(0, wkp);
					kmfit->AddTrack(1, wkm);
					kmfit->AddTrack(2, wpi);
					kmfit->AddTrack(3, 0.0, g0Trk);
					kmfit->AddResonance(0, mDs, 0, 1, 2);
					kmfit->AddResonance(1, mDss, 0, 1, 2, 3);

					if (!kmfit->Fit())
						continue;
					if (iall < 50) {

						if (m_ifdebug)
							cout << "step 9" << endl;

						m_chisq_dss[iall] = kmfit->chisq();
						HepLorentzVector p4ds0 = ecms - kmfit->pfit(0) - kmfit->pfit(1) - kmfit->pfit(2) - kmfit->pfit(3);
						m_ds0[iall] = p4ds0.m();

						m_kk[iall] = (pkp[ik1] + pkm[ik2]).m();
						m_kpp[iall] = (pkp[ik1] + ppi[ipi1]).m();
						m_kmp[iall] = (pkm[ik2] + ppi[ipi1]).m();
						pi_pm[iall] = piTrk->charge();
						m_ds[iall] = p4ds.m();
						m_ig[iall] = ig0;
						m_ds_reco[iall] = (ecms - p4ds).m();
						m_ds_reco_c[iall] = m_ds_reco[iall] + m_ds[iall] - mDs;
						m_dss[iall] = p4dss.m();
						m_dss_c[iall] = m_dss[iall] - m_ds[iall] + mDs;
						m_dss_reco[iall] = (ecms - p4dss).m();
						m_dss_reco_c[iall] = m_dss_reco[iall] + m_dss[iall] - mDss;
						m_g_reco[iall] = (ecms - pGam[ig0]).m();

						m_pxkp[iall] = pkp[ik1].px();
						m_pxkm[iall] = pkm[ik2].px();
						m_pxpi[iall] = ppi[ipi1].px();
						m_pykp[iall] = pkp[ik1].py();
						m_pykm[iall] = pkm[ik2].py();
						m_pypi[iall] = ppi[ipi1].py();
						m_pzkp[iall] = pkp[ik1].pz();
						m_pzkm[iall] = pkm[ik2].pz();
						m_pzpi[iall] = ppi[ipi1].pz();
						m_ekp[iall] = pkp[ik1].e();
						m_ekm[iall] = pkm[ik2].e();
						m_epi[iall] = ppi[ipi1].e();
						m_pxg[iall] = pGam[ig0].px();
						m_pyg[iall] = pGam[ig0].py();
						m_pzg[iall] = pGam[ig0].pz();
						m_eg[iall] = pGam[ig0].e();
						m_kinphi[iall] = HelAng(p4ds, pkp[ik1] + pkm[ik2], piTrk->charge() != 1 ? pkp[ik1] : pkm[ik2]).HelTheta();
						m_kinkst[iall] = HelAng(p4ds, piTrk->charge() != 1 ? pkp[ik1] + ppi[ipi1] : pkm[ik2] + ppi[ipi1], piTrk->charge() != 1 ? pkp[ik1] : pkm[ik2]).HelTheta();
						if (piTrk->charge() != 1) {
							m_kpi[iall] = (pkp[ik1] + ppi[ipi1]).m();
						} else {
							m_kpi[iall] = (pkm[ik2] + ppi[ipi1]).m();
						}
						if (nGamma >= 2) {
							for (int ig1 = 0; ig1 < nGamma - 1; ig1++) {
								for (int ig2 = ig1 + 1; ig2 < nGamma; ig2++) {
									if (m_ifdebug)
										cout << "step 10" << endl;
									HepLorentzVector p4pi0 = pGam[ig1] + pGam[ig2];
									double mp4pi0 = p4pi0.m();
									if (mp4pi0 < 0.05 || mp4pi0 > 0.3)
										continue;
									RecEmcShower *g1Trk = (*(evtRecTrkCol->begin() + iGamma[ig1]))->emcShower();
									RecEmcShower *g2Trk = (*(evtRecTrkCol->begin() + iGamma[ig2]))->emcShower();
									if (m_ifdebug)
										cout << "step 11" << endl;
									kmfit->init();
									kmfit->AddTrack(0, 0.0, g1Trk);
									kmfit->AddTrack(1, 0.0, g2Trk);
									kmfit->AddResonance(0, mPi0, 0, 1);
									kmfit->Fit();
									double chisq_pi0_1C = kmfit->chisq();
									kmfit->init();
									kmfit->AddTrack(0, wkp);
									kmfit->AddTrack(1, wkm);
									kmfit->AddTrack(2, wpi);
									kmfit->AddTrack(3, 0.0, g0Trk);
									kmfit->AddTrack(4, 0.0, g1Trk);
									kmfit->AddTrack(5, 0.0, g2Trk);
									kmfit->AddMissTrack(6, mDss);
									kmfit->AddResonance(0, mDs, 0, 1, 2);
									kmfit->AddResonance(1, mDss, 0, 1, 2, 3);
									kmfit->AddResonance(2, mPi0, 4, 5);
									kmfit->AddFourMomentum(3, ecms);
									//kmfit->setEspread(0.0016);
									//if(!kmfit->Fit())
									//	continue;
									if (ipi0 < 50) {
										m_chisq_pi0_1C[ipi0] = chisq_pi0_1C;
										m_chisq_pi0[ipi0] = kmfit->chisq();
										m_ipi[ipi0] = iall;
										m_ipi01[ipi0] = ig1;
										m_ipi02[ipi0] = ig2;
										m_pi0[ipi0] = mp4pi0;
										m_pi0_reco[ipi0] = (ecms - p4pi0).m();
										m_pxpi0[ipi0] = p4pi0.px();
										m_pypi0[ipi0] = p4pi0.py();
										m_pzpi0[ipi0] = p4pi0.pz();
										m_epi0[ipi0] = p4pi0.e();
										m_pi0_reco_c[ipi0] = m_pi0_reco[ipi0] + m_pi0[ipi0] - mPi0;
										m_pi0dss[ipi0] = (p4dss + p4pi0).m();
										m_pi0dss_c[ipi0] = m_pi0dss[ipi0] - m_dss[iall] + mDss;
										m_pi0dss_cc[ipi0] = m_pi0dss_c[ipi0] - m_pi0[ipi0] + mPi0;
										m_pi0dss_reco[ipi0] = (ecms - p4dss - p4pi0).m();
										m_pi0dss_reco_c[ipi0] = m_pi0dss_reco[ipi0] + m_dss[iall] - mDss;
										m_pi0dss_reco_cc[ipi0] = m_pi0dss_reco_c[ipi0] + m_pi0[ipi0] - mPi0;
										ipi0++;
									}
								}
							}
						}
						iall++;
					}
				}
			}
		}
	}
	m_iall = iall;
	m_ipi0 = ipi0;
	if (iall < 1) {
		m_tuple1->write();
		Nsave5++;
		return StatusCode::SUCCESS;
	}

	Nsave6++;
	m_tuple1->write();
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
StatusCode DssInc::finalize()
{
	cout << "total number:          " << Ncutm0 << endl;
	cout << "nGood==4, nCharge==0:  " << Ncutm1 << endl;
	cout << "bnGam>=3&&<=10:        " << Ncutm2 << endl;
	cout << "Pass pid:              " << Ncutm3 << endl;
	cout << "save result:           " << Ncutm4 << endl;
	cout << "save result:           " << Ncutm5 << endl;
	cout << "save result:           " << Ncutm6 << endl;
	cout << "cms energy:            " << energycms << endl;
	cout << "Nsave 1:               " << Nsave1 << endl;
	cout << "Nsave 2:               " << Nsave2 << endl;
	cout << "Nsave 3:               " << Nsave3 << endl;
	cout << "Nsave 4:               " << Nsave4 << endl;
	cout << "Nsave 5:               " << Nsave5 << endl;
	cout << "Nsave 6:               " << Nsave6 << endl;
	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in finalize()" << endmsg;
	return StatusCode::SUCCESS;
}

void DssInc::BubbleSort(std::vector < double >&p, std::vector < int >&trkid)
{
	if ((int) p.size() != (int) trkid.size()) {
		std::cout << "the two vector have different length!" << std::endl;
		std::cout << "the size of p is " << (int) p.size() << std::endl;
		std::cout << "the size of trkid is " << (int) trkid.size() << std::endl;
		std::cout << "Please check your code!" << std::endl;
		exit(1);
	}

	unsigned int vsize = p.size();

	// sort max->min
	double ptemp;
	int idtemp;

	for (unsigned int i = 0; i < vsize - 1; i++) {
		for (unsigned int j = i + 1; j < vsize; j++) {
			if (p[i] < p[j]) {
				ptemp = p[i];
				idtemp = trkid[i];
				p[i] = p[j];
				trkid[i] = trkid[j];
				p[j] = ptemp;
				trkid[j] = idtemp;
			}
		}							// for j
	}							// for i
}
