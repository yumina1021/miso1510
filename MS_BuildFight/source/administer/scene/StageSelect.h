//=============================================================================
//
// MS_BuildFight [CStageSelect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSTAGE_SELECT_H_
#define _CSTAGE_SELECT_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 列挙体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackGround;	//前方宣言
class CFade;
class CCharPicture;
class CEffect;

class CStageSelect  : public CScene
{
	public:
		CStageSelect(void);			//コンストラクタ
		~CStageSelect(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画
		void SelectByButton(void);				//キーボードでの選択
		void SelectByCursor(void);				//カール移動での選択
		void UpdateFade(void);					//フェードの更新

		bool HitChkRect(const D3DXVECTOR3& paramPos1,
			const D3DXVECTOR3& paramPos2,
			const D3DXVECTOR3& paramLen1,
			const D3DXVECTOR3& paramLen2);

	private:
		CBackGround*		m_pBackGround;		//背景
		CFade*				m_pFade;			//フェード

		int					m_nCursor;			//カーソル
		bool				m_bChangeFlag;		//切り換えフラグ
		float				m_fDiffuse;			//アニメーション用
		bool				m_bVsSelectFlag;	//VSモード用
		bool				m_bTitleBackFlag;	//タイトルに行きました
		bool				m_bSendData;		//相手データが送られた
};

#endif

/////////////EOF////////////