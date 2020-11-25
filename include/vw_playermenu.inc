

//##############################################################################//
//                                                                              //
//                                  МЕНЮ ИГРОКА                                 //
//                                                                              //
//##############################################################################//
stock PlayerMenu(playerid)
{
	new bigmsgitem[] = "{FFFFFF}1\t{00FF00}Статистика\
\n{FFFFFF}2\t{00FF00}Инвентарь\
\n{FFFFFF}3\t{00FF00}Навыки\
\n{FFFFFF}4\t{00FF00}Улучшения\
\n{FFFFFF}5\t{00FF00}Недвижимость\
\n{FFFFFF}6\t{00FF00}Настройки\
\n{FFFFFF}7\t{00FF00}Смена пароля";
/*
Поздороваться\
\nПоздороваться со всеми\
\nПоказать паспорт\
\nПослать SMS\
\nПозвонить по телефону\
\nПередать деньги\
\nПередать оружие\
\nВыразить уважение\
\nВыразить презрение\
\nПопрощаться";
*/
//\n{FFFFFF}7\t{00FF00}Связь с администрацией";
//\n{FFFFFF}7\t{00FF00}Команды";
//\n{FFFFFF}9\t{00FF00}Изменить имя";
	new caption[70];
	format(caption, sizeof(caption), "Меню игрока: %s[%d]", PlayerName(playerid), playerid);
	ShowPlayerDialogGap(playerid, PLMENU_DIALOG, DIALOG_STYLE_LIST, caption, bigmsgitem, "OK", "Назад");
}
stock backPMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])//перехватываем событие кнопки НАЗАД
{//возвращает в меню игрока при нажатии кнопки НАЗАД если у того диалога ID: BACKPLMENU_DIALOG
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BACKPLMENU_DIALOG) return 1;
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	PlaySoundForPlayer(playerid, 5202);
	return 1;
}

