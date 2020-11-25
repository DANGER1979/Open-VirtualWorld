//для проверки ограничения должно быть в vw_sql.inc

stock ServerInfo(playerid)
{
	new bigmsgitem[1522+47+14];//46+56+70+78 + 69+3+3+2+2 + 59+3+3+3 + 61+3+3+3 + 56+3 + 37+3+3 + 43+3+4 + 55+3+4 + 49+4+3 + 41+3+3 + 41+3 + 34+3+3 + 43+4+4 + 46+4+4 + 85+50+49+84+77+42+45 + 21*2 + 75+47 = 1522
	new strcmd[MAX_STRING];

	format(strcmd, sizeof(strcmd), "\nINFO: %d домов, %d бизнесов, 2 семьи, %d банд, %d гонок", MAX_HOUSE, MAX_BIZ+MAX_SBIZ, TEAM_MAFIA, countrace );
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nPlayersMax = %d, HighestPlayerID = %d, Load Players = %d", GetMaxPlayers(), HighestPlayerID, numplayers);//, StreamedVehicle = %d , vid
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nMAX_VEHICLES = %d, VehiclesMaxLoad = %d, Load Vehicles = %d", MAX_VEHICLES, GetMaxVehicles, VehiclesCounter);//, StreamedVehicle = %d , vid
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nVehicleModelsMax = Unlimited, Load VehicleModels = %d", VehiclesModelsCounter);
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nStreamVehCount = %d PublicCar = %d", StreamVehCount[playerid], index12);
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	format(strcmd, sizeof(strcmd), "\nObjectsMax = %d, MAX_STREAM_OBJECTS = %d",
		MAX_OBJECTS, MAX_STREAM_OBJECTS);//+MAX_ROADBLOCK+MAX_SPIKESTRIPS
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	format(strcmd, sizeof(strcmd), "\nLoadObject = %d  LoadPlayerObject = %d RemoveBuilding = %d",
		CreateObjectCounter, CreatePlayerObjectCounter[playerid], RemoveBuildingCounter[playerid]);//+MAX_ROADBLOCK+MAX_SPIKESTRIPS
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	format(strcmd, sizeof(strcmd), "\nMAX_PICKUPS = %d, Load = %d", MAX_PICKUPS, PickupCounter);//для проверки ограничения
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nMAX_3DTEXT_GLOBAL = %d, Load = %d", MAX_3DTEXT_GLOBAL, Counter3DText);//для проверки ограничения
    strins(bigmsgitem, strcmd, strlen(bigmsgitem));

    //new numobject = CreateObject(971, 0.0,0.0,0.0, 0.0,0.0,0.0); DestroyObject(numobject);
    //new numplobject = CreatePlayerObject(playerid, 971, 0.0,0.0,0.0, 0.0,0.0,0.0); DestroyObject(numobject);//тоже самое
    //new numPickup = CreatePickup(1242, 23, 0.0, 0.0, 0.0, -1); DestroyPickup(numPickup);
    //new Text3D: num3DText = Create3DTextLabel("UNLOAD", 0x00000000, 0.0,0.0,0.0, 0.0, 0, 0); Delete3DTextLabel(num3DText);
	//format(strcmd, sizeof(strcmd), "\nSTREAM: ShowObject: %d, ShowPickup: %d", numobject, numPickup);//, Show3DText: %d , num3DText);
	
	format(strcmd, sizeof(strcmd), "\nSTREAM: DynamicObjects: %d, DynamicPickups: %d DynamicLabels: %d", CountDynamicObjects(), CountDynamicPickups(), CountDynamic3DTextLabels());//, Show3DText: %d , num3DText);
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	//format(strcmd, sizeof(strcmd), "\nMax visible objects: %d", Streamer_GetVisibleItems(STREAMER_TYPE_OBJECT, -1));
	//strins(bigmsgitem, strcmd, strlen(bigmsgitem));
    
	format(strcmd, sizeof(strcmd), "\nMAX_GANG_ZONES = %d, Load = %d", MAX_GANG_ZONES, MAX_TURFS);
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nMAX_ICONS = 100, MAX_STREAM_ICONS = %d, Load = %d + house:%d", MAX_STREAM_ICONS, nMapIcon[playerid], nHouseIcon[playerid]);
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nMAX_MENUS = %d, Load = %d", MAX_MENUS, MenuCounter);//MAX_MENU
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	format(strcmd, sizeof(strcmd), "\nMAX_TEXT_DRAWS = %d, Load = %d + player: %d",MAX_TEXT_DRAWS, TEXT_DRAWS_COUNTER, PLAYER_TEXT_DRAWS_COUNTER[playerid]);//для проверки ограничения
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	//format(strcmd, sizeof(strcmd), "\nstarttimer = %d, 1secTimer = %d, 1secTimer2 = %d, 1secTimer3 = %d, 1secTimer4 = %d",starttimer, onesecondtimers, onesecondtimers2, onesecondtimers3, onesecondtimers4);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	//format(strcmd, sizeof(strcmd), "\n1minTimer = %d, 5minTimer = %d, 15minTimer = %d", oneminutstimer, fiveminutstimers, fifteenminutstimers);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	//format(strcmd, sizeof(strcmd), "\ncarupgradetimer = %d, loadcarupgradetimer = %d",carupgradetimer, loadcarupgradetimer);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	//format(strcmd, sizeof(strcmd), "\nfixradiotimer = %d, stopmusictimer = %d, playerblind = %d", fixradiotimer[playerid], stopmusictimer[playerid], playerblind[playerid]);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	//format(strcmd, sizeof(strcmd), "\nPDgateCloseLStimer = %d, PDbarrierCloseSFtimer = %d DoDgateCloseTimer = %d",PDgateCloseLStimer, PDbarrierCloseSFtimer, DoDgateCloseTimer);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	//format(strcmd, sizeof(strcmd), "\ngCountdowntimer = %d, endracetimer = %d, ElevatorBoostTimer = %d",gCountdowntimer, endracetimer, ElevatorBoostTimer);//gReminder = %d, gReminder,
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	//format(strcmd, sizeof(strcmd), "\ngCountdownCSTimer = %d, updatecstimer = %d, offsettimer = %d",gCountdownCSTimer, gUpdatecstimer, offsettimer);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));
 	//format(strcmd, sizeof(strcmd), " \nLICbarriertimer = %d, LICbarriertimer1 = %d",LICbarriertimer, LICbarriertimer1);
    //strins(bigmsgitem, strcmd, strlen(bigmsgitem));

	//format(strcmd, sizeof(strcmd), "\ngCountdownDerbyTimer = %d, updatederbytimer = %d",gCountdownDerbyTimer, updatederbytimer);
    //strcat(bigmsgitem, strcmd);

    //strins(bigmsgitem, "\nINFO: Правила сервера и информация вызываются по командам /rules и /help", strlen(bigmsgitem));
	if(strlen(bigmsgitem) >= sizeof(bigmsgitem) || strlen(bigmsgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strcmd, sizeof(strcmd), "Error: info %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strcmd);
		return 1;
	}
    new caption[17+64];
    format(caption, sizeof(caption), "INFO: сервера %s", SERVERNAME);
	ShowPlayerDialogEx(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "OK", "Назад");
	//ShowPlayerDialogEx(playerid, BACKPLMENU_DIALOG, DIALOG_STYLE_MSGBOX, "INFO: MOD Virtual World разработал Danger_Hidden(DANGER1979)", bigmsgitem, "OK", "Назад");
	return 1;
}

stock TabInfo(playerid)
{
	new bigmsgitem[(15+2+24+3)*50];
	new strcmd[MAX_STRING];
	new plcounter;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];

		if( !IsPlayerConnectedEx(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
		if( !gPlayerLogged[i] ) continue;
		if( !gPlayerSpawned[i] ) continue;
		if( !gAnticheat[i] ) continue;
		if(plcounter > 50) continue;
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n%d: %s[%d]", bigmsgitem,
			j, PlayerName(i), i);
		plcounter ++;
	}
	if(strlen(bigmsgitem) >= sizeof(bigmsgitem) || strlen(bigmsgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strcmd, sizeof(strcmd), "Error: TabInfo %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strcmd);
	}
	else ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "TabInfo", bigmsgitem, "OK", "");
}


