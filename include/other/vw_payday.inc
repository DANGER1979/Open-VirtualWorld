new intrate = 2;//���������� ���������� �� ������

stock payday_OnFiveMinutsTimer(playerid)
{
	new timers = GetTickCount();
	PlayerInfo[playerid][pPayTime] += 5;//������ 5 ����� ��������� ����
	if(PlayerInfo[playerid][pPayTime] < 55)//���� �� ������ ������ 55 �����
	{
		SendClientMessage(playerid, COLOR_GREY, "   B� ������ �� ���������� �����, ����� �������� ��������.");
		return 1;
	}
	new strtmp[MAX_STRING];
	PlayerInfo[playerid][pConnectTime] ++;//����� ������� ����
	WeekOnline ++;
	//PlayerInfo[playerid][pRespect] ++;//�������� 1 ��������
	if(PlayerInfo[playerid][pJob] > 0) PlayerInfo[playerid][pContractTime] ++;//�� ������ ��� �������� �� ���� � ���������
	//PlayerPlayMusic(playerid);
	//--------------------------------------------------------------------------
	new rent = 0;
	//new ToBase[83];//56+3+24�=�83
//��� ������ ����� � �����������
	if(PlayerInfo[playerid][pHouse] >= 0 && PlayerInfo[playerid][pHouse] < MAX_HOUSE)//���� ��� ����
 	{
		new key = PlayerInfo[playerid][pHouse];//���
		rent = HouseInfo[key][hRent];
		//if(!strcmp(PlayerName(playerid), HouseInfo[key][hOwner], true))//���� ����� ��������
		if(PlayerInfo[playerid][pSQLID] == HouseInfo[key][hOwned])
		{
			rent = 0;//�� ������� �����
		}
		else if(rent > GetPlayerMoneyH(playerid))//���� ����� �� ��� ������ ����� ����� � ������
		{
			PlayerInfo[playerid][pHouse] = NOT_KEY;//��������
			SendClientMessage(playerid, COLOR_WHITE, "�� �������� ��-�� ����� �������������������.");
			rent = 0;//�� ������� �����
		}
		HouseInfo[key][hTill] += rent;

	}
	//--------------------------------------------------------------------------
	//���������� ��������
	SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
	format(strtmp, sizeof(strtmp), "| ������� �� ����� �����: $%d", PlayerInfo[playerid][pBank]);//����� � �����
	SendClientMessage(playerid, COLOR_SYSTEM, strtmp);

    if(PlayerInfo[playerid][pAccount] != 0)//���� ���� ����������� � ��� ���� 0
	{
	    new bonus = floatround(PlayerInfo[playerid][pPayCheck]/2);//�� �� ��������� ����� � �������� � ������� �������� ��������
	    PlayerInfo[playerid][pPayCheck] += bonus;
		format(strtmp, sizeof(strtmp), "| �����: $%d", PlayerInfo[playerid][pPayCheck]);//�������� �����
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}

	new tmpTaxValue = floatround(  floatabs( PlayerInfo[playerid][pLevel]*360*TaxValue/100 )  );
	if(BizInfo[0][bTill]+tmpTaxValue < 2147480000) { BizInfo[0][bTill] += tmpTaxValue; BizInfo[0][bExport] += tmpTaxValue; }
	//��� ����� �������� � ���������� TAX ��� ������ �� �� �����
	if(IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD || PlayerInfo[playerid][pMember] == DoH)
	{
		format(strtmp, sizeof(strtmp), "| ��������: $%d", PlayerInfo[playerid][pPayCheck]);//�������� �����
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	if(rent > 0)
	{
		format(strtmp, sizeof(strtmp), "| ������ ����: -$%d | �����: -$%d", rent, tmpTaxValue);//�������� �����
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	else
	{
		format(strtmp, sizeof(strtmp), "| �����: -$%d", tmpTaxValue);//�������� �����
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	//--------------------------------------------------------------------------
	new interest = 0;
	if(PlayerInfo[playerid][pDeposit] > 0)
	{//��� �������� �� ������
		new tmpintrate = 3;//��������� ������� �� ������ ��������� ����������
	    if(PlayerInfo[playerid][pAccount] != 0) tmpintrate = 2;//0.2% �� ������
		if(	PlayerInfo[playerid][pHouse] >= 0 && PlayerInfo[playerid][pHouse] < MAX_HOUSE &&
			//!strcmp(PlayerName(playerid), HouseInfo[PlayerInfo[playerid][pHouse]][hOwner], true))
			PlayerInfo[playerid][pSQLID] == HouseInfo[PlayerInfo[playerid][pHouse]][hOwned]
		  )
		{   //���� �� �������� ����
		    if(PlayerInfo[playerid][pAccount] != 0) tmpintrate += intrate+3;//+0.4% �� ������
			else tmpintrate += intrate+2;//HouseInfo[key][hLevel]//+0.3% �� ������
		}
		//��� �������� ����������� ������
		new bouse = -1;
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] == NOT_KEY) continue;
			bouse = MyBizz[playerid][limit];
		}
		if(bouse != -1)
		{   //���� �� �������� ����
		    if(PlayerInfo[playerid][pAccount] != 0) tmpintrate += intrate+2;//+0.2% �� ������
			else tmpintrate += intrate+1;//HouseInfo[key][hLevel]//+0.1% �� ������
		}
		if(	getdate() < PlayerInfo[playerid][pDepositDay] &&
			(PlayerInfo[playerid][pCash] + PlayerInfo[playerid][pBank] + PlayerInfo[playerid][pDeposit]) <= 5000000 )
		{
			interest = PlayerInfo[playerid][pDeposit]/1000*tmpintrate;//1/100*6 ������� �����
		}
		format(strtmp, sizeof(strtmp), "| ������� �� ��������: $%d", PlayerInfo[playerid][pDeposit]);//'/. ������� �� ������
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
		format(strtmp, sizeof(strtmp), "| ������� �� ������: %.1f%%\%%(+$%d)", tmpintrate/10.0, interest);//'/. ������� �� ������
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
		format(strtmp, sizeof(strtmp), "| ������� ������ ������: $%d", PlayerInfo[playerid][pDeposit]+interest);//'/. ������� �� ������
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
		format(strtmp, sizeof(strtmp), "| ���� ��������� �����: %s", getDate(PlayerInfo[playerid][pDepositDay]));
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
	    format(strtmp, sizeof(strtmp), "| ���������(������ 1 �����): -$%d", CBill);
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
    }
	//--------------------------------------------------------------------------
	SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
//��� ���������
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
	    format(strtmp, sizeof(strtmp), "| ������� ������������: %d | ������: $%d", LevelToCriminality, bonus);//�� �������������
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
	    format(strtmp, sizeof(strtmp), "| ������� ������������: %d | ������: $%d", LevelToCriminality, bonus);//�� �������������
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
	    format(strtmp, sizeof(strtmp), "| ������� ����������: %d | ������: $%d", LevelToDeliver, bonus);//�� �������������
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
	    format(strtmp, sizeof(strtmp), "| ������� ��������: %d | ������: $%d", LevelToEpidemics, bonus);//�� �������������
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
//TestLog(OPTIM, "OnPayDay1.7 ", GetTickCount(), timers);
	//----------------------------------------------------------------------
	if( (PlayerInfo[playerid][pBank] + PlayerInfo[playerid][pPayCheck] + bonus - tmpTaxValue) < 2147483647)
	{
      	if(BizInfo[0][bTill] >= PlayerInfo[playerid][pPayCheck])
		{
			//format(strtmp, sizeof(strtmp), "   ����� ����� !", money);
			//SendClientMessage(playerid, COLOR_GREY, strtmp);
		  	PlayerInfo[playerid][pBank] += (PlayerInfo[playerid][pPayCheck] + bonus - tmpTaxValue);
			format(strtmp, sizeof(strtmp), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strtmp);
			BizInfo[0][bTill] -= PlayerInfo[playerid][pPayCheck]; BizInfo[0][bImport] += PlayerInfo[playerid][pPayCheck];
			//return 1;
		}
		format(strtmp, sizeof(strtmp), "| ����� ���������: $%d", (PlayerInfo[playerid][pPayCheck] + bonus - tmpTaxValue));//�������� �����
		SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	}
	PlayerInfo[playerid][pPayTime] = 0;//��������
	PlayerInfo[playerid][pPayCheck] = 0;
	if(PlayerInfo[playerid][pDeposit] + interest < 2147483647)
	{
	  	PlayerInfo[playerid][pDeposit] += interest;
	}
	format(strtmp, sizeof(strtmp), "| ������� ������: $%d", PlayerInfo[playerid][pBank]);//�����
	SendClientMessage(playerid, COLOR_SYSTEM, strtmp);
	format(strtmp, sizeof(strtmp), "~y~PayDay~n~~w~PayCheck");
	GameTextForPlayerEx(playerid, strtmp, 5000, 1);
	OnPlayerStatsUpdate(playerid, 255);
//======================================================================
	TestLog(OPTIM, "player_OnFiveMinutsTimer ", GetTickCount(), timers);
	return 1;
}
