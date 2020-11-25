//для викторины
#define MAX_QUESTION 202
new MaxQuestions = 100;//стартовое значение, при загрузке инициализируется
enum QInfo
{
	qQuestion[128],
	qAnswer[64],
};
new QuestInfo[MAX_QUESTION][QInfo];
new ThinkTime = 230;//время для обдумывания
new QuestCounter = 230;//таймер
new gQuestStarted = -1;//показатель режима викторины, 1..-такси  или 0-общая
//new gQuestPlayerStarted[MAX_PLAYERS];
new NowQuestion;//номер текущего вопроса из массива



//для викторины начало
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
			//trimSideSpaces(strFromFile);//обрезка пробелов
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

stock LoadQuestsForPassenger()//для викторины
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
{   //вызывается из OnPlayerStateChange
	if(oldstate == PLAYER_STATE_PASSENGER)
	{
		SetPVarInt(playerid, "gPassengerInWindow", 0);//опустили флаг, что игрок уже не в окне
		if(LastCar[playerid] == 106 && gQuestStarted > 0)
		{	//для викторины
			gQuestStarted = -1;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Таксист: Викторина Окончена! До свидания!");

		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{   //если ID нового состояния равно состоянию 3 - пассажир
		if(nCarID[playerid] == 106 && gQuestStarted == -1)//IsInNPCVehicle(vehicleid) &&
		{//для викторины    ////ЗДрасте. Это передача ТАКСИ.
			//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вы попали на телеигру ТАКСИ. За правильный ответ вы получите деньги. Итак поехали.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Таксист: Здравствуйте, садитесь поудобней. Вы попали в программу ТАКСИ. За правильный ответ вы получите деньги.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "ВНИМАНИЕ: Ответ начинается с большой буквы. Итак, поехали.");
			ThinkTime = 30;
			gQuestStarted = playerid;
			QuestCounter = ThinkTime;

			if(gQuestStarted == 0) NowQuestion = random(MaxQuestions);//random(MAX_QUESTION);
			else NowQuestion = random(100);

			LoadQuestsForPassenger();
			//new strtmp[45+2+128];
			format(strings, sizeof(strings), "[Викторина]: {FFFF00}Вопрос №%d: {00CCFF}%s?", NowQuestion, QuestInfo[NowQuestion][qQuestion]);
			SendClientMessage(playerid, COLOR_GREEN, strings);
		}
	}
}
//для викторины конец


stock victorina_OneSecondTimers()//для викторины
{   //вызывается из секундного таймера
	if(gQuestStarted == -1) return 1;
	QuestCounter --;
	switch(QuestCounter)
	{
	    case 0:
	    {
			/*format(strings, sizeof(strings), "{FFD700}[Викторина]: {FFFFE0}Никто не ответил на вопрос. Правильный ответ был: %s",QuestInfo[NowQuestion][qAnswer]);
			SendClientMessageToAll(COLOR_PURPLE,strings);*/
			if(gQuestStarted > 0 && IsPlayerConnectedEx(gQuestStarted) && gPlayerSpawned[gQuestStarted])
			{//если в такси
				SendClientMessage(gQuestStarted, COLOR_PURPLE, "[Викторина]: {FFFF00}Вы не ответили. {00CCFF}Вопрос снимается. {FFFF00}Переходим к следующему вопросу.");
			}
			else OOCNews(COLOR_PURPLE, "[Викторина]: {FFFF00}Никто не ответил. {00CCFF}Вопрос снимается. {FFFF00}Переходим к следующему вопросу.");
			//SendClientMessageToAll(COLOR_PURPLE, "[Викторина]: {FFFF00}Никто не ответил. {00CCFF}Вопрос снимается. {FFFF00}Переходим к следующему вопросу.");
			if(gQuestStarted == 0) NowQuestion = random(MaxQuestions);//random(MAX_QUESTION);
			else NowQuestion = random(100);
			new strtmp[MAX_STRING];
			format(strtmp, sizeof(strtmp), "[Викторина]: {FFFF00}Новый Вопрос №%d: {00CCFF}%s?", NowQuestion, QuestInfo[NowQuestion][qQuestion]);
			if(gQuestStarted > 0 && IsPlayerConnectedEx(gQuestStarted) && gPlayerSpawned[gQuestStarted]) SendClientMessage(gQuestStarted, COLOR_PURPLE, strtmp);
			else OOCNews(COLOR_PURPLE, strtmp); //SendClientMessageToAll(COLOR_PURPLE, strings);
			QuestCounter = ThinkTime;
	    }
	    case 30,60,90,120,150,180,210,240,270,300:
	    {
	    	if(gQuestStarted == 0)
	    	{
				new strtmp[MAX_STRING];
				format(strtmp, sizeof(strtmp), "[Викторина]: {FFFF00}Ответа нет. Напоминаю: {00CCFF}%s?",QuestInfo[NowQuestion][qQuestion]);
				//SendClientMessageToAll(COLOR_PURPLE,strings);
				OOCNews(COLOR_PURPLE, strtmp);
			}
	    }
	}
	return 1;
}
