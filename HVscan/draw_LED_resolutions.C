// draws resolution plots for LED runs; vs. HV setpoints

void draw_LED_resolutions(Int_t day=0)
{
  const Float_t RES_MAX = 0.3; // max resolution shown in plot
  char filename[32];
  if(day!=0) sprintf(filename,"hvtr_%d.root",day);
  else strcpy(filename,"hvtr.root");

  char extra_cuts[128];

  // voltage set points
  Int_t NUM,NUM_large,NUM_small,Shv_lb,Shv_ub;
  Double_t Lhv_lb,Lhv_ub;
  Double_t largehv[30];
  Int_t smallhv[30];
  if(day==353)
  {
    NUM=1;
    NUM_large = NUM;
    NUM_small = NUM;
    largehv[0]=1.2; smallhv[0]=0xA0; // not necessarily correct, only NSTB 2&4 were on
    Lhv_lb=largehv[0]-0.050;
    Lhv_ub=largehv[NUM-1]+0.050;
    Shv_lb=smallhv[0]-0x08;
    Shv_ub=smallhv[NUM-1]+0x08;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800 && (nstb==2||nstb==4)");
  }
  else if(day==17)
  {
    NUM=5;
    NUM_large = NUM;
    NUM_small = NUM;
    largehv[0]=1.1; smallhv[0]=0x90;
    largehv[1]=1.2; smallhv[1]=0xA0;
    largehv[2]=1.3; smallhv[2]=0xB0;
    largehv[3]=1.4; smallhv[3]=0xC0;
    largehv[4]=1.5; smallhv[4]=0xD0;
    Lhv_lb=largehv[0]-0.050;
    Lhv_ub=largehv[NUM-1]+0.050;
    Shv_lb=smallhv[0]-0x08;
    Shv_ub=smallhv[NUM-1]+0x08;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800");
  }
  else if(day==20)
  {
    NUM=13;
    NUM_large = 11;
    NUM_small = NUM;
    largehv[0]=1.10; smallhv[0]=0xA0;
    largehv[1]=1.15; smallhv[1]=0xA8;
    largehv[2]=1.20; smallhv[2]=0xB0;
    largehv[3]=1.25; smallhv[3]=0xB8;
    largehv[4]=1.30; smallhv[4]=0xC0;
    largehv[5]=1.35; smallhv[5]=0xC8;
    largehv[6]=1.40; smallhv[6]=0xD0;
    largehv[7]=1.45; smallhv[7]=0xD8;
    largehv[8]=1.50; smallhv[8]=0xE0;    // DISREGARD NSTB==4 // (lost communication)
    largehv[9]=1.55; smallhv[9]=0xE8;    // DISREGARD NSTB==4 // (lost communication)
    largehv[10]=1.60; smallhv[10]=0xF0; // DISREGARD NSTB==4 // (lost communication)
    largehv[11]=1.60; smallhv[11]=0xF8; // DISREGARD NSTB==4 // (lost communication)
    largehv[12]=1.60; smallhv[12]=0xFF; // DISREGARD NSTB==4 // (lost communication)
    Lhv_lb=largehv[0]-0.025;
    Lhv_ub=largehv[NUM-1]+0.025;
    Shv_lb=smallhv[0]-0x04;
    Shv_ub=smallhv[NUM-1]+0x04;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800 && !(nstb==4&&Shv>=224) ");
  }
  else if(day==21)
  {
    NUM=13;
    NUM_large = NUM;
    NUM_small = NUM;
    largehv[0]=1.10; smallhv[0]=0xA0;
    largehv[1]=1.15; smallhv[1]=0xA8;
    largehv[2]=1.20; smallhv[2]=0xB0;
    largehv[3]=1.25; smallhv[3]=0xB8;
    largehv[4]=1.30; smallhv[4]=0xC0;
    largehv[5]=1.35; smallhv[5]=0xC8;
    largehv[6]=1.40; smallhv[6]=0xD0;
    largehv[7]=1.45; smallhv[7]=0xD8;
    largehv[8]=1.50; smallhv[8]=0xE0;
    largehv[9]=1.55; smallhv[9]=0xE8;
    largehv[10]=1.60; smallhv[10]=0xF0;
    largehv[11]=1.65; smallhv[11]=0xF8;
    largehv[12]=1.70; smallhv[12]=0xFF;
    Lhv_lb=largehv[0]-0.025;
    Lhv_ub=largehv[NUM-1]+0.025;
    Shv_lb=smallhv[0]-0x04;
    Shv_ub=smallhv[NUM-1]+0x04;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800");
  }
  else if(day==37 || day==38)
  {
    NUM=1;
    NUM_large = NUM;
    NUM_small = NUM;
    largehv[0]=1.30; smallhv[0]=0xA0;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800");
    Lhv_lb=largehv[0]-0.025;
    Lhv_ub=largehv[NUM-1]+0.025;
    Shv_lb=smallhv[0]-0x04;
    Shv_ub=smallhv[NUM-1]+0x04;
  }
  else if(day==41)
  {
    NUM=16;
    NUM_large = NUM;
    NUM_small = 15;
    largehv[0]=1.750; smallhv[0]=0xF0;
    largehv[1]=1.700; smallhv[1]=0xFF;
    largehv[2]=1.650; smallhv[2]=0xF8;
    largehv[3]=1.600; smallhv[3]=0xF0;
    largehv[4]=1.550; smallhv[4]=0xE8;
    largehv[5]=1.500; smallhv[5]=0xE0;
    largehv[6]=1.450; smallhv[6]=0xD8;
    largehv[7]=1.400; smallhv[7]=0xD0;
    largehv[8]=1.350; smallhv[8]=0xC8;
    largehv[9]=1.300; smallhv[9]=0xC0;
    largehv[10]=1.250; smallhv[10]=0xB8;
    largehv[11]=1.200; smallhv[11]=0xB0;
    largehv[12]=1.150; smallhv[12]=0xA8;
    largehv[13]=1.100; smallhv[13]=0xA0;
    largehv[14]=1.050; smallhv[14]=0x98;
    largehv[15]=1.000; smallhv[15]=0x90;
    Lhv_lb=1.000-0.025;
    Lhv_ub=1.750+0.025;
    Shv_lb=0x90-0x04;
    Shv_ub=0xFF+0x04;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800");
  }
  else if(day==49 || day==112 || day==125 || day==0)
  {
    NUM=1;
    NUM_large = NUM;
    NUM_small = NUM;
    largehv[0]=1.40; smallhv[0]=0xA0;
    strcpy(extra_cuts,"gaus_sigma<gaus_mean && gaus_mean>10 && gaus_mean<3800");
    Lhv_lb=largehv[0]-0.025;
    Lhv_ub=largehv[NUM-1]+0.025;
    Shv_lb=smallhv[0]-0x04;
    Shv_ub=smallhv[NUM-1]+0x04;
  }

  const Int_t NUMC_large = NUM_large;
  const Int_t NUMC_small = NUM_small;
  Int_t NUMC_tmp = (NUMC_large > NUMC_small) ? NUMC_large:NUMC_small;
  const Int_t NUMC = NUMC_tmp;



  // open adc dist tree and initialise histograms
  TFile * infile = new TFile(filename,"READ");
  TTree * tr = (TTree*) infile->Get("adcdisttr");
  TTree * hvtr = (TTree*) infile->Get("hvtr");

  TH1D * large_all_chisq = new TH1D("large_all_chisq",
    "#chi^{2}/NDF distribution -- all large cells",100,0,5);
  TH1D * large_psu_chisq = new TH1D("large_psu_chisq",
    "#chi^{2}/NDF distribution -- large cells with psu bases",100,0,5);
  TH1D * russian_chisq = new TH1D("russian_chisq",
    "#chi^{2}/NDF distribution -- russian cells",100,0,5);
  TH1D * yale_chisq = new TH1D("yale_chisq",
    "#chi^{2}/NDF distribution -- yale cells",100,0,5);

  TH2D * large_all_adcmean = new TH2D("large_all_adcmean",
    "LED ADC mean (#mu) vs. HV setpoint -- all large cells;HV setpoint (kV);ADC #mu",
    NUM_large,Lhv_lb,Lhv_ub,200,0,4096);
  TH2D * large_psu_adcmean = new TH2D("large_psu_adcmean",
    "LED ADC mean (#mu) vs. HV setpoint -- large cells with psu bases;HV setpoint (kV);ADC #mu",
    NUM_large,Lhv_lb,Lhv_ub,200,0,4096);
  TH2D * russian_adcmean = new TH2D("russian_adcmean",
    "LED ADC mean (#mu) vs. HV setpoint -- russian cells;HV setpoint [0x00-0xFF];ADC #mu",
    NUM_small,Shv_lb,Shv_ub,200,0,4096);
  TH2D * yale_adcmean = new TH2D("yale_adcmean",
    "LED ADC mean (#mu) vs. HV setpoint -- yale cells;HV setpoint [0x00-0xFF];ADC #mu",
    NUM_small,Shv_lb,Shv_ub,200,0,4096);

  TH2D * large_all_adcsigma = new TH2D("large_all_adcsigma",
    "LED ADC width (#sigma) vs. HV setpoint -- all large cells;HV setpoint (kV);ADC #sigma",
    NUM_large,Lhv_lb,Lhv_ub,2000,0,4096);
  TH2D * large_psu_adcsigma = new TH2D("large_psu_adcsigma",
    "LED ADC width (#sigma) vs. HV setpoint -- large cells with psu bases;HV setpoint (kV);ADC #sigma",
    NUM_large,Lhv_lb,Lhv_ub,2000,0,4096);
  TH2D * russian_adcsigma = new TH2D("russian_adcsigma",
    "LED ADC width (#sigma) vs. HV setpoint -- russian cells;HV setpoint [0x00-0xFF];ADC #sigma",
    NUM_small,Shv_lb,Shv_ub,2000,0,4096);
  TH2D * yale_adcsigma = new TH2D("yale_adcsigma",
    "LED ADC width (#sigma) vs. HV setpoint -- yale cells;HV setpoint [0x00-0xFF];ADC #sigma",
    NUM_small,Shv_lb,Shv_ub,2000,0,4096);

  TH2D * large_all_res = new TH2D("large_all_res",
    "LED resolution vs. HV setpoint -- all large cells;HV setpoint (kV);ADC #sigma/#mu",
    NUM_large,Lhv_lb,Lhv_ub,100,0,1);
  TH2D * large_psu_res = new TH2D("large_psu_res",
    "LED resolution vs. HV setpoint -- large cells with psu bases;HV setpoint (kV);ADC #sigma/#mu",
    NUM_large,Lhv_lb,Lhv_ub,100,0,1);
  TH2D * russian_res = new TH2D("russian_res",
    "LED resolution vs. HV setpoint -- russian cells;HV setpoint [0x00-0xFF];ADC #sigma/#mu",
    NUM_small,Shv_lb,Shv_ub,100,0,1);
  TH2D * yale_res = new TH2D("yale_res",
    "LED resolution vs. HV setpoint -- yale cells;HV setpoint [0x00-0xFF];ADC #sigma/#mu",
    NUM_small,Shv_lb,Shv_ub,100,0,1);


  TH2F * large_geom_res[NUMC];
  TH2F * small_geom_res[NUMC];
  char large_geom_res_n[NUMC][64];
  char small_geom_res_n[NUMC][64];
  char geom_res_t[NUMC][64];
  for(Int_t n=0; n<NUMC; n++)
  {
    sprintf(large_geom_res_n[n],"large_geom_res_%d_0x%X",largehv[n]*1000,smallhv[n]);
    sprintf(small_geom_res_n[n],"small_geom_res_%d_0x%X",largehv[n]*1000,smallhv[n]);
    sprintf(geom_res_t[n],"LED resolution L:%d S:0x%X",largehv[n]*1000,smallhv[n]);
    large_geom_res[n] = new TH2F(large_geom_res_n[n],geom_res_t[n],34,-98.6,98.6,34,-98.6,98.6);
    small_geom_res[n] = new TH2F(small_geom_res_n[n],geom_res_t[n],52,-98.6,98.6,52,-98.6,98.6);
    large_geom_res[n]->SetMinimum(0);
    small_geom_res[n]->SetMinimum(0);
    large_geom_res[n]->SetMaximum(RES_MAX);
    small_geom_res[n]->SetMaximum(RES_MAX);
  };
  TH2F* largetxt=new TH2F("largetxt","largetxt",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smalltxt=new TH2F("smalltxt","smalltxt",52,-98.6,98.6,52,-98.6,98.6);

  
  // cuts
  char large_all_cut[1024];
  char large_psu_cut[256];
  char russian_cut[256];
  char yale_cut[256];
  sprintf(large_all_cut,"(cell_type==\"large_psu\" || cell_type==\"large_fermi\" || cell_type==\"large_resistive\") && %s",extra_cuts);
  sprintf(large_psu_cut,"cell_type==\"large_psu\" && %s",extra_cuts);
  sprintf(russian_cut,"cell_type==\"small_russian\" && %s",extra_cuts);
  sprintf(yale_cut,"cell_type==\"small_yale\" && %s",extra_cuts);

  char large_geomcut[NUMC][256];
  char small_geomcut[NUMC][256];
  for(Int_t n=0; n<NUMC; n++)
  {
    sprintf(large_geomcut[n],"dist_sigma/dist_mean*((nstb==1||nstb==2) && abs(Lhv-%f)<0.001 && %s)",largehv[n],extra_cuts);
    sprintf(small_geomcut[n],"dist_sigma/dist_mean*((nstb==3||nstb==4) && Shv==%d && %s)",smallhv[n],extra_cuts);
  };


  // projections
  tr->Project("large_all_chisq","gaus_chisq/gaus_ndf",large_all_cut);
  tr->Project("large_psu_chisq","gaus_chisq/gaus_ndf",large_psu_cut);
  tr->Project("russian_chisq","gaus_chisq/gaus_ndf",russian_cut);
  tr->Project("yale_chisq","gaus_chisq/gaus_ndf",yale_cut);

  // USE GAUSSIAN SIGMA/MEAN
  /*
  tr->Project("large_all_adcmean","gaus_mean:Lhv",large_all_cut);
  tr->Project("large_psu_adcmean","gaus_mean:Lhv",large_psu_cut);
  tr->Project("russian_adcmean","gaus_mean:Shv",russian_cut);
  tr->Project("yale_adcmean","gaus_mean:Shv",yale_cut);

  tr->Project("large_all_adcsigma","gaus_sigma:Lhv",large_all_cut);
  tr->Project("large_psu_adcsigma","gaus_sigma:Lhv",large_psu_cut);
  tr->Project("russian_adcsigma","gaus_sigma:Shv",russian_cut);
  tr->Project("yale_adcsigma","gaus_sigma:Shv",yale_cut);

  tr->Project("large_all_res","gaus_sigma/gaus_mean:Lhv",large_all_cut);
  tr->Project("large_psu_res","gaus_sigma/gaus_mean:Lhv",large_psu_cut);
  tr->Project("russian_res","gaus_sigma/gaus_mean:Shv",russian_cut);
  tr->Project("yale_res","gaus_sigma/gaus_mean:Shv",yale_cut);
  */
  
  // USE DISTRIBUTION RMS/MEAN
  ///*
  tr->Project("large_all_adcmean","dist_mean:Lhv",large_all_cut);
  tr->Project("large_psu_adcmean","dist_mean:Lhv",large_psu_cut);
  tr->Project("russian_adcmean","dist_mean:Shv",russian_cut);
  tr->Project("yale_adcmean","dist_mean:Shv",yale_cut);

  tr->Project("large_all_adcsigma","dist_sigma:Lhv",large_all_cut);
  tr->Project("large_psu_adcsigma","dist_sigma:Lhv",large_psu_cut);
  tr->Project("russian_adcsigma","dist_sigma:Shv",russian_cut);
  tr->Project("yale_adcsigma","dist_sigma:Shv",yale_cut);

  tr->Project("large_all_res","dist_sigma/dist_mean:Lhv",large_all_cut);
  tr->Project("large_psu_res","dist_sigma/dist_mean:Lhv",large_psu_cut);
  tr->Project("russian_res","dist_sigma/dist_mean:Shv",russian_cut);
  tr->Project("yale_res","dist_sigma/dist_mean:Shv",yale_cut);
  //*/

  for(Int_t n=0; n<NUMC; n++)
  {
    tr->Project(large_geom_res_n[n],"-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)",large_geomcut[n]);
    tr->Project(small_geom_res_n[n],"-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)",small_geomcut[n]);
  };

  // geometry
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


  // profiles
  TProfile * large_all_adcmean_pfx = large_all_adcmean->ProfileX();
  TProfile * large_psu_adcmean_pfx = large_psu_adcmean->ProfileX();
  TProfile * russian_adcmean_pfx = russian_adcmean->ProfileX();
  TProfile * yale_adcmean_pfx = yale_adcmean->ProfileX();
  
  TProfile * large_all_adcsigma_pfx = large_all_adcsigma->ProfileX();
  TProfile * large_psu_adcsigma_pfx = large_psu_adcsigma->ProfileX();
  TProfile * russian_adcsigma_pfx = russian_adcsigma->ProfileX();
  TProfile * yale_adcsigma_pfx = yale_adcsigma->ProfileX();

  TProfile * large_all_res_pfx = large_all_res->ProfileX();
  TProfile * large_psu_res_pfx = large_psu_res->ProfileX();
  TProfile * russian_res_pfx = russian_res->ProfileX();
  TProfile * yale_res_pfx = yale_res->ProfileX();

  Double_t lwidth=2;

  large_all_adcmean_pfx->SetLineWidth(lwidth);
  large_psu_adcmean_pfx->SetLineWidth(lwidth);
  russian_adcmean_pfx->SetLineWidth(lwidth);
  yale_adcmean_pfx->SetLineWidth(lwidth);

  large_all_adcsigma_pfx->SetLineWidth(lwidth);
  large_psu_adcsigma_pfx->SetLineWidth(lwidth);
  russian_adcsigma_pfx->SetLineWidth(lwidth);
  yale_adcsigma_pfx->SetLineWidth(lwidth);

  large_all_res_pfx->SetLineWidth(lwidth);
  large_psu_res_pfx->SetLineWidth(lwidth);
  russian_res_pfx->SetLineWidth(lwidth);
  yale_res_pfx->SetLineWidth(lwidth);

  TFile * outfile = new TFile("res.root","RECREATE");

  // draw
  gStyle->SetOptStat(0);
  TCanvas * large_all_adcmean_canv = new TCanvas("large_all_adcmean_canv","large_all_adcmean_canv",600,600);
  large_all_adcmean_canv->SetLogz();
  large_all_adcmean_canv->SetGrid(1,1);
  large_all_adcmean->Draw("colz");
  large_all_adcmean_pfx->Draw("same");
  TCanvas * large_psu_adcmean_canv = new TCanvas("large_psu_adcmean_canv","large_psu_adcmean_canv",600,600);
  large_psu_adcmean_canv->SetLogz();
  large_psu_adcmean_canv->SetGrid(1,1);
  large_psu_adcmean->Draw("colz");
  large_psu_adcmean_pfx->Draw("same");
  TCanvas * russian_adcmean_canv = new TCanvas("russian_adcmean_canv","russian_adcmean_canv",600,600);
  russian_adcmean_canv->SetLogz();
  russian_adcmean_canv->SetGrid(1,1);
  russian_adcmean->Draw("colz");
  russian_adcmean_pfx->Draw("same");
  TCanvas * yale_adcmean_canv = new TCanvas("yale_adcmean_canv","yale_adcmean_canv",600,600);
  yale_adcmean_canv->SetLogz();
  yale_adcmean_canv->SetGrid(1,1);
  russian_adcmean->Draw("colz");
  yale_adcmean->Draw("colz");
  yale_adcmean_pfx->Draw("same");

  TCanvas * large_all_adcsigma_canv = new TCanvas("large_all_adcsigma_canv","large_all_adcsigma_canv",600,600);
  large_all_adcsigma_canv->SetLogz();
  large_all_adcsigma_canv->SetGrid(1,1);
  large_all_adcsigma->Draw("colz");
  large_all_adcsigma_pfx->Draw("same");
  large_all_adcsigma->GetYaxis()->SetRangeUser(0,500);
  TCanvas * large_psu_adcsigma_canv = new TCanvas("large_psu_adcsigma_canv","large_psu_adcsigma_canv",600,600);
  large_psu_adcsigma_canv->SetLogz();
  large_psu_adcsigma_canv->SetGrid(1,1);
  large_psu_adcsigma->Draw("colz");
  large_psu_adcsigma_pfx->Draw("same");
  large_psu_adcsigma->GetYaxis()->SetRangeUser(0,500);
  TCanvas * russian_adcsigma_canv = new TCanvas("russian_adcsigma_canv","russian_adcsigma_canv",600,600);
  russian_adcsigma_canv->SetLogz();
  russian_adcsigma_canv->SetGrid(1,1);
  russian_adcsigma->Draw("colz");
  russian_adcsigma_pfx->Draw("same");
  russian_adcsigma->GetYaxis()->SetRangeUser(0,500);
  TCanvas * yale_adcsigma_canv = new TCanvas("yale_adcsigma_canv","yale_adcsigma_canv",600,600);
  yale_adcsigma_canv->SetLogz();
  yale_adcsigma_canv->SetGrid(1,1);
  russian_adcsigma->Draw("colz");
  yale_adcsigma->Draw("colz");
  yale_adcsigma_pfx->Draw("same");
  yale_adcsigma->GetYaxis()->SetRangeUser(0,500);

  TCanvas * large_all_res_canv = new TCanvas("large_all_res_canv","large_all_res_canv",600,600);
  large_all_res_canv->SetLogz();
  large_all_res_canv->SetGrid(1,1);
  large_all_res->Draw("colz");
  large_all_res_pfx->Draw("same");
  large_all_res->GetYaxis()->SetRangeUser(0,RES_MAX);
  TCanvas * large_psu_res_canv = new TCanvas("large_psu_res_canv","large_psu_res_canv",600,600);
  large_psu_res_canv->SetLogz();
  large_psu_res_canv->SetGrid(1,1);
  large_psu_res->Draw("colz");
  large_psu_res_pfx->Draw("same");
  large_psu_res->GetYaxis()->SetRangeUser(0,RES_MAX);
  TCanvas * russian_res_canv = new TCanvas("russian_res_canv","russian_res_canv",600,600);
  russian_res_canv->SetLogz();
  russian_res_canv->SetGrid(1,1);
  russian_res->Draw("colz");
  russian_res_pfx->Draw("same");
  russian_res->GetYaxis()->SetRangeUser(0,RES_MAX);
  TCanvas * yale_res_canv = new TCanvas("yale_res_canv","yale_res_canv",600,600);
  yale_res_canv->SetLogz();
  yale_res_canv->SetGrid(1,1);
  russian_res->Draw("colz");
  yale_res->Draw("colz");
  yale_res_pfx->Draw("same");
  yale_res->GetYaxis()->SetRangeUser(0,RES_MAX);


  // write
  large_all_chisq->Write();
  large_psu_chisq->Write();
  russian_chisq->Write();
  yale_chisq->Write();

  large_all_adcmean_canv->Write();
  large_psu_adcmean_canv->Write();
  russian_adcmean_canv->Write();
  yale_adcmean_canv->Write();

  large_all_adcsigma_canv->Write();
  large_psu_adcsigma_canv->Write();
  russian_adcsigma_canv->Write();
  yale_adcsigma_canv->Write();

  large_all_res_canv->Write();
  large_psu_res_canv->Write();
  russian_res_canv->Write();
  yale_res_canv->Write();


  // draw geometry canvases with resolutions
  TCanvas * resolution_canv[NUMC];
  char resolution_canv_n[NUMC][32];
  for(Int_t n=0; n<NUMC; n++)
  {
    sprintf(resolution_canv_n[n],"resolution_canv_%d_0x%X",largehv[n]*1000,smallhv[n]);
    resolution_canv[n] = new TCanvas(resolution_canv_n[n],resolution_canv_n[n],950,720);
    large_geom_res[n]->Draw("zcol");
    small_geom_res[n]->Draw("zcolsame");
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
    resolution_canv[n]->SetGrid(0,0);
    resolution_canv[n]->Write();
  };

  printf("res.root created\n");
};
