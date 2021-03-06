//��� ��������
new gGotHit[MAX_PLAYERS];//����� ������ �� ������� ���� - ���� ��������
new GotChaseHitID[MAX_PLAYERS];//ID ���� �� id �������
new GetChaseKillerID[MAX_PLAYERS];//ID ������� �� id ����
new OrderReady[MAX_PLAYERS];
new ConnectedToPC[MAX_PLAYERS];


stock hitman_OnPlayerConnect(playerid)
{
//��� ��������
	gGotHit[playerid] = 0;
	GotChaseHitID[playerid] = MAX_PLAYERS-1; GetChaseKillerID[playerid] = MAX_PLAYERS-1;
	OrderReady[playerid] = 0; ConnectedToPC[playerid] = 0;
}

//��� ��������
stock hitman_OnPlayerStateChange(playerid, newstate)
{
	PlayerInfo[playerid][pMember] != Hitman) return 1;
	if(newstate != PLAYER_STATE_WASTED)  return 1;
//����������� ����� ����� ������ ������
//���� ID ������ ��������� ����� ��������� 7
	if(GotChaseHitID[playerid] >= MAX_PLAYERS-1) return 1;
   	if(	IsPlayerConnected(GotChaseHitID[playerid])
		&& gGotHit[GotChaseHitID[playerid]] == 1
		&& PlayerInfo[GotChaseHitID[playerid]][pHeadValue] > 0)
   	{	//���� ����� ������ � /���� ���� �� ������ > 0
		PlayerInfo[playerid][pProfSkill] -= 5;
		if(PlayerInfo[GotChaseHitID[playerid]][pPurposeMurder] > 0)//��� ��������
		{
			//PlayerInfo[playerid][pRespect] --;
			GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, (-PlayerInfo[GotChaseHitID[playerid]][pHeadValue]/2) );
		}
		format(strings, sizeof(strings), "Hitman %s �� �������� ����� �� %s'a",
			PlayerName(playerid), PlayerName( GotChaseHitID[playerid] ) );
		SendFamilyMessage(Hitman, strings);
		//PlayerInfo[GotChaseHitID[playerid]][pHeadValue] = 0;
		gGotHit[GotChaseHitID[playerid]] = 0;//���������� - ����� �� ������
   		GetChaseKillerID[GotChaseHitID[playerid]] = MAX_PLAYERS-1;//���������� ID ������� �� id ����
   		GotChaseHitID[playerid] = MAX_PLAYERS-1;//���������� ID ���� �������
	}
	return 1;
}

stock hitman_OnPlayerDisconnect(playerid)
{
	//==========================================================================
	//��� ��������
    if(GetChaseKillerID[playerid] < MAX_PLAYERS-1 && GameRestart != 1)
    {//���� ��� ��� ���������� ������, �.�. ����� �� ����� ���� �� ��� �����
        if(	IsPlayerConnected(GetChaseKillerID[playerid]) &&
			PlayerInfo[GetChaseKillerID[playerid]][pMember] == Hitman)
        {   //���� ������ ��� � ����
   			format(strings, sizeof(strings), "���� ����: %s[%d] �������� ���� ������������!!! (%s)", PlayerName(playerid), playerid, strreason);
			SendClientMessage(GetChaseKillerID[playerid], COLOR_CERISE, strings);

    		gGotHit[playerid] = 0;//���������� - ����� �� ������ �� ������� ����
    		GotChaseHitID[GetChaseKillerID[playerid]] = MAX_PLAYERS-1;//���������� ID ���� �� ������� �������
    		GetChaseKillerID[playerid] = MAX_PLAYERS-1;//���������� ID ������� �� id ����
		}
    }
}

