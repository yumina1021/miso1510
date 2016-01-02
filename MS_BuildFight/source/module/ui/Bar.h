//=============================================================================
//
// MS_BuildFight [CBar.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBAR_H_
#define _CBAR_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../common.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POINT_MAX		(4)
#define BAR_WIDTH		(30)
#define BAR_HEIGHT		(60)
#define BAR_FIRST_X		(0)
#define BAR_FIRST_Y		(0)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBar
{
	public:
		CBar();//コンストラクタ
		~CBar(void);//デストラクタ

		static CBar *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetViewFlag(bool Flag){m_bViewFlag=Flag;};
		
	private:
		//LPDIRECT3DTEXTURE9  	m_pD3DTex;		//テクスチャ表示用
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//頂点情報格納ワーク(動的)
		LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)	

		D3DXVECTOR3				m_Pos;			//位置
		D3DXVECTOR3				m_Rot;			//向き

		float					m_fLength;		//ポリゴン対角線の長さ
		float					m_fAngle;		//ポリゴン対角線の角度
		bool					m_bViewFlag;	
		int	m_texid;
};

#endif

/////////////EOF////////////