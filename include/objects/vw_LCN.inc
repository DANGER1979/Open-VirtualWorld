/*
 *            VW_LCN v1.0
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 19.05.2020
 * @update    : 19.05.2020
 *
 * This file is provided as is (no warranties).
 *
 */

//#include <a_samp>

//new check_lcn_tog[MAX_PLAYERS];//тригер спауна на базе LCN

new LCN_object1[2];
new LCN_object_check1;

new LCN_object2[2];
new LCN_object_check2;

new LCN_object3[2];
new LCN_object_check3;

new LCN_object;
new LCN_check;


stock LCN_OnGameModeInit()
{
/*	new tmpobjid, object_world = -1, object_int = -1;
	#include "../include/mapping/LCN/lcn_ext"
	#include "../include/mapping/LCN/int_lcn"
*/

	return 1;
}

stock LCN_OnPlayerConnect(playerid)
{
//ворота лкн
	RemoveBuildingForPlayerEx(playerid, 3749, 664.921, -1309.348, 18.367, 0.250);
	RemoveBuildingForPlayerEx(playerid, 3750, 664.921, -1309.348, 18.367, 0.250);
	RemoveBuildingForPlayerEx(playerid, 3749, 785.375, -1152.448, 28.437, 0.250);
	RemoveBuildingForPlayerEx(playerid, 3750, 785.375, -1152.448, 28.437, 0.250);
	RemoveBuildingForPlayerEx(playerid, 3749, 659.781, -1227.270, 19.913, 0.250);
	RemoveBuildingForPlayerEx(playerid, 3750, 659.781, -1227.270, 19.913, 0.250);
}

stock LCN_OnPlayerKeyState_YES(playerid)
{
    if(PlayerInfo[playerid][pMember] == LCN)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.5, 1402.01563, -4.05390, 1001.06842) || IsPlayerInRangeOfPoint(playerid, 1.5, 1402.41858, -4.03263, 1001.06842))
        {
			if(LCN_check == 1) return 1;
			MoveDynamicObject(LCN_object,1402.209350, -1.885187, 999.911926 +0.03, 0.03, 0.0000, 0.0000, 358.9998);
			SetTimer("@Clost_LCN_object_i", 4000, false);
			LCN_check = 1;
			ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
			//	LoopingAnim(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 0);
		//	LoopingAnim(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0);
			//	SetTimerEx("@stop_thear", 1000, false, "d", playerid);
        }
    }
    return 1;
}


stock LCN_OnPlayerKey_DRIVER(playerid)
{//если игрок посигналил
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
    //if(PlayerInfo[playerid][pVirtual] != 0) return 1;
    //if(IsPlayerControllable[playerid] == 1) return 1;

	if(IsPlayerInRangeOfPoint(playerid, 9.0, 665.0773,-1309.5023,13.4609)) // первые ворота
	{
		if(PlayerInfo[playerid][pMember] != LCN) return true;
		if(LCN_object_check1 == 1) return true;
		MoveObjectEx(LCN_object1[0],660.353515, -1309.428955, 14.220947 + 0.2, 0.02, 0.000000, 0.000007, 90.000000);
		MoveObjectEx(LCN_object1[1],669.913879, -1309.428955, 14.220947 + 0.2, 0.02, 0.000000, -0.000007, 90.000000);
		SetTimer("@Clost_LCN_object1", 15000, false);
		LCN_object_check1 = 1;
	}
	if(IsPlayerInRangeOfPoint(playerid, 9.0, 787.7729,-1152.1172,23.6563)) // первые ворота
	{
		if(PlayerInfo[playerid][pMember] != LCN) return true;
		if(LCN_object_check2 == 1) return true;
		MoveObjectEx(LCN_object2[0],787.347595, -1156.958862, 24.394906 + 0.2, 0.02, 0.000015, 0.000015, 180.0);
		MoveObjectEx(LCN_object2[1],787.347595, -1147.398437, 24.394906 + 0.2, 0.02, -0.000015, -0.000015, 184.0);
		SetTimer("@Clost_LCN_object2", 15000, false);
		LCN_object_check2 = 1;
	}
	if(IsPlayerInRangeOfPoint(playerid, 9.0, 645.8349,-1222.9802,18.2235)) // первые ворота
	{
		if(PlayerInfo[playerid][pMember] != LCN) return true;
		if(LCN_object_check3 == 1) return true;
		MoveObjectEx(LCN_object3[0],644.942504, -1227.618652, 18.912885+ 0.2, 0.02, 0.000066, 0.000031, 343.9516);
		MoveObjectEx(LCN_object3[1],647.577819, -1218.428588, 18.912885+ 0.2, 0.02, -0.000066, -0.000031, 343.9516);
		SetTimer("@Clost_LCN_object3", 15000, false);
		LCN_object_check3 = 1;
	}
	return 1;
}

@Clost_LCN_object_i();
@Clost_LCN_object_i()
{
    MoveDynamicObject(LCN_object,1402.209350, -1.885187, 999.911926, 0.03, 0.000000, 0.000000, 270.000000);
    LCN_check = 0;
}
