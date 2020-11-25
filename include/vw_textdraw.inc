/*
 *            vw_textdraw v1.3
 *       (c) Copyright 2009-2013 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 02.09.2013
 * @update    : 17.11.2013
 *
 * This file is provided as is (no warranties).
 *
 */
//#include "../include/vw_vehicles"

//#include <a_samp>
#include "../include/textdraw/vw_texture.inc"
#include "../include/textdraw/txd_Progress.inc"
#include "../include/textdraw/txd_battery.inc"


new PlayerInZone[MAX_PLAYERS];//номер зоны из массива zones в которой находится игрок для УСТАНОВКИ ИКОНОК НА КАРТЕ
new PlayerInRegion[MAX_PLAYERS];
//##############################################################################//
//                                                                              //
//                          ИДЕНТИФИКАТОРЫ TEXTDRAWS                            //
//                                                                              //
//##############################################################################//

new PlayerText:txdCarTime[MAX_PLAYERS];//объявляем структуру для времени и дерби

new Text:txdTimeDisp,//объявляем структуру для часов и минут
	//Text:txdSecondsTime,//объявляем структуру для секунд
	Text:txdDate,//объявляем структуру для даты
	//Text:txtServerName,//объявляем структуру для названия сервера
	PlayerText:txdBankDisp[MAX_PLAYERS];//объявляем структуру для показа денег в банке

//для спидометров
new	PlayerText:txdInsurances[MAX_PLAYERS],
	PlayerText:txdPositionOfTotal[MAX_PLAYERS];
//new Text:txd_hbarr;
//------------------------------------------------------------------------------
//для гонок
new PlayerText:txdRacePosition[MAX_PLAYERS],
	PlayerText:txdPositionAppend[MAX_PLAYERS],
	Text:txdTotalRacers,
	PlayerText:txdRaceTime[MAX_PLAYERS],
	Text:txdTotalMembers;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
new Text:txdBlind; //для затемнения экрана
//------------------------------------------------------------------------------
//для системной панели
new Text: txdSystemMessage;
#define MAX_LINES 50 // Максимальное кол-во строк.
#define MAX_LENGHT 150 //128+22 Максимальное кол-во символов в одной строчки.
new AdminMessageString[MAX_LINES][MAX_LENGHT];
//------------------------------------------------------------------------------
//для бегущей строки
new Text: txdBegunok;// это массив элементов текстдрав
//------------------------------------------------------------------------------
new PlayerText:txdPlayerArmour[MAX_PLAYERS];
new PlayerText:txdPlayerHealth[MAX_PLAYERS];

new PlayerText:txdSecondsTime[MAX_PLAYERS];//объявляем структуру для секунд

new PlayerText:txdPlayerZone[MAX_PLAYERS];
new PlayerText:txdPlayerRegion[MAX_PLAYERS];
//------------------------------------------------------------------------------
new Text:txdCSTime;//для контры
new Text:Intro[12];//для вступительного ролика

new Text:TD_LOGO[4];

//чек клиента на руссик
//new check_rus_td[MAX_PLAYERS];
//new Text:check_rus_TD[2];
//new Text:SELECT_SPAWN_TD[8];
//##############################################################################//
//                                                                              //
//                               ТРИГЕРЫ TEXTDRAWS                              //
//                                                                              //
//##############################################################################//
//дают разрешение на показ или скрытие
//всё время должны быть на false
new bool:gTextDrawShowCarTime[MAX_PLAYERS];
new bool:gTextDrawShowRace[MAX_PLAYERS];
new bool:gTextDrawShowCS[MAX_PLAYERS];
new bool:gTextDrawShowClock[MAX_PLAYERS];


new bool:gTextDrawShowBlind[MAX_PLAYERS];
new bool:gTextDrawShowMessage[MAX_PLAYERS];
new bool:gTextDrawShowBegunok;
new bool:gTextDrawShowArmour[MAX_PLAYERS];
new bool:gTextDrawShowChat[MAX_PLAYERS];

new bool:gTextDrawHideCarTime[MAX_PLAYERS];
new bool:gTextDrawHideRace[MAX_PLAYERS];
new bool:gTextDrawHideCS[MAX_PLAYERS];
new bool:gTextDrawHideClock[MAX_PLAYERS];


new bool:gTextDrawHideBlind[MAX_PLAYERS];
new bool:gTextDrawHideMessage[MAX_PLAYERS];
new bool:gTextDrawHideBegunok;
new bool:gTextDrawHideArmour[MAX_PLAYERS];
new bool:gTextDrawHideChat[MAX_PLAYERS];
new bool:gHide[MAX_PLAYERS];//для показа текстдров

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
//new bool:TextDrawShowSpeed[MAX_PLAYERS];//индикатор состояния текстдрова
new bool:TextDrawShowCarTime[MAX_PLAYERS];
//new bool:TextDrawShowRace[MAX_PLAYERS];
new bool:TextDrawShowCS[MAX_PLAYERS];
new bool:TextDrawShowClock[MAX_PLAYERS];

new bool:TextDrawShowBlind[MAX_PLAYERS];
new bool:TextDrawShowMessage[MAX_PLAYERS];
new bool:TextDrawShowBegunok;
new bool:TextDrawShowArmour[MAX_PLAYERS];
new bool:TextDrawShowChat[MAX_PLAYERS];


//##############################################################################//
//                                                                              //
//                             СЧЁТЧИКИ TEXTDRAWS                               //
//                                                                              //
//##############################################################################//
//new TEXT_DRAWS_COUNTER;//счётчик загруженных текстдров см. vw_config
//new PLAYER_TEXT_DRAWS_COUNTER[MAX_PLAYERS];//счётчик загруженных текстдров см. vw_config

//##############################################################################//
//                                                                              //
//                             ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ                            //
//                                                                              //
//##############################################################################//
//ф-ии которые на конце имеют Ex, внутри которых сразу инициализируются переменные
forward Text:TextDrawCreateEx(Float:x, Float:y, text[]);
public Text:TextDrawCreateEx(Float:x, Float:y, text[])
//stock Text:TextDrawCreateEx(Float:x, Float:y, text[])
{
	TEXT_DRAWS_COUNTER ++;
	return TextDrawCreate(x, y, text);
}

stock TextDrawDestroyEx(Text:text)
{
	TEXT_DRAWS_COUNTER --;
	return TextDrawDestroy(text);
}
	
stock TextDrawSetStringEx(Text:text, string[])
{
	if (string[0] == '\0' || string[0] == '\1' && string[1] == '\0')
	{
		return TextDrawSetString(text, " ");
	}
	else
	{
		return TextDrawSetString(text, string);
	}
}

stock TextDrawTextSizeEx(playerid, Text:text, Float:x, Float:y)
{
	TextDrawHideForPlayer(playerid, text);
	TextDrawTextSize(text, x, y);
	TextDrawShowForPlayer(playerid, text);
}

stock TextDrawSetPreviewModelEx(playerid, Text:text, modelindex)
{
	TextDrawHideForPlayer(playerid, text);
	TextDrawSetPreviewModel(text, modelindex);
	TextDrawShowForPlayer(playerid, text);
}

