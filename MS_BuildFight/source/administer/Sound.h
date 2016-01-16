//=============================================================================
//
// MS_BuildFight [Sound.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSOUND_H_
#define _CSOUND_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../common.h"
#include "xaudio2.h"
//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM2
	SOUND_LABEL_BGM002,			// BGM1
	SOUND_LABEL_BGM003,			// BGM2
	SOUND_LABEL_BGM_EXTRA,		// エクストラBGM
	SOUND_LABEL_SE_SELECT000,	// カーソル音
	SOUND_LABEL_SE_SELECT001,	// 決定音
	SOUND_LABEL_SE_ORGAN,		// オルガン
	SOUND_LABEL_SE_SENI,		// シーン遷移音
	SOUND_LABEL_SE_SHINE,		// シャランラ音
	SOUND_LABEL_SE_TRUMPET,		// トランペット
	SOUND_LABEL_SE_SHOT,		// ショット音
	SOUND_LABEL_SE_SELECT002,	// 選択音候補
	SOUND_LABEL_MAX
} SOUND_LABEL;

typedef enum
{
	VOICE_LABEL_SE_TITLE_CALL = 0,	// 
	VOICE_LABEL_SE_VOICE00,		// 
	VOICE_LABEL_SE_VOICE01,		// 
	VOICE_LABEL_SE_VOICE02,		// 
	VOICE_LABEL_SE_VOICE03,		// 
	VOICE_LABEL_SE_VOICE04,		// 
	VOICE_LABEL_SE_VOICE05,		// 
	VOICE_LABEL_SE_VOICE06,		// 
	VOICE_LABEL_SE_VOICE07,		// 
	VOICE_LABEL_SE_VOICE08,	// 
	VOICE_LABEL_SE_VOICE09,	// 
	VOICE_LABEL_SE_VOICE10,	// 
	VOICE_LABEL_SE_VOICE11,		// 
	VOICE_LABEL_SE_VOICE12,		// 
	VOICE_LABEL_SE_VOICE13,		// 
	VOICE_LABEL_SE_VOICE14,// 
	VOICE_LABEL_SE_VOICE15,// 
	VOICE_LABEL_MAX
} VOICE_LABEL;

#define CHARACTER_MAX (4)
//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	bool bLoop;			// ループするかどうか
} PARAM;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
	public:
		CSound(void);				//コンストラクタ
		~CSound(void);				//デストラクタ

		HRESULT Init(HWND hWnd);				//初期化
		void Uninit(void);						//終了

		HRESULT Play(SOUND_LABEL label);		//更新
		HRESULT PlayVoice(int nType,VOICE_LABEL label);	//更新

		void Stop(void);						//描画
		void Stop(SOUND_LABEL label);
		void StopVoice(int nType,VOICE_LABEL label);

#ifdef _DEBUG
		void Setm_nCountFPS(int set);
#endif

	private:
		HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

		LPDIRECT3D9				m_pD3D;								// Direct3Dオブジェクト
		LPDIRECT3DDEVICE9		m_pD3DDevice;						// pDeviceオブジェクト(描画に必要)	
		IXAudio2				*g_pXAudio2;						// XAudio2オブジェクトへのインターフェイス
		IXAudio2MasteringVoice	*g_pMasteringVoice;					// マスターボイス

		IXAudio2SourceVoice		*g_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
		BYTE					*g_apDataAudio[SOUND_LABEL_MAX];	// オーディオデータ
		DWORD					g_aSizeAudio[SOUND_LABEL_MAX];

		IXAudio2SourceVoice		*g_apSourceVoice2[VOICE_LABEL_MAX*CHARACTER_MAX];	// ソースボイス
		BYTE					*g_apDataAudio2[VOICE_LABEL_MAX*CHARACTER_MAX];	// オーディオデータ
		DWORD					g_aSizeAudio2[VOICE_LABEL_MAX*CHARACTER_MAX];
};

#endif

/////////////EOF////////////