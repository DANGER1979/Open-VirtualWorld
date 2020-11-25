/*
 *            vw_4 v3.0
 *       (c) Copyright 2009-2012 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 28.10.2013
 * @update    : 13.11.2018
 *
 * This file is provided as is (no warranties).
 *
 */
//#include <a_samp>

enum CameraObjects
{
    camobj
};
new PlayerCam[MAX_PLAYERS][CameraObjects];

new bool:CameraOnePerson[MAX_PLAYERS];

//firstlook_OnGameModeInit();
//firstlook_OnGameModeExit();
//firstlook_OnPlayerConnect(playerid);
//firstlook_OnPlayerDisconnect(playerid);
//firstlook_OnPlayerCommandText(playerid, cmdtext);
//firstlook_OnPlayerStateChange(playerid, newstate, oldstate);

//#if defined FILTERSCRIPT
stock firstlook_OnFilterScriptInit()
//public OnFilterScriptInit()
{
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(IsPlayerNPC(i)) continue;
		CameraOnePerson[i] = false;
	}
	print("  vw_firstlook v3.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

stock firstlook_OnFilterScriptExit()
//public OnFilterScriptExit()
{
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(IsPlayerNPC(i)) continue;

		if(CameraOnePerson[i] == true)
		{
			CameraOnePerson[i] = false;
			SetCameraBehindPlayer(i);
			if(PlayerCam[i][camobj] != 0 && IsValidObjectEx(PlayerCam[i][camobj]))
			{
				DestroyObjectEx(PlayerCam[i][camobj]);
				PlayerCam[i][camobj] = 0;
			}
		}
	}
}

stock firstlook_OnPlayerConnect(playerid)
//public OnPlayerConnect(playerid)
{
    CameraOnePerson[playerid] = false;//Пускай наверное по умолчанию будет выключено..
}

stock firstlook_OnPlayerDisconnect(playerid)
//public OnPlayerDisconnect(playerid, reason)
{
	if(CameraOnePerson[playerid] == true)
	{
		CameraOnePerson[playerid] = false;
		if(PlayerCam[playerid][camobj] != 0 && IsValidObjectEx(PlayerCam[playerid][camobj]))
		{
			DestroyObjectEx(PlayerCam[playerid][camobj]);
			PlayerCam[playerid][camobj] = 0;
		}
	}
}

stock firstlook_OnPlayerCommandText(playerid)
{
   	/*if(!IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в транспортном средстве!");
		return 1;
	}*/
	if(CameraOnePerson[playerid] == true)
	{
		CameraOnePerson[playerid] = false;
		if(PlayerCam[playerid][camobj] != 0 && IsValidObjectEx(PlayerCam[playerid][camobj]))
		{
			SetCameraBehindPlayer(playerid);
			DestroyObjectEx(PlayerCam[playerid][camobj]);
			PlayerCam[playerid][camobj] = 0;
		}
		SendClientMessage(playerid, COLOR_GREEN, "Вы выключили вид от 1 лица");
	}
	else
	{
		CameraOnePerson[playerid] = true;
		SetCameraOnePerson(playerid);
		SendClientMessage(playerid, COLOR_GREEN, "Вы включили вид от 1 лица");
	}
	//return 1;
}

stock firstlook_OnPlayerStateChange(playerid, newstate, oldstate)
//public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(IsPlayerNPC(playerid)) return 1;
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		if(CameraOnePerson[playerid] == true)
		{
			SetCameraOnePerson(playerid);
       	}
	}
	else if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		if(CameraOnePerson[playerid] == true)
		{
			CameraOnePerson[playerid] = false;
			if(PlayerCam[playerid][camobj] != 0 && IsValidObjectEx(PlayerCam[playerid][camobj]))
			{
				SetCameraBehindPlayer(playerid);
				DestroyObjectEx(PlayerCam[playerid][camobj]);
				PlayerCam[playerid][camobj] = 0;
			}
		}
	}
	return 1;
}
	/*#if defined firstlook_OnPlayerStateChange
		return firstlook_OnPlayerStateChange(playerid, newstate, oldstate);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange firstlook_OnPlayerStateChange
#if defined firstlook_OnPlayerStateChange
	forward firstlook_OnPlayerStateChange(playerid, newstate, oldstate);
#endif*/

