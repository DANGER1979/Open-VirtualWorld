//
// Admin player (skins,weapons,vehicles,objects) changer using previews. For SA-MP 0.3.7 and above.
// - Kye 2012
//

/*
 *            CHANGER v1.3
 *       (c) Copyright 2008-2024 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 30.01.2017
 * @update    : 17.03.2019
 *
 * This file is provided as is (no warranties).
 *
 */


//##############################################################################//
//                                                                              //
//                       МЕНЮ ПУКУПКИ ТАЧКИ, СКИНА, ОБЪЕКТА                     //
//                                                                              //
//##############################################################################//

/*
page_active - разделы (1 - скины, 2 - оружие, 3 - тачки, 4 - объекты)
chang_page - номер текущей страницы страницы
chang_active - тригер активности меню
ВЫЗЫВАЕТСЯ из vw_admin
   	    SetPVarInt(playerid, "TotalItems", 311); //gTotalItems = 311; MAX_SKINS
	    if(GetPVarInt(playerid, "page_active") != 1) SetPVarInt(playerid, "chang_page", 0); //если поменялась, тогда стартовать с первой страницы
	    SetPVarInt(playerid, "page_active", 1);//1 - скины или 3 - тачки
		SetTimerEx("PausePlayerTextDraw", 100, 0, "i", playerid);//разовый таймер changer_CreateSelectionMenu(playerid);
*/


//#define CHANGER_FILTERSCRIPT// This is a comment uncomment the line below if you want to write a filterscript
#if defined CHANGER_FILTERSCRIPT

#include <a_samp>
#include "../include/gl_common.inc"
#include "../include/vw_defines"
#include "../include/vw_color"
#include "../include/vw_config"
#include "../include/vw_plids"//оптимизация циклов /vw_Itter"//ф-ии для оптимизации серверов с большим онлайном
#include "../include/vw_arrays"
#include "../include/vw_player"
#include "../include/vw_skin"
#include "../include/car/vw_carstatus"
#include "../include/vw_functions"
#include "../include/vw_log"
#include "../include/vw_sound"
#include "../include/vw_PlayerInfo"
#include "../include/vw_VehInfo"
#include "../include/vw_PlayerEx"
#include "../include/vw_VehEx"
#include "../include/objects/vw_object"
#include "../include/vw_textdraw"
#include "../include/vw_check"//ф-ии проверки Is vw_PlayerInfo vw_VehInfo
#include "../include/vw_message"//использует vw_plids vw_player vw_PlayerInfo vw_checkpoint

#endif


#define TOTAL_ITEMS         311//всего - 20000//#define MAX_SKINS 311 //#define MAX_VEHICLE 212
#define SELECTION_ITEMS 	21//кол-во скинов/тачек на странице
#define ITEMS_PER_LINE  	7//кол-во квадратов на одной строке

#define HEADER_TEXT "Skins"
#define HEADER_TEXT2 "Objects"
#define HEADER_TEXT3 "ПОКУПКА ТРАНСПОРТНОГО СРЕДСТВА"

#define NEXT_TEXT   "LD_BEAT:right"//"Next"
#define PREV_TEXT   "LD_BEAT:left"//"Prev"

//координата левого верхнего угла фона
#define DIALOG_BASE_X   	16.0//75.0
#define DIALOG_BASE_Y   	80.0//80.0//100.0
//габарит фона
#define DIALOG_WIDTH    	640.0-2*DIALOG_BASE_X//510.0
#define DIALOG_HEIGHT   	345.0//300.0//367.0//200.0 //положении кнопок по оси Y
//размер квадрата со скином
#define SPRITE_DIM_X    	83.5//84.5//60
#define SPRITE_DIM_Y    	99.0//100.0//70

new gTotalItems = TOTAL_ITEMS;//MAX_SKINS;//TOTAL_ITEMS;
new gSelectionItemsTag[MAX_PLAYERS][SELECTION_ITEMS];//ID модели

