#define hAnaBeam_cxx
#include "hAnaBeam.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void hAnaBeam::Loop(TString opFile)
{
TFile *popfile = new TFile(opFile,"RECREATE");
const Int_t NBLM = 50;
const Int_t NTEST = 9;
//SSEM in
TH2F* hblmvsct[NBLM];
TGraphErrors *gr[NTEST];

Double_t xBLM[NBLM];
Double_t xerrBLM[NBLM];
for(int i=0; i<NBLM; i++){
xBLM[i] = i+1;
xerrBLM[i]=0.25;
}
Double_t meanADC[NTEST][NBLM];
Double_t rmsADC[NTEST][NBLM];

TH1F* hdata[NBLM][NTEST];
TH1F* hct[NTEST];

//SSEM out for calibration
//gain is 10 larger
const Int_t OUTNTEST = 11;
TGraphErrors *grout[OUTNTEST];
Double_t meanADCout[OUTNTEST][NBLM];
Double_t rmsADCout[OUTNTEST][NBLM];

TH1F* hdata_out[NBLM][OUTNTEST];
TH1F* hct_out[OUTNTEST];

for(int j=0; j<NTEST; j++){
for(int i=0; i<NBLM; i++){
hdata[i][j] = new TH1F(Form("hdata_blm%d_sam%d",i,j),"",3000,0,1500);
}
hct[j] = new TH1F(Form("hct_sam%d",j),"",5000,2.5e12,2.525e14);
}
for (Int_t iblm=0; iblm<NBLM; ++iblm) {
	hblmvsct[iblm] = new TH2F(Form("hblmvsCT%d",iblm+1),Form("hblmvsCT%d",iblm+1),5000,2.5e12,2.525e14,3000,0,1500);
}

//for SSEM out
for(int j=0; j<OUTNTEST; j++){
for(int i=0; i<NBLM; i++){
hdata_out[i][j] = new TH1F(Form("houtdata_blm%d_sam%d",i,j),"",3000,0,1500);
}
hct_out[j] = new TH1F(Form("houtct_sam%d",j),"",5000,2.5e12,2.525e14);
}
///////////
   if (fChain == 0) return;

  // Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nentries = fChain->GetEntries();
	cout<<"number of entries "<<nentries<<endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
//#720122 CT att setting : 30dB shot #13-63
if(nurun==720122 && (midas_event>=13 && midas_event<=63)){ cout<<"SSEM out 100%:  CT 30db "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][0]->Fill(blmint[iblm]);
                hct_out[0]->Fill(ct[4]);
        }

}
//#116-136
if(nurun==720122 && (midas_event>=116 && midas_event<=136)){ cout<<"SSEM out 100%:  CT 30db"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][1]->Fill(blmint[iblm]);
                hct_out[1]->Fill(ct[4]);
        }

}
//137-187
if(nurun==720122 && (midas_event>=137 && midas_event<=187)){ cout<<"SSEM out 100%:  CT 30db"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][2]->Fill(blmint[iblm]);
                hct_out[2]->Fill(ct[4]);
        }

}

//#240-290
if(nurun==720122 && (midas_event>=240 && midas_event<=290)){ cout<<"SSEM out 100%:  CT 30db"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][3]->Fill(blmint[iblm]);
                hct_out[3]->Fill(ct[4]);
        }

}



if(nurun==720124 && (midas_event>=14 && midas_event<=64)){ cout<<"mabiki=2  CT 0dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][4]->Fill(blmint[iblm]);
                hct_out[4]->Fill(ct[4]);
        }
}

if(nurun==720124 && (midas_event>=65 && midas_event<=115)){ cout<<"mabiki=2  CT 6dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][5]->Fill(blmint[iblm]);
                hct_out[5]->Fill(ct[4]);
        }
}

if(nurun==720124 && (midas_event>=116 && midas_event<=166)){ cout<<"mabiki=8  CT 6dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][6]->Fill(blmint[iblm]);
                hct_out[6]->Fill(ct[4]);
        }
}

if(nurun==720124 && (midas_event>=311 && midas_event<=361)){ cout<<"mabiki=18  CT 12dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][7]->Fill(blmint[iblm]);
                hct_out[7]->Fill(ct[4]);
        }
}
//r720126 is after tuning
if(nurun==720126 && (midas_event>=13 && midas_event<=63)){ cout<<"mabiki=18  CT 12dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][8]->Fill(blmint[iblm]);
                hct_out[8]->Fill(ct[4]);
        }
}


