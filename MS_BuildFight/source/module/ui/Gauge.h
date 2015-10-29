//=============================================================================
//
// MS_BuildFight [Gauge.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGAUGE_H_
#define _CGAUGE_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../form/form.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FIGURE_G_MAX		(6)
#define SCORE_G_MAX			(3000)

class CBar;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGauge  : public Cform
{
	public:
		CGauge(int nPriority = 7);//コンストラクタ
		~CGauge(void);//デストラクタ

		static CGauge *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool Etype);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool Etype);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void AddGauge(int nValue);
		void ResetGauge(int nSet);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){};
		void SetRotCamera (D3DXVECTOR3 rotCamera){};
		int GetGauge(void){return m_nGauge;};

	private:
		LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)	

		D3DXVECTOR3				m_Pos;			//位置
		D3DXVECTOR3				m_Rot;			//向き

		CBar					*m_pBar[FIGURE_G_MAX];

		int						m_nGauge;
		int						m_nGaugeFigure;
		float					m_fView;
		bool					m_bEtype;
};

#endif

/////////////EOF////////////