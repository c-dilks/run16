Double_t small_cell_LUT(Int_t val)
{
	Double_t r1=255000.;
	Double_t r2=40000.;
	Double_t rdac=50000.;
	Double_t vref=1.228;
	Double_t vscale=200.;
	Double_t diodes=.001;
	Double_t correction=1.;
	Float_t trdac=rdac/256*(256-val)*correction;
	Float_t reg=(r1+r2+trdac)/(r2+trdac)*vref;
	return (reg-diodes)*vscale;
}

Int_t small_cell_LUT_inv(Double_t val)
{
	Double_t r1=255000.;
	Double_t r2=40000.;
	Double_t rdac=50000.;
	Double_t vref=1.228;
	Double_t vscale=200.;
	Double_t diodes=.001;
	Double_t correction=1.;
  Float_t reg = val/vscale+diodes;
  Float_t trdac = (vref*(r1+r2)-reg*r2)/(reg-vref);
  return (Int_t) (256-256*trdac/(rdac*correction));
}
