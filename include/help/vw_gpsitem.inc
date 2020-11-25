//система GPS
//new Text:GPS_TD[3];
//new PlayerText:GPS_PTD[MAX_PLAYERS][3];
//new markTimer[MAX_PLAYERS];
/*new Float:markX[MAX_PLAYERS],
    Float:markY[MAX_PLAYERS],
    Float:markZ[MAX_PLAYERS];*/
new Float:markDist[MAX_PLAYERS];
new gListitem[MAX_PLAYERS];//храним пункт выбранного меню

stock gpsitem_OnPlayerPickUp(playerid, pickupid)
{
	//--------------------------------------------------------------------------
	if(pickupid == PickupID[33] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		gpsitem_help(playerid);
		//return 1;
	}
}


enum GPS_INFO
{
	gName[64],
	gMenu,//соответсвие с меню в gpsitem_help(playerid)
	gFindClick,//записываем пункт в выбаранном меню
	Float:gX,
	Float:gY,
	Float:gZ
};
const MAX_GPS = 89;//24+8+11+11+8+5+5+1+15 = 88
static const stock GPS_COORDS[MAX_GPS][GPS_INFO] =
{
//1. {FFFFFF}Общественные места
	{"Станция LS", 			1, 0, 1733.7374,-1890.5610,13.5850},//1733.7374,-1890.5610,13.5850,299.6649
	{"Отель", 				1, 1, 1775.0676,-1806.4968,13.5295},//329.2820,-1513.9580,36.0391},
	{"Банк", 				1, 2, iEntrance_Bank},
	{"Мэрия",				1, 3, iEntrance_CityHallLS},
	{"Автошкола", 			1, 4, iEntrance_SchoolSF},
	{"Мед.Центр LS",		1, 5, 2029.5945,-1404.6426,17.2512},
	{"М-н 24/7", 			1, 6, 702.6688,-1778.4446,13.6328},
	{"Клуб Последняя ночь",	1, 7, 1322.5630,-1711.5302,13.5469},
	{"Ресторан",			1, 8, 575.2432,-1386.8186,14.3096},
	{"М-н быт. техники",	1, 9, 1733.8303,-1266.2841,13.5431},
	{"Porchlight Bar",		1, 10, 1285.1681,-1584.9147,13.5469},

	{"Симкарты",			1, 11, 1328.4407,-1557.9713,13.5469},
	{"Аптека",				1, 12, 1021.1942,-1386.9768,13.3585},
	{"Кофейня",				1, 13, 1952.7180,-2004.0569,13.5469},
	{"Market",				1, 14, 1125.1592,-1358.2808,13.3197},
	{"Авторынок",			1, 15, 348.3178,-1786.8843,5.3685},
	{"Бар 10 бутылок",		1, 16, 1222.2057,-1414.9725,13.3447},
	{"Автосалон",			1, 17, -1656.4639,1211.5634,7.2500},
	{"Аксессуары",			1, 18, iEntrance_Accessor},
	{"Тюрьма",				1, 19, 1798.2404,-1578.8049,14.0917},
	{"Аэропорт LS",			1, 20, 1642.3827,-2238.8821,13.4970},
	{"Ферма",				1, 21, -1206.5988,-1052.4946,128.4046},
	{"Склад",				1, 22, iEntrance_Store},
	{"Порт",				1, 23, iEntrance_Port},

	//{"Чёрный рынок", 		1, 2, 2062.6838,2441.2690,10.820},
	//{"Окружная церковь", 	1, 3, -2482.4199,2406.6011,17.109},
	//{"Церковь Los Santos", 	1, 4, 1720.2473,-1740.7023,13.5469},//,357.6003
	//{"Церковь San Fierro", 	1, 4, -1988.6638,1117.8837,54.47},
	//{"Церковь Las Venturas",1, 5, 2489.9905,918.4443,11.02},
	//{"Motel Jefferson", 	1, 6, 2224.6448,-1159.7986,25.750},
	//аренда водного транспорта

//2. {FFFFFF}Работы.
	{"База Механиков",			2, 0, -105.2815,-1264.0732,3.1635},
	{"Раздевалка Грузчиков",	2, 1, 2744.1611,-2453.8428,13.8623},
	{"Водителей Мусоровоза",	2, 2, 2200.1199,-1970.2765,13.7841},
	{"Ремонтников дорог",		2, 3, -253.5860,2596.9019,62.8582},
	{"Раздевалка Шахтёров",		2, 4, 564.8409,872.9808,-43.5540},
	{"Раздевалка Лесорубов",	2, 5, -537.1129,-78.4571,62.8672},
	{"Раздевалка Пожарников",	2, 6, -2026.0195,67.0815,28.6916},
	{"Раздевалка Фермеров",		2, 7, -1206.5988,-1052.4946,128.4046},

//3. {FFFFFF}Организации
	{"Полицейский участок LS",				3, 0, iEntrance_PoliceLS},
	{"Полицейский участок SF",				3, 1, iEntrance_PoliceSF},
	{"Полицейский участок LV",				3, 2, iEntrance_PoliceLV},
	{"[FBI] Федеральное Бюро Раследований",	3, 3, iEntrance_FBI},
	{"Военная база. Zone51",				3, 4, iEntrance_Barracks},
	{"Больница Los Santos",					3, 5, iEntrance_HospitalLS},
	{"Больница San Fierro",					3, 6, iEntrance_HospitalSF},
	{"Больница Las Venturas",				3, 7, iEntrance_HospitalLV},
	{"[DoJ] Министерство Юстиции",			3, 8, iEntrance_CityHallLS},
	{"[CNN] Здание новостей",				3, 9, iEntrance_CNNStudio},
	{"FOX NEWS",							3, 10, 1654.0929,-1655.2439,22.5156},
	{"[DoE] Министерство Образования",		3, 11,iEntrance_SchoolSF},

//4. {FFFFFF}Банды и мафии.
	{"База банды Grove Street",			4, 0, iEntrance_Grove},
	{"База банды The Ballas",			4, 1, iEntrance_Ballas},
	{"База банды Varios Los Aztecas",	4, 2, iEntrance_Aztecas },
	{"База банды Los Santos Vagos",		4, 3, iEntrance_Vagos},
	{"База банды San Fierro Rifa",		4, 4, iEntrance_Rifa},
	{"База банды Da Nang Boys",			4, 5, iEntrance_Nang},
	{"База банды The Traids",			4, 6, iEntrance_Triad},
	{"База банды Biker",				4, 7, iEntrance_Biker},
	{"База банды The Mafia",			4, 8, iEntrance_Mafia},
	{"[LCN] La Cosa Nostra",			4, 9, iEntrance_LCN},
	{"[Yakuza] Yakuza",					4, 10, iEntrance_Yakudza},

//5. {FFFFFF}Автосалоны, мастерские, тюнинги.
	{"Автосалон",							5, 0, -1656.4639,1211.5634,7.2500},
	{"Салон продажи воздушного транспорта",	5, 1, 410.9985,2533.5820,19.1484},
	{"Салон продажи водного транспорта",	5, 2, -2184.7546,2412.9290,5.1563},
//Автомастерские
	{"Тюнинг TransFender Los Santos",		5, 3, 1041.6010,-1033.5819,31.9278},
	{"Тюнинг LocoLovCo Los Santos",			5, 4, 2645.1038,-2036.0793,13.5540},
	{"Тюнинг TransFender San Fierro",		5, 5, -1942.8154,237.3040,34.1289},
	{"Тюнинг WheelArchAngels San Fierro",	5, 6, -2714.6714,223.7548,4.3281},
	{"Тюнинг TransFender Las Venturas",		5, 7, 2386.9714,1037.6620,10.8203},

//6. {FFFFFF}Дерби.
	{"Турнир 8-ball",						6, 0, 2695.6235,-1704.6960,11.8438},
	{"Турнир Blood-Bowl",					6, 1, -2110.5586,-444.1488,38.8344},
	{"Мотофристайл KickStart",				6, 2, 1099.4869,1601.4949,12.5469},
	{"Страйкбол",							6, 3, 2495.1414,2772.7190,10.8162},
	{"Боксерские поединки",					6, 4, 410.9985,2533.5820,19.1484},

//7. {FFFFFF}Различные бизнесы с приёмом товара.
	{"Магазин рыбалова",					7, 0, 359.9126,-2032.1475,7.8359},
	{"Свалка авто",							7, 1, -1938.7368,-1792.6500,31.9410},
	{"Пункт приёма грибов",					7, 2, -382.5433,-1439.0052,25.8975},
	{"Порт",								7, 3, iEntrance_Port},
	{"Склад",								7, 4, iEntrance_Store},
//8. {FFFFFF}Магазин аксессуаров.
	{"Магазин аксессуаров",					8, 0, iEntrance_Accessor}, // 60
	
//9. {FFFFFF}По Работе(материалы, прицепы).
// материалы для работ
	{"Материалы для торговцев оружием[кража]",	9, 0, 109.8271,1875.2222,17.8545},
	{"Материалы для торговцев оружием[сдача]",	9, 1, -2185.6946,-262.7819,40.7195},//, только для мафий!
	{"Материалы для ремонтника дорог",			9, 2, 214.4123,-230.1332,1.7786},
	{"Материалы для автоугонщиков",				9, 3, 2259.0122,-70.9235,31.6016},
	{"Материалы для автоугонщиков",				9, 4, 1489.1801,-1720.0601,8.2377},
// для дальнобойщиков
	{"База-склад",								9, 5, -18.9624,-270.4885,5.4297},
	{"Полуприцепы сферы услуг",					9, 6, 625.7370,864.7533,-42.9609},
	{"Полуприцепы промышленной сферы №1",		9, 7, 260.7742,1395.7524,10.5859},
	{"Полуприцепы промышленной сферы №2",		9, 8, -1037.6437,-669.6494,32.0126},
	{"Полуприцепы индустрии развлечений",		9, 9, -538.9946,-499.9420,25.5178},
	{"Полуприцепы розничной торговли",			9, 10, 316.3118,-232.4742,1.5391},
// для наркодиллеров
	{"Склад",									9, 11, -18.9624,-270.4885,5.4297},
	{"Ферма[Покупка пакетиков конопли]",		9, 12, -1206.5988,-1052.4946,128.4046},
	{"Наркопритон[Сдача пакетиков конопли]",	9, 13, 2166.4712,-1671.8424,15.0743},
	{"Наркопритон[Покупка синт. наркотиков]",	9, 14, 2166.4712,-1671.8424,15.0743}
};

