//��� ���������
/*
 ������� (13:26:37 15/12/2012)
������ ������, ��������� �����, ��������� �� �����.
�� ��� ������ ���������� ������ ���� ���� ���� ��������.
����� ���� ���� ������ �������� x2
���� ����� x1
���� ����� ������ ���� � ������� ���� ���������� ������ � ���������� � ���� � �� ���� ������ ��������� ��������� ���
� ����� ���� ������ �� � ����������� �� ������ �� ����� �����
���� �������� ������, �� ��������� ������
*/


new TaxiValue = 50;//50 ������ �� ������� �������


//new TransportDriver[MAX_PLAYERS];//id ��������/������ ��������
//new TransportValue[MAX_PLAYERS];//���� �� ������ �� �����/��������
//new CostRoute[MAX_PLAYERS];//��������� ��������
//new TransportEarning[MAX_PLAYERS];//������ ������� ������ ��� ��������/�����

//��� ��������� STEP8
//��������� ��� ���������, �� � ��������������� ��������
//stock taxi_OnPlayerCallTime(playerid)
stock taxi_OneSecondTimers(playerid)
{
	if(gTransportTime[playerid] <= 0)  return 1;
	
	if( IsPlayerConnectedEx(TransportDriver[playerid])
		&& TransportDriver[playerid] < MAX_PLAYERS-1
		&& IsPlayerInVehicle(playerid, nCarID[TransportDriver[playerid]]) //��� ��������� � ����������
		&& !IsTunTeleport(playerid))
	{	//���� ��������� ��������� ������� TaxiPassenger[i]
		CrashDetected[playerid] = 234;
	    new taxidriver = TransportDriver[playerid];
	    new taxiid = nCarID[taxidriver];
	    new distance = VehInfo[taxiid][cDist]-gTransportTime[playerid];//gTransportTime - ������� ������� �� ������ �������
		if( distance > 94.0) distance = 0;
		new Float: fuel = distance*VehicleArray[nCarModel[taxidriver]-400][fuelConsumption]/(RealMeter*1000.0);//RealMeter=2.5 ������� ������ ������� ����
//1000*11/2500=4.4
		//fuel = 6091*11/2500=26.8004
		//�� ������ �� �� 6091���� 33������� ��������� 31�� �������
		//costfuel = 27
		new Float: costfuel = fuel*FuelCost;//����� * ��������� 1 ����� * ������� ������� = ��������� ��������
//4.4*0.1=0.44
//��������: ��������� ������ ������������, ����� �� ���� ���������, �� ��� ���� ����� ���� ������ ��������
//��������: ����� ��������� ������ ��������,��� ��� ������
//��������: ��� ��������� ������������ ����� ������ �� ������������, �� ��� ������ ������������ ��� �������
//floatround(3.3, floatround_round);
//floatround_round	Round to the nearest integer. A fractional part of exactly 0.5 rounds upwards (this is the default).
//floatround_floor	Round downwards. ����� ������ �� ���� �� �������, �.�. �������������
//floatround_ceil	Round upwards.
//floatround_tozero	Round downwards for positive values and upwards for negative values (�truncate�).

	 //�������� �� ������� ����� � ���������
			/*if(GetPlayerMoneyH(playerid) < TransportCostCounter[playerid])
			{  //���� ����� ���, �� ���������� �� �����
				new strtmp[40+10];
				format(strtmp, sizeof(strtmp), "* ��� ����� %d$, ����� �������� ������.", TransportCostCounter[playerid]);
				SendClientMessage(playerid, COLOR_GREY, strtmp);
				RemovePlayerFromVehicleEx(playerid);

				PlayerInfo[TransportDriver[playerid]][pTaxiSkill] ++;
				TransportCostCounter[TransportDriver[playerid]] = 0;
		    	format(strings, sizeof(strings), "   �������� {FFFFF}%s{0080FF} ������� ���� �����. ���������� ����� {33AA33}$%d!!!", PlayerName(playerid), TransportCostCounter[playerid]);
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);

				TransportCostCounter[playerid] = 0;//�������� ��������� ������� ��� ���������

				gTransportTime[TransportDriver[playerid]] = 0;
				gTransportTime[playerid] = 0;//���������� ��������� ��� ������ �� ������

				TransportDriver[TransportDriver[playerid]] = MAX_PLAYERS-1;
				TransportDriver[playerid] = MAX_PLAYERS-1;//���������� ���������� �������� � ���������

				TaxiPassenger[TransportDriver[playerid]] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������
				TaxiPassenger[playerid] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������
			}
			else
			{*/
	  	TransportCostCounter[playerid] = floatround(costfuel*TransportValue[taxidriver]*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])/(2+2));
