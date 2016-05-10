void draw_gain_fit_params(const char * filename="hvtr.root")
{
  TFile * infile = new TFile(filename,"READ");
  TTree * hvtr = (TTree*) infile->Get("hvtr");
  Int_t nstb,row,col;
  Double_t scale,alpha,chisq,ndf;
  hvtr->SetBranchAddress("nstb",&nstb);
  hvtr->SetBranchAddress("row",&row);
  hvtr->SetBranchAddress("col",&col);
  hvtr->SetBranchAddress("alpha",&alpha);
  hvtr->SetBranchAddress("scale",&scale);
  hvtr->SetBranchAddress("chisq",&chisq);
  hvtr->SetBranchAddress("ndf",&ndf);

  // fms display
  TH2F* large_alpha=new TH2F("large_alpha","#alpha (from ADC=cV^{#alpha})",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_alpha=new TH2F("small_alpha","#alpha (from ADC=cV^{#alpha})",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_scale=new TH2F("large_scale","c (from ADC=cV^{#alpha})",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_scale=new TH2F("small_scale","c (from ADC=cV^{#alpha})",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_chisq=new TH2F("large_chisq","#chi^{2}/NDF (from ADC=cV^{#alpha})",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_chisq=new TH2F("small_chisq","#chi^{2}/NDF (from ADC=cV^{#alpha})",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* largetxt=new TH2F("largetxt","largetxt",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smalltxt=new TH2F("smalltxt","smalltxt",52,-98.6,98.6,52,-98.6,98.6);
  Double_t alpha_max_large,alpha_max_small,alpha_min,scale_max,scale_min;
  scale_max = hvtr->GetMaximum("scale");
  //scale_min = hvtr->GetMinimum("scale");
  scale_min = 1e-10;
  alpha_max_large = 20;
  alpha_max_small = 13;
  alpha_min = 0;
  large_alpha->SetMaximum(alpha_max_large);
  large_alpha->SetMinimum(alpha_min);
  small_alpha->SetMaximum(alpha_max_small);
  small_alpha->SetMinimum(alpha_min);
  large_scale->SetMaximum(scale_max);
  large_scale->SetMinimum(scale_min);
  small_scale->SetMaximum(scale_max);
  small_scale->SetMinimum(scale_min);
  large_chisq->GetMaximum(3000);
  small_chisq->GetMaximum(3000);
  large_chisq->SetMinimum(0);
  small_chisq->SetMinimum(0);
  TH1F * alpha_dist_large_psu_and_res = new TH1F("alpha_dist_large_psu_and_res",
    "#alpha distribution -- large psu and resistive cells",200,alpha_min,alpha_max_large);
  TH1F * alpha_dist_large_fermi = new TH1F("alpha_dist_large_fermi",
    "#alpha distribution -- large fermi cells",200,alpha_min,alpha_max_large);
  TH1F * alpha_dist_small_russian = new TH1F("alpha_dist_small_russian",
    "#alpha distribution -- small russian cells",200,alpha_min,alpha_max_small);
  TH1F * alpha_dist_small_yale = new TH1F("alpha_dist_small_yale",
    "#alpha distribution -- small yale cells",200,alpha_min,alpha_max_small);
  hvtr->Project("largetxt","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(col+row*17+1)*(nstb==1||nstb==2)");
  hvtr->Project("smalltxt","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(col+row*12+1)*(nstb==3||nstb==4)");
  largetxt->SetMarkerSize(0.5);
  smalltxt->SetMarkerSize(0.5);
  TLine * vline = new TLine(0,-98.6,0,98.6);
  TLine * hline = new TLine(-98.6,0,98.6,0);
  TLine * svline[4];
    svline[0] = new TLine(3.8*2*(4-3.5)*(3+.5)+3.8/2, -3.8*(0-11.5)+3.8/2, 3.8*2*(4-3.5)*(3+.5)+3.8/2, -3.8*(6-11.5)-3.8/2);
    svline[1] = new TLine(3.8*2*(4-3.5)*(3+.5)+3.8/2, -3.8*(17-11.5)+3.8/2, 3.8*2*(4-3.5)*(3+.5)+3.8/2, -3.8*(23-11.5)-3.8/2);
    svline[2] = new TLine(3.8*2*(3-3.5)*(3+.5)-3.8/2, -3.8*(0-11.5)+3.8/2, 3.8*2*(3-3.5)*(3+.5)-3.8/2, -3.8*(6-11.5)-3.8/2);
    svline[3] = new TLine(3.8*2*(3-3.5)*(3+.5)-3.8/2, -3.8*(17-11.5)+3.8/2, 3.8*2*(3-3.5)*(3+.5)-3.8/2, -3.8*(23-11.5)-3.8/2);
  TLine * shline[4];
    shline[0] = new TLine(3.8*2*(4-3.5)*(4+.5)+3.8/2, -3.8*(7-11.5)-3.8/2, 3.8*2*(4-3.5)*(11+.5)+3.8/2, -3.8*(7-11.5)-3.8/2);
    shline[1] = new TLine(3.8*2*(4-3.5)*(4+.5)+3.8/2, -3.8*(15-11.5)-3.8/2, 3.8*2*(4-3.5)*(11+.5)+3.8/2, -3.8*(15-11.5)-3.8/2);
    shline[2] = new TLine(3.8*2*(3-3.5)*(4+.5)-3.8/2, -3.8*(7-11.5)-3.8/2, 3.8*2*(3-3.5)*(11+.5)-3.8/2, -3.8*(7-11.5)-3.8/2);
    shline[3] = new TLine(3.8*2*(3-3.5)*(4+.5)-3.8/2, -3.8*(15-11.5)-3.8/2, 3.8*2*(3-3.5)*(11+.5)-3.8/2, -3.8*(15-11.5)-3.8/2);
  TLine * ibox[4];
    ibox[0] = new TLine(-5*3.8,5*3.8,5*3.8,5*3.8);
    ibox[1] = new TLine(5*3.8,5*3.8,5*3.8,-5*3.8);
    ibox[2] = new TLine(5*3.8,-5*3.8,-5*3.8,-5*3.8);
    ibox[3] = new TLine(-5*3.8,-5*3.8,-5*3.8,5*3.8);
  TLine * obox[4];
    obox[0] = new TLine(-12*3.8,12*3.8,12*3.8,12*3.8);
    obox[1] = new TLine(12*3.8,12*3.8,12*3.8,-12*3.8);
    obox[2] = new TLine(12*3.8,-12*3.8,-12*3.8,-12*3.8);
    obox[3] = new TLine(-12*3.8,-12*3.8,-12*3.8,12*3.8);
  char wname[32];
  vline->SetLineColor(kBlack);
  hline->SetLineColor(kBlack);
  vline->SetLineWidth(2.5);
  hline->SetLineWidth(2.5);

  hvtr->Project("large_alpha","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","alpha*((nstb==1||nstb==2)&&chisq>0)");
  hvtr->Project("small_alpha","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","alpha*((nstb==3||nstb==4)&&chisq>0)");
  hvtr->Project("large_scale","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","scale*((nstb==1||nstb==2)&&chisq>0)");
  hvtr->Project("small_scale","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","scale*((nstb==3||nstb==4)&&chisq>0)");
  hvtr->Project("large_chisq","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(chisq/ndf)*(nstb==1||nstb==2)");
  hvtr->Project("small_chisq","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(chisq/ndf)*(nstb==3||nstb==4)");

  hvtr->Project("alpha_dist_large_psu_and_res","alpha","(cell_type==\"large_psu\"||cell_type==\"large_resistive\")&&chisq>0");
  hvtr->Project("alpha_dist_large_fermi","alpha","cell_type==\"large_fermi\"&&chisq>0");
  hvtr->Project("alpha_dist_small_russian","alpha","cell_type==\"small_russian\"&&chisq>0");
  hvtr->Project("alpha_dist_small_yale","alpha","cell_type==\"small_yale\"&&chisq>0");
  alpha_dist_large_psu_and_res->Fit("gaus","Q","",alpha_min,alpha_max_large);
  alpha_dist_large_fermi->Fit("gaus","Q","",alpha_min,alpha_max_large);
  alpha_dist_small_russian->Fit("gaus","Q","",alpha_min,alpha_max_small);
  alpha_dist_small_yale->Fit("gaus","Q","",alpha_min,alpha_max_small);

  char outfile_n[64];
  strcpy(outfile_n,"gain_file_params.root");
  TFile * outfile = new TFile(outfile_n,"RECREATE");

  // draw
  TCanvas * alpha_canv_small = new TCanvas("alpha_canv_small","alpha_canv_small",950,720); 
  small_alpha->Draw("zcol");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  alpha_canv_small->SetGrid(0,0);
  alpha_canv_small->Write();

  TCanvas * alpha_canv_large = new TCanvas("alpha_canv_large","alpha_canv_large",950,720); 
  large_alpha->Draw("zcol");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  alpha_canv_large->SetGrid(0,0);
  alpha_canv_large->Write();

  TCanvas * scale_canv_small = new TCanvas("scale_canv_small","scale_canv_small",950,720); 
  scale_canv_small->SetLogz();
  small_scale->Draw("zcol");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  scale_canv_small->SetGrid(0,0);
  scale_canv_small->Write();

  TCanvas * scale_canv_large = new TCanvas("scale_canv_large","scale_canv_large",950,720); 
  scale_canv_large->SetLogz();
  large_scale->Draw("zcol");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  scale_canv_large->SetGrid(0,0);
  scale_canv_large->Write();

  TCanvas * chisq_canv_small = new TCanvas("chisq_canv_small","chisq_canv_small",950,720); 
  small_chisq->Draw("zcol");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  chisq_canv_small->SetGrid(0,0);
  chisq_canv_small->Write();

  TCanvas * chisq_canv_large = new TCanvas("chisq_canv_large","chisq_canv_large",950,720); 
  large_chisq->Draw("zcol");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  chisq_canv_large->SetGrid(0,0);
  chisq_canv_large->Write();
  alpha_dist_large_psu_and_res->Write();
  alpha_dist_large_fermi->Write();
  alpha_dist_small_russian->Write();
  alpha_dist_small_yale->Write();

  printf("%s created\n",outfile_n);
};

