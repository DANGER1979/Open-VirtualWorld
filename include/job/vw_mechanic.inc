
stock mechanic_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused oldstate
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	//----------------------------------------------------------------------
	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ АВТОМЕХАНИКУ
	if(modelid == 525)//для автомехаников STEP1
	{   //если вы сели в эвакуатор  || modelid == 539 //Vortex (на воздушной подушке)
		if(PlayerInfo[playerid][pJob] == CARMECHANIC)// && gJobDuty[playerid] == 1
		{   //если Вы автомеханик на дежурстве
            if( !IsTrailerAttachedToVehicle(nCarID[playerid]) )
   			{   //если к данному эвакуатору ни чего не присоеденено
				SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Подцепи брошеную тачку и доставь ее на свалку (USE: /gps 1031).");
				GameTextForPlayerEx(playerid, " Press ~b~~k~~VEHICLE_TURRETUP~ ~n~~g~|~w~Vehicle Join~g~|", 1000, 1);
			}
   		}
		else if( IsPermitToRider(playerid) ) {	}
		else
		{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   Вы - не АвтоМеханик или Вы не на дежурстве. Пожалуйста, переоденьтесь!");
			//return 1;
		}//
	}//для автомехаников конец
	return 1;
}

stock mechanic_OnPlayerExitVehicle(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] != CARMECHANIC) return 1;
	if(!gJobDuty[playerid]) return 1;
	new modelid = GetVehicleModel(vehicleid);
	if(modelid == 525)
	{   //если вы вышли из эвакуатора
		if(CP[playerid] == CP_CARMECHANIC)//если предыдущее задание выполнено
		{   // чтобы нельзя было несколько раз взять задание
			DisablePlayerCheckpointEx(playerid);//убрать чекпоинт
	        //SendClientMessage(playerid, COLOR_ORANGE, "* Вы теперь Не на Дежурстве вашей АвтоРемонтной Службы и не получаете вызовы больше.");
	        //gJobDuty[playerid] = 0;
	        //MechanicsCounter -= 1;
	    }
	}
	return 1;
}


stock mechanic_OnPlayerPickUp(playerid, pickupid)
{
	if(IsPlayerInRangeOfPoint(playerid, 1.9, -105.2947,-1264.2655,3.1635))//Механы
	{
		CrashDetected[playerid] = 101;
		if(gParameter2[playerid] == 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "    В отчаянии Вы не можете получить задание, сесть в авто или выйти на дежурство !");
			SendClientMessage(playerid, COLOR_GREY, "    Вам необходимо развлечься: посетите клубы и потанцуйте !");
			return 1;
		}
		if(gRealWar)
		{
			SendClientMessage(playerid, COLOR_GREY, "    Активизирован режим игры RealWar ! Вы не можете выйти на дежурство!");
			return 1;
		}
		if(gOnDuty[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выйти на работу когда вышли на дежурство.");
			return 1;
		}
		if(PlayerInfo[playerid][pJob] == CARMECHANIC && !GetPVarInt(playerid, "gInRacing"))//для автомехаников
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		    if(gJobDuty[playerid] == 1)
		    {
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве вашей АвтоРемонтной Службы и не получаете вызовы больше.");
		        gJobDuty[playerid] = 0;
		        MechanicsCounter -= 1;
  				//DeletePVar(playerid, "dutylist");
  				strdel(dutylist[playerid], 0, sizeof(dutylist));
  				if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		    }
		    else
		    {
		        //SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь на Дежурстве вашей АвтоРемонтной Службы и получаете вызовы от нуждающихся людей.");
		        gJobDuty[playerid] = 1;
		        MechanicsCounter += 1;
   				format(strings, sizeof(strings), "Mеханик {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
   				//JobNews(COLOR_ORANGE,strings);
   				SendClientMessage(playerid, COLOR_ORANGE, strings);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {FFCC00}%s\n", lH,lM,lS, strings);
				//SetPVarString(playerid, "dutylist", strings);
				format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FFCC00}%s\n", lH,lM,lS, strings);
  				if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, 50);
		    }
		}
		//return 1;
	}
}

