#include <TGTextEntry.h>
#include <TGButtonGroup.h>
#include <TGLabel.h>
#include <TGComboBox.h>
#include <TApplication.h>

using namespace std;

////////////////////////////////////////////////////////////

class CoordBox : public TGGroupFrame
{
  public:
    CoordBox(const TGWindow * p, const char * name, 
             const char * title, char labels[][32], const Int_t num);
    void SetCoords(Int_t settings[]);
    Int_t GetCoords(Int_t settings[]);
    void Clear();

    TGHorizontalFrame * fHoriz;
    TGLabel * fText_label[10];
    TGTextEntry * fText[10];

  protected:
    Int_t num_vals;
    char box_name[32];


    ClassDef(CoordBox,0)
};

/*********************************************/

CoordBox::CoordBox(const TGWindow *p, const char * name, 
                   const char * title, char labels[][32], const int num) :
  TGGroupFrame(p,title)
{
  fHoriz = new TGHorizontalFrame(this);
  AddFrame(fHoriz, new TGLayoutHints(kLHintsExpandX | kLHintsCenterY));

  num_vals = num;
  strcpy(box_name,name);

  for(Int_t i=0; i<num_vals; i++)
  {
    fText_label[i] = new TGLabel(fHoriz,labels[i]);
    fHoriz->AddFrame(fText_label[i], new TGLayoutHints(kLHintsLeft | kLHintsExpandY,20,0,5,5));
    fText[i] = new TGTextEntry(fHoriz);
    fHoriz->AddFrame(fText[i], new TGLayoutHints(kLHintsLeft | kLHintsExpandY,20,0,5,5));
  };
}

void CoordBox::SetCoords(Int_t settings[])
{
  char settings_txt[8];
  for(Int_t i=0; i<num_vals; i++)
  {
    if(!strcmp(box_name,"SHV") && i==3)
      sprintf(settings_txt,"%X",settings[i]);
    else
      sprintf(settings_txt,"%d",settings[i]);
    fText[i]->SetText(settings_txt);
  };
}

Int_t CoordBox::GetCoords(Int_t settings[])
{
  Int_t retval=0;
  Int_t scanval;
  for(Int_t i=0; i<num_vals; i++) 
  {
    if(!strcmp(box_name,"SHV") && i==3) 
      scanval = sscanf(fText[i]->GetText(),"%X",&(settings[i]));
    else scanval = sscanf(fText[i]->GetText(),"%d",&(settings[i]));
    if(scanval!=1) settings[i]=-1;
    else retval++;
  };
  return retval; // return number of entries in instance of CoordBox
};

void CoordBox::Clear()
{
  for(Int_t i=0; i<num_vals; i++) fText[i]->Clear();
};


////////////////////////////////////////////////////////////

class MainFrame
{
  public:
    TGMainFrame * fMain;
    CoordBox * fFmsCoords;
    void Init();
    void ClearAll();
    void Obtain();
    Int_t SearchGeotr(char * name, Int_t num, Int_t settings[]);
    void SetCoordBoxes(Int_t geotr_ent);
    void GetGainString(char return_string[], Int_t nstb0, Int_t chan0, Int_t qtc, Int_t qts, Int_t qtch);

  protected:
    CoordBox * fFMSCH_Coords;
    CoordBox * fFMS_Coords;
    CoordBox * fPP_Coords;
    CoordBox * fQT_Coords;
    CoordBox * fBS_Coords;
    CoordBox * fJEVP_Coords;
    CoordBox * fLHV_Coords;
    CoordBox * fSHV_Coords;

    TGCompositeFrame * fBottomFrame;
    TGTextButton * fClear_Button;
    TGTextButton * fObtain_Button;
    TGLabel * fStatus;

    TFile * geofile;
    TTree * geotr;

    Int_t nstb,chan,row,col;
    Int_t pp,pprow,ppcol;
    Int_t qtcrate,qtslot,qtcard,qtchan;
    Int_t hvcrate,hvboard,hvchip,hvslot,hvchan,hvaddress;
    char hvaddress_char[16];
    char cell_type[32];

    TTree * qtbstr[4];
    Int_t qtbs_slot,qtbs_chan,qtbs_offset,qtbs;

