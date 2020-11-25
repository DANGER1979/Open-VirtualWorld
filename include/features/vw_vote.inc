//для опроса
new gInQuestion[MAX_PLAYERS];//если 1 - то проголосовал
new WritingQuestion[MAX_PLAYERS];//1 - опрос, 2 - голосование
new TimeQuestioning;//время ожидания для вывода результатов
new first_button = 0;//кол-во людей нажавиших первую кнопку
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
	//qInfoFull[700 + 48+2],//текст диалога + "У Вас %d секунд на принятие решения"
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
new Question[InfoQuestion];//для опроса
new FirstMonday = 6;//число первого понедельника в году
new WritingStep[MAX_PLAYERS]; //Used for onplayertext to see which line he's at


//stock Election()
stock vote_OneHourTimer(playerid)
{//вызывается каждый час, но ждёт флага Question[qApprove], который автоматом опустится раз неделю Election_OneDayTimer()
//ВЫБОРЫ
//SendClientMessageToAll(COLOR_RED, "Выборы начало");
	if(Question[qApprove]) return 1; //SendClientMessage(playerid, COLOR_GREY, "   Идёт голосование (USE: /approve) !");
	new giveplayerid = MAX_PLAYERS-3;
	if(WritingQuestion[giveplayerid] > 0) return 1; //SendClientMessage(playerid, COLOR_GREY, "   Составление Опроса уже начато !");
	//----------------------------------------------------------------------
	new MySQLID, playername[MAX_PLAYER_NAME], Score;
	strmid(Question[qMaker], "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	Question[qLine] = 5;//strval(tmp); кол-во участников голосования ответа.
	Question[qStyle] = 2;//strval(tmp);
	Question[qClose] = 0;//strval(nstring);

//находим день в году следующего воскресенья
	new remainder;
	new current_day = getdate();
	do
	{
		remainder = (current_day-(FirstMonday-1))%7;//остаток от деления на 7
		current_day++;
	}
	while(remainder != 0);//выйти из цикла когда remainder станет == 0

	Question[qDays] = (current_day-1)-getdate();
	Question[qStart] = getdate();
	Question[qEnd] = getdate()+Question[qDays];

	WritingQuestion[giveplayerid] = 2;//опрос(1) или голосование(2)
	WritingStep[giveplayerid] = 1;//флаг для начала

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

	strmid(Question[qCaption], "Кто, по вашему мнению, достоин места губернатора?", 0, strlen("Кто, по вашему мнению, достоин места губернатора?"), 65);//Заголовок окна
	strmid(Question[qInfo0], "Не участвовать", 0, 18, 18);
	strmid(Question[qInfo], "Не участвовать\n", 0, 18, 18);
	strmid(Question[qButton1], "OK", 0, strlen("OK"), 10);
	strmid(Question[qButton2], "CANCEL", 0, strlen("CANCEL"), 10);
	
#if defined vw_sql//#endif
	new Field[34];	new idx;
	new ToBase[949];
	format(ToBase, sizeof(ToBase), "SELECT `ID`,`Name`,`Score` FROM `players` WHERE (`ConnectTime`-`Online`)>%d AND `Level`>%d AND `House`<>%d ORDER BY `Score` DESC LIMIT 5", 14, 9, 255);
//если онлайн на этой недели больше 14 часов и уровень выше 9 и живёшь в доме
	//mysql_query(ToBase);
	//mysql_store_result();
	new DBResult:db_result = db_query(db_VW,ToBase);
	//if(mysql_num_rows() <= 1)
	if(!db_num_rows(db_result))
	{
		SendClientMessageToAll(COLOR_YELLOW, "ВЫБОРЫ НЕ СОСТОЯЛИСЬ. Причина: отсутствие достойных кандидатов." );
		//mysql_free_result();
		db_free_result(db_result);
		return 1;
	}
	//new Data[56];//10+24+10 + 12 = 56 AND `ConnectTime`>6 AND `Score`>0
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

		//SendClientMessageToAll(COLOR_YELLOW, "   В Мэрии проводится голосование!!!");
		format(strings, sizeof(strings), "%d. Претендент на пост губернатора: %s[%d]. Score: %d", WritingStep[giveplayerid], playername, MySQLID, Score);
		Log(INVITE,strings);
		SendClientMessageToAll(COLOR_LIGHTBLUE, strings);

		if(WritingStep[giveplayerid] > Question[qLine])
		{//WritingStep[giveplayerid] = 6 > Question[qLine] = 5;
   			if(WritingQuestion[giveplayerid] == 2)
   			{
//очистка данных
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		        	PlayerInfo[i][pVote] = 0;
		        }
				//mysql_query("UPDATE `players` SET `Vote`=0");
   				//mysql_query("TRUNCATE `election`");//очистка таблицы
				db_free_result(db_query(db_VW, "UPDATE `players` SET `Vote`=0"));
				db_free_result(db_query(db_VW, "TRUNCATE `election`"));

  				//сохранение голосования
   				Question[qApprove] = Question[qDays];//поднимаем флаг, чтобы не запускалось новое голосование
				SaveVoteSQL();
				//LoadVoteSQL();//чтобы переменные загрузились
   			}
			WritingQuestion[giveplayerid] = 0;//закончили составление опроса
			WritingStep[giveplayerid] = 0;
			/*TimeQuestioning = 1;//запускаем таймер

	       	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				HideDialog(i);
				if(AFK_IdleTime[i] < 3) TogglePlayerControllableEx(i, 0);//обездвиживает
				new qInfoFull[700 + 48+2];
				format(qInfoFull, sizeof(qInfoFull), "%s\n\t\t\tУ Вас %d секунд на принятие решения !", Question[qInfo], qTime);
				ShowPlayerDialogEx(i, QUESTION2_DIALOG, Question[qStyle],Question[qCaption],qInfoFull,Question[qButton1],Question[qButton2]);
			}*/
		}
		//idx ++;
	}
	while(db_next_row(db_result));
	//mysql_free_result();
	db_free_result(db_result);
