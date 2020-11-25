
new PlayerText:check_rus_TD[MAX_PLAYERS][2];
new GameTextTimer[MAX_PLAYERS] = -1;
stock GameTextForPlayerExx(playerid, const text[], time=3000, font=1)
{
	 #pragma unused time

	// для русика
	check_rus_TD[playerid][0] = CreatePlayerTextDraw(playerid, 244.3333, 101.6742, RusToGame(text));
	PlayerTextDrawLetterSize(playerid, check_rus_TD[playerid][0], 0.4090, 2.6162);
	PlayerTextDrawAlignment(playerid, check_rus_TD[playerid][0], 1);
	PlayerTextDrawColor(playerid, check_rus_TD[playerid][0], -1);
	PlayerTextDrawSetOutline(playerid, check_rus_TD[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, check_rus_TD[playerid][0], 1402450687);
	PlayerTextDrawFont(playerid, check_rus_TD[playerid][0], font);
	PlayerTextDrawSetProportional(playerid, check_rus_TD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, check_rus_TD[playerid][0], 0);
	PlayerTextDrawShow(playerid, check_rus_TD[playerid][0]);

	check_rus_TD[playerid][1] = CreatePlayerTextDraw(playerid, 271.0000, 121.2445, "VIRTUAL_WORLD");
	PlayerTextDrawLetterSize(playerid, check_rus_TD[playerid][1], 0.4090, 2.6161);
	PlayerTextDrawAlignment(playerid, check_rus_TD[playerid][1], 1);
	PlayerTextDrawColor(playerid, check_rus_TD[playerid][1], -1);
	PlayerTextDrawSetOutline(playerid, check_rus_TD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, check_rus_TD[playerid][1], 1402450687);
	PlayerTextDrawFont(playerid, check_rus_TD[playerid][1], font);
	PlayerTextDrawSetProportional(playerid, check_rus_TD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, check_rus_TD[playerid][1], 0);
	PlayerTextDrawShow(playerid, check_rus_TD[playerid][1]);

	//GameTextTimer[playerid] = SetTimerEx("@GameText_Timer", time, false, "d", playerid);//false - разовый таймер
}

//@GameText_Timer(playerid);
//@GameText_Timer(playerid)
stock HideGameTextForPlayerExx(playerid)
{
	for(new i = 0; i < 2; i ++)//sizeof(check_rus_TD)
	{
		PlayerTextDrawHide(playerid, check_rus_TD[playerid][i]);
  		PlayerTextDrawDestroy(playerid, check_rus_TD[playerid][i]);
	}
	if(GameTextTimer[playerid] != -1)
	{
	    KillTimer(GameTextTimer[playerid]);
	    GameTextTimer[playerid] = -1;
    }
	return 1;
}

stock LoginDialog(playerid)
{//может повторяться вызов
	//PlayAudioStreamForPlayerEx(playerid, "GTAV_titles.mp3");
	GameTextForPlayerExx(playerid, "ДОБРО_ПОЖАЛОВАТЬ_НА", 0, 1);
	//GameTextForPlayerEx2(playerid, "VIRTUAL_WORLD", 5000, 1);

	SetPVarInt(playerid, "gPlayerAccount", 2);//учетная запись уже создана
//\n\n\t{8CAA63}- Пожалуйста введите ваш пароль ниже \n\tи нажмите LOGIN:

   	new dlgitem[409];//40+74+67+25+39+76 + 64+24 = 409
    format(dlgitem, sizeof(dlgitem), "\nС Возвращением на сервер {0080FF}V{FFFFFF}irtual {0080FF}W{FFFFFF}orld.\
\n{0080FF}Имя: {FFFFFF}%s{A9C4E4} - зарегистрировано.\
\nВы можете входить.\
\nПожалуйста, введите Пароль ниже:\
\n\n{8CAA63}Примечание:\
\n\t- Пароль чувствителен к регистру:\
\n\t- Если Вы забыли пароль нажмите REMINDER \n\tи проверьте почтовый ящик.", PlayerInfo[playerid][pName]);//SERVERNAME,
	//new caption[19+64];
	//format(caption, sizeof(caption), "Вход на {2680C0}%s", SERVERNAME);
	ShowPlayerDialogEx(playerid, LOGIN_DIALOG, DIALOG_STYLE_PASSWORD, "Вход на {0080FF}V{FFFFFF}irtual {0080FF}W{FFFFFF}orld", dlgitem, "Войти", "Напомнить");//, "Забыл");
	//ShowPlayerDialogEx(playerid, LOGIN_DIALOG, DIALOG_STYLE_MSGBOX, caption, dlgitem, "Войти", "Забыл");
}


stock login_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	changepass_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
//==============================================================================
	if(dialogid != LOGIN_DIALOG) return 1;
	//--------------------------------------------------------------------------
	/*for(new i = 0; i < 2; i ++)//sizeof(check_rus_TD)
	{
		PlayerTextDrawHide(playerid, check_rus_TD[playerid][i]);
  		PlayerTextDrawDestroy(playerid, check_rus_TD[playerid][i]);
	}*/
	//@GameText_Timer(playerid);
	HideGameTextForPlayerExx(playerid);
	//--------------------------------------------------------------------------
	SetPVarInt(playerid, "Intro", 0);
	if(!response)
	{ //REMINDER
		if( GetPVarInt(playerid, "gPlayerAccount") == 2)//&& gPlayerLogged[playerid] == 1//иначе не будет отправлять
		{//если аккаунт существует
			if(strcmp(php_host, "localhost", true))
			{//не localhost
				if(GetPVarInt(playerid, "PasswordHasEdited") == getdate() && !IsPlayerAdmin(playerid))
				{
					SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Вы уже сегодня произвели отправку пароля.");
				    LoginDialog(playerid);
					return 1;
				}

				/*new Field[34];
				new  Mail[34], Password[20], Offline;
				new ToBase[128+3+3+4];
				format(ToBase, sizeof(ToBase), "SELECT `ID`,`Password`,`Mail`,`Offline` FROM `players` WHERE `Name`='%s' LIMIT 1", PlayerInfo[playerid][pName]);
				mysql_query(ToBase);	mysql_store_result();
				if(mysql_num_rows() > 0 && mysql_retrieve_row())
				{
					//mysql_fetch_field_row(playername, "Name");
					mysql_fetch_field_row(Password, "Password");
					mysql_fetch_field_row(Mail, "Mail");
					mysql_fetch_field_row(Field, "Offline"); Offline = strval(Field);
					new strHTTP[118 + 24+34+24+20+3+27];
					format(strHTTP, sizeof(strHTTP), "%s/SendMailVW/SendRememberPassword.php?Mail=%s&PlayerName=%s&Password=%s&IP="#IP_ADRESS":"#PORT"&Days=%d&LastOnline=%s",
						HostName, Mail, PlayerInfo[playerid][pName], Password, getdate()-Offline, getDate(Offline));
					HTTP(playerid, HTTP_GET, strHTTP, "", "HTTP_RememberPassword");
					//ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "Напоминание",strtmp, "OK", "");
				}
				mysql_free_result();*/

			    LoginDialog(playerid);
			}
			else
			{
				SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}На сервере в данный момент не предусмотрена система напоминания пароля.");
			    LoginDialog(playerid);
			}
		}
	}
	else
	{//LOGIN
		if(GetPVarInt(playerid, "gPlayerAccount") && gPlayerLogged[playerid] == 0)
		{  //если ак существует и вы не залогинелись
//RegistrationSTEP14 END
			if(!GetPVarInt(playerid, "gPlayerAccount"))
			{   //если учетная запись не создана(файл), игрок не зарегистрирован
       			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Извините, но этот сервер требует зарегистрироваться перед тем как войти в игру!");
    			RegistrationSTEP6(playerid);
				return 1;
			}
			if(!strlen(inputtext) || strlen(inputtext) > 20)
			{
				SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Пожалуйста введите пароль не более 20 символов!!!");
				LoginDialog(playerid);
				return 1;
			}
			//------------------------------------------------------------------
			if( CheckExistPlayer(playerid, PlayerInfo[playerid][pName]) == 1 )
			{
				OnPlayerLogin(playerid, inputtext); //RegistrationSTEP15
				return 1;
			}
			else if( CheckExistPlayer(playerid, PlayerInfo[playerid][pName]) == 0 )
			{
				SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Извините, Учётной записи: {FFFFFF}%s{A9C4E4} нету в базе. Пройдите регистрацию перед тем как войти в игру!");
			    RegistrationSTEP6(playerid);
				PlaySoundForPlayer(playerid, 21002);
				return 1;
			}
			else //if(CheckExistPlayer(playerid, PlayerInfo[playerid][pName]) == -1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Регистрация прервана по причине отсутствия подключения к базе ! Пожалуйста обратитесь к хостеру ! (kicked)");
				new msgitem[256+1];
				format(msgitem, sizeof(msgitem), "CEPBEP: %s[%d] был кикнут, причина: База данных не отвечает !",
					PlayerInfo[playerid][pName], playerid);
				Log(KICK, msgitem);
				IsKicked[playerid] = 1;
				PlaySoundForPlayer(playerid, 21002);
			}
		}
	}
	return 1;
}


