//��� ���������
new playeridMobileCall[MAX_PLAYERS];//id ������ ���� ������ ������ � id ������ ��� ������ ������
new CallCost[MAX_PLAYERS];//��������� ����� ���������
new gPhoneOnline[MAX_PLAYERS];//������� ��������
new gCellTimeCounter[MAX_PLAYERS];//������� ������� ���������
new cchargetime = 60;//����� ��� ������� ���������� ���������� callcost �� ��������


new Float:Telephone[47][3] = {
{-1697.0389,1334.8060,7.1797},
{-1688.7664,1359.2323,7.1722},
{-1661.2637,1397.7579,7.1722},
{-1964.0696,162.3964,27.6875},
{-1965.2167,162.3911,27.6875},
{-1966.2723,162.3976,27.6875},
{-1967.3297,162.3855,27.6875},
{2278.7866,2528.4956,10.8203},
{2278.7710,2526.6565,10.8203},
{2278.7834,2524.9622,10.8203},
{-2419.3674,717.7355,35.1719},
{1721.1857,-1720.3369,13.5410},
{1721.1970,-1721.2969,13.5452},
{1723.0861,-1721.2853,13.5470},
{1723.0792,-1720.2955,13.5390},
{638.1630,-1229.1355,18.0870},
{637.9344,-1227.5426,18.1330},
{338.8757,-1397.2609,14.2232},
{339.9344,-1397.6611,14.3896},
{339.5494,-1398.7960,14.3888},
{338.5794,-1398.6755,14.3754},
{355.3488,-1365.1289,14.4659},
{356.8065,-1364.4772,14.4849},
{523.1823,-1526.4501,14.8032},
{522.3278,-1525.6112,14.7490},
{523.0820,-1524.7758,14.6954},
{523.9950,-1525.5625,14.7462},
{523.1561,-1517.2479,14.6005},
{522.3231,-1516.4448,14.5962},
{523.0453,-1515.5686,14.5915},
{524.0080,-1516.4518,14.5963},
{523.1635,-1517.2472,14.6005},
{278.0701,-1630.6086,33.3104},
{279.6537,-1630.8873,33.3106},
{2166.3948,-1154.9231,24.8756},
{2166.4006,-1155.7961,24.8618},
{2069.4753,-1766.5579,13.5628},
{2069.4114,-1767.8278,13.5622},
{303.0597,-1592.8389,32.8478},
{302.0926,-1592.7163,32.8099},
{296.7140,-1573.7665,33.4634},
{295.1407,-1573.5374,33.4441},
{379.8264,170.0236,1008.3828},
{381.5215,170.0084,1008.3828},
{383.2478,170.0071,1008.3828},
{2259.2505,-1211.7010,23.9688},
{2257.7051,-1211.6669,23.9688}
};


stock phone_OnPlayerConnect(playerid)
{
	playeridMobileCall[playerid] = MAX_PLAYERS-1; CallCost[playerid] = 0; gPhoneOnline[playerid] = 0;gCellTimeCounter[playerid] = 0;//��� ���������
}

stock phone_OnPlayerDeath(playerid)
{
	new caller = playeridMobileCall[playerid];//��� ���������
	if(caller != MAX_PLAYERS-1)
	{
		//���� ������ ���������� ������ ����� �� ����� ����������� ���������
		SendClientMessage(caller,  COLOR_GREY, "   ������� �� ��������...");
		gCellTimeCounter[caller] = 0;

		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		gCellTimeCounter[playerid] = 0;
	}
}

