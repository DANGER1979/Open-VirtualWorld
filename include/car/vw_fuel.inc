
//##############################################################################//
//                                                                              //
//                          СИСТЕМА РАСХОДА ТОПЛИВА                             //
//                                                                              //
//##############################################################################//
forward OnVehicleFilling(playerid, vehicleid);

new gNoFuel[MAX_VEHICLES+1];//new gNoFuel[MAX_PLAYERS];//если нет топлива
new gRefueling[MAX_PLAYERS];//флаг - начало заправки
new GasCounter[MAX_PLAYERS];//счётчик заправки
new CostFuel[MAX_PLAYERS];
new Float: FillUp;//сколько надо долить
new FillingTimer[MAX_PLAYERS] = -1;

//<20:38:49> "SNap": Золотые ворота - 1.600 (мир) Гант - 650 (игра) = 1600/650 = 2.4
new Float: RealMeter = 2.5; //коэффициент пересчёта с реального растояния на игровое

#define MAX_GAS_PICKUPS 36
/*enum pickupsinfo
{
    //p_ID,
	p_model,
    p_type,
    Float:p_x,
    Float:p_y,
    Float:p_z,
    p_v
}*/
new GasStationPickups[MAX_GAS_PICKUPS][pickupsinfo] = {//координаты пикапов
//для заправок
{1317,14,1003.5368,-933.4891,42.1797},//1
{1317,14,1004.3036,-940.1742,42.1797},//1 //LS
{1317,14,1939.2177,-1772.7787,13.3828},//2.1
{1317,14,1944.4668,-1772.6499,13.3906},//2.2
{1317,14,-90.8836,-1168.9830,2.4203},//3 //FLINT COUNTY
{1317,14,-1609.3260,-2718.5137,48.5391},//4.1
{1317,14,-1605.3621,-2714.6418,48.5335},//4.2
{1317,14,-1602.4027,-2709.8135,48.5391},//4.3 //AngelPine
{1317,14,-2244.4719,-2560.9614,31.9219},//5
{1317,14,-2029.3414,157.3234,28.8359},//6 //SF
{1317,14,-2416.0239,975.4777,45.2969},//7.1
{1317,14,-2405.7397,976.0659,45.2969},//7.2
{1317,14,-1675.7146,413.1008,7.1797},//8
{1317,14,-1328.9539,2671.9795,50.0625},//9.1 //Tierra Robada
{1317,14,-1328.4802,2677.5134,50.0625},//9.2
{1317,14,-1327.8428,2682.7490,50.0625},//9.3
{1317,14,-1471.5114,1863.6404,32.6328},//10
{1317,14,70.3882,1218.6783,18.8120},//11 //BONE COUNTY
{1317,14,605.3773,1704.8448,6.9922},//12.1
{1317,14,608.2607,1699.5612,6.9922},//12.2
{1317,14,611.9772,1694.6018,6.9922},//12.3
{1317,14,615.6050,1690.0255,6.9922},//12.4
{1317,14,618.8618,1684.9766,6.9922},//12.5
{1317,14,621.9689,1679.9858,6.9922},//12.6 //LV
{1317,14,2639.8977,1106.6787,10.8203},//13
{1317,14,2202.0935,2474.4866,10.8203},//14
{1317,14,2147.4282,2748.4614,10.8203},//15
{1317,14,2114.5981,920.6873,10.8203},//16
{1317,14,1596.0123,2199.2844,10.8203},//17
{1317,14,1380.9836,456.6337,20.1462},//18 //RED COUNTY
{1317,14,652.2394,-565.2609,16.3359},//19.1
{1317,14,659.3037,-564.9469,16.3359},//19.2

//32
{3096,14,406.9748,2449.5771,17.9000},//20 16.5000+0.6
{3096,14,1581.8795,1181.0317,12.2125},//21 1581.8795,1181.0317,10.8125
{3096,23,-1436.8766,-526.8726,15.6719},//22.1
{3096,23,-1363.9728,-489.1934,15.6719}//22.2
//для установки пикапов заправок на -0.9 по оси Z
};


//перенесено в stock sbiz_OnGameModeInit()
stock fuel_OnGameModeInit()
{
	for(new pic = 0; pic < MAX_GAS_PICKUPS; pic++)
	{   //для установки пикапов заправок на -0.9 по оси Z на которых будет заправляться тачка
		SetPickupEx(GasStationPickups[pic][p_model],
			GasStationPickups[pic][p_type], GasStationPickups[pic][p_x], GasStationPickups[pic][p_y], GasStationPickups[pic][p_z]-0.9);
	}
}

