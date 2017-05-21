void drawblm_scan20170310_mefile(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    TString subname="beamscan_20170310";
    TFile *pfile = new TFile("beamscan_20170310_vs_scan20170213.root");
    new TCanvas;
    
    const Int_t NBLM = 52;
    char* atitle[NBLM]={
        "BLM01@up-PV1","BLM02@down-PV1","BLM03@down-PH2","BLM04@MR-PQ2","BLM05@aisle-PQ2","BLM06@down-PQ2","BLM07@down-PD1","BLM08@down-PD2-right","BLM09@down-PD2-left","BLM10@down-PC1",
        "BLM11@up-PQ3","BLM12@down-PQ3","BLM13@up-PV2","BLM14@down-PV2","BLM15@down-PQ4","BLM16@down-PC4-right","BLM17@down-PC4-left","BLM18@down-PH3","BLM19@down-PQ5","BLM20@middle-SC01",
        "BLM21@down-SC01", "BLM22@middle-SC02","BLM23@down-SC02","BLM24@middle-SC03","BLM25@down-SC03","BLM26@middle-SC04","BLM27@down-SC04","BLM28@middle-SC05","BLM29@down-SC05","BLM30@middle-SC06",
        "BLM31@down-SC06","BLM32@middle-SC07","BLM33@down-SC07","BLM34@down-SC08","BLM35@down-SC09","BLM36@down-SC010","BLM37@down-SC11","BLM38@down-SC12","BLM39@down-SC13","BLM40@down-SC14",
        "BLM41@down-FQ1","BLM42@down-FV1","BLM43@down-FH1","BLM44@down-FV2","BLM45@down-FQ2","BLM46@down-FQ3","BLM47@down-FH2","BLM48@down-FVD1","BLM49@down-FQ4","BLM50@down-FVD2","Si 1@BLM01","Si 2@BLM16"
    };
    /***********************************/
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
        //new scan 2017 03 13
        gr2fit_17310[iblm] = new TGraphErrors(NTEST17310,ctmean_17310,adcmean_17310[iblm],ctrms_17310,adcrms_17310[iblm]);
        gr2fit_17310[iblm]->SetMarkerStyle(8);
        gr2fit_17310[iblm]->SetMarkerColor(4);
        gr2fit_17310[iblm]->SetLineColor(4);
        gr2fit_17310[iblm]->Draw("PL same");
        TLegend* leg0 = new TLegend(.2, .65, 0.4, .85);
	leg0->SetFillStyle(0);
	leg0->SetBorderSize(0);
	    leg0->SetTextSize(0.045);
	leg0->AddEntry(gr2fit[iblm], "Beam scan 17.02.13", "pl");
	leg0->AddEntry(gr2fit_17310[iblm], "Beam scan 17.03.10", "pl");
	leg0->SetFillStyle(0);
	leg0->Draw();


	gPad->Modified();
        gPad->Print("plots/"+subname+Form("_vsCT_blm%d.eps",iblm+1));
	delete leg0;
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
