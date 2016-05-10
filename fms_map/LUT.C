// various LUT functions

void LUT()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * tr = (TTree*) infile->Get("geotr");
  Int_t nstb,chan,row,col;
  Int_t pp,pprow,ppcol;
  Int_t qtcrate,qtslot,qtcard,qtchan;
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
  tr->SetBranchAddress("hvcrate",&hvcrate);
  tr->SetBranchAddress("hvboard",&hvboard);
  tr->SetBranchAddress("hvchip",&hvchip);
  tr->SetBranchAddress("hvchan",&hvchan);
  tr->SetBranchAddress("hvaddress",&hvaddress);
  tr->SetBranchAddress("hvslot",&hvslot);
}

// qt bit shift file <--> fms coords
void CtoQTbs(Int_t nstb0, Int_t row0, Int_t col0)
{
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    if(nstb==nstb0 && row==row0 && col==col0)
      printf("qtcrate=%d qtslot-1=%d 8*qtcard+qtslot=%d\n",
        qtcrate,qtslot-1,8*qtcard+qtslot);
  };
}
