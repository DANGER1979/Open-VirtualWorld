//#include <a_samp>
//##############################################################################//
//                                                                              //
//                          ИДЕНТИФИКАТОРЫ ТАЙМЕРОВ                             //
//                                                                              //
//##############################################################################//
//new starttimer;
//new gStartCountdown;
//new gCountdownCSTimer;
//new gUpdatecstimer;

//new gOffsettimer = -1;

/*
new onesecondtimers;
new onesecondtimers2;
new onesecondtimers3;
new onesecondtimers4;
new oneminutstimer;
new fiveminutstimers;
new fifteenminutstimers;

new carupgradetimer;
new loadcarupgradetimer;
*/


//##############################################################################//
//                                                                              //
//                                 СЧЁТЧИКИ                                     //
//                                                                              //
//##############################################################################//
new checktimedamage[MAX_PLAYERS];//счётчик для односекундного пакетника без спауна

enum SavePosEnum// сохранение позиции //для PlayerIdleKick15Timer //для фермеров
{
    Float:LastX,
    Float:LastY,
    Float:LastZ
};
new SavePos[MAX_PLAYERS][SavePosEnum];//перезаписывается каждые 15 минут
//##############################################################################//
//#                                                                            #//
//#                           БЕСКОНЕЧНЫЕ ТАЙМЕРЫ  (1)                         #//
//#                                                                            #//
//##############################################################################//

/*

forward OneMinutsTimer();
public OneMinutsTimer()
{
	new timers = GetTickCount();
	//--------------------------------------------------------------------------
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		//if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
  	    //if( !gPlayerLogged[i] ) continue;
	    //if( !gPlayerSpawned[i] ) continue;



	}
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OneMinutsTimer", GetTickCount(), timers);
}

forward OnFiveMinutsTimer();
public OnFiveMinutsTimer()
{
	new timers = GetTickCount();
	//--------------------------------------------------------------------------
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		//if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
  	    //if( !gPlayerLogged[i] ) continue;
	    //if( !gPlayerSpawned[i] ) continue;
	    
#if defined vw_speedometer
		roadblock_OnFiveMinutsTimer(i);
#endif

	}
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnFiveMinutsTimer", GetTickCount(), timers);
}

*/

//stock PlayerIdleKick15Timer(playerid)
stock timers_FifteenMinutsTimer(playerid)
{//вызывается из OnFifteenMinutsTimer()
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	if( PlayerInfo[playerid][pAdmin] >= 6 || PlayerInfo[playerid][pAccount] == 365) return 1;
	//if( TutTimeCounter[playerid] > 0) continue;
    if( IsInNPCVehicle( nCarID[playerid] ) )
    {
		if(GetPVarInt(playerid, "gIdleKick") == 1)
		{   //если игрок не переместился
			//new strings[MAX_STRING];
			if(PlayerInfo[playerid][pAdmin] < 9 && PlayerInfo[playerid][pAccount] == 0)
			{
				format(strings, sizeof(strings), "%s[%d] kicked, reason: enter NPC Vehicle > %d minutes", PlayerName(playerid),playerid,idletime);
				SendSystemMessage(COLOR_MAROON, strings, 1);
				Log(KICK,strings);
				SetPVarInt(playerid, "gIdleKick", 0);
				IsKicked[playerid] = 1;
				return 1;
			}
		}
		SetPVarInt(playerid, "gIdleKick", 1);//подняли флаг - игрок катается с ботом
	}
   	if(lH > 8)
   	{   //не кикать днём
		if( PlayerInfo[playerid][pMember] == DoD || PlayerInfo[playerid][pJailed] == 10)
    	{//вояк и зэков находящихся на зоне
			if(IsPlayerInArea(playerid, specialzone[0])) return 1;
		}
		else if(PlayerInfo[playerid][pMember] == DoH)
		{//медиков в госпитале
			if( IsAtHospital(playerid) ) return 1;
		}
		else if(PlayerInfo[playerid][pMember] == DoJ)
		{//членов правительства в Мэрии
			//if(IsPlayerInArea(playerid, specialzone[7])) continue;
			if(PlayerInfo[playerid][pLocal] == 241) return 1;
		}
		else if(PlayerInfo[playerid][pMember] == DoE)
		{	//инструкторов в АШ
       		if( IsPlayerInRangeOfPoint(playerid, 100.0, -2032.6810,-117.4816,1035.1719) ) return 1;
		}
		else if(PlayerInfo[playerid][pJob] == CARDEALER)
		{//автодилеров в АС
			if(IsPlayerInArea(playerid, specialzone[8])) return 1;
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 5.0, SavePos[playerid][LastX], SavePos[playerid][LastY], SavePos[playerid][LastZ]))
	{   //если игрок не переместился
		//new strings[MAX_STRING];
		if(gLoading[playerid]) return 1;
		if(gUnLoading[playerid]) return 1;
		if(PlayerInfo[playerid][pAdmin] < 9 && PlayerInfo[playerid][pAccount] == 0)
		{
			format(strings, sizeof(strings), "%s[%d] kicked, reason: idle one place > %d min", PlayerName(playerid),playerid, idletime);
			SendSystemMessage(COLOR_MAROON, strings, 1);
			Log(KICK, strings);
			IsKicked[playerid] = 1;
			return 1;
		}
	}
	GetPlayerPos(playerid, SavePos[playerid][LastX], SavePos[playerid][LastY], SavePos[playerid][LastZ]);
	return 1;
}

