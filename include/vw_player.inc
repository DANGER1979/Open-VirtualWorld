/*
 *            vw_player v1.0
 *       (c) Copyright 2017-2018 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 26.01.2017
 * @update    : 10.11.2018
 *
 * This file is provided as is (no warranties).
 * объявление и инициализация переменных
 */

//##############################################################################//
//                                                                              //
//                     ОПРЕДЕЛЕНИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ                        //
//                                                                              //
//##############################################################################//
//используются с разных точек мода
new GameRestart = -1;
new numplayers = 0;//счётчик присоединенных игроков
new HighestPlayerID = 1;//максимальный ИД игрока на сервере, т.е. кол-во ботов +1
/*
//new bigmsgitem[2048];
#define MAX_FUNCTION 65
new TEST[MAX_FUNCTION];
new SWITCH = 1;
new testcount;//счётчик для тестирования
new SynchronizerSaved = 0;//для асинхронного сохранения

new MySQL_DeBug = 0;
new oldtick;

new bool:OnPlayerUpdate_run = false;


//для записи ботов
//new npc_counter;//счётчик


*/

//==============================================================================


/*
new nMessages[MAX_PLAYERS];
*/
//##############################################################################//
//                                                                              //
//                      ОПРЕДЕЛЕНИЯ ПРИВАТНЫХ ПЕРЕМЕННЫХ ИГРОКА                 //
//                                                                              //
//##############################################################################//
//те что не участвуют в циклах и в таймерах перевести на Pvar
//переменные которые могут использоваться в разных библиотеках, а не только в одной
//чтобы постоянно не вызывать GetPlayerInterior(playerid)
new CurInt[MAX_PLAYERS]; new LastInt[MAX_PLAYERS];

//чтобы постоянно не вызывать GetPlayerState(playerid);
new CurState[MAX_PLAYERS]; new LastState[MAX_PLAYERS];

//чтобы постоянно не вызывать
//nCarID[playerid] = GetPlayerVehicleID(playerid);
//nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);//ВНИМАНИЕ: везде проверять нет ли минусовых значение в данном массиве или значение от 0 до 400
new nCarID[MAX_PLAYERS], nCarModel[MAX_PLAYERS];//перезаписывается в OnPlayerStateChange
new LastCar[MAX_PLAYERS], LastDriver[MAX_VEHICLES+1];//для хранения последнего водителя этой машины MAX_VEHICLES+2, т.к. ID тачек начинается с 1
//nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]);//Получить ID трейлера прикреплённого к машине.
//nTrailerModel[playerid] = VehInfo[trailerid][cModel];//GetVehicleModel(nTrailerID[playerid]);//Узнает ID модели данного трейлера прикреплённого к машине.

new WantedLevel[MAX_PLAYERS];

//!!!не переводить на PVar
new MenuOperation[MAX_PLAYERS];

