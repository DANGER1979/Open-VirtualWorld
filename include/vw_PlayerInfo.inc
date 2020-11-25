new WantedPoints[MAX_PLAYERS];//очки розыска

//объявление, инициализация, загрузка и сохранение всех переменных массива PlayerInfo

enum pInfo//для считывания из файла
{
	pSQLID,
	pName[MAX_PLAYER_NAME],
	pKey[20],//пароль 0
	pMail[34],//мыло
	pIP[24],
	pSex,//пол 7
	pAge[12],//возраст - дата регистрации
	pOrigin[3],//страна
	pDepositDay,//зарегистрирован 6
	pLevel,//уровень 1 см GetPlayerLevel
	pAdmin,//уровень админа 2
	pAccount,//ранг плательщика  - дата окончания ВИП
	pMuted,//заглушен
	pWarns,//админ-предупреждений о бане командой warn
	pConnectTime,//время в игре 5
//каждый час переменная в базе Online принимает значение ConnectTime
	pRespect,//уважение
	pRespectDay,//дата последней выдачи уважения кому то
	pPayCheck,//зарплата на 1 лвл 1мс соотв. 1$
	pPayTime,//каждые 5 минут начисляем очки //если вы играли больше 55 минут то +1 час игы и +1 респект
	pDeposit,//денег на депозите
	pCash,//только для установки при логине кол-ва денег на руках при выходе из игры
	pBank,//денег в банке
	Float:pGold,//денег в банке
	Float:pSHealth,//определяет уровень здоровья(50+pSHealth) до которого будет проходить лечение
//if(LastHealth[i] >= floatadd(PlayerInfo[i][pSHealth], 50.0))
	Float:pHealth,//здоровья при возрождении текущее здоровье
	pInt,//интерьер
	Float:pPos_x,//координаты выхода из игры
	Float:pPos_y,
	Float:pPos_z,
	pVirtual,//для параллельных миров
	pLocal,//местность
	pHouse,//номер дома последнего купленнного дома или где игрок арендует комнату
	pBizz,//номер биза где игрок будет работать, 0-99=бизы с интерьером, >100 бизы без интерьера
	pJob,//работа
	pTeam,//клан
	pMember,//член
	pLeader,//лидер
	pRank,//ранг
	pChar,//скин если в организации постоянный устанавливается вновь при респе
	pModel,//скин игрока
	pContractTime,//время контракта

	pMinerSkill,//pDetSkill,//1 навык детектива
	pLawSkill,//2
	pRoadSkill,//3 //RoadWorker
	pDrugsSkill,//4
	pJackSkill,//5
	pProfSkill,//6  - ProfSkill, также день увольнения, т.к. после увольнения переменная свободна
	pMechSkill,//7
	pFarmSkill,//8 //для фермеров
	pGunSkill,//9
	pCarSkill,//10
	pInkasSkill,//11 для инкассаторов
	pBookmakerSkill,//12
	pTaxiSkill,//13 для таксистов
	pBusSkill, //14 //для автобусников
	pCourierSkill, //15 Для курьера
	pTruckSkill,//16 для дальнобойщиков
	pTrashSkill,//17 для мусорщиков
	pLoadSkill,//18 для грузчиков
	pWoodSkill,//19 для дровосеков
	pFishSkill,//20 навык рыбалова
	pFireSkill,//21 навык рыбалова
	pCookSkill,//22

	pCarLic,//лицензия на авто
	pBikeLic,//лицензия на мото
	pFlyLic,
	pBoatLic,
	pFishLic,
	pGunLic,
	    //заменить одной переменной в базе
		pGun1,//оружие
		pAmmo1,//боеприпасы
		pGun2,
		pAmmo2,
		pGun3,
		pAmmo3,
		pGun4,
		pAmmo4,
	pGun22Skill,
	pGun23Skill,
	pGun24Skill,
	pGun25Skill,
	pGun26Skill,
	pGun27Skill,
	pGun28Skill,
	pGun29Skill,
	pGun30Skill,
	pGun31Skill,
	pGun34Skill,

