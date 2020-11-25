//красивой оформление таблиц https://wiki.redage.net/index.php?title=%D0%9A%D0%BD%D0%B8%D0%B3%D0%B0_%D1%80%D0%B5%D0%BA%D0%BE%D1%80%D0%B4%D0%BE%D0%B2





//##############################################################################//
//                                                                              //
//                             СУПЕР КРУТАЯ АДМИНКА                             //
//                                                                              //
//##############################################################################//

//##############################################################################//
//                                                                              //
//                           БЛОКИ АВТОЗАМЕНЫ  (stock)                          //
//                                                                              //
//##############################################################################//
// обязательно начинаются с названия скрипта
// если ф-ия не имеет вначале названия скрипта, значит она применяется только в этом скрипте
//==============================================================================
/*public OnGameModeInit()
//stock admin_Settings(playerid)
//stock settings_OnGameModeInit()
{
	new listitems[1426];

	new strtmp[6+64+64];
	format(strtmp, sizeof(strtmp), "%s %s", GMText, VERSION);
	SetGameModeText(strtmp); //Выводит названия вашего гейммода в списке серверов (имя Мода в столбе Mode SA:MP)
	SetTeamCount(DoE+1);//Устанавливает максимальное число команд в игре.
	ShowNameTags(1);//Используйте эту функцию для включения/выключения подсвечивания над игроками их имен.
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);//Маркеры Игрока только видимые, чтобы около игроков
	if(gRrealTime == 0)//если время изменено
	{
		SetWorldTime(wtime);//Меняет время игры на указанное в переменной wtime=15
		//можно использовать при включении игрового времени
	}
	else if(gRrealTime == 1)//если флаг gRrealTime поднят, т.е. у нас счас реальное время
	{
		//gday = getdate();
		gettime(ghour, _, _);//Получает текущее время на сервере, которое запишется в переменные &hour, &minute и &second.
		//FixHour(ghour);//передали значение часа, а получилил скорректированное
		//ghour = shifthour;//записали скорректированное на величину timeshift
		SetWorldTime(ghour);//установили игровое время
		getdate(_,_,LastDay);
	}
	EnableTirePopping(1);//При помощи этой функции вы можете включить или выключить прокалывание/простреливание шин.
 	EnableVehicleFriendlyFire();//Включите дружественный огонь для командных автомобилей. Игроки не смогут повредить машины товарищей по команде (необходимо использовать SetPlayerTeam!).
 	AllowInteriorWeapons(1);//Переключить, разрешено ли использование оружия в интерьере или нет.
	SetWeather(2);//По умолчанию было 10 в самп 0.3 стало 1.
	//SetGravity(0.008);//Установить гравитацию в мире
 	AllowAdminTeleport(1);
	//DisableInteriorEnterExits();//Отключает все входы/выходы в/из интериоров (желтые маркеры).)
	SetNameTagDrawDistance(NameTagDrawDistance);//60.0 //20.0 Устанавливает расстояния отображения имен игроков.
	LimitGlobalChatRadius(chat_radius);//30 Float:chat_radius Включить ограничение радиуса чата. Только игроки на определенном расстоянии от игрока будут видеть его сообщения в чате.
	LimitPlayerMarkerRadius(300.0);//Set the player marker radius.
	EnableStuntBonusForAll(1);//включает награду за трюки
	//DisableNameTagLOS();//видить ники через объекты	//Disables the nametag Line-Of-Sight checking so players can see nametags through objects.
	//ManualVehicleEngineAndLights();//отключить автозапуск двигателя
	//return 1;
}*/



stock admin_OnPlayerClick(playerid, forplayerid)
{   //вызывается из OnPlayerClickPlayer, LookingUpdate
	//if(!IsPlayerConnected(forplayerid)) { return 1; }
	//if(IsPlayerNPC(forplayerid)) { return 1; }
	//ClearAnimations(playerid);

    SetPVarInt(playerid, "ForPlayerID", forplayerid);
	new caption[70+1];
    format(caption, sizeof(caption), "Вы выбрали игрока %s[%d].", PlayerName(forplayerid), forplayerid);
/*
	new Float:health;	GetPlayerHealth(forplayerid, health);
	new Float:pX, Float:pY, Float:pZ; //new Float:pA, Float:ang;
	GetPlayerPos(forplayerid, pX, pY, pZ);	//GetPlayerFacingAngle(forplayerid, pA);
	new Float: armour;	GetPlayerArmour(forplayerid, armour);
*/
	new listitems[64*31]; 	//new strtmp[64+6*3];
	strcat(listitems, 				"{0080FF}1.\t{FFFFFF}Меню разработчика\n");
	strcat(listitems, 				"{0080FF}2.\t{FFFFFF}Меню админа\n");
	strcat(listitems, 				"{0080FF}3.\t{FFFFFF}Меню игрока\n");
	strcat(listitems, 				"{0080FF}4.\t{FFFFFF}Информация об игроке\n");
	strcat(listitems, 				"{0080FF}5.\t{FFFFFF}Редактор параметров игрока\n");
	if(GetPVarType(playerid, "FlyMode") == 0) {
		strcat(listitems, 			"{0080FF}6.\t{FFFFFF}Редактор камеры\n");	}
	else { strcat(listitems, 		"{0080FF}6.\t{FFFFFF}Редактор камеры\n"); }
	strcat(listitems, 				"{0080FF}7.\t{FFFFFF}Редактор объектов\n");
	strcat(listitems, 				"{0080FF}8.\t{FFFFFF}Редактор анимаций\n");
	strcat(listitems, 				"{0080FF}9.\t{FFFFFF}Редактор актёров\n");
	strcat(listitems, 				"{0080FF}10.\t{FFFFFF}Редактор звуков\n");
	
	/*if(spectateCameraON[playerid] == false) {
		strcat(listitems, 			"{0080FF}9.\t{FF0000}Начать наблюдение\n");	}
	else { strcat(listitems, 		"{0080FF}9.\t{0080FF}Закончить наблюдение\n"); }*/
	//--------------------------------------------------------------------------
	//strcat(listitems, 				"{0080FF}10.\t{0080FF}Пожаловаться на игрока\n");
	if( strlen(listitems) > sizeof(listitems) )
	{
		format(strings, sizeof(strings), "AdmWarning: strlen(info):%d > sizeof(listitems):%d", strlen(listitems), sizeof(listitems));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	if( strlen(caption) > sizeof(caption) )
	{
		format(strings, sizeof(strings), "AdmWarning: strlen(caption):%d > sizeof(caption):%d", strlen(caption), sizeof(caption));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	ShowPlayerDialogGap(playerid, ADMIN_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "OK", "Exit");
	return 1;
}
stock admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused inputtext
	backadmin_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	DeveloperDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != ADMIN_DIALOG) return 1;
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
	
	if(!response)
	{
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}
	if(listitem == 0) DeveloperMenu(playerid, giveplayerid);//Меню разработчика
	else if(listitem == 1) AdminMenu(playerid, giveplayerid);//Меню админа
	else if(listitem == 2) PlayerMenu(playerid);//Меню игрока
	else if(listitem == 3) { SetPVarInt(playerid, "gDocuments", 1); InfoOfPlayer(playerid, giveplayerid); }//Информация об игроке

	else if(listitem == 4) PlayerInfoMenu(playerid, giveplayerid);//Редактор параметров игрока
	else if(listitem == 5)
	{
		if(GetPVarType(playerid, "FlyMode"))
		{
			CancelFlyMode(playerid);
			noclipdata[playerid][lrold]	   	 	= 0;
			noclipdata[playerid][udold]   		= 0;
			noclipdata[playerid][mode]   		= 0;
			noclipdata[playerid][lastmove]   	= 0;
			noclipdata[playerid][accelmul]   	= 0.0;

			IsCamMoving[playerid] 				= false;
			coordInfo[playerid][MoveSpeed] 		= 1000;
			coordInfo[playerid][RotSpeed] 		= 1000;
		}
		else FlyMode(playerid);
	}
	else if(listitem == 6) attach_IndexSelection(playerid);
	else if(listitem == 7) aview_AnimList(playerid);
	else if(listitem == 8) ShowPlayerDialog_CheckForAC(playerid, DACT, DIALOG_STYLE_LIST, "Актёры от Oleg_Petrow","Создать нового актёра\nПросмотр списка актёров\nУдалить всех актёров\nСохранить всех актёров\nНастройки","Далее","Выход");
	else if(listitem == 9) sound_ShowDialog(playerid);
	/*else if(listitem == 8)
	{
		if(spectateCameraON[playerid] == false) {
			recon_StartSpectate(playerid, giveplayerid); }
		else recon_SpecOff(playerid, giveplayerid);
	}*/
	
	//else if(listitem == 5) ComplaintSystem(playerid, giveplayerid);//Пожаловаться на игрока
	return 1;
}
stock backadmin_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BACKADMIN_DIALOG) return 1;
//ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "*** CAR HELP *** наберите команду для информации", listitems, "OK", "Назад");
	if(!response)
	{
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		DeveloperMenu(playerid, giveplayerid);
		return 1;
	}
	PlaySoundForPlayer(playerid, 5202);
	return 1;
}