#endif
//SendClientMessageToAll(COLOR_GREEN, "Выборы конец");
	//----------------------------------------------------------------------
	//Update3DTextLabelText(ElectionInfo, 0x0080FFFF, "Избирательный участок\n{FFFFFF}Нажмите '{0080FF}~k~~VEHICLE_ENTER_EXIT~{FFFFFF}'\nчтобы голосовать");
	return 1;
}
//для выборов конец

//для опроса начало
//stock WritingQuestioningText(playerid, const text[])//для опроса STEP2
stock vote_OnPlayerText(playerid, const text[])//для опроса STEP2
{	//вызывается из OnPlayerText
	if(!strlen(text))
	{
	    SendClientMessage(playerid, COLOR_RED, "   Пожалуйста введите Текст.");
		return 1;
	}
	//new strings[MAX_STRING];

	new nstring[128];
	format(nstring, sizeof(nstring), "%s", text);//полоса текста

	if(WritingStep[playerid] > Question[qLine])
	{   //начало оформления кнопок диалога
//для голосования STEP3
		if(WritingStep[playerid] == 11)
	    {
			if(strlen(nstring) <= 0 || strlen(nstring) > 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Максимальное кол-во символов не более 10 !");
				return 1;
			}
	        strmid(Question[qButton1], nstring, 0, strlen(nstring), 10);
	        WritingStep[playerid] ++;
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Пожалуйста укажите Название второй (правой) кнопки диалога.");
	    }
		else if(WritingStep[playerid] == 12)
	    {
			if(strlen(nstring) <= 0 || strlen(nstring) > 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Максимальное кол-во символов не более 10 !");
				return 1;
			}
	        strmid(Question[qButton2], nstring, 0, strlen(nstring), 10);
	        WritingStep[playerid] ++;
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Пожалуйста укажите тип голосования: 0-Открытое(рекомендуется) или 1-Закрытое(USE: /unfreezall).");
	    }
		else if(WritingStep[playerid] == 13)
	    {
			if(strval(nstring) < 0 || strval(nstring) > 1)
			{
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Пожалуйста укажите тип голосования: 0-Открытое(рекомендуется) или 1-Закрытое.");
				return 1;
			}
			Question[qClose] = strval(nstring);

   			if(WritingQuestion[playerid] == 2)
   			{
			   //очистка данных

			   	for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		        	PlayerInfo[i][pVote] = 0;
		        }
#if defined vw_sql//#endif
				//mysql_query("UPDATE `players` SET `Vote`=0");
   				//mysql_query("TRUNCATE `election`");//очистка таблицы
				db_free_result(db_query(db_VW, "UPDATE `players` SET `Vote`=0"));
				db_free_result(db_query(db_VW, "TRUNCATE `election`"));
#endif
  				//сохранение голосования
   				Question[qApprove] = 1;
				SaveVoteSQL();
				//LoadVoteSQL();//чтобы переменные загрузились
   			}

			WritingQuestion[playerid] = 0;//закончили составление опроса
			WritingStep[playerid] = 0;

			TimeQuestioning = 1;//запускаем таймер

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				HideDialog(i);
				TogglePlayerControllableEx(i, 0);//обездвиживает
				new qInfoFull[700 + 48+2];
				format(qInfoFull, sizeof(qInfoFull), "%s\n\t\t\tУ Вас %d секунд на принятие решения !", Question[qInfo], qTime);
				ShowPlayerDialogEx(i, QUESTION2_DIALOG, Question[qStyle],Question[qCaption],qInfoFull,Question[qButton1],Question[qButton2]);
			}

		    new payout = 10000*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])/10;
			//GivePlayerMoneyB(1, playerid, payout/2);
			FamilyInfo[SAN][fBank] += payout;
		}
	}
	else
	{   //начало составления строк диалога
		//if(Question[qStyle] != 2) return 1;
		if(strlen(text) > 70)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Максимальное кол-во символов не более 70 !");
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
			    format(strings, sizeof(strings), "CEPBEP: {33AA33}Извините, учётной записи %s нету в базе данных.", playername);
    			SendClientMessage(playerid, COLOR_RED, strings);
				return 1;
			}
		}