new PlayerText:gCurrentPageTextDrawId[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:gBuyTextDrawId[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:gHeaderTextDrawId[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
//new PlayerText:gBackgroundTextDrawId[MAX_PLAYERS];
new PlayerText:gBackgroundTXD[26] = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:gNextButtonTextDrawId[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:gPrevButtonTextDrawId[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:gSelectionItems[MAX_PLAYERS][SELECTION_ITEMS]; //= {PlayerText:INVALID_TEXT_DRAW, ...};//ячейка с тачкой

new PlayerText:gStripesTXD[2][SELECTION_ITEMS]; // = {PlayerText:INVALID_TEXT_DRAW, ...};//полоски под названием и стоимостью
new PlayerText:gTitleTextDrawId[MAX_PLAYERS][SELECTION_ITEMS]; // = {PlayerText:INVALID_TEXT_DRAW, ...};//название
new PlayerText:gCostTextDrawId[MAX_PLAYERS][SELECTION_ITEMS]; // = {PlayerText:INVALID_TEXT_DRAW, ...};//стоимость

new PlayerText:gFundsTextDrawId[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};//ваши средства

new PlayerText:txdEdgingChanger[MAX_PLAYERS];
new PlayerText:txdBackgroundChanger[MAX_PLAYERS];
new PlayerText:txdHatChanger[MAX_PLAYERS];
new PlayerText:txdInfocarChanger[MAX_PLAYERS];


//new gItemAt[MAX_PLAYERS];

//#pragma dynamic 16384
//------------------------------------------------------------------------------
new Float:cXpos	= 320.0;
new Float:cYpos = 0.0;

stock Text:cTextDrawCreateEx(Float:x, Float:y, text[])
{
	TEXT_DRAWS_COUNTER ++;
	return TextDrawCreate(x+0.0, y+0.0, text);
}

stock PlayerText:cCreatePlayerTextDrawEx(playerid, Float:x, Float:y, playertext[])
{
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	return CreatePlayerTextDraw(playerid, x+0.0, y+0.0, playertext);
}

stock cTextDrawTextSizeEx(Text:text, Float:x, Float:y)
{
	return TextDrawTextSize(text, x+10.0, y+0.0);
}

stock cPlayerTextDrawTextSizeEx(playerid, PlayerText:playertext, Float:x, Float:y)
{
	return PlayerTextDrawTextSize(playerid, playertext, x+0.0, y+0.0);
}

//------------------------------------------------------------------------------

#if defined CHANGER_FILTERSCRIPT

public OnFilterScriptInit()
{
	for(new j = 0; j < SELECTION_ITEMS; j++)
	{
		for(new i = 0; i < GetMaxPlayers(); i++)
		{
			if(!IsPlayerConnected(i)) continue;

			gSelectionItems[i][j]= PlayerText:INVALID_TEXT_DRAW;//ячейка с тачкой
			gTitleTextDrawId[i][j] = PlayerText:INVALID_TEXT_DRAW;//название
			gCostTextDrawId[i][j] = PlayerText:INVALID_TEXT_DRAW;//стоимость
		}
		gStripesTXD[0][j] = PlayerText:INVALID_TEXT_DRAW;//полоски под названием и стоимостью
		gStripesTXD[1][j] = PlayerText:INVALID_TEXT_DRAW;//полоски под названием и стоимостью
	}
	return 1;
}

public OnFilterScriptExit()
{
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		changer_DestroyGeneralMenu(i);
		changer_DestroySelectionMenu(i);
		changer_DestroySelectionInfo(i);
		
		PLAYER_TEXT_DRAWS_COUNTER[i] = 0;
		SendClientMessage(i, COLOR_ORANGE, "Admin player CHANGER is Destroy.");
	}
	return 1;
}

#else


//public OnGameModeInit()
stock changer_OnGameModeInit()
{
	for(new j = 0; j < SELECTION_ITEMS; j++)
	{
		for(new i = 0; i < MAX_PLAYERS; i++)//GetMaxPlayers() возвращает сколько игроков присоеденилось к игре, но не факт, что это максимальный ид игрока
		{
			if(!IsPlayerConnected(i)) continue;
			PLAYER_TEXT_DRAWS_COUNTER[i] = 0;

			gSelectionItems[i][j]= PlayerText:INVALID_TEXT_DRAW;//ячейка с тачкой
			gTitleTextDrawId[i][j] = PlayerText:INVALID_TEXT_DRAW;//название
			gCostTextDrawId[i][j] = PlayerText:INVALID_TEXT_DRAW;//стоимость
		}
		gStripesTXD[0][j] = PlayerText:INVALID_TEXT_DRAW;//полоски под названием и стоимостью
		gStripesTXD[1][j] = PlayerText:INVALID_TEXT_DRAW;//полоски под названием и стоимостью
	}
}
	/*#if defined change_OnGameModeInit
		return change_OnGameModeInit();
	#else
		return 1; // Allow other scripts to keep processing OnPlayerConnect
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit change_OnGameModeInit
#if defined change_OnGameModeInit
	forward change_OnGameModeInit();
#endif*/

stock changer_OnGameModeExit()
//public OnGameModeExit()
{
	for(new i = 0; i < MAX_PLAYERS; i++)//GetMaxPlayers() возвращает сколько игроков присоеденилось к игре, но не факт, что это максимальный ид игрока
	{
		if(!IsPlayerConnected(i)) continue;
		changer_DestroyGeneralMenu(i);
		changer_DestroySelectionMenu(i);
		changer_DestroySelectionInfo(i);
	}
}
/*	#if defined change_OnGameModeExit
		return change_OnGameModeExit();
	#else
		return 1; // Allow other scripts to keep processing OnPlayerConnect
	#endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit change_OnGameModeExit
#if defined change_OnGameModeExit
	forward change_OnGameModeExit();
#endif*/


#endif


//------------------------------------------------

stock GetNumberOfPages()
{
	if((gTotalItems >= SELECTION_ITEMS) && (gTotalItems % SELECTION_ITEMS) == 0)
	{
		return (gTotalItems / SELECTION_ITEMS);//311/21=14.8
	}
	else return (gTotalItems / SELECTION_ITEMS) + 1;//311//21 + 1 = 15.8
}

//------------------------------------------------

stock PlayerText:CreateCurrentPageTextDraw(playerid, Float:Xpos, Float:Ypos)
{//текущаяя страница / кол-во страниц
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, "0/0");
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.6);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFAFAFAFF);//0xFAFAFAFF);//0xACCBF1FF);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

stock PlayerText:CreateBuyTextDraw(playerid, Float:Xpos, Float:Ypos)
{//текущаяя страница / кол-во страниц
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, RusToGame("Купить"));
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.6);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 0);//1);
    PlayerTextDrawColor(playerid, txtInit, 0x484848FF);//0xFAFAFAFF);//0xACCBF1FF);
    PlayerTextDrawAlignment(playerid, txtInit, 2);

   	PlayerTextDrawUseBox(playerid, txtInit, 1);//0);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x88888800);//0x000000FF);//цвет фона
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
	PlayerTextDrawTextSize(playerid, txtInit, 12.0, 45.0); // The width and height are reversed for centering.. something the game does <g>

    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------
// Creates a button textdraw and returns the textdraw ID.

/*stock PlayerText:CreatePlayerDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, button_text[])
{
 	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, button_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 1);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x888888FF);//0x000000FF);//цвет фона
   	//PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000FF);//цвет фона текста, не работает т.к. стоит PlayerTextDrawUseBox
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColor(playerid, txtInit, 0x484848FF);//0x4A5A6BFF);//цвет текста
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}*/
 
stock PlayerText:CreatePlayerDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, button_text[])
{
 	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, button_text);//"LD_BEAT:right");
   	PlayerTextDrawUseBox(playerid, txtInit, 1);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x888888FF);//0x000000FF);//цвет фона
   	//PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000FF);//цвет фона текста, не работает т.к. стоит PlayerTextDrawUseBox
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
 	PlayerTextDrawColor(playerid, txtInit, 0x484848FF);//0x4A5A6BFF);//цвет текста
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}
//------------------------------------------------

stock PlayerText:CreatePlayerHeaderTextDraw(playerid, Float:Xpos, Float:Ypos, header_text[])
{//ЗАГОЛОВОК
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, RusToGame(header_text));
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit,  0.2, 1.5);//1.25, 3.0);
	PlayerTextDrawFont(playerid, txtInit, 2);//0);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);//0xACCBF1FF);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

stock PlayerText:CreatePlayerFundsTextDraw(playerid, Float:Xpos, Float:Ypos, header_text[])
{//ваши средства
	new PlayerText:txtInit;

   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, header_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit,  0.25, 1.0);//1.25, 3.0);
	PlayerTextDrawFont(playerid, txtInit, 1);//0);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);//0xACCBF1FF);
    PlayerTextDrawAlignment(playerid, txtInit, 3);
 	PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}
//------------------------------------------------