	pHeadValue,//цена за голову
	pWins,//боксёрских побед
	pLoses,//боксёрских проигрышей
	pKills,//убийств
	pDeaths,//смертей
	pAccident,//ДТП
	pTicket,//штрафов
	pCrimes,//преступлений
	pArrested,//кол-во арестов
	pWantedDeaths,//смертей при аресте
	pArticle,
	pPart,
	pJailed,//место тюремного заключения
	pJailTime,//время ареста в минутах если игрок арестован, или дата последнего преступления
	pJailPrice,//величина залога
//на удаление
pPupgrade,//очки усовершенствования 4

//pPerks[11],
	pAlcoholPerk,//увеличивает кол-во получаемого здоровья при принятии спиртных напитков
	pDrugPerk,//увеличивает кол-во получаемого здоровья при принятии наркотиков
	pMiserPerk,//уменьшает стоимость покупки материалов для оружейника
	pPainPerk,//медик лечит свыше 100%
	pTraderPerk,//уменьшает стоимость покупок в магазине 24-7

	pHunger,//АнтиГолод
	pLeisure,//АнтиДосуг
	pContact,//АнтиОбщение
	pToilet,//АнтиТуалет
	pVigour,//АнтиБодрость

	//pVigour,//Марадёрство
	//Воровство
	//Оружейное дело
	//Наркооборот

	pSTD,//болезнь
	
//PlayerItems[11];
		//заменить одной переменной
		pAntiradar,//для сохранения
		pGPS,
		pCDPlayer,//CD
		pDice,//игральные кости или карты
	pDrugs,//наркотиков
		pCigars,//сигарет
//для акссесуаров
	pOther[30],//аксесуары
	pType,
	pType2,

//убрать из базы, но оставить в массиве
pFishes,//споймано кг рыб
pBiggestFish,//самая большая рыба

	pAdrenalin,

//VehicleItems[11];
	pFuel,//топлива в канистре
	pLottoNr,//номер лотереи
	pMats,//материалов
	pMushroom,//собрано грибов

	//на замену
	pPnumber,//номер телефона
	pHelmet,//хранит ИД объекта шлема или кепки
	pMarried,//в браке

	pMarriedTo[20],//с кем обручен
	pOffline,//хранить день выхода с сервера
	//-1 - только что зашёл в игру, >=1 - игрок вне игры, 0 - Online игрок в игре.
	//если -1 сохранилась значит игрок как то странно вышел
	//Показывает нормально ли вышел игрок и в какой день в году
	pReason,//причина при сохранении. Причина выхода из игры. 0 - Timed out
	pCarTime,//время задания по работе
	//для дерби BloodBowl
	//для курьеров
	//для детективов
	//для автомехаников
	//для дальнобойщиков
	pTut,//пройдено миссий
 	pVote,//номер кандидата
	pPurposeMurder,//цель убийства
	pReferal[20],//наставник
	pOnline,//хранит pConnectTime на отметке раз в неделю
	pScore,//общие очки

//текущие потребности
	pParam1,//голод должен достигать максимума за 97 минут(58000)
	pParam2,//Досуг должен достигать максимума за 143 минут(178000)
	pParam3,//Общение должен достигать максимума за 149 минут(298000)
	pParam4,//Туалет должен достигать максимума за 199 минут(598000)
	pParam5//Бодрость должен достигать максимума за 240 минут(958000)
};
new PlayerInfo[MAX_PLAYERS][pInfo];

//##############################################################################//
//                                                                              //
//                       ИНИЦИАЛИЗАЦИЯ МАССИВА PlayerInfo                       //
//                                                                              //
//##############################################################################//



