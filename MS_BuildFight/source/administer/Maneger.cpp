//=============================================================================
//
// MS_BuildFight [CManager.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include <time.h>
#include <process.h>
#include <stdio.h>
#include <direct.h>

#include "Maneger.h"
#include "Renderer.h"
#include "Input.h"
#include "Sound.h"
#include "Debugproc.h"

#include "scene/Scene.h"
#include "scene/Title.h"
#include "scene/Select.h"
#include "scene/StageSelect.h"
#include "scene/Game.h"
#include "scene/Result.h"
#include "scene/Tutorial.h"
#include "scene/GameClear.h"
#include "scene/Vsend.h"

#include "../form/form.h"

#include "../module/etc/Light.h"
#include "../module/etc/Camera.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DDEVICE9 CManager::m_pD3DDevice = NULL;		// �f�o�C�X�̃|�C���^
CInputKeyboard* CManager::m_pKeyboard = NULL;			//�C���v�b�g
CInputMouse * CManager ::m_pMouse = NULL;
CInputJoypad * CManager ::m_pJoypad = NULL;

CSound *CManager::m_pSound = NULL;						//�T�E���h

CScene	*CManager::m_pScene = NULL;						//�t�F�[�Y

CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;						// ���C�g

PHASETYPE CManager::m_phaseType = PHASETYPE_TITLE;			//�t�F�[�Y�̃^�C�v
PHASETYPE CManager::m_afterSceneType = PHASETYPE_TITLE;

HWND CManager::m_hwnd = NULL;

#ifdef _DEBUG
CDebugProc *CManager::m_pDebugProc = NULL;				// �f�o�b�O
#endif

bool CManager::m_pauseFlag = false;
bool CManager::m_gameEndFlag = false;
bool CManager::m_night0PlayFlag = false;

//�C���v�b�g
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager :: CManager(void)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager :: ~CManager(void)
{
}
//=============================================================================
// ������
//=============================================================================
HRESULT CManager :: Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	//����������
	srand( (unsigned int)time( NULL ) );

	RenderInit(hWnd, bWindow);

	//�T�E���h�̏�����
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	//�L�[�{�[�h�̏�����
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance,hWnd);

	//�}�E�X�̏�����
	m_pMouse = new CInputMouse();
	m_pMouse->Init(hInstance,hWnd);

	//�W���C�p�b�h�̏�����
	//m_pJoypad = new CInputJoypad();
	//m_pJoypad->Init(hInstance,hWnd);

	// ���C�g����������
	m_pLight = new CLight;
	m_pLight->Init(m_pD3DDevice);

	m_pCamera = new CCamera;
	m_pCamera->Init();

	//�t�F�[�Y�̏�����
	m_pScene=new CTitle();
	m_pScene->Init(m_pD3DDevice);

#ifdef _DEBUG
		//�f�o�b�N�\���̏�����
		m_pDebugProc = new CDebugProc;
		m_pDebugProc->Init(m_pD3DDevice);
