//https://forum.sa-mp.com/showthread.php?t=262417
//http://pawn-wiki.ru/index.php?/topic/7499-kak-sqlite-bazovii-uchebnik/
//http://lightcode.ru/showthread.php?t=12976
//#include <a_samp>
//#include <a_sampdb>
/*
Изменения в SQLite: - Функции SQLite db_open и db_query теперь возвращают порядковый индекс запроса (начиная с 1).
Это означает, что сервер теперь отслеживает ошибки в запросах и не рухнет при не правильном запросе.
- Были добавлены серверные дополнительные SQLite функции db_*. Ознакомиться с ними можно в инклюде a_sampdb.inc.
- Добавлена %q в format(). %q - это разновидность %s, но выводит запрос полностью со всей пунктуацией.
- Добавлен параметр в server.cfg 'db_logging' который отслеживает ошибки функций db_*.
- Добавлен параметр в server.cfg 'db_log_queries' который выводит в лог все запросы db_query().
http://www.samp-rus.com/forum/2-26942-1#521215

Добавлено в обновлении сервера 0.3.7 R2-1: - Добавлена пустая величина проверок в sqlite db_get*.
Эти функции уронят сервер если имена полей или ячеек будут указаны с ошибкой.
- Исправлены ошибки в работе системы SHA256_PassHash() sha256.
- Исправлена проблема с индексами в системах PVars и SVars в функции *GetUpperIndex, благодаря которой указывались ID'ы уже удаленных переменных
http://www.samp-rus.com/forum/2-26942-1#521215
*/

stock db_OnGameModeInit()
{
	db_VW = db_open("VW.db"); // file 'your.db' will be our SQLite database
	if(db_VW == DB:0)
	{
		// Error
		print("Failed to open a connection to \"VW.db\".");
		SendRconCommand("exit");
	}
	else
	{	//Creating database if does not exist
		// Success
		// Creates a "player spawn log" table, if it doesn't exists, and frees the result
		//db_free_result(db_query(db_handle, "CREATE TABLE IF NOT EXISTS `spawn_log`(`ID` INTEGER PRIMARY KEY AUTOINCREMENT,`PlayerID` INTEGER NOT NULL,`PlayerName` VARCHAR(24) NOT NULL)"));
		print("Successfully created a connection to \"VW.db\".");
	}
}
stock db_OnGameModeExit()
{
	// If there is a database connection, close it
	if(db_VW) db_close(db_VW);

	return 1;
}

//##############################################################################//
//                                                                              //
//               ВЫПОЛНЯЕТСЯ ПРИ СТАРТЕ РЕЖИМА ИЗ GameModeInit()                //
//                                                                              //
//##############################################################################//

//------------------------------------------------------------------------------

stock LoadSettingsSQL()//для загрузки настроек
{
	new time = GetTickCount();
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `settings`");
	if(db_num_rows(db_result))
	{
		new Field[20];
		db_get_field_assoc(db_result, "AntiCheat", Field, sizeof(Field) ); ANTICHEAT = strval(Field);
		db_get_field_assoc(db_result, "AntiSpeedHack", Field, sizeof(Field) ); ANTISPEEDHACK = strval(Field);
		db_get_field_assoc(db_result, "AntiTeleport", Field, sizeof(Field) ); ANTITELEPORT = strval(Field);
		db_get_field_assoc(db_result, "teleports", Field, sizeof(Field) ); CHEATLIM = strval(Field);
		db_get_field_assoc(db_result, "AntiMoney", Field, sizeof(Field) ); ANTIMONEY = strval(Field);
		db_get_field_assoc(db_result, "AntiHealth", Field, sizeof(Field) ); ANTIHEALTH = strval(Field);
		db_get_field_assoc(db_result, "AntiVehHealth", Field, sizeof(Field) ); ANTIVEHHEALTH = strval(Field);
		db_get_field_assoc(db_result, "AntiGodMod", Field, sizeof(Field) ); ANTIGODMOD = strval(Field);
		db_get_field_assoc(db_result, "AntiGun", Field, sizeof(Field) ); ANTIGUN = strval(Field);
		db_get_field_assoc(db_result, "AntiUnFreeze", Field, sizeof(Field) ); UNFREEZE = strval(Field);
		db_get_field_assoc(db_result, "AntiSwear", Field, sizeof(Field) ); ANTISWEER = strval(Field);
		db_get_field_assoc(db_result, "AntiFlood", Field, sizeof(Field) ); ANTIFLOOD = strval(Field);
		db_get_field_assoc(db_result, "floods", Field, sizeof(Field) ); FLOODLIM = strval(Field);
		db_get_field_assoc(db_result, "MaxPing", Field, sizeof(Field) ); PINGS = strval(Field);
		db_get_field_assoc(db_result, "AwayFromKeyboard", Field, sizeof(Field) ); AFK = strval(Field);
		db_get_field_assoc(db_result, "TimeEsc", Field, sizeof(Field) ); ESCSEC = strval(Field);
		db_get_field_assoc(db_result, "WeathChange", Field, sizeof(Field) ); WEATHCHANGE = strval(Field);
		db_get_field_assoc(db_result, "CarSpawnTime", Field, sizeof(Field) ); CARSPAWN = strval(Field);
		db_get_field_assoc(db_result, "Jackpot", Field, sizeof(Field) ); Jackpot = strval(Field);
		db_get_field_assoc(db_result, "CriminalLevel", Field, sizeof(Field) ); CriminalLevel = strval(Field);
		db_get_field_assoc(db_result, "Tax", Field, sizeof(Field) ); TAX = strval(Field);
		db_get_field_assoc(db_result, "TaxValue", Field, sizeof(Field) ); TaxValue = strval(Field);
		db_get_field_assoc(db_result, "Security", Field, sizeof(Field) ); Security = strval(Field);
		db_get_field_assoc(db_result, "TimeTakeZone", Field, sizeof(Field) ); TimeTakeZone = strval(Field);
		db_get_field_assoc(db_result, "CheckProp", Field, sizeof(Field) ); gCheckProp = strval(Field);
		db_get_field_assoc(db_result, "QTime", Field, sizeof(Field) ); qTime = strval(Field);
		db_get_field_assoc(db_result, "Hunger", Field, sizeof(Field) ); HUNGER = strval(Field);
		db_get_field_assoc(db_result, "IdleKick", Field, sizeof(Field) ); IdleKick = strval(Field);
		db_get_field_assoc(db_result, "Logs", Field, sizeof(Field) ); LOGS = strval(Field);
		db_get_field_assoc(db_result, "Registration", Field, sizeof(Field) ); gTesting = strval(Field);
		db_get_field_assoc(db_result, "Reconnect", Field, sizeof(Field) ); ReconnectDelay = strval(Field);

		db_get_field_assoc(db_result, "FuelCost", Field, sizeof(Field) ); FuelCost = floatstr(Field);
		db_get_field_assoc(db_result, "CompCost", Field, sizeof(Field) ); compcost = strval(Field);
		db_get_field_assoc(db_result, "AntiDB", Field, sizeof(Field) ); AntiDB = strval(Field);
		db_get_field_assoc(db_result, "AntiBH", Field, sizeof(Field) ); AntiBH = strval(Field);
		db_get_field_assoc(db_result, "AntiDM", Field, sizeof(Field) ); AntiDM = strval(Field);
		db_get_field_assoc(db_result, "CheckOnline", Field, sizeof(Field) ); gCheckOnline = strval(Field);
		db_get_field_assoc(db_result, "RealWar", Field, sizeof(Field) ); gRealWar = strval(Field);

		db_get_field_assoc(db_result, "Detective", Field, sizeof(Field) ); StatusJob[1] = strval(Field);//Miner
		db_get_field_assoc(db_result, "Lawyer", Field, sizeof(Field) ); StatusJob[2] = strval(Field);
		db_get_field_assoc(db_result, "RoadWorker", Field, sizeof(Field) ); StatusJob[3] = strval(Field);
		db_get_field_assoc(db_result, "DrugDealer", Field, sizeof(Field) ); StatusJob[4] = strval(Field);
		db_get_field_assoc(db_result, "CarJacker", Field, sizeof(Field) ); StatusJob[5] = strval(Field);
		db_get_field_assoc(db_result, "AutoBuyer", Field, sizeof(Field) ); StatusJob[6] = strval(Field);
		db_get_field_assoc(db_result, "CarMechanic", Field, sizeof(Field) ); StatusJob[7] = strval(Field);
		db_get_field_assoc(db_result, "BodyGuard", Field, sizeof(Field) ); StatusJob[8] = strval(Field);
		db_get_field_assoc(db_result, "ArmsDealer", Field, sizeof(Field) ); StatusJob[9] = strval(Field);
		db_get_field_assoc(db_result, "CarDealer", Field, sizeof(Field) ); StatusJob[10] = strval(Field);
		db_get_field_assoc(db_result, "Inkassator", Field, sizeof(Field) ); StatusJob[11] = strval(Field);
		db_get_field_assoc(db_result, "Bookmaker", Field, sizeof(Field) ); StatusJob[12] = strval(Field);
		db_get_field_assoc(db_result, "TaxiDriver", Field, sizeof(Field) ); StatusJob[13] = strval(Field);
		db_get_field_assoc(db_result, "BusDriver", Field, sizeof(Field) ); StatusJob[14] = strval(Field);
		db_get_field_assoc(db_result, "PaperBoy", Field, sizeof(Field) ); StatusJob[15] = strval(Field);
		db_get_field_assoc(db_result, "Trucker", Field, sizeof(Field) ); StatusJob[16] = strval(Field);
		db_get_field_assoc(db_result, "Trashman", Field, sizeof(Field) ); StatusJob[17] = strval(Field);
	}
	printf("1/19. [Загрузка настроек]: Было загружено - %d, потрачено - %d (ms)", db_num_rows(db_result), (GetTickCount()-time));//new time = GetTickCount();
	db_free_result(db_result);

	ChangeWeath = WEATHCHANGE;
	if(FuelCost <= 0.0 || FuelCost > 3.0) FuelCost = 1.0;
}

stock SaveSettingsSQL()//вызывается из OnPlayerDisconnect GameModeInitExitFunc
{   //ф-ция сохранения параметров игрока
	new time = GetTickCount();
	new ToBase[975];//521+330+14 + 2*10+3*2+1+1+4*3+41*1 + 3+24+2 = 975
	format(ToBase, sizeof(ToBase), "UPDATE `settings` SET AntiCheat=%d,\
AntiSpeedHack=%d,\
AntiTeleport=%d,\
teleports=%d,\
AntiMoney=%d,\
AntiHealth=%d,\
AntiVehHealth=%d,\
AntiGodMod=%d,\
AntiGun=%d,\
AntiUnFreeze=%d,\
AntiSwear=%d,\
AntiFlood=%d,\
floods=%d,\
MaxPing=%d,\
AwayFromKeyboard=%d,\
TimeEsc=%d,\
WeathChange=%d,\
CarSpawnTime=%d,\
Jackpot=%d,\
CriminalLevel=%d,\
Tax=%d,\
TaxValue=%d,\
Security=%d,\
TimeTakeZone=%d,\
CheckProp=%d,\
QTime=%d,\
Hunger=%d,\
IdleKick=%d,\
Logs=%d,\
Registration=%d,\
Reconnect=%d,",
	ANTICHEAT,
	ANTISPEEDHACK,
	ANTITELEPORT,
	CHEATLIM,
	ANTIMONEY,
	ANTIHEALTH,
	ANTIVEHHEALTH,
	ANTIGODMOD,
	ANTIGUN,
	UNFREEZE,
	ANTISWEER,
	ANTIFLOOD,
	FLOODLIM,
	PINGS,
	AFK,
	ESCSEC,
	WEATHCHANGE,
	CARSPAWN,
	Jackpot,
	CriminalLevel,
	TAX,
	TaxValue,
	Security,
	TimeTakeZone,
	gCheckProp,
	qTime,
	HUNGER,
	IdleKick,
	LOGS,
	gTesting,
	ReconnectDelay);

	format(ToBase, sizeof(ToBase), "%sFuelCost=%1.1f,\
CompCost=%d,\
AntiDB=%d,\
AntiBH=%d,\
AntiDM=%d,\
CheckOnline=%d,\
RealWar=%d,\
Detective=%d,\
Lawyer=%d,\
RoadWorker=%d,\
DrugDealer=%d,\
CarJacker=%d,\
AutoBuyer=%d,\
CarMechanic=%d,\
BodyGuard=%d,\
ArmsDealer=%d,\
CarDealer=%d,\
Inkassator=%d,\
Bookmaker=%d,\
TaxiDriver=%d,\
BusDriver=%d,\
PaperBoy=%d,\
Trucker=%d,\
Trashman=%d",
	ToBase,
	FuelCost,
	compcost,
	AntiDB,
	AntiBH,
	AntiDM,
	gCheckOnline,
 	gRealWar,
	StatusJob[1],
	StatusJob[2],
	StatusJob[3],
	StatusJob[4],
	StatusJob[5],
	StatusJob[6],
	StatusJob[7],
	StatusJob[8],
	StatusJob[9],
	StatusJob[10],
	StatusJob[11],
	StatusJob[12],
	StatusJob[13],
	StatusJob[14],
	StatusJob[15],
	StatusJob[16],
	StatusJob[17]);
	db_free_result(db_query(db_VW, ToBase));

//ИНФОРМИРОВАНИЕ
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "1/19. [Сохранение настроек]: Было сохранено - %d, потрачено - %d (ms)", 1, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}



/*
stock OnPlayerLoadTempParameters(playerid, const nameplayer[])//вызывается по команде /showplayerstats
{
	new ToBase[125 + 24+20];
	format(ToBase, sizeof(ToBase), "SELECT * FROM `players_temp` WHERE `Name` = '%s'", nameplayer);//playername);
	new DBResult:db_result = db_query(db_VW, ToBase);
	if(db_num_rows(db_result))
	{
		new Field[20];//длина самого большого параметра
		db_get_field_assoc(db_result, "ID", Field, sizeof(Field) );   PlayerInfo[playerid][pSQLID] = strval(Field);

		db_get_field_assoc(db_result, "Account", Field, sizeof(Field) );   PlayerInfo[playerid][pAccount] = strval(Field);
		db_get_field_assoc(db_result, "Muted", Field, sizeof(Field) );   PlayerInfo[playerid][pMuted] = strval(Field);
		db_get_field_assoc(db_result, "Warns", Field, sizeof(Field) );   PlayerInfo[playerid][pWarns] = strval(Field);
		db_get_field_assoc(db_result, "RespectDay", Field, sizeof(Field) );   PlayerInfo[playerid][pRespectDay] = strval(Field);
		db_get_field_assoc(db_result, "PayCheck", Field, sizeof(Field) );   PlayerInfo[playerid][pPayCheck] = strval(Field);
		db_get_field_assoc(db_result, "PayDay", Field, sizeof(Field) );   PlayerInfo[playerid][pPayTime] = strval(Field);
		db_get_field_assoc(db_result, "Health", Field, sizeof(Field) );   PlayerInfo[playerid][pHealth] = floatstr(Field);
		db_get_field_assoc(db_result, "Interior", Field, sizeof(Field) );   PlayerInfo[playerid][pInt] = strval(Field);
		db_get_field_assoc(db_result, "Pos_x", Field, sizeof(Field) );   PlayerInfo[playerid][pPos_x] = floatstr(Field);
		db_get_field_assoc(db_result, "Pos_y", Field, sizeof(Field) );   PlayerInfo[playerid][pPos_y] = floatstr(Field);
		db_get_field_assoc(db_result, "Pos_z", Field, sizeof(Field) );   PlayerInfo[playerid][pPos_z] = floatstr(Field);
		db_get_field_assoc(db_result, "Virtual", Field, sizeof(Field) );   PlayerInfo[playerid][pVirtual] = strval(Field);
		db_get_field_assoc(db_result, "Local", Field, sizeof(Field) );   PlayerInfo[playerid][pLocal] = strval(Field);
		db_get_field_assoc(db_result, "House", Field, sizeof(Field) );   PlayerInfo[playerid][pHouse] = strval(Field);
		db_get_field_assoc(db_result, "Bizz", Field, sizeof(Field) );   PlayerInfo[playerid][pBizz] = strval(Field);
		db_get_field_assoc(db_result, "ContractTime", Field, sizeof(Field) );   PlayerInfo[playerid][pContractTime] = strval(Field);

		db_get_field_assoc(db_result, "HeadValue", Field, sizeof(Field) );   PlayerInfo[playerid][pHeadValue] = strval(Field);
		db_get_field_assoc(db_result, "Wanted", Field, sizeof(Field) );    WantedPoints[playerid] = strval(Field);

		db_get_field_assoc(db_result, "STD", Field, sizeof(Field) );   PlayerInfo[playerid][pSTD] = strval(Field);

		db_get_field_assoc(db_result, "Reason", Field, sizeof(Field) );   	PlayerInfo[playerid][pReason] = strval(Field);
		db_get_field_assoc(db_result, "CarTime", Field, sizeof(Field) );   PlayerInfo[playerid][pCarTime] = strval(Field);
		db_get_field_assoc(db_result, "Vote", Field, sizeof(Field) );   	PlayerInfo[playerid][pVote] = strval(Field);
		db_get_field_assoc(db_result, "PurposeMurder", Field, sizeof(Field) );   PlayerInfo[playerid][pPurposeMurder] = strval(Field);
		db_get_field_assoc(db_result, "Referal", PlayerInfo[playerid][pReferal], sizeof(Field) );

		db_get_field_assoc(db_result, "Param1", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam1] = strval(Field);
		db_get_field_assoc(db_result, "Param2", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam2] = strval(Field);
		db_get_field_assoc(db_result, "Param3", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam3] = strval(Field);
		db_get_field_assoc(db_result, "Param4", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam4] = strval(Field);
		db_get_field_assoc(db_result, "Param5", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam5] = strval(Field);
	}
	db_free_result(db_result);
}
stock OnPlayerSaveTempParameters(playerid, nameplayer[])//вызывается из OnPlayerDisconnect GameModeInitExitFunc
{   //ф-ция сохранения временных параметров игрока
//параметры, неучаствующие в статистике, а нужны лишь для сохранения прогресса игры
	new ToBase[245+210 + 164+505+3*5+24+6+6+3 + 12 + 12+1+4];
	format(ToBase, sizeof(ToBase), "UPDATE `players_temp` SET Account=%d,\
Muted=%d,\
Warns=%d,\
RespectDay=%d,\
PayCheck=%d,\
PayDay=%d,\
Health=%.1f,\
Interior=%d,\
Pos_x=%.1f,\
Pos_y=%.1f,\
Pos_z=%.1f,\
Virtual=%d,\
Local=%d,\
Bizz=%d,\
ContractTime=%d",
	PlayerInfo[playerid][pAccount],
	PlayerInfo[playerid][pMuted],
	PlayerInfo[playerid][pWarns],
	PlayerInfo[playerid][pRespectDay],
	PlayerInfo[playerid][pPayCheck],
	PlayerInfo[playerid][pPayTime],
	PlayerInfo[playerid][pHealth],
	PlayerInfo[playerid][pInt],
	PlayerInfo[playerid][pPos_x],
	PlayerInfo[playerid][pPos_y],
	PlayerInfo[playerid][pPos_z],
	PlayerInfo[playerid][pVirtual],
	PlayerInfo[playerid][pLocal],
	PlayerInfo[playerid][pBizz],
	PlayerInfo[playerid][pContractTime]);

	format(ToBase, sizeof(ToBase), "%s,HeadValue=%d,\
Wanted=%d,\
STD=%d,\
Reason=%d,\
CarTime=%d,\
Tutorial=%d,\
Vote=%d,\
PurposeMurder=%d,\
Referal='%s',\
Param1=%d,\
Param2=%d,\
Param3=%d,\
Param4=%d,\
Param5=%d WHERE `Name`='%s'",
	ToBase,
	PlayerInfo[playerid][pHeadValue],
	WantedPoints[playerid],
	PlayerInfo[playerid][pSTD]
	PlayerInfo[playerid][pReason],
	PlayerInfo[playerid][pCarTime],
	PlayerInfo[playerid][pVote],
	PlayerInfo[playerid][pPurposeMurder],
	PlayerInfo[playerid][pReferal],
	PlayerInfo[playerid][pParam1],
	PlayerInfo[playerid][pParam2],
	PlayerInfo[playerid][pParam3],
	PlayerInfo[playerid][pParam4],
	PlayerInfo[playerid][pParam5],
	nameplayer);
	db_free_result(db_query(db_VW, ToBase));

	return 1;
}*/
stock list_OnPlayerDisconnect(playerid)
{
	//для монитора
	PlayerInfo[playerid][pOffline] = getdate();//записали день выхода с серва
//TestLog(OPTIM, "OnPlayerDisconnect1.1", GetTickCount(), timers, 1);
	new ToBase[87];//60 + 3+24 = 87
    if(PlayerInfo[playerid][pSQLID] > 0)
    {
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `ID`=%d",
			PlayerInfo[playerid][pOffline], PlayerInfo[playerid][pSQLID]);
	}
	else
	{
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `Name`='%s'",
			PlayerInfo[playerid][pOffline], PlayerName(playerid));
	}
	db_free_result(db_query(db_VW, ToBase));
}

