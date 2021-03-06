
new playeridMedicCall = MAX_PLAYERS-1;//ID �������� ������������ �����

//������� ��������

const MAX_BED = 14; // ���� ��������
const MAX_MEDICAL_VIRT = 3; // ���-�� ����������� ����� ��� ��������
new p_MED[MAX_PLAYERS];
//�������
static const stock Float:m_BED_CORDS[MAX_BED][4] =
{
	//������� � ��������
	{1392.2942,-15.5619,1001.4206,180.8236},
	{1392.2452,-12.2048,1001.4206,180.8236},
	{1397.6663,-12.4886,1001.4206,349.1343},
	{1397.5570,-15.7225,1001.4206,349.1343},
	{1400.8430,-19.9001,1001.4206,84.9427},
	{1404.0548,-20.1844,1001.4206,84.9427},
	{1406.6016,-20.0538,1001.4206,0.6551},
	{1406.3263,-23.3818,1001.4206,349.4453},
	{1406.3282,-25.6111,1001.4206,349.4453},
	{1406.3168,-28.9942,1001.4206,349.4453},
	{1406.1917,-31.4886,1001.4206,349.4453},
	{1406.4689,-34.8380,1001.4206,349.4453},
	{1403.5685,-34.0847,1001.4206,266.4113},
	{1400.2258,-33.8751,1001.4206,266.4113}
};

enum m_BED_SYSTEM
{
	mID[MAX_MEDICAL_VIRT],
	mOwned[MAX_MEDICAL_VIRT],
	Text3D:m_MED_TEXT[MAX_MEDICAL_VIRT]
}
new m_BED_NAME[MAX_BED][MAX_MEDICAL_VIRT];
new m_MED[MAX_BED][m_BED_SYSTEM];
//����� ������� ��������

//���� ������ ��������
new fix_med_text[MAX_PLAYERS];


