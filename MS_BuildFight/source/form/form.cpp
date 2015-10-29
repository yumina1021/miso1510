//=============================================================================
//
// MS_BuildFight [Cform.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "form.h"

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
// ���X�g�p
Cform *Cform::m_pTop[NUM_PRIORITY] = {};
Cform *Cform::m_pCur[NUM_PRIORITY] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Cform :: Cform(OBJTYPE objType,int nPriority)
{
	LinkList(nPriority);
	m_bDelete = false;
	m_objType=objType;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Cform :: ~Cform(void)
{

}
//=============================================================================
// ���X�g���I�u�W�F�X�V
//=============================================================================
void Cform::UpdateAll(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			// �I�u�W�F�N�g�̍X�V����
			pform->Update();

			pform = pformNext;
		}

		pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;
			if(pform->m_bDelete==true)
			{
				pform->UnlinkList();
				delete pform;
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g���I�u�W�F�X�V
//=============================================================================
void Cform::UpdateGame(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			if(!(pform->GetObjType()==OBJTYPE_PAUSE))
			{
				// �I�u�W�F�N�g�̍X�V����
				pform->Update();
			}
			pform = pformNext;
		}

		pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;
			if(pform->m_bDelete==true)
			{
				pform->UnlinkList();
				delete pform;
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g���I�u�W�F�X�V
//=============================================================================
void Cform::UpdatePause(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			if(pform->GetObjType()==OBJTYPE_PAUSE)
			{
				// �I�u�W�F�N�g�̍X�V����
				pform->Update();
			}

			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g���I�u�W�F�X�V
//=============================================================================
void Cform::UpdateGameEnd(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			if((!(pform->GetObjType()==OBJTYPE_PLAYER))&&(!(pform->GetObjType()==OBJTYPE_ENEMY))&&(!(pform->GetObjType()==OBJTYPE_TIMER)))
			{
				// �I�u�W�F�N�g�̍X�V����
				pform->Update();
			}
			pform = pformNext;
		}

		pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;
			if(pform->m_bDelete==true)
			{
				pform->UnlinkList();
				delete pform;
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g���I�u�W�F�`��
//=============================================================================
void Cform::DrawAll(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{ 
			Cform *pformNext = pform->m_pNext;

			pform->SetRotCamera(rotCamera);

			pform->SetMtxView(changeMtx);

			// �I�u�W�F�N�g�̕`�揈��
			pform->Draw();

			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g���I�u�W�F�`��
//=============================================================================
void Cform::DrawGame(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{ 
			Cform *pformNext = pform->m_pNext;

			if(!(pform->GetObjType()==OBJTYPE_PAUSE))
			{
				pform->SetRotCamera(rotCamera);

				pform->SetMtxView(changeMtx);

				// �I�u�W�F�N�g�̕`�揈��
				pform->Draw();
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g���I�u�W�F�`��
//=============================================================================
void Cform::DrawPause(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{ 
			Cform *pformNext = pform->m_pNext;

			if(pform->GetObjType()==OBJTYPE_PAUSE)
			{
				pform->SetRotCamera(rotCamera);

				pform->SetMtxView(changeMtx);

				// �I�u�W�F�N�g�̕`�揈��
				pform->Draw();
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// �I�u�W�F�N�g��j��
//=============================================================================
void Cform::Release(void)
{
	// �f���[�g�t���O�𗧂Ă�
	m_bDelete = true;
}

//=============================================================================
// �I�u�W�F�N�g�S�̂�j��
//=============================================================================
void Cform::ReleaseAll(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			// �I�u�W�F�N�g�̏I������
			pform->Uninit();

			pform->UnlinkList();

			delete pform;

			pform = pformNext;
		}
	}
}
//=============================================================================
// ���X�g�ɓo�^
//=============================================================================
void Cform::LinkList(int nPriority)
{
	// �v���C�I���e�B��ݒ�
	m_nPriority = nPriority;

	//���X�g�̐擪��������
	if(!m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = this;
	}
	//���X�g�̌��݂�������
	if(!m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = this;
	}
	//���݂̎��̃��X�g�Ɏ�����
	m_pCur[m_nPriority]->m_pNext = this;

	//���݂̃��X�g�������Ȃ�
	if(m_pCur[m_nPriority] == this)
	{
		m_pPrev = NULL;	
	}
	else
	{
		m_pPrev = m_pCur[m_nPriority];
	}
	//���݂Ɏ�����
	m_pCur[m_nPriority] = this;
	m_pNext = NULL;
}

//=============================================================================
// ���X�g����폜
//=============================================================================
void Cform::UnlinkList(void)
{
	Cform *pform, *pformNext, *pformPrev;

	pform = m_pTop[m_nPriority];
	while(pform)
	{
		//���̃C���X�^���X��ۑ�
		pformNext = pform->m_pNext;

		if(pform == this)
		{
			if(pform->m_pPrev!=NULL)
			{
				//�����e�N(�A���[�A���[)
				//�����̑O�̎��̂�������̎��̂�ɕύX
				pform->m_pPrev->m_pNext = pform->m_pNext;
			}
			if(pform->m_pNext!=NULL)
			{
				//�����̎��̑O�̂�������̑O�̂�ɕύX
				pform->m_pNext->m_pPrev = pform->m_pPrev;
			}
			if(pform == m_pTop[m_nPriority])
			{
				//
				m_pTop[m_nPriority] = pformNext;
			}
		}

		pform = pformNext;
	}
	// ���X�g�̌��݈ʒu(pCur)����擪(pTop)�Ɍ������ĒH���Ă���
	pform = m_pCur[m_nPriority];
	while(pform)
	{
		pformPrev = pform->m_pPrev;

		if(pform == this)
		{// �Ώۂ̃I�u�W�F�N�g������(this)�̏ꍇ
			if(pform->m_pPrev)
			{// �Ώۂ̃I�u�W�F�N�g�̑O�ɃI�u�W�F�N�g�����݂���ꍇ
				// ����(this)�̑O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g������(this)�̎��̃I�u�W�F�N�g�ɂ���
				pform->m_pPrev->m_pNext = pform->m_pNext;
			}
			if(pform->m_pNext)
			{// �Ώۂ̃I�u�W�F�N�g�̎��ɃI�u�W�F�N�g�����݂���ꍇ
				// ����(this)�̎��̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g������(this)�̑O�̃I�u�W�F�N�g�̂���
				pform->m_pNext->m_pPrev = pform->m_pPrev;
			}

			if(pform == m_pCur[m_nPriority])
			{// �Ώۂ̃I�u�W�F�N�g�����݂̃I�u�W�F�N�g(pCur)�̏ꍇ
				m_pCur[m_nPriority] = pformPrev;
			}
		}

		pform = pformPrev;
	}
}
/////////////EOF////////////