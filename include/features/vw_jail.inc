//##############################################################################//
//                                                                              //
//                               СИСТЕМА АРЕСТА                                 //
//                                                                              //
//##############################################################################//

stock jail_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	if(Current == mPunish)
	{//ShowMenuForPlayerEx(mPunish, playerid);
		new giveplayerid = GetPVarInt(playerid, "PlayerID");
		new giveplayername[MAX_PLAYER_NAME]; GetPVarString(playerid, "playername", giveplayername, MAX_PLAYER_NAME);
		new gMessage[MAX_STRING]; GetPVarString(playerid, "Reason", gMessage, MAX_STRING);

	    new strtmp[90+24+3+24+3];
		format(strtmp, sizeof(strtmp), "CEPBEP: {FFFFFF}%s[%d] {800000}%s {FFFFFF}%s[%d]",
			giveplayername, giveplayerid, gMessage, PlayerName(playerid), playerid);
		//SendAllAdminMessage(COLOR_RED, strtmp, 2);
		SendClientMessageToAll(COLOR_RED, strtmp);

		switch(row)
		{
			case 0://Nothing
			{
				HideMenuForPlayerEx(Current, playerid);
				DestroyMenuEx(Current);
			}
			case 1://Warn
			{
				CMD_warn(playerid, giveplayerid, giveplayername, gMessage);
				HideMenuForPlayerEx(Current, playerid);
				DestroyMenuEx(Current);
			}
			/*case 1://Punish
			{
				OnPlayerAutoInPunish(giveplayerid);
			}
			case 2://Kick
			{
				CMD_kick(playerid, giveplayerid, gMessage);
			}*/
	 	}
	}
}


