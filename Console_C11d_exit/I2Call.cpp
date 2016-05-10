#include "StdAfx.h"
#include "I2call.h"
using namespace std;
#include <strstream>
int I2Call::Loadrdac()
{
	for(BYTE dev=0;dev<DeviceCount;dev++)
	{
	    ChangeDev(dev);
		for(BYTE chp=0;chp<4;chp++)
		{
			for(BYTE chan=0;chan<4;chan++)
			{
				mappath(dev,chp,chan);
				if(pathgood())
				{
				BYTE indx=chp*4+chan;
				for(BYTE j=0;j<16;j++)
				{
					BYTE addr=2*j+0XE0;
					if(TableValid[dev][indx][j])
					{
						BYTE value=SetRdacTable[dev][indx][j];
						printf("write dev=%X Chip=%X Chan=%X addr=%X value=%X \n",
							dev,chp,chan,addr,value);
						Sleep(50.);
						printf("error=%d \n",rdac(addr,value,true));
					};
				};
				};
			};
			unmappath(); // Turn off chip
		};
	};
	return 0;
};
int I2Call::DumpRdacTable(string parfile)
{

	ostream* strm;
	string fullfile=Directory_str+parfile;
	parbuf.open(fullfile.c_str(),ios::out);
	if(parbuf.is_open())
	{	
		strm=new ostream(&parbuf);
	}
	else
	{
		return -1;
	};	 
	for(int deV=0;deV<DeviceCount;deV++)
	{
	for(int ichp=0;ichp<4;ichp++)
	{
		for(int ichn=0;ichn<4;ichn++)
		{
			for(int iadc=0;iadc<16;iadc++)
			{
				if(TableValid[DeviceN][ichn+4*ichp][iadc])
				{
				BYTE nadc=iadc*2+0XE0;
				char tcha[10];
				sprintf(tcha,"%2X",nadc);
				tcha[2]=0;
				strm->unsetf(ios_base::dec);
				strm->setf(ios_base::hex);
				int vall=SetRdacTable[deV][ichn+4*ichp][iadc];
				int setv=SetNegHV[deV][ichn+4*ichp][iadc];
				int readv=ReadNegHV[deV][ichn+4*ichp][iadc];
				*strm<<"deV= "<<deV<<" chip= "<<ichp;
				*strm<<" chan= "<<ichn<<" ndac= ";
				*strm<<tcha<<" value= "<<vall;
				strm->unsetf(ios_base::hex);
				strm->setf(ios_base::dec);
				*strm<<" SetHV= "<<setv<<" ReadHV= "<<readv<<"\n";
				};
			};
		};
	};
	};
	delete strm;	
	parbuf.close();
	return 0;
};
int I2Call::GetRdacTable(string parfile)
{
	istream* strm;
	char line[100];
	string skey[5];
	BYTE bkey[5];
	skey[0]="dev= ";
	skey[1]="hip= ";
	skey[2]="han= ";
	skey[3]="dac= ";
	skey[4]="lue= ";
	string::size_type pos;
	string fullfile=Directory_str+parfile;
	parbuf.open(fullfile.c_str(),ios::in);
	if(parbuf.is_open())
	{	
		strm=new istream(&parbuf);

	}
	else
	{
		return -1;
	};	   
	strm->getline(line,99);

	while(!(strm->eof()))
	{
		printf(line);
		printf("\n");
		BYTE Dev=0;
		BYTE Chip=0;
		BYTE Chan=0;
		BYTE indx=0;
		BYTE ndac=0;
		BYTE Value=0;

		if(strlen(line)>11)
		{
			string strline=line;
			bool rerr=true;
			for(int l=0;l<5;l++)
			{
				bkey[l]=0;
				pos=strline.find(skey[l],0);
				pos=pos+5;
				string n=strline.substr(pos,2);
				n="0x"+n+"    \n";
				char* cstp;
				int iv=strtol(n.c_str(),&cstp,0);
				bkey[l]=iv&0XFF;
			};
			if(rerr)
			{
				Dev=bkey[0];
				Chip=bkey[1];
				Chan=bkey[2];
				ndac=bkey[3];
				Value=bkey[4];
 				indx=4*Chip+Chan;
				ndac=(ndac-0XE0)/2;
				SetRdacTable[Dev][indx][ndac]=Value;
				TableValid[Dev][indx][ndac]=true;
			};
		};
		strm->getline(line,99);
	};

	if(strm!=0)delete strm;	
	parbuf.close();
	int retval=0;
	return retval;
};
int I2Call::gethelp(int i0)
{
	string helpstr[40];
	helpstr[5]="raw i2c read/write         :  [0/1 for read/write] [i2c HEX addr] [N words] [nloop] \n";
	helpstr[6]=".... for write on N words  :  [data1] [data2] [data3]...[dataN]\n";
	helpstr[7]="\n";
	helpstr[8]="\n";
	helpstr[9]="Set or Read set base HV    :  !rdac [addr16 E0-FE] [optional value]\n";
	helpstr[10]="Read HV from addr          :  !radc [addr16 E0-FE]\n";
	helpstr[11]="Interpret as YALE base     :  !YALEbase \n";
	helpstr[12]="Interpret as PSU base      :  !PSUbase \n";
	helpstr[13]="Save [addr16] HV powerup   :  !HVsave [addr16] \n";
	helpstr[13]="Reset [addr16] to powerup  :  !HVrestore [addr16] \n";
	helpstr[15]="\nEach base is reached by setting dev[0-1]_chip[0-3]_chan[0-3]_base[0-15]\n\n";
	helpstr[16]="Set device to 0 or 1       :  !SETdevice [dev] \n";
	helpstr[17]="0n  [Chip] 0 to 3          :  ! \n";
	helpstr[18]="    Set [Chan] 0 to 3      :  !setctrl [chip] [chan] \n";
	helpstr[19]="    Set to [Chan]>3 to \n    deselect chip (only one \n    chip at a time)\n";
	helpstr[20]="read controller mem        :  !rmem [startaddr] [nbytes]\n";
	helpstr[21]="write controller mem       :  !wmem [startaddr] [nbytes] [string]\n";
	helpstr[22]="read controller id         :  !rctl \n";
	helpstr[23]="report crl chip registers  :  !chkchip [chip]\n";
	helpstr[24]="set or read power chip/chan:  !power [mask bit0:10V/bit1:30V/bit2:-6V] \n";
	helpstr[25]="run script called [name]   :  @name [param0] [param1]..\n";
	helpstr[26]="run next script [n] times  :  !ScriptRepeat [n] \n";
	helpstr[27]="sleep [m] msec             :  !Sleep [m]\n";
	helpstr[28]="check supply Voltage bits  :  !checkall 1\n";
	helpstr[29]="check for ctrl board ids   :  !checkall 2\n";
	helpstr[30]="i2c read set rdac array    :  !checkall 3\n";
	helpstr[31]="i2c read startup rdac array:  !checkall 4\n";
	helpstr[32]="read rdac array from file  :  !ReadTable [file]\n";
	helpstr[33]="dump rdac array to file    :  !DumpTable [file]\n";
	helpstr[34]="i2c write rdac set array   :  !Loadrdac \n";
	helpstr[35]="i2c read radc HV array     :  !checkall 5\n";
	helpstr[36]="i2c read rdac HV setpoints :  !checkall 6\n";
	helpstr[37]="exit program               :  !exit \n";

	for(int j=5;j<38;j++)printf(helpstr[j].c_str());
	return 0;
};
I2Call::I2Call(	HINSTANCE* phd,HANDLE* ph,I2C_TRANS* itr)
{
	PathState.dev=2;
	PathState.chip=4;
	PathState.chan=4;
	PathState.ismapped=false;
	PathState.check_overide=false;
	PathState.maperror=false;
	CallError=0;
	phDLL=phd;
	phdev=ph;
	DeviceN=0;
	DeviceCount=1;
	ptrans=itr;
	ctraddr[0]=0x80;
	ctraddr[1]=0x82;
	ctraddr[2]=0x84;
	ctraddr[3]=0x86;
	for(int j=0;j<4;j++){ChipStatus[j].read=false;};
	reg3=3;
	BusSelect[0]=0X80;
	BusSelect[1]=0X40;	
	BusSelect[2]=0X20;	
	BusSelect[3]=0X10;
	ReadI2c=(READI2C)GetProcAddress(*phDLL,"DAPI_ReadI2c");
    WriteI2c=(WRITEI2C)GetProcAddress(*phDLL,"DAPI_WriteI2c");
	about_reg0="\n0-Timeout Real Time ->1\n1-Timeout Latched  ->1\n2-Fail Connect Attempt ->0\n3-Alert 4\n4-Alert 3\n5-Alert 2\n6-Alert 1\n7-Downstream Connect ->1\n";
	about_reg1="0-gpio2 logic\n1-gpio1 logic\n4-gpio2 out\n5-gpio1 out\n6-DownStream Accel ->1\n7-UpStream Accel ->1\n";
	about_reg2="0-TimeOut mode bit 0\n1-TimeOut mode bit 1\n2-Mass Write ENABLE\n3-GPIO2 output MODE Config\n4-GPIO1 output MODE Config\n5-Connection Requirement (Connect only if downstream high)->0\n6-GPIO2 Mode Config\n7-GPIO1 Mode Config\n";
	about_reg3="0-BUS 4 LOGIC STATE (NOT HUNG)->1\n1-BUS 3 LOGIC STATE\n2-BUS 2 LOGIC STATE\n3-BUS 1 LOGIC STATE\n4-BUS 4 FET SWITCH  OPEN ->0\n5-BUS 3 FET SWITCH \n6-BUS 2 FET SWITCH\n7-BUS 1 FET SWITCH\n";
	about_regs[0]=about_reg0;
	about_regs[1]=about_reg1;
	about_regs[2]=about_reg2;
	about_regs[3]=about_reg3;
	int preset=0;
	for(int j=0;j<16;j++)
	{
		for(int k=0;k<16;k++)
		{
			for(int kdev=0;kdev<2;kdev++)
			{
				LastMasterController[kdev][j]=0;
				SetRdacTable[kdev][j][k]=preset&0XFF;
				TableValid[kdev][j][k]=false;
				for(int kloc=0;kloc<4;kloc++)
					LastRadcTable[kdev][j][k][kloc]=0;	
				SetNegHV[kdev][j][k]=9999;
				ReadNegHV[kdev][j][k]=9999;
			}
		};
	};
}