//0,44*50*(1+0)/(2+2)�=�5,5
  		//27*50*((1+0)/4)=337.5 ��� 1 ���
  		//27*50*((2+2)/4)=1350
		//}
		new cost;//����������� ��������� ��������� ����������
		//for(new i=0; i<GetMaxPlayers(); i++)
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i)) continue;
			if( IsPlayerInVehicle(i, nCarID[taxidriver]))
			{	//��������� ���� ��� ��������� � ������ �����
				//TransportCostCounter[taxidriver] += TransportCostCounter[i];//�� � ���� ������
				cost += TransportCostCounter[i];
		    }
		}
	    //format(strings, sizeof(strings), "fuel: %.1f costfuel: %.1f TransportCost: %d", fuel, costfuel, TransportCostCounter[playerid]);
		//SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		new strtmp[44+3+6+10+10];
	    format(strtmp, sizeof(strtmp), "~r~%dm ~w~: ~g~+%.1f skill", distance, 2.0*cost/1000.0);//cost, TransportCostCounter[playerid]);
	    GameTextForPlayerEx(TransportDriver[playerid], strtmp, 1500, 6);
    }
	return 1;
}
stock taxi_OnPlayerConnect(playerid)
{
	playeridTaxiAccepted[playerid] = MAX_PLAYERS-1;//��� ���������
	
}

stock taxi_OnPlayerDisconnect(playerid)
{
	if(TransportCostCounter[playerid] > 0 && TransportDriver[playerid] < MAX_PLAYERS-1)
	{	//����� ����� �� ���� �� ����� ����������� ���������� � �������������� �������� ��� ����
	    if(IsPlayerConnected(TransportDriver[playerid]))
		{
			if(PlayerInfo[playerid][pTaxiSkill] < (1000-1)) PlayerInfo[TransportDriver[playerid]][pTaxiSkill] ++;
			TransportCostCounter[TransportDriver[playerid]] = 0;

	    	//format(strings, sizeof(strings), "   �������� %s ������� ���� �����. ���������� ����� $%d!!!", PlayerName(playerid), TransportCostCounter[playerid]);
	    	format(strings, sizeof(strings), "   �������� %s ������� ���� �����.!!!", PlayerName(playerid));
	        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);

			TransportCostCounter[playerid] = 0;//�������� ��������� ������� ��� ���������
			gTransportTime[TransportDriver[playerid]] = 0;
			gTransportTime[playerid] = 0;//���������� ��������� ��� ������ �� ������
			TransportDriver[TransportDriver[playerid]] = MAX_PLAYERS-1;
			TransportDriver[playerid] = MAX_PLAYERS-1;//���������� ���������� �������� � ���������
			TaxiPassenger[TransportDriver[playerid]] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������
			TaxiPassenger[playerid] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������
		}
	}
}

stock taxi_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext

	new msgitem[256+1];
	if(!response && dialogid == CALL_DIALOG)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		if(	MenuOperation[playerid] == 22 || MenuOperation[playerid] == 23 ||
			MenuOperation[playerid] == 24)
		{
			if(!gLoading[playerid] && !gUnLoading[playerid])
			{
				TogglePlayerControllableEx(playerid, 1);//�������������
			}
		}
		Offer[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "RefillPrice", 0);
		gNoFuel[playerid] = 0;
		SetPVarInt(playerid, "RepairPrice", 0);
		SetPVarInt(playerid, "TuningPrice", 0);//���� �� ������ ��������

		format(msgitem, sizeof(msgitem), "%s ��������� �� ������������ ������ !!", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		MenuOperation[playerid] = 0;
	 	return 1;
	}
	if(dialogid != TAXI_DIALOG) return 1;//��� ��������� STEP10