//stock admin_OnPlayerClick(playerid, forplayerid)
stock DeveloperMenu(playerid, forplayerid)
{   //вызывается из OnPlayerClickPlayer, LookingUpdate
	//if(!IsPlayerConnected(forplayerid)) { return 1; }
	//if(IsPlayerNPC(forplayerid)) { return 1; }
	//ClearAnimations(playerid);
    SetPVarInt(playerid, "ForPlayerID", forplayerid);
	new caption[70+1];
    format(caption, sizeof(caption), "Вы выбрали игрока %s[%d]", PlayerName(forplayerid), forplayerid);

	new listitems[64*31]; 	new strtmp[64+6*3];
	new Float:health;	GetPlayerHealth(forplayerid, health);
	new Float:pX, Float:pY, Float:pZ; //new Float:pA, Float:ang;
	GetPlayerPos(forplayerid, pX, pY, pZ);	//GetPlayerFacingAngle(forplayerid, pA);
	new Float: armour;	GetPlayerArmour(forplayerid, armour);
	strcat(listitems, 				"{FFFFFF}1.\t{0080FF}Создать тачку возле игрока\n");
	format(strtmp, sizeof(strtmp), 	"{FFFFFF}2.\t{0080FF}Установить позицию:{FFFFFF}%.1f,%.1f,%.1f\n", pX, pY, pZ);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"{FFFFFF}3.\t{0080FF}Установить спаун:{FFFFFF}%.1f,%.1f,%.1f\n",
		spawnPos[0][forplayerid], spawnPos[1][forplayerid], spawnPos[2][forplayerid] );
	strcat(listitems, strtmp);
	
	if(	IsPlayerInRangeOfPoint(forplayerid, 10, spawnPos[0][forplayerid], spawnPos[1][forplayerid], spawnPos[2][forplayerid])	) {
		strcat(listitems, 				"{FFFFFF}4.\t{FF0000}Отреспаунить игрока\n");	}
	else {  strcat(listitems, 			"{FFFFFF}4.\t{0080FF}Отреспаунить игрока\n"); }

	if(GetPlayerInterior(forplayerid) == 0) {
		format(strtmp, sizeof(strtmp),	"{FFFFFF}5.\t{0080FF}Установить интерьер(0-18):{FFFFFF}%d[%d]\n", GetPlayerInterior(forplayerid), CurInt[playerid]);	strcat(listitems, strtmp); }
	else { format(strtmp, sizeof(strtmp), "{FFFFFF}5.\t{FF0000}Установить интерьер(0-18):{FFFFFF}%d[%d]\n", GetPlayerInterior(forplayerid), CurInt[playerid]);	strcat(listitems, strtmp); }

	if(GetPlayerVirtualWorld(forplayerid) == 0) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}6.\t{0080FF}Установить мир:{FFFFFF}%d\n", GetPlayerVirtualWorld(forplayerid));	strcat(listitems, strtmp);	}
	else { format(strtmp, sizeof(strtmp),"{FFFFFF}6.\t{FF0000}Установить мир:{FFFFFF}%d\n", GetPlayerVirtualWorld(forplayerid));	strcat(listitems, strtmp); }

	if(health == 100.0) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}7.\t{0080FF}Установить здоровье:{FFFFFF}%.0f\n", health);	strcat(listitems, strtmp); }
	else { format(strtmp, sizeof(strtmp), "{FFFFFF}7.\t{FF0000}Установить здоровье:{FFFFFF}%.0f\n", health);	strcat(listitems, strtmp); }

	if(armour == 0.0) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}8.\t{0080FF}Установить броню:{FFFFFF}%.0f\n", armour);	strcat(listitems, strtmp); }
	else { format(strtmp, sizeof(strtmp),	"{FFFFFF}8.\t{FF0000}Установить броню:{FFFFFF}%.0f\n", armour);	strcat(listitems, strtmp); }

	if(GetPlayerTeam(forplayerid) == 255) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}9.\t{0080FF}Присоединить к группе:{FFFFFF}%d\n", GetPlayerTeam(forplayerid));	strcat(listitems, strtmp); }
	else { format(strtmp, sizeof(strtmp),	"{FFFFFF}9.\t{FF0000}Присоединить к группе:{FFFFFF}%d\n", GetPlayerTeam(forplayerid));	strcat(listitems, strtmp); }

	if(GetPlayerScore(forplayerid) == 0) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}10.\t{0080FF}Установить Уровень:{FFFFFF}%d\n", GetPlayerScore(forplayerid));	strcat(listitems, strtmp); }
	else { format(strtmp, sizeof(strtmp),"{FFFFFF}10.\t{FF0000}Установить Уровень:{FFFFFF}%d\n", GetPlayerScore(forplayerid));	strcat(listitems, strtmp); }

	if(GetPlayerDrunkLevel(forplayerid) == 0) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}11.\t{0080FF}Установить опьянение:{FFFFFF}%d\n", GetPlayerDrunkLevel(forplayerid));	strcat(listitems, strtmp); }
	else { format(strtmp, sizeof(strtmp),"{FFFFFF}11.\t{FF0000}Установить опьянение:{FFFFFF}%d\n", GetPlayerDrunkLevel(forplayerid));	strcat(listitems, strtmp); }

	format(strtmp, sizeof(strtmp), 	"{FFFFFF}12.\t{%06x}Установить цвет ника игрока:{FFFFFF}%d\n",  GetPlayerColor(forplayerid) >>> 8, GetPlayerColor(forplayerid)); strcat(listitems, strtmp);

	format(strtmp, sizeof(strtmp), 	"{FFFFFF}13.\t{0080FF}Поменять скин:{FFFFFF}%d\n", GetPlayerSkin(forplayerid));	strcat(listitems, strtmp);

	format(strtmp, sizeof(strtmp), 	"{FFFFFF}14.\t{0080FF}Установить оружие:{FFFFFF}%d[%d]\n", GetPlayerWeapon(forplayerid), GetPlayerAmmo(forplayerid));	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"{FFFFFF}15.\t{0080FF}Установить скил выбранного оружия:{FFFFFF}%d\n", GetPlayerGunSkill(forplayerid, GetPlayerWeapon(forplayerid)));	strcat(listitems, strtmp);

	if(!IsPlayerWeapon(forplayerid)) {
		strcat(listitems, 			"{FFFFFF}16.\t{0080FF}Сбросить всё оружие\n");	}
	else { strcat(listitems, 		"{FFFFFF}16.\t{FF0000}Сбросить всё оружие\n"); }

	format(strtmp, sizeof(strtmp), 	"{FFFFFF}17.\t{0080FF}Установить деньги:{FFFFFF}$%d\n", GetPlayerMoneyH(forplayerid));	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"{FFFFFF}18.\t{0080FF}Установить имя игрока:{FFFFFF}%s\n", PlayerName(forplayerid));	strcat(listitems, strtmp);

	if(GetPVarInt(forplayerid, "gPlayerClock") == 0) {
		strcat(listitems, 			"{FFFFFF}19.\t{FF0000}Включить часики\n");	}
	else { strcat(listitems, 		"{FFFFFF}19.\t{0080FF}Выключить часики\n"); }

	new hour, minutes;
	GetPlayerTime(forplayerid, hour, minutes);
	format(strtmp, sizeof(strtmp), 	"{FFFFFF}20.\t{0080FF}Установить время:{FFFFFF}%02d:%02d\n", hour, minutes);	strcat(listitems, strtmp);

	format(strtmp, sizeof(strtmp), 	"{FFFFFF}21.\t{0080FF}Установить погоду:{FFFFFF}%d\n", GetPVarInt(playerid, "PlayerWeather"));	strcat(listitems, strtmp);

	if(GetPlayerWantedLevel(forplayerid) == 0) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}22.\t{0080FF}Установить розыск:{FFFFFF}%d\n", GetPlayerWantedLevel(forplayerid));	strcat(listitems, strtmp);	}
	else { format(strtmp, sizeof(strtmp),"{FFFFFF}22.\t{FF0000}Установить розыск:{FFFFFF}%d\n", GetPlayerWantedLevel(forplayerid));	strcat(listitems, strtmp); }

	if(GetPlayerFightingStyle(forplayerid) == 4) {
		format(strtmp, sizeof(strtmp), 	"{FFFFFF}23.\t{0080FF}Установить стиль боя:{FFFFFF}%d\n", GetPlayerFightingStyle(forplayerid));	strcat(listitems, strtmp);	}
	else { format(strtmp, sizeof(strtmp),"{FFFFFF}23.\t{FF0000}Установить стиль боя:{FFFFFF}%d\n", GetPlayerFightingStyle(forplayerid));	strcat(listitems, strtmp); }



	if(!IsPlayerControllable[forplayerid]) {
		strcat(listitems, 			"{FFFFFF}24.\t{0080FF}Замарозить игрока\n");
	}else { strcat(listitems, 		"{FFFFFF}24.\t{FF0000}Размарозить игрока\n"); }

	if(GetPVarInt(playerid, "gSpectating") == 0) {
		strcat(listitems, 			"{FFFFFF}25.\t{0080FF}Включить режим зрителя\n");
	}else { strcat(listitems, 		"{FFFFFF}25.\t{FF0000}Отключить режим зрителя\n"); }

	if(!IsPlayerInAnyVehicle(forplayerid)) {
		strcat(listitems, 			"{FFFFFF}26.\t{0080FF}Выкинуть из тачки\n");
	}	else { strcat(listitems, 	"{FFFFFF}26.\t{FF0000}Выкинуть из тачки\n"); }
	
	if(IsPlayerInAnyVehicle(forplayerid)) {
		strcat(listitems, 			"{FFFFFF}27.\t{0080FF}Посадить в тачку\n");
	}	else { strcat(listitems, 	"{FFFFFF}27.\t{FF0000}Посадить в тачку\n"); }
	
	strcat(listitems, 				"{FFFFFF}28.\t{0080FF}Телепорт игрока\n");
	strcat(listitems, 				"{FFFFFF}29.\t{0080FF}Телепорт к игроку\n");
	strcat(listitems, 				"{FFFFFF}30.\t{0080FF}Телепорт на метку\n");

	strcat(listitems, 				"{FFFFFF}31.\t{0080FF}Телепорт к дому\n");
	strcat(listitems, 				"{FFFFFF}32.\t{0080FF}Телепорт к бизу\n");
	strcat(listitems, 				"{FFFFFF}33.\t{0080FF}Телепорт к компании\n");

	strcat(listitems, 				"{FFFFFF}34.\t{0080FF}Включить проверку public\n");
	strcat(listitems, 				"{FFFFFF}35.\t{0080FF}Расстояние до точки\n");