I2Call::~I2Call(void)
{
}
void I2Call::ChangeDev(int dev)
{	
	if(dev>=0 && dev<DeviceCount)
	{
		DeviceN=dev;
		CallError=0;
	}
	else
	{
		printf("Error: illegal device number\n");
	};
	
};
int I2Call::GetControlID()
{
	if(!pathgood()){printf("bad path\n");return  -1;};
	if(PathState.dev!=DeviceN){printf("path device not set to current device\n");return -2;};
	CallError=0;
	char ControlStr[4];
	int val;
	ptrans->Data[0]=0x10;
	ptrans->wCount=1;
	ptrans->bySlvDevAddr=0XA0;
	int cnt;
	cnt=WriteI2c(phdev[DeviceN],ptrans);
	CallError=cnt-1;
	if(CallError<0)return CallError;
	ptrans->wCount=4;
	cnt=ReadI2c(phdev[DeviceN],ptrans);
	CallError=cnt-4;
	for(int i=0;i<4;i++){ControlStr[i]=ptrans->Data[i];};
	sscanf(ControlStr,"%d",&val);
	if(CallError<0)return CallError;
	return val;
};
int I2Call::MasterMap(int chip,int channel)
{
	CallError=0;
	mappath(DeviceN,chip,channel);
	return CallError;
};
int I2Call::ControlStat(BYTE chip)	
{
	int oldDeviceN;
	unmappath();
	DeviceN=oldDeviceN;
	CallError=0;
	int ErrorCount=0;
	for(int j=0;j<4;j++)
	{
		printf("\n");
		printf(about_regs[j]); 
		printf("Reg %d =",j);
		ptrans->wCount=1;
		ptrans->bySlvDevAddr=ctraddr[chip];
		ptrans->Data[0]=j;
		int cnt=WriteI2c(phdev[DeviceN],ptrans);
		CallError=cnt-1;
		if(CallError<0)ErrorCount--;
		ptrans->wCount=1;
		cnt=ReadI2c(phdev[DeviceN],ptrans);
		CallError=cnt-1;
		if(CallError<0)ErrorCount--;
		ChipStatus[chip].reg[j]=ptrans->Data[0];
		printf("hex(%2X) \n",ChipStatus[chip].reg[j]); 
	};
	
	if(ErrorCount==0)
	{
		ChipStatus[chip].read=true;
	}
	else 
	{
		ChipStatus[chip].read=false;
		printf("Fail\n");
	};
	mappath(DeviceN,chip,3);
	unmappath();
	return ErrorCount;
};
int I2Call::rmem(BYTE mstart,BYTE ntoread)
{
	if(!pathgood()){printf("bad i2c path\n");return  -1;};
	ptrans->bySlvDevAddr=0XA0;
	ptrans->wCount=1;
	ptrans->Data[0]=mstart;
	if(WriteI2c(phdev[DeviceN],ptrans)==ptrans->wCount)
	{
		ptrans->bySlvDevAddr=0xA1;
		ptrans->wCount=ntoread;
		int didread;
		Sleep(50);
		printf("Try to read...\n");
		didread=ReadI2c(phdev[DeviceN],ptrans);
		Sleep(100);
		if(didread>0)
		{
			printf("Read %d mem (read %d)\n",ntoread,didread);
			int cnt=0;
			while(cnt<didread)
			{
				int endcnt=cnt+7;
				if(endcnt>didread)endcnt=didread;
				printf("%X - %X :",cnt,endcnt);
				while(cnt<endcnt+1)
				{
					printf("%X ",ptrans->Data[cnt]);
					LastMemRead[cnt]=ptrans->Data[cnt];
					cnt++;
				};
				printf("\n");
			};
			printf("\n %s \n",LastMemRead);
		}
		else
		{
			printf("rmem failed\n");
		};
		return didread;
	}
	else
	{
		printf("Address set failed\n");
	};
	return -1;
};
int I2Call::wmem(BYTE mstart,BYTE ntowrite,char* writechar)
{
	if(!pathgood()){printf("bad i2c path\n");return  -1;};
	ptrans->bySlvDevAddr=0xA0;						
	ptrans->wCount=1;					
	ptrans->Data[0]=mstart;
	if(WriteI2c(phdev[DeviceN],ptrans)==ptrans->wCount)
	{
		printf("step 1\n");
		int didwrite;
		Sleep(50);
		ptrans->wCount=ntowrite+1;
		ptrans->Data[0]=mstart;
		for(int jcn=1;jcn<ntowrite+1;jcn++)ptrans->Data[jcn]=writechar[jcn-1];
		didwrite=WriteI2c(phdev[DeviceN],ptrans);
		Sleep(500);
		didwrite=didwrite-1;
		printf("step 2\n");
		if(didwrite>0)
		{
			printf("Write %d mem (written %d)\n",ntowrite,didwrite);
			int cnt=0;
			while(cnt<didwrite)
			{
				int endcnt=cnt+8;
				if(endcnt>didwrite)endcnt=didwrite;
				printf("%X - %X :",cnt,endcnt);
				while(cnt<endcnt+1)
				{
					printf("%X ",ptrans->Data[cnt+1]);
					NextMemWrit[cnt]=ptrans->Data[cnt+1];
					cnt++;
					NextMemWrit[cnt]=0;
				};	
				printf("\n");
			};		
			printf("\n String: %s \n",NextMemWrit);
		};
		return didwrite;
	};
	return -1;
};
int I2Call::Multiplex(BYTE Addr,bool State)
{
	if(!pathgood()){printf("no established path to chip\n");return  -1;};
	CallError=0;
	ptrans->wCount=2;
	ptrans->bySlvDevAddr=Addr;
	ptrans->Data[0]=1;
	char un[3];

	if(State)
	{
		strcpy(un,"  ");
		ptrans->Data[1]=04;
		CallError=WriteI2c(phdev[DeviceN],ptrans)-2;

	}
	else
	{	
		strcpy(un,"un");
		ptrans->Data[1]=00;
		CallError=WriteI2c(phdev[DeviceN],ptrans)-2;
	};
//	printf("... %smapped to %X with err=%d \n",un,Addr,CallError);
	return CallError;
};
int I2Call::rdac(BYTE addr,BYTE value,bool rdac_write)
{
	if(!pathgood()){printf("no established path to chip\n");return  -1;};
	CallError=0;
	Rdac=0;
	Rdac_Eprom=0;
	BYTE maskaddr=addr | 0XE0;
	if(addr != maskaddr)return CallError=-1;
	if(Multiplex(addr,true)!=0)return CallError=-2+Multiplex(addr,false);
	ptrans->bySlvDevAddr=0X30;
	if(rdac_write)
	{
		ptrans->Data[0]=0;
		ptrans->Data[1]=value;
		ptrans->wCount=2;
		CallError=(WriteI2c(phdev[DeviceN],ptrans)-2);
		if(CallError!=0)return CallError+Multiplex(addr,false);
		Rdac=value;
	};
	ptrans->wCount=1;
	ptrans->Data[0]=0X00;
	if(CallError=(WriteI2c(phdev[DeviceN],ptrans)-1)!=0)return CallError+Multiplex(addr,false);
	if(CallError=(ReadI2c(phdev[DeviceN],ptrans)-1)!=0)return CallError+Multiplex(addr,false);
	Rdac=ptrans->Data[0];
	ptrans->Data[0]=0X20;
	if(CallError=(WriteI2c(phdev[DeviceN],ptrans)-1)!=0)return CallError+Multiplex(addr,false);
	if(CallError=(ReadI2c(phdev[DeviceN],ptrans)-1)!=0)return CallError+Multiplex(addr,false);
	Rdac_Eprom=ptrans->Data[0];

	if(Multiplex(addr,false)!=0)return CallError;
	return CallError;
};

