/*
 *            VW_Hotel v1.1
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 19.05.2020
 * @update    : 14.06.2020
 *
 * This file is provided as is (no warranties).
 *
 */

#include <a_samp>

// Система отеля
//const HOTEL_INT = 7; // интерьер в отеле
//const HOTEL_WORLD = 30; // вирт мир в отеле

const MAX_HOTEL_NUMBER = 12;
new hotel_Pickup[MAX_HOTEL_NUMBER+1];
new Text3D:hotel_Text[MAX_HOTEL_NUMBER+1];

new hotel_Click[MAX_PLAYERS];//номер по которому кликнули, чтобы снять 0-11
//new hotel_actor;

new hotel_Number[MAX_PLAYERS] = 0;//номер комнаты снятой в отеле


enum HOTEL_INFO
{//может быть несколько входов
	iLoc,//0-199 дома, 200-399 бизы, 400-499 компании
	iDiscription[32],//~w~Gun Shop 1 - описание
	
    iOwned,//0 - номер не куплен
	iOwner[MAX_PLAYER_NAME],//имя влядельца


	iEntranceInt,//1 - интерьер
	Float:iEntranceX,//координаты входа
	Float:iEntranceY,
	Float:iEntranceZ,
	Float:iEntranceA,//угол взгляда после выхода из интерьера
	iEntranceVW,

	iExitInt,//1 - интерьер
	Float:iExitX,//координаты выхода
	Float:iExitY,
	Float:iExitZ,
	Float:iExitA,//угол взгляда после входа в интерьер
	iExitVW,//1 - интерьер

	iLock,//1 - закрыт
	iCost,//0 - цена входа
	iDate,//дата последнего посещения для собственности как дом, в остальных случаях посещаемость
};