stock medic_OnGameModeInit()
{
	for(new i; i < MAX_BED; i ++)
	{
		for(new j; j < MAX_MEDICAL_VIRT; j ++)
		{
		    m_MED[i][mID][j] = i;
		    m_MED[i][mOwned][j] = INVALID_PLAYER_ID;
			if(m_MED[i][mOwned][j] == INVALID_PLAYER_ID)
			{
				format(strings, 300, "{FFFFFF}����� �%d\n{FFFFFF}������: %s\n{FFFFFF}����� ������������ ������� Y", m_MED[i][mID][j] + 1, (m_MED[i][mOwned][j]!=INVALID_PLAYER_ID?("{AA5555}������"):("{55AA5C}��������")) );
			}
			else
			{
				format(strings, 300, "{FFFFFF}�����: �%d\n{FFFFFF}������: %s\n{FFFFFF}�������: {AA8E55}%s",m_MED[i][mID][j] +  1, (m_MED[i][mOwned][j]!=INVALID_PLAYER_ID?("{AA5555}������"):("{55AA5C}��������")), m_BED_NAME[i][j]);
			}
			m_MED[i][m_MED_TEXT][j] = Create3DTextLabelEx(strings,-1,
				m_BED_CORDS[i][0],m_BED_CORDS[i][1],m_BED_CORDS[i][2],
				5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, j + MEDIC_LS_WORLD1);//,j + MEDIC_LS_WORLD1,-1,3.0);
		}
	}
	print("  vw_medic 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

stock medic_OnPlayerConnect(playerid)
{
    p_MED[playerid] = -1;

    RemoveBuildingForPlayerEx(playerid, 14795, 1388.882, -20.882, 1005.203, 0.250);// �������� 1
}

stock medic_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	if(p_MED[playerid] != -1)
	{
		CLEAR_MED_INFO(playerid);
	}
}

stock medic_OnPlayerDeath(playerid)
{
	if(p_MED[playerid] != -1)
	{
		CLEAR_MED_INFO(playerid);
	}
}
		
stock CLEAR_MED_INFO(playerid)
{
	m_MED[p_MED[playerid]][mOwned][GetPlayerInterior(playerid) - 12] = INVALID_PLAYER_ID;
    format(m_BED_NAME[p_MED[playerid]][GetPlayerInterior(playerid)- 12], 24, "");
    UPDATE_BED_TEXT(p_MED[playerid], GetPlayerInterior(playerid) - 12);
    p_MED[playerid] = -1;
    return 1;
}

stock UPDATE_BED_TEXT(i, j)
{
	strings = "";
	if(m_MED[i][mOwned][j] == INVALID_PLAYER_ID) format(strings, 300, "{FFFFFF}����� �%d\n{FFFFFF}������: %s\n{FFFFFF}����� ������������ ������� Y", m_MED[i][mID][j] + 1, (m_MED[i][mOwned][j]!=INVALID_PLAYER_ID?("{AA5555}������"):("{55AA5C}��������") ));
	else format(strings, 300, "{FFFFFF}�����: �%d\n{FFFFFF}������: %s\n{FFFFFF}�������: {AA8E55}%s",m_MED[i][mID][j] + 1, (m_MED[i][mOwned][j]!=INVALID_PLAYER_ID?("{AA5555}������"):("{55AA5C}��������") ), m_BED_NAME[i][j]);
	Update3DTextLabelEx(m_MED[i][m_MED_TEXT][j],-1,strings);
	printf(" ||||||||||||| %d %d | %d", i,j, m_MED[i][mOwned][j]);
	return 1;
}

stock medic_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
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
	
	if(dialogid != HEAL_DIALOG) return 1;
//ShowPlayerDialogEx(playerid, HEAL_DIALOG, DIALOG_STYLE_MSGBOX, "Hospital", msgitem, "YES", "NO");
//ShowPlayerDialogEx(playerid, HEAL_DIALOG, DIALOG_STYLE_INPUT, "Cracker House", msgitem, "OK", "Cancel");
//ShowPlayerDialogEx(playerid, HEAL_DIALOG, DIALOG_STYLE_INPUT, "Taxi Cab Company", "������� ����� �� ������.\n��������� 10 ������ ������� \n������ ���� �� ����� $100 \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
	if(MenuOperation[playerid] == 40)//healme
	{
		new recovery;
		if(listitem == 0)
		{//������� � ��������
			if(LastHealth[playerid] >= 100.0 && (PlayerInfo[playerid][pSTD] == 0 || PlayerInfo[playerid][pSTD] == IsNotBeenIll)) { SendClientMessage(playerid, COLOR_GREY, "   �� ��������� ������� !"); return 1; }
			if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll)
			{
				recovery = floatround( DutyFiveMinuts*(1+PlayerInfo[playerid][pSTD]/10.0)*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*2 );
			}
			else recovery = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*2;
//30*(1+0/10)*(21+12)*8�=�7920
#if defined vw_sql//#endif
			new ToBase[74+24+2];
			format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), DoH);
			/*mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
		 	{
	       		SendClientMessage(playerid, COLOR_GREY, "   �������� � ׸���� ������ �� ������� � ������� �������!");
				//SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� �������� ���� ����������� �������� � ׸���� ������!");
				recovery = recovery * 3;
			}
			mysql_free_result();*/
			new DBResult:db_result = db_query(db_VW, ToBase);
			if(db_num_rows(db_result))
		 	{
	       		SendClientMessage(playerid, COLOR_GREY, "   �������� � ׸���� ������ �� ������� � ������� �������!");
				//SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� �������� ���� ����������� �������� � ׸���� ������!");
				recovery = recovery * 3;
			}
			db_free_result(db_result);
