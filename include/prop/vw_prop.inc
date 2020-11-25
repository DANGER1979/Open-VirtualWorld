
stock PropertyHelp(playerid)//для недвижимости STEP1  купленной LIST OF PROPERTIES
{//список купленной недвижимости //вызывается из меню игрока, по команде /prop
	new timers = GetTickCount();

	new DialogIDCounter = 0;
	for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;
   	new bigmsgitem[1925];//(31+2+20+2)*(5+10+20) = 1925
    //new strtmp[55];//31+2+20+2 = 55
	for(new limit = 0; limit < 5; limit++)
	{
		//if( PlayerInfo[playerid][pHouse] == NOT_KEY ) break;
		if(MyHouse[playerid][limit] == NOT_KEY) continue;
		new house = MyHouse[playerid][limit];
		format(bigmsgitem, sizeof(bigmsgitem), "%s{FFFFFF}%d: \t{00FF00}%s[%d]\n", bigmsgitem, DialogIDCounter+1, HouseInfo[house][hDiscription], house);
		//strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][DialogIDCounter] = house;
		DialogIDCounter ++;
	}
	for(new limit = 0; limit < 10; limit++)
	{
		if(MyBizz[playerid][limit] == NOT_KEY) continue;
		new bouse = MyBizz[playerid][limit];

		format(bigmsgitem, sizeof(bigmsgitem), "%s{FFFFFF}%d: \t{00FF00}%s[%d]\n", bigmsgitem, DialogIDCounter+1, BizInfo[bouse][bDiscription], bouse);
		//strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][DialogIDCounter] = 100+bouse;//номер биза по данному пункту
		DialogIDCounter ++;
	}

	for(new limit = 0; limit < 20; limit++)
	{
		if(MyCompany[playerid][limit] == NOT_KEY) continue;
		new sbouse = MyCompany[playerid][limit];

		format(bigmsgitem, sizeof(bigmsgitem), "%s{FFFFFF}%d: \t{00FF00}%s[%d]\n", bigmsgitem, DialogIDCounter+1, SBizInfo[sbouse][sbDiscription], sbouse);
		//strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][DialogIDCounter] = 200+sbouse;//номер биза по данному пункту
		DialogIDCounter ++;
	}

	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Property List by %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		PlayerMenu(playerid);
		SendClientMessage(playerid, COLOR_GREY, "   Property List пуст");//COLOR_BLUEGREY
		return 1;
	}
	MenuOperation[playerid] = 122;//для недвижимости STEP2
	format(strings, sizeof(strings), "Property List by %s", PlayerName(playerid));
	ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_LIST, strings, bigmsgitem, "OK", "Назад");

	TestLog(OPTIM, "PropertyHelp", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}

stock prop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != PROP_DIALOG) return 1;//для владения несколькими бизами
	if(!response)
	{//если в СПИСКЕ НЕДВИЖИМОСТИ LIST OF PROPERTIES нажали НАЗАД
		//if(MenuOperation[playerid] == 123) PropertyHelp(playerid);//если вошли в //ControlMenu
		//else if(MenuOperation[playerid] == 123) ControlMenu(playerid, bizid);
		//else
		PlayerMenu(playerid);//перейти в меню игрока
		return 1;
	}
	new house = -1, bouse = -1, sbouse = -1;
	if(MenuOperation[playerid] == 122 && listitem != -1)
	{//когда мы выбираем недвижимость из списка первый раз
		if(!response) { return 1; }
		if(DialogID[playerid][listitem] < 100 && DialogID[playerid][listitem] != -1) house = DialogID[playerid][listitem];
		else if(DialogID[playerid][listitem] >= 100 && DialogID[playerid][listitem] < 200) bouse = DialogID[playerid][listitem]-100;
		else if(DialogID[playerid][listitem] >= 200) sbouse = DialogID[playerid][listitem]-200;// && DialogID[playerid][listitem] < 255 //#define MAX_SBIZ 60
//printf("playerid: %d, DialogID: %d, listitem: %d, inputtext: %s, Operation: %d", playerid, DialogID[playerid][listitem], listitem, inputtext, MenuOperation[playerid]);
	}
	else
	{   //когды мы выбрали недвижимость и уже работаем только с ней
		if(DialogID[playerid][0] < 100 && DialogID[playerid][0] != -1) house = DialogID[playerid][0];
		else if(DialogID[playerid][0] >= 100 && DialogID[playerid][0] < 200) bouse = DialogID[playerid][0]-100;
		else if(DialogID[playerid][0] >= 200) sbouse = DialogID[playerid][0]-200;// && DialogID[playerid][0] < 255
//printf("playerid: %d, DialogID: %d, listitem: %d, inputtext: %s, Operation: %d", playerid, DialogID[playerid][0], listitem, inputtext, MenuOperation[playerid]);
	}
	if(house != -1)
	{
		//house_ListItem(playerid, house, response, listitem, inputtext);
		SetPVarInt(playerid, "House", house);
		house_ControlMenu(playerid, house);
	}
	else if(bouse != -1)
	{
	    SetPVarInt(playerid, "Bouse", bouse);
		biz_ControlMenu(playerid, bouse);
	}
	else if(sbouse != -1)
	{
		SetPVarInt(playerid, "SBouse", sbouse);
		sbiz_ListItem(playerid, sbouse, response, listitem, inputtext);//для недвижимости STEP2
	}
	return 1;
}

/*stock prop_OnPlayerPickUpPickup(playerid, pickupid)
//stock PropertyOnPlayerPickUp(playerid, pickupid)
{   //вызывается из OnPlayerPickUpPickup только при подборе пикапа
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return 1; }
	if(pickupid < (STAIRWAYS*2-2) || pickupid >= (STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ)) return 1;
//STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ + MAX_VEHICLE_PICKUPS	//35*2 + (52*2+12)+82*2+59 = 409
//12 - максимальное кол-во раздевалок
	//new local = PlayerInfo[playerid][pLocal];
	new msgitem[868];//542+52+57+57 + 38+32+25+35+3+3+5+5 + 14 = 868

	new tregion[20];
	strmid(tregion, "Unknown_Region", 0, strlen("Unknown_Region"), 20);
	new house, bouse, sbouse;//оставляем по нулям, чтобы не было за пределами массива


	if(CHECKING == 1)
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "PropertyOnPlayerPickUp(playerid:%d, house:%d, bouse:%d, sbouse:%d)", playerid, house, bouse, sbouse);
		//SendClientMessageToAll(COLOR_GREEN, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	return 1;
}*/