static const stock hotel_sync[MAX_HOTEL_NUMBER+1][HOTEL_INFO] = {
//{0, "HOTEL", 1, "none", 0,2233.1458,-1159.8044,26.0906,90.0,0,				HOTEL_INT,1865.6656,-1892.7041,908.6309, 90.0,HOTEL_WORLD,	0,0,0},//1//1559 Motel Down Floor HOTEL_WORLD=30
//{0, "HOTEL", 1, "none", 0,329.2820,-1513.9580,36.0391,227.3856,0,				HOTEL_INT,1865.6656,-1892.7041,908.6309, 90.0,HOTEL_WORLD,	0,0,0},//1//1559 Motel Down Floor HOTEL_WORLD=30
{0, "HOTEL", 	1, "none", 0,1775.0676,-1806.4968,13.5295,180.0,0,						HOTEL_INT,1865.6656,-1892.7041,908.6309, 90.0,HOTEL_WORLD,	0,0,0},//1//1559 Motel Down Floor HOTEL_WORLD=30
{1, "Lux",		0, "none", HOTEL_INT,1840.8601,-1895.1127,912.1217,0.0,HOTEL_WORLD, 	HOTEL_INT,1141.2002,-22.6947,1501.1859,180.0,HOTEL_WORLD+1,	1,500,0},// пикап в элит классе
{2, "Econom", 	0, "none", HOTEL_INT,1836.0137,-1895.1127,912.1217,0.0,HOTEL_WORLD,		HOTEL_INT,2166.5637,-1068.9889,1001.1859,270.0,HOTEL_WORLD+2,	1,250,0},// пикап в элит классе
{3, "Lux", 		0, "none", HOTEL_INT,1830.8617,-1895.1127,912.1217,0.0,HOTEL_WORLD,		HOTEL_INT,1141.2002,-22.6947,1501.1859,180.0,HOTEL_WORLD+3,	1,500,0},// пикап в элит классе
{4, "Econom",	0, "none", HOTEL_INT,1840.8601,-1890.4911,912.1217,180.0,HOTEL_WORLD,	HOTEL_INT,2166.5637,-1068.9889,1001.1859,270.0,HOTEL_WORLD+4,	1,250,0},// пикап в элит классе
{5, "Lux",		0, "none", HOTEL_INT,1836.0137,-1890.4911,912.1217,180.0,HOTEL_WORLD,	HOTEL_INT,1141.2002,-22.6947,1501.1859,180.0,HOTEL_WORLD+5,	1,500,0},// пикап в элит классе
{6, "Econom", 	0, "none", HOTEL_INT,1830.8617,-1890.4911,912.1217,180.0,HOTEL_WORLD,	HOTEL_INT,2166.5637,-1068.9889,1001.1859,270.0,HOTEL_WORLD+6,	1,250,0},// пикап в элит классе

{7, "Lux", 		0, "none", HOTEL_INT,1848.1993,-1880.5815,912.1217,180.0,HOTEL_WORLD, 	HOTEL_INT,1141.2002,-22.6947,1501.1859,180.0,HOTEL_WORLD+7,	1,500,0},// пикап в простом классе
{8, "Econom", 	0, "none", HOTEL_INT,1855.8690,-1880.5815,912.1217,180.0,HOTEL_WORLD,	HOTEL_INT,2166.5637,-1068.9889,1001.1859,270.0,HOTEL_WORLD+8,	1,250,0},// пикап в простом классе
{9, "Luxс",		0, "none", HOTEL_INT,1863.2007,-1880.5815,912.1217,180.0,HOTEL_WORLD, 	HOTEL_INT,1141.2002,-22.6947,1501.1859,180.0,HOTEL_WORLD+9,	1,500,0},// пикап в простом классе
{10, "Econom",	0, "none", HOTEL_INT,1848.1993,-1905.0123,912.1232,0.0,HOTEL_WORLD, 	HOTEL_INT,2166.5637,-1068.9889,1001.1859,270.0,HOTEL_WORLD+10,	1,250,0},// пикап в простом классе
{11, "Lux",		0, "none", HOTEL_INT,1855.8690,-1905.0123,912.1232,0.0,HOTEL_WORLD, 	HOTEL_INT,1141.2002,-22.6947,1501.1859,180.0,HOTEL_WORLD+11,	1,500,0},// пикап в простом классе
{12, "Econom",	0, "none", HOTEL_INT,1863.2007,-1905.0123,912.1232,0.0,HOTEL_WORLD, 	HOTEL_INT,2166.5637,-1068.9889,1001.1859,270.0,HOTEL_WORLD+12,	1,250,0}// пикап в простом классе
};


stock hotel_OnGameModeInit()
{
	//--------------------------------------------------------------------------
//Актёры с неуправляемым 3D текстом
    //hotel_actor =
	CreateDynamicActorExY("{EE66EE}Richard{FFFFFF}\nНажмите {FF0000}Y{FFFFFF} для взаимодействия",43, 1852.9167,-1892.6625,908.625,266.2188, true, 80.0, HOTEL_WORLD, HOTEL_INT);

//дверь на вход в Отель ЛС
	new tmpobjid = CreateDynamicObject(19358, 327.3558,-1511.8142,36.7787, -0.09,0.00,-38.50, 0, 0, -1, 200.0, 200.0);//стена
	SetDynamicObjectMaterial(tmpobjid, 0, 5986, "chateau_lawn", "doorkb_1_256", 0x00000000);

	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		hotel_Number[i] = 0;
	}
	for(new i=1; i <= MAX_HOTEL_NUMBER; i ++)
	{
	    hotel_sync[i][iOwned] = 0;
	}

//#if defined vw_sql//#endif
	//new number =
	LoadHotel();
//#endif
	LoadHotelInfo();
	return 1;
}

