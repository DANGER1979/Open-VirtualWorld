
//##############################################################################//
//                                                                              //
//                      ������� ��������� �������� ������                       //
//                                                                              //
//##############################################################################//

new RepairRoadPlayerID[MAX_RADARS] = {MAX_PLAYERS-1, ...};//ID ������ ������������� ����
new pRoadblock[MAX_RADARS];
new BridgeHealth[MAX_RADARS];// = {251, ...};//������� ��� ��� ����������� �����


//������ 5 ����� �������� ����� ���� ��������� � ��������� ����������� �����
stock roadblock_OnFiveMinutsTimer(playerid)
{

//��������� ��� �����
		/*for(new ir=0; ir<MAX_RADARS; ir++)
		{
			DestroyObjectEx(pRoadblock[ir], 13);
			RepairRoadPlayerID[ir] = MAX_PLAYERS-1;
		}
		//GameTextForPlayerEx(playerid, "~g~All RepairedRoadblock deployed successfully", 5000, 5);
		//format(strtmp2, sizeof(strtmp2), "�� ����� %s[%d] ������� ��������� ������!", bridge, RepairRoadPlayerID[ir]);
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-ir);
			SetPlayerMapIcon(i, MAX_PLAYER_ICONS-ir, aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ], 40, 0, MAPICON_GLOBAL);
			//SendClientMessageEx(i, COLOR_GREEN, strtmp);
			PlayerTextDrawSetStringEx(i, txdPager[i], RusToGame("�������� �� ���� ������� �������"));
			PlayAudioStreamForPlayerEx(i, "pager.wav");
		}*/

//��������� ��� �����
	for(new ir=0; ir<MAX_RADARS; ir++)
	{
		DestroyObjectEx(pRoadblock[ir], 13);
		RepairRoadPlayerID[ir] = MAX_PLAYERS-1;
	}
//����������� ������ ����
	new radar = random(MAX_RADARS);
	SetRoadBlock(playerid, radar);
}



forward SetRoadBlock(playerid, radar);
public SetRoadBlock(playerid, radar)//��� ����������� STEP4
{//����������� 1 ��� ����� 5 ������, ����� ����� ��� �������� ����
	new ir = radar;
//��������� ����� ��������
	if(ir >= MAX_RADARS-1) return 1;
	if( RepairRoadPlayerID[ir] == MAX_PLAYERS-1 && !IsValidObjectEx(pRoadblock[ir]) )
	{//���� ������ ���� ir ��� �� ����������
		RepairRoadPlayerID[ir] = MAX_PLAYERS-2;//playerid;
		pRoadblock[ir] = CreateObjectEx(aRadar[ir][objModelid],aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ],aRadar[ir][objrX],aRadar[ir][objrY],aRadar[ir][objrZ]);//0
		new bridge[20];
		strmid(bridge, aRadar[ir][radName], 0, strlen(aRadar[ir][radName]), sizeof(bridge));
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		new strtmp[87+2+2+4+20+24+3];
		format(strtmp, sizeof(strtmp), "[%d:%02d:%02d] �� ����� {FFFFFF}%s[%d]{%.3f,%.3f,%.3f}{33AA33} ������� ��������� ������!", lH,lM,lS, bridge, RepairRoadPlayerID[ir],
			aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ]);
		SendClientMessageToAll(COLOR_GREEN, strtmp);

		format(PagerMessage, sizeof(PagerMessage), "�� ����� %s ������� ��������� ������!", bridge);

		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-MAX_RADARS);
			SetPlayerMapIcon(i, MAX_PLAYER_ICONS-MAX_RADARS, aRadar[ir][objX],aRadar[ir][objY],aRadar[ir][objZ], 11, 0, MAPICON_GLOBAL);//40 - ������ ����� �, 11 - ���������
//��������������
//format(strtmp, sizeof(strtmp), "SetPlayerMapIcon3: %d", MAX_PLAYER_ICONS-MAX_RADARS);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);
			//SendClientMessageEx(i, COLOR_GREEN, strtmp);

			//PlayerTextDrawSetStringEx(i, txdPager[i], RusToGame(PagerMessage));
			//PlayAudioStreamForPlayerEx(i, "pager.wav");
			SendPagerMessage(i);
		}
	}
	return 1;//ir;
}

stock roadblock_OneSecondTimers(playerid)
{
    if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
	//��� �����������
   	if(	IsPlayerInRangeOfPoint(playerid, 30.0, aRadar[nearest[playerid]][radX],aRadar[nearest[playerid]][radY],aRadar[nearest[playerid]][radZ])
		&& !IsInPlane(nCarID[playerid]) )//� �� �� �� ����� � �� �� ����������
  		{   //���� �� �� ��������� 30 � �� ������. 30 ����������� ����������������� ���� ��� ������������ �������� ����������� ����� ����� ��������� ������ ����� ������
  		    //�.�. ��������� ������� �������������� �� ������������ �������� �� �������
		//����� ������� ���� ������
		if(gPlayerUsedBridge[playerid] != nearest[playerid])
		{
			gPlayerUsedBridge[playerid] = nearest[playerid];
			if(BridgeHealth[nearest[playerid]] < 1000)
			{
				BridgeHealth[nearest[playerid]] += floatround(100/numplayers);
				if(BridgeHealth[nearest[playerid]] >= 750)
				{
					if(BridgeHealth[nearest[playerid]] >= 1000) BridgeHealth[nearest[playerid]] = 1000;
					SetTimerEx("SetRoadBlock", 10000, 0, "id", MAX_PLAYERS-2, nearest[playerid]);//SetPlayerRoadBlock(MAX_PLAYERS-2, ir);
					//break;
				}
			}
		}
		//----------------------------------------------------------------------
		if(SpecialBleep[nCarID[playerid]] == 0) //continue;//���� ������ c ��������
		{//���� ������ ��� �������
	     	if(	GaiRad[playerid] == 0 && ExcessPlayerVelocities[playerid] != 0)
	       	{   //���� ���� ����� �� �������� � ����� �������� ������������� ��������
              	GaiRad[playerid] = 1;//����� ��������
//��������������
////new strings[MAX_STRING];
//format(strings, sizeof(strings), "����� %d ��������", nearest[playerid]);
//ABroadCast(COLOR_MAROON, strings, 6);
//SendAllAdminMessage(COLOR_RED, strings, 6);
           	}
       	}
  	}
  	else
	{   //����� ������� �����
		if(gPlayerUsedBridge[playerid] == nearest[playerid]) { gPlayerUsedBridge[playerid] = -1; speedpl[playerid] = 0; }
		GaiRad[playerid] = 0;//����������� ����� � ������������
		//HideDialog(playerid);
		//ExcessPlayerVelocities[playerid] = 0;//������ ���������� (��������� ������������� � ��������)
//��������������
////new strings[MAX_STRING];
//format(strings, sizeof(strings), "����� %d ����� � ������������", nearest[playerid]);
//ABroadCast(COLOR_MAROON, strings, 6);
//SendAllAdminMessage(COLOR_RED, strings, 6);
	}
	return 1;
}



