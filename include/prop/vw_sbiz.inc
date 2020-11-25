new MyCompany[MAX_PLAYERS][20];

new sbEntrancePickupID[MAX_SBIZ];
new Text3D: sbEntranceText3D[MAX_SBIZ];

stock sbiz_OnGameModeInit()
{
	//НАЧАЛО УСТАНОВКИ ПИКАПОВ c надписями
	new text_info[128];//19+20+24
	//==========================================================================
	for(new sb = 0; sb < GAS_STATION; sb++)
	{   //компании
		if(SBizInfo[sb][sbOwned] == 0)
		{   //если биз не куплен
			sbEntrancePickupID[sb] = SetPickupEx(1273, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
			//sbEntrancePickupID[sb] = CreateDynamicPickup(1274, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ],
				//-1, -1, -1, 300.0);
		    format(text_info, sizeof(text_info), "[ %s ]", SBizInfo[sb][sbDiscription]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xEEEE88FF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		else if(SBizInfo[sb][sbOwned] > 0)
		{   //если биз куплен
			sbEntrancePickupID[sb] = SetPickupEx(19522, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", SBizInfo[sb][sbDiscription], SBizInfo[sb][sbOwner]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xAAAAFFFF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		
	}//39-50=12
//для заправок
	for(new sb = GAS_STATION; sb < PARKING; sb++)
	{   //канистры заправки
		if(SBizInfo[sb][sbOwned] == 0)
		{   //если биз не куплен
			sbEntrancePickupID[sb] = SetPickupEx(1650, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]", SBizInfo[sb][sbDiscription]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xEEEE88FF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		else if(SBizInfo[sb][sbOwned] > 0)
		{   //если биз куплен
			sbEntrancePickupID[sb] = SetPickupEx(1650, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", SBizInfo[sb][sbDiscription], SBizInfo[sb][sbOwner]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xAAAAFFFF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
	}//39-50=12
	for(new sb = PARKING; sb < PARKING+sizeof(Parking); sb++)
	{   //паркинги
		if(SBizInfo[sb][sbOwned] == 0)
		{   //если биз не куплен
			sbEntrancePickupID[sb] = SetPickupEx(1239, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]", SBizInfo[sb][sbDiscription]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xEEEE88FF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		else if(SBizInfo[sb][sbOwned] > 0)
		{   //если биз куплен
			sbEntrancePickupID[sb] = SetPickupEx(1239, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", SBizInfo[sb][sbDiscription], SBizInfo[sb][sbOwner]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xAAAAFFFF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
	}
	for(new sb = PARKING+sizeof(Parking); sb < MAX_SBIZ; sb++)
	{   //бизы после паркингов
		if(SBizInfo[sb][sbOwned] == 0)
		{   //если биз не куплен
			sbEntrancePickupID[sb] = SetPickupEx(1273, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]", SBizInfo[sb][sbDiscription]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xEEEE88FF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		else if(SBizInfo[sb][sbOwned] > 0)
		{   //если биз куплен
			sbEntrancePickupID[sb] = SetPickupEx(19522, 23, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], 0);
		    format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", SBizInfo[sb][sbDiscription], SBizInfo[sb][sbOwner]);

			sbEntranceText3D[sb] = Create3DTextLabelEx(text_info, 0xAAAAFFFF,
					SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]+0.75,
					30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
	}
}



stock sbiz_OnPlayerPickUpPickup(playerid, pickupid)
//stock PropertyOnPlayerPickUp(playerid, pickupid)
{   //вызывается из OnPlayerPickUpPickup только при подборе пикапа
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return 1; }
	//if(pickupid < (STAIRWAYS*2-2) || pickupid >= (STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ)) return 1;
//STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ + MAX_VEHICLE_PICKUPS	//35*2 + (52*2+12)+82*2+59 = 409
//12 - максимальное кол-во раздевалок
	//new local = PlayerInfo[playerid][pLocal];
	new msgitem[868];//542+52+57+57 + 38+32+25+35+3+3+5+5 + 14 = 868
	new tregion[20];
	strmid(tregion, "Unknown_Region", 0, strlen("Unknown_Region"), 20);
	new sbouse;//оставляем по нулям, чтобы не было за пределами массива

	for(new sb = 0; sb < MAX_SBIZ; sb++)
	{   //опеделяем у какого биза стоит игрок
		//if(IsPlayerInRangeOfPoint(playerid, 4.1, HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]))
		if(pickupid == sbEntrancePickupID[sb])
		{
			sbouse = sb; SetPVarInt(playerid, "SBouse", sb);
			break;
		}
	}
	//==========================================================================
	if(gDialogStatus[playerid][2] <= 0 &&
		//IsPlayerInRangeOfPoint(playerid, 1.4, SBizInfo[sbouse][sbEntranceX], SBizInfo[sbouse][sbEntranceY], SBizInfo[sbouse][sbEntranceZ]))
		pickupid == sbEntrancePickupID[sbouse])
	{
		for(new j=0; j<MAX_TURFS; j++)
		{
			if( IsPointInRegion(SBizInfo[sbouse][sbEntranceX], SBizInfo[sbouse][sbEntranceY], SBizInfo[sbouse][sbEntranceZ], j) )//если дом находится в координатах по строке j из массива zones
			{
				strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 255);//Извлекает диапазон символов из строки.
				break;
			}
		}
		new style, DIALOG_ID;
		if(SBizInfo[sbouse][sbOwned] > 0)
		{//{0080FF}Описание:\t{FFFFFF}%s\n
		    if(sbouse == 54 && PlayerInfo[playerid][pMushroom] > 0)//для грибников
		    {
				format(msgitem, sizeof(msgitem), "{0080FF}Район:\t\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t\t{FFFFFF}%s\
\n{0080FF}Контроль:\t\t{FFFFFF}%s\
\n{0080FF}Цена входа:\t\t{33AA33}$%d\
\n{0080FF}Скупка грибов:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Продажа грибов:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Грибов на складе:\t{FFFFFF}%d",
					tregion,  100+sbouse+1, SBizInfo[sbouse][sbOwner],
					GetFamilyName(SBizInfo[sbouse][sbExtortion]),
					SBizInfo[sbouse][sbEntranceCost],
					compcost*(100+SBizInfo[sbouse][sbBuyProd])/100.0, 100+SBizInfo[sbouse][sbBuyProd],
					compcost*(100+SBizInfo[sbouse][sbSellProd])/100.0, 100+SBizInfo[sbouse][sbSellProd],
					SBizInfo[sbouse][sbProducts]);
				format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t\t{33AA33}%d\
\n{0080FF}Экспорт[Импорт]:\t{33AA33}$%d{FFFFFF}[$%d]\
\n{0080FF}Зарплата:\t\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}В Кассе:\t\t{33AA33}$%d",
					msgitem,
					SBizInfo[sbouse][sbWorker],
					SBizInfo[sbouse][sbExport],SBizInfo[sbouse][sbImport],
					SBizInfo[sbouse][sbSalary],
					SBizInfo[sbouse][sbExpenses],
					SBizInfo[sbouse][sbTill]);
				strins(msgitem, "\n\n{AFAFAF}Введите количество, которое хотите Сдать.", strlen(msgitem));
				strins(msgitem, "\n\n\t{8CAA63}По окончанию ввода нажмите OK.", strlen(msgitem));
				DIALOG_ID = MUSHROOMER_DIALOG;
				style = DIALOG_STYLE_INPUT;
		    }
		    else if(sbouse == 3 || sbouse == 4 || sbouse == 17 || (sbouse >= GAS_STATION && sbouse < PARKING))
		    {
				format(msgitem, sizeof(msgitem), "{0080FF}Район:\t\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t\t{FFFFFF}%s\
\n{0080FF}Контроль:\t\t{FFFFFF}%s\
\n{0080FF}Цена входа:\t\t{33AA33}$%d\
\n{0080FF}Покупка нефти:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Продажа топлива:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Литров к продаже:\t{FFFFFF}%d",//SBizInfo[sbouse][sbDiscription],
					tregion,  100+sbouse+1, SBizInfo[sbouse][sbOwner],
					GetFamilyName(SBizInfo[sbouse][sbExtortion]),
					SBizInfo[sbouse][sbEntranceCost],
					FuelCost*SBizInfo[sbouse][sbBuyProd]/100.0, SBizInfo[sbouse][sbBuyProd],
					FuelCost*(100+SBizInfo[sbouse][sbSellProd])/100.0, (100+SBizInfo[sbouse][sbSellProd]),
					SBizInfo[sbouse][sbProducts]);

				format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t\t{33AA33}%d\
\n{0080FF}Экспорт[Импорт]:\t{33AA33}$%d{FFFFFF}[$%d]\
\n{0080FF}Зарплата:\t\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}В Кассе:\t\t{33AA33}$%d",
					msgitem,
					SBizInfo[sbouse][sbWorker],
					SBizInfo[sbouse][sbExport],SBizInfo[sbouse][sbImport],
					SBizInfo[sbouse][sbSalary],
					SBizInfo[sbouse][sbExpenses],
					SBizInfo[sbouse][sbTill]);
				DIALOG_ID = DIALOG100;
			}
		    else
		    {
				format(msgitem, sizeof(msgitem), "{0080FF}Район:\t\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t\t{FFFFFF}%s\
\n{0080FF}Контроль:\t\t{FFFFFF}%s\
\n{0080FF}Цена входа:\t\t{33AA33}$%d\
\n{0080FF}Покупка продуктов:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Продажа товаров:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Сырья на складе:\t{FFFFFF}%d",//SBizInfo[sbouse][sbDiscription],
					tregion,  100+sbouse+1, SBizInfo[sbouse][sbOwner],
					GetFamilyName(SBizInfo[sbouse][sbExtortion]),
					SBizInfo[sbouse][sbEntranceCost],
					compcost*(100+SBizInfo[sbouse][sbBuyProd])/100.0, 100+SBizInfo[sbouse][sbBuyProd],
					compcost*(100+SBizInfo[sbouse][sbSellProd])/100.0, 100+SBizInfo[sbouse][sbSellProd],
					SBizInfo[sbouse][sbProducts]);

				format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t\t{33AA33}%d\
\n{0080FF}Экспорт[Импорт]:\t{33AA33}$%d{FFFFFF}[$%d]\
\n{0080FF}Зарплата:\t\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}В Кассе:\t\t{33AA33}$%d",
					msgitem,
					SBizInfo[sbouse][sbWorker],
					SBizInfo[sbouse][sbExport],SBizInfo[sbouse][sbImport],
					SBizInfo[sbouse][sbSalary],
					SBizInfo[sbouse][sbExpenses],
					//SBizInfo[sbouse][sbExport]-SBizInfo[sbouse][sbWorker]*SBizInfo[sbouse][sbSalary]-SBizInfo[sbouse][sbExpenses]);
					SBizInfo[sbouse][sbTill]);
				DIALOG_ID = DIALOG100;
				style = DIALOG_STYLE_MSGBOX;
		    }
		}
		else
		{
		    if(sbouse == 54 && PlayerInfo[playerid][pMushroom] > 0)//для грибников
		    {
				format(msgitem, sizeof(msgitem), "Эта Компания - для продажи\
\n{0080FF}Район:\t\t{FFFFFF}%s, %d\
\n{0080FF}Стоимость:\t{33AA33}$%d\
\n{0080FF}Цена входа:\t{33AA33}$%d\
\n{0080FF}Покупка продуктов:\t{33AA33}$%.2f[%d %%]\
\n{0080FF}Продажа товаров:\t{33AA33}$%.2f[%d %%]\
\n{0080FF}Грибов на складе:\t{33AA33}%d",
					tregion, 100+sbouse+1,
					SBizInfo[sbouse][sbBuyPrice],
					SBizInfo[sbouse][sbEntranceCost],
					compcost*(100+SBizInfo[sbouse][sbBuyProd])/100.0, 100+SBizInfo[sbouse][sbBuyProd],
					compcost*(100+SBizInfo[sbouse][sbSellProd])/100.0, 100+SBizInfo[sbouse][sbSellProd],
					SBizInfo[sbouse][sbProducts]);

				format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t{33AA33}%d\
\n{0080FF}Экспорт[Импорт]:\t{33AA33}$%d{FFFFFF}[$%d]\
\n{0080FF}Зарплата:\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}Баланс:\t{33AA33}$%d",
					msgitem,
					SBizInfo[sbouse][sbWorker],
					SBizInfo[sbouse][sbExport],SBizInfo[sbouse][sbImport],
					SBizInfo[sbouse][sbSalary],
					SBizInfo[sbouse][sbExpenses],
					//SBizInfo[sbouse][sbExport]-SBizInfo[sbouse][sbWorker]*SBizInfo[sbouse][sbSalary]-SBizInfo[sbouse][sbExpenses]);
					SBizInfo[sbouse][sbExport]-SBizInfo[sbouse][sbImport]);
				strins(msgitem, "\nДля покупки введите /buy. \nСтоимость пойдет в Банк", strlen(msgitem));
				strins(msgitem, "\n\n{AFAFAF}Введите кол-во грибов, которое хотите Сдать.", strlen(msgitem));
				strins(msgitem, "\n\n\t{8CAA63}По окончанию ввода нажмите OK.", strlen(msgitem));
				DIALOG_ID = MUSHROOMER_DIALOG;
				style = DIALOG_STYLE_INPUT;
		    }
		    else
		    {
				format(msgitem, sizeof(msgitem), "Эта Компания - для продажи\
\n{0080FF}Район:\t\t{FFFFFF}%s, %d\
\n{0080FF}Стоимость:\t{33AA33}$%d\
\n{0080FF}Цена входа:\t{33AA33}$%d\
\n{0080FF}Покупка продуктов:\t{33AA33}$%.2f[%d %%]\
\n{0080FF}Продажа товаров:\t{33AA33}$%.2f[%d %%]\
\n{0080FF}Сырья на складе:\t{33AA33}%d",//SBizInfo[sbouse][sbDiscription],
				tregion, 100+sbouse+1,
				SBizInfo[sbouse][sbBuyPrice],
				SBizInfo[sbouse][sbEntranceCost],
				compcost*(100+SBizInfo[sbouse][sbBuyProd])/100.0, 100+SBizInfo[sbouse][sbBuyProd],
				compcost*(100+SBizInfo[sbouse][sbSellProd])/100.0, 100+SBizInfo[sbouse][sbSellProd],
				SBizInfo[sbouse][sbProducts]);

				format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t{33AA33}%d\
\n{0080FF}Экспорт[Импорт]:\t{33AA33}$%d{FFFFFF}[$%d]\
\n{0080FF}Зарплата:\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}Баланс:\t{33AA33}$%d",
					msgitem,
					SBizInfo[sbouse][sbWorker],
					SBizInfo[sbouse][sbExport],SBizInfo[sbouse][sbImport],
					SBizInfo[sbouse][sbSalary],
					SBizInfo[sbouse][sbExpenses],
					SBizInfo[sbouse][sbExport]-SBizInfo[sbouse][sbImport]);
				strins(msgitem, "\n\n{AFAFAF}Для покупки введите /buy. \nСтоимость пойдет в Банк", strlen(msgitem));
				DIALOG_ID = DIALOG100;
				style = DIALOG_STYLE_MSGBOX;
			}
		}
		strins(msgitem, "\n{ffffff}_______________________________________________", strlen(msgitem));
		new caption[70];
		format(caption, sizeof(caption), "%s {0080FF}Уровень:\t{FFFFFF}%d %s",SBizInfo[sbouse][sbDiscription], SBizInfo[sbouse][sbLevel], TypeBranch(SBizInfo[sbouse][sbBranch]));
		ShowPlayerDialogGap(playerid, DIALOG_ID, style, caption, msgitem, "OK", "");
		gDialogStatus[playerid][2] = 5;
		
		if(CHECKING[PlayerPickUpPickup])
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "sbiz_OnPlayerPickUpPickup(playerid:%d, sbouse:%d) gDialogStatus:%d", playerid, sbouse, gDialogStatus[playerid][2]);
			//SendClientMessageToAll(COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
	}

	return 1;
}

