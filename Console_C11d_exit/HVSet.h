#pragma once

class HVSet
{
public:
	float r1;
	float r2;
	float rdac;
	float vref;
	float vscale;
	float diodes;
	float correction;
	int BType;
	char BaseType[10];
	HVSet(void);
	float HV(int);
	void SetBaseType(char*);
	~HVSet(void);
	float ADC_HV(char*);
	char ModeUsed;
};
