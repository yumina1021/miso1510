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
#include "renderTarget.h"

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

static const int MAX_CHARCTER(3);
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

	// Live2Dの初期化
	Live2D::init();

	// 生成
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
	

	// 初期化
	mod[Live2DModel::MODEL_TYPE::ROSA].Init(Live2DModel::MODEL_TYPE::ROSA, paramDevice);
	mod[Live2DModel::MODEL_TYPE::ROSA].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -200.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::ROSA].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// 初期化
	mod[Live2DModel::MODEL_TYPE::LILA].Init(Live2DModel::MODEL_TYPE::LILA, paramDevice);
	mod[Live2DModel::MODEL_TYPE::LILA].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -600.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::LILA].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// 初期化
	mod[Live2DModel::MODEL_TYPE::LICHT].Init(Live2DModel::MODEL_TYPE::LICHT, paramDevice);
	mod[Live2DModel::MODEL_TYPE::LICHT].SetPos(D3DXVECTOR3(-SCREEN_WIDTH / 2, -600.0f, 0.0f));
	mod[Live2DModel::MODEL_TYPE::LICHT].SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	// Live2Dモデル用のレンダーターゲット
	for (int i = 0; i < MAX_CHARCTER; i++){

		// 初期化
		if (!modRender[i].Init(paramDevice, SCREEN_WIDTH, SCREEN_HEIGHT)){ return false; }

	}// for

	// 成功
	return true;

}// Init
//=============================================================================
// Update
//=============================================================================
void Live2DManager::Update(void){

	// モデルの更新
	for (int i = 0; i < MAX_CHARCTER; i++){

		// 更新
		mod[i].Update();

	}// for

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_R))
		mod[1].TalkStart();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_T))
		mod[1].TalkEnd();

}
//=============================================================================
// Draw
//=============================================================================
void Live2DManager::Draw(LPDIRECT3DDEVICE9 paramDevice){

	for (int i = 0; i < MAX_CHARCTER; i++){

		if (mod[i].GetDrawFlg()){

			// レンダーステートの切替
			modRender[i].SetRenderTarget(paramDevice, 0);

			//描画用初期化
			paramDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);

			// 描画
			mod[i].Draw(paramDevice);

			// レンダーステートの切替
			modRender[i].ReleaseRenderTarget(paramDevice, 0);

		}// if

	}// for

}// Draw
//=============================================================================
// FunctionName: GetModTex
// Param: どのキャラのモデルのテクスチャにするかの識別用
// ReturnValue: テクスチャバッファ
// Content: LIve2Dモデルが描画されたテクスチャの取得
//=============================================================================
LPDIRECT3DTEXTURE9 Live2DManager::GetModTex(int paramModState){

	return modRender[paramModState].GetTexBuff();

}// GetModTex
//=============================================================================
// FunctionName: SetMotion
// Param: どのモデルのモーションを再生するかの識別子
// Param: どのモーションを再生するかの識別子
// ReturnValue: void
// Content: 指定したモデルのモーションの再生
//			※再生終了後に待機モーションに戻ります
//=============================================================================
void Live2DManager::SetMotion(int paramModState, int pramMotionState){

	// モーションの再生
	mod[paramModState].SetMotion(pramMotionState);

}// SetMotion
//=============================================================================
// FunctionName: SetExMotion
// Param: どのモデルの表情モーションを再生するかの識別子
// Param: どのモデルの表情モーションを再生するかの識別子
// ReturnValue: void
// Content: 指定した表情モデルのモーションの再生
//			※再生終了後に待機モーションに戻ります
//=============================================================================
void Live2DManager::SetExMotion(int paramModState, int pramExMotionState){

	// 表情モーションの再生
	mod[paramModState].SetExMotion(pramExMotionState);

}// SetExMotion
//=============================================================================
// FunctionName: DrawStart
// Param: どのモデルの描画をするかの識別子
// ReturnValue: void
// Content: この関数を呼び出した次のフレームから描画開始
//=============================================================================
void Live2DManager::SetDrawStart(int paramModState){

	// 描画開始
	mod[paramModState].DrawStart();

}// DrawStart
//=============================================================================
// FunctionName: DrawEnd
// Param: void
// ReturnValue: void
// Content: この関数を呼び出した次のフレームから描画終了
//=============================================================================
void Live2DManager::SetDrawEnd(int paramModState){

	// 描画終了
	mod[paramModState].DrawEnd();

}// DrawEnd
// EOF