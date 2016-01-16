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
#include "../common.h"

//*****************************************************************************
// Macro
//*****************************************************************************
static const int MAX_LOAD_EX(20);
static const int MAX_LOAD_MOTION(20);

//*****************************************************************************
// Enum
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
	enum MODEL_TYPE
	{
		ROSA = 0,
		LILA,
		LICHT,
		NAVI,
	};
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
	bool Init(MODEL_TYPE paramType, LPDIRECT3DDEVICE9 paramDevice);

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

	//=============================================================================
	// FunctionName: TalkStart
	// Param: void
	// ReturnValue: void
	// Content: 口パクの更新
	//=============================================================================
	void TalkStart(){ talkStartFlg = true; };

	//=============================================================================
	// FunctionName: TalkStart
	// Param: void
	// ReturnValue: void
	// Content: 口パクの更新
	//=============================================================================
	void TalkEnd();


	//=============================================================================
	// Setter
	//=============================================================================
	void SetPos(D3DXVECTOR3 paramPos){ pos = paramPos; };
	void SetScl(D3DXVECTOR3 paramScl){ scl = paramScl; };

	//=============================================================================
	// Getter
	//=============================================================================
	D3DXVECTOR3 GetPos(){ return pos; };
	D3DXVECTOR3 GetScl(){ return scl; };

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
	AMotion* CreateMotion(const char* paramFilePath, const int paramCnt);

	//=============================================================================
	// FunctionName: CreateExMotion
	// Param: 読み込むファイルのパス
	// ReturnValue: ポインタ
	// Content: Live2Dの表情モーションの生成
	//=============================================================================
	L2DExpressionMotion* CreateExMotion(const char* paramFilePath, const int paramCnt);

	//=============================================================================
	// FunctionName: LoadTexture
	// Param: 読み込むテクスチャのパス
	// Param: DirectXデバイス
	// Param: テクスチャのインデックス
	// ReturnValue: 読み込み結果
	// Content: テクスチャの読み込み
	//=============================================================================
	bool LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum);

	//=============================================================================
	// FunctionName: LoadCharcterTexture
	// Param: モデル用のテクスチャのインデックス
	// Param: DirectXデバイス
	// ReturnValue: 読み込み結果
	// Content: テクスチャの読み込み
	//=============================================================================
	bool LoadCharcterTexture(MODEL_TYPE paramtype, LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: CreateCharcterExMotion
	// Param: 表情モーション用のインデックス
	// ReturnValue: 読み込み結果
	// Content: キャラ別の表情モーションの生成
	//=============================================================================
	bool CreateCharcterExMotion(MODEL_TYPE paramtype);

	//=============================================================================
	// FunctionName: CreateCharctexMotion
	// Param: モーション用のインデックス
	// ReturnValue: 読み込み結果
	// Content: キャラ別のモーションの生成
	//=============================================================================
	bool CreateCharcterMotion(MODEL_TYPE paramtype);

	//=============================================================================
	// FunctionName: UpdateTalk
	// Param: void
	// ReturnValue: void
	// Content: 口パクの更新
	//=============================================================================
	void UpdateTalk();

	//=============================================================================
	// FunctionName: EsasingNone
	// Param: 最小値
	// Param: 最大値
	// Param: 係数用の時間
	// ReturnValue: 補間結果の数値
	// Content: イージング
	//=============================================================================
	float EsasingNone(float paramMin, float paramMax, float paramTime);

	LPDIRECT3DTEXTURE9 tex[3];

	l2d_int64 startTimeMSec;
	Live2DModelD3D* live2DModelPtr;
	L2DEyeBlink* eyeBlinkPtr;
	L2DPose* posePtr;
	L2DPhysics*	physicsPtr;
	L2DExpressionMotion* exMotionPtr[MAX_LOAD_EX];
	AMotion* motionPtr[MAX_LOAD_MOTION];
	L2DMotionManager motionMgr;
	MODEL_TYPE type;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scl;
	int createMotionCnt;
	int createExMotionCnt;
	bool talkStartFlg;
	float mouthCoff;

	SHADER_SET				shader;


};

#endif// _LIVE2D_MODEL_H_