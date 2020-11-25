#include <a_mysql>


stock mysql_CheckPassword(playerid, password[])
{
	if(!mysql_ping())
	{
		format(strings, sizeof(strings), "%s[%d] mysql_ping(): MySQL connection is dead![%d]", PlayerName(playerid), playerid, mysql_ping());
		Log(ERROR, strings);
		return 1;
	}
	//new strings[MAX_STRING];
	//new playername[MAX_PLAYER_NAME];
	//GetPlayerName(playerid, playername, sizeof(playername));

//Экранирование просто заменяет все ' на /'
	//mysql_real_escape_string(playername, playername);//ник ни где не надо экранировать т.к. проверка на РП ник стоит
	mysql_real_escape_string(password, password);//убирает пробелы
// Мы конвертируем имя игрока и туда же записываем конвертированныи текст.
//не даёт в запрос подставлять дополнительно 123' OR `Name`='Danger_Hidden
//нужно только там где есть ввод части запроса вручную
//SELECT * FROM `players` WHERE `Name` = 'Emci_Funtik' AND `Password` = '123' OR `Name`='Danger_Hidden' LIMIT 1
	new ToBase[169];//125 + 24+20 = 169
	format(ToBase, sizeof(ToBase), "SELECT * FROM `players` WHERE `Name` = '%s' AND `Password` = '%s' LIMIT 1", PlayerName(playerid), password);
	mysql_query(ToBase);// - делаем запрос
	mysql_store_result();// - получаем результат.
	if(mysql_num_rows() > 0)
	{	//если в базе нашло хоть одно значение
		SendClientMessage(playerid, COLOR_SYSTEM, "   Пароль принят.");
		if(mysql_retrieve_row()) { OnPlayerLoadParameters(playerid, PlayerName(playerid)); }
		mysql_free_result();
		//OnPlayerLoadTempParameters(playerid, playername);
	}
	else
	{   //Password mismatch
		mysql_free_result();
		format(strings, sizeof(strings), "   Пароль: '%s', не соответствует вашей учётной записи (USE: (/q)uit, чтобы выйти из игры).", password);
		SendClientMessage(playerid, COLOR_SYSTEM, strings);
		SendClientMessage(playerid, COLOR_SYSTEM, "Нажмите кнопку REMINDER при входе. Зайдите на ваш почтовый ящик и проверьте пароль(в разделе СПАМ). Возможно он был изменён.");//Пароль несовпадает с логином.

		GivePVarInt(playerid, "mistaking", +1);
		if(GetPVarInt(playerid, "mistaking") >= 3)
		{
			format(strings, sizeof(strings), "CEPBEP: %s[%d] kicked, reason: password mistaking", PlayerName(playerid), playerid);
			SendSystemMessage(COLOR_MAROON, strings, 1);
			IsKicked[playerid] = 1;
	        //return 1;
        }
        else
        {
 			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Пожалуйста введите пароль не более 20 символов!!! Внимание: пароль чувствителен к регистру!!!");

		    format(strings, sizeof(strings), "Добро пожаловать на SA-MP сервер.\n\n{0080FF}Учётная запись: {FFFFFF}%s{A9C4E4}\n\nПожалуйста введите ваш пароль ниже:", PlayerName(playerid));
			ShowPlayerDialogEx(playerid, LOGIN_DIALOG, DIALOG_STYLE_INPUT, HostName, strings, "Login", "");
			//return 1;
        }
	}
	return 1;
}


stock CheckExistPlayer(playerid, const playerName[])
{//вызывается только для проверки имени в базе
	//if(gPlayerLogged[playerid] == 1) return 1;
	if(strlen(playerName) < 6 || strlen(playerName) >= 20)
	{
		//SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
		return -1;
	}
	if(mysql_ping() == 1)
	{
		new ToBase[79];//55+24 = 79
		format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE `Name` = '%s' LIMIT 1", playerName);//playername);//задержка 1676 ms //LIMIT 1 - для оптимизизации
		mysql_query(ToBase); mysql_store_result();
		switch(mysql_num_rows())
		{
			case 0://учётной записи нету в базе данных
			{
				mysql_free_result();
				return 0;
			}
			case 1://Это имя уже зарегистрировано
			{
				mysql_free_result();
				return 1;
			}
			default:
			{
//ПРЕРЫВАЕМ РЕГИСТРАЦИЮ И ДАЛЬНЕЙШИЕ ДЕЙСТВИЯ, ОТПРАВЛЯЯ ИГРОКУ СООБЩЕНИЯ О ПЕРЕЗАХОДЕ
				mysql_free_result();
				SendClientMessageEx(playerid, COLOR_RED, "CEPBEP: {33AA33}База данных не работает (Kicked)!");
			    IsKicked[playerid] = 1;
				return -1;
			}
		}
	}
	else
	{
// ПРЕРЫВАЕМ РЕГИСТРАЦИЮ И ДАЛЬНЕЙШИЕ ДЕЙСТВИЯ, ОТПРАВЛЯЯ ИГРОКУ СООБЩЕНИЯ О ПЕРЕЗАХОДЕ.
	}
	return -1;
}


//##############################################################################//
//                                                                              //
//               ВЫПОЛНЯЕТСЯ ПРИ СТАРТЕ РЕЖИМА ИЗ GameModeInit()                //
//                                                                              //
//##############################################################################//

stock sql_MysqlConnect()
{
	mysql_debug(MySQL_DeBug);//лог ошибочек
	new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);

	db = mysql_connect("localhost", "root", "statgta", "");
	if (db == MYSQL_INVALID_HANDLE || mysql_errno(db) != 0)
	{
		print("MySQL connection failed. Server is shutting down. %i, %i");
		SendRconCommand("exit");
		return 0;
	}
	mysql_query(db, "SET NAMES cp1251", false);
	mysql_set_charset("cp1251", db);

	print("MySQL connection is successful.");
	return 1;
}
//------------------------------------------------------------------------------


