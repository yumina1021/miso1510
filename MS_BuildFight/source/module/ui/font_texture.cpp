//*****************************************************************************
//
// font texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "font_texture.h"
//*****************************************************************************
// constant definition
//*****************************************************************************
const char* FontTexture::FONT_TYPE_NAME[TYPE_MAX] =
{
	"ＭＳ ゴシック",
	"ＭＳ 明朝",
	"メイリオ",
	"Meiryo UI"
};

//=============================================================================
// constructor
//=============================================================================
FontTexture::FontTexture(LPDIRECT3DDEVICE9 pDevice, const char* character, const short& size, TYPE type) :
device_(nullptr),
texture_(nullptr),
character_code_(0),
offset_y_(0),
type_(type)
{
	device_ = pDevice;

	if(IsDBCSLeadByte(*character))
	{
		character_code_ = (BYTE)character[0] << 8 | (BYTE)character[1];
	}
	else
	{
		character_code_ = character[0];
	}

	size_ = size;
}

//=============================================================================
// constructor
//=============================================================================
FontTexture::FontTexture(LPDIRECT3DDEVICE9 pDevice, const unsigned long& character_code, const short& size, TYPE type) :
device_(nullptr),
texture_(nullptr),
character_code_(0),
offset_y_(0),
type_(type)
{
	device_ = pDevice;
	character_code_ = character_code;
	size_ = size;
}

//=============================================================================
// destructor
//=============================================================================
FontTexture::~FontTexture(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool FontTexture::Initialize(void)
{
	return Create();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void FontTexture::Uninitialize(void)
{
	texture_->Release();
	texture_ = NULL;
}

//=============================================================================
// create
//=============================================================================
bool FontTexture::Create(void)
{
	HDC hdc;
	HFONT hfont;
	HFONT preview_hfont;
	LOGFONT logfont = {0};
	GLYPHMETRICS glyphmetrics;

	logfont.lfHeight = size_;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = weight_;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = TRUE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = SHIFTJIS_CHARSET;
	logfont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = PROOF_QUALITY;
	logfont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
	memcpy(logfont.lfFaceName,FONT_TYPE_NAME[type_],strlen(FONT_TYPE_NAME[type_]));

	hdc = GetDC(NULL);
	hfont = CreateFontIndirect(&logfont);
	preview_hfont = (HFONT)SelectObject(hdc,hfont);
	MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};

	DWORD size = GetGlyphOutline(hdc,character_code_,GGO_GRAY4_BITMAP,&glyphmetrics,0,nullptr,&mat2);
	unsigned char* ptr = nullptr;
	if(size == -1)
	{
		// 
		SelectObject(hdc,preview_hfont);
		DeleteObject(hfont);
		ReleaseDC(NULL,hdc);
		return false;
	}

	ptr = new unsigned char[size];
	GetGlyphOutline(hdc,character_code_,GGO_GRAY4_BITMAP,&glyphmetrics,size,ptr,&mat2);

	// 
	SelectObject(hdc,preview_hfont);
	DeleteObject(hfont);
	ReleaseDC(NULL,hdc);

	if(character_code_ == ' ')
	{
		width_ = (unsigned long)(size_ * 0.5f);
		height_ = size_;
		offset_y_ = 0;
	}
	else
	{
		width_ = (glyphmetrics.gmBlackBoxX + 3) / 4*4;
		height_ = glyphmetrics.gmBlackBoxY;
		offset_y_ = size_ - glyphmetrics.gmptGlyphOrigin.y;
	}
	// 
	device_->CreateTexture(width_,height_,1,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&texture_,nullptr);

	D3DLOCKED_RECT locked_rect;
	texture_->LockRect(0,&locked_rect,NULL,0);  // ロック

	int grad = 16; // 17階調の最大値
	DWORD *texture_buffer = (DWORD*)locked_rect.pBits;   // テクスチャメモリへのポインタ

	if(character_code_ == ' ')
	{
		for(int y = 0; y < height_; y++)
		{
			for(int x = 0; x < width_; x++)
			{
				texture_buffer[y * width_ + x] = (0 << 24) | 0x00ffffff;
			}
		}
	}
	else
	{
		for(int y = 0; y < height_; y++)
		{
			for(int x = 0; x < width_; x++)
			{
				DWORD alpha = ptr[y * width_ + x] * 255 / grad;
				texture_buffer[y * width_ + x] = (alpha << 24) | 0x00ffffff;
			}
		}
	}

	texture_->UnlockRect(0);


	delete[] ptr;
	ptr = NULL;


	return true;
}

//---------------------------------- EOF --------------------------------------