stock CheckPassword(playerid, const nameplayer[], password[])
{
	SetPVarInt(playerid, "gPlayerAccount", 2);//учетная запись уже создана
	//new newpass[64];
	//gpci(playerid, newpass, SERIAL_LENGTH);
	//strmid(PlayerInfo[playerid][pKey], newpass, 0, strlen(newpass), SERIAL_LENGTH);

	new ToBase[90+24+64];
	format(ToBase, sizeof(ToBase), "SELECT `Name`,`Password` FROM `players` WHERE `Name` = '%s' AND `Password` = '%s' LIMIT 1", nameplayer, password);//PlayerInfo[playerid][pKey]);
	new DBResult:db_result = db_query(db_VW, ToBase);
	if( db_num_rows(db_result) )
	{	//если в базе нашло хоть одно значение
		db_free_result(db_result);
		SendClientMessage(playerid, COLOR_SYSTEM, "   Пароль принят.");//PlayerInfo[playerid][pSQLID] != 0
		return 1;
	}
	//Password mismatch
	db_free_result(db_result);

	GivePVarInt(playerid, "mistaking", -1);
	if(GetPVarInt(playerid, "mistaking") > 0)
	{
   		new dlgitem[341];//72+46+36+25+39+36+76 + 11
    	format(dlgitem, sizeof(dlgitem), "\nПароль: {0080FF}'%s'{A9C4E4}, не соответствует вашей учётной записи.\
\nУ вас осталось {0080FF}%d{A9C4E4} попытки.\
\nПожалуйста, введите Пароль ниже:\
\n\n{8CAA63}Примечание:\
\n\t- пароль чувствителен к регистру,\
\n\t- пароль не более 20 символов.\
\n\t- Если Вы забыли пароль нажмите REMINDER \n\tи проверьте почтовый ящик.", password, GetPVarInt(playerid, "mistaking"));

		new caption[19+64];
		format(caption, sizeof(caption), "Вход на {2680C0}%s", SERVERNAME);
		ShowPlayerDialogEx(playerid, LOGIN_DIALOG, DIALOG_STYLE_PASSWORD, caption, dlgitem, "Войти", "Забыл");
		return 0;
	}
	format(strings, sizeof(strings), "   Пароль: '%s', не соответствует вашей учётной записи (USE: (/q)uit, чтобы выйти из игры).", PlayerInfo[playerid][pKey]);
	SendClientMessage(playerid, COLOR_SYSTEM, strings);

	format(strings, sizeof(strings), "CEPBEP: %s[%d] kicked, reason: password mistaking", PlayerInfo[playerid][pName], playerid);
	SendSystemMessage(COLOR_MAROON, strings, 1);
	IsKicked[playerid] = 1;
	return 0;
}