stock prop_CMD_buy(playerid)
{
		new strcmd[MAX_STRING];//, tmp[MAX_STRING], gMessage[MAX_STRING];
		if(PlayerInfo[playerid][pMember] == Hitman && PlayerInfo[playerid][pLeader] != Hitman)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Киллеры не могут иметь недвижимость !");
			return 1;
		}
		new Float:oldposx, Float:oldposy, Float:oldposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		for(new h = 0; h < MAX_HOUSE; h++)
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 1.3,
				HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]) ||
				HouseInfo[h][hOwned] > 0) continue;
	 		new index;
			for(new limit = 0; limit < 5; limit++)
			{
				if(MyHouse[playerid][limit] == NOT_KEY) continue;
				index ++;
			}
			if(index >= 5)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже имееме в наличии 5 домов, введите /prop, чтобы продать и купить другой!");
				return 1;
			}
			/*if(PlayerInfo[playerid][pLevel] < HouseInfo[h][hLevel])
			{
				format(strcmd, sizeof(strcmd), "   Bы должны быть уровня %d, чтобы купить этот дом !", HouseInfo[h][hLevel]);
				SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}*/
			/*if((PlayerInfo[playerid][pLevel] - HouseInfo[h][hLevel]) > 3 &&
				PlayerInfo[playerid][pLevel] < 23  && numplayers >= 50)
			{
				format(strcmd, sizeof(strcmd), "   Bы не можете купить дом ниже %d-го уровня!", PlayerInfo[playerid][pLevel]-3);
				SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}*/
			if(GetPlayerMoneyH(playerid) < HouseInfo[h][hBuyPrice])
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 0 || PlayerInfo[playerid][pBank] < 0 || PlayerInfo[playerid][pDeposit] < 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас зафиксирован минусовой баланс!");
				return 1;
			}
			for(new limit = 0; limit < 5; limit++)
			{
				if(MyHouse[playerid][limit] != NOT_KEY) continue;//пропускаем занятые ячейки
				MyHouse[playerid][limit] = h;
				break;
			}

			PlayerInfo[playerid][pHouse] = h;
			HouseInfo[h][hOwned] = PlayerInfo[playerid][pSQLID];
			HouseInfo[h][hLock] = 1;
			//HouseInfo[h][hRentabil] = 1;
			strmid(HouseInfo[h][hOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
			GivePlayerMoneyH(h, playerid, -HouseInfo[h][hBuyPrice]);
			//BizInfo[0][bProducts] += HouseInfo[h][hBuyPrice];//перечислили деньги в БАНК
			BizInfo[0][bTill] += HouseInfo[h][hBuyPrice];
			//BizInfo[0][bExport] += HouseInfo[h][hBuyPrice];
			PlayerPlayMusic(playerid);
			PlayerInfo[playerid][pLocal] = h;
			SetPlayerVirtualWorldEx(playerid, h+1);
			SetPlayerInteriorEx(playerid, HouseInfo[h][hInt]);
			SetPlayerPosEx(playerid, HouseInfo[h][hExitX],HouseInfo[h][hExitY],HouseInfo[h][hExitZ], 0);

			new text_info[19+20+24];
			format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", HouseInfo[h][hDiscription], HouseInfo[h][hOwner]);
			Update3DTextLabelEx(hEntranceText3D[h], 0xAAAAFFFF, text_info);

			OnSaveDateProp(playerid, h);//записывает день покупки дома

			format(strcmd, sizeof(strcmd), "%s has buy house %d for $%d", PlayerName(playerid), h, HouseInfo[h][hBuyPrice]);
			Log(BUY,strcmd);
			//OnPlayerStatsUpdate(playerid);//запустить ф-ию сохранения параметров игрока
#if defined vw_sql//#endif
			SaveHouseSQL(h);
#else
			HouseInfo_Save();
#endif
			GameTextForPlayerEx(playerid, "~w~Welcome Home~n~You can exit at any time by moving to this door and typing /exit", 5000, 3);
			SendClientMessage(playerid, COLOR_WHITE, "Поздравляем с покупкой ! Введите /prop, чтобы получить справку по собственности !");
			SetPVarInt(playerid, "gGotPermit", 0);
			return 1;//break;
		}
		for(new b = 1; b < MAX_BIZ-2; b++)
		{//пропускаем банк, склад и доки
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]) && BizInfo[b][bOwned] == 0) continue;
			if(BizInfo[b][bOwned] > 0) continue;
	 		new index;
			for(new limit = 0; limit < 10; limit++)
			{
				if(MyBizz[playerid][limit] != NOT_KEY) index ++;
			}
			if(index >= 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже имеете в наличии 10 бизнесов, введите /prop, чтобы продать и купить другой!");
				return 1;
			}
			/*if(PlayerInfo[playerid][pLevel] < BizInfo[b][bLevel])
			{
				format(strcmd, sizeof(strcmd), "   Bы Должны Иметь Уровень %d, чтобы Приобрести Это",BizInfo[b][bLevel]);
				SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}*/
			/*if(	GetPVarInt(playerid, "gGotPermit") != 2 &&//если нет разрешения
				strcmp(FamilyInfo[DoJ][fLeader], "No-One", true) &&//если нет лидера
				FamilyInfo[DoJ][fMembers] != 0 &&//если кол-во членов в министерстве больше нуля
				//numplayers >= 10 &&//если онлайн больше 30
				PlayerInfo[playerid][pAccount] == 0)//если нет вип акааунта
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас нет Разрешения на покупку! Обращайтесь в Мэрию к Солиситору или Губернатору !");
				return 1;
			}*/
			if(BizInfo[b][bTill] < 0) BizInfo[b][bTill] = 0;
			if(GetPlayerMoneyH(playerid) < (BizInfo[b][bBuyPrice]+BizInfo[b][bTill]))
			{
				format(strcmd, sizeof(strcmd), "   У вас нет $%d наличных для этого !", (BizInfo[b][bBuyPrice]+BizInfo[b][bTill]));
				SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 0 || PlayerInfo[playerid][pBank] < 0 || PlayerInfo[playerid][pDeposit] < 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас зафиксирован минусовой баланс!");
				return 1;
			}
			for(new limit = 0; limit < 10; limit++)
			{
				if(MyBizz[playerid][limit] != NOT_KEY) continue;//пропускаем занятые ячейки
				MyBizz[playerid][limit] = b; break;
			}
			BizInfo[b][bOwned] = PlayerInfo[playerid][pSQLID];
			strmid(BizInfo[b][bOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
			BizInfo[b][bLock] = 0;
			//if(BizInfo[b][bProducts] < 100) BizInfo[b][bProducts] = 100;

			GivePlayerMoneyH(fbiz+b, playerid, -(BizInfo[b][bBuyPrice]+BizInfo[b][bTill]));//сначало у игрока, а потом у биза
			//BizInfo[b][bTill] += BizInfo[b][bBuyPrice];
			BizInfo[0][bTill] += BizInfo[b][bBuyPrice];
			new curdate = getdate();//Получает текущий день в году
			BizInfo[b][bDate] = curdate;//записать день покупки
			SetPVarInt(playerid, "gGotPermit", 0);

			PlayerPlayMusic(playerid);
			format(strcmd, sizeof(strcmd), "%s has buy biz %d for $%d", PlayerName(playerid), b, BizInfo[b][bBuyPrice]);
			Log(BUY,strcmd);

			new text_info[19+20+24];
			format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", BizInfo[b][bDiscription], BizInfo[b][bOwner]);
			//Update3DTextLabelText(text3D[MAX_HOUSE+b], 0xAAAAFFFF, strcmd);
			//UpdatePlayer3DTextLabelTextEx(playerid, MAX_HOUSE+b, 0xAAAAFFFF, text_info);
			Update3DTextLabelEx(bEntranceText3D[b], 0xAAAAFFFF, text_info);
#if defined vw_sql//#endif
			SaveBiz(b);
#else
			BizInfo_Save();
#endif
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Поздравляем с новой покупкой. Введите /prop, чтобы посмотреть справку по бизнесу.");
			return 1;//break;
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ])) continue;
			if(SBizInfo[sb][sbOwned] > 0) continue;
	 		new index;
			for(new limit = 0; limit < 20; limit++)
			{
				if(MyCompany[playerid][limit] == NOT_KEY) continue;
				index ++;
			}
			if(index >= 20)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже имееме в наличии 20 компаний, введите /prop, чтобы продать и купить другую!");
				return 1;
			}
			/*if(PlayerInfo[playerid][pLevel] < SBizInfo[sb][sbLevel])
			{
				format(strcmd, sizeof(strcmd), "   Bы должны быть уровня %d, чтобы купить это",SBizInfo[sb][sbLevel]);
				SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}*/
			/*if(	GetPVarInt(playerid, "gGotPermit") != 3 &&//если нет разрешения
				strcmp(FamilyInfo[DoJ][fLeader], "No-One", true) &&//если нет лидера
				FamilyInfo[DoJ][fMembers] != 0 &&//если кол-во членов в министерстве больше нуля
				//numplayers >= 10 &&//если онлайн больше 30
				PlayerInfo[playerid][pAccount] == 0)//если нет вип акааунта
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас нет Разрешения на покупку! Обращайтесь в Мэрию к Солиситору или Губернатору !");
				return 1;
			}*/
			if(SBizInfo[sb][sbTill] < 0) SBizInfo[sb][sbTill] = 0;
			if(GetPlayerMoneyH(playerid) < (SBizInfo[sb][sbBuyPrice]+SBizInfo[sb][sbTill]))
			{
				format(strcmd, sizeof(strcmd), "   У вас нет $%d наличных для этого !", (SBizInfo[sb][sbBuyPrice]+SBizInfo[sb][sbTill]));
				SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 0 || PlayerInfo[playerid][pBank] < 0 || PlayerInfo[playerid][pDeposit] < 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас зафиксирован минусовой баланс!");
				return 1;
			}
			/*if(sb >= PARKING && sb < PARKING+sizeof(Parking))
			{
				if(PlayerInfo[playerid][pJob] != AUTOBUYER)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не скупщик авто, чтобы купить парковку авто!");
					return 1;
				}
				SBizInfo[sb][sbTill] += SBizInfo[sb][sbBuyPrice];//перевели цену биза на его кассу
			}
			else TAX += SBizInfo[sb][sbBuyPrice];//BizInfo[0][bProducts] += SBizInfo[sb][sbBuyPrice];//перечислили деньги в БАНК
*/

			for(new limit = 0; limit < 20; limit++)
			{
				if(MyCompany[playerid][limit] != NOT_KEY) continue;//пропускаем занятые ячейки
				MyCompany[playerid][limit] = sb; break;
			}
			SBizInfo[sb][sbOwned] = PlayerInfo[playerid][pSQLID];
			strmid(SBizInfo[sb][sbOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
			SBizInfo[sb][sbLock] = 0;
			//if(SBizInfo[sb][sbProducts] < 100 && !(sb >= PARKING && sb < PARKING+sizeof(Parking))) SBizInfo[sb][sbProducts] = 100;

			GivePlayerMoneyH(fsbiz+sb, playerid, -(SBizInfo[sb][sbBuyPrice]+SBizInfo[sb][sbTill]));//сначало у игрока, а потом у биза
			//SBizInfo[sb][sbTill] += SBizInfo[sb][sbBuyPrice];
			BizInfo[0][bTill] += SBizInfo[sb][sbBuyPrice];
			new curdate = getdate();//Получает текущий день в году
			SBizInfo[sb][sbDate] = curdate;//записать день покупки
			SetPVarInt(playerid, "gGotPermit", 0);

			//OnSaveDateSBizz(playerid);//записывает день покупки биза
			format(strcmd, sizeof(strcmd), "%s has buy sbiz %d for $%d", PlayerName(playerid), sb+100, SBizInfo[sb][sbBuyPrice]);
			Log(BUY,strcmd);

			new text_info[19+20+24];
			format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", SBizInfo[sb][sbDiscription], SBizInfo[sb][sbOwner]);
			//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+sb], 0xAAAAFFFF, strcmd);
			//UpdatePlayer3DTextLabelTextEx(playerid, MAX_HOUSE+MAX_BIZ+sb, 0xAAAAFFFF, text_info);
			Update3DTextLabelEx(sbEntranceText3D[sb], 0xAAAAFFFF, text_info);
#if defined vw_sql//#endif
			SaveSBiz(sb);
#else
			SBizInfo_Save();
#endif
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Поздравляем с новой покупкой. Введите /prop, чтобы посмотреть справку по бизнесу.");
			break;
		}
		return 1;
}



