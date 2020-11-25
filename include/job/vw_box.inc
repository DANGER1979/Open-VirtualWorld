


stock LoadBoxer()//для боксёров
{
	new time = GetTickCount();
	new File: bFile = fopen("Logs/boxer.ini", io_read);//io_readwrite
	if(bFile)
	{
		new strFromFile[3+40+3 + 12];
		fread(bFile, strFromFile);

		new arrCoords[3][40];
		split(strFromFile, arrCoords, ',');
		Champion[TitelWins] = strval(arrCoords[0]);
		strmid(Champion[TitelName], arrCoords[1], 0, strlen(arrCoords[1]), 40);
		Champion[TitelLoses] = strval(arrCoords[2]);
		fclose(bFile);
	}
	printf("14/19. [Загрузка чемпионов]: Было загружено - %d, потрачено - %d (ms)", 1, (GetTickCount()-time));
}
stock SaveBoxer()
{//вызывается из OnPlayerDeath
	new coordsstring[3+40+3 + 12];
	format(coordsstring, sizeof(coordsstring), "%d,%s,%d", Champion[TitelWins],Champion[TitelName],Champion[TitelLoses]);
	new File: bfile = fopen("Logs/boxer.ini", io_write);
	fwrite(bfile, coordsstring);
	fclose(bfile);
	printf("Сохранение чемпионов успешно завершено");
}


//для боксёров
stock GetBoxerRanks(playerid, &points)
{   //вызывается при ACCEPT secundans, /boxstats
	new BoxTitle[20];
    new level = PlayerInfo[playerid][pWins]-PlayerInfo[playerid][pLoses];
	if(level > 10 && PlayerInfo[playerid][pLoses] == 0)
	{
		points = 100; BoxTitle = "Непобедимый";
		SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_ELBOW);
	}
	else
	{
		if(level < 5) { points = 0; BoxTitle = "Отчаянный"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_NORMAL); }//Desperado
		else if(level >= 5 && level < 10) { points = 10; BoxTitle = "Голодный"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_NORMAL); }//Щелкунчик
		else if(level >= 10 && level < 15) { points = 15; BoxTitle = "Безумец"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_NORMAL); }//Головорез
		else if(level >= 15 && level < 20) { points = 20; BoxTitle = "Стойкий"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_NORMAL); }//Воин
		else if(level >= 20 && level < 25) { points = 25; BoxTitle = "Крепкий Орешек"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_BOXING); }
		else if(level >= 25 && level < 30) { points = 30; BoxTitle = "Ошеломляющий"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_BOXING); }
		else if(level >= 30 && level < 35) { points = 35; BoxTitle = "Пронизывающий"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_BOXING); }
		else if(level >= 35 && level < 40) { points = 40; BoxTitle = "Усмиряющий"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_BOXING); }
		else if(level >= 40 && level < 45) { points = 45; BoxTitle = "Кулак Возмездия"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_KUNGFU); }
		else if(level >= 45 && level < 50) { points = 50; BoxTitle = "Неуловимый"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_KUNGFU); }
		else if(level >= 50 && level < 55) { points = 55; BoxTitle = "Благословлённый"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_KUNGFU); }
		else if(level >= 55 && level < 60) { points = 60; BoxTitle = "Непробиваемый"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_KUNGFU); }
		else if(level >= 60 && level < 65) { points = 68; BoxTitle = "Сокрушитель Черепов"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_GRABKICK); }
		else if(level >= 65 && level < 70) { points = 70; BoxTitle = "Головорез"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_GRABKICK); }
		else if(level >= 70 && level < 75) { points = 75; BoxTitle = "Несокрушимый"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_GRABKICK); }
		else if(level >= 75) { points = 80; BoxTitle = "ХренПопадёшь"; SetPlayerFightingStyleEx(playerid, FIGHT_STYLE_KNEEHEAD); }
    }
	return BoxTitle;
}

