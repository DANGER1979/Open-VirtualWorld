//для таксистов
/*
 Василий (13:26:37 15/12/2012)
Берешь работу, арендуешь тачку, катаешься по штату.
тк там онлайн дохеренный всегда есть кого куда подвести.
скилл идет если нажали одобрено x2
если плохо x1
идет скилл только если я проехал норм количество метров с пассажиром и если я не брал одного пассажира несколько раз
в конце часа дается зп в зависимости от скилла из казны штата
если нажимали хорошо, то плюсуется премия
*/


new TaxiValue = 50;//50 баксов за секунду проезда


//new TransportDriver[MAX_PLAYERS];//id таксиста/водилы автобуса
//new TransportValue[MAX_PLAYERS];//цена за проезд на такси/автобусе
//new CostRoute[MAX_PLAYERS];//стоимость маршрута
//new TransportEarning[MAX_PLAYERS];//полная выручка только для автобуса/такси

//для таксистов STEP8
//таксометр для пассажира, но с информированием водителю
//stock taxi_OnPlayerCallTime(playerid)
stock taxi_OneSecondTimers(playerid)
{
	if(gTransportTime[playerid] <= 0)  return 1;
	
	if( IsPlayerConnectedEx(TransportDriver[playerid])
		&& TransportDriver[playerid] < MAX_PLAYERS-1
		&& IsPlayerInVehicle(playerid, nCarID[TransportDriver[playerid]]) //для таксистов и пассажиров
		&& !IsTunTeleport(playerid))
	{	//если таксометр пассажира запущен TaxiPassenger[i]
		CrashDetected[playerid] = 234;
	    new taxidriver = TransportDriver[playerid];
	    new taxiid = nCarID[taxidriver];
	    new distance = VehInfo[taxiid][cDist]-gTransportTime[playerid];//gTransportTime - отметка пробега на момент посадки
		if( distance > 94.0) distance = 0;
		new Float: fuel = distance*VehicleArray[nCarModel[taxidriver]-400][fuelConsumption]/(RealMeter*1000.0);//RealMeter=2.5 сколько литров топливо ушло
//1000*11/2500=4.4
		//fuel = 6091*11/2500=26.8004
		//от мотеля до АШ 6091метр 33доллара потрачено 31ед топлива
		//costfuel = 27
		new Float: costfuel = fuel*FuelCost;//литры * стоимость 1 литра * процент продажи = стоимость заправки
//4.4*0.1=0.44
//ВНИМАНИЕ: округлять только вещественную, целую не надо округлять, но при этом может быть потеря точности
//ВНИМАНИЕ: лучше округлять каждый отдельно,чем все вместе
//ВНИМАНИЕ: для получения вещественной лучше делить на вещественную, но чем меньше вещественных тем быстрее
//floatround(3.3, floatround_round);
//floatround_round	Round to the nearest integer. A fractional part of exactly 0.5 rounds upwards (this is the default).
//floatround_floor	Round downwards. Лучше вообще ни чего не ставить, т.к. подпедаливает
//floatround_ceil	Round upwards.
//floatround_tozero	Round downwards for positive values and upwards for negative values (“truncate”).

	 //проверка на наличие денег у пассажира
			/*if(GetPlayerMoneyH(playerid) < TransportCostCounter[playerid])
			{  //если денег нет, то выкидываем из тачки
				new strtmp[40+10];
				format(strtmp, sizeof(strtmp), "* Вам нужно %d$, чтобы оплатить проезд.", TransportCostCounter[playerid]);
				SendClientMessage(playerid, COLOR_GREY, strtmp);
				RemovePlayerFromVehicleEx(playerid);

				PlayerInfo[TransportDriver[playerid]][pTaxiSkill] ++;
				TransportCostCounter[TransportDriver[playerid]] = 0;
		    	format(strings, sizeof(strings), "   Пассажир {FFFFF}%s{0080FF} покинул ваше Такси. Полученная сумма {33AA33}$%d!!!", PlayerName(playerid), TransportCostCounter[playerid]);
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);

				TransportCostCounter[playerid] = 0;//обнулили стоимость поездки для пассажира

				gTransportTime[TransportDriver[playerid]] = 0;
				gTransportTime[playerid] = 0;//остановили таксометр при выходе из машины

				TransportDriver[TransportDriver[playerid]] = MAX_PLAYERS-1;
				TransportDriver[playerid] = MAX_PLAYERS-1;//освободили переменную таксиста у пассажира

				TaxiPassenger[TransportDriver[playerid]] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста
				TaxiPassenger[playerid] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста
			}
			else
			{*/
	  	TransportCostCounter[playerid] = floatround(costfuel*TransportValue[taxidriver]*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])/(2+2));