//SetPlayerShopName
//EnableStuntBonusForPlayer(playerid, 1);
//if(IsPlayerAttachedObjectSlotUsed(giveplayerid, CUFF_SLOT)) RemovePlayerAttachedObject(giveplayerid, CUFF_SLOT);
//SetPlayerSpecialAction(giveplayerid, SPECIAL_ACTION_NONE);
		
	/*
	format(strtmp, sizeof(strtmp), 	"{FFFFFF}25.\t{0080FF}Следить за игроком. Наблюдает: {FFFFFF}%d\n", PlayerName(forplayerid), forplayerid);	strcat(listitems, strtmp);
	if(PlayerInfo[forplayerid][pMuted] <= 0 || PlayerInfo[forplayerid][pMuted] < GetTickCount()) {
		strcat(listitems, 			"{FFFFFF}26.\t{0080FF}Заглушить игрока\n");
	}
	else { strcat(listitems, 		"{FFFFFF}26.\t{FF0000}Разглушить игрока\n"); }
	strcat(listitems, 				"{FFFFFF}29.\t{0080FF}Забанить игрока\n");
	*/

	if( strlen(listitems) > sizeof(listitems) )
	{
		format(strings, sizeof(strings), "AdmWarning: strlen(info):%d > sizeof(listitems):%d", strlen(listitems), sizeof(listitems));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	if( strlen(caption) > sizeof(caption) )
	{
		format(strings, sizeof(strings), "AdmWarning: strlen(caption):%d > sizeof(caption):%d", strlen(caption), sizeof(caption));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "Ок", "Назад");
	return 1;
}

