/*
 *            VW_GANGS v1.0
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 19.05.2020
 * @update    : 19.05.2020
 *
 * This file is provided as is (no warranties).
 *
 */
 
new HasZoneAttacker[MAX_TURFS];//�������� ����� ��������� �����
new HasTakingZones[MAX_TURFS];//�������� ����� ����������� �����
new HasLeftZone[MAX_PLAYERS];//���� �������� ��������� ����
new taketurfcount[MAX_TURFS];//������� ������ ���������� � ���� ������ ���� �� � ����� �������� � ����������
new taketurfbackcount[MAX_TURFS];//������� ������� �� ����

stock gangs_OnGameModeInit()
{

/*
#define TEAM_NONE 	0
#define TEAM_GROVE 	1
#define TEAM_BALLAS 2
#define TEAM_AZTEC 	3
#define TEAM_VAGOS 	4
#define TEAM_NANG 	5
#define TEAM_RIFA 	6
#define TEAM_TRIAD 	7
#define TEAM_BIKER 	8
#define TEAM_MAFIA 	9
*/

	LoadTurfsSQL();
	return 1;
}


stock gangs_OnPlayerExitedMenu(playerid, Menu:Current)
{
	//==========================================================================
	if(Current == mGangsVacancies)
	{
		HideMenuForPlayerEx(Current,playerid);
		//TogglePlayerControllableEx(playerid, 1);
		ShowMenuForPlayerEx(mJobMenu1_9,playerid);//�� ���������� �������� ����
	}
}
stock gangs_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//�������� ID ����
	if(Current == mGangsVacancies)
	{
		switch(row)
		{
			case 0..8://1-9
			{
        		/*if(PlayerInfo[playerid][pMember] != 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   �� ���������� ��� � ������! (USE: /uninvite, ����� ���������)");
				}*/
				//else
				if(PlayerInfo[playerid][pLeader] == TEAM_GROVE+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   �� ��� ����� ������ ������� (USE: /uninvite)!");
				}
				else if(
						//(PlayerInfo[playerid][pDrugsSkill] < 500 && PlayerInfo[playerid][pMember] != TEAM_GROVE+row) &&
						//(PlayerInfo[playerid][pGunSkill] < 100 && PlayerInfo[playerid][pMember] != TEAM_GROVE+row) &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*100/100)
					   )
				{
					//SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ����������� ������ 500 !");
					//SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ���������� ������ 100 !");
					format(strings, sizeof(strings), "   ���� �������� %d ������ %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*100/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   � ��� ����������� �������� �� ������ !");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != TEAM_GROVE+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   � ��� ���� ������ (USE: /quitjob, ����� ���� � ������)!");
				}
			    else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[TEAM_GROVE+row][fMembers] > 1 )
				{//���� �� ������� 2 � ����� �������, �� ��������� � ���� ���� ������ 400, � ���� ����� 1 �� ������� �� ������ ���� ���������������� �������
					SendClientMessage(playerid, COLOR_GREY, "   ��� ������c��������� ����� ������ 400 !");
				}
				else
				{
#if defined vw_sql//#endif
				    new ToBase[49+2];
					format(ToBase, sizeof(ToBase), "SELECT `Leader` FROM `players` WHERE `Leader`=%d", TEAM_GROVE+row);// LIMIT 1
					mysql_query(ToBase); mysql_store_result();
					if(mysql_num_rows() == 0)
					{
						if(FamilyInfo[TEAM_GROVE+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, TEAM_GROVE+row);
						else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, TEAM_GROVE+row);
					}
					mysql_free_result();
#endif
					if(!strcmp(FamilyInfo[TEAM_GROVE+row][fLeader], "No-One", true))
					{
						MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+row);
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   � ������ ������� ���� ����� !");
					}

				}
				ShowMenuForPlayerEx(mGangsVacancies, playerid);
			}
			case 9://10 UnInvite
			{//178.124.35.222
			    if(PlayerInfo[playerid][pMember] == 0)
			    {
        			SendClientMessage(playerid, COLOR_GREY, "   �� �� ��������� ������ ����������� !");
				}
				else if(GetPVarInt(playerid, "gShowDialog") != -1)
			    {
        			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ � ������ ������ ���������! �������� ���������� ����!");
				}
				else if(PlayerInfo[playerid][pAccount] == 0)
				{
        			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
				}
				else
				{
					//new family = PlayerInfo[playerid][pMember];
					format(strings, sizeof(strings), "* �� ������ � ��������. �� ������ ����� �����������.", PlayerName(playerid));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
					UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
					//format(strings, sizeof(strings), "AdmCmd: %s has uninvited from Faction %d.", PlayerName(playerid), family);
					//Log(INVITE,strings);
				}
				ShowMenuForPlayerEx(mGangsVacancies, playerid);
			}
		}
	}
}
stock gangs_OnPlayerConnect(playerid)
{
	HasLeftZone[playerid] = MAX_TURFS;//���� �������� ��������� ����
}

