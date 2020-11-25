new SpecialBleep[MAX_VEHICLES+1];//Специальный Звуковой сигнал
//##############################################################################//
//                                                                              //
//                          ИДЕНТИФИКАТОРЫ TEXTDRAWS                            //
//                                                                              //
//##############################################################################//

//------------------------------------------------------------------------------
//для спидометров
new //PlayerText:txdSpeedMark[MAX_PLAYERS],
	PlayerText:txdPositionOfTotal[MAX_PLAYERS],
	PlayerText:txdTaskTime[MAX_PLAYERS],
	PlayerText:txdInsurances[MAX_PLAYERS],
	PlayerText:txdSpeedBar[MAX_PLAYERS],
	PlayerText:txdMeterBar[MAX_PLAYERS],
	PlayerText:txdHealPercent[MAX_PLAYERS],
	PlayerText:txdFuelPercent[MAX_PLAYERS],
	//PlayerText:txdRADAR[MAX_PLAYERS],
	PlayerText:txdPager[MAX_PLAYERS],
	//PlayerText:txdCarIcon[MAX_PLAYERS],
	PlayerText:txdVehicleIcon[MAX_PLAYERS],
	PlayerText:txdTrailerIcon[MAX_PLAYERS];

new Text:txdSpeedBarMark,
	PlayerText:txdHealthBar[MAX_PLAYERS],
	PlayerText:txdFuelBar[MAX_PLAYERS],
	Text:txdHealthIcon,
	Text:txdFuelIcon,
	Text:txd_hbarl,
	Text:txd_hbarm,
	Text:txd_hbarr,
	Text:txd_hbarRadar,
	Text:txd_hbarPager,
	/*Text:txdMark0,
	Text:txdMark20,
	Text:txdMark40,
	Text:txdMark60,
	Text:txdMark80,
	Text:txdMark100,
	Text:txdMark120,
	Text:txdMark140,
	Text:txdMark160;*/
	Text:txdTablo,
	Text:txdTablo1,
	Text:txdTablo2,
	Text:txdTablo21,
	Text:txdTablo3,
	Text:txdTablo4;

//##############################################################################//
//                                                                              //
//                               ТРИГЕРЫ TEXTDRAWS                              //
//                                                                              //
//##############################################################################//
//дают разрешение на показ или скрытие
//всё время должны быть на false
new bool:gTextDrawShowSpeed[MAX_PLAYERS];
new bool:gTextDrawHideSpeed[MAX_PLAYERS];


//##############################################################################//
//                                                                              //
//                             ИНДИКАТОРЫ TEXTDRAWS                             //
//                                                                              //
//##############################################################################//
//new bool:TextDrawsShown[MAX_PLAYERS];
new bool:TextDrawShowSpeed[MAX_PLAYERS];//индикатор состояния текстдрова




//##############################################################################//
//для расхода топлива