forward Float: GetDistanceBizToPoint(bizid, Float:x2, Float:y2, Float:z2);
public Float: GetDistanceBizToPoint(bizid, Float:x2, Float:y2, Float:z2)//возвращает расстояние от биза до точки
{
	new Float: tmpdis = -1.0;
	if(bizid < 100)
	{
		tmpdis = floatsqroot(
			floatpower(floatsub(x2,BizInfo[bizid][bEntranceX]), 2)+
			floatpower(floatsub(y2,BizInfo[bizid][bEntranceY]), 2)+
			floatpower(floatsub(z2,BizInfo[bizid][bEntranceZ]), 2));
	}
	else
	{
		tmpdis = floatsqroot(
		floatpower(floatsub(x2,SBizInfo[bizid-100][sbEntranceX]), 2)+
		floatpower(floatsub(y2,SBizInfo[bizid-100][sbEntranceY]), 2)+
		floatpower(floatsub(z2,SBizInfo[bizid-100][sbEntranceZ]), 2));
	}
	return tmpdis;
}


stock OnSBizInit(bizid)
{
	SBizInfo[bizid][sbOwned] = 0;
	strmid(SBizInfo[bizid][sbOwner], "Банк", 0, strlen("Банк"), 20);//меняем имя владельца на The State
	//strmid(SBizInfo[bizid][sbExtortion], "No-One", 0, strlen("No-One"), 20);//меняем имя владельца на No-One
	SBizInfo[bizid][sbExtortion] = 0;
	SBizInfo[bizid][sbEntranceCost] = 0;
	SBizInfo[bizid][sbTill] = 1000+random(9000);//временно
	SBizInfo[bizid][sbLevel] = 1;
	SBizInfo[bizid][sbLock] = 0;//открыт, т.к. игргок забудет открыть
	SBizInfo[bizid][sbProducts] = 1000+random(9000);//временно
	SBizInfo[bizid][sbBuyProd] = 1;
	SBizInfo[bizid][sbSellProd] = 10;//15 для экономики
	SBizInfo[bizid][sbDate] = getdate();//записать день продажи
	SBizInfo[bizid][sbInkas] = 1000;
	SBizInfo[bizid][sbImport] = 0;//сколько денег потратил на покупку продуктов
	SBizInfo[bizid][sbExport] = 0;//сколько денег заработал на экспорте
	SBizInfo[bizid][sbWorker] = 0;
	SBizInfo[bizid][sbSalary] = 1;
}