stock BackgroundTextDrawStyle(playerid, PlayerText: txtInit, color)
{
	PlayerTextDrawLetterSize(playerid, txtInit, 0.0, 0.0);
	//PlayerTextDrawTextSize(playerid, txtInit, 16.0, -16.0);
	PlayerTextDrawAlignment(playerid, txtInit, 1);
	PlayerTextDrawColor(playerid, txtInit, color);//0x090909FF);//-1061109690);-2139062017);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
	PlayerTextDrawSetOutline(playerid, txtInit, 0);
	PlayerTextDrawFont(playerid, txtInit, TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawShow(playerid, txtInit);
}

stock CreatePlayerBackgroundTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height)
{//ЗАДНИЙ ФОН
//Xpos = 507.0;Ypos = 196.0;Width = 87.5;Height = 209.0;
	new Float: delta = 1.0;//ширина белой окантовки в пикселях
//начинаем с левого верхнего угла по часовой стрелке
	gBackgroundTXD[0] = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, "ld_pool:ball");//создаём кружок в левом верхнем углу, т.е. это будет окантовка
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[0], 16.0, 16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[0],0xD7D7D7AA);
	
	gBackgroundTXD[1] = CreatePlayerTextDrawEx(playerid, Xpos+Width, Ypos, "ld_pool:ball");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[1], -16.0, 16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[1],0xD7D7D7AA);

	gBackgroundTXD[2] = CreatePlayerTextDrawEx(playerid, Xpos+Width, Ypos+Height, "ld_pool:ball");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[2], -16.0, -16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[2],0xD7D7D7AA);
	
	gBackgroundTXD[3] = CreatePlayerTextDrawEx(playerid, Xpos, Ypos+Height, "ld_pool:ball");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[3], 16.0, -16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[3],0xD7D7D7AA);


//вертикальный
	gBackgroundTXD[5] = CreatePlayerTextDrawEx(playerid, Xpos+8.0, Ypos, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[5], Width-16.0, Height);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[5],0xD7D7D7AA);

//горизонтальный
	gBackgroundTXD[4] = CreatePlayerTextDrawEx(playerid, Xpos, Ypos+8.0, "LD_SPAC:white");//создаём прямоугольник между кружками
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[4], Width, Height-16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[4],0xD7D7D7AA);
//------------------------------------------------------------------------------
	gBackgroundTXD[6] = CreatePlayerTextDrawEx(playerid, Xpos+delta, Ypos+delta, "ld_pool:ball");//создаём кружок в левом верхнем углу но уже чёрного цвета, т.е. это будет фона мобилы
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[6], 16.0, 16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[6], 0x090909FF);

	gBackgroundTXD[7] = CreatePlayerTextDrawEx(playerid, Xpos+Width-delta, Ypos+delta, "ld_pool:ball");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[7], -16.0, 16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[7], 0x090909FF);
	
	gBackgroundTXD[8] = CreatePlayerTextDrawEx(playerid, Xpos+Width-delta, Ypos+Height-delta, "ld_pool:ball");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[8], -16.0, -16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[8], 0x090909FF);
	
	gBackgroundTXD[9] = CreatePlayerTextDrawEx(playerid, Xpos+delta, Ypos+Height-delta, "ld_pool:ball");
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[9], 16.0, -16.0);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[9], 0x090909FF);

//вертикальный
	gBackgroundTXD[10] = CreatePlayerTextDrawEx(playerid, Xpos+8.0+delta, Ypos+delta, "LD_SPAC:white");//закрашиваме чёрным
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[10], Width-16.0-delta*2, Height-delta*2);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[10], 0x090909FF);

//горизонтальный
	gBackgroundTXD[11] = CreatePlayerTextDrawEx(playerid, Xpos+delta, Ypos+8.0+delta, "LD_SPAC:white");//закрашиваме чёрным
	PlayerTextDrawTextSize(playerid, gBackgroundTXD[11], Width-delta*2, Height-16.0-delta*2);
	BackgroundTextDrawStyle(playerid, gBackgroundTXD[11], 0x090909FF);
}

/*
stock PlayerText:CreatePlayerBackgroundTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height)
{//ЗАДНИЙ ФОН
	new PlayerText:txtBackground = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, "                                            ~n~"); //достаточно места для всех enough space for everyone
    PlayerTextDrawUseBox(playerid, txtBackground, 1);
    PlayerTextDrawBoxColor(playerid, txtBackground, 0x090909FF);//0x4A5A6BBB);
	PlayerTextDrawLetterSize(playerid, txtBackground, 0.0, 38.0);//также влияет на высоту и ширину
    PlayerTextDrawTextSize(playerid, txtBackground, Width, 0.0);//Height);
    PlayerTextDrawAlignment(playerid, txtBackground, 1);
	PlayerTextDrawFont(playerid, txtBackground, 0);
	PlayerTextDrawSetShadow(playerid, txtBackground, 0);
    PlayerTextDrawSetOutline(playerid, txtBackground, 0);
    //PlayerTextDrawColor(playerid, txtBackground, 0x000000FF);
   	//PlayerTextDrawBackgroundColor(playerid, txtBackground, 0x4A5A6BBB);
    PlayerTextDrawShow(playerid, txtBackground);
    return txtBackground;
}*/

//------------------------------------------------
// Creates a model preview sprite
//дублируется в vw_textdraw
stock PlayerText:CreateModelPreviewTextDraw(playerid, modelindex, Float:Xpos, Float:Ypos, Float:width, Float:height)
{//создание основной ячейки таблицы
	//if(modelindex < 400 || modelindex > 611) return 0;
    new PlayerText:txtPlayerSprite = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, ""); // it has to be set with SetText later
    PlayerTextDrawFont(playerid, txtPlayerSprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColor(playerid, txtPlayerSprite, 0xB2B2B2FF);//0xB2B2B2FF);//0x2A2829FF);//цвет прорисовки моделей, можно не менять если цвет модели должен быть в родном цвете
    //должен быть всегда темнее от подсветки, но не полностью черным т.к. н будет видно моделей
    PlayerTextDrawBackgroundColor(playerid, txtPlayerSprite, 0x49494999);//0x494949FF//0x2A282999);//0x88888899);
    PlayerTextDrawTextSize(playerid, txtPlayerSprite, width, height); // Text size is the Width:Height
    PlayerTextDrawSetPreviewModel(playerid, txtPlayerSprite, modelindex);

	if(GetPVarInt(playerid, "page_active") == 3)
	{//если выбираем тачку
		new color1 = random(256); new color2 = random(256);
		VehInfo[MAX_VEHICLES-modelindex][cColor1] = color1;
		VehInfo[MAX_VEHICLES-modelindex][cColor2] = color2;
		PlayerTextDrawSetPreviewVehCol(playerid, txtPlayerSprite, color1, color2);
    	PlayerTextDrawSetPreviewRot(playerid, txtPlayerSprite, -8.0, 0.0, -45.0, 0.9);
	}
	else
	{
    	PlayerTextDrawSetPreviewRot(playerid, txtPlayerSprite, -8.0, 0.0, -45.0, 1.0);
	}


    PlayerTextDrawSetSelectable(playerid, txtPlayerSprite, 1);
    PlayerTextDrawShow(playerid,txtPlayerSprite);
    return txtPlayerSprite;
}


