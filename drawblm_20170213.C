void drawblm_20170213(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
Int_t run2plot = 720123;
TString subname="study_20170213";
TFile *pfile = new TFile("beamstudy_20170213.root");
new TCanvas;
const Int_t NTEST = 9;
const Int_t NBLM = 50;
char* atitle[50]={
"BLM01@up-PV1","BLM02@down-PV1","BLM03@down-PH2","BLM04@MR-PQ2","BLM05@aisle-PQ2","BLM06@down-PQ2","BLM07@down-PD1","BLM08@down-PD2-right","BLM09@down-PD2-left","BLM10@down-PC1",
"BLM11@up-PQ3","BLM12@down-PQ3","BLM13@up-PV2","BLM14@down-PV2","BLM15@down-PQ4","BLM16@down-PC4-right","BLM17@down-PC4-left","BLM18@down-PH3","BLM19@down-PQ5","BLM20@middle-SC01",
"BLM21@down-SC01", "BLM22@middle-SC02","BLM23@down-SC02","BLM24@middle-SC03","BLM25@down-SC03","BLM26@middle-SC04","BLM27@down-SC04","BLM28@middle-SC05","BLM29@down-SC05","BLM30@middle-SC06",
"BLM31@down-SC06","BLM32@middle-SC07","BLM33@down-SC07","BLM34@down-SC08","BLM35@down-SC09","BLM36@down-SC010","BLM37@down-SC11","BLM38@down-SC12","BLM39@down-SC13","BLM40@down-SC14",
"BLM41@down-FQ1","BLM42@down-FV1","BLM43@down-FH1","BLM44@down-FV2","BLM45@down-FQ2","BLM46@down-FQ3","BLM47@down-FH2","BLM48@down-FVD1","BLM49@down-FQ4","BLM50@down-FVD2"
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

TGraphErrors *gr2fit[NBLM];
TGraphErrors *gr2fitout[NBLM];

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
 //gStyle->SetOptStat(1);
gStyle->SetOptFit();
gr2fit[iblm]->Draw("APL");
titleStyle(gr2fit[iblm]);
gr2fit[iblm]->GetXaxis()->SetTitle("CT intensity [x 10^{12}]");
gr2fit[iblm]->GetYaxis()->SetTitle("Integrated ADC");
//gr2fit[iblm]->GetXaxis()->SetRangeUser(0,300);
gr2fit[iblm]->Fit("pol1");
//gr2fit[iblm]->GetXaxis()->SetLimits(0,300);
gPad->Update();
TPaveStats *st = (TPaveStats*)gr2fit[iblm]->GetListOfFunctions()->FindObject("stats");
    st->SetX1NDC(0.2);
    st->SetX2NDC(0.4);
double yleg = (TMath::MaxElement(NTEST,gr2fit[iblm]->GetY()) + TMath::MinElement(NTEST,gr2fit[iblm]->GetY()))*0.8/2;
TText t1(150,yleg,atitle[iblm]);
 t1.SetTextSize(0.06);
 t1.SetTextColor(1);
 t1.Draw();

gPad->Modified();
gPad->Print("plots/"+subname+Form("_vsCT_blm%d.eps",iblm+1));
}


      char *colorRun[]= {
   "#000000",
   "#0072B2",
   "#D55E00",
   "#CC79A7",
   "#E69F00",
   "#009E73",
   "#56B4E9",
   "#F0E442",
   "#FF0080",
   "#8000FF"
   };
Int_t ci;
TLegend* leg0 = new TLegend(.45, .65, 0.65, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.037);
gPad->SetLogy();
gr[3]->Draw("APL");
gr[3]->GetXaxis()->SetTitle("BLM index");
gr[3]->GetYaxis()->SetTitle("Integrated ADC");
leg0->AddEntry(gr[3],Form("CT %.3f #pm %.3f  x e12",ctmean[0],ctrms[0]),"pl");//sort intense
titleStyle(gr[3]);
gr[3]->GetYaxis()->SetRangeUser(1,3000);

for(int j=2; j>=0; j--){
ci = TColor::GetColor(colorRun[j+1]);
gr[j]->SetLineColor(ci);
gr[j]->SetMarkerColor(ci);
gr[j]->Draw("PL same");
leg0->AddEntry(gr[j],Form("CT %.3f #pm %.3f x e12",ctmean[3-j],ctrms[3-j]),"pl");
}

for(int j=4; j<NTEST; j++){
ci = TColor::GetColor(colorRun[j+1]);
gr[j]->SetLineColor(ci);
gr[j]->SetMarkerColor(ci);
gr[j]->Draw("PL same");
leg0->AddEntry(gr[j],Form("CT %.3f #pm %.3f x e12",ctmean[j],ctrms[j]),"pl");
}

leg0->Draw("same");
gPad->Print("plots/"+subname+"allBLM_4intense.eps");
gPad->Print("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/"+subname+"allBLM_4intense.eps");


//SSEM out
new TCanvas;
TLegend* leg1 = new TLegend(.45, .65, 0.65, .9);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.037);
gPad->SetLogy();
grout[0]->Draw("APL");
    grout[0]->GetXaxis()->SetTitle("BLM index");
    grout[0]->GetYaxis()->SetTitle("Integrated ADC");
    leg1->AddEntry(grout[0],Form("CT %.3f #pm %.3f  x e12",ctmeanout[0],ctrmsout[0]),"pl");
    titleStyle(grout[0]);
    grout[0]->GetYaxis()->SetRangeUser(1,3000);
for(int j=1; j<4; j++){
ci = TColor::GetColor(colorRun[j]);
grout[j]->SetLineColor(ci);
grout[j]->SetMarkerColor(ci);
grout[j]->Draw("PL same");
leg1->AddEntry(grout[j],Form("CT %.3f #pm %.3f  x e12",ctmeanout[j],ctrmsout[j]),"pl");
}
leg1->Draw("same");
gPad->Print("plots/"+subname+"allBLM_4intense_ssemout.eps");
gPad->Print("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/"+subname+"allBLM_4intense_ssemout.eps");

}