//ShowPlayerDialogGap(playerid, TAXI_DIALOG, DIALOG_STYLE_MSGBOX, "���������",
	SetPVarInt(playerid, "gShowDialog", -1);
	//GivePlayerMoneyH(fjob+PlayerInfo[TransportDriver[playerid]][pJob], playerid, -TransportCostCounter[playerid]);
 		//TAX -= TransportCostCounter[playerid];
	if(response)
	{
//���� ������ ��������������� ����������
	    //format(strings, sizeof(strings), "~w~Passenger left the ~n~~g~Earned ~r~$%d",TransportCostCounter[playerid]);//+money
	    //GameTextForPlayerEx(TransportDriver[playerid], strings, 5000, 1);
    	//format(strings, sizeof(strings), "   �������� %s ������� ��� ��������� ���������. ���������� ����� $%d!", PlayerName(playerid), TransportCostCounter[playerid]);//+money
        //SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		if(MenuOperation[playerid] == 43)//��� ��������� STEP2
		{
	        gJobDuty[playerid] = 1;
	        TaxiDriversCounter += 1;
			TransportValue[playerid] = TaxiValue;
			TransportCostCounter[playerid] = 0;

			if(listitem == 0)
			{
				/*if(TaxiDriver[0] < MAX_PLAYERS-1)
				{
	   				format(msgitem, sizeof(msgitem), "   ������� ��� ����� %s[%d] !", PlayerName(TaxiDriver[0]), TaxiDriver[0]);
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}*/
				TaxiDriver[0] = playerid;//�������� ID ������ �� ���� ��������
    			format(msgitem, sizeof(msgitem), "������� {FFFFFF}%s[%d]: ���-������. ����� �� ������: {33AA33}$%d.",
					PlayerName(playerid), playerid, TransportValue[playerid]);
    			//JobNews(COLOR_ORANGE,msgitem);
    			new text[55+10];
    			format(text, sizeof(text), "���-������\n���� �� �������: {33AA33}$%d.", TransportValue[playerid]);
			    //LabelOnHead[playerid] = Create3DTextLabel(text, COLOR_ORANGE, 0.0,0.0,0.0, 50.0,0,1);
			    //Attach3DTextLabelToVehicle(LabelOnHead[playerid], nCarID[playerid], 0.0, 0.0, 1.0);
				DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0); 
			}
			else if(listitem == 1)
			{
				/*if(TaxiDriver[1] < MAX_PLAYERS-1)
				{
	   				format(msgitem, sizeof(msgitem), "   ������� ��� ����� %s[%d] !", PlayerName(TaxiDriver[1]), TaxiDriver[1]);
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}*/
				TaxiDriver[1] = playerid;
	   			format(msgitem, sizeof(msgitem), "������� {FFFFFF}%s[%d]: ���-������. ����� �� ������: {33AA33}$%d.",
				   	PlayerName(playerid), playerid, TransportValue[playerid]);
	   			//JobNews(COLOR_ORANGE,msgitem);
    			new text[55+10];
    			format(text, sizeof(text), "���-������\n���� �� �������: {33AA33}$%d.", TransportValue[playerid]);
				//Delete3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    //LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0,0.0,0.0, 50.0,0,1);
			    //Attach3DTextLabelToVehicle(LabelOnHead[playerid], nCarID[playerid], 0.0, 0.0, 1.0);
				DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0);
			}
			else if(listitem == 2)
			{
				/*if(TaxiDriver[2] < MAX_PLAYERS-1)
				{
	   				format(msgitem, sizeof(msgitem), "   ������� ��� ����� %s[%d] !", PlayerName(TaxiDriver[2]), TaxiDriver[2]);
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}*/
				TaxiDriver[2] = playerid;
	   			format(msgitem, sizeof(msgitem), "������� {FFFFFF}%s[%d]: ���-��������. ����� �� ������: {33AA33}$%d.",
				   	PlayerName(playerid), playerid, TransportValue[playerid]);
	   			//JobNews(COLOR_ORANGE,msgitem);//60+
    			new text[55+10];
    			format(text, sizeof(text), "���-�������c\n���� �� �������: {33AA33}$%d.", TransportValue[playerid]);
				//Delete3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    //LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0,0.0,0.0, 50.0,0,1);
			   //Attach3DTextLabelToVehicle(LabelOnHead[playerid], nCarID[playerid], 0.0, 0.0, 1.0);
			    DestroyDynamic3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
			    LabelOnHead[playerid] = Create3DTextLabelEx(text, COLOR_ORANGE, 0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, nCarID[playerid], 1, 0);
			}
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FF6600}%s\n", lH,lM,lS, msgitem);
			//--------------------------------------------------------------
