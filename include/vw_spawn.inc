//РАСФОРМИРОВАТЬ


// система выбора спавна
//new player_request[MAX_PLAYERS];
//new camera_load_fix[MAX_PLAYERS];
//new player_select_spawn[MAX_PLAYERS];
//new p_reg_acc[MAX_PLAYERS];

new Float:JailSpawnLS[3][4] = {
{264.0578,77.5677,1001.0391,270.3100},//спаунить в полиц. департаменте ЛС
{264.0578,82.0639,1001.0391,270.3100},
{264.0578,86.8017,1001.0391,270.3100}
};

new Float:JailSpawnSF[4][4] = {
{227.7224,109.6645,999.0156,0.7967},//спаунить в полиц. департаменте CФ
{223.4229,109.7885,999.0156,0.2239},
{219.5197,110.2443,999.0156,0.8506},
{215.6135,110.2192,999.0156,0.0439}
};

new Float:JailSpawnLV[3][4] = {
{193.8304,174.6278,1003.0234,0.4874},//спаунить в полиц. департаменте ЛВ
{198.0776,174.5540,1003.0234,0.1740},
{198.0627,162.1720,1003.0300,180.7757}
};

new Float:aPoliceSpawnsLS[2][4] = {
{1568.2250,-1693.5483,5.8906,177.0983},//спаунить в полиц. департаменте ЛС
{1530.6913,-1669.4760,6.2188,270.0}
//{614.8000,-608.2000,17.2000,0.0000},//RED COUNTY
//{611.5000,-607.8000,17.2000,0.0000}
};

new Float:aPoliceSpawnsSF[2][4] = {
{-1604.8442,732.9442,-5.2344,37.6041},//спаунить в полиц. департаменте СФ
{-1614.1016,676.8522,-4.9063,270.0}
};

new Float:aPoliceSpawnsLV[2][4] = {
{2343.4553,2455.5994,14.9688,96.5022},//спаунить в полиц. департаменте ЛВ
{2293.3511,2468.5647,10.8203,270.0}
};

new Float:aMedPlayerSpawns[4][4] = {//для медиков
//{1173.2017,1346.7750,10.9219,180.0},//спаунить В Центральной Больнице ЛС
{1177.9152,-1323.5153,14.0943,264.5785},//спаунить возле Центральной Больнице ЛС
{2034.6453,-1403.5216,17.2826,180.0},//спаунить возле Больнице ЛС
{-2656.0393,635.0596,14.4531,180.0},//спаунить возле Больнице СФ
{1609.5922,1820.9641,10.8280,348.1614}//спаунить возле Больнице ЛВ
};

new Float:aMedPatientSpawns[3][4] = {//для медиков
{1170.0757,1355.1091,10.9219,183.7600},//спаунить в Центральной Больнице ЛС
{1170.3567,1354.6479,10.9219,186.5800},//спаунить в Больнице СФ
{1170.1241,1355.0614,10.9219,179.0600}//спаунить вБольнице ЛВ
};
//==============================================================================
/*new Float:aRandomPlayerSpawns[9][3] = {
{1153.8461,-1770.4789,16.5938},
{1153.9461,-1770.4789,16.5938},
{1154.0461,-1770.4789,16.5938},
{1154.1461,-1770.4789,16.5938},

{1154.2461,-1770.4789,16.5938},

{1154.3461,-1770.4789,16.5938},
{1154.4461,-1770.4789,16.5938},
{1154.5461,-1770.4789,16.5938},
{1154.6461,-1770.4789,16.5938}
};
*/
/*
new Float:aInviteSpawns[10][4] = {
{-1976.5912,166.1818,36.9623,272.6393},
{-1975.8610,162.1945,36.9623,272.0126},
{-1975.7461,157.5404,36.9623,276.1093},
{-1975.2136,151.4920,36.9623,268.2993},
{-1974.9963,145.3430,36.9623,269.2628},
{-1975.5842,140.8170,36.9623,269.8895},
{-1975.7874,134.0368,36.9623,271.7696},
{-1975.1681,129.0926,36.9623,270.8531},
{-1975.9069,121.4700,36.9623,270.5631},
{-1975.3311,112.7078,36.9623,267.7665}
};*/


