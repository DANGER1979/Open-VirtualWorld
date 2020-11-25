
//##############################################################################//
//                                                                              //
//                             СИСТЕМА ПОКУПКИ АВТО                             //
//                                                                              //
//##############################################################################//



//для покупки авто на паркинге у скупщиков
stock BuyVehicleOnParking(playerid, vehicleid)//для продажи авто
{   //вызывается из newstate == PLAYER_STATE_DRIVER
	//if(VehInfo[vehicleid][cPark] <= 1) return 1;
	CarPrice[playerid] = 0;//для автодилеров
	if(VehInfo[vehicleid][cType] < 1000) { RemovePlayerFromVehicleEx(playerid); return 1; }
	new sb;
	for(new j = 0; j < sizeof(Parking); j++)
	{
		if(IsPlayerInArea(playerid, Parking[j]))
		{
			sb = PARKING+j;
			break;
		}
	}
	if(sb < PARKING || sb >= PARKING+sizeof(Parking))
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в паркинге Emerald Isle в Las Venturas (USE: /gps 1024)!");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	if(PlayerInfo[playerid][pJob] == AUTOBUYER)//для скупщиков
	{   //выйти из ф-ии чтобы не выкидывало владельца парковки с этой тачки
		if(PlayerInfo[playerid][pSQLID] == SBizInfo[sb][sbOwned]//!strcmp(PlayerName(playerid), SBizInfo[sb][sbOwner], true)
		&& sb == VehInfo[vehicleid][cPark]) return 1;
	}
	//-------------------------------------------------------------------------*
	if(sb != VehInfo[vehicleid][cPark])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Этот транспорт не принадлежит этой парковке !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	if(SBizInfo[sb][sbLock] != 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Этот скупщик закрыл автостоянку !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	new money = floatround( VehicleArray[nCarModel[playerid]-400][Virtual_Price]*SBizInfo[sb][sbSellProd]/100.0);//30% стоимости тачки
	//new damage = floatround( VehHealth[vehicleid]*100.0/1000.0 );//% состояния
	//new money = floatround(price*damage/100);// 1%
	if(PlayerInfo[playerid][pBank] < money && GetPlayerMoneyH(playerid) < money)
	{
	    //SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе оплатить это !");
	    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
	    RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	CarPrice[playerid] = money;
	SetPVarInt(playerid, "BizID", sb);

	TogglePlayerControllableEx(playerid, 0);//обездвиживает игрок не может двигаться
	new msgitem[458];//290 + 32+10+10+28+28 + 60 = 458
	format(msgitem, sizeof(msgitem), "{0080FF}* Вы можете Купить этот {FFFFFF}%s \n{0080FF}Стоимостью: {33AA33}$%d.\
\n{0080FF}Стоимость в Автосалоне: {33AA33}$%d.\n{0080FF}Страховок: {FFFFFF}%d.\
\n{0080FF}Дата производства: {FFFFFF}%s. \n{0080FF}Дата утилизации: {FFFFFF}%s.\
\n\n{AFAFAF}Нажмите Accept, чтобы принять.", VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid],
		VehicleArray[nCarModel[playerid]-400][Virtual_Price], VehInfo[vehicleid][cInsur],
		getDate(VehInfo[vehicleid][cDate]), getDate(getdate()+15));
	strcat(msgitem, "\n{AFAFAF}_________________________________________________");
	new strtmp[37+24];
	format(strtmp, sizeof(strtmp), "Продажа Транспортных Средств от %s's", SBizInfo[sb][sbOwner]);
	MenuOperation[playerid] = 27;
	ShowPlayerDialogGap(playerid, BUYVEHICLE_DIALOG, DIALOG_STYLE_MSGBOX, strtmp, msgitem, "Accept", "Cancel");
	return 1;
}
stock BuyVehicle27_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{   //dialogid  - диалог на который выйдем
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BUYVEHICLE_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(MenuOperation[playerid] != 27) return 1;
	if(!gLoading[playerid] && !gUnLoading[playerid])
	{
		TogglePlayerControllableEx(playerid, 1);//размораживает
	}
	new msgitem[256+1];
	if(!response)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();

		//TogglePlayerControllableEx(playerid, 1);//освобождает игрока может двигаться
		RemovePlayerFromVehicleEx(playerid);
		//removePlayerFromVehicle(playerid);

		Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;

		format(msgitem, sizeof(msgitem), "%s отказался от покупки транспорта !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

		MenuOperation[playerid] = 0;
		return 1;
	}

//для продажи авто //для покупки авто на паркинге
	if(CurState[playerid] != PLAYER_STATE_DRIVER)
	{
		RemovePlayerFromVehicleEx(playerid);
		//VehInfo[nCarID[playerid]][cPark] = 0;//???
		//VehInfo[nCarID[playerid]][cDate] = getdate();
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться на водительском сидении!");
		return 1;
	}
	//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку
	nCarID[playerid] = GetPlayerVehicleID(playerid);
	nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);
	new vehicleid = nCarID[playerid];
	if(VehInfo[vehicleid][cType] < 1000) { RemovePlayerFromVehicleEx(playerid); return 1; }
	new sb = GetPVarInt(playerid, "BizID");
	if(sb < PARKING || sb >= PARKING+sizeof(Parking))
	{
		//VehInfo[nCarID[playerid]][cPark] = 0;
		//VehInfo[nCarID[playerid]][cDate] = getdate();
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;

	    SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в паркинге Emerald Isle в Las Venturas (USE: /gps 1024)!");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	//-------------------------------------------------------------------------*
	if(sb != VehInfo[vehicleid][cPark])
	{
		//VehInfo[nCarID[playerid]][cPark] = 0;
		//VehInfo[nCarID[playerid]][cDate] = getdate();
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;

		SendClientMessage(playerid, COLOR_GREY, "   Этот транспорт не принадлежит этой парковке !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	if(SBizInfo[sb][sbLock] != 0)
	{
		//VehInfo[nCarID[playerid]][cPark] = 0;
		//VehInfo[nCarID[playerid]][cDate] = getdate();
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREY, "   Этот скупщик закрыл автостоянку !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	new money = VehicleArray[nCarModel[playerid]-400][Virtual_Price]*SBizInfo[sb][sbSellProd]/100;//30% стоимости тачки
	CarPrice[playerid] = money;
	if(	VehInfo[nCarID[playerid]][cOwned] > 0 &&
		//VehInfo[nCarID[playerid]][cOwned] != PlayerInfo[playerid][pSQLID] &&
	 	strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true) &&
	    //если это машина чья-то, т.е. не твоя
		MyCar[playerid][0] != 0 && //а у тебя все слоты машин заняты
		MyCar[playerid][1] != 0 &&
		MyCar[playerid][2] != 0)
	{
		//VehInfo[nCarID[playerid]][cPark] = 0;
		//VehInfo[nCarID[playerid]][cDate] = getdate();
		Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;

		SendClientMessage(playerid, COLOR_GREY, "   Вы уже имеете максимальное кол-во транспортных средств !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
	{
		GivePlayerMoneyB(fsbiz+sb, playerid, -CarPrice[playerid]);
	}
	else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
	{
		GivePlayerMoneyH(fsbiz+sb, playerid, -CarPrice[playerid]);
	}
	else
	{
		//VehInfo[nCarID[playerid]][cPark] = 0;
		//VehInfo[nCarID[playerid]][cDate] = getdate();
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
	    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
	    RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(	VehInfo[nCarID[playerid]][cOwned] > 0 &&
			VehInfo[nCarID[playerid]][cOwned] == PlayerInfo[i][pSQLID]
			//!strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true)
			)
		{   //находим владельца этой тачки с ИД == i
			if(nCarID[playerid] == MyCar[i][0]) MyCar[i][0] = 0;//освобождаем у него переменную
			else if(nCarID[playerid] == MyCar[i][1]) MyCar[i][1] = 0;
			else if(nCarID[playerid] == MyCar[i][2]) MyCar[i][2] = 0;
			break;
		}
	}
	SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbProducts] --;
	SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbTill] += CarPrice[playerid];
	SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbExport] += CarPrice[playerid];

	if(	nCarID[playerid] != MyCar[playerid][0] &&
		nCarID[playerid] != MyCar[playerid][1] &&
		nCarID[playerid] != MyCar[playerid][2])
	{   //если это не ваша тачка
		VehInfo[nCarID[playerid]][cOwned] = PlayerInfo[playerid][pSQLID];
		strmid(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		if(MyCar[playerid][0] == 0) MyCar[playerid][0] = nCarID[playerid];
		else if(MyCar[playerid][1] == 0) MyCar[playerid][1] = nCarID[playerid];
		else if(MyCar[playerid][2] == 0) MyCar[playerid][2] = nCarID[playerid];

		new numberplate[MAX_PLAYER_NAME+10];
		format(numberplate, sizeof(numberplate), "%s [ %d ]", VehInfo[nCarID[playerid]][cOwner], nCarID[playerid]);
		Update3DTextLabelEx(number3D[nCarID[playerid]], 0x009DFFFF, numberplate);
	}
	LockCar(nCarID[playerid]);//GetPlayerVehicleID(playerid)
	format(msgitem, sizeof(msgitem), "* Вы купили Автомобиль {FFFFFF}%s's{0080FF} по цене {33AA33}$%d", SBizInfo[ VehInfo[nCarID[playerid]][cPark] ][sbOwner], CarPrice[playerid]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	Offer[playerid] = ReturnUser(SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbOwner]);
    if( IsPlayerConnectedEx(Offer[playerid]) )
	{
		format(msgitem, sizeof(msgitem), "%s's{0080FF} купил у Вас Автомобиль по цене {33AA33}$%d{0080FF}. Сумма перечислена на счёт вашей компании.", PlayerName(playerid),CarPrice[playerid]);
		SendClientMessage(Offer[playerid], COLOR_WHITE, msgitem);
	}
	VehInfo[nCarID[playerid]][cPark] = 0;
	VehInfo[nCarID[playerid]][cDate] = getdate();
	Offer[playerid] = MAX_PLAYERS-1;
	CarPrice[playerid] = 0;
	MenuOperation[playerid] = 0;
	//TogglePlayerControllableEx(playerid, 1);//освобождает игрока может двигаться
	return 1;
}

//==============================================================================

//для покупки авто
stock BuyVehicle_STATE_DRIVER(playerid, vehicleid)//для продажи авто
{   //вызывается из newstate == PLAYER_STATE_DRIVER
	if(VehInfo[vehicleid][cPark] < 100) return 1;
	CarPrice[playerid] = 0;//для автодилеров
	if(VehInfo[vehicleid][cType] < 1000) { RemovePlayerFromVehicleEx(playerid); return 1; }
	//-------------------------------------------------------------------------*
	//new price = VehicleArray[nCarModel[playerid]-400][Virtual_Price];
	//new damage = floatround( VehHealth[vehicleid]*100.0/1000.0 );//% состояния
	//new money = floatround(price*damage/100);// 1%
	CarPrice[playerid] = VehInfo[vehicleid][cPark];//money;
	TogglePlayerControllableEx(playerid, 0);//обездвиживает игрок не может двигаться
	new msgitem[460+1];//290 + 32+10+10+28+28 + 60 = 458
	if(	CarPrice[playerid] >= 100 && CarPrice[playerid] < 1000)
	{
		format(msgitem, sizeof(msgitem), "{0080FF}* Вы можете Арендовать этот {FFFFFF}%s\n{0080FF}Стоимостью: {33AA33}$%d.\
	\n{0080FF}Стоимость в Автосалоне: {33AA33}$%d.\n{0080FF}Страховок: {FFFFFF}%d.\
	\n{0080FF}Дата производства: {FFFFFF}%s.\n{0080FF}Дата утилизации: {FFFFFF}%s.\
	\n\n{AFAFAF}Нажмите Accept, чтобы принять.", VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid],
			VehicleArray[nCarModel[playerid]-400][Virtual_Price], VehInfo[vehicleid][cInsur],
			getDate(VehInfo[vehicleid][cDate]), getDate(getdate()+15));
		MenuOperation[playerid] = 28;
	}
	else if(CarPrice[playerid] >= 1000)
	{
		format(msgitem, sizeof(msgitem), "{0080FF}* Вы можете Купить этот {FFFFFF}%s\n{0080FF}Стоимостью: {33AA33}$%d.\
	\n{0080FF}Стоимость в Автосалоне: {33AA33}$%d.\n{0080FF}Страховок: {FFFFFF}%d.\
	\n{0080FF}Дата производства: {FFFFFF}%s.\n{0080FF}Дата утилизации: {FFFFFF}%s.\
	\n\n{AFAFAF}Нажмите Accept, чтобы принять.", VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid],
			VehicleArray[nCarModel[playerid]-400][Virtual_Price], VehInfo[vehicleid][cInsur],
			getDate(VehInfo[vehicleid][cDate]), getDate(getdate()+15));
		MenuOperation[playerid] = 29;
	}
	strcat(msgitem, "\n{AFAFAF}_________________________________________________");
	new strtmp[17+24+3];
	format(strtmp, sizeof(strtmp), "Продавец: %s[%d]", VehInfo[vehicleid][cOwner], MenuOperation[playerid]);
	ShowPlayerDialogGap(playerid, BUYVEHICLE_DIALOG, DIALOG_STYLE_MSGBOX, strtmp, msgitem, "Accept", "Cancel");
	return 1;
}
stock BuyVehicle28_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{   //dialogid  - диалог на который выйдем
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BUYVEHICLE_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(MenuOperation[playerid] != 28 && MenuOperation[playerid] != 29) return 1;
	if(!gLoading[playerid] && !gUnLoading[playerid])
	{
		TogglePlayerControllableEx(playerid, 1);//размораживает
	}
	new msgitem[256+1];
	if(!response)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();

		//TogglePlayerControllableEx(playerid, 1);//освобождает игрока может двигаться
		RemovePlayerFromVehicleEx(playerid);
		//removePlayerFromVehicle(playerid);

		Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;

		format(msgitem, sizeof(msgitem), "%s отказался от аренды/покупки транспорта !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		return 1;
	}

//для продажи авто //для покупки авто на паркинге
	if(CurState[playerid] != PLAYER_STATE_DRIVER)
	{
		RemovePlayerFromVehicleEx(playerid);
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться на водительском сидении!");
		return 1;
	}
	//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку
	nCarID[playerid] = GetPlayerVehicleID(playerid);
	nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);
	new vehicleid = nCarID[playerid];
	if(VehInfo[vehicleid][cType] < 1000) { RemovePlayerFromVehicleEx(playerid); return 1; }
	if(	MenuOperation[playerid] == 29 &&
		VehInfo[nCarID[playerid]][cOwned] > 0 &&
		//VehInfo[nCarID[playerid]][cOwned] != PlayerInfo[playerid][pSQLID] &&
	 	strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true) &&
	    //если это машина чья-то, т.е. не твоя
		MyCar[playerid][0] != 0 && //а у тебя все слоты машин заняты
		MyCar[playerid][1] != 0 &&
		MyCar[playerid][2] != 0)
	{
		Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;

		SendClientMessage(playerid, COLOR_GREY, "   Вы уже имеете максимальное кол-во транспортных средств !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
	{
		GivePlayerMoneyB(fredraft, playerid, -CarPrice[playerid]);
	}
	else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
	{
		GivePlayerMoneyH(fredraft, playerid, -CarPrice[playerid]);
	}
	else
	{
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
	    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
	    RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	Offer[playerid] = ReturnUser(VehInfo[nCarID[playerid]][cOwner]);
	if(MenuOperation[playerid] == 28)
	{
		format(msgitem, sizeof(msgitem), "* Вы арендовали Автомобиль {FFFFFF}%s's{0080FF} по цене {33AA33}$%d", VehInfo[nCarID[playerid]][cOwner], CarPrice[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);

	    if( !IsPlayerConnectedEx(Offer[playerid]) )
		{
	    	new ToBase[52+10+24];
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET Bank=Bank+%d WHERE `Name`='%s'",
				CarPrice[playerid], VehInfo[nCarID[playerid]][cOwner]);
			mysql_query(ToBase);
		}
		else
		{
			GivePlayerMoneyB(fredraft, Offer[playerid], CarPrice[playerid]);
			format(msgitem, sizeof(msgitem), "%s{0080FF} арендовал у Вас Автомобиль по цене {33AA33}$%d{0080FF}. Сумма перечислена на ваш счёт в банке.",
				PlayerName(playerid), CarPrice[playerid]);
			SendClientMessage(Offer[playerid], COLOR_WHITE, msgitem);
		}
	}
	else if(MenuOperation[playerid] == 29)
	{
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(	VehInfo[nCarID[playerid]][cOwned] > 0 &&
				VehInfo[nCarID[playerid]][cOwned] == PlayerInfo[i][pSQLID]
				//!strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true)
				)
			{   //находим владельца этой тачки с ИД == i
				if(nCarID[playerid] == MyCar[i][0]) MyCar[i][0] = 0;//освобождаем у него переменную
				else if(nCarID[playerid] == MyCar[i][1]) MyCar[i][1] = 0;
				else if(nCarID[playerid] == MyCar[i][2]) MyCar[i][2] = 0;
				break;
			}
		}
		//LockCar(nCarID[playerid]);//GetPlayerVehicleID(playerid)
		format(msgitem, sizeof(msgitem), "* Вы купили Автомобиль {FFFFFF}%s's{0080FF} по цене {33AA33}$%d", VehInfo[nCarID[playerid]][cOwner], CarPrice[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);

	    if( !IsPlayerConnectedEx(Offer[playerid]) )
		{
	    	new ToBase[52+10+24];
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET Bank=Bank+%d WHERE `Name`='%s'",
				CarPrice[playerid], VehInfo[nCarID[playerid]][cOwner]);
			mysql_query(ToBase);
		}
		else
		{
			GivePlayerMoneyB(fredraft, Offer[playerid], CarPrice[playerid]);
			format(msgitem, sizeof(msgitem), "%s{0080FF} купил у Вас Автомобиль по цене {33AA33}$%d{0080FF}. Сумма перечислена на ваш счёт в банке.",
				PlayerName(playerid), CarPrice[playerid]);
			SendClientMessage(Offer[playerid], COLOR_WHITE, msgitem);
		}
		if(	nCarID[playerid] != MyCar[playerid][0] &&
			nCarID[playerid] != MyCar[playerid][1] &&
			nCarID[playerid] != MyCar[playerid][2])
		{   //если это не ваша тачка
			VehInfo[nCarID[playerid]][cOwned] = PlayerInfo[playerid][pSQLID];
			strmid(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

			if(MyCar[playerid][0] == 0) MyCar[playerid][0] = nCarID[playerid];
			else if(MyCar[playerid][1] == 0) MyCar[playerid][1] = nCarID[playerid];
			else if(MyCar[playerid][2] == 0) MyCar[playerid][2] = nCarID[playerid];

			new numberplate[MAX_PLAYER_NAME+10];
			format(numberplate, sizeof(numberplate), "%s [ %d ]", VehInfo[nCarID[playerid]][cOwner], nCarID[playerid]);
			Update3DTextLabelEx(number3D[nCarID[playerid]], 0x009DFFFF, numberplate);
		}
		Delete3DTextLabel(sale3D[nCarID[playerid]]);	Counter3DText --;
		VehInfo[nCarID[playerid]][cPark] = 0;
		VehInfo[nCarID[playerid]][cDate] = getdate();
	}
	/*SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbProducts] --;
	SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbTill] += CarPrice[playerid];
	SBizInfo[VehInfo[nCarID[playerid]][cPark]][sbExport] += CarPrice[playerid];*/

	Offer[playerid] = MAX_PLAYERS-1;
	CarPrice[playerid] = 0;
	MenuOperation[playerid] = 0;
	//TogglePlayerControllableEx(playerid, 1);//освобождает игрока может двигаться
	return 1;
}




//==============================================================================



stock AutoRedrafting(playerid, giveplayerid, money)
{//для переоформления тачки
	//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку
	nCarID[playerid] = GetPlayerVehicleID(playerid);
	nCarModel[playerid] = VehInfo[nCarID[playerid]][cModel];//GetVehicleModel(nCarID[playerid]);
	//if(GetPlayerState(giveplayerid) != PLAYER_STATE_DRIVER)
	if(GetPlayerState(giveplayerid) != PLAYER_STATE_PASSENGER)
	{
		//SendClientMessage(playerid, COLOR_GREY, "  Игрок должен находиться на водительском сидении!");
		SendClientMessage(playerid, COLOR_GREY, "  Игрок должен находиться на пассажирском сидении!");
		return 1;
	}//если заказчик в машине
	if(!IsPlayerInVehicle(playerid, nCarID[giveplayerid]))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не в Вашей машине!");
		return 1;
	}
	if(money > VehicleArray[nCarModel[playerid]-400][Virtual_Price] )
	{
    	format(strings, sizeof(strings), "   Цена не выше $%d.", VehicleArray[nCarModel[playerid]-400][Virtual_Price]);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	/*if(GetPlayerMoneyH(giveplayerid) < money)
	{
		SendClientMessage(playerid, COLOR_GREY, "   У игрока не хватает денег на руках!");
		return 1;
	}*/
	if( VehInfo[nCarID[playerid]][cOwned] != PlayerInfo[playerid][pSQLID] )
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Вы не владелец данного Транспортного Средства !");
		return 1;
	}
	if(	VehInfo[nCarID[playerid]][cOwned] > 0 &&
		strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true))
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Вы не владелец данного Транспортного Средства !");
		return 1;
	}
	if( VehInfo[nCarID[playerid]][cPark] >= PARKING )//VehInfo[vid][cPark] != 0 &&
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете предложить транспорт принадлежащий Паркингу !");
		return 1;
	}
	if( VehInfo[nCarID[playerid]][cPark] == 2)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете предложить транспорт со свалки !");
		return 1;
	}
	if( nCarModel[playerid] == 447)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете предложить этот транспорт !");
		return 1;
	}
	new strcmd[MAX_STRING];
    format(strcmd, sizeof(strcmd), "* Вы предложили переоформить свой автомобиль на %s за $%d .", PlayerName(giveplayerid), money);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
	new msgitem[90+24+32+10];
	format(msgitem, sizeof(msgitem), " * %s\n хочет переоформить автомобиль %s на Вас за $%d.\n\nНажмите Accept, чтобы принять.",
		PlayerName(playerid), VehicleArray[nCarModel[playerid]-400][Vehicle_Name],  money);
	Offer[giveplayerid] = playerid;
	CarPrice[giveplayerid] = money;
	//MenuOperation[giveplayerid] = 25;
	MenuOperation[giveplayerid] = 131;
	ShowPlayerDialogGap(giveplayerid, REDRAFT_DIALOG, DIALOG_STYLE_MSGBOX, "Переоформление Транспортных Средств",msgitem,"Accept","Cancel");
	return 1;
}

