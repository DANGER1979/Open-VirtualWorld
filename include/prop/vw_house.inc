new MyHouse[MAX_PLAYERS][5];

new hEntrancePickupID[MAX_HOUSE];//записываем id пикапа по номеру дома, чтобы потом знать у какого дома стоит игрок
new Text3D: hEntranceText3D[MAX_HOUSE];
new Text3D: hExitText3D[MAX_HOUSE];
new hExitPickupID[MAX_HOUSE];
new hClothEntPickupID[MAX_HOUSE];


stock GetHouseLocation(playerid)//вызывается по командам /tazer /arrest
{
	new location = 0;
	//if(	PlayerInfo[playerid][pLocal] >= 0 &&
	//	PlayerInfo[playerid][pLocal] < MAX_HOUSE)
	if(	PlayerInfo[playerid][pVirtual] >= 0 &&
		PlayerInfo[playerid][pVirtual] < MAX_HOUSE)
	{
		location = PlayerInfo[playerid][pVirtual];//PlayerInfo[playerid][pLocal];
	}
	return location;
}

stock house_OnGameModeInit()
{
	//НАЧАЛО УСТАНОВКИ ПИКАПОВ c надписями
	new text_info[128];//19+20+24
	for(new h = 0; h < MAX_HOUSE; h++)
	{
//ВХОДЫ
		if(HouseInfo[h][hOwned] == 0)
		{   //если дом не куплен
			//записываем id пикапа по номеру дома, чтобы потом знать у какого дома стоит игрок
			hEntrancePickupID[h] = SetPickupEx(1273, 23, HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ], 0);

		    format(text_info, sizeof(text_info), "[ %s ]", HouseInfo[h][hDiscription]);
			hEntranceText3D[h] = Create3DTextLabelEx(text_info, 0x88EE88FF,
					HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
					
//CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_MAP_ICON_SD, style = MAPICON_LOCAL, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0);
			//CreateDynamicMapIcon(HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ], 31, 0x88EE88FF, 0, 0, 100.0, MAPICON_GLOBAL);
		}
		else //if(HouseInfo[h][hOwned] > 0)
		{   //если дом куплен
			hEntrancePickupID[h] = SetPickupEx(19522, 23, HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]);
	
		    format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s",HouseInfo[h][hDiscription], HouseInfo[h][hOwner]);
			hEntranceText3D[h] = Create3DTextLabelEx(text_info, 0xAAAAFFFF,
					HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]+0.75,
					30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
			//CreateDynamicMapIcon(HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ], 32, 0xAAAAFFFF, 0, 0, 100.0, MAPICON_LOCAL);
		}
//ВХОДЫ В РАЗДЕВАЛКУ (выход у всех один, т.к. интерьер у всех один и тот же)
		if(HouseInfo[h][hCloth] == 1)//для раздевалки
		{   //если раздевалка куплена //всего 12 раздевалок
			hClothEntPickupID[h] = SetPickupEx(1559, 23, HouseInfo[h][hClothEntX], HouseInfo[h][hClothEntY], HouseInfo[h][hClothEntZ]+0.2, h+1);//-1 - во всех мирах устанавливать
		}
//ВЫХОДЫ
		hExitPickupID[h] = SetPickupEx(1559, 23, HouseInfo[h][hExitX], HouseInfo[h][hExitY], HouseInfo[h][hExitZ]+0.1, h+1);//маркер на выходе
		hExitText3D[h] = Create3DTextLabelEx("Выход {FF0000}[EXIT]", 0xBFF600FF,
					HouseInfo[h][hExitX], HouseInfo[h][hExitY], HouseInfo[h][hExitZ]+0.75,
					80.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 1, h+1);
		
	}//0-33=34
}

stock OnHouseInit(houseid)
{
	strmid(HouseInfo[houseid][hOwner], "Банк"", 0, strlen("Банк""), 255);//меняем имя владельца на The State
	HouseInfo[houseid][hHel] = 0;
	HouseInfo[houseid][hCloth] = 0;
	HouseInfo[houseid][hTV] = 0;
	HouseInfo[houseid][hLock] = 0;
	HouseInfo[houseid][hOwned] = 0;
	HouseInfo[houseid][hRent] = 1000+random(9000);
	//HouseInfo[houseid][hRentabil] = 0;
	HouseInfo[houseid][hTill] = 0;
	HouseInfo[houseid][hDate] = curdate;
}



stock house_OnPlayerPickUpPickup(playerid, pickupid)
//stock PropertyOnPlayerPickUp(playerid, pickupid)
{   //вызывается из OnPlayerPickUpPickup только при подборе пикапа
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return 1; }
	//if(pickupid < (STAIRWAYS*2-2) || pickupid >= (STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ)) return 1;
//STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ + MAX_VEHICLE_PICKUPS	//35*2 + (52*2+12)+82*2+59 = 409
//12 - максимальное кол-во раздевалок
	//new local = PlayerInfo[playerid][pLocal];
	new msgitem[868];//542+52+57+57 + 38+32+25+35+3+3+5+5 + 14 = 868

	new tregion[20];
	strmid(tregion, "Unknown_Region", 0, strlen("Unknown_Region"), 20);
	new house;//оставляем по нулям, чтобы не было за пределами массива
	for(new h = 0; h < MAX_HOUSE; h++)
	{   //опеделяем у какого дома стоит игрок
		//if(IsPlayerInRangeOfPoint(playerid, 4.1, HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]))
		if(pickupid == hEntrancePickupID[h])
		{
			house = h; SetPVarInt(playerid, "House", h);
			break;
		}
		//else if(IsPlayerInRangeOfPoint(playerid, 4.0, HouseInfo[h][hExitX], HouseInfo[h][hExitY], HouseInfo[h][hExitZ])
		else if(pickupid == hExitPickupID[h]
		&& PlayerInfo[playerid][pVirtual] == h+1)//если вдруг появятся дома с одним и тем же интерьером
		{
			house = h; SetPVarInt(playerid, "House", h);
			break;
		}
	}
	//==========================================================================
	if(	gDialogStatus[playerid][0] <= 0 &&
		//IsPlayerInRangeOfPoint(playerid, 1.4,  HouseInfo[house][hEntranceX], HouseInfo[house][hEntranceY], HouseInfo[house][hEntranceZ]))
		pickupid == hEntrancePickupID[house])
	{   //если менюшка игроку ещё не установлена и игрок находится в метре от входа в дом
		//if(IsPlayerInRangeOfPoint(playerid, 1.3,  HouseInfo[house][hEntranceX], HouseInfo[house][hEntranceY], HouseInfo[house][hEntranceZ]))
//ВНИМАНИЕ: если (playerid, 1.0, то менюшка может не сработать, т.к.HTTP подбор пикапа уже произошёл, а условие по растоянию не выполнено
		for(new j=0; j<MAX_TURFS; j++)
		{   //определяем в каком районе находится дом для вывода в менюшке
			if( IsPointInRegion(HouseInfo[house][hEntranceX], HouseInfo[house][hEntranceY], HouseInfo[house][hEntranceZ], j) )
			{//если дом находится в координатах по строке j из массива zones
				strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 255);//Извлекает диапазон символов из строки.
				break;
			}
		}
		if(HouseInfo[house][hOwned] > 0)
		{
			if(HouseInfo[house][hRent] == 0) format(msgitem, sizeof(msgitem),//{0080FF}Описание:\t{FFFFFF}%s\n
				"{0080FF}Район:\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t{FFFFFF}%s\
\n{0080FF}Уровень:\t{FFFFFF}%d",//HouseInfo[house][hDiscription],
				tregion, house+1, HouseInfo[house][hOwner],
				HouseInfo[house][hLevel]);
			else format(msgitem, sizeof(msgitem),//{0080FF}Описание:\t{FFFFFF}%s\n
				"{0080FF}Район:\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t{FFFFFF}%s\
\n{0080FF}Уровень:\t{FFFFFF}%d\
\n{0080FF}Аренда:\t{33AA33}$%d",//HouseInfo[house][hDiscription],
				tregion, house+1, HouseInfo[house][hOwner],
				HouseInfo[house][hLevel], HouseInfo[house][hRent]);
			strins(msgitem, "\n\n{AFAFAF}Для аренды введите /rentroom", strlen(msgitem));
		}
		else
		{
			format(msgitem, sizeof(msgitem),//\n{0080FF}Описание:\t{FFFFFF}%s
				"Этот Дом - для продажи\
\n{0080FF}Район:\t\t{FFFFFF}%s, %d\
\n{0080FF}Уровень:\t{FFFFFF}%d\
\n{0080FF}Стоимость:\t{33AA33}$%d",//HouseInfo[house][hDiscription],
				tregion, house+1, HouseInfo[house][hLevel], HouseInfo[house][hBuyPrice]);
			strins(msgitem, "\n\n{AFAFAF}Для покупки введите /buy. Стоимость пойдет в Банк", strlen(msgitem));
		}
		strins(msgitem, "\n{0080FF}Вы желаете войти в дом ?", strlen(msgitem));
		if(strlen(msgitem) > sizeof(msgitem))
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "Error18: House Info - %s[%d], strlen(msgitem): %d, sizeof(msgitem): %d", PlayerName(playerid), playerid, strlen(msgitem), sizeof(msgitem));
			Log(ERROR, strings);
			return 1;
		}
		ShowPlayerDialogGap(playerid, HOUSE_DIALOG, DIALOG_STYLE_MSGBOX, HouseInfo[house][hDiscription],msgitem, "YES", "NO");
		gDialogStatus[playerid][0] = 5;//менюшка показана
		
		if(CHECKING[PlayerPickUpPickup])
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "house_OnPlayerPickUpPickup(playerid:%d, house:%d)", playerid, house);
			//SendClientMessageToAll(COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
	}
	//--------------------------------------------------------------------------
	else if(gDialogStatus[playerid][0] <= 0 &&
		//IsPlayerInRangeOfPoint(playerid, 1.4, HouseInfo[house][hExitX], HouseInfo[house][hExitY], HouseInfo[house][hExitZ]))
		pickupid == hExitPickupID[house])
	{
		strins(msgitem, "\n{0080FF}Вы желаете выйти из дома ?", strlen(msgitem));
		ShowPlayerDialogGap(playerid, HOUSE_DIALOG, DIALOG_STYLE_MSGBOX, HouseInfo[house][hDiscription],msgitem, "YES", "NO");
		gDialogStatus[playerid][0] = 5;//таймер на 5 секунд
	}

	return 1;
}



stock house_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	HouseCtrlMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != HOUSE_DIALOG) return 1;//#define HOUSE_DIALOG 14
	//new msgitem[256+1];
	//new giveplayerid;
	if(!response)
	{
		PlaySoundForPlayer(playerid, SOUND_BEE_TRACK_STOP);
		SetPVarInt(playerid, "House", FREEROAM);
		return 1;
	}
//для входов //для выходов
	new h = GetPVarInt(playerid, "House");
	//for(new h = 0; h < MAX_HOUSE; h++)
//ИНФОРМИРОВАНИЕ
	//new strings[MAX_STRING];
//format(strings, sizeof(strings), "house_OnDialogResponse(playerid:%d, dialogid:%d, House:%d[%d]) pHouse:%d hLock:%d",
//		playerid, dialogid, GetPVarInt(playerid, "House"),
//		IsPlayerInRangeOfPoint(playerid, 3.0,	HouseInfo[h][hEntranceX],	HouseInfo[h][hEntranceY],	HouseInfo[h][hEntranceZ]),
//		PlayerInfo[playerid][pHouse],HouseInfo[h][hLock]	);
//SendClientMessage(playerid, -1, strings);
	
	//if(h != FREEROAM)
	//{   //находим в каком доме стоит сейчас игрок
