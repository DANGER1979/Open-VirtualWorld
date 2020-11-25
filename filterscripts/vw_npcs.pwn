/*
 *            vw_npcs 1.3
 *       (c) Copyright 2009-2010 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (http://forum.gameplanet.by/index.php?showuser=32934)
 * @date      : 18.10.2009
 * @update    : 25.06.2020
 *
 * This file is provided as is (no warranties).
 *
 */

#include <a_samp>
//#include <AntiDeAMX>
//#pragma tabsize 0

#define COLOR_WHITE 0xFFFFFFFF//белый
#define COLOR_LIGHTBLUE 0x0080FFFF//светло-синий
#define COLOR_GREEN 0x008000FF//зеленый
#define COLOR_ORANGE 0xFF6600FF//оранжевый
#define COLOR_PURPLE 0x00CCFFFF//голубой
#define COLOR_YELLOW 0xFFFF00FF//желтый

#define TEAM_BIKERS_COLOR 0xFF660099//ORANGE 255 153 0 //0xFF990096
forward OnRemotePlayerSpawn(playerid);
forward OnRemoteNPCCar(vehicleid);
//forward WaitApplyAnimation(playerid);
new Text3D: Label;
#define COLOR_NEWBIE     	 	0xEE66EEFF//238 102 238
//-------------------------------------------------
new npctimer = -1;
new gConnectNPCCountdown = 0;
forward ConnectNPCTimer();

new NPCCar[16];
new npc_veh;

public OnFilterScriptInit()
{
	//AntiDeAMX();
	//gConnectNPCCountdown = 1;
	npctimer = SetTimer("ConnectNPCTimer", 100, 1);

	/*for(new v; v < sizeof(NPCCar); v++)
	{
		printf("OnPlayerSpawn.NPCCar[%d] = %d", v, NPCCar[v]);
	}*/
	//--------------------------------------------------------------------------
	print("   vw_npcs 1.3 By: Hidden -=DANGER=-");
	print("_____________________________________________");
	print(" ");
	return 1;
}

public ConnectNPCTimer()
{
	gConnectNPCCountdown ++;
	if(gConnectNPCCountdown == 1)
	{
		//SendRconCommand("maxnpc 17");//не даЄт после загрузки загружатьс€ другим ‘—
		ConnectNPC("TrainDriverLS","train_ls");//name[]	The NPC name.
	}
	else if(gConnectNPCCountdown == 2)
	{
		ConnectNPC("TrainDriverSF","train_sf");//script[]	The NPC scriptname that is located in the npcmodes folder
	}
	else if(gConnectNPCCountdown == 3)
	{
		ConnectNPC("TrainDriverLV","train_lv");//Ёто подключит NPC к вашему серверу
	}
	else if(gConnectNPCCountdown == 4)
	{
		ConnectNPC("TramDriverSF","tram_sf1");//name[]	The NPC name.
	}
	else if(gConnectNPCCountdown == 5)
	{
		ConnectNPC("PilotLS","at400_ls");
	}
	else if(gConnectNPCCountdown == 6)
	{
		ConnectNPC("PilotSF","at400_sf");
	}
	else if(gConnectNPCCountdown == 7)
	{
		ConnectNPC("PilotLV","at400_lv");
	}
	else if(gConnectNPCCountdown == 8)
	{
		ConnectNPC("TaxiDriverLS1","taxi_ls1");
	}
	else if(gConnectNPCCountdown == 9)
	{
		ConnectNPC("TaxiDriverLS2","taxi_ls2");
	}
	else if(gConnectNPCCountdown == 10)
	{
		ConnectNPC("TaxiDriverSF1","taxi_sf1");
	}
	else if(gConnectNPCCountdown == 11)
	{
		ConnectNPC("TaxiDriverSF2","taxi_sf2");
	}
	else if(gConnectNPCCountdown == 12)
	{
		ConnectNPC("TaxiDriverLV1","taxi_lv1");
	}
	else if(gConnectNPCCountdown == 13)
	{
		ConnectNPC("TaxiDriverLV2","taxi_lv2");
	}
	else if(gConnectNPCCountdown == 14)
	{
		ConnectNPC("BusDriverLS","bus_ls");
	}
	else if(gConnectNPCCountdown == 15)
	{
		ConnectNPC("BusDriverLV","bus_lv");
	}
	else if(gConnectNPCCountdown == 16)
	{
		ConnectNPC("BusDriverSF","bus_sf");
	}
	else if(gConnectNPCCountdown == 17)
	{
		ConnectNPC("Vika_Jefferson","onfoot_test");
		gConnectNPCCountdown = 0;
		KillTimer(npctimer); npctimer = -1;
	}
}