stock LoadCarSQL()
{
	new time = GetTickCount();
	new carid = 1;//356+131 +
	//new Data[11 + 3+4+10+24+6*4+2+10+1+3+4+10 +3+5+3+3+3+3+4*15+6+10+10+4+4 + 12];
	new Field[24];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `vehicles`", Field, sizeof(Field) );
	do//while(mysql_fetch_row_format(Data, "|"))
	{
		if(carid >= MAX_VEHICLES-1) break;//для предотвращения переполнения массива
		db_get_field_assoc(db_result, "IND", Field, sizeof(Field) );   VehInfo[carid][cIND] = strval(Field);
		db_get_field_assoc(db_result, "Model", Field, sizeof(Field) );   VehInfo[carid][cModel] = strval(Field);
		//if(VehInfo[carid][cModel] < 400) continue;
		db_get_field_assoc(db_result, "Type", Field, sizeof(Field) );   VehInfo[carid][cType] = strval(Field);
		db_get_field_assoc(db_result, "Owned", Field, sizeof(Field) );   VehInfo[carid][cOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) );   strmid(VehInfo[carid][cOwner], Field, 0, strlen(Field), 24);
		db_get_field_assoc(db_result, "LocX", Field, sizeof(Field) );   VehInfo[carid][cLocX] = floatstr(Field);
		db_get_field_assoc(db_result, "LocY", Field, sizeof(Field) );   VehInfo[carid][cLocY] = floatstr(Field);
		db_get_field_assoc(db_result, "LocZ", Field, sizeof(Field) );   VehInfo[carid][cLocZ] = floatstr(Field);
		db_get_field_assoc(db_result, "Ang", Field, sizeof(Field) );   VehInfo[carid][cAng] = floatstr(Field);
		db_get_field_assoc(db_result, "Int", Field, sizeof(Field) );   VehInfo[carid][cInt] = strval(Field);
		db_get_field_assoc(db_result, "Virt", Field, sizeof(Field) );   VehInfo[carid][cVirt] = strval(Field);
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) );   VehInfo[carid][cLock] = strval(Field);

		db_get_field_assoc(db_result, "Park", Field, sizeof(Field) );   VehInfo[carid][cPark] = strval(Field);
		db_get_field_assoc(db_result, "Attach", Field, sizeof(Field) );   VehInfo[carid][cAttach] = strval(Field);
		db_get_field_assoc(db_result, "Insur", Field, sizeof(Field) );   VehInfo[carid][cInsur] = strval(Field);

		db_get_field_assoc(db_result, "Fuel", Field, sizeof(Field) );   VehInfo[carid][cFuel] = float(strval(Field));
		db_get_field_assoc(db_result, "Load", Field, sizeof(Field) );   VehInfo[carid][cLoad] = strval(Field);
		db_get_field_assoc(db_result, "LoadType", Field, sizeof(Field) );   VehInfo[carid][cLoadType] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) );   VehInfo[carid][cDate] = strval(Field);
		db_get_field_assoc(db_result, "Color1", Field, sizeof(Field) );   VehInfo[carid][cColor1] = strval(Field);
		db_get_field_assoc(db_result, "Color2", Field, sizeof(Field) );   VehInfo[carid][cColor2] = strval(Field);
		db_get_field_assoc(db_result, "Paintjob", Field, sizeof(Field) );   VehInfo[carid][cPaintjob] = strval(Field);
		db_get_field_assoc(db_result, "Spoiler", Field, sizeof(Field) );   VehInfo[carid][cSpoiler] = strval(Field);
		db_get_field_assoc(db_result, "Hood", Field, sizeof(Field) );   VehInfo[carid][cHood] = strval(Field);
		db_get_field_assoc(db_result, "Roof", Field, sizeof(Field) );   VehInfo[carid][cRoof] = strval(Field);
		db_get_field_assoc(db_result, "Sideskirt", Field, sizeof(Field) );   VehInfo[carid][cSideskirt] = strval(Field);
		db_get_field_assoc(db_result, "Lamps", Field, sizeof(Field) );   VehInfo[carid][cLamps] = strval(Field);
		db_get_field_assoc(db_result, "Nitro", Field, sizeof(Field) );   VehInfo[carid][cNitro] = strval(Field);
		db_get_field_assoc(db_result, "Exhaust", Field, sizeof(Field) );   VehInfo[carid][cExhaust] = strval(Field);
		db_get_field_assoc(db_result, "Wheels", Field, sizeof(Field) );   VehInfo[carid][cWheels] = strval(Field);
		db_get_field_assoc(db_result, "Stereos", Field, sizeof(Field) );   VehInfo[carid][cStereos] = strval(Field);
		db_get_field_assoc(db_result, "Hydraulics", Field, sizeof(Field) );   VehInfo[carid][cHydraulics] = strval(Field);
		db_get_field_assoc(db_result, "FrontBumper", Field, sizeof(Field) );   VehInfo[carid][cFrontBumper] = strval(Field);
		db_get_field_assoc(db_result, "RearBumper", Field, sizeof(Field) );   VehInfo[carid][cRearBumper] = strval(Field);
		db_get_field_assoc(db_result, "VentRight", Field, sizeof(Field) );   VehInfo[carid][cVentRight] = strval(Field);
		db_get_field_assoc(db_result, "VentLeft", Field, sizeof(Field) );   VehInfo[carid][cVentLeft] = strval(Field);
		db_get_field_assoc(db_result, "Health", Field, sizeof(Field) );   VehInfo[carid][cHealth] = floatstr(Field); VehHealth[carid] = VehInfo[carid][cHealth];
		db_get_field_assoc(db_result, "Panels", Field, sizeof(Field) );   VehInfo[carid][DamagePanels] = strval(Field);
		db_get_field_assoc(db_result, "Doors", Field, sizeof(Field) );   VehInfo[carid][DamageDoors] = strval(Field);
		db_get_field_assoc(db_result, "Lights", Field, sizeof(Field) );   VehInfo[carid][DamageLights] = strval(Field);
		db_get_field_assoc(db_result, "Tires", Field, sizeof(Field) );   VehInfo[carid][DamageTires] = strval(Field);
		//----------------------------------------------------------------------
		//ИНИЦИАЛИЗАЦИЯ
		if(60 <= VehInfo[carid][cType] < 100) { NPCCar[index1] = carid; index1 ++; }//всего 16
		else if(100 <= VehInfo[carid][cType] < 150) { IntCar[index2] = carid; index2 ++; }//всего 12
		else if(150 <= VehInfo[carid][cType] < 200) { DerbyCar[index3] = carid; index3 ++; }//всего 10(ID 9-18) //для дерби BloodBowl
		else if(200 <= VehInfo[carid][cType] < 250) { LessonCar[index4] = carid; index4 ++; }//всего 3
		else if(250 <= VehInfo[carid][cType] < 300) { TruckCar[index5] = carid; index5 ++; }//всего 13
		else if(300 <= VehInfo[carid][cType] < 350) { Trailer[index6] = carid; index6 ++; }//всего 25
		else if(350 <= VehInfo[carid][cType] < 400) { RentCar[index7] = carid; index7 ++; }//всего 12
		else if(400 <= VehInfo[carid][cType] < 450) { BikerCar[index8] = carid; index8 ++; }//всего 6
		else if(450 <= VehInfo[carid][cType] < 500) { Skimmer[index9] = carid; index9 ++; }//всего 7
		//else if(500 <= VehInfo[carid][cType] < 550) { Airplane[index10] = carid; index10 ++; }
		//else if(550 <= VehInfo[carid][cType] < 600) { Boat[index11] = carid; index11 ++; }
		else if(600 <= VehInfo[carid][cType] < 950) { VehInfo[carid][cType] = 600+index12; PublicCar[index12] = carid; index12 ++; }//всего 350
		//else if(950 <= VehInfo[carid][cType] < 960) { DerbylCar8ball[index13] = carid; index13 ++; }//для дерби 8ball
		//else if(960 <= VehInfo[carid][cType] < 980) { AdminCars[index14] = carid; index14 ++; }
		//else if(1000 <= VehInfo[carid][cType] < 1400) { Car[index15] = carid; index15 ++; }

		new vehicleid;
		if(	VehInfo[carid][cModel] == 449 ||
			VehInfo[carid][cModel] == 537 || VehInfo[carid][cModel] == 569 || VehInfo[carid][cModel] == 590 ||
			VehInfo[carid][cModel] == 538 || VehInfo[carid][cModel] == 570)
		{
			if(VehInfo[carid][cModel] == 569 || VehInfo[carid][cModel] == 590 || VehInfo[carid][cModel] == 570)
			{
				vehicleid = carid;//VehInfo[VehiclesCounter][cID] + 1;
			}
		 	else if(VehInfo[carid][cModel] == 449 || VehInfo[carid][cModel] == 538)
		 	{
		 		vehicleid =	AddStaticVehicle(VehInfo[carid][cModel], VehInfo[carid][cLocX],VehInfo[carid][cLocY],VehInfo[carid][cLocZ], VehInfo[carid][cAng],
				 	VehInfo[carid][cColor1], VehInfo[carid][cColor2]);
				gVehicleSpawn[vehicleid] = 1;
			}
		}
		else if(VehInfo[carid][cType] < 1000)//950
		{
	 		vehicleid =	AddStaticVehicleEx(VehInfo[carid][cModel], VehInfo[carid][cLocX],VehInfo[carid][cLocY],VehInfo[carid][cLocZ], VehInfo[carid][cAng],
			 	VehInfo[carid][cColor1], VehInfo[carid][cColor2], (CARSPAWN*60));
		}
		else
		{   //создаём тачки без спауна
			vehicleid =	CreateVehicle(VehInfo[carid][cModel], VehInfo[carid][cLocX],VehInfo[carid][cLocY],VehInfo[carid][cLocZ], VehInfo[carid][cAng],
				VehInfo[carid][cColor1], VehInfo[carid][cColor2], -1);//отключаем респаун
			gVehicleSpawn[vehicleid] = 1;
		}
		CarStatus[vehicleid][st_engine] = VEHICLE_PARAMS_OFF;
		CarStatus[vehicleid][st_lights] = VEHICLE_PARAMS_OFF;
		CarStatus[vehicleid][st_alarm] = VEHICLE_PARAMS_OFF;
		CarStatus[vehicleid][st_doors] = VEHICLE_PARAMS_OFF;
		CarStatus[vehicleid][st_bonnet] = VEHICLE_PARAMS_OFF;
		CarStatus[vehicleid][st_boot] = VEHICLE_PARAMS_OFF;
		CarStatus[vehicleid][st_objective] = VEHICLE_PARAMS_OFF;

		VehPos[vehicleid][0] = VehInfo[carid][cLocX];
		VehPos[vehicleid][1] = VehInfo[carid][cLocY];
		VehPos[vehicleid][2] = VehInfo[carid][cLocZ];
		VehPos[vehicleid][3] = VehInfo[carid][cAng];

		VehiclesCounter ++;//чтобы начиналось с 1

		//if((VehInfo[carid][cLock] == 1 || VehInfo[carid][cLock] == 11) && VehInfo[carid][cPark] == 1)
		//{   //закрыть двери
		//	SetVehicleParams(vehicleid,-1,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_ON,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);
		//}
		//else SetVehicleParams(vehicleid,-1,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);

		if(VehInfo[vehicleid][cPark] == 1) LockCar(vehicleid);
		else if(VehInfo[vehicleid][cPark] == 2) UnLockCar(vehicleid);
		else if(VehInfo[vehicleid][cPark] >= 10 && VehInfo[vehicleid][cPark] < 100 ) UnLockCar(vehicleid);
		else if(VehInfo[vehicleid][cPark] >= 100 && VehInfo[vehicleid][cPark] < 1000 ) UnLockCar(vehicleid);
		else if(VehInfo[vehicleid][cPark] >= 1000) UnLockCar(vehicleid);
		else
		{
			if(VehInfo[vehicleid][cLock] == 1 || VehInfo[vehicleid][cLock] == 11) LockCar(vehicleid);
		}

		new Found = 0;
		for(new i=1; i<=VehiclesCounter; i++)//MAX_VEHICLES //VehiclesCounter //GetMaxVehicles
		{   //сканируем все тачки, добавленные в мод
			if(VehInfo[carid][cModel] == aExistModel[i]) { Found = 1; break; }
		}
	   	if(Found == 0)
	   	{   //если не нашли и дошли до конца массива, создаем массив различных моделей
			aExistModel[VehiclesModelsCounter] = VehInfo[carid][cModel];
			//printf("aExistModel[%d] = %d", VehiclesModelsCounter, aExistModel[VehiclesModelsCounter]);//для проверки ограничения
			VehiclesModelsCounter ++;
		}

		//if( strcmp(VehInfo[vehicleid][cOwner], "The State", true) )
		if(VehInfo[vehicleid][cType] >= 1000)
		{
			new numberplate[MAX_PLAYER_NAME+10];
			format(numberplate, sizeof(numberplate), "%s [ %d ]", VehInfo[vehicleid][cOwner], vehicleid);
		    //number3D[vehicleid] = Create3DTextLabel(numberplate,0xEEEEEE50,0.0,0.0,0.0,15.0,0,1);
		    //Counter3DText ++;
		    //Attach3DTextLabelToVehicle(number3D[vehicleid], vehicleid, 0.0, -1.6, -0.35);
		    number3D[vehicleid] = Create3DTextLabelEx(numberplate,0xEEEEEE50,0.0, -1.6, -0.35,15.0, INVALID_PLAYER_ID, vehicleid, 1, 0); 

			if(VehInfo[carid][cPark] >= 100 && VehInfo[carid][cPark] < 1000)// && PlayerInfo[playerid][pSQLID] == VehInfo[carid][cOwned]
			{
				new text[39+10];
		   		format(text, sizeof(text), " Сдаётся.\n{FFFFFF}Цена: {33AA33}$%d", VehInfo[carid][cPark]);
			    //sale3D[carid] = Create3DTextLabel(text, COLOR_LIGHTBLUE, 0.0,0.0,0.0, 50.0,0,1);
			    //Counter3DText ++;
			    //Attach3DTextLabelToVehicle(sale3D[carid], carid, 0.0, 0.0, 1.0);
			    sale3D[carid] = Create3DTextLabelEx(text, COLOR_LIGHTBLUE, 0.0,0.0,1.0, 50.0, INVALID_PLAYER_ID, carid, 1, 0); 
			}
			else if(VehInfo[carid][cPark] >= 1000)// && PlayerInfo[playerid][pSQLID] == VehInfo[carid][cOwned]
			{
				new text[39+10];
		   		format(text, sizeof(text), " Продаётся.\n{FFFFFF}Цена: {33AA33}$%d", VehInfo[carid][cPark]);
			    //sale3D[carid] = Create3DTextLabel(text, COLOR_LIGHTBLUE, 0.0,0.0,0.0, 50.0,0,1);
			    //Counter3DText ++;
			    //Attach3DTextLabelToVehicle(sale3D[carid], carid, 0.0, 0.0, 1.0);
			    sale3D[carid] = Create3DTextLabelEx(text, COLOR_LIGHTBLUE, 0.0,0.0,1.0, 50.0, INVALID_PLAYER_ID, carid, 1, 0); 
			}
	    }

		if(VehInfo[carid][cPark] >= PARKING && VehInfo[carid][cPark] < PARKING+sizeof(Parking))
		{
			SBizInfo[VehInfo[carid][cPark]][sbProducts] ++;
		}

		VehInfo[carid][cID] = vehicleid;
		new ToBase[45+4+11];
		format(ToBase, sizeof(ToBase), "UPDATE `vehicles` SET `ID`=%d WHERE `IND`=%d", VehInfo[carid][cID], VehInfo[carid][cIND]);
		db_free_result(db_query(db_VW, ToBase));

		LinkVehicleToInterior(vehicleid, VehInfo[vehicleid][cInt]);
		SetVehicleVirtualWorld(vehicleid, VehInfo[vehicleid][cVirt]);
//printf("id: %d", carid);
		carid ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
	GetMaxVehicles = VehiclesCounter;//+1
//printf("GetMaxVehicles: %d", GetMaxVehicles);
    printf("16/19. [Загрузка транспорта]: Было загружено - %d, потрачено - %d (ms)", carid-1, GetTickCount() - time);//new time = GetTickCount();
	return 1;
}


stock SaveCarSQL()
{   //запускается каждый час
	new time = GetTickCount();
	new cartmp;
	for(new idx=1; idx < (MAX_VEHICLES-1); idx++)
	{
		if(VehInfo[idx][cModel] < 400) continue;//VehInfo[idx][cModel] = GetVehicleModel(idx);
//------------------------------------------------------------------------------
//для вайпа начало
		if(VehInfo[idx][cType] < 960) continue;//пропускаем статические тачки
		//if(VehInfo[idx][cType] < 600) continue;//пропускаем статические тачки
		//if(VehInfo[idx][cType] >= 950 && VehInfo[idx][cType] < 960) continue;//пропускаем DerbylCar8ball тачки, т.к. в новый час могут удалиться с под жопы

//УДАЛЕНИЕ ТАЧЕК после часовой проверки
//т.е. пытаемся каждый час удалить тачки свалки или тачки с большим пробегом
		if(	//VehInfo[idx][cType] >= 960 && (//удаляем админские тачки и личные
			VehInfo[idx][cPark] == 2 ||//удаляем тачки на свалке
			//(getdate()-VehInfo[idx][cDate]) >= DestroyDate ||
			VehInfo[idx][cDist] >= 9999999//)
		  )
		{   //если разница между текущей датой и датой покупки больше 15 дней
			//new Float: price = compcost*(100+SBizInfo[57][sbSellProd])/100.0;//15*(100+10)/100 = 16,5
			new cost = VehicleArray[VehInfo[idx][cModel]-400][Virtual_Price]*(SBizInfo[57][sbSellProd])/100;//37282*10/100 = 3728,2
			OnGangsExtortionSBiz(57, cost);
			SBizInfo[57][sbProducts] --;
			DestroyVehicleEx(idx, 1);
		}//удалит также админские тачки, если они были созданы

//пропускаем запаркованные тачки
		if(VehInfo[idx][cPark] == 1) continue;
		if(VehInfo[idx][cPark] >= 10) continue;
//для вайпа конец
//------------------------------------------------------------------------------
		if(VehInfo[idx][cType] < 1000) continue;//не обновляем позицию халявных тачек

	 	GetVehiclePos(idx, VehInfo[idx][cLocX], VehInfo[idx][cLocY], VehInfo[idx][cLocZ]);
		GetVehicleZAngle(idx, VehInfo[idx][cAng]);

	    GetVehicleHealth(idx, VehInfo[idx][cHealth]);
		GetVehicleDamageStatus(idx,VehInfo[idx][DamagePanels],VehInfo[idx][DamageDoors],VehInfo[idx][DamageLights],VehInfo[idx][DamageTires]);

		new ToBase[550+16 + 3+4+10+24+6*4+2+10+1+3+4+10 +3+5+3+3+3+3+4*15+6+10+10+4+4 + 11+ 12];
		strcat(ToBase, "UPDATE `vehicles` SET");
		format(ToBase, sizeof(ToBase), "%s Model=%d,\
Type=%d,\
Owned=%d,\
Owner='%s',\
LocX=%.1f,\
LocY=%.1f,\
LocZ=%.1f,\
Ang=%.1f,\
`Int`=%d,\
Virt=%d,\
`Lock`=%d,\
Park=%d,\
Attach=%d,\
Insur=%d,\
Fuel=%d,\
`Load`=%d,\
LoadType=%d,\
Color1=%d,\
Color2=%d,\
Paintjob=%d,\
Spoiler=%d,\
Hood=%d,\
Roof=%d,\
Sideskirt=%d,\
Lamps=%d,\
Nitro=%d,\
Exhaust=%d,\
Wheels=%d,\
Stereos=%d,\
Hydraulics=%d,\
FrontBumper=%d,\
RearBumper=%d,\
VentRight=%d,\
VentLeft=%d,\
Health=%.1f,\
Panels=%d,\
Doors=%d,\
Lights=%d,\
Tires=%d WHERE `IND`=%d",ToBase,
		VehInfo[idx][cModel],
		VehInfo[idx][cType],
		VehInfo[idx][cOwned],
		VehInfo[idx][cOwner],
		VehInfo[idx][cLocX],
		VehInfo[idx][cLocY],
		VehInfo[idx][cLocZ],
		VehInfo[idx][cAng],
		VehInfo[idx][cInt],
		VehInfo[idx][cVirt],
		VehInfo[idx][cLock],
		VehInfo[idx][cPark],
		VehInfo[idx][cAttach],
		VehInfo[idx][cInsur],
		floatround(VehInfo[idx][cFuel]),
		VehInfo[idx][cLoad],
		VehInfo[idx][cLoadType],
		//VehInfo[idx][cDate],
		VehInfo[idx][cColor1],
		VehInfo[idx][cColor2],
		VehInfo[idx][cPaintjob],
		VehInfo[idx][cSpoiler],
		VehInfo[idx][cHood],
		VehInfo[idx][cRoof],
		VehInfo[idx][cSideskirt],
		VehInfo[idx][cLamps],
		VehInfo[idx][cNitro],
		VehInfo[idx][cExhaust],
		VehInfo[idx][cWheels],
		VehInfo[idx][cStereos],
		VehInfo[idx][cHydraulics],
		VehInfo[idx][cFrontBumper],
		VehInfo[idx][cRearBumper],
		VehInfo[idx][cVentRight],
		VehInfo[idx][cVentLeft],
		VehInfo[idx][cHealth],
		VehInfo[idx][DamagePanels],
		VehInfo[idx][DamageDoors],
		VehInfo[idx][DamageLights],
		VehInfo[idx][DamageTires],
		VehInfo[idx][cIND]);
		db_free_result(db_query(db_VW, ToBase));
//printf("IND: %d, vehicleid: %d, model: %d", VehInfo[idx][cIND], idx, VehInfo[idx][cModel]);
		cartmp ++;
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[73+2+6];
	format(strtmp, sizeof(strtmp), "15/19. [Сохранение транспорта]: Было сохранено - %d, потрачено - %d (ms)", cartmp, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
	return 1;
}



stock SaveCarParameters(vehicleid)//вызывается при /buycar /savecar /parking /dropcar и при нажатии num8
{
	new timers = GetTickCount();
	if(vehicleid <= 0) return 1;
	if(VehInfo[vehicleid][cModel] < 400) return 1;
	if(VehInfo[vehicleid][cType] < 1000) return 1;

 	GetVehiclePos(vehicleid, VehInfo[vehicleid][cLocX], VehInfo[vehicleid][cLocY], VehInfo[vehicleid][cLocZ]);
	GetVehicleZAngle(vehicleid, VehInfo[vehicleid][cAng]);
    GetVehicleHealth(vehicleid, VehInfo[vehicleid][cHealth]);
	GetVehicleDamageStatus(vehicleid,
		VehInfo[vehicleid][DamagePanels], VehInfo[vehicleid][DamageDoors],
		VehInfo[vehicleid][DamageLights], VehInfo[vehicleid][DamageTires]);
//TestLog(OPTIM, "SaveCarParameters1", GetTickCount(), timers);

	//if(VehInfo[vehicleid][cPaintjob] == 255) VehInfo[vehicleid][cPaintjob] = 255;
	if(!IsValidComponent(VehInfo[vehicleid][cSpoiler], CARMODTYPE_SPOILER)) VehInfo[vehicleid][cSpoiler] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cHood], CARMODTYPE_HOOD)) VehInfo[vehicleid][cHood] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cRoof], CARMODTYPE_ROOF)) VehInfo[vehicleid][cRoof] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cSideskirt], CARMODTYPE_SIDESKIRT)) VehInfo[vehicleid][cSideskirt] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cLamps], CARMODTYPE_LAMPS)) VehInfo[vehicleid][cLamps] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cNitro], CARMODTYPE_NITRO)) VehInfo[vehicleid][cNitro] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cExhaust], CARMODTYPE_EXHAUST)) VehInfo[vehicleid][cExhaust] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cWheels], CARMODTYPE_WHEELS)) VehInfo[vehicleid][cWheels] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cStereos], CARMODTYPE_STEREO)) VehInfo[vehicleid][cStereos] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cHydraulics], CARMODTYPE_HYDRAULICS)) VehInfo[vehicleid][cHydraulics] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cFrontBumper], CARMODTYPE_FRONT_BUMPER)) VehInfo[vehicleid][cFrontBumper] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cRearBumper], CARMODTYPE_REAR_BUMPER)) VehInfo[vehicleid][cRearBumper] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cVentRight], CARMODTYPE_VENT_RIGHT)) VehInfo[vehicleid][cVentRight] = 0;
	if(!IsValidComponent(VehInfo[vehicleid][cVentLeft], CARMODTYPE_VENT_LEFT)) VehInfo[vehicleid][cVentLeft] = 0;
//TestLog(OPTIM, "SaveCarParameters2", GetTickCount(), timers);

	new ToBase[798];//550+16 + 3+4+10+24+6*4+2+10+1+3+4+10 +3+5+3+3+3+3+4*15+6+10+10+4+4 + 11 + 12 = 798
	strcat(ToBase, "UPDATE `vehicles` SET");
	format(ToBase, sizeof(ToBase), "%s Model=%d,\
Type=%d,\
Owned=%d,\
Owner='%s',\
LocX=%.1f,\
LocY=%.1f,\
LocZ=%.1f,\
Ang=%.1f,\
`Int`=%d,\
Virt=%d,\
`Lock`=%d,\
Park=%d,\
Attach=%d,\
Insur=%d,\
Fuel=%d,\
`Load`=%d,\
LoadType=%d,\
Color1=%d,\
Color2=%d,\
Paintjob=%d,\
Spoiler=%d,\
Hood=%d,\
Roof=%d,\
Sideskirt=%d,\
Lamps=%d,\
Nitro=%d,\
Exhaust=%d,\
Wheels=%d,\
Stereos=%d,\
Hydraulics=%d,\
FrontBumper=%d,\
RearBumper=%d,\
VentRight=%d,\
VentLeft=%d,\
Health=%.1f,\
Panels=%d,\
Doors=%d,\
Lights=%d,\
Tires=%d WHERE `IND`=%d",ToBase,
	VehInfo[vehicleid][cModel],
	VehInfo[vehicleid][cType],
	VehInfo[vehicleid][cOwned],
	VehInfo[vehicleid][cOwner],
	VehInfo[vehicleid][cLocX],
	VehInfo[vehicleid][cLocY],
	VehInfo[vehicleid][cLocZ],
	VehInfo[vehicleid][cAng],
	VehInfo[vehicleid][cInt],
	VehInfo[vehicleid][cVirt],
	VehInfo[vehicleid][cLock],
	VehInfo[vehicleid][cPark],
	VehInfo[vehicleid][cAttach],
	VehInfo[vehicleid][cInsur],
	floatround(VehInfo[vehicleid][cFuel]),
	VehInfo[vehicleid][cLoad],
	VehInfo[vehicleid][cLoadType],
	//VehInfo[vehicleid][cDate],
	VehInfo[vehicleid][cColor1],
	VehInfo[vehicleid][cColor2],
	VehInfo[vehicleid][cPaintjob],
	VehInfo[vehicleid][cSpoiler],
	VehInfo[vehicleid][cHood],
	VehInfo[vehicleid][cRoof],
	VehInfo[vehicleid][cSideskirt],
	VehInfo[vehicleid][cLamps],
	VehInfo[vehicleid][cNitro],
	VehInfo[vehicleid][cExhaust],
	VehInfo[vehicleid][cWheels],
	VehInfo[vehicleid][cStereos],
	VehInfo[vehicleid][cHydraulics],
	VehInfo[vehicleid][cFrontBumper],
	VehInfo[vehicleid][cRearBumper],
	VehInfo[vehicleid][cVentRight],
	VehInfo[vehicleid][cVentLeft],
	VehInfo[vehicleid][cHealth],
	VehInfo[vehicleid][DamagePanels],
	VehInfo[vehicleid][DamageDoors],
	VehInfo[vehicleid][DamageLights],
	VehInfo[vehicleid][DamageTires],
	VehInfo[vehicleid][cIND]);
	db_free_result(db_query(db_VW, ToBase));

	TestLog(OPTIM, "SaveCarParameters", GetTickCount(), timers);//new timers = GetTickCount();
