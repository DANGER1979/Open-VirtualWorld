//��� ������
new gInQuestion[MAX_PLAYERS];//���� 1 - �� ������������
new WritingQuestion[MAX_PLAYERS];//1 - �����, 2 - �����������
new TimeQuestioning;//����� �������� ��� ������ �����������
new first_button = 0;//���-�� ����� ��������� ������ ������
new second_button = 0;//[MAX_PLAYERS];
new feeQuest = 0;
new listitem_full = 0;
new listitem0 = 0;
new listitem1 = 0;
new listitem2 = 0;
new listitem3 = 0;
new listitem4 = 0;
new listitem5 = 0;
new listitem6 = 0;
new listitem7 = 0;
new listitem8 = 0;
new listitem9 = 0;
new listitem10 = 0;


enum InfoQuestion
{
	qLine,
	qMaker[MAX_PLAYER_NAME],//20 MAX_PLAYER_NAME
	qStyle,
	qCaption[65],
	//qInfoFull[700 + 48+2],//����� ������� + "� ��� %d ������ �� �������� �������"
	qInfo[718],//700+18
	qInfo0[18],
	qInfo1[70],
	qInfo2[70],
	qInfo3[70],
	qInfo4[70],
	qInfo5[70],
	qInfo6[70],
	qInfo7[70],
	qInfo8[70],
	qInfo9[70],
	qInfo10[70],
	qButton1[10],
	qButton2[10],
	qClose,
	qDays,
	qApprove,
	qStart,
	qEnd
};
new Question[InfoQuestion];//��� ������
new FirstMonday = 6;//����� ������� ������������ � ����
new WritingStep[MAX_PLAYERS]; //Used for onplayertext to see which line he's at


