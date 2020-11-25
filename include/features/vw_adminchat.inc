//для системной панели
new CurrentChatLines = 49;

stock SendSystemMessage(color, const message[], level)
{
	if(level < 1 || level > 9) return 1;
	if(strlen(message) < 1 || strlen(message) >= 128) return 1;
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);

	#pragma unused color
/*
//много флуда
	new strtmp[MAX_LENGHT];//148
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
   //посылаем всем у кого выключена системная панель, но уровень администратора выше указанного
		if( !IsPlayerConnectedEx(i) ) continue;
		if(GetPVarInt(i, "gAdmin") == 1) continue;
		if( TextDrawShowMessage[i] == true ) continue;
		if( PlayerInfo[i][pAdmin] < level ) continue;
		format(strtmp, sizeof(strtmp), "[%02d:%02d:%02d] %s", lH,lM,lS, message);//~h~
		SendClientMessage(i, color, strtmp);
	}
*/
	//format(strtmp, sizeof(strtmp), "[%02d:%02d:%02d] %s~n~", lH,lM,lS, message);//~h~
	//новая строка добавляется в конец списка, на экран выводится всегда 5-ой строкой

	for(new l = 0; l < MAX_LINES-1; l++)//50
	{   //смещаем
		strmid( AdminMessageString[l], AdminMessageString[l+1], 0, strlen(AdminMessageString[l+1]), MAX_LENGHT);
	}
	//ВЫВОДИМ на экран
	new txdText[775];//23 + 5*148 + 12 = 775
	format(AdminMessageString[MAX_LINES-1], MAX_LENGHT, "[%02d:%02d:%02d] %s~n~", lH,lM,lS, message);

	for(new l = 5-1; l >= 0; l--)
	{
		strcat(txdText, AdminMessageString[CurrentChatLines-l]);
	}
	TextDrawSetStringEx(txdSystemMessage, txdText);
	return 1;
}


//stock OnPlayerKeyAdminMessage(playerid, newkeys, oldkeys)
stock adminchat_OnPlayerKeyState(playerid, newkeys, oldkeys)
{
	if(TextDrawShowMessage[playerid] == true)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    if(newkeys == KEY_WALK+KEY_ANALOG_RIGHT && oldkeys == KEY_WALK)
		 	{
			    if(CurrentChatLines > 4)
			    {
				    new txdText[MAX_LENGHT*5];
					CurrentChatLines = CurrentChatLines-5;
					for(new l = 5-1; l >= 0; l--)
					{
						strcat(txdText, AdminMessageString[CurrentChatLines-l]);
					}
					TextDrawSetStringEx(txdSystemMessage, txdText);
			        SendClientMessage(playerid, COLOR_GREY, "   Вы подняли чат. НЕ забудьте опустить!");
		        }
		 	}
		    if(newkeys == KEY_WALK+KEY_ANALOG_LEFT && oldkeys == KEY_WALK)
			{
		    	if(CurrentChatLines < 49)
		    	{
			    	new txdText[MAX_LENGHT*5];
		 	    	CurrentChatLines = CurrentChatLines+5;
					for(new l = 5-1; l >= 0; l--)
					{
						strcat(txdText, AdminMessageString[CurrentChatLines-l]);
					}
					TextDrawSetStringEx(txdSystemMessage, txdText);
		 	    	SendClientMessage(playerid, COLOR_GREY, "   Вы опустили чат.");
		    	}
			}
		}
	}
}


