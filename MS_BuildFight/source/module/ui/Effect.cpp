//=============================================================================
//
// MS_BuildFight [CEffect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Effect.h"
#include "../../administer/Texture.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const int CEffect::m_apTextureName[]=
{
	TEXTURE_CIRCUIT,
	TEXTURE_CIRCUIT2,
	TEXTURE_CIRCUIT_CIRCLE,
	TEXTURE_PLEASE_ROSA,
	TEXTURE_PLEASE_LILA,
	TEXTURE_PLEASE_LICHT,
	TEXTURE_PLEASE_JIJI,
	TEXTURE_SHOT_ROSA,
	TEXTURE_SHOT_LILA,
	TEXTURE_SHOT_LICHT,
	TEXTURE_SHOT_JIJI,
	TEXTURE_TIMEOUT,
	TEXTURE_TIMEOUT,
	TEXTURE_READY1,
	TEXTURE_READY2,
	TEXTURE_GAGE,
	TEXTURE_GAME_ROSA,
	TEXTURE_GAME_LILA,
	TEXTURE_GAME_LICHT,
	TEXTURE_GAME_JIJI,
	/*
	"data/TEXTURE/Enemyeffect001.png",
	"data/TEXTURE/Enemyeffect002.png",
	"data/TEXTURE/Enemyeffect003.png",
	"data/TEXTURE/Enemyeffect000.png",
	"data/TEXTURE/Enemyeffect010.png",
	"data/TEXTURE/tutrial002.png",
	"data/TEXTURE/tutrial003.jpg",
	"data/TEXTURE/tutrial004.jpg",
	"data/TEXTURE/tutrial005.jpg",
	"data/TEXTURE/tutrial006.png",
	"data/TEXTURE/tutrial007.png",
	"data/TEXTURE/tutrial008.png",
	"data/TEXTURE/Selecteffect001.png",
	"data/TEXTURE/Selecteffect002.png",
	"data/TEXTURE/Selecteffect003.png",
	"data/TEXTURE/Selecteffect000.png",
	"data/TEXTURE/Selecteffect010.png",
	"data/TEXTURE/Selecteffect999.png",
	"data/TEXTURE/Selecteffect999-1.png",
	"data/TEXTURE/matching.png",
	"data/TEXTURE/ready.png",
	"data/TEXTURE/win.png",
	"data/TEXTURE/lose.png",
	"data/TEXTURE/replay.png",
	"data/TEXTURE/GameClear2.jpg",
	"data/TEXTURE/GameClear3.jpg"
	*/
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect :: CEffect():Cform2D(OBJTYPE_2D,7)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect :: ~CEffect(void)
{
}
//=============================================================================
// CEffect����
//=============================================================================
CEffect *CEffect::Create(LPDIRECT3DDEVICE9 pDevice,EffectNum nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot,float width,float height)
{
	CEffect *pform2D;

	pform2D = new CEffect();
	pform2D->Init(pDevice,nType,movePos,moveRot,width,height);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CEffect::Init(LPDIRECT3DDEVICE9 pDevice, EffectNum nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height)
{
	m_pDevice = pDevice;
	//�t�B�[���h�̏�����
	Cform2D::Init(m_pDevice, m_apTextureName[(int)nType], pos, rot, width, height);

	m_nCount = 0;
	m_nCountFade = 0;
	m_nCountFadeMax = 0;

	m_effectPhase = NOT_VIEW;
	m_FadeType = UP;

	m_firstPos = Cform2D::GetPos();
	m_startPos = D3DXVECTOR2(0.0f, 0.0f);
	m_distPos = D3DXVECTOR2(0.0f, 0.0f);

	m_nCountFadeA = 0;
	m_FadeTypeA = UP;

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CEffect :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CEffect :: Update(void)
{
	switch (m_effectPhase)
	{
		case NOT_VIEW :break;

		case VIEW:	Cform2D::Update();
					break;
		case COUNT_VIEW:
						//�X�V�Ăяo��
						Cform2D::Update();
						if (m_nCount<0)
						{
							m_nCount = 0;
							if (m_nCountFadeA != 0){ FadeOut(m_nCountFadeA, m_FadeTypeA); m_nCountFadeA = 0; }
							else{ m_effectPhase = NOT_VIEW; }
						}
						else
						{
							m_nCount--;
						}
						break;
		case FADE_IN:
						if (m_nCountFade<0)
						{
							m_nCountFade = 0;
							m_effectPhase = VIEW;
						}
						else
						{
							m_nCountFade--;
							FadeMove();
						}
						Cform2D::Update();
						break;
		case FADE_IN_COUNT:
						if (m_nCountFade<0)
						{
							m_nCountFade = 0;
							m_effectPhase = COUNT_VIEW;
						}
						else
						{
							m_nCountFade--;
							FadeMove();
						}
						Cform2D::Update();
						break;
		case FADE_IN_OUT:
						if (m_nCountFade<0)
						{
							m_nCountFade = 0;
							m_effectPhase = COUNT_VIEW;
						}
						else
						{
							m_nCountFade--;
							FadeMove();
						}
						Cform2D::Update();
						break;
		case FADE_OUT:
						if (m_nCountFade<0)
						{
							m_nCountFade = 0;
							m_effectPhase = NOT_VIEW;
						}
						else
						{
							m_nCountFade--;
							FadeMove();
						}
						Cform2D::Update();
						break;
		default:	break;
	}
}
//=============================================================================
// �`��
//=============================================================================
void CEffect :: Draw(void)
{
	if (m_effectPhase != NOT_VIEW)
	{
		Cform2D::Draw();
	}
}
//=============================================================================
// �t�F�[�h�C��
//=============================================================================
void CEffect::FadeIn(int time, EFFECT_FADE type)
{
	m_effectPhase = FADE_IN;
	m_FadeType = type;
	D3DXVECTOR2 start = Cform2D::GetLengthWH()*0.5f;
	D3DXVECTOR3 pos = m_firstPos;

	switch (m_FadeType)
	{
		case UP:	m_startPos = D3DXVECTOR2(pos.x, -start.y);	break;
		case DOWN:	m_startPos = D3DXVECTOR2(pos.x, SCREEN_HEIGHT + start.y);	break;
		case RIGHT:	m_startPos = D3DXVECTOR2(SCREEN_WIDTH + start.x, pos.y);	break;
		case LEFT:	m_startPos = D3DXVECTOR2(-start.x, pos.y);	break;
		case UP_LEFT:	m_startPos = D3DXVECTOR2(-start.x, -start.y);	break;
		case DOWN_RIGHT:	m_startPos = D3DXVECTOR2(SCREEN_WIDTH + start.x, SCREEN_HEIGHT + start.y);	break;

	}

	m_distPos = D3DXVECTOR2(pos.x,pos.y);
	m_nCountFade = time;
	m_nCountFadeMax = time;

	Cform2D::SetPos(D3DXVECTOR3(m_startPos.x, m_startPos.y, 0.0f));
};

//=============================================================================
// �t�F�[�h�A�E�g
//=============================================================================
void CEffect::FadeOut(int time, EFFECT_FADE type)
{
	m_effectPhase = FADE_OUT;
	m_FadeType = type;
	D3DXVECTOR2 start = Cform2D::GetLengthWH()*0.5f;
	D3DXVECTOR3 pos = m_firstPos;

	m_startPos = D3DXVECTOR2(pos.x, pos.y);

	switch (m_FadeType)
	{
		case UP:	m_distPos = D3DXVECTOR2(pos.x, -start.y);	break;
		case DOWN:	m_distPos = D3DXVECTOR2(pos.x, SCREEN_HEIGHT + start.y);	break;
		case RIGHT:	m_distPos = D3DXVECTOR2(SCREEN_WIDTH + start.x, pos.y);	break;
		case LEFT:	m_distPos = D3DXVECTOR2(-start.x, pos.y);	break;
		case UP_LEFT:	m_distPos = D3DXVECTOR2(-start.x, -start.y);	break;
		case DOWN_RIGHT:	m_distPos = D3DXVECTOR2(SCREEN_WIDTH + start.x, SCREEN_HEIGHT + start.y);	break;
	}

	Cform2D::SetPos(D3DXVECTOR3(m_startPos.x, m_startPos.y, 0.0f));
	m_nCountFade = time;
	m_nCountFadeMax = time;
};
//=============================================================================
// �t�F�[�h�ړ�
//=============================================================================
void CEffect::FadeMove(void)
{
	float time = 1.0f-(m_nCountFade / m_nCountFadeMax);

	float ret;
	if (time < 0.5f)
	{
		ret = (2 * time)*(2 * time)*(2 * time)*0.5f;
	}
	else
	{
		ret = (2 * time - 2.0f)*(2 * time - 2.0f)*(2 * time - 2.0f)*0.5f + 1.0f;
	}

	D3DXVECTOR2 pos;
	pos = (m_distPos - m_startPos)*ret + m_startPos;

	Cform2D::SetPos(D3DXVECTOR3(pos.x,pos.y,0.0f));
}

//
void CEffect::FadeInAfterCount(int fadeTime, EFFECT_FADE type, int viewTime)
{
	FadeIn(fadeTime,type);
	m_effectPhase = FADE_IN_COUNT;
	m_nCount = viewTime;
}

//
void CEffect::FadeInAfterFadeOut(int fadeInTime, EFFECT_FADE intype, int viewTime, int fadeOutTime, EFFECT_FADE outtype)
{
	FadeIn(fadeInTime, intype);
	m_effectPhase = FADE_IN_OUT;
	m_nCount = viewTime;
	m_nCountFadeA = fadeOutTime;
	m_FadeTypeA = outtype;

}

/////////////EOF////////////