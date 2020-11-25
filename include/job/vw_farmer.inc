/*
 *            VW_Farmer 1.0
 *       (c) Copyright 2009-2013 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (gameplanet.by)
 * @date      : 01.09.2013
 * @update    : 01.09.2013
 *
 * This file is provided as is (no warranties).
 *
 */
new Text3D: FarmInfo;      // 3д текст для склада фермеров

//для фермеров
#define MAX_POLE 8        //24 Макс. кол-во урожая на поле
new SeedObject[MAX_POLE];	// хранит ИД Объекта кустов


// Статус фермы  0- ничего, 1 - посадка, 2 - созревание, 3 - косьба, 4 - сбор урожая.
//new FarmerCounter;//кол-во людей работающих на ферме
new TakenSeedCounter;		// Счетчик взятых семян
new PlantedSeedCounter;		// Счетчик посаженных семян
new StartMoveBushCounter;	// Счетчик кустов запущенных
new StopMoveBushCounter;	// Счетчик кустов выросших
new MowingBushCounter;		// Счетчик кустов скошенных
new TakenBushCounter;		// Счетчик собраных снопов
new DeliveredBushCounter;	// Счетчик доставленных снопов

new gOccupiedSeedPlace[MAX_POLE];// флаг занятого места
new PlaceSeed[MAX_PLAYERS];  // хранит номер занятого места на поле (TakenSeedCounter) который взял игрок, обнуляется при выходе из CP
new Float:LastObjectX[MAX_PLAYERS], Float:LastObjectY[MAX_PLAYERS];//координаты пикапов снопов, используются при сборе урожая
new FermerStatus[MAX_PLAYERS]; // 0 - без объекта   1 - с объектом

new Float:travka[24][3] = {  // Координаты растений
// Максимальная высота 130.62791442871 в секунду по 0,0069163894653
{-1187.9555,-1055.7226,126.4780},
{-1179.1136,-1055.7226,126.4780},
{-1171.0322,-1055.7226,126.4780},
{-1161.5349,-1055.7226,126.4780},
{-1152.8505,-1055.7226,126.4780},
{-1142.5874,-1055.7226,126.4780},

{-1142.5874,-1046.7897,126.4780},
{-1152.8505,-1046.7897,126.4780},
{-1161.5349,-1046.7897,126.4780},
{-1171.0322,-1046.7897,126.4780},
{-1179.1136,-1046.7897,126.4780},
{-1187.9555,-1046.7897,126.4780},

{-1187.9555,-1037.2169,126.4780},
{-1179.1136,-1037.2169,126.4780},
{-1171.0322,-1037.2169,126.4780},
{-1161.5349,-1037.2169,126.4780},
{-1152.8505,-1037.2169,126.4780},
{-1142.5874,-1037.2169,126.4780},

{-1142.5874,-1028.3585,126.4780},
{-1152.8505,-1028.3585,126.4780},
{-1161.5349,-1028.3585,126.4780},
{-1171.0322,-1028.3585,126.4780},
{-1179.1136,-1028.3585,126.4780},
{-1187.9555,-1028.3585,126.4780}
};

//==============================================================================

stock farmer_OnGameModeInit()
{
//для фермеров
	new strtmp[431];//369 + 5*4 + 2+10 + 10+10+10 = 431
	format(strtmp, sizeof(strtmp), "[ Ферма ]\n\n{FF6600}Саженцев: {FFFFFF}%d{FF6600}\nБаланс {33AA33}$%d{FF6600}\nИнформация /finfo", SBizInfo[52][sbProducts], SBizInfo[52][sbTill]);
	FarmInfo = Create3DTextLabelEx(strtmp, 0xEEEE88FF, -1210.1460,-1043.3667,128.3897-0.75, 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);
}

stock farmer_OnPlayerConnect(playerid)
{
//для фермеров
	//if(callback == PlayerConnect)
	//{
	PlaceSeed[playerid] = 0; FermerStatus[playerid] = 0;
	LastObjectX[playerid] = 0.0; LastObjectY[playerid] = 0.0;
	//}
}

