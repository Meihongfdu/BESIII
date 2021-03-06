#include "Ecmset/Ecmset.h"

Ecmset* Ecmset::m_pointer = 0;

Ecmset* Ecmset::instance() {
  if(!m_pointer) m_pointer = new Ecmset();
  return m_pointer;
}

void Ecmset::EcmSet(int run) {
//-----------------------------------------------------------------------------------
//Input Run number to set the center-of-mass energy
//                                              2012-04-23 Sunday Afternoon.
//-----------------------------------------------------------------------------------

  Ecm = 0.;

  if(run>=8093&&run<=9025)   Ecm = 3.686;
  if(run>=9613&&run<=9779)   Ecm = 3.650;
  if(run>=9485&&run<=9489)   Ecm = 3.767;
  if(run>=9496&&run<=9501)   Ecm = 3.780;
  if(run>=9815&&run<20000)   Ecm = 3.096916;
  if(run>=11414)             Ecm = 3.773;
//mahl 2016-9-6
  if(run>=43716&&run<=47066) Ecm = 4.18;

  if(run==13994)             Ecm = 1.83392*2;
  if(run==13995)             Ecm = 1.83394*2;
  if(run==13996)             Ecm = 1.83535*2;
  if(run==13997)             Ecm = 1.83682*2;
  if(run==13998)             Ecm = 1.84061*2;
  if(run==13999)             Ecm = 1.84119*2;
  if(run==14000)             Ecm = 1.84177*2;
  if(run==14001)             Ecm = 1.84236*2;
  if(run==14002)             Ecm = 1.84296*2;
  if(run==14003)             Ecm = 1.84378*2;
  if(run==14004)             Ecm = 1.84419*2;
  if(run==14005)             Ecm = 1.84496*2;

  if(run>=14006&&run<=14006) Ecm = 3.6450;
  if(run>=14007&&run<=14007) Ecm = 3.6580;
  if(run>=14008&&run<=14008) Ecm = 3.6656;
  if(run>=14009&&run<=14009) Ecm = 3.6707;
  if(run>=14010&&run<=14010) Ecm = 3.6737;
  if(run>=14011&&run<=14011) Ecm = 3.6770;
  if(run>=14012&&run<=14012) Ecm = 3.6790;
  if(run>=14013&&run<=14013) Ecm = 3.6798;
  if(run>=14014&&run<=14014) Ecm = 3.6810;
  if(run>=14015&&run<=14015) Ecm = 3.6818;
  if(run>=14016&&run<=14016) Ecm = 3.6821;
  if(run>=14017&&run<=14017) Ecm = 3.6826;
  if(run>=14018&&run<=14018) Ecm = 3.6834;
  if(run>=14019&&run<=14019) Ecm = 3.6840;
  if(run>=14020&&run<=14020) Ecm = 3.6847;
  if(run>=14027&&run<=14027) Ecm = 3.6849;
  if(run>=14028&&run<=14028) Ecm = 3.6853;
  if(run>=14029&&run<=14029) Ecm = 3.6860;
  if(run>=14030&&run<=14030) Ecm = 3.6866;
  if(run>=14031&&run<=14031) Ecm = 3.6873;
  if(run>=14032&&run<=14032) Ecm = 3.6875;
  if(run>=14033&&run<=14033) Ecm = 3.6891;
  if(run>=14034&&run<=14034) Ecm = 3.6921;
  if(run>=14035&&run<=14035) Ecm = 3.6964;
  if(run>=14036&&run<=14036) Ecm = 3.6995;
  if(run>=14037&&run<=14037) Ecm = 3.7059;
  if(run>=14038&&run<=14038) Ecm = 3.7139;
  if(run>=14039&&run<=14039) Ecm = 3.7219;
  if(run>=14354&&run<=14355) Ecm = 3.7279;
  if(run>=14040&&run<=14040) Ecm = 3.7299;
  if(run>=14041&&run<=14046) Ecm = 3.7366;
  if(run>=14047&&run<=14048) Ecm = 3.7446;
  if(run>=14049&&run<=14053) Ecm = 3.7466;
  if(run>=14057&&run<=14067) Ecm = 3.7486;
  if(run>=14068&&run<=14077) Ecm = 3.7506;
  if(run>=14078&&run<=14086) Ecm = 3.7526;
  if(run>=14087&&run<=14101) Ecm = 3.7541;
  if(run>=14103&&run<=14109) Ecm = 3.7556;
  if(run>=14110&&run<=14123) Ecm = 3.7586;
  if(run>=14129&&run<=14144) Ecm = 3.7606;
  if(run>=14145&&run<=14154) Ecm = 3.7646;
  if(run>=14155&&run<=14160) Ecm = 3.7676;
  if(run>=14161&&run<=14164) Ecm = 3.7706;
  if(run>=14165&&run<=14168) Ecm = 3.7736;
  if(run>=14169&&run<=14174) Ecm = 3.7766;
  if(run>=14175&&run<=14175) Ecm = 3.6481;
  if(run>=14177&&run<=14177) Ecm = 3.6604;
  if(run>=14178&&run<=14178) Ecm = 3.6674;
  if(run>=14179&&run<=14179) Ecm = 3.6700;
  if(run>=14180&&run<=14180) Ecm = 3.6724;
  if(run>=14181&&run<=14181) Ecm = 3.6762;
  if(run>=14182&&run<=14182) Ecm = 3.6778;
  if(run>=14183&&run<=14183) Ecm = 3.6784;
  if(run>=14184&&run<=14184) Ecm = 3.6802;
  if(run>=14185&&run<=14185) Ecm = 3.6810;
  if(run>=14186&&run<=14186) Ecm = 3.6812;
  if(run>=14187&&run<=14187) Ecm = 3.6816;
  if(run>=14188&&run<=14188) Ecm = 3.6825;
  if(run>=14189&&run<=14189) Ecm = 3.6831;
  if(run>=14190&&run<=14190) Ecm = 3.6835;
  if(run>=14191&&run<=14191) Ecm = 3.6842;
  if(run>=14192&&run<=14192) Ecm = 3.6850;
  if(run>=14193&&run<=14193) Ecm = 3.6853;
  if(run>=14194&&run<=14194) Ecm = 3.6861;
  if(run>=14195&&run<=14195) Ecm = 3.6865;
  if(run>=14196&&run<=14196) Ecm = 3.6872;
  if(run>=14197&&run<=14197) Ecm = 3.6888;
  if(run>=14198&&run<=14198) Ecm = 3.6914;
  if(run>=14199&&run<=14199) Ecm = 3.6956;
  if(run>=14200&&run<=14203) Ecm = 3.7796;
  if(run>=14204&&run<=14217) Ecm = 3.7826;
  if(run>=14221&&run<=14226) Ecm = 3.7856;
  if(run>=14230&&run<=14238) Ecm = 3.7886;
  if(run>=14239&&run<=14246) Ecm = 3.7926;
  if(run>=14247&&run<=14259) Ecm = 3.7966;
  if(run>=14260&&run<=14270) Ecm = 3.8006;
  if(run>=14271&&run<=14274) Ecm = 3.8036;
  if(run>=14275&&run<=14279) Ecm = 3.8066;
  if(run>=14280&&run<=14290) Ecm = 3.8096;
  if(run>=14291&&run<=14292) Ecm = 3.8126;
  if(run>=14293&&run<=14294) Ecm = 3.8156;
  if(run>=14295&&run<=14296) Ecm = 3.8236;
  if(run>=14297&&run<=14297) Ecm = 3.8316;
  if(run>=14298&&run<=14298) Ecm = 3.8396;
  if(run>=14299&&run<=14299) Ecm = 3.8476;
  if(run>=14300&&run<=14301) Ecm = 3.8556;
  if(run>=14302&&run<=14303) Ecm = 3.8636;
  if(run>=14304&&run<=14305) Ecm = 3.8716;
  if(run>=14306&&run<=14307) Ecm = 3.8806;
  if(run>=14308&&run<=14308) Ecm = 3.8906;
  if(run>=14313&&run<=14313) Ecm = 3.6439;
  if(run>=14314&&run<=14314) Ecm = 3.6567;
  if(run>=14315&&run<=14315) Ecm = 3.6647;
  if(run>=14316&&run<=14316) Ecm = 3.6701;
  if(run>=14317&&run<=14317) Ecm = 3.6727;
  if(run>=14318&&run<=14318) Ecm = 3.6761;
  if(run>=14319&&run<=14319) Ecm = 3.6779;
  if(run>=14320&&run<=14320) Ecm = 3.6787;
  if(run>=14321&&run<=14321) Ecm = 3.6797;
  if(run>=14322&&run<=14322) Ecm = 3.6807;
  if(run>=14323&&run<=14323) Ecm = 3.6811;
  if(run>=14324&&run<=14324) Ecm = 3.6817;
  if(run>=14325&&run<=14325) Ecm = 3.6823;
  if(run>=14326&&run<=14326) Ecm = 3.6827;
  if(run>=14327&&run<=14327) Ecm = 3.6833;
  if(run>=14328&&run<=14328) Ecm = 3.6839;
  if(run>=14329&&run<=14329) Ecm = 3.6848;
  if(run>=14330&&run<=14330) Ecm = 3.6853;
  if(run>=14331&&run<=14331) Ecm = 3.6859;
  if(run>=14332&&run<=14332) Ecm = 3.6865;
  if(run>=14333&&run<=14333) Ecm = 3.6871;
  if(run>=14334&&run<=14334) Ecm = 3.6879;
  if(run>=14335&&run<=14335) Ecm = 3.6887;
  if(run>=14336&&run<=14336) Ecm = 3.6901;
  if(run>=14337&&run<=14337) Ecm = 3.6913;
  if(run>=14338&&run<=14338) Ecm = 3.6935;
  if(run>=14339&&run<=14339) Ecm = 3.6957;
  if(run>=14340&&run<=14348) Ecm = 3.6473;
  if(run>=14349&&run<=14353) Ecm = 3.6533;
  if(run>=14359&&run<=14359) Ecm = 3.7356;
  if(run>=14360&&run<=14360) Ecm = 3.7376;

  if(run>=11414&&run<=11486) Ecm = 2*1.88635; //1886.35 0.02
  if(run>=11487&&run<=11505) Ecm = 2*1.8876 ; //1887.6  0.02
  if(run>=11506&&run<=11508) Ecm = 2*1.88577; //1885.77 0.04
  if(run>=11509&&run<=11572) Ecm = 2*1.88665; //1886.65 0.02
  if(run>=11573&&run<=11593) Ecm = 2*1.88661; //1886.61 0.02
  if(run>=11595&&run<=11612) Ecm = 2*1.88663; //1886.63 0.02
  if(run>=11613&&run<=11627) Ecm = 2*1.88659; //1886.59 0.02
  if(run>=11628&&run<=11650) Ecm = 2*1.88661; //1886.61 0.02
  if(run>=11651&&run<=11681) Ecm = 2*1.88658; //1886.58 0.02
  if(run>=11682&&run<=11712) Ecm = 2*1.88654; //1886.54 0.02
  if(run>=11714&&run<=11728) Ecm = 2*1.88637; //1886.37 0.02
  if(run>=11729&&run<=11759) Ecm = 2*1.88642; //1886.42 0.02
  if(run>=11760&&run<=11797) Ecm = 2*1.88637; //1886.37 0.03
  if(run>=11798&&run<=11817) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=11818&&run<=11832) Ecm = 2*1.88648; //1886.48 0.02
  if(run>=11833&&run<=11851) Ecm = 2*1.88648; //1886.48 0.03
  if(run>=11854&&run<=11868) Ecm = 2*1.88653; //1886.53 0.03
  if(run>=11869&&run<=11889) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=11891&&run<=11917) Ecm = 2*1.88642; //1886.42 0.02
  if(run>=11918&&run<=11935) Ecm = 2*1.88646; //1886.46 0.02
  if(run>=11936&&run<=11952) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=11953&&run<=11970) Ecm = 2*1.88647; //1886.47 0.02
  if(run>=11971&&run<=11985) Ecm = 2*1.88642; //1886.42 0.02
  if(run>=11986&&run<=12002) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=12012&&run<=12040) Ecm = 2*1.88637; //1886.37 0.02
  if(run>=12050&&run<=12066) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=12067&&run<=12070) Ecm = 2*1.88839; //1888.39 0.05
  if(run>=12092&&run<=12114) Ecm = 2*1.88644; //1886.44 0.02
  if(run>=12116&&run<=12134) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=12135&&run<=12163) Ecm = 2*1.88648; //1886.48 0.03
  if(run>=12223&&run<=12238) Ecm = 2*1.8865 ; //1886.5  0.03
  if(run>=12240&&run<=12264) Ecm = 2*1.88648; //1886.48 0.02
  if(run>=12265&&run<=12279) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=12326&&run<=12352) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=12394&&run<=12408) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=12409&&run<=12423) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=12424&&run<=12435) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=12436&&run<=12447) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=12448&&run<=12460) Ecm = 2*1.88657; //1886.57 0.02
  if(run>=12461&&run<=12505) Ecm = 2*1.88663; //1886.63 0.03
  if(run>=12506&&run<=12519) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=12520&&run<=12550) Ecm = 2*1.88647; //1886.47 0.02
  if(run>=12555&&run<=12563) Ecm = 2*1.88642; //1886.42 0.03
  if(run>=12572&&run<=12595) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=12596&&run<=12628) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=12631&&run<=12663) Ecm = 2*1.88644; //1886.44 0.02
  if(run>=12664&&run<=12673) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=12674&&run<=12692) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=12693&&run<=12706) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=12707&&run<=12725) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=12726&&run<=12744) Ecm = 2*1.88631; //1886.31 0.02
  if(run>=12745&&run<=12776) Ecm = 2*1.88666; //1886.66 0.02
  if(run>=12779&&run<=12793) Ecm = 2*1.88668; //1886.68 0.02
  if(run>=12794&&run<=12812) Ecm = 2*1.88668; //1886.68 0.02
  if(run>=12813&&run<=12844) Ecm = 2*1.88666; //1886.66 0.02
  if(run>=12845&&run<=12868) Ecm = 2*1.88661; //1886.61 0.02
  if(run>=12967&&run<=12990) Ecm = 2*1.88674; //1886.74 0.02
  if(run>=12991&&run<=13013) Ecm = 2*1.8867 ; //1886.7  0.06
  if(run>=13015&&run<=13027) Ecm = 2*1.88675; //1886.75 0.02
  if(run>=13028&&run<=13041) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=13042&&run<=13056) Ecm = 2*1.88676; //1886.76 0.02
  if(run>=13057&&run<=13066) Ecm = 2*1.88667; //1886.67 0.02
  if(run>=13067&&run<=13081) Ecm = 2*1.8866 ; //1886.6  0.02
  if(run>=13082&&run<=13092) Ecm = 2*1.8866 ; //1886.6  0.04
  if(run>=13093&&run<=13105) Ecm = 2*1.8866 ; //1886.6  0.03
  if(run>=13106&&run<=13122) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=13123&&run<=13137) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=13150&&run<=13166) Ecm = 2*1.88659; //1886.59 0.02
  if(run>=13167&&run<=13180) Ecm = 2*1.88662; //1886.62 0.02
  if(run>=13181&&run<=13194) Ecm = 2*1.88656; //1886.56 0.03
  if(run>=13195&&run<=13219) Ecm = 2*1.88655; //1886.55 0.02
  if(run>=13222&&run<=13242) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=13253&&run<=13265) Ecm = 2*1.88661; //1886.61 0.02
  if(run>=13284&&run<=13291) Ecm = 2*1.88651; //1886.51 0.03
  if(run>=13298&&run<=13319) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=13320&&run<=13330) Ecm = 2*1.88631; //1886.31 0.02
  if(run>=13331&&run<=13343) Ecm = 2*1.88629; //1886.29 0.02
  if(run>=13344&&run<=13370) Ecm = 2*1.88626; //1886.26 0.02
  if(run>=13371&&run<=13387) Ecm = 2*1.88625; //1886.25 0.02
  if(run>=13388&&run<=13402) Ecm = 2*1.88622; //1886.22 0.02
  if(run>=13403&&run<=13415) Ecm = 2*1.8861 ; //1886.1  0.02
  if(run>=13443&&run<=13468) Ecm = 2*1.88634; //1886.34 0.03
  if(run>=13469&&run<=13479) Ecm = 2*1.88623; //1886.23 0.02
  if(run>=13480&&run<=13494) Ecm = 2*1.8862 ; //1886.2  0.02
  if(run>=13495&&run<=13507) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=13508&&run<=13529) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=13556&&run<=13622) Ecm = 2*1.88626; //1886.26 0.02
  if(run>=13624&&run<=13637) Ecm = 2*1.88621; //1886.21 0.02
  if(run>=13638&&run<=13652) Ecm = 2*1.8862 ; //1886.2  0.02
  if(run>=13653&&run<=13669) Ecm = 2*1.88618; //1886.18 0.02
  if(run>=13678&&run<=13689) Ecm = 2*1.88576; //1885.76 0.02
  if(run>=13694&&run<=13706) Ecm = 2*1.88569; //1885.69 0.02
  if(run>=13710&&run<=13720) Ecm = 2*1.88569; //1885.69 0.03
  if(run>=13721&&run<=13737) Ecm = 2*1.88546; //1885.46 0.02
  if(run>=13738&&run<=13749) Ecm = 2*1.88546; //1885.46 0.02
  if(run>=13756&&run<=13760) Ecm = 2*1.88585; //1885.85 0.03
  if(run>=13772&&run<=13780) Ecm = 2*1.88592; //1885.92 0.02
  if(run>=13784&&run<=13796) Ecm = 2*1.88587; //1885.87 0.03
  if(run>=13797&&run<=13811) Ecm = 2*1.88579; //1885.79 0.03
  if(run>=13812&&run<=13828) Ecm = 2*1.88569; //1885.69 0.03
  if(run>=13829&&run<=13845) Ecm = 2*1.88575; //1885.75 0.02
  if(run>=13846&&run<=13859) Ecm = 2*1.88574; //1885.74 0.01
  if(run>=13865&&run<=13878) Ecm = 2*1.88646; //1886.46 0.02
  if(run>=13879&&run<=13891) Ecm = 2*1.88634; //1886.34 0.02
  if(run>=13892&&run<=13893) Ecm = 2*1.88643; //1886.43 0.04
  if(run>=13898&&run<=13932) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=13933&&run<=13944) Ecm = 2*1.88635; //1886.35 0.02
  if(run>=13945&&run<=13958) Ecm = 2*1.88637; //1886.37 0.02
  if(run>=13959&&run<=13974) Ecm = 2*1.8864 ; //1886.4  0.02
  if(run>=13975&&run<=13988) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=14395&&run<=14427) Ecm = 2*1.88579; //1885.79 0.02
  if(run>=14428&&run<=14444) Ecm = 2*1.88568; //1885.68 0.02
  if(run>=14447&&run<=14461) Ecm = 2*1.88572; //1885.72 0.02
  if(run>=14462&&run<=14473) Ecm = 2*1.88556; //1885.56 0.03
  if(run>=14474&&run<=14489) Ecm = 2*1.88564; //1885.64 0.04
  if(run>=14490&&run<=14502) Ecm = 2*1.88642; //1886.42 0.03
  if(run>=14536&&run<=14564) Ecm = 2*1.88653; //1886.53 0.03
  if(run>=14568&&run<=14577) Ecm = 2*1.88655; //1886.55 0.03
  if(run>=14578&&run<=14604) Ecm = 2*1.88654; //1886.54 0.02
  if(run>=20448&&run<=20477) Ecm = 2*1.88631; //1886.31 0.01
  if(run>=20513&&run<=20533) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=20550&&run<=20564) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=20567&&run<=20580) Ecm = 2*1.88634; //1886.34 0.02
  if(run>=20582&&run<=20597) Ecm = 2*1.88629; //1886.29 0.02
  if(run>=20601&&run<=20610) Ecm = 2*1.88627; //1886.27 0.02
  if(run>=20613&&run<=20623) Ecm = 2*1.88631; //1886.31 0.02
  if(run>=20629&&run<=20637) Ecm = 2*1.88621; //1886.21 0.02
  if(run>=20638&&run<=20646) Ecm = 2*1.8863 ; //1886.3  0.02
  if(run>=20651&&run<=20667) Ecm = 2*1.8862 ; //1886.2  0.02
  if(run>=20668&&run<=20681) Ecm = 2*1.8862 ; //1886.2  0.02
  if(run>=20682&&run<=20692) Ecm = 2*1.88614; //1886.14 0.02
  if(run>=20701&&run<=20707) Ecm = 2*1.88631; //1886.31 0.02
  if(run>=20711&&run<=20719) Ecm = 2*1.8863 ; //1886.3  0.03
  if(run>=20720&&run<=20729) Ecm = 2*1.88633; //1886.33 0.03
  if(run>=20730&&run<=20739) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=20740&&run<=20749) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=20750&&run<=20757) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=20758&&run<=20763) Ecm = 2*1.88634; //1886.34 0.02
  if(run>=20782&&run<=20789) Ecm = 2*1.8864 ; //1886.4  0.02
  if(run>=20790&&run<=20801) Ecm = 2*1.88644; //1886.44 0.02
  if(run>=20802&&run<=20808) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=20811&&run<=20819) Ecm = 2*1.88641; //1886.41 0.02
  if(run>=20846&&run<=20856) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=20857&&run<=20862) Ecm = 2*1.8864 ; //1886.4  0.03
  if(run>=20875&&run<=20890) Ecm = 2*1.8866 ; //1886.6  0.02
  if(run>=20891&&run<=20895) Ecm = 2*1.88658; //1886.58 0.02
  if(run>=20900&&run<=20909) Ecm = 2*1.88658; //1886.58 0.02
  if(run>=20910&&run<=20919) Ecm = 2*1.88654; //1886.54 0.02
  if(run>=20933&&run<=20940) Ecm = 2*1.88659; //1886.59 0.04
  if(run>=20941&&run<=20957) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=20958&&run<=20968) Ecm = 2*1.88651; //1886.51 0.02
  if(run>=20969&&run<=20979) Ecm = 2*1.88647; //1886.47 0.03
  if(run>=20980&&run<=20989) Ecm = 2*1.88648; //1886.48 0.02
  if(run>=20990&&run<=20999) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=21001&&run<=21008) Ecm = 2*1.88647; //1886.47 0.04
  if(run>=21009&&run<=21014) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=21059&&run<=21069) Ecm = 2*1.88659; //1886.59 0.02
  if(run>=21070&&run<=21079) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=21080&&run<=21089) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=21090&&run<=21099) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=21100&&run<=21109) Ecm = 2*1.88654; //1886.54 0.02
  if(run>=21110&&run<=21120) Ecm = 2*1.88646; //1886.46 0.02
  if(run>=21134&&run<=21149) Ecm = 2*1.88654; //1886.54 0.02
  if(run>=21150&&run<=21170) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=21171&&run<=21179) Ecm = 2*1.88659; //1886.59 0.02
  if(run>=21180&&run<=21189) Ecm = 2*1.88656; //1886.56 0.02
  if(run>=21190&&run<=21199) Ecm = 2*1.88654; //1886.54 0.02
  if(run>=21200&&run<=21207) Ecm = 2*1.88656; //1886.56 0.02
  if(run>=21208&&run<=21220) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=21221&&run<=21232) Ecm = 2*1.88653; //1886.53 0.02
  if(run>=21244&&run<=21267) Ecm = 2*1.88664; //1886.64 0.02
  if(run>=21271&&run<=21284) Ecm = 2*1.88661; //1886.61 0.02
  if(run>=21285&&run<=21304) Ecm = 2*1.88662; //1886.62 0.02
  if(run>=21357&&run<=21382) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21383&&run<=21400) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21401&&run<=21419) Ecm = 2*1.88672; //1886.72 0.02
  if(run>=21434&&run<=21449) Ecm = 2*1.88674; //1886.74 0.02
  if(run>=21450&&run<=21472) Ecm = 2*1.88678; //1886.78 0.04
  if(run>=21473&&run<=21488) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=21491&&run<=21509) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=21510&&run<=21521) Ecm = 2*1.88664; //1886.64 0.02
  if(run>=21523&&run<=21548) Ecm = 2*1.88666; //1886.66 0.02
  if(run>=21561&&run<=21574) Ecm = 2*1.88672; //1886.72 0.03
  if(run>=21578&&run<=21592) Ecm = 2*1.88668; //1886.68 0.02
  if(run>=21595&&run<=21612) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=21629&&run<=21654) Ecm = 2*1.88672; //1886.72 0.02
  if(run>=21684&&run<=21699) Ecm = 2*1.88676; //1886.76 0.02
  if(run>=21702&&run<=21709) Ecm = 2*1.88679; //1886.79 0.02
  if(run>=21714&&run<=21729) Ecm = 2*1.88675; //1886.75 0.03
  if(run>=21733&&run<=21749) Ecm = 2*1.88674; //1886.74 0.02
  if(run>=21754&&run<=21765) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21766&&run<=21777) Ecm = 2*1.88676; //1886.76 0.02
  if(run>=21778&&run<=21786) Ecm = 2*1.88675; //1886.75 0.02
  if(run>=21787&&run<=21797) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=21798&&run<=21806) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21807&&run<=21813) Ecm = 2*1.88665; //1886.65 0.02
  if(run>=21820&&run<=21832) Ecm = 2*1.88681; //1886.81 0.01
  if(run>=21833&&run<=21843) Ecm = 2*1.88681; //1886.81 0.01
  if(run>=21844&&run<=21850) Ecm = 2*1.88678; //1886.78 0.02
  if(run>=21856&&run<=21865) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21866&&run<=21873) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21874&&run<=21881) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21882&&run<=21890) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=21891&&run<=21901) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=21902&&run<=21912) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=21913&&run<=21933) Ecm = 2*1.88674; //1886.74 0.02
  if(run>=21934&&run<=21944) Ecm = 2*1.88673; //1886.73 0.01
  if(run>=21945&&run<=21954) Ecm = 2*1.88667; //1886.67 0.01
  if(run>=21955&&run<=21962) Ecm = 2*1.88666; //1886.66 0.02
  if(run>=21963&&run<=21970) Ecm = 2*1.88664; //1886.64 0.02
  if(run>=21971&&run<=21979) Ecm = 2*1.88668; //1886.68 0.02
  if(run>=21980&&run<=21989) Ecm = 2*1.88667; //1886.67 0.02
  if(run>=21990&&run<=21999) Ecm = 2*1.88664; //1886.64 0.01
  if(run>=22000&&run<=22008) Ecm = 2*1.88666; //1886.66 0.02
  if(run>=22009&&run<=22018) Ecm = 2*1.88672; //1886.72 0.02
  if(run>=22019&&run<=22030) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=22032&&run<=22040) Ecm = 2*1.8867 ; //1886.7  0.02
  if(run>=22041&&run<=22049) Ecm = 2*1.88676; //1886.76 0.05
  if(run>=22050&&run<=22060) Ecm = 2*1.88672; //1886.72 0.02
  if(run>=22062&&run<=22071) Ecm = 2*1.8867 ; //1886.7  0.03
  if(run>=22072&&run<=22080) Ecm = 2*1.88677; //1886.77 0.02
  if(run>=22082&&run<=22091) Ecm = 2*1.88674; //1886.74 0.02
  if(run>=22092&&run<=22102) Ecm = 2*1.88674; //1886.74 0.01
  if(run>=22103&&run<=22113) Ecm = 2*1.88673; //1886.73 0.02
  if(run>=22121&&run<=22130) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=22131&&run<=22141) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=22142&&run<=22149) Ecm = 2*1.88634; //1886.34 0.02
  if(run>=22150&&run<=22162) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=22163&&run<=22172) Ecm = 2*1.88634; //1886.34 0.02
  if(run>=22173&&run<=22180) Ecm = 2*1.88625; //1886.25 0.02
  if(run>=22181&&run<=22194) Ecm = 2*1.88628; //1886.28 0.02
  if(run>=22195&&run<=22206) Ecm = 2*1.88628; //1886.28 0.02
  if(run>=22207&&run<=22222) Ecm = 2*1.88628; //1886.28 0.02
  if(run>=22223&&run<=22230) Ecm = 2*1.88629; //1886.29 0.04
  if(run>=22241&&run<=22254) Ecm = 2*1.8867 ; //1886.7  0.03
  if(run>=22262&&run<=22269) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=22270&&run<=22278) Ecm = 2*1.8867 ; //1886.7  0.02
  if(run>=22279&&run<=22287) Ecm = 2*1.8867 ; //1886.7  0.02
  if(run>=22288&&run<=22300) Ecm = 2*1.88664; //1886.64 0.02
  if(run>=22301&&run<=22312) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=22314&&run<=22327) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=22328&&run<=22335) Ecm = 2*1.88664; //1886.64 0.02
  if(run>=22336&&run<=22344) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=22348&&run<=22357) Ecm = 2*1.88664; //1886.64 0.02
  if(run>=22358&&run<=22367) Ecm = 2*1.88667; //1886.67 0.02
  if(run>=22368&&run<=22380) Ecm = 2*1.88671; //1886.71 0.02
  if(run>=22383&&run<=22392) Ecm = 2*1.88676; //1886.76 0.02
  if(run>=22393&&run<=22402) Ecm = 2*1.88669; //1886.69 0.03
  if(run>=22403&&run<=22410) Ecm = 2*1.88669; //1886.69 0.02
  if(run>=22435&&run<=22467) Ecm = 2*1.8865 ; //1886.5  0.03
  if(run>=22468&&run<=22505) Ecm = 2*1.88644; //1886.44 0.02
  if(run>=22516&&run<=22525) Ecm = 2*1.88639; //1886.39 0.03
  if(run>=22532&&run<=22546) Ecm = 2*1.88643; //1886.43 0.02
  if(run>=22558&&run<=22568) Ecm = 2*1.88624; //1886.24 0.03
  if(run>=22569&&run<=22576) Ecm = 2*1.88604; //1886.04 0.02
  if(run>=22577&&run<=22586) Ecm = 2*1.88611; //1886.11 0.02
  if(run>=22587&&run<=22597) Ecm = 2*1.88616; //1886.16 0.02
  if(run>=22612&&run<=22620) Ecm = 2*1.88643; //1886.43 0.03
  if(run>=22621&&run<=22631) Ecm = 2*1.88653; //1886.53 0.03
  if(run>=22652&&run<=22674) Ecm = 2*1.88657; //1886.57 0.02
  if(run>=22676&&run<=22684) Ecm = 2*1.88655; //1886.55 0.02
  if(run>=22685&&run<=22693) Ecm = 2*1.8865 ; //1886.5  0.02
  if(run>=22694&&run<=22705) Ecm = 2*1.88647; //1886.47 0.03
  if(run>=22706&&run<=22723) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=22724&&run<=22732) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=22733&&run<=22748) Ecm = 2*1.88652; //1886.52 0.02
  if(run>=22749&&run<=22757) Ecm = 2*1.88656; //1886.56 0.02
  if(run>=22758&&run<=22771) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=22772&&run<=22779) Ecm = 2*1.8865 ; //1886.5  0.05
  if(run>=22780&&run<=22787) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=22788&&run<=22796) Ecm = 2*1.88651; //1886.51 0.02
  if(run>=22797&&run<=22808) Ecm = 2*1.88647; //1886.47 0.02
  if(run>=22809&&run<=22817) Ecm = 2*1.88647; //1886.47 0.02
  if(run>=22818&&run<=22830) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=22831&&run<=22838) Ecm = 2*1.88649; //1886.49 0.02
  if(run>=22839&&run<=22851) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=22852&&run<=22861) Ecm = 2*1.88647; //1886.47 0.02
  if(run>=22866&&run<=22875) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=22892&&run<=22906) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=22914&&run<=22923) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=22924&&run<=22931) Ecm = 2*1.88646; //1886.46 0.02
  if(run>=22932&&run<=22940) Ecm = 2*1.88648; //1886.48 0.02
  if(run>=22941&&run<=22949) Ecm = 2*1.88645; //1886.45 0.02
  if(run>=22953&&run<=22961) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=22962&&run<=22969) Ecm = 2*1.88639; //1886.39 0.01
  if(run>=22970&&run<=22982) Ecm = 2*1.88638; //1886.38 0.02
  if(run>=22983&&run<=22991) Ecm = 2*1.88641; //1886.41 0.02
  if(run>=22995&&run<=23002) Ecm = 2*1.88639; //1886.39 0.02
  if(run>=23003&&run<=23009) Ecm = 2*1.88635; //1886.35 0.02
  if(run>=23012&&run<=23021) Ecm = 2*1.88635; //1886.35 0.02
  if(run>=23036&&run<=23044) Ecm = 2*1.88631; //1886.31 0.02
  if(run>=23045&&run<=23062) Ecm = 2*1.88633; //1886.33 0.02
  if(run>=23063&&run<=23070) Ecm = 2*1.8863 ; //1886.3  0.02
  if(run>=23071&&run<=23084) Ecm = 2*1.88637; //1886.37 0.02
  if(run>=23085&&run<=23092) Ecm = 2*1.8863 ; //1886.3  0.02
  if(run>=23093&&run<=23107) Ecm = 2*1.88625; //1886.25 0.02
  if(run>=23108&&run<=23121) Ecm = 2*1.88629; //1886.29 0.02
  if(run>=23123&&run<=23130) Ecm = 2*1.88631; //1886.31 0.02
  if(run>=23131&&run<=23140) Ecm = 2*1.88636; //1886.36 0.02
  if(run>=23141&&run<=23149) Ecm = 2*1.88629; //1886.29 0.02
  if(run>=23150&&run<=23159) Ecm = 2*1.88624; //1886.24 0.02
  if(run>=23173&&run<=23181) Ecm = 2*1.88623; //1886.23 0.02
  if(run>=23182&&run<=23190) Ecm = 2*1.88622; //1886.22 0.02
  if(run>=23191&&run<=23199) Ecm = 2*1.88619; //1886.19 0.02
  if(run>=23200&&run<=23213) Ecm = 2*1.88623; //1886.23 0.02
  if(run>=23214&&run<=23226) Ecm = 2*1.88619; //1886.19 0.02
  if(run>=23241&&run<=23254) Ecm = 2*1.88627; //1886.27 0.02
  if(run>=23255&&run<=23262) Ecm = 2*1.88622; //1886.22 0.02
  if(run>=23263&&run<=23275) Ecm = 2*1.88629; //1886.29 0.02
  if(run>=23277&&run<=23293) Ecm = 2*1.8862 ; //1886.2  0.02
  if(run>=23311&&run<=23322) Ecm = 2*1.88595; //1885.95 0.03
  if(run>=23323&&run<=23332) Ecm = 2*1.88594; //1885.94 0.03
  if(run>=23333&&run<=23346) Ecm = 2*1.88591; //1885.91 0.02
  if(run>=23347&&run<=23361) Ecm = 2*1.88585; //1885.85 0.02
  if(run>=23362&&run<=23381) Ecm = 2*1.88581; //1885.81 0.02
  if(run>=23382&&run<=23395) Ecm = 2*1.88584; //1885.84 0.02
  if(run>=23396&&run<=23406) Ecm = 2*1.88584; //1885.84 0.03
  if(run>=23407&&run<=23417) Ecm = 2*1.88578; //1885.78 0.03
  if(run>=23418&&run<=23436) Ecm = 2*1.88582; //1885.82 0.02
  if(run>=23437&&run<=23446) Ecm = 2*1.88582; //1885.82 0.02
  if(run>=23447&&run<=23454) Ecm = 2*1.8858 ; //1885.8  0.02
                                            
  // XYZ data:
  if(run>=23463&&run<=24177) Ecm = 4.009;   
