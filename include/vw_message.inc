

stock ABroadCast(color, const message[], level)
{   //для уведомления админов уровня level
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pAdmin] == 4) continue;
		if(GetPVarInt(i, "gAdmin") == 1) continue;
		if(PlayerInfo[i][pAdmin] == level)
		{
			SendClientMessage(i, color, message);
		}
	}
}

stock ReasonLeaveServer(playerid, reason)
{
	new strreason[10]; new strtmp[MAX_STRING];
	new pip[16]; GetPlayerIp(playerid, pip, sizeof(pip));
	if(GameRestart != 1) //если не рестарт
	{

	    switch(reason)
	    {
	        case 0:
			{
				strcat(strreason, "TimedOut");
				format(strtmp, sizeof(strtmp), "%s[%d] ip:%s left the server. (%s)", PlayerName(playerid),playerid, pip, strreason);
			    //Log(TIMEOUT, strtmp);
			}
	        case 1:
			{
				strcat(strreason, "Leaving");
				format(strtmp, sizeof(strtmp), "%s[%d] ip:%s left the server. (%s)", PlayerName(playerid),playerid, pip, strreason);
				//Log(TIMEOUT,strtmp);
			}
	        case 2:
	        {
	        	strcat(strreason, "Kicked");
				format(strtmp, sizeof(strtmp), "%s[%d] ip:%s left the server. (%s)", PlayerName(playerid),playerid, pip, strreason);
	    		//Log(TIMEOUT,strtmp);
			}
	    }
	}
	//SendSystemMessage(COLOR_MAROON, strtmp, 2);
	return strtmp;
}

stock SendAllAdminMessage(color, const message[], level)
{   //для уведомления админов уровня level или выше
	//#pragma unused level
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(GetPVarInt(i, "gAdmin") == 1) continue;
		if(PlayerInfo[i][pAdmin] >= level || IsPlayerAdmin(i))
		{
			SendClientMessageEx(i, color, message);
		}
	}
}
/*stock SendAllAdminMessage(color, const message[], level)
{   //для уведомления админов уровня level или выше
	//#pragma unused level
	for(new i=0; i<GetMaxPlayers(); i++)
	{
		if( !IsPlayerConnected(i) ) continue;
		if(	CallRemoteFunction("GetAdminLevel", "d", i) >= level ||
			IsPlayerAdmin(i))
		{
			SendClientMessage(i, color, message);
		}
	}
}*/

stock SendAdminsMessage(playerid, const message[])
{   //чат только для админов
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "%d Admin {FFFFFF}%s[%d]: {2587CE}%s", PlayerInfo[playerid][pAdmin], PlayerName(playerid), playerid, message);
	//AdminChat(ADMINS_MESSAGE_COLOR, strings);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//if(GetPVarInt(i, "gAdmin") == 1) continue;
		if(PlayerInfo[i][pAdmin] >= 1 || IsPlayerAdmin(i))
		{
			SendClientMessage(i, ADMINS_MESSAGE_COLOR, strings);
		}
	}
	SetPVarInt(playerid, "gChatSwitcher", AdminsChat);
	format(strings, sizeof(strings), "~r~A ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}


new MegaphoneSounds[][] =
{
	// SPLIT COMMA
	// SOUND ID , DESCRIPTION
	{"9605,Остановитесь. Вы окружены!"},//Give up. You're surrounded!"},
	{"9612,Мы знаем где Вы!"},//We know you're in there!"},
	{"10200,Эй Вы! Полиция. Остановитесь!"},//Hey you! Police. Stop!"},
	{"15800,Это - Полицейский Отдел Los Santos; Стойте где Вы стоите!"},//This is the Los Santos Police Department; Stay where you are!"},
	{"15801,Остановитесь! Или мы откроем огонь!"},//Freeze! Or we will open fire"},
	{"15802,Go! Go! Go!"},
	{"34402,Полиция! Не двигаться!"},//Police! Don't move!"},
	{"34403,Выйти из машины с поднятыми руками !"},//Get outta the car with your hands in the air!"},
	{"15825,Полиция Los Santos. Прижмитесь вправо..."}// Вы сумасшедшие? Вы убьете нас всех!"}//LSPD. Stop right... are you insane? You'll kill us all!"}
};

stock megaphone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != MEGAPHONE_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) return SendClientMessage(playerid, COLOR_WHITE, "Cancel");
	new soundid, tw1 = 0;
	for(new w1 = 0; w1 < sizeof(MegaphoneSounds); w1++)
	{
		if(tw1 != listitem)
		{
			tw1++;
			continue;
		}
		new tmp1[2][128];
		split(MegaphoneSounds[w1], tmp1, ',');
		soundid = strval(tmp1[0]);
		break;
	}
	//new Float:pos[4];
	//GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	//PlaySoundForPlayersInRange(soundid, 15.0, pos[0], pos[1], pos[2], 15);
	PlaySoundForPlayerInRange(playerid, soundid, 100.0);
	return 1;
}