//"/exit" - начало
	if(IsPlayerInRangeOfPoint(playerid, 3.0,
		HouseInfo[h][hExitX],
		HouseInfo[h][hExitY],
		HouseInfo[h][hExitZ]) &&
		h+1 == PlayerInfo[playerid][pVirtual])
	{   //если игрок у выхода из дома
		PlaySoundForPlayer(playerid, SOUND_BEE_TRACK_STOP);
		if(PlayerInfo[playerid][pHouse] == h &&
			//!strcmp(PlayerName(playerid), HouseInfo[PlayerInfo[playerid][pHouse]][hOwner], true)
			PlayerInfo[playerid][pSQLID] == HouseInfo[h][hOwned]
		  )
		{
			OnSaveDateProp(playerid, h);//записывает день выхода из дом
		}//для владения несколькими бизами

		new Float:X = HouseInfo[h][hEntranceX];
		new Float:Y = HouseInfo[h][hEntranceY];
		new Float:Z = HouseInfo[h][hEntranceZ];
		new Float:Ang = HouseInfo[h][hEntranceA];
		GetXYInFrontOfPoint(2.0, Ang, X,Y);
		SetPlayerPosEx(playerid, X,Y,Z, Ang);

		SetPlayerInteriorEx(playerid, 0);
		SetPlayerVirtualWorldEx(playerid, 0);
		PlayerInfo[playerid][pLocal] = FREEROAM;
		//if(PlayerInfo[playerid][pHouse] == 28)
		//{
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		SetPlayerTime(playerid, lH, lM);//возвращаем время в мире
		SetWeather(weathers[wethindex]);//возвращаем погоду
		//}
		SetPVarInt(playerid, "gHeal", 0);
		SetPVarInt(playerid, "House", FREEROAM);
		PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0,HouseInfo[h][hEntranceX],HouseInfo[h][hEntranceY],HouseInfo[h][hEntranceZ]);
		//вышёл из дома
		//break;
	}
//"/exit" - конец
//"/enter" - начало
	else if(IsPlayerInRangeOfPoint(playerid, 3.0,
		HouseInfo[h][hEntranceX],
		HouseInfo[h][hEntranceY],
		HouseInfo[h][hEntranceZ])
		&& PlayerInfo[playerid][pVirtual] == 0
		//&& PlayerInfo[playerid][pLocal] == FREEROAM
		)
	{   //если игрок у входа в дом
		if(PlayerInfo[playerid][pHouse] == h || HouseInfo[h][hLock] == 0)
		{   //если переменная pHouse равна найденому дому или дверь этого дома не закрыта
			//PlayerInfo[playerid][pLocal] = h;//записали ID дома
			SetPlayerVirtualWorldEx(playerid, h+1);//h
			//if(PlayerInfo[playerid][pHouse] == 28)

		    //записываем в координаты спауна при входе
			PlayerInfo[playerid][pPos_x] = HouseInfo[h][hEntranceX],
			PlayerInfo[playerid][pPos_y] = HouseInfo[h][hEntranceY],
			PlayerInfo[playerid][pPos_z] = HouseInfo[h][hEntranceZ];

			SetPlayerTime(playerid, 22, 0);//ставим на 22 часа, чтобы красивее было
			SetPlayerWeather(playerid, 5);

			SetPlayerInteriorEx(playerid, HouseInfo[h][hInt]);//установить интерьер

			new Float:X = HouseInfo[h][hExitX];
			new Float:Y = HouseInfo[h][hExitY];
			new Float:Z= HouseInfo[h][hExitZ];
			new Float:Ang = HouseInfo[h][hExitA];
			GetXYInFrontOfPoint(2.0, Ang, X,Y);
			SetPlayerPosEx(playerid, X,Y,Z, Ang);

			//OnePlayAnim(playerid, "PED", "RUN_CIVI", 4.1, 0, 1, 1, 0, 0);
			//OnePlayAnim(playerid, "PED", "WALK_CIVI", 4.1, 0, 1, 1, 0, 0);
			//OnePlayAnim(playerid, "PED", "WALK_DOORPARTIAL", 3.1, 0, 0, 0, 0, 0);
			GameTextForPlayerEx(playerid, "~w~Welcome Home", 5000, 1);
			//PlaySoundForPlayer(playerid, SOUND_BEE_TRACK_START);
			PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0,HouseInfo[h][hExitX],HouseInfo[h][hExitY],HouseInfo[h][hExitZ]);

			SetPVarInt(playerid, "House", FREEROAM);
			//вошёл в дом
		}
		else GameTextForPlayerEx(playerid, "~r~Locked", 5000, 1);//по англ обязательно
		//break;
	}
//"/enter" - конец
	//}
//------------------------------------------------------------------------------
	SetPVarInt(playerid, "House", FREEROAM);
	return 1;
}


stock PrintHouseInfo(playerid, houseid)//вызывается по команде bizinfo
{
	new coordsstring[128];
	SendClientMessage(playerid, COLOR_GREEN, "_______________________________________");
	new locked[7];
	if(HouseInfo[houseid][hLock] == 1) locked = "Закрыт";
	else locked = "Открыт";
	format(coordsstring, sizeof(coordsstring), "*** %s %s ***",HouseInfo[houseid][hDiscription], locked);
	SendClientMessage(playerid, COLOR_GRAD6, coordsstring);
	format(coordsstring, sizeof(coordsstring), "В сейфе: $%d",//%%\%%
		HouseInfo[houseid][hTill]);
	SendClientMessage(playerid, COLOR_GRAD5, coordsstring);
	format(coordsstring, sizeof(coordsstring), "Цена аренды: $%d", HouseInfo[houseid][hRent]);
	SendClientMessage(playerid, COLOR_GRAD4, coordsstring);

	new Heal[12], Arm[12], TV[12];
	if(HouseInfo[houseid][hHel] == 1) Heal = "Аптечка,";
	if(HouseInfo[houseid][hCloth] == 1) Arm = "Раздевалка,";
	if(HouseInfo[houseid][hTV] == 1) TV = "Телевизор";
	format(coordsstring, sizeof(coordsstring), "Улучшения: %s %s %s", Heal, Arm, TV);
	SendClientMessage(playerid, COLOR_GRAD3, coordsstring);

	SendClientMessage(playerid, COLOR_GREEN, "_______________________________________");
}


//stock HouseAction(playerid, houseid)
stock house_ControlMenu(playerid, houseid)
{
	new listitems[] = "/houseinfo - информация по дому\n\
/home - установить маркер на ваш дом\n\
/heal - восстановить здоровье\n\
/read paper - читать газету\n\
/open - открыть/закрыть дом\n\
/houseupgrade - доступные улучшения\n\
/housewithdraw - забрать выручку за аренду\n\
/setrent - установить стоимость аренды(/setrent 0 - запретить аренду)\n\
/lessees - список арендаторов онлайн\n\
/sellhouse - продать дом\n";
	DialogID[playerid][0] = houseid;
	MenuOperation[playerid] = 123;
	
	new caption[24+32+3];
	format(caption, sizeof(caption), "МЕНЮ УПРАВЛЕНИЯ: %s[%d]", HouseInfo[houseid][hDiscription], houseid);
	ShowPlayerDialogGap(playerid, HOUSE_CONTROL_MENU, DIALOG_STYLE_LIST, caption, listitems, "OK", "Назад");//BIZ_CONTROL_MENU
}

