
//-------------------------------
//��� ������� ������


new RoundCounter = 0;//���� ����� ����� �������
new RoundStarted = 0;//��� �����
new BoxDelay = 0;
new BoxTime = 0;
//new BoxDate[37];//25+12
new BoxerBlue = MAX_PLAYERS-1;//ID ������ �����
new BoxerRed = MAX_PLAYERS-1;//ID �������� �����
new DeathCounter1 = 0;//������� �������
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
//��� ������� �����





stock bookmaker_OnPlayerPickUp(playerid, pickupid)
{
//��� ���������� ������
	if(
		(pickupid == PickupID[4] ||
		pickupid == PickupID[5] ||
		pickupid == PickupID[6]) &&
		IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		if(gOnDuty[playerid])
		{   //���� ��� � �� �� ��������� � �� � �������
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ��� ������, ����� ����� �� ������!!");
			return 1;
		}
		/*if(gJobDuty[playerid])
		{   //���� ��� � �� �� ��������� � �� � �������
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ��� ������, ����� ����� �� ���������!!");
			return 1;
		}*/
		if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != BOOKMAKER)
		{
			format(strings, sizeof(strings), "������������: {0080FF}�� �� ������ {FFFFFF}%s{0080FF}. ����� ��������� (USE: /quitjob).", GetPlayerJob(playerid) ); //���������
			SendClientMessage(playerid, COLOR_GREEN, strings);
			return 1;
		}
		if(gJobDuty[playerid])//if(PlayerInfo[playerid][pJob] == BOOKMAKER)
		{
			ShowPlayerDialogGap(playerid, BOOKMAKER_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ���������","�� ������������� ������� ��������� ������� ����?","��","���");
		}
		else
		{
			new dlgitem[558];
			strcat(dlgitem, "1. ����� ������ ������ ��������� ������� ���� �������\
\n2. �������� /secundans ���������� �� ����� ���\
\n3. ������ ����� ��������� ����������� �������� � ����� ����, � ������ - � �������\
\n4. ���� � ���� ���� ��� ���� ���������� ������� ������ �������� /dorate\
\n5. ����� ������ ������� � ��� ������ ������ � �������� ������ ���������� ��� �������� /fight");
			strcat(dlgitem, "\n�� ������ �������� ������ � ������� ����������� ��� � ����� � ����� ����� ������\
\n\n���� ������ ����� ���������� ����� ���� ������� ��. ���� ������ ���� � ������ ���������  - ������� ���. ");

			ShowPlayerDialogGap(playerid, BOOKMAKER_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ���������", dlgitem, "��", "���");
			gDialogStatus[playerid][4] = pickupid;
		}
	}
	return 1;
}

stock bookmaker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem

	ExchangeDialogResponse(playerid, dialogid, response, listitem, inputtext);
	if(dialogid != BOOKMAKER_DIALOG) return 1;//��� ���������� STEP2
//ShowPlayerDialogGap(playerid, BOOKMAKER_DIALOG, DIALOG_STYLE_MSGBOX, "����������", dlgitem, "��", "���");
	if(!response) return 1;
	new biz;
	if(gDialogStatus[playerid][4] == PickupID[4]) biz = 65;
	else if(gDialogStatus[playerid][4] == PickupID[5]) biz = 66;
	else if(gDialogStatus[playerid][4] == PickupID[6]) biz = 67;
 	if(PlayerInfo[playerid][pJob] == BOOKMAKER)//��� ���������� STEP10
	{
		BizInfo[biz][bWorker] --;
       	PlayerInfo[playerid][pJob] = 0; gJobDuty[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� �������� ������ ���������.");
		DisablePlayerCheckpointEx(playerid);
		JobAmmount[playerid] = 0;
	}
	else
	{
    	BizInfo[biz][bWorker] ++;
		PlayerInfo[playerid][pJob] = BOOKMAKER; gJobDuty[playerid] = 1;
      	SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� ������ ������ ���������.");
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
		{   //������ �� ������
			new money = strval(inputtext);
			if(money < 1000 || money > 100000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ������ ������ ���� �� 1000 �� 100000");

				LoopingAnim(playerid, "PED", "IDLE_CHAT", 4.0, 1, 0, 0, 0, 0);

				format(msgitem, sizeof(msgitem), "������� ���� O�������� ������ �� $1000 �� $100000. \
					\n����� �������� ����� ����� ������ \n���������� �� �����������. \
					\n\n�� ��������� ������� ������, \n������� ������������� ����� ������ �����. \
					\n����� ����� ������ �� ������ ������: {33AA33}$%d", TotalRates);
				ShowPlayerDialogGap(playerid, 21, DIALOG_STYLE_INPUT, "World Bet Exchange", msgitem, "BLUE", "RED");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < money)
			{
				format(msgitem, sizeof(msgitem), "   � ��� ��� $%d �������� !", money);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
	        if(RoundCounter > 0)
	        {
	        	StopLoopingAnim(playerid);
	            SendClientMessage(playerid, COLOR_GREY, "  ��� ���� ���, ����� ��������� ��� !");
	            return 1;
	        }
	        StopLoopingAnim(playerid);

			GivePlayerMoneyH(fbox, playerid, -money);
			Rates[playerid][0] = money;
			TotalRateBlue += money;
			TotalRates += money;
		    format(msgitem, sizeof(msgitem), "Bookmaker %s: $%d �� ������. ������ �������. ����� ����� ������ {33AA33}$%d.", PlayerName(Offer[BoxerBlue]), Rates[playerid][0], TotalRates);
			SendClientMessage(playerid, COLOR_BLUE, msgitem);
		}
		else
		{	//������ �� ��������
			new money = strval(inputtext);
			if(money < 1000 || money > 100000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ������ ������ ���� �� 1000 �� 100000");

				LoopingAnim(playerid, "PED", "IDLE_CHAT", 4.0, 1, 0, 0, 0, 0);

				format(msgitem, sizeof(msgitem), "������� ���� O�������� ������ �� $1000 �� $100000. \
					\n����� �������� ����� ����� ������ \n���������� �� �����������. \
					\n\n�� ��������� ������� ������, \n������� ������������� ����� ������ �����. \
					\n����� ����� ������ �� ������ ������: {33AA33}$%d",
					TotalRates);
				ShowPlayerDialogGap(playerid, WBE_DIALOG, DIALOG_STYLE_INPUT, "World Bet Exchange", msgitem, "BLUE", "RED");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < money)
			{
				format(msgitem, sizeof(msgitem), "   � ��� ��� $%d �������� !", money);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
	        if(RoundCounter > 0)
	        {
	        	StopLoopingAnim(playerid);
	            SendClientMessage(playerid, COLOR_GREY, "  ��� ���� ���, ����� ��������� ��� !");
	            return 1;
	        }
	        StopLoopingAnim(playerid);

			GivePlayerMoneyH(fbox, playerid, -money);
			Rates[playerid][1] = money;
			TotalRateRed += money;
			TotalRates += money;
		    format(msgitem, sizeof(msgitem), "Bookmaker %s: $%d �� ��������. ������ �������. ����� ����� ������ {33AA33}$%d.", PlayerName(Offer[BoxerRed]), Rates[playerid][1], TotalRates);
			SendClientMessage(playerid, COLOR_RED, msgitem);
		}
		return 1;
}

