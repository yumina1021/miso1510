//=============================================================================
//
// MS_BuildFight [CCharPicture.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCHARPICTURE_H_
#define _CCHARPICTURE_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../form/form2D.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
typedef enum
{
	t_stert=0,
	t_vs,
	t_tutorial,
	t_end,
	s_0,
	s_1,
	s_2,
	s_3,
	s_4,
	s_5,
	s_6,
	s_7,
	n_b,
	s_99,
	p_continue,
	p_retry,
	p_quit,
	num_max
}PictureNum;

// 状態遷移用のモード
enum class GUI_MODE : unsigned short{

	NORMAL = 0,	// 通常
	FLASH,		// 選択中
	HIDE,		// 隠す
	DESELECT,	// ボタンの選択解除用に特別に作る

};

enum class GUI_FADE : unsigned short{

	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX,

};
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharPicture  : public Cform2D
{
	public:
		CCharPicture();//コンストラクタ
		~CCharPicture(void);//デストラクタ

		static CCharPicture *Create(LPDIRECT3DDEVICE9 pDevice,
									PictureNum nType,
									D3DXVECTOR3 pos,
									float fwidth,
									float fheight);// 生成

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,
			PictureNum nType,
			D3DXVECTOR3 pos,
			float fwidth,
			float fheight);								// 初期化
		void Uninit(void);								// 終了
		void Update(void);								// 更新
		void Draw(void);								// 描画
		D3DXVECTOR3 GetLen(void){ return m_Len; };		// 長さの取得
		void ChangeGuiState(GUI_MODE paramMode);		// 状態遷移
		void Flash(void);								// チカチカ
		const GUI_MODE& GetGuiMode(){ return m_Mode; };	// GUIの状態を取得

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;				// フェード時間
		static const LPSTR	m_apTextureName[];		// テクスチャー
		D3DXVECTOR3			m_Len;					// 長さ
		D3DXCOLOR			m_Diff;					// 色
		GUI_MODE			m_Mode;					// 状態遷移用のモード
		GUI_FADE			m_NowFade;				// チカチカさせるためのフェード状態識別用
		float				m_FadeCoff;				// フェードの係数

};

#endif

/////////////EOF////////////