//stock house_ListItem(playerid, house, response, listitem, inputtext[])
stock HouseCtrlMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	/*if(CHECKING == 1)
	{
		//ИНФОРМИРОВАНИЕ
		new msgitem[MAX_STRING];
		format(msgitem, sizeof(msgitem), "HouseListItem(playerid:%d, house:%d, listitem:%d, inputtext:%s)", playerid, house, listitem, inputtext);
		//SendClientMessageToAll(COLOR_YELLOW, msgitem);
		SendClientMessage(playerid, COLOR_RED, msgitem);
	}*/
	if(dialogid != HOUSE_CONTROL_MENU) return 1;//для владения несколькими бизами
	if(!response) { PropertyHelp(playerid);	return 1; }
	new house = GetPVarInt(playerid, "House");

	if(MenuOperation[playerid] == 123)
	{
		if(listitem == 0) PrintHouseInfo(playerid, house);//houseinfo - информация по дому
		else if(listitem == 1)////home"
		{
			if(CP[playerid] != 0 && GetPVarInt(playerid, "gCheckpointStatus") != CHECKPOINT_NONE)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент воспользоваться этой командой !");
				return 1;
			}
	       	if(PlayerInfo[playerid][pInt] != 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны находится Не в Интерьере !");
				return 1;
			}
	        if(PlayerInfo[playerid][pJob] == LOADER)//if(gJobDuty[playerid])
			{
			    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы на работе Грузчика. Если хотите закончить рабочий день, идите в кассу.");
				return 1;
			}
			SetPlayerCheckpointEx(playerid,
				HouseInfo[house][hEntranceX],
				HouseInfo[house][hEntranceY],
				HouseInfo[house][hEntranceZ], CHECKPOINT_SIZE);
			GameTextForPlayerEx(playerid, "~w~Waypoint set ~r~Home", 5000, 1);
			SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_HOME);
		}
		else if(listitem == 2)///heal"
		{
			if(PlayerInfo[playerid][pLocal] == house && HouseInfo[house][hHel] == 1)
			{
				if(LastHealth[playerid] < 100.0)
				{
					if(GetPVarInt(playerid, "gHeal") == 0)
					{
						SetPlayerHealthEx(playerid, 100.0);
						PlaySoundForPlayer(playerid, SOUND_PICKUP_STANDARD);
						format(strings, sizeof(strings), "  Bы были полностью вылечены.");
						SendClientMessage(playerid, COLOR_GREEN,strings);
						SetPVarInt(playerid, "gHeal", 1);
					}
					else SendClientMessage(playerid, COLOR_GREY, "   Вы можете только 1 раз воспользоваться аптечкой в доме.");
				}
				else SendClientMessage(playerid, COLOR_GREY, "   Вы итак полностью здоровы.");
			}
			else SendClientMessage(playerid, COLOR_GREY, "   B этом месте нет аптечки.");
		}
		else if(listitem == 3)////read paper"
		{
			new location = GetHouseLocation(playerid);
	     	if(HouseInfo[location][hPaper] <= 0)
	     	{
		        SendClientMessage(playerid, COLOR_GREY, "   В этот дом ещё не поступала свежая пресса !");
		        return 1;
	     	}
	        new paper = HouseInfo[location][hPaper]-1;
			new bigmsgitem[1304]; new strtmp[70];
    		format(strtmp, sizeof(strtmp), "%s | News Reporter: %s\n", PaperInfo[paper][PaperTitle], PaperInfo[paper][PaperMaker]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
   			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText1]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
   			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText2]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText3]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText4]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText5]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText6]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText7]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText8]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText9]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText10]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			format(strtmp, sizeof(strtmp), "%s\n",PaperInfo[paper][PaperText11]);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			//format(strcmd, sizeof(strcmd), "Если Вам понравилась газета, нажмите кнопку 'YES'.\n");
			//strins(bigmsgitem, strcmd, strlen(bigmsgitem), strlen(strcmd));

			if(strlen(bigmsgitem) > sizeof(bigmsgitem))
			{
				//ИНФОРМИРОВАНИЕ
				format(strings, sizeof(strings), "Error39: Newspaper %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
					PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem) );
				Log(ERROR, strings);
				return 1;
			}
			if(strlen(bigmsgitem) <= 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Newspaper пуст");
				return 1;
			}
			ShowPlayerDialogEx(playerid, NEWS_DIALOG, DIALOG_STYLE_LIST, "Role Play: Newspaper", bigmsgitem, "YES", "NO");
		}
		else if(listitem == 4)//open - открыть/закрыть
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 30.0,HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы слишком далеко от вашего дома !");
				return 1;
			}
			if(HouseInfo[house][hLock] == 1)
			{
				HouseInfo[house][hLock] = 0;
				GameTextForPlayerEx(playerid, "~w~Houses ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				HouseInfo[house][hLock] = 1;
				GameTextForPlayerEx(playerid, "~w~Houses ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if(listitem == 5)///houseupgrade
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 30.0,HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы слишком далеко от вашего дома !");
				return 1;
			}
			new listitems[41*5];
			//strcat(listitems, "_____________ Home Supplys _____________{00FF00}");
			strcat(listitems, "1: {FFFFFF}Телевизор {00FF00}$500\n");
			strcat(listitems, "2: {FFFFFF}Аптечка {00FF00}$5000\n");//для экономики
			strcat(listitems, "3: {FFFFFF}Раздевалка {00FF00}$10000\n");
			//strcat(listitems, "{A9C4E4}_________________________________________");
			//strcat(listitems,"\nВведите № улучшения.\nПо окончанию ввода нажмите OK.");
			MenuOperation[playerid] = 124;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_LIST, HouseInfo[house][hDiscription], listitems, "OK", "Cancel");
		}
		else if(listitem == 6)///housewithdraw
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 30.0,HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы слишком далеко от вашего дома !");
				return 1;
			}
			format(strings, sizeof(strings), "Выручка за аренду = $%d.\n\
Введите сумму.\n\
Минимум - $1, Максимум - $%d.\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", HouseInfo[house][hTill], HouseInfo[house][hTill]);
			MenuOperation[playerid] = 125;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, HouseInfo[house][hDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 7)////setrent"
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 30.0,HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы слишком далеко от вашего дома !");
				return 1;
			}
			new dlgitem[25+74+59+35 + 6+6];
			format(dlgitem, sizeof(dlgitem), "Арендная плата = $%d.\n\
Введите сумму аренды. \nЧтобы запретить аренду введите сумму арренды 0\n\
Минимум - $100, Максимум - $%d.\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", HouseInfo[house][hRent], 10000);//HouseInfo[house][hBuyPrice]
			MenuOperation[playerid] = 126;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, HouseInfo[house][hDiscription], dlgitem, "OK", "Cancel");
		}
		else if(listitem == 8)///lessees"
		{
			new playername[MAX_PLAYER_NAME];
			//strmid(playername, text, 0, strlen(text), MAX_PLAYER_NAME);
			new giveplayerid = MAX_PLAYERS-2;
			new DialogIDCounter = 0;

			new bigmsgitem[16+(15+10+24+2)*20];
			strins(bigmsgitem, "ВЫСЕЛИТЬ ВСЕХ\n", strlen(bigmsgitem));
			DialogID[playerid][DialogIDCounter] = house;
			DialogIDCounter ++;

#if defined vw_sql//#endif
			new Field[34];
			new ToBase[86+3+24];
			format(ToBase, sizeof(ToBase), "SELECT `ID`,`Name`,`Level` FROM `players` WHERE `House`=%d AND `Name`<>'%s'", house, PlayerName(playerid));
			/*mysql_query(ToBase); mysql_store_result();
			while( mysql_retrieve_row() ) //будет идти пока не достигнет последней строки
			{
		        if(DialogIDCounter >= 20) break;
				mysql_fetch_field_row(Field, "ID");	PlayerInfo[giveplayerid][pSQLID] = strval(Field);
				mysql_fetch_field_row(PlayerInfo[giveplayerid][pName], "Name");
				mysql_fetch_field_row(Field, "Level");	PlayerInfo[giveplayerid][pLevel] = strval(Field);
				//SetPVarString(playerid, "playername", playername);

				new strtmp[15+10+24+2];
				if(strlen(playername) < 14) format(strtmp, sizeof(strtmp), "%d\t%s\t\t%d\n", PlayerInfo[giveplayerid][pSQLID], playername, PlayerInfo[giveplayerid][pLevel]);
				else format(strtmp, sizeof(strtmp), "%d\t%s\t%d\n", PlayerInfo[giveplayerid][pSQLID], playername, PlayerInfo[giveplayerid][pLevel]);
				strins(bigmsgitem, strtmp, strlen(bigmsgitem));

				DialogID[playerid][DialogIDCounter] = giveplayerid;
				DialogIDCounter ++;
			}
			mysql_free_result();*/
			
			new DBResult:db_result = db_query(db_VW, ToBase);
			do //будет идти пока не достигнет последней строки
			{
		        if(DialogIDCounter >= 20) break;
				db_get_field_assoc(db_result, "ID", Field, sizeof(Field) );   PlayerInfo[giveplayerid][pSQLID] = strval(Field);
				//db_get_field_assoc(db_result, "Name", Field, sizeof(Field) );   strmid(PlayerInfo[giveplayerid][pName], 0, strlen(Field), sizeof(Field));
				db_get_field_assoc(db_result, "Level", Field, sizeof(Field) );   PlayerInfo[giveplayerid][pLevel] = strval(Field);
				//SetPVarString(playerid, "playername", playername);

				new strtmp[15+10+24+2];
				if(strlen(playername) < 14) format(strtmp, sizeof(strtmp), "%d\t%s\t\t%d\n", PlayerInfo[giveplayerid][pSQLID], playername, PlayerInfo[giveplayerid][pLevel]);
				else format(strtmp, sizeof(strtmp), "%d\t%s\t%d\n", PlayerInfo[giveplayerid][pSQLID], playername, PlayerInfo[giveplayerid][pLevel]);
				strins(bigmsgitem, strtmp, strlen(bigmsgitem));

				DialogID[playerid][DialogIDCounter] = giveplayerid;
				DialogIDCounter ++;
			}
			while(db_next_row(db_result));
			
			db_free_result(db_result);
#else
			for(new j=0, i; j<MaxPlayers; j++)
			{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(strcmp(PlayerName(i), HouseInfo[house][hOwner], true)) continue;//если игрок не владелец то пропустить
		        if(DialogIDCounter >= 20) break;

				new strtmp[15+10+24+2];
				if(strlen(playername) < 14) format(strtmp, sizeof(strtmp), "%d\t%s\t\t%d\n", giveplayerid, playername, PlayerInfo[giveplayerid][pLevel]);
				else format(strtmp, sizeof(strtmp), "%d\t%s\t%d\n", giveplayerid, playername, PlayerInfo[giveplayerid][pLevel]);
				strins(bigmsgitem, strtmp, strlen(bigmsgitem));

				DialogID[playerid][DialogIDCounter] = giveplayerid;
				DialogIDCounter ++;
			}
			
#endif
			//strins(bigmsgitem, "\n\nВыбирите игрока для выселения\nИли выбирите ВЫСЕЛИТЬ ВСЕХ.\n\n\t{8CAA63}По окончанию ввода нажмите OK.", strlen(bigmsgitem));
			if(strlen(bigmsgitem) > sizeof(bigmsgitem) || strlen(bigmsgitem) <= 0)
			{
				//ИНФОРМИРОВАНИЕ
				format(strings, sizeof(strings), "Error: Lessees Online %s[%d], strlen(dlgitem): %d, sizeof(dlgitem): %d",
					PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
				Log(ERROR, strings);
				return 1;
			}
			MenuOperation[playerid] = 127;
			new caption[32+32+2];
			format(caption, sizeof(caption), "id             name               level - %s[%d]", HouseInfo[house][hDiscription], house);
			ShowPlayerDialogEx(playerid, PROP_DIALOG, DIALOG_STYLE_LIST, caption, bigmsgitem, "OK", "Cancel");
		}
		else if(listitem == 9)///sellhouse - продать
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 30.0,HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы слишком далеко от вашего дома !");
				return 1;
			}
			HouseInfo[house][hOwned] = 0;
			strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);
			HouseInfo[house][hLock] = 0;
			//HouseInfo[house][hRentabil] = 0;
			new curdate = getdate();//Получает текущий день в году
			HouseInfo[house][hDate] = curdate;//записать день продажи
			//--------------------------------------------------------------
			if(PlayerInfo[playerid][pLocal] == house)
			{
				SetPlayerVirtualWorldEx(playerid, 0);
			    SetPlayerInteriorEx(playerid, 0);
				PlayerInfo[playerid][pLocal] = FREEROAM;
				SetPlayerPosEx(playerid, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ], 0);
			}
			if(PlayerInfo[playerid][pPurposeMurder] == house) PlayerInfo[playerid][pPurposeMurder] = 0;

			GivePlayerMoneyB(house, playerid, floatround(HouseInfo[house][hBuyPrice]/2));

			for(new limit = 0; limit < 5; limit++)
			{
				if(MyHouse[playerid][limit] != house) continue;
				MyHouse[playerid][limit] = NOT_KEY;
			}
			PlayerInfo[playerid][pHouse] = NOT_KEY;//ВНИМАНИЕ нельзя т.к. домов может быть больше 1

			format(strings, sizeof(strings), "%s has sell house %d for $%d", PlayerName(playerid), house, floatround(HouseInfo[house][hBuyPrice]/2));
			Log(BUY,strings);

			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]", HouseInfo[house][hDiscription]);
			//Update3DTextLabelText(text3D[house], 0x88EE88FF, strings);
			Update3DTextLabelEx(hEntranceText3D[house], 0x88EE88FF, text_info);

			//--------------------------------------------------------------
			//выселяем арендаторов
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(i != playerid && PlayerInfo[i][pHouse] == house)
				{
					SendClientMessage(i, COLOR_OLIVE, "Вы выселены из дома.");
					PlayerInfo[i][pHouse] = NOT_KEY;
				}
			}