//для заправок
stock IsAtGasStation(playerid)//возвращает номер заправки 1 по команде fuel или fillcar если игрок в зоне заправки
{   //все заправки СА
//СРЕДНИЕ ТОЧКИ
	if(IsPlayerInRangeOfPoint(playerid, 8.0, 1003.5368,-933.4891,42.1797)
	|| IsPlayerInRangeOfPoint(playerid, 8.0, 1004.3036,-940.1742,42.1797)	)//LS 1
	{//LS
		return GAS_STATION;//18
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 1939.2177,-1772.7787,13.3828)
	|| IsPlayerInRangeOfPoint(playerid, 8.0, 1944.4668,-1772.6499,13.3906))//LS 2
	{//LS
	    return GAS_STATION+1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -90.8836,-1168.9830,2.4203))//FLINT COUNTY 3
	{//Between LS and SF
	    return GAS_STATION+2;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1605.3621,-2714.6418,48.5335))//AngelPine 4
	{//Between LS and SF
	    return GAS_STATION+3;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -2244.4719,-2560.9614,31.9219))//AngelPine 5
	{//Between LS and SF
	    return GAS_STATION+4;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -2029.3414,157.3234,28.8359))//SF 6
	{//SF
	    return GAS_STATION+5;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -2416.0239,975.4777,45.2969)
	||	IsPlayerInRangeOfPoint(playerid, 8.0, -2405.7397,976.0659,45.2969) )//SF 7
	{//SF
	    return GAS_STATION+6;//24
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -1675.7146,413.1008,7.1797))//SF 8
	{//SF
	    return GAS_STATION+7;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1328.4802,2677.5134,50.0625))//Tierra Robada 9
	{//Between SF and LV
	    return GAS_STATION+8;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -1471.5114,1863.6404,32.6328))//Tierra Robada 10
	{//Between SF and LV
	    return GAS_STATION+9;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 70.3882,1218.6783,18.8120))//BONE COUNTY 11
	{//Between SF and LV
	    return GAS_STATION+10;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 10.0, 608.5040,1700.0131,6.9922)//BONE COUNTY 12.1
	|| IsPlayerInRangeOfPoint(playerid, 10.0, 618.5759,1685.0409,6.9922))//BONE COUNTY 12.2
	{//Between SF and LV
	    return GAS_STATION+11;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 2639.8977,1106.6787,10.8203))//LV 13
	{//LV
	    return GAS_STATION+12;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 2202.0935,2474.4866,10.8203))//LV 14
	{//LV
	    return GAS_STATION+13;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 2147.4282,2748.4614,10.8203))//LV 15
	{//LV
	    return GAS_STATION+14;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 2114.5981,920.6873,10.8203))//LV 16
	{//LV
	    return GAS_STATION+15;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 1596.0123,2199.2844,10.8203))//LV 17
	{//LV
	    return GAS_STATION+16;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 1380.9836,456.6337,20.1462))//RED COUNTY 18
	{//Between LV and LS
	    return GAS_STATION+17;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 652.2394,-565.2609,16.3359)
	|| IsPlayerInRangeOfPoint(playerid, 8.0, 659.3037,-564.9469,16.3359) )//RED COUNTY 19
	{//Between LV and LS
	    return GAS_STATION+18;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 30.0,406.9748,2449.5771,17.9000))//Zone51 Aero
	{
	    return GAS_STATION+19;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 30.0,1581.8795,1181.0317,12.2125))//LV Aero
	{
	    return GAS_STATION+20;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 30.0,-1436.8766,-526.8726,15.6719) ||
		IsPlayerInRangeOfPoint(playerid, 30.0,-1363.9728,-489.1934,15.6719))//SF Aero
	{
	    return GAS_STATION+21;
	}
	return 0;
}

stock fuel_OnPlayerConnect(playerid)
{
	gNoFuel[nCarID[playerid]] = 0;
	GasCounter[playerid] = 0;
	CostFuel[playerid] = 0;
	gRefueling[playerid] = 0;
}