stock SBizzAction(playerid, bizid)//для недвижимости STEP3
{
	new listitems[] = "/bizinfo - информация по компании\n\
/sellbiz - продать компанию\n\
/open - открыть/закрыть компанию\n\
/bizfee - установить входную плату\n\
/bizbuyprods - установить цену покупки продуктов\n\
/bizsellprods - установить цену продажи товаров\n\
/bizbank - пополнить денежную кассу\n\
/bizinkas - установить минимальный остаток денег\n\
/paycheck - установить оплату";
	DialogID[playerid][0] = bizid+200;
	MenuOperation[playerid] = 123;
	ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_LIST, SBizInfo[bizid][sbDiscription], listitems, "OK", "Cancel");
}


stock PrintSBizInfo(playerid, bizid)//вызывается по команде bizinfo
{
	new coordsstring[128+1+3+10+10+10];
	SendClientMessage(playerid, COLOR_GREEN, "_______________________________________");
	new locked[7];
	if(SBizInfo[bizid][sbLock] == 1) locked = "Закрыт";
	else locked = "Открыт";

	format(coordsstring, sizeof(coordsstring), "*** {FFFFFF}%s. %d уровень %s. %s {0080FF}***",
		SBizInfo[bizid][sbDiscription], SBizInfo[bizid][sbLevel], TypeBranch(SBizInfo[bizid][sbBranch]), locked);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, coordsstring);

	format(coordsstring, sizeof(coordsstring), "Цена за вход: {33AA33}$%d {FF6600}В Кассе: {33AA33}$%d {FF6600}Остаток: {33AA33}$%d",//%%\%%
		SBizInfo[bizid][sbEntranceCost], SBizInfo[bizid][sbTill], SBizInfo[bizid][sbInkas]);
	SendClientMessage(playerid, COLOR_ORANGE, coordsstring);


	new Float: buyprice; new Float: sellprice;
	if(bizid == 3 || bizid == 17 || (bizid >= GAS_STATION && bizid < PARKING))
	{
		buyprice = FuelCost*SBizInfo[bizid][sbBuyProd]/100.0;//цена покупки сырья
		sellprice = FuelCost*SBizInfo[bizid][sbSellProd]/100.0;//цена продажи товаров
		format(coordsstring, sizeof(coordsstring), "Товаров:{FFFFFF}%d {FF6600}Покупка:{33AA33}$%.2f{FFFFFF}[%d%%\%%] {FF6600}Продажа:{33AA33}$%.2f{FFFFFF}[%d%%\%%]",
			SBizInfo[bizid][sbProducts], buyprice, SBizInfo[bizid][sbBuyProd], sellprice, SBizInfo[bizid][sbSellProd]);
		SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}
	else
	{

		buyprice = compcost*(100+SBizInfo[bizid][sbBuyProd])/100.0;//цена покупки сырья
		sellprice = compcost*(100+SBizInfo[bizid][sbSellProd])/100.0;//цена продажи товаров
		format(coordsstring, sizeof(coordsstring), "Товаров:{FFFFFF}%d {FF6600}Покупка:{33AA33}$%.1f{FFFFFF}[%d%%\%%] {FF6600}Продажа:{33AA33}$%.1f{FFFFFF}[%d%%\%%]",
			SBizInfo[bizid][sbProducts], buyprice, SBizInfo[bizid][sbBuyProd], sellprice, SBizInfo[bizid][sbSellProd]);
		SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}

	format(coordsstring, sizeof(coordsstring), "Рабочих:{FFFFFF}%d {FF6600}Оплата:{33AA33}$%d {FF6600}Импорт:{33AA33}$%d {FF6600}Экспорт:{33AA33}$%d {FF6600}Баланс:{33AA33}$%d",
		SBizInfo[bizid][sbWorker], SBizInfo[bizid][sbSalary],
		SBizInfo[bizid][sbImport], SBizInfo[bizid][sbExport],
		(SBizInfo[bizid][sbExport]-SBizInfo[bizid][sbImport]));
	SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

	format(coordsstring, sizeof(coordsstring), "Дата покупки: {FFFFFF}%s[%d] {FF6600}Содержание в час: {33AA33}$%d",
		getDate(SBizInfo[bizid][sbDate]), SBizInfo[bizid][sbDate], SBizInfo[bizid][sbExpenses]);
	SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

	format(coordsstring, sizeof(coordsstring), "Контролирует: {FFFFFF}%s", GetFamilyName(SBizInfo[bizid][sbExtortion]));
	SendClientMessage(playerid, COLOR_ORANGE, coordsstring);


	new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
	new olddate = SBizInfo[bizid][sbDate];
