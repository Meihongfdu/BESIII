#ifndef StoeeLAlg_Electron_SELECTOR_H
#define StoeeLAlg_Electron_SELECTOR_H

#include "BesDChain/CDElectron.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class StoeeLAlgElectronSelector : public DCSelectionFunction<CDElectron>
{
  public:
    StoeeLAlgElectronSelector();

    bool operator()(CDElectron& aEle);
    inline void setcharge(int chr) { m_charge = chr; }

  private:
    StoeeLAlgElectronSelector(const StoeeLAlgElectronSelector&);
    const StoeeLAlgElectronSelector& operator=(
        const StoeeLAlgElectronSelector&);

    int m_charge;
    int m_pidtype;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    double m_minEvP;

    bool m_PID;
    bool m_VCut;
    bool m_CutEvP;
};

extern StoeeLAlgElectronSelector stoeeLAlgElectronSelector;

#endif // StoeeLAlg_Electron_SELECTOR_H
