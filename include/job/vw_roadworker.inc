new road_object;
new road_object_check;



//new RepairRoadStatus[MAX_PLAYERS];

//MAX_PLAYERS-2 - блок установлен сервером

stock roadworker_OnGameModeInit()
{
	print("  vw_roadworker 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

stock roadworker_OnPlayerConnect(playerid)
{
	//ремонт дорог
	RemoveBuildingForPlayer(playerid, 16012, -264.671, 2596.570, 61.820, 0.250);
	RemoveBuildingForPlayer(playerid, 956, -253.742, 2599.760, 62.242, 0.250);
	RemoveBuildingForPlayer(playerid, 955, -253.742, 2597.949, 62.242, 0.250);
	RemoveBuildingForPlayer(playerid, 16020, -155.179, 2635.510, 63.398, 0.250);
	RemoveBuildingForPlayer(playerid, 16397, -224.272, 2680.169, 45.585, 0.250);
	RemoveBuildingForPlayer(playerid, 16415, -224.272, 2680.169, 45.585, 0.250);
	RemoveBuildingForPlayer(playerid, 16165, -223.843, 2538.209, 34.859, 0.250);
	RemoveBuildingForPlayer(playerid, 16451, -223.843, 2538.209, 34.859, 0.250);
	RemoveBuildingForPlayer(playerid, 669, -278.968, 2679.020, 61.843, 0.250);
	RemoveBuildingForPlayer(playerid, 16165, -223.843, 2538.209, 34.859, 0.250);
	RemoveBuildingForPlayer(playerid, 16451, -223.843, 2538.209, 34.859, 0.250);
	RemoveBuildingForPlayer(playerid, 16397, -224.272, 2680.169, 45.585, 0.250);
	RemoveBuildingForPlayer(playerid, 16415, -224.272, 2680.169, 45.585, 0.250);
	RemoveBuildingForPlayer(playerid, 16020, -155.179, 2635.510, 63.398, 0.250);
}

stock roadworker_OnPlayerPickUp(playerid, pickupid)
{
	#pragma unused pickupid
	if( //IsPlayerInRangeOfPoint(playerid, 2.1, -2112.6499,-2407.2903,31.30601) ||
			 //IsPlayerInRangeOfPoint(playerid, 2.1, 2563.7883,789.9964,10.9545) ||
			 //IsPlayerInRangeOfPoint(playerid, 2.1, 2730.5715,-2451.3306,17.5937) ||
			 IsPlayerInRangeOfPoint(playerid, 2.1, 214.4123,-230.1332,1.5581) )
	{   //для ремонтников STEP2
	//получение материалов
		if(PlayerInfo[playerid][pJob] == ROADWORKER)
		{	//factory production Material
			new level = PlayerInfo[playerid][pRoadSkill];
			new package;
			if(level < 50) { package = 1+PlayerInfo[playerid][pRoadSkill]*numplayers/50; }
			else if(level >= 50 && level < 100) { package = 1+PlayerInfo[playerid][pRoadSkill]*numplayers/50; }
			else if(level >= 100 && level < 200) { package = 1+PlayerInfo[playerid][pRoadSkill]*numplayers/50; }
			else if(level >= 200 && level < 400) { package = 1+PlayerInfo[playerid][pRoadSkill]*numplayers/50; }
			else if(level >= 400) { package = 1+PlayerInfo[playerid][pRoadSkill]*numplayers/50; }//кол-во материалов в одном пакете

	        if(PlayerInfo[playerid][pMats] >= package)
	        {
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять больше Пакетов с Материалами !");
				return 1;
	        }
		    format(strings, sizeof(strings), "* Вы получили %d Пакетов с Материалами.", package);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		    PlayerInfo[playerid][pMats] += package;
			GameTextForPlayerEx(playerid, "~w~Welcome to the ~y~Factory~n~~g~You have got Packages a Material", 5000, 3);
		}
	}
	return 1;
}

stock roadworker_OneSecondTimers(playerid)
{
    if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
	//для ремонтников
   	if(	IsPlayerInRangeOfPoint(playerid, 30.0, aRadar[nearest[playerid]][radX],aRadar[nearest[playerid]][radY],aRadar[nearest[playerid]][radZ])
		&& !IsInPlane(nCarID[playerid]) )//и ты НЕ на верте и НЕ на велосипеде
  		{   //если ты на растоянии 30 м от радара. 30 подбирается экспериментальным путём при максимальной скорости проезжающей тачки чтобы секундный таймер успел засесь
  		    //т.е. растоянии которое преоделевается на максимальной скорости за секунду
		//игрок проехал мимо радара
		if(gPlayerUsedBridge[playerid] != nearest[playerid])
		{
			gPlayerUsedBridge[playerid] = nearest[playerid];
			if(BridgeHealth[nearest[playerid]] < 1000)
			{
				BridgeHealth[nearest[playerid]] += floatround(100/numplayers);
				if(BridgeHealth[nearest[playerid]] >= 750)
				{
					if(BridgeHealth[nearest[playerid]] >= 1000) BridgeHealth[nearest[playerid]] = 1000;
					SetTimerEx("SetRoadBlock", 10000, 0, "id", MAX_PLAYERS-2, nearest[playerid]);//SetPlayerRoadBlock(MAX_PLAYERS-2, ir);
					//break;
				}
			}
		}
		//----------------------------------------------------------------------
		if(SpecialBleep[nCarID[playerid]] == 0) //continue;//если машина c мигалкой
		{//если машина без мигалки
	     	if(	GaiRad[playerid] == 0 && ExcessPlayerVelocities[playerid] != 0)
	       	{   //если пока радар не сработал и игрок превысил установленную скорость
              	GaiRad[playerid] = 1;//радар сработал
//ИНФОРМИРОВАНИЕ
////new strings[MAX_STRING];
//format(strings, sizeof(strings), "радар %d сработал", nearest[playerid]);
//ABroadCast(COLOR_MAROON, strings, 6);
//SendAllAdminMessage(COLOR_RED, strings, 6);
           	}
       	}
  	}
  	else
	{   //игрок покинул радар
		if(gPlayerUsedBridge[playerid] == nearest[playerid]) { gPlayerUsedBridge[playerid] = -1; speedpl[playerid] = 0; }
		GaiRad[playerid] = 0;//подготовить радар к сканированию
		//HideDialog(playerid);
		//ExcessPlayerVelocities[playerid] = 0;//убрать превышение (убирается автоматически и ставится)
//ИНФОРМИРОВАНИЕ
////new strings[MAX_STRING];
//format(strings, sizeof(strings), "радар %d готов к сканированию", nearest[playerid]);
//ABroadCast(COLOR_MAROON, strings, 6);
//SendAllAdminMessage(COLOR_RED, strings, 6);
	}
	return 1;
}



stock SetPlayerRoadBlock(playerid, radar)//для ремонтников STEP4
{//запускается 1 раз через 5 секунд, чтобы игрок мог покинуть мост
	new ir = radar;
//УСТАНОВКА БЛОКА
	if(ir >= MAX_RADARS-1)
	{//если дошли до конца
		if(playerid != MAX_PLAYERS-2) SendClientMessage(playerid, COLOR_GREY, "   Блок уже установлен !");
		return 1;
	}
	if( RepairRoadPlayerID[ir] == MAX_PLAYERS-1 && !IsValidObjectEx(pRoadblock[ir]) )
	{//если данный блок ir ещё не установлен
		//------------------------------------------------------------------
		//new strings[MAX_STRING];
		/*for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
		    if(PlayerInfo[i][pJob] == ROADWORKER) continue;
			if(!IsPlayerInRangeOfPoint(i, aRadar[ir][radRange], aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ])) continue;
			if(playerid != i)//MAX_PLAYERS-2)
			{
	    		format(strings, sizeof(strings), "   В зоне работ есть люди: %s[%d]", PlayerName(i), i);
		        SendClientMessage(playerid, COLOR_GREY, strings);
	        }
	        return 1;
		}*/
		RepairRoadPlayerID[ir] = playerid;
		pRoadblock[ir] = CreateObjectEx(aRadar[ir][objModelid],aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ],aRadar[ir][objrX],aRadar[ir][objrY],aRadar[ir][objrZ]);//0
		//format(strings, sizeof(strings), "Placed pRoadblock[%d]: %d, RepairRoadPlayerID[ir]: %s[%d]", ir, pRoadblock[ir], PlayerName(RepairRoadPlayerID[ir]), RepairRoadPlayerID[ir]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		new bridge[20];
		strmid(bridge, aRadar[ir][radName], 0, strlen(aRadar[ir][radName]), sizeof(bridge));
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		new strtmp[87+2+2+4+20+24+3];
		if(playerid < MAX_PLAYERS-2)
		{
			format(strtmp, sizeof(strtmp), "~w~RepairedRoadblock ~y~%d ~n~~r~Placed", ir+1);//~n~
			GameTextForPlayerEx(playerid, strtmp, 5000, 5);
			//format(strtmp, sizeof(strtmp), "[%d:%02d:%02d] На мосту {FFFFFF}%s{33AA33} ведутся ремонтные работы {FFFFFF}%s'ом[%d]!",
			format(PagerMessage, sizeof(PagerMessage), "На мосту %s ведутся ремонтные работы %s[%d]",
				bridge, PlayerName(RepairRoadPlayerID[ir]), RepairRoadPlayerID[ir]);

		}
		else
		{
			//format(strtmp, sizeof(strtmp), "[%d:%02d:%02d] На мосту {FFFFFF}%s{33AA33} ведутся ремонтные работы!", lH,lM,lS, bridge);
			format(PagerMessage, sizeof(PagerMessage), "На мосту %s ведутся ремонтные работы!", bridge);
			
		}

		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			//if(GetPVarInt(i, "gJob") == 1) continue;
			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-ir);
			SetPlayerMapIcon(i, MAX_PLAYER_ICONS-ir, aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ], 40, 0, MAPICON_GLOBAL);
			//SendClientMessageEx(i, COLOR_GREEN, strtmp);
			//PlayerTextDrawSetStringEx(i, txdPager[i], RusToGame(strtmp));
			//PlayAudioStreamForPlayerEx(i, "pager.wav");
			//strmid(PagerString, RusToGame(strtmp), 0, strlen(RusToGame(strtmp)), 255);
			//PagerOffset(i, 445.0, 143.0, 120, 200);
			SendPagerMessage(i);//, RusToGame(strtmp));
		}

		//return 1;//break;
	}
	return 1;//ir;
}


