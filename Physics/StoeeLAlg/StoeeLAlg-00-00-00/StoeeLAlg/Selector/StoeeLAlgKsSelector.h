#ifndef StoeeLAlg_KS_SELECTOR_H
#define StoeeLAlg_KS_SELECTOR_H

#include "BesDChain/CDKs.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgKsSelector : public DCSelectionFunction<CDKs>
{
   public :

      StoeeLAlgKsSelector();

      bool operator() (CDKs& aKs);

   private :

      StoeeLAlgKsSelector( const StoeeLAlgKsSelector& );
      const StoeeLAlgKsSelector& operator= ( const StoeeLAlgKsSelector& );

      double m_minMass;
      double m_maxMass;
      double m_maxChisq;

      bool m_doSecondaryVFit;
      double m_maxVFitChisq;
      double m_minFlightSig;

};

extern StoeeLAlgKsSelector stoeeLAlgKsSelector;

#endif
