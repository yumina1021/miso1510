//=============================================================================
//
// MS_BuildFight [CCharacter.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_
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
	normal = 0,
	smile,
	smile2,
	smile3,
	smile4,
	smile5,
	shy,
	star,
	heart,
	hawawa,
	suprise,
	trouble,
	angery,
	seel,
	sad,
	ScenarioMax
}CharacterType;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharacter  : public Cform2D
{
	public:
		CCharacter();//コンストラクタ
		~CCharacter(void);//デストラクタ

		static CCharacter *Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		void SetViewFlag(bool change,int time){m_ViewFlag=change;m_nCount=time;};
		void SetCharaType(CharacterType type){ m_charaType = type; };
		CharacterType GetCharaType(void){ return m_charaType; };

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;
		static const LPSTR	m_apTextureName[];
		bool				m_ViewFlag;
		CharacterType		m_charaType;
		CharacterType		m_charaTypeOld;
};

#endif

/////////////EOF////////////