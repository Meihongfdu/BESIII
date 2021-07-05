#include "StoeeLAlg/Selector/StoeeLAlgLambdaSelector.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EvtRecEvent/EvtRecVeeVertex.h"
#include "ParticleID/ParticleID.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/Helix.h"
#include "HadronInfo/LamInfo.hpp"

StoeeLAlgLambdaSelector::StoeeLAlgLambdaSelector(){
	IJobOptionsSvc* jobSvc;
	Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

	PropertyMgr m_propMgr;

	m_propMgr.declareProperty("MinMassCut",        m_minMass = 1.095 );
	m_propMgr.declareProperty("MaxMassCut",        m_maxMass = 1.135 );
	m_propMgr.declareProperty("MaxChisq",          m_maxChisq = 200 );

	m_propMgr.declareProperty("LambdaMaxVFitChisq",    m_maxVFitChisq = 1000 );

	m_propMgr.declareProperty("CutFlightSig", m_CutFlightSig = false);
	m_propMgr.declareProperty("MinFlightSig", m_minFlightSig = 2.0);


	jobSvc->setMyProperties("StoeeLAlgLambdaSelector", &m_propMgr);
}

bool StoeeLAlgLambdaSelector::operator() (CDDecay& aLambda){
    aLambda.setUserTag(3122);
    
    EvtRecTrack* trkproton = const_cast<EvtRecTrack*>(
            aLambda.decay().child(0).track() );
    EvtRecTrack* trkpion = const_cast<EvtRecTrack*>(
            aLambda.decay().child(1).track() );
    
    // Need the package HadronInfo
    LamInfo lamInf(trkproton, trkpion);
    lamInf.calculate();
    double mass = lamInf.m();
    if ((mass <= m_minMass)||(mass >= m_maxMass)){
        return false;
    }

    double vtxChi2 = lamInf.vtxChi2();
    if(vtxChi2 > m_maxChisq){ 
        return false;
    }
    aLambda.setP4(lamInf.p4());

    return true;
}

StoeeLAlgLambdaSelector lambdaSelector;