stock speedometer_OnGameModeInit()
{
//для спидометров
//------------------------------------------------------------------------------
//нижний фон
#if defined samp03DL
	//txdTablo = TextDrawCreateEx(0.0, txd_Y, "ESC15:tablo");//"ESC15.txd"//так вызываем если текстура лежит в папке с игрой
	txdTablo = TextDrawCreateEx(0.0, txd_Y, "mdl-2004:tablo");//samp03DL_svr_R1_win32
	TextDrawFont(txdTablo, TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawTextSize(txdTablo, 640, 24);
#else//samp037svr_win32
	txdTablo = TextDrawCreateEx(0.0, txd_Y+4.0, "_");//Создать новый Text Draw в памяти сервера.
	TextDrawUseBox(txdTablo,1);//Определяет использование рамки. 1 - использовать, 0 - не использовать
	TextDrawBoxColor(txdTablo,0x2C2C2CFF);//Устанавливает цвет рамки
	//TextDrawAlignment(txdTablo,2);//Устанавливает смещение текста в Text Draw. ID смещения: 0 или 1 - влево, 2 - центр, 3 - вправо.
	TextDrawTextSize(txdTablo,640.0,0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).
	//TextDrawFont(txdTablo,1);//Изменяет шрифт текста. (0-3)
	TextDrawLetterSize(txdTablo,1.0,2.0);//Устанавливает ширину и высоту букв(рамки) в пикселях.
	TextDrawSetProportional(txdTablo,1);//Возможно устанавливает расстояние между буквами

//зеленая рамка
	txdTablo1 = TextDrawCreateEx((137.0),(txd_Y+4.0+2.0), "_");
	TextDrawUseBox(txdTablo1,1);
	TextDrawBoxColor(txdTablo1,0x687F57FF);
	TextDrawTextSize(txdTablo1,(0.0),0.0);
	TextDrawLetterSize(txdTablo1,1.0,1.6);

	txdTablo2 = TextDrawCreateEx(301.0,(txd_Y+4.0+2.0), "_");
	TextDrawUseBox(txdTablo2,1);
	TextDrawBoxColor(txdTablo2,0x687F57FF);
	//TextDrawAlignment(txdTablo2,2);//Устанавливает смещение текста в Text Draw. ID смещения: 0 или 1 - влево, 2 - центр, 3 - вправо.
	TextDrawTextSize(txdTablo2,(136.0),0.0);//136
	//TextDrawFont(txdTablo2,1);
	TextDrawLetterSize(txdTablo2,1.0,1.6);

	txdTablo21 = TextDrawCreateEx(370.0,430.0, "_");
	TextDrawUseBox(txdTablo21,1);
	TextDrawBoxColor(txdTablo21,0x687F57FF);
	TextDrawTextSize(txdTablo21,(300.0),0.0);
	TextDrawLetterSize(txdTablo21,1.0,1.6);

	txdTablo3 = TextDrawCreateEx(395.0,430.0, "_");
	TextDrawUseBox(txdTablo3,1);
	TextDrawBoxColor(txdTablo3,0x687F57FF);
	TextDrawTextSize(txdTablo3,(369.0),0.0);
	TextDrawLetterSize(txdTablo3,1.0,1.6);

	txdTablo4 = TextDrawCreateEx(640.0,430.0, "_");
	TextDrawUseBox(txdTablo4,1);
	TextDrawBoxColor(txdTablo4,0x687F57FF);
	TextDrawTextSize(txdTablo4,(394.0),0.0);
	TextDrawLetterSize(txdTablo4,1.0,1.0);//1.0,1.6
#endif



//------------------------------------------------------------------------------
	txd_hbarl = TextDrawCreateEx(20.0, 427.0, "Position");
	TextDrawLetterSize(txd_hbarl, 0.14, 0.7);
	TextDrawBackgroundColor(txd_hbarl, 0xFFFFFF66);
	TextDrawFont(txd_hbarl, 1);
	TextDrawColor(txd_hbarl, COLOR_TEXTDRAW);
	TextDrawSetOutline(txd_hbarl, 0);
	TextDrawSetShadow(txd_hbarl, 0);
	TextDrawAlignment(txd_hbarl, 2);

	txd_hbarm = TextDrawCreateEx(65.0, 427.0, "Time");
	TextDrawLetterSize(txd_hbarm, 0.14, 0.7);
	TextDrawBackgroundColor(txd_hbarm, 0xFFFFFF66);
	TextDrawFont(txd_hbarm, 1);
	TextDrawColor(txd_hbarm, COLOR_TEXTDRAW);
	TextDrawSetOutline(txd_hbarm, 0);
	TextDrawSetShadow(txd_hbarm, 0);
	TextDrawAlignment(txd_hbarm, 2);

	txd_hbarr = TextDrawCreateEx(113, 427.0, "Insurance");//(Checkpoints)
	TextDrawLetterSize(txd_hbarr, 0.14, 0.7);
	TextDrawBackgroundColor(txd_hbarr, 0xFFFFFF66);
	TextDrawFont(txd_hbarr, 1);
	TextDrawColor(txd_hbarr, COLOR_TEXTDRAW);
	TextDrawSetOutline(txd_hbarr, 0);
	TextDrawSetShadow(txd_hbarr, 0);
	TextDrawAlignment(txd_hbarr, 2);

	txdSpeedBarMark = TextDrawCreateEx(167.0, 435.0, "km/h");
	TextDrawLetterSize(txdSpeedBarMark, 0.14, 0.7);
	TextDrawBackgroundColor(txdSpeedBarMark, 0xFFFFFF66);
	TextDrawFont(txdSpeedBarMark, 1);
	TextDrawColor(txdSpeedBarMark, COLOR_TEXTDRAW);
	TextDrawSetOutline(txdSpeedBarMark, 0);
	TextDrawSetShadow(txdSpeedBarMark, 0);
	TextDrawLetterSize(txdSpeedBarMark,  0.25, 0.85);//0.2, 0.7);

	txdHealthIcon = TextDrawCreateEx(248.0, 435.0, "meters");
	TextDrawLetterSize(txdHealthIcon, 0.14, 0.7);
	TextDrawBackgroundColor(txdHealthIcon, 0xFFFFFF66);
	TextDrawFont(txdHealthIcon, 1);
	TextDrawColor(txdHealthIcon, COLOR_TEXTDRAW);
	TextDrawSetOutline(txdHealthIcon, 0);
	TextDrawSetShadow(txdHealthIcon, 0);
	TextDrawLetterSize(txdHealthIcon,  0.25, 0.85);//0.2, 0.7);

//иконка АЗС
    txdFuelIcon = TextDrawCreateEx(337.0, 429.0, " ");
    TextDrawFont(txdFuelIcon, TEXT_DRAW_FONT_MODEL_PREVIEW);
	TextDrawBackgroundColor(txdFuelIcon, 0x00000000);
	TextDrawTextSize(txdFuelIcon, 14.0, 14.0);
	TextDrawSetPreviewModel(txdFuelIcon, 1676);
    TextDrawSetPreviewRot(txdFuelIcon, 0.0, 0.0, 0.0);


	txd_hbarRadar = TextDrawCreateEx(382.0, 429.0, "Radar");
	TextDrawLetterSize(txd_hbarRadar, 0.14, 0.7);
	TextDrawBackgroundColor(txd_hbarRadar, 0xFFFFFF66);
	TextDrawFont(txd_hbarRadar, 1);
	TextDrawColor(txd_hbarRadar, COLOR_TEXTDRAW);
	TextDrawSetOutline(txd_hbarRadar, 0);
	TextDrawSetShadow(txd_hbarRadar, 0);
	TextDrawAlignment(txd_hbarRadar, 2);


	txd_hbarPager = TextDrawCreateEx(417.0, 425.0, "Pager");
	TextDrawLetterSize(txd_hbarPager, 0.14, 0.7);
	TextDrawBackgroundColor(txd_hbarPager, 0xFFFFFF66);
	TextDrawFont(txd_hbarPager, 1);
	TextDrawColor(txd_hbarPager, COLOR_TEXTDRAW);
	TextDrawSetOutline(txd_hbarPager, 0);
	TextDrawSetShadow(txd_hbarPager, 0);
	TextDrawAlignment(txd_hbarPager, 2);
	TextDrawColor(txd_hbarPager, 0xFFFFFFFF);
}



stock CreateSpeedometer(playerid)//для информационной панели начало
{   //вызывается из speedometer_OnPlayerConnect
//после txdTablo
	//здоровье тачки
	txdHealthBar[playerid] = CreatePlayerTextDraw(playerid, 321.0, 442.0, "LD_DUAL:health");
	PlayerTextDrawFont(playerid, txdHealthBar[playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawColor(playerid, txdHealthBar[playerid], 0xFFFFFFFF);
	PlayerTextDrawTextSize(playerid, txdHealthBar[playerid], 15, -12);//4, -90);
	PlayerTextDrawAlignment(playerid, txdHealthBar[playerid], 1);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	//топливо
	txdFuelBar[playerid] = CreatePlayerTextDraw(playerid, 349.0, 442.0, "LD_DUAL:power");
	PlayerTextDrawFont(playerid, txdFuelBar[playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawColor(playerid, txdFuelBar[playerid], 0xFFFFFFFF);
	PlayerTextDrawTextSize(playerid, txdFuelBar[playerid], 15, -12);//4, -90);
	PlayerTextDrawAlignment(playerid, txdFuelBar[playerid], 1);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
//но перед
	/*txdCarIcon[playerid] = CreatePlayerTextDraw(playerid, 303.0, 420.0, " ");
    PlayerTextDrawFont(playerid, txdCarIcon[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawBackgroundColor(playerid, txdCarIcon[playerid], 0x00000000);
	PlayerTextDrawTextSize(playerid, txdCarIcon[playerid], 26.0, 32.0);
	PlayerTextDrawSetPreviewVehCol(playerid, txdCarIcon[playerid], 6, 9);
    PlayerTextDrawSetPreviewRot(playerid, txdCarIcon[playerid], 0.0, 0.0, 30.0);//0.0, 0.0, 0.0);
	PlayerTextDrawSetPreviewModel(playerid, txdCarIcon[playerid], 403);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;*/

	txdTrailerIcon[playerid] = CreatePlayerTextDraw(playerid, 270.0, 418.0, " ");
    PlayerTextDrawFont(playerid, txdTrailerIcon[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawBackgroundColor(playerid, txdTrailerIcon[playerid], 0x00000000);
	PlayerTextDrawTextSize(playerid, txdTrailerIcon[playerid], 39.0, 39.0);// Text size is the Width:Height
    PlayerTextDrawSetPreviewVehCol(playerid, txdTrailerIcon[playerid], 1, 1); // Set the Linerunner to have colour 6 (Yellow)
    PlayerTextDrawSetPreviewRot(playerid, txdTrailerIcon[playerid], 0.0, 0.0, 30.0);//0.0, 0.0, 270.0);
	PlayerTextDrawSetPreviewModel(playerid, txdTrailerIcon[playerid], 435); // Display model 403 (Linerunner)
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

	txdVehicleIcon[playerid] = CreatePlayerTextDraw(playerid, 303.0, 420.0, " ");
    PlayerTextDrawFont(playerid, txdVehicleIcon[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawBackgroundColor(playerid, txdVehicleIcon[playerid], 0x00000000);
	PlayerTextDrawTextSize(playerid, txdVehicleIcon[playerid], 26.0, 32.0);
	PlayerTextDrawSetPreviewVehCol(playerid, txdVehicleIcon[playerid], 6, 9);
    PlayerTextDrawSetPreviewRot(playerid, txdVehicleIcon[playerid], 0.0, 0.0, 30.0);//0.0, 0.0, 0.0);
	PlayerTextDrawSetPreviewModel(playerid, txdVehicleIcon[playerid], 403);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

}



//stock SystemConsuptionFuel(playerid)//счётчик метража
stock Odometer(playerid)//счётчик метража
{
	//if(spectateid[playerid] != MAX_PLAYERS-1) return 1;
	//if( GetPVarInt(playerid, "gStatusRegistration") ) return 1;
	//if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount")) return 1;
    //new speed;
   	new carid = nCarID[playerid];
    new Float: distance, Float:x,Float:y,Float:z;
    //new curstate = CurState[playerid];
	//if(!IsPlayerInAnyVehicle(playerid)) return 1;
	//if(curstate != PLAYER_STATE_DRIVER) return 1;

	// && LastState[playerid] == PLAYER_STATE_DRIVER

//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку
	//nCarID[playerid] = GetPlayerVehicleID(playerid);
//в момент выхода  GetPlayerVehicleID(playerid); возвращает ноль и соответственно координаты 0.0
    GetVehiclePos(carid,x,y,z);//должны постоянно считываться
	//distance = floatsqroot( floatpower(floatsub(x,CurPos[0][playerid]),2)
	//			 + floatpower(floatsub(y,CurPos[1][playerid]),2) );
	distance = GetVehicleDistanceFromPoint(carid, VehPos[carid][0], VehPos[carid][1], VehPos[carid][2]);
	//new value = floatround(distance/1000*3600);//скорость = расстояние / время(час)
	//предыдущая скорость
   	//speed = GetVehicleSpeed(nCarID[playerid]);//мгновенная скорость
	//new Float:maxDist = VehicleArray[nCarModel[playerid]-400][Speed]/2+35;
	if(VehInfo[carid][cDist] >= 9999999) VehInfo[carid][cDist] = 0;
	else
	{
		VehInfo[carid][cDist] += floatround(distance);
#if defined vw_fuel
		fuel_FuelConsumption(playerid, distance);//система расхода топлива
#endif

	}
	VehPos[carid][0] = x;
	VehPos[carid][1] = y;
	VehPos[carid][2] = z;
}


/*stock speedometer_OnDialogResponse(playerid)
{
	new carid = nCarID[playerid];
    if(CarStatus[carid][st_engine] == VEHICLE_PARAMS_ON)
    {
		gTextDrawHideSpeed[playerid] = true;
	}
    else
    {//если двигатель выключен
  		gTextDrawShowSpeed[playerid] = true;
	}
}*/

///тяжёлая ф-ия = 381 ms
//stock OnPlayerSpeedTimer(playerid)//для информационной панели начало
stock speedometer_OneSecondTimers(playerid)
{//!IsPlayerInAnyVehicle(playerid) ||
    //if(gHide[playerid] == 0) return 1;
    //if(TextDrawShowSpeed[playerid] == false) return 1;
    if(!IsPlayerInAnyVehicle(playerid)) return 1;
    //if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;

	new timers = GetTickCount();
	new strtmp[71+2+2];
//==============================================================================
//РАСТОЯНИЕ
    Odometer(playerid);
//ЗДОРОВЬЕ
	GetVehicleHealth(nCarID[playerid], VehHealth[nCarID[playerid]]);
	new VehicleHealth = floatround(VehHealth[nCarID[playerid]]/10.0);
//СКОРОСТЬ
	new velocity = GetVehicleSpeed(nCarID[playerid]);
//==============================================================================
    if(gHide[playerid] == true && TextDrawShowSpeed[playerid] == true)
    {
//ЗДОРОВЬЕ
		PlayerTextDrawHide(playerid, txdHealthBar[playerid]);
		PlayerTextDrawTextSize(playerid, txdHealthBar[playerid], 15, -(VehicleHealth*12.0/100));
		PlayerTextDrawShow(playerid, txdHealthBar[playerid]);
		format(strtmp, sizeof(strtmp), "%d%%", VehicleHealth);
		PlayerTextDrawSetStringEx(playerid, txdHealPercent[playerid], strtmp);
		//--------------------------------------------------------------------------
//ТОПЛИВО
		PlayerTextDrawHide(playerid, txdFuelBar[playerid]);
		PlayerTextDrawTextSize(playerid, txdFuelBar[playerid], 15, -floatround(VehInfo[nCarID[playerid]][cFuel]*12.0/VehicleArray[nCarModel[playerid]-400][GasMax]) );
		PlayerTextDrawShow(playerid, txdFuelBar[playerid]);
		format(strtmp, sizeof(strtmp), "%.0f %s", VehInfo[nCarID[playerid]][cFuel], RusToGame("л"));
		PlayerTextDrawSetStringEx(playerid, txdFuelPercent[playerid], strtmp);
		//--------------------------------------------------------------------------
//МЕТРАЖ
		format(strtmp, sizeof(strtmp), "%07d",VehInfo[nCarID[playerid]][cDist]);//"~g~KMH:~y~%d"
		PlayerTextDrawSetStringEx(playerid, txdMeterBar[playerid], strtmp);

//СКОРОСТЬ
		format(strtmp, sizeof(strtmp), "%03d", velocity);//"~g~KMH:~y~%d"
		PlayerTextDrawSetString(playerid, txdSpeedBar[playerid], strtmp);
	}
//==============================================================================

/*
	//300 градусов = 100%
	//170 максимальная скорость боинга = (170.0*100.0/300.0)%
	//300 = velocity*100/(170.0*100.0/300.0)
	//GetVehicleVelocity(GetPlayerVehicleID(playerid), fPos[0], fPos[1], fPos[2]);
	//30.0 - начальный угол/смещение
	//170.0*100.0/300.0 - угол соот. макс. скорости боинга
	new Float:alpha = 30.0 + (velocity*100.0/(170.0*100.0/300.0));//100.0;//205.3
	//if(alpha < 60.0) alpha = 60.0;
  	GetXYInring(83.5,403.0, 40, v[0], v[1], alpha);//83.5,403.0 координаты центра окружности
	//new Float:x, Float:x0 = 83.5, Float:y, Float:y0 = 403.0, r = 40;
	//floatpower((x - x0), 2) + floatpower((y - y0),2) = r*r;//уравнение окружности

	PlayerTextDrawHide(playerid, txdSpeedMark[playerid]);
	PlayerTextDrawDestroy(playerid, txdSpeedMark[playerid]);
	txdSpeedMark[playerid] = CreatePlayerTextDraw(playerid, v[0], v[1], "~r~.");
	PlayerTextDrawLetterSize(playerid, txdSpeedMark[playerid], 1.0, -3.0);//0.73, -2.60
	PlayerTextDrawSetOutline(playerid, txdSpeedMark[playerid], 1);
	PlayerTextDrawShow(playerid, txdSpeedMark[playerid]);
*/

//КОНЕЦ РАСЧЁТА СКОРОСТИ
//format(strtmp, sizeof(strtmp), "OnPlayerSpeedTimer. cDist: %d", VehInfo[nCarID[playerid]][cDist]);
//SendClientMessage(playerid, COLOR_RED, strtmp);
	TestLog(OPTIM, "OnPlayerSpeedTimer", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}



stock speedometer_OnGameModeExit()//для информационной панели начало
{   //вызывается из GameModeInitExitFunc

//для спидометров
	TextDrawDestroyEx(txdSpeedBarMark);

	TextDrawDestroyEx(txdHealthIcon);
	TextDrawDestroyEx(txdFuelIcon);

	TextDrawDestroyEx(txd_hbarl);
	TextDrawDestroyEx(txd_hbarm);
	TextDrawDestroyEx(txd_hbarr);
	TextDrawDestroyEx(txd_hbarRadar);
	TextDrawDestroyEx(txd_hbarPager);
	/*TextDrawDestroyEx(txdMark0);
	TextDrawDestroyEx(txdMark20);
	TextDrawDestroyEx(txdMark40);
	TextDrawDestroyEx(txdMark60);
	TextDrawDestroyEx(txdMark80);
	TextDrawDestroyEx(txdMark100);
	TextDrawDestroyEx(txdMark120);
	TextDrawDestroyEx(txdMark140);
	TextDrawDestroyEx(txdMark160);*/

#if defined samp03DL
	TextDrawDestroyEx(txdTablo);
#else
	TextDrawDestroyEx(txdTablo);
	TextDrawDestroyEx(txdTablo1);
	TextDrawDestroyEx(txdTablo2);
	TextDrawDestroyEx(txdTablo21);
	TextDrawDestroyEx(txdTablo3);
	TextDrawDestroyEx(txdTablo4);
#endif
}




stock speedometer_OnPlayerStateChange(playerid, newstate, oldstate)
{
//if(!IsPlayerInAnyVehicle(playerid)) return 1;
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{   //если игрок покинул водительское место
	    if(CarStatus[LastCar[playerid]][st_engine] == VEHICLE_PARAMS_ON)//перестанет пропадать спидометр
	    {//если двигатель включен
			gTextDrawHideSpeed[playerid] = true;
		}
	}
	if(newstate == PLAYER_STATE_DRIVER) //buggy dont finnish  //если ID нового состояния равно состоянию за рулём
	{	//если ID нового состояния равно состоянию 2
		//для отображения названия машины начало
		if(CarStatus[nCarID[playerid]][st_engine] == VEHICLE_PARAMS_ON)
		{
			if(VehicleArray[nCarModel[playerid]-400][Category] != Bicycle)
			{
//если спидометр не показан, то показать
				gTextDrawShowSpeed[playerid] = true;
			}
			format(strings, sizeof(strings), "~g~%s", VehicleArray[nCarModel[playerid]-400][Vehicle_Name] );
			GameTextForPlayerEx(playerid, strings, 3000, 1);//конец
		}
		else //if(CarStatus[nCarID[playerid]][st_engine] == VEHICLE_PARAMS_OFF)
		{   //если мотор выключен, то
			GameTextForPlayerEx(playerid, " Press ~b~~k~~TOGGLE_SUBMISSIONS~ ~n~~g~|~w~switch ON Engine~g~|", 1000, 1);
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER) //buggy dont finnish  //если ID нового состояния равно состоянию за рулём
	{	//если ID нового состояния равно состоянию 2
		//для отображения названия машины начало
		if(CarStatus[nCarID[playerid]][st_engine] == VEHICLE_PARAMS_ON)
		{
			if(VehicleArray[nCarModel[playerid]-400][Category] != Bicycle)
			{
//если спидометр не показан, то показать
				gTextDrawShowSpeed[playerid] = true;
			}
			format(strings, sizeof(strings), "~g~%s", VehicleArray[nCarModel[playerid]-400][Vehicle_Name] );
			GameTextForPlayerEx(playerid, strings, 3000, 1);//конец
		}
	}
	speedometer_StateChange(playerid);
}


//загружается из OnGameModeInit (OnCreateTextDraw)
//чтобы было под спидометром
//в процессе они постоянно то скрываются и снова показыватся для обновления изображения
stock speedometer_OnPlayerConnect(playerid)
{
	CreateSpeedometer(playerid);

	gTextDrawShowSpeed[playerid] = false;
	gTextDrawHideSpeed[playerid] = false;
	
//для спидометров
	txdSpeedBar[playerid] = CreatePlayerTextDraw(playerid, 143.0, 425.0, "000");
	PlayerTextDrawLetterSize(playerid, txdSpeedBar[playerid], 0.14, 0.7);
	PlayerTextDrawBackgroundColor(playerid, txdSpeedBar[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdSpeedBar[playerid], 1);
	PlayerTextDrawColor(playerid, txdSpeedBar[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdSpeedBar[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdSpeedBar[playerid], 0);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

//метраж
	txdMeterBar[playerid] = CreatePlayerTextDraw(playerid, 195.0, 425.0, "0000000");
	PlayerTextDrawLetterSize(playerid, txdMeterBar[playerid], 0.14, 0.7);
	PlayerTextDrawBackgroundColor(playerid, txdMeterBar[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdMeterBar[playerid], 1);
	PlayerTextDrawColor(playerid, txdMeterBar[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdMeterBar[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdMeterBar[playerid], 0);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

//здоровье тачки
  	txdHealPercent[playerid] = CreatePlayerTextDraw(playerid, 336.0, 436.0, "100%");
	PlayerTextDrawBackgroundColor(playerid, txdHealPercent[playerid], 0xFF000066);
	PlayerTextDrawFont(playerid, txdHealPercent[playerid], 2);
	PlayerTextDrawLetterSize(playerid, txdHealPercent[playerid], 0.14, 0.7);
	PlayerTextDrawColor(playerid, txdHealPercent[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdHealPercent[playerid], 1);
	PlayerTextDrawAlignment(playerid, txdHealPercent[playerid], 3);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

//топливо
  	txdFuelPercent[playerid] = CreatePlayerTextDraw(playerid, 363.0, 436.0, RusToGame("100 л"));
	PlayerTextDrawBackgroundColor(playerid, txdFuelPercent[playerid], 0x33AA3366);
	PlayerTextDrawFont(playerid, txdFuelPercent[playerid], 2);
	PlayerTextDrawLetterSize(playerid, txdFuelPercent[playerid], 0.14, 0.7);
	PlayerTextDrawColor(playerid, txdFuelPercent[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdFuelPercent[playerid], 1);
	PlayerTextDrawAlignment(playerid, txdFuelPercent[playerid], 3);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

	txdRADAR[playerid] = CreatePlayerTextDraw(playerid, 382.0, 427.0, "000");
	PlayerTextDrawBackgroundColor(playerid, txdRADAR[playerid], 0xFFFFFF66);
	PlayerTextDrawColor(playerid, txdRADAR[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetShadow(playerid, txdRADAR[playerid], 0);
	PlayerTextDrawAlignment(playerid, txdRADAR[playerid], 2);
	PlayerTextDrawFont(playerid, txdRADAR[playerid], 2);
	PlayerTextDrawLetterSize(playerid, txdRADAR[playerid], 0.25, 2.1);
	PlayerTextDrawSetOutline(playerid, txdRADAR[playerid], 1);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

//метка скорости маркер на радаре
	/*new Float: x = 0.0, Float: y = 0.0;
  	GetXYInring(83.5,404.0, 40, x, y, 0.0);//83.5,403.0 координаты центра окружности
	txdSpeedMark[playerid] = CreatePlayerTextDraw(playerid, x, y, "~r~.");
	PlayerTextDrawLetterSize(playerid, txdSpeedMark[playerid], 1.0, -3.0);//0.73, -2.60
	PlayerTextDrawSetOutline(playerid, txdSpeedMark[playerid], 1);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;*/

//для гонок
	txdPositionOfTotal[playerid] = CreatePlayerTextDraw(playerid, 20.0, 430.0, "0 / 0");
	PlayerTextDrawBackgroundColor(playerid, txdPositionOfTotal[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdPositionOfTotal[playerid], 1);
	PlayerTextDrawColor(playerid, txdPositionOfTotal[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdPositionOfTotal[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdPositionOfTotal[playerid], 0);
	PlayerTextDrawLetterSize(playerid, txdPositionOfTotal[playerid], 0.4, 1.75);
	PlayerTextDrawAlignment(playerid, txdPositionOfTotal[playerid], 2);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

	txdTaskTime[playerid] = CreatePlayerTextDraw(playerid, 65.0, 430.0, "00:00");/
	PlayerTextDrawBackgroundColor(playerid, txdTaskTime[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdTaskTime[playerid], 1);
	PlayerTextDrawColor(playerid, txdTaskTime[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdTaskTime[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdTaskTime[playerid], 0);
	PlayerTextDrawAlignment(playerid, txdTaskTime[playerid], 2);
	PlayerTextDrawLetterSize(playerid, txdTaskTime[playerid], 0.4, 1.75);//0.4, 1.8);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

	txdInsurances[playerid] = CreatePlayerTextDraw(playerid, 113, 430.0, "00 / 00");
	PlayerTextDrawBackgroundColor(playerid, txdInsurances[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdInsurances[playerid], 1);
	PlayerTextDrawColor(playerid, txdInsurances[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdInsurances[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdInsurances[playerid], 0);
	PlayerTextDrawAlignment(playerid, txdInsurances[playerid], 2);
	PlayerTextDrawLetterSize(playerid, txdInsurances[playerid], 0.4, 1.75);//0.4, 1.8);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

	txdPager[playerid] = CreatePlayerTextDraw(playerid, 412.0, 432.0, RusToGame("Движение по трассе открыто"));
	PlayerTextDrawBackgroundColor(playerid, txdPager[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdPager[playerid], 1);
	PlayerTextDrawColor(playerid, txdPager[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdPager[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdPager[playerid], 0);
	PlayerTextDrawLetterSize(playerid, txdPager[playerid],  0.19, 0.85);//0.15, 0.8);
	PlayerTextDrawAlignment(playerid, txdPager[playerid], 1);
	//PlayerTextDrawUseBox(playerid, txdPager[playerid], 1);//Определяет использование рамки. 1 - использовать, 0 - не использовать
	//PlayerTextDrawBoxColor(playerid, txdPager[playerid], 0x687F57FF);//Устанавливает цвет рамки
	//PlayerTextDrawTextSize(playerid, txdPager[playerid], 140.0, 0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	
}


stock speedometer_OnPlayerSpawn(playerid)
{
	gTextDrawShowSpeed[playerid] = false;
	speedometer_StateChange(playerid);
}
stock speedometer_OnTrailerAttached(playerid, vehicleid, trailerid)
{
	#pragma unused vehicleid

	//gTextDrawShowSpeed[playerid] = true;
	if(trailerid != 0)
	{
		PlayerTextDrawSetPreviewVehCol(playerid, txdTrailerIcon[playerid], VehInfo[trailerid][cColor1], VehInfo[trailerid][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
		PlayerTextDrawSetPreviewModel(playerid, txdTrailerIcon[playerid], nTrailerModel[playerid]);
		PlayerTextDrawShow(playerid, txdTrailerIcon[playerid]);
	}
	else
	{
		PlayerTextDrawHide(playerid, txdTrailerIcon[playerid]);
	}
}


stock speedometer_StateChange(playerid)
{
	if(gTextDrawShowSpeed[playerid] == true && gTextDrawHideSpeed[playerid] == false && TextDrawShowSpeed[playerid] == false)
	{//если есть разрешение на показ, нет сигнал на скрытие и текстдров не показан
		//TextDrawHideForPlayer(playerid, txtServerName);//должно загрузиться раньше чем спидометр

//для спидометров
		if(	IsTrailerAttachedToVehicle(nCarID[playerid]) )
		{
			PlayerTextDrawSetPreviewVehCol(playerid, txdTrailerIcon[playerid], VehInfo[nTrailerID[playerid]][cColor1], VehInfo[nTrailerID[playerid]][cColor2]);
			PlayerTextDrawSetPreviewModel(playerid, txdTrailerIcon[playerid], nTrailerModel[playerid]);//435);//nTrailerModel[playerid]);
			PlayerTextDrawShow(playerid, txdTrailerIcon[playerid]);
		}
		PlayerTextDrawTextSize(playerid, txdVehicleIcon[playerid], 26.0, 32.0);
		PlayerTextDrawSetPreviewRot(playerid, txdVehicleIcon[playerid], 0.0, 0.0, 30.0);//0.0, 0.0, 0.0);
		PlayerTextDrawSetPreviewVehCol(playerid, txdVehicleIcon[playerid], VehInfo[nCarID[playerid]][cColor1], VehInfo[nCarID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
		PlayerTextDrawSetPreviewModel(playerid, txdVehicleIcon[playerid], nCarModel[playerid]);
		PlayerTextDrawShow(playerid, txdVehicleIcon[playerid]);

		PlayerTextDrawShow(playerid, txdHealPercent[playerid]);
		PlayerTextDrawShow(playerid, txdFuelPercent[playerid]);

		PlayerTextDrawShow(playerid, txdSpeedBar[playerid]);
		TextDrawShowForPlayer(playerid, txdSpeedBarMark);

		PlayerTextDrawShow(playerid, txdMeterBar[playerid]);

		TextDrawShowForPlayer(playerid, txd_hbarl);
		TextDrawShowForPlayer(playerid, txd_hbarm);
		TextDrawShowForPlayer(playerid, txd_hbarr);
		TextDrawShowForPlayer(playerid, txd_hbarRadar);
		TextDrawShowForPlayer(playerid, txd_hbarPager);

		PlayerTextDrawShow(playerid, txdPositionOfTotal[playerid]);
		PlayerTextDrawShow(playerid, txdTaskTime[playerid]);
		PlayerTextDrawShow(playerid, txdInsurances[playerid]);
		PlayerTextDrawShow(playerid, txdPager[playerid]);

		/*TextDrawShowForPlayer(playerid, txdMark0);
		TextDrawShowForPlayer(playerid, txdMark20);
		TextDrawShowForPlayer(playerid, txdMark40);
		TextDrawShowForPlayer(playerid, txdMark60);
		TextDrawShowForPlayer(playerid, txdMark80);
		TextDrawShowForPlayer(playerid, txdMark100);
		TextDrawShowForPlayer(playerid, txdMark120);
		TextDrawShowForPlayer(playerid, txdMark140);
		TextDrawShowForPlayer(playerid, txdMark160);*/


#if defined samp03DL
		TextDrawShowForPlayer(playerid, txdTablo);
#else
		TextDrawShowForPlayer(playerid, txdTablo);
		TextDrawShowForPlayer(playerid, txdTablo1);
		TextDrawShowForPlayer(playerid, txdTablo2);
		TextDrawShowForPlayer(playerid, txdTablo21);
		TextDrawShowForPlayer(playerid, txdTablo3);
		TextDrawShowForPlayer(playerid, txdTablo4);
#endif

		PlayerTextDrawShow(playerid, txdRADAR[playerid]);

		//TextDrawShowForPlayer(playerid, txdHealthBar[playerid]);
		//TextDrawShowForPlayer(playerid, txdFuelBar[playerid]);
		PlayerTextDrawShow(playerid, txdHealthBar[playerid]);
		PlayerTextDrawShow(playerid, txdFuelBar[playerid]);

		TextDrawShowForPlayer(playerid, txdHealthIcon);
		TextDrawShowForPlayer(playerid, txdFuelIcon);

		TextDrawShowSpeed[playerid] = true;//текстдров показан
		gTextDrawShowSpeed[playerid] = false;//флаг разрешения опустили
	}
	else if(gTextDrawShowSpeed[playerid] == false && gTextDrawHideSpeed[playerid] == true && TextDrawShowSpeed[playerid] == true)
	{//если есть разрешение на скрытие и текстдров показан
		//TextDrawShowForPlayer(playerid, txtServerName);//должно загрузиться раньше чем спидометр
//для спидометров
		//if( IsTrailerAttachedToVehicle(LastCar[playerid]) )
		//{
		PlayerTextDrawHide(playerid, txdTrailerIcon[playerid]);
		//}
		PlayerTextDrawHide(playerid, txdVehicleIcon[playerid]);

		PlayerTextDrawHide(playerid, txdMeterBar[playerid]);
		PlayerTextDrawHide(playerid, txdHealPercent[playerid]);
		PlayerTextDrawHide(playerid, txdFuelPercent[playerid]);

		PlayerTextDrawHide(playerid, txdPositionOfTotal[playerid]);
		PlayerTextDrawHide(playerid, txdTaskTime[playerid]);
		PlayerTextDrawHide(playerid, txdInsurances[playerid]);
		PlayerTextDrawHide(playerid, txdPager[playerid]);

		//TextDrawHideForPlayer(playerid, txdHealthBar[playerid]);
		//TextDrawHideForPlayer(playerid, txdFuelBar[playerid]);
		PlayerTextDrawHide(playerid, txdHealthBar[playerid]);
		PlayerTextDrawHide(playerid, txdFuelBar[playerid]);

		TextDrawHideForPlayer(playerid, txdHealthIcon);
		TextDrawHideForPlayer(playerid, txdFuelIcon);

		PlayerTextDrawHide(playerid, txdSpeedBar[playerid]);
		TextDrawHideForPlayer(playerid, txdSpeedBarMark);

		TextDrawHideForPlayer(playerid, txd_hbarl);
		TextDrawHideForPlayer(playerid, txd_hbarm);
		TextDrawHideForPlayer(playerid, txd_hbarr);
		TextDrawHideForPlayer(playerid, txd_hbarRadar);
		TextDrawHideForPlayer(playerid, txd_hbarPager);
		
		/*TextDrawHideForPlayer(playerid, txdMark0);
		TextDrawHideForPlayer(playerid, txdMark20);
		TextDrawHideForPlayer(playerid, txdMark40);
		TextDrawHideForPlayer(playerid, txdMark60);
		TextDrawHideForPlayer(playerid, txdMark80);
		TextDrawHideForPlayer(playerid, txdMark100);
		TextDrawHideForPlayer(playerid, txdMark120);
		TextDrawHideForPlayer(playerid, txdMark140);
		TextDrawHideForPlayer(playerid, txdMark160);*/

#if defined samp03DL
		TextDrawHideForPlayer(playerid, txdTablo);
#else
		TextDrawHideForPlayer(playerid, txdTablo);
		TextDrawHideForPlayer(playerid, txdTablo1);
		TextDrawHideForPlayer(playerid, txdTablo2);
		TextDrawHideForPlayer(playerid, txdTablo21);
		TextDrawHideForPlayer(playerid, txdTablo3);
		TextDrawHideForPlayer(playerid, txdTablo4);
#endif
		PlayerTextDrawHide(playerid, txdRADAR[playerid]);

		TextDrawShowSpeed[playerid] = false;//1
		gTextDrawHideSpeed[playerid] = false;//2
	}
    else
    {
		gTextDrawShowSpeed[playerid] = false;
		gTextDrawHideSpeed[playerid] = false;
	}
}



stock speedometer_OnPlayerDisconnect(playerid)
{
	if(TextDrawShowSpeed[playerid] == true)
	{//если паказан, то скрыть
//для спидометров
		//PlayerTextDrawHide(playerid, txdCarIcon[playerid]);
		PlayerTextDrawHide(playerid, txdTrailerIcon[playerid]);
		PlayerTextDrawHide(playerid, txdVehicleIcon[playerid]);

		//PlayerTextDrawHide(playerid, txdSpeedMark[playerid]);
		PlayerTextDrawHide(playerid, txdSpeedBar[playerid]);
		TextDrawHideForPlayer(playerid, txdSpeedBarMark);

		TextDrawHideForPlayer(playerid, txd_hbarl);
		TextDrawHideForPlayer(playerid, txd_hbarm);
		TextDrawHideForPlayer(playerid, txd_hbarr);
		TextDrawHideForPlayer(playerid, txd_hbarRadar);
		TextDrawHideForPlayer(playerid, txd_hbarPager);
		
		PlayerTextDrawHide(playerid, txdPositionOfTotal[playerid]);
		PlayerTextDrawHide(playerid, txdTaskTime[playerid]);
		PlayerTextDrawHide(playerid, txdInsurances[playerid]);
		PlayerTextDrawHide(playerid, txdPager[playerid]);

		/*TextDrawHideForPlayer(playerid, txdMark0);
		TextDrawHideForPlayer(playerid, txdMark20);
		TextDrawHideForPlayer(playerid, txdMark40);
		TextDrawHideForPlayer(playerid, txdMark60);
		TextDrawHideForPlayer(playerid, txdMark80);
		TextDrawHideForPlayer(playerid, txdMark100);
		TextDrawHideForPlayer(playerid, txdMark120);
		TextDrawHideForPlayer(playerid, txdMark140);
		TextDrawHideForPlayer(playerid, txdMark160);*/
		
#if defined samp03DL
		TextDrawHideForPlayer(playerid, txdTablo);
#else
		TextDrawHideForPlayer(playerid, txdTablo);
		TextDrawHideForPlayer(playerid, txdTablo1);
		TextDrawHideForPlayer(playerid, txdTablo2);
		TextDrawHideForPlayer(playerid, txdTablo21);
		TextDrawHideForPlayer(playerid, txdTablo3);
		TextDrawHideForPlayer(playerid, txdTablo4);
#endif

		PlayerTextDrawHide(playerid, txdRADAR[playerid]);

		//TextDrawHideForPlayer(playerid, txdHealthBar[playerid]);
		//TextDrawHideForPlayer(playerid, txdFuelBar[playerid]);
		PlayerTextDrawHide(playerid, txdHealthBar[playerid]);
		PlayerTextDrawHide(playerid, txdFuelBar[playerid]);

		TextDrawHideForPlayer(playerid, txdHealthIcon);
		TextDrawHideForPlayer(playerid, txdFuelIcon);

		PlayerTextDrawHide(playerid, txdHealPercent[playerid]);
		PlayerTextDrawHide(playerid, txdFuelPercent[playerid]);

		PlayerTextDrawHide(playerid, txdMeterBar[playerid]);

		TextDrawShowSpeed[playerid] = false;
	}

//OnPlayerUnLoadTextDraw(playerid)
	PlayerTextDrawDestroy(playerid, txdSpeedBar[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdMeterBar[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;

	PlayerTextDrawDestroy(playerid, txdPositionOfTotal[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdTaskTime[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdInsurances[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdPager[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;

	PlayerTextDrawDestroy(playerid, txdHealPercent[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdFuelPercent[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;

	PlayerTextDrawDestroy(playerid, txdRADAR[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;

//OnPlayerDestroyTextDraw(playerid)
	PlayerTextDrawDestroy(playerid, txdFuelBar[playerid]);  PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdHealthBar[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;

	//PlayerTextDrawDestroy(playerid, txdCarIcon[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdTrailerIcon[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, txdVehicleIcon[playerid]); PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
}

stock SendPagerMessage(playerid)//, string[] //const
{
	if(!IsPlayerInAnyVehicle(playerid)) return 1;
    //if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
    
	//new strtmp[42+8+10];//{FFFFFF}%s's{0080FF} по цене {33AA33}$%d
    //format(message, sizeof(message), "Плата за заправку на %.1f л. - $%d.", FillUp, CostFuel);
    //SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	//PlayAudioStreamForPlayerEx(playerid, "pager.wav");
	PlaySoundForPlayer(playerid, SOUND_DOOR_BUZZER);
    PlayerTextDrawSetStringEx(playerid, txdPager[playerid], RusToGame(PagerMessage));
    return 1;
}


stock CMD_show(playerid)
{
    if(gHide[playerid] == false)
    {
	   	if(TextDrawShowCarTime[playerid] == true)
	   	{
	    	PlayerTextDrawShow(playerid, txdCarTime[playerid]);//для спидометров
	//TextDrawShowForPlayer(playerid, txdDebry[playerid]);
	    	//TextDrawShowCarTime[playerid] = true;
		}
		if(TextDrawShowClock[playerid] == true)
		{
		    TextDrawShowForPlayer(playerid, txdTimeDisp);//для часиков
		    TextDrawShowForPlayer(playerid, txdSecondsTime);
		    TextDrawShowForPlayer(playerid, txdDate);
		    //TextDrawShowForPlayer(playerid, txtServerName);

		    PlayerTextDrawShow(playerid, txdBankDisp[playerid]);//для банковского счёта
			//PlayerTextDrawShow(playerid, txdSpeedMark[playerid]);

			PlayerTextDrawShow(playerid, txdPlayerHealth[playerid]);
			//PlayerTextDrawShow(playerid, txdPlayerZone[playerid]);
			PlayerTextDrawShow(playerid, txdPlayerRegion[playerid]);

		    //TextDrawShowClock[playerid] = true;
	    }
		if(TextDrawShowBegunok == true)//для бегущей строки начало
		{
			TextDrawShowForPlayer(playerid, txdBegunok);
		}
		if(TextDrawShowSpeed[playerid] == true)
		{
			TextDrawShowForPlayer(playerid, txdTablo);
			TextDrawShowForPlayer(playerid, txdTablo1);
			TextDrawShowForPlayer(playerid, txdTablo2);
			TextDrawShowForPlayer(playerid, txdTablo3);
			TextDrawShowForPlayer(playerid, txdTablo4);

			if(	IsTrailerAttachedToVehicle(nCarID[playerid]) )
			{
				//TextDrawSetPreviewVehCol(txdTrailerIcon[playerid], VehInfo[nTrailerID[playerid]][cColor1], VehInfo[nTrailerID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
				//TextDrawSetPreviewModel(txdTrailerIcon[playerid], nTrailerModel[playerid]);
				//TextDrawShowForPlayer(playerid, txdTrailerIcon[playerid]);
				PlayerTextDrawSetPreviewVehCol(playerid, txdTrailerIcon[playerid], VehInfo[nTrailerID[playerid]][cColor1], VehInfo[nTrailerID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
				PlayerTextDrawSetPreviewModel(playerid, txdTrailerIcon[playerid], nTrailerModel[playerid]);
				PlayerTextDrawShow(playerid, txdTrailerIcon[playerid]);
			}

			//TextDrawTextSize(txdVehicleIcon[playerid], 26.0, 32.0);
			//TextDrawSetPreviewRot(txdVehicleIcon[playerid], 0.0, 0.0, 0.0);
			//TextDrawSetPreviewVehCol(txdVehicleIcon[playerid], VehInfo[nCarID[playerid]][cColor1], VehInfo[nCarID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
			//TextDrawSetPreviewModel(txdVehicleIcon[playerid], nCarModel[playerid]);
			//TextDrawShowForPlayer(playerid, txdVehicleIcon[playerid]);
			PlayerTextDrawTextSize(playerid, txdVehicleIcon[playerid], 26.0, 32.0);
			PlayerTextDrawSetPreviewRot(playerid, txdVehicleIcon[playerid], 0.0, 0.0, 0.0);
			PlayerTextDrawSetPreviewVehCol(playerid, txdVehicleIcon[playerid], VehInfo[nCarID[playerid]][cColor1], VehInfo[nCarID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
			PlayerTextDrawSetPreviewModel(playerid, txdVehicleIcon[playerid], nCarModel[playerid]);
			PlayerTextDrawShow(playerid, txdVehicleIcon[playerid]);

			TextDrawShowForPlayer(playerid, txd_hbarl);
			TextDrawShowForPlayer(playerid, txd_hbarm);
			TextDrawShowForPlayer(playerid, txd_hbarr);

			PlayerTextDrawShow(playerid, txdPositionOfTotal[playerid]);
			PlayerTextDrawShow(playerid, txdTaskTime[playerid]);
			PlayerTextDrawShow(playerid, txdInsurances[playerid]);

			PlayerTextDrawShow(playerid, txdSpeedBar[playerid]);
			PlayerTextDrawShow(playerid, txdMeterBar[playerid]);
			TextDrawShowForPlayer(playerid, txdSpeedBarMark);

			//TextDrawShowForPlayer(playerid, txdHealthBar[playerid]);
			//TextDrawShowForPlayer(playerid, txdFuelBar[playerid]);
			PlayerTextDrawShow(playerid, txdHealthBar[playerid]);
			PlayerTextDrawShow(playerid, txdFuelBar[playerid]);

			TextDrawShowForPlayer(playerid, txdHealthIcon);
			TextDrawShowForPlayer(playerid, txdFuelIcon);

			PlayerTextDrawShow(playerid, txdHealPercent[playerid]);
			PlayerTextDrawShow(playerid, txdFuelPercent[playerid]);

			PlayerTextDrawShow(playerid, txdRADAR[playerid]);
			PlayerTextDrawShow(playerid, txdPager[playerid]);
			//TextDrawShowSpeed[playerid] = true;
		}
	    if(TextDrawShowRace[playerid] == true)
		{
			PlayerTextDrawShow(playerid, txdRacePosition[playerid]);
		    PlayerTextDrawShow(playerid, txdPositionAppend[playerid]);
		    TextDrawShowForPlayer(playerid, txdTotalRacers);
		    TextDrawShowForPlayer(playerid, txdRaceTime);
		    //TextDrawShowRace[playerid] = true;
	    }
		if(TextDrawShowCS[playerid] == true)
		{
			PlayerTextDrawShow(playerid, txdRacePosition[playerid]);
		    PlayerTextDrawShow(playerid, txdPositionAppend[playerid]);
			TextDrawShowForPlayer(playerid, txdTotalMembers);
			TextDrawShowForPlayer(playerid, txdCSTime);
			//TextDrawShowCS[playerid] = false;
		}
	    if(TextDrawShowBattery[playerid] == true)
	    {
			TextDrawShowForPlayer(playerid, txdBlackSpeed);
		    TextDrawShowForPlayer(playerid, txdMarkerMinus);
		    TextDrawShowForPlayer(playerid, txdMarkerPlus);
		    TextDrawShowForPlayer(playerid, txdDarkYellowSpeed);
		    PlayerTextDrawShow(playerid, txdLightYellowSpeed[playerid]);
	    }
	    if(TextDrawShowMessage[playerid] == true)
		{
			TextDrawShowForPlayer(playerid, txdSystemMessage);
			//TextDrawShowMessage[playerid] = true;
		}
		if(TextDrawShowArmour[playerid] == true)
		{
			PlayerTextDrawShow(playerid, txdPlayerHealth[playerid]);
			PlayerTextDrawShow(playerid, txdPlayerArmour[playerid]);
			//TextDrawShowArmour[playerid] = false;
		}
		if(TextDrawShowChat[playerid] == true)
		{
			PlayerTextDrawShow(playerid, txdCHAT[playerid]);
			//TextDrawShowChat[playerid] = false;
		}
		gHide[playerid] = true;
	}
	else
	{
	   	//if(TextDrawShowCarTime[playerid] == true)
	   	//{
	   	PlayerTextDrawHide(playerid, txdCarTime[playerid]);//для спидометров
		//TextDrawHideForPlayer(playerid, txdDebry[playerid]);
	   	//TextDrawShowCarTime[playerid] = false;
		//}
		//if(TextDrawShowClock[playerid] == true)
		//{
	    TextDrawHideForPlayer(playerid, txdTimeDisp);//для часиков
	    TextDrawHideForPlayer(playerid, txdSecondsTime);
	    TextDrawHideForPlayer(playerid, txdDate);
	    //TextDrawHideForPlayer(playerid, txtServerName);

	    PlayerTextDrawHide(playerid, txdBankDisp[playerid]);//для банковского счёта
		//PlayerTextDrawHide(playerid, txdSpeedMark[playerid]);

		PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);
		//PlayerTextDrawHide(playerid, txdPlayerZone[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerRegion[playerid]);
	    //TextDrawShowClock[playerid] = false;
	    //}
		//if(TextDrawShowBegunok == true)
		//{
		TextDrawHideForPlayer(playerid, txdBegunok);//для бегущей строки начало
		//}
		//if(TextDrawShowSpeed[playerid] == true)
		//{

		TextDrawHideForPlayer(playerid, txdTablo);
		TextDrawHideForPlayer(playerid, txdTablo1);
		TextDrawHideForPlayer(playerid, txdTablo2);
		TextDrawHideForPlayer(playerid, txdTablo3);
		TextDrawHideForPlayer(playerid, txdTablo4);
//#endif

		//PlayerTextDrawHide(playerid, txdCarIcons[playerid]);
		if( IsTrailerAttachedToVehicle(LastCar[playerid]) )
		{
			//TextDrawHideForPlayer(playerid, txdTrailerIcon[playerid]);
			PlayerTextDrawHide(playerid, txdTrailerIcon[playerid]);
		}
		//TextDrawHideForPlayer(playerid, txdVehicleIcon[playerid]);
		PlayerTextDrawHide(playerid, txdVehicleIcon[playerid]);

		TextDrawHideForPlayer(playerid, txd_hbarl);
		TextDrawHideForPlayer(playerid, txd_hbarm);
		TextDrawHideForPlayer(playerid, txd_hbarr);

		PlayerTextDrawHide(playerid, txdPositionOfTotal[playerid]);
		PlayerTextDrawHide(playerid, txdTaskTime[playerid]);
		PlayerTextDrawHide(playerid, txdInsurances[playerid]);

		PlayerTextDrawHide(playerid, txdSpeedBar[playerid]);
		PlayerTextDrawHide(playerid, txdMeterBar[playerid]);
		TextDrawHideForPlayer(playerid, txdSpeedBarMark);

		//TextDrawHideForPlayer(playerid, txdHealthBar[playerid]);
		//TextDrawHideForPlayer(playerid, txdFuelBar[playerid]);
		PlayerTextDrawHide(playerid, txdHealthBar[playerid]);
		PlayerTextDrawHide(playerid, txdFuelBar[playerid]);

		TextDrawHideForPlayer(playerid, txdHealthIcon);
		TextDrawHideForPlayer(playerid, txdFuelIcon);

		PlayerTextDrawHide(playerid, txdHealPercent[playerid]);
		PlayerTextDrawHide(playerid, txdFuelPercent[playerid]);

		PlayerTextDrawHide(playerid, txdRADAR[playerid]);
		PlayerTextDrawHide(playerid, txdPager[playerid]);

		//TextDrawShowSpeed[playerid] = false;
		//}
	    //if(TextDrawShowRace[playerid] == true)
		//{
		PlayerTextDrawHide(playerid, txdRacePosition[playerid]);
	    PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
	    TextDrawHideForPlayer(playerid, txdTotalRacers);
	    TextDrawHideForPlayer(playerid, txdRaceTime);
	    //TextDrawShowRace[playerid] = false;
	    //}

		//if(TextDrawShowCS[playerid] == true)
		//{
		PlayerTextDrawHide(playerid, txdRacePosition[playerid]);
		PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
		TextDrawHideForPlayer(playerid, txdTotalMembers);
		TextDrawHideForPlayer(playerid, txdCSTime);
		//TextDrawShowCS[playerid] = false;
		//}

		//if(TextDrawShowBattery[playerid] == true)
		//{
		TextDrawHideForPlayer(playerid, txdBlackSpeed);
	    TextDrawHideForPlayer(playerid, txdMarkerMinus);
	    TextDrawHideForPlayer(playerid, txdMarkerPlus);
	    TextDrawHideForPlayer(playerid, txdDarkYellowSpeed);
	    PlayerTextDrawHide(playerid, txdLightYellowSpeed[playerid]);
	    //}
	    
	    //if(TextDrawShowMessage[playerid] == true)
		//{
		TextDrawHideForPlayer(playerid, txdSystemMessage);
		//TextDrawShowMessage[playerid] = false;
		//}

		//if(TextDrawShowArmour[playerid] == true)
		//{
		PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerArmour[playerid]);
		//TextDrawShowArmour[playerid] = false;
		//}

		PlayerTextDrawHide(playerid, txdCHAT[playerid]);
		gHide[playerid] = false;
	}
}
