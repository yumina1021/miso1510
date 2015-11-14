//=============================================================================
//
// MS_BuildFight [CCursor.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCURSOR_H_
#define _CCURSOR_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CharPicture.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCursor : public CCharPicture
{
	public:
		CCursor();		//コンストラクタ
		~CCursor(void);	//デストラクタ

		static CCursor *Create(LPDIRECT3DDEVICE9 pDevice,
			PictureNum nType,
			D3DXVECTOR3 pos,
			float fwidth,
			float fheight);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,
						PictureNum nType,
						D3DXVECTOR3 pos,
						float fwidth,
						float fheight);	// 初期化
		void Uninit(void);				// 終了
		void Update(void);				// 更新
		void Draw(void);				// 描画

		void MoveByKeybord(void);					// 
		void AddForce(void);						// 
		void SyncCharPos(D3DXVECTOR3 paramSyncPos);	// キャラの座標と同期させる
		void SetTime(float paramTime){ m_Time = paramTime; };	// キャラの座標と同期させる

		static void RadianRot(float& paramRot);
		static D3DXVECTOR3 EsasingNone(D3DXVECTOR3 paramMinPos,
										D3DXVECTOR3 paramMaxPos,
										float paramTime);
		
		static bool HitChkRect(const D3DXVECTOR3& paramPos1,
			const D3DXVECTOR3& paramPos2,
			const D3DXVECTOR3& paramLen1,
			const D3DXVECTOR3& paramLen2);
	private:
		D3DXVECTOR3 m_fVelocity;
		float m_fDiffuse;
		bool m_bUseWiiPad;
		float m_Time;

};

#endif

/////////////EOF////////////