
//addcar 428,-836.9631,1518.5033,20.9587,176.9585,6,16


stock inkas_OnPlayerConnect(playerid)
{
	PaydeskAccepted[playerid] = MAX_PLAYERS-1; PaydeskAmount[playerid] = 0;//Offer[playerid] = MAX_PLAYERS-1; //��� �����������
}


stock inkas_OnPlayerDisconnect(playerid)
{
	if(Offer[playerid] < MAX_PLAYERS-1)//����� ������ �����������
	{	//���� � ������� ���� ����������
       	SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, "��� ������ ������� ������.");
	    DisablePlayerCheckpointEx(Offer[playerid]);
		PaydeskAccepted[Offer[playerid]] = MAX_PLAYERS-1;
		PaydeskAmount[Offer[playerid]] = 0;
		Offer[playerid] = MAX_PLAYERS-1;
	}
	if(PaydeskAccepted[playerid] < MAX_PLAYERS-2)//����� ����������
	{	//���� � ����������� ���� ������
       	SendClientMessage(PaydeskAccepted[playerid], COLOR_LIGHTBLUE, "��� ���������� ������� ������.");
		Offer[PaydeskAccepted[playerid]] = MAX_PLAYERS-1;
	    DisablePlayerCheckpointEx(playerid);
		PaydeskAccepted[playerid] = MAX_PLAYERS-1;
		PaydeskAmount[playerid] = 0;
	}
}

