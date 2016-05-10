// prints list of unused lecroy channels

void print_unused_lecroy_channels()
{
  TFile * infile = new TFile("geotr.root","READ");
  TTree * tr = (TTree*) infile->Get("geotr");
  char cut[128];
  for(Int_t cr=7005; cr<=7008; cr++)
  {
    for(Int_t sl=0; sl<16; sl++)
    {
      for(Int_t ch=0; ch<16; ch++)
      {
        sprintf(cut,"hvcrate==%d && hvslot==%d && hvchan==%d",cr,sl,ch);
        if(!(tr->GetEntries(cut))) printf("%d %d %d\n",cr,sl,ch);
      };
    };
  };
};
