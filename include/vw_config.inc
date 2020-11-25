//тут все настройки: переходы в интерьеры, точки спауна
new DB: db_VW; // Handle for database. Our queries need to use this so the queries know where to handle things

new CREATOR[] = "Danger_Hidden";
new SERVERNAME[] = "VirtualWorld";//то что пишет в видеоролике и некоторых диалогах
new HostName[] = "localhost";//откуда будут подгружаться звуки и загружаться скрипты
new FORUM[] = "http://strikearena.ru/forums/359-gtasa-virtual-world-server/";
new GMText[] = "LifeSimulator";//название мода с добавлением версии

#if defined LOCAL
	#define MAIL "mail.ru"
	#define IP_ADRESS "127.0.0.1"//ип-адресс сервера
	#define PORT "7777"//порт сервера
	new php_host[] = "localhost";
	//new root_pass[] = "MN6zfHufnfJtm3QW";//пароль для опасных админских команд //пароль для управления сервером
	//не более 20 символов
#endif

new ANTICHEAT = 0;
new ANTISPEEDHACK = 0;
new ANTITELEPORT = 0;
new CHEATLIM = 5;
new ANTIMONEY = 1;
new ANTIHEALTH = 0;
new ANTIVEHHEALTH = 0;
new ANTIGODMOD = 0;
new ANTIGUN = 0;
new UNFREEZE = 0;
new ANTISWEER = 0;
new ANTIFLOOD = 0;
new FLOODLIM = 5;
new PINGS = 150;
new AFK = 0;
new ESCSEC = 900;//300 //допускается секунд афк
new WEATHCHANGE = 10;//5//минут
new CARSPAWN = 30;//минут  60000;

new Jackpot = 1000;
new CriminalLevel = 400;
new TAX;//казна
new TaxValue = 1;
new Security = 0;
new TimeTakeZone = 300;//время захвата зоны по умолчанию
new gCheckProp = 7;//0- выключена, для выключения проверки собственности при отсутствии в игре
new qTime = 30;
new HUNGER = 0;
new IdleKick = 0;
new LOGS = 1;//1 - разрешить логирование
new gTesting = 0;
new ReconnectDelay = 5;//120;

new Float: FuelCost = 0.7;//цена за литр
new compcost = 10;//10 стоимость продуктов для бизов
new AntiDB = 1;
new AntiBH = 1;
new AntiDM = 1;
new gCheckOnline = 1;
new gRealWar = 0;//1//не работает, т.к. загрузка из базы меняет значение

new StatusJob[20];


new countrace = 0;//счётчик кол-ва загруженных гонок racecountdown

new PagerMessage[142];//87+2+2+4+20+24+3 = 142
//##############################################################################
//#define LOCAL //локальный сервер
//##############################################################################


//##############################################################################//
//                                                                              //
//                              НАСТРОЙКИ СЕРВЕРА                               //
//                                                                              //
//##############################################################################//
//которые меняют под каждый сервер индивидуально

#define BANTIME 		2
#define SKIN_DEFAULT	26//78//264
#define SOC_PACKET 		166//MAX_PLAYERS-4;//170-4
#define QUIT_JOB 		167//MAX_PLAYERS-3;
#define SELLGUN 		167//MAX_PLAYERS-3;

//для дальнобойщиков и др.
new Float: CHECKPOINT_SIZE = 4.0;//надо чтобы всегда был меньше проверяемого радиуса в IsPlayerInRangeOfPoint(playerid, 5.0,
new gTogNameTag = 1;//1 - ники включены
new Float: stream_distance = 300.0;

new idletime = 30; //время неперемещения в минутах, было 15 mins

//для экономики
//new levelcost = 2500;//25000 цена уровня



//new gClock = 1;//для часиков

//new DestroyDate = 15;//время жизни тачки


//временные настройки
//new ANIMATION = 0;
//new KEYSTATE = 0;
//new TRAILER = 0;//выводит сообщение из самапального паблика
//new HEALTH = 0;//выводит сообщения по здоровью игрока каждую секунду
//new CAMERA = 0;
//new consuption_fuel = 15;//для расхода топлива, чем ниже цыфра, тем больше расход

