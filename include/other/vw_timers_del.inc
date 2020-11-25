//для вайпа
//new switcher;


//##############################################################################//
//                                                                              //
//                    САМОВЫЗЫВАЕМЫЕ ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ                   //
//                                                                              //
//##############################################################################//


//==============================================================================



stock OnPlayerCallTime(playerid)//запускается каждую секунду из OneSecondTimers
{
	if(TEST[44] != 0) return 1;
	if(PlayerInfo[playerid][pJob] == TRUCKER) return 1;
	//==========================================================================

//для ДЕРБИ //для наркодилеров и для ограничения по времени
	if( PlayerInfo[playerid][pCarTime] > 0 && !gInDerbyBloodBowl[playerid] )
	{
		PlayerInfo[playerid][pCarTime] --;//счётчик секунд работает
		if(PlayerInfo[playerid][pCarTime] <= 0)
	    {
	   		CrashDetected[playerid] = 237;
	    	gUsedFindCount[playerid] = 0;//разрешить снова искать
			PlayerInfo[playerid][pCarTime] = 0;//остановить счётчик

			gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		}
		PlayerTextDrawSetStringEx(playerid, txdTaskTime[playerid], TimeConverter(PlayerInfo[playerid][pCarTime]));
	}
	//==========================================================================
	//if(gTutorial[playerid]) return 1;//игрок сможет юзатьб обучении в корыстных целях
	//==========================================================================

	//==========================================================================
//для медиков //для детективов //для автомехаников //для таксистов STEP5
	else if(CallTimeCounter[playerid] > 0)
	{
	    if(CallTimeCounter[playerid] >= CallTime[playerid])
		{   //если счётчик CallTimeCounter досчитал до отметки CallTime
			CallTimeCounter[playerid] = 0;
			CallTime[playerid] = 0;
			SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
			//gUsedFindCount[playerid] = 0;

			//SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], COLOR_ALIVE);// 0xFF0000FF
			//чтобы не флудило в чате
			if(MarkerToPlayer[playerid] != MAX_PLAYERS-1) SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], ACTION_COLOR);// 0xFF0000FF

			DisablePlayerCheckpointEx(playerid);
			GameTextForPlayerEx(playerid, "~r~RedMarker gone", 2500, 1);

			//не освобождаем, т.к. может кто нить принять после
			//playeridMedicCall = MAX_PLAYERS-1;
			//playeridTaxiCall = MAX_PLAYERS-1;
			//playeridMechanicCall = MAX_PLAYERS-1;
			playeridTaxiAccepted[playerid] = MAX_PLAYERS-1;

			GPS_OnOff[playerid] = 0;
		}
	    else
		{
			if(PlayerInfo[playerid][pGPS] == 1 && GPS_OnOff[playerid] == 1 && MarkerToPlayer[playerid] != MAX_PLAYERS-1)
			{
				if(PlayerInfo[MarkerToPlayer[playerid]][pInt] == 0)
				{   // && PlayerInfo[playerid][pLocal] == FREEROAM
					new Float:X,Float:Y,Float:Z;
					GetPlayerPos(MarkerToPlayer[playerid], X, Y, Z);
					SetPlayerRouting(playerid, X, Y, Z);
				}
				else //if(PlayerInfo[MarkerToPlayer[playerid]][pInt] > 0)
				{
					if(PlayerInfo[MarkerToPlayer[playerid]][pLocal] < 100)
					{
						new house = PlayerInfo[MarkerToPlayer[playerid]][pLocal];
						SetPlayerRouting(playerid, HouseInfo[house][hEntranceX], HouseInfo[house][hEntranceY], HouseInfo[house][hEntranceZ]);
					}
					else if(PlayerInfo[MarkerToPlayer[playerid]][pLocal] >= 100 && PlayerInfo[MarkerToPlayer[playerid]][pLocal] < 200)
					{
						new bouse = PlayerInfo[MarkerToPlayer[playerid]][pLocal]-100;
						SetPlayerRouting(playerid, BizInfo[bouse][bEntranceX], BizInfo[bouse][bEntranceY], BizInfo[bouse][bEntranceZ]);
					}
					//else
					//{
		 			//	if(PlayerInfo[playerid][pLocal] == 201)			sRegion = "Hospital LS";
					//	else if(PlayerInfo[playerid][pLocal] == 202)	sRegion = "Hospital SF";
					//	else if(PlayerInfo[playerid][pLocal] == 203)	sRegion = "Hospital LV";
					//	else if(PlayerInfo[playerid][pLocal] == 211)	sRegion = "8ball Track LS";
					//	else if(PlayerInfo[playerid][pLocal] == 241)	sRegion = "CityHall";
					//	else if(PlayerInfo[playerid][pLocal] == 242)	sRegion = "Hitman Agency";
					//	else if(PlayerInfo[playerid][pLocal] == 243)	sRegion = "LCN Mansion";
					//	else if(PlayerInfo[playerid][pLocal] == 244)	sRegion = "Yakudza Mansion";
					//	else if(PlayerInfo[playerid][pLocal] == 245)	sRegion = "Cracker House";
					//	else if(PlayerInfo[playerid][pLocal] == 246)	sRegion = "LSPD";
					//	else if(PlayerInfo[playerid][pLocal] == 247)	sRegion = "SFPD";
					//	else if(PlayerInfo[playerid][pLocal] == 248)	sRegion = "LVPD";
					//}
				}

			}
			CallTimeCounter[playerid] += 1;
		}
		new strtmp[14+5];
		format(strtmp, sizeof(strtmp), "~p~Time ~w~%s", TimeConverter(CallTime[playerid] - CallTimeCounter[playerid]) );
		PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strtmp);
	}
	return 1;
}
















