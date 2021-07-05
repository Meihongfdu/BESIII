#ifndef Physics_Analysis_Dstoetamv_H
#define Physics_Analysis_Dstoetamv_H 
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
//#include "VertexFit/ReadBeamParFromDb.h"
#include "DstoetamvAlg/ReadBeamInfFromDb.h"
#include "DstoetamvAlg/Match.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/KinematicFit.h"

class Dstoetamv : public Algorithm {

public:
  Dstoetamv(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();  

typedef std::vector<int> Vint;
typedef std::vector<double> Vdou;
typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<WTrackParameter> Vtrack;

void set0();
bool Same(Vint totid);
  // 
private:
  double m_gammaAngleCut;
  int m_mctag;
  bool m_ReadBeamEFromDB;
 
 
 
  NTuple::Tuple*  m_tuple0;
  NTuple::Item<int>       event_temp0;
  NTuple::Item<int>         run_temp0;
  NTuple::Item<int>     mcmode1_temp0;
  NTuple::Item<int>     mcmode2_temp0;
  NTuple::Item<int>     mcmodea_temp0;
  NTuple::Item<int>     mcmodeb_temp0;
  NTuple::Item<int>   tagcharge_temp0;
  NTuple::Item<int>     tagmode_temp0;
  NTuple::Item<int>       mctag_temp0;
  NTuple::Item<int>    Dstmode1_temp0;
  NTuple::Item<int>    Dstmode2_temp0;
  NTuple::Item<int>    gamorpi0_temp0;
  NTuple::Item<double>      ecm_temp0;
  NTuple::Item<double>  maxangle_temp0;
  NTuple::Item<double>  angle_Dst_temp0;
  
  NTuple::Item<double>     delE_temp0;
  
  NTuple::Item<int>       index_temp0;
  NTuple::Array<double>    V4_1_temp0;
  NTuple::Array<double>    V4_2_temp0;
  NTuple::Array<double>    V4_3_temp0;
  NTuple::Array<double>    V4_4_temp0;
  NTuple::Array<double>    V4_5_temp0;

 
 
 
 
 
  
  NTuple::Tuple*  m_tuple1;
  NTuple::Item<int>       event_temp1;
  NTuple::Item<int>         run_temp1;
  NTuple::Item<int>     mcmode1_temp1;
  NTuple::Item<int>     mcmode2_temp1;
  NTuple::Item<int>     mcmodea_temp1;
  NTuple::Item<int>     mcmodeb_temp1;
  NTuple::Item<int>   tagcharge_temp1;
  NTuple::Item<int>     tagmode_temp1;
  NTuple::Item<int>       mctag_temp1;
  NTuple::Item<int>    Dstmode1_temp1;
  NTuple::Item<int>    Dstmode2_temp1;
  NTuple::Item<double>      ecm_temp1;
  NTuple::Item<double>  maxangle_temp1;
  
  NTuple::Item<double>  mDs_rec_temp1;
  NTuple::Item<double>  mDs_tag_temp1;
  NTuple::Item<double>  mBC_tag_temp1;

  NTuple::Item<int>       index_temp1;
  NTuple::Array<double>    V4_1_temp1;
  NTuple::Array<double>    V4_2_temp1;
  NTuple::Array<double>    V4_3_temp1;
  NTuple::Array<double>    V4_4_temp1;

  
  NTuple::Tuple*  m_tuple2;
  NTuple::Item<int>       event_temp2;
  NTuple::Item<int>         run_temp2;
  NTuple::Item<int>     mcmode1_temp2;
  NTuple::Item<int>     mcmode2_temp2;
  NTuple::Item<int>     mcmodea_temp2;
  NTuple::Item<int>     mcmodeb_temp2;
  NTuple::Item<int>   tagcharge_temp2;
  NTuple::Item<int>     tagmode_temp2;
  NTuple::Item<int>     recmode_temp2;
  NTuple::Item<int>       mctag_temp2;
  NTuple::Item<int>    Dstmode1_temp2;
  NTuple::Item<int>    Dstmode2_temp2;
  NTuple::Item<double>      ecm_temp2;
  
  NTuple::Item<double>      mm2m_temp2;
  NTuple::Item<double>       m12_temp2;
  NTuple::Item<double>       m13_temp2;
  NTuple::Item<double>       m14_temp2;
  NTuple::Item<double>       m23_temp2;
  NTuple::Item<double>       m24_temp2;
  NTuple::Item<double>       m34_temp2;
  NTuple::Item<double>      m123_temp2;
  NTuple::Item<double>      m124_temp2;
  NTuple::Item<double>      m134_temp2;
  NTuple::Item<double>      m234_temp2;
  NTuple::Item<double>        q2_temp2;
  NTuple::Item<double>  maxangle_temp2;
  NTuple::Item<double>  maxangle_tag_temp2;
  
  NTuple::Item<double>    mm2mft_temp2;
  NTuple::Item<double>     m12ft_temp2;
  NTuple::Item<double>     m13ft_temp2;
  NTuple::Item<double>     m14ft_temp2;
  NTuple::Item<double>     m23ft_temp2;
  NTuple::Item<double>     m24ft_temp2;
  NTuple::Item<double>     m34ft_temp2;
  NTuple::Item<double>    m123ft_temp2;
  NTuple::Item<double>    m124ft_temp2;
  NTuple::Item<double>    m134ft_temp2;
  NTuple::Item<double>    m234ft_temp2;
  NTuple::Item<double>      q2ft_temp2;

  NTuple::Item<double>  q2_truth_temp2;
  NTuple::Item<int>    extra_pi0_temp2;
  NTuple::Item<int>   extra_char_temp2;
  NTuple::Item<double>   egammax_temp2;
  NTuple::Item<double>   egamsum_temp2;
  NTuple::Item<double>     muemc_temp2;
  NTuple::Item<double>   mudepth_temp2;
  NTuple::Item<double>      delE_temp2;
  
  NTuple::Item<double>   mDs_tag_temp2;
  NTuple::Item<double>   mBC_tag_temp2;
  NTuple::Item<int>     gamorpi0_temp2;
  NTuple::Item<int>       sgmode_temp2;
  NTuple::Item<double>  angle_Dst_temp2;

  NTuple::Item<int>       index_temp2;
  NTuple::Array<double>    V4_1_temp2;
  NTuple::Array<double>    V4_2_temp2;
  NTuple::Array<double>    V4_3_temp2;
  NTuple::Array<double>    V4_4_temp2;
  NTuple::Array<double>    V4_5_temp2;
  NTuple::Array<double>    V4_6_temp2;
  NTuple::Array<double>    V4_7_temp2;
  NTuple::Array<double>    V4_8_temp2;
  NTuple::Array<double>    V4_9_temp2;
  NTuple::Array<double>    F4_1_temp2;
  NTuple::Array<double>    F4_2_temp2;
  NTuple::Array<double>    F4_3_temp2;
  NTuple::Array<double>    F4_4_temp2;



  NTuple::Tuple* mctruth_tuple1;
  NTuple::Item<int>    mctruth_run;
  NTuple::Item<int>    mctruth_event;
  NTuple::Item<double>    mctruth_q2;
  NTuple::Item<double>    mctruth_pe;
  NTuple::Item<double>    mctruth_ce;
  NTuple::Item<double>    mctruth_peta;
  NTuple::Item<double>    mctruth_ceta;

  NTuple::Item<double>    mctruth_ppip;
  NTuple::Item<double>    mctruth_ppim;
  NTuple::Item<double>    mctruth_ppi0;
  NTuple::Item<double>    mctruth_cpip;
  NTuple::Item<double>    mctruth_cpim;
  NTuple::Item<double>    mctruth_cpi0;


  NTuple::Item<int>    mctruth_mcmodea;
  NTuple::Item<int>    mctruth_mcmodeb;
  NTuple::Item<int>    mctruth_mcmode1;
  NTuple::Item<int>    mctruth_mcmode2;
  NTuple::Item<int>    mctruth_Dstmode1;
  NTuple::Item<int>    mctruth_Dstmode2;
  NTuple::Item<int>    mctruth_mctag;









};







#endif 
