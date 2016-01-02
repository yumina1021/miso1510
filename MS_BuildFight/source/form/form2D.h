//=============================================================================
//
// MS_BuildFight [form2D.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CFORM2D_H_
#define _CFORM2D_H_
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
#define POINT_MAX			(4)
#define POLYGON_WIDTH		(400)
#define POLYGON_HEIGHT		(400)
#define POLYGON_FIRST_X		(0)
#define POLYGON_FIRST_Y		(0)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Cform2D  : public Cform
{
	public:
		Cform2D(OBJTYPE objtype=OBJTYPE_2D,int nPriority=7);//コンストラクタ
		~Cform2D(void);//デストラクタ

		static Cform2D *Create(LPDIRECT3DDEVICE9 pDevice, int pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int pFileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot,float width,float height);//初期化
		//HRESULT Init2(LPDIRECT3DDEVICE9 pDevice, int pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);//初期化
		void Uninit(void);//終了
		void Uninit2(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetDiffuse(float r,float g,float b,float a);
		void SetTexture(int pFileName);
		//void SetTexture(LPDIRECT3DTEXTURE9 pTex);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

		void SetLength(float width, float height);
		D3DXVECTOR2 GetLengthWH(void){ return D3DXVECTOR2(m_fWidth, m_fHeight); };
		void SetLength(float length){ m_fLength = length; };
		float GetLength(void){ return m_fLength; };

	private:
		//LPDIRECT3DTEXTURE9  	m_pD3DTex;		//テクスチャ表示用
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//頂点情報格納ワーク(動的)
		LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)	

		D3DXVECTOR3				m_Pos;			//位置
		D3DXVECTOR3				m_Rot;			//向き

		float					m_fLength;		//ポリゴン対角線の長さ
		float					m_fAngle;		//ポリゴン対角線の角度
		float					m_fWidth;
		float					m_fHeight;
		int						m_texid;
};

#endif

/////////////EOF////////////