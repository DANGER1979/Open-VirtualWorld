new advertismenttimer;


//для рекламы
new gAdvertisment = 0;
new sAdvertise[MAX_PLAYERS][MAX_STRING];//строка текста рекламы
new CostAdvertisment[MAX_PLAYERS];//цена строки
new playeridAdvertiser[MAX_PLAYERS];//рекламодатель будет хранить ID подавшего
new addtimer = 65000;//время между рекламами
new txtcost = 10;//3//25 стоимость 1 символа рекламы

stock ad_GameModeExit()//запускается через 4 секунды после вводы команды restart из GameModeInitExitFunc
{
	KillTimer(advertismenttimer); advertismenttimer = -1;
}
stock ad_OnPlayerConnect(playerid)
{
	CostAdvertisment[playerid] = 0;	playeridAdvertiser[playerid] = MAX_PLAYERS-1;//для рекламы
}
	

stock OnPlayerAdvertise(playerid, inputtext[])//ad
{   //для репортёров
	if(PlayerInfo[playerid][pMember] == SAN)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		return 1;
	}
	if(PlayerInfo[playerid][pJailed] > 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вам пока запрещена данная команда !");
		return 1;
	}
	//------------------------------------------------------------------
    // замена любых групп пробельных символов на единичные пробелы
    spaceGroupsToSpaces(inputtext);
    // обрезка пробельных символов по краям
    trimSideSpaces(inputtext);

	new idx;
	new length = strlen(inputtext);
	while ((idx < length) && (inputtext[idx] <= ' '))
	{
		idx ++;
	}
	new offset = idx;
	new result[94];//97//51
	while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
	{
		result[idx - offset] = inputtext[idx];
		idx ++;
	}
	result[idx - offset] = EOS;//End of Scipt - для обнуления данных в строке...
	if(strlen(result) >= sizeof(result))//51
	{
		SendClientMessage(playerid, COLOR_GREY, "   Ваше сообщение не может быть отправлено, т.к. кол-во символов больше 94!");
		return 1;
	}
	//------------------------------------------------------------------
	new strtmp[MAX_STRING];
	if(gAdvertisment == 1)// && PlayerInfo[playerid][pAdmin] < 1
	{
		format(strtmp, sizeof(strtmp), "   Пожалуйста попытайтесь позже. %d секунд между Рекламами !", (addtimer/1000));//new addtimer = 60000;
		SendClientMessage(playerid, COLOR_GREY, strtmp);
		return 1;
	}
	new payout = idx * txtcost;//25 цена за символ
	if(GetPlayerMoneyH(playerid) < payout)
	{
		//format(strings, sizeof(strings), "CEPBEP: {800000}Bы использовали %d символов, которые стоили  $%d.", idx, payout);
		format(strings, sizeof(strings), "   Для подачи объявления вам требуется  $%d.", payout);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	//format(strings, sizeof(strings), "Oбъявление: {FFFFFF}%s, {00FF00}Контакт: {FFFFFF}%s[%d] {00FF00}Ph: {FFFFFF}%d", result, PlayerName(playerid), playerid, PlayerInfo[playerid][pPnumber]);
	format(strtmp, sizeof(strtmp), "Oбъявление: %s, Контакт: %s[%d]", result, PlayerName(playerid), playerid);//, PlayerInfo[playerid][pPnumber]
	sAdvertise[playerid] = strtmp;//записали объявление по ID подавшего
	CostAdvertisment[playerid] = payout;//записали деньги
	SendTeamMessage(SAN, COLOR_GREEN, strtmp);

    format(strtmp, sizeof(strtmp), "%s подал объявление. Наберите /accept ad, чтобы разместить в общем чате", PlayerName(playerid));
    //format(strings, sizeof(strings), "%s подал объявление.\n\nНажмите Accept, \nчтобы разместить его в полоске новостей.", PlayerName(playerid));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] != SAN) continue;
		SendClientMessage(i, COLOR_GREY, strtmp);
		playeridAdvertiser[i] = playerid;//записали ИД подвашего по ИД репортёра
	}
   	SendClientMessage(playerid, COLOR_GREY, "   Bы подали объявление, подождите ответ редактора Агентства новостей.");
	format(strtmp, sizeof(strtmp), "~r~Paid $%d~n~~w~Message contained: %d Characters", payout, idx);
	GameTextForPlayerEx(playerid, strtmp, 5000, 5);
	gAdvertisment = 1;
	advertismenttimer =	SetTimer("tAdvertismentOn", addtimer, 0);
	return 1;
}

forward tAdvertismentOn();//таймер для ограничения рекламы
public tAdvertismentOn()//запускается по команде /advertise через 1 минуту
{   //для рекламы
	gAdvertisment = 0;
	KillTimer(advertismenttimer);
	advertismenttimer = -1;
	return 1;
}
