//============================================================================
// FileName: gameEntity.cpp
// Author: SHUN SAKAI
// Content: ゲーム中に存在するオブジェクト
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

#include <stdio.h>

//*****************************************************************************
// Macro
//*****************************************************************************
const float PI(3.14f);

// モーションの優先度定数
static const int PRIORITY_NONE = 0;
static const int PRIORITY_IDLE = 1;
static const int PRIORITY_NORMAL = 2;
static const int PRIORITY_FORCE = 3;

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

}// Live2DManager
//=============================================================================
// Destructor
//=============================================================================
Live2DManager::~Live2DManager(){

	SafeDelete(mod);
	Live2D::dispose();
}// ~Live2DManager
//=============================================================================
// Init
//=============================================================================
bool Live2DManager::Init(LPDIRECT3DDEVICE9 paramDevice){
	
	// Live2Dの初期化
	Live2D::init();

	// 生成
	mod = Factory::Create<Live2DModel>();

	// 初期化
	mod->Init(Live2DModel::MODEL_TYPE::ROSA, paramDevice);
	mod->SetPos(D3DXVECTOR3(-500.0f, -500.0f, 0.0f));
	mod->SetScl(D3DXVECTOR3(0.7f, 0.7f, 1.0f));

	// 成功
	return S_OK;

}// Init
//=============================================================================
// Update
//=============================================================================
void Live2DManager::Update(void){

	mod->Update();

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_R))
		mod->TalkStart();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_T))
		mod->TalkEnd();

}
//=============================================================================
// Draw
//=============================================================================
void Live2DManager::Draw(LPDIRECT3DDEVICE9 paramDevice){

	// 描画
	mod->Draw(paramDevice);

}
// EOF