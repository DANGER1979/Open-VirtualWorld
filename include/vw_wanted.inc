//##############################################################################//
//                                                                              //
//                  СИСТЕМА НАЧИСЛЕНИЯ ОЧКОВ РОЗЫСКА и СНЯТИЯ                   //
//                                                                              //
//##############################################################################//


new LevelToCriminality = 0;
new LevelToDeliver = 0;


//==============================================================================





stock wanted_OnVehicleDeath(vehicleid, killerid)
{
	#pragma unused killerid
	gVehicleSpawn[vehicleid] = 1;
	DestroyVehicleEx(vehicleid, 6);

//-------------------------------------------------------------------------------
	new Float:X,Float:Y,Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);

//можно поставить проверку на высоту тачки, т.е. если ниже 1 то значит она правильно умирает
//но тогда читер сможет каждую тачку опусть ниже земли и тачки будут умирать после его ф-ии респа
	if(	VehInfo[vehicleid][cPark] == 0 && //(VehHealth[vehicleid] <= 250.0 || Z < 1.0) &&
		GetVehicleModel(vehicleid) != 460 && GetVehicleModel(vehicleid) != 539)
	{
		//----------------------------------------------------------------------
		if(VehInfo[vehicleid][cType] >= 1000)
		{
			new playerid = ReturnUser(VehInfo[vehicleid][cOwner]);
			if( IsPlayerConnected(playerid) && killerid != playerid ) SetPlayerWantedPoints(playerid, killerid, 60);
//Уничтожение транспорта: %s[%d]", WantedPoints[killerid] += 25;
		}
		gVehicleSpawn[vehicleid] = 1;
		DestroyVehicleEx(vehicleid, 6);
	}
}


