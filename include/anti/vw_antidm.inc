
stock antidm_OnPlayerDeath(playerid, killerid, reason)
{
	if(!AntiDM) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;
	CrashDetected[playerid] = 90;
	if(gRealWar) return 1;
	if(gPlayerBoxing[killerid] != 0) return 1;
	if(gInTerrorsCount[killerid] != 0) return 1;
	if(gInCTerrorsCount[killerid] != 0) return 1;
	if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember] && PlayerInfo[playerid][pMember] != 0)
	{
		//ReductionRank(killerid, -10);
		return 1;
	}
	if(IsACop(killerid) && gOnDuty[killerid]
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			ReductionRank(killerid, -100);
		}
		else if(WantedPoints[playerid] <= 0)
		{//���������� � if(newstate == PLAYER_STATE_WASTED)
			ReductionRank(killerid, -10);
		}
		else if(WantedPoints[playerid] > 0)
		{
			IncreaseRank(killerid, 5); return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoD
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			ReductionRank(killerid, -100);
		}
		else if(PlayerInfo[playerid][pJailed] == 10)
		{//1 ������� ���� ������ ������ �������
//���� ������ ���
//�� ��� ������ ������� ������ �� ������ ������ ����
//� �� ���� ��������� �����
			if( IsPlayerInArea(playerid, specialzone[2]) ) ReductionRank(killerid, -20);
			else
			{
				IncreaseRank(killerid, 10);	return 1;
			}
		}
		else if(IsPlayerInArea(playerid, specialzone[0]) && PlayerInfo[playerid][pJailed] != 10)
		{
			IncreaseRank(killerid, 10);	return 1;
		}
	}
	else if(IsAtHospital(playerid) && PlayerInfo[killerid][pMember] == DoH)
	{
		return 1;
	}
	else if(PlayerInfo[killerid][pMember] == LCN
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember]
		&& PlayerTied[playerid] != 5 && PlayerTied[playerid] != 6 && PlayerTied[playerid] != 8)
	{
		if(PlayerInfo[playerid][pMember] == Yakuza)
		{
			IncreaseRank(killerid, 20);
			return 1;
		}
		if(PlayerInfo[playerid][pJob] == DRUGDEALER || PlayerInfo[playerid][pJob] == ARMSDEALER)
		{
			IncreaseRank(killerid, 1);
			return 1;
		}
		if(IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD)
		{
			IncreaseRank(killerid, 10);
			return 1;
		}
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{
			ReductionRank(killerid, -50);
		}
		if(PlayerInfo[playerid][pLocal] == 243) return 1;
		if(IsPlayerInArea(playerid, specialzone[3])) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == Yakuza
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember]
		&& PlayerTied[playerid] != 5 && PlayerTied[playerid] != 6 && PlayerTied[playerid] != 8)
	{
		if(PlayerInfo[playerid][pMember] == LCN)
		{
			IncreaseRank(killerid, 20); return 1;
		}
		if(PlayerInfo[playerid][pJob] == DRUGDEALER || PlayerInfo[playerid][pJob] == ARMSDEALER)
		{
			IncreaseRank(killerid, 1); return 1;
		}
		if(IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD)
		{
			IncreaseRank(killerid, 10); return 1;
		}
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{
			ReductionRank(killerid, -50);
		}
		if(PlayerInfo[playerid][pLocal] == 244) return 1;
		if(IsPlayerInArea(playerid, specialzone[4])) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == DoJ
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])//CityHall
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			ReductionRank(killerid, -100);
		}
		if(PlayerInfo[playerid][pLocal] == 241)
		{
			IncreaseRank(killerid, 10); return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == Hitman
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
	{
		if( IsPlayerInArea(playerid, specialzone[5]) ) return 1;//�� ���������� �������� ��������� �������� ��������������
		if(GotChaseHitID[killerid] == playerid) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == DoE)
	{
		 if(PlayerInfo[playerid][pLocal] == 253) return 1;//DRIVESCHOOL
	}
	/*else if(PlayerInfo[killerid][pJob] == CARDEALER)//CarDealer
	{
		if( IsPlayerInArea(playerid, specialzone[8]) ) return 1;
	}*/
	else if( IsAGangs(killerid)
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember]
		&& PlayerTied[playerid] != 5 && PlayerTied[playerid] != 6 && PlayerTied[playerid] != 8)
	{
		if(IsAGangs(playerid) && PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
		{
			IncreaseRank(killerid, 20);
			return 1;
		}
	}
	//--------------------------------------------------------------------------
	//new strings[MAX_STRING];
	if( IsPlayerInRangeOfPoint(playerid, 10.0, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]) )
	{//���������� ������
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� �� ����� ������: (x: %.4f, y: %.4f, z: %.4f)!",
			PlayerName(killerid), killerid, PlayerName(playerid), playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);
	}
	else if(IsAtHospital(playerid) && IsAtHospital(killerid) && PlayerInfo[killerid][pMember] != DoH )
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� � ����������� �����: Hospital !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 253 && PlayerInfo[killerid][pLocal] == 253 && PlayerInfo[killerid][pMember] != DoE)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� � ����������� �����: DriveSchool !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 241 && PlayerInfo[killerid][pLocal] == 241 && PlayerInfo[killerid][pMember] != DoJ)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� � ����������� �����: CityHall !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[6]) && IsPlayerInArea(killerid, specialzone[6]) && PlayerInfo[killerid][pMember] != Hitman)
	{   //���� ��� ������ ���� �� ���������� ��������, �� ��
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� � ����������� �����: Hitman Mansion!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[8]) && IsPlayerInArea(killerid, specialzone[8]) && PlayerInfo[killerid][pJob] != CARDEALER)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� � ����������� �����: CarDealer AutoSalon!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 254 && PlayerInfo[killerid][pLocal] == 254)//IsPlayerInArea(playerid, specialzone[11])//Motel
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� � ����������� �����: Motel!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	//���� ����� �� 1 ������ 2 ����
	else if( (GetTickCount()-GetPVarInt(killerid, "KillTime")) <= 60000 && //5 ����� = 300000
		LastKill[killerid] == playerid && LastKill[killerid] != MAX_PLAYERS-1)
	{	//��������� ������
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. ��������� ��������!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
    else if(	PlayerInfo[playerid][pGunLic] != 1 && IsFireArm(reason)
    			&& !IsAGangs(playerid)//�� ����� �������
				&& !IsACop(playerid)//�� ����� �������
				&& PlayerInfo[playerid][pMember] != DoD//�� ����� �������
				&& PlayerInfo[playerid][pMember] != Hitman//�� ����� �������
				//&& PlayerInfo[playerid][pJailed] == 10
				/*((PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid]) ||//�����
				(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid]) ||//�������� �������
				(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid]) ||//�����������
				(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid]) ||//�������
				(PlayerInfo[playerid][pJob] == BUSDRIVER && gJobDuty[playerid]))//�������� ��������*/
		   )
    {   //��������� ������
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� ����������� ������!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
    }
	/*else if(PlayerInfo[playerid][pLevel] == 2 && PlayerInfo[playerid][pMember] == 0)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. �������� ������� 2 ������!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}*/
    else return 1;
 	SendClientMessage(killerid, COLOR_RED, strings);
	SendAllAdminMessage(COLOR_RED, strings, 3);

	OnPlayerPunishment(playerid, killerid, reason);

	if(PlayerInfo[playerid][pLevel] <= 1)
	{   //����� ������ 1 ��� �� ����� �������� ����������
		return 1;
	}
	SetPlayerHealthEx(killerid, 0);
	CrashDetected[playerid] = 91;
    return 1;
}