//если в кассе денег хватает на покупку 100 продуктов
	if(SBizInfo[bizid][sbLevel] <= 1 && (curdate-olddate) <= gCheckProp)//gCheckProp = 7
	{
		format(coordsstring, sizeof(coordsstring), "Требуется поднять уровень, чтобы бизнес не обанкротился. {FFFFFF}Осталось %d дней.",
			gCheckProp-(curdate-olddate));
		SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}
	//if(GetProducts(b, BizInfo[b][bBranch]) >= 8*24) continue;
	new Float: price = compcost*(100+SBizInfo[bizid][sbBuyProd])/100.0;
	if( SBizInfo[bizid][sbProducts] < 100 || SBizInfo[bizid][sbTill] < floatround(100*price, floatround_floor) )
//если в бизнесе менее 100 товаров, то забрать //если в кассе денег не хватает на покупку 100 продуктов, то забрать
	{//если бизнес куплен больше 15 дней и до сих пор не вышел из нулевой рентабельности, то забрать

		format(coordsstring, sizeof(coordsstring), "Требуется {FFFFFF}%d{FF6600} товаров или {33AA33}$%d{FF6600}, чтобы бизнес не обанкротился.",
			100-SBizInfo[bizid][sbProducts], floatround(100*price, floatround_floor)-SBizInfo[bizid][sbTill]);
		SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}


	if( !(bizid >= GAS_STATION && bizid < PARKING+sizeof(Parking))
		&& bizid != 3 && bizid != 5 && bizid != 17 )
	{
		new export = (SBizInfo[bizid][sbLevel]+1)*levelexp*10000 - (SBizInfo[bizid][sbExport]-SBizInfo[bizid][sbImport]);//рентабильность = сколько надо - сколько есть
		new Float: prod_export = export/sellprice;//кол-во товаров для экспорта = рентабильность/цена продажи ед. товара
		format(coordsstring, sizeof(coordsstring), "До %d-го уровня требуется: {FFFFFF}продать %.0f товаров и получить с этого $%d дохода.", (SBizInfo[bizid][sbLevel]+1),
			prod_export, export);
		SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

		new Float: prod_onehour = 24*(100+SBizInfo[bizid][sbLevel])/100.0 - 1;//товаров в час производится

	 	new prod;//недостоющее кол-во продов
		if(SBizInfo[bizid][sbProducts] < prod_export) prod = floatround(prod_export, floatround_ceil) - SBizInfo[bizid][sbProducts];
		else prod = 0;
		new hours = floatround(prod/prod_onehour, floatround_ceil);//кол-во часов необходимое, чтобы получить недостающие товары
		format(coordsstring, sizeof(coordsstring), "На переработку необходимо: {FFFFFF}%d товаров, %d часов и %d сырья",
			prod, hours, 24*hours);
		SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}
	SendClientMessage(playerid, COLOR_GREEN, "_______________________________________");
}