//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

stock PlayerCheckInCarTimer(playerid, vehicleid)
{   //вызывается из OneSecondTimers3
	if(IsPlayerNPC(playerid)) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//if(!IsPlayerInAnyVehicle(playerid)) return 1;//т.к. проверяется GetPlayerVehicleID, а не nCarID
    //new strings[MAX_STRING];
	//----------------------------------------------------------
	if( (IsPlayerInArea(playerid, specialzone[14]) && CurState[playerid] == PLAYER_STATE_DRIVER) ||
		IsPlayerInArea(playerid, specialzone[17]) ||
		IsPlayerInArea(playerid, specialzone[18])
	  )
	{
		if(IsKicked[playerid] == 0)
		{
			strmid(ReasonPunishment[playerid], "Used Bug", 0, strlen("Used Bug"), 64);
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d] {FFFF00}был кикнут, причина: %s",
				lH,lM,lS, PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			SendClientMessageToAll(COLOR_MAROON, strings);
			IsKicked[playerid] = 1;
			return 1;
		}
	}
	//----------------------------------------------------------
	if(	ANTICHEAT == 1 && !gAnticheat[playerid] &&
		EjectCounter[playerid] > 0)
	{
		CrashDetected[playerid] = 48;
		if(IsKicked[playerid] == 0)
		{
			InCarFloodCounter[playerid] ++;
		    if(InCarFloodCounter[playerid] >= CHEATLIM+3)//5
			{
				InCarFloodCounter[playerid] = 0;
	         	format(ReasonPunishment[playerid], 64, "Car Magnetick %s", VehicleArray[nCarModel[playerid]-400][Vehicle_Name]);
				/*if(gVoteKicked == MAX_PLAYERS-1)
				{
					gVoteKicked = playerid;
					new strtmp[56 + 24+3 + 64];
					format(strtmp, sizeof(strtmp), "CEPBEP: голосование за кик %s[%d] - %s (USE: /votekick)",
						PlayerName(playerid), playerid, ReasonPunishment[playerid]);
					SendClientMessageToAll(COLOR_MAROON, strtmp);
					return 1;
				}*/
	  	        if(EjectCounter[playerid] >= CHEATLIM+1)//3// && AFK_IdleTime[playerid] < 3
	  	        {
	  	        	new strtmp[34 + 24+3 +64];
					format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
						PlayerName(playerid),playerid, ReasonPunishment[playerid]);
					Log(CHEAT, strtmp);
		    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
					IsKicked[playerid] = 1;
					EjectCounter[playerid] = 0;
					return 1;
				}
				EjectCounter[playerid] = 0;//если время проверки вышло то сбросить
			}
		}
	}
	//----------------------------------------------------------
	if(	ANTICHEAT == 1 && !gAnticheat[playerid] &&
		CheckInCar[playerid] != 2 &&
		(VehInfo[vehicleid][cLock] == 1 ||
		VehInfo[vehicleid][cLock] == 11) )
	{   //если выкидывание не помогло, то кикаем/баним
		CrashDetected[playerid] = 69;
		//removePlayerFromVehicle(playerid);
		//if(IsBaned[playerid] == 0)
		if(IsKicked[playerid] == 0)
		{
			format(ReasonPunishment[playerid], 64, "Enter in Lock Car: %d", vehicleid);// тп в закрытуют тачку
        	new strtmp[34 + 24+3 +64];
			format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
				PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			Log(CHEAT, strtmp);
    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
			IsKicked[playerid] = 1;
			return 1;//0 отключает синхронизацию игрока с сервером
		}
	}
	if(	ANTICHEAT == 1 && !gAnticheat[playerid] &&
		vehicleid != nCarID[playerid]
		&& CheckInCar[playerid] != 2)
		 //&& CurState[playerid] == PLAYER_STATE_DRIVER
		 //LastCar(playerid)
	{   //GetPlayerVehicleID(playerid) - не успевает определить новое место
	    //показывает старую тачку
		CrashDetected[playerid] = 70;
		//removePlayerFromVehicle(playerid);
		//if(IsBaned[playerid] == 0)
		if(IsKicked[playerid] == 0)
		{
			format(ReasonPunishment[playerid], 64, "Enter in Alien CarID: %d from nCarID: %d", vehicleid, nCarID[playerid]);
        	new strtmp[34 + 24+3 +64];
			//format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] baned, reason: %s",
			format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
				PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			Log(CHEAT, strtmp);
    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
			//IsBaned[playerid] = 1;
			IsKicked[playerid] = 1;
			return 1;//0 отключает синхронизацию игрока с сервером
		}
	}
	if(CheckInCar[playerid] != 2)
	{   //сначало просто выкидываем из тачки
		RemovePlayerFromVehicleEx(playerid);
	}
    /*if(CarStatus[vehicleid][st_engine] == VEHICLE_PARAMS_OFF && GetVehicleSpeed(vehicleid) > 1)
    {//будут срабаытвания когда машина идёт накатом
		if(IsKicked[playerid] == 0)
		{
			format(ReasonPunishment[playerid], 64, "driving on car[%d] with switched off by engine. speed: %d", vehicleid, GetVehicleSpeed(vehicleid));
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d] {FFFF00}был кикнут, причина: %s",
			lH,lM,lS, PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			SendClientMessageToAll(COLOR_RED, strings);
			IsKicked[playerid] = 1;
			return 1;//0 отключает синхронизацию игрока с сервером
		}
	}*/
	return 1;
}