//##############################################################################//
//                                                                              //
//                  ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ массива PlayerInfo                 //
//                                                                              //
//##############################################################################//
stock PlayerInfo_OnPlayerConnect(playerid)
{//инициализация пустого массива

	PlayerInfo[playerid][pSQLID] = 0;
	//if(callback == PlayerConnect)
	//GetPlayerName(playerid, PlayerInfo[playerid][pName], MAX_PLAYER_NAME);// узнаем имя подключившегося игрока и записываем в нашу переменную.
	//strmid(PlayerInfo[playerid][pName], "Unknown", 0, strlen("Unknown"), 24);//иначе в киках не будет виден ник входящего
	strdel(PlayerInfo[playerid][pKey], 0, 20);
	strdel(PlayerInfo[playerid][pMail], 0, 34);
	strmid(PlayerInfo[playerid][pIP], "192.168.1.1", 0, strlen("192.168.1.1"), 16);
	PlayerInfo[playerid][pSex] = 0;
	//PlayerInfo[playerid][pAge] = 0;
	strmid(PlayerInfo[playerid][pAge], "1999.12.31", 0, strlen("1999.12.31"), 12);
	PlayerInfo[playerid][pOrigin] = 0;//strmid(PlayerInfo[playerid][pAge], "BY", 0, strlen("BY"), 3);//PlayerInfo[playerid][pOrigin] = 0;
	PlayerInfo[playerid][pDepositDay] = 0;
	PlayerInfo[playerid][pLevel] = 1;
	PlayerInfo[playerid][pAdmin] = 9;//временно
	PlayerInfo[playerid][pAccount] = 0;
	PlayerInfo[playerid][pMuted] = 0;
	PlayerInfo[playerid][pWarns] = 0;
	PlayerInfo[playerid][pConnectTime] = 0;

	PlayerInfo[playerid][pRespect] = 0;
	PlayerInfo[playerid][pRespectDay] = 0;
	PlayerInfo[playerid][pPayCheck] = 0;
	PlayerInfo[playerid][pPayTime] = 0;
	PlayerInfo[playerid][pDeposit] = 0;
	PlayerInfo[playerid][pCash] = 100000;//1000;//временно
	PlayerInfo[playerid][pBank] = 0;
	PlayerInfo[playerid][pGold] = 0; DeletePVar(playerid, "GOLD");
	PlayerInfo[playerid][pSHealth] = 50.0;//0.0
	PlayerInfo[playerid][pHealth] = 50.0;

	/*PlayerInfo[playerid][pInt] = 15;
	PlayerInfo[playerid][pPos_x] = 2246.6;//2246.6,-1161.9,1029.8 - координаты Отеля
	PlayerInfo[playerid][pPos_y] = -1161.9;
	PlayerInfo[playerid][pPos_z] = 1029.8;
	PlayerInfo[playerid][pVirtual] = 15;*/
	/*PlayerInfo[playerid][pInt] = 7;
	PlayerInfo[playerid][pPos_x] = 1860.1427;//1860.1427,-1892.7968,908.6368,91.5286 - координаты Отеля
	PlayerInfo[playerid][pPos_y] = -1892.7968;
	PlayerInfo[playerid][pPos_z] = 908.6368;
	PlayerInfo[playerid][pVirtual] = 1;*/
	PlayerInfo[playerid][pInt] = 0;
	PlayerInfo[playerid][pPos_x] = 1733.7374;//{1733.7374,-1890.5610,13.5850,299.6649}, // station
	PlayerInfo[playerid][pPos_y] = -1890.5610;
	PlayerInfo[playerid][pPos_z] = 13.5850;
	PlayerInfo[playerid][pVirtual] = 0;

	PlayerInfo[playerid][pLocal] = FREEROAM;

	SetPVarInt(playerid, "FirstInterior", PlayerInfo[playerid][pInt]);
	SetPVarInt(playerid, "FirstVirtual", PlayerInfo[playerid][pVirtual]);
	SetPVarInt(playerid, "FirstLocal", PlayerInfo[playerid][pLocal]);

//будет игрок падать после регистрации
/*	PlayerInfo[playerid][pInt] = 0;
	PlayerInfo[playerid][pPos_x] = 0.0;//2246.6,-1161.9,1029.8 - координаты Отеля
	PlayerInfo[playerid][pPos_y] = 0.0;
	PlayerInfo[playerid][pPos_z] = 0.0;
	PlayerInfo[playerid][pVirtual] = 0;
	PlayerInfo[playerid][pLocal] = FREEROAM;*/
//можно удалить
	PlayerInfo[playerid][pHouse] = NOT_KEY;//временно
	PlayerInfo[playerid][pBizz] = NOT_KEY;//временно

	PlayerInfo[playerid][pJob] = TRUCKER;//временно
	PlayerInfo[playerid][pTeam] = 0;//3
	PlayerInfo[playerid][pLeader] = 0;
	PlayerInfo[playerid][pMember] = 0;
	PlayerInfo[playerid][pRank] = 0;
	PlayerInfo[playerid][pChar] = SKIN_DEFAULT;//26 SKIN_DEFAULT; //временно
	PlayerInfo[playerid][pModel] = SKIN_DEFAULT;//26 SKIN_DEFAULT; //временно

	PlayerInfo[playerid][pContractTime] = 0;

	PlayerInfo[playerid][pMinerSkill] = 0;//1
	PlayerInfo[playerid][pLawSkill] = 0;//2
	PlayerInfo[playerid][pRoadSkill] = 0;//3
	PlayerInfo[playerid][pDrugsSkill] = 0;//4
	PlayerInfo[playerid][pJackSkill] = 0;//5
	PlayerInfo[playerid][pProfSkill] = 0;//6
	PlayerInfo[playerid][pMechSkill] = 0;//7
	PlayerInfo[playerid][pFarmSkill] = 0;//8 //для фермеров
	PlayerInfo[playerid][pGunSkill] = 0;//9
	PlayerInfo[playerid][pCarSkill] = 0;//10
	PlayerInfo[playerid][pInkasSkill] = 0;//11
	PlayerInfo[playerid][pBookmakerSkill] = 0;//12
	PlayerInfo[playerid][pTaxiSkill] = 0;//13 для таксистов
	PlayerInfo[playerid][pBusSkill] = 0;//14 //для автобусников
	PlayerInfo[playerid][pCourierSkill] = 0;//15 Для курьера
	PlayerInfo[playerid][pTruckSkill] = 400;//временно//16 для дальнобойщиков

	PlayerInfo[playerid][pTrashSkill] = 0;//17 для мусорщиков
	PlayerInfo[playerid][pLoadSkill] = 0;//19 для грузчиков
	PlayerInfo[playerid][pWoodSkill] = 0;//20 для дровосеков
	PlayerInfo[playerid][pFishSkill] = 0;//21 навык рыбалова
	PlayerInfo[playerid][pCookSkill] = 0;//22

	PlayerInfo[playerid][pCarLic] = 1;//временно
	PlayerInfo[playerid][pBikeLic] = 1;//лицензия на мото
	PlayerInfo[playerid][pFlyLic] = 1;
	PlayerInfo[playerid][pBoatLic] = 1;
	PlayerInfo[playerid][pFishLic] = 1;
	PlayerInfo[playerid][pGunLic] = 1;

	PlayerInfo[playerid][pGun1] = 22;
	PlayerInfo[playerid][pAmmo1] = 100;
	PlayerInfo[playerid][pGun2] = 29;
	PlayerInfo[playerid][pAmmo2] = 200;
	PlayerInfo[playerid][pGun3] = 34;
	PlayerInfo[playerid][pAmmo3] = 300;
	PlayerInfo[playerid][pGun4] = 27;
	PlayerInfo[playerid][pAmmo4] = 400;

	PlayerInfo[playerid][pGun22Skill] = 0;
	PlayerInfo[playerid][pGun23Skill] = 0;
	PlayerInfo[playerid][pGun24Skill] = 0;
	PlayerInfo[playerid][pGun25Skill] = 0;
	PlayerInfo[playerid][pGun26Skill] = 0;
	PlayerInfo[playerid][pGun27Skill] = 0;
	PlayerInfo[playerid][pGun28Skill] = 0;
	PlayerInfo[playerid][pGun29Skill] = 0;
	PlayerInfo[playerid][pGun30Skill] = 0;
	PlayerInfo[playerid][pGun31Skill] = 0;
	PlayerInfo[playerid][pGun34Skill] = 0;

	PlayerInfo[playerid][pHeadValue] = 0;
	PlayerInfo[playerid][pWins] = 0;
	PlayerInfo[playerid][pLoses] = 0;

	PlayerInfo[playerid][pKills] = 0;
	PlayerInfo[playerid][pDeaths] = 0;
	PlayerInfo[playerid][pAccident] = 0;
	PlayerInfo[playerid][pTicket] = 0;
	PlayerInfo[playerid][pCrimes] = 0;
	PlayerInfo[playerid][pArrested] = 0;
	PlayerInfo[playerid][pWantedDeaths] = 0;
	PlayerInfo[playerid][pArticle] = 0;
	PlayerInfo[playerid][pPart] = 0;
	PlayerInfo[playerid][pJailed] = 0;
	PlayerInfo[playerid][pJailTime] = 0;
	PlayerInfo[playerid][pJailPrice] = 0;

	PlayerInfo[playerid][pPupgrade] = 0;

	PlayerInfo[playerid][pAlcoholPerk] = 0;
	PlayerInfo[playerid][pDrugPerk] = 0;
	PlayerInfo[playerid][pMiserPerk] = 0;
	PlayerInfo[playerid][pPainPerk] = 0;
	PlayerInfo[playerid][pTraderPerk] = 0;
	PlayerInfo[playerid][pHunger] = 0;
	PlayerInfo[playerid][pLeisure] = 0;
	PlayerInfo[playerid][pContact] = 0;
	PlayerInfo[playerid][pToilet] = 0;
	PlayerInfo[playerid][pVigour] = 0;

	PlayerInfo[playerid][pSTD] = 0;

	PlayerInfo[playerid][pAntiradar] = 1;//для сохранения
	PlayerInfo[playerid][pGPS] = 1;//временно
	PlayerInfo[playerid][pCDPlayer] = 1;
	PlayerInfo[playerid][pDice] = 1;//для сохранения
	PlayerInfo[playerid][pDrugs] = 1;
	PlayerInfo[playerid][pCigars] = 1;
	PlayerInfo[playerid][pFishes] = 1;
	PlayerInfo[playerid][pAdrenalin] = 1;
	PlayerInfo[playerid][pBiggestFish] = 1;
	PlayerInfo[playerid][pFuel] = 20;
	PlayerInfo[playerid][pLottoNr] = 33;
	PlayerInfo[playerid][pMats] = 1000;
	PlayerInfo[playerid][pMushroom] = 10;
	PlayerInfo[playerid][pPnumber] = 7557347;
	PlayerInfo[playerid][pHelmet] = 1;
	PlayerInfo[playerid][pMarried] = 0;
	strmid(PlayerInfo[playerid][pMarriedTo], "BeSingle", 0, 16, 24);

	PlayerInfo[playerid][pOffline] = getdate();//0;//-1
//strmid(PlayerInfo[playerid][pIP], "255.255.255.255", 0, 16, 16);
	//strmid(PlayerInfo[playerid][pIP], "192.161.1.2", 0, strlen("192.161.1.2"), 16);
	//strdel(PlayerInfo[playerid][pIP], 0, 16);//???
	PlayerInfo[playerid][pReason] = -1;

	PlayerInfo[playerid][pCarTime] = 0;//обнуляем при входе в игру оставшееся время по заданию
	PlayerInfo[playerid][pTut] = 0;
	PlayerInfo[playerid][pVote] = 0;
	PlayerInfo[playerid][pPurposeMurder] = 0;
	//PlayerInfo[playerid][pReferal] = 0;
	strmid(PlayerInfo[playerid][pReferal], "No-One", 0, 16, 24);//для рефералов
}


