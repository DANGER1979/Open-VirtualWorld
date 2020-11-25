//#include <a_samp>
//#include <FCNPC>
	
#define MAX_BODYGUARDS 6
#define DEBUG

#define MAX_BODYPART_NAME 10
#define BG_INVALID_SLOT_ID -1

static
	gPlayerNpc[MAX_PLAYERS][MAX_BODYGUARDS],
	gNpcSlot[MAX_PLAYERS],
	gNpcPlayer[MAX_PLAYERS],
	gFollowTimer[MAX_PLAYERS],
	gFollowTarget[MAX_PLAYERS],
	STREAMER_TAG_3D_TEXT_LABEL:gNpcText3D;
	

//new gInRacing[MAX_PLAYERS];
new gCountdowntimer;//для гонок идентификатор таймера для старта
new endracetimer;

//для меню
new RaceMenuItem[41*(26 + 2+20)];//new Menu:mRacing;



//для гонок
#define MAX_RACES 42//200

new gMaxCheckpoints = 0;//счётчик общего кол-во CP на данной трасе
new RacingMenu = 0;//опустили флаг - вышел из меню для входа в меню только одного игрока
new PrizeFund = 0;

new GridCount = 0;//позиция гонщиков раставленных по сетке
new RaceStartTime = 0;//значение процесорных тиков
new gRaceStarted = 0;//флаг - начало гонки
new FinishedCount = 0;//кол-во игроков на финише
new rMinutes = 0;
new rSeconds = 0;
new GridIndex = 0;//переключатель чет, нечет
new TotalRacers = 0;
new Rate = 0;//Ставка на гонке
new TotalRate = 0;//Общая Ставка на гонке

#define MAX_RACECHECKPOINTS 100
new Float:RaceCheckpoints[MAX_RACECHECKPOINTS][3];
new RaceCheckpointsCount[MAX_RACECHECKPOINTS];
new gRaceMaker[20];//для проверки модели
new TrackName[32];//!!! 256
new RaceNames[MAX_RACES][20];//20//массив названий гонок
new SelectRace[20];
new Float:GridPos[8];
new gCars[6];//модели машин для гонок

//для гонок настройки
new racecountdown = 15;//время старта
new TrackTime = 240;
new WorldTime = 15;
new Weather = 1;
new RaceType = 1;//гонки по земле

#define HIGH_SCORE_SIZE 5  //Max number of ppl on the highscore list
enum rStats
{	//Highscore enum
	rName[20],
	rTime,
	rRacer[MAX_PLAYER_NAME],//25
	rModelCar[32],//MAX_VEHICLES_NAME
	rPrizeFund//призовой фонд за установку нового рекорда
};
new RaceInfo[HIGH_SCORE_SIZE][rStats];//объявляем новый массив


stock race_OnPlayerDisconnect(playerid)
{
	RacingMenu = 0;//опустили флаг - вышел из меню обнулим на всякий случай
	if(gInRacing[playerid])// && TotalRacers > 0
	{
		TotalRacers --;//для гонок если игрок покинул гонку
	}
	NPC_Disconnect(playerid);
}
stock NPC_Disconnect(playerid)
{
	if (!BG_IsValid(playerid)) {
		for (new slot; slot < MAX_BODYGUARDS; slot++) {
			if (BG_IsValidSlot(playerid, slot)) {
				BG_Delete(playerid, slot);
			}
		}
	}
}

//stock LoadRaceList()//для гонок STEP0
stock race_OnGameModeInit()//для гонок STEP0
{   //загрузха списка гонок из OnGameModeInit
	new time = GetTickCount();
	if(fexist("Race/racenames.cfg"))//Проверяет, есть ли указанный файл в папке с Вашими скриптами.
	{   // 	1 - если файл существует, - если нет
		new File:file = fopen("Race/racenames.cfg", io_read);
		new line[20];
		while(fread(file, line, sizeof(line), false))
		{//Чтение фала до тех пор пока в нем есть строки:
     		new iidx;
			RaceNames[countrace] = strtok(line, iidx);//Сканирует строку line на наличие символа 'пробел'
//printf("Race - %s[%d]", RaceNames[countrace], countrace);
			//и возвращает аргумент номер которого указан в переменной (&index).
			//Применяется в основном для команд, чтобы чтобв получать параметры после пробела.
			//cmdtext - Строка, которую нужно разделить.
			//idx - Номер аргумента который вы хотите вернуть.
			//Возвращает  аргумент номер которого указан в переменной idx.
			new trackname[13+32];
			format(trackname, sizeof(trackname), "Race/%s.race", RaceNames[countrace]);
            if(fexist(trackname))
			{
             	//printf("Race%d - %s.race", countrace, RaceNames[countrace]);
			}
			else
			{
				format(strings, sizeof(strings), "Error1: in racenames.cfg: Line%d - %s.race", countrace, RaceNames[countrace]);
				Log(ERROR, strings);
			}
			countrace ++;
		}
		fclose(file);
	}
	NPC_Init();
	//==========================================================================
	//mRacing = CreateMenuEx("Racing", 1, 10.0, 120.0, 100.0, 100.0);
//print("Creating RacingMenu:");
	new itemmenu[26 + 2+20];
	for(new r=0; r<countrace; r++)
	{
	    //AddMenuItem(mRacing, 0, RaceNames[i]);
//printf("Racing: %s[%d]", RaceNames[r], r);
		//format(itemmenu, sizeof(itemmenu), "%d\t%s\n", i, RaceNames[i]);
		format(itemmenu, sizeof(itemmenu), "{FFFFFF}%d \t{00FF00}%s\n", r+1, RaceNames[r]);
		strins(RaceMenuItem, itemmenu, strlen(RaceMenuItem), strlen(itemmenu));
//strins(strings[],const substr[],pos,maxlength=sizeof(strings))
//strings[] 	Строка, в которую вы хотите вставить подстроку.
//const substr[] 	Подстрока, которую вы хотите вставить в строку.
//pos 	Позиция с которой начинается вставка,
//обычно это конец строки которую вы наращиваете, т.е. strlen(strings)
//maxlength=sizeof(strings) 	Максимальный вставляемый размер подстроки
//можно не использовать, т.к. ни на что не влияет
	}
	printf("12/17. [Загрузка гонок]: Было загружено - %d, потрачено - %d (ms)", countrace, GetTickCount() - time);//new time = GetTickCount();
}


stock NPC_Init()
{
	for (new playerid; playerid < MAX_PLAYERS; playerid++) {
		for (new slot; slot < MAX_BODYGUARDS; slot++) {
			gPlayerNpc[playerid][slot] = INVALID_PLAYER_ID;
		}

		gNpcSlot[playerid] = BG_INVALID_SLOT_ID;
		gNpcPlayer[playerid] = INVALID_PLAYER_ID;
		gFollowTimer[playerid] = 0;
		gFollowTarget[playerid] = INVALID_PLAYER_ID;
	}
}

stock NPC_Exit()
{
	for (new playerid; playerid < MAX_PLAYERS; playerid++) {
		if (BG_IsValid(playerid)) {
			BG_DeleteByID(playerid);
		}
	}
}