//stock roadworker_OnPlayerStateChange(playerid, oldstate)
stock roadworker_OnPlayerStateChange(playerid, newstate, oldstate)
//stock roadworker_STATE_DRIVER(playerid)
{
	//#pragma unused newstate
	if(PlayerInfo[playerid][pJob] != ROADWORKER) return 1;
	if(oldstate == PLAYER_STATE_DRIVER)
	{
	    if(gJobDuty[playerid] == 1)
	    {
	        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве вашей Дорожной Службы и не получаете вызовы больше.");
	        gJobDuty[playerid] = 0;
	        //RoadWorkerCounter -= 1;
			//DeletePVar(playerid, "dutylist");
			strdel(dutylist[playerid], 0, sizeof(dutylist));
			if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
	    }
	}
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	//new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	roadworker_TakeTask(playerid, nCarModel[playerid]);//modelid);
	return 1;
}


stock roadworker_TakeTask(playerid, modelid)
{
	if(modelid != 552) return 1;//для ремонтников STEP1
//если вы сели в Utility_Van
	/*if(gParameter2[playerid] == 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "    В отчаянии Вы не можете получить задание, сесть в авто или выйти на дежурство !");
		SendClientMessage(playerid, COLOR_GREY, "    Вам необходимо развлечься: посетите клубы и потанцуйте !");
		return 1;
	}*/
	/*if(gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "    Активизирован режим игры RealWar ! Вы не можете выйти на дежурство!");
		return 1;
	}*/
	/*if(nCarModel[playerid] != 552)
	{
		format(strings, sizeof(strings), "   Вы можете выйти на дежурство только на {FFFFFF}%s[%d]", VehicleArray[552-400][Vehicle_Name], 552);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}*/
//ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ РЕМОНТНИКУ
	if(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid] == 0)
    {
		if(gOnDuty[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выйти на работу когда вышли на дежурство.");
			return 1;
		}
		if(gInRacing[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "    Вы не можете выйти на работу когда участвуете в гонке.");
			return 1;
		}
        //SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь на Дежурстве вашей АвтоРемонтной Службы и получаете вызовы от нуждающихся людей.");
        gJobDuty[playerid] = 1;
        //RoadWorkerCounter += 1;
		format(strings, sizeof(strings), "Дорожный ремонтник {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
		SendClientMessage(playerid, COLOR_ORANGE, strings);
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {B8860B}%s\n", lH,lM,lS, strings);
		//SetPVarString(playerid, "dutylist", strings);
		format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {B8860B}%s\n", lH,lM,lS, strings);
		if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, 260);

		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Возьми коробку с инструментами (USE: /gps 1038)");
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "и установи дорожный блок на одном из мостов СА рядом с радаром");
		GameTextForPlayerEx(playerid, " Press ~b~~k~~VEHICLE_TURRETDOWN~ ~n~~g~|~w~Install road block~g~|", 1000, 1);
	}
	else if( IsPermitToRider(playerid) ) {	}
	else
	{
		//RemovePlayerFromVehicleEx(playerid);
		SendClientMessage(playerid, COLOR_GREY, "   Вы - не Работник Дорожной Службы или Вы не на дежурстве. Пожалуйста, переоденьтесь!");
		//return 1;
	}
	return 1;
}