//��� ��������� STEP7
			//���� �������� �����, � ������� ����� � ����� ���
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
		        if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(!IsPlayerInAnyVehicle(i)) continue;
				if(GetPlayerState(i) != PLAYER_STATE_PASSENGER) continue;
	            if( !IsPlayerInVehicle(i, nCarID[playerid]) ) continue;
               	TransportDriver[i] = playerid;//�������� ID �������� �� ������� ���������
               	TaxiPassenger[playerid] = i;//�������� ID ��������� �� ������� ��������
               	//��� ���������� ���������� ����� ���������� �� ����������

			    gTransportTime[i] = gTransportTime[playerid];//�������� ������� ������ � ������� ���� ������ ��� ���������
			    //����� ������ �� ��������� ������

               	TransportCostCounter[i] += TransportValue[i];
				GPS_OnOff[playerid] = 0;
				//format(msgitem, sizeof(msgitem), "* �� �������� %d$ �������� �����.", TransportValue[playerid]);
				//SendClientMessage(i, COLOR_LIGHTBLUE, msgitem);
    			format(msgitem, sizeof(msgitem), "~w~Passenger %s~n~~g~has chosen your Taxi", PlayerName(i));//+money
    			GameTextForPlayerEx(playerid, msgitem, 5000, 1);
    		}
		}
		else if(MenuOperation[playerid] == 44)
		{
			if(PlayerInfo[playerid][pLevel] > 0)
			{//��� ���� ������� ���, ������ ����� ���������.
				if(PlayerInfo[playerid][pTaxiSkill] < (1000-2.0*TransportCostCounter[playerid]/1000.0)) {
					PlayerInfo[TransportDriver[playerid]][pTaxiSkill] += floatround(2.0*TransportCostCounter[playerid]/1000.0);
				}
				//GivePlayerMoneyB(fjob+PlayerInfo[TransportDriver[playerid]][pJob], TransportDriver[playerid], TransportCostCounter[playerid]);//��������� ����� ������ ����� ��������� ��� �������
				//TAX += TransportCostCounter[playerid];
		    	format(strings, sizeof(strings), "   �������� %s ������� ��� ��������� ���������!", PlayerName(playerid));//+money
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		    	format(strings, sizeof(strings), "   �� �������� %d ����� ����� ������ ��������!", floatround(2.0*TransportCostCounter[playerid]/1000.0));//+money
	        	SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
			}
		}
		else if(MenuOperation[playerid] == 24)
		//else if(!strcmp(x_job, "taxi", true))//��� ��������� STEP4
		{
			if(playeridTaxiCall >= MAX_PLAYERS-1)
			{   //���� ���-�� ������ �����
				SendClientMessage(playerid, COLOR_GREY, "   ����� ��� ������ !");
				return 1;
			}
			if( IsPlayerConnectedEx(playeridTaxiCall) && gPlayerSpawned[playeridTaxiCall] )
			{
				new Float:cX,Float:cY,Float:cZ;
				GetPlayerPos(playeridTaxiCall, cX, cY, cZ);
				SetPlayerCheckpointEx(playerid, cX, cY, cZ, CHECKPOINT_SIZE);
				SetPVarInt(playerid, "gCheckpointStatus", playeridTaxiCall);
				SetPlayerMarkerForPlayerEx(playerid, playeridTaxiCall, COLOR_LIGHTYELLOW);
				new Float:distance = GetDistanceBetweenPlayers(playerid, playeridTaxiCall);
				new speed = 40000;//�/�
				CallTime[playerid] = floatround(distance / speed * 3600);//������ 3600.0
				format(msgitem, sizeof(msgitem), "* �� ������� ����� �� %s[%d], � ��� ���� %d c�����, ����� ��������� �� ����.",
					PlayerName(playeridTaxiCall), playeridTaxiCall, CallTime[playerid]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
				format(msgitem, sizeof(msgitem), "* �������� ����� %s ������ ��� �����, ���������� �������� %s ���:c�� � ����� ������� �������.",
					PlayerName(playerid), TimeConverter(CallTime[playerid]));
				SendClientMessage(playeridTaxiCall, COLOR_ORANGE, msgitem);
				format(msgitem, sizeof(msgitem), "* ������� %s ������ ����� �� %s'a.", PlayerName(playerid), PlayerName(playeridTaxiCall));
				SendJobMessage(13, COLOR_ORANGE, msgitem);
				//GameTextForPlayerEx(playerid, "~w~Taxi Caller~n~~r~Goto Red Marker", 5000, 1);
				CallTimeCounter[playerid] = 1;//��������� ���� ��� ������� ��������
				playeridTaxiAccepted[playerid] = playeridTaxiCall;//�������� ID ���������� �����
				GPS_OnOff[playerid] = 1;
				gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
				playeridTaxiCall = MAX_PLAYERS-1;//����������
				MenuOperation[playerid] = 0;
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				    //if(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1 && CallTimeCounter[i] == 0 && MarkerToPlayer[i] == MAX_PLAYERS-1)
				    if(MenuOperation[i] == 24)
				    {
						HideDialog(i);
						MenuOperation[i] = 0;
						TogglePlayerControllableEx(i, 1);//�����������
					}
				}
			}
		}
	}
	else
	{
		if(MenuOperation[playerid] == 44)
		{
		    //format(strings, sizeof(strings), "~w~Passenger left the ~n~~g~Earned ~r~$%d",TransportCostCounter[playerid]);//+money
		    //GameTextForPlayerEx(TransportDriver[playerid], strings, 5000, 1);
	    	//format(strings, sizeof(strings), "   �������� %s ������� ��� ��������� �� ���������. �� �� �������� $%d!!", PlayerName(playerid), TransportCostCounter[TransportDriver[playerid]]);//+money
			if(PlayerInfo[playerid][pLevel] > 0)
			{//��� ���� ������� ���, ������ ����� ���������.
				if(PlayerInfo[playerid][pTaxiSkill] < (1000-2*TransportCostCounter[playerid]/1000.0)) {
					PlayerInfo[TransportDriver[playerid]][pTaxiSkill] += floatround(2.0*TransportCostCounter[playerid]/1000.0);
				}
				//GivePlayerMoneyB(fjob+PlayerInfo[TransportDriver[playerid]][pJob], TransportDriver[playerid], TransportCostCounter[playerid]);//��������� ����� ������ ����� ��������� ��� �������
		    	format(strings, sizeof(strings), "   �������� %s ������� ��� ��������� �� ���������!", PlayerName(playerid));//+money
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
		    	format(strings, sizeof(strings), "   �� �������� ����� %d ����� ����� ������ ��������!", floatround(2.0*TransportCostCounter[playerid]/1000.0));//+money
		        SendClientMessage(TransportDriver[playerid], COLOR_LIGHTBLUE, strings);
			}
		}
	}
	if(MenuOperation[playerid] == 44)
	{
		TransportCostCounter[TransportDriver[playerid]] = 0;
		TransportCostCounter[playerid] = 0;//�������� ��������� ������� ��� ���������
		gTransportTime[TransportDriver[playerid]] = 0;
		gTransportTime[playerid] = 0;//���������� ��������� ��� ������ �� ������
		TransportDriver[TransportDriver[playerid]] = MAX_PLAYERS-1;
		TransportDriver[playerid] = MAX_PLAYERS-1;//���������� ���������� �������� � ���������
		TaxiPassenger[TransportDriver[playerid]] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������
		TaxiPassenger[playerid] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������
	}
	return 1;
}

