//��� �����
//new switcher;


//##############################################################################//
//                                                                              //
//                    �������������� ���������������� �������                   //
//                                                                              //
//##############################################################################//


//==============================================================================



stock OnPlayerCallTime(playerid)//����������� ������ ������� �� OneSecondTimers
{
	if(TEST[44] != 0) return 1;
	if(PlayerInfo[playerid][pJob] == TRUCKER) return 1;
	//==========================================================================

//��� ����� //��� ������������ � ��� ����������� �� �������
	if( PlayerInfo[playerid][pCarTime] > 0 && !gInDerbyBloodBowl[playerid] )
	{
		PlayerInfo[playerid][pCarTime] --;//������� ������ ��������
		if(PlayerInfo[playerid][pCarTime] <= 0)
	    {
	   		CrashDetected[playerid] = 237;
	    	gUsedFindCount[playerid] = 0;//��������� ����� ������
			PlayerInfo[playerid][pCarTime] = 0;//���������� �������

			gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		}
		PlayerTextDrawSetStringEx(playerid, txdTaskTime[playerid], TimeConverter(PlayerInfo[playerid][pCarTime]));
	}
	//==========================================================================
	//if(gTutorial[playerid]) return 1;//����� ������ ������ �������� � ��������� �����
	//==========================================================================

	//==========================================================================
//��� ������� //��� ���������� //��� ������������� //��� ��������� STEP5
	else if(CallTimeCounter[playerid] > 0)
	{
	    if(CallTimeCounter[playerid] >= CallTime[playerid])
		{   //���� ������� CallTimeCounter �������� �� ������� CallTime
			CallTimeCounter[playerid] = 0;
			CallTime[playerid] = 0;
			SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
			//gUsedFindCount[playerid] = 0;

			//SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], COLOR_ALIVE);// 0xFF0000FF
			//����� �� ������� � ����
			if(MarkerToPlayer[playerid] != MAX_PLAYERS-1) SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], ACTION_COLOR);// 0xFF0000FF

			DisablePlayerCheckpointEx(playerid);
			GameTextForPlayerEx(playerid, "~r~RedMarker gone", 2500, 1);

			//�� �����������, �.�. ����� ��� ���� ������� �����
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
{   //���������� �� OneSecondTimers3
	if(IsPlayerNPC(playerid)) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//if(!IsPlayerInAnyVehicle(playerid)) return 1;//�.�. ����������� GetPlayerVehicleID, � �� nCarID
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
			format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d] {FFFF00}��� ������, �������: %s",
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
					format(strtmp, sizeof(strtmp), "CEPBEP: ����������� �� ��� %s[%d] - %s (USE: /votekick)",
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
				EjectCounter[playerid] = 0;//���� ����� �������� ����� �� ��������
			}
		}
	}
	//----------------------------------------------------------
	if(	ANTICHEAT == 1 && !gAnticheat[playerid] &&
		CheckInCar[playerid] != 2 &&
		(VehInfo[vehicleid][cLock] == 1 ||
		VehInfo[vehicleid][cLock] == 11) )
	{   //���� ����������� �� �������, �� ������/�����
		CrashDetected[playerid] = 69;
		//removePlayerFromVehicle(playerid);
		//if(IsBaned[playerid] == 0)
		if(IsKicked[playerid] == 0)
		{
			format(ReasonPunishment[playerid], 64, "Enter in Lock Car: %d", vehicleid);// �� � ��������� �����
        	new strtmp[34 + 24+3 +64];
			format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
				PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			Log(CHEAT, strtmp);
    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
			IsKicked[playerid] = 1;
			return 1;//0 ��������� ������������� ������ � ��������
		}
	}
	if(	ANTICHEAT == 1 && !gAnticheat[playerid] &&
		vehicleid != nCarID[playerid]
		&& CheckInCar[playerid] != 2)
		 //&& CurState[playerid] == PLAYER_STATE_DRIVER
		 //LastCar(playerid)
	{   //GetPlayerVehicleID(playerid) - �� �������� ���������� ����� �����
	    //���������� ������ �����
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
			return 1;//0 ��������� ������������� ������ � ��������
		}
	}
	if(CheckInCar[playerid] != 2)
	{   //������� ������ ���������� �� �����
		RemovePlayerFromVehicleEx(playerid);
	}
    /*if(CarStatus[vehicleid][st_engine] == VEHICLE_PARAMS_OFF && GetVehicleSpeed(vehicleid) > 1)
    {//����� ������������ ����� ������ ��� �������
		if(IsKicked[playerid] == 0)
		{
			format(ReasonPunishment[playerid], 64, "driving on car[%d] with switched off by engine. speed: %d", vehicleid, GetVehicleSpeed(vehicleid));
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(strings, sizeof(strings), "[%d:%02d:%02d] {FF0000}CEPBEP: {FFFFFF}%s[%d] {FFFF00}��� ������, �������: %s",
			lH,lM,lS, PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			SendClientMessageToAll(COLOR_RED, strings);
			IsKicked[playerid] = 1;
			return 1;//0 ��������� ������������� ������ � ��������
		}
	}*/
	return 1;
}