stock playermenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	backPMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	tog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	upgrade_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	if(dialogid != PLMENU_DIALOG) return 1;
	if(!response) {
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		admin_OnPlayerClick(playerid, giveplayerid);//PlayerMenu(playerid);
		return 1;
	} //PlaySoundForPlayer(playerid, 5202);
	new strcmd[MAX_STRING];
	if(listitem == 0)//Паспорт
	{//Статистика
    	SetPVarInt(playerid, "gDocuments", 1);
		OnPlayerShowStats(playerid, playerid);
	}
	else if(listitem == 1)
	{//Инвентарь
		Items(playerid);
	}
	else if(listitem == 2)
	{//Навыки
		SkillInfo(playerid);
	}
	else if(listitem == 3)
	{ //Улучшения
		PlayerUpgrade(playerid);
	}
	else if(listitem == 4)
	{//Недвижимость
		PropertyHelp(playerid);
	}
	else if(listitem == 5)
	{ //Личные настройки
		TogHelp(playerid);
	}
	else if(listitem == 6)
	{ //Настройки безопасности
		if(GetPVarInt(playerid, "PasswordHasEdited") == getdate() && PlayerInfo[playerid][pAdmin] < 5)
		{
			format(strcmd, sizeof(strcmd), "CEPBEP: {33AA33}playerid:%d уже сегодня производил отправку пароля. Нельзя так часто менять пароль!", playerid);
			SendClientMessage(playerid, COLOR_RED, strcmd);
			return 1;
		}
		login_ChangePass(playerid);
	}
	return 1;
}
stock TogHelp(playerid)
{
	new listitems[545+8*13+22];

	strcat(listitems, "Очистить личный чат\n");

	if (!gPhoneOnline[playerid]) strcat(listitems, "/togphone - {FF0000}откл телефон\n");
	else strcat(listitems, "/togphone - {00FF00}вкл телефон\n");

	if (!GetPVarInt(playerid, "gNews")) strcat(listitems, "/tognews - {FF0000}откл чат новостей\n");
	else strcat(listitems, "/tognews - {00FF00}вкл чат новостей\n");

	if (!GetPVarInt(playerid, "gJob")) strcat(listitems, "/togjob{FF0000} - откл служебные сообщения\n");
	else strcat(listitems, "/togjob{00FF00} - вкл служебные сообщения\n");

	if(!GetPVarInt(playerid, "gSport")) strcat(listitems, "/togsport - {FF0000}откл спортивные новости\n");
	else strcat(listitems, "/togsport - {00FF00}вкл спортивные новости\n");

	if (!GetPVarInt(playerid, "gFam")) strcat(listitems, "/togfam - {FF0000}откл семейный канал\n");
	else strcat(listitems, "/togfam - {00FF00}вкл семейный канал\n");

	if (!GetPVarInt(playerid, "gHidePM")) strcat(listitems, "/togpm - {FF0000}откл личные сообщения\n");
	else strcat(listitems, "/togpm - {00FF00}вкл личные сообщения\n");

	if(!GetPVarInt(playerid, "gOoc")) strcat(listitems, "/togooc - {FF0000}откл общий чат\n");
	else strcat(listitems, "/togooc - {00FF00}вкл общий чат\n");

	if(!GetPVarInt(playerid, "gSwitcher")) strcat(listitems, "/togSwitcher - {FF0000}откл упрощенный режим сообщений\n");
	else strcat(listitems, "/togSwitcher - {00FF00}вкл упрощенный режим сообщений\n");

	if(TextDrawShowClock[playerid] == true) strcat(listitems, "/togtime - {FF0000}откл информацию о дате и времени\n");
	else strcat(listitems, "/togtime - {00FF00}вкл информацию о дате и времени\n");

	if(TextDrawShowArmour[playerid] == true) strcat(listitems, "/toghp - {FF0000}откл информацию о здоровье и брони\n");
	else strcat(listitems, "/toghp - {00FF00}вкл информацию о здоровье и брони\n");

	if(TextDrawShowMessage[playerid] == true) strcat(listitems, "/togsys - {FF0000}откл системную панель\n");
	else strcat(listitems, "/togsys - {00FF00}вкл системную панель\n");

	if(!GetPVarInt(playerid, "gAdmin")) strcat(listitems, "/togadmin - {FF0000}откл админ сообщения\n");
	else strcat(listitems, "/togadmin - {00FF00}вкл админ сообщения.\n");

	strcat(listitems, "/audiomsg - {FF0000}откл/{00FF00}вкл{FFFFFF} сообщения о аудиопотоке\n");

	strcat(listitems, "/dl - {FF0000}откл/{00FF00}вкл{FFFFFF} информацию по транспорту");

	ShowPlayerDialogEx(playerid, TOG_DIALOG, DIALOG_STYLE_LIST, "Личные настройки - список переключателей", listitems, "OK", "Назад");
}
stock tog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != TOG_DIALOG) return 1;
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	if(listitem == 0)
	{
		for(new c = 0; c != 32; c++) SendClientMessage(playerid, -1, " ");
	}
	if(listitem == 1)
	{   //togphone
        /*if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pAccount] == 0)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }*/
		if(gPhoneOnline[playerid] == 0)
		{
			gPhoneOnline[playerid] = 1;
			SendClientMessage(playerid, COLOR_GREY, "   Ваш Телефон Выключен !");
		}
		else
		{
			gPhoneOnline[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   Ваш Телефон Включен !");
		}
	}
	else if(listitem == 2)
	{   //tognews
		if(GetPVarInt(playerid, "gNews") == 0)
		{
			SetPVarInt(playerid, "gNews", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Канал Новостей отключен !");
		}
		else
		{
			SetPVarInt(playerid, "gNews", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Канал Новостей включен !");
		}
	}
	else if(listitem == 3)
	{   //togjob
		if(GetPVarInt(playerid, "gJob") == 0)
		{
			SetPVarInt(playerid, "gJob", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Рабочие Сообщения отключены !");
		}
		else
		{
			SetPVarInt(playerid, "gJob", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Рабочие Сообщения включены !");
		}
	}
	else if(listitem == 4)
	{   //togsport
		if(GetPVarInt(playerid, "gSport") == 0)
		{
			SetPVarInt(playerid, "gSport", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Cпортивные новости отключены !");
		}
		else
		{
			SetPVarInt(playerid, "gSport", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Cпортивные новости включены !");
		}
	}
	else if(listitem == 5)
	{   //togfam
		if(GetPVarInt(playerid, "gFam") == 0)
		{
			SetPVarInt(playerid, "gFam", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Семейный чат отключен !");
		}
		else
		{
			SetPVarInt(playerid, "gFam", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Семейный чат включен !");
		}
	}
	else if(listitem == 6)
	{   //togpm
		if(GetPVarInt(playerid, "gHidePM") == 0)
		{
			SetPVarInt(playerid, "gHidePM", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Whisper chat channel Disabled !");
		}
		else
		{
			SetPVarInt(playerid, "gHidePM", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Whisper chat channel Enabled !");
		}
	}
	else if(listitem == 7)
	{   //togooc
		if(GetPVarInt(playerid, "gOoc") == 0)
		{
			SetPVarInt(playerid, "gOoc", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Общий чат отключен !");
		}
		else
		{
			SetPVarInt(playerid, "gOoc", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Общий чат включен !");
		}
	}
	else if(listitem == 8)
	{   //togswitcher
		if(GetPVarInt(playerid, "gSwitcher") == 0)
		{
			SetPVarInt(playerid, "gSwitcher", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Упрощенный режим Сообщений отключен !");
		}
		else
		{
			SetPVarInt(playerid, "gSwitcher", 0);
			SendClientMessage(playerid, COLOR_GREY, "    Упрощенный режим Сообщений включен !");
		}
	}
	else if(listitem == 9)
	{   ///togtime
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
			SendClientMessage(playerid, COLOR_GREY, "   Информация даты и времени убрана !");
		}
		else
		{
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
			SendClientMessage(playerid, COLOR_GREY, "   Информация даты и времени добавлена !");
		}
	}
	else if(listitem == 10)
	{   //toghp
		if(TextDrawShowArmour[playerid] == true)
		{
			PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);
			PlayerTextDrawHide(playerid, txdPlayerArmour[playerid]);
			TextDrawShowArmour[playerid] = false;
			SendClientMessage(playerid, COLOR_GREY, "   Информация о брони убрана !");
		}
		else
		{
			PlayerTextDrawShow(playerid, txdPlayerHealth[playerid]);
			PlayerTextDrawShow(playerid, txdPlayerArmour[playerid]);
			TextDrawShowArmour[playerid] = true;
			SendClientMessage(playerid, COLOR_GREY, "   Информация о брони добавлена !");
		}
	}
	else if(listitem == 11)
	{   //togsys
        /*if(PlayerInfo[playerid][pAdmin] < 1)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }*/
		if(TextDrawShowMessage[playerid] == false)
		{
			TextDrawShowForPlayer(playerid, txdSystemMessage);
			TextDrawShowMessage[playerid] = true;
			SendClientMessage(playerid, COLOR_GREY, "   Системная панель включена !");
		}
		else
		{
			TextDrawHideForPlayer(playerid, txdSystemMessage);
			TextDrawShowMessage[playerid] = false;
			SendClientMessage(playerid, COLOR_GREY, "   Системная панель убрана !");
		}
	}
	else if(listitem == 12)
	{   ///togadmin
		if(GetPVarInt(playerid, "gAdmin") == 0)
		{
			SetPVarInt(playerid, "gAdmin", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Админ сообщения убраны !");
		}
		else
		{
			SetPVarInt(playerid, "gAdmin", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Админ сообщения добавлены !");
		}
	}
	TogHelp(playerid);
	return 1;
}




stock PlayerUpgrade(playerid)
{
	new DialogIDCounter = 0;
	new listitems[65*12];//65 + 73+55+76+59+67 + 51 + 16 = 462
	for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;

	if(PlayerInfo[playerid][pPupgrade] >= 1)
	{
		if(PlayerInfo[playerid][pLevel] >= 2 &&
			PlayerInfo[playerid][pSHealth] < 50)
		{
			strins(listitems, "Health - игроку даётся на 5% больше здоровья при возраждении.\n", strlen(listitems));
			DialogID[playerid][0] = DialogIDCounter;
			DialogIDCounter ++;
		}
	}

	if(PlayerInfo[playerid][pPupgrade] >= 2)
	{

		if(	PlayerInfo[playerid][pLevel] >= 4 &&
			PlayerInfo[playerid][pHunger] < 9)
		{//увеличивается шкала Голод.
			strins(listitems, "Hunger - Игрок не так быстро испытывает потребность в еде.\n", strlen(listitems));
			DialogID[playerid][1] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 6 &&
			PlayerInfo[playerid][pLeisure] < 9)
		{
			strins(listitems, "Leisure - медленнее растёт потребность Развлечения.\n", strlen(listitems));
			DialogID[playerid][2] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 8 &&
			PlayerInfo[playerid][pContact] < 9)
		{
			strins(listitems, "Contact - Игрок не так быстро испытывает потребность в общении.\n", strlen(listitems));
			DialogID[playerid][3] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 10 &&
			PlayerInfo[playerid][pToilet] < 9)
		{
			strins(listitems, "Toilet - медленнее растёт потребность Туалет.\n", strlen(listitems));
			DialogID[playerid][4] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 12 &&
			PlayerInfo[playerid][pVigour] < 9)
		{
			strins(listitems, "Vigour - Игрок не так быстро испытывает потребность в сне.\n", strlen(listitems));
			DialogID[playerid][5] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 14 &&
			PlayerInfo[playerid][pAlcoholPerk] < 9)
		{
			strins(listitems, "Alcoholic - больше hp за меньшее кол-во денег + меньше пьянеешь.\n", strlen(listitems));
			DialogID[playerid][6] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 16 &&
			PlayerInfo[playerid][pDrugPerk] < 9)
		{
			strins(listitems, "DrugAddict - больше здоровья + иммунитет к болезням.\n", strlen(listitems));
			DialogID[playerid][7] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 18 && //PlayerInfo[playerid][pJob] == ARMSDEALER &&
			PlayerInfo[playerid][pMiserPerk] < 9)
		{
			strins(listitems, "Miser - оружейник тратит на Вас меньше материалов.\n", strlen(listitems));
			DialogID[playerid][8] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 20 &&
			PlayerInfo[playerid][pTraderPerk] < 9)
		{
			strins(listitems, "Trade - дешевле покупки в 24/7, закусочных и аммунициях.\n", strlen(listitems));
			DialogID[playerid][9] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 22 && //PlayerInfo[playerid][pMember] == DoH &&
			PlayerInfo[playerid][pPainPerk] < 9)
		{
			strins(listitems, "PainKillers - медик восст-ет Вам на 20'/. здоровья больше.\n", strlen(listitems));
			DialogID[playerid][10] = DialogIDCounter;
			DialogIDCounter ++;
		}

	}
	if(PlayerInfo[playerid][pLevel] >= 2 &&
		GetPlayerMoneyH(playerid) >= 10000)
	{
		strins(listitems, "Reset Upgrades - сбросить все улучшения ($10000)\n", strlen(listitems));
		DialogID[playerid][11] = DialogIDCounter;
		DialogIDCounter ++;
		//ИНФОРМИРОВАНИЕ
		//format(strings, sizeof(strings), "DialogID[playerid][27]: %d", DialogID[playerid][27]);
		//ABroadCast(COLOR_MAROON, strings, 9);
	}

	if(DialogIDCounter <= 0)
	{
		PlayerMenu(playerid);
		SendClientMessage(playerid, COLOR_GREY, "   Нет доступных улучшений !");
		return 1;
	}

	new caption[70];
	format(caption, sizeof(caption), "*** UPGRADES *** Доступно %d очков улучшений", PlayerInfo[playerid][pPupgrade]);
	if(strlen(listitems) > sizeof(listitems))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: *** UPGRADES *** %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(listitems), sizeof(listitems));
		Log(ERROR, strings);
		return 1;
	}

	if(strlen(listitems) <= 0)
	{
		GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   UPGRADES пуст");//COLOR_BLUEGREY
		return 1;
	}

	ShowPlayerDialogEx(playerid, UPGRADE_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "OK", "Назад");
	return 1;
}
stock upgrade_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != UPGRADE_DIALOG) return 1;
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	new msgitem[70];
	if(listitem == DialogID[playerid][0])
	{   //strcmp(upgradename, "health", true, strlen(upgradename)) == 0
		PlayerInfo[playerid][pSHealth] += 5.0;
		format(msgitem, sizeof(msgitem), "New Upgrade: +5 Здоровье при Возрождении = %.0f", PlayerInfo[playerid][pSHealth]+50.0);
		PlayerInfo[playerid][pPupgrade] -= 1;
		GameTextForPlayerEx(playerid, "~r~-1 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][1])
	{
		PlayerInfo[playerid][pHunger] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш АнтиГолод теперь %d-го уровня.", PlayerInfo[playerid][pHunger]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][2])
	{
		PlayerInfo[playerid][pLeisure] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш АнтиДосуг теперь %d-го уровня.", PlayerInfo[playerid][pLeisure]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][3])
	{
		PlayerInfo[playerid][pContact] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваше АнтиОбщение теперь %d-го уровня.", PlayerInfo[playerid][pContact]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][4])
	{
		PlayerInfo[playerid][pToilet] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш АнтиТуалет теперь %d-го уровня.", PlayerInfo[playerid][pToilet]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][5])
	{
		PlayerInfo[playerid][pVigour] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш АнтиБодрость теперь %d-го уровня.", PlayerInfo[playerid][pVigour]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][6])// && DialogID[playerid][22] != 0
	{   // && (strcmp(upgradename, "alcoholic", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pAlcoholPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваша Алкогольная Независимость теперь %d-го уровня.", PlayerInfo[playerid][pAlcoholPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][7])// && DialogID[playerid][23] != 0
	{   // && (strcmp(upgradename, "drugaddict", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pDrugPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваша Нарко НЕзависимость %d-го уровня.", PlayerInfo[playerid][pDrugPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][8])// && DialogID[playerid][24] != 0
	{   // && (strcmp(upgradename, "miser", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pMiserPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш Навык Скупости %d-го уровня.", PlayerInfo[playerid][pMiserPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][9])// && DialogID[playerid][25] != 0
	{   // && (strcmp(upgradename, "trader", true, strlen(upgradename)) == 0
		PlayerInfo[playerid][pTraderPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш Навык Покупателя %d-го уровня.", PlayerInfo[playerid][pTraderPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][10])// && DialogID[playerid][26] != 0
	{   // && (strcmp(upgradename, "painkillers", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pPainPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: Ваш навык Лекаря теперь %d-го уровня.", PlayerInfo[playerid][pPainPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][11])// && DialogID[playerid][27] != 0
	{
		PlayerInfo[playerid][pPupgrade] = (PlayerInfo[playerid][pLevel]-1)*2;
		PlayerInfo[playerid][pSHealth] = 0.0;

		PlayerInfo[playerid][pAlcoholPerk] = 0;
		PlayerInfo[playerid][pDrugPerk] = 0;
		PlayerInfo[playerid][pMiserPerk] = 0;
		PlayerInfo[playerid][pPainPerk] = 0;
		PlayerInfo[playerid][pTraderPerk] = 0;

		PlayerInfo[playerid][pHunger] = 0;
		PlayerInfo[playerid][pLeisure] = 0;
		PlayerInfo[playerid][pContact] = 0;
		PlayerInfo[playerid][pToilet] = 0;
		PlayerInfo[playerid][pVigour] = 0;

		GivePlayerMoneyH(ftax, playerid, -10000);//10000 для экономики
		if(BizInfo[0][bTill]+10000 < 2147480000) { BizInfo[0][bTill] += 10000; BizInfo[0][bExport] += 10000; }
		//new family = PlayerInfo[Offer[playerid]][pMember];
		//FamilyInfo[0+7][fBank] += recovery;
		format(msgitem, sizeof(msgitem), "Reset Upgrades. Bы имеете %d очка(ов) улучшения !", PlayerInfo[playerid][pPupgrade]);
	}
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
	PlayerUpgrade(playerid);
	return 1;
}


//То что будет отображаться при вводе команды /stats поддерживает русский шрифт
stock OnPlayerShowStats(playerid, targetid)//вызывается по команде /stats
{   //playerid - тот кто запросил инфо, targetid - кем интересуются
	new atext[20];
	if(PlayerInfo[targetid][pSex] == Male) { atext = "Male"; }
	else if(PlayerInfo[targetid][pSex] == Female) { atext = "Female"; }
	else atext = "Unknown";

	new otext[20];//для стран
	if(PlayerInfo[targetid][pOrigin] == 0) { otext = "Minsk"; }
	else if(PlayerInfo[targetid][pOrigin] == 1) { otext = "Grodno"; }
	else if(PlayerInfo[targetid][pOrigin] == 2) { otext = "Gomel"; }
	else if(PlayerInfo[targetid][pOrigin] == 3) { otext = "Mogilev"; }
	else if(PlayerInfo[targetid][pOrigin] == 4) { otext = "Vitebsk"; }
	else if(PlayerInfo[targetid][pOrigin] == 5) { otext = "Brest"; }
	else if(PlayerInfo[targetid][pOrigin] == 6) { otext = "Russia"; }
	else if(PlayerInfo[targetid][pOrigin] == 7) { otext = "Ukraine"; }
	else if(PlayerInfo[targetid][pOrigin] == 8) { otext = "Lithuania"; }
	else if(PlayerInfo[targetid][pOrigin] == 9) { otext = "Latvia"; }
	else if(PlayerInfo[targetid][pOrigin] == 10) { otext = "Estonia"; }
	else if(PlayerInfo[targetid][pOrigin] == 11) { otext = "Moldova"; }
	else if(PlayerInfo[targetid][pOrigin] == 12) { otext = "Bulgaria"; }
	else if(PlayerInfo[targetid][pOrigin] == 13) { otext = "Kazakhstan"; }
	else if(PlayerInfo[targetid][pOrigin] == 14) { otext = "Bashkortostan"; }
	else if(PlayerInfo[targetid][pOrigin] == 15) { otext = "Israil"; }
	else if(PlayerInfo[targetid][pOrigin] == 16) { otext = "Italy"; }
	else if(PlayerInfo[targetid][pOrigin] == 17) { otext = "Germany"; }
	else { otext = "Unknown"; }

	new actext[20];
	if(PlayerInfo[targetid][pAccount] != 0) { actext = "Premium"; }
	else { actext = "None"; }

	//----------------------------------------------------------------------
	new age = GetAgePlayer(PlayerInfo[targetid][pAge])+18+PlayerInfo[targetid][pConnectTime]/12;

	new housekey = PlayerInfo[targetid][pHouse];
	new carid1 = MyCar[targetid][0];
	new carid2 = MyCar[targetid][1];
	new carid3 = MyCar[targetid][2];

	new married[24];
	strmid(married, PlayerInfo[targetid][pMarriedTo], 0, strlen(PlayerInfo[targetid][pMarriedTo]), 24);
	new ptime = PlayerInfo[targetid][pConnectTime];
	new warns = PlayerInfo[targetid][pWarns];
	new cash = GetPlayerMoneyH(targetid);
	new deposit = PlayerInfo[targetid][pDeposit];
	new account = PlayerInfo[targetid][pBank];
	new lotto = PlayerInfo[targetid][pLottoNr];
	new deaths = PlayerInfo[targetid][pDeaths];
	new fishes = PlayerInfo[targetid][pFishes];
	new bigfish = PlayerInfo[targetid][pBiggestFish];
	new accident = PlayerInfo[playerid][pAccident];
	new ticket = PlayerInfo[playerid][pTicket];
	new crimes = PlayerInfo[targetid][pCrimes];
	new arrests = PlayerInfo[targetid][pArrested];
	new warrests = PlayerInfo[targetid][pWantedDeaths];
	new drugs = PlayerInfo[targetid][pDrugs];
	new mats = PlayerInfo[targetid][pMats];
	new mushrooms = PlayerInfo[targetid][pMushroom];
	new wanted = WantedLevel[targetid];
	new level = PlayerInfo[targetid][pLevel];
	new expamount = PlayerInfo[targetid][pRespect];
	new kills = PlayerInfo[targetid][pKills];
	new pnumber = PlayerInfo[targetid][pPnumber];

	new bizkey = PlayerInfo[targetid][pBizz];
	new intir = PlayerInfo[targetid][pInt];
	new local = PlayerInfo[targetid][pLocal];
	new wirtual = PlayerInfo[targetid][pVirtual];

	new Float:lhealth = LastHealth[targetid];
	new Float:shealth;
	GetPlayerHealth(playerid, shealth);

	new payday = PlayerInfo[targetid][pPayTime];
	new paycheck = PlayerInfo[targetid][pPayCheck];
	new std = PlayerInfo[targetid][pSTD];
	//======================================================================
	new text0[8], text1[8], text2[8], text3[8], text4[8], text5[8];
	new coordsstring[128];
	new name[MAX_PLAYER_NAME]; GetPlayerName(targetid, name, sizeof(name));
	if(GetPVarInt(playerid, "gDocuments") == 1)
	{
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "* %s показал %s'у свои Документы.", PlayerName(targetid), PlayerName(playerid));
		ProxDetector(targetid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

		new Float:px, Float:py, Float:pz; GetPlayerPos(targetid, px, py, pz);
		new tcity[20], tregion[20], tcar[32];
		new name_info[2][20]; split(name, name_info, '_');
 		if(housekey != NOT_KEY)
		{
			tcity = GetPointInZoneName(HouseInfo[housekey][hEntranceX], HouseInfo[housekey][hEntranceY], HouseInfo[housekey][hEntranceZ]);
			for(new j=0; j<MAX_TURFS; j++)
			{
				if( IsPointInRegion(HouseInfo[housekey][hEntranceX], HouseInfo[housekey][hEntranceY], HouseInfo[housekey][hEntranceZ], j) )//если дом находится в координатах по строке j из массива zones
				{
					strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 20);//Извлекает диапазон символов из строки.
					break;
				}
			}
		}
		else
		{
			tcity = "Los Santos"; tregion = "Jefferson";
			strmid(tcar, "None", 0, strlen("None"), 255);//Извлекает диапазон символов из строки.
		}//Motel
		if(carid1 <= 0) strmid(tcar, "None", 0, strlen("None"), 32);
		else
		{
			new modelid = VehInfo[carid1][cModel];//GetVehicleModel(carid1);
			strmid(tcar, VehicleArray[modelid-400][Vehicle_Name], 0, strlen(VehicleArray[modelid-400][Vehicle_Name]), 32);//Извлекает диапазон символов из строки.
		}
		new JobSkill, JobLevel;
		GetPlayerSkill(targetid, PlayerInfo[targetid][pJob], JobSkill, JobLevel);

		new msgitem[1476];//49+55+58+46+55 +29+ 61*3 + 37+62+37+38+35+46+51+40*7  +  24+2+4+2+4+20+20+2+(3+2+2+3)*3+24+20+1+3+20+20+3+8*6+24*7 = 1476
		strcat(msgitem, "{AFAFAF}________________________________________");
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}Имя: {FFFFFF}%s\t{0080FF}Фамилия: {FFFFFF}%s", name_info[0], name_info[1]);
		strcat(msgitem, coordsstring);
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}Пол: {FFFFFF}%s \t\t{0080FF}Возраст: {FFFFFF}%d", atext, age);
		strcat(msgitem, coordsstring);
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}Проживает: \t\t{FFFFFF}%d г.(%d ч.)", PlayerInfo[targetid][pLevel], PlayerInfo[targetid][pConnectTime]);
		strcat(msgitem, coordsstring);
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}Город: {FFFFFF}%s\t{0080FF}Улица: {FFFFFF}%s", tcity, tregion);
		strcat(msgitem, coordsstring);

		if(housekey != NOT_KEY)	{ format(coordsstring, sizeof(coordsstring), "\n{0080FF}№ дома: {FFFFFF}%d", housekey+1); strcat(msgitem, coordsstring); }

		if(carid1)	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}ID Авто1[lock/parking/insur]: {FFFFFF}%d[%d/%d/%d]",
				carid1, VehInfo[carid1][cLock], VehInfo[carid1][cPark], VehInfo[carid1][cInsur]);
			strcat(msgitem, coordsstring);
		}
		if(carid2)	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}ID Авто2[lock/parking/insur]: {FFFFFF}%d[%d/%d/%d]",
				carid2, VehInfo[carid2][cLock], VehInfo[carid2][cPark], VehInfo[carid2][cInsur]);
			strcat(msgitem, coordsstring);
		}
		if(carid3)	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}ID Авто3[lock/parking/insur]: {FFFFFF}%d[%d/%d/%d]",
				carid3, VehInfo[carid3][cLock], VehInfo[carid3][cPark], VehInfo[carid3][cInsur]);
			strcat(msgitem, coordsstring);
		}
		if( strcmp(PlayerInfo[targetid][pMarriedTo], "BeSingle", true) )	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}В браке за: \t\t{FFFFFF}%s", PlayerInfo[targetid][pMarriedTo]);
			strcat(msgitem, coordsstring);
		}
		if( PlayerInfo[targetid][pJob] != 0)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Работает: {FFFFFF}%s\t{0080FF}Skill: {FFFFFF}%d[%d]", GetPlayerJob(targetid), JobLevel, JobSkill);
			strcat(msgitem, coordsstring);
		}
		if( PlayerInfo[targetid][pMember] > 0 && PlayerInfo[targetid][pMember] < DoT)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Банда:\t\t{FFFFFF}%s", GetPlayerMembers(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Ранг: \t\t{FFFFFF}%s", GetPlayerRanks(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
		}
		else if( PlayerInfo[targetid][pMember] >= DoT)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Организация:\t\t{FFFFFF}%s", GetPlayerMembers(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Должность: \t\t{FFFFFF}%s", GetPlayerRanks(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
		}
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}Уважение: \t\t{FFFFFF}%d", PlayerInfo[targetid][pRespect]);
		strcat(msgitem, coordsstring);

        if(PlayerInfo[targetid][pBikeLic] == 1) { text0 = 	"Bike"; } else { text0 = ""; }//лицензия на мото
        if(PlayerInfo[targetid][pCarLic] == 1) { text1 = 	"Drivers"; } else { text1 = ""; }
		if(PlayerInfo[targetid][pFlyLic] == 1) { text2 = 	"Flying"; } else { text2 = ""; }
		if(PlayerInfo[targetid][pBoatLic] == 1) { text3 = 	"Sailing"; } else { text3 = ""; }
        if(PlayerInfo[targetid][pFishLic] == 1) { text4 = 	"Fishing"; } else { text4 = ""; }
        if(PlayerInfo[targetid][pGunLic] == 1) { text5 = 	"Weapon"; } else { text5 = ""; }

        format(coordsstring, sizeof(coordsstring), "\n{0080FF}Licenses: {FFFFFF}%s %s %s %s %s %s", text0, text1, text2, text3, text4, text5);
		strcat(msgitem, coordsstring);
		strcat(msgitem, "\n{AFAFAF}________________________________________");
		if(gGotOrder[targetid] < MAX_PLAYERS-1 && gGotOrder[targetid] != SOC_PACKET && gGotOrder[targetid] != QUIT_JOB)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Order: \t{FFFFFF}%s", PlayerName(gGotOrder[targetid]));
			strcat(msgitem, coordsstring);
		}
		else if(gGotOrder[targetid] < MAX_PLAYERS-1 && gGotOrder[targetid] == SOC_PACKET)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Соц. пакет: \t{FFFFFF}%s", PlayerName(gGotOrder[targetid]));
			strcat(msgitem, coordsstring);
		}
		else if(gGotOrder[targetid] < MAX_PLAYERS-1 && gGotOrder[targetid] == QUIT_JOB)
		{
			strcat(msgitem, "\n{0080FF}Разрешение на увольнение");
		}
		if(PlayerInfo[targetid][pSTD] == IsNotBeenIll)
		{
			strcat(msgitem, "\n{0080FF}Мед. осмотр: {FFFFFF}Получен");
		}
		if(GetPVarInt(playerid, "gGotPermit") == 1)
		{
			strcat(msgitem, "\n{0080FF}Разрешение: {FFFFFF}House");
		}
		else if(GetPVarInt(playerid, "gGotPermit") == 2)
		{
			strcat(msgitem, "\n{0080FF}Разрешение: {FFFFFF}Business");
		}
		else if(GetPVarInt(playerid, "gGotPermit") == 3)
		{
			strcat(msgitem, "\n{0080FF}Разрешение: {FFFFFF}Company");
		}
		//ShowPlayerDialogGap(playerid, 65, DIALOG_STYLE_MSGBOX, "{0000FF}PASSPORT OF CITIZEN OF THE SAN ANDREAS", msgitem, "Return", "Take");
		ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "{80FFFF}PASSPORT OF CITIZEN OF THE SAN ANDREAS", msgitem, "OK", "");
		SetPVarInt(playerid, "gDocuments", 0);
    	return 1;
	}
	else //if(GetPVarInt(playerid, "gDocuments") == 2)
	{
		//if(PlayerInfo[playerid][pAdmin] > 0) ShowStats(playerid, targetid);

		format(coordsstring, sizeof(coordsstring), "*** {FFFFFF}%s{33AA33} ***____________________________________________________________________________",name);
		SendClientMessage(playerid, COLOR_GREEN,coordsstring);
		format(coordsstring, sizeof(coordsstring), "gPlayerLogged:%d, gPlayerSpawned:%d, CurState:%d",
			gPlayerLogged[targetid], gPlayerSpawned[targetid], CurState[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);

		format(coordsstring, sizeof(coordsstring), "Hаличных:[$%d] В Банке:[$%d] На депозите:[$%d] PayTime/PayCheck/Online:[%d/%d/%d]",
			cash,account,deposit, payday, paycheck, PlayerInfo[targetid][pConnectTime]-PlayerInfo[targetid][pOnline]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Здоровье:[%.0f/%.0f] Телефон:[%d] Пол:[%s] Возраст:[%d] Откуда:[%s] Модель:%d[Сhar:%d]",
			lhealth,shealth,pnumber,atext,age,otext, PlayerInfo[targetid][pModel], PlayerInfo[targetid][pChar]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Уровень:[%d] Часов:[%d] Уважение:[%d] Warn:[%d] Обручён:[%s] Заболевание:[%d]",
			level, ptime, expamount, warns, married, std);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Hаркотиков:[%d] Материалов:[%d] Рыб Поймано:[%d] Большая Рыба:[%d] Грибов:[%d] Лотерейный №:[%d]",
			drugs,mats,fishes,bigfish, mushrooms,lotto);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Cмертей:[%d] Убийств:[%d] ДТП:[%d] Штрафов:[%d] Преступлений:[%d] Уровень Розыска:%d[%d мин] Арестов:[%d] Смертей при Розыске:[%d]",
			deaths,kills,accident,ticket,crimes,wanted,WantedPoints[targetid]*5,arrests,warrests);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Pабота:[%s(duty:%d)] ContractTime:[%d] Фракция:[%s] Должность:[%s(duty:%d)] Миссия:%d[%d]",
			GetPlayerJob(targetid), gJobDuty[targetid], PlayerInfo[targetid][pContractTime], GetPlayerMembers(targetid), GetPlayerRanks(targetid), gOnDuty[targetid], PlayerInfo[targetid][pTut], gCheckInMission[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Личное авто1[lock/parking/insur]: авто1: %d[%d/%d/%d], авто2: %d[%d/%d/%d], авто3: %d[%d/%d/%d]",
			carid1, VehInfo[carid1][cLock], VehInfo[carid1][cPark], VehInfo[carid1][cInsur],
			carid2, VehInfo[carid2][cLock], VehInfo[carid2][cPark], VehInfo[carid2][cInsur],
			carid3, VehInfo[carid3][cLock], VehInfo[carid3][cPark], VehInfo[carid3][cInsur]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "ПрокатноеАвто[lock]: %d[%d], Последн.Авто[lock]: %d[%d], Серфавто: %d, CarTime: %d",
			HireCarID[targetid],iVehicleObjective[HireCarID[targetid]][MAX_PLAYERS-1],
			LastCar[targetid],iVehicleObjective[LastCar[targetid]][MAX_PLAYERS-1],
			GetPlayerSurfingVehicleID(targetid),
			PlayerInfo[targetid][pCarTime]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		//----------------------------------------------------------------------
		format(coordsstring, sizeof(coordsstring), "Kлюч от дома:[%d] Kлюч от биза:[%d] Интерьер:[%d] Локация:[%d] Мир:[%d]", housekey, bizkey, intir,local,wirtual);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		new AdminLevel = PlayerInfo[targetid][pAdmin];

		new Float:armour;	GetPlayerArmour(targetid, armour);
        new Gun = GetPlayerWeapon(targetid); new Ammo = GetPlayerAmmo(targetid);
		format(coordsstring, sizeof(coordsstring), "Aккаунт:[%s] Armour:[%.0f] Gun:[%d] Ammo:[%d] PlayerIP:[%s] AdminLevel:[%d] AFK_IdleSec:[%d]",
			actext,armour,Gun,Ammo, PlayerInfo[targetid][pIP],AdminLevel,AFK_IdleTime[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		if(PlayerInfo[targetid][pBikeLic] == 1) { text0 = "Bike"; } else { text0 = ""; }//лицензия на мото
        if(PlayerInfo[targetid][pCarLic] == 1) { text1 = "Drivers"; } else { text1 = ""; }
		if(PlayerInfo[targetid][pFlyLic] == 1) { text2 = "Flying"; } else { text2 = ""; }
		if(PlayerInfo[targetid][pBoatLic] == 1) { text3 = "Sailing"; } else { text3 = ""; }
        if(PlayerInfo[targetid][pFishLic] == 1) { text4 = "Fishing"; } else { text4 = ""; }
        if(PlayerInfo[targetid][pGunLic] == 1) { text5 = "Weapon"; } else { text5 = ""; }
        format(coordsstring, sizeof(coordsstring), "Licenses: %s %s %s %s %s %s", text0, text1, text2, text3, text4, text5);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "CallTime:[%d] Marker:[%d] Anticheat:[%d] Team:[%d] Vote:[%d] Controllable:[%d]",
			CallTimeCounter[targetid], MarkerToPlayer[targetid], gAnticheat[targetid], PlayerInfo[targetid][pTeam], PlayerInfo[targetid][pVote], IsPlayerControllable[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		//}
		SendClientMessage(playerid, COLOR_GREEN, "__________________________________________________________________________________________________________");
	}
	return 1;
}//end OnPlayerShowStats(playerid, targetid)





