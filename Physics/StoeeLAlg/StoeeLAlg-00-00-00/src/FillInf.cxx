#include "StoeeLAlg/Selector/StoeeLAlgGoodChrTrkSelector.h"
#include "StoeeLAlg/StoeeLAlg.h"

#include "HadronInfo/EtaInfo.hpp"
#include "HadronInfo/LamInfo.hpp"
#include "HadronInfo/Pi0Info.hpp"

#include "GammaConv/GammaConv.h"

#include <map>

using CLHEP::HepLorentzVector;
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif

using Event::McParticle;
using Event::McParticleCol;
using std::cout;
using std::endl;
using std::map;
using std::vector;

typedef NTuple::Item<double> NIdouble;
typedef NTuple::Array<double> NAdouble;
void StoeeLAlg::FillInf(const CDCandidate& tag)
{
    m_chisq    = this->KinematicFit(tag, m_fid);
    m_tracks   = this->GoodTracks();
    m_NShowers = this->GoodShowers();
    this->FillFinalPar(tag);
    this->FillPi0Inf(tag);
    this->FillEtaInf(tag);
    this->FillLamInf(tag);
    this->FillGammaCovInf(tag);
    if (m_run > 0) return;
    m_match = this->match(tag);
    // this->fillDecayChain(tag.charge());
    this->fillDecayChain();
}
void StoeeLAlg::FillFinalPar(const CDCandidate& tag)
{
    for (unsigned i = 0; i < m_fid.size(); i++) {
        if (abs(m_fid[i]) == 211 || abs(m_fid[i]) == 321 ||
            abs(m_fid[i]) == 11 || abs(m_fid[i]) == 2212 ||
            abs(m_fid[i]) == 111 || abs(m_fid[i]) == 22 ||
            abs(m_fid[i]) == 221) {
            continue;
        }
        m_mass[i] = tag.decay().child(i).mass();
    }

    for (unsigned i = 0; i < m_fid.size(); i++) {
        if (abs(m_fid[i]) == 211 || abs(m_fid[i]) == 321 ||
            abs(m_fid[i]) == 11 || abs(m_fid[i]) == 2212 ||
            abs(m_fid[i]) == 13) {

            if (m_InfL > 10) {
                std::cout << i << ", " << m_fid[i] << std::endl;
                std::cout << tag.decay().child(i).finalChildren().first.size()
                          << std::endl;
                std::cout << tag.decay().child(i).finalChildren().second.size()
                          << std::endl;
            }
            EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(
                tag.decay().child(i).finalChildren().first[0]);
            // no need in this final stage
            // // MDC track selection
            // if (!recTrk->isMdcKalTrackValid()) {
            //     cout << __func__ << "mdcnotvalid" << endl;
            //     return false;
            // }
            RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
            switch (abs(m_fid[i])) {
                case 11: {
                    RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
                    // no need in this final stage
                    // if (mdcKalTrk->charge() == 0) return false;
                    // HepLorentzVector p4Ele = mdcKalTrk->p4(0.0005109989);
                    break;
                }
                case 211: {
                    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
                    // no need in this final stage
                    // if (mdcKalTrk->charge() == 0) return false;
                    // HepLorentzVector p4Ele = mdcKalTrk->p4(0.139570);
                    break;
                }
                case 321: {
                    RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);
                    // no need in this final stage
                    // if (mdcKalTrk->charge() == 0) return false;
                    // HepLorentzVector p4Ele = mdcKalTrk->p4(0.49368);
                    break;
                }
                case 2212: {
                    RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
                    // no need in this final stage
                    // if (mdcKalTrk->charge() == 0) return false;
                    // HepLorentzVector p4Ele = mdcKalTrk->p4(0.9382723);
                    break;
                }
                case 13: {
                    RecMdcKalTrack::setPidType(RecMdcKalTrack::muon);
                    // no need in this final stage
                    // if (mdcKalTrk->charge() == 0) return false;
                    // HepLorentzVector p4Ele = mdcKalTrk->p4(0.1056584);
                    break;
                }
                default: { // default is electron
                    RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
                    // no need in this final stage
                    // if (mdcKalTrk->charge() == 0) return false;
                    // HepLorentzVector p4Ele = mdcKalTrk->p4(0.0005109989);
                }
            }

            Hep3Vector xorigin(0, 0, 0);
            IVertexDbSvc* vtxsvc;
            Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
            if (vtxsvc->isVertexValid()) {
                double* dbv = vtxsvc->PrimaryVertex();
                // double* vv  = vtxsvc->SigmaPrimaryVertex();
                xorigin.setX(dbv[0]);
                xorigin.setY(dbv[1]);
                xorigin.setZ(dbv[2]);
            }
            HepVector a     = mdcKalTrk->helix();
            HepSymMatrix Ea = mdcKalTrk->err();
            HepPoint3D point0(0.0, 0.0, 0.0);
            HepPoint3D IP(xorigin[0], xorigin[1], xorigin[2]);
            VFHelix helixip3(point0, a, Ea);
            helixip3.pivot(IP);
            HepVector vecipa = helixip3.a();

            m_Rxy[i]      = abs(vecipa[0]);
            m_Vz0[i]      = abs(vecipa[3]);
            m_CosTheta[i] = cos(mdcKalTrk->theta());
        }
    }

    for (unsigned i = 0; i < m_fid.size(); i++) {
        fillP4(m_p4[i], tag.decay().child(i).p4());
        if (m_InfL >= 4) {
            cout << "child\t" << i << "\t" << tag.decay().child(i).p4() << endl;
        }
    }
}
void StoeeLAlg::FillGammaCovInf(const CDCandidate& signal)
{
    ParticleInf particleInf;
    particleInf.SetChildren(m_fid);
    vector<int> eleIds = particleInf.GammaCov();
    if (eleIds.empty()) return;

    // IVertexDbSvc* vtxsvc;
    // Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    // double* dbv = vtxsvc->PrimaryVertex();
    // double* vv  = vtxsvc->SigmaPrimaryVertex();
    // HepPoint3D IP(dbv[0], dbv[1], dbv[2]);

    // To get the position where gamma conversion happens, one needs to
    // calculate it from detector's space origin (0, 0, 0), thus can determine
    // whether it locates in detector materials or the inner vacuum since gamma
    // conversion only occurs in detector materials i.e. gamma interacts with
    // those materials to generate electrons and positrons.
    HepPoint3D IP(0, 0, 0);

    for (unsigned i = 0; i < eleIds.size() / 2; i++) {
        const CDCandidate& E1   = signal.decay().child(eleIds[i]);
        const CDCandidate& E2   = signal.decay().child(eleIds[i + 1]);
        const EvtRecTrack* trk1 = E1.finalChildren().first[0];
        const EvtRecTrack* trk2 = E2.finalChildren().first[0];
        HepVector helix1 =
            const_cast<EvtRecTrack*>(trk1)->mdcKalTrack()->getZHelixE();
        HepVector helix2 =
            const_cast<EvtRecTrack*>(trk2)->mdcKalTrack()->getZHelixE();
        GammaConv gammaConv(helix1, helix2, IP);
        m_GammaCov_Rxy[i] = gammaConv.getRxy();
        m_GammaCov_Rx[i]  = gammaConv.getRx();
        m_GammaCov_Ry[i]  = gammaConv.getRy();
        for (int i = 0; i < 5; ++i) {
            m_helixEp[i] = helix1[i];
            m_helixEm[i] = helix2[i];
        }
    }
}
void StoeeLAlg::FillPi0Inf(const CDCandidate& tag)
{
    for (unsigned i = 0; i < m_fid.size(); i++) {
        if (m_fid[i] == 111) {
            const CDCandidate& aPi0 = tag.decay().child(i);
            Pi0Info pi0Inf(aPi0.finalChildren().second);
            m_chisqs[i] = pi0Inf.chisq();
            m_mass[i]   = pi0Inf.m();
            continue;
        }
    }
}
void StoeeLAlg::FillEtaInf(const CDCandidate& tag)
{
    for (unsigned i = 0; i < m_fid.size(); i++) {
        if (m_fid[i] == 221) {
            const CDCandidate& aEta = tag.decay().child(i);
            EtaInfo etaInf(aEta.finalChildren().second);
            m_chisqs[i] = etaInf.chisq();
            m_mass[i]   = etaInf.m();
        }
    }
}
void StoeeLAlg::FillLamInf(const CDCandidate& tag)
{
    int index = 0;
    for (unsigned i = 0; i < m_fid.size(); ++i) {
        if (abs(m_fid[i]) != 3122) {
            continue;
        }
        const CDCandidate& aLam = tag.decay().child(i);
        LamInfo lamInf(aLam.finalChildren().first[0],
                       aLam.finalChildren().first[1]);
        m_mLamCol[index]      = lamInf.m();
        m_RLamCol[index]      = lamInf.decayLengthRatio();
        m_dLamCol[index]      = lamInf.decayLength();
        m_chisq1LamCol[index] = lamInf.vtxChi2();
        m_chisq2LamCol[index] = lamInf.chisq();
        m_RxyPrLam[index] = lamInf.rxypr();
        m_Vz0PrLam[index] = lamInf.vz0pr();
        m_CosThetaPrLam[index] = lamInf.costpr();
        m_RxyPiLam[index]      = lamInf.rxypi();
        m_Vz0PiLam[index]      = lamInf.vz0pi();
        m_CosThetaPiLam[index] = lamInf.costpi();
        fillP4(m_p4PrLamCol[index], lamInf.p4child(0));
        fillP4(m_p4PiLamCol[index], lamInf.p4child(1));
        index += 1;
    }
}

