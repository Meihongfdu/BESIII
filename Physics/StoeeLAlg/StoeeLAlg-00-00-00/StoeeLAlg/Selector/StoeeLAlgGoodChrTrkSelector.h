#ifndef StoeeLAlg_GoodChrTrk_SELECTOR_H
#define StoeeLAlg_GoodChrTrk_SELECTOR_H

#include "BesDChain/CDElectron.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgGoodChrTrkSelector : public DCSelectionFunction<CDElectron>{

    public :

        StoeeLAlgGoodChrTrkSelector();

        bool operator() (CDElectron &aEle);
        inline void setcharge(int chr){ m_charge = chr;}

    private :

        StoeeLAlgGoodChrTrkSelector(const StoeeLAlgGoodChrTrkSelector&);
        const StoeeLAlgGoodChrTrkSelector &operator= (const StoeeLAlgGoodChrTrkSelector&);

        int m_charge;
        int m_pidtype;
          

        double m_VrCut;
        double m_VzCut;
        double m_CosThetaCut;

        double m_minEvP;

        bool  m_PID;
        bool  m_VCut;
        bool  m_CutEvP;

};

extern StoeeLAlgGoodChrTrkSelector stoeeLAlgGoodChrTrkSelector;

#endif