//stock RaceMenu(playerid)//для гонок STEP1
//stock RaceMenu(playerid)//для гонок STEP1
stock race_Menu(playerid)//для гонок STEP1
{
	//if(TEST[MAX_FUNCTION-1] == 1) { return 1; }
   	if(!IsPlayerInAnyVehicle(playerid))
	{
		//LIST(playerid);
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства !");
		return 1;
	}
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства !");
		return 1;
	}
	if(PlayerInfo[playerid][pInt] != 0)
	{
		//LIST(playerid);
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться НЕ в интерьере !");
		return 1;
	}
	if(gRaceStarted)
	{   //если игрок ещё не присоединился ни к какой гонке и гонка ещё не началась и таймер больше 3
		SendClientMessage(playerid, COLOR_GREY, "   Гонка уже началась. Подождите окончания гонки.");
		return 1;
	}
	if(gInRacing[playerid])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы уже участвуете в гонке.");
		return 1;
	}
	/*if(gOnDuty[playerid])
	{   //если коп и не на дежурстве и не в розыске
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке на службе.");
		return 1;
	}
	if(gJobDuty[playerid])
	{   //если коп и не на дежурстве и не в розыске
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке на дежурстве.");
		return 1;
	}
	if( IsInIntCar(nCarID[playerid]) )
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке на дерби-тачках.");
		return 1;//SLAdd // && HireCarID[playerid] == MAX_VEHICLES-1
	}
	if( IsInRentCar(nCarID[playerid]) && HireCarID[playerid] == MAX_VEHICLES-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы не можете участвовать в гонке на арендованых тачках, пока не оплатите аренду!");
		return 1;
	}
	if(PlayerInfo[playerid][pLevel] < 2)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке на первом уровне !");
		return 1;
	}
	if(WantedPoints[playerid] > 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке находясь в розыске !");
		return 1;
	}
    if(PlayerCuffed[playerid] < MAX_PLAYERS-1)
    {
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке находясь в наручниках !");
        return 1;
    }
	if(PlayerTied[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке связанным !");
		return 1;
	}
	if(PlayerInfo[playerid][pJailed] > 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке под арестом !");
		return 1;
	}
	if( IsPlayerInArea(playerid, specialzone[10]) )
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке пока находитесь в паркинге !");
		return 1;
	}
	if( gInAdventure[playerid] != 0 )
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке пока проходите квест !");
		return 1;
	}*/
	/*if(gLoading[playerid] || gUnLoading[playerid])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Подождите окончания загрузки/выгрузки !");
		return 1;
	}
	if(PlayerInfo[playerid][pJob] == TRUCKER && CP[playerid] == CP_TRUCKER)
	{ 
	   	SendClientMessage(playerid, COLOR_GREY, "   Вы взяли груз ! Поторопитесь !");
	   	return 1;
	}
	if(Rate > GetPlayerMoneyH(playerid))
	{   //если сумма больше денег на руках
		SendClientMessage(playerid, COLOR_GREY, "   У вас недостаточно денег на руках!");
		return 1;
	}*/
	//new modelid = VehInfo[nCarID[playerid]][cModel];//GetVehicleModel(nCarID[playerid]);
	/*for(new seat=1; seat<=VehicleArray[modelid-400][SeatID]-1; seat++)//500 в автобусах
	{
	    if( GetSeatVehiclePlayer(nCarID[playerid], seat) != INVALID_PLAYER_ID)
	    {   //если пассажирские места заняты кем-то
	    	new passenger = GetSeatVehiclePlayer(nCarID[playerid], seat);//получить ID Того кто сидит на этом месте
	    	if(AFK_IdleTime[passenger] > 5)
	    	{   //если человек в АФК выкинуть его
				//RemovePlayerFromVehicleEx(passenger);//не работает для АФК игроков
				removePlayerFromVehicle(passenger);
			}
			else RemovePlayerFromVehicleEx(passenger);//не работает для АФК игроков
			SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке c пассажирами ! Попробуйте снова.");
			return 1;
	    }
    }*/
	//----------------------------------------------------------
	if(TotalRacers > 0 && racecountdown > 3)
	{    //если кол-во гонщиков больше 0 и таймер больше 3
		if(!strcmp(gRaceMaker, "AVANGARD", true))
		{   //если в файле гонки установлено слово AVANGARD
			if(	nCarModel[playerid] != gCars[0] &&
				nCarModel[playerid] != gCars[1] &&
				nCarModel[playerid] != gCars[2] &&
				nCarModel[playerid] != gCars[3] &&
				nCarModel[playerid] != gCars[4] &&
				nCarModel[playerid] != gCars[5])
			{   //то проводим проверку на модель машины игрока
				SendClientMessage(playerid, COLOR_GREY, "   Ваше транспортное средство не соответствует данному типу гонки !");
				return 1;
			}
		}
		TogglePlayerControllableEx(playerid, 0);//обездвиживает игрока
		gInRacing[playerid] = 1;//вошёл в гонку
		TotalRacers += 1;//увеличить кол-во гонщиков
		TotalRate += Rate;//подсчитывам общую ставку
		racecountdown = 21;//начать заново отсчёт
		GivePlayerMoneyH(frace, playerid, -Rate);

		//new strings[MAX_STRING];
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(GetPVarInt(i, "gSport") == 0)
				//&& WantedPoints[i] <= 0)
			{
				format(strings, sizeof(strings), "%s присоединился к гонке %s",
					PlayerName(playerid),SelectRace);
				SendClientMessage(i, COLOR_BLUEGREEN, strings);
			}
		}
		GivePlayerMoneyH(fsbiz+11, playerid, -SBizInfo[11][sbEntranceCost]);
		//OnGangsExtortionSBiz(11, SBizInfo[11][sbEntranceCost]);
		SBizInfo[11][sbProducts] --;

		GridSetupPlayer(playerid);//для установки на старте
	}
	else if(TotalRacers == 0 && RacingMenu == 0)
	{   //иначе если ты первым стартуешь гонку
		GivePlayerMoneyH(fsbiz+11, playerid, -SBizInfo[11][sbEntranceCost]);
		//OnGangsExtortionSBiz(11, SBizInfo[11][sbEntranceCost]);
		SBizInfo[11][sbProducts] --;

		MenuOperation[playerid] = 51;
		ShowPlayerDialogGap(playerid, RACE_DIALOG, DIALOG_STYLE_LIST, "Select Race", RaceMenuItem, "OK", "Cancel");
//ИНФОРМИРОВАНИЕ
//format(strings, sizeof(strings), "strlen(RaceMenuItem): %d, sizeof(RaceMenuItem): %d", strlen(RaceMenuItem), sizeof(RaceMenuItem));
//ABroadCast(COLOR_MAROON, strings, 9);
	}
	else
	{
		format(strings, sizeof(strings), "   Дождитесь запуска гонки. RacingMenu=%d. TotalRacers=%d. racecountdown=%d",
			RacingMenu, TotalRacers, racecountdown);
		SendClientMessage(playerid, COLOR_GREY, strings);
	}
	return 1;
}
stock race_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != RACE_DIALOG) return 1;//для гонок STEP2 //Select Race
//ShowPlayerDialogGap(playerid, RACE_DIALOG, DIALOG_STYLE_LIST, "Select Race",RaceMenuItem, "OK", "Cancel");
//ShowPlayerDialogEx(playerid, RACE_DIALOG, DIALOG_STYLE_INPUT, "Race Rate", "Введите Вашу Ставку. \nСтавка может быть не ниже 5000$ и не выше 50000$ \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	if(response)
	{   //создание гонки
		
		new msgitem[256+1];				
		if(gInRacing[playerid] || gRaceStarted != 0) return 1;
		//если игрок ещё не присоединился ни к какой гонке и гонка ещё не началась
		if(MenuOperation[playerid] == 51)
		{
	 		RacingMenu = 1;//вошел в меню
			LoadRace(RaceNames[listitem]);//для гонок STEP3 //для загрузки гонки
			if(!strcmp(gRaceMaker, "AVANGARD", true))
			{   //если в файле гонки установлено слово AVANGARD
				if(	nCarModel[playerid] != gCars[0] && nCarModel[playerid] != gCars[1] &&
					nCarModel[playerid] != gCars[2] && nCarModel[playerid] != gCars[3] &&
					nCarModel[playerid] != gCars[4] && nCarModel[playerid] != gCars[5])
				{   //то проводим проверку на модель машины игрока
					//TogglePlayerControllableEx(playerid, 1);//освободить
					RacingMenu = 0;//вышел из меню
					TotalRacers = 0;//обнуляем общее кол-во гонщиков 0
					SendClientMessage(playerid, COLOR_GREY, "   Ваше транспортное средство не соответствует данному типу гонки !");
					MenuOperation[playerid] = 51;
					ShowPlayerDialogGap(playerid, RACE_DIALOG, DIALOG_STYLE_LIST, "Select Race", RaceMenuItem, "OK", "Cancel");
					return 1;
				}
			}
			//SelectRace = RaceNames[listitem];//записали название выбранной гонки
			strmid(SelectRace, RaceNames[listitem], 0, strlen(RaceNames[listitem]), 20);
			Rate = 1;//10000 для экономики
			MenuOperation[playerid] = 52;
			ShowPlayerDialogEx(playerid, RACE_DIALOG, DIALOG_STYLE_INPUT, "Race Rate", "Введите Вашу Ставку. \
				\nСтавка может быть не ниже 1$ \nи не выше 10000$ \
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else if(MenuOperation[playerid] == 52)
		{
			if(strlen(inputtext))
			{
				Rate = strval(inputtext);
				if(Rate < 1 || Rate > 10000)//для экономики
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ставка НЕ может быть ниже 1$ или выше 10000$ !");
					MenuOperation[playerid] = 52;
					ShowPlayerDialogEx(playerid, RACE_DIALOG, DIALOG_STYLE_INPUT, "Race Rate", "Введите Вашу Ставку. \
						\nСтавка может быть не ниже 10000$ \nи не выше 100000$ \
						\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
					return 1;
				}
			}
			else
			{
				MenuOperation[playerid] = 52;
				ShowPlayerDialogEx(playerid, RACE_DIALOG, DIALOG_STYLE_INPUT, "Race Rate", "Введите Вашу Ставку. \
					\nСтавка может быть не ниже 1$ \nи не выше 10000$ \
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			if( GetPlayerMoneyH(playerid) < Rate )
			{   //если сумма больше денег на руках
				RacingMenu = 0;//освободить меню
				gInRacing[playerid] = 0;
				SendClientMessage(playerid, COLOR_GREY, "   У вас недостаточно денег на руках !");
				return 1;
			}
			GivePlayerMoneyH(frace, playerid, -Rate);
			TogglePlayerControllableEx(playerid, 0);//обездвиживает игрока для того чтобы он не стартанул раньше время
			TotalRacers = 1;//установить кол-во гонщиков
			TotalRate = Rate;//перезаписали общую ставку
			gInRacing[playerid] = 1;//поднять флаг вошёл в гонку
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				//if(GetPVarInt(i, "gSport") == 0 && WantedPoints[i] <= 0)
				//{   //ОПОВЕЩЕНИЕ ВСЕМ
				format(msgitem, sizeof(msgitem), "%s[%d] запустил гонку %s с призовым фондом $%d. Ставка - $%d. (USE: /race)",
					PlayerName(playerid), playerid, SelectRace, PrizeFund, Rate);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				format(msgitem, sizeof(msgitem), "[%d:%02d:%02d] %s", lH,lM,lS, msgitem);
				SendClientMessage(i, COLOR_BRIGHTLYGREEN, msgitem);

				//SendClientMessage(i, COLOR_GREY, "   Чтобы присоединиться к гонке (USE: /race)");
				//}
			}
			GridSetupPlayer(playerid);//для гонок STEP3
		//для установки на старте
			SetTimerEx("NPC_StartPosition", 1000, 0, "i", playerid);
		}
	}
	else
	{
		
		TogglePlayerControllableEx(playerid, 1);//освободить
		RacingMenu = 0;//вышел из меню
		TotalRacers = 0;//обнуляем общее кол-во гонщиков 0
		gInRacing[playerid] = 0;
	}
	return 1;
}

stock BG_Add(playerid)
{
	new slot = BG_GetFreeSlot(playerid);
	if (slot == BG_INVALID_SLOT_ID) {
		return -1;
	}

	new name[MAX_PLAYER_NAME + 1];
	format(name, sizeof(name), "Racer%d(%d)", playerid, slot);
	new npcid = FCNPC_Create(name);
	if (npcid == INVALID_PLAYER_ID) {
		return -2;
	}

	gPlayerNpc[playerid][slot] = npcid;
	gNpcPlayer[npcid] = playerid;
	gNpcSlot[npcid] = slot;
	return npcid;
}
stock BG_GetFreeSlot(playerid)
{
	for (new slot; slot < sizeof(gPlayerNpc[]); slot++) {
		if (gPlayerNpc[playerid][slot] == INVALID_PLAYER_ID) {
			return slot;
		}
	}
	return BG_INVALID_SLOT_ID;
}
stock GetCoordsInFront(Float:x, Float:y, Float:a, Float:distance, &Float:res_x, &Float:res_y)
{
	res_x = x + (distance * floatsin(-a, degrees));
	res_y = y + (distance * floatcos(-a, degrees));
}
stock BG_GetSlotByID(npcid)
{
	return gNpcSlot[npcid];
}
stock NPC_ADD(playerid)
{
	new npcid = BG_Add(playerid);
	if (npcid < 0) {
		if (npcid == -1) {
			SendClientMessage(playerid, -1, "{CC0000}Error: {FFFFFF}Maximum bodyguards allowed per player is reached.");
		} else if (npcid == -2) {
			SendClientMessage(playerid, -1, "{CC0000}Error: {FFFFFF}No slots available.");
		} else {
			SendClientMessage(playerid, -1, "{CC0000}Error: {FFFFFF}Unknown error.");
		}
		return 1;
	}
	new
		Float:player_x,
		Float:player_y,
		Float:player_z,
		Float:player_angle;

	GetPlayerPos(playerid, player_x, player_y, player_z);
	GetPlayerFacingAngle(playerid, player_angle);

	new
		Float:pos_x,
		Float:pos_y;

	GetCoordsInFront(player_x, player_y, player_angle, 2.0, pos_x, pos_y);

	FCNPC_Spawn(npcid, random(4) + 163, pos_x, pos_y, player_z);
	FCNPC_SetAngleToPlayer(npcid, playerid);
	FCNPC_SetVirtualWorld(npcid, GetPlayerVirtualWorld(playerid));
	FCNPC_SetInterior(npcid, GetPlayerInterior(playerid));
	FCNPC_SetWeapon(npcid, random(3) + 22);
	FCNPC_UseInfiniteAmmo(npcid, true);
	FCNPC_SetArmour(npcid, 80);
	FCNPC_SetFightingStyle(npcid, random(4) + 3);

	new label_text[2 + 3 + 1];
	format(label_text, sizeof(label_text), "[%d]", BG_GetSlotByID(npcid));
	gNpcText3D = Create3DTextLabelEx(label_text, 0xFFFFFFFF, 0.0, 0.0, 0.0, 5.0, npcid,INVALID_VEHICLE_ID,0,GetPlayerVirtualWorld(playerid));
#if defined DEBUG
	new
		string[38 + MAX_PLAYER_NAME + 3 + 1],
		playername[MAX_PLAYER_NAME + 1];

	GetPlayerName(playerid, playername, sizeof(playername));
	format(string, sizeof(string), "Player %s (ID: %d) has created a bodyguard", playername, playerid);
	SendClientMessageToAll(0xFF0000FF, string);
#endif
	return npcid;
}

forward NPC_StartPosition(playerid);
public NPC_StartPosition(playerid)
{
	//strmid(SelectRace, RaceNames[listitem], 0, strlen(RaceNames[listitem]), 20);
	new trackname[32+4];
	format(trackname, sizeof(trackname), "%s.rec", SelectRace);
	if( !fexist(trackname) )
	{
		new strtmp[26+32+4+3];
        if(CurState[playerid] == PLAYER_STATE_DRIVER)
	    {
		    //new vrecord[512] = "mynpc";
			//format(strtmp, sizeof(strtmp), "recordings/%s", SelectRace);
			StartRecordingPlayerData(playerid, PLAYER_RECORDING_TYPE_DRIVER, SelectRace);
			format(strtmp, sizeof(strtmp), "Recording: %s.rec. Started NPC in vehicle.", SelectRace);//, PlayerName(playerid)
			SendClientMessage(playerid, 0xFF0000FF,strtmp);
		}
	}
	else
	{
		new npcid = NPC_ADD(playerid);
		new carid = nCarID[playerid];
		//new vehicleid = CreateVehicle(nCarModel[playerid], x, y, z, 0, -1, -1, 1);
		//new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
    	new vehicleid = vehicle_SpawnInfrontOfPlayer(playerid, nCarModel[playerid], VehInfo[carid][cColor1], VehInfo[carid][cColor1]);
		/*new vehicleid = VehicleCreateEx(npcid,
			VehInfo[carid][cInt],
			VehInfo[carid][cVirt],
			nCarModel[playerid], x,y,temp_z, facing, VehInfo[carid][cColor1], VehInfo[carid][cColor1],
			-1);*/
		FCNPC_PutInVehicle(npcid, vehicleid, 0);
		//BG_EnterVehicle(playerid, gNpcSlot[npcid], vehicleid, 0);
		GridSetupPlayer(npcid);
	}
}

stock NPC_EnterVehicle(playerid)
{
	if (!strcmp(subcmd, "enter", true)) {
		param = strcharsplit(cmdtext, idx);
		if (strlen(param) == 0) {
			SendClientMessage(playerid, -1, "{8470FF}Use: {FFFFFF}/bg enter [slot] [vehicleid] [seat]");
			return 1;
		}

		new slot = strval(param);
		if (!BG_IsValidSlot(playerid, slot)) {
			SendClientMessage(playerid, -1, "{CC0000}Error: {FFFFFF}Invalid bodyguard.");
			return 1;
		}

		param = strcharsplit(cmdtext, idx);
		if (strlen(param) == 0) {
			SendClientMessage(playerid, -1, "{8470FF}Use: {FFFFFF}/bg enter [slot] [vehicleid] [seat]");
			return 1;
		}

		new vehicleid = strval(param);
		if (!GetVehicleModel(vehicleid)) {
			SendClientMessage(playerid, -1, "{CC0000}Error: {FFFFFF}Invalid target.");
			return 1;
		}

		param = strcharsplit(cmdtext, idx);
		new seat = strval(param);

		BG_UnFollowPlayer(playerid, slot);
		BG_EnterVehicle(playerid, slot, vehicleid, seat);
		return 1;
	}
}

//для гонок начало
stock LoadRace(const racename[])//для гонок STEP4 Загрузка из файла гонки вызывается из меню
{
//printf("Loading Race:%s",racename);
	new trackname[13+32];
	format(trackname, sizeof(trackname), "Race/%s.race",racename);
	if(!fexist(trackname))
	{   //если файла гонки с таким именем из списка racenames.txt нет
	    printf("Error4: race file not found: %s",trackname);
	    LoadRace(RaceNames[random(countrace)]);//то запустить случайную гонку из списка RaceNames
	    return 0;
	}
	//format(TrackName, sizeof(TrackName), "%s", racename);
	strmid(TrackName, racename, 0, strlen(racename), 32);
	for(new rc=0; rc<MAX_RACECHECKPOINTS; rc++)
	{   //обнуляем массив
		RaceCheckpoints[rc][0] = 0.0;
		RaceCheckpoints[rc][1] = 0.0;
		RaceCheckpoints[rc][2] = 0.0;
	}
	gMaxCheckpoints = 0;
	//--------------------------------------------------------------------------
	new line[160];
	new File:file = fopen(trackname, io_read);//открываем файл гонки Oil.race
	//загружаем из файла параметры гонки
	fread(file,line, sizeof(line),false);
	new idx;
	racecountdown = strval(strtok(line,idx));//15 - время для отcчёта
	TrackTime = strval(strtok(line,idx));//240 сек - время гонки
	WorldTime = strval(strtok(line,idx));//15 - время суток
	Weather = strval(strtok(line,idx));//1 - погода для даной гонки
	RaceType = strval(strtok(line,idx));//1 - тип гонки
	gRaceMaker = strtok(line,idx);//switch - можно использовать как флаг для проверки модели

	//загружаем из файла 5 моделей машин для данной гонки
	fread(file,line, sizeof(line),false);//строка в которой находится максимум 5 допустимых моделй для данной гонки
	new iiddxx;
	gCars[0] = strval(strtok(line,iiddxx));//1
	gCars[1] = strval(strtok(line,iiddxx));//2
	gCars[2] = strval(strtok(line,iiddxx));//3
	gCars[3] = strval(strtok(line,iiddxx));//4
	gCars[4] = strval(strtok(line,iiddxx));//5
	gCars[5] = strval(strtok(line,iiddxx));//6

	//загружаем из файла 3 строку: координаты начального положения первого игрока в левом ряду
	fread(file,line, sizeof(line),false);
	iiddxx = 0;
	GridPos[0] = floatstr(strtok(line,iiddxx));//624.760253
	GridPos[1] = floatstr(strtok(line,iiddxx));//865.711791
	GridPos[2] = floatstr(strtok(line,iiddxx));//-43.291885
	GridPos[3] = floatstr(strtok(line,iiddxx));//121.836662

	//загружаем из файла 4 строку: координаты начального положения второго игрока в правом ряду
	fread(file,line, sizeof(line),false);
	iiddxx = 0;
	GridPos[4] = floatstr(strtok(line,iiddxx));//630.981933
	GridPos[5] = floatstr(strtok(line,iiddxx));//865.051818
	GridPos[6] = floatstr(strtok(line,iiddxx));//-43.290763
	GridPos[7] = floatstr(strtok(line,iiddxx));//117.499839

	//загружаем из файла координаты гоночных CP
	while(fread(file,line, sizeof(line),false))
	{   //цыкл считывания и формирования массива RaceCheckpoints
		new idxx;
		RaceCheckpoints[gMaxCheckpoints][0] = floatstr(strtok(line,idxx));
		RaceCheckpoints[gMaxCheckpoints][1] = floatstr(strtok(line,idxx));
		RaceCheckpoints[gMaxCheckpoints][2] = floatstr(strtok(line,idxx));
		gMaxCheckpoints ++;//общее кол-во CP на данной трасе
	}
	fclose(file);//закрываем файл
	//--------------------------------------------------------------------------
	if(WorldTime > 0) { }//SetWorldTime(WorldTime);//устанавливаем время для этой гонки
	if(Weather > 0) { }//gWeatherSetWeather(Weather);//устанавливаем погоду для этой гонки

	//Начальная инициализация
	//new tempTime[128];
	//tempTime = HighScore(0);//возвращает строку текста с рекордом в первой строке
	new gBestTime[19+32 + 50+2+2+2+24+32];

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		//чтобы не создавать новый цыкл, т.к. GetMaxPlayers() > 100
		if(i<MAX_RACECHECKPOINTS) RaceCheckpointsCount[i] = 0;
		//обнуляем счётчик игроков прошедших через данный CP

		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		//new Menu:Current;
		//спрятать различные меню у всех гонщиков
		//if(GetPlayerMenu(i) == Current && gInRacing[i]) HideMenuForPlayerEx(Current,i);//mRacing
		//if(GetPVarInt(i, "gOoc") == 0 && gJobDuty[i] == 0 && gOnDuty[i] == 0 && WantedPoints[i] <= 0)
		//{
		format(gBestTime, sizeof(gBestTime), "< Tрасса %s > | %s",
			racename,
			HighScore(racename));//для гонок STEP5
		SendClientMessageEx(i, COLOR_BLUEGREEN, gBestTime);
		//}
	}
	FinishedCount = 0;//обнуляем кол-во игроков на финише
	GridCount = 0;//обнуляем позиции гонщиков раставленных по сетке
	RaceStartTime = 0;//обнуляем значение процесорных тиков
	gRaceStarted = 0;//опускаем флаг - начало гонки
	return 1;
}
//------------------------------------------------------------------------------
stock HighScore(const racename[])//для гонок STEP5 //вызывается из LoadRace
{   //для считывания рекорда из файла txt по названию гонки
	//#pragma unused racename//неиспользуем переменную Track
	new TrackFile[12+32];
	format(TrackFile, sizeof(TrackFile), "Race/%s.txt", racename);
	if(!fexist(TrackFile))
	{   //если файла не существует
	    new File: file = fopen(TrackFile, io_write);//то создать файл по указанному пути
	    fclose(file);
	}
	new line[160], idx, track[20], recordtimestr[20], racer[MAX_PLAYER_NAME], carmodel[32], prizefund[20];

	new File: file = fopen(TrackFile, io_read);
	fread(file, line, sizeof (line));
	track = strtok(line, idx);
	recordtimestr = strtok(line, idx);
	racer = strtok(line, idx);
	carmodel = strtok(line, idx);
	prizefund = strtok(line, idx);
	fclose (file);

	new recordtime = strval(recordtimestr);
	PrizeFund = strval(prizefund);
	//--------------------------------------------------------------------------
	new Minutes, Seconds, rMSeconds;
	new sHighScore[50+2+2+2+24+32];
	if(recordtime > 0)
	{   //если рекорд есть хоть какой-то
		timeconvert(recordtime, Minutes, Seconds, rMSeconds);//сконвертировать милисекунды в формат времени
		format(sHighScore, sizeof(sHighScore), "< Pекорд: %d:%02d.%03d установил %s на тачке %s >", Minutes, Seconds, rMSeconds, racer, carmodel);// \n
	}
	else format(sHighScore, sizeof(sHighScore), "< Pекорд на этой трассе не установлен >");// \n There is currently no track record
	return sHighScore;//вернуть строку текста с рекордом
}

stock GridSetupPlayer(playerid)//для гонок STEP3 //вызывается по команде /race
{   //для установки машин в позицию на старте по узлам сетки
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{   //если игрок не за рулем машины
	    SendClientMessage(playerid, COLOR_GREY, "   Вы должны находится за рулём машины !");
	    return 1;
	}
	//==========================================================================
	if(GridCount == 0)//если присоединился 1-ий гонщик
	{
		if(gCountdowntimer != -1) { KillTimer(gCountdowntimer); gCountdowntimer = -1; }//убить предыдущий (навсякий  случай), чтобы можно было установить новый
		gCountdowntimer = SetTimer("RaceCountdown", 1000, 1);//для гонок STEP4
		//запускаем таймер отсчёта
	}
	//для пролучения новых координат
	new Float:distance;
	if(GridCount > 1)//если присоединился 3-ий гонщик //if(GridCount == 2)
	{   //если кол-во гонщиков участвующих в гонке >1
		distance = 10.0;
		switch(GridIndex)
		{
		    case 0://для третьего гонщика - 3 строка файла
		    {
				GridPos[0] -= (distance * floatsin(-GridPos[3], degrees));//смещение по противоположному направлению угла, т.е. назад на 10 м
				//GridPos[0] = 2875,934570 - 10 * sin(-342,909027) = 2872,995672644 по X
				GridPos[1] -= (distance * floatcos(-GridPos[3], degrees));
				//GridPos[1] = -1591,060424 - 10 * cos(-342,909027) = -1600,618817292 по Y
		    }//LSRace - 2872.995672644,-1600.618817292,10.500221
		    case 1://для четвёртого гонщика - 4 строка файла
		    {
				GridPos[4] -= (distance * floatsin(-GridPos[7], degrees));
				//GridPos[4] = 2879,042480 - 10 * sin(-342,909027) = 2876,103582644 по X
				GridPos[5] -= (distance * floatcos(-GridPos[7], degrees));
				//GridPos[5] = -1597,285644 - 10 * cos(-342,909027) = -1606,844037292 по Y
		    }//LSRace - 2876.103582644,-1606.844037292,10.498308
		}
	}
	switch(GridIndex)//устанавливаем по новым координатам гонщиков
	{
	    case 0://координаты начального положения первого игрока в левом ряду и каждого нечётного
	    {   //if(GridCount == 0)
			SetVehiclePosEx(nCarID[playerid],GridPos[0],GridPos[1],GridPos[2]);
			SetVehicleZAngleEx(nCarID[playerid],GridPos[3]);
			GridIndex = 1;//переключаем, чтобы второй гонщик стал по координатам GridPos[4],GridPos[5],GridPos[6]
		}
	    case 1://координаты начального положения второго игрока в правом ряду
	    {	//if(GridCount == 1)
			SetVehiclePosEx(nCarID[playerid],GridPos[4],GridPos[5],GridPos[6]);
			SetVehicleZAngleEx(nCarID[playerid],GridPos[7]);
			GridIndex = 0;
	    }
	}
	GridCount ++;//подсчитываем кол-во гонщиков участвующих в гонке для растановки по сетке
	SetRaceText(playerid, GridCount);//для гонок STEP4
	//для показа позиции и приставки append

	SetPVarInt(playerid, "PlayerProgressCount", 0);//обнуляем кол-во пройденых игроком CP
	SetCheckpoint(playerid, GetPVarInt(playerid, "PlayerProgressCount"), gMaxCheckpoints);
	//для гонок STEP4
	//установить первый гоночный CP

	/*
   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(i != playerid)
		{
			if(!IsInPlane(nCarID[playerid]) && !IsInBoat(nCarID[playerid]))
			{
				SetVehicleParamsForPlayer(nCarID[playerid],i,0,1);//блокируем двери
				//SetVehicleParamsForPlayer(carid,i,false,true);//GetPlayerVehicleID(playerid)
			}
		}
	}*/

    if(TextDrawShowMessage[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdSystemMessage);
	}
	//gTextDrawShowRace[playerid] = true;  OnPlayerTextDrawStateChange(playerid);

	PlaySoundForPlayer(playerid, SOUND_OTB_TRACK_START);
	//ИНФОРМИРОВАНИЕ
	//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "GridSetupDebug - gridpos:%d/%d playerid:%d vehicleid:%d",GridCount,TotalRacers,playerid,nCarID[playerid]);//time:%d GetTickCount()
//ABroadCast(COLOR_MAROON, strings,9);
	return 1;
}


stock SetRaceText(playerid, pos)//для гонок STEP4 
//запускается из GridSetupPlayer и из PlayerEnterRaceCheckpoint
{   //для показа позиции и приставки append в TextDraw
	new append[5], tmp[8+2+2];
	////new temp[5]; format(temp,5, "/%d", GridCount);//sizeof(temp)
	//PlayerTextDrawSetStringEx(playerid, txdRacePosition[playerid], temp);
	format(tmp, sizeof(tmp), "%d / %d", pos, GridCount);//sizeof(tmp)
	PlayerTextDrawSetStringEx(playerid, txdPositionOfTotal[playerid], tmp);//позиция игрока
	
	switch(pos)
	{
		case 1,21,31,41,51,61,71,81,91:	format(append, sizeof(append), "ST");//FirST
		case 2,22,32,42,52,62,72,82,92:	format(append, sizeof(append), "ND");//SecoND
		case 3,23,33,43,53,63,73,83,93: format(append, sizeof(append), "RD");//ThiRD
		default: format(append, sizeof(append), "TH");//FourTH,fifth,sixth,seventh,eighth,ninth,tenth,nineteenteenth
	}
	PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid],append);//приставка
}

