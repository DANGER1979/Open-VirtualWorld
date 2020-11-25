/*
 *            RouteAdvisor v1.0
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 23.03.2020
 * @update    : 23.03.2020
 *
 * This file is provided as is (no warranties).
 *
 */
//#include <a_samp>


//##############################################################################//
//                                                                              //
//                          ИДЕНТИФИКАТОРЫ TEXTDRAWS                            //
//                                                                              //
//##############################################################################//
/*enum txdidentificator
{
	ADVISOR
}*/


//для спидометров
new	Text:txdAdvisor[14]; //Text:txdEdging
/*new	Text:txdAdvisor[0], //Text:txdEdging,
	Text:txdAdvisor[1], //Text:txdFrame,
	Text:txdAdvisor[2], //Text:txdBackground,
	Text:txdAdvisor[3], //Text:txdHat,
	Text:txdAdvisor[4], //Text:txdFuelIcon,
	Text:txdAdvisor[5], //Text:txdGasSation,
	Text:txdAdvisor[6], //Text:txdDayTime,
	Text:txdAdvisor[7], //Text:txdCurrentTask,
	Text:txdAdvisor[8], //Text:txdCargo,
	Text:txdAdvisor[9], //Text:txdDestination,
	Text:txdAdvisor[10], //Text:txdLeft,
	Text:txdAdvisor[11], //Text:txdIncome,
	Text:txdAdvisor[12], //Text:txdRestStop,
	Text:txdAdvisor[13], //Text:txdCancelTask;*/

	/*Text:txdMark20,
	Text:txdMark40,
	Text:txdMark60,
	Text:txdMark80,
	Text:txdMark100,
	Text:txdMark120,
	Text:txdMark140,
	Text:txdMark160,
	Text:txdFrame1,
	Text:txdTablo;*/

/*new	PlayerText:txdHealthBar[MAX_PLAYERS],
	PlayerText:txdFuelBar[MAX_PLAYERS],
	PlayerText:txdVehicleIcon[MAX_PLAYERS],
	PlayerText:txdTrailerIcon[MAX_PLAYERS],
	PlayerText:txdSpeedBar[MAX_PLAYERS],
	PlayerText:txdHealPercent[MAX_PLAYERS],
	PlayerText:txdFuelPercent[MAX_PLAYERS],
	PlayerText:txdBankBar[MAX_PLAYERS],
	PlayerText:txdNameItem[MAX_PLAYERS],
	PlayerText:txdDestinationBar[MAX_PLAYERS],
	PlayerText:txdTaskTime[MAX_PLAYERS],
	PlayerText:txdIncomeBar[MAX_PLAYERS],
	PlayerText:txdETA[MAX_PLAYERS],
	PlayerText:txdRestStopBar[MAX_PLAYERS];*/

new	PlayerText:txdMeterBar[MAX_PLAYERS];
new	PlayerText:txdPager[MAX_PLAYERS];

new	PlayerText:pltxdAdvisor[MAX_PLAYERS][14];
/*new	PlayerText:pltxdAdvisor[MAX_PLAYERS][0], //PlayerText:txdHealthBar[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][1], //PlayerText:txdFuelBar[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][2], //PlayerText:txdVehicleIcon[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][3], //PlayerText:txdTrailerIcon[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][4], //PlayerText:txdSpeedBar[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][5], //PlayerText:txdHealPercent[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][6], //PlayerText:txdFuelPercent[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][7], //PlayerText:txdBankBar[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][8], //PlayerText:txdNameItem[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][9], //PlayerText:txdDestinationBar[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][10], //PlayerText:txdTaskTime[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][11], //PlayerText:txdIncomeBar[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][12], //PlayerText:txdETA[MAX_PLAYERS],
	PlayerText:pltxdAdvisor[MAX_PLAYERS][13], //PlayerText:txdRestStopBar[MAX_PLAYERS],*/



//##############################################################################//
//                                                                              //
//                             ИНДИКАТОРЫ TEXTDRAWS                             //
//                                                                              //
//##############################################################################//
//new bool:TextDrawsShown[MAX_PLAYERS];
new bool:TextDrawShowSpeed[MAX_PLAYERS];//индикатор состояния текстдрова


//##############################################################################//
//                                                                              //
//                             ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ                            //
//                                                                              //
//##############################################################################//
//для сдвига всех текстдровов
stock Text:aTextDrawCreateEx(Float:x, Float:y, text[])
{
	TEXT_DRAWS_COUNTER ++;
	//return TextDrawCreate(x-465.0, y-80.0, text);//левое расположение
	return TextDrawCreate(x+12.0, y+50.0, text);//правое расположение
}

stock PlayerText:aCreatePlayerTextDrawEx(playerid, Float:x, Float:y, playertext[])
{
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	//return CreatePlayerTextDraw(playerid, x-465.0, y-80.0, playertext);
	return CreatePlayerTextDraw(playerid, x+12.0, y+50.0, playertext);
}

/*stock TextDrawDestroyEx(Text:text)
{
	TEXT_DRAWS_COUNTER --;
	return TextDrawDestroy(text);
}*/
/*stock PlayerTextDrawDestroyEx(playerid, PlayerText:playertext)
{
	if(playertext == PlayerText:INVALID_TEXT_DRAW) return 0;
	PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, playertext);
	return INVALID_TEXT_DRAW;
}*/

stock aTextDrawTextSizeEx(Text:text, Float:x, Float:y)
{
	//return TextDrawTextSize(text, x-465.0, y-80.0);
	return TextDrawTextSize(text, x+12.0, y+50.0);
}

stock aPlayerTextDrawTextSizeEx(playerid, PlayerText:playertext, Float:x, Float:y)
{
	//return PlayerTextDrawTextSize(playerid, playertext, x-465.0, y-80.0);
	return PlayerTextDrawTextSize(playerid, playertext, x+12.0, y+50.0);
}
//##############################################################################//
//##############################################################################//


