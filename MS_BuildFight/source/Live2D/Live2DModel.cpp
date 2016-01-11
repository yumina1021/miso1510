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
const LPCWSTR TEXTURES[] = {
	L"data\\res\\haru\\haru_01.1024\\texture_00.png",
	L"data\\res\\haru\\haru_01.1024\\texture_01.png",
	L"data\\res\\haru\\haru_01.1024\\texture_02.png",
	NULL,
};

//=============================================================================
// Constructor
//=============================================================================
Live2DModel::Live2DModel(){

	// 開始時間の取得
	startTimeMSec = live2d::UtSystem::getUserTimeMSec();

}// Live2DModel
//=============================================================================
// Destructor
//=============================================================================
Live2DModel::~Live2DModel(){

	
	SafeDelete(live2DModel);
	SafeDelete(eyeBlink);
	SafeDelete(pose);
	SafeDelete(physics);
	SafeDelete(exMotion1);
	SafeDelete(exMotion2);
	SafeDelete(motionMgr);
	SafeDelete(motion1);
	SafeDelete(motion2);

}// ~Live2DModel
//=============================================================================
// Init
//=============================================================================
bool Live2DModel::Init(LPDIRECT3DDEVICE9 paramDevice)
{

	// モデルのロード
	live2DModel = Live2DModelD3D::loadModel("data\\res\\haru\\haru_01.moc");

	// テクスチャのロード
	for (int i = 0; i < 10; i++){
		if (!TEXTURES[i]) break;

		LoadTexture(TEXTURES[i], paramDevice, i);

	}// for

	// モーション管理
	motionMgr = new L2DMotionManager();

	// 目パチ
	eyeBlink = new L2DEyeBlink();

	// ポーズ
	pose = CreatePose("data\\res\\haru\\haru.pose.json");

	// 物理演算（髪）
	physics = CreatePysics("data\\res\\haru\\haru.physics.json");


	// 待機モーション
	motion1 = CreateMotion("data\\res\\haru\\motions\\idle_00.mtn");

	// タッチモーション
	motion2 = CreateMotion("data\\res\\haru\\motions\\tapBody_00.mtn");

	// 表情
	exMotion1 = CreateExMotion("data\\res\\haru\\expressions\\f05.exp.json");

	// 表情
	exMotion2 = CreateExMotion("data\\res\\haru\\expressions\\f01.exp.json");

	// 成功
	return S_OK;

}// Init
//=============================================================================
// FunctionName: LoadTexture
// Param: 読み込むテクスチャのパス
// ReturnValue: 読み込み結果
// Content: テクスチャの読み込み
//=============================================================================
bool Live2DModel::LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum){

	// 変数宣言
	LPDIRECT3DTEXTURE9 tex;
	bool tmpFlg = false;

	// テクスチャ画像をDirextXでの表示用に変換
	if (SUCCEEDED(D3DXCreateTextureFromFileExW(paramDevice
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
		, &tex))){

		// 変換が成功したらセット
		live2DModel->setTexture(paramTexNum, tex);
		tmpFlg = true;

	}// if

	// 結果を返す
	return tmpFlg;

}// LoadTexture
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
AMotion* Live2DModel::CreateMotion(const char* paramFilePath){

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
L2DExpressionMotion* Live2DModel::CreateExMotion(const char* paramFilePath){

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
void Live2DModel::Update(void)
{
	eyeBlink->setParam(live2DModel);// 目パチ

	if (GetAsyncKeyState('E') & 0x8000)
	{
		motionMgr->startMotionPrio(motion1, false, PRIORITY_IDLE);


	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		motionMgr->startMotionPrio(motion2, false, PRIORITY_NORMAL);


	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		motionMgr->startMotionPrio(exMotion1, false, PRIORITY_NORMAL);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{

		motionMgr->startMotionPrio(exMotion2, false, PRIORITY_NORMAL);


	}

}
//=============================================================================
// Draw
//=============================================================================
void Live2DModel::Draw(LPDIRECT3DDEVICE9 paramDevice)
{

	// 描画の前に行列の準備
	SetupMatrix(paramDevice);

	// モデルの描画
	DrawMod(paramDevice);

}
//=============================================================================
// DrawMod
//=============================================================================
void Live2DModel::DrawMod(LPDIRECT3DDEVICE9 paramDevice){

	// 呼吸など
	LDint64	 timeMSec = live2d::UtSystem::getUserTimeMSec() - startTimeMSec;
	double t = (timeMSec / 1000.0) * 2 * 3.14159;//2*Pi*t
	live2DModel->setParamFloat("PARAM_BREATH", (float)(0.5f + 0.5f * sin(t / 3.2345)), 1);// 0~1 まで周期的に設定。モーションを上書き。

	// 物理演算でパラメータ更新
	if (physics != NULL)physics->updateParam(live2DModel);

	// ポーズの設定
	if (pose != NULL)pose->updateParam(live2DModel);

	// モーションの更新
	motionMgr->updateParam(live2DModel);

	live2DModel->setDevice(paramDevice);
	live2DModel->update();
	live2DModel->draw();

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
	w = 1300;
	h = 750;

	float raito = (float)(h / w);

	float modelWidth = live2DModel->getModelImpl()->getCanvasWidth();
	float modelHeight = live2DModel->getModelImpl()->getCanvasHeight();

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


	D3DXMatrixTranslation(&trans, -modelWidth / 2, -modelHeight / 2, 0);
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 1.0f);
	world = trans *world * scale;

	paramDevice->SetTransform(D3DTS_WORLD, &world);

}// SetupMatrix
// EOF