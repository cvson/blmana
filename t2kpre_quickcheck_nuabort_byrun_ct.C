void t2kpre_quickcheck_nuabort_byrun_ct(Int_t run2plot){
gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
//ifstream cfile("database_nuabort.txt");
ifstream cfile("database_nuabort_r71_wsub.txt");
//ifstream cfile("database_nuabort_r72_wsub.txt");
         string line;
        getline(cfile,line);
        std::vector<int> run;
        std::vector<int> spill;
	std::vector<int> subrun;
	std::vector<int> processid;

         while (getline(cfile, line))
     {
       stringstream ss(line);
       int p1, p2, p3, p4;
       if(!(ss>>p1>>p2>>p3>>p4))
         {
           cerr<<"Bad line format: "<<endl
               <<"     "<<line<<endl;
           continue;
         }
       if(p1==run2plot){
	run.push_back(p1);
       	spill.push_back(p2);
	subrun.push_back(p3);
	processid.push_back(p4);
	}
     }
   cfile.close();
cout<<"Total NU Abort "<<run.size()<<endl;
TFile *pfile;
TCanvas *c1 = new TCanvas("c1","c1",800,650);
gPad->SetRightMargin(gPad->GetRightMargin()*1.5);
//TH2F *hct = new TH2F("hct","",23,0,23,100,-5,5);
//TH2F *hct_all = new TH2F("hct_all","",46,0,23,100,-5,5);
//TH2F *haxis = new TH2F("hct_all0","",46,0,23,100,-5,5);
//haxis->GetYaxis()->SetRangeUser(-5,5);
//haxis->SetTitle();
//haxis->GetXaxis()->SetTitle("ESM monitors");
//haxis->GetYaxis()->SetTitle("ESM X");
//haxis->DrawClone();
TLegend* leg0 = new TLegend(.22, .64, 0.5, .95);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    leg0->SetFillStyle(0);
Int_t ncolors  = gStyle->GetNumberOfColors() ;


int color=1;
TChain *pchain = new TChain("anabeam");
for (int i=0; i<run.size();i++){
if (i==0 || subrun.at(i)!=subrun.at(i-1)){
if(subrun.at(i)==0) pchain->Add(Form("rootfiles/run%07d_orbit.root",run.at(i)));
else pchain->Add(Form("rootfiles/run%07d_%d_orbit.root",run.at(i),subrun.at(i)));
}
}

c1->cd();
pchain->Draw("ct_bunch[4]:Iteration$+1.0>>haxis(18,0,9,100,25e12,30e12)","ssemx[18]!=0","colz");
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("By bunch");
haxis->GetYaxis()->SetTitle("CT 5 POT");

//outlineer
for (int i=0; i<run.size();i++){
if(subrun.at(i)==0) pfile = new TFile(Form("rootfiles/run%07d_orbit.root",run.at(i)));
else pfile = new TFile(Form("rootfiles/run%07d_%d_orbit.root",run.at(i),subrun.at(i)));
Int_t theColor = Int_t((i+0.99)*Float_t(ncolors)/Float_t(run.size())) ;
        if (theColor > ncolors-1) theColor = ncolors-1 ;
        anabeam->SetLineColor(gStyle->GetColorPalette(theColor));
c1->cd();
anabeam->Draw("ct_bunch[4]:Iteration$+1>>hct",Form("spillnum==%d",spill.at(i)),"lsame");
hct->SetLineColor(gStyle->GetColorPalette(theColor));
leg0->AddEntry(hct,Form("Run %06d Spill%06d ",run.at(i),spill.at(i)),"l");
c1->cd();
c1->Modified();
}
//

c1->Modified();
leg0->Draw("same");
c1->Print(Form("plots/r71_nuabort_run%07d_ct.eps",run2plot));
//c1->Print(Form("plots/r72_nuabort_run%07d_ct.eps",run2plot));
pfile->Close();
}
