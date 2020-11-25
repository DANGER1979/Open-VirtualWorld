//оформить как тут  https://pawno-info.ru/showthread.php?t=267265

//для античита   SetPVarInt(playerid, "LastState", 0);

new CheckInCar[MAX_PLAYERS];
new TeleportDetected[MAX_PLAYERS];
new CheatFloodDetected[MAX_PLAYERS];
new gVoteKicked = MAX_PLAYERS-1;

new DetectedGun[MAX_PLAYERS][MAX_WEAPONS+1];

new checkcheat[MAX_PLAYERS];
new telepSpeed[MAX_PLAYERS];

new C_BUG_TIME = 1;
new CBugCount[MAX_PLAYERS];

new BugTickCountOld[MAX_PLAYERS], BugTickCountNew[MAX_PLAYERS];

//для анимаций
new PlayerNowAnimCount[MAX_PLAYERS];
new PlayerLastAnimation[MAX_PLAYERS];
new animOld[MAX_PLAYERS][32];
//для облегчения нагрузки на сервер
new ReasonPunishment[MAX_PLAYERS][32+32];

new DetectedHealth[MAX_PLAYERS];//флаг разрешённого пополнения здоровья

//#define DecreaseVehHP(%1) if (vhp > %1) SetVehicleHealth(vehicleid, vhp - %1)

new DetectedGiveDamage[MAX_PLAYERS];
new WaitGodModDetected[MAX_PLAYERS];

new Float:WorldBoundsPos[MAX_PLAYERS][4];//gWorldBounds[MAX_PLAYERS];

new UnFreezeFloodCounter[MAX_PLAYERS];//UnFreezeDetected[MAX_PLAYERS];
new TeleportFloodCounter[MAX_PLAYERS];//TeleportDetected[MAX_PLAYERS];

//##############################################################################//
//                                                                              //
//                                 для АНТИЧИТа                                 //
//                                                                              //
//##############################################################################//
new DetectedGunCounter[MAX_PLAYERS];//индикатор и счётчик проверки легального оружия



//##############################################################################//
//                                                                              //
//                               Переменные LAST                               //
//                                                                              //
//##############################################################################//

new ArmourKickCount[MAX_PLAYERS];
//new LastMessagesSent[MAX_PLAYERS];
//new gVehicleDeath[MAX_VEHICLES+1];



new HealthKickCount[MAX_PLAYERS];//!!!не переводить на PVar



new EjectCounter[MAX_PLAYERS], InCarFloodCounter[MAX_PLAYERS];




//antireconnect
new LastIP[MAX_PLAYERS][16], LastTime[MAX_PLAYERS];

//##############################################################################//
//                                                                              //
//                               ФУНКЦИИ ПРОВЕРКИ                               //
//                                                                              //
//##############################################################################//
//начинаются на Is Check


stock anticheat_OnPlayerConnect(playerid)
{

//для античита начало
	TeleportDetected[playerid] = 0;
	CheatFloodDetected[playerid] = 0;
	if(gVoteKicked == playerid) gVoteKicked = MAX_PLAYERS-1;
	
	gAnticheat[playerid] = 0;
	checktimedeliver[playerid] = 0;
	IsKicked[playerid] = 0; IsBaned[playerid] = 0;
	DetectedGiveDamage[playerid] = 0;
	WaitGodModDetected[playerid] = 0;
	CheckInCar[playerid] = -1; //SetPVarInt(playerid, "CheckInCar", -1);
    checkcheat[playerid] = CHEATLIM+1; CurInt[playerid] = 0; telepSpeed[playerid] = 0;
	LastState[playerid] = 0; //CurState[playerid] = 0;
	LastKey[playerid] = 0;
    IsPlayerControllable[playerid] = 0;
	//CurPos[0][playerid] = 0.0;  CurPos[1][playerid] = 0.0;	CurPos[2][playerid] = 999.9;
	TeleportFloodCounter[playerid] = 0;
	UnFreezeFloodCounter[playerid] = 0;
	EjectCounter[playerid] = 0;
	InCarFloodCounter[playerid] = 0;
	
	LastHealth[playerid] = 100.0, HealthKickCount[playerid] = 0;
	LastVehHealth[playerid] = 1000.0;
	DetectedHealth[playerid] = 1;

	LastArmour[playerid] = 0.0, ArmourKickCount[playerid] = 0,	DetectedArmour[playerid] = 0;

	WorldBoundsPos[playerid][0] = 0.0; WorldBoundsPos[playerid][1] = 0.0; WorldBoundsPos[playerid][2] = 0.0; WorldBoundsPos[playerid][3] = 0.0;

	PlayerNowAnimCount[playerid] = CHEATLIM+3; PlayerLastAnimation[playerid] = 0;
	PlayerIsAtRespray[playerid] = 0;
	LastMoney[playerid] = 0;
	LastDamagedid[playerid] = MAX_PLAYERS-1;
	LastIssuerid[playerid] = MAX_PLAYERS-1;
	LastWeapon[playerid] = 0;
	LastStateWeapon[playerid] = 0;
	iLastScrollWeapon[playerid] = 0;
	DetectedGunCounter[playerid] = 0;
	CBugCount[playerid] = 0;
	
	BugTickCountOld[playerid] = 0;
	BugTickCountNew[playerid] = 0;
	LastKill[playerid] = MAX_PLAYERS-1;
	
	gConsumingMoney[playerid] = 0;//если игрок получил деньги
	gCheckArmedWeapon[playerid] = 0;
	
 	SavePos[playerid][LastX] = 0.0; SavePos[playerid][LastY] = 0.0; SavePos[playerid][LastZ] = 0.0;
	TeleportDest[playerid][tX] = 0; TeleportDest[playerid][tY] = 0; TeleportDest[playerid][tZ] = 0;//для gotomark
	TeleportDest[playerid][Int] = 0; TeleportDest[playerid][Virt] = 0; TeleportDest[playerid][Loc] = 255;//для gotomark

//для античита конец

}

stock anticheat_OnVehicleMod(playerid, vehicleid, componentid, interiorid)
{
	#pragma unused vehicleid
	if(componentid < 1000 || componentid > 1193)
	{
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: wrong componentid %d", PlayerName(playerid),playerid, componentid);
		SendClientMessage(playerid, COLOR_RED, strings);
		Log(CHEAT, strings);
		IsKicked[playerid] = 1;
		return 1;
	}
	//new interiorid = GetPlayerInterior(playerid);
	//ComponentArray[componentid-1000][compPart] == Spoiler &&
	new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	if(	Current != mTuningMenu && Current != mColors &&
		Current != mNitro && Current != mWheels &&
		Current != mHydraulics && Current != mSpoiler &&
		Current != mFrontBumper && Current != mRearBumper &&
		Current != mSideskirt && Current != mRoof &&
		Current != mExhaust && Current != mNeon &&
		//Current != mBullbarsFront && Current != mBullbarsRear &&
		//Current != mHood &&	Current != mVents &&
		//Current != mLamps &&
		interiorid != 1 && interiorid != 2 && interiorid != 3)
	{
		//new strings[MAX_STRING];

    	new reason[] = "Car Upgrade";
		format(strings, sizeof(strings), "CEPBEP: %s[%d] забанен на "#BANTIME" дня, причина: %s",
			PlayerName(playerid), playerid, reason);
		//Log(BAN,strings);
		SendClientMessageToAll(COLOR_RED, strings);
		if(PlayerInfo[playerid][pAdmin] < 8)
		{
			PlayerInfo[playerid][pWarns] = getdate() + BANTIME;
			BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);
			PlayerInfo[playerid][pLevel] = -999;
			IsKicked[playerid] = 1;
		}

		/*format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: inadmissible importance componentid %d", PlayerName(playerid),playerid, componentid);
		SendClientMessage(playerid, COLOR_RED, strings);
		if(PlayerInfo[playerid][pAdmin] != 9) //Kick(playerid);*/
		return 1;
	}
	return 0;
}


stock anticheat_OnVehiclePaintjob(playerid, vehicleid, paintjobid, interiorid)
{
	#pragma unused vehicleid
	//покраска 255 - отмена покраски
	if((paintjobid < 0 || paintjobid > 3) && paintjobid != 255)
	{
	//new strings[MAX_STRING];
		format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: wrong paintjobid %d",
			PlayerName(playerid),playerid, paintjobid);
		SendClientMessage(playerid, COLOR_RED, strings);

		Log(CHEAT, strings);
		IsKicked[playerid] = 1;
		return 1;
	}
	//new interiorid = GetPlayerInterior(playerid);//PlayerInfo[playerid][pInt]
	new Menu: Current = GetPlayerMenu(playerid);//получить ID меню
	if(	Current != mTuningMenu && Current != mPaintJob &&
		interiorid != 1 && interiorid != 2 && interiorid != 3)
	{
		//new strings[MAX_STRING];
    	new reason[23+2];
		format(reason, sizeof(reason), "carupgrade in int: %d", interiorid);
		format(strings, sizeof(strings), "CEPBEP: %s[%d] забанен на "#BANTIME" дня, причина: %s",
			PlayerName(playerid), playerid, reason);
		//Log(BAN,strings);
		SendClientMessageToAll(COLOR_RED, strings);
		if(PlayerInfo[playerid][pAdmin] != 9)
		{
			PlayerInfo[playerid][pWarns] = getdate() + BANTIME;
			BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);
			PlayerInfo[playerid][pLevel] = -999;
			IsKicked[playerid] = 1;
		}
		/*format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: wrong paintjobid %d", PlayerName(playerid),playerid, paintjobid);
		SendClientMessage(playerid, COLOR_RED, strings);
		if(PlayerInfo[playerid][pAdmin] != 9) //Kick(playerid);*/
		return 1;
	}
	return 0;
}


stock anticheat_OnPlayerUpdate(playerid)
{
	if(ANTICHEAT == 1)
	{
		if( IsACloseWeapon(LastWeapon[playerid]) )
		{
			CrashDetected[playerid] = 117;
			//if(IsBaned[playerid] == 0)
			//{
				//format(ReasonPunishment[playerid], 64, "cheat lock weapon( %s )", WeaponName(LastWeapon[playerid]) );
				//new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d]{FFFF00} был забанен, причина: %s",
				//	lH,lM,lS, PlayerName(playerid),playerid, ReasonPunishment[playerid]);
				//SendClientMessageToAll(COLOR_RED, strings);
			ResetPlayerWeaponsEx(playerid);
				//IsBaned[playerid] = 1;
			OnPlayerUpdate_run = false;
			return 0;//выход из ф-ии
			//}
		}
		//--------------------------------------------------------------
		// No jetpacks allowed
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
		{
			CrashDetected[playerid] = 118;
			//if(IsBaned[playerid] == 0)
			//{
			    /*strmid(ReasonPunishment[playerid], "Used Jetpack", 0, strlen("Used Jetpack"), 64);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d]{FFFF00} был забанен, причина: %s",
					lH,lM,lS, PlayerName(playerid),playerid, ReasonPunishment[playerid]);
				SendClientMessageToAll(COLOR_RED, strings);*/
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				//IsBaned[playerid] = 1;
			OnPlayerUpdate_run = false;
			return 0;//- 0, рассинхронизация игрока: для всех игрок стоит на месте,
				//с момента последнего полученного синхронизированного пакета, для него все по прежнему.
			//}
		}//SPECIAL_ACTION_ENTER_VEHICLE //SPECIAL_ACTION_EXIT_VEHICLE //SPECIAL_ACTION_DUCK
		//--------------------------------------------------------------
	}
	return 1;
}

