//для обучения начало
new TutTimeCounter[MAX_PLAYERS];//признак и счётчик переходов в обычном обучении

//##############################################################################//
//                                                                              //
//                                СПИСКИ МАНУАЛОВ                               //
//                                                                              //
//##############################################################################//

//stock HELP(playerid)//т.к. плохо под автозамену
stock help_OnPlayerKeyStateChange(playerid)
{
	if(gate_IsAtGate(playerid)) return 1;
	new listitems[946+41];
	strcat(listitems, "{00FF00} - меню игрока \t{FFFFFF}/menu\n");//0
	strcat(listitems, "{00FF00} - GPS-навигатор\t{FFFFFF}/gps\n");//0
	/*strcat(listitems, "{00FF00} - Мобильный телефон\t{FFFFFF}/phone\n");
	strcat(listitems, "{00FF00} - Инвентарь\t{FFFFFF}/inv\n");
	strcat(listitems, "{00FF00} - Связь с администрацией\t{FFFFFF}/report\n");
	strcat(listitems, "{00FF00} - Главное меню\t{FFFFFF}/mm\n");*/
	strcat(listitems, "{00FF00} - список услуг\t{FFFFFF}/service\n");//1
	strcat(listitems, "{00FF00} - общая игровая информация\t{FFFFFF}/info\n");//2
	strcat(listitems, "{00FF00} - правила сервера\t{FFFFFF}/rules\n");//3//strcat(listitems, "{FFFFFF}\n/items\t\t{00FF00}инвентарь");
	strcat(listitems, "{00FF00} - общее обучение\t{FFFFFF}/tutorial\n");//4
	strcat(listitems, "{00FF00} - списки команд, списки игроков\t{FFFFFF}/list\n");//5
	strcat(listitems, "{00FF00} - помощь по выбранной профессии\t{FFFFFF}/jobmanual\n");//6
	strcat(listitems, "{00FF00} - помощь по телефону\t{FFFFFF}/phonehelp\n");//7
	strcat(listitems, "{00FF00} - помощь по дому\t{FFFFFF}/househelp\n");//8
	strcat(listitems, "{00FF00} - помощь по кланам\t{FFFFFF}/clanhelp\n");//9
	strcat(listitems, "{00FF00} - помощь по рыбалке\t{FFFFFF}/fishhelp\n");//10
	strcat(listitems, "{00FF00} - помощь по цветам ников игроков\t{FFFFFF}/color\n");//11
	strcat(listitems, "{00FF00} - ServerInfo\t{FFFFFF}/settings\n");//12
	strcat(listitems, "{00FF00} - помощь по кухне\t{FFFFFF}/cookhelp\n");//13
	strcat(listitems, "{00FF00} - помощь по вступлению в брак\t{FFFFFF}/marriagehelp\n");//14
	strcat(listitems, "{00FF00} - помощь по IRC-чату\t{FFFFFF}/irchelp\n");//15
	strcat(listitems, "{00FF00} - преимущества премиум аккаунта\t{FFFFFF}/viphelp\n");//16
	strcat(listitems, "{00FF00} - стандартные интерьеры\t{FFFFFF}/int\n");//17

	//ShowPlayerDialogGap(playerid, HELP_DIALOG, DIALOG_STYLE_LIST, "HELP - наберите команду для информации", listitems, "OK", "Exit");
	ShowPlayerDialogGap(playerid, HELP_DIALOG, DIALOG_STYLE_TABLIST, "Быстрое меню", listitems, "Выбрать", "Закрыть");
	return 1;
}
stock backhelp_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != BACKHELP_DIALOG) return 1;
	#pragma unused listitem
	#pragma unused inputtext
//ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "*** CAR HELP *** наберите команду для информации", listitems, "OK", "Назад");
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
		return 1;
	}
	PlaySoundForPlayer(playerid, 5202);
	return 1;
}


//##############################################################################//
//                                                                              //
//                                СПИСКИ МАНУАЛОВ                               //
//                                                                              //
//##############################################################################//