stock SetPlayerWantedPoints(playerid, killerid, reason)
{//вызывается из OnPlayerDeath
	//if(playerid == INVALID_PLAYER_ID) return 1;
	//if(killerid == INVALID_PLAYER_ID) return 1;
	if( gRealWar ) return 1;
	if( !IsPlayerConnected(playerid) ) return 1;
	if( !IsPlayerConnected(killerid) ) return 1;
	if(gPlayerBoxing[killerid] == 1) return 1;
	if(gInTerrorsCount[killerid] > 0 || gInCTerrorsCount[killerid] > 0)	return 1;

	//назначение статьи розыска за убийство
	if(PlayerInfo[killerid][pJailed] >= 1 && PlayerInfo[killerid][pJailed] <= 3 &&
		PlayerInfo[playerid][pJailed] >= 1 && PlayerInfo[playerid][pJailed] <= 3)
	{
		PlayerInfo[killerid][pJailTime] += 10;
		SendClientMessage(killerid,COLOR_MAROON, "За убийство в КПЗ +10 минут к сроку.");
	}
	else if(PlayerInfo[killerid][pJailed] == 10 && PlayerInfo[playerid][pJailed] == 10 &&
		IsPlayerInArea(playerid, specialzone[2]) )
	{
		PlayerInfo[killerid][pJailTime] += 30;
		SendClientMessage(killerid,COLOR_MAROON, "За убийство на зоне +30 минут к сроку.");
	}

	else if(( gOnDuty[killerid] &&//cops kill civ
			( IsACop(killerid) || PlayerInfo[killerid][pMember] == DoD ||
			//( PlayerInfo[killerid][pMember] == DoJ && IsPlayerInArea(playerid, specialzone[7]) ) ||
			( PlayerInfo[killerid][pMember] == DoJ && PlayerInfo[playerid][pLocal] == 241) ||
			( PlayerInfo[killerid][pMember] == DoJ && PlayerInfo[killerid][pRank] == 1 ) ||
			( PlayerInfo[killerid][pMember] == DoE && IsPlayerInArea(playerid, checkCoords[1]) ))
			|| gJobDuty[killerid] && PlayerInfo[killerid][pJob] == CARDEALER && IsPlayerInArea(playerid, specialzone[8]) )
		   )
	{
		if(reason == 50)// && GetPlayerState(killerid) == PLAYER_STATE_DRIVER
		{
			WantedPoints[killerid] += 25;
			new strtmp[30+32+3];
			format(strtmp, sizeof(strtmp), "Убийство транспортом: %s[%d]",
				VehicleArray[nCarModel[killerid]-400][Vehicle_Name], nCarID[killerid]);
			SetPlayerCriminal(FBI, killerid, playerid, strtmp);
			SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [139] [1-5] [playerid/PartOfName]");
		}
		//else //иначе ни чего не делать
	}
	else if((IsAFamilyMember(killerid) && IsAFamilyMember(playerid)) ||
			(IsAFamilyMember(playerid) && IsAGangs(killerid)) ||
			(IsAFamilyMember(killerid) && IsAGangs(playerid)) ||
			(IsAGangs(killerid) && IsAGangs(playerid))
			)
	{
		if(reason == 50) // && GetPlayerState(killerid) == PLAYER_STATE_DRIVER
		{
			WantedPoints[killerid] += 25;
			new strtmp[30+32+3];
			format(strtmp, sizeof(strtmp), "Убийство транспортом: %s[%d]",
				VehicleArray[nCarModel[killerid]-400][Vehicle_Name], nCarID[killerid]);
			SetPlayerCriminal(FBI, killerid, playerid, strtmp);
			SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [139] [1-5] [playerid/PartOfName]");
		}
	}
	else if(reason != 50 && IsPlayerInAnyVehicle(killerid) && GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
	{
		if(reason == 28 || reason == 29 || reason == 31 || reason == 32) // && GetPlayerState(killerid) == PLAYER_STATE_DRIVER
		{  //  || reason == 38 || reason == 51
			WantedPoints[killerid] += 25;
			new strtmp[39+32+3];
			format(strtmp, sizeof(strtmp), "Убийство с водительского места: %s[%d]",
				VehicleArray[nCarModel[killerid]-400][Vehicle_Name], nCarID[killerid]);
			SetPlayerCriminal(FBI, killerid, playerid, strtmp);
			SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [139] [1-5] [playerid/PartOfName]");
		}//огнестрельным оружием
	}
	else
	{
		if(PlayerInfo[killerid][pJailed] == 0)// || PlayerInfo[playerid][pJailed] == 10 - итак в розыске
		{   //если игрок не арестован т.е. не в камере то начислять розыск по обычной схеме
			//new strings[MAX_STRING];
			if(reason >= 0 && reason <= 15)
			{
				WantedPoints[killerid] += 10;
				SetPlayerCriminal(FBI, killerid, playerid, " Причинение тяжкого вреда здоровью, повлекшее смерть потерпевшего");
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [144] [1-2] [playerid/PartOfName]");
			}
			else if(reason >= 22 && reason <= 34)
			{
				WantedPoints[killerid] += 15;
				new strtmp[64];
				format(strtmp, sizeof(strtmp), " Убийство из: %s", GetDeathReason(killerid, reason));//WeaponName(reason));
				SetPlayerCriminal(FBI, killerid, playerid, strtmp);
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [139] [1-5] [playerid/PartOfName]");
			}
			else if(reason == 41 && reason == 42)
			{
				WantedPoints[killerid] += 15;
				new strtmp[64];
				format(strtmp, sizeof(strtmp), " Убийство при превышении пределов необходимой обороны: %s", GetDeathReason(killerid, reason));//WeaponName(reason));
				SetPlayerCriminal(FBI, killerid, playerid, strtmp);
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [139] [4] [playerid/PartOfName]");
			}
			else if(reason == 49) // && GetPlayerState(killerid) == PLAYER_STATE_DRIVER
			{
				WantedPoints[killerid] += 5;
				PlayerInfo[killerid][pAccident] ++;
				SetPlayerCriminal(FBI, killerid, playerid, " Транспортное происшествие, повлекшее смерть человека");//ДТП
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [317] [2-3] [playerid/PartOfName]");
			}
			else if(reason == 50) // && GetPlayerState(killerid) == PLAYER_STATE_DRIVER
			{
				WantedPoints[killerid] += 25;
				new strtmp[30+32+3];
				format(strtmp, sizeof(strtmp), "Убийство транспортом: %s[%d]",
					VehicleArray[nCarModel[killerid]-400][Vehicle_Name], nCarID[killerid]);
				SetPlayerCriminal(FBI, killerid, playerid, strtmp);
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [139] [1-5] [playerid/PartOfName]");
			}
			else if(reason == 60) // && GetPlayerState(killerid) == PLAYER_STATE_DRIVER
			{
				WantedPoints[killerid] += 25;
				new strtmp[30+32+3];
				format(strtmp, sizeof(strtmp), "Уничтожение транспорта: %s[%d]",
					VehicleArray[nCarModel[killerid]-400][Vehicle_Name], nCarID[killerid]);
				SetPlayerCriminal(FBI, killerid, playerid, strtmp);
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [293] [1-2] [playerid/PartOfName]");
			}
		}
    }
    return 1;
}

//КОНВЕРТЕРЫ СООБЩЕНИЙ
stock SetPlayerCriminal(member, playerid, killed, const reason[])//ф-ции начисления вам уровня Розыска, killed=255-неизвестный, reason[]-Преступление:
//stock SetPlayerCriminal(playerid, killed,reason[])
{//example: SetPlayerCriminal(playerid, 255, "Stealing A Police Vehicle");
	if( !IsPlayerConnected(playerid) ) return 1;

	//strmid(reason, reason, 0, 64, 64);//обрезали до 64 символов
	//new strings[MAX_STRING];
	new turned[MAX_PLAYER_NAME];//Подозреваемый MAX_PLAYER_NAME
	new turner[MAX_PLAYER_NAME];//Обвинитель MAX_PLAYER_NAME
	GetPlayerName(playerid, turned, MAX_PLAYER_NAME);//Подозреваемый
    if(	WantedLevel[playerid] == 0 &&
		killed != MAX_PLAYERS-1 && //killed != INVALID_PLAYER_ID &&
		gPlayerSpawned[playerid]) PlayerInfo[playerid][pCrimes] ++;//счётчик преступлений

	if(!IsPlayerConnected(killed) || killed == INVALID_PLAYER_ID || killed == MAX_PLAYERS-1)
	{   //если просто входящее сообщение
		strmid(turner, "Unknown", 0, strlen("Unknown"), 20);//Bх.Cообщение Обвинение: ////Репортёр
		strmid(PlayerCrime[playerid][pVictim], turner, 0, strlen(turner), 20);//Oтправитель Victim - Жертва/Репортёр
		strmid(PlayerCrime[playerid][pAccusing], reason, 0, strlen(reason), 128);//Bх.Cообщение Обвинение: ////Нарушение

	}
	else //if(IsPlayerConnectedEx(killed))// && killed <= numplayers
	{   //если есть отправитель и есть жертва
		strmid(PlayerCrime[playerid][pAccusedof], reason, 0, strlen(reason), 128);//Нарушение
		GetPlayerName(killed, turner, MAX_PLAYER_NAME);
		strmid(PlayerCrime[playerid][pVictim], turner, 0, strlen(turner), 20);//Oтправитель Victim - Жертва/Репортёр
		strmid(PlayerCrime[killed][pBplayer], turned, 0, strlen(turned), 20);//Bиновник/Подозреваемый

	}
//printf("PlayerInZone[playerid]: %d", PlayerInZone[playerid]);//PlayerInZone[playerid]: 999
//ВНИМАНИЕ: пока игрок не заспаунился нельзя взять переменную PlayerInZone[playerid]
	new sZone[40];//17+2+20
	if(PlayerInfo[playerid][pInt] == 0 && PlayerInfo[playerid][pLocal] == FREEROAM)
	{
		for(new j=0; j<MAX_ZONES; j++)
		{
			if(IsPlayerInZone(playerid, j))
			{
				strmid(sZone, zones[j][zone_name], 0, strlen(zones[j][zone_name]), 20);
			}
		}
		//strmid(sZone, zones[PlayerInZone[playerid]][zone_name], 0, strlen(zones[PlayerInZone[playerid]][zone_name]), 20);
		//strmid(sZone, regions[PlayerInRegion][region_name], 0, strlen(regions[PlayerInRegion][region_name]), 20);
	}
	else
	{

		//format(sZone, sizeof(sZone), "Interior - %d", GetPlayerInterior(playerid));
		if(PlayerInfo[playerid][pLocal] < 100)
		{
			new house = PlayerInfo[playerid][pLocal];
			format(sZone, sizeof(sZone), "House %d - %s", house+1, HouseInfo[house][hDiscription]);
		}
		else if(PlayerInfo[playerid][pLocal] >= 100 && PlayerInfo[playerid][pLocal] < 200)
		{
			new bouse = PlayerInfo[playerid][pLocal]-100;
			format(sZone, sizeof(sZone), "Business %d - %s", bouse+1, BizInfo[bouse][bDiscription]);
		}
		else
		{
			if(PlayerInfo[playerid][pLocal] == 201)			sZone = "Hospital LS";
			else if(PlayerInfo[playerid][pLocal] == 202)	sZone = "Hospital SF";
			else if(PlayerInfo[playerid][pLocal] == 203)	sZone = "Hospital LV";

			else if(PlayerInfo[playerid][pLocal] == 211)	sZone = "8ball Track LS";
			else if(PlayerInfo[playerid][pLocal] == 212)	sZone = "BloodBowl SF";
			else if(PlayerInfo[playerid][pLocal] == 213)	sZone = "Dirt Track LV";
			else if(PlayerInfo[playerid][pLocal] == 214)	sZone = "Kickstart LV";//(доступно по понедельникам и средам)

			else if(PlayerInfo[playerid][pLocal] == 241)	sZone = "CityHall";
			else if(PlayerInfo[playerid][pLocal] == 242)	sZone = "Hitman Agency";
			else if(PlayerInfo[playerid][pLocal] == 243)	sZone = "LCN Mansion";
			else if(PlayerInfo[playerid][pLocal] == 244)	sZone = "Yakudza Mansion";
			else if(PlayerInfo[playerid][pLocal] == 245)	sZone = "Cracker House";
			else if(PlayerInfo[playerid][pLocal] == 246)	sZone = "LSPD";
			else if(PlayerInfo[playerid][pLocal] == 247)	sZone = "SFPD";
			else if(PlayerInfo[playerid][pLocal] == 248)	sZone = "LVPD";
			else if(PlayerInfo[playerid][pLocal] == 249)	sZone = "CNNStudio";

			else if(PlayerInfo[playerid][pLocal] == 250)	sZone = "gotoin";
			else if(PlayerInfo[playerid][pLocal] == 251)	sZone = "gotostad";
			else if(PlayerInfo[playerid][pLocal] == 252)	sZone = "gotojet";

			else if(PlayerInfo[playerid][pLocal] == 253)	sZone = "Driving School";
			else if(PlayerInfo[playerid][pLocal] == 254)	sZone = "Motel";

			else sZone = "Unknown Region";
		}

	}
	new strtmp[43+128+20];
	format(strtmp, sizeof(strtmp), "Bы совершили Преступление: %s. Стукач: %s.", reason, turner);
	SendClientMessage(playerid, COLOR_PINK, strtmp);//COLOR_BLUEGREY
	//if(PlayerInfo[playerid][pJailed] == 0) PlayerInfo[playerid][pJailTime] = getdate();

	if(WantedLevel[playerid] == 0)
	{
		LevelToCriminality ++;
		format(strtmp, sizeof(strtmp), "Tекущий Уровень Преступности в штате: %d - %s[%d].", LevelToCriminality, PlayerName(playerid), playerid);
		SendTeamMessage(DoT, COLOR_DARKRED, strtmp);
		SendTeamMessage(FBI, COLOR_DARKRED, strtmp);
		SendTeamMessage(DoJ, COLOR_DARKRED, strtmp);
	}

	new crimeid = 21;
	new yesno;
	if(WantedPoints[playerid] >= 1 && WantedPoints[playerid] <= 6)
	{
		if(WantedLevel[playerid] != 1)
		{
			WantedLevel[playerid] = 1; crimeid = 3; yesno = 1;
			SetPlayerWantedLevel(playerid, 1);
			/*PlayerInfo[playerid][pTeam] = 4;*/
		}
	}
	else if(WantedPoints[playerid] >= 7 && WantedPoints[playerid] <= 10)
	{
		if(WantedLevel[playerid] != 2)
		{
			WantedLevel[playerid] = 2; crimeid = 4; yesno = 1; SetPlayerWantedLevel(playerid, 2); /*PlayerInfo[playerid][pTeam] = 4;*/
		}
	}
	else if(WantedPoints[playerid] >= 11 && WantedPoints[playerid] <= 14)
	{
		if(WantedLevel[playerid] != 3)
		{
			WantedLevel[playerid] = 3; crimeid = 5; yesno = 1; SetPlayerWantedLevel(playerid, 3); /*PlayerInfo[playerid][pTeam] = 4;*/
		}
	}
	else if(WantedPoints[playerid] >= 15 && WantedPoints[playerid] <= 18)
	{
		if(WantedLevel[playerid] != 4)
		{
			WantedLevel[playerid] = 4; crimeid = 6; yesno = 1; SetPlayerWantedLevel(playerid, 4); /*PlayerInfo[playerid][pTeam] = 4;*/
		}
	}
	else if(WantedPoints[playerid] >= 19 && WantedPoints[playerid] <= 22)
	{
		if(WantedLevel[playerid] != 5)
		{
			WantedLevel[playerid] = 5; crimeid = 7; yesno = 1; SetPlayerWantedLevel(playerid, 5); /*PlayerInfo[playerid][pTeam] = 4;*/
		}
	}
	else if(WantedPoints[playerid] >= 23)
	{
		if(WantedLevel[playerid] != 6)
		{
			WantedLevel[playerid] = 6; crimeid = 8; yesno = 1; SetPlayerWantedLevel(playerid, 6); /*PlayerInfo[playerid][pTeam] = 4;*/
		}
	}

	//------------------------------------------------------------------
	new strtmp1[34+40+24], strtmp2[26+128], strtmp3[31+24+3];
	format(strtmp1, sizeof(strtmp1), "***HQ*** Регион: %s. Репортёр: %s", sZone, turner);//Стукач: Reporter:
	format(strtmp2, sizeof(strtmp2), "***HQ*** Преступление: %s", reason);//PlayerName(playerid),
	format(strtmp3, sizeof(strtmp3), "***HQ*** Подозреваемый: %s[%d]", turned, playerid);//PlayerName(playerid),

	if(yesno == 1 && killed != INVALID_PLAYER_ID && killed != MAX_PLAYERS-1)//чтобы не было слишком частых звуковых оповещений
	{   //если произошло изменение уровня розыска и это преступник уже играл, а не просто зашёл на сервер
		/*if(LabelOnHead[playerid]) { UpdateDynamic3DTextLabelText(LabelOnHead[playerid], 0x800000FF, "Преступник"); //DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --; }
		else
		{
			DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			LabelOnHead[playerid] = Create3DTextLabelEx("Преступник", 0x800000FF, 0.0,0.0,0.3,30.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0);
		}*/

#if defined vw_sql//#endif
		if(PlayerInfo[playerid][pArticle] <= 0) CriminalList(playerid, turner, reason, 1);//0 - ничего, 1 - преступление, 2 - арест, 3 - перевод
#endif

		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(PlayerInfo[i][pMember] != member) continue;
			if(gOnDuty[i] == 0) continue;
			//&& gPlayerSpawned[i] == 1 && spectateid[i] == 255
			//strings[0] = EOS;
			SendClientMessage(i, COLOR_LIGHTBLUE, strtmp1);
			SendClientMessage(i, COLOR_LIGHTBLUE, strtmp2);
			SendClientMessage(i, COLOR_LIGHTBLUE, strtmp3);
			if(IsInCopCar(nCarID[i]))
			{
				PlayCrimeReportForPlayer(i, playerid, crimeid);
			}
		}
	}

	//ИНФОРМИРОВАНИЕ
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "SetPlayerCriminal(%d,%d,%s)", Playerid,killed,reason);
	//ABroadCast(COLOR_MAROON, strings, 9);
	CrashDetected[playerid] = 89;
	return 1;//myadd
}
stock ClearCrime(playerid, forplayerid, money=0)//вызывается при конекте, после смерти, по команде /clear
{
	if(IsPlayerConnected(playerid))
	{
		new strtmp[128] = "********************";
		strmid(PlayerCrime[playerid][pAccusedof], strtmp, 0, strlen(strtmp), 128);
		strmid(PlayerCrime[playerid][pVictim], strtmp, 0, strlen(strtmp), 20);
		strmid(PlayerCrime[playerid][pAccusing], strtmp, 0, strlen(strtmp), 128);
		strmid(PlayerCrime[playerid][pBplayer], strtmp, 0, strlen(strtmp), 20);

		if(WantedLevel[playerid] > 0)
		{
			if(LevelToCriminality > 0) LevelToCriminality --;
			format(strings, sizeof(strings), "Tекущий Уровень Преступности: %d - %s[%d].", LevelToCriminality, PlayerName(playerid), playerid);
			SendTeamMessage(DoT, COLOR_HERBAL, strings);
			SendTeamMessage(FBI, COLOR_HERBAL, strings);
		}

		if(forplayerid != MAX_PLAYERS-1)
		{
			format(strtmp, sizeof(strtmp), "%s %s[%d] снял %d[%d] очков розыска c %s'а. Штраф: $%d",
				GetPlayerRanks(forplayerid), PlayerName(forplayerid), forplayerid, WantedPoints[playerid], WantedLevel[playerid], PlayerName(playerid), money);//3600
		}
		else
		{
			format(strtmp, sizeof(strtmp), "CEPBEP снял %d[%d] очков розыска c %s'а. Штраф: $%d",
				WantedPoints[playerid], WantedLevel[playerid], PlayerName(playerid), money);//3600
		}
		Log(CRIMINAL, strtmp);
		//Delete3DTextLabel(LabelOnHead[playerid]); Counter3DText --;
		WantedPoints[playerid] = 0;//убрали очки розыска
		WantedLevel[playerid] = 0;//убрали уровень розыска
		SetPlayerWantedLevel(playerid, 0);//убрали звёзды
		GaiWant[playerid] = 0;//подготовить ГАИ к сканированию
  		GaiRad[playerid] = 0;//подготовить радар к сканированию
  		//ExcessPlayerVelocitiesInTown[playerid] = 0;//убрать превышение в городе
  		ExcessPlayerVelocities[playerid] = 0;//убрать превышение
	}
	//return 1;
}


