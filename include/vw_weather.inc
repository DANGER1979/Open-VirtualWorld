//https://dev.prineside.com/ru/gtasa_weather_id/

//������� ����� ������
//������� ��������


new LevelToEpidemics = 0;
//------------------------------------------------------------------------------
//��� ������ //�� ������� ���������
//new weathers[] = {17,18,3,10,5,6,11,1,14,0,13,2,4,9,12,15,7,8,21,22,18,20,19};
new weathers[] = {17,18,3,10,5,6,11,1,14,0,13,2,9,12,15,7,8,18,19};//8,16   ,30,38-�������, 4 - �������� ���������
new wethindex = 0;//������� ����� � ������ ������


new STD[10][66] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 10},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7}
};//����������� �������� 43%
/*������ ��������:
3)���������� 1��
1)������ 4��
2)������ 6��
4)������� 7��
5)�������� ���� 4��
6)������� 3��
7)�������� 4��
8)�������
9)�����
13)����
14)���������
15)�������
16)�������
18)��� �����
19)����������
20)������ ������
21)�������
22)��������
23)������
24)���
25)�������� ������
26)��������� ����
27)�������
28)���������
29)������ ������
30)�������
31)����
*/

//��� ������
stock GisMeteoMessage(weatherid)
{
	new wtext[128];
	if(weatherid == 0) { strmid(wtext, "����� ����, ��������� - �������", 0, strlen("����� ����, ��������� - �������"), 128); }
	else if(weatherid == 1) { strmid(wtext, "����� ����, ��������� - �������", 0, strlen("����� ����, ��������� - �������"), 128); }
	else if(weatherid == 2) { strmid(wtext, "������� ����, ��������� - �������", 0, strlen("������� ����, ��������� - �������"), 128); }
	else if(weatherid == 3) { strmid(wtext, "������� ����, ��������� - �������", 0, strlen("������� ����, ��������� - �������"), 128); }
	else if(weatherid == 4) { strmid(wtext, "������� �������� ����, ��������� - �������", 0, strlen("������� �������� ����, ��������� - �������"), 128); }
	else if(weatherid == 5) { strmid(wtext, "��������� ����� ����, ��������� - ������", 0, strlen("��������� ����� ����, ��������� - ������"), 128); }
	else if(weatherid == 6) { strmid(wtext, "����� ����, ��������� - ������", 0, strlen("����� ����, ��������� - ������"), 128); }
	else if(weatherid == 7) { strmid(wtext, "������-����� ��������� ����, ��������� - �������", 0, strlen("������-����� ��������� ����, ��������� - �������"), 128); }
	else if(weatherid == 8) { strmid(wtext, "����� � ������, ��������� - �������", 0, strlen("����� � ������, ��������� - �������"), 128); }
	else if(weatherid == 9) { strmid(wtext, "�����, ��������� - ������", 0, strlen("�����, ��������� - ������"), 128); }
	else if(weatherid == 10) { strmid(wtext, "����� ����� ����, ��������� - �������", 0, strlen("����� ����� ����, ��������� - �������"), 128); }
	else if(weatherid == 11) { strmid(wtext, "������ ������� ����, ��������� - �������", 0, strlen("������ ������� ����, ��������� - �������"), 128); }
	else if(weatherid == 12) { strmid(wtext, "������-����� ��������� ����, ��������� - �������", 0, strlen("������-����� ��������� ����, ��������� - �������"), 128); }
	else if(weatherid == 13) { strmid(wtext, "����� ����, ��������� - �������", 0, strlen("����� ����, ��������� - �������"), 128); }
	else if(weatherid == 14) { strmid(wtext, "����������� ����� ����, ��������� - �������", 0, strlen("����������� ����� ����, ��������� - �������"), 128); }
	else if(weatherid == 15) { strmid(wtext, "������-����� ��������� ����, ��������� - �������", 0, strlen("������-����� ��������� ����, ��������� - �������"), 128); }
	else if(weatherid == 16) { strmid(wtext, "����� � ������, ��������� - �������", 0, strlen("����� � ������, ��������� - �������"), 128); }
	else if(weatherid == 17) { strmid(wtext, "������� ����, ��������� - �������", 0, strlen("����� ������� ����, ��������� - �������"), 128); }
	else if(weatherid == 18) { strmid(wtext, "����� ������� ����, ��������� - �������", 0, strlen("����� ������� ����, ��������� - �������"), 128); }
	else if(weatherid == 19) { strmid(wtext, "�������� ����, ��������� - ������", 0, strlen("�������� ����, ��������� - ������"), 128); }
	else if(weatherid == 20) { strmid(wtext, "����-����� ��������� ����, ��������� - ���� ��������", 0, strlen("����-����� ��������� ����, ��������� - ���� ��������"), 128); }
	else if(weatherid == 21) { strmid(wtext, "����������� ���������� ����, ��������� - �������", 0, strlen("����������� ���������� ����, ��������� - �������"), 128); }
	else if(weatherid == 22) { strmid(wtext, "����������� ����� ����, ��������� - �������", 0, strlen("����������� ����� ����, ��������� - �������"), 128); }
	else if(weatherid == 42) { strmid(wtext, "���������� �������� ����, ��������� - ������", 0, strlen("���������� �������� ����, ��������� - ������"), 128); }
	return wtext;
}

