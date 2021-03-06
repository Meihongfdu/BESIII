#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"
#include "StoeeLAlg/Selector/StoeeLAlgSigma0Selector.h"

StoeeLAlgSigma0Selector::StoeeLAlgSigma0Selector(){
   IJobOptionsSvc* jobSvc;
   Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

   PropertyMgr m_propMgr;

   //Declare the properties
   m_propMgr.declareProperty("MinMassCut",               m_minMass=1.161);
   m_propMgr.declareProperty("MaxMassCut",               m_maxMass=1.222);
   m_propMgr.declareProperty("MinMassCut_tight",         m_minMass_tight=1.179);
   m_propMgr.declareProperty("MaxMassCut_tight",         m_maxMass_tight=1.203);   
   
   jobSvc->setMyProperties("StoeeLAlgSigma0Selector", &m_propMgr);
}

bool StoeeLAlgSigma0Selector::operator() (CDDecay& aSigma0) {

  aSigma0.setUserTag(1);
  double mass = aSigma0.mass();
  if ((mass <= m_minMass)||(mass >= m_maxMass)) return false;

   if(mass < m_minMass_tight || mass > m_maxMass_tight)
     aSigma0.setUserTag(2);

   return true;
}


StoeeLAlgSigma0Selector sigma0Selector;