//stock InGasStationPickUp(playerid)
stock fuel_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	for(new sb = GAS_STATION; sb < PARKING; sb++)//для информации по компаниям
	{//если это заправка
		if(!IsPlayerInRangeOfPoint(playerid, 3.0,
			SBizInfo[sb][sbEntranceX],
			SBizInfo[sb][sbEntranceY],
			SBizInfo[sb][sbEntranceZ])) continue;
	    if(SBizInfo[sb][sbProducts] <= 19 && !gRealWar)
	    {
			GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~GasStation", 5000, 1);
	    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
	    	break;
		}
	   	//new Float: FillUp = 20.0;
	   	FillUp = 20.0;
		if(PlayerInfo[playerid][pFuel] >= 9)
		{
	        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть 9 Канистр Топлива на 20 л. !");
	        break;
		}
		CostFuel[playerid] = floatround(FillUp * FuelCost*(100+SBizInfo[ IsAtGasStation(playerid) ][sbSellProd])/100.0, floatround_ceil);//литры * стоимость 1 литра * процент продажи = стоимость заправки
		if(GetPlayerMoneyH(playerid) < CostFuel[playerid]+4)
		{
			format(strings, sizeof(strings), "   У вас не хватает $%d на %.0f л топлива по цене $%.0f за литр",
				CostFuel[playerid]+4, FillUp, FuelCost*(100+SBizInfo[ IsAtGasStation(playerid) ][sbSellProd])/100.0 );
		    SendClientMessage(playerid, COLOR_GREY, strings);
		    break;
		}
		GivePlayerMoneyH(fsbiz+sb, playerid, -CostFuel[playerid]);
	    PlayerInfo[playerid][pFuel] += 1;//floatround(FillUp);
		SBizInfo[sb][sbProducts] -= floatround(FillUp);
		//OnGangsExtortionSBiz(sb, CostFuel);

	    format(strings, sizeof(strings), "* Вы купили Канистру с 20л Топлива за $%d", CostFuel[playerid]);
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		break;
	}
}


stock fuel_VehicleEnterPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	if(!IsAtGasStation(playerid)) return 1;
//если вы подобрали пикап в координатах по АЗС
   	if(gRefueling[playerid] != 0) return 1;
	//if(VehInfo[nCarID[playerid]][cFuel] < 90.0*VehicleArray[nCarModel[playerid]-400][GasMax]/100.0)
	//if(floatcmp(VehInfo[nCarID[playerid]][cFuel], (90.0*VehicleArray[nCarModel[playerid]-400][GasMax]/100.0)) < 0)
	//{   //если уровень топлива меньше 90 %
    if(SBizInfo[IsAtGasStation(playerid)][sbProducts] <= 0 && !gRealWar)
    {
		GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~GasStation", 5000, 1);
    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
    	return 1;
	}
	if( IsAtGasStation(playerid) >= GAS_STATION+19 && IsAtGasStation(playerid) <= GAS_STATION+21 )
	{
		if( IsInPlane(nCarID[playerid]) ) gRefueling[playerid] = 1;//поднимаем флаг для включения таймера
	}
	else
	{
	    SetPVarInt(playerid, "GasStationPickUp", pickupid);
 		TogglePlayerControllableEx(playerid, 0);//игрок НЕ сможет двигаться
 		gRefueling[playerid] = 1;//поднимаем флаг для включения таймера
//определяем сколько надо залить до того как начнёт работать таймер
		FillUp = floatsub(VehicleArray[nCarModel[playerid]-400][GasMax], VehInfo[nCarID[playerid]][cFuel]);//сколько влезет

 		TextDrawSetStringEx(txdAdvisor[7], RusToGame("Заправочная станция"));
		TextDrawHideForPlayer(playerid, txdAdvisor[8]);
		TextDrawHideForPlayer(playerid, txdAdvisor[8]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][8]);
		
		TextDrawHideForPlayer(playerid, txdAdvisor[9]);
  		TextDrawSetStringEx(txdAdvisor[9], RusToGame("Цена за литр:"));
		TextDrawBoxColor(txdAdvisor[9], 0x00000000);
		TextDrawShowForPlayer(playerid, txdAdvisor[9]);
		
		TextDrawHideForPlayer(playerid, txdAdvisor[10]);
  		TextDrawSetStringEx(txdAdvisor[10], RusToGame("Литров:"));
  		TextDrawBoxColor(txdAdvisor[10], 0x00000000);
  		TextDrawShowForPlayer(playerid, txdAdvisor[10]);

		TextDrawHideForPlayer(playerid, txdAdvisor[11]);
  		TextDrawSetStringEx(txdAdvisor[11], RusToGame("Стоимость:"));
  		TextDrawBoxColor(txdAdvisor[11], 0x00000000);
  		TextDrawShowForPlayer(playerid, txdAdvisor[11]);
  		
  		
		//new Float: PricePerLiter = FuelCost*(100.0+SBizInfo[sbiz][sbSellProd])/100.0;//стоимость 1 литра * процент продажи(выше цены покупки) = стоимость заправки
		new strtmp[11+10];
		format(strtmp, sizeof(strtmp), "%.1f $", FuelCost);
  		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][9], strtmp);
  		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][10], "0");
  		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][11], "0 $");
  		
		TextDrawShowForPlayer(playerid, txdAdvisor[5]);
		
    	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][12], RusToGame("Чтобы заглушить двигатель, нажмите 2"));// "#KEY_SUBMISSION"
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][13]);
  		TextDrawSetStringEx(txdAdvisor[12], RusToGame("Чтобы начать заправку, ЗАжмите Y"));//#KEY_YES".
  		TextDrawSetStringEx(txdAdvisor[13], RusToGame("Заправить полный бак"));

		if( IsPlayerNPC(playerid) ) return 1;
		if(nCarID[playerid] < 1) { return 1; }
		if(nCarModel[playerid] < 400) { return 1; }
		if( IsInNPCVehicle(nCarID[playerid]) ) { return 1; }
		if(IsInBoat(nCarID[playerid])) { return 1; }
		if(IsInIntCar(nCarID[playerid])) { return 1; }
		if(VehicleArray[nCarModel[playerid]-400][Category] == Rail_Transport) { return 1; }
		if(VehicleArray[nCarModel[playerid]-400][Category] == Bicycle) { return 1; }
		if(nCarModel[playerid] == 485) { return 1; }