stock mechanic_VehicleEnterPickUp(playerid)
{

	if( IsPlayerInRangeOfPoint(playerid, 10.0, -126.7453,-1264.7269,3.7841) )//[ Утилизация Авто ]
	{//для автомехаников в мастерской
		//----------------------------------------------------------------------
		//ФУНКЦИЯ ЗАВЕРШЕНИЯ ЗАДАНИЯ АВТОМЕХАНИКОМ
//Бизнес получает сырьё и расплачивается деньгами с механиком по цене 10% от стоимости тачки
		if( GetPlayerState(playerid) == PLAYER_STATE_DRIVER
			&& nCarModel[playerid] == 525
			&& gTrailerAttached[playerid]) //для автомехаников начало STEP3
		{	//если игрок взял на буксир и за рулём эвакуатора
		    if(!gJobDuty[playerid])
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   Вы Не на Дежурстве вашей АвтоРемонтной Службы !");
		        return 1;
		    }
			if(!IsTrailerAttachedToVehicle(nCarID[playerid]))//если уже что то присоеденено к тачке игрока
			{   //если что-то присоед к нашей
				SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты чё удумал, нет тачки нет денег!");
				return 1;
			}
	        if(nTrailerModel[playerid] == 525)//если счётчик времени отсчитал значение в зависимости отскила
	        {
	  			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы не за рулём TowTruck!");
	 			return 1;
	        }
	        if(VehInfo[nTrailerID[playerid]][cType] < 1000)//если счётчик времени отсчитал значение в зависимости отскила
	        {
	  			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты чё, самый хитрый!");
	 			return 1;
	        }
	        if(PlayerInfo[playerid][pCarTime] > 0)//если счётчик времени отсчитал значение в зависимости отскила
	        {
   				SendClientMessage(playerid, COLOR_GREY, "   Вы уже Сдали автомобиль, ожидайте следующего времени сдачи (USE: /time)!");
  				return 1;
	        }
			/*if(VehHealth[nTrailerID[playerid]] > 900.0)
			{   //если здоровье тачки > 900.0 или это битая тачка  || nTrailerModel[playerid] == 604 || nTrailerModel[playerid] == 605
    			format(strings, sizeof(strings), "Работодатель: {0080FF}транспорт [%d] достаточно целый [%.0f hp]. Не принимается!", nTrailerID[playerid], VehHealth[nTrailerID[playerid]]);
			  	SendClientMessage(playerid, COLOR_GREEN, strings);
				return 1;
			}*/
		    if(	VehInfo[nTrailerID[playerid]][cPark] > 0)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Запаркованное транспортное средство не подлежит разборке !");
			    return 1;
			}
			new money;//, skill;
			PlayerInfo[playerid][pMechSkill] += 10;
			new level = PlayerInfo[playerid][pMechSkill];
			if(level == 50) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 2.");
			else if(level == 100) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 3.");
			else if(level == 200) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 4.");
			else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 5.");
			//--------------------------------------------------
			if(level < 50) { /*skill = 1;*/ money = 100 + random(100); PlayerInfo[playerid][pCarTime] = 600;}
			else if(level >= 50 && level < 100) { /*skill = 2;*/ money = 200 + random(100); PlayerInfo[playerid][pCarTime] = 540;}
			else if(level >= 100 && level < 200) { /*skill = 3;*/ money = 300 + random(100); PlayerInfo[playerid][pCarTime] = 480;}
			else if(level >= 200 && level < 400) { /*skill = 4;*/ money = 400 + random(100); PlayerInfo[playerid][pCarTime] = 420;}
			else if(level >= 400) { /*skill = 5;*/ money = RANDMONEY5; PlayerInfo[playerid][pCarTime] = 360;}
			BizInfo[0][bTill] -= money; BizInfo[0][bImport] += money;
			//--------------------------------------------------
			new Float: price = compcost*(100+SBizInfo[58][sbBuyProd])/100.0;//15*(100+5)/100 = 15,75 - сдача на базе механов
			new cost = VehicleArray[nCarModel[playerid]-400][Virtual_Price]*(SBizInfo[58][sbBuyProd])/100;//37282*5/100 = 1864,1
			new iMaterials = floatround( cost/price, floatround_ceil);//1864,1/15,75 = 118,3555555556
			//PlayerInfo[playerid][pMats] += iMaterials/2;
			SBizInfo[58][sbProducts] += iMaterials;//т.к. игрок сдал тачку
			SBizInfo[58][sbTill] -= cost;
			SBizInfo[58][sbImport] += cost;
			
			GivePlayerMoneyB(fsbiz+58, playerid, (money+cost));
			
        	//format(strings, sizeof(strings), "%s: {0080FF}Я перевёл тебе {33AA33}$%d{0080FF} за снятых с тачки {FFFFFF}%d запчастей!",
			//	SBizInfo[58][sbDiscription], (money+cost), iMaterials);
				
			new strtmp[138];//76 + 20+32+10 = 138
        	format(strtmp, sizeof(strtmp), "%s: {0080FF}За снятые запчасти с {FFFFFF}%s{0080FF} ты получил {33AA33}$%d.",
				SBizInfo[58][sbDiscription], VehicleArray[nTrailerModel[playerid]-400][Vehicle_Name], (money+cost));
			SendClientMessage(playerid, COLOR_GREEN, strtmp);
			SendClientMessage(playerid, COLOR_GREY, "USE: /time, чтобы узнать время следующего задания.");
				
        	//format(strings, sizeof(strings), "%s: {0080FF}За снятые запчасти с {FFFFFF}%s{0080FF} ты получил {FFFFFF}%d{0080FF} деталей для тюнинга машин!!",
			//	SBizInfo[58][sbDiscription], VehicleArray[nTrailerModel[playerid]-400][Vehicle_Name], iMaterials/2);
			//SendClientMessage(playerid, COLOR_GREEN,strings);
			//SendClientMessage(playerid, COLOR_GREEN, "USE: /time, чтобы узнать время следующего задания.");
			
			SetVehicleToRespawnEx(playerid, nTrailerID[playerid]);

			gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		}//для автомехаников конец
		else//для разборки своей тачки любым игроком
		{
			if(SBizInfo[58][sbTill] <= 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Извените, в кассе нет больше денег.");
				return 1;
			}
	       	if(!IsPlayerInAnyVehicle(playerid) || !nCarID[playerid])
			{
				SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
				return 1;
			}
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			{
				SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
				return 1;
			}
			if(	IsTrailerAttachedToVehicle(nCarID[playerid]) && PlayerInfo[playerid][pJob] == TRUCKER)
			{
				if(	nTrailerID[playerid] != MyCar[playerid][0] &&
					nTrailerID[playerid] != MyCar[playerid][1] &&
					nTrailerID[playerid] != MyCar[playerid][2])
				{   //если это не ваша тачка
					SendClientMessage(playerid, COLOR_GREY, "  Это не ваш прицеп!");
					return 1;
				}
				new money = VehicleArray[nTrailerModel[playerid]-400][Virtual_Price]*SBizInfo[58][sbBuyProd]/100;
				new msgitem[24+52+44+66 + 32+3+6];
				format(msgitem, sizeof(msgitem), "{0080FF}Ваш прицеп\
\n{FFFFFF}%s{0080FF} [modelid: {FFFFFF}%d{0080FF}]\
\nподлежит утилизации по цене {33AA33}$%d.\
\n\n{AFAFAF}Нажмите Accept, если согласны утилизировать ваш авто.",
					VehicleArray[nTrailerModel[playerid]-400][Vehicle_Name],nTrailerModel[playerid],money);
				ShowPlayerDialogGap(playerid, AUTOREPAIR_DIALOG, DIALOG_STYLE_MSGBOX, SBizInfo[58][sbDiscription], msgitem, "Accept", "Cancel");
			}
			else
			{
				if(	nCarID[playerid] != MyCar[playerid][0] &&
					nCarID[playerid] != MyCar[playerid][1] &&
					nCarID[playerid] != MyCar[playerid][2])
				{   //если это не ваша тачка
					SendClientMessage(playerid, COLOR_GREY, "  Это не ваш транспорт!");
					return 1;
				}
			    if(	VehInfo[nCarID[playerid]][cPark] > 0)
				{
				    SendClientMessage(playerid, COLOR_GREY, "   Запаркованное транспортное средство не принимается !");
				    return 1;
				}
				new money = VehicleArray[nCarModel[playerid]-400][Virtual_Price]*SBizInfo[58][sbBuyProd]/100;
				new msgitem[24+52+44+66 + 32+3+6];
				format(msgitem, sizeof(msgitem), "{0080FF}Ваш автомобиль\
\n{FFFFFF}%s{0080FF} [modelid: {FFFFFF}%d{0080FF}]\
\nподлежит утилизации по цене {33AA33}$%d.\
\n\n{AFAFAF}Нажмите Accept, если согласны утилизировать ваш авто.",
					VehicleArray[nCarModel[playerid]-400][Vehicle_Name],nCarModel[playerid],money);
				ShowPlayerDialogGap(playerid, AUTOREPAIR_DIALOG, DIALOG_STYLE_MSGBOX, SBizInfo[58][sbDiscription], msgitem, "Accept", "Cancel");
			}
		}
	}
	return 1;
}


