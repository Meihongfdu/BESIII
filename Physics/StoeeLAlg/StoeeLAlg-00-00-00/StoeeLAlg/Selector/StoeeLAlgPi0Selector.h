#ifndef StoeeLAlg_Pio_SELECTOR_H
#define StoeeLAlg_Pio_SELECTOR_H

#include "BesDChain/CDPi0.h"
#include "DecayChain/Function/DCSelectionFunction.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EvtRecEvent/EvtRecPi0.h"

class StoeeLAlgPi0Selector : public DCSelectionFunction<CDPi0>{
    public :

        StoeeLAlgPi0Selector();

        bool operator() (CDPi0& aPi0);


    private :

        StoeeLAlgPi0Selector( const StoeeLAlgPi0Selector& );
        const StoeeLAlgPi0Selector& operator= ( const StoeeLAlgPi0Selector& );
        double m_minP;
        double m_minMass;
        double m_maxMass; 
        double m_maxChisq;

};

extern StoeeLAlgPi0Selector stoeeLAlgPi0Selector;

#endif
