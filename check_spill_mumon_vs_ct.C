void check_spill_mumon_vs_ct(Int_t spill, Int_t run){

  TChain c("anabeam");
  c.Add(Form("/export/jnufs01/data1/mfriend/generalAnaFiles/2016oct/run0%d*.root",run));
  c.SetLineColor(kRed);
gStyle->SetOptStat(0);
TCanvas *c1 = new TCanvas("c1","c1",800,650);
c1->cd();
  c.Draw("musiadc_cent:Iteration$+1>>haxis(200,0,500,200,-800,0)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Timing bin");
haxis->GetYaxis()->SetTitle("MUMON Si ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();
  c.Draw("musiadc_cent:Iteration$+1>>h1(200,0,500,200,-800,0)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
  c.Draw("musiadc_cent:Iteration$+1>>h2(200,0,500,200,-800,0)",Form("spillnum==%d",spill-1),"same L");
  h1->SetLineColor(kRed);
  h2->SetLineColor(kBlue);
    TLegend* leg0 = new TLegend(.65, .7, .85, .85);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
leg0->AddEntry(h1,Form("bad spill %d",spill),"l");
leg0->AddEntry(h2,Form("good spill %d",spill-1),"l");
leg0->Draw();
c1->Print(Form("plots/badspill_siadc_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
  c.Draw("ctadc[0]:Iteration$+1>>haxis(500,0,1000)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Timing bin");
haxis->GetYaxis()->SetTitle("CT 1 ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();

c.Draw("ctadc[0]:Iteration$+1>>h12(500,0,1000)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("ctadc[0]:Iteration$+1>>h22(500,0,1000)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ct1_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
  c.Draw("ctadc[1]:Iteration$+1>>haxis(500,0,1000)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Timing bin");
haxis->GetYaxis()->SetTitle("CT 2 ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();

c.Draw("ctadc[1]:Iteration$+1>>h12(500,0,1000)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("ctadc[1]:Iteration$+1>>h22(500,0,1000)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ct2_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
  c.Draw("ctadc[2]:Iteration$+1>>haxis(500,0,1000)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Timing bin");
haxis->GetYaxis()->SetTitle("CT 3 ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();
c.Draw("ctadc[2]:Iteration$+1>>h12(500,0,1000)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("ctadc[2]:Iteration$+1>>h22(500,0,1000)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ct3_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
  c.Draw("ctadc[3]:Iteration$+1>>haxis(500,0,1000)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Timing bin");
haxis->GetYaxis()->SetTitle("CT 4 ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();

c.Draw("ctadc[3]:Iteration$+1>>h12(500,0,1000)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("ctadc[3]:Iteration$+1>>h22(500,0,1000)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ct4_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
  c.Draw("ctadc[4]:Iteration$+1>>haxis(500,0,1000)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Timing bin");
haxis->GetYaxis()->SetTitle("CT 5 ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();
c.Draw("ctadc[4]:Iteration$+1>>h12(500,0,1000)",Form("spillnum==%d",spill),"same L");
  c.SetLineColor(kBlue);
  c.Draw("ctadc[4]:Iteration$+1>>h22(500,0,1000)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ct5_%d_run%d.eps",spill,run));




c1->cd();
c.SetLineColor(kRed);
  c.Draw("blmint:Iteration$+1>>haxis(102,0,51,500,0,2500)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("BLM index");
haxis->GetYaxis()->SetTitle("Integrated ADC count");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();

c.Draw("blmint:Iteration$+1>>h120a(102,0,51,500,0,2500)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("blmint:Iteration$+1>>h120b(102,0,51,500,0,2500)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Modified();
c1->Print(Form("plots/badspill_blm_%d_run%d.eps",spill,run));

//SSEM 19
c1->cd();
c.SetLineColor(kRed);
 c.Draw("ssem19x_bunch:Iteration$+1>>haxis(16,0,8,80,-20,20)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Position By bunch");
haxis->GetYaxis()->SetTitle("SSEM 19 X");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();

c.Draw("ssem19x_bunch:Iteration$+1>>h121a(16,0,8,80,-20,20)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("ssem19x_bunch:Iteration$+1>>h121b(16,0,8,80,-20,20)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ssem19x_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
 c.Draw("ssem19y_bunch:Iteration$+1>>haxis(16,0,8,80,-20,20)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("Position By bunch");
haxis->GetYaxis()->SetTitle("SSEM 19 Y");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();

c.Draw("ssem19y_bunch:Iteration$+1>>h122a(16,0,8)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("ssem19y_bunch:Iteration$+1>>h122b(16,0,8)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_ssem19y_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
 c.Draw("esmx:Iteration$+1>>haxis(40,0,20)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("ESM by index");
haxis->GetYaxis()->SetTitle("ESM X position");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c1->Modified();
c.Draw("esmx:Iteration$+1>>h123a(40,0,20)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("esmx:Iteration$+1>>h123b(40,0,20)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_esmx_%d_run%d.eps",spill,run));

c1->cd();
c.SetLineColor(kRed);
 c.Draw("esmy:Iteration$+1>>haxis(40,0,20)",Form("spillnum==%d",spill),"AXIS");
c1->Update();
haxis->SetTitle();
haxis->GetXaxis()->SetTitle("ESM by index");
haxis->GetYaxis()->SetTitle("ESM Y position");
haxis->GetXaxis()->SetTitleOffset(1.1);
haxis->GetYaxis()->SetTitleOffset(1.1);
c.Draw("esmy:Iteration$+1>>h124a(40,0,8)",Form("spillnum==%d",spill),"same L");
c.SetLineColor(kBlue);
c.Draw("esmy:Iteration$+1>>h124b(40,0,8)",Form("spillnum==%d",spill-1),"same L");
leg0->Draw();
c1->Print(Form("plots/badspill_esmy_%d_run%d.eps",spill,run));



}