//stock OnPlayerKeyRepairRoad(playerid, newkeys, oldkeys)//для ремонтников начало
stock roadworker_OnPlayerKeyState_UP(playerid)
{
	    if(PlayerInfo[playerid][pJob] != ROADWORKER) return 1;
	   	/*if(!IsPlayerInAnyVehicle(playerid))
		{
			//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
			return 1;
		}
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
			return 1;
		}*/
		if(gJobDuty[playerid] != 1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не вышли на дежурство !");
		    return 1;
		}
		if(nCarModel[playerid] != 552)
	   	{
	        SendClientMessage(playerid, COLOR_GREY, "   Вы - не в рабочей машине Utility_Van. (Model:552) !");
	        return 1;
	    }
		new bridge[20];
		//new found = -1;
		new strtmp[107+10+20];
		for(new ir=0; ir<MAX_RADARS; ir++)
		{
//для ремонтников STEP5
//РАЗГРУЗКА МАТЕРИАЛОВ
			if(	IsPlayerInRangeOfPoint(playerid, aRadar[ir][radRange]+10.0, aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ]) )
			{//сначало определим номер объекта где находится человек, т.е. зону ремонта
				if(	RepairRoadPlayerID[ir] < MAX_PLAYERS-1 && IsValidObjectEx(pRoadblock[ir]) )
				{//если блок установлен кем то и объект существует
					if(PlayerInfo[playerid][pMats] <= 0)
					{
						SendClientMessage(playerid, COLOR_GREY, "   У вас нет больше Пакетов с Материалами !");
						return 1;
					}
               		new money;
					PlayerInfo[playerid][pRoadSkill] += 1;//довать больше за ремонт, чем за бибикание, т.к. будут подставные
                	new level = PlayerInfo[playerid][pRoadSkill];
					if(level < 50) { money = (200 + random(200)); }
					else if(level >= 50 && level < 100) { money = (300 + random(300)); }
					else if(level >= 100 && level < 200) { money = (400 + random(400)); }
					else if(level >= 200 && level < 400) { money = (500 + random(500)); }
					else if(level >= 400) { money = (RANDMONEY5 + random(RANDMONEY5)); }
					//------------------------------------------------------
	                if(level == 50) { GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money*10); SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Ремонтника теперь 2."); }
					else if(level == 100) { GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money*10); SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Ремонтника теперь 3."); }
					else if(level == 200) { GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money*10); SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Ремонтника теперь 4."); }
					else if(level == 400) { GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money*10); SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Ремонтника теперь 5."); }
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);//money*100/100
					BizInfo[0][bTill] -= money; BizInfo[0][bImport] += money;

					strmid(bridge, aRadar[ir][radName], 0, strlen(aRadar[ir][radName]), sizeof(bridge));

		        	format(strings, sizeof(strings), "Pаботодатель: {0080FF}На твой счёт перечислено {33AA33}$%d{0080FF} за ремонтные работы на мосту {FFFFFF}%s", money, bridge);// money*100/100
					SendClientMessage(playerid, COLOR_GREEN, strings);
					//------------------------------------------------------
					BridgeHealth[ir] -= PlayerInfo[playerid][pMats];
					PlayerInfo[playerid][pMats] = 0;
					if(BridgeHealth[ir] <= 0)
					{
						PlayerInfo[RepairRoadPlayerID[ir]][pRoadSkill] += 10;
						DestroyObjectEx(pRoadblock[ir], 3);
						if( IsPlayerConnectedEx(RepairRoadPlayerID[ir]) )
						{
							format(strtmp, sizeof(strtmp), "~w~Roadblock ~y~%d ~n~~g~Deployed successfully", ir+1);//~n~
							GameTextForPlayerEx(RepairRoadPlayerID[ir], strtmp, 1500, 6);
						}
						//format(strings, sizeof(strings), "Мост {FFFFFF}%s{33AA33} свободен !", bridge);
						format(PagerMessage, sizeof(PagerMessage), "Мост %s свободен !", bridge);
						for(new j=0, i; j<MaxPlayers; j++)	{
							i = PLIDs[j];
							if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
							RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-ir);
							//SendClientMessage(i, COLOR_GREEN, strings);
							//PlayerTextDrawSetStringEx(i, txdPager[i], RusToGame(strtmp));
							//PlayAudioStreamForPlayerEx(i, "pager.wav");
							SendPagerMessage(i);//, RusToGame(strtmp));
						}
	    				//JobNews(COLOR_GREEN,strings);

						RepairRoadPlayerID[ir] = MAX_PLAYERS-1;
						BridgeHealth[ir] = 0;
					}
					else SetPlayerGameTextScale(playerid, "Repair Jobs", 1000-BridgeHealth[ir], 1000);
					return 1;
				}
				if(ir >= MAX_RADARS-1)
				{//если дошли до конца
					SendClientMessage(playerid, COLOR_GREY, "   Блок НЕ установлен !");
					return 1;
				}
			}
			/*if(ir >= MAX_RADARS-1)
			{//если дошли до конца
				SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от места ремонта моста !");
				return 1;
			}*/
			//------------------------------------------------------------------
