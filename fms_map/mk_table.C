void mk_table()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * tr = (TTree*) infile->Get("geotr");

  gROOT->ProcessLine(".! touch table_large.txt; rm table_large.txt");
  gROOT->ProcessLine(".! touch table_small.txt; rm table_small.txt");

  tr->SetScanField(2000);

  gSystem->RedirectOutput("table_large.txt");
  tr->Scan("nstb:chan:row:col:pp:pprow:ppcol:qtcrate:qtslot:qtcard:qtchan:hvcrate:hvslot:hvchan:cell_type",
    "nstb==1||nstb==2");

  gSystem->RedirectOutput("table_small.txt");
  tr->Scan("nstb:chan:row:col:pp:pprow:ppcol:qtcrate:qtslot:qtcard:qtchan:hvboard:hvchip:hvchan:hvaddress_char:cell_type",
    "nstb==3||nstb==4");

  gSystem->RedirectOutput(0);
};