//stock GPS(playerid)
stock gpsitem_help(playerid)
{
    /*if(PlayerInfo[playerid][pGPS] == 0 && PlayerInfo[playerid][pAdmin] != 9)
    {
        SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует GPS-Навигатор !");
		return 1;
    }*/
	if(CP[playerid] != 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент воспользоваться поисковой системой !");
		return 1;
	}
   	if(PlayerInfo[playerid][pInt] != 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы должны находится Не в Интерьере !");
		return 1;
	}
	new listitems[1344];
//\n{2680C0}5. {FFFFFF}Материалы для работ.
//\n{2680C0}6. {FFFFFF}Для дальнобойщиков.
//\n{2680C0}7. {FFFFFF}Для наркодиллеров.
	if(GetPVarInt(playerid, "gCheckpointStatus") != CHECKPOINT_NONE)
	{ strcat(listitems, 		"{2680C0}0.\t{FF0000}Выключить GPS"); }//красный
	else { strcat(listitems, 	"{2680C0}0.\t{FFFFFF}Включить GPS"); }//{00FF00} ярко-зеленый

	strcat(listitems, "\n{2680C0}1. {FFFFFF}Общественные места.\
\n{2680C0}2. {FFFFFF}Работы.\
\n{2680C0}3. {FFFFFF}Организации.\
\n{2680C0}4. {FFFFFF}Банды и мафии.\
\n{2680C0}5. {FFFFFF}Автосалоны, мастерские, тюнинги.\
\n{2680C0}6. {FFFFFF}Дерби.\
\n{2680C0}7. {FFFFFF}Различные бизнесы с приёмом товара.\
\n{2680C0}8. {FFFFFF}Магазин аксессуаров.\
\n{2680C0}9. {FFFFFF}По Работе(материалы, прицепы).");
	strcat(listitems, "\n{008C23}Ближайшие места\
\n{FFFFFF}11. {00FF00}Найти ближайший свободный/арендный транспорт");
	strcat(listitems, "\n{FFFFFF}12. {00FF00}Найти ближайший магазин 24/7\
\n{FFFFFF}13. {00FF00}Найти ближайший магазин одежды.\
\n{FFFFFF}14. {00FF00}Найти ближайшую закусочную.\
\n{FFFFFF}15. {00FF00}Найти ближайший ресторан.\
\n{FFFFFF}16. {00FF00}Найти ближайший банкомат.\
\n{FFFFFF}17. {00FF00}Найти ближайшую АЗС.\
\n{FFFFFF}18. {00FF00}Найти ближайшую автомастерскую.\
\n{FFFFFF}19. {00FF00}Найти ближайший оружейный магазин.\
\n{FFFFFF}20. {00FF00}Найти ближайший клуб/бар.");//19

	MenuOperation[playerid] = 0;
	ShowPlayerDialogEx(playerid, GPS_DIALOG, DIALOG_STYLE_LIST, "Твой навигатор", listitems, "OK", "Назад");
	return 1;
}

