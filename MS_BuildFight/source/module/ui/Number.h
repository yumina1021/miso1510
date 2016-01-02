//=============================================================================
//
// MS_BuildFight [Number.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CNUMBER_H_
#define _CNUMBER_H_
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
#define POINT_MAX			(4)
#define NUMBER_WIDTH		(30)
#define NUMBER_HEIGHT		(60)
#define NUMBER_FIRST_X		(0)
#define NUMBER_FIRST_Y		(0)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CNumber
{
	public:
		CNumber(void);//コンストラクタ
		~CNumber(void);//デストラクタ

		static CNumber *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetNumber(float nNumber);
		void SetColor(D3DXCOLOR color);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
	private:
		//LPDIRECT3DTEXTURE9  	m_pD3DTex;		//テクスチャ表示用
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//頂点情報格納ワーク(動的)
		LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)	

		D3DXVECTOR3				m_Pos;			//位置
		D3DXVECTOR3				m_Rot;			//向き

		float					m_fLength;		//ポリゴン対角線の長さ
		float					m_fAngle;		//ポリゴン対角線の角度

		int m_nNumber;
		int m_texid;
};

#endif

/////////////EOF////////////