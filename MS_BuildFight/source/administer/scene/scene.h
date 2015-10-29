//=============================================================================
//
// MS_BuildFight [CScene.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENE_H_
#define _CSCENE_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../common.h"
#include "../../module/etc/Fade.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************

class CScene
{
	public:
		CScene(void){};			//コンストラクタ
		virtual ~CScene(void){};			//デストラクタ

		virtual HRESULT Init(LPDIRECT3DDEVICE9 pDevice)=0;	//初期化
		virtual void Uninit(void)=0;	//終了
		virtual void Update(void)=0;	//更新
		virtual void Draw(void)=0;		//描画

		int GetFrame(void){return m_nSelectFrame;};
		int GetEnemy(void){return m_nSelectEnemy;};
		int GetMap(void){return m_nSelectMap;};
		int GetTime(void){return m_nGameTime;};
		int GetScore(void){return m_nGameScore;};
		bool GetVSFlag(void){return m_bVSFlag;};
		bool GetReplayFlag(void){return m_bReplayFlag;};

		void SetFrame(int nType){m_nSelectFrame=nType;};
		void SetEnemy(int nType){m_nSelectEnemy=nType;};
		void SetMap(int nType){m_nSelectMap=nType;};
		void SetTime(int nType){m_nGameTime=nType;};
		void SetScore(int nType){m_nGameScore+=nType;};
		void SetVSFlag(bool bChange){m_bVSFlag=bChange;};
		void SetReplayFlag(bool bChange){m_bReplayFlag=bChange;};

	protected:

	private:
		int		m_nSelectFrame;
		int		m_nSelectEnemy;
		int		m_nSelectMap;
		int		m_nGameTime;
		int		m_nGameScore;
		bool	m_bVSFlag;
		bool	m_bEndLoad;
		bool	m_bReplayFlag;
};

#endif

/////////////EOF////////////