public OnFilterScriptExit()
{
	for(new i=0; i<=GetMaxPlayers(); i++)
	{
		if( !IsPlayerConnected(i)) continue;
		if(IsPlayerNPC(i))
		{
			Kick(i);
		}
	}
	gConnectNPCCountdown = 0;
	if(npctimer != -1) { KillTimer(npctimer); npctimer = -1; }
	print("OnFilterScriptExit: VW_npcs");
	return 1;
}
//-------------------------------------------------
// IMPORTANT: This restricts NPCs connecting from
// an IP address outside this server. If you need
// to connect NPCs externally you will need to modify
// the code in this callback.

public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid))
	{
	    new ip_addr_npc[64+1];
	    new ip_addr_server[64+1];
	    GetServerVarAsString("bind",ip_addr_server,64);
	    GetPlayerIp(playerid,ip_addr_npc,64);
	    
		if(!strlen(ip_addr_server)) {//если ип адрес сервера не получен, то присвоить ип адрес локального сервера
		    ip_addr_server = "127.0.0.1";
		}
		
		if(strcmp(ip_addr_npc,ip_addr_server,true) != 0) {//если ип адрес бота не равен адресу сервер
		    // this bot is remote connecting
		    printf("NPC: Got a remote NPC connecting from %s and I'm kicking it.",ip_addr_npc);
		    Kick(playerid);
		    return 0;
		}
        printf("NPC: Connection from %s is allowed.",ip_addr_npc);
	}
	return 1;
}
//-------------------------------------------------
public OnPlayerDisconnect(playerid, reason)//¬ыполн€етс€ при отключении игрока от сервера.
{
	if(IsPlayerNPC(playerid))
	{
		Delete3DTextLabel(Label);
	    /*new Text3D: tthreed = Create3DTextLabel("UNLOAD", 0x00000000, 0.0, 0.0, 0.0, 0.0, 0, 0);
	    Delete3DTextLabel(tthreed);
	    for(new Text3D: i; i < tthreed; i++)
	    {
	        Delete3DTextLabel(i);
	    }*/

		new npcname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcname, sizeof(npcname));
		printf("NPC %s[%d]: Disconnection from server. Reason: %d", npcname, playerid, reason);
	}
	return 1;
}
public OnPlayerRequestClass(playerid, classid)
{
	//if(!IsPlayerNPC(playerid)) return 0; // We only deal with NPC players in this script
	if(IsPlayerNPC(playerid))
	{
		new npcname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcname, sizeof(npcname));
		if(!strcmp(npcname,"TrainDriverLS",true)) {
		    SetSpawnInfo(playerid,69,255,1700.7551,-1953.6531,14.8756,0.0,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"TrainDriverSF",true)) {
		    SetSpawnInfo(playerid,69,255,-1942.7950,168.4164,27.0006,0.0,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"TrainDriverLV",true)) {
	        SetSpawnInfo(playerid,69,255,1462.0745,2630.8787,10.8203,0.0,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"TramDriverSF",true)) {
		    SetSpawnInfo(playerid,69,255,-2006.5000,145.1613,27.9973,0.0,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"PilotLS",true)) {
		    SetSpawnInfo(playerid,69,61,-1513.0963,-21.4589,14.0641,0.0,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"PilotSF",true)) {
		    SetSpawnInfo(playerid,69,61,-1513.0963,-21.4589,14.0641,0.0,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"PilotLV",true)) {
		    SetSpawnInfo(playerid,69,61,1477.4631,1647.4589,10.7281,0.0,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"TaxiDriverLS1",true)) {
		    SetSpawnInfo(playerid,69,253,2148.5190,-1138.6353,25.2557,90.5812,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"TaxiDriverLS2",true)) {
		    SetSpawnInfo(playerid,69,253,1784.8588,-1932.0735,13.1650,272.0414,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"TaxiDriverSF1",true)) {
		    SetSpawnInfo(playerid,69,253,-2411.5671,328.6443,34.7468,332.0064,-1,-1,-1,-1,-1,-1);
		}
		else if(!strcmp(npcname,"TaxiDriverSF2",true)) {
		    SetSpawnInfo(playerid,69,253,-1995.2744,137.3855,27.3897,181.3393,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"TaxiDriverLV1",true)) {
	        SetSpawnInfo(playerid,69,253,2083.1565,2468.5425,10.5992,270.1927,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"TaxiDriverLV2",true)) {
	        SetSpawnInfo(playerid,69,253,1434.2495,2603.4407,10.5218,269.9725,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"BusDriverLS",true)) {
	        SetSpawnInfo(playerid,69,255,1990.1984,-2479.2349,13.6447,0.0,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"BusDriverLV",true)) {
	        SetSpawnInfo(playerid,69,255,1495.1095,1635.3882,10.9130,0.0,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"BusDriverSF",true)) {
	        SetSpawnInfo(playerid,69,255,-1491.0757,-20.1990,14.2469,0.0,-1,-1,-1,-1,-1,-1);
		}
	 	else if(!strcmp(npcname,"Vika_Jefferson",true)) {
	 	
	        SetSpawnInfo(playerid,69,40, 2214.4048,-1150.8993,1025.7969, 270.0, -1,-1,-1,-1,-1,-1);
			SetPlayerInterior(playerid, 15);
			SetPlayerVirtualWorld(playerid, 15);
			
			/*new strtmp[8+24+3];
			format(strtmp, sizeof(strtmp), "%s [%d]", npcname, ReturnUser(npcname));
			Label = Create3DTextLabel(strtmp, COLOR_NEWBIE, 0.0,0.0,0.0, 15.0,0,1);
			Attach3DTextLabelToPlayer(Label, ReturnUser(npcname), 0.0, 0.0, 0.1);*/
			
		}
		new strtmp[8+24+3];
		format(strtmp, sizeof(strtmp), "%s [%d]", npcname, ReturnUser(npcname));
		if(!strcmp(npcname,"Vika_Jefferson",true))  Create3DTextLabel(strtmp,  GetPlayerColor(playerid) >>> 8, 0.0,0.0,0.0, 15.0,15,1);
		else Label = Create3DTextLabel(strtmp, COLOR_NEWBIE, 0.0,0.0,0.0, 30.0,0,0);
		Attach3DTextLabelToPlayer(Label, ReturnUser(npcname), 0.0, 0.0, 0.1);
		return 1;
	}
	return 0;
}

