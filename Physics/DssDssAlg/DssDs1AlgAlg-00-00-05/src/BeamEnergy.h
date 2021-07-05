// read beam energy
// from BAM-165
#include "DssDs1Alg/RscanDQ.h"

double BeamEnergy(int runNo){
	double ecms;

	if( fabs(runNo)>=23463 && fabs(runNo)<=24141 ){ //4009
		ecms = 4.0043;
	}
	if(runNo>=34011 && runNo<=35116)
	{
		RscanDQ scan(runNo);
		ecms=2*scan.getEbeam();
	}
	else if( fabs(runNo)>=29677 && fabs(runNo)<=30367 ){ //4260-I
		ecms = 4.2580;
	}
	else if( fabs(runNo)>=30372 && fabs(runNo)<=30437 ){ //4190
		ecms = 4.1886;
	}
	else if( fabs(runNo)>=30438 && fabs(runNo)<=30491 ){ //4230-I
		ecms = 4.2273;
	}
	else if( fabs(runNo)>=30492 && fabs(runNo)<=30557 ){ //4310
		ecms = 4.3079;
	}
	else if( fabs(runNo)>=30616 && fabs(runNo)<=31279 ){ //4360
		ecms = 4.3582;
	}
	else if( fabs(runNo)>=31281 && fabs(runNo)<=31325 ){ //4390
		ecms = 4.3874;
	}
	else if( fabs(runNo)>=31327 && fabs(runNo)<=31390 ){ //4420-I
		ecms = 4.4169;
	}
	else if( fabs(runNo)>=31561 && fabs(runNo)<=31981 ){ //4260-II
		ecms = 4.2574;
	}
	else if( fabs(runNo)>=31983 && fabs(runNo)<=32045 ){ //4210
		ecms = 4.2077;
	}
	else if( fabs(runNo)>=32046 && fabs(runNo)<=32140 ){ //4220
		ecms = 4.2171;
	}
	else if( fabs(runNo)>=32141 && fabs(runNo)<=32226 ){ //4245
		ecms = 4.2416;
	}
	else if( fabs(runNo)>=32239 && fabs(runNo)<=33484 ){ //4230-II
		ecms = 4.2260;
	}
	else if( fabs(runNo)>=33490 && fabs(runNo)<=33556 ){ //3810
		ecms = 3.8077;
	}
	else if( fabs(runNo)>=33571 && fabs(runNo)<=33657 ){ //3900
		ecms = 3.8963;
	}
	else if( fabs(runNo)>=33659 && fabs(runNo)<=33719 ){ //4090
		ecms = 4.0855;
	}
	else if( fabs(runNo)>=35227 && fabs(runNo)<=36244 ){ //4600
		ecms = 4.5995;
	}
	else if( fabs(runNo)>=36245 && fabs(runNo)<=36393 ){ //4470
		ecms = 4.4670;
	}
	else if( fabs(runNo)>=36398 && fabs(runNo)<=36588 ){ //4530
		ecms = 4.5271;
	}
	else if( fabs(runNo)>=36603 && fabs(runNo)<=36699 ){ //4575
		ecms = 4.5744;
	}
	else if( fabs(runNo)>=36773 && fabs(runNo)<=37855 ){ //4420-II
		ecms = 4.4158;
	}
	else if( fabs(runNo)>=37856 && fabs(runNo)<=38140 ){ //4420-III
		ecms = 4.4140;
	}

	return ecms;
}