stock anticheat_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) &&
			newstate != PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)//если ID нового состояния равно состоянию 1( на ногах)
	{   //выполняется после выхода из машины И ВО ВСЕХ СЛУЧАЯХ
		//----------------------------------------------------------------------
		//проверяем есть ли рядом тачка
		if( !gAnticheat[playerid] && ANTITELEPORT)
		{//если это не телепорт к стадиону ЛС
	   		new Float:x1,Float:y1,Float:z1; GetPlayerPos(playerid, x1,y1,z1);
	   		new Float:x2,Float:y2,Float:z2; GetVehiclePos(nCarID[playerid],x2,y2,z2);//должны постоянно считываться

			new Float: distance = GetVehicleDistanceFromPoint(nCarID[playerid], x1,y1,z1);
	    	new speed = GetVehicleSpeed(nCarID[playerid]);//мгновенная скорость
			new anim_id = PlayerLastAnimation[playerid];//GetPlayerAnimationIndex(playerid);

			new carid;
			new vid = 1;
			new Float:vX,Float:vY,Float:vZ;
			for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
				if(StreamedVehicle[playerid][v] == -1) continue;
				vid = StreamedVehicle[playerid][v];

				if(vid <= 0) continue;
				if(!IsValidVehicle(vid)) continue;//if(nCarModel[playerid] < 400) continue;
				GetVehicleModelInfo(nCarModel[playerid], VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
				if(GetDistanceToCar(playerid, vid) >= (6.0+vY)) continue;//20 - расстояние от пассажирского сидения до центра ТС
				carid = vid;
				break;
			}
			if(	carid == 0 && speed < 97 &&	nCarModel[playerid] != 570 &&
				x1 != 0.0 && y1 != 0.0 && x2 != 0.0 && y2 != 0.0 &&
				!IsPlayerInRangeOfPoint(playerid, 7.5, 2728.0933,-1834.9763,10.3494)
			  )
//PlayerLastAnimation[playerid] != 1129 || PlayerLastAnimation[playerid] != 1134 || PlayerLastAnimation[playerid] != 1156 || PlayerLastAnimation[playerid] != 1189 //если игрок не выпрыгивает из самалёта
			{//если вышли из машины а её рядом нету, и при этом скорость той машины меньше 97,
			//т.к. если скорость больше, то секундный таймер не успеет
	    		new reason[78 + 3+3+7+4*65+3+3+4+2];//123
				format(reason, sizeof(reason), "teleport stream car:%d[%d] %.1f(%.1f,%.1f[%.1f,%.1f]) speed:%d[%d] anim:%d state:%d",
					 nCarID[playerid],nCarModel[playerid],
					 distance, x1,y1, x2,y2,
					 speed, telepSpeed[playerid], anim_id, LastState[playerid]);//PlayerLastAnimation[playerid]
				new strtmp[34 + 24+3 + 123];
				format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s", PlayerName(playerid),playerid, reason);
				Log(CHEAT, strtmp);
				SendAllAdminMessage(COLOR_MAROON, strtmp, 3);

				TeleportDetected[playerid] += 1;
				PlayerInfo[playerid][pInt] = CurInt[playerid];
				PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
				PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
				PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
				SendClientMessage(playerid, COLOR_RED,  "CEPBEP: Подозрение на использование телепортов (Kicked)!");
				if(PlayerInfo[playerid][pAdmin] != 9) {
					IsKicked[playerid] = 1;
				}
				return 1;
			}
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT)//если ID нового состояния равно состоянию на ногах
	{   //если ID нового состояния равно состоянию 1

		//----------------------------------------------------------------------
//для античита начало
		CheckInCar[playerid] = -1;
		SetPVarInt(playerid, "gIdleKick", 0);//опустили флаг - игрок вышел из тачки бота

		LastVehHealth[playerid] = 1000.0;
		EjectCounter[playerid] = 0;
//для античита конец
	}
	else if(newstate == PLAYER_STATE_DRIVER) //buggy dont finnish  //если ID нового состояния равно состоянию за рулём
	{	//если ID нового состояния равно состоянию 2
//для античита начало
	    if(CheckInCar[playerid] == 0)
	    {//если игрок нажал F при посадке в машину
			CheckInCar[playerid] = 2;
		}
		LastVehHealth[playerid] = 1000.0;
//для античита конец
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{   //если ID нового состояния равно состоянию 3 - пассажир
//для античита начало
	    if(CheckInCar[playerid] == 1)
	    {//если игрок нажал F при посадке в машину
			CheckInCar[playerid] = 2;
		}
	}
	return 1;
}

stock anticheat_EnterCheckpoint(playerid)
{
	if(GetTickCount() < (TimeSetCheckpoint[playerid]+MinTimeCheckpoint[playerid]) && MinTimeCheckpoint[playerid] != 0 && !gAnticheat[playerid])
	{
   		new reason[64];
		format(reason, sizeof(reason), "teleport checkpoint %d. Time: %d[minimum %d] sec",
			CP[playerid], (GetTickCount()-TimeSetCheckpoint[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
		new strtmp[23 + 24+3+64];
		format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s", PlayerName(playerid),playerid, reason);
		Log(JOB, strtmp);
		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
        //DisablePlayerCheckpointEx(playerid);
	    //return 1;
	}
}


stock antiflood_OnPlayerSelectedMenu(playerid, Menu:Current)
{
	if(ANTIFLOOD == 1 && PlayerInfo[playerid][pAdmin] != 9)//для антифлуда начало ANTIFLOOD=0;
	{
		//if(GetTickCount() - iPlayerMenuTime[playerid] < 1000)
		if((GetTickCount()-GetPVarInt(playerid, "MenuTime")) < 1000)
		{
			//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
            ShowMenuForPlayerEx(Current, playerid);
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}Вы можете использовать меню только раз в секунду.");
		    return 1;
		}
		//iPlayerMenuTime[playerid] = GetTickCount();
		SetPVarInt(playerid, "MenuTime", GetTickCount());
    }//флуд конец
	SetPVarInt(playerid, "ShowMenu", 0);//при выборе опускаем флаг, т.к. менюшка может сразу скрыться,
//если она снова появится, то флаг поднимется.
    return 0;
}

stock check_OnPlayerConnect(playerid)
{//проверка на дубликаты ip на серве
	if( gRealWar) return 1;

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];

		////if( !strcmp(PlayerInfo[playerid][pIP], "178.124.35.222", true) ) break;
		////if( !strcmp(PlayerInfo[playerid][pIP], "178.124.102.181", true) ) break;
		////if( !strcmp(PlayerInfo[playerid][pIP], "192.168.100.100", true) ) break;

		if( strfind(PlayerInfo[playerid][pIP], "93.125.49.", true) != -1 ) break;//93.125.49.235 - UNET.BY
		if( strfind(PlayerInfo[playerid][pIP], "91.149.162.", true) != -1 ) break;//91.149.162.250 - Гарант
		if( strfind(PlayerInfo[playerid][pIP], "86.57.252.", true) != -1 ) break;
		if( strfind(PlayerInfo[playerid][pIP], "87.252.227.", true) != -1 ) break;
		if( strfind(PlayerInfo[playerid][pIP], "178.125.64.", true) != -1 ) break;
		//----------------------------------------------------------------------
		if( strlen(PlayerInfo[i][pIP]) < 6) continue;//пропускаем пустые ip
		if( strcmp(PlayerInfo[playerid][pIP], PlayerInfo[i][pIP], true) ) continue;
		if( !IsPlayerConnectedEx(i) ) continue;
		if( strlen(PlayerName(playerid)) < 6) continue;
		//находим наше совпадение

		//format(strings, sizeof(strings), "CEPBEP: %s[%s] был кикнут, причина: DoubleIP %s", PlayerName(playerid), PlayerInfo[playerid][pIP], PlayerName(i));
		format(strings, sizeof(strings), "AdmWarning: %s[%d] зашёл под IP %s'а[%d]", PlayerName(playerid), playerid, PlayerName(i), i);
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		format(strings, sizeof(strings), "[%d:%02d:%02d] %s", lH,lM,lS, strings);
		SendAllAdminMessage(COLOR_MAROON, strings, 7);

    	//format(strings, sizeof(strings), "%s[%d] doubleIP:%s(%s)", PlayerName(playerid), playerid, PlayerInfo[playerid][pIP], PlayerName(i));
 		//Log(KICK, strings);

		//SendSystemMessage(COLOR_DARKBLUE,strings,1);
		////Kick(playerid);
		//IsKicked[playerid] = 1;
		break;
	}
	return 1;
}
//antireconnect
stock AntiDisconnect(playerid)
{//вызывается из OnPlayerDisconnect
	//Anti Quick Reconnect III - Stepashka
    for(new i=0, curtime=gettime(); i<sizeof(LastIP); i++)
    {   //пробегаемся по массиву где храняться IP адреса
        if(curtime - LastTime[i] >= ReconnectDelay)
        {   //если встречаем запись у которой время больше 5 секунд обнуляем значения адреса и времени
            LastIP[i] = ""; LastTime[i] = 0;
        }
        if( strlen(LastIP[i]) )
        {   //если находим НЕ нулевую строку пропускаем её, в случае если предыдущая проверка обнулила строку запись произведётся в неё
		 	continue;
		}
        //GetPlayerIp(playerid, LastIP[i], 16);//при дисконекте игрока ип всегда будет 255,255,255,255 при reason == 1
        strmid(LastIP[i], PlayerInfo[playerid][pIP], 0, strlen(PlayerInfo[playerid][pIP]), 16);
        LastTime[i] = gettime();//записываем время выхода
		//The number of seconds since midnight, 1 January 1970
        break;//обрываем дальнейшую проверку
    }
}
//antireconnect
stock AntiReconnect(playerid)
{//вызывается из OnPlayerInit
	for(new i=0, curtime=gettime(); i<sizeof(LastIP); i++)
	{
		if(!strlen(LastIP[i])) break;//пропускаем пустые ip
		if(!strcmp(PlayerName(playerid), CREATOR, false) ) continue;
		if( strcmp(PlayerInfo[playerid][pIP], LastIP[i], false) ) continue;
		//находим наше совпадение
		if((curtime-LastTime[i]) < ReconnectDelay && !IsPlayerAdmin(playerid) )
		{	//если прошло время меньше чем задано, то кикать
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: reconnect < %d сек", PlayerName(playerid),playerid, ReconnectDelay);
//Log(KICK, strings);
			new lH, lM, lS; gettime(lH,lM,lS); //FixHour(lH);
			format(strings, sizeof(strings), "[%d:%02d:%02d] %s", lH,lM,lS, strings);
			SendClientMessage(playerid, COLOR_RED, strings);

			//IsKicked[playerid] = 1; break;
			return 0;
		}
		else
		{   //иначе по этому ip произвести очистку
			LastIP[i] = "";	LastTime[i] = 0;
			break;
		}
	}
	return 1;
}


//##############################################################################//
//                                                                              //
//                                   АНТИЧИТ                                    //
//                                                                              //
//##############################################################################//

stock AntiCrasher(playerid, newstate)
{
    //if( CurState[playerid] != PLAYER_STATE_NONE )
    if (newstate == PLAYER_STATE_ONFOOT)
    {
	    new Float:x,Float:y,Float:z;
	    GetPlayerCameraFrontVector(playerid,x,y,z);
	    //if( !((-1.0 <= x <= 1.0) && (-1.0 <= y <= 1.0) && (-1.0 <= z <= 1.0)) )
		if(floatcmp(1.0, floatabs(x))==-1 || floatcmp(1.0, floatabs(y))==-1 || floatcmp(1.0, floatabs(z))==-1)
	    {
	        if(IsKicked[playerid])
	        {
				if(IsBaned[playerid] == 0)
				{
					IsKicked[playerid] = 0;
					strmid(ReasonPunishment[playerid], "OnFoot Crasher", 0, strlen("OnFoot Crasher"), 64);
					new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
					format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d]{FFFF00} был забанен, причина: %s",
						lH,lM,lS, PlayerName(playerid),playerid, ReasonPunishment[playerid]);
					SendClientMessageToAll(COLOR_RED, strings);

					//format(strings, sizeof(strings), "%s[%d] baned, CameraFrontVector: x:%0.1f, y:%0.1f, z:%0.1f", PlayerName(playerid),playerid, x,y,z);
					//SendSystemMessage(COLOR_MAROON, strings, 1);
					//Log(BAN,strings);
					IsBaned[playerid] = 1;
				}
	        }
	        else
	        {
	            IsKicked[playerid] = 1;//ложный вызов из-за старых данных.
	        }
	    }
    }
}


stock AntiCarJacked(playerid, vehicleid, ispassenger)
{
	if( IsInNPCVehicle(vehicleid) ) return 1;
	if(vehicleid <= 0) return 1;
	//new modelid = GetVehicleModel(vehicleid);
	if( ispassenger == 0 )
	{   //если я сажусь на водительское сидение
		if(	GetVehicleSpeed(vehicleid) > 10 &&
			GetSeatVehiclePlayer(vehicleid, 0) != INVALID_PLAYER_ID)
		{
			ClearAnimations(playerid, 1);
  			return 1;
	    }
		if( GetSeatVehiclePlayer(vehicleid, 0) != INVALID_PLAYER_ID)
		{   //если водительское место занято кем-то
			/*for(new seat=1; seat<=VehicleArray[modelid-400][SeatID]-1; seat++)//500 в автобусах
			{   //сканируем пассажирские места
			    if( GetSeatVehiclePlayer(vehicleid, seat) == INVALID_PLAYER_ID )
			    {   //находим свободные места
		    		if( CarStatus[vehicleid][st_doors] == VEHICLE_PARAMS_OFF)
		    		{   //если тачка открыта
						PutPlayerInVehicleEx(playerid, vehicleid, seat);
	    			}
	    			return 1;
			    }
			    //jacker = GetSeatVehiclePlayer(vehicleid, 0);
		    }*/
			//removePlayerFromVehicle(playerid);
		    ClearAnimations(playerid);
		}
	}
	return 1;
}


