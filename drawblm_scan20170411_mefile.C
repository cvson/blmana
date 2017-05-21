void drawblm_scan20170411_mefile(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    TString subname="beamscan_20170411";
    TFile *pfile = new TFile("beamscan_20170315.root");
    TFile *pfile17324 = new TFile("beamscan_20170324.root");
    TFile *pfile17411 = new TFile("beamscan_20170411.root");
    new TCanvas;
    
    const Int_t NBLM = 52;
    char* atitle[NBLM]={
        "BLM01@up-PV1","BLM02@down-PV1","BLM03@down-PH2","BLM04@MR-PQ2","BLM05@aisle-PQ2","BLM06@down-PQ2","BLM07@down-PD1","BLM08@down-PD2-right","BLM09@down-PD2-left","BLM10@down-PC1",
        "BLM11@up-PQ3","BLM12@down-PQ3","BLM13@up-PV2","BLM14@down-PV2","BLM15@down-PQ4","BLM16@down-PC4-right","BLM17@down-PC4-left","BLM18@down-PH3","BLM19@down-PQ5","BLM20@middle-SC01",
        "BLM21@down-SC01", "BLM22@middle-SC02","BLM23@down-SC02","BLM24@middle-SC03","BLM25@down-SC03","BLM26@middle-SC04","BLM27@down-SC04","BLM28@middle-SC05","BLM29@down-SC05","BLM30@middle-SC06",
        "BLM31@down-SC06","BLM32@middle-SC07","BLM33@down-SC07","BLM34@down-SC08","BLM35@down-SC09","BLM36@down-SC010","BLM37@down-SC11","BLM38@down-SC12","BLM39@down-SC13","BLM40@down-SC14",
        "BLM41@down-FQ1","BLM42@down-FV1","BLM43@down-FH1","BLM44@down-FV2","BLM45@down-FQ2","BLM46@down-FQ3","BLM47@down-FH2","BLM48@down-FVD1","BLM49@down-FQ4","BLM50@down-FVD2","Si 1@BLM01","Si 2@BLM16"
    };
    
    char *colorRun[]= {
        "#000000",
        "#0072B2",
        "#D55E00",
        "#CC79A7",
        "#E69F00",
        "#009E73",
        "#56B4E9",
        "#F0E442"
    };
    Int_t ci;
    /***********************************/
    //scan 20170213
    const Int_t NTEST = 9;
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
    /***********************************/
    //scan 20170310
    const Int_t NTEST17310 = 5;
    TGraphErrors *gr_17310[NTEST17310];
    for(int j=0; j<NTEST17310; j++){
        gr_17310[j]= (TGraphErrors*)pfile->Get(Form("grtest_17310%d",j));
    }
    TGraphErrors *gr2fit_17310[NBLM];
    TH1F* hct_17310[NTEST17310];
    double ctmean_17310[NTEST17310];
    double ctrms_17310[NTEST17310];
    double adcmean_17310[NBLM][NTEST17310];
    double adcrms_17310[NBLM][NTEST17310];
    
    for(int j=0; j<NTEST17310; j++){
        
        hct_17310[j] = (TH1F*)pfile->Get(Form("hct17310_sam%d",j));
        ctmean_17310[j] = hct_17310[j]->GetMean()*1e-12;
        ctrms_17310[j] = hct_17310[j]->GetRMS()*1e-12;
        
        gr_17310[j]= (TGraphErrors*)pfile->Get(Form("grtest_17310%d",j));
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            gr_17310[j]->GetPoint(iblm,blmindex[iblm],adcmean_17310[iblm][j]);
            adcrms_17310[iblm][j] = gr_17310[j]->GetErrorY(iblm);
        }
    }
    
    /***********************************/
    //scan 20170315
    const Int_t NTEST17315 = 4;
    TGraphErrors *gr_17315[NTEST17315];
    for(int j=0; j<NTEST17315; j++){
        gr_17315[j]= (TGraphErrors*)pfile->Get(Form("grtest_17315%d",j));
    }
    TGraphErrors *gr2fit_17315[NBLM];
    TH1F* hct_17315[NTEST17315];
    double ctmean_17315[NTEST17315];
    double ctrms_17315[NTEST17315];
    double adcmean_17315[NBLM][NTEST17315];
    double adcrms_17315[NBLM][NTEST17315];
    
    for(int j=0; j<NTEST17315; j++){
        
        hct_17315[j] = (TH1F*)pfile->Get(Form("hct17315_sam%d",j));
        ctmean_17315[j] = hct_17315[j]->GetMean()*1e-12;
        ctrms_17315[j] = hct_17315[j]->GetRMS()*1e-12;
        
        gr_17315[j]= (TGraphErrors*)pfile->Get(Form("grtest_17315%d",j));
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            gr_17315[j]->GetPoint(iblm,blmindex[iblm],adcmean_17315[iblm][j]);
            adcrms_17315[iblm][j] = gr_17315[j]->GetErrorY(iblm);
        }
    }
    
    /***********************************/
    //scan 20170324
    const Int_t NTEST17324 = 4;