stock box_OnPlayerRequestClass(playerid)
{
//==============================================================================
	//для боксёров начало STEP7
	if(gPlayerBoxing[playerid] == 1)
	{   //если раунд начался и игрок участник боя умер и спаунится
		if(RoundStarted > 0 && RoundCounter > 0)
		{
	       	RoundCounter ++;
	        if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,764.9067,6.4177,1000.7171))
	        {	//проверяем где стоит букмекер
	            //SendClientMessage(playerid, COLOR_GREY, "   Вы не в Зале Ganton Gym на Grove Street (LS)!");
				if(BoxerBlue == playerid)
				{
					PlayerInfo[playerid][pInt] = 5;
					PlayerInfo[playerid][pVirtual] = 63;//"Ganton Gym"
					PlayerInfo[playerid][pLocal] = 163;
					SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], 81,
						762.9852,2.4439,1001.6942, 131.8632,-1, -1, -1, -1, -1, -1);
				}
				else if(BoxerRed == playerid)
				{
					PlayerInfo[playerid][pInt] = 5;
					PlayerInfo[playerid][pVirtual] = 63;
					PlayerInfo[playerid][pLocal] = 163;
					SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], 80,
							758.7064,-1.8038,1001.6942, 313.1165,-1, -1, -1, -1, -1, -1);
				}
	        }
	        else if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,766.7358,-68.5967,1001.5692))
	        {
	            //SendClientMessage(playerid, COLOR_GREY, "   Вы не в Зале Below the Belt Gym на Redsands_East2 (LV)!");
				if(BoxerBlue == playerid)
				{
					PlayerInfo[playerid][pInt] = 7;
					PlayerInfo[playerid][pVirtual] = 65;
					PlayerInfo[playerid][pLocal] = 165;
					SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], 81,
						764.4096,-66.4512,1001.6692, 225.7098,-1, -1, -1, -1, -1, -1);
				}
				else if(BoxerRed == playerid)
				{
					PlayerInfo[playerid][pInt] = 7;
					PlayerInfo[playerid][pVirtual] = 65;
					PlayerInfo[playerid][pLocal] = 165;
					SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], 80,
							768.9097,-70.9200,1001.6692, 45.3064,-1, -1, -1, -1, -1, -1);
				}
	        }
	        /*else if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,766.7358,-68.5967,1001.5692))
	        {
	            //SendClientMessage(playerid, COLOR_GREY, "   Вы не в Зале Marital Arts Gym на ... (SF)!");
				if(BoxerBlue == playerid)
				{
					PlayerInfo[playerid][pInt] = 6;
					PlayerInfo[playerid][pVirtual] = 64;
					PlayerInfo[playerid][pLocal] = 164;
					SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], 81,
						764.4096,-66.4512,1001.5692, 225.7098,-1, -1, -1, -1, -1, -1);
				}
				else if(BoxerRed == playerid)
				{
					PlayerInfo[playerid][pInt] = 6;
					PlayerInfo[playerid][pVirtual] = 64;
					PlayerInfo[playerid][pLocal] = 164;
					SetSpawnInfoEx(playerid, PlayerInfo[playerid][pTeam], 80,
							768.9097,-70.9200,1001.5692, 45.3064,-1, -1, -1, -1, -1, -1);
				}
	        }*/

	        //new strings[MAX_STRING];
			format(strings, sizeof(strings), "~r~Round ~w~%d", RoundCounter);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(gPlayerLogged[i] == 0) continue;
		        //if(IsPlayerInRangeOfPoint(i, 15.0, 764.9067,6.4177,1000.7171))
		        //if(IsPlayerInRangeOfPoint(i, 15.0, 768.9097,-70.9200,1001.5692))
				if(IsPlayerInRangeOfPlayer(15.0, i, Offer[playerid]))
		        {
					GameTextForPlayerEx(i, strings, 5000, 4);
		        	//GameTextForAll(strings, 5000, 4);
				}
			}
		}
/*
		//ИНФОРМИРОВАНИЕ
		//new strtmp[MAX_STRING];
		format(strtmp, sizeof(strtmp), "RoundStarted:%d gPlayerBoxing:%d RoundCounter:%d BoxerBlue:%d BoxerRed:%d",
			RoundStarted, gPlayerBoxing[playerid], RoundCounter, BoxerBlue, BoxerRed);
		ABroadCast(COLOR_MAROON, strtmp, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strtmp);
*/
       	return 1;
	}
	//для боксёров начало STEP9
	else if(gPlayerBoxing[playerid] == 2)
	{   //если раунд начался и игрок участник боя умер и спаунится
		//снятие с ринга
	   	new Float:plocx, Float:plocy, Float:plocz;
		GetPlayerPos(Offer[playerid], plocx, plocy, plocz);

		PlayerInfo[playerid][pInt] = PlayerInfo[Offer[playerid]][pInt];
		PlayerInfo[playerid][pVirtual] = PlayerInfo[Offer[playerid]][pVirtual];
		PlayerInfo[playerid][pLocal] = PlayerInfo[Offer[playerid]][pLocal];
		SetSpawnInfoEx(playerid,
			PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],
			plocx-1.0, plocy-1.0, plocz, 0.0, -1, -1, -1, -1, -1, -1);

		gPlayerBoxing[playerid] = 0;
		Offer[playerid] = MAX_PLAYERS-1;
		return 1;
	}//для боксёров конец
	return 0;
}