#if defined vw_sql//#endif
			new ToBase[118];//84+10+24 = 118
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY" WHERE `House`=%d AND `ID`<>%d", house, HouseInfo[house][hOwned]);
			//mysql_query(ToBase);
			db_free_result(db_query(db_VW, ToBase));
			//--------------------------------------------------------------
			SaveHouseSQL(house);
#endif
			format(strings, sizeof(strings), "~y~Congratulations~n~~w~You have sold your property for ~n~~g~$%d", floatround(HouseInfo[house][hBuyPrice]/2));
			GameTextForPlayerEx(playerid, strings, 10000, 3);
		}
	}
	//------------------------------------------------------------------
	else if(MenuOperation[playerid] == 124)///houseupgrade
	{
		if(listitem == 0)//TV
		{
			if(SBizInfo[6][sbProducts] <= 0 && !gRealWar)
			{
				GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~House Upgrade", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 500)
			{
				SendClientMessage(playerid, COLOR_GRAD5, "У вас не хватает денег, чтобы купить это");
				return 1;
			}
			if(HouseInfo[house][hTV] == 0)
			{
				HouseInfo[house][hTV] = 1;
				GivePlayerMoneyH(house, playerid, -500);
				OnGangsExtortionSBiz(6, 500);
				SBizInfo[6][sbProducts] --;
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
				SendClientMessage(playerid, COLOR_GRAD5, "Теперь вы можете смотреть TV, введите /tv.");
			}
			else SendClientMessage(playerid, COLOR_GREY, "   У вас уже установлен TV, введите /tv.");
		}
		else if(listitem == 1)//Health Upgrade
		{
			if(SBizInfo[6][sbProducts] <= 0 && !gRealWar)
			{
				GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~House Upgrade", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 5000)//для экономики
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько наличных для этого !");
				return 1;
			}
			if(HouseInfo[house][hHel] == 0)
			{
				HouseInfo[house][hHel] = 1;
				GivePlayerMoneyH(house, playerid, -5000);//для экономики
				OnGangsExtortionSBiz(6, 5000);
				SBizInfo[6][sbProducts] --;
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
				SendClientMessage(playerid, COLOR_GRAD5, "Вы Можете Теперь Излечить Себя Дома, Введите /heal.");
			}
			else SendClientMessage(playerid, COLOR_GREY, "   У вас уже установлена аптечка.");
		}
		else if(listitem == 2)//Clothes Upgrade
		{
	    	if(HouseInfo[house][hClothEntX] == 0 && HouseInfo[house][hClothEntY] == 0 && HouseInfo[house][hClothEntZ] == 0)
		    {
				SendClientMessage(playerid, COLOR_GREY, "   В вашем доме не предусмотрена раздевалка !");
				return 1;
		    }
			if(SBizInfo[6][sbProducts] <= 0 && !gRealWar)
			{
				GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~House Upgrade", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 10000)//для экономики
			{
				SendClientMessage(playerid, COLOR_GRAD5, "У вас не хватит денег, чтобы купить это");
				return 1;
			}
			if(HouseInfo[house][hCloth] == 0)
			{
				HouseInfo[house][hCloth] = 1;
				GivePlayerMoneyH(house, playerid, -10000);//для экономики
				OnGangsExtortionSBiz(6, 10000);
				SBizInfo[6][sbProducts] --;
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
				SendClientMessage(playerid, COLOR_GRAD5, "Вы можете теперь переодеваться в Вашей домашней Раздевалке.");
			}
			else SendClientMessage(playerid, COLOR_GREY, "   У вас уже установлена раздевалка.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Выбирети 1-3 строки в списке.");

			new listitems[41*5];
			//strcat(listitems, "_____________ Home Supplys _____________{00FF00}");
			strcat(listitems, "1: {FFFFFF}TV {00FF00}$500\n");
			strcat(listitems, "2: {FFFFFF}Health Upgrade {00FF00}$5000\n");//для экономики
			strcat(listitems, "3: {FFFFFF}Clothes Upgrade {00FF00}$10000\n");
			//strcat(listitems, "{A9C4E4}_________________________________________");
			strcat(listitems,"\nВведите № улучшения.\n\n\t{8CAA63}По окончанию ввода нажмите OK.");
			MenuOperation[playerid] = 124;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_LIST, HouseInfo[house][hDiscription], listitems, "OK", "Cancel");
			return 1;
		}
	}
	else if(MenuOperation[playerid] == 125)///housewithdraw
	{
		if(strval(inputtext) < 1 || strval(inputtext) > HouseInfo[house][hTill])//для экономики
		{
			format(strings, sizeof(strings), "Выручка за аренду = $%d.\n\
				Введите сумму.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", HouseInfo[house][hTill], HouseInfo[house][hTill]);
			MenuOperation[playerid] = 125;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, HouseInfo[house][hDiscription], strings, "OK", "Cancel");
			return 1;
		}
		GivePlayerMoneyH(house, playerid, strval(inputtext));
		HouseInfo[house][hTill] -= strval(inputtext);
		format(strings, sizeof(strings), "  Bы взяли $%d из вашего денежного ящика. Остаток: $%d ", strval(inputtext), HouseInfo[house][hTill]);
		SendClientMessage(playerid, COLOR_YELLOW, strings);

	}
	else if(MenuOperation[playerid] == 126)///setrent"
	{
		if(strval(inputtext) < 100 || strval(inputtext) > 10000)//для экономики //HouseInfo[house][hBuyPrice]
		{
			new dlgitem[25+74+59+6+6];
			format(dlgitem, sizeof(dlgitem), "Арендная плата = $%d.\n\
Введите сумму аренды. \nЧтобы запретить аренду введите сумму арренды 0\n\
Минимум - $100, Максимум - $%d.\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", HouseInfo[house][hRent], 10000);//HouseInfo[house][hBuyPrice]
			MenuOperation[playerid] = 126;
			ShowPlayerDialogGap(playerid, PROP_DIALOG, DIALOG_STYLE_INPUT, HouseInfo[house][hDiscription], dlgitem, "OK", "Cancel");
			return 1;
		}
		HouseInfo[house][hRent] = strval(inputtext);
		format(strings, sizeof(strings), "Aренда дома установлена в размере $%d", HouseInfo[house][hRent]);
		SendClientMessage(playerid, COLOR_OLIVE, strings);
	}
	else if(MenuOperation[playerid] == 127)///lessees"
	{
		if(listitem == 0)
		{
			//--------------------------------------------------------------
			//выселяем арендаторов
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(i != playerid && PlayerInfo[i][pHouse] == house)
				{
					SendClientMessage(i, COLOR_OLIVE, "Вы выселены из дома.");
					PlayerInfo[i][pHouse] = NOT_KEY;
				}
			}
#if defined vw_sql//#endif
			new ToBase[118];//84+10+24 = 118
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY" WHERE `House`=%d AND `ID`<>%d", house, HouseInfo[house][hOwned]);
			//mysql_query(ToBase);
			db_free_result(db_query(db_VW, ToBase));