void StoeeLAlg::fillP4(NTuple::Array<double> m_p4, HepLorentzVector p4)
{
    for (int i = 0; i < 4; i++)
        m_p4[i] = p4[i];
}

void StoeeLAlg::fillDecayChain(NTuple::Item<int>& nt_idxmc,
                               NTuple::Array<int>& nt_pdgid,
                               NTuple::Array<int>& nt_motheridx, int thePdgId)
{
    SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),
                                                     "/Event/MC/McParticleCol");
    int m_numParticle = 0;
    if (!mcParticleCol) {
        cout << "Could not retrieve McParticelCol" << endl;
        return;
    } else {
        std::vector<int> pdgid;
        std::vector<int> motherindex;
        pdgid.clear();
        motherindex.clear();

        Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
        for (; iter_mc != mcParticleCol->end(); iter_mc++) {
            if ((*iter_mc)->particleProperty() == thePdgId) {
                m_svc->extract(*iter_mc, pdgid, motherindex);
                m_numParticle = pdgid.size();
                for (unsigned i = 0; i != pdgid.size(); i++) {
                    nt_pdgid[i]     = pdgid[i];
                    nt_motheridx[i] = motherindex[i];
                }
                break;
            }
        }
        nt_idxmc        = m_numParticle;
        nt_motheridx[0] = -1;

        return;
    }
}
void StoeeLAlg::getDecayChain(vector<int>& n_pdgid, vector<int>& n_motheridx,
                              int thePdgId)
{
    SmartDataPtr<McParticleCol> mcParticleCol(eventSvc(),
                                              "/Event/MC/McParticleCol");
    if (!mcParticleCol) {
        cout << "Could not retrieve McParticelCol" << endl;
        return;
    }
    n_pdgid.erase(n_pdgid.begin(), n_pdgid.end());
    n_motheridx.erase(n_motheridx.begin(), n_motheridx.end());

    for (McParticleCol::iterator itr = mcParticleCol->begin();
         itr != mcParticleCol->end(); itr++) {
        if ((*itr)->particleProperty() == thePdgId) {
            m_svc->extract(*itr, n_pdgid, n_motheridx);
            break;
        }
    }
    if (n_motheridx.empty()) return;
    n_motheridx[0] = -1;
}
int StoeeLAlg::match(const CDCandidate& aTag)
{
    // int charge = aTag.charge();
    vector<int> pdg, dechain;
    getDecayChain(pdg, dechain, m_Mother);
    vector<int> TrkIds;
    vector<int> ShowerIds;
    for (unsigned i = 0; i < aTag.finalChildren().second.size(); i++) {
        ShowerIds.push_back(22);
    }

    vector<const EvtRecTrack*> tracks;
    ParticleInf pinf;
    for (unsigned i = 0; i < m_fid.size(); i++) {
        vector<int> pids = pinf.ChargedChildren(m_fid[i]);
        vector<const EvtRecTrack*> chrTrks =
            aTag.decay().child(i).finalChildren().first;
        for (unsigned j = 0; j < pids.size(); j++) {
            tracks.push_back(chrTrks[j]);
            TrkIds.push_back(pids[j]);
        }
    }

    if (matchSvc->match(tracks, TrkIds, pdg, dechain)) {
        if (matchSvc->match(aTag.finalChildren().second, ShowerIds, pdg,
                            dechain)) {
            return 2;
        }
        return 1;
    }
    return 0;
}
void StoeeLAlg::FillTruthInf(vector<int> m_fid)
{
    vector<HepLorentzVector> p4List;

    SmartDataPtr<McParticleCol> mcParticleCol(eventSvc(),
                                              "/Event/MC/McParticleCol");
    if (!mcParticleCol) {
        cout << "Could not retrieve McParticelCol" << endl;
        return;
    }

    for (McParticleCol::iterator itr = mcParticleCol->begin();
         itr != mcParticleCol->end(); ++itr) {

        int aPID = (*itr)->particleProperty();
        for (unsigned i = p4List.size(); i < m_fid.size(); i++) {
            if (m_fid[i] == aPID) {
                HepLorentzVector p4 = (*itr)->initialFourMomentum();
                p4List.push_back(p4);
                break;
            }
        }
    }
    if (p4List.size() < m_fid.size()) {
        // cout<<"missing some particle"<<endl;
        return;
    }
    for (unsigned i = 0; i < m_fid.size(); i++) {
        fillP4(m_truthP4[i], p4List[i]);
    }
}
int StoeeLAlg::GoodTracks()
{
    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc(),
                                                "/Event/EvtRec/EvtRecTrackCol");
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),
                                          "/Event/EvtRec/EvtRecEvent");

    EvtRecTrackIterator track_begin = evtRecTrackCol->begin();
    EvtRecTrackIterator track_end =
        evtRecTrackCol->begin() + evtRecEvent->totalCharged();
    CDElectronList goodTrkList(track_begin, track_end,
                               stoeeLAlgGoodChrTrkSelector);
    return goodTrkList.size();
}
int StoeeLAlg::GoodShowers()
{
    SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc(),
                                                "/Event/EvtRec/EvtRecTrackCol");
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),
                                          "/Event/EvtRec/EvtRecEvent");
    EvtRecTrackIterator neu_begin =
        evtRecTrackCol->begin() + evtRecEvent->totalCharged();
    EvtRecTrackIterator neu_end = evtRecTrackCol->end();
    CDPhotonList photonList(neu_begin, neu_end, stoeeLAlgPhotonSelector);
    return photonList.size();
}