stock box_OnPlayerSpawn(playerid)
{
	new points;
	GetBoxerRanks(playerid, points);//для установки стиля боя
}

stock box_OnPlayerConnect(playerid)
{
 //для боксёров
	BoxWaitTime[playerid] = 0; gPlayerBoxing[playerid] = 0; //Offer[playerid] = MAX_PLAYERS-1;
	Rates[playerid][0] = 0; Rates[playerid][1] = 0;

}

stock box_OnPlayerDisconnect(playerid)
{
	//для боксёров
	if(gPlayerBoxing[playerid] == 1)
	{   //если вышел участник боя
		BoxWaitTime[BoxerBlue] = 0;
		BoxWaitTime[BoxerRed] = 0;
		gPlayerBoxing[BoxerBlue] = 0;
		gPlayerBoxing[BoxerRed] = 0;
		Offer[BoxerBlue] = MAX_PLAYERS-1;
		Offer[BoxerRed] = MAX_PLAYERS-1;
		RoundCounter = 0;
		RoundStarted = 0;
		BoxerBlue = MAX_PLAYERS-1;
		BoxerRed = MAX_PLAYERS-1;
		DeathCounter1 = 0;
		DeathCounter2 = 0;
		TotalRates = 0;
		TotalRateBlue = 0;
		TotalRateRed = 0;
		if(GameRestart != 1) GameTextForAll("~g~Match Over", 5000, 1);
	}
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
 	//если вышел секундандт
		if( IsPlayerConnectedEx(i) ) continue;
		if( Offer[i] != playerid) continue;
		//сканируем всех у кого этот игрок секундант
		BoxWaitTime[BoxerBlue] = 0;
		BoxWaitTime[BoxerRed] = 0;
		gPlayerBoxing[BoxerBlue] = 0;
		gPlayerBoxing[BoxerRed] = 0;
		Offer[BoxerBlue] = MAX_PLAYERS-1;
		Offer[BoxerRed] = MAX_PLAYERS-1;
		RoundCounter = 0;
		RoundStarted = 0;
		BoxerBlue = MAX_PLAYERS-1;
		BoxerRed = MAX_PLAYERS-1;
		DeathCounter1 = 0;
		DeathCounter2 = 0;
		TotalRates = 0;
		TotalRateBlue = 0;
		TotalRateRed = 0;
		if(GameRestart != 1) GameTextForAll("~g~Match Over", 5000, 1);
		break;
	}
}


