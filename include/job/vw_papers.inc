//��� ���������
new PaperPrice[MAX_PLAYERS];
new BringingPaper[MAX_PLAYERS];//����� ���� ���� ���������� ������
new TakePaper[MAX_PLAYERS];
new GotPaper[MAX_PLAYERS];//������ ������� //������ ��� ���� ������ //The player has a paper so he can use /read
new WritingPaper[MAX_PLAYERS]; //Used for onplayertext so he can type in lines
new WritingPaperNumber[MAX_PLAYERS]; //To which Paper in PaperInfo will it be written

new TalkingLive[MAX_PLAYERS];//���������� �� �� ����������� ���� ��



enum pPaper
{
	pMaker[MAX_PLAYER_NAME],//20 MAX_PLAYER_NAME
	pTitle[32],
	pLine1[70],
	pLine2[70],
	pLine3[70],
	pLine4[70],
	pLine5[70],
	pLine6[70],
	pLine7[70],
	pLine8[70],
	pLine9[70],
	pLine10[70],
	pLine11[70],
	pDate,//���� ���������
};
new Paper[MAX_PLAYERS][pPaper];//��� ����� ������ � �������


//��� ��������
stock LoadPapers()//��� ����� ���������� �� OnGameModeInit
{
	new time = GetTickCount();
	new File: pFile = fopen("Logs/papers.cfg", io_read);//io_readwrite
	if(pFile)
	{
		new arrCoords[15][70];
		new strFromFile[2+24+32+70*11+3 + 12];//1478
		for(new idx=0; idx<PAPERLINE; idx++)
		{
			fread(pFile, strFromFile);
			split(strFromFile, arrCoords, '|');
			PaperInfo[idx][PaperUsed] = strval(arrCoords[0]);
			strmid(PaperInfo[idx][PaperMaker], arrCoords[1], 0, strlen(arrCoords[1]), 70);
			strmid(PaperInfo[idx][PaperTitle], arrCoords[2], 0, strlen(arrCoords[2]), 70);
			strmid(PaperInfo[idx][PaperText1], arrCoords[3], 0, strlen(arrCoords[3]), 70);
			strmid(PaperInfo[idx][PaperText2], arrCoords[4], 0, strlen(arrCoords[4]), 70);
			strmid(PaperInfo[idx][PaperText3], arrCoords[5], 0, strlen(arrCoords[5]), 70);
			strmid(PaperInfo[idx][PaperText4], arrCoords[6], 0, strlen(arrCoords[6]), 70);
			strmid(PaperInfo[idx][PaperText5], arrCoords[7], 0, strlen(arrCoords[7]), 70);
			strmid(PaperInfo[idx][PaperText6], arrCoords[8], 0, strlen(arrCoords[8]), 70);
			strmid(PaperInfo[idx][PaperText7], arrCoords[9], 0, strlen(arrCoords[9]), 70);
			strmid(PaperInfo[idx][PaperText8], arrCoords[10], 0, strlen(arrCoords[10]), 70);
			strmid(PaperInfo[idx][PaperText9], arrCoords[11], 0, strlen(arrCoords[11]), 70);
			strmid(PaperInfo[idx][PaperText10], arrCoords[12], 0, strlen(arrCoords[12]), 70);
			strmid(PaperInfo[idx][PaperText11], arrCoords[13], 0, strlen(arrCoords[13]), 70);
			PaperInfo[idx][PaperDate] = strval(arrCoords[14]);//��������� �������� �� �����������
//printf("Paper:%d Used:%d Maker:%s",idx+1,PaperInfo[idx][PaperUsed],PaperInfo[idx][PaperMaker]);
		}
		fclose(pFile);
	}
	printf("13/17. [�������� �����]: ���� ��������� - %d, ��������� - %d (ms)", PAPERLINE, (GetTickCount()-time));
}
stock SavePapers()//��� ����� ����������� ��� �������� ������� ������ � ��� � �-�� OnPlayerText
{
	new File: pFile = fopen("Logs/papers.cfg", io_write);
	if(pFile)
	{
		//new idx;
		//while(idx < PAPERLINE)
		for(new idx=0; idx<PAPERLINE; idx++)
		{
			new coordsstring[47 + 2+24+32+70*11+3];//1478
			format(coordsstring, sizeof(coordsstring), "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%d\n",
			PaperInfo[idx][PaperUsed],
			PaperInfo[idx][PaperMaker],
			PaperInfo[idx][PaperTitle],
			PaperInfo[idx][PaperText1],
			PaperInfo[idx][PaperText2],
			PaperInfo[idx][PaperText3],
			PaperInfo[idx][PaperText4],
			PaperInfo[idx][PaperText5],
			PaperInfo[idx][PaperText6],
			PaperInfo[idx][PaperText7],
			PaperInfo[idx][PaperText8],
			PaperInfo[idx][PaperText9],
			PaperInfo[idx][PaperText10],
			PaperInfo[idx][PaperText11],
			PaperInfo[idx][PaperDate]);
			//fwrite(hFile, coordsstring);
		    for(new c=0; c<strlen(coordsstring); c++)
			{   //��������� �� �������� ������� �� ����� ������
		        fputchar(pFile, coordsstring[c], false);
		    }
			//idx ++;
		}
		fclose(pFile);
	}
	//��������������
	//SendAllAdminMessage( COLOR_RESTARTING, "���������� ����� ������� ���������", 1);
	SendFamilyMessage(SAN, "���������� ����� ������� ���������");
}

