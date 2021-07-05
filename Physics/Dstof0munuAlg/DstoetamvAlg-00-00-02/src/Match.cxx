#include <iostream>
#include "DstoetamvAlg/Match.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef std::vector<HepLorentzVector> Vp4;
Match::Match(){}

double Match::match(){

//R4_kp;   Tp4_kp;    
//R4_km;   Tp4_km;
//R4_pip;  Tp4_pip;
//R4_pim;  Tp4_pim;
//R4_gam;  Tp4_gam;
//R4_pi0;  Tp4_pi0;
//R4_eta;  Tp4_eta;
//R4_e;    Tp4_e;
//R4_mu;   Tp4_mu;

Vp4 T4_kp;T4_kp.clear();
Vp4 T4_km;T4_km.clear();
Vp4 T4_pip;T4_pip.clear();
Vp4 T4_pim;T4_pim.clear();
Vp4 T4_gam;T4_gam.clear();
Vp4 T4_pi0;T4_pi0.clear();
Vp4 T4_eta;T4_eta.clear();
Vp4 T4_e;T4_e.clear();
Vp4 T4_mu;T4_mu.clear();
if(tagcharge==-1){
T4_kp=Tm4_kp;
T4_km=Tm4_km;
T4_pip=Tm4_pip;
T4_pim=Tm4_pim;
T4_gam=Tm4_gam;
T4_pi0=Tm4_pi0;
T4_eta=Tm4_eta;
T4_e=Tm4_e;
T4_mu=Tm4_mu;
}
else{
T4_kp=Tp4_kp;
T4_km=Tp4_km;
T4_pip=Tp4_pip;
T4_pim=Tp4_pim;
T4_gam=Tp4_gam;
T4_pi0=Tp4_pi0;
T4_eta=Tp4_eta;
T4_e=Tp4_e;
T4_mu=Tp4_mu;
}

	double max[9]={0};
if(R4_kp.size()==T4_kp.size()&&R4_kp.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_kp.size();i++){
for(int j=0;j<T4_kp.size();j++){
angle1[i][j]=R4_kp[i].vect().angle(T4_kp[j].vect())/3.1415926*180.;
}
}
max[0]=MaxAngle(angle1);
}
if(R4_km.size()==T4_km.size()&&R4_km.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_km.size();i++){
for(int j=0;j<T4_km.size();j++){
angle1[i][j]=R4_km[i].vect().angle(T4_km[j].vect())/3.1415926*180.;
}
}
max[1]=MaxAngle(angle1);
}

if(R4_pip.size()==T4_pip.size()&&R4_pip.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_pip.size();i++){
for(int j=0;j<T4_pip.size();j++){
angle1[i][j]=R4_pip[i].vect().angle(T4_pip[j].vect())/3.1415926*180.;

}
}
max[2]=MaxAngle(angle1);
}


if(R4_pim.size()==T4_pim.size()&&R4_pim.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_pim.size();i++){
for(int j=0;j<T4_pim.size();j++){
angle1[i][j]=R4_pim[i].vect().angle(T4_pim[j].vect())/3.1415926*180.;
}
}
max[3]=MaxAngle(angle1);
}

if(R4_gam.size()==T4_gam.size()&&R4_gam.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_gam.size();i++){
for(int j=0;j<T4_gam.size();j++){
angle1[i][j]=R4_gam[i].vect().angle(T4_gam[j].vect())/3.1415926*180.;
}
}
max[4]=MaxAngle(angle1);
}
if(R4_pi0.size()==T4_pi0.size()&&R4_pi0.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_pi0.size();i++){
for(int j=0;j<T4_pi0.size();j++){
angle1[i][j]=R4_pi0[i].vect().angle(T4_pi0[j].vect())/3.1415926*180.;
}
}
max[5]=MaxAngle(angle1);
}