//для ремонтников STEP3
//УСТАНОВКА БЛОКА
			if( IsPlayerInRangeOfPoint(playerid, aRadar[ir][radRange], aRadar[ir][radX],aRadar[ir][radY],aRadar[ir][radZ]) )
			{	//если ремонтник в радиусе действия этого радара
			    //new skill, roadblockcounter;
				if(BridgeHealth[ir] < 250)
				{
					strmid(bridge, aRadar[ir][radName], 0, strlen(aRadar[ir][radName]), sizeof(bridge));
					format(strings, sizeof(strings), "   Мост %s[%d] в хорошем состоянии ! Ремонт не требуется !", bridge, ir);
					SendClientMessage(playerid, COLOR_GREY, strings);
					return 1;
				}
				for(new irr=0; irr<MAX_RADARS; irr++)
				{
					if(RepairRoadPlayerID[irr] == playerid)
					{   //проверяем если установленные блоки этим игроком
					    //roadblockcounter ++;//подсчёт кол-ва установленных блоков
				        SendClientMessageEx(playerid, COLOR_GREY, "   Вы уже установили дорожный блок !");
				        return 1;
			    	}
			    }
				SetPlayerRoadBlock(playerid, ir);
				return 1;
			}
			if(ir >= MAX_RADARS-1)
			{//если дошли до конца
				SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от места установки дорожного блока !");
				return 1;
			}
		}
		//SendClientMessage(playerid, COLOR_GREY, "   Блок уже установлен !");
		return 1;
}
//===============================================================================
stock roadworker_OnPlayerKey_DRIVER(playerid)
{   //если игрок посигналил / просигналил
	if(PlayerInfo[playerid][pJob] != ROADWORKER) return 1;

	if(IsPlayerInRangeOfPoint(playerid, 9.0, -222.45360, 2612.67627, 61.72884)) // первые ворота
	{
		if(road_object_check == 1) return true;
		MoveObjectEx(road_object,-218.985733, 2612.877197, 62.408126 + 0.01, 0.01, 0.000000, 0.0, 0.000000);
		SetTimer("@Clost_road_object_object", 10000, false);
		road_object_check = 1;
	}
	new bridge[20]; new strtmp[107+10+20];
	for(new ir=0; ir<MAX_RADARS; ir++)
	{
		if(	!IsValidObjectEx(pRoadblock[ir]) ) continue;
		if(	RepairRoadPlayerID[ir] == playerid ) continue;
		if(	!IsPlayerInRangeOfPoint(playerid,
			aRadar[ir][radRange], aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ]) ) continue;
			//если клиент в зоне ремонта
		//если блок существует и игрок который сигналит не установливал данный блок
		//т.е. смогут сигналить все кроме того кто установил его
		BeepCounter[playerid] ++;
		//new strings[MAX_STRING];
		if(BeepCounter[playerid] < 3)
		{
			format(strtmp, sizeof(strtmp), "~y~%d", BeepCounter[playerid]);//~n~
			GameTextForPlayerEx(playerid, strtmp, 1000, 5);
		}
		else //if(BeepCounter[playerid] >= 3)//для ремонтников
		{
			BeepCounter[playerid] = 0;
			if(GetPlayerMoneyH(playerid) < compcost)
			{
				format(strtmp, sizeof(strtmp), "   У вас нет $%d наличных !", compcost);
				SendClientMessage(playerid, COLOR_GREY, strtmp);
				return 1;
			}
			PlayerInfo[playerid][pCash] -= compcost;
			//PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
			ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
			gConsumingMoney[playerid] = 2;
			GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
			LastMoney[playerid] = PlayerInfo[playerid][pCash];
			if(BizInfo[0][bTill]+compcost < 2147480000) { BizInfo[0][bTill] += compcost; BizInfo[0][bExport] += compcost; }
			if( RepairRoadPlayerID[ir] < MAX_PLAYERS-2 && IsPlayerConnected(RepairRoadPlayerID[ir]) )
			{//если блок установлен игроком, а не сервер
				BridgeHealth[ir] -= 100/numplayers;//200/numplayers; - слишком быстро
				if(BridgeHealth[ir] <= 0)
				{//если мост полностью отремонтирован
					PlayerInfo[ RepairRoadPlayerID[ir] ][pRoadSkill] += 5;
					DestroyObjectEx(pRoadblock[ir], 4);
					format(strtmp, sizeof(strtmp), "~w~Roadblock ~y~%d ~n~~g~Deployed successfully", ir+1);//~n~
					GameTextForPlayerEx(RepairRoadPlayerID[ir], strtmp, 1500, 6);
				}
			}
			else
			{
				BridgeHealth[ir] -= 100/numplayers;
				if(BridgeHealth[ir] <= 0)
				{
					DestroyObjectEx(pRoadblock[ir], 5);
				}
			}

			strmid(bridge, aRadar[ir][radName], 0, strlen(aRadar[ir][radName]), sizeof(bridge));
    		//format(strtmp, sizeof(strtmp), "Мост {FFFFFF}%s[RepairPlayerID:%d]{33AA33} свободен !!", bridge, RepairRoadPlayerID[ir]);
    		format(PagerMessage, sizeof(PagerMessage), "Мост %s[%d] свободен !!", bridge, RepairRoadPlayerID[ir]);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;

				RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-ir);
				//SendClientMessage(i, COLOR_GREEN, strtmp);
				//PlayerTextDrawSetStringEx(i, txdPager[i], RusToGame(strtmp));
				//PlayAudioStreamForPlayerEx(i, "pager.wav");
				SendPagerMessage(i);//, RusToGame(strtmp));
			}
    	//JobNews(COLOR_GREEN,strings);
			RepairRoadPlayerID[ir] = MAX_PLAYERS-1;
			BridgeHealth[ir] = 0;
			SetPlayerGameTextScale(playerid, "Repair Jobs", 1000-BridgeHealth[ir], 1000);
			break;
		}
	}
	return 1;
}


