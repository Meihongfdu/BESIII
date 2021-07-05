#ifndef MY_UTIL_H
#define MY_UTIL_H
#include "GaudiKernel/NTuple.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "EmcRecEventModel/RecEmcShower.h"
#include "GaudiKernel/NTuple.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "BesDChain/CDDecayList.h"
#include "McTruth/McParticle.h"
#include "MucRecEvent/RecMucTrack.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "McDecayModeSvc/McDecayModeSvc.h"
#include "EventModel/Event.h"
#include "EventNavigator/EventNavigator.h"
#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecPi0.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "EvtRecEvent/EvtRecVeeVertex.h"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
 
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"

#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
//-----------------------------------------------------------------------------------------------------------------
typedef NTuple::Item<int> NIint;
typedef NTuple::Array<int> NAint;
void FillP4Inf( HepLorentzVector p4, NTuple::Item<double>& m,NTuple::Item<double>& p);
void FillP4Inf( int,EvtRecTrack*, NTuple::Item<double>& m,NTuple::Item<double>& p);
void FillP4Inf(const CDCandidate&,NTuple::Item<double>& m,NTuple::Item<double>& p);
#endif

