#define hOrbitAna_cxx
#include "hOrbitAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
void hOrbitAna::MakeBasicPlot(TString ipFile, TString opFile){
    //Re initialization ipFile
    /////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    //for BLM blmint[50];
    //   Double_t        blmadc[50][450];
    const int NBLM = 50;
    TH1F* hblm_int[NBLM];
    //TH2F* hblm_corNN1[NBLM];
    for(int i=0; i<NBLM; i++){
        hblm_int[i] = new TH1F(Form("hblm_int_n%d",i),"",500,0,1000);
       // if(i<NBLM-2)hblm_corNN1[i] = new TH2F(Form("hblm_corNN1%d",i),"",1000,0,2000,1000,0,2000);
       // else hblm_corNN1[i] = new TH2F(Form("hblm_corNN1%d",i),"",100,0,0.05,1000,0,2000);
    }
    
     //for ESM
     const int NESM=21;
     TH1F* hesm[NESM][4];//x y ex ey


    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"total "<<nentries<<" iprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        if (jentry%iprintProcess == 0) std::cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<std::endl;
        for(int i=0; i<NBLM; i++){
            hblm_int[i]->Fill(blmint[i]);
        }
    }
    
    popfile->Write();
    popfile->Close();
}
void hOrbitAna::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