stock ReadHighScoreList(playerid, track[32], display)//для гонок STEP9 //запускается из WriteHighScoreList
{   //для считывания и показа списка рекордов
	//где track - название трассы, display=0, playerid=0
	if(!strlen(track))
	{   //если параметр track не передан
		track = TrackName;//записать название гонки в переменную track
	}
	//--------------------------------------------------------------------------
	new TrackFile[12+32]; //игрок, просящий отображение и если это должно быть
	format(TrackFile, sizeof(TrackFile), "Race/%s.txt", track);//преобразовываем имя файла в путь к файлу
	new strtmp[65+2+2+2+2+24+32+10];//для показа всех записей
	if(fexist(TrackFile))
	{   //если файл по указанному пути существует
		if(display == 1)
		{   //если должно быть отображено
			format(strtmp, sizeof(strtmp), "Cписок старых рекордов для Трассы %s:\n", track);
			SendClientMessage(playerid, COLOR_BROWNGREEN, strtmp);
		}
		new File: hsfile = fopen(TrackFile, io_read);
		new line[160], idx, temp[32];
		for(new l=0; l<HIGH_SCORE_SIZE; l++)//sizeof(RaceInfo)-1
		{   //последовательно считываем строки файла от 0 до 5
			fread(hsfile, line, sizeof(line));//открываем файл на чтение
			temp = strtok(line, idx);//считываем первое значение - имя трассы
			strmid(RaceInfo[l][rName], temp, 0, strlen(temp), 20);//Извлекает диапазон символов из строки. //в HSList[i][rName] заносим temp;
			temp = strtok(line, idx);//считываем второе значение - время прохождения трассы
			RaceInfo[l][rTime] = strval(temp);//конвертируем строку теста в целое
			temp = strtok(line, idx);//считываем третье значение - имя гонщика
			strmid(RaceInfo[l][rRacer], temp, 0, strlen(temp), 24);//в HSList[i][rRacer] заносим temp;
			temp = strtok(line, idx);//считываем четвёртое значение - название тачки
			strmid(RaceInfo[l][rModelCar], temp, 0, strlen(temp), 32);
			temp = strtok(line, idx);//считываем пятое значение - призовой фонд
			RaceInfo[l][rPrizeFund] = strval(temp);//конвертируем строку теста в целое
			//список сформирован по старым данным
			//------------------------------------------------------------------
			idx = 0;//сбрасываем для считывания параметров следующей строки
			if(display == 0)
			{	//Нет необходимости возвращать если это отображается
				if(RaceInfo[l][rTime] == 0)
				{	//check if record is not set (0) previously
					fclose(hsfile);//закрыть файл
					return (RaceInfo);	//если список до конца, вернуть что было
				}
			}
			if(display == 1)
			{   //если установлено отображать список рекордов
				if(RaceInfo[l][rTime] != 0)
				{	//если время рекорда неравно нулю, т.е. не установлено
					new Minutes, Seconds, rMSeconds;
					timeconvert(RaceInfo[l][rTime], Minutes, Seconds, rMSeconds);//сконвертировать милисекунды в формат времени
					format(strtmp, sizeof(strtmp), "%d - %d:%02d.%03d установил %s на машине %s и получил приз {33AA33}$%d\n",
						l+1, Minutes, Seconds, rMSeconds, RaceInfo[l][rRacer], RaceInfo[l][rModelCar], RaceInfo[l][rPrizeFund]);
					SendClientMessage(playerid, COLOR_BLUEGREEN, strtmp);
				}
			}
		}
		fclose(hsfile);//закрыть файл
	}
	else
	{	//if client passed as param a race that doesn't exist
		format(strtmp, sizeof(strtmp), "Error5: Файл Гонки «%s» не существует.", track);
		Log(ERROR, strtmp);
	}
	if(display == 0)
	{	//Нет необходимости возвращать если это отображается
		return (RaceInfo);	//so warning 209 can be ignored.
	}
	return (RaceInfo);//вернуть массив из 5-и строк и 5-и столбцов с рекордами
}//для гонок конец