stock gpsitem_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	gpsitem2_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != GPS_DIALOG) return 1;
	if(!response && MenuOperation[playerid] == 0)
	{
		PlaySoundForPlayer(playerid, 5202);
		help_OnPlayerKeyStateChange(playerid);
		return 1;
	}
	new listitems[(21+64+11)*15];
	if(listitem == 0)
	{
		SYSTEM_GPS(playerid, 0, DialogResponse);
		return 1;
	}
	//if(listitem == 1)
	if(listitem >= 1 && listitem <= 9)//формируем меню согласно выбранного пункта
	{//1. {FFFFFF}Общественные места.
		MenuOperation[playerid] = 1;

	    gListitem[playerid] = listitem;//записали какой пункт мы выбрали
	    strcat(listitems, "№\tНазвание\tРасстояние\n");
	    for(new i; i < MAX_GPS; i ++)
	    {
	        if(GPS_COORDS[i][gMenu] != listitem) continue;
	    	new Float: distance = GetPlayerDistanceFromPoint(playerid, GPS_COORDS[i][gX],GPS_COORDS[i][gY],GPS_COORDS[i][gZ]);
      		new strtmp[21+64+11];
            format(strtmp, sizeof strtmp, "%d\t%s\t%.0fм\n", i, GPS_COORDS[i][gName], distance);
            strcat(listitems, strtmp);
	    }
	}
	/*if(listitem == 11)
	{//11. {00FF00}Найти ближайший магазин 24/7
    	new Nearest; new hypotenuse = 6000;
		for(new b = 15; b <= 26; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerPosEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], 0);
		}
		else
		{
			SetPlayerCheckpointEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], CHECKPOINT_SIZE/2);
			SetPVarInt(playerid, "gCheckpointStatus", 1011);
		}
		new strtmp[32+32];
		format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s ~n~~r~activated", BizInfo[Nearest][bDiscription]);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);
		return 1;
	}*/
	if(listitem == 12)
	{//11. {00FF00}Найти ближайший магазин 24/7
    	new Nearest; new hypotenuse = 6000;
		for(new b = 15; b <= 26; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerPosEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], 0);
		}
		else
		{
			SetPlayerCheckpointEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], CHECKPOINT_SIZE/2);
			SetPVarInt(playerid, "gCheckpointStatus", 1011);
		}
		new strtmp[32+32];
		format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s ~n~~r~activated", BizInfo[Nearest][bDiscription]);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);
		return 1;
	}
	else if(listitem == 13)
	{//12. {00FF00}Найти ближайший магазин одежды.
	    new Nearest; new hypotenuse = 6000;
		for(new b = 66; b <= 73; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerPosEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], 0);
		}
		else
		{
			SetPlayerCheckpointEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], CHECKPOINT_SIZE/2);
			SetPVarInt(playerid, "gCheckpointStatus", 1012);
		}
		new strtmp[32+32];
		format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s ~n~~r~activated", BizInfo[Nearest][bDiscription]);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);
		return 1;
	}
	else if(listitem == 14)
	{//13. {00FF00}Найти ближайшую закусочную.
    	new Nearest; new hypotenuse = 6000;
		for(new b = 27; b <= 53; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerPosEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], 0);
		}
		else
		{
			SetPlayerCheckpointEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], CHECKPOINT_SIZE/2);
			SetPVarInt(playerid, "gCheckpointStatus", 1013);
		}
		new strtmp[32+32];
		format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s ~n~~r~activated", BizInfo[Nearest][bDiscription]);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);
		return 1;
	}
	else if(listitem == 15)
	{//14. {00FF00}Найти ближайший ресторан.
	    new Nearest; new hypotenuse = 6000;
		for(new b = 1; b <= 3; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		/*if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerPosEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], 0);
		}
		else
		{
			SetPlayerCheckpointEx(playerid, BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ], CHECKPOINT_SIZE/2);
			SetPVarInt(playerid, "gCheckpointStatus", 1014);
		}
		new strtmp[32+32];
		format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s ~n~~r~activated", BizInfo[Nearest][bDiscription]);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);*/
		SetGPS(playerid, 1014, BizInfo[Nearest][bDiscription],
			BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ]);
		return 1;
	}
	else if(MenuOperation[playerid] == 16)
	{//15. {00FF00}Найти ближайший банкомат
	    new Nearest; new hypotenuse = 6000;
		for(new b = 0; b < MAX_ATM ; b++)
		{
		    if(Bankomat[b][aZ] > 500.0) continue;
			new range = floatround(GetPlayerDistanceFromPoint(playerid, Bankomat[b][aX],Bankomat[b][aY],Bankomat[b][aZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		/*if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerPosEx(playerid, Bankomat[Nearest][aX],Bankomat[Nearest][aY],Bankomat[Nearest][aZ], 0);
		}
		else
		{
			SetPlayerCheckpointEx(playerid, Bankomat[Nearest][aX],Bankomat[Nearest][aY],Bankomat[Nearest][aZ], CHECKPOINT_SIZE/2);
			SetPVarInt(playerid, "gCheckpointStatus", 1015);
		}
		new strtmp[32+32];
		format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s[%d] ~n~~r~activated", "Bankomat", Nearest);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);*/
		SetGPS(playerid, 1015, "ATM",
			Bankomat[Nearest][aX],Bankomat[Nearest][aY],Bankomat[Nearest][aZ]);
		return 1;
	}
	else if(listitem == 17)
	{//16. {00FF00}Найти ближайшую АЗС.
//#define GAS_STATION 18//ID первой заправки в массиве SBizInfo
//#define PARKING 40//ID первой парковки в массиве SBizInfo
	    new Nearest;	new hypotenuse = 6000;
		for(new sb = GAS_STATION; sb < PARKING; sb++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = sb;
			}
		}
		SetGPS(playerid, 1016, SBizInfo[Nearest][sbDiscription],
			SBizInfo[Nearest][sbEntranceX], SBizInfo[Nearest][sbEntranceY], SBizInfo[Nearest][sbEntranceZ]);
		return 1;
	}
	else if(listitem == 18)
	{//17. {00FF00}Найти ближайшую автомастерскую
	    new Nearest;	new hypotenuse = 6000;
		for(new sb = 13; sb < 16; sb++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = sb;
			}
		}
		SetGPS(playerid, 1017, SBizInfo[Nearest][sbDiscription],
			SBizInfo[Nearest][sbEntranceX], SBizInfo[Nearest][sbEntranceY], SBizInfo[Nearest][sbEntranceZ]);
		return 1;
	}
	else if(listitem == 19)
	{//18. {00FF00}Найти ближайший оружейный магазин.
	    new Nearest; new hypotenuse = 6000;
		for(new b = 4; b <= 14; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		SetGPS(playerid, 1018, BizInfo[Nearest][bDiscription],
			BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ]);
		return 1;
	}
	else if(listitem == 20)
	{//19. {00FF00}Найти ближайший клуб/бар
	    new Nearest; new hypotenuse = 6000;
		for(new b = 54; b <= 62; b++)
		{
			new range = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]));
			if(range < hypotenuse)
			{
				hypotenuse = range;
				Nearest = b;
			}
		}
		SetGPS(playerid, 1019, BizInfo[Nearest][bDiscription],
			BizInfo[Nearest][bEntranceX], BizInfo[Nearest][bEntranceY], BizInfo[Nearest][bEntranceZ]);
		return 1;
	}
	if(strlen(listitems) > sizeof(listitems) || strlen(listitems) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error%d: GPS %s[%d], caption: %s[%d] strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			listitems, PlayerName(playerid), playerid, inputtext, strlen(inputtext), strlen(listitems), sizeof(listitems));
		//ABroadCast(COLOR_RED, strings, 1);
		Log(ERROR, strings);

		new Float:slx, Float:sly, Float:slz;
		GetPlayerHealth(playerid, LastHealth[playerid]);
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPos(playerid, slx, sly, slz+5.0);
		PlayerPlaySound(playerid, SOUND_PUNCH_PED, slx, sly, slz+5.0);

		return 1;
	}
	ShowPlayerDialogEx(playerid, GPS_DIALOG2, DIALOG_STYLE_TABLIST_HEADERS, inputtext, listitems, "OK", "Назад");
	return 1;
}