//для боксёров начало STEP6
stock box_OnPlayerDeath(playerid, killerid)
{   //срабатывает при убийстве из OnPlayerDeath
//НЕДОРАБОТКА: не учтено если игрок не с ринга убьёт боксёра, запрыгнув на ринг
	if( gRealWar ) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;
	//new strings[MAX_STRING];
	//для отсчёта времени при старте
	//--------------------------------------------------------------------------
	if(RoundStarted <= 0) return 1;//если бой не начался
    if(!gPlayerBoxing[killerid])  return 1; //если убийца находится не в схватке
	if(DeathCounter1 < 3 && DeathCounter2 < 3) return 1;	//если оба из участников поединка ещё не достигли 3 смерти то выйти
	//--------------------------------------------------------------------------
    if(!strcmp(PlayerName(killerid), Champion[TitelName], true))
	{
		Champion[TitelWins] = PlayerInfo[killerid][pWins];
        Champion[TitelLoses] = PlayerInfo[killerid][pLoses];
        //GivePlayerMoneyB(1, killerid, 20000);
		SaveBoxer();
	    format(strings, sizeof(strings), "Bookmaker %s: Чемпион {FFFFFF}%s{FF9900} одержал очередную победу против {FFFFFF}%s{FF9900} в %d раунде.",
			PlayerName(Offer[killerid]), PlayerName(killerid), PlayerName(playerid), RoundCounter);
		OOCNews(COLOR_LIGHTORANGE,strings);//OOC(COLOR_BROWN,strings);
	}
    else if(!strcmp(PlayerName(playerid), Champion[TitelName], true))
	{   //если имя побеждённого равно имени чимпиона
		strmid(Champion[TitelName], PlayerName(killerid), 0, strlen(PlayerName(killerid)), 24);
		Champion[TitelWins] = PlayerInfo[killerid][pWins];
		Champion[TitelLoses] = PlayerInfo[killerid][pLoses];
		//GivePlayerMoneyB(1, killerid, 10000);
		//GivePlayerMoneyB(1, playerid, -10000);
		SaveBoxer();
      	format(strings, sizeof(strings), "Bookmaker %s: {FFFFFF}%s{FF9900} одержал победу против Чемпиона {FFFFFF}%s{FF9900} в %d раунде и теперь он новый Чемпион.",
			PlayerName(Offer[killerid]), PlayerName(killerid), PlayerName(playerid), RoundCounter);
		OOCNews(COLOR_LIGHTORANGE,strings);//(COLOR_BROWN,strings);
	}
    else if( (PlayerInfo[killerid][pWins]-PlayerInfo[killerid][pLoses]) > (Champion[TitelWins]-Champion[TitelLoses])  )
    {   //если имя побеждённого равно имени чимпиона
        //или кол-во побед и поражений ваших больше чем у чемпиона
		strmid(Champion[TitelName], PlayerName(killerid), 0, strlen(PlayerName(killerid)), 24);
		Champion[TitelWins] = PlayerInfo[killerid][pWins];
		Champion[TitelLoses] = PlayerInfo[killerid][pLoses];
		GivePlayerMoneyB(fbox, killerid, 10000);
		//GivePlayerMoneyB(1, playerid, -10000);
		SaveBoxer();
       	format(strings, sizeof(strings), "Bookmaker %s: {FFFFFF}%s{FF9900} одержал победу против {FFFFFF}%s{FF9900} в %d раунде и теперь он новый Чемпион. Гонорар $10000.",
			PlayerName(Offer[killerid]), PlayerName(killerid), PlayerName(playerid), RoundCounter);
		OOCNews(COLOR_LIGHTORANGE,strings);//(COLOR_BROWN,strings);
	}
	else
	{
	    format(strings, sizeof(strings), "Bookmaker %s: {FFFFFF}%s{FF9900} одержал победу против {FFFFFF}%s{FF9900} в %d раунде.",  PlayerName(Offer[killerid]), PlayerName(killerid), PlayerName(playerid), RoundCounter);
		OOCNews(COLOR_LIGHTORANGE,strings);//OOC(COLOR_BROWN,strings);
	}
	PlayerInfo[killerid][pWins] += 1;
	PlayerInfo[playerid][pLoses] += 1;
	new boxerfee;
	new level = PlayerInfo[killerid][pWins]-PlayerInfo[killerid][pLoses];
	if(level == 10) { boxerfee = 100 + random(100); }//Щелкунчик
	else if(level == 20) { boxerfee = 200 + random(200); }
	else if(level == 30) { boxerfee = 300 + random(300); }
	else if(level == 40) { boxerfee = 400 + random(400); }
	else if(level == 50) { boxerfee = 500 + random(500); }
	else if(level == 60) { boxerfee = 600 + random(600); }
	else if(level == 70) { boxerfee = 700 + random(700); }
	else if(level == 80) { boxerfee = 800 + random(800); }
	else if(level == 90) { boxerfee = 900 + random(900); }
	else if(level == 100) { boxerfee = 1000 + random(1000); }
	else if(level == 110) { boxerfee = 1100 + random(1100); }
	else if(level == 120) { boxerfee = 1200 + random(1200); }
	else if(level >= 130 && level < 140) { boxerfee = 1300 + random(1300); }
	else if(level >= 140 && level < 150) { boxerfee = 1400 + random(1400); }
	else if(level >= 150) { boxerfee = 1500 + random(1500); }
	GivePlayerMoneyB(fbox, killerid, boxerfee);

	format(strings, sizeof(strings), "* Вы Проиграли в Бою против %s.", PlayerName(killerid));
	SendClientMessage(playerid, COLOR_YELLOW, strings);
	//GameTextForPlayerEx(playerid, "~r~You lost", 3500, 1);
	format(strings, sizeof(strings), "* Вы Победили в Бою против %s.", PlayerName(playerid));
	SendClientMessage(killerid, COLOR_YELLOW, strings);

	//GameTextForPlayerEx(killerid, "~r~You won", 3500, 1);
	//==========================================================================
	PlayerInfo[Offer[killerid]][pBookmakerSkill] ++;
	level = PlayerInfo[Offer[killerid]][pBookmakerSkill];
	if(level == 50)	{ SendClientMessage(Offer[killerid], COLOR_GREEN, "* Ваш Навык Букмекера теперь Уровня 2."); }
	else if(level == 100) { SendClientMessage(Offer[killerid], COLOR_YELLOW, "* Ваш Навык Букмекера теперь Уровня 3."); }
	else if(level == 200) { SendClientMessage(Offer[killerid], COLOR_YELLOW, "* Ваш Навык Букмекера теперь Уровня 4."); }
	else if(level == 400) { SendClientMessage(Offer[killerid], COLOR_YELLOW, "* Ваш Навык Букмекера теперь Уровня 5."); }
	new percent;
	if(level < 50) { percent = 1; }
	else if(level >= 50 && level < 100) { percent = 2; }
	else if(level >= 100 && level < 200) { percent = 3; }
	else if(level >= 200 && level < 400) { percent = 4; }
	else if(level >= 400) { percent = 5; }
	//--------------------------------------------------------------
	//расчёт гонораров
	new Float: ProbabilityLose = 1.0;
	/*if(PlayerInfo[killerid][pWins] > 0 || PlayerInfo[killerid][pLoses] > 0)
	{
		if(PlayerInfo[killerid][pWins] > PlayerInfo[killerid][pLoses]) {
			ProbabilityLose = float(PlayerInfo[killerid][pWins])/float(PlayerInfo[killerid][pWins]+PlayerInfo[killerid][pLoses]); }
		else {
			ProbabilityLose = float(PlayerInfo[killerid][pLoses])/float(PlayerInfo[killerid][pWins]+PlayerInfo[killerid][pLoses]));
	}*/
		//1-4/(1+4+0)=0.2
		//1-1/(1+1+0)=0.5
		//определяет вероятность проигрыша, чем ближе к еденице тем больше вероятность проигрыша
		//т.е. получит больше денег тот кто поставит на слабого
	//new Float: FactorBlue = float(TotalRateBlue)/float(TotalRates);//15418/(1+4200)=3.670078
	//new Float: FactorRed = float(TotalRateRed)/float(TotalRates);//15418/(1+11218)=1.374275
	//определяем процент ставки к общей сумме ставки на этого боксёра
	//--------------------------------------------------------------
	if(TotalRates > 0)
	{
		PlayerInfo[killerid][pRespect] ++;
		PlayerInfo[Offer[killerid]][pRespect] ++;

		//ИНФОРМИРОВАНИЕ
		//format(strings, sizeof(strings), "TotalRates: $%d, TotalRateBlue: $%d, TotalRateRed: $%d, FactorBlue: %.2f, FactorRed: %.2f, ProbabilityLose: %.2f", TotalRates, TotalRateBlue, TotalRateRed, FactorBlue, FactorRed, ProbabilityLose);
		format(strings, sizeof(strings), "TotalRates: $%d, TotalRateBlue: $%d, TotalRateRed: $%d, ProbabilityLose: %.2f", TotalRates, TotalRateBlue, TotalRateRed, ProbabilityLose);
		//ABroadCast(COLOR_MAROON, strings, 5);
		Log(RATE,strings);

		GivePlayerMoneyB(fjob+PlayerInfo[Offer[killerid]][pJob], Offer[killerid], floatround(percent*TotalRates/100));
		TotalRates -= floatround(percent*TotalRates/100);
		//TotalRates = 200 - 5*200/100 = 200 - 10 = 190
		/*new ammount = 0;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if(IsPlayerConnected(i) && gPlayerSpawned[i] == 1)
			{
				if(Rates[i][0] > 0 && killerid == BoxerBlue)
				{
		            ammount ++;
			    }
				else if(Rates[i][1] > 0 && killerid == BoxerRed)
				{
		            ammount ++;
			    }
			}
		}*/

		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if( !IsPlayerInRangeOfPlayer(30.0, i, killerid) ) continue;
			if(Rates[i][0] > 0 )
			{
		        //if(IsPlayerInRangeOfPoint(i, 15.0, 764.9067,6.4177,1000.7171))
		        //if(IsPlayerInRangeOfPoint(i, 15.0, 768.9097,-70.9200,1001.5692))
	        	if(killerid == BoxerBlue)
	        	{//если игрок поставил на синего и выйграл синий игрок
	        		new Float: FactorBlue = float(Rates[i][0])/float(TotalRateBlue);
	        		//100/200 = 0.5
	        		//находим процент вашей ставки от суммы ставок на этого бойца
	        		new money;
	  			    if(TotalRates > 0 && FactorBlue > 0) money = floatround( TotalRates*FactorBlue);//*ProbabilityLose сколько дать от общей суммы
	  			    //0.5 * 190*0.2 = 19
					GivePlayerMoneyH(fbox, i, money);
	    			format(strings, sizeof(strings), "Bookmaker %s: Ваша Ставка $%d на Синего(%s) - Сыграла. Вы выйграли $%d",  PlayerName(Offer[killerid]), Rates[i][0], PlayerName(BoxerBlue), money);
					SendClientMessage(i, COLOR_YELLOW, strings);
					Log(RATE,strings);
					//Rates[i][0] = 0;
	        	}
		       	else
		        {
	    			format(strings, sizeof(strings), "Bookmaker %s: Ваша Ставка $%d на Синего(%s) - НЕ Сыграла.",  PlayerName(Offer[killerid]), Rates[i][0], PlayerName(BoxerBlue));
					SendClientMessage(i, COLOR_YELLOW, strings);
				}
			}
			else if(Rates[i][1] > 0)
			{
	        	if(killerid == BoxerRed)
	        	{//если игрок поставил на красного и выйграл красный игрок
	        		new Float: FactorRed = float(Rates[i][1])/float(TotalRateRed);
	        		//находим процент вашей ставки от суммы ставок на этого бойца
	        		new money;
	  			    if(TotalRates > 0 && FactorRed > 0) money = floatround(TotalRates * FactorRed);//*ProbabilityLose сколько дать от общей суммы
	 				GivePlayerMoneyH(fbox, i, money);
	    			format(strings, sizeof(strings), "Bookmaker %s: Ваша Ставка $%d на Красного(%s) - Сыграла. Вы выйграли $%d",  PlayerName(Offer[killerid]), Rates[i][1], PlayerName(BoxerRed), money);
					SendClientMessage(i, COLOR_YELLOW, strings);
					Log(RATE,strings);
					//Rates[i][1] = 0;
		        }
		        else
		        {
	    			format(strings, sizeof(strings), "Bookmaker %s: Ваша Ставка $%d на Красного(%s) - НЕ Сыграла.",  PlayerName(Offer[killerid]), Rates[i][1], PlayerName(BoxerRed));
					SendClientMessage(i, COLOR_YELLOW, strings);
				}
			}
		}
	}

	FightStarted(PlayerInfo[killerid][pInt],
		Offer[killerid],
		BoxerBlue, TotalRateBlue, DeathCounter2,
		BoxerRed, TotalRateRed, DeathCounter1 );
	//--------------------------------------------------------------
	//снятие с ринга убийцы
	SetPlayerSkinEx(killerid, PlayerInfo[killerid][pModel]);

   	new Float:plocx, Float:plocy, Float:plocz;
	GetPlayerPos(Offer[killerid], plocx, plocy, plocz);
	SetPlayerVirtualWorldEx(killerid, PlayerInfo[Offer[killerid]][pVirtual]);
	SetPlayerInteriorEx(killerid, PlayerInfo[Offer[killerid]][pInt]);//Изменяет ид интерьера на интерьер цели наблюдения
	PlayerInfo[killerid][pLocal] = PlayerInfo[Offer[killerid]][pLocal];
	SetPlayerPosEx(killerid, plocx+1.0,plocy+1.0,plocz, 0);//plocy+2

	gPlayerBoxing[killerid] = 0;
	Offer[killerid] = MAX_PLAYERS-1;
	//--------------------------------------------------------------
	TotalRates = 0;
	TotalRateBlue = 0;
	TotalRateRed = 0;

	RoundCounter = 0;
	RoundStarted = 0;

	BoxerBlue = MAX_PLAYERS-1;
	BoxerRed = MAX_PLAYERS-1;
	DeathCounter1 = 0;
	DeathCounter2 = 0;
	return 1;
}