stock PlayerInfo_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	PlayerInfo[playerid][pDeaths] += 1;
	PlayerInfo[killerid][pKills] += 1;//пусть подсчитываются все убийства

}


stock PlayerInfo_OnPlayerSpawn(playerid)
{//ставим интерьер и мир только тут при спауне
	SetPlayerVirtualWorldEx(playerid, PlayerInfo[playerid][pVirtual]);//1
	SetPlayerInteriorEx(playerid, PlayerInfo[playerid][pInt]);//2

	LastMoney[playerid] = PlayerInfo[playerid][pCash];
	GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);//начислить деньги игроку из переменной

	SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth]);//Кол-во жизней у игрока

	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_PISTOL, PlayerInfo[playerid][pGun22Skill]);//PISTOL
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_PISTOL_SILENCED, PlayerInfo[playerid][pGun23Skill]);//PISTOL_SILENCED
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_DESERT_EAGLE, PlayerInfo[playerid][pGun24Skill]);//DESERT_EAGLE
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SHOTGUN, PlayerInfo[playerid][pGun25Skill]);//SHOTGUN
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, PlayerInfo[playerid][pGun26Skill]);//SAWNOFF_SHOTGUN
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SPAS12_SHOTGUN, PlayerInfo[playerid][pGun27Skill]);//SPAS12_SHOTGUN
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_MICRO_UZI, PlayerInfo[playerid][pGun28Skill]);//MICRO_UZI
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_MP5, PlayerInfo[playerid][pGun29Skill]);//MP5
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_AK47, PlayerInfo[playerid][pGun30Skill]);//AK47
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_M4, PlayerInfo[playerid][pGun31Skill]);//M4
	SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SNIPERRIFLE, PlayerInfo[playerid][pGun34Skill]);//SNIPERRIFLE
	
	PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
}