stock mechanic_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	NoFuelDialogResponse(playerid, dialogid, response, listitem, inputtext);
	AutorepairDialogResponse(playerid, dialogid, response, listitem, inputtext);

	new msgitem[256+1];
	if(!response && dialogid == CALL_DIALOG)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		
		/*if(	MenuOperation[playerid] == 22 || MenuOperation[playerid] == 23 ||
			MenuOperation[playerid] == 24)
		{
			if(!gLoading[playerid] && !gUnLoading[playerid])
			{
				TogglePlayerControllableEx(playerid, 1);//размораживает
			}
		}*/

		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		Offer[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "RefillPrice", 0);
		gNoFuel[playerid] = 0;
		SetPVarInt(playerid, "RepairPrice", 0);
		SetPVarInt(playerid, "TuningPrice", 0);//цену на услугу обнуляем

		format(msgitem, sizeof(msgitem), "%s отказался от предложенной услуги !!", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		MenuOperation[playerid] = 0;
	 	return 1;
	}
	
	if(dialogid != CARMECHANIC_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);

	if(MenuOperation[playerid] == 8)
//else if(!strcmp(x_job, "refill", true))//для автомехаников исправлено
	{   // accept
	    if(Offer[playerid] >= MAX_PLAYERS-1)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Нет Предложений заправить ваш автомобиль !");
            return 1;
		}
		if(GetPlayerMoneyH(playerid) <= GetPVarInt(playerid, "RefillPrice"))
		{
            SendClientMessage(playerid, COLOR_GREY, "   Вы Не Можете позволить себе Заправиться !");
            return 1;
		}
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
			return 1;
		}
		if(CurState[playerid] != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
			return 1;
		}
		if( nCarModel[playerid] == 481 ||
		 	nCarModel[playerid] == 509 ||
		 	nCarModel[playerid] == 510 )
		{
			SendClientMessage(playerid, COLOR_GREY, "   Это транспортное средство не подлежит заправке!");
			return 1;
		}
        if(!IsPlayerConnected(Offer[playerid]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Предложивший вам игрок вышел из игры.");
			return 1;
		}
        if(	IsPlayerInAnyVehicle(Offer[playerid]))// || GetPlayerState(Offer[playerid]) != PLAYER_STATE_DRIVER
		{
			SendClientMessage(playerid, COLOR_GREY, "   Предложивший вам игрок НЕ должен находиться в автомобиле.");
			return 1;
		}
		if(IsInRentCar(nCarID[playerid]) && HireCarID[playerid] == MAX_VEHICLES-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете заправлять автомобиль проката, пока не оплатите аренду!");
			return 1;
		}
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
		//--------------------------------------------------
   		//new Float:
		FillUp = floatsub(VehicleArray[nCarModel[playerid]-400][GasMax], VehInfo[nCarID[playerid]][cFuel]);
		if(FillUp < 10.0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   В транспортном средстве достаточно топлива!");
			SendClientMessage(Offer[playerid], COLOR_GREY, "   В транспортном средстве достаточно топлива!");
			return 1;
		}
   		VehInfo[nCarID[playerid]][cFuel] = float(VehicleArray[nCarModel[playerid]-400][GasMax]);
		format(msgitem, sizeof(msgitem), "* Вам заправил автомобиль на %.1fл, за $%d АвтоМеханик %s.", FillUp, GetPVarInt(playerid, "RefillPrice"), PlayerName(Offer[playerid]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "* Вы заправили %s'а автомобиль на %.1fл. Вам перечислено на счёт в банке {33AA33}$%d.", PlayerName(playerid), FillUp, GetPVarInt(playerid, "RefillPrice"));
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], GetPVarInt(playerid, "RefillPrice"));
		GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -GetPVarInt(playerid, "RefillPrice"));//отнять у заказчика
        Offer[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "RefillPrice", 0);
		gNoFuel[playerid] = 0;
	    TogglePlayerControllableEx(playerid, 1);
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 9)
	//else if(!strcmp(x_job, "repair", true))//для автомехаников
	{   // accept
	    if(Offer[playerid] >= MAX_PLAYERS-1) return 1;
        if(GetPlayerMoneyH(playerid) <= GetPVarInt(playerid, "RepairPrice"))
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Вы Не Можете оплатить Ремонт !");
			return 1;
		}
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в транспортном средстве!");
			return 1;
		}
		if(CurState[playerid] != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться за рулём транспортного средства!");
			return 1;
		}
		if( IsInBike(nCarID[playerid]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   Это транспортное средство не подлежит ремонту!");
			return 1;
		}
        if(!IsPlayerConnected(Offer[playerid]))
        {
   			SendClientMessage(playerid, COLOR_GREY, "   Нет Предложений на ремонт вашего автомобиля !");
			return 1;
		}
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
        if(	IsPlayerInAnyVehicle(Offer[playerid]))// || GetPlayerState(Offer[playerid]) != PLAYER_STATE_DRIVER
		{
			SendClientMessage(playerid, COLOR_GREY, "   Предложивший вам игрок НЕ должен находиться в автомобиле.");
			return 1;
		}
        if(	VehHealth[nCarID[playerid]] > 900)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Транспортное средство не требует ремонта.");
			SendClientMessage(Offer[playerid], COLOR_GREY, "   Транспортное средство не требует ремонта.");
			return 1;
		}
	    RepairVehicleEx(playerid, nCarID[playerid]);//чиним тачку
		GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], GetPVarInt(playerid, "RepairPrice"));
		GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -GetPVarInt(playerid, "RepairPrice"));
		format(msgitem, sizeof(msgitem), "* Ваш автомобиль отремонтирован на сумму $%d АвтоМехаником %s.",GetPVarInt(playerid, "RepairPrice"),PlayerName(Offer[playerid]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "* Вы отремонтировали %s'у автомобиль, $%d добавлено к вашей Зарплате.", PlayerName(playerid),GetPVarInt(playerid, "RepairPrice"));
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
        Offer[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "RepairPrice", 0);
	}
	else if(MenuOperation[playerid] == 10)
	//else if(!strcmp(x_job, "moding", true))//для автомехаников
	{   //оплата клиентов счёта за модификацию машины с повышением навыка
	    if(Offer[playerid] < MAX_PLAYERS-1)
	    {
	        if(GetPlayerMoneyH(playerid) > GetPVarInt(playerid, "TuningPrice"))
		    {
            	if(!IsPlayerInAnyVehicle(playerid))
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в транспортном средстве!");
					return 1;
				}
				if(CurState[playerid] != PLAYER_STATE_DRIVER)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться за рулём транспортного средства!");
					return 1;
				}
				if( IsInBike( nCarID[playerid] ) )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Это транспортное средство не подлежит модификации!");
					return 1;
				}
		        if(IsPlayerConnected(Offer[playerid]))
		        {
			        if( IsPlayerInVehicle(Offer[playerid], nCarID[playerid]) )
					{
						PlayerInfo[Offer[playerid]][pMats] -= 70;
						PlayerInfo[Offer[playerid]][pMechSkill] ++;
		                if(PlayerInfo[Offer[playerid]][pMechSkill] == 50)
						{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык АвтоМеханика теперь Уровня 2, Вы можете залить больше Топлива в Автомобиль Игрока."); }
						else if(PlayerInfo[Offer[playerid]][pMechSkill] == 100)
						{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык АвтоМеханика теперь Уровня 3, Вы можете залить больше Топлива в Автомобиль Игрока."); }
						else if(PlayerInfo[Offer[playerid]][pMechSkill] == 200)
						{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык АвтоМеханика теперь Уровня 4, Вы можете залить больше Топлива в Автомобиль Игрока."); }
						else if(PlayerInfo[Offer[playerid]][pMechSkill] == 400)
						{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык АвтоМеханика теперь Уровня 5, Вы можете залить больше Топлива в Автомобиль Игрока."); }
						GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], GetPVarInt(playerid, "TuningPrice"));
						GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -GetPVarInt(playerid, "TuningPrice"));//отнимаем у клиента
						format(msgitem, sizeof(msgitem), "* Ваш автомобиль готов к модификации. Стоимость $%d. АвтоМеханик %s.",GetPVarInt(playerid, "TuningPrice"),PlayerName(Offer[playerid]));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
						format(msgitem, sizeof(msgitem), "* Автомобиль %s'а готов к модификации. Вам перечислено на счёт в банке $%d.", PlayerName(playerid),GetPVarInt(playerid, "TuningPrice"));
						SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);//послать тому кто предложил услугу
						ShowMenuForPlayerEx(mTuningMenu, playerid);
				        Offer[playerid] = MAX_PLAYERS-1;//Предложение освобождаем
						SetPVarInt(playerid, "TuningPrice", 0);
			    	    TogglePlayerControllableEx(playerid, 0);//обездвиживает нельзя двигаться
					}
					else { SendClientMessage(playerid, COLOR_GREY, "   Автомеханик не в Вашем автомобиле."); return 1; }
				}
			}
			else { SendClientMessage(playerid, COLOR_GREY, "   Вы Не Можете позволить себе Модернизацию !"); return 1; }
	    }
	    else
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Нет Предложений на Модернизацию вашего автомобиля !");
	    }
	}
	else if(MenuOperation[playerid] == 23)
	//else if(!strcmp(x_job, "mechanic", true))//для автомехаников
	{   //  /accept
		if(playeridMechanicCall >= MAX_PLAYERS-1)
		{   //если кто то из других механов принял вызов
			SendClientMessage(playerid, COLOR_GREY, "   Вызов уже принят !");
			return 1;
		}
		if( IsPlayerConnectedEx(playeridMechanicCall) && gPlayerSpawned[playeridMechanicCall] )
		{
			new Float:cX,Float:cY,Float:cZ;
			GetPlayerPos(playeridMechanicCall, cX, cY, cZ);
			SetPlayerCheckpointEx(playerid, cX, cY, cZ, CHECKPOINT_SIZE);
			SetPVarInt(playerid, "gCheckpointStatus", playeridMechanicCall);
			SetPlayerMarkerForPlayerEx(playerid, playeridMechanicCall, COLOR_LIGHTORANGE);
			new Float:distance = GetDistanceBetweenPlayers(playerid, playeridMechanicCall);
			new speed = 40000;//м/ч
			CallTime[playerid] = floatround(distance / speed * 3600);//секунд 3600.0
			format(msgitem, sizeof(msgitem), "* Вы приняли Вызов от %s[%d], у вас есть %d cекунд, чтобы добраться туда.",
				PlayerName(playeridMechanicCall), playeridMechanicCall, CallTime[playerid]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* АвтоМеханик %s принял ваш Вызов, пожалуйста ожидайте %s мин:cек в вашей текущей Позиции.",
				PlayerName(playerid),  TimeConverter(CallTime[playerid]));
			SendClientMessage(playeridMechanicCall, COLOR_ORANGE, msgitem);
			format(msgitem, sizeof(msgitem), "* АвтоМеханик %s принял вызов от %s'a.", PlayerName(playerid), PlayerName(playeridMechanicCall));
			SendJobMessage(7, COLOR_ORANGE, msgitem);
			GameTextForPlayerEx(playerid, "~w~Mechanic Caller~n~~r~Goto Red Marker", 5000, 1);
			CallTimeCounter[playerid] = 1;
			GPS_OnOff[playerid] = 1;
			gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			playeridMechanicCall = MAX_PLAYERS-1;
			MenuOperation[playerid] = 0;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			    //if(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1 && CallTimeCounter[i] == 0 && MarkerToPlayer[i] == MAX_PLAYERS-1)
			    if(MenuOperation[i] == 23)
			    {
					HideDialog(i);
					MenuOperation[i] = 0;
					TogglePlayerControllableEx(i, 1);//освобождает
				}
			}
		}
	}
	return 1;
}


