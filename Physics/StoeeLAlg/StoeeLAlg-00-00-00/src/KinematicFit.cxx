#include "StoeeLAlg/StoeeLAlg.h"
#include "HadronInfo/TrackInfo.hpp"
#include "HadronInfo/KsInfo.hpp"
#include "HadronInfo/LamInfo.hpp" 
#include "HadronInfo/Pi0Info.hpp"
#include "HadronInfo/EtaInfo.hpp"
double StoeeLAlg::KinematicFit(const CDCandidate& sig, vector<int> fid) 
{
    vector<WTrackParameter> wtrks;
    vector< double > resmass ; 
    vector< vector<int>  > cList;
    vector<int> childsize;

    for(int i=0; i<fid.size(); i++){
        const CDCandidate& aChild = sig.decay().child(i);
        int PID = abs(fid[i]);
        AddWTrack(aChild, PID,  wtrks, childsize, resmass, cList);
    }

    vector<int> dstrk;
    for(int i=0;i<wtrks.size();i++){
        dstrk.push_back(i);
    }
    KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();
    kmfit->init();
    for(int i=0;i<wtrks.size();i++){
        kmfit->AddTrack(i, wtrks[i]); 
    }
    HepLorentzVector p4tot(m_BeamE*0.011, 0, 0, m_BeamE);
    kmfit->AddFourMomentum(0, p4tot);
    kmfit->Fit(0);

    double  m_sig_chisq = kmfit->chisq(0);
    //cout<<"chisq: "<<m_sig_chisq<<endl;
    int index=0;
    for(int i=0; i< fid.size();++i){
        int size = childsize[i];
        HepLorentzVector p4(0,0,0,0);
        for(int j=0; j< size; j++ ){
            p4 += kmfit->pfit(index);
            //cout<<"p4 in fit "<<index<<kmfit->pfit(index)<<endl;
            index++;
        }
        fillP4(m_fitP4[i], p4);
    }
    return m_sig_chisq;
}
void StoeeLAlg::AddWTrack(const CDCandidate &aChild, 
        const int &PID, 
        vector<WTrackParameter> &wtrks, 
        vector<int> &child,
        vector< double > &resmass , 
        vector< vector<int>  > &cList )
{
    if( PID == 310){
        KsInfo ksInfo(aChild);
        //wtrks.push_back( ksInfo.wtrk(0) );
        //wtrks.push_back( ksInfo.wtrk(1) );
        wtrks.push_back( ksInfo.wtrk());
        child.push_back(1);
        return ;
    }
    if(PID == 321 || PID == 211 || PID == 2212 
            || PID == 11 || PID == 13 ){
        TrackInfo trackInf(aChild);
        wtrks.push_back(trackInf.wtrk( PID ));
        child.push_back(1);
        // cout<<"PID="<<PID<<trackInf.wtrk(PID)<<endl;
        return;
    }
    if(PID == 22){
       TrackInfo trackInf;
       const EvtRecTrack* shower = aChild.finalChildren().second[0];
       wtrks.push_back(trackInf.wtrkc(shower, 22));
       child.push_back(1);
       return;
    }
    if(PID == 111){
        Pi0Info pi0Inf(aChild);
        wtrks.push_back(pi0Inf.wtrk());
        child.push_back(1);
        //   cout<<"PID="<<PID<<pi0Inf.wtrk()<<endl;
        return;
    }
    if(PID==221){
        EtaInfo etaInfo(aChild);
        wtrks.push_back(etaInfo.wtrk());
        child.push_back(1);
        return;
    }
    if(PID==3122){
        LamInfo lamInfo(aChild);
        //wtrks.push_back( ksInfo.wtrk(0) );
        //wtrks.push_back( ksInfo.wtrk(1) );
        wtrks.push_back( lamInfo.wtrk());
        child.push_back(1);
        return;
    }
    cout<<"KinematicFit::AddWTrack Error:: the particle: "
        <<PID<<" should be defines fisrt"<<endl;
}