stock GetPlayerGunSkill(playerid, Gun)
{
    switch(Gun)
	{
        case 22: return PlayerInfo[playerid][pGun22Skill];
        case 23: return PlayerInfo[playerid][pGun23Skill];
        case 24: return PlayerInfo[playerid][pGun24Skill];
        case 25: return PlayerInfo[playerid][pGun25Skill];
        case 26: return PlayerInfo[playerid][pGun26Skill];
        case 27: return PlayerInfo[playerid][pGun27Skill];
        case 28: return PlayerInfo[playerid][pGun28Skill];
        case 29: return PlayerInfo[playerid][pGun29Skill];
        case 30: return PlayerInfo[playerid][pGun30Skill];
        case 31: return PlayerInfo[playerid][pGun31Skill];
        case 32: return PlayerInfo[playerid][pGun28Skill];
        case 34: return PlayerInfo[playerid][pGun34Skill];
		default: return 0;
	}
	return 0;
}

forward GetAdminLevel(playerid);
public GetAdminLevel(playerid)
{
	return PlayerInfo[playerid][pAdmin];
}

stock GetAdminRanks(playerid)
{
	new rtext[12];
    if(PlayerInfo[playerid][pAdmin] == 1) { rtext =       "Helper"; }
	else if(PlayerInfo[playerid][pAdmin] == 2) { rtext =  "GangManager"; }
	else if(PlayerInfo[playerid][pAdmin] == 3) { rtext =  "Moderator"; }
	else if(PlayerInfo[playerid][pAdmin] == 4) { rtext =  "EventMaster"; }
	else if(PlayerInfo[playerid][pAdmin] == 5) { rtext =  "GameAdmin"; }
	else if(PlayerInfo[playerid][pAdmin] == 6) { rtext =  "DeBugger"; }
    else if(PlayerInfo[playerid][pAdmin] == 7) { rtext =  "Judge"; }
	else if(PlayerInfo[playerid][pAdmin] == 8) { rtext =  "Developer"; }
	else if(PlayerInfo[playerid][pAdmin] == 9) { rtext =  "Creator"; }
	else if(PlayerInfo[playerid][pAdmin] == 10) { rtext = "Invisible"; }
	else { rtext = "Invisible"; }
	return rtext;
}



