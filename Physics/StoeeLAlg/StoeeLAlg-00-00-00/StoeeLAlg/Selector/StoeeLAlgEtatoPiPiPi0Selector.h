#ifndef StoeeLAlg_ETATOPIPIPI0_SELECTOR_H
#define StoeeLAlg_ETATOPIPIPI0_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgEtatoPiPiPi0Selector : public DCSelectionFunction<CDDecay> {
    public :
    
        StoeeLAlgEtatoPiPiPi0Selector();
        
        bool operator() (CDDecay& aEp);
    
    
    private :
    
        StoeeLAlgEtatoPiPiPi0Selector( const StoeeLAlgEtatoPiPiPi0Selector& );
        const StoeeLAlgEtatoPiPiPi0Selector& operator= ( const StoeeLAlgEtatoPiPiPi0Selector& );
        
        double m_minMass;
        double m_maxMass;
    
};

extern StoeeLAlgEtatoPiPiPi0Selector stoeeLAlgEtatoPiPiPi0Selector;

#endif
