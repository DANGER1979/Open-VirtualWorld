// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

/*#include <a_samp>
#define COLOR_BLUE 0x0000FFFF
#define COLOR_YELLOW 0xFFFF00FF
#define COLOR_RED 0xFF0000FF
#define COLOR_GREY 0xAFAFAFAA
#define DoJ 16*/

new ObjectLightPoliceCar[MAX_VEHICLES+1];


stock migalka_OnGameModeInit()
{
	/*for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(IsPlayerNPC(i)) continue;
		CameraOnePerson[i] = false;
	}*/
	print("   vw_migalka 1.0 By: Maksim_Edishions");
	print("_____________________________________________");
	print(" ");
	return 1;
}

stock migalka_OnGameModeExit()
{
    /*for(new idx = 1; idx < MAX_VEHICLES-1; idx++)
	{
		if(IsValidObjectEx(ObjectLightPoliceCar[idx]))
		{
			DestroyObjectEx(ObjectLightPoliceCar[idx]);
		}
	}*/
	return 1;
}

stock migalka_OnVehicleSpawn(vehicleid)
{
	DestroyObjectEx(ObjectLightPoliceCar[vehicleid]);
	return 1;
}
stock migalka_OnVehicleDeath(vehicleid)
{
	DestroyObjectEx(ObjectLightPoliceCar[vehicleid]);
	return 1;
}

stock OnPlayerKeySpecialBleep(playerid)
{
	//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid,0xFFFFFFFF,"Вы должны находится за рулем автомобиля!");
	if(PlayerInfo[playerid][pMember] != DoJ)
	{
	    //SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
	    return 1;
	}
	if(PlayerInfo[playerid][pRank] < 4)
	{
		//SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
	    return 1;
	}
	new carid = nCarID[playerid];
	if(!IsValidDynamicObject(ObjectLightPoliceCar[carid]))//if(CarStatus[carid][st_alarm] == VEHICLE_PARAMS_OFF)
	{
		if(nCarModel[playerid] == 421)
		{
			AttachObjectToVehicleEx(ObjectLightPoliceCar[carid] = CreateObjectEx(18646, 0.0,0.0,0.0, 0.0,0.0,0.0), carid, -0.45,0.15,0.75, 0.0,0.0,0.0);
		}
		else if(nCarModel[playerid] == 551)
		{
			AttachObjectToVehicleEx(ObjectLightPoliceCar[carid] = CreateObjectEx(18646, 0.0,0.0,0.0, 0.0,0.0,0.0), carid, -0.5,0.05,0.92, 0.0,0.0,0.0);
		}
		else if(nCarModel[playerid] == 547)
		{
			AttachObjectToVehicleEx(ObjectLightPoliceCar[carid] = CreateObjectEx(18646, 0.0,0.0,0.0, 0.0,0.0,0.0), carid, -0.53,0.052,0.92, 0.0,0.0,0.0);
		}
		else if(nCarModel[playerid] == 579)
		{
			AttachObjectToVehicleEx(ObjectLightPoliceCar[carid] = CreateObjectEx(19419, 0.0,0.0,0.0, 0.0,0.0,0.0), carid, 0.0,-0.05,1.23, 0.0,0.0,0.0);
		}
		else return 1;
		SetVehicleParams(carid,//playerid,
			CarStatus[carid][st_engine],CarStatus[carid][st_lights],VEHICLE_PARAMS_ON,CarStatus[carid][st_doors],CarStatus[carid][st_bonnet],
		  	CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
			  	
		SpecialBleep[carid] = 1;
		SendClientMessage(playerid, COLOR_BLUE, "   Проблесковый маячок синего и красного цветов и специальный звуковой сигнал ВКЛЮЧЕНЫ.");
	}
	else
	{
    	SetVehicleParams(carid,//playerid,
			CarStatus[carid][st_engine],CarStatus[carid][st_lights],VEHICLE_PARAMS_OFF,CarStatus[carid][st_doors],CarStatus[carid][st_bonnet],
			CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
				
		SpecialBleep[carid] = 0;
	    DestroyObjectEx(ObjectLightPoliceCar[carid]);
		SendClientMessage(playerid, COLOR_RED,  "   Проблесковый маячок синего и красного цветов и специальный звуковой сигнал ВЫКЛЮЧЕНЫ.");
	}
	return 1;
}

stock migalka_OnPlayerKeyState_DRIVER(playerid)//для ворот начало
{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	    if(PlayerInfo[playerid][pVirtual] != 0)
	    {
			 //SendClientMessage(playerid, COLOR_GREY, "   В этом виртуальном мире ВЫ не можете открыть ворота !");
	        return 1;
	    }
	    if(IsPlayerControllable[playerid] == 1) return 1;
	    if(IsInCopCar(nCarID[playerid]) || IsInAmbulanceCar(nCarID[playerid]))
	    {
	    	new carid = nCarID[playerid];
			if(CarStatus[carid][st_alarm] == VEHICLE_PARAMS_OFF)
			{//SpecialBleep[nCarID[playerid]] == 0 &&
				SpecialBleep[nCarID[playerid]] = 1;
				SendClientMessage(playerid, COLOR_BLUE, "   Проблесковый маячок синего и красного цветов и специальный звуковой сигнал ВКЛЮЧЕНЫ.");
				SetVehicleParams(carid,//playerid,
					CarStatus[carid][st_engine],CarStatus[carid][st_lights],VEHICLE_PARAMS_ON,CarStatus[carid][st_doors],CarStatus[carid][st_bonnet],
				  	CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
			}
			else //if(SpecialBleep[nCarID[playerid]] == 1 && alarm == VEHICLE_PARAMS_ON)
			{
				SpecialBleep[nCarID[playerid]] = 0;
				SendClientMessage(playerid, COLOR_RED,  "   Проблесковый маячок синего и красного цветов и специальный звуковой сигнал ВЫКЛЮЧЕНЫ.");
	    		SetVehicleParams(carid,//playerid,
					CarStatus[carid][st_engine],CarStatus[carid][st_lights],VEHICLE_PARAMS_OFF,CarStatus[carid][st_doors],CarStatus[carid][st_bonnet],
					CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
			}
			return 1;
		}
		OnPlayerKeySpecialBleep(playerid);
		return 1;
}
