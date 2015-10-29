//=============================================================================
//
// kadai_XXXPlus [CRenderer.cpp]
// 14/11/10
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include <stdio.h>
#include <direct.h>

#include "Renderer.h"
#include "Input.h"
#include "Maneger.h"
#include "debugproc.h"

#include "../form/form.h"

#include "../module/etc/Light.h"
#include "../module/etc/Camera.h"


CCamera *CRenderer::m_pCamera = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer :: CRenderer(void)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer :: ~CRenderer(void)
{
}
//=============================================================================
// ������
//=============================================================================
HRESULT CRenderer :: Init(HWND hWnd,BOOL bWindow)
{
	//���C�g
	CLight* pLight;

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,							// �f�B�X�v���C�^�C�v
									hWnd,									// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,									// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&m_pD3DDevice)))						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&m_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	//�l�X�ȃI�u�W�F�N�g�̏���������

	//�����_�[�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	m_nCountform=0;

	pLight=new CLight;
	pLight->Init(m_pD3DDevice);

	m_pCamera= new CCamera;
	m_pCamera->Init();

	if(pLight!=NULL)
	{
		delete pLight;
		pLight=NULL;
	}

	m_bWirerFlag=false;
	
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CRenderer :: Uninit(void)
{

	m_pCamera->Uninit();	//�J����

	if(m_pCamera!=NULL)
	{
		delete m_pCamera;
		m_pCamera=NULL;
	}

	//�V�[����S�ďI��
	Cform::ReleaseAll();

	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	SafeRelease(&m_pD3D);
	SafeRelease(&m_pD3DDevice);

}
//=============================================================================
// �X�V
//=============================================================================
void CRenderer :: Update(int nType)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���C���[�t���[���\���̐؂�ւ�
	if(pInputKeyboard->GetKeyTrigger(DIK_F1))
	{
		if(!m_bWirerFlag){
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
			m_bWirerFlag=true;
		}else{
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
			m_bWirerFlag=false;
		}
	}

	//�J�����X�V
	m_pCamera->Update();

	switch(nType)
	{
		//�V�[���̍X�V
		case 0:Cform::UpdateAll();
				break;
		case 1:Cform::UpdateGame();
				break;
		case 2:Cform::UpdatePause();
				break;
		case 3:Cform::UpdateGameEnd();
				break;
	}

	// �X�N���[���V���b�g
	if (pInputKeyboard->GetKeyTrigger(DIK_F11))
	{
		// �ϐ��錾
		LPDIRECT3DSURFACE9 pSurface;	// �摜��ۑ����邽�߂̕ϐ�
		int no = 0;						// ���łɂ������ꍇ�̕ϐ�
		char *filename;					// �ۑ�����摜�̖��O
		filename = (char *)malloc(100);
		sprintf(filename, "data/screenshot/�X�N���[���V���b�g%d.bmp", no);
		m_pD3DDevice->GetRenderTarget(0, &pSurface);
		FILE *file;
		fopen_s(&file, "./screenshot//nul", "r");
		if (file == NULL)
		{
			_mkdir("data/screenshot");
		}
		while (1)
		{
			fopen_s(&file, filename, "r");
			if (file == NULL)
			{
				//�t�@�C���͂˂���I������Z�[�u�����(�͂���)
				break;
			}
			else
			{
				//�t�@�C���͂����!�����I�����I
				no++;
				memset(filename, 0, 100);
				sprintf(filename, "data/screenshot/�X�N���[���V���b�g%d.bmp", no);
			}
		}
		D3DXSaveSurfaceToFile(filename, D3DXIFF_BMP, pSurface, NULL, NULL);
		pSurface->Release();
		filename = NULL;
	}
}
//=============================================================================
// �`��
//=============================================================================
void CRenderer :: Draw(int nType)
{
	//�`��p������
	m_pD3DDevice ->Clear(0,NULL,(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
						D3DCOLOR_RGBA(100,100,100,0),
						1.0f,
						0);


	if(SUCCEEDED(m_pD3DDevice->BeginScene()))//�`��̊J�n
	{
		//�J�����̐ݒ�
		m_pCamera->Set(m_pD3DDevice);

		switch(nType)
		{
			case 0:Cform::DrawAll(m_pCamera->GetMtxView(),m_pCamera->GetRotCamera());
					break;
			case 1:Cform::DrawGame(m_pCamera->GetMtxView(),m_pCamera->GetRotCamera());
					break;
			case 2:Cform::DrawPause(m_pCamera->GetMtxView(),m_pCamera->GetRotCamera());
					break;
		}

#ifdef _DEBUG
		// �f�o�b�O����
		CDebugProc::Draw();
#endif
		m_pD3DDevice->EndScene();//�`��̏I��
	}

	m_pD3DDevice ->Present(NULL,NULL,NULL,NULL);
}
//=============================================================================
// �V�[���o�^�p
//=============================================================================
void CRenderer::Addform(Cform* pform)
{
	if(m_nCountform<SCENE_MAX)
	{
		m_apforms[m_nCountform]=pform;
		m_nCountform++;
	}
}
/////////////EOF////////////