stock sbiz_ListItem(playerid, sbouse, response, listitem, inputtext[])
{
//printf("SBizListItem - playerid: %d, bouse: %d, listitem: %d, inputtext: %s, Operation: %d", playerid, sbouse, listitem, inputtext, MenuOperation[playerid]);
	if(MenuOperation[playerid] == 122)//для недвижимости STEP2
	{
		SBizzAction(playerid, sbouse);//для недвижимости STEP3
	}
	else if(MenuOperation[playerid] == 123)//для недвижимости STEP4
	{
		if(!response) { PropertyHelp(playerid); return 1; }

		if(listitem == 0) PrintSBizInfo(playerid, sbouse);///bizinfo - информация по бизнесу
		else if(listitem == 1)///sellbiz - продать бизнес\n
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, SBizInfo[sbouse][sbEntranceX],SBizInfo[sbouse][sbEntranceY],SBizInfo[sbouse][sbEntranceZ]) )
			{
				format(strings, sizeof(strings), "Вы далеко от вашего бизнеса: %s[%d]", SBizInfo[sbouse][sbDiscription], sbouse);
				SendClientMessage(playerid, COLOR_GREY, strings);
				return 1;
			}
			//--------------------------------------------------------------
			if(PlayerInfo[playerid][pPurposeMurder] == 200+sbouse) PlayerInfo[playerid][pPurposeMurder] = 0;
			if(SBizInfo[sbouse][sbTill] < 0) { GivePlayerMoneyB(fbiz+sbouse, playerid, SBizInfo[sbouse][sbTill]); SBizInfo[sbouse][sbTill] = 0; }
			for(new limit = 0; limit < 20; limit++)
			{
				if(MyCompany[playerid][limit] != sbouse) continue;
				MyCompany[playerid][limit] = NOT_KEY;
				break;
			}

			//OnPlayerStatsUpdate(playerid);
			format(strings, sizeof(strings), "%s has sell sbiz %d", PlayerName(playerid), sbouse);
			Log(BUY,strings);

			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]", SBizInfo[sbouse][sbDiscription]);
			//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+sbouse], 0xEEEE88FF, strings);
			Update3DTextLabelEx(sbEntranceText3D[sbouse], 0xEEEE88FF, text_info);

			OnSBizInit(sbouse);
#if defined vw_sql//#endif
			SaveSBiz(sbouse);
