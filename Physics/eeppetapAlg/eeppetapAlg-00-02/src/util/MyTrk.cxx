#include "eeppetapAlg/util/MyTrk.h"
#include "HadronInfo/TrackInfo.h"


bool fillChargedTrkInfo (EvtRecTrack* track1, NTuple::Matrix<double>& nt_M4, NTuple::Matrix<double>& m_m, int type, int i){

  HepLorentzVector p4mu(0,0,0,0);
  TrackInfo track1Info;
  track1Info.settrack(type, track1);// e, mu, pi, K, p: 0,1,2,3,4;
  p4mu = track1Info.p4();

  nt_M4[i][0] = p4mu.x();
  nt_M4[i][1] = p4mu.y();
  nt_M4[i][2] = p4mu.z();
  nt_M4[i][3] = p4mu.e();

  m_m[i][0]   = track1Info.dedxchie();
  m_m[i][1]   = track1Info.dedxchimu();
  m_m[i][2]   = track1Info.dedxchipi();
  m_m[i][3]   = track1Info.dedxchik();
	m_m[i][4]   = track1Info.dedxchip();
	m_m[i][5]   = p4mu.rho();
	m_m[i][6]   = p4mu.cosTheta();
	m_m[i][7]   = track1Info.emctrk();
	m_m[i][8]   = track1Info.eoptrk();
	m_m[i][9]   = track1Info.muLay();
	m_m[i][10]  = track1Info.muDep();
	m_m[i][11]  = track1Info.muNhits();
	m_m[i][12]  = track1Info.muLastLay();
	m_m[i][13]  = track1Info.muMaxHitsInLay();
	m_m[i][14]  = track1Info.mcharge();

	return true;
}

bool fillChargedTrkInfos (EvtRecTrack* track1, NTuple::Array<double>& nt_M4, NTuple::Array<double>& m_m, int type){
 
for(int i = 0; i< 15; i++){
	 m_m[i] = 0.;  
 }

HepLorentzVector p4mu(0.0,0.0,0.0,0.0);
  TrackInfo track1Info;
  track1Info.settrack(type, track1);// e, mu, pi, K, p: 0,1,2,3,4;
  p4mu = track1Info.p4();

  nt_M4[0] = p4mu.x();
  nt_M4[1] = p4mu.y();
  nt_M4[2] = p4mu.z();
  nt_M4[3] = p4mu.e();
  m_m[0]   = track1Info.dedxchie();
  m_m[1]   = track1Info.dedxchimu();
  m_m[2]   = track1Info.dedxchipi();
  m_m[3]   = track1Info.dedxchik();
  m_m[4]   = track1Info.dedxchip();
	m_m[5]   = p4mu.rho();
	m_m[6]   = p4mu.cosTheta();
	m_m[7]   = track1Info.emctrk();
	m_m[8]   = track1Info.eoptrk();
	m_m[9]   = track1Info.muLay();
	m_m[10]  = track1Info.muDep();
	m_m[11]  = track1Info.muNhits();
	m_m[12]  = track1Info.muLastLay();
	m_m[13]  = track1Info.muMaxHitsInLay();
	m_m[14]  = track1Info.mcharge();


	return true;
}