forward RaceCountdown();//для гонок
public RaceCountdown()//для гонок STEP4
{   //секундый таймер отсчёта запускается из LoadRace при старте режима
	racecountdown --;//15
	switch(racecountdown)
	{
		case 0:
		{
			if(gCountdowntimer != -1) { KillTimer(gCountdowntimer); gCountdowntimer = -1; }//и сразу убиваем
			StartRace();//для гонок STEP5
		}
		case 3,2,1://для приготовления к старту
		{
			new strtmp[3];
			format(strtmp, sizeof(strtmp), "%d", racecountdown);

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(gInRacing[i])
				{   //если игрок присоединился к гонке
					SetCameraBehindPlayer(i);
					//PlaySoundForPlayer(i, SOUND_OTB_TRACK_STOP);
					PlaySoundForPlayer(i, SOUND_RACE_321);
					GameTextForPlayerEx(i,strtmp, 750, 5);
					TogglePlayerControllableEx(i, 0);//обездвиживает
				}
			}
		}
		case 4..9://для приготовления к старту
		{

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(gInRacing[i])
				{   //если игрок присоединился к гонке
					TogglePlayerControllableEx(i, 0);//обездвиживает
					//NPC_StartPosition(i, SelectRace);
				}
			}
		}
		case 10,15,20,30,40,50,60,70,80,90://для общего информирования
		{

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				//если игрок присоединился к гонке
				if(gInRacing[i]) TogglePlayerControllableEx(i, 0);//обездвиживает
				//ОПОВЕЩЕНИЕ
				//if(GetPVarInt(i, "gSport") == 0 && gJobDuty[i] == 0 && WantedPoints[i] <= 0)
		   		//{   //gOnDuty[i] == 0
	   			new strtmp[37+3];
				format(strtmp, sizeof(strtmp), "~w~RACE STARTING IN ~y~%d ~w~SECONDS", racecountdown);
				GameTextForPlayerEx(i,strtmp, 2000, 4);
				//}
			}
		}
	}
}
stock StartRace()//для гонок STEP5
{   //запускается из RaceCountdown()
    //GameTextForAll("~W~GO", 2000, 5);

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(gInRacing[i])
		{   //сканируем всех вошедших в гонку
			TogglePlayerControllableEx(i, 1);//освободить
			PlaySoundForPlayer(i, SOUND_RACE_GO);
			GameTextForPlayerEx(i, "~W~GO", 750, 5);
			//PlayerTextDrawSetStringEx(i, txd_hbarr, "Checkpoint");
		}
	}
	//записали значение процесорных тиков
	RaceStartTime = GetTickCount();//возвращает число в миллисекундах с момента последнего запуска.
	endracetimer = SetTimer("EndRaceCountdown", 1000, 1);//для гонок STEP6
	//секундный тамер для остановки гонки запускается из StartRace()
	gRaceStarted = 1;//поднимаем флаг - гонка началась
}
forward EndRaceCountdown();//для гонок
public EndRaceCountdown()//для гонок STEP6 //секундный тамер для выхода из гонки запускается из StartRace
{   //если кто то вышел из игры
	new timers = GetTickCount();
	TrackTime --;//240 - время гонки уменьшаем по 1 каждую секунду
	if(TrackTime <= 0)
	{
	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(gInRacing[i])
			{
				//PlayerInfo[i][pParam2] = 0; gParameter2[i] = 0;
				//SetPlayerShowScale(i, 2, PlayerInfo[i][pParam2], 50);

				gInRacing[i] = 0;//опускаем флаг - игрок не в гонке
				PlaySoundForPlayer(i, SOUND_DRIVING_AWARD_TRACK_STOP);//Выключить Музыкальный трек - конец гонки
				//PlaySoundForPlayer(i, SOUND_BIKE_AWARD_TRACK_STOP);//Выключить Музыкальный трек - победа в гонке
				DisablePlayerRaceCheckpoint(i);

				if(PlayerInfo[i][pJob] == TRUCKER) RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
				//gTextDrawHideRace[i] = true;
				//PlayerTextDrawSetStringEx(i, txd_hbarr, "Insurance");				
			}
		}

		gRaceStarted = 0;//опускаем флаг - гонка закончилась
		TotalRacers = 0;//обнуляем общее кол-во гонщиков 0
		KillTimer(endracetimer); endracetimer = -1;
		RacingMenu = 0;//опустили флаг - вышел из меню

		format(strings, sizeof(strings), "Гонка {FF0000}%s{FF6600} окончена!", TrackName);
		SendClientMessageToAll(COLOR_GREEN, strings);
		
		
	}
    else if(TrackTime == 10 || TrackTime == 20 || TrackTime == 30)
    {
        new strtmp[32];
        format(strtmp, sizeof(strtmp), "%d секунд до окончания гонки.", TrackTime);

	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(gInRacing[i])
			{
				SendClientMessage(i, COLOR_DARKGREEN, strtmp);
			}
		}
	}
	tUpdateRaceTime();//для гонок STEP7
	TestLog(OPTIM, "EndRaceCountdown", GetTickCount(), timers);//new timers = GetTickCount();
}