TGraphErrors *gr_17324[NTEST17324];
for(int j=0; j<NTEST17324; j++){
    gr_17324[j]= (TGraphErrors*)pfile17324->Get(Form("grtest_17324%d",j));
}
TGraphErrors *gr2fit_17324[NBLM];
TH1F* hct_17324[NTEST17324];
double ctmean_17324[NTEST17324];
double ctrms_17324[NTEST17324];
double adcmean_17324[NBLM][NTEST17324];
double adcrms_17324[NBLM][NTEST17324];

for(int j=0; j<NTEST17324; j++){
    
    hct_17324[j] = (TH1F*)pfile17324->Get(Form("hct17324_sam%d",j));
    ctmean_17324[j] = hct_17324[j]->GetMean()*1e-12;
    ctrms_17324[j] = hct_17324[j]->GetRMS()*1e-12;
    
    gr_17324[j]= (TGraphErrors*)pfile17324->Get(Form("grtest_17324%d",j));
    for (Int_t iblm=0; iblm<NBLM; ++iblm) {
        gr_17324[j]->GetPoint(iblm,blmindex[iblm],adcmean_17324[iblm][j]);
        adcrms_17324[iblm][j] = gr_17324[j]->GetErrorY(iblm);
    }
}
    
    /***********************************/
    //scan 20170411
    const Int_t NTEST17411 = 4;
    TGraphErrors *gr_17411[NTEST17411];
    for(int j=0; j<NTEST17411; j++){
        gr_17411[j]= (TGraphErrors*)pfile17411->Get(Form("grtest_17411%d",j));
    }
    TGraphErrors *gr2fit_17411[NBLM];
    TH1F* hct_17411[NTEST17411];
    double ctmean_17411[NTEST17411];
    double ctrms_17411[NTEST17411];
    double adcmean_17411[NBLM][NTEST17411];
    double adcrms_17411[NBLM][NTEST17411];
    
    for(int j=0; j<NTEST17411; j++){
        
        hct_17411[j] = (TH1F*)pfile17411->Get(Form("hct17411_sam%d",j));
        ctmean_17411[j] = hct_17411[j]->GetMean()*1e-12;
        ctrms_17411[j] = hct_17411[j]->GetRMS()*1e-12;
        
        gr_17411[j]= (TGraphErrors*)pfile17411->Get(Form("grtest_17411%d",j));
        for (Int_t iblm=0; iblm<NBLM; ++iblm) {
            gr_17411[j]->GetPoint(iblm,blmindex[iblm],adcmean_17411[iblm][j]);
            adcrms_17411[iblm][j] = gr_17411[j]->GetErrorY(iblm);
        }
    }

        /***********************************/
    for(Int_t iblm=0; iblm<NBLM; ++iblm){
        gr2fit[iblm] = new TGraphErrors(NTEST,ctmean,adcmean[iblm],ctrms,adcrms[iblm]);
        new TCanvas;
        gStyle->SetOptFit();
        gr2fit[iblm]->Draw("APL");
        gr2fit[iblm]->GetXaxis()->SetLimits(0,250);//newadd
        gr2fit[iblm]->SetMinimum(0);
        if(iblm>49)gr2fit[iblm]->SetMaximum(180);//for Si detector
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
        
        //scan 20170310
        gr2fit_17310[iblm] = new TGraphErrors(NTEST17310,ctmean_17310,adcmean_17310[iblm],ctrms_17310,adcrms_17310[iblm]);
        gr2fit_17310[iblm]->SetMarkerStyle(8);
        ci = TColor::GetColor(colorRun[1]);
        gr2fit_17310[iblm]->SetMarkerColor(ci);
        gr2fit_17310[iblm]->SetLineColor(ci);
        gr2fit_17310[iblm]->Draw("PL same");
        
        //scan 20170315
        gr2fit_17315[iblm] = new TGraphErrors(NTEST17315,ctmean_17315,adcmean_17315[iblm],ctrms_17315,adcrms_17315[iblm]);
        gr2fit_17315[iblm]->SetMarkerStyle(8);
        ci = TColor::GetColor(colorRun[2]);
        gr2fit_17315[iblm]->SetMarkerColor(ci);
        gr2fit_17315[iblm]->SetLineColor(ci);
        gr2fit_17315[iblm]->Draw("PL same");
       
	//scan 20170324
       gr2fit_17324[iblm] = new TGraphErrors(NTEST17324,ctmean_17324,adcmean_17324[iblm],ctrms_17324,adcrms_17324[iblm]);
gr2fit_17324[iblm]->SetMarkerStyle(8);
ci = TColor::GetColor(colorRun[3]);
gr2fit_17324[iblm]->SetMarkerColor(ci);
gr2fit_17324[iblm]->SetLineColor(ci);
gr2fit_17324[iblm]->Draw("PL same");
        
        //scan 20170411
        gr2fit_17411[iblm] = new TGraphErrors(NTEST17411,ctmean_17411,adcmean_17411[iblm],ctrms_17411,adcrms_17411[iblm]);
        gr2fit_17411[iblm]->SetMarkerStyle(8);
        ci = TColor::GetColor(colorRun[4]);
        gr2fit_17411[iblm]->SetMarkerColor(ci);
        gr2fit_17411[iblm]->SetLineColor(ci);
        gr2fit_17411[iblm]->Draw("PL same");
        
        TLegend* leg0 = new TLegend(.2, .65, 0.4, .85);
	leg0->SetFillStyle(0);
	leg0->SetBorderSize(0);
	    leg0->SetTextSize(0.045);
	leg0->AddEntry(gr2fit[iblm], "Beam scan 17.02.13", "pl");
	leg0->AddEntry(gr2fit_17310[iblm], "Beam scan 17.03.10", "pl");
    leg0->AddEntry(gr2fit_17315[iblm], "Beam scan 17.03.15", "pl");
	leg0->AddEntry(gr2fit_17324[iblm], "Beam scan 17.03.24", "pl");
     leg0->AddEntry(gr2fit_17411[iblm], "Beam scan 17.04.11", "pl");
leg0->SetFillStyle(0);
	leg0->Draw();


	gPad->Modified();
        gPad->Print("plots/"+subname+Form("_vsCT_blm%d.eps",iblm+1));
	delete leg0;
    }
    
    //compare BLM15, Si01, Si02
    double fitpara[4];
    new TCanvas;
    gStyle->SetOptFit();
    ci = TColor::GetColor(colorRun[1]);
    gr2fit_17315[50]->SetMarkerColor(ci);
    gr2fit_17315[50]->SetLineColor(ci);
    gr2fit_17315[50]->Draw("APL");
    
    gr2fit_17315[50]->GetXaxis()->SetLimits(0,250);//newadd
    gr2fit_17315[50]->SetMinimum(0);
    if(iblm>49)gr2fit_17315[50]->SetMaximum(180);//for Si detector
    titleStyle(gr2fit_17315[50]);
    gr2fit_17315[50]->GetXaxis()->SetTitle("CT intensity [x 10^{12}]");
    gr2fit_17315[50]->GetYaxis()->SetTitle("Integrated ADC");
    gr2fit_17315[50]->Fit("pol1","same",0,250);
    
    TF1 *f1 = gr2fit_17315[50]->GetListOfFunctions()->FindObject("pol1");
    f1->SetLineColor(ci);
    f1->Draw("same");
	fitpara[0] = f1->GetParameter(1);//slope
    gPad->Update();
    TPaveStats *st1 = (TPaveStats*)gr2fit_17315[50]->GetListOfFunctions()->FindObject("stats");
    st1->SetX1NDC(0.2);
    st1->SetX2NDC(0.4);
    st1->SetTextColor(ci);
    
    
    
    
    ci = TColor::GetColor(colorRun[2]);
    gr2fit_17315[51]->SetMarkerColor(ci);
    gr2fit_17315[51]->SetLineColor(ci);
    gr2fit_17315[51]->Draw("PL same");
    gr2fit_17315[51]->GetXaxis()->SetLimits(0,250);//newadd
    gr2fit_17315[51]->Fit("pol1","same",0,250);
    
    TF1 *f11 = gr2fit_17315[51]->GetListOfFunctions()->FindObject("pol1");
    f11->SetLineColor(ci);
    f11->Draw("same");
	fitpara[1] = f11->GetParameter(1);//slope
    gPad->Update();
    TPaveStats *st2 = (TPaveStats*)gr2fit_17315[51]->GetListOfFunctions()->FindObject("stats");
    st2->SetX1NDC(0.6);
    st2->SetX2NDC(0.8);
    st2->SetTextColor(ci);
   

     //new scan 20170324