stock message_OnPlayerDisconnect(playerid, reason)
{
	new strreason[10]; new strtmp[MAX_STRING];
	if(GameRestart != 1)
	{   //если не рестарт
	    switch(reason)
	    {
	        case 0:
			{
				strcat(strreason, "TimedOut");
				format(strtmp, sizeof(strtmp), "%s[%d] ip:%s left the server. (TimeOut)", PlayerName(playerid),playerid, PlayerInfo[playerid][pIP]);
			    Log(TIMEOUT, strtmp);
			}
	        case 1:
			{
				strcat(strreason, "Leaving");
				format(strtmp, sizeof(strtmp), "%s[%d] ip:%s left the server. (Leaving)", PlayerName(playerid),playerid, PlayerInfo[playerid][pIP]);
				//Log(TIMEOUT,strtmp);
			}
	        case 2:
	        {
	        	strcat(strreason, "Kicked");
				format(strtmp, sizeof(strtmp), "%s[%d] ip:%s left the server. (Kicked)", PlayerName(playerid),playerid, PlayerInfo[playerid][pIP]);
	    		//Log(TIMEOUT,strtmp);
			}
	    }
		SendSystemMessage(COLOR_MAROON, strtmp, 2);
	}
}
//##############################################################################//
//                                                                              //
//                               ФУНКЦИИ СООБЩЕНИЙ                              //
//                                                                              //
//##############################################################################//
//начинаются на Send


stock OOC(playerid, Float:radi, const message[],col1,col2,col3,col4,col5)
{   //для выключения общего чата
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "[%d:%02d:%02d] %s", lH,lM,lS, message);
	new Float:posx, Float:posy, Float:posz;
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(GetPVarInt(i, "gOoc") == 0)
		{
			GetPlayerPos(i, posx, posy, posz);
			tempposx = (oldposx - posx);	tempposy = (oldposy - posy);	tempposz = (oldposz - posz);
			if(((tempposx < radi/16) && (tempposx > -radi/16)) &&
				((tempposy < radi/16) && (tempposy > -radi/16)) &&
				((tempposz < radi/16) && (tempposz > -radi/16)))
			{
				SendClientMessageEx(i, col1, strings);
			}
			else if(((tempposx < radi/8) && (tempposx > -radi/8)) &&
				((tempposy < radi/8) && (tempposy > -radi/8)) &&
				((tempposz < radi/8) && (tempposz > -radi/8)))
			{
				SendClientMessageEx(i, col2, strings);
			}
			else if(((tempposx < radi/4) && (tempposx > -radi/4)) &&
				((tempposy < radi/4) && (tempposy > -radi/4)) &&
				((tempposz < radi/4) && (tempposz > -radi/4)))
			{
				SendClientMessageEx(i, col3, strings);
			}
			else if(((tempposx < radi/2) && (tempposx > -radi/2)) &&
				((tempposy < radi/2) && (tempposy > -radi/2)) &&
				((tempposz < radi/2) && (tempposz > -radi/2)))
			{
				SendClientMessageEx(i, col4, strings);
			}
			else if(((tempposx < radi) && (tempposx > -radi)) &&
				((tempposy < radi) && (tempposy > -radi)) &&
				((tempposz < radi) && (tempposz > -radi)))
			{   //если игрок максимально удален от источника сообщения
				SendClientMessageEx(i, col5, strings);
			}
		}
	}
}
stock OOCNews(color, const message[])
{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(GetPVarInt(i, "gNews") == 1) continue;
		SendClientMessageEx(i, color, message);
	}
}
stock JobNews(color, const message[])
{
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "[%d:%02d:%02d] %s", lH,lM,lS, message);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(GetPVarInt(i, "gJob") == 1) continue;
		SendClientMessageEx(i, color, strings);
	}
}