stock jail_OnPlayerDisconnect(playerid, reason=1)
{
	new strreason[10];
    switch(reason)
    {
        case 0:strcat(strreason, "TimedOut");
        case 1: strcat(strreason, "Leaving");
        case 2: strcat(strreason, "Kicked");
    }

	if(	PlayerInfo[playerid][pJailed] == 10 &&
		(
			PlayerCuffed[playerid] < MAX_PLAYERS-1 ||
			PlayerTied[playerid] == 1 ||
        	FollowBy[playerid] != MAX_PLAYERS-1
		) &&
		//reason == 1 &&
		GameRestart != 1)
	{ //если игрок был зэком и в наручниках, оглушенный или под конвоем вышел из игры, то возвращаем на зону
	    PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pVirtual] = 0;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		PlayerInfo[playerid][pPos_x] = 268.5777;//268.5777,1857.9351,9.8133
		PlayerInfo[playerid][pPos_y] = 1857.9351;
		PlayerInfo[playerid][pPos_z] = 9.8133;
	}
	else if(PlayerInfo[playerid][pJailed] != 10 &&
			(
				PlayerCuffed[playerid] < MAX_PLAYERS-1 ||
				PlayerTied[playerid] == 1 ||
				PlayerTazed[playerid] == 1
			) &&
			WantedLevel[playerid] > 0 &&
			PlayerInfo[playerid][pLevel] > 3 &&
			GameRestart != 1)
	{   //если игрок был в наручниках вышел из игры
		OnPlayerAutoInPunish(playerid);
	}
	
	PlayerCuffed[playerid] = MAX_PLAYERS-1;
	PlayerTied[playerid] = 0;
	PlayerTazed[playerid] = 0;
	if(PlayerTied[playerid] == 5 && GameRestart != 1)
	{   //если игрок был в заложниках LCN
		ResetPlayerWeaponsEx(playerid);
		PlayerInfo[playerid][pJailed] = 5;
		PlayerInfo[playerid][pJailTime] = 20;//1200;
	}
	else if(PlayerTied[playerid] == 6 && GameRestart != 1)
	{   //если игрок был в заложниках Yakuza
		ResetPlayerWeaponsEx(playerid);
		PlayerInfo[playerid][pJailed] = 6;
		PlayerInfo[playerid][pJailTime] = 20;//1200;
	}
	else if(PlayerTied[playerid] == 8 && GameRestart != 1)
	{   //если игрок был в заложниках Hitman
		ResetPlayerWeaponsEx(playerid);
		PlayerInfo[playerid][pJailed] = 8;
		PlayerInfo[playerid][pJailTime] = 20;//1200;
	}
	
	if( LastIssuerid[playerid] != MAX_PLAYERS-1 && LastIssuerid[playerid] != playerid &&
		(reason == 1 || (reason == 2 && gAnticheat[playerid])) &&
		PlayerInfo[playerid][pLevel] > 1
	  )
	{	//наказание варном
		if(	IsPlayerConnected(LastIssuerid[playerid]) &&
			(GetTickCount()-GetPVarInt(playerid, "DamageTime")) <= 10000)
	    {
		    //new strtmp[90+24+3+24+3];
			//format(strtmp, sizeof(strtmp), "CEPBEP: {FFFFFF}%s[%d] {800000}выход из игры в целях спасения от оппонента {FFFFFF}%s[%d]", PlayerName(playerid), playerid, PlayerName(LastIssuerid[playerid]), LastIssuerid[playerid]);
			//SendAllAdminMessage(COLOR_RED, strtmp, 2);

		    SetPVarString(LastIssuerid[playerid], "Reason", "выход из игры в целях спасения жизни");
		    SetPVarInt(LastIssuerid[playerid], "PlayerID", playerid);
		    SetPVarString(LastIssuerid[playerid], "playername", PlayerName(playerid));

			//if( !IsValidMenu(mPunish) )
			//{//Порверяет, создано ли меню с данным ID.
				//DestroyMenuEx(mPunish);
			mPunish = CreateMenuEx(PlayerName(playerid),1,10.0,120.0,100.0,0.0);
		    AddMenuItem(mPunish, 0, "Nothing");
		    AddMenuItem(mPunish, 0, "Warn");
			    //AddMenuItem(mPunish, 0, "Ban");
			    //AddMenuItem(mPunish, 0, "Kick");
		    //}
			ShowMenuForPlayerEx(mPunish, LastIssuerid[playerid]);
		}
	}
	if(	MarkerForPlayer[playerid] != MAX_PLAYERS-1 &&
		(reason == 1 || (reason == 2 && gAnticheat[playerid])) &&
		PlayerInfo[playerid][pLevel] > 1
	  )
	{//если вас кто то ищет
        if(	IsPlayerConnected(MarkerForPlayer[playerid]) &&
         	PlayerInfo[playerid][pVirtual] == 0 &&
         	(WantedPoints[playerid] > 0 || PlayerInfo[playerid][pJailed] == 10) &&
			IsACop(MarkerForPlayer[playerid]) &&
			IsPlayerInRangeOfPlayer(stream_distance, playerid, MarkerForPlayer[playerid]) )
        {   //если ещё в игре
		    SetPVarString(MarkerForPlayer[playerid], "Reason", "выход из игры в целях спасения от копа");
		    SetPVarInt(MarkerForPlayer[playerid], "PlayerID", playerid);
		    SetPVarString(MarkerForPlayer[playerid], "playername", PlayerName(playerid));

			//if( !IsValidMenu(mPunish) )
			//{//Порверяет, создано ли меню с данным ID.
			//DestroyMenuEx(mPunish);
			mPunish = CreateMenuEx(PlayerName(playerid),1,10.0,120.0,100.0,0.0);
		    AddMenuItem(mPunish, 0, "Nothing");
		    AddMenuItem(mPunish, 0, "Warn");
			    //AddMenuItem(mPunish, 0, "Ban");
			    //AddMenuItem(mPunish, 0, "Kick");
			ShowMenuForPlayerEx(mPunish, MarkerForPlayer[playerid]);
		    //}
		}
	}
	//==========================================================================
	if(MarkerForPlayer[playerid] != MAX_PLAYERS-1)
	{//если вас кто то ищет
		//для маркеров и для навигатора вертолёта
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(MarkerToPlayer[i] == MAX_PLAYERS-1) continue;//пропускаем всех кто вообще ни кого не ишит
			if(MarkerToPlayer[i] != playerid) continue;
		    //сканируем всех кто установил маркер на выходящего игрока

			SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
			DisablePlayerCheckpointEx(i);
			CallTimeCounter[i] = 0;
			//if(PlayerInfo[i][pCarTime] > 0) PlayerInfo[i][pCarTime] = 0;
			if(PlayerInfo[i][pCarTime] <= 0)
			{
				gTextDrawHideCarTime[i] = true; OnPlayerTextDrawStateChange(playerid);
			}

			format(strings, sizeof(strings), "Ваша цель: %s[%d] покинула зону досягаемости!! (%s)", PlayerName(playerid), playerid, strreason);
			SendClientMessage(i, COLOR_CERISE, strings);

			//SetPlayerMarkerForPlayerEx(i, MarkerToPlayer[i], COLOR_ALIVE);
			//SetPlayerMarkerForPlayerEx(i, MarkerToPlayer[i], ACTION_COLOR);
			playeridTaxiAccepted[i] = MAX_PLAYERS-1;
			MarkerToPlayer[i] = MAX_PLAYERS-1;
			//GameTextForPlayerEx(i, "~w~Caller~n~~r~Left the game", 5000, 1);
			break;
		}
	}
}