stock LoadHotel()
{
//db_free_result(db_query(db_handle, "CREATE TABLE IF NOT EXISTS `hotel`(`Number` INTEGER PRIMARY KEY AUTOINCREMENT,`ID` INTEGER NOT NULL,`Owner` VARCHAR(24) NOT NULL,`Day` INTEGER NOT NULL,`Lock` INTEGER NOT NULL)"));
/*
	new ToBase[185+1];//116 + 3+10+24+10+10+6+6 = 185
	format(ToBase, sizeof(ToBase), "INSERT INTO `hotel` (`Number`,`ID`,`Owner`,`Day`,`Lock`) VALUES (%d,%d,'%s',%d,%d)",
		operation, PlayerInfo[playerid][pSQLID], PlayerName(playerid), PlayerInfo[playerid][pCash], PlayerInfo[playerid][pBank], receipts, consuption);
	db_free_result(db_query(db_VW, ToBase));
*/

	new Field[MAX_PLAYER_NAME];
	new DBResult:db_result = db_query(db_VW,"SELECT * FROM `hotel`");
 	new number = 0;
  	//printf("db_num_rows: %d", db_num_rows(db_result));//12
	do
	{
		if(number > db_num_rows(db_result)) break;

		db_get_field_assoc(db_result, "Number", Field, sizeof(Field) ); number = strval(Field);
		db_get_field_assoc(db_result, "ID", Field, sizeof(Field) ); hotel_sync[number][iOwned] = strval(Field);
		db_get_field_assoc(db_result, "Owner", Field, sizeof(Field) ); strmid(hotel_sync[number][iOwner], Field, 0, strlen(Field), sizeof(Field));
		db_get_field_assoc(db_result, "Day", Field, sizeof(Field) ); hotel_sync[number][iDate] = strval(Field);
		db_get_field_assoc(db_result, "Lock", Field, sizeof(Field) ); hotel_sync[number][iLock] = strval(Field);

//printf("%d: Owned:%d, Owner:%s, Days:%d, Lock:%d", number, hotel_sync[number][iOwned], hotel_sync[number][iOwner], hotel_sync[number][iDate], hotel_sync[number][iLock]);
		number ++;
	}
	while(db_next_row(db_result));
	db_free_result(db_result);
	return number;
}