stock gpsitem2_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != GPS_DIALOG2) return 1;

	if(!response)// && MenuOperation[playerid] <= 0
	{
		gpsitem_help(playerid); return 1;
	}
	if(MenuOperation[playerid] == 1)
	{
       	for(new i; i < MAX_GPS; i ++)
        {
            if(GPS_COORDS[i][gMenu] != gListitem[playerid]) continue;
//находим меню согласно выбранного пункта
			if(GPS_COORDS[i][gFindClick] != listitem) continue;
			SetGPS(playerid, 1000+i, GPS_COORDS[i][gName], GPS_COORDS[i][gX],GPS_COORDS[i][gY],GPS_COORDS[i][gZ]);
			break;
        }
	}
	return 1;
}

stock SYSTEM_GPS(playerid, item, callback)
{
	#pragma unused callback
	if(item == 0)
	{   // && gCheckpointStatus[playerid] != CHECKPOINT_NONE
		if(GetPVarInt(playerid, "gCheckpointStatus") > 1000)
		{
			DisablePlayerCheckpointEx(playerid);
			SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
			RemovePlayerMapIcon(playerid, MAX_PLAYER_ICONS);
		}
		else
		{
			if(MarkerToPlayer[playerid] != MAX_PLAYERS-1)
			{
				SetPlayerMarkerForPlayer(playerid, MarkerToPlayer[playerid], OldPlayerColorMarker[MarkerToPlayer[playerid]]);//COLOR_ALIVE //вернули старый цвет
				MarkerToPlayer[playerid] = MAX_PLAYERS-1;
			}
		}
		PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
		GPS_OnOff[playerid] = 0;
		GameTextForPlayerEx(playerid, "~r~gps off", 5000, 1);
		return 1;
	}
	if(MarkerToPlayer[playerid] != MAX_PLAYERS-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете воспользоваться GPS системой, т.к. маркер установлен (USE: /gps "#CHECKPOINT_NONE")!");
		return 1;
	}
	if(GetPVarInt(playerid, "gCheckpointStatus") != CHECKPOINT_NONE)
	{
		SendClientMessage(playerid, COLOR_GREY, "   GPS-Навигатор уже активирован, т.к. сheckpoint установлен (USE: /gps "#CHECKPOINT_NONE")!");
		return 1;
	}
	//------------------------------------------------------------------
	if( item > 0 && item < MAX_PLAYERS && item < 1000 && callback == PlayerCommandText )
	{
		if(!IsACop(playerid) && PlayerInfo[playerid][pMember] != DoH)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать GPS-навигатор !");
			return 1;
		}
		if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не за рулём транспортного средства !");
			return 1;
		}
		if(nCarModel[playerid] != 497//Полицейского
		&& nCarModel[playerid] != 447)//Seasparrow
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не за рулём Вертолёта!");
			return 1;
		}
		if(PlayerInfo[playerid][pGPS] == 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует GPS-Навигатор !");
			return 1;
		}
		new giveplayerid = item;//ReturnUser(tmp);
		if(IsPlayerConnected(giveplayerid))
		{   // && !IsPlayerNPC(giveplayerid) && gPlayerSpawned[giveplayerid] == 1
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Вы не можете Искать самого себя!"); return 1; }
			if(PlayerInfo[giveplayerid][pMember] == Hitman)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете Искать этого человека !");
				return 1;
			}
			if(PlayerInfo[giveplayerid][pInt] == 0)
			{
				//gCheckpointStatus[playerid] = giveplayerid;
				SetPlayerMarkerForPlayerEx(playerid, giveplayerid, COLOR_BLUEGREY);//COLOR_RED - 0xFF0000FF
				GPS_OnOff[playerid] = 1;
			}
			else SendClientMessage(playerid, COLOR_GREY, "   Игрок находится в интерьере !");
		}
		else SendClientMessage(playerid, COLOR_GREY, "   Неправильное Name/ID !");
	}
	return 1;
}