stock tUpdateRaceTime()//для гонок STEP7 //запускается каждую секунду из StartRace->EndRaceCountdown()
{   //для отображения времени с момента старта
	new Time;
	new curtime = GetTickCount();//Получает число процессорных тиков со времени последнего перезапуска сервера.
	if(RaceStartTime != 0) Time = curtime - RaceStartTime;
	else Time = 0;
	new rmSeconds;
	timeconvert(Time, rMinutes,rSeconds,rmSeconds);//передаём кол-во процесорных тиков Time, а возвращаем три переменнх
	new strTime[9+2+2];
	format(strTime, sizeof(strTime), "%02d:%02d", rMinutes, rSeconds);//sizeof(strTime)

	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(gInRacing[i])
		{
			PlayerTextDrawSetStringEx(i, txdRaceTime[i], strTime);
		}
	}	
}
//для гонок конец

stock SetCheckpoint(playerid, progress, totalchecks)//для гонок STEP4 //для установки гоночных чекпоинтов
{   //запускается из GridSetupPlayer, PlayerEnterRaceCheckpoint,
	//где progress - кол-во пройденых игроком CP, totalchecks - общее кол-во CP на данной трасе
	new checktype = 0;
	new Float: SIZE = 12.0;
	//checktype=0 - Простой гоночный чекпоинт со стрелкой
	//checktype=1 - Старт/Финиш
	//checktype=2 - Простой гоночный чекпоинт без стрелки
	//checktype=3 - чекпоинт ввиде кольца
	//checktype=4 - чекпоинт ввиде кольца
	//checktype=7 - чекпоинт ввиде кольца для прыжка с бонусом
	//checktype=8 - чекпоинт ввиде кольца для прыжка с бонусом
	if(RaceType == 1) { checktype = 0; SIZE = 10.0; }//если тип гонки 1 то установить тип CP=0 - чекпоинт со стрелкой
	else if(RaceType == 2) { checktype = 2; SIZE = 5.0; }
	//3-Air normal, если тип гонки 2 то установить тип CP=3 - чекпоинт ввиде кольца
	else if(RaceType == 3) { checktype = 3; SIZE = 12.0; }
	else if(RaceType == 4) { checktype = 4; SIZE = 1.5; }
	
	if(progress == (totalchecks-1))
	{   //если это финиш,
		if(RaceType == 1 || RaceType == 2 || RaceType == 4)
		{   //1-Finish
			SetPlayerRaceCheckpoint(playerid, 1,
				RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
				RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
				8.0);
		}
		else //if(RaceType == 3)
		{   //Air finish
			SetPlayerRaceCheckpoint(playerid, 4,
				RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
				RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
				SIZE);
		}
	}
	else
	{
		SetPlayerRaceCheckpoint(playerid, checktype,
			RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
			RaceCheckpoints[progress+1][0],RaceCheckpoints[progress+1][1],RaceCheckpoints[progress+1][2],
			SIZE);
	}
	
	new strtmp[8+2+2];
	format(strtmp,sizeof(strtmp),"%d / %d", progress, totalchecks-1);
	PlayerTextDrawSetStringEx(playerid, txdInsurances[playerid], strtmp);
	
	TextDrawSetStringEx(txd_hbarr, "Checkpoints");
}