//-------------------------------------------------

public OnPlayerSpawn(playerid)
{//ф-и€ должна вызыватьс€ после того как загруз€тьс€ тачки,а т.к. ‘— груз€тс€ первыми и быстрее, значит надо делать через таймер
//или грузить скрипт после создани€ тачек
	//if(!IsPlayerNPC(playerid)) return 1; // We only deal with NPC players in this script
	if(IsPlayerNPC(playerid))
	{
		new npcname[MAX_PLAYER_NAME];
		GetPlayerName(playerid,npcname, sizeof(npcname));
		if(!strcmp(npcname,"TrainDriverLS",true)) {
		    //if(IsValidVehicle(NPCCar[0])) {
		    if( NPCCar[0] > 0 && NPCCar[0] != INVALID_VEHICLE_ID) {
				PutPlayerInVehicle(playerid,NPCCar[0],0);
		    	printf("PutPlayerInVehicle(playerid:%d, NPCCar[0]:%d)", playerid, NPCCar[0]);
		    }
		    else printf("* There are %d INVALID spawned vehicles on this server.", NPCCar[0]);
		    SetPlayerColor(playerid,COLOR_GREEN);
		}
		else if(!strcmp(npcname,"TrainDriverSF",true)) {//+4
			PutPlayerInVehicle(playerid,NPCCar[1],0);
	    	printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[1]);
		    SetPlayerColor(playerid,COLOR_GREEN);
		}
		else if(!strcmp(npcname,"TrainDriverLV",true)) {//+4
	        PutPlayerInVehicle(playerid,NPCCar[2],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[2]);
	        SetPlayerColor(playerid,COLOR_GREEN);
	 	}
		else if(!strcmp(npcname,"TramDriverSF",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[3],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[3]);
		    SetPlayerColor(playerid,COLOR_WHITE);
		}
		else if(!strcmp(npcname,"PilotLS",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[4],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[4]);
		    SetPlayerColor(playerid,COLOR_PURPLE);
		}
		else if(!strcmp(npcname,"PilotSF",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[5],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[5]);
		    SetPlayerColor(playerid,COLOR_PURPLE);
		}
		else if(!strcmp(npcname,"PilotLV",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[6],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[6]);
		    SetPlayerColor(playerid,COLOR_PURPLE);
		}
		else if(!strcmp(npcname,"TaxiDriverLS1",true)) {
		    if( NPCCar[7] > 0 && NPCCar[7] != INVALID_VEHICLE_ID) {
		    	PutPlayerInVehicle(playerid,NPCCar[7],0);
		    	printf("PutPlayerInVehicle(playerid:%d, NPCCar[%d]:%d)", playerid, 7, NPCCar[7]);
		    }
		    else printf("* There are %d INVALID spawned vehicles on this server.", NPCCar[7]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverLS2",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[8],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[8]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverSF1",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[9],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[9]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverSF2",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[10],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[10]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverLV1",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[11],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[11]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverLV2",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[12],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[12]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"BusDriverLS",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[13],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[13]);
		    SetPlayerColor(playerid,COLOR_ORANGE);
		}
		else if(!strcmp(npcname,"BusDriverLV",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[14],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[14]);
		    SetPlayerColor(playerid,COLOR_ORANGE);
		}
		else if(!strcmp(npcname,"BusDriverSF",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[15],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[15]);
		    SetPlayerColor(playerid,COLOR_ORANGE);
		}
		else if(!strcmp(npcname,"Vika_Jefferson",true)) {
		    SetPlayerColor(playerid, COLOR_NEWBIE);
			//PreloadAnimLibEx(playerid);
			
			SetPlayerFacingAngle(playerid, 312.8140);
			SetCameraBehindPlayer(playerid);
			//ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 1000);
			SetPlayerPos(playerid,2220.9819,-1151.9783,1025.7969);
			//ApplyAnimation(playerid, "PED", "SEAT_down", 4.0,0,1,1,1,0, 1);
			//SetTimerEx("WaitApplyAnimation", 25000, 0, "d", playerid);
		}
	}
	return 1;
}

