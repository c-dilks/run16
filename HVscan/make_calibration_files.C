// builds {large,small}_gaincurve_par.txt for Thomas's fmsvoltages software;
// these are library files with columns [nstb] [row] [col]
//
// set use_averages to 1 if you would rather just use average gain curve parameters
// for each cell; these average values are expect_alpha_*, which should be
// copied from hv_scan.C

void make_calibration_files(const char * filename="hvtr.root", Bool_t use_averages=0)
{
  const Double_t expect_alpha_large = 12.23;
  const Double_t expect_alpha_russian = 3.93;
  const Double_t expect_alpha_yale = 7.80;

  TFile * infile = new TFile(filename,"READ");
  TTree * tr = (TTree*) infile->Get("hvtr");
  Int_t nstb,row,col;
  Double_t scale,alpha;
  char cell_type[32];
  tr->SetBranchAddress("nstb",&nstb);
  tr->SetBranchAddress("row",&row);
  tr->SetBranchAddress("col",&col);
  tr->SetBranchAddress("scale",&scale);
  tr->SetBranchAddress("alpha",&alpha);
  tr->SetBranchAddress("cell_type",cell_type);

  char large_file[64];
  char small_file[64];
  strcpy(large_file,"large_gaincurve_par.txt");
  strcpy(small_file,"small_gaincurve_par.txt");
  char initialise_large[256];
  char initialise_small[256];
  sprintf(initialise_large,".! touch %s ; rm %s",large_file,large_file);
  sprintf(initialise_small,".! touch %s ; rm %s",small_file,small_file);
  printf("%s\n",initialise_large);
  printf("%s\n",initialise_small);

  gROOT->ProcessLine(initialise_large);
  gROOT->ProcessLine(initialise_small);

  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    if(use_averages)
    {
      if(!strcmp(cell_type,"large_psu") ||
         !strcmp(cell_type,"large_fermi") ||
         !strcmp(cell_type,"large_resistive") ||
         !strcmp(cell_type,"not_stacked")) alpha=expect_alpha_large;
      else if(!strcmp(cell_type,"small_russian")) 
        alpha=expect_alpha_russian;
      else if(!strcmp(cell_type,"small_yale"))
        alpha=expect_alpha_yale;
      else
        printf("error\n");
    };
    if(nstb==1 || nstb==2) gSystem->RedirectOutput(large_file);
    else gSystem->RedirectOutput(small_file);
    printf("%d %d %d %f %f\n",nstb,row,col,scale,alpha);
  };
  gSystem->RedirectOutput(0);
  printf("%s created\n",large_file);
  printf("%s created\n",small_file);
};