//ИНФОРМИРОВАНИЕ
	new strtmp[73+2+6];
	format(strtmp, sizeof(strtmp), "[Сохранение тюнинга]: vehicleid - %d[%d], потрачено - %d (ms)", vehicleid, VehInfo[vehicleid][cModel], (GetTickCount()-timers));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
	return 1;
}

stock SaveTrailerParameters(vehicleid)//вызывается при /buycar /savecar /parking /dropcar и при нажатии num8
{
	new timers = GetTickCount();
	if(vehicleid <= 0) return 1;
	if(VehInfo[vehicleid][cModel] < 400) return 1;
	if(VehInfo[vehicleid][cType] < 1000) return 1;

 	GetVehiclePos(vehicleid, VehInfo[vehicleid][cLocX], VehInfo[vehicleid][cLocY], VehInfo[vehicleid][cLocZ]);
	GetVehicleZAngle(vehicleid, VehInfo[vehicleid][cAng]);
    //GetVehicleHealth(vehicleid, VehInfo[vehicleid][cHealth]);

	new ToBase[798];//550+16 + 3+4+10+24+6*4+2+10+1+3+4+10 +3+5+3+3+3+3+4*15+6+10+10+4+4 + 11 + 12 = 798
	strcat(ToBase, "UPDATE `vehicles` SET");
	format(ToBase, sizeof(ToBase), "%s Model=%d,\
Type=%d,\
Owned=%d,\
Owner='%s',\
LocX=%.1f,\
LocY=%.1f,\
LocZ=%.1f,\
Ang=%.1f,\
`Int`=%d,\
Virt=%d,\
`Lock`=%d,\
Park=%d,\
Attach=%d,\
Insur=%d,\
Fuel=%d,\
`Load`=%d,\
LoadType=%d,\
Color1=%d,\
Color2=%d,\
Paintjob=%d,\
Spoiler=%d,\
Hood=%d,\
Roof=%d,\
Sideskirt=%d,\
Lamps=%d,\
Nitro=%d,\
Exhaust=%d,\
Wheels=%d,\
Stereos=%d,\
Hydraulics=%d,\
FrontBumper=%d,\
RearBumper=%d,\
VentRight=%d,\
VentLeft=%d,\
Health=%.1f,\
Panels=%d,\
Doors=%d,\
Lights=%d,\
Tires=%d WHERE `IND`=%d",ToBase,
	VehInfo[vehicleid][cModel],
	VehInfo[vehicleid][cType],
	VehInfo[vehicleid][cOwned],
	VehInfo[vehicleid][cOwner],
	VehInfo[vehicleid][cLocX],
	VehInfo[vehicleid][cLocY],
	VehInfo[vehicleid][cLocZ],
	VehInfo[vehicleid][cAng],
	VehInfo[vehicleid][cInt],
	VehInfo[vehicleid][cVirt],
	VehInfo[vehicleid][cLock],
	VehInfo[vehicleid][cPark],
	VehInfo[vehicleid][cAttach],
	VehInfo[vehicleid][cInsur],
	floatround(VehInfo[vehicleid][cFuel]),
	VehInfo[vehicleid][cLoad],
	VehInfo[vehicleid][cLoadType],
	//VehInfo[vehicleid][cDate],
	VehInfo[vehicleid][cColor1],
	VehInfo[vehicleid][cColor2],
	VehInfo[vehicleid][cPaintjob],
	VehInfo[vehicleid][cSpoiler],
	VehInfo[vehicleid][cHood],
	VehInfo[vehicleid][cRoof],
	VehInfo[vehicleid][cSideskirt],
	VehInfo[vehicleid][cLamps],
	VehInfo[vehicleid][cNitro],
	VehInfo[vehicleid][cExhaust],
	VehInfo[vehicleid][cWheels],
	VehInfo[vehicleid][cStereos],
	VehInfo[vehicleid][cHydraulics],
	VehInfo[vehicleid][cFrontBumper],
	VehInfo[vehicleid][cRearBumper],
	VehInfo[vehicleid][cVentRight],
	VehInfo[vehicleid][cVentLeft],
	VehInfo[vehicleid][cHealth],
	VehInfo[vehicleid][DamagePanels],
	VehInfo[vehicleid][DamageDoors],
	VehInfo[vehicleid][DamageLights],
	VehInfo[vehicleid][DamageTires],
	VehInfo[vehicleid][cIND]);
	db_free_result(db_query(db_VW, ToBase));

	TestLog(OPTIM, "SaveTrailerParameters", GetTickCount(), timers);//new timers = GetTickCount();
//ИНФОРМИРОВАНИЕ
	new strtmp[73+2+6];
	format(strtmp, sizeof(strtmp), "[Сохранение прицепа]: trailerid - %d[%d], потрачено - %d (ms)", vehicleid, VehInfo[vehicleid][cModel], (GetTickCount()-timers));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
	return 1;
}
//##############################################################################//
//                                                                              //
//                  ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ ПРИ ВЫХОДЕ ИГРОКА                  //
//                                                                              //
//##############################################################################//






///#############################################################################





stock LoadHousesSQL()//вызывается из функции 4
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new time = GetTickCount();
	new idx;	//235+118 +
	//new Data[1+24 + 20+2+6+6+6+2+6+6+6 + 1+6+6+6 + 1+6+6+6 + 1 + 7+2+1+1+6+10+2+3 + 12];
	new Field[24];
	//db_result = db_query(db_VW,"SELECT * FROM `house`");
	new DBResult:db_result = db_query(db_VW,"SELECT `Owned`,`Owner`,`Hel`,`Arm`,`TV`,`Lock`,`Rent`,`Till`,`Paper`,`Date` FROM `house`");
	do//while(mysql_fetch_row_format(Data, "|"))//Функция служит для обработки полной строки из результата запроса
	{   //пока функция возвращает true
		if(idx >= MAX_HOUSE) break;
		db_get_field_assoc(db_result, "Owned", Field, sizeof(Field) );   HouseInfo[idx][hOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) );   strmid(HouseInfo[idx][hOwner], Field, 0, strlen(Field), sizeof(Field));