stock DeveloperDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != DEVELOPER_DIALOG) return 1;// && dialogid != H_DIALOG
	if(!response)
	{
		DeletePVar(playerid, "Action");
		/*DeletePVar(playerid, "InputValue");
		DeletePVar(playerid, "InputCounter");
		DeletePVar(playerid, "ForPlayerID");*/
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		admin_OnPlayerClick(playerid, giveplayerid);//PlayerMenu(playerid);
		return 1;
	}
	new msgitem[256+1];
	new Float:pX, Float:pY, Float:pZ, Float:pA; //new Float:ang;
	//new Float:vX, Float:vY, Float:vZ;//, Float:vA;
	new Array[4][MAX_STRING];//40
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
	/*if(!IsPlayerAdmin(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
		return 1;
	}*/

	/*if(CHECKING == 1)
	{//ИНФОРМИРОВАНИЕ
	format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, \
Action:%d, InputCounter:%d) InputValue:%d",
playerid, giveplayerid,
GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter"), strval(inputtext));
GetPVarInt(playerid, "InputValue"), GetPVarInt(giveplayerid, "InputValue"));
	SendClientMessage(playerid, COLOR_PURPLE, strings);
	}*/
//==============================================================================
	if(GetPVarInt(playerid, "Action") == 0)
	{//если операция ещё не выбрана, т.е. это ввод первого параметра
	    //не забыть обнулить при окончанию ввода параметров
		//if(dialogid == DEVELOPER_DIALOG)
		SetPVarInt(playerid, "Action", listitem+1);//записали выбранную операцию
		//else  SetPVarInt(playerid, "Action", listitem+100);//записали выбранную операцию

		DeletePVar(playerid, "InputCounter");//очистили от предыдущих операций
	}
	new operation = GetPVarInt(playerid, "Action");