int I2Call::radc(BYTE addr, BYTE mode)
{
	CallError=0;
	for(int j=0;j<4;j++)Radc[j]=0;
	if(Multiplex(addr,true)!=0)return CallError;
	ptrans->bySlvDevAddr=0X90;
	ptrans->wCount=1;
	ptrans->Data[0]=mode;
	if(CallError=(WriteI2c(phdev[DeviceN],ptrans)-1)!=0)
		return CallError+Multiplex(addr,false);
	ptrans->wCount=1;
	if(CallError=(ReadI2c(phdev[DeviceN],ptrans)-1)!=0)
		return CallError+Multiplex(addr,false);
	ptrans->wCount=4;
	if(CallError=(ReadI2c(phdev[DeviceN],ptrans)-4)!=0)
		return CallError+Multiplex(addr,false);
	for(int j=0;j<4;j++)Radc[j]=ptrans->Data[j];
	if(Multiplex(addr,false)!=0)return CallError;
	return CallError;
};
int I2Call::powerchan(BYTE value,bool Write)
{
	CallError=-1;
	ptrans->bySlvDevAddr=0X9E;
	ptrans->wCount=1;
	power=0XF0;
	if(Write && ((value&0X07)==value))
	{
		ptrans->Data[0]=value;
		CallError=WriteI2c(phdev[DeviceN],ptrans)-1;
	}
	else
	{
		CallError=ReadI2c(phdev[DeviceN],ptrans)-1;
	};
	if(CallError==0)
	{
		power=ptrans->Data[0];
	};
	return CallError;
};
int I2Call::checkall(int mode)
{
	unmappath();
	if(mode>0)
	{
		if(mode==3)printf("Active RDAC Table\n\n");
		if(mode==4)printf("Stored RDAC Table \n");
		if(mode==5)printf("Read ADC Negative Voltages\n\n");
		if(mode==6)printf("Set Point Negative Voltages\n\n");
		if((mode>2) && (mode<7))printf(" blank for base not found  \n");
		if(mode==1)printf(" Power        \n return A0 if chip not found\n return B0 if channel power switch not found \n");
		if(mode==2)
		{
			printf(" control#     \n 10** for PSU base controller\n 20** for YALE base controller \n 3000 for chip/chan path failure \n 4000 for no controller found \n\n ");
		};
		printf("Controller Num:\n     0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15\n");
		printf("chip/channel  :\n    0/0  0/1  0/2  0/3  1/0  1/1  1/2  1/3  2/0  2/1  2/2  2/3  3/0  0/1  0/2  0/3\n\n");

		BYTE p16[16];
		int cntrN[16];
		string rdacstr[16][16];

		for(BYTE chp=0;chp<4;chp++)
		{
			for(BYTE chn=0;chn<4;chn++)
			{
				int cntrl=4*chp+chn;
				if(mode==3 || mode==4 ||mode==5)
				{
					for(int l=0;l<16;l++)TableValid[DeviceN][cntrl][l]=false;
				};
				char tmch[5];
				strcpy(tmch,"|  |");
				if(mode>4)strcpy(tmch,"    ");
				for(int j=0;j<16;j++)rdacstr[cntrl][j]=tmch;
				p16[cntrl]=0XA0;
				cntrN[cntrl]=3000;
				MasterMap(chp,chn);
				if(CallError==0)
				{
					p16[cntrl]=0XB0;
					cntrN[cntrl]=4000;
					if(powerchan(0,false)==0)
					{
						p16[cntrl]=power&0X07;
							
							if((cntrN[cntrl]=GetControlID())>0)
							{
								LastMasterController[DeviceN][cntrl]=cntrN[cntrl];
							}
							else 
							{
								cntrN[cntrl]=0;
							};
						

						if(mode>2 && mode<7)
						{
							for(BYTE j=0;j<16;j++)
							{			
								SetNegHV[DeviceN][cntrl][j]=7777;			
								ReadNegHV[DeviceN][cntrl][j]=7777;
								BYTE tadr;
								Rdac=0;
								int tmpjrdac=rdac(tadr=2*j+0XE0,0,false);
								if(tmpjrdac==0)
								{
									SetRdacTable[DeviceN][cntrl][j]=Rdac;
									SetRdacEpromTable[DeviceN][cntrl][j]=Rdac_Eprom;
									TableValid[DeviceN][cntrl][j]=true;
									char tmpchar[6];
									if(mode==3)sprintf(tmpchar,"|%2X|",Rdac);
									if(mode==4)sprintf(tmpchar,"|%2X|",Rdac_Eprom);
									if(mode==5 || mode==6)
									{
										BYTE PSU_YALE_mode=cntrN[cntrl]/1000;											
										//printf("psu_yale_mode %X %d \n",PSU_YALE_mode,cntrN[cntrl]/1000);
										if(PSU_YALE_mode==1 ||PSU_YALE_mode==2)
										{
											int newHV=0;
											int setHV=0;
											HV=HVPSU;	
										//	printf("PSU_YALE_mode= %d\n",PSU_YALE_mode);

											HV=HVPSU;
											if(PSU_YALE_mode==2)HV=HVYALE;
										//	printf("HV set to %s\n",HV->BaseType);
											if(radc(tadr,HV->ModeUsed)>=0)
											{
												for(int k4=0;k4<4;k4++)
												{
													LastRadcTable[DeviceN][cntrl][j][k4]=Radc[k4];
												};
												newHV=HV->ADC_HV((char*) Radc);
										//		printf("1. newHV %d \n",newHV); 
												newHV=abs(newHV);
												setHV=HV->HV((int) Rdac&0XFF);
											//	printf("setHV=%d \n",setHV);
												setHV=abs(setHV);
										//		printf("2. setHV= %d \n",setHV);
										//		printf(" %d %X %d %d\n",cntrl,j,cntrN[cntrl],newHV);
										//		printf("radc[0-3] %X %X %X %X rdac=%X\n",Radc[0],Radc[1],Radc[2],Radc[3],Rdac);

											};
											if(mode==5)sprintf(tmpchar,"%4d",newHV);
											if(mode==6)sprintf(tmpchar,"%4d",setHV);
											SetNegHV[DeviceN][cntrl][j]=setHV;
											ReadNegHV[DeviceN][cntrl][j]=newHV;
										};
									};
									rdacstr[cntrl][j]=tmpchar;
								};
							}
						};
					};
				};	
				LastMasterController[DeviceN][cntrl]=cntrN[cntrl];
				unmappath();
				if(mode==1)printf("  %2X ",p16[cntrl]);
				if(mode==2)printf(" %4d",cntrN[cntrl]);
			};
		};	
		printf("\n");
		if(mode==3 || mode==4 || mode==5 ||mode==6)
		{
			for(int j=0;j<16;j++)
			{
				printf("\n%2X: ",0XE0+2*j);
				for(int k=0;k<16;k++)
				{
					printf("%4s ",rdacstr[k][j].c_str());
				};
			};
			printf("\n");
		};
	};
	return 0;
};

