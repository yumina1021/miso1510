//=============================================================================
//
// MS_BuildFight [main.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "common.h"
#include "administer/Maneger.h"
#include "administer/Renderer.h"
#include "administer/debugproc.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool GameEndFlag;
//=============================================================================
// ���C���֐�
//  (WINAPI : Win32API�֐����Ăяo�����̋K��)
//  hInstance     : ���̃A�v���P�[�V�����̃C���X�^���X�n���h��(���ʎq)
//  hPrevInstance : ���NULL(16bit����̖��c��)
//  lpCmdLine     : �R�}���h���C������󂯎���������ւ̃|�C���^
//  nCmdShow      : �A�v���P�[�V�����̏����E�C���h�E�\�����@�̎w��
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���������[�N�`�F�b�N
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�}�l�[�W���[
	CManager* pManeger;
#ifdef _DEBUG
	int nCountFPS = 0;								// FPS�J�E���^
#endif

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//�E�C���h�E�̏���
	WNDCLASSEX wcex=
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"window",
		NULL
	};

	HWND hwnd;
	MSG msg;
	GameEndFlag=false;

	//�E�C���h�E�̐ݒ�
	RegisterClassEx(&wcex);

	//�E�C���h�E�̍쐬
	hwnd=CreateWindowEx(
				0,
				"window",
				"�N���O���i�K���i�C�g-�I�[�o�[�h�o�[�T�X",
				WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				NULL,
				NULL,
				hInstance,
				NULL);

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = dwExecLastTime;
	dwCurrentTime = 0;
	dwFrameCount = 0;

	//�}�l�[�W���[�̏�����
	pManeger = new CManager;
	BOOL Rerease = FALSE;
#ifdef _DEBUG
	Rerease = TRUE;
#endif
	pManeger->Init(hInstance, hwnd, Rerease);

	//�E�C���h�E�̕\��
	ShowWindow(hwnd,nCmdShow);

	//�E�C���h�E�̍X�V
	UpdateWindow(hwnd);

	// ���b�Z�[�W���[�v
	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
#ifdef _DEBUG
				CDebugProc::Print("FPS:%d\n", nCountFPS);
#endif
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				pManeger->Update();

				// �`�揈��
				pManeger->Draw();

				dwFrameCount++;

				if(GameEndFlag)
				{
					DestroyWindow(hwnd);
				}
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass("window", wcex.hInstance);

	pManeger->Uninit();

	if(pManeger!=NULL)
	{
		delete pManeger;
		pManeger=NULL;
	}

	return (int)msg.wParam;
}
//=============================================================================
// �E�C���h�E�v���V�[�W��
//  (CALLBACK : Win32API�֐����Ăяo�����̋K��)
//  hWnd   : �E�B���h�E�̃n���h��
//  uMsg   : ���b�Z�[�W�̎��ʎq
//  wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
//  lParam : ���b�Z�[�W��2�Ԗڂ̃p�����[�^
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//�֐��̖��O��ς��Ă����v
{

	//�C�x���g����������֐�
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);									// "WM_QUIT"���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);		// ����̏������
}
void GameEnd(void)
{
	GameEndFlag=true;
}