#ifndef HGETABLEFILE_H
#define HGETABLEFILE_H

#include "hge.h"
#include <vector>

using namespace std;

/************************************************************************/
/* HGE Table File Class                                                 */
/************************************************************************/

#define HGETABLEFORMATSTRMAX	16

struct hgeTableFormatOffset 
{
	char format[HGETABLEFORMATSTRMAX];
	int offset;
};

class hgeTableFile
{
public:
	static hgeTableFile& getInstance() { static hgeTableFile instance; return instance; }

private:
	hgeTableFile();
	~hgeTableFile();
	hgeTableFile(hgeTableFile const&);
	void operator=(hgeTableFile const&);

public:

	bool ReadTableFile(const char * filename, int version, const char * signature, int filetype, int linesize, int * uddata = NULL);
	bool SetDataFormatOffset(int index, const char * format, int offset);
	bool ReadIntoData(void * data, int structsize, int clearsize=0, bool bclose=true);
	void CloseTableFile();

private:

	bool ReadStringBuffer(int nCol);
	bool CommentBuffer();

	char buffer[MAX_PATH];
	char bufferlong[MAX_PATH*4];

	HGE * hge;

	FILE * file;
	int lsize;
	hgeTableFormatOffset * formatoffset;
};

#endif