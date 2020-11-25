new gKickStartDoor = 0;

//для KickStart начало
#define MAX_SCORE 32       // Макс. кол-во
#define GREEN_PACKAGE 12
new Float:EasyPickupC[GREEN_PACKAGE][3] = {
{-1387.9177, 1572.2270, 1055.0},//0
{-1384.6793, 1603.8028, 1055.0},
{-1456.8065, 1648.6833, 1056.0},
{-1442.9694, 1648.5679, 1056.0},
{-1431.2161, 1598.0710, 1056.0},
{-1420.9184, 1597.8729, 1056.0},
{-1398.7708, 1604.2564, 1056.0},
{-1408.2796, 1592.9285, 1057.0},
{-1408.5103, 1568.8586, 1057.0},
{-1486.8350, 1630.4362, 1058.0},
{-1354.7637, 1583.5765, 1059.0},
{-1377.0338, 1562.3503, 1060.0}
};
#define YELLOW_PACKAGE 11
new Float:MediumPickupC[YELLOW_PACKAGE][3] = {
{-1371.5153, 1623.3035, 1056.0},
{-1462.0891, 1622.5404, 1056.0},
{-1461.9200, 1636.1784, 1056.0},
{-1417.8778, 1606.6501, 1057.0},
{-1409.0939, 1618.0404, 1057.0},
{-1362.8763, 1613.4726, 1057.0},
{-1431.0374, 1580.7763, 1057.0},
{-1454.1529, 1636.0413, 1058.0},
{-1488.2212, 1564.8015, 1058.0},
{-1452.8483, 1573.9895, 1059.0},
{-1405.0095, 1644.5498, 1071.0}
};
#define RED_PACKAGE 9
new Float:HardPickupC[RED_PACKAGE][3] = {
{-1453.9658, 1628.5312, 1056.0},//0
{-1390.0844, 1622.2866, 1057.0},
{-1370.9227, 1635.2860, 1057.0},
{-1451.1343, 1620.8309, 1057.0},
{-1359.5809, 1637.7708, 1057.0},
{-1446.5382, 1620.8988, 1058.0},//{-1454.3531, 1617.3087, 1058.0},//5
{-1466.1433, 1594.2271, 1059.0},
{-1485.1008, 1643.4156, 1062.0},
{-1429.1083, 1617.3617, 1058.0}//{-1378.6506, 1610.4999, 1057.0},//{-1408.4288, 1585.5469, 1057.0},//8
};

//ID пикапов
new EasyPickup[GREEN_PACKAGE] = {-1,...}; //Простые пикапы для подбора
new MediumPickup[YELLOW_PACKAGE] = {-1,...};  //Сложные пикапы для подбора
new HardPickup[RED_PACKAGE] = {-1,...};  //Сложные пикапы для подбора


new gInDerbyKickStart[MAX_PLAYERS]; //проверка на нахождение игрока в здании
new PickupScore[MAX_PLAYERS];//кол-во собраных очков данным игроком
new gKickStarted;
new KickStartProgress; //Общий Счетчик собраных пикапов
new TimeSecRide[MAX_PLAYERS];  //Таймер отсчёта
//для KickStart конец

stock kickstart_OnPlayerConnect(playerid)
{
//для KickStart
	gInDerbyKickStart[playerid] = 0; //проверка на нахождение игрока в здании
	PickupScore[playerid] = 0;
	TimeSecRide[playerid] = 0; //Таймер отсчёта
}


//stock KickStartTimer(playerid)//для дерби BloodBowl //для дерби 8ball
stock kickstart_OneSecondTimers(playerid)
{   //вызывается из секундного таймера OnPlayerCallTime
	//для KickStart STEP3
	if(!gInDerbyKickStart[playerid]) return 1;
	if(!gKickStarted) return 1;
    if(TimeSecRide[playerid] > 0)
    {
		CrashDetected[playerid] = 25;
		TimeSecRide[playerid] --;
		if(TimeSecRide[playerid] <= 0) //Обновление текстдрава
		{
			StopKickStart(playerid);
			//если время закончилось, а пикапы ещё нет
			//то продолжить
		}
		new strtmp[84+2+2+2+4];
		format(strtmp, sizeof(strtmp), "~y~Time: ~w~%d ~y~sec. ~n~Markers: ~w~%d ~y~/ "#MAX_SCORE" ~n~Score: ~p~$%d ~n~Money: ~g~$%d", TimeSecRide[playerid], KickStartProgress, PickupScore[playerid], PickupScore[playerid]*50);
		PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strtmp);
	}
	return 1;
}