stock prop_OnGameModeInit()
{
	new time = GetTickCount();
	//new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
	//db_prop = db_open("Property/prop.db");
#if defined vw_sql//#endif
	LoadHousesSQL();
	LoadBizSQL();
	LoadSBizSQL();
#else
	#if defined vw_props//#endif
		HouseInfo_Load();
		BizInfo_Load();//db_LoadBiz();//BizInfo_Load();
		SBizInfo_Load();
	#else
		for(new h = 0; h < MAX_HOUSE; h++)
		{
		 	OnHouseInit(h);
		}
		//------------------------------------------------------------------
		for(new b=0; b<MAX_BIZ; b++)
		{
			OnBizInit(b);
		}
		BizInfo[0][bTill] = 1000000000;
		BizInfo[0][bBuyProd] = 5;
		BizInfo[0][bSellProd] = 10;

		SBizInfo[54][sbBuyProd] = 40;//MushroomVault
		SBizInfo[54][sbSellProd] = 60;
	//СКЛАД
		BizInfo[80][bBuyProd] = 60;
		BizInfo[80][bSellProd] = 70;
		BizInfo[80][bTill] = 1000000;
		BizInfo[80][bInkas] = 100000;
	//ПОРТ
		BizInfo[81][bBuyProd] = 80;//цена покупки товаров ПОРТом
		BizInfo[81][bSellProd] = 10;//цена продажи сырья
		BizInfo[81][bTill] = 1000000;//чтобы грузчики могли работать
		BizInfo[81][bInkas] = 1000000;
		
		//------------------------------------------------------------------
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{
			OnSBizInit(sb);
		}//для экономики

		SBizInfo[0][sbEntranceCost] = 100;//100 начальная стоимость аренды тачки
		SBizInfo[1][sbEntranceCost] = 100;//100 начальная стоимость аренды тачки

		SBizInfo[2][sbEntranceCost] = 10;//100 начальная стоимость 1 минуты разговора
		SBizInfo[3][sbEntranceCost] = 1;//начальная цена 1 л топлива
		SBizInfo[4][sbEntranceCost] = 17;//173 начальная цена 1кВт эл-ва
		SBizInfo[7][sbEntranceCost] = 3;//25 начальная стоимость 1-го символа рекламы
		SBizInfo[8][sbEntranceCost] = 500;//500 начальная стоимость возврата машины к дому

		SBizInfo[17][sbBuyProd] = 50;//Oil Company
		SBizInfo[17][sbSellProd] = 60;
		SBizInfo[3][sbBuyProd] = 70;//	Gas Company
		SBizInfo[3][sbSellProd] = 80;

		for(new sb = GAS_STATION; sb < PARKING; sb++)
		{
			SBizInfo[sb][sbProducts] = 10000;
			SBizInfo[sb][sbBuyProd] = 40;//GasStation
			SBizInfo[sb][sbSellProd] = 50;
			SBizInfo[sb][sbInkas] = 100000;
		}//для экономики

		for(new sb = PARKING; sb < PARKING+sizeof(Parking); sb++)
		{
			SBizInfo[sb][sbProducts] = 0;
		}//для экономики

		SBizInfo[52][sbTill] = 1000000;//ферма
		SBizInfo[52][sbInkas] = 100000;
		SBizInfo[55][sbTill] = 1000000;//шахта
		SBizInfo[55][sbInkas] = 100000;
	#endif
#endif



 	//------------------------------------------------------------------
 	//для вайпа
	/*for(new vid=1; vid<MAX_VEHICLES-1; vid++)
	{
		VehInfo[vid][cInsur] = 0;
		DestroyVehicleEx(vid, 10);
	}*/


	//------------------------------------------------------------------
	//new strtmp[25+24];
	//format(strtmp, sizeof(strtmp), "AdmCmd: %s Full resetted", playername);
	//Log(ADMINLOG, strtmp);
	//SendClientMessage(playerid, COLOR_GREY, "   Вся недвижимость продана !");
	//SendClientMessageToAll(COLOR_YELLOW, "   Вся недвижимость продана !");

	//format(strtmp, sizeof(strtmp), "AdmCmd: %s has done reset server", playername);
	//Log(ADMINLOG,  strtmp);

	printf("   Инициализация параметров недвижимости закончена, потрачено - %d (ms)", (GetTickCount()-time));
	//return 1;

}
stock prop_OnGameModeExit()
//public OnFilterScriptExit()
{//все созданные объекты этим скриптом должны быть уничтожены, но не уничтожая объекты созданные модом
#if defined vw_sql//#endif
	SaveHousesSQL();
	SaveBizSQL();
	SaveSBizSQL();
#else
	HouseInfo_Save();
	BizInfo_Save();
	SBizInfo_Save();
#endif

	//if(db_prop) db_close(db_prop);
}