stock box_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BOX_DIALOG) return 1;//для букмекеров STEP2
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) { Offer[playerid] = MAX_PLAYERS-1; return 1; }

   	new Float:plocx, Float:plocy, Float:plocz;
	GetPlayerPos(Offer[playerid], plocx, plocy, plocz);
	SetPlayerVirtualWorldEx(playerid, PlayerInfo[Offer[playerid]][pVirtual]);
	SetPlayerInteriorEx(playerid, PlayerInfo[Offer[playerid]][pInt]);//Изменяет ид интерьера на интерьер цели наблюдения
	PlayerInfo[playerid][pLocal] = PlayerInfo[Offer[playerid]][pLocal];
	SetPlayerPosEx(playerid, plocx+1.0,plocy+1.0,plocz, 0);//plocy+2
	Offer[playerid] = MAX_PLAYERS-1;
	return 1;
}


stock box_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_WASTED)//выполняется сразу после смерти игрока
	{   //если ID нового состояния равно состоянию 7
		//if(gPlayerBoxing[playerid] == 0)
		//для боксёров начало STEP8
		if(RoundStarted > 0 && gPlayerBoxing[playerid] == 1 && RoundCounter > 0)
		{   //если раунд начался и игрок участник боя
			if(playerid == BoxerBlue) DeathCounter1 ++;
			else if(playerid == BoxerRed) DeathCounter2 ++;
			if(DeathCounter1 >= 3 || DeathCounter2 >= 3)
			{   //если участник поединка достигает 3 смерти
				gPlayerBoxing[playerid] = 2;
				//выводим из поединка до того моментка как ему установиться спаун
			}
		}
	}
}