stock hitman_OnPlayerPickUp(playerid, pickupid)
{
	if( IsPlayerInRangeOfPoint(playerid, 1.9, -684.9224,939.5638,13.6328))
	{	//��� ��������
		CrashDetected[playerid] = 98;
		if(gParameter2[playerid] == 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "    � �������� �� �� ������ �������� �������, ����� � ���� ��� ����� �� ��������� !");
			SendClientMessage(playerid, COLOR_GREY, "    ��� ���������� ����������: �������� ����� � ���������� !");
			return 1;
		}
		if(gRealWar)
		{
			SendClientMessage(playerid, COLOR_GREY, "    ������������� ����� ���� RealWar ! �� �� ������ ����� �� ���������!");
			return 1;
		}
		if(gJobDuty[playerid])
		{   //���� ��� � �� �� ��������� � �� � �������
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� �� ���������, ����� ����� �� ������.");
			return 1;
		}
		if(PlayerInfo[playerid][pMember] == Hitman && !GetPVarInt(playerid, "gInRacing"))
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			if(gOnDuty[playerid] == 0)
	        {
	        	/*PlayerInfo[playerid][pTeam] = 2;*/
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
				gOnDuty[playerid] = 1;
			}
			else //if(gOnDuty[playerid] == 1)
			{
				/*PlayerInfo[playerid][pTeam] = 3;*/
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
				gOnDuty[playerid] = 0;
			}
		}
		new cost;
	    if(OrderReady[playerid] > 0)
	    {
			ResetPlayerWeaponsEx(playerid);//�������� ������
	        switch(OrderReady[playerid])
	        {
	            case 1:
	            {   //|(1) ($5000) Rank 1: Knife(200), Desert Eagle(2400), MP5(10000), Shotgun(2400), Rifle(1000)
	                //GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 24, 30); GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60); GivePlayerWeaponEx(playerid, 33, 20);
					GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 60);
					cost = 1060;//��� ���������
	            }
	            case 2:
	            {   //|(2) ($6000) Rank 2: Knife, Silenced 9mm(1200), Sniper(10/5000 2*5000=10000
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 20);
					GivePlayerWeaponEx(playerid, 34, 10);
					cost = 1140;
	            }
	            case 3:
	            {   //|(3) ($6000) Rank 3: Knife, Silenced, Shotgun, Sniper(10000)
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 40); //GivePlayerWeaponEx(playerid, 25, 60);
					GivePlayerWeaponEx(playerid, 34, 20);
					cost = 1380;
	            }
	            case 4:
	            {   //|(4) ($8000) Rank 4: Knife, Silenced, MP5, Sniper
	               	GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 80); //GivePlayerWeaponEx(playerid, 29, 450);
					GivePlayerWeaponEx(playerid, 34, 40);
					cost = 2140;
	            }
	            case 5:
	            {   //|(5) ($8000) Rank 6: Knife, Silenced, MP5, Shotgun, Sniper
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 160); //GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60);
					GivePlayerWeaponEx(playerid, 34, 80);
					cost = 2380;
				}
	            case 6:
	            {   //|(6) ($8500) Rank 8: Knife, Desert Eagle, MP5, Shotgun, AK47(14000), Sniper
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 320); //GivePlayerWeaponEx(playerid, 24, 30); //GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60); GivePlayerWeaponEx(playerid, 30, 480);
					GivePlayerWeaponEx(playerid, 34, 160);
					cost = 3900;
				}
	            case 7:
	            {   //|(7) ($8500) Rank 8: Knife(200), Desert Eagle(2400), MP5(10000), Shotgun(2400), M4(18000), Sniper(10000)
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 640); //GivePlayerWeaponEx(playerid, 24, 30); //GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60); GivePlayerWeaponEx(playerid, 31, 480);
					GivePlayerWeaponEx(playerid, 34, 320);
					cost = 4300;
	            }
	        }
	        new Float:rating[MAX_PLAYERS];
	        if(PlayerInfo[playerid][pDeaths] == 0) PlayerInfo[playerid][pDeaths] = 1;
			rating[playerid] = PlayerInfo[playerid][pKills]/PlayerInfo[playerid][pDeaths];//���������� ���������� �������� ������������� �����.
			if(rating[playerid] <= 0) rating[playerid] = 1;
			if(PlayerInfo[playerid][pRank] <= 0) PlayerInfo[playerid][pRank] = 1;
			new money = floatround( float(cost) / (rating[playerid]*PlayerInfo[playerid][pRank]) );
			//float - ������������ ��� ����, ����� �������� ��������� �������� �������, � �� ��������������
			//float - ��������������� ����� � ������������
			GivePlayerMoneyH(fsbiz+9, playerid, -money);
			//SBizInfo[9][sbTill] += money/2;//����������� ������ � ��� General Store �� ������� ������� ��������
			//BizInfo[0][bProducts] += money/2;//����������� ������ � ����
			BizInfo[0][bTill] += money/2; BizInfo[0][bExport] += money/2;
			format(strings, sizeof(strings), "* %s ������ ����� %d � ������� �� ����� $%d � ������ �������� � �����.", PlayerName(playerid), OrderReady[playerid], money);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			OrderReady[playerid] = 0;
		}
		//return 1;
	}//Hitman delivery stuff
}