//0,44*50*(1+0)/(2+2) = 5,5
  		//27*50*((1+0)/4)=337.5 для 1 лвл
  		//27*50*((2+2)/4)=1350
		//}
		new cost;//обязательно временная локальная переменная
		//for(new i=0; i<GetMaxPlayers(); i++)
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i)) continue;
			if( IsPlayerInVehicle(i, nCarID[taxidriver]))
			{	//сканируем всех кто находится в данной тачке
				//TransportCostCounter[taxidriver] += TransportCostCounter[i];//ни в коем случаи
				cost += TransportCostCounter[i];
		    }
		}
	    //format(strings, sizeof(strings), "fuel: %.1f costfuel: %.1f TransportCost: %d", fuel, costfuel, TransportCostCounter[playerid]);
		//SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		new strtmp[44+3+6+10+10];
	    format(strtmp, sizeof(strtmp), "~r~%dm ~w~: ~g~+%.1f skill", distance, 2.0*cost/1000.0);//cost, TransportCostCounter[playerid]);
	    GameTextForPlayerEx(TransportDriver[playerid], strtmp, 1500, 6);
    }
	return 1;
}
stock taxi_OnPlayerConnect(playerid)
{
	playeridTaxiAccepted[playerid] = MAX_PLAYERS-1;//для таксистов
	
}

stock taxi_OnPlayerDisconnect(playerid)
{
	if(TransportCostCounter[playerid] > 0 && TransportDriver[playerid] < MAX_PLAYERS-1)
	{	//игрок вышел из игры во время запущенного таксометра и установленного таксиста для него
	    if(IsPlayerConnected(TransportDriver[playerid]))
		{
			if(PlayerInfo[playerid][pTaxiSkill] < (1000-1)) PlayerInfo[TransportDriver[playerid]][pTaxiSkill] ++;
			TransportCostCounter[TransportDriver[playerid]] = 0;

	    	//format(strings, sizeof(strings), "   Пассажир %s покинул ваше Такси. Полученная сумма $%d!!!", PlayerName(playerid), TransportCostCounter[playerid]);
	    	format(strings, sizeof(strings), "   Пассажир %s покинул ваше Такси.!!!", PlayerName(playerid));
	        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);

			TransportCostCounter[playerid] = 0;//обнулили стоимость поездки для пассажира
			gTransportTime[TransportDriver[playerid]] = 0;
			gTransportTime[playerid] = 0;//остановили таксометр при выходе из машины
			TransportDriver[TransportDriver[playerid]] = MAX_PLAYERS-1;
			TransportDriver[playerid] = MAX_PLAYERS-1;//освободили переменную таксиста у пассажира
			TaxiPassenger[TransportDriver[playerid]] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста
			TaxiPassenger[playerid] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста
		}
	}
}

stock taxi_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext

	new msgitem[256+1];
	if(!response && dialogid == CALL_DIALOG)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		if(	MenuOperation[playerid] == 22 || MenuOperation[playerid] == 23 ||
			MenuOperation[playerid] == 24)
		{
			if(!gLoading[playerid] && !gUnLoading[playerid])
			{
				TogglePlayerControllableEx(playerid, 1);//размораживает
			}
		}
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
	if(dialogid != TAXI_DIALOG) return 1;//для таксистов STEP10