//------------------------------------------------------------------------------
	if(operation == 1)//Создать тачку
	{
		DeletePVar(playerid, "Action");
   	    SetPVarInt(playerid, "TotalItems", 212); //gTotalItems = 212;
	    if(GetPVarInt(playerid, "page_active") != 3) {	SetPVarInt(playerid, "chang_page", 0);  } //19);
		SetPVarInt(playerid, "page_active", 3);//1 - скины или 3 - тачки

#if defined vw_changer
		//SetTimerEx("PausePlayerTextDraw", 100, 0, "i", playerid);
		changer_CreateSelectionMenu(playerid);
#endif
	}
	else if(operation == 2)//Установить позицию
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			//new Float:pX, Float:pY, Float:pZ, Float:pA;
			/*if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 100)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}*/
			new idx;
			Array[0] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[0]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z,Ang");//,[Ang]
				return 1;
			}
			pX = floatstr(Array[0]);//Конвертирует строку в соответствующее вещественное число.

			Array[1] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[1]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z,Ang");//,[Ang]
				return 1;
			}
			pY = floatstr(Array[1]);

			Array[2] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[2]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z,Ang");//,[Ang]
				return 1;
			}
			pZ = floatstr(Array[2]);

			Array[3] = strtoko(inputtext, idx, ',');
			pA = floatstr(Array[3]);

			//format(strcmd, sizeof(strcmd), "SetAngle(%d, %.4f)", playerid, Ang);
			//SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				SetVehiclePosEx(GetPlayerVehicleID(giveplayerid), pX, pY, pZ);
			}
			else
			{
				SetPlayerPosEx(playerid, pX, pY, pZ, pA);
				//SetPlayerPosFindZ(giveplayerid, pX, pY, pZ);
			}
			
 			//format(strcmd, sizeof(strcmd), "SetPos(%d, %.4f, %.4f, %.4f)", giveplayerid, pX, pY, pZ);
			//SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's SetPos(%d, %.4f, %.4f, %.4f)", PlayerName(playerid), PlayerName(giveplayerid), giveplayerid, pX, pY, pZ);
			//Log(ADMINLOG, msgitem);
			//ABroadCast(COLOR_RED, msgitem, 9);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);

	    	//SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы телепорнули игрока по новым координатам !");
			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 3)//Установить спаун
	{
		//GetPlayerPos(giveplayerid, pX, pY, pZ);
		GetPlayerFacingAngle(giveplayerid, pA);
		
		PlayerInfo[playerid][pPos_x] = CurPos[0][giveplayerid];
		PlayerInfo[playerid][pPos_y] = CurPos[1][giveplayerid];
		PlayerInfo[playerid][pPos_z] = CurPos[2][giveplayerid];
		
		SetSpawnInfoEx(giveplayerid, GetPlayerTeam(giveplayerid), GetPlayerSkin(giveplayerid),
			CurPos[0][giveplayerid], CurPos[1][giveplayerid], CurPos[2][giveplayerid], pA,
			//302.4, 1998.0, 18.0, 0.0,
			//weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
			-1, -1, -1, -1, -1, -1);
		//SpawnPlayer(giveplayerid);

		//SetPVarInt(giveplayerid, "pModel", GetPlayerSkin(playerid));
		//SetPVarFloat(giveplayerid, "sX", pX);
		//SetPVarFloat(giveplayerid, "sY", pY);
		//SetPVarFloat(giveplayerid, "sZ", pZ);

		/*SetPlayerFacingAngle(giveplayerid, pA);
		SetCameraBehindPlayer(giveplayerid);
		//OnePlayAnim(giveplayerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 1000);//1273
		SetPlayerPosFindZ(giveplayerid, pX, pY, pZ);*/

    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы отредактировали место появления !");
		DeletePVar(playerid, "Action");
	}
	else if(operation == 4)//Отреспаунить игрока
	{
		SpawnPlayer(giveplayerid);
    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы отреспанили игрока !");
		DeletePVar(playerid, "Action");
	}
	else if(operation == 5)//Установить интерьер
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 256. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) > 256)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 256. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");
			new interior = strval(inputtext);
			SetPlayerInteriorEx(giveplayerid, interior);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's VirtualWorld: %d", PlayerName(playerid), PlayerName(giveplayerid), interior);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
		}
	}
	else if(operation == 6)//Установить мир
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 1000. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) > 999)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 1000. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new world = strval(inputtext);
			SetPlayerVirtualWorldEx(giveplayerid, world);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's VirtualWorld: %d", PlayerName(playerid), PlayerName(giveplayerid), world);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	
	else if(operation == 7)//Установить здоровье
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 100. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 1000)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 100. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new Float: health = strval(inputtext);
			SetPlayerHealthEx(giveplayerid, health);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's %.0f health", PlayerName(playerid), PlayerName(giveplayerid), health);
			//Log(ADMINLOG, msgitem);
			//ABroadCast(COLOR_RED, msgitem, 9);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 8)//Установить броню
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 150. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 1000)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 150. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new Float: armour = strval(inputtext);
			SetPlayerArmourEx(giveplayerid, armour);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's %.1f armours", PlayerName(playerid), PlayerName(giveplayerid), armour);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 9)//Установить команду
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 255. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 255)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 255. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new team = strval(inputtext);
			SetPlayerTeamEx(giveplayerid, team);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's team %d", PlayerName(playerid), PlayerName(giveplayerid), team);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 10)//Установить очки
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 100)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new score = strval(inputtext);
			SetPlayerScore(giveplayerid, score);
			
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's score %d", PlayerName(playerid), PlayerName(giveplayerid), score);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 11)//Установить опьянение
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 50000. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0)//|| strval(inputtext) > 5000
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 50000. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");
			//ApplyAnimation(playerid, "PED","WALK_DRUNK",4.1,0,1,0,0,0);
			new drunk = strval(inputtext);
			SetPlayerDrunkLevel(giveplayerid, drunk);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's DrunkLevel: %d", PlayerName(playerid), PlayerName(giveplayerid), drunk);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 12)//Установить цвет ника игрока
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			/*if(strval(inputtext) < 0)//|| strval(inputtext) > 5000
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение > 0. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}*/
			DeletePVar(playerid, "Action");
			new color = HexToInt(inputtext);//strval(inputtext);
			SetPlayerColor(giveplayerid, color);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's color: %d", PlayerName(playerid), PlayerName(giveplayerid), color);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 13)//Поменять скин
	{
   	    SetPVarInt(playerid, "TotalItems", 311); //gTotalItems = 311;
	    if(GetPVarInt(playerid, "page_active") != 1) SetPVarInt(playerid, "chang_page", 0); //если поменялась ЗАГОЛОВОК, тогда стартовать с первой страницы
	    SetPVarInt(playerid, "page_active", 1);//1 - скины или 3 - тачки
#if defined vw_changer
		//SetTimerEx("PausePlayerTextDraw", 100, 0, "i", playerid);//разовый таймер
		changer_CreateSelectionMenu(playerid);
#endif
	    DeletePVar(playerid, "Action");
	}
	else if(operation == 14)//Установить оружие
	{
		gunchange_ShowWeaponMenu(playerid);
		DeletePVar(playerid, "Action");
	}
	else if(operation == 15)//Установить скил выбранного оружия
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 999. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 999)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите скил выбранного оружия от 0 до 999. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new Gun = GetPlayerWeapon(giveplayerid);
			if(Gun == -1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У игрока отсутствует допустимое оружие!");
				SendClientMessage(playerid, COLOR_GREY, "   Установите оружие 22-34 перед тем как устанавливать ему скил!");
				return 1;
			}
			new Skill = strval(inputtext);
			SetPlayerGunSkillEx(giveplayerid, Gun, Skill);//SetPlayerSkillLevelEx
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's Gun: %d, Skill: %d", PlayerName(playerid), PlayerName(giveplayerid), Gun, Skill);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 16)//Сбросить всё оружие
	{
		ResetPlayerWeaponsEx(giveplayerid);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы сбросили всё оружие у игрока !");
		DeletePVar(playerid, "Action");
	}

	else if(operation == 17)// && operation <= 6)//Установить деньги
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			//SetPVarInt(playerid, "InputCounter", 1);
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		/*else if(GetPVarInt(playerid, "InputCounter") == 1)
		{
			SetPVarInt(playerid, "InputValue", strval(inputtext));
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите камеру заключения. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}*/
		else
		{   //если введено два параметра
			if(!strlen(inputtext))
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");
			CMD_money(playerid, giveplayerid, strval(inputtext));

			/*new money = strval(inputtext);
			GivePlayerMoney(giveplayerid, money);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s givemoney %s's - $%d!!", PlayerName(playerid), PlayerName(giveplayerid), money);
			//SendAllAdminMessage(COLOR_RED, strcmd, 6);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);*/
		}
	}
	else if(operation == 18)//Установить имя игрока
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите строку. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > MAX_PLAYER_NAME)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите имя. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new oldname[MAX_PLAYER_NAME];
			strmid(oldname, PlayerName(giveplayerid), 0, strlen(PlayerName(giveplayerid)), MAX_PLAYER_NAME);

			new newname[MAX_PLAYER_NAME];
			strmid(newname, inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);

			/*if(CheckExistPlayer(playerid, newname) == 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Это имя уже зарегистрировано !");
				return 1;
			}*/
		    switch(SetPlayerName(giveplayerid, newname))
		    {//изменяет ник в игре, сохранение данных в базу не пойдёт, т.к. в базе нету нового ника
		        case -1:
		        {
		       		format(msgitem, sizeof(msgitem), "CEPBEP: {0080FF}Не в состоянии изменить имя, кто-то уже известен как «%s».", newname);
					SendClientMessage(playerid, COLOR_RED, msgitem);
					return 1;
				}
		        case 0:
		        {
		       		format(msgitem, sizeof(msgitem), "CEPBEP: {0080FF}'%s' уже известен как '%s'", oldname, newname);
					SendClientMessage(playerid, COLOR_RED, msgitem);
					return 1;
				}
		        case 1:
		        {
		       		format(msgitem, sizeof(msgitem), "CEPBEP: {0080FF}'%s' теперь известен как '%s'", oldname, newname);
					SendClientMessage(playerid, COLOR_RED, msgitem);
				}
			}

	   		//format(strcmd, sizeof(strcmd), "CEPBEP: '%s' теперь известен как '%s'. Установил: %s", oldname, newname, PlayerName(playerid));
			//Log(ADMINLOG, msgitem);
			//SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);

		}
	}
	else if(operation == 19)//Включить часики
	{
		//if(GetPVarInt(playerid, "InputCounter") == 0)
		//{//STEP1
		if(GetPVarInt(giveplayerid, "gPlayerClock") == 0)
		{
			TogglePlayerClockEx(giveplayerid, 1);
		}
		else
		{
			TogglePlayerClockEx(giveplayerid, 0);
		}
		DeletePVar(playerid, "Action");
		//ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), msgitem, "OK", "Cancel");
		//}
	}
	else if(operation == 20)//Установить время
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			new Time[2][MAX_STRING];	new idx; new a_hour, a_minute;