stock AntiFakeKill_OnPlayerDeath(playerid, killerid, reason)
{//выызвается из OnPlayerDeath
	//if(playerid == INVALID_PLAYER_ID) return 1;
	//if(killerid == INVALID_PLAYER_ID) return 1;
	if( !IsPlayerConnected(playerid) ) return 1;
	//if( !IsPlayerConnected(killerid) ) return 1;
	if( IsPlayerNPC(playerid) ) return 1;
	//if( IsPlayerNPC(killerid) ) return 1;

	//для античита
	//new strings[MAX_STRING];
	/*new Float:PposX, Float:PposY, Float:PposZ;
	new Float:KposX, Float:KposY, Float:KposZ;
	GetPlayerPos(playerid, PposX, PposY, PposZ);
	GetPlayerPos(killerid, KposX, KposY, KposZ);
	new Float: tmpdis = floatsqroot(
		floatpower(floatsub(KposX,PposX),2)+
		floatpower(floatsub(KposY,PposY),2)+
		floatpower(floatsub(KposZ,PposZ),2));*/
	if(ANTICHEAT == 1)
	{
		new Float: tmpdis = GetDistanceBetweenPlayers(playerid, killerid);
		if(AFK_IdleTime[killerid] > 3)
		{
			format(strings, sizeof(strings), "CEPBEP: %s[%d](AFK) killerid FakeKill %s[%d](cheater)",
					PlayerName(killerid), killerid, PlayerName(playerid), playerid);
			SendAllAdminMessage(COLOR_RED, strings, 3);
			//SendClientMessageToAll(COLOR_RED, strings);

			if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid])
			{
				Log(CHEAT, strings);//чтобы не сильно грузить лог
				IsKicked[playerid] = 1;
				playerid = INVALID_PLAYER_ID;
			}
			return 1;
		}
		if( reason < 22 && tmpdis > 10.0)// && !IsPlayerInAnyVehicle(killerid)
		{
			format(strings, sizeof(strings), "CEPBEP: %s[%d] убил ближним оружием на растоянии > 10 %s[%d](cheater)",
					PlayerName(killerid), killerid, PlayerName(playerid), playerid);
			SendAllAdminMessage(COLOR_RED, strings, 3);
			//SendClientMessageToAll(COLOR_RED, strings);
			//Log(CHEAT, strings);

		    /*SetPVarString(killerid, "Reason", "FakeKill");
		    SetPVarInt(killerid, "PlayerID", playerid);
		    SetPVarString(killerid, "playername", PlayerName(playerid));

			mPunish = CreateMenuEx(PlayerName(playerid),1,10.0,120.0,100.0,0.0);
		    AddMenuItem(mPunish, 0, "Nothing");
		    AddMenuItem(mPunish, 0, "Warn");
			ShowMenuForPlayerEx(mPunish, killerid);*/

			if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid])
			{
				Log(CHEAT, strings);
				IsKicked[playerid] = 1;
				Kick(playerid);
				playerid = INVALID_PLAYER_ID;
			}
			return 1;
		}
		if(GetDistanceBetweenPlayers(killerid, playerid) > 255.0)
		{
			//OnPlayerPunishment(killerid, reason);
			format(strings, sizeof(strings), "CEPBEP: %s[%d] killerid Distance %.0fm FakeKill %s[%d](cheater)",
					PlayerName(killerid), killerid, GetDistanceBetweenPlayers(killerid, playerid),
					PlayerName(playerid), playerid);
			SendAllAdminMessage(COLOR_RED, strings, 3);
			//SendClientMessageToAll(COLOR_RED, strings);
			//Log(CHEAT, strings);
			if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid])
			{
				Log(CHEAT, strings);
				IsKicked[playerid] = 1;
				Kick(playerid);
				playerid = INVALID_PLAYER_ID;
			}
			return 1;
		}
		if( LastWeapon[killerid] != -1 &&
			LastWeapon[killerid] != reason &&//если убийца не имеет в руках это оружие
			reason < 49 &&
			//reason != 51 &&//Взорвался/Rhino
			GetPlayerState(killerid) != PLAYER_STATE_DRIVER)
		{
			format(strings, sizeof(strings), "CEPBEP: %s[%d](Weapon:%d[%d]) killerid FakeKill %s[%d](cheater)",
					PlayerName(killerid), killerid, LastWeapon[killerid], reason, PlayerName(playerid), playerid);
			SendAllAdminMessage(COLOR_RED, strings, 3);
			//SendClientMessageToAll(COLOR_RED, strings);
			//Log(CHEAT, strings);

		    /*SetPVarString(killerid, "Reason", "FakeKill");
		    SetPVarInt(killerid, "PlayerID", playerid);
		    SetPVarString(killerid, "playername", PlayerName(playerid));

			mPunish = CreateMenuEx(PlayerName(playerid),1,10.0,120.0,100.0,0.0);
		    AddMenuItem(mPunish, 0, "Nothing");
		    AddMenuItem(mPunish, 0, "Warn");
			ShowMenuForPlayerEx(mPunish, killerid);*/

			if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid])
			{
				Log(CHEAT, strings);
				IsKicked[playerid] = 1;
				playerid = INVALID_PLAYER_ID;
			}
			return 1;
		}
		if(LastIssuerid[playerid] != killerid)
		{//в конце, т.к. может LastIssuerid не проинициализироваться из-за глючности ф-ии OnPlayerTakeDamage
			format(strings, sizeof(strings), "CEPBEP: %s[%d](WrongLastKiller) killerid FakeKill %s[%d](cheater)",
					PlayerName(killerid), killerid, PlayerName(playerid), playerid);
			SendAllAdminMessage(COLOR_RED, strings, 3);
			//SendClientMessageToAll(COLOR_RED, strings);
			//Log(CHEAT, strings);

		    /*SetPVarString(killerid, "Reason", "FakeKill");
		    SetPVarInt(killerid, "PlayerID", playerid);
		    SetPVarString(killerid, "playername", PlayerName(playerid));

			mPunish = CreateMenuEx(PlayerName(playerid),1,10.0,120.0,100.0,0.0);
		    AddMenuItem(mPunish, 0, "Nothing");
		    AddMenuItem(mPunish, 0, "Warn");
			ShowMenuForPlayerEx(mPunish, killerid);*/

			if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid])
			{
				Log(CHEAT, strings);
				IsKicked[playerid] = 1;
				playerid = INVALID_PLAYER_ID;
			}
			return 1;
		}
	}
	//======================================================================
	//if(PlayerInfo[playerid][pSTD] >= 1 && PlayerInfo[playerid][pSTD] <= 10) return 1;
	AntiDM_OnPlayerDeath(playerid, killerid, reason);
	return 1;
}

//stock OnPlayerAutoInJail(playerid, giveplayerid)//, time
stock OnPlayerArrestKill(playerid, giveplayerid)//, time
{   //ARREST KILL
//НАЗНАЧЕНИЕ: чтобы игроки не использовали смерть в целях спасения от оппонента
	/*if(PlayerInfo[playerid][pLevel] < 0) {
		SendClientMessageToAll(COLOR_YELLOW, "   На сервер зашёл игрок с нулевым уровнем !");
		//return 1;
	}*/
	if(PlayerInfo[giveplayerid][pLevel] <= 3) return 1;
	if(WantedLevel[giveplayerid] == 0) return 1;

	//new strings[MAX_STRING];
	new title[64], commentary[128];
	if( IsPlayerInArea(giveplayerid, specialzone[5]) )//15 база Hitman
	{
		//SendClientMessage(playerid, COLOR_GREY, "   Вы не можете парализовать на этой территории !");
	    return 1;
	}
	new strtmp[44+3+1];
	if(PlayerInfo[giveplayerid][pArticle] >= 1 && PlayerInfo[giveplayerid][pArticle] <= 36)
	{   //pdd
		for(new i=0; i<sizeof(PDD); i++)
		{
			if(PlayerInfo[giveplayerid][pArticle] != PDD[i][Article]) continue;
			if(PlayerInfo[giveplayerid][pPart] != PDD[i][Part]) continue;
			//new PDDticket = PDD[i][Bail]*PlayerInfo[giveplayerid][pLevel]*360;//3600

			//new PDDperiod = PDD[i][Period]*(PlayerInfo[giveplayerid][pLevel]+1);//*4
			new PDDperiod = 1+PDD[i][Period];
			if(PDD[i][Jailed] == 3 || PDD[i][Jailed] == 4)
			{
				if(PlayerInfo[giveplayerid][pCarLic] == 1) PlayerInfo[giveplayerid][pCarLic] = PDDperiod+10;
			}
			//LevelToCriminality --;//ClearCrime снижает уровень преступности
			PlayerInfo[giveplayerid][pJailed] = 1;//Садим в ЛС
			PlayerInfo[giveplayerid][pJailTime] = WantedLevel[giveplayerid]*5;//6*5=30
			//PlayerInfo[giveplayerid][pJailPrice] = PDDticket;//установили залог, в случаи отказа он обнулится

			strmid(title, PDD[i][Title], 0, strlen(PDD[i][Title]), 64);
			format(strings, sizeof(strings), " Bы убиты при задержании по Cтатье %d.%d: %s !", PlayerInfo[giveplayerid][pArticle], PlayerInfo[giveplayerid][pPart], title);
			SendClientMessage(giveplayerid, COLOR_RED, strings);
			strmid(commentary, PDD[i][Commentary], 0, strlen(PDD[i][Commentary]), 128);
			format(strings, sizeof(strings), " %s", commentary);
			SendClientMessage(giveplayerid, COLOR_RED, strings);

			format(strtmp, sizeof(strtmp), "Убит при задержании по статье %d.%d",
				PlayerInfo[giveplayerid][pArticle], PlayerInfo[giveplayerid][pPart]);//Статья

			format(strings, sizeof(strings), "* Вы убили подозреваемого %s'а. Уровень Преступности был %d.", PlayerName(giveplayerid), LevelToCriminality);//3600
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			CriminalList(giveplayerid, PlayerName(playerid), strtmp, 2);//0 - ничего, 1 - преступление, 2 - арест, 3 - перевод
			break;
		}
	}
	else if(PlayerInfo[giveplayerid][pArticle] >= 139)
	{   //pun
		for(new i=0; i<sizeof(PenalCode); i++)
		{
			if(PlayerInfo[giveplayerid][pArticle] != PenalCode[i][Article]) continue;
			if(PlayerInfo[giveplayerid][pPart] != PenalCode[i][Part]) continue;

			//new PUNticket = PenalCode[i][Bail]*PlayerInfo[giveplayerid][pLevel]*360;//3600
			new PUNticket = PenalCode[i][Bail]*WantedLevel[giveplayerid]*ticket_rate;//3600
			PlayerInfo[giveplayerid][pJailPrice] = PUNticket;//установили залог, в случаи отказа он обнулится

			//LevelToCriminality --;//ClearCrime снижает уровень преступности
			if(PenalCode[i][Jailed] == 10)
			{
				PlayerInfo[giveplayerid][pJailed] = 10;//Садим на зону
				PlayerInfo[giveplayerid][pJailTime] = DOTL[ PenalCode[i][Period] ][0] * 60;//минут
				//PlayerInfo[giveplayerid][pJailed] = 2;//Садим в ЛС
				//PlayerInfo[giveplayerid][pJailTime] = 2*WantedLevel[giveplayerid]*5;//6*5=30

				PlayerInfo[giveplayerid][pJailPrice] = PUNticket;
				if(PlayerInfo[giveplayerid][pSex] == Male) PlayerInfo[giveplayerid][pChar] = 62;//скин зэка
				if(PlayerInfo[giveplayerid][pGunLic] == 1) PlayerInfo[giveplayerid][pGunLic] = DOTL[ PenalCode[i][Period] ][0]+10;

				format(strtmp, sizeof(strtmp), "Убит при переводе по статье %d.%d",
					PlayerInfo[giveplayerid][pArticle], PlayerInfo[giveplayerid][pPart]);//Статья
				CriminalList(giveplayerid, PlayerName(playerid), strtmp, 3);//0 - ничего, 1 - преступление, 2 - арест, 3 - перевод
			}
			else
			{
				LevelToDeliver ++;
				PlayerInfo[giveplayerid][pJailed] = 2;//Садим в СФ
				PlayerInfo[giveplayerid][pJailTime] = WantedLevel[playerid]*5;//3600;

				format(strtmp, sizeof(strtmp), "Убит при при задержании по статье %d.%d",
					PlayerInfo[giveplayerid][pArticle], PlayerInfo[giveplayerid][pPart]);//Статья
				CriminalList(giveplayerid, PlayerName(playerid), strtmp, 2);//0 - ничего, 1 - преступление, 2 - арест, 3 - перевод
			}
			strmid(title, PenalCode[i][Title], 0, strlen(PenalCode[i][Title]), 64);
			format(strings, sizeof(strings), " Bы убиты при задержании по Cтатье %d.%d: %s !", PlayerInfo[giveplayerid][pArticle], PlayerInfo[giveplayerid][pPart], title);
			SendClientMessage(giveplayerid, COLOR_RED, strings);
			strmid(commentary, PenalCode[i][Commentary], 0, strlen(PenalCode[i][Commentary]), 128);
			format(strings, sizeof(strings), " %s", commentary);
			SendClientMessage(giveplayerid, COLOR_RED, strings);

			format(strings, sizeof(strings), "* Вы убили подозреваемого %s'а. Уровень Преступности был %d.", PlayerName(giveplayerid), LevelToCriminality);//3600
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

			break;
		}
	}

	gOnDuty[giveplayerid] = 0;
	//gJobDuty[giveplayerid] = 0;
	FixJobCounter(giveplayerid);
	ResetPlayerWeaponsEx(giveplayerid);//забрали оружие
	PlayerInfo[giveplayerid][pDrugs] = 0;//Наркотики
	PlayerInfo[giveplayerid][pFuel] = 0;//Канистра с топливом.
	PlayerInfo[giveplayerid][pArrested] += 1;//добавили к общему кол-во арестов 1
	//PlayerInfo[giveplayerid][pJailTime] = time;// * 60;
	//ClearCrime(giveplayerid, playerid);//не очищаем розыск, чтобы по уровню розыска расчитать залог
	PlayerCuffed[giveplayerid] = MAX_PLAYERS-1;
	PlayerCuffedTime[giveplayerid] = 0;

	if(IsPlayerAttachedObjectSlotUsed(giveplayerid, CUFF_SLOT)) RemovePlayerAttachedObject(giveplayerid, CUFF_SLOT);
	SetPlayerSpecialAction(giveplayerid, SPECIAL_ACTION_NONE);

	PlayerTied[giveplayerid] = 0;
	PlayerTiedTime[giveplayerid] = 0;
	TogglePlayerControllableEx(giveplayerid, 1);//оcвободили игрока
	SetPlayerToTeamColor(8);

	if(PlayerInfo[giveplayerid][pJailed] == 10)
	{
		format(strings, sizeof(strings), "Bас посадили на зону на %d минут. Залог: %d$. Все ваши вещи конфискованы.",
			PlayerInfo[giveplayerid][pJailTime], PlayerInfo[giveplayerid][pJailPrice]);
	}
	else if(PlayerInfo[giveplayerid][pJailed] == 1)
	{
		format(strings, sizeof(strings), "Bас посадили в КПЗ Лос-Сантоса на %d минут. Залог: %d$. Все ваши вещи конфискованы.",
			PlayerInfo[giveplayerid][pJailTime], PlayerInfo[giveplayerid][pJailPrice]);
	}
	else if(PlayerInfo[giveplayerid][pJailed] == 2)
	{
		format(strings, sizeof(strings), "Bас посадили в КПЗ Сан-Фиерро на %d минут. Залог: %d$. Все ваши вещи конфискованы.",
			PlayerInfo[giveplayerid][pJailTime], PlayerInfo[giveplayerid][pJailPrice]);
	}
	SendClientMessage(giveplayerid, COLOR_BROWN, strings);

	if(PlayerInfo[playerid][pMember] == DoT)
	{
		format(strings, sizeof(strings), "убил розыскиваемого %s'а !", PlayerName(giveplayerid));
		//JobNews(COLOR_BLUEGREY, strings);
		//SendClientMessage(giveplayerid, COLOR_BLUEGREY, strings);
		SendDepartmentMessage(playerid, strings);
	}
	else if(PlayerInfo[playerid][pMember] == FBI)
	{
		format(strings, sizeof(strings), "убил розыскиваемого %s'а !", PlayerName(giveplayerid));
		//JobNews(COLOR_BLUEGREY, strings);
		//SendClientMessage(giveplayerid, COLOR_BLUEGREY, strings);
		SendDepartmentMessage(playerid, strings);
	}
	return 1;
}