//для фермеров STEP14
stock farmer_OnPlayerPickUp(playerid, pickupid)// Сбор растений на ферме
{   //вызывается из OnPlayerPickUpPickup
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
	//if(PlayerInfo[playerid][pJob] != FARMER) return 1;//работу может брать ещё не фермер

//для фермеров STEP1
	if( IsPlayerInRangeOfPoint(playerid, 2.1, -1216.0327,-1055.8462,128.7905) )
	{//раздевалка /майка
		if(gOnDuty[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на службу!");
			return 1;
		}
		if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != FARMER)
		{
			format(strings, sizeof(strings), "Работодатель: {0080FF}Вы на работе {FFFFFF}%s{0080FF}. Чтобы уволиться (USE: /quitjob).", GetPlayerJob(playerid) ); //сообщение
			SendClientMessage(playerid, COLOR_GREEN, strings);
			return 1;
		}
		if(gJobDuty[playerid])
		{
			ShowPlayerDialogGap(playerid, FARMER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка фермеров", "Вы уже приступили к работе фермера!\nВы хотите закончить работу?","Да","Нет");
		}
		else
		{
			new dlgitem[65+93+91+67+60+89+87+83+47+89+44];
			//strcat(dlgitem, "Чтобы начать работу подойдите к зданию (USE: /gps 1035) и переоденьтесь в рабочую одежду\n");
			strcat(dlgitem, "1. Чтобы начать работу фермера переоденьтесь в рабочую одежду.\n");
			strcat(dlgitem, "2. Получив саженец, на вашей карте появится чекпоинт, идите на него.\n");
			strcat(dlgitem, "3. Посадив кустик вы получите ЗП(устанавливает владелец фермы), идите за новым саженцем.\n");
			strcat(dlgitem, "4. Когда засеете всё поле и урожай ("#MAX_POLE" кустов) созреет,\n");
			strcat(dlgitem, "снимите рубашку на всё том же маркере и начинайте косить.\n");
			strcat(dlgitem, "5. Вам надо просто не спеша пройти последовательно все кусты от первого до последнего.\n");
			strcat(dlgitem, "и останавливаться в центре каждого кустика. За каждый скошенный куст вы получите ЗП\n");
			strcat(dlgitem, "6. После того, как всё поле будет скошено, собирайте снопы и относите их в ангар\n");
			strcat(dlgitem, "За каждый доставленный сноп вы получите ЗП.\n");
			strcat(dlgitem, "Итого: на поле 8х4 вы заработаете премию=ЗП*96.\n\n");
			strcat(dlgitem, "Вы хотите переодеться, чтобы начать работу?");
			ShowPlayerDialogGap(playerid, FARMER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка фермеров", dlgitem, "Да", "Нет");
		}
	}
	else if( IsPlayerInRangeOfPoint(playerid, 2.1, -1210.1460,-1043.3667,128.3897) )
	{//доллар бизнесса ФЕРМЫ
		if(!gJobDuty[playerid]) return 1;
//для фермеров STEP3
		if(FermaStatus == 1)
		{
			FermerStart(playerid);
		}
//для фермеров STEP7
		else if(FermaStatus == 2)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Идёт созревание урожая. Ждите");
		}
//для фермеров STEP9
		else if(FermaStatus == 3)
		{
			if(PlayerInfo[playerid][pSex] == Female) SetPlayerSkinEx(playerid, 90);
			else SetPlayerSkinEx(playerid, 162);
			SendClientMessage(playerid, COLOR_GREY, "   Идёт покос урожая.");
			SendClientMessage(playerid, COLOR_GREY, "   Идите от первого куста к последнему, не спеша, останавливаясь в центре.");
		}
//для фермеров STEP15
		else if(FermaStatus == 4)
		{
		    FermaEnd(playerid);//для фермеров STEP16
		}
		UpdateFarm();
	}
	else
	{//иначе если ты просто подобрал какой то пикап в зоне поля во время сбора урожая
		if(PlayerInfo[playerid][pJob] != FARMER) return 1;
		if(!gJobDuty[playerid]) return 1;
		if(FermaStatus != 4) return 1;
		if( !IsPlayerInArea(playerid, specialzone[9]) ) return 1;

		//if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) return SendClientMessage(playerid, COLOR_GREY, "   У вас есть сноп в руках !");
		if(FermerStatus[playerid] == 1) return SendClientMessage(playerid, COLOR_GREY, "   У вас есть сноп в руках !");
		//if(GetPlayerSkin(playerid) != 162) return 1;

		for(new p = 0; p <= MAX_POLE; p++)
		{   //сканируем все снопы
			if(	!IsPlayerInRangeOfPoint(playerid, 4.8, travka[p][0],travka[p][1],travka[p][2]) ) continue;
			//находим индекс в массиве всех точек, чтобы записать координаты где был пикап
			LastObjectX[playerid] = travka[p][0];
			LastObjectY[playerid] = travka[p][1];
			//ObjectIndex = p;
			break;
		}

		//SeedPickup[TakenBushCounter] = pickupid;//записали ИД пикапа
		TakenBushCounter ++;
		if(PlayerInfo[playerid][pAdmin] > 0)
		{
			format(strings, sizeof(strings), "%s подобрал %d[DestroyPickupID:%d] сноп конопли.", PlayerName(playerid), TakenBushCounter, pickupid);
			//SendClientMessage(playerid, COLOR_GREY, strings);
			SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 6);
		}
		DestroyPickupEx(pickupid);

		SetPlayerAttachedObjectEx( playerid, DUTY_SLOT, 2901, Neck, -0.07,0.35,0.07, 331.51,271.87,321.75, 0.83,1.0,0.75 );
		FermerStatus[playerid] = 1;

		//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,1,0,0,1,1);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

		/*if(PlayerInfo[playerid][pAdmin] > 0)
		{
			//ИНФОРМИРОВАНИЕ
		   	format(strings, sizeof(strings), "   Ты взял %d[pickupid:%d] сноп конопли (LastObjectX: %.4f, LastObjectY: %.4f)",
			   	TakenBushCounter, pickupid, LastObjectX[playerid], LastObjectY[playerid]);
			SendClientMessage(playerid, COLOR_GREY, strings);
		}*/
	   	GivePlayerMoneyB(fsbiz+52, playerid, SBizInfo[52][sbSalary]);//JOBPRICE);
	    SBizInfo[52][sbTill] -= SBizInfo[52][sbSalary];//JOBPRICE;
	    SBizInfo[52][sbImport] += SBizInfo[52][sbSalary];
		UpdateFarm();
	}
	return 1;
}



stock farmer_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != FARMER_DIALOG) return 1;
 //ShowPlayerDialogGap(playerid, FARMER_DIALOG, DIALOG_STYLE_MSGBOX, "Ферма", dlgitem, "Да", "Нет");
		SetPVarInt(playerid, "gShowDialog", -1);
		if(!response) return 1;

//для фермеров STEP2
		//if(PlayerInfo[playerid][pJob] == FARMER)
		if(gJobDuty[playerid])
		{
			//для фермеров STEP0
			FixJobCounter(playerid);
			//FarmerExitAndDeath(playerid);//должна быть всегда перед FixJobCounter
			SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
			if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты завершил работу на ферме !");
		}
		else
		{
			PlayerInfo[playerid][pJob] = FARMER; gJobDuty[playerid] = 1;
			JobAmmount[playerid] = 0;
			if(PlayerInfo[playerid][pSex] == Female)
			{
			    new skin = random(4);
			    if(skin == 0) SetPlayerSkinEx(playerid, 130);
			    else if(skin == 1) SetPlayerSkinEx(playerid, 131);
			    else if(skin == 2) SetPlayerSkinEx(playerid, 157);
			    else if(skin == 3) SetPlayerSkinEx(playerid, 201);
				else SetPlayerSkinEx(playerid, 90);
			}
			else
			{
			    new skin = random(9);
			    if(skin == 0) SetPlayerSkinEx(playerid, 32);
			    else if(skin == 1) SetPlayerSkinEx(playerid, 34);
			    else if(skin == 2) SetPlayerSkinEx(playerid, 128);
			    else if(skin == 3) SetPlayerSkinEx(playerid, 132);
			    else if(skin == 4) SetPlayerSkinEx(playerid, 158);
			    else if(skin == 5) SetPlayerSkinEx(playerid, 159);
			    else if(skin == 6) SetPlayerSkinEx(playerid, 160);
			    else if(skin == 7) SetPlayerSkinEx(playerid, 161);
			    else if(skin == 8) SetPlayerSkinEx(playerid, 200);
				else SetPlayerSkinEx(playerid, 162);
			}

			CP[playerid] = 0;
			PlaceSeed[playerid] = 0;
			FermerStatus[playerid] = 0;
			LastObjectX[playerid] = 0.0;
			LastObjectY[playerid] = 0.0;

			SBizInfo[52][sbWorker] ++;//FarmerCounter ++;
			if(FermaStatus == 0 && SBizInfo[52][sbWorker] == 1)
			{
				for(new o; o<MAX_POLE; o++)
				{
					SeedObject[o] = 0;
				}
				FermaStatus = 1;//1- посадка
			}
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты начал работу на ферме. Иди на доллар, чтобы получить саженец.");
		}
		return 1;
}//для фермеров конец