stock spawn_OnPlayerRequestClass(playerid, classid)
{
	if(	PlayerInfo[playerid][pHouse] == NOT_KEY &&
		PlayerInfo[playerid][pAccount] == 0 &&
		PlayerInfo[playerid][pMember] != DoD )
	{
   		SetPlayerCameraPos(playerid, -1300.8754,68.0546,129.4823);
		SetPlayerCameraLookAt(playerid, -1817.9412,769.3878,132.6589);
		SendClientMessage(playerid, COLOR_SYSTEM, "   Вы появитесь по основному месту респауна!");

		gSpawn[playerid] = 0;
		SetPVarInt(playerid, "SpawnChange", 2);
		SetPlayerSpawn(playerid);//запускаем ф-ию установки спауна игрока
		assault_OnPlayerRequestClass(playerid);
		box_OnPlayerRequestClass(playerid);
		return 1;
	}
	
	if(classid == 1 && PlayerInfo[playerid][pReason] != 0)
	{
		//SetPlayerVirtualWorldEx(playerid, 0);
		//SetPlayerInteriorEx(playerid, 0);
   		SetPlayerCameraPos(playerid, -1300.8754,68.0546,129.4823);
		SetPlayerCameraLookAt(playerid, -1817.9412,769.3878,132.6589);
		if(GetPVarInt(playerid, "SpawnSelection") == 1)
		{
			GameTextForPlayerEx(playerid, "~y~> ~p~Motel Spawn ~y~<",5000,4);
			SendClientMessage(playerid, COLOR_SYSTEM, "   Вы теперь будете появляться по основному месту респауна!");
			gSpawn[playerid] = 0;
	    }
		else
		{
			GameTextForPlayerEx(playerid, "~y~>      ~g~Job Spawn     ~y~<",5000,4);
			SendClientMessage(playerid, COLOR_SYSTEM, "   Вы теперь будете появляться по месту службы, если она у вас есть!");
			gSpawn[playerid] = 1;
		}
		SetPVarInt(playerid, "SpawnChange", 1);
	}
	else if(classid == 2 && PlayerInfo[playerid][pReason] != 0)
	{
		//SetPlayerVirtualWorldEx(playerid, 0);
		//SetPlayerInteriorEx(playerid, 0);
   		SetPlayerCameraPos(playerid, 1310.6155,1675.9182,110.7390);
		SetPlayerCameraLookAt(playerid, 2285.2944,1919.3756,68.2275);
		if(GetPVarInt(playerid, "SpawnSelection") == 1)
		{
			GameTextForPlayerEx(playerid, "~y~>  ~h~Home Spawn  ~y~<",5000,4);
			SendClientMessage(playerid, COLOR_SYSTEM, "   Вы будете теперь возраждаться в Доме!");
	    }
		else
		{
			GameTextForPlayerEx(playerid, "~y~> ~p~Home/Motel Spawn ~y~<",5000,4);
			SendClientMessage(playerid, COLOR_SYSTEM, "   Вы будете теперь возраждаться в Доме или по основному месту респауна!");
		}
		gSpawn[playerid] = 0;
		SetPVarInt(playerid, "SpawnChange", 2);
	}
	else //if(classid == 0)
	{
		//SetPlayerVirtualWorldEx(playerid, 0);
		//SetPlayerInteriorEx(playerid, 0);
		SetPlayerCameraPos(playerid, 1630.6136,-2286.0298,110.0);
		SetPlayerCameraLookAt(playerid, 1887.6034,-1682.1442,47.6167);
		if(GetPVarInt(playerid, "SpawnSelection") == 1 && PlayerInfo[playerid][pReason] != 0)
		{
			GameTextForPlayerEx(playerid, "~y~>   ~g~Job Spawn   ~y~<",5000,4);
			SendClientMessage(playerid, COLOR_SYSTEM, "   Вы теперь будете появляться по основному месту службы, если она у вас есть!");
			gSpawn[playerid] = 1;
			SetPVarInt(playerid, "SpawnChange", 1);
		}
		else
		{   //если игрок только что зашёл в игру
			GameTextForPlayerEx(playerid, "~y~>   ~h~Place Output   ~y~<",5000,4);//3500
			if(PlayerInfo[playerid][pLevel] != 1) SendClientMessage(playerid, COLOR_SYSTEM, "   Вы появитесь в точке выхода из игры!");
			gSpawn[playerid] = 0;
			SetPVarInt(playerid, "SpawnChange", 0);
		}
		PlayerInfo[playerid][pReason] = -1;
	}
	return 1;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//SpawnSTEP7
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//Функция Изменения информацию по размещению указанного игрока в стартовой позиции, но она не спаунит игрока
stock SetPlayerSpawn(playerid)//Выполняется из OnPlayerRequestClass и OnPlayerDeath //при состоянии OnPlayerDeath PLAYER_STATE_WASTED
{
	if(CHECKING[PlayerSpawn])
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Begin SetPlayerSpawn(playerid: %d gSpawn: %d gSpawnChange: %d)",
			playerid, gSpawn[playerid], GetPVarInt(playerid, "SpawnChange"));
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}

	if(PlayerInfo[playerid][pJailed] == 1)
	{   //если вы в тюрьме LSPD
	    PlayerInfo[playerid][pInt] = 6;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = 246;//LSPD
	    new rand = random(sizeof(JailSpawnLS));
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
			JailSpawnLS[rand][0],JailSpawnLS[rand][1],JailSpawnLS[rand][2], JailSpawnLS[rand][3],-1, -1, -1, -1, -1, -1);
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы недосидели свой тюремный срок, сидите и думайте над своим поведением.");
		SetPlayerWorldBoundsEx(playerid, checkCoords[CP_LSPD][maxx], checkCoords[CP_LSPD][minx], checkCoords[CP_LSPD][maxy], checkCoords[CP_LSPD][miny]);
		SetPVarInt(playerid, "gWorldBounds", 1);
		return 1;
	}
	else if(PlayerInfo[playerid][pJailed] == 2)
	{   //если вы в тюрьме SFPD
	    PlayerInfo[playerid][pInt] = 10;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = 247;//SFPD

	    new rand = random(sizeof(JailSpawnSF));
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
			JailSpawnSF[rand][0],JailSpawnSF[rand][1],JailSpawnSF[rand][2], JailSpawnSF[rand][3],-1, -1, -1, -1, -1, -1);
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы вышли из игры во время задержания, сидите и думайте над своим поведением.");
		SetPlayerWorldBoundsEx(playerid, checkCoords[CP_SFPD][maxx], checkCoords[CP_SFPD][minx], checkCoords[CP_SFPD][maxy], checkCoords[CP_SFPD][miny]);
		SetPVarInt(playerid, "gWorldBounds", 1);
		return 1;
	}
	else if(PlayerInfo[playerid][pJailed] == 3)
	{   //если вы в тюрьме LVPD
	    PlayerInfo[playerid][pInt] = 3;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = 248;//LVPD
		//{Вы - в Тюрьме на %d минут за сопротивление при задержании.

	    new rand = random(sizeof(JailSpawnLV));
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
			JailSpawnLV[rand][0],JailSpawnLV[rand][1],JailSpawnLV[rand][2], JailSpawnLV[rand][3],-1, -1, -1, -1, -1, -1);
		//SendClientMessage(playerid, COLOR_BLUEGREY, "Вы не оплатили минусовой баланс на момент зарплаты или убиты за сопротивление при задержании.");
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы убиты за сопротивление при задержании.");
		SetPlayerWorldBoundsEx(playerid, checkCoords[CP_LVPD_DOWNFLOOR][maxx], checkCoords[CP_LVPD_DOWNFLOOR][minx], checkCoords[CP_LVPD_DOWNFLOOR][maxy], checkCoords[CP_LVPD_DOWNFLOOR][miny]);
		SetPVarInt(playerid, "gWorldBounds", 1);
		return 1;
	}
	else if(PlayerInfo[playerid][pJailed] == 5)
	{   //если вы в тюрьме LCN
	    PlayerInfo[playerid][pInt] = 3;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = 243;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
			943.3190,-51.0405,1001.1172,268.8511, -1, -1, -1, -1, -1, -1);
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы вышли из игры связанные. Вы находитесь в заложниках у La Cosa Nostrа.");
		return 1;
	}
	else if(PlayerInfo[playerid][pJailed] == 6)
	{   //если вы в тюрьме Yakuza
	    PlayerInfo[playerid][pInt] = 1;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = 244;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
			-2170.2839,645.4468,1057.5938,186.1609,-1, -1, -1, -1, -1, -1);
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы вышли из игры связанные. Вы находитесь в заложниках у Yakuza.");
		return 1;
	}
	else if(PlayerInfo[playerid][pJailed] == 8)
	{   //если вы в тюрьме Hitman
	    PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		//PlayerInfo[playerid][pLocal] = 242;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
			-688.2499,933.8837,13.6328,1.5109,-1, -1, -1, -1, -1, -1);
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы вышли из игры связанные. Вы находитесь в заложниках у Агентства Hitman.");
		return 1;
	}