//new stringLength = strlen("This is an example strings.", Field, sizeof(Field) );   // stringLength is now set to 26
		//db_get_field_assoc(db_result, "Discription", Field, sizeof(Field) );   strmid(HouseInfo[idx][hDiscription], Field, 0, strlen(Field), 20);
		//db_get_field_assoc(db_result, "Rooms", Field, sizeof(Field) );   HouseInfo[idx][hRooms] = strval(Field);
		//db_get_field_assoc(db_result, "EntranceX", Field, sizeof(Field) );   HouseInfo[idx][hEntranceX] = floatstr(Field);
		//db_get_field_assoc(db_result, "EntranceY", Field, sizeof(Field) );   HouseInfo[idx][hEntranceY] = floatstr(Field);
		//db_get_field_assoc(db_result, "EntranceZ", Field, sizeof(Field) );   HouseInfo[idx][hEntranceZ] = floatstr(Field);
		//db_get_field_assoc(db_result, "Int", Field, sizeof(Field) );   HouseInfo[idx][hInt] = strval(Field);
		//db_get_field_assoc(db_result, "ExitX", Field, sizeof(Field) );   HouseInfo[idx][hExitX] = floatstr(Field);
		//db_get_field_assoc(db_result, "ExitY", Field, sizeof(Field) );   HouseInfo[idx][hExitY] = floatstr(Field);
		//db_get_field_assoc(db_result, "ExitZ", Field, sizeof(Field) );   HouseInfo[idx][hExitZ] = floatstr(Field);
		db_get_field_assoc(db_result, "Hel", Field, sizeof(Field) );   HouseInfo[idx][hHel] = strval(Field);
		//db_get_field_assoc(db_result, "HealthX", Field, sizeof(Field) );   HouseInfo[idx][hClothExX] = floatstr(Field);
		//db_get_field_assoc(db_result, "HealthY", Field, sizeof(Field) );   HouseInfo[idx][hClothExY] = floatstr(Field);
		//db_get_field_assoc(db_result, "HealthZ", Field, sizeof(Field) );   HouseInfo[idx][hClothExZ] = floatstr(Field);
		db_get_field_assoc(db_result, "Arm", Field, sizeof(Field) );   HouseInfo[idx][hCloth] = strval(Field);
		//db_get_field_assoc(db_result, "ArmourX", Field, sizeof(Field) );   HouseInfo[idx][hClothEntX] = floatstr(Field);
		//db_get_field_assoc(db_result, "ArmourY", Field, sizeof(Field) );   HouseInfo[idx][hClothEntY] = floatstr(Field);
		//db_get_field_assoc(db_result, "ArmourZ", Field, sizeof(Field) );   HouseInfo[idx][hClothEntZ] = floatstr(Field);
		db_get_field_assoc(db_result, "TV", Field, sizeof(Field) );   HouseInfo[idx][hTV] = strval(Field);
		//db_get_field_assoc(db_result, "BuyPrice", Field, sizeof(Field) );   HouseInfo[idx][hBuyPrice] = strval(Field);
		//db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   HouseInfo[idx][hLevel] = strval(Field);
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) );   HouseInfo[idx][hLock] = strval(Field);
		//db_get_field_assoc(db_result, "Rentabil", Field, sizeof(Field) );   HouseInfo[idx][hRentabil] = strval(Field);
		db_get_field_assoc(db_result, "Rent", Field, sizeof(Field) );   HouseInfo[idx][hRent] = strval(Field);
		db_get_field_assoc(db_result, "Till", Field, sizeof(Field) );   HouseInfo[idx][hTill] = strval(Field);
		db_get_field_assoc(db_result, "Paper", Field, sizeof(Field) );   HouseInfo[idx][hPaper] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) );   HouseInfo[idx][hDate] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
	printf("3/19. [Загрузка домов]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock SaveHousesSQL()//вызывается из OnCheckProp, /rentcar
{   //для сохранения параметров домов, бизов, машин
	new time = GetTickCount();
	new ToBase[235+118 + 1+24 + 20+2+6+6+6+2+6+6+6 + 1+6+6+6 + 1+6+6+6 + 1 + 7+2+1+1+6+10+2+3 + 12];
	for(new idx=0; idx<MAX_HOUSE; idx++)
	{//Rentabil=%d,
		format(ToBase, sizeof(ToBase), "UPDATE `house` SET Owned=%d,\
Owner='%s',\
Hel=%d,\
Arm=%d,\
TV=%d,\
`Lock`=%d,\
Rent=%d,\
Till=%d,\
Paper=%d,\
`Date`=%d WHERE ID=%d",
			HouseInfo[idx][hOwned],
			HouseInfo[idx][hOwner],
			HouseInfo[idx][hHel],
			HouseInfo[idx][hCloth],
			HouseInfo[idx][hTV],
			HouseInfo[idx][hLock],
			//HouseInfo[idx][hRentabil],
			HouseInfo[idx][hRent],
			HouseInfo[idx][hTill],
			HouseInfo[idx][hPaper],
			HouseInfo[idx][hDate],
			idx+1);
		/*format(ToBase, sizeof(ToBase), "UPDATE `house` SET Owned=%d,\
			Owner='%s',\
			Discription='%s',\
			Rooms=%d,\
			EntranceX=%.1f,\
			EntranceY=%.1f,\
			EntranceZ=%.1f,\
			`Int`=%d,\
			ExitX=%.1f,\
			ExitY=%.1f,\
			ExitZ=%.1f,\
			Hel=%d,\
			HealthX=%.1f,\
			HealthY=%.1f,\
			HealthZ=%.1f,\
			Arm=%d,\
			ArmourX=%.1f,\
			ArmourY=%.1f,\
			ArmourZ=%.1f,\
			TV=%d,\
			BuyPrice=%d,\
			`Level`=%d,\
			`Lock`=%d,\
			Rentabil=%d,\
			Rent=%d,\
			Till=%d,\
			Paper=%d,\
			`Date`=%d WHERE ID=%d",
			HouseInfo[idx][hOwned],
			HouseInfo[idx][hOwner],
			HouseInfo[idx][hDiscription],
			HouseInfo[idx][hRooms],
			HouseInfo[idx][hEntranceX],
			HouseInfo[idx][hEntranceY],
			HouseInfo[idx][hEntranceZ],
			HouseInfo[idx][hInt],
			HouseInfo[idx][hExitX],
			HouseInfo[idx][hExitY],
			HouseInfo[idx][hExitZ],
			HouseInfo[idx][hHel],
			HouseInfo[idx][hClothExX],
			HouseInfo[idx][hClothExY],
			HouseInfo[idx][hClothExZ],
			HouseInfo[idx][hCloth],
			HouseInfo[idx][hClothEntX],
			HouseInfo[idx][hClothEntY],
			HouseInfo[idx][hClothEntZ],
			HouseInfo[idx][hTV],
			HouseInfo[idx][hBuyPrice],
			HouseInfo[idx][hLevel],
			HouseInfo[idx][hLock],
			HouseInfo[idx][hRentabil],
			HouseInfo[idx][hRent],
			HouseInfo[idx][hTill],
			HouseInfo[idx][hPaper],
			HouseInfo[idx][hDate],
			idx+1);*/
		db_free_result(db_query(db_VW, ToBase));
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[67+2+6];
	format(strtmp, sizeof(strtmp), "2/19. [Сохранение домов]: Было сохранено - %d, потрачено - %d (ms)", MAX_HOUSE, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}//End SaveHousesSQL()

stock SaveHouseSQL(house)
{   //Rentabil=%d,
	new time = GetTickCount();
	new ToBase[235+118 + 1+24 + 20+2+6+6+6+2+6+6+6 + 1+6+6+6 + 1+6+6+6 + 1 + 7+2+1+1+6+10+2+3 + 12];
	format(ToBase, sizeof(ToBase), "UPDATE `house` SET Owned=%d,\
		Owner='%s',\
		Discription='%s',\
		Rooms=%d,\
		EntranceX=%.1f,\
		EntranceY=%.1f,\
		EntranceZ=%.1f,\
		`Int`=%d,\
		ExitX=%.1f,\
		ExitY=%.1f,\
		ExitZ=%.1f,\
		Hel=%d,\
		HealthX=%.1f,\
		HealthY=%.1f,\
		HealthZ=%.1f,\
		Arm=%d,\
		ArmourX=%.1f,\
		ArmourY=%.1f,\
		ArmourZ=%.1f,\
		TV=%d,\
		BuyPrice=%d,\
		`Level`=%d,\
		`Lock`=%d,\
		Rent=%d,\
		Till=%d,\
		Paper=%d,\
		`Date`=%d WHERE ID=%d",
		HouseInfo[house][hOwned],
		HouseInfo[house][hOwner],
		HouseInfo[house][hDiscription],
		HouseInfo[house][hRooms],
		HouseInfo[house][hEntranceX],
		HouseInfo[house][hEntranceY],
		HouseInfo[house][hEntranceZ],
		HouseInfo[house][hInt],
		HouseInfo[house][hExitX],
		HouseInfo[house][hExitY],
		HouseInfo[house][hExitZ],
		HouseInfo[house][hHel],
		HouseInfo[house][hClothExX],
		HouseInfo[house][hClothExY],
		HouseInfo[house][hClothExZ],
		HouseInfo[house][hCloth],
		HouseInfo[house][hClothEntX],
		HouseInfo[house][hClothEntY],
		HouseInfo[house][hClothEntZ],
		HouseInfo[house][hTV],
		HouseInfo[house][hBuyPrice],
		HouseInfo[house][hLevel],
		HouseInfo[house][hLock],
		//HouseInfo[house][hRentabil],
		HouseInfo[house][hRent],
		HouseInfo[house][hTill],
		HouseInfo[house][hPaper],
		HouseInfo[house][hDate],
		house+1);
	db_free_result(db_query(db_VW, ToBase));

	new strtmp[67+2+6];
	format(strtmp, sizeof(strtmp), "Сохранение дома №%d успешно завершено. Потрачено - %d (ms)", house, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}//End SaveHouse()



stock LoadBizSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new time = GetTickCount();
	new idx;
	//new Data[234+12];//11+11+24+3+20+6*3+2+6*3+7+2+1+6+10*6+3+3+10+3+6+3+10+10+3 = 234
	new Field[24];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `bizz`");
	
	do//while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= MAX_BIZ) break;
		db_get_field_assoc(db_result, "Owned", Field, sizeof(Field) );   BizInfo[idx][bOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) );   strmid(BizInfo[idx][bOwner], Field, 0, strlen(Field), 24);
		db_get_field_assoc(db_result, "Extortion", Field, sizeof(Field) );   BizInfo[idx][bExtortion] = strval(Field);

//чтобы не загружались из базы, т.к. исправлено только в моде
//db_get_field_assoc(db_result, "Discription", Field, sizeof(Field) );   strmid(BizInfo[idx][bDiscription], Field, 0, strlen(Field), 20);
		/*if(idx == 66)
		{
			db_get_field_assoc(db_result, "EntranceX", Field, sizeof(Field) );   BizInfo[idx][bEntranceX] = floatstr(Field);
			db_get_field_assoc(db_result, "EntranceY", Field, sizeof(Field) );   BizInfo[idx][bEntranceY] = floatstr(Field);
			db_get_field_assoc(db_result, "EntranceZ", Field, sizeof(Field) );   BizInfo[idx][bEntranceZ] = floatstr(Field);
			//BizInfo[idx][bEntranceA] = floatstr(Field);//угол взгляда после выхода из интерьера

			//db_get_field_assoc(db_result, "Int", Field, sizeof(Field) );   BizInfo[idx][bInt] = strval(Field);
			//db_get_field_assoc(db_result, "ExitX", Field, sizeof(Field) );   BizInfo[idx][bExitX] = strval(Field);
			//db_get_field_assoc(db_result, "ExitY", Field, sizeof(Field) );   BizInfo[idx][bExitY] = strval(Field);
			//db_get_field_assoc(db_result, "ExitZ", Field, sizeof(Field) );   BizInfo[idx][bExitZ] = strval(Field);
			//BizInfo[idx][bExitA] = strval(Field);//угол взгляда после входа в интерьер
		}*/
//db_get_field_assoc(db_result, "BuyPrice", Field, sizeof(Field) );   BizInfo[idx][bBuyPrice] = strval(Field);

		db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   BizInfo[idx][bLevel] = strval(Field);
//закоментировать, чтобы сбросить уровень до 1
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) );   BizInfo[idx][bLock] = strval(Field);
		db_get_field_assoc(db_result, "EntranceCost", Field, sizeof(Field) );   BizInfo[idx][bEntranceCost] = strval(Field);

		db_get_field_assoc(db_result, "Metal", Field, sizeof(Field) );   BizInfo[idx][bMetal] = strval(Field);
		db_get_field_assoc(db_result, "Textiles", Field, sizeof(Field) );   BizInfo[idx][bTextiles] = strval(Field);
		db_get_field_assoc(db_result, "Provisions", Field, sizeof(Field) );   BizInfo[idx][bProvisions] = strval(Field);
		db_get_field_assoc(db_result, "Tree", Field, sizeof(Field) );   BizInfo[idx][bTree] = strval(Field);
		db_get_field_assoc(db_result, "Fuel", Field, sizeof(Field) );   BizInfo[idx][bFuel] = strval(Field);

		db_get_field_assoc(db_result, "Products", Field, sizeof(Field) );   BizInfo[idx][bProducts] = strval(Field);
		db_get_field_assoc(db_result, "BuyProd", Field, sizeof(Field) );   BizInfo[idx][bBuyProd] = strval(Field);
		db_get_field_assoc(db_result, "SellProd", Field, sizeof(Field) );   BizInfo[idx][bSellProd] = strval(Field);
		db_get_field_assoc(db_result, "Till", Field, sizeof(Field) );   BizInfo[idx][bTill] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) );   BizInfo[idx][bDate] = strval(Field);
		db_get_field_assoc(db_result, "Inkas", Field, sizeof(Field) );   BizInfo[idx][bInkas] = strval(Field);

		//db_get_field_assoc(db_result, "Worker", Field, sizeof(Field) );   BizInfo[idx][bWorker] = strval(Field);
		db_get_field_assoc(db_result, "Import", Field, sizeof(Field) );   BizInfo[idx][bImport] = strval(Field);
		db_get_field_assoc(db_result, "Export", Field, sizeof(Field) );   BizInfo[idx][bExport] = strval(Field);
		db_get_field_assoc(db_result, "Salary", Field, sizeof(Field) );   BizInfo[idx][bSalary] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
	//compcost = BizInfo[81][bSalary];
	printf("4/19. [Загрузка бизнесов]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock SaveBizSQL()//вызывается каждый час и при рестарте мода
{   //для сохранения параметров бизов, машин
	new time = GetTickCount();
	new ToBase[704];
	//new ToBase[698];//461 + 11+11+24+3+20+3 + 6*3+2 + 6*3+7 + 2+1 + 6+10*6 +3+3+10+3+6+3+10+10+3 = 698

	for(new idx=0; idx<MAX_BIZ; idx++)
	{
		BizInfo[idx][bLevel] = GetBizLevel(idx);
		/*format(ToBase, sizeof(ToBase), "UPDATE `bizz` SET Owned=%d,\
Owner='%s',\
Extortion=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Metal=%d,\
Textiles=%d,\
Provisions=%d,\
Tree=%d,\
Fuel=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d",
			BizInfo[idx][bOwned],
			BizInfo[idx][bOwner],
			BizInfo[idx][bExtortion],

			BizInfo[idx][bLevel],
			BizInfo[idx][bLock],
			BizInfo[idx][bEntranceCost],

			BizInfo[idx][bMetal],
			BizInfo[idx][bTextiles],
			BizInfo[idx][bProvisions],
			BizInfo[idx][bTree],
			BizInfo[idx][bFuel],

			BizInfo[idx][bProducts],
			BizInfo[idx][bBuyProd],
			BizInfo[idx][bSellProd],
			BizInfo[idx][bTill],
			BizInfo[idx][bDate],
			BizInfo[idx][bInkas],

			BizInfo[idx][bWorker],
			BizInfo[idx][bImport],
			BizInfo[idx][bExport],
			BizInfo[idx][bSalary],
			idx+1);
*/
		format(ToBase, sizeof(ToBase), "UPDATE `bizz` SET Owned=%d,\
Owner='%s',\
Extortion='%s',\
Discription='%s',\
EntranceX=%.1f,\
EntranceY=%.1f,\
EntranceZ=%.1f,\
`Int`=%d,\
ExitX=%.1f,\
ExitY=%.1f,\
ExitZ=%.1f,\
BuyPrice=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Metal=%d,\
Textiles=%d,\
Provisions=%d,\
Tree=%d,\
Fuel=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d",
			BizInfo[idx][bOwned],
			BizInfo[idx][bOwner],
			BizInfo[idx][bExtortion],

			BizInfo[idx][bDiscription],
			BizInfo[idx][bEntranceX],
			BizInfo[idx][bEntranceY],
			BizInfo[idx][bEntranceZ],
			BizInfo[idx][bInt],
			BizInfo[idx][bExitX],
			BizInfo[idx][bExitY],
			BizInfo[idx][bExitZ],

			BizInfo[idx][bBuyPrice],
			BizInfo[idx][bLevel],

			BizInfo[idx][bLock],
			BizInfo[idx][bEntranceCost],
			
			BizInfo[idx][bMetal],
			BizInfo[idx][bTextiles],
			BizInfo[idx][bProvisions],
			BizInfo[idx][bTree],
			BizInfo[idx][bFuel],

			BizInfo[idx][bProducts],
			BizInfo[idx][bBuyProd],
			BizInfo[idx][bSellProd],
			BizInfo[idx][bTill],
			BizInfo[idx][bDate],
			BizInfo[idx][bInkas],

			BizInfo[idx][bWorker],
			BizInfo[idx][bImport],
			BizInfo[idx][bExport],
			BizInfo[idx][bSalary],
			idx+1);
//printf("Biz:%d, Discription: %s", idx,BizInfo[idx][bDiscription]);
		db_free_result(db_query(db_VW, ToBase));
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "3/19. [Сохранение бизнесов]: Было сохранено - %d, потрачено - %d (ms)", MAX_BIZ, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}
stock SaveBiz(bouse)//вызывается из PerformingTheContract по команде /edit /asellsbiz /raspredturf /buy /bizbank /sellbiz
{
	new time = GetTickCount();
	new ToBase[704];
	BizInfo[bouse][bLevel] = GetBizLevel(bouse);

	format(ToBase, sizeof(ToBase), "UPDATE `bizz` SET Owned=%d,\
Owner='%s',\
Extortion=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Metal=%d,\
Textiles=%d,\
Provisions=%d,\
Tree=%d,\
Fuel=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d",
		BizInfo[bouse][bOwned],
		BizInfo[bouse][bOwner],
		BizInfo[bouse][bExtortion],

		BizInfo[bouse][bLevel],
		BizInfo[bouse][bLock],
		BizInfo[bouse][bEntranceCost],

		BizInfo[bouse][bMetal],
		BizInfo[bouse][bTextiles],
		BizInfo[bouse][bProvisions],
		BizInfo[bouse][bTree],
		BizInfo[bouse][bFuel],

		BizInfo[bouse][bProducts],
		BizInfo[bouse][bBuyProd],
		BizInfo[bouse][bSellProd],
		BizInfo[bouse][bTill],
		BizInfo[bouse][bDate],
		BizInfo[bouse][bInkas],

		BizInfo[bouse][bWorker],
		BizInfo[bouse][bImport],
		BizInfo[bouse][bExport],
		BizInfo[bouse][bSalary],
		bouse+1);

	/*format(ToBase, sizeof(ToBase), "UPDATE `bizz` SET Owned=%d,\
Owner='%s',\
Extortion=%d,\
Discription='%s',\
EntranceX=%.1f,\
EntranceY=%.1f,\
EntranceZ=%.1f,\
`Int`=%d,\
ExitX=%.1f,\
ExitY=%.1f,\
ExitZ=%.1f,\
BuyPrice=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Metal=%d,\
Textiles=%d,\
Provisions=%d,\
Tree=%d,\
Fuel=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d",
		BizInfo[bouse][bOwned],
		BizInfo[bouse][bOwner],
		BizInfo[bouse][bExtortion],

		BizInfo[bouse][bDiscription],
		BizInfo[bouse][bEntranceX],
		BizInfo[bouse][bEntranceY],
		BizInfo[bouse][bEntranceZ],
		BizInfo[bouse][bInt],
		BizInfo[bouse][bExitX],
		BizInfo[bouse][bExitY],
		BizInfo[bouse][bExitZ],

		BizInfo[bouse][bBuyPrice],
		BizInfo[bouse][bLevel],

		BizInfo[bouse][bLock],
		BizInfo[bouse][bEntranceCost],

		BizInfo[bouse][bMetal],
		BizInfo[bouse][bTextiles],
		BizInfo[bouse][bProvisions],
		BizInfo[bouse][bTree],
		BizInfo[bouse][bFuel],

		BizInfo[bouse][bProducts],
		BizInfo[bouse][bBuyProd],
		BizInfo[bouse][bSellProd],
		BizInfo[bouse][bTill],
		BizInfo[bouse][bDate],
		BizInfo[bouse][bInkas],

		BizInfo[bouse][bWorker],
		BizInfo[bouse][bImport],
		BizInfo[bouse][bExport],
		BizInfo[bouse][bSalary],
		bouse+1);*/
	db_free_result(db_query(db_VW, ToBase));

	//ИНФОРМИРОВАНИЕ
	new strtmp[67+2+6];
	format(strtmp, sizeof(strtmp), "Сохранение бизнеса №%d успешно завершено. Потрачено - %d (ms)", bouse, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}

stock LoadSBizSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new time = GetTickCount();
	new idx;//198+88 +
	//new Data[1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+ 10*5 +3+3+6+10+3+1 + 3+10+10+2 + 12];
	new Field[24];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `sbizz`");
	do//while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= MAX_SBIZ) break;//MAX_SBIZ //GAS_STATION
		db_get_field_assoc(db_result, "Owned", Field, sizeof(Field) );   SBizInfo[idx][sbOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbOwner], Field, 0, strlen(Field), 24);
		db_get_field_assoc(db_result, "Extortion", Field, sizeof(Field) );   SBizInfo[idx][sbExtortion] = strval(Field);

//db_get_field_assoc(db_result, "Discription", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbDiscription], Field, 0, strlen(Field), 20);
//db_get_field_assoc(db_result, "EntranceX", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceX] = floatstr(Field);
//db_get_field_assoc(db_result, "EntranceY", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceY] = floatstr(Field);
//db_get_field_assoc(db_result, "EntranceZ", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceZ] = floatstr(Field);
//db_get_field_assoc(db_result, "BuyPrice", Field, sizeof(Field) );   SBizInfo[idx][sbBuyPrice] = strval(Field);

		db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   SBizInfo[idx][sbLevel] = strval(Field);
//закоментировать, чтобы сбросить уровень до 1
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) );   SBizInfo[idx][sbLock] = strval(Field);
		db_get_field_assoc(db_result, "EntranceCost", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceCost] = strval(Field);

		db_get_field_assoc(db_result, "Products", Field, sizeof(Field) );   SBizInfo[idx][sbProducts] = strval(Field);
		if(idx >= PARKING && idx < PARKING+sizeof(Parking))
		{
			SBizInfo[idx][sbProducts] = 0;
		}

		db_get_field_assoc(db_result, "BuyProd", Field, sizeof(Field) );   SBizInfo[idx][sbBuyProd] = strval(Field);
		db_get_field_assoc(db_result, "SellProd", Field, sizeof(Field) );   SBizInfo[idx][sbSellProd] = strval(Field);
		db_get_field_assoc(db_result, "Till", Field, sizeof(Field) );   SBizInfo[idx][sbTill] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) );   SBizInfo[idx][sbDate] = strval(Field);
		db_get_field_assoc(db_result, "Inkas", Field, sizeof(Field) );   SBizInfo[idx][sbInkas] = strval(Field);

		//db_get_field_assoc(db_result, "Worker", Field, sizeof(Field) );   SBizInfo[idx][sbWorker] = strval(Field);
		db_get_field_assoc(db_result, "Import", Field, sizeof(Field) );   SBizInfo[idx][sbImport] = strval(Field);
		db_get_field_assoc(db_result, "Export", Field, sizeof(Field) );   SBizInfo[idx][sbExport] = strval(Field);
		db_get_field_assoc(db_result, "Salary", Field, sizeof(Field) );   SBizInfo[idx][sbSalary] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
	printf("5/19. [Загрузка компаний]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock SaveSBizSQL()//вызывается при рестарте мода и каждый час
{   //для сохранения бизов, машин
	new time = GetTickCount();
	new ToBase[259+18 + 1+1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+ 10*5 +3+3+6+10+3 + 3+10+10+2 + 12];
	for(new idx=0; idx<MAX_SBIZ; idx++)//MAX_SBIZ //GAS_STATION
	{
		SBizInfo[idx][sbLevel] = GetBizLevel(idx+100);
		format(ToBase, sizeof(ToBase), "UPDATE `sbizz` SET Owned=%d,\
Owner='%s',\
Extortion=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
TypeProducts=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d",
			SBizInfo[idx][sbOwned],
			SBizInfo[idx][sbOwner],
			SBizInfo[idx][sbExtortion],

			SBizInfo[idx][sbLevel],
			SBizInfo[idx][sbLock],
			SBizInfo[idx][sbEntranceCost],
			SBizInfo[idx][sbBranch],

			SBizInfo[idx][sbProducts],
			SBizInfo[idx][sbBuyProd],
			SBizInfo[idx][sbSellProd],
			SBizInfo[idx][sbTill],
	        SBizInfo[idx][sbDate],
	        SBizInfo[idx][sbInkas],

			SBizInfo[idx][sbWorker],
			SBizInfo[idx][sbImport],
			SBizInfo[idx][sbExport],
			SBizInfo[idx][sbSalary],
			idx+1);

		/*format(ToBase, sizeof(ToBase), "UPDATE `sbizz` SET Owned=%d,\
Owner='%s',\
Extortion=%d,\
Discription='%s',\
EntranceX=%.1f,\
EntranceY=%.1f,\
EntranceZ=%.1f,\
BuyPrice=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d",
			SBizInfo[idx][sbOwned],
			SBizInfo[idx][sbOwner],
			SBizInfo[idx][sbExtortion],

			SBizInfo[idx][sbDiscription],
			SBizInfo[idx][sbEntranceX],
			SBizInfo[idx][sbEntranceY],
			SBizInfo[idx][sbEntranceZ],
			SBizInfo[idx][sbBuyPrice],
			SBizInfo[idx][sbLevel],

			SBizInfo[idx][sbLock],
			SBizInfo[idx][sbEntranceCost],

			SBizInfo[idx][sbProducts],
			SBizInfo[idx][sbBuyProd],
			SBizInfo[idx][sbSellProd],
			SBizInfo[idx][sbTill],
	        SBizInfo[idx][sbDate],
	        SBizInfo[idx][sbInkas],

			SBizInfo[idx][sbWorker],
			SBizInfo[idx][sbImport],
			SBizInfo[idx][sbExport],
			SBizInfo[idx][sbSalary],
			idx+1);*/
		db_free_result(db_query(db_VW, ToBase));
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[74+2+6];
	format(strtmp, sizeof(strtmp), "4/19. [Сохранение биз-компаний]: Было сохранено - %d, потрачено - %d (ms)", MAX_SBIZ, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}
stock SaveSBiz(sbouse)//вызывается из PerformingTheContract по команде /edit /asellsbiz /raspredturf /buy /bizbank /sellbiz
{   //для сохранения бизов, машин
	new time = GetTickCount();
	new ToBase[618];//299+57+48 + 1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+ 10*5 +3+3+6+10+3+1 + 3+10+10+2 + 12 = 618

	SBizInfo[sbouse][sbLevel] = GetBizLevel(sbouse+100);
	format(ToBase, sizeof(ToBase), "UPDATE `sbizz` SET Owned=%d,\
Owner='%s',\
Extortion='%s',\
Discription='%s',\
EntranceX=%.1f,\
EntranceY=%.1f,\
EntranceZ=%.1f,\
BuyPrice=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d WHERE `ID`=%d",
		SBizInfo[sbouse][sbOwned],
		SBizInfo[sbouse][sbOwner],
		SBizInfo[sbouse][sbExtortion],
		SBizInfo[sbouse][sbDiscription],
		SBizInfo[sbouse][sbEntranceX],
		SBizInfo[sbouse][sbEntranceY],
		SBizInfo[sbouse][sbEntranceZ],
		SBizInfo[sbouse][sbBuyPrice],
		SBizInfo[sbouse][sbLevel],

		SBizInfo[sbouse][sbLock],
		SBizInfo[sbouse][sbEntranceCost],
		SBizInfo[sbouse][sbProducts],
		SBizInfo[sbouse][sbBuyProd],
		SBizInfo[sbouse][sbSellProd],
		SBizInfo[sbouse][sbTill],
        SBizInfo[sbouse][sbDate],
        SBizInfo[sbouse][sbInkas],
		sbouse+1);
	db_free_result(db_query(db_VW, ToBase));
	//ИНФОРМИРОВАНИЕ
	new strtmp[67+2+6];
	format(strtmp, sizeof(strtmp), "Сохранение биз-компании №%d успешно завершено. Потрачено - %d (ms)", sbouse, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}


/*
stock LoadGasStationSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new idx = GAS_STATION;//198+88 +
	new Data[1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3+1 + 12];
	new Field[24];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `gas`");
	do//while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= PARKING) break;
		db_get_field_assoc(db_result, "Owned", Field, sizeof(Field) );   SBizInfo[idx][sbOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbOwner], Field, 0, strlen(Field), 24);
		db_get_field_assoc(db_result, "Extortion", Field, sizeof(Field) );  SBizInfo[idx][sbExtortion] = strval(Field);
		//db_get_field_assoc(db_result, "Discription", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbDiscription], Field, 0, strlen(Field), 20);
		//db_get_field_assoc(db_result, "EntranceX", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceX] = floatstr(Field);
		//db_get_field_assoc(db_result, "EntranceY", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceY] = floatstr(Field);
		//db_get_field_assoc(db_result, "EntranceZ", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceZ] = floatstr(Field);
		//db_get_field_assoc(db_result, "BuyPrice", Field, sizeof(Field) );   SBizInfo[idx][sbBuyPrice] = strval(Field);
		//db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   SBizInfo[idx][sbLevel] = strval(Field);
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) );   SBizInfo[idx][sbLock] = strval(Field);
		db_get_field_assoc(db_result, "EntranceCost", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceCost] = strval(Field);
		db_get_field_assoc(db_result, "Products", Field, sizeof(Field) );   SBizInfo[idx][sbProducts] = strval(Field);
		db_get_field_assoc(db_result, "BuyProd", Field, sizeof(Field) );   SBizInfo[idx][sbBuyProd] = strval(Field);
		db_get_field_assoc(db_result, "SellProd", Field, sizeof(Field) );   SBizInfo[idx][sbSellProd] = strval(Field);
		db_get_field_assoc(db_result, "Till", Field, sizeof(Field) );   SBizInfo[idx][sbTill] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) );   SBizInfo[idx][sbDate] = strval(Field);
		db_get_field_assoc(db_result, "Inkas", Field, sizeof(Field) );   SBizInfo[idx][sbInkas] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
}
stock SaveGasStationSQL()//вызывается при рестарте мода и каждый час
{   //для сохранения бизов, машин

	new ToBase[299 + 1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3 + 12];
	for(new idx = GAS_STATION; idx < PARKING; idx++)
	{
		format(ToBase, sizeof(ToBase), "UPDATE `gas` SET Owned=%d,\
Owner='%s',\
Extortion='%s',\
Discription='%s',\
EntranceX=%.1f,\
EntranceY=%.1f,\
EntranceZ=%.1f,\
BuyPrice=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d WHERE `ID`=%d",
			SBizInfo[idx][sbOwned],
			SBizInfo[idx][sbOwner],
			SBizInfo[idx][sbExtortion],

			SBizInfo[idx][sbDiscription],
			SBizInfo[idx][sbEntranceX],
			SBizInfo[idx][sbEntranceY],
			SBizInfo[idx][sbEntranceZ],
			SBizInfo[idx][sbBuyPrice],
			SBizInfo[idx][sbLevel],

			SBizInfo[idx][sbLock],
			SBizInfo[idx][sbEntranceCost],
			SBizInfo[idx][sbProducts],
			SBizInfo[idx][sbBuyProd],
			SBizInfo[idx][sbSellProd],
			SBizInfo[idx][sbTill],
	        SBizInfo[idx][sbDate],
	        SBizInfo[idx][sbInkas],
			idx+1);
		db_free_result(db_query(db_VW, ToBase));
	}
	//ИНФОРМИРОВАНИЕ
	SendAllAdminMessage( COLOR_RESTARTING, "Сохранение АЗС успешно завершено", 1);
}


stock LoadParkingSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрузка property.cfg
	new idx = PARKING;//198+88 +
	new Data[1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3+1 + 12];
	new Field[24];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `parking`");
	do//while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= PARKING+sizeof(Parking)) break;
		db_get_field_assoc(db_result, "Owned", Field, sizeof(Field) );   SBizInfo[idx][sbOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbOwner], Field, 0, strlen(Field), 24);
		db_get_field_assoc(db_result, "Extortion", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbExtortion], Field, 0, strlen(Field), 20);
		//db_get_field_assoc(db_result, "Discription", Field, sizeof(Field) );   strmid(SBizInfo[idx][sbDiscription], Field, 0, strlen(Field), 20);
		//db_get_field_assoc(db_result, "EntranceX", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceX] = floatstr(Field);
		//db_get_field_assoc(db_result, "EntranceY", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceY] = floatstr(Field);
		//db_get_field_assoc(db_result, "EntranceZ", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceZ] = floatstr(Field);
		//db_get_field_assoc(db_result, "BuyPrice", Field, sizeof(Field) );   SBizInfo[idx][sbBuyPrice] = strval(Field);
		//db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   SBizInfo[idx][sbLevel] = strval(Field);
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) );   SBizInfo[idx][sbLock] = strval(Field);
		db_get_field_assoc(db_result, "EntranceCost", Field, sizeof(Field) );   SBizInfo[idx][sbEntranceCost] = strval(Field);
		db_get_field_assoc(db_result, "Products", Field, sizeof(Field) );   SBizInfo[idx][sbProducts] = strval(Field);
		db_get_field_assoc(db_result, "BuyProd", Field, sizeof(Field) );   SBizInfo[idx][sbBuyProd] = strval(Field);
		db_get_field_assoc(db_result, "SellProd", Field, sizeof(Field) );   SBizInfo[idx][sbSellProd] = strval(Field);
		db_get_field_assoc(db_result, "Till", Field, sizeof(Field) );   SBizInfo[idx][sbTill] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) );   SBizInfo[idx][sbDate] = strval(Field);
		db_get_field_assoc(db_result, "Inkas", Field, sizeof(Field) );   SBizInfo[idx][sbInkas] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
}
stock SaveParkingSQL()//вызывается при рестарте мода и каждый час
{   //для сохранения бизов, машин

	new ToBase[299 + 1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3 + 12];
	for(new idx = PARKING; idx < PARKING+sizeof(Parking); idx++)
	{
		format(ToBase, sizeof(ToBase), "UPDATE `parking` SET Owned=%d,\
Owner='%s',\
Extortion='%s',\
Discription='%s',\
EntranceX=%.1f,\
EntranceY=%.1f,\
EntranceZ=%.1f,\
BuyPrice=%d,\
`Level`=%d,\
`Lock`=%d,\
EntranceCost=%d,\
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d WHERE `ID`=%d",
			SBizInfo[idx][sbOwned],
			SBizInfo[idx][sbOwner],
			SBizInfo[idx][sbExtortion],

			SBizInfo[idx][sbDiscription],
			SBizInfo[idx][sbEntranceX],
			SBizInfo[idx][sbEntranceY],
			SBizInfo[idx][sbEntranceZ],
			SBizInfo[idx][sbBuyPrice],
			SBizInfo[idx][sbLevel],

			SBizInfo[idx][sbLock],
			SBizInfo[idx][sbEntranceCost],
			SBizInfo[idx][sbProducts],
			SBizInfo[idx][sbBuyProd],
			SBizInfo[idx][sbSellProd],
			SBizInfo[idx][sbTill],
	        SBizInfo[idx][sbDate],
	        SBizInfo[idx][sbInkas],
			idx+1);
		db_free_result(db_query(db_VW, ToBase));
	}
	//ИНФОРМИРОВАНИЕ
	SendAllAdminMessage( COLOR_RESTARTING, "Сохранение Паркинга успешно завершено", 1);
}*/


stock LoadVoteSQL()//для загрузки настроек
{
	new time = GetTickCount();
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `vote`");
	if(db_num_rows(db_result))
	{
		new Field[70];//712
		db_get_field_assoc(db_result, "maker", Field, sizeof(Field) );   strmid(Question[qMaker], Field, 0, strlen(Field), 24);
		db_get_field_assoc(db_result, "style", Field, sizeof(Field) );   Question[qStyle] = strval(Field);
		//db_get_field_assoc(db_result, "time");
		db_get_field_assoc(db_result, "title", Field, sizeof(Field) );   strmid(Question[qCaption], Field, 0, strlen(Field), 65);

		strmid(Question[qInfo0], "Не участвовать", 0, 18, 18);
		strmid(Question[qInfo], "Не участвовать\n", 0, 18, 18);

		//new strings[MAX_STRING];
		//strdel(strings, 0, MAX_STRING);
		db_get_field_assoc(db_result, "Info1", Field, sizeof(Field) );   strmid(Question[qInfo1], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo1]);
  		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo1]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));

		db_get_field_assoc(db_result, "Info2", Field, sizeof(Field) );   strmid(Question[qInfo2], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo2]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo2]);

		db_get_field_assoc(db_result, "Info3", Field, sizeof(Field) );   strmid(Question[qInfo3], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo3]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo3]);

		db_get_field_assoc(db_result, "Info4", Field, sizeof(Field) );   strmid(Question[qInfo4], Field, 0, strlen(Field), 70);
 		format(strings, sizeof(strings), "%s\n", Question[qInfo4]);
		strins(Question[qInfo], strings, strlen(Question[qInfo]));

		db_get_field_assoc(db_result, "Info5", Field, sizeof(Field) );   strmid(Question[qInfo5], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo5]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo5]);

		db_get_field_assoc(db_result, "Info6", Field, sizeof(Field) );   strmid(Question[qInfo6], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo6]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo6]);

		db_get_field_assoc(db_result, "Info7", Field, sizeof(Field) );   strmid(Question[qInfo7], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo7]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo7]);

		db_get_field_assoc(db_result, "Info8", Field, sizeof(Field) );   strmid(Question[qInfo8], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo8]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo8]);

		db_get_field_assoc(db_result, "Info9", Field, sizeof(Field) );   strmid(Question[qInfo9], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo9]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo9]);

		db_get_field_assoc(db_result, "Info10", Field, sizeof(Field) );   strmid(Question[qInfo10], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo10]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo10]);

		db_get_field_assoc(db_result, "Button1", Field, sizeof(Field) );   strmid(Question[qButton1], Field, 0, strlen(Field), 10);
		db_get_field_assoc(db_result, "Button2", Field, sizeof(Field) );   strmid(Question[qButton2], Field, 0, strlen(Field), 10);
		db_get_field_assoc(db_result, "Open", Field, sizeof(Field) );   Question[qClose] = strval(Field);
		db_get_field_assoc(db_result, "approve", Field, sizeof(Field) );   Question[qApprove] = strval(Field);
		db_get_field_assoc(db_result, "start", Field, sizeof(Field) );   Question[qStart] = strval(Field);
		db_get_field_assoc(db_result, "end", Field, sizeof(Field) );   Question[qEnd] = strval(Field);

		Question[qDays] = Question[qEnd] - Question[qStart];
		printf("9/19. [Загрузка голосов]: Было загружено - %d, потрачено - %d (ms)", db_num_rows(db_result), (GetTickCount()-time));
	}
	db_free_result(db_result);
}

stock SaveVoteSQL()//вызывается из OnPlayerDisconnect GameModeInitExitFunc
{   //ф-ция сохранения параметров игрока
	new time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[303 + 24+1+25+65+10*70+2*10+1+1+3+3 + 12];
//body='%s',
	format(ToBase, sizeof(ToBase), "UPDATE `vote` SET `maker`='%s',\
`style`=%d,\
`time`='%s',\
`title`='%s',\
Info1='%s',\
Info2='%s',\
Info3='%s',\
Info4='%s',\
Info5='%s',\
Info6='%s',\
Info7='%s',\
Info8='%s',\
Info9='%s',\
Info10='%s',\
Button1='%s',\
Button2='%s',\
`Open`=%d,\
`approve`=%d,\
`start`=%d,\
`end`=%d",
	Question[qMaker],
	Question[qStyle],
	time,
	Question[qCaption],
	//Question[qInfo],
	Question[qInfo1],
	Question[qInfo2],
	Question[qInfo3],
	Question[qInfo4],
	Question[qInfo5],
	Question[qInfo6],
	Question[qInfo7],
	Question[qInfo8],
	Question[qInfo9],
	Question[qInfo10],
	Question[qButton1],
	Question[qButton2],
	Question[qClose],
	Question[qApprove],
	getdate(),
	getdate()+Question[qDays]);
	db_free_result(db_query(db_VW, ToBase));
	printf("Сохранение голосов успешно завершено");
}



