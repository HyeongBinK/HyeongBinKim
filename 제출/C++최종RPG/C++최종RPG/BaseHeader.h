#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<math.h>

using namespace std;

//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////

#define BASEWIDTH 30//가로
#define BASEHEIGHT 30 //세로

enum CLASS
{
	CLASS_eCIVILIAN = 1,
	CLASS_eWARRIOR,
	CLASS_eHERO,
	/*m_eARCHER,
	m_eRANGER,
	m_eMAGICIAN,
	m_eARCHMAGE, */
	CLASS_eMONSTER, //몬스터
	CLASS_eBOSSMONSTER //보스몬스터
};

enum LIFESTATUS
{
	LIFESTATUS_eNORMAL = 0, //기본상태
	LIFESTATUS_eDEAD, //(사망상태)
	LIFESTATUS_eON_POISON, //자신이공격할떄마다(자신의턴이될떄마다) 최대체력의 5프로의지속데미지
	LIFESTATUS_eON_PARALYSIS, //공격속도가 매우느려져 무조건 후공
};

enum SPECIALEFFECT
{
	SPECIALEFFECT_eNONE_EFFECT = 0, //추가효과없음
	SPECIALEFFECT_ePOISON_EFFECT, //독효과부여
	SPECIALEFFECT_ePARAIYSIS_EFFECT, //마비효과부여 
	//m_ePOISON_RESISTANCE, //독저항
	//m_ePARALYSIS_RESISTANCE, //마비저항
};

enum KEY
{
	KEY_LEFT = 75,  
	KEY_RIGHT = 77,
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_ESC = 27, //강제종료키
	KEY_ENTER = 13, //메뉴키
};

enum WEAPONNAME
{
	WEAPONNAME_eSHORTSWORD =1,
	WEAPONNAME_eLONGSWORD,
	WEAPONNAME_eBUSTERSWORD,
	WEAPONNAME_eGOBKINGSWORD,
	WEAPONNAME_eMISRILLSWORD,
	WEAPONNAME_eDEMONKINGSWORD,
	WEAPONNAME_eDRAGONSWORD,
	WEAPONNAME_eRETURN, //되돌아가기
	WEAPONNAME_eETERNALSWORD = 999
};

enum SKILLNAME
{
	//액티브
	SKILLNAME_eNORMALATTACK =0,
	SKILLNAME_ePOWERSLASH,
	SKILLNAME_eCOMBOASSULT,
	SKILLNAME_eCOMBOEXTINGSION,
	SKILLNAME_eRETURN //되돌아가기
	//버프
	//SKILLNAME_eRAGE,
	//패시브
	//SKILLNAME_eSWORDMASTER
};

enum MOBNAME
{
	MOBNAME_eGOB = 1,
	MOBNAME_eKINGGOB,
	MOBNAME_eMINOTAURS,
	MOBNAME_eMINOTARUSKING,
	MOBNAME_eDEVIL,
	MOBNAME_eDEMONKING,
	MOBNAME_eWYVERN,
	MOBNAME_eHORNTAIL
};

enum WEAPONPRIDE
{
	WEAPONPRIDE_eSHORTSWORD = 100,
	WEAPONPRIDE_eLONGSWORD = 1000,
	WEAPONPRIDE_eBUSTERSWORD = 10000,
	WEAPONPRIDE_eGOBKINGSWORD = 7777,
	WEAPONPRIDE_eMISRILLSWORD = 20000,
	WEAPONPRIDE_eDEMONKINGSWORD = 50000,
	WEAPONPRIDE_eDRAGONSWORD = 99999,
	WEAPONPRIDE_eETERNALSWORD = 9999999
};

enum WEAPONTYPE
{
	WEAPONTYPE_eONEHANDSWORD =1, //한손검 
	WEAPONTYPE_eTWOHANDSWORD, //두손검
};