//RegistrationSTEP15
//должна вызываться до выбора спауна и скина, чтобы не менять данные на заблокировнные аках
stock OnPlayerLogin(playerid, password[])//вызывается из OnDialogResponse->Login_OnDialogResponse
{   //ф-ция загрузки параметров игрока из файла .ini, но к этому моменту в файл необх сохранить данные
	new timers = GetTickCount();
	if(!IsPlayerConnected(playerid)) return 1;
	/*if(gPlayerLogged[playerid] == 0 && CurState[playerid] != PLAYER_STATE_SPECTATING)//!= 9
	{//если ф-ия запустилась до момента логирования
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Wrong OnPlayerLogin(player:%s, logged:%d, %s)",
			PlayerInfo[playerid][pName], gPlayerLogged[playerid], SendPlayerStateMessage(playerid));
		SendClientMessage(playerid, COLOR_RED, strings);
		LoginDialog(playerid);
		Log(ERROR, strings);
		return 1;
	}*/

	if( CheckPassword(playerid, PlayerInfo[playerid][pName], password) == 0) return 1;//если пароль не верен
//если пароль принят
	OnPlayerLoadParameters(playerid, PlayerInfo[playerid][pName]);
	//OnPlayerLoadTempParameters(playerid, PlayerInfo[playerid][pName]);

	//if(CHECKING == 1)
	//{
//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
//format(strings, sizeof(strings), "Begin OnPlayerLogin(playerid: %d, Int: %d, Virt: %d, Loc: %d)", playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
//SendClientMessage(playerid, COLOR_RED, strings);
	//}

//==============================================================================
//АВТОСИСТЕМЫ
	if(PlayerInfo[playerid][pLevel] < 0) //-999 автобан
	{
		if(getdate() < PlayerInfo[playerid][pWarns]
		&& PlayerInfo[playerid][pWarns] <= 365) //-999 autoban
		{
			format(strings, sizeof(strings), "   Ваш аккаунт заблокирован на %d дней !", PlayerInfo[playerid][pWarns] - getdate());
			SendClientMessage(playerid, COLOR_SYSTEM, strings);

			format(strings, sizeof(strings), "%s[%d] kicked, reason: account blocked !", PlayerInfo[playerid][pName], playerid);
			SendSystemMessage(COLOR_MAROON, strings, 1);
			IsKicked[playerid] = 1;
	        return 1;
		}
		else //if(getdate() >= PlayerInfo[playerid][pWarns]) //авторазбан
		{
			//PlayerInfo[playerid][pLevel] = PlayerInfo[playerid][pAdmin];
			//PlayerInfo[playerid][pAdmin] = 0;
			PlayerInfo[playerid][pWarns] = 0;
		}
	}
	if(PlayerInfo[playerid][pMuted] > GetTickCount()) //автомут
	{
		if(GetTickCount() < PlayerInfo[playerid][pMuted])
		{
			format(strings, sizeof(strings), "   Вы заглушены на %d минут !", floatround((PlayerInfo[playerid][pMuted]-GetTickCount())/1000.0)/60.0);//PlayerInfo[playerid][pMuted] - getdate());
			SendClientMessage(playerid, COLOR_SYSTEM, strings);
		}
		else //авторазмут
		{
			PlayerInfo[playerid][pMuted] = 0;
		}
	}
//print("1");
//==============================================================================

//АВТОНАКАЗАНИЯ
	if(PlayerInfo[playerid][pArticle] >= 1 && PlayerInfo[playerid][pArticle] <= 36)
	{
		new strtmp[13+3+1 + 12];
		format(strtmp, sizeof(strtmp), "Cтатья %d.%d",
			PlayerInfo[playerid][pArticle], PlayerInfo[playerid][pPart]);//Статья
		SetPlayerCriminal(DoT, playerid, INVALID_PLAYER_ID, strtmp);
	}
	else if(PlayerInfo[playerid][pArticle] >= 139)
	{
		new strtmp[13+3+1 + 12];
		format(strtmp, sizeof(strtmp), "Cтатья %d.%d",
			PlayerInfo[playerid][pArticle], PlayerInfo[playerid][pPart]);//Статья
		SetPlayerCriminal(FBI, playerid, INVALID_PLAYER_ID, strtmp);
	}
	else if(PlayerInfo[playerid][pArticle] == 0 && WantedPoints[playerid] > 0)
	{//если нету статьи
		//найти последнюю запись в логе преступлений
#if defined vw_sql//#endif
		new ToBase[78+11];
		format(ToBase, sizeof(ToBase), "SELECT `Reason` FROM `criminallist` WHERE `ID`=%d ORDER BY `IND` DESC LIMIT 1",
				PlayerInfo[playerid][pSQLID]);//playername);
		//mysql_query(ToBase); mysql_store_result();
		//if(mysql_num_rows() > 0 && mysql_retrieve_row())
		//{
		//	mysql_fetch_field_row(PlayerCrime[playerid][pAccusedof], "Reason");
		//}
		//mysql_free_result();
		new DBResult:db_result = db_query(db_VW, ToBase);
		new Field[128];
		if(db_num_rows(db_result))
		{
			//db_get_field_assoc(db_result, "Reason", Field, sizeof(Field) );   PlayerCrime[playerid][pAccusedof] = strval(Field);
			db_get_field_assoc(db_result, "Reason", Field, sizeof(Field) );  strmid(PlayerCrime[playerid][pAccusedof], Field, 0, strlen(Field), sizeof(Field));
		}
		db_free_result(db_result);
#endif

		if(WantedPoints[playerid] >= 1 && WantedPoints[playerid] <= 6) { SetPlayerCriminal(DoT, playerid, MAX_PLAYERS-1, PlayerCrime[playerid][pAccusedof]); }
		else if(WantedPoints[playerid] >= 7 && WantedPoints[playerid] <= 10) { SetPlayerCriminal(DoT, playerid, MAX_PLAYERS-1, PlayerCrime[playerid][pAccusedof]); }
		else if(WantedPoints[playerid] >= 11 && WantedPoints[playerid] <= 14) { SetPlayerCriminal(DoT, playerid, MAX_PLAYERS-1, PlayerCrime[playerid][pAccusedof]); }
		else if(WantedPoints[playerid] >= 15 && WantedPoints[playerid] <= 18) { SetPlayerCriminal(FBI, playerid, MAX_PLAYERS-1, PlayerCrime[playerid][pAccusedof]); }
		else if(WantedPoints[playerid] >= 19 && WantedPoints[playerid] <= 22) { SetPlayerCriminal(FBI, playerid, MAX_PLAYERS-1, PlayerCrime[playerid][pAccusedof]); }
		else if(WantedPoints[playerid] >= 23) { SetPlayerCriminal(FBI, playerid, MAX_PLAYERS-1, PlayerCrime[playerid][pAccusedof]); }
	}
	if( (PlayerInfo[playerid][pJailed] >= 1 && PlayerInfo[playerid][pJailed] <= 3)
		&& PlayerInfo[playerid][pArticle] >= 139) LevelToDeliver ++;
	if(	PlayerInfo[playerid][pSTD] > 0 &&
		PlayerInfo[playerid][pSTD] < IsNotBeenIll) LevelToEpidemics ++;
//print("2");
//==============================================================================

//ИНИЦИАЛИЗАЦИИ НЕПРАВИЛЬНЫХ ДАННЫХ
	if(PlayerInfo[playerid][pLocal] == -1) PlayerInfo[playerid][pLocal] = FREEROAM;
	if(PlayerInfo[playerid][pHouse] == -1) PlayerInfo[playerid][pHouse] = NOT_KEY;
	if(PlayerInfo[playerid][pBizz] == -1) PlayerInfo[playerid][pBizz] = NOT_KEY;
	//if(PlayerInfo[playerid][pTeam] == 0) PlayerInfo[playerid][pTeam] = 3;
	if(PlayerInfo[playerid][pSTD] == -1 || PlayerInfo[playerid][pSTD] == IsNotBeenIll) PlayerInfo[playerid][pSTD] = 0;
	if( !IsValidSkin(PlayerInfo[playerid][pModel]))
	{
		format(strings, sizeof(strings), "Error14: playerid %s[%d], reason: Use Invalid Skin %d", PlayerInfo[playerid][pName], playerid, PlayerInfo[playerid][pModel]);
		Log(ERROR, strings);
		PlayerInfo[playerid][pModel] = SKIN_DEFAULT;
	}
	if( !IsValidSkin(PlayerInfo[playerid][pChar]))
	{
		format(strings, sizeof(strings), "Error15: playerid %s[%d], reason: Use Invalid Skin %d", PlayerInfo[playerid][pName], playerid, PlayerInfo[playerid][pChar]);
		Log(ERROR, strings);
		PlayerInfo[playerid][pChar] = SKIN_DEFAULT;
	}
//ИНИЦИАЛИЗАЦИИ ДАННЫХ
	DollahScoreUpdate(playerid);
//vw_adminchat
	//if(PlayerInfo[playerid][pAdmin] > 0) TextDrawShowMessage[playerid] = true;
	//else TextDrawShowMessage[playerid] = false;

	SetPVarInt(playerid, "gOoc", 0); SetPVarInt(playerid, "gNews", 0); SetPVarInt(playerid, "gFam", 0);
	SetPVarInt(playerid, "gSport", 0); SetPVarInt(playerid, "gJob", 0);

	if(PlayerInfo[playerid][pGun22Skill] > 999) PlayerInfo[playerid][pGun22Skill] = 999;
	if(PlayerInfo[playerid][pGun23Skill] > 999) PlayerInfo[playerid][pGun23Skill] = 999;
	if(PlayerInfo[playerid][pGun24Skill] > 999) PlayerInfo[playerid][pGun24Skill] = 999;
	if(PlayerInfo[playerid][pGun25Skill] > 999) PlayerInfo[playerid][pGun25Skill] = 999;
	if(PlayerInfo[playerid][pGun26Skill] > 999) PlayerInfo[playerid][pGun26Skill] = 999;
	if(PlayerInfo[playerid][pGun27Skill] > 999) PlayerInfo[playerid][pGun27Skill] = 999;
	if(PlayerInfo[playerid][pGun28Skill] > 999) PlayerInfo[playerid][pGun28Skill] = 999;
	if(PlayerInfo[playerid][pGun29Skill] > 999) PlayerInfo[playerid][pGun29Skill] = 999;
	if(PlayerInfo[playerid][pGun30Skill] > 999) PlayerInfo[playerid][pGun30Skill] = 999;
	if(PlayerInfo[playerid][pGun31Skill] > 999) PlayerInfo[playerid][pGun31Skill] = 999;
	if(PlayerInfo[playerid][pGun34Skill] > 999) PlayerInfo[playerid][pGun34Skill] = 999;

	if(!gRealWar)
	{
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_PISTOL, PlayerInfo[playerid][pGun22Skill]);//PISTOL
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_PISTOL_SILENCED, PlayerInfo[playerid][pGun23Skill]);//PISTOL_SILENCED
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_DESERT_EAGLE, PlayerInfo[playerid][pGun24Skill]);//DESERT_EAGLE
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SHOTGUN, PlayerInfo[playerid][pGun25Skill]);//SHOTGUN
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, PlayerInfo[playerid][pGun26Skill]);//SAWNOFF_SHOTGUN
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SPAS12_SHOTGUN, PlayerInfo[playerid][pGun27Skill]);//SPAS12_SHOTGUN
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_MICRO_UZI, PlayerInfo[playerid][pGun28Skill]);//MICRO_UZI
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_MP5, PlayerInfo[playerid][pGun29Skill]);//MP5
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_AK47, PlayerInfo[playerid][pGun30Skill]);//AK47
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_M4, PlayerInfo[playerid][pGun31Skill]);//M4
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SNIPERRIFLE, PlayerInfo[playerid][pGun34Skill]);//SNIPERRIFLE
	}
	else
	{
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_PISTOL, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_PISTOL_SILENCED, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SHOTGUN, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_MICRO_UZI, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_MP5, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_AK47, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_M4, 999);
		SetPlayerSkillLevelEx(playerid, WEAPONSKILL_SNIPERRIFLE, 999);
	}
