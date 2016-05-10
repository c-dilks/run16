// tests small_cell_LUT conversion from hex --> voltage and draws 
// result in black; also tests inverse function, drawing the result
// in red

{
  gROOT->LoadMacro("small_cell_LUT.C");
  TGraph * plot = new TGraph();
  TGraph * plot_inv = new TGraph();
  plot->SetMarkerSize(0.5);
  plot->SetMarkerStyle(kFullCircle);
  plot_inv->SetMarkerSize(0.5);
  plot_inv->SetMarkerStyle(kFullCircle);
  plot_inv->SetMarkerColor(kRed);
  plot->SetTitle("rdac to hv;rdac set point;voltage set point (V)");
  Int_t c=0;
  Int_t c_inv=0;
  for(Int_t i=0; i<=256; i++)
  {
    //printf("%d\n",i+1);
    plot->SetPoint(c,i,small_cell_LUT(i));
    c++;
  };
  for(Int_t v=900; v<=1800; v+=50)
  {
    plot_inv->SetPoint(c_inv,small_cell_LUT_inv((Double_t)v),v);
    c_inv++;
  };

  TF1 * ff = new TF1("ff","pol3",0,250);
  plot->Fit(ff,"","",0,250);

  TCanvas * c1 = new TCanvas("c1","c1",500,700);
  TMultiGraph * mg = new TMultiGraph();
  mg->Add(plot);
  mg->Add(plot_inv);
  c1->SetGrid(1,1);
  mg->Draw("AP");
};