//##############################################################################//
//                                                                              //
//                     ОПРЕДЕЛЕНИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ                        //
//                                                                              //
//##############################################################################//
new Float: NameTagDrawDistance = 60.0;

//для чата
//new gRealChat = 1;//местный чат включен
//new gOffGeneralChat = 1;//общий чата включен
#define chat_radius 8.0

//для времени
new gRrealTime = 1;//реальное время
new timeshift = 0;//-1 - чтобы темнело на 1 час позже летом//3 - чтобы темнело на 3 часа раньше зимой
//new shifthour = 1;//скоректированый час
new wtime = 15;//времмя рестарта сервера
new ghour;//хранит предыдущий час, инициализируется при загрузке мода
new LastDay;//new gday;//хранит предыдущий день, инициализируется при загрузке мода
//, gminute, gsecond;//для синхронизации времени


new ChangeWeath;//таймер смены погоды

//##############################################################################//
//                                                                              //
//                                  СЧЁТЧИКИ                                    //
//                                                                              //
//##############################################################################//

//для проверки ограничения
new PingCount[MAX_PLAYERS];//счётчик кол-ва срабатываний при превышении пинга

new GetMaxVehicles = 1;//максимальный ИД тачек в игре
new LoadCarCounter = 0;//счетчик добавленного транспорта при старте мода
new VehiclesCounter; //общий счётчик загруженных машин
new CreatedCarCounter;//счётчик созданных тачек в процессе игры
new VehiclesModelsCounter = 0;//счётчик моделей
new aExistModel[MAX_VEHICLES+1];//все существующие модели

new CreateObjectCounter = 0;//счётчик объектов
new CreatePlayerObjectCounter[MAX_PLAYERS];//счётчик объектов
new RemoveBuildingCounter[MAX_PLAYERS];//счётчик объектов

new ActorCounter = 0;//счётчик актёров

new PickupCounter = 0;//счетчик загруженых пикапов

new TEXT_DRAWS_COUNTER;//счётчик загруженных текстдров
new PLAYER_TEXT_DRAWS_COUNTER[MAX_PLAYERS];//счётчик загруженных текстдров

new Counter3DText = 0;//счётчик 3Д текстов
new LabelPlayerCounter[MAX_PLAYERS];//счётчик Player3д текстов
//##############################################################################//

