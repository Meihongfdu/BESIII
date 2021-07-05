#ifndef Ecmset_selection_H 
#define Ecmset_selection_H

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"

class  Ecmset 
{

 public:

  ~Ecmset(){;}
  static Ecmset* instance();

  void EcmSet(int run);

  double ECM() const {return   Ecm;}

  private:
  Ecmset(){;}
  static Ecmset *m_pointer;

  double  Ecm;
};

#endif

