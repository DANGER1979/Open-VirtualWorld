new introtimer[MAX_PLAYERS];

//==============================================================================
//RegistrationSTEP0
stock Rules(playerid)
{
//ВНИМАНИЕ: длина строки не больше 70 символов
	new listitems[3715];
	strcat(listitems, "\t\t\t1/6. {0080FF}Игровой процесс. Запрещается");
	strcat(listitems, "\n1.1. Использовать нечестные способы превосходства.");
	strcat(listitems, "\n1.2. Использование багов, ошибок, недоработок мода.");
	strcat(listitems, "\n1.3. Любая ускоренная прокачка.");
	strcat(listitems, "\n1.4. Заниматься неигровой коммерцией.");
	strcat(listitems, "\n1.5. Передавать свой пароль на сервере другим лицам.");
	strcat(listitems, "\n1.6. Создавать и использовать более одного аккаунта.");
	strcat(listitems, "\n1.7. Реклама или обсуждение чит-программ.");
	strcat(listitems, "\n1.8. Использование команды показа диалогового окна");
	strcat(listitems, "\nс целью помехи игроку совершить то или иное действие.");
	strcat(listitems, "\n1.9. Использовать ESC, выход из игры или самоубийство");
	strcat(listitems, "\nв целях спасения от оппонента, прерывания ареста или заказа.");
	strcat(listitems, "\n1.10. Стоять на паузе (ESC) в игре длительное время.");
	strcat(listitems, "\n1.11. Длительное время находиться на проезжей части в");
	strcat(listitems, "\nсостоянии АФК, либо вести на ней беседу.");
	strcat(listitems, "\n1.12. Баннихоп, что даёт преимущество в скорости бега)");
	strcat(listitems, "\n1.13. Езда на крыше автомобиля.");
	strcat(listitems, "\n1.14. Куфить/связывать/тазерить/стрелять через текстуры");
	strcat(listitems, "\n1.15. Стрельба с водительского места или наезд на пешехода");
	strcat(listitems, "\n1.16. Убивать в Мотеле,Банке,Автошколе,Мэрии,Автосалоне.");
	strcat(listitems, "\n1.17. Повторно убивать за короткое время");
	strcat(listitems, "\n1.18. Убивать игроков по месту спауна.");
	strcat(listitems, "\n\t\t\t2/6. {0080FF}Процесс общения");
	strcat(listitems, "\n2.1. Запрещено проявлять неуважение к серверу и его разработчикам.");
	strcat(listitems, "\n2.2. Запрещено публичное оскорбление, хамство.");
	strcat(listitems, "\n2.3. Запрещены угрозы игрокам (не относящиеся к игровому процессу).");
	strcat(listitems, "\n2.4. Запрещено слишком часто писать заглавными буквами.");
	strcat(listitems, "\n2.5. Запрещено рекламировать что-либо (сайты, форумы, сервера).");
	strcat(listitems, "\n2.6. Запрещено часто повторять одинаковые фразы.");
	strcat(listitems, "\n\t\t\t3/6. {0080FF}Правило Ников");
	strcat(listitems, "\n3.1. Запрещено использовать бессмысленные или матерные ники.");
	strcat(listitems, "\n3.2. Запрещены ники, похожие на ники других игроков.");
	strcat(listitems, "\n3.3. Запрещены ники, содержащие оскорбления.");
	strcat(listitems, "\n3.4. Запрещены ники, содержащие более 50 % заглавных букв.");
	//strcat(listitems, "\n3.1. Запрещены ники содержащие географические названия.");
	//strcat(listitems, "\n3.2. Запрещено использовать в никах слова типа:");
	//strcat(listitems, "\nMister, Super, Girl, Pro, New, Man, The, Boy, Cool, Best и т.п.");
	//strcat(listitems, "\n3.3. Запрещены ники содержащие названия команд, фракций, работ.");
	//strcat(listitems, "\n3.5. Запрещено использовать имена, отличные от реальных.");
	strcat(listitems, "\n\t\t\t4/6. {0080FF}Администрирование сервера");
	strcat(listitems, "\n4.1. Запрещено обсуждать/критиковать действия администрации.");
	strcat(listitems, "\n4.2. Запрещено препятствовать администрации в работе.");
	strcat(listitems, "\n4.3. Запрещено оскорблять администрацию сервера.");
	strcat(listitems, "\n4.4. Запрещено злоупотреблять доверием.");
	strcat(listitems, "\n\t\t\t5/6. {0080FF}Штрафные санкции");
	strcat(listitems, "\n5.1. Администрация самостоятельно выбирает штрафные санкции.");
	strcat(listitems, "\n5.2. Решение можно оспорить, предоставив док-ва своей невиновности");
	strcat(listitems, "\n5.3. Штрафные санкции могут применяться как после нарушения, ");
	strcat(listitems, "\nтак и через некоторое время (впоследствии поступления жалобы).");
	strcat(listitems, "\n5.4. Предусмотрены следующие штрафные санкции: предупреждение, ");
	strcat(listitems, "\nкик(отключение от сервера),бан(временный запрет на посещение сервера)");
	strcat(listitems, "\n5.5. Если вы полагаете, что штрафная санкция была применена к вам");
	strcat(listitems, "\nошибочно, свяжитесь с администрацией сервера на сайте.");
	strcat(listitems, "\n5.6. В случаи отсутствия док-в, штрафные санкции могут быть увеличены.");
	strcat(listitems, "\n\t\t\t6/6. {0080FF}Требование Помощи");
	strcat(listitems, "\n6.1. Чтобы узнать некоторые команды Помощи, наберите /help");
	strcat(listitems, "\n6.2. Чтобы узнать, кто из администраторов в игре, наберите /admins");
	strcat(listitems, "\n6.3. Чтобы задать вопрос Хелперам, введите /question и сформулируйте вопрос");
	strcat(listitems, "\n6.4. Чтобы пожаловаться на читера Модераторам, введите /report,");
	strcat(listitems, "\nукажите ИД читера и опишите вид чита");
	strcat(listitems, "\n6.5. Чтобы обратиться к другим администраторам, выберите в /admins");
	strcat(listitems, "\n6.6. Формулируйте свою проблему чётко и ясно. Не стоит флудить.");
	strcat(listitems, "\n_____________________________________________________________________");
	strcat(listitems, "\n{0080FF}Если Вы согласны с данными правилами, нажмите кнопку 'Accept'.\0");
//RegistrationSTEP1
	new caption[23+64];
	format(caption, sizeof(caption), "Rules of the %s Server", SERVERNAME);
//{0080FF}Rules of the {FFFFFF}{88AA88}V{FFFFFF}irtual {88AA88}W{FFFFFF}orld{0080FF} Server
//Rules of the {88AA88}V{FFFFFF}irtual {88AA88}W{FFFFFF}orld{0080FF} Server
	ShowPlayerDialogGap(playerid, RULES_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "Accept", "Cancel");
}
stock rules_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != RULES_DIALOG) return 1;
//ShowPlayerDialogEx(playerid, 19, DIALOG_STYLE_LIST, "Role Play - "#SERVERNAME": Newspaper", listitems, "YES", "NO");
//ShowPlayerDialogGap(playerid, 19, DIALOG_STYLE_LIST, "{0080FF}Rules of the {FFFFFF}"#SERVERNAME" {0080FF}Server", listitems, "Accept", "Cancel");
	if(!response)
	{
		/*if(!GetPVarInt(playerid, "gPlayerAccount"))// && PlayerInfo[playerid][pDepositDay] == 0
		{
		    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Вы НЕ приняли условия сервера - Kicked.");
		    IsKicked[playerid] = 1;
		}
		else
		{
		    help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
		}*/
		help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
 		return 1;
	}
	//------------------------------------------------------------------