//stock RacerEnterCheckpoint(playerid)//для гонок STEP8
stock race_OnPlayerEnterCheckpoint(playerid)//для гонок STEP8
{   //вызывается из OnPlayerEnterRaceCheckpoint
	if(gInRacing[playerid] && GetPVarInt(playerid, "PlayerProgressCount") >= (gMaxCheckpoints-1)) //Если игрок финишировал...
	{   //если кол-во пройденных меток совпало с максимальным кол-вом в массиве
	    DisablePlayerRaceCheckpoint(playerid);
	    PlaySoundForPlayer(playerid, SOUND_DRIVING_AWARD_TRACK_START);//Включить Музыкальный трек - конец гонки
		//----------------------------------------------------------------------
		//Для вывода сообщения
	    new append[3];
		FinishedCount ++;//получаем позицию на финише или кол-во игроков на финише
		switch(FinishedCount)
		{   //для приставке к позиции
			case 1,21,31,41,51,61,71,81,91:	format(append, sizeof(append), "st");
			case 2,22,32,42,52,62,72,82,92:	format(append, sizeof(append), "nd");
			case 3,23,33,43,53,63,73,83,93: format(append, sizeof(append), "rd");
			default: format(append, sizeof(append), "th");
		}
		//для подсчёта затраченного времени на прохождение трассы
		new curtime = GetTickCount();//возвращает число в миллисекундах с момента последнего запуска.
		new Time = curtime - RaceStartTime;//находим разницу между новым значением и старым
		new Minutes,Seconds,rMSeconds;
		timeconvert(Time, Minutes, Seconds, rMSeconds);//передаём кол-во процесорных тиков Time, а возвращаем время в формате
		new prize;
		PrizeFund = 0;
		/*switch (FinishedCount)//порядок на финише
		{
			case 1: prize=5000;
			case 2:	prize=4000;
			case 3:	prize=3000;
			case 4:	prize=2000;
			case 5:	prize=1500;
  			case 6:	prize=1000;
			default: prize=500;
		}*/
		RaceInfo = ReadHighScoreList(playerid, TrackName, 0);//для гонок STEP9
		//запускаем ф-ию считывания лучшего времени и призового фонда на этой трассе
		if(RaceInfo[0][rTime] == 0) RaceInfo[0][rTime] = 3000000;//начальная инициализация
		/*if(TotalRacers > 1)
		{   //если гонщиков > 1
	  		if(FinishedCount==1 && Time < RaceInfo[0][rTime]) PrizeFund = RaceInfo[0][rPrizeFund];//для поднятия вознаграждения если чувак побил рекорд
	  		//если игрок прибыл первым и установил лучшее время
		}
		else
		{
	  		if(Time < RaceInfo[0][rTime]) PrizeFund = RaceInfo[0][rPrizeFund];
			prize = TotalRate;
		}*///Credit $1 for every win - AndrsOG
  		//if(Time < RaceInfo[0][rTime]) PrizeFund = RaceInfo[0][rPrizeFund];
  		//для поднятия вознаграждения если чувак побил рекорд
		if(FinishedCount == 1)
		{
			prize = TotalRate;//если финишировал первым то получить общую ставку

			//для дальнобойщиков STEP13
			/*if(PlayerInfo[playerid][pJob] == TRUCKER)
			{//RacingMenu == 2 &&
				PrizeFund = 0;//чтобы не суммировало
				PlayerInfo[playerid][pMats] += 6*60;

				new msgitem[9*8 + 54 + 38 + 27+2 + 22+24 + 32+10 + 40];//1024/2800//3072
				strcat(msgitem, "{FB0808}Ты лучший в заезде.\n Можешь открыть свою компанию.\n");
				strcat(msgitem, "{AFAFAF}___________________________________\n");
				format(msgitem, sizeof(msgitem), "%s{5F5646}Водителей в наём: {FFFFFF}\t%d\n", msgitem, PlayerInfo[playerid][pMats]/360);
				format(msgitem, sizeof(msgitem), "%s{5F5646}Кому выдана: {FFFFFF}\t\t%s\n", msgitem, PlayerName(playerid));
				format(msgitem, sizeof(msgitem), "%s{5F5646}Срок действия: {FFFFFF}\t%d секунд\n", msgitem, PlayerInfo[playerid][pMats]);//Целостность груза:
				format(msgitem, sizeof(msgitem), "%s{AFAFAF}___________________________________\n", msgitem);//Bы заработали: $%d
				//format(msgitem, sizeof(msgitem), "%sИТОГО: \t\t\t$%d\n", msgitem, money);//Bы заработали: $%d
				//TogglePlayerControllableEx(playerid, 0);//обездвиживает
				ShowPlayerDialogEx(playerid, 20,DIALOG_STYLE_MSGBOX, "{A79566}ЛИЦЕНЗИЯ на право найма водителя",msgitem, "OK", "");
			}*/

		}
		//else if(FinishedCount == 2) prize = floatround(Rate/2);//иначе ставку/2
		//else if(FinishedCount == 3) prize = floatround(Rate/3);//иначе ставку/3
		else prize = 0;
		GivePlayerMoneyH(frace, playerid, (prize+PrizeFund));

	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(gInRacing[i])
			{
				//new strings[MAX_STRING];
				format(strings, sizeof(strings), "%s финишировал %d%s в %d:%02d.%03d и получил приз {33AA33}$%d",
					PlayerName(playerid), FinishedCount, append, Minutes, Seconds, rMSeconds, (prize+PrizeFund));
				SendClientMessage(i, COLOR_LIGHTBLUE, strings);//на счёт в банке
			}
		}

		/*//для гонки Weather
		if( (weathers[wethindex] == 8 || weathers[wethindex] == 16 || weathers[wethindex] == 19) &&
			!strcmp(TrackName, "Weather", true) )
		{
			format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}очистил небо.", PlayerName(playerid), playerid);
			OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
			OOCNews(COLOR_LIGHTBLUE, strings);
//для погоды начало
		    wethindex ++;//номер ячейки погоды
		    if(wethindex == sizeof(weathers)) wethindex = 0;
		    SetWeather(weathers[wethindex]);//из массива weathers установить погоду следующую по списку
	       	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pVirtual] == 0) SetPlayerWeather(i, weathers[wethindex]);
			}
		    ChangeWeath = WEATHCHANGE;
			format(strings, sizeof(strings), "GisMeteoMessage: в San Andreas установлено %s[%d].", GisMeteoMessage(weathers[wethindex]), weathers[wethindex]);
			OOCNews(COLOR_GREEN, strings);
			if(weathers[wethindex] == 8 || weathers[wethindex] == 16)
			{
				SBizInfo[51][sbProducts] += 500;
			}
		}*/
				
		WriteHighScoreList(playerid, Time, (prize+PrizeFund));//для гонок STEP10
		//передаём время на финише и призовой фонд для записи и проверки рекорда
		if(FinishedCount >= TotalRacers)//если финишировавших равно общему кол-ву и время больше 35 секунд
		{   //если все финишировали //и время ещё не вышло  && TrackTime > 35

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(gInRacing[i])
				{   //для всех участников гонки
					PlaySoundForPlayer(i, SOUND_DRIVING_AWARD_TRACK_STOP);//Выключить Музыкальный трек - конец гонки
					//PlaySoundForPlayer(i, SOUND_BIKE_AWARD_TRACK_STOP);//Выключить Музыкальный трек - победа в гонке
					gInRacing[i] = 0;//опускаем флаг - игрок не в гонке
					if(PlayerInfo[i][pJob] == TRUCKER) RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
				}
			}
			gRaceStarted = 0;//опускаем флаг - гонка закончилась
			TotalRacers = 0;//обнуляем общее кол-во гонщиков 0
			KillTimer(endracetimer); endracetimer = -1;
 			RacingMenu = 0;//опустили флаг - вышел из меню
 			FinishedCount = 0;
 			
			// Stop recording any data
			StopRecordingPlayerData(playerid);
			SendClientMessage(playerid, 0xFF0000FF, "Recording stopped.");

			format(strings, sizeof(strings), "Гонка {FF0000}%s{FF6600} окончена!!", TrackName);
   			SendClientMessageToAll(COLOR_GREEN, strings);
		}