if(R4_eta.size()==T4_eta.size()&&R4_eta.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_eta.size();i++){
for(int j=0;j<T4_eta.size();j++){
angle1[i][j]=R4_eta[i].vect().angle(T4_eta[j].vect())/3.1415926*180.;
}
}
max[6]=MaxAngle(angle1);
}

if(R4_e.size()==T4_e.size()&&R4_e.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_e.size();i++){
for(int j=0;j<T4_e.size();j++){
angle1[i][j]=R4_e[i].vect().angle(T4_e[j].vect())/3.1415926*180.;
}
}
max[7]=MaxAngle(angle1);
}


if(R4_mu.size()==T4_mu.size()&&R4_mu.size()!=0){
double angle1[4][4]={0};
for(int i=0;i<R4_mu.size();i++){
for(int j=0;j<T4_mu.size();j++){
angle1[i][j]=R4_mu[i].vect().angle(T4_mu[j].vect())/3.1415926*180.;
}
}
max[8]=MaxAngle(angle1);
}
sort(max,max+8,greater<double>());
return max[0];


}

double Match::MaxAngle(double angle[4][4]){
	double ang[24]={0};
	int tem=0;
double cut=999;
double max_angle=999;


if(angle[0][0]!=0&&angle[0][1]==0){
for(int i1=0;i1<1;i1++){
ang[tem]=angle[i1][0];
if(ang[tem]<cut){
cut=ang[tem];
double angtem[1]={angle[i1][0]};
sort(angtem,angtem+1,greater<double>());
max_angle=angtem[0];
}
tem++;
}
}

if(angle[0][1]!=0&&angle[0][2]==0){
for(int i1=0;i1<2;i1++){
for(int i2=0;i2<2;i2++){
if(i2==i1)continue;
ang[tem]=angle[i1][0]+angle[i2][1];
if(ang[tem]<cut){
cut=ang[tem];
double angtem[2]={angle[i1][0],angle[i2][1]};
sort(angtem,angtem+2,greater<double>());
max_angle=angtem[0];
}
tem++;
}
}
}


if(angle[0][2]!=0&&angle[0][3]==0){
for(int i1=0;i1<3;i1++){
for(int i2=0;i2<3;i2++){
if(i2==i1)continue;
for(int i3=0;i3<3;i3++){
if(i3==i2||i3==i1)continue;
ang[tem]=angle[i1][0]+angle[i2][1]+angle[i3][2];
if(ang[tem]<cut){
cut=ang[tem];
double angtem[3]={angle[i1][0],angle[i2][1],angle[i3][2]};
sort(angtem,angtem+3,greater<double>());
max_angle=angtem[0];
}
tem++;
}
}
}
}

if(angle[0][3]!=0){
for(int i1=0;i1<4;i1++){
for(int i2=0;i2<4;i2++){
if(i2==i1)continue;
for(int i3=0;i3<4;i3++){
if(i3==i2||i3==i1)continue;
for(int i4=0;i4<4;i4++){
if(i4==i3||i4==i2||i4==i1)continue;
ang[tem]=angle[i1][0]+angle[i2][1]+angle[i3][2]+angle[i4][3];
if(ang[tem]<cut){
cut=ang[tem];
double angtem[4]={angle[i1][0],angle[i2][1],angle[i3][2],angle[i4][3]};
sort(angtem,angtem+4,greater<double>());
max_angle=angtem[0];
}
tem++;
}
}
}
}
}

return max_angle;
}

double Match::compare(double Angle1,double Angle2,double Angle3,double Angle4){
if(Angle1!=0&&Angle1>Angle2&&Angle1>Angle3&&Angle1>Angle4){
return Angle1;
}
if(Angle2!=0&&Angle2>Angle1&&Angle2>Angle3&&Angle2>Angle4){
return Angle2;
}
if(Angle3!=0&&Angle3>Angle1&&Angle3>Angle2&&Angle3>Angle4){
return Angle3;
}
if(Angle4!=0&&Angle4>Angle1&&Angle4>Angle3&&Angle4>Angle2){
return Angle4;
}

}

Match::~Match(){
}
