#include "StdAfx.h"
#include "strfilter.h"

strfilter::strfilter(int n,string* ps)
{
	pstr=ps;
	nargs=n;
		
	keys[0]="$0";
	keys[1]="$1";
	keys[2]="$2";
	keys[3]="$3";
	keys[4]="$4";

}
string strfilter::ArgReplace(string in)
{
	string::size_type pos;
	string out;
	string* pout=&out;
	out=in;
	for(int j=0;j<nargs;j++)
	{
		while((pos=pout->find(keys[j],0))!=string::npos)
		{
			string repl=pstr[j];
			pout->replace(pos,2,repl);
		};
	};
	return out;
};
void strfilter::print()
{
	cout<<pstr[0]<<" "<<pstr[1]<<" "<<pstr[2]<<" "<<pstr[3]<<" "<<pstr[4]<<"\n ";
};
strfilter::~strfilter(void)
{
}
