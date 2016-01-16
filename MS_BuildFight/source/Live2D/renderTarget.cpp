//============================================================================
// File: renderTarget.cpp
// Author: SHUN SAKAI
// Content: リソース管理
//============================================================================
//*****************************************************************************
// Include
//*****************************************************************************
#include "renderTarget.h"
#include "../Resource/texture.h"
#include "../Utility/factory.hpp"
#include "../Utility/finalize.hpp"

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
// Content: コンストラクタであり引数のプライオリティで描画順番が決まる
//			全てのメンバ変数はここで初期化をしておくこと
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
// Content: 各種動的に確保したバッファなどの開放処理を行う
//=============================================================================
RenderTarget::~RenderTarget(){

	SafeRelease(surface);

}// ~RenderTarget
//=============================================================================
// FunctionName: Init
// Param: デバイス
// Param: 幅
// Param: 高さ
// ReturnValue: 成功したかどうか
// Content: 初期化
//=============================================================================
bool RenderTarget::Init(LPDIRECT3DDEVICE9 paramDevice9,
	float paramWidth,
	float paramHeight){


	if (FAILED(paramDevice9->CreateTexture((UINT)paramWidth,
											(UINT)paramWidth,
											1,
											D3DUSAGE_RENDERTARGET,
											D3DFMT_A32B32G32R32F,
											D3DPOOL_DEFAULT,
											&texBuff,
											NULL))){
#ifdef _DEBUG

		//メッセージボックスで出力
		MessageBox(NULL, "テクスチャの生成に失敗したのん", "失敗", MB_OK);

#endif

		return false;
	}// if


	// サーフェース周りの設定
	if (FAILED(texBuff->GetSurfaceLevel(0, &surface))){

#ifdef _DEBUG
		// windowsのメッセージを表示
		MessageBox(NULL, "レンダーターゲット用のテクスチャの生成に失敗したのん", "エラー", MB_OK);
#endif
		return false; 
	}

	return true;

}// Init
//=============================================================================
// FunctionName: SetRenderTarget
// Param: デバイス
// Param: 幅
// Param: 高さ
// ReturnValue: 成功したかどうか
// Content: 初期化
//=============================================================================
bool RenderTarget::SetRenderTarget(LPDIRECT3DDEVICE9 paramDevice9, DWORD paramSetIndex){

	if (FAILED(paramDevice9->SetRenderTarget(paramSetIndex, surface))){ return false; }

	return true;

}// SetRenderTarget
//=============================================================================
// FunctionName: SetRenderTarget
// Param: デバイス
// Param: 幅
// Param: 高さ
// ReturnValue: 成功したかどうか
// Content: 初期化
//=============================================================================
bool RenderTarget::ReleaseRenderTarget(LPDIRECT3DDEVICE9 paramDevice9, DWORD paramSetIndex){

	if (FAILED(paramDevice9->SetRenderTarget(paramSetIndex, nullptr))){ return false; }

	return true;

}// SetRenderTarget
//=============================================================================
// FunctionName: SetRenderTarget
// Param: デバイス
// Param: 幅
// Param: 高さ
// ReturnValue: 成功したかどうか
// Content: 初期化
//=============================================================================
bool RenderTarget::GetRenderTarget(LPDIRECT3DDEVICE9 paramDevice9, DWORD paramSetIndex){

	if (FAILED(paramDevice9->GetRenderTarget(paramSetIndex, &surface))){ return false; }

	return true;

}// SetRenderTarget
LPDIRECT3DTEXTURE9 RenderTarget::GetTexBuff(){
	return texBuff;
}
// EOF