stock LoadSettings()//для загрузки настроек
{
	new time = GetTickCount();
	if( !fexist("Logs/settings.ini") ) { SaveSettings(); return 1; }
	new File: sFile = fopen("Logs/settings.ini", io_read);
	if( !sFile ) { return 1; }
    new key[256+1], val[256+1], Line[256+1];
	while( fread(sFile, Line, sizeof(Line)) )
	{//Чтение файла до тех пор пока в нем есть строки:
		key = ini_GetKey(Line);

		if(!strcmp(key, "CREATOR", true)) { val = ini_GetValue( Line ); strmid(CREATOR, val, 0, strlen(val), MAX_PLAYER_NAME); }
		if(!strcmp(key, "SERVERNAME", true)) { val = ini_GetValue( Line ); strmid(SERVERNAME, val, 0, strlen(val), sizeof(val)); }
		//if(!strcmp(key, "SERVERNAME", true)) { val = ini_GetValue( Line ); strcat(SERVERNAME, val); }
		
		if(!strcmp(key, "HOSTNAME", true)) { val = ini_GetValue( Line ); strmid(HostName, val, 0, strlen(val), sizeof(val)); }
		if(!strcmp(key, "FORUM", true)) { val = ini_GetValue( Line ); strmid(FORUM, val, 0, strlen(val), sizeof(val)); }
		if(!strcmp(key, "GMText", true)) { val = ini_GetValue( Line ); strmid(GMText, val, 0, strlen(val), sizeof(val)); }

		if(!strcmp(key, "AntiCheat", true)) { val = ini_GetValue( Line ); ANTICHEAT=strval(val); }
		if(!strcmp(key, "AntiSpeedHack", true)) { val = ini_GetValue( Line ); ANTISPEEDHACK=strval(val); }
		if(!strcmp(key, "AntiTeleport", true)) { val = ini_GetValue( Line ); ANTITELEPORT=strval(val); }
		if(!strcmp(key, "CheatLim", true)) { val = ini_GetValue( Line ); CHEATLIM=strval(val); }
		if(!strcmp(key, "AntiMoney", true)) { val = ini_GetValue( Line ); ANTIMONEY=strval(val); }
		if(!strcmp(key, "AntiHealth", true)) { val = ini_GetValue( Line ); ANTIHEALTH=strval(val); }
		if(!strcmp(key, "AntiVehHealth", true)) { val = ini_GetValue( Line ); ANTIVEHHEALTH=strval(val); }
		if(!strcmp(key, "AntiGodMod", true)) { val = ini_GetValue( Line ); ANTIGODMOD=strval(val); }
		if(!strcmp(key, "AntiGun", true)) { val = ini_GetValue( Line ); ANTIGUN=strval(val); }
		if(!strcmp(key, "AntiUnFreeze", true)) { val = ini_GetValue( Line ); UNFREEZE=strval(val); }
		if(!strcmp(key, "AntiSwear", true)) { val = ini_GetValue( Line ); ANTISWEER=strval(val); }
		if(!strcmp(key, "AntiFlood", true)) { val = ini_GetValue( Line ); ANTIFLOOD=strval(val); }
		if(!strcmp(key, "FloodLim", true)) { val = ini_GetValue( Line ); FLOODLIM=strval(val); }
		if(!strcmp(key, "MaxPing", true)) { val = ini_GetValue( Line ); PINGS=strval(val); }
		if(!strcmp(key, "AFK", true)) { val = ini_GetValue( Line ); AFK=strval(val); }
		if(!strcmp(key, "TimeEsc", true)) { val = ini_GetValue( Line ); ESCSEC=strval(val); }
		if(!strcmp(key, "WeathChange", true)) { val = ini_GetValue( Line ); WEATHCHANGE=strval(val); }
		if(!strcmp(key, "CarSpawnTime", true)) { val = ini_GetValue( Line ); CARSPAWN=strval(val); }

		if(!strcmp(key, "Jackpot", true)) { val = ini_GetValue( Line ); Jackpot=strval(val); }
		if(!strcmp(key, "CriminalLevel", true)) { val = ini_GetValue( Line ); CriminalLevel=strval(val); }
		if(!strcmp(key, "Tax", true)) { val = ini_GetValue( Line ); TAX=strval(val); }
		if(!strcmp(key, "TaxValue", true)) { val = ini_GetValue( Line ); TaxValue=strval(val); }
		if(!strcmp(key, "Security", true)) { val = ini_GetValue( Line ); Security=strval(val); }
		if(!strcmp(key, "TimeTakeZone", true)) { val = ini_GetValue( Line ); TimeTakeZone=strval(val); }
		if(!strcmp(key, "CheckProp", true)) { val = ini_GetValue( Line ); gCheckProp=strval(val); }
		if(!strcmp(key, "QTime", true)) { val = ini_GetValue( Line ); qTime=strval(val); }
		if(!strcmp(key, "Hunger", true)) { val = ini_GetValue( Line ); HUNGER=strval(val); }
		if(!strcmp(key, "IdleKick", true)) { val = ini_GetValue( Line ); IdleKick=strval(val); }
		if(!strcmp(key, "Logs", true)) { val = ini_GetValue( Line ); LOGS=strval(val); }
		if(!strcmp(key, "Testing", true)) { val = ini_GetValue( Line ); gTesting=strval(val); }
		if(!strcmp(key, "Reconnect", true)) { val = ini_GetValue( Line ); ReconnectDelay=strval(val); }

		if(!strcmp(key, "FuelCost", true)) { val = ini_GetValue( Line ); FuelCost=floatstr(val); }
		if(!strcmp(key, "CompCost", true)) { val = ini_GetValue( Line ); compcost=strval(val); }
		if(!strcmp(key, "AntiDB", true)) { val = ini_GetValue( Line ); AntiDB=strval(val); }
		if(!strcmp(key, "AntiBH", true)) { val = ini_GetValue( Line ); AntiBH=strval(val); }
		if(!strcmp(key, "AntiDM", true)) { val = ini_GetValue( Line ); AntiDM=strval(val); }
		if(!strcmp(key, "CheckOnline", true)) { val = ini_GetValue( Line ); gCheckOnline=strval(val); }
		if(!strcmp(key, "RealWar", true)) { val = ini_GetValue( Line ); gRealWar=strval(val); }

		if(!strcmp(key, "Miner", true)) { val = ini_GetValue( Line ); StatusJob[1]=strval(val); }//Miner
		if(!strcmp(key, "Lawyer", true)) { val = ini_GetValue( Line ); StatusJob[2]=strval(val); }
		if(!strcmp(key, "RoadWorker", true)) { val = ini_GetValue( Line ); StatusJob[3]=strval(val); }
		if(!strcmp(key, "DrugDealer", true)) { val = ini_GetValue( Line ); StatusJob[4]=strval(val); }
		if(!strcmp(key, "CarJacker", true)) { val = ini_GetValue( Line ); StatusJob[5]=strval(val); }
		if(!strcmp(key, "AutoBuyer", true)) { val = ini_GetValue( Line ); StatusJob[6]=strval(val); }
		if(!strcmp(key, "CarMechanic", true)) { val = ini_GetValue( Line ); StatusJob[7]=strval(val); }
		if(!strcmp(key, "BodyGuard", true)) { val = ini_GetValue( Line ); StatusJob[8]=strval(val); }
		if(!strcmp(key, "ArmsDealer", true)) { val = ini_GetValue( Line ); StatusJob[9]=strval(val); }
		if(!strcmp(key, "CarDealer", true)) { val = ini_GetValue( Line ); StatusJob[10]=strval(val); }
		if(!strcmp(key, "Inkassator", true)) { val = ini_GetValue( Line ); StatusJob[11]=strval(val); }
		if(!strcmp(key, "Bookmaker", true)) { val = ini_GetValue( Line ); StatusJob[12]=strval(val); }
		if(!strcmp(key, "TaxiDriver", true)) { val = ini_GetValue( Line ); StatusJob[13]=strval(val); }
		if(!strcmp(key, "BusDriver", true)) { val = ini_GetValue( Line ); StatusJob[14]=strval(val); }
		if(!strcmp(key, "PaperBoy", true)) { val = ini_GetValue( Line ); StatusJob[15]=strval(val); }
		if(!strcmp(key, "Trucker", true)) { val = ini_GetValue( Line ); StatusJob[16]=strval(val); }
		if(!strcmp(key, "Trashman", true)) { val = ini_GetValue( Line ); StatusJob[17]=strval(val); }
	}
	fclose(sFile);
	printf("1/19. [Загрузка настроек]: Было загружено - %d, потрачено - %d (ms)", 50, (GetTickCount()-time));
	ChangeWeath = WEATHCHANGE;
	if(FuelCost <= 0.0 || FuelCost > 3.0) FuelCost = 1.0;
	return 1;
}