//stock autorepair_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
stock AutorepairDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != AUTOREPAIR_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		return 1;
	}
	//new msgitem[256+1];
//если обычный игрок сдал тачку или прицеп на утилизацию
	SetPVarInt(playerid, "gShowDialog", -1);
	new carid, iMaterials, cost;//
	new Float: price = compcost*(100+SBizInfo[58][sbBuyProd])/100.0;
//продаём за 1% от стоимости
	//new Float: price = compcost*SBizInfo[58][sbBuyProd]/100.0;//20*1/100 = 101
	if(	IsTrailerAttachedToVehicle(nCarID[playerid]))
	{
		 if(PlayerInfo[playerid][pJob] == TRUCKER)
		 {
			carid = nTrailerID[playerid];
			cost = VehicleArray[nTrailerModel[playerid]-400][Virtual_Price]*(SBizInfo[58][sbBuyProd])/100;
			iMaterials = floatround(cost/price);
			//money = floatround( VehicleArray[nTrailerModel[playerid]-400][Virtual_Price]*SBizInfo[58][sbBuyProd]/100.0);
			//iMaterials = floatround(money/price, floatround_floor);
       		format(strings, sizeof(strings), "%s: {0080FF}Я перевёл тебе {33AA33}$%d за снятые с прицепа запчасти.", SBizInfo[58][sbDiscription], cost);
		}
	}
	else
	{
		carid = nCarID[playerid];
		cost = VehicleArray[nCarModel[playerid]-400][Virtual_Price]*(SBizInfo[58][sbBuyProd])/100;
		iMaterials = floatround(cost/price);
       	format(strings, sizeof(strings), "%s: {0080FF}Я перевёл тебе {33AA33}$%d за снятые с тачки запчасти.", SBizInfo[58][sbDiscription], cost);
		nCarID[playerid] = 0; nCarModel[playerid] = 0;
	}
	SendClientMessage(playerid, COLOR_GREEN,strings);

	if(carid == MyCar[playerid][0]) MyCar[playerid][0] = 0;
	else if(carid == MyCar[playerid][1]) MyCar[playerid][1] = 0;
	else if(carid == MyCar[playerid][2]) MyCar[playerid][2] = 0;

	VehInfo[carid][cInsur] = 0;
   	DestroyVehicleEx(carid, 3);

	GivePlayerMoneyB(fsbiz+58, playerid, cost);//для экономики
	SBizInfo[58][sbProducts] += iMaterials;
	SBizInfo[58][sbTill] -= cost;
	SBizInfo[58][sbImport] += cost;

	nTrailerID[playerid] = 0; nTrailerModel[playerid] = 0;
	format(strings, sizeof(strings), "AdmCmd: %s has destroyed vehicle ID:%d Materials:%d Cost:%d", PlayerName(playerid), carid, iMaterials, cost);
	SendAllAdminMessage(COLOR_RED, strings, 6);
	return 1;
}


