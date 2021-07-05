#include "pipipi0Alg/util/MyIsPID.h"


bool isPion(EvtRecTrack* recTrk, NTuple::Matrix<double>& prod_mu, int s, int i){
	// to obtain the information of PID of pion or kaon
	ParticleID *pid = ParticleID::instance();
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(4);
	pid->setRecTrack(recTrk);
	if(s==1){
		pid->usePidSys(pid->useDedx() | pid->useTofCorr() );
	}
	else if(s==2){
		pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc());
	}
	pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() | pid->onlyMuon() | pid->onlyProton() );
	pid->calculate();

	double ratio = pid->probElectron() / (pid->probPion() + pid->probKaon() + pid->probElectron());
	prod_mu[i][0] = pid->probElectron() ;
	prod_mu[i][1] = pid->probMuon() ;
	prod_mu[i][2] = pid->probPion() ;
	prod_mu[i][3] = pid->probKaon() ;
	prod_mu[i][4] = pid->probProton() ;
	prod_mu[i][5] = ratio ;

	//if( (pid->probPion()>0 && pid->probPion()>pid->probKaon()) )
	return true;
	//return false;
}

bool isElectron(EvtRecTrack* recTrk, NTuple::Array<double>& prod_mu, int s ){
	ParticleID *pid = ParticleID::instance();
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(4);
	pid->setRecTrack(recTrk);
	if(s==2){
		pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc());
	}
	else if(s==1){
		pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() |  pid->useTof() | pid->useEmc());
	}
	pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyElectron() | pid->onlyMuon() | pid->onlyProton());
	pid->calculate();

	double ratio = pid->probElectron() / (pid->probPion() + pid->probKaon() + pid->probElectron());
	prod_mu[0] = pid->probElectron() ;
	prod_mu[1] = pid->probMuon() ;
	prod_mu[2] = pid->probPion() ;
	prod_mu[3] = pid->probKaon() ;
	prod_mu[4] = pid->probProton() ;
	prod_mu[5] = ratio ;


	//if(pid->probElectron()>0.001 && ratio>0.8)
	//  return true;
	return true;
}


bool isProton(EvtRecTrack* recTrk, NTuple::Matrix<double>& prod_mu,  int i){
	ParticleID *pid = ParticleID::instance();
	pid->init();
	pid->setMethod(pid->methodProbability());
	//pid->setChiMinCut(8);
	pid->setChiMinCut(4);
	pid->setRecTrack(recTrk);
	//pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc() );
	pid->usePidSys(pid->useDedx() | pid->useTof1() |  pid->useTof2() );
	pid->identify(pid->onlyProton() | pid->onlyKaon()  | pid->onlyPion() | pid->onlyElectron() | pid->onlyMuon());
	pid->calculate();

  double ratio1 = pid->probElectron() / (pid->probPion() + pid->probKaon() + pid->probElectron());
  double ratio2 = pid->probPion() / (pid->probPion() + pid->probKaon() );
  double ratio3 = pid->probPion() / (pid->probPion() + pid->probKaon() + pid->probProton() );
  double ratio4 = pid->probPion() / (pid->probPion() + pid->probKaon() + pid->probElectron() );
  double ratio5 = pid->probPion() / (pid->probPion() + pid->probKaon() + pid->probElectron() + pid->probMuon() );
  prod_mu[i][0] = pid->probElectron() ;
  prod_mu[i][1] = pid->probMuon() ;
  prod_mu[i][2] = pid->probPion() ;
  prod_mu[i][3] = pid->probKaon() ;
  prod_mu[i][4] = pid->probProton() ;
  prod_mu[i][5] = ratio1 ;
  prod_mu[i][6] = ratio2 ;
  prod_mu[i][7] = ratio3 ;
  prod_mu[i][8] = ratio4 ;
  prod_mu[i][9] = ratio5 ;
  

	return true;
}


