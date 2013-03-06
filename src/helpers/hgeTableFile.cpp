#include "../../include/hgeTableFile.h"

#define _EOF_DATATABLE	(feof(file))
#define _CHECKEOF_DATATABLE(CLOSE)	if (_EOF_DATATABLE)	\
	{	\
		if (CLOSE)	\
		{	\
			CloseTableFile();	\
		}	\
		return false;\
	}
#define _READSTRINGBUFFERLINE(X, CLOSE)	if (!ReadStringBuffer(X))	\
	{	\
	if (CLOSE)	\
		{	\
		CloseTableFile();	\
		}	\
		return false;\
	}
#define _BREAKCOMMENTBUFFER	if (!CommentBuffer())	\
	break
#define _INITTINT	ti = -1
#define _LOADTINT	(tint[++ti])
#define _SAVETINT	(&_LOADTINT)

#ifndef __INTEL_COMPILER
#define _DOSWAPTINT	int tbegin = 0;	\
	int tend = ti;	\
	while (tbegin < tend)	\
{	\
	int tswapint = tint[tbegin];	\
	tint[tbegin] = tint[tend];	\
	tint[tend] = tswapint;	\
	++tbegin;	\
	--tend;	\
}
#else
#define _DOSWAPTINT
#endif

hgeTableFile::hgeTableFile()
{
	hge = hgeCreate(HGE_VERSION);
	formatoffset = NULL;
}


hgeTableFile::~hgeTableFile()
{
	CloseTableFile();
	hge->Release();
}

bool hgeTableFile::ReadTableFile( const char * filename, int version, const char * signature, int filetype, int linesize, int * uddata /*= NULL*/ )
{
	CloseTableFile();
	file = fopen(hge->Resource_MakePath(filename), "rb");
	if (!file)
	{
		return false;
	}


	int tgameversion = -1;
	char tsignature[256];
	int tfiletype = -1;

	fscanf(file, "%x%s%x", &tgameversion, tsignature, &tfiletype);
	if (tgameversion != version || strcmp(tsignature, signature) || tfiletype != filetype)
	{
		fclose(file);
		return false;
	}

	if (uddata)
	{
		fscanf(file, "%d", uddata);
	}

	lsize = linesize;
	if (lsize <= 0)
	{
		fclose(file);
		return false;
	}

	int mallocsize = sizeof(hgeTableFormatOffset) * lsize;
	formatoffset = (hgeTableFormatOffset *)malloc(mallocsize);
	ZeroMemory(formatoffset, mallocsize);

	return true;
}

bool hgeTableFile::ReadIntoData( void * data, int structsize, int clearsize/*=0*/, bool bclose/*=true*/ )
{
	if (!data || !formatoffset || lsize<=0 || structsize<=0)
	{
		if (bclose)
		{
			CloseTableFile();
		}
		return false;
	}

	for (int i=0; i<lsize; i++)
	{
		if (!strlen(formatoffset[i].format))
		{
			if (bclose)
			{
				CloseTableFile();
			}
			return false;
		}
	}

	if (clearsize)
	{
		ZeroMemory(data, clearsize);
	}

	_READSTRINGBUFFERLINE(lsize+2, bclose);
	int tindex = -1;

	while (!feof(file))
	{
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE(bclose);

		for (int i=0; i<lsize; i++)
		{
			fscanf(file, formatoffset[i].format, (BYTE *)data+tindex*structsize+formatoffset[i].offset);
			_CHECKEOF_DATATABLE(bclose);
		}
	}
	if (bclose)
	{
		CloseTableFile();
	}
	return true;
}

bool hgeTableFile::SetDataFormatOffset( int index, const char * format, int offset )
{
	if (index < 0 || index >= lsize)
	{
		return false;
	}
	strcpy_s(formatoffset[index].format, HGETABLEFORMATSTRMAX, format);
	formatoffset[index].offset = offset;
	return true;
}

bool hgeTableFile::CommentBuffer()
{
	if (!file)
	{
		return false;
	}
	fscanf(file, "%s", buffer);
	_CHECKEOF_DATATABLE(false);
	if (buffer[0] == '#')
	{
		fscanf(file, "%[^\r\n]", bufferlong);
		_CHECKEOF_DATATABLE(false);
		CommentBuffer();
	}
	return true;
}

bool hgeTableFile::ReadStringBuffer( int nCol )
{
	if (!file)
	{
		return false;
	}
	for (int i=0; i<nCol; i++)
	{
		fscanf(file, "%s", buffer);
		_CHECKEOF_DATATABLE(false);
	}
	return true;
}

void hgeTableFile::CloseTableFile()
{
	if (formatoffset)
	{
		free(formatoffset);
		formatoffset = NULL;
	}
	if (file)
	{
		fclose(file);
		file = NULL;
	}
	lsize = 0;
}
