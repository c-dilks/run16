// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <stdio.h>
#include <string>
#include "strfilter.h"
#include "usbi2cio.h"
#include "HVSet.h"
#include "I2Call.h"



BOOL flag;
HVSet HVYale;
HVSet HVPsu;
HVSet Voltage;
char LineReport[120];
	int DeviceInUse=0;
	LONG *IoRead;
	LONG ulIoPortConfig;
	HANDLE hDevice[127];
	I2C_TRANS TransI2C;
	HINSTANCE hDLL;
	typedef WORD(CALLBACK* GETDLLVERSION)(void);
	typedef HANDLE(CALLBACK* OPENDEVICEINSTANCE)(LPSTR,BYTE);
	typedef BOOL(CALLBACK* CLOSEDEVICEINSTANCE)(HANDLE);
	typedef BOOL(CALLBACK* DETECTDEVICE)(HANDLE);
  typedef BYTE(CALLBACK* GETDEVICECOUNT)(LPSTR);
  typedef BYTE(CALLBACK* GETDEVICEINFO)(LPSTR,LPDEVINFO);
  typedef HANDLE(CALLBACK* OPENDEVICEBYSERIALID)(LPSTR,LPSTR);
	typedef BOOL(CALLBACK* GETSERIALID)(HANDLE,LPSTR);
	typedef BOOL(CALLBACK* CONFIGIOPORTS)(HANDLE,ULONG);
	typedef BOOL(CALLBACK* GETIOCONFIG)(HANDLE,LPLONG);
	typedef BOOL(CALLBACK* READIOPORTS)(HANDLE,LPLONG);
	typedef BOOL(CALLBACK* WRITEIOPORTS)(HANDLE,ULONG,ULONG);
	typedef BOOL(CALLBACK* READI2C)(HANDLE,PI2C_TRANS);
	typedef BOOL(CALLBACK* WRITEI2C)(HANDLE,PI2C_TRANS);
	GETDLLVERSION GetDllVersion;
	OPENDEVICEINSTANCE OpenDeviceInstance;
	CLOSEDEVICEINSTANCE CloseDeviceInstance;
	DETECTDEVICE DetectDevice;
  GETDEVICECOUNT GetDeviceCount;
  GETDEVICEINFO GetDeviceInfo;
  OPENDEVICEBYSERIALID OpenDeviceBySerialId;
	GETSERIALID GetSerialId;
	CONFIGIOPORTS ConfigIoPorts;
	GETIOCONFIG GetIoConfig;
	READIOPORTS ReadIoPorts;
	WRITEIOPORTS WriteIoPorts;
	READI2C ReadI2c;
	WRITEI2C WriteI2c;