stock ClearPaper(paper)//���������� �� ������� /paper delete
{
    new strtmp[8];//MAX_PLAYER_NAME
	format(strtmp, sizeof(strtmp), "None");
	PaperInfo[paper][PaperUsed] = 0;
	strmid(PaperInfo[paper][PaperMaker], strtmp, 0, strlen(strtmp), MAX_PLAYER_NAME);
	strmid(PaperInfo[paper][PaperTitle], strtmp, 0, strlen(strtmp), 32);
	strmid(PaperInfo[paper][PaperText1], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText2], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText3], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText4], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText5], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText6], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText7], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText8], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText9], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText10], strtmp, 0, strlen(strtmp), 70);
	strmid(PaperInfo[paper][PaperText11], strtmp, 0, strlen(strtmp), 70);
	PaperInfo[paper][PaperDate] = 0;
}

//==============================================================================
stock paperboy_OnPlayerConnect(playerid)
{
//��� ���������
	PaperPrice[playerid] = 0;//Offer[playerid] = MAX_PLAYERS-1;
	BringingPaper[playerid] = 0; TakePaper[playerid] = 0; GotPaper[playerid] = 0;
	WritingPaper[playerid] = 0; WritingPaperNumber[playerid] = MAX_PAPERNUMBER; WritingStep[playerid] = 0;
	TalkingLive[playerid] = MAX_PLAYERS-1;//Offer[playerid] = MAX_PLAYERS-1;
	WritingQuestion[playerid] = 0;
	gInQuestion[playerid] = 0;
	
}
	
stock paperboy_OnEnterCheckpoint(playerid)
{
	//--------------------------------------------------------------------------
	if(CP[playerid] == CP_PAPERBOY && PlayerInfo[playerid][pJob] == PAPERBOY)//��� ������� //���� �� ������� ������ �������
	{   //������� �� �����
		if(	PlayerInfo[playerid][pCarTime] > 0 &&
			PlayerInfo[playerid][pVirtual] == 0 &&
			PlayerInfo[playerid][pLocal] == FREEROAM)
		{   //���� ����� ��� �� �����������, �.�. �� ������ �� �����
			/*if(	PlayerInfo[playerid][pVirtual] == 0 &&
				PlayerInfo[playerid][pLocal] == FREEROAM)
			{*/

  			//if(GetTickCount() < (checktimedeliver[playerid]+CallTime[playerid]*1000) && !gAnticheat[playerid])
			/*if(GetTickCount() < (checktimedeliver[playerid]+MinTimeCheckpoint[playerid]) && !gAnticheat[playerid])
  			{
				format(strings, sizeof(strings), "%s[%d] Reset CourierSkill:%d checktimedeliver:%d[%d] sec",
					PlayerName(playerid),playerid, PlayerInfo[playerid][pCourierSkill],
					(GetTickCount()-checktimedeliver[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
				Log(JOB, strings);

				//CP[playerid] = 0;
				PlayerInfo[playerid][pCourierSkill] = 0;
				CallTime[playerid] = 0;
				SendClientMessage(playerid, COLOR_GREY, strings);
				return 1;
   			}*/
			/*format(strings, sizeof(strings), "%s[%d] CourierSkill:%d checktimedeliver:%d[%d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pCourierSkill], (GetTickCount()-checktimedeliver[playerid])/1000, CallTime[playerid]);
			Log(JOB, strings);*/

			new money;
		   	if(PlayerInfo[playerid][pCourierSkill] < (1000-5)) PlayerInfo[playerid][pCourierSkill] += 5;//��������� ������� ����. ������ ������������ ������
			new level = PlayerInfo[playerid][pCourierSkill];
			if(level <= 50)//���� ����� �������� 1 / 49-�� ������
			{
			    money = (100 + random(300));
				if(level == 50)//���� ����� �������� 50 ������ �� ����������� �� ��������� ������� 2
				{
					new Fee = (200 + random(300))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee); SBizInfo[7][sbTill] -= Fee;
			    	format(strings, sizeof(strings), "B�� ����� ������� ������ 2 ! ������� %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ������ ��������� $200-500 �� �������� �����.");
				}
			}
			else if(level > 50 && level <= 100)//2 �������
			{
			    money = (200 + random(300));
				if(level == 100)
				{
					new Fee = (300 + random(300))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee); SBizInfo[7][sbTill] -= Fee;
			    	format(strings, sizeof(strings), "B�� ����� ������� ������ 3 ! ������� %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ��������� $300-600 �� �������� �����.");
				}
			}
			else if(level > 100 && level <= 200)//3 �������
			{
			    money = (300 + random(300));
				if(level == 200)
				{
				    new Fee = (400 + random(300))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee); SBizInfo[7][sbTill] -= Fee;
			    	format(strings, sizeof(strings), "B�� ����� ������� ������ 4 ! ������� %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ��������� $400-700 �� �������� �����.");
				}
			}
			else if(level > 200 && level <= 400)//4 �������
			{
			    money = (400 + random(300));
				if(level == 400)
				{
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, RANDMONEY5*10); SBizInfo[7][sbTill] -= RANDMONEY5*10;
			    	format(strings, sizeof(strings), "B�� ����� ������� ������ 5 ! ������� %d$.", RANDMONEY5*10);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ��������� $600 �� �������� �����.");
				}
			}
			else if(level > 400)//5 �������
			{
			    money = RANDMONEY5;
			}
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			SBizInfo[7][sbTill] -= money;
			//SBizInfo[7][sbImport] += money;
			
			//OnGangsExtortionSBiz(7, SBizInfo[7][sbEntranceCost]);
			//SBizInfo[7][sbProducts] --;

			HouseInfo[BringingPaper[playerid]-1][hPaper] = TakePaper[playerid];
			//}
		}
		else //���� ����� �����
		{
	   		if(PlayerInfo[playerid][pCourierSkill] < 400)
	   		{
	  			if(PlayerInfo[playerid][pCourierSkill] >= 10) PlayerInfo[playerid][pCourierSkill] -= 10;//��������� ������� ����. ������
				if(PlayerInfo[playerid][pCourierSkill] == 49)//���� ����� �������� 50 ������ �� ����������� �� ��������� ������� 2
				{
					SendClientMessage(playerid, COLOR_GREEN, "��� ����� ������� ������ 1, �� ��������� $100-400 �� �������� ����� � ������� 20 �����.");
				}
				if(PlayerInfo[playerid][pCourierSkill] == 99)
				{
					SendClientMessage(playerid, COLOR_GREEN, "��� ����� ������� ������ 2, �� ��������� $200-500 �� �������� ����� � ������� 18 �����.");
				}
				if(PlayerInfo[playerid][pCourierSkill] == 199)
				{
					SendClientMessage(playerid, COLOR_GREEN, "��� ����� ������� ������ 3, �� ��������� $300-600 �� �������� ����� � ������� 16 �����.");
				}
				if(PlayerInfo[playerid][pCourierSkill] == 399)
				{
					SendClientMessage(playerid, COLOR_GREEN, "��� ����� ������� ������ 4, �� ��������� $400-700  �� �������� ����� � ������� 14 �����.");
				}
				SendClientMessage(playerid, COLOR_GREEN, "P�����������: {0080FF}�� �� ��������� � ��������� ����� ! ��� ����� ������� ������� !");
			}
			GameTextForPlayerEx(playerid, "~w~Paper Delivery~n~~r~Shipment is Not Delivered", 2500, 1);
		}
		TakePaper[playerid] = 0;
		BringingPaper[playerid] = 0;//��� ������
		PlaySoundForPlayer(playerid, SOUND_RACE_GO);//���� ����� ������� �����
	    PlayerInfo[playerid][pCarTime] = 0;//�������� ����� ������� - ���������� ������

		gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);

	    DisablePlayerCheckpointEx(playerid);//������ ��������
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.9 ", GetTickCount(), timers);
	}//��� �������� �����
	return 1;
}

