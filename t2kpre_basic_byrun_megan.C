void t2kpre_basic_byrun_megan(Int_t run2plot, Int_t nsubrun){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    /*const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
	*/
TFile *pfile;
TCanvas *c1 = new TCanvas("c1","c1",800,650);
//gPad->SetRightMargin(gPad->GetRightMargin()*1.5);

TChain *pchain = new TChain("anabeam");
for (int i=0; i<nsubrun;i++){
	if (i==0) pchain->Add(Form("2016oct/run%07d_gen.root",run2plot));
	else pchain->Add(Form("2016oct/run%07d_%d_gen.root",run2plot,i));
}

//CT plots
c1->cd();
pchain->Draw("ct_bunch[4]:Iteration$+1.0>>haxis(18,0,9,500,27e12,31e12)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("By bunch");
haxis->GetYaxis()->SetTitle("CT 5 POT");
c1->Modified();
c1->Print(Form("plots/basic_run%07d_ct.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct.gif",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct.gif",0));

//CT0
    c1->cd();
    pchain->Draw("ct_bunch[0]:Iteration$+1.0>>haxisct0(18,0,9,500,27e12,31e12)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    haxisct0->SetTitle();
    haxisct0->GetXaxis()->SetTitle("By bunch");
    haxisct0->GetYaxis()->SetTitle("CT 0 POT");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_ct.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct0.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct0.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct0.gif",0));


//ESM X
c1->cd();
pchain->Draw("esmx:Iteration$+1.0>>hesmx(46,0,23,500,-6,6)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
hesmx->SetTitle();
hesmx->GetXaxis()->SetTitle("ESM monitors");
hesmx->GetYaxis()->SetTitle("ESM X [mm]");
c1->Modified();
c1->Print(Form("plots/basic_run%07d_esmx.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmx.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmx.gif",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmx.gif",0));

//ESM 1 X by bunch
    c1->cd();
    pchain->Draw("esmx_bunch[0]:Iteration$+1.0>>hesm0xbunch(18,0,9,100,-8,8)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hesm0xbunch->SetTitle();
    hesm0xbunch->GetXaxis()->SetTitle("ESM by bunch");
    hesm0xbunch->GetYaxis()->SetTitle("ESM 0 X [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_esmx.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm0x_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm0x_bunch.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm0x_bunch.gif",0));
//ESM 1 Y by bunch
       c1->cd();
    pchain->Draw("esmy_bunch[0]:Iteration$+1.0>>hesm0ybunch(18,0,9,500,-8,8)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hesm0ybunch->SetTitle();
    hesm0ybunch->GetXaxis()->SetTitle("ESM by bunch");
    hesm0ybunch->GetYaxis()->SetTitle("ESM 0 Y [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_esmx.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm0y_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm0y_bunch.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm0y_bunch.gif",0));
//ESM 8 X by bunch

   c1->cd();
    pchain->Draw("esmx_bunch[7]:Iteration$+1.0>>hesm8xbunch(18,0,9,100,-8,8)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hesm8xbunch->SetTitle();
    hesm8xbunch->GetXaxis()->SetTitle("ESM by bunch");
    hesm8xbunch->GetYaxis()->SetTitle("ESM 8 X [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_esmx.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm8x_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm8x_bunch.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm8x_bunch.gif",0));

//ESM 8 Y by bunch
        c1->cd();
    pchain->Draw("esmy_bunch[7]:Iteration$+1.0>>hesm8ybunch(18,0,9,100,-8,8)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hesm8ybunch->SetTitle();
    hesm8ybunch->GetXaxis()->SetTitle("ESM by bunch");
    hesm8ybunch->GetYaxis()->SetTitle("ESM 8 Y [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_esmx.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm8y_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm8y_bunch.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esm8y_bunch.gif",0));

   

//ESM Y
 c1->cd();
    pchain->Draw("esmy:Iteration$+1.0>>hesmy(46,0,23,500,-6,6)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hesmy->SetTitle();
    hesmy->GetXaxis()->SetTitle("ESM monitors");
    hesmy->GetYaxis()->SetTitle("ESM Y [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_esmy.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmy.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmy.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmy.gif",0));
//SSEM X
c1->cd();
    pchain->Draw("ssem19x_bunch:Iteration$+1>>hssemx(18,0,9,100,-10,10)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hssemx->SetTitle();
    hssemx->GetXaxis()->SetTitle("SSEM 19 by bunch");
    hssemx->GetYaxis()->SetTitle("SSEM 19 X pos. [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_ssem19x_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ssem19x_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ssem19x_bunch.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ssem19x_bunch.gif",0));

//SSEM Y
c1->cd();
    pchain->Draw("ssem19y_bunch:Iteration$+1>>hssemy(18,0,9,100,-10,10)","ct[4]>0 && ssemx[18]!=0 && ssemy[18]!=0","colz");
    hssemy->SetTitle();
    hssemy->GetXaxis()->SetTitle("SSEM 19 by bunch");
    hssemy->GetYaxis()->SetTitle("SSEM 19 Y pos. [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_ssem19y_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ssem19y_bunch.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ssem19y_bunch.gif",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ssem19y_bunch.gif",0));


}
