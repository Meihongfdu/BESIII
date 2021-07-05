#include "HadronInfo/ParticleInf.hpp"
#include "StoeeLAlg/StoeeLAlg.h"

#include <algorithm>

using CLHEP::HepLorentzVector;
using std::find;

bool StoeeLAlg::GetParList()
{
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),
                                          "/Event/EvtRec/EvtRecEvent");
    if (!evtRecEvent) return false;

    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc(),
                                                "/Event/EvtRec/EvtRecTrackCol");
    if (!evtRecTrackCol) return false;

    EvtRecTrackIterator track_begin = evtRecTrackCol->begin();
    EvtRecTrackIterator track_end =
        evtRecTrackCol->begin() + evtRecEvent->totalCharged();
    // m_PhotonList.erase();
    // m_PionList.erase();
    // m_ProtonList.erase();
    // m_KaonList.erase();
    // m_Pi0List.erase();
    // m_EtaList.erase();
    // m_KsList.erase();

    ParticleInf particleInf;
    particleInf.SetChildren(m_fid);
    bool need_all = false;

    if (particleInf.NeedProton() || need_all) {
        CDProtonList protonList(track_begin, track_end,
                                stoeeLAlgProtonSelector);
        // if(protonList.empty() ) return false;
        m_ProtonList = protonList;
        if (m_InfL > 6) {
            cout << "need to reconstructe the " << particleInf.Name(2212)
                 << endl
                 << "And find " << protonList.size() << " candidates" << endl;
            // Print(protonList);
        }
    }

    if (particleInf.NeedPion() || need_all) {
        stoeeLAlgPionSelector.setpidtype(0);
        CDChargedPionList pionNopid(track_begin, track_end,
                                    stoeeLAlgPionSelector);
        stoeeLAlgPionSelector.setpidtype(1);
        CDChargedPionList pionList(track_begin, track_end,
                                   stoeeLAlgPionSelector);
        // if(pionNopid.empty()  )return false;
        m_PionList  = pionList;
        m_PionNoPid = pionNopid;
        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the" << particleInf.Name(211) << endl
                 << "And find " << pionList.size() << " candidates" << endl;
            // Print(pionList);
        }
    }

    if (particleInf.NeedKaon() || need_all) {
        CDChargedKaonList kaonList(track_begin, track_end,
                                   stoeeLAlgKaonSelector);
        // if(kaonList.empty() )return false;
        m_KaonList = kaonList;
        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the " << particleInf.Name(321) << endl
                 << "And find " << kaonList.size() << " candidates" << endl;
            // Print(kaonList);
        }
    }

    if (particleInf.NeedPi0() || need_all) {
        SmartDataPtr<EvtRecPi0Col> recPi0Col(eventSvc(),
                                             "/Event/EvtRec/EvtRecPi0Col");
        if (!recPi0Col) {
            return false;
        }
        CDPi0List pi0List(stoeeLAlgPi0Selector);
        dc_fill(pi0List, recPi0Col->begin(), recPi0Col->end());
        // if(pi0List.empty() )return false;
        m_Pi0List = pi0List;
        if (m_InfL > 6) {
            cout << "need to reconstructe the " << particleInf.Name(111) << endl
                 << "And find " << pi0List.size() << " candidates" << endl;
            // Print(pi0List);
        }
    }
    if (particleInf.NeedPhoton() || need_all) {
        vector<const EvtRecPi0*> _pi0s;
        CDDecayList::iterator begin = m_Pi0List.particle_begin();
        CDDecayList::iterator end   = m_Pi0List.particle_end();
        for (CDDecayList::iterator itr = begin; itr != end; itr++) {
            const CDCandidate& aPi0 = (*itr).particle();
            const EvtRecPi0* navPi0 = aPi0.decay().child(0).navPi0();
            _pi0s.push_back(navPi0);
        }
        EvtRecTrackIterator neu_begin =
            evtRecTrackCol->begin() + evtRecEvent->totalCharged();
        EvtRecTrackIterator neu_end = evtRecTrackCol->end();
        stoeeLAlgPhotonSelector.setPi0s(_pi0s);
        CDPhotonList photonList(neu_begin, neu_end, stoeeLAlgPhotonSelector);
        // if(photonList.empty() ) return false;
        m_PhotonList = photonList;

        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the" << particleInf.Name(22) << endl
                 << "And find " << m_PhotonList.size() << " gamma candidate"
                 << endl;
            // Print(m_PhotonList);
        }
    }

    if (particleInf.NeedEta() || need_all) {
        SmartDataPtr<EvtRecEtaToGGCol> evtRecEtaToGGCol(
            eventSvc(), "/Event/EvtRec/EvtRecEtaToGGCol");
        if (!evtRecEtaToGGCol) {
            return false;
        }
        CDEtaList etaList(stoeeLAlgEtatoGGSelector);
        dc_fill(etaList, evtRecEtaToGGCol->begin(), evtRecEtaToGGCol->end());
        // if(etaList.empty() )return false;
        m_EtaList = etaList;
        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the" << particleInf.Name(221) << endl
                 << "And find " << etaList.size() << " candidates" << endl;
        }
    }

    if (particleInf.NeedKs() || need_all) {
        SmartDataPtr<EvtRecVeeVertexCol> recVeeVertexCol(
            eventSvc(), "/Event/EvtRec/EvtRecVeeVertexCol");
        if (!recVeeVertexCol) {
            return false;
        }
        CDKsList ksList(stoeeLAlgKsSelector);
        dc_fill(ksList, recVeeVertexCol->begin(), recVeeVertexCol->end());
        // if(ksList.empty() )return false;
        m_KsList = ksList;
        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the " << particleInf.Name(310) << endl
                 << "And find " << ksList.size() << " candidates" << endl;
            // Print(ksList);
        }
    }

    if (particleInf.NeedElectron() || need_all) {
        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the" << particleInf.Name(11) << endl;
        }
        // Print(eList);
        CDElectronList eList(track_begin, track_end, stoeeLAlgElectronSelector);
        // if(eList.empty() )return false;
        m_ElectronList = eList;
        if (m_InfL > 6) {
            ParticleInf particleInf;
            cout << "need to reconstructe the" << particleInf.Name(11) << endl
                 << "And find " << eList.size() << " candidates" << endl;
            // Print(eList);
        }
    }
    return true;
}
CDDecayList StoeeLAlg::DecayList(int pid)
{
    // Ks 310 ; K 321 ; pion 211 ; Pi0 111 ; Eta 221 ; eta' 331
    // Lambda: 3122, etaV3pi 2212211, electron 11
    CDDecayList decayList;
    decayList.erase();
    if (pid == 310) {
        return m_KsList;
    }
    if (pid == 321) {
        decayList = m_KaonList.plus();
        return decayList;
    }
    if (pid == -321) {
        decayList = m_KaonList.minus();
        return decayList;
    }

    if (pid == 211) {
        decayList = m_PionList.plus();
        return decayList;
    }
    if (pid == 11) {
        decayList = m_ElectronList.plus();
        return decayList;
    }
    if (pid == -11) {
        decayList = m_ElectronList.minus();
        return decayList;
    }
    if (pid == -211) {
        decayList = m_PionList.minus();
        return decayList;
    }
    if (pid == 111) {
        decayList = m_Pi0List;
        return decayList;
    }
    if (pid == 221) {
        return m_EtaList;
    }
    if (pid == 22) {
        decayList = m_PhotonList;
        return decayList;
    }
    if (pid == 331) {
        return m_PionList.plus() * m_PionList.minus() * m_EtaList;
    }
    if (pid == 223) {
        return m_PionList.plus() * m_PionList.minus() * m_Pi0List;
    }
    if (pid == 333) {
        return m_KaonList.plus() * m_KaonList.minus();
    }
    if (pid == 2212) {
        decayList = m_ProtonList.plus();
        return decayList;
    }
    if (pid == -2212) {
        decayList = m_ProtonList.minus();
        return decayList;
    }
    if (pid == 3122) {
        CDDecayList lambda(lambdaSelector);
        lambda = m_ProtonList.plus() * m_PionNoPid.minus();
        return lambda;
    }
    if (pid == -3122) {
        CDDecayList lambda(lambdaSelector);
        lambda = m_ProtonList.minus() * m_PionNoPid.plus();
        return lambda;
    }
    if (pid == 2212211) {
        CDDecayList eta(stoeeLAlgEtatoPiPiPi0Selector);
        eta = m_PionList.plus() * m_PionList.minus() * m_Pi0List;
        return eta;
    }
    if (pid == 3212) {
        CDDecayList lambda(lambdaSelector);
        lambda = m_ProtonList.plus() * m_PionList.minus();
        CDDecayList sigma0(sigma0Selector);
        sigma0 = lambda * m_PhotonList;
        return sigma0;
    }
    if (pid == -3212) {
        CDDecayList lambda(lambdaSelector);
        lambda = m_ProtonList.minus() * m_PionList.plus();
        CDDecayList sigma0(sigma0Selector);
        sigma0 = lambda * m_PhotonList;
        return sigma0;
    }
    return decayList;
}
CDDecayList StoeeLAlg::DecayList(vector<int> fid)
{
    CDDecayList decayList;
    if (fid.size() == 1) {
        decayList = DecayList(fid[0]);
    } else if (fid.size() == 2) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]);
    } else if (fid.size() == 3) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]);
    } else if (fid.size() == 4) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]);
    } else if (fid.size() == 5) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]);
    } else if (fid.size() == 6) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]);
    } else if (fid.size() == 7) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]);
    } else if (fid.size() == 8) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]);
    } else if (fid.size() == 9) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]);
    } else if (fid.size() == 10) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                    DecayList(fid[9]);
    } else if (fid.size() == 11) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                    DecayList(fid[9]) * DecayList(fid[10]);
    } else if (fid.size() == 12) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                    DecayList(fid[9]) * DecayList(fid[10]) * DecayList(fid[11]);
    } else if (fid.size() == 13) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                    DecayList(fid[9]) * DecayList(fid[10]) *
                    DecayList(fid[11]) * DecayList(fid[12]);
    } else if (fid.size() == 14) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                    DecayList(fid[9]) * DecayList(fid[10]) *
                    DecayList(fid[11]) * DecayList(fid[12]) *
                    DecayList(fid[13]);
    } else if (fid.size() == 15) {
        decayList = DecayList(fid[0]) * DecayList(fid[1]) * DecayList(fid[2]) *
                    DecayList(fid[3]) * DecayList(fid[4]) * DecayList(fid[5]) *
                    DecayList(fid[6]) * DecayList(fid[7]) * DecayList(fid[8]) *
                    DecayList(fid[9]) * DecayList(fid[10]) *
                    DecayList(fid[11]) * DecayList(fid[12]) *
                    DecayList(fid[13]) * DecayList(fid[14]);
    }
    return decayList;
}
