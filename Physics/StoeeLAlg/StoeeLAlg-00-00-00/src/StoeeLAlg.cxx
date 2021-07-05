#include "StoeeLAlg/StoeeLAlg.h"
// #include "DataBaseReader/DataBaseReader.h"
// #include "DataBaseReader/RscanDQ.h"

using CLHEP::HepLorentzVector;
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif

using Event::McParticle;
using std::cout;
using std::endl;
using std::vector;

StatusCode StoeeLAlg::execute()
{
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "in execute()" << endmsg;

    SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),
                                                 "/Event/EventHeader");
    if (!eventHeader) {
        log << MSG::FATAL << "Could not find EvtHeader" << endmsg;
        return StatusCode::FAILURE;
    }
    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),
                                          "/Event/EvtRec/EvtRecEvent");
    if (!evtRecEvent) {
        log << MSG::FATAL << "Could not find EvtRecEvent" << endmsg;
        return StatusCode::FAILURE;
    }
    // Get Event Info

    m_run = eventHeader->runNumber();
    //-----mc idx
    if (m_run < 0 && m_fillMCInf) {
        fillDecayChain(m_indexmc, m_pdgid, m_motheridx, m_Mother);
        FillTruthInf(m_fid);
        mctp->write();
    }
    int chrTrks = evtRecEvent->totalCharged();
    if (chrTrks < m_minTrks) return StatusCode::SUCCESS;
    if (chrTrks > m_maxTrks) return StatusCode::SUCCESS;

    int showers = evtRecEvent->totalNeutral();
    if (showers < m_minShowers) return StatusCode::SUCCESS;
    if (showers > m_maxShowers) return StatusCode::SUCCESS;

    // return StatusCode::SUCCESS;

    if (!GetParList()) return StatusCode::SUCCESS;

    // round02  2009         -9947, -10878
    // round05  2012        -27255, -28236
    // round11  2017-2018   -52940, -54976; -55861, -56546
    // round12  2018-2019   -56788, -59015
    // RscanDQ rscanDQ(abs(m_run));
    // m_BeamE = rscanDQ.getEcm();
    // // cout<<"beamE Rscan: "<<m_BeamE<<endl;
    // DataBaseReader dataReader;
    // if (dataReader.isRunValid(abs(m_run))) {
    //     // cout<<"dataReader:"<<endl;
    //     m_BeamE = dataReader.getbeamE(abs(m_run), m_BeamE);
    //     // cout<<"beamE  "<<m_BeamE<<endl;
    // }
    m_beamE = m_BeamE / 2;
    SearchJpsi();
    return StatusCode::SUCCESS;
}

void StoeeLAlg::SearchJpsi()
{
    // SmartDataPtr<EvtRecTrackCol> evtRecTrackCol( eventSvc(),
    // "/Event/EvtRec/EvtRecTrackCol"); if ( ! evtRecTrackCol )  return ;

    SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),
                                                 "/Event/EventHeader");
    if (!eventHeader) return;

    SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),
                                          "/Event/EvtRec/EvtRecEvent");
    if (!evtRecEvent) return;

    m_run    = eventHeader->runNumber();
    m_events = eventHeader->eventNumber();

    CDDecayList ds(stoeeLAlgSignalSelector);
    ds = DecayList(m_fid);

    if (m_InfL >= 1) {
        ParticleInf pinf;
        cout << "The number of candidates:\t" << ds.size() << endl;
        if (m_InfL >= 2) {
            Print(ds);
        }
    }
    if (ds.empty()) return;

    CDDecayList::iterator begin = ds.particle_begin();
    CDDecayList::iterator best  = ds.particle_end();
    CDDecayList::iterator end   = ds.particle_end();
    double minQ = 1000, Q = 1000;
    for (CDDecayList::iterator itr = begin; itr != end; itr++) {
        const CDCandidate& aCandidate = (*itr).particle();
        if (m_InfL >= 5)
            cout << "chisq\t" << KinematicFit(aCandidate, m_fid) << endl;
        Q = KinematicFit(aCandidate, m_fid);
        if (Q < minQ) {
            minQ = Q;
            best = itr;
        }
    }
    if (best == end) return;
    const CDCandidate& aTag = (*best).particle();
    FillInf(aTag);
    tp->write();
}

bool StoeeLAlg::fromVee(const CDCandidate& sig, const int& pid)
{
    CDDecayList veeList = DecayList(pid);

    CDDecayList::iterator begin = veeList.particle_begin();
    CDDecayList::iterator end   = veeList.particle_end();
    for (CDDecayList::iterator itr = begin; itr != end; ++itr) {
        const CDCandidate& aVee = (*itr).particle();
        if (aVee.overlap(sig)) {
            return true;
        }
    }
    return false;
}