#endif
			//format(strings, sizeof(strings), "~y~Congratulations~n~~w~You have sold your property for ~n~~g~$%d", SBizInfo[sbouse][sbBuyPrice]/2);
			GameTextForPlayerEx(playerid, "~y~Congratulations~n~~w~You have sold your property", 10000, 3);
		}
		else if(listitem == 2)//open - открыть/закрыть бизнес
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, SBizInfo[sbouse][sbEntranceX],SBizInfo[sbouse][sbEntranceY],SBizInfo[sbouse][sbEntranceZ]) )
			{
				format(strings, sizeof(strings), "Вы далеко от вашего бизнеса: %s[%d]", SBizInfo[sbouse][sbDiscription], sbouse);
				SendClientMessage(playerid, COLOR_GREY, strings);
				return 1;
			}
			if(SBizInfo[sbouse][sbLock] == 1)
			{
				SBizInfo[sbouse][sbLock] = 0;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				SBizInfo[sbouse][sbLock] = 1;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if(listitem == 3)///bizfee - установить входную плату
		{
			format(strings, sizeof(strings), "Сумма входной платы - $%d.\n\
				Введите сумму.\n\
				Минимум - $1, Максимум - $1000.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbEntranceCost]);
			MenuOperation[playerid] = 124;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 4)///bizbuyprods - установить цену покупки продуктов
		{
			format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
				Введите процент покупки.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd]);
			MenuOperation[playerid] = 125;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 5)///bizsellprods - установить цену продажи товаров
		{
			format(strings, sizeof(strings), "Процент продажи сырья = %d%%.\n\
				Введите процент продажи.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSellProd]);
			MenuOperation[playerid] = 126;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 6)///bizbank - пополнить денежную кассу
		{
			format(strings, sizeof(strings), "B кассе $%d.\n\
				Введите сумму перевода на счёт вашего бизнеса.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbTill], PlayerInfo[playerid][pBank]);
			MenuOperation[playerid] = 127;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 7)///bizinkas - установить минимальный остаток денег";
		{
			format(strings, sizeof(strings), "Мин. размер инкасации = $%d.\n\
				Введите сумму ограничения для вывоза денег.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbInkas], SBizInfo[sbouse][sbTill]);
			MenuOperation[playerid] = 128;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 8)//paycheck - установить оплату
		{
			MenuOperation[playerid] = 149;
			format(strings, sizeof(strings), "Оплата работникам = $%d.\n\
				Введите сумму оплаты перевозчикам за рейс.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSalary], 1000*SBizInfo[sbouse][sbLevel]);
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
		}
	}
	//------------------------------------------------------------------
	else if(MenuOperation[playerid] == 124)///bizfee
	{
		if(strval(inputtext) < 1 || strval(inputtext) > 1000)//для экономики
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Минимальная цена входа - $1, Максимальная цена входа - $1000.");
			format(strings, sizeof(strings), "Сумма входной платы - $%d.\n\
				Введите сумму входной платы.\n\
				Минимум - $1, Максимум - $1000.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbEntranceCost]);
			MenuOperation[playerid] = 124;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
			return 1;
		}

		if(sbouse == 2)
		{   //Phone Company
			if(strval(inputtext) < 1 || strval(inputtext) > 100)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная стоимость 1 минуты разговора - $1, Максимальная - $100.");
				return 1;
			}//SBizInfo[2][sbEntranceCost]
		}
		else if(sbouse == 3 || sbouse == 4 || sbouse == 17)//3 == 3
		{   //Fuel Company Red County
			//SendClientMessage(playerid, COLOR_WHITE, "Вы не имеете право изменять цену топлива.");
			if(strval(inputtext) < 1 || strval(inputtext) > 3)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная цена топлива - $1, Максимальная - $3.");
				return 1;
			}
		}
		/*else if(sbouse == 4)//3 == 3
		{   //Electro Company
			//SendClientMessage(playerid, COLOR_WHITE, "Вы не имеете право изменять цену топлива.");
			if(strval(inputtext) < 10 || strval(inputtext) > 20)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная цена кВт эл-ва - $10, Максимальная - $20.");
				return 1;
			}
		}*/
		else if(sbouse == 7)
		{   //CNN Studio
			if(strval(inputtext) < 1 || strval(inputtext) > 10)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная стоимость 1-го символа рекламы - $1, Максимальная - $10.");
				return 1;
			}
		}
		else if(sbouse == 8)
		{   //Tow Car Service
			if(strval(inputtext) < 50 || strval(inputtext) > 1000)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная стоимость возврата машины к дому - $50, Максимальная - $1000.");
				return 1;
			}
		}
		else if(sbouse == 12)
		{   //Sprunk
			if(strval(inputtext) < 1 || strval(inputtext) > 50)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная цена - $1, Максимальная - $50.");
				return 1;
			}
		}
		else if(sbouse == 13)
		{   //Vehicle Respray
			if(strval(inputtext) < 100 || strval(inputtext) > 100)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Цена покраски - $100.");
				return 1;
			}
		}
		/*else if(sbouse == 17)
		{   //Oil Company Bone County
			if(strval(inputtext) < 1 || strval(inputtext) > 3)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная цена топлива - $1, Максимальная - $3.");
				return 1;
			}
		}*/

		else if(sbouse >= 100+PARKING && sbouse < 100+PARKING+sizeof(Parking))
		{
	        if(PlayerInfo[playerid][pJob] != AUTOBUYER)//для скупщиков
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы - не Скупщик Авто !");
			    return 1;
			}
			if(strval(inputtext) < 10 || strval(inputtext) > 90)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Процент покупки авто (оплаты автоугонщикам) от 10 до 90 %%.");
				return 1;
			}
		}
		else
		{
			if(strval(inputtext) < 100 || strval(inputtext) > 1000)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   Минимальная стоимость входа в бизнес - $100, Максимальная - $1000.");
				return 1;
			}
		}
		SBizInfo[sbouse][sbEntranceCost] = strval(inputtext);
		format(strings, sizeof(strings), "Cтоимость входа установлена в $%d.", SBizInfo[sbouse][sbEntranceCost]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}

	else if(MenuOperation[playerid] == 125)///bizbuyprods - установить цену покупки продуктов
	{
		/*if(strval(inputtext) < 10 || strval(inputtext) > 100)//для экономики
		{
			format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
				Введите процент покупки.\n\
				Минимум - 10%%, Максимум - 100%%.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd]);
			MenuOperation[playerid] = 125);
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
			return 1;
		}*/
		if(SBizInfo[sbouse][sbTill] < 2250 && strval(inputtext) > SBizInfo[sbouse][sbBuyProd])
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы не можете повышать процент покупки при наличии в кассе менее $2250");
			return 1;
		}

		if(	sbouse >= GAS_STATION && sbouse < PARKING)
		{//если АЗС
		    if(strval(inputtext) < BizInfo[80][bSellProd]+10 || strval(inputtext) > 90)
		    {
				format(strings, sizeof(strings), "Процент покупки топлива = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd], BizInfo[80][bSellProd]+10, 90);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}

		}
		else if(sbouse >= PARKING && sbouse < PARKING+sizeof(Parking))
		{//если Паркинг
		    if(strval(inputtext) < 10 || strval(inputtext) > 90)
		    {
				format(strings, sizeof(strings), "Процент покупки машин = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd], 10, 90);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else if(sbouse >= 57 && sbouse <= 58)
		{//если свалка или СТО
		    if(strval(inputtext) < 1 || strval(inputtext) > 100)
		    {
				format(strings, sizeof(strings), "Процент покупки машин = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd], 1, 100);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else if(sbouse == 54)
		{//если MushroomVault
			if(strval(inputtext) < 40 || strval(inputtext) > 50)
			{
				format(strings, sizeof(strings), "Процент покупки грибов = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd], 40, 50);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else //if( !(sbouse >= GAS_STATION && sbouse < PARKING))
		{//если Компания, то продовать сырьё не больше чем покупает Склад
			if(strval(inputtext) < 1 || strval(inputtext) > 10)
			{
				format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbBuyProd], 1, 10);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		SBizInfo[sbouse][sbBuyProd] = strval(inputtext);
		format(strings, sizeof(strings), "Процент покупки продуктов установлен - %d%%\%%.", SBizInfo[sbouse][sbBuyProd]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 126)///bizsellprods - установить цену продажи товаров
	{
		if(	sbouse >= GAS_STATION && sbouse < PARKING)
		{//если АЗС
		    if(strval(inputtext) < SBizInfo[sbouse][sbBuyProd]+10 || strval(inputtext) > 100)
		    {
				format(strings, sizeof(strings), "Процент продажи топлива = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSellProd], SBizInfo[sbouse][sbBuyProd]+10, 100);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else if(sbouse >= PARKING && sbouse < PARKING+sizeof(Parking))
		{//если Паркинг
		    if(strval(inputtext) < 20 || strval(inputtext) > 100)
		    {
				format(strings, sizeof(strings), "Процент продажи машин = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSellProd], 20, 100);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else if(sbouse == 54)
		{//если MushroomVault
			if(strval(inputtext) < 50 || strval(inputtext) > 60)
			{
				format(strings, sizeof(strings), "Процент продажи грибов = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSellProd], 50, 60);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else //if( !(sbouse >= GAS_STATION && sbouse < PARKING))
		{//если Компания, то продовать сырьё не больше чем покупает Склад
			if(strval(inputtext) < 1 || strval(inputtext) > BizInfo[80][bBuyProd]-10)
			{
				format(strings, sizeof(strings), "Процент продажи сырья = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSellProd], 1, BizInfo[80][bBuyProd]-10);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		SBizInfo[sbouse][sbSellProd] = strval(inputtext);
		format(strings, sizeof(strings), "Процент продажи товаров (оплаты покупателем) установлен на %d%%\%%.", SBizInfo[sbouse][sbSellProd]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 127)///bizbank
	{
		new cashdeposit = strval(inputtext);
		if(PlayerInfo[playerid][pBank] < cashdeposit || cashdeposit < 1)
		{
			//SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько наличных для этого !");
			format(strings, sizeof(strings), "У вас нет столько наличных для этого !\n\
				B кассе $%d.\n\
				Введите сумму перевода на счёт вашего бизнеса.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbTill], PlayerInfo[playerid][pBank]);
			MenuOperation[playerid] = 127;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
			return 1;
		}
		if(	!IsPlayerInRangeOfPoint(playerid, 3.0, SBizInfo[sbouse][sbEntranceX],SBizInfo[sbouse][sbEntranceY],SBizInfo[sbouse][sbEntranceZ]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от вашего бизнеса !");
			return 1;
		}
		GivePlayerMoneyB(fsbiz+sbouse, playerid, -cashdeposit);
		//OnGangsExtortionBiz(sbouse, cashdeposit);
		SBizInfo[sbouse][sbTill] += cashdeposit;
		format(strings, sizeof(strings), " Bы пополнили вашу кассу на $%d. Итого: $%d ", cashdeposit, SBizInfo[sbouse][sbTill]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		//SaveSBiz(sbouse);
	}
	else if(MenuOperation[playerid] == 128)///bizinkas - установить минимальный остаток денег";
	{
		if(strval(inputtext) < 1 || strval(inputtext) > SBizInfo[sbouse][sbTill])
		{
			format(strings, sizeof(strings), "Мин. размер инкасации $%d.\n\
				Введите сумму ограничения.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbInkas], SBizInfo[sbouse][sbTill]);
			MenuOperation[playerid] = 128;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
			return 1;
		}
		SBizInfo[sbouse][sbInkas] = strval(inputtext);
		format(strings, sizeof(strings), "* Минимальное кол-во денег в бизе установлено $%d.", SBizInfo[sbouse][sbInkas]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 149)//paycheck - установить оплату
	{
		if(!response) { SBizzAction(playerid, sbouse); return 1; }
		if( response &&
			(strval(inputtext) < 1 || strval(inputtext) > 1000*SBizInfo[sbouse][sbLevel]))
		{
			MenuOperation[playerid] = 149;
			format(strings, sizeof(strings), "Оплата работникам = $%d.\n\
				Введите сумму оплаты перевозчикам за рейс.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", SBizInfo[sbouse][sbSalary], 1000*SBizInfo[sbouse][sbLevel]);
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, SBizInfo[sbouse][sbDiscription], strings, "OK", "Cancel");
			return 1;
		}
		SBizInfo[sbouse][sbSalary] = strval(inputtext);
		format(strings, sizeof(strings), "Оплата работникам установлена - $%d.", SBizInfo[sbouse][sbSalary]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	return 1;
}


stock OnCheckSBizz()//вызывается из OnPayDay5Timer
{   //проверка собственности каждый час, т.е. купленных бизов
//если продуктов стало меньше 10
//если в кассе денег не хватает на покупку 100 продуктов
//то биз банкрот
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{   //кроме банка
	  	if(sb >= PARKING && sb < PARKING+sizeof(Parking)) continue;
		if(SBizInfo[sb][sbOwned] == 0) continue;
		new olddate = SBizInfo[sb][sbDate];
		new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
		//if(curdate-olddate < gCheckProp) continue;//не надо проверки, т.к.проверяется на Банкротство
		//if(SBizInfo[sb][sbProducts] >= 100) continue;//т.к. у них у всех сырья больше 100
		new Float: price = compcost*(100+SBizInfo[sb][sbBuyProd])/100.0;//15*(100+1)/100 = 15,15
		if( !(SBizInfo[sb][sbLevel] <= 1 && curdate-olddate > gCheckProp) //если бизнес куплен больше 5 дней и до сих пор не вышел из нулевой рентабельности, то забрать
			&& SBizInfo[sb][sbTill] >= floatround(100*price, floatround_floor)//если в кассе денег не хватает на покупку 100 продуктов, то забрать
		  ) continue;
	  	//if(SBizInfo[sb][sbProducts] >= 100 && b >= GAS_STATION && b < PARKING) continue;
		new strtmp[103+20+2+24+10+10+10];
		new playername[MAX_PLAYER_NAME];
		strmid(playername, SBizInfo[sb][sbOwner], 0, strlen(SBizInfo[sb][sbOwner]), MAX_PLAYER_NAME);
		//mysql_real_escape_string(playername, playername);
		new giveplayerid = ReturnUser( playername );
		if( !IsPlayerConnected(giveplayerid) )
		{
			if(CheckExistPlayer(giveplayerid, playername) > 0) //return 1;
			{
	    		giveplayerid = MAX_PLAYERS-2;
	    		new ToBase[104];//77+24+3 = 104
				//format(ToBase, sizeof(ToBase), "SELECT `Account`,`Bank` FROM `players` WHERE `ID`=%d AND `Name`='%s' AND Account=0", sb, playername);
				format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE `Name`='%s' AND Account>=%d LIMIT 1", playername, getdate());
				mysql_query(ToBase); mysql_store_result();
				if(mysql_num_rows())
				{
					mysql_free_result(); continue; //return 1;
				}
				else mysql_free_result();

				/*format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bizz`="#NOT_KEY" WHERE `ID`=%d AND `Name`='%s'",
					sb, playername);
				mysql_query(ToBase);*/
			}
		}
		else
		{
			if(PlayerInfo[giveplayerid][pAccount] != 0) continue; //return 1;
			for(new limit = 0; limit < 20; limit++)
			{
				if(MyBizz[giveplayerid][limit] != sb) continue;
				MyBizz[giveplayerid][limit] = NOT_KEY;
			}
			PlayerInfo[giveplayerid][pBizz] = NOT_KEY;
			//PlayerInfo[giveplayerid][pBank] += SBizInfo[sb][sbBuyPrice];
			if(SBizInfo[sb][sbTill] < 0) { GivePlayerMoneyB(fbiz+sb, giveplayerid, SBizInfo[sb][sbTill]); SBizInfo[sb][sbTill] = 0; }
		}
		//--------------------------------------------------------------
		format(strtmp, sizeof(strtmp), "БАНКРОТ: Компания %s[%d] %s'а была выставлена на аукцион и продана (Level=%d, Till=$%d<$100*%.1f)",
			SBizInfo[sb][sbDiscription], sb, SBizInfo[sb][sbOwner], SBizInfo[sb][sbLevel], SBizInfo[sb][sbTill], price);
		SendClientMessageToAll(0xEEEE88FF, strtmp);

		//ИНФОРМИРОВАНИЕ
		format(strtmp, sizeof(strtmp), "REAL ESTATE: %s has sell sbiz %d (Level=%d, Till=$%d<$100*%.1f)",
			playername, sb, SBizInfo[sb][sbLevel], SBizInfo[sb][sbTill], price);
		Log(BUY,strtmp);

		OnSBizInit(sb);
#if defined vw_sql//#endif
		SaveSBiz(sb);
#endif
		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]",SBizInfo[sb][sbDiscription]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+sb], 0xEEEE88FF, strtmp);
		Update3DTextLabelEx(sbEntranceText3D[sb], 0xEEEE88FF, text_info);
	}
	return 1;
}

stock OnGangsExtortionSBiz(bizid, money)//запускается всякий раз когда в биз поступают деньги с продажи оружия или одежды или ...
{
	if(money <= 0) return 1;
	//if(SBizInfo[bizid][sbOwned] > 0)
	SBizInfo[bizid][sbTill] += money;
	SBizInfo[bizid][sbExport] += money;
	//else BizInfo[0][bProducts] += money;
	//--------------------------------------------------------------------------
    //if(!strcmp(SBizInfo[bizid][sbExtortion], "No-One", true))
    if(SBizInfo[bizid][sbExtortion] == 0)
	{   //если ни кем не контролируется то выйти чтобы не долбать сервер цыклом
	    return 1;
	}
	//new gangsname[20];
	for(new i = 1; i <= TEAM_MAFIA; i++)
	{   //сканируем все банды
		//strmid(gangsname, FamilyInfo[i][fName], 0, strlen(FamilyInfo[i][fName]), sizeof(gangsname));//Извлекает диапазон символов из строки.
		//if(!strcmp(SBizInfo[bizid][sbExtortion], FamilyInfo[i][fName], true))
		if(i == SBizInfo[bizid][sbExtortion])
		{   //если имя контролирующей банды этот бизнес совпало с найденным
		    //10 процентов от суммы перечислить в общак банды
			new value = floatround(money*30/100);
		    if(SBizInfo[bizid][sbOwned] > 0)
		    {
		    	FamilyInfo[i][fBank] += value;
				SBizInfo[bizid][sbTill] -= value;//уменьшить на эту сумму количество денег в бизе
			}
		    //else BizInfo[0][bTill] -= value;
			//format(strings, sizeof(strings), "Вам было перечислено $%d в общак.", value);
			//SendFamilyMessage(i, strings);
			break;
		}
	}
	return 1;
}