stock box_OneSecondTimers(playerid)
{
	if( AFK_IdleTime[playerid] >= 3) return 1;
	//---------------------------------------------------------------------------
	//для боксёров начало STEP4
	if(RoundCounter > 0 && gPlayerBoxing[playerid] && BoxWaitTime[playerid] > 0)
	{
	    if(BoxWaitTime[playerid] >= BoxDelay)
		{
		    BoxDelay = 0;
			BoxWaitTime[playerid] = 0;
			GameTextForPlayerEx(playerid, "~g~Match Started", 5000, 1);
			TogglePlayerControllableEx(playerid, 1);
			RoundStarted = 1;
			//PlaySoundForPlayer(playerid, SOUND_RACE_GO);
			PlaySoundForPlayer(playerid, SOUND_GYM_BOXING_BELL);
		}
	    else
		{
			new strtmp[2+10];
		    format(strtmp, sizeof(strtmp), "%d", BoxDelay - BoxWaitTime[playerid]);
			GameTextForPlayerEx(playerid, strtmp, 1500, 3);
			BoxWaitTime[playerid] += 1;
			//PlaySoundForPlayer(playerid, SOUND_RACE_321);
			PlaySoundForPlayer(playerid, SOUND_GYM_BOXING_BELL);
		}
	}
	return 1;
}