stock help_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused inputtext
	backhelp_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	report_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);//вызывается из vw_help.inc
	list_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	if(dialogid != HELP_DIALOG) return 1;
	//ShowPlayerDialogGap(playerid, HELP_DIALOG, DIALOG_STYLE_LIST, "*** HELP *** наберите команду для информации", listitems, "OK", "Cancel");
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
	   	PlaySoundForPlayer(playerid, 5202);
 		return 1;
	}
	if(listitem == 0) admin_OnPlayerClick(playerid, playerid);//PlayerMenu(playerid);
	else if(listitem == 1) gpsitem_help(playerid);//GPS-навигатор
	else if(listitem == 2) ServiceHelp(playerid);//список услуг /service
	else if(listitem == 3) AboutServer(playerid);//общая информация о сервере
	else if(listitem == 4) Rules(playerid);//правила сервера
	else if(listitem == 5)
	{//общее обучение
    	if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
		{
			SetPVarInt(playerid, "gOoc", 1);
			SetPVarInt(playerid, "gNews", 1);
			SetPVarInt(playerid, "gFam", 1);
			SetPVarInt(playerid, "gHidePM", 0);
			SetPVarInt(playerid, "gSport", 1);
			SetPVarInt(playerid, "gJob", 1);//для чата
		}//Общий чат отключен
		TutTimeCounter[playerid] = 1;//поднимаем флаг чтобы начать
	 	Tutorial(playerid);//общее обучение
	}
	else if(listitem == 6) LIST(playerid);//списки команд, списки игроков//cmd - списки команд
	else if(listitem == 7)//помощь по выбранной профессии
	{   ///jobmanual
	    if(PlayerInfo[playerid][pJob] == 0)
	    {
			help_OnPlayerKeyStateChange(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   JobManual пуст! Вы ни кем не работаете !");
			return 1;
	    }
		JobManual(playerid, 32, DIALOG_STYLE_MSGBOX, "OK", "Назад", PlayerInfo[playerid][pJob]);//caption, bigmsgitem,
		//return 1;
	}
	else if(listitem == 8)//помощь по телефону
	{   //phonehelp
		PhoneHelp(playerid);
	}
	else if(listitem == 9) HouseHelp(playerid);//помощь по дому
	else if(listitem == 10)//помощь по кланам
	{   //clanhelp
		ClanHelp(playerid);
	}
	else if(listitem == 11)//помощь по рыбалке
	{   //fishhelp //\n/sell fish - продать рыбу в магазине 24-7
		FishHelp(playerid);
	}
	else if(listitem == 12) ColorHelp(playerid);//помощь по цветам ников игроков
	else if(listitem == 13) ServerInfo(playerid);//Настройки сервера
	else if(listitem == 14)//помощь по кухне
	{   //cookhelp
		new dlgitem[] = "/cook [Lastfish,Fish,Chicken,Hamburger,Pizza] - готовить\n\
в Burger Shot, Pizza Stack или Cluckin' Bell у плиты\n\
/cooked - список приготовленных блюд\n\
/eat – Съесть то, что Вы приготовили";
		ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "COOK HELP - наберите команду для информации", dlgitem, "OK", "Назад");
	}
	else if(listitem == 15)//помощь по вступлению в брак
	{   //marriagehelp
		new dlgitem[] = "/propose - сделать предложение\n\
/divorce - расторгнуть Брак\n\
/witness - попросить быть вашим Свидетелем на Свадьбе\n\
/kiss - поцеловать";
		ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "MARRIAGE HELP - наберите команду для информации", dlgitem, "OK", "Назад");
	}
	else if(listitem == 16)//помощь по IRC-чату
	{   //irchelp
		new dlgitem[] = "/irc join - войти на irc-канал\n\
/irc leave - выйти с irc-канала\n\
/giverank - дать доступный ранг\n\
/irc Password - установить пароль на этом irc-канале\n\
/irc NeedPass - изменить на данном irc-канале\n\t\tнеобходимость ввода пароля\n\
/irc Lock - закрыть irc-канал\n\
/irc Admins - посмотреть ник админа irc-канала\n\
/irc MOTD - изменить текст приветствия irc-канала\n\
/irc status - посмотреть информацию по данному irc-каналу\n\
/i - писать в irc-чате";
		ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "IRC HELP - наберите команду для информации", dlgitem, "OK", "Назад");
	}
	else if(listitem == 17) VIPHelp(playerid);//преимущества премиум аккаунта
	else if(listitem == 18) interior_Example(playerid);
	return 1;
}

stock PhoneHelp(playerid)
{
	if(PlayerInfo[playerid][pPnumber] > 0)
	{
		new dlgitem[] = "(/p)ickup(Y) - поднять трубку, когда вам звонят\n\
						(/h)angup(N) - повесить трубку";
		ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "PHONE HELP - наберите команду для информации", dlgitem, "OK", "Назад");
	}
	else
	{
		help_OnPlayerKeyStateChange(playerid);
		SendClientMessage(playerid, COLOR_WHITE, "Вы можете купить телефон в любом магазине 24-7");
	}
}

stock HouseHelp(playerid)
{
	new dlgitem[30+36+43+41+47+29];
	strcat(dlgitem, "/buy - купить свободный дом\n");
	strcat(dlgitem, "/prop - список вашей недвижимости\n");
	strcat(dlgitem, "/rentroom - снять комнату/поменять ключи\n");
	strcat(dlgitem, "/unrent - отказаться от аренды комнаты\n");
	strcat(dlgitem, "/tv - Смотреть ТВ-трансляцию сотрудников САН\n");
	strcat(dlgitem, "/heal - Пополнить здоровье\n");
	ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "HOUSE HELP - наберите команду для информации", dlgitem, "OK", "Назад");
}