//==============================================================================
	/*if(	gMedicBill[playerid] != 0 && !IsAGangs(playerid) && PlayerInfo[playerid][pMember] != DoD && PlayerInfo[playerid][pJailed] != 10 && !IsAFamilyMember(playerid) && PlayerInfo[playerid][pMember] != DoH)
	{
		if(PlayerInfo[playerid][pMember] == DoH) gMedicBill[playerid] = 1;
		switch(gMedicBill[playerid])
		{
		    case 1: { PlayerInfo[playerid][pLocal] = 201; SetPlayerVirtualWorldEx(playerid, INT_MEDIC_LS), SetPlayerInteriorEx(playerid, INT_MEDIC_LS); if(fix_med_text[playerid] == 0 ) SendClientMessage(playerid, COLOR_PINK, "Вы доставлены в Больницу Los Santos."); fix_med_text[playerid] = 3; }
		    case 2: { PlayerInfo[playerid][pLocal] = 202; SetPlayerVirtualWorldEx(playerid, INT_MEDIC_SF), SetPlayerInteriorEx(playerid, INT_MEDIC_SF); if(fix_med_text[playerid] == 0 ) SendClientMessage(playerid, COLOR_PINK, "Вы доставлены в Больницу San Fierro."); fix_med_text[playerid] = 3; }
		    case 3: { PlayerInfo[playerid][pLocal] = 203; SetPlayerVirtualWorldEx(playerid, INT_MEDIC_LV), SetPlayerInteriorEx(playerid, INT_MEDIC_LV); if(fix_med_text[playerid] == 0 ) SendClientMessage(playerid, COLOR_PINK, "Вы доставлены в Больницу Las Venturas."); fix_med_text[playerid] = 3;  }
		}
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel], 1403.5874,-22.6844,1000.9175,160.5273,-1, -1, -1, -1, -1, -1);
		SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		return 1;
	}*/
	if(	gMedicBill[playerid] == 1 &&
		!IsAGangs(playerid) &&
		PlayerInfo[playerid][pMember] != DoD &&
		PlayerInfo[playerid][pJailed] != 10 &&
		PlayerInfo[playerid][pLevel] > 3
	//LastState[playerid] == PLAYER_STATE_KILLED)
		//if(PlayerInfo[playerid][pHealth] < floatadd(PlayerInfo[playerid][pSHealth], 50.0) )
		//|| IsAtHospital(playerid)//если игрок входит в игру по больнице
	  )
	{   //если флаг поднят на прохождение лечения //если вы были убиты //если вы были в больнице
	    //если вы находились в ЛВ
	    if(PlayerInfo[playerid][pMember] == DoD)
		{   //Вы будете теперь появляться на Авианосце в SF
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				-1349.4200,488.6331,21.2533,182.4450,-1, -1, -1, -1, -1, -1);
		}
		if(PlayerInfo[playerid][pMember] != DoH) gMedicBill[playerid] = 1;


		if(	PlayerInZone[playerid] == MI_LAS_VENTURAS || //PlayerInZone[playerid] == MI_FLINT_COUNTY ||
			PlayerInZone[playerid] == MI_FLINT_COUNTY  || PlayerInZone[playerid] == MI_BONE_COUNTY ||
			PlayerInZone[playerid] == MI_TIERRA_ROBADA_UP || PlayerInZone[playerid] == MI_TIERRA_ROBADA_D)
		{   //спаунить В Больнице ЛВ
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 203;
			PlayerInfo[playerid][pLocal] = 203;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				aMedPatientSpawns[2][0],aMedPatientSpawns[2][1],aMedPatientSpawns[2][2],aMedPatientSpawns[2][3],-1, -1, -1, -1, -1, -1);

			SendClientMessage(playerid, COLOR_PINK, "Вы доставлены в Больницу LAS VENTURAS с тяжёлыми огнестрельными ранениями.");
			return 1;
		}
		else if(PlayerInZone[playerid] == MI_SAN_FIERRO || PlayerInZone[playerid] == MI_WHETSTONE)
		{   //спаунить В Больнице СФ
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 202;
			PlayerInfo[playerid][pLocal] = 202;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				aMedPatientSpawns[1][0],aMedPatientSpawns[1][1],aMedPatientSpawns[1][2],aMedPatientSpawns[1][3],-1, -1, -1, -1, -1, -1);
			SendClientMessage(playerid, COLOR_PINK, "Вы доставлены в Больницу SAN FIERRO с тяжёлыми огнестрельными ранениями.");
			return 1;
		}
		else //if(PlayerInZone[playerid] == MI_LOS_SANTOS || PlayerInZone[playerid] == MI_RED_COUNTY)
		{   //спаунить В Центральной Больнице ЛС
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 201;//201;
			PlayerInfo[playerid][pLocal] = 201;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				aMedPatientSpawns[0][0],aMedPatientSpawns[0][1],aMedPatientSpawns[0][2],aMedPatientSpawns[0][3],-1, -1, -1, -1, -1, -1);
			SendClientMessage(playerid, COLOR_PINK, "Вы доставлены в Больницу LOS SANTOS с тяжёлыми огнестрельными ранениями.");
			return 1;
		}

	}