stock LoadSettingsSQL()//для загрузки настроек
{
	new time = GetTickCount();
	mysql_query("SELECT * FROM `settings`");//делаем запрос
	mysql_store_result();//получаем результат.
//сохраняет результат в буфер. всегда возвращает единицу
//mysql_retrieve_row Возвращает: 1 - если строка сменилась, 0 - если больше нет строк
	if(mysql_num_rows() > 0 && mysql_retrieve_row())//mysql_retrieve_row() - получает строку, а если строки нет - даёт ноль, служит для перехода на следующую строку.
//mysql_num_rows() - получает кол-во строк, полученных в результате выполнения запросов SELECT и SHOW (схожа с mysql_affected_rows)
	{	//если в базе нашло хоть одно значение
		new Field[20];
		//mysql_fetch_field - Функция получает название определенного столбца.
		//mysql_fetch_field_row - получает данные из указанного столбца
		mysql_fetch_field_row(Field, "AntiCheat"); ANTICHEAT = strval(Field);
		mysql_fetch_field_row(Field, "AntiSpeedHack"); ANTISPEEDHACK = strval(Field);
		mysql_fetch_field_row(Field, "AntiTeleport"); ANTITELEPORT = strval(Field);
		mysql_fetch_field_row(Field, "teleports"); CHEATLIM = strval(Field);
		mysql_fetch_field_row(Field, "AntiMoney"); ANTIMONEY = strval(Field);
		mysql_fetch_field_row(Field, "AntiHealth"); ANTIHEALTH = strval(Field);
		mysql_fetch_field_row(Field, "AntiVehHealth"); ANTIVEHHEALTH = strval(Field);
		mysql_fetch_field_row(Field, "AntiGodMod"); ANTIGODMOD = strval(Field);
		mysql_fetch_field_row(Field, "AntiGun"); ANTIGUN = strval(Field);
		mysql_fetch_field_row(Field, "AntiUnFreeze"); UNFREEZE = strval(Field);
		mysql_fetch_field_row(Field, "AntiSwear"); ANTISWEER = strval(Field);
		mysql_fetch_field_row(Field, "AntiFlood"); ANTIFLOOD = strval(Field);
		mysql_fetch_field_row(Field, "floods"); FLOODLIM = strval(Field);
		mysql_fetch_field_row(Field, "MaxPing"); PINGS = strval(Field);
		mysql_fetch_field_row(Field, "AwayFromKeyboard"); AFK = strval(Field);
		mysql_fetch_field_row(Field, "TimeEsc"); ESCSEC = strval(Field);
		mysql_fetch_field_row(Field, "WeathChange"); WEATHCHANGE = strval(Field);
		mysql_fetch_field_row(Field, "CarSpawnTime"); CARSPAWN = strval(Field);
		mysql_fetch_field_row(Field, "Jackpot"); Jackpot = strval(Field);
		mysql_fetch_field_row(Field, "CriminalLevel"); CriminalLevel = strval(Field);
		mysql_fetch_field_row(Field, "Tax"); TAX = strval(Field);
		mysql_fetch_field_row(Field, "TaxValue"); TaxValue = strval(Field);
		mysql_fetch_field_row(Field, "Security"); Security = strval(Field);
		mysql_fetch_field_row(Field, "TimeTakeZone"); TimeTakeZone = strval(Field);
		mysql_fetch_field_row(Field, "CheckProp"); gCheckProp = strval(Field);
		mysql_fetch_field_row(Field, "QTime"); qTime = strval(Field);
		mysql_fetch_field_row(Field, "Hunger"); HUNGER = strval(Field);
		mysql_fetch_field_row(Field, "IdleKick"); IdleKick = strval(Field);
		mysql_fetch_field_row(Field, "Logs"); LOGS = strval(Field);
		mysql_fetch_field_row(Field, "Registration"); gTesting = strval(Field);
		mysql_fetch_field_row(Field, "Reconnect"); ReconnectDelay = strval(Field);

		mysql_fetch_field_row(Field, "FuelCost"); FuelCost = floatstr(Field);
		mysql_fetch_field_row(Field, "CompCost"); compcost = strval(Field);
		mysql_fetch_field_row(Field, "AntiDB"); AntiDB = strval(Field);
		mysql_fetch_field_row(Field, "AntiBH"); AntiBH = strval(Field);
		mysql_fetch_field_row(Field, "AntiDM"); AntiDM = strval(Field);
		mysql_fetch_field_row(Field, "CheckOnline"); gCheckOnline = strval(Field);
		mysql_fetch_field_row(Field, "RealWar"); gRealWar = strval(Field);

		mysql_fetch_field_row(Field, "Detective"); StatusJob[1] = strval(Field);//Miner
		mysql_fetch_field_row(Field, "Lawyer"); StatusJob[2] = strval(Field);
		mysql_fetch_field_row(Field, "RoadWorker"); StatusJob[3] = strval(Field);
		mysql_fetch_field_row(Field, "DrugDealer"); StatusJob[4] = strval(Field);
		mysql_fetch_field_row(Field, "CarJacker"); StatusJob[5] = strval(Field);
		mysql_fetch_field_row(Field, "AutoBuyer"); StatusJob[6] = strval(Field);
		mysql_fetch_field_row(Field, "CarMechanic"); StatusJob[7] = strval(Field);
		mysql_fetch_field_row(Field, "BodyGuard"); StatusJob[8] = strval(Field);
		mysql_fetch_field_row(Field, "ArmsDealer"); StatusJob[9] = strval(Field);
		mysql_fetch_field_row(Field, "CarDealer"); StatusJob[10] = strval(Field);
		mysql_fetch_field_row(Field, "Inkassator"); StatusJob[11] = strval(Field);
		mysql_fetch_field_row(Field, "Bookmaker"); StatusJob[12] = strval(Field);
		mysql_fetch_field_row(Field, "TaxiDriver"); StatusJob[13] = strval(Field);
		mysql_fetch_field_row(Field, "BusDriver"); StatusJob[14] = strval(Field);
		mysql_fetch_field_row(Field, "PaperBoy"); StatusJob[15] = strval(Field);
		mysql_fetch_field_row(Field, "Trucker"); StatusJob[16] = strval(Field);
		mysql_fetch_field_row(Field, "Trashman"); StatusJob[17] = strval(Field);
	}
	printf("1/19. [Загрузка настроек]: Было загружено - %d, потрачено - %d (ms)", mysql_num_rows(), (GetTickCount()-time));//new time = GetTickCount();

	mysql_free_result();//Функция используется для очистки результата после использования mysql_store_result
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
	mysql_query(ToBase);

//ИНФОРМИРОВАНИЕ
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "1/19. [Сохранение настроек]: Было сохранено - %d, потрачено - %d (ms)", 1, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//SpawnSTEP6
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
stock OnPlayerLoadParameters(playerid, const nameplayer[])//вызывается по команде /showplayerstats
{//ВНИМАНИЕ: перед должны быть mysql_query(ToBase); mysql_store_result();
	#pragma unused nameplayer
	if(playerid < 0 || playerid >= MAX_PLAYERS) return 1;

	new Field[34];//длина самого большого параметра
	mysql_fetch_field_row(Field, "ID"); PlayerInfo[playerid][pSQLID] = strval(Field);
	//mysql_fetch_field_row(PlayerInfo[playerid][pName], "Name");//strmid(PlayerInfo[playerid][pName], "Unknown", 0, strlen("Unknown"), 24);
	mysql_fetch_field_row(PlayerInfo[playerid][pMail], "Mail");	//strmid(PlayerInfo[playerid][pMail], Field, 0, strlen(Field), 34);
	mysql_fetch_field_row(PlayerInfo[playerid][pIP], "IP");//		strmid(PlayerInfo[playerid][pIP], Field, 0, strlen(Field), 16);	//не загружать, т.к. при входе он инициализируется
//если сработает ф-ия, то IP может загрузиться пустым
	mysql_fetch_field_row(Field, "Sex");	PlayerInfo[playerid][pSex] = strval(Field);
	mysql_fetch_field_row(Field, "Age");	strmid(PlayerInfo[playerid][pAge], Field, 0, strlen(Field), 12);
	//mysql_fetch_field_row(Field, "Origin");	PlayerInfo[playerid][pOrigin] = strval(Field);
	mysql_fetch_field_row(Field, "DepositDay");	PlayerInfo[playerid][pDepositDay] = strval(Field);
	mysql_fetch_field_row(Field, "Level"); PlayerInfo[playerid][pLevel] = strval(Field);
	mysql_fetch_field_row(Field, "AdminLevel");	PlayerInfo[playerid][pAdmin] = strval(Field);
	mysql_fetch_field_row(Field, "Account");	PlayerInfo[playerid][pAccount] = strval(Field);
	mysql_fetch_field_row(Field, "Muted");	PlayerInfo[playerid][pMuted] = strval(Field);
	mysql_fetch_field_row(Field, "Warns");	PlayerInfo[playerid][pWarns] = strval(Field);
	mysql_fetch_field_row(Field, "ConnectTime");	PlayerInfo[playerid][pConnectTime] = strval(Field);
	mysql_fetch_field_row(Field, "Respect");	PlayerInfo[playerid][pRespect] = strval(Field);
	mysql_fetch_field_row(Field, "RespectDay");	PlayerInfo[playerid][pRespectDay] = strval(Field);
	mysql_fetch_field_row(Field, "PayCheck");	PlayerInfo[playerid][pPayCheck] = strval(Field);
	mysql_fetch_field_row(Field, "PayDay");	PlayerInfo[playerid][pPayTime] = strval(Field);
	mysql_fetch_field_row(Field, "Deposit");	PlayerInfo[playerid][pDeposit] = strval(Field);
	mysql_fetch_field_row(Field, "Cash");	PlayerInfo[playerid][pCash] = strval(Field);
	mysql_fetch_field_row(Field, "Bank");	PlayerInfo[playerid][pBank] = strval(Field);
	//mysql_fetch_field_row(Field, "Gold");	PlayerInfo[playerid][pGold] = strval(Field);
	mysql_fetch_field_row(Field, "SHealth");	PlayerInfo[playerid][pSHealth] = floatstr(Field);
	mysql_fetch_field_row(Field, "Health");	PlayerInfo[playerid][pHealth] = floatstr(Field);
	mysql_fetch_field_row(Field, "Interior");	PlayerInfo[playerid][pInt] = strval(Field);
	mysql_fetch_field_row(Field, "Pos_x");	PlayerInfo[playerid][pPos_x] = floatstr(Field);
	mysql_fetch_field_row(Field, "Pos_y");	PlayerInfo[playerid][pPos_y] = floatstr(Field);
	mysql_fetch_field_row(Field, "Pos_z");	PlayerInfo[playerid][pPos_z] = floatstr(Field);
	mysql_fetch_field_row(Field, "Virtual");	PlayerInfo[playerid][pVirtual] = strval(Field);
	mysql_fetch_field_row(Field, "Local");	PlayerInfo[playerid][pLocal] = strval(Field);
	mysql_fetch_field_row(Field, "House");	PlayerInfo[playerid][pHouse] = strval(Field);
	mysql_fetch_field_row(Field, "Bizz");	PlayerInfo[playerid][pBizz] = strval(Field);
	mysql_fetch_field_row(Field, "Job");	PlayerInfo[playerid][pJob] = strval(Field);
	mysql_fetch_field_row(Field, "Team");	PlayerInfo[playerid][pTeam] = strval(Field);
	mysql_fetch_field_row(Field, "Member");	PlayerInfo[playerid][pMember] = strval(Field);
	mysql_fetch_field_row(Field, "Leader");	PlayerInfo[playerid][pLeader] = strval(Field);
	mysql_fetch_field_row(Field, "Rank");	PlayerInfo[playerid][pRank] = strval(Field);
	mysql_fetch_field_row(Field, "Char");	PlayerInfo[playerid][pChar] = strval(Field);
	mysql_fetch_field_row(Field, "Model");	PlayerInfo[playerid][pModel] = strval(Field);
	mysql_fetch_field_row(Field, "ContractTime");	PlayerInfo[playerid][pContractTime] = strval(Field);
	mysql_fetch_field_row(Field, "MinerSkill");	PlayerInfo[playerid][pMinerSkill] = strval(Field);
	mysql_fetch_field_row(Field, "LawSkill");	PlayerInfo[playerid][pLawSkill] = strval(Field);
	mysql_fetch_field_row(Field, "RoadSkill");	PlayerInfo[playerid][pRoadSkill] = strval(Field);
	mysql_fetch_field_row(Field, "DrugsSkill");	PlayerInfo[playerid][pDrugsSkill] = strval(Field);
	mysql_fetch_field_row(Field, "JackSkill");	PlayerInfo[playerid][pJackSkill] = strval(Field);
	mysql_fetch_field_row(Field, "ProfSkill");	PlayerInfo[playerid][pProfSkill] = strval(Field);
	mysql_fetch_field_row(Field, "MechSkill");	PlayerInfo[playerid][pMechSkill] = strval(Field);
	mysql_fetch_field_row(Field, "FarmSkill");	PlayerInfo[playerid][pFarmSkill] = strval(Field);
	mysql_fetch_field_row(Field, "GunSkill");	PlayerInfo[playerid][pGunSkill] = strval(Field);
	mysql_fetch_field_row(Field, "CarSkill");	PlayerInfo[playerid][pCarSkill] = strval(Field);
	mysql_fetch_field_row(Field, "InkasSkill");	PlayerInfo[playerid][pInkasSkill] = strval(Field);
	mysql_fetch_field_row(Field, "BookmakerSkill");	PlayerInfo[playerid][pBookmakerSkill] = strval(Field);
	mysql_fetch_field_row(Field, "TaxiSkill");	PlayerInfo[playerid][pTaxiSkill] = strval(Field);
	mysql_fetch_field_row(Field, "BusSkill");	PlayerInfo[playerid][pBusSkill] = strval(Field);
	mysql_fetch_field_row(Field, "CourierSkill");	PlayerInfo[playerid][pCourierSkill] = strval(Field);
	mysql_fetch_field_row(Field, "TruckSkill");	PlayerInfo[playerid][pTruckSkill] = strval(Field);
	mysql_fetch_field_row(Field, "TrashSkill");	PlayerInfo[playerid][pTrashSkill] = strval(Field);
	mysql_fetch_field_row(Field, "LoadSkill");	PlayerInfo[playerid][pLoadSkill] = strval(Field);
	mysql_fetch_field_row(Field, "WoodSkill");	PlayerInfo[playerid][pWoodSkill] = strval(Field);
	mysql_fetch_field_row(Field, "FishSkill");	PlayerInfo[playerid][pFishSkill] = strval(Field);
	mysql_fetch_field_row(Field, "FireSkill");	PlayerInfo[playerid][pFireSkill] = strval(Field);
	mysql_fetch_field_row(Field, "CookSkill");	PlayerInfo[playerid][pCookSkill] = strval(Field);

	mysql_fetch_field_row(Field, "CarLic");	PlayerInfo[playerid][pCarLic] = strval(Field);
	mysql_fetch_field_row(Field, "BikeLic");	PlayerInfo[playerid][pBikeLic] = strval(Field);
	mysql_fetch_field_row(Field, "FlyLic");	PlayerInfo[playerid][pFlyLic] = strval(Field);
	mysql_fetch_field_row(Field, "BoatLic");	PlayerInfo[playerid][pBoatLic] = strval(Field);
	mysql_fetch_field_row(Field, "FishLic");	PlayerInfo[playerid][pFishLic] = strval(Field);
	mysql_fetch_field_row(Field, "GunLic");	PlayerInfo[playerid][pGunLic] = strval(Field);
	mysql_fetch_field_row(Field, "Gun1");	PlayerInfo[playerid][pGun1] = strval(Field);
	mysql_fetch_field_row(Field, "Ammo1");	PlayerInfo[playerid][pAmmo1] = strval(Field);
	mysql_fetch_field_row(Field, "Gun2");	PlayerInfo[playerid][pGun2] = strval(Field);
	mysql_fetch_field_row(Field, "Ammo2");	PlayerInfo[playerid][pAmmo2] = strval(Field);
	mysql_fetch_field_row(Field, "Gun3");	PlayerInfo[playerid][pGun3] = strval(Field);
	mysql_fetch_field_row(Field, "Ammo3");	PlayerInfo[playerid][pAmmo3] = strval(Field);
	mysql_fetch_field_row(Field, "Gun4");	PlayerInfo[playerid][pGun4] = strval(Field);
	mysql_fetch_field_row(Field, "Ammo4");	PlayerInfo[playerid][pAmmo4] = strval(Field);
	mysql_fetch_field_row(Field, "Gun22Skill");	PlayerInfo[playerid][pGun22Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun23Skill");	PlayerInfo[playerid][pGun23Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun24Skill");	PlayerInfo[playerid][pGun24Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun25Skill");	PlayerInfo[playerid][pGun25Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun26Skill");	PlayerInfo[playerid][pGun26Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun27Skill");	PlayerInfo[playerid][pGun27Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun28Skill");	PlayerInfo[playerid][pGun28Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun29Skill");	PlayerInfo[playerid][pGun29Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun30Skill");	PlayerInfo[playerid][pGun30Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun31Skill");	PlayerInfo[playerid][pGun31Skill] = strval(Field);
	mysql_fetch_field_row(Field, "Gun34Skill");	PlayerInfo[playerid][pGun34Skill] = strval(Field);
	mysql_fetch_field_row(Field, "HeadValue");	PlayerInfo[playerid][pHeadValue] = strval(Field);
	mysql_fetch_field_row(Field, "Wins");	PlayerInfo[playerid][pWins] = strval(Field);
	mysql_fetch_field_row(Field, "Loses");	PlayerInfo[playerid][pLoses] = strval(Field);
	mysql_fetch_field_row(Field, "Kills");	PlayerInfo[playerid][pKills] = strval(Field);
	mysql_fetch_field_row(Field, "Deaths");	PlayerInfo[playerid][pDeaths] = strval(Field);
	mysql_fetch_field_row(Field, "Accident");	PlayerInfo[playerid][pAccident] = strval(Field);
	mysql_fetch_field_row(Field, "Ticket");	PlayerInfo[playerid][pTicket] = strval(Field);
	mysql_fetch_field_row(Field, "Crimes");	PlayerInfo[playerid][pCrimes] = strval(Field);
	mysql_fetch_field_row(Field, "Arrested"); PlayerInfo[playerid][pArrested] = strval(Field);
	mysql_fetch_field_row(Field, "WantedDeaths");	PlayerInfo[playerid][pWantedDeaths] = strval(Field);
	mysql_fetch_field_row(Field, "Wanted");	 WantedPoints[playerid] = strval(Field);
	mysql_fetch_field_row(Field, "Article");	PlayerInfo[playerid][pArticle] = strval(Field);
	mysql_fetch_field_row(Field, "Part");	PlayerInfo[playerid][pPart] = strval(Field);
	mysql_fetch_field_row(Field, "Jailed");	PlayerInfo[playerid][pJailed] = strval(Field);
	mysql_fetch_field_row(Field, "JailTime");	PlayerInfo[playerid][pJailTime] = strval(Field);
	mysql_fetch_field_row(Field, "JailPrice");	PlayerInfo[playerid][pJailPrice] = strval(Field);
	mysql_fetch_field_row(Field, "UpgradePoints");	PlayerInfo[playerid][pPupgrade] = strval(Field);

	new Perks[11];
	mysql_fetch_field_row(Perks, "Perks");
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

	mysql_fetch_field_row(Field, "STD"); PlayerInfo[playerid][pSTD] = strval(Field);
	if(PlayerInfo[playerid][pSTD] == IsNotBeenIll) PlayerInfo[playerid][pSTD] = 0;

	new PlayerItems[11];
	mysql_fetch_field_row(PlayerItems, "PlayerItems");
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
	mysql_fetch_field_row(VehicleItems, "VehicleItems");
	PlayerInfo[playerid][pAntiradar] = VehicleItems[0]-'0';
	PlayerInfo[playerid][pGPS] = VehicleItems[1]-'0';
	PlayerInfo[playerid][pCDPlayer] = VehicleItems[2]-'0';
	PlayerInfo[playerid][pFuel] = VehicleItems[3]-'0';

	//mysql_fetch_field_row(Field, "Antiradar");	PlayerInfo[playerid][pAntiradar] = strval(Field);
	//mysql_fetch_field_row(Field, "GPS");	PlayerInfo[playerid][pGPS] = strval(Field);
	//mysql_fetch_field_row(Field, "CDPlayer");	PlayerInfo[playerid][pCDPlayer] = strval(Field);

	//mysql_fetch_field_row(Field, "Dice");	PlayerInfo[playerid][pDice] = strval(Field);
	mysql_fetch_field_row(Field, "Drugs");	PlayerInfo[playerid][pDrugs] = strval(Field);
	//mysql_fetch_field_row(Field, "Cigars");	PlayerInfo[playerid][pCigars] = strval(Field);
	//mysql_fetch_field_row(Field, "Fishes");	PlayerInfo[playerid][pFishes] = strval(Field);
	//mysql_fetch_field_row(Field, "Fuel");	PlayerInfo[playerid][pFuel] = strval(Field);
	mysql_fetch_field_row(Field, "LottoNr");	PlayerInfo[playerid][pLottoNr] = strval(Field);
	mysql_fetch_field_row(Field, "Materials");	PlayerInfo[playerid][pMats] = strval(Field);
	mysql_fetch_field_row(Field, "Mushroom");	PlayerInfo[playerid][pMushroom] = strval(Field);
	mysql_fetch_field_row(Field, "PhoneNr");	PlayerInfo[playerid][pPnumber] = strval(Field);
	mysql_fetch_field_row(Field, "Helmet");	PlayerInfo[playerid][pHelmet] = strval(Field);

	mysql_fetch_field_row(Field, "Married");	PlayerInfo[playerid][pMarried] = strval(Field);
	mysql_fetch_field_row(PlayerInfo[playerid][pMarriedTo], "MarriedTo");
//mysql_fetch_field_row(Field, "Offline");	PlayerInfo[playerid][pOffline] = strval(Field);//не загружать, т.к. при входе он инициализируется
	mysql_fetch_field_row(Field, "Reason");		PlayerInfo[playerid][pReason] = strval(Field);
	mysql_fetch_field_row(Field, "CarTime");	PlayerInfo[playerid][pCarTime] = strval(Field);
	mysql_fetch_field_row(Field, "Tutorial");	PlayerInfo[playerid][pTut] = strval(Field);
	mysql_fetch_field_row(Field, "Vote");		PlayerInfo[playerid][pVote] = strval(Field);
	mysql_fetch_field_row(Field, "PurposeMurder");	PlayerInfo[playerid][pPurposeMurder] = strval(Field);
	mysql_fetch_field_row(PlayerInfo[playerid][pReferal], "Referal");
	//mysql_fetch_field_row(Field, "Passport");		PlayerInfo[playerid][pPassport] = strval(Field);
	mysql_fetch_field_row(Field, "Online");		PlayerInfo[playerid][pOnline] = strval(Field);
	mysql_fetch_field_row(Field, "Score");		PlayerInfo[playerid][pScore] = strval(Field);

	mysql_fetch_field_row(Field, "Param1");		PlayerInfo[playerid][pParam1] = strval(Field);
	mysql_fetch_field_row(Field, "Param2");		PlayerInfo[playerid][pParam2] = strval(Field);
	mysql_fetch_field_row(Field, "Param3");		PlayerInfo[playerid][pParam3] = strval(Field);
	mysql_fetch_field_row(Field, "Param4");		PlayerInfo[playerid][pParam4] = strval(Field);
	mysql_fetch_field_row(Field, "Param5");		PlayerInfo[playerid][pParam5] = strval(Field);

	//PlayerInfo[playerid][pTut] = 0;
	//mysql_free_result();//!!! Не трогать

	//ИНФОРМИРОВАНИЕ
	/*if(!IsPlayerConnected(playerid))
	{
	    //new strings[MAX_STRING];
		format(strings, sizeof(strings), "OnPlayerLoadParameters(offline player:%s[%d])", nameplayer, playerid);
		Log(OFFLINE, strings);
	}*/
	return 1;
}

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
	{
		format(ToBase, sizeof(ToBase), "%s WHERE `ID`=%d LIMIT 1", ToBase, PlayerInfo[playerid][pSQLID]);
	}
	else
	{
		format(ToBase, sizeof(ToBase), "%s WHERE `Name`='%s' LIMIT 1", ToBase, nameplayer);
	}
	mysql_query(ToBase);

	if(PlayerInfo[playerid][pAdmin] >= 6)
	{
		new strtmp[64];//30+24+10 = 64
		format(strtmp, sizeof(strtmp), "OnPlayerSaveParameters %s[%d] ip:%s", nameplayer, PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pIP]);
		SendClientMessage(playerid, COLOR_YELLOW, strtmp);
		TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

		format(strings, sizeof(strings), "Int:%d, Virt:%d, Loc:%d, X:%.1f, Y:%.1f, Z:%.1f",
			PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual],	PlayerInfo[playerid][pLocal],
			PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
			//CurPos[0][playerid], CurPos[1][playerid], CurPos[2][playerid]);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	//return 1;
}

/*
stock OnPlayerLoadTempParameters(playerid, const nameplayer[])//вызывается по команде /showplayerstats
{
	new ToBase[125 + 24+20];
	format(ToBase, sizeof(ToBase), "SELECT * FROM `players_temp` WHERE `Name` = '%s' LIMIT 1", nameplayer);//playername);
	mysql_query(ToBase); mysql_store_result();
	if(mysql_num_rows() > 0 && mysql_retrieve_row())
	{
		new Field[20];//длина самого большого параметра
		mysql_fetch_field_row(Field, "ID"); PlayerInfo[playerid][pSQLID] = strval(Field);

		mysql_fetch_field_row(Field, "Account");	PlayerInfo[playerid][pAccount] = strval(Field);
		mysql_fetch_field_row(Field, "Muted");	PlayerInfo[playerid][pMuted] = strval(Field);
		mysql_fetch_field_row(Field, "Warns");	PlayerInfo[playerid][pWarns] = strval(Field);
		mysql_fetch_field_row(Field, "RespectDay");	PlayerInfo[playerid][pRespectDay] = strval(Field);
		mysql_fetch_field_row(Field, "PayCheck");	PlayerInfo[playerid][pPayCheck] = strval(Field);
		mysql_fetch_field_row(Field, "PayDay");	PlayerInfo[playerid][pPayTime] = strval(Field);
		mysql_fetch_field_row(Field, "Health");	PlayerInfo[playerid][pHealth] = floatstr(Field);
		mysql_fetch_field_row(Field, "Interior");	PlayerInfo[playerid][pInt] = strval(Field);
		mysql_fetch_field_row(Field, "Pos_x");	PlayerInfo[playerid][pPos_x] = floatstr(Field);
		mysql_fetch_field_row(Field, "Pos_y");	PlayerInfo[playerid][pPos_y] = floatstr(Field);
		mysql_fetch_field_row(Field, "Pos_z");	PlayerInfo[playerid][pPos_z] = floatstr(Field);
		mysql_fetch_field_row(Field, "Virtual");	PlayerInfo[playerid][pVirtual] = strval(Field);
		mysql_fetch_field_row(Field, "Local");	PlayerInfo[playerid][pLocal] = strval(Field);
		mysql_fetch_field_row(Field, "House");	PlayerInfo[playerid][pHouse] = strval(Field);
		mysql_fetch_field_row(Field, "Bizz");	PlayerInfo[playerid][pBizz] = strval(Field);
		mysql_fetch_field_row(Field, "ContractTime");	PlayerInfo[playerid][pContractTime] = strval(Field);

		mysql_fetch_field_row(Field, "HeadValue");	PlayerInfo[playerid][pHeadValue] = strval(Field);
		mysql_fetch_field_row(Field, "Wanted");	 WantedPoints[playerid] = strval(Field);

		mysql_fetch_field_row(Field, "STD");	PlayerInfo[playerid][pSTD] = strval(Field);

		mysql_fetch_field_row(Field, "Reason");		PlayerInfo[playerid][pReason] = strval(Field);
		mysql_fetch_field_row(Field, "CarTime");	PlayerInfo[playerid][pCarTime] = strval(Field);
		mysql_fetch_field_row(Field, "Vote");		PlayerInfo[playerid][pVote] = strval(Field);
		mysql_fetch_field_row(Field, "PurposeMurder");	PlayerInfo[playerid][pPurposeMurder] = strval(Field);
		mysql_fetch_field_row(PlayerInfo[playerid][pReferal], "Referal");

		mysql_fetch_field_row(Field, "Param1");		PlayerInfo[playerid][pParam1] = strval(Field);
		mysql_fetch_field_row(Field, "Param2");		PlayerInfo[playerid][pParam2] = strval(Field);
		mysql_fetch_field_row(Field, "Param3");		PlayerInfo[playerid][pParam3] = strval(Field);
		mysql_fetch_field_row(Field, "Param4");		PlayerInfo[playerid][pParam4] = strval(Field);
		mysql_fetch_field_row(Field, "Param5");		PlayerInfo[playerid][pParam5] = strval(Field);
	}
	mysql_free_result();
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
	mysql_query(ToBase);

	return 1;
}
*/

stock LoadCarSQL()
{
	new time = GetTickCount();
	new carid = 1;//356+131 +
	new Data[11 + 3+4+10+24+6*4+2+10+1+3+4+10 +3+5+3+3+3+3+4*15+6+10+10+4+4 + 12];
	new Field[24];
	mysql_query("SELECT * FROM `vehicles`");	mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		//if(carid >= MAX_VEHICLES-1) break;//для предотвращения переполнения массива mysql_num_rows()
		mysql_fetch_field_row(Field, "IND"); VehInfo[carid][cIND] = strval(Field);
		mysql_fetch_field_row(Field, "Model"); VehInfo[carid][cModel] = strval(Field);
		//if(VehInfo[carid][cModel] < 400) continue;
		mysql_fetch_field_row(Field, "Type"); VehInfo[carid][cType] = strval(Field);
		mysql_fetch_field_row(Field, "Owned"); VehInfo[carid][cOwned] = strval(Field);
		mysql_fetch_field_row(Field, "Owner"); strmid(VehInfo[carid][cOwner], Field, 0, strlen(Field), 24);
		mysql_fetch_field_row(Field, "LocX"); VehInfo[carid][cLocX] = floatstr(Field);
		mysql_fetch_field_row(Field, "LocY"); VehInfo[carid][cLocY] = floatstr(Field);
		mysql_fetch_field_row(Field, "LocZ"); VehInfo[carid][cLocZ] = floatstr(Field);
		mysql_fetch_field_row(Field, "Ang"); VehInfo[carid][cAng] = floatstr(Field);
		mysql_fetch_field_row(Field, "Int"); VehInfo[carid][cInt] = strval(Field);
		mysql_fetch_field_row(Field, "Virt"); VehInfo[carid][cVirt] = strval(Field);
		mysql_fetch_field_row(Field, "Lock"); VehInfo[carid][cLock] = strval(Field);

		mysql_fetch_field_row(Field, "Park"); VehInfo[carid][cPark] = strval(Field);
		mysql_fetch_field_row(Field, "Attach"); VehInfo[carid][cAttach] = strval(Field);
		mysql_fetch_field_row(Field, "Insur"); VehInfo[carid][cInsur] = strval(Field);

		mysql_fetch_field_row(Field, "Fuel"); VehInfo[carid][cFuel] = float(strval(Field));
		mysql_fetch_field_row(Field, "Load"); VehInfo[carid][cLoad] = strval(Field);
		mysql_fetch_field_row(Field, "LoadType"); VehInfo[carid][cLoadType] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); VehInfo[carid][cDate] = strval(Field);
		mysql_fetch_field_row(Field, "Color1"); VehInfo[carid][cColor1] = strval(Field);
		mysql_fetch_field_row(Field, "Color2"); VehInfo[carid][cColor2] = strval(Field);
		mysql_fetch_field_row(Field, "Paintjob"); VehInfo[carid][cPaintjob] = strval(Field);
		mysql_fetch_field_row(Field, "Spoiler"); VehInfo[carid][cSpoiler] = strval(Field);
		mysql_fetch_field_row(Field, "Hood"); VehInfo[carid][cHood] = strval(Field);
		mysql_fetch_field_row(Field, "Roof"); VehInfo[carid][cRoof] = strval(Field);
		mysql_fetch_field_row(Field, "Sideskirt"); VehInfo[carid][cSideskirt] = strval(Field);
		mysql_fetch_field_row(Field, "Lamps"); VehInfo[carid][cLamps] = strval(Field);
		mysql_fetch_field_row(Field, "Nitro"); VehInfo[carid][cNitro] = strval(Field);
		mysql_fetch_field_row(Field, "Exhaust"); VehInfo[carid][cExhaust] = strval(Field);
		mysql_fetch_field_row(Field, "Wheels"); VehInfo[carid][cWheels] = strval(Field);
		mysql_fetch_field_row(Field, "Stereos"); VehInfo[carid][cStereos] = strval(Field);
		mysql_fetch_field_row(Field, "Hydraulics"); VehInfo[carid][cHydraulics] = strval(Field);
		mysql_fetch_field_row(Field, "FrontBumper"); VehInfo[carid][cFrontBumper] = strval(Field);
		mysql_fetch_field_row(Field, "RearBumper"); VehInfo[carid][cRearBumper] = strval(Field);
		mysql_fetch_field_row(Field, "VentRight"); VehInfo[carid][cVentRight] = strval(Field);
		mysql_fetch_field_row(Field, "VentLeft"); VehInfo[carid][cVentLeft] = strval(Field);
		mysql_fetch_field_row(Field, "Health"); VehInfo[carid][cHealth] = floatstr(Field); VehHealth[carid] = VehInfo[carid][cHealth];
		mysql_fetch_field_row(Field, "Panels"); VehInfo[carid][DamagePanels] = strval(Field);
		mysql_fetch_field_row(Field, "Doors"); VehInfo[carid][DamageDoors] = strval(Field);
		mysql_fetch_field_row(Field, "Lights"); VehInfo[carid][DamageLights] = strval(Field);
		mysql_fetch_field_row(Field, "Tires"); VehInfo[carid][DamageTires] = strval(Field);
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
		    number3D[vehicleid] = Create3DTextLabel(numberplate,0xEEEEEE50,0.0,0.0,0.0,15.0,0,1);
		    Counter3DText ++;
		    Attach3DTextLabelToVehicle(number3D[vehicleid], vehicleid, 0.0, -1.6, -0.35);

			if(VehInfo[carid][cPark] >= 100 && VehInfo[carid][cPark] < 1000)// && PlayerInfo[playerid][pSQLID] == VehInfo[carid][cOwned]
			{
				new text[39+10];
		   		format(text, sizeof(text), " Сдаётся.\n{FFFFFF}Цена: {33AA33}$%d", VehInfo[carid][cPark]);
			    sale3D[carid] = Create3DTextLabel(text, COLOR_LIGHTBLUE, 0.0,0.0,0.0, 50.0,0,1);
			    Counter3DText ++;
			    Attach3DTextLabelToVehicle(sale3D[carid], carid, 0.0, 0.0, 1.0);
			}
			else if(VehInfo[carid][cPark] >= 1000)// && PlayerInfo[playerid][pSQLID] == VehInfo[carid][cOwned]
			{
				new text[39+10];
		   		format(text, sizeof(text), " Продаётся.\n{FFFFFF}Цена: {33AA33}$%d", VehInfo[carid][cPark]);
			    sale3D[carid] = Create3DTextLabel(text, COLOR_LIGHTBLUE, 0.0,0.0,0.0, 50.0,0,1);
			    Counter3DText ++;
			    Attach3DTextLabelToVehicle(sale3D[carid], carid, 0.0, 0.0, 1.0);
			}
	    }

		if(VehInfo[carid][cPark] >= PARKING && VehInfo[carid][cPark] < PARKING+sizeof(Parking))
		{
			SBizInfo[VehInfo[carid][cPark]][sbProducts] ++;
		}

		VehInfo[carid][cID] = vehicleid;
		new ToBase[45+4+11];
		format(ToBase, sizeof(ToBase), "UPDATE `vehicles` SET `ID`=%d WHERE `IND`=%d LIMIT 1", VehInfo[carid][cID], VehInfo[carid][cIND]);
		mysql_query(ToBase);

		LinkVehicleToInterior(vehicleid, VehInfo[vehicleid][cInt]);
		SetVehicleVirtualWorld(vehicleid, VehInfo[vehicleid][cVirt]);