//format(strtmp, sizeof(strtmp), "FillUp %.1f л", FillUp);
//SendClientMessage(playerid, COLOR_LIGHTBLUE, strtmp);
 		
 		FillingTimer[playerid] = SetTimerEx("OnVehicleFilling", 100, 1, "ii", playerid, nCarID[playerid]);//запускается постоянно каждые 100 мc до уничтожения
	}
	//}
	return 1;
}


stock fuel_OnPlayerLeavePickUp(playerid, pickupid)
{//возвращаем назад значения и цвета ТД
	if(pickupid != GetPVarInt(playerid, "GasStationPickUp")) return 1;

 	TextDrawSetStringEx(txdAdvisor[7], RusToGame("Текущее задание"));
	TextDrawShowForPlayer(playerid, txdAdvisor[8]);
	PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][8]);
	
 	TextDrawSetStringEx(txdAdvisor[9], RusToGame("Пункт назначения"));
	TextDrawBoxColor(txdAdvisor[9], 505290495);
	
	TextDrawHideForPlayer(playerid, txdAdvisor[9]);
 	TextDrawSetStringEx(txdAdvisor[9], RusToGame("Куда:"));
	TextDrawBoxColor(txdAdvisor[9], 505290495);
	TextDrawShowForPlayer(playerid, txdAdvisor[9]);

	TextDrawHideForPlayer(playerid, txdAdvisor[10]);
	TextDrawSetStringEx(txdAdvisor[10], RusToGame("Осталось"));
	TextDrawBoxColor(txdAdvisor[10], 673720575);
  	TextDrawShowForPlayer(playerid, txdAdvisor[10]);


	TextDrawHideForPlayer(playerid, txdAdvisor[11]);
	TextDrawSetStringEx(txdAdvisor[11], RusToGame("Доход"));
	TextDrawBoxColor(txdAdvisor[11], 505290495);
	TextDrawShowForPlayer(playerid, txdAdvisor[11]);

	//PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][9], RusToGame("ЛОС-Хантос - Пляж"));
	//PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][10], RusToGame("18 ч 18 мин"));
	//PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][11], "4 182 $");
	TextDrawHideForPlayer(playerid, txdAdvisor[5]);
   	//PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][12], RusToGame("ETA: Ср 2:30, 102 км, 1 ч 53 мин"));// "#KEY_SUBMISSION"
	PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][13]);
	TextDrawSetStringEx(txdAdvisor[12], RusToGame("Остановка для отдыха"));//#KEY_YES".
	TextDrawSetStringEx(txdAdvisor[13], RusToGame("Отменить текущее задание"));
	return 1;
}


stock fuel_OneSecondTimers(playerid)
{
	if( AFK_IdleTime[playerid] >= 3) return 1;
	/*if(gRefueling[playerid] == 1)//поднимается командой /fill /refill или при заезде в зону заправки
    {
    	OnVehicleFilling(playerid, nCarID[playerid]);//вызывается по команде fill через 5 сек 1 раз
    }*/
 	//==========================================================================
   	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
   	{//сначало лёгкие проверки
 		if(	gRefueling[playerid] == 0 && IsInPlane(nCarID[playerid]) &&
		 	IsAtGasStation(playerid) == GAS_STATION+21)
		{   //АЗС для самалётов
			//if(VehInfo[nCarID[playerid]][cFuel] < 90.0*VehicleArray[nCarModel[playerid]-400][GasMax]/100.0)
			if(floatcmp(VehInfo[nCarID[playerid]][cFuel], (90.0*VehicleArray[nCarModel[playerid]-400][GasMax]/100.0)) < 0)
			{   //если уровень топлива меньше 90
			    if(SBizInfo[IsAtGasStation(playerid)][sbProducts] <= 0 && !gRealWar)
			    {
					GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~GasStation", 5000, 1);
			    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			    	return 1;
				}
				gRefueling[playerid] = 1;//поднимаем флаг для включения таймера
			}
		}
	}
	return 1;
}