//stock Election()
stock vote_OneHourTimer(playerid)
{//���������� ������ ���, �� ��� ����� Question[qApprove], ������� ��������� ��������� ��� ������ Election_OneDayTimer()
//������
//SendClientMessageToAll(COLOR_RED, "������ ������");
	if(Question[qApprove]) return 1; //SendClientMessage(playerid, COLOR_GREY, "   ��� ����������� (USE: /approve) !");
	new giveplayerid = MAX_PLAYERS-3;
	if(WritingQuestion[giveplayerid] > 0) return 1; //SendClientMessage(playerid, COLOR_GREY, "   ����������� ������ ��� ������ !");
	//----------------------------------------------------------------------
	new MySQLID, playername[MAX_PLAYER_NAME], Score;
	strmid(Question[qMaker], "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	Question[qLine] = 5;//strval(tmp); ���-�� ���������� ����������� ������.
	Question[qStyle] = 2;//strval(tmp);
	Question[qClose] = 0;//strval(nstring);

//������� ���� � ���� ���������� �����������
	new remainder;
	new current_day = getdate();
	do
	{
		remainder = (current_day-(FirstMonday-1))%7;//������� �� ������� �� 7
		current_day++;
	}
	while(remainder != 0);//����� �� ����� ����� remainder ������ == 0

	Question[qDays] = (current_day-1)-getdate();
	Question[qStart] = getdate();
	Question[qEnd] = getdate()+Question[qDays];

	WritingQuestion[giveplayerid] = 2;//�����(1) ��� �����������(2)
	WritingStep[giveplayerid] = 1;//���� ��� ������

	strdel(Question[qCaption], 0, 65);
	strdel(Question[qInfo], 0, 718);
	strdel(Question[qInfo0], 0, 70);
	strdel(Question[qInfo1], 0, 70);
	strdel(Question[qInfo2], 0, 70);
	strdel(Question[qInfo3], 0, 70);
	strdel(Question[qInfo4], 0, 70);
	strdel(Question[qInfo5], 0, 70);
	strdel(Question[qInfo6], 0, 70);
	strdel(Question[qInfo7], 0, 70);
	strdel(Question[qInfo8], 0, 70);
	strdel(Question[qInfo9], 0, 70);
	strdel(Question[qInfo10], 0, 70);
	strdel(Question[qButton1], 0, 10);
	strdel(Question[qButton2], 0, 10);

	strmid(Question[qCaption], "���, �� ������ ������, ������� ����� �����������?", 0, strlen("���, �� ������ ������, ������� ����� �����������?"), 65);//��������� ����
	strmid(Question[qInfo0], "�� �����������", 0, 18, 18);
	strmid(Question[qInfo], "�� �����������\n", 0, 18, 18);
	strmid(Question[qButton1], "OK", 0, strlen("OK"), 10);
	strmid(Question[qButton2], "CANCEL", 0, strlen("CANCEL"), 10);
	
#if defined vw_sql//#endif
	new Field[34];	new idx;
	new ToBase[949];
	format(ToBase, sizeof(ToBase), "SELECT `ID`,`Name`,`Score` FROM `players` WHERE (`ConnectTime`-`Online`)>%d AND `Level`>%d AND `House`<>%d ORDER BY `Score` DESC LIMIT 5", 14, 9, 255);
//���� ������ �� ���� ������ ������ 14 ����� � ������� ���� 9 � ����� � ����
	//mysql_query(ToBase);
	//mysql_store_result();
	new DBResult:db_result = db_query(db_VW,ToBase);
	//if(mysql_num_rows() <= 1)
	if(!db_num_rows(db_result))
	{
		SendClientMessageToAll(COLOR_YELLOW, "������ �� ����������. �������: ���������� ��������� ����������." );
		//mysql_free_result();
		db_free_result(db_result);
		return 1;
	}
	//new Data[56];//10+24+10 + 12�=�56 AND `ConnectTime`>6 AND `Score`>0
	do //while(mysql_fetch_row_format(Data, "|"))
	{
		//if(idx >= 5) break;
		if(WritingStep[giveplayerid] > Question[qLine]) break;
		//mysql_fetch_field_row(Field, "ID"); MySQLID = strval(Field);
		db_get_field_assoc(db_result, "ID", Field, sizeof(Field) );   MySQLID = strval(Field);
		//mysql_fetch_field_row(playername, "Name");
		db_get_field_assoc(db_result, "Name", playername, sizeof(playername)); //strmid(playername, Field, 0, strlen(Field), sizeof(Field));
		//mysql_fetch_field_row(Field, "Score"); Score = strval(Field);
		db_get_field_assoc(db_result, "Score", Field, sizeof(Field) );  Score = strval(Field);

		if(WritingStep[giveplayerid] == 1) strmid(Question[qInfo1], playername, 0, strlen(playername), 24);
		else if(WritingStep[giveplayerid] == 2) strmid(Question[qInfo2], playername, 0, strlen(playername), 24);
		else if(WritingStep[giveplayerid] == 3) strmid(Question[qInfo3], playername, 0, strlen(playername), 24);
		else if(WritingStep[giveplayerid] == 4) strmid(Question[qInfo4], playername, 0, strlen(playername), 24);
		else if(WritingStep[giveplayerid] == 5) strmid(Question[qInfo5], playername, 0, strlen(playername), 24);
		else if(Question[qLine] == 6 && WritingStep[giveplayerid] == 6) strmid(Question[qInfo6], playername, 0, strlen(playername), 24);
		else if(Question[qLine] == 7 && WritingStep[giveplayerid] == 7) strmid(Question[qInfo7], playername, 0, strlen(playername), 24);
		else if(Question[qLine] == 8 && WritingStep[giveplayerid] == 8) strmid(Question[qInfo8], playername, 0, strlen(playername), 24);
		else if(Question[qLine] == 9 && WritingStep[giveplayerid] == 9) strmid(Question[qInfo9], playername, 0, strlen(playername), 24);
		else if(Question[qLine] == 10 && WritingStep[giveplayerid] == 10) strmid(Question[qInfo10], playername, 0, strlen(playername), 24);

		if(WritingStep[giveplayerid] >= 1 && WritingStep[giveplayerid] <= Question[qLine]) format(Question[qInfo], 718, "%s%s\n", Question[qInfo], playername);
		WritingStep[giveplayerid] ++;

		//SendClientMessageToAll(COLOR_YELLOW, "   � ����� ���������� �����������!!!");
		format(strings, sizeof(strings), "%d. ���������� �� ���� �����������: %s[%d]. Score: %d", WritingStep[giveplayerid], playername, MySQLID, Score);
		Log(INVITE,strings);
		SendClientMessageToAll(COLOR_LIGHTBLUE, strings);

		if(WritingStep[giveplayerid] > Question[qLine])
		{//WritingStep[giveplayerid] = 6 > Question[qLine] = 5;
   			if(WritingQuestion[giveplayerid] == 2)
   			{
//������� ������
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		        	PlayerInfo[i][pVote] = 0;
		        }
				//mysql_query("UPDATE `players` SET `Vote`=0");
   				//mysql_query("TRUNCATE `election`");//������� �������
				db_free_result(db_query(db_VW, "UPDATE `players` SET `Vote`=0"));
				db_free_result(db_query(db_VW, "TRUNCATE `election`"));

  				//���������� �����������
   				Question[qApprove] = Question[qDays];//��������� ����, ����� �� ����������� ����� �����������
				SaveVoteSQL();
				//LoadVoteSQL();//����� ���������� �����������
   			}
			WritingQuestion[giveplayerid] = 0;//��������� ����������� ������
			WritingStep[giveplayerid] = 0;
			/*TimeQuestioning = 1;//��������� ������

	       	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				HideDialog(i);
				if(AFK_IdleTime[i] < 3) TogglePlayerControllableEx(i, 0);//�������������
				new qInfoFull[700 + 48+2];
				format(qInfoFull, sizeof(qInfoFull), "%s\n\t\t\t� ��� %d ������ �� �������� ������� !", Question[qInfo], qTime);
				ShowPlayerDialogEx(i, QUESTION2_DIALOG, Question[qStyle],Question[qCaption],qInfoFull,Question[qButton1],Question[qButton2]);
			}*/
		}
		//idx ++;
	}
	while(db_next_row(db_result));
	//mysql_free_result();
	db_free_result(db_result);
#endif
//SendClientMessageToAll(COLOR_GREEN, "������ �����");
	//----------------------------------------------------------------------
	//Update3DTextLabelText(ElectionInfo, 0x0080FFFF, "������������� �������\n{FFFFFF}������� '{0080FF}~k~~VEHICLE_ENTER_EXIT~{FFFFFF}'\n����� ����������");
	return 1;
}
//��� ������� �����

//��� ������ ������
//stock WritingQuestioningText(playerid, const text[])//��� ������ STEP2
stock vote_OnPlayerText(playerid, const text[])//��� ������ STEP2
{	//���������� �� OnPlayerText
	if(!strlen(text))
	{
	    SendClientMessage(playerid, COLOR_RED, "   ���������� ������� �����.");
		return 1;
	}
	//new strings[MAX_STRING];

	new nstring[128];
	format(nstring, sizeof(nstring), "%s", text);//������ ������

	if(WritingStep[playerid] > Question[qLine])
	{   //������ ���������� ������ �������
//��� ����������� STEP3
		if(WritingStep[playerid] == 11)
	    {
			if(strlen(nstring) <= 0 || strlen(nstring) > 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ������������ ���-�� �������� �� ����� 10 !");
				return 1;
			}
	        strmid(Question[qButton1], nstring, 0, strlen(nstring), 10);
	        WritingStep[playerid] ++;
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   ���������� ������� �������� ������ (������) ������ �������.");
	    }
		else if(WritingStep[playerid] == 12)
	    {
			if(strlen(nstring) <= 0 || strlen(nstring) > 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ������������ ���-�� �������� �� ����� 10 !");
				return 1;
			}
	        strmid(Question[qButton2], nstring, 0, strlen(nstring), 10);
	        WritingStep[playerid] ++;
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   ���������� ������� ��� �����������: 0-��������(�������������) ��� 1-��������(USE: /unfreezall).");
	    }
		else if(WritingStep[playerid] == 13)
	    {
			if(strval(nstring) < 0 || strval(nstring) > 1)
			{
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "   ���������� ������� ��� �����������: 0-��������(�������������) ��� 1-��������.");
				return 1;
			}
			Question[qClose] = strval(nstring);

   			if(WritingQuestion[playerid] == 2)
   			{
			   //������� ������

			   	for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		        	PlayerInfo[i][pVote] = 0;
		        }
#if defined vw_sql//#endif
				//mysql_query("UPDATE `players` SET `Vote`=0");
   				//mysql_query("TRUNCATE `election`");//������� �������
				db_free_result(db_query(db_VW, "UPDATE `players` SET `Vote`=0"));
				db_free_result(db_query(db_VW, "TRUNCATE `election`"));
#endif
  				//���������� �����������
   				Question[qApprove] = 1;
				SaveVoteSQL();
				//LoadVoteSQL();//����� ���������� �����������
   			}

			WritingQuestion[playerid] = 0;//��������� ����������� ������
			WritingStep[playerid] = 0;

			TimeQuestioning = 1;//��������� ������

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				HideDialog(i);
				TogglePlayerControllableEx(i, 0);//�������������
				new qInfoFull[700 + 48+2];
				format(qInfoFull, sizeof(qInfoFull), "%s\n\t\t\t� ��� %d ������ �� �������� ������� !", Question[qInfo], qTime);
				ShowPlayerDialogEx(i, QUESTION2_DIALOG, Question[qStyle],Question[qCaption],qInfoFull,Question[qButton1],Question[qButton2]);
			}

		    new payout = 10000*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])/10;
			//GivePlayerMoneyB(1, playerid, payout/2);
			FamilyInfo[SAN][fBank] += payout;
		}
	}
	else
	{   //������ ����������� ����� �������
		//if(Question[qStyle] != 2) return 1;
		if(strlen(text) > 70)
		{
			SendClientMessage(playerid, COLOR_GREY, "   ������������ ���-�� �������� �� ����� 70 !");
			return 1;
		}
	 	//if(	WritingQuestion[playerid] == 2 &&
		// 	WritingStep[playerid] >= 2 && WritingStep[playerid] <= 10)
	 	if(	WritingStep[playerid] >= 1 && WritingStep[playerid] <= 10)
		{
			new playername[MAX_PLAYER_NAME];
			strmid(playername, text, 0, strlen(text), MAX_PLAYER_NAME);
			if(CheckExistPlayer(playerid, playername) == 0)
			{
			    format(strings, sizeof(strings), "CEPBEP: {33AA33}��������, ������� ������ %s ���� � ���� ������.", playername);
    			SendClientMessage(playerid, COLOR_RED, strings);
				return 1;
			}
		}
//��� ����������� STEP2
		//-----------------------------
		if(WritingStep[playerid] == 0)
		{
			if(strlen(nstring) > 65)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ������������ ���-�� �������� �� ����� 65 !");
				return 1;
			}
	        strmid(Question[qCaption], nstring, 0, strlen(nstring), 65);//��������� ����

	        format(strings, sizeof(strings), "   ������ �� ������ �������� ����� ������ �������. �� ����� �������� � ���� ����. ��� �������� %d �����.", Question[qLine]);
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

	        if(WritingQuestion[playerid] == 2)
	        {
	        	//SendClientMessage(playerid, COLOR_RED, "������������: ������ ������� ������ ������������� ���: '�� �����������'");
	        	SendClientMessage(playerid, COLOR_GREY, "   ����� ������ �������� ������� ������� � TAB ��� �������� ����.");
	        }
	        SendClientMessage(playerid, COLOR_GREY, "   ����� ������������ (/n) ��� �������� ������ � (/t) ��� ��������� (���� �������� �� �����)");
		}
		else if(WritingStep[playerid] == 1)
  		{
  			strmid(Question[qInfo0], "�� �����������", 0, 18, 18);
  			strmid(Question[qInfo], "�� �����������\n", 0, 18, 18);
			//strins(Question[qInfo], "�� �����������\n", strlen(Question[qInfo]));

        	strmid(Question[qInfo1], nstring, 0, strlen(nstring), 70);
  			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 2)
  		{
	        strmid(Question[qInfo2], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 3)
	    {
	        strmid(Question[qInfo3], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 4)
	    {
	        strmid(Question[qInfo4], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 5)
	    {
	        strmid(Question[qInfo5], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 6)
	    {
	        strmid(Question[qInfo6], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 7)
	    {
	        strmid(Question[qInfo7], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 8)
	    {
	        strmid(Question[qInfo8], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 9)
	    {
	        strmid(Question[qInfo9], nstring, 0, strlen(nstring), 70);
   			//format(strings, sizeof(strings), "%s\n", nstring);
			//strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		else if(WritingStep[playerid] == 10)
	    {
	        strmid(Question[qInfo10], nstring, 0, strlen(nstring), 70);
	        //format(strings, sizeof(strings), "%s\n", nstring);
	        //strins(Question[qInfo], strings, strlen(Question[qInfo]));
	    }
		if(WritingStep[playerid] >= 1 &&WritingStep[playerid] <= 10) format(Question[qInfo], 718, "%s%s\n", Question[qInfo], nstring);
		WritingStep[playerid] ++;
		if((WritingStep[playerid]-1) > 0 && (WritingStep[playerid]-1) < 10)
		{
			format(strings, sizeof(strings), "   B� �������� ������� ������ �%d.", WritingStep[playerid]-1);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		}
		if(WritingStep[playerid] > Question[qLine])
		{
  			//format(Question[qInfoFull], sizeof(Question[qInfoFull]), "%s\n\t\t\t� ��� %d ������ �� �������� ������� !", Question[qInfo], qTime);
			WritingStep[playerid] = 11;
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   ���������� ������� �������� ������ (�����) ������ �������.");
		}
	}
    return 1;
}

stock vote_OnPlayerClickPlayer(playerid, clickedplayerid)
{
		//new strings[MAX_STRING];
		if(	WritingQuestion[playerid] == 2 &&
			WritingStep[playerid] >= 1 && WritingStep[playerid] <= 10)
		{
			if(WritingStep[playerid] == 1)
	  		{
	  			strmid(Question[qInfo0], "�� �����������", 0, 18, 18);
	  			strmid(Question[qInfo], "�� �����������\n", 0, 18, 18);

	        	strmid(Question[qInfo1], PlayerName(clickedplayerid), 0, 24, 70);
	  			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 2)
	  		{
		        strmid(Question[qInfo2], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 3)
		    {
		        strmid(Question[qInfo3], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 4)
		    {
		        strmid(Question[qInfo4], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 5)
		    {
		        strmid(Question[qInfo5], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 6)
		    {
		        strmid(Question[qInfo6], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 7)
		    {
		        strmid(Question[qInfo7], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 8)
		    {
		        strmid(Question[qInfo8], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 9)
		    {
		        strmid(Question[qInfo9], PlayerName(clickedplayerid), 0, 24, 70);
	   			//format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
				//strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
			else if(WritingStep[playerid] == 10)
		    {
		        strmid(Question[qInfo10], PlayerName(clickedplayerid), 0, 24, 70);
		        //format(strings, sizeof(strings), "%s\n", PlayerName(clickedplayerid));
		        //strins(Question[qInfo], strings, strlen(Question[qInfo]));
		    }
  			if(WritingStep[playerid] >= 1 && WritingStep[playerid] <= 10) format(Question[qInfo], 718, "%s%s\n", Question[qInfo], PlayerName(clickedplayerid));
			WritingStep[playerid] ++;
			if((WritingStep[playerid]-1) > 0 && (WritingStep[playerid]-1) < 10)
			{
				format(strings, sizeof(strings), "   B� �������� ������� ������ �%d.", WritingStep[playerid]-1);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			}
			if(WritingStep[playerid] > Question[qLine])
			{
	  			//format(Question[qInfoFull], sizeof(Question[qInfoFull]), "%s\n\t\t\t� ��� %d ������ �� �������� ������� !", Question[qInfo], qTime);
				WritingStep[playerid] = 11;
		        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   ���������� ������� �������� ������ (�����) ������ �������.");
			}
		}
}

stock vote_OnDialogResponse1(playerid, dialogid, response, listitem, inputtext[])
{
		//#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != QUESTION2_DIALOG) return 1;
		SetPVarInt(playerid, "gShowDialog", -1);
		//new msgitem[256+1];
		//new giveplayerid;
//��� ������ STEP3 //��� ����������� STEP4
//ShowPlayerDialogEx(j,20,Question[qStyle],Question[qCaption],qInfoFull,Question[qButton1],Question[qButton2]);
		TogglePlayerControllableEx(playerid, 1);//�������������
		if(response)
		{
			ClearAnimations(playerid, 1);
		    if(Question[qStyle] == DIALOG_STYLE_MSGBOX && !gInQuestion[playerid])
		    {
				first_button ++;
				gInQuestion[playerid] = 1;
			}
		    else if(Question[qStyle] == DIALOG_STYLE_INPUT && !gInQuestion[playerid])
		    {
				new money = strval(inputtext);
				if(money < 1 || money > 1000000)
				{
					SendClientMessage(playerid, COLOR_GREY, "   �������� ������ ���� �� 1 �� 1000000");
					//new qInfoFull[700 + 48+2];
					//format(qInfoFull, sizeof(qInfoFull), "%s\n\t\t\t� ��� %d ������ �� �������� ������� !", Question[qInfo], qTime);
					ShowPlayerDialogEx(playerid, QUESTION2_DIALOG, Question[qStyle], Question[qCaption], Question[qInfo], Question[qButton1], Question[qButton2]);
					return 1;
				}
				gInQuestion[playerid] = 1;
				feeQuest += money;
			}
		    else if(Question[qStyle] == DIALOG_STYLE_LIST && !gInQuestion[playerid])
		    {
				if(listitem == 0) listitem0 ++;
				else if(listitem == 1) listitem1 ++;
				else if(listitem == 2) listitem2 ++;
				else if(listitem == 3) listitem3 ++;
				else if(listitem == 4) listitem4 ++;
				else if(listitem == 5) listitem5 ++;
				else if(listitem == 6) listitem6 ++;
				else if(listitem == 7) listitem7 ++;
				else if(listitem == 8) listitem8 ++;
				else if(listitem == 9) listitem9 ++;
				else if(listitem == 10) listitem10 ++;
				gInQuestion[playerid] = 1;
			}
		}
		else
		{
		    if(Question[qStyle] == DIALOG_STYLE_MSGBOX && !gInQuestion[playerid])
		    {
				second_button ++;
				gInQuestion[playerid] = 1;
			}
		    else if(Question[qStyle] == DIALOG_STYLE_INPUT && !gInQuestion[playerid])
			{
				gInQuestion[playerid] = 0;
			}
		    else if(Question[qStyle] == DIALOG_STYLE_LIST && !gInQuestion[playerid])
		    {
				gInQuestion[playerid] = 0;
			}
		}
		return 1;
}

//stock QuestioningTimer()//��� ������ STEP4 //��� ����������� STEP5
stock vote_OneSecondTimers(playerid)
{   //���������� �� ���������� �������
	TimeQuestioning ++;
    if(TimeQuestioning < qTime) return 1;

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(gInQuestion[i] && AFK_IdleTime[i] < 3)//���� ����� ��������� � ������
		{   //���������� ���� ���������� ������
	    	new dlgitem[1024];
	    	if(Question[qStyle] == DIALOG_STYLE_MSGBOX)
	    	{
				format(dlgitem, sizeof(dlgitem), "�����:\n%s - \t\t\t%d �������\n%s - \t\t\t%d �������\n����� �������:\t%d",
					Question[qButton1], first_button, Question[qButton2], second_button, (first_button+second_button));
			}
	    	else if(Question[qStyle] == DIALOG_STYLE_INPUT)
   			{
				//new qInfoFull[700 + 48+2];
				format(dlgitem, sizeof(dlgitem), "�����: \n%s\n\t\t\t%d", Question[qInfo], feeQuest);
				//format(dlgitem, sizeof(dlgitem), "�����: \n%s\n\t\t\t%d", Question[qInfoFull], feeQuest);
			}
	    	else if(Question[qStyle] == DIALOG_STYLE_LIST)
	    	{
				listitem_full = listitem1+listitem2+listitem3+listitem4+listitem5+listitem6+listitem7+listitem8+listitem9+listitem10;
				//listitem0 - �� ������������
				format(dlgitem, sizeof(dlgitem),
					"�����:\
					\n%s - \t\t%d �������\n",Question[qInfo1], listitem1);
				if(Question[qLine] >= 2) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo2], listitem2);
				if(Question[qLine] >= 3) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo3], listitem3);
				if(Question[qLine] >= 4) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo4], listitem4);
				if(Question[qLine] >= 5) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\nd", dlgitem, Question[qInfo5], listitem5);
				if(Question[qLine] >= 6) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo6], listitem6);
				if(Question[qLine] >= 7) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo7], listitem7);
				if(Question[qLine] >= 8) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo8], listitem8);
				if(Question[qLine] >= 9) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo9], listitem9);
				if(Question[qLine] >= 10) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d �������\n", dlgitem, Question[qInfo10], listitem10);
				format(dlgitem, sizeof(dlgitem), "%s\n����� �������:\t%d", dlgitem, listitem_full);
			}
			HideDialog(i);
			TogglePlayerControllableEx(i, 0);//�������������
	        if(Question[qClose] == 0)
	        {
				ShowPlayerDialogEx(i, QUESTION2_DIALOG, DIALOG_STYLE_MSGBOX, Question[qCaption],dlgitem, "OK", "Cancel");
			}
			else if(Question[qClose] == 1 && !strcmp(Question[qMaker], PlayerName(i), true))
			{   //���� ��������, �� ���������� ������ ���������
				ShowPlayerDialogGap(i, QUESTION2_DIALOG, DIALOG_STYLE_MSGBOX, Question[qCaption],dlgitem, "OK", "Cancel");
			}
			gInQuestion[i] = 0;
		}
		else// if(!gInQuestion[i])
		{   //���� ����� �� ��������� �� ������� ��� ��� ������ ���� ��������
			HideDialog(i);
		}
	}
	first_button = 0;
	second_button = 0;
	feeQuest = 0;
	listitem0 = 0;
	listitem1 = 0;
	listitem2 = 0;
	listitem3 = 0;
	listitem4 = 0;
	listitem5 = 0;
	listitem6 = 0;
	listitem7 = 0;
	listitem8 = 0;
	listitem9 = 0;
	listitem10 = 0;
	TimeQuestioning = 0;
	return 1;
}



