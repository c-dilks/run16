void hv_scan()
{
  gStyle->SetOptFit(1);

  // ====================================================================
 
  // curves for bad fits. A fit is considered bad if alpha is far from
  // it's expected value. In this case, alpha is fixed to this expected
  // value, and the scale factor is then fit for
  const Double_t expect_alpha_large = 12.23;
  const Double_t expect_alpha_russian = 3.93;
  const Double_t expect_alpha_yale = 7.80;
  // alpha from fit must be within range expect_alpha +/- range_alpha
  const Double_t range_alpha_large = 4;
  const Double_t range_alpha_russian = 2;
  const Double_t range_alpha_yale = 2;

  // ====================================================================

  // runnum <--> HV settings
  /*
  // MAGNET OFF
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=15353003; largehv[0]=1.2; smallrdac[0]=0xA0; // not necessarily correct, only NSTB 2&4 were on
  */
  /*
  // MAGNET OFF
  const Int_t NUM = 5;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16017058; largehv[0]=1.1; smallrdac[0]=0x90;
  runnum[1]=16017054; largehv[1]=1.2; smallrdac[1]=0xA0;
  runnum[2]=16017055; largehv[2]=1.3; smallrdac[2]=0xB0;
  runnum[3]=16017056; largehv[3]=1.4; smallrdac[3]=0xC0;
  runnum[4]=16017057; largehv[4]=1.5; smallrdac[4]=0xD0;
  */
  /*
  // MAGNET OFF
  const Int_t NUM = 13;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16020005; largehv[0]=1.10; smallrdac[0]=0xA0;
  runnum[1]=16020006; largehv[1]=1.15; smallrdac[1]=0xA8;
  runnum[2]=16020004; largehv[2]=1.20; smallrdac[2]=0xB0;
  runnum[3]=16020007; largehv[3]=1.25; smallrdac[3]=0xB8;
  runnum[4]=16020008; largehv[4]=1.30; smallrdac[4]=0xC0;
  runnum[5]=16020009; largehv[5]=1.35; smallrdac[5]=0xC8;
  runnum[6]=16020010; largehv[6]=1.40; smallrdac[6]=0xD0;
  runnum[7]=16020011; largehv[7]=1.45; smallrdac[7]=0xD8;
  runnum[8]=16020012; largehv[8]=1.50; smallrdac[8]=0xE0;    // DISREGARD NSTB==4 // (lost communication)
  runnum[9]=16020013; largehv[9]=1.55; smallrdac[9]=0xE8;    // DISREGARD NSTB==4 // (lost communication)
  runnum[10]=16020014; largehv[10]=1.60; smallrdac[10]=0xF0; // DISREGARD NSTB==4 // (lost communication)
  runnum[11]=16020015; largehv[11]=1.60; smallrdac[11]=0xF8; // DISREGARD NSTB==4 // (lost communication)
  runnum[12]=16020016; largehv[12]=1.60; smallrdac[12]=0xFF; // DISREGARD NSTB==4 // (lost communication)
  */
  /*
  // MAGNET ON
  const Int_t NUM = 13;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16021065; largehv[0]=1.10; smallrdac[0]=0xA0;
  runnum[1]=16021066; largehv[1]=1.15; smallrdac[1]=0xA8;
  runnum[2]=16021067; largehv[2]=1.20; smallrdac[2]=0xB0; //
  runnum[3]=16021068; largehv[3]=1.25; smallrdac[3]=0xB8;
  runnum[4]=16021069; largehv[4]=1.30; smallrdac[4]=0xC0;
  runnum[5]=16021070; largehv[5]=1.35; smallrdac[5]=0xC8; //
  runnum[6]=16021071; largehv[6]=1.40; smallrdac[6]=0xD0;
  runnum[7]=16021072; largehv[7]=1.45; smallrdac[7]=0xD8;
  runnum[8]=16021073; largehv[8]=1.50; smallrdac[8]=0xE0; //
  runnum[9]=16021074; largehv[9]=1.55; smallrdac[9]=0xE8;
  runnum[10]=16021075; largehv[10]=1.60; smallrdac[10]=0xF0;
  runnum[11]=16021076; largehv[11]=1.65; smallrdac[11]=0xF8; //
  runnum[12]=16021077; largehv[12]=1.70; smallrdac[12]=0xFF;
  */
  /*
  // MAGNET OFF
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16037091; largehv[0]=1.30; smallrdac[0]=0xA0;
  */
  /*
  // MAGNET ON
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16042057; largehv[0]=1.30; smallrdac[0]=0xA0;
  */
  /*
  // MAGNET ON
  const Int_t NUM = 16;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16041163; largehv[0]=1.750; smallrdac[0]=0xF0;
  runnum[1]=16041164; largehv[1]=1.700; smallrdac[1]=0xFF;
  runnum[2]=16041165; largehv[2]=1.650; smallrdac[2]=0xF8;
  runnum[3]=16041166; largehv[3]=1.600; smallrdac[3]=0xF0;
  runnum[4]=16041167; largehv[4]=1.550; smallrdac[4]=0xE8;
  runnum[5]=16041168; largehv[5]=1.500; smallrdac[5]=0xE0;
  runnum[6]=16041169; largehv[6]=1.450; smallrdac[6]=0xD8;
  runnum[7]=16041170; largehv[7]=1.400; smallrdac[7]=0xD0;
  runnum[8]=16041171; largehv[8]=1.350; smallrdac[8]=0xC8;
  runnum[9]=16041172; largehv[9]=1.300; smallrdac[9]=0xC0;
  runnum[10]=16041173; largehv[10]=1.250; smallrdac[10]=0xB8;
  runnum[11]=16041174; largehv[11]=1.200; smallrdac[11]=0xB0;
  runnum[12]=16041175; largehv[12]=1.150; smallrdac[12]=0xA8;
  runnum[13]=16041176; largehv[13]=1.100; smallrdac[13]=0xA0;
  runnum[14]=16041177; largehv[14]=1.050; smallrdac[14]=0x98;
  runnum[15]=16041178; largehv[15]=1.000; smallrdac[15]=0x90;
  */
  /*
  // MAGNET ON
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16062061; largehv[0]=1.40; smallrdac[0]=0xA0;
  */
  /*
  // MAGNET ON
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16112024; largehv[0]=1.40; smallrdac[0]=0xA0; // (@ iteration values)
  */
  ///*
  // MAGNET OFF
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16133072; largehv[0]=1.40; smallrdac[0]=0xA0; // (@ iteration values)
  //*/
  
  /*
  // MAGNET ON
  const Int_t NUM = 1;
  Int_t runnum[NUM];
  Double_t largehv[NUM]; // in kV
  Int_t smallrdac[NUM]; // software value {0x00-0xFF} (maps to voltage value)
  runnum[0]=16125028; largehv[0]=1.40; smallrdac[0]=0xA0; // (@ iteration values)
  */
  
  // ====================================================================

  // convert small cell rdac value to HV setpoint (in kV)
  gROOT->LoadMacro("small_cell_LUT.C");
  Double_t smallhv[NUM]; // small cell HV setpoint [kV]
  for(Int_t i=0; i<NUM; i++) smallhv[i]=(small_cell_LUT(smallrdac[i]))/1000.;


  // open adc trees
  TFile * adcfile[NUM];
  char adcfile_n[NUM][64];
  TTree * adctr[NUM];
  for(Int_t r=0; r<NUM; r++)
  {
    sprintf(adcfile_n[r],"%d.1/adcTr.root",runnum[r]);
    adcfile[r] = new TFile(adcfile_n[r],"READ");
    adctr[r] = (TTree*) adcfile[r]->Get("Tr_adc");
    printf("run=%d largehv=-%.2fkV smallrdac=%X smallhv=%.3f entries=%d\n",
      runnum[r],largehv[r],smallrdac[r],smallhv[r],adctr[r]->GetEntries());
  };


  // open geotr
  TFile * geofile = new TFile("geotr.root","READ");
  TTree * geotr = (TTree*) geofile->Get("geotr");
  Int_t nstb,row,col,chan;
  char cell_type[32];
  geotr->SetBranchAddress("row",&row);
  geotr->SetBranchAddress("col",&col);
  geotr->SetBranchAddress("nstb",&nstb);
  geotr->SetBranchAddress("chan",&chan);
  geotr->SetBranchAddress("cell_type",cell_type);


  // define output file & tree
  TFile * outfile = new TFile("hvtr.root","RECREATE");
  TTree * hvtr = new TTree("hvtr","hvtr");
  Double_t alpha,scale,chisq,ndf;
  Double_t alpha_arr[3];
  Double_t scale_arr[3];
  Double_t chisq_arr[3];
  Double_t ndf_arr[3];
  Int_t choice;
  Float_t Lhv,Shv;
  Double_t gaus_const,gaus_mean,gaus_sigma,gaus_chisq,gaus_ndf;
  Double_t dist_mean,dist_sigma;
  hvtr->Branch("nstb",&nstb,"nstb/I");
  hvtr->Branch("row",&row,"row/I");
  hvtr->Branch("col",&col,"col/I");
  hvtr->Branch("cell_type",cell_type,"cell_type/C");
  hvtr->Branch("scale",&scale,"scale/D"); // gain curve fit: ADC = scale*V^alpha
  hvtr->Branch("alpha",&alpha,"alpha/D");
  hvtr->Branch("chisq",&chisq,"chisq/D");
  hvtr->Branch("ndf",&ndf,"ndf/D");
  TTree * adcdisttr = new TTree("adcdisttr","adcdisttr");
  adcdisttr->Branch("nstb",&nstb,"nstb/I");
  adcdisttr->Branch("row",&row,"row/I");
  adcdisttr->Branch("col",&col,"col/I");
  adcdisttr->Branch("cell_type",cell_type,"cell_type/C");
  adcdisttr->Branch("Lhv",&Lhv,"Lhv/F"); // large cell voltage setpoint
  adcdisttr->Branch("Shv",&Shv,"Shv/F"); // small cell voltage setpoint
  adcdisttr->Branch("dist_mean",&dist_mean,"dist_mean/D"); // distribution mean
  adcdisttr->Branch("dist_sigma",&dist_sigma,"dist_sigma/D"); // distribution rms
  adcdisttr->Branch("gaus_const",&gaus_const,"gaus_const/D"); // height of gaussian fit
  adcdisttr->Branch("gaus_mean",&gaus_mean,"gaus_mean/D"); // mean of gaussian fit
  adcdisttr->Branch("gaus_sigma",&gaus_sigma,"gaus_sigma/D"); // sigma of gaussian fit
  adcdisttr->Branch("gaus_chisq",&gaus_chisq,"gaus_chisq/D"); // chisq of gaussian fit
  adcdisttr->Branch("gaus_ndf",&gaus_ndf,"gaus_ndf/D"); // ndf of gaussian fit


  // loop through FMS cells
  Int_t sf=3;
  Int_t factor;
  TCanvas * adccanv = new TCanvas("adccanv","adccanv",sf*NUM*200,sf*200);
  TCanvas * gaincanv = new TCanvas("gaincanv","gaincanv",1000,1000);
  TCanvas * fitcanv = new TCanvas("fitcanv","fitanv",500,500); // for fitting
  Int_t cdno;
  Int_t canv_row=1;
  Int_t page=1;
  TH1D * adcdist[4][34][17][NUM];
  char adcdist_n[4][34][17][NUM][64];
  char cellcut[256];
  TGraphErrors * gaingr[4][34][17];
  TF1 * gaingr_fit[4][34][17];
  TF1 * gaingr_fitL[4][34][17]; // left half fit
  TF1 * gaingr_fitA[4][34][17]; // all points
  TF1 * gaingr_fitR[4][34][17]; // right half fit
  char gaingr_fit_n[4][34][17][128];
  char gaingr_fitL_n[4][34][17][128];
  char gaingr_fitA_n[4][34][17][128];
  char gaingr_fitR_n[4][34][17][128];
  char gaingr_n[4][34][17][64];
  Int_t gaingr_i[4][34][17];
  Double_t hv,hv_low,hv_high,hv_low_small,hv_low_large,hv_high_small,hv_high_large;
  Double_t hv_mid,hv_midcalc_low,hv_midcalc_high;
  Int_t ent = geotr->GetEntries();
  char printname[64];
  Double_t distmaxloc,distrms;
  Double_t expect_alpha,range_alpha;
  Int_t distmaxbin;
  char fit_param_txt[4][34][17][256];
  char better_str[16];
  char titlemod[256];
  TLatex * choice_tex[4][34][17];
  Color_t choice_color[3] = {kRed,kGreen+1,kBlue};
  hv_low_small = 3000;
  hv_low_large = 3000;
  hv_high_small = 0;
  hv_high_large = 0;
  for(Int_t i=0; i<NUM; i++)
  {
    hv_low_small = (smallhv[i] < hv_low_small) ? smallhv[i]:hv_low_small;
    hv_low_large = (largehv[i] < hv_low_large) ? largehv[i]:hv_low_large;
    hv_high_small = (smallhv[i] > hv_high_small) ? smallhv[i]:hv_high_small;
    hv_high_large = (largehv[i] > hv_high_large) ? largehv[i]:hv_high_large;
  };

  // -------------- FMS CHANNEL LOOP -------------------- //
  for(Int_t i=0; i<ent; i++)
  {
    // -- DEBUG --
    /*
      if(i==0) i=370;
      if(i==390) i=400;
      if(i==420) i=800;
      if(i==820) i=1100;
      if(i==1120) i=1263;
    */
    // -- END DEBUG --
    geotr->GetEntry(i);
    printf("%d %d %d [%d]\n",nstb,row,col,chan);

    // set alpha expected values based on cell type
    // (only caring about large cells, small russian cells, small yale cells
    if(nstb==1 || nstb==2)
    {
      expect_alpha = expect_alpha_large;
      range_alpha = range_alpha_large;
    }
    else
    {
      if(!strcmp(cell_type,"small_russian"))
      {
        expect_alpha = expect_alpha_russian;
        range_alpha = range_alpha_russian;
      }
      else if(!strcmp(cell_type,"small_yale"))
      {
        expect_alpha = expect_alpha_yale;
        range_alpha = range_alpha_yale;
      };
    };

    // define ADC vs. V plots 
    if(nstb==1||nstb==2) factor=17;
    else factor=12;
    sprintf(gaingr_n[nstb-1][row][col],"ADC_vs_V_n%d_ch%d_r%d_c%d (fit: ADC=cV^{#alpha})",
      nstb,col+row*factor+1,row,col);
    gaingr[nstb-1][row][col] = new TGraphErrors();
    gaingr[nstb-1][row][col]->SetName(gaingr_n[nstb-1][row][col]);
    gaingr[nstb-1][row][col]->SetTitle(gaingr_n[nstb-1][row][col]);
    gaingr[nstb-1][row][col]->SetMarkerStyle(kFullCircle);
    sprintf(gaingr_fit_n[nstb-1][row][col],"gaingr_fit_n%d_ch%d_r%d_c%d",
      nstb,col+row*factor+1,row,col);
    sprintf(gaingr_fitL_n[nstb-1][row][col],"gaingr_fitL_n%d_ch%d_r%d_c%d",
      nstb,col+row*factor+1,row,col);
    sprintf(gaingr_fitA_n[nstb-1][row][col],"gaingr_fitA_n%d_ch%d_r%d_c%d",
      nstb,col+row*factor+1,row,col);
    sprintf(gaingr_fitR_n[nstb-1][row][col],"gaingr_fitR_n%d_ch%d_r%d_c%d",
      nstb,col+row*factor+1,row,col);
    if(nstb==1||nstb==2) { hv_low=hv_low_large-0.1; hv_high=hv_high_large+0.1; }
    else {hv_low=hv_low_small-0.1; hv_high=hv_high_small+0.1; };
    hv_midcalc_low=hv_high;
    hv_midcalc_high=hv_low;
    
    // ================== GAIN CURVE FIT FUNCTIONS =================== //

    // power law fit
    gaingr_fit[nstb-1][row][col] = new TF1(gaingr_fit_n[nstb-1][row][col],"[0]*x^[1]",hv_low,hv_high);
    gaingr_fitL[nstb-1][row][col] = new TF1(gaingr_fitL_n[nstb-1][row][col],"[0]*x^[1]",hv_low,hv_high);
    gaingr_fitA[nstb-1][row][col] = new TF1(gaingr_fitA_n[nstb-1][row][col],"[0]*x^[1]",hv_low,hv_high);
    gaingr_fitR[nstb-1][row][col] = new TF1(gaingr_fitR_n[nstb-1][row][col],"[0]*x^[1]",hv_low,hv_high);
    if(nstb==1||nstb==2)  
    {
      gaingr_fit[nstb-1][row][col]->SetParameters(1,8);
      gaingr_fitL[nstb-1][row][col]->SetParameters(1,8);
      gaingr_fitA[nstb-1][row][col]->SetParameters(1,8);
      gaingr_fitR[nstb-1][row][col]->SetParameters(1,8);
    }
    else 
    {
      gaingr_fit[nstb-1][row][col]->SetParameters(1,4);
      gaingr_fitL[nstb-1][row][col]->SetParameters(1,4);
      gaingr_fitA[nstb-1][row][col]->SetParameters(1,4);
      gaingr_fitR[nstb-1][row][col]->SetParameters(1,4);
    };

    gaingr_fit[nstb-1][row][col]->SetParLimits(1,1,30);
    gaingr_fitL[nstb-1][row][col]->SetParLimits(1,1,30);
    gaingr_fitA[nstb-1][row][col]->SetParLimits(1,1,30);
    gaingr_fitR[nstb-1][row][col]->SetParLimits(1,1,30);

    gaingr_fit[nstb-1][row][col]->SetParName(0,"c");
    gaingr_fit[nstb-1][row][col]->SetParName(1,"#alpha");
    gaingr_fitL[nstb-1][row][col]->SetParName(0,"c_{L}");
    gaingr_fitL[nstb-1][row][col]->SetParName(1,"#alpha_{L}");
    gaingr_fitA[nstb-1][row][col]->SetParName(0,"c_{A}");
    gaingr_fitA[nstb-1][row][col]->SetParName(1,"#alpha_{A}");
    gaingr_fitR[nstb-1][row][col]->SetParName(0,"c_{R}");
    gaingr_fitR[nstb-1][row][col]->SetParName(1,"#alpha_{R}");

    
    // e^quadratic fit -- DEPRECATED
    /*
    gaingr_fit[nstb-1][row][col] =
      new TF1(gaingr_fit_n[nstb-1][row][col],"exp([0]*[1]*x+[2]*x^2)",hv_low,hv_high);
    gaingr_fit[nstb-1][row][col]->SetParameters(3.,0.01,0.00005);
    gaingr_fit[nstb-1][row][col]->SetParLimits(0,1e-10,100);
    gaingr_fit[nstb-1][row][col]->SetParLimits(1,1e-10,100);
    gaingr_fit[nstb-1][row][col]->SetParLimits(2,1e-10,100);
    */

    // =============================================================== //


    // loop through HV settings
    gaingr_i[nstb-1][row][col] = 0;
    for(Int_t r=0; r<NUM; r++)
    {
      // project ADC distribution and fit to Gaussian
      printf(" %.2f 0x%X\n",largehv[r],smallrdac[r]);
      sprintf(adcdist_n[nstb-1][row][col][r],"adcdist_n%d_ch%d_r%d_c%d_hv%d%X",
        nstb,col+row*factor+1,row,col,(Int_t)1000*largehv[r],smallrdac[r]);
      adcdist[nstb-1][row][col][r] = new TH1D(adcdist_n[nstb-1][row][col][r],
        adcdist_n[nstb-1][row][col][r],4096,0,4096);
      sprintf(cellcut,"nstbADC==%d&&rowADC==%d&&colADC==%d",nstb,row,col);
      adctr[r]->Project(adcdist_n[nstb-1][row][col][r],"ADC",cellcut);
      fitcanv->Clear();
      fitcanv->cd();
      Lhv=largehv[r];
      Shv=smallrdac[r];
      if(adcdist[nstb-1][row][col][r]->GetEntries())
      {
        //adcdist[nstb-1][row][col][r]->Fit("gaus","Q","",0,4096);
        distmaxbin = adcdist[nstb-1][row][col][r]->GetMaximumBin();
        distmaxloc = adcdist[nstb-1][row][col][r]->GetBinCenter(distmaxbin);
        distrms = adcdist[nstb-1][row][col][r]->GetRMS();
        adcdist[nstb-1][row][col][r]->Fit("gaus","Q","",distmaxloc-4*distrms,distmaxloc+4*distrms);
        gaus_const = adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(0);
        gaus_mean = adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(1);
        gaus_sigma = adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(2);
        gaus_chisq = adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetChisquare();
        gaus_ndf = adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetNDF();
        dist_mean = adcdist[nstb-1][row][col][r]->GetMean();
        dist_sigma = distrms;
        adcdisttr->Fill();
      };

      // add point to ADC vs. HV gain curve graph
      if(adcdist[nstb-1][row][col][r]->GetFunction("gaus"))
      {
        // points are added to gain curves given the following constraints:
        // -- upper limit is in place to remove saturated ADC counts from fit
        // -- lower limit is in place to remove low gain junk
        // -- mean error must be less than mean
        if(adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(1) > 10 &&
           adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(1) <= 3800 &&
           adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(1) >
           adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParError(1)) 
        {
          if(nstb==1||nstb==2) hv=largehv[r];
          else hv=smallhv[r];

          // NSTB==4 LOST COMMUNICATION RUNS 020012-16; THIS FILTERS IT OUT (FILTER DISABLED)
          // to enable filter, place the following if statement:
          // if(!(r>=8 && nstb==4)) { around SetPoint & SetPointError & gaingr_i++ lines }
          
          gaingr[nstb-1][row][col]->SetPoint(gaingr_i[nstb-1][row][col],hv,
            adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParameter(1));
          gaingr[nstb-1][row][col]->SetPointError(gaingr_i[nstb-1][row][col],0,
            adcdist[nstb-1][row][col][r]->GetFunction("gaus")->GetParError(1));
          (gaingr_i[nstb-1][row][col])++;

          hv_midcalc_low = (hv < hv_midcalc_low) ? hv:hv_midcalc_low;
          hv_midcalc_high = (hv > hv_midcalc_high) ? hv:hv_midcalc_high;
        };
      };

      // draw ADC dists to canvas
      cdno=(canv_row-1)*NUM+r+canv_row;
      if(cdno==1) 
      {
        adccanv->Clear();
        adccanv->Divide(NUM,1);
      };
      //printf("--- %d %d %d %d %d %p\n",cdno,nstb-1,row,col,r,(void*)(adccanv->GetPad(cdno)));
      adccanv->GetPad(cdno)->SetLogx();
      adccanv->GetPad(cdno)->SetLogy();
      adccanv->GetPad(cdno)->cd();
      adcdist[nstb-1][row][col][r]->Draw();
      //adcdist[nstb-1][row][col][r]->Write();
    };
    hv_mid = (hv_midcalc_low+hv_midcalc_high)/2.0;

    // fit ADC vs. HV gain curves and fill hvtr tree
    gaincanv->cd();
    gaincanv->SetLogy();
    gaincanv->SetGrid(1,1);

    // fit left half & right half of HV range separately, and choose the one with the
    // better chisq to be the gain curve; this technique helps to avoid the cases where
    // an outlier point draws the fit away from the trending data points
    if(gaingr_i[nstb-1][row][col])
    {
      // fit left half (L), right half (R) and all points (A)
      gaingr[nstb-1][row][col]->Fit(gaingr_fitL[nstb-1][row][col],"MQN","",hv_low,hv_mid); 
      gaingr[nstb-1][row][col]->Fit(gaingr_fitA[nstb-1][row][col],"MQN","",hv_low,hv_high); 
      gaingr[nstb-1][row][col]->Fit(gaingr_fitR[nstb-1][row][col],"MQN","",hv_mid,hv_high); 

      // parameter, chisq, and ndf "array", where array index is
      //  0 for L (left half fit)
      //  1 for A (all points fit)
      //  2 for R (right half fit)
      scale_arr[0] = gaingr_fitL[nstb-1][row][col]->GetParameter(0);
      alpha_arr[0] = gaingr_fitL[nstb-1][row][col]->GetParameter(1);
      chisq_arr[0] = gaingr_fitL[nstb-1][row][col]->GetChisquare();
      ndf_arr[0] = gaingr_fitL[nstb-1][row][col]->GetNDF();
      scale_arr[1] = gaingr_fitA[nstb-1][row][col]->GetParameter(0);
      alpha_arr[1] = gaingr_fitA[nstb-1][row][col]->GetParameter(1);
      chisq_arr[1] = gaingr_fitA[nstb-1][row][col]->GetChisquare();
      ndf_arr[1] = gaingr_fitA[nstb-1][row][col]->GetNDF();
      scale_arr[2] = gaingr_fitR[nstb-1][row][col]->GetParameter(0);
      alpha_arr[2] = gaingr_fitR[nstb-1][row][col]->GetParameter(1);
      chisq_arr[2] = gaingr_fitR[nstb-1][row][col]->GetChisquare();
      ndf_arr[2] = gaingr_fitR[nstb-1][row][col]->GetNDF();

      // choose lowest chisq, but only if
      // - all points fit chisq is bad
      // - best chosen must be chisq>1
      // ==> Int_t choice is then the chosen array index; this is the "choice number"
      if(chisq_arr[1]>3000)
      {
        if(!(chisq_arr[0]>1) && !(chisq_arr[2]>1)) choice=1;
        else if(!(chisq_arr[0]>1)) choice=2;
        else if(!(chisq_arr[2]>1)) choice=0;
        else choice = (chisq_arr[0]/ndf_arr[0] < chisq_arr[2]/ndf_arr[2]) ? 0:2;
        choice = (chisq_arr[1]/ndf_arr[1] < chisq_arr[choice]/ndf_arr[choice]) ? 1:choice;
        //printf("----------- %.2f %.2f %.2f ---- choose %d\n",chisq_arr[0],chisq_arr[1],chisq_arr[2],choice);
      }
      else
      {
        choice=1;
        //printf("----------- %.2f %.2f %.2f ---- choose %d, since full chisq ok\n",chisq_arr[0],chisq_arr[1],chisq_arr[2],choice);
      };

      // set tree branch variables to the chosen values according to "choice number"
      scale = scale_arr[choice];
      alpha = alpha_arr[choice];
      chisq = chisq_arr[choice];
      ndf = ndf_arr[choice];

      // set gaingr limits & titles
      gaingr[nstb-1][row][col]->GetHistogram()->SetMaximum(1e5);
      gaingr[nstb-1][row][col]->GetHistogram()->SetMinimum(1e-1);
      gaingr[nstb-1][row][col]->GetXaxis()->SetLimits(hv_low,hv_high);
      gaingr[nstb-1][row][col]->GetXaxis()->SetTitle("voltage set point (kV)");
      gaingr[nstb-1][row][col]->GetYaxis()->SetTitle("mean ADC counts");

      // set TF1 colors
      gaingr_fitL[nstb-1][row][col]->SetLineColor(choice_color[0]);
      gaingr_fitA[nstb-1][row][col]->SetLineColor(choice_color[1]);
      gaingr_fitR[nstb-1][row][col]->SetLineColor(choice_color[2]);

      // now that we've chosen which gain curve to use, we fix the parameters for
      // gaingr_fit to the chosen parameters, and run TGraph::Fit with these
      // fixed parameters so they show up when the TGraph is drawn later
      gaingr_fit[nstb-1][row][col]->FixParameter(0,scale);
      gaingr_fit[nstb-1][row][col]->FixParameter(1,alpha);
      gaingr_fit[nstb-1][row][col]->SetLineColor(choice_color[choice]);
      gaingr[nstb-1][row][col]->Fit(gaingr_fit[nstb-1][row][col],"MQ","",hv_low,hv_high); 

      // draw the TGraph first so chosen fit parameters are drawn, then draw
      // the other three TF1's over the TGraph
      gaingr[nstb-1][row][col]->Draw("APE");
      gaingr_fitL[nstb-1][row][col]->Draw("same");
      gaingr_fitA[nstb-1][row][col]->Draw("same");
      gaingr_fitR[nstb-1][row][col]->Draw("same");

      choice_tex[nstb-1][row][col] = new TLatex(0.12,0.83,"#bullet");
      choice_tex[nstb-1][row][col]->SetNDC();
      choice_tex[nstb-1][row][col]->SetTextColor(choice_color[choice]);
      choice_tex[nstb-1][row][col]->Draw();
      
      // when either the left half fit or right half fit was chosen,
      // we change the x-axis title to be three floats: 
      // chisq/ndf for left half, all points, right half fits, respectively
      // --> this is for diagnosing why the all points fit wasn't chosen
      if(choice!=1)
      {
        sprintf(titlemod,"%.2f %.2f %.2f",chisq_arr[0]/ndf_arr[0],chisq_arr[1]/ndf_arr[1],chisq_arr[2]/ndf_arr[2]);
        gaingr[nstb-1][row][col]->GetXaxis()->SetTitle(titlemod);
      };
    }
    else
    {
      // set parameters to expected values for completely data-less channels
      gaincanv->Clear();
      alpha = expect_alpha;
      scale = 1;
      chisq = 0; 
      ndf = 0;
    };
    hvtr->Fill();

    //if(cdno==NUM*(NUM+1) || i+1==ent)

    if(cdno==NUM)
    {
      //if(page==1) adccanv->Print("gain_curves.pdf(","pdf");
      //else if(i+1==ent) adccanv->Print("gain_curves.pdf)","pdf");
      //else adccanv->Print("gain_curves.pdf","pdf");
      if(nstb==1||nstb==2) factor=17;
      else factor=12;
      sprintf(printname,"adc_dists/n%d_ch%d_r%d_c%d.png",nstb,col+row*factor+1,row,col);
      adccanv->Print(printname,"png");
      sprintf(printname,"gain_curves/n%d_ch%d_r%d_c%d.png",nstb,col+row*factor+1,row,col);
      gaincanv->Print(printname,"png");
      page++;
      canv_row=1;
    }
    else canv_row++;
  }; // end cell loop


  // write output
  hvtr->Write("hvtr");
  adcdisttr->Write("adcdisttr");
};