stock AntiDB_OnPlayerStateChange(playerid, newstate, oldstate)
{   //вызывается из OnPlayerStateChange
	#pragma unused oldstate

	if(AntiDB == 0) return 1;
	//new newstate = CurState[playerid];
	//ЗАПРЕТ НА ПОСАДКУ С ДИГЛОМ и др., т.к. с этих пушек большая скорость стрельбы
	if(newstate == PLAYER_STATE_PASSENGER && IsPlayerControllable[playerid] == 0 )
	{//если был не замарожен
		switch(LastWeapon[playerid])
		{
	    	case 24:
	    	{
	       		//SendClientMessage(playerid, 0x33AA33AA, "С Пустынным орлом запрещено садиться на пассажирское место.");
	        	//RemovePlayerFromVehicleEx(playerid);
	        	SetPlayerArmedWeaponEx(playerid, 0);
  	    	}
	    	case 26:
	    	{
	       		//SendClientMessage(playerid, 0x33AA33AA, "С Обрезом запрещено садиться на пассажирское место.");
	        	//RemovePlayerFromVehicleEx(playerid);
	        	SetPlayerArmedWeaponEx(playerid, 0);
  	    	}
	  		case 27:
	  		{
   				//SendClientMessage(playerid, 0x33AA33AA, "С Боевым дробовиком запрещено садиться на пассажирское место.");
	        	//RemovePlayerFromVehicleEx(playerid);
	        	SetPlayerArmedWeaponEx(playerid, 0);
	  		}
		}
	}
	else if( newstate == PLAYER_STATE_DRIVER )// && IsFireArm(GetPlayerWeapon(playerid))
	{
		SetPlayerArmedWeaponEx(playerid, 0);
	}
	return 1;
}

new Float: RotationY[MAX_VEHICLES+1];
stock AntiSpeedHackTimer(playerid)
{
//добавить античит на проверку езду с выключеным двигателм
//сделать проверку на предыдущую скорость
//если скорость увеличивается, двигатель выключен, то чит

	if(ANTISPEEDHACK != 1) return 1;
 	if(gAnticheat[playerid] == 1) return 1;//!strcmp(php_host, "gta.strikearena.ru", true)
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(!IsPlayerInAnyVehicle(playerid)) return 1;
	if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;

	//new Float:X,Float:Y,Float:Z;
	//GetVehiclePos(vehicleid, X, Y, Z);
	//GetVehicleZAngle(nCarID[playerid], angle);
	new maxspeed = 380;//максимальная разрешённая скорость
	new Float:rotX,Float:rotZ;//Float:rotY,
	//GetVehicleRotation(nCarID[playerid], rotX, RotationY[nCarID[playerid]], rotZ);
	if(nCarID[playerid] && RotationY[nCarID[playerid]] > -1.2)//-1.3 //-2.0//тангаж
	{
		maxspeed = VehicleArray[nCarModel[playerid]-400][LineSpeed];//150;//если в тачке на месте водилы то максимальная скорость
	}
	else if(nCarID[playerid] && RotationY[nCarID[playerid]] <= -1.2)//
	{
		maxspeed = VehicleArray[nCarModel[playerid]-400][MaxSpeed];//150;//если в тачке на месте водилы то максимальная скорость
	}

	new value = GetVehicleSpeedXY(nCarID[playerid]);
	new SENSITIVITY = 2;
	if( value > (maxspeed + SENSITIVITY) && !gAnticheat[playerid])
	{
		CrashDetected[playerid] = 64;

	    new reason[42 + 32+3+6+6];
		format(reason, sizeof(reason), "SpeedHack %s[%d] - %d[%d](Тангаж: %.1f)",
			VehicleArray[nCarModel[playerid]-400][Vehicle_Name], nCarModel[playerid],
			value, maxspeed, RotationY[nCarID[playerid]]);

		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AdmWarning: %s[%d]. %s",
			PlayerName(playerid), playerid,	reason);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 3);

		TogglePlayerControllableEx(playerid, 0);//обездвиживает когда не в машине
		PlayerTazed[playerid] = 1;
		PlayerTazeTime[playerid] = 30;

		format(strings, sizeof(strings), "* %s Парализован на %d секунд, reason: %s", PlayerName(playerid), PlayerTazeTime[playerid], reason);
		ProxDetector(playerid, 30.0,  strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

		GameTextForPlayerEx(playerid, "~r~Tazed", 2500, 3);
	}
	GetVehicleRotation(nCarID[playerid], rotX, RotationY[nCarID[playerid]], rotZ);
	return 1;
}

stock UnFreezeTimer(playerid)//запускается каждые 2 секунды
{
 	if(UNFREEZE != 1) return 1;
 	if(gAnticheat[playerid] == 1) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//--------------------------------------------------------------------------
	if(CurState[playerid] == PLAYER_STATE_PASSENGER)
	{
       	return 1;
	}
	if(!IsPlayerInAnyVehicle(playerid) && GetPlayerSurfingVehicleID(playerid) != INVALID_VEHICLE_ID )
	{   //если вы на тачке
		return 1;
	}
	//--------------------------------------------------------------------------
	new FreezeSpeed = 0; new minspeed = 380;//максимальная разрешённая скорость
	//--------------------------------------------------------------------------
	if(CheatFloodDetected[playerid] > 0)
	{
		CrashDetected[playerid] = 73;
		UnFreezeFloodCounter[playerid] ++;//флудилка
	    if(UnFreezeFloodCounter[playerid] >= CHEATLIM+2)//проверка 8 секунд
		{
			UnFreezeFloodCounter[playerid] = 0;//закончили проверку
        	//FreezeSpeed = 0;
			CheatFloodDetected[playerid] = 0;
	        if(GetPVarInt(playerid, "UnFreezeDetected") >= CHEATLIM)
	        {   //если чит зафиксирован 5 раз за 8 секунд
	        	SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на UnFreeze (Kicked)");
			    new reason[] = "UnFreeze";
			    //new strings[MAX_STRING];
				//format(strings, sizeof(strings), "CEPBEP: %s[%d] was banned for "#BANTIME" days, reason: %s",
				format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: %s",
					PlayerName(playerid), playerid, reason);
				//Log(KICK,strings);
				//SendClientMessageToAll(COLOR_MAROON, strings);
				Log(CHEAT, strings);
	    		SendAllAdminMessage(COLOR_MAROON, strings, 3);

				if(PlayerInfo[playerid][pAdmin] < 8)
				{
					SetPVarInt(playerid, "UnFreezeDetected", 0);

					//PlayerInfo[playerid][pLevel] = -999;
					//PlayerInfo[playerid][pWarns] = getdate() + BANTIME;//Получает текущий день в году + бан на 30 дней
					//BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);

					IsKicked[playerid] = 1;
					return 1;
				}
			}
			SetPVarInt(playerid, "UnFreezeDetected", 0);
		}
	}
	//--------------------------------------------------------------------------
	if(CurState[playerid] == PLAYER_STATE_DRIVER)
	{   //если вы в тачке
		FreezeSpeed = GetVehicleSpeedXY(nCarID[playerid]);
       	minspeed = 25;//25 минимальная скорость
	}
	else if(!IsPlayerInAnyVehicle(playerid) && GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID)//You are not surfing.
	{	//если вы пешком и не на крыше
		FreezeSpeed = GetPlayerSpeedXY(playerid);
       	if(GetPlayerSkin(playerid) == 99) minspeed = 7;//7 минимальная скорость
       	else minspeed = 7;//7 минимальная скорость
	}
	if(FreezeSpeed > 0 && FreezeSpeed > minspeed &&
		IsPlayerControllable[playerid] == 1 && GetPVarInt(playerid, "gWorldBounds") <= 0)
	{
		new strtmp[MAX_STRING];
		format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. Подозрение на UnFreeze (speed:%d[%d])", PlayerName(playerid), playerid, FreezeSpeed, minspeed);
   		//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strtmp, 3);
   		ABroadCast(COLOR_MAROON, strtmp, 3);

		CheatFloodDetected[playerid] = 1;
		GivePVarInt(playerid, "UnFreezeDetected", +1);
	}
	else
	{
 		SetPVarInt(playerid, "gWorldBounds", GetPVarInt(playerid, "gWorldBounds")-1);
	}
	return 1;
}
stock WorldBoundsTimer(playerid)
{//вызывается из OneSecondTimers3
	if(ANTICHEAT == 0) return 1;
 	if(gAnticheat[playerid] == 1) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//if(PlayerInfo[playerid][pAdmin] == 9) return 1;
	if(	GetPVarInt(playerid, "gWorldBounds") &&
		!IsPlayerInAreaEx(playerid,
			WorldBoundsPos[playerid][1], WorldBoundsPos[playerid][0],
			WorldBoundsPos[playerid][3], WorldBoundsPos[playerid][2])
		)
	{
		CrashDetected[playerid] = 74;
		if(IsKicked[playerid] == 0)
		{
			strmid(ReasonPunishment[playerid], "NOP SetPlayerWorldBounds", 0, strlen("NOP SetPlayerWorldBounds"), 64);
        	new strtmp[34 + 24+3 +64];
			format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
				PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			Log(CHEAT, strtmp);
    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
    		SetPVarInt(playerid, "gWorldBounds", 0);
			IsKicked[playerid] = 1;
			//return 1;//0 отключает синхронизацию игрока с сервером
		}
	}
	return 1;
}


//##############################################################################//
//                                                                              //
//                   ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ для работы античита                  //
//                                                                              //
//##############################################################################//


