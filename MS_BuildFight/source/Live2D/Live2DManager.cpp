//============================================================================
// FileName: gameEntity.cpp
// Author: SHUN SAKAI
// Content: �Q�[�����ɑ��݂���I�u�W�F�N�g
//============================================================================
//*****************************************************************************
// Include
//*****************************************************************************
#include "Live2DManager.h"
#include "Live2DModel.h"
#include "../administer/finalize.hpp"
#include "../administer/entityFactory.hpp"
#include "../administer/Input.h"
#include "../administer/Maneger.h"
#include "renderTarget.h"

#include <stdio.h>

//*****************************************************************************
// Macro
//*****************************************************************************
const float PI(3.14f);

// ���[�V�����̗D��x�萔
static const int PRIORITY_NONE = 0;
static const int PRIORITY_IDLE = 1;
static const int PRIORITY_NORMAL = 2;
static const int PRIORITY_FORCE = 3;

static const int MAX_CHARCTER(4);
//*****************************************************************************
// NameSpace
//*****************************************************************************
using namespace live2d;

//*****************************************************************************
// GlobalArea
//*****************************************************************************

//=============================================================================
// Constructor
//=============================================================================
Live2DManager::Live2DManager(){

	// Live2D�̏�����
	Live2D::init();

	// ����
	mod = Factory::CreateArray<Live2DModel>(MAX_CHARCTER);
	modRender = Factory::CreateArray<RenderTarget>(MAX_CHARCTER);

}// Live2DManager
//=============================================================================
// Destructor
//=============================================================================
Live2DManager::~Live2DManager(){

	SafeDeleteArray(mod);
	SafeDeleteArray(modRender);


	Live2D::dispose();

}// ~Live2DManager
//=============================================================================
// Init
//=============================================================================
bool Live2DManager::Init(LPDIRECT3DDEVICE9 paramDevice){
	

	// ������
	mod[Live2DModel::MODEL_TYPE::ROSA].Init(Live2DModel::MODEL_TYPE::ROSA, paramDevice);
	mod[Live2DModel::MODEL_TYPE::ROSA].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -200.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::ROSA].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// ������
	mod[Live2DModel::MODEL_TYPE::LILA].Init(Live2DModel::MODEL_TYPE::LILA, paramDevice);
	mod[Live2DModel::MODEL_TYPE::LILA].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -600.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::LILA].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// ������
	mod[Live2DModel::MODEL_TYPE::LICHT].Init(Live2DModel::MODEL_TYPE::LICHT, paramDevice);
	mod[Live2DModel::MODEL_TYPE::LICHT].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -600.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::LICHT].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// ������
	mod[Live2DModel::MODEL_TYPE::NAVI].Init(Live2DModel::MODEL_TYPE::NAVI, paramDevice);
	mod[Live2DModel::MODEL_TYPE::NAVI].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -600.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::NAVI].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// Live2D���f���p�̃����_�[�^�[�Q�b�g
	for (int i = 0; i < MAX_CHARCTER; i++){

		// ������
		if (!modRender[i].Init(paramDevice, SCREEN_WIDTH, SCREEN_HEIGHT)){ return false; }

	}// for

	// ����
	return true;

}// Init
//=============================================================================
// Update
//=============================================================================
void Live2DManager::Update(void){

	// ���f���̍X�V
	for (int i = 0; i < MAX_CHARCTER; i++){

		// �X�V
		mod[i].Update();

	}// for

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_R))
		mod[1].TalkStart();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_T))
		mod[1].TalkEnd();

}
//=============================================================================
// Draw
//=============================================================================
void Live2DManager::Draw(LPDIRECT3DDEVICE9 paramDevice){

	// �����_�[�X�e�[�g�̐ؑ�
	modRender[0].SetRenderTarget(paramDevice, 0);

	//�`��p������
	paramDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);

	// �`��
	mod[0].Draw(paramDevice);
	
	// �����_�[�X�e�[�g�̐ؑ�
	modRender[0].ReleaseRenderTarget(paramDevice, 0);

	// �����_�[�X�e�[�g�̐ؑ�
	modRender[1].SetRenderTarget(paramDevice, 0);

	//�`��p������
	paramDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 0, 255, 255), 1.0f, 0);

	// �`��
	mod[1].Draw(paramDevice);

	// �����_�[�X�e�[�g�̐ؑ�
	modRender[1].ReleaseRenderTarget(paramDevice, 0);

	// �����_�[�X�e�[�g�̐ؑ�
	modRender[2].SetRenderTarget(paramDevice, 0);

	//�`��p������
	paramDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 0, 255), 1.0f, 0);

	// �`��
	mod[2].Draw(paramDevice);

	// �����_�[�X�e�[�g�̐ؑ�
	modRender[2].ReleaseRenderTarget(paramDevice, 0);

}// Draw
//=============================================================================
// FunctionName: GetModTex
// Param: �ǂ̃L�����̃��f���̃e�N�X�`���ɂ��邩�̎��ʗp
// ReturnValue: �e�N�X�`���o�b�t�@
// Content: LIve2D���f�����`�悳�ꂽ�e�N�X�`���̎擾
//=============================================================================
LPDIRECT3DTEXTURE9 Live2DManager::GetModTex(int paramModState){

	return modRender[paramModState].GetTexBuff();

}// GetModTex
//=============================================================================
// FunctionName: SetMotion
// Param: �ǂ̃��f���̃��[�V�������Đ����邩�̎��ʎq
// Param: �ǂ̃��[�V�������Đ����邩�̎��ʎq
// ReturnValue: void
// Content: �w�肵�����f���̃��[�V�����̍Đ�
//			���Đ��I����ɑҋ@���[�V�����ɖ߂�܂�
//=============================================================================
void Live2DManager::SetMotion(int paramModState, int pramMotionState){

	// ���[�V�����̍Đ�
	mod[paramModState].SetMotion(pramMotionState);

}// SetMotion
// EOF