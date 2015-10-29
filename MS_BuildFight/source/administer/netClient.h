//=============================================================================
//
// MS_BuildFight [netClient.h]
// 15/08/20
// Author : YOSHIKI ITO
//
//=============================================================================
#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include "../common.h"
#include <winsock.h>
#include <process.h>
#include "data.h"

#pragma comment( lib, "wsock32.lib" )


//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*********************************************************
// ネットワーククライアントクラス
//*********************************************************
class CNetClient
{
public:

	CNetClient();
	~CNetClient();

	static void Init( void );
	static void Uninit( void );

	static unsigned __stdcall ReceiveThread( LPVOID Param );

	static bool GetStartFlag(void){return m_StartFlag;};
	static bool GetEndGameFlag(void){return m_bEndGameFlag;};
	static bool GetEndGameTimeFlag(void){return m_bEndGameTimeFlag;};
	static bool GetEndGameLoseFlag(void){return m_bEndGameLoseFlag;};

	static int GetAnotherTime(void){return m_nTime;};

	static void SetStartFlag(bool change){m_StartFlag=change;};
	static void SetEndGameFlag(bool change){m_bEndGameFlag=change;};
	static void SetEndGameTimeFlag(bool change){m_bEndGameTimeFlag=change;};
	static void SetEndGameLoseFlag(bool change){m_bEndGameLoseFlag=change;};

	static void SetAnotherTime(int nTime){m_nTime=nTime;};

	static void SendData( DATA Data );
	//static void SendPacket( int PacketType, ... );

private:

	static SOCKET		m_Socket;
	static int			m_ID;

	static bool			m_StartFlag;
	static int			m_nTime;
	static bool			m_bEndGameFlag;
	static bool			m_bEndGameLoseFlag;
	static bool			m_bEndGameTimeFlag;


	static SOCKADDR_IN	m_ServerAddress;

};

#endif