stock SearchingHit(playerid)//��� ��������
{   // ����������� ��� ����� ������ Contracts
	new searchhit = 0;
	new DialogIDCounter = 0; for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;
	new bigmsgitem[2048];//25*(42 + 2+24+3+10)
	//new tmp[16];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(searchhit >= MAX_DLGITEMS) break;
		if( !IsPlayerConnectedEx(i) ) continue;
		if( PlayerInfo[i][pGunLic] != 1 && !gRealWar) continue;
		if( gGotHit[i] != 0) continue;//����� ��� �� ����//���������� ��� �����
		if(PlayerInfo[i][pHeadValue] <= 0) continue;
		if(PlayerInfo[i][pAccount] != 0) continue;
		//��������� ��� ������ �� ������� ��������� ���������������
   		searchhit ++;//��������� ���� ��� ������ ���������� - ���� ���������
   		DialogID[playerid][DialogIDCounter] = i;
   		//if(PlayerInfo[i][pGunLic] == 1) tmp = "�������";
   		//else tmp = "�����������";
		format(bigmsgitem, sizeof(bigmsgitem), "%s%d\t����: %s[%d]\t��������������: $%d\n",// ��������: %s
			bigmsgitem, searchhit, PlayerName(i), i, PlayerInfo[i][pHeadValue]);//, tmp
		DialogIDCounter ++;
		if(DialogIDCounter >= 25) break;
	}
	if(searchhit < 1) { SendClientMessage(playerid, COLOR_GREY, "   ��� ��������� ����������!"); return 1; }
	if(IsPlayerInArea(playerid, specialzone[6]))
	{
		MenuOperation[playerid] = 96;
		new TextRow[65];
		format(TextRow, sizeof(TextRow), "Hitman Agency Contracts: %d", searchhit);
		ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, TextRow, bigmsgitem, "OK", "Cancel");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ���������� � �������� !");
	}
	return 1;
}

stock hitman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
			//#pragma unused listitem
			#pragma unused inputtext
			if(dialogid != HITMAN_DIALOG) return 1;
			SetPVarInt(playerid, "gShowDialog", -1);
			if(!response)
			{
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� ������� ���� ���������� �� � ����������� �� ������� ���������.");
      			ConnectedToPC[playerid] = 0;
			 	return 1;
			}
			new msgitem[256+1];
			//new giveplayerid;
