 
void beamscan_20170331(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
	gROOT->ProcessLine(".L hAnaBeamMe.C");
TFile *pfile;
//TCanvas *c1 = new TCanvas("c1","c1",800,650);
//gPad->SetRightMargin(gPad->GetRightMargin()*1.5);
//Run #720122 SSEM out, CT attenuation testing
//Run #720123 SSEM in  CT auto?
//Run #720124 
Int_t runstart = 720122;
Int_t runend = 720142;
TChain *pchain = new TChain("anabeam");
/*for (int i=runstart; i<=runend;i++){
	pchain->Add(Form("rootfilesct/run%07d_blmct.root",i));
}
//blm15 in new pos. (shift 4cm)
pchain->Add(Form("rootfilesct/run%07d_blmct.root",730010));
pchain->Add(Form("rootfilesct/run%07d_blmct.root",730011));
pchain->Add(Form("rootfilesct/run%07d_blmct.root",730012));
pchain->Add(Form("rootfilesct/run%07d_14_blmct.root",730018));

//scan 20170315
pchain->Add(Form("rootfilesct/run%07d_blmct.root",730044));
*/
//scan 20170324
//pchain->Add(Form("rootfilesct/run%07d_blmct.root",730091));
//pchain->Add(Form("rootfilesct/run%07d_blmct.root",730093));
//scan 20170331
pchain->Add(Form("rootfilesct/run%07d_blmct.root",740006));
hAnaBeamMe *pAnalysis = new hAnaBeamMe();
pAnalysis->Init(pchain);
pAnalysis->BeamScan20170331("beamscan_20170331.root");



}
