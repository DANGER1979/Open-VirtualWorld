new advertismenttimer;


//��� �������
new gAdvertisment = 0;
new sAdvertise[MAX_PLAYERS][MAX_STRING];//������ ������ �������
new CostAdvertisment[MAX_PLAYERS];//���� ������
new playeridAdvertiser[MAX_PLAYERS];//������������� ����� ������� ID ���������
new addtimer = 65000;//����� ����� ���������
new txtcost = 10;//3//25 ��������� 1 ������� �������

stock ad_GameModeExit()//����������� ����� 4 ������� ����� ����� ������� restart �� GameModeInitExitFunc
{
	KillTimer(advertismenttimer); advertismenttimer = -1;
}
stock ad_OnPlayerConnect(playerid)
{
	CostAdvertisment[playerid] = 0;	playeridAdvertiser[playerid] = MAX_PLAYERS-1;//��� �������
}
	

stock OnPlayerAdvertise(playerid, inputtext[])//ad
{   //��� ���������
	if(PlayerInfo[playerid][pMember] == SAN)
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� �������!");
		return 1;
	}
	if(PlayerInfo[playerid][pJailed] > 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   ��� ���� ��������� ������ ������� !");
		return 1;
	}
	//------------------------------------------------------------------
    // ������ ����� ����� ���������� �������� �� ��������� �������
    spaceGroupsToSpaces(inputtext);
    // ������� ���������� �������� �� �����
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
	result[idx - offset] = EOS;//End of Scipt - ��� ��������� ������ � ������...
	if(strlen(result) >= sizeof(result))//51
	{
		SendClientMessage(playerid, COLOR_GREY, "   ���� ��������� �� ����� ���� ����������, �.�. ���-�� �������� ������ 94!");
		return 1;
	}
	//------------------------------------------------------------------
	new strtmp[MAX_STRING];
	if(gAdvertisment == 1)// && PlayerInfo[playerid][pAdmin] < 1
	{
		format(strtmp, sizeof(strtmp), "   ���������� ����������� �����. %d ������ ����� ��������� !", (addtimer/1000));//new addtimer = 60000;
		SendClientMessage(playerid, COLOR_GREY, strtmp);
		return 1;
	}
	new payout = idx * txtcost;//25 ���� �� ������
	if(GetPlayerMoneyH(playerid) < payout)
	{
		//format(strings, sizeof(strings), "CEPBEP: {800000}B� ������������ %d ��������, ������� ������  $%d.", idx, payout);
		format(strings, sizeof(strings), "   ��� ������ ���������� ��� ���������  $%d.", payout);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	//format(strings, sizeof(strings), "O���������: {FFFFFF}%s, {00FF00}�������: {FFFFFF}%s[%d] {00FF00}Ph: {FFFFFF}%d", result, PlayerName(playerid), playerid, PlayerInfo[playerid][pPnumber]);
	format(strtmp, sizeof(strtmp), "O���������: %s, �������: %s[%d]", result, PlayerName(playerid), playerid);//, PlayerInfo[playerid][pPnumber]
	sAdvertise[playerid] = strtmp;//�������� ���������� �� ID ���������
	CostAdvertisment[playerid] = payout;//�������� ������
	SendTeamMessage(SAN, COLOR_GREEN, strtmp);

    format(strtmp, sizeof(strtmp), "%s ����� ����������. �������� /accept ad, ����� ���������� � ����� ����", PlayerName(playerid));
    //format(strings, sizeof(strings), "%s ����� ����������.\n\n������� Accept, \n����� ���������� ��� � ������� ��������.", PlayerName(playerid));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] != SAN) continue;
		SendClientMessage(i, COLOR_GREY, strtmp);
		playeridAdvertiser[i] = playerid;//�������� �� ��������� �� �� ��������
	}
   	SendClientMessage(playerid, COLOR_GREY, "   B� ������ ����������, ��������� ����� ��������� ��������� ��������.");
	format(strtmp, sizeof(strtmp), "~r~Paid $%d~n~~w~Message contained: %d Characters", payout, idx);
	GameTextForPlayerEx(playerid, strtmp, 5000, 5);
	gAdvertisment = 1;
	advertismenttimer =	SetTimer("tAdvertismentOn", addtimer, 0);
	return 1;
}

forward tAdvertismentOn();//������ ��� ����������� �������
public tAdvertismentOn()//����������� �� ������� /advertise ����� 1 ������
{   //��� �������
	gAdvertisment = 0;
	KillTimer(advertismenttimer);
	advertismenttimer = -1;
	return 1;
}
