void mk_python_if()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * tr = (TTree*) infile->Get("geotr");
  Int_t chan,hvcrate,nstb;
  tr->SetBranchAddress("chan",&chan);
  tr->SetBranchAddress("nstb",&nstb);
  tr->SetBranchAddress("hvcrate",&hvcrate);
  gSystem->RedirectOutput("python_if.py","w");
  printf("        if ( self.detector==2 and (\n");
  gSystem->RedirectOutput(0);
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    if(nstb==2 && hvcrate==7008)
    {
      gSystem->RedirectOutput("python_if.py","a");
      printf("             self.channel==%d or\n",chan);
      gSystem->RedirectOutput(0);
    };
  };
  gSystem->RedirectOutput("python_if.py","a");
  printf("             ) ):",chan);
  gSystem->RedirectOutput(0);
  printf("python_if.py created\n");
};
