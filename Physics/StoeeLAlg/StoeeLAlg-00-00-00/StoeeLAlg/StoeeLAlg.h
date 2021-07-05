#ifndef Physics_Analysis_StoeeLAlg_H
#define Physics_Analysis_StoeeLAlg_H

//#include "StoeeLAlg/util/MyUtil.h"
#include "StoeeLAlg/util/current.h"
#include "HadronInfo/ParticleInf.hpp"
#include "StoeeLAlg/util/ReadBeamInfFromDb.h"

#include "StoeeLAlg/Selector/StoeeLAlgElectronSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgEptoPiPiEtaSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgEtatoGGSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgEtatoPiPiPi0Selector.h"
#include "StoeeLAlg/Selector/StoeeLAlgGoodChrTrkSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgKaonSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgKsSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgLambdaSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgPhotonSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgPi0Selector.h"
#include "StoeeLAlg/Selector/StoeeLAlgPionSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgProtonSelector.h"
#include "StoeeLAlg/Selector/StoeeLAlgSigma0Selector.h"
#include "StoeeLAlg/Selector/StoeeLAlgSignalSelector.h"

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"

#include "BesDChain/CDChargedKaonList.h"
#include "BesDChain/CDChargedPionList.h"
#include "BesDChain/CDDecay.h"
#include "BesDChain/CDDecayList.h"
#include "BesDChain/CDElectronList.h"
#include "BesDChain/CDKsList.h"
#include "BesDChain/CDLambdaList.h"
#include "BesDChain/CDPhotonList.h"
#include "BesDChain/CDPi0List.h"
#include "BesDChain/CDProtonList.h"

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "CLHEP/Geometry/Point3D.h"
#include "McDecayModeSvc/McDecayModeSvc.h"
#include "McTruth/McParticle.h"
#include "MdcRecEvent/RecMdcKalTrack.h"
#include "MucRecEvent/RecMucTrack.h"
#include "ParticleID/ParticleID.h"
#include "VertexFit/Helix.h"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/WTrackParameter.h"

#include "TMath.h"

#include "GaudiKernel/IHistogramSvc.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/TwoVector.h"

#include "EventModel/Event.h"
#include "EventModel/EventHeader.h"
#include "EventModel/EventModel.h"
#include "EventNavigator/EventNavigator.h"

#include "DstEvent/TofHitStatus.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"

#include "EvTimeEvent/RecEsTime.h"
#include "EvtRecEvent/EvtRecEtaToGG.h"
#include "EvtRecEvent/EvtRecPi0.h"
#include "EvtRecEvent/EvtRecVeeVertex.h"

// EMC reconstructed data
#include "EmcRecEventModel/RecEmcShower.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/SmartDataPtr.h"

//-----------------------------------------
// EventNavigator

#include "McDecayModeSvc/McDecayModeSvc.h"

#include "MCTruthMatchSvc/MCTruthMatchSvc.h"

#include "EventModel/Event.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "VertexFit/IVertexDbSvc.h"

#include "McTruth/McParticle.h"
#include "VertexFit/Helix.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/VertexFit.h"

#include "BesDChain/CDChargedKaonList.h"
#include "BesDChain/CDChargedPionList.h"
#include "BesDChain/CDDecay.h"
#include "BesDChain/CDDecayList.h"
#include "BesDChain/CDElectronList.h"
#include "BesDChain/CDEtaList.h"
#include "BesDChain/CDLambdaList.h"
#include "BesDChain/CDPhotonList.h"
#include "BesDChain/CDPi0List.h"
#include "BesDChain/CDProtonList.h"

#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"

using CLHEP::HepLorentzVector;
using std::vector;

class StoeeLAlg : public Algorithm
{
  public:
    StoeeLAlg(const std::string& name, ISvcLocator* pSvcLocator);
    StatusCode initialize();
    StatusCode execute();
    StatusCode finalize();

  private:
    bool m_debug;
    double m_BeamE;
    int m_minTrks, m_maxTrks, m_minShowers, m_maxShowers, m_InfL, m_Mother;
    bool m_findGamma;
    // template<typename T> void Print(T ll) ;
    void Print(CDDecayList);
    double KinematicFit(const CDCandidate&, vector<int>);
    void AddWTrack(const CDCandidate& aChild, const int& pid,
                   vector<WTrackParameter>& wtrks, vector<int>& child,
                   vector<double>& resmass, vector<vector<int> >& cList);
    void FillPi0Inf(const CDCandidate&);
    void FillEtaInf(const CDCandidate&);
    void FillLamInf(const CDCandidate&);
    void FillTruthInf(vector<int> m_fid);
    bool fromVee(const CDCandidate& sig, const int& pid);
    int GoodShowers();
    int GoodTracks();
    void FillFinalPar(const CDCandidate& tag);
    vector<int> m_fid;
    CDDecayList m_Pi0List;
    CDDecayList m_EtaList;
    CDDecayList m_PhotonList;
    CDProtonList m_ProtonList;
    CDElectronList m_ElectronList;
    CDLambdaList m_LambdaList;
    CDDecayList m_KsList;
    CDDecayList m_DsList;

    CDDecayList DecayList(int);
    CDDecayList DecayList(vector<int> fid);

    CDChargedPionList m_PionList, m_PionNoPid;
    CDChargedKaonList m_KaonList;

    vector<std::string> _parname;

    vector<std::string> NamePar(vector<int> _fid);
    void GetDsList(int);
    void SearchJpsi();
    bool GetParList();
    int match(const CDCandidate&);
    void FillInf(const CDCandidate&);
    void FillGammaCovInf(const CDCandidate& signal);

    void fillDecayChain(NTuple::Item<int>&, NTuple::Array<int>&,
                        NTuple::Array<int>&, int);
    inline void fillDecayChain()
    {
        fillDecayChain(tag_indexmc, tag_pdgid, tag_motheridx, m_Mother);
    }
    void getDecayChain(vector<int>& n_pdgid, vector<int>& n_motheridx,
                       int thePdgId);
    void fillP4(NTuple::Array<double> m_p4, HepLorentzVector p4);
    bool m_doMatch;
    bool m_seleBestLmda;
    bool m_fillMCInf;
    int m_minMethod;
    int m_Tag;
    int m_SigMode;
    int m_SigCharge;
    McDecayModeSvc* m_svc;
    MCTruthMatchSvc* matchSvc;
    NTuple::Tuple *tp, *mctp;

    NTuple::Item<int> m_run, m_tracks, m_events, m_charge, m_NShowers, m_match,
        tag_indexmc, m_indexmc;
    NTuple::Array<int> tag_pdgid, tag_motheridx, m_pdgid, m_motheridx;

    NTuple::Item<double> m_beamE, m_chisq, m_mass[10], m_Rxy[10], m_Vz0[10],
        m_CosTheta[10], m_unconm[8], m_chisqs[8], m_GammaCov_Rxy[10],
        m_GammaCov_Rx[10], m_GammaCov_Ry[10], m_mLamCol[4], m_RLamCol[4],
        m_dLamCol[4], m_chisq1LamCol[4], m_chisq2LamCol[4], m_RxyPrLam[4],
        m_Vz0PrLam[4], m_CosThetaPrLam[4], m_RxyPiLam[4], m_Vz0PiLam[4],
        m_CosThetaPiLam[4];

    NTuple::Array<double> m_p4[20], m_fitP4[20], m_truthP4[20], m_p4PrLamCol[4],
        m_p4PiLamCol[4], m_helixEp, m_helixEm;
};

#endif // Physics_Analysis_StoeeLAlg_H