stock gangs_OnPlayerSpawn(playerid)//��� ��� ����
{
	for(new j=0; j<MAX_TURFS; j++)//��� ��� ���� MAX_TURFS
	{
		if(	IsAGangs(playerid) || IsAFamilyMember(playerid)	|| PlayerInfo[playerid][pAdmin] == 2)
		{   //��������� ��� ���� ������� �������
			if(TurfInfo[j][zFlash] == 1)
			{
				GangZoneFlashForPlayer(playerid, Turfs[j], FamilyInfo[HasZoneAttacker[j]][fColor]);
			}
		}
	}
}

stock gangs_OnPlayerDisconnect(playerid)//��� ��� ����
{
 	for(new t=0; t<MAX_TURFS; t++)//��� ��� ���� 132 MAX_TURFS
	{
		GangZoneHideForPlayer(playerid, t);//�������� ��� ����
	}
}
//=============== [ TAKE GANGS TURF ] ==============================
stock gangs_OnPlayerDeath(playerid, killerid)//��� ��� ����
{   //���������� �� OnPlayerDeath
	if( gRealWar ) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;
	if(!IsAGangs(playerid)) { return 1; }

//����� ����� ���� ������� �����
    //TogglePlayerSpectatingEx(playerid, 1);
    //PlayerSpectatePlayer(playerid, killerid);
    
	if(	!IsAGangs(killerid) ||
		GetPlayerState(killerid) != PLAYER_STATE_ONFOOT) { return 1; }
	if(IsZoneAttacker(killerid)) return 1;
	for(new j=0; j<MAX_TURFS-1; j++)//��� ��� ���� 132 MAX_TURFS
	{   //��������� ��� ����
		if(IsPlayerInRegion(playerid, j))// && gPlayerSpawned[playerid] == 1==1
		{   //���� ����� ��������� � ����� �� ���� j
			//=============== [ TAKE OTHER GANGS TURF ] ============================
	        if(	PlayerInfo[playerid][pMember] == TurfInfo[j][zFamily] &&
				PlayerInfo[killerid][pMember] != TurfInfo[j][zFamily] &&
				(PlayerInfo[killerid][pMember] == HasZoneAttacker[j] ||
				HasZoneAttacker[j] == TEAM_NONE)	)
	        {   //���� ���� ����������� ����� � ������� ��������� ������ �����
				//� �� ����������� ����� � ������� ��������� ������
				//� ������ ����������� ��������� ����� ��� ���� �� ���������
				//����������� ������
			    taketurfbackcount[j] ++;
				if((taketurfbackcount[j] == GANGAREA_WARNINGS && taketurfbackcount[j] < GANGAREA_TAKE))
				{   //���� ����� 1 �� ���� �� �������� ����
					AttackedGangsTurf(killerid, j);
					HasTakingZones[j] = PlayerInfo[playerid][pMember];
					HasZoneAttacker[j] = PlayerInfo[killerid][pMember];
					//�������� ����� ��������� ����� �� j ����
				}
			}
			break;
		}
	}
	//��������������
	//format(strings, sizeof(strings), "OnPlayerGangWar(playerid:%d, killerid:%d)", playerid, killerid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}
stock AttackedGangsTurf(playerid, gangzone)//playerid = killerid
{   //��������� �� gangs_OnPlayerDeath
	//new strings[MAX_STRING];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
	    if(	IsAGangs(i)	|| IsAFamilyMember(i) )
	    {
			format(strings, sizeof(strings), "GangZone Message: ������� %s[%d] �������� ������ %s",
				regions[gangzone][region_name], gangzone, FamilyInfo[PlayerInfo[playerid][pMember]][fName]);
			SendClientMessage(i, FamilyInfo[PlayerInfo[playerid][pMember]][fColor], strings);
			GangZoneFlashForPlayer(i, Turfs[gangzone], FamilyInfo[PlayerInfo[playerid][pMember]][fColor]);
			TurfInfo[gangzone][zFlash] = 1;//������
			IncreaseRank(playerid, 1);
		}
	}
	//��������������
	//format(strings, sizeof(strings), "AttackedGangsTurf(playerid:%d)", playerid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}//GangZoneStopFlashForAll

stock IsZoneAttacker(playerid)
{
//���� ��� ����� ���� ��������� ���� ������
	for(new j=0; j<MAX_TURFS-1; j++)//��� ��� ���� 132 MAX_TURFS
	{//��������� ��� ����, ������� ������� ��� �����
		if(HasZoneAttacker[j] == PlayerInfo[playerid][pMember])	return 1;
	}
	return 0;
}

//stock TakeGangsTurfTimer(playerid)
stock gangs_OneSecondTimers(playerid)
{   //���������� �� OneSecondTimers
	if(	!IsAGangs(playerid) ) return 1;
	if( GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;//&& AFK_IdleTime[playerid] < 3

	//new strings[MAX_STRING];
	//������� ���� ������ � ����� ���� ��������� ����� ��� ����� ��������� ��� ����
	for(new j=0; j<MAX_TURFS-1; j++)//��� ��� ���� MAX_TURFS=229 //���������� Zone 51 [228]
	{//�� ������� ��������� ���� 51
	    if(j == LCN_TURF1 || j == LCN_TURF2 || j == Yakuz_TURF) continue; //���������� ���� ��� � �����
		if(IsPlayerInRegion(playerid, j))
		{   //���� ����� �� ����� ��������� � ���� j
			CrashDetected[playerid] = 31;

		    if(HasLeftZone[playerid] == j)
			{   //���� ���������� ���� ����� ����� ������� ���� �� ��������
			//if((taketurfbackcount[j] >= GANGAREA_WARNINGS && taketurfbackcount[j] < GANGAREA_TAKE) || TurfInfo[j][zFamily] == 0)// && j!=232
				if((HasZoneAttacker[j] >= TEAM_GROVE && HasZoneAttacker[j] <= TEAM_MAFIA)//���� ���� ���������
				|| (TurfInfo[j][zFamily] == TEAM_NONE && j != (MAX_TURFS-1)) )//��� ���� ����������� � �� �������� ������� ����� ���
				{
				    if(HasZoneAttacker[j] == PlayerInfo[playerid][pMember])
				    {   //���� ���� ��������� ���� ������
						//����� ������ �������
					    format(strings, sizeof(strings), "~g~|~r~%s~g~|~n~~p~%d", regions[j][region_name], taketurfcount[j]);
						GameTextForPlayerEx(playerid, strings, 1500, 6);
						if(taketurfcount[j] <= 0)
						{   //���� ������� �������� �� 0
							TakeGangsTurf(playerid, j);//��������� �-�� ������� ����
							taketurfcount[j] = TimeTakeZone;//����������� �������� ��������
						}
						taketurfcount[j] --;//����� ������ �� ������ ����
					}
					else if(HasTakingZones[j] == PlayerInfo[playerid][pMember])
					//����� ���� ����� ����������� ����������� �����
					{
					    format(strings, sizeof(strings), "~g~|~r~%s~g~|~n~~p~%d", regions[j][region_name], taketurfcount[j]);
						GameTextForPlayerEx(playerid, strings, 1500, 6);
						if(taketurfcount[j] >= TimeTakeZone)
						{   //���� ������� �������� �� ���������
							GangZoneStopFlashForAll(HasLeftZone[playerid]);//���������� �������� � ���� ������� ���������� ����
							TurfInfo[j][zFlash] = 0;
							HasTakingZones[j] = 0;
							taketurfcount[j] = TimeTakeZone;//����������� �������� ��������
							HasZoneAttacker[j] = TEAM_NONE;//�������� ����� ��������� �����
							taketurfbackcount[j] = 0;//�������� ������� �������
						}
						taketurfcount[j] ++;//����� ������ �� ������ ����
					}
				}
			}
		    else if(HasLeftZone[playerid] != j)//���� ����� ����� � ��. ����
		    {//���� ���� � ������� ��������� ����� �� ����� ����������, �.�. �� ������� ����
				if(taketurfbackcount[j] == 0 && TurfInfo[j][zFamily] == TEAM_NONE && j != (MAX_TURFS-1) )
				{   //���� ���� �� ��������� � ���� ����������� 			� �� �������� ������� ����� ���
				    taketurfbackcount[j] ++;
					if(taketurfbackcount[j] == GANGAREA_WARNINGS)
					{   //��������� ������ 1 ���
						AttackedGangsTurf(playerid, j);
						HasTakingZones[j] = TEAM_NONE;
						HasZoneAttacker[j] = PlayerInfo[playerid][pMember];
						//�������� ����� ��������� ����� �� j ����
					}
				}
			}
			//���������� �������� ����� ���� � ������� ��������� �����
			HasLeftZone[playerid] = j;//��������� ��������� �������� ��� �������� ������ �� ����
		}
	}
	return 1;
}
stock TakeGangsTurf(playerid, gangzone)//playerid = killerid,
{//���������� �� TakeGangsTurfTimer
	//new strings[MAX_STRING];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//��������� ���� ����� ������� ���������� �������� ������ ����������
		if( IsAGangs(i) || IsAFamilyMember(i) )
		{
			format(strings, sizeof(strings), "GangZone Message: %s �������� ������� %s[%d]", PlayerName(playerid), regions[gangzone][region_name], gangzone);
			SendClientMessage(i, FamilyInfo[PlayerInfo[playerid][pMember]][fColor], strings);
			GangZoneStopFlashForAll(Turfs[gangzone]);//���������� ��������
			TurfInfo[gangzone][zColor] = FamilyInfo[PlayerInfo[playerid][pMember]][fColor];
			//GangZoneHideForPlayer(i, Turfs[gangzone]);//�������� ���� Turfs[gangzone] ��� ������ � ������ �����
			GangZoneShowForPlayer(i, Turfs[gangzone], TurfInfo[gangzone][zColor]);//����������� ��� ���� ����� ����
			TurfInfo[gangzone][zFamily] = PlayerInfo[playerid][pMember];
			HasZoneAttacker[gangzone] = TEAM_NONE;
			HasTakingZones[gangzone] = TEAM_NONE;
			taketurfbackcount[gangzone] = 0;
			TurfInfo[gangzone][zFlash] = 0;
			taketurfcount[gangzone] = TimeTakeZone;//������������� ����� ������

			IncreaseRank(playerid, 1);
		}
	}

	for(new b=0; b<MAX_BIZ; b++)
	{   //��������� ��� ���� ��� ��������� � ������ ����
		if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], gangzone) )//���� ��� ��������� � ����������� �� ������ j �� ������� zones
		{   //���� ��� ��������� � ������ ����
			//strmid( BizInfo[b][bExtortion], FamilyInfo[PlayerInfo[playerid][pMember]][fName], 0, 20, 255);
			BizInfo[b][bExtortion] = PlayerInfo[playerid][pMember];
		}
	}
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{   //��������� ��� ���� ��� ��������� � ������ ����
		if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], gangzone) )//���� ��� ��������� � ����������� �� ������ j �� ������� zones
		{   //���� ��� ��������� � ������ ����
			//strmid( SBizInfo[sb][sbExtortion], FamilyInfo[PlayerInfo[playerid][pMember]][fName], 0, 20, 255);
			SBizInfo[sb][sbExtortion] = PlayerInfo[playerid][pMember];
		}
	}
    SaveTurfsSQL();
	return 1;
}