stock FuelAllCars()//Обнаружено длительное выполнение обратного вызова (зависание или проблема производительности)
{
	/*if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6 && PlayerInfo[playerid][pAdmin] != 9)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
	    return 1;
	}
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /fuelallcars [percent]");
		return 1;
	}
	if(strval(tmp) < 5 || strval(tmp) > 100)
	{
		SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /fuelallcars [percent(5-100 %%)]");
		return 1;
	}*/
	//new percent = strval(tmp);
	//for(new c=1; c<=GetMaxVehicles; c++)
	for(new carid = GetVehiclePoolSize(); carid > 0; carid--)//Gets the highest vehicleid currently in use on the server.
//GetMaxVehicles перезаписывается при создании тачек, если тачка создана другим скриптом, то работать не будет
	{
		if(!IsValidVehicle(carid)) continue;//создано ли транспортное средство.
    	if(VehInfo[carid][cModel] < 400) continue;
    	//if(VehInfo[c][cFuel] <= 1.0) continue;
    	//if(floatcmp(VehInfo[c][cFuel], 1.0) <= 0)
		VehInfo[carid][cFuel] = float(VehicleArray[VehInfo[carid][cModel]-400][GasMax]);
  		/*if(percent == 100) VehInfo[c][cFuel] = VehicleArray[GetVehicleModel(c)-400][GasMax];
		else*/
		//VehInfo[c][cFuel] = percent*VehicleArray[VehInfo[c][cModel]-400][GasMax]/100.0;
	}
	//format(strings, sizeof(strings), "AdmCmd: %s All cars filled with Fuel on the %d%%\%%", PlayerName(playerid), percent);
	//format(strings, sizeof(stringsd), "%s[%d]: Все автомобили заправлены на %d%%\%%", PlayerName(playerid), playerid, percent);
	//Log(ADMINLOG, strcmd);
	//SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
	SendClientMessageToAll(COLOR_LIGHTBLUE, "Все автомобили заправлены");
	return 1;
}

