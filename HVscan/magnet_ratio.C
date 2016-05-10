void magnet_ratio(Int_t runnum=16014037)
{
  // open file
  char infile_n[128];
  sprintf(infile_n,"%d.1/adcTr.root",runnum);
  TFile * geofile = new TFile("geotr.root","READ");
  TTree * geotr = (TTree*) geofile->Get("geotr");
  TFile * infile = new TFile(infile_n,"READ");
  TTree * tr = (TTree*) infile->Get("Tr_adc");
  Int_t row,col,ADC,nstb,evtnum;
  tr->SetBranchAddress("br_ADC",&ADC);
  tr->SetBranchAddress("br_rowADC",&row);
  tr->SetBranchAddress("br_colADC",&col);
  tr->SetBranchAddress("br_nstbADC",&nstb);
  tr->SetBranchAddress("br_evtnum",&evtnum);
  Int_t evtmax = tr->GetMaximum("evtnum");
  printf("-------%d\n",evtmax);


  // initialise hists
  TH1D * dd[4][34][17];
  char dd_n[4][34][17][64];
  for(Int_t n=0; n<4; n++)
  {
    for(Int_t r=0; r<34; r++)
    {
      for(Int_t c=0; c<17; c++)
      {
        sprintf(dd_n[n][r][c],"dd_n%d_r%d_c%d",n+1,r,c);
        dd[n][r][c] = new TH1D(dd_n[n][r][c],dd_n[n][r][c],evtmax+1,0,evtmax+1);
      };
    };
  };


  // loop through tree and fill hists
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    if(i%1000==0) printf("%.2f%%\n",i/((Float_t)(tr->GetEntries()))*100);
    tr->GetEntry(i);
    //printf("%d %d %d %p\n",nstb-1,row,col,(void*)dd[nstb-1][row][col]);
    //printf("n%d r%d c%d e%d a%d\n",nstb-1,row,col,evtnum+1,ADC);
    dd[nstb-1][row][col]->SetBinContent(evtnum+1,ADC);
  };


  // fms display
  TH2F* large_averat=new TH2F("large_averat","ave ADC(magnet=off)/ADC(magnet=on)",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_averat=new TH2F("small_averat","ave ADC(magnet=off)/ADC(magnet=on)",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_maxrat=new TH2F("large_maxrat","max ADC(magnet=off)/ADC(magnet=on)",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_maxrat=new TH2F("small_maxrat","max ADC(magnet=off)/ADC(magnet=on)",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_stdev_magon=new TH2F("large_stdev_magon","stdev/ave ADC(magnet=on)",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_stdev_magon=new TH2F("small_stdev_magon","stdev/ave ADC(magnet=on)",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_stdev_magoff=new TH2F("large_stdev_magoff","stdev ADC(magnet=off)",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_stdev_magoff=new TH2F("small_stdev_magoff","stdev ADC(magnet=off)",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_stdev_diff=new TH2F("large_stdev_diff","stdev/ave ADC(magnet=off) - stdev/ave ADC(magnet=on)",
    34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_stdev_diff=new TH2F("small_stdev_diff","stdev/ave ADC(magnet=off) - stdev/ave ADC(magnet=on)",
    52,-98.6,98.6,52,-98.6,98.6);
  TH2F* largetxt=new TH2F("largetxt","largetxt",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smalltxt=new TH2F("smalltxt","smalltxt",52,-98.6,98.6,52,-98.6,98.6);
  large_averat->SetMinimum(.1);
  large_averat->SetMaximum(4096);
  small_averat->SetMinimum(.1);
  small_averat->SetMaximum(4096);
  large_maxrat->SetMinimum(.1);
  large_maxrat->SetMaximum(4096);
  small_maxrat->SetMinimum(.1);
  small_maxrat->SetMaximum(4096);
  geotr->Project("largetxt","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(col+row*17+1)*(nstb==1||nstb==2)");
  geotr->Project("smalltxt","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(col+row*12+1)*(nstb==3||nstb==4)");
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


  // compute ADC(magnet=off)/ADC(magnet=on) ratios for each cell, 
  // and add to FMS display
  
  Int_t evt_l_lb=1;    // event no. bounds
  Int_t evt_l_ub=50;
  Int_t evt_h_lb=950;
  Int_t evt_h_ub=1000;

  Double_t magrat[4][34][17];
  Int_t count_l;
  Double_t sum_l,ave_l,max_l,ssq_l,stdev_l;
  Int_t count_h;
  Double_t sum_h,ave_h,max_h,ssq_h,stdev_h;
  Double_t bc;
  Int_t binn;
  Double_t stdev_l_MAX,stdev_h_MAX;
  stdev_l_MAX=0;
  stdev_h_MAX=0;
  for(Int_t n=0; n<4; n++)
  {
    for(Int_t r=0; r<34; r++)
    {
      for(Int_t c=0; c<17; c++)
      {
        count_l=0;
        sum_l=0;
        ave_l=0;
        count_h=0;
        sum_h=0;
        ave_h=0;
        max_l=0;
        max_h=0;
        ssq_l=0;
        ssq_h=0;
        stdev_l = 0;
        stdev_h = 0;

        for(Int_t b=evt_l_lb; b<=evt_l_ub; b++)
        {
          bc = dd[n][r][c]->GetBinContent(b);
          if(bc>0)
          {
            sum_l+=bc;
            count_l++;
            max_l=(bc>max_l) ? bc:max_l;
          };
        };
        if(count_l>0) 
        {
          ave_l=sum_l/count_l;
          for(Int_t b=evt_l_lb; b<=evt_l_ub; b++)
          {
            bc = dd[n][r][c]->GetBinContent(b);
            ssq_l += pow(bc-ave_l,2);
          };
          stdev_l = sqrt(ssq_l/count_l);
          stdev_l_MAX = (stdev_l/ave_l>stdev_l_MAX) ? stdev_l/ave_l:stdev_l_MAX;
        };

        for(Int_t b=evt_h_lb; b<=evt_h_ub; b++)
        {
          bc = dd[n][r][c]->GetBinContent(b);
          if(bc>0)
          {
            sum_h+=bc;
            count_h++;
            max_h=(bc>max_h) ? bc:max_h;
          };
        };
        if(count_h>0) 
        {
          ave_h=sum_h/count_h;
          for(Int_t b=evt_h_lb; b<=evt_h_ub; b++)
          {
            bc = dd[n][r][c]->GetBinContent(b);
            ssq_h += pow(bc-ave_h,2);
          };
          stdev_h = sqrt(ssq_h/count_h);
          stdev_h_MAX = (stdev_h/ave_h>stdev_h_MAX) ? stdev_h/ave_h:stdev_h_MAX;
        };

        if(n==0||n==1)
        {
          // ave rat
          binn = large_averat->FindBin(5.8*2*((n+1)-1.5)*(c+0.5),-5.8*(r+0.5-17));
          if(ave_l*ave_h>0) large_averat->SetBinContent(binn,ave_h/ave_l);
          else if(ave_h>0) large_averat->SetBinContent(binn,ave_h);
          // max rat
          binn = large_maxrat->FindBin(5.8*2*((n+1)-1.5)*(c+0.5),-5.8*(r+0.5-17));
          if(max_l*max_h>0) large_maxrat->SetBinContent(binn,max_h/max_l);
          else if(max_h>0) large_maxrat->SetBinContent(binn,max_h);
          // stdev
          if(stdev_l>0 && ave_l>0) large_stdev_magon->SetBinContent(binn,stdev_l/ave_l);
          if(stdev_h>0 && ave_h>0) large_stdev_magoff->SetBinContent(binn,stdev_h/ave_h);
        }
        else if(n==2||n==3)
        {
          // ave rat
          binn = small_averat->FindBin(3.8*2*((n+1)-3.5)*(c+0.5),-3.8*(r-11.5));
          if(ave_l*ave_h>0) small_averat->SetBinContent(binn,ave_h/ave_l);
          else if(ave_h>0) small_averat->SetBinContent(binn,ave_h);
          // max rat
          binn = small_maxrat->FindBin(3.8*2*((n+1)-3.5)*(c+0.5),-3.8*(r-11.5));
          if(max_l*max_h>0) small_maxrat->SetBinContent(binn,max_h/max_l);
          else if(max_h>0) small_maxrat->SetBinContent(binn,max_h);
          // stdev
          if(stdev_l>0 && ave_l>0) small_stdev_magon->SetBinContent(binn,stdev_l/ave_l);
          if(stdev_h>0 && ave_h>0) small_stdev_magoff->SetBinContent(binn,stdev_h/ave_h);
        };
      };
    };
  };

  large_stdev_diff->Add(large_stdev_magoff,large_stdev_magon,1.0,-1.0);
  small_stdev_diff->Add(small_stdev_magoff,small_stdev_magon,1.0,-1.0);

  Double_t stdev_overall_MAX;
  stdev_overall_MAX = (stdev_l_MAX>stdev_h_MAX) ? stdev_l_MAX:stdev_h_MAX;

  large_stdev_magon->SetMinimum(.001);
  large_stdev_magon->SetMaximum(stdev_overall_MAX);
  small_stdev_magon->SetMinimum(.001);
  small_stdev_magon->SetMaximum(stdev_overall_MAX);
  large_stdev_magoff->SetMinimum(.001);
  large_stdev_magoff->SetMaximum(stdev_overall_MAX);
  small_stdev_magoff->SetMinimum(.001);
  small_stdev_magoff->SetMaximum(stdev_overall_MAX);
  large_stdev_diff->SetMinimum(.0001);
  large_stdev_diff->SetMaximum(stdev_overall_MAX);
  small_stdev_diff->SetMinimum(.0001);
  small_stdev_diff->SetMaximum(stdev_overall_MAX);


  TFile * outfile = new TFile("magrat.root","RECREATE");

  // draw 
  TCanvas* magrat_ave=new TCanvas("magrat_ave","magrat_ave",950,720);
  magrat_ave->SetLogz();
  large_averat->Draw("zcol");
  small_averat->Draw("zcolsame");
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
  magrat_ave->SetGrid(0,0);
  magrat_ave->Write();

  TCanvas* magrat_max=new TCanvas("magrat_max","magrat_max",950,720);
  magrat_max->SetLogz();
  large_maxrat->Draw("zcol");
  small_maxrat->Draw("zcolsame");
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
  magrat_max->SetGrid(0,0);
  magrat_max->Write();

  TCanvas* stdev_magon=new TCanvas("stdev_magon","stdev_magon",950,720);
  stdev_magon->SetLogz();
  large_stdev_magon->Draw("zcol");
  small_stdev_magon->Draw("zcolsame");
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
  stdev_magon->SetGrid(0,0);
  stdev_magon->Write();

  TCanvas* stdev_magoff=new TCanvas("stdev_magoff","stdev_magoff",950,720);
  stdev_magoff->SetLogz();
  large_stdev_magoff->Draw("zcol");
  small_stdev_magoff->Draw("zcolsame");
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
  stdev_magoff->SetGrid(0,0);
  stdev_magoff->Write();

  TCanvas* stdev_diff=new TCanvas("stdev_diff","stdev_diff",950,720);
  stdev_diff->SetLogz();
  large_stdev_diff->Draw("zcol");
  small_stdev_diff->Draw("zcolsame");
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
  stdev_diff->SetGrid(0,0);
  stdev_diff->Write();


  // write dd
  for(Int_t n=0; n<4; n++)
  {
    for(Int_t r=0; r<34; r++)
    {
      for(Int_t c=0; c<17; c++)
      {
        dd[n][r][c]->Write();
      };
    };
  };
};
