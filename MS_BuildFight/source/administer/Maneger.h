//=============================================================================
//
// MS_BuildFight [CManager.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CMANAGER_H_
#define _CMANAGER_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "../common.h"


#define SCENE_MAX	(10)


typedef enum			//フェーズの種類
{
	PHASETYPE_TITLE =0,
	PHASETYPE_TUTRIAL,
	PHASETYPE_SELECT,
	PHASETYPE_STAGE_SELECT,
	PHASETYPE_LOAD,
	PHASETYPE_GAME,
	PHASETYPE_RESULT,
	PHASETYPE_CLEAR,
	PHASETYPE_GAMEOVER,
	PHASETYPE_VSEND,
	PHASETYPE_MAX
}PHASETYPE;

struct RenderTagets		//レンダーターゲット
{
	LPDIRECT3DTEXTURE9		texture;		//テクスチャ用ポインタ
	LPDIRECT3DSURFACE9		surface;		//カラーバッファ用サーフェス
	LPDIRECT3DSURFACE9		surfaceDepth;	//Ｚバッファ用サーフェス
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;	// 頂点バッファインターフェースへのポインタ
};
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CInputKeyboard;	//前方宣言
class CInputMouse;
class CInputJoypad;
class CSound;
class CScene;
class CCamera;
class CGame;
class Cform;
class CLight;
class CEffect;

#ifdef _DEBUG
class CDebugProc;
#endif

class CManager
{
	public:
		CManager(void);					//コンストラクタ
		~CManager(void);				//デストラクタ

		HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);	//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画

		void Addform(Cform* pform);				//シーンの登録用

		static void SetAfterScene(PHASETYPE phase){m_afterSceneType=phase;};	//次のフェーズ受け取り

		static CInputKeyboard* GetInputKeyboard(void){ return m_pKeyboard; };
		static CInputMouse* GetInputMouse(void){ return m_pMouse; };
		static CInputJoypad* GetInputJoypad(void){ return m_pJoypad; };
		static CSound *GetSound(void){ return m_pSound; };
		static CScene *GetScene(void){ return m_pScene; };
		static CCamera* GetCamera(void){ return m_pCamera; };
		static CLight *GetLight(void){ return m_pLight; }

		static LPDIRECT3DDEVICE9 GetDevice(void){ return m_pD3DDevice; };	//デバイスの取得
		void SetDevice(LPDIRECT3DDEVICE9 device){ m_pD3DDevice = device; };	//デバイスの取得

		static PHASETYPE GetSceneType(void){ return m_phaseType; };
		static PHASETYPE GetAfetrSceneType(void){ return m_afterSceneType; };

		static void SetpauseFlag(bool pause){m_pauseFlag =pause;};
		static bool GetpauseFlag(void){return m_pauseFlag;};

		static void SetgameEndFlag(bool pause){m_gameEndFlag =pause;};
		static bool GetgameEndFlag(void){return m_gameEndFlag;};

		static void Setnight0PlayFlag(bool pause){m_night0PlayFlag =pause;};
		static bool Getnight0PlayFlag(void){return m_night0PlayFlag;};

		static void SetWndHandle(HWND paramWnd){ m_hwnd = paramWnd; };
		static HWND GetWndHandle(void){ return m_hwnd; };

		static void SetSelectMap(int paramMap){ m_nSelectMap = paramMap; };
		static int GetSelectMap(void){ return m_nSelectMap; };

		static void SetSelectChar(int paramSetPlayer, int paramMap){ m_nSelectChar[paramSetPlayer] = paramMap; };
		static int  GetSelectChar(int paramSetPlayer){ return m_nSelectChar[paramSetPlayer]; };

		int SetRenderTargets(float width, float height);
		void RemoveRenderTargets(int i);
		RenderTagets* GetRenderTargets(int i){ return m_renderTargets[i]; };

	private:
		void RenderTargetDraw(void);
		HRESULT RenderInit(HWND hWnd, BOOL bWindow);
		
		HRESULT SetShader(void);

		void ChangeScene(void);						//フェーズの変更

		LPDIRECT3D9					m_pD3D;					// Direct3Dオブジェクト
		static LPDIRECT3DDEVICE9	m_pD3DDevice;			// pDeviceオブジェクト(描画に必要)

		Cform*					m_apforms[SCENE_MAX];	//シーン登録用ポインタ
		int						m_nCountform;			//登録数
		bool					m_bWirerFlag;			//ワイヤーフレーム表示フラグ

		static CInputKeyboard*	m_pKeyboard;		//キーボードへのポインタ
		static CInputMouse*		m_pMouse;			//マウスへのポインタ
		static CInputJoypad*	m_pJoypad;			//ジョイパッドへのポインタ
		static CSound*			m_pSound;			//サウンドのポインター
		static CScene*			m_pScene;			//フェーズのポインター
		static CScene*			m_pSceneT;			//フェーズのポインター
		static CCamera*			m_pCamera;				//カメラのポインタ
		static CLight*			m_pLight;			// ライトへのポインタ

		static PHASETYPE		m_phaseType;		//現在のフェーズタイプ
		static PHASETYPE		m_afterSceneType;	//次のフェーズタイプ
		static HWND				m_hwnd;

#ifdef _DEBUG
		static  CDebugProc *m_pDebugProc;			//デバッグ処理へのポインタ
#endif

		static bool				m_pauseFlag;		//ポーズをしているかのフラグ
		static bool				m_gameEndFlag;		//ゲーム終了中かのフラグ
		static bool				m_night0PlayFlag;	//ナイト０と戦ったかどうか？

		int						m_nFrameNum;
		int						m_nEnemyNum;

		RenderTagets*			m_renderTargets[5];

		LPDIRECT3DSURFACE9		m_pSurfaceBack;	//バックバッファ用サーフェス
		LPDIRECT3DSURFACE9		m_pSurfaceBackD;//バックバッファ用サーフェス

		D3DVIEWPORT9			m_pViewport;	//ビューポート保存用

		LPDIRECT3DPIXELSHADER9 _ps[3];			//ピクセルシェーダー
		LPD3DXCONSTANTTABLE    _psc[3];		//ピクセルシェーダー用コンスタントテーブル

		static int				m_nSelectMap;		//選んだマップ
		static int				m_nSelectChar[2];	//選んだキャラ
};

#endif

/////////////EOF////////////