///portable
//ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, "Hitman Agency", listitems, "OK", "Cancel");
//"News\nContracts\nGivehit\nOrder\nRating\nLogout";
			if(MenuOperation[playerid] == 95)
			{
				if(listitem == 0)//News
				{
					new dlgitem[512];
					SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: News [number] [text] or News delete [number] or News delete all");
					format(msgitem, sizeof(msgitem), "1. %s :: \tHitman: %s", News[hAdd1], News[hContact1]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n2. %s :: \tHitman: %s", News[hAdd2], News[hContact2]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n3. %s :: \tHitman: %s", News[hAdd3], News[hContact3]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n4. %s :: \tHitman: %s", News[hAdd4], News[hContact4]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n5. %s :: \tHitman: %s", News[hAdd5], News[hContact5]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
					{
						//��������������
						format(msgitem, sizeof(msgitem), "Error11: Hitman Agency News %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
							PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
						Log(ERROR, msgitem);
						return 1;
					}
					ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, "Hitman Agency News", dlgitem, "OK", "Cancel");
				}
				else if(listitem == 1)//Contracts
				{
					ConnectedToPC[playerid] = 0;
				    if(GotChaseHitID[playerid] < MAX_PLAYERS-1)
				    {   //���� ID ���� ������� ��� ����������� �� �����-�� ��������
				        SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���� ���� !");
						return 1;
				    }
					SearchingHit(playerid);//�������� �-�� ������ ����������
				}
				else if(listitem == 2)//Order
				{
					ConnectedToPC[playerid] = 0;
			        if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			        {
				        SendClientMessage(playerid, COLOR_GREY, "   � ��� ����������� �������� �� ������!");
					    return 1;
			        }
				    if(PlayerInfo[playerid][pRank] < 2)
					{
				        SendClientMessage(playerid, COLOR_GREY, "   ��� ���� �� �������� ������ � ������� !");
				        return 1;
					}
				    if(OrderReady[playerid] > 0)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� ��� �������� ����� !");
				        return 1;
				    }
					if( gParameter5[playerid] == 1 )
					{
						SendClientMessage(playerid, COLOR_GREY, "   � ��� ���� ���, ����� ������� ������!");
						SendClientMessage(playerid, COLOR_GREY, "   ��� ���������� ��������� �� ������� � �������!");
						return 1;
					}

					new dlgitem[62+47+56+52+61+70+69];//398
					new DialogIDCounter = 0;
					for(new i=0; i<MAX_DLGITEMS; i++) DialogID[playerid][i] = -1;
				    if(PlayerInfo[playerid][pRank] >= 2)
					{   //��� ���������
						strcat(dlgitem, "1. \t$1600 \tRank 2: Knife, Silenced");//strcat(dlgitem, "1. \t$1600 \tRank 1: Knife, Desert Eagle, MP5, Shotgun, Rifle");
						DialogID[playerid][0] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 3)
					{
						strcat(dlgitem, "\n2. \t$1140 \tRank 3: Knife, Silenced, Sniper");//strcat(dlgitem, "\n2. \t$1140 \tRank 2: Knife, Silenced, Sniper");
						DialogID[playerid][1] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 5)
					{
						strcat(dlgitem, "\n3. \t$1380 \tRank 5: Knife, Silenced, Sniper");//strcat(dlgitem, "\n3. \t$1380 \tRank 3: Knife, Silenced, Shotgun, Sniper");
						DialogID[playerid][2] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 7)
					{
						strcat(dlgitem, "\n4. \t$2140 \tRank 7: Knife, Silenced, Sniper");//strcat(dlgitem, "\n4. \t$2140 \tRank 4: Knife, Silenced, MP5, Sniper");
						DialogID[playerid][3] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 9)
					{
						strcat(dlgitem, "\n5. \t$2380 \tRank 9: Knife, Silenced, Sniper");//strcat(dlgitem, "\n5. \t$2380 \tRank 5: Knife, Silenced, MP5, Shotgun, Sniper");
						DialogID[playerid][4] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 10)
					{
						strcat(dlgitem, "\n6.\t$3900 \tRank 10: Knife, Silenced, Sniper");//strcat(dlgitem, "\n6.\t$3900 \tRank 6: Knife, Desert Eagle, MP5, Shotgun, AK47, Sniper");
						DialogID[playerid][5] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 10)
					{
						strcat(dlgitem, "\n7. \t$4300 \tRank 10: Knife, Silenced, Sniper");//strcat(dlgitem, "\n7. \t$4300 \tRank 6: Knife, Desert Eagle, MP5, Shotgun, M4, Sniper");
						DialogID[playerid][6] = DialogIDCounter;
						//DialogIDCounter ++;
					}
					MenuOperation[playerid] = 97;
					ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, "Available Packages", dlgitem, "OK", "Cancel");
				}
				else if(listitem == 3)//Rating
				//else if((strcmp("Rating", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Rating")))
				{
					ConnectedToPC[playerid] = 0;
					new dlgitem[1024];
					strins(dlgitem, "id \tname \t\t\tlevel \trank\trating\n______________________________________________________________________\n", strlen(dlgitem));
					new Float:rating[MAX_PLAYERS];
					for(new j=0, i; j<MaxPlayers; j++)	{
						i = PLIDs[j];
						if( !IsPlayerConnectedEx(i) ) continue;
						if(PlayerInfo[i][pMember] == Hitman)
						{
					        if(PlayerInfo[i][pDeaths] == 0) PlayerInfo[i][pDeaths] = 1;
			                rating[i] = PlayerInfo[i][pKills]/PlayerInfo[i][pDeaths];//���������� ���������� �������� ������������� �����.
							if(strlen(PlayerName(i)) < 13) format(msgitem, sizeof(msgitem), "%d \t%s \t\t%d \t%d \t%.1f\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], rating[i]);
							else format(msgitem, sizeof(msgitem), "%d \t%s \t%d \t%d \t%.1f\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], rating[i]);
							strins(dlgitem, msgitem, strlen(dlgitem));
						}
					}
					strins(dlgitem, "\n______________________________________________________________________\n", strlen(dlgitem));
					if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
					{
						//��������������
						format(msgitem, sizeof(msgitem), "Error12: Agency's Ratings %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
							PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
						Log(ERROR, msgitem);
						return 1;
					}
					ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "Agency's Ratings", dlgitem, "OK", "");
				}
			}
			else if(MenuOperation[playerid] == 96)
			{//Contracts
				SetPVarInt(playerid, "PlayerID", DialogID[playerid][listitem]);
				new hitid = DialogID[playerid][listitem];
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				if(hitid == playerid)
				{
					SendClientMessage(playerid, COLOR_GREY, "  �� �� ������ ����� ����� �� ������ ���� !");
					return 1;
				}
			    if( !IsPlayerConnectedEx(hitid) )
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   ���� ��� ������������ !");
			        return 1;
			    }
			    if(	IsPlayerInRangeOfPlayer(500.0, playerid, hitid) )
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   ���� ������� ������ !");
			        return 1;
			    }
    			format(msgitem, sizeof(msgitem), "Hitman %s, ������ ����� �� ��������: %s[%d], �� $%d.", PlayerName(playerid), PlayerName(hitid), hitid, PlayerInfo[hitid][pHeadValue]);
    			SendFamilyMessage(Hitman, msgitem);
    			GotChaseHitID[playerid] = hitid;//ID ����
    			GetChaseKillerID[hitid] = playerid;//ID ������� - �������� �� ����
    			gGotHit[hitid] = 1;//����� ������ �� ������� ���� - ���� ��������
    			hitid = MAX_PLAYERS-1;//���������� ID ����

    			format(msgitem, sizeof(msgitem), "Hitman ������ ����� �� ��������: %s[%d]. ���������� ��� ������.", PlayerName(hitid), hitid);
    			SendFamilyMessage(FBI, msgitem);
    			//hitfound = 0;//���������� ��������� �����������
			}
			else if(MenuOperation[playerid] == 97)
			{
				if(listitem == DialogID[playerid][0])
			    //if((strcmp("1", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("1")))
				{
				    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 1600)
				    {   //��� ���������
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ����� 1 ($1600). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 1;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
				else if(listitem == DialogID[playerid][1])
				{
				    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 1140)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ���� ����� 2 ($1400). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 2;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
				else if(listitem == DialogID[playerid][2])
				{
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 1380)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ���� ����� 3 ($1380). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 3;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
				else if(listitem == DialogID[playerid][3])
				{
				    if(PlayerInfo[playerid][pRank] < 4) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 2140)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ���� ����� 4 ($2140). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 4;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
				else if(listitem == DialogID[playerid][4])
				{
				    if(PlayerInfo[playerid][pRank] < 6) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 2380)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ���� ����� 5 ($2380). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 5;
				        return 1;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
				else if(listitem == DialogID[playerid][5])
				{
				    if(PlayerInfo[playerid][pRank] < 8) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 3900)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ���� ����� 6 ($3900). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 6;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
				else if(listitem == DialogID[playerid][6])
				{
				    if(PlayerInfo[playerid][pRank] < 10) { SendClientMessage(playerid, COLOR_GREY, "   ��� ���� - �� ���������� �����, ����� ���������� ���� ����� !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 4300)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� �������� ����� 7 ($4300). �� ����� ��������� � ������ ���������.");
				        OrderReady[playerid] = 7;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ���� ����� !");
				    }
				}
			}
			return 1;
}