bool I2Call::pathgood()
{
	if(PathState.check_overide)return true;
	if((pathmapped() && !PathState.maperror))
	{
		if(DeviceN==PathState.dev)
		{
			return true;
		}
		else
		{
			printf("Device not set to mapped Device\n");
		};
	};
	return false;
}
bool I2Call::pathmapped()
{
	if(PathState.check_overide)return true;
	return PathState.ismapped;		
};

int I2Call::mappath(int dv, int chip, int channel)
{
	CallError=0;

	if(	pathmapped())
	{
		if(PathState.dev!=dv || PathState.chip!=chip)
		{
			unmappath();
		};	
		
	};
	if(CallError!=0)CallError=-64+CallError;//problem unmapping path

	if(dv<DeviceCount && dv>=0)
	{
		DeviceN=dv;
	}
	else
	{
		printf("dev =%d mapping non-existing dev\n",dv);
		return -26;
	};
	DeviceN=dv;

	if(CallError!=0)
	{
		PathState.maperror=true;
		if(!PathState.check_overide)return CallError;
	};

	if(chip>-1 && chip<4)
	{
		ptrans->wCount=2;
		ptrans->bySlvDevAddr=ctraddr[chip];
		ptrans->Data[0]=reg3;
		ptrans->Data[1]=0;
		if(channel<4 && channel >-1)ptrans->Data[1]=BusSelect[channel];
		int cnt;
		cnt=WriteI2c(phdev[DeviceN],ptrans);
		CallError=cnt-2;
		if(CallError!=0)
		{
		
			PathState.maperror=true;
			return CallError;
		};
		Chip=chip;
		Channel=channel;
		PathState.dev=DeviceN;
		PathState.chip=Chip;
		PathState.chan=Channel;
		PathState.maperror=false;
		PathState.ismapped=true;
		return 0;
	};	
	CallError=-11;//fail to map non-existing chip
	PathState.maperror=false;
	return CallError;
};
int I2Call::unmappath()
{
	//return errors -25 : bad device
	//              -11 : fail to write change
int OldDev=DeviceN;
if(!PathState.ismapped)return 0;
int dv=PathState.dev;
int chip=PathState.chip;
int channel=PathState.chan;
if(dv<DeviceCount && dv>=0)
{
	DeviceN=dv;
}
else
{
	printf("dev =%d umapping non-existing dev\n",dv);
	return -25;
};
if(chip>-1 && chip<4)
{
	ptrans->wCount=2;
	ptrans->bySlvDevAddr=ctraddr[chip];
	ptrans->Data[0]=reg3;
	ptrans->Data[1]=0;// Clear all channels
	int cnt;
	cnt=WriteI2c(phdev[DeviceN],ptrans);
	CallError=cnt-2;
	if(CallError!=0)
	{
		PathState.maperror=true;
		DeviceN=OldDev;
		return CallError;
	};
	Chip=chip;
	Channel=channel;
	PathState.ismapped=false;
	PathState.maperror=false;
	return 0;
	};	
	CallError=-11;
	return CallError;
};