stock paperboy_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != NEWS_DIALOG) return 1;
		
		//new msgitem[256+1];
		new giveplayerid;
//ShowPlayerDialogEx(playerid, 19, DIALOG_STYLE_LIST, "Role Play - "#HostName": Newspaper", listitems, "YES", "NO");
		if(response)
		{
			if(GotPaper[playerid] && Offer[playerid] < MAX_PLAYERS-1)
			{
			    giveplayerid = Offer[playerid];
				if(PlayerInfo[giveplayerid][pCourierSkill] < (1000-2)) PlayerInfo[giveplayerid][pCourierSkill] += 2;
				if(PlayerInfo[giveplayerid][pCourierSkill] == 50)
				{ SendClientMessage(giveplayerid, COLOR_GREEN, "* ��� ����� ������� ������ ������ 2."); }
				else if(PlayerInfo[giveplayerid][pCourierSkill] == 100)
				{ SendClientMessage(giveplayerid, COLOR_YELLOW, "* ��� ����� ������� ������ ������ 3."); }
				else if(PlayerInfo[giveplayerid][pCourierSkill] == 200)
				{ SendClientMessage(giveplayerid, COLOR_YELLOW, "* ��� ����� ������� ������ ������ 4."); }
				else if(PlayerInfo[giveplayerid][pCourierSkill] == 400)
				{ SendClientMessage(giveplayerid, COLOR_YELLOW, "* ��� ����� ������� ������ ������ 5."); }
				//GotPaper[playerid] = 0;
				Offer[playerid] = MAX_PLAYERS-1;
			}
		}
		else
		{
			if(GotPaper[playerid] && Offer[playerid] < MAX_PLAYERS-1)
			{   //Role Play - "#HostName": Newspaper
				GotPaper[playerid] = 0;
				Offer[playerid] = MAX_PLAYERS-1;
			}
			else
			{
			    help_OnPlayerKeyStateChange(playerid);
			}

		}
		return 1;
}