//stock OnPlayerKeyCarDeliver(playerid, newkeys,oldkeys)//для автомехаников начало
stock mechanic_OnPlayerKeyState_DOWN(playerid)
{
		if(PlayerInfo[playerid][pJob] != CARMECHANIC) return 1;
		if( nCarModel[playerid] != 525 && nCarModel[playerid] != 539) return 1;
		//----------------------------------------------------------------------
	   	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ АВТОМЕХАНИКОМ
		//для автомехаников начало STEP2
	    if(IsTrailerAttachedToVehicle(nCarID[playerid]))//если уже что то присоеденено к тачке игрока
	    {
	    	SendClientMessage(playerid, COLOR_GREY, "   К вашему транспорту уже что-то прицеплено");
			return 1;
		}
		//new vid;
		//foreachex(StreamedVehicle[playerid], vid)
		//for(new vid = 1; vid<=GetMaxVehicles; vid++)
		new vid = 1;
		for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
			if(StreamedVehicle[playerid][v] == -1) continue;
			vid = StreamedVehicle[playerid][v];

			if(GetDistanceToCar(playerid, vid) < 7.0 && vid != nCarID[playerid])
  			{ 	//если какая то тачка в радиусе 7 м и не является тачкой игрока
				if( nCarModel[playerid] == 428
					|| IsInPlane(vid) || IsInBoat(vid) || IsInBike(vid) || IsInMotorcycle(vid))
				{
					SendClientMessage(playerid, COLOR_GREY, "   двухколёсные, воздушные, водные средства нельзя брать на буксир !");
					return 1;
				}
				//----------------------------------------------------------------------
				for(new j = 0; j < sizeof(AvailableParkings); j++)
				{
					if( IsVehicleInArea(vid, AvailableParkings[j]) )
					{
						SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт запаркован на автостоянке, необходимо привозить брошеные авто!");
						return 1;
					}
				}
				/*if( IsVehicleInArea(vid, specialzone[10]))
				{
					SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт запаркован по Паркингу, необходимо привозить брошеные авто!");
					return 1;
				}*/
				if( VehInfo[vid][cPark] >= PARKING )//VehInfo[vid][cPark] != 0 &&
				{
					SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт запаркован по Паркингу, необходимо привозить брошеные авто!");
					return 1;
				}
/*if( VehInfo[vid][cPark] != 0)
{
	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт запаркован, необходимо привозить НЕ запаркованые авто! ВРЕМЕННО!");
	return 1;
}*/
				if( IsVehicleInArea(vid, specialzone[12]) )
				{
					SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт на свалке, необходимо привозить брошеные авто!");
					return 1;
				}
				if( VehInfo[vid][cPark] == 2)
				{
					SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт уже на свалке!");
					return 1;
				}
				//----------------------------------------------------------------------
				/*GetVehicleHealth(vid, VehHealth[vid]);
				if(VehHealth[vid] >= 900.0 && PlayerInfo[playerid][pJob] == CARMECHANIC)
   				{
   					format(strings, sizeof(strings), "Работодатель: {0080FF}транспорт [%d] целый [%.0f hp], необходимо привозить разбитые авто!", vid, VehHealth[vid]);
				  	SendClientMessage(playerid, COLOR_GREEN, strings);
				  	//return 1;
				}*/

				AttachTrailerToVehicleEx(vid, nCarID[playerid]);//прицепить тачку в радиусе к тачке игрока
				//ВНИМАНИЕ: ф-ии GetVehicleTrailer и IsTrailerAttachedToVehicle не будут работать при этом событии
				//AttachTrailerToVehicleEx и IsTrailerAttachedToVehicle
				nTrailerID[playerid] = vid;//Получить ID трейлера прикреплённогj к машине.
				nTrailerModel[playerid] = GetVehicleModel(nTrailerID[playerid]);//Узнает ID модели данного трейлера прикреплённог к машине.

				if(nTrailerID[playerid] != 0)
				{
					gTrailerAttached[playerid] = 1;//что то прицепил
				}
				//if(IsTrailerAttachedToVehicle(nCarID[playerid]))//ВНИМАНИЕ: не будет работать
				if(gTrailerAttached[playerid] && PlayerInfo[playerid][pJob] == CARMECHANIC)
				{
			      	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Привези этот транспорт на свалку.");
				}
				//break;
				return 1;
			}
		}
   		//if(Found == 0)
		SendClientMessage(playerid, COLOR_GREY, "   Рядом нет транспорта.");
		return 1;
}

