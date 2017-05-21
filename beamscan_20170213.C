 
void beamscan_20170213(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
	gROOT->ProcessLine(".L hAnaBeam.C");
TFile *pfile;
TCanvas *c1 = new TCanvas("c1","c1",800,650);
//gPad->SetRightMargin(gPad->GetRightMargin()*1.5);
//Run #720122 SSEM out, CT attenuation testing
//Run #720123 SSEM in  CT auto?
//Run #720124 
Int_t runstart = 720122;
Int_t runend = 720142;
TChain *pchain = new TChain("anabeam");
for (int i=runstart; i<=runend;i++){
	pchain->Add(Form("2016oct/run%07d_gen.root",i));
	//else pchain->Add(Form("2016oct/run%07d_%d_gen.root",run2plot,i));
}

hAnaBeam *pAnalysis = new hAnaBeam();
pAnalysis->Init(pchain);
pAnalysis->Loop("beamstudy_20170213.root");

//CT plots
/*c1->cd();
pchain->Draw("ct_bunch[4]:Iteration$+1.0>>haxis(18,0,9,500,27e12,31e12)","esmx[18]!=0","colz");
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("By bunch");
haxis->GetYaxis()->SetTitle("CT 5 POT");
c1->Modified();
c1->Print(Form("plots/basic_run%07d_ct.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_ct.gif",run2plot));

//ESM X
c1->cd();
pchain->Draw("esmx:Iteration$+1.0>>hesmx(46,0,23,500,-5,5)","ssemx[18]!=0","colz");
hesmx->SetTitle();
hesmx->GetXaxis()->SetTitle("ESM monitors");
hesmx->GetYaxis()->SetTitle("ESM X [mm]");
c1->Modified();
c1->Print(Form("plots/basic_run%07d_esmx.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmx.eps",run2plot));
c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmx.gif",run2plot));

//ESM Y
 c1->cd();
    pchain->Draw("esmy:Iteration$+1.0>>hesmy(46,0,23,500,-5,5)","ssemx[18]!=0","colz");
    hesmy->SetTitle();
    hesmy->GetXaxis()->SetTitle("ESM monitors");
    hesmy->GetYaxis()->SetTitle("ESM Y [mm]");
    c1->Modified();
    c1->Print(Form("plots/basic_run%07d_esmy.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmy.eps",run2plot));
    c1->Print(Form("/export/jnulsv01/home/cvson/public_html/beamorbit/basic/basic_run%07d_esmy.gif",run2plot));
*/


}