ci = TColor::GetColor(colorRun[3]);
gr2fit_17324[50]->SetMarkerColor(ci);
gr2fit_17324[50]->SetLineColor(ci);
gr2fit_17324[50]->Draw("PL same");
gr2fit_17324[50]->GetXaxis()->SetLimits(0,250);//newadd
gr2fit_17324[50]->Fit("pol1","same",0,250);

TF1 *f12 = gr2fit_17324[50]->GetListOfFunctions()->FindObject("pol1");
f12->SetLineColor(ci);
f12->Draw("same");
fitpara[2] = f12->GetParameter(1);//slope
gPad->Update();
 TPaveStats *st3 = (TPaveStats*)gr2fit_17324[50]->GetListOfFunctions()->FindObject("stats");
    st3->SetX1NDC(0.2);
    st3->SetX2NDC(0.4);
    st3->SetY1NDC(0.1);
    st3->SetY2NDC(0.3);
    st3->SetTextColor(ci);

     ci = TColor::GetColor(colorRun[4]);
gr2fit_17324[51]->SetMarkerColor(ci);
gr2fit_17324[51]->SetLineColor(ci);
gr2fit_17324[51]->Draw("PL same");
gr2fit_17324[51]->GetXaxis()->SetLimits(0,250);//newadd
gr2fit_17324[51]->Fit("pol1","same",0,250);