stock mechanic_OnPlayerKeyState_UP(playerid)
{
		if(PlayerInfo[playerid][pJob] != CARMECHANIC) return 1;
		if( nCarModel[playerid] != 525 && nCarModel[playerid] != 539) return 1;
		//----------------------------------------------------------------------
		//если игрок взял на буксир и за рулём эвакуатора
		//if(gTrailerAttached[playerid] == 0) return 1;
	    if(!gJobDuty[playerid])
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Вы Не на Дежурстве вашей АвтоРемонтной Службы !");
	        return 1;
	    }
	    nTrailerID[playerid] = 0; nTrailerModel[playerid] = 0;
		if(IsTrailerAttachedToVehicle(nCarID[playerid]))
		{
			gTrailerAttached[playerid] = 1;
			nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]);//Получить ID трейлера прикреплённого к машине.
			nTrailerModel[playerid] = GetVehicleModel(nTrailerID[playerid]);//Узнает ID модели данного трейлера прикреплённого к машине.
		}
		if(!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerModel[playerid] == 0)//если уже что то присоеденено к тачке игрока
		{   //если что-то присоед к нашей
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты чё удумал, нет тачки нет денег!");
			return 1;
		}
		if(IsPlayerInArea(playerid, specialzone[12]))//свалка scramble
		{
			if(SBizInfo[57][sbTill] <= 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Извените, в кассе нет больше денег.");
				return 1;
			}
	        if(PlayerInfo[playerid][pCarTime] > 0)//если счётчик времени отсчитал значение в зависимости отскила
	        { //&& PlayerInfo[playerid][pMechSkill] < 400
   				SendClientMessage(playerid, COLOR_GREY, "   Вы уже Сдали автомобиль, ожидайте следующего времени сдачи (USE: /time)!");
  				return 1;
	        }
	        if(VehInfo[nTrailerID[playerid]][cType] < 1000)
	        {
   				SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты должен привозить авто с подписанными никами!");
  				return 1;
	        }
			//new skill;//money,
			PlayerInfo[playerid][pMechSkill] += 10;
			new level = PlayerInfo[playerid][pMechSkill];
			if(level == 50) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 2, Вы получаете $200-300.");
			else if(level == 100) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 3, Вы получаете $300-400.");
			else if(level == 200) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 4, Вы получаете $400-500.");
			else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык АвтоМеханика теперь 5, Вы получаете $600.");
			//--------------------------------------------------
			if(level < 50) { /*skill = 1; money = 100 + random(100);*/ PlayerInfo[playerid][pCarTime] = 600;}
			else if(level >= 50 && level < 100) { /*skill = 2; money = 200 + random(100);*/ PlayerInfo[playerid][pCarTime] = 540;}
			else if(level >= 100 && level < 200) { /*skill = 3; money = 300 + random(100);*/ PlayerInfo[playerid][pCarTime] = 480;}
			else if(level >= 200 && level < 400) { /*skill = 4; money = 400 + random(100);*/ PlayerInfo[playerid][pCarTime] = 420;}
			else if(level >= 400) { /*skill = 5; money = RANDMONEY5;*/ PlayerInfo[playerid][pCarTime] = 360;}
			//--------------------------------------------------
			new Float: price = compcost*(100+SBizInfo[57][sbBuyProd])/100.0;//15*(100+1)/100 = 15*(100+1)/100 = 15,15
			new cost = VehicleArray[nTrailerModel[playerid]-400][Virtual_Price]*(SBizInfo[57][sbBuyProd])/100;//37282*1/100 = 372,82
			new iMaterials = floatround(cost/price);//372,82/5,15 = 72,39223300971
			SBizInfo[57][sbProducts] -= iMaterials;
			//SBizInfo[57][sbTill] -= cost;
			//SBizInfo[57][sbImport] += cost;
/*
			new cost = VehicleArray[nTrailerModel[playerid]-400][Virtual_Price]*(100+SBizInfo[57][sbBuyProd])/100;
//реально проверил 36151$*(100+1)/100=361$
			new Float: price = compcost*SBizInfo[57][sbBuyProd]/100.0;
//реально проверил 15$*1/100=0.15$
			new iMaterials = floatround(cost/price);
// реально проверил  361$/0.15$=2406.6

ДАНГЕР!!! весь проеб в SBizInfo[57][sbBuyProd] оно равно 1 а не 101!!!! отсюда если поставить процент покупки 109% то посчитай какие суммы даватся будут и матеров!!!
*/
			//13663*0.2=2732.6
			//GivePlayerMoneyB(fsbiz+57, playerid, cost);//для экономики
			PlayerInfo[playerid][pMats] += iMaterials;
			
			new strtmp[138];//76 + 20+32+10 = 138
        	format(strtmp, sizeof(strtmp), "%s: {0080FF}За снятые запчасти с {FFFFFF}%s{0080FF} ты получил {33AA33}%d материалов.",
				SBizInfo[57][sbDiscription], VehicleArray[nTrailerModel[playerid]-400][Vehicle_Name], iMaterials);
			SendClientMessage(playerid, COLOR_GREEN, strtmp);
			SendClientMessage(playerid, COLOR_GREY, "USE: /time, чтобы узнать время следующего задания.");
			DetachTrailerFromVehicleEx(nCarID[playerid]);//отсоединили от машины

			VehInfo[nTrailerID[playerid]][cPark] = 2;//пометили, что машина на свалке.

			//SaveCarParameters(nTrailerID[playerid]);
		    //GameTextForPlayerEx(playerid, "~r~Detach ~y~From Vehicle!",3000,1);//послать сообщение
			//SetVehicleToRespawnEx(playerid, nTrailerID[playerid]);

			gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		    return 1;
		}
		SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от места свалки !");
		return 1;
}


