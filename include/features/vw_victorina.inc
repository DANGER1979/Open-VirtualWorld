//��� ���������
#define MAX_QUESTION 202
new MaxQuestions = 100;//��������� ��������, ��� �������� ����������������
enum QInfo
{
	qQuestion[128],
	qAnswer[64],
};
new QuestInfo[MAX_QUESTION][QInfo];
new ThinkTime = 230;//����� ��� �����������
new QuestCounter = 230;//������
new gQuestStarted = -1;//���������� ������ ���������, 1..-�����  ��� 0-�����
//new gQuestPlayerStarted[MAX_PLAYERS];
new NowQuestion;//����� �������� ������� �� �������



//��� ��������� ������
stock LoadQuests()
{
	if(fexist("Quest.ini"))
	{
		new File: file = fopen("Quest.ini", io_read);
		new strFromFile[256+1];
		//new arrCoords[2][128];
		new idx, index;
		while( fread(file, strFromFile, sizeof(strFromFile)) )
		{
			index = 0;
			//trimSideSpaces(strFromFile);//������� ��������
			//split(strFromFile, arrCoords, '=');
			index = token_by_delim(strFromFile, QuestInfo[idx][qQuestion], '=', index);
			if(index == (-1)) continue;

			index = token_by_delim(strFromFile, QuestInfo[idx][qAnswer], ';',index+1);
			//strmid(QuestInfo[idx][qQuestion], arrCoords[0], 0, strlen(arrCoords[0]), 128);
			//strmid(QuestInfo[idx][qAnswer], arrCoords[1], 0, strlen(arrCoords[1]), 64);
			//printf("%d.%s.", idx, QuestInfo[idx][qAnswer]);
			idx ++;
		}
		fclose(file);
		MaxQuestions = idx;
	}
}

stock LoadQuestsForPassenger()//��� ���������
{
	if(fexist("CashCab.ini"))
	{
		new File: file = fopen("CashCab.ini", io_read);
		new strFromFile[256+1];
		new idx, index;
		while( fread(file, strFromFile, sizeof(strFromFile)) )
		{
			index = 0;
			index = token_by_delim(strFromFile, QuestInfo[idx][qQuestion], '=', index);
			if(index == (-1)) continue;
			index = token_by_delim(strFromFile, QuestInfo[idx][qAnswer], ';', index+1);
			idx ++;
		}
		fclose(file);
	}
}

//stock CashCab_OnPlayerStateChange(playerid, newstate, oldstate)
stock victorina_OnPlayerStateChange(playerid, newstate, oldstate)
{   //���������� �� OnPlayerStateChange
	if(oldstate == PLAYER_STATE_PASSENGER)
	{
		SetPVarInt(playerid, "gPassengerInWindow", 0);//�������� ����, ��� ����� ��� �� � ����
		if(LastCar[playerid] == 106 && gQuestStarted > 0)
		{	//��� ���������
			gQuestStarted = -1;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "�������: ��������� ��������! �� ��������!");

		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{   //���� ID ������ ��������� ����� ��������� 3 - ��������
		if(nCarID[playerid] == 106 && gQuestStarted == -1)//IsInNPCVehicle(vehicleid) &&
		{//��� ���������    ////�������. ��� �������� �����.
			//SendClientMessage(playerid, COLOR_LIGHTBLUE, "�� ������ �� �������� �����. �� ���������� ����� �� �������� ������. ���� �������.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "�������: ������������, �������� ���������. �� ������ � ��������� �����. �� ���������� ����� �� �������� ������.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "��������: ����� ���������� � ������� �����. ����, �������.");
			ThinkTime = 30;
			gQuestStarted = playerid;
			QuestCounter = ThinkTime;

			if(gQuestStarted == 0) NowQuestion = random(MaxQuestions);//random(MAX_QUESTION);
			else NowQuestion = random(100);

			LoadQuestsForPassenger();
			//new strtmp[45+2+128];
			format(strings, sizeof(strings), "[���������]: {FFFF00}������ �%d: {00CCFF}%s?", NowQuestion, QuestInfo[NowQuestion][qQuestion]);
			SendClientMessage(playerid, COLOR_GREEN, strings);
		}
	}
}
//��� ��������� �����


stock victorina_OneSecondTimers()//��� ���������
{   //���������� �� ���������� �������
	if(gQuestStarted == -1) return 1;
	QuestCounter --;
	switch(QuestCounter)
	{
	    case 0:
	    {
			/*format(strings, sizeof(strings), "{FFD700}[���������]: {FFFFE0}����� �� ������� �� ������. ���������� ����� ���: %s",QuestInfo[NowQuestion][qAnswer]);
			SendClientMessageToAll(COLOR_PURPLE,strings);*/
			if(gQuestStarted > 0 && IsPlayerConnectedEx(gQuestStarted) && gPlayerSpawned[gQuestStarted])
			{//���� � �����
				SendClientMessage(gQuestStarted, COLOR_PURPLE, "[���������]: {FFFF00}�� �� ��������. {00CCFF}������ ���������. {FFFF00}��������� � ���������� �������.");
			}
			else OOCNews(COLOR_PURPLE, "[���������]: {FFFF00}����� �� �������. {00CCFF}������ ���������. {FFFF00}��������� � ���������� �������.");
			//SendClientMessageToAll(COLOR_PURPLE, "[���������]: {FFFF00}����� �� �������. {00CCFF}������ ���������. {FFFF00}��������� � ���������� �������.");
			if(gQuestStarted == 0) NowQuestion = random(MaxQuestions);//random(MAX_QUESTION);
			else NowQuestion = random(100);
			new strtmp[MAX_STRING];
			format(strtmp, sizeof(strtmp), "[���������]: {FFFF00}����� ������ �%d: {00CCFF}%s?", NowQuestion, QuestInfo[NowQuestion][qQuestion]);
			if(gQuestStarted > 0 && IsPlayerConnectedEx(gQuestStarted) && gPlayerSpawned[gQuestStarted]) SendClientMessage(gQuestStarted, COLOR_PURPLE, strtmp);
			else OOCNews(COLOR_PURPLE, strtmp); //SendClientMessageToAll(COLOR_PURPLE, strings);
			QuestCounter = ThinkTime;
	    }
	    case 30,60,90,120,150,180,210,240,270,300:
	    {
	    	if(gQuestStarted == 0)
	    	{
				new strtmp[MAX_STRING];
				format(strtmp, sizeof(strtmp), "[���������]: {FFFF00}������ ���. ���������: {00CCFF}%s?",QuestInfo[NowQuestion][qQuestion]);
				//SendClientMessageToAll(COLOR_PURPLE,strings);
				OOCNews(COLOR_PURPLE, strtmp);
			}
	    }
	}
	return 1;
}