stock FermerStart(playerid)//для фермеров STEP3
{
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
	if(PlayerInfo[playerid][pJob] != FARMER) return 1;
	if(!gJobDuty[playerid]) return 1;

    //////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "CP[%d] == 0 && TakenSeedCounter[%d] < %d && PlaceSeed[%d] == 0", 
	//	CP[playerid], TakenSeedCounter, MAX_POLE, PlaceSeed[playerid]);
	//SendClientMessage(playerid, COLOR_GREY, strings);
	//SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 9);

	if(	CP[playerid] == 0 && TakenSeedCounter < MAX_POLE &&
		PlaceSeed[playerid] == 0)
	{//место
		//gJobDuty[playerid] = 1;
		if(TakenSeedCounter == 0) SendClientMessage(playerid, COLOR_GREY, "   Чтобы начать посадку семян конопли, идите на красную метку на радаре.");

       	SetPlayerAttachedObjectEx(playerid, DUTY_SLOT, 2247, Right_hand, -0.003353,0.093383,0.176903, 0.0,0.0,0.0, 0.788097,1.0,0.991011);
		FermerStatus[playerid] = 1;

//ищим пусты пропущенные места
		for(new o=0; o<MAX_POLE; o++)
       	{
       		if(gOccupiedSeedPlace[o] == 0)  //если место свободно, то занять
       		{
				CP[playerid] = CP_FARMER;
				SetPlayerCheckpointEx(playerid, travka[o][0],travka[o][1],travka[o][2],CHECKPOINT_SIZE);//TakenSeedCounter
				PlaceSeed[playerid] = o+1;//TakenSeedCounter
				gOccupiedSeedPlace[o] = 1;
				break;
			}
        }
		TakenSeedCounter ++;
		SBizInfo[52][sbProducts] -= 1;//отнимаем со склада саженец

		if(PlayerInfo[playerid][pAdmin] > 0)
		{
			//ИНФОРМИРОВАНИЕ
			format(strings, sizeof(strings), "   %s[%d] взял %d-ый[%d] саженец", PlayerName(playerid), playerid, TakenSeedCounter, PlaceSeed[playerid]);
			SendClientMessage(playerid, COLOR_GREY, strings);
			//SendClientMessage(playerid, COLOR_GREY, "   Вы получили саженцы для посадки конопли");
		}
	}
	return 1;
}

stock farm_OnPlayerEnterCheckpoint(playerid)//для фермеров STEP4
{
	if(CP[playerid] == CP_FARMER && FermaStatus == 1 && PlayerInfo[playerid][pJob] == FARMER)
	{//для фермеров STEP4
		if(PlaceSeed[playerid] == 0) SendClientMessage(playerid, COLOR_GREY, "   У вас нету саженца в руках !");
		else
		{
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0,0,0,0,0,6000, 1);
			//OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.1,1,0,0,0,6000);
			//надо предотвратить повторный запуск, когда игрок вводит новую анимацию
			//и сразу выбегает из чекпоинта раньше чем сработала ф-ия покидания чекпонта
			//т.е. если игрок зашёл раз в чекпоинт, потом покинул чекпоинт раньше чем сработал таймер и ещё раз посадил, т.к. саженец
			SetTimerEx("tPosadka", 4000, 0, "d", playerid);//разовый таймер
	//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.5 ", GetTickCount(), timers);
		}
  	}
}

//для фермеров STEP5
forward tPosadka(playerid);  // Посадка растений на ферме
public tPosadka(playerid)// Посадка растений на ферме
{   //запускается разовым таймеров через 6 секунд из OnPlayerEnterCheckpoint
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
	if(PlayerInfo[playerid][pJob] != FARMER) return 1;
	if(!gJobDuty[playerid]) return 1;

	new timers = GetTickCount();
	if(!IsPlayerInCheckpoint(playerid))
	{
		return SendClientMessage(playerid, COLOR_GREY, "   Вы покинули место посадки. Возвращайтесь в красный маркер !");
	}
	if(FermerStatus[playerid] == 1)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
		FermerStatus[playerid] = 0;
	}
	else return SendClientMessage(playerid, COLOR_GREY, "   У вас нету саженца в руках !");

	SeedObject[PlaceSeed[playerid]-1] = CreateObjectEx(823,travka[PlaceSeed[playerid]-1][0],travka[PlaceSeed[playerid]-1][1],travka[PlaceSeed[playerid]-1][2], 0.0,0.0,0.0);
	if( !IsValidObjectEx(SeedObject[PlaceSeed[playerid]-1]) ) return SendClientMessage(playerid, COLOR_GREY, "   Вы не посадили кустик !");

    GivePlayerMoneyB(fsbiz+52, playerid, SBizInfo[52][sbSalary]);//JOBPRICE*2);
	SBizInfo[52][sbTill] -= SBizInfo[52][sbSalary];//JOBPRICE);
	SBizInfo[52][sbImport] += SBizInfo[52][sbSalary];//JOBPRICE);
    PlantedSeedCounter ++;
    UpdateFarm();

	if(PlayerInfo[playerid][pAdmin] > 0)
	{
		format(strings, sizeof(strings), "%s посадил %d[objectid:%d] кустик конопли.", PlayerName(playerid), PlaceSeed[playerid], SeedObject[PlaceSeed[playerid]-1]);
		//SendClientMessage(playerid, COLOR_GREY, strings);
		SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 6);
	}
	TestLog(OPTIM, "tPosadka", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}
	
