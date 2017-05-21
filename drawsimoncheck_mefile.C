void drawsimoncheck_mefile(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
TString subname="simoncheck_20170220";
TFile *pfile = new TFile("simoncheck_20170220_mefile.root");
new TCanvas;
const Int_t NBLM = 52;
TH1F* hdata[NBLM];
        TH2F* hcorNN1[NBLM];
for(int i=0; i<NBLM; i++){
                hdata[i] = (TH1F*)pfile->Get(Form("hdata_blm%d",i));

                 hcorNN1[i] = (TH2F*)pfile->Get(Form("hcorNN1_blm%d",i));
        }

//si 01
hcorNN1[50]->GetXaxis()->SetTitle("Integrated ADC of BLM01");
hcorNN1[50]->GetYaxis()->SetTitle("Integrated ADC of Si 01");
hcorNN1[50]->GetXaxis()->SetRangeUser(100,150);
hcorNN1[50]->GetYaxis()->SetRangeUser(25,35);

/*hcorNN1[50]->GetXaxis()->SetRangeUser(100,600);
hcorNN1[50]->GetYaxis()->SetRangeUser(0,35);
*/
titleStyle(hcorNN1[50]);
hcorNN1[50]->Draw("colz");
gPad->Print("plots/"+subname+"si01.eps");
gPad->Print("/export/jnulsv01/home/cvson/public_html/beamloss/simon/"+subname+"si01.eps");


hcorNN1[51]->GetXaxis()->SetTitle("Integrated ADC of BLM16");
hcorNN1[51]->GetYaxis()->SetTitle("Integrated ADC of Si 02");
hcorNN1[51]->GetXaxis()->SetRangeUser(480,530);
hcorNN1[51]->GetYaxis()->SetRangeUser(90,100);

/*hcorNN1[51]->GetXaxis()->SetRangeUser(0,600);
hcorNN1[51]->GetYaxis()->SetRangeUser(0,100);
*/
titleStyle(hcorNN1[51]);
hcorNN1[51]->Draw("colz");
gPad->Print("plots/"+subname+"si02.eps");
gPad->Print("/export/jnulsv01/home/cvson/public_html/beamloss/simon/"+subname+"si02.eps");

}