//print("3");
//для потребностей инициализация
	if(PlayerInfo[playerid][pParam1] >= operator1) gParameter1[playerid] = 1;
	SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);

	if(PlayerInfo[playerid][pParam2] >= operator2) gParameter2[playerid] = 1;
	SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);

	if(PlayerInfo[playerid][pParam3] >= operator3) gParameter3[playerid] = 1;
	SetPlayerShowScale(playerid, 3, PlayerInfo[playerid][pParam3], operator3);

	if(PlayerInfo[playerid][pParam4] >= operator4) gParameter4[playerid] = 1;
	SetPlayerShowScale(playerid, 4, PlayerInfo[playerid][pParam4], operator4);

	if(PlayerInfo[playerid][pParam5] >= operator5) gParameter5[playerid] = 1;
	SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);

	ResetPlayerMoney(playerid);//Сбросить деньги игрока на 0
	gConsumingMoney[playerid] = CHEATLIM;
	//SetPVarInt(playerid, "LastMoney", PlayerInfo[playerid][pCash]);//перезаписать значение денег на руках
	LastMoney[playerid] = PlayerInfo[playerid][pCash];
	GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);//начислить деньги игроку из переменной

	LastHealth[playerid] = 100.0;
	PlayerInfo[playerid][pHealth] = floatadd(PlayerInfo[playerid][pSHealth], 50.0);
	SetPlayerHealth(playerid, PlayerInfo[playerid][pHealth]);//Кол-во жизней у игрока
	//SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth]);//Кол-во жизней у игрока
	LastState[playerid] = CurState[playerid];

	if(PlayerInfo[playerid][pLeader] >= TEAM_GROVE)
	{
	    new family = PlayerInfo[playerid][pLeader];
		strmid(FamilyInfo[family][fLeader], PlayerInfo[playerid][pName], 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
	}

	TextDrawShowScale[playerid] = true;

	for(new j=0; j<MAX_TURFS; j++)//для зон банд MAX_TURFS
	{
		if(	IsAGangs(playerid) || IsAFamilyMember(playerid) || PlayerInfo[playerid][pAdmin] == 2)
		{   //скорее всего нужен будет Hide
			//GangZoneHideForPlayer(playerid, Turfs[j]);//спрятать зону Turfs[gangzone] для показа в другом цвете
			GangZoneShowForPlayer(playerid, Turfs[j], TurfInfo[j][zColor]);//Показать зону для игрока в том цвете которой она счас является
		}
	}
//print("4");
//==============================================================================
//ЗАМЕНА ЗАПРОСОВ НА ЦИКЛЫ

//АВТОПРИСВАИВАНИЕ ТАЧКИ

//можно заменить проверку запросом
	for(new vid = 1; vid<=GetMaxVehicles; vid++)
	{   //сканируем все тачки на сервере
		//if(	VehInfo[vid][cModel] < 400) continue;
		if(!IsValidVehicle(vid)) continue;
		if(	VehInfo[vid][cOwned] > 0 &&
			VehInfo[vid][cOwned] == PlayerInfo[playerid][pSQLID]
			//!strcmp(VehInfo[vid][cOwner], PlayerInfo[playerid][pName], true)
		  )
		{   //находим ваши
			if(MyCar[playerid][0] == 0) MyCar[playerid][0] = vid;
			else if(MyCar[playerid][1] == 0) MyCar[playerid][1] = vid;
			else if(MyCar[playerid][2] == 0) { MyCar[playerid][2] = vid; break; }
		}
	}
 	//new Field[20];
 	new index; //мможно заменить проверку по массиву домов на параметр владельца дома
	//if(PlayerInfo[playerid][pHouse] >= 0 && PlayerInfo[playerid][pHouse] < MAX_HOUSE)
	//{
	for(new h = 0; h < MAX_HOUSE; h++)
	{
  		if(PlayerInfo[playerid][pSQLID] == HouseInfo[h][hOwned])
		{
			if(index >= 5) break;
			MyHouse[playerid][index] = h;
			index ++;
		}
	}
	//}
	index = 0;
	for(new b=0; b<MAX_BIZ; b++)
	{
  		if(PlayerInfo[playerid][pSQLID] == BizInfo[b][bOwned])
		{
		    if(index >= 10) break;
			MyBizz[playerid][index] = b;
			index ++;
		}
	}
	index = 0;
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{
  		if(PlayerInfo[playerid][pSQLID] == SBizInfo[sb][sbOwned])
		{
			if(index >= 20) break;
			MyCompany[playerid][index] = sb;
			index ++;
		}
	}
//print("5");
//==============================================================================
//СООБЩЕНИЯ ПРИ ВХОДЕ
	if(PlayerInfo[playerid][pLevel] == 1)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Посмотреть все доступные команды и многое другое можно при помощи команды /help или клавиши H");
		//SendClientMessage(playerid, COLOR_GREEN, "Сменить пароль можно командой /changepass.");
		//SendClientMessage(playerid, COLOR_GRAD2, "Для приглашения наставника (USE: /accept referal)");
		//SendClientMessage(playerid, COLOR_GRAD3, "Для Получения Информации по моду в любое время Вы можете набрать /info.");
		SendClientMessage(playerid, COLOR_GREEN, "Задать вопрос по игре Хелперам (USE: /question). Пожаловаться на читера Модераторам (USE: /report)");
		//SendClientMessage(playerid, COLOR_GRAD5, "Посмотреть список админов и послать им сообщение командой /admins");
		//SendClientMessage(playerid, COLOR_GREEN, "Обязательно посетите наш форум "#FORUM" на нем вы найдете всю необходимую информацию!");
	}
	else if(PlayerInfo[playerid][pLevel] > 1)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Пригласи своего друга на сервер и стань ему наставником. И будешь получать уважение за его прокачку уровня.");
		//SendClientMessage(playerid, COLOR_GREEN, "Ошибки пишем в отчете на форуме по шаблону в теме <Bug reports - Отчёт об ошибках>");
	}

	if(PlayerInfo[playerid][pTut] < 43) SendClientMessage(playerid, COLOR_GREEN, "Наберите /tut, чтобы продолжить интерактивное обучение");
	//SendClientMessage(playerid, COLOR_GRAD8, "Для нормальной игры без лагов закройте браузер.");

 	if(getdate() >= Question[qStart] && getdate() <= Question[qEnd])
	{// && PlayerInfo[playerid][pVote] == 0
		SendClientMessage(playerid, COLOR_YELLOW, "В Мэрии в данный момент проводится голосование. Нам интересно Ваше мнение !");
	}