//ShowPlayerDialogGap(playerid, TAXI_DIALOG, DIALOG_STYLE_MSGBOX, "Диспетчер",
	SetPVarInt(playerid, "gShowDialog", -1);
	//GivePlayerMoneyH(fjob+PlayerInfo[TransportDriver[playerid]][pJob], playerid, -TransportCostCounter[playerid]);
 		//TAX -= TransportCostCounter[playerid];
	if(response)
	{
//надо заново пересканировать пассажиров
	    //format(strings, sizeof(strings), "~w~Passenger left the ~n~~g~Earned ~r~$%d",TransportCostCounter[playerid]);//+money
	    //GameTextForPlayerEx(TransportDriver[playerid], strings, 5000, 1);
    	//format(strings, sizeof(strings), "   Пассажир %s покинул ваш транспорт довольным. Полученная сумма $%d!", PlayerName(playerid), TransportCostCounter[playerid]);//+money
        //SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		if(MenuOperation[playerid] == 43)//для таксистов STEP2
		{
	        gJobDuty[playerid] = 1;
	        TaxiDriversCounter += 1;
			TransportValue[playerid] = TaxiValue;
			TransportCostCounter[playerid] = 0;

			if(listitem == 0)
			{
				/*if(TaxiDriver[0] < MAX_PLAYERS-1)
				{
	   				format(msgitem, sizeof(msgitem), "   Маршрут уже занял %s[%d] !", PlayerName(TaxiDriver[0]), TaxiDriver[0]);
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}*/
				TaxiDriver[0] = playerid;//записать ID водилы на этом маршруте
    			format(msgitem, sizeof(msgitem), "Таксист {FFFFFF}%s[%d]: Лос-Сантос. Плата за проезд: {33AA33}$%d.",
					PlayerName(playerid), playerid, TransportValue[playerid]);
    			//JobNews(COLOR_ORANGE,msgitem);
    			new text[55+10];
    			format(text, sizeof(text), "Лос-Сантос\nЦена за посадку: {33AA33}$%d.", TransportValue[playerid]);
			    //LabelOnHead[playerid] = Create3DTextLabel(text, COLOR_ORANGE, 0.0,0.0,0.0, 50.0,0,1);
			    //Attach3DTextLabelToVehicle(LabelOnHead[playerid], nCarID[playerid], 0.0, 0.0, 1.0);
				DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0); 
			}
			else if(listitem == 1)
			{
				/*if(TaxiDriver[1] < MAX_PLAYERS-1)
				{
	   				format(msgitem, sizeof(msgitem), "   Маршрут уже занял %s[%d] !", PlayerName(TaxiDriver[1]), TaxiDriver[1]);
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}*/
				TaxiDriver[1] = playerid;
	   			format(msgitem, sizeof(msgitem), "Таксист {FFFFFF}%s[%d]: Сан-Фиерро. Плата за проезд: {33AA33}$%d.",
				   	PlayerName(playerid), playerid, TransportValue[playerid]);
	   			//JobNews(COLOR_ORANGE,msgitem);
    			new text[55+10];
    			format(text, sizeof(text), "Сан-Фиерро\nЦена за посадку: {33AA33}$%d.", TransportValue[playerid]);
				//Delete3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    //LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0,0.0,0.0, 50.0,0,1);
			    //Attach3DTextLabelToVehicle(LabelOnHead[playerid], nCarID[playerid], 0.0, 0.0, 1.0);
				DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0);
			}
			else if(listitem == 2)
			{
				/*if(TaxiDriver[2] < MAX_PLAYERS-1)
				{
	   				format(msgitem, sizeof(msgitem), "   Маршрут уже занял %s[%d] !", PlayerName(TaxiDriver[2]), TaxiDriver[2]);
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}*/
				TaxiDriver[2] = playerid;
	   			format(msgitem, sizeof(msgitem), "Таксист {FFFFFF}%s[%d]: Лас-Вентурас. Плата за проезд: {33AA33}$%d.",
				   	PlayerName(playerid), playerid, TransportValue[playerid]);
	   			//JobNews(COLOR_ORANGE,msgitem);//60+
    			new text[55+10];
    			format(text, sizeof(text), "Лас-Вентураc\nЦена за посадку: {33AA33}$%d.", TransportValue[playerid]);
				//Delete3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    //LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0,0.0,0.0, 50.0,0,1);
			   //Attach3DTextLabelToVehicle(LabelOnHead[playerid], nCarID[playerid], 0.0, 0.0, 1.0);
			    DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0);
			}
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FF6600}%s\n", lH,lM,lS, msgitem);
			//--------------------------------------------------------------