//CheckFromVehicleStateChange
stock OnPlayerCheckInVehicleTimer(playerid, vehicleid)
{   //вызывается каждую секунду из OneSecondTimers
	if(IsPlayerNPC(playerid)) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//if(!IsPlayerInAnyVehicle(playerid)) return 1;

	//new strings[MAX_STRING];
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "OnPlayerCheckInVehicleTimer(playerid:%d, vehicleid:%d)", playerid, vehicleid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	//SendClientMessageToAll(COLOR_GREEN, strings);
/*
	new Float:X,Float:Y,Float:Z;
	new Float:rotX,Float:rotY,Float:rotZ;
	GetVehiclePos(vehicleid, X, Y, Z);
	GetVehicleRotation(vehicleid, rotX, rotY, rotZ);
	format(strings, sizeof(strings),
		"AdmWarning: VehicleDeath [%d]. LastDriver: %s[%d]. X: %.1f, Y: %.1f, Z: %.1f; rotX: %.1f, rotY: %.1f, rotZ: %.1f",
		vehicleid, PlayerName(LastDriver[vehicleid]), LastDriver[vehicleid], X, Y, Z, rotX, rotY, rotZ);
	ABroadCast(ADMINS_MESSAGE_COLOR, strings, 9);
*/
	//if(CheckInCar[playerid] == 2) antidb_OnPlayerStateChange(playerid);
	//----------------------------------------------------------------------
	if(VehInfo[vehicleid][cPark] == 1)
	{
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	//----------------------------------------------------------------------
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;

	//для противоугона свеже купленной тачки
	if(VehInfo[vehicleid][cDate] == getdate())
	{   //если это тачка куплена сегодня
		CrashDetected[playerid] = 50;
		new giveplayerid = ReturnUser(VehInfo[vehicleid][cOwner]);
		//giveplayerid = ReturnUser(VehInfo[nCarID[playerid]][cOwner]);
		if(	IsPlayerConnected(giveplayerid) &&
			VehInfo[vehicleid][cOwned] > 0 &&
			//VehInfo[vehicleid][cOwned] != PlayerInfo[playerid][pSQLID]
			strcmp(VehInfo[vehicleid][cOwner], PlayerName(playerid), true))
		{   //если тачка не ваша, а владелец на сервере, но ещё её не запарковал
			RemovePlayerFromVehicleEx(playerid);
			return 1;
		}
	}//выкидываем из тачки не владельца, пока она не запаркована
	//--------------------------------------------------------------------------
	if(gRealWar)
	{
		//SendClientMessage(playerid, COLOR_GREY, "    Активизирован режим игры RealWar ! Подробнее про этот режим читайте на форуме !");
		return 1;
	}
	new modelid = VehInfo[vehicleid][cModel];//GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	if(IsInCopCar(vehicleid))//если вы в полицейской машине
	{
	    if(!IsPermitToRider(playerid) && !IsACop(playerid))
		{ RemovePlayerFromVehicleEx(playerid); return 1; }//если вы коп
	}
	else if(IsInNGCar(vehicleid))
	{
	    if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pMember] != DoD
			&& !IsAMilitary(playerid))
		{ RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(IsInAmbulanceCar(vehicleid))
	{
	    if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pMember] != DoH &&
   			PlayerInfo[playerid][pJob] != FIREMAN)
		{ RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 488 || modelid == 582)//для репортеров
	{
		if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pMember] != SAN)
		{ RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 552)//Для ремонтников дорог Utility_Van
	{
	    if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != ROADWORKER &&
			PlayerInfo[playerid][pJob] != TRUCKER)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 428)//для инкассаторов collect money
	{
	    if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != INKASSATOR)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 420 || modelid == 438)//для таксистов
	{
		if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != TAXIDRIVER)//Taxi Cab Company spawn
		{ RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 431 || modelid == 437)//для автобусников  || vehicleid == 437
	{   //остальные автобусы будут для всех
	    if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != BUSDRIVER &&
			PlayerInfo[playerid][pMember] != SAN)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(IsInHardTruck(vehicleid))//для дальнобойщиков STEP1
	{   //если Вы сели в тягач
	    if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != TRUCKER)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
		else if(modelid == 514)//для дальнобойщиков
		{
		    if( (IsPermitToRider(playerid) || PlayerInfo[playerid][pJob] == TRUCKER) && PlayerInfo[playerid][pTruckSkill] < 50)
		    { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
		else if(modelid == 515)//для дальнобойщиков
		{
		    if(	(IsPermitToRider(playerid) || PlayerInfo[playerid][pJob] == TRUCKER) && PlayerInfo[playerid][pTruckSkill] < 400)
		    { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
	}
	//----------------------------------------------------------------------
	if(IsInBoat(vehicleid))
	{
	    if(PlayerInfo[playerid][pBoatLic] != 1) { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(IsInPlane(vehicleid))
	{
	    if(PlayerInfo[playerid][pFlyLic] != 1)
		{
			if(modelid == 469)
			{
				if(gTakingLesson[playerid] != 2) { RemovePlayerFromVehicleEx(playerid); return 1; }
			}
			else { RemovePlayerFromVehicleEx(playerid);  return 1; }
		}
	}
	else if(IsInBike(vehicleid) || VehicleArray[nCarModel[playerid]-400][Category] == Rail_Transport) { }//для вождения без прав
	else if(IsInMotorcycle(vehicleid))
	{//лицензия на мото
	    if(PlayerInfo[playerid][pBikeLic] != 1 && PlayerInfo[playerid][pMember] != TEAM_BIKER)
		{
		    if(gTakingLesson[playerid] != 1) { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
	}
	else//если вы сели во что-то другое чем указанное выше, т.е. scooter, велосипед
	{
		if(//PlayerInfo[playerid][pCarLic] != 1 ||
			PlayerInfo[playerid][pMember] == TEAM_BIKER)//если у вас нет прав на авто
		{
			if(gTakingLesson[playerid] == 1 && modelid == 405) { }
			else if(PlayerInfo[playerid][pCarLic] == 2 &&
				(vehicleid == LessonCar[0] || vehicleid == LessonCar[1] ||vehicleid == LessonCar[2])) { }
			else { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
	}//Done with car check
	//CrashDetected[playerid] = 52;
	//ИНФОРМИРОВАНИЕ
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "OnPlayerCheckInVehicleTimer(playerid:%d, vehicleid:%d)", playerid, vehicleid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}








stock SyncTime()//вызывается каждую минуту из OneMinutsTimer для синхронизации времени
{//изменяет только время суток, самому время на часах не меняет
	new tmphour;//, tmpminute, tmpsecond;
	//new tmpyear, tmpmonth, tmpday;

	gettime(tmphour, _, _);//получили время из Биоса
	//FixHour(tmphour);//скорректировали его на величину timeshift и записали в shifthour
	//проверка на смену часа
	if((tmphour > ghour)//если текущий час больше чем предыдущий
		|| (tmphour == 0 && ghour == 23) &&//или текущий час равен 0 и предыдущий равен 23
		SynchronizerSaved == 0)//и предыдущее сохранение успешно до конца выполнено
	{
		SynchronizerSaved = 1;//запускаем последовательное сохранение
		OneHourTimer();//расчитывает ЗП
		ghour = tmphour;//записали полученное значение
		//если счас реальное время из биоса
		if(gRrealTime == 1)	SetWorldTime(ghour);//установить этот час
	}

//ПОСЛЕДОВАТЕЛЬНОЕ СОХРАНЕНИЕ
	if(SynchronizerSaved >= 1)
	{
		SynchronizerSaved ++;
//сохранение через день
		if(SynchronizerSaved == 3)
		{
			new remainder = (getdate()-FirstMonday)%7;//остаток от деления на 7
			//где 7 - это числов первого понедельника в году
			if( tmphour == 23 && IsEvenNumber(getdate()) ) //если чётное число
			{   //если 23 часа вечера, производим запись
		        mysql_query("DROP TABLE IF EXISTS `backuphouse`");
				mysql_query("CREATE TABLE IF NOT EXISTS `backuphouse` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `house`");
				SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `house` сохранён в `backuphouse`!", 1);

				mysql_query("DROP TABLE IF EXISTS `backupsbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupsbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `sbizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `sbizz` сохранён в `backupsbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `bizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `bizz` сохранён в `backupbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupplayers`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupplayers` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `players`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `players` сохранён в `backupplayers`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupvehicles`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupvehicles` \
(`IND` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `vehicles`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `vehicles` сохранён в `backupvehicles`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupfamilies`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupfamilies` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `families`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `families` сохранён в `backupfamilies`!", 1);

		        /*
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupturfs`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `turfs`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `invitelist`
(`IND` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_bin
SELECT * FROM `banlist`");*/
			}
//сохранение перед проверкой онлайна
			else if(tmphour == 23 && remainder == 0)//Проверка онлайна STEP2
			{   //если 23 вечера и сегодня понедельник

	        	/*
				mysql_query("CREATE TABLE IF NOT EXISTS `house`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backuphouse`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `sbizz`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backupsbizz`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `bizz`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backupbizz`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `players`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backupplayers`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `vehicles`
(`IND` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backupvehicles`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `families`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backupfamilies`");

		        mysql_query("CREATE TABLE IF NOT EXISTS `turfs`
(`ID` INT AUTO_INCREMENT PRIMARY KEY)
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci
SELECT * FROM `backupturfs`");
*/

		        mysql_query("DROP TABLE IF EXISTS `backuphouse`");
				mysql_query("CREATE TABLE IF NOT EXISTS `backuphouse` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `house`");
				SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `house` сохранён в `backuphouse`!", 1);

				mysql_query("DROP TABLE IF EXISTS `backupsbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupsbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `sbizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `sbizz` сохранён в `backupsbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `bizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `bizz` сохранён в `backupbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupplayers`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupplayers` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `players`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `players` сохранён в `backupplayers`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupvehicles`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupvehicles` \
(`IND` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `vehicles`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `vehicles` сохранён в `backupvehicles`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupfamilies`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupfamilies` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `families`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "Бэкап таблицы `families` сохранён в `backupfamilies`!", 1);
			}
		}
		else if(SynchronizerSaved == 4)
		{
			SaveCarSQL();
		}
		else if(SynchronizerSaved == 5)
		{
			if(gCheckProp > 0)
			{
				OnCheckProp();//проверка домов каждый час
				SendAllAdminMessage(COLOR_MAROON, "Проверка домов успешна завершена", 1);
			}
			SaveHousesSQL();
		}
		else if(SynchronizerSaved == 6)
		{
			if(gCheckProp > 0)
			{
				OnCheckBizz();//проверка бизнесов каждый час
				SendAllAdminMessage(COLOR_MAROON, "Проверка бизнесов успешна завершена", 1);
			}
			SaveBizSQL();
		}
		else if(SynchronizerSaved == 7)
		{
			if(gCheckProp > 0)
			{
				OnCheckSBizz();
				SendAllAdminMessage(COLOR_MAROON, "Проверка компаний успешна завершена", 1);
			}
			SaveSBizSQL();
		}
		else if(SynchronizerSaved == 8)
		{
			SaveFamiliesSQL("CEPBEP");
			SaveTurfsSQL();
			//ИНФОРМИРОВАНИЕ
			SendAllAdminMessage(COLOR_MAROON, "Сохранение банд успешно завершено", 1);
		}
//СОХРАНЕНИЕ ЗАКОНЧЕНО
		else if(SynchronizerSaved == 9)
		{

			new remainder = (getdate()-FirstMonday)%7;//остаток от деления на 7
			//где 7 - это числов первого понедельника в году
			if(tmphour == 23 && remainder == 0)//Проверка онлайна STEP2
			{   //если 23:00 вечера и сегодня понедельник
				CheckOnline();
			}
			/*else if(tmphour == 3 && remainder == 0 && strcmp(php_host, "localhost", true))
			{	//если 3 часа ночи и сегодня понедельник и не localhost
			    new days = 10;
				new ToBase[65 + 3+3];
				format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE %d-`Offline`>%d AND `Offline`>0", getdate(), days);
				mysql_query(ToBase);	mysql_store_result();
				new repeating = mysql_num_rows();
				mysql_free_result();

				index_repeating = 1;

				if(gReminder != -1) { KillTimer(gReminder); gReminder = -1; }
				print("Напоминание начато!!!");
				//[19/11/2012 03:07:36] Напоминание начато!!!
				//[19/11/2012 04:04:51] Напоминание закончено!!!
				//Всего разослано на 1109 ящиков
				gReminder = SetTimerEx("Reminder", 5000, repeating, "ddd", 0, days, repeating);
			}*/
		}
//обнуление недельного онлайна
		else if(SynchronizerSaved == 10)
		{
			SaveOnline();

			new remainder = (getdate()-FirstMonday)%7;//остаток от деления на 7
			//где 7 - это числов первого понедельника в году
			if(tmphour == 23 && remainder == 0)//Проверка онлайна STEP2
			{   //если 23 вечера и сегодня понедельник, производим запись
				mysql_query("UPDATE `players` SET `Online` = `ConnectTime`");
			}

		    //new strings[MAX_STRING];
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(strings, sizeof(strings), "CEPBEP: {800000}Текущее Время %02d:%02d", lH,lM);
			SendClientMessageToAll(COLOR_RED, strings);
			SynchronizerSaved = 0;
		}
	}
}



//##############################################################################//
//                                                                              //
//                               ПРИВАТНЫЕ ФУНКЦИИ                              //
//                                                                              //
//##############################################################################//







//##############################################################################//
//#                                                                            #//
//#                              РАЗОВЫЕ ТАЙМЕРЫ                               #//
//#                                                                            #//
//##############################################################################//






stock PlayerFixRadio(playerid)
{   //запускается по команде /fixr, при спауне, и при команде /music
	if(GetPVarInt(playerid, "gFixRadio") == 0)
	{
		PlaySoundForPlayer(playerid, SOUND_DUAL_TRACK_START);
		SetPVarInt(playerid, "gFixRadio", 1);
		SetTimerEx("PlayerFixRadioTimer", 1000, 0, "d", playerid);
    }
}

forward PlayerFixRadioTimer(playerid);
public PlayerFixRadioTimer(playerid)//запускается через 1 секунду 1 раз
{
	PlaySoundForPlayer(playerid, SOUND_DUAL_TRACK_STOP);
	SetPVarInt(playerid, "gFixRadio", 0);
}




public tLoadCarUpgrade()//вызывается из функции GameModeInit //для загрузки тюна запускается разово через 25 секунд
{   //загрузка модернизаций машин
	for(new idx = 1; idx<=GetMaxVehicles; idx++)//GetMaxVehicles //MAX_VEHICLES //sizeof(VehInfo)
	{
		//!!! Будь ВНИМАТЕЛЕН Сынок!!! Ошибка может привести, что мод не будет загружать после команды restart
		//if(VehInfo[idx][cModel] < 400) continue;
		if(!IsValidVehicle(idx)) continue;
		LoadCarUpgrade(idx);//для тюнинга
		StartTruckHealth[idx] = 1000.0;//установили в переменной для правильных расчётов починили тягач
	}
	RespawnAllCars();
	//SendClientMessageToAll(COLOR_GREEN, "   Bсе параметры машин установлены! Доброго пути !");
	//KillTimer(loadcarupgradetimer);
	loadcarupgradetimer = -1;

	//==========================================================================
	cargoship_OnGameModeInit();
	//airdefence_OnGameModeInit();
 	//==========================================================================
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "loadfs vw_pirateisland");
	//SendRconCommand(strings);

	//format(strings, sizeof(strings), "loadfs vw_ferriswheel");
	//SendRconCommand(strings);

	//format(strings, sizeof(strings), "loadfs flymode");
	//SendRconCommand(strings);
}