//print("6");
	if(	PlayerInfo[playerid][pMember] >= TEAM_GROVE &&
		PlayerInfo[playerid][pMember] <= TEAM_MAFIA)
	{
	    format(strings, sizeof(strings), "Family MOTD: %s.", FamilyInfo[PlayerInfo[playerid][pMember]][fMOTD]);
	    SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	if(PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] <= DoE)
	{
	    format(strings, sizeof(strings), "Family MOTD: %s.", FamilyInfo[0+PlayerInfo[playerid][pMember]][fMOTD]);
	    SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	if(PlayerInfo[playerid][pAccount] != 0)
	{
	    if(getdate() > PlayerInfo[playerid][pAccount])
	    {
	    	SendClientMessage(playerid, COLOR_SYSTEM, "   Срок действия Премиум Аккаунта закончен.");
	    	PlayerInfo[playerid][pAccount] = 0;
	    }
	    else
	    {
	    	format(strings, sizeof(strings), "   Вы имеете Премиум Аккаунт до %s, с чем Вас и Поздравляю.", getDate(PlayerInfo[playerid][pAccount]));
			SendClientMessage(playerid, COLOR_SYSTEM, strings);
			PlayerInfo[playerid][pSTD] = IsNotBeenIll;
		}
	}
//print("7");
	
	new arrCoords[3][5];
	split(PlayerInfo[playerid][pAge], arrCoords, '.');
	new dd = strval(arrCoords[0]);
	new mm = strval(arrCoords[1]);
	//new yyyy = strval(arrCoords[2]);
	new month, day;	getdate(_, month, day);
	if(day == dd && month == mm)
	{
		format(strings, sizeof(strings), "CEPBEP: {33AA33}Администрация сервера поздравляет {FFFFFF}%s'a {FFFF00}с Днём Рождения и желает удачи.", PlayerInfo[playerid][pName]);
		SendClientMessageToAll(COLOR_RED, strings);
	}

	if(PlayerInfo[playerid][pLeader] >= TEAM_GROVE)// && PlayerInfo[playerid][pLeader] < DoT
	{
		format(strings, sizeof(strings), "%s %s {FFFFFF}%s{FFFF00}: {33AA33}вошёл на сервер.", GetPlayerRanks(playerid), GetFamilyName(PlayerInfo[playerid][pLeader]), PlayerInfo[playerid][pName]);
	   	SendClientMessageToAll(COLOR_YELLOW, strings);//FamilyInfo[PlayerInfo[playerid][pLeader]][fColor]
	}
	/*else if(PlayerInfo[playerid][pLeader] >= DoT)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s{FFFF00}: {33AA33}вошёл на сервер.", GetPlayerRanks(playerid), PlayerInfo[playerid][pName]);
	   	SendClientMessageToAll(COLOR_YELLOW, strings);
	}*/
//print("8");
//-----------------------------------------------------------------------------
	if( strcmp(PlayerInfo[playerid][pReferal], "No-One", true) &&//для рефералов
	  	strcmp(PlayerInfo[playerid][pReferal], "0", true))
	{   //если у игрока есть какой то учитель
		new referalname[MAX_PLAYER_NAME];
		strmid(referalname, PlayerInfo[playerid][pReferal], 0, strlen(PlayerInfo[playerid][pReferal]), MAX_PLAYER_NAME);
		//mysql_real_escape_string(referalname, referalname);
		if(CheckExistPlayer(playerid, referalname) == 0)
		{
		    format(strings, sizeof(strings), "CEPBEP: {33AA33}Извините, учётной записи %s нету в базе данных. (USE: /accept referal).", referalname);
		    SendClientMessage(playerid, COLOR_RED, strings);
		    strmid(PlayerInfo[playerid][pReferal], "No-One", 0, 16, 24);
		}
		else
		{
  			new giveplayerid = ReturnUser(referalname);
		    if( IsPlayerConnectedEx(giveplayerid) )
			{
				format(strings, sizeof(strings), "Ученик %s[%d] приветствует Вас наставник! ", PlayerInfo[playerid][pName], playerid);
				SendClientMessage(giveplayerid,  COLOR_LIGHTYELLOW, strings);
			}
		}
	}
//print("9");
	if(PlayerInfo[playerid][pMarried] == 1)
	{
		new marriedname[MAX_PLAYER_NAME];
		strmid(marriedname, PlayerInfo[playerid][pMarriedTo], 0, strlen(PlayerInfo[playerid][pMarriedTo]), MAX_PLAYER_NAME);
		//mysql_real_escape_string(marriedname, marriedname);
		if(CheckExistPlayer(playerid, marriedname) == 0)
		{
    		ClearMarriage(playerid);
 		    format(strings, sizeof(strings), "CEPBEP: {33AA33}Извините, учётной записи %s нету в базе данных. Вы разведены.", PlayerInfo[playerid][pMarriedTo]);
    		SendClientMessage(playerid, COLOR_RED, strings);
		}
		else
		{
 			new giveplayerid = ReturnUser(marriedname);
		    if( IsPlayerConnectedEx(giveplayerid) )
			{
				format(strings, sizeof(strings), "Ваш супруг %s[%d] только что зашёл в игру!", PlayerInfo[playerid][pName], playerid);
	    		SendClientMessage(giveplayerid, COLOR_LIGHTYELLOW, strings);
    		}
		}
	}
//print("10");
//==============================================================================
//для монитора
/*	PlayerInfo[playerid][pOffline] = 0;//пометили игрока онлайн
//GetPlayerIp(playerid, PlayerInfo[playerid][pIP], 16);
#if defined vw_sql//#endif
	new ToBase[109];//66+3+16+24 = 109
	format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d,`IP`='%s' WHERE `ID`=%d",//WHERE `ID`=%d//`Name`='%s'
		PlayerInfo[playerid][pOffline], PlayerInfo[playerid][pIP], PlayerInfo[playerid][pSQLID]);//playername//PlayerInfo[playerid][pSQLID]
	//mysql_query(ToBase);
	db_free_result(db_query(db_VW, ToBase));
#endif
*/

   	if(BizInfo[0][bTill] <= 0)
	{
		format(strings, sizeof(strings), "   Казна пуста ! В казне $%d", BizInfo[0][bTill]);
		SendClientMessage(playerid, COLOR_GREY, strings);
		Log(ERROR, strings);
	}
//print("11");
	if(numplayers > OnlineRecord)
	{
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		new ly, lmm, ld; getdate(ly,lmm,ld);
		format(OnlineRecordDate, sizeof(OnlineRecordDate), "%02d/%02d/%04d", ld,lmm,ly);
		format(OnlineRecordTime, sizeof(OnlineRecordTime), "%02d:%02d:%02d", lH,lM,lS);
		OnlineRecord = numplayers;
		SaveOnline();
//print("12");
		GivePlayerMoneyB(fjackpot, playerid, Jackpot);
		BizInfo[0][bTill] -= Jackpot;
		BizInfo[0][bImport] += Jackpot;
		OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
		format(strings, sizeof(strings), "{FFFFFF}%s[%d]: {FFFF00}вошёл %d-ым посетителем и получил бонус {33AA33}$%d.", PlayerInfo[playerid][pName], playerid, OnlineRecord, Jackpot);
		OOCNews(COLOR_LIGHTBLUE, strings);
//print("13");
	    new rand = random(1500); rand += 215;//для экономики
	    Jackpot += rand;
	    format(strings, sizeof(strings), "Lottery News: Jackpot поднят до $%d.", Jackpot);
		SendClientMessageToAll(COLOR_YELLOW, strings);
		SaveSettings();
	}
//print("14");

//==============================================================================
//для вход по месту выхода, т.к. при пролистывании перезаписываются переменные
	SetPVarInt(playerid, "FirstInterior", PlayerInfo[playerid][pInt]);
	SetPVarInt(playerid, "FirstVirtual", PlayerInfo[playerid][pVirtual]);
	SetPVarInt(playerid, "FirstLocal", PlayerInfo[playerid][pLocal]);

	if(PlayerInfo[playerid][pAdmin] > 0)
	{
		format(strings, sizeof(strings), "   Вы вошли как админ %d уровня.", PlayerInfo[playerid][pAdmin]);
		SendClientMessage(playerid, COLOR_SYSTEM, strings);//отсюда идёт задержка
	}
//print("15");
#if defined grandlarc//#endif
	grandlarc_OnPlayerConnect(playerid);
#else
	if(CurState[playerid] == PLAYER_STATE_SPECTATING)
	{   //если игрок спектатор
		TogglePlayerSpectating(playerid, 0);//откл. режим спектатора, чтобы появились кнопки выбора спауна
	}
#endif
//print("16");
	gPlayerLogged[playerid] = 1;//поднимаем флаг - игрок залогинелся - данные из файла загружены
	PlaySoundForPlayer(playerid, 21000);

//спаунить по месту выхода
	//gSpawn[playerid] = 0; SetPVarInt(playerid, "SpawnChange", 0);//спаунить по месту выхода
	//SetPlayerSpawn(playerid);//подменили инфу по месту спауна
	//SpawnPlayer(playerid);//спауним игрока вызывая ф-ию OnPlayerSpawn

	new strtmp[60+3+3+5+3];
	format(strtmp, sizeof(strtmp), "End OnPlayerLogin(playerid: %d, Int: %d, Virt: %d, Loc: %d)",
			playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
	SendClientMessage(playerid, COLOR_GREEN, strtmp);
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}//end OnPlayerLogin(playerid, password[])


stock DollahScoreUpdate(playerid)//запускается из OneMinutsTimer
{   //каждую минуту возвращает в TAB значение очков равное уровню
	if(!IsPlayerConnected(playerid)) return 1;
	if(gInTerrorsCount[playerid]) return 1;
	if(gInCTerrorsCount[playerid]) return 1;
	PlayerInfo[playerid][pLevel] = GetPlayerLevel(playerid, PlayerInfo[playerid][pScore]);
	OnPlayerChangeLevel(playerid);//для рефералов //проверили стал ли больше уровень
	SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);//установить очки в TAB равные уровню игрока
	return 1;
}