stock ClanHelp(playerid)
{
		new dlgitem[] = "\n/opencompany - создать клан\
\n/closecompany - удалить клан\
\n/slogan - лозунг партии\
\n/enterclan - войти в клан\
\n/exitclan - выйти из клана\
\n/clanmoney - касса клана\
\n/clan - чат клана";
		ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "* CLAN HELP * наберите команду для информации", dlgitem, "OK", "Назад");
}
stock FishHelp(playerid)
{
		new dlgitem[] = "/fish - закинуть удочку\n\
						/fishes - показать рыб, которых Вы поймали\n\
						/throwback - выбросить последнюю пойманую рыбу\n\
						/throwbackall - выбросить всю рыбу\n\
						/releasefish - отпустить указанную рыбу\n\
						/sell fish - продать рыбу в магазине 24-7\n\
						/eat fish - съесть приготовленную рыбу";
		ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "FISH HELP - наберите команду для информации", dlgitem, "OK", "Назад");
}
stock ColorHelp(playerid)
{
   	new listitems[70+70*20];
	new strtmp[70];
   	format(strtmp, sizeof(strtmp), "{FFFFFF}%d. \t{%06x}Нет лицензии на оружие\n",
		0, COLOR_NEWBIE >>> 8);
   	strcat(listitems, strtmp);
	for(new i = TEAM_GROVE; i <= DoE; i++)
	{
       	format(strtmp, sizeof(strtmp), "{FFFFFF}%d. \t{%06x}Фракция : %s\n",
			i, FamilyInfo[i][fColor] >>> 8, FamilyInfo[i][fName]);
       	strcat(listitems, strtmp);
	}
	ShowPlayerDialogGap(playerid, BACKHELP_DIALOG, DIALOG_STYLE_LIST, "Помощь по цветам ников игроков", listitems, "OK", "Назад");
	return 1;
}


//##############################################################################//
//                                                                              //
//                                     СПИСКИ                                   //
//                                                                              //
//##############################################################################//
stock LIST(playerid)
{
	new listitems[946];
 	strcat(listitems, "{FFFFFF}/cmd\t\t{00FF00}cписок команд");//0
 	strcat(listitems, "{FFFFFF}\n/leaders\t{00FF00}список лидеров");//0
	strcat(listitems, "{FFFFFF}\n/dutylist\t\t{00FF00}список игроков на дежурстве");
	strcat(listitems, "{FFFFFF}\n/race\t\t{00FF00}список гонок для участия");
	strcat(listitems, "{FFFFFF}\n/records\t{00FF00}список лучших");
	strcat(listitems, "{FFFFFF}\n/admins\t\t{00FF00}список администраторов");
	strcat(listitems, "{FFFFFF}\n/instructors\t{00FF00}список инструкторов");
	strcat(listitems, "{FFFFFF}\n/lawyers\t{00FF00}список адвокатов");
	strcat(listitems, "{FFFFFF}\n/cardealer\t{00FF00}список автодилеров");
	strcat(listitems, "{FFFFFF}\n/womans\t{00FF00}список девушек");
	strcat(listitems, "{FFFFFF}\n/referals\t{00FF00}список учеников");//для рефералов
	strcat(listitems, "{FFFFFF}\n/animlist\t{00FF00}список анимаций");
	strcat(listitems, "{FFFFFF}\n/banlist\t\t{00FF00}список забаненых");//11
	//strcat(listitems, "{FFFFFF}\n/walk\t{00FF00}список стилей походки", strlen(listitems));
	ShowPlayerDialogEx(playerid, LIST_DIALOG, DIALOG_STYLE_LIST, "LIST - наберите команду для информации", listitems, "OK", "Назад");
}
stock list_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != LIST_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		help_OnPlayerKeyStateChange(playerid);
		return 1;
	}
	if(listitem == 0) command_help(playerid);//LISTCOMMAND(playerid);
	else if(listitem == 1) LeadersOnline(playerid);
	else if(listitem == 2) DutyList(playerid);
	else if(listitem == 3)
	{
#if defined vw_races
		race_Menu(playerid);//для гонок STEP1
#endif
	}
	else if(listitem == 4) BestOfTheBest(playerid);
	else if(listitem == 5) AdminsOnline(playerid);//список администраторов
	else if(listitem == 6) InstructorsOnline(playerid);
	else if(listitem == 7) LawyersOnline(playerid);
	else if(listitem == 8) CarDealerOnline(playerid);
	else if(listitem == 9) WomansOnline(playerid);
	else if(listitem == 10) ReferalsOnline(playerid);//для рефералов
	else if(listitem == 11) anim_List(playerid);
	else if(listitem == 12)
	{   ///banlist
		if(PlayerInfo[playerid][pAdmin] < 1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
		    return 1;
		}
#if defined vw_sql//#endif
 		ShowPlayerBans(playerid);
#endif
	}
	return 1;
}
stock backlist_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{//Обработка кнопки НАЗАД
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BACKLIST_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		LIST(playerid);
		return 1;
	}
	PlaySoundForPlayer(playerid, 5202);
	return 1;
}