#endif
	        if(	GetPlayerMoneyH(playerid) < recovery &&
				PlayerInfo[playerid][pLevel] > 1)
		    {
			    SendClientMessage(playerid, COLOR_GREY, "   � ��� �� ���������� �����!");
			    return 1;
			}
			SetPlayerHealthEx(playerid, 250.0);
		    PlayerStoned[playerid] = 0;//�������� �� �����
			SetPlayerDrunkLevel(playerid, 0);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			if(LevelToEpidemics > 0) LevelToEpidemics --;
			if(PlayerInfo[playerid][pLevel] > 1)
			{
				GivePlayerMoneyH(ffamily+DoH, playerid, -recovery);
				FamilyInfo[DoH][fBank] += recovery;
				format(msgitem, sizeof(msgitem), "Hospital: ������ ���� ������� �������� $%d. ��� ������� ��������. ��������� ���!", recovery);
				SendClientMessage(playerid, COLOR_PINK, msgitem);
			}
			PlayerInfo[playerid][pSTD] = IsNotBeenIll;
			//return 1;
		}
		else if(listitem == 1)
		{//���. ������
			//if(PlayerInfo[playerid][pLevel] <= 1) { SendClientMessage(playerid, COLOR_GREY, "   �� �� ���������� � ���. ������� !"); return 1; }
			if(PlayerInfo[playerid][pSTD] == IsNotBeenIll) { SendClientMessage(playerid, COLOR_GREY, "   �� �� ���������� � ���. ������� !"); return 1; }
			if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll) { SendClientMessage(playerid, COLOR_GREY, "   �� ������ ! �������� ������ ���� ������� !"); return 1; }
			recovery = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*8;
#if defined vw_sql//#endif
			new ToBase[74+24+2];
			format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), DoH);
			/*mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
		 	{
	       		SendClientMessage(playerid, COLOR_GREY, "   �������� � ׸���� ������ �� ������� �� �������� ������!");
				recovery = recovery * 2;
			}
			mysql_free_result();*/
			new DBResult:db_result = db_query(db_VW, ToBase);
			if(db_num_rows(db_result))
		 	{
	       		SendClientMessage(playerid, COLOR_GREY, "   �������� � ׸���� ������ �� ������� � ������� �������!");
				//SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� �������� ���� ����������� �������� � ׸���� ������!");
				recovery = recovery * 3;
			}
			db_free_result(db_result);
#endif
	        if(GetPlayerMoneyH(playerid) < recovery)
		    {
				format(msgitem, sizeof(msgitem), "   � ��� ��� $%d �������� !", recovery);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
			    return 1;
			}
			format(msgitem, sizeof(msgitem), "Hospital: ��������� ����������� ���. ������� - $%d. ��������� ���!",recovery);
			SendClientMessage(playerid, COLOR_PINK, msgitem);
			if(PlayerInfo[playerid][pLevel] > 1)
			{
				GivePlayerMoneyH(ffamily+DoH, playerid, -recovery);
				FamilyInfo[DoH][fBank] += recovery;
			}
			PlayerInfo[playerid][pSTD] = IsNotBeenIll;
			SendClientMessage(playerid, COLOR_PINK, "Hospital: ���. ������ �������!");
		}
		else if(listitem == 2)
		{//���������
		    if(PlayerInfo[playerid][pAdrenalin] >= 9)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   � ��� ���� ��� 9 ������ ����������!");
		        return 1;
		    }
			recovery = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*4;
#if defined vw_sql//#endif
			new ToBase[74+24+2];
			format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), DoH);
			/*mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
		 	{
	       		SendClientMessage(playerid, COLOR_GREY, "   �������� � ׸���� ������ �� ������� � ������� �������!");
				//SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� �������� ���� ����������� �������� � ׸���� ������!");
				recovery = recovery * 3;
			}
			mysql_free_result();*/
			new DBResult:db_result = db_query(db_VW, ToBase);
			if(db_num_rows(db_result))
		 	{
	       		SendClientMessage(playerid, COLOR_GREY, "   �������� � ׸���� ������ �� ������� � ������� �������!");
				//SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� �������� ���� ����������� �������� � ׸���� ������!");
				recovery = recovery * 3;
			}
			db_free_result(db_result);