//##############################################################################//
//                                                                              //
//                            СИСТЕМА РАСХОДА ТОПЛИВА                           //
//                                                                              //
//##############################################################################//
//НАЧАЛО РАСЧЁТА ТОПЛИВА
//Вариант 1: чем выше скорость тем больше расход
//для расхода топлива
//<20:38:49> "SNap": Золотые ворота - 1.600 (мир) Гант - 650 (игра)
//<20:46:31> "SNap": 1 = 2.4
//VehicleArray[nCarModel[playerid]-400][fuelConsumption] /1000 - расход на 1 метр
// 0.176 л за мост.
//stock FuelConsumption(playerid, Float: distance)
stock fuel_FuelConsumption(playerid, Float: distance)
{   //вызывается из AntiTeleportTimer //Odometer(playerid)
//каждую секунду подаём сведения о пройдённом пути
	if( IsPlayerNPC(playerid) ) return 1;
	if(nCarID[playerid] < 1) return 1;
	if(gNoFuel[nCarID[playerid]] == 1) return 1;//if(gNoFuel[playerid] == 1) return 1;//чтобы не было повторного вывода инфы, что бак пуст
    if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
	if(CarStatus[nCarID[playerid]][st_engine] != VEHICLE_PARAMS_ON) return 1;
	//if( IsInNPCVehicle(nCarID[playerid]) ) return 1;
	if(IsInBoat(nCarID[playerid])) return 1;
	if(IsInIntCar(nCarID[playerid])) return 1;

	if(nCarModel[playerid] < 400) return 1;
	if(VehicleArray[nCarModel[playerid]-400][Category] == Rail_Transport) return 1;
	if(VehicleArray[nCarModel[playerid]-400][Category] == Bicycle) return 1;
	if(nCarModel[playerid] == 485) return 1;//{485,	"Baggage_Handler",	Lorries,	None,	34542,	None,	55,	80,	4,	100,	0,	10000},
	if(VehicleArray[nCarModel[playerid]-400][Category] == Scooter) return 1;

   	if(floatcmp(VehInfo[nCarID[playerid]][cFuel], 0.0) > 0)
	{
		gNoFuel[nCarID[playerid]] = 0; //gNoFuel[playerid] = 0;
	    if(floatcmp(VehInfo[nCarID[playerid]][cFuel], (10.0*VehicleArray[nCarModel[playerid]-400][GasMax]/100.0)) <= 0)
		{ PlaySoundForPlayer(playerid, SOUND_ROULETTE_REMOVE_CASH); }

		VehInfo[nCarID[playerid]][cFuel] = floatsub(VehInfo[nCarID[playerid]][cFuel], (distance*VehicleArray[nCarModel[playerid]-400][fuelConsumption]/(RealMeter*1000.0)));
		//дистанция * расход(л на сотню) / 100 км = литров
		//но у нас домножается на 1000 для реалистичности
		//RealMeter = 2.5
		//отнимаем по долям литра, т.к. если округлять до литра будет быстро кончатся
	}
	else //if(VehInfo[nCarID[playerid]][cFuel] < 1.0)//если топлива нет
   	{
   		VehInfo[nCarID[playerid]][cFuel] = 0.0;//откоректировали
       	gNoFuel[nCarID[playerid]] = 1;//gNoFuel[playerid] = 1;
		SendClientMessage(playerid, COLOR_GREY, "   Топливный Бак пуст (USE: /service mechanic).");
 		SetVehicleParams(nCarID[playerid],//playerid,
			VEHICLE_PARAMS_OFF,
			CarStatus[nCarID[playerid]][st_lights],
			CarStatus[nCarID[playerid]][st_alarm],
			CarStatus[nCarID[playerid]][st_doors],
			CarStatus[nCarID[playerid]][st_bonnet],
			CarStatus[nCarID[playerid]][st_boot],
			CarStatus[nCarID[playerid]][st_objective]);
		new msgitem[170+MAX_PLAYER_NAME];
	    if(PlayerInfo[playerid][pFuel] > 0)//если в канистру залито 20 л топлива
	    {
			format(msgitem, sizeof(msgitem), "%s\nВаш топливный Бак пуст.\nНадо было вовремя заправлять!\
											\nНажмите FillCar, чтобы залить топливо из канистры.\
											\nИли нажмите Mechanic, чтобы вызвать механика.", PlayerName(playerid));
		}
		else
		{
			format(msgitem, sizeof(msgitem), "%s\nВаш топливный Бак пуст.\nНадо было вовремя заправлять!\
											\nУ Вас нет с собой канистры.\
											\nНажмите Mechanic, чтобы вызвать механика.\
											\nПожалуйста ожидайте ответ Диспетчера.", PlayerName(playerid));
		}
		//ShowPlayerDialogGap(playerid, NOFUEL_DIALOG, DIALOG_STYLE_MSGBOX, "No fuel in Vehicle", msgitem, "FillCar", "Mechanic");
		ShowPlayerDialogEx(playerid, NOFUEL_DIALOG, DIALOG_STYLE_MSGBOX, "No fuel in Vehicle", msgitem, "FillCar", "Mechanic");
	}
	return 1;
}

stock FillCar(playerid)
{   //вызывается по команде /fillcar
	//if(gLoading[playerid]) return 1;
	//if(gUnLoading[playerid]) return 1;
   	if(!IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
		return 1;
	}
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
		return 1;
	}
    /*if(PlayerCuffed[playerid] < MAX_PLAYERS-1)
    {
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете заправлять автомобиль когда у вас надеты наручники !");
        return 1;
    }*/
	/*if(PlayerTied[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете заправлять автомобиль когда связаны !");
		return 1;
	}*/

    if(PlayerInfo[playerid][pFuel] <= 0)//если в канистре есть топливо
    {
		SendClientMessage(playerid, COLOR_GREY, "   У Вас не осталось Канистр с Топливом!");
		return 1;
	}
	//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку
	nCarID[playerid] = GetPlayerVehicleID(playerid);
	nCarModel[playerid] = VehInfo[nCarID[playerid]][cModel];//GetVehicleModel(nCarID[playerid]);
	if(	//HireCarID[playerid] == MAX_VEHICLES-1  &&
		IsInRentCar(nCarID[playerid]) )
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы не можете Заправлять автомобиль проката, пока не оплатите аренду!");
		return 1;
	}
