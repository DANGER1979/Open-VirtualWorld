//new offsettimer = -1;
new WriteIndex;// ��� ����� ������� � �������� �� �������� ���������� � ���� �������
new RunString[128] = "Zdes mogla byt vasha reklama";//0xFF // ��� ����� �������
//new PagerString[256+1] = "�������� �� ������ �������";

/*stock PagerOffset(playerid, txdX, txdYOffset, txdSize, movetime) // ������� �������, ��������� ������� � �����������
{
	new pattern[256+1]; //0xFF ��� ������ ����������� ���������, ����� ������� ��������� ������������ ����� (� ��������)
	WriteIndex = (-1)*txdSize; //������������� ������ ���, ����� ������ ������ ����� ���������, �.�. �� 'c' �������� �����
	for(new i=0; i<txdSize; i++) { pattern[i] = ' '; }// ��������� ��� ���������� ������ ��� ���������� (�� �� ���� �� ����������)
	pattern[txdSize] = 0; // ��������� ������

	if(TextDrawShowBegunok == false)
	{
		//for(new l; l < sizeof(RunString)-1; l++) RunString[l] = " ";//�������� �� �����������
		txdPager[playerid] = TextDrawCreateEx(445.0, 433.0, pattern);//150.0, 2.1, //������� ����� Text Draw � ������ �������  � ����� ��������.
		PlayerTextDrawUseBox(playerid, txdPager[playerid], 0);//���������� ������������� �����. 1 - ������������, 0 - �� ������������
		PlayerTextDrawFont(playerid, txdPager[playerid], 1);//�������� ����� ������. (0-3)
		PlayerTextDrawLetterSize(playerid, txdPager[playerid], 0.30, 1.0);//������������� ������ � ������ ����(�����) � ��������.
		PlayerTextDrawSetOutline(playerid, txdPager[playerid], 1);//������������� ������ ������� ������. 1 - ������� �������
		PlayerTextDrawBackgroundColor(playerid, txdPager[playerid], 0x000000FF);//������������� ���� ���� ������
		PlayerTextDrawBoxColor(playerid, txdPager[playerid], 0x0000ff11);//0x00FFFF66 ������������� ���� �����
		PlayerTextDrawColor(playerid, txdPager[playerid], COLOR_BRIGHTLYGREEN);//COLOR_DARKTURQUOISE 0x000000FF COLOR_LIGHTTURQUOISE
		PlayerTextDrawTextSize(playerid, txdPager[playerid], 540.0, 0.0);//������������� ������ � ������ ����� (��� ������������� �����).

		TextDrawShowForAll(txdPager[playerid]);
		TextDrawShowBegunok = true;
	}
	KillTimer(gOffsettimer); gOffsettimer = -1;
	gOffsettimer = SetTimerEx("PagerTimer", movetime, 1, "ii", playerid, txdSize); //��������� ����������� ������
	return gOffsettimer;
}
public PagerTimer(playerid, size)
{ // ������� ������ ��� ����������� �����������
	BegunokOffsetLine(RunString, strlen(RunString), size, playerid); // ��������� ������� ������������ �������
}*/

//��� ������� ������ ������
stock BegunokOffset(txdX, txdYOffset, txdSize, movetime) // ������� �������, ��������� ������� � �����������
{
	new pattern[255]; //0xFF ��� ������ ����������� ���������, ����� ������� ��������� ������������ ����� (� ��������)
	WriteIndex = (-1)*txdSize; //������������� ������ ���, ����� ������ ������ ����� ���������, �.�. �� txdSize �������� �����
	for(new i=0; i<txdSize; i++) { pattern[i] = ' '; }// ��������� ��� ���������� ������ ��� ���������� (�� �� ���� �� ����������)
//����� ������� ���
	pattern[txdSize] = '\0';//0; // ��������� ������

	if(TextDrawShowBegunok == false)
	{
		//for(new l; l < sizeof(RunString)-1; l++) RunString[l] = " ";//�������� �� �����������
		txdBegunok = TextDrawCreateEx(txdX*1.0, txdYOffset*1.0, pattern);//150.0, 2.1, //������� ����� Text Draw � ������ �������  � ����� ��������.
		TextDrawUseBox(txdBegunok, 1);//���������� ������������� �����. 1 - ������������, 0 - �� ������������
		TextDrawFont(txdBegunok, 1);//�������� ����� ������. (0-3)
		TextDrawLetterSize(txdBegunok, 0.30, 1.0);//������������� ������ � ������ ����(�����) � ��������.
		TextDrawSetOutline(txdBegunok, 1);//������������� ������ ������� ������. 1 - ������� �������
		TextDrawBackgroundColor(txdBegunok, 0x000000FF);//������������� ���� ���� ������
		TextDrawBoxColor(txdBegunok, 0x0000ff11);//0x00FFFF66 ������������� ���� �����
		TextDrawColor(txdBegunok, COLOR_BRIGHTLYGREEN);//COLOR_DARKTURQUOISE 0x000000FF COLOR_LIGHTTURQUOISE
		TextDrawTextSize(txdBegunok, 540.0, 0.0);//������������� ������ � ������ ����� (��� ������������� �����).

		TextDrawShowForAll(txdBegunok);
		TextDrawShowBegunok = true;
	}
	KillTimer(gOffsettimer); gOffsettimer = -1;
	gOffsettimer = SetTimerEx("BegunokTimer", movetime, 1, "i", txdSize); //��������� ����������� ������
	return gOffsettimer;
}
forward BegunokTimer(size);//��� ������� ������
public BegunokTimer(size)
{ // ������� ������ ��� ����������� �����������
	BegunokOffsetLine(RunString, strlen(RunString), size); // ��������� ������� ������������ �������
}
stock BegunokOffsetLine(const message[], length, size, mode=0)
{ // ������� ������������ ������� � RunString
	new buffer[0xFF];//256//0xFF ���� �������� ������, ����� ����� �� ����������
	new i; // ������� ��� for
	new pos = 0; // ���������� ��� ����������� ����� ������ ������ ������������ ������ ������ ������� 
//(������ ����� index+size-1)
	for(i=0; i<size; i++)
	{
		pos = WriteIndex + i; // ���������� ������� ������ ������������ index
		if( (pos > -1) && (pos < length) ) buffer[i] = message[pos]; 
// ���� �� ��������� � �������� ������ �������, ����� ����� i-�� ������ � pos-��
		else
		{//� ��������� ������ �� ������ �������, ���� �� ������, � ���������� ����, ���� �����
			if(pos >= length) break;
			else buffer[i] = ' ';//32
		}
	}
	if(buffer[size-1] == ' ') buffer[size-1] = '\0';//0; // ���� ��� ����� ������������ �� ������, �� �������� ��� 0,
	//���� ��� �� �������, �� ��������� � ���� ������ ����� �������� � ������
	else buffer[i] = '\0';//0; // ���� ������ �� ��������, �� ������ ������ ������ ����� index+size �������, ����� ��������� ��������� ������

//SendClientMessageToAll(-1, buffer);
	if(mode == 1)
	{
		//PlayerTextDrawSetStringEx(txdPager[i], buffer); // ������� ��������� ����������� ����������
	}
    else TextDrawSetStringEx(txdBegunok, RusToGame(buffer)); // ������� ��������� ����������� ����������
//printf("%s", buffer);

	if(WriteIndex >= strlen(RunString)-1) WriteIndex = (-1)*size;
	else WriteIndex ++;
	

}//��� ������� ������ �����

