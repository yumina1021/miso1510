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
	n_b,
	s_99,
	p_continue,
	p_retry,
	p_quit,
	num_max
}PictureNum;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharPicture  : public Cform2D
{
	public:
		CCharPicture();//コンストラクタ
		~CCharPicture(void);//デストラクタ

		static CCharPicture *Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		D3DXVECTOR3 GetLen(void){ return m_Len; };

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;				//フェード時間
		static const LPSTR	m_apTextureName[];		//テクスチャー
		D3DXVECTOR3			m_Len;

};

#endif

/////////////EOF////////////