stock taxi_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER)
	{   //���� ����� ��� �� ���� � ������ � ������� ��� ��������
//��� ��������� STEP10 ������
		if(TransportCostCounter[playerid] > 0 && PlayerInfo[playerid][pJob] == TAXIDRIVER)// && TaxiPassenger[playerid] < MAX_PLAYERS-1
		{   //������� ����� �� ����� �� ����� ����������� ���������� � �������������� ��������� ��� ����
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
		        if( !IsPlayerConnectedEx(i) ) continue;
				//if(!IsPlayerInAnyVehicle(i)) continue;
				//if(GetPlayerState(i) != PLAYER_STATE_PASSENGER) continue;
				//if(i != TaxiPassenger[playerid]) continue;//�� ����� �������� ��� ���������� ����������
				if(TransportDriver[i] != playerid) continue;

 				//GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], i, -TransportCostCounter[i]);
		    	format(strings, sizeof(strings), "   ������� %s ������� ������������ �����.", PlayerName(playerid));//+money
		        SendClientMessage(i, COLOR_LIGHTBLUE, strings);

				TransportCostCounter[playerid] += TransportCostCounter[i];//���� ���� ����� ����������
				TransportCostCounter[i] = 0;//�������� ��������� ������� ��� ���������
				gTransportTime[i] = 0;//���������� ��������� ��� ������ �� ������
				TransportDriver[i] = MAX_PLAYERS-1;//���������� ���������� �������� � ���������
				TaxiPassenger[i] = MAX_PLAYERS-1;//���������� ���������� ��������� � ��������

    		}
 			GPS_OnOff[playerid] = 0;
			//GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, TransportCostCounter[playerid]);
			TransportCostCounter[playerid] = 0;//�������� ��������� ������� ��� ���������
			gTransportTime[playerid] = 0;//���������� ��������� ��� ������ �� ������
			TransportDriver[playerid] = MAX_PLAYERS-1;//�� �������� ���������� ���������� �������� � ���������
			TaxiPassenger[playerid] = MAX_PLAYERS-1;//�� ��������� ���������� ���������� ��������� � ��������
		}//��� ��������� �����
//��� ��������� STEP11
		if(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid])
		{	//Taxi Cab Company
			FixJobCounter(playerid);
			//SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
	        SendClientMessage(playerid, COLOR_ORANGE, "   �� ������ �� �� ��������� ����� ������ � �� ��������� ������ ������.");
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{
		//----------------------------------------------------------------------
//��� ���������
        if(GetSeatVehiclePlayer(nCarID[playerid], 0) != INVALID_PLAYER_ID)
        {//���� �� ���� ����� ������ ��� �� �����
			new driver = GetSeatVehiclePlayer(nCarID[playerid], 0);
			if(PlayerInfo[driver][pJob] == TAXIDRIVER && gJobDuty[driver])
			{
	      		gTransportTime[playerid] = VehInfo[nCarID[driver]][cDist];//�������� ������� ������
	           	TransportCostCounter[playerid] += TransportValue[driver];
	           	TransportDriver[playerid] = driver;//�������� ID �������� �� ������� ���������
	           	TaxiPassenger[driver] = playerid;//�������� ID ��������� �� ������� ��������

				GivePlayerMoneyH(fjob+PlayerInfo[driver][pJob], playerid, -TransportValue[driver]);//�������� ������ � ��������� ���� �� ������ �� �����
				BizInfo[0][bTill] += TransportValue[driver]; BizInfo[0][bExport] += TransportValue[driver];
				
				GPS_OnOff[driver] = 0;
				//format(strings, sizeof(strings), "* �� �������� %d$ �������� ����� %s.", TransportValue[driver], PlayerName(driver));
				//SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	   			format(strings, sizeof(strings), "~w~Passenger %s~n~~g~has chosen your Taxi", PlayerName(playerid));//+money
	   			GameTextForPlayerEx(driver, strings, 5000, 1);
			}
		}
	}
	else if(newstate == PLAYER_STATE_ONFOOT)//���� ID ������ ��������� ����� ��������� �� �����
	{   //���� ID ������ ��������� ����� ��������� 1
		if(TransportDriver[playerid] < MAX_PLAYERS-1)//��� ��������� STEP9
		{   //�������� ����� �� ����� �� ����� �������������� �������� ��� ����
		//TransportCostCounter[playerid] > 0// ����������� ����������  - �� �������, �.�. ��� ������ �� ����� � ������� ����������� �� �������� ������
	//printf("TaxiDriver: %d TaxiCost: %d",  TransportDriver[playerid], TransportCostCounter[playerid]);
		    if(	IsPlayerConnected(TransportDriver[playerid]) && !IsPlayerNPC(TransportDriver[playerid]))
			{   //���� ��� ������� ��� � ����
				MenuOperation[playerid] = 44;
				ShowPlayerDialogGap(playerid, TAXI_DIALOG, DIALOG_STYLE_MSGBOX, PlayerName(TransportDriver[playerid]),
					"�� �������� ��������� �������?\n\n{AFAFAF}������� YES, ���� ��������.", "YES", "NO");
			}
		}
	}
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	taxi_TakeTask(playerid, modelid);
	return 1;
}