stock LoadHotelInfo()
{
	new time = GetTickCount();
	//--------------------------------------------------------------------------

	//==========================================================================
	for(new pic = 0; pic <= MAX_HOTEL_NUMBER; pic++)
	{   //для установки пикапов не привязанных к ИД
		hotel_Pickup[pic] = SetPickupEx(1559, 23, hotel_sync[pic][iExitX],hotel_sync[pic][iExitY],hotel_sync[pic][iExitZ]+0.1, hotel_sync[pic][iExitVW]);
		hotel_Text[pic] = Create3DTextLabelEx("Выход {FF0000}[EXIT]",
				0xBFF600FF, hotel_sync[pic][iExitX],hotel_sync[pic][iExitY],hotel_sync[pic][iExitZ]+0.75,
				30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, hotel_sync[pic][iExitVW]);

		hotel_Pickup[pic] = SetPickupEx(19132, 23, hotel_sync[pic][iEntranceX],hotel_sync[pic][iEntranceY],hotel_sync[pic][iEntranceZ], hotel_sync[pic][iEntranceVW]);
		new strtmp[15+2+32+8+24];
		if(hotel_sync[pic][iOwned] == 0)
		{
			format(strtmp, sizeof(strtmp), "[ %d. %s ]\n{EEEE88}[ Свободен ]", pic, hotel_sync[pic][iDiscription], hotel_sync[pic][iOwner]);
			hotel_Text[pic] = Create3DTextLabelEx(strtmp,
					0xFFFFFFFF, hotel_sync[pic][iEntranceX],hotel_sync[pic][iEntranceY],hotel_sync[pic][iEntranceZ]+0.75,
					10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, hotel_sync[pic][iEntranceVW]);
		}
		else if(pic == 0)
		{
			format(strtmp, sizeof(strtmp), "[ %s ]", hotel_sync[pic][iDiscription]);
			hotel_Text[pic] = Create3DTextLabelEx(strtmp,
					0xFFFFFFFF, hotel_sync[pic][iEntranceX],hotel_sync[pic][iEntranceY],hotel_sync[pic][iEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, hotel_sync[pic][iEntranceVW]);
		}
		else
		{
			format(strtmp, sizeof(strtmp), "[ %d. %s ]\n{AAAAFF}%s", pic, hotel_sync[pic][iDiscription], hotel_sync[pic][iOwner]);
			hotel_Text[pic] = Create3DTextLabelEx(strtmp,
				0xFFFFFFFF, hotel_sync[pic][iEntranceX],hotel_sync[pic][iEntranceY],hotel_sync[pic][iEntranceZ]+0.75,
				10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, hotel_sync[pic][iEntranceVW]);
		}
	}
	printf("13/19. [Загрузка пикапов отеля]: Было загружено - %d[3DText: %d], потрачено - %d (ms)", MAX_HOTEL_NUMBER, MAX_HOTEL_NUMBER-1, GetTickCount() - time);//new time = GetTickCount();
	return 1;
}

stock UpdateHotelIcon(hotel_number)
{
	new strtmp[73+2+32+8+24];
	if(hotel_sync[hotel_number][iOwned] == 0)
	{
		format(strtmp, sizeof(strtmp), "[ %d. %s ]\n{EEEE88}Свободен",
			hotel_number, hotel_sync[hotel_number][iDiscription]);
	}
	else
	{
		format(strtmp, sizeof(strtmp), "[ %d. %s ]\n{AAAAFF}%s{FFFFFF}\nНажмите {FF0000}Y{FFFFFF}, чтобы открыть/закрыть",
			hotel_number, hotel_sync[hotel_number][iDiscription], hotel_sync[hotel_number][iOwner]);
	}
	UpdateDynamic3DTextLabelText(hotel_Text[hotel_number], 0xFFFFFFFF, strtmp);
	return 1;
}

stock hotel_Clear()
{   
	db_free_result(db_query(db_VW, "UPDATE `hotel` SET `ID` = '0',`Owner` = 'none',`Day` = '0',`Lock` = '1'"));
}


stock hotel_OnPlayerConnect(playerid)
{
	hotel_Number[playerid] = 0;
}

stock hotel_OnPlayerSpawn(playerid)
{
	new ToBase[40+11];
	format(ToBase, sizeof(ToBase), "SELECT * FROM `hotel` WHERE `ID` = '%d'", PlayerInfo[playerid][pSQLID]);
	new DBResult:db_result = db_query(db_VW, ToBase);
	if(db_num_rows(db_result))
	{
		new Field[MAX_PLAYER_NAME];
		db_get_field_assoc(db_result, "Number", Field, sizeof(Field) ); hotel_Number[playerid] = strval(Field);
	}
	db_free_result(db_result);
	new strtmp[37+2];
    format(strtmp, sizeof strtmp, "Вы арендуете номер отеля: {2680C0}%d", hotel_Number[playerid]);
	SendClientMessage(playerid, COLOR_GREEN, strtmp);
}


//##############################################################################//
//                                                                              //
//                               ВХОД В ИНТЕРЬЕРЫ                               //
//                                                                              //
//##############################################################################//
stock hotel_EnterOfInteriorPickUp(playerid, pickupid)
{   //вызывается из interior_OnPlayerPickUp(playerid, pickupid) -> PlayerEnterPickUp -> pickup_OnPlayerPickUpPickup -> OnPlayerPickUpPickup
 	#pragma unused pickupid
//"/enter" - начало
	for(new i=0; i<=MAX_HOTEL_NUMBER; i++)
	{
		if(	IsPlayerInRangeOfPoint(playerid, 3.0, hotel_sync[i][iEntranceX],hotel_sync[i][iEntranceY],hotel_sync[i][iEntranceZ])
				//&& 	PlayerInfo[playerid][pLocal] == FREEROAM
				&& PlayerInfo[playerid][pVirtual] == hotel_sync[i][iEntranceVW])
		{
			if(hotel_sync[i][iLock] == 1)
			{
				//GTFP(playerid, "%s ~r~Closed", hotel_sync[0][iDiscription]);
				format(strings, sizeof(strings), "%d. %s ~r~Closed", i, hotel_sync[i][iDiscription]);
				GameTextForPlayer(playerid, strings, 5000, 1);
				SendErr(playerid, "Данный номер закрыт");
				return 1;
			}

		    //записываем в координаты спауна при входе
			PlayerInfo[playerid][pPos_x] = hotel_sync[i][iEntranceX];
			PlayerInfo[playerid][pPos_y] = hotel_sync[i][iEntranceY];
			PlayerInfo[playerid][pPos_z] = hotel_sync[i][iEntranceZ];


			SetPlayerWeather(playerid, 6);
			SetPlayerTime(playerid, 12, 0);

			new Float:X = hotel_sync[i][iExitX];
			new Float:Y = hotel_sync[i][iExitY];
			new Float:Z = hotel_sync[i][iExitZ];
			new Float:Ang = hotel_sync[i][iExitA];
			GetXYInFrontOfPoint(2.0, Ang, X,Y);
			
			PlayerInfo[playerid][pLocal] = hotel_sync[i][iLoc];
			SetPlayerInteriorEx(playerid, hotel_sync[i][iExitInt]);
			if(PlayerInfo[playerid][pVirtual] == 0 && PlayerInfo[playerid][pInt] == 0) { SetLoadTexture(playerid); SetPlayerPosC(playerid, X,Y,Z, Ang); }//с замарозкой
			else SetPlayerPosEx(playerid, X,Y,Z, Ang);
			SetPlayerVirtualWorldEx(playerid, hotel_sync[i][iExitVW]);

		    //GTFP(playerid, "~w~Welcome to the ~n~~y~%s",hotel_sync[0][iDiscription]);
			format(strings, sizeof(strings), "~w~Welcome to the ~n~~y~%s", hotel_sync[i][iDiscription]);
			GameTextForPlayer(playerid, strings, 5000, 1);
			//OnePlayAnim(playerid, "PED", "WALK_CIVI", 4.1, 0, 1, 1, 0, 0);
			//SetPVarInt(playerid, "Int", hotel_sync[i][iExitInt]);
			break;
		}
	}
//"/enter" - конец
//------------------------------------------------------------------------------
	if(CHECKING[PlayerPickUpPickup])
	{
		//ИНФОРМИРОВАНИЕ
		////new strings[MAX_STRING];
		format(strings, sizeof(strings), "hotel_EnterOfInteriorPickUp(playerid:%d) interior:%d virtual:%d",
			playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual]);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	return 1;
}//END EnterOfInteriorPickUp
//##############################################################################//
//                                                                              //
//                             ВЫХОД ИЗ ИНТЕРЬЕРОВ                              //
//                                                                              //
//##############################################################################//
stock hotel_ExitOfInteriorPickUp(playerid, pickupid)
{   //вызывается OnPlayerPickUpPickup
 	#pragma unused pickupid
	if(CHECKING[PlayerPickUpPickup])
	{
		//ИНФОРМИРОВАНИЕ
		////new strings[MAX_STRING];
		format(strings, sizeof(strings), "hotel_ExitOfInteriorPickUp(playerid:%d) Interior:%d Virtual:%d", playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual]);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}

//-------------------------------------------------------------------------
//"/exit" - начало
	for(new i=0; i<=MAX_HOTEL_NUMBER; i++)
	{
		if( IsPlayerInRangeOfPoint(playerid, 3.0, hotel_sync[i][iExitX],hotel_sync[i][iExitY],hotel_sync[i][iExitZ])
			&& PlayerInfo[playerid][pVirtual] == hotel_sync[i][iExitVW])
		{//если локация совпадает с виртуальным миром в котором находится игрок
			SetPlayerVirtualWorldEx(playerid, hotel_sync[i][iEntranceVW]);
			SetPlayerInteriorEx(playerid, hotel_sync[i][iEntranceInt]);

			new Float:X = hotel_sync[i][iEntranceX];
			new Float:Y = hotel_sync[i][iEntranceY];
			new Float:Z = hotel_sync[i][iEntranceZ];
			new Float:Ang = hotel_sync[i][iEntranceA];
			GetXYInFrontOfPoint(2.0, Ang, X,Y);
			SetPlayerPosEx(playerid, X,Y,Z, Ang);

			PlayerInfo[playerid][pLocal] = FREEROAM;
			//SetPVarInt(playerid, "Int", FREEROAM);
			break;
		}
	}
//"/exit" - конец
	return 1;
}//END ExitOfInteriorPickUp

