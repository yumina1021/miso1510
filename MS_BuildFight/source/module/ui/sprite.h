//*****************************************************************************
//
// sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../../form/form.h"
//*****************************************************************************
// class definition
//*****************************************************************************
class Sprite
{
public:
	enum POINT
	{
		POINT_CENTER = 0,
		POINT_LEFT_UP,
		POINT_LEFT_MIDDLE,
		POINT_LEFT_DOWN,
		POINT_RIGHT_UP,
		POINT_RIGHT_MIDDLE,
		POINT_RIGHT_DOWN,
		POINT_MIDDLE_UP,
		POINT_MIDDLE_DOWN,
		POINT_MAX,
	};

	enum TEXTURE_ID
	{
		TEXTURE_ID_NONE = 0,
		TEXTURE_ID_MAX
	};

	// constructor
	Sprite(LPDIRECT3DDEVICE9 pDevice);

	// destructor
	virtual ~Sprite(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// draw
	void Draw(void);
	void Draw(const D3DXMATRIX& matrix, SHADER_SET shader_);

	// set parameter
	void SetParameter(void);

	// accessor
	const D3DXVECTOR2& __position(void)const { return position_; }
	void __position(const D3DXVECTOR2& position) { position_ = position; }
	const float& __rotation(void)const { return rotation_; }
	void __rotation(const float& rotation) { rotation_ = rotation; }
	const D3DXVECTOR2& __size(void)const { return size_; }
	void __size(const D3DXVECTOR2& size) { size_ = size; }
	const POINT& __point(void)const { return point_; }
	void __point(const POINT& point) { point_ = point; }
	const D3DCOLOR& __color(void)const { return color_; }
	void __color(const D3DCOLOR& color) { color_ = color; }
	const float& __left(void)const { return left_; }
	void __left(const float& left) { left_ = left; }
	const float& __right(void)const { return right_; }
	void __right(const float& right) { right_ = right; }
	const float& __top(void)const { return top_; }
	void __top(const float& top) { top_ = top; }
	const float& __bottom(void)const { return bottom_; }
	void __bottom(const float& bottom) { bottom_ = bottom; }
	const TEXTURE_ID& __texture_id(void)const { return texture_id_; }
	void __texture_id(const TEXTURE_ID& texture_id) { texture_id_ = texture_id; }
	void __texture(LPDIRECT3DTEXTURE9 texture) { texture_ = texture; }
	void __index(const long& index) { index_ = index; }
	void __division_width(const unsigned long& division_width) { division_width_ = division_width; }
	void __division_height(const unsigned long& division_height) { division_height_ = division_height; }
	bool __is_flip(void)const { return is_flip_; }
	void __is_flip(bool is_flip) { is_flip_ = is_flip; }


private:
	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DTEXTURE9 texture_;

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const POINT DEFAULT_POINT;

	D3DXVECTOR2 position_;
	float rotation_;
	D3DXVECTOR2 scale_;

	D3DXVECTOR2 size_;
	D3DCOLOR color_;
	POINT point_;
	float left_;
	float right_;
	float top_;
	float bottom_;
	TEXTURE_ID texture_id_;
	long index_;
	unsigned long division_width_;
	unsigned long division_height_;
	bool is_flip_;
};

#endif	// _SPRITE_H_

//---------------------------------- EOF --------------------------------------
