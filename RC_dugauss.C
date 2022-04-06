#include <iostream>
#include <fstream>
#include <math.h>

#include "TH1F.h"
#include "TF1.h"
#include "TLine.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"


///GRAFICO 1:98cm


void RC_dugauss(){

const float m1_g1=180.9;
const float err_m1_g1=0.4;
const float m2_g1=227.6;
const float err_m2_g1=0.7;
const float h1=11.0;
const float err_h1=0.1; //cm

const float m1_g2=204.6;
const float err_m1_g2=0.8;
const float m2_g2=248.9;
const float err_m2_g2=1.9;
const float h2=98.5; //cm
const float err_h2=0.1; //cm

const float m1_g3=202.4;
const float err_m1_g3=6.3;
const float m2_g3=244.4;
const float err_m2_g3=1.3;
const float h3=148.4; //cm
const float err_h3=0.1; //cm

const float m1_g4=235.9;
const float err_m1_g4=0.2;
const float m2_g4=261.0;
const float err_m2_g4=1.2;
const float h4=172.2;  //cm
const float err_h4=0.1; //cm

const float n_misure=4;
float m1[]={m1_g1,m1_g2,m1_g3,m1_g4};
float m2[]={m2_g1,m2_g2,m2_g3,m2_g4};
float err_m1[]={err_m1_g1,err_m1_g2,err_m1_g3,err_m1_g4};
float err_m2[]={err_m2_g1,err_m2_g2,err_m2_g3,err_m2_g4};
float h[]={h1,h2,h3,h4};
float err_h[]={err_h1,err_h2,err_h3,err_h4};

//------------------------DELTA----------------------
float dm[4]={};
float err_dm[4]={};
for (int i=0;i<n_misure;i++){
  dm[i]=m2[i]-m1[i];
  err_dm[i]=err_m1[i]+err_m2[i];
  cout<<"DELTA: "<<dm[i]<<" +/- "<<err_dm[i]<<endl;
}


TCanvas *G = new TCanvas("G","Delta mean",0,400,800,600);
G->cd();

TGraphErrors *Misure1 = new TGraphErrors(n_misure,h,dm,err_h,err_dm);
Misure1->SetMarkerSize(0.5);
Misure1->SetMarkerStyle(21);
Misure1->SetTitle("Delta Mean");
Misure1->GetXaxis()->SetTitle("Altezza (cm)");
Misure1->GetYaxis()->SetTitle("Differenza tra le medie");
//Misure1->Draw("APL");
Misure1->SetLineColor(2);
Misure1->Draw("AP");



//MEDIA DELLE medie


float mm[4]={};
float err_mm[4]={};

for(int i=0;i<n_misure;i++){
  mm[i]=(m2[i]+m1[i])/2;
  err_mm[i]=err_m1[i]+err_m2[i];
  cout<<"Means: "<<mm[i]<<" +/- "<<err_mm[i]<<endl;
}


float v_volo[4]={};
float err_v_volo[4]={};
float t[4]={};
float err_t[4]={};
for (int i=0;i<4;i++){
  t[i]=0.0978*mm[i]+1.6;
  err_t[i]=sqrt((0.0978*err_mm[i])*(0.0978*err_mm[i])+(mm[i]*0.0015)*(mm[i]*0.0015)+(0.4*0.4));
  cout<<"tempo di volo: "<<t[i]<<" +/- "<<err_t[i]<<endl;
}


for(int i=0;i<4;i++){
  v_volo[i]=h[i]/t[i];
  err_v_volo[i]=(err_h[i]/t[i])-((h[i]*err_t[i])/pow(t,2));
  cout<<"Altezze: "<<h[i]<<" +/- "<<err_h[i]<<endl;
  cout<<"Velocità di volo: "<<v_volo[i]<<" +/- "<<err_v_volo[i]<<endl;
}




}
