//��� ��� ���������: �������� � ���������, ����� ������
new DB: db_VW; // Handle for database. Our queries need to use this so the queries know where to handle things

new CREATOR[] = "Danger_Hidden";
new SERVERNAME[] = "VirtualWorld";//�� ��� ����� � ����������� � ��������� ��������
new HostName[] = "localhost";//������ ����� ������������ ����� � ����������� �������
new FORUM[] = "http://strikearena.ru/forums/359-gtasa-virtual-world-server/";
new GMText[] = "LifeSimulator";//�������� ���� � ����������� ������

#if defined LOCAL
	#define MAIL "mail.ru"
	#define IP_ADRESS "127.0.0.1"//��-������ �������
	#define PORT "7777"//���� �������
	new php_host[] = "localhost";
	//new root_pass[] = "MN6zfHufnfJtm3QW";//������ ��� ������� ��������� ������ //������ ��� ���������� ��������
	//�� ����� 20 ��������
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
new ESCSEC = 900;//300 //����������� ������ ���
new WEATHCHANGE = 10;//5//�����
new CARSPAWN = 30;//�����  60000;

new Jackpot = 1000;
new CriminalLevel = 400;
new TAX;//�����
new TaxValue = 1;
new Security = 0;
new TimeTakeZone = 300;//����� ������� ���� �� ���������
new gCheckProp = 7;//0- ���������, ��� ���������� �������� ������������� ��� ���������� � ����
new qTime = 30;
new HUNGER = 0;
new IdleKick = 0;
new LOGS = 1;//1 - ��������� �����������
new gTesting = 0;
new ReconnectDelay = 5;//120;

new Float: FuelCost = 0.7;//���� �� ����
new compcost = 10;//10 ��������� ��������� ��� �����
new AntiDB = 1;
new AntiBH = 1;
new AntiDM = 1;
new gCheckOnline = 1;
new gRealWar = 0;//1//�� ��������, �.�. �������� �� ���� ������ ��������

new StatusJob[20];


new countrace = 0;//������� ���-�� ����������� ����� racecountdown

new PagerMessage[142];//87+2+2+4+20+24+3�=�142
//##############################################################################
//#define LOCAL //��������� ������
//##############################################################################


//##############################################################################//
//                                                                              //
//                              ��������� �������                               //
//                                                                              //
//##############################################################################//
//������� ������ ��� ������ ������ �������������

#define BANTIME 		2
#define SKIN_DEFAULT	26//78//264
#define SOC_PACKET 		166//MAX_PLAYERS-4;//170-4
#define QUIT_JOB 		167//MAX_PLAYERS-3;
#define SELLGUN 		167//MAX_PLAYERS-3;

//��� �������������� � ��.
new Float: CHECKPOINT_SIZE = 4.0;//���� ����� ������ ��� ������ ������������ ������� � IsPlayerInRangeOfPoint(playerid, 5.0,
new gTogNameTag = 1;//1 - ���� ��������
new Float: stream_distance = 300.0;

new idletime = 30; //����� ������������� � �������, ���� 15 mins

//��� ���������
//new levelcost = 2500;//25000 ���� ������



//new gClock = 1;//��� �������

//new DestroyDate = 15;//����� ����� �����


//��������� ���������
//new ANIMATION = 0;
//new KEYSTATE = 0;
//new TRAILER = 0;//������� ��������� �� ������������ �������
//new HEALTH = 0;//������� ��������� �� �������� ������ ������ �������
//new CAMERA = 0;
//new consuption_fuel = 15;//��� ������� �������, ��� ���� �����, ��� ������ ������

//##############################################################################//
//                                                                              //
//                     ����������� ���������� ����������                        //
//                                                                              //
//##############################################################################//
new Float: NameTagDrawDistance = 60.0;

//��� ����
//new gRealChat = 1;//������� ��� �������
//new gOffGeneralChat = 1;//����� ���� �������
#define chat_radius 8.0

//��� �������
new gRrealTime = 1;//�������� �����
new timeshift = 0;//-1 - ����� ������� �� 1 ��� ����� �����//3 - ����� ������� �� 3 ���� ������ �����
//new shifthour = 1;//��������������� ���
new wtime = 15;//������ �������� �������
new ghour;//������ ���������� ���, ���������������� ��� �������� ����
new LastDay;//new gday;//������ ���������� ����, ���������������� ��� �������� ����
//, gminute, gsecond;//��� ������������� �������


new ChangeWeath;//������ ����� ������

//##############################################################################//
//                                                                              //
//                                  �ר�����                                    //
//                                                                              //
//##############################################################################//

//��� �������� �����������
new PingCount[MAX_PLAYERS];//������� ���-�� ������������ ��� ���������� �����

new GetMaxVehicles = 1;//������������ �� ����� � ����
new LoadCarCounter = 0;//������� ������������ ���������� ��� ������ ����
new VehiclesCounter; //����� ������� ����������� �����
new CreatedCarCounter;//������� ��������� ����� � �������� ����
new VehiclesModelsCounter = 0;//������� �������
new aExistModel[MAX_VEHICLES+1];//��� ������������ ������

new CreateObjectCounter = 0;//������� ��������
new CreatePlayerObjectCounter[MAX_PLAYERS];//������� ��������
new RemoveBuildingCounter[MAX_PLAYERS];//������� ��������

new ActorCounter = 0;//������� ������

new PickupCounter = 0;//������� ���������� �������

new TEXT_DRAWS_COUNTER;//������� ����������� ���������
new PLAYER_TEXT_DRAWS_COUNTER[MAX_PLAYERS];//������� ����������� ���������

new Counter3DText = 0;//������� 3� �������
new LabelPlayerCounter[MAX_PLAYERS];//������� Player3� �������
//##############################################################################//

stock LoadSettings()//��� �������� ��������
{
	new time = GetTickCount();
	if( !fexist("Logs/settings.ini") ) { SaveSettings(); return 1; }
	new File: sFile = fopen("Logs/settings.ini", io_read);
	if( !sFile ) { return 1; }
    new key[256+1], val[256+1], Line[256+1];
	while( fread(sFile, Line, sizeof(Line)) )
	{//������ ����� �� ��� ��� ���� � ��� ���� ������:
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
	printf("1/19. [�������� ��������]: ���� ��������� - %d, ��������� - %d (ms)", 50, (GetTickCount()-time));
	ChangeWeath = WEATHCHANGE;
	if(FuelCost <= 0.0 || FuelCost > 3.0) FuelCost = 1.0;
	return 1;
}


stock SaveSettings()//��� �������� ��������
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

//��������������
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "1/19. [���������� ��������]: ���� ��������� - %d, ��������� - %d (ms)", 1, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
	return 1;
}



stock config_OnGameModeInit()//��� �������� ��������
{
	//new time = GetTickCount();
	//SendRconCommand("maxnpc 17");
/*
	mysql_debug(MySQL_DeBug);//��� ��������
	//mysql_close();//����� �� ����� ����� �� ������������� �����������
	mysql_connect("localhost", "root", "statgta", "");//����������: ID ���������� (��� ����� ������������ � connectionHandle)
	//format(strings, sizeof(strings), "reloadfs vw_reconnect");//��������: ������� ����������� ������ ��� ��� � �������� �� ���������� �������.��� �������� ���� �� �������������
	//SendRconCommand(strings);
#endif
*/
//mysql_connect(const host[], const user[], const database[], const password[])
//const host[]	IP or hostname of the MySQL server.
//const user[]	Username of the account you want to connect to.
//const database[]	Name of the database you want to connect to.
//const password[]	Password of the account you want to connect to.
	//mysql_set_charset("cp1251");//������ ��������� ��� ���� ����������� �������
	//mysql_query("SET NAMES 'cp1251'");//��� ��� ������ �������, � ����� ��� ������ ������ ������ ������	//����������� ������ ���� cp1251
//mysql_set_charset("utf8");
//mysql_query("SET NAMES 'utf8'");

//mysql_query("OPTIM TABLE `banlist`,`bizz`,`blacklist`,`criminallist`,`election`,`families`,`house`,`invitelist`,`lastrounds`,`players`,`sbizz`,`settings`,`turfs`,`unbanlist`,`vehicles`,`vote`");
//mysql_function_query(cH, "SET NAMES utf8;", false, "", "");
//mysql_function_query(cH, "SET SESSION character_set_server=utf8;", false, "", "");

#if defined vw_sql//#endif
	//sql_MysqlConnect();
	db_OnGameModeInit();//���������� ����
	LoadSettingsSQL();
#else
	LoadSettings();
#endif

	new strtmp[6+64+64];
	format(strtmp, sizeof(strtmp), "%s %s", GMText, VERSION);
	SetGameModeText(strtmp); //������� �������� ������ �������� � ������ �������� (��� ���� � ������ Mode SA:MP)

//��������� ��������� ������
    //ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);//LimitPlayerMarkerRadius(300.0);//Set the player marker radius.
	//��� ������� ����� ���� ������������ ��� ���������/���������� �� ����� �������� ��� �������.
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);//������� ������ ������ �������, ����� ����� �������

	DisableInteriorEnterExits();//��������� ��� �����/������ �/�� ���������� (������ �������).)
	ShowNameTags(1);//����������� ��� ������� ��� ���������/���������� ������������� ��� �������� �� ����.
	SetNameTagDrawDistance(NameTagDrawDistance);//60.0 //20.0 ������������� ���������� ����������� ���� �������.
	LimitGlobalChatRadius(chat_radius);//30 Float:chat_radius �������� ����������� ������� ����. ������ ������ �� ������������ ���������� �� ������ ����� ������ ��� ��������� � ����.
	//���������, ��������� � �������� ����������, ������, �������, �����������, ��������� ��� ������������, �����������(43), ���� ������� �������, ������������ ����
	SetWeather(1);//�� ��������� ���� 10 � ���� 0.3 ����� 1(�������� ���� � ��������).