stock OnPlayerAutoInPunish(playerid)//ф-ия автоматической пасадки в КПЗ или на зону
{   //вызывается из OnPlayerDisconnect
	if(PlayerInfo[playerid][pJailed] != 0) return 1;
	if(WantedLevel[playerid] == 0) return 1;
	/*if(PlayerInfo[playerid][pLevel] < 0) {
		SendClientMessageToAll(COLOR_YELLOW, "   На сервер зашёл игрок с нулевым уровнем !");
		//return 1;
	}*/
	if(PlayerInfo[playerid][pArticle] >= 1 && PlayerInfo[playerid][pArticle] <= 36)
	{   //pdd
		for(new i=0; i<sizeof(PDD); i++)
		{
			if(PlayerInfo[playerid][pArticle] != PDD[i][Article]) continue;
			if(PlayerInfo[playerid][pPart] != PDD[i][Part]) continue;

			//new PDDticket = PDD[i][Bail]*PlayerInfo[playerid][pLevel]*360;//3600
			new PDDticket = PDD[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600

			new PDDperiod = PDD[i][Period]*(PlayerInfo[playerid][pLevel]+1);//*4
			if(PDD[i][Jailed] == 1)
			{
				PlayerInfo[playerid][pBank] -= PDDticket;
				break;
			}
			//else if(PDD[i][Jailed] == 2) {	}
			else if(PDD[i][Jailed] == 3 || PDD[i][Jailed] == 4)
			{
				if(PlayerInfo[playerid][pCarLic] == 1) PlayerInfo[playerid][pCarLic] = PDDperiod+10;
			}
			PlayerInfo[playerid][pJailed] = 1;//Садим в ЛС
			PlayerInfo[playerid][pJailTime] = 60;//3600;
			PlayerInfo[playerid][pBank] -= PDDticket;
			//FamilyInfo[DoT][fBank] += PDDticket;
			if(BizInfo[0][bTill]+PDDticket < 2147480000) { BizInfo[0][bTill] += PDDticket; BizInfo[0][bExport] += PDDticket; }
			break;

		}
	}
	else if(PlayerInfo[playerid][pArticle] >= 139)
	{   //pun
		for(new i=0; i<sizeof(PenalCode); i++)
		{
			if(PlayerInfo[playerid][pArticle] != PenalCode[i][Article]) continue;
			if(PlayerInfo[playerid][pPart] != PenalCode[i][Part]) continue;
			if(PenalCode[i][Jailed] == 10)
			{
				PlayerInfo[playerid][pJailed] = 10;//Садим на зону
				PlayerInfo[playerid][pJailTime] = DOTL[ PenalCode[i][Period] ][0] * 60;//минут
				//PlayerInfo[playerid][pJailPrice] = PenalCode[i][Bail]*PlayerInfo[playerid][pLevel]*360;//3600
				PlayerInfo[playerid][pJailPrice] = PenalCode[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600

				if(PlayerInfo[playerid][pSex] == Male) PlayerInfo[playerid][pChar] = 62;//скин зэка
				if(PlayerInfo[playerid][pGunLic] == 1) PlayerInfo[playerid][pGunLic] = DOTL[PenalCode[i][Period]][17]+10;
//format(strings, sizeof(strings), "%s[%d] вышел в наручниках по Cтатье %d.%d с отбыванием на зоне %d часов и залогом $%d",
				//PlayerName(playerid), playerid, PenalCode[i][Article],
				//PenalCode[i][Part], DOTL[PenalCode[i][Period]][17],
				//PlayerInfo[playerid][pJailPrice]);
//SendClientMessage(PlayerCuffed[playerid], COLOR_LIGHTBLUE, strings);
			}
			else
			{
				PlayerInfo[playerid][pJailed] = 2;//Садим в СФ
				PlayerInfo[playerid][pJailTime] = 60;//3600;
				//new PUNticket = PenalCode[i][Bail]*PlayerInfo[playerid][pLevel]*360;//3600
				new PUNticket = PenalCode[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600

				PlayerInfo[playerid][pBank] -= PUNticket;
				if(BizInfo[0][bTill]+PUNticket < 2147480000) { BizInfo[0][bTill] += PUNticket; BizInfo[0][bExport] += PUNticket; }
				//FamilyInfo[FBI][fBank] += PUNticket;
//format(strings, sizeof(strings), "%s[%d] покинул игру при надетых наручниках.", PlayerName(playerid), playerid);
//SendClientMessage(PlayerCuffed[playerid], COLOR_LIGHTBLUE, strings);
			}
			break;
		}
	}
	PlayerInfo[playerid][pArrested] += 1;//добавили к общему кол-во арестов 1
	ResetPlayerWeaponsEx(playerid);//забрали оружие
//SetPlayerToTeamColor(9);
/*
	gOnDuty[giveplayerid] = 0;
	//gJobDuty[giveplayerid] = 0;
	FixJobCounter(giveplayerid);
	PlayerInfo[giveplayerid][pDrugs] = 0;//Наркотики
	PlayerInfo[giveplayerid][pFuel] = 0;//Канистра с топливом.
	//PlayerInfo[giveplayerid][pJailTime] = time;// * 60;
	ClearCrime(giveplayerid);
	PlayerCuffed[giveplayerid] = MAX_PLAYERS-1;
	PlayerCuffedTime[giveplayerid] = 0;
	PlayerTied[giveplayerid] = 0;
	PlayerTiedTime[giveplayerid] = 0;
	TogglePlayerControllableEx(giveplayerid, 1);//оcвободили игрока
*/
	//ClearCrime(playerid, MAX_PLAYERS-1);//не очищаем розыск, чтобы по уровню розыска расчитать залог
	return 1;
}

//stock SetPlayerUnjail(playerid)//вызывается каждую минуту
stock jail_OneMinutsTimer(playerid)//вызывается каждую минуту
{   //для выхода из тюрьмы
	if(gPlayerLogged[playerid] == 0 || gPlayerSpawned[playerid] == 0) { return 1; }
	if(gRealWar)
	{
		//SendClientMessage(playerid, COLOR_GREY, "    Активизирован режим игры RealWar ! Подробнее про этот режим читайте на форуме !");
		return 1;
	}
	//new strings[MAX_STRING];
	if(PlayerInfo[playerid][pJailed] > 0)
    {   //как только появилось у игрока наказание
		CrashDetected[playerid] = 78;

		if(PlayerInfo[playerid][pJailTime] > 0)// && WantLawyerTime[playerid] == 0
		{   //если вам назначено время отсидки и время на решение об отказе от адвоката вышло
			PlayerInfo[playerid][pJailTime] --;//пошел течь срок
		}
		if(PlayerInfo[playerid][pJailTime] <= 0 &&
			(	PlayerInfo[playerid][pJailed] == 5 ||
				PlayerInfo[playerid][pJailed] == 6 ||
				PlayerInfo[playerid][pJailed] == 8) )
		{   //если вы в заложниках
			PlayerInfo[playerid][pJailTime] = 0;
			PlayerInfo[playerid][pJailed] = 0;
			PlayerTied[playerid] = 0;
			GameTextForPlayerEx(playerid, "~g~Untied", 2500, 3);
			return 1;
		}
		if(PlayerInfo[playerid][pJailTime] <= 0)
		{   //если вы отсидели весь срок
		    PlayerInfo[playerid][pJailTime] = 0;
			if(PlayerInfo[playerid][pJailed] == 1)//выход из под ареста
			{   //LS
				SetPlayerInteriorEx(playerid, 6);
				SetPlayerPosEx(playerid, 268.0903,77.6489,1001.0391, 0);//за решёткой
				if(PlayerInfo[playerid][pArticle] >= 139 && LevelToDeliver > 0) LevelToDeliver --;
			}
			else if(PlayerInfo[playerid][pJailed] == 2)//выход из под ареста
			{   //SF
				SetPlayerInteriorEx(playerid, 10);
				SetPlayerPosEx(playerid, 227.2106,114.6068,999.0156, 0);//за решёткой
				if(PlayerInfo[playerid][pArticle] >= 139 && LevelToDeliver > 0) LevelToDeliver --;
			}
			else if(PlayerInfo[playerid][pJailed] == 3)//выход из под ареста
			{   //LV
				SetPlayerInteriorEx(playerid, 3);
				SetPlayerPosEx(playerid, 197.2874,179.4189,1003.0234, 0);//за решёткой
				if(PlayerInfo[playerid][pArticle] >= 139 && LevelToDeliver > 0) LevelToDeliver --;
			}
			else if(PlayerInfo[playerid][pJailed] == 10)//выход из зоны
			{   //если игрок был заключен на зону
				SetPlayerSkinEx(playerid, 239);
				PlayerInfo[playerid][pModel] = 239;
				if(PlayerInfo[playerid][pGunLic] >= 10) PlayerInfo[playerid][pGunLic] = 0;
			    SetPlayerInteriorEx(playerid, 0);
			    SetPlayerPosEx(playerid, 90.2101,1920.4854,17.9422, 0);//за воротами из зоны
			}
		    //SetPlayerWorldBoundsEx(playerid, 20000.0000,-20000.0000,20000.0000,-20000.0000); //Reset world to player
    		SetPlayerWorldBoundsEx(playerid, 4100.0000,-4100.0000,4100.0000,-4100.0000); //Reset world to player
    		SetPVarInt(playerid, "gWorldBounds", 0);
			if(PlayerInfo[playerid][pSex] == Male)
			{
		        if(PlayerInfo[playerid][pMember] == DoT) { PlayerInfo[playerid][pChar] = 280; }
		        else if(PlayerInfo[playerid][pMember] == FBI) { PlayerInfo[playerid][pChar] = 286; }
		        else if(PlayerInfo[playerid][pMember] == DoD) { PlayerInfo[playerid][pChar] = 204; }
		        else if(PlayerInfo[playerid][pMember] == DoH) { PlayerInfo[playerid][pChar] = 71; }
		        else if(PlayerInfo[playerid][pMember] == LCN) { PlayerInfo[playerid][pChar] = 46; }
		        else if(PlayerInfo[playerid][pMember] == Yakuza) { PlayerInfo[playerid][pChar] = 228; }
		        else if(PlayerInfo[playerid][pMember] == DoJ) { PlayerInfo[playerid][pChar] = 147; }
		        else if(PlayerInfo[playerid][pMember] == Hitman) { PlayerInfo[playerid][pChar] = 294; }
		        else if(PlayerInfo[playerid][pMember] == SAN) { PlayerInfo[playerid][pChar] = 187; }
		        else if(PlayerInfo[playerid][pMember] == DoE) { PlayerInfo[playerid][pChar] = 240; }
				else PlayerInfo[playerid][pChar] = 78;//78//бомж//264;//клоун
			}
			PlayerInfo[playerid][pArticle] = 0;//убрали статью
			PlayerInfo[playerid][pPart] = 0;//убрали часть

			SendClientMessage(playerid, COLOR_BLUEGREY, "   Вы оплатили ваш долг перед обществом. Вы свободны.");
			format(strings, sizeof(strings), "~g~Freedom~n~~w~Try to be a better citizen");
			GameTextForPlayerEx(playerid, strings, 5000, 1);

			PlayerInfo[playerid][pJailed] = 0;//игрок не в тюрьме
			PlayerInfo[playerid][pJailTime] = getdate();//перезаписали дату последнего преступления
			//при условии что PlayerInfo[playerid][pJailed] = 0;
			ClearCrime(playerid, MAX_PLAYERS-1, 0);
		}
		CrashDetected[playerid] = 79;
	}
	return 1;
}


//stock InWantedOnPlayerDeath(playerid, killerid, reason)
stock InWantedOnPlayerDeath(playerid)
{   //вызывается из OnPlayerDeath для всех случаев смерти игрока
	if(gRealWar) return 1;

	if( (IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD || PlayerInfo[playerid][pMember] == DoJ)
		&& gOnDuty[playerid]) return 1;
	CrashDetected[playerid] = 92;
	//#pragma unused killerid
	//#pragma unused reason
	//----------------------------------------------------------------------
	//new strings[MAX_STRING];
	if(WantedLevel[playerid] >= 1)
	{   //если игрок умер при розыске

		for(new j=0; j<MAX_TURFS; j++)
		{   //сканируем все зоны
			if(!IsAGangs(playerid)) continue;//SendClientMessage(playerid, COLOR_GREY, "   Игрок не в банде !");
			if(!IsPlayerInRegion(playerid, j) || gPlayerSpawned[playerid] == 0) continue; //если игрок находится в какой то зоне j
			//Вы не можете связывать на чужой зоне или
			if(taketurfbackcount[j] != 0 && TurfInfo[j][zFlash] == 1)
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Вы Не можете связывать, т.к. эта зона атакована !");
				return 1;
		    }
	        /*if(	PlayerInfo[playerid][pMember] != TurfInfo[j][zFamily] &&
	 			PlayerInfo[giveplayerid][pMember] == TurfInfo[j][zFamily])
	        {	//если эта зона не принадлежит банде в которой находится playerid
				//SendClientMessage(playerid, COLOR_GREY, "   Вы Не можете связать, т.к. этот игрок на своей зоне !");
			    return 1;
			}*/
        }

	    //new price = WantedLevel[playerid] * 4000;//4000-40000$
		new copid = -1;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1 ) continue;
		    if( !(IsACop(i) && gOnDuty[i]) ) continue;
		    if( IsInCopCar(nCarID[i]) ) continue;
			if(PlayerInfo[playerid][pJailed] >= 1 && PlayerInfo[playerid][pJailed] <= 3) continue;
			if(PlayerInfo[playerid][pJailed] == 10) continue;
			//if(	!IsPlayerInRangeOfPlayer(30.0, playerid, i) ) continue;
			new Float:distance = GetDistanceBetweenPlayers(playerid, i);
			if(distance < 15.0 || distance > 55.0) continue;
			//находим всех кто больше 15-30 метров
		    //если коп в 30 м от преступника
			copid = i;
			GameTextForPlayerEx(i, "~w~Running Suspect ~r~Killed", 5000, 1);
			//вывести сообщение копу что преступник в радиусе 30 м убит
			PlaySoundForPlayer(i, SOUND_PART_MISSION_COMPLETE);//Звук окончание миссии - 1058
			break;
		}
		if(copid != -1)
		{
			PlayerInfo[playerid][pWantedDeaths] += 1;
			if(PlayerInfo[playerid][pArticle] != 0 && FollowBy[playerid] == MAX_PLAYERS-1)
			{//если игрок в розыске и
				//OnPlayerAutoInJail(copid, playerid);
				OnPlayerArrestKill(copid, playerid);
			}
			else
			{
				new diecash = 50*WantedPoints[playerid];//500 для экономики
		    	GivePlayerMoneyH(ftax, playerid, -diecash);
				//new family = PlayerInfo[copid][pMember];
				//FamilyInfo[family][fBank] += diecash;
				if(BizInfo[0][bTill]+diecash < 2147480000) { BizInfo[0][bTill] += diecash; BizInfo[0][bExport] += diecash; }

		    	format(strings, sizeof(strings), "* Bы оплатили %d штрафных очка(ов) в размере $%d.", WantedPoints[playerid], diecash );
		    	SendClientMessage(playerid, COLOR_BLUEGREY, strings);

				PlayerInfo[playerid][pJailed] = 3;
			    PlayerInfo[playerid][pJailTime] = WantedLevel[playerid]*5;//6*5=30 минут максимум
			    format(strings, sizeof(strings), "* Вы - в Тюрьме на %d минут за сопротивление при задержании.", PlayerInfo[playerid][pJailTime]);//, price
			    SendClientMessage(playerid, COLOR_BLUEGREY, strings);// и потеряли %d$.  При побеге можете быть застрелены Офицером.

				//PlayerInfo[playerid][pArticle] = 0;//НЕ убирать статью
				//PlayerInfo[playerid][pPart] = 0;//убрали часть
				//ClearCrime(playerid, MAX_PLAYERS-1, diecash);//не очищаем розыск, чтобы по уровню розыска расчитать залог
				//LevelToCriminality --;//ClearCrime снижает уровень преступности
			}
		}
	}
	CrashDetected[playerid] = 93;
	return 1;
}