//printf("id: %d", carid);
		carid ++;
	}
	mysql_free_result();
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
Tires=%d WHERE `IND`=%d LIMIT 1",ToBase,
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
		mysql_query(ToBase);
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
	mysql_query(ToBase);

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
	mysql_query(ToBase);

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



stock sql_OnPlayerDisconnect(playerid)
{
	//для монитора
	PlayerInfo[playerid][pOffline] = getdate();//записали день выхода с серва
//TestLog(OPTIM, "OnPlayerDisconnect1.1", GetTickCount(), timers, 1);
	new ToBase[87];//60 + 3+24 = 87
    if(PlayerInfo[playerid][pSQLID] > 0)
    {
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `ID`=%d LIMIT 1",
			PlayerInfo[playerid][pOffline], PlayerInfo[playerid][pSQLID]);
	}
	else
	{
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `Name`='%s' LIMIT 1",
			PlayerInfo[playerid][pOffline], PlayerName(playerid));
	}
	mysql_query(ToBase);
}






///#############################################################################





stock LoadHousesSQL()//вызывается из функции 4
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new time = GetTickCount();
	new idx;	//235+118 +
	new Data[1+24 + 20+2+6+6+6+2+6+6+6 + 1+6+6+6 + 1+6+6+6 + 1 + 7+2+1+1+6+10+2+3 + 12];
	new Field[24];
	//mysql_query("SELECT * FROM `house`");	mysql_store_result();
	mysql_query("SELECT Owned,Owner,Hel,Arm,TV,`Lock`,Rent,Till,Paper,Date FROM `house`");	mysql_store_result();
	//while(mysql_fetch_row_format(Data, "|", connectHandle))//Функция служит для обработки полной строки из результата запроса
	while(mysql_fetch_row_format(Data, "|"))//Функция служит для обработки полной строки из результата запроса
	{   //пока функция возвращает true
		if(idx >= MAX_HOUSE) break;
		mysql_fetch_field_row(Field, "Owned"); HouseInfo[idx][hOwned] = strval(Field);
		mysql_fetch_field_row(HouseInfo[idx][hOwner], "Owner"); //strmid(HouseInfo[idx][hOwner], Field, 0, strlen(Field), 24);
//new stringLength = strlen("This is an example strings."); // stringLength is now set to 26
		//mysql_fetch_field_row(Field, "Discription"); strmid(HouseInfo[idx][hDiscription], Field, 0, strlen(Field), 20);
		//mysql_fetch_field_row(Field, "Rooms"); HouseInfo[idx][hRooms] = strval(Field);
		//mysql_fetch_field_row(Field, "EntranceX"); HouseInfo[idx][hEntranceX] = floatstr(Field);
		//mysql_fetch_field_row(Field, "EntranceY"); HouseInfo[idx][hEntranceY] = floatstr(Field);
		//mysql_fetch_field_row(Field, "EntranceZ"); HouseInfo[idx][hEntranceZ] = floatstr(Field);
		//mysql_fetch_field_row(Field, "Int"); HouseInfo[idx][hInt] = strval(Field);
		//mysql_fetch_field_row(Field, "ExitX"); HouseInfo[idx][hExitX] = floatstr(Field);
		//mysql_fetch_field_row(Field, "ExitY"); HouseInfo[idx][hExitY] = floatstr(Field);
		//mysql_fetch_field_row(Field, "ExitZ"); HouseInfo[idx][hExitZ] = floatstr(Field);
		mysql_fetch_field_row(Field, "Hel"); HouseInfo[idx][hHel] = strval(Field);
		//mysql_fetch_field_row(Field, "HealthX"); HouseInfo[idx][hClothExX] = floatstr(Field);
		//mysql_fetch_field_row(Field, "HealthY"); HouseInfo[idx][hClothExY] = floatstr(Field);
		//mysql_fetch_field_row(Field, "HealthZ"); HouseInfo[idx][hClothExZ] = floatstr(Field);
		mysql_fetch_field_row(Field, "Arm"); HouseInfo[idx][hCloth] = strval(Field);
		//mysql_fetch_field_row(Field, "ArmourX"); HouseInfo[idx][hClothEntX] = floatstr(Field);
		//mysql_fetch_field_row(Field, "ArmourY"); HouseInfo[idx][hClothEntY] = floatstr(Field);
		//mysql_fetch_field_row(Field, "ArmourZ"); HouseInfo[idx][hClothEntZ] = floatstr(Field);
		mysql_fetch_field_row(Field, "TV"); HouseInfo[idx][hTV] = strval(Field);
		//mysql_fetch_field_row(Field, "BuyPrice"); HouseInfo[idx][hBuyPrice] = strval(Field);
		//mysql_fetch_field_row(Field, "Level"); HouseInfo[idx][hLevel] = strval(Field);
		mysql_fetch_field_row(Field, "Lock"); HouseInfo[idx][hLock] = strval(Field);
		//mysql_fetch_field_row(Field, "Rentabil"); HouseInfo[idx][hRentabil] = strval(Field);
		mysql_fetch_field_row(Field, "Rent"); HouseInfo[idx][hRent] = strval(Field);
		mysql_fetch_field_row(Field, "Till"); HouseInfo[idx][hTill] = strval(Field);
		mysql_fetch_field_row(Field, "Paper"); HouseInfo[idx][hPaper] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); HouseInfo[idx][hDate] = strval(Field);
		idx ++;
	}
	mysql_free_result();
	printf("2/19. [Загрузка домов]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock HouseInfo_SaveAllSQL()//SaveHousesSQL()//вызывается из OnCheckProp, /rentcar
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
`Date`=%d WHERE ID=%d LIMIT 1",
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
		mysql_query(ToBase); //mysql_free_result();
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
		`Date`=%d WHERE ID=%d LIMIT 1",
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
	mysql_query(ToBase); //mysql_free_result();

	new strtmp[67+2+6];
	format(strtmp, sizeof(strtmp), "Сохранение дома №%d успешно завершено. Потрачено - %d (ms)", house, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}//End SaveHouse()



stock LoadBizSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new time = GetTickCount();
	new idx;
	new Data[234+12];//11+11+24+3+20+6*3+2+6*3+7+2+1+6+10*6+3+3+10+3+6+3+10+10+3 = 234
	new Field[24];
	mysql_query("SELECT * FROM `bizz`");
	mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= MAX_BIZ) break;
		mysql_fetch_field_row(Field, "Owned"); BizInfo[idx][bOwned] = strval(Field);
		mysql_fetch_field_row(BizInfo[idx][bOwner], "Owner");
		//mysql_fetch_field_row(BizInfo[idx][bExtortion], "Extortion");
		mysql_fetch_field_row(Field, "Extortion"); BizInfo[idx][bExtortion] = strval(Field);

