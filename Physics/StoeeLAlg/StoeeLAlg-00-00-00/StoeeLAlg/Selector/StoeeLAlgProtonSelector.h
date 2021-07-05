#ifndef StoeeLAlg_Proton_SELECTOR_H
#define StoeeLAlg_Proton_SELECTOR_H

#include "BesDChain/CDProton.h"
#include "DecayChain/Function/DCSelectionFunction.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"
#include "BesDChain/CDProton.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"


class StoeeLAlgProtonSelector : public DCSelectionFunction<CDProton>{
   public :

      StoeeLAlgProtonSelector();

      bool operator() (CDProton &aProton);

   private :

      StoeeLAlgProtonSelector(const StoeeLAlgProtonSelector& );
      const StoeeLAlgProtonSelector &operator= ( const StoeeLAlgProtonSelector& );

      int m_pidtype;


      double m_VrCut;
      double m_VzCut;
      double m_CosThetaCut;
      
      double m_minP;

      bool   m_PID;

};

extern StoeeLAlgProtonSelector stoeeLAlgProtonSelector;

#endif