#endif
	        if(	GetPlayerMoneyH(playerid) < recovery)
		    {
			    SendClientMessage(playerid, COLOR_GREY, "   � ��� �� ���������� �����!");
			    return 1;
			}
			GivePlayerMoneyH(ffamily+DoH, playerid, -recovery);
			FamilyInfo[DoH][fBank] += recovery;
			PlayerInfo[playerid][pAdrenalin] ++;
			format(msgitem, sizeof(msgitem), "Hospital: �� ��������� ���� ���������� �� ���� $%d. �� ������ ������������ ��� ��� ������ �� ����(USE: /items).", recovery);
			SendClientMessage(playerid, COLOR_PINK, msgitem);
		}
		//else SendClientMessage(playerid, COLOR_GREY, "   �� �� �������� ���������, ����� ��������� ������� � �������� !");
	}
	if(MenuOperation[playerid] == 22)
	//else if(!strcmp(x_job, "medic", true))//��� �������
	{   //	/accept
		if(playeridMedicCall >= MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   ����� ��� ������ !");
			return 1;
		}
		if( IsPlayerConnectedEx(playeridMedicCall) && gPlayerSpawned[playeridMedicCall] )
		{
			new Float:cX,Float:cY,Float:cZ;
			GetPlayerPos(playeridMedicCall, cX, cY, cZ);
			SetPlayerCheckpointEx(playerid, cX, cY, cZ, CHECKPOINT_SIZE);
			SetPVarInt(playerid, "gCheckpointStatus", playeridMedicCall);
			SetPlayerMarkerForPlayerEx(playerid, playeridMedicCall, COLOR_MAUVE);
			new Float:distance = GetDistanceBetweenPlayers(playerid, playeridMedicCall);
			new speed = 40000;//�/�
			CallTime[playerid] = floatround(distance / speed * 3600);//������ 3600.0
			format(msgitem, sizeof(msgitem), "* �� ������� ����� �� %s[%d], � ��� ���� %d c�����, ����� �������� %.0f �.",
				PlayerName(playeridMedicCall), playeridMedicCall, CallTime[playerid], distance);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* ����� %s ������ ��� �����, ���������� �������� %s ���:c�� � ����� ������� �������.",
				PlayerName(playerid), TimeConverter(CallTime[playerid]) );
			SendClientMessage(playeridMedicCall, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* ����� %s ������ ����� �� %s'a.", PlayerName(playerid), PlayerName(playeridMedicCall));
			SendFamilyMessage(DoH, msgitem);
			GameTextForPlayerEx(playerid, "~w~Medic Caller~n~~r~Goto Red Marker", 5000, 1);
			CallTimeCounter[playerid] = 1;
			GPS_OnOff[playerid] = 1;
			gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			playeridMedicCall = MAX_PLAYERS-1;
			MenuOperation[playerid] = 0;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			    //if(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1 && CallTimeCounter[i] == 0 && MarkerToPlayer[i] == MAX_PLAYERS-1)
			    if(MenuOperation[i] == 22)
			    {
					HideDialog(i);
					MenuOperation[i] = 0;
					TogglePlayerControllableEx(i, 1);//�����������
				}
			}
		}
	}
	return 1;
}


