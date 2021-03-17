
#include "../../ini.h"
#include <fstream>
#include <iostream>

extern CLoaderINI *pLoaderINI;
 
using namespace std;

void CopyFile(const char *Export)
{
	char buff[0x7F];
		char * buffer;
    	int len = 4096;
	
		sprintf(buff, "%splugins/%s.pm", GameStorage, Export);
    	ifstream infile(buff, ios::in | ios::binary);
		sprintf(buff, "%scache/lib%s.so", RootStorage, Export);
    	ofstream outfile(buff, ios::out | ios::binary);
    	if(!infile || !outfile)
		{ 
        	Log("No such plugin '%s' in folder plugins", Export);
        	exit(1);
    	}
 
   		buffer = new char[len];
    	while (!infile.eof())
		{
        	infile.read(buffer, len);
        	if(infile.gcount()) outfile.write(buffer, infile.gcount());
		}

    infile.close();
    outfile.close(); 
    delete[] buffer;
}

void SAMPLoad(bool SAMPLoading)
{
	char SAMPbuff[0x7F];

	if(SAMPLoading == true)
	{
		char * buffer;
    	int len = 4096; 
	
		sprintf(SAMPbuff, "%splugins/files/servers/%d/libsamp.so", GameStorage, pLoaderINI->Get().iServer);
    	ifstream infile(SAMPbuff, ios::in | ios::binary);
		sprintf(SAMPbuff, "%scache/libsamp.so", RootStorage);
    	ofstream outfile(SAMPbuff, ios::out | ios::binary);
    	if(!infile || !outfile)
		{ 
        	Log("No such file libsamp.so in folder: %d", pLoaderINI->Get().iServer);
        	exit(1);
    	}
 
   		buffer = new char[len];
    	while (!infile.eof())
		{
        	infile.read(buffer, len);
        	if(infile.gcount()) outfile.write(buffer, infile.gcount());
		}
 
    infile.close();
    outfile.close();
    delete[] buffer;
	}
	
}