//format(msgitem, sizeof(msgitem), "AdmCmd: inputtext: %s", inputtext);
//SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);

			Time[0] = strcharsplit(inputtext, idx, ':');
			if(strval(Time[0]) < 0 || strval(Time[0]) > 23)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение 0-23. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			a_hour = strval(Time[0]);

			Time[1] = strcharsplit(inputtext, idx, ':');
			if(strval(Time[1]) < 0 || strval(Time[1]) > 59)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение 0-59. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			a_minute = strval(Time[1]);
			DeletePVar(playerid, "Action");

			SetPlayerTime(giveplayerid, a_hour, a_minute);
			SetWorldTime(a_hour);//устанавливаем время согласно часового пояса

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's Time: %02d:%02d", PlayerName(playerid), PlayerName(giveplayerid), a_hour, a_minute);
	  		Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 21)//Установить погоду
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) > 20)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new weather;
			weather = strval(inputtext);
			//if(weather == 0) { ChangeWeath = -1; return 1; }
			if(weather < 1 || weather > 20) { SendClientMessage(playerid, COLOR_GREY, "    ID погоды от 1 до 20 !"); return 1; }
			SetPlayerWeatherEx(giveplayerid, weather);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's weather: %d", PlayerName(playerid), PlayerName(giveplayerid), weather);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 22)//Установить розыск
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 6. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) > 6)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 6. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new wanted = strval(inputtext);

			//SetPlayerWantedLevelEx(giveplayerid, wanted);
			//PlayCrimeReportForPlayer(playerid, giveplayerid, 2+wanted);
			//PlayCrimeReportForPlayer(giveplayerid, playerid, 2+wanted);
			
			SetPlayerWantedLevelEx(playerid, giveplayerid, wanted);
			
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's WantedLevel: %d", PlayerName(playerid), PlayerName(giveplayerid), wanted);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 23)//Установить стиль боя
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			new listitems[7*39];

			new Style = GetPlayerFightingStyle(giveplayerid);
			if(Style == FIGHT_STYLE_NORMAL) strcat(listitems, "{FFFFFF}4.\t{0080FF}Уличный стиль\n");
			else strcat(listitems, "{FFFFFF}4.\tУличный стиль\n");

			if(Style == FIGHT_STYLE_BOXING) strcat(listitems, "{FFFFFF}5.\t{0080FF}Бокс\n");
			else strcat(listitems, "{FFFFFF}5.\tБокс\n");

			if(Style == FIGHT_STYLE_KUNGFU) strcat(listitems, "{FFFFFF}6.\t{0080FF}Кунг-фу\n");
			else strcat(listitems, "{FFFFFF}6.\tКунг-фу\n");

			if(Style == FIGHT_STYLE_KNEEHEAD) strcat(listitems, "{FFFFFF}7.\t{0080FF}Колено\n");
			else strcat(listitems, "{FFFFFF}7.\tКолено\n");

			if(Style == FIGHT_STYLE_GRABKICK) strcat(listitems, "{FFFFFF}15.\t{0080FF}Захват/Бросок\n");
			else strcat(listitems, "{FFFFFF}15.\tЗахват/Бросок)\n");

			if(Style == FIGHT_STYLE_ELBOW) strcat(listitems, "{FFFFFF}16.\t{0080FF}Удар локтём");
			else strcat(listitems, "{FFFFFF}16.\tУдар локтём");

			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_LIST, "Выбирите стиль боя", listitems, "OK", "Cancel");
		}
		else
		{
			DeletePVar(playerid, "Action");

			new style;
			if(listitem == 1) style = FIGHT_STYLE_BOXING;
			else if(listitem == 2) style = FIGHT_STYLE_KUNGFU;
			else if(listitem == 3) style = FIGHT_STYLE_KNEEHEAD;
			else if(listitem == 4) style = FIGHT_STYLE_GRABKICK;
			else if(listitem == 5) style = FIGHT_STYLE_ELBOW;
			else style = FIGHT_STYLE_NORMAL;
			SetPlayerFightingStyleEx(giveplayerid, style);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's FightingStyle: %d", PlayerName(playerid), PlayerName(giveplayerid), style);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}


	else if(operation == 24)//Замарозить игрока
	{
		DeletePVar(playerid, "Action");
		CMD_freeze(playerid, giveplayerid);
	}
	
	else if(operation == 25)//Включить режим зрителя
	{
		DeletePVar(playerid, "Action");
		CMD_spectate(playerid, giveplayerid);
	}

	else if(operation == 26)//Выкинуть из тачки
	{
		DeletePVar(playerid, "Action");
		SendClientMessage(playerid, -1, "Выкинуть из тачки");
		RemovePlayerFromVehicleEx(giveplayerid);
		
	}
	else if(operation == 27)//Посадить в тачку
	{
		new carid, seatid;
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			format(msgitem, sizeof(msgitem), "Введите значение carid от 1 до %d. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", GetVehiclePoolSize());
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, msgitem, "OK", "Cancel");
		}
		else if(GetPVarInt(playerid, "InputCounter") == 1)
		{
			carid = strval(inputtext);
			SetPVarInt(playerid, "InputValue", strval(inputtext));
			new caption[70];
			strcat(caption, "carid: "); strcat(caption, inputtext);
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, caption, "Введите значение seatid. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			DeletePVar(playerid, "Action");

			carid = GetPVarInt(playerid, "InputValue");//strval(inputtext);//GetPVarInt(playerid, "InputValue");
			seatid = strval(inputtext);
    		PutPlayerInVehicleEx(giveplayerid, carid, seatid);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's PutPlayerInVehicle: %d seatid: %d", PlayerName(playerid), PlayerName(giveplayerid), carid, seatid);
			//Log(ADMINLOG, msgitem);
			//ABroadCast(COLOR_RED, msgitem, 9);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 28)//Телепорт игрока
	{
		DeletePVar(playerid, "Action");
		SendClientMessage(playerid, -1, "Телепорт игрока");

		SetPlayerVirtualWorldEx(giveplayerid, PlayerInfo[playerid][pVirtual]);
		SetPlayerInteriorEx(giveplayerid, CurInt[playerid]);
		PlayerInfo[giveplayerid][pLocal] = PlayerInfo[playerid][pLocal];
		if(CurState[giveplayerid] == PLAYER_STATE_DRIVER && PlayerInfo[playerid][pInt] == 0)
		{
			LinkVehicleToInteriorEx(nCarID[giveplayerid], PlayerInfo[playerid][pInt]);
			SetVehiclePosEx(nCarID[giveplayerid], CurPos[0][playerid], CurPos[1][playerid]+4.0, CurPos[2][playerid]);
		}
		else
		{
			SetPlayerPosEx(giveplayerid, CurPos[0][playerid], CurPos[1][playerid], CurPos[2][playerid]+1.0, 0);//plocy+2
		}
		format(msgitem, sizeof(msgitem), "AdmCmd: %s gethere %s's to itself", PlayerName(playerid),PlayerName(giveplayerid));
		Log(ADMINLOG, msgitem);
		SendClientMessage(giveplayerid, COLOR_GREY, "   Вас телепортировал админ!");
	}
	else if(operation == 29)//Телепорт к игроку
	{
		DeletePVar(playerid, "Action");
		SendClientMessage(playerid, -1, "Телепорт к игроку");
		
		SetPlayerVirtualWorldEx(playerid, PlayerInfo[giveplayerid][pVirtual]);
		SetPlayerInteriorEx(playerid, CurInt[giveplayerid]);
		PlayerInfo[playerid][pLocal] = PlayerInfo[giveplayerid][pLocal];
		if(PlayerInfo[giveplayerid][pInt] > 0)
		{
			SetPlayerPosEx(playerid, CurPos[0][giveplayerid], CurPos[1][giveplayerid], CurPos[2][giveplayerid]+1.0, 0);//plocy+1
		}
		else
		{
			if(CurState[playerid] == PLAYER_STATE_DRIVER && PlayerInfo[giveplayerid][pInt] == 0)
			{
				LinkVehicleToInteriorEx(nCarID[playerid], PlayerInfo[giveplayerid][pInt]);
				SetVehiclePosEx(nCarID[playerid], CurPos[0][giveplayerid], CurPos[1][giveplayerid]+4.0, CurPos[2][giveplayerid]);
			}
			else
			{
				SetPlayerPosEx(playerid, CurPos[0][giveplayerid], CurPos[1][giveplayerid]+1.0, CurPos[2][giveplayerid]+2.5, 0);//plocy+1
			}
		}
		format(msgitem, sizeof(msgitem), "AdmCmd: %s goto teleported to %s's", PlayerName(playerid),PlayerName(giveplayerid));
		Log(ADMINLOG, msgitem);
		SendClientMessage(giveplayerid, COLOR_GREY, "   Вы телепортировались к игроку!");
	}
	else if(operation == 30)//Телепорт на метку
	{
		DeletePVar(playerid, "Action");
		SendClientMessage(playerid, -1, "Телепорт на метку");
		
		SetPlayerVirtualWorldEx(giveplayerid, 0);
		SetPlayerInteriorEx(giveplayerid, 0);
		PlayerInfo[giveplayerid][pLocal] = FREEROAM;
		if(PlayerInfo[giveplayerid][pInt] > 0)
		{
			SetPlayerPosEx(giveplayerid, Mark[0][playerid], Mark[1][playerid], Mark[2][playerid]+1.0, 0);//plocy+1
		}
		else
		{
			if(CurState[playerid] == PLAYER_STATE_DRIVER && PlayerInfo[giveplayerid][pInt] == 0)
			{
				LinkVehicleToInteriorEx(nCarID[giveplayerid], 0);
				SetVehiclePosEx(nCarID[giveplayerid], Mark[0][playerid], Mark[1][playerid]+4.0, Mark[2][playerid]);
			}
			else
			{
				SetPlayerPosEx(giveplayerid, Mark[0][playerid], Mark[1][playerid]+1.0, Mark[2][playerid]+2.5, 0);//plocy+1
			}
		}
		format(msgitem, sizeof(msgitem), "AdmCmd: %s goto teleported to mark: ", PlayerName(giveplayerid));
		//Log(ADMINLOG, msgitem);
		SendClientMessage(giveplayerid, COLOR_GREY, "   Вы телепортировали игрока на метку!");
	}
	else if(operation == 31)//Телепорт к дому
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#MAX_HOUSE". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) >= MAX_HOUSE)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#MAX_HOUSE". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new house = strval(inputtext);
			CMD_house(giveplayerid, house);
			
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's house: %d", PlayerName(playerid), PlayerName(giveplayerid), house);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 32)//Телепорт к бизу
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#MAX_BIZ". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) >= MAX_BIZ)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#MAX_BIZ". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(giveplayerid, "Action");

			new bouse = strval(inputtext);
			CMD_biz(playerid, bouse);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's biz: %d", PlayerName(playerid), PlayerName(giveplayerid), bouse);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 33)//Телепорт к компании
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#MAX_SBIZ". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strval(inputtext) < 0 || strval(inputtext) >= MAX_SBIZ)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#MAX_SBIZ". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(giveplayerid, "Action");

			new sbouse = strval(inputtext);
			CMD_sbiz(playerid, sbouse);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's sbiz: %d", PlayerName(playerid), PlayerName(giveplayerid), sbouse);
	  		//Log(ADMINLOG, msgitem);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 34)//включить проверку public
	{
		DeletePVar(playerid, "Action");
#if defined vw_checking
		checking_FunctionCheckList(giveplayerid);
#endif
		SendClientMessage(playerid, -1, "Если диалог проверок не отображается, значит выключен vw_checking в моде");
	}
	else if(operation == 35)//Расстояние до точки
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение X,Y,Z. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(strlen(inputtext) < 0 || strlen(inputtext) >= 128)
			{
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение X,Y,Z. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(giveplayerid, "Action");
			
			new idx;
			Array[0] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[0]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z");
				return 1;
			}
			pX = floatstr(Array[0]);

			Array[1] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[1]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z");
				return 1;
			}
			pY = floatstr(Array[1]);

			Array[2] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[2]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z");
				return 1;
			}
			pZ = floatstr(Array[2]);

			format(msgitem, sizeof(msgitem), "Distance(playerid: %d, point: (%.1f,%.1f,%.1f) = %.1f", playerid, pX, pY, pZ, GetPlayerDistanceFromPoint(playerid, pX, pY, pZ));
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
		}
	}
	/*else if(operation == 25)//Следить за игроком
	{
		DeletePVar(playerid, "Action");
	}
	else if(operation == 26)//Заглушить игрока
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{//STEP1
			if(PlayerInfo[giveplayerid][pMuted] <= getdate())
			{
				format(msgitem, sizeof(msgitem), "Введите кол-во дней [1-%d] наказания!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
					365-getdate(), PlayerName(giveplayerid), giveplayerid);
			}
			else
			{
				format(msgitem, sizeof(msgitem), "%s был заглушен до %s.\
\nВведите 0 дней, \nчтобы снять наказание!!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
					PlayerName(giveplayerid), getDate(PlayerInfo[giveplayerid][pMuted]), 365-getdate());
			}
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), msgitem, "OK", "Cancel");
		}
		else
		{//STEP2
			if(!strlen(inputtext))
			{//STEP3 --> STEP2
				format(msgitem, sizeof(msgitem), "Введите кол-во дней [1-%d] наказания!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
					365-getdate(), PlayerName(giveplayerid), giveplayerid);
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), msgitem, "OK", "Cancel");
				return 1;
			}
			//STEP4
			//new day = strval(inputtext);
			CMD_mute(playerid, giveplayerid, inputtext);
			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 29)//Забанить игрока
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите причину. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext))
			{
				format(msgitem, sizeof(msgitem), "Введите кол-во дней [1-%d] наказания!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
					365-getdate(), PlayerName(giveplayerid), giveplayerid);
				ShowPlayerDialogEx(playerid, DEVELOPER_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), msgitem, "OK", "Cancel");
				return 1;
			}
			CMD_kick(playerid, giveplayerid, inputtext);
			DeletePVar(playerid, "Action");
		}
	}*/
	//==========================================================================
	else DeletePVar(playerid, "Action");
	GivePVarInt(playerid, "InputCounter", +1);//счётчик кол-ва входов в данную обработку
	//format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, Action:%d, InputCounter:%d)", playerid, giveplayerid, GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter") );
	//SendClientMessage(playerid, COLOR_GREEN, strings);
	return 1;
}


