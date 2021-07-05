#ifndef StoeeLAlg_EPTOPIPIETA_SELECTOR_H
#define StoeeLAlg_EPTOPIPIETA_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgEptoPiPiEtaSelector : public DCSelectionFunction<CDDecay> {
   public :

      StoeeLAlgEptoPiPiEtaSelector();

      bool operator() (CDDecay& aEp);


   private :

      StoeeLAlgEptoPiPiEtaSelector( const StoeeLAlgEptoPiPiEtaSelector& );
      const StoeeLAlgEptoPiPiEtaSelector& operator= ( const StoeeLAlgEptoPiPiEtaSelector& );

      double m_minMass;
      double m_maxMass;

};

extern StoeeLAlgEptoPiPiEtaSelector stoeeLAlgEptoPiPiEtaSelector;

#endif