stock taxi_TakeTask(playerid, modelid)
{
	//������� ��������� ������� ��������
	if(modelid == 420 || modelid == 438)//��� ��������� STEP1
	{
		if(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid] == 0)
		{
	    	new listitems[] = "1\tLS\n2\tSF\n3\tLV\n";
			MenuOperation[playerid] = 43;
			ShowPlayerDialogEx(playerid, TAXI_DIALOG, DIALOG_STYLE_LIST, "������������: �������� ����� ��� ���������", listitems, "OK", "Cancel");//��� ��������� STEP2
   		}
   		else if( IsPermitToRider(playerid) ) {	}
		else if( PlayerInfo[playerid][pJob] != TAXIDRIVER )
		{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   �� �� �������� ����� !");
			//return 1;
		}
	}///��� ��������� �����
	return 1;
}


stock taxi_OnEnterCheckpoint(playerid)
{
	if(GetPVarInt(playerid, "gCheckpointStatus") != CHECKPOINT_NONE)//���� ��� ���������� ������ GPS ��� �� ������ ��� ������ ������
	{   //���� gCheckpointStatus == 255
		if(CallTimeCounter[playerid] > 0)//��� ������� //��� ������������� //��� ��������� STEP6
		{
			CallTimeCounter[playerid] = 0;
			CallTime[playerid] = 0;
			//format(strings, sizeof(strings), "~p~BPEM%s ~w~%s", RusToGame("�"), TimeConverter(CallTimeCounter[playerid]) );
			//PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strings);
			PlayerTextDrawSetStringEx(playerid, txdRaceTime[playerid], TimeConverter(CallTimeCounter[playerid]));
			/*if(PlayerInfo[playerid][pCarTime] <= 0)
			{
				gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			}*/
		}

		//SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], COLOR_ALIVE);// 0xFF0000FF
		SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], ACTION_COLOR);
		playeridTaxiAccepted[playerid] = MAX_PLAYERS-1;
		DisablePlayerCheckpointEx(playerid);
		SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
		GPS_OnOff[playerid] = 0;
		GameTextForPlayerEx(playerid, "~r~RedMarker gone", 2500, 1);
	}
}
