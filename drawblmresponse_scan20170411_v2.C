void drawblmresponse_scan20170411_v2(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    TString subname="blmresponse_20170411_v2";
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
    new TCanvas;
    /*Int_t blm_first = 19;
    Int_t blm_second = 40;*/
    /*Int_t blm_first = 0;
    Int_t blm_second = 10;*/
    /*Int_t blm_first = 10;
    Int_t blm_second = 19;*/
    Int_t blm_first = 40;
    Int_t blm_second = 50;
    
    /*for(Int_t iblm=blm_first; iblm<blm_second; ++iblm){
        gr2fit[iblm] = new TGraphErrors(NTEST,ctmean,adcmean[iblm],ctrms,adcrms[iblm]);
        
        gStyle->SetOptFit();
        if(iblm==blm_first)gr2fit[iblm]->Draw("APL");
        else gr2fit[iblm]->Draw("PL same");
        gr2fit[iblm]->GetXaxis()->SetLimits(0,250);//newadd
        gr2fit[iblm]->SetMinimum(0);
        
        if (iblm<10) gr2fit[iblm]->SetMaximum(600);
        else if (iblm<20) gr2fit[iblm]->SetMaximum(1100);
        else if (iblm<40) gr2fit[iblm]->SetMaximum(90);//for Si detector
        else gr2fit[iblm]->SetMaximum(600);
        titleStyle(gr2fit[iblm]);
        gr2fit[iblm]->GetXaxis()->SetTitle("CT intensity [x 10^{12}]");
        gr2fit[iblm]->GetYaxis()->SetTitle("Integrated ADC");
        gPad->Update();
       
        double yleg = TMath::MinElement(NTEST,gr2fit[iblm]->GetY()) + (TMath::MaxElement(NTEST,gr2fit[iblm]->GetY()) - TMath::MinElement(NTEST,gr2fit[iblm]->GetY()))*0.36/2;
        TText t1(150,yleg,Form("BLM %d - %d",blm_first+1,blm_second));
        t1.SetTextSize(0.06);
        t1.SetTextColor(1);
        t1.Draw();
        
       
        
        
    }*/
    Int_t iblm = blm_first;
    //gr2fit[iblm] = new TGraphErrors(NTEST,ctmean,adcmean[iblm],ctrms,adcrms[iblm]);
    gr2fit[iblm] = new TGraphErrors(NTEST,adcmean[iblm],ctmean,adcrms[iblm],ctrms);
    gr2fit[iblm]->Draw("APL");
    //gr2fit[iblm]->GetXaxis()->SetLimits(0,250);//newadd
    gr2fit[iblm]->SetMinimum(0);
    gr2fit[iblm]->SetMaximum(250);
    
    if (iblm<10) gr2fit[iblm]->GetXaxis()->SetLimits(0,600);
    else if (iblm<20) gr2fit[iblm]->GetXaxis()->SetLimits(0,1100);
    else if (iblm<40) gr2fit[iblm]->GetXaxis()->SetLimits(0,90);//for Si detector
    else gr2fit[iblm]->GetXaxis()->SetLimits(0,600);
    titleStyle(gr2fit[iblm]);
    gr2fit[iblm]->GetYaxis()->SetTitle("CT intensity [x 10^{12}]");
    gr2fit[iblm]->GetXaxis()->SetTitle("Integrated ADC");
    gPad->Update();
    
    Int_t iblm2 = iblm+1;
    for (Int_t ipoint=0; ipoint<NTEST; ipoint++) {
        double evalct = gr2fit[iblm]->Eval(adcmean[iblm2][ipoint],0,"S");
        cout<<"BLM "<<iblm2+1<<" point "<<ipoint<<" adc "<<adcmean[iblm2][ipoint]<<" eval "<<evalct<<" ct "<<ctmean[ipoint]<<" ratio "<<evalct/ctmean[ipoint]<<endl;
    }

     //TSpline3 *sp = new TSpline3("Cubic Spline", ctmean, adcmean[iblm], NTEST, "b2e2", 0, 0);
    // refer to http://root.cern.ch/root/html/Tspline3.html for the usage of TSpline3
    // "b2e2" together with the last two "0" means that the second derivatives
    // of the begin and end points equal to zero
   // sp->SetLineColor(kRed);
    //sp->Draw("lsame");

    
    gPad->Modified();
    gPad->Print("plots/"+subname+Form("_vsCT_blm%d_%d.eps",blm_first+1,blm_second));
    
    
}
