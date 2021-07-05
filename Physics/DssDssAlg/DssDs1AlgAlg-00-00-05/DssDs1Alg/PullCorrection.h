#ifndef Physics_Analysis_Tool_PullCorrection_H
#define Physics_Analysis_Tool_PullCorrection_H
////////////////////////////////////////////////
//  LI Ke 2013.10.14
//  like@ihep.ac.cn
///////////////////////////////////////////////

#include "TMath.h"
#include "TRandom.h"
#include <iostream>
#include <fstream>
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;

class PullCorrection{
	public:
		PullCorrection(HepMatrix & mean_cor, HepMatrix & sigma_cor):Mean_cor(mean_cor),Sigma_cor(sigma_cor){};

		PullCorrection(){

			ifstream file("/workfs/bes/like/boss663p01/workarea/Analysis/SysErrAlg/SysErrAlg-00-00-03/SysErrAlg/PullValue.txt");

			Mean_cor=HepMatrix(8,5,0);
			Sigma_cor=HepMatrix(8,5,0);
			HepVector sigma_tem(5,0);
			while(1){
				if(!file.good())
					break;
				for(int i=0;i<8;i++){
					for(int j=0;j<5;j++){
						//cout<<"init i = "<< i<<" init j= "<<j<<endl;
						file>>Mean_cor[i][j]>>sigma_tem[j];
						Sigma_cor[i][j]=sqrt(sigma_tem[j]*sigma_tem[j]-1);
						//cout<<" sigma("<<i<<j<<") = "<<Sigma_cor[i][j];
					}
					//cout<<endl;
				}
				break;
			}
			file.close();
			//      cout<<"ini done"<<endl;
		};

		HepVector GetCorrection(int n, const HepSymMatrix& V){
			//      cout<<"n= "<<n<<endl;
			//cout<<"*************************************"<<endl;
			HepVector gauss_tem(5,0);
			for(int i=0;i<5;i++){
				double tem=gRandom->Gaus(0,1);
				gauss_tem[i]=tem*Sigma_cor[n][i]*sqrt(V[i][i])+Mean_cor[n][i]*sqrt(V[i][i]);
				//cout<<" mean"<<n<<i<<"="<<Mean_cor[n][i]<<" sigma "<<"="<<Sigma_cor[n][i]<<endl;
				//cout<<" i= "<<i<<" V("<<i<<i<<")="<<V[i][i]<<" gaus "<<tem<<" correction = "<<gauss_tem[i]<<endl;
			}
			return gauss_tem;
		};
	private:
		// (0.*),k+, (1,*)k-, (2,*)pi+, (3,*)pi-, (4,*)e+. (5,*)e-, (6,*)mu+, (7,*)mu-
		HepMatrix Mean_cor;// mean value for the smeared gauss,
		HepMatrix Sigma_cor;// sigma for the smeared gauss;
};
/*
   class PullCorrection{
   public:
   PullCorrection(HepMatrix  , HepMatrix  ){};
   PullCorrection(){};
   HepVector GetCorrection(int , const HepSymMatrix & ){};
   private:
// (0.*),k+, (1,*)k-, (2,*)pi+, (3,*)pi-, (4,*)e+. (5,*)e-, (6,*)mu+, (7,*)mu-
HepMatrix Mean_cor;// mean value for the smeared gauss,
HepMatrix Sigma_cor;// sigma for the smeared gauss;

};
 */

#endif
