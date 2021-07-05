#ifndef StoeeLAlg_PHOTON_SELECTOR_H
#define StoeeLAlg_PHOTON_SELECTOR_H

#include "BesDChain/CDPhoton.h"
#include "BesDChain/BesDCSelector.h"
#include "EvtRecEvent/EvtRecPi0.h"
#include <iostream>
using std::vector;

class StoeeLAlgPhotonSelector : public BesDCSelector<CDPhoton>
{
   public :

      StoeeLAlgPhotonSelector();

      bool operator() (CDPhoton& aPhoton);
      void setPi0s(vector<const EvtRecPi0*> m_pi0s);
      inline void SetEnergy(double e){ 
                    m_energy = e ; }


   private :

      double m_energy ;
      bool m_vetoPi0;
      bool FromPi0(int id, vector<const EvtRecPi0*> m_pi0s);
      vector<const EvtRecPi0*> m_pi0s;

      StoeeLAlgPhotonSelector( const StoeeLAlgPhotonSelector& );
      const StoeeLAlgPhotonSelector& operator= ( const StoeeLAlgPhotonSelector& );

      double m_minEnergy;
 
      bool   m_useBarrelEndcap;
      double m_maxCosThetaBarrel;
      double m_minCosThetaEndcap;
      double m_maxCosThetaEndcap;
      double m_minEndcapEnergy;
 
      bool   m_applyTimeCut;
      double m_minTime;
      double m_maxTime;
      double m_deltaTime;
 
      bool m_applyDangCut;
      double m_minDang;
};

extern StoeeLAlgPhotonSelector stoeeLAlgPhotonSelector;

#endif