stock prop_OnPlayerConnect(playerid)
{
//------------------------------------------------------------------------------
//обязательно записываем 255 во все ячейки массива
	for(new limit = 0; limit < 5; limit++)
	{
		MyHouse[playerid][limit] = NOT_KEY;
	}
	for(new limit = 0; limit < 10; limit++)
	{
		MyBizz[playerid][limit] = NOT_KEY;
	}
	for(new limit = 0; limit < 20; limit++)
	{
		MyCompany[playerid][limit] = NOT_KEY;
	}
//------------------------------------------------------------------------------
	new playername[MAX_PLAYER_NAME];//имя назначаемого админа
	if(playerid != MAX_PLAYERS-1) GetPlayerName(playerid, playername, sizeof(playername));
	new propcounter;
	for(new h = 0; h < MAX_HOUSE; h++)
	{   //сканируем все дома
		if( strcmp(playername, HouseInfo[h][hOwner], true) ) continue;//пропускаем если имя не свопадает с владельцем дома
		for(new limit = 0; limit < 5; limit++)
		{
			if( MyHouse[playerid][limit] != NOT_KEY) continue;//пропускаем занятые ячейки
			MyHouse[playerid][limit] = h;//находим свободную и записываем туда ИД купленного дома
			propcounter ++;
			break;
		}
	}
	for(new b = 0; b < MAX_BIZ; b++)
	{   //сканируем все дома
		if( strcmp(playername, BizInfo[b][bOwner], true) ) continue;
		for(new limit = 0; limit < 10; limit++)
		{
			if(	MyBizz[playerid][limit] != NOT_KEY) continue;//пропускаем занятые ячейки
			MyBizz[playerid][limit] = b;
			propcounter ++;
			break;
		}
	}
	for(new sb = 0; sb < MAX_SBIZ; sb++)
	{   //сканируем все дома
		if( strcmp(playername, SBizInfo[sb][sbOwner], true) ) continue;
		for(new limit = 0; limit < 20; limit++)
		{
			if(	MyCompany[playerid][limit] != NOT_KEY) continue;//пропускаем занятые ячейки
			MyCompany[playerid][limit] = sb;
			propcounter ++;
			break;
		}
	}
	//ИНФОРМИРОВАНИЕ
	format(strings, sizeof(strings), "У вас %d из 35 объектов недвижимости. Наберите (USE: /prop), чтобы просмотреть.", propcounter);
	SendClientMessage(playerid, COLOR_PURPLE, strings);
}