stock AntiCheatMoney(playerid)//вызывается каждую секунду
{
	if(ANTIMONEY != 1) return 1;
 	if(gAnticheat[playerid] == 1) return 1;
    new money = GetPlayerMoney(playerid);
    if(	(money-LastMoney[playerid]) >= 500
		&& gConsumingMoney[playerid] <= 0)
    {   //если проверка закончена
		SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на moneycheat (Kicked)");

   		new reason[16+10];
		//format(reason, sizeof(reason), "moneycheat: $%d", money-GetPVarInt(playerid, "LastMoney") );
		format(reason, sizeof(reason), "moneycheat: $%d", money-LastMoney[playerid] );
   		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AdmWarning: %s[%d] kicked, reason: %s",
			PlayerName(playerid), playerid, reason);

		//SendClientMessageToAll(COLOR_RED, strings);
		Log(CHEAT, strings);
    	SendAllAdminMessage(COLOR_MAROON, strings, 3);

		if(PlayerInfo[playerid][pAdmin] < 8)
		{
			IsKicked[playerid] = 1;
			return 1;
		}
    }
	if(gConsumingMoney[playerid] > 0)
	{
		CrashDetected[playerid] = 65;
		gConsumingMoney[playerid] --;
		//SetPVarInt(playerid, "LastMoney", money);
		LastMoney[playerid] = money;
	}
	return 1;
}
//т.е. если сесть в авто и аирбегом воспользоваться то не кикнет при выходе из тачки?
stock AntiTeleportTimer(playerid)// 19.06.2011
{
	if(GameRestart == 1) return 1;
	if(spectateid[playerid] != MAX_PLAYERS-1) return 1;

	new timers = GetTickCount();

	//if( GetPVarInt(playerid, "gStatusRegistration") ) return 1;
	//if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount")) return 1;
    new speed;
	new interiorid = GetPlayerInterior(playerid);
    new Float: distance, Float:x,Float:y,Float:z;
    new curstate = CurState[playerid];

	if(curstate == PLAYER_STATE_ONFOOT)
   	{
	    GetPlayerPos(playerid, x,y,z);
		//distance = GetPlayerDistanceFromPoint(playerid, CurPos[0][playerid],CurPos[1][playerid],CurPos[2][playerid]);
		distance = floatsqroot( floatpower(floatsub(x,CurPos[0][playerid]),2) +
				 				floatpower(floatsub(y,CurPos[1][playerid]),2) );
		//new value = floatround(distance/1000*3600);//скорость = расстояние / время(час)
		//предыдущая скорость
		if(	GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID &&
			PlayerCuffed[playerid] == MAX_PLAYERS-1 &&
			PlayerTied[playerid] == 0 &&
			FollowBy[playerid] == MAX_PLAYERS-1 &&
			GameRestart != 1)
		{//если не на крыше и не в куфе и не под конвоем и небыло команды на рестарт
    		//CrashDetected[playerid] = 76;
	   		speed = GetPlayerSpeedXY(playerid);//GetPlayerSpeed(playerid);////мгновенная скорость
			new anim_id = PlayerLastAnimation[playerid];//GetPlayerAnimationIndex(playerid);
			/*if(CHECKING == 1)
			{
				//ИНФОРМИРОВАНИЕ
	    		new reason[67+3+7+33+10+10+4+2];
				format(reason, sizeof(reason), "airbag onfoot: %.1fm(Z:%.1f) speed:%d[%d] anim:%d[%d] state:%d[%d]",
					 distance, z,
					 speed, telepSpeed[playerid],
					 anim_id, PlayerLastAnimation[playerid], curstate, LastState[playerid]);
				new strtmp[23+24+3 + 73+3+7+33+10+10+4+2];
				format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
					PlayerName(playerid),playerid, reason);
				SendAllAdminMessage(COLOR_RED, strtmp, 6);
			}*/
			if(checkcheat[playerid] <= 0)
			{   //LastWeapon[playerid] != 46 &&

				if(	ANTITELEPORT == 1 && GetPlayerPing(playerid) < PINGS && IsPlayerControllable[playerid] == 0 &&
		    		x != 0.0 && CurPos[0][playerid] != 0.0 &&	y != 0.0 && CurPos[1][playerid] != 0.0)
		    	{
					if(	distance > 4.2 && //distance > 4.2 &&//distance < 27.0 &&
		     		 	(anim_id == 1186 || anim_id == 1189 || anim_id == 1275 || anim_id == 1456) &&
 //если анимация стоящего мужика или женщины или роллера
//или любая другая зациклинная анимация  || anim_id == 46 - rap
						speed < 1 && telepSpeed[playerid] < 1 &&//если изменение скорости закончено и GetPlayerSpeed равна 0
						z == CurPos[2][playerid])//при аэрбеге координата Z у игрока постоянна
					{
							CrashDetected[playerid] = 761;
				    		new reason[81+7+33+10+10+4+2];
							format(reason, sizeof(reason), "airbag onfoot: %.1f(%.1f[%.1f],%.1f[%.1f]) speed:%d[%d] anim:%d[%d] state:%d[%d]",
								 distance, x,CurPos[0][playerid], y,CurPos[1][playerid],
								 speed, telepSpeed[playerid], anim_id, PlayerLastAnimation[playerid], curstate, LastState[playerid]);

							new strtmp[23+24+3 + 66+7+33+10+10+4+2];
							format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
								PlayerName(playerid), playerid, reason);
							//Log(CHEAT, strtmp);
							SendAllAdminMessage(COLOR_RED, strtmp, 3);

							TeleportFloodCounter[playerid] ++;
							if(TeleportFloodCounter[playerid] >= CHEATLIM-1 && SynchronizerSaved != 1)
							{
								TeleportFloodCounter[playerid] = 0;
								TeleportDetected[playerid] += 1;//для пометки, чтобы сохранить при кике по предыдущим координатам

								PlayerInfo[playerid][pInt] = CurInt[playerid];
								PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
								PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
								PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
								SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на airbag (Kicked).");
								if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid])
								{
									IsKicked[playerid] = 1;
								}
/*new str[26+24];
strcat(str, "OnPlayerAntiTeleport1.1 ");
strcat(str, PlayerName(playerid));
TestLog(OPTIM, str, GetTickCount(), timers);*/
								return 1;
							}
		    		}
		    		if(	distance >= 44.0 && //63.0 при выходе из вагона //28.5 максимальная скорость бега с горки роллера или сиджея
            			!(LastState[playerid] == PLAYER_STATE_DRIVER) && //упал с мото //!(IsInMotorcycle(LastCar[playerid]) || IsInBike(LastCar[playerid])) &&  && (anim_id == 1203 || anim_id == 1155)
						!((PlayerLastAnimation[playerid] == 1132 || PlayerLastAnimation[playerid] == 1133) && LastState[playerid] == PLAYER_STATE_PASSENGER) &&//выход из поезда
						anim_id != 971 && anim_id != 963 && anim_id != 965 && anim_id != 978 && anim_id != 976)//анимации при открытом парашуте
		    		{ 	//если координата Z у игрока НЕ постоянна, значит был обычный телепорт
						CrashDetected[playerid] = 762;
						if(	anim_id != 1273	)//WALK_WUZI
						{   //если перемещение произошло, но анимация не равна установленной для легальных тп
				    		new reason[83+7+33+10+10+4+2];
							format(reason, sizeof(reason), "teleport onfoot: %.1fm speed:%d[%d] anim:%d[%d] state:%d[%d] int:%d[%d] LastCar:%d",//(%.1f[%.1f],%.1f[%.1f],%.1f[%.1f])
								 distance,
								 //x,CurPos[0][playerid], y,CurPos[1][playerid], z,CurPos[2][playerid],
								 speed, telepSpeed[playerid],
								 anim_id, PlayerLastAnimation[playerid],
								 curstate, LastState[playerid],
								 interiorid, CurInt[playerid],
								 LastCar[playerid]);

							new strtmp[23+24+3 + 68+7+33+10+10+4+2];
							format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
								PlayerName(playerid),playerid, reason);
							//Log(CHEAT, strtmp);
							SendAllAdminMessage(COLOR_RED, strtmp, 3);

							TeleportFloodCounter[playerid] ++;
							if(TeleportFloodCounter[playerid] >= CHEATLIM-1 && SynchronizerSaved != 1)
							{
								TeleportFloodCounter[playerid] = 0;
								TeleportDetected[playerid] += 1;

								PlayerInfo[playerid][pInt] = CurInt[playerid];
								PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
								PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
								PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
								SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на использование телепортов (Kicked)!!");
								if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid]) {
									IsKicked[playerid] = 1;
								}
/*new str[26+24];
strcat(str, "OnPlayerAntiTeleport1.2 ");
strcat(str, PlayerName(playerid));
TestLog(OPTIM, str, GetTickCount(), timers);*/
								return 1;
							}
						}
		    		}
		    	}
	    	}
			else checkcheat[playerid] --;
		}
		else
		{
			/*if(distance > 4.0 && PlayerInfo[playerid][pAccount] == 0)
			{
				CrashDetected[playerid] = 763;
				new modelid = VehInfo[GetPlayerSurfingVehicleID(playerid)][cModel];//GetVehicleModel(GetPlayerSurfingVehicleID(playerid));
			 	if(	VehicleArray[modelid-400][Category] == Rail_Transport ||
					VehicleArray[modelid-400][Category] == Airplane ||
					VehicleArray[modelid-400][Category] == Boats) { }
				else
				{
					//format(strings, sizeof(strings), "   Запрещена езда на крыше!", Ammo);
					//SendClientMessage(playerid, COLOR_GREY, "   Запрещена езда на крыше!");
					SetPlayerPos(playerid, x,y,z+5.0);
				}
			}*/
		}
	}
//==============================================================================
	else if( IsPlayerInAnyVehicle(playerid) && !IsTunTeleport(playerid))
	{   //когда игрок выходит, то он ещё считается в машине
		//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку
		nCarID[playerid] = GetPlayerVehicleID(playerid);
		//в момент выхода  GetPlayerVehicleID(playerid); возвращает ноль и соответственно координаты 0.0
	    GetVehiclePos(nCarID[playerid],x,y,z);//должны постоянно считываться
    	//CrashDetected[playerid] = 77;
		//distance = floatsqroot( floatpower(floatsub(x,CurPos[0][playerid]),2)
		//			 + floatpower(floatsub(y,CurPos[1][playerid]),2) );
		distance = GetVehicleDistanceFromPoint(nCarID[playerid], CurPos[0][playerid], CurPos[1][playerid], CurPos[2][playerid]);
		//new value = floatround(distance/1000*3600);//скорость = расстояние / время(час)
		//предыдущая скорость
    	speed = GetVehicleSpeed(nCarID[playerid]);//мгновенная скорость
		//new Float:maxDist = VehicleArray[nCarModel[playerid]-400][Speed]/2+35;
		new anim_id = PlayerLastAnimation[playerid];//GetPlayerAnimationIndex(playerid);

		/*if(CHECKING == 3)
		{
			//ИНФОРМИРОВАНИЕ
    		new reason[84+3+7+33+10+10+4+2];
			format(reason, sizeof(reason), "teleport car:%d distance: %.1f(%.1f[%.1f],%.1f[%.1f]) speed:%d[%d] anim:%d state:%d",
				 nCarModel[playerid], distance, x,CurPos[0][playerid], y,CurPos[1][playerid],
				 speed, telepSpeed[playerid], PlayerLastAnimation[playerid], LastState[playerid]);

			new strtmp[23+24+3 + 73+3+7+33+10+10+4+2];
			format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
				PlayerName(playerid),playerid, reason);
			SendAllAdminMessage(COLOR_RED, strtmp, 6);
		}*/
	    if(checkcheat[playerid] <= 0)
	    {
	        if(	interiorid == 0 && ANTITELEPORT == 1 &&
	         	GetPlayerPing(playerid) < PINGS && anim_id == 0 &&
	    		x != 0.0 && CurPos[0][playerid] != 0.0 &&
	    		y != 0.0 && CurPos[1][playerid] != 0.0 )
			{
				/*if(CHECKING == 3)
				{
					//ИНФОРМИРОВАНИЕ
		    		new reason[73+3+7+33+10+10+4+2];
					format(reason, sizeof(reason), "car:%d distance: %.1f(%.1f[%.1f],%.1f[%.1f]) speed:%d[%d] anim:%d state:%d",
						 nCarModel[playerid], distance, x,CurPos[0][playerid], y,CurPos[1][playerid],
						 speed, telepSpeed[playerid], PlayerLastAnimation[playerid], LastState[playerid]);

					new strtmp[23+24+3 + 73+3+7+33+10+10+4+2];
					format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
						PlayerName(playerid),playerid, reason);
					SendAllAdminMessage(COLOR_RED, strtmp, 6);
				}*/

				if(	//curstate == PLAYER_STATE_DRIVER && //LastState[playerid] == PLAYER_STATE_DRIVER &&
					//PlayerCuffed[playerid] == MAX_PLAYERS-1 &&
					//PlayerTied[playerid] == 0 &&
					//FollowBy[playerid] == MAX_PLAYERS-1 &&
					!(curstate == PLAYER_STATE_PASSENGER && IsInNPCVehicle(nCarID[playerid])) &&
					speed < 2 && telepSpeed[playerid] == speed && IsPlayerControllable[playerid] == 0 &&
					//если изменение скорости закончено и GetVehicleSpeed меньше 2, т.к. бывает колеблется
					distance > 7.0 && distance < 94.0 && //CheckInCar[playerid] == 2 &&
					PlayerLastAnimation[playerid] != 226 && //посадка в 431 тачку
					PlayerLastAnimation[playerid] != 354 && //посадка в 437 тачку
					PlayerLastAnimation[playerid] != 1628 //посадка в 532 тачку
				  )
	    		{
	    			CrashDetected[playerid] = 771;

		    		new reason[73+3+7+33+10+10+4+2];
					format(reason, sizeof(reason), "airbag car:%d %.1f(%.1f[%.1f],%.1f[%.1f]) speed:%d[%d] anim:%d state:%d",
						 nCarModel[playerid], distance, x,CurPos[0][playerid], y,CurPos[1][playerid],
						 speed, telepSpeed[playerid], PlayerLastAnimation[playerid], LastState[playerid]);

					new strtmp[23+24+3 + 73+3+7+33+10+10+4+2];
					format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
						PlayerName(playerid),playerid, reason);
					//Log(CHEAT, strtmp);
					SendAllAdminMessage(COLOR_RED, strtmp, 3);

					TeleportFloodCounter[playerid] ++;
					if(TeleportFloodCounter[playerid] >= CHEATLIM-1 && SynchronizerSaved != 1)
					{
						TeleportFloodCounter[playerid] = 0;
						TeleportDetected[playerid] += 1;

						PlayerInfo[playerid][pInt] = CurInt[playerid];
						PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
						PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
						PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
						SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на car airbag (Kicked).");
						if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid]) {
							IsKicked[playerid] = 1;
						}
/*new str[26+24];
strcat(str, "OnPlayerAntiTeleport1.3 ");
strcat(str, PlayerName(playerid));
TestLog(OPTIM, str, GetTickCount(), timers);*/
						return 1;
					}
				}
	   			//------------------------------------------------------------------
	   			if( CarStatus[nCarID[playerid]][st_engine] == VEHICLE_PARAMS_OFF &&
				  	telepSpeed[playerid] < 1 && distance > 7.0 &&
				  	RotationY[nCarID[playerid]] > -1.0 && RotationY[nCarID[playerid]] < 1.0 )
	   			{   //если тачка стояла и вдруг начала перемещаться стоя на горизонтальной поверхности
 					CrashDetected[playerid] = 772;
	   			    //и при этом тангаж около нуля
	   			    //если скорость больше чем предыдущая
		    		new reason[55 + 3+3+3+5];
					format(reason, sizeof(reason), "EngineOFF %s (distance:%.0f, curspeed:%d[%d], Fuel:%.1f)",
						 VehicleArray[nCarModel[playerid]-400][Vehicle_Name],
						 distance,
						 speed, telepSpeed[playerid],
						 VehInfo[nCarID[playerid]][cFuel]);

					new strtmp[23+24+3+69];
					format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
						PlayerName(playerid),playerid, reason);
					//Log(CHEAT, strtmp);
					SendAllAdminMessage(COLOR_RED, strtmp, 3);

					TeleportFloodCounter[playerid] ++;
					if(TeleportFloodCounter[playerid] >= CHEATLIM-1 && SynchronizerSaved != 1)
					{
						TeleportFloodCounter[playerid] = 0;
						TeleportDetected[playerid] += 1;

						PlayerInfo[playerid][pInt] = CurInt[playerid];
						PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
						PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
						PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
						SendClientMessage(playerid, COLOR_RED, "CEPBEP: езда с выключенным двигателем (Kicked)");
						if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid]) {
							IsKicked[playerid] = 1;
						}