stock hotel_OnPlayerPickUp(playerid, pickupid)
{
 	//#pragma unused pickupid
	hotel_EnterOfInteriorPickUp(playerid, pickupid);//для автовхода в интерьер с несколькими выходами
	hotel_ExitOfInteriorPickUp(playerid, pickupid);
}

stock hotel_OnPlayerKeyState_YES(playerid)
{
	//new interior = GetPVarInt(playerid, "ForPlayerID");
	if(IsPlayerInRangeOfPoint(playerid, 2.0, 1852.9167,-1892.6625,908.625 ))
	{
		new listitems[31+(55+1+12+24)*MAX_HOTEL_NUMBER];
		new strtmp[55+1+12+24];
		strcat(listitems, "Номер\tТип\tСтатус\tВладелец\n");
		for(new i=1; i <= MAX_HOTEL_NUMBER; i ++)
		{
		    if(hotel_sync[i][iOwned] == 0)
		    {
		        format(strtmp, sizeof strtmp, "{FFFFFF}%d\t%s\t{63BC70}Свободен\t{FFFFFF}Не имеется\n", i, hotel_sync[i][iDiscription]);
		    }
		    else
		    {
		        format(strtmp, sizeof strtmp, "{FFFFFF}%d\t%s\t{BC6363}Занят\t{FFFFFF}%s\n", i, hotel_sync[i][iDiscription], hotel_sync[i][iOwner]);
		    }
		    strcat(listitems, strtmp);
		}
		ShowPlayerDialogEx(playerid, HOTEL_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "Reception", listitems, "Выбрать", "Закрыть");
		return 1;
	}
//ф-ия вызовится если игрок снял номер
	if(hotel_Number[playerid] == 0) return 1;//обязательно сначало проверяем hotel_Number, т.к. массив не может принять значение -1
//2.5 - см GetXYInFrontOfPoint(2.0, Ang, X,Y); в ф-ии stock ExitOfInteriorPickUp(playerid, pickupid)
    if(	IsPlayerInRangeOfPoint(playerid, 3.0, 	hotel_sync[hotel_Number[playerid]][iEntranceX],
												hotel_sync[hotel_Number[playerid]][iEntranceY],
												hotel_sync[hotel_Number[playerid]][iEntranceZ] ) ||
		IsPlayerInRangeOfPoint(playerid, 3.0, 	hotel_sync[hotel_Number[playerid]][iExitX],
												hotel_sync[hotel_Number[playerid]][iExitY],
												hotel_sync[hotel_Number[playerid]][iExitZ] )
      )
    {//если ты рядом с номером в отеле
        if(hotel_sync[hotel_Number[playerid]][iLock] == 1)
        {
			hotel_sync[hotel_Number[playerid]][iLock] = 0;//hotel_Lock[hotel_Number[playerid]] = 0;
			
			new i = hotel_Number[playerid];
			PlayerInfo[playerid][pLocal] = hotel_sync[i][iLoc];
			SetPlayerInteriorEx(playerid, hotel_sync[i][iExitInt]);

			SetPlayerWeather(playerid, 6);
			SetPlayerTime(playerid, 12, 0);

			new Float:X = hotel_sync[i][iExitX];
			new Float:Y = hotel_sync[i][iExitY];
			new Float:Z = hotel_sync[i][iExitZ];
			new Float:Ang = hotel_sync[i][iExitA];
			GetXYInFrontOfPoint(2.0, Ang, X,Y);

			SetPlayerPosEx(playerid, X,Y,Z, Ang);
			SetPlayerVirtualWorldEx(playerid, hotel_sync[i][iExitVW]);

			//format(strings, sizeof(strings), "~w~Welcome to the ~n~~y~%s", hotel_sync[i][iDiscription]);
			//GameTextForPlayer(playerid, strings, 5000, 1);
			GameTextForPlayerEx(playerid, "~w~Hotel Door ~g~Open", 5000, 6);
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
        }
        else
        {
			hotel_sync[hotel_Number[playerid]][iLock] = 1;//hotel_Lock[hotel_Number[playerid]] = 1;
			GameTextForPlayerEx(playerid, "~w~Hotel Door ~r~Closed", 5000, 6);
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
        }
		//strings ="";
		//mysql_format(g_SQL,strings,200, "UPDATE `hotel` SET  `Lock` = '%d' WHERE `Number` = '%d' LIMIT 1",hotel_Lock[hotel_Number[playerid]], hotel_Number[playerid]);
		//mysql_pquery(g_SQL, strings, "", "");

		new ToBase[86+11];
		format(ToBase, sizeof(ToBase), "UPDATE `hotel` SET  `Lock` = '%d' WHERE `Number` = '%d'", hotel_sync[hotel_Number[playerid]][iLock], hotel_Number[playerid]);
		db_free_result(db_query(db_VW, ToBase));
		return 1;
    }

    return 1;
}

