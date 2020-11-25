



stock clans_OnGameModeInit()
{
	LoadClansSQL();
	return 1;
}


stock clans_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	if(dialogid != CLANS_DIALOG) return 1;
	if(!response)
	{
		Offer[playerid] = MAX_PLAYERS-1;
		MenuOperation[playerid] = 0;
		return 1;
	}
	new msgitem[256+1];
	if(MenuOperation[playerid] == 1)
	{
		///new msgitem[256+1];
		new giveplayerid = Offer[playerid];
	//ShowPlayerDialogGap(playerid, INVITE2_DIALOG, DIALOG_STYLE_MSGBOX, "Invite", msgitem, "Accept", "Cancel");
		//if(MenuOperation[playerid] != 111) return 1;
		new guild = PlayerInfo[giveplayerid][pTeam];//SelectCharID[playerid];

		PlayerInfo[playerid][pTeam] = ClanInfo[guild][gID];

		GivePlayerMoneyH(fclan+ClanInfo[guild][gID], playerid, -ClanInfo[guild][gEntranceCost]);
		ClanInfo[guild][gTill] += ClanInfo[guild][gEntranceCost];
		OnPlayerStatsUpdate(playerid, 255);

		ClanInfo[guild][gMembers] ++;
		SaveGuildSQL(PlayerName(playerid));
		//OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}вошёл в клан: '%s[%d]'.",
			PlayerName(playerid), playerid, ClanInfo[guild][gDiscription], ClanInfo[guild][gID]);
		OOCNews(COLOR_LIGHTBLUE, strings);
		SendClientMessage(playerid, COLOR_GREY, "   Чтобы покинуть клан (USE: /exitclan)");
	}
	else if(MenuOperation[playerid] == 112)///opencompany
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 64)
	    {
			MenuOperation[playerid] = 112;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "Введите адрес логотипа(не более 64 символов).\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
	    }
	    if(strfind(inputtext, ".png", true) == -1 && strfind(inputtext, ".jpg", true) == -1)
	    {// если в inputtext отсутствует ".png"
			MenuOperation[playerid] = 112;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "Введите ссылку на изображение.\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
	    }
	    new guild = -1;// = guildcounter;

