#include "../Header/BResource.h"
#include "../../../include/hgeTableFile.h"
#include "../Header/SpriteItemManager.h"

#define BRES_DATAFOLDER	"Data/"
#define BRES_TABLEEXT	".table"
#define BRES_TEXTURETABLE		"Texture"
#define BRES_SPRITETABLE		"Sprite"
#define BRES_PLAYERMOTIONTABLE	"PlayerMotion"

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
	if (!ReadPlayerMotionTable())
	{
		return false;
	}
	return true;
}

bool BResource::ReadTextureTable()
{
	hgeTableFile * ptable = hgeTableFile::PIns();
	if (ptable->ReadTableFile(BRES_DATAFOLDER BRES_TEXTURETABLE BRES_TABLEEXT, GAME_VERSION, GAME_SIGNATURE, BRES_TEXTURETABLEID, 3))
	{
		ptable->SetDataFormatOffset(0, "%s", offsetof(struct textureData, texfilename));
		ptable->SetDataFormatOffset(1, "%d", offsetof(struct textureData, width));
		ptable->SetDataFormatOffset(2, "%d", offsetof(struct textureData, height));

		if (ptable->ReadIntoData(texturedata, sizeof(textureData), RSIZE_TEXTURE))
		{
			return true;
		}
	}
	return false;
}

bool BResource::ReadSpriteTable()
{
	hgeTableFile * ptable = hgeTableFile::PIns();
	if (ptable->ReadTableFile(BRES_DATAFOLDER BRES_SPRITETABLE BRES_TABLEEXT, GAME_VERSION, GAME_SIGNATURE, BRES_SPRITETABLEID, 6, &spritenumber))
	{
		ptable->SetDataFormatOffset(0, "%s", offsetof(struct spriteData, spritename));
		ptable->SetDataFormatOffset(1, "%d", offsetof(struct spriteData, tex));
		ptable->SetDataFormatOffset(2, "%d", offsetof(struct spriteData, tex_x));
		ptable->SetDataFormatOffset(3, "%d", offsetof(struct spriteData, tex_y));
		ptable->SetDataFormatOffset(4, "%d", offsetof(struct spriteData, tex_w));
		ptable->SetDataFormatOffset(5, "%d", offsetof(struct spriteData, tex_h));

		InitSpriteData();
		if (ptable->ReadIntoData(spritedata, sizeof(spriteData), RSIZE_SPRITE))
		{
			return true;
		}
	}
	return false;
}

bool BResource::ReadPlayerMotionTable()
{
	hgeTableFile * ptable = hgeTableFile::PIns();

	if (ptable->ReadTableFile(BRES_DATAFOLDER BRES_PLAYERMOTIONTABLE BRES_TABLEEXT, GAME_VERSION, GAME_SIGNATURE, BRES_PLAYERMOTIONTABLEID, 12/*16*/))
	{
		ptable->SetDataFormatOffset(0, "%s", offsetof(struct playerMotionData, basesiid), &SpriteItemManager::GetIndexByName);
		ptable->SetDataFormatOffset(1, "%d", offsetof(struct playerMotionData, duration[0]));
		ptable->SetDataFormatOffset(2, "%d", offsetof(struct playerMotionData, siidoffset[0]));
		ptable->SetDataFormatOffset(3, "%d", offsetof(struct playerMotionData, duration[1]));
		ptable->SetDataFormatOffset(4, "%d", offsetof(struct playerMotionData, siidoffset[1]));
		ptable->SetDataFormatOffset(5, "%d", offsetof(struct playerMotionData, duration[2]));
		ptable->SetDataFormatOffset(6, "%d", offsetof(struct playerMotionData, siidoffset[2]));
		ptable->SetDataFormatOffset(7, "%d", offsetof(struct playerMotionData, duration[3]));
		ptable->SetDataFormatOffset(8, "%f", offsetof(struct playerMotionData, bbxoff));
		ptable->SetDataFormatOffset(9, "%f", offsetof(struct playerMotionData, bbyoff));
		ptable->SetDataFormatOffset(10, "%f", offsetof(struct playerMotionData, bbw));
		ptable->SetDataFormatOffset(11, "%f", offsetof(struct playerMotionData, bbh));
		/*
		ptable->SetDataFormatOffset(8, "%d", offsetof(struct playerMotionData, siidoffset[3]));
		ptable->SetDataFormatOffset(9, "%d", offsetof(struct playerMotionData, duration[4]));
		ptable->SetDataFormatOffset(10, "%d", offsetof(struct playerMotionData, siidoffset[4]));
		ptable->SetDataFormatOffset(11, "%d", offsetof(struct playerMotionData, duration[5]));
		ptable->SetDataFormatOffset(12, "%d", offsetof(struct playerMotionData, siidoffset[5]));
		ptable->SetDataFormatOffset(13, "%d", offsetof(struct playerMotionData, duration[6]));
		ptable->SetDataFormatOffset(14, "%d", offsetof(struct playerMotionData, siidoffset[6]));
		ptable->SetDataFormatOffset(15, "%d", offsetof(struct playerMotionData, duration[7]));
		*/
		if (ptable->ReadIntoData(playermotiondata, sizeof(playerMotionData), RSIZE_PLAYERMOTION))
		{
			for (int i=0; i<PLAYERMOTIONSETMAX; i++)
			{
				playermotiondata[i].bbxoff *= FLT_IMUL;
				playermotiondata[i].bbyoff *= FLT_IMUL;
				playermotiondata[i].bbw *= FLT_IMUL;
				playermotiondata[i].bbh *= FLT_IMUL;
			}
			return true;
		}
	}
	return false;
}