stock prop_OneHourTimer()
{
	for(new b = 1; b < MAX_BIZ-2; b++)
	{//пропускаем банк, доки и склад
		if(BizInfo[b][bOwned] == 0) continue;//пропускаем не купленные
		//if(BizInfo[b][bLock] == 1) continue;//пропускаем закрытые //чтобы переработка шла при закрытом
		//if(BizInfo[b][bWorker] <= 0) continue;
		//BizInfo[b][bTill] += floatround(1.0+BizInfo[b][bWorker]/10.0)*1000; //Базовый доход магазина, в день: 1,000
//скорость производства товаров 24 единицы в день при наличии необходимого кол-ва материалов.
		new prod = 8*24;
		if(BizInfo[b][bMetal] >= prod) { BizInfo[b][bMetal] -= prod; BizInfo[b][bProducts] += floatround(prod*(100+BizInfo[b][bLevel])/100.0, floatround_ceil); }
		if(BizInfo[b][bTextiles] >= prod) { BizInfo[b][bTextiles] -= prod; BizInfo[b][bProducts] += floatround(prod*(100+BizInfo[b][bLevel])/100.0, floatround_ceil); }
		if(BizInfo[b][bProvisions] >= prod) { BizInfo[b][bProvisions] -= prod; BizInfo[b][bProducts] += floatround(prod*(100+BizInfo[b][bLevel])/100.0, floatround_ceil); }
		if(BizInfo[b][bTree] >= prod) { BizInfo[b][bTree] -= prod; BizInfo[b][bProducts] += floatround(prod*(100+BizInfo[b][bLevel])/100.0, floatround_ceil); }
		if(BizInfo[b][bFuel] >= prod) { BizInfo[b][bFuel] -= prod; BizInfo[b][bProducts] += floatround(prod*(100+BizInfo[b][bLevel])/100.0, floatround_ceil); }
		/*if(BizInfo[b][bTill] > (floatround(BizInfo[b][bProducts]*24) && BizInfo[b][bTill] > 118)
		{
			if((curdate > gday)
			{//если сменились сутки
				gday = curdate;
				BizInfo[b][bTill] -= floatround(BizInfo[b][bProducts]*24 );	//Стоимость хранения: $24 за единицу в сутки.
			}
		}*/
		if(BizInfo[b][bTill] > 0 && BizInfo[b][bLevel] > 1)
		{
			BizInfo[b][bTill] -= BizInfo[b][bExpenses]; //Средняя арендная плата бизнеса 1 уровня(BizInfo[b][bLevel]) $118 в час.
			BizInfo[b][bImport] += BizInfo[b][bExpenses];//BizInfo[b][bLevel]*
			if(BizInfo[0][bTill]+BizInfo[b][bLevel]*BizInfo[b][bExpenses] < 2147480000) { BizInfo[0][bTill] += BizInfo[b][bExpenses]; BizInfo[0][bExport] += BizInfo[b][bExpenses]; }
		}
		 //&& BizInfo[b][bLock] == 0
		if(BizInfo[b][bProducts] > 0) BizInfo[b][bProducts] -= 1;//Магазин расходует 1 товар в час.
		//товары мы должны экспортировать, т.е. вывозить на грузовиках в доки.
	}
	//---------------------------------------------------------------------------
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{//пропускаем от фермы до базы механов
		if(sb >= PARKING && sb < PARKING+sizeof(Parking)) continue;//пропускаем паркинги
		if(/*sb == 8 || */sb == 51 || sb == 52 || sb == 53/* || sb == 54*/ || sb == 55 || sb == 56/* || sb == 57*/ || sb == 58) continue;
//пропускаем Tow Car Service sb == 8 и от дамбы начиная
//пропускаем MushroomVault sb == 54
//пропускаем свалку sb == 57, т.к. от туда только идут расход сырья и товарова
		//if(SBizInfo[sb][sbOwned] == 0) continue;//нефтянки должны работать иначе топливный кризис
		//if(SBizInfo[sb][sbLock] == 1) continue;//пропускаем закрытые  //чтобы переработка шла при закрытом

		/*if(sb >= GAS_STATION && sb < PARKING)
		{//коэф. 1 при онлайне 30
			SBizInfo[sb][sbProducts] += floatround(24.0*(numplayers/10.0)*(100.0+SBizInfo[sb][sbLevel])/100.0, floatround_ceil);
			//24*(20/10)*(100+1)/100 = 48,48
		}//24 литра каждый час
		else*/
		if(sb == 3 || sb == 4 || sb == 17)//5 - Car Delivery // || sb == 5
		{//22 АЗС на сервере
			//SBizInfo[sb][sbProducts] += floatround((PARKING-GAS_STATION)*24.0*(numplayers/10.0)*(100.0+SBizInfo[sb][sbLevel])/100.0, floatround_ceil);
			SBizInfo[sb][sbProducts] += floatround(24.0*(100.0+SBizInfo[sb][sbLevel])/100.0, floatround_ceil);
			//(40-18)*24*(20/10)*(100+1)/100 = 1066,56
		}
		else SBizInfo[sb][sbProducts] += floatround(100.0*(100.0+SBizInfo[sb][sbLevel])/100.0, floatround_ceil);
		//24*(100+1)/100 = 24,24



//АРЕНДА
		if(SBizInfo[sb][sbTill] > 0 && SBizInfo[sb][sbLevel] > 1)
		{//расход не должен превышать SBizInfo[sb][sbProducts]*price
			SBizInfo[sb][sbTill] -= SBizInfo[sb][sbExpenses]; //Средняя арендная плата бизнеса 1 уровня(BizInfo[b][bLevel]) $118 в час.
			SBizInfo[sb][sbImport] += SBizInfo[sb][sbExpenses];//SBizInfo[sb][sbLevel]*
			if(BizInfo[0][bTill]+SBizInfo[sb][sbExpenses] < 2147480000)//45*50 = 2250
			{ BizInfo[0][bTill] += SBizInfo[sb][sbExpenses]; BizInfo[0][bExport] += SBizInfo[sb][sbExpenses]; }
		}
		if(SBizInfo[sb][sbProducts] > 0) SBizInfo[sb][sbProducts] -= 1;//компания расходует 1 товар в час.
		//чтобы слетали, если владелец не заботится
	}
}