stock SaveSettings()//для загрузки настроек
{
	new time = GetTickCount();
	new File: sFile = fopen("Logs/settings.ini", io_write);
	if( !sFile ) { return 1; }

 	new var[20+MAX_PLAYER_NAME];
	format(var, sizeof(var), "CREATOR=%s\n", CREATOR);		fwrite(sFile, var);
	format(var, sizeof(var), "SERVERNAME=%s \n", SERVERNAME);		fwrite(sFile, var);
	format(var, sizeof(var), "HOSTNAME=%s\n", HostName);		fwrite(sFile, var);
	format(var, sizeof(var), "FORUM=%s\n", FORUM);		fwrite(sFile, var);
	format(var, sizeof(var), "GMText=%s\n", GMText);		fwrite(sFile, var);

	format(var, sizeof(var), "AntiCheat=%d\n", ANTICHEAT);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiSpeedHack=%d\n", ANTISPEEDHACK);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiTeleport=%d\n", ANTITELEPORT);		fwrite(sFile, var);
	format(var, sizeof(var), "CheatLim=%d\n", CHEATLIM);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiMoney=%d\n", ANTIMONEY);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiHealth=%d\n", ANTIHEALTH);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiVehHealth=%d\n", ANTIVEHHEALTH);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiGodMod=%d\n", ANTIGODMOD);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiGun=%d\n", ANTIGUN);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiUnFreeze=%d\n", UNFREEZE);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiSwear=%d\n", ANTISWEER);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiFlood=%d\n", ANTIFLOOD);		fwrite(sFile, var);
	format(var, sizeof(var), "FloodLim=%d\n", FLOODLIM);		fwrite(sFile, var);
	format(var, sizeof(var), "Ping=%d\n", PINGS);		fwrite(sFile, var);
	format(var, sizeof(var), "AFK=%d\n", AFK);		fwrite(sFile, var);
	format(var, sizeof(var), "TimeEsc=%d\n", ESCSEC);		fwrite(sFile, var);
	format(var, sizeof(var), "WeathChange=%d\n", WEATHCHANGE);		fwrite(sFile, var);
	format(var, sizeof(var), "CarSpawnTime=%d\n", CARSPAWN);		fwrite(sFile, var);

	format(var, sizeof(var), "Jackpot=%d\n", Jackpot);		fwrite(sFile, var);
	format(var, sizeof(var), "CriminalLevel=%d\n", CriminalLevel);		fwrite(sFile, var);
	format(var, sizeof(var), "Tax=%d\n", TAX);		fwrite(sFile, var);
	format(var, sizeof(var), "TaxValue=%d\n", TaxValue);		fwrite(sFile, var);
	format(var, sizeof(var), "Security=%d\n", Security);		fwrite(sFile, var);
	format(var, sizeof(var), "TimeTakeZone=%d\n", TimeTakeZone);		fwrite(sFile, var);
	format(var, sizeof(var), "CheckProp=%d\n", gCheckProp);		fwrite(sFile, var);
	format(var, sizeof(var), "QTime=%d\n", qTime);		fwrite(sFile, var);
	format(var, sizeof(var), "Hunger=%d\n", HUNGER);		fwrite(sFile, var);
	format(var, sizeof(var), "IdleKick=%d\n", IdleKick);		fwrite(sFile, var);
	format(var, sizeof(var), "Logs=%d\n", LOGS);		fwrite(sFile, var);
	format(var, sizeof(var), "Testing=%d\n", gTesting);		fwrite(sFile, var);
	format(var, sizeof(var), "Reconnect=%d\n", ReconnectDelay);		fwrite(sFile, var);

	format(var, sizeof(var), "FuelCost=%1.1f\n", FuelCost);		fwrite(sFile, var);
	format(var, sizeof(var), "CompCost=%d\n", compcost);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiDB=%d\n", AntiDB);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiBH=%d\n", AntiBH);		fwrite(sFile, var);
	format(var, sizeof(var), "AntiDM=%d\n", AntiDM);		fwrite(sFile, var);
	format(var, sizeof(var), "CheckOnline=%d\n", gCheckOnline);		fwrite(sFile, var);
	format(var, sizeof(var), "RealWar=%d\n", gRealWar);		fwrite(sFile, var);

	format(var, sizeof(var), "Miner=%d\n", StatusJob[1]);		fwrite(sFile, var);//Miner
	format(var, sizeof(var), "Lawyer=%d\n", StatusJob[2]);		fwrite(sFile, var);
	format(var, sizeof(var), "RoadWorker=%d\n", StatusJob[3]);		fwrite(sFile, var);
	format(var, sizeof(var), "DrugDealer=%d\n", StatusJob[4]);		fwrite(sFile, var);
	format(var, sizeof(var), "CarJacker=%d\n", StatusJob[5]);		fwrite(sFile, var);
	format(var, sizeof(var), "AutoBuyer=%d\n", StatusJob[6]);		fwrite(sFile, var);
	format(var, sizeof(var), "CarMechanic=%d\n", StatusJob[7]);		fwrite(sFile, var);
	format(var, sizeof(var), "BodyGuard=%d\n", StatusJob[8]);		fwrite(sFile, var);
	format(var, sizeof(var), "ArmsDealer=%d\n", StatusJob[9]);		fwrite(sFile, var);
	format(var, sizeof(var), "CarDealer=%d\n", StatusJob[10]);		fwrite(sFile, var);
	format(var, sizeof(var), "Inkassator=%d\n", StatusJob[11]);		fwrite(sFile, var);
	format(var, sizeof(var), "Bookmaker=%d\n", StatusJob[12]);		fwrite(sFile, var);
	format(var, sizeof(var), "TaxiDriver=%d\n", StatusJob[13]);		fwrite(sFile, var);
	format(var, sizeof(var), "BusDriver=%d\n", StatusJob[14]);		fwrite(sFile, var);
	format(var, sizeof(var), "PaperBoy=%d\n", StatusJob[15]);		fwrite(sFile, var);
	format(var, sizeof(var), "Trucker=%d\n", StatusJob[16]);		fwrite(sFile, var);
	format(var, sizeof(var), "Trashman=%d\n", StatusJob[17]);		fwrite(sFile, var);
	fclose(sFile);