//CheckFromVehicleStateChange
stock OnPlayerCheckInVehicleTimer(playerid, vehicleid)
{   //���������� ������ ������� �� OneSecondTimers
	if(IsPlayerNPC(playerid)) return 1;
	if(AFK_IdleTime[playerid] >= 3) return 1;
	//if(!IsPlayerInAnyVehicle(playerid)) return 1;

	//new strings[MAX_STRING];
	//��������������
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

	//��� ������������ ����� ��������� �����
	if(VehInfo[vehicleid][cDate] == getdate())
	{   //���� ��� ����� ������� �������
		CrashDetected[playerid] = 50;
		new giveplayerid = ReturnUser(VehInfo[vehicleid][cOwner]);
		//giveplayerid = ReturnUser(VehInfo[nCarID[playerid]][cOwner]);
		if(	IsPlayerConnected(giveplayerid) &&
			VehInfo[vehicleid][cOwned] > 0 &&
			//VehInfo[vehicleid][cOwned] != PlayerInfo[playerid][pSQLID]
			strcmp(VehInfo[vehicleid][cOwner], PlayerName(playerid), true))
		{   //���� ����� �� ����, � �������� �� �������, �� ��� � �� ����������
			RemovePlayerFromVehicleEx(playerid);
			return 1;
		}
	}//���������� �� ����� �� ���������, ���� ��� �� �����������
	//--------------------------------------------------------------------------
	if(gRealWar)
	{
		//SendClientMessage(playerid, COLOR_GREY, "    ������������� ����� ���� RealWar ! ��������� ��� ���� ����� ������� �� ������ !");
		return 1;
	}
	new modelid = VehInfo[vehicleid][cModel];//GetVehicleModel(vehicleid);//������ ID ������ ������� ������������� ��������.
	if(IsInCopCar(vehicleid))//���� �� � ����������� ������
	{
	    if(!IsPermitToRider(playerid) && !IsACop(playerid))
		{ RemovePlayerFromVehicleEx(playerid); return 1; }//���� �� ���
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
	else if(modelid == 488 || modelid == 582)//��� ����������
	{
		if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pMember] != SAN)
		{ RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 552)//��� ����������� ����� Utility_Van
	{
	    if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != ROADWORKER &&
			PlayerInfo[playerid][pJob] != TRUCKER)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 428)//��� ������������ collect money
	{
	    if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != INKASSATOR)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 420 || modelid == 438)//��� ���������
	{
		if(!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != TAXIDRIVER)//Taxi Cab Company spawn
		{ RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(modelid == 431 || modelid == 437)//��� ������������  || vehicleid == 437
	{   //��������� �������� ����� ��� ����
	    if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != BUSDRIVER &&
			PlayerInfo[playerid][pMember] != SAN)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
	}
	else if(IsInHardTruck(vehicleid))//��� �������������� STEP1
	{   //���� �� ���� � �����
	    if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pJob] != TRUCKER)
	    { RemovePlayerFromVehicleEx(playerid); return 1; }
		else if(modelid == 514)//��� ��������������
		{
		    if( (IsPermitToRider(playerid) || PlayerInfo[playerid][pJob] == TRUCKER) && PlayerInfo[playerid][pTruckSkill] < 50)
		    { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
		else if(modelid == 515)//��� ��������������
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
	else if(IsInBike(vehicleid) || VehicleArray[nCarModel[playerid]-400][Category] == Rail_Transport) { }//��� �������� ��� ����
	else if(IsInMotorcycle(vehicleid))
	{//�������� �� ����
	    if(PlayerInfo[playerid][pBikeLic] != 1 && PlayerInfo[playerid][pMember] != TEAM_BIKER)
		{
		    if(gTakingLesson[playerid] != 1) { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
	}
	else//���� �� ���� �� ���-�� ������ ��� ��������� ����, �.�. scooter, ���������
	{
		if(//PlayerInfo[playerid][pCarLic] != 1 ||
			PlayerInfo[playerid][pMember] == TEAM_BIKER)//���� � ��� ��� ���� �� ����
		{
			if(gTakingLesson[playerid] == 1 && modelid == 405) { }
			else if(PlayerInfo[playerid][pCarLic] == 2 &&
				(vehicleid == LessonCar[0] || vehicleid == LessonCar[1] ||vehicleid == LessonCar[2])) { }
			else { RemovePlayerFromVehicleEx(playerid); return 1; }
		}
	}//Done with car check
	//CrashDetected[playerid] = 52;
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "OnPlayerCheckInVehicleTimer(playerid:%d, vehicleid:%d)", playerid, vehicleid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}








stock SyncTime()//���������� ������ ������ �� OneMinutsTimer ��� ������������� �������
{//�������� ������ ����� �����, ������ ����� �� ����� �� ������
	new tmphour;//, tmpminute, tmpsecond;
	//new tmpyear, tmpmonth, tmpday;

	gettime(tmphour, _, _);//�������� ����� �� �����
	//FixHour(tmphour);//��������������� ��� �� �������� timeshift � �������� � shifthour
	//�������� �� ����� ����
	if((tmphour > ghour)//���� ������� ��� ������ ��� ����������
		|| (tmphour == 0 && ghour == 23) &&//��� ������� ��� ����� 0 � ���������� ����� 23
		SynchronizerSaved == 0)//� ���������� ���������� ������� �� ����� ���������
	{
		SynchronizerSaved = 1;//��������� ���������������� ����������
		OneHourTimer();//����������� ��
		ghour = tmphour;//�������� ���������� ��������
		//���� ���� �������� ����� �� �����
		if(gRrealTime == 1)	SetWorldTime(ghour);//���������� ���� ���
	}

//���������������� ����������
	if(SynchronizerSaved >= 1)
	{
		SynchronizerSaved ++;
//���������� ����� ����
		if(SynchronizerSaved == 3)
		{
			new remainder = (getdate()-FirstMonday)%7;//������� �� ������� �� 7
			//��� 7 - ��� ������ ������� ������������ � ����
			if( tmphour == 23 && IsEvenNumber(getdate()) ) //���� ������ �����
			{   //���� 23 ���� ������, ���������� ������
		        mysql_query("DROP TABLE IF EXISTS `backuphouse`");
				mysql_query("CREATE TABLE IF NOT EXISTS `backuphouse` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `house`");
				SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `house` �������� � `backuphouse`!", 1);

				mysql_query("DROP TABLE IF EXISTS `backupsbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupsbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `sbizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `sbizz` �������� � `backupsbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `bizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `bizz` �������� � `backupbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupplayers`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupplayers` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `players`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `players` �������� � `backupplayers`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupvehicles`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupvehicles` \
(`IND` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `vehicles`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `vehicles` �������� � `backupvehicles`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupfamilies`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupfamilies` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `families`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `families` �������� � `backupfamilies`!", 1);

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
//���������� ����� ��������� �������
			else if(tmphour == 23 && remainder == 0)//�������� ������� STEP2
			{   //���� 23 ������ � ������� �����������

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
				SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `house` �������� � `backuphouse`!", 1);

				mysql_query("DROP TABLE IF EXISTS `backupsbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupsbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `sbizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `sbizz` �������� � `backupsbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupbizz`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupbizz` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `bizz`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `bizz` �������� � `backupbizz`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupplayers`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupplayers` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `players`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `players` �������� � `backupplayers`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupvehicles`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupvehicles` \
(`IND` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `vehicles`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `vehicles` �������� � `backupvehicles`!", 1);

		        mysql_query("DROP TABLE IF EXISTS `backupfamilies`");
		        mysql_query("CREATE TABLE IF NOT EXISTS `backupfamilies` \
(`ID` INT AUTO_INCREMENT PRIMARY KEY) \
ENGINE = MYISAM DEFAULT CHARACTER SET = cp1251 COLLATE = cp1251_general_ci \
SELECT * FROM `families`");
		        SendAllAdminMessage(COLOR_LIGHTBLUE, "����� ������� `families` �������� � `backupfamilies`!", 1);
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
				OnCheckProp();//�������� ����� ������ ���
				SendAllAdminMessage(COLOR_MAROON, "�������� ����� ������� ���������", 1);
			}
			SaveHousesSQL();
		}
		else if(SynchronizerSaved == 6)
		{
			if(gCheckProp > 0)
			{
				OnCheckBizz();//�������� �������� ������ ���
				SendAllAdminMessage(COLOR_MAROON, "�������� �������� ������� ���������", 1);
			}
			SaveBizSQL();
		}
		else if(SynchronizerSaved == 7)
		{
			if(gCheckProp > 0)
			{
				OnCheckSBizz();
				SendAllAdminMessage(COLOR_MAROON, "�������� �������� ������� ���������", 1);
			}
			SaveSBizSQL();
		}
		else if(SynchronizerSaved == 8)
		{
			SaveFamiliesSQL("CEPBEP");
			SaveTurfsSQL();
			//��������������
			SendAllAdminMessage(COLOR_MAROON, "���������� ���� ������� ���������", 1);
		}
//���������� ���������
		else if(SynchronizerSaved == 9)
		{

			new remainder = (getdate()-FirstMonday)%7;//������� �� ������� �� 7
			//��� 7 - ��� ������ ������� ������������ � ����
			if(tmphour == 23 && remainder == 0)//�������� ������� STEP2
			{   //���� 23:00 ������ � ������� �����������
				CheckOnline();
			}
			/*else if(tmphour == 3 && remainder == 0 && strcmp(php_host, "localhost", true))
			{	//���� 3 ���� ���� � ������� ����������� � �� localhost
			    new days = 10;
				new ToBase[65 + 3+3];
				format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE %d-`Offline`>%d AND `Offline`>0", getdate(), days);
				mysql_query(ToBase);	mysql_store_result();
				new repeating = mysql_num_rows();
				mysql_free_result();

				index_repeating = 1;

				if(gReminder != -1) { KillTimer(gReminder); gReminder = -1; }
				print("����������� ������!!!");
				//[19/11/2012 03:07:36] ����������� ������!!!
				//[19/11/2012 04:04:51] ����������� ���������!!!
				//����� ��������� �� 1109 ������
				gReminder = SetTimerEx("Reminder", 5000, repeating, "ddd", 0, days, repeating);
			}*/
		}
//��������� ���������� �������
		else if(SynchronizerSaved == 10)
		{
			SaveOnline();

			new remainder = (getdate()-FirstMonday)%7;//������� �� ������� �� 7
			//��� 7 - ��� ������ ������� ������������ � ����
			if(tmphour == 23 && remainder == 0)//�������� ������� STEP2
			{   //���� 23 ������ � ������� �����������, ���������� ������
				mysql_query("UPDATE `players` SET `Online` = `ConnectTime`");
			}

		    //new strings[MAX_STRING];
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(strings, sizeof(strings), "CEPBEP: {800000}������� ����� %02d:%02d", lH,lM);
			SendClientMessageToAll(COLOR_RED, strings);
			SynchronizerSaved = 0;
		}
	}
}



//##############################################################################//
//                                                                              //
//                               ��������� �������                              //
//                                                                              //
//##############################################################################//







//##############################################################################//
//#                                                                            #//
//#                              ������� �������                               #//
//#                                                                            #//
//##############################################################################//






stock PlayerFixRadio(playerid)
{   //����������� �� ������� /fixr, ��� ������, � ��� ������� /music
	if(GetPVarInt(playerid, "gFixRadio") == 0)
	{
		PlaySoundForPlayer(playerid, SOUND_DUAL_TRACK_START);
		SetPVarInt(playerid, "gFixRadio", 1);
		SetTimerEx("PlayerFixRadioTimer", 1000, 0, "d", playerid);
    }
}

forward PlayerFixRadioTimer(playerid);
public PlayerFixRadioTimer(playerid)//����������� ����� 1 ������� 1 ���
{
	PlaySoundForPlayer(playerid, SOUND_DUAL_TRACK_STOP);
	SetPVarInt(playerid, "gFixRadio", 0);
}




public tLoadCarUpgrade()//���������� �� ������� GameModeInit //��� �������� ���� ����������� ������ ����� 25 ������
{   //�������� ������������ �����
	for(new idx = 1; idx<=GetMaxVehicles; idx++)//GetMaxVehicles //MAX_VEHICLES //sizeof(VehInfo)
	{
		//!!! ���� ���������� �����!!! ������ ����� ��������, ��� ��� �� ����� ��������� ����� ������� restart
		//if(VehInfo[idx][cModel] < 400) continue;
		if(!IsValidVehicle(idx)) continue;
		LoadCarUpgrade(idx);//��� �������
		StartTruckHealth[idx] = 1000.0;//���������� � ���������� ��� ���������� �������� �������� �����
	}
	RespawnAllCars();
	//SendClientMessageToAll(COLOR_GREEN, "   B�� ��������� ����� �����������! ������� ���� !");
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




