#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"
#include "StoeeLAlg/Selector/StoeeLAlgEtatoPiPiPi0Selector.h"

StoeeLAlgEtatoPiPiPi0Selector::StoeeLAlgEtatoPiPiPi0Selector(){
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);
    
    PropertyMgr m_propMgr;
    
    //Declare the properties
    m_propMgr.declareProperty("minMassEtatoPiPiPi0",               m_minMass=0.40);
    m_propMgr.declareProperty("maxMassEtatoPiPiPi0",               m_maxMass=0.70);
     
     
    jobSvc->setMyProperties("StoeeLAlgEtatoPiPiPi0Selector", &m_propMgr);
}

bool StoeeLAlgEtatoPiPiPi0Selector::operator() (CDDecay& aEta) {

    aEta.setUserTag(1);
    double mass = aEta.mass();
    if(mass >= m_minMass && mass<= m_maxMass) {
        return true;
    }
    else { 
        return false;
    }
}
StoeeLAlgEtatoPiPiPi0Selector stoeeLAlgEtatoPiPiPi0Selector;

