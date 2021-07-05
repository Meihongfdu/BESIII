#ifndef StoeeLAlg_EtaToGG_SELECTOR_H
#define StoeeLAlg_EtaToGG_SELECTOR_H

#include "BesDChain/CDEta.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgEtatoGGSelector : public DCSelectionFunction<CDEta>
{
   public :

      StoeeLAlgEtatoGGSelector();

      bool operator() (CDEta& aEta);


   private :

      StoeeLAlgEtatoGGSelector( const StoeeLAlgEtatoGGSelector& );
      const StoeeLAlgEtatoGGSelector& operator= ( const StoeeLAlgEtatoGGSelector& );

      double m_minMass;
      double m_maxMass; 
      double m_maxChisq;

};

extern StoeeLAlgEtatoGGSelector stoeeLAlgEtatoGGSelector;

#endif