stock LeadersOnline(playerid)
{
	new dlgitem[1024+12];
	strins(dlgitem, "family \t\t\t\tname[id]\n______________________________________________________________________\n", strlen(dlgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pLeader] != 0)
		{
			if(strlen(GetFamilyName(PlayerInfo[i][pLeader])) < 13) format(strings, sizeof(strings), "%s \t\t\t%s[%d]\n", GetFamilyName(PlayerInfo[i][pLeader]), PlayerName(i),i);
			else if(strlen(GetFamilyName(PlayerInfo[i][pLeader])) >= 13 && strlen(GetFamilyName(PlayerInfo[i][pLeader])) < 18) format(strings, sizeof(strings), "%s \t\t%s[%d]\n", GetFamilyName(PlayerInfo[i][pLeader]), PlayerName(i),i);
			else format(strings, sizeof(strings), "%s \t%s[%d]\n", GetFamilyName(PlayerInfo[i][pLeader]), PlayerName(i),i);
			strins(dlgitem, strings, strlen(dlgitem));
		}
	}
	strins(dlgitem, "\n______________________________________________________________________\n", strlen(dlgitem));
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Leaders Online %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_MSGBOX, "Leaders Online:", dlgitem, "OK", "Назад");
	return 1;
}

new dutylist[MAX_PLAYERS][176];//53+86+24+3+2+8 = 176 для показа вышедших на дежурство //не переводить на пивар

stock DutyList(playerid)
{   //вызывается из list_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) и OnPlayerCommandText -> else if(!strcmp(cmd, "/dutylist", true))
	new bigmsgitem[2048];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if((gJobDuty[i] || gOnDuty[i]) && strlen(dutylist[i]))
		{
			strins(bigmsgitem, dutylist[i], strlen(bigmsgitem));
		}
	}
	if(strlen(bigmsgitem) >= sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: DutyList %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		//ABroadCast(COLOR_RED, strings, 1);
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   DutyList пуст");//COLOR_BLUEGREY
		LIST(playerid);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_LIST, "Duty List: На Дежурстве", bigmsgitem, "OK", "Назад");
	return 1;
}