#endif
			//--------------------------------------------------------------
		}
		else
		{
			new giveplayerid = DialogID[playerid][listitem];
#if defined vw_sql//#endif
			new ToBase[118];//84+10+24 = 118
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY" WHERE `House`=%d AND `Name`<>%d", house, PlayerInfo[giveplayerid][pName]);
			//mysql_query(ToBase);
			db_free_result(db_query(db_VW, ToBase));
#endif
			SendClientMessageEx(giveplayerid, COLOR_OLIVE, "Вы выселены из дома.");
			//new giveplayername[MAX_PLAYER_NAME]; GetPVarString(playerid, "playername", giveplayername, MAX_PLAYER_NAME);
			format(strings, sizeof(strings), "%s выселен из вашего дома", PlayerInfo[giveplayerid][pName]);
			SendClientMessage(playerid, COLOR_OLIVE, strings);

			PlayerInfo[giveplayerid][pHouse] = NOT_KEY;
		}
	}
	return 1;
}




stock OnCheckProp()//вызывается из OnPayDay5Timer
{   //проверка собственности каждый час, т.е. купленных домов
	for(new h = 0; h < MAX_HOUSE; h++)
	{
		if(HouseInfo[h][hOwned] == 0) continue; //если дом не куплен - пропустить
		new olddate = HouseInfo[h][hDate];
		new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
		if(curdate-olddate < gCheckProp) continue; //если прошло меньше 7 дней - пропустить

		//new strings[MAX_STRING];
		new playername[MAX_PLAYER_NAME];
		strmid(playername, HouseInfo[h][hOwner], 0, strlen(HouseInfo[h][hOwner]), MAX_PLAYER_NAME);
		//mysql_real_escape_string(playername, playername);

		new giveplayerid = ReturnUser( playername );
		//--------------------------------------------------------------
		//выселяем арендаторов
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(i != giveplayerid && PlayerInfo[i][pHouse] == h)
			{
				SendClientMessage(i, COLOR_OLIVE, "Вы выселены из дома.");
				PlayerInfo[i][pHouse] = NOT_KEY;
			}
		}
#if defined vw_sql//#endif
		new ToBase[118];//84+10+24 = 118
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY" WHERE `House`=%d", h);
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif
		//--------------------------------------------------------------
		if( !IsPlayerConnected(giveplayerid) )
		{
			if(CheckExistPlayer(giveplayerid, playername) > 0) //return 1;
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
	    		giveplayerid = MAX_PLAYERS-2;
#if defined vw_sql//#endif
				new ToBase[98];//71+24+3 = 98 //84+10+24 = 118
				format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE `Name`='%s' AND `Account`>=%d LIMIT 1", playername, getdate());
				
				/*mysql_query(ToBase); mysql_store_result();
				if(mysql_num_rows())
				{
					mysql_free_result();
					continue;
				}
				else mysql_free_result();
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY", `Bank`=`Bank`+%d WHERE `Name`='%s'",
					HouseInfo[h][hBuyPrice], playername);
				mysql_query(ToBase);*/
				
				new DBResult:db_result = db_query(db_VW, ToBase);
				if(db_num_rows(db_result))
				{
					db_free_result(db_result);
					continue;
				}
				else db_free_result(db_result);
				
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY", `Bank`=`Bank`+%d WHERE `Name`='%s'",
					HouseInfo[h][hBuyPrice], playername);
    			db_free_result(db_query(db_VW, ToBase));