//если финишировавших равно общему кол-ву и время больше 35 секунд
		//gTextDrawHideRace[playerid] = true; OnPlayerTextDrawStateChange(playerid);
	}
	else if(gInRacing[playerid] && GetPVarInt(playerid, "PlayerProgressCount") < (gMaxCheckpoints-1))
	{    //Если гонщик ещё не финишировал, установить следующий checkpoint
		GivePVarInt(playerid, "PlayerProgressCount", +1);//счётчик пройденных CP
		SetCheckpoint(playerid, GetPVarInt(playerid, "PlayerProgressCount"), gMaxCheckpoints);//для гонок STEP4
		//Sets the next checkpoint in the race
		RaceCheckpointsCount[GetPVarInt(playerid, "PlayerProgressCount")] ++;//счётчик игроков прошедших через данный CP
		new RacePosition = RaceCheckpointsCount[ GetPVarInt(playerid, "PlayerProgressCount") ];
		//округляем вещественное в нижнее значение
		SetRaceText(playerid, RacePosition);//для гонок STEP4
		//запускаем ф-ию для показа позиции и приставки append в TextDraw
		//new tmp[5];	format(tmp, sizeof(tmp), "/%d",TotalRacers);
		//TextDrawSetStringEx(txdTotalRacers,tmp);
		PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);
	}
}