//stock NOFUEL_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
stock NoFuelDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{//нет топлива
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != NOFUEL_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	new msgitem[256+1];
	if(!response)
	{
	    if(MechanicsCounter < 1)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Нет Механиков на дежурстве в настоящее время, попробуйте еще раз позже !");
            return 1;
        }
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		    if(PlayerInfo[i][pJob] == CARMECHANIC && gJobDuty[i] == 1 && CallTimeCounter[i] > 0 && MarkerToPlayer[i] == playerid)
		    {
	            SendClientMessage(playerid, COLOR_GREY, "   Вы уже сделали вызов !");
	            return 1;
			}
		}
	    format(msgitem, sizeof(msgitem), "Требуется Механик в %s.\nЗаказчик: %s\n\nНажмите Accept, чтобы принять", GetPlayerInZoneName(playerid), PlayerName(playerid));
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
		    if(PlayerInfo[i][pJob] == CARMECHANIC && gJobDuty[i] == 1 &&
				CallTimeCounter[i] == 0 && MarkerToPlayer[i] == MAX_PLAYERS-1 &&
				GetPlayerState(i) == PLAYER_STATE_DRIVER && nCarModel[i] == 525 )
		    {
				SendClientMessage(i, COLOR_ORANGE, msgitem);
				HideDialog(i);
				SetVehicleVelocity(nCarID[i], 0.0, 0.0, 0.0);
				MenuOperation[i] = 23;
				//TogglePlayerControllableEx(i, 0);//обездвиживает
				new TrafficManager[65];
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				format(TrafficManager, sizeof(TrafficManager), "[%02d:%02d:%02d] Диспетчер", lH,lM,lS);
				ShowPlayerDialogEx(i, CALL_DIALOG, DIALOG_STYLE_MSGBOX, TrafficManager,msgitem, "Accept", "Cancel");
			}
		}
    	SendClientMessage(playerid, COLOR_GREY, "   Вы вызвали Механика, подождите ответ. Оставайтесь на месте.");
    	playeridMechanicCall = playerid;
		return 1;
	}
	//new giveplayerid;