stock login_ChangePass(playerid)
{
/*		new dlgitem[93+24];
	    format(dlgitem, sizeof(dlgitem), "{FFFFFF}%s{A9C4E4}\nПожалуйста, придумайте \nлегко запоминаемый пароль \nи введите его ниже:", PlayerInfo[playerid][pName]);
		ShowPlayerDialogEx(playerid, CHANGEPASS_DIALOG, DIALOG_STYLE_INPUT, "Смена пароля", dlgitem, "Change", "");//RegistrationSTEP16
*/
	//if(GetPVarInt(playerid, "gPlayerAccount") == 1)
	//{
	new dlgitem[240];//46+75+24+34+37 + 24 = 240
    format(dlgitem, sizeof(dlgitem), "{0080FF}Учётная запись: {FFFFFF}%s{A9C4E4}\n\
\nПожалуйста, придумайте легко запоминаемый пароль \nи введите его ниже:\n", PlayerInfo[playerid][pName]);
	strcat(dlgitem, "\n{8CAA63}Примечание:\n");
	strcat(dlgitem, "\t- пароль не более 20 символов\n");
	strcat(dlgitem, "\t- пароль чувствителен к регистру\n");
	ShowPlayerDialogEx(playerid, CHANGEPASS_DIALOG, DIALOG_STYLE_INPUT, "Смена пароля", dlgitem, "Change", "Cancel");//RegistrationSTEP16
	//}
}
stock changepass_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != CHANGEPASS_DIALOG) return 1;
	new msgitem[256+1];
	if(!response) return 1;
	//new giveplayerid;

