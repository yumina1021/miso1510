//=============================================================================
//
// MS_BuildFight [Timer.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTIMER_H_
#define _CTIMER_H_
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
#define FIGURE_MAX			(3)
#define TIMER_MAX			(180)

class CNumber;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTimer  : public Cform
{
	public:
		CTimer(int nPriority = 7);//コンストラクタ
		~CTimer(void);//デストラクタ

		static CTimer *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void AddTimer(int nValue);
		void ResetTimer(int nSet);

		int GetTimer(void){return m_nTimer;};

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){};

		void SetRotCamera (D3DXVECTOR3 rotCamera){};

	private:
		LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)	

		D3DXVECTOR3				m_Pos;			//位置
		D3DXVECTOR3				m_Rot;			//向き

		CNumber					*m_pNumber[FIGURE_MAX];

		int						m_nTimer;
};

#endif

/////////////EOF////////////