//ShowPlayerDialogEx(playerid, NOFUEL_DIALOG, DIALOG_STYLE_MSGBOX, "No fuel in Vehicle", msgitem, "FillCar", "Mechanic");
    if(PlayerInfo[playerid][pFuel] > 0)//если в канистру есть топливо
    {
		FillCar(playerid);
    }
    else
    {
	    if(PlayerInfo[playerid][pFuel] <= 0)//если в канистру залито 20 л топлива
	    {
			format(msgitem, sizeof(msgitem), "%s\nВаш топливный Бак пуст.\nНадо было вовремя заправлять!\
											\nУ Вас не осталось Топлива в вашей Канистре!\
											\nНажмите Mechanic, чтобы вызвать механика.\
											\nПожалуйста ожидайте ответ Диспетчера.", PlayerName(playerid));
		}//нельяз чтобы окно блокировалось при скорости больше 10, т.к. машина ещё катится без топлива
		ShowPlayerDialogEx(playerid, NOFUEL_DIALOG, DIALOG_STYLE_MSGBOX, "No fuel in Vehicle", msgitem, "FillCar", "Mechanic");
	}
	return 1;
}

stock mechanic_OnEnterCheckpoint(playerid)
{
	if(GetPVarInt(playerid, "gCheckpointStatus") != CHECKPOINT_NONE)//если был установлен маркер GPS или на игрока или маркер вызова
	{   //если gCheckpointStatus == 255
		if(CallTimeCounter[playerid] > 0)//для медиков //для автомехаников //для таксистов STEP6
		{
			CallTimeCounter[playerid] = 0;
			CallTime[playerid] = 0;
			//format(strings, sizeof(strings), "~p~BPEM%s ~w~%s", RusToGame("Я"), TimeConverter(CallTimeCounter[playerid]) );
			//PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strings);
			PlayerTextDrawSetStringEx(playerid, txdRaceTime[playerid], TimeConverter(CallTimeCounter[playerid]));
			/*if(PlayerInfo[playerid][pCarTime] <= 0)
			{
				gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			}*/
		}

		//SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], COLOR_ALIVE);// 0xFF0000FF
		SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], ACTION_COLOR);
		playeridTaxiAccepted[playerid] = MAX_PLAYERS-1;
		DisablePlayerCheckpointEx(playerid);
		SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
		GPS_OnOff[playerid] = 0;
		GameTextForPlayerEx(playerid, "~r~RedMarker gone", 2500, 1);
	}
}

