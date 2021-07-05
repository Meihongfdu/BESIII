#include "mmppetapAlg/util/MyIsGoodtrack.h"

bool isGoodTrack(EvtRecTrack* trk, Hep3Vector xorigin, double& costheta){
  if(!(trk->isMdcTrackValid())) return false;
  if(!(trk->isMdcKalTrackValid())) return false;

  RecMdcTrack *mdcTrk = trk->mdcTrack();
  HepVector    a   = mdcTrk->helix();
  HepSymMatrix Ea  = mdcTrk->err();
  HepPoint3D pivot(0.,0.,0.);
  HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
  VFHelix helixp(pivot,a,Ea);
  helixp.pivot(IP);
  HepVector vec    = helixp.a();
  double    vrl    = vec[0];
  double    vzl    = vec[3];
  costheta         = cos(mdcTrk->theta());

	RecMdcKalTrack *mdcKalTrk = trk->mdcKalTrack();
	if(mdcKalTrk->charge() == 0) return false; 

  if(fabs(vrl) < 1 && fabs(vzl) < 10 && fabs(costheta) < 0.93)
    return true;
  return false;
}