stock inkas_OnPlayerEnterCheckpoint(playerid)
{
	if(CP[playerid] == CP_INKASSATOR && PlayerInfo[playerid][pJob] == INKASSATOR)//��� ������������ ������ STEP3
	{   //������� � �����
		if(!IsPlayerInAnyVehicle(playerid) || CurState[playerid] != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� ������ ��������� �� ���� �������������� ������ !");
		    return 1;
		}
	    DisablePlayerCheckpointEx(playerid);
	    if(nCarModel[playerid] != 428)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   � ��� �� ��� ��� ������������� �������� !");
		    return 1;
		}
		if(PaydeskAccepted[playerid] > MAX_PLAYERS-1)
	    {
  			if( GetTickCount() < (checktimedeliver[playerid]+CallTime[playerid]*1000)  && !gAnticheat[playerid])
  			{
				format(strings, sizeof(strings), "%s[%d] Reset InkasSkill:%d Paydesk:%d checktimedeliver:%d[%d] sec",
					PlayerName(playerid),playerid, PlayerInfo[playerid][pInkasSkill], PaydeskAmount[playerid], (GetTickCount()-checktimedeliver[playerid])/1000, CallTime[playerid]);
				Log(JOB, strings);

				CP[playerid] = 0;
			    //DisablePlayerCheckpointEx(playerid);
				PaydeskAccepted[playerid] = MAX_PLAYERS-1;
				PaydeskAmount[playerid] = 0;
				PlayerInfo[playerid][pInkasSkill] = 0;
				CallTime[playerid] = 0;
				SendClientMessage(playerid, COLOR_GREY, strings);
				return 1;
   			}
			//format(strings, sizeof(strings), "%s[%d] InkasSkill:%d checktimedeliver:%d sec",
			//	PlayerName(playerid),playerid, PlayerInfo[playerid][pInkasSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
			//Log(JOB, strings);

			new bouse = PaydeskAccepted[playerid]-MAX_PLAYERS;
			if(bouse >= 100)
			{
			    if(SBizInfo[bouse-100][sbTill] < PaydeskAmount[playerid])
			    {
					CP[playerid] = 0;
					PaydeskAccepted[playerid] = MAX_PLAYERS-1;
					PaydeskAmount[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   � ������� ��� ������� �����. ������� ����������.");
					return 1;
			    }
				SBizInfo[bouse-100][sbTill] -= PaydeskAmount[playerid];
			}
			else
			{
			    if(BizInfo[bouse][bTill] < PaydeskAmount[playerid])
			    {
					CP[playerid] = 0;
					PaydeskAccepted[playerid] = MAX_PLAYERS-1;
					PaydeskAmount[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   � ������� ��� ������� �����. ������� ����������.");
					return 1;
			    }
				BizInfo[bouse][bTill] -= PaydeskAmount[playerid];
			}

		   	PlayerInfo[playerid][pInkasSkill] ++;//��������� ������� ����. ������ ������������ ������
			new skill = PlayerInfo[playerid][pInkasSkill];
			new money, percent;
			if(skill <= 50)//���� ����� �������� 1 / 49-�� ������
			{
			    percent = 3;
				if(skill == 50)//���� ����� �������� 50 ������ �� ����������� �� ��������� ������� 2
				{
				    money = (100 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			    	format(strings, sizeof(strings), "B�� ����� ����������� ������ 2 ! ������� %d$.", money);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ������ ������ ������ �� 300000$.");
				}
			}
			else if(skill > 50 && skill <= 100)//2 �������
			{
			    percent = 3;
				if(skill == 100)
				{
			    	money = (200 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			    	format(strings, sizeof(strings), "B�� ����� ����������� ������ 3 ! ������� %d$.", money);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ������ ������ ������ �� 500000$.");
				}
			}
			else if(skill > 100 && skill <= 200)//3 �������
			{
			    percent = 3;
				if(skill == 200)
				{
			    	money = (300 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			    	format(strings, sizeof(strings), "B�� ����� ����������� ������ 4 ! ������� %d$.", money);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ������ ������ ������ �� 800000$.");
				}
			}
			else if(skill > 200 && skill <= 400)//4 �������
			{
			    percent = 3;
				if(skill == 400)
				{
			    	money = (400 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			    	format(strings, sizeof(strings), "B�� ����� ����������� ������ 5 ! ������� %d$.", money);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "�� ������ ������ ������ �� 1000000$.");
				}
			}
			else if(skill > 400)//4 �������
			{
			    percent = 3;
			}
			new amount = floatround(PaydeskAmount[playerid]*percent/100.0);

			new giveplayerid = MAX_PLAYERS-2;
			new playername[MAX_PLAYER_NAME];
			if(bouse >= 100)
			{
				giveplayerid = ReturnUser(SBizInfo[bouse-100][sbOwner]);
				if( IsPlayerConnectedEx(giveplayerid) )
				{
					GivePlayerMoneyB(fsbiz+(bouse-100), giveplayerid, PaydeskAmount[playerid]-amount);

					format(strings, sizeof(strings), "   B� ��������� � �������� $%d �� ���� %s'�. ��� ����������� �� ���� � ����� $%d �� ��������.",
						PaydeskAmount[playerid], SBizInfo[bouse-100][sbOwner], amount);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "���������� %s[%d]: ������� ���� ������ �� %s[%d] �� �����.",
						PlayerName(playerid), playerid, SBizInfo[bouse-100][sbDiscription], bouse-100);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "���������� %s[%d]: ���������� �� ��� ���� $%d (-3 %% �� ��������).",
						PlayerName(playerid), playerid, PaydeskAmount[playerid]-amount);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "%s[%d] inkassator deliver $%d to %s[%d]",
							PlayerName(playerid), playerid, PaydeskAmount[playerid], SBizInfo[bouse-100][sbOwner], bouse-100);
					Log(INKASS,strings);
				}
				else
				{
					giveplayerid = MAX_PLAYERS-2;

					strmid(playername, SBizInfo[bouse-100][sbOwner], 0, strlen(SBizInfo[bouse-100][sbOwner]), MAX_PLAYER_NAME);
#if defined vw_sql//#endif
					//new ToBase[56+10+24];
					new ToBase[127 +  12+10+11+24+10+10+10+10];
					//mysql_real_escape_string(playername, playername);
					format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bank`=`Bank`+%d WHERE `Name`='%s'",
						PaydeskAmount[playerid]-amount, playername);
					//mysql_query(ToBase);
					db_free_result(db_query(db_VW, ToBase));
#endif
					//-----------------------------------------------------------
					//if(money >= 100) FinaceList(giveplayerid, PaydeskAmount[playerid]-amount, 0, fjob+PlayerInfo[playerid][pJob]);
					/*new date[12], time[10];
					new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
					new ly, lmm, ld;	getdate(ly,lmm,ld);
					format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
					format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);*/

#if defined vw_sql//#endif
					format(ToBase, sizeof(ToBase), "INSERT INTO `finance` (`Article`,`Name`,`Receipts`) VALUES (%d,'%s',%d)",
						fsbiz+(bouse-100), playername, PaydeskAmount[playerid]-amount);
					//mysql_query(ToBase);
					db_free_result(db_query(db_VW, ToBase));
#endif
					//-----------------------------------------------------------
					format(strings, sizeof(strings), "   B� ��������� � �������� $%d �� ���� %s'�. ��� ����������� �� ���� � ����� $%d �� ��������.",
						PaydeskAmount[playerid], SBizInfo[bouse-100][sbOwner], amount);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "%s[%d] inkassator deliver $%d to %s[%d]",
							PlayerName(playerid), playerid, PaydeskAmount[playerid], SBizInfo[bouse-100][sbOwner], bouse-100);
					Log(INKASS,strings);
				}
			}
			else if(bouse > -1 && bouse < 100)
			{

				giveplayerid = ReturnUser(BizInfo[bouse][bOwner]);
				if( IsPlayerConnectedEx(giveplayerid) )
				{
					GivePlayerMoneyB(fbiz+bouse, giveplayerid, PaydeskAmount[playerid]-amount);

					format(strings, sizeof(strings), "   B� ��������� � �������� $%d �� ���� %s'�. ��� ����������� �� ���� � ����� $%d �� ��������.",
						PaydeskAmount[playerid], BizInfo[bouse][bOwner], amount);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "���������� %s[%d]: ������� ���� ������ �� %s[%d] �� �����.",
						PlayerName(playerid), playerid, BizInfo[bouse][bDiscription], bouse);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "���������� %s[%d]: ���������� �� ��� ���� $%d (-3 %% �� ��������).",
						PlayerName(playerid), playerid, PaydeskAmount[playerid]-amount);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "%s[%d] inkassator deliver $%d to %s[%d]",
						PlayerName(playerid), playerid, PaydeskAmount[playerid], BizInfo[bouse][bOwner], bouse);
					Log(INKASS,strings);
				}
				else
				{
					giveplayerid = MAX_PLAYERS-2;

					strmid(playername, BizInfo[bouse][bOwner], 0, strlen(BizInfo[bouse][bOwner]), MAX_PLAYER_NAME);
#if defined vw_sql//#endif
					//new ToBase[56+10+24];
					new ToBase[127 +  12+10+11+24+10+10+10+10];
					//mysql_real_escape_string(playername, playername);

					format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bank`=`Bank`+%d WHERE `Name`='%s'",
						PaydeskAmount[playerid]-amount, playername);
					//mysql_query(ToBase);
					db_free_result(db_query(db_VW, ToBase));
#endif
					//-----------------------------------------------------------
					//if(money >= 100) FinaceList(giveplayerid, PaydeskAmount[playerid]-amount, 0, fjob+PlayerInfo[playerid][pJob]);
					/*new date[12], time[10];
					new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
					new ly, lmm, ld;	getdate(ly,lmm,ld);
					format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
					format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);*/
#if defined vw_sql//#endif
					format(ToBase, sizeof(ToBase), "INSERT INTO `finance` (`Article`,`Name`,`Receipts`) VALUES (%d,'%s',%d)",
						fbiz+bouse, playername, PaydeskAmount[playerid]-amount);
					//mysql_query(ToBase);
					db_free_result(db_query(db_VW, ToBase));
#endif
					//-----------------------------------------------------------
					format(strings, sizeof(strings), "   B� ��������� � �������� $%d �� ���� %s'�. ��� ����������� �� ���� � ����� $%d �� ��������.",
						PaydeskAmount[playerid], BizInfo[bouse][bOwner], amount);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

					format(strings, sizeof(strings), "%s[%d] inkassator deliver $%d to %s[%d]",
						PlayerName(playerid), playerid, PaydeskAmount[playerid], BizInfo[bouse][bOwner], bouse);
					Log(INKASS,strings);
				}
			}
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, amount);

	    }
		CP[playerid] = 0;
		PaydeskAmount[playerid] = 0;
		Offer[PaydeskAccepted[playerid]] = MAX_PLAYERS-1;//���������� � ������� ID �����������
		PaydeskAccepted[playerid] = MAX_PLAYERS-1;//���������� � ����������� ID �������
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.8 ", GetTickCount(), timers);
	}
	return 1;
}


stock inkas_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused oldstate
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	//----------------------------------------------------------------------
	//������� ��������� ������� �����������
	if(modelid == 428)//��� ������������ collect money
	{
	    if(PlayerInfo[playerid][pJob] == INKASSATOR)
	    {
			format(strings, sizeof(strings), "Pay-Desk: $%d", PaydeskAmount[playerid]);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� ������ ���������� ������ �� ������� � ���� (USE: /paydesk).");
	    }
	    else if( IsPermitToRider(playerid) ) {	}
		else
		{
	        //RemovePlayerFromVehicleEx(playerid);
	        SendClientMessage(playerid, COLOR_GREY, "   �� �� ���������� !");
			//return 1;
		}
	}
	return 1;
}