stock hotel_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(!response)
	{
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}
	switch(dialogid)
	{
		case HOTEL_DIALOG:
		{
		    switch(listitem)
		    {
			    case 0..11:
			    {
					if(hotel_Number[playerid] != 0)// && hotel_Number[playerid] != listitem+1
					{
						ShowPlayerDialogEx(playerid, HOTEL2_DIALOG, DIALOG_STYLE_MSGBOX, "Reception", "Вы уже арендуете номер в отеле", "Выселиться", "Закрыть");
						return 1;
					}
					
			    	new strtmp[171+43+68+2+12+11];//msgitems//listitems//inputitems
				    hotel_Click[playerid] = listitem+1;
				    if(hotel_sync[hotel_Click[playerid]][iOwned] != 0)
					{//если вы не арендатор данного номера
					    new day_info[10];
					    switch(hotel_sync[hotel_Click[playerid]][iDate])
					    {
					        case 1: day_info = "день";
					        case 2..4: day_info = "дня";
					        case 5..6: day_info = "дней";
					    }
					    format(strtmp, sizeof strtmp, "{C6B154}Информация о номере отеля\n\n{FFFFFF}Номер отеля: {2680C0}%d\n\n\
							{C65454}Данный номер занят.\n\
							{FFFFFF}Арендатор: {C6B154}%s\n\
							{FFFFFF}Номер освободится через: {C6B154}%d %s",
							hotel_Click[playerid], hotel_sync[hotel_Click[playerid]][iOwner], hotel_sync[hotel_Click[playerid]][iDate], day_info);
						ShowPlayerDialogEx(playerid, HOTEL2_DIALOG, DIALOG_STYLE_MSGBOX, "Аренда номера в отеле", strtmp, "Выселиться", "Закрыть");
						return 1;
					}
					format(strtmp, sizeof strtmp, "{FFFFFF}Вы хотите снять номер в отеле: {2680C0}%d{FFFFFF}\n\n\
{BC9B63}Информация о номере:\n\
{FFFFFF}Класс номера: {2680C0}%s{FFFFFF}\n\
Цена аренды за день: {2680C0}$%d\n\n\
{BCB063}Номер арендуется от 1 до 6 дней\n\
{FFFFFF}Введите количество дней \nна которые хотите арендовать номер:",
						hotel_Click[playerid], hotel_sync[hotel_Click[playerid]][iDiscription],hotel_sync[hotel_Click[playerid]][iCost]);
				    ShowPlayerDialogEx(playerid, HOTEL1_DIALOG, DIALOG_STYLE_INPUT, "Аренда номера в отеле", strtmp, "Принять", "Отмена");
				}
			}
		}
		case HOTEL1_DIALOG:
		{
	        if(hotel_sync[hotel_Click[playerid]][iOwned] != 0) return SendErr(playerid, "Данный номер уже сняли");
	        if(!strlen(inputtext)) return SendErr(playerid, "Вы оставили поле пустым");
	        new days = strval(inputtext);
	        if(days < 1 || days > 6) return SendErr(playerid, "Номер можно арендовать от 1 до 6 дней");
	        if(GetPlayerMoneyH(playerid) < hotel_sync[hotel_Click[playerid]][iCost]) return SendErr(playerid, "У вас недостаточно денег");
	        GivePlayerMoneyH(fhotel, playerid, -hotel_sync[hotel_Click[playerid]][iCost]);
	        SendClientMessage(playerid, 0x74B77FFF, "Вы успешно арендовали номер.");

			//strings ="";
			//mysql_format(g_SQL,strings,200, "UPDATE `hotel` SET  `ID` = '%d',`Owner` = '%s',`Day` = '%d' WHERE `Number` = '%d' LIMIT 1", PlayerInfo[playerid][pSQLID], PlayerName(playerid), c, hotel_Click[playerid]);
			//printf("%s", strings);
			//mysql_pquery(g_SQL, strings, "", "");

			new ToBase[86+11+24+3+2];
			format(ToBase, sizeof(ToBase), "UPDATE `hotel` SET  `ID` = '%d',`Owner` = '%s',`Day` = '%d' WHERE `Number` = '%d'",
				PlayerInfo[playerid][pSQLID], PlayerName(playerid), days, hotel_Click[playerid]);
			db_free_result(db_query(db_VW, ToBase));

			hotel_sync[hotel_Click[playerid]][iOwned] = PlayerInfo[playerid][pSQLID];
			hotel_sync[hotel_Click[playerid]][iDate] = days;// hotel_Days[hotel_Click[playerid]] = days;
			strmid(hotel_sync[hotel_Click[playerid]][iOwner], PlayerName(playerid), 0, strlen(PlayerName(playerid)), 24);

			UpdateHotelIcon(hotel_Click[playerid]);
			hotel_Number[playerid] = hotel_Click[playerid];
		}
		case HOTEL2_DIALOG:
		{
	        if(hotel_Number[playerid] == 0) return 1;
			ShowPlayerDialogEx(playerid, HOTEL3_DIALOG, DIALOG_STYLE_MSGBOX, "Отель", "{FFFFFF}Вы действительно желаете выселиться из номера?", "Принять", "Отмена");
		}
		case HOTEL3_DIALOG:
		{
	        if(hotel_Number[playerid] == 0) return 1;
			//strings ="";
			//mysql_format(g_SQL,strings,200, "UPDATE `hotel` SET  `ID` = '-1',`Owner` = 'Свободно',`Day` = '0' WHERE `Number` = '%d' LIMIT 1",hotel_Number[playerid]);
			//mysql_pquery(g_SQL, strings, "", "");

			new ToBase[86+11];
			format(ToBase, sizeof(ToBase), "UPDATE `hotel` SET `ID` = '0',`Owner` = 'none',`Day` = '0' WHERE `Number` = '%d'", hotel_Number[playerid]);
			db_free_result(db_query(db_VW, ToBase));

			hotel_sync[hotel_Number[playerid]][iOwned] = 0;
			strmid(hotel_sync[hotel_Number[playerid]][iOwner], "Свободно", 0, strlen("Свободно"), 24);
			hotel_sync[hotel_Number[playerid]][iDate] = 0;
			hotel_sync[hotel_Number[playerid]][iLock] = 1;
			
			UpdateHotelIcon(hotel_Number[playerid]);
			hotel_Number[playerid] = 0;
			
	        SendClientMessage(playerid, 0x74B77FFF, "Вы успешно выселились из отеля");
		}
	}
	//PlaySoundForPlayer(playerid, 5202);
	return 1;
}
