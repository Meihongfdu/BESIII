#ifndef Physics_Analysis_DssInc_H
#define Physics_Analysis_DssInc_H 

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
//#include "VertexFit/ReadBeamParFromDb.h"


class DssInc : public Algorithm {

	public:
		DssInc(const std::string& name, ISvcLocator* pSvcLocator);
		StatusCode initialize();
		StatusCode execute();
		StatusCode finalize();  
		void BubbleSort(std::vector<double> &, std::vector<int> &);

	private:
		int m_irun;
		double energycms;
	bool ifRscan;

		//ReadBeamParFromDb m_reader;
		// Declare r0, z0 cut for charged tracks
		double m_vr0cut;
		double m_vz0cut;
		double m_energyBarrelThreshold;
		double m_energyEndcapThreshold;
		double m_gammaCosBarrelCut;
		double m_gammaCosEndcapMin;
		double m_gammaCosEndcapMax;
		double m_gammaAngleCut;
		bool m_ifdebug;
		bool m_ifcorrection;

		//Declare energy, dphi, dthe cuts for fake gamma's


		NTuple::Tuple*  m_tuple1;      // charged track vertex
		NTuple::Item<int>   m_idxmc;
		NTuple::Array<int>  m_pdgid;
		NTuple::Array<int>  m_motheridx;
		NTuple::Item<double>  m_pxkp_t;
		NTuple::Item<double>  m_pykp_t;
		NTuple::Item<double>  m_pzkp_t;
		NTuple::Item<double>   m_ekp_t;
		NTuple::Item<double>  m_pxkm_t;
		NTuple::Item<double>  m_pykm_t;
		NTuple::Item<double>  m_pzkm_t;
		NTuple::Item<double>   m_ekm_t;
		NTuple::Item<double>  m_pxpi_t;
		NTuple::Item<double>  m_pypi_t;
		NTuple::Item<double>  m_pzpi_t;
		NTuple::Item<double>   m_epi_t;
		NTuple::Item<double>   m_dss_reco_t;
		NTuple::Item<double>   m_dss_t;
		NTuple::Item<double>   m_ds1_t;
		NTuple::Item<double>   m_dssm_t;
		NTuple::Item<double>   m_dssm_reco_t;

		NTuple::Item<long>   m_idxemc;
		NTuple::Array<double>  m_egamma_rec;
		NTuple::Array<double>  m_costhetagamma_rec;
		NTuple::Array<double>  m_phigamma_rec;
		NTuple::Item<int>  m_run;
		NTuple::Item<int>  m_ntrack;
		NTuple::Item<int>  m_ncharge;
		NTuple::Item<int>  m_nkp;
		NTuple::Item<int>  m_nkm;
		NTuple::Item<int>  m_npi;
		NTuple::Item<int>  m_event;
		NTuple::Item<double>  m_vx0;
		NTuple::Item<double>  m_vy0;
		NTuple::Item<double>  m_vz0;
		NTuple::Item<double>  m_vr0;
		NTuple::Item<double>  m_rvxy0;
		NTuple::Item<double>  m_rvz0;
		NTuple::Item<double>  m_rvphi0;
		NTuple::Item<double>  m_cmsenergy;
		
		// variables for the best Dss

		NTuple::Item<int>   m_iall;
		NTuple::Array<int>   pi_pm; 
		NTuple::Array<int>   m_ig; 
		NTuple::Array<double>  m_chisq_dss;
		NTuple::Array<double>  m_ds0;
		NTuple::Array<double>  m_kk;
		NTuple::Array<double>  m_kpp;
		NTuple::Array<double>  m_kmp;
		NTuple::Array<double>  m_kpi;
		NTuple::Array<double>  m_ds;
		NTuple::Array<double>  m_ds_reco;
		NTuple::Array<double>  m_ds_reco_c;
		NTuple::Array<double>  m_dss;
		NTuple::Array<double>  m_dss_c;
		NTuple::Array<double>  m_dss_reco;
		NTuple::Array<double>  m_dss_reco_c;
		NTuple::Array<double>  m_g_reco;
		NTuple::Array<double>  m_pxkp;
		NTuple::Array<double>  m_pxkm;
		NTuple::Array<double>  m_pxpi;
		NTuple::Array<double>  m_pxg;
		NTuple::Array<double>  m_pykp;
		NTuple::Array<double>  m_pykm;
		NTuple::Array<double>  m_pypi;
		NTuple::Array<double>  m_pyg;
		NTuple::Array<double>  m_pzkp;
		NTuple::Array<double>  m_pzkm;
		NTuple::Array<double>  m_pzpi;
		NTuple::Array<double>  m_pzg;
		NTuple::Array<double>  m_ekp;
		NTuple::Array<double>  m_ekm;
		NTuple::Array<double>  m_epi;
		NTuple::Array<double>  m_eg;
		NTuple::Array<double>  m_kinphi;
		NTuple::Array<double>  m_kinkst;

		//if found pi0
		NTuple::Item<int>   m_ipi0;
		NTuple::Array<int>   m_ipi;
		NTuple::Array<int>   m_ipi01;
		NTuple::Array<int>   m_ipi02;
		NTuple::Array<double>  m_chisq_pi0;
		NTuple::Array<double>  m_chisq_pi0_1C;
		NTuple::Array<double>  m_pi0;
		NTuple::Array<double>  m_pi0_reco;
		NTuple::Array<double>  m_pi0_reco_c;
		NTuple::Array<double>  m_pi0dss;
		NTuple::Array<double>  m_pi0dss_c;
		NTuple::Array<double>  m_pi0dss_cc;
		NTuple::Array<double>  m_pi0dss_reco;
		NTuple::Array<double>  m_pi0dss_reco_c;
		NTuple::Array<double>  m_pi0dss_reco_cc;
		NTuple::Array<double>  m_pxpi0;
		NTuple::Array<double>  m_pypi0;
		NTuple::Array<double>  m_pzpi0;
		NTuple::Array<double>  m_epi0;

};

#endif 