//для таксистов STEP7
			//если пассажир сидел, а таксист вышел и снова сел
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
		        if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(!IsPlayerInAnyVehicle(i)) continue;
				if(GetPlayerState(i) != PLAYER_STATE_PASSENGER) continue;
	            if( !IsPlayerInVehicle(i, nCarID[playerid]) ) continue;
               	TransportDriver[i] = playerid;//записали ID таксиста по индексу пассажира
               	TaxiPassenger[playerid] = i;//записали ID пассажира по индексу водителя
               	//при нескольких пассажирах будет показывать ИД последнего

			    gTransportTime[i] = gTransportTime[playerid];//записали текущий пробег и подняли флаг только для пассажира
			    //чтобы дважды не нагружать сервер

               	TransportCostCounter[i] += TransportValue[i];
				GPS_OnOff[playerid] = 0;
				//format(msgitem, sizeof(msgitem), "* Вы уплатили %d$ Водителю Такси.", TransportValue[playerid]);
				//SendClientMessage(i, COLOR_LIGHTBLUE, msgitem);
    			format(msgitem, sizeof(msgitem), "~w~Passenger %s~n~~g~has chosen your Taxi", PlayerName(i));//+money
    			GameTextForPlayerEx(playerid, msgitem, 5000, 1);
    		}
		}
		else if(MenuOperation[playerid] == 44)
		{
			if(PlayerInfo[playerid][pLevel] > 0)
			{//чем выше уровень тем, меньше опыта добавляет.
				if(PlayerInfo[playerid][pTaxiSkill] < (1000-2.0*TransportCostCounter[playerid]/1000.0)) {
					PlayerInfo[TransportDriver[playerid]][pTaxiSkill] += floatround(2.0*TransportCostCounter[playerid]/1000.0);
				}
				//GivePlayerMoneyB(fjob+PlayerInfo[TransportDriver[playerid]][pJob], TransportDriver[playerid], TransportCostCounter[playerid]);//добавляем сумму именно этого пассажира что покинул
				//TAX += TransportCostCounter[playerid];
		    	format(strings, sizeof(strings), "   Пассажир %s покинул ваш транспорт довольным!", PlayerName(playerid));//+money
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		    	format(strings, sizeof(strings), "   Вы получили %d очков опыта работы таксиста!", floatround(2.0*TransportCostCounter[playerid]/1000.0));//+money
	        	SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
			}
		}
		else if(MenuOperation[playerid] == 24)
		//else if(!strcmp(x_job, "taxi", true))//для таксистов STEP4
		{
			if(playeridTaxiCall >= MAX_PLAYERS-1)
			{   //если кто-то вызвал такси
				SendClientMessage(playerid, COLOR_GREY, "   Вызов уже принят !");
				return 1;
			}
			if( IsPlayerConnectedEx(playeridTaxiCall) && gPlayerSpawned[playeridTaxiCall] )
			{
				new Float:cX,Float:cY,Float:cZ;
				GetPlayerPos(playeridTaxiCall, cX, cY, cZ);
				SetPlayerCheckpointEx(playerid, cX, cY, cZ, CHECKPOINT_SIZE);
				SetPVarInt(playerid, "gCheckpointStatus", playeridTaxiCall);
				SetPlayerMarkerForPlayerEx(playerid, playeridTaxiCall, COLOR_LIGHTYELLOW);
				new Float:distance = GetDistanceBetweenPlayers(playerid, playeridTaxiCall);
				new speed = 40000;//м/ч
				CallTime[playerid] = floatround(distance / speed * 3600);//секунд 3600.0
				format(msgitem, sizeof(msgitem), "* Вы приняли Вызов от %s[%d], у вас есть %d cекунд, чтобы добраться до туда.",
					PlayerName(playeridTaxiCall), playeridTaxiCall, CallTime[playerid]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
				format(msgitem, sizeof(msgitem), "* Водитель Такси %s принял ваш Вызов, пожалуйста ожидайте %s мин:cек в вашей текущей Позиции.",
					PlayerName(playerid), TimeConverter(CallTime[playerid]));
				SendClientMessage(playeridTaxiCall, COLOR_ORANGE, msgitem);
				format(msgitem, sizeof(msgitem), "* Таксист %s принял вызов от %s'a.", PlayerName(playerid), PlayerName(playeridTaxiCall));
				SendJobMessage(13, COLOR_ORANGE, msgitem);
				//GameTextForPlayerEx(playerid, "~w~Taxi Caller~n~~r~Goto Red Marker", 5000, 1);
				CallTimeCounter[playerid] = 1;//поднимаем флаг для запуска счётчика
				playeridTaxiAccepted[playerid] = playeridTaxiCall;//записали ID вызвавшего такси
				GPS_OnOff[playerid] = 1;
				gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
				playeridTaxiCall = MAX_PLAYERS-1;//освободили
				MenuOperation[playerid] = 0;
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				    //if(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1 && CallTimeCounter[i] == 0 && MarkerToPlayer[i] == MAX_PLAYERS-1)
				    if(MenuOperation[i] == 24)
				    {
						HideDialog(i);
						MenuOperation[i] = 0;
						TogglePlayerControllableEx(i, 1);//освобождает
					}
				}
			}
		}
	}
	else
	{
		if(MenuOperation[playerid] == 44)
		{
		    //format(strings, sizeof(strings), "~w~Passenger left the ~n~~g~Earned ~r~$%d",TransportCostCounter[playerid]);//+money
		    //GameTextForPlayerEx(TransportDriver[playerid], strings, 5000, 1);
	    	//format(strings, sizeof(strings), "   Пассажир %s покинул ваш транспорт НЕ довольным. Вы НЕ получили $%d!!", PlayerName(playerid), TransportCostCounter[TransportDriver[playerid]]);//+money
			if(PlayerInfo[playerid][pLevel] > 0)
			{//чем выше уровень тем, меньше опыта добавляет.
				if(PlayerInfo[playerid][pTaxiSkill] < (1000-2*TransportCostCounter[playerid]/1000.0)) {
					PlayerInfo[TransportDriver[playerid]][pTaxiSkill] += floatround(2.0*TransportCostCounter[playerid]/1000.0);
				}
				//GivePlayerMoneyB(fjob+PlayerInfo[TransportDriver[playerid]][pJob], TransportDriver[playerid], TransportCostCounter[playerid]);//добавляем сумму именно этого пассажира что покинул
		    	format(strings, sizeof(strings), "   Пассажир %s покинул ваш транспорт НЕ довольным!", PlayerName(playerid));//+money
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		    	format(strings, sizeof(strings), "   Вы получили всего %d очков опыта работы таксиста!", floatround(2.0*TransportCostCounter[playerid]/1000.0));//+money
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
			}
		}
	}
	if(MenuOperation[playerid] == 44)
	{
		TransportCostCounter[TransportDriver[playerid]] = 0;
		TransportCostCounter[playerid] = 0;//обнулили стоимость поездки для пассажира
		gTransportTime[TransportDriver[playerid]] = 0;
		gTransportTime[playerid] = 0;//остановили таксометр при выходе из машины
		TransportDriver[TransportDriver[playerid]] = MAX_PLAYERS-1;
		TransportDriver[playerid] = MAX_PLAYERS-1;//освободили переменную таксиста у пассажира
		TaxiPassenger[TransportDriver[playerid]] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста
		TaxiPassenger[playerid] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста
	}
	return 1;
}

