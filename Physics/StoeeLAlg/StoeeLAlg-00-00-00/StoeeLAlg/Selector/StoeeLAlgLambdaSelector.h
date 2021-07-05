#ifndef StoeeLAlg_Lamda_SELECTOR_H
#define StoeeLAlg_Lamda_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgLambdaSelector : public DCSelectionFunction<CDDecay>{
	public :

		StoeeLAlgLambdaSelector();

		bool operator() (CDDecay& aLambda);

	private :

		StoeeLAlgLambdaSelector( const StoeeLAlgLambdaSelector& );
		const StoeeLAlgLambdaSelector& operator= ( const StoeeLAlgLambdaSelector& );

		double m_minMass;
		double m_maxMass;
		double m_maxChisq;
 
        bool m_CutFlightSig;
		double m_maxVFitChisq;
		double m_minFlightSig;
};

extern StoeeLAlgLambdaSelector lambdaSelector;

#endif
