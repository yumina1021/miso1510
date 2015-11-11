//*****************************************************************************
//
// font texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FONT_TEXTURE_H_
#define _FONT_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../../form/form.h"
//*****************************************************************************
// class definition
//*****************************************************************************
class FontTexture
{
public:
	enum TYPE
	{
		TYPE_MS_GOTHIC = 0,
		TYPE_MS_MINTYO,
		TYPE_MEIRYO,
		TYPE_MEIRYO_UI,
		TYPE_MAX
	};

	// constructor
	FontTexture(LPDIRECT3DDEVICE9 pDevice,const char* character, const short& size, TYPE type = TYPE_MS_MINTYO);
	FontTexture(LPDIRECT3DDEVICE9 pDevice, const unsigned long& character_code, const short& size, TYPE type = TYPE_MS_MINTYO);

	// destructor
	virtual ~FontTexture(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// create
	bool Create(void);

	// accessor
	LPDIRECT3DTEXTURE9 __texture(void)const { return texture_; }
	const TYPE& __type(void)const { return type_; }
	const unsigned long& __width(void)const { return width_; }
	const unsigned long& __height(void)const { return height_; }
	const unsigned long& __offset_y(void)const { return offset_y_; }

private:
	static const char* FONT_TYPE_NAME[TYPE_MAX];

	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DTEXTURE9 texture_;
	unsigned long character_code_;
	short size_;
	short weight_;
	TYPE type_;

	unsigned long width_;
	unsigned long height_;
	unsigned long offset_y_;
};

#endif	// _FONT_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