//==============================================================================
	if(gSpawn[playerid] == 0 && GetPVarInt(playerid, "SpawnChange") == 0
		&& PlayerInfo[playerid][pPos_x] != 0.0
		&& PlayerInfo[playerid][pPos_y] != 0.0
		&& PlayerInfo[playerid][pPos_z] != 0.0)//если игрок уже входил в игру, т.е. зареген
	{   //если игрок только что зашёл в игру - спаунить по месту выхода
		PlayerInfo[playerid][pInt] = GetPVarInt(playerid, "FirstInterior");
		PlayerInfo[playerid][pVirtual] = GetPVarInt(playerid, "FirstVirtual");
		PlayerInfo[playerid][pLocal] = GetPVarInt(playerid, "FirstLocal");
		if(PlayerInfo[playerid][pJailed] == 10)
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pChar],
				PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 0.0,
	           -1, -1, -1, -1, -1, -1);
        }
        else
        {
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 0.0,
	           -1, -1, -1, -1, -1, -1);
        }
		return 1;
	}
//==============================================================================
	//всё что выше должно выполняться даже если вы заключенный зоны 51, чтобы вас не кидало сразу на зону
	if(PlayerInfo[playerid][pJailed] == 10)
	{   //если вы на зоне
	    PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pChar],//myadd
			268.5777,1857.9351,9.8133, 0.0,-1, -1, -1, -1, -1, -1);
		SendClientMessage(playerid, COLOR_BLUEGREY, "Вы недосидели свой тюремный срок, ищите адвоката.");
		return 1;
	}