/*public WaitApplyAnimation(playerid)
{
	ApplyAnimation(playerid, "PED", "SEAT_down", 4.1,0,1,1,1,0, 1);
}*/
stock PreloadAnimLibEx(playerid)
{
	if(GetPVarInt(playerid, "AnimLibsPreloaded") == 0)
	{
		PreloadAnimLib(playerid, "BASEBALL");
   		PreloadAnimLib(playerid, "BEACH");
		PreloadAnimLib(playerid, "benchpress");
		PreloadAnimLib(playerid, "BD_FIRE");
   		PreloadAnimLib(playerid, "BOMBER");
   		PreloadAnimLib(playerid, "CAMERA");
		PreloadAnimLib(playerid, "CAR_CHAT");
		PreloadAnimLib(playerid, "CARRY");
		PreloadAnimLib(playerid, "CASINO");
		PreloadAnimLib(playerid, "COP_AMBIENT");
 		PreloadAnimLib(playerid, "CRACK");
		PreloadAnimLib(playerid, "DAM_JUMP");
    	PreloadAnimLib(playerid, "DEALER");
		PreloadAnimLib(playerid, "DODGE");
    	PreloadAnimLib(playerid, "FOOD");
		PreloadAnimLib(playerid, "GANGS");
		PreloadAnimLib(playerid, "GRAVEYARD");
		PreloadAnimLib(playerid, "HEIST9");
		PreloadAnimLib(playerid, "INT_HOUSE");
		PreloadAnimLib(playerid, "INT_OFFICE");
		PreloadAnimLib(playerid, "KISSING");
		PreloadAnimLib(playerid, "LOWRIDER");
		PreloadAnimLib(playerid, "MD_CHASE");
    	PreloadAnimLib(playerid, "ON_LOOKERS");
		PreloadAnimLib(playerid, "PARK");
		PreloadAnimLib(playerid, "PAULNMAC");
		PreloadAnimLib(playerid, "PED");
		PreloadAnimLib(playerid, "RYDER");
   		PreloadAnimLib(playerid, "RAPPING");
   		PreloadAnimLib(playerid, "RIOT");
    	PreloadAnimLib(playerid, "SHOP");
   		PreloadAnimLib(playerid, "SMOKING");
		PreloadAnimLib(playerid, "SNM");
		PreloadAnimLib(playerid, "STRIP");
		PreloadAnimLib(playerid, "SUNBATHE");
		PreloadAnimLib(playerid, "SWAT");
    	PreloadAnimLib(playerid, "SWEET");
		SetPVarInt(playerid, "AnimLibsPreloaded", 1);
	}
}
stock PreloadAnimLib(playerid, animlib[])
{
	return ApplyAnimation(playerid, animlib,"null",0.0,0,0,0,0,0,1);
}
/*
public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(IsPlayerNPC(playerid))
	{
		new npcname[MAX_PLAYER_NAME];
		GetPlayerName(playerid,npcname, sizeof(npcname));
		if(!strcmp(npcname,"Vika_Jefferson",true)) {
			ApplyAnimation(playerid, "PED", "SEAT_down", 4.0, 0, 1, 1, 1, 0);
		}
	}
	return 1;
}*/

