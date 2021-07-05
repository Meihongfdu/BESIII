#ifndef DDmcmode_selection_H 
#define DDmcmode_selection_H
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "EventTag/EventTagSvc.h"
#include "McTruth/McParticle.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
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
#include <vector>
#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/IVertexDbSvc.h"
#include "ParticleID/ParticleID.h"

typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<Hep3Vector> Vp3;
typedef std::vector<double> Vdouble;

class  DDmcmode 
{

 public:

  ~DDmcmode(){;}
  static DDmcmode* instance();

  void  D0mcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol);
  void D0bmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol);
  void  Dpmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol);
  void  Dnmcmode(SmartDataPtr<Event::McParticleCol> mcParticleCol);
  
  void  D0mcmodeF(SmartDataPtr<Event::McParticleCol>);
  void D0bmcmodeF(SmartDataPtr<Event::McParticleCol>);
  void  DpmcmodeF(SmartDataPtr<Event::McParticleCol>);
  void  DnmcmodeF(SmartDataPtr<Event::McParticleCol>);  

  Vint MctkPID;
  
  Vint  mcmode()  {return  Mcmode;}
  Vint    idtk()  {return IDtk;}
  Vp4      p4d()  {return  P4D;}
  Vp4      p4k()  {return  P4K;}
  Vp4      ptk()  {return  Ptk;}
   int  chargd()  {return ChargD;}
   int  chargk()  {return ChargK;}
   int  mcmodef() {return  Mcmodef;}
  Vint finalID;
   int m_Mode;
  
  private:
  DDmcmode(){;}
  static DDmcmode *m_pointer;

  Vint Mcmode;
  Vint IDtk;  
  Vp4  P4D;  
  Vp4  P4K;  
  Vp4  Ptk;  
  int  Mcmodef;
  int  ChargD;
  int  ChargK;
  
};

#endif

