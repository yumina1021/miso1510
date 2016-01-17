//============================================================================
// FileName: gameEntity.cpp
// Author: SHUN SAKAI
// Content: ゲーム中に存在するオブジェクト
//============================================================================
//*****************************************************************************
// Include
//*****************************************************************************
#include "Live2DModel.h"
#include "../administer/finalize.hpp"
#include "../administer/entityFactory.hpp"
#include "../administer/Input.h"
#include "../exten_common.h"

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
// GlobalArea
//*****************************************************************************
const char* USE_MODEL[] = {
	"data\\res\\haru\\haru_01.moc",
	"data\\res\\haru\\haru_02.moc",
	"data\\res\\haru\\haru_01.moc",
	NULL,
};
const char* POSE[] = {
	"data\\res\\haru\\haru.pose.json",
	"data\\res\\haru\\haru.pose.json",
	"data\\res\\haru\\haru.pose.json",
	NULL,
};
const char* PHYSICS[] = {
	"data\\res\\haru\\haru.physics.json",
	"data\\res\\haru\\haru.physics.json",
	"data\\res\\haru\\haru.physics.json",
	NULL,
};
const LPCWSTR TEXTURES1[] = {
	L"data\\res\\haru\\haru_01.1024\\texture_00.png",
	L"data\\res\\haru\\haru_01.1024\\texture_01.png",
	L"data\\res\\haru\\haru_01.1024\\texture_02.png",
	NULL,
};

const LPCWSTR TEXTURES2[] = {
	L"data\\res\\haru\\haru_02.1024\\texture_00.png",
	L"data\\res\\haru\\haru_02.1024\\texture_01.png",
	L"data\\res\\haru\\haru_02.1024\\texture_02.png",
	NULL,
};
const LPCWSTR TEXTURES3[] = {
	L"data\\res\\haru\\haru_01.1024\\texture_00.png",
	L"data\\res\\haru\\haru_01.1024\\texture_01.png",
	L"data\\res\\haru\\haru_01.1024\\texture_02.png",
	NULL,
};
const char* EX_MOTION1[] = {
	"data\\res\\haru\\expressions\\f01.exp.json",
	"data\\res\\haru\\expressions\\f02.exp.json",
	"data\\res\\haru\\expressions\\f03.exp.json",
	"data\\res\\haru\\expressions\\f04.exp.json",
	"data\\res\\haru\\expressions\\f05.exp.json",
	"data\\res\\haru\\expressions\\f06.exp.json",
	"data\\res\\haru\\expressions\\f07.exp.json",
	"data\\res\\haru\\expressions\\f08.exp.json",
	NULL,
};

const char* EX_MOTION2[] = {
	"data\\res\\haru\\expressions\\f01.exp.json",
	"data\\res\\haru\\expressions\\f02.exp.json",
	"data\\res\\haru\\expressions\\f03.exp.json",
	"data\\res\\haru\\expressions\\f04.exp.json",
	"data\\res\\haru\\expressions\\f05.exp.json",
	"data\\res\\haru\\expressions\\f06.exp.json",
	"data\\res\\haru\\expressions\\f07.exp.json",
	"data\\res\\haru\\expressions\\f08.exp.json",
	NULL,
};
const char* EX_MOTION3[] = {
	"data\\res\\haru\\expressions\\f01.exp.json",
	"data\\res\\haru\\expressions\\f02.exp.json",
	"data\\res\\haru\\expressions\\f03.exp.json",
	"data\\res\\haru\\expressions\\f04.exp.json",
	"data\\res\\haru\\expressions\\f05.exp.json",
	"data\\res\\haru\\expressions\\f06.exp.json",
	"data\\res\\haru\\expressions\\f07.exp.json",
	"data\\res\\haru\\expressions\\f08.exp.json",
	NULL,
};
const char* MOTION1[] = {
	"data\\res\\haru\\motions\\idle_00.mtn",
	"data\\res\\haru\\motions\\idle_01.mtn",
	"data\\res\\haru\\motions\\idle_02.mtn",
	"data\\res\\haru\\motions\\tapBody_01.mtn",
	"data\\res\\haru\\motions\\tapBody_02.mtn",
	"data\\res\\haru\\motions\\tapBody_03.mtn",
	"data\\res\\haru\\motions\\tapBody_04.mtn",
	"data\\res\\haru\\motions\\tapBody_05.mtn",
	"data\\res\\haru\\motions\\tapBody_06.mtn",
	"data\\res\\haru\\motions\\tapBody_07.mtn",
	"data\\res\\haru\\motions\\tapBody_08.mtn",
	"data\\res\\haru\\motions\\tapBody_09.mtn",
	NULL,
};