stock FinanceInfo(playerid, forplayerid)
{
	new msgitem[41*5+1+128+24+128+24];
	format(msgitem, sizeof(msgitem), "%s{0080FF}На руках:\t{FFFFFF}%d\n", msgitem, PlayerInfo[forplayerid][pCash]);
	format(msgitem, sizeof(msgitem), "%s{0080FF}В Банке:\t{FFFFFF}%d\n", msgitem, PlayerInfo[forplayerid][pBank]);
	format(msgitem, sizeof(msgitem), "%s{0080FF}На Депозите:\t\t{FFFFFF}%d\n", msgitem, PlayerInfo[forplayerid][pDeposit]);
	//format(msgitem, sizeof(msgitem), "%s{0080FF}Вложено в Дом:\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pAccusing]);
	//format(msgitem, sizeof(msgitem), "%s{0080FF}Вложено в Бизнес:\t\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pBplayer]);
	//format(msgitem, sizeof(msgitem), "%s{0080FF}Вложено в Компанию:\t\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pBplayer]);
	//format(msgitem, sizeof(msgitem), "%s_____________________________________________________________________\n\0", strings);
	new caption[37+24+3];
	format(caption, sizeof(caption), "Finance Data Computer: {FFFFFF}%s[%d]", PlayerName(forplayerid), forplayerid);
	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, msgitem, "OK", "");
}