stock MobileDataComputerOfPlayer(playerid, forplayerid)
{
	new msgitem[41*5+1+128+24+128+24];
	format(msgitem, sizeof(msgitem), "%s{0080FF}Уровень Розыска:\t{FFFFFF}%d\n", msgitem, WantedLevel[forplayerid]);//Bиновник //Имя
	format(msgitem, sizeof(msgitem), "%s{0080FF}Hарушение:\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pAccusedof]);//Преступление
	format(msgitem, sizeof(msgitem), "%s{0080FF}Oтправитель:\t\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pVictim]);//Истец
	format(msgitem, sizeof(msgitem), "%s{0080FF}Bх.Cообщение:\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pAccusing]);//Обвинение: //Сообщенное
	format(msgitem, sizeof(msgitem), "%s{0080FF}Bиновник:\t\t{FFFFFF}%s\n", msgitem, PlayerCrime[forplayerid][pBplayer]);//Bиновник //Пострадавший //Обвиненное
	//format(msgitem, sizeof(msgitem), "%s_____________________________________________________________________\n\0", strings);
	new caption[37+24+3];
	format(caption, sizeof(caption), "Mobile Data Computer: {FFFFFF}%s[%d]", PlayerName(forplayerid), forplayerid);
	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, msgitem, "OK", "");
}

stock MobileDataComputer(playerid)
{
	new searchhit = 0;
	if(!IsACop(playerid))
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Вы не Коп / FBI !");// / National Guard
		ShowMenuForPlayerEx(mPoliceDepartment, playerid);
		return 1;
	}
	TogglePlayerControllableEx(playerid, 1);//освободить
	new bigmsgitem[1692];
	new DialogIDCounter = 0; for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;
    for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(searchhit >= MAX_DLGITEMS) break;
		if( !IsPlayerConnectedEx(i) ) continue;
		if(WantedLevel[i] > 0)
		{   //сканируем всех в розыске
			searchhit ++;
       		DialogID[playerid][DialogIDCounter] = i;//listitem
			format(bigmsgitem, sizeof(bigmsgitem),
				"%s%s[%d] \tУровень Розыска: %d\n", bigmsgitem, PlayerName(i), i, WantedLevel[i]);
				//20+5+1+2+17+1=46+10=56
				//56*30=1680+12=1692
			DialogIDCounter ++;
		}
	}
	if(searchhit < 1) { SendClientMessage(playerid, COLOR_GREY, "   В базе данных нет правонарушений!"); return 1; }
	if(strlen(bigmsgitem) >= sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error: Mobile Data Computer %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Mobile Data Computer пуст");//COLOR_BLUEGREY
		return 1;
	}
	new TextRow[65];
	format(TextRow, sizeof(TextRow), "Mobile Data Computer: %d в розыске", searchhit);
	ShowPlayerDialogEx(playerid, MDC_DIALOG, DIALOG_STYLE_LIST, TextRow,bigmsgitem, "OK", "Cancel");
	return 1;
}
stock MDC_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != MDC_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mPoliceDepartment, playerid);
	 	return 1;
	}
	//new msgitem[256+1];
	new giveplayerid;
