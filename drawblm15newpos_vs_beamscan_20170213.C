void drawblm15newpos_vs_beamscan_20170213(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
TString subname="blm15newpos";
TFile *pfile = new TFile("blm15newpos_vs_beamscan_20170213.root");
new TCanvas;
const Int_t NTEST = 9;
const Int_t NBLM = 52;
char* atitle[NBLM]={
"BLM01@up-PV1","BLM02@down-PV1","BLM03@down-PH2","BLM04@MR-PQ2","BLM05@aisle-PQ2","BLM06@down-PQ2","BLM07@down-PD1","BLM08@down-PD2-right","BLM09@down-PD2-left","BLM10@down-PC1",
"BLM11@up-PQ3","BLM12@down-PQ3","BLM13@up-PV2","BLM14@down-PV2","BLM15@down-PQ4","BLM16@down-PC4-right","BLM17@down-PC4-left","BLM18@down-PH3","BLM19@down-PQ5","BLM20@middle-SC01",
"BLM21@down-SC01", "BLM22@middle-SC02","BLM23@down-SC02","BLM24@middle-SC03","BLM25@down-SC03","BLM26@middle-SC04","BLM27@down-SC04","BLM28@middle-SC05","BLM29@down-SC05","BLM30@middle-SC06",
"BLM31@down-SC06","BLM32@middle-SC07","BLM33@down-SC07","BLM34@down-SC08","BLM35@down-SC09","BLM36@down-SC010","BLM37@down-SC11","BLM38@down-SC12","BLM39@down-SC13","BLM40@down-SC14",
"BLM41@down-FQ1","BLM42@down-FV1","BLM43@down-FH1","BLM44@down-FV2","BLM45@down-FQ2","BLM46@down-FQ3","BLM47@down-FH2","BLM48@down-FVD1","BLM49@down-FQ4","BLM50@down-FVD2","Si 1@BLM01","Si 2@BLM16"
};

TGraphErrors *gr[NTEST];
for(int j=0; j<NTEST; j++){
 gr[j]= (TGraphErrors*)pfile->Get(Form("grtest_%d",j));
}


const Int_t OUTNTEST = 9;
TGraphErrors *grout[OUTNTEST];
for(int j=0; j<OUTNTEST; j++){
 grout[j]= (TGraphErrors*)pfile->Get(Form("grouttest_%d",j));
}

TGraphErrors *gr_blm15new = (TGraphErrors*)pfile->Get("gr_blm15new");
TGraphErrors *grout_blm15new = (TGraphErrors*)pfile->Get("grout_blm15new");

TGraphErrors *gr2fit[NBLM];
TGraphErrors *gr2fitout[NBLM];
TGraphErrors *gr2fit4point[NBLM];

TH1F* hct[NTEST];
double ctmean[NTEST];
double ctrms[NTEST];

TH1F* hctout[OUTNTEST];
double ctmeanout[OUTNTEST];
double ctrmsout[OUTNTEST];


for(int j=0; j<NTEST; j++){
int jsort = j;
        if(j==3) jsort=0;
        if(j==2) jsort=1;
        if(j==1) jsort=2;
        if(j==0) jsort=3;
hct[j] = (TH1F*)pfile->Get(Form("hct_sam%d",j));
ctmean[jsort] = hct[j]->GetMean()*1e-12;
ctrms[jsort] = hct[j]->GetRMS()*1e-12;
}

for(int j=0; j<OUTNTEST; j++){
int jsort = j;
hctout[j] = (TH1F*)pfile->Get(Form("houtct_sam%d",j));
ctmeanout[jsort] = hctout[j]->GetMean()*1e-12;
ctrmsout[jsort] = hctout[j]->GetRMS()*1e-12;
}

TH1F* hct_blm15new = (TH1F*)pfile->Get("hct_blm15new");
TH1F* hct_out_blm15new = (TH1F*)pfile->Get("hct_out_blm15new");
double ctmean_blm15new[1]; ctmean_blm15new[0] = hct_blm15new->GetMean()*1e-12;
double ctrms_blm15new[1]; ctrms_blm15new[0]= hct_blm15new->GetRMS()*1e-12;
double ctmeanout_blm15new[1]; ctmeanout_blm15new[0]= hct_out_blm15new->GetMean()*1e-12;
double ctrmsout_blm15new[1]; ctrmsout_blm15new[0]= hct_out_blm15new->GetRMS()*1e-12;

double adcmean_blm15new[NBLM][1];
double adcrms_blm15new[NBLM][1];
double adcmeanout_blm15new[NBLM][1];
double adcrmsout_blm15new[NBLM][1];
double blmindex_new[NBLM];

for(Int_t iblm=0; iblm<NBLM; ++iblm){
	 gr_blm15new->GetPoint(iblm,blmindex_new[iblm],adcmean_blm15new[iblm][0]);
	adcrms_blm15new[iblm][0] = gr_blm15new->GetErrorY(iblm); 
	cout<<"iblm "<<iblm<<" mean "<<adcmean_blm15new[iblm][0]<<endl;
 	grout_blm15new->GetPoint(iblm,blmindex_new[iblm],adcmeanout_blm15new[iblm][0]);
	adcrmsout_blm15new[iblm][0] = grout_blm15new->GetErrorY(iblm);
}

TGraphErrors *grOne_blm15new[NBLM];
TGraphErrors *grOneout_blm15new[NBLM];

double adcmean[NBLM][NTEST];
double blmindex[NBLM];
double adcrms[NBLM][NTEST];

//3 is with full density, then 2,1,0, then 4
for(int j=0; j<NTEST; j++){
 	int jsort = j;
	if(j==3) jsort=0;
	if(j==2) jsort=1;
	if(j==1) jsort=2;
	if(j==0) jsort=3; 
	for (Int_t iblm=0; iblm<NBLM; ++iblm) {
	gr[j]->GetPoint(iblm,blmindex[iblm],adcmean[iblm][jsort]);
	adcrms[iblm][jsort] = gr[j]->GetErrorY(iblm);
	}
}
for(Int_t iblm=0; iblm<NBLM; ++iblm){
gr2fit[iblm] = new TGraphErrors(NTEST,ctmean,adcmean[iblm],ctrms,adcrms[iblm]);
new TCanvas;
gStyle->SetOptFit();
gr2fit[iblm]->Draw("APL");
gr2fit[iblm]->GetXaxis()->SetLimits(0,250);//newadd
gr2fit[iblm]->SetMinimum(0);
titleStyle(gr2fit[iblm]);
gr2fit[iblm]->GetXaxis()->SetTitle("CT intensity [x 10^{12}]");
gr2fit[iblm]->GetYaxis()->SetTitle("Integrated ADC");
gr2fit[iblm]->Fit("pol1");
gPad->Update();
TPaveStats *st = (TPaveStats*)gr2fit[iblm]->GetListOfFunctions()->FindObject("stats");
    st->SetX1NDC(0.2);
    st->SetX2NDC(0.4);
double yleg = TMath::MinElement(NTEST,gr2fit[iblm]->GetY()) + (TMath::MaxElement(NTEST,gr2fit[iblm]->GetY()) - TMath::MinElement(NTEST,gr2fit[iblm]->GetY()))*0.36/2;
TText t1(150,yleg,atitle[iblm]);
 t1.SetTextSize(0.06);
 t1.SetTextColor(1);
 t1.Draw();
grOne_blm15new[iblm]  = new TGraphErrors(1,ctmean_blm15new,adcmean_blm15new[iblm],ctrms_blm15new,adcrms_blm15new[iblm]);
grOne_blm15new[iblm]->SetMarkerStyle(8);
  grOne_blm15new[iblm]->SetMarkerColor(4);
grOne_blm15new[iblm]->Draw("p same");
gPad->Modified();
gPad->Print("plots/"+subname+Form("_vsCT_blm%d.eps",iblm+1));
}
////////////////////////////////////////
/////////////Fit graph w/ SSEM out
const Int_t NTESTSH = 4;
    double adcmeanout[NBLM][NTESTSH];
    double blmindex[NBLM];
    double adcrmsout[NBLM][NTESTSH];
    for(int j=0; j<NTESTSH; j++){
        int jsort = j;
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            grout[j]->GetPoint(iblm,blmindex[iblm],adcmeanout[iblm][jsort]);
            adcrmsout[iblm][jsort] = grout[j]->GetErrorY(iblm);
        }
    }
    for(Int_t iblm=0; iblm<NBLM; ++iblm){
        gr2fitout[iblm] = new TGraphErrors(NTESTSH,ctmeanout,adcmeanout[iblm],ctrmsout,adcrmsout[iblm]);
        new TCanvas;
        gStyle->SetOptFit();
        gr2fitout[iblm]->Draw("APL");
       gr2fitout[iblm]->GetXaxis()->SetLimits(0,250);//newadd
       gr2fitout[iblm]->SetMinimum(0);
	 titleStyle(gr2fitout[iblm]);
        gr2fitout[iblm]->GetXaxis()->SetTitle("CT intensity [x 10^{12}]");
        gr2fitout[iblm]->GetYaxis()->SetTitle("Integrated ADC");
        gr2fitout[iblm]->Fit("pol1");
        gPad->Update();
        TPaveStats *st = (TPaveStats*)gr2fitout[iblm]->GetListOfFunctions()->FindObject("stats");
        st->SetX1NDC(0.2);
        st->SetX2NDC(0.4);
        double yleg =  TMath::MinElement(NTESTSH,gr2fitout[iblm]->GetY()) + (TMath::MaxElement(NTESTSH,gr2fitout[iblm]->GetY()) - TMath::MinElement(NTESTSH,gr2fitout[iblm]->GetY()))*0.36/2;
        TText t1(150,yleg,atitle[iblm]);
        t1.SetTextSize(0.06);
        t1.SetTextColor(1);
        t1.Draw();

	grOneout_blm15new[iblm]  = new TGraphErrors(1,ctmeanout_blm15new,adcmeanout_blm15new[iblm],ctrmsout_blm15new,adcrmsout_blm15new[iblm]);
grOneout_blm15new[iblm]->SetMarkerStyle(8);
  grOneout_blm15new[iblm]->SetMarkerColor(4);
grOneout_blm15new[iblm]->Draw("p same");
        
        gPad->Modified();
        gPad->Print("plots/"+subname+Form("_ssemout_vsCT_blm%d.eps",iblm+1));
    }

}
