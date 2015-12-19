//*****************************************************************************
//
// sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include"sprite.h"
#include "../etc/Camera.h"
#include "../../administer/Maneger.h"
//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Sprite::DEFAULT_SIZE = D3DXVECTOR2(100.0f,100.0f);
const D3DCOLOR Sprite::DEFAULT_COLOR = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
const D3DXVECTOR2 Sprite::DEFAULT_POSITION = D3DXVECTOR2(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f);
const Sprite::POINT Sprite::DEFAULT_POINT = Sprite::POINT_LEFT_UP;

//=============================================================================
// constructor
//=============================================================================
Sprite::Sprite(LPDIRECT3DDEVICE9 pDevice)
	:device_(nullptr)
	,vertex_buffer_(nullptr)
	,texture_(nullptr)
	,position_(DEFAULT_POSITION)
	,size_(DEFAULT_SIZE)
	,color_(DEFAULT_COLOR)
	,point_(DEFAULT_POINT)
	,left_(0.0f)
	,right_(1.0f)
	,top_(0.0f)
	,bottom_(1.0f)
	,rotation_(0.0f)
	,scale_(1.0f,1.0f)
	, texture_id_(TEXTURE_ID_NONE)
	,index_(-1)
	,division_width_(1)
	,division_height_(1)
	,is_flip_(false)
{
	device_ = pDevice;
}