//------------------------------------------------------------------------------
forward PlayerText:CreatePlayerTextDrawEx(playerid, Float:x, Float:y, text[]);
public PlayerText:CreatePlayerTextDrawEx(playerid, Float:x, Float:y, text[])
//stock PlayerText:CreatePlayerTextDrawEx(playerid, Float:x, Float:y, text[])
{
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	return CreatePlayerTextDraw(playerid, x, y, text);
}

stock PlayerTextDrawDestroyEx(playerid, PlayerText:text)
{
	if(text == PlayerText:INVALID_TEXT_DRAW) return 0;
	PLAYER_TEXT_DRAWS_COUNTER[playerid] --;
	PlayerTextDrawDestroy(playerid, text);
	return INVALID_TEXT_DRAW;
}

stock PlayerTextDrawSetStringEx(playerid, PlayerText:text, string[])
{
	if (string[0] == '\0' || string[0] == '\1' && string[1] == '\0')
	{
		format(strings, sizeof(strings), "PlayerTextDrawSetStringEx: %s[%d] '%s'", PlayerName(playerid), playerid, string);
		Log(ERROR, strings);
		return PlayerTextDrawSetString(playerid, text, " ");
	}
	else
	{
		return PlayerTextDrawSetString(playerid, text, string);
	}
}

stock PlayerTextDrawBackgroundColorEx(playerid, PlayerText:text, color)
{
	PlayerTextDrawHide(playerid, text);
	PlayerTextDrawBackgroundColor(playerid, text, color);
	PlayerTextDrawShow(playerid, text);
}

stock PlayerTextDrawColorEx(playerid, PlayerText:text, color)
{
	PlayerTextDrawHide(playerid, text);
	PlayerTextDrawColor(playerid, text, color);
	PlayerTextDrawShow(playerid, text);
}


//##############################################################################//
//                                                                              //
//                                БЛОКИ АВТОЗАМЕНЫ                              //
//                                                                              //
//##############################################################################//
stock TextDrawStyle(Text: txtInit)
{
	TextDrawLetterSize(txtInit, 0.14, 0.7);
	TextDrawBackgroundColor(txtInit, COLOR_BACKGROUND);
	TextDrawFont(txtInit, 1);
	TextDrawColor(txtInit, COLOR_TEXTDRAW);
	TextDrawSetOutline(txtInit, 0);
	TextDrawSetShadow(txtInit, 0);
}

stock PlayerTextDrawStyle(playerid, PlayerText: txtInit)
{
	PlayerTextDrawLetterSize(playerid, txtInit, 0.14, 0.7);
	PlayerTextDrawBackgroundColor(playerid, txtInit, COLOR_BACKGROUND);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawColor(playerid, txtInit, COLOR_WHITE);
	PlayerTextDrawSetOutline(playerid, txtInit, 0);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
}
/*
stock Init_txdProgressObv(Text:txtInit)
{
	TextDrawUseBox(txtInit, 1);
	TextDrawBoxColor(txtInit, 0x00000077);
	TextDrawTextSize(txtInit, 103.0,0.0);
	TextDrawLetterSize(txtInit, 0.0, 0.8);
}
stock Init_txdProgress(Text:txtInit)
{
	TextDrawUseBox(txtInit, 1);
	TextDrawBoxColor(txtInit,0x60646033);
	TextDrawTextSize(txtInit,105.0,0.0);
	TextDrawLetterSize(txtInit, 0.0, 0.3);
}
stock Init_txdMark(Text:txtInit)
{
	TextDrawBackgroundColor(txtInit, 0x0000ff66);
	TextDrawFont(txtInit, 2);
	TextDrawLetterSize(txtInit, 0.3, 1.0);
	TextDrawColor(txtInit, COLOR_WHITE);
	TextDrawSetOutline(txtInit, 1);
}

stock Init_txdBar(Text:txtInit)
{
	TextDrawFont(txtInit, TEXT_DRAW_FONT_SPRITE_DRAW);
	//TextDrawColor(txtInit, 0xFFFFFFFF);
	TextDrawTextSize(txtInit, 15, -12);//4, -90);
	TextDrawAlignment(txtInit, 1);
}
stock PlayerInit_txdBar(playerid, PlayerText:txtInit)
{
	PlayerTextDrawFont(playerid, txtInit, TEXT_DRAW_FONT_SPRITE_DRAW);
	//PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);
	PlayerTextDrawTextSize(playerid, txtInit, 15, -12);//4, -90);
	PlayerTextDrawAlignment(playerid, txtInit, 1);
}
*/
//##############################################################################//
//                                                                              //
//                               ФУНКЦИИ TEXTDRAWS                              //
//                                                                              //
//##############################################################################//


// Creates a model preview sprite
// Создает ячейку предварительного просмотра модели
/*PlayerText:CreateModelPreviewTextDraw(playerid, modelindex, color1, color2, Float:Xpos, Float:Ypos, Float:width, Float:height)
{
	//txdVehicleIcon[playerid] = CreatePlayerTextDrawEx(playerid, txd_X+168.0, txd_Y-4.0, " ");
    //PlayerTextDrawFont(playerid, txdVehicleIcon[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	//PlayerTextDrawBackgroundColor(playerid, txdVehicleIcon[playerid], 0x00000000);
	//PlayerTextDrawTextSize(playerid, txdVehicleIcon[playerid], 26.0, 32.0);
	//PlayerTextDrawSetPreviewVehCol(playerid, txdVehicleIcon[playerid], 6, 9);
    //PlayerTextDrawSetPreviewRot(playerid, txdVehicleIcon[playerid], 0.0, 0.0, 30.0);//0.0, 0.0, 0.0);
	//PlayerTextDrawSetPreviewModel(playerid, txdVehicleIcon[playerid], 403);
	//PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

    new PlayerText:txtPlayerSprite = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, " "); // it has to be set with SetText later
    PlayerTextDrawFont(playerid, txtPlayerSprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColor(playerid, txtPlayerSprite, 0xFFFFFFFF);
    PlayerTextDrawBackgroundColor(playerid, txtPlayerSprite, 0x88888866);//0x00000000);//0x88888899);0xAFAFAFAA
    PlayerTextDrawTextSize(playerid, txtPlayerSprite, width, height); // Text size is the Width:Height
    PlayerTextDrawSetPreviewModel(playerid, txtPlayerSprite, modelindex);
   	PlayerTextDrawSetPreviewRot(playerid,txtPlayerSprite, 0.0, 0.0, 30.0);
	PlayerTextDrawSetPreviewVehCol(playerid,txtPlayerSprite, color1, color2);
    //PlayerTextDrawSetSelectable(playerid, txtPlayerSprite, 1);

    PlayerTextDrawShow(playerid,txtPlayerSprite);
    return txtPlayerSprite;
}*/



