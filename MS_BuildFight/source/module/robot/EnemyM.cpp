//=============================================================================
//
// MS_BuildFight [CEnemyM.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "EnemyM.h"
#include "Model.h"
#include "robotmotiondata.h"
#include "robotmotiondataGN3.h"

#include "../field/Field.h"

#include "../etc/Camera.h"

#include "../ui/Gauge.h"
#include "../ui/Score.h"
#include "../ui/Effect.h"
#include "../ui/Icon.h"

#include "../../form/formX.h"

#include "../../administer/Maneger.h"
#include "../../administer/debugproc.h"
#include "../../administer/Sound.h"

#include "../../administer/scene/Game.h"
#include "../../exten_common.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyM :: CEnemyM(int nPriority) : Cform(OBJTYPE_ENEMY,nPriority)
{
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		m_pD3DTex[i]=NULL;
	}
	
	m_nTextureNum=0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyM :: ~CEnemyM(void)
{
}
//=============================================================================
// CEnemyM����
//=============================================================================
CEnemyM *CEnemyM::Create(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot,bool CPU)
{
	CEnemyM *pformX;

	pformX = new CEnemyM();
	pformX->Init(pDevice,nTypeModel,movePos,moveRot,CPU);

	return pformX;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CEnemyM :: Init(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	//�f�o�C�X�̎擾
	m_pDevice=pDevice;

	//�^�C�v�̕ۑ�
	m_nType=nTypeModel;
	int modeltype = nTypeModel+1;
	if (modeltype == 5)
	{
		modeltype = 0;
	}
	for (int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = CModel::Create(pDevice, nCntModel, modeltype * 12,
			D3DXVECTOR3(g_aKeyDef[nCntModel][0], g_aKeyDef[nCntModel][1], g_aKeyDef[nCntModel][2]),
			D3DXVECTOR3(g_aKeyDef[nCntModel][3], g_aKeyDef[nCntModel][4], g_aKeyDef[nCntModel][5]));
	}

	// ���f���p�[�c�K�w�\���ݒ�
	m_apModel[0]->SetParent(NULL);			// [0]��   �� (�e)NULL
	m_apModel[1]->SetParent(m_apModel[0]);	// [1]��   �� (�e)[0]��
	m_apModel[2]->SetParent(m_apModel[0]);	// [2]�E�r �� (�e)[0]��
	m_apModel[3]->SetParent(m_apModel[2]);	// [3]�E�� �� (�e)[2]�E�r
	m_apModel[4]->SetParent(m_apModel[3]);	// [3]�E�� �� (�e)[2]�E�r
	m_apModel[5]->SetParent(m_apModel[0]);	// [4]���r �� (�e)[0]��
	m_apModel[6]->SetParent(m_apModel[5]);	// [5]���� �� (�e)[4]���r
	m_apModel[7]->SetParent(m_apModel[6]);	// [5]���� �� (�e)[4]���r
	m_apModel[8]->SetParent(m_apModel[0]);	// [6]�E�� �� (�e)[0]��
	m_apModel[9]->SetParent(m_apModel[8]);	// [7]�E�� �� (�e)[6]�E��
	m_apModel[10]->SetParent(m_apModel[0]);	// [8]���� �� (�e)[0]��
	m_apModel[11]->SetParent(m_apModel[10]);	// [9]���� �� (�e)[8]����

	//�e�N�X�`���ݒ�
	SetTexture("data/TEXTURE/toumei3.png",1);
	SetTexture("data/TEXTURE/toumei.png",2);
	SetTexture("data/TEXTURE/toumei5.png",3);

	m_Pos = pos;
	m_PosOld = pos;
	m_Rot = rot;
	m_rotDestModel = rot;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bJump = false;
	m_fHeightField = 0.0f;

	//�p�[�c�������i�[
	m_nNumModel = MODELPARTS_MAX;

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;

	m_nCountMotion = 0;
	m_bLoopMotion = false;
	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;
	m_bDispDebug = true;

	m_bCPUFlag=CPU;
	m_move=MOVE_UP;
	m_moveCnt=0;

	m_fPosHightPlus=0.0f;
	m_nEffectFinishCount=0;

	m_Min=D3DXVECTOR3(-30.0f,-20.0f,-30.0f);
	m_Max=D3DXVECTOR3(30.0f,20.0f,30.0f);

	// �A�j���[�V�����ݒ�
	SetMotion(MOTIONTYPE_NEUTRAL);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CEnemyM :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����

	// ���f���̊J��
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		if(m_apModel[nCntModel])
		{
			m_apModel[nCntModel]->Uninit();
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}
	}

	if(m_pKeyInfo)
	{
		m_pKeyInfo = NULL;
	}

	// �e�N�X�`���̊J��
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		if(m_pD3DTex[i]!=NULL)
		{
			m_pD3DTex[i]->Release();
			m_pD3DTex[i]=NULL;
		}
	}

	Cform::Release();

}
//=============================================================================
// �ĊJ
//=============================================================================
void CEnemyM :: Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_Pos = pos;
	m_PosOld = pos;
	m_Rot = rot;
	m_rotDestModel = rot;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bJump = false;
	m_fHeightField = 0.0f;

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;
	m_nCountMotion = 0;
	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	m_move=MOVE_UP;
	m_moveCnt=0;
	m_fPosHightPlus=0.0f;
	m_nEffectFinishCount=0;

	SetTextureNum(0);

	// �A�j���[�V�����ݒ�
	SetMotion(MOTIONTYPE_NEUTRAL);
}
//=============================================================================
// �X�V
//=============================================================================
void CEnemyM :: Update(void)
{

	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CSound	*pSound;
	pSound = CManager::GetSound();

	CPlayerM *pPlayerM;
	pPlayerM = CGame::GetPlayer(0);

	D3DXVECTOR3 playerPos = pPlayerM->GetPos();

	//�@���i�܂����g�p�j
	D3DXVECTOR3 normal;

	//�ϐ���`
	float fDiffRotY=0;

	// �O��̈ʒu��ۑ�
	m_PosOld = m_Pos;

	if(m_bCPUFlag)
	{
		//�ړ��p�J�E���g�̊m�F
		if(m_moveCnt>30)
		{
			//�p�^�[���̌���i�����j
			m_move=(MOVE)(rand()%MOVE_MAX);
			//�J�E���g�̏�����
			m_moveCnt=0;
		}else
		{
			//�J�E���g�̑���
			m_moveCnt++;
		}

		if(!m_bJump){
			if(m_motionType != MOTIONTYPE_DOWN)
			{
				switch(m_move)
				{
					//�����
					case MOVE_UP:
								m_Move.x = sinf(GetRotCamera().y)*VALUE_MOVE_PLAYER;
								m_Move.z = cosf(GetRotCamera().y)*VALUE_MOVE_PLAYER;
								break;
					//������
					case MOVE_DOWN:
								m_Move.x = -sinf(GetRotCamera().y)*VALUE_MOVE_PLAYER;
								m_Move.z = -cosf(GetRotCamera().y)*VALUE_MOVE_PLAYER;
								break;
					//�E����
					case MOVE_RIGHT:
								m_Move.x = sinf(GetRotCamera().y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
								m_Move.z = cosf(GetRotCamera().y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
								break;
					//������
					case MOVE_LEFT:
								m_Move.x = -sinf(GetRotCamera().y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
								m_Move.z = -cosf(GetRotCamera().y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
								break;
					//��~
					case MOVE_STAY:
								m_Move.x =0;
								m_Move.z =0;
								break;
					case MOVE_JUMP:
								m_Move.y = VALUE_JUMP;
								m_bJump = true;
								// �W�����v���[�V�����Đ�
								SetMotion(MOTIONTYPE_JUMP);
								break;
				}
			}
		}

		// �͈̓`�F�b�N
		if(m_Pos.x > 900.0f-PLAYER_SIZE)
		{
			m_Pos.x = 900.0f-PLAYER_SIZE;
		}
		if(m_Pos.x < -900.0f+PLAYER_SIZE)
		{
			m_Pos.x = -900.0f+PLAYER_SIZE;
		}
		if(m_Pos.z > 900.0f-PLAYER_SIZE)
		{
			m_Pos.z = 900.0f-PLAYER_SIZE;
		}
		if(m_Pos.z < -900.0f+PLAYER_SIZE)
		{
			m_Pos.z = -900.0f+PLAYER_SIZE;
		}
		if(m_Pos.y > 700.0f+PLAYER_SIZE)
		{
			m_Pos.y=700.0f+PLAYER_SIZE;
		}

		// �ړI�̊p�x�܂ł̍���
		fDiffRotY = Rotation_Normalizer(m_rotDestModel.y - m_Rot.y);

		// �ړI�̊p�x�܂Ŋ�����������
		m_Rot.y += fDiffRotY * RATE_ROTATE_PLAYER;

		m_Rot.y = Rotation_Normalizer(m_Rot.y);
		// �d�͂�������
		m_Move.y -= GRAVITY * 0.05f;

		if(m_motionType!=MOTIONTYPE_DOWN)
		{
			//�����̐ݒ�i��Ɏ��@�̕��Ɍ����悤�Ɂj
			m_Rot.y = atan2f((m_Pos.x-playerPos.x),(m_Pos.z-playerPos.z));
		}

		float Distance = 0.0f;
		Distance = (float)sqrt((double)(m_Pos.x - playerPos.x)*(double)(m_Pos.x - playerPos.x) + (double)(m_Pos.y - playerPos.y)*(double)(m_Pos.y - playerPos.y) + (double)(m_Pos.z - playerPos.z)*(double)(m_Pos.z - playerPos.z));

		// �ʒu�ړ�
		m_Pos.x += m_Move.x;
		m_Pos.y += m_Move.y;
		m_Pos.z += m_Move.z;

		m_Move.x += (0.0f - m_Move.x) * REGIST_MOVE;
		m_Move.z += (0.0f - m_Move.z) * REGIST_MOVE;

		//�t�B�[���h�Ƃ̓����蔻��
		m_fHeightField = 0.0f;

		if(m_Pos.y <= m_fHeightField)
		{
			if(m_bJump == true)
			{
				m_Move.x *= 0.005f;
				m_Move.z *= 0.005f;

				// ���n���[�V�����Đ�
				SetMotion(MOTIONTYPE_LANDING);
				//pSound->Play(SOUND_LABEL_SE_LANDING);
			}

			m_Pos.y = m_fHeightField;
			m_Move.y = 0.0f;
			m_bJump = false;
		}

		if(m_bJump == false)
		{
			if(m_Move.x <= 0.005f && m_Move.x >= -0.005f
			&& m_Move.z <= 0.005f && m_Move.z >= -0.005f)
			{
				if(m_motionType == MOTIONTYPE_RUN
				|| m_motionType == MOTIONTYPE_TURBO
				|| (m_motionType == MOTIONTYPE_LANDING && IsFinishMotion() == true))
				{// ���胂�[�V����/���n���[�V�����I��
					// �j���[�g�������[�V�����Đ�
					SetMotion(MOTIONTYPE_NEUTRAL);
				}
			}
			else
			{
				if(m_motionType == MOTIONTYPE_NEUTRAL
				|| m_motionType == MOTIONTYPE_TURBO
				|| m_motionType == MOTIONTYPE_LANDING)
				{
					// ���胂�[�V�����Đ�
					SetMotion(MOTIONTYPE_RUN);
				}
			}
		}
	}else
	{

	}

	if(m_bCPUFlag==false)
	{
		if((m_motionType == MOTIONTYPE_PUNCH_W && IsFinishMotion() == true)
		|| (m_motionType == MOTIONTYPE_PUNCH_S && IsFinishMotion() == true))
		{// �p���`���[�V�����I��
		}

		if((m_motionType == MOTIONTYPE_KICK_W && IsFinishMotion() == true)
		|| (m_motionType == MOTIONTYPE_KICK_S && IsFinishMotion() == true))
		{// �L�b�N���[�V�����I��
		}

		if((m_motionType == MOTIONTYPE_ATTACK && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_ATTACKDAMEGE && IsFinishMotion() == true))
		{// �A�^�b�N���[�V�����I��
			m_bJump=true;
		}
	}else
	{
		if((m_motionType == MOTIONTYPE_PUNCH_W && IsFinishMotion() == true)
		|| (m_motionType == MOTIONTYPE_PUNCH_S && IsFinishMotion() == true))
		{// �p���`���[�V�����I��
			// �j���[�g�������[�V�����Đ�
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_KICK_W && IsFinishMotion() == true)
		|| (m_motionType == MOTIONTYPE_KICK_S && IsFinishMotion() == true))
		{// �L�b�N���[�V�����I��
			// �j���[�g�������[�V�����Đ�
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_SHOT && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_DAMAGE && IsFinishMotion() == true))
		{// �V���b�g���[�V�����I��
			// �j���[�g�������[�V�����Đ�
			SetMotion(MOTIONTYPE_NEUTRAL);
		}
		if(m_motionType == MOTIONTYPE_DOWN && IsFinishMotion() == true)
		{// �_�E�����[�V�����I��
			// �j���[�g�������[�V�����Đ�
			SetMotion(MOTIONTYPE_NEUTRAL);
		}
		if((m_motionType == MOTIONTYPE_OVER_LOAD && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_OVER_LOAD2 && IsFinishMotion() == true))
		{// �X�L�����[�V�����I��
			// �j���[�g�������[�V�����Đ�
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_ATTACK && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_ATTACKDAMEGE && IsFinishMotion() == true))
		{// �A�^�b�N���[�V�����I��
			// �j���[�g�������[�V�����Đ�
			m_bJump=true;
			SetMotion(MOTIONTYPE_JUMP);
		}
	}
		
	// �A�j���[�V�����X�V
	UpdateMotion();

}
//=============================================================================
// �`��
//=============================================================================
void CEnemyM :: Draw(void)
{

	D3DXMATRIX mtxScale,mtxRot,mtxTranslate;

	SetRotCamera(CManager::GetCamera()->GetRotCamera());

	SetMtxView(CManager::GetCamera()->GetMtxView());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���p�[�c�̕`��
	for(int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if(m_apModel[nCntModel])
		{
			//m_apModel[nCntModel]->Draw(m_pD3DTex[m_nTextureNum]);
		}
	}

	m_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
}
//=============================================================================
// ���[�V�����ݒ�
//=============================================================================
void CEnemyM::SetMotion(MOTIONTYPE motionType)
{
	switch (motionType)
	{
	case MOTIONTYPE_NEUTRAL:
		m_pKeyInfo = &g_aKeyNeutral[0];
		m_nNumKey = sizeof g_aKeyNeutral / sizeof(KEY_INFO);
		m_bLoopMotion = true;
		break;

	case MOTIONTYPE_RUN:
		m_pKeyInfo = &g_aKeyRun[0];
		m_nNumKey = sizeof g_aKeyRun / sizeof(KEY_INFO);
		m_bLoopMotion = true;
		break;

	case MOTIONTYPE_JUMP:
		m_pKeyInfo = &g_aKeyJump[0];
		m_nNumKey = sizeof g_aKeyJump / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_LANDING:
		m_pKeyInfo = &g_aKeyLanding[0];
		m_nNumKey = sizeof g_aKeyLanding / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_PUNCH_W:
		m_pKeyInfo = &g_aKeyPunchW[0];
		m_nNumKey = sizeof g_aKeyPunchW / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_PUNCH_S:
		m_pKeyInfo = &g_aKeyPunchS[0];
		m_nNumKey = sizeof g_aKeyPunchS / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_KICK_W:
		m_pKeyInfo = &g_aKeyKickW[0];
		m_nNumKey = sizeof g_aKeyKickW / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_KICK_S:
		m_pKeyInfo = &g_aKeyKickS[0];
		m_nNumKey = sizeof g_aKeyKickS / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_SHOT:
		m_pKeyInfo = &g_aKeyShot[0];
		m_nNumKey = sizeof g_aKeyShot / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_OVER_LOAD:
		m_pKeyInfo = &g_aKeyOverLoad[0];
		m_nNumKey = sizeof g_aKeyOverLoad / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_OVER_LOAD2:
		m_pKeyInfo = &g_aKeyOverLoad2[0];
		m_nNumKey = sizeof g_aKeyOverLoad2 / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_TURBO:
		m_pKeyInfo = &g_aKeyTurbo[0];
		m_nNumKey = sizeof g_aKeyTurbo / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_DAMAGE:
		m_pKeyInfo = &g_aKeyDamage[0];
		m_nNumKey = sizeof g_aKeyDamage / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_DOWN:
		m_pKeyInfo = &g_aKeyDown[0];
		m_nNumKey = sizeof g_aKeyDown / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_ATTACK:
		m_pKeyInfo = &g_aKeyAttack[0];
		m_nNumKey = sizeof g_aKeyAttack / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_ATTACKDAMEGE:
		m_pKeyInfo = &g_aKeyAttackDamage[0];
		m_nNumKey = sizeof g_aKeyAttackDamage / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;
	}

	m_motionType = motionType;
	m_nKey = 0;

	m_nCountMotion = 0;
	m_bMotion = true;
	m_bFinishMotion = false;

	if (m_apModel[0] != NULL)
	{
		// �����l�ݒ�
		for (int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
		{
			m_apModel[nCntModel]->SetPos(m_pKeyInfo->aKey[nCntModel].fPosX,
				m_pKeyInfo->aKey[nCntModel].fPosY,
				m_pKeyInfo->aKey[nCntModel].fPosZ);

			m_apModel[nCntModel]->SetRot(m_pKeyInfo->aKey[nCntModel].fRotX,
				m_pKeyInfo->aKey[nCntModel].fRotY,
				m_pKeyInfo->aKey[nCntModel].fRotZ);
		}
	}
}

//=============================================================================
// ���[�V�����X�V
//=============================================================================
void CEnemyM::UpdateMotion(void)
{
	if(m_bMotion == true)
	{// ���[�V��������
		for(int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			if(m_apModel[nCntModel])
			{// ���f������

				KEY *pKey, *pKeyNext;
				float fDiffMotion;
				float fRateMotion;

				float fPosX, fPosY, fPosZ;
				float fRotX, fRotY, fRotZ;

				// ���݂̃L�[
				pKey = &m_pKeyInfo[m_nKey].aKey[nCntModel];
				// ���̃L�[
				pKeyNext = &m_pKeyInfo[((m_nKey + 1) % m_nNumKey)].aKey[nCntModel];
				// ���݂̃L�[�̍Đ��t���[���S�̂ɑ΂��鑊�Βl
				fRateMotion = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

				// X�ړ�
				fDiffMotion = pKeyNext->fPosX - pKey->fPosX;
				fPosX = (pKey->fPosX + (fDiffMotion * fRateMotion));

				// Y�ړ�
				fDiffMotion = pKeyNext->fPosY - pKey->fPosY;
				fPosY = pKey->fPosY + (fDiffMotion * fRateMotion);

				// Z�ړ�
				fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;
				fPosZ = pKey->fPosZ + (fDiffMotion * fRateMotion);

				// X��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotX - pKey->fRotX);

				fRotX = Rotation_Normalizer(pKey->fRotX + (fDiffMotion * fRateMotion));

				// Y��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotY - pKey->fRotY);

				fRotY = Rotation_Normalizer(pKey->fRotY + (fDiffMotion * fRateMotion));

				// Z��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotZ - pKey->fRotZ);

				fRotZ = Rotation_Normalizer(pKey->fRotZ + (fDiffMotion * fRateMotion));

				if((nCntModel==0)&&((m_motionType==MOTIONTYPE_ATTACK)||(m_motionType==MOTIONTYPE_ATTACKDAMEGE)))
				{
					m_Pos.x+=fPosX;
					m_Pos.y=fPosY;
					m_Pos.z+=fPosZ;
				}
				// �ʒu(�I�t�Z�b�g)��ݒ�
				m_apModel[nCntModel]->SetPos(fPosX, fPosY, fPosZ);

				// ��]��ݒ�
				m_apModel[nCntModel]->SetRot(fRotX, fRotY, fRotZ);
			}
		}

		m_nCountMotion++;

		if(m_nCountMotion > m_pKeyInfo[m_nKey].nFrame)
		{// �L�[�̍Đ��t���[�����ɒB����
			if(m_bLoopMotion == false && (m_nKey + 2) >= m_nNumKey)
			{// �P�����[�V�����ōŏI�L�[�ɒB����
				m_bFinishMotion = true;
				m_nCountMotion = m_pKeyInfo[(m_nNumKey - 1)].nFrame;
			}
			else
			{
				m_nKey = (m_nKey + 1) % m_nNumKey;
				m_nCountMotion = 0;
			}	
		}
	}
}
void CEnemyM ::SetTexture(LPSTR pTexName,int num)
{
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex[num]);
	}else
	{
		m_pD3DTex[num]=NULL;
	}
}

D3DXVECTOR3 CEnemyM ::lerpVec(D3DXVECTOR3 a,D3DXVECTOR3 b,float per)
{
	D3DXVECTOR3 c;

	c.x=lerp(a.x,b.x,per);
	c.y=lerp(a.y,b.y,per);
	c.z=lerp(a.z,b.z,per);

	return c;
}
/////////////EOF////////////