//для KickStart STEP2 начало
//stock KickStartInit(playerid)//может вызываться несколько раз при посадки за руль тачки
stock kickstart_OnPlayerStateChange(playerid, newstate)//может вызываться несколько раз при посадки за руль тачки
{ 
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	if(PlayerInfo[playerid][pLocal] != 214) return 1;
	//----------------------------------------------------------------------
	if(gInDerbyKickStart[playerid] == 1) return 1;//чтобы каждый раз при посадке не инициализировалось

	PlayerInfo[playerid][pParam2] = 0; gParameter2[playerid] = 0;
	SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], 50);

//стартовая инициализация
	gInDerbyKickStart[playerid] = 1;
	TimeSecRide[playerid] = 20;
	PickupScore[playerid] = 0;
	gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);

	GameTextForPlayerEx(playerid, "Use the Sanchez to collect Coronas.\
~n~The ~g~Green Corona ~w~is worth 1 point.\
~n~The ~y~Amber Corona ~w~is worth 2 points.\
~n~The ~r~Red Corona ~w~is worth 3 points.", 5000, 5);

	//GameTextForPlayerEx(playerid, "Collect as many points as possible.", 1000, 3);

	//--------------------------------------------------------------------------
	if(gKickStarted != 0) return 1;
	//если KickStart ещё не начат, то начать
	KickStartProgress = 0;
	for(new i=0; i<GREEN_PACKAGE; i++)
    {
		EasyPickup[i] = SetPickupEx(19291,14,EasyPickupC[i][0],EasyPickupC[i][1],EasyPickupC[i][2],14);//1254//19291

        if(i >= YELLOW_PACKAGE) continue;
        MediumPickup[i] = SetPickupEx(19294,14,MediumPickupC[i][0],MediumPickupC[i][1],MediumPickupC[i][2],14);//1313 //19294

		if(i >= RED_PACKAGE) continue;
        HardPickup[i] = SetPickupEx(19290,14,HardPickupC[i][0],HardPickupC[i][1],HardPickupC[i][2],14);//1313 //19290
	}
	gKickStarted = 1;
	//SendClientMessageToAll(COLOR_ORANGE, "Заезд {FF0000}KickStart{FF6600} начался.");
	SendAllAdminMessage(COLOR_ORANGE, "Заезд {FF0000}KickStart{FF6600} начался.", 1);
	return 1;
}