stock advisor_OnGameModeInit()
{
//для спидометров
//------------------------------------------------------------------------------
//нижний фон
	txdAdvisor[0] = aTextDrawCreateEx(628.500000, 233.000000, "usebox1");//Создать новый Text Draw в памяти сервера.
	TextDrawLetterSize(txdAdvisor[0], 0.000000, 17.899999);//Устанавливает ширину и высоту букв(рамки) в пикселях.
	aTextDrawTextSizeEx(txdAdvisor[0], 468.000000, 0.000000);//Устанавливает ширину и высоту рамки (при использовании рамки).
	TextDrawAlignment(txdAdvisor[0], 1);//Устанавливает смещение текста в Text Draw. ID смещения: 0 или 1 - влево, 2 - центр, 3 - вправо.
	TextDrawColor(txdAdvisor[0], 269553920);
	TextDrawUseBox(txdAdvisor[0], true);//Определяет использование рамки. 1 - использовать, 0 - не использовать
	TextDrawBoxColor(txdAdvisor[0], 269554090);//Устанавливает цвет рамки
	TextDrawSetShadow(txdAdvisor[0], 0);
	TextDrawSetOutline(txdAdvisor[0], 0);
	TextDrawFont(txdAdvisor[0], 0);//Изменяет шрифт текста. (0-3) 4-текстура 5-модель

	txdAdvisor[1] = aTextDrawCreateEx(626.299987, 236.000000, "usebox2");
	TextDrawLetterSize(txdAdvisor[1], 0.000000, 17.200000);
	aTextDrawTextSizeEx(txdAdvisor[1], 470.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[1], 1);
	TextDrawColor(txdAdvisor[1], 1052945);
	TextDrawUseBox(txdAdvisor[1], true);
	TextDrawBoxColor(txdAdvisor[1], 1616928938);
	TextDrawSetShadow(txdAdvisor[1], 0);
	TextDrawSetOutline(txdAdvisor[1], 0);
	TextDrawFont(txdAdvisor[1], 0);


	txdAdvisor[2] = aTextDrawCreateEx(622.000000, 241.199996, "usebox3");
	TextDrawLetterSize(txdAdvisor[2], 0.000000, 16.000000);
	aTextDrawTextSizeEx(txdAdvisor[2], 474.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[2], 1);
	TextDrawColor(txdAdvisor[2], 168430335);
	TextDrawUseBox(txdAdvisor[2], true);
	TextDrawBoxColor(txdAdvisor[2], 336860415);
	TextDrawSetShadow(txdAdvisor[2], 0);
	TextDrawSetOutline(txdAdvisor[2], 0);
	TextDrawFont(txdAdvisor[2], 0);
	
//------------------------------------------------------------------------------
//шапка
	txdAdvisor[3] = aTextDrawCreateEx(478.000000, 242.000000, "LD_SPAC:white");
	TextDrawLetterSize(txdAdvisor[3], 0.000000, 0.000000);
	TextDrawTextSize(txdAdvisor[3], 140.000000, 14.000000);
	TextDrawAlignment(txdAdvisor[3], 1);
	TextDrawColor(txdAdvisor[3], 673720575);
	TextDrawSetShadow(txdAdvisor[3], 0);
	TextDrawSetOutline(txdAdvisor[3], 0);
	TextDrawFont(txdAdvisor[3], 4);

	//иконка АЗС
	txdAdvisor[4] = aTextDrawCreateEx(557.000000, 241.000000, "Fuel");
	TextDrawLetterSize(txdAdvisor[4], 0.000000, 0.000000);
	TextDrawTextSize(txdAdvisor[4], 16.000000, 16.000000);
	TextDrawAlignment(txdAdvisor[4], 1);
	TextDrawColor(txdAdvisor[4], -1);
	TextDrawUseBox(txdAdvisor[4], true);
	TextDrawBoxColor(txdAdvisor[4], 0);
	TextDrawSetShadow(txdAdvisor[4], 0);
	TextDrawSetOutline(txdAdvisor[4], 1);
	TextDrawBackgroundColor(txdAdvisor[4], 0x00000000);
	TextDrawFont(txdAdvisor[4], 5);
	TextDrawSetProportional(txdAdvisor[4], 1);
	TextDrawSetPreviewModel(txdAdvisor[4], 1676);
	TextDrawSetPreviewRot(txdAdvisor[4], 0.000000, 0.000000, 0.000000, 1.000000);
	
	//иконка АЗС
	txdAdvisor[5] = aTextDrawCreateEx(520.000000, 265.000000, "Fuel");
	TextDrawLetterSize(txdAdvisor[5], 0.000000, 0.000000);
	TextDrawTextSize(txdAdvisor[5], 60.000000, 80.000000);
	TextDrawAlignment(txdAdvisor[5], 1);
	TextDrawColor(txdAdvisor[5], -1);
	TextDrawUseBox(txdAdvisor[5], true);
	TextDrawBoxColor(txdAdvisor[5], 0);
	TextDrawSetShadow(txdAdvisor[5], 0);
	TextDrawSetOutline(txdAdvisor[5], 1);
	TextDrawBackgroundColor(txdAdvisor[5], 0x00000000);
	TextDrawFont(txdAdvisor[5], 5);
	TextDrawSetProportional(txdAdvisor[5], 1);
	TextDrawSetPreviewModel(txdAdvisor[5], 1676);
	TextDrawSetPreviewRot(txdAdvisor[5], 0.000000, 0.000000, 0.000000, 1.000000);


	txdAdvisor[6] = aTextDrawCreateEx(588.000000, 243.500000, "Вт 22:55");
	TextDrawLetterSize(txdAdvisor[6], 0.200000, 1.250000);
	aTextDrawTextSizeEx(txdAdvisor[6], 617.000000, 150.000000);
	TextDrawAlignment(txdAdvisor[6], 1);
	TextDrawColor(txdAdvisor[6], -1);
	TextDrawSetShadow(txdAdvisor[6], 0);
	TextDrawSetOutline(txdAdvisor[6], 1);
	TextDrawBackgroundColor(txdAdvisor[6], 51);
	TextDrawFont(txdAdvisor[6], 1);
	TextDrawSetProportional(txdAdvisor[6], 1);
	
//------------------------------------------------------------------------------
	txdAdvisor[7] = aTextDrawCreateEx(479.000000, 259.000000, RusToGame("Текущее задание"));//"Текущее задание");
	TextDrawLetterSize(txdAdvisor[7], 0.200000, 1.299998);
	aTextDrawTextSizeEx(txdAdvisor[7], 567.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[7], 1);
	TextDrawColor(txdAdvisor[7], -5373697);
	TextDrawUseBox(txdAdvisor[7], true);
	TextDrawBoxColor(txdAdvisor[7], 505290495);
	TextDrawSetShadow(txdAdvisor[7], 0);
	TextDrawSetOutline(txdAdvisor[7], 0);
	TextDrawBackgroundColor(txdAdvisor[7], -1);
	TextDrawFont(txdAdvisor[7], 1);
	TextDrawSetProportional(txdAdvisor[7], 1);


	txdAdvisor[8] = aTextDrawCreateEx(479.000000, 275.000000, RusToGame("Груз"));//"Груз");
	TextDrawLetterSize(txdAdvisor[8], 0.200000, 1.299998);
	aTextDrawTextSizeEx(txdAdvisor[8], 617.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[8], 1);
	TextDrawColor(txdAdvisor[8], -926365441);
	TextDrawUseBox(txdAdvisor[8], true);
	TextDrawBoxColor(txdAdvisor[8], 673720575);
	TextDrawSetShadow(txdAdvisor[8], 0);
	TextDrawSetOutline(txdAdvisor[8], 0);
	TextDrawBackgroundColor(txdAdvisor[8], -1);
	TextDrawFont(txdAdvisor[8], 1);
	TextDrawSetProportional(txdAdvisor[8], 1);

	txdAdvisor[9] = aTextDrawCreateEx(479.000000, 291.000000, RusToGame("Пункт назначения"));//"Пункт назначения");
	TextDrawLetterSize(txdAdvisor[9], 0.200000, 1.299998);
	aTextDrawTextSizeEx(txdAdvisor[9], 617.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[9], 1);
	TextDrawColor(txdAdvisor[9], -926365441);
	TextDrawUseBox(txdAdvisor[9], true);
	TextDrawBoxColor(txdAdvisor[9], 505290495);
	TextDrawSetShadow(txdAdvisor[9], 0);
	TextDrawSetOutline(txdAdvisor[9], 0);
	TextDrawBackgroundColor(txdAdvisor[9], -1);
	TextDrawFont(txdAdvisor[9], 1);
	TextDrawSetProportional(txdAdvisor[9], 1);

	txdAdvisor[10] = aTextDrawCreateEx(479.000000, 307.000000, RusToGame("Осталось"));//"Осталось");
	TextDrawLetterSize(txdAdvisor[10], 0.200000, 1.299998);
	aTextDrawTextSizeEx(txdAdvisor[10], 617.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[10], 1);
	TextDrawColor(txdAdvisor[10], -926365441);
	TextDrawUseBox(txdAdvisor[10], true);
	TextDrawBoxColor(txdAdvisor[10], 673720575);
	TextDrawSetShadow(txdAdvisor[10], 0);
	TextDrawSetOutline(txdAdvisor[10], 0);
	TextDrawBackgroundColor(txdAdvisor[10], -1);
	TextDrawFont(txdAdvisor[10], 1);
	TextDrawSetProportional(txdAdvisor[10], 1);

	txdAdvisor[11] = aTextDrawCreateEx(479.000000, 323.000000, RusToGame("Доход"));//"Доход");
	TextDrawLetterSize(txdAdvisor[11], 0.200000, 1.299998);
	aTextDrawTextSizeEx(txdAdvisor[11], 617.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[11], 1);
	TextDrawColor(txdAdvisor[11], -926365441);
	TextDrawUseBox(txdAdvisor[11], true);
	TextDrawBoxColor(txdAdvisor[11], 505290495);
	TextDrawSetShadow(txdAdvisor[11], 0);
	TextDrawSetOutline(txdAdvisor[11], 0);
	TextDrawBackgroundColor(txdAdvisor[11], -1);
	TextDrawFont(txdAdvisor[11], 1);
	TextDrawSetProportional(txdAdvisor[11], 1);

	txdAdvisor[12] = aTextDrawCreateEx(479.000000, 355.000000, RusToGame("Остановка для отдыха"));//"Остановка для отдыха");
	TextDrawLetterSize(txdAdvisor[12], 0.200000, 1.299998);
	aTextDrawTextSizeEx(txdAdvisor[12], 617.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[12], 1);
	TextDrawColor(txdAdvisor[12], -926365441);
	TextDrawUseBox(txdAdvisor[12], true);
	TextDrawBoxColor(txdAdvisor[12], 673720575);
	TextDrawSetShadow(txdAdvisor[12], 0);
	TextDrawSetOutline(txdAdvisor[12], 0);
	TextDrawBackgroundColor(txdAdvisor[12], -1);
	TextDrawFont(txdAdvisor[12], 1);
	TextDrawSetProportional(txdAdvisor[12], 1);

	txdAdvisor[13] = aTextDrawCreateEx(492.000000, 371.000000, RusToGame("Отменить текущее задание"));//"Отменить текущее задание");
	TextDrawLetterSize(txdAdvisor[13], 0.250000, 1.500000);
	TextDrawTextSize(txdAdvisor[13], 617.000000, 0.000000);
	TextDrawAlignment(txdAdvisor[13], 1);
	TextDrawColor(txdAdvisor[13], -16776961);
	TextDrawUseBox(txdAdvisor[12], 0);
	TextDrawBoxColor(txdAdvisor[12], 505290495);
	TextDrawSetShadow(txdAdvisor[13], 1);
	TextDrawSetOutline(txdAdvisor[13], 0);
	TextDrawBackgroundColor(txdAdvisor[13], 168430335);
	TextDrawFont(txdAdvisor[13], 1);
	TextDrawSetProportional(txdAdvisor[13], 1);
	TextDrawSetSelectable(txdAdvisor[13], true);
	
//------------------------------------------------------------------------------
}