//==============================================================================
	if(PlayerInfo[playerid][pMember] == DoT && GetPVarInt(playerid, "SpawnChange") == 1)//Police Force spawn & FBI/ATF
	{   //если вы коп
		if(gSpawn[playerid] == 2)
		{   //спаунить в SF
		    new rand = random(sizeof(aPoliceSpawnsSF));
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aPoliceSpawnsSF[rand][0],aPoliceSpawnsSF[rand][1],aPoliceSpawnsSF[rand][2], aPoliceSpawnsSF[rand][3],-1, -1, -1, -1, -1, -1);
		}
		else if(gSpawn[playerid] == 3)
		{   //спаунить в LV
		    new rand = random(sizeof(aPoliceSpawnsLV));
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aPoliceSpawnsLV[rand][0],aPoliceSpawnsLV[rand][1],aPoliceSpawnsLV[rand][2], aPoliceSpawnsLV[rand][3], -1, -1, -1, -1, -1, -1);
		}
		else //if(gSpawn[playerid] == 1)
		{   //спаунить в LS
		    new rand = random(sizeof(aPoliceSpawnsLS));
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aPoliceSpawnsLS[rand][0],aPoliceSpawnsLS[rand][1],aPoliceSpawnsLS[rand][2], aPoliceSpawnsLS[rand][3],-1, -1, -1, -1, -1, -1);
		}
		return 1;
    }
	else if(PlayerInfo[playerid][pMember] == FBI && GetPVarInt(playerid, "SpawnChange") == 1)//Police Force spawn & FBI/ATF
	{   //если вы ФБР
		if(gSpawn[playerid] == 2)
		{   //спаунить в LV
		    new rand = random(sizeof(aPoliceSpawnsLV));
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aPoliceSpawnsLV[rand][0],aPoliceSpawnsLV[rand][1],aPoliceSpawnsLV[rand][2], aPoliceSpawnsLV[rand][3], -1, -1, -1, -1, -1, -1);
		}
		else if(gSpawn[playerid] == 3)
		{   //спаунить в LS
		    new rand = random(sizeof(aPoliceSpawnsLS));
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aPoliceSpawnsLS[rand][0],aPoliceSpawnsLS[rand][1],aPoliceSpawnsLS[rand][2], aPoliceSpawnsLS[rand][3],-1, -1, -1, -1, -1, -1);
		}
		else //if(gSpawn[playerid] == 1)
		{   //спаунить в SF
		    new rand = random(sizeof(aPoliceSpawnsSF));
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aPoliceSpawnsSF[rand][0],aPoliceSpawnsSF[rand][1],aPoliceSpawnsSF[rand][2], aPoliceSpawnsSF[rand][3],-1, -1, -1, -1, -1, -1);
		}
		return 1;
    }
	else if(PlayerInfo[playerid][pMember] == DoD && GetPVarInt(playerid, "SpawnChange") == 1)//National Guard spawn
	{   //если вы военный
		if(gSpawn[playerid] == 2)
		{   //Вы будете теперь появляться на Авианосце в SF
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				-1349.4200,488.6331,21.2533,182.4450,-1, -1, -1, -1, -1, -1);
		}
		else if(gSpawn[playerid] == 3)
		{   //Вы теперь будете возрождаться на Военной Базе
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				108.6259,1916.6233,18.5439, 273.9626,-1, -1, -1, -1, -1, -1);
		}
		else //if(gSpawn[playerid] == 1)
		{   //Вы будете теперь появляться на АвиаБазе
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				283.1560,2036.8771,17.6406,176.5818,-1, -1, -1, -1, -1, -1);
		}
		return 1;
	}
	else if(PlayerInfo[playerid][pMember] == DoH && GetPVarInt(playerid, "SpawnChange") == 1)//Fire/Ambulance spawn
	{   //если вы спасатель
		if(gSpawn[playerid] == 2)
		{   //спаунить В Больнице ЛВ
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;//203;
			PlayerInfo[playerid][pLocal] = FREEROAM;//203;//Hospital
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aMedPlayerSpawns[3][0],aMedPlayerSpawns[3][1],aMedPlayerSpawns[3][2],aMedPlayerSpawns[3][3],-1, -1, -1, -1, -1, -1);
		}
		else if(gSpawn[playerid] == 3)
		{   //спаунить В Центральной Больнице ЛС
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;//201;
			PlayerInfo[playerid][pLocal] = FREEROAM;//201;//Hospital
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aMedPlayerSpawns[0][0],aMedPlayerSpawns[0][1],aMedPlayerSpawns[0][2],aMedPlayerSpawns[0][3],-1, -1, -1, -1, -1, -1);
		}
		else if(gSpawn[playerid] == 4)
		{   //спаунить В Больнице ЛС
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;//Hospital
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aMedPlayerSpawns[1][0],aMedPlayerSpawns[1][1],aMedPlayerSpawns[1][2],aMedPlayerSpawns[1][3],-1, -1, -1, -1, -1, -1);
		}
		else //if(gSpawn[playerid] == 1)
		{   //спаунить В Больнице СФ
		    PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;//202;
			PlayerInfo[playerid][pLocal] = FREEROAM;//202;//Hospital
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				aMedPlayerSpawns[2][0],aMedPlayerSpawns[2][1],aMedPlayerSpawns[2][2],aMedPlayerSpawns[2][3],-1, -1, -1, -1, -1, -1);
		}
	    return 1;
	}
	else if(PlayerInfo[playerid][pMember] == LCN && GetPVarInt(playerid, "SpawnChange") == 1)//LaCosaNostra spawn
	{   //LCN
		//if(gSpawn[playerid] == 1)
		//{
	    PlayerInfo[playerid][pInt] = 3;
		PlayerInfo[playerid][pVirtual] = 0;
	    PlayerInfo[playerid][pLocal] = 243;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pChar],//myadd PlayerInfo[playerid][pChar]
			960.8127,-53.9257,1001.1172, 95.0584, -1, -1, -1, -1, -1, -1);
	    return 1;
	    //}
	}
	else if(PlayerInfo[playerid][pMember] == Yakuza && GetPVarInt(playerid, "SpawnChange") == 1)//Yakuza spawn
	{   //Yakudza
		//if(gSpawn[playerid] == 1)
		//{
	    PlayerInfo[playerid][pInt] = 1;//1
		PlayerInfo[playerid][pVirtual] = 0;
	    PlayerInfo[playerid][pLocal] = 244;//244
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pChar],//myadd PlayerInfo[playerid][pChar]
			-2158.1479,643.9607,1057.5938, 93.5935, -1, -1, -1, -1, -1, -1);
	    return 1;
		//}
	}
	else if(PlayerInfo[playerid][pMember] == DoJ && GetPVarInt(playerid, "SpawnChange") == 1)//Mayor spawn
	{   //Если Вы Мэр
		//if(gSpawn[playerid] == 1)
		//{
	    PlayerInfo[playerid][pInt] = 3;
		PlayerInfo[playerid][pVirtual] = 3;
		PlayerInfo[playerid][pLocal] = 241;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd Кабинет МЭРА
			//346.6554,162.2610,1025.7891, 90.0,-1, -1, -1, -1, -1, -1);
			//355.3329,213.1842,1008.3828,198.0546, -1,-1,-1,-1,-1,-1);
			361.6438,213.5513,1008.4828,87.9518, -1,-1,-1,-1,-1,-1);
	    return 1;
		//}
	}
    else if(PlayerInfo[playerid][pMember] == Hitman && GetPVarInt(playerid, "SpawnChange") == 1) //Hitman spawn
    {   //если вы наёмный убийца
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		//PlayerInfo[playerid][pLocal] = 242;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pChar],//PlayerInfo[playerid][pChar]
			-688.1303,936.8342,13.6328, 0.0, -1, -1, -1, -1, -1, -1);
        return 1;
		//}
    }
    else if( (PlayerInfo[playerid][pMember] == SAN)// || PlayerInfo[playerid][pJob] == PAPERBOY
	 	&& GetPVarInt(playerid, "SpawnChange") == 1) //News spawn
    {   //если вы репортёр
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 1;
		PlayerInfo[playerid][pVirtual] = 249;
		PlayerInfo[playerid][pLocal] = 249;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			2163.9585,1605.1295,999.9769,133.1994, -1, -1, -1, -1, -1, -1);
        return 1;
		//}
    }
    else if(PlayerInfo[playerid][pMember] == DoE && GetPVarInt(playerid, "SpawnChange") == 1) //Driving/Flying School spawn
    {   //если вы инструктор
		if(gSpawn[playerid] == 2)
		{   //спаунить в авиашколе
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				414.4144,2531.9580,19.1565, 4.6505, -1, -1, -1, -1, -1, -1);
		}
		else //if(gSpawn[playerid] == 1)
		{   //спаунить в автошколе
			PlayerInfo[playerid][pInt] = 3;
			PlayerInfo[playerid][pVirtual] = 3;
			PlayerInfo[playerid][pLocal] = 253;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				-2032.6810,-117.4816,1035.1719, 275.1114, -1, -1, -1, -1, -1, -1);
		}
       	return 1;
    }
	if(IsAGangs(playerid) && GetPVarInt(playerid, "SpawnChange") == 1)
	{   //если ты в банде
		//if(gSpawn[playerid] == 1)
		//{
	    new family = PlayerInfo[playerid][pMember];
		PlayerInfo[playerid][pInt] = FamilyInfo[family][fInterior];//myadd
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			FamilyInfo[family][fSpawns][0],FamilyInfo[family][fSpawns][1],FamilyInfo[family][fSpawns][2], FamilyInfo[family][fSpawns][3],-1, -1, -1, -1, -1, -1);
		return 1;
		//}
	}
	//--------------------------------------------------------------------------
    if(PlayerInfo[playerid][pJob] == ROADWORKER && GetPVarInt(playerid, "SpawnChange") == 1) //Дорожный рабочий spawn
    {
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			-253.5483,2603.2510,62.8582, 270.4709, -1, -1, -1, -1, -1, -1);
        return 1;
        //}
    }
    if(PlayerInfo[playerid][pJob] == DRUGDEALER) //НАРКОДИЛЛЕР spawn
    {   //может быть конфликт со спауном банды
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 5;
		PlayerInfo[playerid][pVirtual] = 5;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			320.2927,1121.9141,1083.8828, 180.0000, -1, -1, -1, -1, -1, -1);
		return 1;
       //}
    }
    else if(PlayerInfo[playerid][pJob] == AUTOBUYER && GetPVarInt(playerid, "SpawnChange") == 1) //СКУПЩИК spawn
    {//для скупщиков
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			2116.2334,2416.6816,10.8203,88.0434, -1, -1, -1, -1, -1, -1);
        return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == CARMECHANIC && GetPVarInt(playerid, "SpawnChange") == 1) //AutoMechanic spawn
    {
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			-103.6227,-1264.4902,3.1635, 127.9907, -1, -1, -1, -1, -1, -1);
        return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == FARMER && GetPVarInt(playerid, "SpawnChange") == 1) //для фермеров
    {
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			-18.9624,-270.4885,5.4297, 0.0000, -1, -1, -1, -1, -1, -1);
		return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == ARMSDEALER && GetPVarInt(playerid, "SpawnChange") == 1) //ОРУЖЕЙНИК spawn
    {	//может быть конфликт со спауном банды
		if(gSpawn[playerid] == 1)
		{
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pVirtual] = 0;
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				-2182.0100,-262.7700,40.7195,287.8279, -1, -1, -1, -1, -1, -1);
	        return 1;
        }
    }
    else if(PlayerInfo[playerid][pJob] == CARDEALER && GetPVarInt(playerid, "SpawnChange") == 1)
    {   //если вы автодилер
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			-1657.5237,1207.6644,13.6719, 90.0, -1, -1, -1, -1, -1, -1);
        return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == TAXIDRIVER && GetPVarInt(playerid, "SpawnChange") == 1)//для таксистов //Taxi Cab Company spawn
    {   //если вы таксист
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			-1978.5934,102.9237,27.6875, 90.0, -1, -1, -1, -1, -1, -1);
		return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == BUSDRIVER && GetPVarInt(playerid, "SpawnChange") == 1)//для
    {   //если вы водитель автобуса
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			1222.2764,-1814.3480,16.5938,4.9095, -1, -1, -1, -1, -1, -1);
		return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == TRUCKER && GetPVarInt(playerid, "SpawnChange") == 1) //HardDriver spawn
    {   //если вы дальнобойщик
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			//-49.9002,-269.6879,6.6332, 0.0,-1, -1, -1, -1, -1, -1);
			-49.8351,-274.3823,5.4297,177.7557, -1, -1, -1, -1, -1, -1);
		return 1;
        //}
    }
    else if(PlayerInfo[playerid][pJob] == TRASHMAN && GetPVarInt(playerid, "SpawnChange") == 1) //TrashMaster spawn
    {   //для мусорщиков
		//if(gSpawn[playerid] == 1)
		//{
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			//-49.9002,-269.6879,6.6332, 0.0,-1, -1, -1, -1, -1, -1);
			2194.6794,-1969.3612,13.7841,231.8455, -1, -1, -1, -1, -1, -1);
		return 1;
        //}
    }
	/*new house = PlayerInfo[playerid][pHouse];
	if(house != NOT_KEY)
	{   //если у вас есть дом
	    if(GetPVarInt(playerid, "SpawnChange") == 2) //If 1, then you get to your house, else spawn somewhere else
	    {   //если стартовая позиция установлена на дом
			if(PlayerInfo[playerid][pHouse] == 28) SetPlayerTime(playerid, 20, 0);
			PlayerInfo[playerid][pLocal] = house;
			PlayerInfo[playerid][pInt] = HouseInfo[house][hInt];
			PlayerInfo[playerid][pVirtual] = house;
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],//myadd
				HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ], 0.0,-1, -1, -1, -1, -1, -1);
			return 1;
		}
	}*/
	/*if( !strcmp(php_host, "vw-rp.net", true) )
	{
		//SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			//1654.0109,-1658.0770,22.5156, 180.3, -1, -1, -1, -1, -1, -1);
		//	1154.2461,-1770.4789,16.5938,357.4707, -1, -1, -1, -1, -1, -1); // new spawn

		new ran = random(sizeof(aRandomPlayerSpawns));
		SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			aRandomPlayerSpawns[ran][0],aRandomPlayerSpawns[ran][1],aRandomPlayerSpawns[ran][2], 0.0, -1, -1, -1, -1, -1, -1);

		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
	}*/
	//else
	//{
	PlayerInfo[playerid][pLocal] = FREEROAM;
	SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
		1733.7374,-1890.5610,13.5850,299.6649, -1, -1, -1, -1, -1, -1);

	SetPlayerVirtualWorldEx(playerid, 0);
	SetPlayerInteriorEx(playerid, 0);
		/*if(GetPVarInt(playerid, "RegTut"))
		{
			ShowPlayerDialogEx(playerid, 10000, DIALOG_STYLE_MSGBOX, "{000000}___",
				"{ffffff} - C тобой хочет познакомиться {928BC7}Тайлер{ffffff}. \nОн поможет тебе освоиться в штате.\n\nПоказать местоположение {928BC7}Тайлера{ffffff}?", "Да", "Нет");
		    DeletePVar(playerid, "RegTut");
	    }*/
	
		/*PlayerInfo[playerid][pInt] = 15;
		PlayerInfo[playerid][pVirtual] = 15;
		PlayerInfo[playerid][pLocal] = 254;
		new rand = random(7);
		if(rand == 0)//Number of the Hotel 2 - Minsk
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2235.8259,-1158.0253,1029.9043, 262.9963, -1, -1, -1, -1, -1, -1);
			//Изменяет информацию по размещению указанного игрока в стартовой позиции
		}
		else if(rand == 1)//Number of the Hotel 4 - Grodno
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2236.0105,-1168.7025,1029.9043, 46.8583, -1, -1, -1, -1, -1, -1);
		}
		else if(rand == 2)//Number of the Hotel 6 - Gomel
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2227.2993,-1183.5814,1029.9043, 359.5470, -1, -1, -1, -1, -1, -1);
		}
		else if(rand == 3)//Number of the Hotel 7 - Mogilev
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2207.7600,-1193.9304,1029.9043, 86.8966, -1, -1, -1, -1, -1, -1);
		}
		else if(rand == 4)//Number of the Hotel 10 - Vitebsk
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2198.4475,-1175.1149,1029.9043, 272.3543, -1, -1, -1, -1, -1, -1);
		}
		else if(rand == 5)//Number of the Hotel 11 - Brest
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2187.9270,-1153.9933,1029.9043, 232.4724, -1, -1, -1, -1, -1, -1);
		}
		else //if(rand == 6)//Number of the Hotel 12 - Russia
		{
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				2198.2603,-1158.9595,1029.9043, 172.4559, -1, -1, -1, -1, -1, -1);
		}*/
		/*else//если игрок ещё не прошёл анкетирование, т.е. не выбрал регион!!! Other
		{   //if(PlayerInfo[playerid][pOrigin] == 0)
			new ran = random(sizeof(aRandomPlayerSpawns));
			SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
				aRandomPlayerSpawns[ran][0],aRandomPlayerSpawns[ran][1],aRandomPlayerSpawns[ran][2], 270.0, -1, -1, -1, -1, -1, -1);
		}*/
	//}
	if(CHECKING[PlayerSpawn])
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "End SetPlayerSpawn(playerid: %d, Int: %d, Virt: %d, Loc: %d)",
			playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	return 1;
}//end SetPlayerSpawn