stock PlayerText:CreateModelNameTextDraw(playerid, Float:Xpos, Float:Ypos, name_model[])
{//название модели вверху ячейки
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, name_model);
   	
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.2, 1.0);//0.3, 0.6);
	//Шрифты выглядят лучше всего при соотношении X к Y от 1 до 4 (например, если х равен 0,5, то у должно быть 2).
	
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColor(playerid, txtInit, 0xD7D7D7FF);//0x000000FF);
	//PlayerTextDrawBackgroundColor(playerid, txdRADAR[playerid], COLOR_BACKGROUND);

    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

stock PlayerText:CreateModelCostTextDraw(playerid, Float:Xpos, Float:Ypos, name_model[])
{//стоимость внизу ячейки
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDrawEx(playerid, Xpos, Ypos, name_model);

   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.2, 1.0);//0.3, 0.6);

	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColor(playerid, txtInit, 0xD7D7D7FF);//0x000000FF);
	//PlayerTextDrawBackgroundColor(playerid, txdRADAR[playerid], COLOR_BACKGROUND);
	PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}
//------------------------------------------------

stock DestroyPlayerModelPreviews(playerid)
{
	new x=0;
	while(x != SELECTION_ITEMS) {
	    if(gSelectionItems[playerid][x] != PlayerText:INVALID_TEXT_DRAW) {
	    	PlayerTextDrawHide(playerid, gSelectionItems[playerid][x]);
	    	PlayerTextDrawHide(playerid, gStripesTXD[0][x]);
	    	PlayerTextDrawHide(playerid, gStripesTXD[1][x]);
	    	PlayerTextDrawHide(playerid, gTitleTextDrawId[playerid][x]);
	    	PlayerTextDrawHide(playerid, gCostTextDrawId[playerid][x]);
	    	
			PlayerTextDrawDestroyEx(playerid, gSelectionItems[playerid][x]);
			PlayerTextDrawDestroyEx(playerid, gStripesTXD[0][x]);
			PlayerTextDrawDestroyEx(playerid, gStripesTXD[1][x]);
			PlayerTextDrawDestroyEx(playerid, gTitleTextDrawId[playerid][x]);
			PlayerTextDrawDestroyEx(playerid, gCostTextDrawId[playerid][x]);
			
			gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
			gStripesTXD[0][x] = PlayerText:INVALID_TEXT_DRAW;
			gStripesTXD[1][x] = PlayerText:INVALID_TEXT_DRAW;
			gTitleTextDrawId[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
			gCostTextDrawId[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
		}
		x++;
	}
}

//------------------------------------------------

stock ShowPlayerModelPreviews(playerid)//ф-ия создания окна со скинами или моделями тачек
{//вызывается из OnPlayerClickPlayerTextDraw, changer_CreateSelectionMenu

    new x = 0;
	new Float:BaseX = DIALOG_BASE_X;
	new Float:BaseY = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.6); // down a bit
	new linetracker = 0;
	
	new itemat = GetPVarInt(playerid, "chang_page") * SELECTION_ITEMS;
	
	//Уничтожить все предыдущие созданные Destroy any previous ones created
	DestroyPlayerModelPreviews(playerid);
	
 	//gTotalItems = GetPVarInt(playerid, "TotalItems");
	new PageText[8+32+36], PageText2[24+10];//нельзя объявлять переменные внутри цикла
	
	/*new str[256+1];
	format(str, sizeof(str), "itemat: %d, SELECTION_ITEMS: %d, gTotalItems:%d", itemat, SELECTION_ITEMS, gTotalItems);
	SendClientMessage(playerid, COLOR_ORANGE, str);*/
	
	while(x != SELECTION_ITEMS && itemat < gTotalItems) {////кол-во скинов на странице
	    if(linetracker == 0) {
	        BaseX = DIALOG_BASE_X + 5.0; // in a bit from the box
	        BaseY += SPRITE_DIM_Y + 2.0; // move on the Y for the next line//задаём смещение
		}

		if(GetPVarInt(playerid, "page_active") == 3)
		{//если выбираем тачку
		  	gSelectionItems[playerid][x] = CreateModelPreviewTextDraw(playerid, VehicleArray[itemat][ModelID], BaseX, BaseY, SPRITE_DIM_X, SPRITE_DIM_Y);

			gStripesTXD[0][x] = CreatePlayerTextDrawEx(playerid, BaseX, BaseY, "LD_SPAC:white");//полоски закрашиваме чёрным
			PlayerTextDrawTextSize(playerid, gStripesTXD[0][x], SPRITE_DIM_X, 12.0);
			BackgroundTextDrawStyle(playerid, gStripesTXD[0][x], 0x1D1B1CFF);

			gStripesTXD[1][x] = CreatePlayerTextDrawEx(playerid, BaseX, BaseY+SPRITE_DIM_Y-12.0, "LD_SPAC:white");//закрашиваме чёрным
			PlayerTextDrawTextSize(playerid, gStripesTXD[1][x], SPRITE_DIM_X, 12.0);
			BackgroundTextDrawStyle(playerid, gStripesTXD[1][x], 0x1D1B1CFF);

			format(PageText, sizeof(PageText), "%d %s", VehicleArray[itemat][ModelID], VehicleArray[itemat][Vehicle_Name]);//получаем название модели
			gSelectionItemsTag[playerid][x] = VehicleArray[itemat][ModelID];//записываем модели машины по номеру ячейки
			
			//format(PageText2, sizeof(PageText2), "Стоимость: ~y~%s$", NiceMoney(VehicleArray[itemat][Virtual_Price], " ")  );//получаем стоимость модели
			strcat(PageText2, RusToGame("Стоимость: "));
			strcat(PageText2, "~y~");
			strcat(PageText2, NiceMoney(VehicleArray[itemat][Virtual_Price], " "));
			strcat(PageText2, "$");
			gCostTextDrawId[playerid][x] = CreateModelCostTextDraw(playerid, BaseX+SPRITE_DIM_X-30.0, BaseY+SPRITE_DIM_Y-11.0, PageText2);//RusToGame(PageText2));
			PlayerTextDrawAlignment(playerid, gCostTextDrawId[playerid][x], 3);
		 	strdel(PageText2, 0, sizeof(PageText2));
		}
  		else
		{
			gSelectionItems[playerid][x] = CreateModelPreviewTextDraw(playerid, SkinArray[itemat][Skin_ID], BaseX, BaseY, SPRITE_DIM_X, SPRITE_DIM_Y);

	/*new str[256+1];
	format(str, sizeof(str), "SkinArray[itemat][Skin_ID]: %d, Skin_ID:%d",  SkinArray[itemat][Skin_ID], Skin_ID);
	SendClientMessage(playerid, COLOR_ORANGE, str);*/

			format(PageText, sizeof(PageText), "%d~n~%s~n~%s", SkinArray[itemat][Skin_ID], SkinArray[itemat][Skin_Name], GetFamilyName(SkinArray[itemat][Type_Ped]));//получаем название модели
	   		gSelectionItemsTag[playerid][x] = SkinArray[itemat][Skin_ID];//itemat;//
   		}


 		gTitleTextDrawId[playerid][x] = CreateModelNameTextDraw(playerid, BaseX+1.0, BaseY+1.0, PageText);//название модели
 		PlayerTextDrawAlignment(playerid, gTitleTextDrawId[playerid][x], 1);
 		
 		
		BaseX += SPRITE_DIM_X + 2.0; // move on the X for the next sprite
		linetracker++;
		if(linetracker == ITEMS_PER_LINE) linetracker = 0;
		itemat++;
		x++;
	}
	
	/*new str[35+3+10];
	format(str, sizeof(str), "PLAYER_TEXT_DRAWS_COUNTER[%d] = %d", playerid, PLAYER_TEXT_DRAWS_COUNTER[playerid]);
	SendClientMessage(playerid, COLOR_ORANGE, str);*/
}

//------------------------------------------------

stock UpdatePageTextDraw(playerid)
{
	new PageText[64+1];
	format(PageText, 64, "%d/%d", GetPVarInt(playerid,"chang_page") + 1, GetNumberOfPages());
	PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid],  PageText);
