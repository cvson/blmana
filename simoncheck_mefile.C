 
void simoncheck_mefile(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
	gROOT->ProcessLine(".L hAnaBeamMe.C");
TFile *pfile;
TCanvas *c1 = new TCanvas("c1","c1",800,650);
//gPad->SetRightMargin(gPad->GetRightMargin()*1.5);
//Run #720122 SSEM out, CT attenuation testing
//Run #720123 SSEM in  CT auto?
//Run #720124 
Int_t run2add[]={720119,720142,720144,720153,720160};
//Int_t run2add[]={720119,720142,720144,720153,720160,720165};//720165 is when SSEM out, standard BLM has gain 10 times
Int_t norun2add = sizeof(run2add)/sizeof(Int_t);
TChain *pchain = new TChain("anabeam");
for (int i=0; i<norun2add;i++){
	pchain->Add(Form("rootfilesct/run%07d_blmct.root",run2add[i]));
}

hAnaBeamMe *pAnalysis = new hAnaBeamMe();
pAnalysis->Init(pchain);
pAnalysis->SiMonCheck("simoncheck_20170220_mefile.root");



}
