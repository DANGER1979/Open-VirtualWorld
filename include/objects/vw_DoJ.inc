/*
 *            VW_DoJ v1.0
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


stock DoJ_OnGameModeInit()
{
/*	new tmpobjid, object_world = -1, object_int = -1;
	#include "../include/mapping/DoJ/govermentHall"
	#include "../include/mapping/DoJ/goverment2"
	#include "../include/mapping/DoJ/mayoroffice"
*/

	return 1;
}

stock DoJ_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid

	if(	IsPlayerInRangeOfPoint(playerid, 2.1, 1492.3281,-1756.6941,2106.2101) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 1485.7433,-1748.6017,106.1200) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 1490.9055,-1753.7274,106.1200) )
	{
		new msgitem[] = "FLOOR 1\nFLOOR 2\nFLOOR 3";//\n\nНажмите Accept, чтобы принять.
		ShowPlayerDialogEx(playerid, DoJ_DIALOG, DIALOG_STYLE_LIST, "Лифт в Мэрии", msgitem, "Перейти", "Отмена");
		//return 1;
	}
}

stock DoJ_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != DoJ_DIALOG) return 1;
	
	if(!response) return 1;

	//new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
	if(listitem == 0)//Level 1
	{
		SetPlayerPosEx(playerid, 1492.3281,-1756.6941,2106.2101,90.0);
		PlayerInfo[playerid][pLocal] = 39;
		SetPlayerVirtualWorldEx(playerid, DOJ_LS_WORLD1);
		SetPlayerInteriorEx(playerid, DoJ);
	}
	else if(listitem == 1)//Level 2
	{
	//ACP_SetPlayerPos(playerid, 1485.7433,-1748.6017,106.1200);
		//SetPlayerFacingAngle(playerid,0.0);
		SetPlayerPosEx(playerid, 1485.7433,-1748.6017,106.1200, 0.0);
		PlayerInfo[playerid][pLocal] = 39;
		SetPlayerVirtualWorldEx(playerid, DOJ_LS_WORLD2);//DoJ+1);
		SetPlayerInteriorEx(playerid, 0);
	}
	else if(listitem == 2)//Level 3
	{
		SetPlayerPosEx(playerid, 1490.9055,-1753.7274,106.1200, 0.0);
		PlayerInfo[playerid][pLocal] = 39;
		SetPlayerVirtualWorldEx(playerid, DOJ_LS_WORLD3);
		SetPlayerInteriorEx(playerid, 0);
	}
	else
	{
		return 1;
	}
	//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);//выбор этажа
	//PlaySoundForPlayer(playerid, SOUND_LIFT_START);//выбор этажа
	PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0, CurPos[0][playerid],CurPos[1][playerid],CurPos[2][playerid]);//проигрывает всем в радиусе 50 м
	return 1;
}