stock prop_OnVehiclePaintjob(playerid, vehicleid, paintjobid, interiorid)
{
	#pragma unused vehicleid
	#pragma unused paintjobid
	if(interiorid == 1)
	{   //TransFender   //14 //16 //18
		PlayerInfo[playerid][pCash] -= 500;
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(14, 500);
			SBizInfo[14][sbProducts] --;
		}
	}
	else if(interiorid == 2)
	{   //LocoLowCo
		PlayerInfo[playerid][pCash] -= 500;
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(15, 500);
			SBizInfo[15][sbProducts] --;
		}
	}
	else if(interiorid == 3)
	{   //Wheel_Arch_Angel
		PlayerInfo[playerid][pCash] -= 500;
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(16, 500);
			SBizInfo[16][sbProducts] --;
		}
	}
}


stock prop_OnVehicleRespray(playerid)
{
	if(PlayerInfo[playerid][pInt] == 1)
	{   //TransFender   //14 //16 //18
		PlayerInfo[playerid][pCash] -= 150;
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(14, 150);
			SBizInfo[14][sbProducts] --;
		}
	}
	else if(PlayerInfo[playerid][pInt] == 2)
	{   //LocoLowCo
		PlayerInfo[playerid][pCash] -= 150;
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(15, 150);
			SBizInfo[15][sbProducts] --;
		}
	}
	else if(PlayerInfo[playerid][pInt] == 3)
	{   //Wheel_Arch_Angel
		PlayerInfo[playerid][pCash] -= 150;
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(16, 150);
			SBizInfo[16][sbProducts] --;
		}
	}
}

stock GetBizLocation(playerid)//вызывается по командам /tazer /arrest
{
	new location = 100;
	/*if(	PlayerInfo[playerid][pLocal] >= 100 &&
		PlayerInfo[playerid][pLocal] < 100+MAX_BIZ)
	{
		location = PlayerInfo[playerid][pLocal];
	}*/
	location = PlayerInfo[playerid][pVirtual];
	return location;
}
stock GetBizLevel(bizid)
{   //вызывается из SaveBizSQL
	new level, score;
	if(bizid >= 100)
	{
		new sbiz = bizid-100;
		score = SBizInfo[sbiz][sbExport] - SBizInfo[sbiz][sbImport];
		level = SBizInfo[sbiz][sbLevel];
		if(SBizInfo[sbiz][sbOwned] == 0 && level > 1)
		{
			level --;
			return level;
		}
	}
	else
	{
		new biz = bizid;
 		score = BizInfo[biz][bExport] - BizInfo[biz][bImport];
		level = BizInfo[biz][bLevel];
		if(BizInfo[biz][bOwned] == 0 && level > 1 && biz != 80 && biz != 81)
		{
			level --;
			return level;
		}
	}
	new nxtlevel = level+1;
	new expamount = nxtlevel*levelexp*10000;
//2*4*10000 = 80000
//6*4*10000 = 240000
//10*4*10000 = 400000
//20*4*10000 = 800000
//30*4*10000 = 1200000
//40*4*10000 = 1600000
//97*4*10000 = 3890315

//до следующего уровня
//(level+1)*levelexp*10000 = (5+1)*4*10000 = 240000
//(SBizInfo[sbiz][sbExport] - SBizInfo[sbiz][sbImport]) > 240000
	if(score > 0)
	{
		if(score >= expamount && level < 80)
		{//156516 >= 240000
	  		level ++;
	//printf("bizid: %d; if(score: %d >= expamount: %d) { level: %d = nxtlevel: %d; }", bizid, score, expamount, level, nxtlevel);
		}
	}
	else
	{
		if(level > 1) level --;
		else level = 1;
	}
	return level;
}

stock GetCargoType(vehicleid, trailerid)
{//согласно грузовиа или прицепа возвращает тип отрасли (TypeBranch)
	if(vehicleid == 0) { return 0; }
	new modelid = VehInfo[vehicleid][cModel];//GetVehicleModel(vehicleid);
	new trailermodelid = VehInfo[trailerid][cModel];//GetVehicleModel(trailerid);
//сырьё
	if(modelid == 455 || trailermodelid == 591) return Amusements;//1. Металл - основа для производства товаров индустрии развлечений
	else if(modelid == 456 || trailermodelid == 435) return Trade;//2. Текстиль - основа для производства товаров розничной торговли
	else if(modelid == 423 || modelid == 588 || trailermodelid == 606 || trailermodelid == 607) return Restaurant;//3. Продовольствие - основа для производства товаров ресторанного бизнеса
	else if(modelid == 478 || trailermodelid == 450) return Service;//4.CreateActor  - основа для производства товаров сферы услуг
	else if(modelid == 524 || trailermodelid == 584) return Industry;//5. Нефть - основа для производства товара промышленной сферы
//товар
	else if(modelid == 404 || modelid == 413 || modelid == 414 || modelid == 418 ||
			modelid == 440 || modelid == 458 || modelid == 459 || modelid == 479 ||
			modelid == 482 || modelid == 498 || modelid == 499 || modelid == 508 ||
			modelid == 609) return Station_Wagons;//9. Товар - основа для экспорта любой сферы
	return 0;
}