stock SetCameraOnePerson(playerid)
{
	new Float:x, Float:y, Float:z;
	new vehicleid = GetPlayerVehicleID(playerid);
	new vehmodel = GetVehicleModel(vehicleid);
	if(IsPlayerInAnyVehicle(playerid))
	{
	    new Float:V_x,Float:V_y,Float:V_z, Float:angle2;
	    GetVehiclePos(vehicleid,V_x,V_y,V_z);
		GetVehicleZAngle(vehicleid, angle2);
		//format(strings, sizeof(strings), "GetVehPos(%d, %.4f, %.4f, %.4f) angle:%.1f", vehicleid, V_x, V_y, V_z, angle2);
		//SendClientMessage(playerid, COLOR_GRAD10, strings);
		new Float:vX,Float:vY,Float:vZ;
//-0.40, -0.15, 0.52
		new seatid = GetPlayerVehicleSeat(playerid);
		if(IsInBike(vehicleid))
		{
			if(seatid == 0)
			{
				GetVehicleModelInfo(vehmodel, VEHICLE_MODEL_INFO_FRONTSEAT, vX, vY, vZ);
				x = 0.0;//+ справа, - слева
				y = 0.0;//+ cпереди, - сзади
				z = vZ + 0.6598;//+ выше центра, - ниже
			}
			if(seatid == 1)
			{
				GetVehicleModelInfo(vehmodel, VEHICLE_MODEL_INFO_REARSEAT, vX, vY, vZ);
				x = 0.0;
				y = vY;
				z = vZ + 0.6598;
			}
		}
		else
		{
			if(seatid == 0)
			{
				GetVehicleModelInfo(vehmodel, VEHICLE_MODEL_INFO_FRONTSEAT, vX, vY, vZ);
				x = -1*vX;//+ справа, - слева
				y = vY;//+ cпереди, - сзади
				z = vZ + 0.6598;//+ выше центра, - ниже
			}
			else if(seatid == 1)
			{
				GetVehicleModelInfo(vehmodel, VEHICLE_MODEL_INFO_FRONTSEAT, vX, vY, vZ);
				x = vX;//+ справа, - слева
				y = vY;//+ cпереди, - сзади
				z = vZ + 0.6598;//+ выше центра, - ниже
			}
			else if(seatid == 2)
			{
				GetVehicleModelInfo(vehmodel, VEHICLE_MODEL_INFO_REARSEAT, vX, vY, vZ);
				x = -1*vX;
				y = vY;
				z = vZ + 0.6598;
			}
			else if(seatid == 3)
			{
				GetVehicleModelInfo(vehmodel, VEHICLE_MODEL_INFO_REARSEAT, vX, vY, vZ);
				x = vX;
				y = vY;
				z = vZ + 0.6598;
			}
		}
		//format(strings, sizeof(strings), "GetVehInfo(%d, %.4f, %.4f, %.4f) seat: %d", vehicleid, vX, vY, vZ, seatid);
		//SendClientMessage(playerid, COLOR_GRAD9, strings);
       	PlayerCam[playerid][camobj] = CreateObjectEx(19254, x, y, z, 0.0,0.0,0.0, 0,0,-1, 8.0, 8.0);
       	AttachObjectToVehicleEx(PlayerCam[playerid][camobj], vehicleid, x, y, z, 0.0,0.0,0.0);
       	AttachCameraToObjectEx(playerid, PlayerCam[playerid][camobj]);
		//format(strings, sizeof(strings), "AttachObjectToVehicleEx(objectid:%d, vehicleid:%d, %.4f, %.4f, %.4f",
		//	PlayerCam[playerid][camobj], vehicleid, x, y, z);
		//SendClientMessage(playerid, COLOR_GRAD7, strings);
	}
	else
	{
	    new Float:F_x,Float:F_y,Float:F_z, Float:angle;
		GetPlayerPos(playerid,F_x,F_y,F_z);
		GetPlayerFacingAngle(playerid, angle);
		new Float: camPos[3];
		GetPlayerCameraPos(playerid, camPos[0], camPos[1], camPos[2]);

		format(strings, sizeof(strings), "PlayerPos[CameraPos](%.4f[%.4f], %.4f[%.4f], %.4f[%.4f]) angle:%.1f",
			F_x, camPos[0], F_y, camPos[1], F_z, camPos[2], angle);
		SendClientMessage(playerid, COLOR_GRAD11, strings);

    	x = 0.0;
		y = 0.2;
		z = 0.0 + 0.6598;

       	PlayerCam[playerid][camobj] = CreateObjectEx(19254, x, y, z, 0.0,0.0,0.0, 0,0,-1, 8.0, 8.0);//19254

       	new Float:o_x,Float:o_y,Float:o_z;
		GetObjectPos(PlayerCam[playerid][camobj],o_x,o_y,o_z);
//format(strings, sizeof(strings), "CreateObjectEx(objectid:%d %.4f[%.4f], %.4f[%.4f], %.4f[%.4f])",
//			PlayerCam[playerid][camobj], x,o_x, y,o_y, z,o_z);
//SendClientMessage(playerid, COLOR_GRAD7, strings);

       	AttachObjectToPlayerEx(PlayerCam[playerid][camobj], playerid, x, y, z, 0.0,0.0,0.0);

//format(strings, sizeof(strings), "%d AttachObjectToPlayer(objectid:%d, playerid:%d, %.4f, %.4f, %.4f)",
//		PlayerCam[playerid][camobj], playerid, x, y, z);
//SendClientMessage(playerid, COLOR_GRAD7, strings);

       	AttachCameraToObjectEx(playerid, PlayerCam[playerid][camobj]);
	}
}