stock farm_OnPlayerLeaveCheckpoint(playerid)
{	//для фермеров STEP6
	if(PlayerInfo[playerid][pJob] != FARMER) return 1; 
	if(CP[playerid] == CP_FARMER && FermaStatus == 1 && PlaceSeed[playerid] != 0)
	{
	    //не уверен что это ф-ия правильно отработает
		if( !IsValidObjectEx(SeedObject[PlaceSeed[playerid]-1]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не посадили кустик !");
			return 1;
		}
		if(FermerStatus[playerid] == 1)
		{   //на всякий случай, если игроку удастся выйти с саженцем из чекпоинта
		    //то не запускать рост куста
			//FermerStatus[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   Вы не посадили кустик !");
			return 1;
			//if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) RemovePlayerAttachedObject(playerid, 3);
		}

		new Float:x,Float:y,Float:z;
        GetObjectPos(SeedObject[PlaceSeed[playerid]-1], x, y, z);
        MoveObjectEx(SeedObject[PlaceSeed[playerid]-1], x, y, 130.6279, 0.1);
		StartMoveBushCounter ++;

		//ИНФОРМИРОВАНИЕ
		////new strings[MAX_STRING];
		//format(strings, sizeof(strings), "   Кустик %d[%d] пошёл расти", PlaceSeed[playerid], SeedObject[PlaceSeed[playerid]-1]);
		//SendClientMessageToAll(COLOR_GREY, strings);
		//SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 9);

		DisablePlayerCheckpointEx(playerid);
		PlaceSeed[playerid] = 0;
		LastObjectX[playerid] = 0.0;
		LastObjectY[playerid] = 0.0;

		//gOccupiedSeedPlace[PlaceSeed[playerid]-1] = 0;//потому что место осталось занято

		if(	TakenSeedCounter >= PlantedSeedCounter &&//если кол-во взятых и посаженных совпало
			PlantedSeedCounter >= StartMoveBushCounter &&//если кол-во посаженных и запущенных совпало
			StartMoveBushCounter >= MAX_POLE)//если кол-во запущенных равно максимуму поля
		{
   			FermaStatus = 2;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(spectateid[i] != MAX_PLAYERS-1) continue;
			    if(PlayerInfo[i][pJob] != FARMER) continue;
			    if(!gJobDuty[i]) continue;

				SendClientMessage(i, COLOR_GREEN, "Работодатель: {0080FF}Всё поле засеяно. Ждите когда вырастут кусты.");
	        }
		}
		UpdateFarm();
  	}
  	return 1;
}

stock farmer_OnObjectMoved(objectid)//для фермеров STEP8
{

	if( (FermaStatus == 1 || FermaStatus == 2)
		&& IsSeedObject(objectid) && StopMoveBushCounter < MAX_POLE)
	{
		StopMoveBushCounter ++; UpdateFarm();
	}//подсчитываем кол-во выросших кустов
	
	if( (FermaStatus == 1 || FermaStatus == 2) && //если ферма в статусе созревания
		TakenSeedCounter == PlantedSeedCounter && //кол-во взятых равно кол-ву посаженных саженцев
		PlantedSeedCounter == StartMoveBushCounter && //кол-во посаженных саженцев равно кол-ву движущихся кустов
		StartMoveBushCounter == StopMoveBushCounter &&//кол-во движущихся кустов равно кол-ву остановившехся кустов
		StopMoveBushCounter == MAX_POLE)// кол-ву остановившехся кустов равно максимальному кол-ву поля
	{
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			//if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1) continue;
		    if(PlayerInfo[i][pJob] != FARMER) continue;
		    if(!gJobDuty[i]) continue;
		    
			PlaySoundForPlayer(i, SOUND_AIR_HORN_L);

			CP[i] = 0;
			PlaceSeed[i] = 0;
			FermerStatus[i] = 0;
			LastObjectX[i] = 0.0;
			LastObjectY[i] = 0.0;
		    
			SendClientMessage(i, COLOR_GREEN, "Работодатель: {0080FF}Урожай созрел, пора собирать");
			SendClientMessage(i, COLOR_GREY, "   Идите на доллар и снимите рубашку, чтобы собирать на голое тело");
			SendClientMessage(i, COLOR_GREY, "   Косить коноплю нужно в той же последовательности !");
        }
	    FermaStatus = 3; //Статус фермы 3 - косьба
    	UpdateFarm();
	}
}