stock antidm_OnPlayerGiveDamage(playerid, damagedid, weaponid)
{
    if(	PlayerInfo[damagedid][pGunLic] != 1 && IsFireArm(weaponid)
		&& !IsAGangs(damagedid)//�� ����� �������
		&& !IsACop(damagedid)//�� ����� �������
		&& PlayerInfo[damagedid][pMember] != DoD//�� ����� �������
		&& PlayerInfo[damagedid][pMember] != Hitman//�� ����� �������
		//&& PlayerInfo[playerid][pJailed] == 10
		/*((PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid]) ||//�����
		(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid]) ||//�������� �������
		(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid]) ||//�����������
		(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid]) ||//�������
		(PlayerInfo[playerid][pJob] == BUSDRIVER && gJobDuty[playerid]))//�������� ��������*/
	   )
    {   //��������� ������
		format(strings, sizeof(strings), "�� ��������� � ����������� %s! ��� ��� ������ - ������ ��������!", PlayerName(damagedid));
		SendClientMessage(playerid, COLOR_YELLOW, strings);
    }
}
stock antidm_OnPlayerTakeDamage(playerid, killerid, Float:amount, weaponid, bodypart)
{	//playerid - ��� ��� �������� �����
	//killerid - ��� ��� �������
	//amount - ���-�� ����������� ������
	CrashDetected[playerid] = 82;

	if(!AntiDM) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;

	/*new Float:health; GetPlayerHealth(playerid, health);
	if(LastHealth[playerid] == health)
	//if(DetectedGiveDamage[playerid] != 0 && WaitGodModDetected[playerid] <= 0)
	{
       	//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AdmWarning: %s[%d]. ���������� �� ���������� (Damage: %.1f, LastHealth: %.1f)",
			PlayerName(playerid), playerid, amount, LastHealth[playerid]);
		//SendClientMessage(LastDamagedid[playerid], ADMINS_MESSAGE_COLOR, strings);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);

		//SetPlayerHealthEx(playerid, (LastHealth[playerid]-amount));

		//DetectedGiveDamage[playerid] = 0;
		//WaitGodModDetected[playerid] = 0;
	}*/

	if(weaponid == 34 && bodypart == BODY_PART_HEAD)
	{
		SetPlayerHealthEx(playerid, 0);
	}
	if(gRealWar) return 1;
	if(gPlayerBoxing[killerid] != 0) return 1;
	if(gInTerrorsCount[killerid] != 0) return 1;
	if(gInCTerrorsCount[killerid] != 0) return 1;
	//if(!IsFireArm(GetPlayerWeapon(killerid))) return 1;
	if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember] && PlayerInfo[playerid][pMember] != 0)
	{
		//ReductionRank(killerid, -10);
		return 1;
	}

	if(	IsFireArm(weaponid) &&
		PlayerInfo[playerid][pJailed] != 10) checktimedamage[playerid] = GetTickCount();

	GetPlayerHealth(killerid, LastHealth[killerid]);

	new Float: difference;
	if(LastHealth[killerid] >= LastHealth[playerid])
	{//���� �������� ������� ������ ��� � ������
		difference = 1.0 + LastHealth[killerid]/LastHealth[playerid];
	}
	else difference = 2.0;
	//==========================================================================
	if( PlayerInfo[playerid][pAccount] == 365)
	{
		SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
	}
	if(//���� ����� ������ �� ��� �������� � ������
		IsFireArm(weaponid) &&
		(
			PlayerInfo[killerid][pGunLic] != 1 ||//���� ��������
			//(!gAnticheat[killerid] && !strcmp(php_host, "gta.strikearena.ru", true)) ||//���� ��������
			GetPlayerInterior(killerid) != 0 ||//� ����������
			(IsPlayerInArea(killerid, specialzone[6]) && PlayerInfo[killerid][pMember] != Hitman) ||//������� Hitman
			(IsPlayerInArea(killerid, specialzone[8]) && PlayerInfo[killerid][pJob] != CARDEALER) ||//AutoSalon
			(IsAtHospital(killerid) && PlayerInfo[killerid][pMember] != DoH) ||//Hospital
			(PlayerInfo[killerid][pJob] == MINER && gJobDuty[killerid])//��� �������
		)
	  )
	{
		SetPlayerHealthEx(killerid, (LastHealth[killerid]-3*amount));
	}
	//--------------------------------------------------------------------------