//самый важный момент
		for(new i = 0; i < MAX_CLANS; i++)
        {   //находим индекс первого не занятого клана
        //проверяем в списке нету ли такого уже клана
        	if(ClanInfo[i][gID] == 0)
			{//находим индекс первого не занятого клана
				guild = i; break;
			}
        }
        if(guild == -1)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Достигнуто максимальное кол-во кланов на сервере.");
			return 1;
	    }
        SetPVarInt(playerid, "Guild", guild);
	    strmid(ClanInfo[guild][gLogo], inputtext, 0, strlen(inputtext), 64);
		MenuOperation[playerid] = 113;
		ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "Введите название вашей компании. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 113)
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 128)
	    {
			MenuOperation[playerid] = 113;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "Введите название вашей компании(не более 128 символов). \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
	    }
	    new guild = GetPVarInt(playerid, "Guild");
	    strmid(ClanInfo[guild][gDiscription], inputtext, 0, strlen(inputtext), 128);
		MenuOperation[playerid] = 114;
		ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "Введите абривиатуру вашей компании. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 114)
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 4)
	    {
			MenuOperation[playerid] = 114;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "Введите абривиатуру вашей компании. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
	    }

	    new guild = GetPVarInt(playerid, "Guild");
       	if(ClanInfo[guild][gID] != 0)
 	   {
			SendClientMessage(playerid, COLOR_GREY, "   Извените, данный клан занят. Повторите регистрацию клана.");
			return 1;
        }
	    //ClanInfo[guild][gType] = guild;
	    strmid(ClanInfo[guild][gBrevis], inputtext, 0, strlen(inputtext), 4);
		//---------------------------------------------------------------
		new idx = 1;
		for(new j = 0; j < MAX_CLANS; j++)
		{//находим свободный клан
	       	if(ClanInfo[j][gID] == idx)
	      	{
	      		//printf("continue gID: %d", ClanInfo[j][gID]);
	      		idx++;
	       	    continue;
	       	}
		}
		ClanInfo[guild][gID] = idx;
		//---------------------------------------------------------------
		strmid(ClanInfo[guild][gOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		PlayerInfo[playerid][pTeam] = ClanInfo[guild][gID];
		OnPlayerStatsUpdate(playerid, 255);

	    format(msgitem, sizeof(msgitem), "Welcome to %s", ClanInfo[guild][gBrevis]);
		strmid(ClanInfo[guild][gMOTD], msgitem, 0, strlen(msgitem), 128);

		ClanInfo[guild][gMembers] = 1;
   		GetPlayerPos(playerid, ClanInfo[guild][gSpawns][0],ClanInfo[guild][gSpawns][1],ClanInfo[guild][gSpawns][2]);
   		GetPlayerFacingAngle(playerid, ClanInfo[guild][gSpawns][3]);
	    ClanInfo[guild][gInterior] = PlayerInfo[playerid][pInt];
	    ClanInfo[guild][gWorld] = PlayerInfo[playerid][pVirtual];
	    ClanInfo[guild][gLocal] = PlayerInfo[playerid][pLocal];

	    ClanInfo[guild][gBuyPrice] += 10000;
	    ClanInfo[guild][gEntranceCost] = 10000;
	    ClanInfo[guild][gProducts] = 100;
	    ClanInfo[guild][gBuyProd] = 1;
		ClanInfo[guild][gSellProd] = 10;

		ClanInfo[guild][gTill] += ClanInfo[guild][gEntranceCost];
		GivePlayerMoneyB(fclan+ClanInfo[guild][gID], playerid, -ClanInfo[guild][gEntranceCost]);
		ClanInfo[guild][gDate] = getdate();
		ClanInfo[guild][gInkas] += ClanInfo[guild][gEntranceCost];
		AddGuildSQL(guild);

		OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}открыл свою компанию под названием: '%s[%d]'.",
			PlayerName(playerid), playerid, ClanInfo[guild][gDiscription], ClanInfo[guild][gID]);
		OOCNews(COLOR_LIGHTBLUE, strings);
		format(strings, sizeof(strings), "   Чтобы вступить в клан (USE: /enterclan [точное название клана]).", PlayerName(playerid), playerid, ClanInfo[guild][gDiscription]);
		OOCNews(COLOR_GREY, strings);
		SendClientMessage(playerid, COLOR_GREY, "   Чтобы закрыть компанию (USE: /closecompany).");
	}
	else if(MenuOperation[playerid] == 115)
	{//	/enterclan
		//if(guildcounter >= MAX_CLANS)
		new guild = -1;
		for(new g=0; g<MAX_CLANS; g++)
		{
			if(ClanInfo[g][gID] == 0) continue;
			if( !strcmp(ClanInfo[g][gDiscription], inputtext, true) )
		    {
	            guild = g;
		    }
		}
   	 	if(guild == -1)
	    {
            SendClientMessage(playerid, COLOR_GREY, "   Такого клана не обнаружено !");
            return 1;
        }
		PlayerInfo[playerid][pTeam] = ClanInfo[guild][gID];

		GivePlayerMoneyH(fclan+ClanInfo[guild][gID], playerid, -ClanInfo[guild][gEntranceCost]);
		ClanInfo[guild][gTill] += ClanInfo[guild][gEntranceCost];
		OnPlayerStatsUpdate(playerid, 255);

		ClanInfo[guild][gMembers] ++;
		SaveGuildSQL(PlayerName(playerid));
		//OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}вошёл в клан: '%s[%d]'.",
			PlayerName(playerid), playerid, ClanInfo[guild][gDiscription], ClanInfo[guild][gID]);
		OOCNews(COLOR_LIGHTBLUE, strings);
		SendClientMessage(playerid, COLOR_GREY, "   Чтобы покинуть клан (USE: /exitclan)");
	}
	return 1;
}