stock farmer_OneSecondTimers(playerid)
{//вызывается из OneSecondTimers
	if(PlayerInfo[playerid][pJob] != FARMER) return 1;
	if(!gJobDuty[playerid]) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;

	if(FermaStatus == 3)// косьба кустов на ферме
	{
		if(GetPlayerSkin(playerid) != 90 && GetPlayerSkin(playerid) != 162) return 1;

	    if(	!(GetPlayerSkin(playerid) == 162 && IsPlayerApplyAnimation(playerid, "RUN_OLD")) && //если игрок бежит
	    	!(GetPlayerSkin(playerid) == 90 && IsPlayerApplyAnimation(playerid, "WOMAN_RUN")) && //если игрок бежит
			!(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && nCarModel[playerid] == 532 && PlayerInfo[playerid][pFarmSkill] >= 400) )//и игрок не в комбайне
		{//то не скашивать
			return 1;
		}

		CrashDetected[playerid] = 36;

		if(	FermaStatus == 3 &&//если ферма в статусе косьбы
			TakenSeedCounter == PlantedSeedCounter &&
			PlantedSeedCounter == StartMoveBushCounter &&
			StartMoveBushCounter == StopMoveBushCounter &&
			StopMoveBushCounter == MowingBushCounter &&
			MowingBushCounter == MAX_POLE) //для фермеров STEP12
		{
			FermaStatus = 4;

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				//if(i == playerid) continue;
				if(spectateid[i] != MAX_PLAYERS-1) continue;
			    if(PlayerInfo[i][pJob] != FARMER) continue;
			    if(!gJobDuty[i]) continue;
				SendClientMessage(i, COLOR_GREEN, "Работодатель: {0080FF}Урожай скошен. Принимайтесь за сбор снопов.");
	        }
		    UpdateFarm();
	   	}
	   	else if(MowingBushCounter < MAX_POLE)//для фермеров STEP11
	   	{
	   	    new Float: x, Float: y, Float: z;
			GetObjectPos(SeedObject[MowingBushCounter], x, y, z);
			if( IsPlayerInRangeOfPoint(playerid, 3.0, x, y, 128.6) || //128.6 - т.к. центр объекта находится под землёй
				(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInRangeOfPoint(playerid, 5.0, x, y, 128.6)) )
			{
		    	MowingBushCounter ++;
				new pickupid = SetPickupEx(2901, 23, x, y, 128.6);
				if(PlayerInfo[playerid][pAdmin] > 0)
				{
					format(strings, sizeof(strings), "%s скосил %d[SetPickupID:%d DestroyObjectID:%d] кустик конопли.", PlayerName(playerid), MowingBushCounter, pickupid, SeedObject[MowingBushCounter-1]);
					//SendClientMessage(playerid, COLOR_GREY, strings);
					SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 6);					
				}
		    	DestroyObjectEx(SeedObject[MowingBushCounter-1], 24);

				FermerStatus[playerid] = 0;
				LastObjectX[playerid] = 0.0;
				LastObjectY[playerid] = 0.0;

		    	GivePlayerMoneyB(fsbiz+52, playerid, SBizInfo[52][sbSalary]);//JOBPRICE);
			    SBizInfo[52][sbTill] -= SBizInfo[52][sbSalary];//JOBPRICE;
			    SBizInfo[52][sbImport] += SBizInfo[52][sbSalary];
			    UpdateFarm();
			}
	   	}
	}
	else if(FermaStatus == 4)
	{//сбор урожая (снопов)
		if(FermerStatus[playerid] == 0) return 1;
		//if(GetPlayerWalkingStyle(playerid) != WALK_OLD)
	    if(	IsPlayerApplyAnimation(playerid, "FALL_back") ||
			IsPlayerApplyAnimation(playerid, "FALL_collapse") ||
			IsPlayerApplyAnimation(playerid, "FALL_fall") ||
			IsPlayerApplyAnimation(playerid, "FALL_front") ||
			IsPlayerApplyAnimation(playerid, "FALL_glide") ||
			IsPlayerApplyAnimation(playerid, "FALL_land") ||
			IsPlayerApplyAnimation(playerid, "FALL_skyDive") ||
			IsPlayerApplyAnimation(playerid, "JUMP_glide") ||
			IsPlayerApplyAnimation(playerid, "JUMP_land") ||
			IsPlayerApplyAnimation(playerid, "JUMP_launch") ||
			IsPlayerApplyAnimation(playerid, "JUMP_launch_R") ||
			IsPlayerApplyAnimation(playerid, "WALK_OLD") ||
			IsPlayerApplyAnimation(playerid, "SPRINT_CIVI") ||
			IsPlayerApplyAnimation(playerid, "SPRINT_PANIC") ||
			IsPlayerApplyAnimation(playerid, "WEAPON_CROUCH") ||
			IsPlayerApplyAnimation(playerid, "FIGHTA_1") ||
			IsPlayerApplyAnimation(playerid, "FIGHTA_2") ||
			IsPlayerApplyAnimation(playerid, "FIGHTA_3")
	      )
	    {
			if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
			CrashDetected[playerid] = 35;

			//ClearAnimations(playerid, 1);
			//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

			//SeedPickup[TakenBushCounter] =
			SetPickupEx(2901, 23, LastObjectX[playerid], LastObjectY[playerid], 128.6);
			TakenBushCounter --;

			//ИНФОРМИРОВАНИЕ
			////new strings[MAX_STRING];
			format(strings, sizeof(strings), "Сноп возвращён. TakenSeedCounter: %d", TakenSeedCounter);
			//SendClientMessageToAll(COLOR_GREY, strings);
			SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 6);
			//SendClientMessage(playerid, COLOR_GREY, strings);

			FermerStatus[playerid] = 0;
			LastObjectX[playerid] = 0.0;
			LastObjectY[playerid] = 0.0;

		   	GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, -SBizInfo[52][sbSalary]);//-JOBPRICE);
    		SBizInfo[52][sbTill] += SBizInfo[52][sbSalary];//JOBPRICE);
			UpdateFarm();

	        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты уронил сноп!");
		}
	}
	return 1;
}