TF1 *f13 = gr2fit_17324[51]->GetListOfFunctions()->FindObject("pol1");
f13->SetLineColor(ci);
f13->Draw("same");
	fitpara[3] = f13->GetParameter(1);//slope
gPad->Update();
 TPaveStats *st4 = (TPaveStats*)gr2fit_17324[51]->GetListOfFunctions()->FindObject("stats");
    st4->SetX1NDC(0.6);
    st4->SetX2NDC(0.8);
    st4->SetY1NDC(0.1);
    st4->SetY2NDC(0.3);
    st4->SetTextColor(ci);

    //new scan 20170411
    ci = TColor::GetColor(colorRun[5]);
    gr2fit_17411[50]->SetMarkerColor(ci);
    gr2fit_17411[50]->SetLineColor(ci);
    gr2fit_17411[50]->Draw("PL same");
    
    
    
    ci = TColor::GetColor(colorRun[6]);
    gr2fit_17411[51]->SetMarkerColor(ci);
    gr2fit_17411[51]->SetLineColor(ci);
    gr2fit_17411[51]->Draw("PL same");

 
    gPad->Update();
    
    TLegend* leg0 = new TLegend(.2, .65, 0.4, .85);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(35);
    //leg0->SetTextSize(0.045);
    leg0->AddEntry(gr2fit_17315[50], "Si 01 (~20cm), Mar.15", "pl");
    leg0->AddEntry(gr2fit_17315[51], "Si 02 (~20cm), Mar.15", "pl");
    leg0->AddEntry(gr2fit_17324[50], "Si 01 center, Mar.24", "pl");
    leg0->AddEntry(gr2fit_17324[51], "Si 02 center, Mar.24", "pl");
    leg0->AddEntry(gr2fit_17411[50], "Si 01 (~20cm), Apr.11", "pl");
    leg0->AddEntry(gr2fit_17411[51], "Si 02 (~20cm), Apr.11", "pl");
    leg0->SetFillStyle(0);
    leg0->Draw();
    
    
    gPad->Modified();
    gPad->Print("plots/"+subname+"blm15_vs_si0102.eps");
    delete leg0;
   