//для выборов начало
stock Election_OneDayTimer()
{   //запускается при смене суток
//Запустится сразу после 12:00 ночью после окончания выборов
	new DBResult:db_result;
	if(getdate() == Question[qEnd]+1)
	{//если день сменился на следующий после окончания выборов
		new timers = GetTickCount();

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info1` FROM `vote`)");
		new votes1 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info2` FROM `vote`)");
		new votes2 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info3` FROM `vote`)");
		new votes3 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info4` FROM `vote`)");
		new votes4 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info5` FROM `vote`)");
		new votes5 = db_num_rows(db_result); db_free_result(db_result);

	/*	db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info6` FROM `vote`)");
		new votes6 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info7` FROM `vote`)");
		new votes7 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info8` FROM `vote`)");
		new votes8 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info9` FROM `vote`)");
		new votes9 = db_num_rows(db_result); db_free_result(db_result);

		db_result = db_query(db_VW,"SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info10` FROM `vote`)
		new votes10 = db_num_rows(db_result); db_free_result(db_result);*/

		new playername[MAX_PLAYER_NAME], giveplayername[MAX_PLAYER_NAME];

		if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4 && votes1 > votes5)
		{
			strmid(playername, Question[qInfo1], 0, strlen(Question[qInfo1]), MAX_PLAYER_NAME);
		}
		else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4 && votes2 > votes5)
		{
			strmid(playername, Question[qInfo2], 0, strlen(Question[qInfo2]), MAX_PLAYER_NAME);
		}
		else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4 && votes3 > votes5)
		{
			strmid(playername, Question[qInfo3], 0, strlen(Question[qInfo3]), MAX_PLAYER_NAME);
		}
		else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3 && votes4 > votes5)
		{
			strmid(playername, Question[qInfo4], 0, strlen(Question[qInfo4]), MAX_PLAYER_NAME);
		}
		else if(votes5 > votes1 && votes5 > votes2 && votes5 > votes3 && votes5 > votes4)
		{
			strmid(playername, Question[qInfo5], 0, strlen(Question[qInfo5]), MAX_PLAYER_NAME);
		}

		/*else if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4 && votes1 > votes5)
		{
			strmid(playername, Question[qInfo1], 0, strlen(Question[qInfo1]), MAX_PLAYER_NAME);
		}
		else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4 && votes2 > votes5)
		{
			strmid(playername, Question[qInfo2], 0, strlen(Question[qInfo2]), MAX_PLAYER_NAME);
		}
		else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4 && votes3 > votes5)
		{
			strmid(playername, Question[qInfo3], 0, strlen(Question[qInfo3]), MAX_PLAYER_NAME);
		}
		else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3 && votes4 > votes5)
		{
			strmid(playername, Question[qInfo4], 0, strlen(Question[qInfo4]), MAX_PLAYER_NAME);
		}
		else if(votes5 > votes1 && votes5 > votes2 && votes5 > votes3 && votes5 > votes4)
		{
			strmid(playername, Question[qInfo5], 0, strlen(Question[qInfo5]), MAX_PLAYER_NAME);
		}*/
		else
		{
			Question[qApprove] = 0;
			strmid(playername, FamilyInfo[DoJ][fLeader], 0, strlen(FamilyInfo[DoJ][fLeader]), MAX_PLAYER_NAME);
			SendClientMessageToAll(COLOR_YELLOW, "ВЫБОРЫ НЕ СОСТОЯЛИСЬ. Причина: отсутствие лучшего кандидата." );
			SaveVoteSQL();
			return 1;
		}
	    if(WeekOnline > LastOnline)
	    {
			Question[qApprove] = 0;
			format(strings, sizeof(strings), "ВЫБОРЫ ОТМЕНЕНЫ. Причина: губернатор %s увеличил онлайн c %d на %d часов за неделю.",
				FamilyInfo[DoJ][fLeader], LastOnline, WeekOnline);
			Log(INVITE,strings);
	    	SendClientMessageToAll(COLOR_YELLOW, strings);
			SaveVoteSQL();
	    	return 1;
	    }

		//new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);//%02d/%02d/%04d, [09/12/2012 | 14:44:51]
		format(strings, sizeof(strings), "В Мэрии закончилось голосование. Победил %s !", playername);
		Log(INVITE,strings);
		//SendClientMessage(playerid, COLOR_YELLOW, strings);
		SendClientMessageToAll(COLOR_YELLOW, strings);
		Question[qApprove] = 0;
		SaveVoteSQL();
		//Update3DTextLabelText(ElectionInfo, 0xFFFFFFAA, "{FFFFFF}Нажмите '{0080FF}~k~~VEHICLE_ENTER_EXIT~{FFFFFF}'\nчтобы использовать банкомат");

		new playerid = ReturnUser(playername);
		//if(IsPlayerConnectedEx(playerid) && PlayerInfo[playerid][pLeader] == DoJ)
		if(!strcmp(FamilyInfo[DoJ][fLeader], playername, true))
		{
			SendClientMessageEx(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
		}
		else
		{
			new giveplayerid = MAX_PLAYERS-2;
			if( strcmp(FamilyInfo[DoJ][fLeader], "No-One", true) )
			{//если лидер какой то есть
				//new playername[MAX_PLAYER_NAME];
				//SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				strmid(giveplayername, FamilyInfo[DoJ][fLeader], 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
				giveplayerid = ReturnUser(giveplayername);//если игрока не в игре, то вернёт 0xFFFF или 65535, массив не возмёт тачку ячейку поэтому замениваем на MAX_PLAYERS-2
			    if( !IsPlayerConnected(giveplayerid) )// && giveplayerid != playerid
			    {   //если уволняется неиграющий
					OnPlayerLoadParameters(MAX_PLAYERS-2, giveplayername);
					UninvitePlayerid(MAX_PLAYERS-1, giveplayerid, giveplayername);
					if(PlayerInfo[giveplayerid][pAdmin] <= 5) PlayerInfo[giveplayerid][pAdmin] = 0;
					OnPlayerSaveParameters(giveplayerid, giveplayername);
					format(strings, sizeof(strings), "* %s был выкинут из Мин. Юстиции Лидером %s.", giveplayername, playername);
					Log(INVITE,strings);
					//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);
					OnPlayerInit(giveplayerid);
				}//not connected
				else //if(IsPlayerConnected(giveplayerid))
				{	//new playername[MAX_PLAYER_NAME];
					UninvitePlayerid(MAX_PLAYERS-1, giveplayerid, giveplayername);
					if(PlayerInfo[giveplayerid][pAdmin] <= 5) PlayerInfo[giveplayerid][pAdmin] = 0;
					format(strings, sizeof(strings), "* %s был выкинут из Мин. Юстиции Лидером %s.", PlayerName(giveplayerid), playername);
					Log(INVITE,strings);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);
				}
			}
			//------------------------------------------------------------------
			if(!IsPlayerConnectedEx(playerid))
			{
				OnPlayerLoadParameters(MAX_PLAYERS-2, playername);
				UninvitePlayerid(MAX_PLAYERS-1, giveplayerid, playername);
				MakeLeader(MAX_PLAYERS-2, giveplayerid, playername, DoJ);
				if(PlayerInfo[giveplayerid][pAdmin] <= 5) PlayerInfo[giveplayerid][pAdmin] = 5;
				OnPlayerSaveParameters(giveplayerid, playername);

				format(strings, sizeof(strings), "%s {FFFFFF}%s[%d]: {FFFF00}назначен лидером фракции %s.",
					GetPlayerRanks(giveplayerid), playername, giveplayerid, GetPlayerMembers(giveplayerid));
				Log(INVITE,strings);
				SendClientMessageToAll(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
				SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
				OnPlayerInit(giveplayerid);
			}
			else
			{
				UninvitePlayerid(MAX_PLAYERS-1, playerid, playername);
				MakeLeader(MAX_PLAYERS-2, playerid, playername, DoJ);
				if(PlayerInfo[giveplayerid][pAdmin] <= 5) PlayerInfo[playerid][pAdmin] = 5;

				format(strings, sizeof(strings), "%s {FFFFFF}%s[%d]: {FFFF00}назначен лидером фракции %s.",
					GetPlayerRanks(playerid), playername, playerid, GetPlayerMembers(playerid));
				Log(INVITE,strings);
				SendClientMessageToAll(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
				SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
			}
		}
		new strtmp[22+24];
		strcat(strtmp, "Election_OneDayTimer ");
		strcat(strtmp, playername);
		TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();
	}
	return 1;
}//конец Election_OneDayTimer()




//##############################################################################//
//                                                                              //
//               ВЫПОЛНЯЕТСЯ ПРИ СТАРТЕ РЕЖИМА ИЗ GameModeInit()                //
//                                                                              //
//##############################################################################//


//------------------------------------------------------------------------------