const char* MOTION2[] = {
	"data\\res\\haru\\motions\\idle_00.mtn",
	"data\\res\\haru\\motions\\idle_01.mtn",
	"data\\res\\haru\\motions\\idle_02.mtn",
	"data\\res\\haru\\motions\\tapBody_01.mtn",
	"data\\res\\haru\\motions\\tapBody_02.mtn",
	"data\\res\\haru\\motions\\tapBody_03.mtn",
	"data\\res\\haru\\motions\\tapBody_04.mtn",
	"data\\res\\haru\\motions\\tapBody_05.mtn",
	"data\\res\\haru\\motions\\tapBody_06.mtn",
	"data\\res\\haru\\motions\\tapBody_07.mtn",
	"data\\res\\haru\\motions\\tapBody_08.mtn",
	"data\\res\\haru\\motions\\tapBody_09.mtn",
	NULL,
};
const char* MOTION3[] = {
	"data\\res\\haru\\motions\\idle_00.mtn",
	"data\\res\\haru\\motions\\idle_01.mtn",
	"data\\res\\haru\\motions\\idle_02.mtn",
	"data\\res\\haru\\motions\\tapBody_01.mtn",
	"data\\res\\haru\\motions\\tapBody_02.mtn",
	"data\\res\\haru\\motions\\tapBody_03.mtn",
	"data\\res\\haru\\motions\\tapBody_04.mtn",
	"data\\res\\haru\\motions\\tapBody_05.mtn",
	"data\\res\\haru\\motions\\tapBody_06.mtn",
	"data\\res\\haru\\motions\\tapBody_07.mtn",
	"data\\res\\haru\\motions\\tapBody_08.mtn",
	"data\\res\\haru\\motions\\tapBody_09.mtn",
	NULL,
};
//=============================================================================
// Constructor
//=============================================================================
Live2DModel::Live2DModel():
startTimeMSec(0),
live2DModelPtr(nullptr),
eyeBlinkPtr(nullptr),
posePtr(nullptr),
physicsPtr(nullptr),
pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
scl(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
createMotionCnt(0),
createExMotionCnt(0),
talkStartFlg(false),
mouthCoff(0.0f),
drawFlg(false){

	// 開始時間の取得
	startTimeMSec = live2d::UtSystem::getUserTimeMSec();

}// Live2DModel
//=============================================================================
// Destructor
//=============================================================================
Live2DModel::~Live2DModel(){

	
	SafeDelete(live2DModelPtr);
	SafeDelete(eyeBlinkPtr);
	SafeDelete(posePtr);
	SafeDelete(physicsPtr);


	for (int i = 0; i < createMotionCnt; i++)
	{
		SafeDelete(motionPtr[i]);

	}
	for (int i = 0; i < createExMotionCnt; i++)
	{
		SafeDelete(exMotionPtr[i]);

	}

	for (int i = 0; i < 3; i++)
	{

		//SafeRelease(tex[i]);

	}

}// ~Live2DModel
//=============================================================================
// Init
//=============================================================================
bool Live2DModel::Init(MODEL_TYPE paramType, LPDIRECT3DDEVICE9 paramDevice)
{

	// モデルのロード
	live2DModelPtr = Live2DModelD3D::loadModel(USE_MODEL[paramType]);
	
	// キャラのテクスチャのロード
	LoadCharcterTexture(paramType, paramDevice);

	// 目パチ
	eyeBlinkPtr = Factory::Create<L2DEyeBlink>();

	// ポーズ
	posePtr = CreatePose(POSE[paramType]);

	// 物理演算（髪）
	physicsPtr = CreatePysics(PHYSICS[paramType]);

	// 待機モーション
	CreateCharcterMotion(paramType);

	// 表情
	CreateCharcterExMotion(paramType);

	// 成功
	return true;

}// Init
//=============================================================================
// FunctionName: LoadTexture
// Param: 読み込むテクスチャのパス
// ReturnValue: 読み込み結果
// Content: テクスチャの読み込み
//=============================================================================
bool Live2DModel::LoadCharcterTexture(MODEL_TYPE paramtype, LPDIRECT3DDEVICE9 paramDevice){

	switch (paramtype)
	{
	case ROSA:

		// テクスチャのロード
		for (int i = 0; i < 10; i++){
			if (!TEXTURES1[i]) break;

			if (!LoadTexture(TEXTURES1[i], paramDevice, i)){ break; };

		}// for

		break;
	case LILA:
		// テクスチャのロード
		for (int i = 0; i < 10; i++){
			if (!TEXTURES2[i]) break;

			if (!LoadTexture(TEXTURES2[i], paramDevice, i)){ break; };

		}// for

		break;
	case LICHT:
		// テクスチャのロード
		for (int i = 0; i < 10; i++){
			if (!TEXTURES3[i]) break;

			if (!LoadTexture(TEXTURES3[i], paramDevice, i)){ break; };

		}// for

		break;
	default:
		break;
	}

	return true;

}// LoadCharcterTexture
//=============================================================================
// FunctionName: LoadTexture
//=============================================================================
bool Live2DModel::LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum){

	// 変数宣言
	bool tmpFlg = false;

	// テクスチャ画像をDirextXでの表示用に変換
	if (FAILED(D3DXCreateTextureFromFileExW(paramDevice
		, paramFilePath
		, 0	//width 
		, 0	//height
		, 0	//mipmap //( 0なら完全なミップマップチェーン）
		, 0	//Usage
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED
		, D3DX_FILTER_LINEAR
		, D3DX_FILTER_BOX
		, 0
		, NULL
		, NULL
		, &tex[paramTexNum]))){

	}else{

		// 変換が成功したらセット
		live2DModelPtr->setTexture(paramTexNum, tex[paramTexNum]);
		tmpFlg = true;

	}

	// 結果を返す
	return tmpFlg;


}// LoadTexture
//=============================================================================
// CreateCharcterExMotion
//=============================================================================
bool Live2DModel::CreateCharcterExMotion(MODEL_TYPE paramtype){

	// 変数宣言
	int cnt = 0;
	switch (paramtype){
	case ROSA:

		// テクスチャのロード
		for (cnt = 0; cnt < MAX_LOAD_EX; cnt++){
			if (!EX_MOTION1[cnt]) break;

			exMotionPtr[cnt] = CreateExMotion(EX_MOTION1[cnt], cnt);

		}// for

		break;
	case LILA:
		// テクスチャのロード
		for (cnt = 0; cnt < MAX_LOAD_EX; cnt++){
			if (!EX_MOTION2[cnt]) break;

			exMotionPtr[cnt] = CreateExMotion(EX_MOTION1[cnt], cnt);

		}// for

		break;
	case LICHT:
		// テクスチャのロード
		for (cnt = 0; cnt < MAX_LOAD_EX; cnt++){
			if (!EX_MOTION3[cnt]) break;

			exMotionPtr[cnt] = CreateExMotion(EX_MOTION1[cnt], cnt);

		}// for

		break;
	default:
		break;
	}

	createExMotionCnt = cnt;

	return true;

}// CreateCharcterExMotion
//=============================================================================
// CreateCharcterExMotion
//=============================================================================
bool Live2DModel::CreateCharcterMotion(MODEL_TYPE paramtype){

	// 変数宣言
	int cnt = 0;

	switch (paramtype){
	case ROSA:

		// テクスチャのロード
		for (cnt = 0; cnt < MAX_LOAD_MOTION; cnt++){
			if (!MOTION1[cnt]) break;

			motionPtr[cnt] = CreateMotion(MOTION1[cnt], cnt);

		}// for

		break;
	case LILA:
		// テクスチャのロード
		for (cnt = 0; cnt < MAX_LOAD_MOTION; cnt++){
			if (!MOTION2[cnt]) break;

			motionPtr[cnt] = CreateMotion(MOTION2[cnt], cnt);

		}// for

		break;
	case LICHT:
		// テクスチャのロード
		for (cnt = 0; cnt < MAX_LOAD_MOTION; cnt++){
			if (!MOTION3[cnt]) break;

			motionPtr[cnt] = CreateMotion(MOTION3[cnt], cnt);

		}// for

		break;
	default:
		break;
	}

	// 生成した数を記録
	createMotionCnt = cnt;

	return true;

}// CreateCharcterExMotion
//=============================================================================
// CreatePose
//=============================================================================
L2DPose* Live2DModel::CreatePose(const char* paramFilePath){

	// 変数宣言
	unsigned char* buf = nullptr;
	int size = 0;
	L2DPose* tmpPosePtr = nullptr;

	// ファイルのロード
	buf = LoadFile(paramFilePath, size);

	// ポーズの読み込み
	tmpPosePtr = L2DPose::load(buf, (int)size);

	// 取得時に確保したバッファの開放
	SafeDeleteArray(buf);

	// 生成したポーズを返す
	return tmpPosePtr;

}// CreatePose
//=============================================================================
// CreatePysics
//=============================================================================
L2DPhysics* Live2DModel::CreatePysics(const char* paramFilePath){

	// 変数宣言
	unsigned char* buf = nullptr;
	int size = 0;
	L2DPhysics*	tmpPhysicsPtr = nullptr;

	// ファイルのロード
	buf = LoadFile(paramFilePath, size);

	// ポーズの読み込み
	tmpPhysicsPtr = L2DPhysics::load(buf, (int)size);

	// 取得時に確保したバッファの開放
	SafeDeleteArray(buf);

	// 生成した物理演算を返す
	return tmpPhysicsPtr;

}// CreatePysics
//=============================================================================
// CreateMotion
//=============================================================================
AMotion* Live2DModel::CreateMotion(const char* paramFilePath, const int paramCnt){

	// 変数宣言
	unsigned char* buf = nullptr;
	int size = 0;
	AMotion* tmpMotionPtr = nullptr;

	// ファイルのロード
	buf = LoadFile(paramFilePath, size);

	// ポーズの読み込み
	tmpMotionPtr = Live2DMotion::loadMotion(buf, (int)size);

	// 取得時に確保したバッファの開放
	SafeDeleteArray(buf);

	// 生成したモーションを返す
	return tmpMotionPtr;

}// CreateMotion
//=============================================================================
// CreateMotion
//=============================================================================
L2DExpressionMotion* Live2DModel::CreateExMotion(const char* paramFilePath, const int paramCnt){

	// 変数宣言
	unsigned char* buf = nullptr;
	int size = 0;
	L2DExpressionMotion* tmpExtionPtr = nullptr;

	// ファイルのロード
	buf = LoadFile(paramFilePath, size);

	// ポーズの読み込み
	tmpExtionPtr = L2DExpressionMotion::loadJson(buf, (int)size);

	// 取得時に確保したバッファの開放
	SafeDeleteArray(buf);

	// 生成した表情モーションを返す
	return tmpExtionPtr;

}// CreateMotion
//=============================================================================
// LoadFile
//=============================================================================
unsigned char* Live2DModel::LoadFile(const char* paramFilePath, int &refFileSize){

	// 変数宣言
	FILE *fp = nullptr;
	unsigned char* buf = nullptr;

	// ファイルオープン
	fopen_s(&fp, paramFilePath, "rb");

	// サイズを取得
	fseek(fp, 0, SEEK_END);
	refFileSize = ftell(fp);

	// ファイルの読み込み
	buf = Factory::CreateArray<unsigned char>(refFileSize);
	fseek(fp, 0, SEEK_SET);

	// 読み込んだ大きさが一致しない場合
	if ((int)fread(buf, sizeof(char), refFileSize, fp) != refFileSize){

		// メッセージBOXの表示
		MessageBox(NULL, "ファイルの読み込みで失敗なのん", "失敗", MB_OK);

		// 確保したメモリの開放
		SafeDeleteArray(buf);

	}// if

	// ファイルクローズ
	fclose(fp);

	// 値を返す
	return buf;

}// LoadFile
//=============================================================================
// Update
//=============================================================================
void Live2DModel::Update(){

	// 目パチ
	eyeBlinkPtr->setParam(live2DModelPtr);

	// モーションの更新
	UpdateMotion();

	// 呼吸など
	LDint64	 timeMSec = live2d::UtSystem::getUserTimeMSec() - startTimeMSec;
	double t = (timeMSec / 1000.0) * 2 * 3.14159;//2*Pi*t
	live2DModelPtr->setParamFloat("PARAM_BREATH", (float)(0.5f + 0.5f * sin(t / 3.2345)), 1);// 0~1 まで周期的に設定。モーションを上書き。

	// 物理演算でパラメータ更新
	if (physicsPtr)
		physicsPtr->updateParam(live2DModelPtr);

	// ポーズの設定
	if (posePtr)
		posePtr->updateParam(live2DModelPtr);

	// モーションの更新
	motionMgr.updateParam(live2DModelPtr);

	// 口パク
	if (talkStartFlg)
		UpdateTalk();

	// モデルの更新
	live2DModelPtr->update();

}// Update
//=============================================================================
// Draw
//=============================================================================
void Live2DModel::Draw(LPDIRECT3DDEVICE9 paramDevice)
{

	// 描画の前に行列の準備
	SetupMatrix(paramDevice);

	// モデルの描画
	DrawMod(paramDevice);

	// レンダリングステートパラメータの設定
	paramDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	paramDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	paramDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	paramDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	paramDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	paramDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	paramDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	paramDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	paramDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートパラメータの設定
	paramDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	paramDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	paramDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
}
//=============================================================================
// DrawMod
//=============================================================================
void Live2DModel::DrawMod(LPDIRECT3DDEVICE9 paramDevice){


	live2DModelPtr->setDevice(paramDevice);
	live2DModelPtr->draw();

	D3DXMATRIXA16 Identity;
	D3DXMatrixIdentity(&Identity);
	paramDevice->SetTransform(D3DTS_PROJECTION, &Identity);
	paramDevice->SetTransform(D3DTS_VIEW, &Identity);
	paramDevice->SetTransform(D3DTS_WORLD, &Identity);

}
//=============================================================================
// SetupMatrix
//=============================================================================
void Live2DModel::SetupMatrix(LPDIRECT3DDEVICE9 paramDevice){

	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIX Ortho2D;
	D3DXMATRIX Identity;

	int w, h;
	w = SCREEN_WIDTH;
	h = SCREEN_HEIGHT;

	float raito = (float)(h / w);

	float modelWidth = live2DModelPtr->getModelImpl()->getCanvasWidth();
	float modelHeight = live2DModelPtr->getModelImpl()->getCanvasHeight();

	D3DXMatrixOrthoLH(&Ortho2D, modelHeight, -modelHeight * h / w, -1.0f, 1.0f);

	D3DXMatrixIdentity(&Identity);

	paramDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	paramDevice->SetTransform(D3DTS_VIEW, &Identity);
	paramDevice->SetTransform(D3DTS_WORLD, &Identity);


	// --- 座標変換
	// 現在のLive2Dモデルは、画像のように下向きに(0,0,w,h)に配置される
	// センタリングと上下逆転が必要
	D3DXMATRIXA16 world, scale, trans;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trans);


	D3DXMatrixTranslation(&trans, -modelWidth / 2, -modelHeight / 2 + 600, 0.0f);
	D3DXMatrixScaling(&scale, scl.x, scl.y, 1.0f);
	world = trans *world * scale;

	paramDevice->SetTransform(D3DTS_WORLD, &world);

}// SetupMatrix
//=============================================================================
// EsasingNone
//=============================================================================
float Live2DModel::EsasingNone(float paramMin, float paramMax, float paramTime){

	float tmpRet(0.0f);

	if (paramTime < 0.5f){

		// 二次曲線
		tmpRet = (2.0 * paramTime) * (2.0 * paramTime) * 0.5f;

	}else{

		tmpRet = -((2.0 * paramTime - 2.0f) * (2.0 * paramTime - 2.0f)) * 0.5f + 1.0f;

	}// else

	return (paramMax - paramMin) * tmpRet + paramMin;

}// EsasingNone
//=============================================================================
// UpdateTalk
//=============================================================================
void Live2DModel::UpdateTalk(){

	live2DModelPtr->setParamFloat("PARAM_MOUTH_OPEN_Y", EsasingNone(0.0f, 0.8f, mouthCoff), 0.8f);

	if (mouthCoff > 1.0f)
	{
		mouthCoff = 0.0f;

	}else{

		mouthCoff += 0.05f;

	}// else


}// UpdateTalk
//=============================================================================
// TalkStart
//=============================================================================
void Live2DModel::TalkEnd(){

	// 口パクしている場合のみ停止
	if (!talkStartFlg){ return; }

	// 各種値の初期化
	talkStartFlg = false;
	mouthCoff = 0.0f;

	// 口パクの更新
	UpdateTalk();

}// TalkEnd
//=============================================================================
// TalkStart
//=============================================================================
void Live2DModel::TalkStart(){

	// 口パクしていない場合のみ開始
	if (talkStartFlg){ return; }

	// 口パク開始
	talkStartFlg = true;

}// TalkStart
//=============================================================================
// SetMotion
//=============================================================================
void Live2DModel::SetMotion(int pramMotionState){

	motionMgr.startMotionPrio(motionPtr[pramMotionState], false, PRIORITY_NORMAL);

}// SetMotion
//=============================================================================
// SetExMotion
//=============================================================================
void Live2DModel::SetExMotion(int pramMotionState){

	exMotionMgr.startMotion(exMotionPtr[pramMotionState], false);

}// SetMotion
//=============================================================================
// UpdateMotion
//=============================================================================
void Live2DModel::UpdateMotion(){

	// 前回セーブされた状態をロード
	live2DModelPtr->loadParam();

	// モーションが終了していたら
	if (motionMgr.isFinished()){

		// モーションの再生がない場合、待機モーションの中からランダムで再生する
		//startRandomMotion(MOTION_GROUP_IDLE, PRIORITY_IDLE);
		motionMgr.startMotionPrio(motionPtr[0], false, PRIORITY_IDLE);

	}else{

		motionMgr.updateParam(live2DModelPtr);// モーションを更新

	}// else

	// 状態を保存
	live2DModelPtr->saveParam();

}// UpdateMotion
// EOF