/*Examples:
floatcmp(2.0, 2.0) ->  0
floatcmp(1.0, 2.0) -> -1
floatcmp(2.0, 1.0) ->  1*/
	//gNoFuel[nCarID[playerid]] = 0; //gNoFuel[playerid] = 0;
	//if( VehInfo[nCarID[playerid]][cFuel] >= VehicleArray[nCarModel[playerid]-400][GasMax] )
	if(nCarModel[playerid] == 485)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Данный автомобиль использует электродвигатель. Заправка не требуется !");
		return 1;
	}
	if( floatcmp(VehInfo[nCarID[playerid]][cFuel], VehicleArray[nCarModel[playerid]-400][GasMax]) >= 0 )
	{//floatcmp
		SendClientMessage(playerid, COLOR_GREY, "  Бак автомобиля полный !");
		VehInfo[nCarID[playerid]][cFuel] = float(VehicleArray[nCarModel[playerid]-400][GasMax]);
		return 1;
	}
   	//new Float: FillUp = VehicleArray[nCarModel[playerid]-400][GasMax] - 20;//VehInfo[nCarID[playerid]][cFuel];
  	FillUp = VehicleArray[nCarModel[playerid]-400][GasMax] - 20;//VehInfo[nCarID[playerid]][cFuel];
	//отнимаем от максимального текущее значение топлива, чтобы найти сколько надо долить до краев
	//new strings[MAX_STRING];
	//if(FillUp > PlayerInfo[playerid][pFuel])//20.0
	//if(floatcmp(FillUp, PlayerInfo[playerid][pFuel]) > 0)
	if(floatcmp(FillUp, 20) > 0)
	{//если надо залить больше чем есть в канистре, то выливаем всю канистру
		VehInfo[nCarID[playerid]][cFuel] = floatadd(VehInfo[nCarID[playerid]][cFuel], 20);//PlayerInfo[playerid][pFuel]
		format(strings, sizeof(strings), "   Bы залили в бак Вашего Автомобиля(ID: %d) 20л Топлива из Канистры.", nCarID[playerid]);//, PlayerInfo[playerid][pFuel]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		PlayerInfo[playerid][pFuel] -= 1;//0;
	}
	else
	{
		VehInfo[nCarID[playerid]][cFuel] = float(VehicleArray[nCarModel[playerid]-400][GasMax]);
		PlayerInfo[playerid][pFuel] -= 1;//floatround(FillUp);
		format(strings, sizeof(strings), "   Bы залили в бак Вашего Автомобиля(%d) 20л Топлива из Канистры.", nCarID[playerid]);//, FillUp);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	gRefueling[playerid] = 0;
    TogglePlayerControllableEx(playerid, 1);
	return 1;
}

//для заправок