stock LoadFamiliesSQL()//для банд
{
	new time = GetTickCount();
	new idx=1;//=TEAM_MAFIA+1;
	//new Data[2+24+128+24+2+6*4+2+3+3+10+3*2+2 + 12];//182 +
	new Field[128];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `families`");
	do
	{
		if(idx > db_num_rows(db_result)) break;//sizeof(FamilyInfo)
		db_get_field_assoc(db_result, "ID", Field, sizeof(Field) ); FamilyInfo[idx][NumberFamily] = strval(Field);
		db_get_field_assoc(db_result, "Name", Field, sizeof(Field) ); strmid(FamilyInfo[idx][fName], Field, 0, strlen(Field), 20);
		db_get_field_assoc(db_result, "MOTD", Field, sizeof(Field) ); strmid(FamilyInfo[idx][fMOTD], Field, 0, strlen(Field), 128);
		db_get_field_assoc(db_result, "Leader", Field, sizeof(Field) ); strmid(FamilyInfo[idx][fLeader], Field, 0, strlen(Field), MAX_PLAYER_NAME);
		db_get_field_assoc(db_result, "Members", Field, sizeof(Field) ); FamilyInfo[idx][fMembers] = strval(Field);
		db_get_field_assoc(db_result, "SpawnX", Field, sizeof(Field) ); FamilyInfo[idx][fSpawns][0] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnY", Field, sizeof(Field) ); FamilyInfo[idx][fSpawns][1] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnZ", Field, sizeof(Field) ); FamilyInfo[idx][fSpawns][2] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnA", Field, sizeof(Field) ); FamilyInfo[idx][fSpawns][3] = floatstr(Field);
		db_get_field_assoc(db_result, "Int", Field, sizeof(Field) ); FamilyInfo[idx][fInterior] = strval(Field);
		db_get_field_assoc(db_result, "World", Field, sizeof(Field) ); FamilyInfo[idx][fWorld] = strval(Field);
		db_get_field_assoc(db_result, "Local", Field, sizeof(Field) ); FamilyInfo[idx][fLocal] = strval(Field);
		db_get_field_assoc(db_result, "Bank", Field, sizeof(Field) ); FamilyInfo[idx][fBank] = strval(Field);
		db_get_field_assoc(db_result, "Rank", Field, sizeof(Field) ); FamilyInfo[idx][fRank] = strval(Field);
		db_get_field_assoc(db_result, "Alliance", Field, sizeof(Field) ); strmid(FamilyInfo[idx][fAlliance], Field, 0, strlen(Field), 20);
		db_get_field_assoc(db_result, "War", Field, sizeof(Field) ); strmid(FamilyInfo[idx][fWar], Field, 0, strlen(Field), 20);
		db_get_field_assoc(db_result, "Material", Field, sizeof(Field) ); FamilyInfo[idx][fMaterial] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
	printf("15/19. [Загрузка банд и фракций]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}

stock SaveFamiliesSQL(const playername[])//для банд
{
	#pragma unused playername
	new time = GetTickCount();
	new ToBase[218 + 24+128+24+2+6*4+2+3+3+10+3*2+2];
	for(new idx = 1; idx < MAX_FAMILY; idx++)//TEAM_MAFIA
	{
		format(ToBase, sizeof(ToBase), "UPDATE `families` SET `Name`='%s',\
MOTD='%s',\
Leader='%s',\
Members=%d,\
SpawnX=%.1f,\
SpawnY=%.1f,\
SpawnZ=%.1f,\
SpawnA=%.1f,\
`Int`=%d,\
World=%d,\
Local=%d,\
Bank=%d,\
Rank=%d,\
Material=%d WHERE `ID`=%d",
		FamilyInfo[idx][fName],
		FamilyInfo[idx][fMOTD],
		FamilyInfo[idx][fLeader],
		FamilyInfo[idx][fMembers],
		FamilyInfo[idx][fSpawns][0],
		FamilyInfo[idx][fSpawns][1],
		FamilyInfo[idx][fSpawns][2],
		FamilyInfo[idx][fSpawns][3],//угол
		FamilyInfo[idx][fInterior],
		FamilyInfo[idx][fWorld],
		FamilyInfo[idx][fLocal],
		FamilyInfo[idx][fBank],
		FamilyInfo[idx][fRank],
		FamilyInfo[idx][fMaterial],
		idx);
		db_free_result(db_query(db_VW, ToBase));
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[69+2+6];
	format(strtmp, sizeof(strtmp), "5/19. [Сохранение фракций]: Было сохранено - %d, потрачено - %d (ms)", MAX_FAMILY, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}

stock ClearFamily(family)//вызывается по команде removegang
{   //для банд
	strmid(FamilyInfo[family][fLeader], "No-One", 0, 8, 8);
	FamilyInfo[family][fRank] = 11;

	new ToBase[40+2];
	format(ToBase, sizeof(ToBase), "DELETE FROM `blacklist` WHERE Family=%d", family);
 	db_free_result(db_query(db_VW, ToBase));
}



stock LoadTurfsSQL()
{
	new time = GetTickCount();
	new idx;
	//new Data[1+ 20+3 + 12];
	new Field[20];
	new DBResult:db_result = db_query(db_VW,"SELECT `Family` FROM `turfs`");
	do
	{
		if(idx > MAX_TURFS) break;
		strmid(TurfInfo[idx][zName], regions[idx][region_name], 0, 20, 32);
		db_get_field_assoc(db_result, "Family", Field, sizeof(Field) ); TurfInfo[idx][zFamily] = strval(Field);
		idx ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);

	//==========================================================================

	//устанавливаем всем бандам их цвета (переписываем загруженные из файла) и не меняем их ни когда
	FamilyInfo[TEAM_NONE][fColor] = 0x0000003C;//0xF6F6F63C(белый 60 прозрачность) /0x0000003C(черный 60 прозрачность)  [0xFF000069]
	FamilyInfo[TEAM_GROVE][fColor] = TEAM_GROVE_COLOR;
	FamilyInfo[TEAM_BALLAS][fColor] = TEAM_BALLAS_COLOR;
	FamilyInfo[TEAM_AZTEC][fColor] = TEAM_AZTECAS_COLOR;
	FamilyInfo[TEAM_VAGOS][fColor] = TEAM_VAGOS_COLOR;
	FamilyInfo[TEAM_NANG][fColor] = TEAM_NANG_COLOR;
	FamilyInfo[TEAM_RIFA][fColor] = TEAM_RIFA_COLOR;
	FamilyInfo[TEAM_TRIAD][fColor] = TEAM_TRIADS_COLOR;
	FamilyInfo[TEAM_BIKER][fColor] = TEAM_BIKERS_COLOR;
	FamilyInfo[TEAM_MAFIA][fColor] = TEAM_MAFIA_COLOR;

	FamilyInfo[DoT][fColor] = COLOR_DARKTURQUOISE;//0xF6F6F63C(белый 60 прозрачность) /0x0000003C(черный 60 прозрачность)  [0xFF000069]
	FamilyInfo[FBI][fColor] = COLOR_PALEPURPLE;
	FamilyInfo[DoD][fColor] = COLOR_EMERALD;
	FamilyInfo[DoH][fColor] = COLOR_MAUVE;
	FamilyInfo[LCN][fColor] = COLOR_VIOLET;
	FamilyInfo[Yakuza][fColor] = COLOR_CERISE;
	FamilyInfo[DoJ][fColor] = COLOR_HERBAL;
	FamilyInfo[Hitman][fColor] = COLOR_BROWN;
	FamilyInfo[SAN][fColor] = COLOR_LIGHTORANGE;
	FamilyInfo[DoE][fColor] = COLOR_LIGHTBROWN;

	// Zones
	for(new j=0; j<MAX_TURFS; j++)//для зон банд 230 MAX_TURFS
	{
//Создали 355 новых зон в памяти сервера
		Turfs[j] = GangZoneCreate(regions[j][region_minx], regions[j][region_miny], regions[j][region_maxx], regions[j][region_maxy]);//Создать новую зону в памяти сервера
		taketurfcount[j] = TimeTakeZone;//всем зонам установили время захвата

//устанавливаем всем зонам первоначальные цвета в соот. с цветом банды
		if(TurfInfo[j][zFamily] == 255 || TurfInfo[j][zFamily] == 0) TurfInfo[j][zColor] = FamilyInfo[0][fColor];
		else TurfInfo[j][zColor] = FamilyInfo[TurfInfo[j][zFamily]][fColor];
		//TurfInfo[j][zFamily] = 0;//временно
		//strmid(TurfInfo[j][zName], regions[j][region_name], 0, strlen(regions[j][region_name]), 255);
		//strlen - Эта функция может быть использована для проверки длины указанной строки.

//каждому бизу устанавливаем крышу
		for(new b=0; b<MAX_BIZ; b++)
		{   //сканируем все бизы что находятся в данной зоне
			if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], j) )//если биз находится в координатах по строке j из массива zones
			{   //если биз находится в данной зоне
				BizInfo[b][bExtortion] = TurfInfo[j][zFamily];
				//break;
			}
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{   //сканируем все бизы что находятся в данной зоне
			if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], j) )//если биз находится в координатах по строке j из массива zones
			{   //если биз находится в данной зоне
				SBizInfo[sb][sbExtortion] = TurfInfo[j][zFamily];
				//break;
			}
		}
	}

	//SaveTurfsSQL();//временно
	printf("16/19. [Загрузка зон]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}

stock InsertTurfsSQL()
{
	new ToBase[61 + 32+2+3 + 12];
	for(new idx=0; idx<MAX_TURFS; idx++)
	{
		format(ToBase, sizeof(ToBase),"INSERT INTO `turfs` (Name,Family) VALUES ('%s',%d)",
			regions[idx][region_name],//TurfInfo[idx][zName],
			TurfInfo[idx][zFamily]);
		db_free_result(db_query(db_VW, ToBase));
	}
}
stock SaveTurfsSQL()
{
	new time = GetTickCount();
	new ToBase[61 + 32+2+3];
	for(new idx=0; idx<MAX_TURFS; idx++)
	{
		format(ToBase, sizeof(ToBase), "UPDATE `turfs` SET Name='%s',\
Family=%d WHERE ID=%d",
			regions[idx][region_name],//TurfInfo[idx][zName],
			TurfInfo[idx][zFamily],
			idx+1);
		db_free_result(db_query(db_VW, ToBase));
	}
	//ИНФОРМИРОВАНИЕ
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "8/19. [Сохранение зон]: Было сохранено - %d, потрачено - %d (ms)", MAX_TURFS, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}


stock AddGuildSQL(guild)
{
	new ToBase[22+55+81+82+112 + 10+61+1+256+4+2+4*7+2+3+3+11+32+128+3*7+2+7+2+1+6+11+3+3+10+3+6];
	new idx = guild;

	strcat(ToBase, "INSERT INTO `clans` \
(`ID`,`Owner`,`Members`,`Brevis`,`Discription`,`MOTD`,`Logo`,\
`SpawnX`,`SpawnY`,`SpawnZ`,`SpawnA`,`SpawnInt`,`SpawnWorld`,`SpawnLocal`,\
`EntranceX`,`EntranceY`,`EntranceZ`,`Int`, \
`BuyPrice`,`Level`,`Lock`,`EntranceCost`,`Products`, `BuyProd`,`SellProd`,`Till`,`Date`,`Inkas`) VALUES ");
//(1, 'www.pecom.ru/images/logo.png', 1, 'Привет', 'ПЭК', 1, 0.0, 0.0, 0.0, 0.0, 0, 0, 255, 1, 'Danger_Hidden', 'Первая Экспедиционная Компания', 0.0, 0.0, 0.0, 0, 1000000, 10, 0, 10000, 100, 1, 10, 1000000, 1, 1000000);
	format(ToBase, sizeof(ToBase), "%s(%d,'%s',%d,'%s','%s','%s','%s', %.1f,%.1f,%.1f,%.1f,%d,%d,%d, %.1f,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
		ToBase,
		//ClanInfo[idx][NumberGuild],
		ClanInfo[idx][gID],
		ClanInfo[idx][gOwner],
		ClanInfo[idx][gMembers],
		ClanInfo[idx][gBrevis],
		ClanInfo[idx][gDiscription],
		ClanInfo[idx][gMOTD],
		ClanInfo[idx][gLogo],

		ClanInfo[idx][gSpawns][0],
		ClanInfo[idx][gSpawns][1],
		ClanInfo[idx][gSpawns][2],
		ClanInfo[idx][gSpawns][3],//угол
		ClanInfo[idx][gInterior],
		ClanInfo[idx][gWorld],
		ClanInfo[idx][gLocal],

		ClanInfo[idx][gEntranceX],
		ClanInfo[idx][gEntranceY],
		ClanInfo[idx][gEntranceZ],
		ClanInfo[idx][gInt],

		ClanInfo[idx][gBuyPrice],
		ClanInfo[idx][gLevel],
		ClanInfo[idx][gLock],
		ClanInfo[idx][gEntranceCost],
		ClanInfo[idx][gProducts],
		ClanInfo[idx][gBuyProd],
		ClanInfo[idx][gSellProd],
		ClanInfo[idx][gTill],
		ClanInfo[idx][gDate],
		ClanInfo[idx][gInkas]);
	db_free_result(db_query(db_VW, ToBase));
	guildcounter ++;
	return 1;
}
stock LoadClansSQL()
{
	for(new guild = 0; guild < MAX_CLANS; guild++)
	{   //инициализация всех кланов
		ClanInfo[guild][NumberGuild] = 0;
		ClanInfo[guild][gID] = 0;
		strmid(ClanInfo[guild][gOwner], "No-One", 0, 8, 8);
		ClanInfo[guild][gMembers] = 0;

	    ClanInfo[guild][gBuyPrice] = 0;
	    ClanInfo[guild][gLevel] = 0;
	    ClanInfo[guild][gLock] = 0;

	    ClanInfo[guild][gEntranceCost] = 0;
	    ClanInfo[guild][gProducts] = 100;
	    ClanInfo[guild][gBuyProd] = 1;
		ClanInfo[guild][gSellProd] = 10;

		ClanInfo[guild][gTill] = 0;
		ClanInfo[guild][gDate] = 0;
		ClanInfo[guild][gInkas] = 0;
	}

	new time = GetTickCount();
	new idx=0;
	//new Data[10+61+1+128+4+2+4*7+2+3+3+11+32+256+3*7+2+7+2+1+6+11+3+3+10+3+6 + 12];//182 +
	new Field[256+1];
	new DBResult:db_result = db_query(db_VW, "SELECT * FROM `clans`");
	do
	{
		if(idx > db_num_rows(db_result)) break;//sizeof(ClanInfo)
		db_get_field_assoc(db_result, "IND", Field, sizeof(Field) ); ClanInfo[idx][NumberGuild] = strval(Field);

		db_get_field_assoc(db_result, "ID", Field, sizeof(Field) ); ClanInfo[idx][gID] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) ); strmid(ClanInfo[idx][gOwner], Field, 0, strlen(Field), MAX_PLAYER_NAME);
		db_get_field_assoc(db_result, "Members", Field, sizeof(Field) ); ClanInfo[idx][gMembers] = strval(Field);
		db_get_field_assoc(db_result, "Brevis", Field, sizeof(Field) ); strmid(ClanInfo[idx][gBrevis], Field, 0, strlen(Field), 255);
		db_get_field_assoc(db_result, "Discription", Field, sizeof(Field) ); strmid(ClanInfo[idx][gDiscription], Field, 0, strlen(Field), 255);
		db_get_field_assoc(db_result, "MOTD", Field, sizeof(Field) ); strmid(ClanInfo[idx][gMOTD], Field, 0, strlen(Field), 255);
		//db_get_field_assoc(db_result, "Logo", Field, sizeof(Field) ); strmid(ClanInfo[idx][gLogo], Field, 0, strlen(Field), 255);

		db_get_field_assoc(db_result, "SpawnX", Field, sizeof(Field) ); ClanInfo[idx][gSpawns][0] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnY", Field, sizeof(Field) ); ClanInfo[idx][gSpawns][1] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnZ", Field, sizeof(Field) ); ClanInfo[idx][gSpawns][2] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnA", Field, sizeof(Field) ); ClanInfo[idx][gSpawns][3] = floatstr(Field);
		db_get_field_assoc(db_result, "SpawnInt", Field, sizeof(Field) ); ClanInfo[idx][gInterior] = strval(Field);
		db_get_field_assoc(db_result, "SpawnWorld", Field, sizeof(Field) ); ClanInfo[idx][gWorld] = strval(Field);
		db_get_field_assoc(db_result, "SpawnLocal", Field, sizeof(Field) ); ClanInfo[idx][gLocal] = strval(Field);

		db_get_field_assoc(db_result, "EntranceX", Field, sizeof(Field) ); ClanInfo[idx][gEntranceX] = floatstr(Field);
		db_get_field_assoc(db_result, "EntranceY", Field, sizeof(Field) ); ClanInfo[idx][gEntranceY] = floatstr(Field);
		db_get_field_assoc(db_result, "EntranceZ", Field, sizeof(Field) ); ClanInfo[idx][gEntranceZ] = floatstr(Field);
		db_get_field_assoc(db_result, "Int", Field, sizeof(Field) ); ClanInfo[idx][gInt] = strval(Field);

		db_get_field_assoc(db_result, "BuyPrice", Field, sizeof(Field) ); ClanInfo[idx][gBuyPrice] = strval(Field);
		db_get_field_assoc(db_result, "Level", Field, sizeof(Field) ); ClanInfo[idx][gLevel] = strval(Field);
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) ); ClanInfo[idx][gLock] = strval(Field);
		db_get_field_assoc(db_result, "EntranceCost", Field, sizeof(Field) ); ClanInfo[idx][gEntranceCost] = strval(Field);
		db_get_field_assoc(db_result, "Products", Field, sizeof(Field) ); ClanInfo[idx][gProducts] = strval(Field);
		db_get_field_assoc(db_result, "BuyProd", Field, sizeof(Field) ); ClanInfo[idx][gBuyProd] = strval(Field);
		db_get_field_assoc(db_result, "SellProd", Field, sizeof(Field) ); ClanInfo[idx][gSellProd] = strval(Field);
		db_get_field_assoc(db_result, "Till", Field, sizeof(Field) ); ClanInfo[idx][gTill] = strval(Field);
		db_get_field_assoc(db_result, "Date", Field, sizeof(Field) ); ClanInfo[idx][gDate] = strval(Field);
		db_get_field_assoc(db_result, "Inkas", Field, sizeof(Field) ); ClanInfo[idx][gInkas] = strval(Field);

		idx ++;
		guildcounter = idx;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);

	printf("17/19. [Загрузка кланов]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock SaveClansSQL(const playername[])//для банд
{
	#pragma unused playername
	new time = GetTickCount();
	new ToBase[1124];//508 + 10+61+1+256+4+2+4*7+2+3+3+11+32+128+3*7+2+7+2+1+6+11+3+3+10+3+6 = 1124
	for(new idx=0; idx<MAX_CLANS; idx++)
	{
		format(ToBase, sizeof(ToBase), "UPDATE `clans` SET `Owner`='%s',`Members`=%d,`Discription`='%s',\
`SpawnX`=%.1f,\
`SpawnY`=%.1f,\
`SpawnZ`=%.1f,\
`SpawnA`=%.1f,\
`SpawnInt`=%d,\
`SpawnWorld`=%d,\
`SpawnLocal`=%d,\
`EntranceX`=%.1f,\
`EntranceY`=%.1f,\
`EntranceZ`=%.1f,\
`Int`=%d,\
`BuyPrice`=%d,\
`Level`=%d,\
`Lock`=%d,\
`EntranceCost`=%d,\
`Products`=%d,\
`BuyProd`=%d,\
`SellProd`=%d,\
`Till`=%d,\
`Date`=%d,\
`Inkas`=%d WHERE `ID`=%d",
		ClanInfo[idx][gOwner],
		ClanInfo[idx][gMembers],
		ClanInfo[idx][gDiscription],

		ClanInfo[idx][gSpawns][0],
		ClanInfo[idx][gSpawns][1],
		ClanInfo[idx][gSpawns][2],
		ClanInfo[idx][gSpawns][3],//угол
		ClanInfo[idx][gInterior],
		ClanInfo[idx][gWorld],
		ClanInfo[idx][gLocal],

		ClanInfo[idx][gEntranceX],
		ClanInfo[idx][gEntranceY],
		ClanInfo[idx][gEntranceZ],
		ClanInfo[idx][gInt],

		ClanInfo[idx][gBuyPrice],
		ClanInfo[idx][gLevel],
		ClanInfo[idx][gLock],
		ClanInfo[idx][gEntranceCost],
		ClanInfo[idx][gProducts],
		ClanInfo[idx][gBuyProd],
		ClanInfo[idx][gSellProd],
		ClanInfo[idx][gTill],
		ClanInfo[idx][gDate],
		ClanInfo[idx][gInkas],
		//ClanInfo[idx][NumberGuild]);//idx);
		ClanInfo[idx][gID]);
		db_free_result(db_query(db_VW, ToBase));
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[69+2+6];
	format(strtmp, sizeof(strtmp), "6/19. [Сохранение кланов]: Было сохранено - %d, потрачено - %d (ms)", MAX_CLANS, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}



//##############################################################################//
//                                                                              //
//                           СПИСКИ ДЛЯ СТАТИСТИКИ                              //
//                                                                              //
//##############################################################################//
stock FinaceList(playerid, receipts, consuption, operation)//
{//receipts - доход, consuption - расход
	//if(TEST[61] != 0) return 1;//при 0 ф-ия работает
	//if(TEST[61] == 0) return 1;

#if defined STRIKEARENA_7777
	new timers = GetTickCount();

	/*new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);*/

	/*new ToBase[140 +  14+12+10+11+24+10+10+10+10];
	format(ToBase, sizeof(ToBase), "INSERT INTO `finance` (`Article`,`Date`,`Time`,`ID`,`Name`,`Cash`,`Bank`,`Receipts`,`Consuption`) VALUES (%d,'%s','%s',%d,'%s',%d,%d,%d,%d)",
		operation, date, time, PlayerInfo[playerid][pSQLID], PlayerName(playerid), PlayerInfo[playerid][pCash], PlayerInfo[playerid][pBank], receipts, consuption);
	db_free_result(db_query(db_VW, ToBase));*/

	new ToBase[185+1];//116 + 3+10+24+10+10+6+6 = 185
	format(ToBase, sizeof(ToBase), "INSERT INTO `finance` (`Article`,`ID`,`Name`,`Cash`,`Bank`,`Receipts`,`Consuption`) VALUES (%d,%d,'%s',%d,%d,%d,%d)",
		operation, PlayerInfo[playerid][pSQLID], PlayerName(playerid), PlayerInfo[playerid][pCash], PlayerInfo[playerid][pBank], receipts, consuption);
	db_free_result(db_query(db_VW, ToBase));

	new strtmp[50];//26+24 = 50
	strcat(strtmp, "FinaceList ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

#else
	#pragma unused playerid
	#pragma unused receipts
	#pragma unused consuption
	#pragma unused operation
#endif
	return 1;
}

stock CriminalList(playerid, turner[], const reason[], status)//108 ms -  938 ms
{//playerid - убийца
//0 - ничего, 1 - преступление, 2 - арест, 3 - перевод
	//if(TEST[62] != 0) return 1;
	//if(TEST[62] == 0) return 1;

#if defined STRIKEARENA_7777
	new timers = GetTickCount();

	new playername[MAX_PLAYER_NAME];
	if(playerid != MAX_PLAYERS-1)
	{
		GetPlayerName(playerid, playername, sizeof(playername));
	}
	else strmid(playername, "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[328+1];//118 +  12+10+11+24+24+128+1 = 328
	format(ToBase, sizeof(ToBase), "INSERT INTO `criminallist` (`Date`,`Time`,`ID`,Player,Turner,Reason,`Status`) VALUES ('%s','%s',%d,'%s','%s','%s',%d)",
		date, time, PlayerInfo[playerid][pSQLID], playername, turner, reason, status);
	db_free_result(db_query(db_VW, ToBase));

	new strtmp[50];//26+24 = 50
	strcat(strtmp, "CriminalList ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

//#elseif defined STRIKEARENA_7778

#else
	#pragma unused playerid
	#pragma unused turner
	#pragma unused reason
	#pragma unused status
#endif


	return 1;
}

stock KillList(playerid, killerid, family, rank, reason)//100 ms - 824 ms
{//playerid - убитый
	//if(TEST[63] != 0) return 1;

#if defined STRIKEARENA_7777

	if(gRealWar) return 1;
	if(gPlayerBoxing[killerid]) return 1;
	if(gInTerrorsCount[killerid]) return 1;
	if(gInCTerrorsCount[killerid]) return 1;
	if(LastKill[killerid] == playerid) return 1;// || LastKill[killerid] == MAX_PLAYERS-1

	/*if(TEST[63] == 0)
	{
	    new strtmp[45+24+3+24+3+32+3];
		format(strtmp, sizeof(strtmp), "player:%s[%d], killer:%s[%d], weapon: %s[%d]",
			PlayerName(playerid), playerid, PlayerName(killerid), killerid, GetDeathReason(killerid, reason), reason);
		Log(KILL, strtmp);
		return 1;
	}*/

	new timers = GetTickCount();

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[215];//128 +  12+10+24+11+24+2+2+2 = 215
	format(ToBase, sizeof(ToBase), "INSERT INTO `killlist` (`Date`,`Time`,`Player`,`ID`,`Killer`,`Family`,`Rank`,`Weapon`) VALUES ('%s','%s','%s',%d,'%s',%d,%d,%d)",
		date, time, PlayerName(playerid),
		PlayerInfo[killerid][pSQLID], PlayerName(killerid), family, rank, reason);
	db_free_result(db_query(db_VW, ToBase));

	new strtmp[50];//26+24 = 50
	strcat(strtmp, "KillList ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

#else
	#pragma unused playerid
	#pragma unused killerid
	#pragma unused family
	#pragma unused rank
	#pragma unused reason
#endif
	return 1;
}

stock InviteList(playerid, giveplayername[], family, rank, status)
{//status 0 - уволен, 1 - принят
#if defined STRIKEARENA_7777

	new playername[MAX_PLAYER_NAME];
	if(playerid != MAX_PLAYERS-1 && playerid != MAX_PLAYERS-2)
	{
		GetPlayerName(playerid, playername, sizeof(playername));
	}
	else strmid(playername, "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	if(!strcmp(playername, giveplayername, true)) return 1;//если сам себя принял, то в лог не писать

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[126 +  12+10+24+24+2+2+1];
	format(ToBase, sizeof(ToBase), "INSERT INTO `invitelist` (`Date`, `Time`, Player, Leader, Family, Rank, `Status`) VALUES ('%s', '%s', '%s', '%s', %d, %d, %d)",
		date, time, giveplayername, playername, family, rank, status);
 	db_free_result(db_query(db_VW, ToBase));

#else
	#pragma unused playerid
	#pragma unused giveplayername
	#pragma unused family
	#pragma unused rank
	#pragma unused status
#endif
	return 1;
}

stock BlackList(playerid, family, giveplayername[], reason[])
{
	//if(forplayerid == INVALID_PLAYER_ID) return 1;

#if defined STRIKEARENA_7777

	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[109 + 12+10+24+2+24+128];
	format(ToBase, sizeof(ToBase), "INSERT INTO `blacklist` (`Date`,`Time`, Player,Family,Leader, Reason) VALUES ('%s','%s', '%s',%d,'%s', '%s')",
		date, time, giveplayername, family, playername, reason);
	db_free_result(db_query(db_VW, ToBase));

#else
	#pragma unused playerid
	#pragma unused family
	#pragma unused giveplayername
	#pragma unused reason
#endif
}

stock WarnList(adminname[], forplayerid, days, const reason[])
{
#if defined STRIKEARENA_7777
	new playername[MAX_PLAYER_NAME];
	if(IsPlayerConnected(forplayerid))
	{
		GetPlayerName(forplayerid, playername, sizeof(playername));
	}
	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `warnlist` (Player,AdminLevel,`Level`,IP,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
		playername, PlayerInfo[forplayerid][pAdmin], PlayerInfo[forplayerid][pLevel],
		PlayerInfo[forplayerid][pIP], date, time, adminname, reason, days);
	db_free_result(db_query(db_VW, ToBase));
#else
	#pragma unused adminname
	#pragma unused forplayerid
	#pragma unused days
	#pragma unused reason
#endif
}

stock BanList(adminname[], forplayerid, days, const reason[])
{
#if defined STRIKEARENA_7777

	new playername[MAX_PLAYER_NAME];
	if(IsPlayerConnected(forplayerid))
	{
		GetPlayerName(forplayerid, playername, sizeof(playername));
	}

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `banlist` (Player,AdminLevel,`Level`,IP,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
		playername, PlayerInfo[forplayerid][pAdmin], PlayerInfo[forplayerid][pLevel],
		PlayerInfo[forplayerid][pIP], date, time, adminname, reason, days);
	db_free_result(db_query(db_VW, ToBase));

/*#if defined STRIKEARENA_7778
	new playername[MAX_PLAYER_NAME];
	if(IsPlayerConnected(forplayerid))
	{
		GetPlayerName(forplayerid, playername, sizeof(playername));
	}
	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `banlist` (Player,AdminLevel,`Level`,IP,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
		playername, PlayerInfo[forplayerid][pAdmin], PlayerInfo[forplayerid][pLevel],
		PlayerInfo[forplayerid][pIP], date, time, adminname, reason, days);
	db_free_result(db_query(db_VW, ToBase));
#elseif defined STRIKEARENA_7777*/

#else
	#pragma unused adminname
	#pragma unused forplayerid
	#pragma unused days
	#pragma unused reason
#endif

}

stock UnBanList(playername[], adminid, reason[])
{

#if defined STRIKEARENA_7777
	new adminname[MAX_PLAYER_NAME];
	GetPlayerName(adminid, adminname, sizeof(adminname));

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	//mysql_real_escape_string(playername, playername);
	//mysql_real_escape_string(date, date);
	//mysql_real_escape_string(time, time);
	//mysql_real_escape_string(adminname, adminname);
	//mysql_real_escape_string(reason, reason);

	new ToBase[98 + 24 + 12+10 + 24 + 128];
	format(ToBase, sizeof(ToBase), "INSERT INTO `unbanlist` (Player,`Date`,`Time`,Admin,Reason) VALUES ('%s', '%s', '%s', '%s', '%s')",
		playername,
		date, time,
		adminname, reason);
	db_free_result(db_query(db_VW, ToBase));

	//format(strings, sizeof(strings), "[%d:%02d:%02d] AdmCmd: %s was unbanned by %s's.",  lH,lM,lS, playername, adminname);
	//Log(BAN,strcmd);
	//format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
	//SendClientMessageToAll(COLOR_RED, strings);

/*#if defined STRIKEARENA_7778
	new adminname[MAX_PLAYER_NAME];
	GetPlayerName(adminid, adminname, sizeof(adminname));

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	//mysql_real_escape_string(playername, playername);
	//mysql_real_escape_string(date, date);
	//mysql_real_escape_string(time, time);
	//mysql_real_escape_string(adminname, adminname);
	//mysql_real_escape_string(reason, reason);

	new ToBase[98 + 24 + 12+10 + 24 + 128];
	format(ToBase, sizeof(ToBase), "INSERT INTO `unbanlist` (Player,`Date`,`Time`,Admin,Reason) VALUES ('%s', '%s', '%s', '%s', '%s')",
		playername,
		date, time,
		adminname, reason);
	db_free_result(db_query(db_VW, ToBase));

	//format(strings, sizeof(strings), "[%d:%02d:%02d] AdmCmd: %s was unbanned by %s's.",  lH,lM,lS, playername, adminname);
	//Log(BAN,strcmd);
	//format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
	//SendClientMessageToAll(COLOR_RED, strings);
#elseif defined STRIKEARENA_7777*/

#else
	#pragma unused playername
	#pragma unused adminid
	#pragma unused reason
#endif

}



stock NetList(playerid)
{
	new dlgitem[50*(13+24+3+5)];
	new str[13+24+3+5];
	new count;
	new stats[418+1];
	new playername[MAX_PLAYER_NAME];
	strins(dlgitem, "______________________________\nNetList:\n",strlen(dlgitem));
	//for(new j=0, i; j<MaxPlayers; j++)	{
		//i = PLIDs[j];
	for(new i=0; i<GetMaxPlayers(); i++) {
		if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
		if(count >= 50) break;
        GetPlayerNetworkStats(i, stats, sizeof(stats)); // get your own networkstats
		new mss = strval(findParam(stats, "Messages sent: "));
		if( (mss - nMessages[i]) < 10) continue;

		GetPlayerName(i, playername, sizeof(playername));
		format(str, sizeof(str), "%d\t%s\t%d\n", i, playername, (mss - nMessages[i]));
		strins(dlgitem, str, strlen(dlgitem));
  		count++;
	}
	strins(dlgitem, "\n______________________________\n", strlen(dlgitem), 35);
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		new strtmp[56+4+4+12];
		format(strtmp, sizeof(strtmp), "Error: NetList strlen(dlgitem): %d, sizeof(dlgitem): %d",
			strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strtmp);
		return 1;
	}
	ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "     id         name                              messages", dlgitem, "OK", "");
	return 1;
}

//для серийников
stock SerialList(playerid)
{
	new dlgitem[30*(15+2+20+64)];
	//new strings[MAX_STRING];
	//strins(dlgitem, "______________________________\nSerialList:\n",strlen(dlgitem));
	new serialid[64];//164
	new playername[MAX_PLAYER_NAME];
	new count;
	//for(new i=0; i<GetMaxPlayers(); i++)//сканируем всех
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//if( IsPlayerNPC(i) ) continue;
		//if(count >= 30) break;
		gpci(i, serialid, sizeof(serialid));
		GetPlayerName(i, playername, sizeof(playername));
		if(strlen(playername) < 14) format(strings, sizeof(strings), "%d\t%s\t\t%s\n", i, playername, serialid);
		else format(strings, sizeof(strings), "%d\t%s\t%s\n", i, playername, serialid);
		strins(dlgitem, strings, strlen(dlgitem), strlen(strings));
  		count++;
	}//DIALOG_STYLE_LIST
	//strins(dlgitem, "\n______________________________\n", strlen(dlgitem), 35);
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		new strtmp[59+4+4+12];
		format(strtmp, sizeof(strtmp), "Error: SerialList strlen(dlgitem): %d, sizeof(dlgitem): %d",
			strlen(dlgitem), sizeof(dlgitem));
		//ShowPlayerDialogGap(playerid, 101, DIALOG_STYLE_MSGBOX, "SerialList", strtmp, "OK", "");
		//SendClientMessage(playerid, 0x6EF83CFF, strtmp);
		Log(ERROR, strtmp);
		return 1;
	}
	ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "     id         name                              serial", dlgitem, "OK", "");
	return 1;
}


//##############################################################################//
//                                                                              //
//                  СПИСКИ сформированные из базы данных                         //
//                                                                              //
//##############################################################################//


stock ShowPlayerBans(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	new GetStepPlayer = GetPVarInt(playerid, "TempStep");

	new Field[24]; //new Data[1024];
	new CurrentStatus;
	new idx = GetStepPlayer;
	new TempName[MAX_PLAYER_NAME];
	new BaseID, TimeForBan, Money, House, Biz;

	new ToBase[128]; new Step = GetStepPlayer+20;
	//format(ToBase, sizeof(ToBase), "SELECT `Name`,`ID``,Warns`,`Cash`,`House`,`Bizz` FROM `players` WHERE `Level`=-999 AND `Warns`>%d LIMIT %d, %d", getdate(), GetStepPlayer, GetStepPlayer+21);
	format(ToBase, sizeof(ToBase), "SELECT `Name`,`ID``,Warns`,`Cash`,`House`,`Bizz` FROM `players` WHERE `Level`=-999 AND `Warns`>%d", getdate());
 	new DBResult:db_result = db_query(db_VW, ToBase);
	if(db_num_rows(db_result))
 	{
 		new ResultRow[2024];
 	    strcat(ResultRow, "ID \tName \t\t\tBanTime \tCash \tHouse \tBizz\n______________________________________________________________________\n");
		do
		{
		    if(idx >= Step)
		    {
				SetPVarInt(playerid, "TempStep", idx);
				new info[24+3];
				new curdate = getdate();//Получает текущий день в году
				format(info, sizeof(info), "BANS LIST ON THE %d DAY", curdate);
		        ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, info, ResultRow, "Next", "Cancel");
		        db_free_result(db_result);
				return 1;
		    }
  			db_get_field_assoc(db_result, "Name", Field, sizeof(Field) ); strmid(TempName, Field, 0, strlen(Field), MAX_PLAYER_NAME);
            db_get_field_assoc(db_result, "ID", Field, sizeof(Field) ); BaseID = strval(Field);
            db_get_field_assoc(db_result, "Warns", Field, sizeof(Field) ); TimeForBan = strval(Field);
           	db_get_field_assoc(db_result, "Cash", Field, sizeof(Field) ); Money = strval(Field);
           	db_get_field_assoc(db_result, "House", Field, sizeof(Field) ); House = strval(Field);
           	db_get_field_assoc(db_result, "Bizz", Field, sizeof(Field) ); Biz = strval(Field);
			if(strlen(TempName) == 13)
			{
            	format(ResultRow, sizeof(ResultRow), "%s%d \t%s \t\t%d \t\t%d \t%d \t%d\n", ResultRow,BaseID,TempName,TimeForBan,Money,House,Biz);
            }
			else if(strlen(TempName) < 13)
			{
            	format(ResultRow, sizeof(ResultRow), "%s%d \t%s \t\t%d \t\t%d \t%d \t%d\n", ResultRow,BaseID,TempName,TimeForBan,Money,House,Biz);
            }
            else
            {
                format(ResultRow, sizeof(ResultRow), "%s%d \t%s \t%d \t\t%d \t%d \t%d\n", ResultRow,BaseID,TempName,TimeForBan,Money,House,Biz);
            }
			idx ++;
		}
		while(db_next_row(db_result));

		CurrentStatus = GetPVarInt(playerid, "TempStep");
		if(GetStepPlayer != 0 && CurrentStatus < Step)
		{
		    SetPVarInt(playerid, "TempStep", CurrentStatus-20);
			db_free_result(db_result);
			new info[24+3];
			new curdate = getdate();//Получает текущий день в году
			format(info, sizeof(info), "BANS LIST ON THE %d DAY", curdate);
			ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, info, ResultRow, "Back", "Cancel");
			return 1;
		}
		else
		{
			db_free_result(db_result);
			new info[24+3];
			new curdate = getdate();//Получает текущий день в году
			format(info, sizeof(info), "BANS LIST ON THE %d DAY", curdate);
			ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, info, ResultRow, "Update", "Cancel");
			return 1;
		}
	}
	else { LIST(playerid); SendClientMessage(playerid, COLOR_GREY, "   Бан лист пуст!"); }
	return 1;
}
stock BANLIST_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BANLIST_DIALOG) return 1;//44
	if(!response)
	{
	    DeletePVar(playerid, "TempStep");
     	LIST(playerid);
	 	return 1;
	}
	//new msgitem[256+1];
	//new giveplayerid;
//ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, "BANS LIST", ResultRow, "Back", "Cancel");
	ShowPlayerBans(playerid);
	return 1;
}