stock begunok_OnPlayerSpawn(playerid)
{
	if(TextDrawShowBegunok == true)//��� ������� ������
	{
		TextDrawShowForPlayer(playerid, txdBegunok);
	}
}

stock begunok_STATE_WASTED(playerid)
{
	if(TextDrawShowBegunok == true)//��� ������� ������
	{
		TextDrawHideForPlayer(playerid, txdBegunok);
	}
}
/*
stock begunok_OnPlayerCommandText(playerid, cmdtext[])
{
	new strcmd[MAX_STRING];
	new cmd[20], idx, tmp[MAX_STRING], gMessage[MAX_STRING];
	//new giveplayerid;
	cmd = strtok(cmdtext, idx);
	if(!strcmp(cmd, "/stopline", true))
	{
		if(PlayerInfo[playerid][pMember] != SAN && PlayerInfo[playerid][pAdmin] != 9)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   �� �� ������� ��������! !");
		}
		if(PlayerInfo[playerid][pRank] < 6 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   �� ������ ���� 6 ����� !");
		}
		if(gOffsettimer < 0)
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		KillTimer(gOffsettimer); gOffsettimer = -1;
		if(TextDrawShowBegunok == true)
		{
			TextDrawShowBegunok = false;
			TextDrawHideForAll(txdBegunok);
			TextDrawDestroyEx(txdBegunok);
		}
		else SendClientMessage(playerid, COLOR_GREY, "   ������� ������ �� �������� (USE: /startline)");
		return 1;
	}
	if(!strcmp(cmd, "/startline", true))
	{
		if(PlayerInfo[playerid][pMember] != SAN && PlayerInfo[playerid][pAdmin] != 9)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   �� �� ����� �������� �������� !");
		}
		if(PlayerInfo[playerid][pMember] == SAN && PlayerInfo[playerid][pRank] < 6)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   �� ������ ���� 6 ����� !");
		}
		if(gOffsettimer >= 0)
		{
			return SendClientMessage(playerid, COLOR_GREY, "USE: /stopline, ����� ���������� ������� ������");
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
			SendClientMessage(playerid, COLOR_GREY, "USE: /stopline, ����� ����������");
			return 1;
		}
		if(strval(tmp) < 10 && strval(tmp) > 300)
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE,  "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		new txdSize = strval(tmp);

   		format(strcmd, sizeof(strcmd), "txdSize: %d", txdSize);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);

		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE,  "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		if(strval(tmp) < 100 && strval(tmp) > 1000)
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE,  "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		new movetime = strval(tmp);
   		format(strcmd, sizeof(strcmd), "movetime: %d miliseconds", movetime);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);

		gMessage = strrest(cmdtext, idx);
		if(strlen(gMessage) > sizeof(RunString))
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /startline [Size ~120] [Speed(ms) ~200] [Text(256 char)]");
		}
		if(!strlen(gMessage))
		{
			strmid(gMessage, "Zdes mogla byt vasha reklama", 0, strlen(gMessage), 255);
			//return 1;
		}
		strmid(RunString, gMessage, 0, strlen(gMessage), 255);
		BegunokOffset(150, 410, txdSize, movetime);//BegunokOffset(150, 438, txdSize, movetime);

   		format(strcmd, sizeof(strcmd), "gMessage: %s", gMessage);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);	
		return 1;
	}
//��� ������� ������ �����
	return 1;
}*/