//чтобы не загружались из базы, т.к. исправлено только в моде
//mysql_fetch_field_row(Field, "Discription"); strmid(BizInfo[idx][bDiscription], Field, 0, strlen(Field), 20);
		/*if(idx == 66)
		{
			mysql_fetch_field_row(Field, "EntranceX"); BizInfo[idx][bEntranceX] = floatstr(Field);
			mysql_fetch_field_row(Field, "EntranceY"); BizInfo[idx][bEntranceY] = floatstr(Field);
			mysql_fetch_field_row(Field, "EntranceZ"); BizInfo[idx][bEntranceZ] = floatstr(Field);
			//BizInfo[idx][bEntranceA] = floatstr(Field);//угол взгляда после выхода из интерьера

			//mysql_fetch_field_row(Field, "Int"); BizInfo[idx][bInt] = strval(Field);
			//mysql_fetch_field_row(Field, "ExitX"); BizInfo[idx][bExitX] = strval(Field);
			//mysql_fetch_field_row(Field, "ExitY"); BizInfo[idx][bExitY] = strval(Field);
			//mysql_fetch_field_row(Field, "ExitZ"); BizInfo[idx][bExitZ] = strval(Field);
			//BizInfo[idx][bExitA] = strval(Field);//угол взгляда после входа в интерьер
		}*/
