#ifndef Physics_Analysis_pmu_H
#define Physics_Analysis_pmu_H 
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
#include "DDmcmode/DDmcmode.h"
//#include "VertexFit/ReadBeamParFromDb.h"


class pmu : public Algorithm {

public:
  pmu(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();  
void DpSelection(SmartDataPtr<Event::McParticleCol> mcParticleCol);
void DmSelection(SmartDataPtr<Event::McParticleCol> mcParticleCol);
void OmegaetapSelection(SmartDataPtr<Event::McParticleCol> mcParticleCol);
void OmegaetamSelection(SmartDataPtr<Event::McParticleCol> mcParticleCol);
void set0();
bool same(int id[20]);


  // 
private:
  double m_gammaAngleCut;
  bool   m_debug;
  int    m_mctag;

  NTuple::Tuple*  m_tupleb;
  NTuple::Item<int>     topo_temp_00;
  NTuple::Array<int>    pdgid_temp_00;
  NTuple::Array<int>    mcidx_temp_00;

  NTuple::Item<double>  lam_DIF_0_temp_b;
  NTuple::Item<double>  lam_DIF_1_temp_b;
  NTuple::Item<double>  lam_DFG_0_temp_b;
  NTuple::Item<double>  lam_DFG_1_temp_b;

  NTuple::Item<double>  lam_leafP_0_temp_b;
  NTuple::Item<double>  lam_leafP_1_temp_b;
  NTuple::Item<double>  lam_vertex_0_temp_b;
  NTuple::Item<double>  lam_vertex_1_temp_b;

  NTuple::Item<double>  p_DIF_0_temp_b;
  NTuple::Item<double>  p_DIF_1_temp_b;
  NTuple::Item<double>  p_DFG_0_temp_b;
  NTuple::Item<double>  p_DFG_1_temp_b;

  NTuple::Item<double>  p_leafP_0_temp_b;
  NTuple::Item<double>  p_leafP_1_temp_b;
  NTuple::Item<double>  p_vertex_0_temp_b;
  NTuple::Item<double>  p_vertex_1_temp_b;

  NTuple::Item<double>  pi_DIF_0_temp_b;
  NTuple::Item<double>  pi_DIF_1_temp_b;
  NTuple::Item<double>  pi_DFG_0_temp_b;
  NTuple::Item<double>  pi_DFG_1_temp_b;

  NTuple::Item<double>  pi_leafP_0_temp_b;
  NTuple::Item<double>  pi_leafP_1_temp_b;
  NTuple::Item<double>  pi_vertex_0_temp_b;
  NTuple::Item<double>  pi_vertex_1_temp_b;

  NTuple::Item<double>  mu_DIF_0_temp_b;
  NTuple::Item<double>  mu_DIF_1_temp_b;
  NTuple::Item<double>  mu_DFG_0_temp_b;
  NTuple::Item<double>  mu_DFG_1_temp_b;

  NTuple::Item<double>  mu_leafP_0_temp_b;
  NTuple::Item<double>  mu_leafP_1_temp_b;
  NTuple::Item<double>  mu_vertex_0_temp_b;
  NTuple::Item<double>  mu_vertex_1_temp_b;


  NTuple::Item<int>     index_temp_b;
  NTuple::Array<double>  V4_1_0_temp_b;
  NTuple::Array<double>  V4_2_0_temp_b;
  NTuple::Array<double>  V4_3_0_temp_b;
  NTuple::Array<double>  V4_4_0_temp_b;
  NTuple::Array<double>  V4_5_0_temp_b;

  NTuple::Array<double>  V4_1_1_temp_b;
  NTuple::Array<double>  V4_2_1_temp_b;
  NTuple::Array<double>  V4_3_1_temp_b;
  NTuple::Array<double>  V4_4_1_temp_b;
  NTuple::Array<double>  V4_5_1_temp_b;

  NTuple::Item<double>  p_1_0_temp_b;
  NTuple::Item<double>  p_2_0_temp_b;
  NTuple::Item<double>  p_3_0_temp_b;
  NTuple::Item<double>  p_4_0_temp_b;
  NTuple::Item<double>  p_5_0_temp_b;

  NTuple::Item<double>  p_1_1_temp_b;
  NTuple::Item<double>  p_2_1_temp_b;
  NTuple::Item<double>  p_3_1_temp_b;
  NTuple::Item<double>  p_4_1_temp_b;
  NTuple::Item<double>  p_5_1_temp_b;

  NTuple::Item<double>  c_1_0_temp_b;
  NTuple::Item<double>  c_2_0_temp_b;
  NTuple::Item<double>  c_3_0_temp_b;
  NTuple::Item<double>  c_4_0_temp_b;
  NTuple::Item<double>  c_5_0_temp_b;

  NTuple::Item<double>  c_1_1_temp_b;
  NTuple::Item<double>  c_2_1_temp_b;
  NTuple::Item<double>  c_3_1_temp_b;
  NTuple::Item<double>  c_4_1_temp_b;
  NTuple::Item<double>  c_5_1_temp_b;

  NTuple::Item<int>     mcmode1_temp_b;
  NTuple::Item<int>     mcmode2_temp_b;
  NTuple::Item<int>     mcmodea_temp_b;
  NTuple::Item<int>     mcmodeb_temp_b;
  NTuple::Item<int>     event_temp_b;
  NTuple::Item<int>     run_temp_b;
  NTuple::Item<int>     mctag_temp_b;
  
//	bool FindMode(int);
  NTuple::Tuple*  m_tuple1;
  NTuple::Item<int>     topo_temp_10;
  NTuple::Array<int>    pdgid_temp_10;
  NTuple::Array<int>    mcidx_temp_10;

  NTuple::Item<double>  mass_bc_temp_1;
  NTuple::Item<double>  delE_tag_temp_1;
  NTuple::Item<double>  mass_bc_temp_test;
  NTuple::Item<double>  delE_tag_temp_test;
  NTuple::Item<double>  mass_inv_temp_1;
  NTuple::Item<double>  mass_reco_tag_temp_1;
  NTuple::Item<double>  pdp_temp_1;
  NTuple::Item<double>  pdp_e_temp_1;
  NTuple::Item<int>     m_irec1;
  NTuple::Item<int>     m_irun1;
  NTuple::Item<int>     tagcharge_temp_1;
  NTuple::Item<int>     tagmode_temp_1;
  NTuple::Item<double>  m_mdbc1;
  NTuple::Item<double>  m_mdbc2;
  NTuple::Item<int>     cosmicray_temp_1;
  NTuple::Item<int>     m_idxmc;
  NTuple::Array<double> m_pdgid;
  NTuple::Array<double> m_motheridx;
  NTuple::Array<double> m_trkindex;
  NTuple::Item<double>  p_tag_1_temp_1;
  NTuple::Item<double>  c_tag_1_temp_1;
  NTuple::Item<double>  p_tag_2_temp_1;
  NTuple::Item<double>  c_tag_2_temp_1;
  NTuple::Item<double>  p_tag_temp_1;
  NTuple::Item<double>  c_tag_temp_1;
  NTuple::Item<double>  p_theta_temp_1;
  NTuple::Item<double>  mdbc1_1;
  NTuple::Item<double>  mdbc2_1;
  NTuple::Item<int>     mcmode1_1;
  NTuple::Item<int>     mcmode2_1;
  NTuple::Item<int>     mcmodea_1;
  NTuple::Item<int>     mcmodeb_1;
  NTuple::Item<double>  T_angle1_temp_1;
  NTuple::Item<double>  T_angle2_temp_1;
  NTuple::Item<double>  T_angle3_temp_1;
  NTuple::Item<double>  T_angle4_temp_1;
  NTuple::Item<double>  T_angle5_temp_1;
  NTuple::Item<double>  lam_chi_temp_1;
  NTuple::Item<double>  lam_len_temp_1;
  NTuple::Item<double>  lam_lenerr_temp_1;

  NTuple::Item<double> evp_1_temp_1;
  NTuple::Item<double> evp_2_temp_1;
  NTuple::Item<double> evp_3_temp_1;
  NTuple::Item<double> evp_4_temp_1;
  NTuple::Item<double> evp_5_temp_1;

  NTuple::Item<double>  eemc_1_temp_1;
  NTuple::Item<double>  eemc_2_temp_1;
  NTuple::Item<double>  eemc_3_temp_1;
  NTuple::Item<double>  eemc_4_temp_1;
  NTuple::Item<double>  eemc_5_temp_1;

  NTuple::Item<int>     mctag_temp_1;

/*
  NTuple::Tuple*  m_tuple2;
  NTuple::Item<int>                               index_temp_2;
  NTuple::Array<double>                            V4_1_temp_2;
  NTuple::Array<double>                            V4_2_temp_2;
  NTuple::Array<double>                            V4_3_temp_2;
  NTuple::Array<double>                            V4_4_temp_2;
  NTuple::Array<double>                            V4_5_temp_2;

  NTuple::Item<int>                           cosmicray_temp_2;
  NTuple::Item<double>                            gam_e_temp_2;

  NTuple::Item<double>                          p_sig_1_temp_2;
  NTuple::Item<double>                    p_sig_1_theta_temp_2;
  NTuple::Item<double>                          p_sig_2_temp_2;
  NTuple::Item<double>                    p_sig_2_theta_temp_2;
  NTuple::Item<double>                          p_sig_3_temp_2;
  NTuple::Item<double>                    p_sig_3_theta_temp_2;
  NTuple::Item<double>                          p_sig_4_temp_2;
  NTuple::Item<double>                    p_sig_4_theta_temp_2;
  NTuple::Item<double>                          p_sig_5_temp_2;
  NTuple::Item<double>                    p_sig_5_theta_temp_2;

  NTuple::Item<double>                         m_sig_12_temp_2;
  NTuple::Item<double>                         m_sig_13_temp_2;
  NTuple::Item<double>                         m_sig_14_temp_2;
  NTuple::Item<double>                         m_sig_15_temp_2;
  NTuple::Item<double>                         m_sig_23_temp_2;
  NTuple::Item<double>                         m_sig_24_temp_2;
  NTuple::Item<double>                         m_sig_25_temp_2;
  NTuple::Item<double>                         m_sig_34_temp_2;
  NTuple::Item<double>                         m_sig_35_temp_2;
  NTuple::Item<double>                         m_sig_45_temp_2;
  NTuple::Item<double>                        m_sig_123_temp_2;
  NTuple::Item<double>                        m_sig_124_temp_2;
  NTuple::Item<double>                        m_sig_125_temp_2;
  NTuple::Item<double>                        m_sig_134_temp_2;
  NTuple::Item<double>                        m_sig_135_temp_2;
  NTuple::Item<double>                        m_sig_234_temp_2;
  NTuple::Item<double>                        m_sig_235_temp_2;
  NTuple::Item<double>                        m_sig_345_temp_2;
  NTuple::Item<double>                       m_sig_1234_temp_2;
  NTuple::Item<double>                         gam_emax_temp_2;
  NTuple::Item<int>                       Ncharge_ex_temp_2;
                                         
  NTuple::Item<int>                             pi0_num_temp_2;
  NTuple::Item<double>                      sig_mass_bc_temp_2;
  NTuple::Item<double>                       sig_deltaE_temp_2;
  NTuple::Item<double>                          T_pdp_temp_2;
  NTuple::Item<int>                         T_tagmode_temp_2;
  NTuple::Item<int>                              m_irec_temp_2;
  NTuple::Item<int>                              m_irun_temp_2;
  NTuple::Item<int>                       sig_tagcharge_temp_2;
  NTuple::Item<double>                            mdbc1_temp_2;
  NTuple::Item<double>                            mdbc2_temp_2;
  NTuple::Item<int>                             mcmode1_temp_2;
  NTuple::Item<int>                             mcmode2_temp_2;
  NTuple::Item<int>                             mcmodea_temp_2;
  NTuple::Item<int>                             mcmodeb_temp_2;
                                         
  NTuple::Item<double>                          mbc_sig_temp_2;
  NTuple::Item<double>                         delE_sig_temp_2;
  NTuple::Item<double>                         mass_inv_temp_2;
  NTuple::Item<double>                              H_w_temp_2;
  NTuple::Item<double>                             CL_k_temp_2;
  NTuple::Item<double>                          CL_k_pi_temp_2;
  NTuple::Item<double>                           CL_pi1_temp_2;
  NTuple::Item<double>                         CL_pi1_k_temp_2;
  NTuple::Item<double>                           CL_pi2_temp_2;
  NTuple::Item<double>                         CL_pi2_k_temp_2;
  NTuple::Item<double>                          pi0_chi_temp_2;
  NTuple::Item<double>                          eta_chi_temp_2;

  NTuple::Item<double>                          m12_tag_temp_2;
  NTuple::Item<double>                          m13_tag_temp_2;
  NTuple::Item<double>                          m14_tag_temp_2;
  NTuple::Item<double>                          m23_tag_temp_2;
  NTuple::Item<double>                          m24_tag_temp_2;
  NTuple::Item<double>                          m34_tag_temp_2;
                                        
  NTuple::Tuple*  m_tuple3;
  NTuple::Item<int>                               index_temp_3;
  NTuple::Array<double>                            V4_1_temp_3;
  NTuple::Array<double>                            V4_2_temp_3;
  NTuple::Array<double>                            V4_3_temp_3;
  NTuple::Array<double>                            V4_4_temp_3;
  NTuple::Array<double>                            V4_5_temp_3;

  NTuple::Item<int>                           cosmicray_temp_3;
  NTuple::Item<double>                            gam_e_temp_3;

  NTuple::Item<double>                          p_sig_1_temp_3;
  NTuple::Item<double>                    p_sig_1_theta_temp_3;
  NTuple::Item<double>                          p_sig_2_temp_3;
  NTuple::Item<double>                    p_sig_2_theta_temp_3;
  NTuple::Item<double>                          p_sig_3_temp_3;
  NTuple::Item<double>                    p_sig_3_theta_temp_3;
  NTuple::Item<double>                          p_sig_4_temp_3;
  NTuple::Item<double>                    p_sig_4_theta_temp_3;
  NTuple::Item<double>                          p_sig_5_temp_3;
  NTuple::Item<double>                    p_sig_5_theta_temp_3;

  NTuple::Item<double>                         m_sig_12_temp_3;
  NTuple::Item<double>                         m_sig_13_temp_3;
  NTuple::Item<double>                         m_sig_14_temp_3;
  NTuple::Item<double>                         m_sig_15_temp_3;
  NTuple::Item<double>                         m_sig_23_temp_3;
  NTuple::Item<double>                         m_sig_24_temp_3;
  NTuple::Item<double>                         m_sig_25_temp_3;
  NTuple::Item<double>                         m_sig_34_temp_3;
  NTuple::Item<double>                         m_sig_35_temp_3;
  NTuple::Item<double>                         m_sig_45_temp_3;
  NTuple::Item<double>                        m_sig_123_temp_3;
  NTuple::Item<double>                        m_sig_124_temp_3;
  NTuple::Item<double>                        m_sig_125_temp_3;
  NTuple::Item<double>                        m_sig_134_temp_3;
  NTuple::Item<double>                        m_sig_135_temp_3;
  NTuple::Item<double>                        m_sig_234_temp_3;
  NTuple::Item<double>                        m_sig_235_temp_3;
  NTuple::Item<double>                        m_sig_345_temp_3;
  NTuple::Item<double>                       m_sig_1234_temp_3;
  NTuple::Item<double>                         gam_emax_temp_3;
  NTuple::Item<int>                       Ncharge_ex_temp_3;
                                         
  NTuple::Item<int>                             pi0_num_temp_3;
  NTuple::Item<double>                      sig_mass_bc_temp_3;
  NTuple::Item<double>                       sig_deltaE_temp_3;
  NTuple::Item<double>                          T_pdp_temp_3;
  NTuple::Item<int>                         T_tagmode_temp_3;
  NTuple::Item<int>                              m_irec_temp_3;
  NTuple::Item<int>                              m_irun_temp_3;
  NTuple::Item<int>                       sig_tagcharge_temp_3;
  NTuple::Item<double>                            mdbc1_temp_3;
  NTuple::Item<double>                            mdbc2_temp_3;
  NTuple::Item<int>                             mcmode1_temp_3;
  NTuple::Item<int>                             mcmode2_temp_3;
  NTuple::Item<int>                             mcmodea_temp_3;
  NTuple::Item<int>                             mcmodeb_temp_3;
                                         
  NTuple::Item<double>                          mbc_sig_temp_3;
  NTuple::Item<double>                         delE_sig_temp_3;
  NTuple::Item<double>                         mass_inv_temp_3;
  NTuple::Item<double>                              H_w_temp_3;
  NTuple::Item<double>                             CL_k_temp_3;
  NTuple::Item<double>                          CL_k_pi_temp_3;
  NTuple::Item<double>                           CL_pi1_temp_3;
  NTuple::Item<double>                         CL_pi1_k_temp_3;
  NTuple::Item<double>                           CL_pi2_temp_3;
  NTuple::Item<double>                         CL_pi2_k_temp_3;
  NTuple::Item<double>                          pi0_chi_temp_3;
  NTuple::Item<double>                          eta_chi_temp_3;

  NTuple::Item<double>                          m12_tag_temp_3;
  NTuple::Item<double>                          m13_tag_temp_3;
  NTuple::Item<double>                          m14_tag_temp_3;
  NTuple::Item<double>                          m23_tag_temp_3;
  NTuple::Item<double>                          m24_tag_temp_3;
  NTuple::Item<double>                          m34_tag_temp_3;

  NTuple::Tuple*  m_tuple4;
  NTuple::Item<int>                               index_temp_4;
  NTuple::Array<double>                            V4_1_temp_4;
  NTuple::Array<double>                            V4_2_temp_4;
  NTuple::Array<double>                            V4_3_temp_4;
  NTuple::Array<double>                            V4_4_temp_4;
  NTuple::Array<double>                            V4_5_temp_4;

  NTuple::Item<int>                           cosmicray_temp_4;
  NTuple::Item<double>                            gam_e_temp_4;

  NTuple::Item<double>                          p_sig_1_temp_4;
  NTuple::Item<double>                    p_sig_1_theta_temp_4;
  NTuple::Item<double>                          p_sig_2_temp_4;
  NTuple::Item<double>                    p_sig_2_theta_temp_4;
  NTuple::Item<double>                          p_sig_3_temp_4;
  NTuple::Item<double>                    p_sig_3_theta_temp_4;
  NTuple::Item<double>                          p_sig_4_temp_4;
  NTuple::Item<double>                    p_sig_4_theta_temp_4;
  NTuple::Item<double>                          p_sig_5_temp_4;
  NTuple::Item<double>                    p_sig_5_theta_temp_4;

  NTuple::Item<double>                         m_sig_12_temp_4;
  NTuple::Item<double>                         m_sig_13_temp_4;
  NTuple::Item<double>                         m_sig_14_temp_4;
  NTuple::Item<double>                         m_sig_15_temp_4;
  NTuple::Item<double>                         m_sig_23_temp_4;
  NTuple::Item<double>                         m_sig_24_temp_4;
  NTuple::Item<double>                         m_sig_25_temp_4;
  NTuple::Item<double>                         m_sig_34_temp_4;
  NTuple::Item<double>                         m_sig_35_temp_4;
  NTuple::Item<double>                         m_sig_45_temp_4;
  NTuple::Item<double>                        m_sig_123_temp_4;
  NTuple::Item<double>                        m_sig_124_temp_4;
  NTuple::Item<double>                        m_sig_125_temp_4;
  NTuple::Item<double>                        m_sig_134_temp_4;
  NTuple::Item<double>                        m_sig_135_temp_4;
  NTuple::Item<double>                        m_sig_234_temp_4;
  NTuple::Item<double>                        m_sig_235_temp_4;
  NTuple::Item<double>                        m_sig_345_temp_4;
  NTuple::Item<double>                       m_sig_1234_temp_4;
  NTuple::Item<double>                         gam_emax_temp_4;
  NTuple::Item<int>                       Ncharge_ex_temp_4;
                                         
  NTuple::Item<int>                             pi0_num_temp_4;
  NTuple::Item<double>                      sig_mass_bc_temp_4;
  NTuple::Item<double>                       sig_deltaE_temp_4;
  NTuple::Item<double>                          T_pdp_temp_4;
  NTuple::Item<int>                         T_tagmode_temp_4;
  NTuple::Item<int>                              m_irec_temp_4;
  NTuple::Item<int>                              m_irun_temp_4;
  NTuple::Item<int>                       sig_tagcharge_temp_4;
  NTuple::Item<double>                            mdbc1_temp_4;
  NTuple::Item<double>                            mdbc2_temp_4;
  NTuple::Item<int>                             mcmode1_temp_4;
  NTuple::Item<int>                             mcmode2_temp_4;
  NTuple::Item<int>                             mcmodea_temp_4;
  NTuple::Item<int>                             mcmodeb_temp_4;
                                         
  NTuple::Item<double>                          mbc_sig_temp_4;
  NTuple::Item<double>                         delE_sig_temp_4;
  NTuple::Item<double>                         mass_inv_temp_4;
  NTuple::Item<double>                              H_w_temp_4;
  NTuple::Item<double>                             CL_k_temp_4;
  NTuple::Item<double>                          CL_k_pi_temp_4;
  NTuple::Item<double>                           CL_pi1_temp_4;
  NTuple::Item<double>                         CL_pi1_k_temp_4;
  NTuple::Item<double>                           CL_pi2_temp_4;
  NTuple::Item<double>                         CL_pi2_k_temp_4;
  NTuple::Item<double>                          pi0_chi_temp_4;
  NTuple::Item<double>                          eta_chi_temp_4;
  NTuple::Item<double>                          m12_tag_temp_4;
  NTuple::Item<double>                          m13_tag_temp_4;
  NTuple::Item<double>                          m14_tag_temp_4;
  NTuple::Item<double>                          m23_tag_temp_4;
  NTuple::Item<double>                          m24_tag_temp_4;
  NTuple::Item<double>                          m34_tag_temp_4;

  NTuple::Tuple*  m_tuple5;
  NTuple::Item<int>                               index_temp_5;
  NTuple::Array<double>                            V4_1_temp_5;
  NTuple::Array<double>                            V4_2_temp_5;
  NTuple::Array<double>                            V4_3_temp_5;
  NTuple::Array<double>                            V4_4_temp_5;
  NTuple::Array<double>                            V4_5_temp_5;

  NTuple::Item<int>                           cosmicray_temp_5;
  NTuple::Item<double>                            gam_e_temp_5;

  NTuple::Item<double>                          p_sig_1_temp_5;
  NTuple::Item<double>                    p_sig_1_theta_temp_5;
  NTuple::Item<double>                          p_sig_2_temp_5;
  NTuple::Item<double>                    p_sig_2_theta_temp_5;
  NTuple::Item<double>                          p_sig_3_temp_5;
  NTuple::Item<double>                    p_sig_3_theta_temp_5;
  NTuple::Item<double>                          p_sig_4_temp_5;
  NTuple::Item<double>                    p_sig_4_theta_temp_5;
  NTuple::Item<double>                          p_sig_5_temp_5;
  NTuple::Item<double>                    p_sig_5_theta_temp_5;

  NTuple::Item<double>                         m_sig_12_temp_5;
  NTuple::Item<double>                         m_sig_13_temp_5;
  NTuple::Item<double>                         m_sig_14_temp_5;
  NTuple::Item<double>                         m_sig_15_temp_5;
  NTuple::Item<double>                         m_sig_23_temp_5;
  NTuple::Item<double>                         m_sig_24_temp_5;
  NTuple::Item<double>                         m_sig_25_temp_5;
  NTuple::Item<double>                         m_sig_34_temp_5;
  NTuple::Item<double>                         m_sig_35_temp_5;
  NTuple::Item<double>                         m_sig_45_temp_5;
  NTuple::Item<double>                        m_sig_123_temp_5;
  NTuple::Item<double>                        m_sig_124_temp_5;
  NTuple::Item<double>                        m_sig_125_temp_5;
  NTuple::Item<double>                        m_sig_134_temp_5;
  NTuple::Item<double>                        m_sig_135_temp_5;
  NTuple::Item<double>                        m_sig_234_temp_5;
  NTuple::Item<double>                        m_sig_235_temp_5;
  NTuple::Item<double>                        m_sig_345_temp_5;
  NTuple::Item<double>                       m_sig_1234_temp_5;
  NTuple::Item<double>                         gam_emax_temp_5;
  NTuple::Item<int>                       Ncharge_ex_temp_5;
                                         
  NTuple::Item<int>                             pi0_num_temp_5;
  NTuple::Item<double>                      sig_mass_bc_temp_5;
  NTuple::Item<double>                       sig_deltaE_temp_5;
  NTuple::Item<double>                          T_pdp_temp_5;
  NTuple::Item<int>                         T_tagmode_temp_5;
  NTuple::Item<int>                              m_irec_temp_5;
  NTuple::Item<int>                              m_irun_temp_5;
  NTuple::Item<int>                       sig_tagcharge_temp_5;
  NTuple::Item<double>                            mdbc1_temp_5;
  NTuple::Item<double>                            mdbc2_temp_5;
  NTuple::Item<int>                             mcmode1_temp_5;
  NTuple::Item<int>                             mcmode2_temp_5;
  NTuple::Item<int>                             mcmodea_temp_5;
  NTuple::Item<int>                             mcmodeb_temp_5;
                                         
  NTuple::Item<double>                          mbc_sig_temp_5;
  NTuple::Item<double>                         delE_sig_temp_5;
  NTuple::Item<double>                         mass_inv_temp_5;
  NTuple::Item<double>                              H_w_temp_5;
  NTuple::Item<double>                             CL_k_temp_5;
  NTuple::Item<double>                          CL_k_pi_temp_5;
  NTuple::Item<double>                           CL_pi1_temp_5;
  NTuple::Item<double>                         CL_pi1_k_temp_5;
  NTuple::Item<double>                           CL_pi2_temp_5;
  NTuple::Item<double>                         CL_pi2_k_temp_5;
  NTuple::Item<double>                          pi0_chi_temp_5;
  NTuple::Item<double>                          eta_chi_temp_5;
  NTuple::Item<double>                          m12_tag_temp_5;
  NTuple::Item<double>                          m13_tag_temp_5;
  NTuple::Item<double>                          m14_tag_temp_5;
  NTuple::Item<double>                          m23_tag_temp_5;
  NTuple::Item<double>                          m24_tag_temp_5;
  NTuple::Item<double>                          m34_tag_temp_5;

  NTuple::Tuple*  m_tuple6;
  NTuple::Item<int>                               index_temp_6;
  NTuple::Array<double>                            V4_1_temp_6;
  NTuple::Array<double>                            V4_2_temp_6;
  NTuple::Array<double>                            V4_3_temp_6;
  NTuple::Array<double>                            V4_4_temp_6;
  NTuple::Array<double>                            V4_5_temp_6;

  NTuple::Item<int>                           cosmicray_temp_6;
  NTuple::Item<double>                            gam_e_temp_6;

  NTuple::Item<double>                          p_sig_1_temp_6;
  NTuple::Item<double>                    p_sig_1_theta_temp_6;
  NTuple::Item<double>                          p_sig_2_temp_6;
  NTuple::Item<double>                    p_sig_2_theta_temp_6;
  NTuple::Item<double>                          p_sig_3_temp_6;
  NTuple::Item<double>                    p_sig_3_theta_temp_6;
  NTuple::Item<double>                          p_sig_4_temp_6;
  NTuple::Item<double>                    p_sig_4_theta_temp_6;
  NTuple::Item<double>                          p_sig_5_temp_6;
  NTuple::Item<double>                    p_sig_5_theta_temp_6;

  NTuple::Item<double>                         m_sig_12_temp_6;
  NTuple::Item<double>                         m_sig_13_temp_6;
  NTuple::Item<double>                         m_sig_14_temp_6;
  NTuple::Item<double>                         m_sig_15_temp_6;
  NTuple::Item<double>                         m_sig_23_temp_6;
  NTuple::Item<double>                         m_sig_24_temp_6;
  NTuple::Item<double>                         m_sig_25_temp_6;
  NTuple::Item<double>                         m_sig_34_temp_6;
  NTuple::Item<double>                         m_sig_35_temp_6;
  NTuple::Item<double>                         m_sig_45_temp_6;
  NTuple::Item<double>                        m_sig_123_temp_6;
  NTuple::Item<double>                        m_sig_124_temp_6;
  NTuple::Item<double>                        m_sig_125_temp_6;
  NTuple::Item<double>                        m_sig_134_temp_6;
  NTuple::Item<double>                        m_sig_135_temp_6;
  NTuple::Item<double>                        m_sig_234_temp_6;
  NTuple::Item<double>                        m_sig_235_temp_6;
  NTuple::Item<double>                        m_sig_345_temp_6;
  NTuple::Item<double>                       m_sig_1234_temp_6;
  NTuple::Item<double>                         gam_emax_temp_6;
  NTuple::Item<int>                       Ncharge_ex_temp_6;
                                         
  NTuple::Item<int>                             pi0_num_temp_6;
  NTuple::Item<double>                      sig_mass_bc_temp_6;
  NTuple::Item<double>                       sig_deltaE_temp_6;
  NTuple::Item<double>                          T_pdp_temp_6;
  NTuple::Item<int>                         T_tagmode_temp_6;
  NTuple::Item<int>                              m_irec_temp_6;
  NTuple::Item<int>                              m_irun_temp_6;
  NTuple::Item<int>                       sig_tagcharge_temp_6;
  NTuple::Item<double>                            mdbc1_temp_6;
  NTuple::Item<double>                            mdbc2_temp_6;
  NTuple::Item<int>                             mcmode1_temp_6;
  NTuple::Item<int>                             mcmode2_temp_6;
  NTuple::Item<int>                             mcmodea_temp_6;
  NTuple::Item<int>                             mcmodeb_temp_6;
                                         
  NTuple::Item<double>                          mbc_sig_temp_6;
  NTuple::Item<double>                         delE_sig_temp_6;
  NTuple::Item<double>                         mass_inv_temp_6;
  NTuple::Item<double>                              H_w_temp_6;
  NTuple::Item<double>                             CL_k_temp_6;
  NTuple::Item<double>                          CL_k_pi_temp_6;
  NTuple::Item<double>                           CL_pi1_temp_6;
  NTuple::Item<double>                         CL_pi1_k_temp_6;
  NTuple::Item<double>                           CL_pi2_temp_6;
  NTuple::Item<double>                         CL_pi2_k_temp_6;
  NTuple::Item<double>                          pi0_chi_temp_6;
  NTuple::Item<double>                          eta_chi_temp_6;
  NTuple::Item<double>                          m12_tag_temp_6;
  NTuple::Item<double>                          m13_tag_temp_6;
  NTuple::Item<double>                          m14_tag_temp_6;
  NTuple::Item<double>                          m23_tag_temp_6;
  NTuple::Item<double>                          m24_tag_temp_6;
  NTuple::Item<double>                          m34_tag_temp_6;

  NTuple::Tuple*  m_tuple7;
  NTuple::Item<int>                               index_temp_7;
  NTuple::Array<double>                            V4_1_temp_7;
  NTuple::Array<double>                            V4_2_temp_7;
  NTuple::Array<double>                            V4_3_temp_7;
  NTuple::Array<double>                            V4_4_temp_7;
  NTuple::Array<double>                            V4_5_temp_7;

  NTuple::Item<int>                           cosmicray_temp_7;
  NTuple::Item<double>                            gam_e_temp_7;

  NTuple::Item<double>                          p_sig_1_temp_7;
  NTuple::Item<double>                    p_sig_1_theta_temp_7;
  NTuple::Item<double>                          p_sig_2_temp_7;
  NTuple::Item<double>                    p_sig_2_theta_temp_7;
  NTuple::Item<double>                          p_sig_3_temp_7;
  NTuple::Item<double>                    p_sig_3_theta_temp_7;
  NTuple::Item<double>                          p_sig_4_temp_7;
  NTuple::Item<double>                    p_sig_4_theta_temp_7;
  NTuple::Item<double>                          p_sig_5_temp_7;
  NTuple::Item<double>                    p_sig_5_theta_temp_7;

  NTuple::Item<double>                         m_sig_12_temp_7;
  NTuple::Item<double>                         m_sig_13_temp_7;
  NTuple::Item<double>                         m_sig_14_temp_7;
  NTuple::Item<double>                         m_sig_15_temp_7;
  NTuple::Item<double>                         m_sig_23_temp_7;
  NTuple::Item<double>                         m_sig_24_temp_7;
  NTuple::Item<double>                         m_sig_25_temp_7;
  NTuple::Item<double>                         m_sig_34_temp_7;
  NTuple::Item<double>                         m_sig_35_temp_7;
  NTuple::Item<double>                         m_sig_45_temp_7;
  NTuple::Item<double>                        m_sig_123_temp_7;
  NTuple::Item<double>                        m_sig_124_temp_7;
  NTuple::Item<double>                        m_sig_125_temp_7;
  NTuple::Item<double>                        m_sig_134_temp_7;
  NTuple::Item<double>                        m_sig_135_temp_7;
  NTuple::Item<double>                        m_sig_234_temp_7;
  NTuple::Item<double>                        m_sig_235_temp_7;
  NTuple::Item<double>                        m_sig_345_temp_7;
  NTuple::Item<double>                       m_sig_1234_temp_7;
  NTuple::Item<double>                         gam_emax_temp_7;
  NTuple::Item<int>                       Ncharge_ex_temp_7;
                                         
  NTuple::Item<int>                             pi0_num_temp_7;
  NTuple::Item<double>                      sig_mass_bc_temp_7;
  NTuple::Item<double>                       sig_deltaE_temp_7;
  NTuple::Item<double>                          T_pdp_temp_7;
  NTuple::Item<int>                         T_tagmode_temp_7;
  NTuple::Item<int>                              m_irec_temp_7;
  NTuple::Item<int>                              m_irun_temp_7;
  NTuple::Item<int>                       sig_tagcharge_temp_7;
  NTuple::Item<double>                            mdbc1_temp_7;
  NTuple::Item<double>                            mdbc2_temp_7;
  NTuple::Item<int>                             mcmode1_temp_7;
  NTuple::Item<int>                             mcmode2_temp_7;
  NTuple::Item<int>                             mcmodea_temp_7;
  NTuple::Item<int>                             mcmodeb_temp_7;
                                         
  NTuple::Item<double>                          mbc_sig_temp_7;
  NTuple::Item<double>                         delE_sig_temp_7;
  NTuple::Item<double>                         mass_inv_temp_7;
  NTuple::Item<double>                              H_w_temp_7;
  NTuple::Item<double>                             CL_k_temp_7;
  NTuple::Item<double>                          CL_k_pi_temp_7;
  NTuple::Item<double>                           CL_pi1_temp_7;
  NTuple::Item<double>                         CL_pi1_k_temp_7;
  NTuple::Item<double>                           CL_pi2_temp_7;
  NTuple::Item<double>                         CL_pi2_k_temp_7;
  NTuple::Item<double>                          pi0_chi_temp_7;
  NTuple::Item<double>                          eta_chi_temp_7;
  NTuple::Item<double>                          m12_tag_temp_7;
  NTuple::Item<double>                          m13_tag_temp_7;
  NTuple::Item<double>                          m14_tag_temp_7;
  NTuple::Item<double>                          m23_tag_temp_7;
  NTuple::Item<double>                          m24_tag_temp_7;
  NTuple::Item<double>                          m34_tag_temp_7;

  NTuple::Tuple*  m_tuple8;
  NTuple::Item<int>                               index_temp_8;
  NTuple::Array<double>                            V4_1_temp_8;
  NTuple::Array<double>                            V4_2_temp_8;
  NTuple::Array<double>                            V4_3_temp_8;
  NTuple::Array<double>                            V4_4_temp_8;
  NTuple::Array<double>                            V4_5_temp_8;

  NTuple::Item<int>                           cosmicray_temp_8;
  NTuple::Item<double>                            gam_e_temp_8;

  NTuple::Item<double>                          p_sig_1_temp_8;
  NTuple::Item<double>                    p_sig_1_theta_temp_8;
  NTuple::Item<double>                          p_sig_2_temp_8;
  NTuple::Item<double>                    p_sig_2_theta_temp_8;
  NTuple::Item<double>                          p_sig_3_temp_8;
  NTuple::Item<double>                    p_sig_3_theta_temp_8;
  NTuple::Item<double>                          p_sig_4_temp_8;
  NTuple::Item<double>                    p_sig_4_theta_temp_8;
  NTuple::Item<double>                          p_sig_5_temp_8;
  NTuple::Item<double>                    p_sig_5_theta_temp_8;

  NTuple::Item<double>                         m_sig_12_temp_8;
  NTuple::Item<double>                         m_sig_13_temp_8;
  NTuple::Item<double>                         m_sig_14_temp_8;
  NTuple::Item<double>                         m_sig_15_temp_8;
  NTuple::Item<double>                         m_sig_23_temp_8;
  NTuple::Item<double>                         m_sig_24_temp_8;
  NTuple::Item<double>                         m_sig_25_temp_8;
  NTuple::Item<double>                         m_sig_34_temp_8;
  NTuple::Item<double>                         m_sig_35_temp_8;
  NTuple::Item<double>                         m_sig_45_temp_8;
  NTuple::Item<double>                        m_sig_123_temp_8;
  NTuple::Item<double>                        m_sig_124_temp_8;
  NTuple::Item<double>                        m_sig_125_temp_8;
  NTuple::Item<double>                        m_sig_134_temp_8;
  NTuple::Item<double>                        m_sig_135_temp_8;
  NTuple::Item<double>                        m_sig_234_temp_8;
  NTuple::Item<double>                        m_sig_235_temp_8;
  NTuple::Item<double>                        m_sig_345_temp_8;
  NTuple::Item<double>                       m_sig_1234_temp_8;
  NTuple::Item<double>                         gam_emax_temp_8;
  NTuple::Item<int>                       Ncharge_ex_temp_8;
                                         
  NTuple::Item<int>                             pi0_num_temp_8;
  NTuple::Item<double>                      sig_mass_bc_temp_8;
  NTuple::Item<double>                       sig_deltaE_temp_8;
  NTuple::Item<double>                          T_pdp_temp_8;
  NTuple::Item<int>                         T_tagmode_temp_8;
  NTuple::Item<int>                              m_irec_temp_8;
  NTuple::Item<int>                              m_irun_temp_8;
  NTuple::Item<int>                       sig_tagcharge_temp_8;
  NTuple::Item<double>                            mdbc1_temp_8;
  NTuple::Item<double>                            mdbc2_temp_8;
  NTuple::Item<int>                             mcmode1_temp_8;
  NTuple::Item<int>                             mcmode2_temp_8;
  NTuple::Item<int>                             mcmodea_temp_8;
  NTuple::Item<int>                             mcmodeb_temp_8;
                                         
  NTuple::Item<double>                          mbc_sig_temp_8;
  NTuple::Item<double>                         delE_sig_temp_8;
  NTuple::Item<double>                         mass_inv_temp_8;
  NTuple::Item<double>                              H_w_temp_8;
  NTuple::Item<double>                             CL_k_temp_8;
  NTuple::Item<double>                          CL_k_pi_temp_8;
  NTuple::Item<double>                           CL_pi1_temp_8;
  NTuple::Item<double>                         CL_pi1_k_temp_8;
  NTuple::Item<double>                           CL_pi2_temp_8;
  NTuple::Item<double>                         CL_pi2_k_temp_8;
  NTuple::Item<double>                          pi0_chi_temp_8;
  NTuple::Item<double>                          eta_chi_temp_8;
  NTuple::Item<double>                          m12_tag_temp_8;
  NTuple::Item<double>                          m13_tag_temp_8;
  NTuple::Item<double>                          m14_tag_temp_8;
  NTuple::Item<double>                          m23_tag_temp_8;
  NTuple::Item<double>                          m24_tag_temp_8;
  NTuple::Item<double>                          m34_tag_temp_8;


  NTuple::Tuple*  m_tuple9;
  NTuple::Item<int>                               index_temp_9;
  NTuple::Array<double>                            V4_1_temp_9;
  NTuple::Array<double>                            V4_2_temp_9;
  NTuple::Array<double>                            V4_3_temp_9;
  NTuple::Array<double>                            V4_4_temp_9;
  NTuple::Array<double>                            V4_5_temp_9;

  NTuple::Item<int>                           cosmicray_temp_9;
  NTuple::Item<double>                            gam_e_temp_9;

  NTuple::Item<double>                          p_sig_1_temp_9;
  NTuple::Item<double>                    p_sig_1_theta_temp_9;
  NTuple::Item<double>                          p_sig_2_temp_9;
  NTuple::Item<double>                    p_sig_2_theta_temp_9;
  NTuple::Item<double>                          p_sig_3_temp_9;
  NTuple::Item<double>                    p_sig_3_theta_temp_9;
  NTuple::Item<double>                          p_sig_4_temp_9;
  NTuple::Item<double>                    p_sig_4_theta_temp_9;
  NTuple::Item<double>                          p_sig_5_temp_9;
  NTuple::Item<double>                    p_sig_5_theta_temp_9;

  NTuple::Item<double>                         m_sig_12_temp_9;
  NTuple::Item<double>                         m_sig_13_temp_9;
  NTuple::Item<double>                         m_sig_14_temp_9;
  NTuple::Item<double>                         m_sig_15_temp_9;
  NTuple::Item<double>                         m_sig_23_temp_9;
  NTuple::Item<double>                         m_sig_24_temp_9;
  NTuple::Item<double>                         m_sig_25_temp_9;
  NTuple::Item<double>                         m_sig_34_temp_9;
  NTuple::Item<double>                         m_sig_35_temp_9;
  NTuple::Item<double>                         m_sig_45_temp_9;
  NTuple::Item<double>                        m_sig_123_temp_9;
  NTuple::Item<double>                        m_sig_124_temp_9;
  NTuple::Item<double>                        m_sig_125_temp_9;
  NTuple::Item<double>                        m_sig_134_temp_9;
  NTuple::Item<double>                        m_sig_135_temp_9;
  NTuple::Item<double>                        m_sig_234_temp_9;
  NTuple::Item<double>                        m_sig_235_temp_9;
  NTuple::Item<double>                        m_sig_345_temp_9;
  NTuple::Item<double>                       m_sig_1234_temp_9;
  NTuple::Item<double>                         gam_emax_temp_9;
  NTuple::Item<int>                       Ncharge_ex_temp_9;
                                         
  NTuple::Item<int>                             pi0_num_temp_9;
  NTuple::Item<double>                      sig_mass_bc_temp_9;
  NTuple::Item<double>                       sig_deltaE_temp_9;
  NTuple::Item<double>                          T_pdp_temp_9;
  NTuple::Item<int>                         T_tagmode_temp_9;
  NTuple::Item<int>                              m_irec_temp_9;
  NTuple::Item<int>                              m_irun_temp_9;
  NTuple::Item<int>                       sig_tagcharge_temp_9;
  NTuple::Item<double>                            mdbc1_temp_9;
  NTuple::Item<double>                            mdbc2_temp_9;
  NTuple::Item<int>                             mcmode1_temp_9;
  NTuple::Item<int>                             mcmode2_temp_9;
  NTuple::Item<int>                             mcmodea_temp_9;
  NTuple::Item<int>                             mcmodeb_temp_9;
                                         
  NTuple::Item<double>                          mbc_sig_temp_9;
  NTuple::Item<double>                         delE_sig_temp_9;
  NTuple::Item<double>                         mass_inv_temp_9;
  NTuple::Item<double>                              H_w_temp_9;
  NTuple::Item<double>                             CL_k_temp_9;
  NTuple::Item<double>                          CL_k_pi_temp_9;
  NTuple::Item<double>                           CL_pi1_temp_9;
  NTuple::Item<double>                         CL_pi1_k_temp_9;
  NTuple::Item<double>                           CL_pi2_temp_9;
  NTuple::Item<double>                         CL_pi2_k_temp_9;
  NTuple::Item<double>                          pi0_chi_temp_9;
  NTuple::Item<double>                          eta_chi_temp_9;
  NTuple::Item<double>                          m12_tag_temp_9;
  NTuple::Item<double>                          m13_tag_temp_9;
  NTuple::Item<double>                          m14_tag_temp_9;
  NTuple::Item<double>                          m23_tag_temp_9;
  NTuple::Item<double>                          m24_tag_temp_9;
  NTuple::Item<double>                          m34_tag_temp_9;

  NTuple::Tuple*  m_tuple10;
  NTuple::Item<int>                               index_temp_10;
  NTuple::Array<double>                            V4_1_temp_10;
  NTuple::Array<double>                            V4_2_temp_10;
  NTuple::Array<double>                            V4_3_temp_10;
  NTuple::Array<double>                            V4_4_temp_10;
  NTuple::Array<double>                            V4_5_temp_10;

  NTuple::Item<int>                           cosmicray_temp_10;
  NTuple::Item<double>                            gam_e_temp_10;

  NTuple::Item<double>                          p_sig_1_temp_10;
  NTuple::Item<double>                    p_sig_1_theta_temp_10;
  NTuple::Item<double>                          p_sig_2_temp_10;
  NTuple::Item<double>                    p_sig_2_theta_temp_10;
  NTuple::Item<double>                          p_sig_3_temp_10;
  NTuple::Item<double>                    p_sig_3_theta_temp_10;
  NTuple::Item<double>                          p_sig_4_temp_10;
  NTuple::Item<double>                    p_sig_4_theta_temp_10;
  NTuple::Item<double>                          p_sig_5_temp_10;
  NTuple::Item<double>                    p_sig_5_theta_temp_10;

  NTuple::Item<double>                         m_sig_12_temp_10;
  NTuple::Item<double>                         m_sig_13_temp_10;
  NTuple::Item<double>                         m_sig_14_temp_10;
  NTuple::Item<double>                         m_sig_15_temp_10;
  NTuple::Item<double>                         m_sig_23_temp_10;
  NTuple::Item<double>                         m_sig_24_temp_10;
  NTuple::Item<double>                         m_sig_25_temp_10;
  NTuple::Item<double>                         m_sig_34_temp_10;
  NTuple::Item<double>                         m_sig_35_temp_10;
  NTuple::Item<double>                         m_sig_45_temp_10;
  NTuple::Item<double>                        m_sig_123_temp_10;
  NTuple::Item<double>                        m_sig_124_temp_10;
  NTuple::Item<double>                        m_sig_125_temp_10;
  NTuple::Item<double>                        m_sig_134_temp_10;
  NTuple::Item<double>                        m_sig_135_temp_10;
  NTuple::Item<double>                        m_sig_234_temp_10;
  NTuple::Item<double>                        m_sig_235_temp_10;
  NTuple::Item<double>                        m_sig_345_temp_10;
  NTuple::Item<double>                       m_sig_1234_temp_10;
  NTuple::Item<double>                         gam_emax_temp_10;
  NTuple::Item<int>                       Ncharge_ex_temp_10;
                                         
  NTuple::Item<int>                             pi0_num_temp_10;
  NTuple::Item<double>                      sig_mass_bc_temp_10;
  NTuple::Item<double>                       sig_deltaE_temp_10;
  NTuple::Item<double>                          T_pdp_temp_10;
  NTuple::Item<int>                         T_tagmode_temp_10;
  NTuple::Item<int>                              m_irec_temp_10;
  NTuple::Item<int>                              m_irun_temp_10;
  NTuple::Item<int>                       sig_tagcharge_temp_10;
  NTuple::Item<double>                            mdbc1_temp_10;
  NTuple::Item<double>                            mdbc2_temp_10;
  NTuple::Item<int>                             mcmode1_temp_10;
  NTuple::Item<int>                             mcmode2_temp_10;
  NTuple::Item<int>                             mcmodea_temp_10;
  NTuple::Item<int>                             mcmodeb_temp_10;
                                         
  NTuple::Item<double>                          mbc_sig_temp_10;
  NTuple::Item<double>                         delE_sig_temp_10;
  NTuple::Item<double>                         mass_inv_temp_10;
  NTuple::Item<double>                              H_w_temp_10;
  NTuple::Item<double>                             CL_k_temp_10;
  NTuple::Item<double>                          CL_k_pi_temp_10;
  NTuple::Item<double>                           CL_pi1_temp_10;
  NTuple::Item<double>                         CL_pi1_k_temp_10;
  NTuple::Item<double>                           CL_pi2_temp_10;
  NTuple::Item<double>                         CL_pi2_k_temp_10;
  NTuple::Item<double>                          pi0_chi_temp_10;
  NTuple::Item<double>                          eta_chi_temp_10;
  NTuple::Item<double>                          m12_tag_temp_10;
  NTuple::Item<double>                          m13_tag_temp_10;
  NTuple::Item<double>                          m14_tag_temp_10;
  NTuple::Item<double>                          m23_tag_temp_10;
  NTuple::Item<double>                          m24_tag_temp_10;
  NTuple::Item<double>                          m34_tag_temp_10;
*/
  NTuple::Tuple*  m_tuple11;

  NTuple::Item<double>   lam_tag_chi_temp_11;
  NTuple::Item<double>   lam_tag_len_temp_11;
  NTuple::Item<double>   lam_tag_lenerr_temp_11;
  NTuple::Item<double>   lam_sig_chi_temp_11;
  NTuple::Item<double>   lam_sig_len_temp_11;
  NTuple::Item<double>   lam_sig_lenerr_temp_11;
  NTuple::Item<double>   p_theta_temp_11;
  NTuple::Item<double>   p_phi_temp_11;

  NTuple::Item<int>                            topo_temp_11;
  NTuple::Array<int>                           pdgid_temp_11;
  NTuple::Array<int>                           mcidx_temp_11;

  NTuple::Item<int>                               index_temp_11;
  NTuple::Array<double>                            V4_1_temp_11;
  NTuple::Array<double>                            V4_2_temp_11;
  NTuple::Array<double>                            V4_3_temp_11;
  NTuple::Array<double>                            V4_4_temp_11;
  NTuple::Array<double>                            V4_4c_1_temp_11;
  NTuple::Array<double>                            V4_4c_2_temp_11;
  NTuple::Array<double>                            V4_4c_3_temp_11;
  NTuple::Array<double>                            V4_4c_4_temp_11;

  NTuple::Item<int>                           cosmicray_temp_11;
  NTuple::Item<double>                            gam_e_temp_11;

  NTuple::Item<double>                            evp_1_temp_11;
  NTuple::Item<double>                            evp_2_temp_11;
  NTuple::Item<double>                            evp_3_temp_11;
  NTuple::Item<double>                            evp_4_temp_11;
  NTuple::Item<double>                            evp_5_temp_11;
  NTuple::Item<double>                            evp_6_temp_11;

  NTuple::Item<double>                           eemc_1_temp_11;
  NTuple::Item<double>                           eemc_2_temp_11;
  NTuple::Item<double>                           eemc_3_temp_11;
  NTuple::Item<double>                           eemc_4_temp_11;
  NTuple::Item<double>                           eemc_5_temp_11;
  NTuple::Item<double>                           eemc_6_temp_11;

  NTuple::Item<double>                          p_sig_1_temp_11;
  NTuple::Item<double>                          c_sig_1_temp_11;
  NTuple::Item<double>                          p_sig_2_temp_11;
  NTuple::Item<double>                          c_sig_2_temp_11;
  NTuple::Item<double>                          p_sig_3_temp_11;
  NTuple::Item<double>                          c_sig_3_temp_11;
  NTuple::Item<double>                          p_sig_4_temp_11;
  NTuple::Item<double>                          c_sig_4_temp_11;
  NTuple::Item<double>                          p_sig_5_temp_11;
  NTuple::Item<double>                          c_sig_5_temp_11;
  NTuple::Item<double>                          p_sig_6_temp_11;
  NTuple::Item<double>                          c_sig_6_temp_11;
  NTuple::Item<double>                          p_sig_7_temp_11;
  NTuple::Item<double>                          c_sig_7_temp_11;
  NTuple::Item<double>                          p_sig_8_temp_11;
  NTuple::Item<double>                          c_sig_8_temp_11;

  NTuple::Item<double>                          p_tag_1_temp_11;
  NTuple::Item<double>                          c_tag_1_temp_11;
  NTuple::Item<double>                          p_tag_2_temp_11;
  NTuple::Item<double>                          c_tag_2_temp_11;
  NTuple::Item<double>                          p_tag_3_temp_11;
  NTuple::Item<double>                          c_tag_3_temp_11;
  NTuple::Item<double>                          p_tag_4_temp_11;
  NTuple::Item<double>                          c_tag_4_temp_11;
  NTuple::Item<double>                          p_tag_5_temp_11;
  NTuple::Item<double>                          c_tag_5_temp_11;


  NTuple::Item<double>                          p_1_4c_temp_11;
  NTuple::Item<double>                          p_2_4c_temp_11;
  NTuple::Item<double>                          p_3_4c_temp_11;
  NTuple::Item<double>                          p_4_4c_temp_11;

  NTuple::Item<double>                          mass_lam_tag_4c_temp_11;
  NTuple::Item<double>                          mass_lam_sig_4c_temp_11;
  NTuple::Item<double>                          mass_lam_sig_temp_11;
  NTuple::Item<double>                          mass_jpsi_4c_2_temp_11;
  NTuple::Item<double>                          mass_sig_miss_pi_1_temp_11;
  NTuple::Item<double>                          mass_sig_miss_pi_2_temp_11;
  NTuple::Item<double>                          mass_sig_pmu_temp_11;
  NTuple::Item<double>                          mass_reco_lmdmu_temp_11;

  NTuple::Item<double>                         m_sig_12_temp_11;
  NTuple::Item<double>                         m_sig_13_temp_11;
  NTuple::Item<double>                         m_sig_14_temp_11;
  NTuple::Item<double>                         m_sig_15_temp_11;
  NTuple::Item<double>                         m_sig_23_temp_11;
  NTuple::Item<double>                         m_sig_24_temp_11;
  NTuple::Item<double>                         m_sig_25_temp_11;
  NTuple::Item<double>                         m_sig_34_temp_11;
  NTuple::Item<double>                         m_sig_35_temp_11;
  NTuple::Item<double>                         m_sig_45_temp_11;
  NTuple::Item<double>                        m_sig_123_temp_11;
  NTuple::Item<double>                        m_sig_124_temp_11;
  NTuple::Item<double>                        m_sig_125_temp_11;
  NTuple::Item<double>                        m_sig_134_temp_11;
  NTuple::Item<double>                        m_sig_135_temp_11;
  NTuple::Item<double>                        m_sig_234_temp_11;
  NTuple::Item<double>                        m_sig_235_temp_11;
  NTuple::Item<double>                        m_sig_345_temp_11;
  NTuple::Item<double>                       m_sig_1234_temp_11;
  NTuple::Item<double>                         gam_emax_temp_11;
  NTuple::Item<int>                       Ncharge_ex_temp_11;
                                         
  NTuple::Item<int>                             pi0_num_temp_11;
  NTuple::Item<double>                      tag_mass_bc_temp_11;
  NTuple::Item<double>                       tag_deltaE_temp_11;
  NTuple::Item<double>                         tag_mass_temp_11;
  NTuple::Item<double>                        reco_mass_temp_11;
  NTuple::Item<double>                        pte2_temp_11;
  NTuple::Item<double>                        angle_lampmu_58_temp_11;
  NTuple::Item<double>                        angle_pi_0616_temp_11;
  NTuple::Item<double>                        ene_gam_sigma0_1_temp_11;
  NTuple::Item<double>                        ene_gam_sigma0_2_temp_11;
  NTuple::Item<int>                         T_tagmode_temp_11;

  NTuple::Item<int>                              pipD_temp_11;
  NTuple::Item<int>                              pimD_temp_11;
  NTuple::Item<int>                              pipD2mu_temp_11;
  NTuple::Item<int>                              pimD2mu_temp_11;

  NTuple::Item<double>                           p_pt_rest_jpsi_temp_11;
  NTuple::Item<double>                           p_pt_rest_lmd_temp_11;
  NTuple::Item<double>                           p_pt_jp_la_temp_11;
  NTuple::Item<double>                           p_pt_lp_ja_temp_11;

  NTuple::Item<int>                              m_irec_temp_11;
  NTuple::Item<int>                              m_irun_temp_11;
  NTuple::Item<int>                       tag_tagcharge_temp_11;
  NTuple::Item<double>                            mdbc1_temp_11;
  NTuple::Item<double>                            mdbc2_temp_11;
  NTuple::Item<int>                             mcmode1_temp_11;
  NTuple::Item<int>                             mcmode2_temp_11;
  NTuple::Item<int>                             mcmodea_temp_11;
  NTuple::Item<int>                             mcmodeb_temp_11;
                                         
  NTuple::Item<double>                          mbc_sig_temp_11;
  NTuple::Item<double>                         delE_sig_temp_11;
  NTuple::Item<double>                         mass_inv_temp_11;

  NTuple::Item<double>                           angle1_temp_11;
  NTuple::Item<double>                           angle2_temp_11;
  NTuple::Item<double>                           angle3_temp_11;
  NTuple::Item<double>                           angle4_temp_11;
  NTuple::Item<double>                           angle5_temp_11;
  NTuple::Item<double>                           angle6_temp_11;
  NTuple::Item<double>                         T_angle1_temp_11;
  NTuple::Item<double>                         T_angle2_temp_11;
  NTuple::Item<double>                         T_angle3_temp_11;
  NTuple::Item<double>                         T_angle4_temp_11;
  NTuple::Item<double>                         T_angle5_temp_11;
  NTuple::Item<double>                         T_angle6_temp_11;

  NTuple::Item<double>                        kmfit_chi_temp_11;
  NTuple::Item<double>                        kmfit_chi_2_temp_11;
  NTuple::Item<double>                             A_DD_temp_11;
  NTuple::Item<int>                               mctag_temp_11;
  NTuple::Item<double>                           u_miss_temp_11;
  NTuple::Item<double>                           q2_temp_11;
  NTuple::Item<double>                           q2_2_temp_11;
  NTuple::Item<double>                           q2_truth_temp_11;
  NTuple::Item<double>                           e_miss_temp_11;
  NTuple::Item<double>                           p_miss_temp_11;
  NTuple::Item<double>                          miss_m2_temp_11;

  NTuple::Item<double>                           u_miss_4c_temp_11;
  NTuple::Item<double>                           e_miss_4c_temp_11;
  NTuple::Item<double>                           p_miss_4c_temp_11;
  NTuple::Item<double>                          miss_m2_4c_temp_11;
  
  NTuple::Item<double>                          esig_V_ebeam_temp_11;
  NTuple::Item<double>                          esig_V_ebeam_4c_temp_11;
  NTuple::Item<double>                          angle_pmu_57_temp_11;
  NTuple::Item<double>                          angle_pmu_57_4c_temp_11;

  
  NTuple::Item<double>                     u_miss_truth_lame_11;
  NTuple::Item<double>                        u_miss_truth_e_11;
  NTuple::Item<double>                     u_miss_truth_ppie_11;
  NTuple::Item<double>                      u_miss_truth_ppi_11;
  NTuple::Item<double>                      u_miss_truth_pie_11;
  NTuple::Item<double>                       u_miss_truth_pe_11;
  NTuple::Item<double>                            E_emc_temp_11;

  NTuple::Item<int>       m_ngoodtrk_11;
  NTuple::Item<int>       m_ngoodgam_11;
  NTuple::Item<int>       m_netcharge_11;
  NTuple::Item<int>       m_nchartrk_11;

  NTuple::Item<double>    m_vxy_1_11;
  NTuple::Item<double>    m_vxy_2_11;
  NTuple::Item<double>    m_vxy_3_11;
  NTuple::Item<double>    m_vxy_4_11;

  NTuple::Item<double>    m_vz_1_11;
  NTuple::Item<double>    m_vz_2_11;
  NTuple::Item<double>    m_vz_3_11;
  NTuple::Item<double>    m_vz_4_11;

  NTuple::Item<double>    m_phi_1_11;
  NTuple::Item<double>    m_phi_2_11;
  NTuple::Item<double>    m_phi_3_11;
  NTuple::Item<double>    m_phi_4_11;
//PID information
  NTuple::Item<double>    m_probe_1_11;
  NTuple::Item<double>    m_probe_2_11;
  NTuple::Item<double>    m_probe_3_11;
  NTuple::Item<double>    m_probe_4_11;
  NTuple::Item<double>    m_probmu_1_11;
  NTuple::Item<double>    m_probmu_2_11;
  NTuple::Item<double>    m_probmu_3_11;
  NTuple::Item<double>    m_probmu_4_11;
  NTuple::Item<double>    m_probpi_1_11;
  NTuple::Item<double>    m_probpi_2_11;
  NTuple::Item<double>    m_probpi_3_11;
  NTuple::Item<double>    m_probpi_4_11;
  NTuple::Item<double>    m_probk_1_11;
  NTuple::Item<double>    m_probk_2_11;
  NTuple::Item<double>    m_probk_3_11;
  NTuple::Item<double>    m_probk_4_11;
  NTuple::Item<double>    m_probp_1_11;
  NTuple::Item<double>    m_probp_2_11;
  NTuple::Item<double>    m_probp_3_11;
  NTuple::Item<double>    m_probp_4_11;

//TOF information
  NTuple::Item<long>     m_fgtof_1_11;
  NTuple::Item<double>   m_counter_1_11;
  NTuple::Item<double>   m_isbarrel_1_11;
  NTuple::Item<double>   m_layertof_1_11;
  NTuple::Item<double>   m_iscluster_1_11;
  NTuple::Item<double>   m_tof_1_11;
  NTuple::Item<double>   m_texe_1_11;
  NTuple::Item<double>   m_texmu_1_11;
  NTuple::Item<double>   m_texpi_1_11;
  NTuple::Item<double>   m_texk_1_11;
  NTuple::Item<double>   m_texp_1_11;
  NTuple::Item<double>   m_dte_1_11;
  NTuple::Item<double>   m_dtmu_1_11;
  NTuple::Item<double>   m_dtpi_1_11;
  NTuple::Item<double>   m_dtk_1_11;
  NTuple::Item<double>   m_dtp_1_11;

  NTuple::Item<long>     m_fgtof_2_11;
  NTuple::Item<double>   m_counter_2_11;
  NTuple::Item<double>   m_isbarrel_2_11;
  NTuple::Item<double>   m_layertof_2_11;
  NTuple::Item<double>   m_iscluster_2_11;
  NTuple::Item<double>   m_tof_2_11;
  NTuple::Item<double>   m_texe_2_11;
  NTuple::Item<double>   m_texmu_2_11;
  NTuple::Item<double>   m_texpi_2_11;
  NTuple::Item<double>   m_texk_2_11;
  NTuple::Item<double>   m_texp_2_11;
  NTuple::Item<double>   m_dte_2_11;
  NTuple::Item<double>   m_dtmu_2_11;
  NTuple::Item<double>   m_dtpi_2_11;
  NTuple::Item<double>   m_dtk_2_11;
  NTuple::Item<double>   m_dtp_2_11;

  NTuple::Item<long>     m_fgtof_3_11;
  NTuple::Item<double>   m_counter_3_11;
  NTuple::Item<double>   m_isbarrel_3_11;
  NTuple::Item<double>   m_layertof_3_11;
  NTuple::Item<double>   m_iscluster_3_11;
  NTuple::Item<double>   m_tof_3_11;
  NTuple::Item<double>   m_texe_3_11;
  NTuple::Item<double>   m_texmu_3_11;
  NTuple::Item<double>   m_texpi_3_11;
  NTuple::Item<double>   m_texk_3_11;
  NTuple::Item<double>   m_texp_3_11;
  NTuple::Item<double>   m_dte_3_11;
  NTuple::Item<double>   m_dtmu_3_11;
  NTuple::Item<double>   m_dtpi_3_11;
  NTuple::Item<double>   m_dtk_3_11;
  NTuple::Item<double>   m_dtp_3_11;

  NTuple::Item<long>     m_fgtof_4_11;
  NTuple::Item<double>   m_counter_4_11;
  NTuple::Item<double>   m_isbarrel_4_11;
  NTuple::Item<double>   m_layertof_4_11;
  NTuple::Item<double>   m_iscluster_4_11;
  NTuple::Item<double>   m_tof_4_11;
  NTuple::Item<double>   m_texe_4_11;
  NTuple::Item<double>   m_texmu_4_11;
  NTuple::Item<double>   m_texpi_4_11;
  NTuple::Item<double>   m_texk_4_11;
  NTuple::Item<double>   m_texp_4_11;
  NTuple::Item<double>   m_dte_4_11;
  NTuple::Item<double>   m_dtmu_4_11;
  NTuple::Item<double>   m_dtpi_4_11;
  NTuple::Item<double>   m_dtk_4_11;
  NTuple::Item<double>   m_dtp_4_11;

 //dedx information
  NTuple::Item<double>   m_chi_e_1_11;
  NTuple::Item<double>   m_chi_mu_1_11;
  NTuple::Item<double>   m_chi_pi_1_11;
  NTuple::Item<double>   m_chi_k_1_11;
  NTuple::Item<double>   m_chi_p_1_11;

  NTuple::Item<double>   m_chi_e_2_11;
  NTuple::Item<double>   m_chi_mu_2_11;
  NTuple::Item<double>   m_chi_pi_2_11;
  NTuple::Item<double>   m_chi_k_2_11;
  NTuple::Item<double>   m_chi_p_2_11;

  NTuple::Item<double>   m_chi_e_3_11;
  NTuple::Item<double>   m_chi_mu_3_11;
  NTuple::Item<double>   m_chi_pi_3_11;
  NTuple::Item<double>   m_chi_k_3_11;
  NTuple::Item<double>   m_chi_p_3_11;

  NTuple::Item<double>   m_chi_e_4_11;
  NTuple::Item<double>   m_chi_mu_4_11;
  NTuple::Item<double>   m_chi_pi_4_11;
  NTuple::Item<double>   m_chi_k_4_11;
  NTuple::Item<double>   m_chi_p_4_11;

  //MUC information
  NTuple::Item<long>     m_maxhitsinlay_2_11;
  NTuple::Item<long>     m_numhits_2_11;
  NTuple::Item<long>     m_numlayers_2_11;
  NTuple::Item<double>   m_depth_2_11;
  NTuple::Item<double>   m_mucchi2_2_11;

/*
  NTuple::Tuple*  m_tuple12;
  NTuple::Item<int>                               index_temp_12;
  NTuple::Array<double>                            V4_1_temp_12;
  NTuple::Array<double>                            V4_2_temp_12;
  NTuple::Array<double>                            V4_3_temp_12;
  NTuple::Array<double>                            V4_4_temp_12;
  NTuple::Array<double>                            V4_5_temp_12;

  NTuple::Item<int>                           cosmicray_temp_12;
  NTuple::Item<double>                            gam_e_temp_12;

  NTuple::Item<double>                          p_sig_1_temp_12;
  NTuple::Item<double>                    p_sig_1_theta_temp_12;
  NTuple::Item<double>                          p_sig_2_temp_12;
  NTuple::Item<double>                    p_sig_2_theta_temp_12;
  NTuple::Item<double>                          p_sig_3_temp_12;
  NTuple::Item<double>                    p_sig_3_theta_temp_12;
  NTuple::Item<double>                          p_sig_4_temp_12;
  NTuple::Item<double>                    p_sig_4_theta_temp_12;
  NTuple::Item<double>                          p_sig_5_temp_12;
  NTuple::Item<double>                    p_sig_5_theta_temp_12;

  NTuple::Item<double>                         m_sig_12_temp_12;
  NTuple::Item<double>                         m_sig_13_temp_12;
  NTuple::Item<double>                         m_sig_14_temp_12;
  NTuple::Item<double>                         m_sig_15_temp_12;
  NTuple::Item<double>                         m_sig_23_temp_12;
  NTuple::Item<double>                         m_sig_24_temp_12;
  NTuple::Item<double>                         m_sig_25_temp_12;
  NTuple::Item<double>                         m_sig_34_temp_12;
  NTuple::Item<double>                         m_sig_35_temp_12;
  NTuple::Item<double>                         m_sig_45_temp_12;
  NTuple::Item<double>                        m_sig_123_temp_12;
  NTuple::Item<double>                        m_sig_124_temp_12;
  NTuple::Item<double>                        m_sig_125_temp_12;
  NTuple::Item<double>                        m_sig_134_temp_12;
  NTuple::Item<double>                        m_sig_135_temp_12;
  NTuple::Item<double>                        m_sig_234_temp_12;
  NTuple::Item<double>                        m_sig_235_temp_12;
  NTuple::Item<double>                        m_sig_345_temp_12;
  NTuple::Item<double>                       m_sig_1234_temp_12;
  NTuple::Item<double>                         gam_emax_temp_12;
  NTuple::Item<int>                       Ncharge_ex_temp_12;
                                         
  NTuple::Item<int>                             pi0_num_temp_12;
  NTuple::Item<double>                      sig_mass_bc_temp_12;
  NTuple::Item<double>                       sig_deltaE_temp_12;
  NTuple::Item<double>                          T_pdp_temp_12;
  NTuple::Item<int>                         T_tagmode_temp_12;
  NTuple::Item<int>                              m_irec_temp_12;
  NTuple::Item<int>                              m_irun_temp_12;
  NTuple::Item<int>                       sig_tagcharge_temp_12;
  NTuple::Item<double>                            mdbc1_temp_12;
  NTuple::Item<double>                            mdbc2_temp_12;
  NTuple::Item<int>                             mcmode1_temp_12;
  NTuple::Item<int>                             mcmode2_temp_12;
  NTuple::Item<int>                             mcmodea_temp_12;
  NTuple::Item<int>                             mcmodeb_temp_12;
                                         
  NTuple::Item<double>                          mbc_sig_temp_12;
  NTuple::Item<double>                         delE_sig_temp_12;
  NTuple::Item<double>                         mass_inv_temp_12;
  NTuple::Item<double>                              H_w_temp_12;
  NTuple::Item<double>                             CL_k_temp_12;
  NTuple::Item<double>                          CL_k_pi_temp_12;
  NTuple::Item<double>                           CL_pi1_temp_12;
  NTuple::Item<double>                         CL_pi1_k_temp_12;
  NTuple::Item<double>                           CL_pi2_temp_12;
  NTuple::Item<double>                         CL_pi2_k_temp_12;
  NTuple::Item<double>                          pi0_chi_temp_12;
  NTuple::Item<double>                          eta_chi_temp_12;

  NTuple::Item<double>                           angle1_temp_12;
  NTuple::Item<double>                           angle2_temp_12;
  NTuple::Item<double>                           angle3_temp_12;
  NTuple::Item<double>                           angle4_temp_12;
  NTuple::Item<double>                           angle5_temp_12;
  NTuple::Item<double>                           angle6_temp_12;
  NTuple::Item<double>                         T_angle1_temp_12;
  NTuple::Item<double>                         T_angle2_temp_12;
  NTuple::Item<double>                         T_angle3_temp_12;
  NTuple::Item<double>                         T_angle4_temp_12;
  NTuple::Item<double>                         T_angle5_temp_12;
  NTuple::Item<double>                         T_angle6_temp_12;


  NTuple::Tuple*  m_tuple13;
  NTuple::Item<int>                               index_temp_13;
  NTuple::Array<double>                            V4_1_temp_13;
  NTuple::Array<double>                            V4_2_temp_13;
  NTuple::Array<double>                            V4_3_temp_13;
  NTuple::Array<double>                            V4_4_temp_13;
  NTuple::Array<double>                            V4_5_temp_13;

  NTuple::Item<int>                           cosmicray_temp_13;
  NTuple::Item<double>                            gam_e_temp_13;

  NTuple::Item<double>                          p_sig_1_temp_13;
  NTuple::Item<double>                    p_sig_1_theta_temp_13;
  NTuple::Item<double>                          p_sig_2_temp_13;
  NTuple::Item<double>                    p_sig_2_theta_temp_13;
  NTuple::Item<double>                          p_sig_3_temp_13;
  NTuple::Item<double>                    p_sig_3_theta_temp_13;
  NTuple::Item<double>                          p_sig_4_temp_13;
  NTuple::Item<double>                    p_sig_4_theta_temp_13;
  NTuple::Item<double>                          p_sig_5_temp_13;
  NTuple::Item<double>                    p_sig_5_theta_temp_13;

  NTuple::Item<double>                         m_sig_12_temp_13;
  NTuple::Item<double>                         m_sig_13_temp_13;
  NTuple::Item<double>                         m_sig_14_temp_13;
  NTuple::Item<double>                         m_sig_15_temp_13;
  NTuple::Item<double>                         m_sig_23_temp_13;
  NTuple::Item<double>                         m_sig_24_temp_13;
  NTuple::Item<double>                         m_sig_25_temp_13;
  NTuple::Item<double>                         m_sig_34_temp_13;
  NTuple::Item<double>                         m_sig_35_temp_13;
  NTuple::Item<double>                         m_sig_45_temp_13;
  NTuple::Item<double>                        m_sig_123_temp_13;
  NTuple::Item<double>                        m_sig_124_temp_13;
  NTuple::Item<double>                        m_sig_125_temp_13;
  NTuple::Item<double>                        m_sig_134_temp_13;
  NTuple::Item<double>                        m_sig_135_temp_13;
  NTuple::Item<double>                        m_sig_234_temp_13;
  NTuple::Item<double>                        m_sig_235_temp_13;
  NTuple::Item<double>                        m_sig_345_temp_13;
  NTuple::Item<double>                       m_sig_1234_temp_13;
  NTuple::Item<double>                         gam_emax_temp_13;
  NTuple::Item<int>                       Ncharge_ex_temp_13;
                                         
  NTuple::Item<int>                             pi0_num_temp_13;
  NTuple::Item<double>                      sig_mass_bc_temp_13;
  NTuple::Item<double>                       sig_deltaE_temp_13;
  NTuple::Item<double>                          T_pdp_temp_13;
  NTuple::Item<int>                         T_tagmode_temp_13;
  NTuple::Item<int>                              m_irec_temp_13;
  NTuple::Item<int>                              m_irun_temp_13;
  NTuple::Item<int>                       sig_tagcharge_temp_13;
  NTuple::Item<double>                            mdbc1_temp_13;
  NTuple::Item<double>                            mdbc2_temp_13;
  NTuple::Item<int>                             mcmode1_temp_13;
  NTuple::Item<int>                             mcmode2_temp_13;
  NTuple::Item<int>                             mcmodea_temp_13;
  NTuple::Item<int>                             mcmodeb_temp_13;
                                         
  NTuple::Item<double>                          mbc_sig_temp_13;
  NTuple::Item<double>                         delE_sig_temp_13;
  NTuple::Item<double>                         mass_inv_temp_13;
  NTuple::Item<double>                              H_w_temp_13;
  NTuple::Item<double>                             CL_k_temp_13;
  NTuple::Item<double>                          CL_k_pi_temp_13;
  NTuple::Item<double>                           CL_pi1_temp_13;
  NTuple::Item<double>                         CL_pi1_k_temp_13;
  NTuple::Item<double>                           CL_pi2_temp_13;
  NTuple::Item<double>                         CL_pi2_k_temp_13;
  NTuple::Item<double>                          pi0_chi_temp_13;
  NTuple::Item<double>                          eta_chi_temp_13;


  NTuple::Item<double>                           angle1_temp_13;
  NTuple::Item<double>                           angle2_temp_13;
  NTuple::Item<double>                           angle3_temp_13;
  NTuple::Item<double>                           angle4_temp_13;
  NTuple::Item<double>                           angle5_temp_13;
  NTuple::Item<double>                           angle6_temp_13;
  NTuple::Item<double>                         T_angle1_temp_13;
  NTuple::Item<double>                         T_angle2_temp_13;
  NTuple::Item<double>                         T_angle3_temp_13;
  NTuple::Item<double>                         T_angle4_temp_13;
  NTuple::Item<double>                         T_angle5_temp_13;
  NTuple::Item<double>                         T_angle6_temp_13;


  NTuple::Tuple*  m_tuple14;
  NTuple::Item<int>                               index_temp_14;
  NTuple::Array<double>                            V4_1_temp_14;
  NTuple::Array<double>                            V4_2_temp_14;
  NTuple::Array<double>                            V4_3_temp_14;
  NTuple::Array<double>                            V4_4_temp_14;
  NTuple::Array<double>                            V4_5_temp_14;

  NTuple::Item<int>                           cosmicray_temp_14;
  NTuple::Item<double>                            gam_e_temp_14;

  NTuple::Item<double>                          p_sig_1_temp_14;
  NTuple::Item<double>                    p_sig_1_theta_temp_14;
  NTuple::Item<double>                          p_sig_2_temp_14;
  NTuple::Item<double>                    p_sig_2_theta_temp_14;
  NTuple::Item<double>                          p_sig_3_temp_14;
  NTuple::Item<double>                    p_sig_3_theta_temp_14;
  NTuple::Item<double>                          p_sig_4_temp_14;
  NTuple::Item<double>                    p_sig_4_theta_temp_14;
  NTuple::Item<double>                          p_sig_5_temp_14;
  NTuple::Item<double>                    p_sig_5_theta_temp_14;

  NTuple::Item<double>                         m_sig_12_temp_14;
  NTuple::Item<double>                         m_sig_13_temp_14;
  NTuple::Item<double>                         m_sig_14_temp_14;
  NTuple::Item<double>                         m_sig_15_temp_14;
  NTuple::Item<double>                         m_sig_23_temp_14;
  NTuple::Item<double>                         m_sig_24_temp_14;
  NTuple::Item<double>                         m_sig_25_temp_14;
  NTuple::Item<double>                         m_sig_34_temp_14;
  NTuple::Item<double>                         m_sig_35_temp_14;
  NTuple::Item<double>                         m_sig_45_temp_14;
  NTuple::Item<double>                        m_sig_123_temp_14;
  NTuple::Item<double>                        m_sig_124_temp_14;
  NTuple::Item<double>                        m_sig_125_temp_14;
  NTuple::Item<double>                        m_sig_134_temp_14;
  NTuple::Item<double>                        m_sig_135_temp_14;
  NTuple::Item<double>                        m_sig_234_temp_14;
  NTuple::Item<double>                        m_sig_235_temp_14;
  NTuple::Item<double>                        m_sig_345_temp_14;
  NTuple::Item<double>                       m_sig_1234_temp_14;
  NTuple::Item<double>                         gam_emax_temp_14;
  NTuple::Item<int>                       Ncharge_ex_temp_14;
                                         
  NTuple::Item<int>                             pi0_num_temp_14;
  NTuple::Item<double>                      sig_mass_bc_temp_14;
  NTuple::Item<double>                       sig_deltaE_temp_14;
  NTuple::Item<double>                          T_pdp_temp_14;
  NTuple::Item<int>                         T_tagmode_temp_14;
  NTuple::Item<int>                              m_irec_temp_14;
  NTuple::Item<int>                              m_irun_temp_14;
  NTuple::Item<int>                       sig_tagcharge_temp_14;
  NTuple::Item<double>                            mdbc1_temp_14;
  NTuple::Item<double>                            mdbc2_temp_14;
  NTuple::Item<int>                             mcmode1_temp_14;
  NTuple::Item<int>                             mcmode2_temp_14;
  NTuple::Item<int>                             mcmodea_temp_14;
  NTuple::Item<int>                             mcmodeb_temp_14;
                                         
  NTuple::Item<double>                          mbc_sig_temp_14;
  NTuple::Item<double>                         delE_sig_temp_14;
  NTuple::Item<double>                         mass_inv_temp_14;
  NTuple::Item<double>                              H_w_temp_14;
  NTuple::Item<double>                             CL_k_temp_14;
  NTuple::Item<double>                          CL_k_pi_temp_14;
  NTuple::Item<double>                           CL_pi1_temp_14;
  NTuple::Item<double>                         CL_pi1_k_temp_14;
  NTuple::Item<double>                           CL_pi2_temp_14;
  NTuple::Item<double>                         CL_pi2_k_temp_14;
  NTuple::Item<double>                          pi0_chi_temp_14;
  NTuple::Item<double>                          eta_chi_temp_14;

  NTuple::Item<double>                           angle1_temp_14;
  NTuple::Item<double>                           angle2_temp_14;
  NTuple::Item<double>                           angle3_temp_14;
  NTuple::Item<double>                           angle4_temp_14;
  NTuple::Item<double>                           angle5_temp_14;
  NTuple::Item<double>                           angle6_temp_14;
  NTuple::Item<double>                         T_angle1_temp_14;
  NTuple::Item<double>                         T_angle2_temp_14;
  NTuple::Item<double>                         T_angle3_temp_14;
  NTuple::Item<double>                         T_angle4_temp_14;
  NTuple::Item<double>                         T_angle5_temp_14;
  NTuple::Item<double>                         T_angle6_temp_14;

  NTuple::Tuple*  m_tuple15;
  NTuple::Item<int>                               index_temp_15;
  NTuple::Array<double>                            V4_1_temp_15;
  NTuple::Array<double>                            V4_2_temp_15;
  NTuple::Array<double>                            V4_3_temp_15;
  NTuple::Array<double>                            V4_4_temp_15;
  NTuple::Array<double>                            V4_5_temp_15;

  NTuple::Item<int>                           cosmicray_temp_15;
  NTuple::Item<double>                            gam_e_temp_15;

  NTuple::Item<double>                          p_sig_1_temp_15;
  NTuple::Item<double>                    p_sig_1_theta_temp_15;
  NTuple::Item<double>                          p_sig_2_temp_15;
  NTuple::Item<double>                    p_sig_2_theta_temp_15;
  NTuple::Item<double>                          p_sig_3_temp_15;
  NTuple::Item<double>                    p_sig_3_theta_temp_15;
  NTuple::Item<double>                          p_sig_4_temp_15;
  NTuple::Item<double>                    p_sig_4_theta_temp_15;
  NTuple::Item<double>                          p_sig_5_temp_15;
  NTuple::Item<double>                    p_sig_5_theta_temp_15;

  NTuple::Item<double>                         m_sig_12_temp_15;
  NTuple::Item<double>                         m_sig_13_temp_15;
  NTuple::Item<double>                         m_sig_14_temp_15;
  NTuple::Item<double>                         m_sig_15_temp_15;
  NTuple::Item<double>                         m_sig_23_temp_15;
  NTuple::Item<double>                         m_sig_24_temp_15;
  NTuple::Item<double>                         m_sig_25_temp_15;
  NTuple::Item<double>                         m_sig_34_temp_15;
  NTuple::Item<double>                         m_sig_35_temp_15;
  NTuple::Item<double>                         m_sig_45_temp_15;
  NTuple::Item<double>                        m_sig_123_temp_15;
  NTuple::Item<double>                        m_sig_124_temp_15;
  NTuple::Item<double>                        m_sig_125_temp_15;
  NTuple::Item<double>                        m_sig_134_temp_15;
  NTuple::Item<double>                        m_sig_135_temp_15;
  NTuple::Item<double>                        m_sig_234_temp_15;
  NTuple::Item<double>                        m_sig_235_temp_15;
  NTuple::Item<double>                        m_sig_345_temp_15;
  NTuple::Item<double>                       m_sig_1234_temp_15;
  NTuple::Item<double>                         gam_emax_temp_15;
  NTuple::Item<int>                       Ncharge_ex_temp_15;
                                         
  NTuple::Item<int>                             pi0_num_temp_15;
  NTuple::Item<double>                      sig_mass_bc_temp_15;
  NTuple::Item<double>                       sig_deltaE_temp_15;
  NTuple::Item<double>                          T_pdp_temp_15;
  NTuple::Item<int>                         T_tagmode_temp_15;
  NTuple::Item<int>                              m_irec_temp_15;
  NTuple::Item<int>                              m_irun_temp_15;
  NTuple::Item<int>                       sig_tagcharge_temp_15;
  NTuple::Item<double>                            mdbc1_temp_15;
  NTuple::Item<double>                            mdbc2_temp_15;
  NTuple::Item<int>                             mcmode1_temp_15;
  NTuple::Item<int>                             mcmode2_temp_15;
  NTuple::Item<int>                             mcmodea_temp_15;
  NTuple::Item<int>                             mcmodeb_temp_15;
                                         
  NTuple::Item<double>                          mbc_sig_temp_15;
  NTuple::Item<double>                         delE_sig_temp_15;
  NTuple::Item<double>                         mass_inv_temp_15;
  NTuple::Item<double>                              H_w_temp_15;
  NTuple::Item<double>                             CL_k_temp_15;
  NTuple::Item<double>                          CL_k_pi_temp_15;
  NTuple::Item<double>                           CL_pi1_temp_15;
  NTuple::Item<double>                         CL_pi1_k_temp_15;
  NTuple::Item<double>                           CL_pi2_temp_15;
  NTuple::Item<double>                         CL_pi2_k_temp_15;
  NTuple::Item<double>                          pi0_chi_temp_15;
  NTuple::Item<double>                          eta_chi_temp_15;

  NTuple::Item<double>                           angle1_temp_15;
  NTuple::Item<double>                           angle2_temp_15;
  NTuple::Item<double>                           angle3_temp_15;
  NTuple::Item<double>                           angle4_temp_15;
  NTuple::Item<double>                           angle5_temp_15;
  NTuple::Item<double>                           angle6_temp_15;
  NTuple::Item<double>                         T_angle1_temp_15;
  NTuple::Item<double>                         T_angle2_temp_15;
  NTuple::Item<double>                         T_angle3_temp_15;
  NTuple::Item<double>                         T_angle4_temp_15;
  NTuple::Item<double>                         T_angle5_temp_15;
  NTuple::Item<double>                         T_angle6_temp_15;

  NTuple::Tuple*  m_tuple16;
  NTuple::Item<int>                               index_temp_16;
  NTuple::Array<double>                            V4_1_temp_16;
  NTuple::Array<double>                            V4_2_temp_16;
  NTuple::Array<double>                            V4_3_temp_16;
  NTuple::Array<double>                            V4_4_temp_16;
  NTuple::Array<double>                            V4_5_temp_16;

  NTuple::Item<int>                           cosmicray_temp_16;
  NTuple::Item<double>                            gam_e_temp_16;

  NTuple::Item<double>                          p_sig_1_temp_16;
  NTuple::Item<double>                    p_sig_1_theta_temp_16;
  NTuple::Item<double>                          p_sig_2_temp_16;
  NTuple::Item<double>                    p_sig_2_theta_temp_16;
  NTuple::Item<double>                          p_sig_3_temp_16;
  NTuple::Item<double>                    p_sig_3_theta_temp_16;
  NTuple::Item<double>                          p_sig_4_temp_16;
  NTuple::Item<double>                    p_sig_4_theta_temp_16;
  NTuple::Item<double>                          p_sig_5_temp_16;
  NTuple::Item<double>                    p_sig_5_theta_temp_16;

  NTuple::Item<double>                         m_sig_12_temp_16;
  NTuple::Item<double>                         m_sig_13_temp_16;
  NTuple::Item<double>                         m_sig_14_temp_16;
  NTuple::Item<double>                         m_sig_15_temp_16;
  NTuple::Item<double>                         m_sig_23_temp_16;
  NTuple::Item<double>                         m_sig_24_temp_16;
  NTuple::Item<double>                         m_sig_25_temp_16;
  NTuple::Item<double>                         m_sig_34_temp_16;
  NTuple::Item<double>                         m_sig_35_temp_16;
  NTuple::Item<double>                         m_sig_45_temp_16;
  NTuple::Item<double>                        m_sig_123_temp_16;
  NTuple::Item<double>                        m_sig_124_temp_16;
  NTuple::Item<double>                        m_sig_125_temp_16;
  NTuple::Item<double>                        m_sig_134_temp_16;
  NTuple::Item<double>                        m_sig_135_temp_16;
  NTuple::Item<double>                        m_sig_234_temp_16;
  NTuple::Item<double>                        m_sig_235_temp_16;
  NTuple::Item<double>                        m_sig_345_temp_16;
  NTuple::Item<double>                       m_sig_1234_temp_16;
  NTuple::Item<double>                         gam_emax_temp_16;
  NTuple::Item<int>                       Ncharge_ex_temp_16;
                                         
  NTuple::Item<int>                             pi0_num_temp_16;
  NTuple::Item<double>                      sig_mass_bc_temp_16;
  NTuple::Item<double>                       sig_deltaE_temp_16;
  NTuple::Item<double>                          T_pdp_temp_16;
  NTuple::Item<int>                         T_tagmode_temp_16;
  NTuple::Item<int>                              m_irec_temp_16;
  NTuple::Item<int>                              m_irun_temp_16;
  NTuple::Item<int>                       sig_tagcharge_temp_16;
  NTuple::Item<double>                            mdbc1_temp_16;
  NTuple::Item<double>                            mdbc2_temp_16;
  NTuple::Item<int>                             mcmode1_temp_16;
  NTuple::Item<int>                             mcmode2_temp_16;
  NTuple::Item<int>                             mcmodea_temp_16;
  NTuple::Item<int>                             mcmodeb_temp_16;
                                         
  NTuple::Item<double>                          mbc_sig_temp_16;
  NTuple::Item<double>                         delE_sig_temp_16;
  NTuple::Item<double>                         mass_inv_temp_16;
  NTuple::Item<double>                              H_w_temp_16;
  NTuple::Item<double>                             CL_k_temp_16;
  NTuple::Item<double>                          CL_k_pi_temp_16;
  NTuple::Item<double>                           CL_pi1_temp_16;
  NTuple::Item<double>                         CL_pi1_k_temp_16;
  NTuple::Item<double>                           CL_pi2_temp_16;
  NTuple::Item<double>                         CL_pi2_k_temp_16;
  NTuple::Item<double>                          pi0_chi_temp_16;
  NTuple::Item<double>                          eta_chi_temp_16;

  NTuple::Item<double>                           angle1_temp_16;
  NTuple::Item<double>                           angle2_temp_16;
  NTuple::Item<double>                           angle3_temp_16;
  NTuple::Item<double>                           angle4_temp_16;
  NTuple::Item<double>                           angle5_temp_16;
  NTuple::Item<double>                           angle6_temp_16;
  NTuple::Item<double>                         T_angle1_temp_16;
  NTuple::Item<double>                         T_angle2_temp_16;
  NTuple::Item<double>                         T_angle3_temp_16;
  NTuple::Item<double>                         T_angle4_temp_16;
  NTuple::Item<double>                         T_angle5_temp_16;
  NTuple::Item<double>                         T_angle6_temp_16;

  NTuple::Tuple*  m_tuple17;
  NTuple::Item<int>                               index_temp_17;
  NTuple::Array<double>                            V4_1_temp_17;
  NTuple::Array<double>                            V4_2_temp_17;
  NTuple::Array<double>                            V4_3_temp_17;
  NTuple::Array<double>                            V4_4_temp_17;
  NTuple::Array<double>                            V4_5_temp_17;

  NTuple::Item<int>                           cosmicray_temp_17;
  NTuple::Item<double>                            gam_e_temp_17;

  NTuple::Item<double>                          p_sig_1_temp_17;
  NTuple::Item<double>                    p_sig_1_theta_temp_17;
  NTuple::Item<double>                          p_sig_2_temp_17;
  NTuple::Item<double>                    p_sig_2_theta_temp_17;
  NTuple::Item<double>                          p_sig_3_temp_17;
  NTuple::Item<double>                    p_sig_3_theta_temp_17;
  NTuple::Item<double>                          p_sig_4_temp_17;
  NTuple::Item<double>                    p_sig_4_theta_temp_17;
  NTuple::Item<double>                          p_sig_5_temp_17;
  NTuple::Item<double>                    p_sig_5_theta_temp_17;

  NTuple::Item<double>                         m_sig_12_temp_17;
  NTuple::Item<double>                         m_sig_13_temp_17;
  NTuple::Item<double>                         m_sig_14_temp_17;
  NTuple::Item<double>                         m_sig_15_temp_17;
  NTuple::Item<double>                         m_sig_23_temp_17;
  NTuple::Item<double>                         m_sig_24_temp_17;
  NTuple::Item<double>                         m_sig_25_temp_17;
  NTuple::Item<double>                         m_sig_34_temp_17;
  NTuple::Item<double>                         m_sig_35_temp_17;
  NTuple::Item<double>                         m_sig_45_temp_17;
  NTuple::Item<double>                        m_sig_123_temp_17;
  NTuple::Item<double>                        m_sig_124_temp_17;
  NTuple::Item<double>                        m_sig_125_temp_17;
  NTuple::Item<double>                        m_sig_134_temp_17;
  NTuple::Item<double>                        m_sig_135_temp_17;
  NTuple::Item<double>                        m_sig_234_temp_17;
  NTuple::Item<double>                        m_sig_235_temp_17;
  NTuple::Item<double>                        m_sig_345_temp_17;
  NTuple::Item<double>                       m_sig_1234_temp_17;
  NTuple::Item<double>                         gam_emax_temp_17;
  NTuple::Item<int>                       Ncharge_ex_temp_17;
                                         
  NTuple::Item<int>                             pi0_num_temp_17;
  NTuple::Item<double>                      sig_mass_bc_temp_17;
  NTuple::Item<double>                       sig_deltaE_temp_17;
  NTuple::Item<double>                          T_pdp_temp_17;
  NTuple::Item<int>                         T_tagmode_temp_17;
  NTuple::Item<int>                              m_irec_temp_17;
  NTuple::Item<int>                              m_irun_temp_17;
  NTuple::Item<int>                       sig_tagcharge_temp_17;
  NTuple::Item<double>                            mdbc1_temp_17;
  NTuple::Item<double>                            mdbc2_temp_17;
  NTuple::Item<int>                             mcmode1_temp_17;
  NTuple::Item<int>                             mcmode2_temp_17;
  NTuple::Item<int>                             mcmodea_temp_17;
  NTuple::Item<int>                             mcmodeb_temp_17;
                                         
  NTuple::Item<double>                          mbc_sig_temp_17;
  NTuple::Item<double>                         delE_sig_temp_17;
  NTuple::Item<double>                         mass_inv_temp_17;
  NTuple::Item<double>                              H_w_temp_17;
  NTuple::Item<double>                             CL_k_temp_17;
  NTuple::Item<double>                          CL_k_pi_temp_17;
  NTuple::Item<double>                           CL_pi1_temp_17;
  NTuple::Item<double>                         CL_pi1_k_temp_17;
  NTuple::Item<double>                           CL_pi2_temp_17;
  NTuple::Item<double>                         CL_pi2_k_temp_17;
  NTuple::Item<double>                          pi0_chi_temp_17;
  NTuple::Item<double>                          eta_chi_temp_17;


  NTuple::Item<double>                           angle1_temp_17;
  NTuple::Item<double>                           angle2_temp_17;
  NTuple::Item<double>                           angle3_temp_17;
  NTuple::Item<double>                           angle4_temp_17;
  NTuple::Item<double>                           angle5_temp_17;
  NTuple::Item<double>                           angle6_temp_17;
  NTuple::Item<double>                         T_angle1_temp_17;
  NTuple::Item<double>                         T_angle2_temp_17;
  NTuple::Item<double>                         T_angle3_temp_17;
  NTuple::Item<double>                         T_angle4_temp_17;
  NTuple::Item<double>                         T_angle5_temp_17;
  NTuple::Item<double>                         T_angle6_temp_17;
  NTuple::Tuple*  m_tuple18;
  NTuple::Item<int>                               index_temp_18;
  NTuple::Array<double>                            V4_1_temp_18;
  NTuple::Array<double>                            V4_2_temp_18;
  NTuple::Array<double>                            V4_3_temp_18;
  NTuple::Array<double>                            V4_4_temp_18;
  NTuple::Array<double>                            V4_5_temp_18;

  NTuple::Item<int>                           cosmicray_temp_18;
  NTuple::Item<double>                            gam_e_temp_18;

  NTuple::Item<double>                          p_sig_1_temp_18;
  NTuple::Item<double>                    p_sig_1_theta_temp_18;
  NTuple::Item<double>                          p_sig_2_temp_18;
  NTuple::Item<double>                    p_sig_2_theta_temp_18;
  NTuple::Item<double>                          p_sig_3_temp_18;
  NTuple::Item<double>                    p_sig_3_theta_temp_18;
  NTuple::Item<double>                          p_sig_4_temp_18;
  NTuple::Item<double>                    p_sig_4_theta_temp_18;
  NTuple::Item<double>                          p_sig_5_temp_18;
  NTuple::Item<double>                    p_sig_5_theta_temp_18;

  NTuple::Item<double>                         m_sig_12_temp_18;
  NTuple::Item<double>                         m_sig_13_temp_18;
  NTuple::Item<double>                         m_sig_14_temp_18;
  NTuple::Item<double>                         m_sig_15_temp_18;
  NTuple::Item<double>                         m_sig_23_temp_18;
  NTuple::Item<double>                         m_sig_24_temp_18;
  NTuple::Item<double>                         m_sig_25_temp_18;
  NTuple::Item<double>                         m_sig_34_temp_18;
  NTuple::Item<double>                         m_sig_35_temp_18;
  NTuple::Item<double>                         m_sig_45_temp_18;
  NTuple::Item<double>                        m_sig_123_temp_18;
  NTuple::Item<double>                        m_sig_124_temp_18;
  NTuple::Item<double>                        m_sig_125_temp_18;
  NTuple::Item<double>                        m_sig_134_temp_18;
  NTuple::Item<double>                        m_sig_135_temp_18;
  NTuple::Item<double>                        m_sig_234_temp_18;
  NTuple::Item<double>                        m_sig_235_temp_18;
  NTuple::Item<double>                        m_sig_345_temp_18;
  NTuple::Item<double>                       m_sig_1234_temp_18;
  NTuple::Item<double>                         gam_emax_temp_18;
  NTuple::Item<int>                       Ncharge_ex_temp_18;
                                         
  NTuple::Item<int>                             pi0_num_temp_18;
  NTuple::Item<double>                      sig_mass_bc_temp_18;
  NTuple::Item<double>                       sig_deltaE_temp_18;
  NTuple::Item<double>                          T_pdp_temp_18;
  NTuple::Item<int>                         T_tagmode_temp_18;
  NTuple::Item<int>                              m_irec_temp_18;
  NTuple::Item<int>                              m_irun_temp_18;
  NTuple::Item<int>                       sig_tagcharge_temp_18;
  NTuple::Item<double>                            mdbc1_temp_18;
  NTuple::Item<double>                            mdbc2_temp_18;
  NTuple::Item<int>                             mcmode1_temp_18;
  NTuple::Item<int>                             mcmode2_temp_18;
  NTuple::Item<int>                             mcmodea_temp_18;
  NTuple::Item<int>                             mcmodeb_temp_18;
                                         
  NTuple::Item<double>                          mbc_sig_temp_18;
  NTuple::Item<double>                         delE_sig_temp_18;
  NTuple::Item<double>                         mass_inv_temp_18;
  NTuple::Item<double>                              H_w_temp_18;
  NTuple::Item<double>                             CL_k_temp_18;
  NTuple::Item<double>                          CL_k_pi_temp_18;
  NTuple::Item<double>                           CL_pi1_temp_18;
  NTuple::Item<double>                         CL_pi1_k_temp_18;
  NTuple::Item<double>                           CL_pi2_temp_18;
  NTuple::Item<double>                         CL_pi2_k_temp_18;
  NTuple::Item<double>                          pi0_chi_temp_18;
  NTuple::Item<double>                          eta_chi_temp_18;


  NTuple::Item<double>                           angle1_temp_18;
  NTuple::Item<double>                           angle2_temp_18;
  NTuple::Item<double>                           angle3_temp_18;
  NTuple::Item<double>                           angle4_temp_18;
  NTuple::Item<double>                           angle5_temp_18;
  NTuple::Item<double>                           angle6_temp_18;
  NTuple::Item<double>                         T_angle1_temp_18;
  NTuple::Item<double>                         T_angle2_temp_18;
  NTuple::Item<double>                         T_angle3_temp_18;
  NTuple::Item<double>                         T_angle4_temp_18;
  NTuple::Item<double>                         T_angle5_temp_18;
  NTuple::Item<double>                         T_angle6_temp_18;


  NTuple::Tuple*  m_tuple19;
  NTuple::Item<int>                               index_temp_19;
  NTuple::Array<double>                            V4_1_temp_19;
  NTuple::Array<double>                            V4_2_temp_19;
  NTuple::Array<double>                            V4_3_temp_19;
  NTuple::Array<double>                            V4_4_temp_19;
  NTuple::Array<double>                            V4_5_temp_19;

  NTuple::Item<int>                           cosmicray_temp_19;
  NTuple::Item<double>                            gam_e_temp_19;

  NTuple::Item<double>                          p_sig_1_temp_19;
  NTuple::Item<double>                    p_sig_1_theta_temp_19;
  NTuple::Item<double>                          p_sig_2_temp_19;
  NTuple::Item<double>                    p_sig_2_theta_temp_19;
  NTuple::Item<double>                          p_sig_3_temp_19;
  NTuple::Item<double>                    p_sig_3_theta_temp_19;
  NTuple::Item<double>                          p_sig_4_temp_19;
  NTuple::Item<double>                    p_sig_4_theta_temp_19;
  NTuple::Item<double>                          p_sig_5_temp_19;
  NTuple::Item<double>                    p_sig_5_theta_temp_19;

  NTuple::Item<double>                         m_sig_12_temp_19;
  NTuple::Item<double>                         m_sig_13_temp_19;
  NTuple::Item<double>                         m_sig_14_temp_19;
  NTuple::Item<double>                         m_sig_15_temp_19;
  NTuple::Item<double>                         m_sig_23_temp_19;
  NTuple::Item<double>                         m_sig_24_temp_19;
  NTuple::Item<double>                         m_sig_25_temp_19;
  NTuple::Item<double>                         m_sig_34_temp_19;
  NTuple::Item<double>                         m_sig_35_temp_19;
  NTuple::Item<double>                         m_sig_45_temp_19;
  NTuple::Item<double>                        m_sig_123_temp_19;
  NTuple::Item<double>                        m_sig_124_temp_19;
  NTuple::Item<double>                        m_sig_125_temp_19;
  NTuple::Item<double>                        m_sig_134_temp_19;
  NTuple::Item<double>                        m_sig_135_temp_19;
  NTuple::Item<double>                        m_sig_234_temp_19;
  NTuple::Item<double>                        m_sig_235_temp_19;
  NTuple::Item<double>                        m_sig_345_temp_19;
  NTuple::Item<double>                       m_sig_1234_temp_19;
  NTuple::Item<double>                         gam_emax_temp_19;
  NTuple::Item<int>                       Ncharge_ex_temp_19;
                                         
  NTuple::Item<int>                             pi0_num_temp_19;
  NTuple::Item<double>                      sig_mass_bc_temp_19;
  NTuple::Item<double>                       sig_deltaE_temp_19;
  NTuple::Item<double>                          T_pdp_temp_19;
  NTuple::Item<int>                         T_tagmode_temp_19;
  NTuple::Item<int>                              m_irec_temp_19;
  NTuple::Item<int>                              m_irun_temp_19;
  NTuple::Item<int>                       sig_tagcharge_temp_19;
  NTuple::Item<double>                            mdbc1_temp_19;
  NTuple::Item<double>                            mdbc2_temp_19;
  NTuple::Item<int>                             mcmode1_temp_19;
  NTuple::Item<int>                             mcmode2_temp_19;
  NTuple::Item<int>                             mcmodea_temp_19;
  NTuple::Item<int>                             mcmodeb_temp_19;
                                         
  NTuple::Item<double>                          mbc_sig_temp_19;
  NTuple::Item<double>                         delE_sig_temp_19;
  NTuple::Item<double>                         mass_inv_temp_19;
  NTuple::Item<double>                              H_w_temp_19;
  NTuple::Item<double>                             CL_k_temp_19;
  NTuple::Item<double>                          CL_k_pi_temp_19;
  NTuple::Item<double>                           CL_pi1_temp_19;
  NTuple::Item<double>                         CL_pi1_k_temp_19;
  NTuple::Item<double>                           CL_pi2_temp_19;
  NTuple::Item<double>                         CL_pi2_k_temp_19;
  NTuple::Item<double>                          pi0_chi_temp_19;
  NTuple::Item<double>                          eta_chi_temp_19;

  NTuple::Item<double>                           angle1_temp_19;
  NTuple::Item<double>                           angle2_temp_19;
  NTuple::Item<double>                           angle3_temp_19;
  NTuple::Item<double>                           angle4_temp_19;
  NTuple::Item<double>                           angle5_temp_19;
  NTuple::Item<double>                           angle6_temp_19;
  NTuple::Item<double>                         T_angle1_temp_19;
  NTuple::Item<double>                         T_angle2_temp_19;
  NTuple::Item<double>                         T_angle3_temp_19;
  NTuple::Item<double>                         T_angle4_temp_19;
  NTuple::Item<double>                         T_angle5_temp_19;
  NTuple::Item<double>                         T_angle6_temp_19;

  NTuple::Tuple*  m_tuple20;
  NTuple::Item<int>                               index_temp_20;
  NTuple::Array<double>                            V4_1_temp_20;
  NTuple::Array<double>                            V4_2_temp_20;
  NTuple::Array<double>                            V4_3_temp_20;
  NTuple::Array<double>                            V4_4_temp_20;
  NTuple::Array<double>                            V4_5_temp_20;

  NTuple::Item<int>                           cosmicray_temp_20;
  NTuple::Item<double>                            gam_e_temp_20;

  NTuple::Item<double>                          p_sig_1_temp_20;
  NTuple::Item<double>                    p_sig_1_theta_temp_20;
  NTuple::Item<double>                          p_sig_2_temp_20;
  NTuple::Item<double>                    p_sig_2_theta_temp_20;
  NTuple::Item<double>                          p_sig_3_temp_20;
  NTuple::Item<double>                    p_sig_3_theta_temp_20;
  NTuple::Item<double>                          p_sig_4_temp_20;
  NTuple::Item<double>                    p_sig_4_theta_temp_20;
  NTuple::Item<double>                          p_sig_5_temp_20;
  NTuple::Item<double>                    p_sig_5_theta_temp_20;

  NTuple::Item<double>                         m_sig_12_temp_20;
  NTuple::Item<double>                         m_sig_13_temp_20;
  NTuple::Item<double>                         m_sig_14_temp_20;
  NTuple::Item<double>                         m_sig_15_temp_20;
  NTuple::Item<double>                         m_sig_23_temp_20;
  NTuple::Item<double>                         m_sig_24_temp_20;
  NTuple::Item<double>                         m_sig_25_temp_20;
  NTuple::Item<double>                         m_sig_34_temp_20;
  NTuple::Item<double>                         m_sig_35_temp_20;
  NTuple::Item<double>                         m_sig_45_temp_20;
  NTuple::Item<double>                        m_sig_123_temp_20;
  NTuple::Item<double>                        m_sig_124_temp_20;
  NTuple::Item<double>                        m_sig_125_temp_20;
  NTuple::Item<double>                        m_sig_134_temp_20;
  NTuple::Item<double>                        m_sig_135_temp_20;
  NTuple::Item<double>                        m_sig_234_temp_20;
  NTuple::Item<double>                        m_sig_235_temp_20;
  NTuple::Item<double>                        m_sig_345_temp_20;
  NTuple::Item<double>                       m_sig_1234_temp_20;
  NTuple::Item<double>                         gam_emax_temp_20;
  NTuple::Item<int>                       Ncharge_ex_temp_20;
                                         
  NTuple::Item<int>                             pi0_num_temp_20;
  NTuple::Item<double>                      sig_mass_bc_temp_20;
  NTuple::Item<double>                       sig_deltaE_temp_20;
  NTuple::Item<double>                          T_pdp_temp_20;
  NTuple::Item<int>                         T_tagmode_temp_20;
  NTuple::Item<int>                              m_irec_temp_20;
  NTuple::Item<int>                              m_irun_temp_20;
  NTuple::Item<int>                       sig_tagcharge_temp_20;
  NTuple::Item<double>                            mdbc1_temp_20;
  NTuple::Item<double>                            mdbc2_temp_20;
  NTuple::Item<int>                             mcmode1_temp_20;
  NTuple::Item<int>                             mcmode2_temp_20;
  NTuple::Item<int>                             mcmodea_temp_20;
  NTuple::Item<int>                             mcmodeb_temp_20;
                                         
  NTuple::Item<double>                          mbc_sig_temp_20;
  NTuple::Item<double>                         delE_sig_temp_20;
  NTuple::Item<double>                         mass_inv_temp_20;
  NTuple::Item<double>                              H_w_temp_20;
  NTuple::Item<double>                             CL_k_temp_20;
  NTuple::Item<double>                          CL_k_pi_temp_20;
  NTuple::Item<double>                           CL_pi1_temp_20;
  NTuple::Item<double>                         CL_pi1_k_temp_20;
  NTuple::Item<double>                           CL_pi2_temp_20;
  NTuple::Item<double>                         CL_pi2_k_temp_20;
  NTuple::Item<double>                          pi0_chi_temp_20;
  NTuple::Item<double>                          eta_chi_temp_20;


  NTuple::Item<double>                           angle1_temp_20;
  NTuple::Item<double>                           angle2_temp_20;
  NTuple::Item<double>                           angle3_temp_20;
  NTuple::Item<double>                           angle4_temp_20;
  NTuple::Item<double>                           angle5_temp_20;
  NTuple::Item<double>                           angle6_temp_20;
  NTuple::Item<double>                         T_angle1_temp_20;
  NTuple::Item<double>                         T_angle2_temp_20;
  NTuple::Item<double>                         T_angle3_temp_20;
  NTuple::Item<double>                         T_angle4_temp_20;
  NTuple::Item<double>                         T_angle5_temp_20;
  NTuple::Item<double>                         T_angle6_temp_20;

  NTuple::Tuple*  m_tuple21;
  NTuple::Item<int>                               index_temp_21;
  NTuple::Array<double>                            V4_1_temp_21;
  NTuple::Array<double>                            V4_2_temp_21;
  NTuple::Array<double>                            V4_3_temp_21;
  NTuple::Array<double>                            V4_4_temp_21;
  NTuple::Array<double>                            V4_5_temp_21;

  NTuple::Item<int>                           cosmicray_temp_21;
  NTuple::Item<double>                            gam_e_temp_21;

  NTuple::Item<double>                          p_sig_1_temp_21;
  NTuple::Item<double>                    p_sig_1_theta_temp_21;
  NTuple::Item<double>                          p_sig_2_temp_21;
  NTuple::Item<double>                    p_sig_2_theta_temp_21;
  NTuple::Item<double>                          p_sig_3_temp_21;
  NTuple::Item<double>                    p_sig_3_theta_temp_21;
  NTuple::Item<double>                          p_sig_4_temp_21;
  NTuple::Item<double>                    p_sig_4_theta_temp_21;
  NTuple::Item<double>                          p_sig_5_temp_21;
  NTuple::Item<double>                    p_sig_5_theta_temp_21;

  NTuple::Item<double>                         m_sig_12_temp_21;
  NTuple::Item<double>                         m_sig_13_temp_21;
  NTuple::Item<double>                         m_sig_14_temp_21;
  NTuple::Item<double>                         m_sig_15_temp_21;
  NTuple::Item<double>                         m_sig_23_temp_21;
  NTuple::Item<double>                         m_sig_24_temp_21;
  NTuple::Item<double>                         m_sig_25_temp_21;
  NTuple::Item<double>                         m_sig_34_temp_21;
  NTuple::Item<double>                         m_sig_35_temp_21;
  NTuple::Item<double>                         m_sig_45_temp_21;
  NTuple::Item<double>                        m_sig_123_temp_21;
  NTuple::Item<double>                        m_sig_124_temp_21;
  NTuple::Item<double>                        m_sig_125_temp_21;
  NTuple::Item<double>                        m_sig_134_temp_21;
  NTuple::Item<double>                        m_sig_135_temp_21;
  NTuple::Item<double>                        m_sig_234_temp_21;
  NTuple::Item<double>                        m_sig_235_temp_21;
  NTuple::Item<double>                        m_sig_345_temp_21;
  NTuple::Item<double>                       m_sig_1234_temp_21;
  NTuple::Item<double>                         gam_emax_temp_21;
  NTuple::Item<int>                       Ncharge_ex_temp_21;
                                         
  NTuple::Item<int>                             pi0_num_temp_21;
  NTuple::Item<double>                      sig_mass_bc_temp_21;
  NTuple::Item<double>                       sig_deltaE_temp_21;
  NTuple::Item<double>                          T_pdp_temp_21;
  NTuple::Item<int>                         T_tagmode_temp_21;
  NTuple::Item<int>                              m_irec_temp_21;
  NTuple::Item<int>                              m_irun_temp_21;
  NTuple::Item<int>                       sig_tagcharge_temp_21;
  NTuple::Item<double>                            mdbc1_temp_21;
  NTuple::Item<double>                            mdbc2_temp_21;
  NTuple::Item<int>                             mcmode1_temp_21;
  NTuple::Item<int>                             mcmode2_temp_21;
  NTuple::Item<int>                             mcmodea_temp_21;
  NTuple::Item<int>                             mcmodeb_temp_21;
                                         
  NTuple::Item<double>                          mbc_sig_temp_21;
  NTuple::Item<double>                         delE_sig_temp_21;
  NTuple::Item<double>                         mass_inv_temp_21;
  NTuple::Item<double>                              H_w_temp_21;
  NTuple::Item<double>                             CL_k_temp_21;
  NTuple::Item<double>                          CL_k_pi_temp_21;
  NTuple::Item<double>                           CL_pi1_temp_21;
  NTuple::Item<double>                         CL_pi1_k_temp_21;
  NTuple::Item<double>                           CL_pi2_temp_21;
  NTuple::Item<double>                         CL_pi2_k_temp_21;
  NTuple::Item<double>                          pi0_chi_temp_21;
  NTuple::Item<double>                          eta_chi_temp_21;


  NTuple::Item<double>                           angle1_temp_21;
  NTuple::Item<double>                           angle2_temp_21;
  NTuple::Item<double>                           angle3_temp_21;
  NTuple::Item<double>                           angle4_temp_21;
  NTuple::Item<double>                           angle5_temp_21;
  NTuple::Item<double>                           angle6_temp_21;
  NTuple::Item<double>                         T_angle1_temp_21;
  NTuple::Item<double>                         T_angle2_temp_21;
  NTuple::Item<double>                         T_angle3_temp_21;
  NTuple::Item<double>                         T_angle4_temp_21;
  NTuple::Item<double>                         T_angle5_temp_21;
  NTuple::Item<double>                         T_angle6_temp_21;

  NTuple::Tuple*  m_tuple22;
  NTuple::Item<int>                               index_temp_22;
  NTuple::Array<double>                            V4_1_temp_22;
  NTuple::Array<double>                            V4_2_temp_22;
  NTuple::Array<double>                            V4_3_temp_22;
  NTuple::Array<double>                            V4_4_temp_22;
  NTuple::Array<double>                            V4_5_temp_22;

  NTuple::Item<int>                           cosmicray_temp_22;
  NTuple::Item<double>                            gam_e_temp_22;

  NTuple::Item<double>                          p_sig_1_temp_22;
  NTuple::Item<double>                    p_sig_1_theta_temp_22;
  NTuple::Item<double>                          p_sig_2_temp_22;
  NTuple::Item<double>                    p_sig_2_theta_temp_22;
  NTuple::Item<double>                          p_sig_3_temp_22;
  NTuple::Item<double>                    p_sig_3_theta_temp_22;
  NTuple::Item<double>                          p_sig_4_temp_22;
  NTuple::Item<double>                    p_sig_4_theta_temp_22;
  NTuple::Item<double>                          p_sig_5_temp_22;
  NTuple::Item<double>                    p_sig_5_theta_temp_22;

  NTuple::Item<double>                         m_sig_12_temp_22;
  NTuple::Item<double>                         m_sig_13_temp_22;
  NTuple::Item<double>                         m_sig_14_temp_22;
  NTuple::Item<double>                         m_sig_15_temp_22;
  NTuple::Item<double>                         m_sig_23_temp_22;
  NTuple::Item<double>                         m_sig_24_temp_22;
  NTuple::Item<double>                         m_sig_25_temp_22;
  NTuple::Item<double>                         m_sig_34_temp_22;
  NTuple::Item<double>                         m_sig_35_temp_22;
  NTuple::Item<double>                         m_sig_45_temp_22;
  NTuple::Item<double>                        m_sig_123_temp_22;
  NTuple::Item<double>                        m_sig_124_temp_22;
  NTuple::Item<double>                        m_sig_125_temp_22;
  NTuple::Item<double>                        m_sig_134_temp_22;
  NTuple::Item<double>                        m_sig_135_temp_22;
  NTuple::Item<double>                        m_sig_234_temp_22;
  NTuple::Item<double>                        m_sig_235_temp_22;
  NTuple::Item<double>                        m_sig_345_temp_22;
  NTuple::Item<double>                       m_sig_1234_temp_22;
  NTuple::Item<double>                         gam_emax_temp_22;
  NTuple::Item<int>                       Ncharge_ex_temp_22;
                                         
  NTuple::Item<int>                             pi0_num_temp_22;
  NTuple::Item<double>                      sig_mass_bc_temp_22;
  NTuple::Item<double>                       sig_deltaE_temp_22;
  NTuple::Item<double>                          T_pdp_temp_22;
  NTuple::Item<int>                         T_tagmode_temp_22;
  NTuple::Item<int>                              m_irec_temp_22;
  NTuple::Item<int>                              m_irun_temp_22;
  NTuple::Item<int>                       sig_tagcharge_temp_22;
  NTuple::Item<double>                            mdbc1_temp_22;
  NTuple::Item<double>                            mdbc2_temp_22;
  NTuple::Item<int>                             mcmode1_temp_22;
  NTuple::Item<int>                             mcmode2_temp_22;
  NTuple::Item<int>                             mcmodea_temp_22;
  NTuple::Item<int>                             mcmodeb_temp_22;
                                         
  NTuple::Item<double>                          mbc_sig_temp_22;
  NTuple::Item<double>                         delE_sig_temp_22;
  NTuple::Item<double>                         mass_inv_temp_22;
  NTuple::Item<double>                              H_w_temp_22;
  NTuple::Item<double>                             CL_k_temp_22;
  NTuple::Item<double>                          CL_k_pi_temp_22;
  NTuple::Item<double>                           CL_pi1_temp_22;
  NTuple::Item<double>                         CL_pi1_k_temp_22;
  NTuple::Item<double>                           CL_pi2_temp_22;
  NTuple::Item<double>                         CL_pi2_k_temp_22;
  NTuple::Item<double>                          pi0_chi_temp_22;
  NTuple::Item<double>                          eta_chi_temp_22;


  NTuple::Item<double>                           angle1_temp_22;
  NTuple::Item<double>                           angle2_temp_22;
  NTuple::Item<double>                           angle3_temp_22;
  NTuple::Item<double>                           angle4_temp_22;
  NTuple::Item<double>                           angle5_temp_22;
  NTuple::Item<double>                           angle6_temp_22;
  NTuple::Item<double>                         T_angle1_temp_22;
  NTuple::Item<double>                         T_angle2_temp_22;
  NTuple::Item<double>                         T_angle3_temp_22;
  NTuple::Item<double>                         T_angle4_temp_22;
  NTuple::Item<double>                         T_angle5_temp_22;
  NTuple::Item<double>                         T_angle6_temp_22;
  NTuple::Tuple*  m_tuple23;
  NTuple::Item<int>                               index_temp_23;
  NTuple::Array<double>                            V4_1_temp_23;
  NTuple::Array<double>                            V4_2_temp_23;
  NTuple::Array<double>                            V4_3_temp_23;
  NTuple::Array<double>                            V4_4_temp_23;
  NTuple::Array<double>                            V4_5_temp_23;

  NTuple::Item<int>                           cosmicray_temp_23;
  NTuple::Item<double>                            gam_e_temp_23;

  NTuple::Item<double>                          p_sig_1_temp_23;
  NTuple::Item<double>                    p_sig_1_theta_temp_23;
  NTuple::Item<double>                          p_sig_2_temp_23;
  NTuple::Item<double>                    p_sig_2_theta_temp_23;
  NTuple::Item<double>                          p_sig_3_temp_23;
  NTuple::Item<double>                    p_sig_3_theta_temp_23;
  NTuple::Item<double>                          p_sig_4_temp_23;
  NTuple::Item<double>                    p_sig_4_theta_temp_23;
  NTuple::Item<double>                          p_sig_5_temp_23;
  NTuple::Item<double>                    p_sig_5_theta_temp_23;

  NTuple::Item<double>                         m_sig_12_temp_23;
  NTuple::Item<double>                         m_sig_13_temp_23;
  NTuple::Item<double>                         m_sig_14_temp_23;
  NTuple::Item<double>                         m_sig_15_temp_23;
  NTuple::Item<double>                         m_sig_23_temp_23;
  NTuple::Item<double>                         m_sig_24_temp_23;
  NTuple::Item<double>                         m_sig_25_temp_23;
  NTuple::Item<double>                         m_sig_34_temp_23;
  NTuple::Item<double>                         m_sig_35_temp_23;
  NTuple::Item<double>                         m_sig_45_temp_23;
  NTuple::Item<double>                        m_sig_123_temp_23;
  NTuple::Item<double>                        m_sig_124_temp_23;
  NTuple::Item<double>                        m_sig_125_temp_23;
  NTuple::Item<double>                        m_sig_134_temp_23;
  NTuple::Item<double>                        m_sig_135_temp_23;
  NTuple::Item<double>                        m_sig_234_temp_23;
  NTuple::Item<double>                        m_sig_235_temp_23;
  NTuple::Item<double>                        m_sig_345_temp_23;
  NTuple::Item<double>                       m_sig_1234_temp_23;
  NTuple::Item<double>                         gam_emax_temp_23;
  NTuple::Item<int>                       Ncharge_ex_temp_23;
                                         
  NTuple::Item<int>                             pi0_num_temp_23;
  NTuple::Item<double>                      sig_mass_bc_temp_23;
  NTuple::Item<double>                       sig_deltaE_temp_23;
  NTuple::Item<double>                          T_pdp_temp_23;
  NTuple::Item<int>                         T_tagmode_temp_23;
  NTuple::Item<int>                              m_irec_temp_23;
  NTuple::Item<int>                              m_irun_temp_23;
  NTuple::Item<int>                       sig_tagcharge_temp_23;
  NTuple::Item<double>                            mdbc1_temp_23;
  NTuple::Item<double>                            mdbc2_temp_23;
  NTuple::Item<int>                             mcmode1_temp_23;
  NTuple::Item<int>                             mcmode2_temp_23;
  NTuple::Item<int>                             mcmodea_temp_23;
  NTuple::Item<int>                             mcmodeb_temp_23;
                                         
  NTuple::Item<double>                          mbc_sig_temp_23;
  NTuple::Item<double>                         delE_sig_temp_23;
  NTuple::Item<double>                         mass_inv_temp_23;
  NTuple::Item<double>                              H_w_temp_23;
  NTuple::Item<double>                             CL_k_temp_23;
  NTuple::Item<double>                          CL_k_pi_temp_23;
  NTuple::Item<double>                           CL_pi1_temp_23;
  NTuple::Item<double>                         CL_pi1_k_temp_23;
  NTuple::Item<double>                           CL_pi2_temp_23;
  NTuple::Item<double>                         CL_pi2_k_temp_23;
  NTuple::Item<double>                          pi0_chi_temp_23;
  NTuple::Item<double>                          eta_chi_temp_23;

  NTuple::Item<double>                           angle1_temp_23;
  NTuple::Item<double>                           angle2_temp_23;
  NTuple::Item<double>                           angle3_temp_23;
  NTuple::Item<double>                           angle4_temp_23;
  NTuple::Item<double>                           angle5_temp_23;
  NTuple::Item<double>                           angle6_temp_23;
  NTuple::Item<double>                         T_angle1_temp_23;
  NTuple::Item<double>                         T_angle2_temp_23;
  NTuple::Item<double>                         T_angle3_temp_23;
  NTuple::Item<double>                         T_angle4_temp_23;
  NTuple::Item<double>                         T_angle5_temp_23;
  NTuple::Item<double>                         T_angle6_temp_23;

  NTuple::Tuple*  m_tuple24;
  NTuple::Item<int>                               index_temp_24;
  NTuple::Array<double>                            V4_1_temp_24;
  NTuple::Array<double>                            V4_2_temp_24;
  NTuple::Array<double>                            V4_3_temp_24;
  NTuple::Array<double>                            V4_4_temp_24;
  NTuple::Array<double>                            V4_5_temp_24;

  NTuple::Item<int>                           cosmicray_temp_24;
  NTuple::Item<double>                            gam_e_temp_24;

  NTuple::Item<double>                          p_sig_1_temp_24;
  NTuple::Item<double>                    p_sig_1_theta_temp_24;
  NTuple::Item<double>                          p_sig_2_temp_24;
  NTuple::Item<double>                    p_sig_2_theta_temp_24;
  NTuple::Item<double>                          p_sig_3_temp_24;
  NTuple::Item<double>                    p_sig_3_theta_temp_24;
  NTuple::Item<double>                          p_sig_4_temp_24;
  NTuple::Item<double>                    p_sig_4_theta_temp_24;
  NTuple::Item<double>                          p_sig_5_temp_24;
  NTuple::Item<double>                    p_sig_5_theta_temp_24;

  NTuple::Item<double>                         m_sig_12_temp_24;
  NTuple::Item<double>                         m_sig_13_temp_24;
  NTuple::Item<double>                         m_sig_14_temp_24;
  NTuple::Item<double>                         m_sig_15_temp_24;
  NTuple::Item<double>                         m_sig_23_temp_24;
  NTuple::Item<double>                         m_sig_24_temp_24;
  NTuple::Item<double>                         m_sig_25_temp_24;
  NTuple::Item<double>                         m_sig_34_temp_24;
  NTuple::Item<double>                         m_sig_35_temp_24;
  NTuple::Item<double>                         m_sig_45_temp_24;
  NTuple::Item<double>                        m_sig_123_temp_24;
  NTuple::Item<double>                        m_sig_124_temp_24;
  NTuple::Item<double>                        m_sig_125_temp_24;
  NTuple::Item<double>                        m_sig_134_temp_24;
  NTuple::Item<double>                        m_sig_135_temp_24;
  NTuple::Item<double>                        m_sig_234_temp_24;
  NTuple::Item<double>                        m_sig_235_temp_24;
  NTuple::Item<double>                        m_sig_345_temp_24;
  NTuple::Item<double>                       m_sig_1234_temp_24;
  NTuple::Item<double>                         gam_emax_temp_24;
  NTuple::Item<int>                       Ncharge_ex_temp_24;
                                         
  NTuple::Item<int>                             pi0_num_temp_24;
  NTuple::Item<double>                      sig_mass_bc_temp_24;
  NTuple::Item<double>                       sig_deltaE_temp_24;
  NTuple::Item<double>                          T_pdp_temp_24;
  NTuple::Item<int>                         T_tagmode_temp_24;
  NTuple::Item<int>                              m_irec_temp_24;
  NTuple::Item<int>                              m_irun_temp_24;
  NTuple::Item<int>                       sig_tagcharge_temp_24;
  NTuple::Item<double>                            mdbc1_temp_24;
  NTuple::Item<double>                            mdbc2_temp_24;
  NTuple::Item<int>                             mcmode1_temp_24;
  NTuple::Item<int>                             mcmode2_temp_24;
  NTuple::Item<int>                             mcmodea_temp_24;
  NTuple::Item<int>                             mcmodeb_temp_24;
                                         
  NTuple::Item<double>                          mbc_sig_temp_24;
  NTuple::Item<double>                         delE_sig_temp_24;
  NTuple::Item<double>                         mass_inv_temp_24;
  NTuple::Item<double>                              H_w_temp_24;
  NTuple::Item<double>                             CL_k_temp_24;
  NTuple::Item<double>                          CL_k_pi_temp_24;
  NTuple::Item<double>                           CL_pi1_temp_24;
  NTuple::Item<double>                         CL_pi1_k_temp_24;
  NTuple::Item<double>                           CL_pi2_temp_24;
  NTuple::Item<double>                         CL_pi2_k_temp_24;
  NTuple::Item<double>                          pi0_chi_temp_24;
  NTuple::Item<double>                          eta_chi_temp_24;

  NTuple::Item<double>                           angle1_temp_24;
  NTuple::Item<double>                           angle2_temp_24;
  NTuple::Item<double>                           angle3_temp_24;
  NTuple::Item<double>                           angle4_temp_24;
  NTuple::Item<double>                           angle5_temp_24;
  NTuple::Item<double>                           angle6_temp_24;
  NTuple::Item<double>                         T_angle1_temp_24;
  NTuple::Item<double>                         T_angle2_temp_24;
  NTuple::Item<double>                         T_angle3_temp_24;
  NTuple::Item<double>                         T_angle4_temp_24;
  NTuple::Item<double>                         T_angle5_temp_24;
  NTuple::Item<double>                         T_angle6_temp_24;

  NTuple::Tuple*  m_tuple25;
  NTuple::Item<int>                               index_temp_25;
  NTuple::Array<double>                            V4_1_temp_25;
  NTuple::Array<double>                            V4_2_temp_25;
  NTuple::Array<double>                            V4_3_temp_25;
  NTuple::Array<double>                            V4_4_temp_25;
  NTuple::Array<double>                            V4_5_temp_25;

  NTuple::Item<int>                           cosmicray_temp_25;
  NTuple::Item<double>                            gam_e_temp_25;

  NTuple::Item<double>                          p_sig_1_temp_25;
  NTuple::Item<double>                    p_sig_1_theta_temp_25;
  NTuple::Item<double>                          p_sig_2_temp_25;
  NTuple::Item<double>                    p_sig_2_theta_temp_25;
  NTuple::Item<double>                          p_sig_3_temp_25;
  NTuple::Item<double>                    p_sig_3_theta_temp_25;
  NTuple::Item<double>                          p_sig_4_temp_25;
  NTuple::Item<double>                    p_sig_4_theta_temp_25;
  NTuple::Item<double>                          p_sig_5_temp_25;
  NTuple::Item<double>                    p_sig_5_theta_temp_25;

  NTuple::Item<double>                         m_sig_12_temp_25;
  NTuple::Item<double>                         m_sig_13_temp_25;
  NTuple::Item<double>                         m_sig_14_temp_25;
  NTuple::Item<double>                         m_sig_15_temp_25;
  NTuple::Item<double>                         m_sig_23_temp_25;
  NTuple::Item<double>                         m_sig_24_temp_25;
  NTuple::Item<double>                         m_sig_25_temp_25;
  NTuple::Item<double>                         m_sig_34_temp_25;
  NTuple::Item<double>                         m_sig_35_temp_25;
  NTuple::Item<double>                         m_sig_45_temp_25;
  NTuple::Item<double>                        m_sig_123_temp_25;
  NTuple::Item<double>                        m_sig_124_temp_25;
  NTuple::Item<double>                        m_sig_125_temp_25;
  NTuple::Item<double>                        m_sig_134_temp_25;
  NTuple::Item<double>                        m_sig_135_temp_25;
  NTuple::Item<double>                        m_sig_234_temp_25;
  NTuple::Item<double>                        m_sig_235_temp_25;
  NTuple::Item<double>                        m_sig_345_temp_25;
  NTuple::Item<double>                       m_sig_1234_temp_25;
  NTuple::Item<double>                         gam_emax_temp_25;
  NTuple::Item<int>                       Ncharge_ex_temp_25;
                                         
  NTuple::Item<int>                             pi0_num_temp_25;
  NTuple::Item<double>                      sig_mass_bc_temp_25;
  NTuple::Item<double>                       sig_deltaE_temp_25;
  NTuple::Item<double>                          T_pdp_temp_25;
  NTuple::Item<int>                         T_tagmode_temp_25;
  NTuple::Item<int>                              m_irec_temp_25;
  NTuple::Item<int>                              m_irun_temp_25;
  NTuple::Item<int>                       sig_tagcharge_temp_25;
  NTuple::Item<double>                            mdbc1_temp_25;
  NTuple::Item<double>                            mdbc2_temp_25;
  NTuple::Item<int>                             mcmode1_temp_25;
  NTuple::Item<int>                             mcmode2_temp_25;
  NTuple::Item<int>                             mcmodea_temp_25;
  NTuple::Item<int>                             mcmodeb_temp_25;
                                         
  NTuple::Item<double>                          mbc_sig_temp_25;
  NTuple::Item<double>                         delE_sig_temp_25;
  NTuple::Item<double>                         mass_inv_temp_25;
  NTuple::Item<double>                              H_w_temp_25;
  NTuple::Item<double>                             CL_k_temp_25;
  NTuple::Item<double>                          CL_k_pi_temp_25;
  NTuple::Item<double>                           CL_pi1_temp_25;
  NTuple::Item<double>                         CL_pi1_k_temp_25;
  NTuple::Item<double>                           CL_pi2_temp_25;
  NTuple::Item<double>                         CL_pi2_k_temp_25;
  NTuple::Item<double>                          pi0_chi_temp_25;
  NTuple::Item<double>                          eta_chi_temp_25;


  NTuple::Item<double>                           angle1_temp_25;
  NTuple::Item<double>                           angle2_temp_25;
  NTuple::Item<double>                           angle3_temp_25;
  NTuple::Item<double>                           angle4_temp_25;
  NTuple::Item<double>                           angle5_temp_25;
  NTuple::Item<double>                           angle6_temp_25;
  NTuple::Item<double>                         T_angle1_temp_25;
  NTuple::Item<double>                         T_angle2_temp_25;
  NTuple::Item<double>                         T_angle3_temp_25;
  NTuple::Item<double>                         T_angle4_temp_25;
  NTuple::Item<double>                         T_angle5_temp_25;
  NTuple::Item<double>                         T_angle6_temp_25;

  NTuple::Tuple*  m_tuple26;
  NTuple::Item<int>                               index_temp_26;
  NTuple::Array<double>                            V4_1_temp_26;
  NTuple::Array<double>                            V4_2_temp_26;
  NTuple::Array<double>                            V4_3_temp_26;
  NTuple::Array<double>                            V4_4_temp_26;
  NTuple::Array<double>                            V4_5_temp_26;

  NTuple::Item<int>                           cosmicray_temp_26;
  NTuple::Item<double>                            gam_e_temp_26;

  NTuple::Item<double>                          p_sig_1_temp_26;
  NTuple::Item<double>                    p_sig_1_theta_temp_26;
  NTuple::Item<double>                          p_sig_2_temp_26;
  NTuple::Item<double>                    p_sig_2_theta_temp_26;
  NTuple::Item<double>                          p_sig_3_temp_26;
  NTuple::Item<double>                    p_sig_3_theta_temp_26;
  NTuple::Item<double>                          p_sig_4_temp_26;
  NTuple::Item<double>                    p_sig_4_theta_temp_26;
  NTuple::Item<double>                          p_sig_5_temp_26;
  NTuple::Item<double>                    p_sig_5_theta_temp_26;

  NTuple::Item<double>                         m_sig_12_temp_26;
  NTuple::Item<double>                         m_sig_13_temp_26;
  NTuple::Item<double>                         m_sig_14_temp_26;
  NTuple::Item<double>                         m_sig_15_temp_26;
  NTuple::Item<double>                         m_sig_23_temp_26;
  NTuple::Item<double>                         m_sig_24_temp_26;
  NTuple::Item<double>                         m_sig_25_temp_26;
  NTuple::Item<double>                         m_sig_34_temp_26;
  NTuple::Item<double>                         m_sig_35_temp_26;
  NTuple::Item<double>                         m_sig_45_temp_26;
  NTuple::Item<double>                        m_sig_123_temp_26;
  NTuple::Item<double>                        m_sig_124_temp_26;
  NTuple::Item<double>                        m_sig_125_temp_26;
  NTuple::Item<double>                        m_sig_134_temp_26;
  NTuple::Item<double>                        m_sig_135_temp_26;
  NTuple::Item<double>                        m_sig_234_temp_26;
  NTuple::Item<double>                        m_sig_235_temp_26;
  NTuple::Item<double>                        m_sig_345_temp_26;
  NTuple::Item<double>                       m_sig_1234_temp_26;
  NTuple::Item<double>                         gam_emax_temp_26;
  NTuple::Item<int>                       Ncharge_ex_temp_26;
                                         
  NTuple::Item<int>                             pi0_num_temp_26;
  NTuple::Item<double>                      sig_mass_bc_temp_26;
  NTuple::Item<double>                       sig_deltaE_temp_26;
  NTuple::Item<double>                          T_pdp_temp_26;
  NTuple::Item<int>                         T_tagmode_temp_26;
  NTuple::Item<int>                              m_irec_temp_26;
  NTuple::Item<int>                              m_irun_temp_26;
  NTuple::Item<int>                       sig_tagcharge_temp_26;
  NTuple::Item<double>                            mdbc1_temp_26;
  NTuple::Item<double>                            mdbc2_temp_26;
  NTuple::Item<int>                             mcmode1_temp_26;
  NTuple::Item<int>                             mcmode2_temp_26;
  NTuple::Item<int>                             mcmodea_temp_26;
  NTuple::Item<int>                             mcmodeb_temp_26;
                                         
  NTuple::Item<double>                          mbc_sig_temp_26;
  NTuple::Item<double>                         delE_sig_temp_26;
  NTuple::Item<double>                         mass_inv_temp_26;
  NTuple::Item<double>                              H_w_temp_26;
  NTuple::Item<double>                             CL_k_temp_26;
  NTuple::Item<double>                          CL_k_pi_temp_26;
  NTuple::Item<double>                           CL_pi1_temp_26;
  NTuple::Item<double>                         CL_pi1_k_temp_26;
  NTuple::Item<double>                           CL_pi2_temp_26;
  NTuple::Item<double>                         CL_pi2_k_temp_26;
  NTuple::Item<double>                          pi0_chi_temp_26;
  NTuple::Item<double>                          eta_chi_temp_26;


  NTuple::Item<double>                           angle1_temp_26;
  NTuple::Item<double>                           angle2_temp_26;
  NTuple::Item<double>                           angle3_temp_26;
  NTuple::Item<double>                           angle4_temp_26;
  NTuple::Item<double>                           angle5_temp_26;
  NTuple::Item<double>                           angle6_temp_26;
  NTuple::Item<double>                         T_angle1_temp_26;
  NTuple::Item<double>                         T_angle2_temp_26;
  NTuple::Item<double>                         T_angle3_temp_26;
  NTuple::Item<double>                         T_angle4_temp_26;
  NTuple::Item<double>                         T_angle5_temp_26;
  NTuple::Item<double>                         T_angle6_temp_26;

  NTuple::Tuple*  m_tuple27;
  NTuple::Item<int>                               index_temp_27;
  NTuple::Array<double>                            V4_1_temp_27;
  NTuple::Array<double>                            V4_2_temp_27;
  NTuple::Array<double>                            V4_3_temp_27;
  NTuple::Array<double>                            V4_4_temp_27;
  NTuple::Array<double>                            V4_5_temp_27;

  NTuple::Item<int>                           cosmicray_temp_27;
  NTuple::Item<double>                            gam_e_temp_27;

  NTuple::Item<double>                          p_sig_1_temp_27;
  NTuple::Item<double>                    p_sig_1_theta_temp_27;
  NTuple::Item<double>                          p_sig_2_temp_27;
  NTuple::Item<double>                    p_sig_2_theta_temp_27;
  NTuple::Item<double>                          p_sig_3_temp_27;
  NTuple::Item<double>                    p_sig_3_theta_temp_27;
  NTuple::Item<double>                          p_sig_4_temp_27;
  NTuple::Item<double>                    p_sig_4_theta_temp_27;
  NTuple::Item<double>                          p_sig_5_temp_27;
  NTuple::Item<double>                    p_sig_5_theta_temp_27;

  NTuple::Item<double>                         m_sig_12_temp_27;
  NTuple::Item<double>                         m_sig_13_temp_27;
  NTuple::Item<double>                         m_sig_14_temp_27;
  NTuple::Item<double>                         m_sig_15_temp_27;
  NTuple::Item<double>                         m_sig_23_temp_27;
  NTuple::Item<double>                         m_sig_24_temp_27;
  NTuple::Item<double>                         m_sig_25_temp_27;
  NTuple::Item<double>                         m_sig_34_temp_27;
  NTuple::Item<double>                         m_sig_35_temp_27;
  NTuple::Item<double>                         m_sig_45_temp_27;
  NTuple::Item<double>                        m_sig_123_temp_27;
  NTuple::Item<double>                        m_sig_124_temp_27;
  NTuple::Item<double>                        m_sig_125_temp_27;
  NTuple::Item<double>                        m_sig_134_temp_27;
  NTuple::Item<double>                        m_sig_135_temp_27;
  NTuple::Item<double>                        m_sig_234_temp_27;
  NTuple::Item<double>                        m_sig_235_temp_27;
  NTuple::Item<double>                        m_sig_345_temp_27;
  NTuple::Item<double>                       m_sig_1234_temp_27;
  NTuple::Item<double>                         gam_emax_temp_27;
  NTuple::Item<int>                       Ncharge_ex_temp_27;
                                         
  NTuple::Item<int>                             pi0_num_temp_27;
  NTuple::Item<double>                      sig_mass_bc_temp_27;
  NTuple::Item<double>                       sig_deltaE_temp_27;
  NTuple::Item<double>                          T_pdp_temp_27;
  NTuple::Item<int>                         T_tagmode_temp_27;
  NTuple::Item<int>                              m_irec_temp_27;
  NTuple::Item<int>                              m_irun_temp_27;
  NTuple::Item<int>                       sig_tagcharge_temp_27;
  NTuple::Item<double>                            mdbc1_temp_27;
  NTuple::Item<double>                            mdbc2_temp_27;
  NTuple::Item<int>                             mcmode1_temp_27;
  NTuple::Item<int>                             mcmode2_temp_27;
  NTuple::Item<int>                             mcmodea_temp_27;
  NTuple::Item<int>                             mcmodeb_temp_27;
                                         
  NTuple::Item<double>                          mbc_sig_temp_27;
  NTuple::Item<double>                         delE_sig_temp_27;
  NTuple::Item<double>                         mass_inv_temp_27;
  NTuple::Item<double>                              H_w_temp_27;
  NTuple::Item<double>                             CL_k_temp_27;
  NTuple::Item<double>                          CL_k_pi_temp_27;
  NTuple::Item<double>                           CL_pi1_temp_27;
  NTuple::Item<double>                         CL_pi1_k_temp_27;
  NTuple::Item<double>                           CL_pi2_temp_27;
  NTuple::Item<double>                         CL_pi2_k_temp_27;
  NTuple::Item<double>                          pi0_chi_temp_27;
  NTuple::Item<double>                          eta_chi_temp_27;


  NTuple::Item<double>                           angle1_temp_27;
  NTuple::Item<double>                           angle2_temp_27;
  NTuple::Item<double>                           angle3_temp_27;
  NTuple::Item<double>                           angle4_temp_27;
  NTuple::Item<double>                           angle5_temp_27;
  NTuple::Item<double>                           angle6_temp_27;
  NTuple::Item<double>                         T_angle1_temp_27;
  NTuple::Item<double>                         T_angle2_temp_27;
  NTuple::Item<double>                         T_angle3_temp_27;
  NTuple::Item<double>                         T_angle4_temp_27;
  NTuple::Item<double>                         T_angle5_temp_27;
  NTuple::Item<double>                         T_angle6_temp_27;


  NTuple::Tuple*  m_tuple28;
  NTuple::Item<int>                               index_temp_28;
  NTuple::Array<double>                            V4_1_temp_28;
  NTuple::Array<double>                            V4_2_temp_28;
  NTuple::Array<double>                            V4_3_temp_28;
  NTuple::Array<double>                            V4_4_temp_28;
  NTuple::Array<double>                            V4_5_temp_28;

  NTuple::Item<int>                           cosmicray_temp_28;
  NTuple::Item<double>                            gam_e_temp_28;

  NTuple::Item<double>                          p_sig_1_temp_28;
  NTuple::Item<double>                    p_sig_1_theta_temp_28;
  NTuple::Item<double>                          p_sig_2_temp_28;
  NTuple::Item<double>                    p_sig_2_theta_temp_28;
  NTuple::Item<double>                          p_sig_3_temp_28;
  NTuple::Item<double>                    p_sig_3_theta_temp_28;
  NTuple::Item<double>                          p_sig_4_temp_28;
  NTuple::Item<double>                    p_sig_4_theta_temp_28;
  NTuple::Item<double>                          p_sig_5_temp_28;
  NTuple::Item<double>                    p_sig_5_theta_temp_28;

  NTuple::Item<double>                         m_sig_12_temp_28;
  NTuple::Item<double>                         m_sig_13_temp_28;
  NTuple::Item<double>                         m_sig_14_temp_28;
  NTuple::Item<double>                         m_sig_15_temp_28;
  NTuple::Item<double>                         m_sig_23_temp_28;
  NTuple::Item<double>                         m_sig_24_temp_28;
  NTuple::Item<double>                         m_sig_25_temp_28;
  NTuple::Item<double>                         m_sig_34_temp_28;
  NTuple::Item<double>                         m_sig_35_temp_28;
  NTuple::Item<double>                         m_sig_45_temp_28;
  NTuple::Item<double>                        m_sig_123_temp_28;
  NTuple::Item<double>                        m_sig_124_temp_28;
  NTuple::Item<double>                        m_sig_125_temp_28;
  NTuple::Item<double>                        m_sig_134_temp_28;
  NTuple::Item<double>                        m_sig_135_temp_28;
  NTuple::Item<double>                        m_sig_234_temp_28;
  NTuple::Item<double>                        m_sig_235_temp_28;
  NTuple::Item<double>                        m_sig_345_temp_28;
  NTuple::Item<double>                       m_sig_1234_temp_28;
  NTuple::Item<double>                         gam_emax_temp_28;
  NTuple::Item<int>                       Ncharge_ex_temp_28;
                                         
  NTuple::Item<int>                             pi0_num_temp_28;
  NTuple::Item<double>                      sig_mass_bc_temp_28;
  NTuple::Item<double>                       sig_deltaE_temp_28;
  NTuple::Item<double>                          T_pdp_temp_28;
  NTuple::Item<int>                         T_tagmode_temp_28;
  NTuple::Item<int>                              m_irec_temp_28;
  NTuple::Item<int>                              m_irun_temp_28;
  NTuple::Item<int>                       sig_tagcharge_temp_28;
  NTuple::Item<double>                            mdbc1_temp_28;
  NTuple::Item<double>                            mdbc2_temp_28;
  NTuple::Item<int>                             mcmode1_temp_28;
  NTuple::Item<int>                             mcmode2_temp_28;
  NTuple::Item<int>                             mcmodea_temp_28;
  NTuple::Item<int>                             mcmodeb_temp_28;
                                         
  NTuple::Item<double>                          mbc_sig_temp_28;
  NTuple::Item<double>                         delE_sig_temp_28;
  NTuple::Item<double>                         mass_inv_temp_28;
  NTuple::Item<double>                              H_w_temp_28;
  NTuple::Item<double>                             CL_k_temp_28;
  NTuple::Item<double>                          CL_k_pi_temp_28;
  NTuple::Item<double>                           CL_pi1_temp_28;
  NTuple::Item<double>                         CL_pi1_k_temp_28;
  NTuple::Item<double>                           CL_pi2_temp_28;
  NTuple::Item<double>                         CL_pi2_k_temp_28;
  NTuple::Item<double>                          pi0_chi_temp_28;
  NTuple::Item<double>                          eta_chi_temp_28;

  NTuple::Item<double>                           angle1_temp_28;
  NTuple::Item<double>                           angle2_temp_28;
  NTuple::Item<double>                           angle3_temp_28;
  NTuple::Item<double>                           angle4_temp_28;
  NTuple::Item<double>                           angle5_temp_28;
  NTuple::Item<double>                           angle6_temp_28;
  NTuple::Item<double>                         T_angle1_temp_28;
  NTuple::Item<double>                         T_angle2_temp_28;
  NTuple::Item<double>                         T_angle3_temp_28;
  NTuple::Item<double>                         T_angle4_temp_28;
  NTuple::Item<double>                         T_angle5_temp_28;
  NTuple::Item<double>                         T_angle6_temp_28;

  NTuple::Tuple*  m_tuple29;
  NTuple::Item<int>                               index_temp_29;
  NTuple::Array<double>                            V4_1_temp_29;
  NTuple::Array<double>                            V4_2_temp_29;
  NTuple::Array<double>                            V4_3_temp_29;
  NTuple::Array<double>                            V4_4_temp_29;
  NTuple::Array<double>                            V4_5_temp_29;

  NTuple::Item<int>                           cosmicray_temp_29;
  NTuple::Item<double>                            gam_e_temp_29;

  NTuple::Item<double>                          p_sig_1_temp_29;
  NTuple::Item<double>                    p_sig_1_theta_temp_29;
  NTuple::Item<double>                          p_sig_2_temp_29;
  NTuple::Item<double>                    p_sig_2_theta_temp_29;
  NTuple::Item<double>                          p_sig_3_temp_29;
  NTuple::Item<double>                    p_sig_3_theta_temp_29;
  NTuple::Item<double>                          p_sig_4_temp_29;
  NTuple::Item<double>                    p_sig_4_theta_temp_29;
  NTuple::Item<double>                          p_sig_5_temp_29;
  NTuple::Item<double>                    p_sig_5_theta_temp_29;

  NTuple::Item<double>                         m_sig_12_temp_29;
  NTuple::Item<double>                         m_sig_13_temp_29;
  NTuple::Item<double>                         m_sig_14_temp_29;
  NTuple::Item<double>                         m_sig_15_temp_29;
  NTuple::Item<double>                         m_sig_23_temp_29;
  NTuple::Item<double>                         m_sig_24_temp_29;
  NTuple::Item<double>                         m_sig_25_temp_29;
  NTuple::Item<double>                         m_sig_34_temp_29;
  NTuple::Item<double>                         m_sig_35_temp_29;
  NTuple::Item<double>                         m_sig_45_temp_29;
  NTuple::Item<double>                        m_sig_123_temp_29;
  NTuple::Item<double>                        m_sig_124_temp_29;
  NTuple::Item<double>                        m_sig_125_temp_29;
  NTuple::Item<double>                        m_sig_134_temp_29;
  NTuple::Item<double>                        m_sig_135_temp_29;
  NTuple::Item<double>                        m_sig_234_temp_29;
  NTuple::Item<double>                        m_sig_235_temp_29;
  NTuple::Item<double>                        m_sig_345_temp_29;
  NTuple::Item<double>                       m_sig_1234_temp_29;
  NTuple::Item<double>                         gam_emax_temp_29;
  NTuple::Item<int>                       Ncharge_ex_temp_29;
                                         
  NTuple::Item<int>                             pi0_num_temp_29;
  NTuple::Item<double>                      sig_mass_bc_temp_29;
  NTuple::Item<double>                       sig_deltaE_temp_29;
  NTuple::Item<double>                          T_pdp_temp_29;
  NTuple::Item<int>                         T_tagmode_temp_29;
  NTuple::Item<int>                              m_irec_temp_29;
  NTuple::Item<int>                              m_irun_temp_29;
  NTuple::Item<int>                       sig_tagcharge_temp_29;
  NTuple::Item<double>                            mdbc1_temp_29;
  NTuple::Item<double>                            mdbc2_temp_29;
  NTuple::Item<int>                             mcmode1_temp_29;
  NTuple::Item<int>                             mcmode2_temp_29;
  NTuple::Item<int>                             mcmodea_temp_29;
  NTuple::Item<int>                             mcmodeb_temp_29;
                                         
  NTuple::Item<double>                          mbc_sig_temp_29;
  NTuple::Item<double>                         delE_sig_temp_29;
  NTuple::Item<double>                         mass_inv_temp_29;
  NTuple::Item<double>                              H_w_temp_29;
  NTuple::Item<double>                             CL_k_temp_29;
  NTuple::Item<double>                          CL_k_pi_temp_29;
  NTuple::Item<double>                           CL_pi1_temp_29;
  NTuple::Item<double>                         CL_pi1_k_temp_29;
  NTuple::Item<double>                           CL_pi2_temp_29;
  NTuple::Item<double>                         CL_pi2_k_temp_29;
  NTuple::Item<double>                          pi0_chi_temp_29;
  NTuple::Item<double>                          eta_chi_temp_29;


  NTuple::Item<double>                           angle1_temp_29;
  NTuple::Item<double>                           angle2_temp_29;
  NTuple::Item<double>                           angle3_temp_29;
  NTuple::Item<double>                           angle4_temp_29;
  NTuple::Item<double>                           angle5_temp_29;
  NTuple::Item<double>                           angle6_temp_29;
  NTuple::Item<double>                         T_angle1_temp_29;
  NTuple::Item<double>                         T_angle2_temp_29;
  NTuple::Item<double>                         T_angle3_temp_29;
  NTuple::Item<double>                         T_angle4_temp_29;
  NTuple::Item<double>                         T_angle5_temp_29;
  NTuple::Item<double>                         T_angle6_temp_29;
*/
  NTuple::Tuple*  m_tuple30;
  NTuple::Item<int>                               index_temp_30;
  NTuple::Array<double>                            V4_1_temp_30;
  NTuple::Array<double>                            V4_2_temp_30;
  NTuple::Array<double>                            V4_3_temp_30;
  NTuple::Array<double>                            V4_4_temp_30;
  NTuple::Array<double>                            V4_5_temp_30;

  NTuple::Item<int>                        cosmicray_temp_30;
  NTuple::Item<double>                            gam_e_temp_30;

  NTuple::Item<double>                          p_sig_1_temp_30;
  NTuple::Item<double>                    p_sig_1_theta_temp_30;
  NTuple::Item<double>                          p_sig_2_temp_30;
  NTuple::Item<double>                    p_sig_2_theta_temp_30;
  NTuple::Item<double>                          p_sig_3_temp_30;
  NTuple::Item<double>                    p_sig_3_theta_temp_30;
  NTuple::Item<double>                          p_sig_4_temp_30;
  NTuple::Item<double>                    p_sig_4_theta_temp_30;
  NTuple::Item<double>                          p_sig_5_temp_30;
  NTuple::Item<double>                    p_sig_5_theta_temp_30;

  NTuple::Item<double>                         m_sig_12_temp_30;
  NTuple::Item<double>                         m_sig_13_temp_30;
  NTuple::Item<double>                         m_sig_14_temp_30;
  NTuple::Item<double>                         m_sig_15_temp_30;
  NTuple::Item<double>                         m_sig_23_temp_30;
  NTuple::Item<double>                         m_sig_24_temp_30;
  NTuple::Item<double>                         m_sig_25_temp_30;
  NTuple::Item<double>                         m_sig_34_temp_30;
  NTuple::Item<double>                         m_sig_35_temp_30;
  NTuple::Item<double>                         m_sig_45_temp_30;
  NTuple::Item<double>                        m_sig_123_temp_30;
  NTuple::Item<double>                        m_sig_124_temp_30;
  NTuple::Item<double>                        m_sig_134_temp_30;
  NTuple::Item<double>                        m_sig_234_temp_30;
  NTuple::Item<double>                       m_sig_1234_temp_30;
  NTuple::Item<double>                         gam_emax_temp_30;
  NTuple::Item<double>                                x_temp_30;
  NTuple::Item<double>                                y_temp_30;
  NTuple::Item<double>                           lambda_temp_30;
  NTuple::Item<double>                       lambda_max_temp_30;
  NTuple::Item<int>                          Ncharge_ex_temp_30;
                                         
  NTuple::Item<int>                             pi0_num_temp_30;
  NTuple::Item<double>                      sig_mass_bc_temp_30;
  NTuple::Item<double>                       sig_deltaE_temp_30;
  NTuple::Item<double>                          T_pdp_temp_30;
  NTuple::Item<int>                         T_tagmode_temp_30;
  NTuple::Item<int>                              m_irec_temp_30;
  NTuple::Item<int>                              m_irun_temp_30;
  NTuple::Item<int>                       sig_tagcharge_temp_30;
  NTuple::Item<double>                            mdbc1_temp_30;
  NTuple::Item<double>                            mdbc2_temp_30;
  NTuple::Item<int>                             mcmode1_temp_30;
  NTuple::Item<int>                             mcmode2_temp_30;
  NTuple::Item<int>                             mcmodea_temp_30;
  NTuple::Item<int>                             mcmodeb_temp_30;
                                         
  NTuple::Item<double>                          mbc_sig_temp_30;
  NTuple::Item<double>                         delE_sig_temp_30;
  NTuple::Item<double>                         mass_inv_temp_30;
  NTuple::Item<double>                              H_w_temp_30;
  NTuple::Item<double>                             CL_k_temp_30;
  NTuple::Item<double>                          CL_k_pi_temp_30;
  NTuple::Item<double>                           CL_pi1_temp_30;
  NTuple::Item<double>                         CL_pi1_k_temp_30;
  NTuple::Item<double>                           CL_pi2_temp_30;
  NTuple::Item<double>                         CL_pi2_k_temp_30;
  NTuple::Item<double>                          pi0_chi_temp_30;

  NTuple::Item<double>                             A_DD_temp_30;

  NTuple::Item<double>                           angle1_temp_30;
  NTuple::Item<double>                           angle2_temp_30;
  NTuple::Item<double>                           angle3_temp_30;
  NTuple::Item<double>                           angle4_temp_30;
  NTuple::Item<double>                           angle5_temp_30;
  NTuple::Item<double>                           angle6_temp_30;
  NTuple::Item<double>                         T_angle1_temp_30;
  NTuple::Item<double>                         T_angle2_temp_30;
  NTuple::Item<double>                         T_angle3_temp_30;
  NTuple::Item<double>                         T_angle4_temp_30;
  NTuple::Item<double>                         T_angle5_temp_30;
  NTuple::Item<double>                         T_angle6_temp_30;
  NTuple::Item<int>                               mctag_temp_30;

  NTuple::Tuple*  m_tuple31;
  NTuple::Item<int>                                topo_temp_31;
  NTuple::Array<int>                           pdgid_temp_31;
  NTuple::Array<int>                           mcidx_temp_31;


  NTuple::Item<int>                               index_temp_31;
  NTuple::Array<double>                            V4_1_temp_31;
  NTuple::Array<double>                            V4_2_temp_31;
  NTuple::Array<double>                            V4_3_temp_31;
  NTuple::Array<double>                            V4_4_temp_31;
  NTuple::Array<double>                            V4_5_temp_31;

  NTuple::Item<int>                               mctag_temp_31;

  NTuple::Item<int>                           cosmicray_temp_31;
  NTuple::Item<double>                            gam_e_temp_31;

  NTuple::Item<double>                          p_sig_1_temp_31;
  NTuple::Item<double>                    p_sig_1_theta_temp_31;
  NTuple::Item<double>                          p_sig_2_temp_31;
  NTuple::Item<double>                    p_sig_2_theta_temp_31;
  NTuple::Item<double>                          p_sig_3_temp_31;
  NTuple::Item<double>                    p_sig_3_theta_temp_31;
  NTuple::Item<double>                          p_sig_4_temp_31;
  NTuple::Item<double>                    p_sig_4_theta_temp_31;
  NTuple::Item<double>                          p_sig_5_temp_31;
  NTuple::Item<double>                    p_sig_5_theta_temp_31;

  NTuple::Item<double>                         m_sig_12_temp_31;
  NTuple::Item<double>                         m_sig_13_temp_31;
  NTuple::Item<double>                         m_sig_14_temp_31;
  NTuple::Item<double>                         m_sig_15_temp_31;
  NTuple::Item<double>                         m_sig_23_temp_31;
  NTuple::Item<double>                         m_sig_24_temp_31;
  NTuple::Item<double>                         m_sig_25_temp_31;
  NTuple::Item<double>                         m_sig_34_temp_31;
  NTuple::Item<double>                         m_sig_35_temp_31;
  NTuple::Item<double>                         m_sig_45_temp_31;
  NTuple::Item<double>                        m_sig_123_temp_31;
  NTuple::Item<double>                        m_sig_124_temp_31;
  NTuple::Item<double>                        m_sig_125_temp_31;
  NTuple::Item<double>                        m_sig_134_temp_31;
  NTuple::Item<double>                        m_sig_135_temp_31;
  NTuple::Item<double>                        m_sig_234_temp_31;
  NTuple::Item<double>                        m_sig_235_temp_31;
  NTuple::Item<double>                        m_sig_345_temp_31;
  NTuple::Item<double>                       m_sig_1234_temp_31;
  NTuple::Item<double>                         gam_emax_temp_31;
  NTuple::Item<int>                       Ncharge_ex_temp_31;
                                         
  NTuple::Item<int>                             pi0_num_temp_31;
  NTuple::Item<double>                      sig_mass_bc_temp_31;
  NTuple::Item<double>                       sig_deltaE_temp_31;
  NTuple::Item<double>                          T_pdp_temp_31;
  NTuple::Item<int>                         T_tagmode_temp_31;
  NTuple::Item<int>                              m_irec_temp_31;
  NTuple::Item<int>                              m_irun_temp_31;
  NTuple::Item<int>                       sig_tagcharge_temp_31;
  NTuple::Item<double>                            mdbc1_temp_31;
  NTuple::Item<double>                            mdbc2_temp_31;
  NTuple::Item<int>                             mcmode1_temp_31;
  NTuple::Item<int>                             mcmode2_temp_31;
  NTuple::Item<int>                             mcmodea_temp_31;
  NTuple::Item<int>                             mcmodeb_temp_31;
                                         
  NTuple::Item<double>                          mbc_sig_temp_31;
  NTuple::Item<double>                         delE_sig_temp_31;
  NTuple::Item<double>                         mass_inv_temp_31;
  NTuple::Item<double>                              H_w_temp_31;
  NTuple::Item<double>                             CL_k_temp_31;
  NTuple::Item<double>                          CL_k_pi_temp_31;
  NTuple::Item<double>                           CL_pi1_temp_31;
  NTuple::Item<double>                         CL_pi1_k_temp_31;
  NTuple::Item<double>                           CL_pi2_temp_31;
  NTuple::Item<double>                         CL_pi2_k_temp_31;
  NTuple::Item<double>                          pi0_chi_temp_31;
  NTuple::Item<double>                          eta_chi_temp_31;

  NTuple::Item<double>                             A_DD_temp_31;
  NTuple::Item<double>                           angle1_temp_31;
  NTuple::Item<double>                           angle2_temp_31;
  NTuple::Item<double>                           angle3_temp_31;
  NTuple::Item<double>                           angle4_temp_31;
  NTuple::Item<double>                           angle5_temp_31;
  NTuple::Item<double>                           angle6_temp_31;
  NTuple::Item<double>                         T_angle1_temp_31;
  NTuple::Item<double>                         T_angle2_temp_31;
  NTuple::Item<double>                         T_angle3_temp_31;
  NTuple::Item<double>                         T_angle4_temp_31;
  NTuple::Item<double>                         T_angle5_temp_31;
  NTuple::Item<double>                         T_angle6_temp_31;
/*
  NTuple::Tuple*  m_tuple32;
  NTuple::Item<int>                               index_temp_32;
  NTuple::Array<double>                            V4_1_temp_32;
  NTuple::Array<double>                            V4_2_temp_32;
  NTuple::Array<double>                            V4_3_temp_32;
  NTuple::Array<double>                            V4_4_temp_32;
  NTuple::Array<double>                            V4_5_temp_32;

  NTuple::Item<int>                           cosmicray_temp_32;
  NTuple::Item<double>                            gam_e_temp_32;

  NTuple::Item<double>                          p_sig_1_temp_32;
  NTuple::Item<double>                    p_sig_1_theta_temp_32;
  NTuple::Item<double>                          p_sig_2_temp_32;
  NTuple::Item<double>                    p_sig_2_theta_temp_32;
  NTuple::Item<double>                          p_sig_3_temp_32;
  NTuple::Item<double>                    p_sig_3_theta_temp_32;
  NTuple::Item<double>                          p_sig_4_temp_32;
  NTuple::Item<double>                    p_sig_4_theta_temp_32;
  NTuple::Item<double>                          p_sig_5_temp_32;
  NTuple::Item<double>                    p_sig_5_theta_temp_32;

  NTuple::Item<double>                         m_sig_12_temp_32;
  NTuple::Item<double>                         m_sig_13_temp_32;
  NTuple::Item<double>                         m_sig_14_temp_32;
  NTuple::Item<double>                         m_sig_15_temp_32;
  NTuple::Item<double>                         m_sig_23_temp_32;
  NTuple::Item<double>                         m_sig_24_temp_32;
  NTuple::Item<double>                         m_sig_25_temp_32;
  NTuple::Item<double>                         m_sig_34_temp_32;
  NTuple::Item<double>                         m_sig_35_temp_32;
  NTuple::Item<double>                         m_sig_45_temp_32;
  NTuple::Item<double>                        m_sig_123_temp_32;
  NTuple::Item<double>                        m_sig_124_temp_32;
  NTuple::Item<double>                        m_sig_125_temp_32;
  NTuple::Item<double>                        m_sig_134_temp_32;
  NTuple::Item<double>                        m_sig_135_temp_32;
  NTuple::Item<double>                        m_sig_234_temp_32;
  NTuple::Item<double>                        m_sig_235_temp_32;
  NTuple::Item<double>                        m_sig_345_temp_32;
  NTuple::Item<double>                       m_sig_1234_temp_32;
  NTuple::Item<double>                         gam_emax_temp_32;
  NTuple::Item<int>                       Ncharge_ex_temp_32;
                                         
  NTuple::Item<int>                             pi0_num_temp_32;
  NTuple::Item<double>                      sig_mass_bc_temp_32;
  NTuple::Item<double>                       sig_deltaE_temp_32;
  NTuple::Item<double>                          T_pdp_temp_32;
  NTuple::Item<int>                         T_tagmode_temp_32;
  NTuple::Item<int>                              m_irec_temp_32;
  NTuple::Item<int>                              m_irun_temp_32;
  NTuple::Item<int>                       sig_tagcharge_temp_32;
  NTuple::Item<double>                            mdbc1_temp_32;
  NTuple::Item<double>                            mdbc2_temp_32;
  NTuple::Item<int>                             mcmode1_temp_32;
  NTuple::Item<int>                             mcmode2_temp_32;
  NTuple::Item<int>                             mcmodea_temp_32;
  NTuple::Item<int>                             mcmodeb_temp_32;
                                         
  NTuple::Item<double>                          mbc_sig_temp_32;
  NTuple::Item<double>                         delE_sig_temp_32;
  NTuple::Item<double>                         mass_inv_temp_32;
  NTuple::Item<double>                              H_w_temp_32;
  NTuple::Item<double>                             CL_k_temp_32;
  NTuple::Item<double>                          CL_k_pi_temp_32;
  NTuple::Item<double>                           CL_pi1_temp_32;
  NTuple::Item<double>                         CL_pi1_k_temp_32;
  NTuple::Item<double>                           CL_pi2_temp_32;
  NTuple::Item<double>                         CL_pi2_k_temp_32;
  NTuple::Item<double>                          pi0_chi_temp_32;
  NTuple::Item<double>                          eta_chi_temp_32;

  NTuple::Item<double>                           angle1_temp_32;
  NTuple::Item<double>                           angle2_temp_32;
  NTuple::Item<double>                           angle3_temp_32;
  NTuple::Item<double>                           angle4_temp_32;
  NTuple::Item<double>                           angle5_temp_32;
  NTuple::Item<double>                           angle6_temp_32;
  NTuple::Item<double>                         T_angle1_temp_32;
  NTuple::Item<double>                         T_angle2_temp_32;
  NTuple::Item<double>                         T_angle3_temp_32;
  NTuple::Item<double>                         T_angle4_temp_32;
  NTuple::Item<double>                         T_angle5_temp_32;
  NTuple::Item<double>                         T_angle6_temp_32;

  NTuple::Tuple*  m_tuple33;
  NTuple::Item<int>                               index_temp_33;
  NTuple::Array<double>                            V4_1_temp_33;
  NTuple::Array<double>                            V4_2_temp_33;
  NTuple::Array<double>                            V4_3_temp_33;
  NTuple::Array<double>                            V4_4_temp_33;
  NTuple::Array<double>                            V4_5_temp_33;

  NTuple::Item<int>                           cosmicray_temp_33;
  NTuple::Item<double>                            gam_e_temp_33;

  NTuple::Item<double>                          p_sig_1_temp_33;
  NTuple::Item<double>                    p_sig_1_theta_temp_33;
  NTuple::Item<double>                          p_sig_2_temp_33;
  NTuple::Item<double>                    p_sig_2_theta_temp_33;
  NTuple::Item<double>                          p_sig_3_temp_33;
  NTuple::Item<double>                    p_sig_3_theta_temp_33;
  NTuple::Item<double>                          p_sig_4_temp_33;
  NTuple::Item<double>                    p_sig_4_theta_temp_33;
  NTuple::Item<double>                          p_sig_5_temp_33;
  NTuple::Item<double>                    p_sig_5_theta_temp_33;

  NTuple::Item<double>                         m_sig_12_temp_33;
  NTuple::Item<double>                         m_sig_13_temp_33;
  NTuple::Item<double>                         m_sig_14_temp_33;
  NTuple::Item<double>                         m_sig_15_temp_33;
  NTuple::Item<double>                         m_sig_23_temp_33;
  NTuple::Item<double>                         m_sig_24_temp_33;
  NTuple::Item<double>                         m_sig_25_temp_33;
  NTuple::Item<double>                         m_sig_34_temp_33;
  NTuple::Item<double>                         m_sig_35_temp_33;
  NTuple::Item<double>                         m_sig_45_temp_33;
  NTuple::Item<double>                        m_sig_123_temp_33;
  NTuple::Item<double>                        m_sig_124_temp_33;
  NTuple::Item<double>                        m_sig_125_temp_33;
  NTuple::Item<double>                        m_sig_134_temp_33;
  NTuple::Item<double>                        m_sig_135_temp_33;
  NTuple::Item<double>                        m_sig_234_temp_33;
  NTuple::Item<double>                        m_sig_235_temp_33;
  NTuple::Item<double>                        m_sig_345_temp_33;
  NTuple::Item<double>                       m_sig_1234_temp_33;
  NTuple::Item<double>                         gam_emax_temp_33;
  NTuple::Item<int>                       Ncharge_ex_temp_33;
                                         
  NTuple::Item<int>                             pi0_num_temp_33;
  NTuple::Item<double>                      sig_mass_bc_temp_33;
  NTuple::Item<double>                       sig_deltaE_temp_33;
  NTuple::Item<double>                          T_pdp_temp_33;
  NTuple::Item<int>                         T_tagmode_temp_33;
  NTuple::Item<int>                              m_irec_temp_33;
  NTuple::Item<int>                              m_irun_temp_33;
  NTuple::Item<int>                       sig_tagcharge_temp_33;
  NTuple::Item<double>                            mdbc1_temp_33;
  NTuple::Item<double>                            mdbc2_temp_33;
  NTuple::Item<int>                             mcmode1_temp_33;
  NTuple::Item<int>                             mcmode2_temp_33;
  NTuple::Item<int>                             mcmodea_temp_33;
  NTuple::Item<int>                             mcmodeb_temp_33;
                                         
  NTuple::Item<double>                          mbc_sig_temp_33;
  NTuple::Item<double>                         delE_sig_temp_33;
  NTuple::Item<double>                         mass_inv_temp_33;
  NTuple::Item<double>                              H_w_temp_33;
  NTuple::Item<double>                             CL_k_temp_33;
  NTuple::Item<double>                          CL_k_pi_temp_33;
  NTuple::Item<double>                           CL_pi1_temp_33;
  NTuple::Item<double>                         CL_pi1_k_temp_33;
  NTuple::Item<double>                           CL_pi2_temp_33;
  NTuple::Item<double>                         CL_pi2_k_temp_33;
  NTuple::Item<double>                          pi0_chi_temp_33;
  NTuple::Item<double>                          eta_chi_temp_33;

  NTuple::Item<double>                           angle1_temp_33;
  NTuple::Item<double>                           angle2_temp_33;
  NTuple::Item<double>                           angle3_temp_33;
  NTuple::Item<double>                           angle4_temp_33;
  NTuple::Item<double>                           angle5_temp_33;
  NTuple::Item<double>                           angle6_temp_33;
  NTuple::Item<double>                         T_angle1_temp_33;
  NTuple::Item<double>                         T_angle2_temp_33;
  NTuple::Item<double>                         T_angle3_temp_33;
  NTuple::Item<double>                         T_angle4_temp_33;
  NTuple::Item<double>                         T_angle5_temp_33;
  NTuple::Item<double>                         T_angle6_temp_33;

  NTuple::Tuple*  m_tuple34;
  NTuple::Item<int>                               index_temp_34;
  NTuple::Array<double>                            V4_1_temp_34;
  NTuple::Array<double>                            V4_2_temp_34;
  NTuple::Array<double>                            V4_3_temp_34;
  NTuple::Array<double>                            V4_4_temp_34;
  NTuple::Array<double>                            V4_5_temp_34;

  NTuple::Item<int>                           cosmicray_temp_34;
  NTuple::Item<double>                            gam_e_temp_34;

  NTuple::Item<double>                          p_sig_1_temp_34;
  NTuple::Item<double>                    p_sig_1_theta_temp_34;
  NTuple::Item<double>                          p_sig_2_temp_34;
  NTuple::Item<double>                    p_sig_2_theta_temp_34;
  NTuple::Item<double>                          p_sig_3_temp_34;
  NTuple::Item<double>                    p_sig_3_theta_temp_34;
  NTuple::Item<double>                          p_sig_4_temp_34;
  NTuple::Item<double>                    p_sig_4_theta_temp_34;
  NTuple::Item<double>                          p_sig_5_temp_34;
  NTuple::Item<double>                    p_sig_5_theta_temp_34;

  NTuple::Item<double>                         m_sig_12_temp_34;
  NTuple::Item<double>                         m_sig_13_temp_34;
  NTuple::Item<double>                         m_sig_14_temp_34;
  NTuple::Item<double>                         m_sig_15_temp_34;
  NTuple::Item<double>                         m_sig_23_temp_34;
  NTuple::Item<double>                         m_sig_24_temp_34;
  NTuple::Item<double>                         m_sig_25_temp_34;
  NTuple::Item<double>                         m_sig_34_temp_34;
  NTuple::Item<double>                         m_sig_35_temp_34;
  NTuple::Item<double>                         m_sig_45_temp_34;
  NTuple::Item<double>                        m_sig_123_temp_34;
  NTuple::Item<double>                        m_sig_124_temp_34;
  NTuple::Item<double>                        m_sig_125_temp_34;
  NTuple::Item<double>                        m_sig_134_temp_34;
  NTuple::Item<double>                        m_sig_135_temp_34;
  NTuple::Item<double>                        m_sig_234_temp_34;
  NTuple::Item<double>                        m_sig_235_temp_34;
  NTuple::Item<double>                        m_sig_345_temp_34;
  NTuple::Item<double>                       m_sig_1234_temp_34;
  NTuple::Item<double>                         gam_emax_temp_34;
  NTuple::Item<int>                       Ncharge_ex_temp_34;
                                         
  NTuple::Item<int>                             pi0_num_temp_34;
  NTuple::Item<double>                      sig_mass_bc_temp_34;
  NTuple::Item<double>                       sig_deltaE_temp_34;
  NTuple::Item<double>                          T_pdp_temp_34;
  NTuple::Item<int>                         T_tagmode_temp_34;
  NTuple::Item<int>                              m_irec_temp_34;
  NTuple::Item<int>                              m_irun_temp_34;
  NTuple::Item<int>                       sig_tagcharge_temp_34;
  NTuple::Item<double>                            mdbc1_temp_34;
  NTuple::Item<double>                            mdbc2_temp_34;
  NTuple::Item<int>                             mcmode1_temp_34;
  NTuple::Item<int>                             mcmode2_temp_34;
  NTuple::Item<int>                             mcmodea_temp_34;
  NTuple::Item<int>                             mcmodeb_temp_34;
                                         
  NTuple::Item<double>                          mbc_sig_temp_34;
  NTuple::Item<double>                         delE_sig_temp_34;
  NTuple::Item<double>                         mass_inv_temp_34;
  NTuple::Item<double>                              H_w_temp_34;
  NTuple::Item<double>                             CL_k_temp_34;
  NTuple::Item<double>                          CL_k_pi_temp_34;
  NTuple::Item<double>                           CL_pi1_temp_34;
  NTuple::Item<double>                         CL_pi1_k_temp_34;
  NTuple::Item<double>                           CL_pi2_temp_34;
  NTuple::Item<double>                         CL_pi2_k_temp_34;
  NTuple::Item<double>                          pi0_chi_temp_34;
  NTuple::Item<double>                          eta_chi_temp_34;

  NTuple::Item<double>                           angle1_temp_34;
  NTuple::Item<double>                           angle2_temp_34;
  NTuple::Item<double>                           angle3_temp_34;
  NTuple::Item<double>                           angle4_temp_34;
  NTuple::Item<double>                           angle5_temp_34;
  NTuple::Item<double>                           angle6_temp_34;
  NTuple::Item<double>                         T_angle1_temp_34;
  NTuple::Item<double>                         T_angle2_temp_34;
  NTuple::Item<double>                         T_angle3_temp_34;
  NTuple::Item<double>                         T_angle4_temp_34;
  NTuple::Item<double>                         T_angle5_temp_34;
  NTuple::Item<double>                         T_angle6_temp_34;


*/

  NTuple::Tuple*  m_tuple35;
  NTuple::Item<int>                               index_temp_35;
  NTuple::Array<double>                            V4_1_temp_35;
  NTuple::Array<double>                            V4_2_temp_35;
  NTuple::Array<double>                            V4_3_temp_35;
  NTuple::Array<double>                            V4_4_temp_35;
  NTuple::Array<double>                            V4_5_temp_35;

  NTuple::Item<int>                           cosmicray_temp_35;
  NTuple::Item<double>                            gam_e_temp_35;

  NTuple::Item<double>                          p_sig_1_temp_35;
  NTuple::Item<double>                    p_sig_1_theta_temp_35;
  NTuple::Item<double>                          p_sig_2_temp_35;
  NTuple::Item<double>                    p_sig_2_theta_temp_35;
  NTuple::Item<double>                          p_sig_3_temp_35;
  NTuple::Item<double>                    p_sig_3_theta_temp_35;
  NTuple::Item<double>                          p_sig_4_temp_35;
  NTuple::Item<double>                    p_sig_4_theta_temp_35;
  NTuple::Item<double>                          p_sig_5_temp_35;
  NTuple::Item<double>                    p_sig_5_theta_temp_35;

  NTuple::Item<double>                         m_sig_12_temp_35;
  NTuple::Item<double>                         m_sig_13_temp_35;
  NTuple::Item<double>                         m_sig_14_temp_35;
  NTuple::Item<double>                         m_sig_15_temp_35;
  NTuple::Item<double>                         m_sig_23_temp_35;
  NTuple::Item<double>                         m_sig_24_temp_35;
  NTuple::Item<double>                         m_sig_25_temp_35;
  NTuple::Item<double>                         m_sig_34_temp_35;
  NTuple::Item<double>                         m_sig_35_temp_35;
  NTuple::Item<double>                         m_sig_45_temp_35;
  NTuple::Item<double>                        m_sig_123_temp_35;
  NTuple::Item<double>                        m_sig_124_temp_35;
  NTuple::Item<double>                        m_sig_125_temp_35;
  NTuple::Item<double>                        m_sig_134_temp_35;
  NTuple::Item<double>                        m_sig_135_temp_35;
  NTuple::Item<double>                        m_sig_234_temp_35;
  NTuple::Item<double>                        m_sig_235_temp_35;
  NTuple::Item<double>                        m_sig_345_temp_35;
  NTuple::Item<double>                       m_sig_1234_temp_35;
  NTuple::Item<double>                         gam_emax_temp_35;
  NTuple::Item<int>                       Ncharge_ex_temp_35;
                                         
  NTuple::Item<double>                             A_DD_temp_35;
  NTuple::Item<int>                             pi0_num_temp_35;
  NTuple::Item<double>                      sig_mass_bc_temp_35;
  NTuple::Item<double>                       sig_deltaE_temp_35;
  NTuple::Item<double>                          T_pdp_temp_35;
  NTuple::Item<int>                         T_tagmode_temp_35;
  NTuple::Item<int>                              m_irec_temp_35;
  NTuple::Item<int>                              m_irun_temp_35;
  NTuple::Item<int>                       sig_tagcharge_temp_35;
  NTuple::Item<double>                            mdbc1_temp_35;
  NTuple::Item<double>                            mdbc2_temp_35;
  NTuple::Item<int>                             mcmode1_temp_35;
  NTuple::Item<int>                             mcmode2_temp_35;
  NTuple::Item<int>                             mcmodea_temp_35;
  NTuple::Item<int>                             mcmodeb_temp_35;
                                         
  NTuple::Item<double>                          mbc_sig_temp_35;
  NTuple::Item<double>                         delE_sig_temp_35;
  NTuple::Item<double>                         mass_inv_temp_35;
  NTuple::Item<double>                              H_w_temp_35;
  NTuple::Item<double>                             CL_k_temp_35;
  NTuple::Item<double>                          CL_k_pi_temp_35;
  NTuple::Item<double>                           CL_pi1_temp_35;
  NTuple::Item<double>                         CL_pi1_k_temp_35;
  NTuple::Item<double>                           CL_pi2_temp_35;
  NTuple::Item<double>                         CL_pi2_k_temp_35;
  NTuple::Item<double>                          pi0_chi_temp_35;
  NTuple::Item<double>                          eta_chi_temp_35;

  NTuple::Item<double>                           angle1_temp_35;
  NTuple::Item<double>                           angle2_temp_35;
  NTuple::Item<double>                           angle3_temp_35;
  NTuple::Item<double>                           angle4_temp_35;
  NTuple::Item<double>                           angle5_temp_35;
  NTuple::Item<double>                           angle6_temp_35;
  NTuple::Item<double>                         T_angle1_temp_35;
  NTuple::Item<double>                         T_angle2_temp_35;
  NTuple::Item<double>                         T_angle3_temp_35;
  NTuple::Item<double>                         T_angle4_temp_35;
  NTuple::Item<double>                         T_angle5_temp_35;
  NTuple::Item<double>                         T_angle6_temp_35;
  NTuple::Item<int>                               mctag_temp_35;

  NTuple::Tuple*  m_tuple36;
  NTuple::Item<int>                               index_temp_36;
  NTuple::Array<double>                            V4_1_temp_36;
  NTuple::Array<double>                            V4_2_temp_36;
  NTuple::Array<double>                            V4_3_temp_36;
  NTuple::Array<double>                            V4_4_temp_36;
  NTuple::Array<double>                            V4_5_temp_36;

  NTuple::Item<int>                        cosmicray_temp_36;
  NTuple::Item<double>                            gam_e_temp_36;

  NTuple::Item<double>                          p_sig_1_temp_36;
  NTuple::Item<double>                    p_sig_1_theta_temp_36;
  NTuple::Item<double>                          p_sig_2_temp_36;
  NTuple::Item<double>                    p_sig_2_theta_temp_36;
  NTuple::Item<double>                          p_sig_3_temp_36;
  NTuple::Item<double>                    p_sig_3_theta_temp_36;
  NTuple::Item<double>                          p_sig_4_temp_36;
  NTuple::Item<double>                    p_sig_4_theta_temp_36;
  NTuple::Item<double>                          p_sig_5_temp_36;
  NTuple::Item<double>                    p_sig_5_theta_temp_36;

  NTuple::Item<double>                         m_sig_12_temp_36;
  NTuple::Item<double>                         m_sig_13_temp_36;
  NTuple::Item<double>                         m_sig_14_temp_36;
  NTuple::Item<double>                         m_sig_15_temp_36;
  NTuple::Item<double>                         m_sig_23_temp_36;
  NTuple::Item<double>                         m_sig_24_temp_36;
  NTuple::Item<double>                         m_sig_25_temp_36;
  NTuple::Item<double>                         m_sig_34_temp_36;
  NTuple::Item<double>                         m_sig_35_temp_36;
  NTuple::Item<double>                         m_sig_45_temp_36;
  NTuple::Item<double>                        m_sig_123_temp_36;
  NTuple::Item<double>                        m_sig_124_temp_36;
  NTuple::Item<double>                        m_sig_134_temp_36;
  NTuple::Item<double>                        m_sig_234_temp_36;
  NTuple::Item<double>                       m_sig_1234_temp_36;
  NTuple::Item<double>                         gam_emax_temp_36;
  NTuple::Item<int>                       Ncharge_ex_temp_36;
  NTuple::Item<double>                           lambda_temp_36;
  NTuple::Item<double>                       lambda_max_temp_36;
                                         
  NTuple::Item<int>                             pi0_num_temp_36;
  NTuple::Item<double>                      sig_mass_bc_temp_36;
  NTuple::Item<double>                       sig_deltaE_temp_36;
  NTuple::Item<double>                            T_pdp_temp_36;
  NTuple::Item<int>                           T_tagmode_temp_36;
  NTuple::Item<int>                              m_irec_temp_36;
  NTuple::Item<int>                              m_irun_temp_36;
  NTuple::Item<int>                       sig_tagcharge_temp_36;
  NTuple::Item<double>                            mdbc1_temp_36;
  NTuple::Item<double>                            mdbc2_temp_36;
  NTuple::Item<int>                             mcmode1_temp_36;
  NTuple::Item<int>                             mcmode2_temp_36;
  NTuple::Item<int>                             mcmodea_temp_36;
  NTuple::Item<int>                             mcmodeb_temp_36;
                                         
  NTuple::Item<double>                          mbc_sig_temp_36;
  NTuple::Item<double>                         delE_sig_temp_36;
  NTuple::Item<double>                         mass_inv_temp_36;
  NTuple::Item<double>                              H_w_temp_36;
  NTuple::Item<double>                             CL_k_temp_36;
  NTuple::Item<double>                          CL_k_pi_temp_36;
  NTuple::Item<double>                           CL_pi1_temp_36;
  NTuple::Item<double>                         CL_pi1_k_temp_36;
  NTuple::Item<double>                           CL_pi2_temp_36;
  NTuple::Item<double>                         CL_pi2_k_temp_36;
  NTuple::Item<double>                          pi0_chi_temp_36;


  NTuple::Item<double>                           angle1_temp_36;
  NTuple::Item<double>                           angle2_temp_36;
  NTuple::Item<double>                           angle3_temp_36;
  NTuple::Item<double>                           angle4_temp_36;
  NTuple::Item<double>                           angle5_temp_36;
  NTuple::Item<double>                           angle6_temp_36;
  NTuple::Item<double>                         T_angle1_temp_36;
  NTuple::Item<double>                         T_angle2_temp_36;
  NTuple::Item<double>                         T_angle3_temp_36;
  NTuple::Item<double>                         T_angle4_temp_36;
  NTuple::Item<double>                         T_angle5_temp_36;
  NTuple::Item<double>                         T_angle6_temp_36;

  NTuple::Item<int>                               mctag_temp_36;

  NTuple::Item<double>                             A_DD_temp_36;




  NTuple::Tuple*  m_tuplea;
  NTuple::Item<int>     m1_irec ;
  NTuple::Item<int>     m1_irun ;
  NTuple::Item<double>  m1_mdbc1;
  NTuple::Item<double>  m1_mdbc2;
  NTuple::Item<int>     m1_mcmode1;
  NTuple::Item<int>     m1_mcmode2;
  NTuple::Item<int>     m1_mcmodea;
  NTuple::Item<int>     m1_mcmodeb;
  NTuple::Item<int>     m1_mctag;









};







#endif 