//------------------------------------------------
stock OnPlayerTextDrawHide(playerid)
{//вызывается из OnPlayerDisconnect
	if(TextDrawShowClock[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdTimeDisp);//для часиков
		//TextDrawHideForPlayer(playerid, txdSecondsTime);
		TextDrawHideForPlayer(playerid, txdDate);
		//TextDrawHideForPlayer(playerid, txtServerName);

		PlayerTextDrawHide(playerid, txdBankDisp[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);
		
		PlayerTextDrawHide(playerid, txdSecondsTime[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerZone[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerRegion[playerid]);

		TextDrawShowClock[playerid] = false;
	}

	if(TextDrawShowCarTime[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdCarTime[playerid]);
		TextDrawShowCarTime[playerid] = false;
	}
	if(TextDrawShowBegunok == true)//для бегущей строки
	{
		TextDrawHideForPlayer(playerid, txdBegunok);
		//TextDrawShowBegunok = false;//т.к. бегущая строка не должна пропадать
	}
	if(TextDrawShowMessage[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdSystemMessage);
		TextDrawShowMessage[playerid] = false;
	}
	/*if(TextDrawShowRace[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdRacePosition[playerid]);//для гонок
		PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
		TextDrawHideForPlayer(playerid, txdTotalRacers);
		PlayerTextDrawHide(playerid, txdRaceTime[playerid]);
		TextDrawShowRace[playerid] = false;
	}*/
	if(TextDrawShowCS[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdRacePosition[playerid]);
		PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
		TextDrawHideForPlayer(playerid, txdTotalMembers);
		TextDrawHideForPlayer(playerid, txdCSTime);
		TextDrawShowCS[playerid] = false;
	}

	if(TextDrawShowArmour[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdPlayerArmour[playerid]);
	
		TextDrawShowArmour[playerid] = false;
	}
	/*if(TextDrawShowChat[playerid] == true)
	{
		PlayerTextDrawShow(playerid, txdCHAT[playerid]);
		TextDrawShowChat[playerid] = false;
	}*/
	gHide[playerid] = false;
}

/*stock OnPlayerDestroyTextDraw(playerid)//загружается из GameModeInitExitFunc (OnDestroyTextDraw)
{//удаление глобальных TextDraw созданных для игрока



//удаление персональных см. OnPlayerUnLoadTextDraw(playerid)
}*/

stock OnPlayerUnLoadTextDraw(playerid)//уничтожаем только те, что созданы для игрока при входе в игру
{   //вызывается из OnPlayerDisconnect
//ВНИММАНИЕ: а ты знаешь что команда TextDrawDestroyEx() влияет на все текстдровы которые видит игрок,
// т.е. уничтожает заданый и делает невидимыми все остальные. Делай выводы. wiki
	PlayerTextDrawDestroyEx(playerid, txdCarTime[playerid]);
	//OnPlayerDestroyTextDraw(playerid);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//для гонок
	PlayerTextDrawDestroyEx(playerid, txdRaceTime[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdRacePosition[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdPositionAppend[playerid]);
//для денег в банке
	PlayerTextDrawDestroyEx(playerid, txdBankDisp[playerid]);

	PlayerTextDrawDestroyEx(playerid, txdPlayerHealth[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdPlayerArmour[playerid]);
	
	PlayerTextDrawDestroyEx(playerid, txdSecondsTime[playerid]);
	
	PlayerTextDrawDestroyEx(playerid, txdPlayerZone[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdPlayerRegion[playerid]);
 	return 1;
}


stock textdraw_OnPlayerKeySelect(playerid, newkeys, oldkeys)
{
//#define KEY_FOOT_LOOK_BEHIND	KEY_LOOK_BEHIND		~k~~PED_LOOKBEHIND~ 		//512 - Смотреть назад (Mouse3 - MButton)

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;
	if( PRESSED(KEY_LOOK_BEHIND))
	{
		CancelSelectTextDraw(playerid);
        SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Вы вышли из режима {FF0000}'Clicked TextDraw' !");
	}
	else if( RELEASED(KEY_LOOK_BEHIND))
	{
        SelectTextDraw(playerid, COLOR_LIGHTYELLOW);//нельзя использовать совместо с показам текстдровов, т.к. они прячутся
        SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Вы вошли в режим {FF0000}'Clicked TextDraw'{33AA33}. Пожалуйста выбирите TextDraw!");
        SendClientMessage(playerid, COLOR_GREY, "   Для выходи из режима {FF0000}'Clicked TextDraw'{AFAFAF}(USE: ESC)!");
	}
	return 1;	
}

/*stock OnPlayerTextDrawShow(playerid)
{//не используется
	gTextDrawShowSpeed[playerid] = true;
	gTextDrawShowCarTime[playerid] = true;
	gTextDrawShowRace[playerid] = true;
	gTextDrawShowCS[playerid] = true;
	gTextDrawShowClock[playerid] = true;
	gTextDrawShowScale[playerid] = true;
	gTextDrawShowBattery[playerid] = true;
	gTextDrawShowBlind[playerid] = true;
	gTextDrawShowMessage[playerid] = true;
	gTextDrawShowBegunok = true;
	gTextDrawShowArmour[playerid] = true;
	gTextDrawShowChat[playerid] = true;
}*/

/*
public TextDrawTimer()//запускается каждую секунду сразу при старте мода
{
	for(new playerid=0; playerid<GetMaxPlayers(); playerid++)
	{
		if( !IsPlayerConnected(playerid) ) continue;
		if( IsPlayerNPC(playerid) ) continue;
		OnPlayerTextDrawStateChange(playerid);
	}
}*/

stock OnPlayerTextDrawStateChange(playerid)
{//вызывается из OnPlayerSpawn и не только
//ИНФОРМИРОВАНИЕ
//format(strings, sizeof(strings), "OnPlayerTextDrawStateChange(playerid:%d) ", playerid);
//SendClientMessage(playerid, COLOR_PURPLE, strings);
//format(strings, sizeof(strings), "gTextDrawShowClock:%d TextDrawShowClock:%d ", gTextDrawShowClock[playerid], TextDrawShowClock[playerid]);
//SendClientMessage(playerid, COLOR_PURPLE, strings);
//format(strings, sizeof(strings), "gTextDrawHideClock:%d TextDrawShowClock:%d", gTextDrawHideClock[playerid], TextDrawShowClock[playerid]);
//SendClientMessage(playerid, COLOR_PURPLE, strings);
//format(strings, sizeof(strings), "TextDrawShowCarTime:%d", TextDrawShowCarTime[playerid]);
//SendClientMessage(playerid, COLOR_PURPLE, strings);
//format(strings, sizeof(strings), "TextDrawShowMessage:%d", TextDrawShowMessage[playerid]);
//SendClientMessage(playerid, COLOR_PURPLE, strings);
//format(strings, sizeof(strings), "TextDrawShowBattery:%d", TextDrawShowBattery[playerid]);
//SendClientMessage(playerid, COLOR_PURPLE, strings);

	if(gTextDrawShowClock[playerid] == true && TextDrawShowClock[playerid] == false)
	{//если есть разрешение на показ и текстдров не показан
		TextDrawShowForPlayer(playerid, txdTimeDisp);//для часиков
		//TextDrawShowForPlayer(playerid, txdSecondsTime);
		TextDrawShowForPlayer(playerid, txdDate);
		//TextDrawShowForPlayer(playerid, txtServerName);

		PlayerTextDrawShow(playerid, txdBankDisp[playerid]);
		//PlayerTextDrawShow(playerid, txdSpeedMark[playerid]);

		PlayerTextDrawShow(playerid, txdPlayerHealth[playerid]);
		
		PlayerTextDrawShow(playerid, txdSecondsTime[playerid]);
		PlayerTextDrawShow(playerid, txdPlayerZone[playerid]);
		PlayerTextDrawShow(playerid, txdPlayerRegion[playerid]);

		TextDrawShowClock[playerid] = true;
		gTextDrawShowClock[playerid] = false;
	}
	else if(gTextDrawHideClock[playerid] == true && TextDrawShowClock[playerid] == true)
	{//если есть разрешение на скрытие и текстдров показан
		TextDrawHideForPlayer(playerid, txdTimeDisp);//для часиков
		//TextDrawHideForPlayer(playerid, txdSecondsTime);
		TextDrawHideForPlayer(playerid, txdDate);
		//TextDrawHideForPlayer(playerid, txtServerName);

		PlayerTextDrawHide(playerid, txdBankDisp[playerid]);
		//PlayerTextDrawHide(playerid, txdSpeedMark[playerid]);
		
		PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);

		PlayerTextDrawHide(playerid, txdSecondsTime[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerZone[playerid]);
		PlayerTextDrawHide(playerid, txdPlayerRegion[playerid]);

		TextDrawShowClock[playerid] = false;
		gTextDrawHideClock[playerid] = false;
	}
//==============================================================================
	if(gTextDrawShowCarTime[playerid] == true && TextDrawShowCarTime[playerid] == false)
	{
		PlayerTextDrawShow(playerid, txdCarTime[playerid]);
		TextDrawShowCarTime[playerid] = true;
		gTextDrawShowCarTime[playerid] = false;
	}
	else if(gTextDrawHideCarTime[playerid] == true && TextDrawShowCarTime[playerid] == true)
	{

		PlayerTextDrawHide(playerid, txdCarTime[playerid]);
		TextDrawShowCarTime[playerid] = false;//1
		gTextDrawHideCarTime[playerid] = false;//2
	}
//==============================================================================
//для бегущей строки
	/*else if(gTextDrawShowBegunok == true && TextDrawShowBegunok == false)
	{
		TextDrawShowForPlayer(playerid, txdBegunok);
		TextDrawShowBegunok = true;
		gTextDrawShowBegunok = false;
	}
	else if(gTextDrawHideBegunok == true && TextDrawShowBegunok == true)//для бегущей строки
	{
		TextDrawHideForPlayer(playerid, txdBegunok);
		TextDrawShowBegunok = false;//1
		gTextDrawHideBegunok = false;//2
	}*/
//==============================================================================
	if(gTextDrawShowMessage[playerid] == true && TextDrawShowMessage[playerid] == false)
	{
		TextDrawShowForPlayer(playerid, txdSystemMessage);
		TextDrawShowMessage[playerid] = true;
		gTextDrawShowMessage[playerid] = false;
	}
	else if(gTextDrawHideMessage[playerid] == true && TextDrawShowMessage[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdSystemMessage);
		TextDrawShowMessage[playerid] = false;//1
		gTextDrawHideMessage[playerid] = false;//2
	}
//==============================================================================
	/*else if(gTextDrawShowRace[playerid] == true && TextDrawShowRace[playerid] == false)
	{
		PlayerTextDrawShow(playerid, txdRacePosition[playerid]);//для гонок
		PlayerTextDrawShow(playerid, txdPositionAppend[playerid]);
		TextDrawShowForPlayer(playerid, txdTotalRacers);
		PlayerTextDrawShow(playerid, txdRaceTime[playerid]);
		TextDrawShowRace[playerid] = true;
		gTextDrawShowRace[playerid] = false;
	}
	else if(gTextDrawHideRace[playerid] == true && TextDrawShowRace[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdRacePosition[playerid]);//для гонок
		PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
		TextDrawHideForPlayer(playerid, txdTotalRacers);
		PlayerTextDrawHide(playerid, txdRaceTime[playerid]);
		TextDrawShowRace[playerid] = false;//1
		gTextDrawHideRace[playerid] = false;//2
	}*/
//==============================================================================
	/*if(gTextDrawShowCS[playerid] == true && TextDrawShowCS[playerid] == false)
	{
		PlayerTextDrawShow(playerid, txdRacePosition[playerid]);
		PlayerTextDrawShow(playerid, txdPositionAppend[playerid]);
		TextDrawShowForPlayer(playerid, txdTotalMembers);
		TextDrawShowForPlayer(playerid, txdCSTime);
		TextDrawShowCS[playerid] = true;
		gTextDrawShowCS[playerid] = false;
	}
	else if(gTextDrawHideCS[playerid] == true && TextDrawShowCS[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdRacePosition[playerid]);
		PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
		//TextDrawHideForPlayer(playerid, txdTotalMembers);
		TextDrawHideForPlayer(playerid, txdCSTime);
		TextDrawShowCS[playerid] = false;//1
		gTextDrawHideCS[playerid] = false;//2
	}*/
//==============================================================================
	if(gTextDrawShowBattery[playerid] == true && TextDrawShowBattery[playerid] == false)
	{
		TextDrawShowForPlayer(playerid, txdBlackSpeed);
		TextDrawShowForPlayer(playerid, txdDarkYellowSpeed);
		TextDrawShowForPlayer(playerid, txdMarkerMinus);
		TextDrawShowForPlayer(playerid, txdMarkerPlus);
		PlayerTextDrawShow(playerid, txdLightYellowSpeed[playerid]);
		TextDrawShowBattery[playerid] = true;
		gTextDrawShowBattery[playerid] = false;
	}
	else if(gTextDrawHideBattery[playerid] == true && TextDrawShowBattery[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdBlackSpeed);
		TextDrawHideForPlayer(playerid, txdDarkYellowSpeed);
		TextDrawHideForPlayer(playerid, txdMarkerMinus);
		TextDrawHideForPlayer(playerid, txdMarkerPlus);
		PlayerTextDrawHide(playerid, txdLightYellowSpeed[playerid]);
		TextDrawShowBattery[playerid] = false;//1
		gTextDrawHideBattery[playerid] = false;//2
	}
//==============================================================================
	/*if(gTextDrawShowScale[playerid] == true && TextDrawShowScale[playerid] == false)
	{
		TextDrawShowForPlayer(playerid, txdStatistics);

		TextDrawShowForPlayer(playerid, txdProgressObv1);
		TextDrawShowForPlayer(playerid, txdProgressObv2);
		TextDrawShowForPlayer(playerid, txdProgressObv3);
		TextDrawShowForPlayer(playerid, txdProgressObv4);
		TextDrawShowForPlayer(playerid, txdProgressObv5);

		TextDrawShowForPlayer(playerid, txdProgress1);
		TextDrawShowForPlayer(playerid, txdProgress2);
		TextDrawShowForPlayer(playerid, txdProgress3);
		TextDrawShowForPlayer(playerid, txdProgress4);
		TextDrawShowForPlayer(playerid, txdProgress5);

		TextDrawShowForPlayer(playerid, txdRamka);
		TextDrawShowForPlayer(playerid, txdRespect);
		TextDrawShowForPlayer(playerid, txdSunday);

		PlayerTextDrawShow(playerid, txdProgressZap1[playerid]);
		PlayerTextDrawShow(playerid, txdProgressZap2[playerid]);
		PlayerTextDrawShow(playerid, txdProgressZap3[playerid]);
		PlayerTextDrawShow(playerid, txdProgressZap4[playerid]);
		PlayerTextDrawShow(playerid, txdProgressZap5[playerid]);
		TextDrawShowScale[playerid] = true;
		gTextDrawShowScale[playerid] = false;
	}
	else if(gTextDrawHideScale[playerid] == true && TextDrawShowScale[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdStatistics);

		TextDrawHideForPlayer(playerid, txdProgressObv1);
		TextDrawHideForPlayer(playerid, txdProgressObv2);
		TextDrawHideForPlayer(playerid, txdProgressObv3);
		TextDrawHideForPlayer(playerid, txdProgressObv4);
		TextDrawHideForPlayer(playerid, txdProgressObv5);

		TextDrawHideForPlayer(playerid, txdProgress1);
		TextDrawHideForPlayer(playerid, txdProgress2);
		TextDrawHideForPlayer(playerid, txdProgress3);
		TextDrawHideForPlayer(playerid, txdProgress4);
		TextDrawHideForPlayer(playerid, txdProgress5);

		TextDrawHideForPlayer(playerid, txdRamka);
		TextDrawHideForPlayer(playerid, txdRespect);
		TextDrawHideForPlayer(playerid, txdSunday);

		PlayerTextDrawHide(playerid, txdProgressZap1[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap2[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap3[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap4[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap5[playerid]);
		TextDrawShowScale[playerid] = false;//1
		gTextDrawHideScale[playerid] = false;//2
	}*/
//==============================================================================
	if(gTextDrawShowArmour[playerid] == true && TextDrawShowArmour[playerid] == false)
	{
		format(strings, sizeof(strings), "TextDrawShowArmour:%d", TextDrawShowArmour[playerid]);
		SendClientMessage(playerid, COLOR_PURPLE, strings);
	
		PlayerTextDrawShow(playerid, txdPlayerArmour[playerid]);
	
		TextDrawShowArmour[playerid] = true;
		gTextDrawShowArmour[playerid] = false;
	}
	else if(gTextDrawHideArmour[playerid] == true && TextDrawShowArmour[playerid] == true)
	{
		format(strings, sizeof(strings), "TextDrawShowArmour:%d", TextDrawShowArmour[playerid]);
		SendClientMessage(playerid, COLOR_PURPLE, strings);
	
		PlayerTextDrawHide(playerid, txdPlayerArmour[playerid]);
		
		TextDrawShowArmour[playerid] = false;//1
		gTextDrawHideArmour[playerid] = false;//2
	}
//==============================================================================
	/*else if(gTextDrawShowChat[playerid] == true && TextDrawShowChat[playerid] == false)
	{
		PlayerTextDrawShow(playerid, txdCHAT[playerid]);
		TextDrawShowChat[playerid] = true;
		gTextDrawShowChat[playerid] = false;
	}
	else if(gTextDrawHideChat[playerid] == true && TextDrawShowChat[playerid] == true)
	{
		PlayerTextDrawHide(playerid, txdCHAT[playerid]);
		TextDrawShowChat[playerid] = false;//1
		gTextDrawHideChat[playerid] = false;//2
	}*/
//==============================================================================
    if(gTextDrawShowBlind[playerid] == true && TextDrawShowBlind[playerid] == false)
    {
		format(strings, sizeof(strings), "TextDrawShowBlind:%d", TextDrawShowBlind[playerid]);
		SendClientMessage(playerid, COLOR_PURPLE, strings);
	
        TextDrawShowForPlayer(playerid, txdBlind);
  		TextDrawShowBlind[playerid] = true;
		gTextDrawShowBlind[playerid] = false;
    }
    else if(gTextDrawHideBlind[playerid] == true && TextDrawShowBlind[playerid] == true)
    {
	 	format(strings, sizeof(strings), "TextDrawShowBlind:%d", TextDrawShowBlind[playerid]);
		SendClientMessage(playerid, COLOR_PURPLE, strings);
	
        TextDrawHideForPlayer(playerid, txdBlind);
  		TextDrawShowBlind[playerid] = false;//1
		gTextDrawHideBlind[playerid] = false;//2
    }
    /*else
    {
		//gTextDrawShowSpeed[playerid] = false;
		gTextDrawShowCarTime[playerid] = false;
		gTextDrawShowRace[playerid] = false;
		gTextDrawShowCS[playerid] = false;
		//gTextDrawShowClock[playerid] = false;
		gTextDrawShowScale[playerid] = false;
		gTextDrawShowBattery[playerid] = false;
		gTextDrawShowBlind[playerid] = false;
		gTextDrawShowMessage[playerid] = false;
		gTextDrawShowBegunok = false;
		gTextDrawShowArmour[playerid] = false;
		gTextDrawShowChat[playerid] = false;

		//gTextDrawHideSpeed[playerid] = false;
		gTextDrawHideCarTime[playerid] = false;
		gTextDrawHideRace[playerid] = false;
		gTextDrawHideCS[playerid] = false;
		//gTextDrawHideClock[playerid] = false;
		gTextDrawHideScale[playerid] = false;
		gTextDrawHideBattery[playerid] = false;
		gTextDrawHideBlind[playerid] = false;
		gTextDrawHideMessage[playerid] = false;
		gTextDrawHideBegunok = false;
		gTextDrawHideArmour[playerid] = false;
		gTextDrawHideChat[playerid] = false;
		

		SendClientMessage(playerid, COLOR_PURPLE, "OnPlayerTextDrawStateChange: false");
    }*/
}




//==============================================================================


stock ShowRegion(playerid)
{//ВЫВОД РЕГИОНОВ НАД РАДАРОМ
	for(new r=0; r<MAX_TURFS; r++)
	{
		if(regions[r][region_id] != PlayerInZone[playerid]) continue;
		if( IsPlayerInRegion(playerid, r) )
		{
			if(PlayerInRegion[playerid] != r)
			{
				PlayerTextDrawSetString(playerid, txdPlayerRegion[playerid], regions[r][region_name]);
				PlayerInRegion[playerid] = r;
				break;
			}
		}

		/*else
		{
			if(PlayerInRegion[playerid] == r)
			{
				PlayerInRegion[playerid] = NOT_ZONES;
			}
		}*/
	}
}
stock ShowHealth(playerid)
{
	if(TextDrawShowClock[playerid] == true)
	{
	    new Float:health; GetPlayerHealth(playerid, health);
		new strtmp[5+3];
		format(strtmp, sizeof(strtmp), "%.0f", health);
		PlayerTextDrawSetString(playerid, txdPlayerHealth[playerid], strtmp);
		new Float:Armour;
        GetPlayerArmour(playerid, Armour);
		format(strtmp, sizeof(strtmp),"%.0f", Armour);
		PlayerTextDrawSetString(playerid, txdPlayerArmour[playerid], strtmp);
	}
}




//##############################################################################//
//                                                                              //
//                      ПЕРЕГРУЖЕННЫЕ ОБРАБОТЧИКИ СОБЫТИЙ                       //
//                                                                              //
//##############################################################################//

stock textdraw_OnGameModeInit()//OnCreateTextDraw()//текстдровы, которые создаются при старте сервера, живут пока сервер работает и не будут изменяться или будут изменяться всем при показе
{   //вызывается из OnGameModeInit
//все TextDraw должны находится сдесь иначе смещение ID
	//textdrawtimer = SetTimer("TextDrawTimer", 1000, 1);
	new time = GetTickCount();
	//==========================================================================
//для гонок
	txdTotalRacers = TextDrawCreateEx(320.0, 402.5, "/~w~1");// /~w~1 //кол-во гонщиков
	TextDrawLetterSize(txdTotalRacers, 0.5, 2.5);

	txdTotalMembers = TextDrawCreateEx(320.0, 402.5, "/~w~1");// /~w~1 //кол-во гонщиков
	TextDrawLetterSize(txdTotalMembers, 0.5, 2.5);

	txdCSTime = TextDrawCreateEx(300.0, 420.0, "0:00");//0:00 //время
	TextDrawLetterSize(txdCSTime, 0.6, 3.0);
	//--------------------------------------------------------------------------
//для часиков начальная инициализация
	/*txdTimeDisp = TextDrawCreateEx(547.0, 29.5, " ");//547.0, 30.0
	TextDrawFont(txdTimeDisp, 3);
    TextDrawSetOutline(txdTimeDisp, 1);
    TextDrawLetterSize(txdTimeDisp, 0.5,1.5);
	TextDrawColor(txdTimeDisp, 0x00FF00FF);//COLOR_WHITE);

    txdSecondsTime = TextDrawCreateEx(596.0, 29.5, " ");//547.0 +50 = 597.0, 30.0
	TextDrawFont(txdSecondsTime, 3);
    TextDrawSetOutline(txdSecondsTime, 1);
    TextDrawLetterSize(txdSecondsTime,0.4,1.1);
	TextDrawColor(txdSecondsTime, COLOR_WHITE);

    txdDate = TextDrawCreateEx(547.0, 20.0, " ");//547.0 +50 = 597.0, 30.0
	TextDrawFont(txdDate, 2);
    TextDrawSetOutline(txdDate, 1);
    TextDrawLetterSize(txdDate,0.3,1.0);
	TextDrawColor(txdDate, COLOR_EMERALD);*/

    txdDate = TextDrawCreateEx(145.0, 355.0, RusToGame("Понедельник~n~15 Июнь 2020"));
	TextDrawLetterSize(txdDate, 0.150000, 1.500000);
	//TextDrawTextSize(txdDate, 617.000000, 0.000000);
	TextDrawAlignment(txdDate, 1);
	TextDrawColor(txdDate, COLOR_LIGHTGREY);
	TextDrawUseBox(txdDate, 0);
	TextDrawBoxColor(txdDate, 505290495);
	TextDrawSetShadow(txdDate, 0);
	TextDrawSetOutline(txdDate, 0);
	TextDrawBackgroundColor(txdDate, 168430335);
	TextDrawFont(txdDate, 1);
	TextDrawSetProportional(txdDate, 1);

	txdTimeDisp = TextDrawCreateEx(178.0, 355.0, "21:08");
	TextDrawLetterSize(txdTimeDisp, 0.300000, 3.000000);
	//TextDrawTextSize(txdTimeDisp, 617.000000, 0.000000);
	TextDrawAlignment(txdTimeDisp, 1);
	TextDrawColor(txdTimeDisp, COLOR_WHITE);
	TextDrawUseBox(txdTimeDisp, 0);
	TextDrawBoxColor(txdTimeDisp, 505290495);
	TextDrawSetShadow(txdTimeDisp, 1);
	TextDrawSetOutline(txdTimeDisp, 0);
	TextDrawBackgroundColor(txdTimeDisp, 168430335);
	TextDrawFont(txdTimeDisp, 1);
	TextDrawSetProportional(txdTimeDisp, 1);
	//--------------------------------------------------------------------------
//для названия хоста
	/*new strtmp[12+64+64];
	format(strtmp, sizeof(strtmp), "~y~%s ~h~%s", GMText, VERSION);
	txtServerName = TextDrawCreateEx(1.0, 438.0, strtmp);//(1.0, 439.0, VERSION);
  	TextDrawUseBox(txtServerName, 0);
	//TextDrawLetterSize(txtServerName,0.625,1.5);
	TextDrawLetterSize(txtServerName, 0.5,1.2);
	TextDrawFont(txtServerName, 0);
	TextDrawSetShadow(txtServerName, 0);
    TextDrawSetOutline(txtServerName, 1);
    TextDrawColor(txtServerName, COLOR_GOLD);//COLOR_SYSTEM);
*/
	//==========================================================================
//для затемнения экрана
    txdBlind = TextDrawCreateEx(0.0,0.0, "."); //For /blind cmd//"00000"); //For /blind cmd
    TextDrawUseBox(txdBlind,1);
    TextDrawBoxColor(txdBlind,0x000000FF);
    TextDrawTextSize(txdBlind,950.0,0.0);//950
    TextDrawFont(txdBlind,3);
    TextDrawLetterSize(txdBlind,5,100);
    TextDrawColor(txdBlind,0x000000FF);
	//==========================================================================
//для системной панели
	for(new l; l < MAX_LINES; l++) AdminMessageString[l] = " ";//начальное заполнение пробелами для создания пустой рамки
	txdSystemMessage = TextDrawCreateEx(150.0, 388.0-24.0, " ");//Создать новый Text Draw в памяти сервера.
	TextDrawUseBox(txdSystemMessage, 1);//Определяет использование рамки. 1 - использовать, 0 - не использовать
	TextDrawFont(txdSystemMessage, 1);//Изменяет шрифт текста. (0-3)
	TextDrawLetterSize(txdSystemMessage, 0.30, 1.00);//Устанавливает ширину и высоту букв(рамки) в пикселях.
	TextDrawSetOutline(txdSystemMessage, 1);//Устанавливает размер обводки текста. 1 - Толщина обводки
	TextDrawBackgroundColor(txdSystemMessage, 0x000000FF);//Устанавливает цвет фона текста
	TextDrawBoxColor(txdSystemMessage, 0x0000ff11);//Устанавливает цвет рамки
	TextDrawColor(txdSystemMessage, 0x00FF00FF);//Устанавливает цвет текста
	TextDrawTextSize(txdSystemMessage, 540.0, 0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).
	//==========================================================================
//для бегущей строки
	//for(new l; l < MAX_LINES; l++) RunString[l] = " ";//очистка
	txdBegunok = TextDrawCreateEx(150.0, 2.1, " ");
	TextDrawUseBox(txdBegunok, 1);
	TextDrawFont(txdBegunok, 1);
	TextDrawLetterSize(txdBegunok, 0.30, 1.00);
	TextDrawSetOutline(txdBegunok, 1);
	TextDrawBackgroundColor(txdBegunok, 0x000000FF);
	TextDrawBoxColor(txdBegunok, 0x0000ff11);
	TextDrawColor(txdBegunok, 0x00FF00FF);
	TextDrawTextSize(txdBegunok, 540.0, 10.0);

//==============================================================================
	Progress_OnGameModeInit();
	battery_OnGameModeInit();
	
	#include "../include/textdraw/txd_logo_new.pwn"
	//#include "../include/textdraw/txd_check_rus.inc"
	//#include "../include/textdraw/txd_SELECT_SPAWN.inc"
	//#include "../include/textdraw/txd_Intro.inc"
//==============================================================================
	printf("21/19. [Загрузка TextDraw]: Было загружено - %d, потрачено - %d (ms)", TEXT_DRAWS_COUNTER, GetTickCount() - time);//new time = GetTickCount();
 	return 1;
}//end OnCreateTextDraw



//stock OnDestroyTextDraw()//для информационной панели начало
stock textdraw_OnGameModeExit()//для информационной панели начало
{   //вызывается из remote_GameModeExitFunc -> GameModeInitExitFunc
	//KillTimer(textdrawtimer); textdrawtimer = -1;

//для гонок
	TextDrawDestroyEx(txdTotalRacers);
	//TextDrawDestroyEx(txdRaceTime);
	TextDrawDestroyEx(txdTotalMembers);
	TextDrawDestroyEx(txdCSTime);
	//==========================================================================
//для часиков начальная инициализация
  	TextDrawDestroyEx(txdTimeDisp);
	//TextDrawDestroyEx(txdSecondsTime);
	TextDrawDestroyEx(txdDate);
	//==========================================================================
//для названия хоста
	//TextDrawDestroyEx(txtServerName);
	//==========================================================================
//для батарейки
	battery_OnGameModeExit();
	//==========================================================================
//для потребностей
	Progress_OnGameModeExit();
	//==========================================================================
    TextDrawDestroyEx(txdBlind);//Для затемнение экрана
	TextDrawDestroyEx(txdSystemMessage);//Для системной панели
	TextDrawDestroyEx(txdBegunok);//длЯ бегущей строки
	//==========================================================================

	for(new i; i < sizeof(Intro); i++)
	{
		TextDrawDestroyEx(Intro[i]);
	}
	print("OnDestroyTextDraw() завершено");
	return 1;
}


stock textdraw_OnPlayerConnect(playerid)//текстдровы, которые создаются при входе каждого игрока и существуют пока игрок не покинет игру
{   //вызывается из OnPlayerConnect->OnPlayerLogin
	indicator1[playerid] = 0;
	indicator2[playerid] = 0;
	indicator3[playerid] = 0;
	indicator4[playerid] = 0;
	indicator5[playerid] = 0;
	indicator6[playerid] = 0;
	indicator7[playerid] = 0;

//все TextDraw должны находится сдесь иначе смещение ID
	//начальная инициализация
	gHide[playerid] = true;
	//gTextDrawShowSpeed[playerid] = false;
	gTextDrawShowCarTime[playerid] = false;
	gTextDrawShowRace[playerid] = false;
	gTextDrawShowCS[playerid] = false;
	gTextDrawShowClock[playerid] = false;
	gTextDrawShowScale[playerid] = false;

	gTextDrawShowBlind[playerid] = false;
	gTextDrawShowMessage[playerid] = false;
	gTextDrawShowBegunok = false;
	gTextDrawShowArmour[playerid] = false;
	gTextDrawShowChat[playerid] = false;

	//gTextDrawHideSpeed[playerid] = false;
	gTextDrawHideCarTime[playerid] = false;
	gTextDrawHideRace[playerid] = false;
	gTextDrawHideCS[playerid] = false;
	gTextDrawHideClock[playerid] = false;
	gTextDrawHideScale[playerid] = false;

	gTextDrawHideBlind[playerid] = false;
	gTextDrawHideMessage[playerid] = false;
	gTextDrawHideBegunok = false;
	gTextDrawHideArmour[playerid] = false;
	gTextDrawHideChat[playerid] = false;

	txdRaceTime[playerid] = CreatePlayerTextDrawEx(playerid, 300.0, 420.0, "0:00");//0:00 //время
	PlayerTextDrawLetterSize(playerid, txdRaceTime[playerid], 0.6, 3.0);

	txdRacePosition[playerid] = CreatePlayerTextDrawEx(playerid, 295.0, 375.0, "~w~1");//~w~1  //280
	PlayerTextDrawLetterSize(playerid, txdRacePosition[playerid], 1.2, 6.2);

	txdPositionAppend[playerid] = CreatePlayerTextDrawEx(playerid, 320.0, 385.0, " ");//~w~ST
	//PlayerTextDrawLetterSize(playerid, txdPositionAppend[playerid], 0.5, 2.5);
	PlayerTextDrawLetterSize(playerid, txdPositionAppend[playerid], 0.586340, 3.052500);
	PlayerTextDrawAlignment(playerid, txdPositionAppend[playerid], 2);
	PlayerTextDrawColor(playerid, txdPositionAppend[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdPositionAppend[playerid], -258);
	PlayerTextDrawSetOutline(playerid, txdPositionAppend[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, txdPositionAppend[playerid], -2139062017);
	PlayerTextDrawFont(playerid, txdPositionAppend[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdPositionAppend[playerid], 1);

//для дерби BloodBowl //для KickStart
	txdCarTime[playerid] = CreatePlayerTextDrawEx(playerid, 15.0, 130.0, " ");
	PlayerTextDrawUseBox(playerid, txdCarTime[playerid], 1);//Определяет использование рамки. 1 - использовать, 0 - не использовать
	PlayerTextDrawBoxColor(playerid, txdCarTime[playerid],0x00000011);//Устанавливает цвет рамки
	PlayerTextDrawTextSize(playerid, txdCarTime[playerid],165.0,0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).
	PlayerTextDrawAlignment(playerid, txdCarTime[playerid],0);//Устанавливает смещение текста в Text Draw. ID смещения: 0 или 1 - влево, 2 - центр, 3 - вправо.
	PlayerTextDrawBackgroundColor(playerid, txdCarTime[playerid],0x000000ff);//Устанавливает цвет фона теста
	PlayerTextDrawFont(playerid, txdCarTime[playerid], 1);//Изменяет шрифт текста. (0-3) 0(Style 2)-закавырестый, 1- компактный 2-все большие 3-все маленькие
	PlayerTextDrawLetterSize(playerid, txdCarTime[playerid], 0.4,1.5);//Устанавливает ширину и высоту букв(рамки) в пикселях.
	PlayerTextDrawColor(playerid, txdCarTime[playerid], COLOR_WHITE);//Устанавливает цвет текста
	//TextDrawSetOutline(txdCarTime[playerid], 2);//Устанавливает размер обводки текста и убирает тень. 1 - Толщина обводки
	PlayerTextDrawSetShadow(playerid, txdCarTime[playerid], 1);//Устанавливает размер тени текста. 2 - Размер тени по умолчанию


//------------------------------------------------------------------------------

    txdSecondsTime[playerid] = CreatePlayerTextDrawEx(playerid, 638.0, 0.0, "online: 1(1000) %100 fps ping: %10 ms");//fps ping time  //credit gold exp
	PlayerTextDrawLetterSize(playerid, txdSecondsTime[playerid],  0.19, 0.85);
	PlayerTextDrawAlignment(playerid, txdSecondsTime[playerid], 3);
	PlayerTextDrawColor(playerid, txdSecondsTime[playerid], COLOR_WHITE);
	PlayerTextDrawSetShadow(playerid, txdSecondsTime[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdSecondsTime[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, txdSecondsTime[playerid], -1);
	PlayerTextDrawFont(playerid, txdSecondsTime[playerid], 1);

//эталон растановки последовательности строк
    //txdPlayerRegion[playerid] = CreatePlayerTextDrawEx(playerid, 89.0, 330.0, " ");
    //txdPlayerRegion[playerid] = CreatePlayerTextDrawEx(playerid, 70.0, 320.0, " ");
    txdPlayerRegion[playerid] = CreatePlayerTextDrawEx(playerid, 145.0, 387.0, "Conference_Center");
    PlayerTextDrawLetterSize(playerid, txdPlayerRegion[playerid], 0.200000, 1.299998);
	PlayerTextDrawAlignment(playerid, txdPlayerRegion[playerid], 1);
    PlayerTextDrawColor(playerid, txdPlayerRegion[playerid], COLOR_WHITE);
	PlayerTextDrawSetShadow(playerid, txdPlayerRegion[playerid], 0);
    PlayerTextDrawSetOutline(playerid, txdPlayerRegion[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, txdPlayerRegion[playerid], -1);
    PlayerTextDrawFont(playerid, txdPlayerRegion[playerid], 1);//3
    //PlayerTextDrawSetProportional(playerid, txdPlayerRegion[playerid], 1);

    //txdPlayerZone[playerid] = CreatePlayerTextDrawEx(playerid, 89.0, 420.0, " ");
    //txdPlayerZone[playerid] = CreatePlayerTextDrawEx(playerid, 70.0, 430.0, " ");
    txdPlayerZone[playerid] = CreatePlayerTextDrawEx(playerid, 145.0, 403.0, "LOS SANTOS");
    PlayerTextDrawLetterSize(playerid, txdPlayerZone[playerid], 0.200000, 1.299998);
    PlayerTextDrawFont(playerid, txdPlayerZone[playerid], 1);//3
    PlayerTextDrawColor(playerid, txdPlayerZone[playerid], COLOR_LIGHTGREY);
	PlayerTextDrawSetShadow(playerid, txdPlayerZone[playerid], 0);
    //PlayerTextDrawSetOutline(playerid, txdPlayerZone[playerid], 0);
	//PlayerTextDrawAlignment(playerid, txdPlayerZone[playerid], 1);
    //PlayerTextDrawSetProportional(playerid, txdPlayerZone[playerid], 1);

//для денег в банке
	txdBankDisp[playerid] = CreatePlayerTextDrawEx(playerid, 145.0, 419.0, "$00000000");
	PlayerTextDrawLetterSize(playerid, txdBankDisp[playerid], 0.200000, 1.299998);
	PlayerTextDrawAlignment(playerid, txdBankDisp[playerid],1);//Устанавливает смещение текста в Text Draw. ID смещения: 0 или 1 - влево, 2 - центр, 3 - вправо.
    PlayerTextDrawColor(playerid, txdBankDisp[playerid], COLOR_GOLD);
	PlayerTextDrawSetShadow(playerid, txdBankDisp[playerid], 0);
    PlayerTextDrawSetOutline(playerid, txdBankDisp[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, txdBankDisp[playerid], -1);
	PlayerTextDrawFont(playerid, txdBankDisp[playerid], 1);


	//--------------------------------------------------------------------------
	//txdPlayerArmour[playerid] = CreatePlayerTextDrawEx(playerid, 606.0,96.0," ");
    txdPlayerArmour[playerid] = CreatePlayerTextDrawEx(playerid, 577.0,44.0," ");
	PlayerTextDrawAlignment(playerid, txdPlayerArmour[playerid], 2);
    PlayerTextDrawFont(playerid, txdPlayerArmour[playerid],1);
    PlayerTextDrawLetterSize(playerid, txdPlayerArmour[playerid], 0.314, 1.0);
    PlayerTextDrawColor(playerid, txdPlayerArmour[playerid],COLOR_WHITE);
    PlayerTextDrawSetOutline(playerid, txdPlayerArmour[playerid],1);
    PlayerTextDrawSetProportional(playerid, txdPlayerArmour[playerid],1);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;

     //txdPlayerHealth[playerid] = CreatePlayerTextDrawEx(playerid, 547.0,96.0," ");
	txdPlayerHealth[playerid] = CreatePlayerTextDrawEx(playerid, 577.0,66.0," ");
	PlayerTextDrawAlignment(playerid, txdPlayerHealth[playerid], 2);
    PlayerTextDrawFont(playerid, txdPlayerHealth[playerid],1);
    PlayerTextDrawLetterSize(playerid, txdPlayerHealth[playerid], 0.314, 1.0);
    PlayerTextDrawColor(playerid, txdPlayerHealth[playerid],COLOR_RED);
    PlayerTextDrawSetOutline(playerid, txdPlayerHealth[playerid],1);
    PlayerTextDrawSetProportional(playerid, txdPlayerHealth[playerid],1);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	//==========================================================================
	Progress_OnPlayerConnect(playerid);
	battery_OnPlayerConnect(playerid);

	for(new i; i < sizeof(TD_LOGO); i ++)
	{
	    TextDrawShowForPlayer(playerid, TD_LOGO[i]);
	}

	//ospawner(playerid);
 	return 1;
}//для информационной панели конец

stock textdraw_OnPlayerDisconnect(playerid)
{
	OnPlayerTextDrawHide(playerid);
	OnPlayerUnLoadTextDraw(playerid);
	
	Progress_OnPlayerDisconnect(playerid);
	battery_OnPlayerDisconnect(playerid);
}
//------------------------------------------------
stock textdraw_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused oldstate

	//--------------------------------------------------------------------------
	if(newstate == PLAYER_STATE_WASTED)//выполняется сразу после смерти игрока
	{   //если ID нового состояния равно состоянию 7 - истощенный/мертв
		gTextDrawHideClock[playerid] = true;

		//begunok_STATE_WASTED(playerid);

		if(TextDrawShowMessage[playerid] == true)
		{
			TextDrawHideForPlayer(playerid, txdSystemMessage);
		}
		gTextDrawHideArmour[playerid] = true;
	}
	OnPlayerTextDrawStateChange(playerid);
}

stock textdraw_OnPlayerSpawn(playerid)
{
	gTextDrawShowClock[playerid] = true;
	OnPlayerTextDrawStateChange(playerid);

	format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);

	if(	PlayerInfo[playerid][pAdmin] >= 1 //&&
		//!gInRacing[playerid] &&
		//!gInDerbyBloodBowl[playerid] &&
		//!gInDerby8ball[playerid] &&
		//!gInTerrorsCount[playerid] &&
		//!gInCTerrorsCount[playerid]
		)
	{
		if(TextDrawShowMessage[playerid] == true)
		{
			TextDrawShowForPlayer(playerid, txdSystemMessage);
		}
	}
	if(LastArmour[playerid] > 0.0)
	{
		gTextDrawShowArmour[playerid] = true;
		OnPlayerTextDrawStateChange(playerid);
	}


	if(GetPVarInt(playerid, "gChatSwitcher") != Off)
	{
		format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
		PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);

		SetPVarInt(playerid, "gChatSwitcher", Off);
		GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
	}
}

//stock textdraw_UpdateTime(playerid)
stock textdraw_OneSecondTimers(playerid)
{//вызывается из OneSecondTimers

	ShowRegion(playerid);
	ShowHealth(playerid);
}