//mysql_fetch_field_row(Field, "BuyPrice"); BizInfo[idx][bBuyPrice] = strval(Field);

		mysql_fetch_field_row(Field, "Level"); BizInfo[idx][bLevel] = strval(Field);
//закоментировать, чтобы сбросить уровень до 1
		mysql_fetch_field_row(Field, "Lock"); BizInfo[idx][bLock] = strval(Field);
		mysql_fetch_field_row(Field, "EntranceCost"); BizInfo[idx][bEntranceCost] = strval(Field);

		/*mysql_fetch_field_row(Field, "Metal"); BizInfo[idx][bMetal] = strval(Field);
		mysql_fetch_field_row(Field, "Textiles"); BizInfo[idx][bTextiles] = strval(Field);
		mysql_fetch_field_row(Field, "Provisions"); BizInfo[idx][bProvisions] = strval(Field);
		mysql_fetch_field_row(Field, "Tree"); BizInfo[idx][bTree] = strval(Field);
		mysql_fetch_field_row(Field, "Fuel"); BizInfo[idx][bFuel] = strval(Field);*/

		mysql_fetch_field_row(Field, "Products"); BizInfo[idx][bProducts] = strval(Field);
		mysql_fetch_field_row(Field, "BuyProd"); BizInfo[idx][bBuyProd] = strval(Field);
		mysql_fetch_field_row(Field, "SellProd"); BizInfo[idx][bSellProd] = strval(Field);
		mysql_fetch_field_row(Field, "Till"); BizInfo[idx][bTill] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); BizInfo[idx][bDate] = strval(Field);
		mysql_fetch_field_row(Field, "Inkas"); BizInfo[idx][bInkas] = strval(Field);

		//mysql_fetch_field_row(Field, "Worker"); BizInfo[idx][bWorker] = strval(Field);
		mysql_fetch_field_row(Field, "Import"); BizInfo[idx][bImport] = strval(Field);
		mysql_fetch_field_row(Field, "Export"); BizInfo[idx][bExport] = strval(Field);
		mysql_fetch_field_row(Field, "Salary"); BizInfo[idx][bSalary] = strval(Field);
		idx ++;
	}
	mysql_free_result();
	//compcost = BizInfo[81][bSalary];
	printf("3/19. [Загрузка бизнесов]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock SaveBizSQL()//вызывается каждый час и при рестарте мода
{   //для сохранения параметров бизов, машин
	new time = GetTickCount();
	new ToBase[704];
	//new ToBase[672+12];//438 + 11+11+24+3+20+6*3+2+6*3+7+2+1+6+10*6+3+3+10+3+6+3+10+10+3 = 672
	for(new idx=0; idx<MAX_BIZ; idx++)
	{
		BizInfo[idx][bLevel] = GetBizLevel(idx);
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
Salary=%d WHERE `ID`=%d LIMIT 1",
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

		/*format(ToBase, sizeof(ToBase), "UPDATE `bizz` SET Owned=%d,\
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
Products=%d,\
BuyProd=%d,\
SellProd=%d,\
Till=%d,\
`Date`=%d,\
Inkas=%d,\
`Worker`=%d,\
Import=%d,\
Export=%d,\
Salary=%d WHERE `ID`=%d LIMIT 1",
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
			idx+1);*/
//printf("Biz:%d, Discription: %s", idx,BizInfo[idx][bDiscription]);
		mysql_query(ToBase);
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
Salary=%d WHERE `ID`=%d LIMIT 1",
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
Salary=%d WHERE `ID`=%d LIMIT 1",
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
	mysql_query(ToBase); //mysql_free_result();

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
	new Data[1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+ 10*5 +3+3+6+10+3+1 + 3+10+10+2 + 12];
	new Field[24];
	//mysql_query("SELECT * FROM `sbizz`");	mysql_store_result();
	mysql_query("SELECT * FROM `sbizz`");	mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= MAX_SBIZ) break;//MAX_SBIZ //GAS_STATION
		mysql_fetch_field_row(Field, "Owned"); SBizInfo[idx][sbOwned] = strval(Field);
		mysql_fetch_field_row(SBizInfo[idx][sbOwner], "Owner"); //strmid(SBizInfo[idx][sbOwner], Field, 0, strlen(Field), 24);
		//mysql_fetch_field_row(SBizInfo[idx][sbExtortion], "Extortion");
		mysql_fetch_field_row(Field, "Extortion"); SBizInfo[idx][sbExtortion] = strval(Field);

//mysql_fetch_field_row(Field, "Discription"); strmid(SBizInfo[idx][sbDiscription], Field, 0, strlen(Field), 20);
//mysql_fetch_field_row(Field, "EntranceX"); SBizInfo[idx][sbEntranceX] = floatstr(Field);
//mysql_fetch_field_row(Field, "EntranceY"); SBizInfo[idx][sbEntranceY] = floatstr(Field);
//mysql_fetch_field_row(Field, "EntranceZ"); SBizInfo[idx][sbEntranceZ] = floatstr(Field);
//mysql_fetch_field_row(Field, "BuyPrice"); SBizInfo[idx][sbBuyPrice] = strval(Field);

		mysql_fetch_field_row(Field, "Level"); SBizInfo[idx][sbLevel] = strval(Field);
//закоментировать, чтобы сбросить уровень до 1
		mysql_fetch_field_row(Field, "Lock"); SBizInfo[idx][sbLock] = strval(Field);
		mysql_fetch_field_row(Field, "EntranceCost"); SBizInfo[idx][sbEntranceCost] = strval(Field);

		mysql_fetch_field_row(Field, "Products"); SBizInfo[idx][sbProducts] = strval(Field);
		if(idx >= PARKING && idx < PARKING+sizeof(Parking))
		{
			SBizInfo[idx][sbProducts] = 0;
		}

		mysql_fetch_field_row(Field, "BuyProd"); SBizInfo[idx][sbBuyProd] = strval(Field);
		mysql_fetch_field_row(Field, "SellProd"); SBizInfo[idx][sbSellProd] = strval(Field);
		mysql_fetch_field_row(Field, "Till"); SBizInfo[idx][sbTill] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); SBizInfo[idx][sbDate] = strval(Field);
		mysql_fetch_field_row(Field, "Inkas"); SBizInfo[idx][sbInkas] = strval(Field);

		//mysql_fetch_field_row(Field, "Worker"); SBizInfo[idx][sbWorker] = strval(Field);
		mysql_fetch_field_row(Field, "Import"); SBizInfo[idx][sbImport] = strval(Field);
		mysql_fetch_field_row(Field, "Export"); SBizInfo[idx][sbExport] = strval(Field);
		mysql_fetch_field_row(Field, "Salary"); SBizInfo[idx][sbSalary] = strval(Field);
		idx ++;
	}
	mysql_free_result();
	printf("4/19. [Загрузка компаний]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
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
Salary=%d WHERE `ID`=%d LIMIT 1",
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
		mysql_query(ToBase); //mysql_free_result();
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
Inkas=%d WHERE `ID`=%d LIMIT 1",
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
	mysql_query(ToBase); //mysql_free_result();
	//ИНФОРМИРОВАНИЕ
	new strtmp[67+2+6];
	format(strtmp, sizeof(strtmp), "Сохранение биз-компании №%d успешно завершено. Потрачено - %d (ms)", sbouse, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}



stock LoadGasStationSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрухка property.cfg
	new idx = GAS_STATION;//198+88 +
	new Data[1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3+1 + 12];
	new Field[24];
	mysql_query("SELECT * FROM `gas`");	mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= PARKING) break;
		mysql_fetch_field_row(Field, "Owned"); SBizInfo[idx][sbOwned] = strval(Field);
		mysql_fetch_field_row(SBizInfo[idx][sbOwner], "Owner"); //strmid(SBizInfo[idx][sbOwner], Field, 0, strlen(Field), 24);
		mysql_fetch_field_row(SBizInfo[idx][sbExtortion], "Extortion"); //strmid(SBizInfo[idx][sbExtortion], Field, 0, strlen(Field), 20);
		//mysql_fetch_field_row(Field, "Discription"); strmid(SBizInfo[idx][sbDiscription], Field, 0, strlen(Field), 20);
		//mysql_fetch_field_row(Field, "EntranceX"); SBizInfo[idx][sbEntranceX] = floatstr(Field);
		//mysql_fetch_field_row(Field, "EntranceY"); SBizInfo[idx][sbEntranceY] = floatstr(Field);
		//mysql_fetch_field_row(Field, "EntranceZ"); SBizInfo[idx][sbEntranceZ] = floatstr(Field);
		//mysql_fetch_field_row(Field, "BuyPrice"); SBizInfo[idx][sbBuyPrice] = strval(Field);
		//mysql_fetch_field_row(Field, "Level"); SBizInfo[idx][sbLevel] = strval(Field);
		mysql_fetch_field_row(Field, "Lock"); SBizInfo[idx][sbLock] = strval(Field);
		mysql_fetch_field_row(Field, "EntranceCost"); SBizInfo[idx][sbEntranceCost] = strval(Field);
		mysql_fetch_field_row(Field, "Products"); SBizInfo[idx][sbProducts] = strval(Field);
		mysql_fetch_field_row(Field, "BuyProd"); SBizInfo[idx][sbBuyProd] = strval(Field);
		mysql_fetch_field_row(Field, "SellProd"); SBizInfo[idx][sbSellProd] = strval(Field);
		mysql_fetch_field_row(Field, "Till"); SBizInfo[idx][sbTill] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); SBizInfo[idx][sbDate] = strval(Field);
		mysql_fetch_field_row(Field, "Inkas"); SBizInfo[idx][sbInkas] = strval(Field);
		idx ++;
	}
	mysql_free_result();
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
		mysql_query(ToBase); //mysql_free_result();
	}
	//ИНФОРМИРОВАНИЕ
	SendAllAdminMessage( COLOR_RESTARTING, "Сохранение АЗС успешно завершено", 1);
}