stock taxi_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER)
	{   //если игрок был за рулём в машине и изменил своё состания
//для таксистов STEP10 начало
		if(TransportCostCounter[playerid] > 0 && PlayerInfo[playerid][pJob] == TAXIDRIVER)// && TaxiPassenger[playerid] < MAX_PLAYERS-1
		{   //таксист вышел из такси во время запущенного таксометра и установленного пассажира для него
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
		        if( !IsPlayerConnectedEx(i) ) continue;
				//if(!IsPlayerInAnyVehicle(i)) continue;
				//if(GetPlayerState(i) != PLAYER_STATE_PASSENGER) continue;
				//if(i != TaxiPassenger[playerid]) continue;//не будет работать при нескольких пассажирах
				if(TransportDriver[i] != playerid) continue;

 				//GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], i, -TransportCostCounter[i]);
		    	format(strings, sizeof(strings), "   Таксист %s покинул водительское место.", PlayerName(playerid));//+money
		        SendClientMessage(i, COLOR_LIGHTBLUE, strings);

				TransportCostCounter[playerid] += TransportCostCounter[i];//если было много пассажиров
				TransportCostCounter[i] = 0;//обнулили стоимость поездки для пассажира
				gTransportTime[i] = 0;//остановили таксометр при выходе из машины
				TransportDriver[i] = MAX_PLAYERS-1;//освободили переменную таксиста у пассажира
				TaxiPassenger[i] = MAX_PLAYERS-1;//освободили переменную пассажира у таксиста

    		}
 			GPS_OnOff[playerid] = 0;
			//GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, TransportCostCounter[playerid]);
			TransportCostCounter[playerid] = 0;//обнулили стоимость поездки для пассажира
			gTransportTime[playerid] = 0;//остановили таксометр при выходе из машины
			TransportDriver[playerid] = MAX_PLAYERS-1;//ИД таксиста освободили переменную таксиста у пассажира
			TaxiPassenger[playerid] = MAX_PLAYERS-1;//ИД пассажира освободили переменную пассажира у таксиста
		}//для таксистов конец
