void mk_tree(const char * filename="master", Int_t month0=2, Int_t day0=20, 
              Int_t timecut_low=0, Int_t timecut_high=0)
{
  // list of channels to not plot in summary.pdf (so scales get set properly)
  const Int_t N_MASK = 10;
  Int_t mask[N_MASK][3]; // [count] [crate,slot,chan]
  Int_t ii=0;
  mask[ii][0]=7005; mask[ii][1]=13; mask[ii++][2]=0;  // not stacked
  mask[ii][0]=7005; mask[ii][1]=14; mask[ii++][2]=2;  // not stacked
  mask[ii][0]=7005; mask[ii][1]=15; mask[ii++][2]=1;  // not stacked
  mask[ii][0]=7006; mask[ii][1]=15; mask[ii++][2]=2;  // suppressed to 0 V
  mask[ii][0]=7007; mask[ii][1]=1;  mask[ii++][2]=15; // unused channel: setpoint=900V, but readback=~1V
  mask[ii][0]=7008; mask[ii][1]=4;  mask[ii++][2]=13; // suppressed to 0 V
  mask[ii][0]=7005; mask[ii][1]=12;  mask[ii++][2]=4;
  mask[ii][0]=7007; mask[ii][1]=0;  mask[ii++][2]=15;
  mask[ii][0]=7007; mask[ii][1]=7;  mask[ii++][2]=2;
  mask[ii][0]=7007; mask[ii][1]=7;  mask[ii++][2]=7;



  // make tree after daily log file
  char outfilename[128];
  sprintf(outfilename,"rootfile.2015.%d.%d.root",month0,day0);
  TFile * outfile = new TFile(outfilename,"RECREATE");
  TTree * tr = new TTree();
  tr->ReadFile(filename,"crate/I:date/C:time/C:slot/I:chan/I:setpoint/I:readback/F");
  tr->Write("tr");
  Int_t crate,slot,chan,setpoint;
  Int_t year,month,day,hour,minute,second;
  Int_t c;
  Float_t readback;
  char date[32];
  char time[32];
  Color_t color[4] = {kRed,kGreen+1,kBlue,kMagenta};

  tr->SetBranchAddress("crate",&crate);
  tr->SetBranchAddress("date",date);
  tr->SetBranchAddress("time",time);
  tr->SetBranchAddress("slot",&slot);
  tr->SetBranchAddress("chan",&chan);
  tr->SetBranchAddress("setpoint",&setpoint);
  tr->SetBranchAddress("readback",&readback);


  // read list of unused channels
  TTree * ul = new TTree(); // list of unused channels
  ul->ReadFile("unused_list.txt","crate/I:slot/I:chan/I");
  Int_t ucrate,uslot,uchan;
  ul->SetBranchAddress("crate",&ucrate);
  ul->SetBranchAddress("slot",&uslot);
  ul->SetBranchAddress("chan",&uchan);


  // initalise (x) vs. time plots
  TGraph * stability_gr[4][16][16]; // [crate] [slot] [chan] // V_set-V_read vs. HHMM time
  TGraph * readback_gr[4][16][16]; // [crate] [slot] [chan] // V_read vs. HHMM time
  TGraph * setpoint_gr[4][16][16]; // [crate] [slot] [chan] // V_set vs. HHMM time
  Int_t gr_i[4][16][16];
  for(Int_t c=0; c<4; c++)
  {
    for(Int_t sl=0; sl<16; sl++)
    {
      for(Int_t ch=0; ch<16; ch++)
      {
        stability_gr[c][sl][ch] = new TGraph();
        readback_gr[c][sl][ch] = new TGraph();
        setpoint_gr[c][sl][ch] = new TGraph();
        gr_i[c][sl][ch] = 0;
        stability_gr[c][sl][ch]->SetMarkerStyle(kFullCircle);
        readback_gr[c][sl][ch]->SetMarkerStyle(kFullCircle);
        setpoint_gr[c][sl][ch]->SetMarkerStyle(kFullCircle);
        stability_gr[c][sl][ch]->SetMarkerColor(color[c]);
        readback_gr[c][sl][ch]->SetMarkerColor(color[c]);
        setpoint_gr[c][sl][ch]->SetMarkerColor(color[c]);
      };
    };
  };
  

  // fill (x) vs. time plots
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    sscanf(date,"%d.%d.%d",&year,&month,&day);
    if(month==month0 && day==day0)
    {
      sscanf(time,"%d.%d.%d",&hour,&minute,&second);
      c = CrateToIndex(crate);
      if(100*hour+minute>=timecut_low && (timecut_high==0 || 100*hour+minute<=timecut_high))
      {
        stability_gr[c][slot][chan]->SetPoint(
          gr_i[c][slot][chan],
          100*hour+minute,
          setpoint-readback);
        readback_gr[c][slot][chan]->SetPoint(
          gr_i[c][slot][chan],
          100*hour+minute,
          readback);
        setpoint_gr[c][slot][chan]->SetPoint(
          gr_i[c][slot][chan],
          100*hour+minute,
          setpoint);
        gr_i[c][slot][chan]++;
      };
    };
  };


  // define legend for voltage difference vs. time plots
  TLatex * color_leg[4];
  char color_leg_txt[4][8];
  for(Int_t c=0; c<4; c++)
  {
    sprintf(color_leg_txt[c],"%d",IndexToCrate(c));
    color_leg[c] = new TLatex(0.0,0.9-c*0.1,color_leg_txt[c]);
    color_leg[c]->SetNDC();
    color_leg[c]->SetTextColor(color[c]);
    color_leg[c]->SetTextSize(0.08);
  };

  
  // draw pdf for voltage difference vs. time plots
  gStyle->SetTitleH(0.1);
  gStyle->SetTitleW(0.7);
  TMultiGraph * multi_stability[16][16]; // [slot] [chan]
  char multi_stability_t[16][16][512];
  char unused_lab[32];
  char unused_str[40];
  TCanvas * canv = new TCanvas("canv","canv",700,1200);
  canv->Divide(1,8);
  Int_t padnum=1;
  Int_t pagenum=1;
  char pdfname[64];
  char pdfnameL[64];
  char pdfnameR[64];
  char canv_writename[64];
  sprintf(pdfname,"monitor.%d.%d.%d.pdf",year,month,day);
  sprintf(pdfnameL,"%s(",pdfname);
  sprintf(pdfnameR,"%s)",pdfname);
  for(Int_t sl=0; sl<16; sl++)
  {
    for(Int_t ch=0; ch<16; ch++)
    {
      strcpy(unused_str,"");
      strcpy(unused_lab,"");
      for(Int_t ent=0; ent<ul->GetEntries(); ent++)
      {
        ul->GetEntry(ent);
        if(sl==uslot && ch==uchan) 
        {
          strcpy(unused_lab," -- unused chan in");
          sprintf(unused_str,"%s %d",unused_str,ucrate);
        };
      };
      if((sl==13 && ch==0) ||
         (sl==14 && ch==2) ||
         (sl==15 && ch==1))
      {
        strcpy(unused_lab," -- unused chan in");
        sprintf(unused_str,"%s 7005[not_stacked]",unused_str);
      };
      sprintf(multi_stability_t[sl][ch],
        "V_{set}-V_{read} vs. time (%d,%d) on %d-%d-%d%s%s",
        sl,ch,year,month,day,unused_lab,unused_str);
      multi_stability[sl][ch] = new TMultiGraph();
      multi_stability[sl][ch]->SetTitle(multi_stability_t[sl][ch]);
      for(Int_t c=0; c<4; c++)
      {
        if(stability_gr[c][sl][ch]!=NULL && gr_i[c][sl][ch]>0)
        {
          multi_stability[sl][ch]->Add(stability_gr[c][sl][ch]);
        };
      };
      canv->cd(padnum);
      canv->GetPad(padnum)->SetGrid(1,1);
      multi_stability[sl][ch]->Draw("AP");
      multi_stability[sl][ch]->GetXaxis()->SetLabelSize(0.08);
      multi_stability[sl][ch]->GetYaxis()->SetLabelSize(0.08);
      for(Int_t c=0; c<4; c++) color_leg[c]->Draw();
      //printf("%d %d\n",pagenum,padnum);
      padnum++;
      if(padnum>8)
      {
        if(pagenum==1) canv->Print(pdfnameL,"PDF");
        else if(pagenum==32) canv->Print(pdfnameR,"PDF");
        else canv->Print(pdfname,"PDF");
        sprintf(canv_writename,"stability_slot%d_ch%d-%d",sl,
          (pagenum%2)?0:8,(pagenum%2)?7:15);
        canv->Write(canv_writename);
        pagenum++;
        padnum=1;
      };
    };
  };




  // summary plots
  TH2F * rms_plot[4]; // rms of V_set-V_read
  char rms_plot_t[4][64];
  char rms_plot_n[4][32];
  TH2F * ave_plot[4]; // abs value of average V_set-V_read
  char ave_plot_t[4][64];
  char ave_plot_n[4][32];
  TH2F * set_plot[4]; // abs value of average V_set
  char set_plot_t[4][64];
  char set_plot_n[4][32];
  TH2F * rdb_plot[4]; // abs value of average V_read
  char rdb_plot_t[4][64];
  char rdb_plot_n[4][32];
  Int_t binn;
  TGraph * unused_gr[4]; // unused channel markers
  Int_t unused_gr_i[4]; 
  TGraph * masked_gr[4]; // masked channel markers
  Int_t masked_gr_i[4]; 
  Bool_t plot_summary_point;
  for(Int_t c=0; c<4; c++) 
  {
    unused_gr[c] = new TGraph();
    unused_gr_i[c]=0;
    unused_gr[c]->SetMarkerStyle(28);
    unused_gr[c]->SetMarkerSize(3);
    unused_gr[c]->SetMarkerColor(kBlack);
    masked_gr[c] = new TGraph();
    masked_gr_i[c]=0;
    masked_gr[c]->SetMarkerStyle(8);
    masked_gr[c]->SetMarkerSize(1.5);
    masked_gr[c]->SetMarkerColor(kBlack);
  };
  for(Int_t c=0; c<4; c++)
  {
    sprintf(rms_plot_t[c],"RMS(V_{set}-V_{read}) vs. slot,channel [%d];slot;channel",IndexToCrate(c));
    sprintf(rms_plot_n[c],"rms_plot_%d",IndexToCrate(c));
    rms_plot[c] = new TH2F(rms_plot_n[c],rms_plot_t[c],16,-0.5,15.5,16,-0.5,15.5);
    sprintf(ave_plot_t[c],"|<V_{set}-V_{read}>| vs. slot,channel [%d];slot;channel",IndexToCrate(c));
    sprintf(ave_plot_n[c],"ave_plot_%d",IndexToCrate(c));
    ave_plot[c] = new TH2F(ave_plot_n[c],ave_plot_t[c],16,-0.5,15.5,16,-0.5,15.5);
    sprintf(set_plot_t[c],"|<V_{set}>| vs. slot,channel [%d];slot;channel",IndexToCrate(c));
    sprintf(set_plot_n[c],"set_plot_%d",IndexToCrate(c));
    set_plot[c] = new TH2F(set_plot_n[c],set_plot_t[c],16,-0.5,15.5,16,-0.5,15.5);
    sprintf(rdb_plot_t[c],"|<V_{read}>| vs. slot,channel [%d];slot;channel",IndexToCrate(c));
    sprintf(rdb_plot_n[c],"rdb_plot_%d",IndexToCrate(c));
    rdb_plot[c] = new TH2F(rdb_plot_n[c],rdb_plot_t[c],16,-0.5,15.5,16,-0.5,15.5);

    for(Int_t sl=0; sl<16; sl++)
    {
      for(Int_t ch=0; ch<16; ch++)
      {
        if(gr_i[c][sl][ch])
        {
          plot_summary_point=true;
          for(Int_t kk=0; kk<N_MASK; kk++)
          {
            if(IndexToCrate(c)==mask[kk][0] &&
               sl==mask[kk][1] &&
               ch==mask[kk][2]) plot_summary_point=false;
          };
          if(plot_summary_point) 
          {
            binn = rms_plot[c]->FindBin(sl,ch);
            rms_plot[c]->SetBinContent(binn,stability_gr[c][sl][ch]->GetRMS(2));
            ave_plot[c]->SetBinContent(binn,fabs(stability_gr[c][sl][ch]->GetMean(2)));
            set_plot[c]->SetBinContent(binn,fabs(setpoint_gr[c][sl][ch]->GetMean(2)));
            rdb_plot[c]->SetBinContent(binn,fabs(readback_gr[c][sl][ch]->GetMean(2)));
          };
        };
        for(Int_t ent=0; ent<ul->GetEntries(); ent++)
        {
          ul->GetEntry(ent);
          // filters not_stacked cells and unused channels
          if(sl==uslot && ch==uchan && IndexToCrate(c)==ucrate)
          {
            unused_gr[c]->SetPoint(unused_gr_i[c],sl,ch);
            unused_gr_i[c]++;
          };
          if(!plot_summary_point)
          {
            masked_gr[c]->SetPoint(masked_gr_i[c],sl,ch);
            masked_gr_i[c]++;
          };
        };
      };
    };
  };


  // draw summary plots
  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("5.2f");

  char summarypdfL[64];
  char summarypdf[64];
  char summarypdfR[64];
  sprintf(summarypdf,"summary.%d.%d.%d.pdf",year,month,day);
  sprintf(summarypdfL,"%s(",summarypdf);
  sprintf(summarypdfR,"%s)",summarypdf);

  TCanvas * rms_canv = new TCanvas("rms_canv","rms_canv",1700,1000);
  rms_canv->Divide(2,2);
  char draw_style[16];
  strcpy(draw_style,"colztext");
  //for(Int_t c=1; c<5; c++) rms_canv->GetPad(c)->SetLogz();
  for(Int_t p=0; p<4; p++)
  {
    rms_canv->cd(p+1);
    rms_plot[p]->Draw(draw_style);
    if(unused_gr_i[p]) unused_gr[p]->Draw("P");
    if(masked_gr_i[p]) masked_gr[p]->Draw("P");
  };
  rms_canv->Write();
  rms_canv->Print(summarypdfL,"pdf");

  TCanvas * ave_canv = new TCanvas("ave_canv","ave_canv",1700,1000);
  ave_canv->Divide(2,2);
  char draw_style[16];
  strcpy(draw_style,"colztext");
  //for(Int_t c=1; c<5; c++) ave_canv->GetPad(c)->SetLogz();
  for(Int_t p=0; p<4; p++)
  {
    ave_canv->cd(p+1);
    ave_plot[p]->Draw(draw_style);
    if(unused_gr_i[p]) unused_gr[p]->Draw("P");
    if(masked_gr_i[p]) masked_gr[p]->Draw("P");
  };
  ave_canv->Write();
  ave_canv->Print(summarypdf,"pdf");

  TCanvas * rdb_canv = new TCanvas("rdb_canv","rdb_canv",1700,1000);
  rdb_canv->Divide(2,2);
  char draw_style[16];
  strcpy(draw_style,"colztext");
  //for(Int_t c=1; c<5; c++) rdb_canv->GetPad(c)->SetLogz();
  for(Int_t p=0; p<4; p++)
  {
    rdb_canv->cd(p+1);
    rdb_plot[p]->Draw(draw_style);
    if(unused_gr_i[p]) unused_gr[p]->Draw("P");
    if(masked_gr_i[p]) masked_gr[p]->Draw("P");
  };
  rdb_canv->Write();
  rdb_canv->Print(summarypdf,"pdf");

  TCanvas * set_canv = new TCanvas("set_canv","set_canv",1700,1000);
  set_canv->Divide(2,2);
  char draw_style[16];
  strcpy(draw_style,"colztext");
  //for(Int_t c=1; c<5; c++) set_canv->GetPad(c)->SetLogz();
  for(Int_t p=0; p<4; p++)
  {
    set_canv->cd(p+1);
    set_plot[p]->Draw(draw_style);
    if(unused_gr_i[p]) unused_gr[p]->Draw("P");
    if(masked_gr_i[p]) masked_gr[p]->Draw("P");
  };
  set_canv->Write();
  set_canv->Print(summarypdfR,"pdf");


  printf("\n");
  printf("%s created (V_set-V_read vs. HHMM time)\n",pdfname);
  printf("%s created (summary diagnostics)\n",summarypdf);
  printf("%s created\n",outfilename);
}


Int_t CrateToIndex(Int_t crate0)
{
  return crate0-7005;
}


Int_t IndexToCrate(Int_t index0)
{
  return index0+7005;
}