//=============================================================================
// destructor
//=============================================================================
Sprite::~Sprite(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Sprite::Initialize(void)
{
	// create vertex buffer
	if (FAILED(device_->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &vertex_buffer_, NULL)))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Sprite::Uninitialize (void)
{
	// relase vertex buffer
	vertex_buffer_->Release();
	texture_ = NULL;
}

//=============================================================================
// draw
//=============================================================================
void Sprite::Draw(void)
{
	D3DXMATRIX matrix;

	D3DXMatrixIdentity(&matrix);

	SHADER_SET shader;
	Draw(matrix, shader);
}

//=============================================================================
// draw
//=============================================================================
void Sprite::Draw(const D3DXMATRIX& matrix,SHADER_SET shader_)
{
	CCamera* pCamera = CManager::GetCamera();

	//ƒrƒ…[s—ñ
	D3DXVECTOR3 eye(0.0f, 0.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX scale_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX tranlation_matrix;
	D3DXMATRIX world_matrix, view_matrix, proj_matrix;

	eye = pCamera->GetPosP();
	at = pCamera->GetPosR();
	up = pCamera->GetVecUp();

	D3DXMatrixIdentity(&world_matrix);
	
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&matrix);

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

	D3DXMatrixLookAtLH(&view_matrix, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj_matrix, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = world_matrix*view_matrix*proj_matrix;

	shader_.vsc->SetMatrix(device_, "gWvp", &wvp);
	shader_.vsc->SetVector(device_, "MatDiffuse", (D3DXVECTOR4*)&color_);

	if (texture_ != NULL)
	{
		unsigned int s0 = shader_.psc->GetSamplerIndex("texSampler");
		device_->SetTexture(s0, texture_);
	}
	else
	{
		device_->SetTexture(0, NULL);
	}

	device_->SetVertexShader(shader_.vs);
	device_->SetPixelShader(shader_.ps);

	device_->SetStreamSource(0, vertex_buffer_, 0, sizeof(VERTEX_2D));

	device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	device_->SetVertexShader(NULL);
	device_->SetPixelShader(NULL);
}

//=============================================================================
// set parameter
//=============================================================================
void Sprite::SetParameter(void)
{
	VERTEX_2D* vertex = nullptr;

	// lock
	vertex_buffer_->Lock(0,0,(void**)&vertex,0);

	switch(point_)
	{
		case POINT_LEFT_UP:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x, 0.0f, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, size_.y, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x, size_.y, 0.0f);
			break;
		}
		case POINT_LEFT_MIDDLE:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, -size_.y * 0.5f, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x, -size_.y * 0.5f, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, size_.y * 0.5f, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x, size_.y * 0.5f, 0.0f);
			break;
		}
		case POINT_LEFT_DOWN:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, -size_.y, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x, -size_.y, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x, 0.0f, 0.0f);
			break;
		}
		case POINT_MIDDLE_UP:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x * 0.5f, 0.0f, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x * 0.5f, 0.0f, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x * 0.5f, size_.y, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x * 0.5f, size_.y, 0.0f);
			break;
		}
		case POINT_CENTER:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x * 0.5f, -size_.y * 0.5f, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x * 0.5f, -size_.y * 0.5f, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x * 0.5f, size_.y * 0.5f, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x * 0.5f, size_.y * 0.5f, 0.0f);
			break;
		}
		case POINT_MIDDLE_DOWN:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x * 0.5f, -size_.y, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x * 0.5f, -size_.y, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x * 0.5f, 0.0f, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(size_.x * 0.5f, 0.0f, 0.0f);
			break;
		}
		case POINT_RIGHT_UP:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x, 0.0f, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x, size_.y, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, size_.y, 0.0f);
			break;
		}
		case POINT_RIGHT_MIDDLE:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x, -size_.y * 0.5f, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, -size_.y * 0.5f, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x, size_.y * 0.5f, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, size_.y * 0.5f, 0.0f);
			break;
		}
		case POINT_RIGHT_DOWN:
		{
			vertex[0].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x, -size_.y, 0.0f);
			vertex[1].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, -size_.y, 0.0f);
			vertex[2].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(-size_.x, 0.0f, 0.0f);
			vertex[3].vtx = D3DXVECTOR3(position_.x, position_.y, 0.0f) + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}
	}

	//hrw
	vertex[0].hrw = 1.0f;
	vertex[1].hrw = 1.0f;
	vertex[2].hrw = 1.0f;
	vertex[3].hrw = 1.0f;

	// color
	vertex[0].diffuse = color_;
	vertex[1].diffuse = color_;
	vertex[2].diffuse = color_;
	vertex[3].diffuse = color_;

	if(index_ == -1)
	{
		if(is_flip_)
		{
			// texcoord
			vertex[0].tex = D3DXVECTOR2(right_,top_);
			vertex[1].tex = D3DXVECTOR2(left_, top_);
			vertex[2].tex = D3DXVECTOR2(right_, bottom_);
			vertex[3].tex = D3DXVECTOR2(left_, bottom_);
		}
		else
		{
			// texcoord
			vertex[0].tex = D3DXVECTOR2(left_, top_);
			vertex[1].tex = D3DXVECTOR2(right_, top_);
			vertex[2].tex = D3DXVECTOR2(left_, bottom_);
			vertex[3].tex = D3DXVECTOR2(right_, bottom_);
		}
	}
	else
	{
		float left = 1.0f / division_width_ * (index_ % division_width_);
		float right = 1.0f / division_width_ * ((index_ % division_width_) + 1);
		float top = 1.0f / division_height_ * (index_ / division_width_);
		float bottom = 1.0f / division_height_ * ((index_ / division_width_) + 1);

		if(is_flip_)
		{
			// texcoord
			vertex[0].tex = D3DXVECTOR2(right, top);
			vertex[1].tex = D3DXVECTOR2(left, top);
			vertex[2].tex = D3DXVECTOR2(right, bottom);
			vertex[3].tex = D3DXVECTOR2(left, bottom);
		}
		else
		{
			// texcoord
			vertex[0].tex = D3DXVECTOR2(left, top);
			vertex[1].tex = D3DXVECTOR2(right, top);
			vertex[2].tex = D3DXVECTOR2(left, bottom);
			vertex[3].tex = D3DXVECTOR2(right, bottom);
		}
	}

	// unlock
	vertex_buffer_->Unlock();

	if (texture_id_ != TEXTURE_ID_NONE)
	{
		// get texture
		//texture_ = device_->GetTexture(0,texture_id_);
		texture_ = texture_;
	}

}

//---------------------------------- EOF --------------------------------------