//для голосования STEP2
		//-----------------------------
		if(WritingStep[playerid] == 0)
		{
			if(strlen(nstring) > 65)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Максимальное кол-во символов не более 65 !");
				return 1;
			}
	        strmid(Question[qCaption], nstring, 0, strlen(nstring), 65);//Заголовок окна

	        format(strings, sizeof(strings), "   Теперь вы можете написать Текст самого диалога. Он будет размещён в теле окна. Вам доступно %d строк.", Question[qLine]);
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

	        if(WritingQuestion[playerid] == 2)
	        {
	        	//SendClientMessage(playerid, COLOR_RED, "Рекомендации: первый вариант ответа сформулируйти так: 'Не участвовать'");
	        	SendClientMessage(playerid, COLOR_GREY, "   Можно просто кликнуть двойным щелчком в TAB для указания ника.");
	        }
	        SendClientMessage(playerid, COLOR_GREY, "   Можно использовать (/n) для перевода строки и (/t) для табуляции (слэш заменить на левый)");
		}
		else if(WritingStep[playerid] == 1)
  		{
  			strmid(Question[qInfo0], "Не участвовать", 0, 18, 18);
  			strmid(Question[qInfo], "Не участвовать\n", 0, 18, 18);
			//strins(Question[qInfo], "Не участвовать\n", strlen(Question[qInfo]));

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
			format(strings, sizeof(strings), "   Bы написали Вариант Ответа №%d.", WritingStep[playerid]-1);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		}
		if(WritingStep[playerid] > Question[qLine])
		{
  			//format(Question[qInfoFull], sizeof(Question[qInfoFull]), "%s\n\t\t\tУ Вас %d секунд на принятие решения !", Question[qInfo], qTime);
			WritingStep[playerid] = 11;
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Пожалуйста укажите Название первой (левой) кнопки диалога.");
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
	  			strmid(Question[qInfo0], "Не участвовать", 0, 18, 18);
	  			strmid(Question[qInfo], "Не участвовать\n", 0, 18, 18);

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
				format(strings, sizeof(strings), "   Bы написали Вариант Ответа №%d.", WritingStep[playerid]-1);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			}
			if(WritingStep[playerid] > Question[qLine])
			{
	  			//format(Question[qInfoFull], sizeof(Question[qInfoFull]), "%s\n\t\t\tУ Вас %d секунд на принятие решения !", Question[qInfo], qTime);
				WritingStep[playerid] = 11;
		        SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Пожалуйста укажите Название первой (левой) кнопки диалога.");
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
//для опроса STEP3 //для голосования STEP4
//ShowPlayerDialogEx(j,20,Question[qStyle],Question[qCaption],qInfoFull,Question[qButton1],Question[qButton2]);
		TogglePlayerControllableEx(playerid, 1);//размораживает
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
					SendClientMessage(playerid, COLOR_GREY, "   Значение должно быть от 1 до 1000000");
					//new qInfoFull[700 + 48+2];
					//format(qInfoFull, sizeof(qInfoFull), "%s\n\t\t\tУ Вас %d секунд на принятие решения !", Question[qInfo], qTime);
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

//stock QuestioningTimer()//для опроса STEP4 //для голосования STEP5
stock vote_OneSecondTimers(playerid)
{   //вызывается из секундного таймера
	TimeQuestioning ++;
    if(TimeQuestioning < qTime) return 1;

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(gInQuestion[i] && AFK_IdleTime[i] < 3)//если игрок голосовал в опросе
		{   //посылается всем участникам опроса
	    	new dlgitem[1024];
	    	if(Question[qStyle] == DIALOG_STYLE_MSGBOX)
	    	{
				format(dlgitem, sizeof(dlgitem), "Итого:\n%s - \t\t\t%d голосов\n%s - \t\t\t%d голосов\nВсего голосов:\t%d",
					Question[qButton1], first_button, Question[qButton2], second_button, (first_button+second_button));
			}
	    	else if(Question[qStyle] == DIALOG_STYLE_INPUT)
   			{
				//new qInfoFull[700 + 48+2];
				format(dlgitem, sizeof(dlgitem), "Итого: \n%s\n\t\t\t%d", Question[qInfo], feeQuest);
				//format(dlgitem, sizeof(dlgitem), "Итого: \n%s\n\t\t\t%d", Question[qInfoFull], feeQuest);
			}
	    	else if(Question[qStyle] == DIALOG_STYLE_LIST)
	    	{
				listitem_full = listitem1+listitem2+listitem3+listitem4+listitem5+listitem6+listitem7+listitem8+listitem9+listitem10;
				//listitem0 - не подсчитываем
				format(dlgitem, sizeof(dlgitem),
					"Итого:\
					\n%s - \t\t%d голосов\n",Question[qInfo1], listitem1);
				if(Question[qLine] >= 2) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo2], listitem2);
				if(Question[qLine] >= 3) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo3], listitem3);
				if(Question[qLine] >= 4) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo4], listitem4);
				if(Question[qLine] >= 5) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\nd", dlgitem, Question[qInfo5], listitem5);
				if(Question[qLine] >= 6) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo6], listitem6);
				if(Question[qLine] >= 7) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo7], listitem7);
				if(Question[qLine] >= 8) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo8], listitem8);
				if(Question[qLine] >= 9) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo9], listitem9);
				if(Question[qLine] >= 10) format(dlgitem, sizeof(dlgitem),
					"%s%s - \t\t%d голосов\n", dlgitem, Question[qInfo10], listitem10);
				format(dlgitem, sizeof(dlgitem), "%s\nВсего голосов:\t%d", dlgitem, listitem_full);
			}
			HideDialog(i);
			TogglePlayerControllableEx(i, 0);//обездвиживает
	        if(Question[qClose] == 0)
	        {
				ShowPlayerDialogEx(i, QUESTION2_DIALOG, DIALOG_STYLE_MSGBOX, Question[qCaption],dlgitem, "OK", "Cancel");
			}
			else if(Question[qClose] == 1 && !strcmp(Question[qMaker], PlayerName(i), true))
			{   //если закрытое, то показываем только создателю
				ShowPlayerDialogGap(i, QUESTION2_DIALOG, DIALOG_STYLE_MSGBOX, Question[qCaption],dlgitem, "OK", "Cancel");
			}
			gInQuestion[i] = 0;
		}
		else// if(!gInQuestion[i])
		{   //если игрок не голосовал но менюшка ему для опроса была показана
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
//для выборов
   	if(//PlayerInfo[playerid][pConnectTime] >= 20 && //PlayerInfo[playerid][pLevel] >= 3 &&
   		PlayerInfo[playerid][pConnectTime] >= (OnlineRecord*20/100) &&
		PlayerInfo[playerid][pVote] == 0 &&
		getdate() >= Question[qStart] && getdate() <= Question[qEnd])
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "Избирательный участок №1: В данный момент проводится голосование. Нам интересно Ваше мнение !");
		ShowPlayerDialogEx(playerid, QUESTION1_DIALOG,Question[qStyle],Question[qCaption],Question[qInfo],Question[qButton1],Question[qButton2]);
		//return 1;
	}
	else
	{
		if( PlayerInfo[playerid][pConnectTime] < (OnlineRecord*20/100))
		{
			format(strings, sizeof(strings), "   Принимать участие в голосовании могут лица играющие на сервере больше %d часов.", (OnlineRecord*20/100));
			SendClientMessage(playerid, COLOR_GREY, strings);
		}
 		if( PlayerInfo[playerid][pVote] == 1)
 		{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже проголосовали.");
		}
		MenuOperation[playerid] = 4;
		format(strings, sizeof(strings), "У Вас на счету: $%d\
\nВведите сумму обналичивания. \
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", PlayerInfo[playerid][pBank]);
		ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "BANK: Снятие денег", strings, "OK", "Cancel");
	}
	return 1;
}
stock vote_OnDialogResponse2(playerid, dialogid, response, listitem, inputtext[])
{
			//#pragma unused listitem
			#pragma unused inputtext
			if(dialogid != QUESTION1_DIALOG) return 1;//для голосования STEP7
			SetPVarInt(playerid, "gShowDialog", -1);
			if(!response) { return 1; }
			new msgitem[256+1];
			//new giveplayerid;
//ShowPlayerDialogEx(playerid, QUESTION1_DIALOG,Question[qStyle],Question[qCaption],Question[qInfo],Question[qButton1],Question[qButton2]);
//"Избирательный участок №1"
//для опроса STEP6
 			if(	//PlayerInfo[playerid][pLevel] < 3 ||
			 	PlayerInfo[playerid][pConnectTime] < (OnlineRecord*20/100))
 			{
 				format(msgitem, sizeof(msgitem), "   Принимать участие в голосовании могут лица играющие на сервере больше %d часов.", (OnlineRecord*20/100));
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
 			if(PlayerInfo[playerid][pVote] != 0)
 			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже голосовали!");
				return 1;
			}
			new forplayername[MAX_PLAYER_NAME];
 			if(listitem == 0)
			{
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вы отказались от участия в голосовании, но можете проголосовать позже!");
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
			format(msgitem, sizeof(msgitem), "Спасибо! Ваш голос за %s'а принят!", forplayername);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);

			return 1;
}

