



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
		//OOCNews(COLOR_HERBAL, "|_____________________________________ ����������������� ��������� _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}����� � ����: '%s[%d]'.",
			PlayerName(playerid), playerid, ClanInfo[guild][gDiscription], ClanInfo[guild][gID]);
		OOCNews(COLOR_LIGHTBLUE, strings);
		SendClientMessage(playerid, COLOR_GREY, "   ����� �������� ���� (USE: /exitclan)");
	}
	else if(MenuOperation[playerid] == 112)///opencompany
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 64)
	    {
			MenuOperation[playerid] = 112;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "������� ����� ��������(�� ����� 64 ��������).\
\n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			return 1;
	    }
	    if(strfind(inputtext, ".png", true) == -1 && strfind(inputtext, ".jpg", true) == -1)
	    {// ���� � inputtext ����������� ".png"
			MenuOperation[playerid] = 112;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "������� ������ �� �����������.\
\n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			return 1;
	    }
	    new guild = -1;// = guildcounter;

//����� ������ ������
		for(new i = 0; i < MAX_CLANS; i++)
        {   //������� ������ ������� �� �������� �����
        //��������� � ������ ���� �� ������ ��� �����
        	if(ClanInfo[i][gID] == 0)
			{//������� ������ ������� �� �������� �����
				guild = i; break;
			}
        }
        if(guild == -1)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   ���������� ������������ ���-�� ������ �� �������.");
			return 1;
	    }
        SetPVarInt(playerid, "Guild", guild);
	    strmid(ClanInfo[guild][gLogo], inputtext, 0, strlen(inputtext), 64);
		MenuOperation[playerid] = 113;
		ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "������� �������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 113)
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 128)
	    {
			MenuOperation[playerid] = 113;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "������� �������� ����� ��������(�� ����� 128 ��������). \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			return 1;
	    }
	    new guild = GetPVarInt(playerid, "Guild");
	    strmid(ClanInfo[guild][gDiscription], inputtext, 0, strlen(inputtext), 128);
		MenuOperation[playerid] = 114;
		ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "������� ����������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 114)
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 4)
	    {
			MenuOperation[playerid] = 114;
			ShowPlayerDialogEx(playerid, CLANS_DIALOG, DIALOG_STYLE_INPUT, "Create of Company", "������� ����������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			return 1;
	    }

	    new guild = GetPVarInt(playerid, "Guild");
       	if(ClanInfo[guild][gID] != 0)
 	   {
			SendClientMessage(playerid, COLOR_GREY, "   ��������, ������ ���� �����. ��������� ����������� �����.");
			return 1;
        }
	    //ClanInfo[guild][gType] = guild;
	    strmid(ClanInfo[guild][gBrevis], inputtext, 0, strlen(inputtext), 4);
		//---------------------------------------------------------------
		new idx = 1;
		for(new j = 0; j < MAX_CLANS; j++)
		{//������� ��������� ����
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

		OOCNews(COLOR_HERBAL, "|_____________________________________ ����������������� ��������� _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}������ ���� �������� ��� ���������: '%s[%d]'.",
			PlayerName(playerid), playerid, ClanInfo[guild][gDiscription], ClanInfo[guild][gID]);
		OOCNews(COLOR_LIGHTBLUE, strings);
		format(strings, sizeof(strings), "   ����� �������� � ���� (USE: /enterclan [������ �������� �����]).", PlayerName(playerid), playerid, ClanInfo[guild][gDiscription]);
		OOCNews(COLOR_GREY, strings);
		SendClientMessage(playerid, COLOR_GREY, "   ����� ������� �������� (USE: /closecompany).");
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
            SendClientMessage(playerid, COLOR_GREY, "   ������ ����� �� ���������� !");
            return 1;
        }
		PlayerInfo[playerid][pTeam] = ClanInfo[guild][gID];

		GivePlayerMoneyH(fclan+ClanInfo[guild][gID], playerid, -ClanInfo[guild][gEntranceCost]);
		ClanInfo[guild][gTill] += ClanInfo[guild][gEntranceCost];
		OnPlayerStatsUpdate(playerid, 255);

		ClanInfo[guild][gMembers] ++;
		SaveGuildSQL(PlayerName(playerid));
		//OOCNews(COLOR_HERBAL, "|_____________________________________ ����������������� ��������� _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}����� � ����: '%s[%d]'.",
			PlayerName(playerid), playerid, ClanInfo[guild][gDiscription], ClanInfo[guild][gID]);
		OOCNews(COLOR_LIGHTBLUE, strings);
		SendClientMessage(playerid, COLOR_GREY, "   ����� �������� ���� (USE: /exitclan)");
	}
	return 1;
}