//RegistrationSTEP1
	if(!GetPVarInt(playerid, "gPlayerAccount") && gPlayerLogged[playerid] == 0)
	{   //если аккаунт не зарегистрирован  && PlayerInfo[playerid][pDepositDay] == 0
		//SetPVarInt(playerid, "gStatusRegistration", 1);
		if( GetPVarInt(playerid, "Intro") > 0 )//introtimer[playerid] != -1 )
		{
			for(new i; i < sizeof(Intro); i++)
			{
				TextDrawHideForPlayer(playerid, Intro[i]);
			}
			PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
			if(introtimer[playerid] != -1) { KillTimer(introtimer[playerid]); introtimer[playerid] = -1; }
			SetPVarInt(playerid, "Intro", 0);
		}
		//==============================================================
		if(gTesting == 0)
		{//если тестирование выключено
	    	//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, итак вы согласны с правилами сервера. Для начала регистрации Вам необходимо пройти анкетирование");
			//SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно! Тест окончен.");
			//SendClientMessage(playerid, COLOR_GREEN, "Для игры, Вам необходимо просматреть обучение и затем пройти регистрацию!");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, итак, вы согласны с правилами сервера. Для начала регистрации Вам необходимо просмотреть обучение.");
		    if(TutTimeCounter[playerid] == 0)
		    {   //если правила ни кто в данный момент не запустил, т.е. одновременно тока 1 поток
				//SetPVarInt(playerid, "gStatusRegistration", 1);//чтобы нельзя было запустить несколько таймеров
		    	//if(GetPVarInt(playerid, "gStatusRegistration"))
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
				Tutorial(playerid);//RegistrationSTEP4
			}
		}
		else
		{
	    	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, итак вы согласны с правилами сервера. Для начала регистрации Вам необходимо пройти тестирование");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Чтобы пройти его, вам необходимо ответить правильно на все вопросы.");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Не нажимайте ни каких клавиш на клавиатуре, пока вас не попросит СЕРВЕР");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}не пишите в чат ни каких сообщений, чтобы Вас не кикнуло.");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}В случае ошибки, Вы будете также кикнуты с сервера и при входе начнёте всё заново.");
		    new listitems[] = "1. Нажав на F6, введя /dutylist и нажав на Enter.\n2. Нажав на F6, введя /info и нажав на Enter.\n3. Нажав на F6, введя /question [текст] и нажав Enter.";//\n4. Нажав на F6, введя /report и нажав на Enter.
			MenuOperation[playerid] = 71;
	        ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "1/15. Как на сервере можно задать вопрос хелперам?", listitems, "OK", "");//RegistrationSTEP2
		}
	}
	return 1;
}