//RegistrationSTEP16
//ShowPlayerDialogEx(playerid, CHANGEPASS_DIALOG, DIALOG_STYLE_INPUT, "Регистрация на "#HostName, loginmsg, "OK", "Cancel");
	if(!strlen(inputtext)) return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /changepass [new password]");
	else if(strlen(inputtext) > 20) return SendClientMessage(playerid, COLOR_GRAYWHITE, "Пароль не должен превышать больше 20 символов!");
	for(new i=0; i<strlen(inputtext); i++)
	{
		switch(inputtext[i])
		{
			case '0' .. '9': { continue; }
			case 'A' .. 'Z': { continue; }
			case 'a' .. 'z': { continue; }
			default:
			{   //если символы отличны от 'A' .. 'Z' || 'a' .. 'z'
				SendClientMessage(playerid, COLOR_EMERALD, "ENTERING REJECTED. BAD PASSWORD!");
				SendClientMessage(playerid, COLOR_EMERALD, "Please choose another Password containing only 0-9 A-Z a-z");
				SendClientMessage(playerid, COLOR_EMERALD, "USE: /changepass [new password]");
			    return 1;
			}
		}
	}

	new ToBase[55+20+24], Field[34];//используется для нижнего запроса
	format(ToBase, sizeof(ToBase), "SELECT `Mail` FROM `players` WHERE `ID`=%d LIMIT 1", PlayerInfo[playerid][pSQLID]);//playername);//`Name` = '%s'
	/*mysql_query(ToBase); mysql_store_result();
	if(mysql_num_rows() > 0 && mysql_retrieve_row()) mysql_fetch_field_row(PlayerInfo[playerid][pMail], "Mail");
	else { mysql_free_result(); return SendClientMessage(playerid, COLOR_GRAYWHITE, "Ошибка с работой базы данных. Возможно Ваш аккаунт был удалён!"); }
	mysql_free_result();*/
	new DBResult:db_result = db_query(db_VW, ToBase);
	if( db_num_rows(db_result) )
	{	//если в базе нашло хоть одно значение
		db_get_field_assoc(db_result, "Mail", Field, sizeof(Field) );  strmid(PlayerInfo[playerid][pMail], Field, 0, strlen(Field), sizeof(Field));
	}
	else { db_free_result(db_result); return SendClientMessage(playerid, COLOR_GRAYWHITE, "Ошибка с работой базы данных. Возможно Ваш аккаунт был удалён!"); }
	db_free_result(db_result);

	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	new date[25+2+2+4+2+2];//37
	format(date, sizeof(date), "%02d.%02d.%04d|%02d:%02d",ld,lmm,ly, lH,lM);
	if(strcmp(php_host, "localhost", true))
	{//не localhost
		new strHTTP[92 + 24+34+24+20+16+37];
		format(strHTTP, sizeof(strHTTP), "%s/SendMailVW/SendNewPassword.php?Mail=%s&PlayerName=%s&Password=%s&IP=%s&PasswordDate=%s",
			HostName, PlayerInfo[playerid][pMail], PlayerInfo[playerid][pName], inputtext, PlayerInfo[playerid][pIP], date);
		HTTP(playerid, HTTP_GET, strHTTP, "", "HTTP_PasswordSendToMail");
	}
	format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Password`='%s' WHERE `ID`=%d", inputtext, PlayerInfo[playerid][pSQLID]);//playername);
	//mysql_query(ToBase);
	db_free_result(db_query(db_VW, ToBase));

	SetPVarInt(playerid, "gPlayerAccount", 2);

	format(msgitem, sizeof(msgitem), "Ваш пароль был успешно изменён на %s", inputtext);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	return 1;
}




stock login_OnPlayerSpawn(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{   //если игрок не залогинился и не зарегистрировался
    	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Извините, но этот сервер требует залогиниться перед тем как войти в игру! (Kicked)");
		IsKicked[playerid] = 1;
		return 1;
 	}
	if(PlayerInfo[playerid][pLevel] < 0) //-999 autoban
	{
		if(getdate() < PlayerInfo[playerid][pWarns] && PlayerInfo[playerid][pWarns] <= 365) //-999 autoban
		{
			format(strings, sizeof(strings), "CEPBEP: {33AA33}Ваш аккаунт заблокирован на %d дней !", PlayerInfo[playerid][pWarns] - getdate());
			SendClientMessage(playerid, COLOR_RED, strings);
			format(strings, sizeof(strings), "%s[%d] kicked, reason: account blocked !", PlayerInfo[playerid][pName], playerid);
			SendSystemMessage(COLOR_MAROON, strings, 1);

			Log(KICK, strings);
			IsKicked[playerid] = 1;
	        return 1;
		}
	}
	return 0;
}
stock login_OnPlayerRequestSpawn(playerid)
{
	if(IsPlayerNPC(playerid)) { return 1; }
	//if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	//if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	
	if(gPlayerLogged[playerid] == 1)//если игрок зарегистрирован
	{  //если игрок зашёл в игру
		//PlayerInfo[playerid][pHealth] = floatadd(PlayerInfo[playerid][pSHealth], 50.0);
		SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth]);//Кол-во жизней у игрока
		//SetPlayerHealthEx(playerid, 100.0);
	    SetPVarInt(playerid, "SpawnSelection", 1);//поднимаем флаг - выбор спауна произошёл
	    //SpawnPlayer(playerid);
		return 1;//- 1, игрок спавница.
	}
	else
	{   //если игрок не залогинился и не зарегистрировался
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerRequestSpawn", PlayerInfo[playerid][pName]);
		SendClientMessage(playerid, COLOR_RED,  strings);
		IsKicked[playerid] = 1;
 	}
	return 0;//- 0, игрок не спавница.
}



stock login_OnPlayerKeyState(playerid)
{
	//new strings[MAX_STRING];
	if(gPlayerLogged[playerid] == 0 && !GetPVarInt(playerid, "Intro"))
	{  
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerKeyStateChange [%d]", PlayerInfo[playerid][pName],  GetPVarInt(playerid, "gShowDialog"));
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	if(gPlayerSpawned[playerid] == 0 && CurState[playerid] != PLAYER_STATE_SPECTATING)// && introtimer[playerid] == -1
	{
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no spawned before OnPlayerKeyStateChange", PlayerInfo[playerid][pName]);
		//SendClientMessageToAll(COLOR_RED, strings);
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
 	return 0;
}


stock login_OnPlayerSelectedMenuRow(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerSelectedMenuRow", PlayerInfo[playerid][pName]);
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	return 0;
}
stock login_OnPlayerInterior(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{   //если игрок не залогинился и не зарегистрировался
		//new strings[MAX_STRING];
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerInteriorChange", PlayerInfo[playerid][pName]);
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	return 0;
}
stock login_OnPlayerDeath(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{   //если игрок не залогинился и не зарегистрировался
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerDeath", PlayerInfo[playerid][pName]);
 		SendClientMessage(playerid, COLOR_RED,  strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	return 0;
}



stock login_OnPlayerEnterCheckpoint(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerEnterCheckpoint", PlayerInfo[playerid][pName]);
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	return 0;
}

stock login_OnPlayerPickUp(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerPickUpPickup", PlayerInfo[playerid][pName]);
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	return 0;
}


stock login_OnPlayerClickMap(playerid)
{
	if(gPlayerLogged[playerid] == 0)
	{
		//new strings[MAX_STRING];
 		format(strings, sizeof(strings), "CEPBEP: %s был кикнут, причина: no login before OnPlayerClickMap", PlayerInfo[playerid][pName]);
		SendClientMessage(playerid, COLOR_RED, strings);
		IsKicked[playerid] = 1;
		return 1;
 	}
	return 0;
}



