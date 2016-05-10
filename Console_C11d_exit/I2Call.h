#pragma once
#include <iostream>
#include <istream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "usbi2cio.h"
#include "HVSet.h"

typedef BOOL(CALLBACK* READI2C)(HANDLE,PI2C_TRANS);
typedef BOOL(CALLBACK* WRITEI2C)(HANDLE,PI2C_TRANS);
typedef struct _ChipStats {             // structure for device information
  BYTE reg[4];
  bool read;
} ChipStats;
typedef struct _pathstate {
	bool check_overide; // if true, no checking of pathstate
	bool ismapped; // true after mapping path established
	bool maperror;
	int dev;
	int chip;
	int chan;
} pathstate;
class I2Call
{
public:
	HVSet *HVPSU;
	HVSet *HVYALE;
	HVSet *HV;
	filebuf parbuf;
	BYTE SetRdacTable[2][16][16];// [device] [chp/chn] [addrindex]
	BYTE SetRdacEpromTable[2][16][16];// [device] [chp/chn] [addrindex]
	BYTE LastRadcTable[2][16][16][4];// [device] [chp/chn] [addrindex]
	int SetNegHV[2][16][16];
	int ReadNegHV[2][16][16];
	int LastMasterController[2][16];
	bool TableValid[2][16][16];
	pathstate PathState;
	string Directory_str;
	int GetRdacTable(string);
	int DumpRdacTable(string);
	int Loadrdac();
	HINSTANCE* phDLL;
	HANDLE* phdev;
	int DeviceCount;
	ChipStats ChipStatus[4];
	BYTE ctraddr[4];
	BYTE reg3;
	BYTE BusSelect[4];
	BYTE Rdac;
	BYTE Rdac_Eprom;
	BYTE Radc[4];
	int gethelp(int);
	READI2C ReadI2c;
    WRITEI2C WriteI2c;
	I2C_TRANS* ptrans;
	int CallError;
	int Chip;
	int Channel;
	int DeviceN;
	BYTE power;
//	string directory;
	I2Call(	HINSTANCE*,HANDLE*,I2C_TRANS*);
	~I2Call(void);
	void ChangeDev(int);
	int GetControlID();
	int MasterMap(int ,int);
	int wmem(BYTE,BYTE,char*);	
	int rmem(BYTE,BYTE);
	int Multiplex(BYTE,bool);
	int rdac(BYTE ,BYTE ,bool );
	int radc(BYTE , BYTE);
	char LastMemRead[256];
	char NextMemWrit[256];
	int ControlStat(BYTE); 
	char* about_reg0;
	char* about_reg1;
	char* about_reg2;
	char* about_reg3;
	char* about_regs[4]; 
	int powerchan(BYTE,bool);
	int checkall(int);
	int SetDeviceCount(int Dcount){if(Dcount>=0 && Dcount<=2){DeviceCount=Dcount;};return DeviceCount;}
	bool pathmapped(); //true if a dev-chip-chan map is in connected state
	int unmappath();// call to disconnect current dev-chip-chan path
	int mappath(int dev, int chip, int chan);
	bool pathgood();
	};	