stock LoadParkingSQL()//вызывается из функции GameModeInit
{   //загрузка параметров домов и машин, т.е. загрузка property.cfg
	new idx = PARKING;//198+88 +
	new Data[1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3+1 + 12];
	new Field[24];
	mysql_query("SELECT * FROM `gas`");	mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx >= PARKING+sizeof(Parking)) break;
		mysql_fetch_field_row(Field, "Owned"); SBizInfo[idx][sbOwned] = strval(Field);
		mysql_fetch_field_row(SBizInfo[idx][sbOwner], "Owner"); //strmid(SBizInfo[idx][sbOwner], Field, 0, strlen(Field), 24);
		mysql_fetch_field_row(SBizInfo[idx][sbExtortion], "Extortion"); //strmid(SBizInfo[idx][sbExtortion], Field, 0, strlen(Field), 20);
		//mysql_fetch_field_row(Field, "Discription"); strmid(SBizInfo[idx][sbDiscription], Field, 0, strlen(Field), 20);
		//mysql_fetch_field_row(Field, "EntranceX"); SBizInfo[idx][sbEntranceX] = floatstr(Field);
		//mysql_fetch_field_row(Field, "EntranceY"); SBizInfo[idx][sbEntranceY] = floatstr(Field);
		//mysql_fetch_field_row(Field, "EntranceZ"); SBizInfo[idx][sbEntranceZ] = floatstr(Field);
		//mysql_fetch_field_row(Field, "BuyPrice"); SBizInfo[idx][sbBuyPrice] = strval(Field);
		//mysql_fetch_field_row(Field, "Level"); SBizInfo[idx][sbLevel] = strval(Field);
		mysql_fetch_field_row(Field, "Lock"); SBizInfo[idx][sbLock] = strval(Field);
		mysql_fetch_field_row(Field, "EntranceCost"); SBizInfo[idx][sbEntranceCost] = strval(Field);
		mysql_fetch_field_row(Field, "Products"); SBizInfo[idx][sbProducts] = strval(Field);
		mysql_fetch_field_row(Field, "BuyProd"); SBizInfo[idx][sbBuyProd] = strval(Field);
		mysql_fetch_field_row(Field, "SellProd"); SBizInfo[idx][sbSellProd] = strval(Field);
		mysql_fetch_field_row(Field, "Till"); SBizInfo[idx][sbTill] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); SBizInfo[idx][sbDate] = strval(Field);
		mysql_fetch_field_row(Field, "Inkas"); SBizInfo[idx][sbInkas] = strval(Field);
		idx ++;
	}
	mysql_free_result();
}
stock SaveParkingSQL()//вызывается при рестарте мода и каждый час
{   //для сохранения бизов, машин

	new ToBase[299 + 1+24 + 20+20 + 6+6+6+2 + 7+2 + 1+6+3+3+6+10+3 + 12];
	for(new idx = PARKING; idx < PARKING+sizeof(Parking); idx++)
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
		mysql_query(ToBase); //mysql_free_result();
	}
	//ИНФОРМИРОВАНИЕ
	SendAllAdminMessage( COLOR_RESTARTING, "Сохранение Паркинга успешно завершено", 1);
}


