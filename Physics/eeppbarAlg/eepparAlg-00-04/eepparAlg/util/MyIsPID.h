#ifndef MY_ISPID_H
#define MY_ISPID_H
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"
#include "GaudiKernel/NTuple.h"

//bool isElectron(EvtRecTrack* recTrk, NTuple::Array<double>& prod_mu);
bool isElectron(EvtRecTrack* recTrk, NTuple::Array<double>& prod_mu, int s);
bool isMuon(EvtRecTrack* recTrk);
bool isMuon(EvtRecTrack* recTrk, vector<double>& prod_e);
bool isPion(EvtRecTrack* recTrk, NTuple::Matrix<double>& prod_mu, int s, int i);
bool isPion(EvtRecTrack* recTrk);
bool isKaon(EvtRecTrack* recTrk);
bool isProton(EvtRecTrack* recTrk, NTuple::Matrix<double>& prod_mu, int s);

#endif



