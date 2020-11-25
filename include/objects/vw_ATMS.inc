//##############################################################################//
//                                                                              //
//                              СИСТЕМА БАНКОМАТОВ                              //
//                                                                              //
//##############################################################################//

enum atm_info
{
	bool: aShow,//false -если объект ставится в процессе игры,true - если объект сразу установлен при запуске мода
	aModel,
	Float:aX,
	Float:aY,
	Float:aZ,
	
	Float:arX,
	Float:arY,
	Float:arZ,
	
    aVW,

	aText[128],//19+20+24+1
	aColor,
	Float:aDist,//дистанция отрисовки
	aLos//будет ли видно через стены
}
#define MAX_ATM 11
new Bankomat[MAX_ATM][atm_info] = {//77	//32//32	//134
//2757 - OTB_machine
//2618 - CJ_SLOT_PROPg
//19324 - kmb_atm1_2 //2942 - kmb_atm1(Ломается при ударе)
//{true, 19324, 2144.2,1642.6000,993.5761, 		0.0,0.0,0.0, 0, "{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//2618 банкомат в банке
{true, 19324, 2225.4323,-1151.8704,1025.4265,	0.0,0.0,-90.69, 	15, "{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//2757 банкомат LS Motel 2219.5566,-1154.3215,1025.7969
{true, 19324, 2157.7932,1620.9016,999.8701,		0.0,0.0,90.0, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//26 банкомат LV CNN Studio
{true, 19324, 381.1362,177.6035,1008.2974, 		0.0,0.0,88.0, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//банкомат SF City Hall
{true, 19324, 1485.9813,-1760.5220,2105.7497, 	0.0,0.0,-91.29, 	DoJ,"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//банкомат LS City Hall
//{-1, -1, 381.1362,177.6035,1008.2974, 3, "Избирательный участок\n{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы голосовать", 0x0080FFFF, 15.0, 1},

{true, 19324, -1668.3493,1221.5891,6.8899, 		0.0,0.0,-46.1,	 	0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//27 банкомат АвтоСалон
{true, 19324, -47.1699,-268.3399,6.2899, 		0.0,0.0,0.0, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//банкомат возле склада
{true, 19324, 2728.77,-2417.5551,13.2828, 		0.0,0.0,180.0, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//банкомат возле порта
{true, 19324, 1141.6661,-1762.1408,13.2319, 	0.00,0.00,179.59, 	0,	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1},//банкомат возле спавна//1698.7653,-1675.4104,20.0787
{true, 19324, 1467.2169,-1749.9229,15.1080, 	0.0,0.0,179.6, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1}, //банкомат возле мерии ЛС
{true, 19324, -1980.6005,144.3486,27.3189, 		0.0,0.0,-87.0, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1}, //банкомат на возале СФ
{true, 19324, 2241.5007,-1722.6901,13.2018, 	0.0,0.0,-0.5, 		0, 	"{FFFFFF}Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат", 0xFFFFFFAA, 15.0, 1} //банкомат возле качалки ЛС
};


stock atm_OnGameModeInit()///загрузка глобальных объектов
{
	new time = GetTickCount();
	for(new atm = 0; atm < MAX_ATM; atm ++)
	{
		CreateObjectEx(Bankomat[atm][aModel],Bankomat[atm][aX],Bankomat[atm][aY],Bankomat[atm][aZ],
							Bankomat[atm][arX],Bankomat[atm][arY],Bankomat[atm][arZ], Bankomat[atm][aVW], -1, -1, 300.0);
		Create3DTextLabelEx(Bankomat[atm][aText], Bankomat[atm][aColor], Bankomat[atm][aX], Bankomat[atm][aY], Bankomat[atm][aZ]+1.2,
			Bankomat[atm][aDist], INVALID_PLAYER_ID,INVALID_VEHICLE_ID, Bankomat[atm][aLos], Bankomat[atm][aVW]);
	}
//3д тексты без создания объектов
	Create3DTextLabelEx("Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат",
		-1, -1506.046630, 757.898254, 1041.042480, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, BANK_WORLD);
	Create3DTextLabelEx("Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат",
		-1, -1506.886230, 757.898254, 1041.042480, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, BANK_WORLD);
	Create3DTextLabelEx("Нажмите '{0080FF}L. Alt{FFFFFF}'\nчтобы использовать банкомат",
		-1, -1507.666992, 757.898254, 1041.042480, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, BANK_WORLD);

	printf("11/19. [Загрузка банкоматов]: Было загружено - %d, потрачено - %d (ms)", MAX_ATM+3, GetTickCount() - time);
}



stock atm_OnPlayerExitedMenu(playerid, Menu:Current)
{
	if(Current == mBank)//для банка
	{
		HideMenuForPlayerEx(mBank,playerid);
		TogglePlayerControllableEx(playerid, 1);//освободить
	}
}

//stock show_bankomat(playerid)
stock atm_OnPlayerKeyStateChange(playerid)//если игрок нажал Alt
{//при нажатии выполняется два раза, т.к. сработает при нажатии
    new found;
	for(new b = 0; b < MAX_ATM; b++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.3, Bankomat[b][aX],Bankomat[b][aY],Bankomat[b][aZ]))
		{
			found ++;
		}
	}
	if( IsPlayerInRangeOfPoint(playerid, 1.3, -1506.046630, 757.898254, 1041.042480) ||
	    IsPlayerInRangeOfPoint(playerid, 1.3, -1506.886230, 757.898254, 1041.042480) ||
	    IsPlayerInRangeOfPoint(playerid, 1.3, -1507.666992, 757.898254, 1041.042480)
	  )
	{
		found ++;
	}
	if(found)
	{	//для банкоматов
 		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mBank, playerid);
		//return 1;
	}
}

stock atm_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	if(Current == mBank)//Для банка
	{
		switch(row)
		{
			case 0://Balance
			{
				new salary, online;
				new level = PlayerInfo[playerid][pLevel];
				for(new Lvl=1; Lvl<level; Lvl++)
				{
					salary += Lvl*360 * (Lvl+1)*4;//3600 - (Lvl+1)*levelcost
					online += (Lvl+1)*4;
				}
				SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
				format(strings, sizeof(strings), "  Текущая зарплата за %d часов: $%d", online, salary);
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
				salary = 0; online = 0;
				for(new Lvl=1; Lvl<=level; Lvl++)
				{
					salary += Lvl*360 * (Lvl+1)*4;//3600 - (Lvl+1)*levelcost
					online += (Lvl+1)*4;
				} 
				format(strings, sizeof(strings), "  Ожидаемый баланс за %d часов: $%d", online, salary);//%d hours
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
				format(strings, sizeof(strings), "  Ожидается Зарплата: $%d", PlayerInfo[playerid][pPayCheck]);
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
				format(strings, sizeof(strings), "  Текущий баланс: $%d", PlayerInfo[playerid][pBank]);
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
				format(strings, sizeof(strings), "  Ожидаемый Баланс: $%d", PlayerInfo[playerid][pBank] + PlayerInfo[playerid][pPayCheck]);
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
				SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
				format(strings, sizeof(strings), "  Текущий Депозит: $%d", PlayerInfo[playerid][pDeposit]);
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
				ShowMenuForPlayerEx(mBank, playerid);
			}
			/*case 1://Transfer
			{
				if(PlayerInfo[playerid][pLevel] < 2)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть 2 уровня !");
					ShowMenuForPlayerEx(mBank, playerid);
				}
				else
				{
					TogglePlayerControllableEx(playerid, 1);
					ShowPlayerDialogEx(playerid, 16, DIALOG_STYLE_INPUT, "Transfer", "Введите ID игрока [playerid] \nили часть имени [PartOfName]", "OK", "Cancel");
				}
			}*/
			case 1://Deposit
			{
				TogglePlayerControllableEx(playerid, 1);
				new strtmp[375 + 10];
				MenuOperation[playerid] = 2;
				format(strtmp, sizeof(strtmp), "У Вас на депозите: $%d\n", PlayerInfo[playerid][pDeposit]);
	    		strcat(strtmp, "\n\nВведите сумму вклада не менее 1000$.\n\t{8CAA63}По окончанию ввода нажмите OK.");
				strcat(strtmp, "{8CAA63}Примечание:\n");
				strcat(strtmp, "\t- только через 7 дней вы сможете забрать деньги\n");
				strcat(strtmp, "\t- по истечении которых, проценты больше не начисляются.\n");
				strcat(strtmp, "\t- Сумма денег на руках, на карточке и на депозите\n");
	    		strcat(strtmp, "\t- не должна превышать $5.000.000, чтобы каждый час получать проценты.\n");
				ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "ATM: сделать вклад", strtmp, "OK", "Cancel");
				//ShowMenuForPlayerEx(mBank, playerid);
			}
			case 2://Credit
			{

				TogglePlayerControllableEx(playerid, 1);
				MenuOperation[playerid] = 3;
				format(strings, sizeof(strings), "У Вас на депозите: $%d\
\nВведите сумму обналичивания. \
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", PlayerInfo[playerid][pDeposit]);
				ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "ATM: снять вклад", strings, "OK", "Cancel");
			}
			case 3://Withdraw
			{
				TogglePlayerControllableEx(playerid, 1);
				MenuOperation[playerid] = 4;
				format(strings, sizeof(strings), "У Вас на счету: $%d\
\nВведите сумму обналичивания. \
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", PlayerInfo[playerid][pBank]);
				ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "ATM: Снятие денег", strings, "OK", "Cancel");
			}
		}
	}
}

