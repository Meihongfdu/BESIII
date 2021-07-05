#include "StoeeLAlg/Selector/StoeeLAlgSignalSelector.h"

using CLHEP::Hep3Vector;
using CLHEP::HepLorentzVector;

using namespace std;

StoeeLAlgSignalSelector::StoeeLAlgSignalSelector()
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;
    m_propMgr.declareProperty("UseMassCuts", m_useMbcCuts = false);
    m_propMgr.declareProperty("MinMass", m_minMass = 1.90);
    m_propMgr.declareProperty("MaxMass", m_maxMass = 2.04);
    m_propMgr.declareProperty("UseRecMassCuts", m_useRecCuts = false);
    m_propMgr.declareProperty("MinRecMass", m_minRecMass = 2.0);
    m_propMgr.declareProperty("MaxRecMass", m_maxRecMass = 2.2);

    jobSvc->setMyProperties("StoeeLAlgSignalSelector", &m_propMgr);
    m_beamE = 4.178 / 2;
}

bool StoeeLAlgSignalSelector::operator()(CDDecay& aJpsi)
{
    if (m_useMbcCuts) {
        double mass = aJpsi.mass();
        if (mass < m_minMass || mass > m_maxMass) return false;
    }
    if (m_useRecCuts) {
        HepLorentzVector p4beam(0, 0, 0, 2 * m_beamE);
        HepLorentzVector p4Ds = aJpsi.p4();
        p4Ds.boost(-0.011, 0, 0);
        double mrec = (p4beam - p4Ds).m();
        if (mrec < m_minRecMass || mrec > m_maxRecMass) {
            return false;
        }
    }
    return true;
}

StoeeLAlgSignalSelector stoeeLAlgSignalSelector;