stock weather_OneMinutsTimer()
{
//��� ������ ������
	new setpog = 0;
	if(ChangeWeath == 0)
	{	//���� ����� �� �����, ����� ������
	    wethindex ++;//����� ������ ������
	    if(wethindex >= sizeof(weathers)) wethindex = 0;
	    SetWeather(weathers[wethindex]);//�� ������� weathers ���������� ������ ��������� �� ������
	    ChangeWeath = WEATHCHANGE;//��������
	    setpog = 1;//������� ���� ��� ������������ ������
		if(weathers[wethindex+1] == 8 || weathers[wethindex+1] == 9 || weathers[wethindex+1] == 16 || weathers[wethindex+1] == 19)
		{
			format(strings, sizeof(strings), "GisMeteoMessage: � ��������� ����� � ����� San Andreas ��������� %s[%d].", GisMeteoMessage(weathers[wethindex+1]), weathers[wethindex+1]);
			SendFamilyMessage(SAN, strings);
		}
		if(weathers[wethindex] == 8 || weathers[wethindex] == 16)
		{
			SBizInfo[51][sbProducts] += 500;
		}
	}
	else if(ChangeWeath > 0) { ChangeWeath --; }//������ �����
	
	for(new j=0, i; j<MaxPlayers; j++)
	{
		i = PLIDs[j];
		//if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
		if( !gPlayerLogged[i] ) continue;
		if( !gPlayerSpawned[i] ) continue;
		
		if(setpog == 1 && PlayerInfo[i][pVirtual] == 0)	SetPlayerWeather(i, weathers[wethindex]);
		OnPlayerCheckInRain(i);
	}
	
//��� ������ �����
}


//��� �������� ������
stock OnPlayerCheckInRain(playerid)
{	//���������� �� ��������� �������
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(weathers[wethindex] != 8 && weathers[wethindex] != 16) return 1;
	if(PlayerInfo[playerid][pLevel] <= 1) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(spectateid[playerid] != MAX_PLAYERS-1) return 1;
	if(PlayerInfo[playerid][pSTD] != 0 || PlayerInfo[playerid][pAccount] != 0) return 1;

	if(IsInAmbulanceCar(playerid) || IsPlayerInAnyVehicle(playerid) ||
		IsAtHospital(playerid) ) return 1;
	if( IsPlayerInArea(playerid, specialzone[2]) ||//������� ���� ������ ������ �������
		IsPlayerInArea(playerid, specialzone[6]) || //������� Hitman
		IsPlayerInArea(playerid, specialzone[8]) || //CarDealer
		IsPlayerInArea(playerid, specialzone[10])) return 1;

	if(LastHealth[playerid] < 50.0) return 1;
	new rand = random(66);//�������� �� ������ ������� � ����� ������������ ��������
	PlayerInfo[playerid][pSTD] = STD[PlayerInfo[playerid][pDrugPerk]][rand];//43% // STD4 - 29% �����������
	if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll)
	{   //���� ����� �������� �����
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "* %s �������", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		LevelToEpidemics ++;
	}
	return 1;
}