stock ProxDetector(playerid, Float:radi, const message[], col1,col2,col3,col4,col5)
{   //ф-ия отправки сообщения всем игрокам находящимся в заданом радиусе в зависимости от удалённсти разными цветами
	if( !IsPlayerConnectedEx(playerid)
		 || spectateid[playerid] != MAX_PLAYERS-1) return 1;
		 //если вы зритель, то не оповещать
	new Float:oldposx, Float:oldposy, Float:oldposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	//radi = 2.0; //Trigger Radius
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(	!IsPlayerConnectedEx(i)
			|| spectateid[i] != MAX_PLAYERS-1) continue;
		if(	GetPVarInt(i, "BigEar") == 0)
		{   //если подслушка выключена, то вы слышите как и все люди
			if(	PlayerInfo[i][pLocal] != PlayerInfo[playerid][pLocal]) continue;
			if(	PlayerInfo[i][pVirtual] != PlayerInfo[playerid][pVirtual]) continue;
			if(	PlayerInfo[i][pInt] != PlayerInfo[playerid][pInt]) continue;
			
			new Float:posx, Float:posy, Float:posz;
			GetPlayerPos(i, posx, posy, posz);
			new Float:tempposx, Float:tempposy, Float:tempposz;
			tempposx = (oldposx -posx);	tempposy = (oldposy -posy);	tempposz = (oldposz -posz);
			//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);

			if(((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
			{   //если игрок почти рядом с вами
				SendClientMessageEx(i, col1, message);
			}
			else if(((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
			{
				SendClientMessageEx(i, col2, message);
			}
			else if(((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
			{
				SendClientMessageEx(i, col3, message);
			}
			else if(((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
			{
				SendClientMessageEx(i, col4, message);
			}
			else if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
			{	//если игрок почти максимально удалён от вас но в пределах заданного радиуса
				SendClientMessageEx(i, col5, message);
			}
		}
		else if(GetPVarInt(i, "BigEar") == 1) SendClientMessageEx(i, col1, message);
		//else if(GetPVarInt(i, "BigEar") >= 10) SendClientMessageEx(i, col1, message);
	}
	return 1;
}
stock ProxDetectorTelephone(playerid, color, const message[])
{   //для прослушки
	if( IsPlayerConnectedEx(playerid) )
	{
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(GetPVarInt(i, "BigEar") == 2 && PlayerInfo[playerid][pAccount] == 0)
			{   //если у этого игрока включена прослушка, то также получать эти сообщения
				SendClientMessageEx(i, color, message);
			}
		}
		SendClientMessage(playerid, COLOR_LILAC, message);//чтобы работал для АФК игроков
	}
}


stock CheckOnIP1(playerid, const message[])
{
    new dight;
    for(new line; line < strlen(message); ++line)
    {
        if('0' <= message[line] <= '9')
        {
            do
            {
                if(message[line] == '.') ++dight;
                ++line;
            }
            while(('0' <= message[line] <= '9') || message[line] == '.' || message[line] == ':');
        }
    }
    if(dight >= 3)
	{
		new text[64+128+24];
		format(text, sizeof(text), "[ 1 ] Попытка рекламы от %s[%d] IP адреса: %s",
			PlayerName(playerid), playerid, message);
   		SendAllAdminMessage(COLOR_MAROON, text, 3);
		return 1;
	}
    return 0;
}
stock CheckOnIP2(playerid, const message[])
{
	new i, digits, numbers, flashlight;
	if((i = strfind(message, ".", false, 0)) >= 0)
	{
		for(++i; ; i++)
		{
			switch(message[i])
			{
				case ' ': if(digits > 0) continue;
				case '0'..'9': numbers ++;
				case '.': digits ++;
				case ':': flashlight ++;
				default: break;
			}
		}
 	}
 	//printf("Точки: %d, Числа: %d, Двоеточие: %d", digits, numbers, flashlight);
	if((numbers >= 6 && digits >= 2) ||
		(numbers >= 10 && (flashlight >= 1 && digits >= 1)))
	{
		new text[64+128+24];
		format(text, sizeof(text), "[ 2 ] Попытка рекламы от %s[%d] IP адреса: %s", PlayerName(playerid), playerid, message);
		SendAllAdminMessage(COLOR_MAROON, text, 3);
	    return 1;
	}
	return 0;
}

//==============================================================================
//КОМАНДНЫЕ СООБЩЕНИЯ
/*stock AdminChat(color, const message[])
{   //для админ чата
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pAdmin] >= 1)
		{
			SendClientMessage(i, color, message);
		}
	}
}*/
stock SendHQMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {FF0000}Admin {FFFFFF}%s: {FF0000}%s", lH,lM,lS, PlayerName(playerid), message);
	SendClientMessageToAll(COLOR_RED, strings);
	SetPVarInt(playerid, "gChatSwitcher", HQChat);

	format(strings, sizeof(strings), "~r~HQ ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}

stock SendOOCMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s[%d]: %s", PlayerName(playerid), playerid, message);
	OOC(playerid, 6000.0, strings, COLOR_GRAD6,COLOR_GRAD5,COLOR_GRAD4,COLOR_GRAD3,COLOR_GRAD2);
	SetPVarInt(playerid, "gChatSwitcher", OOChat);

	format(strings, sizeof(strings), "~r~O ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}

stock SendGovMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s {FFFFFF}%s[%d]: {0080FF}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
	//if(strlen(strings) > (MAX_STRING - 30-strlen(GetPlayerRanks(playerid))-strlen(PlayerName(playerid))-3) )
	if(strlen(strings) > 128)//sizeof(strings))
	{
		format(strings, sizeof(strings), "   Ваше сообщение в %d символов не можут быть отправлено, т.к. кол-во символов больше %d!", strlen(strings), 128);//sizeof(strings)
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
	OOCNews(COLOR_LIGHTBLUE, strings);
	//OOCNews(COLOR_HERBAL, "|__________________________________________________________________________________________________________|");
	SetPVarInt(playerid, "gChatSwitcher", GovernmentChat);
	return 1;
}
stock SendMegaphoneMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	if(gTagForPlayer[playerid] != 0)
	{   //если ник НЕ скрыт
    	format(strings, sizeof(strings), "%s %s:o< %s", GetPlayerRanks(playerid), PlayerName(playerid), message);
    }
    else
    {
    	format(strings, sizeof(strings), "%s:o< %s", GetPlayerRanks(playerid), message);
	}
	ProxDetector(playerid, 100.0, strings,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
	SetPVarInt(playerid, "gChatSwitcher", MegaphoneChat);

	format(strings, sizeof(strings), "~r~M ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}
stock SendWalkietalkieChatMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "TruckDriver {FFFFFF}%s:{FF9900}o< %s", PlayerName(playerid), message);
	SendJobMessage(16, COLOR_LIGHTORANGE, strings);//SendJobMessage(job, color, strings[])
	SetPVarInt(playerid, "gChatSwitcher", WalkietalkieChat);
	format(strings, sizeof(strings), "~r~WT ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}
/*stock SendWhisperMessage(playerid, text[])
{
	new idx;
	if(PlayerInfo[playerid][pMuted] > 0) return SendClientMessage(playerid, COLOR_GREY, "   Вы не можете говорить, Вы заглушены!");
	new tmp = strtok(text, idx);
	if(!strlen(tmp)) return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: (/w)isper [playerid/PartOfName] [whisper text]");
	new giveplayerid = ReturnUser(tmp);
	if(!IsPlayerConnected(giveplayerid)) return SendClientMessage(playerid, COLOR_GREY, "Invalid ID");
	if(GetPVarInt(giveplayerid, "gHidePM") >  0) return SendClientMessage(playerid, COLOR_GREY, "   Этот игрок заблокировал Шепот !");

	if((IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid) ||
		PlayerInfo[playerid][pAdmin] >= 1) && spectateid[giveplayerid] == MAX_PLAYERS-1)
	{
		new message = strrest(text,idx);
		if(!strlen(message)) return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: (/w)isper [playerid/PartOfName] [whisper text]");
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "{FFFF99}whisper %s", message);
		SendPlayerMessageToPlayer(giveplayerid, playerid, strings);
		PlaySoundForPlayer(giveplayerid, 1085);
		format(strings, sizeof(strings), "Whisper sent to %s[%d]", PlayerName(giveplayerid), giveplayerid);
		return SendClientMessage(playerid,  COLOR_LIGHTYELLOW, strings);
	}
	else return SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");

	gChatSwitcher[playerid] = WhisperChat;
}*/
stock SendMEMessage(playerid, const message[])
{
	//AudioMessage(playerid, message); // В игре скажет вам по русски слово текст.
	new strtmp[MAX_CHATBUBBLE_LENGTH+1];//144+1
	format(strtmp, sizeof(strtmp), " %s", message);
	SetPlayerChatBubble(playerid, strtmp, ACTION_COLOR,30.0,10000);
	//30.0 - The distance from where players are able to see the chat bubble
	//10000 - The time in miliseconds the bubble should be displayed for.
//	format(strtmp, sizeof(strtmp), "%s{FFFF00} - сказал {FFFFFF}%s", message, PlayerName(playerid));
	if(PlayerInfo[playerid][pMuted] == 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%s {FFFF00}%s", PlayerName(playerid), message);
		ProxDetector(playerid, 30.0, strtmp, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
	}
	//printf("%s", strings);
	SetPVarInt(playerid, "gChatSwitcher", MEChat);
	//OnePlayAnim(playerid, "PED", "IDLE_CHAT", 4.0, 0, 0, 0, 0, 0);
	format(strtmp, sizeof(strtmp), "~r~ME ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strtmp);
}
stock SendShoutMessage(playerid, const message[])
{
	//if( !IsPlayerConnectedEx(playerid) ) return 1;
	//if( spectateid[playerid] != MAX_PLAYERS-1 ) return 1;

	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s shout: %s!", PlayerName(playerid), message);

	new Float:oldposx, Float:oldposy, Float:oldposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(	!IsPlayerConnectedEx(i)
			|| spectateid[i] != MAX_PLAYERS-1) continue;
		if(	GetPVarInt(i, "BigEar") == 0)
		{   //если подслушка выключена, то вы слышите как и все люди
			new Float:posx, Float:posy, Float:posz;
			GetPlayerPos(i, posx, posy, posz);
			new Float: radi = 60.0;

			//new strtmp[512];
			//format(strtmp, 512, "http://translate.google.kg/translate_tts?ie=UTF-8&q=%s&tl=ru&prev=input", message);
			//PlayAudioStreamForPlayer(i, strtmp, oldposx, oldposy, oldposz, radi, 1);

			new Float:tempposx, Float:tempposy, Float:tempposz;
			tempposx = (oldposx-posx);	tempposy = (oldposy-posy);	tempposz = (oldposz-posz);
			//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);

			if(((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
			{   //если игрок почти рядом с вами
				SendClientMessageEx(i, COLOR_GRAD5, strings);
			}
			else if(((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
			{
				SendClientMessageEx(i, COLOR_GRAD4, strings);
			}
			else if(((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
			{
				SendClientMessageEx(i, COLOR_GRAD3, strings);
			}
			else if(((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
			{
				SendClientMessageEx(i, COLOR_GRAD2, strings);
			}
			else if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
			{	//если игрок почти максимально удалён от вас но в пределах заданного радиуса
				SendClientMessageEx(i, COLOR_GRAD1, strings);
			}
		}
		else if(GetPVarInt(i, "BigEar") == 1) SendClientMessageEx(i, COLOR_GRAD5, strings);
	}
	//ProxDetector(playerid, 60.0, strings, COLOR_GRAD5,COLOR_GRAD4,COLOR_GRAD3,COLOR_GRAD2,COLOR_GRAD1);

	if(!IsPlayerInAnyVehicle(playerid))	OnePlayAnim(playerid, "RIOT", "RIOT_shout",3.0,0,1,1,0,0);
	SetPVarInt(playerid, "gChatSwitcher", ShoutChat);
	format(strings, sizeof(strings), "~r~S ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
	//return 1;
}

stock SendRPMessage(playerid, const message[])
{
	new strtmp[MAX_STRING];
	format(strtmp, sizeof(strtmp), "%s сказал: (( {FFFFFF}%s{CC99FF} ))", PlayerName(playerid), message);
	if(PlayerInfo[playerid][pMuted] == 0)
	{
		//format(strtmp, sizeof(strtmp), "{FFFFFF}%s {FFFF00}%s", PlayerName(playerid), message);
		ProxDetector(playerid, 60.0, strtmp, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
	}
	SetPVarInt(playerid, "gChatSwitcher", RPChat);
	format(strings, sizeof(strings), "~r~B ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}

stock SendLocalMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s local says: %s", PlayerName(playerid), message);
	SetPVarInt(playerid, "gChatSwitcher", LocalChat);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
		if(	PlayerInfo[playerid][pLocal] != PlayerInfo[i][pLocal]) continue;
		if(	PlayerInfo[playerid][pLocal] == FREEROAM) continue;
		if(gPlayerSpawned[playerid] == 0)
		{
			if(gPlayerSpawned[i] == 1) continue;
			SendClientMessage(i, COLOR_LIGHTYELLOW, strings);
		}
		else
		{
			if(gPlayerSpawned[i] == 0) continue;
			SendClientMessage(i, COLOR_LIGHTYELLOW, strings);
		}
	}
	format(strings, sizeof(strings), "~r~L ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}

stock SendDepartmentMessage(playerid, const message[])
{
	//new cmd[20], idx, tmp[128], message[MAX_STRING];
	//new giveplayerid;
	//new strings[MAX_STRING];
	if(PlayerInfo[playerid][pMember] == DoT)
	{
		format(strings, sizeof(strings), "• %s {FFFFFF}%s[%d]: {33CCCC}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
		SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strings);
		SendTeamMessage(FBI, COLOR_DARKTURQUOISE, strings);
		SendTeamMessage(DoD, COLOR_DARKTURQUOISE, strings);
		SendTeamMessage(DoH, COLOR_DARKTURQUOISE, strings);
		SendTeamMessage(DoJ, COLOR_DARKTURQUOISE, strings);
		SendTeamMessage(DoE, COLOR_DARKTURQUOISE, strings);
	}
	else if(PlayerInfo[playerid][pMember] == FBI)
	{
		format(strings, sizeof(strings), "° %s {FFFFFF}%s[%d]: {99CCFF}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
		SendTeamMessage(DoT, COLOR_PALEPURPLE, strings);
		SendTeamMessage(FBI, COLOR_PALEPURPLE, strings);
		SendTeamMessage(DoD, COLOR_PALEPURPLE, strings);
		SendTeamMessage(DoH, COLOR_PALEPURPLE, strings);
		SendTeamMessage(DoJ, COLOR_PALEPURPLE, strings);
		SendTeamMessage(DoE, COLOR_PALEPURPLE, strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoD)
	{
		format(strings, sizeof(strings), "* %s {FFFFFF}%s[%d]: {339966}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
		SendTeamMessage(DoT, COLOR_EMERALD, strings);
		SendTeamMessage(FBI, COLOR_EMERALD, strings);
		SendTeamMessage(DoD, COLOR_EMERALD, strings);
		SendTeamMessage(DoH, COLOR_EMERALD, strings);
		SendTeamMessage(DoJ, COLOR_EMERALD, strings);
		SendTeamMessage(DoE, COLOR_EMERALD, strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoH)
	{
		format(strings, sizeof(strings), "+ %s {FFFFFF}%s[%d]: {FF00FF}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
		SendTeamMessage(DoT, COLOR_MAUVE, strings);
		SendTeamMessage(FBI, COLOR_MAUVE, strings);
		SendTeamMessage(DoD, COLOR_MAUVE, strings);
		SendTeamMessage(DoH, COLOR_MAUVE, strings);
		SendTeamMessage(DoJ, COLOR_MAUVE, strings);
		SendTeamMessage(DoE, COLOR_MAUVE, strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoJ)
	{
		format(strings, sizeof(strings), "‡ %s {FFFFFF}%s[%d]: {99CC00}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
		SendTeamMessage(DoT, COLOR_HERBAL, strings);
		SendTeamMessage(FBI, COLOR_HERBAL, strings);
		SendTeamMessage(DoD, COLOR_HERBAL, strings);
		SendTeamMessage(DoH, COLOR_HERBAL, strings);
		SendTeamMessage(DoJ, COLOR_HERBAL, strings);
		SendTeamMessage(DoE, COLOR_HERBAL, strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoE)
	{
		format(strings, sizeof(strings), "† %s {FFFFFF}%s[%d]: {FFCC99}%s", GetPlayerRanks(playerid), PlayerName(playerid), playerid, message);
		//SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_LIGHTBROWN, strings);
		SendTeamMessage(DoT, COLOR_LIGHTBROWN, strings);
		SendTeamMessage(FBI, COLOR_LIGHTBROWN, strings);
		SendTeamMessage(DoD, COLOR_LIGHTBROWN, strings);
		SendTeamMessage(DoH, COLOR_LIGHTBROWN, strings);
		SendTeamMessage(DoJ, COLOR_LIGHTBROWN, strings);
		SendTeamMessage(DoE, COLOR_LIGHTBROWN, strings);
	}
	else SendClientMessage(playerid, COLOR_GREY, "   Вы не член министерства !");
	SetPVarInt(playerid, "gChatSwitcher", DepartmentsChat);
	format(strings, sizeof(strings), "~r~D ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
}

stock SendRadioMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	if(PlayerInfo[playerid][pMember] == DoT)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {33CCCC}%s, конец связи.", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strings);
		//printf("%s", strings);
	}
	else if(PlayerInfo[playerid][pMember] == FBI)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {99CCFF}%s, конец связи.", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendTeamMessage(FBI, COLOR_PALEPURPLE, strings);
		//printf("%s", strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoD)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {339966}%s, конец связи.", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendTeamMessage(DoD, COLOR_EMERALD, strings);
		//printf("%s", strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoH)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {FF00FF}%s, конец связи.", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendTeamMessage(DoH, COLOR_MAUVE, strings);
		//printf("%s", strings);
	}
	else if(PlayerInfo[playerid][pMember] == DoE)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {FFCC99}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		//SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_LIGHTBROWN, strings);
		SendTeamMessage(DoE, COLOR_LIGHTBROWN, strings);
	}
	else SendClientMessage(playerid, COLOR_GREY, "   Вы не член министерства !");
	SetPVarInt(playerid, "gChatSwitcher", RadioChat);
	format(strings, sizeof(strings), "~r~R ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
	//return 1;
}

stock SendFactionMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
    if(PlayerInfo[playerid][pMember] == LCN)
    {
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {00FFFF}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendFamilyMessage(PlayerInfo[playerid][pMember], strings);
	}
    else if(PlayerInfo[playerid][pMember] == Yakuza)
    {
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {00FFFF}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendFamilyMessage(PlayerInfo[playerid][pMember], strings);
	}
    else if(PlayerInfo[playerid][pMember] == DoJ)
    {
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {00FFFF}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendFamilyMessage(PlayerInfo[playerid][pMember], strings);
	}
	else if(PlayerInfo[playerid][pMember] == Hitman)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {00FFFF}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendFamilyMessage(PlayerInfo[playerid][pMember], strings);
	}
	else if(PlayerInfo[playerid][pMember] == SAN)
	{
		format(strings, sizeof(strings), "%s {FFFFFF}%s: {FFCC00}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendFamilyMessage(PlayerInfo[playerid][pMember], strings);
	}
	else if(IsAGangs(playerid))
    {
		format(strings, sizeof(strings), "%s %s: %s", GetPlayerRanks(playerid), PlayerName(playerid), message);
		SendFamilyMessage(PlayerInfo[playerid][pMember], strings);
	}
	SetPVarInt(playerid, "gChatSwitcher", FamilyChat);
	format(strings, sizeof(strings), "~r~F ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
	//return 1;
}
stock SendNewsMessage(playerid, const message[])
{
	//new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s {FFFFFF}%s: {FF9900}%s", GetPlayerRanks(playerid), PlayerName(playerid), message);
	OOCNews(COLOR_PURPLE,strings);
	SetPVarInt(playerid, "gChatSwitcher", NewsChat);
	format(strings, sizeof(strings), "~r~N ~g~$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
	//return 1;
}
//------------------------------------------------------------------------------
stock SendTeamMessage(member, color, const message[])
{
	//new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	//format(strings, sizeof(strings), "[%d:%02d:%02d] %s", lH,lM,lS, strings);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] == member || (PlayerInfo[i][pMember] == DoJ && GetPVarInt(i, "BigEar") == member))
		{
			if(IsACop(i) && !gOnDuty[i]) continue;
			SendClientMessage(i, color, message);
		}
	}
}
stock SendFamilyMessage(family, const message[])//SendGangsMessage
{   //вызываеться покоманде /f
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] == family && GetPVarInt(i, "gFam") == 0)
		{
			SendClientMessageEx(i, FamilyInfo[family][fColor], message);
		}
	}
}
stock SendTeamBeepMessage(playerid, color, const message[])
{
	//new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] %s", lH,lM,lS, message);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pTeam] == PlayerInfo[playerid][pTeam])
		{
			format(strings, sizeof(strings), "%s {FFFFFF}%s: {00FFFF}%s",
				GetPlayerRanks(playerid), PlayerName(playerid), message);
			SendClientMessageEx(i, color, strings);
		}
	}
}


stock SendJobMessage(job, color, const message[])
{
	//new strings[MAX_STRING];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	format(strings, sizeof(strings), "[%02d:%02d:%02d] %s", lH,lM,lS, message);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pJob] == job && PlayerInfo[i][pMuted] == 0)
		{
			SendClientMessageEx(i, color, strings);
		}
	}
}

//для IRC
stock SendIRCMessage(channel, color, const message[])
{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayersChannel[i] == channel && !PlayerInfo[i][pMuted])
		{
			SendClientMessageEx(i, color, message);
		}
	}
}

stock SendPagerMessage(playerid)//, string[] //const
{
	if(!IsPlayerInAnyVehicle(playerid)) return 1;
    //if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;

	//new strtmp[42+8+10];//{FFFFFF}%s's{0080FF} по цене {33AA33}$%d
    //format(message, sizeof(message), "Плата за заправку на %.1f л. - $%d.", FillUp, CostFuel);
    //SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	//PlayAudioStreamForPlayerEx(playerid, "pager.wav");
	PlaySoundForPlayer(playerid, SOUND_DOOR_BUZZER);
    PlayerTextDrawSetStringEx(playerid, txdPager[playerid], RusToGame(PagerMessage));
    return 1;
}

stock SendErr(playerid,text[])
{
	new idx[144];
	format(idx, 144, "{4595B2}[Ошибка] {ffffff}%s",text);
	SendClientMessage(playerid, COLOR_ERROR, idx);
	return 1;
}
stock SendSucc(playerid,text[])
{
	new idx[144];
	format(idx, 144, "{5AAB68}[Успешно] {ffffff}%s",text);
	SendClientMessage(playerid, COLOR_ERROR, idx);
	return 1;
}