//Начисление прибыли в бизнес и уплата налогов
stock OneHourTimer()//вызывается каждый час из SyncTime(), проверяется каждую минуту
{
	new timers = GetTickCount();

	//Election();
	//if(switcher == 0) {	Election();	switcher = 1; }
	//else { Election_OneDayTimer(); switcher = 0; }
	//--------------------------------------------------------------------------
//если сменился день
	new tmpday;// = getdate();
	getdate(_,_,tmpday);
	if(	(tmpday > LastDay)//если текущий день больше чем предыдущий
		|| (tmpday == 1 && (LastDay == 28 || LastDay == 29 || LastDay == 30 || LastDay == 31))//или текущий день равен 1 и предыдущий равен 30 или 31
	  )//и предыдущее сохранение успешно до конца выполнено
	{
		//Election_OneDayTimer();
		LastDay = tmpday;//записали полученное значение
	}
	//--------------------------------------------------------------------------
  	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i)) continue;
		if( !gPlayerSpawned[i] ) continue;
		if( AFK_IdleTime[i] >= 3 &&//если в АФК пропустить и не начислять ЗП, кроме
			(PlayerInfo[i][pAdmin] != 9 && PlayerInfo[i][pAccount] != 365)) continue;
		if(PlayerInfo[i][pLevel] <= 3)
		{
			SendClientMessage(i, COLOR_YELLOW, "Просмотреть подробное обучение по серверу командой /tutorial");
			SendClientMessage(i, COLOR_GREEN, "Посмотреть все доступные команды и многое другое можно при помощи команды /help или клавиши H");
			//SendClientMessage(i, COLOR_GREEN, "Сменить пароль можно командой /changepass.");
			//SendClientMessage(i, COLOR_GREEN, "Обязательно посетите наш форум "#FORUM" на нем вы найдете всю необходимую информацию!");

			/*new weburl[64];
			GetServerVarAsString("weburl", weburl, sizeof(weburl));
			format(strings, sizeof(strings), "На сайте %s (на вкладке ДОНАТ) можно пополнить счёт,", weburl);
			SendClientMessage(i, COLOR_GREEN, strings);
			SendClientMessage(i, COLOR_GREEN, "чтобы купить игровую валюту, VIP аккаунт или снять варн, очистить преступность (USE: /donat)");
			SendClientMessage(i, COLOR_GREEN, "Чтобы узнать преимущества премиум-аккаунта (USE: /viphelp)");
			SendClientMessage(i, COLOR_GREEN, "Деньги пойдут на раскрутку сервера, покупку рекламы!");*/
		}
	}
	TestLog(OPTIM, "OneHourTimer", GetTickCount(), timers);//new timers = GetTickCount();
}

//##############################################################################//
//#                                                                            #//
//#                    ТАЙМЕРЫ ЗАПУСКАЕМЫЕ ПРИ СТАРТЕ РЕЖИМА                   #//
//#                                                                            #//
//##############################################################################//


stock timers_OnGameModeInit()
{
//ТАЙМЕРЫ 16 - 6%
	//gStartCountdown = 1;
	//starttimer = SetTimer("StartTimers", 300, 1);
	SetTimer("tLoadCarUpgrade", 2500, 0);//RespawnAllCars//для загрузки тюна запускается разово через 2.5 секунд
}