//загружается из OnGameModeInit (OnCreateTextDraw)
//чтобы было под спидометром
//в процессе они постоянно то скрываются и снова показыватся для обновления изображения
stock advisor_OnPlayerConnect(playerid)
{
//шапка
//------------------------------------------------------------------------------
//после txdTablo

	//здоровье тачки
	pltxdAdvisor[playerid][0] = aCreatePlayerTextDrawEx(playerid, 542.000000, 255.000000, "LD_DUAL:health");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][0], 15.000000, -12.000000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][0], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][0], 0);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][0], 4);

	//топливо
	pltxdAdvisor[playerid][1] = aCreatePlayerTextDrawEx(playerid, 570.000000, 255.000000, "LD_DUAL:power");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][1], 15.000000, -12.000000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][1], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, pltxdAdvisor[playerid][1], true);
	PlayerTextDrawBoxColor(playerid, pltxdAdvisor[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][1], 0);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][1], 4);

	//иконка тачки
	pltxdAdvisor[playerid][2] = aCreatePlayerTextDrawEx(playerid, 505.000000, 230.000000, "Truck");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][2], 0.300000, 0.000000);
	PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][2], 40.000000, 40.000000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][2], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, pltxdAdvisor[playerid][2], true);
	PlayerTextDrawBoxColor(playerid, pltxdAdvisor[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][2], 0x00000000);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][2], 1);
	PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][2], 403);
	PlayerTextDrawSetPreviewRot(playerid, pltxdAdvisor[playerid][2], 0.000000, 0.000000, -90.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][2], 1, 1);//6, 9);

	//иконка полуприцепа
	/*pltxdAdvisor[playerid][3] = aCreatePlayerTextDrawEx(playerid, 270.0, 418.0, " "); //it has to be set with SetText later
    PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][3], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][3], 0x00000000);
	PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][3], 39.0, 39.0);// Text size is the Width:Height
    PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][3], 1, 1); // Set the Linerunner to have colour 6 (Yellow)
    PlayerTextDrawSetPreviewRot(playerid, pltxdAdvisor[playerid][3], 0.0, 0.0, 30.0);//0.0, 0.0, 270.0);
	PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][3], 435); // Display model 403 (Linerunner)
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;*/
//но перед текстом
//------------------------------------------------------------------------------
	gTextDrawShowSpeed[playerid] = false;
	gTextDrawHideSpeed[playerid] = false;

