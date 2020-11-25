new gReminder, index_repeating;


forward Reminder(playerid, days, repeating);
public Reminder(playerid, days, repeating)
{//напоминание на почтовый €щик всем игрокам
	index_repeating ++;
//index, - с какой позиции выводить инфу
//limit - сколько игроков отображать
	//SendClientMessageToAll(COLOR_PINK, "Ќапоминание начато!!!");
	new  Mail[34], playername[MAX_PLAYER_NAME], Password[20], Offline;
	//GetPlayerName(playerid, playername, MAX_PLAYER_NAME);
	//mysql_real_escape_string(playername, playername);

	new ToBase[128+3+3+4];
	format(ToBase, sizeof(ToBase), "SELECT `ID`, `Name`,`Password`,`Mail`,`Offline` FROM `players` WHERE %d-`Offline`>%d AND `Offline`>0 ORDER BY `ID` LIMIT %d, 1",
		getdate(), days, index_repeating-1);
	//format(ToBase, sizeof(ToBase), "SELECT `Name`,`Password`,`Mail`,`Offline` FROM `players` WHERE `Name` = '%s'", playername);
	mysql_query(ToBase);	mysql_store_result();

	new Field[34];
	//new Data[128 + 178+57+24+65+85+82 + 24 +12];
	//while(mysql_fetch_row_format(Data, "|"))
	if(mysql_num_rows() > 0)
	{
		if(mysql_retrieve_row())
		{
			mysql_fetch_field_row(playername, "Name");
			mysql_fetch_field_row(Password, "Password");

			mysql_fetch_field_row(Mail, "Mail");
			mysql_fetch_field_row(Field, "Offline"); Offline = strval(Field);

			new strHTTP[119+ 24+34+24+20+3+27];
			format(strHTTP, sizeof(strHTTP), "%s/SendMailVW/SendRememberPassword.php?Mail=%s&PlayerName=%s&Password=%s&IP="#IP_ADRESS":"#PORT"&Days=%d&LastOnline=%s",
				HostName, Mail, playername, Password, getdate()-Offline, getDate(Offline));
			HTTP(playerid, HTTP_GET, strHTTP, "", "");
			//ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "Ќапоминание",strtmp, "OK", "");

			//new strings[37+24+4];
			//format(strings, sizeof(strings), "CEPBEP: %s[%d] напоминание отослано.",  playername, index_repeating);
			//SendClientMessage(playerid, COLOR_GREY, strings);
			printf("CEPBEP: %s[%d] напоминание отослано на email %s.",  playername, index_repeating, Mail);
		}
	}
	mysql_free_result();

	if(index_repeating >= repeating)
	{
		KillTimer(gReminder); gReminder = -1;
		//SendClientMessageToAll(COLOR_PINK, "Ќапоминание закончено!!!");
		print("Ќапоминание закончено!!!");
	}
	return 1;
}


	else if(!strcmp(cmd, "/reminder", true))
	{
		if(PlayerInfo[playerid][pAdmin] < 7)
		{
			SendClientMessage(playerid, COLOR_GREY, "   ¬ы не уполномочены использовать эту команду !");
			return 1;
		}
		if(!strcmp(php_host, "localhost", true))
		{//localhost
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ќа вашем сервере не предусмотрена система напоминани€ парол€.");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /reminder [PlayerName]");
			return 1;
		}
		new playername[MAX_PLAYER_NAME];
		strmid(playername, tmp, 0, strlen(tmp), MAX_PLAYER_NAME);
		//mysql_real_escape_string(playername, playername);
		if(CheckExistPlayer(playerid, playername) == 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Ёто им€ не зарегистрировано или указано не верно !");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);//возвращает INVALID_PLAYER_ID если игрока нету

		new Field[34];
		new Mail[34], Password[20], Offline;

		new newpass[20];
		format(newpass, sizeof(newpass), "%s", generate_password(6));
		strmid(Password, newpass, 0, 7, 20);
		//mysql_real_escape_string(newpass, newpass);

		new ToBase[128+3+3+4];
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Password`='%s' WHERE `Name`='%s'", newpass, playername);
		mysql_query(ToBase);

		format(ToBase, sizeof(ToBase), "SELECT `ID`,`Name`,`Password`,`Mail`,`Offline` FROM `players` WHERE `Name` = '%s'", playername);
		mysql_query(ToBase);	mysql_store_result();
		if(mysql_num_rows() > 0)
		{
			if(mysql_retrieve_row())
			{
				mysql_fetch_field_row(playername, "Name");
				mysql_fetch_field_row(Password, "Password");
				mysql_fetch_field_row(Mail, "Mail");
				mysql_fetch_field_row(Field, "Offline"); Offline = strval(Field);

				new strHTTP[119+ 24+34+24+20+3+27 + 12];
				format(strHTTP, sizeof(strHTTP), "%s/SendMailVW/SendRememberPassword.php?Mail=%s&PlayerName=%s&Password=%s&IP="#IP_ADRESS":"#PORT"&Days=%d&LastOnline=%s",
					HostName,Mail,playername,Password,getdate()-Offline,getDate(Offline));
				HTTP(playerid, HTTP_GET, strHTTP, "", "");

				if(PlayerInfo[playerid][pAdmin] == 9) ShowPlayerDialogEx1(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "Ќапоминание",strHTTP, "OK", "");

				new strtmp[44+24+34];
				format(strtmp, sizeof(strtmp), "%s: напоминание отослано %s'у на майл.",  PlayerName(playerid), playername);
				SendClientMessage(playerid, COLOR_GREY, strtmp);

				//printf("CEPBEP: %s[%d] напоминание отослано на email %s.",  playername, index_repeating, Mail);
			}
		}
		mysql_free_result();

		//return 1;
	}
	else if(!strcmp(cmd, "/reminderall", true))
	{
		if(PlayerInfo[playerid][pAdmin] != 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "   ¬ы не уполномочены использовать эту команду !");
			return 1;
		}
		if(!strcmp(php_host, "localhost", true))
		{//localhost
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ќа вашем сервере не предусмотрена система напоминани€ парол€.");
			return 1;
		}
		new ToBase[96+3];
		format(ToBase, sizeof(ToBase), "SELECT `Name`,`Password`,`Mail`,`Offline` FROM `players` WHERE %d-`Offline`>10 AND `Offline`>0", getdate());
		mysql_query(ToBase);	mysql_store_result();
		new repeating = mysql_num_rows();	//if( limit < 1)  limit = 0;
		mysql_free_result();

		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			format(strcmd, sizeof(strcmd), "USE: /reminder [days] [interval] [start(0-%d)]",  repeating);
			SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
			return 1;
		}
	 	new days= strval(tmp);
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			format(strcmd, sizeof(strcmd), "USE: /reminder [days] [interval] [start(0-%d)]",  repeating);
			SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
			return 1;
		}
		if(strval(tmp) < 1000)
		{
			format(strcmd, sizeof(strcmd), "USE: /reminder [days] [interval] [start(0-%d)]",  repeating);
			SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
			return 1;
		}
		new interval = strval(tmp);
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			format(strcmd, sizeof(strcmd), "USE: /reminder [days] [interval] [start(0-%d)]",  repeating);
			SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
			return 1;
		}
		if(strval(tmp) > repeating)
		{
			format(strcmd, sizeof(strcmd), "USE: /reminder [days] [interval] [start(0-%d)]",  repeating);
			SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
			return 1;
		}
		index_repeating = strval(tmp);
		//format(strcmd, sizeof(strcmd), "* MySQL вернула %d строк. Ќапоминание отослано %d-му.",  limit, index);
		//SendClientMessage(playerid, COLOR_PINK, strcmd);
		//Reminder(playerid, index, days);

		//SendClientMessageToAll(COLOR_PINK, "Ќапоминание начато!!!");
		print("Ќапоминание начато!!!");
		KillTimer(gReminder); gReminder = -1;
		gReminder = SetTimerEx("Reminder", interval, repeating, "ddd", playerid, days, repeating);
		//return 1;
	}
