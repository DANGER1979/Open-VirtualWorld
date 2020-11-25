/*
 *            VW_CNN v1.0
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 19.05.2020
 * @update    : 19.05.2020
 *
 * This file is provided as is (no warranties).
 *
 */

#include <a_samp>


stock CNN_OnGameModeInit()
{
/*	new tmpobjid, object_world = -1, object_int = -1;
	#include "../include/mapping/CNN/govermentHall"
	#include "../include/mapping/CNN/goverment2"
	#include "../include/mapping/CNN/mayoroffice"
*/
	//--------------------------------------------------------------------------
	print("   vw_CNN.inc v1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
	return 1;
}

stock CNN_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid

	if(	IsPlayerInRangeOfPoint(playerid, 2.1, 1453.2072,-1802.2932,2349.6951) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 1453.2283,-1801.5675,2643.3000) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 1490.9055,-1753.7274,106.1200) )
	{
		new msgitem[] = "Level 1\nLevel 2\nLevel 3";//\n\nНажмите Accept, чтобы принять.
		ShowPlayerDialogEx(playerid, CNN_DIALOG, DIALOG_STYLE_LIST, "Лифт в CNN STUDIO", msgitem, "Перейти", "Отмена");
		//return 1;
	}
}

stock CNN_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != CNN_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) return 1;

	//new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
	if(listitem == 0)//Level 1
	{
		SetPlayerPosEx(playerid, 1453.2072,-1802.2932,2349.6951,7.4330);
		PlayerInfo[playerid][pLocal] = 42;
		SetPlayerVirtualWorldEx(playerid, 2);
		SetPlayerInteriorEx(playerid, 0);
	}
	else if(listitem == 1)//Level 2
	{
	//ACP_SetPlayerPos(playerid, 1485.7433,-1748.6017,106.1200);
		//SetPlayerFacingAngle(playerid,0.0);
		SetPlayerPosEx(playerid, 1453.2283,-1801.5675,2643.3000, 0.0);
		PlayerInfo[playerid][pLocal] = 42;
		SetPlayerVirtualWorldEx(playerid, 7);//CNN+1);
		SetPlayerInteriorEx(playerid, 0);
	}
	else if(listitem == 2)//Level 3
	{
		SetPlayerPosEx(playerid, 1490.9055,-1753.7274,106.1200, 0.0);
		PlayerInfo[playerid][pLocal] = 42;
		SetPlayerVirtualWorldEx(playerid, 5);
		SetPlayerInteriorEx(playerid, 0);
	}
	else
	{
		return 1;
	}
	//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);//выбор этажа
	PlaySoundForPlayer(playerid, SOUND_LIFT_START);//выбор этажа
	//SetPlayerPosEx(playerid, plocx,plocy,plocz, ploca);
	return 1;
}
