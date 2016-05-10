void draw()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * tr = (TTree*) infile->Get("geotr");
  
  Int_t nstb,row,col,chan,qtslot;
  char cell_type[32];
  char hvaddress_char[8];
  tr->SetBranchAddress("nstb",&nstb);
  tr->SetBranchAddress("row",&row);
  tr->SetBranchAddress("col",&col);
  tr->SetBranchAddress("chan",&chan);
  tr->SetBranchAddress("cell_type",cell_type);
  tr->SetBranchAddress("hvaddress_char",hvaddress_char);
  tr->SetBranchAddress("qtslot",&qtslot);

  // cell types
  const Int_t NUM_TYPES=6;
  char cell_type_def[NUM_TYPES][32];
  strcpy(cell_type_def[0],"large_psu");
  strcpy(cell_type_def[1],"large_fermi");
  strcpy(cell_type_def[2],"large_resistive");
  strcpy(cell_type_def[3],"small_russian");
  strcpy(cell_type_def[4],"small_yale");
  strcpy(cell_type_def[5],"not_stacked");
  char cell_type_legend[1024];
  strcpy(cell_type_legend,"leg:");
  for(Int_t i=0; i<NUM_TYPES; i++) 
    sprintf(cell_type_legend,"%s %d=%s",cell_type_legend,i+1,cell_type_def[i]);


  // fms display
  TH2F* large_type=new TH2F("large_type","cell types",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_type=new TH2F("small_type","cell types",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_pp=new TH2F("large_pp","patch panel",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_pp=new TH2F("small_pp","patch panel",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_pprow=new TH2F("large_pprow","patch panel row",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_pprow=new TH2F("small_pprow","patch panel row",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_ppcol=new TH2F("large_ppcol","patch panel column",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_ppcol=new TH2F("small_ppcol","patch panel column",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_qtcrate=new TH2F("large_qtcrate","qt crate",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_qtcrate=new TH2F("small_qtcrate","qt crate",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_qtslot=new TH2F("large_qtslot","qt slot",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_qtslot=new TH2F("small_qtslot","qt slot",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_qtcard=new TH2F("large_qtcard","qt card",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_qtcard=new TH2F("small_qtcard","qt card",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_qtchan=new TH2F("large_qtchan","qt chan",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_qtchan=new TH2F("small_qtchan","qt chan",52,-98.6,98.6,52,-98.6,98.6);

  TH2F* large_hvcrate=new TH2F("large_hvcrate","lecroy crate",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* large_hvslot=new TH2F("large_hvslot","lecroy slot",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* large_hvchan=new TH2F("large_hvchan","lecroy channel",34,-98.6,98.6,34,-98.6,98.6);

  TH2F* small_hvboard=new TH2F("small_hvboard","motherboard number N (device=N%2)",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* small_hvchip=new TH2F("small_hvchip","motherboard chip",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* small_hvchan=new TH2F("small_hvchan","motherboard channel",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* small_hvaddress=new TH2F("small_hvaddress","base address (text = address integer)",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* small_hvaddress_char=new TH2F("small_hvaddress_char","base address (text = address integer)",52,-98.6,98.6,52,-98.6,98.6);

  TH2F* large_trg=new TH2F("large_trg","",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_trg=new TH2F("small_trg","",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_sel=new TH2F("large_sel","",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_sel=new TH2F("small_sel","",52,-98.6,98.6,52,-98.6,98.6);


  large_type->GetXaxis()->SetTitle(cell_type_legend);
  large_type->SetMinimum(0);
  large_type->SetMaximum(NUM_TYPES);
  small_type->GetXaxis()->SetTitle(cell_type_legend);
  small_type->SetMinimum(0);
  small_type->SetMaximum(NUM_TYPES);

  large_pp->SetMinimum(0);
  small_pp->SetMinimum(0);
  large_pprow->SetMinimum(0);
  small_pprow->SetMinimum(0);
  large_ppcol->SetMinimum(0);
  small_ppcol->SetMinimum(0);
  large_qtcrate->SetMinimum(0);
  small_qtcrate->SetMinimum(0);
  large_qtslot->SetMinimum(0);
  small_qtslot->SetMinimum(0);
  large_qtcard->SetMinimum(0);
  small_qtcard->SetMinimum(0);
  large_qtchan->SetMinimum(0);
  small_qtchan->SetMinimum(0);
  large_hvcrate->SetMinimum(7005);
  large_hvslot->SetMinimum(0);
  large_hvchan->SetMinimum(0);
  small_hvboard->SetMinimum(0);
  small_hvchip->SetMinimum(0);
  small_hvchan->SetMinimum(0);
  small_hvaddress->SetMinimum(224);

  large_pp->SetMaximum(3);
  small_pp->SetMaximum(3);
  large_pprow->SetMaximum(22);
  small_pprow->SetMaximum(22);
  large_ppcol->SetMaximum(18);
  small_ppcol->SetMaximum(18);
  large_qtcrate->SetMaximum(5);
  small_qtcrate->SetMaximum(5);
  large_qtslot->SetMaximum(17);
  small_qtslot->SetMaximum(17);
  large_qtcard->SetMaximum(4);
  small_qtcard->SetMaximum(4);
  large_qtchan->SetMaximum(8);
  small_qtchan->SetMaximum(8);
  large_hvcrate->SetMaximum(7009);
  large_hvslot->SetMaximum(17);
  large_hvchan->SetMaximum(17);
  small_hvboard->SetMaximum(4);
  small_hvchip->SetMaximum(4);
  small_hvchan->SetMaximum(4);
  small_hvaddress->SetMaximum(256);

  tr->Project("large_pp","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","pp*(nstb==1||nstb==2)");
  tr->Project("small_pp","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","pp*(nstb==3||nstb==4)");
  tr->Project("large_pprow","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","pprow*(nstb==1||nstb==2)");
  tr->Project("small_pprow","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","pprow*(nstb==3||nstb==4)");
  tr->Project("large_ppcol","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","ppcol*(nstb==1||nstb==2)");
  tr->Project("small_ppcol","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","ppcol*(nstb==3||nstb==4)");
  tr->Project("large_qtcrate","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","qtcrate*(nstb==1||nstb==2)");
  tr->Project("small_qtcrate","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","qtcrate*(nstb==3||nstb==4)");
  tr->Project("large_qtslot","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(qtslot+0.01)*(nstb==1||nstb==2)");
  tr->Project("small_qtslot","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(qtslot+0.01)*(nstb==3||nstb==4)");
  tr->Project("large_qtcard","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(qtcard+0.01)*(nstb==1||nstb==2)");
  tr->Project("small_qtcard","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(qtcard+0.01)*(nstb==3||nstb==4)");
  tr->Project("large_qtchan","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(qtchan+0.01)*(nstb==1||nstb==2)");
  tr->Project("small_qtchan","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(qtchan+0.01)*(nstb==3||nstb==4)");

  tr->Project("large_hvcrate","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","hvcrate*(nstb==1||nstb==2)");
  tr->Project("large_hvslot","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(hvslot+0.01)*(nstb==1||nstb==2)");
  tr->Project("large_hvchan","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(hvchan+0.01)*(nstb==1||nstb==2)");

  tr->Project("small_hvboard","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","hvboard*(nstb==3||nstb==4)");
  tr->Project("small_hvchip","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(hvchip+0.01)*(nstb==3||nstb==4)");
  tr->Project("small_hvchan","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(hvchan+0.01)*(nstb==3||nstb==4)");
  tr->Project("small_hvaddress","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","hvaddress*(nstb==3||nstb==4)");


  // for coloring non-trigger cells
  tr->Project("large_sel","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)",
    "0*((nstb==1||nstb==2)&&qtslot!=11) + 2*((nstb==1||nstb==2)&&qtslot==11)");
  tr->Project("small_sel","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)",
    "0*(nstb==3||nstb==4)");
  large_sel->SetMinimum(0);
  small_trg->SetMinimum(0);
  large_sel->SetMaximum(2);
  small_trg->SetMaximum(2);

  // for drawing boxes around each cell
  tr->Project("large_trg","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)",
    "2*(nstb==1||nstb==2)");
  tr->Project("small_trg","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)",
    "2*(nstb==3||nstb==4)");
  large_trg->SetMinimum(0);
  small_trg->SetMinimum(0);
  large_trg->SetMaximum(2);
  small_trg->SetMaximum(2);

  /*
  Int_t binn;
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    if(nstb==3 || nstb==4)
    {
      binn = small_hvaddress->FindBin(3.8*2*(nstb-3.5)*(col+.5),-3.8*(row-11.5));
      small_hvaddress->SetBinContent(binn,hvaddress_char);
    };
  };
  */



  TH2F* largetxt=new TH2F("largetxt","largetxt",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* smalltxt=new TH2F("smalltxt","smalltxt",52,-98.6,98.6,52,-98.6,98.6);
  tr->Project("largetxt","-5.8*(row+0.5-17):5.8*2*(nstb-1.5)*(col+.5)","(col+row*17+1)*(nstb==1||nstb==2)");
  tr->Project("smalltxt","-3.8*(row-11.5):3.8*2*(nstb-3.5)*(col+.5)","(col+row*12+1)*(nstb==3||nstb==4)");
  largetxt->SetMarkerSize(0.5);
  smalltxt->SetMarkerSize(0.5);
  TLine * vline = new TLine(0,-98.6,0,98.6);
  TLine * hline = new TLine(-98.6,0,98.6,0);
  TLine * short_vline = new TLine(0,-46,0,46);
  TLine * short_hline = new TLine(-46,0,46,0);
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
  TLine * obox2[4];
    obox2[0] = new TLine(-8*5.8,8*5.8,8*5.8,8*5.8);
    obox2[1] = new TLine(8*5.8,8*5.8,8*5.8,-8*5.8);
    obox2[2] = new TLine(8*5.8,-8*5.8,-8*5.8,-8*5.8);
    obox2[3] = new TLine(-8*5.8,-8*5.8,-8*5.8,8*5.8);
  char wname[32];
  vline->SetLineColor(kBlack);
  hline->SetLineColor(kBlack);
  vline->SetLineWidth(4);
  hline->SetLineWidth(4);
  short_vline->SetLineColor(kBlack);
  short_hline->SetLineColor(kBlack);
  short_vline->SetLineWidth(2.5);
  short_hline->SetLineWidth(2.5);

  for(int ii=0; ii<4; ii++)
  {
    ibox[ii]->SetLineWidth(4);
    obox[ii]->SetLineWidth(4);
    obox2[ii]->SetLineWidth(4);
  };



  // cell type
  Double_t row_map,col_map,type_weight;
  Double_t xs[4][600][4]; // [nstb-1] [chan] [quadrant-1]
  Double_t ys[4][600][4]; // [nstb-1] [chan] [quadrant-1]
  Int_t binn;
  Double_t cell_size;
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    for(Int_t tt=0; tt<NUM_TYPES; tt++)
      if(!strcmp(cell_type,cell_type_def[tt])) type_weight=tt+1;
    if(nstb==1||nstb==2) 
    {
      cell_size = 5.8;
      row_map = -cell_size*(row+0.5-17);
      col_map = cell_size*2*(nstb-1.5)*(col+0.5);
      binn = large_type->FindBin(col_map,row_map);
      large_type->SetBinContent(binn,type_weight);
    }

    else
    {
      cell_size = 3.8;
      row_map = -cell_size*(row-11.5);
      col_map = cell_size*2*(nstb-3.5)*(col+0.5);
      binn = small_type->FindBin(col_map,row_map);
      small_type->SetBinContent(binn,type_weight);
    };

    xs[nstb-1][chan][0] = col_map + (cell_size/2.0);
    xs[nstb-1][chan][1] = col_map - (cell_size/2.0);
    xs[nstb-1][chan][2] = xs[nstb-1][chan][1];
    xs[nstb-1][chan][3] = xs[nstb-1][chan][0];

    ys[nstb-1][chan][0] = row_map + (cell_size/2.0);
    ys[nstb-1][chan][1] = ys[nstb-1][chan][0];
    ys[nstb-1][chan][2] = row_map - (cell_size/2.0);
    ys[nstb-1][chan][3] = ys[nstb-1][chan][2];
  };

  
  // trigger lines (e.g., between board sums)
  TLine * trgl[100];
  Int_t Ntrgl=0;

  trgl[Ntrgl++] = new TLine(xs[0][18][0],ys[0][18][0],xs[0][137][3],ys[0][137][3]);
  trgl[Ntrgl++] = new TLine(xs[0][21][1],ys[0][21][1],xs[0][140][2],ys[0][140][2]);
  trgl[Ntrgl++] = new TLine(xs[0][25][1],ys[0][25][1],xs[0][144][2],ys[0][144][2]);
  trgl[Ntrgl++] = new TLine(xs[0][10][2],ys[0][10][2],xs[0][1][3],ys[0][1][3]);
  trgl[Ntrgl++] = new TLine(xs[0][63][1],ys[0][63][1],xs[0][80][2],ys[0][80][2]);
  trgl[Ntrgl++] = new TLine(xs[0][99][1],ys[0][99][1],xs[0][94][0],ys[0][94][0]);
  trgl[Ntrgl++] = new TLine(xs[0][169][1],ys[0][169][1],xs[0][162][0],ys[0][162][0]);
  trgl[Ntrgl++] = new TLine(xs[0][237][1],ys[0][237][1],xs[0][230][0],ys[0][230][0]);
  trgl[Ntrgl++] = new TLine(xs[0][305][1],ys[0][305][1],xs[0][298][0],ys[0][298][0]);
  trgl[Ntrgl++] = new TLine(xs[0][136][0],ys[0][136][0],xs[0][459][3],ys[0][459][3]);
  trgl[Ntrgl++] = new TLine(xs[0][373][1],ys[0][373][1],xs[0][366][0],ys[0][366][0]);
  trgl[Ntrgl++] = new TLine(xs[0][441][1],ys[0][441][1],xs[0][434][0],ys[0][434][0]);
  trgl[Ntrgl++] = new TLine(xs[0][507][1],ys[0][507][1],xs[0][502][0],ys[0][502][0]);
  trgl[Ntrgl++] = new TLine(xs[0][434][0],ys[0][434][0],xs[0][553][3],ys[0][553][3]);
  trgl[Ntrgl++] = new TLine(xs[0][506][0],ys[0][506][0],xs[0][523][3],ys[0][523][3]);
  trgl[Ntrgl++] = new TLine(xs[0][430][0],ys[0][430][0],xs[0][549][3],ys[0][549][3]);
  trgl[Ntrgl++] = new TLine(xs[0][426][0],ys[0][426][0],xs[0][545][3],ys[0][545][3]);
  trgl[Ntrgl++] = new TLine(xs[0][571][1],ys[0][571][1],xs[0][562][0],ys[0][562][0]);

  trgl[Ntrgl++] = new TLine(xs[1][21][0],ys[1][21][1],xs[1][140][3],ys[1][140][2]);
  trgl[Ntrgl++] = new TLine(xs[1][25][0],ys[1][25][1],xs[1][144][3],ys[1][144][2]);
  trgl[Ntrgl++] = new TLine(xs[1][10][3],ys[1][10][2],xs[1][1][2],ys[1][1][3]);
  trgl[Ntrgl++] = new TLine(xs[1][63][0],ys[1][63][1],xs[1][80][3],ys[1][80][2]);
  trgl[Ntrgl++] = new TLine(xs[1][99][0],ys[1][99][1],xs[1][94][1],ys[1][94][0]);
  trgl[Ntrgl++] = new TLine(xs[1][169][0],ys[1][169][1],xs[1][162][1],ys[1][162][0]);
  trgl[Ntrgl++] = new TLine(xs[1][237][0],ys[1][237][1],xs[1][230][1],ys[1][230][0]);
  trgl[Ntrgl++] = new TLine(xs[1][305][0],ys[1][305][1],xs[1][298][1],ys[1][298][0]);
  trgl[Ntrgl++] = new TLine(xs[1][136][1],ys[1][136][0],xs[1][459][2],ys[1][459][3]);
  trgl[Ntrgl++] = new TLine(xs[1][373][0],ys[1][373][1],xs[1][366][1],ys[1][366][0]);
  trgl[Ntrgl++] = new TLine(xs[1][441][0],ys[1][441][1],xs[1][434][1],ys[1][434][0]);
  trgl[Ntrgl++] = new TLine(xs[1][507][0],ys[1][507][1],xs[1][502][1],ys[1][502][0]);
  trgl[Ntrgl++] = new TLine(xs[1][434][1],ys[1][434][0],xs[1][553][2],ys[1][553][3]);
  trgl[Ntrgl++] = new TLine(xs[1][506][1],ys[1][506][0],xs[1][523][2],ys[1][523][3]);
  trgl[Ntrgl++] = new TLine(xs[1][430][1],ys[1][430][0],xs[1][549][2],ys[1][549][3]);
  trgl[Ntrgl++] = new TLine(xs[1][571][0],ys[1][571][1],xs[1][562][1],ys[1][562][0]);

  trgl[Ntrgl++] = new TLine(xs[2][1][0],ys[2][1][0],xs[2][73][3],ys[2][73][3]);
  trgl[Ntrgl++] = new TLine(xs[2][4][1],ys[2][4][1],xs[2][76][2],ys[2][76][2]);
  trgl[Ntrgl++] = new TLine(xs[2][60][1],ys[2][60][1],xs[2][53][0],ys[2][53][0]);
  trgl[Ntrgl++] = new TLine(xs[2][108][1],ys[2][108][1],xs[2][102][0],ys[2][102][0]);
  trgl[Ntrgl++] = new TLine(xs[2][156][1],ys[2][156][1],xs[2][150][0],ys[2][150][0]);
  trgl[Ntrgl++] = new TLine(xs[2][204][1],ys[2][204][1],xs[2][198][0],ys[2][198][0]);
  trgl[Ntrgl++] = new TLine(xs[2][252][1],ys[2][252][1],xs[2][245][0],ys[2][245][0]);
  trgl[Ntrgl++] = new TLine(xs[2][208][1],ys[2][208][1],xs[2][280][2],ys[2][280][2]);
  trgl[Ntrgl++] = new TLine(xs[2][205][0],ys[2][205][0],xs[2][277][3],ys[2][277][3]);

  trgl[Ntrgl++] = new TLine(xs[3][4][0],ys[3][4][1],xs[3][76][3],ys[3][76][2]);
  trgl[Ntrgl++] = new TLine(xs[3][60][0],ys[3][60][1],xs[3][53][1],ys[3][53][0]);
  trgl[Ntrgl++] = new TLine(xs[3][108][0],ys[3][108][1],xs[3][102][1],ys[3][102][0]);
  trgl[Ntrgl++] = new TLine(xs[3][156][0],ys[3][156][1],xs[3][150][1],ys[3][150][0]);
  trgl[Ntrgl++] = new TLine(xs[3][204][0],ys[3][204][1],xs[3][198][1],ys[3][198][0]);
  trgl[Ntrgl++] = new TLine(xs[3][252][0],ys[3][252][1],xs[3][245][1],ys[3][245][0]);
  trgl[Ntrgl++] = new TLine(xs[3][208][0],ys[3][208][1],xs[3][280][3],ys[3][280][2]);

  for(int ii=0; ii<Ntrgl; ii++)
  {
    trgl[ii]->SetLineWidth(4);
    trgl[ii]->SetLineColor(kBlack);
  };


  // outer border lines
  TLine * obl[100];
  Int_t Nobl=0;

  obl[Nobl++] = new TLine(xs[0][1][0],ys[0][1][0],xs[0][10][1],ys[0][10][1]);
  obl[Nobl++] = new TLine(xs[0][10][1],ys[0][10][1],xs[0][10][2],ys[0][10][2]);
  obl[Nobl++] = new TLine(xs[0][28][0],ys[0][28][0],xs[0][28][1],ys[0][28][1]);
  obl[Nobl++] = new TLine(xs[0][28][1],ys[0][28][1],xs[0][28][2],ys[0][28][2]);
  obl[Nobl++] = new TLine(xs[0][46][0],ys[0][46][0],xs[0][46][1],ys[0][46][1]);
  obl[Nobl++] = new TLine(xs[0][46][1],ys[0][46][1],xs[0][46][2],ys[0][46][2]);
  obl[Nobl++] = new TLine(xs[0][64][0],ys[0][64][0],xs[0][64][1],ys[0][64][1]);
  obl[Nobl++] = new TLine(xs[0][64][1],ys[0][64][1],xs[0][64][2],ys[0][64][2]);
  obl[Nobl++] = new TLine(xs[0][82][0],ys[0][82][0],xs[0][82][1],ys[0][82][1]);
  obl[Nobl++] = new TLine(xs[0][82][1],ys[0][82][1],xs[0][82][2],ys[0][82][2]);
  obl[Nobl++] = new TLine(xs[0][100][0],ys[0][100][0],xs[0][100][1],ys[0][100][1]);
  obl[Nobl++] = new TLine(xs[0][100][1],ys[0][100][1],xs[0][100][2],ys[0][100][2]);
  obl[Nobl++] = new TLine(xs[0][118][0],ys[0][118][0],xs[0][118][1],ys[0][118][1]);
  obl[Nobl++] = new TLine(xs[0][118][1],ys[0][118][1],xs[0][118][2],ys[0][118][2]);
  obl[Nobl++] = new TLine(xs[0][136][0],ys[0][136][0],xs[0][136][1],ys[0][136][1]);
  obl[Nobl++] = new TLine(xs[0][136][1],ys[0][136][1],xs[0][459][2],ys[0][459][2]);
  obl[Nobl++] = new TLine(xs[0][459][2],ys[0][459][2],xs[0][459][3],ys[0][459][3]);
  obl[Nobl++] = new TLine(xs[0][475][1],ys[0][475][1],xs[0][475][2],ys[0][475][2]);
  obl[Nobl++] = new TLine(xs[0][475][2],ys[0][475][2],xs[0][475][3],ys[0][475][3]);
  obl[Nobl++] = new TLine(xs[0][491][1],ys[0][491][1],xs[0][491][2],ys[0][491][2]);
  obl[Nobl++] = new TLine(xs[0][491][2],ys[0][491][2],xs[0][491][3],ys[0][491][3]);
  obl[Nobl++] = new TLine(xs[0][507][1],ys[0][507][1],xs[0][507][2],ys[0][507][2]);
  obl[Nobl++] = new TLine(xs[0][507][2],ys[0][507][2],xs[0][507][3],ys[0][507][3]);
  obl[Nobl++] = new TLine(xs[0][523][1],ys[0][523][1],xs[0][523][2],ys[0][523][2]);
  obl[Nobl++] = new TLine(xs[0][523][2],ys[0][523][2],xs[0][523][3],ys[0][523][3]);
  obl[Nobl++] = new TLine(xs[0][539][1],ys[0][539][1],xs[0][539][2],ys[0][539][2]);
  obl[Nobl++] = new TLine(xs[0][539][2],ys[0][539][2],xs[0][539][3],ys[0][539][3]);
  obl[Nobl++] = new TLine(xs[0][555][1],ys[0][555][1],xs[0][555][2],ys[0][555][2]);
  obl[Nobl++] = new TLine(xs[0][555][2],ys[0][555][2],xs[0][555][3],ys[0][555][3]);
  obl[Nobl++] = new TLine(xs[0][571][1],ys[0][571][1],xs[0][571][2],ys[0][571][2]);
  obl[Nobl++] = new TLine(xs[0][571][2],ys[0][571][2],xs[0][562][3],ys[0][562][3]);

  obl[Nobl++] = new TLine(xs[1][1][1],ys[1][1][0],xs[1][10][0],ys[1][10][1]);
  obl[Nobl++] = new TLine(xs[1][10][0],ys[1][10][1],xs[1][10][3],ys[1][10][2]);
  obl[Nobl++] = new TLine(xs[1][28][1],ys[1][28][0],xs[1][28][0],ys[1][28][1]);
  obl[Nobl++] = new TLine(xs[1][28][0],ys[1][28][1],xs[1][28][3],ys[1][28][2]);
  obl[Nobl++] = new TLine(xs[1][46][1],ys[1][46][0],xs[1][46][0],ys[1][46][1]);
  obl[Nobl++] = new TLine(xs[1][46][0],ys[1][46][1],xs[1][46][3],ys[1][46][2]);
  obl[Nobl++] = new TLine(xs[1][64][1],ys[1][64][0],xs[1][64][0],ys[1][64][1]);
  obl[Nobl++] = new TLine(xs[1][64][0],ys[1][64][1],xs[1][64][3],ys[1][64][2]);
  obl[Nobl++] = new TLine(xs[1][82][1],ys[1][82][0],xs[1][82][0],ys[1][82][1]);
  obl[Nobl++] = new TLine(xs[1][82][0],ys[1][82][1],xs[1][82][3],ys[1][82][2]);
  obl[Nobl++] = new TLine(xs[1][100][1],ys[1][100][0],xs[1][100][0],ys[1][100][1]);
  obl[Nobl++] = new TLine(xs[1][100][0],ys[1][100][1],xs[1][100][3],ys[1][100][2]);
  obl[Nobl++] = new TLine(xs[1][118][1],ys[1][118][0],xs[1][118][0],ys[1][118][1]);
  obl[Nobl++] = new TLine(xs[1][118][0],ys[1][118][1],xs[1][118][3],ys[1][118][2]);
  obl[Nobl++] = new TLine(xs[1][136][1],ys[1][136][0],xs[1][136][0],ys[1][136][1]);
  obl[Nobl++] = new TLine(xs[1][136][0],ys[1][136][1],xs[1][459][3],ys[1][459][2]);
  obl[Nobl++] = new TLine(xs[1][459][3],ys[1][459][2],xs[1][459][2],ys[1][459][3]);
  obl[Nobl++] = new TLine(xs[1][475][0],ys[1][475][1],xs[1][475][3],ys[1][475][2]);
  obl[Nobl++] = new TLine(xs[1][475][3],ys[1][475][2],xs[1][475][2],ys[1][475][3]);
  obl[Nobl++] = new TLine(xs[1][491][0],ys[1][491][1],xs[1][491][3],ys[1][491][2]);
  obl[Nobl++] = new TLine(xs[1][491][3],ys[1][491][2],xs[1][491][2],ys[1][491][3]);
  obl[Nobl++] = new TLine(xs[1][507][0],ys[1][507][1],xs[1][507][3],ys[1][507][2]);
  obl[Nobl++] = new TLine(xs[1][507][3],ys[1][507][2],xs[1][507][2],ys[1][507][3]);
  obl[Nobl++] = new TLine(xs[1][523][0],ys[1][523][1],xs[1][523][3],ys[1][523][2]);
  obl[Nobl++] = new TLine(xs[1][523][3],ys[1][523][2],xs[1][523][2],ys[1][523][3]);
  obl[Nobl++] = new TLine(xs[1][539][0],ys[1][539][1],xs[1][539][3],ys[1][539][2]);
  obl[Nobl++] = new TLine(xs[1][539][3],ys[1][539][2],xs[1][539][2],ys[1][539][3]);
  obl[Nobl++] = new TLine(xs[1][555][0],ys[1][555][1],xs[1][555][3],ys[1][555][2]);
  obl[Nobl++] = new TLine(xs[1][555][3],ys[1][555][2],xs[1][555][2],ys[1][555][3]);
  obl[Nobl++] = new TLine(xs[1][571][0],ys[1][571][1],xs[1][571][3],ys[1][571][2]);
  obl[Nobl++] = new TLine(xs[1][571][3],ys[1][571][2],xs[1][562][2],ys[1][562][3]);

  for(int ii=0; ii<Nobl; ii++)
  {
    obl[ii]->SetLineWidth(4);
    obl[ii]->SetLineColor(kBlack);
  };



  // dotted lines
  TLine * dott[200];
  Int_t Ndott=0;

  dott[Ndott++] = new TLine(xs[0][18][1],ys[0][18][1],xs[0][137][2],ys[0][137][2]);
  dott[Ndott++] = new TLine(xs[0][19][1],ys[0][19][1],xs[0][138][2],ys[0][138][2]);
  dott[Ndott++] = new TLine(xs[0][20][1],ys[0][20][1],xs[0][139][2],ys[0][139][2]);
  dott[Ndott++] = new TLine(xs[0][22][1],ys[0][22][1],xs[0][141][2],ys[0][141][2]);
  dott[Ndott++] = new TLine(xs[0][23][1],ys[0][23][1],xs[0][142][2],ys[0][142][2]);
  dott[Ndott++] = new TLine(xs[0][24][1],ys[0][24][1],xs[0][143][2],ys[0][143][2]);
  dott[Ndott++] = new TLine(xs[0][426][1],ys[0][426][1],xs[0][545][2],ys[0][545][2]);
  dott[Ndott++] = new TLine(xs[0][427][1],ys[0][427][1],xs[0][546][2],ys[0][546][2]);
  dott[Ndott++] = new TLine(xs[0][428][1],ys[0][428][1],xs[0][547][2],ys[0][547][2]);
  dott[Ndott++] = new TLine(xs[0][430][1],ys[0][430][1],xs[0][549][2],ys[0][549][2]);
  dott[Ndott++] = new TLine(xs[0][431][1],ys[0][431][1],xs[0][550][2],ys[0][550][2]);
  dott[Ndott++] = new TLine(xs[0][432][1],ys[0][432][1],xs[0][551][2],ys[0][551][2]);
  dott[Ndott++] = new TLine(xs[0][26][3],ys[0][26][3],xs[0][28][2],ys[0][28][2]);
  dott[Ndott++] = new TLine(xs[0][43][3],ys[0][43][3],xs[0][46][2],ys[0][46][2]);
  dott[Ndott++] = new TLine(xs[0][60][3],ys[0][60][3],xs[0][63][2],ys[0][63][2]);
  dott[Ndott++] = new TLine(xs[0][94][3],ys[0][94][3],xs[0][100][2],ys[0][100][2]);
  dott[Ndott++] = new TLine(xs[0][111][3],ys[0][111][3],xs[0][118][2],ys[0][118][2]);
  dott[Ndott++] = new TLine(xs[0][128][3],ys[0][128][3],xs[0][135][2],ys[0][135][2]);
  dott[Ndott++] = new TLine(xs[0][162][3],ys[0][162][3],xs[0][169][2],ys[0][169][2]);
  dott[Ndott++] = new TLine(xs[0][179][3],ys[0][179][3],xs[0][186][2],ys[0][186][2]);
  dott[Ndott++] = new TLine(xs[0][196][3],ys[0][196][3],xs[0][203][2],ys[0][203][2]);
  dott[Ndott++] = new TLine(xs[0][230][3],ys[0][230][3],xs[0][237][2],ys[0][237][2]);
  dott[Ndott++] = new TLine(xs[0][247][3],ys[0][247][3],xs[0][254][2],ys[0][254][2]);
  dott[Ndott++] = new TLine(xs[0][264][3],ys[0][264][3],xs[0][271][2],ys[0][271][2]);
  dott[Ndott++] = new TLine(xs[0][298][3],ys[0][298][3],xs[0][305][2],ys[0][305][2]);
  dott[Ndott++] = new TLine(xs[0][315][3],ys[0][315][3],xs[0][322][2],ys[0][322][2]);
  dott[Ndott++] = new TLine(xs[0][332][3],ys[0][332][3],xs[0][339][2],ys[0][339][2]);
  dott[Ndott++] = new TLine(xs[0][366][3],ys[0][366][3],xs[0][373][2],ys[0][373][2]);
  dott[Ndott++] = new TLine(xs[0][383][3],ys[0][383][3],xs[0][390][2],ys[0][390][2]);
  dott[Ndott++] = new TLine(xs[0][400][3],ys[0][400][3],xs[0][407][2],ys[0][407][2]);
  dott[Ndott++] = new TLine(xs[0][434][3],ys[0][434][3],xs[0][441][2],ys[0][441][2]);
  dott[Ndott++] = new TLine(xs[0][451][3],ys[0][451][3],xs[0][458][2],ys[0][458][2]);
  dott[Ndott++] = new TLine(xs[0][468][3],ys[0][468][3],xs[0][474][2],ys[0][474][2]);
  dott[Ndott++] = new TLine(xs[0][502][3],ys[0][502][3],xs[0][505][2],ys[0][505][2]);
  dott[Ndott++] = new TLine(xs[0][519][3],ys[0][519][3],xs[0][522][2],ys[0][522][2]);
  dott[Ndott++] = new TLine(xs[0][536][3],ys[0][536][3],xs[0][538][2],ys[0][538][2]);

  dott[Ndott++] = new TLine(xs[1][18][0],ys[1][18][1],xs[1][137][3],ys[1][137][2]);
  dott[Ndott++] = new TLine(xs[1][19][0],ys[1][19][1],xs[1][138][3],ys[1][138][2]);
  dott[Ndott++] = new TLine(xs[1][20][0],ys[1][20][1],xs[1][139][3],ys[1][139][2]);
  dott[Ndott++] = new TLine(xs[1][22][0],ys[1][22][1],xs[1][141][3],ys[1][141][2]);
  dott[Ndott++] = new TLine(xs[1][23][0],ys[1][23][1],xs[1][142][3],ys[1][142][2]);
  dott[Ndott++] = new TLine(xs[1][24][0],ys[1][24][1],xs[1][143][3],ys[1][143][2]);
  dott[Ndott++] = new TLine(xs[1][426][0],ys[1][426][1],xs[1][545][3],ys[1][545][2]);
  dott[Ndott++] = new TLine(xs[1][427][0],ys[1][427][1],xs[1][546][3],ys[1][546][2]);
  dott[Ndott++] = new TLine(xs[1][428][0],ys[1][428][1],xs[1][547][3],ys[1][547][2]);
  dott[Ndott++] = new TLine(xs[1][430][0],ys[1][430][1],xs[1][549][3],ys[1][549][2]);
  dott[Ndott++] = new TLine(xs[1][431][0],ys[1][431][1],xs[1][550][3],ys[1][550][2]);
  dott[Ndott++] = new TLine(xs[1][432][0],ys[1][432][1],xs[1][551][3],ys[1][551][2]);
  dott[Ndott++] = new TLine(xs[1][26][2],ys[1][26][3],xs[1][28][3],ys[1][28][2]);
  dott[Ndott++] = new TLine(xs[1][43][2],ys[1][43][3],xs[1][46][3],ys[1][46][2]);
  dott[Ndott++] = new TLine(xs[1][60][2],ys[1][60][3],xs[1][63][3],ys[1][63][2]);
  dott[Ndott++] = new TLine(xs[1][94][2],ys[1][94][3],xs[1][100][3],ys[1][100][2]);
  dott[Ndott++] = new TLine(xs[1][111][2],ys[1][111][3],xs[1][118][3],ys[1][118][2]);
  dott[Ndott++] = new TLine(xs[1][128][2],ys[1][128][3],xs[1][135][3],ys[1][135][2]);
  dott[Ndott++] = new TLine(xs[1][162][2],ys[1][162][3],xs[1][169][3],ys[1][169][2]);
  dott[Ndott++] = new TLine(xs[1][179][2],ys[1][179][3],xs[1][186][3],ys[1][186][2]);
  dott[Ndott++] = new TLine(xs[1][196][2],ys[1][196][3],xs[1][203][3],ys[1][203][2]);
  dott[Ndott++] = new TLine(xs[1][230][2],ys[1][230][3],xs[1][237][3],ys[1][237][2]);
  dott[Ndott++] = new TLine(xs[1][247][2],ys[1][247][3],xs[1][254][3],ys[1][254][2]);
  dott[Ndott++] = new TLine(xs[1][264][2],ys[1][264][3],xs[1][271][3],ys[1][271][2]);
  dott[Ndott++] = new TLine(xs[1][298][2],ys[1][298][3],xs[1][305][3],ys[1][305][2]);
  dott[Ndott++] = new TLine(xs[1][315][2],ys[1][315][3],xs[1][322][3],ys[1][322][2]);
  dott[Ndott++] = new TLine(xs[1][332][2],ys[1][332][3],xs[1][339][3],ys[1][339][2]);
  dott[Ndott++] = new TLine(xs[1][366][2],ys[1][366][3],xs[1][373][3],ys[1][373][2]);
  dott[Ndott++] = new TLine(xs[1][383][2],ys[1][383][3],xs[1][390][3],ys[1][390][2]);
  dott[Ndott++] = new TLine(xs[1][400][2],ys[1][400][3],xs[1][407][3],ys[1][407][2]);
  dott[Ndott++] = new TLine(xs[1][434][2],ys[1][434][3],xs[1][441][3],ys[1][441][2]);
  dott[Ndott++] = new TLine(xs[1][451][2],ys[1][451][3],xs[1][458][3],ys[1][458][2]);
  dott[Ndott++] = new TLine(xs[1][468][2],ys[1][468][3],xs[1][474][3],ys[1][474][2]);
  dott[Ndott++] = new TLine(xs[1][502][2],ys[1][502][3],xs[1][505][3],ys[1][505][2]);
  dott[Ndott++] = new TLine(xs[1][519][2],ys[1][519][3],xs[1][522][3],ys[1][522][2]);
  dott[Ndott++] = new TLine(xs[1][536][2],ys[1][536][3],xs[1][538][3],ys[1][538][2]);

  dott[Ndott++] = new TLine(xs[2][1][1],ys[2][1][1],xs[2][73][2],ys[2][73][2]);
  dott[Ndott++] = new TLine(xs[2][2][1],ys[2][2][1],xs[2][74][2],ys[2][74][2]);
  dott[Ndott++] = new TLine(xs[2][3][1],ys[2][3][1],xs[2][75][2],ys[2][75][2]);
  dott[Ndott++] = new TLine(xs[2][205][1],ys[2][205][1],xs[2][277][2],ys[2][277][2]);
  dott[Ndott++] = new TLine(xs[2][206][1],ys[2][206][1],xs[2][278][2],ys[2][278][2]);
  dott[Ndott++] = new TLine(xs[2][207][1],ys[2][207][1],xs[2][279][2],ys[2][279][2]);
  dott[Ndott++] = new TLine(xs[2][5][3],ys[2][5][3],xs[2][12][2],ys[2][12][2]);
  dott[Ndott++] = new TLine(xs[2][17][3],ys[2][17][3],xs[2][24][2],ys[2][24][2]);
  dott[Ndott++] = new TLine(xs[2][29][3],ys[2][29][3],xs[2][36][2],ys[2][36][2]);
  dott[Ndott++] = new TLine(xs[2][53][3],ys[2][53][3],xs[2][60][2],ys[2][60][2]);
  dott[Ndott++] = new TLine(xs[2][65][3],ys[2][65][3],xs[2][72][2],ys[2][72][2]);
  dott[Ndott++] = new TLine(xs[2][78][3],ys[2][78][3],xs[2][84][2],ys[2][84][2]);
  dott[Ndott++] = new TLine(xs[2][102][3],ys[2][102][3],xs[2][108][2],ys[2][108][2]);
  dott[Ndott++] = new TLine(xs[2][114][3],ys[2][114][3],xs[2][120][2],ys[2][120][2]);
  dott[Ndott++] = new TLine(xs[2][126][3],ys[2][126][3],xs[2][132][2],ys[2][132][2]);
  dott[Ndott++] = new TLine(xs[2][150][3],ys[2][150][3],xs[2][156][2],ys[2][156][2]);
  dott[Ndott++] = new TLine(xs[2][162][3],ys[2][162][3],xs[2][168][2],ys[2][168][2]);
  dott[Ndott++] = new TLine(xs[2][174][3],ys[2][174][3],xs[2][180][2],ys[2][180][2]);
  dott[Ndott++] = new TLine(xs[2][198][3],ys[2][198][3],xs[2][204][2],ys[2][204][2]);
  dott[Ndott++] = new TLine(xs[2][209][3],ys[2][209][3],xs[2][216][2],ys[2][216][2]);
  dott[Ndott++] = new TLine(xs[2][221][3],ys[2][221][3],xs[2][228][2],ys[2][228][2]);
  dott[Ndott++] = new TLine(xs[2][245][3],ys[2][245][3],xs[2][252][2],ys[2][252][2]);
  dott[Ndott++] = new TLine(xs[2][257][3],ys[2][257][3],xs[2][264][2],ys[2][264][2]);
  dott[Ndott++] = new TLine(xs[2][269][3],ys[2][269][3],xs[2][276][2],ys[2][276][2]);

  dott[Ndott++] = new TLine(xs[3][1][0],ys[3][1][1],xs[3][73][3],ys[3][73][2]);
  dott[Ndott++] = new TLine(xs[3][2][0],ys[3][2][1],xs[3][74][3],ys[3][74][2]);
  dott[Ndott++] = new TLine(xs[3][3][0],ys[3][3][1],xs[3][75][3],ys[3][75][2]);
  dott[Ndott++] = new TLine(xs[3][205][0],ys[3][205][1],xs[3][277][3],ys[3][277][2]);
  dott[Ndott++] = new TLine(xs[3][206][0],ys[3][206][1],xs[3][278][3],ys[3][278][2]);
  dott[Ndott++] = new TLine(xs[3][207][0],ys[3][207][1],xs[3][279][3],ys[3][279][2]);
  dott[Ndott++] = new TLine(xs[3][5][2],ys[3][5][3],xs[3][12][3],ys[3][12][2]);
  dott[Ndott++] = new TLine(xs[3][17][2],ys[3][17][3],xs[3][24][3],ys[3][24][2]);
  dott[Ndott++] = new TLine(xs[3][29][2],ys[3][29][3],xs[3][36][3],ys[3][36][2]);
  dott[Ndott++] = new TLine(xs[3][53][2],ys[3][53][3],xs[3][60][3],ys[3][60][2]);
  dott[Ndott++] = new TLine(xs[3][65][2],ys[3][65][3],xs[3][72][3],ys[3][72][2]);
  dott[Ndott++] = new TLine(xs[3][78][2],ys[3][78][3],xs[3][84][3],ys[3][84][2]);
  dott[Ndott++] = new TLine(xs[3][102][2],ys[3][102][3],xs[3][108][3],ys[3][108][2]);
  dott[Ndott++] = new TLine(xs[3][114][2],ys[3][114][3],xs[3][120][3],ys[3][120][2]);
  dott[Ndott++] = new TLine(xs[3][126][2],ys[3][126][3],xs[3][132][3],ys[3][132][2]);
  dott[Ndott++] = new TLine(xs[3][150][2],ys[3][150][3],xs[3][156][3],ys[3][156][2]);
  dott[Ndott++] = new TLine(xs[3][162][2],ys[3][162][3],xs[3][168][3],ys[3][168][2]);
  dott[Ndott++] = new TLine(xs[3][174][2],ys[3][174][3],xs[3][180][3],ys[3][180][2]);
  dott[Ndott++] = new TLine(xs[3][198][2],ys[3][198][3],xs[3][204][3],ys[3][204][2]);
  dott[Ndott++] = new TLine(xs[3][209][2],ys[3][209][3],xs[3][216][3],ys[3][216][2]);
  dott[Ndott++] = new TLine(xs[3][221][2],ys[3][221][3],xs[3][228][3],ys[3][228][2]);
  dott[Ndott++] = new TLine(xs[3][245][2],ys[3][245][3],xs[3][252][3],ys[3][252][2]);
  dott[Ndott++] = new TLine(xs[3][257][2],ys[3][257][3],xs[3][264][3],ys[3][264][2]);
  dott[Ndott++] = new TLine(xs[3][269][2],ys[3][269][3],xs[3][276][3],ys[3][276][2]);

  for(int ii=0; ii<Ndott; ii++)
  {
    dott[ii]->SetLineWidth(2);
    dott[ii]->SetLineColor(kGray+2);
    dott[ii]->SetLineStyle(2);
  };




  // eta circles
  TEllipse * etac[20];
  Int_t Netac = 0;

  // eta rings for analysis
  //etac[Netac++] = new TEllipse(0,0,XofEta(2.65));  // minimum eta
  //etac[Netac++] = new TEllipse(0,0,XofEta(3.105)); // corner of l/s boundary
  //etac[Netac++] = new TEllipse(0,0,XofEta(3.28)); // average eta of l/s boundary
  //etac[Netac++] = new TEllipse(0,0,XofEta(3.45)); // side of l/s boundary
  //etac[Netac++] = new TEllipse(0,0,XofEta(3.9)); // maximum eta
  
  etac[Netac++] = new TEllipse(0,0,XofEta(2.6));
  etac[Netac++] = new TEllipse(0,0,XofEta(3.0));
  etac[Netac++] = new TEllipse(0,0,XofEta(3.5));
  etac[Netac++] = new TEllipse(0,0,XofEta(4.0));

  for(int ii=0; ii<Netac; ii++)
  {
    etac[ii]->SetLineColor(kRed);
    etac[ii]->SetFillColorAlpha(kWhite,0);
    etac[ii]->SetLineWidth(6);
  };
  //etac[0]->SetLineColor(kRed); etac[0]->SetLineWidth(7);
  //etac[Netac-1]->SetLineColor(kRed); etac[Netac-1]->SetLineWidth(7);


  
  // draw JP diagrams
  TH2F* small_jptb=new TH2F("small_jptb","",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_jptb=new TH2F("large_jptb","",34,-98.6,98.6,34,-98.6,98.6);
  TH2F* small_jpm=new TH2F("small_jpm","",52,-98.6,98.6,52,-98.6,98.6);
  TH2F* large_jpm=new TH2F("large_jpm","",34,-98.6,98.6,34,-98.6,98.6);
  Int_t jpstb,jpsm,bn;
  for(int x=0; x<tr->GetEntries(); x++)
  {
    tr->GetEntry(x);
    jpstb = JPTB(nstb,chan,qtslot);
    jpsm = JPM(nstb,chan,qtslot);
    if(nstb==1 || nstb==2)
    {
      bn = large_qtslot->FindBin(5.8*2*(nstb-1.5)*(col+.5), -5.8*(row+0.5-17));
      if(jpstb>0) large_jptb->SetBinContent(bn,jpstb);
      if(jpsm>0) large_jpm->SetBinContent(bn,jpsm);
    }
    else if(nstb==3 || nstb==4)
    {
      bn = small_qtslot->FindBin(3.8*2*(nstb-3.5)*(col+.5), -3.8*(row-11.5));
      if(jpstb>0) small_jptb->SetBinContent(bn,jpstb);
      if(jpsm>0) small_jpm->SetBinContent(bn,jpsm);
    }
  };


  // draw
  TFile * outfile = new TFile("maps.root","RECREATE");

  TCanvas * type_canv = new TCanvas("type_canv","type_canv",1000,650); 
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

  TCanvas * pp_canv = new TCanvas("pp_canv","pp_canv",1000,650); 
  large_pp->Draw("zcol");
  small_pp->Draw("zcolsame");
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
  pp_canv->SetGrid(0,0);
  pp_canv->Write();

  TCanvas * pprow_canv = new TCanvas("pprow_canv","pprow_canv",1000,650); 
  large_pprow->Draw("zcol");
  small_pprow->Draw("zcolsame");
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
  pprow_canv->SetGrid(0,0);
  pprow_canv->Write();

  TCanvas * ppcol_canv = new TCanvas("ppcol_canv","ppcol_canv",1000,650); 
  large_ppcol->Draw("zcol");
  small_ppcol->Draw("zcolsame");
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
  ppcol_canv->SetGrid(0,0);
  ppcol_canv->Write();

  TCanvas * qtcrate_canv = new TCanvas("qtcrate_canv","qtcrate_canv",1000,650); 
  large_qtcrate->Draw("zcol");
  small_qtcrate->Draw("zcolsame");
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
  qtcrate_canv->SetGrid(0,0);
  qtcrate_canv->Write();

  TCanvas * qtslot_canv = new TCanvas("qtslot_canv","qtslot_canv",1000,650); 
  large_qtslot->Draw("zcol");
  small_qtslot->Draw("zcolsame");
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
  qtslot_canv->SetGrid(0,0);
  qtslot_canv->Write();

  TCanvas * qtcard_canv = new TCanvas("qtcard_canv","qtcard_canv",1000,650); 
  large_qtcard->Draw("zcol");
  small_qtcard->Draw("zcolsame");
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
  qtcard_canv->SetGrid(0,0);
  qtcard_canv->Write();

  TCanvas * qtchan_canv = new TCanvas("qtchan_canv","qtchan_canv",1000,650); 
  large_qtchan->Draw("zcol");
  small_qtchan->Draw("zcolsame");
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
  qtchan_canv->SetGrid(0,0);
  qtchan_canv->Write();

  TCanvas * large_hvcrate_canv = new TCanvas("large_hvcrate_canv","large_hvcrate_canv",1000,650); 
  large_hvcrate->Draw("zcol");
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
  large_hvcrate_canv->SetGrid(0,0);
  large_hvcrate_canv->Write();

  TCanvas * large_hvslot_canv = new TCanvas("large_hvslot_canv","large_hvslot_canv",1000,650); 
  large_hvslot->Draw("zcol");
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
  large_hvslot_canv->SetGrid(0,0);
  large_hvslot_canv->Write();

  TCanvas * large_hvchan_canv = new TCanvas("large_hvchan_canv","large_hvchan_canv",1000,650); 
  large_hvchan->Draw("zcol");
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
  large_hvchan_canv->SetGrid(0,0);
  large_hvchan_canv->Write();

  TCanvas * small_hvboard_canv = new TCanvas("small_hvboard_canv","small_hvboard_canv",1000,650); 
  small_hvboard->GetXaxis()->SetRangeUser(-46,46);
  small_hvboard->GetYaxis()->SetRangeUser(-46,46);
  small_hvboard->Draw("zcol");
  smalltxt->Draw("textsame");
  short_vline->Draw();
  short_hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  small_hvboard_canv->SetGrid(0,0);
  small_hvboard_canv->Write();

  TCanvas * small_hvchip_canv = new TCanvas("small_hvchip_canv","small_hvchip_canv",1000,650); 
  small_hvchip->GetXaxis()->SetRangeUser(-46,46);
  small_hvchip->GetYaxis()->SetRangeUser(-46,46);
  small_hvchip->Draw("zcol");
  smalltxt->Draw("textsame");
  short_vline->Draw();
  short_hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  small_hvchip_canv->SetGrid(0,0);
  small_hvchip_canv->Write();

  TCanvas * small_hvchan_canv = new TCanvas("small_hvchan_canv","small_hvchan_canv",1000,650); 
  small_hvchan->GetXaxis()->SetRangeUser(-46,46);
  small_hvchan->GetYaxis()->SetRangeUser(-46,46);
  small_hvchan->Draw("zcol");
  smalltxt->Draw("textsame");
  short_vline->Draw();
  short_hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  small_hvchan_canv->SetGrid(0,0);
  small_hvchan_canv->Write();

  TCanvas * small_hvaddress_canv = new TCanvas("small_hvaddress_canv","small_hvaddress_canv",1000,650); 
  small_hvaddress->GetXaxis()->SetRangeUser(-46,46);
  small_hvaddress->GetYaxis()->SetRangeUser(-46,46);
  small_hvaddress->Draw("zcol");
  small_hvaddress->SetMarkerSize(0.8);
  small_hvaddress->Draw("textsame");
  //small_hvaddress_char->Draw("textsame");
  short_vline->Draw();
  short_hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  small_hvaddress_canv->SetGrid(0,0);
  small_hvaddress_canv->Write();


  gStyle->SetOptStat(0);
  gStyle->SetPalette(3,0);

  TCanvas * trg_canv = new TCanvas("trg_canv","trg_canv",2000,2000); 
  large_trg->GetXaxis()->SetRangeUser(-100,100);
  large_trg->GetYaxis()->SetRangeUser(-100,100);
  large_sel->GetXaxis()->SetRangeUser(-100,100);
  large_sel->GetYaxis()->SetRangeUser(-100,100);
  large_sel->Draw("acol");
  small_sel->Draw("acolsame");
  large_trg->Draw("aboxsame");
  small_trg->Draw("aboxsame");
  //for(int ii=0; ii<Ndott; ii++) dott[ii]->Draw();
  for(int ii=0; ii<Ntrgl; ii++) trgl[ii]->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    ibox[ii]->Draw();
    obox[ii]->Draw();
    obox2[ii]->Draw();
  };
  for(int ii=0; ii<Nobl; ii++) obl[ii]->Draw();
  for(int ii=0; ii<Netac; ii++) etac[ii]->Draw();
  trg_canv->SetGrid(0,0);
  trg_canv->Write();
  trg_canv->Print("trig_pic.png","png");


  TCanvas * trg_canv2 = new TCanvas("trg_canv2","trg_canv2",1500,1500); 
  large_trg->GetXaxis()->SetRangeUser(-100,100);
  large_trg->GetYaxis()->SetRangeUser(-100,100);
  large_sel->GetXaxis()->SetRangeUser(-100,100);
  large_sel->GetYaxis()->SetRangeUser(-100,100);
  large_sel->Draw("acol");
  small_sel->Draw("acolsame");
  //large_trg->Draw("aboxsame");
  //small_trg->Draw("aboxsame");
  for(int ii=0; ii<Ndott; ii++) dott[ii]->Draw();
  for(int ii=0; ii<Ntrgl; ii++) trgl[ii]->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    ibox[ii]->Draw();
    obox[ii]->Draw();
    obox2[ii]->Draw();
  };
  for(int ii=0; ii<Nobl; ii++) obl[ii]->Draw();
  //for(int ii=0; ii<Netac; ii++) etac[ii]->Draw();
  trg_canv2->SetGrid(0,0);
  trg_canv2->Write();
  trg_canv2->Print("trig2_pic.png","png");


  gStyle->SetPalette(1,0);
  TCanvas * jptb_canv = new TCanvas("jptb_canv","jptb_canv",2000,2000); 
  large_jptb->GetXaxis()->SetRangeUser(-100,100);
  large_jptb->GetYaxis()->SetRangeUser(-100,100);
  large_jptb->Draw("acol");
  small_jptb->Draw("acolsame");
  //for(int ii=0; ii<Ndott; ii++) dott[ii]->Draw();
  for(int ii=0; ii<Ntrgl; ii++) trgl[ii]->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    ibox[ii]->Draw();
    obox[ii]->Draw();
    obox2[ii]->Draw();
  };
  for(int ii=0; ii<Nobl; ii++) obl[ii]->Draw();
  //for(int ii=0; ii<Netac; ii++) etac[ii]->Draw();
  jptb_canv->SetGrid(0,0);
  jptb_canv->Write();
  jptb_canv->Print("jptb_pic.png","png");


  TCanvas * jpm_canv = new TCanvas("jpm_canv","jpm_canv",2000,2000); 
  large_jpm->GetXaxis()->SetRangeUser(-100,100);
  large_jpm->GetYaxis()->SetRangeUser(-100,100);
  large_jpm->Draw("acol");
  small_jpm->Draw("acolsame");
  //for(int ii=0; ii<Ndott; ii++) dott[ii]->Draw();
  for(int ii=0; ii<Ntrgl; ii++) trgl[ii]->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    ibox[ii]->Draw();
    obox[ii]->Draw();
    obox2[ii]->Draw();
  };
  for(int ii=0; ii<Nobl; ii++) obl[ii]->Draw();
  //for(int ii=0; ii<Netac; ii++) etac[ii]->Draw();
  jpm_canv->SetGrid(0,0);
  jpm_canv->Write();
  jpm_canv->Print("jpm_pic.png","png");


  // print qtslot number in fms (was used for determing qtslot <--> jet patch)
  TCanvas * qtslotnum_canv = new TCanvas("qtslotnum_canv","qtslotnum_canv",4000,1000); 
  large_qtslot->Draw("textzcol");
  small_qtslot->Draw("textzcolsame");
  //largetxt->Draw("textsame");
  //smalltxt->Draw("textsame");
  vline->Draw();
  hline->Draw();
  for(Int_t ii=0; ii<4; ii++) 
  {
    svline[ii]->Draw();
    shline[ii]->Draw();
    ibox[ii]->Draw();
    obox[ii]->Draw();
  };
  qtslot_canv->SetGrid(0,0);
  qtslotnum_canv->Print("qtslot_num.png","png");
};


Double_t XofEta(Double_t eta0)
{
  return 720 * tan(2*atan2(exp(-1*eta0),1));
};


Int_t JPTB(Int_t nstb0, Int_t chan0, Int_t qtslot0)
{
  if(nstb0==1)
  {
    if(qtslot0<11)
    {
      if(chan0<=289) return 2; // north top
      else return 3; // north bottom
    }
    else return 0; // qtslot 11 not in trigger
  }
  else if(nstb0==2)
  {
    if(qtslot0<11)
    {
      if(chan0<=289) return 4; // south top
      else return 1; // south bottom
    }
    else return 0; // qtslot 11 not in trigger
  }
  else if(nstb0==3)
  {
    if(chan0<=144) return 2; // north top
    else return 3; // north bottom
  }
  else if(nstb0==4)
  {
    if(chan0<=144) return 4; // south top
    else return 1; // south bottom
  }
  return 0;
};


Int_t JPM(Int_t nstb0, Int_t chan0, Int_t qtslot0)
{
  // run 15
  /*
  if(qtslot0==9 || qtslot0==10)
  {
    if(nstb0==1) return 1; // north middle
    else if (nstb0==2) return 2; // south middle
  }
  else if(qtslot0==3 || qtslot0==4)
  {
    if(nstb0==3) return 1; // north middle
    else if(nstb0==4) return 2; // south middle
  };
  return 0;
  */

  // runs 12 and 13 ??
  if(qtslot0==1 || qtslot0==2)
  {
    if(chan0<=144) return 3; // top
    else return 4; // bottom
  }
  else if(qtslot0==3 || qtslot0==4)
  {
    if(nstb0==3) return 1; // north middle
    else if(nstb0==4) return 2; // south middle
  }
  else if(qtslot0>=5 && qtslot0<=7)
  {
    if(chan0<=289) return 3; // top
    else return 4; // bottom
  }
  else if(qtslot0>=8 && qtslot0<=10)
  {
    if(nstb0==1) return 1; // north middle
    else if (nstb0==2) return 2; // south middle
  }
  return 0;
};
