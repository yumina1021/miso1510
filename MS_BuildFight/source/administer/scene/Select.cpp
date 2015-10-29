//=============================================================================
//
// MS_BuildFight [CSelect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Select.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"
#include "../netClient.h"

#include "../../module/etc/Fade.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelect :: CSelect(void)
{
	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[5] = { };
	m_pEffect[6] = {};
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelect :: ~CSelect(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSelect :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_SELECT);

	//�L�����摜�z�u
	m_pEffect[0]=CEffect::Create(pDevice,Selecteffect001,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[1]=CEffect::Create(pDevice,Selecteffect002,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[2]=CEffect::Create(pDevice,Selecteffect003,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	//�����̔z�u
	m_pCharPicture[0]=CCharPicture::Create(pDevice,s_1,D3DXVECTOR3(200.0f,200.0f,0.0f),400,100);
	m_pCharPicture[1]=CCharPicture::Create(pDevice,s_2,D3DXVECTOR3(200.0f,300.0f,0.0f),400,100);
	m_pCharPicture[2]=CCharPicture::Create(pDevice,s_3,D3DXVECTOR3(200.0f,400.0f,0.0f),400,100);


	//�B���L����
	if(CManager::Getnight0PlayFlag()==true)
	{
		m_pCharPicture[3] = CCharPicture::Create(pDevice, s_0, D3DXVECTOR3(200.0f, 500.0f, 0.0f), 400, 100);
		m_pEffect[3]=CEffect::Create(pDevice,Selecteffect000,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_pCharPicture[4] = CCharPicture::Create(pDevice, n_b, D3DXVECTOR3(200.0f, 600.0f, 0.0f), 400, 100);
		m_pEffect[4] = CEffect::Create(pDevice, Selecteffect010, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		m_pCharPicture[3] = CCharPicture::Create(pDevice, s_99, D3DXVECTOR3(200.0f, 500.0f, 0.0f), 400, 100);
		m_pEffect[3] = CEffect::Create(pDevice, Selecteffect999, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pCharPicture[4] = CCharPicture::Create(pDevice, s_99, D3DXVECTOR3(200.0f, 600.0f, 0.0f), 400, 100);
		m_pEffect[4] = CEffect::Create(pDevice, Selecteffect1000, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//�}�b�`���O�ҋ@
	m_pEffect[5]=CEffect::Create(pDevice,SelecteffectMatching,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM004);

	m_bChangeFlag=false;
	m_nCursor=0;

	m_fDiffuse=1.0f;

	m_bVsSelectFlag = CScene::GetVSFlag();

	m_bTitleBackFlag=false;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_bSendData=false;

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CSelect :: Uninit(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	pSound->Stop();

	//�V�[����S�ďI��
	Cform::ReleaseAll();
}
//=============================================================================
// �X�V
//=============================================================================
void CSelect :: Update(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G�X�P�[�v�L�[�������ꂽ�ꍇ
	if(pInputKeyboard->GetKeyTrigger(DIK_ESCAPE))
	{
		// �f�[�^���M
		DATA data;

		data.Type = DATA_TYPE_EVENT;

		data.Event.Type = DATA_EVENT_TYPE_NONE;
		data.Event.Frame = 0;

		CNetClient::SendData( data );

		m_bTitleBackFlag=true;
		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
	}

	//�B���L�������g���Ȃ���ԂŉB���L�������I�΂ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z)) && CManager::Getnight0PlayFlag() == false && (m_nCursor == 3 || m_nCursor == 4) && m_bChangeFlag == false)
	{

	}else
	//�G���^�[�L�[�������ꂽ�ꍇ
	if((pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))&&m_bChangeFlag==false)
	{
		//�J�[�\���������Ă���R�}���h�𔭓�
		switch(m_nCursor)
		{
			//1���@
			case 0 :	m_bChangeFlag=true;
						CScene::SetFrame(0);
						//pSound->PlayVoice(0,VOICE_LABEL_SE_START);
						break;
			//�Q���@
			case 1 :	m_bChangeFlag=true;
						CScene::SetFrame(1);
						//pSound->PlayVoice(1,VOICE_LABEL_SE_START);
						break;
			//�R���@
			case 2 :	m_bChangeFlag=true;
						CScene::SetFrame(2);
						//pSound->PlayVoice(2,VOICE_LABEL_SE_START);
						break;
			if(CManager::Getnight0PlayFlag()==true)
			{
				//�O���@
				case 3 :	m_bChangeFlag=true;
							CScene::SetFrame(3);
							//pSound->PlayVoice(3,VOICE_LABEL_SE_START);
							break;
				//�O���@
				case 4:		m_bChangeFlag = true;
							CScene::SetFrame(4);
							//pSound->PlayVoice(3, VOICE_LABEL_SE_START);
							break;
			}
			default : break;
		}

		CScene::SetMap(0);

		if(m_bVsSelectFlag==false)
		{
			CScene::SetEnemy(rand()%3);
			if(m_pFade->GetPlayFade()==false)
			{
				//pSound->Play(SOUND_LABEL_SE_SELECT001);
				m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
			}
		}else
		{
			if(m_bSendData==false)
			{
				// �f�[�^���M
				DATA data;
				data.Type = DATA_TYPE_EVENT;
				data.Event.Type = DATA_EVENT_TYPE_START;
				data.Event.Frame = m_nCursor;
				CNetClient::SendData( data );
				m_bSendData=true;
			}
			m_pEffect[5]->SetViewFlag(true,90000);
		}
	}
	else if(m_bChangeFlag!=true)
	{
		if(pInputKeyboard->GetKeyTrigger(DIK_W)||pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pEffect[m_nCursor]->SetViewFlag(false,1);
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f,1.0f,1.0f,1.0f);
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if(m_nCursor<0)
			{
					m_nCursor=4;
			}
		}else if(pInputKeyboard->GetKeyTrigger(DIK_S)||pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pEffect[m_nCursor]->SetViewFlag(false,1);
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f,1.0f,1.0f,1.0f);
			m_nCursor++;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if(m_nCursor>4)
			{
			m_nCursor=0;
			}

		}
	}

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	m_pEffect[m_nCursor]->SetViewFlag(true,1);

	if(CNetClient::GetStartFlag()==true&&m_bChangeFlag==true)
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT002);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
		m_bChangeFlag=false;
	}

	//�t�F�[�h�C�����I�������
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		if(m_bTitleBackFlag==false)
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_GAME);
		}else
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_TITLE);
		}
	}
}
//=============================================================================
// �`��
//=============================================================================
void CSelect :: Draw(void)
{
	m_pBackGround->Draw();

	for (int i = 0; i < 5; i++)
	{
		m_pEffect[i]->Draw();
		m_pCharPicture[i]->Draw();
	}

	m_pEffect[5]->Draw();

	//�t�F�[�h�̍쐬
	m_pFade->Draw();
}
/////////////EOF////////////