// by OKStyle
public OnPlayerStreamIn(playerid, forplayerid)
{
	//if(IsPlayerNPC(playerid))
	//{//выполнитс€ дл€ всех ботов
		//ApplyAnimation(playerid, "PED", "SEAT_down", 4.1,0,1,1,1,0, 1);
	    /*#pragma unused forplayerid
	    new aindex = GetPlayerAnimationIndex(playerid);
	    if(aindex > 0)
	    {
	        new animlib[32], animname[32];
	        GetAnimationName(aindex, animlib, sizeof(animlib), animname, sizeof(animname));
	        ApplyAnimation(playerid, animlib, animname, 4.0,0,1,1,0,0, 1);
	    }*/
    //}
    return 1;
}

public OnRemoteNPCCar(vehicleid)//vehicleid == NPCCar[i]
{
	NPCCar[npc_veh] = vehicleid;
	printf("OnRemoteNPCCar.NPCCar[%d] = %d", npc_veh, NPCCar[npc_veh]);
	npc_veh ++;
}
public OnRemotePlayerSpawn(playerid)
{
	//if(!IsPlayerNPC(playerid)) return 1; // We only deal with NPC players in this script
	if(IsPlayerNPC(playerid))
	{
		new npcname[MAX_PLAYER_NAME];
		GetPlayerName(playerid,npcname, sizeof(npcname));
		if(!strcmp(npcname,"TrainDriverLS",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[0],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[0]);
		    SetPlayerColor(playerid,COLOR_GREEN);
		}
		else if(!strcmp(npcname,"TrainDriverSF",true)) {//+4
		    PutPlayerInVehicle(playerid,NPCCar[1],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[1]);
		    SetPlayerColor(playerid,COLOR_GREEN);
		}
		else if(!strcmp(npcname,"TrainDriverLV",true)) {//+4
	        PutPlayerInVehicle(playerid,NPCCar[2],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[2]);
	        SetPlayerColor(playerid,COLOR_GREEN);
	 	}
		else if(!strcmp(npcname,"TramDriverSF",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[3],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[3]);
		    SetPlayerColor(playerid,COLOR_WHITE);
		}
		else if(!strcmp(npcname,"PilotLS",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[4],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[4]);
		    SetPlayerColor(playerid,COLOR_PURPLE);
		}
		else if(!strcmp(npcname,"PilotSF",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[5],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[5]);
		    SetPlayerColor(playerid,COLOR_PURPLE);
		}
		else if(!strcmp(npcname,"PilotLV",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[6],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[6]);
		    SetPlayerColor(playerid,COLOR_PURPLE);
		}
		else if(!strcmp(npcname,"TaxiDriverLS1",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[7],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar[%d]:%d)", playerid, 7, NPCCar[7]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverLS2",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[8],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[8]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverSF1",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[9],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[9]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverSF2",true)) {
		    PutPlayerInVehicle(playerid,NPCCar[10],0);
		    printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[10]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverLV1",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[11],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[11]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"TaxiDriverLV2",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[12],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[12]);
		    SetPlayerColor(playerid, COLOR_YELLOW);
		}
		else if(!strcmp(npcname,"BusDriverLS",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[13],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[13]);
		    SetPlayerColor(playerid,COLOR_ORANGE);
		}
		else if(!strcmp(npcname,"BusDriverLV",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[14],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[14]);
		    SetPlayerColor(playerid,COLOR_ORANGE);
		}
		else if(!strcmp(npcname,"BusDriverSF",true)) {
	        PutPlayerInVehicle(playerid,NPCCar[15],0);
	        printf("PutPlayerInVehicle(playerid:%d, NPCCar:%d)", playerid, NPCCar[15]);
		    SetPlayerColor(playerid,COLOR_ORANGE);
		}
		else if(!strcmp(npcname,"Vika_Jefferson",true)) {
		    SetPlayerColor(playerid, COLOR_NEWBIE);
			//PreloadAnimLibEx(playerid);

			SetPlayerFacingAngle(playerid, 312.8140);
			SetCameraBehindPlayer(playerid);
			//ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 1000);
			SetPlayerPos(playerid,2220.9819,-1151.9783,1025.7969);
			//ApplyAnimation(playerid, "PED", "SEAT_down", 4.0,0,1,1,1,0, 1);
			//SetTimerEx("WaitApplyAnimation", 25000, 0, "d", playerid);
		}
	}
}

