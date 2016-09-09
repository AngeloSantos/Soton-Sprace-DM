#include "setTDRStyle.h"

void plotLimitsMET () {

  // Number of bins
  int nBM = 15;//8;//23;//7;

  // These values come from limitsForPlotting.py
  double x[] = { 275 , 325 , 375 , 425 , 475 , 525 , 575 , 625 , 675 , 725 , 775 , 825 , 875 , 925 , 975 };
  double xErr[] = { 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 , 25 };
  double yErr[] = { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 };
  double yExp[] = { 0.0825453492728 , 0.055966299165 , 0.0325462073933 , 0.0189564658044 , 0.0116307034855 , 0.00719754385896 , 0.00463710091383 , 0.00280083343617 , 0.00180280674945 , 0.00112601679876 , 0.00088078148928 , 0.00063218747025 , 0.00049543958772 , 0.0003931944093 , 0.00027456730056 };
  double yObs[] = { 0.0615939814413 , 0.0735512963371 , 0.0469994432783 , 0.0233912083476 , 0.010454414675 , 0.00683282569032 , 0.00366494035509 , 0.00227690356698 , 0.00144437664672 , 0.0008230722822 , 0.00064832775084 , 0.00042678519975 , 0.00036305987508 , 0.00027141329124 , 0.00027708577848 };
  double yLow2[] = { 0.0381674789313 , 0.0260326918921 , 0.0151474711727 , 0.00884091721086 , 0.0054468292536 , 0.0033730163964 , 0.00216646816239 , 0.00131047091973 , 0.00084473503506 , 0.00053676612549 , 0.00041964581736 , 0.00030743831475 , 0.0002440218879 , 0.00019575401706 , 0.00014299899894 };
  double yLow1[] = { 0.0232999999848 , 0.0159201605947 , 0.00926504130762 , 0.00541025146557 , 0.00333856172664 , 0.00206767628424 , 0.00132705163836 , 0.00080310846735 , 0.00051789305988 , 0.00033078744279 , 0.00025859624868 , 0.00019075179375 , 0.00015206640624 , 0.00012246394482 , 9.067850694e-05 };
  double yHigh1[] = { 0.032934785332 , 0.0226489823104 , 0.0131861850618 , 0.00771752752155 , 0.00478384880904 , 0.00296631177192 , 0.00189767606868 , 0.00115102422036 , 0.00074532757824 , 0.00048520827117 , 0.00037965167856 , 0.0002860260795 , 0.00023154478074 , 0.00018930854628 , 0.00014656832064 };
  double yHigh2[] = { 0.0721015361483 , 0.0497546832485 , 0.0289750382183 , 0.0169827617056 , 0.010557282083 , 0.0065533337604 , 0.00418483829484 , 0.00254280473181 , 0.00165004199766 , 0.00108772750989 , 0.00085220031204 , 0.00065088391725 , 0.00053229893094 , 0.00043983354618 , 0.00034933239684 };
  double ySignal[] = { 0.00490319865 , 0.00257316318 , 0.00142846767 , 0.00084023163 , 0.00051433704 , 0.00031333176 , 0.00019435437 , 0.00011749941 , 7.611597e-05 , 4.212243e-05 , 3.251556e-05 , 1.847475e-05 , 1.330182e-05 , 1.034586e-05 , 4.43394e-06 };



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