/*new str[26+24];
strcat(str, "OnPlayerAntiTeleport1.4 ");
strcat(str, PlayerName(playerid));
TestLog(OPTIM, str, GetTickCount(), timers);*/
						return 1;
					}
	   			}
	   			//------------------------------------------------------------------
	   			/*if(distance > 7.0 &&  )
	   			{   //если водительское место пусто, а машина перемещается

		    		new reason[55 + 3+3+3+5];
					format(reason, sizeof(reason), "car:%d Driver Empty (lastspeed:%d, curspeed:%d Fuel:%.1f)",
						 nCarID[playerid], telepSpeed[playerid], speed, VehInfo[nCarID[playerid]][cFuel]);
	   			}*/
				if( distance > 94.0 && !IsInNPCVehicle(nCarID[playerid]) )//максимальная скорость 91-гидры, 86-рустлера, инфернуса
				{

					CrashDetected[playerid] = 773;
		    		new reason[73+3+7+33+10+10+4+2];
					format(reason, sizeof(reason), "teleport car:%d %.1f(%.1f[%.1f],%.1f[%.1f]) speed:%d[%d] anim:%d state:%d",
						 nCarModel[playerid], distance, x,CurPos[0][playerid], y,CurPos[1][playerid],
						 speed, telepSpeed[playerid], PlayerLastAnimation[playerid], LastState[playerid]);

					new strtmp[23+24+3 + 73+3+7+33+10+10+4+2];
					format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d]. %s",
						PlayerName(playerid),playerid, reason);
					SendAllAdminMessage(COLOR_RED, strtmp, 3);

					//Log(KICK, strings);
					TeleportFloodCounter[playerid] ++;
					if(TeleportFloodCounter[playerid] >= CHEATLIM-1 && SynchronizerSaved != 1)
					{
					    TeleportFloodCounter[playerid] = 0;
						TeleportDetected[playerid] += 1;

						PlayerInfo[playerid][pInt] = CurInt[playerid];
						PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
						PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
						PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
						SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на использование телепортов (Kicked)!!!");
						if(PlayerInfo[playerid][pAdmin] != 9 && !gAnticheat[playerid]) {
							IsKicked[playerid] = 1;
						}

/*new str[26+24];
strcat(str, "OnPlayerAntiTeleport1.5 ");
strcat(str, PlayerName(playerid));
TestLog(OPTIM, str, GetTickCount(), timers);*/
						return 1;
					}
	   			}
			}
		}
	 	else checkcheat[playerid] --;
		//------------------------------------------------------------------
		//счётчик метража
		SystemConsuptionFuel(playerid, curstate, distance);
 	}
    CurPos[0][playerid] = x;
	CurPos[1][playerid] = y ;
	CurPos[2][playerid] = z;
	CurInt[playerid] = interiorid;
	telepSpeed[playerid] = speed;
	//LastState[playerid] = CurState[playerid];

	new str[26+24];
	strcat(str, "AntiTeleportTimer ");
	strcat(str, PlayerName(playerid));
	TestLog(OPTIM, str, GetTickCount(), timers);
	return 1;
}


stock OnPlayerIsAtMachines(playerid, anim_id)
{   //вызывается постоянно из OnPlayerUpdate когда анимация сменилась
	//new anim_id = GetPlayerAnimationIndex(playerid);
	if(anim_id == 1660 || PlayerLastAnimation[playerid] == 1660)
	//if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DRINK_SPRUNK)
	//if(	IsAtCandyMachines(playerid) || IsAtSprunkMachines(playerid) )
	{//если игрок использовал анимации выпивания колы
		PlayerNowAnimCount[playerid] = CHEATLIM;//задержка 2 секунды
		new Float:health; GetPlayerHealth(playerid, health);
		if(	health > LastHealth[playerid]
			&& health <= 100.0)
	    {   //если здоровье увеличилось но меньше 100
			DetectedHealth[playerid] = 1;
			LastHealth[playerid] = health;
	        if(PlayerInfo[playerid][pLevel] > 1)
	        {
				PlayerInfo[playerid][pCash] -= SBizInfo[12][sbEntranceCost];
				PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
				ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
				gConsumingMoney[playerid] = 2;
				GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
				LastMoney[playerid] = PlayerInfo[playerid][pCash];

				//SBizInfo[12][sbTill] += SBizInfo[12][sbEntranceCost];//перечислили деньги в биз Sprunk
				//SBizInfo[12][sbExport] += SBizInfo[12][sbEntranceCost];
				OnGangsExtortionSBiz(12, SBizInfo[12][sbEntranceCost]);
				SBizInfo[12][sbProducts] --;
			}
		}
	}
	return 1;
}

stock AntiRecoveringHealthTimer(playerid)
{   //вызывается из OneSecondTimers3
	if(ANTIHEALTH == 0) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
    new Float:health; GetPlayerHealth(playerid, health);

 	/*if(floatsub(LastHealth[playerid], health) > 2.0)
	{//если произошло изменение здоровья в меньшую сторону
		if(//!IsPlayerWalking(playerid) &&
			health < PlayerInfo[playerid][pSHealth] )
		{
			//SetPlayerWalkingStyle(playerid, WALK_GANGSTA2);
			TogglePlayerWalking(playerid, true);
			//new strtmp[MAX_STRING];
			//format(strtmp, sizeof(strtmp), "Доктор: Вы не можете бегать пока ваше здоровье меньше: %.0f",
			//	floatadd(PlayerInfo[playerid][pSHealth], 50.0) );
			//SendClientMessage(playerid, COLOR_PINK, strtmp);
		}
	}*/

	if(DetectedHealth[playerid] == 1)
	{//если есть разрешение на изм. хп, иначе просто выйдет
        DetectedHealth[playerid] = 0;
        return 1;
    }

    if(//health > LastHealth[playerid] &&
		floatsub(health, LastHealth[playerid]) > 2.0 &&
		PlayerNowAnimCount[playerid] <= 0 && !gAnticheat[playerid])
    {   //если проверка закончена

		CrashDetected[playerid] = 71;
		//ИНФОРМИРОВАНИЕ
		new reason[65 + 3+3+3+4];
		format(reason, sizeof(reason), "CheatHealth: %.0f (Current:%.0f, Last:%.0f) AnimIdx: %d",
			(health-LastHealth[playerid]),
			health,	LastHealth[playerid],
			PlayerLastAnimation[playerid]);

//ВНИМАНИЕ: сервер бывает не успевает считывать новое значение здоровье если SetPlayerHealth и GetPlayerHealth в одном цикле
		new strtmp[38 + 24+3 + 65 + 3+3+3+4];
		format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d] reason: %s",
			PlayerName(playerid),playerid, reason);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strtmp, 3);

		//SetPlayerHealthEx(playerid, LastHealth[playerid]);

		HealthKickCount[playerid] ++;
		if(HealthKickCount[playerid] >= 2*CHEATLIM)
		{
			HealthKickCount[playerid] = 0;
			//format(strings, sizeof(strings), "CEPBEP: %s[%d] was banned for "#BANTIME" days, reason: %s",
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: %s",
				PlayerName(playerid), playerid, reason);
			SendClientMessageToAll(COLOR_RED, strings);

			//PlayerInfo[playerid][pLevel] = -999;
			//PlayerInfo[playerid][pWarns] = getdate() + BANTIME;//Получает текущий день в году + бан на 30 дней
			//BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);
			IsKicked[playerid] = 1;
			return 1;
		}
    }
//задержка
	if(PlayerNowAnimCount[playerid] > 0)
	{//если игрок использовал анимации выпивания колы
		PlayerNowAnimCount[playerid] --;
	}
	if(HEALTH)
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AntiRecoveringHealthTimer(playerid:%d, health:%.1f, LastHealth:%.1f)", playerid, health, LastHealth[playerid]);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	LastHealth[playerid] = health;//всегда в самом конце должна быть
	return 1;
}


stock AntiRecoveringArmourTimer(playerid)
{   //вызывается из OneSecondTimers3
	if(ANTIHEALTH == 0) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
    new Float:Armour; GetPlayerArmour(playerid, Armour);
	if(Armour > 0.0) { gTextDrawShowArmour[playerid] = true; OnPlayerTextDrawStateChange(playerid); }
	if(TextDrawShowArmour[playerid] == true)
	{
		new string[5+3];
		format(string, sizeof(string),"%.0f", Armour);
		PlayerTextDrawSetString(playerid, txdPlayerArmour[playerid], string);
	}
	if(DetectedArmour[playerid] == 1)
	{
        DetectedArmour[playerid] = 0;
        return 1;
    }
    if(	floatsub(Armour, LastArmour[playerid]) > 2.0 && !gAnticheat[playerid])// && PlayerNowAnimCount[playerid] <= 0
    {   //если проверка закончена
		CrashDetected[playerid] = 71;
		//ИНФОРМИРОВАНИЕ
		new reason[68 + 3+3+3+4];
		format(reason, sizeof(reason), "CheatArmour: %.0f (CurrentArmour:%.0f, LastArmour:%.0f) AnimIdx: %d",
			(Armour-LastArmour[playerid]),
			Armour,	LastArmour[playerid],
			PlayerLastAnimation[playerid]);

		new strtmp[38 + 24+3 + 65 + 3+3+3+4];
		format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d] reason: %s",
			PlayerName(playerid),playerid, reason);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strtmp, 3);

		SetPlayerArmourEx(playerid, (LastArmour[playerid]));

		ArmourKickCount[playerid] ++;
		if(ArmourKickCount[playerid] >= 2*CHEATLIM && !gAnticheat[playerid])
		{
			ArmourKickCount[playerid] = 0;
			//format(strings, sizeof(strings), "CEPBEP: %s[%d] was banned for "#BANTIME" days, reason: %s",
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: %s",
				PlayerName(playerid), playerid, reason);
			SendClientMessageToAll(COLOR_RED, strings);

			if(PlayerInfo[playerid][pAdmin] < 8)
			{
				//PlayerInfo[playerid][pLevel] = -999;
				//PlayerInfo[playerid][pWarns] = getdate() + BANTIME;//Получает текущий день в году + бан на 30 дней
				//BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);
				IsKicked[playerid] = 1;
				return 1;
			}
		}
    }
//задержка
	/*if(PlayerNowAnimCount[playerid] > 0)
	{//если игрок использовал анимации выпивания колы
		PlayerNowAnimCount[playerid] --;
	}*/
	if(HEALTH)
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AntiRecoveringArmourTimer(playerid:%d, armour:%.1f, LastArmour:%.1f)", playerid, Armour, LastArmour[playerid]);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	LastArmour[playerid] = Armour;//всегда в самом конце должна быть
	return 1;
}