stock atm_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != BANKOMAT_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	new msgitem[256+1];
	//new giveplayerid;
	if(!response)
	{
	    new found;
		for(new b = 0; b < MAX_ATM; b++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, Bankomat[b][aX],Bankomat[b][aY],Bankomat[b][aZ]))
			{
				found ++;
			}
		}
		if(found)
  		{
	 		TogglePlayerControllableEx(playerid, 0);//обездвиживает
			ShowMenuForPlayerEx(mBank, playerid);
		}
		return 1;
	}
	if(MenuOperation[playerid] == 2)//Deposit
	{
		if(!strlen(inputtext))
		{
			//SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /deposit [amount]");
			format(msgitem, sizeof(msgitem), "BANK: Bы Имеете $%d на вашем счету.", PlayerInfo[playerid][pBank]);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
			return 1;
		}
		new cashdeposit = strval(inputtext);
		if(cashdeposit > GetPlayerMoneyH(playerid) || cashdeposit < 1000//для экономики
			|| PlayerInfo[playerid][pDeposit] + cashdeposit >= 2147483647)
		{   //если сумма больше денег на руках
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько денег или сумма меньше $1000 !");
			return 1;
		}
		if((PlayerInfo[playerid][pCash] + PlayerInfo[playerid][pBank]+
			PlayerInfo[playerid][pDeposit]) > 5000000)
		{   //если сумма больше денег на руках
			SendClientMessage(playerid, COLOR_GREY, "   Банк больше не принимает от вас вклады ! Вы слишком богаты!");
			return 1;
		}
		GivePlayerMoneyH(fdeposit, playerid, -cashdeposit);
		new curfunds = PlayerInfo[playerid][pDeposit];
		//GivePlayerMoneyB(1, playerid, cashdeposit);
		PlayerInfo[playerid][pDeposit] += cashdeposit;
		if(getdate()+7 <= 365) PlayerInfo[playerid][pDepositDay] = getdate() + 7;
		else PlayerInfo[playerid][pDepositDay] = 365;
		SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
		format(msgitem, sizeof(msgitem), "  Остаток: {33AA33}$%d", curfunds);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Сумма вклада: {33AA33}$%d",cashdeposit);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Депозит-Счёт: {33AA33}$%d", PlayerInfo[playerid][pDeposit]);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Дата истечения срока: %s", getDate(PlayerInfo[playerid][pDepositDay]));
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 3)//Credit
	{
		if(!strlen(inputtext))
		{
			format(msgitem, sizeof(msgitem), "BANK: Bы имеете $%d на депозите.", PlayerInfo[playerid][pDeposit]);
			SendClientMessage(playerid, COLOR_GRAD3, msgitem);
			return 1;
		}
		new cashdeposit = strval(inputtext);
		if(cashdeposit > PlayerInfo[playerid][pDeposit] || cashdeposit < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько денег или сумма указана не верно !");
			return 1;
		}
		if(getdate() < PlayerInfo[playerid][pDepositDay] && PlayerInfo[playerid][pDepositDay] <= 365) //-999 autoban
		{
			format(msgitem, sizeof(msgitem), "BANK: Срок истечения действия вклада: %s(осталось %d дней)", getDate(PlayerInfo[playerid][pDepositDay]), PlayerInfo[playerid][pDepositDay] - getdate());
			SendClientMessage(playerid, COLOR_RED, msgitem);
	        return 1;
		}
		new curfunds = PlayerInfo[playerid][pDeposit];
		PlayerInfo[playerid][pDeposit] -= cashdeposit;
		GivePlayerMoneyB(fdeposit, playerid, cashdeposit);
		SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
		format(msgitem, sizeof(msgitem), "  Старый Баланс: {33AA33}$%d", curfunds);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Сумма снятия: {33AA33}$%d", cashdeposit);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Новый баланс: {33AA33}$%d", PlayerInfo[playerid][pBank]);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 4)//Withdraw
	{   //для банкоматов
		if(!strlen(inputtext))
		{
			format(msgitem, sizeof(msgitem), "ATM: Bы имеете $%d на счету.", PlayerInfo[playerid][pBank]);
			SendClientMessage(playerid, COLOR_GRAD3, msgitem);
			return 1;
		}
		new cashdeposit = strval(inputtext);
		if(cashdeposit > PlayerInfo[playerid][pBank] || cashdeposit < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько денег или сумма указана не верно !");
			return 1;
		}
		new money = cashdeposit;
		//--------------------------------------------------------------
		//GivePlayerMoneyH(fwithdraw, playerid, cashdeposit);
		if(PlayerInfo[playerid][pCash] + money < 2147483647)
		{
			new strtmp[11+10];
			PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
			format(strtmp, sizeof(strtmp), "~b~+~g~%s$", NiceMoney(money));
			GameTextForPlayerEx(playerid, strtmp, 1000, 1);
			PlayerInfo[playerid][pCash] += money;
			ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
			gConsumingMoney[playerid] = 2;
			GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
			LastMoney[playerid] = PlayerInfo[playerid][pCash];
		}
		//--------------------------------------------------------------
		new curfunds = PlayerInfo[playerid][pBank];
		//--------------------------------------------------------------
		//GivePlayerMoneyB(fwithdraw, playerid, -cashdeposit);
		if(PlayerInfo[playerid][pBank] + money < 2147483647)
		{
			new strtmp[11+10];
			PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			format(strtmp, sizeof(strtmp), "~r~%s$", NiceMoney(money));
			GameTextForPlayerEx(playerid, strtmp, 1000, 1);
		  	PlayerInfo[playerid][pBank] += (-1*money);
			format(strtmp, sizeof(strtmp), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strtmp);
		}
		//--------------------------------------------------------------
		SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
		format(msgitem, sizeof(msgitem), "  Старый Баланс: {33AA33}$%d", curfunds);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Сумма снятия: {33AA33}$%d", cashdeposit);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		format(msgitem, sizeof(msgitem), "  Новый баланс: {33AA33}$%d", PlayerInfo[playerid][pBank]);
		SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
		SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
		MenuOperation[playerid] = 0;
	}
	return 1;
}


