//=============================================================================
//
// MS_BuildFight [DomeU.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CDOMEU_H_
#define _CDOMEU_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../form/form3D.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SUM_INDEX(X,Z)	((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDomeU  : public Cform3D
{
	public:
		CDomeU(int nPriority = 3);//コンストラクタ
		~CDomeU(void);//デストラクタ

		static CDomeU *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){};

	private:
		LPDIRECT3DTEXTURE9		m_pD3DTex;			//テクスチャ表示用
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;		//頂点情報格納ワーク(動的)
		LPDIRECT3DDEVICE9		m_pDevice;			// pDeviceオブジェクト(描画に必要)
		LPDIRECT3DINDEXBUFFER9  m_pD3DIndexBuff;	// インデックスバッファへのポインタ

		D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス		
		D3DXMATRIX				m_MtxView;			//ビューマトリクス

		D3DXVECTOR3				m_Pos;				//位置
		D3DXVECTOR3				m_Rot;				//向き
		D3DXVECTOR3				m_Scl;				//大きさ

		int		m_nNumVertex;						// 総頂点数
		int		m_nNumVertexIndex;					// 頂点の総インデックス数

		LPDIRECT3DPIXELSHADER9 _ps;			//ピクセルシェーダー
		LPD3DXCONSTANTTABLE    _psc;		//ピクセルシェーダー用コンスタントテーブル
		LPDIRECT3DVERTEXSHADER9 _vs;		//バーテックスシェーダー
		LPD3DXCONSTANTTABLE    _vsc;		//バーテックスシェーダー用コンスタントテーブル

};

#endif

/////////////EOF////////////