//stock OnPlayerKeyTelephone(playerid, newkeys)
//stock phone_OnPlayerKeyState(playerid, newkeys)
stock phone_OnPlayerKeyState_YES(playerid)//if(newkeys & KEY_YES)
{
		if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
		{
			//SendClientMessage(playerid, COLOR_GREY, "   �� - ��� �� ������...");
			return 1;
		}
		//--------------------------------------------------------------
		format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
		PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
		SetPVarInt(playerid, "gChatSwitcher", Off);
		GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
		//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		//--------------------------------------------------------------
		//PlaySoundForPlayer(playerid, 3402);
		for(new j=0, i; j<MaxPlayers; j++)
		{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(playeridMobileCall[i] == playerid)
			{   //��������� ���� ������� ��� ���������
				playeridMobileCall[playerid] = i; //�������� ID ���� ��� ��� ������, �.�. ������ �����������
				gCellTimeCounter[i] = 1;//������ ��������� ��������� � ���� ��� ��������
				CallCost[i] = SBizInfo[2][sbEntranceCost];//callcost;//���������� �� 100$
				//������� ������ ����� �� ����� �������� ID ���������� ������
				format(strings, sizeof(strings), "* %s ������ ������.", PlayerName(playerid));
				SendClientMessage(playeridMobileCall[playerid],  COLOR_LILAC, strings);

				//TextDrawBackgroundColor(txdVehicleIcon[playerid], 0x00000033);
				/*TextDrawTextSize(txdVehicleIcon[playeridMobileCall[playerid]], 120.0, 120.0);// Text size is the Width:Height
		    	TextDrawSetPreviewRot(txdVehicleIcon[playeridMobileCall[playerid]], 0.0, 0.0, 0.0);
				TextDrawSetPreviewModel(txdVehicleIcon[playeridMobileCall[playerid]], GetPlayerSkin(playerid));
				TextDrawShowForPlayer(playeridMobileCall[playerid], txdVehicleIcon[playeridMobileCall[playerid]]);

				TextDrawTextSize(txdVehicleIcon[playerid], 120.0, 120.0);// Text size is the Width:Height
		    	TextDrawSetPreviewRot(txdVehicleIcon[playerid], 0.0, 0.0, 0.0);
				TextDrawSetPreviewModel(txdVehicleIcon[playerid], GetPlayerSkin(playeridMobileCall[playerid]));
				TextDrawShowForPlayer(playerid, txdVehicleIcon[playerid]);*/

				SendClientMessage(playeridMobileCall[playerid], COLOR_GREY, "HAMEK: �� ������ ������ ������������ F6 ��� '/', ����� �������� �� ������ ��������.");
				if( !IsPlayerInAnyVehicle(playerid) )
				{
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
					SetPlayerAttachedObjectEx(playerid, MOBILE_SLOT, 330, 6); // 4 = ����, 330 = ������ ��������, 6 = ������ ����
				}
				else ApplyAnimation(playerid, "CAR_CHAT", "carfone_in", 4.0,0,1,1,1,0);
				//RingTone[playerid] = 0;
				return 1;//����� ����� ������� ���������� �������� ������ ������������
			}
		}
		return 1;
}