stock hitman_OnPlayerDeath(playerid, killerid)//Hitman_OnPlayerDeath(playerid, killerid)
{   //���������� �� OnPlayerDeath
	if(killerid == INVALID_PLAYER_ID) return 0;
    if(!IsPlayerConnectedEx(killerid)) return 0;
    if(PlayerInfo[killerid][pMember] != Hitman) return 0;
	if(PlayerInfo[playerid][pHeadValue] <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "Hitman Agency: �� ����� ������ �� ��������� ���� �� ������.");
		return 0;
	}
	if(PlayerInfo[killerid][pInt] != 0 || PlayerInfo[killerid][pLocal] != FREEROAM)
	{
		SendClientMessage(playerid, COLOR_GREY, "Hitman Agency: ������ ����� ��������� � ��������� ��� �������.");
		return 0;
	}
	if(GotChaseHitID[killerid] != playerid)
	{
		SendClientMessage(playerid, COLOR_GREY, "Hitman Agency: ������ ����� �� ������������� ����� ����.");
		return 0;
	}

	//new strings[MAX_STRING];
    if( PlayerInfo[playerid][pPurposeMurder] == 301)
   	{
        if(PlayerInfo[playerid][pBikeLic] == 1) { PlayerInfo[playerid][pBikeLic] = 0; }
        if(PlayerInfo[playerid][pCarLic] == 1) { PlayerInfo[playerid][pCarLic] = 0; }
		if(PlayerInfo[playerid][pFlyLic] == 1) { PlayerInfo[playerid][pFlyLic] = 0; }
		if(PlayerInfo[playerid][pBoatLic] == 1) { PlayerInfo[playerid][pBoatLic] = 0; }
        if(PlayerInfo[playerid][pFishLic] == 1) { PlayerInfo[playerid][pFishLic] = 0; }
        if(PlayerInfo[playerid][pGunLic] == 1) { PlayerInfo[playerid][pGunLic] = 0; SetPlayerToTeamColor(6); }
		SendClientMessage(playerid, 0x88EE88FF, "Hitman Agency: ��� ���� �������� ��������.");
		IncreaseRank(killerid, 25);
    }
	else if( PlayerInfo[playerid][pPurposeMurder] >= 0 && PlayerInfo[playerid][pPurposeMurder] < MAX_HOUSE &&
			PlayerInfo[playerid][pHouse] != NOT_KEY &&
			PlayerInfo[playerid][pSQLID] == HouseInfo[PlayerInfo[playerid][pHouse]][hOwned])
	{
		new house = PlayerInfo[playerid][pHouse];
		//HouseInfo[house][hHel] = 0;
		//HouseInfo[house][hTV] = 0;
		//HouseInfo[house][hCloth] = 0;
		HouseInfo[house][hLock] = 0;
		HouseInfo[house][hOwned] = 0;
		HouseInfo[house][hLock] = 0;
		//HouseInfo[house][hRentabil] = 0;
		strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);
		SaveHouse(house);

		for(new limit = 0; limit < 5; limit++)
		{
			if(MyHouse[playerid][limit] != house) continue;
			MyHouse[playerid][limit] = NOT_KEY;
		}
		PlayerInfo[playerid][pHouse] = NOT_KEY;//c������� ����� //�������� ������ �.�. ����� ����� ���� ������ 1
		//OnPlayerStatsUpdate(playerid);

		format(strings, sizeof(strings), "%s has sell house %d for $%d. reason: killed by %s",
			PlayerName(playerid), house, HouseInfo[house][hBuyPrice],
			PlayerName(killerid));
		Log(BUY,strings);

		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]", HouseInfo[house][hDiscription]);
		//Update3DTextLabelText(text3D[house], 0x88EE88FF, strings);
		Update3DTextLabelEx(hEntranceText3D[house], 0x88EE88FF, text_info);

		format(strings, sizeof(strings), "Hitman Agency: ��� ��� ������ �� $%d",HouseInfo[house][hBuyPrice]);
		SendClientMessage(playerid, 0x88EE88FF, strings);
		IncreaseRank(killerid, 25);
	}
	else if(PlayerInfo[playerid][pPurposeMurder] >= 100 && PlayerInfo[playerid][pPurposeMurder] < 100+MAX_BIZ)
	{//���� ��� ������� �� ���, �� ������ ������
		new bouse;
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] == NOT_KEY) continue;
			bouse = MyBizz[playerid][limit];
			MyBizz[playerid][limit] = NOT_KEY;
			break;
		}
		if(bouse == 0)
		{
			SendClientMessage(killerid, 0x88EE88FF, "Hitman Agency: ����� �� ��������. �������: � ������ ����������� ������");
			return 1;
		}
		OnBizInit(bouse);
		SaveBiz(bouse);
		//OnPlayerStatsUpdate(playerid);

		/*format(strings, sizeof(strings), "%s has sell biz %d for $%d. reason: killed by %s",
			PlayerName(playerid), bouse, BizInfo[bouse][bBuyPrice],
			PlayerName(killerid));*/
		format(strings, sizeof(strings), "%s has sell biz %d reason: killed by %s",
			PlayerName(playerid), bouse, PlayerName(killerid));
		Log(BUY,strings);

		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]",BizInfo[bouse][bDiscription]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+bouse], 0xEEEE88FF, strings);
		Update3DTextLabelEx(bEntranceText3D[bouse], 0xEEEE88FF, text_info);

		//format(strings, sizeof(strings), "Hitman Agency: ��� ������ ������ �� $%d", BizInfo[bouse][bBuyPrice]);
		SendClientMessage(playerid, 0x88EE88FF, "Hitman Agency: ��� ������ ������");
		IncreaseRank(killerid, 25);
	}
	else if(PlayerInfo[playerid][pPurposeMurder] >= 200 && PlayerInfo[playerid][pPurposeMurder] < 200+MAX_SBIZ)
	{
		//��� �������� ����������� ������
#if defined vw_sql//#endif
		new ToBase[44+24];
		new sbouse;// = PlayerInfo[playerid][pBizz]-100;
		//format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `sbizz` WHERE `Owner`='%s'",PlayerName(playerid));
		format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `sbizz` WHERE `Owned`=%d LIMIT 1", PlayerInfo[playerid][pSQLID]);
		mysql_query(ToBase); mysql_store_result();
		if(mysql_num_rows() > 0 && mysql_retrieve_row())
	 	{
	 		new Field[20];
			mysql_fetch_field_row(Field, "ID");	sbouse = strval(Field)-1;
		}
		mysql_free_result();
#endif
		new sbouse;
		for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] == NOT_KEY) continue;
			sbouse = MyCompany[playerid][limit];
			MyCompany[playerid][limit] = NOT_KEY;
			break;
		}
		if(sbouse == 0)
		{
			SendClientMessage(killerid, 0x88EE88FF, "Hitman Agency: ����� �� ��������. �������: � ������ ����������� ��������");
			return 1;
		}
		OnSBizInit(sbouse);
		SaveSBiz(sbouse);

		PlayerInfo[playerid][pBizz] = NOT_KEY;
		//OnPlayerStatsUpdate(playerid);

		/*format(strings, sizeof(strings), "%s has sell sbiz %d for $%d. reason: killed by %s",
			PlayerName(playerid), bouse, SBizInfo[bouse][sbBuyPrice],
			PlayerName(killerid));*/
		format(strings, sizeof(strings), "%s has sell sbiz %d reason: killed by %s",
			PlayerName(playerid), sbouse, PlayerName(killerid));
		Log(BUY,strings);

		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]",SBizInfo[sbouse][sbDiscription]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+bouse], 0xEEEE88FF, strings);
		Update3DTextLabelEx(sbEntranceText3D[sbouse], 0xEEEE88FF, text_info);

		format(strings, sizeof(strings), "Hitman Agency: ���� �������� ������� �� $%d", SBizInfo[sbouse][sbBuyPrice]);
		SendClientMessage(playerid, 0x88EE88FF, strings);
		IncreaseRank(killerid, 25);
	}
	else
	{
		IncreaseRank(killerid, 1);
		SendClientMessage(playerid, 0x88EE88FF, "�� ����� ������� Hitman Agancy");
	}
	if(IsACop(playerid)) IncreaseRank(killerid, 10);

	FamilyInfo[0+PlayerInfo[killerid][pMember]][fBank] += PlayerInfo[playerid][pHeadValue]/2;
	GivePlayerMoneyB(ffamily+PlayerInfo[killerid][pMember], killerid, PlayerInfo[playerid][pHeadValue]/2 );

	format(strings, sizeof(strings), "Hitman Agency: ��� ����������� �� ���� � ����� $%d �� ���������� ������ !", PlayerInfo[playerid][pHeadValue]/2);
	SendClientMessage(killerid, COLOR_MAROON, strings);
	format(strings, sizeof(strings), "Hitman %s �������� ����� �� %s'a", PlayerName(killerid),PlayerName(playerid));
	SendFamilyMessage(Hitman, strings);

	PlayerInfo[playerid][pHeadValue] = 0;
	PlayerInfo[playerid][pPurposeMurder] = 0;
	gGotHit[playerid] = 0;//���������� - ����� �� ������
	GetChaseKillerID[playerid] = MAX_PLAYERS-1;//���������� ID �������
	GotChaseHitID[killerid] = MAX_PLAYERS-1;//���������� ID ���� �������
	return 1;
}


stock right(source[], len)//��� ��������
{   //���������� �� ������� news
	new retval[MAX_STRING], srclen;
	srclen = strlen(source);
	strmid(retval, source, srclen - len, srclen, MAX_STRING);
	return retval;
}


