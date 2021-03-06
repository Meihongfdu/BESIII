#include "StoeeLAlg/Selector/StoeeLAlgProtonSelector.h"

StoeeLAlgProtonSelector::StoeeLAlgProtonSelector(){
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);
  
     PropertyMgr m_propMgr;
  
    //Declare the properties
    m_propMgr.declareProperty("RxyCut",         m_VrCut       =1.0);
    m_propMgr.declareProperty("Vz0Cut",         m_VzCut       =10.0);
    m_propMgr.declareProperty("CosThetaCut",    m_CosThetaCut =0.93);
    m_propMgr.declareProperty("DoPID",          m_PID  = true);
    m_propMgr.declareProperty("minP",           m_minP = 0.0);
  
    jobSvc->setMyProperties("StoeeLAlgProtonSelector", &m_propMgr);
}

bool StoeeLAlgProtonSelector::operator() (CDProton& aProton) {
    aProton.setUserTag(1);    
    HepLorentzVector p4 = aProton.p4();
    if(p4.rho()<m_minP){
         return false;
    }

    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>( aProton.track() );

    // MDC track selection
    RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
    if ( !recTrk->isMdcKalTrackValid() ){
         return false;
    }
    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
    if ( mdcKalTrk->charge()==0 ){ 
        return false;
    }
 
    Hep3Vector xorigin(0,0,0);
    IVertexDbSvc*  vtxsvc;
    Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    if(vtxsvc->isVertexValid()){
        double* dbv = vtxsvc->PrimaryVertex();
        double*  vv = vtxsvc->SigmaPrimaryVertex();
        xorigin.setX(dbv[0]);
        xorigin.setY(dbv[1]);
        xorigin.setZ(dbv[2]);
    }
    HepVector a = mdcKalTrk->getZHelix();
    HepSymMatrix Ea = mdcKalTrk->getZError();
    HepPoint3D point0(0.,0.,0.);
    HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
    VFHelix helixip3(point0,a,Ea);
    helixip3.pivot(IP);
    HepVector  vecipa = helixip3.a();
 
    double dr=fabs(vecipa[0]);
    double dz=fabs(vecipa[3]);
    double costheta=cos(mdcKalTrk->theta());
    if (  dr>= m_VrCut ) {
        return false;
    }
    if (  dz>= m_VzCut ) {
        return false;
    }
    if ( fabs(costheta) >= m_CosThetaCut ){ 
        return false;
    }

    //----do pid-----
    if(m_PID){
        ParticleID *pid = ParticleID::instance();
        pid->init();
        pid->setMethod(pid->methodProbability());
        pid->setChiMinCut(8);
        pid->setRecTrack(recTrk);
        pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTof() );
        pid->identify(pid->onlyProton() | pid->onlyKaon() | pid->onlyPion());
        //pid->identify(pid->onlyProton() | pid->onlyKaon() | pid->onlyPion() | pid->onlyElectron());
        pid->calculate();

        if( pid->probProton() > 0.001 && pid->probProton() > pid->probKaon()
            &&pid->probProton() > pid->probPion()){
            aProton.setUserTag(aProton.charge()*2);
        }
        else{
            return false;
        }
    }
    return true;
}

StoeeLAlgProtonSelector stoeeLAlgProtonSelector;