//ShowPlayerDialogEx(playerid, MDC_DIALOG, DIALOG_STYLE_LIST, TextRow,listitems, "OK", "Cancel");
	SetPVarInt(playerid, "gShowDialog", -1);
	giveplayerid = DialogID[playerid][listitem];
	MobileDataComputerOfPlayer(playerid, giveplayerid);
	return 1;
}


//stock PlayerLoseWanted5Timer(playerid)//запускается каждые 5 минут из таймера OnFiveMinutsTimer
stock wanted_OnFiveMinutsTimer(playerid)
{   //уменьшение розыска при радиусе больше 80 от силовиков
	if(	WantedLevel[playerid] == 0 &&
		PlayerInfo[playerid][pJailed] == 0 &&
		PlayerInfo[playerid][pTeam] != 4 &&
		(getdate()-PlayerInfo[playerid][pJailTime]) >= 3 &&
		PlayerInfo[playerid][pCrimes] > 0)
	{//ели игрок не в розыске не арестован и с момента последнего преступления прошло больше 3-х суток
		PlayerInfo[playerid][pCrimes] --;//счётчик преступлений
		if(PlayerInfo[playerid][pCrimes] <= 0) PlayerInfo[playerid][pCrimes] = 0;
		format(strings, sizeof(strings), "Tекущий Уровень Преступности: %d", PlayerInfo[playerid][pCrimes]);
		SendClientMessage(playerid, COLOR_BROWNGREEN, strings);
	}

    for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		//сканируем всех силовиков в радиусе 100 м
	    if(IsACop(i) && IsPlayerInRangeOfPlayer(100.0, playerid, i))
		{
			return 1;
		}
	}
	//==========================================================================
	//если ты дальше 100 м от силовиков
	//new strings[MAX_STRING];
	//каждые 5 минут отнимаем по 1 розыска
    new yesno; //new wlevel;
    if(WantedPoints[playerid] > 0)//для того, чтобы нарушитель всегда оставался с 1 уровнем розыска
	{
		WantedPoints[playerid] -= 1;
	    if(WantedPoints[playerid] <= 1)
		{
			if(WantedLevel[playerid] != 0)
			{
				yesno = 1; //wlevel = 0;
				PlayerInfo[playerid][pArticle] = 0;//убрали статью
				PlayerInfo[playerid][pPart] = 0;//убрали часть
				ClearCrime(playerid, MAX_PLAYERS-1, 4);
				TicketMoney[playerid] = 0;
			}
		}
		else if(WantedPoints[playerid] > 1 && WantedPoints[playerid] <= 6)
		{
			if(WantedLevel[playerid] != 1)
			{
				WantedLevel[playerid] = 1; SetPlayerWantedLevel(playerid, 1); yesno = 1; //wlevel = 1;
			}
		}
		else if(WantedPoints[playerid] >= 7 && WantedPoints[playerid] <= 10)
		{
			if(WantedLevel[playerid] != 2)
			{
				WantedLevel[playerid] = 2; SetPlayerWantedLevel(playerid, 2); yesno = 1; //wlevel = 3;
			}
		}
		else if(WantedPoints[playerid] >= 11 && WantedPoints[playerid] <= 14)
		{
			if(WantedLevel[playerid] != 3)
			{
				WantedLevel[playerid] = 3; SetPlayerWantedLevel(playerid, 3); yesno = 1; //wlevel = 5;
			}
		}
		else if(WantedPoints[playerid] >= 15 && WantedPoints[playerid] <= 18)
		{
			if(WantedLevel[playerid] != 4)
			{
				WantedLevel[playerid] = 4; SetPlayerWantedLevel(playerid, 4); yesno = 1; //wlevel = 10;
			}
		}
		else if(WantedPoints[playerid] >= 19 && WantedPoints[playerid] <= 22)
		{
			if(WantedLevel[playerid] != 5)
			{
				WantedLevel[playerid] = 5; SetPlayerWantedLevel(playerid, 5); yesno = 1; //wlevel = 10;
			}
		}
		else if(WantedPoints[playerid] >= 23)
		{
			if(WantedLevel[playerid] != 6)
			{
				WantedLevel[playerid] = 6; SetPlayerWantedLevel(playerid, 6); yesno = 1; //wlevel = 10;
			}
		}
		if(yesno == 1)
		{   //если произошло изменение уровня розыска
			format(strings, sizeof(strings), "Tекущий Уровень Розыска: %d", WantedLevel[playerid]);
			SendClientMessage(playerid, COLOR_BROWNGREEN, strings);
		}
	}
	return 1;
}
