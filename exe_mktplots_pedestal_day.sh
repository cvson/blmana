#!/bin/sh

# exe_mktplots.sh

echo Shell started

echo $#

if [ $# != 2 ]
then
    echo "Usage: ./exe_mktplots_pedestal_day.sh first_run# last_run#"
    exit
else
    echo $1 $2
fi

run=$1
run2=$2

echo '
#include <TTree.h>
#include <iostream>
#include <iomanip>
#include <fstream.h>
#include <stdio>

TChain *blmchain;
TLine *ladc800;
TLine *ladc900;
class BLMData {
 public:
  struct BLMData {
// 120215
    Int_t spill;
    Int_t run;
    Int_t event;
    Int_t dummy;
	
    Double_t integ[50];

    Long_t trgtime;

  } blmdata;

  BLMData(TChain *fChain){
    fChain->SetBranchAddress("BLMBranch",&blmdata);
  };
};

Double_t aymin[50]={
    -132,-154,-142,-132,-138,-78,-168,-122,10,50,
    70,75,80,80,18,50,-142,-118,-118,-148,
    -110,-130,-102,-120,-134,-126,-140,-126,-118,-122,
    -120,-94,-115,-100,-104,-108,-140,-107,-100,-125,
    -90,-160,-123,-55,-178,-132,-170,-130,-154,-160
};
Double_t aymax[50]={
-100,-100,-100,-100,-100,-50,-120,-60,60,90,
110,110,110,110,60,90,-100,-80,80,-110,
400,400,400,400,400,400,400,400,400,400,
400,400,400,400,400,400,400,400,400,400,
400,400,400,400,400,400,400,400,400,400
};
char* atitle[50]={
"BLM01@up-PV1","BLM02@down-PV1","BLM03@down-PH2","BLM04@MR-PQ2","BLM05@aisle-PQ2","BLM06@down-PQ2","BLM07@down-PD1","BLM08@down-PD2-right","BLM09@down-PD2-left","BLM10@down-PC1",
"BLM11@up-PQ3","BLM12@down-PQ3","BLM13@up-PV2","BLM14@down-PV2","BLM15@down-PQ4","BLM16@down-PC4-right","BLM17@down-PC4-left","BLM18@down-PH3","BLM19@down-PQ5","BLM20@middle-SC01",
"BLM21@down-SC01", "BLM22@middle-SC02","BLM23@down-SC02","BLM24@middle-SC03","BLM25@down-SC03","BLM26@middle-SC04","BLM27@down-SC04","BLM28@middle-SC05","BLM29@down-SC05","BLM30@middle-SC06",
"BLM31@down-SC06","BLM32@middle-SC07","BLM33@down-SC07","BLM34@down-SC08","BLM35@down-SC09","BLM36@down-SC010","BLM37@down-SC11","BLM38@down-SC12","BLM39@down-SC13","BLM40@down-SC14",
"BLM41@down-FQ1","BLM42@down-FV1","BLM43@down-FH1","BLM44@down-FV2","BLM45@down-FQ2","BLM46@down-FQ3","BLM47@down-FH2","BLM48@down-FVD1","BLM49@down-FQ4","BLM50@down-FVD2"
};

void autoplotPedestal()
{
  blmchain = new TChain("BLMTree");

' > autoplotPedestal.cc


while [ "${run}" -le $2 ]
  do
#  rfile=root_integ/run"$run"BLMI.root
  rfile=root_pedes2/run"$run"BLMI2.root
  echo ${rfile}

  if [ -f ${rfile} ]
      then
      echo "  blmchain->Add(\"${rfile}\");" >> autoplotPedestal.cc
  else
      echo "no such file: ${run}"
  fi

  run=`expr "${run}" + 1`
done

echo '
  BLMData *data = new BLMData(blmchain); 

  /* Get number of events */
  Int_t nevents = blmchain->GetEntries();

  Double_t xmin, xmax;
  Double_t runmin, runmax;
  Double_t vmin, vmax;

// Unix time of 2012/01/01 00:00:00 (JST = UTC+9) 1325343600
// Unix time of 2013/01/01 00:00:00 (JST = UTC+9) 1356966000
// Unix time of 2014/01/01 00:00:00 (JST = UTC+9) 1388502000
// Unix time of 2015/01/01 00:00:00 (JST = UTC+9) 1420038000
// Unix time of 2016/01/01 00:00:00 (JST = UTC+9) 1451574000

  Long_t toffset = -32400;//1451574000;
  Double_t daysec = 1.;

  blmchain->GetEntry(0);
  xmin = (data->blmdata.trgtime - toffset)/daysec;
  runmin = data->blmdata.run;
  vmin = data->blmdata.spill;

  blmchain->GetEntry(nevents-1);
  xmax = (data->blmdata.trgtime - toffset)/daysec;
  runmax = data->blmdata.run;
  vmax = data->blmdata.spill;
TCanvas* c1 = new TCanvas("c1", "", 1000, 700);
//gStyle->SetPadRightMargin(gStyle->GetPadRightMargin()*1.5);
gPad->SetRightMargin(gPad->GetRightMargin()*2);
  //mkplrunnum(xmin,xmax,runmin,runmax);
  //mkplspill(xmin,xmax,vmin,vmax);

for (Int_t ich=0; ich<50; ++ich) {
	mkpleachBLM(xmin, xmax, ich);
}
};


void mkpleachBLM(Double_t xmin, Double_t xmax, Int_t ithchannel)
{
Double_t ymin = aymin[ithchannel];
Double_t ymax = aymin[ithchannel]+20;
TH2D *hgraph = new TH2D("hgraph","",100,xmin,xmax,200,ymin,ymax);
hgraph->GetYaxis()->SetTitle("ADC pedestal mean");
hgraph->GetYaxis()->CenterTitle();
hgraph->GetXaxis()->SetTimeDisplay(1);
hgraph->GetXaxis()->SetTimeFormat("%d\/%m");
hgraph->GetXaxis()->SetTimeOffset(0,"gmt");
hgraph->GetXaxis()->SetNdivisions(-406);
hgraph->Draw();
TH2D *hgraph2proj = new TH2D("hgraph2proj","",100,xmin,xmax,200,ymin,ymax);
gStyle->SetOptStat(0);
//c1->SetLogy();
blmchain->SetMarkerStyle(8);
blmchain->SetMarkerSize(0.5);

blmchain->SetMarkerColor(1);
blmchain->Draw(Form("integ[%d]:(trgtime+32400)>>hgraph2proj",ithchannel),"","same");
TProfile *hprofile = (TProfile*)hgraph2proj->ProfileX();
    hprofile->SetLineWidth(3);
    hprofile->SetLineColor(kRed);
    hprofile->Draw("same");
 
TText t1(xmax+(xmax-xmin)/100.,ymax+(ymax-ymin)/100.,atitle[ithchannel]);
 t1.SetTextSize(0.03);
 t1.SetTextColor(1);
 t1.Draw();

c1->Print(Form("outBLM_%d.gif",ithchannel+1));
delete hgraph;
delete hgraph2proj;
delete hprofile;
}

void mkplrunnum(Double_t xmin, Double_t xmax, Double_t runmin, Double_t runmax)
{
  Double_t ymin = runmin;
  Double_t ymax = runmax;
TH2D *graphrunnum = new TH2D("RUN_NUMBER","run_number",100,xmin,xmax,200,ymin,ymax);
graphrunnum->GetXaxis()->SetTimeDisplay(1);
graphrunnum->GetXaxis()->SetTimeFormat("%d\/%m");
graphrunnum->GetXaxis()->SetTimeOffset(0,"gmt");
graphrunnum->GetXaxis()->SetNdivisions(-406);
//graphrunnum->GetXaxis()->SetNdivisions(510, kTRUE);
graphrunnum->Draw();
gStyle->SetOptStat(0);
blmchain->SetMarkerStyle(8);
blmchain->SetMarkerSize(0.5);
blmchain->SetMarkerColor(1);
blmchain->Draw("run:(trgtime+32400)","","same");
 TText t1(xmax+(xmax-xmin)/100.,ymin+(ymax-ymin)*19./20.,"RunNum");
 t1.SetTextSize(0.03);
 t1.SetTextColor(1);
 t1.Draw();

 TText t11(xmin+(xmax-xmin)*0.4.,ymin-(ymax-ymin)*0.1,"(JST = UTC+9)");
 t11.SetTextSize(0.04);
 t11.SetTextColor(1);
 t11.Draw();

c1->Print("outrunnum.gif");
}


void mkplspill(Double_t xmin, Double_t xmax, Double_t vmin, Double_t vmax)
{
  Double_t ymin = vmin;
  Double_t ymax = vmax;
TH2D *graphspill = new TH2D("SPILL NUMBER","spill number",100,xmin,xmax,200,ymin,ymax);
graphspill->GetXaxis()->SetTimeDisplay(1);
graphspill->GetXaxis()->SetTimeFormat("%d\/%m");
graphspill->GetXaxis()->SetTimeOffset(0,"gmt");
graphspill->GetXaxis()->SetNdivisions(-406);
graphspill->Draw();
gStyle->SetOptStat(0);
blmchain->SetMarkerStyle(8);
blmchain->SetMarkerSize(0.5);
blmchain->SetMarkerColor(1);
blmchain->Draw("spill:(trgtime+32400)","","same");
 TText t1(xmax+(xmax-xmin)/100.,ymin+(ymax-ymin)*19./20.,"Spill");
 t1.SetTextSize(0.03);
 t1.SetTextColor(1);
 t1.Draw();

 TText t11(xmin+(xmax-xmin)*0.4.,ymin-(ymax-ymin)*0.1,"(JST = UTC+9)");
 t11.SetTextSize(0.04);
 t11.SetTextColor(1);
 t11.Draw();

c1->Print("outspill.gif");
}
' >> autoplotPedestal.cc


# cat autoplotPedestal.cc

#root -b -q "autoplotPedestal.cc"
root -l -q "autoplotPedestal.cc"
for i in {1..50}; do mv "outBLM_${i}.gif" "day${1}-${2}_BLM${i}_pedestal.gif"; done
#mv "outBLM41-50.gif" "day$1-$2BLMI41-50log.gif"
mv "outrunnum.gif" "day$1-$2runnum_pedestal.gif"
mv "outspill.gif" "day$1-$2spill_pedestal.gif"

echo Shell ended