    TTree * lhvtr;
    TTree * shvtr;
    Int_t hv_nstb,hv_chan,hv_row,hv_col,voltage;
    Float_t gain;
    char voltage_char[8];

    ClassDef(MainFrame,0)
};

/*********************************************/

MainFrame::MainFrame()
{
  // load trees and set addresses
  Init();

  fMain = new TGMainFrame(gClient->GetRoot(), 20, 20, kVerticalFrame);
  fMain->SetCleanup(kDeepCleanup);

  // --
  const Int_t FMSCH_num = 2;
  char FMSCH_lab[FMSCH_num][32];
  strcpy(FMSCH_lab[0],"NSTB:");
  strcpy(FMSCH_lab[1],"Channel:");
  fFMSCH_Coords = new CoordBox(fMain,"FMSCH","FMS Pb-Glass Channel",FMSCH_lab,FMSCH_num);
  fMain->AddFrame(fFMSCH_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t FMS_num = 3;
  char FMS_lab[FMS_num][32];
  strcpy(FMS_lab[0],"NSTB:");
  strcpy(FMS_lab[1],"Row:");
  strcpy(FMS_lab[2],"Col:");
  fFMS_Coords = new CoordBox(fMain,"FMS","FMS Pb-Glass Coordinates",FMS_lab,FMS_num);
  fMain->AddFrame(fFMS_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t PP_num = 4;
  char PP_lab[PP_num][32];
  strcpy(PP_lab[0],"NSTB:");
  strcpy(PP_lab[1],"PP:");
  strcpy(PP_lab[2],"PP Row:");
  strcpy(PP_lab[3],"PP Col:");
  fPP_Coords = new CoordBox(fMain,"PP","Patch Panel Coordinates",PP_lab,PP_num);
  fMain->AddFrame(fPP_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t QT_num = 4;
  char QT_lab[QT_num][32];
  strcpy(QT_lab[0],"QT Crate:");
  strcpy(QT_lab[1],"QT Slot:");
  strcpy(QT_lab[2],"QT Card:");
  strcpy(QT_lab[3],"QT Channel:");
  fQT_Coords = new CoordBox(fMain,"QT","QT Coordinates",QT_lab,QT_num);
  fMain->AddFrame(fQT_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t BS_num = 3;
  char BS_lab[BS_num][32];
  strcpy(BS_lab[0],"QT Crate:");
  strcpy(BS_lab[1],"QT Slot-1:");
  strcpy(BS_lab[2],"QT 8*Card+Chan:");
  fBS_Coords = new CoordBox(fMain,"BS","QT Coordinates (from bitshift files)",BS_lab,BS_num);
  fMain->AddFrame(fBS_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t JEVP_num = 2;
  char JEVP_lab[JEVP_num][32];
  strcpy(JEVP_lab[0],"QT Crate:");
  strcpy(JEVP_lab[1],"QT 32*(Slot-1)+8*Card+Chan");
  fJEVP_Coords = new CoordBox(fMain,"JEVP","QT Coordinates (from JEVP plots)",JEVP_lab,JEVP_num);
  fMain->AddFrame(fJEVP_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t LHV_num = 3;
  char LHV_lab[LHV_num][32];
  strcpy(LHV_lab[0],"HV Crate:");
  strcpy(LHV_lab[1],"HV Slot:");
  strcpy(LHV_lab[2],"HV Channel:");
  fLHV_Coords = new CoordBox(fMain,"LHV","Large Cell High Voltage Coordinates",LHV_lab,LHV_num);
  fMain->AddFrame(fLHV_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));

  // --
  const Int_t SHV_num = 4;
  char SHV_lab[SHV_num][32];
  strcpy(SHV_lab[0],"Device:");
  strcpy(SHV_lab[1],"Chip:");
  strcpy(SHV_lab[2],"Channel:");
  strcpy(SHV_lab[3],"Address:");
  fSHV_Coords = new CoordBox(fMain,"SHV","Small Cell High Voltage Coordinates",SHV_lab,SHV_num);
  fMain->AddFrame(fSHV_Coords, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5,5));


  // -----
  // buttons
  fBottomFrame = new TGCompositeFrame(fMain,60,20,kHorizontalFrame | kSunkenFrame);
  fClear_Button = new TGTextButton(fBottomFrame,"&Clear",150);
  fObtain_Button = new TGTextButton(fBottomFrame,"&Obtain Coordinates",150);
  fBottomFrame->AddFrame(fObtain_Button, new TGLayoutHints(kLHintsTop | kLHintsRight,2,0,2,2));
  fBottomFrame->AddFrame(fClear_Button, new TGLayoutHints(kLHintsTop | kLHintsRight,2,0,2,2));
  fClear_Button->Connect("Clicked()","MainFrame",this,"ClearAll()");
  fObtain_Button->Connect("Clicked()","MainFrame",this,"Obtain()");

  // status
  fStatus = new TGLabel(fBottomFrame,"Ready");
  fBottomFrame->AddFrame(fStatus, new TGLayoutHints(kLHintsTop | kLHintsExpandX,2,0,4,2));
  
  fMain->AddFrame(fBottomFrame, new TGLayoutHints(kLHintsBottom | kLHintsExpandX,0,0,1,0));



  // --
  fMain->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  fMain->DontCallClose();

  fMain->MapSubwindows();
  fMain->Resize();

  fMain->SetWMSizeHints(fMain->GetDefaultWidth(), fMain->GetDefaultHeight(),
      1000, 1000, 0, 0);
  fMain->SetWindowName("Text Entries");
  fMain->MapRaised();
};

void MainFrame::Init()
{
  geofile = new TFile("geotr.root","READ");
  geotr = (TTree*) geofile->Get("geotr");
  geotr->SetBranchAddress("nstb",&nstb);
  geotr->SetBranchAddress("chan",&chan);
  geotr->SetBranchAddress("row",&row);
  geotr->SetBranchAddress("col",&col);
  geotr->SetBranchAddress("pp",&pp);
  geotr->SetBranchAddress("pprow",&pprow);
  geotr->SetBranchAddress("ppcol",&ppcol);
  geotr->SetBranchAddress("qtcrate",&qtcrate);
  geotr->SetBranchAddress("qtslot",&qtslot);
  geotr->SetBranchAddress("qtcard",&qtcard);
  geotr->SetBranchAddress("qtchan",&qtchan);
  geotr->SetBranchAddress("hvcrate",&hvcrate);
  geotr->SetBranchAddress("hvboard",&hvboard);
  geotr->SetBranchAddress("hvchip",&hvchip);
  geotr->SetBranchAddress("hvslot",&hvslot);
  geotr->SetBranchAddress("hvchan",&hvchan);
  geotr->SetBranchAddress("hvaddress",&hvaddress);
  geotr->SetBranchAddress("hvaddress_char",hvaddress_char);
  geotr->SetBranchAddress("cell_type",cell_type);

  char qtbstr_file[4][32];
  for(Int_t i=0; i<4; i++) 
  {
    sprintf(qtbstr_file[i],"current_iteration/qt%d_tac.dat",i+1);
    qtbstr[i] = new TTree();
    qtbstr[i]->ReadFile(qtbstr_file[i],"qtbs_slot/I:qtbs_chan/I:qtbs_offset/I:qtbs/I");
    qtbstr[i]->SetBranchAddress("qtbs_slot",&qtbs_slot);
    qtbstr[i]->SetBranchAddress("qtbs_chan",&qtbs_chan);
    qtbstr[i]->SetBranchAddress("qtbs_offset",&qtbs_offset);
    qtbstr[i]->SetBranchAddress("qtbs",&qtbs);
  };

  lhvtr = new TTree();
  lhvtr->ReadFile("current_iteration/largeCellGains.txt",
    "hv_nstb/I:hv_chan/I:hv_row/I:hv_col/I:voltage/I:gain/F");
  lhvtr->SetBranchAddress("hv_nstb",&hv_nstb);
  lhvtr->SetBranchAddress("hv_chan",&hv_chan);
  lhvtr->SetBranchAddress("hv_row",&hv_row);
  lhvtr->SetBranchAddress("hv_col",&hv_col);
  lhvtr->SetBranchAddress("voltage",&voltage);
  lhvtr->SetBranchAddress("gain",&gain);

  shvtr = new TTree();
  shvtr->ReadFile("current_iteration/smallCellGains.txt",
    "hv_nstb/I:hv_chan/I:hv_row/I:hv_col/I:voltage_char/C:gain/F");
  shvtr->SetBranchAddress("hv_nstb",&hv_nstb);
  shvtr->SetBranchAddress("hv_chan",&hv_chan);
  shvtr->SetBranchAddress("hv_row",&hv_row);
  shvtr->SetBranchAddress("hv_col",&hv_col);
  shvtr->SetBranchAddress("voltage_char",voltage_char);
  shvtr->SetBranchAddress("gain",&gain);
};


void MainFrame::ClearAll()
{
  fFMSCH_Coords->Clear();
  fFMS_Coords->Clear();
  fPP_Coords->Clear();
  fQT_Coords->Clear();
  fBS_Coords->Clear();
  fJEVP_Coords->Clear();
  fLHV_Coords->Clear();
  fSHV_Coords->Clear();
  fStatus->SetText("All entries cleared");
};


void MainFrame::Obtain()
{
  CoordBox * choice = NULL;
  Int_t num_check=0;
  Int_t retval;
  Int_t coordinates[10];
  Int_t ent;
  retval = fFMSCH_Coords->GetCoords(coordinates);
    if(retval == fFMSCH_Coords->num_vals) { num_check++; choice = fFMSCH_Coords; };
  retval = fFMS_Coords->GetCoords(coordinates);
    if(retval == fFMS_Coords->num_vals) { num_check++; choice = fFMS_Coords; };
  retval = fPP_Coords->GetCoords(coordinates); 
    if(retval == fPP_Coords->num_vals) { num_check++; choice = fPP_Coords; };
  retval = fQT_Coords->GetCoords(coordinates);
    if(retval == fQT_Coords->num_vals) { num_check++;  choice = fQT_Coords; };
  retval = fBS_Coords->GetCoords(coordinates);
    if(retval == fBS_Coords->num_vals) { num_check++;  choice = fBS_Coords; };
  retval = fJEVP_Coords->GetCoords(coordinates);
    if(retval == fJEVP_Coords->num_vals) { num_check++;  choice = fJEVP_Coords; };
  retval = fLHV_Coords->GetCoords(coordinates);
    if(retval == fLHV_Coords->num_vals) { num_check++;  choice = fLHV_Coords; };
  retval = fSHV_Coords->GetCoords(coordinates);
    if(retval == fSHV_Coords->num_vals) { num_check++;  choice = fSHV_Coords; };

  if(num_check==0) fStatus->SetText("ERROR: too few entries");
  else if(num_check>1) fStatus->SetText("ERROR: too many entries");
  else if(num_check==1 && choice!=NULL)
  {
    choice->GetCoords(coordinates);
    ent=SearchGeotr(choice->box_name,choice->num_vals,coordinates);
    if(ent>=0)
    {
      SetCoordBoxes(ent);
    };
  };
};


Int_t MainFrame::SearchGeotr(char * name, Int_t num, Int_t se[])
{
  Int_t ent=-1;
  Int_t cnt=0;
  for(Int_t i=0; i<geotr->GetEntries(); i++)
  {
    geotr->GetEntry(i);
    if( (!strcmp(name,"FMSCH") && (se[0]==nstb && se[1]==chan)) ||
        (!strcmp(name,"FMS") && (se[0]==nstb && se[1]==row && se[2]==col)) ||
        (!strcmp(name,"PP") && (se[0]==nstb && se[1]==pp && se[2]==pprow && se[3]==ppcol)) ||
        (!strcmp(name,"QT") && (se[0]==qtcrate && se[1]==qtslot && se[2]==qtcard && se[3]==qtchan)) ||
        (!strcmp(name,"BS") && (se[0]==qtcrate && se[1]==qtslot-1 && se[2]==(8*qtcard+qtchan))) ||
        (!strcmp(name,"JEVP") && (se[0]==qtcrate && se[1]==(32*(qtslot-1)+8*qtcard+qtchan))) ||
        (!strcmp(name,"LHV") && (se[0]==hvcrate && se[1]==hvslot && se[2]==hvchan)) ||
        (!strcmp(name,"SHV") && (se[0]==hvboard%2 && se[1]==hvchip && se[2]==hvchan && se[3]==hvaddress)) )
    {
      ent = i;
      cnt++;
    };
  };
  char status_text[256];
  if(cnt==1) return ent;
  else if(cnt==0) fStatus->SetText("ERROR: requested cell not found");
  else 
  {
    sprintf(status_text,"ERROR: %d cells match request",cnt);
    fStatus->SetText(status_text);
  };
  return -1;
};


void MainFrame::SetCoordBoxes(Int_t geotr_ent)
{
  geotr->GetEntry(geotr_ent);

  char cell_gain_string[128];
  GetGainString(cell_gain_string,nstb,chan,qtcrate,qtslot-1,8*qtcard+qtchan);

  Int_t FMSCHset[3] = {nstb,chan};
  Int_t FMSset[3] = {nstb,row,col};
  Int_t PPset[4] = {nstb,pp,pprow,ppcol};
  Int_t QTset[4] = {qtcrate,qtslot,qtcard,qtchan};
  Int_t BSset[4] = {qtcrate,qtslot-1,8*qtcard+qtchan};
  Int_t JEVPset[4] = {qtcrate,32*(qtslot-1)+8*qtcard+qtchan};
  Int_t LHVset[3] = {hvcrate,hvslot,hvchan};
  Int_t SHVset[4] = {hvboard%2,hvchip,hvchan,hvaddress};

  fFMSCH_Coords->SetCoords(FMSCHset);
  fFMS_Coords->SetCoords(FMSset);
  fPP_Coords->SetCoords(PPset);
  fQT_Coords->SetCoords(QTset);
  fBS_Coords->SetCoords(BSset);
  fJEVP_Coords->SetCoords(JEVPset);
  if(nstb<3) 
  {
    fLHV_Coords->SetCoords(LHVset);
    fSHV_Coords->Clear();
  }
  else
  {
    fSHV_Coords->SetCoords(SHVset);
    fLHV_Coords->Clear();
  };
  char status_text[256];
  sprintf(status_text,"%s cell found -- %s",cell_type,cell_gain_string);
  fStatus->SetText(status_text);
};


void MainFrame::GetGainString(char cell_gain_string0[], 
   Int_t nstb0, Int_t chan0, Int_t qtc, Int_t qts, Int_t qtch)
{
  char voltage_found[16];
  Float_t gain_found;
  Int_t qtbs_found;
  char cell_gain_string0[128];

  Int_t ent;
  if(nstb0<3) ent = lhvtr->GetEntries();
  else ent = shvtr->GetEntries();

  Int_t cnt=0;

  for(Int_t i=0; i<ent; i++)
  {
    if(nstb0<3) lhvtr->GetEntry(i);
    else shvtr->GetEntry(i);
    if(hv_nstb==nstb0 && hv_chan==chan0)
    {
      if(nstb0<3) sprintf(voltage_found,"%d",voltage);
      else sprintf(voltage_found,"%s",voltage_char);
      gain_found = gain;
      cnt++;
    };
  };
  if(cnt>1 || cnt==0) strcpy(cell_gain_string0,"[hvtr error]");
  else sprintf(cell_gain_string0,"Voltage: %s  Gain: %.3f",voltage_found,gain_found);

  cnt=0;
  Int_t offset_found,qtbs_found;
  for(Int_t i=0; i<qtbstr[qtc-1]->GetEntries(); i++)
  {
    qtbstr[qtc-1]->GetEntry(i);
    if(qts==qtbs_slot && qtch==qtbs_chan)
    {
      offset_found = qtbs_offset;
      qtbs_found = qtbs;
      cnt++;
    };
  };
  if(cnt>1 || cnt==0) strcpy(cell_gain_string0,"[qtbstr error]");
  else sprintf(cell_gain_string0,"%s  Bitshift: %d  Offset: %d",cell_gain_string0,qtbs_found,offset_found);
};



////////////////////////////////////////////////////////////

void GUI_MAP()
{
  new MainFrame();
};