stock spawn_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(PlayerInfo[playerid][pInt] != 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться НЕ в интерьере !");
		return 1;
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться ВНЕ транспортного средства !");
		return 1;
	}
 	if( !IsAGangs(playerid) && !IsPlayerAdmin(playerid) && PlayerInfo[playerid][pAdmin] < 6) return 1;
	if(IsAGangs(playerid))
	{
		if(gInRacing[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить место возраждения когда участвуете в гонке.");
			return 1;
		}
		if(gOnDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить место возраждения на службе.");
			return 1;
		}
		if(gJobDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить место возраждения на дежурстве.");
			return 1;
		}
		if(PlayerInfo[playerid][pLevel] < 2)
		{
			SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете установить место возраждения на первом уровне !");
			return 1;
		}
		if(WantedPoints[playerid] > 0)
		{
			SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете установить место возраждения находясь в розыске !");
			return 1;
		}
	    if(PlayerCuffed[playerid] < MAX_PLAYERS-1)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить место возраждения находясь в наручниках !");
	        return 1;
	    }
		if(PlayerTied[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить место возраждения связанным !");
			return 1;
		}
		if(PlayerInfo[playerid][pJailed] > 0)
		{
			SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете установить место возраждения под арестом !");
			return 1;
		}
		if( IsPlayerInArea(playerid, specialzone[10]) )
		{
			SendClientMessage(playerid,  COLOR_GREY, "  Вы не можете установить место возраждения находясь в паркинге !");
			return 1;
		}
		if( gInAdventure[playerid] != 0 )
		{
			SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете установить место возраждения во время квеста !");
			return 1;
		}
		if(gLoading[playerid] || gUnLoading[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Подождите окончания загрузки/выгрузки !");
			return 1;
		}
		if(CP[playerid] != 0)
		{
		   	SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить место возраждения при выполнении задания !");
		   	return 1;
		}
		new family = PlayerInfo[playerid][pMember];
		for(new t=0; t<MAX_TURFS; t++)//для зон банд 132 MAX_TURFS
		{
            if(!IsPointInRegion(fX, fY, fZ, t) || gPlayerSpawned[playerid] == 0) continue;
			if(TurfInfo[t][zFamily] != PlayerInfo[playerid][pMember])
			{	//если игрок находится не в своей зоне
				SendClientMessage(playerid, COLOR_GREY, "   Вы Не можете установить место возраждения в чужой зоне !");
			    return 1;
		    }
			if(TurfInfo[t][zFlash] == 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы Не можете установить место возраждения, т.к. зона атакована !");
				return 1;
		    }
		    FamilyInfo[family][fLocal] = FREEROAM;
		    FamilyInfo[family][fInterior] = 0;
		    FamilyInfo[family][fWorld] = 0;

			FamilyInfo[family][fSpawns][0] = fX;
			FamilyInfo[family][fSpawns][1] = fY;
			FamilyInfo[family][fSpawns][2] = fZ;
			checkcheat[playerid] = CHEATLIM;
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы отредактировали место появления вашей Банды !");

			/*for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(i == playerid) continue;
				if(spectateid[i] != MAX_PLAYERS-1) continue;
				if(	IsPlayerInRangeOfPlayer(150.0, playerid, i) && IsACop(i) && gOnDuty[i]) return 1;
				//SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы перемещены !");
	       	    //break;
	   		}*/
			//SetCameraBehindPlayer(playerid);
			//SetPlayerPosFindZ(playerid, fX, fY, fZ+10.0);
		}
		return 1;
	}
    PlayerInfo[playerid][pLocal] = FREEROAM;
    SetPlayerInteriorEx(playerid, 0);
    SetPlayerVirtualWorldEx(playerid, 0);

	CurPos[0][playerid] = fX;
	CurPos[1][playerid] = fY;
	CurPos[2][playerid] = fZ;
	checkcheat[playerid] = CHEATLIM;

	//SetPlayerFacingAngle(playerid, ang);
	SetCameraBehindPlayer(playerid);
	//OnePlayAnim(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 1000);//1273
    //SetPlayerPosEx(playerid, fX, fY, fZ);
	SetPlayerPosFindZ(playerid, fX, fY, fZ+10.0);
	return 1;
}