//ИНФОРМИРОВАНИЕ
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "1/19. [Сохранение настроек]: Было сохранено - %d, потрачено - %d (ms)", 1, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
	return 1;
}



stock config_OnGameModeInit()//для загрузки настроек
{
	//new time = GetTickCount();
	//SendRconCommand("maxnpc 17");
/*
	mysql_debug(MySQL_DeBug);//лог ошибочек
	//mysql_close();//чтобы не могли через ФС перенаправить подключение
	mysql_connect("localhost", "root", "statgta", "");//Возвращает: ID соединения (его нудно использовать в connectionHandle)
	//format(strings, sizeof(strings), "reloadfs vw_reconnect");//ВНИМАНИЕ: скрипты загружаются раньше чем мод и действую до выключения сервере.При рестарте мода не перегружаются
	//SendRconCommand(strings);
#endif
*/
//mysql_connect(const host[], const user[], const database[], const password[])
//const host[]	IP or hostname of the MySQL server.
//const user[]	Username of the account you want to connect to.
//const database[]	Name of the database you want to connect to.
//const password[]	Password of the account you want to connect to.
	//mysql_set_charset("cp1251");//создаём кодировку для базы учитывающую регистр
	//mysql_query("SET NAMES 'cp1251'");//это для самого плагина, а также для самого скьюла делаем запрос	//обязательна должна быть cp1251
//mysql_set_charset("utf8");
//mysql_query("SET NAMES 'utf8'");

//mysql_query("OPTIM TABLE `banlist`,`bizz`,`blacklist`,`criminallist`,`election`,`families`,`house`,`invitelist`,`lastrounds`,`players`,`sbizz`,`settings`,`turfs`,`unbanlist`,`vehicles`,`vote`");
//mysql_function_query(cH, "SET NAMES utf8;", false, "", "");
//mysql_function_query(cH, "SET SESSION character_set_server=utf8;", false, "", "");

#if defined vw_sql//#endif
	//sql_MysqlConnect();
	db_OnGameModeInit();//подключаем базу
	LoadSettingsSQL();
#else
	LoadSettings();
#endif

	new strtmp[6+64+64];
	format(strtmp, sizeof(strtmp), "%s %s", GMText, VERSION);
	SetGameModeText(strtmp); //Выводит названия вашего гейммода в списке серверов (имя Мода в столбе Mode SA:MP)

//НАЧАЛЬНАЯ НАСТРОЙКА РЕЖИМА
    //ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);//LimitPlayerMarkerRadius(300.0);//Set the player marker radius.
	//Эта функция может быть использована для включения/выключения на карте маркеров для игроков.
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);//Маркеры Игрока только видимые, чтобы около игроков

	DisableInteriorEnterExits();//Отключает все входы/выходы в/из интериоров (желтые маркеры).)
	ShowNameTags(1);//Используйте эту функцию для включения/выключения подсвечивания над игроками их имен.
	SetNameTagDrawDistance(NameTagDrawDistance);//60.0 //20.0 Устанавливает расстояния отображения имен игроков.
	LimitGlobalChatRadius(chat_radius);//30 Float:chat_radius Включить ограничение радиуса чата. Только игроки на определенном расстоянии от игрока будут видеть его сообщения в чате.
	//Ракетница, Ракетница с тепловым наведением, Огнемёт, Миниган, Взрывпакеты, Детонатор для взрывпакетов, Фотоаппарат(43), Очки ночного видения, Инфракрасные очки
	SetWeather(1);//По умолчанию было 10 в самп 0.3 стало 1(красивое небо с облаками).