#if defined vw_sql//#endif

stock LoadFamiliesSQL()//для банд
{
	new time = GetTickCount();
	new idx=1;//=TEAM_MAFIA+1;
	new Data[2+24+128+24+2+6*4+2+3+3+10+3*2+2 + 12];//182 +
	new Field[128];
	mysql_query("SELECT * FROM `families`"); mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx > mysql_num_rows()) break;//sizeof(FamilyInfo)
		mysql_fetch_field_row(Field, "ID"); FamilyInfo[idx][NumberFamily] = strval(Field);
		mysql_fetch_field_row(FamilyInfo[idx][fName], "Name"); //strmid(FamilyInfo[idx][fName], Field, 0, strlen(Field), 20);
		mysql_fetch_field_row(FamilyInfo[idx][fMOTD], "MOTD"); //strmid(FamilyInfo[idx][fMOTD], Field, 0, strlen(Field), 128);
		mysql_fetch_field_row(FamilyInfo[idx][fLeader], "Leader"); //strmid(FamilyInfo[idx][fLeader], Field, 0, strlen(Field), MAX_PLAYER_NAME);

		mysql_fetch_field_row(Field, "Members"); FamilyInfo[idx][fMembers] = strval(Field);
		mysql_fetch_field_row(Field, "SpawnX"); FamilyInfo[idx][fSpawns][0] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnY"); FamilyInfo[idx][fSpawns][1] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnZ"); FamilyInfo[idx][fSpawns][2] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnA"); FamilyInfo[idx][fSpawns][3] = floatstr(Field);
		mysql_fetch_field_row(Field, "Int"); FamilyInfo[idx][fInterior] = strval(Field);
		mysql_fetch_field_row(Field, "World"); FamilyInfo[idx][fWorld] = strval(Field);
		mysql_fetch_field_row(Field, "Local"); FamilyInfo[idx][fLocal] = strval(Field);
		mysql_fetch_field_row(Field, "Bank"); FamilyInfo[idx][fBank] = strval(Field);
		mysql_fetch_field_row(Field, "Rank"); FamilyInfo[idx][fRank] = strval(Field);
		mysql_fetch_field_row(FamilyInfo[idx][fAlliance], "Alliance");
		mysql_fetch_field_row(FamilyInfo[idx][fWar], "War");
		mysql_fetch_field_row(Field, "Material"); FamilyInfo[idx][fMaterial] = strval(Field);
		idx ++;
	}
	mysql_free_result();
	printf("5/19. [Загрузка фракций]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
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
		mysql_query(ToBase); //mysql_free_result();
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
	mysql_query(ToBase);
}
#endif


stock LoadVoteSQL()//для загрузки настроек
{
	new time = GetTickCount();
	mysql_query("SELECT * FROM `vote`"); mysql_store_result();
	if(mysql_num_rows() > 0 && mysql_retrieve_row())
	{
		new Field[70];//712
		mysql_fetch_field_row(Question[qMaker], "maker"); //strmid(Question[qMaker], Field, 0, strlen(Field), 24);
		mysql_fetch_field_row(Field, "style"); Question[qStyle] = strval(Field);
		//mysql_fetch_field_row(Field, "time");
		mysql_fetch_field_row(Question[qCaption], "title"); //strmid(Question[qCaption], Field, 0, strlen(Field), 65);

		strmid(Question[qInfo0], "Не участвовать", 0, 18, 18);
		strmid(Question[qInfo], "Не участвовать\n", 0, 18, 18);

		//new strings[MAX_STRING];
		//strdel(strings, 0, MAX_STRING);
		mysql_fetch_field_row(Question[qInfo1], "Info1"); //strmid(Question[qInfo1], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo1]);
  		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo1]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));

		mysql_fetch_field_row(Question[qInfo2], "Info2"); //strmid(Question[qInfo2], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo2]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo2]);

		mysql_fetch_field_row(Question[qInfo3], "Info3"); //strmid(Question[qInfo3], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo3]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo3]);

		mysql_fetch_field_row(Question[qInfo4], "Info4"); //strmid(Question[qInfo4], Field, 0, strlen(Field), 70);
 		format(strings, sizeof(strings), "%s\n", Question[qInfo4]);
		strins(Question[qInfo], strings, strlen(Question[qInfo]));

		mysql_fetch_field_row(Question[qInfo5], "Info5"); //strmid(Question[qInfo5], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo5]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo5]);

		mysql_fetch_field_row(Question[qInfo6], "Info6"); //strmid(Question[qInfo6], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo6]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo6]);

		mysql_fetch_field_row(Question[qInfo7], "Info7"); //strmid(Question[qInfo7], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo7]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo7]);

		mysql_fetch_field_row(Question[qInfo8], "Info8"); //strmid(Question[qInfo8], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo8]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo8]);

		mysql_fetch_field_row(Question[qInfo9], "Info9"); //strmid(Question[qInfo9], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo9]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo9]);

		mysql_fetch_field_row(Question[qInfo10], "Info10"); //strmid(Question[qInfo10], Field, 0, strlen(Field), 70);
 		//format(strings, sizeof(strings), "%s\n", Question[qInfo10]);
		//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		format(Question[qInfo], 718, "%s%s\n", Question[qInfo], Question[qInfo10]);

		mysql_fetch_field_row(Question[qButton1], "Button1"); //strmid(Question[qButton1], Field, 0, strlen(Field), 10);
		mysql_fetch_field_row(Question[qButton2], "Button2"); //strmid(Question[qButton2], Field, 0, strlen(Field), 10);
		mysql_fetch_field_row(Field, "Open"); Question[qClose] = strval(Field);
		mysql_fetch_field_row(Field, "approve"); Question[qApprove] = strval(Field);
		mysql_fetch_field_row(Field, "start"); Question[qStart] = strval(Field);
		mysql_fetch_field_row(Field, "end"); Question[qEnd] = strval(Field);

		Question[qDays] = Question[qEnd] - Question[qStart];
		printf("9/19. [Загрузка голосов]: Было загружено - %d, потрачено - %d (ms)", mysql_num_rows(), (GetTickCount()-time));
	}
	mysql_free_result();
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
	mysql_query(ToBase); //mysql_free_result();
	printf("Сохранение голосов успешно завершено");
}



