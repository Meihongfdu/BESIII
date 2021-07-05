#ifndef LOCAL_SIGMA0_SELECTOR_H
#define LOCAL_SIGMA0_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgSigma0Selector : public DCSelectionFunction<CDDecay>{
   public :

      StoeeLAlgSigma0Selector();

      bool operator() (CDDecay& aSigma);


   private :

      StoeeLAlgSigma0Selector( const StoeeLAlgSigma0Selector& );
      const StoeeLAlgSigma0Selector& operator= ( const StoeeLAlgSigma0Selector& );

      double m_minMass;
      double m_maxMass;

      double m_minMass_tight;
      double m_maxMass_tight;
};

extern StoeeLAlgSigma0Selector sigma0Selector;

#endif
