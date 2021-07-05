#ifndef MY_TRK_H
#define MY_TRK_H
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"
#include "GaudiKernel/NTuple.h"

bool fillChargedTrkInfo (EvtRecTrack* track1, NTuple::Matrix<double>& nt_M4, NTuple::Matrix<double>& m_m, int type, int i);
bool fillChargedTrkInfos (EvtRecTrack* track1, NTuple::Array<double>& nt_M4, NTuple::Array<double>& m_m, int type );


#endif



