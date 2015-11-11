//*****************************************************************************
//
// text box
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "font_texture.h"
#include "../../form/form.h"
#include <map>
//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;
//*****************************************************************************
// class definition
//*****************************************************************************
class TextBox
{
public:
	// constructor
	TextBox(LPDIRECT3DDEVICE9 pDevice, const FontTexture::TYPE& font_type, const unsigned long& font_size);

	// destructor
	virtual ~TextBox(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// draw
	void Draw(void);

	// print
	void Print(const char* format,...);

	// print
	void Print(const char* format,D3DCOLOR font_color,...);

	// clear
	void Clear(void);

	// reset
	void Reset(void);

	// restart
	void Restart(void);

	// accessor
	const D3DXVECTOR2& __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	void __show_speed(const unsigned long& show_speed) { show_speed_ = show_speed; }
	const D3DCOLOR& __font_color(void)const { return font_color_; }
	const D3DCOLOR __font_color(const D3DCOLOR& font_color) { D3DCOLOR ret = font_color_;font_color_ = font_color; return ret; }

private:
	static const unsigned long STRING_MAX = 1024;
	LPDIRECT3DDEVICE9 device_;

	D3DCOLOR font_color_;
	unsigned long font_size_;
	FontTexture::TYPE font_type_;

	D3DXVECTOR2 position_;
	float rotation_;
	D3DXVECTOR2 scale_;

	D3DXVECTOR2 size_;
	char string_[STRING_MAX];
	Sprite* sprites_[STRING_MAX];
	std::map<unsigned long, FontTexture*> font_texture_container_;
	unsigned long offset_x_;
	unsigned long offset_y_;
	unsigned long string_count_;
	unsigned long string_length_;

	unsigned long show_speed_;
	unsigned long show_count_;
	unsigned long frame_count_;

	SHADER_SET	shader_;
};

#endif	// _TEXT_BOX_H_

//---------------------------------- EOF --------------------------------------
