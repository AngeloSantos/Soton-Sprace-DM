#include "setTDRStyle.h"

void plotLimitsMET () {

  int nBM = 15;//8;//23;//7;

  double x[] = { 275 , 325 , 375 , 425 , 475 , 525 , 575 , 625 , 675 , 725 , 775 , 825 , 875 , 925 , 975 };
  double xErr[] = { 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 };
  double yErr[] = { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 };
  double yExp[] = { 0.0846224647632 , 0.0546981210547 , 0.031000813896 , 0.0183422776618 , 0.0112412576975 , 0.0070630299012 , 0.00501427993274 , 0.00329687082608 , 0.00213401161792 , 0.0013510620838 , 0.00094654638208 , 0.0006507410286 , 0.0004596983872 , 0.0003462886336 , 0.000258682086 };
  double yObs[] = { 0.10100821221 , 0.087606267241 , 0.053377224134 , 0.0256592823302 , 0.0123021204782 , 0.0078032455956 , 0.0035514325951 , 0.00274761920472 , 0.00176265345984 , 0.000993098418 , 0.00073302414588 , 0.00048871554784 , 0.00034744483202 , 0.0002188383184 , 0.000215116213 };
  double yLow2[] = { 0.0390524790802 , 0.0253013361869 , 0.014331405842 , 0.00850171605504 , 0.00522386385924 , 0.0032837278656 , 0.0023239121919 , 0.00153084627488 , 0.00099160731488 , 0.0006346203838 , 0.0004483723907 , 0.00031599713938 , 0.00023002554848 , 0.00017847792144 , 0.000137226141 };
  double yLow1[] = { 0.0238249406117 , 0.0154460828621 , 0.008747908598 , 0.0051934477296 , 0.00319375126668 , 0.0020079359664 , 0.0014197118949 , 0.00093560898808 , 0.00060628998976 , 0.0003892115461 , 0.00027578031338 , 0.00019591133614 , 0.00014391660426 , 0.0001126410272 , 8.7414366e-05 };
  double yHigh1[] = { 0.0336199721364 , 0.0218417418086 , 0.012359622626 , 0.00735787830336 , 0.00453869123604 , 0.0028555755228 , 0.00201131723208 , 0.00132833434864 , 0.00086204978496 , 0.0005605513342 , 0.00040154819172 , 0.0002926417052 , 0.0002218764834 , 0.0001784801824 , 0.000143076375 };
  double yHigh2[] = { 0.0735152969725 , 0.0478101878093 , 0.027041138124 , 0.0161257410038 , 0.00996829934646 , 0.0062753340468 , 0.00440975744846 , 0.00291556896592 , 0.00189452169088 , 0.0012417220582 , 0.00089640450692 , 0.0006641315642 , 0.0005131192196 , 0.00041940808 , 0.000342888715 };
  double ySignal[] = { 0.00187716204 , 0.00097673472 , 0.000536978 , 0.00031201248 , 0.00019246422 , 0.0001187004 , 7.828574e-05 , 4.861064e-05 , 3.165344e-05 , 1.83703e-05 , 1.215266e-05 , 6.50026e-06 , 3.67406e-06 , 2.26096e-06 , 1.4131e-06 };


  //  char *label[5]   = {"BM1",    "BM2",    "BM3",    "BM4",    "BM4"};

  TGraphErrors *gEmpty  = new TGraphErrors(nBM, x, yExp,    xErr, yErr);
  TGraphErrors *gExp    = new TGraphErrors(nBM, x, yExp,    xErr, yErr);
  TGraphErrors *gObs    = new TGraphErrors(nBM, x, yObs,    xErr, yErr);
  TGraphErrors *gSignal = new TGraphErrors(nBM, x, ySignal, yErr, yErr);
  
  TGraphAsymmErrors *gBand1 = new TGraphAsymmErrors(nBM, x, yExp, xErr, xErr, yLow1, yHigh1);
  TGraphAsymmErrors *gBand2 = new TGraphAsymmErrors(nBM, x, yExp, xErr, xErr, yLow2, yHigh2);

  //  TH1F *hLabel = new TH1F("hLabel", "hLabel", 5, 0.5, 5.5);

  gExp->SetLineStyle(2);
  gExp->SetLineColor(kBlue);
  gExp->SetMarkerColor(kBlue);
  gExp->SetLineWidth(2);

  gObs->SetMarkerStyle(20);
  gObs->SetMarkerColor(kBlack);
  gObs->SetMarkerSize(0.8);

  gSignal->SetMarkerColor(kRed);
  gSignal->SetLineColor(kRed);
  gSignal->SetLineWidth(3);

  gBand1->SetLineColor(kGreen);
  gBand1->SetFillColor(kGreen);
  gBand2->SetLineColor(kYellow-4);
  gBand2->SetFillColor(kYellow-4);

  gEmpty->SetTitle("");
  //  gEmpty->GetYaxis()->SetRangeUser(0.003, 1);
  gEmpty->GetYaxis()->SetRangeUser(0.000003, 1);
  gEmpty->GetXaxis()->SetRangeUser(250, 1000);
  gEmpty->GetYaxis()->SetTitleOffset(1.4);
  gEmpty->GetYaxis()->SetTitleSize(0.05);
  gEmpty->GetYaxis()->SetLabelSize(0.04);
  gEmpty->GetYaxis()->SetTitle("#sigma #times #varepsilon [pb]");
  //  gEmpty->GetXaxis()->SetTitle("M#scale[0.6]{h1} [GeV]");
  gEmpty->GetXaxis()->SetTitle("MET [GeV]");
  gEmpty->GetXaxis()->SetTitleSize(0.05);
  gEmpty->GetYaxis()->CenterTitle();
  gEmpty->GetXaxis()->SetLabelSize(0.04);

  //  for (int i = 0; i < 5; i++) hLabel->Fill(label[i], x[i]);
  //  hLabel->LabelsDeflate();

  TCanvas *canvas = new TCanvas("canvas", "canvas", 600, 600);
  canvas->cd();

  TStyle tdrStyle("tdrStyle","Style for P-TDR");
  setTDRStyle(tdrStyle);

  gStyle->SetOptStat(kFALSE);
  gPad->SetLogy();
  gPad->SetGrid();
  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetTopMargin(0.06);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.12);

  gEmpty->Draw("AP");
  //  hLabel->Draw("P same");
  gBand2->Draw("E2 same");
  gBand1->Draw("E2 same");
  gExp->Draw("PE same");
  gObs->Draw("P same");
  gSignal->Draw("PL same");

  /*
  TPaveText *paveDat2 = new TPaveText(0.15, 0.02, 0.95, 0.1, "NDC");
  paveDat2->AddText("      BM1      BM2      BM3      BM4      BM5");
  paveDat2->SetTextFont(62);
  paveDat2->SetTextAlign(10);
  paveDat2->SetTextSize(0.04);
  paveDat2->SetFillColor(kWhite);
  paveDat2->SetLineColor(kWhite);
  paveDat2->SetShadowColor(kWhite);
  paveDat2->Draw();
  */

  //  TLegend *leg = new TLegend(0.2,0.15,0.64,0.43);
  TLegend *leg = new TLegend(0.48,0.64,0.92,0.92);
  leg->SetBorderSize(1);
  leg->SetFillColor(0);
  leg->SetMargin(0.2);
  leg->SetTextFont(42);
  leg->SetTextSize(0.032);
  leg->SetHeader("95% upper limit for L = 19.7 fb^{-1}");
  leg->AddEntry(gObs,        "Observed limits", "pl"); // from EPJC 75 (2015) 235", "pl");
  leg->AddEntry(gExp,        "Expected limits", "pl"); // from EPJC 75 (2015) 235", "l");
  leg->AddEntry(gBand1,      "Expected #pm 1 std. deviation",  "f");
  leg->AddEntry(gBand2,      "Expected #pm 2 std. deviation",  "f");
  //  leg->AddEntry(gSignal,     "Signal of i2HDM",  "l");
  leg->AddEntry(gSignal,     "i2HDM (M#scale[0.6]{h1} = 60 GeV)",  "l");
  //  leg->AddEntry((TObject*)0, "BM1, M_{h1} = 45 GeV", "");
  //  leg->AddEntry((TObject*)0, "BM2, M_{h1} = 53 GeV", "");
  //  leg->AddEntry((TObject*)0, "BM3, M_{h1} = 66 GeV", "");
  //  leg->AddEntry((TObject*)0, "BM4, M_{h1} = 82 GeV", "");
  //  leg->AddEntry((TObject*)0, "BM5, M_{h1} = 120 GeV", "");
  leg->Draw();

  gPad->RedrawAxis();

  canvas->SaveAs("i2HDM_limits_Delphes_8TeV_Mh60_shapeAnalysis_250_1000_jetPtScale.png");
  canvas->SaveAs("i2HDM_limits_Delphes_8TeV_Mh60_shapeAnalysis_250_1000_jetPtScale.pdf");
  canvas->SaveAs("i2HDM_limits_Delphes_8TeV_Mh60_shapeAnalysis_250_1000_jetPtScale.root");

}