//��� �� ��� ������ ��� �������� � ����������� �����
	/*if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember] && PlayerInfo[playerid][pMember] != 0)
	{
		SetPlayerHealthEx(killerid, (LastHealth[killerid]-amount));
	}*/
	if(IsACop(killerid) && gOnDuty[killerid])
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{//���� ��� �������� �� ������������� ������
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		else if(WantedPoints[playerid] <= 0)
		{//���� ��� �������� � ������ ��� �������
   			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		else if(WantedPoints[playerid] > 0)
		{//��������� �� ����� �� ���� � ��������
			return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoD)
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{//���� �������� �� ������������� ������
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		else if(PlayerInfo[playerid][pJailed] == 10)
		{//1 ������� ���� ������ ������ �������
			if( IsPlayerInArea(playerid, specialzone[2]) )
			{//���� �� �������� �� ���� �� ������ ������
				SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
			}
			else
			{
				return 1;
			}
		}
		else if(IsPlayerInArea(playerid, specialzone[0]) && PlayerInfo[playerid][pJailed] != 10)
		{
			return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoH)
	{//�������� �� ������� � ���������
		if(IsAtHospital(playerid)) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == LCN)
	{
		if(PlayerInfo[playerid][pMember] == Yakuza)
		{//��������� �� ������ ������ �����
			return 1;
		}
		if(PlayerInfo[playerid][pLocal] == 243) return 1;//������� LCN
		if(IsPlayerInArea(playerid, specialzone[3])) return 1;//���� LCN
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{//���� ���� ����� �������� �� ������, ������� ��� ������������
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
	}
	else if(PlayerInfo[killerid][pMember] == Yakuza)
	{
		if(PlayerInfo[playerid][pMember] == LCN)
		{
			return 1;
		}
		if(PlayerInfo[playerid][pLocal] == 244) return 1;//������� Yakudza
		if(IsPlayerInArea(playerid, specialzone[4])) return 1;//4 ���� Yakuza
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoJ)//CityHall
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		if(PlayerInfo[playerid][pLocal] == 241)
		{//��������� �� ������������� � �����
			return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == Hitman)
	{
		if( IsPlayerInArea(playerid, specialzone[5]) ) return 1;//�� ���������� �������� ��������� �������� ��������������
		if(GotChaseHitID[killerid] == playerid) return 1;//��������� � ����� ����� ��������� ������
	}
	else if(PlayerInfo[killerid][pMember] == SAN)
	{//��������� �� �������� � ������ ��������
		 if(PlayerInfo[playerid][pLocal] == 249) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == DoE)
	{//��������� �� ����������� � ���������
		 if(PlayerInfo[playerid][pLocal] == 253) return 1;//DRIVESCHOOL
	}
	else if(PlayerInfo[killerid][pJob] == CARDEALER)//CarDealer
	{//��������� �� ����������� � ����������
		if( IsPlayerInArea(playerid, specialzone[8]) ) return 1;
	}
	else if( IsAGangs(killerid) )
	{
		if(IsAGangs(playerid) && PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
		{//��������� �� ����
			return 1;
		}
	}
	//--------------------------------------------------------------------------
	//new strings[MAX_STRING];
	if(IsAtHospital(playerid) && IsAtHospital(killerid) && PlayerInfo[killerid][pMember] != DoH )
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: Hospital !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 241 && PlayerInfo[killerid][pLocal] == 241 && PlayerInfo[killerid][pMember] != DoJ)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: CityHall !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[6]) && IsPlayerInArea(killerid, specialzone[6]) && PlayerInfo[killerid][pMember] != Hitman)
	{   //���� ��� ������ ���� �� ���������� ��������, �� ��
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: Hitman Mansion!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[killerid][pLocal] == 249 && PlayerInfo[killerid][pMember] != SAN)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: CNNStudio !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 253 && PlayerInfo[killerid][pLocal] == 253 && PlayerInfo[killerid][pMember] != DoE)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: DriveSchool !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[8]) && IsPlayerInArea(killerid, specialzone[8]) && PlayerInfo[killerid][pJob] != CARDEALER)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: CarDealer AutoSalon!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 254 && PlayerInfo[killerid][pLocal] == 254)//IsPlayerInArea(playerid, specialzone[11])//Motel
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] � ����������� �����: Motel!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
    else if(	PlayerInfo[playerid][pGunLic] != 1 && IsFireArm(weaponid)
    			&& !IsAGangs(playerid)//�� ����� �������
				&& !IsACop(playerid)//�� ����� �������
				&& PlayerInfo[playerid][pMember] != LCN//�� ����� �������
				&& PlayerInfo[playerid][pMember] != Yakuza//�� ����� �������
				&& PlayerInfo[playerid][pMember] != DoD//�� ����� �������
				&& PlayerInfo[playerid][pMember] != Hitman//�� ����� �������
				//&& PlayerInfo[playerid][pJailed] == 10
				/*((PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid]) ||//�����
				(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid]) ||//�������� �������
				(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid]) ||//�����������
				(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid]) ||//�������
				(PlayerInfo[playerid][pJob] == BUSDRIVER && gJobDuty[playerid]))//�������� ��������*/
		   )
    {   //��������� ������
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] ����������� ������!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
    }
	else if(PlayerInfo[playerid][pMember] == SAN && (playerid == gTranslatorTV || TalkingLive[playerid] != MAX_PLAYERS-1))
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] �������� SAN !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLevel] < 3 && PlayerInfo[playerid][pMember] == 0)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch ������� {FFFFFF}%s[%d] !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	//���� ������� ����� � ������� ������ 2 ����
	/*else if( (GetTickCount()-GetPVarInt(killerid, "KillTime")) <= 60000 && //5 ����� = 300000
		(GetTickCount()-GetPVarInt(killerid, "KillTime")) >= 1000 &&
		LastKill[killerid] == playerid && LastKill[killerid] != MAX_PLAYERS-1)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] ���������!",
			PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}*/
    else return 1;
 	SendClientMessage(killerid, COLOR_RED, strings);

	SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
	CrashDetected[playerid] = 83;
    return 1;
}
