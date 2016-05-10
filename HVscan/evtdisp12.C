evtdisp12(const char* infile="15265001.1/adcTr.root") {
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  TFile * a = new TFile(infile,"READ");
  TFile * geofile = new TFile("geotr.root","READ");
  TTree * geotr = (TTree*) geofile->Get("geotr");
  TTree * Tr_adc = (TTree*) a->Get("Tr_adc");
  TFile * outfile = new TFile("canvas.root","RECREATE");
  Int_t gn,grow,gcol;
  geotr->SetBranchAddress("nstb",&gn);
  geotr->SetBranchAddress("row",&grow);
  geotr->SetBranchAddress("col",&gcol);

  TTree * probtree = new TTree();
  probtree->ReadFile("prob_list","nstb/I:chan/I:prob/I");
  Int_t pn,pc,pp;
  probtree->SetBranchAddress("nstb",&pn);
  probtree->SetBranchAddress("chan",&pc);
  probtree->SetBranchAddress("prob",&pp);

  int nev=Tr_adc->GetEntries();
  TH2F* large=new TH2F("large","large",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small=new TH2F("small","small",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* largesum=new TH2F("largesum","largesum",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smallsum=new TH2F("smallsum","smallsum",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* largefullsum=new TH2F("largefullsum","largefullsum",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smallfullsum=new TH2F("smallfullsum","smallfullsum",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* largebox=new TH2F("largebox","largebox",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smallbox=new TH2F("smallbox","smallbox",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* largetxt=new TH2F("largetxt","largetxt",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smalltxt=new TH2F("smalltxt","smalltxt",52,-98.6,98.6,52,-98.6,98.6);

  // fill problem characterisation histograms
  TGraph * largeprob[6];
  TGraph * smallprob[6];
  char largeprob_n[6][32];
  char smallprob_n[6][32];
  Int_t largeprob_i[6];
  Int_t smallprob_i[6];
  for(Int_t ppp=0; ppp<6; ppp++)
  {
    sprintf(largeprob_n[ppp],"largeprob_p%d",ppp+1);
    sprintf(smallprob_n[ppp],"smallprob_p%d",ppp+1);
    largeprob[ppp]=new TGraph();
    smallprob[ppp]=new TGraph();
    largeprob_i[ppp]=0;
    smallprob_i[ppp]=0;
  };
  Int_t chancal;
  Double_t posnumx;
  Double_t posnumy;
  for(Int_t ee=0; ee<geotr->GetEntries(); ee++)
  {
    geotr->GetEntry(ee);
    if(gn==1 || gn==2) chancal = gcol+grow*17+1;
    else if(gn==3 || gn==4) chancal = gcol+grow*12+1;
    for(Int_t ff=0; ff<probtree->GetEntries(); ff++)
    {
      probtree->GetEntry(ff);
      if(gn==pn && chancal==pc)
      {
        if(gn==1||gn==2)
        {
          posnumx=5.8*2*(gn-1.5)*(gcol+0.5);
          posnumy=-5.8*(grow+0.5-17);
          largeprob[pp-1]->SetPoint(largeprob_i[pp-1],posnumx,posnumy);
          (largeprob_i[pp-1])++;
        }
        else if(gn==3||gn==4)
        {
          posnumx=3.8*2*(gn-3.5)*(gcol+0.5);
          posnumy=-3.8*(grow-11.5);
          smallprob[pp-1]->SetPoint(smallprob_i[pp-1],posnumx,posnumy);
          (smallprob_i[pp-1])++;
        };
      };
    };
  };

  // problem names
  largeprob[0]->SetName("no LED");
  largeprob[1]->SetName("needs new base");
  largeprob[2]->SetName("QT problem");
  largeprob[3]->SetName("bad PMT");
  largeprob[4]->SetName("low gain");
  largeprob[5]->SetName("miscellaneous");


  // -- marker styles --
  // no LED
  largeprob[0]->SetMarkerStyle(27); //33/27
  smallprob[0]->SetMarkerStyle(27);
  //largeprob[0]->SetMarkerColor(49);
  //smallprob[0]->SetMarkerColor(49);
  // needs new base
  largeprob[1]->SetMarkerStyle(4); //8/4
  smallprob[1]->SetMarkerStyle(4);
  //largeprob[1]->SetMarkerColor(12);
  //smallprob[1]->SetMarkerColor(12);
  // QT problem
  largeprob[2]->SetMarkerStyle(28); //34/28
  smallprob[2]->SetMarkerStyle(28);
  //largeprob[2]->SetMarkerColor(28);
  //smallprob[2]->SetMarkerColor(28);
  // bad PMT
  largeprob[3]->SetMarkerStyle(25); //21/25
  smallprob[3]->SetMarkerStyle(25);
  //largeprob[3]->SetMarkerColor(1);
  //smallprob[3]->SetMarkerColor(1);
  // low gain
  largeprob[4]->SetMarkerStyle(26); //22/26
  smallprob[4]->SetMarkerStyle(26);
  //largeprob[4]->SetMarkerColor(39);
  //smallprob[4]->SetMarkerColor(39);
  largeprob[5]->SetMarkerStyle(30); //29/30
  smallprob[5]->SetMarkerStyle(30);
  //largeprob[5]->SetMarkerColor(39);
  //smallprob[5]->SetMarkerColor(39);

  for(Int_t ppp=0; ppp<6; ppp++)
  {
    largeprob[ppp]->SetMarkerSize(2);
    smallprob[ppp]->SetMarkerSize(1.3);
  };

  TMultiGraph * mg = new TMultiGraph();
  for(Int_t ppp=0; ppp<6; ppp++)
  {
    if(largeprob[ppp]->GetN()) mg->Add(largeprob[ppp]);
    if(smallprob[ppp]->GetN()) mg->Add(smallprob[ppp]);
  };

  TCanvas * legend = new TCanvas("legend","legend",270,300);
  TLegend * leg = new TLegend(0,0,1,1);
  for(Int_t ppp=0; ppp<6; ppp++) leg->AddEntry(largeprob[ppp],largeprob[ppp]->GetName(),"P");
  legend->cd();
  leg->Draw();
  legend->Write("legend");
 

  TCanvas* c1=new TCanvas("c1","c1",950,720);
  c1->Divide(3,3);
  c1->cd(1);
  Tr_adc->Draw("evtnum","ADC");
  c1->cd(2);
  Tr_adc->Draw("evtnum","(nstbADC==1)*ADC");
  c1->cd(3);
  Tr_adc->Draw("evtnum","(nstbADC==2)*ADC");
  c1->cd(4);
  Tr_adc->Draw("evtnum","(nstbADC==3)*ADC");
  c1->cd(5);
  Tr_adc->Draw("evtnum","(nstbADC==4)*ADC");
  c1->cd(6);
  Tr_adc->Draw("evtnum","(nstbADC==1&&rowADC>16||nstbADC==3&&rowADC>11)*ADC");
  c1->cd(7);
  Tr_adc->Draw("evtnum","(nstbADC==1&&rowADC<17||nstbADC==3&&rowADC<12)*ADC");
  c1->cd(8);
  Tr_adc->Draw("evtnum","(nstbADC==2&&rowADC>16||nstbADC==4&&rowADC>11)*ADC");
  c1->cd(9);
  Tr_adc->Draw("evtnum","(nstbADC==2&&rowADC<17||nstbADC==4&&rowADC<12)*ADC");
  c1->Print("eventdisp.ps(");

  int ntoshow=10;
  TString envntoshow=gSystem->Getenv("NToShow");
  if(envntoshow!="")
  {
    sscanf((char*) envntoshow,"%d",&ntoshow);
  };
  if(nev>ntoshow)nev=ntoshow;
  cout<<"Events to be plotted: "<<nev<<endl;
  int sbunch =-2;
  c1->Clear();
  TH2F* prepostEv=new TH2F("prepostEv","prepostEv",ntoshow,0,ntoshow,20,-5,5);
  prepostEv->GetXaxis()->SetTitle("Event Number");
  prepostEv->GetYaxis()->SetTitle("PrePost");
  Tr_adc->Draw("PrePost:evtnum>>prepostEv","","box");
  c1->Print("eventdisp.ps");
  char lcut[200];
  char scut[200];
  char tit[100];
  largebox->SetMinimum(.1);
  smallbox->SetMinimum(.1);
  largebox->SetMaximum(4096);
  smallbox->SetMaximum(4096);
  geotr->Project("largebox","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","4096*(nstb==1||nstb==2)");
  geotr->Project("smallbox","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","4096*(nstb==3||nstb==4)");
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


  // draw event sum histograms (events 1-max)
  largesum->SetMinimum(.1);
  largesum->SetMaximum(4096*nev);
  smallsum->SetMinimum(.1);
  smallsum->SetMaximum(4096*nev);
  char smallsumcut[256];
  char largesumcut[256];
  sprintf(largesumcut,"(abs(nstbADC-1.5)<1.&&evtnum<=%d)*ADC",nev);
  sprintf(smallsumcut,"(abs(nstbADC-3.5)<1.&&evtnum<=%d)*ADC",nev);
  Tr_adc->Project("largesum","-5.8*(rowADC+0.5-17):5.8*2*(nstbADC-1.5)*(colADC+.5)",largesumcut);
  Tr_adc->Project("smallsum","-3.8*(rowADC-11.5):3.8*2*(nstbADC-3.5)*(colADC+.5)",smallsumcut);
  char sumtit[128];
  sprintf(sumtit,"event ADC sum (events 1-%d) -- run=%s",nev,infile);
  largesum->SetTitle(sumtit);
  smallsum->SetTitle(sumtit);
  c1->Clear();
  c1->SetLogz(1);
  largesum->Draw("zcol");
  smallsum->Draw("zcolsame");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  mg->Draw("P");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  c1->SetGrid(0,0);
  c1->Print("eventdisp.ps");
  c1->Write("evsum");

  // draw event "full" sum histograms ("full" = all events)
  largefullsum->SetMinimum(.1);
  largefullsum->SetMaximum(4096*Tr_adc->GetMaximum("evtnum"));
  smallfullsum->SetMinimum(.1);
  smallfullsum->SetMaximum(4096*Tr_adc->GetMaximum("evtnum"));
  Tr_adc->Project("largefullsum","-5.8*(rowADC+0.5-17):5.8*2*(nstbADC-1.5)*(colADC+.5)",
    "(abs(nstbADC-1.5)<1.)*ADC");
  Tr_adc->Project("smallfullsum","-3.8*(rowADC-11.5):3.8*2*(nstbADC-3.5)*(colADC+.5)",
    "(abs(nstbADC-3.5)<1.)*ADC");
  char fullsumtit[128];
  sprintf(fullsumtit,"event ADC sum (all events) -- run=%s",infile);
  largefullsum->SetTitle(fullsumtit);
  smallfullsum->SetTitle(fullsumtit);
  c1->Clear();
  c1->SetLogz(1);
  largefullsum->Draw("zcol");
  smallfullsum->Draw("zcolsame");
  largetxt->Draw("textsame");
  smalltxt->Draw("textsame");
  mg->Draw("P");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  c1->SetGrid(0,0);
  c1->Print("eventdisp.ps");
  c1->Write("evfullsum");

  for(int j=0;j<nev;j++)
  {
    c1->Clear();
    large->Reset();
    small->Reset();
    large->SetMinimum(.1);
    large->SetMaximum(4096.);
    small->SetMinimum(.1);
    small->SetMaximum(4096);
    sprintf(lcut,"(abs(nstbADC-1.5)<1.&&evtnum==%d)*ADC",j);
    sprintf(scut,"(abs(nstbADC-3.5)<1.&&evtnum==%d)*ADC",j);

    //      Tr_adc->Draw("5.8*2*(nstbADC-1.5)*colADC:-5.8*(rowADC+0.5-17)>>Large(34,-98.6,98.6,34,-98.6,98.6)",lcut);
    //      Tr_adc->Draw("3.8*2*(nstbADC-3.5)*colADC:-3.8*(rowADC+0.5-12)>>Small(52,-98.6,98.6,52,-98.6,98.6)",scut);
    Tr_adc->Project("large","-5.8*(rowADC+0.5-17):5.8*2*(nstbADC-1.5)*(colADC+.5)",lcut);
    Tr_adc->Project("small","-3.8*(rowADC-11.5):3.8*2*(nstbADC-3.5)*(colADC+.5)",scut);

    sprintf(tit,"Event=%d Run=%s",j,infile);
    large->SetTitle(tit);
    c1->SetLogz(1);
    large->Draw("zcol");
    small->Draw("zcolsame");
    largetxt->Draw("textsame");
    smalltxt->Draw("textsame");
    mg->Draw("P");
    vline->Draw();
    hline->Draw();
    for(Int_t ii=0; ii<4; ii++) 
    {
      svline[ii]->Draw();
      shline[ii]->Draw();
      ibox[ii]->Draw();
      obox[ii]->Draw();
    };
    //printf("%s \n",str);
    //c1->Update();
    c1->SetGrid(0,0);
    c1->Print("eventdisp.ps");
    sprintf(wname,"ev%d",j);
    c1->Write(wname);
  };
  c1->Print("eventdisp.ps)");
  largefullsum->Write("largefullsum");
  smallfullsum->Write("smallfullsum");

};

