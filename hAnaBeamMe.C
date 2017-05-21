#define hAnaBeamMe_cxx
#include "hAnaBeamMe.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
void hAnaBeamMe::SiMonCheck(TString opFile)
{
   	 TFile *popfile = new TFile(opFile,"RECREATE");
    	const Int_t NBLM = 52;
	TH1F* hdata[NBLM];
	TH2F* hcorNN1[NBLM];
	for(int i=0; i<NBLM; i++){
		if(i<NBLM-2)hdata[i] = new TH1F(Form("hdata_blm%d",i),"",1000,1,1000);
		else hdata[i] = new TH1F(Form("hdata_blm%d",i),"",1000,0,100);

		if(i<NBLM-2)hcorNN1[i] = new TH2F(Form("hcorNN1_blm%d",i),"",1000,1,1000,1000,1,1000);
		else hcorNN1[i] = new TH2F(Form("hcorNN1_blm%d",i),"",1000,1,1000,1000,0,100);
	}

	if (fChain == 0) return;		
	
	Long64_t nentries = fChain->GetEntries();
    	cout<<"number of entries "<<nentries<<endl;
    	Long64_t nbytes = 0, nb = 0;
    	for (Long64_t jentry=0; jentry<nentries;jentry++) {
        	Long64_t ientry = LoadTree(jentry);
        	if (ientry < 0) break;
       		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if(ct[0]>0){
			for (Int_t iblm=0; iblm<NBLM; ++iblm) {
			hdata[iblm]->Fill(blmint[iblm]);
			if(i<NBLM-2)hcorNN1[iblm]->Fill(blmint[iblm],blmint[iblm+1]);
			else if (iblm==(NBLM-2)) hcorNN1[iblm]->Fill(blmint[0],blmint[50]);
			else hcorNN1[iblm]->Fill(blmint[15],blmint[51]);
			}
		
		}//end if
	}	
	//end for jentry
	
    popfile->Write();
    popfile->Close();


}
void hAnaBeamMe::Loop(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
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
   
    TH2F* Si01_vs_blm01 = new TH2F("Si01_vs_blm01","",400,0,200,100,0,50);
    TH2F* Si02_vs_blm16 = new TH2F("Si02_vs_blm16","",1200,0,600,200,0,100); 
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
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
		Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //60% intensity   10 shots (1-4 : mabiki=16)
        if(nurun==720123 && (midas_event>=25 && midas_event<=35)){ cout<<"60% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][1]->Fill(blmint[iblm]);
                hct[1]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //80% intensity   10 shots (1-2 : mabiki=24, 380kW)
        if(nurun==720123 && (midas_event>=36 && midas_event<=46)){ cout<<"80% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][2]->Fill(blmint[iblm]);
                hct[2]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //Full intensity  10 shots  (1-0: mabiki=26, BW=463us, 450kW)
        if(nurun==720123 && (midas_event>=47 && midas_event<=57)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][3]->Fill(blmint[iblm]);
                hct[3]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=24 ==> ppb=3.92e13/8  (8bunch=76.5kW)
        if(nurun==720123 && (midas_event>=60 && midas_event<=70)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][4]->Fill(blmint[iblm]);
                hct[4]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=12 ==> ppb=2.47e12  (8bunch=38.3kW)
        //
        if(nurun==720123 && (midas_event>=71 && midas_event<=81)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][5]->Fill(blmint[iblm]);
                hct[5]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=8  ==> ppb=1.36e13/8  (8bunch=25kW)
        if(nurun==720123 && (midas_event>=82 && midas_event<=92)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][6]->Fill(blmint[iblm]);
                hct[6]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //(2-3) mp=100us, bw=451ns, mabiki=4  ==> ppb=8.23e11  (8bunch=12.8kW)
        if(nurun==720123 && (midas_event>=95 && midas_event<=105)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][7]->Fill(blmint[iblm]);
                hct[7]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mabiki=2 ==> ppb=3.27e12/8, 6.3kW
        if(nurun==720123 && (midas_event>=106 && midas_event<=126)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][8]->Fill(blmint[iblm]);
                hct[8]->Fill(ct[4]);
		Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
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
   Si01_vs_blm01->Write("Si01_vs_blm01");
   Si02_vs_blm16->Write("Si02_vs_blm16"); 
    //Write output
    popfile->Write();
    popfile->Close();

}

void hAnaBeamMe::BLM15PosCheck(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
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
    
    //new data after moving BLM15 by 4cm
    TH1F* hdata_blm15new[NBLM];
    TH1F* hct_blm15new;
    Double_t meanADC_blm15new[NBLM];
    Double_t rmsADC_blm15new[NBLM];
    TGraphErrors *gr_blm15new;
    
    TH2F* Si01_vs_blm01 = new TH2F("Si01_vs_blm01","",400,0,200,100,0,50);
    TH2F* Si02_vs_blm16 = new TH2F("Si02_vs_blm16","",1200,0,600,200,0,100);
    //SSEM out for calibration
    //gain is 10 larger
    const Int_t OUTNTEST = 11;
    TGraphErrors *grout[OUTNTEST];
    Double_t meanADCout[OUTNTEST][NBLM];
    Double_t rmsADCout[OUTNTEST][NBLM];
    
    TH1F* hdata_out[NBLM][OUTNTEST];
    TH1F* hct_out[OUTNTEST];
    
    //new data after moving BLM15 by 4cm
    TH1F* hdata_out_blm15new[NBLM];
    TH1F* hct_out_blm15new;
    Double_t meanADCout_blm15new[NBLM];
    Double_t rmsADCout_blm15new[NBLM];
    TGraphErrors *grout_blm15new;
    
    
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
    
    //for new BLM 15 pos.
    for(int i=0; i<NBLM; i++){
        hdata_blm15new[i] = new TH1F(Form("hdata_blm15new_blm%d",i),"",3000,0,1500);
        hdata_out_blm15new[i] = new TH1F(Form("houtdata_blm15new_blm%d",i),"",3000,0,1500);
    }
    hct_blm15new = new TH1F("hct_blm15new","",5000,2.5e12,2.525e14);
    hct_out_blm15new = new TH1F("hct_out_blm15new","",5000,2.5e12,2.525e14);
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
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //60% intensity   10 shots (1-4 : mabiki=16)
        if(nurun==720123 && (midas_event>=25 && midas_event<=35)){ cout<<"60% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][1]->Fill(blmint[iblm]);
                hct[1]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //80% intensity   10 shots (1-2 : mabiki=24, 380kW)
        if(nurun==720123 && (midas_event>=36 && midas_event<=46)){ cout<<"80% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][2]->Fill(blmint[iblm]);
                hct[2]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //Full intensity  10 shots  (1-0: mabiki=26, BW=463us, 450kW)
        if(nurun==720123 && (midas_event>=47 && midas_event<=57)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][3]->Fill(blmint[iblm]);
                hct[3]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=24 ==> ppb=3.92e13/8  (8bunch=76.5kW)
        if(nurun==720123 && (midas_event>=60 && midas_event<=70)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][4]->Fill(blmint[iblm]);
                hct[4]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=12 ==> ppb=2.47e12  (8bunch=38.3kW)
        //
        if(nurun==720123 && (midas_event>=71 && midas_event<=81)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][5]->Fill(blmint[iblm]);
                hct[5]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=8  ==> ppb=1.36e13/8  (8bunch=25kW)
        if(nurun==720123 && (midas_event>=82 && midas_event<=92)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][6]->Fill(blmint[iblm]);
                hct[6]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //(2-3) mp=100us, bw=451ns, mabiki=4  ==> ppb=8.23e11  (8bunch=12.8kW)
        if(nurun==720123 && (midas_event>=95 && midas_event<=105)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][7]->Fill(blmint[iblm]);
                hct[7]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mabiki=2 ==> ppb=3.27e12/8, 6.3kW
        if(nurun==720123 && (midas_event>=106 && midas_event<=126)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][8]->Fill(blmint[iblm]);
                hct[8]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //for new position
        //SSEM in 50 shot
        if (nurun==730010 && (midas_event>=15 && midas_event<=65)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_blm15new[iblm]->Fill(blmint[iblm]);
            }
            hct_blm15new->Fill(ct[4]);
        }
        //SSEM out
        if (nurun==730018 && (midas_event>=18860 && midas_event<=18960)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out_blm15new[iblm]->Fill(blmint[iblm]);
            }
            hct_out_blm15new->Fill(ct[4]);
        }
        
    }//end for
    //get mean and RMS for SSEM in
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
    
    
    
    //get mean and RMS for SSEM out
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
    
    //get mean and RMS for new pos. of BLM15
    for (Int_t iblm=0; iblm<NBLM; ++iblm) {
        meanADC_blm15new[iblm] = hdata_blm15new[iblm]->GetMean();
        rmsADC_blm15new[iblm] = hdata_blm15new[iblm]->GetRMS();
        
        meanADCout_blm15new[iblm] = hdata_out_blm15new[iblm]->GetMean();
        rmsADCout_blm15new[iblm] = hdata_out_blm15new[iblm]->GetRMS();
    }
    gr_blm15new = new TGraphErrors(NBLM,xBLM,meanADC_blm15new,xerrBLM,rmsADC_blm15new);
    grout_blm15new = new TGraphErrors(NBLM,xBLM,meanADCout_blm15new,xerrBLM,rmsADCout_blm15new);
    gr_blm15new->Write("gr_blm15new");
    grout_blm15new->Write("grout_blm15new");
    
    Si01_vs_blm01->Write("Si01_vs_blm01");
    Si02_vs_blm16->Write("Si02_vs_blm16");
    //Write output
    popfile->Write();
    popfile->Close();
    
}
void hAnaBeamMe::BeamScan20170310(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    /***********************************/
    //for Beam intensity on 2017 Feb. 13
    /***********************************/
    const Int_t NTEST = 9;
    //SSEM in
    TH2F* hblmvsct[NBLM];
    TGraphErrors *gr[NTEST];
    Double_t meanADC[NTEST][NBLM];
    Double_t rmsADC[NTEST][NBLM];
    TH1F* hdata[NBLM][NTEST];
    TH1F* hct[NTEST];
    TH2F* Si01_vs_blm01 = new TH2F("Si01_vs_blm01","",400,0,200,100,0,50);
    TH2F* Si02_vs_blm16 = new TH2F("Si02_vs_blm16","",1200,0,600,200,0,100);
    //SSEM out for calibration; gain is 10 larger
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
    /***********************************/
    /*new data after moving BLM15 by 4cm*/
    /***********************************/
    //SSEM IN
    TH1F* hdata_blm15new[NBLM];
    TH1F* hct_blm15new;
    Double_t meanADC_blm15new[NBLM];
    Double_t rmsADC_blm15new[NBLM];
    TGraphErrors *gr_blm15new;
    
    //SSEM OUT; gain is 10 larger
    TH1F* hdata_out_blm15new[NBLM];
    TH1F* hct_out_blm15new;
    Double_t meanADCout_blm15new[NBLM];
    Double_t rmsADCout_blm15new[NBLM];
    TGraphErrors *grout_blm15new;
    
    for(int i=0; i<NBLM; i++){
        hdata_blm15new[i] = new TH1F(Form("hdata_blm15new_blm%d",i),"",3000,0,1500);
        hdata_out_blm15new[i] = new TH1F(Form("houtdata_blm15new_blm%d",i),"",3000,0,1500);
    }
    hct_blm15new = new TH1F("hct_blm15new","",5000,2.5e12,2.525e14);
    hct_out_blm15new = new TH1F("houtct_blm15new","",5000,2.5e12,2.525e14);
    
    
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 10 run 73011
    /***********************************/
    const Int_t NTEST17310 = 5;
    //SSEM in
    TGraphErrors *gr_17310[NTEST17310];
    Double_t meanADC_17310[NTEST17310][NBLM];
    Double_t rmsADC_17310[NTEST17310][NBLM];
    TH1F* hdata_17310[NBLM][NTEST17310];
    TH1F* hct_17310[NTEST17310];
    
    for(int j=0; j<NTEST17310; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17310[i][j] = new TH1F(Form("hdata17310_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17310[j] = new TH1F(Form("hct17310_sam%d",j),"",5000,2.5e12,2.525e14);
    }
    
    /***********************************/
    /*Move SSEM 19 out 730012*/
    /***********************************/
    //SSEM IN
    TH1F* hdata_ssem19out[NBLM];
    TH1F* hct_ssem19out;
    Double_t meanADC_ssem19out[NBLM];
    Double_t rmsADC_ssem19out[NBLM];
    TGraphErrors *gr_ssem19out;
    
    //SSEM OUT; gain is 10 larger
    TH1F* hdata_out_ssem19out[NBLM];
    TH1F* hct_out_ssem19out;
    Double_t meanADCout_ssem19out[NBLM];
    Double_t rmsADCout_ssem19out[NBLM];
    TGraphErrors *grout_ssem19out;
    
    for(int i=0; i<NBLM; i++){
        hdata_ssem19out[i] = new TH1F(Form("hdata_ssem19out_blm%d",i),"",3000,0,1500);
        hdata_out_ssem19out[i] = new TH1F(Form("houtdata_ssem19out_blm%d",i),"",3000,0,1500);
    }
    hct_ssem19out = new TH1F("hct_ssem19out","",5000,2.5e12,2.525e14);
    hct_out_ssem19out = new TH1F("houtct_ssem19out","",5000,2.5e12,2.525e14);
    
    
    
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
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //60% intensity   10 shots (1-4 : mabiki=16)
        if(nurun==720123 && (midas_event>=25 && midas_event<=35)){ cout<<"60% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][1]->Fill(blmint[iblm]);
                hct[1]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //80% intensity   10 shots (1-2 : mabiki=24, 380kW)
        if(nurun==720123 && (midas_event>=36 && midas_event<=46)){ cout<<"80% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][2]->Fill(blmint[iblm]);
                hct[2]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //Full intensity  10 shots  (1-0: mabiki=26, BW=463us, 450kW)
        if(nurun==720123 && (midas_event>=47 && midas_event<=57)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][3]->Fill(blmint[iblm]);
                hct[3]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=24 ==> ppb=3.92e13/8  (8bunch=76.5kW)
        if(nurun==720123 && (midas_event>=60 && midas_event<=70)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][4]->Fill(blmint[iblm]);
                hct[4]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=12 ==> ppb=2.47e12  (8bunch=38.3kW)
        //
        if(nurun==720123 && (midas_event>=71 && midas_event<=81)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][5]->Fill(blmint[iblm]);
                hct[5]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=8  ==> ppb=1.36e13/8  (8bunch=25kW)
        if(nurun==720123 && (midas_event>=82 && midas_event<=92)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][6]->Fill(blmint[iblm]);
                hct[6]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //(2-3) mp=100us, bw=451ns, mabiki=4  ==> ppb=8.23e11  (8bunch=12.8kW)
        if(nurun==720123 && (midas_event>=95 && midas_event<=105)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][7]->Fill(blmint[iblm]);
                hct[7]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mabiki=2 ==> ppb=3.27e12/8, 6.3kW
        if(nurun==720123 && (midas_event>=106 && midas_event<=126)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][8]->Fill(blmint[iblm]);
                hct[8]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //for new position
        //SSEM in 50 shot
        if (nurun==730010 && (midas_event>=15 && midas_event<=65)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_blm15new[iblm]->Fill(blmint[iblm]);
            }
            hct_blm15new->Fill(ct[4]);
        }
        //SSEM out
        if (nurun==730018 && (midas_event>=18860 && midas_event<=18960)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out_blm15new[iblm]->Fill(blmint[iblm]);
            }
            hct_out_blm15new->Fill(ct[4]);
        }
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 10
        //mabiki=30/32
        if(nurun==730011 && (midas_event>=13 && midas_event<=23)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][0]->Fill(blmint[iblm]);
                hct_17310[0]->Fill(ct[4]);
            }
        }
        //mabiki=28/32
        if(nurun==730011 && (midas_event>=24 && midas_event<=34)){ cout<<"RUN "<<nurun<<" item #2 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][1]->Fill(blmint[iblm]);
                hct_17310[1]->Fill(ct[4]);
            }
        }
        //mabiki=26/32
        if(nurun==730011 && (midas_event>=35 && midas_event<=45)){ cout<<"RUN "<<nurun<<" item #3 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][2]->Fill(blmint[iblm]);
                hct_17310[2]->Fill(ct[4]);
            }
        }
        //mabiki=22/32
        if(nurun==730011 && (midas_event>=46 && midas_event<=56)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][3]->Fill(blmint[iblm]);
                hct_17310[3]->Fill(ct[4]);
            }
        }
        //mabiki=18/32
        if(nurun==730011 && (midas_event>=57 && midas_event<=67)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][4]->Fill(blmint[iblm]);
                hct_17310[4]->Fill(ct[4]);
            }
        }
        //////////////////////////////////////////////////////////////////////////
        
        //SSEM in 50 shot
        if (nurun==730012 && (midas_event>=13 && midas_event<=23)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_ssem19out[iblm]->Fill(blmint[iblm]);
            }
            hct_ssem19out->Fill(ct[4]);
        }
        //SSEM out
        if (nurun==730012 && (midas_event>=24 && midas_event<=34)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out_ssem19out[iblm]->Fill(blmint[iblm]);
            }
            hct_out_ssem19out->Fill(ct[4]);
        }
        //////////////////////////////////////////////////////////////////////////
        
        
    }//end for
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170213
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
    
    //get mean and RMS for SSEM out
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
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for new pos. of BLM15
    for (Int_t iblm=0; iblm<NBLM; ++iblm) {
        meanADC_blm15new[iblm] = hdata_blm15new[iblm]->GetMean();
        rmsADC_blm15new[iblm] = hdata_blm15new[iblm]->GetRMS();
        
        meanADCout_blm15new[iblm] = hdata_out_blm15new[iblm]->GetMean();
        rmsADCout_blm15new[iblm] = hdata_out_blm15new[iblm]->GetRMS();
    }
    
    
    gr_blm15new = new TGraphErrors(NBLM,xBLM,meanADC_blm15new,xerrBLM,rmsADC_blm15new);
    grout_blm15new = new TGraphErrors(NBLM,xBLM,meanADCout_blm15new,xerrBLM,rmsADCout_blm15new);
    gr_blm15new->Write("gr_blm15new");
    grout_blm15new->Write("grout_blm15new");
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170213
    for(int j=0; j<NTEST17310; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17310[j][iblm] = hdata_17310[iblm][j]->GetMean();
            rmsADC_17310[j][iblm] = hdata_17310[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17310; j++){
        gr_17310[j] = new TGraphErrors(NBLM,xBLM,meanADC_17310[j],xerrBLM,rmsADC_17310[j]);
        gr_17310[j]->Write(Form("grtest_17310%d",j));
    }
    
    
    //////////////////////////////////////////////////////////////////////////
    
    for (Int_t iblm=0; iblm<NBLM; ++iblm) {
        meanADC_ssem19out[iblm] = hdata_ssem19out[iblm]->GetMean();
        rmsADC_ssem19out[iblm] = hdata_ssem19out[iblm]->GetRMS();
        
        meanADCout_ssem19out[iblm] = hdata_out_ssem19out[iblm]->GetMean();
        rmsADCout_ssem19out[iblm] = hdata_out_ssem19out[iblm]->GetRMS();
    }
    
    
    gr_ssem19out = new TGraphErrors(NBLM,xBLM,meanADC_ssem19out,xerrBLM,rmsADC_ssem19out);
    grout_ssem19out = new TGraphErrors(NBLM,xBLM,meanADCout_ssem19out,xerrBLM,rmsADCout_ssem19out);
    gr_ssem19out->Write("gr_ssem19out");
    grout_ssem19out->Write("grout_ssem19out");
    //////////////////////////////////////////////////////////////////////////
    
    
    Si01_vs_blm01->Write("Si01_vs_blm01");
    Si02_vs_blm16->Write("Si02_vs_blm16");
    //Write output
    popfile->Write();
    popfile->Close();
    
}
void hAnaBeamMe::BeamScan20170315(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    /***********************************/
    //for Beam intensity on 2017 Feb. 13
    /***********************************/
    const Int_t NTEST = 9;
    //SSEM in
    TH2F* hblmvsct[NBLM];
    TGraphErrors *gr[NTEST];
    Double_t meanADC[NTEST][NBLM];
    Double_t rmsADC[NTEST][NBLM];
    TH1F* hdata[NBLM][NTEST];
    TH1F* hct[NTEST];
    TH2F* Si01_vs_blm01 = new TH2F("Si01_vs_blm01","",400,0,200,100,0,50);
    TH2F* Si02_vs_blm16 = new TH2F("Si02_vs_blm16","",1200,0,600,200,0,100);
    
    TH2F* Si01_vs_blm15_17315 = new TH2F("Si01_vs_blm15_17315","",200,50,100,800,200,400);
    TH2F* Si02_vs_blm15_17315 = new TH2F("Si02_vs_blm15_17315","",200,50,100,800,200,400);
    TH2F* Si01_vs_si02_17315 = new TH2F("Si01_vs_si02_17315","",200,50,100,200,50,100);
    //SSEM out for calibration; gain is 10 larger
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
    /***********************************/
    /*new data after moving BLM15 by 4cm*/
    /***********************************/
    //SSEM IN
    TH1F* hdata_blm15new[NBLM];
    TH1F* hct_blm15new;
    Double_t meanADC_blm15new[NBLM];
    Double_t rmsADC_blm15new[NBLM];
    TGraphErrors *gr_blm15new;
    
    //SSEM OUT; gain is 10 larger
    TH1F* hdata_out_blm15new[NBLM];
    TH1F* hct_out_blm15new;
    Double_t meanADCout_blm15new[NBLM];
    Double_t rmsADCout_blm15new[NBLM];
    TGraphErrors *grout_blm15new;
    
    for(int i=0; i<NBLM; i++){
        hdata_blm15new[i] = new TH1F(Form("hdata_blm15new_blm%d",i),"",3000,0,1500);
        hdata_out_blm15new[i] = new TH1F(Form("houtdata_blm15new_blm%d",i),"",3000,0,1500);
    }
    hct_blm15new = new TH1F("hct_blm15new","",5000,2.5e12,2.525e14);
    hct_out_blm15new = new TH1F("houtct_blm15new","",5000,2.5e12,2.525e14);
    
    
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 10 run 73011
    /***********************************/
    const Int_t NTEST17310 = 5;
    //SSEM in
    TGraphErrors *gr_17310[NTEST17310];
    Double_t meanADC_17310[NTEST17310][NBLM];
    Double_t rmsADC_17310[NTEST17310][NBLM];
    TH1F* hdata_17310[NBLM][NTEST17310];
    TH1F* hct_17310[NTEST17310];
    
    for(int j=0; j<NTEST17310; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17310[i][j] = new TH1F(Form("hdata17310_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17310[j] = new TH1F(Form("hct17310_sam%d",j),"",5000,2.5e12,2.525e14);
    }
    
    /***********************************/
    /*Move SSEM 19 out 730012*/
    /***********************************/
    //SSEM IN
    TH1F* hdata_ssem19out[NBLM];
    TH1F* hct_ssem19out;
    Double_t meanADC_ssem19out[NBLM];
    Double_t rmsADC_ssem19out[NBLM];
    TGraphErrors *gr_ssem19out;
    
    //SSEM OUT; gain is 10 larger
    TH1F* hdata_out_ssem19out[NBLM];
    TH1F* hct_out_ssem19out;
    Double_t meanADCout_ssem19out[NBLM];
    Double_t rmsADCout_ssem19out[NBLM];
    TGraphErrors *grout_ssem19out;
    
    for(int i=0; i<NBLM; i++){
        hdata_ssem19out[i] = new TH1F(Form("hdata_ssem19out_blm%d",i),"",3000,0,1500);
        hdata_out_ssem19out[i] = new TH1F(Form("houtdata_ssem19out_blm%d",i),"",3000,0,1500);
    }
    hct_ssem19out = new TH1F("hct_ssem19out","",5000,2.5e12,2.525e14);
    hct_out_ssem19out = new TH1F("houtct_ssem19out","",5000,2.5e12,2.525e14);
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 15 run 73044
    /***********************************/
    const Int_t NTEST17315 = 4;
    //SSEM in
    TGraphErrors *gr_17315[NTEST17315];
    Double_t meanADC_17315[NTEST17315][NBLM];
    Double_t rmsADC_17315[NTEST17315][NBLM];
    TH1F* hdata_17315[NBLM][NTEST17315];
    TH1F* hct_17315[NTEST17315];
    
    for(int j=0; j<NTEST17315; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17315[i][j] = new TH1F(Form("hdata17315_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17315[j] = new TH1F(Form("hct17315_sam%d",j),"",5000,2.5e12,2.525e14);
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
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //60% intensity   10 shots (1-4 : mabiki=16)
        if(nurun==720123 && (midas_event>=25 && midas_event<=35)){ cout<<"60% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][1]->Fill(blmint[iblm]);
                hct[1]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //80% intensity   10 shots (1-2 : mabiki=24, 380kW)
        if(nurun==720123 && (midas_event>=36 && midas_event<=46)){ cout<<"80% intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][2]->Fill(blmint[iblm]);
                hct[2]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        //Full intensity  10 shots  (1-0: mabiki=26, BW=463us, 450kW)
        if(nurun==720123 && (midas_event>=47 && midas_event<=57)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][3]->Fill(blmint[iblm]);
                hct[3]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=24 ==> ppb=3.92e13/8  (8bunch=76.5kW)
        if(nurun==720123 && (midas_event>=60 && midas_event<=70)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][4]->Fill(blmint[iblm]);
                hct[4]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=12 ==> ppb=2.47e12  (8bunch=38.3kW)
        //
        if(nurun==720123 && (midas_event>=71 && midas_event<=81)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][5]->Fill(blmint[iblm]);
                hct[5]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mp=100us, bw=451ns, mabiki=8  ==> ppb=1.36e13/8  (8bunch=25kW)
        if(nurun==720123 && (midas_event>=82 && midas_event<=92)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][6]->Fill(blmint[iblm]);
                hct[6]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //(2-3) mp=100us, bw=451ns, mabiki=4  ==> ppb=8.23e11  (8bunch=12.8kW)
        if(nurun==720123 && (midas_event>=95 && midas_event<=105)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][7]->Fill(blmint[iblm]);
                hct[7]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //mabiki=2 ==> ppb=3.27e12/8, 6.3kW
        if(nurun==720123 && (midas_event>=106 && midas_event<=126)){ cout<<"Full intensity:  CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hblmvsct[iblm]->Fill(ct[4],blmint[iblm]);
                hdata[iblm][8]->Fill(blmint[iblm]);
                hct[8]->Fill(ct[4]);
                Si01_vs_blm01->Fill(blmint[0],blmint[50]);
                Si02_vs_blm16->Fill(blmint[15],blmint[51]);
            }
        }
        
        //for new position
        //SSEM in 50 shot
        if (nurun==730010 && (midas_event>=15 && midas_event<=65)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_blm15new[iblm]->Fill(blmint[iblm]);
            }
            hct_blm15new->Fill(ct[4]);
        }
        //SSEM out
        if (nurun==730018 && (midas_event>=18860 && midas_event<=18960)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out_blm15new[iblm]->Fill(blmint[iblm]);
            }
            hct_out_blm15new->Fill(ct[4]);
        }
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 10
        //mabiki=30/32
        if(nurun==730011 && (midas_event>=13 && midas_event<=23)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][0]->Fill(blmint[iblm]);
                hct_17310[0]->Fill(ct[4]);
            }
        }
        //mabiki=28/32
        if(nurun==730011 && (midas_event>=24 && midas_event<=34)){ cout<<"RUN "<<nurun<<" item #2 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][1]->Fill(blmint[iblm]);
                hct_17310[1]->Fill(ct[4]);
            }
        }
        //mabiki=26/32
        if(nurun==730011 && (midas_event>=35 && midas_event<=45)){ cout<<"RUN "<<nurun<<" item #3 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][2]->Fill(blmint[iblm]);
                hct_17310[2]->Fill(ct[4]);
            }
        }
        //mabiki=22/32
        if(nurun==730011 && (midas_event>=46 && midas_event<=56)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][3]->Fill(blmint[iblm]);
                hct_17310[3]->Fill(ct[4]);
            }
        }
        //mabiki=18/32
        if(nurun==730011 && (midas_event>=57 && midas_event<=67)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17310[iblm][4]->Fill(blmint[iblm]);
                hct_17310[4]->Fill(ct[4]);
            }
        }
        
        
        //////////////////////////////////////////////////////////////////////////
        
        //SSEM in 50 shot
        if (nurun==730012 && (midas_event>=13 && midas_event<=23)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_ssem19out[iblm]->Fill(blmint[iblm]);
            }
            hct_ssem19out->Fill(ct[4]);
        }
        //SSEM out
        if (nurun==730012 && (midas_event>=24 && midas_event<=34)) {
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_out_ssem19out[iblm]->Fill(blmint[iblm]);
            }
            hct_out_ssem19out->Fill(ct[4]);
        }
        //////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 15
        //mabiki=30/32
        if(nurun==730044 && ((midas_event>=12 && midas_event<=22) || (midas_event>=62 && midas_event<=72))){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17315[iblm][0]->Fill(blmint[iblm]);
                hct_17315[0]->Fill(ct[4]);
            }
            Si01_vs_blm15_17315->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17315->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17315->Fill(blmint[50],blmint[51]);
        }
        //mabiki=28/32
        if(nurun==730044 && (midas_event>=24 && midas_event<=34)){ cout<<"RUN "<<nurun<<" item #2 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17315[iblm][1]->Fill(blmint[iblm]);
                hct_17315[1]->Fill(ct[4]);
            }
            Si01_vs_blm15_17315->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17315->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17315->Fill(blmint[50],blmint[51]);
        }
        //mabiki=26/32 short 39 is aborted
        if(nurun==730044 && ((midas_event>=35 && midas_event<=38) || (midas_event>=44 && midas_event<=50))){ cout<<"RUN "<<nurun<<" item #3 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17315[iblm][2]->Fill(blmint[iblm]);
                hct_17315[2]->Fill(ct[4]);
            }
            Si01_vs_blm15_17315->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17315->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17315->Fill(blmint[50],blmint[51]);
        }
        //mabiki=22/32
        if(nurun==730044 && (midas_event>=51 && midas_event<=61)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17315[iblm][3]->Fill(blmint[iblm]);
                hct_17315[3]->Fill(ct[4]);
            }
            Si01_vs_blm15_17315->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17315->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17315->Fill(blmint[50],blmint[51]);
        }
        
        
    }//end for
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170213
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
    
    //get mean and RMS for SSEM out
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
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for new pos. of BLM15
    for (Int_t iblm=0; iblm<NBLM; ++iblm) {
        meanADC_blm15new[iblm] = hdata_blm15new[iblm]->GetMean();
        rmsADC_blm15new[iblm] = hdata_blm15new[iblm]->GetRMS();
        
        meanADCout_blm15new[iblm] = hdata_out_blm15new[iblm]->GetMean();
        rmsADCout_blm15new[iblm] = hdata_out_blm15new[iblm]->GetRMS();
    }
    
    
    gr_blm15new = new TGraphErrors(NBLM,xBLM,meanADC_blm15new,xerrBLM,rmsADC_blm15new);
    grout_blm15new = new TGraphErrors(NBLM,xBLM,meanADCout_blm15new,xerrBLM,rmsADCout_blm15new);
    gr_blm15new->Write("gr_blm15new");
    grout_blm15new->Write("grout_blm15new");
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170213
    for(int j=0; j<NTEST17310; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17310[j][iblm] = hdata_17310[iblm][j]->GetMean();
            rmsADC_17310[j][iblm] = hdata_17310[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17310; j++){
        gr_17310[j] = new TGraphErrors(NBLM,xBLM,meanADC_17310[j],xerrBLM,rmsADC_17310[j]);
        gr_17310[j]->Write(Form("grtest_17310%d",j));
    }
    
    
    //////////////////////////////////////////////////////////////////////////
    
    for (Int_t iblm=0; iblm<NBLM; ++iblm) {
        meanADC_ssem19out[iblm] = hdata_ssem19out[iblm]->GetMean();
        rmsADC_ssem19out[iblm] = hdata_ssem19out[iblm]->GetRMS();
        
        meanADCout_ssem19out[iblm] = hdata_out_ssem19out[iblm]->GetMean();
        rmsADCout_ssem19out[iblm] = hdata_out_ssem19out[iblm]->GetRMS();
    }
    
    
    gr_ssem19out = new TGraphErrors(NBLM,xBLM,meanADC_ssem19out,xerrBLM,rmsADC_ssem19out);
    grout_ssem19out = new TGraphErrors(NBLM,xBLM,meanADCout_ssem19out,xerrBLM,rmsADCout_ssem19out);
    gr_ssem19out->Write("gr_ssem19out");
    grout_ssem19out->Write("grout_ssem19out");
    //////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170213
    for(int j=0; j<NTEST17315; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17315[j][iblm] = hdata_17315[iblm][j]->GetMean();
            rmsADC_17315[j][iblm] = hdata_17315[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17315; j++){
        gr_17315[j] = new TGraphErrors(NBLM,xBLM,meanADC_17315[j],xerrBLM,rmsADC_17315[j]);
        gr_17315[j]->Write(Form("grtest_17315%d",j));
    }
    
    
    Si01_vs_blm01->Write("Si01_vs_blm01");
    Si02_vs_blm16->Write("Si02_vs_blm16");
    Si01_vs_blm15_17315->Write("Si01_vs_blm15_17315");
    Si02_vs_blm15_17315->Write("Si02_vs_blm15_17315");
    Si01_vs_si02_17315->Write("Si01_vs_si02_17315");
    
    //Write output
    popfile->Write();
    popfile->Close();
    
}

void hAnaBeamMe::BeamScan20170324(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 24 run 73044
    /***********************************/
    const Int_t NTEST17324 = 4;
    //correlation
    TH2F* Si01_vs_blm15_17324 = new TH2F("Si01_vs_blm15_17324","",600,50,200,800,200,400);
    TH2F* Si02_vs_blm15_17324 = new TH2F("Si02_vs_blm15_17324","",600,50,200,800,200,400);
    TH2F* Si01_vs_si02_17324 = new TH2F("Si01_vs_si02_17324","",600,50,200,600,50,200);
    
    //SSEM in
    TGraphErrors *gr_17324[NTEST17324];
    Double_t meanADC_17324[NTEST17324][NBLM];
    Double_t rmsADC_17324[NTEST17324][NBLM];
    TH1F* hdata_17324[NBLM][NTEST17324];
    TH1F* hct_17324[NTEST17324];
    
    for(int j=0; j<NTEST17324; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17324[i][j] = new TH1F(Form("hdata17324_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17324[j] = new TH1F(Form("hct17324_sam%d",j),"",5000,2.5e12,2.525e14);
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
        //////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 15
        //mabiki=30/32
        if(nurun==730091 && (midas_event>=13 && midas_event<=63)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17324[iblm][0]->Fill(blmint[iblm]);
                hct_17324[0]->Fill(ct[4]);
            }
            Si01_vs_blm15_17324->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17324->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17324->Fill(blmint[50],blmint[51]);
        }
        //mabiki=28/32
        if(nurun==730093 && (midas_event>=16 && midas_event<=26)){ cout<<"RUN "<<nurun<<" item #2 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17324[iblm][1]->Fill(blmint[iblm]);
                hct_17324[1]->Fill(ct[4]);
            }
            Si01_vs_blm15_17324->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17324->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17324->Fill(blmint[50],blmint[51]);
        }
        //mabiki=26/32 short 39 is aborted
        if(nurun==730093 && (midas_event>=27 && midas_event<=37)){ cout<<"RUN "<<nurun<<" item #3 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17324[iblm][2]->Fill(blmint[iblm]);
                hct_17324[2]->Fill(ct[4]);
            }
            Si01_vs_blm15_17324->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17324->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17324->Fill(blmint[50],blmint[51]);
        }
        //mabiki=22/32
        if(nurun==730093 && (midas_event>=38 && midas_event<=48)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17324[iblm][3]->Fill(blmint[iblm]);
                hct_17324[3]->Fill(ct[4]);
            }
            Si01_vs_blm15_17324->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17324->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17324->Fill(blmint[50],blmint[51]);
        }
        
        
    }//end for
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170324
    for(int j=0; j<NTEST17324; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17324[j][iblm] = hdata_17324[iblm][j]->GetMean();
            rmsADC_17324[j][iblm] = hdata_17324[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17324; j++){
        gr_17324[j] = new TGraphErrors(NBLM,xBLM,meanADC_17324[j],xerrBLM,rmsADC_17324[j]);
        gr_17324[j]->Write(Form("grtest_17324%d",j));
    }
    
    
    Si01_vs_blm15_17324->Write("Si01_vs_blm15_17324");
    Si02_vs_blm15_17324->Write("Si02_vs_blm15_17324");
    Si01_vs_si02_17324->Write("Si01_vs_si02_17324");
    
    //Write output
    popfile->Write();
    popfile->Close();
    
}
void hAnaBeamMe::BeamScan20170331(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 24 run 73044
    /***********************************/
    const Int_t NTEST17331 = 4;
    //correlation
    TH2F* Si01_vs_blm15_17331 = new TH2F("Si01_vs_blm15_17331","",600,50,200,800,200,400);
    TH2F* Si02_vs_blm15_17331 = new TH2F("Si02_vs_blm15_17331","",600,50,200,800,200,400);
    TH2F* Si01_vs_si02_17331 = new TH2F("Si01_vs_si02_17331","",600,50,200,600,50,200);
    
    //SSEM in
    TGraphErrors *gr_17331[NTEST17331];
    Double_t meanADC_17331[NTEST17331][NBLM];
    Double_t rmsADC_17331[NTEST17331][NBLM];
    TH1F* hdata_17331[NBLM][NTEST17331];
    TH1F* hct_17331[NTEST17331];
    
    for(int j=0; j<NTEST17331; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17331[i][j] = new TH1F(Form("hdata17331_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17331[j] = new TH1F(Form("hct17331_sam%d",j),"",5000,2.5e12,2.525e14);
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
        //////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 15
        //mabiki=28/32
        if(nurun==740006 && (midas_event>=12 && midas_event<=22)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17331[iblm][0]->Fill(blmint[iblm]);
                hct_17331[0]->Fill(ct[4]);
            }
            Si01_vs_blm15_17331->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17331->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17331->Fill(blmint[50],blmint[51]);
        }
        //mabiki=24/32
        if(nurun==740006 && (midas_event>=23 && midas_event<=33)){ cout<<"RUN "<<nurun<<" item #2 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17331[iblm][1]->Fill(blmint[iblm]);
                hct_17331[1]->Fill(ct[4]);
            }
            Si01_vs_blm15_17331->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17331->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17331->Fill(blmint[50],blmint[51]);
        }
        //mabiki=20/32
        if(nurun==740006 && (midas_event>=34 && midas_event<=44)){ cout<<"RUN "<<nurun<<" item #3 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17331[iblm][2]->Fill(blmint[iblm]);
                hct_17331[2]->Fill(ct[4]);
            }
            Si01_vs_blm15_17331->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17331->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17331->Fill(blmint[50],blmint[51]);
        }
        //mabiki=16/32
        if(nurun==740006 && (midas_event>=45 && midas_event<=55)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17331[iblm][3]->Fill(blmint[iblm]);
                hct_17331[3]->Fill(ct[4]);
            }
            Si01_vs_blm15_17331->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17331->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17331->Fill(blmint[50],blmint[51]);
        }
        
        
    }//end for
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170324
    for(int j=0; j<NTEST17331; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17331[j][iblm] = hdata_17331[iblm][j]->GetMean();
            rmsADC_17331[j][iblm] = hdata_17331[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17331; j++){
        gr_17331[j] = new TGraphErrors(NBLM,xBLM,meanADC_17331[j],xerrBLM,rmsADC_17331[j]);
        gr_17331[j]->Write(Form("grtest_17331%d",j));
    }
    
    
    Si01_vs_blm15_17331->Write("Si01_vs_blm15_17331");
    Si02_vs_blm15_17331->Write("Si02_vs_blm15_17331");
    Si01_vs_si02_17331->Write("Si01_vs_si02_17331");
    
    //Write output
    popfile->Write();
    popfile->Close();
    
}
void hAnaBeamMe::BeamScan20170406(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 24 run 73044
    /***********************************/
    const Int_t NTEST17406 = 1;
    //correlation
    TH2F* Si01_vs_blm15_17406 = new TH2F("Si01_vs_blm15_17406","",600,50,200,800,200,400);
    TH2F* Si02_vs_blm15_17406 = new TH2F("Si02_vs_blm15_17406","",600,50,200,800,200,400);
    TH2F* Si01_vs_si02_17406 = new TH2F("Si01_vs_si02_17406","",600,50,200,600,50,200);
    
    //SSEM in
    TGraphErrors *gr_17406[NTEST17406];
    Double_t meanADC_17406[NTEST17406][NBLM];
    Double_t rmsADC_17406[NTEST17406][NBLM];
    TH1F* hdata_17406[NBLM][NTEST17406];
    TH1F* hct_17406[NTEST17406];
    
    for(int j=0; j<NTEST17406; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17406[i][j] = new TH1F(Form("hdata17406_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17406[j] = new TH1F(Form("hct17406_sam%d",j),"",5000,2.5e12,2.525e14);
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
        //////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 15
        //mabiki=28/32
        if(nurun==740026 && (midas_event>=41 && midas_event<=91)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17406[iblm][0]->Fill(blmint[iblm]);
                hct_17406[0]->Fill(ct[4]);
            }
            Si01_vs_blm15_17406->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17406->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17406->Fill(blmint[50],blmint[51]);
        }
        
        
    }//end for
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170324
    for(int j=0; j<NTEST17406; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17406[j][iblm] = hdata_17406[iblm][j]->GetMean();
            rmsADC_17406[j][iblm] = hdata_17406[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17406; j++){
        gr_17406[j] = new TGraphErrors(NBLM,xBLM,meanADC_17406[j],xerrBLM,rmsADC_17406[j]);
        gr_17406[j]->Write(Form("grtest_17406%d",j));
    }
    
    
    Si01_vs_blm15_17406->Write("Si01_vs_blm15_17406");
    Si02_vs_blm15_17406->Write("Si02_vs_blm15_17406");
    Si01_vs_si02_17406->Write("Si01_vs_si02_17406");
    
    //Write output
    popfile->Write();
    popfile->Close();
    
}
void hAnaBeamMe::BeamScan20170411(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 24 run 73044
    /***********************************/
    const Int_t NTEST17411 = 4;
    //correlation
    TH2F* Si01_vs_blm15_17411 = new TH2F("Si01_vs_blm15_17411","",600,50,200,800,200,400);
    TH2F* Si02_vs_blm15_17411 = new TH2F("Si02_vs_blm15_17411","",600,50,200,800,200,400);
    TH2F* Si01_vs_si02_17411 = new TH2F("Si01_vs_si02_17411","",600,50,200,600,50,200);
    
    //SSEM in
    TGraphErrors *gr_17411[NTEST17411];
    Double_t meanADC_17411[NTEST17411][NBLM];
    Double_t rmsADC_17411[NTEST17411][NBLM];
    TH1F* hdata_17411[NBLM][NTEST17411];
    TH1F* hct_17411[NTEST17411];
    
    for(int j=0; j<NTEST17411; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17411[i][j] = new TH1F(Form("hdata17411_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17411[j] = new TH1F(Form("hct17411_sam%d",j),"",5000,2.5e12,2.525e14);
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
        //////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 15
        //mabiki=30/32
        if(nurun==740052 && (midas_event>=13 && midas_event<=63)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17411[iblm][0]->Fill(blmint[iblm]);
                hct_17411[0]->Fill(ct[4]);
            }
            Si01_vs_blm15_17411->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17411->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17411->Fill(blmint[50],blmint[51]);
        }
        //mabiki=28/32
        if(nurun==740053 && (midas_event>=41 && midas_event<=51)){ cout<<"RUN "<<nurun<<" item #2 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17411[iblm][1]->Fill(blmint[iblm]);
                hct_17411[1]->Fill(ct[4]);
            }
            Si01_vs_blm15_17411->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17411->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17411->Fill(blmint[50],blmint[51]);
        }
        //mabiki=26/32 short 39 is aborted
        if(nurun==740053 && (midas_event>=52 && midas_event<=62)){ cout<<"RUN "<<nurun<<" item #3 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17411[iblm][2]->Fill(blmint[iblm]);
                hct_17411[2]->Fill(ct[4]);
            }
            Si01_vs_blm15_17411->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17411->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17411->Fill(blmint[50],blmint[51]);
        }
        //mabiki=22/32
        if(nurun==740053 && (midas_event>=63 && midas_event<=73)){ cout<<"RUN "<<nurun<<" item #4 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17411[iblm][3]->Fill(blmint[iblm]);
                hct_17411[3]->Fill(ct[4]);
            }
            Si01_vs_blm15_17411->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17411->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17411->Fill(blmint[50],blmint[51]);
        }
        
        
    }//end for
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170411
    for(int j=0; j<NTEST17411; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17411[j][iblm] = hdata_17411[iblm][j]->GetMean();
            rmsADC_17411[j][iblm] = hdata_17411[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17411; j++){
        gr_17411[j] = new TGraphErrors(NBLM,xBLM,meanADC_17411[j],xerrBLM,rmsADC_17411[j]);
        gr_17411[j]->Write(Form("grtest_17411%d",j));
    }
    
    
    Si01_vs_blm15_17411->Write("Si01_vs_blm15_17411");
    Si02_vs_blm15_17411->Write("Si02_vs_blm15_17411");
    Si01_vs_si02_17411->Write("Si01_vs_si02_17411");
    
    //Write output
    popfile->Write();
    popfile->Close();
}
void hAnaBeamMe::BeamScan20170411newcircuit(TString opFile)
{
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NBLM = 52;
    Double_t xBLM[NBLM];
    Double_t xerrBLM[NBLM];
    for(int i=0; i<NBLM; i++){
        xBLM[i] = i+1;
        xerrBLM[i]=0.25;
    }
    
    
    
    /***********************************/
    //for Beam intensity on 2017 Mar. 24 run 73044
    /***********************************/
    const Int_t NTEST17411newci = 1;
    //correlation
    TH2F* Si01_vs_blm15_17411newci = new TH2F("Si01_vs_blm15_17411newci","",600,50,200,800,200,400);
    TH2F* Si02_vs_blm15_17411newci = new TH2F("Si02_vs_blm15_17411newci","",600,50,200,800,200,400);
    TH2F* Si01_vs_si02_17411newci = new TH2F("Si01_vs_si02_17411newci","",600,50,200,600,50,200);
    
    //SSEM in
    TGraphErrors *gr_17411newci[NTEST17411newci];
    Double_t meanADC_17411newci[NTEST17411newci][NBLM];
    Double_t rmsADC_17411newci[NTEST17411newci][NBLM];
    TH1F* hdata_17411newci[NBLM][NTEST17411newci];
    TH1F* hct_17411newci[NTEST17411newci];
    
    for(int j=0; j<NTEST17411newci; j++){
        for(int i=0; i<NBLM; i++){
            hdata_17411newci[i][j] = new TH1F(Form("hdata17411newci_blm%d_sam%d",i,j),"",3000,0,1500);
        }
        hct_17411newci[j] = new TH1F(Form("hct17411newci_sam%d",j),"",5000,2.5e12,2.525e14);
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
        //////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        //for intensity scan on Mar. 15
        //mabiki=28/32
        if(nurun==740053 && (midas_event>=30 && midas_event<=39)){ cout<<"RUN "<<nurun<<" item #1 CT "<<ct[4]<<" BLM1 "<<blmint[0]<<" BLM16 "<<blmint[15]<<endl;
            for (Int_t iblm=0; iblm<NBLM; ++iblm) {
                hdata_17411newci[iblm][0]->Fill(blmint[iblm]);
                hct_17411newci[0]->Fill(ct[4]);
            }
            Si01_vs_blm15_17411newci->Fill(blmint[50],blmint[14]);
            Si02_vs_blm15_17411newci->Fill(blmint[51],blmint[14]);
            Si01_vs_si02_17411newci->Fill(blmint[50],blmint[51]);
        }
        
        
    }//end for
    
    
    //////////////////////////////////////////////////////////////////////////
    //get mean and RMS for SSEM in Scan 20170324
    for(int j=0; j<NTEST17411newci; j++){
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            meanADC_17411newci[j][iblm] = hdata_17411newci[iblm][j]->GetMean();
            rmsADC_17411newci[j][iblm] = hdata_17411newci[iblm][j]->GetRMS();
        }
    }
    for(int j=0; j<NTEST17411newci; j++){
        gr_17411newci[j] = new TGraphErrors(NBLM,xBLM,meanADC_17411newci[j],xerrBLM,rmsADC_17411newci[j]);
        gr_17411newci[j]->Write(Form("grtest_17411newci%d",j));
    }
    
    
    Si01_vs_blm15_17411newci->Write("Si01_vs_blm15_17411newci");
    Si02_vs_blm15_17411newci->Write("Si02_vs_blm15_17411newci");
    Si01_vs_si02_17411newci->Write("Si01_vs_si02_17411newci");
    
    //Write output
    popfile->Write();
    popfile->Close();
    
}