/*public OnPlayerCommandText(playerid, cmdtext[])
{
	new strcmd[256+1], cmd[20], idx;
	cmd = strtok(cmdtext, idx);
 	if(!strcmp(cmd, "/NPCrestart", true) || !strcmp(cmd, "/NPCres", true))
	{
        if( //PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6 &&//может крашить сервер
			PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   ¬ы не уполномочены использовать эту команду !");
            return 1;
        }
		//foreach(Bot, i)
		for(new i=0; i<GetMaxPlayers(); i++)
		{
			if( !IsPlayerConnected(i) ) continue;
			if( !IsPlayerNPC(i) ) continue;
			CallRemoteFunction("OnRemotePlayerSpawn", "i", i);//может крашить сервер
		}
		format(strcmd, sizeof(strcmd), "AdmCmd: %s рестартнул NPC транспорт.", PlayerName(playerid));
		//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 5);
		SendClientMessage(playerid, -1, strcmd);
	}
	return 1;
}*/

stock PlayerName(playerid)
{
	new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
	return name;
}

//----------------------------------------------------------

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

//-------------------------------------------------
// EOF

stock ReturnUser(text[], playerid = INVALID_PLAYER_ID)
{
	new pos = 0;
	while(text[pos] < 0x21) // Strip out leading spaces //”дал€ет свободное место
	{
		if(text[pos] == 0) return INVALID_PLAYER_ID; // No passed text //Ќет текста на входе
		pos++;
	}
	new userid = INVALID_PLAYER_ID;
	if(IsNumeric(text[pos])) // Check whole passed str - ѕроверьте целую прошедшую строку
	{   //если строка представлена в виде числа
		// If they have a numeric name you have a problem (although names are checked on id failure)
		// ≈сли у них есть числовое им€ у вас есть проблема (хот€ имена проверены в неудаче)
		userid = strval(text[pos]);
		if(userid >= 0 && userid < MAX_PLAYERS)// && !IsPlayerNPC(userid)
		{
			if(!IsPlayerConnected(userid))	userid = INVALID_PLAYER_ID;
			else return userid; // A player was found
		}
	}
	// They entered [part of] a name or the id search failed (check names just incase)
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME+1];
	//foreach(Player, i)
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if( !IsPlayerConnected(i)) continue;
		GetPlayerName(i, name, sizeof(name));
		if(strcmp(name, text[pos], true, len) == 0) // Check segment of name
		{   //провер€ем совпадает ли введенное им€ с одним из онлайн игроков
			if(len == strlen(name)) // Exact match //более “очна€ проверка
			{   //если длина также совпадает
				return i; // Return the exact player on an exact match
				//¬озвращает точного указанного игрока ID и выходит из ф-ии
			}
			else // Partial match //„астична€ проверка
			//¬ противном случае если есть два игрока:
			//Me и MeYou вс€кий раз, когда ¬ы ввели Me это должно найти оба
			//» никогда не быть способным возвращать просто Me id
			{   //если введена не полна€ часть имени, то совпадение частичное
				count++;
				userid = i;//записываем userid =
			}
		}
	}
	if(count != 1)
	{
		if(playerid != INVALID_PLAYER_ID)// && !IsPlayerNPC(playerid)
		{
			//if(count) ABroadCast(COLOR_RED, "Error: Multiple users found, please narrow earch", 1);
			//else ABroadCast(COLOR_RED, "Error: No matching user found", 1);
			if(count) SendClientMessageToAll(0xFF0000FF, "Error: Multiple users found, please narrow earch");
			else SendClientMessageToAll(0xFF0000FF, "Error: No matching user found");
		}
		userid = INVALID_PLAYER_ID;
	}
	return userid; // INVALID_USER_ID for bad return
}
stock IsNumeric(const str[])
{
	new length = strlen(str);
	if(length == 0) return 0;
	for(new i = 0; i < length; i++)
    {
		if((str[i] > '9' || str[i] < '0' && str[i] != '-' && str[i] != '+') // Not a number,'+' or '-'
             || (str[i] == '-' && i != 0)                                             // A '-' but not at first.
             || (str[i] == '+' && i != 0)                                             // A '+' but not at first.
		   ) return 0;
    }
	if(length == 1 && (str[0] == '-' || str[0] == '+')) return 0;
	return 1;
}