//переделать на TextDraw для вывода всех изменяемых параметров
//Информация об игроке
stock InfoOfPlayer(playerid, targetid)//вызывается по команде /stats
{   //playerid - тот кто запросил инфо, targetid - кем интересуются
	new msgitem[1476];//49+55+20+20+47+6+59+58*11+32+16+28+3+51
	new name[MAX_PLAYER_NAME]; GetPlayerName(targetid, name, sizeof(name));
	new name_info[2][20]; split(name, name_info, '_');
	new pip[16]; GetPlayerIp(targetid, pip, sizeof(pip));
	strcat(msgitem, "{AFAFAF}________________________________________");
	format(msgitem, sizeof(msgitem), "%s\n{0080FF}Имя: {FFFFFF}%s\t{0080FF}Фамилия: {FFFFFF}%s", msgitem, name_info[0], name_info[1]);
	format(msgitem, sizeof(msgitem), "%s\n{0080FF}Расстояние до игрока:\t{FFFFFF}%.1f", msgitem, GetDistanceBetweenPlayers(playerid, targetid));
	if(IsPlayerStreamedIn(playerid,targetid)) strcat(msgitem, "\n{0080FF}Игрок находится в зоне вашей видимости на радаре");//59
	strcat(msgitem, SendPlayerStateMessage(targetid));
	format(msgitem, sizeof(msgitem), "%s\n{0080FF}PlayerIp: \t\t{FFFFFF}%s", msgitem, pip);
	format(msgitem, sizeof(msgitem), "%s\n{0080FF}Ping: \t\t\t{FFFFFF}%d", msgitem, GetPlayerPing(targetid));
	strcat(msgitem, "\n{AFAFAF}________________________________________");//51
	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "{80FFFF}Info Of Player", msgitem, "OK", "");
   	return 1;
}