stock GetTruckType(type)
{//согласно тип отрасли возвращает модель грузовика
	new modelid;
	if(type == Amusements) modelid = 455 ;//"Metal";//"Метал";
	else if(type == Trade) modelid = 456;//"Textiles";//"Текстиль";
	else if(type == Restaurant) modelid = 423;//"Provisions";//"Продовольствие";
	else if(type == Service) modelid = 478;//"Tree";//"Дерево";
	else if(type == Industry) modelid = 524;//"Oil";//"Нефть";
	else modelid = 413;//"Goods";//"Товар";
	return modelid;
}

stock GetMarketValue(type)
{//рычночная стоимость
	new market_value;
	if(type == Amusements) market_value = 138;//"Metal";//"Метал";
	else if(type == Trade) market_value = 218;//"Textiles";//"Текстиль";
	else if(type == Restaurant) market_value = 202;//"Provisions";//"Продовольствие";
	else if(type == Service) market_value = 228;//"Tree";//"Дерево";
	else if(type == Industry) market_value = 1;//"Oil";//"Нефть";
	else market_value = 204;//"Goods";//"Товар";
	return market_value;
}

stock TypeCargo(type)
{
	new strtmp[20];
	if(type == Amusements) strtmp = "Метал";//"Metal";//"Метал";
	else if(type == Trade)  strtmp = "Текстиль";//"Textiles";//"Текстиль";
	else if(type == Restaurant)  strtmp = "Продовольствие";//"Provisions";//"Продовольствие";
	else if(type == Service)  strtmp = "Дерево";//"Tree";//"Дерево";
	else if(type == Industry)  strtmp = "Нефть";//"Oil";//"Нефть";
	else strtmp = "Товар";//"Goods";//"Товар";
	return strtmp;
}
stock TypeBranch(type)
{//ф-ия возврата названия сферы
	new strtmp[24];
	if(type == Amusements) strtmp = "Индустрии развлечений";//"Метал";
	else if(type == Trade)  strtmp = "Розничной торговли";//"Текстиль";
	else if(type == Restaurant)  strtmp = "Ресторанного бизнеса";//"Продовольствие";
	else if(type == Service)  strtmp = "Сферы услуг";//"Дерево";
	else if(type == Industry)  strtmp = "Промышленной сферы";//"Нефть";
	else strtmp = "Складcкого хранения";//"Товар";
	return strtmp;
}
stock GetProducts(bizid)//TypeProds(bizid)
{//ф-ия возврата кол-во продуктов в бизе
	new prods;
	new type = BizInfo[bizid][bBranch];
	if(bizid >= 100) prods = BizInfo[bizid-100][bProducts];
	else
	{
		if(type == Amusements) prods = BizInfo[bizid][bMetal];
		else if(type == Trade) prods = BizInfo[bizid][bTextiles];
		else if(type == Restaurant) prods = BizInfo[bizid][bProvisions];
		else if(type == Service) prods = BizInfo[bizid][bTree];
		else if(type == Industry) prods = BizInfo[bizid][bFuel];
		else prods = BizInfo[bizid][bProducts];
	}
	return prods;
}
/*stock GetProducts(biz, branch)
{//81, Amusements //возвращает кол-во сырья или продуктов в бизнессе согласно
	if(biz >= 100)
	{
	    new sbiz = biz - 100;
	    if(branch == Amusements)//1. Металл
	    {
			return SBizInfo[sbiz][sbProducts];
	    }
	    else if(branch == Trade)//2. Текстиль
	    {
			return SBizInfo[sbiz][sbProducts];
	    }
	    else if(branch == Restaurant)//3. Продовольствие
	    {
			return SBizInfo[sbiz][sbProducts];
	    }
	    else if(branch == Service)//4. Древесина
	    {
			return SBizInfo[sbiz][sbProducts];
	    }
	    else if(branch == Industry)//5. Нефть
	    {
			return SBizInfo[sbiz][sbProducts];
	    }
	    else//6. Товар
	    {
			return SBizInfo[sbiz][sbProducts];
	    }
	    return SBizInfo[biz-100][sbProducts];
	}
	else
	{
	    if(branch == Amusements)//1. Металл
	    {
			return BizInfo[biz][bMetal];
	    }
	    else if(branch == Trade)//2. Текстиль
	    {
			return BizInfo[biz][bTextiles];
	    }
	    else if(branch == Restaurant)//3. Продовольствие
	    {
			return BizInfo[biz][bProvisions];
	    }
	    else if(branch == Service)//4. Древесина
	    {
			return BizInfo[biz][bTree];
	    }
	    else if(branch == Industry)//5. Нефть
	    {
			return BizInfo[biz][bFuel];
	    }
	    else//6. Товар
	    {
			return BizInfo[biz][bProducts];
	    }
	}
    //return 0;
}*/

stock UpdateStoreHouse() // Обновление склада
{	new strtmp[362];//300 + 5*4 + 2+10 + 10+10+10 = 362
	format(strtmp, sizeof(strtmp), "[ Склад ]\n\
\n{FF6600}Металл: {FFFFFF}%d\
\n{FF6600}Текстиль: {FFFFFF}%d\
\n{FF6600}Продовольствие: {FFFFFF}%d\
\n{FF6600}Древесина: {FFFFFF}%d\
\n{FF6600}Топливо: {FFFFFF}%d\
\n{FF6600}Товаров: {FFFFFF}%d\
\n{FF6600}Рабочих: {FFFFFF}%d\
\n{FF6600}Оплата: {33AA33}$%d\
\n{FF6600}В Кассе: {33AA33}$%d",
		BizInfo[80][bMetal],BizInfo[80][bTextiles],BizInfo[80][bProvisions],BizInfo[80][bTree],BizInfo[80][bFuel],
		BizInfo[80][bProducts],
		BizInfo[80][bWorker],	BizInfo[80][bSalary],
		//BizInfo[80][bImport],	BizInfo[80][bExport],
		//BizInfo[80][bExport]-BizInfo[80][bImport]
		BizInfo[80][bTill]);
	Update3DTextLabelEx(StoreHouseInfo, 0xEEEE88FF, strtmp);
	//SaveBiz(80);
}