if(nurun==720126 && (midas_event>=64 && midas_event<=114)){ cout<<"mabiki=18  CT 18dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][9]->Fill(blmint[iblm]);
                hct_out[9]->Fill(ct[4]);
        }
}

if(nurun==720126 && (midas_event>=115 && midas_event<=165)){ cout<<"mabiki=18  CT 24dB"<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out[iblm][10]->Fill(blmint[iblm]);
                hct_out[10]->Fill(ct[4]);
        }
}


///////////////SSEM in
//40% intensity   10 shots (1-5 : mabiki=14) 
   if(nurun==720123 && (midas_event>=14 && midas_event<=24)){ cout<<"40% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
       for (Int_t iblm=0; iblm<NBLM; ++iblm) {
		hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
		hdata[iblm][0]->Fill(blmint[iblm]);
		hct[0]->Fill(ct[4]);
	}
	}
//60% intensity   10 shots (1-4 : mabiki=16)
    if(nurun==720123 && (midas_event>=25 && midas_event<=35)){ cout<<"60% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
   for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
		hdata[iblm][1]->Fill(blmint[iblm]);
		hct[1]->Fill(ct[4]);
        }
	 }

//80% intensity   10 shots (1-2 : mabiki=24, 380kW)
   if(nurun==720123 && (midas_event>=36 && midas_event<=46)){ cout<<"80% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
	for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
		hdata[iblm][2]->Fill(blmint[iblm]);
		hct[2]->Fill(ct[4]);
        }
	}
//Full intensity  10 shots  (1-0: mabiki=26, BW=463us, 450kW)    
if(nurun==720123 && (midas_event>=47 && midas_event<=57)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
	for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
		hdata[iblm][3]->Fill(blmint[iblm]);
		hct[3]->Fill(ct[4]);
        }
	}  

//mp=100us, bw=451ns, mabiki=24 ==> ppb=3.92e13/8  (8bunch=76.5kW)
if(nurun==720123 && (midas_event>=60 && midas_event<=70)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][4]->Fill(blmint[iblm]);
                hct[4]->Fill(ct[4]);
        }
        }

//mp=100us, bw=451ns, mabiki=12 ==> ppb=2.47e12  (8bunch=38.3kW)
//
if(nurun==720123 && (midas_event>=71 && midas_event<=81)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][5]->Fill(blmint[iblm]);
                hct[5]->Fill(ct[4]);
        }
        }

//mp=100us, bw=451ns, mabiki=8  ==> ppb=1.36e13/8  (8bunch=25kW)
if(nurun==720123 && (midas_event>=82 && midas_event<=92)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][6]->Fill(blmint[iblm]);
                hct[6]->Fill(ct[4]);
        }       
        }

//(2-3) mp=100us, bw=451ns, mabiki=4  ==> ppb=8.23e11  (8bunch=12.8kW)
if(nurun==720123 && (midas_event>=95 && midas_event<=105)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][7]->Fill(blmint[iblm]);
                hct[7]->Fill(ct[4]);
        }
        }

//mabiki=2 ==> ppb=3.27e12/8, 6.3kW
if(nurun==720123 && (midas_event>=106 && midas_event<=126)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][8]->Fill(blmint[iblm]);
                hct[8]->Fill(ct[4]);
        }
        }

 }//end for
//get mean and RMS
for(int j=0; j<NTEST; j++){
	for (Int_t iblm=0; iblm<NBLM; ++iblm) {
		meanADC[j][iblm] = hdata[iblm][j]->GetMean();
		rmsADC[j][iblm] = hdata[iblm][j]->GetRMS();
	}
}
for(int j=0; j<NTEST; j++){
gr[j] = new TGraphErrors(NBLM,xBLM,meanADC[j],xerrBLM,rmsADC[j]);
gr[j]->Write(Form("grtest_%d",j));
}


//for SSEM out
for(int j=0; j<OUTNTEST; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                meanADCout[j][iblm] = hdata_out[iblm][j]->GetMean();
                rmsADCout[j][iblm] = hdata_out[iblm][j]->GetRMS();
        }
}
for(int j=0; j<OUTNTEST; j++){
grout[j] = new TGraphErrors(NBLM,xBLM,meanADCout[j],xerrBLM,rmsADCout[j]);
grout[j]->Write(Form("grouttest_%d",j));
}

//Write output
    popfile->Write();
     popfile->Close();
}