stock WriteHighScoreList(playerid, time, prize)//для гонок STEP10 //запускается из RacerEnterCheckpoint //race_OnPlayerEnterCheckpoint(playerid)//для гонок STEP8
{   //для записи рекорда получили кол-во милисекунд с момента старта до момента финиша
	RaceInfo = ReadHighScoreList(playerid, TrackName, 1);//запускаем ф-ию считывания рекорда на этой трассе
	//if(nCarID[playerid] == 0)  return 1;
	//nCarID[playerid] = GetPlayerVehicleID(playerid);//получить ID машины игрока из списка установленных моделей
	//nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);
	new carmodel[32];
	strmid(carmodel, VehicleArray[nCarModel[playerid]-400][Vehicle_Name], 0, 32, 32);
	new recordflag = -1;//чтобы запись происходила один раз
	new pflag = -1;//чтобы запись происходила один раз
	for(new l=0; l<HIGH_SCORE_SIZE; l++)
	{   //сканируем массив записей рекордов
		if(RaceInfo[l][rTime] == 0)
		{   //если рекорд по строке i не установлен, т.е. равен нулю
			RaceInfo[l][rTime] = 3000000;//то установить ложный рекорд, т.е. освободить переменную
		}
		if(!strcmp(RaceInfo[l][rRacer], PlayerName(playerid), true) && pflag ==-1)
		{ //если по строке i имена совпадают и флаг опущен
			pflag = l;//поднять флаг - записать номер строки где уже есть рекорд этого игрока
		}
		if(time < RaceInfo[l][rTime] && recordflag ==-1
			&& (pflag == -1 || pflag == l) )//для нового рекорда
		{	//если время меньше рекорда и флаг рекорда опущен,
			//и если рекорд не установлен или это рекорд этого игрока
			new strtmp[37+2+32+24];
			if(l+1 == 1)
			{
				//printf("NEW FIRST RECORD - %s", PlayerName(playerid));
				format(strtmp, sizeof(strtmp), "Bремя %d на трассе %s установил %s\n" , l+1, TrackName, PlayerName(playerid));
				SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
			}
			recordflag = l;	//поднять флаг рекорда - записать номер строки
		}
	}
	if(recordflag > -1)//для нового рекорда
	{	//если получен новый рекорд
		new TrackFile[12+32];
		new strtmp[17+32+10+24+32+10];
		format(TrackFile, sizeof(TrackFile), "Race/%s.txt", TrackName);//time to update list (file)
		if(fexist(TrackFile))
		{
			new File: file = fopen(TrackFile, io_write);//открыть файл по названию гонки для записи

			format(strtmp, sizeof(strtmp), "%s %d %s %s %d\n" ,
				TrackName,
				time,
				PlayerName(playerid),
				carmodel,
				prize);//PrizeFund gScores[playerid][1]
			for(new l=0; l<HIGH_SCORE_SIZE; l++)
			{   //сканируем все строки массива RaceInfo
				if(l == recordflag)//записать и скорректировать место в списке
				{   //если нашли строку по которой установлен новый рекорд, т.е. время по этой строке больше чем полученное
					fwrite(file, strtmp);//запись рекорда в файл
				}
				if(!strcmp(RaceInfo[l][rRacer], PlayerName(playerid)))//чтобы один и тот же человек не фигурировал 5 раз в списке
				{   //пропустите все записи, которые соответствуют этому гонщику
					continue;
				}
				if(RaceInfo[l][rTime] == 3000000)
				{   //проигнорировать ложные записи
					break;
				}
				format(strtmp, sizeof(strtmp), "%s %d %s %s %d\n",
					TrackName,
					RaceInfo[l][rTime],
					RaceInfo[l][rRacer],
					RaceInfo[l][rModelCar],
					RaceInfo[l][rPrizeFund]);//gScores[i][1]
				fwrite(file, strtmp);//перезаписать все строки списка
			}
			fclose(file);//запись закончена - закрыть файл
		}
		else
		{
			format(strtmp, sizeof(strtmp), "Error6: Файл Гонки «%s» не существует.", TrackName);
			Log(ERROR, strtmp);
		}
	}
}




