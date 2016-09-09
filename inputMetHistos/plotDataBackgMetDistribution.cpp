void plotDataBackgMetDistribution () {

  TFile *fData = TFile::Open("../exampleOfInputFiles_8TeV/EXO-12-048_data5.root",      "read");
  TFile *fBack = TFile::Open("../exampleOfInputFiles_8TeV/alternate_background5.root", "read");

  TH1F *hBack  = fBack->Get("CMS_EXO_12_048__background");
  TH1F *hBackP = fBack->Get("CMS_EXO_12_048__background__uncer__plus");
  TH1F *hBackM = fBack->Get("CMS_EXO_12_048__background__uncer__minus");
  TH1F *hData  = fData->Get("CMS_EXO_12_048__DATA");

  int nBins = hData->GetNbinsX();
  const int NBINS = nBins;

  double x[NBINS];
  double y[NBINS];
  double xErr[NBINS];
  double yErrLow[NBINS];
  double yErrHigh[NBINS];

  for (int i = 0; i < nBins; i++) {
    x[i] = hData->GetBinCenter(i+1);
    xErr[i] = hData->GetBinWidth(i+1) / 2;
    y[i] = hBack->GetBinContent(i+1);
    yErrLow[i] = y[i] - hBackM->GetBinContent(i+1);
    if (yErrLow[i] < 0) cout << "*\t yErrLow[" << i << "]: " << yErrLow[i] << endl;
    yErrHigh[i] =  hBackP->GetBinContent(i+1) - y[i];
    if (yErrHigh[i] < 0) cout << "*\t yErrHigh[" << i << "]: " << yErrHigh[i] << endl;
  }

  TGraphAsymmErrors *gBack = new TGraphAsymmErrors(nBins, x, y, xErr, xErr, yErrLow, yErrHigh);

  TCanvas *canvas = new TCanvas("canvas", "canvas", 600, 600);
  canvas->cd();
  gStyle->SetOptStat(kFALSE);
  gStyle->SetErrorX(0);

  // Set pads
  const double leftMargin     = 0.15;
  const double rightMargin    = 0.05;
  const double topMargin      = 0.075;
  const double bottomMargin   = 0.12;
  const double topMargin1     = 0.075;// In case of a first  pad (Mjj)
  const double bottomMargin1  = 0.0;  // In case of a first  pad (Mjj)
  const double topMargin2     = 0.0;  // In case of a second pad (Data/MC ratio)
  const double bottomMargin2  = 0.0;  // In case of a second pad (Data/MC ratio)
  const double topMargin3     = 0.0;  // In case of a third  pad (pull)
  const double bottomMargin3  = 0.3;  // In case of a third  pad (pull)

  // Set pads position in case of two pads:
  // - top pad for Mjj distribution;
  // - bottom pad for ratio.
  const Float_t padXmin  = 0.00;  // minimum x position of the pad1
  const Float_t padXmax  = 1.00;  // maximum x position of the pad1
  const Float_t padYmin1 = 0.25;  // minimum y position of the pad1
  const Float_t padYmax1 = 1.00;  // minimum y position of the pad1
  const Float_t padYmin2 = 0.25;  // minimum y position of the pad2
  const Float_t padYmax2 = 0.50;  // minimum y position of the pad2
  const Float_t padYmin3 = 0.00;  // minimum y position of the pad3
  const Float_t padYmax3 = 0.25;  // minimum y position of the pad3

  TPad *pad1 = new TPad("pad1", "pad1", padXmin, padYmin1, padXmax, padYmax1);
  pad1->Draw();
  pad1->SetBottomMargin(bottomMargin1);
  pad1->SetLeftMargin(leftMargin);
  pad1->SetRightMargin(rightMargin);
  pad1->SetTopMargin(topMargin);
  TPad *pad2 = new TPad("pad2", "pad2", padXmin, padYmin3, padXmax, padYmax3);
  pad2->Draw();
  pad2->SetTopMargin(topMargin3);
  pad2->SetLeftMargin(leftMargin);
  pad2->SetRightMargin(rightMargin);
  pad2->SetBottomMargin(bottomMargin3);

  //==================================================================
  pad1->cd();
  pad1->SetLogy();
  pad1->SetTicks();

  gBack->SetFillStyle(3015);
  gBack->SetFillColor(kBlue);
  gBack->SetLineColor(0);
  gBack->SetLineWidth(2);

  hBack->SetLineColor(kRed);
  hBack->SetLineWidth(2);
  hBack->GetYaxis()->SetTitle("Events / 25 GeV");
  hBack->GetXaxis()->SetTitle("MET [GeV]");
  hBack->GetYaxis()->SetTitleOffset(1.3);
  hBack->GetYaxis()->SetTitleSize(0.05);
  hBack->GetYaxis()->SetLabelSize(0.05);
  hBack->GetYaxis()->CenterTitle();
  hBack->GetYaxis()->SetRangeUser(0.02, 25000000);
  hBack->SetTitle("L = 19.7 fb^{-1} (8 TeV)");

  hData->SetMarkerStyle(8);
  hData->SetMarkerSize(0.8);
  hData->SetLineColor(kBlack);

  hBackP->SetLineColor(kGreen);
  hBackM->SetLineColor(kCyan);

  hBack->Draw();
  gBack->Draw("same E2");
  hBack->Draw("same histo");
  hData->Draw("same e0");
  //  hBackP->Draw("same histo");
  //  hBackM->Draw("same histo");

  TLegend *l = new TLegend(0.6, 0.7, 0.9, 0.9);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  //  l->SetMargin(0.15);
  l->SetTextSize(0.05);
  l->AddEntry(hData, "Data", "pl");
  l->AddEntry(hBack, "Background", "l");
  l->AddEntry(gBack, "Uncertainty", "f");
  l->Draw();


  //==================================================================
  pad2->cd();
  pad2->SetTicks();
  gStyle->SetEndErrorSize(0);

  double xxErr[NBINS];
  double yy[NBINS];
  double yyErrLow[NBINS];
  double yyErrHigh[NBINS];
  double yData;
  double yBack;
  double ySystData;
  double ySystBack;

  TH1F *h = (TH1F*)hBack->Clone("h");

  for (int i = 0; i < nBins; i++) {
    xxErr[i]     = 0.0;

    yData        = hData->GetBinContent(i+1);
    yBack        = hBack->GetBinContent(i+1);
    yy[i]        = (yData - yBack) / yBack;

    ySystData    = hData->GetBinError(i+1);
    ySystBack    = yErrLow[i];
    yyErrLow[i]  = (yData / yBack) * sqrt( pow(ySystData / yData, 2) + pow(ySystBack / yBack, 2) );

    ySystBack    = yErrHigh[i];
    yyErrHigh[i] = (yData / yBack) * sqrt( pow(ySystData / yData, 2) + pow(ySystBack / yBack, 2) );

    h->SetBinContent(i+1, 0);// yy[i]);
    //    h->SetBinError(i+1, yyErrHigh[i]);
  }

  TGraphAsymmErrors *pull = new TGraphAsymmErrors(nBins, x, yy, xxErr, xxErr, yyErrLow, yyErrHigh);
  pull->SetMarkerStyle(8);
  pull->SetMarkerSize(0.8);
  pull->SetMarkerColor(kBlack);
  pull->SetLineColor(kBlack);

  h->SetLineColor(kRed);
  h->SetLineWidth(2);
  h->GetYaxis()->SetRangeUser(-1.2, 1.2);
  h->GetYaxis()->SetTitle("#frac{Data - MC}{MC}");
  h->GetYaxis()->SetTitleOffset(0.4);
  h->GetYaxis()->SetTitleSize(0.15);
  h->GetYaxis()->SetLabelSize(0.12);
  h->GetXaxis()->SetTitle("MET [GeV]");
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetXaxis()->SetTitleSize(0.15);
  h->GetXaxis()->SetLabelSize(0.14);
  h->SetTitle();

  h->Draw();
  pull->Draw("same pe");

  canvas->SaveAs("DataBackgMET.root");
  canvas->SaveAs("DataBackgMET.png");
  canvas->SaveAs("DataBackgMET.pdf");

}
