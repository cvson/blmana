void drawblm_scan20170315_mefile(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    TString subname="beamscan_20170315";
    TFile *pfile = new TFile("beamscan_20170315.root");
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
    for(Int_t iblm=0; iblm<NBLM; ++iblm){
        gr2fit[iblm] = new TGraphErrors(NTEST,ctmean,adcmean[iblm],ctrms,adcrms[iblm]);
        new TCanvas;
        gStyle->SetOptFit();
        gr2fit[iblm]->Draw("APL");
        gr2fit[iblm]->GetXaxis()->SetLimits(0,250);//newadd
        gr2fit[iblm]->SetMinimum(0);
        if(iblm>49)gr2fit[iblm]->SetMaximum(110);//for Si detector
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
        
        //scan 20170310
        gr2fit_17315[iblm] = new TGraphErrors(NTEST17315,ctmean_17315,adcmean_17315[iblm],ctrms_17315,adcrms_17315[iblm]);
        gr2fit_17315[iblm]->SetMarkerStyle(8);
        ci = TColor::GetColor(colorRun[2]);
        gr2fit_17315[iblm]->SetMarkerColor(ci);
        gr2fit_17315[iblm]->SetLineColor(ci);
        gr2fit_17315[iblm]->Draw("PL same");
        
        
        TLegend* leg0 = new TLegend(.2, .65, 0.4, .85);
	leg0->SetFillStyle(0);
	leg0->SetBorderSize(0);
	    leg0->SetTextSize(0.045);
	leg0->AddEntry(gr2fit[iblm], "Beam scan 17.02.13", "pl");
	leg0->AddEntry(gr2fit_17310[iblm], "Beam scan 17.03.10", "pl");
    leg0->AddEntry(gr2fit_17315[iblm], "Beam scan 17.03.15", "pl");
	leg0->SetFillStyle(0);
	leg0->Draw();


	gPad->Modified();
        gPad->Print("plots/"+subname+Form("_vsCT_blm%d.eps",iblm+1));
	delete leg0;
    }
    
    //compare BLM15, Si01, Si02
    new TCanvas;
    gStyle->SetOptFit();
    ci = TColor::GetColor(colorRun[1]);
    gr2fit_17315[50]->SetMarkerColor(ci);
    gr2fit_17315[50]->SetLineColor(ci);
    gr2fit_17315[50]->Draw("APL");
    
    gr2fit_17315[50]->GetXaxis()->SetLimits(0,250);//newadd
    gr2fit_17315[50]->SetMinimum(0);
    if(iblm>49)gr2fit_17315[50]->SetMaximum(110);//for Si detector
    titleStyle(gr2fit_17315[50]);
    gr2fit_17315[50]->GetXaxis()->SetTitle("CT intensity [x 10^{12}]");
    gr2fit_17315[50]->GetYaxis()->SetTitle("Integrated ADC");
    gr2fit_17315[50]->Fit("pol1","same",0,250);
    
    TF1 *f1 = gr2fit_17315[50]->GetListOfFunctions()->FindObject("pol1");
    f1->SetLineColor(ci);
    f1->Draw("same");
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
    gPad->Update();
    TPaveStats *st2 = (TPaveStats*)gr2fit_17315[51]->GetListOfFunctions()->FindObject("stats");
    st2->SetX1NDC(0.6);
    st2->SetX2NDC(0.8);
    st2->SetTextColor(ci);
    
    gPad->Update();
    
    TLegend* leg0 = new TLegend(.2, .65, 0.4, .85);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.045);
    leg0->AddEntry(gr2fit_17315[50], "Si 01", "pl");
    leg0->AddEntry(gr2fit_17315[51], "Si 02", "pl");
    leg0->SetFillStyle(0);
    leg0->Draw();
    
    
    gPad->Modified();
    gPad->Print("plots/"+subname+"blm15_vs_si0102.eps");
    delete leg0;
    
    TH2F* Si01_vs_blm15_17315 = (TH2F*)pfile->Get("Si01_vs_blm15_17315");
    TH2F* Si02_vs_blm15_17315 = (TH2F*)pfile->Get("Si02_vs_blm15_17315");
    TH2F* Si01_vs_si02_17315 = (TH2F*)pfile->Get("Si01_vs_si02_17315");
    
    Si01_vs_blm15_17315->GetXaxis()->SetTitle("Integrated ADC of Si 01");
    Si01_vs_blm15_17315->GetYaxis()->SetTitle("Integrated ADC of BLM 15");
    titleStyle(Si01_vs_blm15_17315);
    new TCanvas;
    Si01_vs_blm15_17315->SetMarkerStyle(8);
    Si01_vs_blm15_17315->SetMarkerSize(0.6);
    Si01_vs_blm15_17315->Draw("SCAT");
    gPad->Print("plots/"+subname+"2d_blm15_vs_si01.eps");
    
    
    Si02_vs_blm15_17315->GetXaxis()->SetTitle("Integrated ADC of Si 02");
    Si02_vs_blm15_17315->GetYaxis()->SetTitle("Integrated ADC of BLM 15");
    titleStyle(Si02_vs_blm15_17315);
    new TCanvas;
    Si02_vs_blm15_17315->SetMarkerStyle(8);
    Si02_vs_blm15_17315->SetMarkerSize(0.6);
    Si02_vs_blm15_17315->Draw("SCAT");
    gPad->Print("plots/"+subname+"2d_blm15_vs_si02.eps");
    
    new TCanvas;
    ci = TColor::GetColor(colorRun[1]);
    Si01_vs_blm15_17315->GetXaxis()->SetTitle("Integrated ADC of Si 01-02");
    Si01_vs_blm15_17315->SetMarkerColor(ci);
    Si01_vs_blm15_17315->Draw("SCAT");
    //gPad->Modified();
    ci = TColor::GetColor(colorRun[2]);
    Si02_vs_blm15_17315->SetMarkerColor(ci);
    Si02_vs_blm15_17315->Draw("SCAT same");
    TLegend* leg1 = new TLegend(.2, .65, 0.4, .85);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.045);
    leg1->AddEntry(Si01_vs_blm15_17315, "Si-1 vs BLM-15", "pl");
    leg1->AddEntry(Si02_vs_blm15_17315, "Si-2 vs BLM-15", "pl");
    leg1->SetFillStyle(0);
    leg1->Draw();
    gPad->Print("plots/"+subname+"2d_blm15_vs_si0102.eps");
    
    
    
    
    Si01_vs_si02_17315->GetXaxis()->SetTitle("Integrated ADC of Si 01");
    Si01_vs_si02_17315->GetYaxis()->SetTitle("Integrated ADC of Si 02");
    titleStyle(Si01_vs_si02_17315);
    new TCanvas;
    Si01_vs_si02_17315->SetMarkerStyle(8);
    Si01_vs_si02_17315->SetMarkerSize(0.6);
    Si01_vs_si02_17315->Draw("SCAT");
    gPad->Print("plots/"+subname+"2d_si01_vs_si02.eps");
    
    
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
    /////////////////////////////////////////
    //for SSEM19 out
    TGraphErrors *gr_ssem19out = (TGraphErrors*)pfile->Get("gr_ssem19out");
    TGraphErrors *grout_ssem19out = (TGraphErrors*)pfile->Get("grout_ssem19out");
    TH1F* hct_ssem19out = (TH1F*)pfile->Get("hct_ssem19out");
    TH1F* hct_out_ssem19out = (TH1F*)pfile->Get("houtct_ssem19out");
    double ctmean_ssem19out[1]; ctmean_ssem19out[0] = hct_ssem19out->GetMean()*1e-12;
    double ctrms_ssem19out[1]; ctrms_ssem19out[0]= hct_ssem19out->GetRMS()*1e-12;
    double ctmeanout_ssem19out[1]; ctmeanout_ssem19out[0]= hct_out_ssem19out->GetMean()*1e-12;
    double ctrmsout_ssem19out[1]; ctrmsout_ssem19out[0]= hct_out_ssem19out->GetRMS()*1e-12;
    
    double adcmean_ssem19out[NBLM][1];
    double adcrms_ssem19out[NBLM][1];
    double adcmeanout_ssem19out[NBLM][1];
    double adcrmsout_ssem19out[NBLM][1];
    double blmindex_new[NBLM];
    
    for(Int_t iblm=0; iblm<NBLM; ++iblm){
        gr_ssem19out->GetPoint(iblm,blmindex_new[iblm],adcmean_ssem19out[iblm][0]);
        adcrms_ssem19out[iblm][0] = gr_ssem19out->GetErrorY(iblm);
        cout<<"iblm "<<iblm<<" mean "<<adcmean_ssem19out[iblm][0]<<endl;
        grout_ssem19out->GetPoint(iblm,blmindex_new[iblm],adcmeanout_ssem19out[iblm][0]);
        adcrmsout_ssem19out[iblm][0] = grout_ssem19out->GetErrorY(iblm);
    }
    
    
    TGraphErrors *grOne_ssem19out[NBLM];
    TGraphErrors *grOneout_ssem19out[NBLM];
    
        /***********************************/
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
        
        grOne_ssem19out[iblm]  = new TGraphErrors(1,ctmean_ssem19out,adcmean_ssem19out[iblm],ctrms_ssem19out,adcrms_ssem19out[iblm]);
        grOne_ssem19out[iblm]->SetMarkerStyle(8);
        grOne_ssem19out[iblm]->SetMarkerColor(4);
        grOne_ssem19out[iblm]->SetLineColor(4);
        grOne_ssem19out[iblm]->Draw("p same");
        
        grOneout_ssem19out[iblm]  = new TGraphErrors(1,ctmeanout_ssem19out,adcmeanout_ssem19out[iblm],ctrmsout_ssem19out,adcrmsout_ssem19out[iblm]);
        grOneout_ssem19out[iblm]->SetMarkerStyle(8);
        grOneout_ssem19out[iblm]->SetMarkerColor(2);
        grOneout_ssem19out[iblm]->SetLineColor(2);
        grOneout_ssem19out[iblm]->Draw("p same");
        
        TLegend* leg0 = new TLegend(.2, .25, 0.4, .45);
        leg0->SetFillStyle(0);
        leg0->SetBorderSize(0);
        leg0->SetTextSize(0.040);
        leg0->AddEntry(gr2fitout[iblm], "Beam scan 17.02.13", "pl");
        leg0->AddEntry(grOne_ssem19out[iblm], "Beam scan 17.03.10 (SSEM 19 in)", "pl");
        leg0->AddEntry(grOneout_ssem19out[iblm], "Beam scan 17.03.10 (SSEM 19 out)", "pl");
        leg0->SetFillStyle(0);
        leg0->Draw();
        
        gPad->Modified();
        gPad->Print("plots/"+subname+Form("_ssemout_vsCT_blm%d.eps",iblm+1));
    }
    
    

    
}