new gGotOrder[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//ID того на кого выписан ордер
new Offer[MAX_PLAYERS+MAX_SBIZ+100];//MAX_PLAYERS //хранит ID предложившего игрока по индексу клиента

new HireCarID[MAX_PLAYERS];//для хранения ключей (ID машины) от автомобиля проката


new AFK_IdleTime[MAX_PLAYERS];//для проверки AwayFromKeyboard
new gAFK_ToggleMode[MAX_PLAYERS];//!!!не переводить на PVar

new gAnticheat[MAX_PLAYERS];

//для копов и банд
new TicketMoney[MAX_PLAYERS];
new PlayerTazed[MAX_PLAYERS];
new PlayerTazeTime[MAX_PLAYERS];
new PlayerTied[MAX_PLAYERS];
new PlayerTiedTime[MAX_PLAYERS];
new PlayerCuffed[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};
new PlayerCuffedTime[MAX_PLAYERS];


//!!!не переводить на PVar
new spectateid[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//spectateid[playerid] = giveplayerid; ID того за кем вы наблюдаете по индексу наблюдателя
new spectatorid[MAX_PLAYERS];//ID наблюдателя по индексу того кто за кем он наблюдает

new gPlayerBoxing[MAX_PLAYERS];//игрок в бою

new IsPlayerControllable[MAX_PLAYERS];//проверка замарозки

//СИСТЕМА УСТАНОВКИ ЧЕКПОИНТОВ И СНЯТИЕ

new MinTimeCheckpoint[MAX_PLAYERS];//для проверки минимального времени подбирания маркера
new TimeSetCheckpoint[MAX_PLAYERS];
new playerCheckpoint[MAX_PLAYERS];// = {MAX_POINTS, ...};//для сопоставления checkCoords - checkpointType
new CP[MAX_PLAYERS];//для установки чекпоинтов
//для УСТАНОВКИ КОНТРОЛЬНЫХ МЕТОК конец

//для фракций
new gSpawn[MAX_PLAYERS];//переключатель спауна для смены места службы
//##############################################################################//
//                                                                              //
//                               Переменные LAST                               //
//                                                                              //
//##############################################################################//
new Float: LastHealth[MAX_PLAYERS] = {100.0, ...};
new Float: VehHealth[MAX_VEHICLES+1]; new Float: LastVehHealth[MAX_PLAYERS];

new Float: LastArmour[MAX_PLAYERS];

new LastKey[MAX_PLAYERS];
new LastMoney[MAX_PLAYERS];
new LastDamagedid[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//ИД последнего игрока которому Вы нанесли урон
new LastIssuerid[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//Ид последнего игрока который Вам нанёс урон

new LastWeapon[MAX_PLAYERS], LastStateWeapon[MAX_PLAYERS];//!!!не переводить на PVar
new LastWeaponInSlot[MAX_PLAYERS][13];//последнее оружие в каждом слоте
new LastAmmo[MAX_PLAYERS][MAX_WEAPONS+1];//постоянно обновляется из OnPlayerKeyStateChange

new LastKill[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//ИД последного киллера для системы повторный ДМ

//чтобы постоянно не вызывать GetPlayerPos
new Float: CurPos[3][MAX_PLAYERS];//координаты игрока, постоянно перезаписываются в player_OnPlayerUpdate(playerid)
new Float: spawnPos[3][MAX_PLAYERS];//координаты спауна игрока перезаписываются в player_OnPlayerSpawn(playerid)
new Float: VehPos[MAX_VEHICLES+1][4];//координаты тачки, постоянно перезаписываются //перезаписывается в SetVehiclePosEx

new Float: Mark[3][MAX_PLAYERS];//метка на карте

new votecount[MAX_PLAYERS];//счётчик кол-ва голосов за кик
new CrashDetected[MAX_PLAYERS];

//##############################################################################//
//                                                                              //
//                                    ТРИГЕРЫ                                   //
//                                                                              //
//##############################################################################//

new gPlayerSpawned[MAX_PLAYERS];//если игрок заспаунился !!!не переводить на PVar
new gVehicleSpawn[MAX_VEHICLES+1];
new gPlayerLogged[MAX_PLAYERS];//если игрок залогинелся  !!!не переводить на PVar
new gGameText[MAX_PLAYERS];//1 - отключается все ф-ии GameTextForPlayerEx, т.е. не показывать все GameText пока gGameText == 1
new gTagForPlayer[MAX_PLAYERS];//для показа тэгов над игроками
new IsPlayerTagShow[MAX_PLAYERS][MAX_PLAYERS];//перевести на PVar
new IsKicked[MAX_PLAYERS]; //new IsBaned[MAX_PLAYERS];
new gCheckDisconnect[MAX_PLAYERS] = 0;//если игрок вошёл на сервер, но типа не вышел
new gJobDuty[MAX_PLAYERS];//для выхода на работу
new gOnDuty[MAX_PLAYERS];//для выхода на службу
new gInTerrorsCount[MAX_PLAYERS];//присоединился в команду терористов
new gInCTerrorsCount[MAX_PLAYERS];//присоединился в команду контротерористов
new gInRacing[MAX_PLAYERS];
new gInDerbyBloodBowl[MAX_PLAYERS];
new gInDerby8ball[MAX_PLAYERS] = 0;//проверка на игрока учавствующего в деюри
//для автоугонщиков//для дальнобойщиков
new gRobCountdown[MAX_PLAYERS] = {-1, ...};
new gConsumingMoney[MAX_PLAYERS];//если игрок получил деньги

new gWatchingTV[MAX_PLAYERS];//для зрителя ТВ !!!не переводить на PVar
new gTranslatorTV = -1;//для ТВ


/*
//##############################################################################//
enum TeleportEnum// текущая позиции
{
	Flag,
    Float:tX,
    Float:tY,
    Float:tZ,
	Int,
	Virt,
	Loc
};
new Float:TeleportDest[MAX_PLAYERS][TeleportEnum];//для gotomark getdist

//------------------------------------------------------------------------------
new HouseCar[MAX_PLAYERS];
//new Works[MAX_PLAYERS];//признак дежурства
//new ProposedFamily[MAX_PLAYERS];
//-------------------------------


*/

#if defined FILTERSCRIPT
stock player_OnFilterScriptInit()
{
	new time = GetTickCount();
	numplayers = 0;
	HighestPlayerID = 1;

	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		SetPVarInt(i, "ShowMenu", 0);
		numplayers ++;
		if(i > HighestPlayerID) { HighestPlayerID = i+1; }
//для ФС
		new newstate = GetPlayerState(i);
		CurState[i] = newstate;
		LastState[i] = 0;
		if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
		{	//если ID нового состояния равно состоянию 2//если ID нового состояния равно состоянию 3 - пассажир
			if(newstate == PLAYER_STATE_DRIVER) LastDriver[LastCar[i]] = MAX_PLAYERS-1;
			LastCar[i] = MAX_VEHICLES+1;//освобождаем переменную предыдущей машины
			nCarID[i] = GetPlayerVehicleID(i);//получить ID машины игрока из списка установленных моделей
			nCarModel[i] = GetVehicleModel(nCarID[i]);//Узнает ID модели данного транспортного средства.
		}
		else
		{
			LastCar[i] = 0;
			nCarID[i] = 0; nCarModel[i] = 0;//освобождаем переменную
			gPlayerSpawned[i] = 1;
		}

		OnPlayerInit(i);
	}

	printf("1/19. [Загрузка настроек игрока]: потрачено - %d (ms)", (GetTickCount()-time));
}
#endif

stock OnPlayerInit(playerid, callback=0, reason=1)//вызывается из OnPlayerConnect и OnPlayerDisconnect
{//инициализация всех переменных этой библиотеки
	#pragma unused reason
	//--------------------------------------------------------------------------
	//for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");//очистка чата
	//--------------------------------------------------------------------------
	/*if( strcmp(php_host, "localhost", true) )//для статистики
	{
		if(playerid > HighestPlayerID) {
    		format(strings, sizeof(strings), "%s/UpdateMonitor.php", HostName);//stat1.vw-rp.net/UpdateMonitor.php
			HTTP(MAX_PLAYERS-1, HTTP_GET, strings, "", "");
		}
	}*/

	//--------------------------------------------------------------------------

//кикает игрока//должно быть до презентации
	if(!CheckPlayerName(playerid, PlayerName(playerid))
		 //&& strcmp(php_host, "gta.strikearena.ru", true)
      )//всегда после OnPlayerInit
	{
		IsKicked[playerid] = 1;
		return 1;
	}
////////////////////////////////////////////////////////////////////////////////
	//ИНФОРМИРОВАНИЕ
	//GetPlayerIp(playerid, PlayerInfo[playerid][pIP], 16);//получать ip только при коннекте и больше ни где
    //format(strings, sizeof(strings), "[join] %s[%d] (IP:%s)", PlayerName(playerid), playerid, PlayerInfo[playerid][pIP]);
	//SendSystemMessage(COLOR_DARKBLUE, strings, 1);
	/*if(!AntiReconnect(playerid))//всегда должно быть после получение ip адреса
	{
		IsKicked[playerid] = 1;
		return 1;
	}*/
	if(callback == PlayerDisconnect)
	{
		//--------------------------------------------------------------------------
	    if(spectatorid[playerid] != MAX_PLAYERS-1)
	    {   //если у playerid есть наблюдатель
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
				if( !gPlayerLogged[i] ) continue;
				if(spectateid[i] != playerid) continue;
				ReconOff(i);
				TogglePlayerControllableEx(i, 1);
		        gWatchingTV[i] = -1;
	   		}
		}
		//--------------------------------------------------------------------------
		if(HireCarID[playerid] < MAX_VEHICLES-1)
		{   //если у игрока был автомобиль проката при выходе из игры
			UnLockCar(HireCarID[playerid]);//разблокируем двери HireCarID
		}
		if(LastCar[playerid] > 0 && LastCar[playerid] < MAX_VEHICLES-1)//всегда выполнится LastCar[playerid] !=701 MAX_VEHICLES+1
		{   //если переменная LastCar[playerid] не свободная
			if( !IsInRentCar(LastCar[playerid]) )
			{   //если последняя машина не арендованная
				if(LastDriver[LastCar[playerid]] == playerid)
				{   //если последний водитель этой машины имменно Вы и новая машина не та что была предыдущей
					LastDriver[LastCar[playerid]] = MAX_PLAYERS-1;
					//освобождаем переменную предыдущей машины
					//UnLockCar(LastCar[playerid]);
					//разблокируем двери при выходе из обычной тачки
				}
			}
		}
		//KillTimer(PickupTimer[playerid]);//для анекдотов
		RemovePlayerAllAttachedObjectEx(playerid);
		PlayerKillTimer(playerid);
		/*if(strcmp(php_host, "localhost", true) && reason == 1 && GameRestart != 1)
		{// если не localhost
			new strtmp[52+24];
			format(strtmp, sizeof(strtmp), "%s/UpdatePasport.php?Login=%s", HostName, PlayerName(playerid));
			HTTP(playerid, HTTP_GET, strtmp, "", "");
		}*/
	}

//для скрытия ников
	/*if( !strcmp(php_host, "vw-rp.net", true) )
	{
//при старте режима ники всех видны
		gTagForPlayer[playerid] = 1;//поставили, что ник не скрыт данного игрока
		for(new i = 0; i < MAX_PLAYERS; i++) ShowPlayerNameTagForPlayerEx(playerid, i, 1);//для игрока playerid показать ники всех игроков
	}
	else
	{
//при старте режима ники всех НЕ видны
		gTagForPlayer[playerid] = 0;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			IsPlayerTagShow[i][playerid] = 0; //скрываем ник игрока playerid для всех
		}
	}*/
	//--------------------------------------------------------------------------
//если через 3 секунды произошёл коннект, то обнулить переменную
	//if(GetTickCount() >= gCheckDisconnect[playerid] + 3000)
	gCheckDisconnect[playerid] = 0;
	CrashDetected[playerid] = 0;
	gPlayerLogged[playerid] = 0;//1 - если игрок залогинелся
	gPlayerSpawned[playerid] = 0;//1 - если игрок заспаунился
	gSpawn[playerid] = 0;//переключатель спауна для смены места службы

	votecount[playerid] = 0;//счётчик кол-ва голосов за кик
	PingCount[playerid] = 0;//счётчик кол-ва срабатываний при превышении пинга

	playerCheckpoint[playerid] = 0;//MAX_POINTS;//для УСТАНОВКИ КОНТРОЛЬНЫХ МЕТОК
	CP[playerid] = 0; //для установки чекпоинтов
	gGotOrder[playerid] = MAX_PLAYERS-1;
	gAFK_ToggleMode[playerid] = 0;	AFK_IdleTime[playerid] = 0;//для проверки AwayFromKeyboard
	gGameText[playerid] = 0;
	
    SetPVarInt(playerid, "PlayerID", MAX_PLAYERS-1);
	SetPVarInt(playerid, "gOoc", 1);
	SetPVarInt(playerid, "gNews", 1);
	SetPVarInt(playerid, "gFam", 1);
	SetPVarInt(playerid, "gHidePM", 0);
	SetPVarInt(playerid, "gSport", 1);
	SetPVarInt(playerid, "gJob", 1);
	SetPVarInt(playerid, "gSwitcher", 0);
	SetPVarInt(playerid, "OldSkin", SKIN_DEFAULT);
	//------------------------------------------------------------------------------
	//GuardPrice[playerid] = 0;//Offer[playerid] = MAX_PLAYERS-1; //для телохранителей

	CurState[playerid] = 0;
	LastState[playerid] = 0;
	LastDriver[playerid] = MAX_PLAYERS-1;
	LastCar[playerid] = MAX_VEHICLES+1;//освобождаем переменную предыдущей машины
	nCarID[playerid] = 0;//получить ID машины игрока из списка установленных моделей
	nCarModel[playerid] = 0;//Узнает ID модели данного транспортного средства.

//для попугая
	/*strdel(pParrotSentence[playerid][0],0,MAX_STRING);
	strdel(pParrotSentence[playerid][1],0,MAX_STRING);
	strdel(pParrotSentence[playerid][2],0,MAX_STRING);
	strdel(pParrotSentence[playerid][3],0,MAX_STRING);
	strdel(pParrotSentence[playerid][4],0,MAX_STRING);
	strdel(pParrotName,0,20);
	pHasParrot[playerid] = 0;*/

	return 1;
}//END OnPlayerInit


//##############################################################################//
//                                                                              //
//                             ОБРАБОТЧИКИ СОБЫТИЙ                              //
//                                                                              //
//##############################################################################//


stock player_OnPlayerConnect(playerid)
//public OnPlayerConnect(playerid)
{
	numplayers ++;//кол-во игроков на сервере //после IsPlayerNPC
	if(playerid > HighestPlayerID) { HighestPlayerID = playerid+1; }
	
	OnPlayerInit(playerid, PlayerConnect);

	SendClientMessage(playerid, COLOR_ORANGE, "Game Editor v1.0 {FFFFFF}");
	SendClientMessage(playerid, COLOR_ORANGE, "(USE: ~k~~GROUP_CONTROL_BWD~) общий help");
	SendClientMessage(playerid, COLOR_ORANGE, "(USE: ~k~~PED_ANSWER_PHONE~) для работы с параметрами игрока");
	SendClientMessage(playerid, COLOR_ORANGE, "(USE: ~k~~TOGGLE_SUBMISSIONS~) для работы с параметрами тачки сидя в ней");
	SendClientMessage(playerid, COLOR_ORANGE, "Нажмите на карту и затем введите команду /gps для прокладывания маршрута");
	
    new version[40];
    GetPlayerVersion(playerid, version, sizeof(version));
	if( strcmp(version, "0.3.7-R4", true) )
	{
		new strtmp[69+40];
	    //format(strtmp, sizeof(strtmp), "Your version of SA-MP: %s", version);
	    //SendClientMessage(playerid, 0xFFFFFFFF, strtmp);
	    format(strtmp, sizeof(strtmp), "CEPBEP: {33AA33}Пожалуйста обновите вашу версию SA-MP до {FFFFFF}%s!", version);
	    SendClientMessage(playerid, COLOR_RED, strtmp);
	    SendClientMessage(playerid, COLOR_GREY, "Cкачать последнюю версию SA-MP можно с http://www.sa-mp.com/download.php");
	    //if( !strcmp(php_host, "gta.strikearena.ru", true) ) { IsKicked[playerid] = 1; return 1; }
	}
	if(Security != 0 && strcmp(PlayerName(playerid), CREATOR, true))
	{
	    SendClientMessage(playerid, COLOR_RED, "Aдминистратор временно закрыл вход на сервер.");
	    IsKicked[playerid] = 1;
	    return 1;
	}
	return 1;
}

stock player_OnPlayerSpawn(playerid)
{
	//#pragma unused playerid
	StopAudioStreamForPlayer(playerid);

	//SetPlayerCriminal(member, playerid, killed, reason);
	SetPlayerWantedLevel(playerid, WantedLevel[playerid]);//звёзды

	GetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);

	ResetPlayerMoney(playerid);//Сбросить деньги игрока на 0
	gConsumingMoney[playerid] = CHEATLIM;
	LastHealth[playerid] = 100.0;
	LastState[playerid] = CurState[playerid];
//==============================================================================

	SetPVarInt(playerid, "SpawnSelection", 1);//На всякий случай Игрок произвел выбор спауна при входе
	//чтобы второй раз не предлогался вход по точке выхода, в случаии рестарта мода
}


stock player_OnPlayerDisconnect(playerid, reason)
//public OnPlayerDisconnect(playerid, reason)
{
	//#pragma unused reason
	numplayers --;//после IsPlayerNPC
	if(playerid >= HighestPlayerID+1) HighestPlayerID = playerid - 1;

	OnPlayerInit(playerid, PlayerDisconnect, reason);
	return 1;
}


stock player_OnPlayerDeath(playerid, killerid, reason)
//public OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	
	//if(	PlayerInfo[playerid][pJailed] == 0 &&
	//	!gPlayerBoxing[playerid] && !gInTerrorsCount[playerid] && !gInCTerrorsCount[playerid])
	//{
	CurState[playerid] = PLAYER_STATE_KILLED;
	//gMedicBill[playerid] = 1;//поднимаем флаг для прохождения лечения
	//}
	
	LastKill[killerid] = playerid;//всегда должно быть в конце
	
	gPlayerSpawned[playerid] = 0;
}

//LastDriver - чтобы видеть кто последний ездил на данной тачке
stock player_OnPlayerStateChange(playerid, newstate, oldstate)
//public OnPlayerStateChange(playerid, newstate, oldstate)
{//не вызывается если игрок меняет тачку не меняя место
	//SendAllAdminMessage(COLOR_RED, "CHECKING OnPlayerStateChange !!!", 6);
	if(newstate != oldstate) { CurState[playerid] = newstate; LastState[playerid] = oldstate; }
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{	//если ID нового состояния равно состоянию 2//если ID нового состояния равно состоянию 3 - пассажир

		if(newstate == PLAYER_STATE_DRIVER)
		{
			/*if(LastCar[playerid] > 0 && LastCar[playerid] < MAX_VEHICLES+1)
			{   //если переменная LastCar[playerid] не свободная
				if(	LastDriver[LastCar[playerid]] == playerid &&
					nCarID[playerid] != LastCar[playerid])	//если сели в др. машину то надо освободить переменные предыдущей
				{   //если последний водитель этой машины имменно Вы и новая машина не та что была предыдущей
					LastDriver[LastCar[playerid]] = MAX_PLAYERS-1;//освобождаем переменную последнего водителя
				}
			}*/
			LastDriver[LastCar[playerid]] = MAX_PLAYERS-1;
		}
		LastCar[playerid] = MAX_VEHICLES+1;//освобождаем переменную предыдущей машины
		nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
		nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
		
		format(strings, sizeof(strings), "~g~%s", VehicleArray[nCarModel[playerid]-400][Vehicle_Name] );
		GameTextForPlayerEx(playerid, strings, 3000, 1);
	}
	/*else if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) &&
			newstate != PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)//если ID нового состояния равно состоянию 1( на ногах)
	{   //выполняется только после выхода из машины
		nCarID[playerid] = 0; nCarModel[playerid] = 0;//освобождаем переменную
	}*/
	else if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)//выполняется после выхода из машины
	{	//если ID старого состояния равно состоянию 2//если ID старого состояния равно состоянию 3 - пассажир
		LastCar[playerid] = nCarID[playerid];
		if(oldstate == PLAYER_STATE_DRIVER) LastDriver[nCarID[playerid]] = playerid;//записали ID игрока по машине в которую он садился
		nCarID[playerid] = 0; nCarModel[playerid] = 0;//освобождаем переменную
	}
}

