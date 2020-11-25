new intrate = 2;//показатель увеличения по вкладу

stock payday_OnFiveMinutsTimer(playerid)
{
	new timers = GetTickCount();
	PlayerInfo[playerid][pPayTime] += 5;//каждые 5 минут начисляем очки
	if(PlayerInfo[playerid][pPayTime] < 55)//если вы играли меньше 55 минут
	{
		SendClientMessage(playerid, COLOR_GREY, "   Bы играли не достаточно долго, чтобы получить зарплату.");
		return 1;
	}
	new strtmp[MAX_STRING];
	PlayerInfo[playerid][pConnectTime] ++;//игрок отыграл часа
	WeekOnline ++;
	//PlayerInfo[playerid][pRespect] ++;//добавили 1 уважение
	if(PlayerInfo[playerid][pJob] > 0) PlayerInfo[playerid][pContractTime] ++;//то каждый час добавить по часу к контракту
	//PlayerPlayMusic(playerid);
	//--------------------------------------------------------------------------
	new rent = 0;
	//new ToBase[83];//56+3+24 = 83
//для снятия ренты у арендаторов
	if(PlayerInfo[playerid][pHouse] >= 0 && PlayerInfo[playerid][pHouse] < MAX_HOUSE)//если дом есть
 	{
		new key = PlayerInfo[playerid][pHouse];//дом
		rent = HouseInfo[key][hRent];
		//if(!strcmp(PlayerName(playerid), HouseInfo[key][hOwner], true))//если игрок владелец
		if(PlayerInfo[playerid][pSQLID] == HouseInfo[key][hOwned])
		{
			rent = 0;//не снимать ренты
		}
		else if(rent > GetPlayerMoneyH(playerid))//если рента за дом больше суммы денег у игрока
		{
			PlayerInfo[playerid][pHouse] = NOT_KEY;//выселить
			SendClientMessage(playerid, COLOR_WHITE, "Вы выселены из-за своей неплатёжеспособности.");
			rent = 0;//не снимать ренты
		}
		HouseInfo[key][hTill] += rent;

	}
	//--------------------------------------------------------------------------
	//НАЧИСЛЕНИЕ ЗАРПЛАТЫ
	SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
	format(strtmp, sizeof(strtmp), "| Остаток на вашем счету: $%d", PlayerInfo[playerid][pBank]);//денег в банке
	SendClientMessage(playerid, COLOR_SYSTEM, strtmp);

    if(PlayerInfo[playerid][pAccount] != 0)//если ранг плательщика у вас выше 0
	{
	    new bonus = floatround(PlayerInfo[playerid][pPayCheck]/2);//то вы получаете бонус к зарплате в размере половины зарплаты
	    PlayerInfo[playerid][pPayCheck] += bonus;
		format(strtmp, sizeof(strtmp), "| Бонус: $%d", PlayerInfo[playerid][pPayCheck]);//зарплата налог
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}

	new tmpTaxValue = floatround(  floatabs( PlayerInfo[playerid][pLevel]*360*TaxValue/100 )  );
	if(BizInfo[0][bTill]+tmpTaxValue < 2147480000) { BizInfo[0][bTill] += tmpTaxValue; BizInfo[0][bExport] += tmpTaxValue; }
	//ваш налог полажили в переменную TAX для выплат из неё копам
	if(IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD || PlayerInfo[playerid][pMember] == DoH)
	{
		format(strtmp, sizeof(strtmp), "| Зарплата: $%d", PlayerInfo[playerid][pPayCheck]);//зарплата налог
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	if(rent > 0)
	{
		format(strtmp, sizeof(strtmp), "| Аренда дома: -$%d | Налог: -$%d", rent, tmpTaxValue);//зарплата налог
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	else
	{
		format(strtmp, sizeof(strtmp), "| Налог: -$%d", tmpTaxValue);//зарплата налог
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	//--------------------------------------------------------------------------
	new interest = 0;
	if(PlayerInfo[playerid][pDeposit] > 0)
	{//для процента по вкладу
		new tmpintrate = 3;//начальный процент по вкладу временный показатель
	    if(PlayerInfo[playerid][pAccount] != 0) tmpintrate = 2;//0.2% по вкладу
		if(	PlayerInfo[playerid][pHouse] >= 0 && PlayerInfo[playerid][pHouse] < MAX_HOUSE &&
			//!strcmp(PlayerName(playerid), HouseInfo[PlayerInfo[playerid][pHouse]][hOwner], true))
			PlayerInfo[playerid][pSQLID] == HouseInfo[PlayerInfo[playerid][pHouse]][hOwned]
		  )
		{   //если вы владелец дома
		    if(PlayerInfo[playerid][pAccount] != 0) tmpintrate += intrate+3;//+0.4% по вкладу
			else tmpintrate += intrate+2;//HouseInfo[key][hLevel]//+0.3% по вкладу
		}
		//для владения несколькими бизами
		new bouse = -1;
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] == NOT_KEY) continue;
			bouse = MyBizz[playerid][limit];
		}
		if(bouse != -1)
		{   //если вы владелец биза
		    if(PlayerInfo[playerid][pAccount] != 0) tmpintrate += intrate+2;//+0.2% по вкладу
			else tmpintrate += intrate+1;//HouseInfo[key][hLevel]//+0.1% по вкладу
		}
		if(	getdate() < PlayerInfo[playerid][pDepositDay] &&
			(PlayerInfo[playerid][pCash] + PlayerInfo[playerid][pBank] + PlayerInfo[playerid][pDeposit]) <= 5000000 )
		{
			interest = PlayerInfo[playerid][pDeposit]/1000*tmpintrate;//1/100*6 процент банка
		}
		format(strtmp, sizeof(strtmp), "| Остаток на депозите: $%d", PlayerInfo[playerid][pDeposit]);//'/. процент по вкладу
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
		format(strtmp, sizeof(strtmp), "| Процент по вкладу: %.1f%%\%%(+$%d)", tmpintrate/10.0, interest);//'/. процент по вкладу
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
		format(strtmp, sizeof(strtmp), "| Текущий размер вклада: $%d", PlayerInfo[playerid][pDeposit]+interest);//'/. процент по вкладу
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
		format(strtmp, sizeof(strtmp), "| Дата истечения срока: %s", getDate(PlayerInfo[playerid][pDepositDay]));
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	//--------------------------------------------------------------------------
    new CBill, cbill = 0;
	for(new limit = 0; limit < 3; limit++)
	{
		if(MyCar[playerid][limit] != 0)	cbill ++;
	}
	if(cbill >= 2)
	{
        CBill = PlayerInfo[playerid][pDeposit]*cbill/1000;
        PlayerInfo[playerid][pBank] -= CBill;
		if(BizInfo[0][bTill]+CBill < 2147480000) { BizInfo[0][bTill] += CBill; BizInfo[0][bExport] += CBill; }
	    format(strtmp, sizeof(strtmp), "| АвтоНалог(больше 1 тачки): -$%d", CBill);
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
    }
	//--------------------------------------------------------------------------
	SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
//для экономики
	new bonus = 0;
	if(PlayerInfo[playerid][pMember] == DoT)
	{
		if(LevelToCriminality > 10)
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck]*10.0/LevelToCriminality );
		}
		else
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck] * (3.0 - LevelToCriminality/10.0 ) );
		}
		FamilyInfo[DoT][fBank] -= bonus;
	    format(strtmp, sizeof(strtmp), "| Уровень Преступности: %d | Премия: $%d", LevelToCriminality, bonus);//за электричество
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	else if(PlayerInfo[playerid][pMember] == FBI)
	{
		if(LevelToCriminality > 10)
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck]*10.0/LevelToCriminality );
		}
		else
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck] * (3.0 - LevelToCriminality/10.0 ) );
		}
		FamilyInfo[FBI][fBank] -= bonus;
	    format(strtmp, sizeof(strtmp), "| Уровень Преступности: %d | Премия: $%d", LevelToCriminality, bonus);//за электричество
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	else if(PlayerInfo[playerid][pMember] == DoD)
	{
		if(LevelToDeliver > 5)
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck]*3.0/LevelToDeliver );
		}
		else
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck] * (2.0 - LevelToDeliver/3.0) );
		}
		FamilyInfo[DoD][fBank] -= bonus;
	    format(strtmp, sizeof(strtmp), "| Уровень Судимостей: %d | Премия: $%d", LevelToDeliver, bonus);//за электричество
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	else if(PlayerInfo[playerid][pMember] == DoH)
	{
		if(LevelToEpidemics > 5)
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck]*5.0/LevelToEpidemics );
		}
		else
		{
			bonus = floatround( PlayerInfo[playerid][pPayCheck] * (2.5 - LevelToEpidemics/5.0) );
		}
		FamilyInfo[DoH][fBank] -= bonus;
	    format(strtmp, sizeof(strtmp), "| Уровень Эпидемии: %d | Премия: $%d", LevelToEpidemics, bonus);//за электричество
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
//TestLog(OPTIM, "OnPayDay1.7 ", GetTickCount(), timers);
	//----------------------------------------------------------------------
	if( (PlayerInfo[playerid][pBank] + PlayerInfo[playerid][pPayCheck] + bonus - tmpTaxValue) < 2147483647)
	{
      	if(BizInfo[0][bTill] >= PlayerInfo[playerid][pPayCheck])
		{
			//format(strtmp, sizeof(strtmp), "   Казна пуста !", money);
			//SendClientMessage(playerid, COLOR_GREY, strtmp);
		  	PlayerInfo[playerid][pBank] += (PlayerInfo[playerid][pPayCheck] + bonus - tmpTaxValue);
			format(strtmp, sizeof(strtmp), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strtmp);
			BizInfo[0][bTill] -= PlayerInfo[playerid][pPayCheck]; BizInfo[0][bImport] += PlayerInfo[playerid][pPayCheck];
			//return 1;
		}
		format(strtmp, sizeof(strtmp), "| Итого начислено: $%d", (PlayerInfo[playerid][pPayCheck] + bonus - tmpTaxValue));//зарплата налог
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	PlayerInfo[playerid][pPayTime] = 0;//обнулить
	PlayerInfo[playerid][pPayCheck] = 0;
	if(PlayerInfo[playerid][pDeposit] + interest < 2147483647)
	{
	  	PlayerInfo[playerid][pDeposit] += interest;
	}
	format(strtmp, sizeof(strtmp), "| Текущий Баланс: $%d", PlayerInfo[playerid][pBank]);//Итого
	SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	format(strtmp, sizeof(strtmp), "~y~PayDay~n~~w~PayCheck");
	GameTextForPlayerEx(playerid, strtmp, 5000, 1);
	OnPlayerStatsUpdate(playerid, 255);
//======================================================================
	TestLog(OPTIM, "player_OnFiveMinutsTimer ", GetTickCount(), timers);
	return 1;
}