//##############################################################################//


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//SpawnSTEP6
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
stock OnPlayerLoadParameters(playerid, const nameplayer[])//вызывается из CheckPassword или по команде /showplayerstats
{//ВНИМАНИЕ: перед должны быть db_result = db_query(db_VW, ToBase);
	if(playerid < 0 || playerid >= MAX_PLAYERS) return 1;//чтобы не было переполнения массива

	//#pragma unused nameplayer
	new ToBase[52+MAX_PLAYER_NAME];
	format(ToBase, sizeof(ToBase), "SELECT * FROM `players` WHERE `Name` = '%s'", nameplayer);
	new DBResult:db_result = db_query(db_VW, ToBase);
	if(!db_num_rows(db_result)) { printf("В таблице `players` %d строк", db_num_rows(db_result)); return 1; }

	new Field[34];//длина самого большого параметра
	db_get_field_assoc(db_result, "ID", Field, sizeof(Field) );   PlayerInfo[playerid][pSQLID] = strval(Field);
	//db_get_field_assoc(db_result, "Name");//strmid(PlayerInfo[playerid][pName], "Unknown", 0, strlen("Unknown"), sizeof(Field));
	db_get_field_assoc(db_result, "Mail", Field, sizeof(Field) );  strmid(PlayerInfo[playerid][pMail], Field, 0, strlen(Field), sizeof(Field));
	db_get_field_assoc(db_result, "IP", Field, sizeof(Field) );  strmid(PlayerInfo[playerid][pIP], Field, 0, strlen(Field), sizeof(Field));	//не загружать, т.к. при входе он инициализируется
//если сработает ф-ия, то IP может загрузиться пустым
	db_get_field_assoc(db_result, "Sex", Field, sizeof(Field) );   PlayerInfo[playerid][pSex] = strval(Field);
	db_get_field_assoc(db_result, "Age", Field, sizeof(Field) );   strmid(PlayerInfo[playerid][pAge], Field, 0, strlen(Field), sizeof(Field));
	//db_get_field_assoc(db_result, "Origin", Field, sizeof(Field) );   PlayerInfo[playerid][pOrigin] = strval(Field);
	db_get_field_assoc(db_result, "DepositDay", Field, sizeof(Field) );   PlayerInfo[playerid][pDepositDay] = strval(Field);
	db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   PlayerInfo[playerid][pLevel] = strval(Field);
	db_get_field_assoc(db_result, "AdminLevel", Field, sizeof(Field) );   PlayerInfo[playerid][pAdmin] = strval(Field);
	db_get_field_assoc(db_result, "Account", Field, sizeof(Field) );   PlayerInfo[playerid][pAccount] = strval(Field);
	db_get_field_assoc(db_result, "Muted", Field, sizeof(Field) );   PlayerInfo[playerid][pMuted] = strval(Field);
	db_get_field_assoc(db_result, "Warns", Field, sizeof(Field) );   PlayerInfo[playerid][pWarns] = strval(Field);
	db_get_field_assoc(db_result, "ConnectTime", Field, sizeof(Field) );   PlayerInfo[playerid][pConnectTime] = strval(Field);
	db_get_field_assoc(db_result, "Respect", Field, sizeof(Field) );   PlayerInfo[playerid][pRespect] = strval(Field);
	db_get_field_assoc(db_result, "RespectDay", Field, sizeof(Field) );   PlayerInfo[playerid][pRespectDay] = strval(Field);
	db_get_field_assoc(db_result, "PayCheck", Field, sizeof(Field) );   PlayerInfo[playerid][pPayCheck] = strval(Field);
	db_get_field_assoc(db_result, "PayDay", Field, sizeof(Field) );   PlayerInfo[playerid][pPayTime] = strval(Field);
	db_get_field_assoc(db_result, "Deposit", Field, sizeof(Field) );   PlayerInfo[playerid][pDeposit] = strval(Field);
	db_get_field_assoc(db_result, "Cash", Field, sizeof(Field) );   PlayerInfo[playerid][pCash] = strval(Field);
	db_get_field_assoc(db_result, "Bank", Field, sizeof(Field) );   PlayerInfo[playerid][pBank] = strval(Field);
	//db_get_field_assoc(db_result, "Gold", Field, sizeof(Field) );   PlayerInfo[playerid][pGold] = strval(Field);
	db_get_field_assoc(db_result, "SHealth", Field, sizeof(Field) );   PlayerInfo[playerid][pSHealth] = floatstr(Field);
	db_get_field_assoc(db_result, "Health", Field, sizeof(Field) );   PlayerInfo[playerid][pHealth] = floatstr(Field);

	db_get_field_assoc(db_result, "Interior", Field, sizeof(Field) );   PlayerInfo[playerid][pInt] = strval(Field);
	//SetPVarInt(playerid, "FirstInterior", PlayerInfo[playerid][pInt]);//см. OnPlayerLogin

	db_get_field_assoc(db_result, "Pos_x", Field, sizeof(Field) );   PlayerInfo[playerid][pPos_x] = floatstr(Field);
	db_get_field_assoc(db_result, "Pos_y", Field, sizeof(Field) );   PlayerInfo[playerid][pPos_y] = floatstr(Field);
	db_get_field_assoc(db_result, "Pos_z", Field, sizeof(Field) );   PlayerInfo[playerid][pPos_z] = floatstr(Field);

	db_get_field_assoc(db_result, "Virtual", Field, sizeof(Field) );   PlayerInfo[playerid][pVirtual] = strval(Field);
	//SetPVarInt(playerid, "FirstVirtual", PlayerInfo[playerid][pVirtual]);//см. OnPlayerLogin

	db_get_field_assoc(db_result, "Local", Field, sizeof(Field) );   PlayerInfo[playerid][pLocal] = strval(Field);
	//SetPVarInt(playerid, "FirstLocal", PlayerInfo[playerid][pLocal]);//см. OnPlayerLogin

	db_get_field_assoc(db_result, "House", Field, sizeof(Field) );   PlayerInfo[playerid][pHouse] = strval(Field);
	db_get_field_assoc(db_result, "Bizz", Field, sizeof(Field) );   PlayerInfo[playerid][pBizz] = strval(Field);
	db_get_field_assoc(db_result, "Job", Field, sizeof(Field) );   PlayerInfo[playerid][pJob] = strval(Field);
	db_get_field_assoc(db_result, "Team", Field, sizeof(Field) );   PlayerInfo[playerid][pTeam] = strval(Field);
	db_get_field_assoc(db_result, "Member", Field, sizeof(Field) );   PlayerInfo[playerid][pMember] = strval(Field);
	db_get_field_assoc(db_result, "Leader", Field, sizeof(Field) );   PlayerInfo[playerid][pLeader] = strval(Field);
	db_get_field_assoc(db_result, "Rank", Field, sizeof(Field) );   PlayerInfo[playerid][pRank] = strval(Field);
	db_get_field_assoc(db_result, "Char", Field, sizeof(Field) );   PlayerInfo[playerid][pChar] = strval(Field);
	db_get_field_assoc(db_result, "Model", Field, sizeof(Field) );   PlayerInfo[playerid][pModel] = strval(Field);
	db_get_field_assoc(db_result, "ContractTime", Field, sizeof(Field) );   PlayerInfo[playerid][pContractTime] = strval(Field);
	db_get_field_assoc(db_result, "MinerSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pMinerSkill] = strval(Field);
	db_get_field_assoc(db_result, "LawSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pLawSkill] = strval(Field);
	db_get_field_assoc(db_result, "RoadSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pRoadSkill] = strval(Field);
	db_get_field_assoc(db_result, "DrugsSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pDrugsSkill] = strval(Field);
	db_get_field_assoc(db_result, "JackSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pJackSkill] = strval(Field);
	db_get_field_assoc(db_result, "ProfSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pProfSkill] = strval(Field);
	db_get_field_assoc(db_result, "MechSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pMechSkill] = strval(Field);
	db_get_field_assoc(db_result, "FarmSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pFarmSkill] = strval(Field);
	db_get_field_assoc(db_result, "GunSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pGunSkill] = strval(Field);
	db_get_field_assoc(db_result, "CarSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pCarSkill] = strval(Field);
	db_get_field_assoc(db_result, "InkasSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pInkasSkill] = strval(Field);
	db_get_field_assoc(db_result, "BookmakerSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pBookmakerSkill] = strval(Field);
	db_get_field_assoc(db_result, "TaxiSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pTaxiSkill] = strval(Field);
	db_get_field_assoc(db_result, "BusSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pBusSkill] = strval(Field);
	db_get_field_assoc(db_result, "CourierSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pCourierSkill] = strval(Field);
	db_get_field_assoc(db_result, "TruckSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pTruckSkill] = strval(Field);
	db_get_field_assoc(db_result, "TrashSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pTrashSkill] = strval(Field);
	db_get_field_assoc(db_result, "LoadSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pLoadSkill] = strval(Field);
	db_get_field_assoc(db_result, "WoodSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pWoodSkill] = strval(Field);
	db_get_field_assoc(db_result, "FishSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pFishSkill] = strval(Field);
	db_get_field_assoc(db_result, "FireSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pFireSkill] = strval(Field);
	db_get_field_assoc(db_result, "CookSkill", Field, sizeof(Field) );   PlayerInfo[playerid][pCookSkill] = strval(Field);

	db_get_field_assoc(db_result, "CarLic", Field, sizeof(Field) );   PlayerInfo[playerid][pCarLic] = strval(Field);
	db_get_field_assoc(db_result, "BikeLic", Field, sizeof(Field) );   PlayerInfo[playerid][pBikeLic] = strval(Field);
	db_get_field_assoc(db_result, "FlyLic", Field, sizeof(Field) );   PlayerInfo[playerid][pFlyLic] = strval(Field);
	db_get_field_assoc(db_result, "BoatLic", Field, sizeof(Field) );   PlayerInfo[playerid][pBoatLic] = strval(Field);
	db_get_field_assoc(db_result, "FishLic", Field, sizeof(Field) );   PlayerInfo[playerid][pFishLic] = strval(Field);
	db_get_field_assoc(db_result, "GunLic", Field, sizeof(Field) );   PlayerInfo[playerid][pGunLic] = strval(Field);
	db_get_field_assoc(db_result, "Gun1", Field, sizeof(Field) );   PlayerInfo[playerid][pGun1] = strval(Field);
	db_get_field_assoc(db_result, "Ammo1", Field, sizeof(Field) );   PlayerInfo[playerid][pAmmo1] = strval(Field);
	db_get_field_assoc(db_result, "Gun2", Field, sizeof(Field) );   PlayerInfo[playerid][pGun2] = strval(Field);
	db_get_field_assoc(db_result, "Ammo2", Field, sizeof(Field) );   PlayerInfo[playerid][pAmmo2] = strval(Field);
	db_get_field_assoc(db_result, "Gun3", Field, sizeof(Field) );   PlayerInfo[playerid][pGun3] = strval(Field);
	db_get_field_assoc(db_result, "Ammo3", Field, sizeof(Field) );   PlayerInfo[playerid][pAmmo3] = strval(Field);
	db_get_field_assoc(db_result, "Gun4", Field, sizeof(Field) );   PlayerInfo[playerid][pGun4] = strval(Field);
	db_get_field_assoc(db_result, "Ammo4", Field, sizeof(Field) );   PlayerInfo[playerid][pAmmo4] = strval(Field);
	db_get_field_assoc(db_result, "Gun22Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun22Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun23Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun23Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun24Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun24Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun25Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun25Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun26Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun26Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun27Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun27Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun28Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun28Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun29Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun29Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun30Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun30Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun31Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun31Skill] = strval(Field);
	db_get_field_assoc(db_result, "Gun34Skill", Field, sizeof(Field) );   PlayerInfo[playerid][pGun34Skill] = strval(Field);
	db_get_field_assoc(db_result, "HeadValue", Field, sizeof(Field) );   PlayerInfo[playerid][pHeadValue] = strval(Field);
	db_get_field_assoc(db_result, "Wins", Field, sizeof(Field) );   PlayerInfo[playerid][pWins] = strval(Field);
	db_get_field_assoc(db_result, "Loses", Field, sizeof(Field) );   PlayerInfo[playerid][pLoses] = strval(Field);
	db_get_field_assoc(db_result, "Kills", Field, sizeof(Field) );   PlayerInfo[playerid][pKills] = strval(Field);
	db_get_field_assoc(db_result, "Deaths", Field, sizeof(Field) );   PlayerInfo[playerid][pDeaths] = strval(Field);
	db_get_field_assoc(db_result, "Accident", Field, sizeof(Field) );   PlayerInfo[playerid][pAccident] = strval(Field);
	db_get_field_assoc(db_result, "Ticket", Field, sizeof(Field) );   PlayerInfo[playerid][pTicket] = strval(Field);
	db_get_field_assoc(db_result, "Crimes", Field, sizeof(Field) );   PlayerInfo[playerid][pCrimes] = strval(Field);
	db_get_field_assoc(db_result, "Arrested", Field, sizeof(Field) );   PlayerInfo[playerid][pArrested] = strval(Field);
	db_get_field_assoc(db_result, "WantedDeaths", Field, sizeof(Field) );   PlayerInfo[playerid][pWantedDeaths] = strval(Field);
	db_get_field_assoc(db_result, "Wanted", Field, sizeof(Field) );    WantedPoints[playerid] = strval(Field);
	db_get_field_assoc(db_result, "Article", Field, sizeof(Field) );   PlayerInfo[playerid][pArticle] = strval(Field);
	db_get_field_assoc(db_result, "Part", Field, sizeof(Field) );   PlayerInfo[playerid][pPart] = strval(Field);
	db_get_field_assoc(db_result, "Jailed", Field, sizeof(Field) );   PlayerInfo[playerid][pJailed] = strval(Field);
	db_get_field_assoc(db_result, "JailTime", Field, sizeof(Field) );   PlayerInfo[playerid][pJailTime] = strval(Field);
	db_get_field_assoc(db_result, "JailPrice", Field, sizeof(Field) );   PlayerInfo[playerid][pJailPrice] = strval(Field);
	db_get_field_assoc(db_result, "UpgradePoints", Field, sizeof(Field) );   PlayerInfo[playerid][pPupgrade] = strval(Field);

	new Perks[11];
	db_get_field_assoc(db_result, "Perks", Perks, sizeof(Perks) );
	PlayerInfo[playerid][pAlcoholPerk] = Perks[0]-'0';
	PlayerInfo[playerid][pDrugPerk] = Perks[1]-'0';
	PlayerInfo[playerid][pMiserPerk] = Perks[2]-'0';
	PlayerInfo[playerid][pPainPerk] = Perks[3]-'0';
	PlayerInfo[playerid][pTraderPerk] = Perks[4]-'0';
	PlayerInfo[playerid][pHunger] = Perks[5]-'0';////АнтиГолод
	PlayerInfo[playerid][pLeisure] = Perks[6]-'0';//АнтиДосуг
	PlayerInfo[playerid][pContact] = Perks[7]-'0';//АнтиОбщение
	PlayerInfo[playerid][pToilet] = Perks[8]-'0';//АнтиТуалет
	PlayerInfo[playerid][pVigour] = Perks[9]-'0';//АнтиБодрость

	db_get_field_assoc(db_result, "STD", Field, sizeof(Field) );   PlayerInfo[playerid][pSTD] = strval(Field);
	if(PlayerInfo[playerid][pSTD] == IsNotBeenIll) PlayerInfo[playerid][pSTD] = 0;

	new PlayerItems[11];
	db_get_field_assoc(db_result, "PlayerItems", PlayerItems, sizeof(PlayerItems) );
	PlayerInfo[playerid][pDice] = PlayerItems[0]-'0';
	PlayerInfo[playerid][pCigars] = PlayerItems[1]-'0';
	Groceries[playerid][gChickens] = PlayerItems[2]-'0'; new rand = random(15);	Groceries[playerid][gChicken] = (1+rand);
	Groceries[playerid][gHamburgers] = PlayerItems[3]-'0'; rand = random(15); Groceries[playerid][gHamburger] = (1+rand);
	Groceries[playerid][gPizzas] = PlayerItems[4]-'0'; rand = random(15); Groceries[playerid][gPizza] = (1+rand);
	PlayerInfo[playerid][pFishes] = PlayerItems[5]-'0';
	PlayerInfo[playerid][pAdrenalin] = PlayerItems[6]-'0';

	Groceries[playerid][gBeer] = PlayerItems[7]-'0';
	//Groceries[playerid][gVodka] = PlayerItems[8]-'0';
	//Groceries[playerid][gSoda] = PlayerItems[9]-'0';

	new VehicleItems[11];
	db_get_field_assoc(db_result, "VehicleItems", VehicleItems, sizeof(VehicleItems) );
	PlayerInfo[playerid][pAntiradar] = VehicleItems[0]-'0';
	PlayerInfo[playerid][pGPS] = VehicleItems[1]-'0';
	PlayerInfo[playerid][pCDPlayer] = VehicleItems[2]-'0';
	PlayerInfo[playerid][pFuel] = VehicleItems[3]-'0';

	//db_get_field_assoc(db_result, "Antiradar", Field, sizeof(Field) );   PlayerInfo[playerid][pAntiradar] = strval(Field);
	//db_get_field_assoc(db_result, "GPS", Field, sizeof(Field) );   PlayerInfo[playerid][pGPS] = strval(Field);
	//db_get_field_assoc(db_result, "CDPlayer", Field, sizeof(Field) );   PlayerInfo[playerid][pCDPlayer] = strval(Field);

	//db_get_field_assoc(db_result, "Dice", Field, sizeof(Field) );   PlayerInfo[playerid][pDice] = strval(Field);
	db_get_field_assoc(db_result, "Drugs", Field, sizeof(Field) );   PlayerInfo[playerid][pDrugs] = strval(Field);
	//db_get_field_assoc(db_result, "Cigars", Field, sizeof(Field) );   PlayerInfo[playerid][pCigars] = strval(Field);
	//db_get_field_assoc(db_result, "Fishes", Field, sizeof(Field) );   PlayerInfo[playerid][pFishes] = strval(Field);
	//db_get_field_assoc(db_result, "Fuel", Field, sizeof(Field) );   PlayerInfo[playerid][pFuel] = strval(Field);
	db_get_field_assoc(db_result, "LottoNr", Field, sizeof(Field) );   PlayerInfo[playerid][pLottoNr] = strval(Field);
	db_get_field_assoc(db_result, "Materials", Field, sizeof(Field) );   PlayerInfo[playerid][pMats] = strval(Field);
	db_get_field_assoc(db_result, "Mushroom", Field, sizeof(Field) );   PlayerInfo[playerid][pMushroom] = strval(Field);
	db_get_field_assoc(db_result, "PhoneNr", Field, sizeof(Field) );   PlayerInfo[playerid][pPnumber] = strval(Field);
	db_get_field_assoc(db_result, "Helmet", Field, sizeof(Field) );   PlayerInfo[playerid][pHelmet] = strval(Field);
	
	db_get_field_assoc(db_result, "SlotItem0", Field, sizeof(Field) );   PlayerInfo[playerid][pOther][11] = strval(Field);
	db_get_field_assoc(db_result, "SlotItem1", Field, sizeof(Field) );   PlayerInfo[playerid][pOther][12] = strval(Field);
	db_get_field_assoc(db_result, "SlotItem2", Field, sizeof(Field) );   PlayerInfo[playerid][pOther][13] = strval(Field);
	db_get_field_assoc(db_result, "SlotItem3", Field, sizeof(Field) );   PlayerInfo[playerid][pOther][14] = strval(Field);
	db_get_field_assoc(db_result, "SlotItem4", Field, sizeof(Field) );   PlayerInfo[playerid][pOther][15] = strval(Field);
	db_get_field_assoc(db_result, "SlotItem5", Field, sizeof(Field) );   PlayerInfo[playerid][pOther][16] = strval(Field);


	db_get_field_assoc(db_result, "Married", Field, sizeof(Field) );   PlayerInfo[playerid][pMarried] = strval(Field);
	db_get_field_assoc(db_result, "MarriedTo", PlayerInfo[playerid][pMarriedTo], sizeof(Field) );
//db_get_field_assoc(db_result, "Offline", Field, sizeof(Field) );   PlayerInfo[playerid][pOffline] = strval(Field);//не загружать, т.к. при входе он инициализируется
	db_get_field_assoc(db_result, "Reason", Field, sizeof(Field) );   	PlayerInfo[playerid][pReason] = strval(Field);
	db_get_field_assoc(db_result, "CarTime", Field, sizeof(Field) );   PlayerInfo[playerid][pCarTime] = strval(Field);
	db_get_field_assoc(db_result, "Tutorial", Field, sizeof(Field) );   PlayerInfo[playerid][pTut] = strval(Field);
	db_get_field_assoc(db_result, "Vote", Field, sizeof(Field) );   	PlayerInfo[playerid][pVote] = strval(Field);
	db_get_field_assoc(db_result, "PurposeMurder", Field, sizeof(Field) );   PlayerInfo[playerid][pPurposeMurder] = strval(Field);
	db_get_field_assoc(db_result, "Referal", PlayerInfo[playerid][pReferal], sizeof(Field) );
	//db_get_field_assoc(db_result, "Passport", Field, sizeof(Field) );   	PlayerInfo[playerid][pPassport] = strval(Field);
	db_get_field_assoc(db_result, "Online", Field, sizeof(Field) );   	PlayerInfo[playerid][pOnline] = strval(Field);
	db_get_field_assoc(db_result, "Score", Field, sizeof(Field) );   	PlayerInfo[playerid][pScore] = strval(Field);

	db_get_field_assoc(db_result, "Param1", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam1] = strval(Field);
	db_get_field_assoc(db_result, "Param2", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam2] = strval(Field);
	db_get_field_assoc(db_result, "Param3", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam3] = strval(Field);
	db_get_field_assoc(db_result, "Param4", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam4] = strval(Field);
	db_get_field_assoc(db_result, "Param5", Field, sizeof(Field) );   	PlayerInfo[playerid][pParam5] = strval(Field);

	//PlayerInfo[playerid][pTut] = 0;
	db_free_result(db_result);

    new strtmp[MAX_STRING];
	format(strtmp, sizeof(strtmp), "OnPlayerLoadParameters(player:%s[%d])", nameplayer, playerid);
	print(strtmp);

	//ИНФОРМИРОВАНИЕ
	/*if(!IsPlayerConnected(playerid))
	{
	    //new strings[MAX_STRING];
		format(strings, sizeof(strings), "OnPlayerLoadParameters(offline player:%s[%d])", nameplayer, playerid);
		print(strings);
		Log(OFFLINE, strings);

	}*/
	return 1;
}




stock sql_OnPlayerDisconnect(playerid)
{
	//для монитора
	PlayerInfo[playerid][pOffline] = getdate();//записали день выхода с серва
//TestLog(OPTIM, "OnPlayerDisconnect1.1", GetTickCount(), timers, 1);
	new ToBase[87];//60 + 3+24 = 87
    if(PlayerInfo[playerid][pSQLID] > 0)
    {
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `ID`=%d",
			PlayerInfo[playerid][pOffline], PlayerInfo[playerid][pSQLID]);
	}
	else
	{
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `Name`='%s'",
			PlayerInfo[playerid][pOffline], PlayerName(playerid));
	}
	db_free_result(db_query(db_VW, ToBase));
}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
stock OnPlayerStatsUpdate(playerid, reason=-1)//вызывается из
{//OnPlayerDisconnect, GameModeInitExitFunc, dialogid==17, PerformingTheContract, MakeLeader
//если игрок выходит и сразу под его ID въходит другой, то при лагах может быть неправильная перезапись
/*
case 0: Timed out
case 1: Leaving
case 2: Kicked/Banned
остальные просто сохранение
*/
	//if(TEST[MAX_FUNCTION-1] == 1)  return 1;
	new timers = GetTickCount();
	//==========================================================================
	if(!IsPlayerConnected(playerid))  return 1;
	if(IsPlayerNPC(playerid))  return 1;
	if(!gPlayerLogged[playerid])  return 1;
	//if(!gPlayerSpawned[playerid]) return 1; //будут выходить с серва когда в состоянии мертв

	if( !IsValidSkin(PlayerInfo[playerid][pModel]) ) PlayerInfo[playerid][pModel] = SKIN_DEFAULT;

	PlayerInfo[playerid][pReason] = reason;

	PlayerInfo[playerid][pHealth] = LastHealth[playerid];

	PlayerInfo[playerid][pLocal] = FREEROAM;
	if(gInDerbyBloodBowl[playerid])//для дерби BloodBowl STEP10
	{   //если игрок в дерби вышел из игры
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pPos_x] = -2119.5925;
		PlayerInfo[playerid][pPos_y] = -443.8909;
		PlayerInfo[playerid][pPos_z] = 35.5313;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		PlayerInfo[playerid][pVirtual] = 0;
	}
	else if(gInDerby8ball[playerid])//для дерби 8ball STEP10
	{   //если игрок в дерби вышел из игры
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pPos_x] = 2728.0933;
		PlayerInfo[playerid][pPos_y] = -1834.9763;
		PlayerInfo[playerid][pPos_z] = 10.3494;
		PlayerInfo[playerid][pLocal] = FREEROAM;
		PlayerInfo[playerid][pVirtual] = 0;
	}
	if(spectateid[playerid] != MAX_PLAYERS-1 && gPlayerLogged[playerid])//если зритель
	{   //если игрок вышел из игры в режиме зрителя
		PlayerInfo[playerid][pInt] = Unspec[playerid][sInt];
		PlayerInfo[playerid][pPos_x] = Unspec[playerid][sPx];
		PlayerInfo[playerid][pPos_y] = Unspec[playerid][sPy];
		PlayerInfo[playerid][pPos_z] = Unspec[playerid][sPz];
		PlayerInfo[playerid][pLocal] = Unspec[playerid][sLocal];
		PlayerInfo[playerid][pVirtual] = Unspec[playerid][sVirtual];
	}
	else if(TeleportDetected[playerid] == 0 && gPlayerSpawned[playerid] && gPlayerLogged[playerid]
		&& CurInt[playerid] == 0)
	{   //если античит телепортов не засек
	    //при рестарте позиция равна нулю
	    //GetPlayerPos(playerid, PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z]);

	    //PlayerInfo[playerid][pInt] = GetPlayerInterior(playerid);
	    //PlayerInfo[playerid][pVirtual] = GetPlayerVirtualWorld(playerid);
		//PlayerInfo[playerid][pInt] = CurInt[playerid];
		PlayerInfo[playerid][pPos_x] = CurPos[0][playerid];
		PlayerInfo[playerid][pPos_y] = CurPos[1][playerid];
		PlayerInfo[playerid][pPos_z] = CurPos[2][playerid];
	}
	if(GameRestart != 1)//для сохранения при обычном выходе
	{   //ВНИМАНИЕ: нельзя сохранять при рестарте мода
	    //GetPlayerPos только
		/*if(gPlayerSpawned[playerid] == 1)
		{   //перезаписывает PlayerInfo[playerid][pInt] часто в 0
			PlayerInfo[playerid][pInt] = GetPlayerInterior(playerid);
			PlayerInfo[playerid][pVirtual] = GetPlayerVirtualWorld(playerid);
			//PlayerInfo[playerid][pLocal] = PlayerInfo[playerid][pLocal];
			GetPlayerPos(playerid, PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z]);
		}*/
		//для сохранения оружия
		//Вариант 2
		PlayerInfo[playerid][pGun1] = 0; PlayerInfo[playerid][pAmmo1] = 0;
		PlayerInfo[playerid][pGun2] = 0; PlayerInfo[playerid][pAmmo2] = 0;
		PlayerInfo[playerid][pGun3] = 0; PlayerInfo[playerid][pAmmo3] = 0;
		PlayerInfo[playerid][pGun4] = 0; PlayerInfo[playerid][pAmmo4] = 0;
		for(new weaponid = 22; weaponid <= 32; weaponid++)//MAX_WEAPONS
		{   //сканируем всё огнестрельное оружие
			if(LastAmmo[playerid][weaponid] > 0 && LastAmmo[playerid][weaponid] < 1000)
			{   //записываем те виды в которых есть патроны
				//по тем пушкам что есть в слотах
				new slot = GetWeaponSlot(weaponid);
				if(slot == 2 && LastWeaponInSlot[playerid][slot] == weaponid)
				{ PlayerInfo[playerid][pGun1] = weaponid; PlayerInfo[playerid][pAmmo1] = LastAmmo[playerid][weaponid]; }
				else if(slot == 3 && LastWeaponInSlot[playerid][slot] == weaponid)
				{ PlayerInfo[playerid][pGun2] = weaponid; PlayerInfo[playerid][pAmmo2] = LastAmmo[playerid][weaponid]; }
				//если пуха принадлежит слоту 2 и в этом слоте куплен дробовик
				else if(slot == 4 && LastWeaponInSlot[playerid][slot] == weaponid)
				{ PlayerInfo[playerid][pGun3] = weaponid; PlayerInfo[playerid][pAmmo3] = LastAmmo[playerid][weaponid]; }
				else if(slot == 5 && LastWeaponInSlot[playerid][slot] == weaponid)
				{ PlayerInfo[playerid][pGun4] = weaponid; PlayerInfo[playerid][pAmmo4] = LastAmmo[playerid][weaponid]; }
			}
		}
	}
	//--------------------------------------------------------------------------
	new BuyPrice;//для подсчёта стоимости имущества и определения уровня игрока
//printf("1.carid: %d modelid: %d", MyCar[playerid][0], VehInfo[MyCar[playerid][0]][cModel] );
//printf("2.carid: %d modelid: %d", MyCar[playerid][1], GetVehicleModel(MyCar[playerid][1]) );
//printf("3.carid: %d modelid: %d", MyCar[playerid][2], GetVehicleModel(MyCar[playerid][2]) );
	for(new limit = 0; limit < 3; limit++)
	{
		if(MyCar[playerid][limit] != 0)
		{
			new carid = MyCar[playerid][limit];
//printf("carid: %d", carid);
			new modelid = VehInfo[carid][cModel];//GetVehicleModel(carid)
			if(modelid < 400) continue; //пропускаем не существуеющие тачки
//printf("modelid: %d", modelid);
			BuyPrice += VehicleArray[modelid-400][Virtual_Price];
		}
	}
//print("5");
	//if(PlayerInfo[playerid][pHouse] >= 0 && PlayerInfo[playerid][pHouse] < MAX_HOUSE)
	//{
	for(new limit = 0; limit < 5; limit++)
	{
		if(MyHouse[playerid][limit] == NOT_KEY) continue;
		new house = MyHouse[playerid][limit];
//printf("house: %d", house);
		BuyPrice += HouseInfo[house][hTill];
		BuyPrice += HouseInfo[house][hBuyPrice];
	}
	//}
	for(new limit = 0; limit < 10; limit++)
	{
		if(MyBizz[playerid][limit] == NOT_KEY) continue;
		new bouse = MyBizz[playerid][limit];
//printf("bouse: %d", bouse);
		BuyPrice += BizInfo[bouse][bTill];
		BuyPrice += BizInfo[bouse][bBuyPrice];
	}
	for(new limit = 0; limit < 20; limit++)
	{
		if(MyCompany[playerid][limit] == NOT_KEY) continue;
		new sbouse = MyCompany[playerid][limit];
//printf("sbouse: %d", sbouse);
		BuyPrice += SBizInfo[sbouse][sbTill];
		BuyPrice += SBizInfo[sbouse][sbBuyPrice];
	}
	GetPlayerScoreBuyPrice(playerid, BuyPrice, 0);

	if(reason == 0 || reason == 2)
	{//для монитора
		PlayerInfo[playerid][pOffline] = getdate();
		PlayerInfo[playerid][pReason] = reason;
	}
	//--------------------------------------------------------------------------
	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));
	//if(reason == 1)//иначе не будет сохраняться при /logoutall а будут только при выходе
	OnPlayerSaveParameters(playerid, playername);//   OnPlayerSaveTempParameters(playerid, playername);


	new strtmp[75];//38+24+10+1 = 73
	format(strtmp, sizeof(strtmp), "OnPlayerStatsUpdate %s[%d] reason: %d", playername, PlayerInfo[playerid][pSQLID], reason);
	SendClientMessage(playerid, COLOR_YELLOW, strtmp);
	TestLog(OPTIM, strtmp, GetTickCount(), timers);
	return 1;
}//end OnPlayerStatsUpdate(playerid)


stock OnPlayerSaveParameters(playerid, nameplayer[])//вызывается из OnPlayerDisconnect GameModeInitExitFunc OnPlayerStatsUpdate
{   //ф-ция сохранения параметров игрока
	new timers = GetTickCount();
//Origin=%d,
	new ToBase[2724];//468+518+542+345+14+25+16+16+16 + 164+505+3*5+24+6+6+3+6+6 + 12 + 12+1+4 = 2724
	format(ToBase, sizeof(ToBase), "UPDATE `players` SET `IP`='%s',\
Sex=%d,\
Age='%s',\
DepositDay=%d,\
Level=%d,\
AdminLevel=%d,\
Account=%d,\
Muted=%d,\
Warns=%d,\
ConnectTime=%d,\
Respect=%d,\
RespectDay=%d,\
PayCheck=%d,\
PayDay=%d,\
Deposit=%d,\
Cash=%d,\
Bank=%d,\
SHealth=%.1f,\
Health=%.1f,\
Interior=%d,\
Pos_x=%.1f,\
Pos_y=%.1f,\
Pos_z=%.1f,\
Virtual=%d,\
Local=%d,\
House=%d,\
Bizz=%d,\
Job=%d,\
Team=%d,\
Member=%d,\
Leader=%d,\
Rank=%d,\
`Char`=%d,\
`Model`=%d",
	PlayerInfo[playerid][pIP],
	//serialid,
	PlayerInfo[playerid][pSex],
	PlayerInfo[playerid][pAge],
	//PlayerInfo[playerid][pOrigin],
	PlayerInfo[playerid][pDepositDay],
	PlayerInfo[playerid][pLevel],
	PlayerInfo[playerid][pAdmin],
	PlayerInfo[playerid][pAccount],
	PlayerInfo[playerid][pMuted],
	PlayerInfo[playerid][pWarns],
	PlayerInfo[playerid][pConnectTime],
	PlayerInfo[playerid][pRespect],
	PlayerInfo[playerid][pRespectDay],
	PlayerInfo[playerid][pPayCheck],
	PlayerInfo[playerid][pPayTime],
	PlayerInfo[playerid][pDeposit],
	PlayerInfo[playerid][pCash],
	PlayerInfo[playerid][pBank],
	PlayerInfo[playerid][pSHealth],
	PlayerInfo[playerid][pHealth],
	PlayerInfo[playerid][pInt],
	PlayerInfo[playerid][pPos_x],
	PlayerInfo[playerid][pPos_y],
	PlayerInfo[playerid][pPos_z],
	PlayerInfo[playerid][pVirtual],
	PlayerInfo[playerid][pLocal],
	PlayerInfo[playerid][pHouse],
	PlayerInfo[playerid][pBizz],
	PlayerInfo[playerid][pJob],
	PlayerInfo[playerid][pTeam],
	PlayerInfo[playerid][pMember],
	PlayerInfo[playerid][pLeader],
	PlayerInfo[playerid][pRank],
	PlayerInfo[playerid][pChar],
	PlayerInfo[playerid][pModel]);

	format(ToBase, sizeof(ToBase), "%s,ContractTime=%d,\
MinerSkill=%d,\
LawSkill=%d,\
RoadSkill=%d,\
DrugsSkill=%d,\
JackSkill=%d,\
ProfSkill=%d,\
MechSkill=%d,\
FarmSkill=%d,\
GunSkill=%d,\
CarSkill=%d,\
InkasSkill=%d,\
BookmakerSkill=%d,\
TaxiSkill=%d,\
BusSkill=%d,\
CourierSkill=%d,\
TruckSkill=%d,\
TrashSkill=%d,\
LoadSkill=%d,\
WoodSkill=%d,\
FishSkill=%d,\
FireSkill=%d,\
CookSkill=%d",
	ToBase,
	PlayerInfo[playerid][pContractTime],
	PlayerInfo[playerid][pMinerSkill],
	PlayerInfo[playerid][pLawSkill],
	PlayerInfo[playerid][pRoadSkill],
	PlayerInfo[playerid][pDrugsSkill],
	PlayerInfo[playerid][pJackSkill],
	PlayerInfo[playerid][pProfSkill],
	PlayerInfo[playerid][pMechSkill],
	PlayerInfo[playerid][pFarmSkill],
	PlayerInfo[playerid][pGunSkill],
	PlayerInfo[playerid][pCarSkill],
	PlayerInfo[playerid][pInkasSkill],
	PlayerInfo[playerid][pBookmakerSkill],
	PlayerInfo[playerid][pTaxiSkill],
	PlayerInfo[playerid][pBusSkill],
	PlayerInfo[playerid][pCourierSkill],
	PlayerInfo[playerid][pTruckSkill],//16 для дальнобойщиков
	PlayerInfo[playerid][pTrashSkill],
	PlayerInfo[playerid][pLoadSkill],
	PlayerInfo[playerid][pWoodSkill],
	PlayerInfo[playerid][pFishSkill],//17
	PlayerInfo[playerid][pFireSkill],
	PlayerInfo[playerid][pCookSkill]);

	format(ToBase, sizeof(ToBase), "%s,CarLic=%d,\
BikeLic=%d,\
FlyLic=%d,\
BoatLic=%d,\
FishLic=%d,\
GunLic=%d,\
Gun1=%d,\
Ammo1=%d,\
Gun2=%d,\
Ammo2=%d,\
Gun3=%d,\
Ammo3=%d,\
Gun4=%d,\
Ammo4=%d",
	ToBase,
	PlayerInfo[playerid][pCarLic],
	PlayerInfo[playerid][pBikeLic],//лицензия на мото
	PlayerInfo[playerid][pFlyLic],
	PlayerInfo[playerid][pBoatLic],
	PlayerInfo[playerid][pFishLic],
	PlayerInfo[playerid][pGunLic],
	PlayerInfo[playerid][pGun1],
	PlayerInfo[playerid][pAmmo1],
	PlayerInfo[playerid][pGun2],
	PlayerInfo[playerid][pAmmo2],
	PlayerInfo[playerid][pGun3],
	PlayerInfo[playerid][pAmmo3],
	PlayerInfo[playerid][pGun4],
	PlayerInfo[playerid][pAmmo4]);

	new Perks[21+10];
	format(Perks, sizeof(Perks), "%d%d%d%d%d%d%d%d%d%d",
		PlayerInfo[playerid][pAlcoholPerk],
		PlayerInfo[playerid][pDrugPerk],
        PlayerInfo[playerid][pMiserPerk],
        PlayerInfo[playerid][pPainPerk],
        PlayerInfo[playerid][pTraderPerk],
		PlayerInfo[playerid][pHunger],//АнтиГолод
		PlayerInfo[playerid][pLeisure],//АнтиДосуг
		PlayerInfo[playerid][pContact],//АнтиОбщение
		PlayerInfo[playerid][pToilet],//АнтиТуалет
		PlayerInfo[playerid][pVigour]//АнтиБодрость
		);
/*print(tmp_str);
printf("%d%d%d%d%d00000",
		PlayerInfo[playerid][pAlcoholPerk],
		PlayerInfo[playerid][pDrugPerk],
        PlayerInfo[playerid][pMiserPerk],
        PlayerInfo[playerid][pPainPerk],
        PlayerInfo[playerid][pTraderPerk]);*/
/*AlcoholPerk=%d,\
DrugPerk=%d,\
MiserPerk=%d,\
PainPerk=%d,\
TraderPerk=%d,\
*/

	format(ToBase, sizeof(ToBase), "%s,Gun22Skill=%d,\
Gun23Skill=%d,\
Gun24Skill=%d,\
Gun25Skill=%d,\
Gun26Skill=%d,\
Gun27Skill=%d,\
Gun28Skill=%d,\
Gun29Skill=%d,\
Gun30Skill=%d,\
Gun31Skill=%d,\
Gun34Skill=%d,\
HeadValue=%d,\
Wins=%d,\
Loses=%d,\
Kills=%d,\
Deaths=%d,\
Accident=%d,\
Ticket=%d,\
Crimes=%d,\
Arrested=%d,\
WantedDeaths=%d,\
Wanted=%d,\
Article=%d,\
Part=%d,\
Jailed=%d,\
JailTime=%d,\
JailPrice=%d,\
UpgradePoints=%d,\
Perks='%s',\
STD=%d",
	ToBase,
	PlayerInfo[playerid][pGun22Skill],
	PlayerInfo[playerid][pGun23Skill],
	PlayerInfo[playerid][pGun24Skill],
	PlayerInfo[playerid][pGun25Skill],
	PlayerInfo[playerid][pGun26Skill],
	PlayerInfo[playerid][pGun27Skill],
	PlayerInfo[playerid][pGun28Skill],
	PlayerInfo[playerid][pGun29Skill],
	PlayerInfo[playerid][pGun30Skill],
	PlayerInfo[playerid][pGun31Skill],
	PlayerInfo[playerid][pGun34Skill],
	PlayerInfo[playerid][pHeadValue],
	PlayerInfo[playerid][pWins],
	PlayerInfo[playerid][pLoses],
	PlayerInfo[playerid][pKills],
	PlayerInfo[playerid][pDeaths],
	PlayerInfo[playerid][pAccident],
	PlayerInfo[playerid][pTicket],
	PlayerInfo[playerid][pCrimes],
	PlayerInfo[playerid][pArrested],
	PlayerInfo[playerid][pWantedDeaths],
	WantedPoints[playerid],
	PlayerInfo[playerid][pArticle],
	PlayerInfo[playerid][pPart],
	PlayerInfo[playerid][pJailed],
	PlayerInfo[playerid][pJailTime],
	PlayerInfo[playerid][pJailPrice],
	PlayerInfo[playerid][pPupgrade],
	Perks,
	PlayerInfo[playerid][pSTD]);

	if(PlayerInfo[playerid][pDice] > 9 || PlayerInfo[playerid][pDice] < 0) PlayerInfo[playerid][pDice] = 0;
	if(PlayerInfo[playerid][pCigars] > 9 || PlayerInfo[playerid][pCigars] < 0) PlayerInfo[playerid][pCigars] = 0;
	if(Groceries[playerid][gBeer] > 9 || Groceries[playerid][gBeer] < 0) Groceries[playerid][gBeer] = 0;
	if(Groceries[playerid][gChickens] > 9 || Groceries[playerid][gChickens] < 0) Groceries[playerid][gChickens] = 0;
	if(Groceries[playerid][gHamburgers] > 9 || Groceries[playerid][gHamburgers] < 0) Groceries[playerid][gHamburgers] = 0;
	if(Groceries[playerid][gPizzas] > 9 || Groceries[playerid][gPizzas] < 0) Groceries[playerid][gPizzas] = 0;
	if(PlayerInfo[playerid][pFishes] > 9 || PlayerInfo[playerid][pFishes] < 0) PlayerInfo[playerid][pFishes] = 0;
	if(PlayerInfo[playerid][pAdrenalin] > 9 || PlayerInfo[playerid][pAdrenalin] < 0) PlayerInfo[playerid][pAdrenalin] = 0;

/*
	if(Fishes[playerid][pWeight][0] > 0) PlayerInfo[playerid][pFishes] ++;
	else if(Fishes[playerid][pWeight][1] > 0) PlayerInfo[playerid][pFishes] ++;
	else if(Fishes[playerid][pWeight][2] > 0) PlayerInfo[playerid][pFishes] ++;
	else if(Fishes[playerid][pWeight][3] > 0) PlayerInfo[playerid][pFishes] ++;
	else if(Fishes[playerid][pWeight][4] > 0) PlayerInfo[playerid][pFishes] ++;
*/

	new PlayerItems[21+11];
	format(PlayerItems, sizeof(PlayerItems), "%d%d%d%d%d%d%d%d%d%d",
		PlayerInfo[playerid][pDice],
		PlayerInfo[playerid][pCigars],
		Groceries[playerid][gChickens],
		Groceries[playerid][gHamburgers],
		Groceries[playerid][gPizzas],
		PlayerInfo[playerid][pFishes],
		PlayerInfo[playerid][pAdrenalin],
		Groceries[playerid][gBeer],
		0,
		0);

	if(PlayerInfo[playerid][pAntiradar] > 9 || PlayerInfo[playerid][pAntiradar] < 0) PlayerInfo[playerid][pAntiradar] = 0;
	if(PlayerInfo[playerid][pGPS] > 9 || PlayerInfo[playerid][pGPS] < 0) PlayerInfo[playerid][pGPS] = 0;
	if(PlayerInfo[playerid][pCDPlayer] > 9 || PlayerInfo[playerid][pCDPlayer] < 0) PlayerInfo[playerid][pCDPlayer] = 0;
	if(PlayerInfo[playerid][pFuel] > 9 || PlayerInfo[playerid][pFuel] < 0) PlayerInfo[playerid][pFuel] = 0;

   	new VehicleItems[21+11];
	format(VehicleItems, sizeof(VehicleItems), "%d%d%d%d000000",
		PlayerInfo[playerid][pAntiradar],
		PlayerInfo[playerid][pGPS],
		PlayerInfo[playerid][pCDPlayer],
		PlayerInfo[playerid][pFuel]);

//BiggestFish=%d,
//Antiradar=%d,
//GPS=%d,
//CDPlayer=%d,
//Dice=%d,
//Cigars=%d,
//Fuel=%d,
//Fishes=%d,


	format(ToBase, sizeof(ToBase), "%s,PlayerItems='%s',VehicleItems='%s',\
Drugs=%d,\
LottoNr=%d,\
Materials=%d,\
Mushroom=%d,\
PhoneNr=%d,\
Helmet=%d,\
Married=%d,\
MarriedTo='%s',\
`Offline`=%d,\
Reason=%d,\
CarTime=%d,\
Tutorial=%d,\
Vote=%d,\
PurposeMurder=%d,\
Referal='%s',\
Score=%d,\
Param1=%d,\
Param2=%d,\
Param3=%d,\
Param4=%d,\
Param5=%d",
	ToBase,
	PlayerItems,VehicleItems,
	//PlayerInfo[playerid][pAntiradar],
	//PlayerInfo[playerid][pGPS],
	//PlayerInfo[playerid][pCDPlayer],
	//PlayerInfo[playerid][pDice],
	PlayerInfo[playerid][pDrugs],
	//PlayerInfo[playerid][pCigars],
	//PlayerInfo[playerid][pFishes],
	//PlayerInfo[playerid][pFuel],
	PlayerInfo[playerid][pLottoNr],
	PlayerInfo[playerid][pMats],
	PlayerInfo[playerid][pMushroom],
	PlayerInfo[playerid][pPnumber],
	PlayerInfo[playerid][pHelmet],
	PlayerInfo[playerid][pMarried],
	PlayerInfo[playerid][pMarriedTo],
	PlayerInfo[playerid][pOffline],
	PlayerInfo[playerid][pReason],
	PlayerInfo[playerid][pCarTime],
	PlayerInfo[playerid][pTut],
	PlayerInfo[playerid][pVote],
	PlayerInfo[playerid][pPurposeMurder],
	PlayerInfo[playerid][pReferal],
	PlayerInfo[playerid][pScore],
	PlayerInfo[playerid][pParam1],
	PlayerInfo[playerid][pParam2],
	PlayerInfo[playerid][pParam3],
	PlayerInfo[playerid][pParam4],
	PlayerInfo[playerid][pParam5]);

	if(PlayerInfo[playerid][pSQLID] > 0)
	{//если получен уникальный ИД из базы, то сохранять по нему
		format(ToBase, sizeof(ToBase), "%s WHERE `ID`=%d", ToBase, PlayerInfo[playerid][pSQLID]);
	}
	else
	{//иначен сохранять по нику, для неиграющих
		format(ToBase, sizeof(ToBase), "%s WHERE `Name`='%s'", ToBase, nameplayer);
	}
	db_free_result(db_query(db_VW, ToBase));

	new strtmp[64];//30+24+10 = 64
	format(strtmp, sizeof(strtmp), "OnPlayerSaveParameters %s[%d] ip:%s", nameplayer, PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pIP]);
	print(strtmp);
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();
	if(PlayerInfo[playerid][pAdmin] >= 6) SendClientMessage(playerid, COLOR_YELLOW, strtmp);

	format(strtmp, sizeof(strtmp), "Int:%d, Virt:%d, Loc:%d, X:%.1f, Y:%.1f, Z:%.1f",
		PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual],	PlayerInfo[playerid][pLocal],
		PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
		//CurPos[0][playerid], CurPos[1][playerid], CurPos[2][playerid]);
	if(PlayerInfo[playerid][pAdmin] >= 6) SendClientMessage(playerid, COLOR_YELLOW, strtmp);
	return 1;
}

//##############################################################################//





// prevent sql injection: [url]http://wiki.sa-mp.com/wiki/Escaping_Strings_SQLite[/url]
#define MAX_INI_ENTRY_TEXT 80
stock DB_Escape(text[])
{
    new
        ret[MAX_INI_ENTRY_TEXT * 2],
        ch,
        i,
        j;
    while ((ch = text[i++]) && j < sizeof (ret))
    {
        if (ch == '\'')
        {
            if (j < sizeof (ret) - 2)
            {
                ret[j++] = '\'';
                ret[j++] = '\'';
            }
        }
        else if (j < sizeof (ret))
        {
            ret[j++] = ch;
        }
        else
        {
            j++;
        }
    }
    ret[sizeof (ret) - 1] = '\0';
    return ret;
}