stock player_InteriorChange(playerid, newinteriorid, oldinteriorid)
//public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	if(newinteriorid != oldinteriorid) { CurInt[playerid] = newinteriorid; LastInt[playerid] = oldinteriorid; }
}

stock player_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{//вызывается когда игрок playerid наносит урон игроку damagedid
	LastDamagedid[playerid] = damagedid;
}

stock player_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{   //при год моде и АФК не вызывается

	LastIssuerid[playerid] = issuerid;//записываем последнего кто вам наносил урон
	LastHealth[playerid] -= amount;

}

stock player_OnPlayerUpdate(playerid)
//public OnPlayerUpdate(playerid)
{
	new Float:pX, Float:pY, Float:pZ; //new Float:pA, Float:ang;
	GetPlayerPos(playerid, pX, pY, pZ);	//GetPlayerFacingAngle(forplayerid, pA);
    CurPos[0][playerid] = pX;
	CurPos[1][playerid] = pY;
	CurPos[2][playerid] = pZ;
}

stock IsPlayerInRangeOfPointEx(playerid, Float:range, Float:x, Float:y, Float:z)
{
	new Float:distance;
	distance = floatsqroot(
						floatpower(floatsub(x, CurPos[0][playerid]),2)+
						floatpower(floatsub(y, CurPos[1][playerid]),2)+
						floatpower(floatsub(z, CurPos[2][playerid]),2)
					  );
	if( floatcmp(range, distance) != -1) return 1;//IsPlayerInRangeOfPoint(playerid, range, x, y, z);
/* Compare two integers. If the two elements are equal, return 0.
   If the first argument is greater than the second argument, return 1,
   If the first argument is less than the second argument, return -1. */
	else return 0;
}
//##############################################################################


//Убиваем также разовые таймеры, т.к. они могут быть ещё запущены
stock PlayerKillTimer(playerid)
{
	//KillTimer(stopmusictimer[playerid]); stopmusictimer[playerid] = -1;
	//KillTimer(fixradiotimer[playerid]); fixradiotimer[playerid] = -1;
	//KillTimer(playerblind[playerid]); playerblind[playerid] = -1;
 	KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1;
	//KillTimer(WeaponTimer[playerid]); WeaponTimer[playerid] = -1;
}