//скорость
	pltxdAdvisor[playerid][4] = aCreatePlayerTextDrawEx(playerid, 479.000000, 243.500000, RusToGame("90 км/ч"));
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][4], 0.200000, 1.250000);
	aPlayerTextDrawTextSizeEx(playerid, pltxdAdvisor[playerid][4], 506.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][4], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, pltxdAdvisor[playerid][4], true);
	PlayerTextDrawBoxColor(playerid, pltxdAdvisor[playerid][4], 0x00000000);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][4], -2139062017);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][4], 1);

//здоровье тачки
 	pltxdAdvisor[playerid][5] = aCreatePlayerTextDrawEx(playerid, 542.000000, 248.000000, "100%");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][5], 0.140000, 0.699998);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][5], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][5], 1);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][5], -16777114);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][5], 1);

//топливо
	pltxdAdvisor[playerid][6] = aCreatePlayerTextDrawEx(playerid, 577.000000, 248.000000, "100 л");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][6], 0.140000, 0.699998);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][6], 2);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][6], 866792294);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][6], 1);

	pltxdAdvisor[playerid][7] = aCreatePlayerTextDrawEx(playerid, 570.000000, 259.000000, "63 773 932 $");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][7], 0.200000, 1.299998);
	aPlayerTextDrawTextSizeEx(playerid, pltxdAdvisor[playerid][7], 617.000000, -10.000000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][7], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][7], -5373697);
	PlayerTextDrawUseBox(playerid, pltxdAdvisor[playerid][7], true);
	PlayerTextDrawBoxColor(playerid, pltxdAdvisor[playerid][7], 252645220);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][7], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][7], 1);

	pltxdAdvisor[playerid][8] = aCreatePlayerTextDrawEx(playerid, 615.000000, 274.000000, RusToGame("Картонная тара(20т)"));//"Картонная тара(20т)");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][8], 0.200000, 1.500000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][8], 3);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][8], -926365441);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][8], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][8], 1);

	pltxdAdvisor[playerid][9] = aCreatePlayerTextDrawEx(playerid, 615.000000, 290.000000, RusToGame("ЛОС-Хантос - Пляж"));//"Лос-Сантос - Пляж");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][9], 0.200000, 1.500000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][9], 3);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][9], -926365441);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][9], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][9], 1);

	pltxdAdvisor[playerid][10] = aCreatePlayerTextDrawEx(playerid, 615.000000, 306.000000,  RusToGame("18 ч 18 мин"));//"18 ч 18 мин");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][10], 0.200000, 1.500000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][10], 3);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][10], 262727594);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][10], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][10], 1);

	pltxdAdvisor[playerid][11] = aCreatePlayerTextDrawEx(playerid, 615.000000, 322.000000, "4 182 $");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][11], 0.200000, 1.500000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][11], 3);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][11], -926365441);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][11], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][11], 1);

	pltxdAdvisor[playerid][12] = aCreatePlayerTextDrawEx(playerid, 479.000000, 339.000000,  RusToGame("ETA: Ср 2:30, 102 км, 1 ч 53 мин"));//"ETA: Ср 2:30, 102 км, 1 ч 53 мин");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][12], 0.200000, 1.299998);
	aPlayerTextDrawTextSizeEx(playerid, pltxdAdvisor[playerid][12], 617.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][12], 1);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][12], -926365441);
	PlayerTextDrawUseBox(playerid, pltxdAdvisor[playerid][12], true);
	PlayerTextDrawBoxColor(playerid, pltxdAdvisor[playerid][12], 673720575);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][12], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][12], 1);

	pltxdAdvisor[playerid][13] = aCreatePlayerTextDrawEx(playerid, 615.000000, 354.000000, RusToGame("16 ч 00 мин"));//"16 ч 00 мин");
	PlayerTextDrawLetterSize(playerid, pltxdAdvisor[playerid][13], 0.200000, 1.500000);
	PlayerTextDrawAlignment(playerid, pltxdAdvisor[playerid][13], 3);
	PlayerTextDrawColor(playerid, pltxdAdvisor[playerid][13], -5373782);
	PlayerTextDrawSetShadow(playerid, pltxdAdvisor[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, pltxdAdvisor[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, pltxdAdvisor[playerid][13], -1);
	PlayerTextDrawFont(playerid, pltxdAdvisor[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, pltxdAdvisor[playerid][13], 1);
	
//метраж
	txdMeterBar[playerid] = CreatePlayerTextDrawEx(playerid, 195.0, 425.0, "0000000");
	PlayerTextDrawLetterSize(playerid, txdMeterBar[playerid], 0.14, 0.7);
	PlayerTextDrawBackgroundColor(playerid, txdMeterBar[playerid], 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdMeterBar[playerid], 1);
	PlayerTextDrawColor(playerid, txdMeterBar[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdMeterBar[playerid], 0);
	PlayerTextDrawSetShadow(playerid, txdMeterBar[playerid], 0);

	txdPager[playerid] = CreatePlayerTextDrawEx(playerid, 412.0, 432.0, RusToGame("Движение по трассе открыто"));
	PlayerTextDrawBackgroundColor(playerid, txdPager[playerid] , 0xFFFFFF66);
	PlayerTextDrawFont(playerid, txdPager[playerid], 1);
	PlayerTextDrawColor(playerid, txdPager[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetOutline(playerid, txdPager[playerid] , 0);
	PlayerTextDrawSetShadow(playerid, txdPager[playerid] , 0);
	PlayerTextDrawLetterSize(playerid, txdPager[playerid],  0.19, 0.85);//0.15, 0.8);
	PlayerTextDrawAlignment(playerid, txdPager[playerid], 1);
}

stock advisor_OnGameModeExit()//для информационной панели начало
{   //вызывается из GameModeInitExitFunc

//для спидометров
	TextDrawDestroyEx(txdAdvisor[9]);
	TextDrawDestroyEx(txdAdvisor[10]);
	TextDrawDestroyEx(txdAdvisor[4]);
	TextDrawDestroyEx(txdAdvisor[5]);
	TextDrawDestroyEx(txdAdvisor[6]);
	TextDrawDestroyEx(txdAdvisor[7]);
	TextDrawDestroyEx(txdAdvisor[8]);
	TextDrawDestroyEx(txdAdvisor[11]);
	TextDrawDestroyEx(txdAdvisor[12]);
	TextDrawDestroyEx(txdAdvisor[13]);
	TextDrawDestroyEx(txdAdvisor[0]);
	TextDrawDestroyEx(txdAdvisor[1]);

	TextDrawDestroyEx(txdAdvisor[2]);
	TextDrawDestroyEx(txdAdvisor[3]);

	/*TextDrawDestroyEx(txdMark20);
	TextDrawDestroyEx(txdMark40);
	TextDrawDestroyEx(txdMark60);
	TextDrawDestroyEx(txdMark80);
	TextDrawDestroyEx(txdMark100);
	TextDrawDestroyEx(txdMark120);
	TextDrawDestroyEx(txdMark140);
	TextDrawDestroyEx(txdMark160);
	TextDrawDestroyEx(txdFrame1);
	TextDrawDestroyEx(txdTablo);
	*/
}


stock advisor_OnPlayerDisconnect(playerid)
{
	if(TextDrawShowSpeed[playerid] == true)
	{//если паказан, то скрыть
//для спидометров
		TextDrawHideForPlayer(playerid, txdAdvisor[9]);
		TextDrawHideForPlayer(playerid, txdAdvisor[13]);

		TextDrawHideForPlayer(playerid, txdAdvisor[0]);
		TextDrawHideForPlayer(playerid, txdAdvisor[1]);
		TextDrawHideForPlayer(playerid, txdAdvisor[2]);
		TextDrawHideForPlayer(playerid, txdAdvisor[3]);
		TextDrawHideForPlayer(playerid, txdAdvisor[6]);
		TextDrawHideForPlayer(playerid, txdAdvisor[7]);
		TextDrawHideForPlayer(playerid, txdAdvisor[8]);
		TextDrawHideForPlayer(playerid, txdAdvisor[11]);
		TextDrawHideForPlayer(playerid, txdAdvisor[12]);
		TextDrawHideForPlayer(playerid, txdAdvisor[10]);
		TextDrawHideForPlayer(playerid, txdAdvisor[4]);
		TextDrawHideForPlayer(playerid, txdAdvisor[5]);
		
		
		/*TextDrawHideForPlayer(playerid, txdMark20);
		TextDrawHideForPlayer(playerid, txdMark40);
		TextDrawHideForPlayer(playerid, txdMark60);
		TextDrawHideForPlayer(playerid, txdMark80);
		TextDrawHideForPlayer(playerid, txdMark100);
		TextDrawHideForPlayer(playerid, txdMark120);
		TextDrawHideForPlayer(playerid, txdMark140);
		TextDrawHideForPlayer(playerid, txdMark160);
		TextDrawHideForPlayer(playerid, txdFrame1);
		TextDrawHideForPlayer(playerid, txdTablo);
		*/
		

		
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][13]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][10]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][9]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][11]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][8]);
		//PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][3]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][2]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][7]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][4]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][12]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][0]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][1]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][5]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][6]);
		
		PlayerTextDrawHide(playerid, txdMeterBar[playerid]);
		PlayerTextDrawShow(playerid, txdPager[playerid]);
		TextDrawShowSpeed[playerid] = false;
	}
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][4]);

	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][13]);
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][10]);
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][9]);
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][11]);

	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][5]);
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][6]);

	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][12]);

	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][1]);
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][0]);

	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][8]);
	//PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][3]);
	PlayerTextDrawDestroyEx(playerid, pltxdAdvisor[playerid][2]);
	
	PlayerTextDrawDestroyEx(playerid, txdMeterBar[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdPager[playerid]);
}