stock phone_OnPlayerKeyState_NO(playerid)//else if(newkeys & KEY_NO)
{
		if(playeridMobileCall[playerid] == MAX_PLAYERS-1)
		{
			//SendClientMessage(playerid, COLOR_GREY, "   �� - ��� �� ������...");
			return 1;
		}
		new caller = playeridMobileCall[playerid];//playeridMobileCall[133]=3
		//ID ���� � ��� �� ��������
		if(IsPlayerConnected(caller) && caller != INVALID_PLAYER_ID)
		{   //���� ���������� � ���� //���� � ������ ���� ����� �� ����������
			//PlaySoundForPlayer(caller, 3402);
			if(playeridMobileCall[caller] == playerid)//���� ���������� ��� �� ������ � ����
			{   //playeridMobileCall[3] = 133 == 133

				//TextDrawHideForPlayer(playerid, txdVehicleIcon[playerid]);
				//TextDrawHideForPlayer(playeridMobileCall[playerid], txdVehicleIcon[playeridMobileCall[playerid]]);

				format(strings, sizeof(strings), "* %s ������� ������.", PlayerName(playerid));
				//ProxDetector(caller, 10.0, strcmd, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			    for(new t=0; t<sizeof(Telephone); t++)
			    {   //���� ���������� ����� � ���������
					if(IsPlayerInRangeOfPoint(playerid, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
					{
						//TogglePlayerControllableEx(caller, true);//�����������
						strmid(strings, "* ���������� ������� ������", 0, strlen("* ���������� ������� ������"), 255);
						break;
					}
					if(IsPlayerInRangeOfPoint(caller, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
					{
						TogglePlayerControllableEx(caller, true);//�����������
						break;
					}
				}
				SendClientMessage(caller,  COLOR_LILAC, strings);
				gCellTimeCounter[caller] = 0;
				playeridMobileCall[caller] = MAX_PLAYERS-1;

				if(!IsPlayerInAnyVehicle(caller))
				{
					SetPlayerSpecialAction(caller, SPECIAL_ACTION_STOPUSECELLPHONE);
					RemovePlayerAttachedObject(caller, MOBILE_SLOT);
					//ClearAnimations(caller, 1);
				}
			}
		}
	    for(new t=0; t< sizeof(Telephone); t++)
	    {
			if(IsPlayerInRangeOfPoint(playerid, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
			{
				TogglePlayerControllableEx(playerid, 1);//�����������
				break;
			}
		}

		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		gCellTimeCounter[playerid] = 0;
		SendClientMessage(playerid,  COLOR_GREY, "   ��� ������� ��������� � �������.");
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
			//ClearAnimations(playerid, 1);
		}
		return 1;
}


//stock CallCellTimer(playerid)//��� ���������
stock phone_OneSecondTimers(playerid)//��� ���������
{   //���������� �� OneSecondTimers
    if(gCellTimeCounter[playerid] > 0)//��� ��������� //����� �������� � �������� ������
	{//������ ���������
		if(gCellTimeCounter[playerid] >= cchargetime)
		{   //���� ��������� �� 60
			gCellTimeCounter[playerid] = 1;//���������� ����������
			if(playeridMobileCall[playeridMobileCall[playerid]] == playerid)
			{//���� id ������ �������� ������ ������ ������ �������
				CallCost[playerid] += SBizInfo[2][sbEntranceCost];//callcost;//���������� �� 100 ������ ������
			    //format(strings, sizeof(strings), "~r~%d~w~: ~g~$%d",gCellTimeCounter[playerid],CallCost[playerid]);
			    //GameTextForPlayerEx(playerid, strings, 15000, 6);
			}   //�.�. ������ ����� 6000$
		}
		gCellTimeCounter[playerid] += 1;
		format(strings, sizeof(strings), "~r~%d~w~: ~g~$%d",gCellTimeCounter[playerid],CallCost[playerid]);
    	GameTextForPlayerEx(playerid, strings, 15000, 6);
	}
	else
	{
		if(CallCost[playerid] > 0)
		{   //���� ������ ��������� � ��������� ��������� ������ ����
			CrashDetected[playerid] = 30;
			if(PlayerInfo[playerid][pJailed] < 1)
			{//���������� ������ ���������
				GivePlayerMoneyH(fsbiz+2, playerid, -CallCost[playerid]);
				OnGangsExtortionSBiz(2, CallCost[playerid]);
				SBizInfo[2][sbProducts] --;
			}
			CallCost[playerid] = 0;
		}
	}
}


//��� ���������
stock Call_OnPlayerSelectPlayer(playerid, clickedplayerid)
{
	if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� ��� ������� �����...");
		return 1;
	}
	playeridMobileCall[playerid] = clickedplayerid; //caller connecting
	if(playerid == clickedplayerid)
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "PlayerID", MAX_PLAYERS-1);//SetPVarInt(playerid, "PlayerID", -1);
		SendClientMessage(playerid, COLOR_GREY, "   B� �� ������ ������� ������ ����...");//
		return 1;
	}
	if(GetPlayerMoneyH(playerid) < 100)//��� ���������
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� $100 �� ����� !!!");
		return 1;
	}
	if(PlayerInfo[playerid][pMuted] > GetTickCount())
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		format(strings, sizeof(strings), "   �� �� ������ ������������� �� ��������. �� ��������� �� %d ���� !", PlayerInfo[playerid][pMuted] - getdate());
		SendClientMessage(playerid, COLOR_SYSTEM, strings);
		return 1;
	}
    for(new t=0; t< sizeof(Telephone); t++)
    {
		if(!IsPlayerInAnyVehicle(playerid) &&
			IsPlayerInRangeOfPoint(playerid, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
		{
			//--------------------------------------------------------------
			format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
			SetPVarInt(playerid, "gChatSwitcher", Off);
			GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
			//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//--------------------------------------------------------------
			PlaySoundForPlayer(playerid, SOUND_MOBILE_DIALING);//�������� �����
			TogglePlayerControllableEx(playerid, 0);//�������������
			if( IsPlayerConnectedEx(clickedplayerid) )
			{
		        if(PlayerInfo[clickedplayerid][pPnumber] <= 0 || gPhoneOnline[clickedplayerid] != 0)
				{   //���� � ������ ��� �������� //���� ����� �������� �������
					TogglePlayerControllableEx(playerid, true);//�����������
		            SendClientMessage(playerid, COLOR_GREY, "   ������� ���������� !");
					playeridMobileCall[playerid] = MAX_PLAYERS-1;
		            return 1;
		        }
				if(playeridMobileCall[clickedplayerid] == MAX_PLAYERS-1)
				{   //���� ������� ��������
					//new phonenumb == 755;
					//PlaySoundForPlayer(clickedplayerid, SOUND_DOOR_BUZER);
					PlaySoundForPlayer(clickedplayerid, SOUND_MOBRING);
					SendClientMessage(clickedplayerid, COLOR_LILAC, "T��������� 3�����. ������� /pickup ��� ������� ������� ~k~~CONVERSATION_YES~, ����� ������� ������");
					//------------------------------------------------------------------
					//format(strings, sizeof(strings), "* %s ������ ����� �� ���������.", PlayerName(playerid));
					//ProxDetector(playerid, 10.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
					SendClientMessage(playerid, COLOR_GREY, "HAMEK: ������� /hangup ��� ������� ������� ~k~~CONVERSATION_NO~, ����� �������� ������");

					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
					SetPlayerAttachedObjectEx(playerid, MOBILE_SLOT, 330, Right_hand); // 4 = ����, 330 = ������ ��������, 6 = ������ ����
					return 1;
				}
				else {
					TogglePlayerControllableEx(playerid, true);//�����������
					SendClientMessage(playerid, COLOR_GREY, "   ������� ��� ������ �����. ����������� �����...");
				}
			}
			else {
				TogglePlayerControllableEx(playerid, true);//�����������
				SendClientMessage(playerid, COLOR_GREY, "   ������� ��������� ��� ���� �������� ���� !");
			}
			playeridMobileCall[playerid] = MAX_PLAYERS-1;
			return 1;
		}
	}
	//==========================================================================
	if(PlayerInfo[playerid][pPnumber] == 0)
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� �������� !");
		return 1;
	}
	if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SendClientMessage(playerid, COLOR_GREY, "   � ��� �������� ������� (USE: /togphone, ����� ��������)");
		return 1;
	}
	PlaySoundForPlayer(playerid, SOUND_MOBILE_DIALING);//�������� �����
    //new strings[MAX_STRING];
	if( IsPlayerConnectedEx(clickedplayerid) )
	{
        if(PlayerInfo[clickedplayerid][pPnumber] <= 0)
		{   //���� � ������ ��� �������� //���� ����� �������� �������
			SendClientMessage(playerid, COLOR_GREY, "   ������� �� ��������������� � ��������� ���� ��� �� ����� �������� ����� !");
			playeridMobileCall[playerid] = MAX_PLAYERS-1;
            return 1;
        }
        if(gPhoneOnline[clickedplayerid] > 0)
		{   //���� � ������ ��� �������� //���� ����� �������� �������
            SendClientMessage(playerid, COLOR_GREY, "   ������� ���������� !");
			playeridMobileCall[playerid] = MAX_PLAYERS-1;
            return 1;
        }
		if(playeridMobileCall[clickedplayerid] == MAX_PLAYERS-1)
		{   //���� ������� ��������
			//--------------------------------------------------------------
			format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
			SetPVarInt(playerid, "gChatSwitcher", Off);
			GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
			//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//--------------------------------------------------------------
			PlaySoundForPlayer(clickedplayerid, SOUND_MOBRING);//������ �������
			format(strings, sizeof(strings), "T��������� 3����� �� {FFFFFF}%s[%d]. {AFAFAF}������� /pickup ��� ������� ������� ~k~~CONVERSATION_YES~, ����� ������� ������",
				PlayerName(playerid), playerid);//PlayerInfo[playerid][pPnumber]);
			SendClientMessage(clickedplayerid, COLOR_LILAC, strings);
			//------------------------------------------------------------------
			//format(strings, sizeof(strings), "* %s ������ ���� �������.", PlayerName(playerid));
			//SendClientMessage(playerid, COLOR_LILAC, strings);
			SendClientMessage(playerid, COLOR_GREY, "HAMEK: ������� /hangup ��� ������� ������� ~k~~CONVERSATION_NO~, ����� �������� ������");
			if(!IsPlayerInAnyVehicle(playerid))
			{
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
				SetPlayerAttachedObjectEx(playerid, MOBILE_SLOT, 330, Right_hand); // 4 = ����, 330 = ������ ��������, 6 = ������ ����
			}
			else ApplyAnimation(playerid, "CAR_CHAT", "carfone_in", 4.0,0,1,1,1,0);
			return 1;
		}
		else SendClientMessage(playerid, COLOR_GREY, "   ������� ��� ������ �����. ����������� �����...");
	}
	else  SendClientMessage(playerid, COLOR_GREY, "   ������� ��������� ��� ���� �������� ���� !");
	playeridMobileCall[playerid] = MAX_PLAYERS-1;
	return 1;
}


