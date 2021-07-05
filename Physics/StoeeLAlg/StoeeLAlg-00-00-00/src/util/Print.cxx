#include "StoeeLAlg/StoeeLAlg.h"
#include <iterator>
using std::cout;
using std::endl;
using std::iterator;

//emplate<typename T> void StoeeLAlg::Print(T ll) { 
//   cout<<"========== this is all information about this decaylist ============="<<endl;
//   cout<<"######################  begind ##########################"<<endl;
//   typename T::iterator itr;
//   for( itr = ll.particle_begin() ; itr!=ll.particle_end() ; itr++){
//       const CDCandidate& aP = (*itr).particle() ;
//       cout<<"# "<<aP.mass()<<"\tP4:\t"<<aP.p4()<<endl;
//   }
//   cout<<"######################  E N D ##########################"<<endl;
//
void StoeeLAlg::Print(CDDecayList ll) { 
    cout<<"========== this is all information about this decaylist ============="<<endl;
    cout<<"######################  begind ##########################"<<endl;
    CDDecayList::iterator itr = ll.particle_begin();
    for( itr ; itr!=ll.particle_end() ; itr++){
        const CDCandidate& aP = (*itr).particle() ;
        cout<<"# "<<aP.mass()<<"\tP4:\t"<<aP.p4()<<endl;
    }
    cout<<"######################  E N D ##########################"<<endl;
}