forward tLoadCarUpgrade();//для загрузки тюна таймер
public tLoadCarUpgrade()//вызывается из функции GameModeInit
{
	RespawnAllCars();
#if defined vw_fuel
	FuelAllCars();//Обнаружено длительное выполнение обратного вызова (зависание или проблема производительности)
#endif
	//SendClientMessageToAll(COLOR_GREEN, "   Bсе параметры машин установлены! Доброго пути !");
	//KillTimer(loadcarupgradetimer);
	//loadcarupgradetimer = -1;

	//==========================================================================
	//cargoship_OnGameModeInit();
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
/*
stock timers_OnGameModeExit()
{
	KillTimer(onesecondtimers);
	KillTimer(oneminutstimer);
	KillTimer(fiveminutstimers);
}

stock timers_OnPlayerConnect(playerid)
{
	//KillTimer(introtimer[playerid]); introtimer[playerid] = -1;

	oneseconds[playerid] = 0;//счётчик для 1-секундного пакетника
	twoseconds[playerid] = 0;//счётчик для 2-хсекундного таймера
	threeseconds[playerid] = 0;
	oneminuts[playerid] = 0;
	fiveminuts[playerid] = 0;
	fifteenminuts[playerid] = 0;
	onehour[playerid] = 0;
}
*/

stock RespawnAllCars()
{//вызывается из tLoadCarUpgrade и по команде /res
	new unoccupied[MAX_VEHICLES-1];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
   //если занята
		if( !IsPlayerConnectedEx(i) ) continue;
       	if(IsPlayerInAnyVehicle(i))	unoccupied[nCarID[i]] = 1;//помечаем тачка заняты
    }
	//for(new carid = 1; carid<GetMaxVehicles; carid++)//(MAX_VEHICLES-1)
	for(new carid = GetVehiclePoolSize(); carid > 0; carid--)//Gets the highest vehicleid currently in use on the server.
	//GetMaxVehicles перезаписывается при создании тачек, если тачка создана другим скриптом, то работать не будет
	{
		if(!IsValidVehicle(carid)) continue;//создано ли транспортное средство.
		//VehicleArray[GetVehicleModel(car)-400][Category] != Trailers)
		//ВНИМАНИЕ: трейлер не считается прицепленным когда игрок не сидит за рулём тягача
		/*if( unoccupied[carid] == 1 || unoccupied[IsVehicleAttachedToTrailer(carid)] == 1)//Обнаружено длительное выполнение обратного вызова (зависание или проблема производительности)
	 	{   //занятые тачки не респауним

		}*/
 		if(IsInNPCVehicle(carid) || IsInDerbyCar(carid))
 		{//нпс тачкам включаем двигло и свет
			//new engine, lights, alarm, doors, bonnet, boot, objective;
			//GetVehicleParams(carid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParams(carid, //-1,
				VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
		}
		else if(!unoccupied[carid])
		{   //если тачка пуста
			//if(VehInfo[carid][cType] < 950)
			//{
				gVehicleSpawn[carid] = 1;
				SetVehicleToRespawn(carid);//ВНИМАНИЕ: тачка также починится полностью и востановит здоровье на 1000
				VehInfo[carid][cFuel] = float(VehicleArray[VehInfo[carid][cModel]-400][GasMax]);
				//LastVehHealth[playerid] = 1000;
			/*}
			else
			{
				//gVehicleSpawn[carid] = 1;
				SetVehiclePosEx(carid, VehInfo[carid][cLocX], VehInfo[carid][cLocY], VehInfo[carid][cLocZ]);
		    	SetVehicleZAngleEx(carid, VehInfo[carid][cAng]);
			}*/
		}
	}
}
/*
forward StartTimers();
public StartTimers()//запускается каждые 300 мс сразу при старте мода
{
	if(gStartCountdown == 1)
	{
		onesecondtimers = SetTimer("OneSecondTimers", 1000, 1);
		gStartCountdown = 2;
	}
	else if(gStartCountdown == 2)
	{
		//onesecondtimers2 = SetTimer("OneSecondTimers2", 1000, 1);//для уменьшения срока и для оcвобождения от наручников, для медиков //Проверка на наличие лицензии //Проверка служебных машин
		gStartCountdown = 3;
	}
	else if(gStartCountdown == 3)
	{
		//onesecondtimers3 = SetTimer("OneSecondTimers3", 1000, 1);
		gStartCountdown = 4;
	}
	else if(gStartCountdown == 4)
	{
		//onesecondtimers4 = SetTimer("OneSecondTimers4", 1000, 1);
		gStartCountdown = 5;
	}
	else if(gStartCountdown == 5)
	{
		oneminutstimer = SetTimer("OneMinutsTimer", 60000, 1);//запускает каждые 60 секунд таймеры SyncTime
		gStartCountdown = 6;
	}
	else if(gStartCountdown == 6)
	{
		fiveminutstimers = SetTimer("OnFiveMinutsTimer", 300000, 1);//запускается каждые 5 минут
		gStartCountdown = 7;
	}
	else if(gStartCountdown == 7)
	{
		//fifteenminutstimers = SetTimer("OnFifteenMinutsTimer", 900000, 1);//запускает каждые 150 минут
		gStartCountdown = 0;
		KillTimer(starttimer); starttimer = -1;
	}
}
*/
//##############################################################################//
//                                                                              //
//                    САМОВЫЗЫВАЕМЫЕ ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ                   //
//                                                                              //
//##############################################################################//



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