//SendClientMessage(playerid, COLOR_ORANGE, PageText);
}

//------------------------------------------------


stock changer_CreateSelectionMenu(playerid)
{
	if(GetPVarInt(playerid, "chang_active") == 1)
	{//если перед этим мень было активно. то уничтожить чтобы заново создать
		changer_DestroyGeneralMenu(playerid);
		return 1;
	}
	gTotalItems = GetPVarInt(playerid, "TotalItems");
	
	//Если было ранее созданное меню выбора, то уничтожить.  If there was a previously created selection menu, destroy it
	changer_DestroySelectionMenu(playerid);
	changer_DestroySelectionInfo(playerid);

	SetPVarInt(playerid, "chang_active", 1);//поднимаем флаг - страница активна
	//SetPVarInt(playerid, "chang_page", 0); // will reset the page back to the first


    //gBackgroundTextDrawId[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
											//Xpos = 507.0;	Ypos = 196.0;		Width = 87.5;	Height = 209.0;
	CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);

	
    if(GetPVarInt(playerid, "page_active") == 3)
    {
		gHeaderTextDrawId[playerid] = CreatePlayerHeaderTextDraw(playerid, 640.0/2.0, DIALOG_BASE_Y+22.0, HEADER_TEXT3);
	}
    else
    {
		gHeaderTextDrawId[playerid] = CreatePlayerHeaderTextDraw(playerid, 640.0/2.0, DIALOG_BASE_Y+22.0, HEADER_TEXT);
	}

	
	new PageText[64+10];
	new money = GetPlayerMoney(playerid);//GetPlayerMoneyH(playerid));
	//format(PageText, 64, "Ваши средства: ~y~%s$", NiceMoney(money, " ") );//так нельзя, будет зависать из за RusToGame
	strcat(PageText, RusToGame("Ваши средства: "));
	strcat(PageText, "~y~");
	strcat(PageText, NiceMoney(money, " "));
	strcat(PageText, "$");
	gFundsTextDrawId[playerid] = CreatePlayerFundsTextDraw(playerid, 640.0-25.0, DIALOG_BASE_Y+30.0, PageText);//DIALOG_BASE_X, DIALOG_BASE_Y, HEADER_TEXT3);
	strdel(PageText, 0, sizeof(PageText));

    gCurrentPageTextDrawId[playerid] = CreateCurrentPageTextDraw(playerid, 640.0-40.0, DIALOG_BASE_Y+DIALOG_HEIGHT+1.0);//номера страниц
    gBuyTextDrawId[playerid] = CreateBuyTextDraw(playerid, 640.0/2.0, DIALOG_BASE_Y+DIALOG_HEIGHT+1.0);//кнопка покупки
    
    //gNextButtonTextDrawId[playerid] = CreatePlayerDialogButton(playerid, 640/2 + 30.0, DIALOG_BASE_Y+DIALOG_HEIGHT-50.0, 50.0, 16.0, NEXT_TEXT);
    //gPrevButtonTextDrawId[playerid] = CreatePlayerDialogButton(playerid, 640/2 - 30.0, DIALOG_BASE_Y+DIALOG_HEIGHT-50.0, 50.0, 16.0, PREV_TEXT);
    gPrevButtonTextDrawId[playerid] = CreatePlayerDialogButton(playerid, 640.0/2.0 - 40.0, DIALOG_BASE_Y+DIALOG_HEIGHT+1.0, 16.0, 16.0, PREV_TEXT);
    gNextButtonTextDrawId[playerid] = CreatePlayerDialogButton(playerid, 640.0/2.0 + 25.0, DIALOG_BASE_Y+DIALOG_HEIGHT+1.0, 16.0, 16.0, NEXT_TEXT);

    ShowPlayerModelPreviews(playerid);//создания ячеек

    UpdatePageTextDraw(playerid);//изменили названия страниц  и кол-во, т.к. для разных разделов оно разное
    
    SelectTextDraw(playerid, 0xFFFFFFFF);//0xB2B2B2FF);//0xFFFFFFFF);//0xACCBF1FF);//переходим в режим выбора TXD с указанным цветом

 	new str[35+3+10];
	format(str, sizeof(str), "PLAYER_TEXT_DRAWS_COUNTER[%d] = %d", playerid, PLAYER_TEXT_DRAWS_COUNTER[playerid]);
	SendClientMessage(playerid, COLOR_ORANGE, str);
	return 1;
}