int _tmain(int argc, _TCHAR* argv[])
{	
	int ScriptRepeat[10];
	int ScriptRepeatCount[10];
	char LastMemRead[256]="";
	char NextMemWrit[256]="";
	for(int jj=0;jj<10;jj++)
	{
		ScriptRepeat[jj]=0;
		ScriptRepeatCount[jj]=0;
	};
	HVPsu.r1=2710000;
	HVPsu.r2= 120000;
	HVPsu.vscale=66;
	HVPsu.diodes=1.8;
	HVPsu.SetBaseType("PSU");
	HVPsu.ModeUsed=0X14;
	Voltage=HVPsu;
	LineReport[0]=0;
	int loglimit=1000;
	filebuf infiles[10];
	istream* strms[10];
	string filenames[10];
	int curr_cnt[10];
	string cmdarg[5][10];
	for(int j=0;j<5;j++)cmdarg[j][0]="XX";
	string newcmdarg[5];
	for(int j=0;j<5;j++)newcmdarg[j]=cmdarg[j][0];
	strfilter* sfilter=new strfilter(0,newcmdarg);
	
	string after=sfilter->ArgReplace("0 $0 1 $1");
	cout<<after<<"\n";
	int ncmdarg[10]={0,0,0,0,0,0,0,0,0,0};

	int level=0;
	printf("Number of ARgs=%d \n",argc);
	
		printf("%s \n",argv[0]);
		level=0;
		filenames[level]="cin:";
		strms[level]=&cin;
		curr_cnt[level]=0;
		string str="";
		int length=(int) strlen(argv[0]);
		char tmp[100];
		tmp[length+1]=0;
		strcpy(tmp,argv[0]);
		str=(const char*) tmp;
		int sloc=(int) str.rfind("console.exe");
		string directory=str.erase(sloc);
		cout<<directory<<"\n\n";
		level=1;
		curr_cnt[level]=0;
		filenames[level]="first.txt";
		string file1=directory+filenames[level];
		cout<<file1<<"\n";
		infiles[level].open(file1.c_str(),ios::in);
		istream* thesrc;
		bool read_cin=1;
		if(infiles[level].is_open())
		{
			strms[level]=new istream(&(infiles[level]));
			thesrc=strms[level];
			read_cin=0;
		};
		filebuf logfile;
		string log=directory+"log.txt";
		logfile.open(log.c_str(),ios::out);
		ostream* logstrm=new ostream(&logfile);
    hDLL = LoadLibrary("UsbI2cIo.dll"); 
	GetDllVersion=(GETDLLVERSION)GetProcAddress(hDLL,"DAPI_GetDllVersion");
	OpenDeviceInstance=(OPENDEVICEINSTANCE)GetProcAddress(hDLL,"DAPI_OpenDeviceInstance");
	GetDeviceCount=(GETDEVICECOUNT) GetProcAddress(hDLL,"DAPI_GetDeviceCount");
	ReadI2c=(READI2C)GetProcAddress(hDLL,"DAPI_ReadI2c");
    WriteI2c=(WRITEI2C)GetProcAddress(hDLL,"DAPI_WriteI2c");
	
	WORD vers=GetDllVersion();
	printf("vers=%d \n",vers);
	WORD DeviceCount=GetDeviceCount("UsbI2cIo");
	printf("Number of Devices=%d \n",DeviceCount);
	for(int jcntr=0;jcntr<DeviceCount;jcntr++)
	{
		hDevice[jcntr]=OpenDeviceInstance("UsbI2cIo", jcntr);
		printf(" Device # %d Instance=%d \n",jcntr, (int) hDevice[jcntr]);
	};
	  LONG lReadCnt;
	  int Writ=0;
	  TransI2C.byTransType = I2C_TRANS_NOADR;
	  TransI2C.wMemoryAddr = 0;      // number of bytes to read
	 // I2Ccom i2com(hDLL,hDevice[0]);
	  I2Call* i2call=new I2Call(&hDLL,&(hDevice[0]),&TransI2C);
	  i2call->DeviceCount=DeviceCount;
	  if(DeviceCount==0)i2call->PathState.check_overide=true;// no devices means direct path map
	  i2call->Directory_str=directory;
	  i2call->HVPSU=&HVPsu;
	  i2call->HVYALE=&HVYale;
	
	  int loopcnt=0;
while(Writ<3)
{
	  loopcnt=0;
	  logfile.pubsync();
	  if(read_cin)
	  {
		if(i2call->PathState.ismapped)printf("dev/chip/chan=%d/%d/%d\n",i2call->PathState.dev,i2call->PathState.chip,i2call->PathState.chan);
		printf("\nEnter \n [W/R(1/0)] [Addr(hex)] [cnt:] [loop] \n");};
	  char line[100];
	  thesrc->getline(line,99);
	  (curr_cnt[level])++;
	  if(ncmdarg[level]>0)
	  {
		  string tmpline=line;
		  for(int j=0;j<5;j++)newcmdarg[j]=cmdarg[j][level];
		  sfilter->pstr=newcmdarg;
		  sfilter->nargs=ncmdarg[level];
		  string newline=sfilter->ArgReplace(tmpline);
		  strcpy(line,newline.c_str());
	  };
	  if(thesrc->eof()&&strlen(line)<4)
	  {
		  if(level>0 && ScriptRepeat[level]>0)
		  {
			  ScriptRepeat[level]--;
			  ScriptRepeatCount[level]++;
			  curr_cnt[level]=0;
			  delete strms[level];
			  infiles[level].close();
			  file1=directory+filenames[level];
			  cout<<"reopen script "<<filenames[level]<<"\n";
			  (*logstrm)<<"reopen script "<<filenames[level]<<"\n";
			  (infiles[level]).open(file1.c_str(),ios::in);
			  if((infiles[level]).is_open())
			  {
			    strms[level]=new istream(&(infiles[level]));
			    thesrc=strms[level];
			  };
		  }
		  else
		  {			  
	    ScriptRepeatCount[level]=0;
		level=level-1;
		thesrc=strms[level];
		delete strms[level+1];
		infiles[level+1].close();
		if(level==0)read_cin=1;
		  };
	  };
	  if(strncmp(line,"@",1)==0)
	  {
		char nfile[100];
		char cmdastr[10][5];
		string tmpstring(&(line[1]));
		int newcmdarg=sscanf(tmpstring.c_str(),"%s %s %s %s %s %s",nfile,
			cmdastr[0],cmdastr[1],cmdastr[2],cmdastr[3],cmdastr[4])-1;
		for(int m=0;m<5;m++){cmdarg[m][level+1]="  ";};
		for(int m=0;m<newcmdarg;m++){cmdarg[m][level+1]=cmdastr[m];};
		ncmdarg[level+1]=newcmdarg;
		file1=directory+nfile;
		if(ncmdarg>0)
		{
			cout<<"@"<<nfile<<" "<<cmdarg[0][level+1]<<" "<<cmdarg[1][level+1]<<" "
				<<cmdarg[2][level+1]<<" "<<cmdarg[3][level+1]<<" "<<cmdarg[4][level+1]
				<<"\n";
			(*logstrm)<<"@"<<nfile<<" "<<cmdarg[0][level+1]<<" "<<cmdarg[1][level+1]<<" "
				<<cmdarg[2][level+1]<<" "<<cmdarg[3][level+1]<<" "<<cmdarg[4][level+1]
				<<"\n";
		};
		if(level>8)
		{
			int done;
			printf("this program can not do so much recursion \n");
			(*logstrm)<<"exit because of too much recursion\n";
			scanf("%d",&done);
			exit(99);
		};
		(infiles[level+1]).open(file1.c_str(),ios::in);
		if((infiles[level+1]).is_open())
		{
			level++;
			strms[level]=new istream(&(infiles[level]));
			thesrc=strms[level];
			filenames[level]=nfile;
			curr_cnt[level]=0;
			read_cin=0;
		};
		Writ=2;
	  }
	  else if (strncmp("?",line,1)==0)
	  {
		  i2call->gethelp(0);
	  }
	  else if (strncmp("!",line,1)==0)
	  {
		  char cmdparts[20][20];
		  string tmpstring(&(line[1]));
		  int nscan=sscanf(tmpstring.c_str(),"%s %s %s %s %s %s %s %s %s %s",
			  cmdparts[0],
			  cmdparts[1],cmdparts[2],cmdparts[3],cmdparts[4],cmdparts[5],
			  cmdparts[6],cmdparts[7],cmdparts[8],cmdparts[9]);
		  BYTE TranError=0;
			
		  if(nscan>0)
		  {
			  if(strncmp("exit",cmdparts[0],4)==0)exit(0);
			  if(strncmp("Loadrdac",cmdparts[0],8)==0)
			  {
				  i2call->Loadrdac();
			  };

				  if(strncmp("power",cmdparts[0],5)==0)
				  {
					  BYTE value=0;
					
					  if(nscan>1)
					  {
						  if(sscanf(cmdparts[1],"%X",&value)==1)
						  {
							  i2call->powerchan(value,true);
						  }
						  else
						  {
							  i2call->powerchan(value,false);
						  }
					  }
					  else
					  {
						  i2call->powerchan(value,false);
					  };
					  TranError=i2call->CallError;
					  char ReportErr[30];
					  if(TranError==0)
					  {
						  sprintf(ReportErr,"%s[%d,%d]:",(filenames[level]).c_str(),
						curr_cnt[level],ScriptRepeatCount[level]);
					  }
					  else
					  {
						  sprintf(ReportErr,"%s[%d,err]:",(filenames[level]).c_str(),
						curr_cnt[level]);
					  };

					  printf(" %s Voltage for (chip=%X chan=%X)=%X\n",
						  ReportErr,i2call->Chip,i2call->Channel,i2call->power); 
				  };
			  if(nscan>1)
			  {
				  if(strncmp("ReadTable",cmdparts[0],9)==0)
				  {
					  string fnam=cmdparts[1];
					  i2call->GetRdacTable(fnam);
				  };
				  				  
				  if(strncmp("DumpTable",cmdparts[0],9)==0)
				  {
					  string fnam=cmdparts[1];
					  i2call->DumpRdacTable(fnam);
				  };
				  if(strncmp("checkall",cmdparts[0],8)==0)
				  {
					  int chkmode=0;
					  if(sscanf(cmdparts[1],"%d",&chkmode)==1)
					  {
						  i2call->checkall(chkmode);
					  };

				  };

				if(strncmp("chkchip",cmdparts[0],7)==0)
			  {
				  BYTE chip;
				  sscanf(cmdparts[1],"%X",&chip);
				  int result=i2call->ControlStat(chip);
				  TranError=i2call->CallError;
			  };
			  };
			  if(nscan>2)
			  {

			  if(strncmp("setctrl",cmdparts[0],7)==0)
			  {
				  int chp,chan;
				  sscanf(cmdparts[1],"%X",&chp);
				  sscanf(cmdparts[2],"%X",&chan);
				  int result=i2call->MasterMap(chp,chan);
				  if(i2call->PathState.ismapped && !(i2call->PathState.maperror))
				  {
					  printf("setctrl to dev=%d Chip: %X Chan: %X \n",i2call->PathState.dev,i2call->PathState.chip,i2call->PathState.chan);
				  }
				  else
				  {
					  printf("error setting chip / chan \n");
				      TranError=i2call->CallError;
				  };
			  };
			  };
			  if(strncmp("rctl",cmdparts[0],4)==0)
			  {
				int ctrlid=i2call->GetControlID();
				printf("Control Id=%d \n",ctrlid);
			  };
			   if(strncmp("wmem",cmdparts[0],4)==0)
			  {
				  BYTE ntowrite=1;
				  BYTE memstart=0;
				  char writechar[20];
				  if(nscan>3)
				  {
					  if(sscanf(cmdparts[1],"%X",&memstart)==1 &&
						  sscanf(cmdparts[2],"%X",&ntowrite)==1)
					  {
					    if(ntowrite>20)ntowrite=20;
						strncpy(writechar,cmdparts[3],20);	
						int wreturn=i2call->wmem(memstart,ntowrite,writechar);
						TranError=i2call->CallError;
					  };
				  };
			  };
			  if(strncmp("rmem",cmdparts[0],4)==0)
			  {
				  BYTE ntoread=1;
				  BYTE memstart=0;
				  if(nscan>2)
				  {
					  if(sscanf(cmdparts[1],"%X",&memstart)==1 &&
						  sscanf(cmdparts[2],"%X",&ntoread)==1)
					  {
						  int rreturn=i2call->rmem(memstart,ntoread);
						  TranError=i2call->CallError;
					  };
				  };
			  };
			  if(strncmp("radc",cmdparts[0],4)==0)
			  {

				  BYTE *radc_read;
				  radc_read=i2call->Radc;
				  BYTE addr16=0XE0;
				  BYTE newValue=0;
				  BYTE ADCmode=0;
				  bool goodaddr=false;
				  if(nscan>1)
				  {
					  goodaddr=true;
					  if(sscanf(cmdparts[1],"%X",&addr16)!=1)
					  {
						  goodaddr=false;
						  TranError=-100;
					  };
				  };
				   if(Voltage.BType==1)
				   {
					ADCmode=0X14;
				   } else 
				   {
					ADCmode=0X04;
				   };
				  TranError=i2call->radc(addr16,ADCmode);
				  char ReportErr[30];	
				  sprintf(ReportErr,"%s[%d,%d]:",(filenames[level]).c_str(),
						curr_cnt[level],ScriptRepeatCount[level]);
				  if(TranError!=0)	
				  {
					  sprintf(ReportErr,"%s[%d,Err]:",(filenames[level]).c_str(),curr_cnt[level]);	
				  };		
				  sprintf(LineReport," %s radc chan= %X : %X %X %X %X (-%6.1fV) %s\n",
							ReportErr,addr16,radc_read[0],radc_read[1],
							radc_read[2],radc_read[3],Voltage.ADC_HV((char*)radc_read),Voltage.BaseType);		
				  cout<<LineReport;		
				  (*logstrm)<<LineReport;
			  };
			  //
			  if(strncmp("rdac",cmdparts[0],4)==0)
			  {				  
				  BYTE addr16=0XE0;	  
				  BYTE newValue=0;
				  BYTE rdac_read;
				  BYTE eeprom_read;						  
				  bool r_write=false;
				  if(nscan>1)
				  {
					  if(sscanf(cmdparts[1],"%X",&addr16)==1)
					  {

						  if(nscan>2 && sscanf(cmdparts[2],"%X",&newValue)==1)r_write=true;
					  };
					  int wreturn=i2call->rdac(addr16,newValue,r_write);
				  };					
				  char ReportErr[30];
				  sprintf(ReportErr,"%s[%d,%d]:",(filenames[level]).c_str(),curr_cnt[level],
						ScriptRepeatCount[level]);
				  if(i2call->CallError!=0)
				  {	
					  printf(" Error=%d\n",i2call->CallError);
					  sprintf(ReportErr,"%s[%d,Err]:",(filenames[level]).c_str(),curr_cnt[level]);
				  };		
				  rdac_read=i2call->Rdac;
				  eeprom_read=i2call->Rdac_Eprom;
				  sprintf(LineReport," %s rdac chan= %X : volitile=%X (-%6.1fV) saved=%X (-%6.1fV) %s\n",
							ReportErr,addr16,rdac_read,Voltage.HV(rdac_read),eeprom_read,
							Voltage.HV(eeprom_read),Voltage.BaseType);		
				  cout<<LineReport;
				  (*logstrm)<<LineReport;
			  };

			  if(nscan==1)
			  {
				  if(strncmp("PSUbase",cmdparts[0],7)==0)
				  {
					Voltage=HVPsu;
					printf("Base Type PSU \n");
					(*logstrm)<<"Base Type PSU \n";
				  };
			  	  if(strncmp("YALEbase",cmdparts[0],8)==0)
				  {
					  Voltage=HVYale;
					  printf("Base Type YALE\n");
					  (*logstrm)<<"Base Type YALE \n";
				  };
			  };
			  if(nscan==2)
			  {
				  if(strncmp("ScriptRepeat",cmdparts[0],12)==0)
				  {
					  sscanf(cmdparts[1],"%d",&(ScriptRepeat[level+1]));
					  if(ScriptRepeat[level]>1000)ScriptRepeat[level+1]=1000;
					  cout<<"ScriptRepeat ["<<level+1<<"] set to "<<ScriptRepeat[level+1] <<"\n";
					  (*logstrm)<<"ScriptRepeat ["<<level+1<<"] set to "<<ScriptRepeat[level+1] <<"\n";
				  };

				  if(strncmp("Sleep",cmdparts[0],5)==0)
				  {
					  DWORD msec;
					  sscanf(cmdparts[1],"%d",&msec);
					  if(msec>0 && msec<<10000)Sleep(msec);
					  cout<<" "<<(filenames[level]).c_str()<<"["<<curr_cnt[level]<<","<<
						  ScriptRepeatCount[level]<<"]:";
					  (*logstrm)<<" "<<(filenames[level]).c_str()<<"["<<curr_cnt[level]<<","<<
						  ScriptRepeatCount[level]<<"]:";
					  cout<<" Sleep "<<msec<<" milliseconds \n";
					  (*logstrm)<<" Sleep "<<msec<<" milliseconds \n";
				  };
				  if(strncmp("SETdevice",cmdparts[0],8)==0)
				  {
					  int tempDevice;
					  sscanf(cmdparts[1],"%d",&tempDevice);
					  if(tempDevice>=0 && tempDevice<DeviceCount)
					  {
		
						  if(tempDevice>1)
						  {
							  printf("can not set device > 1\n");
						  }
						  else
						  {				  
							  DeviceInUse=tempDevice;
							  i2call->ChangeDev(DeviceInUse);
							  printf("Device number set to %d",i2call->DeviceN);
							  (*logstrm)<<"Device number set to "<<DeviceInUse<<" \n";
						  };
					  }
					  else
					  {
						  printf("Device %d not found\n",tempDevice);
					  };
				  };
			  };
			  if(nscan==2 && strncmp("HV",cmdparts[0],2)==0)
			  {
				  BYTE addr16=0;
			  if(sscanf(cmdparts[1],"%X",&addr16)!=1)TranError=1;
			  TransI2C.bySlvDevAddr=addr16;
			  TransI2C.wCount=2;
			  TransI2C.Data[0]=0X01;
			  TransI2C.Data[1]=0X04;
			  if(WriteI2c(hDevice[DeviceInUse],&TransI2C)!=TransI2C.wCount)
							  TranError=1;

			  if(strncmp("HVsave",cmdparts[0],6)==0)
				{
					TransI2C.bySlvDevAddr=0X30;
					TransI2C.wCount=1;
					TransI2C.Data[0]=0XC0;
					if(WriteI2c(hDevice[DeviceInUse],&TransI2C)!=TransI2C.wCount)
							  TranError=1;
				};
			  if(strncmp("HVrestore",cmdparts[0],6)==0)
				{
					TransI2C.bySlvDevAddr=0X30;
					TransI2C.wCount=1;
					TransI2C.Data[0]=0XA0;
					if(WriteI2c(hDevice[DeviceInUse],&TransI2C)!=TransI2C.wCount)
							  TranError=1;
				};
			  if(strncmp("HVGetTol",cmdparts[0],6)==0)
				{
					TransI2C.bySlvDevAddr=0X30;
					TransI2C.wCount=1;
					TransI2C.Data[0]=0X3E;
					if(WriteI2c(hDevice[DeviceInUse],&TransI2C)!=TransI2C.wCount)
							  TranError=1;
					TransI2C.bySlvDevAddr=0X31;
					TransI2C.wCount=2;
					if(ReadI2c(hDevice[DeviceInUse],&TransI2C)!=TransI2C.wCount)
							  TranError=1;
					BYTE dev1=TransI2C.Data[0];
					BYTE dev2=TransI2C.Data[1];
					printf("Tol: %X %X \n",dev1,dev2);
					WORD devsign=dev1&0X80;
					dev1=0X7F&dev1;
					float devRes=(float) ((dev1+dev2/256.)/100.);
					if(devsign!=0)devRes=-devRes;
					devRes=devRes+1;
					Voltage.correction=devRes;
					printf("devRes=%f  \n",devRes);
				};

				TransI2C.bySlvDevAddr=addr16;
				TransI2C.wCount=2;
				TransI2C.Data[0]=0X01;
				TransI2C.Data[1]=0X00;
				if(WriteI2c(hDevice[DeviceInUse],&TransI2C)!=TransI2C.wCount)
							  TranError=1;
				char ReportErr[30];
				sprintf(ReportErr,"%s[%d,%d]:",(filenames[level]).c_str(),
					curr_cnt[level],ScriptRepeatCount[level]);
				if(TranError==1)
					{
						sprintf(ReportErr,"%s[%d,Err]:",(filenames[level]).c_str(),curr_cnt[level]);
					};
						sprintf(LineReport," %s HV Update chan= %X  \n",
							ReportErr,addr16);
						cout<<LineReport;
						(*logstrm)<<LineReport;

			  };
		  };
	if(nscan<4)Writ=2;
	  }
	  else
	  {
	  int fcount=sscanf(line,"%d %X %d %d",&Writ,
		  &(TransI2C.bySlvDevAddr),&(TransI2C.wCount),&(loopcnt));
	  if(fcount<4)Writ=2;
	  };
	
	  if(Writ==1)
	  {
		  
		for(int k=0;k<TransI2C.wCount;k++)
		{
			if(read_cin)printf("Enter %d data () ()... : ",TransI2C.wCount-k);
			int val[20];
			thesrc->getline(line,99);
		if(ncmdarg[level]>0)
			{
				string tmpline=line;
				string newline=sfilter->ArgReplace(tmpline);
				strcpy(line,newline.c_str());
			};
			int num=sscanf(line,"%2x %2x  %2x %2x %2x %2x %2x %2x %2x %2x",
				&val[0],&val[1],&val[2],&val[3],&val[4],&val[5],&val[6],
				&val[7],&val[8],&val[9]);
			for(int jj=0;jj<num;jj++)
				{
					TransI2C.Data[k]=val[jj];
					if(jj<num-1){k++;};
				};
		

		};
	  };
	  for(int l=0;l<loopcnt+1;l++)
	  {
      if(Writ==0)
	  {
		  lReadCnt = ReadI2c(hDevice[DeviceInUse], &TransI2C);
	  }
	  else if(Writ==1)
	  {
          lReadCnt = WriteI2c(hDevice[DeviceInUse], &TransI2C);
	  };
if(Writ<2)
  {
	  string io_ok;
	  io_ok=";";
	  if(TransI2C.wCount==lReadCnt)io_ok="*";
	  printf("%s[%d,%d]: Type=%X,Addr=%X,N attempt=%d, N r/w=%d%s",(filenames[level]).c_str(),
	  curr_cnt[level],l,Writ,TransI2C.bySlvDevAddr,
	  TransI2C.wCount,lReadCnt,io_ok.c_str());
	  char logline[200];
	  sprintf(logline,"%s[%d,%d]: Type=%X,Addr=%X,N attempt=%d, N r/w=%d%s",(filenames[level]).c_str(),
	  curr_cnt[level],l,Writ,TransI2C.bySlvDevAddr,
	  TransI2C.wCount,lReadCnt,io_ok.c_str());
	  if(l<loglimit)(*logstrm)<<logline<<"  ";
	  if(l==loglimit)(*logstrm)<<"log limit\n";
	  int even=0;
	  printf("data:");
	  for(int n=0;n<TransI2C.wCount;n++)
      {
	  printf(" %X",TransI2C.Data[n]);
	  if(l<loglimit)
	  {
	    sprintf(logline,",%X ",TransI2C.Data[n]);
	    (*logstrm)<<logline;
	  };
	   even++;
	    if(even>2){even=0;printf("\n");};
	  };
	  if(l<loglimit)(*logstrm)<<"\n";
	  cout<<"\n";
  };
	  };
};
exit(0);
}