#endif
			}
		}
		else
		{
			if(PlayerInfo[giveplayerid][pAccount] != 0) continue; //return 1;
			for(new limit = 0; limit < 5; limit++)
			{
				if(MyHouse[giveplayerid][limit] != h) continue;
				MyHouse[giveplayerid][limit] = NOT_KEY;
			}
			PlayerInfo[giveplayerid][pHouse] = NOT_KEY;
			PlayerInfo[giveplayerid][pBank] += HouseInfo[h][hBuyPrice];
		}
		//SendClientMessage(playerid, COLOR_OLIVE, "Все выселены.");
		//--------------------------------------------------------------
		//HouseInfo[h][hHel] = 0;
		//HouseInfo[h][hCloth] = 0;
		//HouseInfo[h][hTV] = 0;
		HouseInfo[h][hLock] = 1;
		HouseInfo[h][hOwned] = 0;
		HouseInfo[h][hDate] = curdate;
		format(strings, sizeof(strings), "REAL ESTATE: Дом %s[%d] %s'а был выставлен на аукцион и продан за $%d",
			HouseInfo[h][hDiscription], h, HouseInfo[h][hOwner], HouseInfo[h][hBuyPrice]);
		SendClientMessageToAll(0x88EE88FF, strings);
		strmid(HouseInfo[h][hOwner], "The State", 0, strlen("The State"), 24);//меняем имя владельца на The State
