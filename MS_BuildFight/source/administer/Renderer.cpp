//=============================================================================
//
// kadai_XXXPlus [CRenderer.cpp]
// 14/11/10
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include <stdio.h>
#include <direct.h>

#include "Renderer.h"
#include "Input.h"
#include "Maneger.h"
#include "debugproc.h"

#include "../form/form.h"

#include "../module/etc/Light.h"
#include "../module/etc/Camera.h"


CCamera *CRenderer::m_pCamera = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer :: CRenderer(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CRenderer :: ~CRenderer(void)
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenderer :: Init(HWND hWnd,BOOL bWindow)
{
	//ライト
	CLight* pLight;

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// ディスプレイタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&m_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	//様々なオブジェクトの初期化処理

	//レンダーステートパラメータの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// サンプラーステートパラメータの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	m_nCountform=0;

	pLight=new CLight;
	pLight->Init(m_pD3DDevice);

	m_pCamera= new CCamera;
	m_pCamera->Init();

	if(pLight!=NULL)
	{
		delete pLight;
		pLight=NULL;
	}

	m_bWirerFlag=false;
	
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CRenderer :: Uninit(void)
{

	m_pCamera->Uninit();	//カメラ

	if(m_pCamera!=NULL)
	{
		delete m_pCamera;
		m_pCamera=NULL;
	}

	//シーンを全て終了
	Cform::ReleaseAll();

	//様々なオブジェクトの終了（開放）処理
	SafeRelease(&m_pD3D);
	SafeRelease(&m_pD3DDevice);

}
//=============================================================================
// 更新
//=============================================================================
void CRenderer :: Update(int nType)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ワイヤーフレーム表示の切り替え
	if(pInputKeyboard->GetKeyTrigger(DIK_F1))
	{
		if(!m_bWirerFlag){
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
			m_bWirerFlag=true;
		}else{
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
			m_bWirerFlag=false;
		}
	}

	//カメラ更新
	m_pCamera->Update();

	switch(nType)
	{
		//シーンの更新
		case 0:Cform::UpdateAll();
				break;
		case 1:Cform::UpdateGame();
				break;
		case 2:Cform::UpdatePause();
				break;
		case 3:Cform::UpdateGameEnd();
				break;
	}

	// スクリーンショット
	if (pInputKeyboard->GetKeyTrigger(DIK_F11))
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
}
//=============================================================================
// 描画
//=============================================================================
void CRenderer :: Draw(int nType)
{
	//描画用初期化
	m_pD3DDevice ->Clear(0,NULL,(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
						D3DCOLOR_RGBA(100,100,100,0),
						1.0f,
						0);


	if(SUCCEEDED(m_pD3DDevice->BeginScene()))//描画の開始
	{
		//カメラの設定
		m_pCamera->Set(m_pD3DDevice);

		switch(nType)
		{
			case 0:Cform::DrawAll(m_pCamera->GetMtxView(),m_pCamera->GetRotCamera());
					break;
			case 1:Cform::DrawGame(m_pCamera->GetMtxView(),m_pCamera->GetRotCamera());
					break;
			case 2:Cform::DrawPause(m_pCamera->GetMtxView(),m_pCamera->GetRotCamera());
					break;
		}

#ifdef _DEBUG
		// デバッグ処理
		CDebugProc::Draw();
#endif
		m_pD3DDevice->EndScene();//描画の終了
	}

	m_pD3DDevice ->Present(NULL,NULL,NULL,NULL);
}
//=============================================================================
// シーン登録用
//=============================================================================
void CRenderer::Addform(Cform* pform)
{
	if(m_nCountform<SCENE_MAX)
	{
		m_apforms[m_nCountform]=pform;
		m_nCountform++;
	}
}
/////////////EOF////////////