//для фермеров STEP16
stock FermaEnd(playerid)
{   //вызывается из OnPlayerPickUpPickup по координатам IsPlayerInRangeOfPoint(playerid, 2.1, -1210.1460,-1043.3667,128.3897)
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
	if(PlayerInfo[playerid][pJob] != FARMER) return 1;
	if(!gJobDuty[playerid]) return 1;
	if(FermerStatus[playerid])
	{//выполняется каждый раз при занесения снопа
		if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
		//ClearAnimations(playerid, 1);
		//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		//gJobDuty[playerid] = 0;
		CP[playerid] = 0;
		PlaceSeed[playerid] = 0;
		FermerStatus[playerid] = 0;
		LastObjectX[playerid] = 0.0;
		LastObjectY[playerid] = 0.0;

		DeliveredBushCounter ++;
		//----------------------------------------------------------------------
		//new strings[MAX_STRING];
		new skill, Fee;//money,
	   	PlayerInfo[playerid][pFarmSkill] ++;
		new level = PlayerInfo[playerid][pFarmSkill];
		if(level <= 50)
		{
		    //money = (100 + random(100));//деньги за
			if(level == 50)
			{
				Fee = (200 + random(100))*10; skill = 2; //гонорар за переход
				format(strings, sizeof(strings), "Bаш Навык Фермера теперь %d ! Гонорар {33AA33}$%d", skill, Fee);
				SendClientMessage(playerid, COLOR_GREEN, strings);
			}
		}
		else if(level > 50 && level <= 100)//2 Уровень
		{
		    //money = (200 + random(100));
			if(level == 100)
			{
				Fee = (300 + random(100))*10; skill = 3;
				format(strings, sizeof(strings), "Bаш Навык Фермера теперь %d ! Гонорар {33AA33}$%d", skill, Fee);
				SendClientMessage(playerid, COLOR_GREEN, strings);
			}
		}
		else if(level > 100 && level <= 200)//3 Уровень
		{
		    //money = (300 + random(100));
			if(level == 200)
			{
			    Fee = (400 + random(100))*10; skill = 4;
			    format(strings, sizeof(strings), "Bаш Навык Фермера теперь %d ! Гонорар {33AA33}$%d", skill, Fee);
			    SendClientMessage(playerid, COLOR_GREEN, strings);
			}
		}
		else if(level > 200 && level <= 400)//4 Уровень
		{
		    //money = (400 + random(100));
			if(level == 400)
			{
				Fee = RANDMONEY5*10; skill = 5;
				format(strings, sizeof(strings), "Bаш Навык Фермера теперь %d ! Гонорар {33AA33}$%d ! Вы можете управлять комбайном !", skill, Fee);
				SendClientMessage(playerid, COLOR_GREEN, strings);
			}
		}
		else if(level > 400)//5 Уровень
		{
		    //money = RANDMONEY5;
		}
		
		if(Fee > 0) GivePlayerMoneyB(fsbiz+52, playerid, Fee);
		//----------------------------------------------------------------------
		//заканчивая сбор
		SBizInfo[52][sbProducts] += 10;//1000;//добавляем на склад по 10 семян

	   	GivePlayerMoneyB(fsbiz+52, playerid, SBizInfo[52][sbSalary]);//JOBPRICE);
	    SBizInfo[52][sbTill] -= SBizInfo[52][sbSalary];//JOBPRICE;
	    SBizInfo[52][sbImport] += SBizInfo[52][sbSalary];

		if(	FermaStatus == 4 &&
			TakenSeedCounter == PlantedSeedCounter &&
			PlantedSeedCounter == StartMoveBushCounter &&
			StartMoveBushCounter == StopMoveBushCounter &&
			StopMoveBushCounter == MowingBushCounter &&
			MowingBushCounter == DeliveredBushCounter &&
			DeliveredBushCounter == MAX_POLE) //для фермеров STEP18
		{
			//ObjectIndex = 0;
			FermaStatus = 0;		// Статус фермы  0- ничего, 1- посадка, 2 - созревание, 3- косьба, 3- сбор урожая.
			SBizInfo[52][sbWorker] = 0;//FarmerCounter = 0;		//кол-во людей работающих на ферме
			TakenSeedCounter = 0;		// Счетчик взятых семян
			PlantedSeedCounter = 0;		// Счетчик посаженных семян
			StartMoveBushCounter = 0;	// Счетчик кустов запущенных
			StopMoveBushCounter = 0;	// Счетчик кустов выросших
			MowingBushCounter = 0;		// Счетчик кустов скошенных
			TakenBushCounter = 0;		// Счетчик собраных снопов
			DeliveredBushCounter = 0;	// Счетчик доставленных снопов
			for(new o=0; o<MAX_POLE; o++)
	       	{
       			gOccupiedSeedPlace[o] = 0;
       		}

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				//if(i == playerid) continue;
				//if(spectateid[i] != MAX_PLAYERS-1) continue;
			    if(PlayerInfo[i][pJob] != FARMER) continue;
			    if(!gJobDuty[i]) continue;//всем кто на дежурке был раздать скилы

	       		PlaceSeed[i] = 0;
				FermerStatus[i] = 0;
				LastObjectX[i] = 0.0;
				LastObjectY[i] = 0.0;

			    SetPlayerSkinEx(i, PlayerInfo[i][pModel]);

				SBizInfo[52][sbWorker] --;//FarmerCounter --;
				if(SBizInfo[52][sbWorker] <= 0) SBizInfo[52][sbWorker] = 0;//FarmerCounter = 0;
			    DisablePlayerCheckpointEx(i);
			    PlayerInfo[i][pJob] = 0; gJobDuty[i] = 0;
				if(i != playerid) GivePlayerMoneyB(fsbiz+52, i, SBizInfo[52][sbSalary]);//JOBPRICE);//должно быть после PlayerInfo[i][pJob] = 0; чтобы выполнилось обучение
				SBizInfo[52][sbTill] -= SBizInfo[52][sbSalary];//JOBPRICE;
				SBizInfo[52][sbImport] += SBizInfo[52][sbSalary];
				//подбор пикапа должен быть после

				if(IsPlayerAttachedObjectSlotUsed(i, DUTY_SLOT)) RemovePlayerAttachedObject(i, DUTY_SLOT);
				//ClearAnimations(playerid, 1);
				//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				SendClientMessage(i, COLOR_GREEN, "Работодатель: {0080FF}Ты завершил работу на ферме !!");
				SendClientMessage(i, COLOR_GREEN, "Работодатель: {0080FF}Сбор закончен");

				//OnPlayerInCheckLocation(i, PlayerPickUpPickup);
	        }
		}
	}
	return 1;
}

//==============================================================================

stock farmer_OnPlayerKeyStateChange(playerid)
{
	if(PlayerInfo[playerid][pJob] != FARMER) return 1; 
	if(!gJobDuty[playerid])  return 1; 
	//if(!gJobDuty[playerid]) return 1;
	if(FermaStatus != 4) return 1;
	if(!FermerStatus[playerid]) return 1;

	if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
	//ClearAnimations(playerid, 1);
	ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	//SeedPickup[TakenBushCounter] =
	new pickupid = SetPickupEx(2901, 23, LastObjectX[playerid], LastObjectY[playerid], 128.6);
	//ИНФОРМИРОВАНИЕ
	//new strings[MAX_STRING];
	if(PlayerInfo[playerid][pAdmin] > 0)
	{
	   	format(strings, sizeof(strings), "   Ты бросил %d[%d] сноп конопли (LastObjectX: %.4f, LastObjectY: %.4f)",
		   	TakenBushCounter, pickupid, LastObjectX[playerid], LastObjectY[playerid]);
	}
	else
	{
	   	format(strings, sizeof(strings), "   Ты бросил %d[%d] сноп конопли", TakenBushCounter, pickupid);
	}
	SendClientMessage(playerid, COLOR_GREY, strings);
		
	FermerStatus[playerid] = 0;
	LastObjectX[playerid] = 0.0;
	LastObjectY[playerid] = 0.0;
			
	TakenBushCounter --;
			
   	GivePlayerMoneyB(fsbiz+52, playerid, -SBizInfo[52][sbSalary]);//JOBPRICE);
  	SBizInfo[52][sbTill] += SBizInfo[52][sbSalary];//JOBPRICE;
	UpdateFarm();
	return 1;	
}	