#endif

	//�t�F�[�Y�̐ݒ�
	m_phaseType=PHASETYPE_TITLE;
	m_afterSceneType=m_phaseType;
	m_pauseFlag=false;
	m_gameEndFlag=false;

	m_nCountform = 0;
	m_bWirerFlag = false;

	m_hwnd = hWnd;

	return S_OK;
}
//=============================================================================
// �����_���\������
//=============================================================================
HRESULT CManager::RenderInit(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	//SetShader();

	//�o�b�N�o�b�t�@�i�J���[�j�T�[�t�F�X�̕ۑ�
	if (FAILED(m_pD3DDevice->GetRenderTarget(0, &m_pSurfaceBack)))
	{
		// ���������s
		MessageBox(NULL, "�o�b�N�o�b�t�@(�J���[)�T�[�t�F�X�̕ۑ��G���[", "error", MB_OK);
		return E_FAIL;
	};

	//�o�b�N�o�b�t�@�i�y�j�T�[�t�F�X�̕ۑ�
	if (FAILED(m_pD3DDevice->GetDepthStencilSurface(&m_pSurfaceBackD)))
	{
		// ���������s
		MessageBox(NULL, "�o�b�N�o�b�t�@(Z)�T�[�t�F�X�̕ۑ��G���[", "error", MB_OK);
		return E_FAIL;
	};

	//�r���[�|�[�g�̕ۑ�
	m_pD3DDevice->GetViewport(&m_pViewport);

	for (int i = 0; i < 5; i++)
	{
		m_renderTargets[i] = new RenderTagets;
		RemoveRenderTargets(i);
	}

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CManager :: Uninit(void)
{

	//���������[�N�`�F�b�N
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	m_pCamera->Uninit();	//�J����

	if (m_pCamera != NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	m_pLight->Uninit();

	if (m_pLight != NULL)
	{
		delete m_pLight;
		m_pLight = NULL;
	}

	//�V�[����S�ďI��
	Cform::ReleaseAll();

	for (int i = 0; i < 5; i++)
	{
		delete m_renderTargets[i];
	}

	SafeRelease(&m_pD3D);
	SafeRelease(&m_pD3DDevice);

	//�e�I������
	m_pScene->Uninit();		//�t�F�[�Y

	if(m_pScene!=NULL)
	{
		delete m_pScene;
		m_pScene=NULL;
	}

	m_pMouse->Uninit();		//�}�E�X

	if(m_pMouse!=NULL)
	{
		delete m_pMouse;
		m_pMouse = NULL;
	}

	m_pKeyboard->Uninit();	//�L�[�{�[�h

	if(m_pKeyboard!=NULL)
	{
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	m_pSound->Uninit();		//�T�E���h

	if (m_pSound != NULL)
	{
		delete m_pSound;
		m_pSound = NULL;
	}

	//m_pJoypad->Uninit();		//�W���C�p�b�h

	//if(m_pJoypad!=NULL)
	//{
	//	delete m_pJoypad;
	//	m_pJoypad = NULL;
	//}

#ifdef _DEBUG
	if(m_pDebugProc)		//�f�o�b�N�\��
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
#endif
}
//=============================================================================
// �X�V
//=============================================================================
void CManager :: Update(void)
{
#pragma omp parallel sections

#pragma omp section
	//�e�X�V����
	m_pKeyboard->Update();
	m_pMouse->Update();
	//m_pJoypad->Update();
	m_pScene->Update();

	//�t�F�[�Y�̕ύX
	ChangeScene();

#pragma omp section

	//�J�����X�V
	m_pCamera->Update();

	// �`�揈��
	if(!(m_phaseType==PHASETYPE_GAME))
	{
		Cform::UpdateAll();
	}else if(m_pauseFlag)
	{
		Cform::UpdatePause();
	}else if(m_gameEndFlag)
	{
		Cform::UpdateGameEnd();
	}else
	{
		Cform::UpdateGame();
	}

	// �X�N���[���V���b�g
	if (m_pKeyboard->GetKeyTrigger(DIK_F11))
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
void CManager :: Draw(void)
{
	//�`��p������
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 100, 100, 0), 1.0f, 0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))//�`��̊J�n
	{
		//�J�����̐ݒ�
		m_pCamera->Set(m_pD3DDevice);

		m_pScene->Draw();

#ifdef _DEBUG
		// �f�o�b�O����
		CDebugProc::Draw();
#endif
		m_pD3DDevice->EndScene();//�`��̏I��
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
// �V�[���o�^�p
//=============================================================================
void CManager::Addform(Cform* pform)
{
	if (m_nCountform<SCENE_MAX)
	{
		m_apforms[m_nCountform] = pform;
		m_nCountform++;
	}
}
//=============================================================================
// �t�F�[�Y�ύX
//=============================================================================
void CManager::ChangeScene(void)
{
	static int frame;
	static int enemy;
	static int map;
	static int time;
	static int score;
	static bool vs;
	static bool replay;
	//���̃t�F�[�Y�����̃t�F�[�Y���Ⴄ�ꍇ
	if(m_afterSceneType!=m_phaseType)
	{
		switch(m_afterSceneType)
		{
			//���̃t�F�[�Y���^�C�g��
			case PHASETYPE_TITLE:
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CTitle();
							m_pScene->Init(m_pD3DDevice);
							break;
			//���̃t�F�[�Y���`���[�g���A��
			case PHASETYPE_TUTRIAL:
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CTutorial();
							m_pScene->Init(m_pD3DDevice);
							break;
			//���̃t�F�[�Y���Z���N�g
			case PHASETYPE_SELECT:
							replay=m_pScene->GetReplayFlag();
							vs=m_pScene->GetVSFlag();
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CSelect();
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
							//���̃t�F�[�Y���Z���N�g
			case PHASETYPE_STAGE_SELECT:
							replay = m_pScene->GetReplayFlag();
							vs = m_pScene->GetVSFlag();
							m_pScene->Uninit();
							delete m_pScene;
							m_pScene = NULL;
							m_pScene = new CStageSelect();
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
			//���̃t�F�[�Y�����[�h
			case PHASETYPE_LOAD:
							break;
			//���̃t�F�[�Y���Q�[��
			case PHASETYPE_GAME:
							frame=m_pScene->GetFrame();
							enemy=m_pScene->GetEnemy();
							map=m_pScene->GetMap();
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();
							vs=m_pScene->GetVSFlag();
							replay=m_pScene->GetReplayFlag();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene = new CGame();

							m_pScene->SetFrame(frame);
							m_pScene->SetEnemy(enemy);
							m_pScene->SetMap(map);
							m_pScene->SetTime(time);
							m_pScene->SetScore(score);
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
			//���̃t�F�[�Y���N���A
			case PHASETYPE_CLEAR:
							frame=m_pScene->GetFrame();
							map=m_pScene->GetMap();
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();
							vs=m_pScene->GetVSFlag();
							replay = m_pScene->GetReplayFlag();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CGameClear();

							m_pScene->SetFrame(frame);
							m_pScene->SetMap(map);
							m_pScene->SetTime(time);
							m_pScene->SetScore(score);
							m_pScene->SetVSFlag(vs);
							m_pScene->SetReplayFlag(replay);
							m_pScene->Init(m_pD3DDevice);
							break;
			//���̃t�F�[�Y���ΐ�I��
			case PHASETYPE_VSEND:
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();
							vs=m_pScene->GetVSFlag();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene=new CVsend();

							m_pScene->SetTime(time);
							m_pScene->SetScore(score);
							m_pScene->SetVSFlag(vs);

							m_pScene->Init(m_pD3DDevice);
							break;

			//���̃t�F�[�Y�����U���g
			case PHASETYPE_RESULT:
							time=m_pScene->GetTime();
							score=m_pScene->GetScore();

							m_pScene->Uninit();
							delete m_pScene;
							m_pScene=NULL;
							m_pScene = new CResult();

							m_pScene->SetTime(time);
							m_pScene->SetScore(score);

							m_pScene->Init(m_pD3DDevice);
							break;
		}
		//���̃t�F�[�Y�Ɏ��̃t�F�[�Y������
		m_phaseType=m_afterSceneType;
	}
}

//=============================================================================
// �����_�[�^�[�Q�b�g�̍쐬
//=============================================================================
int CManager::SetRenderTargets(float width, float height)
{
	int rendernum;

	for (rendernum = 0; rendernum < 5; rendernum++)
	{
		if (m_renderTargets[rendernum]->surface == NULL)
		{
			break;
		}
	}
	//�e�N�X�`���쐬
	if (FAILED(m_pD3DDevice->CreateTexture(width,		//��
		height,			//����
		1,						//�~�b�v�}�b�v���x��
		D3DUSAGE_RENDERTARGET,	//�g�p���@
		D3DFMT_A8R8G8B8,		//�t�H�[�}�b�g
		D3DPOOL_DEFAULT,		//�������Ǘ����@
		&m_renderTargets[rendernum]->texture,			//�e�N�X�`���[�|�C���^
		NULL)))					//��
	{
		// ���������s
		MessageBox(NULL, "Render�p�e�N�X�`���������G���[", "error", MB_OK);
		return E_FAIL;
	};

	//�����_�����O�^�[�Q�b�g�p�T�[�t�F�X�̎擾
	if (FAILED(m_renderTargets[rendernum]->texture->GetSurfaceLevel(0, &m_renderTargets[rendernum]->surface)))
	{
		// ���������s
		MessageBox(NULL, "�����_�����O�^�[�Q�b�g�p�T�[�t�F�X�̎擾�G���[", "error", MB_OK);
		return E_FAIL;
	};

	//�y�o�b�t�@�̃T�[�t�F�X�擾
	if (FAILED(m_pD3DDevice->CreateDepthStencilSurface(width,	//��(�e�N�X�`���Ɠ���)
		height,					//����(�e�N�X�`���Ɠ���)
		D3DFMT_D16,						//�t�H�[�}�b�g
		D3DMULTISAMPLE_NONE,			//�}���`�T���v�����O���x���i�j
		0,								//�}���`�T���v�����O�i��
		TRUE,
		&m_renderTargets[rendernum]->surfaceDepth,			//�T�[�t�F�X�C���^�[�t�F�[�X�|�C���^
		NULL)))							//
	{
		// ���������s
		MessageBox(NULL, "�y�o�b�t�@�̃T�[�t�F�X�擾�G���[", "error", MB_OK);
		return E_FAIL;
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_renderTargets[rendernum]->vtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_renderTargets[rendernum]->vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].hrw =
			pVtx[1].hrw =
			pVtx[2].hrw =
			pVtx[3].hrw = 1.0f;

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = 0.0f;
		pVtx[0].vtx.y = 0.0f;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = width;
		pVtx[1].vtx.y = 0.0f;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = 0.0f;
		pVtx[2].vtx.y = height;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = width;
		pVtx[3].vtx.y = height;
		pVtx[3].vtx.z = 0.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_renderTargets[rendernum]->vtxBuff->Unlock();
	}

	return rendernum;
}

void CManager::RemoveRenderTargets(int i)
{
	m_renderTargets[i]->surface = NULL;
	m_renderTargets[i]->surfaceDepth = NULL;
	m_renderTargets[i]->texture = NULL;
	m_renderTargets[i]->vtxBuff = NULL;
}

HRESULT CManager::SetShader(void)
{
	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�
	hr = D3DXCompileShaderFromFile("basicPS.hlsl", NULL, NULL, "PS_BN_CHECK", "ps_2_0", 0, &code, &err, &_psc[0]);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return E_FAIL;
	}
	//�V�F�[�_�[�̓o�^
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps[0]);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return E_FAIL;
	}

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�
	hr = D3DXCompileShaderFromFile("basicPS.hlsl", NULL, NULL, "PS_GAUS_W", "ps_2_0", 0, &code, &err, &_psc[1]);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return E_FAIL;
	}
	//�V�F�[�_�[�̓o�^
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps[1]);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return E_FAIL;
	}

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�
	hr = D3DXCompileShaderFromFile("basicPS.hlsl", NULL, NULL, "PS_GAUS_H", "ps_2_0", 0, &code, &err, &_psc[2]);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return E_FAIL;
	}
	//�V�F�[�_�[�̓o�^
	hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps[2]);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
/////////////EOF////////////