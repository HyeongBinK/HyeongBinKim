#include "Ward.h"

void Ward::Warddraw()
{
	Draw::TextDraw(m_strWard, m_iLocationX, m_iLocationY);
}

void Ward::Warddrop()
{
	m_iLocationY++;
}

void Ward::Live(int NewTimer)
{
	if(m_bDead != true && m_SuccessAttack != true)
	{
		if (NewTimer - m_iTimer >= m_iFallenDelay)
		{
			if (m_iLocationY >= (HEIGHT*0.8) - 3 && m_iLocationY <= (HEIGHT*0.8) + 1)
			{
				if (m_iLocationX < ((WIDTH * 0.5) + 10)*2 && (m_iLocationX + m_strWard.length()) > ((WIDTH * 0.5) - 10)*2)
				{
					if(m_iLocationY == HEIGHT*0.8 - 3 )
						Draw::EraseWard(m_iLocationX, m_iLocationY, m_strWard.length());
					Warddrop();
					m_iTimer = NewTimer;
					return;
				}

			}
				Draw::EraseWard(m_iLocationX, m_iLocationY, m_strWard.length());

				if (m_iLocationY + 2 == HEIGHT)
				{
					m_SuccessAttack = true;
					return;
				}
				Warddrop();
				Warddraw();
				m_iTimer = NewTimer;
			
		}
	}
}

void Ward::Die()
{
	m_bDead = true;
}

void Ward::MakeNewWard(string NewWard, int XLocation, int NewFallenDelay)
{
	m_iLocationX = XLocation;
	m_strWard = NewWard;
	m_iLocationY = 1;
	m_iTimer = clock();
	m_iFallenDelay = NewFallenDelay;
	m_bDead = false;
	m_SuccessAttack = false;
}

void Ward::UserUseSpeedItem(int NewSpeed)
{
	m_iFallenDelay = NewSpeed;
}
