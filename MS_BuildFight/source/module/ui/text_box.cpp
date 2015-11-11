//*****************************************************************************
//
// text box
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include"text_box.h"
#include "sprite.h"
#include "../../exten_common.h"
//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
TextBox::TextBox(LPDIRECT3DDEVICE9 pDevice, const FontTexture::TYPE& font_type, const unsigned long& font_size) :
device_(nullptr),
size_(1280.0f,720.0f),
font_color_(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f)),
font_size_(0),
string_length_(0),
position_(0.0f,0.0f),
offset_x_(0),
offset_y_(0),
string_count_(0),
scale_(1.0f,1.0f),
rotation_(0.0f),
show_speed_(3),
show_count_(0),
frame_count_(0),
font_type_(font_type)
{
	device_ = pDevice;

	font_color_ = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	font_size_ = font_size;
	font_type_ = font_type;
	memset(string_,0,sizeof(string_));
}

//=============================================================================
// destructor
//=============================================================================
TextBox::~TextBox(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TextBox::Initialize(void)
{
	for(unsigned long i = 0;i < STRING_MAX;++i)
	{
		sprites_[i] = new Sprite(device_);
		sprites_[i]->Initialize();
		sprites_[i]->SetParameter();
	}

	//PS作成
	Create_PS("source/shader/basicPS.hlsl", "PS", &shader_.ps, &shader_.psc, device_);
	//VS作成
	Create_VS("source/shader/basicVS.hlsl", "VS", &shader_.vs, &shader_.vsc, device_);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void TextBox::Uninitialize (void)
{
	for(unsigned long i = 0;i < STRING_MAX;++i)
	{
		sprites_[i]->Uninitialize();
		delete sprites_[i];
		sprites_[i] = NULL;
	}

	for(auto it = font_texture_container_.begin();it != font_texture_container_.end();++it)
	{
		it->second->Uninitialize();
		delete it->second;
		it->second = NULL;
	}

	font_texture_container_.clear();
}

//=============================================================================
// draw
//=============================================================================
void TextBox::Draw(void)
{
	D3DXMATRIX scale_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX tranlation_matrix;
	D3DXMATRIX world_matrix;

	D3DXMatrixIdentity(&world_matrix);

	// scale matrix
	D3DXMatrixIdentity(&scale_matrix);
	D3DXMatrixScaling(&scale_matrix,scale_.x,scale_.y,0.0f);
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&scale_matrix);

	// rotation matrix
	D3DXMatrixIdentity(&rotation_matrix);
	D3DXMatrixRotationYawPitchRoll(&rotation_matrix,0.0f,0.0f,rotation_);
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&rotation_matrix);

	// tranlation matrix
	D3DXMatrixIdentity(&tranlation_matrix);
	D3DXMatrixTranslation(&tranlation_matrix,position_.x,position_.y,0.0f);
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&tranlation_matrix);

	if(show_speed_ == 0)
	{
		show_count_ = string_count_;
	}

	if(show_count_ < string_count_)
	{
		frame_count_++;

		if(frame_count_ % show_speed_ == 0)
		{
			show_count_++;
		}
	}

	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	for(unsigned long i = 0;i < show_count_;++i)
	{
		sprites_[i]->Draw(world_matrix,shader_);
	}

	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

//=============================================================================
// print
//=============================================================================
void TextBox::Print(const char* format,...)
{
	va_list args;

	va_start(args,format);

	Print(format,font_color_,args);

	va_end(args);
}

//=============================================================================
// print
//=============================================================================
void TextBox::Print(const char* format,D3DCOLOR font_color,...)
{
	va_list args;
	char work[STRING_MAX] = {NULL};
	unsigned long length = 0;

	// 可変引数の参照開始
	va_start(args,font_color);

	// 文字列に変更
	vsprintf(work,format,args);

	// 可変引数の参照終了
	va_end(args);

	strcat_s(string_,work);

	string_length_ = strlen(string_);

	for(unsigned long i = length; i < string_length_;++i)
	{
		unsigned long character_code = 0;
		FontTexture* font_texture = nullptr;

		if(IsDBCSLeadByte(string_[i]))
		{
			character_code = (BYTE)string_[i + 0] << 8 | (BYTE)string_[i + 1];
			++i;
		}
		else
		{
			character_code = string_[i + 0];
		}

		// 
		if(character_code == '\n')
		{
			offset_x_ = 0;
			offset_y_ += font_size_;
			continue;
		}

		auto it = font_texture_container_.find(character_code);

		if(it == font_texture_container_.end())
		{
			font_texture = new FontTexture(device_,character_code,font_size_,font_type_);
			font_texture->Initialize();
			font_texture_container_.insert(std::pair<unsigned long,FontTexture*>(character_code,font_texture));
		}
		else
		{
			font_texture = it->second;
		}

		if(offset_x_ + font_texture->__width() > (unsigned long)size_.x)
		{
			offset_x_ = 0;
			offset_y_ += font_size_;
		}

		sprites_[string_count_]->__texture(font_texture->__texture());
		sprites_[string_count_]->__position(D3DXVECTOR2((float)(position_.x + offset_x_), (float)(position_.y+offset_y_ + font_texture->__offset_y())));
		sprites_[string_count_]->__size(D3DXVECTOR2((float)font_texture->__width(),(float)font_texture->__height()));
		sprites_[string_count_]->__color(font_color);
		sprites_[string_count_]->SetParameter();
		offset_x_ += font_texture->__width();
		string_count_++;
	}
}

//=============================================================================
// clear
//=============================================================================
void TextBox::Clear(void)
{
	memset(string_,0,sizeof(string_));
	string_count_ = 0;
	offset_x_ = 0;
	offset_y_ = 0;
	show_count_ = 0;
	frame_count_ = 0;
}

//=============================================================================
// restart
//=============================================================================
void TextBox::Restart(void)
{
	show_count_ = 0;
	frame_count_ = 0;
}

//---------------------------------- EOF --------------------------------------
