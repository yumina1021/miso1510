//============================================================================
// File: renderTarget.cpp
// Author: SHUN SAKAI
// Content: ���\�[�X�Ǘ�
//============================================================================
//*****************************************************************************
// Include
//*****************************************************************************
#include "renderTarget.h"
#include "../administer/entityFactory.hpp"
#include "../administer/finalize.hpp"

//*****************************************************************************
// Link
//*****************************************************************************

//*****************************************************************************
// Macro
//*****************************************************************************

//*****************************************************************************
// GlobalArea
//*****************************************************************************

//=============================================================================
// FunctionName: Constructor
// Param: void
// ReturnValue: void
// Content: �R���X�g���N�^�ł�������̃v���C�I���e�B�ŕ`�揇�Ԃ����܂�
//			�S�Ẵ����o�ϐ��͂����ŏ����������Ă�������
//=============================================================================
RenderTarget::RenderTarget() :
tex(nullptr),
surface(nullptr)
{

}// RenderTarget
//=============================================================================
// FunctionName: Destructor
// Param: void
// ReturnValue: void
// Content: �e�퓮�I�Ɋm�ۂ����o�b�t�@�Ȃǂ̊J���������s��
//=============================================================================
RenderTarget::~RenderTarget(){

	SafeRelease(surface);

}// ~RenderTarget
//=============================================================================
// FunctionName: Init
// Param: �f�o�C�X
// Param: ��
// Param: ����
// ReturnValue: �����������ǂ���
// Content: ������
//=============================================================================
bool RenderTarget::Init(LPDIRECT3DDEVICE9 paramDevice9,
	float paramWidth,
	float paramHeight){


	if (FAILED(paramDevice9->CreateTexture((UINT)paramWidth,
											(UINT)paramHeight,
											1,
											D3DUSAGE_RENDERTARGET,
											D3DFMT_A32B32G32R32F,
											D3DPOOL_DEFAULT,
											&texBuff,
											NULL))){
#ifdef _DEBUG

		//���b�Z�[�W�{�b�N�X�ŏo��
		MessageBox(NULL, "�e�N�X�`���̐����Ɏ��s�����̂�", "���s", MB_OK);

#endif

		return false;
	}// if


	// �T�[�t�F�[�X����̐ݒ�
	if (FAILED(texBuff->GetSurfaceLevel(0, &surface))){

#ifdef _DEBUG
		// windows�̃��b�Z�[�W��\��
		MessageBox(NULL, "�����_�[�^�[�Q�b�g�p�̃e�N�X�`���̐����Ɏ��s�����̂�", "�G���[", MB_OK);
#endif
		return false; 
	}

	return true;

}// Init
//=============================================================================
// FunctionName: SetRenderTarget
// Param: �f�o�C�X
// Param: ��
// Param: ����
// ReturnValue: �����������ǂ���
// Content: ������
//=============================================================================
bool RenderTarget::SetRenderTarget(LPDIRECT3DDEVICE9 paramDevice9, DWORD paramSetIndex){

	if (FAILED(paramDevice9->SetRenderTarget(paramSetIndex, surface))){ return false; }

	return true;

}// SetRenderTarget
//=============================================================================
// FunctionName: SetRenderTarget
// Param: �f�o�C�X
// Param: ��
// Param: ����
// ReturnValue: �����������ǂ���
// Content: ������
//=============================================================================
bool RenderTarget::ReleaseRenderTarget(LPDIRECT3DDEVICE9 paramDevice9, DWORD paramSetIndex){

	if (FAILED(paramDevice9->SetRenderTarget(paramSetIndex, nullptr))){ return false; }

	return true;

}// SetRenderTarget
//=============================================================================
// FunctionName: SetRenderTarget
// Param: �f�o�C�X
// Param: ��
// Param: ����
// ReturnValue: �����������ǂ���
// Content: ������
//=============================================================================
bool RenderTarget::GetRenderTarget(LPDIRECT3DDEVICE9 paramDevice9, DWORD paramSetIndex){

	if (FAILED(paramDevice9->GetRenderTarget(paramSetIndex, &surface))){ return false; }

	return true;

}// SetRenderTarget
LPDIRECT3DTEXTURE9 RenderTarget::GetTexBuff(){
	return texBuff;
}
// EOF