//Added /pagesize client command to set the number of chat lines displayed (10-20 lines default: 10).
	SetTeamCount(DoE+1);//Устанавливает максимальное число команд в игре.

	//DisableNameTagLOS();//видить ники через объекты	//Disables the nametag Line-Of-Sight checking so players can see nametags through objects.
	//SetGravity(0.008);//Установить гравитацию в мире
	EnableStuntBonusForAll(0);//включает награду за трюки
	//EnableVehicleFriendlyFire();
	//EnableStuntBonusForPlayer(playerid, 1);
	ManualVehicleEngineAndLights();//отключить автозапуск двигателя и света
	//HighestPlayerID += GetServerVarAsInt("maxnpc");

	if(gRrealTime == 0)//если время изменено
	{
		SetWorldTime(wtime);//Меняет время игры на указанное в переменной wtime=15
		//можно использовать при включении игрового времени
	}
	else if(gRrealTime == 1)//если флаг gRrealTime поднят, т.е. у нас счас реальное время
	{
		//gday = getdate();
		gettime(ghour, _, _);//Получает текущее время на сервере, которое запишется в переменные &hour, &minute и &second.
		//FixHour(ghour);//передали значение часа, а получилил скорректированное
		//ghour = shifthour;//записали скорректированное на величину timeshift
		SetWorldTime(ghour);//установили игровое время
		getdate(_,_,LastDay);
	}

	//==========================================================================
	// Player Class's Добавляем 3 класса для выбора спауна только после загрузки машин
	//AddPlayerClass(79,840.8961,-2058.4443,12.8672,269.1425,-1,-1,-1,-1,-1,-1);//координаты пристани
	//AddPlayerClass(137,2246.6,-1161.9,1029.8,0.0,-1,-1,-1,-1,-1,-1);//координаты Отеля(int15)
	//AddPlayerClass(SKIN_DEFAULT,-1657.5237,1207.6644,13.6719,0.0,-1,-1,-1,-1,-1,-1);//координаты OTTO'S AUTOS
//SetPlayerCameraPos(playerid,-1300.8754,68.0546,129.4823);
//SetPlayerCameraLookAt(playerid,-1817.9412,769.3878,132.6589);

	//Эта функция добавляет класс игрока в gamemode и работает она в пределах GameModeInit.
	//игрок установиться по этим координатам только при отсут.-ии SetSpawnInfoEx в ф-ии OnPlayerLogin
	//или при нажатии F4 и /kill

	//------------------------------------------------------------------
	/*Jackpot = 1000;
	StatusJob[5] = 0;//разрешить CarJacker
	StatusJob[11] = 1;//запретить Inkassator
	//TAX = 0;
	TaxValue = 1;
	gCheckProp = 7;
	ANTIVEHHEALTH = 1;
	ANTIHEALTH = 1;
	FuelCost = 0.7;*/

//для отображение онлайн игроков в стате
	//new ToBase[52+3];//для монитора
	//format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `Offline`=0", getdate());
	//mysql_query(ToBase);//все кто типа были онлайн, поставить текущий день
}
