// makes a tree based on map file

void mk_tree(const char * filename="FULL_MAP")
{
  TFile * outfile = new TFile("geotr.root","RECREATE");
  TTree * tr = new TTree();
  char str[512];
  strcpy(str,"nstb/I:chan/I:row/I:col/I"); // cell coordinates
  sprintf(str,"%s:pp/I:pprow/I:ppcol/I",str); // patch panel coordinates
  sprintf(str,"%s:qtcrate/I:qtslot/I:qtcard/I:qtchan/I",str); // qt coordinates
  sprintf(str,"%s:id1/I:id2/I:id3/I:id4/I:id5/C",str); // hv coordinates
  tr->ReadFile(filename,str);

  TTree * outtr = new TTree();
  Int_t nstb,chan,row,col;
  Int_t pp,pprow,ppcol;
  Int_t qtcrate,qtslot,qtcard,qtchan;
  Int_t id1,id2,id3,id4;
  char id5[16];
  char cell_type[32];
  char hvaddress_char[8];
  Int_t hvcrate,hvboard,hvchip,hvchan,hvaddress,hvslot;
  tr->SetBranchAddress("nstb",&nstb);
  tr->SetBranchAddress("chan",&chan);
  tr->SetBranchAddress("row",&row);
  tr->SetBranchAddress("col",&col);
  tr->SetBranchAddress("pp",&pp);
  tr->SetBranchAddress("pprow",&pprow);
  tr->SetBranchAddress("ppcol",&ppcol);
  tr->SetBranchAddress("qtcrate",&qtcrate);
  tr->SetBranchAddress("qtslot",&qtslot);
  tr->SetBranchAddress("qtcard",&qtcard);
  tr->SetBranchAddress("qtchan",&qtchan);
  tr->SetBranchAddress("id1",&id1);
  tr->SetBranchAddress("id2",&id2);
  tr->SetBranchAddress("id3",&id3);
  tr->SetBranchAddress("id4",&id4);
  tr->SetBranchAddress("id5",id5);

  outtr->Branch("nstb",&nstb,"nstb/I"); // cell coordinates
  outtr->Branch("chan",&chan,"chan/I");
  outtr->Branch("row",&row,"row/I");
  outtr->Branch("col",&col,"col/I");
  outtr->Branch("pp",&pp,"pp/I"); // patch panel coordinates
  outtr->Branch("pprow",&pprow,"pprow/I");
  outtr->Branch("ppcol",&ppcol,"ppcol/I");
  outtr->Branch("qtcrate",&qtcrate,"qtcrate/I"); // qt coordinates
  outtr->Branch("qtslot",&qtslot,"qtslot/I"); 
  outtr->Branch("qtcard",&qtcard,"qtcard/I");
  outtr->Branch("qtchan",&qtchan,"qtchan/I");
  outtr->Branch("hvcrate",&hvcrate,"hvcrate/I"); // lecroy crate (large)
  outtr->Branch("hvboard",&hvboard,"hvboard/I"); // yale board, russian ?? (small)
  outtr->Branch("hvchip",&hvchip,"hvchip/I"); // mother board chip (small)
  outtr->Branch("hvslot",&hvslot,"hvslot/I"); // lecroy slot (large)
  outtr->Branch("hvchan",&hvchan,"hvchan/I"); // lecroy channel (large), mother board channel (small)
  outtr->Branch("hvaddress",&hvaddress,"hvaddress/I"); // yale daughter spigot, russian base address (small)
  outtr->Branch("hvaddress_char",hvaddress_char,"hvaddress_char/C"); // hvaddress in string format
  outtr->Branch("cell_type",cell_type,"cell_type/C");

  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    // classify cell types
    if(nstb==1||nstb==2)
    {
      if( nstb==1 && 
          (chan==9 || chan==10 || chan==28) )
        strcpy(cell_type,"not_stacked");
      else if( nstb==1 && row==7 && 
          col>=10 && col<=15 )
        strcpy(cell_type,"large_resistive");
      else if( ( nstb==1 &&
                 ( (chan>=25 && chan<=27) ||
                   (chan>=43 && chan<=45) ||
                   (chan>=62 && chan<=63) )) ||
               col==9+row ||
               col==16 ||
               col==42-row ||
               row%33==0 )
        strcpy(cell_type,"large_fermi");
      else strcpy(cell_type,"large_psu");
    }
    else
    {
      if((row>=0 && row<=6 && col>=0 && col<=3) ||
          (row>=8 && row<=15 && col>=5 && col<=11) ||
          (row>=17 && row<=23 && col>=0 && col<=3))
        strcpy(cell_type,"small_russian");
      else strcpy(cell_type,"small_yale");
    };
    // id# --> hv coordinates
    if(nstb==1 || nstb==2)
    {
      hvcrate = id1;
      hvboard = -1;
      hvchip = -1;
      hvslot = id3;
      hvchan = id4;
      hvaddress = -1;
      strcpy(hvaddress_char,"0");
    }
    else
    {
      hvcrate = -1;
      hvboard = id1;
      hvchip = id2;
      hvslot = -1;
      hvchan = id3;
      if(!strcmp(id5,"0xE0")) hvaddress=0xE0;
      else if(!strcmp(id5,"0xE2")) hvaddress=0xE2;
      else if(!strcmp(id5,"0xE4")) hvaddress=0xE4;
      else if(!strcmp(id5,"0xE6")) hvaddress=0xE6;
      else if(!strcmp(id5,"0xE8")) hvaddress=0xE8;
      else if(!strcmp(id5,"0xEA")) hvaddress=0xEA;
      else if(!strcmp(id5,"0xEC")) hvaddress=0xEC;
      else if(!strcmp(id5,"0xEE")) hvaddress=0xEE;
      else if(!strcmp(id5,"0xF0")) hvaddress=0xF0;
      else if(!strcmp(id5,"0xF2")) hvaddress=0xF2;
      else if(!strcmp(id5,"0xF4")) hvaddress=0xF4;
      else if(!strcmp(id5,"0xF6")) hvaddress=0xF6;
      else if(!strcmp(id5,"0xF8")) hvaddress=0xF8;
      else if(!strcmp(id5,"0xFA")) hvaddress=0xFA;
      else if(!strcmp(id5,"0xFC")) hvaddress=0xFC;
      else if(!strcmp(id5,"0xFE")) hvaddress=0xFE;
      sprintf(hvaddress_char,"%c%c",id5[2],id5[3]);
    };
    outtr->Fill();
  };
  outtr->Write("geotr");
  printf("geotr.root created\n");
};