stock AntiRecovVehHealthTimer(playerid)//вызывается каждую секунду
{
	if(ANTIVEHHEALTH == 0) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(!IsPlayerInAnyVehicle(playerid)) return 1;
	if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
	if(GetPVarInt(playerid, "DetectedVehHealth") == 1)
	{
        SetPVarInt(playerid, "DetectedVehHealth", 0);
        return 1;
    }
    new vehicleid = GetPlayerVehicleID(playerid);
    new Float:health; GetVehicleHealth(vehicleid, health);
    if(health > LastVehHealth[playerid] && PlayerIsAtRespray[playerid] <= 0 && !gAnticheat[playerid])
    {
    	CrashDetected[playerid] = 72;

    	PlayerIsAtRespray[playerid] = 0;
        if(	GetPVarInt(playerid, "gEnterExit") == 0 && //если вышел из тюна
			CurInt[playerid] != 1 && CurInt[playerid] != 3)//если это не тюны
        {
            //ИНФОРМИРОВАНИЕ
			new reason[56 + 3+4+4];
			format(reason, sizeof(reason), "CheatVehHealth: %.0f (Current:%.0f, Last:%.0f)",
				(health-LastVehHealth[playerid]),
				health, LastVehHealth[playerid]);

			new strtmp[38 + 24+3 + 56 + 3+4+4];
			format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d] reason: %s",
				PlayerName(playerid),playerid, reason);
			SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strtmp, 3);

			SetVehicleHealthEx(playerid, vehicleid, LastVehHealth[playerid]);

			HealthKickCount[playerid] ++;
			if(HealthKickCount[playerid] >= 2*CHEATLIM)
			{//при 5 срабатываниях кик
				HealthKickCount[playerid] = 0;
				//format(strings, sizeof(strings), "CEPBEP: %s[%d] was banned for "#BANTIME" days, reason: %s",
				format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: %s",
					PlayerName(playerid), playerid, reason);
				SendClientMessageToAll(COLOR_RED, strings);

				if(PlayerInfo[playerid][pAdmin] < 8)
				{
					//PlayerInfo[playerid][pLevel] = -999;
					//PlayerInfo[playerid][pWarns] = getdate() + BANTIME;//Получает текущий день в году + бан на 30 дней
					//BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);
					IsKicked[playerid] = 1;
					return 1;
				}
			}
		}
    }
	if(PlayerIsAtRespray[playerid] > 0)
	{
		PlayerIsAtRespray[playerid] --;
	}
	LastVehHealth[playerid] = health;
	VehHealth[vehicleid] = health;
	return 1;
}
//для античита патронов начало
stock RemovePlayerWeaponEx(playerid, weaponid)
{   //забирает у игрока указанное оружие
	SetPlayerAmmo(playerid, weaponid, 0);
	DetectedGun[playerid][weaponid] = 1;
	LastWeaponInSlot[playerid][GetWeaponSlot(weaponid)] = 0;
	LastAmmo[playerid][weaponid] = 0;

	/*if(CHECKING[weapon] == 2)
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "RemovePlayerWeaponEx(playerid: %d, weaponid: %d)", playerid, weaponid);
		SendClientMessage(playerid, COLOR_RED, strings);
	}*/
	//ИНФОРМИРОВАНИЕ
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "RemovePlayerWeaponEx(playerid: %d, weaponid: %d)", playerid, weaponid);
	//ABroadCast(ADMINS_MESSAGE_COLOR, strings, 1);
	//SendClientMessageToAll(COLOR_YELLOW, strings);
	//return SetPlayerAmmo(playerid, weaponid, 0);
}





stock AntiRecoveringAmmoTimer(playerid)//вызывается каждую секунду
{
	if(ANTIGUN != 1) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//if(PlayerInfo[playerid][pGunLic] != 1) return 1;
	//если у игрока есть лицензия на оружие
	//if(gAnticheat[playerid] == 1) return 1;
	if(	iLastScrollWeapon[playerid] == LastWeapon[playerid])
	{   //если прокрутка скрола закончена, т.е. текущее оружие равно что и секунду назад
		new dataweapons[13][2];
		for(new sl = 1; sl <= 9; sl++)//1-12  2-6
		{   //проверяем только огнестрельное оружие, и гранаты (8 слот)
		    GetPlayerWeaponData(playerid, sl, dataweapons[sl][0], dataweapons[sl][1]);

			if(GetPlayerAmmo(playerid) >= 32767)
			{//Боеприпасы могут подержать 16-битовые величины, следовательно величины свыше 32767 возвращает ошибочные величины.
				format( ReasonPunishment[playerid], 64, "cheating weapons (%s[%d] CheatAmmo:%d)",
					WeaponName( LastWeapon[playerid] ), LastWeapon[playerid], (dataweapons[sl][1] - LastAmmo[playerid][ dataweapons[sl][0] ]));
				new strtmp[22 + 24+3 + 64];
				format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d] %s", PlayerName(playerid), playerid, ReasonPunishment[playerid]);
				Log(CHEAT,strtmp);
				ResetPlayerWeaponsEx(playerid);
				SetPlayerArmedWeaponEx(playerid, 0);
			}
//ВНИМАНИЕ СЫНОК: !!!
//GetPlayerAmmo(playerid) не работает на пассажирском сидении
//GetPlayerWeaponData и GetPlayerAmmo не замеряют минусовое кол-во патронов
//при отнимании их ф-ией GivePlayerWeapon (при отнимании SetPlayerAmmo минус замеряется)
//и показывает 0 патронов

//при SetPlayerAmmo оружие становится с бесконечными патронами при установки минусового значения
//а на тачке стреляет без перезарядки быстро и бесконечно

			else if(	//LastWeaponInSlot[playerid][slot] == dataweapons[sl][0] &&
				LastWeapon[playerid] == dataweapons[sl][0] && dataweapons[sl][0] != 0 &&
				GetPlayerAmmo(playerid) == dataweapons[sl][1] && dataweapons[sl][1] != 0
			  )
			{   //дополнительная проверка на совпадение двух способов получения оружия
				CrashDetected[playerid] = 66;
		        if( DetectedGun[playerid][ LastWeapon[playerid] ] == 0
					/*&& GetPlayerWeaponState(playerid) == WEAPONSTATE_MORE_BULLETS
					|| GetPlayerWeaponState(playerid) == WEAPONSTATE_LAST_BULLET
					|| GetPlayerWeaponState(playerid) == WEAPONSTATE_UNKNOWN*/)
		        {
					if(	(dataweapons[sl][1] > 0 && dataweapons[sl][1] > LastAmmo[playerid][dataweapons[sl][0]])	||
						(dataweapons[sl][1] < 0 && dataweapons[sl][1] != -(LastAmmo[playerid][dataweapons[sl][0]]))//при временном отборе патронов на минус
					  )
				    {   //если разница между текущим значением патронов и предыдущим увеличилась
				        //или кол-во патронов меньше положенного
						//new strings[MAX_STRING];
						format(strings, sizeof(strings),
							"AdmWarning: %s[%d] Gun:%s[%d] Cheat Ammo:%d (Current:%d, Last:%d)",
							PlayerName(playerid), playerid,
							WeaponName(dataweapons[sl][0]), dataweapons[sl][0],
							(dataweapons[sl][1] - LastAmmo[playerid][ dataweapons[sl][0] ]),
							dataweapons[sl][1], LastAmmo[playerid][ dataweapons[sl][0] ]);
						SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 3);

						DetectedGun[playerid][ LastWeapon[playerid] ] = 0;
				  		DetectedGunCounter[playerid] ++;//добавить предупреждение
				  		if(DetectedGunCounter[playerid] >= CHEATLIM)
				  		{   //если игрок прошёл 5 проверок на чит
							DetectedGunCounter[playerid] = 0;
						    //new reason[23+32];
							format( ReasonPunishment[playerid], 64, "cheating weapons (%s[%d] CheatAmmo:%d)",
								WeaponName( LastWeapon[playerid] ), LastWeapon[playerid], (dataweapons[sl][1] - LastAmmo[playerid][ dataweapons[sl][0] ]));

							ResetPlayerWeaponsEx(playerid);
							SetPlayerArmedWeaponEx(playerid, 0);

							/*new strtmp[22 + 24+3 + 64];
							format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d] %s", PlayerName(playerid), playerid, ReasonPunishment[playerid]);
							Log(CHEAT,strtmp);
							new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
							format(strtmp, sizeof(strtmp), "[%d:%02d:%02d] %s", lH,lM,lS, strtmp);
							SendAllAdminMessage(COLOR_MAROON, strtmp, 3);*/

							//SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на чит оружия (Reset Weapons)");
							//Log(BAN,strings);
							if(IsKicked[playerid] == 0)
							{
								//format(ReasonPunishment[playerid], 64, "Enter in Lock Car: %d", vehicleid);// тп в закрытуют тачку
					        	new strtmp[34 + 24+3 +64];
								format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
									PlayerName(playerid),playerid, ReasonPunishment[playerid]);
								Log(CHEAT, strtmp);
					    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
								IsKicked[playerid] = 1;
							}
							/*if(IsBaned[playerid] == 0 && !gAnticheat[playerid])
							{
								format(strings, sizeof(strings), "CEPBEP: %s[%d] забанен на "#BANTIME" дня, причина: %s.",
									PlayerName(playerid), playerid, reason);
								SendClientMessageToAll(COLOR_RED, strings);

								PlayerInfo[playerid][pLevel] = -999;
								PlayerInfo[playerid][pWarns] = getdate() + BANTIME;
								BanList("CEPBEP", playerid, PlayerInfo[playerid][pWarns], reason);
								IsBaned[playerid] = 1;
							}*/
							return 1;
				  		}
			        }
			    }
				else
				{
					DetectedGun[playerid][ LastWeapon[playerid] ] ++;
					if(DetectedGun[playerid][ LastWeapon[playerid] ] >= CHEATLIM)
					{
						DetectedGun[playerid][ LastWeapon[playerid] ] = 0;
					}
				}
			}
		}
	}
	iLastScrollWeapon[playerid] = LastWeapon[playerid];//для проверки прокрутки скрола закончен
    return 1;
}
//для античита патронов конец




stock anticheat_OnPlayerInterior(playerid, newinteriorid)
{
 	if( !gAnticheat[playerid] &&
	 	newinteriorid == 0 && PlayerInfo[playerid][pInt] != 0)
 	{
   		new Float:x,Float:y,Float:z; GetPlayerPos(playerid, x,y,z);
		new Float: distance = floatsqroot( floatpower(floatsub(x,CurPos[0][playerid]),2) +
			 				floatpower(floatsub(y,CurPos[1][playerid]),2) );
		if(distance >= 44.0)//63.0 при выходе из вагона
		{
	 		//new strings[MAX_STRING];
	   		new reason[53 + 6+4*6+2+2];//87
			format(reason, sizeof(reason), "teleport interior:%d[%d] %.1f(%.1f,%.1f[%.1f,%.1f]) ",
				 newinteriorid, PlayerInfo[playerid][pInt],
				 distance, x,y, CurPos[0][playerid],CurPos[1][playerid]);//PlayerLastAnimation[playerid]

			new strtmp[34 + 24+3 + 87];
			format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s", PlayerName(playerid),playerid, reason);
			Log(CHEAT, strtmp);
			SendAllAdminMessage(COLOR_MAROON, strtmp, 3);

			TeleportDetected[playerid] += 1;
			PlayerInfo[playerid][pInt] = CurInt[playerid];
			PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
			PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
			PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на использование телепортов из интерьера (Kicked).");
			if(PlayerInfo[playerid][pAdmin] != 9) {
				IsKicked[playerid] = 1;
			}
		}
 	}
}

stock IsShooting(playerid, newkeys, oldkeys)
{//для проверки на на бесконечные патроны
	if( !IsFireArm(GetPlayerWeapon(playerid)) ) return -1;
	if(GetPlayerWeaponState(playerid) == WEAPONSTATE_NO_BULLETS) return -1;
	if(GetPlayerWeaponState(playerid) == WEAPONSTATE_RELOADING) return -1;

	if(	//!GetPVarInt(playerid, "IsShooting") &&
			( oldkeys == KEY_FIRE ) ||
			( CurState[playerid] == PLAYER_STATE_DRIVER && AntiDB == 0 &&
				(oldkeys == KEY_FIRE || oldkeys == KEY_ACTION || oldkeys == KEY_VEHICLE_FIRE_LOOK_RIGHT || oldkeys == KEY_VEHICLE_FIRE_LOOK_LEFT) ) ||
		 	( CurState[playerid] == PLAYER_STATE_PASSENGER && GetPlayerCameraMode(playerid) == 55 &&
				(oldkeys == KEY_FIRE || oldkeys == KEY_ACTION) )
	  )
	{
		SetPVarInt(playerid, "IsShooting", 0);
		//if(WEAPON) GameTextForPlayerEx(playerid, "~p~SHOOTING ~r~END", 1000, 3);
		return 0;
	}
//если игрок нажал ОГОНЬ, то вернуть 1
	else if(	//!GetPVarInt(playerid, "IsShooting") &&
			( newkeys == KEY_FIRE ) ||
			( CurState[playerid] == PLAYER_STATE_DRIVER && AntiDB == 0 &&
				(newkeys == KEY_FIRE || newkeys == KEY_ACTION || newkeys == KEY_VEHICLE_FIRE_LOOK_RIGHT || newkeys == KEY_VEHICLE_FIRE_LOOK_LEFT) ) ||
		 	( CurState[playerid] == PLAYER_STATE_PASSENGER && GetPlayerCameraMode(playerid) == 55 &&
				(newkeys == KEY_FIRE || newkeys == KEY_ACTION) )
  		   )
	{
		SetPVarInt(playerid, "IsShooting", 1);
    	//if(WEAPON) GameTextForPlayerEx(playerid, "~p~SHOOTING ~r~BEGIN", 1000, 3);
		return 1;
	}
	return -1;
}