//------------------------------------------------
stock changer_DestroyGeneralMenu(playerid)
{
	SetPVarInt(playerid, "chang_active", 0);//меню не активно
	changer_DestroySelectionMenu(playerid);
	changer_DestroySelectionInfo(playerid);
	PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	SetPVarInt(playerid, "Action", 0);
}

stock changer_DestroySelectionMenu(playerid)
{
	DestroyPlayerModelPreviews(playerid);

	PlayerTextDrawHide(playerid, gHeaderTextDrawId[playerid]);
	PlayerTextDrawHide(playerid, gFundsTextDrawId[playerid]);
	
	//PlayerTextDrawHide(playerid, gBackgroundTextDrawId[playerid]);
	for(new i = 0; i < sizeof(gBackgroundTXD); i++) PlayerTextDrawHide(playerid, gBackgroundTXD[i]);

	PlayerTextDrawHide(playerid, gCurrentPageTextDrawId[playerid]);
	PlayerTextDrawHide(playerid, gBuyTextDrawId[playerid]);

	PlayerTextDrawHide(playerid, gNextButtonTextDrawId[playerid]);
	PlayerTextDrawHide(playerid, gPrevButtonTextDrawId[playerid]);

	PlayerTextDrawDestroyEx(playerid, gHeaderTextDrawId[playerid]);
	PlayerTextDrawDestroyEx(playerid, gFundsTextDrawId[playerid]);
	//PlayerTextDrawDestroyEx(playerid, gBackgroundTextDrawId[playerid]);
	for(new i = 0; i < sizeof(gBackgroundTXD); i++) PlayerTextDrawDestroyEx(playerid, gBackgroundTXD[i]);
	PlayerTextDrawDestroyEx(playerid, gCurrentPageTextDrawId[playerid]);
	PlayerTextDrawDestroyEx(playerid, gBuyTextDrawId[playerid]);
	PlayerTextDrawDestroyEx(playerid, gNextButtonTextDrawId[playerid]);
	PlayerTextDrawDestroyEx(playerid, gPrevButtonTextDrawId[playerid]);

	gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
	gFundsTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    //gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    for(new i = 0; i < sizeof(gBackgroundTXD); i++) gBackgroundTXD[i] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBuyTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
}

//------------------------------------------------

stock SpawnObject_InfrontOfPlayer(playerid, model)
{
	new Float:x,Float:y,Float:z;
	new Float:facing;
	new Float:distance;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, facing);

    distance = 5.0;

  	x += (distance * floatsin(-facing, degrees));
    y += (distance * floatcos(-facing, degrees));

	facing += 90.0;
	if(facing > 360.0) facing -= 360.0;

	return CreateObjectEx(model, x,y,z, 0.0,0.0,0.0);
}

//------------------------------------------------

stock HandlePlayerItemSelection(playerid, selecteditem)
{//selecteditem - номер ячейки на странице
    if(gSelectionItemsTag[playerid][selecteditem] >= 0 && gSelectionItemsTag[playerid][selecteditem] < 312) {	// && gSelectionItemsTag[playerid][selecteditem] != 74
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
        SetPlayerSkinEx(giveplayerid, gSelectionItemsTag[playerid][selecteditem]);
        new str[128];
		format(str, sizeof(str), "AdmCmd: %s установил %s'у скин %d.", PlayerName(playerid), PlayerName(giveplayerid), gSelectionItemsTag[playerid][selecteditem]);
		SendClientMessage(playerid, COLOR_RED, str);
		return;
	}
    if(gSelectionItemsTag[playerid][selecteditem] >= 321 && gSelectionItemsTag[playerid][selecteditem] < 374) {//оружие
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		//GivePlayerWeapon(giveplayerid, gSelectionItemsTag[playerid][selecteditem], WeaponList[i][g_ammo]);
		new str[128];
		format(str, sizeof(str), "AdmCmd: %s give %s's Gun %d with %d ammunition", PlayerName(playerid), PlayerName(giveplayerid),
			gSelectionItemsTag[playerid][selecteditem], gSelectionItemsTag[playerid][selecteditem]);
  		//Log(ADMINLOG, strcmd);
		//SendAllAdminMessage(COLOR_RED, strcmd, 4);
		SendClientMessage(playerid, COLOR_RED, str);
		return;
	}
	if(gSelectionItemsTag[playerid][selecteditem] >= 400 && gSelectionItemsTag[playerid][selecteditem] < 612) {//тачки
		// In this case we're spawning a vehicle for them
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		new modelid = gSelectionItemsTag[playerid][selecteditem];
		new color1 = VehInfo[MAX_VEHICLES-modelid][cColor1]; new color2 = VehInfo[MAX_VEHICLES-modelid][cColor2];

		vehicle_SpawnInfrontOfPlayer(giveplayerid, modelid, color1, color2);//спауним тачку
    	
		//new str[128];
		//format(str, sizeof(str), "AdmCmd: %s give %s's Vehicle %d", PlayerName(playerid), PlayerName(giveplayerid),
		//	gSelectionItemsTag[playerid][selecteditem]);
    	return;
	}
    if(gSelectionItemsTag[playerid][selecteditem] > 615) {
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
    	new objectid = SpawnObject_InfrontOfPlayer(giveplayerid, gSelectionItemsTag[playerid][selecteditem]);
    	EditObject(playerid, objectid);
    	return;
	}
}

//------------------------------------------------

