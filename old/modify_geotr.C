// make modifications to geotr
// DEPRECATED BY FMS_MAP CODE

void modify_geotr()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * tr = (TTree*) infile->Get("geotr");
  Int_t row,col,nstb;
  Int_t cell[4][34][17];
  tr->SetBranchAddress("nstb",&nstb);
  tr->SetBranchAddress("row",&row);
  tr->SetBranchAddress("col",&col);

  for(Int_t n=0; n<4; n++)
  {
    for(Int_t r=0; r<34; r++)
    {
      for(Int_t c=0; c<17; c++)
      {
        cell[n][r][c]=0;
      };
    };
  };

  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    cell[nstb-1][row][col]=1;
  };

  TFile * outfile = new TFile("new_geotr.root","RECREATE");
  TTree * ntr = new TTree("geotr","geotr");
  Int_t nn,rr,cc,chan;
  char cell_type[32];
  ntr->Branch("nstb",&nn,"nstb/I");
  ntr->Branch("row",&rr,"row/I");
  ntr->Branch("col",&cc,"col/I");
  ntr->Branch("chan",&chan,"chan/I");
  ntr->Branch("cell_type",cell_type,"cell_type/C");
  for(Int_t n=0; n<4; n++)
  {
    for(Int_t r=0; r<34; r++)
    {
      for(Int_t c=0; c<17; c++)
      {
        if(cell[n][r][c]==1)
        {
          // classify cell types
          if(n==0||n==1)
          {
            if(r==0 ||
               (r==1 && c==10) ||
               (r==2 && c==11) ||
               (r==3 && c==12) ||
               (r==4 && c==13) ||
               (r==5 && c==14) ||
               (r==6 && c==15) ||
               c==16 ||
               (r==27 && c==15) ||
               (r==28 && c==14) ||
               (r==29 && c==13) ||
               (r==30 && c==12) ||
               (r==31 && c==11) ||
               (r==32 && c==10) ||
               r==33) strcpy(cell_type,"large_edge");
            else strcpy(cell_type,"large_regular");
          }
          else
          {
            if((r>=0 && r<=6 && c>=0 && c<=3) ||
               (r>=8 && r<=15 && c>=5 && c<=11) ||
               (r>=17 && r<=23 && c>=0 && c<=3))
              strcpy(cell_type,"small_russian");
            else strcpy(cell_type,"small_yale");
          };
          nn=n+1;
          rr=r;
          cc=c;
          if(nn==1||nn==2) chan=cc+rr*17+1;
          else chan=cc+rr*12+1;
          printf("ch%dn%dr%dc%d_%s\n",chan,nn,rr,cc,cell_type);
          ntr->Fill();
        };
      };
    };
  };
  ntr->Write();
};



