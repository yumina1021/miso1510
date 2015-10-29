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
#include "../module/robot/EnemyM.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 静的変数
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
// 初期化処理
//=============================================================================
void CNetClient::Init( void )
{
	int ret;

	// IDをランダムに設定（本来ならばユーザID等を設定すべき）
	srand( timeGetTime() );
	m_ID = rand();
	m_StartFlag = false;

	char adress[256];
	int port;

	//テキストファイルからアドレス取得
	FILE *file;

	fopen_s(&file,"adress.txt", "rt");

	fscanf( file, "%s", adress );
	fscanf( file, "%d", &port );

	fclose( file );

	// 送信先アドレス
	m_ServerAddress.sin_port = htons( (unsigned short)port );
	m_ServerAddress.sin_family= AF_INET;
	m_ServerAddress.sin_addr.s_addr = inet_addr( adress );


	// WinSock初期化
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData );


	// ソケット生成
	m_Socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );


	// マルチキャスト受信許可
	int value = 1;
	ret = setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value) );


	// 受信アドレス
	sockaddr_in addressServer;
	addressServer.sin_port = htons( 20001 );
	addressServer.sin_family= AF_INET;
	addressServer.sin_addr.s_addr = INADDR_ANY;


	// バインド
	ret = bind( m_Socket, (sockaddr*)&addressServer, sizeof(addressServer) );


	// マルチキャストグループに参加
	ip_mreq mreq;
	memset( &mreq, 0, sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = inet_addr( "239.0.0.2" );//マルチキャストアドレス
	mreq.imr_interface.s_addr = INADDR_ANY;
	ret = setsockopt( m_Socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq) );

	// 受信スレッド開始
	_beginthreadex( NULL, 0, ReceiveThread, NULL, 0, NULL );

}


//=============================================================================
// 終了処理
//=============================================================================
void CNetClient::Uninit( void )
{

	// ソケット終了
	closesocket( m_Socket );

	// WinSock終了処理
	WSACleanup();

}

//=============================================================================
// 受信スレッド
//=============================================================================
unsigned __stdcall CNetClient::ReceiveThread( LPVOID Param )
{
	int ret;
	DATA data;

	while( true )
	{
		// データ受信
		ret = recv( m_Socket, (char*)&data, sizeof( data ), 0 );

		if( ret == SOCKET_ERROR )
		{

		}
		else
		{
			// データタイプ解析
			switch( data.Type )
			{
				// イベント関連
				case DATA_TYPE_EVENT:
				{
					break;
				}

				// 座標
				case DATA_TYPE_POSITION:
				{
					break;
				}

				// 回転角度
				case DATA_TYPE_ROTATION:
				{
					break;
				}

				//モーション
				case DATA_TYPE_MOTION:
				{
					break;
				}

				//ショット
				case DATA_TYPE_SHOT:
				{
					break;
				}

				//オーバーロード
				case DATA_TYPE_OVERLOAD:
				{
					break;
				}
				//タイム
				case DATA_TYPE_TIME:
				{
					break;
				}

				//ライフ
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
// データ送信
//=============================================================================
void CNetClient::SendData( DATA Data )
{
	// ID設定
	Data.ID = m_ID;

	int ret;

	// サーバにデータ送信
	ret = sendto( m_Socket, (char*)&Data, sizeof( Data ), 0, (sockaddr*)&m_ServerAddress, sizeof( m_ServerAddress ) );

	if( ret == SOCKET_ERROR )
	{
		//printf( "切断: [%d]\n", g_Socket );
		m_Socket = INVALID_SOCKET;
	}

}