//для выборов начало
stock Election_OneDayTimer()
{   //запускается при смене суток
//Запустится сразу после 12:00 ночью после окончания выборов
	if(getdate() == Question[qEnd]+1)
	{//если день сменился на следующий после окончания выборов
		new timers = GetTickCount();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info1` FROM `vote`)"); mysql_store_result();
		new votes1 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info2` FROM `vote`)"); mysql_store_result();
		new votes2 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info3` FROM `vote`)"); mysql_store_result();
		new votes3 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info4` FROM `vote`)"); mysql_store_result();
		new votes4 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info5` FROM `vote`)"); mysql_store_result();
		new votes5 = mysql_num_rows(); mysql_free_result();

	/*	mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info6` FROM `vote`)"); mysql_store_result();
		new votes6 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info7` FROM `vote`)"); mysql_store_result();
		new votes7 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info8` FROM `vote`)"); mysql_store_result();
		new votes8 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info9` FROM `vote`)"); mysql_store_result();
		new votes9 = mysql_num_rows(); mysql_free_result();

		mysql_query("SELECT `IND` FROM `election` WHERE `Candidate` IN(SELECT `Info10` FROM `vote`)"); mysql_store_result();
		new votes10 = mysql_num_rows(); mysql_free_result();*/

		new playername[MAX_PLAYER_NAME], giveplayername[MAX_PLAYER_NAME];

		if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4 && votes1 > votes5)
		{
			strmid(playername, Question[qInfo1], 0, strlen(Question[qInfo1]), 24);
		}
		else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4 && votes2 > votes5)
		{
			strmid(playername, Question[qInfo2], 0, strlen(Question[qInfo2]), 24);
		}
		else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4 && votes3 > votes5)
		{
			strmid(playername, Question[qInfo3], 0, strlen(Question[qInfo3]), 24);
		}
		else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3 && votes4 > votes5)
		{
			strmid(playername, Question[qInfo4], 0, strlen(Question[qInfo4]), 24);
		}
		else if(votes5 > votes1 && votes5 > votes2 && votes5 > votes3 && votes5 > votes4)
		{
			strmid(playername, Question[qInfo5], 0, strlen(Question[qInfo5]), 24);
		}

		/*else if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4 && votes1 > votes5)
		{
			strmid(playername, Question[qInfo1], 0, strlen(Question[qInfo1]), 24);
		}
		else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4 && votes2 > votes5)
		{
			strmid(playername, Question[qInfo2], 0, strlen(Question[qInfo2]), 24);
		}
		else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4 && votes3 > votes5)
		{
			strmid(playername, Question[qInfo3], 0, strlen(Question[qInfo3]), 24);
		}
		else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3 && votes4 > votes5)
		{
			strmid(playername, Question[qInfo4], 0, strlen(Question[qInfo4]), 24);
		}
		else if(votes5 > votes1 && votes5 > votes2 && votes5 > votes3 && votes5 > votes4)
		{
			strmid(playername, Question[qInfo5], 0, strlen(Question[qInfo5]), 24);
		}*/
		else
		{
			Question[qApprove] = 0;
			strmid(playername, FamilyInfo[DoJ][fLeader], 0, strlen(FamilyInfo[DoJ][fLeader]), 24);
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
				giveplayerid = ReturnUser(giveplayername);
			    if( !IsPlayerConnected(giveplayerid) )// && giveplayerid != playerid
			    {   //если уволняется неиграющий
					new ToBase[52+MAX_PLAYER_NAME];
					format(ToBase, sizeof(ToBase), "SELECT * FROM `players` WHERE `Name` = '%s' LIMIT 1", giveplayername);
					mysql_query(ToBase); mysql_store_result();
					if(mysql_num_rows() > 0)
					{
			    		giveplayerid = MAX_PLAYERS-2;
						if(mysql_retrieve_row()) OnPlayerLoadParameters(giveplayerid, giveplayername);
					}
					mysql_free_result();
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
				new ToBase[52+MAX_PLAYER_NAME];
				format(ToBase, sizeof(ToBase), "SELECT * FROM `players` WHERE `Name` = '%s' LIMIT 1", playername);
				mysql_query(ToBase); mysql_store_result();
				giveplayerid = MAX_PLAYERS-2;
				if(mysql_num_rows() > 0)
				{
		    		giveplayerid = MAX_PLAYERS-2;
					if(mysql_retrieve_row()) OnPlayerLoadParameters(giveplayerid, playername);
				}
				mysql_free_result();
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
}




stock LoadTurfsSQL()
{
	new time = GetTickCount();
	new idx;
	new Data[1+ 20+3 + 12];
	new Field[20];
	mysql_query("SELECT Family FROM `turfs` LIMIT "#MAX_TURFS);	mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx > MAX_TURFS) break;
		//mysql_fetch_field_row(TurfInfo[idx][zName], "Name"); //strmid(TurfInfo[idx][zName], Field, 0, strlen(Field), 24);
		strmid(TurfInfo[idx][zName], regions[idx][region_name], 0, 20, 32);
		mysql_fetch_field_row(Field, "Family"); TurfInfo[idx][zFamily] = strval(Field);
		idx ++;
	}
	mysql_free_result();

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
	printf("8/19. [Загрузка зон]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}

stock InsertTurfsSQL()
{
	new ToBase[61 + 32+2+3 + 12];
	for(new idx=0; idx<MAX_TURFS; idx++)
	{
		format(ToBase, sizeof(ToBase),"INSERT INTO `turfs` (Name,Family) VALUES ('%s',%d)",
			regions[idx][region_name],//TurfInfo[idx][zName],
			TurfInfo[idx][zFamily]);
		mysql_query(ToBase);
	}
}
stock SaveTurfsSQL()
{
	new time = GetTickCount();
	new ToBase[61 + 32+2+3];
	for(new idx=0; idx<MAX_TURFS; idx++)
	{
		format(ToBase, sizeof(ToBase), "UPDATE `turfs` SET Name='%s',\
Family=%d WHERE ID=%d LIMIT 1",
			regions[idx][region_name],//TurfInfo[idx][zName],
			TurfInfo[idx][zFamily],
			idx+1);
		mysql_query(ToBase); //mysql_free_result();
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
		//GuildInfo[idx][NumberGuild],
		GuildInfo[idx][gID],
		GuildInfo[idx][gOwner],
		GuildInfo[idx][gMembers],
		GuildInfo[idx][gBrevis],
		GuildInfo[idx][gDiscription],
		GuildInfo[idx][gMOTD],
		GuildInfo[idx][gLogo],

		GuildInfo[idx][gSpawns][0],
		GuildInfo[idx][gSpawns][1],
		GuildInfo[idx][gSpawns][2],
		GuildInfo[idx][gSpawns][3],//угол
		GuildInfo[idx][gInterior],
		GuildInfo[idx][gWorld],
		GuildInfo[idx][gLocal],

		GuildInfo[idx][gEntranceX],
		GuildInfo[idx][gEntranceY],
		GuildInfo[idx][gEntranceZ],
		GuildInfo[idx][gInt],

		GuildInfo[idx][gBuyPrice],
		GuildInfo[idx][gLevel],
		GuildInfo[idx][gLock],
		GuildInfo[idx][gEntranceCost],
		GuildInfo[idx][gProducts],
		GuildInfo[idx][gBuyProd],
		GuildInfo[idx][gSellProd],
		GuildInfo[idx][gTill],
		GuildInfo[idx][gDate],
		GuildInfo[idx][gInkas]);
	mysql_query(ToBase);
	guildcounter ++;
	return 1;
}
stock LoadGuildSQL()
{
	for(new guild = 0; guild < MAX_CLANS; guild++)
	{   //инициализация всех кланов
		GuildInfo[guild][NumberGuild] = 0;
		GuildInfo[guild][gID] = 0;
		strmid(GuildInfo[guild][gOwner], "No-One", 0, 8, 8);
		GuildInfo[guild][gMembers] = 0;

	    GuildInfo[guild][gBuyPrice] = 0;
	    GuildInfo[guild][gLevel] = 0;
	    GuildInfo[guild][gLock] = 0;

	    GuildInfo[guild][gEntranceCost] = 0;
	    GuildInfo[guild][gProducts] = 100;
	    GuildInfo[guild][gBuyProd] = 1;
		GuildInfo[guild][gSellProd] = 10;

		GuildInfo[guild][gTill] = 0;
		GuildInfo[guild][gDate] = 0;
		GuildInfo[guild][gInkas] = 0;
	}

	new time = GetTickCount();
	new idx=0;
	new Data[10+61+1+128+4+2+4*7+2+3+3+11+32+256+3*7+2+7+2+1+6+11+3+3+10+3+6 + 12];//182 +
	new Field[128];
	mysql_query("SELECT * FROM `clans`"); mysql_store_result();
	while(mysql_fetch_row_format(Data, "|"))
	{
		if(idx > mysql_num_rows()) break;//sizeof(GuildInfo)
		mysql_fetch_field_row(Field, "IND"); GuildInfo[idx][NumberGuild] = strval(Field);

		mysql_fetch_field_row(Field, "ID"); GuildInfo[idx][gID] = strval(Field);
		mysql_fetch_field_row(GuildInfo[idx][gOwner], "Owner");
		mysql_fetch_field_row(Field, "Members"); GuildInfo[idx][gMembers] = strval(Field);
		mysql_fetch_field_row(GuildInfo[idx][gBrevis], "Brevis");
		mysql_fetch_field_row(GuildInfo[idx][gDiscription], "Discription");
		mysql_fetch_field_row(GuildInfo[idx][gMOTD], "MOTD");
		//mysql_fetch_field_row(GuildInfo[idx][gLogo], "Logo");

		mysql_fetch_field_row(Field, "SpawnX"); GuildInfo[idx][gSpawns][0] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnY"); GuildInfo[idx][gSpawns][1] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnZ"); GuildInfo[idx][gSpawns][2] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnA"); GuildInfo[idx][gSpawns][3] = floatstr(Field);
		mysql_fetch_field_row(Field, "SpawnInt"); GuildInfo[idx][gInterior] = strval(Field);
		mysql_fetch_field_row(Field, "SpawnWorld"); GuildInfo[idx][gWorld] = strval(Field);
		mysql_fetch_field_row(Field, "SpawnLocal"); GuildInfo[idx][gLocal] = strval(Field);

		mysql_fetch_field_row(Field, "EntranceX"); GuildInfo[idx][gEntranceX] = floatstr(Field);
		mysql_fetch_field_row(Field, "EntranceY"); GuildInfo[idx][gEntranceY] = floatstr(Field);
		mysql_fetch_field_row(Field, "EntranceZ"); GuildInfo[idx][gEntranceZ] = floatstr(Field);
		mysql_fetch_field_row(Field, "Int"); GuildInfo[idx][gInt] = strval(Field);

		mysql_fetch_field_row(Field, "BuyPrice"); GuildInfo[idx][gBuyPrice] = strval(Field);
		mysql_fetch_field_row(Field, "Level"); GuildInfo[idx][gLevel] = strval(Field);
		mysql_fetch_field_row(Field, "Lock"); GuildInfo[idx][gLock] = strval(Field);
		mysql_fetch_field_row(Field, "EntranceCost"); GuildInfo[idx][gEntranceCost] = strval(Field);
		mysql_fetch_field_row(Field, "Products"); GuildInfo[idx][gProducts] = strval(Field);
		mysql_fetch_field_row(Field, "BuyProd"); GuildInfo[idx][gBuyProd] = strval(Field);
		mysql_fetch_field_row(Field, "SellProd"); GuildInfo[idx][gSellProd] = strval(Field);
		mysql_fetch_field_row(Field, "Till"); GuildInfo[idx][gTill] = strval(Field);
		mysql_fetch_field_row(Field, "Date"); GuildInfo[idx][gDate] = strval(Field);
		mysql_fetch_field_row(Field, "Inkas"); GuildInfo[idx][gInkas] = strval(Field);

		idx ++;
		guildcounter = idx;
	}
	mysql_free_result();

	printf("6/19. [Загрузка кланов]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}
stock SaveGuildSQL(const playername[])//для банд
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
		GuildInfo[idx][gOwner],
		GuildInfo[idx][gMembers],
		GuildInfo[idx][gDiscription],

		GuildInfo[idx][gSpawns][0],
		GuildInfo[idx][gSpawns][1],
		GuildInfo[idx][gSpawns][2],
		GuildInfo[idx][gSpawns][3],//угол
		GuildInfo[idx][gInterior],
		GuildInfo[idx][gWorld],
		GuildInfo[idx][gLocal],

		GuildInfo[idx][gEntranceX],
		GuildInfo[idx][gEntranceY],
		GuildInfo[idx][gEntranceZ],
		GuildInfo[idx][gInt],

		GuildInfo[idx][gBuyPrice],
		GuildInfo[idx][gLevel],
		GuildInfo[idx][gLock],
		GuildInfo[idx][gEntranceCost],
		GuildInfo[idx][gProducts],
		GuildInfo[idx][gBuyProd],
		GuildInfo[idx][gSellProd],
		GuildInfo[idx][gTill],
		GuildInfo[idx][gDate],
		GuildInfo[idx][gInkas],
		//GuildInfo[idx][NumberGuild]);//idx);
		GuildInfo[idx][gID]);
		mysql_query(ToBase);
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[69+2+6];
	format(strtmp, sizeof(strtmp), "6/19. [Сохранение кланов]: Было сохранено - %d, потрачено - %d (ms)", MAX_CLANS, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}