//для таксистов STEP11
		if(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid])
		{	//Taxi Cab Company
			FixJobCounter(playerid);
			//SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
	        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве вашей Службы и не получаете вызовы больше.");
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{
		//----------------------------------------------------------------------
//для таксистов
        if(GetSeatVehiclePlayer(nCarID[playerid], 0) != INVALID_PLAYER_ID)
        {//если за рулём вашей машину кто то сидит
			new driver = GetSeatVehiclePlayer(nCarID[playerid], 0);
			if(PlayerInfo[driver][pJob] == TAXIDRIVER && gJobDuty[driver])
			{
	      		gTransportTime[playerid] = VehInfo[nCarID[driver]][cDist];//записали текущий пробег
	           	TransportCostCounter[playerid] += TransportValue[driver];
	           	TransportDriver[playerid] = driver;//записали ID таксиста по индексу пассажира
	           	TaxiPassenger[driver] = playerid;//записали ID пассажира по индексу водителя

				GivePlayerMoneyH(fjob+PlayerInfo[driver][pJob], playerid, -TransportValue[driver]);//отнимаем деньги у пассажира цену за проезд на такси
				BizInfo[0][bTill] += TransportValue[driver]; BizInfo[0][bExport] += TransportValue[driver];
				
				GPS_OnOff[driver] = 0;
				//format(strings, sizeof(strings), "* Вы уплатили %d$ Водителю Такси %s.", TransportValue[driver], PlayerName(driver));
				//SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	   			format(strings, sizeof(strings), "~w~Passenger %s~n~~g~has chosen your Taxi", PlayerName(playerid));//+money
	   			GameTextForPlayerEx(driver, strings, 5000, 1);
			}
		}
	}
	else if(newstate == PLAYER_STATE_ONFOOT)//если ID нового состояния равно состоянию на ногах
	{   //если ID нового состояния равно состоянию 1
		if(TransportDriver[playerid] < MAX_PLAYERS-1)//для таксистов STEP9
		{   //пассажир вышел из такси во время установленного таксиста для него
		//TransportCostCounter[playerid] > 0// запущенного таксометра  - не ставить, т.к. при выходе из такси с нулевым таксометром не появится диалог
	//printf("TaxiDriver: %d TaxiCost: %d",  TransportDriver[playerid], TransportCostCounter[playerid]);
		    if(	IsPlayerConnected(TransportDriver[playerid]) && !IsPlayerNPC(TransportDriver[playerid]))
			{   //если его таксист ещё в игре
				MenuOperation[playerid] = 44;
				ShowPlayerDialogGap(playerid, TAXI_DIALOG, DIALOG_STYLE_MSGBOX, PlayerName(TransportDriver[playerid]),
					"Вы довольны оказанной услугой?\n\n{AFAFAF}Нажмите YES, если довольны.", "YES", "NO");
			}
		}
	}
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	taxi_TakeTask(playerid, modelid);
	return 1;
}

stock taxi_TakeTask(playerid, modelid)
{
	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ ТАКСИСТА
	if(modelid == 420 || modelid == 438)//для таксистов STEP1
	{
		if(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid] == 0)
		{
	    	new listitems[] = "1\tLS\n2\tSF\n3\tLV\n";
			MenuOperation[playerid] = 43;
			ShowPlayerDialogEx(playerid, TAXI_DIALOG, DIALOG_STYLE_LIST, "Работодатель: Выберите город для дежурства", listitems, "OK", "Cancel");//для таксистов STEP2
   		}
   		else if( IsPermitToRider(playerid) ) {	}
		else if( PlayerInfo[playerid][pJob] != TAXIDRIVER )
		{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Такси !");
			//return 1;
		}
	}///для таксистов конец
	return 1;
}


stock taxi_OnEnterCheckpoint(playerid)
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