stock StopKickStart(playerid) //для KickStart STEP5
{//вызывается из  OnPlayerPickUpPickup || OnPlayerCallTime
	//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;//т.е. если игрок слезет с мото, то не будет идти время
	if(!gInDerbyKickStart[playerid]) return 1;//чтобы каждый раз при посадке не инициализировалось

	if(gKickStarted == 1 && KickStartProgress >= MAX_SCORE)
	{   //если кто то поднял последний пикап
		gKickStarted = 0;
		KickStartProgress = 0;

		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
		    if(i == playerid) continue;
			if(!IsPlayerConnectedEx(i)) continue;// || !gPlayerSpawned[i]
			if(!gInDerbyKickStart[i]) continue;

			gTextDrawHideCarTime[i] = true; OnPlayerTextDrawStateChange(playerid);
			TimeSecRide[i] = 0;
			gInDerbyKickStart[i] = 0;
			if(PickupScore[i] > 0) GivePlayerMoneyH(fkickstart, i, PickupScore[i]*50);
			PickupScore[i] = 0;
		}

		SendWinnerMessage(playerid);
		return 1;
	}
	if(TimeSecRide[playerid] <= 0 && gKickStarted == 1 && KickStartProgress < MAX_SCORE)
	{//если время закончилось //игра начата, а пикапы ещё нет, то заново начать
		if(PlayerInfo[playerid][pLocal] == 214)//вы в стадионе,
		{
			if(PickupScore[playerid] > 0) GivePlayerMoneyH(fkickstart, playerid, PickupScore[playerid]*50);

			TimeSecRide[playerid] = 20;
			PickupScore[playerid] = 0;
			gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		}
		//----------------------------------------------------------------------
		else//иначе просто закончить, если игрок вышел из стадиона и время кончилось
		{
			gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		    if(PickupScore[playerid] > 0) GivePlayerMoneyH(fkickstart, playerid, PickupScore[playerid]*50);
			TimeSecRide[playerid] = 0;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if( !gInDerbyKickStart[i] ) continue;
			 	//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, strings);
		    	format(strings, sizeof(strings), "KickStart: {FFFFFF}%s[%d]{00FF00} покинул стадион в Лас-Вентурасе. Причина: закончилось время", PlayerName(playerid), playerid);
			 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
			}
			gInDerbyKickStart[playerid] = 0;
			PickupScore[playerid] = 0;
		}
	    new found = -1;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if(!IsPlayerConnectedEx(i)) continue;
			if(!gInDerbyKickStart[i]) continue;
			found = i;
			break;
		}
		if(found == -1)
		{
			gKickStarted = 0;
			KickStartProgress = 0;
			//SendClientMessageToAll(COLOR_ORANGE, "Заезд {FF0000}KickStart{FF6600} закончился.");
			SendAllAdminMessage(COLOR_ORANGE, "Заезд {FF0000}KickStart{FF6600} закончился.", 1);
		}
	}
	return 1;
}
stock SendWinnerMessage(playerid) //Отсылает сообщение о победе в заезде
{
	new money = PickupScore[playerid]*50+3000;
	GivePlayerMoneyB(fkickstart, playerid, money);
    //new strings[MAX_STRING];
	format(strings, sizeof(strings), "В {FF0000}KickStart{FF6600} победил{FFFFFF} %s[%d]{FF6600}, выигрыш: {33AA33}$%d",
		PlayerName(playerid), playerid, money);
	SendClientMessageToAll(COLOR_ORANGE, strings);

	TimeSecRide[playerid] = 0;
	gInDerbyKickStart[playerid] = 0;
	PickupScore[playerid] = 0;
	gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
}


//stock IsPlayerInKickStart(playerid, pickupid)//для KickStart STEP4
stock kickstart_VehicleEnterPickUp(playerid, pickupid)
{   //вызывается из VehicleEnterPickUp - PlayerEnterPickups - OnPlayerPickUpPickup
	//для того чтобы не гонять цыкл каждый раз
	if(!gKickStarted) return 1;
	if(PlayerInfo[playerid][pLocal] != 214) return 1;
	if(!gInDerbyKickStart[playerid]) return 1;
	//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	//--------------------------------------------------------------------------
	for(new i=0; i<GREEN_PACKAGE; i++)
 	{   //находим из какого массив игрок поднял пикап
  		if(pickupid == EasyPickup[i] && EasyPickup[i] != -1) //простые пикапы
    	{
			TimeSecRide[playerid] += 10;
   			PickupScore[playerid] += 1;
			DestroyPickupEx(EasyPickup[i]); EasyPickup[i] = -1;
			KickStartProgress ++;
			GameTextForPlayerEx(playerid, "~p~You have collected an ~n~~g~Green Corona ~w~+1", 3000, 3);
       		if(KickStartProgress >= MAX_SCORE)
     		{   //если кто то поднял последний пикап, то закончить для всех KickStart
				StopKickStart(playerid);
			}
         	break;
		}
		if(i >= YELLOW_PACKAGE) continue;//защита
    	if(pickupid == MediumPickup[i] && MediumPickup[i] != -1) //средние пикапы
    	{
			TimeSecRide[playerid] += 20;
			PickupScore[playerid] += 2;
			DestroyPickupEx(MediumPickup[i]); MediumPickup[i] = -1;
			KickStartProgress ++;
			GameTextForPlayerEx(playerid, "~p~You have collected an ~n~~y~Amber Corona ~w~+2", 3000, 4);
       		if(KickStartProgress >= MAX_SCORE)
     		{   //если кто то поднял последний пикап, то закончить для всех KickStart
				StopKickStart(playerid);
			}
   			break;
		}
		if(i >= RED_PACKAGE) continue;//защита
    	if(pickupid == HardPickup[i] && HardPickup[i] != -1) //сложные пикапы
    	{
			TimeSecRide[playerid] += 30;
			PickupScore[playerid] += 3;
			DestroyPickupEx(HardPickup[i]); HardPickup[i] = -1;
			KickStartProgress ++;
			GameTextForPlayerEx(playerid, "~p~You have collected an ~n~~r~Red Corona ~w~+3", 3000, 5);
       		if(KickStartProgress >= MAX_SCORE)
     		{   //если кто то поднял последний пикап, то закончить для всех KickStart
				StopKickStart(playerid);
			}
   			break;
		}
	}
	return 1;
}

