void draw_geom()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * geotr = (TTree*) infile->Get("geotr");
  Int_t nstb,row,col;
  char cell_type[32];
  geotr->SetBranchAddress("nstb",&nstb);
  geotr->SetBranchAddress("row",&row);
  geotr->SetBranchAddress("col",&col);
  geotr->SetBranchAddress("cell_type",cell_type);

  // cell types
  const Int_t NUM_TYPES=4;
  char cell_type_def[NUM_TYPES][32];
  strcpy(cell_type_def[0],"large_edge");
  strcpy(cell_type_def[1],"large_regular");
  strcpy(cell_type_def[2],"small_russian");
  strcpy(cell_type_def[3],"small_yale");
  char cell_type_legend[1024];
  strcpy(cell_type_legend,"legend:");
  for(Int_t i=0; i<NUM_TYPES; i++) 
    sprintf(cell_type_legend,"%s %d=%s",cell_type_legend,i+1,cell_type_def[i]);


  // fms display
  TH2F* large_type=new TH2F("large_type","cell types",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_type=new TH2F("small_type","cell types",52,-98.6,98.6,52,-98.6,98.6);
  large_type->GetXaxis()->SetTitle(cell_type_legend);
  small_type->GetXaxis()->SetTitle(cell_type_legend);
  TH2F* largetxt=new TH2F("largetxt","largetxt",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smalltxt=new TH2F("smalltxt","smalltxt",52,-98.6,98.6,52,-98.6,98.6);
  large_type->SetMinimum(0);
  small_type->SetMinimum(0);
  large_type->SetMaximum(NUM_TYPES);
  small_type->SetMaximum(NUM_TYPES);
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
  

  Double_t row_map,col_map,type_weight;
  Int_t binn;
  for(Int_t i=0; i<geotr->GetEntries(); i++)
  {
    geotr->GetEntry(i);
    for(Int_t tt=0; tt<NUM_TYPES; tt++)
      if(!strcmp(cell_type,cell_type_def[tt])) type_weight=tt+1;
    if(nstb==1||nstb==2) 
    {
      row_map = -5.8*(row+0.5-17);
      col_map = 5.8*2*(nstb-1.5)*(col+0.5);
      binn = large_type->FindBin(col_map,row_map);
      large_type->SetBinContent(binn,type_weight);
    }
    else
    {
      row_map = -3.8*(row-11.5);
      col_map = 3.8*2*(nstb-3.5)*(col+0.5);
      binn = small_type->FindBin(col_map,row_map);
      small_type->SetBinContent(binn,type_weight);
    };
  };


  TFile * outfile = new TFile("geometry_canvases.root","RECREATE");

  // draw
  TCanvas * type_canv = new TCanvas("type_canv","type_canv",950,720); 
  large_type->Draw("zcol");
  small_type->Draw("zcolsame");
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
  type_canv->SetGrid(0,0);
  type_canv->Write();
};

