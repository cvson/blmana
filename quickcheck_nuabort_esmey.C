void quickcheck_nuabort_esmey(){
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
       run.push_back(p1);
       spill.push_back(p2);
	subrun.push_back(p3);
	processid.push_back(p4);
     }
   cfile.close();
cout<<"Total NU Abort "<<run.size()<<endl;
TFile *pfile;
TCanvas *c1 = new TCanvas("c1","c1",800,650);
TH2F *hesmey = new TH2F("hesmey","",23,0,23,100,0,1);
TH2F *hesmey_all = new TH2F("hesmey_all","",23,0,23,100,0,1);
Int_t ncolors  = gStyle->GetNumberOfColors() ;
for (int i=0; i<run.size();i++){
if(subrun.at(i)==0) pfile = new TFile(Form("rootfiles/run%07d_orbit.root",run.at(i)));
else pfile = new TFile(Form("rootfiles/run%07d_%d_orbit.root",run.at(i),subrun.at(i)));
Int_t theColor = Int_t((i+0.99)*Float_t(ncolors)/Float_t(run.size())) ;
        if (theColor > ncolors-1) theColor = ncolors-1 ;
        anabeam->SetLineColor(gStyle->GetColorPalette(theColor));
c1->cd();
if (i==0)anabeam->Draw("esmey:Iteration$+1>>hesmey_all","ssemx[18]!=0","");
else anabeam->Draw("esmey:Iteration$+1>>hesmey_all","ssemx[18]!=0","same");

hesmey_all->GetYaxis()->SetRangeUser(0,1);
hesmey_all->SetTitle();
hesmey_all->GetXaxis()->SetTitle("ESM monitors");
hesmey_all->GetYaxis()->SetTitle("ESM EY");
hesmey->SetLineWidth(2);
//c1->cd();
if (i==0)hesmey_all->Draw("SCAT");
else hesmey_all->Draw("SCAT same");
}
//outlineer
for (int i=0; i<run.size();i++){
if(subrun.at(i)==0) pfile = new TFile(Form("rootfiles/run%07d_orbit.root",run.at(i)));
else pfile = new TFile(Form("rootfiles/run%07d_%d_orbit.root",run.at(i),subrun.at(i)));
Int_t theColor = Int_t((i+0.99)*Float_t(ncolors)/Float_t(run.size())) ;
        if (theColor > ncolors-1) theColor = ncolors-1 ;
        anabeam->SetLineColor(gStyle->GetColorPalette(theColor));
c1->cd();
if (i==0)anabeam->Draw("esmey:Iteration$+1>>hesmey",Form("spillnum==%d",spill.at(i)),"lsame");
else anabeam->Draw("esmey:Iteration$+1>>hesmey",Form("spillnum==%d",spill.at(i)),"lsame");

c1->cd();
c1->Modified();
 //hesmey->Draw("lsame");
}
//

c1->Update();
c1->Print("plots/r71_nuabort_esmey.eps");
pfile->Close();
}
