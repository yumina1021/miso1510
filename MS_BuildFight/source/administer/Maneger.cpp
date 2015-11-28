//=============================================================================
//
// MS_BuildFight [CManager.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include <time.h>
#include <process.h>
#include <stdio.h>
#include <direct.h>

#include "Maneger.h"
#include "Renderer.h"
#include "Input.h"
#include "Sound.h"
#include "Debugproc.h"

#include "scene/Scene.h"
#include "scene/Title.h"
#include "scene/Select.h"
#include "scene/StageSelect.h"
#include "scene/Game.h"
#include "scene/Result.h"
#include "scene/Tutorial.h"
#include "scene/GameClear.h"
#include "scene/Vsend.h"

#include "../form/form.h"

#include "../module/etc/Light.h"
#include "../module/etc/Camera.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DDEVICE9 CManager::m_pD3DDevice = NULL;		// デバイスのポインタ
CInputKeyboard* CManager::m_pKeyboard = NULL;			//インプット
CInputMouse * CManager ::m_pMouse = NULL;
CInputJoypad * CManager::m_pJoypad = NULL;
WiiRemote* CManager::wiimote[2] = { NULL ,NULL};

CSound *CManager::m_pSound = NULL;						//サウンド

CScene	*CManager::m_pScene = NULL;						//フェーズ

CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;						// ライト

PHASETYPE CManager::m_phaseType = PHASETYPE_TITLE;			//フェーズのタイプ
PHASETYPE CManager::m_afterSceneType = PHASETYPE_TITLE;

HWND CManager::m_hwnd = NULL;

#ifdef _DEBUG
CDebugProc *CManager::m_pDebugProc = NULL;				// デバッグ
#endif

bool CManager::m_pauseFlag = false;
bool CManager::m_gameEndFlag = false;
bool CManager::m_night0PlayFlag = false;
int CManager::m_nSelectMap = 0;
int CManager::m_nSelectChar[] = { 0, 1 };

//インプット
//=============================================================================
// コンストラクタ
//=============================================================================
CManager :: CManager(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CManager :: ~CManager(void)
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CManager :: Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	//乱数初期化
	srand( (unsigned int)time( NULL ) );

	RenderInit(hWnd, bWindow);

	//サウンドの初期化
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	//キーボードの初期化
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance,hWnd);

	//マウスの初期化
	m_pMouse = new CInputMouse();
	m_pMouse->Init(hInstance,hWnd);

	//ジョイパッドの初期化
	//m_pJoypad = new CInputJoypad();
	//m_pJoypad->Init(hInstance,hWnd);

	for (int i = 0; i < 2; i++)
	{
		wiimote[i] = new WiiRemote;
		if (!wiimote[i]->Init(0x1))
		{
			delete wiimote[i];
			MessageBox(hWnd, "wiicon not connet", "Error", MB_OK);
			wiimote[i] = NULL;
		}
	}

	// ライト処理初期化
	m_pLight = new CLight;
	m_pLight->Init(m_pD3DDevice);

	m_pCamera = new CCamera;
	m_pCamera->Init();

	//フェーズの初期化
	m_pScene=new CTitle();
	m_pScene->Init(m_pD3DDevice);

#ifdef _DEBUG
		//デバック表示の初期化
		m_pDebugProc = new CDebugProc;
		m_pDebugProc->Init(m_pD3DDevice);
