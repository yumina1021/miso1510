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
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_SE_SELECT000,	// カーソル音
	SOUND_LABEL_SE_SELECT001,	// カーソル音
	SOUND_LABEL_SE_SELECT002,	// カーソル音
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_HIT000,		// 衝突音0
	SOUND_LABEL_SE_START,		// 衝突音0
	SOUND_LABEL_SE_LANDING,		// 衝突音0
	SOUND_LABEL_SE_SLASH,		// 衝突音0
	SOUND_LABEL_SE_BEAMSWORD,	// 衝突音0
	SOUND_LABEL_MAX
} SOUND_LABEL;

typedef enum
{
	VOICE_LABEL_SE_START,		// 発進音
	VOICE_LABEL_SE_SHOT,		// 弾発射音
	VOICE_LABEL_SE_SHOT2,		// 弾発射音
	VOICE_LABEL_SE_SHOT3,		// 弾発射音
	VOICE_LABEL_SE_SLASH,		// 衝突音0
	VOICE_LABEL_SE_SLASH2,		// 衝突音0
	VOICE_LABEL_SE_DAMAGE,		// ダメージ
	VOICE_LABEL_SE_DAMAGE2,		// ダメージ
	VOICE_LABEL_SE_DAMAGE3,		// ダメージ
	VOICE_LABEL_SE_SKILL,		// スキル
	VOICE_LABEL_SE_SKILL2,		// スキル
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