stock SetGPS(playerid, item, const text[], Float:x, Float:y, Float:z)
{
    new strtmp[144];
    /*if(item == 1000)
    {
	    x = BizInfo[0][bEntranceX],
		y = BizInfo[0][bEntranceY],
		z = BizInfo[0][bEntranceZ];
	}*/
    
	if(PlayerInfo[playerid][pAdmin] >= 6 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
	    markDist[playerid] = GetPlayerDistanceFromPoint(playerid, x, y, z);
	    new Float:Angle;
		GetPlayerFacingAngle(playerid, Angle);
		SetPlayerPosEx(playerid, x,y,z, Angle);
		//return 1;
	}
	else
	{
		markDist[playerid] = float(SetPlayerCheckpointEx(playerid, x,y,z, CHECKPOINT_SIZE/2));
		SetPVarInt(playerid, "gCheckpointStatus", item);

	    format(strtmp, sizeof(strtmp), "~g~gps ~n~~w~%s ~n~~r~ activated", text);
		GameTextForPlayerEx(playerid, strtmp, 5000, 1);
	}
    format(strtmp, sizeof(strtmp), "{FFFFFF}Пункт назначения '{4595B2}%s{FFFFFF}' выбран | Расстояние: {4595B2}%.0f{FFFFFF} метров", text, markDist[playerid]);
    SendClientMessage(playerid, -1, strtmp);
    return 1;
}