//  if(run>=32239&&run<=33484) Ecm = 4.23;   
  if(run>=32239&&run<=33484) Ecm = 4.22626;   
  if(run>=29677&&run<=30367) Ecm = 4.26;
  if(run>=31561&&run<=31981) Ecm = 4.26;   
  if(run>=30616&&run<=31279) Ecm = 4.36;   
   
  if(run>=33490&&run<=33556) Ecm = 3.810;   
  if(run>=33572&&run<=33657) Ecm = 3.900;   
  if(run>=33659&&run<=33719) Ecm = 4.090;   
  if(run>=30372&&run<=30437) Ecm = 4.19;   
  if(run>=31983&&run<=32045) Ecm = 4.21;   
  if(run>=32046&&run<=32140) Ecm = 4.22;  
//  if(run>=30438&&run<=30491) Ecm = 4.23;   
  if(run>=30438&&run<=30491) Ecm = 4.22626;   
  if(run>=32141&&run<=32226) Ecm = 4.245; 
  if(run>=30492&&run<=30557) Ecm = 4.31;   
  if(run>=31281&&run<=31325) Ecm = 4.39;  
  if(run>=31327&&run<=31390) Ecm = 4.42;  

  // tau scan data:
  if(run>=24983&&run<=25015) Ecm = 3.5426;
  if(run>=25016&&run<=25094) Ecm = 3.5540;
  if(run>=25100&&run<=25141) Ecm = 3.5614;
  if(run>=25143&&run<=25243) Ecm = 3.6004;

  if(run>=35227&&run<=36213) Ecm = 4.600;

  if(run>=36773&&run<=38140) Ecm = 4.42;
  
  //2017 XYZ data:
  if(run>=47543&&run<=48170) Ecm = 4.190;
  if(run>=48172&&run<=48713) Ecm = 4.200;
  if(run>=48714&&run<=49239) Ecm = 4.210;
  if(run>=49270&&run<=49787) Ecm = 4.220;
  if(run>=49788&&run<=50254) Ecm = 4.237;
  if(run>=50255&&run<=50793) Ecm = 4.246;
  if(run>=50796&&run<=51302) Ecm = 4.270;
  if(run>=51303&&run<=51498) Ecm = 4.280;
                                           
  return ;                                  
}                                           
                                            