//stock Question1(playerid)
stock vote_OnPlayerKeyStateChange(playerid)
{
   	if( !IsPlayerInRangeOfPoint(playerid, 1.3, 381.1362,177.6035,1008.2974) ) return 1;
//��� �������
   	if(//PlayerInfo[playerid][pConnectTime] >= 20 && //PlayerInfo[playerid][pLevel] >= 3 &&
   		PlayerInfo[playerid][pConnectTime] >= (OnlineRecord*20/100) &&
		PlayerInfo[playerid][pVote] == 0 &&
		getdate() >= Question[qStart] && getdate() <= Question[qEnd])
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "������������� ������� �1: � ������ ������ ���������� �����������. ��� ��������� ���� ������ !");
		ShowPlayerDialogEx(playerid, QUESTION1_DIALOG,Question[qStyle],Question[qCaption],Question[qInfo],Question[qButton1],Question[qButton2]);
		//return 1;
	}
	else
	{
		if( PlayerInfo[playerid][pConnectTime] < (OnlineRecord*20/100))
		{
			format(strings, sizeof(strings), "   ��������� ������� � ����������� ����� ���� �������� �� ������� ������ %d �����.", (OnlineRecord*20/100));
			SendClientMessage(playerid, COLOR_GREY, strings);
		}
 		if( PlayerInfo[playerid][pVote] == 1)
 		{
				SendClientMessage(playerid, COLOR_GREY, "   �� ��� �������������.");
		}
		MenuOperation[playerid] = 4;
		format(strings, sizeof(strings), "� ��� �� �����: $%d\
\n������� ����� �������������. \
\n\n\t{8CAA63}�� ��������� ����� ������� OK.", PlayerInfo[playerid][pBank]);
		ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "BANK: ������ �����", strings, "OK", "Cancel");
	}
	return 1;
}
stock vote_OnDialogResponse2(playerid, dialogid, response, listitem, inputtext[])
{
			//#pragma unused listitem
			#pragma unused inputtext
			if(dialogid != QUESTION1_DIALOG) return 1;//��� ����������� STEP7
			SetPVarInt(playerid, "gShowDialog", -1);
			if(!response) { return 1; }
			new msgitem[256+1];
			//new giveplayerid;
//ShowPlayerDialogEx(playerid, QUESTION1_DIALOG,Question[qStyle],Question[qCaption],Question[qInfo],Question[qButton1],Question[qButton2]);
//"������������� ������� �1"
//��� ������ STEP6
 			if(	//PlayerInfo[playerid][pLevel] < 3 ||
			 	PlayerInfo[playerid][pConnectTime] < (OnlineRecord*20/100))
 			{
 				format(msgitem, sizeof(msgitem), "   ��������� ������� � ����������� ����� ���� �������� �� ������� ������ %d �����.", (OnlineRecord*20/100));
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
 			if(PlayerInfo[playerid][pVote] != 0)
 			{
				SendClientMessage(playerid, COLOR_GREY, "   �� ��� ����������!");
				return 1;
			}
			new forplayername[MAX_PLAYER_NAME];
 			if(listitem == 0)
			{
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "�� ���������� �� ������� � �����������, �� ������ ������������� �����!");
				return 1;
			}
 			else if(listitem == 1)
 			{
				PlayerInfo[playerid][pVote] = 1;
				strmid(forplayername, Question[qInfo1], 0, MAX_PLAYER_NAME, 70);
			}
 			else if(listitem == 2)
 			{
				PlayerInfo[playerid][pVote] = 2;
				strmid(forplayername, Question[qInfo2], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 3)
 			{
				PlayerInfo[playerid][pVote] = 3;
				strmid(forplayername, Question[qInfo3], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 4)
 			{
				PlayerInfo[playerid][pVote] = 4;
				strmid(forplayername, Question[qInfo4], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 5)
 			{
				PlayerInfo[playerid][pVote] = 5;
				strmid(forplayername, Question[qInfo5], 0, MAX_PLAYER_NAME, 70);
			}
 			else if(listitem == 6)
 			{
				PlayerInfo[playerid][pVote] = 6;
				strmid(forplayername, Question[qInfo6], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 7)
 			{
				PlayerInfo[playerid][pVote] = 7;
				strmid(forplayername, Question[qInfo7], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 8)
 			{
				PlayerInfo[playerid][pVote] = 8;
				strmid(forplayername, Question[qInfo8], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 9)
 			{
				PlayerInfo[playerid][pVote] = 9;
				strmid(forplayername, Question[qInfo9], 0, MAX_PLAYER_NAME, 70);
 			}
 			else if(listitem == 10)
 			{
				PlayerInfo[playerid][pVote] = 10;
				strmid(forplayername, Question[qInfo10], 0, MAX_PLAYER_NAME, 70);
 			}
#if defined vw_sql//#endif
			new date[12], time[10];
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			new ly, lmm, ld;	getdate(ly,lmm,ld);
			format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
			format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);
			new ToBase[94 + 12+10 + 24 + 70 + 12];
			format(ToBase, sizeof(ToBase),
				"INSERT INTO `election` (`Date`,`Time`, `Constituent`, `Candidate`) VALUES ('%s', '%s', '%s', '%s')",
				date, time, PlayerName(playerid), forplayername);
			//mysql_query(ToBase);
			db_free_result(db_query(db_VW, ToBase));
#endif
			format(msgitem, sizeof(msgitem), "�������! ��� ����� �� %s'� ������!", forplayername);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);

			return 1;
}