stock box_OnPlayerCommandText(playerid)
{
		new strcmd[MAX_STRING];
//для боксёров начало STEP3
        //if(PlayerInfo[playerid][pJob] != 12)
        if(PlayerInfo[playerid][pJob] != BOOKMAKER)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы - не Букмекер!");
            return 1;
        }
        if(RoundCounter > 0)
        {
            SendClientMessage(playerid, COLOR_GREY, "  Уже идет Бой, ждите окончания Боя !");
            return 1;
        }
        /*if(!IsPlayerInRangeOfPoint(playerid, 15.0, 764.9067,6.4177,1000.7171))
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не в Зале Ganton Gym на Grove Street (LS)!");
            return 1;
        }
        if(!IsPlayerInRangeOfPoint(playerid, 15.0, 766.7358,-68.5967,1001.5692))
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не в Зале Below the Belt Gym на Redsands_East2 (LV)!");
            return 1;
        }*/
        if(!IsPlayerInRangeOfPoint(playerid, 15.0, 764.9067,6.4177,1000.7171) && !IsPlayerInRangeOfPoint(playerid, 15.0, 766.7358,-68.5967,1001.5692))
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не в Спортивном Зале!");
            return 1;
        }
        if(BoxerBlue == MAX_PLAYERS-1 || BoxerRed == MAX_PLAYERS-1)
        { 	//когда оба участника согласились на бой
            SendClientMessage(playerid, COLOR_GREY, "  На ринге нету двух бойцов !");
            return 1;
        }
		if( Offer[BoxerBlue] != playerid && Offer[BoxerRed] != playerid &&
			Offer[BoxerBlue] != MAX_PLAYERS-1 && Offer[BoxerRed] != MAX_PLAYERS-1)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы - не можете начать бой, т.к. не Вы организатор данного боя!");
            return 1;
        }
        if(TotalRates < 1000)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы - не можете начать бой, т.к. сумма ставок меньше $1000!");
            return 1;
        }

	    format(strcmd, sizeof(strcmd), "Bookmaker %s: Начинаем бой. На ринге %s %s (Ставка $%d) и %s %s (Ставка $%d).",
			PlayerName(playerid), titleblue, PlayerName(BoxerBlue), TotalRateBlue, titlered, PlayerName(BoxerRed), TotalRateRed);
		OOCNews(COLOR_LIGHTORANGE,strcmd);
		BoxDelay = 10;//задержка до старта
		BoxWaitTime[BoxerBlue] = 1;//флаг для начала отсчёта
		BoxWaitTime[BoxerRed] = 1;//флаг для начала отсчёта

		RoundCounter = 1;//ринг занет начинаем первый раунд

		FightStarted(PlayerInfo[BoxerBlue][pInt],
			Offer[BoxerBlue],
			BoxerBlue, TotalRateBlue, DeathCounter1,
			BoxerRed, TotalRateRed, DeathCounter2 );

		format(strcmd, sizeof(strcmd), "~r~Round ~w~%d", RoundCounter);
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(gPlayerLogged[i] == 1 && IsPlayerInRangeOfPlayer(30.0, i, playerid))
			{
		        //if(IsPlayerInRangeOfPoint(i, 15.0, 764.9067,6.4177,1000.7171))
		        //if(IsPlayerInRangeOfPoint(i, 15.0, 768.9097,-70.9200,1001.5692))
				GameTextForPlayerEx(i, strcmd, 5000, 4);
			}
		}
		//GameTextForAll(strcmd, 5000, 4);
		return 1;
}//для боксёров конец

