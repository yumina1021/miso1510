//=============================================================================
//
// MS_BuildFight [netClient.cpp]
// 15/08/20
// Author : YOSHIKI ITO
//
//=============================================================================
#include "netClient.h"
#include <stdarg.h>
#include <stdio.h>
#include "Maneger.h"
#include "data.h"

#include "scene/Scene.h"
#include "scene/Game.h"

#include "../module/etc/Fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
SOCKET		CNetClient::m_Socket = INVALID_SOCKET;
int			CNetClient::m_ID = -1;
SOCKADDR_IN	CNetClient::m_ServerAddress;
int			CNetClient::m_nTime = 0;
bool		CNetClient::m_StartFlag = false;
bool		CNetClient::m_bEndGameFlag = false;
bool		CNetClient::m_bEndGameTimeFlag = false;
bool		CNetClient::m_bEndGameLoseFlag = false;


//=============================================================================
// ����������
//=============================================================================
void CNetClient::Init( void )
{
	int ret;

	// ID�������_���ɐݒ�i�{���Ȃ�΃��[�UID����ݒ肷�ׂ��j
	srand( timeGetTime() );
	m_ID = rand();
	m_StartFlag = false;

	char adress[256];
	int port;

	//�e�L�X�g�t�@�C������A�h���X�擾
	FILE *file;

	fopen_s(&file,"adress.txt", "rt");

	fscanf( file, "%s", adress );
	fscanf( file, "%d", &port );

	fclose( file );

	// ���M��A�h���X
	m_ServerAddress.sin_port = htons( (unsigned short)port );
	m_ServerAddress.sin_family= AF_INET;
	m_ServerAddress.sin_addr.s_addr = inet_addr( adress );


	// WinSock������
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData );


	// �\�P�b�g����
	m_Socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );


	// �}���`�L���X�g��M����
	int value = 1;
	ret = setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value) );


	// ��M�A�h���X
	sockaddr_in addressServer;
	addressServer.sin_port = htons( 20001 );
	addressServer.sin_family= AF_INET;
	addressServer.sin_addr.s_addr = INADDR_ANY;


	// �o�C���h
	ret = bind( m_Socket, (sockaddr*)&addressServer, sizeof(addressServer) );


	// �}���`�L���X�g�O���[�v�ɎQ��
	ip_mreq mreq;
	memset( &mreq, 0, sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = inet_addr( "239.0.0.2" );//�}���`�L���X�g�A�h���X
	mreq.imr_interface.s_addr = INADDR_ANY;
	ret = setsockopt( m_Socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq) );

	// ��M�X���b�h�J�n
	_beginthreadex( NULL, 0, ReceiveThread, NULL, 0, NULL );

}


//=============================================================================
// �I������
//=============================================================================
void CNetClient::Uninit( void )
{

	// �\�P�b�g�I��
	closesocket( m_Socket );

	// WinSock�I������
	WSACleanup();

}

//=============================================================================
// ��M�X���b�h
//=============================================================================
unsigned __stdcall CNetClient::ReceiveThread( LPVOID Param )
{
	int ret;
	DATA data;

	while( true )
	{
		// �f�[�^��M
		ret = recv( m_Socket, (char*)&data, sizeof( data ), 0 );

		if( ret == SOCKET_ERROR )
		{

		}
		else
		{
			// �f�[�^�^�C�v���
			switch( data.Type )
			{
				// �C�x���g�֘A
				case DATA_TYPE_EVENT:
				{
					break;
				}

				// ���W
				case DATA_TYPE_POSITION:
				{
					break;
				}

				// ��]�p�x
				case DATA_TYPE_ROTATION:
				{
					break;
				}

				//���[�V����
				case DATA_TYPE_MOTION:
				{
					break;
				}

				//�V���b�g
				case DATA_TYPE_SHOT:
				{
					break;
				}

				//�I�[�o�[���[�h
				case DATA_TYPE_OVERLOAD:
				{
					break;
				}
				//�^�C��
				case DATA_TYPE_TIME:
				{
					break;
				}

				//���C�t
				case DATA_TYPE_LIFE:
				{
					break;
				}
			}
		}

	}


	return 0;

}


//=============================================================================
// �f�[�^���M
//=============================================================================
void CNetClient::SendData( DATA Data )
{
	// ID�ݒ�
	Data.ID = m_ID;

	int ret;

	// �T�[�o�Ƀf�[�^���M
	ret = sendto( m_Socket, (char*)&Data, sizeof( Data ), 0, (sockaddr*)&m_ServerAddress, sizeof( m_ServerAddress ) );

	if( ret == SOCKET_ERROR )
	{
		//printf( "�ؒf: [%d]\n", g_Socket );
		m_Socket = INVALID_SOCKET;
	}

}