stock kickstart_OnPlayerPickUp(playerid)
{
	if( !IsPlayerInRangeOfPoint(playerid, 2.2, 1099.4869,1601.4949,12.5469) ) return 1;
  //вход Stunting Track(Kickstart)
	if(PlayerInfo[playerid][pLevel] < 10)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Доступ только с 10 уровня !");
		return 1;
	}
    SetPlayerInteriorEx(playerid, 14);
	SetPlayerPosEx(playerid, -1464.7804,1559.8026,1052.7500, 0.0);
	SetPlayerVirtualWorldEx(playerid, 14);
	PlayerInfo[playerid][pLocal] = 214;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if( !gInDerbyKickStart[i] ) continue;
	 	//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, strings);
    	format(strings, sizeof(strings), "KickStart: {FFFFFF}%s[%d]{00FF00} вошёл в стадион в Лас-Вентурасе", PlayerName(playerid), playerid);
	 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
	}
    GameTextForPlayerEx(playerid, "~w~Welcome to the ~n~~y~Stunting Track", 5000, 1);
	return 1;
}
//для KickStart конец

stock kickstart_OnPlayerCommandText(playerid)
{
		new strcmd[MAX_STRING];
	//else if(!strcmp(cmd, "/kinfo", true) || !strcmp(cmd, "/kickstartinfo", true))//для KickStart
	//{
		new bigmsgitem[1000];//71+20+34+3*39+37+36+43+18 + 10+3*7+10 + 75+71 + 15*(37+3+24+3+2+12+1) + 75 = 1868
	    format(bigmsgitem, sizeof(bigmsgitem), "gKickStartClosed: \t%d\ngKickStarted: \t\t%d\nKickStartProgress: \t%d",
			gKickStartDoor, gKickStarted, KickStartProgress);
		strins(bigmsgitem, "\n______________________________________________________________________\n", strlen(bigmsgitem));
		//new plCounter;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(gInDerbyKickStart[i] != 1) continue;
			//if(plCounter > 15) break;
			format(strcmd, sizeof(strcmd), "%d \t%s \tScore: %d \tTime:%d \tLocal:%d \tState:%d\n",
				i, PlayerName(i), PickupScore[i], TimeSecRide[i], PlayerInfo[i][pLocal], CurState[playerid]);
			strins(bigmsgitem, strcmd, strlen(bigmsgitem));
			//plCounter ++;
		}
		strins(bigmsgitem, "\nEasyPickup: ", strlen(bigmsgitem));
		for(new i=0; i<GREEN_PACKAGE; i++)
	    {
			format(strcmd, sizeof(strcmd), "%d[%d], ", EasyPickup[i], i);
			strins(bigmsgitem, strcmd, strlen(bigmsgitem));
		}
		strins(bigmsgitem, "\nMediumPickup: ", strlen(bigmsgitem));
		for(new i=0; i<YELLOW_PACKAGE; i++)
	    {
			format(strcmd, sizeof(strcmd), "%d[%d], ", MediumPickup[i], i);
			strins(bigmsgitem, strcmd, strlen(bigmsgitem));
		}
		strins(bigmsgitem, "\nHardPickup: ", strlen(bigmsgitem));
		for(new i=0; i<RED_PACKAGE; i++)
	    {
			format(strcmd, sizeof(strcmd), "%d[%d] ", HardPickup[i], i);
			strins(bigmsgitem, strcmd, strlen(bigmsgitem));
		}
		strins(bigmsgitem, "\n", strlen(bigmsgitem));
		if(strlen(bigmsgitem) >= sizeof(bigmsgitem))
		{
			//ИНФОРМИРОВАНИЕ
			format(strcmd, sizeof(strcmd), "Error30: KICKSTART - %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
				PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
			Log(ERROR, strcmd);
			return 1;
		}
		if(strlen(bigmsgitem) <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   KICKSTART пуст");
			return 1;
		}
		ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "KICKSTART", bigmsgitem, "OK", "");
		return 1;
}