stock farmer_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_DRIVER) //buggy dont finnish  //если ID нового состояния равно состоянию за рулём
	{	//если ID нового состояния равно состоянию 2
//для фермеров
		//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
		new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
		if(modelid == 532)//для фермеров
		{
		    if(PlayerInfo[playerid][pJob] == FARMER && PlayerInfo[playerid][pFarmSkill] >= 400) { }
		    else
			{
				//RemovePlayerFromVehicleEx(playerid);
				SendClientMessage(playerid, COLOR_GREY, "   Чтобы управлять комбайном вам нужен скилл 5 !");
				return 1;
			}
		}
		else FarmerExitAndDeath(playerid);//должна быть всегда перед FixJobCounter
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{   //если ID нового состояния равно состоянию 3 - пассажир
		//if(FermaStatus == 1 || FermaStatus == 2)
		FarmerExitAndDeath(playerid);//должна быть всегда перед FixJobCounter
	}
	else if(newstate == PLAYER_STATE_WASTED)//выполняется сразу после смерти игрока
	{   //если ID нового состояния равно состоянию 7
		//для фермеров STEP0
		FarmerExitAndDeath(playerid);//должна быть всегда перед FixJobCounter
	}
	return 1;
}

//для фермеров STEP0
stock FarmerExitAndDeath(playerid)
{   //вызывается из OnPlayerStateChange и OnPlayerDisconnect(playerid, reason)
	if(PlayerInfo[playerid][pJob] != FARMER) return 1;
    //if(!gJobDuty[playerid]) return 1;

    format(strings, sizeof(strings), "Работодатель: {0080FF}%s[%d]{33AA33} покинул ферму.", PlayerName(playerid), playerid);

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//if(spectateid[i] != MAX_PLAYERS-1) continue;
	    if(PlayerInfo[i][pJob] != FARMER) continue;
	    if(!gJobDuty[i]) continue;
		SendClientMessage(i, COLOR_GREEN, strings);
	}

	if(FermaStatus == 1)
	{//1 - посадка
//если игрок посадил саженец, УМЕР, но не покинул чекпоинт
		/*if(CP[playerid] == CP_FARMER)
		{
		    DisablePlayerCheckpointEx(playerid); CP[playerid] = 0;
		}*/
	  	if(FermerStatus[playerid] == 1)//освобождается через 6 сек как только игрок вошёл в чекпоинт
	  	{   //если объект типа в руках
//если игрок взял саженец, но не посадил и вышел
//если игрок взял саженец, но не посадил и вышел когда поле засеяно было
			if(PlaceSeed[playerid] != 0 && gOccupiedSeedPlace[PlaceSeed[playerid]-1] != 0)
			{//если место под саженец определено и занято
				if( IsValidObjectEx(SeedObject[PlaceSeed[playerid]-1]))
				{   //если объект существует по данному месту
		//если игрок начал садить, но не покинул чекпоинт и вышел
		//если игрок покинул чекпоинт, но не посадил и вышел
				 	//if(IsObjectMoved[SeedObject[PlaceSeed[playerid]-1]] == 0)//, но   (сработает также когда куст уже вырос)
					if( !IsObjectMoving(SeedObject[PlaceSeed[playerid]-1]) )
				 	{//если объект не запустился то запустить куст на рост
						new Float:x,Float:y,Float:z;
				        GetObjectPos(SeedObject[PlaceSeed[playerid]-1], x, y, z);
				        MoveObjectEx(SeedObject[PlaceSeed[playerid]-1], x, y, 130.6279, 0.1);
						StartMoveBushCounter ++;

						if(PlayerInfo[playerid][pAdmin] > 0)
						{
							//ИНФОРМИРОВАНИЕ
							////new strings[MAX_STRING];
							format(strings, sizeof(strings), "Запущен куст. StartMoveBushCounter(place:%d, object:%d)", PlaceSeed[playerid], SeedObject[PlaceSeed[playerid]-1]);
							//SendClientMessageToAll(COLOR_GREY, strings);
							SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 6);
							//SendClientMessage(playerid, COLOR_GREY, strings);
						}
						//gOccupiedSeedPlace[PlaceSeed[playerid]-1] = 0;//опустить флаг
						//PlaceSeed[playerid] = 0;//освободить место
					}
			  	}
			  	else    //если объект НЕ установлен
		  	    {
					if(PlayerInfo[playerid][pAdmin] > 0)
					{
						//ИНФОРМИРОВАНИЕ
						////new strings[MAX_STRING];
						format(strings, sizeof(strings), "Сажанец возвращён. TakenSeedCounter: %d(place:%d, OccupiedSeedPlace:%d)", TakenSeedCounter, PlaceSeed[playerid], gOccupiedSeedPlace[PlaceSeed[playerid]-1]);
						//SendClientMessageToAll(COLOR_GREY, strings);
						//SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 9);
						SendClientMessage(playerid, COLOR_GREY, strings);
					}
					TakenSeedCounter --; SBizInfo[52][sbProducts] ++;//вернуть саженец
					gOccupiedSeedPlace[PlaceSeed[playerid]-1] = 0;//опустить флаг
					PlaceSeed[playerid] = 0;//освободить место					
				}
			}
			FermerStatus[playerid] = 0;
	  	}
//если игрок просто умер
		//----------------------------------------------------------------------
		if(	TakenSeedCounter == PlantedSeedCounter &&//если кол-во взятых и посаженных совпало
			PlantedSeedCounter == StartMoveBushCounter &&//если кол-во посаженных и запущенных совпало
			StartMoveBushCounter == MAX_POLE)//если кол-во запущенных равно максимуму поля
		{//то автоматом перейти ферме в режим 2
   			FermaStatus = 2;

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(spectateid[i] != MAX_PLAYERS-1) continue;
			    if(PlayerInfo[i][pJob] != FARMER) continue;
			    if(!gJobDuty[i]) continue;
				SendClientMessage(i, COLOR_GREEN, "Работодатель: {0080FF}Всё поле засеяно. Ждите когда вырастут кусты.");
	        }
		}
	}
	else if(FermaStatus == 2)
	{// Статус фермы: 2 - созревание

	}
	else if(FermaStatus == 3)
	{// Статус фермы: 3 - косьба

	}