stock advisor_OnPlayerStateChange(playerid, newstate, oldstate)
{
//if(!IsPlayerInAnyVehicle(playerid)) return 1;
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{   //если игрок покинул водительское место
	    if(CarStatus[LastCar[playerid]][st_engine] == VEHICLE_PARAMS_ON)//перестанет пропадать спидометр
	    {//если двигатель включен
			gTextDrawHideSpeed[playerid] = true;
		}
	}
//------------------------------------------------------------------------------
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
			GameTextForPlayerEx(playerid, "~n~~n~~n~Press ~b~~k~~TOGGLE_SUBMISSIONS~ ~n~~g~|~w~switch ON Engine~g~|", 1000, 1);
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
	AdvisorOnOff(playerid);
}


stock advisor_OnPlayerSpawn(playerid)
{

	format(strings, sizeof(strings), "%s $", NiceMoney(63773932, " ") );//PlayerInfo[playerid][pBank]
	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][7], strings);

	new a_hour, a_minute;
	gettime(a_hour, a_minute, _);//Получает текущее время на сервере, которое запишется в переменные &hour, &minute и &second.
	//SendClientMessage(playerid, COLOR_GREY, GetWeekDay());
	format(strings, sizeof(strings), "%s_%02d:%02d", GetWeekDay(), a_hour, a_minute);
	//format(strings, sizeof(strings), "%s", GetWeekDay(23, 3, 2020));
	TextDrawSetStringEx(txdAdvisor[6], strings);
	//SendClientMessage(playerid, COLOR_GREY, strings);

	gTextDrawShowSpeed[playerid] = false;
	//AdvisorOnOff(playerid);//присутсвует в advisor_OnPlayerStateChange
}