cout<<"Si different at swing"<<(fitpara[1]-fitpara[0])/fitpara[0]<<endl;
cout<<"Si different at center"<<(fitpara[3]-fitpara[2])/fitpara[2]<<endl;
cout<<"Si01 reduce when go off center"<<(fitpara[0]-fitpara[2])/fitpara[2]<<endl;
cout<<"Si02 reduce when go off center"<<(fitpara[1]-fitpara[3])/fitpara[3]<<endl;
 //2D plots
    TH2F* Si01_vs_blm15_17324 = (TH2F*)pfile17324->Get("Si01_vs_blm15_17324");
    TH2F* Si02_vs_blm15_17324 = (TH2F*)pfile17324->Get("Si02_vs_blm15_17324");
    TH2F* Si01_vs_si02_17324 = (TH2F*)pfile17324->Get("Si01_vs_si02_17324");
    
    Si01_vs_blm15_17324->GetXaxis()->SetTitle("Integrated ADC of Si 01");
    Si01_vs_blm15_17324->GetYaxis()->SetTitle("Integrated ADC of BLM 15");
    titleStyle(Si01_vs_blm15_17324);
    new TCanvas;
    Si01_vs_blm15_17324->SetMarkerStyle(8);
    Si01_vs_blm15_17324->SetMarkerSize(0.6);
    Si01_vs_blm15_17324->Draw("SCAT");
    gPad->Print("plots/"+subname+"2d_blm15_vs_si01.eps");
    
    
    Si02_vs_blm15_17324->GetXaxis()->SetTitle("Integrated ADC of Si 02");
    Si02_vs_blm15_17324->GetYaxis()->SetTitle("Integrated ADC of BLM 15");
    titleStyle(Si02_vs_blm15_17324);
    new TCanvas;
    Si02_vs_blm15_17324->SetMarkerStyle(8);
    Si02_vs_blm15_17324->SetMarkerSize(0.6);
    Si02_vs_blm15_17324->Draw("SCAT");
    gPad->Print("plots/"+subname+"2d_blm15_vs_si02.eps");
    
    new TCanvas;
    ci = TColor::GetColor(colorRun[1]);
    Si01_vs_blm15_17324->GetXaxis()->SetTitle("Integrated ADC of Si 01-02");
    Si01_vs_blm15_17324->SetMarkerColor(ci);
    Si01_vs_blm15_17324->Draw("SCAT");
    //gPad->Modified();
    ci = TColor::GetColor(colorRun[2]);
    Si02_vs_blm15_17324->SetMarkerColor(ci);
    Si02_vs_blm15_17324->Draw("SCAT same");
    TLegend* leg1 = new TLegend(.2, .65, 0.4, .85);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.045);
    leg1->AddEntry(Si01_vs_blm15_17324, "Si-1 vs BLM-15", "pl");
    leg1->AddEntry(Si02_vs_blm15_17324, "Si-2 vs BLM-15", "pl");
    leg1->SetFillStyle(0);
    leg1->Draw();
    gPad->Print("plots/"+subname+"2d_blm15_vs_si0102.eps");
    
    
    
    
    Si01_vs_si02_17324->GetXaxis()->SetTitle("Integrated ADC of Si 01");
    Si01_vs_si02_17324->GetYaxis()->SetTitle("Integrated ADC of Si 02");
    titleStyle(Si01_vs_si02_17324);
    new TCanvas;
    Si01_vs_si02_17324->SetMarkerStyle(8);
    Si01_vs_si02_17324->SetMarkerSize(0.6);
    Si01_vs_si02_17324->Draw("SCAT");
    gPad->Print("plots/"+subname+"2d_si01_vs_si02.eps");
    
    
    ////////////////////////////////////////
    /////////////Fit graph w/ SSEM out
    
    

    
}