#if defined vw_sql//#endif
		SaveHouseSQL(h);
#endif
		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]",HouseInfo[h][hDiscription]);
		//Update3DTextLabelText(text3D[h], 0x88EE88FF, strings);
		UpdatePlayer3DTextLabelTextEx(MAX_PLAYERS-1, hEntranceText3D[h], 0x88EE88FF, text_info);

		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "REAL ESTATE: %s has sell house %d for $%d(curdate=%d, olddate=%d)", playername, h, HouseInfo[h][hBuyPrice], curdate, olddate);
		Log(BUY,strings);


	}
	return 1;
}

/*
stock house_OnPlayerPickUp(playerid, pickupid)
stock clothes_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	new house;
	if(PlayerInfo[playerid][pHouse] == PlayerInfo[playerid][pLocal] && PlayerInfo[playerid][pLocal] < 100) house = PlayerInfo[playerid][pLocal];

//для раздевалки в доме
	if(IsPlayerInRangeOfPoint(playerid, 2.1, HouseInfo[house][hClothEntX],HouseInfo[house][hClothEntY],HouseInfo[house][hClothEntZ]))
	{
	    if(HouseInfo[house][hCloth] == 1)
		{
			//если вы арендатор или хозяин дома и в доме куплена раздевалка
			//PlayerInfo[playerid][pLocal] = local;//записали ID дома
			SetPlayerVirtualWorldEx(playerid, house);//local);//0
			SetPlayerInteriorEx(playerid, 14);//установить интерьер
			SetPlayerPosEx(playerid, 256.8213,-41.5293,1002.0234, 0);//переместить игрока
			GameTextForPlayerEx(playerid, "~w~Welcome Clothes", 5000, 1);
			//return 1;
		}
	}
	else if( IsPlayerInRangeOfPoint(playerid, 2.1, 254.3039,-41.5549,1002.2234))
	{   //если игрок у выхода из раздевалки
		SetPlayerVirtualWorldEx(playerid, house);
		SetPlayerInteriorEx(playerid, HouseInfo[house][hInt]);
		SetPlayerPosEx(playerid, HouseInfo[house][hClothExX],HouseInfo[house][hClothExY],HouseInfo[house][hClothExZ], 0);
		//return 1;
	}
	return 1;
}*/

///тяжёлая ф-ия = 3302
//stock OnPayDay5Timer(playerid)
stock house_OnFiveMinutsTimer(playerid)
{
	//new ToBase[83];//56+3+24 = 83
//для снятие дома если уровень достиг предела
		/*for(new limit = 0; limit < 5; limit++)
		{
			if(MyHouse[playerid][limit] == NOT_KEY) continue;
			new house = MyHouse[playerid][limit];
			if(	PlayerInfo[playerid][pLevel] - HouseInfo[house][hLevel] > 5 &&
			 	PlayerInfo[playerid][pLevel] < 25)
			{

				HouseInfo[house][hHel] = 0;
				HouseInfo[house][hCloth] = 0;
				HouseInfo[house][hTV] = 0;
				HouseInfo[house][hLock] = 0;
				HouseInfo[house][hOwned] = 0;
				HouseInfo[house][hLock] = 0;
				//HouseInfo[house][hRentabil] = 0;
				strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);

				if(PlayerInfo[playerid][pLocal] == house)
				{
					SetPlayerVirtualWorldEx(playerid, 0);
				    SetPlayerInteriorEx(playerid, 0);
					PlayerInfo[playerid][pLocal] = FREEROAM;
					SetPlayerPosEx(playerid, HouseInfo[house][hEntranceX],HouseInfo[house][hEntranceY],HouseInfo[house][hEntranceZ], 0);
				}
				GivePlayerMoneyB(house, playerid, HouseInfo[house][hBuyPrice]);

				MyHouse[playerid][limit] = NOT_KEY;
				PlayerInfo[playerid][pHouse] = NOT_KEY;
				//OnPlayerStatsUpdate(playerid);

				new text_info[19+20+24];
		    	format(text_info, sizeof(text_info), "[ %s ]",HouseInfo[house][hDiscription]);
				//Update3DTextLabelText(text3D[house], 0x88EE88FF, strings);
				UpdatePlayer3DTextLabelTextEx(playerid, hEntranceText3D[house], 0x88EE88FF, text_info);

				//format(strings, sizeof(strings), "~y~Congratulations~n~~w~You have sold your property for ~n~~g~$%d", HouseInfo[house][hBuyPrice]);
				//GameTextForPlayerEx(playerid, strings, 10000, 3);
				format(strtmp, sizeof(strtmp), "Ваш дом №%d продан, т.к. ваш уровень[pLevel: %d] выше уровня дома[hLevel: %d] на 6.",
					house, PlayerInfo[playerid][pLevel], HouseInfo[house][hLevel]);
				SendClientMessage(playerid, COLOR_GRAD6, strtmp);
				format(strtmp, sizeof(strtmp), "Сумма в $%d возвращена на ваш расчётный счёт.", HouseInfo[house][hBuyPrice]);
				SendClientMessage(playerid, COLOR_GRAD6, strtmp);
				break;
			}
		}*/
	//==========================================================================
//END
	//для монитора
	//PlayerInfo[playerid][pOffline] = 0;//потом сохраняем в OnPlayerStatsUpdate
	//if(gPlayerLogged[playerid] == 1)
	//if(AFK_IdleTime[playerid] < 3) OnPlayerStatsUpdate(playerid, 5);//сохранять после начисления ЗП

	//new str[50];//16+24+10 = 50
	//format(str, sizeof(str), "OnPayDay5Timer %s[%d]", PlayerName(playerid), PlayerInfo[playerid][pSQLID]);//Итого
	//TestLog(OPTIM, str, GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}//END OnPayDay5Timer


