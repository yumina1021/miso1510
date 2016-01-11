//=============================================================================
// FileName : Live2DModel.h
// Author：SHUN SAKAI
// 内容：ポリゴン関連の処理
//=============================================================================
#ifndef _LIVE_2D_MODEL_H_
#define _LIVE_2D_MODEL_H_
//*****************************************************************************
// Include
//*****************************************************************************
#include "include\Live2D.h"
#include "include\Live2DModelD3D.h"
#include "include\util/UtSystem.h"
#include "L2DEyeBlink.h"
#include "L2DPose.h"
#include "L2DPhysics.h"
#include "L2DExpressionMotion.h"
#include "L2DMotionManager.h"
#include "include\motion\Live2DMotion.h"

//*****************************************************************************
// Macro
//*****************************************************************************

//*****************************************************************************
// NameSpace
//*****************************************************************************
using namespace live2d;
using namespace live2d::framework;

//*****************************************************************************
// class
//*****************************************************************************
class Live2DModel
{
public:
	//=============================================================================
	// FunctionName: Constructor
	// Param: void
	// ReturnValue: void
	// Content: 全てのメンバ変数はここで初期化をしておくこと
	//=============================================================================
	Live2DModel();
	//=============================================================================
	// FunctionName: Destructor
	// Param: void
	// ReturnValue: void
	// Content: 各種動的に確保したバッファなどの開放処理を行う
	//=============================================================================
	~Live2DModel();

	//=============================================================================
	// FuncName: Init
	// ParamValue: DirectXデバイス
	// Content: 初期化
	//=============================================================================
	bool Init(LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: Update
	// Param: なし
	// ReturnValue: void
	// Content: 更新
	//=============================================================================
	void Update();

	//=============================================================================
	// FunctionName: Draw
	// Param: DirectXデバイス
	// ReturnValue: void
	// Content: 描画
	//=============================================================================
	void Draw(LPDIRECT3DDEVICE9 paramDevice);

private:
	//=============================================================================
	// FunctionName: SetupMatrix
	// Param: DirectXデバイス
	// ReturnValue: void
	// Content: 描画に必要な行列の準備
	//=============================================================================
	void SetupMatrix(LPDIRECT3DDEVICE9 paramDevice);// 行列の準備

	//=============================================================================
	// FunctionName: DrawMod
	// Param: DirectXデバイス
	// ReturnValue: void
	// Content: Live2Dモデルの描画
	//=============================================================================
	void DrawMod(LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: LoadFile
	// Param: 読み込むファイルのパス
	// Param: 取得したファイルのサイズ（参照で呼び出した関数に渡す）
	// ReturnValue: 読み込んだファイルの先頭アドレス
	// Content: Live2D関係のファイルの読み込み
	//=============================================================================
	unsigned char* LoadFile(const char* paramFilePath, int &refFileSize);

	//=============================================================================
	// FunctionName: CreatePose
	// Param: 読み込むファイルのパス
	// ReturnValue: 生成結果
	// Content: Live2Dのポーズの生成
	//=============================================================================
	L2DPose* CreatePose(const char* paramFilePath);

	//=============================================================================
	// FunctionName: CreatePose
	// Param: 読み込むファイルのパス
	// ReturnValue: 生成結果
	// Content: Live2Dのポーズの生成
	//=============================================================================
	L2DPhysics* CreatePysics(const char* paramFilePath);

	//=============================================================================
	// FunctionName: CreatePose
	// Param: 読み込むファイルのパス
	// ReturnValue: モーションのポインタ
	// Content: Live2Dのモーションの生成
	//=============================================================================
	AMotion* CreateMotion(const char* paramFilePath);

	//=============================================================================
	// FunctionName: CreateExMotion
	// Param: 読み込むファイルのパス
	// ReturnValue: ポインタ
	// Content: Live2Dの表情モーションの生成
	//=============================================================================
	L2DExpressionMotion* CreateExMotion(const char* paramFilePath);

	//=============================================================================
	// FunctionName: LoadTexture
	// Param: 読み込むテクスチャのパス
	// ReturnValue: 読み込み結果
	// Content: テクスチャの読み込み
	//=============================================================================
	bool LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum);

	l2d_int64 startTimeMSec;
	Live2DModelD3D* live2DModel;
	L2DEyeBlink* eyeBlink;
	L2DPose* pose;
	L2DPhysics*	physics;
	L2DExpressionMotion* exMotion1;
	L2DExpressionMotion* exMotion2;
	L2DMotionManager* motionMgr;
	AMotion* motion1;
	AMotion* motion2;
};

#endif// _LIVE2D_MODEL_H_