stock OnPlayerPunishment(playerid, killerid, reason)
{//вызываетс из AntiDM_OnPlayerDeath
	if(killerid == INVALID_PLAYER_ID) return 1;
	if( IsFireArm(reason) )
	{
		PlayerInfo[killerid][pKills] -= 1;
		PlayerInfo[killerid][pDeaths] += 1;
	}
	if(reason == 22 && 1 <= PlayerInfo[killerid][pGun22Skill] < 999) { PlayerInfo[killerid][pGun22Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun22Skill]); }//PISTOL
	else if(reason == 23 && 1 <= PlayerInfo[killerid][pGun23Skill] < 999) { PlayerInfo[killerid][pGun23Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun23Skill]); }//PISTOL_SILENCED
	else if(reason == 24 && 1 <= PlayerInfo[killerid][pGun24Skill] < 999) { PlayerInfo[killerid][pGun24Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun24Skill]); }//DESERT_EAGLE
	else if(reason == 25 && 1 <= PlayerInfo[killerid][pGun25Skill] < 999) { PlayerInfo[killerid][pGun25Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun25Skill]); }//SHOTGUN
	else if(reason == 26 && 1 <= PlayerInfo[killerid][pGun26Skill] < 999) { PlayerInfo[killerid][pGun26Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun26Skill]); }//SAWNOFF_SHOTGUN
	else if(reason == 27 && 1 <= PlayerInfo[killerid][pGun27Skill] < 999) { PlayerInfo[killerid][pGun27Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun27Skill]); }//SPAS12_SHOTGUN
	else if((reason == 28 || reason == 32) &&
		1 <= PlayerInfo[killerid][pGun28Skill] < 999)
	{
		PlayerInfo[killerid][pGun28Skill] --;
		SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun28Skill]);
	}//MICRO_UZI
	else if(reason == 29 && 1 <= PlayerInfo[killerid][pGun29Skill] < 999) { PlayerInfo[killerid][pGun29Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun29Skill]); }//MP5
	else if(reason == 30 && 1 <= PlayerInfo[killerid][pGun30Skill] < 999) { PlayerInfo[killerid][pGun30Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun30Skill]); }//AK47
	else if(reason == 31 && 1 <= PlayerInfo[killerid][pGun31Skill] < 999) { PlayerInfo[killerid][pGun31Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun31Skill]); }//M4
	else if(reason == 34 && 1 <= PlayerInfo[killerid][pGun34Skill] < 999) { PlayerInfo[killerid][pGun34Skill] --; SetPlayerGunSkillEx(killerid, reason, PlayerInfo[killerid][pGun34Skill]); }//SNIPERRIFLE

	if(PlayerInfo[playerid][pLevel] > 1 && PlayerInfo[killerid][pLevel] > 1)
	{
		new money = PlayerInfo[killerid][pCash] +
					PlayerInfo[killerid][pBank] +
					PlayerInfo[killerid][pDeposit];
		new percent;
		if(money < 100000) percent = floatround( 0.01 * money / 100.0);
		else if(money >= 100000 && money < 1000000) percent = floatround( 0.1 * money / 100.0);
		else if(money >= 1000000 && money < 2000000) percent = floatround( 0.2 * money / 100.0);
		else if(money >= 2000000 && money < 3000000) percent = floatround( 0.3 * money / 100.0);
		else if(money >= 3000000 && money < 5000000) percent = floatround( 0.5 * money / 100.0);
		else if(money >= 5000000 && money < 10000000) percent = floatround( 1.0 * money / 100.0);
		else percent = floatround( 2.0 * money / 100.0 );
		GivePlayerMoneyB(fpunish, killerid, -percent);
	    if(BizInfo[0][bTill]+percent < 2147480000) { BizInfo[0][bTill] += percent; BizInfo[0][bExport] += percent; }

	    SendClientMessage(killerid, COLOR_GREY, "   Вы были наказаны !");
	}
	return 1;
}


