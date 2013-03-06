#include "../Header/BResource.h"
#include "../../../include/hgeTableFile.h"

#define BRES_DATAFOLDER	"Data/"
#define BRES_TABLEEXT	".table"
#define BRES_TEXTURETABLE	"Texture"
#define BRES_SPRITETABLE	"Sprite"

BResource::BResource(void)
{
	ZeroMemory(tex, sizeof(HTEXTURE) * TEXMAX);
	ZeroMemory(texinfo, sizeof(hgeTextureInfo) * TEXMAX);
	InitTexinfo();
	spritenumber = 0;
	spritedata = NULL;
}


BResource::~BResource(void)
{
	ReleaseSpriteData();
}

bool BResource::LoadTexture( int texindex/*=-1*/ )
{
	if (texindex < 0)
	{
		for (int i=0; i<TEXMAX; i++)
		{
			LoadTexture(i);
		}
		return true;
	}

	char tnbuffer[M_STRMAX];
	if(tex[texindex].tex)
		hge->Texture_Free(tex[texindex]);
	tex[texindex].tex = NULL;

	strcpy(tnbuffer, texturedata[texindex].texfilename);
	if(strlen(tnbuffer))
	{
		tex[texindex] = hge->Texture_Load(tnbuffer);
	}

	if(tex[texindex].tex == NULL)
	{
		tex[texindex] = hge->Texture_Create(0, 0);
		return false;
	}
	tex[texindex].texindex = texindex;
	return true;
}

void BResource::InitTexinfo()
{
	for (int i=0; i<TEXMAX; i++)
	{
		texinfo[i].tex = NULL;
		texinfo[i].texw = texturedata[i].width;
		texinfo[i].texh = texturedata[i].height;
	}
	for (int i=0; i<TEXMAX; i++)
	{
		tex[i].texindex = i;
		texinfo[i].tex = &tex[i].tex;
	}
	hge->Gfx_SetTextureInfo(TEXMAX, texinfo);
}

bool BResource::FreeTexture( int texindex/*=-1*/ )
{
	if (texindex < 0)
	{
		for (int i=0; i<TEXMAX; i++)
		{
			FreeTexture(i);
		}
		return true;
	}

	if (tex[texindex].tex)
	{
		hge->Texture_Free(tex[texindex]);
		tex[texindex] = NULL;
		tex[texindex].texindex = texindex;
		return true;
	}
	return false;
}

void BResource::InitSpriteData()
{
	ReleaseSpriteData();
	spritedata = (spriteData *)malloc(RSIZE_SPRITE);
	ZeroMemory(spritedata, RSIZE_SPRITE);
}

void BResource::ReleaseSpriteData()
{
	if (spritedata)
	{
		free(spritedata);
		spritedata = NULL;
	}
}

bool BResource::ReadTables()
{
	if (!ReadTextureTable())
	{
		return false;
	}
	if (!ReadSpriteTable())
	{
		return false;
	}
	return true;
}

bool BResource::ReadTextureTable()
{
	hgeTableFile * ptable = &hgeTableFile::getInstance();
	if (ptable->ReadTableFile(BRES_DATAFOLDER BRES_TEXTURETABLE BRES_TABLEEXT, GAME_VERSION, GAME_SIGNATURE, BRES_TEXTURETABLEID, 3))
	{
		ptable->SetDataFormatOffset(0, "%s", offsetof(struct textureData, texfilename));
		ptable->SetDataFormatOffset(1, "%d", offsetof(struct textureData, width));
		ptable->SetDataFormatOffset(2, "%d", offsetof(struct textureData, height));

		if (ptable->ReadIntoData(texturedata, sizeof(textureData), RSIZE_TEXTURE, false))
		{
			return true;
		}
	}
	return false;
}

bool BResource::ReadSpriteTable()
{
	hgeTableFile * ptable = &hgeTableFile::getInstance();
	if (ptable->ReadTableFile(BRES_DATAFOLDER BRES_SPRITETABLE BRES_TABLEEXT, GAME_VERSION, GAME_SIGNATURE, BRES_SPRITETABLEID, 6, &spritenumber))
	{
		ptable->SetDataFormatOffset(0, "%s", offsetof(struct spriteData, spritename));
		ptable->SetDataFormatOffset(1, "%d", offsetof(struct spriteData, tex));
		ptable->SetDataFormatOffset(2, "%d", offsetof(struct spriteData, tex_x));
		ptable->SetDataFormatOffset(3, "%d", offsetof(struct spriteData, tex_y));
		ptable->SetDataFormatOffset(4, "%d", offsetof(struct spriteData, tex_w));
		ptable->SetDataFormatOffset(5, "%d", offsetof(struct spriteData, tex_h));

		InitSpriteData();
		if (ptable->ReadIntoData(spritedata, sizeof(spriteData), RSIZE_SPRITE, false))
		{
			return true;
		}
	}
	return false;
}