stock OnPlayerKeyCheckFireKey(playerid, newkeys, oldkeys)
{   //���������� �� OnPlayerKeyStateChange ��� ��������� ��������� ������
	//#pragma unused oldkeys
	//if(newkeys & KEY_FIRE)
	//if(PRESSED(KEY_FIRE))//1 ������� = 2 ������������
	//((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	if(newkeys == KEY_FIRE && oldkeys != KEY_FIRE)
	{//��������� ������ ����� ������� �������
//��� ���� ������
		new weaponid = GetPlayerWeapon(playerid);
		new ammo = GetPlayerAmmo(playerid);
		new Float:bomb_X, Float:bomb_Y, Float:bomb_Z, Float:bomb_A;
		if(weaponid == 39)//���� � ����� ����� ����� //40 - ���������
 		{	//������ ����� �� ��������� 2.5 �� ����
			if(GetPVarInt(playerid, "gBomb") == 0)
		    {//����� ����� ���� ������������ �����
				//RemovePlayerWeaponEx(playerid, weaponid);//GetPlayerWeapon(playerid)
				SetPlayerAmmo(playerid, weaponid, ammo-1);
				DetectedGun[playerid][weaponid] = 1;
				//LastWeaponInSlot[playerid][GetWeaponSlot(weaponid)] = 0;
				LastAmmo[playerid][weaponid] = ammo-1;

				SetPVarInt(playerid, "gBomb", 1);
				GetXYZInFrontOfPlayer(playerid, 2.5, bomb_X,bomb_Y,bomb_Z, bomb_A);
		   		SetPVarFloat(playerid, "bomb_X", bomb_X);
		   		SetPVarFloat(playerid, "bomb_Y", bomb_Y);
		   		SetPVarFloat(playerid, "bomb_Z", bomb_Z);
				SendClientMessage(playerid, COLOR_GREY, "   ����� �����������!");
				LastWeapon[playerid] = 39;
				//��������� ���� ����� �����������
			}
		}
		else if(weaponid == 39 || weaponid == 40 || LastWeapon[playerid] == 40 || LastWeapon[playerid] == 39)
		{
			if(GetPVarInt(playerid, "gBomb") == 1)
			{//���� ����� �����������
				SetPVarInt(playerid, "gBomb", 0);//�������� �����
				CreateExplosion(GetPVarFloat(playerid, "bomb_X"),GetPVarFloat(playerid, "bomb_Y"),GetPVarFloat(playerid, "bomb_Z"), 7, 25.0);//������ ������ ����� ����� = 8�
				SendClientMessage(playerid, COLOR_RED, "   ����� ��������!");
				SendClientMessage(playerid, COLOR_GREY, "   ������ ��� �������� � 18:00 �� 23:00 � �� ���������� �������!");//� ������� ���
				SendClientMessage(playerid, COLOR_GREY, "   ����������� ������������ ����������� ������ ���� ����!");
				//=============== [ TAKE OTHER GANGS TURF ] ============================
				//��� ��� ����
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//new remainder = (getdate()-8)%7;//������� �� ������� �� 7  && remainder == 0
				//��� 8 - ��� ������ ������ ������� � ����
				//new remainder = (getdate()-1)%7;//������� �� ������� �� 7  && remainder == 0
				//��� 1 - ��� ������ ������� ����������� � ����
				if(	IsAGangs(playerid) &&
					lH >= 18 && lH < 23
				  )//���� ������ �����
				{
					if(IsZoneAttacker(playerid)) return 1;
					for(new j=0; j<MAX_TURFS-1; j++)//��� ��� ���� 132 MAX_TURFS
					{   //���������� � ����� ���� ���� ����� � �����

					    //���� ����� � ����� �� ���� � � ���� �� ���� ����������� ����� � ��� ���� �� ����������� � ���� �� ����������� ����� � ������� ��������� ��������
						if(	IsPlayerInRegion(playerid, j) && TurfInfo[j][zFamily] != 0 && PlayerInfo[playerid][pMember] != TurfInfo[j][zFamily] &&
							IsPointInRegion(GetPVarFloat(playerid, "bomb_X"), GetPVarFloat(playerid, "bomb_Y"), GetPVarFloat(playerid, "bomb_Z"), j) &&//����� � ��� �����
							HasZoneAttacker[j] == TEAM_NONE)
						{   //���� �� ���������

						    //���� ��� ����� ���� ��������� ���� ������

						    taketurfbackcount[j] ++;
							if((taketurfbackcount[j] == GANGAREA_WARNINGS && taketurfbackcount[j] < GANGAREA_TAKE))
							{   //���� ����� 1 �� ���� �� �������� ����
								AttackedGangsTurf(playerid, j);
								HasTakingZones[j] = TurfInfo[j][zFamily];
								HasZoneAttacker[j] = PlayerInfo[playerid][pMember];//��� ����� ��������� ������ �������
								//�������� ����� ��������� ����� �� j ����
							}
							break;
						}
					}
				}
			}
		}

//��� ���� �����
		//----------------------------------------------------------------------
		if(KEYSTATE == 1)
		{
			format(strings, sizeof(strings), "OnPlayerKeyCheckFireKey(newkeys:%d, oldkeys:%d) LastWeapon:%d", newkeys, oldkeys, LastWeapon[playerid]);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
	}
	return 1;
}