//Added /pagesize client command to set the number of chat lines displayed (10-20 lines default: 10).
	SetTeamCount(DoE+1);//������������� ������������ ����� ������ � ����.

	//DisableNameTagLOS();//������ ���� ����� �������	//Disables the nametag Line-Of-Sight checking so players can see nametags through objects.
	//SetGravity(0.008);//���������� ���������� � ����
	EnableStuntBonusForAll(0);//�������� ������� �� �����
	//EnableVehicleFriendlyFire();
	//EnableStuntBonusForPlayer(playerid, 1);
	ManualVehicleEngineAndLights();//��������� ���������� ��������� � �����
	//HighestPlayerID += GetServerVarAsInt("maxnpc");

	if(gRrealTime == 0)//���� ����� ��������
	{
		SetWorldTime(wtime);//������ ����� ���� �� ��������� � ���������� wtime=15
		//����� ������������ ��� ��������� �������� �������
	}
	else if(gRrealTime == 1)//���� ���� gRrealTime ������, �.�. � ��� ���� �������� �����
	{
		//gday = getdate();
		gettime(ghour, _, _);//�������� ������� ����� �� �������, ������� ��������� � ���������� &hour, &minute � &second.
		//FixHour(ghour);//�������� �������� ����, � ��������� �����������������
		//ghour = shifthour;//�������� ����������������� �� �������� timeshift
		SetWorldTime(ghour);//���������� ������� �����
		getdate(_,_,LastDay);
	}

	//==========================================================================
	// Player Class's ��������� 3 ������ ��� ������ ������ ������ ����� �������� �����
	//AddPlayerClass(79,840.8961,-2058.4443,12.8672,269.1425,-1,-1,-1,-1,-1,-1);//���������� ��������
	//AddPlayerClass(137,2246.6,-1161.9,1029.8,0.0,-1,-1,-1,-1,-1,-1);//���������� �����(int15)
	//AddPlayerClass(SKIN_DEFAULT,-1657.5237,1207.6644,13.6719,0.0,-1,-1,-1,-1,-1,-1);//���������� OTTO'S AUTOS
//SetPlayerCameraPos(playerid,-1300.8754,68.0546,129.4823);
//SetPlayerCameraLookAt(playerid,-1817.9412,769.3878,132.6589);

	//��� ������� ��������� ����� ������ � gamemode � �������� ��� � �������� GameModeInit.
	//����� ������������ �� ���� ����������� ������ ��� �����.-�� SetSpawnInfoEx � �-�� OnPlayerLogin
	//��� ��� ������� F4 � /kill

	//------------------------------------------------------------------
	/*Jackpot = 1000;
	StatusJob[5] = 0;//��������� CarJacker
	StatusJob[11] = 1;//��������� Inkassator
	//TAX = 0;
	TaxValue = 1;
	gCheckProp = 7;
	ANTIVEHHEALTH = 1;
	ANTIHEALTH = 1;
	FuelCost = 0.7;*/

//��� ����������� ������ ������� � �����
	//new ToBase[52+3];//��� ��������
	//format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `Offline`=0", getdate());
	//mysql_query(ToBase);//��� ��� ���� ���� ������, ��������� ������� ����
}