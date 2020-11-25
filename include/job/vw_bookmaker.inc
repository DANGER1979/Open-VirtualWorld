
//-------------------------------
//для боксёров начало


new RoundCounter = 0;//ринг занет раунд начался
new RoundStarted = 0;//для бокса
new BoxDelay = 0;
new BoxTime = 0;
//new BoxDate[37];//25+12
new BoxerBlue = MAX_PLAYERS-1;//ID синего бойца
new BoxerRed = MAX_PLAYERS-1;//ID красного бойца
new DeathCounter1 = 0;//счётчик смертей
new DeathCounter2 = 0;
new BoxWaitTime[MAX_PLAYERS];

new titleblue[20];
new titlered[20];
new Rates[MAX_PLAYERS][2];
new TotalRates = 0;
new TotalRateBlue = 0;
new TotalRateRed = 0;

enum pBoxingStats
{
    TitelName[40],
    TitelWins,
    TitelLoses
};
new Champion[pBoxingStats];
//для боксёров конец





stock bookmaker_OnPlayerPickUp(playerid, pickupid)
{
//для букмекеров начало
	if(
		(pickupid == PickupID[4] ||
		pickupid == PickupID[5] ||
		pickupid == PickupID[6]) &&
		IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		if(gOnDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на службу!!");
			return 1;
		}
		/*if(gJobDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на дежурство!!");
			return 1;
		}*/
		if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != BOOKMAKER)
		{
			format(strings, sizeof(strings), "Работодатель: {0080FF}Вы на работе {FFFFFF}%s{0080FF}. Чтобы уволиться (USE: /quitjob).", GetPlayerJob(playerid) ); //сообщение
			SendClientMessage(playerid, COLOR_GREEN, strings);
			return 1;
		}
		if(gJobDuty[playerid])//if(PlayerInfo[playerid][pJob] == BOOKMAKER)
		{
			ShowPlayerDialogGap(playerid, BOOKMAKER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка Букмекера","Вы действительно желаете закончить рабочий день?","Да","Нет");
		}
		else
		{
			new dlgitem[558];
			strcat(dlgitem, "1. Чтобы начать работу букмекера найдите двух игроков\
\n2. Командой /secundans предложите им обоим бой\
\n3. Первый игрок приняшвий предложение появится в синем углу, а второй - в красном\
\n4. Если в зале есть ещё люди предложите сделать ставки командой /dorate\
\n5. Когда ставки сделаны и оба игрока готовы к поединку можете стартовать бой командой /fight");
			strcat(dlgitem, "\nВы будите получать деньги с каждого проведённого боя и часть с общей суммы ставок\
\n\nЕсли хотите стать букмекером этого зала нажмите ДА. Если хотите уйти с работы букмекера  - нажмите НЕТ. ");

			ShowPlayerDialogGap(playerid, BOOKMAKER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка Букмекера", dlgitem, "Да", "Нет");
			gDialogStatus[playerid][4] = pickupid;
		}
	}
	return 1;
}

stock bookmaker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem

	ExchangeDialogResponse(playerid, dialogid, response, listitem, inputtext);
	if(dialogid != BOOKMAKER_DIALOG) return 1;//для букмекеров STEP2
//ShowPlayerDialogGap(playerid, BOOKMAKER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка", dlgitem, "Да", "Нет");
	if(!response) return 1;
	new biz;
	if(gDialogStatus[playerid][4] == PickupID[4]) biz = 65;
	else if(gDialogStatus[playerid][4] == PickupID[5]) biz = 66;
	else if(gDialogStatus[playerid][4] == PickupID[6]) biz = 67;
 	if(PlayerInfo[playerid][pJob] == BOOKMAKER)//для дровосеков STEP10
	{
		BizInfo[biz][bWorker] --;
       	PlayerInfo[playerid][pJob] = 0; gJobDuty[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу Букмекера.");
		DisablePlayerCheckpointEx(playerid);
		JobAmmount[playerid] = 0;
	}
	else
	{
    	BizInfo[biz][bWorker] ++;
		PlayerInfo[playerid][pJob] = BOOKMAKER; gJobDuty[playerid] = 1;
      	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы начали работу Букмекера.");
	}
//printf("gDialogStatus: %d PickupID: %d", gDialogStatus[playerid][4], PickupID[8]);
	gDialogStatus[playerid][4] = 0;
	return 1;
}


//--------------------------------------------------------------------------
stock ExchangeDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		//#pragma unused inputtext
		if(dialogid != WBE_DIALOG) return 1;
		new msgitem[256+1];
		//new giveplayerid;
//ShowPlayerDialogGap(i,21, DIALOG_STYLE_INPUT, "World Bet Exchange", msgitem, "BLUE", "RED");
//ShowPlayerDialogGap(playerid, 21, DIALOG_STYLE_INPUT, "World Bet Exchange", msgitem, "BLUE", "RED");
		if(response)
		{   //ставка на синего
			new money = strval(inputtext);
			if(money < 1000 || money > 100000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ставка должна быть от 1000 до 100000");

				LoopingAnim(playerid, "PED", "IDLE_CHAT", 4.0, 1, 0, 0, 0, 0);

				format(msgitem, sizeof(msgitem), "Введите вашу Oдиночную ставку от $1000 до $100000. \
					\nСумма выигрыша равна сумме ставки \nумноженной на коэффициент. \
					\n\nПо окончанию нажмите кнопку, \nкоторая соответствует цвету Вашего бойца. \
					\nОбщая сумма ставок на данный момент: {33AA33}$%d", TotalRates);
				ShowPlayerDialogGap(playerid, 21, DIALOG_STYLE_INPUT, "World Bet Exchange", msgitem, "BLUE", "RED");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < money)
			{
				format(msgitem, sizeof(msgitem), "   У вас нет $%d наличных !", money);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
	        if(RoundCounter > 0)
	        {
	        	StopLoopingAnim(playerid);
	            SendClientMessage(playerid, COLOR_GREY, "  Уже идет Бой, ждите окончания Боя !");
	            return 1;
	        }
	        StopLoopingAnim(playerid);

			GivePlayerMoneyH(fbox, playerid, -money);
			Rates[playerid][0] = money;
			TotalRateBlue += money;
			TotalRates += money;
		    format(msgitem, sizeof(msgitem), "Bookmaker %s: $%d на Синего. Ставка принята. Общая сумма ставок {33AA33}$%d.", PlayerName(Offer[BoxerBlue]), Rates[playerid][0], TotalRates);
			SendClientMessage(playerid, COLOR_BLUE, msgitem);
		}
		else
		{	//ставка на красного
			new money = strval(inputtext);
			if(money < 1000 || money > 100000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ставка должна быть от 1000 до 100000");

				LoopingAnim(playerid, "PED", "IDLE_CHAT", 4.0, 1, 0, 0, 0, 0);

				format(msgitem, sizeof(msgitem), "Введите вашу Oдиночную ставку от $1000 до $100000. \
					\nСумма выигрыша равна сумме ставки \nумноженной на коэффициент. \
					\n\nПо окончанию нажмите кнопку, \nкоторая соответствует цвету Вашего бойца. \
					\nОбщая сумма ставок на данный момент: {33AA33}$%d",
					TotalRates);
				ShowPlayerDialogGap(playerid, WBE_DIALOG, DIALOG_STYLE_INPUT, "World Bet Exchange", msgitem, "BLUE", "RED");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < money)
			{
				format(msgitem, sizeof(msgitem), "   У вас нет $%d наличных !", money);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
	        if(RoundCounter > 0)
	        {
	        	StopLoopingAnim(playerid);
	            SendClientMessage(playerid, COLOR_GREY, "  Уже идет Бой, ждите окончания Боя !");
	            return 1;
	        }
	        StopLoopingAnim(playerid);

			GivePlayerMoneyH(fbox, playerid, -money);
			Rates[playerid][1] = money;
			TotalRateRed += money;
			TotalRates += money;
		    format(msgitem, sizeof(msgitem), "Bookmaker %s: $%d на Красного. Ставка принята. Общая сумма ставок {33AA33}$%d.", PlayerName(Offer[BoxerRed]), Rates[playerid][1], TotalRates);
			SendClientMessage(playerid, COLOR_RED, msgitem);
		}
		return 1;
}