stock medic_OneSecondTimers(playerid)
{
	if( AFK_IdleTime[playerid] >= 3) return 1;
	//---------------------------------------------------------------------------
	if(	//��� ������� � ��������
		gMedicBill[playerid] == 1 && //PlayerInfo[i][pMember] != DoH &&
		LastHealth[playerid] < floatadd(PlayerInfo[playerid][pSHealth], 50.0) )
	{
		/*if(PlayerInfo[playerid][pAccount] != 0) PlayerInfo[playerid][pHealth] = 100.0;
		else
		{
			PlayerInfo[playerid][pHealth] = floatadd(PlayerInfo[playerid][pSHealth], 50.0);//50 + ��������� ��������
		}*/
		//new Float: health = LastHealth[playerid];
		SetPlayerHealthEx(playerid, LastHealth[playerid]+1.0);//PlayerInfo[playerid][pHealth]
		if(LastHealth[playerid] >= floatadd(PlayerInfo[playerid][pSHealth], 50.0))
		{
			if(PlayerInfo[playerid][pSTD] != IsNotBeenIll)
			{
				PlayerInfo[playerid][pSTD] = IsNotBeenIll;
				SetPlayerDrunkLevel(playerid, 0);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* �� ������ ������ ���� �������. ��� ������� ��������. �� ������ �� ������ ������ !");
				if(PlayerInfo[playerid][pSTD] > 0 &&
					PlayerInfo[playerid][pSTD] < IsNotBeenIll &&
					LevelToEpidemics > 0) LevelToEpidemics --;
			}
			PlayerRecoveryHealth(playerid);
			SendClientMessage(playerid, COLOR_PINK, "������: ���� ������� �������! �� ��������!");
		}
	}
	
	if(fix_med_text[playerid] != 0) fix_med_text[playerid] --;
	/*if(Anti_Sbiv[playerid] != 0)
	{
	    Anti_Sbiv[playerid] --;
	    if(Anti_Sbiv[playerid] == 0)
	    {
	        TogglePlayerControllable(playerid, 1);
	        ClearAnimations(playerid, 1);
	    }
	}*/
	if(p_MED[playerid] != -1)
	{
	    //if(!PlayerToPoint(1.5,playerid,m_BED_CORDS[p_MED[playerid]][0],m_BED_CORDS[p_MED[playerid]][1],m_BED_CORDS[p_MED[playerid]][2]))
	    if( IsPlayerInRangeOfPoint(playerid, 1.5, m_BED_CORDS[p_MED[playerid]][0],m_BED_CORDS[p_MED[playerid]][1],m_BED_CORDS[p_MED[playerid]][2]) )
        {
			CLEAR_MED_INFO(playerid);
		    SendClientMessage(playerid, COLOR_PINK, "�� ���������� ��������� �������");
        }
        else
        {
            new Float:h; GetPlayerHealth(playerid, h);
			if(floatround(h + 1) > 100)
			{
			    SetPlayerHealthEx(playerid, 100.0);
				CLEAR_MED_INFO(playerid);
			    gMedicBill[playerid] = 0;
			    StopLoopingAnim(playerid);
			    SendClientMessage(playerid, COLOR_PINK, "�� ������ ���� �������. ������ �� ������ �������� ��������");
			}
			else
			{
				SetPlayerHealthEx(playerid, h + 1.0);
			}
        }
	}
	
	return 1;
}


stock PlayerRecoveryHealth(playerid)
{//���������� �� OneSecondTimers()
	/*if(PlayerInfo[playerid][pAccount] != 0) PlayerInfo[playerid][pHealth] = 100.0;
	else
	{
		PlayerInfo[playerid][pHealth] = floatadd(PlayerInfo[playerid][pSHealth], 50.0);//50 + ��������� ��������
	}
	SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth]);*/
	SetPVarInt(playerid, "gWorldBounds", 0);
	SetPVarInt(playerid, "gSpectating", 0);
	//----------------------------------------------------------------------
	PlayerInfo[playerid][pParam5] = 0;	gParameter5[playerid] = 0;
	SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);

    new cut = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank]);
	GivePlayerMoneyH(ffamily+DoH, playerid, -cut);
	FamilyInfo[DoH][fBank] += cut;
	format(strings, sizeof(strings), "Hospital: ���� �� ���� ����������� ������������ �������� $%d, ��������� ���.", cut);
	SendClientMessage(playerid, COLOR_MAUVE, strings);
	gMedicBill[playerid] = 0;
	CallTime[playerid] = 0;
}

