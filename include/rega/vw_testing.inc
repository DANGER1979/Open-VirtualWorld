
stock Testing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
//#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != TEST_DIALOG) return 1;
	if(!response)
	{
		SendClientMessage(playerid, COLOR_RED, "Вы отказались от прохождения теста (Kicked)!");
	 	return 1;
	}
	//new msgitem[256+1];
	//new giveplayerid;
//RegistrationSTEP2
//ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "1. Вы едете на авто и увидели у обочины голосующего.", listitems, "OK", "Cancel");
	PlayerTesting(playerid, listitem);//RegistrationSTEP3
	return 1;
}
//RegistrationSTEP3
stock PlayerTesting(playerid, listitem)
{
	if(MenuOperation[playerid] == 71)
	{
		if(listitem == 2) //2 , т.к. счёт идёт от нуля
		{       //если игрок выбрал 3 строку сверху
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Продолжу играть, не обращая на него внимания.\
\n2. Cвяжусь с модератором через /report, расскажу о читере указав его ID.\
\n3. Спрошу, где достать и как установить такую же.";
			MenuOperation[playerid] = 72;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "2/15. Игрок на ваших глазах использует чит-программу.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 72)
	{
		if(listitem == 1)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Дам свой пароль другу, т.к. не вижу в этом ничего плохого\
\n2. Дам свой пароль только в обмен на его пароль.\
\n3. Не дам ни кому свой пароль.";

			MenuOperation[playerid] = 73;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "3/15. Вам предложили покачать вашего персонажа.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 73)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Повторю ему через /report, пока не ответит.\
\n2. Припугну его, что у Вас папа на БелТелеКоме работает.\
\n3. Найду его на сервере и убью.\
\n4. Найду его на сервере и вежливо повторю просьбу.\
\n5. Подожду некоторое время и вежливо повторю просьбу.";
			MenuOperation[playerid] = 74;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "4/15. Вы отправили модератору жалобу, а он не реагирует.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 74)
	{
		if(listitem == 3 || listitem == 4)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Напишу в /report и расскажу ГеймАдмину.\
\n2. Я сам так делал.\
\n3. Не вижу в этом ничего плохого.\
\n4. Проигнорирую, т.к. меня это не задело.";
			MenuOperation[playerid] = 75;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "5/15. У вас на глазах игрок вышел в ESC, чтобы избежать смерти.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 75)
	{
		if(listitem == 0 || listitem == 3)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Использую программу для зацикливания своих движений.\
\n2. Выйду из игры, чтобы не мешать другим.\
\n3. Прямо на дороге выйду в ESC и сверну игру.";
			MenuOperation[playerid] = 76;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "6/15. Вам нужно на час отойти от игры.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 76)
	{
		if(listitem == 1)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Ники, содержащие географические названия.\
\n2. Ники, содержащие слова типа Mister, Super, Girl, Pro, New, Man\
\n3. Ники, содержащие названия команд, фракций, работ.\
\n4. Бессмысленные и нецензурные ники.\
\n5. Все перечисленные.";
			MenuOperation[playerid] = 77;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "7/15. Правила ников персонажей запрещают использовать:", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 77)
	{
		if(listitem == 4)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Буду активно использовать эту недоработку, чтобы заработать.\
\n2. Проигнорирую данное сообщение.\
\n3. Буду пользоваться сам и никому не скажу.\
\n4. Напишу о недоработке в объявление.\
\n5. Сообщу только друзьям и знакомым.\
\n6. Сообщу администрации. И не буду пользоваться.\
\n7. Сообщу родителям.";
			MenuOperation[playerid] = 78;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "8/15. Вам рассказали способ быстро заработать деньги.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 78)
	{
		if(listitem == 5)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Вы положите трубку и забудете о разговоре.\
\n2. Вы поторгуетесь, чтобы договориться о лучшей цене.\
\n3. Вы согласитесь, т.к. давно хотели поиграть другим персонажем.\
\n4. Буду дальше играть, не обращая внимания.\
\n5. Соглашусь, т.к. это лучший способ быстро заработать.\
\n6. Откажусь и сообщу администрации о звонившем.";
			MenuOperation[playerid] = 79;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "9/15. Вам предложили купить/продать аккаунт за реальные деньги.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 79)
	{
		if(listitem == 5)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Установлю чит-программу и накажу обманщика.\
\n2. Буду, оскорбляя, угрожать ему в чате.\
\n3. Сообщу администрации сервера.\
\n4. Зайду на канал TS3 и обложу его 3-х томным матом.\
\n5. Сообщу в ФБР через службу /service Rescue 911.\
\n6. Постараюсь успокоиться, т.к. угрозы запрещены на сервере.";
			MenuOperation[playerid] = 80;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "10/15. Вас обманули/убили и вы хотите отомстить.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 80)
	{
		if(listitem == 4 || listitem == 5)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. С радостью соглашусь, т.к. качать их честно очень скучно.\
\n2. Проигнорирую сообщение.\
\n3. Сделаю скриншот разговора (F8) и свяжусь с администрацией.\
\n4. Я прекрасно понимаю, что за это банят или удаляют аккаунт.";
			MenuOperation[playerid] = 81;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "11/15. Вам предложили ускоренно прокачать ваши навыки.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 81)
	{
		if(listitem == 2 || listitem == 3)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Я самый хитрый.\
\n2. Это не запрещено правилами.\
\n3. Это запрещено правилами.\
\n4. Об этом не написано в правилах.";
			MenuOperation[playerid] = 82;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "12/15. Вы решили зарегистрировать ещё один аккаунт.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 82)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Убью обидчика.\
\n2. Не буду отвечать бранью на брань.\
\n3. Отвечу ему выражениями похлеще.\
\n4. Сделаю скриншот и cообщу администрации.";
			MenuOperation[playerid] = 83;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "13/15. Вы услышали в свой адрес оскорбления и нецензурные выражения.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 83)
	{
		if(listitem == 1 || listitem == 3)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Завладею машиной, вытащив водителя.\
\n2. Запрыгну на крышу и поеду.\
\n3. Поблагодарю и откажусь.\
\n4. Стану перед машиной, угрожая оружием.";
			MenuOperation[playerid] = 84;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "14/15. Вас хотят подвезти, но все места в машине заняты.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 84)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно!");
			new listitems[] = "1. Убью игрока, чтобы упростить задачу администратору.\
\n2. Убьёте администратора, чтобы получить вознаграждение от игрока.\
\n3. Не будете мешать администратору выполнять свои обязанности.";
			MenuOperation[playerid] = 85;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "15/15. Вы видите, как администратор обсуждает нарушение с игроком.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 85)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Вы ответили правильно! Тест окончен.");
			SendClientMessage(playerid, COLOR_GREEN, "Для игры, Вам необходимо просмотреть обучение и затем пройти регистрацию!");

		    if(TutTimeCounter[playerid] == 0)
		    {   //если правила ни кто в данный момент не запустил, т.е. одновременно тока 1 поток
				//SetPVarInt(playerid, "gStatusRegistration", 1);//чтобы нельзя было запустить несколько таймеров
		    	//if(GetPVarInt(playerid, "gStatusRegistration"))
		    	if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
				{
					SetPVarInt(playerid, "gOoc", 1); SetPVarInt(playerid, "gNews", 1);
					SetPVarInt(playerid, "gFam", 1); SetPVarInt(playerid, "gHidePM", 0);
					SetPVarInt(playerid, "gSport", 1); SetPVarInt(playerid, "gJob", 1);//для чата
				}
				TutTimeCounter[playerid] = 1;//поднимаем флаг чтобы начать
				Tutorial(playerid);//RegistrationSTEP4
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "Вы ответили неверно (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: Вы ответили неверно !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	CrashDetected[playerid] = 87;
	return 1;
}