//для боксёров
stock FightStarted(interior, boxofferid, blueplayerid,rateblue,deathblue, redplayerid,ratered,deathred)
{   //запускается по команде /fight и по окончанию боя
#if defined vw_sql//#endif

#else
	#pragma unused rateblue
	#pragma unused deathblue
	#pragma unused ratered
	#pragma unused deathred
#endif

	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	if(RoundStarted == 0)
	{   //начало боя
		//format(BoxDate, sizeof(BoxDate), "%04d-%02d-%02d %02d:%02d", ly,lmm,ld, lH,lM);
		BoxTime = GetTickCount();
	}
	else
	{
		new gym[11];
		if(interior == 5) gym = "Ganton Gym";
		else if(interior == 6) gym = "Arts Gym";
		else if(interior == 7) gym = "Belt Gym";
		BoxTime = (GetTickCount() - BoxTime)/1000;
		RoundStarted = 0;

		new boxoffername[MAX_PLAYER_NAME];
		GetPlayerName(boxofferid, boxoffername, MAX_PLAYER_NAME);
		//mysql_real_escape_string(boxoffername, boxoffername);

		new blueplayername[MAX_PLAYER_NAME];
		GetPlayerName(blueplayerid, blueplayername, MAX_PLAYER_NAME);
		//mysql_real_escape_string(blueplayername, blueplayername);

		new redplayername[MAX_PLAYER_NAME];
		GetPlayerName(redplayerid, redplayername, MAX_PLAYER_NAME);
		//mysql_real_escape_string(redplayername, redplayername);
#if defined vw_sql//#endif
		new ToBase[188 + 37+11+24 + 24+10+2 + 24+10+2 + 7];
		format(ToBase, sizeof(ToBase), "INSERT INTO `lastrounds`\
(`Date`,`Gym`,`BoxOffer`, `BluePlayer`,`BlueRate`,`BlueDeath`, `RedPlayer`,`RedRate`,`RedDeath`, `BoxTime`)\
VALUES (NULL,'%s','%s', '%s',%d,%d, '%s',%d,%d, %d)",
			//BoxDate,
			gym, boxoffername,
			blueplayername, rateblue, deathblue,
			redplayername, ratered, deathred,
			BoxTime);
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif
	}
}