#endif

	//フェーズの設定
	m_phaseType=PHASETYPE_TITLE;
	m_afterSceneType=m_phaseType;
	m_pauseFlag=false;
	m_gameEndFlag=false;

	m_nCountform = 0;
	m_bWirerFlag = false;

	m_nFrameNum = 0;
	m_nEnemyNum = 0;

	m_hwnd = hWnd;

	return S_OK;
}
//=============================================================================
// レンダラ―初期化
//=============================================================================
HRESULT CManager::RenderInit(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定

	if (bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートパラメータの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	//SetShader();

	//バックバッファ（カラー）サーフェスの保存
	if (FAILED(m_pD3DDevice->GetRenderTarget(0, &m_pSurfaceBack)))
	{
		// 初期化失敗
		MessageBox(NULL, "バックバッファ(カラー)サーフェスの保存エラー", "error", MB_OK);
		return E_FAIL;
	};

	//バックバッファ（Ｚ）サーフェスの保存
	if (FAILED(m_pD3DDevice->GetDepthStencilSurface(&m_pSurfaceBackD)))
	{
		// 初期化失敗
		MessageBox(NULL, "バックバッファ(Z)サーフェスの保存エラー", "error", MB_OK);
		return E_FAIL;
	};

	//ビューポートの保存
	m_pD3DDevice->GetViewport(&m_pViewport);

	for (int i = 0; i < 5; i++)
	{
		m_renderTargets[i] = new RenderTagets;
		RemoveRenderTargets(i);
	}

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CManager :: Uninit(void)
{
	//メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	m_pSurfaceBackD->Release();
	m_pSurfaceBack->Release();

	m_pCamera->Uninit();	//カメラ

	if (m_pCamera != NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	m_pLight->Uninit();

	if (m_pLight != NULL)
	{
		delete m_pLight;
		m_pLight = NULL;
	}

	//シーンを全て終了
	Cform::ReleaseAll();

	for (int i = 0; i < 5; i++)
	{
		delete m_renderTargets[i];
	}

	SafeRelease(&m_pD3D);
	SafeRelease(&m_pD3DDevice);

	//各終了処理
	m_pScene->Uninit();		//フェーズ

	if(m_pScene!=NULL)
	{
		delete m_pScene;
		m_pScene=NULL;
	}

	m_pMouse->Uninit();		//マウス

	if(m_pMouse!=NULL)
	{
		delete m_pMouse;
		m_pMouse = NULL;
	}

	m_pKeyboard->Uninit();	//キーボード

	if(m_pKeyboard!=NULL)
	{
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	m_pSound->Uninit();		//サウンド

	if (m_pSound != NULL)
	{
		delete m_pSound;
		m_pSound = NULL;
	}


	for (int i = 0; i < 2; i++)
	{
		if (wiimote[i] != NULL)
		{
			wiimote[i]->Uninit();
			delete wiimote[i];
		}
	}
	//m_pJoypad->Uninit();		//ジョイパッド

	//if(m_pJoypad!=NULL)
	//{
	//	delete m_pJoypad;
	//	m_pJoypad = NULL;
	//}

#ifdef _DEBUG
	if(m_pDebugProc)		//デバック表示
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
#endif
}
//=============================================================================
// 更新
//=============================================================================
void CManager :: Update(void)
{
#pragma omp parallel sections

#pragma omp section
	//各更新処理
	m_pKeyboard->Update();
	m_pMouse->Update();
	//m_pJoypad->Update();
	m_pScene->Update();
	for (int i = 0; i < 2; i++)
	{
		if (wiimote[i] != NULL)
		{
			wiimote[i]->Update();
		}
	}

	//フェーズの変更
	ChangeScene();

#pragma omp section

	//カメラ更新
	m_pCamera->Update();

	// 描画処理
	if(!(m_phaseType==PHASETYPE_GAME))
	{
		Cform::UpdateAll();
	}else if(m_pauseFlag)
	{
		Cform::UpdatePause();
	}else if(m_gameEndFlag)
	{
		Cform::UpdateGameEnd();
	}else
	{
		Cform::UpdateGame();
	}

	// スクリーンショット
	if (m_pKeyboard->GetKeyTrigger(DIK_F11))
	{
		// 変数宣言
		LPDIRECT3DSURFACE9 pSurface;	// 画像を保存するための変数
		int no = 0;						// すでにあった場合の変数
		char *filename;					// 保存する画像の名前
		filename = (char *)malloc(100);
		sprintf(filename, "data/screenshot/スクリーンショット%d.bmp", no);
		m_pD3DDevice->GetRenderTarget(0, &pSurface);
		FILE *file;
		fopen_s(&file, "./screenshot//nul", "r");
		if (file == NULL)
		{
			_mkdir("data/screenshot");
		}
		while (1)
		{
			fopen_s(&file, filename, "r");
			if (file == NULL)
			{
				//ファイルはねえよ！だからセーブするね(はぁと)
				break;
			}
			else
			{
				//ファイルはあるよ!次だ！次っ！
				no++;
				memset(filename, 0, 100);
				sprintf(filename, "data/screenshot/スクリーンショット%d.bmp", no);
			}
		}
		D3DXSaveSurfaceToFile(filename, D3DXIFF_BMP, pSurface, NULL, NULL);
		pSurface->Release();
		filename = NULL;
	}
	if (m_pKeyboard->GetKeyTrigger(DIK_F5))
	{
		SetAfterScene(PHASETYPE_TITLE);
	}
	if (m_pKeyboard->GetKeyTrigger(DIK_F6))
	{
		SetAfterScene(PHASETYPE_SELECT);
	}
	if (m_pKeyboard->GetKeyTrigger(DIK_F7))
	{
		SetAfterScene(PHASETYPE_STAGE_SELECT);
	}
	if (m_pKeyboard->GetKeyTrigger(DIK_F8))
	{
		SetAfterScene(PHASETYPE_RESULT);
	}
}
//=============================================================================
// 描画
//=============================================================================
void CManager :: Draw(void)
{
	//描画用初期化
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 100, 100, 0), 1.0f, 0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))//描画の開始
	{
		//カメラの設定
		m_pCamera->Set(m_pD3DDevice);

		m_pScene->Draw();

#ifdef _DEBUG
		// デバッグ処理
		CDebugProc::Draw();
#endif
		m_pD3DDevice->EndScene();//描画の終了
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
// シーン登録用
//=============================================================================
void CManager::Addform(Cform* pform)
{
	if (m_nCountform<SCENE_MAX)
	{
		m_apforms[m_nCountform] = pform;
		m_nCountform++;
	}
}
//=============================================================================
// フェーズ変更
//=============================================================================
void CManager::ChangeScene(void)
{
	static int frame;
	static int enemy;
	static int map;
	static int time;
	static int score;
	static bool vs;
	static bool replay;
	//次のフェーズが今のフェーズを違う場合
	if(m_afterSceneType!=m_phaseType)
	{
		switch(m_afterSceneType)
		{
			//次のフェーズがタイトル
			case PHASETYPE_TITLE:
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CTitle();
							m_pScene->Init(m_pD3DDevice);
							break;
			//次のフェーズがチュートリアル
			case PHASETYPE_TUTRIAL:
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CTutorial();
							m_pScene->Init(m_pD3DDevice);
							break;
			//次のフェーズがセレクト
			case PHASETYPE_SELECT:
							replay=m_pScene->GetReplayFlag();
							vs=m_pScene->GetVSFlag();
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CSelect();
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
							//次のフェーズがセレクト
			case PHASETYPE_STAGE_SELECT:
							m_nFrameNum = m_pScene->GetFrame();
							m_nEnemyNum = m_pScene->GetEnemy();
							replay = m_pScene->GetReplayFlag();
							vs = m_pScene->GetVSFlag();
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene = NULL;
							m_pScene = new CStageSelect();
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
			//次のフェーズがロード
			case PHASETYPE_LOAD:
							break;
			//次のフェーズがゲーム
			case PHASETYPE_GAME:
							map=m_pScene->GetMap();
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();
							vs=m_pScene->GetVSFlag();
							replay=m_pScene->GetReplayFlag();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene = new CGame();

							m_pScene->SetFrame(m_nFrameNum);
							m_pScene->SetEnemy(m_nEnemyNum);
							m_pScene->SetMap(map);
							m_pScene->SetTime(time);
							m_pScene->SetScore(score);
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
			//次のフェーズがクリア
			case PHASETYPE_CLEAR:
							frame=m_pScene->GetFrame();
							map=m_pScene->GetMap();
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();
							vs=m_pScene->GetVSFlag();
							replay = m_pScene->GetReplayFlag();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CGameClear();

							m_pScene->SetFrame(frame);
							m_pScene->SetMap(map);
							m_pScene->SetTime(time);
							m_pScene->SetScore(score);
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
			//次のフェーズが対戦終了
			case PHASETYPE_VSEND:
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();
							vs=m_pScene->GetVSFlag();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CVsend();

							m_pScene->SetTime(time);
							m_pScene->SetScore(score);
							m_pScene->SetVSFlag(vs);

							m_pScene->Init(m_pD3DDevice);
							break;

			//次のフェーズがリザルト
			case PHASETYPE_RESULT:
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene = new CResult();

							m_pScene->SetTime(time);
							m_pScene->SetScore(score);

							m_pScene->Init(m_pD3DDevice);
							break;
		}
		//今のフェーズに次のフェーズを入れる
		m_phaseType=m_afterSceneType;
	}
}

//=============================================================================
// レンダーターゲットの作成
//=============================================================================
int CManager::SetRenderTargets(float width, float height)
{
	int rendernum;

	for (rendernum = 0; rendernum < 5; rendernum++)
	{
		if (m_renderTargets[rendernum]->surface == NULL)
		{
			break;
		}
	}
	//テクスチャ作成
	if (FAILED(m_pD3DDevice->CreateTexture(width,		//幅
		height,			//高さ
		1,						//ミップマップレベル
		D3DUSAGE_RENDERTARGET,	//使用方法
		D3DFMT_A8R8G8B8,		//フォーマット
		D3DPOOL_DEFAULT,		//メモリ管理方法
		&m_renderTargets[rendernum]->texture,			//テクスチャーポインタ
		NULL)))					//謎
	{
		// 初期化失敗
		MessageBox(NULL, "Render用テクスチャ初期化エラー", "error", MB_OK);
		return E_FAIL;
	};

	//レンダリングターゲット用サーフェスの取得
	if (FAILED(m_renderTargets[rendernum]->texture->GetSurfaceLevel(0, &m_renderTargets[rendernum]->surface)))
	{
		// 初期化失敗
		MessageBox(NULL, "レンダリングターゲット用サーフェスの取得エラー", "error", MB_OK);
		return E_FAIL;
	};

	//Ｚバッファのサーフェス取得
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(width,	//幅(テクスチャと同じ)
		height,					//高さ(テクスチャと同じ)
		D3DFMT_D16,						//フォーマット
		D3DMULTISAMPLE_NONE,			//マルチサンプリングレベル（）
		0,								//マルチサンプリング品質
		TRUE,
		&m_renderTargets[rendernum]->surfaceDepth,			//サーフェスインターフェースポインタ
		NULL)))							//
	{
		// 初期化失敗
		MessageBox(NULL, "Ｚバッファのサーフェス取得エラー", "error", MB_OK);
		return E_FAIL;
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_renderTargets[rendernum]->vtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_renderTargets[rendernum]->vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].hrw =
			pVtx[1].hrw =
			pVtx[2].hrw =
			pVtx[3].hrw = 1.0f;

		// 頂点座標の設定
		pVtx[0].vtx.x = 0.0f;
		pVtx[0].vtx.y = 0.0f;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = width;
		pVtx[1].vtx.y = 0.0f;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = 0.0f;
		pVtx[2].vtx.y = height;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = width;
		pVtx[3].vtx.y = height;
		pVtx[3].vtx.z = 0.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		m_renderTargets[rendernum]->vtxBuff->Unlock();
	}

	return rendernum;
}