stock jail_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
	if(	!(IsACop(playerid) && gOnDuty[playerid]) &&
		weaponid >= 0 && weaponid <= 15 &&
		GetPVarInt(playerid, "Tazer") == 0 &&
		PlayerInfo[playerid][pJailed] == 0)//&& !IsACop(playerid)
	{   //если игрок(не коп) ударил игрока ближним оружием на глазах копа в 60 метрах, тазер не актвирован, игрок не арестован
		new found = -1;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1) continue;
		    if(!IsACop(i)) continue;
		    if(!gOnDuty[i]) continue;
			if(	!IsPlayerInRangeOfPlayer(60.0, playerid, i) ) continue;
      	    found = i;
      	    break;
	 	}
		if(found != -1)
		{//1-6 - малое, 7-14 - среднее, 15-25 - тяжкое
			//if(WantedPoints[playerid] > 15)
			if(amount >= 50.0)
			{
				WantedPoints[playerid] += 5;
				SetPlayerCriminal(FBI, playerid, damagedid, "Причинение тяжкого повреждения");
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [150] [1-2] [playerid/PartOfName]");
			}
			else if(amount >= 1.0 && amount < 50.0)
			{
				WantedPoints[playerid] += 1;
				SetPlayerCriminal(FBI, playerid, damagedid, "Причинение менее тяжкого повреждения");
				SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [149] [1-2] [playerid/PartOfName]");
			}
		}
	}
}