stock SMS_OnPlayerSelectPlayer(playerid, clickedplayerid, const inputtext[])
{
	if(PlayerInfo[playerid][pMuted] > GetTickCount())
	{
		format(strings, sizeof(strings), "   �� �� ������ ������ SMS-���������. �� ��������� �� %d ���� !", PlayerInfo[playerid][pMuted] - getdate());
		SendClientMessage(playerid, COLOR_SYSTEM, strings);
		return 1;
	}
 	/*if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ �� ����� ��������� ������ SMS-��������� !");
		return 1;
	}
	playeridMobileCall[playerid] = clickedplayerid; //caller connecting
	if(playerid == clickedplayerid)
	{
		SendClientMessage(playerid, COLOR_GREY, "   B� �� ������ ������ SMS ������ ����...");//
		return 1;
	}
	if(GetPlayerMoneyH(playerid) < 1000)
	{
		SendClientMessage(playerid, COLOR_GREY, "   � ��� �� ���������� �����!");
		return 1;
	}*/
 	//==========================================================================
	if(PlayerInfo[playerid][pPnumber] == 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� �������� !");
		return 1;
	}
	if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
	{
		SendClientMessage(playerid, COLOR_GREY, "   � ��� �������� ������� (USE: /togphone, ����� ��������)");
		return 1;
	}
	if(!strlen(inputtext) || strlen(inputtext) > 87)
	{
		SendClientMessage(playerid, COLOR_GREY, "   ���� ��������� �� ����� ���� ����������, �.�. ���-�� �������� ������ 87 ��� �����!");
		return 1;
	}
	//new strings[MAX_STRING];
	if( IsPlayerConnectedEx(clickedplayerid) )
	{
        if(PlayerInfo[clickedplayerid][pPnumber] <= 0)
		{   //���� � ������ ��� �������� //���� ����� �������� �������
			SendClientMessage(playerid, COLOR_GREY, "   ������� �� ��������������� � ��������� ���� ��� �� ����� �������� ����� !");
            return 1;
        }
        if(gPhoneOnline[clickedplayerid] > 0)
		{   //���� � ������ ��� �������� //���� ����� �������� �������
            SendClientMessage(playerid, COLOR_GREY, "   ������� ���������� !");
            return 1;
        }
        if(GetPlayerMoneyH(playerid) < SBizInfo[2][sbEntranceCost])
        {
			format(strings, sizeof(strings), "   � ��� ��� $%d �������� !", SBizInfo[2][sbEntranceCost]);
			SendClientMessage(playerid, COLOR_GREY, strings);
            return 1;
        }
        PlaySoundForPlayer(clickedplayerid, SOUND_ROULETTE_NO_CASH);
		//format(strings, sizeof(strings), "SMS: {FFFFFF}%s,{CC99FF}�����������:{FFFFFF}%s[%d] {CC99FF}Ph:{FFFFFF}%d", inputtext, PlayerName(playerid), playerid, PlayerInfo[playerid][pPnumber]);
		format(strings, sizeof(strings), "SMS: {FFFFFF}%s,{CC99FF}�����������:{FFFFFF}%s[%d]", inputtext, PlayerName(playerid), playerid);
		ProxDetectorTelephone(clickedplayerid, COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_GREY, "   ��������� ��������� ����������.");
		if(PlayerInfo[playerid][pJailed] < 1)
		{
			GivePlayerMoneyH(fsbiz+2, playerid, -SBizInfo[2][sbEntranceCost]);//callcost);
			OnGangsExtortionSBiz(2, SBizInfo[2][sbEntranceCost]);//callcost);
			SBizInfo[2][sbProducts] --;
		}
		//}
		//else SendClientMessage(playerid, COLOR_GREY, "   ������� ��� ������ �����. ����������� �����...");
	}
	else  SendClientMessage(playerid, COLOR_GREY, "   ������� ��������� ��� ���� �������� ���� !");
	//playeridMobileCall[playerid] = MAX_PLAYERS-1;
	return 1;
}