stock AdvisorOnOff(playerid)
{
	if(gTextDrawShowSpeed[playerid] == true && gTextDrawHideSpeed[playerid] == false && TextDrawShowSpeed[playerid] == false)
	{//если есть сигнал на показ, нет сигнала на скрытие и текстдров не показан
		//TextDrawHideForPlayer(playerid, txtServerName);//должно загрузиться раньше чем спидометр
//для спидометров
		TextDrawShowForPlayer(playerid, txdAdvisor[0]);
		TextDrawShowForPlayer(playerid, txdAdvisor[1]);
		TextDrawShowForPlayer(playerid, txdAdvisor[2]);
		TextDrawShowForPlayer(playerid, txdAdvisor[3]);
		TextDrawShowForPlayer(playerid, txdAdvisor[4]);
		//TextDrawShowForPlayer(playerid, txdAdvisor[5]);
		
		TextDrawShowForPlayer(playerid, txdAdvisor[6]);
		TextDrawShowForPlayer(playerid, txdAdvisor[7]);
		TextDrawShowForPlayer(playerid, txdAdvisor[8]);
		TextDrawShowForPlayer(playerid, txdAdvisor[9]);
		TextDrawShowForPlayer(playerid, txdAdvisor[10]);
		TextDrawShowForPlayer(playerid, txdAdvisor[11]);
		TextDrawShowForPlayer(playerid, txdAdvisor[12]);
		TextDrawShowForPlayer(playerid, txdAdvisor[13]);
		
		/*TextDrawShowForPlayer(playerid, txdMark20);
		TextDrawShowForPlayer(playerid, txdMark40);
		TextDrawShowForPlayer(playerid, txdMark60);
		TextDrawShowForPlayer(playerid, txdMark80);
		TextDrawShowForPlayer(playerid, txdMark100);
		TextDrawShowForPlayer(playerid, txdMark120);
		TextDrawShowForPlayer(playerid, txdMark140);
		TextDrawShowForPlayer(playerid, txdMark160);
		TextDrawShowForPlayer(playerid, txdFrame1);
		TextDrawShowForPlayer(playerid, txdTablo);*/

//------------------------------------------------------------------------------
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][0]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][1]);

		//aPlayerTextDrawTextSizeEx(playerid, pltxdAdvisor[playerid][2], 40.0, 40.0);
		//PlayerTextDrawSetPreviewRot(playerid, pltxdAdvisor[playerid][2], 0.0, 0.0, -90.0, 1.0);//0.0, 0.0, 0.0);
		PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][2], VehInfo[nCarID[playerid]][cColor1], VehInfo[nCarID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
		PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][2], nCarModel[playerid]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][2]);

		/*if(	IsTrailerAttachedToVehicle(nCarID[playerid]) )
		{
			PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][3], VehInfo[nTrailerID[playerid]][cColor1], VehInfo[nTrailerID[playerid]][cColor2]);
			PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][3], nTrailerModel[playerid]);//435);//nTrailerModel[playerid]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][3]);
		}*/
		
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][4]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][5]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][6]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][7]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][8]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][9]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][10]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][11]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][12]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][13]);
		PlayerTextDrawShow(playerid, txdMeterBar[playerid]);
		PlayerTextDrawShow(playerid, txdPager[playerid]);

		TextDrawShowSpeed[playerid] = true;//текстдров показан
		gTextDrawShowSpeed[playerid] = false;//флаг разрешения опустили
	}
	else if(gTextDrawShowSpeed[playerid] == false && gTextDrawHideSpeed[playerid] == true && TextDrawShowSpeed[playerid] == true)
	{//если есть разрешение на скрытие и текстдров показан
		//TextDrawShowForPlayer(playerid, txtServerName);//должно загрузиться раньше чем спидометр
//для спидометров
		TextDrawHideForPlayer(playerid, txdAdvisor[0]);
		TextDrawHideForPlayer(playerid, txdAdvisor[1]);
		TextDrawHideForPlayer(playerid, txdAdvisor[2]);
		TextDrawHideForPlayer(playerid, txdAdvisor[3]);
		TextDrawHideForPlayer(playerid, txdAdvisor[4]);
		//TextDrawHideForPlayer(playerid, txdAdvisor[5]);
		
		TextDrawHideForPlayer(playerid, txdAdvisor[6]);
		TextDrawHideForPlayer(playerid, txdAdvisor[7]);
		TextDrawHideForPlayer(playerid, txdAdvisor[8]);
		TextDrawHideForPlayer(playerid, txdAdvisor[9]);
		TextDrawHideForPlayer(playerid, txdAdvisor[10]);
		TextDrawHideForPlayer(playerid, txdAdvisor[11]);
		TextDrawHideForPlayer(playerid, txdAdvisor[12]);
		TextDrawHideForPlayer(playerid, txdAdvisor[13]);
		
		/*TextDrawHideForPlayer(playerid, txdMark20);
		TextDrawHideForPlayer(playerid, txdMark40);
		TextDrawHideForPlayer(playerid, txdMark60);
		TextDrawHideForPlayer(playerid, txdMark80);
		TextDrawHideForPlayer(playerid, txdMark100);
		TextDrawHideForPlayer(playerid, txdMark120);
		TextDrawHideForPlayer(playerid, txdMark140);
		TextDrawHideForPlayer(playerid, txdMark160);
		TextDrawHideForPlayer(playerid, txdFrame1);
		TextDrawHideForPlayer(playerid, txdTablo);*/

//------------------------------------------------------------------------------
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][0]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][1]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][2]);
		//PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][3]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][4]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][5]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][6]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][7]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][8]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][9]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][10]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][11]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][12]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][13]);
		PlayerTextDrawHide(playerid, txdMeterBar[playerid]);
		PlayerTextDrawHide(playerid, txdPager[playerid]);
		
		TextDrawShowSpeed[playerid] = false;
		gTextDrawHideSpeed[playerid] = false;
	}
    else
    {
		gTextDrawShowSpeed[playerid] = false;
		gTextDrawHideSpeed[playerid] = false;
	}
}


