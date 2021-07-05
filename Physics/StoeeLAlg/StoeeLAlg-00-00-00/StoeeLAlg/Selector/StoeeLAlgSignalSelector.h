#ifndef StoeeLAlg_Ds_SELECTOR_H
#define StoeeLAlg_Ds_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
using CLHEP::HepLorentzVector;

class StoeeLAlgSignalSelector : public DCSelectionFunction<CDDecay>
{
  public :
    
    StoeeLAlgSignalSelector();
  
    inline void setebeam(double ebeam) { m_beamE = ebeam; }
    
    bool operator() (CDDecay& aOmega);

  private :
    
    StoeeLAlgSignalSelector( const StoeeLAlgSignalSelector& );
    const StoeeLAlgSignalSelector& operator= ( const StoeeLAlgSignalSelector& );
    
    double m_beamE;
    
    bool m_useMbcCuts;
    bool m_useDeltaECut;
    bool m_useRecCuts ;
    double m_maxRecMass;
    double m_minRecMass ;

    double m_minMass;
    double m_maxMass;
    
    double m_MinDeltaE;
    double m_MaxDeltaE;
    
};

extern StoeeLAlgSignalSelector stoeeLAlgSignalSelector;

#endif