stock UpdateOceanDock() // Обновление порта
{
    new strtmp[362];//300 + 5*4 + 2+10 + 10+10+10 = 362
    format(strtmp, sizeof(strtmp), "[ Склад ]\n\
\n{FF6600}Металл: {FFFFFF}%d\
\n{FF6600}Текстиль: {FFFFFF}%d\
\n{FF6600}Продовольствие: {FFFFFF}%d\
\n{FF6600}Древесина: {FFFFFF}%d\
\n{FF6600}Топливо: {FFFFFF}%d\
\n{FF6600}Товаров: {FFFFFF}%d\
\n{FF6600}Рабочих: {FFFFFF}%d\
\n{FF6600}Оплата: {33AA33}$%d\
\n{FF6600}В Кассе: {33AA33}$%d",
		BizInfo[81][bMetal],BizInfo[81][bTextiles],BizInfo[81][bProvisions],BizInfo[81][bTree],BizInfo[81][bFuel],
		BizInfo[81][bProducts],
		BizInfo[81][bWorker], BizInfo[81][bSalary],
		//BizInfo[81][bImport],	BizInfo[81][bExport],
		//BizInfo[81][bExport]-BizInfo[81][bImport]
		BizInfo[81][bTill]);
	Update3DTextLabelEx(OceanDockInfo, 0xEEEE88FF, strtmp);
	//SaveBiz(81);
}

stock OnSaveDateProp(playerid, house)//вызывается по команде /buy /exit
{   //для учета посещения недвижимости, чтобы отобрать её при долгом отсутствии
	/*for(new h = 0; h < MAX_HOUSE; h++)
	{   //сканируем все дома
		if( strcmp(PlayerName(playerid), HouseInfo[h][hOwner], true) ) continue;
		new curdate = getdate();//Получает текущий день в году
		HouseInfo[h][hDate] = curdate;//записать день захода в дом(на сервер)
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "ГОРНИЧНАЯ: До свидания %s. Не забывайте посещать нас. (curdate=%d)", PlayerName(playerid), curdate);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
		SaveHouse(h);
		break;
	}*/
	new curdate = getdate();//Получает текущий день в году
	HouseInfo[house][hDate] = curdate;//записать день захода в дом(на сервер)
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "ГОРНИЧНАЯ: До свидания %s. Не забывайте посещать нас. (curdate=%d)", PlayerName(playerid), curdate);
	SendClientMessage(playerid, COLOR_YELLOW, strings);
#if defined vw_sql//#endif
	SaveHouseSQL(house);
#endif
}


stock CallCar(playerid)
{
	if(PlayerInfo[playerid][pJailed] > 0 || PlayerInfo[playerid][pInt] != 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вам пока запрещена данная команда !");
		return 1;
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться ВНЕ транспортного средства!");
		return 1;
	}
	//проверяем последнюю тачку владельца
	if(	!LastCar[playerid] )
	{
		SendClientMessage(playerid,  COLOR_GREY, "    Вы ещё не сели ни в один Автомобиль!");
		return 1;
	}
	if(strcmp(VehInfo[LastCar[playerid]][cOwner], PlayerName(playerid), true)) //VehInfo[LastCar[playerid]][cOwned] != PlayerInfo[playerid][pSQLID]
	{
		SendClientMessage(playerid,  COLOR_GREY, "    Вызвать можно только свой Автомобиль!");
		return 1;
	}
    if(VehInfo[LastCar[playerid]][cInsur] < 1)
    {
    	SendClientMessage(playerid, COLOR_GREY, "   Этот автомобиль не застрахован !");
    	return 1;
    }
    if(IsPlayerInArea(playerid, specialzone[0]) && PlayerInfo[playerid][pMember] != DoD)
    {
    	SendClientMessage(playerid, COLOR_GREY, "   На данной территории запрещено использовать эту команду !");
    	return 1;
    }

 	new index;
	for(new limit = 0; limit < 5; limit++)
	{
		if(MyHouse[playerid][limit] == NOT_KEY) continue;
		index ++;
	}
	if(!index)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Команда доступна только при наличии собственного дома !");
		return 1;
	}

	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if( !IsPlayerInAnyVehicle(i) ) continue; //пропускаем всех кто не в машине
		if( IsPlayerInVehicle(i, LastCar[playerid]) )
		{//если игрок в вашейвызываемой машине
			SendClientMessage(playerid,  COLOR_GREY, "    Вы не можете вызвать ТС, пока в нём находятся люди!");
			return 1;
		}
       	if(!IsPlayerInVehicle(i, LastCar[playerid])) continue;
		RemovePlayerFromVehicleEx(i);
    }

	GetVehicleHealth(LastCar[playerid], VehInfo[LastCar[playerid]][cHealth]);
    if(VehInfo[LastCar[playerid]][cHealth] <= 250)
    {
    	SendClientMessage(playerid,  COLOR_GREY, "   Транспортное средство повреждено и не подлежит возврату!");
    	return 1;
    }
	new Float:plocx,Float:plocy,Float:plocz;
	GetPlayerPos(playerid, plocx, plocy, plocz);
	SetVehiclePosEx(LastCar[playerid],plocx,plocy+4, plocz);

	LoadCarUpgrade(LastCar[playerid]);
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "Страховая компания: Автомобиль доставлен с %.1f %%\%% здоровья.", VehInfo[LastCar[playerid]][cHealth]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	VehInfo[LastCar[playerid]][cInsur] -= 1;
	format(strings, sizeof(strings), "* Оставшееся кол-во страховок: %d.", VehInfo[LastCar[playerid]][cInsur]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	return 1;
}