//##############################################################################//
//для расхода топлива
//stock SystemConsuptionFuel(playerid)//счётчик метража
stock Odometer(playerid)//счётчик метража
{//запусается из advisor_OneSecondTimers
	//if(spectateid[playerid] != MAX_PLAYERS-1) return 1;
	//if( GetPVarInt(playerid, "gStatusRegistration") ) return 1;
	//if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount")) return 1;
    //new speed;
   	new carid = nCarID[playerid];
    new Float: distance, Float:x,Float:y,Float:z;
    new curstate = CurState[playerid];
	//if(!IsPlayerInAnyVehicle(playerid)) return 1;//дублируется в advisor_OneSecondTimers(playerid)
	if(curstate != PLAYER_STATE_DRIVER) return 1;//чтобы метраж не подсчитывал по одной тачки от срабатывания у двух игроков в машине

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
		fuel_FuelConsumption(playerid, distance);//система расхода топлива от пройденного расстояния
#endif

	}
	VehPos[carid][0] = x;
	VehPos[carid][1] = y;
	VehPos[carid][2] = z;
	return 1;
}


/*stock advisor_OnDialogResponse(playerid)
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

stock advisor_OnTrailerAttached(playerid, vehicleid, trailerid)
{
	#pragma unused playerid
	#pragma unused vehicleid
	#pragma unused trailerid
	//gTextDrawShowSpeed[playerid] = true;
	
	/*if(trailerid != 0)
	{
		PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][3], VehInfo[trailerid][cColor1], VehInfo[trailerid][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
		PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][3], nTrailerModel[playerid]);
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][3]);
	}
	else
	{
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][3]);
	}*/
}


///тяжёлая ф-ия = 381 ms
//stock OnPlayerSpeedTimer(playerid)//для информационной панели начало
stock advisor_OneSecondTimers(playerid)
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
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][0]);
		PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][0], 15, -(VehicleHealth*12.0/100));
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][0]);
		format(strtmp, sizeof(strtmp), "%d%%", VehicleHealth);
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][5], strtmp);
		//--------------------------------------------------------------------------
//ТОПЛИВО
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][1]);
		PlayerTextDrawTextSize(playerid, pltxdAdvisor[playerid][1], 15, -floatround(VehInfo[nCarID[playerid]][cFuel]*12.0/VehicleArray[nCarModel[playerid]-400][GasMax]) );
		PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][1]);
		format(strtmp, sizeof(strtmp), "%.0f %s", VehInfo[nCarID[playerid]][cFuel], RusToGame("л"));
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][6], strtmp);
		//--------------------------------------------------------------------------
