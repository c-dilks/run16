void print()
{
  gStyle->SetOptStat(0);
  TFile * infile = new TFile("maps.root","READ");

  gStyle->SetPalette(55,0);
  type_canv->Print("maps.pdf(","pdf");
  pp_canv->Print("maps.pdf","pdf");
  pprow_canv->Print("maps.pdf","pdf");
  ppcol_canv->Print("maps.pdf","pdf");
  qtcrate_canv->Print("maps.pdf","pdf");
  gStyle->SetPalette(70,0);
  qtslot_canv->Print("maps.pdf","pdf");
  gStyle->SetPalette(55,0);
  qtcard_canv->Print("maps.pdf","pdf");
  qtchan_canv->Print("maps.pdf","pdf");
  large_hvcrate_canv->Print("maps.pdf","pdf");
  large_hvslot_canv->Print("maps.pdf","pdf");
  large_hvchan_canv->Print("maps.pdf","pdf");
  small_hvboard_canv->Print("maps.pdf","pdf");
  small_hvchip_canv->Print("maps.pdf","pdf");
  small_hvchan_canv->Print("maps.pdf","pdf");
  gStyle->SetPalette(50,0);
  small_hvaddress_canv->Print("maps.pdf)","pdf");
};