stock medic_OnPlayerPickUpPickup(playerid)
{
	if( IsAtHospitalPill(playerid) )
	{// Hospital near Ammu
		new msgitem[178+10];
		//new ToBase[74+24+2];
		//format(ToBase, sizeof(ToBase), "SELECT `Player`,Family FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), DoH);
		//mysql_query(g_SQL, ToBase); mysql_store_result();
		//if(mysql_num_rows() > 0)
	 	//{
		//	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� �������� ���� ����������� �������� � ׸���� ������!");
		//	return 1;
		//}
		//mysql_free_result();

		//new dlgitem[396];
		new recovery;
		if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll)
		{
			recovery = floatround( DutyFiveMinuts*(1+PlayerInfo[playerid][pSTD]/10.0)*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*2 );
		}
		else recovery = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*2;
		format(msgitem, sizeof(msgitem), "������� � �������� - $%d\n", recovery);

		recovery = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*8;
		format(msgitem, sizeof(msgitem), "%s���. ������ - $%d\n", msgitem, recovery);

		recovery = DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*4;
		format(msgitem, sizeof(msgitem), "%s��������� - $%d\n", msgitem, recovery);

	//\n\n�� ������� ������ ������ ���� �������?", recovery);
		MenuOperation[playerid] = 40;
		ShowPlayerDialogEx(playerid, HEAL_DIALOG, DIALOG_STYLE_LIST, "������������ ���������������", msgitem, "OK", "Cancel");
		return 1;
	}
	if(IsAtHospital(playerid) >= MEDIC_LS_WORLD1 && IsAtHospital(playerid) <= MEDIC_LV_WORLD1)
	{
		if(p_MED[playerid] != -1)
		{
		    m_MED[p_MED[playerid]][mOwned][GetPlayerInterior(playerid)- 12] = INVALID_PLAYER_ID;
		    format(m_BED_NAME[p_MED[playerid]][GetPlayerInterior(playerid)- 12], 24, "");
		    UPDATE_BED_TEXT(p_MED[playerid], GetPlayerInterior(playerid) - 12);
		    p_MED[playerid] = -1;
		}
	}
	return 1;
}

stock medic_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused oldstate
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	new vehicleid = nCarID[playerid];
	//new modelid = nCarModel[playerid];
	if(IsInAmbulanceCar(vehicleid))//��� �������
	{
	    if(	IsPermitToRider(playerid) ||
			PlayerInfo[playerid][pMember] == DoH ||
			PlayerInfo[playerid][pJob] == FIREMAN)
		{
	    	//if(gOnDuty[playerid] == 1) { }
	    	//else { RemovePlayerFromVehicleEx(playerid); SendClientMessage(playerid, COLOR_GREY, "   �� - �� �� ��������� !"); return 1; }
		}
	    else
		{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ��������� !");
			//return 1;
		}
	}
	return 1;
}

stock medic_OnEnterCheckpoint(playerid)
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

stock medic_OnPlayerKeyState_YES(playerid)
{
	//if(	GetPlayerInterior(playerid) == MEDIC_LS_WORLD1 || GetPlayerInterior(playerid) == MEDIC_LV_WORLD1 ||	GetPlayerInterior(playerid) == MEDIC_SF_WORLD1)
	if(	!IsAtHospital(playerid) ) return 1;
    if(p_MED[playerid] != -1) return 1;
    for(new i; i < MAX_BED; i ++)
    {
		if(!IsPlayerInRangeOfPoint(playerid, 2.0, m_BED_CORDS[i][0],m_BED_CORDS[i][1],m_BED_CORDS[i][2])) continue;
		if(m_MED[i][mOwned][GetPlayerInterior(playerid)- 12] != INVALID_PLAYER_ID) return SendErr(playerid, "������ ����� ������");

		SetPlayerPosEx(playerid, m_BED_CORDS[i][0],m_BED_CORDS[i][1],m_BED_CORDS[i][2], m_BED_CORDS[i][3]);
		LoopingAnim(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
		SendClientMessage(playerid, COLOR_MAUVE, "�� ������ ��������� �������");
		p_MED[playerid] = i;
		format(m_BED_NAME[p_MED[playerid]][GetPlayerInterior(playerid)- 12], 24, "%s", PlayerName(playerid));
		m_MED[i][mOwned][GetPlayerInterior(playerid)- 12] = playerid;
		UPDATE_BED_TEXT(i, GetPlayerInterior(playerid) - 12);
		break; //return 1;
    }
	return 1;
}

stock medic_OnPlayerKeyState_SPRINT(playerid)
{
	if(p_MED[playerid] != -1)
	{
		CLEAR_MED_INFO(playerid);
	    SendClientMessage(playerid, COLOR_PINK, "�� ���������� ��������� �������");
	}
}

stock medic_OnPlayerKeyState_JUMP(playerid)
{
	if(p_MED[playerid] != -1)
	{
		CLEAR_MED_INFO(playerid);
	    SendClientMessage(playerid, COLOR_PINK, "�� ���������� ��������� �������");
	}
}