//public OnPlayerConnect(playerid)
stock changer_OnPlayerConnect(playerid)
{
	// Init all of the textdraw related globals
    gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
	gFundsTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    //gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    for(new i = 0; i < sizeof(gBackgroundTXD); i++) gBackgroundTXD[i] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBuyTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    
    for(new x=0; x < SELECTION_ITEMS; x++) {
        gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
		gStripesTXD[0][x] = PlayerText:INVALID_TEXT_DRAW;
		gStripesTXD[1][x] = PlayerText:INVALID_TEXT_DRAW;
        gTitleTextDrawId[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
        gCostTextDrawId[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
	}
}
	//gItemAt[playerid] = 0;
	/*#if defined change_OnPlayerConnect
		return change_OnPlayerConnect(playerid);
	#else
		return 1; // Allow other scripts to keep processing OnPlayerConnect
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect change_OnPlayerConnect
#if defined change_OnPlayerConnect
	forward change_OnPlayerConnect(playerid);
#endif*/


//-------------------------------------------
// Even though only Player* textdraws are used in this script,
// OnPlayerClickTextDraw is still required to handle ESC

//Не используйте CancelSelectTextDraw безоговорочно в рамках этой функции обратного вызова. Это приводит к бесконечному циклу.
//public OnPlayerClickTextDraw(playerid, Text:clickedid)
stock changer_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	//SendClientMessage(playerid, -1, "CEPBEP: {33AA33}OnPlayerClickTextDraw {00ccff}GENERAL");//skinchange
   	if(GetPVarInt(playerid, "chang_active") == 0) return 1;//вернуть 0 / ложь , если TextDraw, на который мы нажали не был найден

	// Handle: They cancelled (with ESC)
	if(clickedid == Text:INVALID_TEXT_DRAW) {
		changer_DestroyGeneralMenu(playerid);
        //return 1;//Возвращение 1 - будет препятствовать его вызывать в других сценариях.
	}
	return 1;
}
	/*#if defined change_OnPlayerClickTextDraw
		return change_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#endif
	return 0;
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw change_OnPlayerClickTextDraw
#if defined change_OnPlayerClickTextDraw
	forward change_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif*/

//------------------------------------------------
stock changer_OnPlayerClickPlTextDraw(playerid, PlayerText:playertextid)
//public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	//SendClientMessage(playerid, -1, "CEPBEP: {33AA33}OnPlayerClickPlayerTextDraw {00ccff}skinchange");
	if(GetPVarInt(playerid, "chang_active") == 0) return 0;//вернуть 0 / ложь , если TextDraw, на который мы нажали не был найден

 	//new str[256];
	//format(str, sizeof(str), "CEPBEP: {33AA33}OnPlayerClickTextDraw: %d [%06x] {00ccff}gunchange", 0, 16);//playertextid, playertextid);
	//SendClientMessage(playerid, -1, str);

	
	// Handle: They cancelled (with ESC)
	//if(playertextid == PlayerText:INVALID_TEXT_DRAW) { SendClientMessage(playerid, -1, "CEPBEP: {33AA33}PlayerText: {00ccff}INVALID_TEXT_DRAW"); }
	//в этом паблике OnPlayerClickPlayerTextDraw не работает, поэтому перенесено в OnPlayerClickTextDraw

	new curpage = GetPVarInt(playerid, "chang_page");

	// Handle: next button
	if(playertextid == gNextButtonTextDrawId[playerid]) {

	    if(curpage < (GetNumberOfPages() - 1)) {
	        SetPVarInt(playerid, "chang_page", curpage + 1);
	        ShowPlayerModelPreviews(playerid);


         	UpdatePageTextDraw(playerid);
         	PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
		} else {//если дошли доконца страниц
		    //changer_DestroyGeneralMenu(playerid);
		    CancelSelectTextDraw(playerid);
		}

		return 1;
	}
	

	// Handle: previous button
	if(playertextid == gPrevButtonTextDrawId[playerid]) {
	    if(curpage > 0) {
	    	SetPVarInt(playerid, "chang_page", curpage - 1);
	    	ShowPlayerModelPreviews(playerid);
	    	UpdatePageTextDraw(playerid);
	    	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		    /*if(GetPVarInt(playerid, "page_active") == 3 && curpage < 20)
		    {
			    changer_DestroyGeneralMenu(playerid);
			    CancelSelectTextDraw(playerid);
		    }*/
		} else {
		    //changer_DestroyGeneralMenu(playerid);
		    CancelSelectTextDraw(playerid);
		}
		return 1;
	}
	
	// Handle: buy
	if(playertextid == gBuyTextDrawId[playerid]) {
        HandlePlayerItemSelection(playerid, GetPVarInt(playerid, "SelectionItems") );//if(gSelectionItemsTag[playerid][selecteditem] >= 0 && gSelectionItemsTag[playerid][selecteditem] < 312)

        //changer_DestroyGeneralMenu(playerid);//при двойном нажатии в диалоге будет пропадать сразу вся страница TXD
        CancelSelectTextDraw(playerid);
		return 1;
	}

	// Search in the array of textdraws used for the items
	//должно срабатывать при повторном клике, а не при запуске
	//if(GetPVarInt(playerid, "Action") == 0) return 1;
	
//записываем номер выбранной ячейки
	for(new x=0; x < SELECTION_ITEMS; x++) {////кол-во скинов на странице
	    if(playertextid == gSelectionItems[playerid][x]) {
            SetPVarInt(playerid, "SelectionItems", x);
            
            changer_CreateSelectionInfo(playerid, x);
        	return 1;
		}
	}
	return 0;
}
	/*#if defined change_OnPlayerClickPlTD
		return change_OnPlayerClickPlTD(playerid, PlayerText:playertextid);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif
}

#if defined _ALS_ OnPlayerClickPlayerTextDraw
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_ OnPlayerClickPlayerTextDraw
#endif
#define OnPlayerClickPlayerTextDraw change_OnPlayerClickPlTD//OnPlayerClickPlayerTD
#if defined change_OnPlayerClickPlTD
	forward change_OnPlayerClickPlTD(playerid, PlayerText:playertextid);
#endif*/
//------------------------------------------------

