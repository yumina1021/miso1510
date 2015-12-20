//=============================================================================
//
// MS_BuildFight [CMagnet.cpp]
// 15/08/20
// Author : TOSIKAZU INAZAWA
//
//=============================================================================
//*****************************************************************************
// É}ÉNÉçíËã`
//*****************************************************************************
#include "Magnet.h" 

D3DXVECTOR3 MagnetMove(NS ballNS, D3DXVECTOR3 ballPos, NS objNS, D3DXVECTOR3 objPos)
{
	D3DXVECTOR3 vector;

	float disX = (ballPos.x - objPos.x)*(ballPos.x - objPos.x);
	float disY = (ballPos.y - objPos.y)*(ballPos.y - objPos.y);
	float disZ = (ballPos.z - objPos.z)*(ballPos.z - objPos.z);

	// 3DÇÃãóó£
	float distance = (float)sqrt(disX + disY + disZ);

	if (distance < 200)
	{
		float per = distance / 200;

		//é•ã…Ç™à·Ç§èÍçá
		if (ballNS != objNS)
		{
			vector = (objPos - ballPos)*(1 - per);

			vector = vector *0.01f;

			return vector;
		}
		else
		{
			vector = (objPos - ballPos)*(1 - per);

			vector = vector *0.01f;

			return -vector;
		}
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
/////////////EOF////////////