stock BestOfTheBest(playerid)
{
	new bestitem0[40], bestitem1[40], bestitem2[40], bestitem3[40], bestitem4[40], bestitem5[40], bestitem6[40], bestitem7[40];
	new bestitem8[40], bestitem9[40], bestitem10[40], bestitem11[40], bestitem12[40], bestitem13[40], bestitem14[40], bestitem15[40];
	new bestitem16[40], bestitem17[40], bestitem18[40], bestitem19[40], bestitem20[40], bestitem21[40], bestitem22[40], bestitem23[40];
	new bestitem24[40], bestitem25[40], bestitem26[40];
	new BestSkill[27];
	new AmountAchievedZones[TEAM_MAFIA+1];
	for(new g = 1; g <= TEAM_MAFIA; g++)
	{   //сканируем все банды
		for(new j=0; j<MAX_TURFS; j++)//MAX_TURFS
		{   //сканируем все зоны
	        if(TurfInfo[j][zFamily] == FamilyInfo[g][NumberFamily])
        	{   //если зона принадлежит банде в которой находится игрок
				AmountAchievedZones[FamilyInfo[g][NumberFamily]] ++;
			}
		}
	}
	for(new g = 1; g <= TEAM_MAFIA; g++)
	{   //сканируем все банды
        if(AmountAchievedZones[FamilyInfo[g][NumberFamily]] > BestSkill[0])
        {   //если у данной банды больше зон чем у предыдущей
			BestSkill[0] = AmountAchievedZones[FamilyInfo[g][NumberFamily]];
   			format(bestitem0, sizeof(bestitem0), "Банда: \t\t\t%s\n", FamilyInfo[g][fName]);
		}
	}
	//------------------------------------------------------------------
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] == DoT)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem1, sizeof(bestitem1), "Инспектор ДПС: \t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pMember] == FBI)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem2, sizeof(bestitem2), "Агент FBI: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pMember] == DoD)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem3, sizeof(bestitem3), "Охранник NG: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pMember] == DoH)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem4, sizeof(bestitem4), "Спасатель MoH: \t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pMember] == Hitman)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem5, sizeof(bestitem5), "Киллер: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pMember] == SAN)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem6, sizeof(bestitem6), "Репортёр SAN: \t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pMember] == DoE)
		{
			if(PlayerInfo[i][pProfSkill] > BestSkill[PlayerInfo[i][pMember]])
			{
				BestSkill[PlayerInfo[i][pMember]] = PlayerInfo[i][pProfSkill];
		    	format(bestitem7, sizeof(bestitem7), "Инструктор DoE: \t%s\n", PlayerName(i));
			}
		}
		//----------------------------------------------------------
		if(PlayerInfo[i][pJob] == 1)
		{
			if(PlayerInfo[i][pMinerSkill] > BestSkill[8])
			{
				BestSkill[8] = PlayerInfo[i][pMinerSkill];
		    	format(bestitem8, sizeof(bestitem8), "Шахтёр: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == LAWYER)
		{
			if(PlayerInfo[i][pLawSkill] > BestSkill[9])
			{
				BestSkill[9] = PlayerInfo[i][pLawSkill];
		    	format(bestitem9, sizeof(bestitem9), "Адвокат: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == ROADWORKER)
		{
			if(PlayerInfo[i][pRoadSkill] > BestSkill[10])
			{
				BestSkill[10] = PlayerInfo[i][pRoadSkill];
		    	format(bestitem10, sizeof(bestitem10), "Дорожный Рабочий: \t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == DRUGDEALER)
		{
			if(PlayerInfo[i][pDrugsSkill] > BestSkill[11])
			{
				BestSkill[11] = PlayerInfo[i][pDrugsSkill];
		    	format(bestitem11, sizeof(bestitem11), "Наркодилер: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == CARJACKER)
		{
			if(PlayerInfo[i][pJackSkill] > BestSkill[12])
			{
				BestSkill[12] = PlayerInfo[i][pJackSkill];
		    	format(bestitem12, sizeof(bestitem12), "Автоугонщик: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == CARMECHANIC)
		{
			if(PlayerInfo[i][pMechSkill] > BestSkill[13])
			{
				BestSkill[13] = PlayerInfo[i][pMechSkill];
			    format(bestitem13, sizeof(bestitem13), "Механик: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == ARMSDEALER)
		{
			if(PlayerInfo[i][pGunSkill] > BestSkill[14])
			{
				BestSkill[14] = PlayerInfo[i][pGunSkill];
		    	format(bestitem14, sizeof(bestitem14), "Оружейник: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == CARDEALER)
		{
			if(PlayerInfo[i][pCarSkill] > BestSkill[15])
			{
				BestSkill[15] = PlayerInfo[i][pCarSkill];
		    	format(bestitem15, sizeof(bestitem15), "Автодилер: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == INKASSATOR)
		{
			if(PlayerInfo[i][pInkasSkill] > BestSkill[16])
			{
				BestSkill[16] = PlayerInfo[i][pInkasSkill];
		    	format(bestitem16, sizeof(bestitem16), "Инкассатор: \t\t%s\n", PlayerName(i));
			}
		}
		//if(PlayerInfo[i][pJob] == BOOKMAKER)
		if(PlayerInfo[i][pJob] == BOOKMAKER)
		{
			if(PlayerInfo[i][pBookmakerSkill] > BestSkill[17])
			{
				BestSkill[17] = PlayerInfo[i][pBookmakerSkill];
		    	format(bestitem17, sizeof(bestitem17), "Букмекер: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == TAXIDRIVER)
		{
			if(PlayerInfo[i][pTaxiSkill] > BestSkill[18])
			{
				BestSkill[18] = PlayerInfo[i][pTaxiSkill];
		    	format(bestitem18, sizeof(bestitem18), "Таксист: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == BUSDRIVER)
		{
			if(PlayerInfo[i][pBusSkill] > BestSkill[19])
			{
				BestSkill[19] = PlayerInfo[i][pBusSkill];
		    	format(bestitem19, sizeof(bestitem19), "Водитель Автобуса: \t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == PAPERBOY)
		{
			if(PlayerInfo[i][pCourierSkill] > BestSkill[20])
			{
				BestSkill[20] = PlayerInfo[i][pCourierSkill];
		    	format(bestitem20, sizeof(bestitem20), "Курьер: \t\t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pJob] == TRUCKER)
		{
			if(PlayerInfo[i][pTruckSkill] > BestSkill[21])
			{
				BestSkill[21] = PlayerInfo[i][pTruckSkill];
		    	format(bestitem21, sizeof(bestitem21), "Дальнобойщик: \t%s\n", PlayerName(i));
			}
		}
		if(PlayerInfo[i][pFishSkill] > BestSkill[22])
		{
			BestSkill[22] = PlayerInfo[i][pFishSkill];
	    	format(bestitem22, sizeof(bestitem22), "Рыбалов: \t\t%s\n", PlayerName(i));
		}
		if(PlayerInfo[i][pCrimes] > BestSkill[23])
		{
			BestSkill[23] = PlayerInfo[i][pCrimes];
	    	format(bestitem23, sizeof(bestitem23), "Криминал.Авторитет: \t%s\n", PlayerName(i));
		}
		if((PlayerInfo[i][pKills]-PlayerInfo[i][pDeaths]) > BestSkill[24])
		{
			BestSkill[24] = PlayerInfo[i][pKills]-PlayerInfo[i][pDeaths];
			format(bestitem24, sizeof(bestitem23), "Стрелок: \t\t%s\n", PlayerName(i));
		}
		if((PlayerInfo[i][pBank] + PlayerInfo[i][pCash] + PlayerInfo[i][pDeposit]) > BestSkill[25])
		{
			BestSkill[25] = PlayerInfo[i][pBank] + PlayerInfo[i][pCash] + PlayerInfo[i][pDeposit];
	    	format(bestitem25, sizeof(bestitem25), "Казначей: \t\t%s\n", PlayerName(i));
		}
		if(PlayerInfo[i][pConnectTime] > BestSkill[26])
		{
			BestSkill[26] = PlayerInfo[i][pConnectTime];
	    	format(bestitem26, sizeof(bestitem26), "Долгожитель: \t\t%s\n", PlayerName(i));
		}
	}
	//------------------------------------------------------------------
	new listitems[1080];//1080
	//strdel(listitems, 0, sizeof(listitems));
	if(strlen(bestitem0) > 0) strins(listitems, bestitem0, strlen(listitems));
	if(strlen(bestitem1) > 0) strins(listitems, bestitem1, strlen(listitems));
	if(strlen(bestitem2) > 0) strins(listitems, bestitem2, strlen(listitems));
	if(strlen(bestitem3) > 0) strins(listitems, bestitem3, strlen(listitems));
	if(strlen(bestitem4) > 0) strins(listitems, bestitem4, strlen(listitems));
	if(strlen(bestitem5) > 0) strins(listitems, bestitem5, strlen(listitems));
	if(strlen(bestitem6) > 0) strins(listitems, bestitem6, strlen(listitems));
	if(strlen(bestitem7) > 0) strins(listitems, bestitem7, strlen(listitems));
	if(strlen(bestitem8) > 0) strins(listitems, bestitem8, strlen(listitems));
	if(strlen(bestitem9) > 0) strins(listitems, bestitem9, strlen(listitems));
	if(strlen(bestitem10) > 0) strins(listitems, bestitem10, strlen(listitems));
	if(strlen(bestitem11) > 0) strins(listitems, bestitem11, strlen(listitems));
	if(strlen(bestitem12) > 0) strins(listitems, bestitem12, strlen(listitems));
	if(strlen(bestitem13) > 0) strins(listitems, bestitem13, strlen(listitems));
	if(strlen(bestitem14) > 0) strins(listitems, bestitem14, strlen(listitems));
	if(strlen(bestitem15) > 0) strins(listitems, bestitem15, strlen(listitems));
	if(strlen(bestitem16) > 0) strins(listitems, bestitem16, strlen(listitems));
	if(strlen(bestitem17) > 0) strins(listitems, bestitem17, strlen(listitems));
	if(strlen(bestitem18) > 0) strins(listitems, bestitem18, strlen(listitems));
	if(strlen(bestitem19) > 0) strins(listitems, bestitem19, strlen(listitems));
	if(strlen(bestitem20) > 0) strins(listitems, bestitem20, strlen(listitems));
	if(strlen(bestitem21) > 0) strins(listitems, bestitem21, strlen(listitems));
	if(strlen(bestitem22) > 0) strins(listitems, bestitem22, strlen(listitems));
	if(strlen(bestitem23) > 0) strins(listitems, bestitem23, strlen(listitems));
	if(strlen(bestitem24) > 0) strins(listitems, bestitem24, strlen(listitems));
	if(strlen(bestitem25) > 0) strins(listitems, bestitem25, strlen(listitems));
	if(strlen(bestitem26) > 0) strins(listitems, bestitem26, strlen(listitems));
	//strdel(listitems, 1280, 5600);
	if(strlen(listitems) > sizeof(listitems))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Best of the Best %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(listitems), sizeof(listitems));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(listitems) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Best of the Best пуст");
		LIST(playerid);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_LIST, "Best of the Best", listitems, "OK", "Назад");
  	return 1;
}



stock AdminsOnline(playerid)
{
	new listitems[20*(27+2+3+12+24+3)];//29*(27+2+3+12+24+3)
	new DialogIDCounter = 0; for(new i=0; i<MAX_DLGITEMS; i++) { DialogID[playerid][i] = -1; }
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//если игрок подключен
		//if(PlayerInfo[i][pAdmin] < 1 || (PlayerInfo[i][pAdmin] > 5 && PlayerInfo[i][pLeader] != DoJ)) continue;// && PlayerInfo[i][pAdmin] < 10
		if(PlayerInfo[i][pAdmin] < 1) continue;
		//if(AFK_IdleTime[i] >= 3) continue;
		//если находим ID игрока у которого параметр pAdmin >0
		DialogID[playerid][DialogIDCounter] = i;//listitem
		if(	PlayerInfo[i][pAdmin] == 2 || PlayerInfo[i][pAdmin] == 4 ||
			PlayerInfo[i][pAdmin] == 5)
		{
			format(strings, sizeof(strings),
				"%d\t*%d* %s: \t%s [%d]\n", DialogIDCounter+1,
				PlayerInfo[i][pAdmin], GetAdminRanks(i), PlayerName(i), i);
		}
		else
		{
			format(strings, sizeof(strings),
				"%d\t*%d* %s: \t\t%s [%d]\n", DialogIDCounter+1,
				PlayerInfo[i][pAdmin], GetAdminRanks(i), PlayerName(i), i);
		}
		strins(listitems, strings, strlen(listitems));
		DialogIDCounter ++;
	}
	if(strlen(listitems) > sizeof(listitems))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Admins Online %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(listitems), sizeof(listitems));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(listitems) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Admins Online пуст");//COLOR_BLUEGREY
		LIST(playerid);
		return 1;
	}
//Проблема должна соответствовать группе админа
//Формулируйте свою проблему чётко и ясно. \nНе стоит флудить, т.к. можно получить молчанку.
	MenuOperation[playerid] = 53;
	ShowPlayerDialogGap(playerid, REPORT_DIALOG, DIALOG_STYLE_LIST, "Администратор вправе наказывать за злоупотребление этой функцией", listitems, "OK", "Назад");
	return 1;
}
stock report_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != REPORT_DIALOG) return 1;
	if(!response)
	{
		SetPVarInt(playerid, "gShowDialog", -1);
		LIST(playerid);
		return 1;
	}
	
	//#pragma unused inputtext
//ShowPlayerDialogGap(playerid, 31, DIALOG_STYLE_LIST, "Администратор вправе наказывать за злоупотребление этой функцией", listitems, "OK", "Cancel");
//ShowPlayerDialogEx(playerid, 31, DIALOG_STYLE_INPUT, "REPORT", dlgitem, "OK", "Cancel");
	SetPVarInt(playerid, "gShowDialog", -1);
	new msgitem[256+1];
	new giveplayerid;
	if(MenuOperation[playerid] == 53)
	{
		if(PlayerInfo[playerid][pMuted] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете говорить, Вы заглушены!");
			return 1;
		}
		SetPVarInt(playerid, "PlayerID", DialogID[playerid][listitem]);
		giveplayerid = DialogID[playerid][listitem];
		new dlgitem[200];
        format(dlgitem, sizeof(dlgitem), "Введите текст для администратора %s[%d]\
\nФормулируйте свою проблему чётко и ясно\
\nНе стоит флудить, т.к. можно получить молчанку.\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.",
		PlayerName(giveplayerid), giveplayerid);
    	MenuOperation[playerid] = 54;
		ShowPlayerDialogEx(playerid, REPORT_DIALOG, DIALOG_STYLE_INPUT, "REPORT", dlgitem, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 54)
	{
		if(!strlen(inputtext))
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Вы не указали текст сообщения!");
			return 1;
		}
		giveplayerid = GetPVarInt(playerid, "PlayerID");
		if(PlayerInfo[giveplayerid][pAdmin] == 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этому человеку нельзя дурить голову! Обращайтесь к администраторам ниже 9 уровня!");
			return 1;
		}
		if(AFK_IdleTime[giveplayerid] >= 3)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Админ в AFK !");
			return 1;
		}
		PlaySoundForPlayer(giveplayerid, SOUND_ROULETTE_NO_CASH);
		format(msgitem, sizeof(msgitem), "Report from {FFFFFF}%s[%d]: {FF0000}%s", PlayerName(playerid), playerid, inputtext);
		//ABroadCast(COLOR_RED,msgitem,1);
		SendClientMessageEx(giveplayerid, COLOR_RED, msgitem);
		SendClientMessage(playerid, COLOR_YELLOW, msgitem);//"Ваш Рапорт был отправлен Админу.");
	}
	//else if(MenuOperation[playerid] == 55)
	//else if(MenuOperation[playerid] == 59)
	return 1;
}


stock InstructorsOnline(playerid)
{
	new dlgitem[1024+12];
	strins(dlgitem, "id \tname \t\t\tlevel \trank\tjob title\n______________________________________________________________________\n", strlen(dlgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] == DoE)
		{
			if(strlen(PlayerName(i)) < 13) format(strings, sizeof(strings), "%d \t%s \t\t%d \t%d \t%s\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], GetPlayerRanks(i));
			else format(strings, sizeof(strings), "%d \t%s \t%d \t%d \t%s\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], GetPlayerRanks(i));
			strins(dlgitem, strings, strlen(dlgitem));
		}
	}
	strins(dlgitem, "\n______________________________________________________________________\n", strlen(dlgitem));
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Instructors Online %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_MSGBOX, "Instructors Online:", dlgitem, "OK", "Назад");
	return 1;
}
stock LawyersOnline(playerid)
{
	new dlgitem[1024+12];
	strins(dlgitem, "id \tname \t\t\tlevel \tskill \tphone\n______________________________________________________________________\n", strlen(dlgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pJob] == LAWYER)
		{
			if(strlen(PlayerName(i)) < 13) format(strings, sizeof(strings), "%d \t%s \t\t%d \t%d \tPh:%d\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pLawSkill], PlayerInfo[i][pPnumber]);
			else format(strings, sizeof(strings), "%d \t%s \t%d \t%d \tPh:%d\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pLawSkill], PlayerInfo[i][pPnumber]);
			strins(dlgitem, strings, strlen(dlgitem));
		}
	}
	strins(dlgitem, "\n______________________________________________________________________\n", strlen(dlgitem));
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Lawyers Online %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_MSGBOX, "Lawyers Online:", dlgitem, "OK", "Назад");
	return 1;
}

stock CarDealerOnline(playerid)
{
	new dlgitem[1024+12];
	strins(dlgitem, "id \tname \t\t\tlevel \tskill \tphone\n_________________________________________________________________\n", strlen(dlgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pJob] == CARDEALER)
		{
			if(strlen(PlayerName(i)) < 13) format(strings, sizeof(strings), "%d \t%s \t\t%d \t%d \tPh:%d\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pCarSkill], PlayerInfo[i][pPnumber]);
			else format(strings, sizeof(strings), "%d \t%s \t%d \t%d \tPh:%d\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pCarSkill], PlayerInfo[i][pPnumber]);
			strins(dlgitem, strings, strlen(dlgitem));
		}
	}
	strins(dlgitem, "\n_________________________________________________________________\n", strlen(dlgitem));
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: CarDealer Online %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_MSGBOX, "CarDealer Online:", dlgitem, "OK", "Назад");
	return 1;
}

stock WomansOnline(playerid)
{
	new dlgitem[512+12];
	strins(dlgitem, "______________________________\nWomans Online:\n",strlen(dlgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pSex] == Female)
		{    //если находим ID игрока у которого параметр pAdmin >0
			if(strlen(PlayerName(i)) < 14) format(strings, sizeof(strings), "%d\t%s\t\t%d\n", i, PlayerName(i), PlayerInfo[i][pLevel]);
			else format(strings, sizeof(strings), "%d\t%s\t%d\n", i, PlayerName(i), PlayerInfo[i][pLevel]);
			strins(dlgitem, strings, strlen(dlgitem), strlen(strings));
		}
	}//DIALOG_STYLE_LIST
	strins(dlgitem, "\n______________________________\n", strlen(dlgitem), 35);
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Womans Online %s[%d], strlen(dlgitem): %d, sizeof(dlgitem): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_MSGBOX, "     id         name                              level", dlgitem, "OK", "Назад");
	return 1;
}

stock ReferalsOnline(playerid)//для рефералов
{
	new dlgitem[512+12];
	strins(dlgitem, "______________________________\nReferals Online:\n",strlen(dlgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(!strcmp(PlayerInfo[i][pReferal], PlayerName(playerid), true)
		|| !strcmp(PlayerInfo[playerid][pReferal], PlayerName(i), true))
		{
			if(strlen(PlayerName(i)) < 14) format(strings, sizeof(strings), "%d\t%s\t\t%d\n", i, PlayerName(i), PlayerInfo[i][pLevel]);
			else format(strings, sizeof(strings), "%d\t%s\t%d\n", i, PlayerName(i), PlayerInfo[i][pLevel]);
			strins(dlgitem, strings, strlen(dlgitem), strlen(strings));
		}
	}//DIALOG_STYLE_LIST
	strins(dlgitem, "\n______________________________\n", strlen(dlgitem), 35);
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Referals Online %s[%d], strlen(dlgitem): %d, sizeof(dlgitem): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKLIST_DIALOG, DIALOG_STYLE_MSGBOX, "     id         name                              level", dlgitem, "OK", "Назад");
	return 1;
}