stock changer_DestroySelectionInfo(playerid)
{
	SetPVarInt(playerid, "info_active", 0);//меню не активно
	PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);

	PlayerTextDrawHide(playerid, txdEdgingChanger[playerid]);
	PlayerTextDrawHide(playerid, txdBackgroundChanger[playerid]);
	PlayerTextDrawHide(playerid, txdHatChanger[playerid]);
	PlayerTextDrawHide(playerid, txdInfocarChanger[playerid]);

	PlayerTextDrawDestroyEx(playerid, txdEdgingChanger[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdBackgroundChanger[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdHatChanger[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdInfocarChanger[playerid]);

	txdEdgingChanger[playerid] = PlayerText:INVALID_TEXT_DRAW;
	txdBackgroundChanger[playerid] = PlayerText:INVALID_TEXT_DRAW;
	txdHatChanger[playerid] = PlayerText:INVALID_TEXT_DRAW;
	txdInfocarChanger[playerid] = PlayerText:INVALID_TEXT_DRAW;
}

stock changer_CreateSelectionInfo(playerid, selecteditem)
{
	if(GetPVarInt(playerid, "info_active") == 1)
	{//если перед этим мень было активно. то уничтожить чтобы заново создать
		changer_DestroySelectionInfo(playerid);
		return 1;
	}
	if(GetPVarInt(playerid, "page_active") != 3) return 1;//только для тачек
	if(gSelectionItemsTag[playerid][selecteditem] < 400 || gSelectionItemsTag[playerid][selecteditem] >= 612)
	{//тачки
		// In this case we're spawning a vehicle for them
    	return 1;
	}
	
	//changer_DestroySelectionInfo(playerid);
	/*new str[256];
	format(str, sizeof(str), "gSelectionItemsTag[playerid:%d][selecteditem:%d]=%d", playerid, selecteditem, gSelectionItemsTag[playerid][selecteditem]);
	SendClientMessage(playerid, COLOR_ORANGE, str);*/
	
	new modelid = gSelectionItemsTag[playerid][selecteditem];

	txdEdgingChanger[playerid] = cCreatePlayerTextDrawEx(playerid, cXpos, cYpos, //240.000000, 125.000000,
		"LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, txdEdgingChanger[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, txdEdgingChanger[playerid], 155.000000, 125.000000);
	PlayerTextDrawAlignment(playerid, txdEdgingChanger[playerid], 1);
	PlayerTextDrawColor(playerid, txdEdgingChanger[playerid], 0xCECECEFF);
	PlayerTextDrawSetShadow(playerid, txdEdgingChanger[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdEdgingChanger[playerid], 0);
	PlayerTextDrawFont(playerid, txdEdgingChanger[playerid], 4);
	PlayerTextDrawShow(playerid, txdEdgingChanger[playerid]);

	txdBackgroundChanger[playerid] = cCreatePlayerTextDrawEx(playerid, cXpos+1.5, cYpos+2.0, //241.500000, 127.000000,
		"LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, txdBackgroundChanger[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, txdBackgroundChanger[playerid], 151.500000, 121.000000);
	PlayerTextDrawAlignment(playerid, txdBackgroundChanger[playerid], 1);
	PlayerTextDrawColor(playerid, txdBackgroundChanger[playerid], 0x000000FF);
	PlayerTextDrawSetShadow(playerid, txdBackgroundChanger[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdBackgroundChanger[playerid], 0);
	PlayerTextDrawFont(playerid, txdBackgroundChanger[playerid], 4);
	PlayerTextDrawShow(playerid, txdBackgroundChanger[playerid]);

	new msgitem[526];//360 + 32+20+20 + 10+3+6 + 6+4+5 + 60 = 526
	format(msgitem, sizeof(msgitem), "%s~n~%s~n~%s~n~%d~n~$%d~n~%d~n~%dл~n~%dкм/ч~n~%dл/100км~n~%dкг",
				VehicleArray[modelid-400][Prototype],
				GetCarCategory(modelid-400),
				GetCarModifications(modelid-400),
				VehicleArray[modelid-400][Level],
				VehicleArray[modelid-400][Virtual_Price],
				VehicleArray[modelid-400][SeatID],
				VehicleArray[modelid-400][GasMax],
				VehicleArray[modelid-400][LineSpeed],
				VehicleArray[modelid-400][fuelConsumption],
				VehicleArray[modelid-400][Weight]/2);

	txdHatChanger[playerid] = cCreatePlayerTextDrawEx(playerid, cXpos+5.0, cYpos+10.0, //245.000000, 135.000000,
		RusToGame("~y~ПРОТОТИП:~w~~n~Категория:~n~Тюн:~n~Уровень:~n~Цена:~n~Мест:~n~Бак:~n~Скорость:~n~Расход:~n~Грузоподъёмность:"));
	PlayerTextDrawLetterSize(playerid, txdHatChanger[playerid], 0.170000, 1.200000);
	cPlayerTextDrawTextSizeEx(playerid, txdHatChanger[playerid], cXpos+80.0, cYpos+325.0);//320.000000, 450.000000);
	PlayerTextDrawAlignment(playerid, txdHatChanger[playerid], 1);
	PlayerTextDrawColor(playerid, txdHatChanger[playerid], -218959105);
	PlayerTextDrawSetShadow(playerid, txdHatChanger[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdHatChanger[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, txdHatChanger[playerid], 51);
	PlayerTextDrawFont(playerid, txdHatChanger[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdHatChanger[playerid], 1);
	PlayerTextDrawShow(playerid, txdHatChanger[playerid]);

	txdInfocarChanger[playerid] = cCreatePlayerTextDrawEx(playerid, cXpos+75.0, cYpos+10.0, //320.000000, 135.000000,
		RusToGame(msgitem));
	PlayerTextDrawLetterSize(playerid, txdInfocarChanger[playerid], 0.170000, 1.200000);
	cPlayerTextDrawTextSizeEx(playerid, txdInfocarChanger[playerid], cXpos+80.0, cYpos+325.0);//320.000000, 450.000000);
	PlayerTextDrawAlignment(playerid, txdInfocarChanger[playerid], 1);
	PlayerTextDrawColor(playerid, txdInfocarChanger[playerid], -218959105);
	PlayerTextDrawSetShadow(playerid, txdInfocarChanger[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdInfocarChanger[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, txdInfocarChanger[playerid], 51);
	PlayerTextDrawFont(playerid, txdInfocarChanger[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdInfocarChanger[playerid], 1);
	PlayerTextDrawShow(playerid, txdInfocarChanger[playerid]);

	SetPVarInt(playerid, "info_active", 1);//поднимаем флаг - страница активна
	return 1;
}

/*
public OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[256+1];	new	idx;
	//if(!IsPlayerAdmin(playerid)) return 1;
	cmd = strtok(cmdtext, idx);
	if(strcmp("/changer", cmd, true) == 0)
	{
		DeletePVar(playerid, "Action");
   	    SetPVarInt(playerid, "TotalItems", 212); //gTotalItems = 212;
	    if(GetPVarInt(playerid, "page_active") != 3) SetPVarInt(playerid, "chang_page", 0);//19);
		SetPVarInt(playerid, "page_active", 3);//1 - скины или 3 - тачки


		//SetPVarInt(playerid, "TotalItems", 311); //gTotalItems = 311;
	    //if(GetPVarInt(playerid, "page_active") != 1) SetPVarInt(playerid, "chang_page", 0); //если поменялась ЗАГОЛОВОК, тогда стартовать с первой страницы
	    //SetPVarInt(playerid, "page_active", 1);//1 - скины или 3 - тачки
	    
		changer_CreateSelectionMenu(playerid);
	    return 1;
	}
	#if defined change_OnPlayerCommandText
		return change_OnPlayerCommandText(playerid, cmdtext);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText change_OnPlayerCommandText
#if defined change_OnPlayerCommandText
	forward change_OnPlayerCommandText(playerid, cmdtext[]);
#endif*/
//------------------------------------------------