//МЕТРАЖ
		format(strtmp, sizeof(strtmp), "%07d%s",VehInfo[nCarID[playerid]][cDist], RusToGame("км"));//"~g~KMH:~y~%d"
		PlayerTextDrawSetStringEx(playerid, txdMeterBar[playerid], strtmp);

//СКОРОСТЬ
		format(strtmp, sizeof(strtmp), "%03d%s", velocity, RusToGame("км/ч"));//"~g~KMH:~y~%d"
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][4], strtmp);
	}
//==============================================================================
	TestLog(OPTIM, "OnPlayerSpeedTimer", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}




stock CMD_show(playerid)
{
	#pragma unused playerid
/*
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

		    //PlayerTextDrawShow(playerid, txdBankBarDisp[playerid]);//для банковского счёта
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][7]);

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
			TextDrawShowForPlayer(playerid, txdAdvisor[0]);
			TextDrawShowForPlayer(playerid, txdAdvisor[1]);
			TextDrawShowForPlayer(playerid, txdAdvisor[2]);
			TextDrawShowForPlayer(playerid, txdAdvisor[3]);

			if(	IsTrailerAttachedToVehicle(nCarID[playerid]) )
			{
				//TextDrawSetPreviewVehCol(pltxdAdvisor[playerid][3], VehInfo[nTrailerID[playerid]][cColor1], VehInfo[nTrailerID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
				//TextDrawSetPreviewModel(pltxdAdvisor[playerid][3], nTrailerModel[playerid]);
				//TextDrawShowForPlayer(playerid, pltxdAdvisor[playerid][3]);
				PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][3], VehInfo[nTrailerID[playerid]][cColor1], VehInfo[nTrailerID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
				PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][3], nTrailerModel[playerid]);
				PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][3]);
			}

			//aTextDrawTextSizeEx(pltxdAdvisor[playerid][2], 26.0, 32.0);
			//TextDrawSetPreviewRot(pltxdAdvisor[playerid][2], 0.0, 0.0, 0.0);
			//TextDrawSetPreviewVehCol(pltxdAdvisor[playerid][2], VehInfo[nCarID[playerid]][cColor1], VehInfo[nCarID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
			//TextDrawSetPreviewModel(pltxdAdvisor[playerid][2], nCarModel[playerid]);
			//TextDrawShowForPlayer(playerid, pltxdAdvisor[playerid][2]);
			aPlayerTextDrawTextSizeEx(playerid, pltxdAdvisor[playerid][2], 26.0, 32.0);
			PlayerTextDrawSetPreviewRot(playerid, pltxdAdvisor[playerid][2], 0.0, 0.0, 0.0);
			PlayerTextDrawSetPreviewVehCol(playerid, pltxdAdvisor[playerid][2], VehInfo[nCarID[playerid]][cColor1], VehInfo[nCarID[playerid]][cColor2]); // Set the Linerunner to have colour 6 (Yellow)
			PlayerTextDrawSetPreviewModel(playerid, pltxdAdvisor[playerid][2], nCarModel[playerid]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][2]);

			TextDrawShowForPlayer(playerid, txdAdvisor[6]);
			TextDrawShowForPlayer(playerid, txdAdvisor[7]);
			TextDrawShowForPlayer(playerid, txdAdvisor[8]);

			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][13]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][10]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][9]);

			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][4]);
			PlayerTextDrawShow(playerid, txdMeterBar[playerid]);
			
			TextDrawShowForPlayer(playerid, txdAdvisor[9]);

			//TextDrawShowForPlayer(playerid, pltxdAdvisor[playerid][0]);
			//TextDrawShowForPlayer(playerid, pltxdAdvisor[playerid][1]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][0]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][1]);

			TextDrawShowForPlayer(playerid, txdAdvisor[10]);
			TextDrawShowForPlayer(playerid, txdAdvisor[4]);

			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][5]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][6]);

			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][12]);
			PlayerTextDrawShow(playerid, pltxdAdvisor[playerid][11]);
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

	    //PlayerTextDrawHide(playerid, txdBankBarDisp[playerid]);//для банковского счёта
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][7]);

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
		TextDrawHideForPlayer(playerid, txdAdvisor[0]);
		TextDrawHideForPlayer(playerid, txdAdvisor[1]);
		TextDrawHideForPlayer(playerid, txdAdvisor[2]);
		TextDrawHideForPlayer(playerid, txdAdvisor[3]);
//#endif

		PlayerTextDrawHide(playerid, txdNameItems[playerid]);
		if( IsTrailerAttachedToVehicle(LastCar[playerid]) )
		{
			//TextDrawHideForPlayer(playerid, pltxdAdvisor[playerid][3]);
			PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][3]);
		}
		//TextDrawHideForPlayer(playerid, pltxdAdvisor[playerid][2]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][2]);

		TextDrawHideForPlayer(playerid, txdAdvisor[6]);
		TextDrawHideForPlayer(playerid, txdAdvisor[7]);
		TextDrawHideForPlayer(playerid, txdAdvisor[8]);

		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][13]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][10]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][9]);

		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][4]);
		PlayerTextDrawHide(playerid, txdMeterBar[playerid]);
		TextDrawHideForPlayer(playerid, txdAdvisor[9]);

		//TextDrawHideForPlayer(playerid, pltxdAdvisor[playerid][0]);
		//TextDrawHideForPlayer(playerid, pltxdAdvisor[playerid][1]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][0]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][1]);

		TextDrawHideForPlayer(playerid, txdAdvisor[10]);
		TextDrawHideForPlayer(playerid, txdAdvisor[4]);

		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][5]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][6]);

		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][12]);
		PlayerTextDrawHide(playerid, pltxdAdvisor[playerid][11]);

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
*/
}

