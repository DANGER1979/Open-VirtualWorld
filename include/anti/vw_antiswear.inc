//��� ��������
#define MAX_SWEARS 200 //������������ ���-�� ������ ����, ��� ���������� - ���������
#define length_swear_word 16 //����� ������� �����
new Swears[MAX_SWEARS][length_swear_word];//������ ��� �������� ������ ���� � ����
new WordsCounter = 0;//������� ���-�� ������ ���� � ����
new BreachCounter[MAX_PLAYERS];//������� ���������

stock antiswear_OnGameModeInit()
{
	//��� ��������
	new	LSW[length_swear_word], File:file;
	if((file = fopen("Logs/antiswear.cfg",io_read)))
	{
		while(fread(file,LSW))
		{//������ ���� �� ��� ��� ���� � ��� ���� ������:
			for(new i=0, j=strlen(LSW); i<j; i++)
			{
				if(LSW[i] == '\n' || LSW[i] == '\r') LSW[i] = '\0';//\0 - ����������� ������
			}
			Swears[WordsCounter] = LSW;//���������� � ������ ��� ������ ����� �� �����
			WordsCounter ++;
		}
		fclose(file);
	}
}

stock antiswear_OnPlayerConnect(playerid)
{
	BreachCounter[playerid] = 0;//��� �������� ������� ���������
}

stock AntiSweer(playerid, const message[])
{
/*
	new index;
	new length = strlen(strings);//��� ������� ����� ���� ������������ ��� �������� ����� ��������� ������ ����� �������.
	while ((index < length) && (strings[index] <= ' '))
	{
		index ++;//����� ������� �������
	}
	new offset = index;//���������� ������� ������� � ���������� ������
	new result[MAX_STRING];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = strings[index];//� ���������� result �������� ������� � ������� ����� �������
		index ++;
	}
	result[index - offset] = EOS;//�������� ������ � ������ result ������� � ������� ���������� ����������� �������
*/
	//------------------------------------------------------------------
	new result[MAX_STRING];
	strmid(result, message, 0, strlen(message), MAX_STRING);//����� �����
	if(ANTISWEER == 1)//��� �������� ������
	{   //���� ������� �����������
		new SweerFound = 0;
		for(new s=0; s<WordsCounter; s++)
    	{   //��������� ��� ������ ����� � ����
			new pos;
			if( ( pos = strfind(result, Swears[s], true) ) != -1)//���� ������ ����� �������
			//������ ��������� � ������. -1 - ���� �� �������
			//cmdtext - ������, � ������� ����� ������������� �����
			//Swears[s] - ������� ������
	    	{   //���� ����� ��������� � ����� � ���� �������
				for(new i=pos, j=pos+strlen(Swears[s]); i<j; i++)
				{   //��� ������� ������� � ������� ������� ������� ����� �� ����� ����� �����
		 	 		result[i] = '*';//���������� �� ������ *
				}
				SweerFound = 1;
				BreachCounter[playerid] ++;//������� ���-�� ��� ���������� ������ ���� � ����� ���
			}
		}
		if(BreachCounter[playerid] > 0 && SweerFound == 1)//���������
		{
	 	 	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}�� ��� �� ������ ��������� (����������� ���� � �����)!!!");
	        new tmpSwear = FLOODLIM - BreachCounter[playerid];
	       	//new strings[MAX_STRING];
	        format(strings, sizeof(strings), "CEPBEP: {800000}��� %d �������������� � �� �� c������ ��������!", tmpSwear);
	 	 	SendClientMessage(playerid, COLOR_RED, strings);
	  		if(PlayerInfo[playerid][pBank] > 100*BreachCounter[playerid])
	  		{
			  	GivePlayerMoneyB(fadmin, playerid, -100*BreachCounter[playerid]);
			}
	  		else
	  		{
				GivePlayerMoneyH(fadmin, playerid, -100*BreachCounter[playerid]);
			}
			if(BizInfo[0][bTill]+100*BreachCounter[playerid] < 2147480000) { BizInfo[0][bTill] += 100*BreachCounter[playerid]; BizInfo[0][bExport] += 100*BreachCounter[playerid]; }
	        if(BreachCounter[playerid] >= FLOODLIM)
	        {

				PlayerInfo[playerid][pMuted] = getdate() + 3;
	        	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}�� �� ������ ��������! �� ��������� �� 3 ���!");
				format(strings, sizeof(strings), "CEPBEP: %s ��� �������� �� 3 ���. reason: ignore %d warnings in local chat", PlayerName(playerid), BreachCounter[playerid]);
		 		Log(CHAT,strings);
  				BreachCounter[playerid] = 0;
	        }
		}
	}//��� �������� �����'
	return result;
	//------------------------------------------------------------------
}
