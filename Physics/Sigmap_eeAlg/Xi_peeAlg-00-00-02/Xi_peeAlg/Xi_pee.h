#ifndef Physics_Analysis_Xi_pee_H
#define Physics_Analysis_Xi_pee_H 

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
#include "TH1.h"
//#include "VertexFit/ReadBeamParFromDb.h"


class Xi_pee : public Algorithm {

public:
  Xi_pee(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();  

private:

  //ReadBeamParFromDb m_reader;
  // Declare r0, z0 cut for charged tracks
  double m_vr0cut;
  double m_vz0cut;
  double m_coscut;
  double m_ecms;
  double m_beamangle; 
  double mpi0;
  double m_pi0chisq1ccut;
  double m_pi0mhCut;
  double m_pi0mlCut;
  double m_pi0decayanglecut;


  NTuple::Tuple*  m_tuple0;
  NTuple::Item<double>  m_truth_costheta_sigma_p;
  NTuple::Item<double>  m_truth_costheta_sigma_m;
  NTuple::Item<double>  m_truth_costheta_sigma_p_boost;
  NTuple::Item<double>  m_truth_costheta_sigma_m_boost;
  NTuple::Item<double>  m_truth_decaylength;
  NTuple::Array<double> m_truth_ppx;
  NTuple::Array<double> m_truth_ppy;
  NTuple::Array<double> m_truth_ppz;
  NTuple::Array<double> m_truth_pe;

  NTuple::Array<double> m_truth_pipx;
  NTuple::Array<double> m_truth_pipy;
  NTuple::Array<double> m_truth_pipz;
  NTuple::Array<double> m_truth_pie;


  NTuple::Array<double> m_truth_sigma_px;
  NTuple::Array<double> m_truth_sigma_py;
  NTuple::Array<double> m_truth_sigma_pz;
  NTuple::Array<double> m_truth_sigma_e;


  NTuple::Item<double>  m_truth_pip_p;
  NTuple::Item<double>  m_truth_pim_p;
  NTuple::Item<double>  m_truth_proton_p;
  NTuple::Item<double>  m_truth_pbar_p;

  NTuple::Tuple*  m_tuple4;
  NTuple::Item<int>   m_idxmc;
  NTuple::Array<int>   m_trkidx;
  NTuple::Array<int>  m_pdgid;   
  NTuple::Array<int>  m_motheridx;


  NTuple::Item<int>  m_type;
  NTuple::Item<long>  m_run;
  NTuple::Item<long>  m_rec;
  NTuple::Item<long>  m_evttag;
  NTuple::Item<long>  m_ngam;

  NTuple::Item<long>  m_npi0;
  NTuple::Array<double> m_mpi0;
  NTuple::Array<double> m_chisq1cpi0;
  NTuple::Array<long> m_ig1pi0;
  NTuple::Array<long> m_ig2pi0;

  NTuple::Item<double>  m_lambda_mass;
  NTuple::Item<double>  m_lambda_ratio;
  NTuple::Item<double>  m_lambda_decayL;
  
  NTuple::Item<double>  m_lambdabar_mass;
  NTuple::Item<double>  m_lambdabar_ratio;
  NTuple::Item<double>  m_lambdabar_decayL;
  
  NTuple::Item<double>  m_costheta_lambda;
  NTuple::Item<double>  m_costheta_lambdabar;
  NTuple::Item<double>  m_costheta_lambda_boost;
  NTuple::Item<double>  m_costheta_lambdabar_boost;

  NTuple::Item<double>  m_Xi_mass;
  NTuple::Item<double>  m_Xi_ratio;
  NTuple::Item<double>  m_Xi_decayL;

  NTuple::Item<double>  m_Xibar_mass;
  NTuple::Item<double>  m_Xibar_ratio;
  NTuple::Item<double>  m_Xibar_decayL;

  NTuple::Item<double>  m_costheta_Xi;
  NTuple::Item<double>  m_costheta_Xibar;
  NTuple::Item<double>  m_costheta_Xi_boost;
  NTuple::Item<double>  m_costheta_Xibar_boost;


  NTuple::Item<double>  m_Xi0_mass;
  NTuple::Item<double>  m_Xi0_ratio;
  NTuple::Item<double>  m_Xi0_decayL;
  
  NTuple::Item<double>  m_Xi0bar_mass;
  NTuple::Item<double>  m_Xi0bar_ratio;
  NTuple::Item<double>  m_Xi0bar_decayL;
  NTuple::Item<double>  m_tag_Xibar_mass;
  NTuple::Item<double>  m_tag_Xibar_energy;
  NTuple::Item<double>  m_tag_rec_Xibar_mass;
  NTuple::Item<double>  m_costheta_Xi0;
  NTuple::Item<double>  m_costheta_Xi0bar;
  NTuple::Item<double>  m_costheta_Xi0_boost;
  NTuple::Item<double>  m_costheta_Xi0bar_boost;






  NTuple::Item<double>  m_pppim_mass;
  NTuple::Item<double>  m_pmpip_mass;
  NTuple::Item<double>  m_lambdapim_mass;
  NTuple::Item<double>  m_lambdabarpip_mass;
  NTuple::Item<double>  m_Xipip_mass;
  NTuple::Item<double>  m_Xibarpim_mass;



  NTuple::Item<double>  m_chisq4c;


  NTuple::Array<double> m_4cpipx;
  NTuple::Array<double> m_4cpipy;
  NTuple::Array<double> m_4cpipz;
  NTuple::Array<double> m_4cpie;

  NTuple::Array<double> m_4cppx;
  NTuple::Array<double> m_4cppy;
  NTuple::Array<double> m_4cppz;
  NTuple::Array<double> m_4cpe;


  NTuple::Array<double> m_4clambda_px;
  NTuple::Array<double> m_4clambda_py;
  NTuple::Array<double> m_4clambda_pz;
  NTuple::Array<double> m_4clambda_e;

  NTuple::Array<double> m_4cXi_px;
  NTuple::Array<double> m_4cXi_py;
  NTuple::Array<double> m_4cXi_pz;
  NTuple::Array<double> m_4cXi_e;

  NTuple::Array<double> m_4cXi0_px;
  NTuple::Array<double> m_4cXi0_py;
  NTuple::Array<double> m_4cXi0_pz;
  NTuple::Array<double> m_4cXi0_e;


  NTuple::Item<double>  m_p_x;
  NTuple::Item<double>  m_p_y;
  NTuple::Item<double>  m_p_z;
  NTuple::Item<double>  m_pbar_x;
  NTuple::Item<double>  m_pbar_y;
  NTuple::Item<double>  m_pbar_z;



};

#endif 