//stock OnVehicleFilling(playerid, vehicleid)//вызывается из секундного таймера OneSecondTimers
public OnVehicleFilling(playerid, vehicleid)
{   //для всех у кого gRefueling[playerid] == 1
 	if(gRefueling[playerid] == 0)//gStopVehicleFilling == 1)
	{//закончили заправку
		//gStopVehicleFilling = 0;
  		gGameText[playerid] = 0;
		GasCounter[playerid] = 0;
		CostFuel[playerid] = 0;
		gNoFuel[nCarID[playerid]] = 0;//gNoFuel[playerid] = 0;//опустили флаг - окончили заправку
		if( !IsInPlane(vehicleid) ) TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться
		KillTimer(FillingTimer[playerid]); FillingTimer[playerid] = -1;
		return 1;
	}

	new sbiz = IsAtGasStation(playerid);
	if( !IsPlayerInAnyVehicle(playerid) || sbiz == 0 )
	{//если вышел из машины или съехал с заправки
		gRefueling[playerid] = 0;//опустили флаг - окончили заправку
		return 1;
	}
	if(SBizInfo[sbiz][sbProducts] <= 0)
	{//если закончились продукты
 		gRefueling[playerid] = 0;//опустили флаг - окончили заправку
		GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~GasStation", 5000, 1);
		PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		return 1;
	}

	//nCarID[playerid] = GetPlayerVehicleID(playerid);
	//vehicleid = nCarID[playerid];
	//nCarModel[playerid] = VehInfo[nCarID[playerid]][cModel];//GetVehicleModel(nCarID[playerid]);


	/*if(SBizInfo[sbiz][sbProducts] < floatround(FillUp))
	{
  		gGameText[playerid] = 0;
		GasCounter[playerid] = 0;
		gNoFuel[nCarID[playerid]] = 0;//gNoFuel[playerid] = 0;//опустили флаг - окончили заправку
		gRefueling[playerid] = 0;//опустили флаг - окончили заправку
		if( !IsInPlane(vehicleid) ) TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться
		KillTimer(FillingTimer[playerid]); FillingTimer[playerid] = -1;
    	SendClientMessage(playerid, COLOR_GREY, "   Не достаточное кол-во топлива на АЗС, чтобы заправить ваш транспорт!");
		return 1;
	}*/

 	//--------------------------------------------------------------------------
	//if(	GasCounter[playerid] == 1 || GasCounter[playerid] == 3 ||
	//	GasCounter[playerid] == 5) PlaySoundForPlayer(playerid, SOUND_BUY_CAR_RESPRAY);//звук спрэя
	//if( IsEvenNumber(GasCounter[playerid]) ) PlayAudioStreamForPlayerEx(playerid, "refuel.wav");

	//gGameText[playerid] = 1;
	//SetPlayerGameTextScale(playerid, "Re-Fueling Vehicle", GasCounter[playerid], floatround(FillUp));

	new Float: PricePerLiter = FuelCost*(100.0+SBizInfo[sbiz][sbSellProd])/100.0;//стоимость 1 литра * процент продажи(выше цены покупки) = стоимость заправки
	new strtmp[11+10];
	format(strtmp, sizeof(strtmp), "%.1f $", PricePerLiter);
  	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][9], strtmp);//цена за литр
	GasCounter[playerid] ++;

	VehInfo[vehicleid][cFuel] = floatadd(VehInfo[vehicleid][cFuel], 1);
	
	PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][1]);
	PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][1], 15, -floatround(VehInfo[nCarID[playerid]][cFuel]*12.0/VehicleArray[nCarModel[playerid]-400][GasMax]) );
	PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][1]);
	format(strtmp, sizeof(strtmp), "%.0f %s", VehInfo[nCarID[playerid]][cFuel], RusToGame("л"));
	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][6], strtmp);
	
	//strmid(strtmp, GasCounter[playerid], 0, 10, sizeof(strtmp));
	format(strtmp, sizeof(strtmp), "%d %s", GasCounter[playerid], RusToGame("л"));
  	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][10], strtmp);

	//new CostFuel = FillUp * SBizInfo[3][sbEntranceCost];//литры * стоимость 1 литра = стоимость заправки
	//new CostFuel = floatround(FillUp * (FuelCost*(100+SBizInfo[IsAtGasStation(playerid)][sbSellProd])/100.0));//литры * стоимость 1 литра * процент продажи = стоимость заправки
	CostFuel[playerid] = floatround(GasCounter[playerid] * PricePerLiter);//литры * стоимость 1 литра * процент продажи = стоимость заправки
	format(strtmp, sizeof(strtmp), "%d $", CostFuel[playerid]);
  	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][11], strtmp);

   	if(GetPlayerMoneyH(playerid) < CostFuel[playerid])
   	{
   	    FillUp = GasCounter[playerid];
   		gRefueling[playerid] = 0;//gStopVehicleFilling = 1;
   		//new strings[MAX_STRING];
   	    //format(strings, sizeof(strings), "   Нет денег для того, чтобы заправить машину. Необходимо $%d для заправки. ", CostFuel);
    	SendClientMessage(playerid, COLOR_GREY, "   Нет денег для того, чтобы заправить полностью машину.");
      	//return 1;//чтобы прошла заправка
 	}
 	if(GasCounter[playerid] >= floatround(FillUp)) 	//if(GasCounter[playerid] > 7)
	{

		if(sbiz >= GAS_STATION+19 && sbiz <= GAS_STATION+21)
		{//параллелно чиним самолёты
			if( IsInPlane(vehicleid) ) RepairVehicleEx(playerid, vehicleid);
			//else { return 1; }
		}
		//VehInfo[vehicleid][cFuel] = floatadd(VehInfo[vehicleid][cFuel], FillUp);//FillUp;//добавить к текущему значение топлива недостающую разницу
		GivePlayerMoneyH(fsbiz+sbiz, playerid, -CostFuel[playerid]);//отнимаем у игрока стоимость заправки

		SBizInfo[sbiz][sbProducts] -= floatround(FillUp);
		SBizInfo[sbiz][sbExport] += CostFuel[playerid];
		//OnGangsExtortionSBiz(sbiz, CostFuel);

		//new strtmp[42+8+10];//{FFFFFF}%s's{0080FF} по цене {33AA33}$%d
	    format(PagerMessage, sizeof(PagerMessage), "Плата за заправку на %.1f л. - $%d.", FillUp, CostFuel[playerid]);
	    SendPagerMessage(playerid);
	    //SendClientMessage(playerid, COLOR_LIGHTBLUE, strtmp);
	    //PlayerTextDrawSetStringEx(playerid, txdPager[playerid], RusToGame(strtmp));
		//PlayAudioStreamForPlayerEx(playerid, "pager.wav");
		
 		gRefueling[playerid] = 0;//опустили флаг - окончили заправку
	}
	return 1;
}