void CManager::RemoveRenderTargets(int i)
{
	m_renderTargets[i]->surface = NULL;
	m_renderTargets[i]->surfaceDepth = NULL;
	m_renderTargets[i]->texture = NULL;
	m_renderTargets[i]->vtxBuff = NULL;
}

HRESULT CManager::SetShader(void)
{
	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//ピクセルシェーダー用に変換
	hr = D3DXCompileShaderFromFile("basicPS.hlsl", NULL, NULL, "PS_BN_CHECK", "ps_2_0", 0, &code, &err, &_psc[0]);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return E_FAIL;
	}
	//シェーダーの登録
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps[0]);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return E_FAIL;
	}

	//ピクセルシェーダー用に変換
	hr = D3DXCompileShaderFromFile("basicPS.hlsl", NULL, NULL, "PS_GAUS_W", "ps_2_0", 0, &code, &err, &_psc[1]);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return E_FAIL;
	}
	//シェーダーの登録
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps[1]);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return E_FAIL;
	}

	//ピクセルシェーダー用に変換
	hr = D3DXCompileShaderFromFile("basicPS.hlsl", NULL, NULL, "PS_GAUS_H", "ps_2_0", 0, &code, &err, &_psc[2]);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return E_FAIL;
	}
	//シェーダーの登録
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps[2]);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
/////////////EOF////////////