stock admin_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{//не работает в интерьерах и в тачке
	/*if(GetPVarInt(playerid, "Action") == 1)
	{//если операция ещё не выбрана, т.е. это ввод первого параметра
	    //не забыть обнулить при окончанию ввода параметров
		//SetPVarInt(playerid, "Action", listitem+1);//записали выбранную операцию
		//DeletePVar(playerid, "InputCounter");//очистили от предыдущих операций
		return 1;
	}*/

	//if(CHECKING == 1)
	//{//ИНФОРМИРОВАНИЕ
	format(strings, sizeof(strings), "OnPlayerClickMap(%d, %.4f, %.4f, %.4f)", playerid, fX, fY, fZ);
	SendClientMessage(playerid, COLOR_GREEN, strings);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
	//}
	Mark[0][playerid] = fX;
	Mark[1][playerid] = fY;
	Mark[2][playerid] = fZ;


	/*if(PlayerInfo[playerid][pInt] != 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться НЕ в интерьере !");
		return 1;
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться ВНЕ транспортного средства !");
		return 1;
	}*/

    //PlayerInfo[playerid][pLocal] = FREEROAM;
    //SetPlayerInteriorEx(playerid, 0);
    //SetPlayerVirtualWorldEx(playerid, 0);

	//CurPos[0][playerid] = fX;
	//CurPos[1][playerid] = fY;
	//CurPos[2][playerid] = fZ;
	//checkcheat[playerid] = CHEATLIM;

	//SetPlayerFacingAngle(playerid, ang);
	//SetCameraBehindPlayer(playerid);
	//OnePlayAnim(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 1000);//1273

	//new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
    //	SetPlayerPos(giveplayerid, fX, fY, fZ+10.0);
	//SetPlayerPosFindZ(giveplayerid, fX, fY, fZ+10.0);
	return 1;
}

stock gotomark(playerid, giveplayerid, Float:fX, Float:fY, Float:fZ)
{
	new curstate = GetPlayerState(playerid);
	if(curstate == PLAYER_STATE_DRIVER)//GetPlayerInterior(j) == 0
	{
		new vehicle = GetPlayerVehicleID(giveplayerid);
		SetVehicleVirtualWorld(vehicle, GetPlayerVirtualWorld(playerid));
		//SetPlayerVirtualWorld(playerid, TeleportDest[playerid][Virt]);
		LinkVehicleToInterior(vehicle, GetPlayerInterior(playerid));
		//SetPlayerInterior(playerid, TeleportDest[playerid][Int]);
		//PlayerInfo[playerid][pLocal] = TeleportDest[playerid][Loc];//gotoin
		SetVehiclePos(vehicle, fX, fY, fZ);
	}
	else if(curstate == PLAYER_STATE_ONFOOT)
	{
		SetPlayerVirtualWorld(giveplayerid, GetPlayerVirtualWorld(playerid));
		SetPlayerInterior(giveplayerid, GetPlayerInterior(playerid));
		//PlayerInfo[playerid][pLocal] = TeleportDest[playerid][Loc];//gotoin
		SetPlayerPosFindZ(giveplayerid, fX, fY, fZ);
	}
}

stock CMD_money(playerid, giveplayerid, money)
{
    //new money = GetPVarInt(giveplayerid, "InputValue");
#if defined FILTERSCRIPT
	GivePlayerMoney(giveplayerid, money);
#else
	GivePlayerMoneyH(fadmin, giveplayerid, money);
#endif
	format(strings, sizeof(strings), "AdmCmd: %s givemoney %s's - $%d!!", PlayerName(playerid), PlayerName(giveplayerid), money);
	//SendAllAdminMessage(COLOR_RED, strcmd, 6);
	SendClientMessage(playerid, COLOR_RED, strings);
	SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);
	//DeletePVar(playerid, "InputValue");
	//DeletePVar(playerid, "Action");
	//DeletePVar(playerid, "InputCounter");
	//DeletePVar(playerid, "Action");
}

stock CMD_house(playerid, house)
{
	//new house = strval(tmp);
	SetPlayerVirtualWorldEx(playerid, house+1);//PlayerInfo[playerid][pLocal]
	SetPlayerInteriorEx(playerid, HouseInfo[house][hInt]);
	SetPlayerPosEx(playerid, HouseInfo[house][hExitX],HouseInfo[house][hExitY],HouseInfo[house][hExitZ], HouseInfo[house][hExitA]);
	//GameTextForPlayerEx(playerid, "~w~Teleporting", 5000, 1);
	PlayerInfo[playerid][pLocal] = house;
}
stock CMD_biz(playerid, bouse)
{
	DisablePlayerCheckpointEx(playerid);
	//SetPlayerVirtualWorldEx(playerid, bouse);//PlayerInfo[playerid][pLocal]
	//SetPlayerInteriorEx(playerid, BizInfo[bouse][bInt]);
	//SetPlayerPosEx(playerid, BizInfo[bouse][bExitX],BizInfo[bouse][bExitY],BizInfo[bouse][bExitZ], BizInfo[bouse][bExitA]);
	SetPlayerPosEx(playerid, BizInfo[bouse][bEntranceX],BizInfo[bouse][bEntranceY],BizInfo[bouse][bEntranceZ], 0);
	//PlayerInfo[playerid][pLocal] = bouse+100;//0+100=100 0-5 / 0-44
	GameTextForPlayerEx(playerid, "~w~Teleporting", 5000, 1);
}
stock CMD_sbiz(playerid, sbouse)
{
	DisablePlayerCheckpointEx(playerid);
	PlayerInfo[playerid][pLocal] = FREEROAM;
	SetPlayerVirtualWorldEx(playerid, 0);//PlayerInfo[playerid][pLocal]
	SetPlayerInteriorEx(playerid, 0);
	SetPlayerPosEx(playerid, SBizInfo[sbouse][sbEntranceX],SBizInfo[sbouse][sbEntranceY],SBizInfo[sbouse][sbEntranceZ], 0);
	GameTextForPlayerEx(playerid, "~w~Teleporting", 5000, 1);
}




/*
forward PausePlayerTextDraw(playerid);
public PausePlayerTextDraw(playerid)
{
#if defined vw_changer
	changer_CreateSelectionMenu(playerid);
#endif
}*/