stock jail_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	//--------------------------------------------------------------------------
	if( IsPlayerInRangeOfPoint(playerid, 2.1, 275.0578,1872.7856,8.7649) )
	{   //для выхода под залог на маркере
	    if(PlayerInfo[playerid][pJailPrice] <= 0)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Выход под залог - невозможен !");
			return 1;
		}
        if(GetPlayerMoneyH(playerid) < PlayerInfo[playerid][pJailPrice] &&
			PlayerInfo[playerid][pBank] < PlayerInfo[playerid][pJailPrice])
        {
			format(strings, sizeof(strings), "   Вы НЕ можете позволить себе оплатить залог $%d!", PlayerInfo[playerid][pJailPrice]);
			SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
        }
		new found;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(PlayerInfo[i][pJob] == LAWYER)
			{
	            found ++;
			}
		}
       	if(found)
		{
			SendClientMessage(playerid, COLOR_GREY, "  Выход под залог возможен только при отсутствии адвокатов (USE: /lawyers)!");
			return 1;
		}
		new ToBase[74+24+2];
		format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), DoD);
		mysql_query(ToBase); mysql_store_result();
		if(mysql_num_rows() > 0)
	 	{
			mysql_free_result();
       		SendClientMessage(playerid, COLOR_GREY, "   Выход под залог не возможен находясь в Чёрном Списке!");
			return 1;
		}
		mysql_free_result();

        Offer[playerid] = playerid;
        MenuOperation[playerid] = 21;

        new msgitem[239];//26+37+41+50+31 + 24+10+10+10
	   	format(msgitem, sizeof(msgitem), "\t\t%s \nк вам адвокат\n\
Сумма ваше залога составляет $%d.\n\
Плата за предоставления адвоката $%d.\n\
Оставшее время заключения составляет %d минут.\n\
\nВы согласны выйти под залог?",
			PlayerName(playerid),
			PlayerInfo[playerid][pJailPrice],
			DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*8,
			PlayerInfo[playerid][pJailTime]);
		ShowPlayerDialogGap(playerid, ACCEPT_DIALOG, DIALOG_STYLE_MSGBOX, "Want Lawyer", msgitem, "YES", "NO");

	}
	return 1;
}