stock redraft_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != REDRAFT_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		SetPVarInt(playerid, "gShowDialog", -1);
		Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
		return 1;
	}
	new msgitem[256+1];
	if(MenuOperation[playerid] == 131)//	/redraft
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnectedEx(Offer[playerid]))
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;

		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Авто!");
		    return 1;
		}
		//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		if(GetPlayerState(playerid) != PLAYER_STATE_PASSENGER)
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;

			//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться на водительском сидении!");
			SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться на пассажирском сидении!");
			return 1;
		}
		nCarID[playerid] = GetPlayerVehicleID(playerid);
		if(VehInfo[nCarID[playerid]][cPark] != 0)
		{
		    RemovePlayerFromVehicleEx(playerid);
			RemovePlayerFromVehicleEx(Offer[playerid]);

	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
		    SendClientMessage(playerid, COLOR_GREY, "   Запаркованное транспортное средство не подлежит продаже !");
		    return 1;
		}
		if(	VehInfo[nCarID[playerid]][cOwned] > 0 &&
			//VehInfo[nCarID[playerid]][cOwned] != PlayerInfo[playerid][pSQLID] &&
		 	strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true) &&
		    //если это машина чья-то, т.е. не твоя
			MyCar[playerid][0] != 0 && //а у тебя все слоты машин заняты
			MyCar[playerid][1] != 0 &&
			MyCar[playerid][2] != 0)
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;

			SendClientMessage(playerid, COLOR_GREY, "   Вы уже имеете максимальное кол-во транспортных средств !");
			RemovePlayerFromVehicleEx(playerid);
			return 1;
		}
		//new money = floatround( VehicleArray[nCarModel[playerid]-400][Virtual_Price]*SBizInfo[sb][sbSellProd]/100.0);//30% стоимости тачки
		//CarPrice[playerid] = money;
        if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
        {
			GivePlayerMoneyB(fredraft, playerid, -CarPrice[playerid]);
		}
        else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
        {
			GivePlayerMoneyH(fredraft, playerid, -CarPrice[playerid]);
		}
		else
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;

		    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
		    RemovePlayerFromVehicleEx(playerid);
			return 1;
		}
		GivePlayerMoneyB(fredraft, Offer[playerid], CarPrice[playerid]);

		if(	VehInfo[ nCarID[Offer[playerid]] ][cOwned] > 0 &&
			VehInfo[ nCarID[Offer[playerid]] ][cOwned] == PlayerInfo[Offer[playerid]][pSQLID])
		{   //находим владельца этой тачки с ИД == i
		   if(nCarID[playerid] == MyCar[Offer[playerid]][0]) MyCar[Offer[playerid]][0] = 0;//освобождаем переменную у владельца этой тачки
		   else if(nCarID[playerid] == MyCar[Offer[playerid]][1]) MyCar[Offer[playerid]][1] = 0;
		   else if(nCarID[playerid] == MyCar[Offer[playerid]][2]) MyCar[Offer[playerid]][2] = 0;
		}
		else return 1;

		VehInfo[nCarID[playerid]][cOwned] = PlayerInfo[playerid][pSQLID];
		strmid(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		if(MyCar[playerid][0] == 0) MyCar[playerid][0] = nCarID[playerid];
		else if(MyCar[playerid][1] == 0) MyCar[playerid][1] = nCarID[playerid];
		else if(MyCar[playerid][2] == 0) MyCar[playerid][2] = nCarID[playerid];

		new numberplate[MAX_PLAYER_NAME+10];
		format(numberplate, sizeof(numberplate), "%s [ %d ]", VehInfo[nCarID[playerid]][cOwner], nCarID[playerid]);
		Update3DTextLabelEx(number3D[nCarID[playerid]], 0x009DFFFF, numberplate);

		LockCar(nCarID[playerid]);

		format(strings, sizeof(strings), "* Вы переоформили Автомобиль у %s за $%d",PlayerName(Offer[playerid]),CarPrice[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		format(strings, sizeof(strings), "* Вам %s оплатил переоформление Автомобиля стоимостью $%d",PlayerName(playerid),CarPrice[playerid]);
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, strings);

		VehInfo[nCarID[playerid]][cPark] = 0;
		VehInfo[nCarID[playerid]][cDate] = getdate();
		//TogglePlayerControllableEx(playerid, 1);//освобождает игрока может двигаться
		RemovePlayerFromVehicleEx(Offer[playerid]);
	}
	else if(MenuOperation[playerid] == 132)//	/redraft
	{
		new h = GetPVarInt(playerid, "House");
        if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
        {
			GivePlayerMoneyB(fredraft, playerid, -CarPrice[playerid]);
		}
        else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
        {
			GivePlayerMoneyH(fredraft, playerid, -CarPrice[playerid]);
		}
		else
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;

		    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
			return 1;
		}
		GivePlayerMoneyB(fredraft, Offer[playerid], CarPrice[playerid]);


		for(new limit = 0; limit < 5; limit++)
		{
			if(MyHouse[Offer[playerid]][limit] != h) continue;
			MyHouse[Offer[playerid]][limit] = NOT_KEY;
		}
		PlayerInfo[Offer[playerid]][pHouse] = NOT_KEY;//ВНИМАНИЕ нельзя т.к. домов может быть больше 1
		for(new limit = 0; limit < 5; limit++)
		{
			if(MyHouse[playerid][limit] == NOT_KEY) continue;
			MyHouse[playerid][limit] = h; break;
		}
		PlayerInfo[playerid][pHouse] = h;
		HouseInfo[h][hOwned] = PlayerInfo[playerid][pSQLID];
		HouseInfo[h][hLock] = 1;
		//HouseInfo[h][hRentabil] = 1;
		strmid(HouseInfo[h][hOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		//SBizInfo[6][sbTill] += HouseInfo[h][hBuyPrice];//перечислили деньги в биз House Upgrade
		PlayerPlayMusic(playerid);
		PlayerInfo[playerid][pLocal] = h;
		SetPlayerVirtualWorldEx(playerid, h);
		SetPlayerInteriorEx(playerid, HouseInfo[h][hInt]);
		SetPlayerPosEx(playerid, HouseInfo[h][hExitX],HouseInfo[h][hExitY],HouseInfo[h][hExitZ], 0);

		new text_info[19+20+24];
		format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", HouseInfo[h][hDiscription], HouseInfo[h][hOwner]);
		//Update3DTextLabelText(text3D[h], 0xAAAAFFFF, msgitem);
		Update3DTextLabelEx(hEntranceText3D[h], 0xAAAAFFFF, text_info);

		OnSaveDateProp(playerid, h);//записывает день покупки дома

		format(strings, sizeof(strings), "%s has sell house %d for $%d", PlayerName(Offer[playerid]), h, CarPrice[playerid]);
		Log(BUY,strings);
		format(msgitem, sizeof(msgitem), "%s has buy house %d for $%d", PlayerName(playerid), h, CarPrice[playerid]);
		Log(BUY,msgitem);
		//OnPlayerStatsUpdate(playerid);//запустить ф-ию сохранения параметров игрока

		SaveHouse(h);
		GameTextForPlayerEx(playerid, "~w~Welcome Home~n~You can exit at any time by moving to this door and typing /exit", 5000, 3);
		SendClientMessage(playerid, COLOR_WHITE, "Поздравляем с покупкой ! Введите /prop, чтобы получить справку по собственности !");
		SetPVarInt(playerid, "gGotPermit", 0);
	}
	else if(MenuOperation[playerid] == 133)//	/redraft
	{
		new b = GetPVarInt(playerid, "Bouse");
        if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
        {
			GivePlayerMoneyB(fredraft, playerid, -CarPrice[playerid]);
		}
        else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
        {
			GivePlayerMoneyH(fredraft, playerid, -CarPrice[playerid]);
		}
		else
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;

		    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
			return 1;
		}
		GivePlayerMoneyB(fredraft, Offer[playerid], CarPrice[playerid]);

	 	for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[Offer[playerid]][limit] != b) continue;
			MyBizz[Offer[playerid]][limit] = NOT_KEY;
		}
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] == NOT_KEY) continue;
			MyBizz[playerid][limit] = b; break;
		}
		BizInfo[b][bOwned] = PlayerInfo[playerid][pSQLID];
		BizInfo[b][bLock] = 0;
		//if(BizInfo[b][bProducts] < 100) BizInfo[b][bProducts] = 100;
		new curdate = getdate();//Получает текущий день в году
		BizInfo[b][bDate] = curdate;//записать день покупки
		strmid(BizInfo[b][bOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		//BizInfo[0][bProducts] += BizInfo[b][bBuyPrice];//перечислили деньги в БАНК
		SetPVarInt(playerid, "gGotPermit", 0);

		PlayerPlayMusic(playerid);

		format(strings, sizeof(strings), "%s has sell biz %d for $%d", PlayerName(Offer[playerid]), b, CarPrice[playerid]);
		Log(BUY,strings);
		format(msgitem, sizeof(msgitem), "%s has buy biz %d for $%d", PlayerName(playerid), b, CarPrice[playerid]);
		Log(BUY,msgitem);

		new text_info[19+20+24];
		format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", BizInfo[b][bDiscription], BizInfo[b][bOwner]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+b], 0xAAAAFFFF, msgitem);
		Update3DTextLabelEx(bEntranceText3D[b], 0xAAAAFFFF, text_info);

		SaveBiz(b);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "Поздравляем с новой покупкой. Введите /prop, чтобы посмотреть справку по бизнесу.");
	}
	else if(MenuOperation[playerid] == 134)//	/redraft
	{
		new sb = GetPVarInt(playerid, "SBouse");
		if(sb >= PARKING && sb < PARKING+sizeof(Parking))
		{
			if(PlayerInfo[playerid][pJob] != AUTOBUYER)//для скупщиков
			{
		        Offer[playerid] = MAX_PLAYERS-1;
				CarPrice[playerid] = 0;
				MenuOperation[playerid] = 0;

				SendClientMessage(Offer[playerid], COLOR_GREY, "   Игрок не скупщик авто, чтобы купить парковку авто!");
				SendClientMessage(playerid, COLOR_GREY, "   Вы не скупщик авто, чтобы купить парковку авто!");
				return 1;
			}
	        if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
	        {
				GivePlayerMoneyB(fredraft, playerid, -CarPrice[playerid]);
			}
	        else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
	        {
				GivePlayerMoneyH(fredraft, playerid, -CarPrice[playerid]);
			}
			else
			{
		        Offer[playerid] = MAX_PLAYERS-1;
				CarPrice[playerid] = 0;
				MenuOperation[playerid] = 0;

			    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
				return 1;
			}
			//SBizInfo[sb][sbTill] += SBizInfo[sb][sbBuyPrice];
		}
		else
		{
	        if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
	        {
				GivePlayerMoneyB(fredraft, playerid, -CarPrice[playerid]);
			}
	        else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
	        {
				GivePlayerMoneyH(fredraft, playerid, -CarPrice[playerid]);
			}
			else
			{
		        Offer[playerid] = MAX_PLAYERS-1;
				CarPrice[playerid] = 0;
				MenuOperation[playerid] = 0;

			    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет этой суммы денег !");
				return 1;
			}
			//BizInfo[0][bProducts] += SBizInfo[sb][sbBuyPrice];//перечислили деньги в БАНК
		}
		GivePlayerMoneyB(fredraft, Offer[playerid], CarPrice[playerid]);

	 	for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] == sb)
			{
				MyCompany[Offer[playerid]][limit] = NOT_KEY;
				break;
			}
		}
		for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] == NOT_KEY)
			{
				MyCompany[playerid][limit] = sb;
				break;
			}
		}

		SBizInfo[sb][sbOwned] = PlayerInfo[playerid][pSQLID];
		SBizInfo[sb][sbLock] = 0;
		//if( SBizInfo[sb][sbProducts] < 100 &&
		//	!(sb >= PARKING && sb < PARKING+sizeof(Parking)) ) SBizInfo[sb][sbProducts] = 100;
		new curdate = getdate();//Получает текущий день в году
		SBizInfo[sb][sbDate] = curdate;//записать день покупки
		strmid(SBizInfo[sb][sbOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
		SetPVarInt(playerid, "gGotPermit", 0);

		//OnSaveDateSBizz(playerid);//записывает день покупки биза

		format(strings, sizeof(strings), "%s has sell sbiz %d for $%d", PlayerName(Offer[playerid]), sb+100, CarPrice[playerid]);
		Log(BUY,strings);
		format(msgitem, sizeof(msgitem), "%s has buy sbiz %d for $%d", PlayerName(playerid), sb+100, CarPrice[playerid]);
		Log(BUY,msgitem);

		new text_info[19+20+24];
		format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", SBizInfo[sb][sbDiscription], SBizInfo[sb][sbOwner]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+sb], 0xAAAAFFFF, msgitem);
		Update3DTextLabelEx(sbEntranceText3D[sb], 0xAAAAFFFF, text_info);

		SaveSBiz(sb);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "Поздравляем с новой покупкой. Введите /prop, чтобы посмотреть справку по бизнесу.");
	}
	Offer[playerid] = MAX_PLAYERS-1;
	CarPrice[playerid] = 0;
	MenuOperation[playerid] = 0;
	return 1;
}

