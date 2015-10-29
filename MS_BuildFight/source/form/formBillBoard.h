//=============================================================================
//
// MS_BuildFight [formBillBoard.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENEBILLBOARD_H_
#define _CSCENEBILLBOARD_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "form.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CformBillBoard  : public Cform
{
	public:
		CformBillBoard(int nPriority = 7);//コンストラクタ
		~CformBillBoard(void);//デストラクタ

		static CformBillBoard *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,float fLength,D3DXCOLOR changeColor);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetDiffuse(float r,float g,float b,float a);
		void SetVtx(float fLength);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		void SetUV(float ful,float fur,float fvt,float fvu);

	protected:
		LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)
	private:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;		//テクスチャ表示用
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//頂点情報格納ワーク(動的)

		D3DXMATRIX				m_MtxView;		//ビューマトリクス

		D3DXVECTOR3				m_Pos;			//位置
		D3DXVECTOR3				m_Rot;			//向き
		D3DXVECTOR3				m_Scl;			//大きさ
};

#endif

/////////////EOF////////////