//если игрок взял сноп, но не донес до ангара и вышел
	else if(FermaStatus == 4)
	{   // Статус фермы:4 - сбор урожая.
		if(FermerStatus[playerid] == 1)
		{
			//SeedPickup[TakenBushCounter] =
			SetPickupEx(2901, 23, LastObjectX[playerid], LastObjectY[playerid], 128.6);
			TakenBushCounter --;

			if(PlayerInfo[playerid][pAdmin] > 0)
			{
				//ИНФОРМИРОВАНИЕ
				////new strings[MAX_STRING];
				format(strings, sizeof(strings), "   TakenSeedCounter: %d", TakenSeedCounter);
				//SendClientMessageToAll(COLOR_GREY, strings);
				//SendAllAdminMessage(COLOR_LIGHTBLUE, strings, 9);
				SendClientMessage(playerid, COLOR_GREY, strings);
			}

			/*FermerStatus[playerid] = 0;
			LastObjectX[playerid] = 0.0;
			LastObjectY[playerid] = 0.0;*///обнуление идёт при входе/выходе

			/*if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT))
			{
				RemovePlayerAttachedObject(playerid, DUTY_SLOT );
			}*/
		}
	}
	PlaceSeed[playerid] = 0;

	DisablePlayerCheckpointEx(playerid); 
	//SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);

	PlayerInfo[playerid][pJob] = 0;	gJobDuty[playerid] = 0;
	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты завершил работу на ферме !!!");
	UpdateFarm();
	//print("FarmerExitAndDeath");
	return 1;
}

//для фермеров
stock IsSeedObject(objectid)
{   //если это объект фермы, то вернуть 1.
	for(new o; o<MAX_POLE; o++)
	{
		if(objectid == SeedObject[o]) return 1;
	}
	return 0;
}

//для фермеров начало
stock UpdateFarm() // Обновление склада фермеров
{
    new strtmp[317 + 10+3*7+10];
    format(strtmp, sizeof(strtmp), "[ Склад ]\n\n{FF6600}Саженцев: {FFFFFF}%d\
\n{FF6600}Взято: {FFFFFF}%d\
\n{FF6600}Посажено: {FFFFFF}%d\
\n{FF6600}Кустов: {FFFFFF}%d\
\n{FF6600}Выросло: {FFFFFF}%d\
\n{FF6600}Скошено: {FFFFFF}%d\
\n{FF6600}Собрано: {FFFFFF}%d\
\n{FF6600}Доставлено: {FFFFFF}%d\
\n{FF6600}Баланс {33AA33}$%d\
\n{0080FF}Информация (Use: /finfo)",
		SBizInfo[52][sbProducts],
		TakenSeedCounter,
		PlantedSeedCounter,
		StartMoveBushCounter,
		StopMoveBushCounter,
		MowingBushCounter,
		TakenBushCounter,
		DeliveredBushCounter,
		SBizInfo[52][sbTill]);
	UpdateDynamic3DTextLabelText(FarmInfo, 0xEEEE88FF, strtmp);
	//SaveBiz(52);
}



//ShowPlayerDialogGap(playerid, 70, DIALOG_STYLE_MSGBOX, "Ганжа ФЕРМА", dlgitem, "Нет", "Да");
stock ferma_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != FERMA_DIALOG) return 1;//для дальнобойщиков STEP4
		SetPVarInt(playerid, "gShowDialog", -1);
		if(response) return 1;
//для наркодилеров STEP2
		new msgitem[256+1];
		//GameTextForPlayerEx(playerid, "~y~Welcome to the ~n~Factory~n~~b~Use (~w~/materials get~b~)~n~~g~to take a Materials Packages", 5000, 3);
		new level = PlayerInfo[playerid][pDrugsSkill];
		new package;//для экономики
		if(level < 250) { package = 30; }
		else if(level >= 250 && level < 500) { package = 34; }
		else if(level >= 500 && level < 1000) { package = 37; }
		else if(level >= 1000 && level < 2000) { package = 39; }
		else if(level >= 2000) { package = 40; }
		//new price = package * pricepackage;//40*7=280 на 1 скиле
		//new price = package*compcost*(100+SBizInfo[52][sbSellProd])/100;//потеря точности
		new price = floatround(package*compcost*(100+SBizInfo[52][sbSellProd])/100.0, floatround_ceil);
//new pricepackage = 7;//цена пакета
//new amountmaterials = 30;//кол-во матеров в одном пакете
		//цена коробки 30*7=$210 за amountmaterials*package = 30*30=900 грамм на 1 скиле
		if(GetPlayerMoneyH(playerid) > price)
		{
		    format(msgitem, sizeof(msgitem), "* Вы купили {FFFFFF}%d{0080FF} Пакетов с Коноплёй за {33AA33}$%d.", package, price);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);

			checktimedeliver[playerid] = GetTickCount();
		    format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", 60);//MinTimeCheckpoint[playerid]/1000);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

		    GivePlayerMoneyH(fsbiz+52, playerid, -price);
		    //SBizInfo[9][sbTill] += price/2;//перечислили деньги в биз General Store за покупку пакетов наркодилеров
		    //BizInfo[0][bProducts] += price/2;//перечислили деньги в БАНК
		    PlayerInfo[playerid][pMats] += amountmaterials*package;

		    SBizInfo[52][sbProducts] -= package;
		    SBizInfo[52][sbTill] += price;//перечислили деньги на ферму
		    SBizInfo[52][sbExport] += price;
		    //MatsHolding[playerid] = package;
		}
		else
		{
		    format(msgitem, sizeof(msgitem), "   У Вас нет $%d для получения %d пакетов с Коноплёй !", price, package);
		    SendClientMessage(playerid, COLOR_GREY, msgitem);
		}
		return 1;
}