stock OnPlayerKeyFire(playerid, newkeys, oldkeys)//для античита патронов
{ //вызывается из OnPlayerKeyStateChange
//конец стрельбы
	if(IsPlayerControllable[playerid] == 1) return 1;//если игрок обездвижен
	//if(gAnticheat[playerid] == 1) return 1;//не раскоментировать, т.к. есть трейнеры

    if( IsShooting(playerid, newkeys, oldkeys) == 0)
	{   //если игрок закончил стрельбу, т.е. отпустил клавишу огонь,
	    //проверим сколько осталось в пушке
		new weaponid = GetPlayerWeapon(playerid);
		//if(	IsFireArm(weaponid) &&
		//	GetPlayerWeaponState(playerid) != WEAPONSTATE_NO_BULLETS &&
		//	GetPlayerWeaponState(playerid) != WEAPONSTATE_RELOADING)
		//{ 	//а в руках у него огнестрельное оружие,  в котором есть патроны и не перезаряжается в данный момент
			//проверяем не замарожен ли игрок    //или находится в окне
			//GameTextForPlayerEx(playerid, "~p~SHOOTING ~r~END", 1000, 3);

		new slot = GetWeaponSlot(weaponid);
		new dataweapons[13][2];
		GetPlayerWeaponData(playerid, slot, dataweapons[slot][0], dataweapons[slot][1]);

		if(	weaponid == dataweapons[slot][0] &&
			dataweapons[slot][1] > 0 &&
			dataweapons[slot][1] < LastAmmo[playerid][weaponid])
		{	//если текущее значение патронов в стволе уменьшилось
			//и не достигло нуля
			//сработает только при уменьшении патронов
			//ВНИМАНИЕ СЫНОК: GetPlayerAmmo(playerid) не работает на пассажирском сидении
			LastAmmo[playerid][weaponid] = dataweapons[slot][1];//GetPlayerAmmo(playerid);
			//записываем только при окончании стрельбы
		}
		else if(ANTIGUN == 1 &&
			weaponid == dataweapons[slot][0] &&
			dataweapons[slot][1] == LastAmmo[playerid][weaponid])
		{   //чит, т.е. было произведён выстрел, а кол-во патронов осталось тоже
		    //может произойти когда игрок слегка нажал клавишу
			//на короткий промежуток времени
			//тогда засчитает за чит
			if( (GetTickCount()-BugTickCountNew[playerid]) > 4000) //минимальное время на высаживание обоймы?
			{//делаем задержку на проверку, т.к. стрельба одиночными даёт сбой
				//new reason[35+ 2+3];//67+ 32+2+3+3 = 107
				format(ReasonPunishment[playerid], 64, "бесконечные патроны Gun:%d Ammo:%d",
					dataweapons[slot][0], dataweapons[slot][1]);
				ResetPlayerWeaponsEx(playerid);
				SetPlayerArmedWeaponEx(playerid, 0);

				new strtmp[34 + 24+3 + 107];
				format(strtmp, sizeof(strtmp), "AdmWarning: %s[%d] %s", PlayerName(playerid), playerid, ReasonPunishment[playerid]);
				Log(CHEAT, strtmp);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				format(strtmp, sizeof(strtmp), "[%d:%02d:%02d] %s", lH,lM,lS, strtmp);
				SendAllAdminMessage(COLOR_MAROON, strtmp, 3);

				/*if(gVoteKicked == MAX_PLAYERS-1)
				{
					gVoteKicked = playerid;
					format(strtmp, sizeof(strtmp), "CEPBEP: голосование за кик %s[%d] - %s (USE: /votekick)",
						PlayerName(playerid), playerid, ReasonPunishment[playerid]);
					SendClientMessageToAll(COLOR_MAROON, strtmp);
				}
				else
				{*/
					//format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s", PlayerName(playerid),playerid, ReasonPunishment[playerid]);
					//Log(CHEAT, strtmp);
					//SendAllAdminMessage(COLOR_MAROON, strtmp, 3);

				SendClientMessage(playerid, COLOR_RED, "CEPBEP: Подозрение на бесконечные патроны (Reset Weapons)");
					//if(PlayerInfo[playerid][pAdmin] != 9) {
					//	IsKicked[playerid] = 1; }
				//}
			}
		}
    	//if(WEAPON)
		//OnPlayerWeaponStateChange(playerid, weaponid, WEAPONSTATE_MORE_BULLETS, WEAPONSTATE_SHOOTING);
		LastStateWeapon[playerid] = WEAPONSTATE_MORE_BULLETS;
		//return 1;//WEAPONSTATE_MORE_BULLETS;
		//}
		//======================================================================
		if(CHECKING == 2)
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "OnPlayerKeyFire(weapon:%d ammo:%d)", dataweapons[slot][0], dataweapons[slot][1]);
			//SendClientMessageToAll(COLOR_YELLOW, strings);
			SendClientMessage(playerid, COLOR_RED, strings);
		}
		//======================================================================
	}
//начало стрельбы
    else if( IsShooting(playerid, newkeys, oldkeys) == 1)
	{   //нажал огонь, однозначно что то должно было вылететь
		//а в руках у него огнестрельное оружие, которое стреляет и не перезаряжается в данный момент
		//GameTextForPlayerEx(playerid, "~p~SHOOTING ~r~BEGIN", 1000, 3);
		BugTickCountNew[playerid] = GetTickCount();
    	//if(WEAPON)
		//OnPlayerWeaponStateChange(playerid, GetPlayerWeapon(playerid), WEAPONSTATE_SHOOTING, LastStateWeapon[playerid]);
		LastStateWeapon[playerid] = WEAPONSTATE_SHOOTING;
		//return WEAPONSTATE_SHOOTING;
	}
	return 1;//WEAPONSTATE_NO_BULLETS;
}

stock OnPlayerKeyAntiBugC(playerid, newkeys, oldkeys)
{//отключен
 	//if(gAnticheat[playerid] == 1) return 1;
	//if(IsPlayerInAnyVehicle(playerid)) return 1;
    //Bug C Вариант 1
	new ticks = GetTickCount() - BugTickCountOld[playerid];
    if(GetPVarInt(playerid, "Fire") && PRESSED(KEY_CROUCH))
    {   //если старое нажатие было кнопки KEY_FIRE а новое KEY_CROUCH
        //if(22 <= GetPlayerWeapon(playerid) <= 38)
        if(IsCbugWeapon(playerid))
        {
            if(ticks > 10 && ticks < 1500 && GetPlayerSpeed(playerid) > 0)
            {   //если время меньше 1.5 секунды и скорость игрока больше 0
				SetPVarInt(playerid, "PrepareUsedBugC", 1);
            }
            SetPVarInt(playerid, "Fire", 0);
        }
    }
    if(PRESSED(KEY_FIRE))
    {
        SetPVarInt(playerid, "Fire", 1);//кнопка огонь нажата
		BugTickCountOld[playerid] = GetTickCount();
        //записали время нажатия
    }
    //Bug C Вариант 2
	if(PRESSED(KEY_FIRE) && RELEASED(KEY_CROUCH) && GetPVarInt(playerid, "PrepareUsedBugC"))
	{
		CBugCount[playerid] ++;
		if(CBugCount[playerid] > C_BUG_TIME)
		{
			CBugCount[playerid] = 0;
			SetPVarInt(playerid, "PrepareUsedBugC", 0);
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "AdmWarning: %s[%d], reason: Used Bug C", PlayerName(playerid), playerid);
			//ABroadCast(COLOR_MAROON, strings, 5);
			SendAllAdminMessage(COLOR_MAROON, strtmp, 5);
			//SetPlayerVelocity(playerid, 0.0, 0.0, 7.0);
			ResetPlayerWeaponsEx(playerid);//для сброса оружия без лицензии и телефона тоже
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: Used Bug C (Reset Weapons)");
		}
	}
	return 1;
}
stock OnPlayerKeyAntiDB(playerid, newkeys, oldkeys)
{
	//#pragma unused oldkeys
	if(AntiDB == 0) return 1;
	//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar) return 1;
	if(	LastWeapon[playerid] <= 0) return 1;
	if(	!IsFireArm(LastWeapon[playerid]) ) return 1;
	if(	!IsFireArm(GetPlayerWeapon(playerid)) ) return 1;
	if(gLoading[playerid] != 0) return 1;
	if(gUnLoading[playerid] != 0) return 1;
	if(nCarModel[playerid] == 425 || nCarModel[playerid] == 520) return 1;//для гидры и апача допускаем
	if( PRESSED(KEY_FIRE) ||
		((newkeys & KEY_FIRE) && (newkeys & KEY_LOOK_LEFT)) ||
		((newkeys & KEY_FIRE) && (newkeys & KEY_LOOK_RIGHT))
	  )
	{   //запрещаем огонь с водительского сидения влево и вправо
		SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}DriveBy(ДБ, Драйв-Бай) с водительского места Запрещён на этом сервере.");
		RemovePlayerFromVehicleEx(playerid);
		//SetPlayerArmedWeaponEx(playerid, 0);
	}
	return 1;
}


stock OnPlayerKeyAntiBH(playerid, newkeys, oldkeys)
{//банихоп
	#pragma unused oldkeys

	if(!AntiBH) return 1;
	//if(IsPlayerInAnyVehicle(playerid)) return 1;
	/*if( (newkeys & KEY_JUMP) || (newkeys & KEY_SPRINT) &&
		(newkeys & KEY_JUMP) || (newkeys & KEY_UP) &&
		(newkeys & KEY_JUMP) || (newkeys & KEY_DOWN) &&
		(newkeys & KEY_JUMP) || (newkeys & KEY_WALK) &&
		(newkeys & KEY_JUMP) || (newkeys & KEY_LEFT) &&
		(newkeys & KEY_JUMP) || (newkeys & KEY_RIGHT) &&
		//(newkeys & KEY_JUMP) || (newkeys & KEY_FIRE) &&
		(newkeys & KEY_JUMP) )*/
	if(PRESSED(KEY_JUMP))
	{
		new animNew[32];
		new anim_id = GetPlayerAnimationIndex(playerid);
		if(anim_id)
		{
			new animlib[32];
			GetAnimationName(anim_id, animlib, 32, animNew, 32);
			if(//tickcount() - iPlayerKeyTime[playerid] < 10000 &&
	   			(!strcmp(animNew, "JUMP_LAND", true) && !strcmp(animOld[playerid], "RUN_CIVI", true)) ||
				!strcmp(animNew, "JUMP_LAND", true) ||
				!strcmp(animNew, "JUMP_GLIDE", true) ||
				!strcmp(animNew, "JUMP_LAUNCH", true) ||
				!strcmp(animNew, "JUMP_LAUNCH_R", true) ||
				!strcmp(animNew, "FIGHTA_M", true)
			  )
			{   //  отсекаем каждый второй прыжок сделанный за короткий промежуток времени
				ClearAnimations(playerid, 0);
				ApplyAnimation(playerid, "PED", "RUN_STOPR", 4.0, 0, 0, 0, 0, 0, 0);
				//OnePlayAnim(playerid, "PED", "RUN_STOPR", 4.1, 0, 1, 1, 0, 2000);
			   	//OnePlayAnim(playerid, "FAT", "IDLE_TIRED", 4.0, 0, 0, 0, 0, 0);

				//SendClientMessage(playerid, COLOR_RED, "CEPBEP: Вы можете использовать это действие только раз в 2 секунды.");
				/*switch(CheckBunnyHop[playerid])
				{
					case 2:
					{
						CheckBunnyHop[playerid] = 0;
					}
					default:
					{
			   			OnePlayAnim(playerid, "PED", "RUN_STOPR", 4.0, 0, 0, 0, 0, 0);
					}
				}
			 	CheckBunnyHop[playerid] ++;*/
			}
			//iPlayerKeyTime[playerid] = tickcount();
			strmid(animOld[playerid], animNew, 0, strlen(animNew), 32);
		}
	}
	return 1;
}


stock AntiPingTimer(playerid)
{   //предотвращает некоторые ложные срабатывания
	if(gPlayerSpawned[playerid] == 0) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//new strings[MAX_STRING];
	if(GetPlayerPing(playerid) > PINGS && PlayerInfo[playerid][pAdmin] < 1)//1500
	{
		CrashDetected[playerid] = 67;
	    PingCount[playerid] ++;
	    if(PingCount[playerid] > 3)
		{
			format(strings, sizeof(strings), "CEPBEP: {33AA33}Ты был кикнут за высокий пинг (%d)", GetPlayerPing(playerid));
			SendClientMessage(playerid, COLOR_RED, strings);

			if(PlayerInfo[playerid][pAdmin] != 9 && PlayerInfo[playerid][pAccount] == 0)
			{
				format(strings, sizeof(strings), "CEPBEP: %s[%d] kicked, reason: ping %d", PlayerName(playerid),playerid, GetPlayerPing(playerid));
				SendSystemMessage(COLOR_MAROON, strings, 1);
				Log(KICK, strings);
				IsKicked[playerid] = 1;
			}
		}
	}
	return 1;
}

stock JOYPADUpdate(playerid)
{
    new keys, ud, lr;
    GetPlayerKeys(playerid, keys, ud, lr);
    if((ud != 128 && ud != 0 && ud != -128) || (lr != 128 && lr != 0 && lr != -128))
        SendClientMessage(playerid, 0x0FFFFFFA, "JOYPADDER!");
    else
        SendClientMessage(playerid, 0x0FFFFFFA, "Not a joypadder.");
}

