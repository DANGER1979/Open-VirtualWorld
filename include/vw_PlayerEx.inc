
//##############################################################################//
//                                                                              //
//                               ������� ��������                               //
//                                                                              //
//##############################################################################//
//���������� �� Is Check

stock IsAnInstructor(playerid)//���� �� ���� ������� 11 ��� ����� ������� 11 �� ������� 1 ����� 0
{
    if(PlayerInfo[playerid][pLeader] == DoE) { return 1; }
	if(PlayerInfo[playerid][pMember] == DoE) { return 1; }
	return 0;
}
stock IsAFamilyMember(playerid)//���� �� ���� ������ LCN,Yacuza,Hitman ��� ����� ������ 5/6/8 �� ������� 1 ����� 0
{
    new leader = PlayerInfo[playerid][pLeader];
    new member = PlayerInfo[playerid][pMember];
    if(member == LCN || member == Yakuza) { return 1; }
	if(leader == LCN || leader == Yakuza) { return 1; }
	return 0;
}
stock IsACop(playerid)//���� �� PoliceMen/FBI Agent ��� ����� ������ 1/2 �� ������� 1 ����� 0
{
    new leader = PlayerInfo[playerid][pLeader];
    new member = PlayerInfo[playerid][pMember];
    if(member == DoT || member == FBI) { return 1; }
	if(leader == DoT || leader == FBI) { return 1; }
	return 0;
}
stock IsAgentCID(playerid)
{
	if(	PlayerInfo[playerid][pMember] == FBI &&
	 	(PlayerInfo[playerid][pRank] == 3 ||
		PlayerInfo[playerid][pRank] == 5 ||
		PlayerInfo[playerid][pRank] == 7 ||
		PlayerInfo[playerid][pRank] == 9)) return 1;
	return 0;
}

stock IsAMilitary(playerid)
{
    new skin = PlayerInfo[playerid][pModel];
    if(skin == 73 || skin == 179 || skin == 206  || skin == 287 || skin == 191) { return 1; }
    skin = PlayerInfo[playerid][pChar];
	if(skin == 73 || skin == 179 || skin == 206  || skin == 287 || skin == 191) { return 1; }
	skin = GetPlayerSkin(playerid);
	if(skin == 73 || skin == 179 || skin == 206  || skin == 287 || skin == 191) { return 1; }
	return 0;
}




//##############################################################################//
//                                                                              //
//                             ������������� �������                            //
//                                                                              //
//##############################################################################//
//�-�� ������� �� ����� ����� Ex, ������ ������� ����� ���������������� ����������
//� ����������� ���� ����� ��� ��������

new gCheckArmedWeapon[MAX_PLAYERS];


//----------------------------------------------------------



stock SetPlayerWeatherEx(playerid, weather)
{
	SetPVarInt(playerid, "PlayerWeather", weather);
	return SetPlayerWeather(playerid, weather);
}


stock ShowPlayerNameTagForPlayerEx(playerid, showplayerid, show)
{   //��� ������� � ������ �����
	if(show == 0)
    {
 		gTagForPlayer[showplayerid] = show;//������������� �������� � ��������� ���������(0)
		ShowPlayerNameTagForPlayer(playerid, showplayerid, show);
		/*new strtmp[33+24+3];
		format(strtmp, sizeof(strtmp), "~w~Nametags ~r~OFF for ~w~%s[%d]", PlayerName(playerid), playerid);
	    GameTextForPlayerEx(showplayerid, strtmp, 1000, 5);*/
	    IsPlayerTagShow[playerid][showplayerid] = show;//�������� ��� ������ playerid ������ ��� showplayerid
	}
	else//1
	{
 		gTagForPlayer[showplayerid] = show;//������������� �������� � ��������� ��������(1)
		ShowPlayerNameTagForPlayer(playerid, showplayerid, show);
		/*new strtmp[33+24+3];
		format(strtmp, sizeof(strtmp), "~w~Nametags ~r~ON for ~w~%s[%d]", PlayerName(playerid), playerid);
	    GameTextForPlayerEx(showplayerid, strtmp, 1000, 5);*/
	    IsPlayerTagShow[playerid][showplayerid] = show;//�������� ��� ������ playerid �������� ��� showplayerid
	}

	//ShowPlayerNameTagForPlayer(playerid, showplayerid, show);
	//IsPlayerTagShow[showplayerid] = playerid;
	//1 - ��� ������ showplayerid ����� ������� ��� ������ playerid
	return 1;
}
new AnimTimer[MAX_PLAYERS];
//stock SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, Float:ang)
forward SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, Float:ang);
public SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, Float:ang)
{//��������� ������ ��� ����� �������������
	CurPos[0][playerid] = x;
	CurPos[1][playerid] = y;
	CurPos[2][playerid] = z;
	//checkcheat[playerid] = CHEATLIM;

//new strtmp[48+9*3];
//format(strtmp, sizeof(strtmp), "SetPlayerPosEx(playerid, x:%.4f, y:%.4f, z:%.4f", x, y, z);
//SendClientMessage(playerid, -1, strtmp);
	
	SetPlayerFacingAngle(playerid, ang);
	//SetCameraBehindPlayer(playerid);
		//OnePlayAnim(playerid, "PED", "WALK_CIVI", 4.1, 0, 1, 1, 0, 1500);//1257
	//ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 1000);//1273
		//OnePlayAnim(playerid, "PED", "WALK_DOORPARTIAL", 4.1, 0, 1, 1, 0, 3000);

	//if(TEST[52] == 0) OnPlayerCheckpointTimer(playerid);//
	/*if(AnimTimer[playerid] != -1)
	{
	    KillTimer(AnimTimer[playerid]);
	    AnimTimer[playerid] = -1;
	}
	AnimTimer[playerid] = SetTimerEx("@Animation_Timer", 100, false, "d", playerid);*/
	return SetPlayerPos(playerid, x, y, z);
}
@Animation_Timer(playerid); @Animation_Timer(playerid)
{
    if(GetPVarInt(playerid, "UseLoopAnim") == 1)
    {
		/*new animlib[16]; GetPVarString(playerid, "animlib", animlib, sizeof(animlib));
		new animname[32]; GetPVarString(playerid, "animname", animlib, sizeof(animlib));
		new Float: animspeed =	GetPVarFloat(playerid, "animspeed");
		new looping = GetPVarInt(playerid, "looping");
		new freeze= GetPVarInt(playerid, "freeze");
		new time = GetPVarInt(playerid, "time");
		ApplyAnimation(playerid,animlib,animname,animspeed,looping, 0, 0, freeze, time);*/

		ApplyAnimation(playerid, "PED", "SEAT_DOWN", 4.1, 0, 0, 0, 1, 0);
	}
	if(AnimTimer[playerid] != -1)
	{
	    KillTimer(AnimTimer[playerid]);
	    AnimTimer[playerid] = -1;
	}
	return 1;
}


stock SendDeathMessageEx(killerid, playerid, reason)
{
	//if(TEST[64] != 0) return 1;
	//if( !gRealWar ) return 1;
	//if(killerid != INVALID_PLAYER_ID) { if(PlayerInfo[playerid][pAdmin] < 6) return 1; }
	//if(killerid != INVALID_PLAYER_ID) { if(PlayerInfo[killerid][pMember] == Hitman && GotChaseHitID[killerid] == playerid) return 1; }
	//if( !strcmp(php_host, "vw-rp.net", true) ) return 1;
	return SendDeathMessageToPlayer(playerid, killerid, playerid, reason);//������� ���������� � ������ ���� ��� ����, ����� ������ ���� ��� ���� ����
    //return SendDeathMessage(killerid, playerid, reason);//��������� � ������� ��� ����� ��������
}
stock SetPlayerSkillLevelEx(playerid, skill, level)
{
	if(PlayerInfo[playerid][pAccount] != 0) SetPlayerSkillLevel(playerid, skill, 999);
	else SetPlayerSkillLevel(playerid, skill, level);
}
stock SetPlayerFightingStyleEx(playerid, style)
{
	if(PlayerInfo[playerid][pAccount] != 0) SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
	else SetPlayerFightingStyle(playerid, style);
}
stock SetPlayerVirtualWorldEx(playerid, worldid)
{
	PlayerInfo[playerid][pVirtual] = worldid;
	return SetPlayerVirtualWorld(playerid, worldid);
}
stock SetPlayerInteriorEx(playerid, interiorid)
{
	PlayerInfo[playerid][pInt] = interiorid;
	CurInt[playerid] = interiorid;
	return SetPlayerInterior(playerid, interiorid);
}
stock SetPlayerSkinEx(playerid, skinid)
{
	if(!IsValidSkin(skinid))
	{
	    //new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error: playerid %s[%d], reason: Use Invalid Skin %d", PlayerName(playerid), playerid, skinid);
		//ABroadCast(COLOR_MAROON, strings, 1);
		//SendClientMessageToAll(COLOR_MAROON, strings);
		Log(ERROR, strings);
		return PlayerInfo[playerid][pModel];
	}
	if(PlayerInfo[playerid][pSex] == Female)
	{
		for(new i=0; i<MAX_SKINS; i++)
		{
			if(skinid != SkinArray[i][Skin_ID]) continue;
			 //����� � ������� ��� ����, ��������� ��� ������ � �������
			if(	SkinArray[i][Gender] != Female ) return PlayerInfo[playerid][pModel];
			else break;//�� ����� ������� ��������� ��������� �� �� � �����
		}
	}
	if(IsPlayerConnectedEx(playerid) && IsPlayerInAnyVehicle(playerid))
	{
		//new	vehicleid = GetPlayerVehicleID(playerid);
		if (nCarID[playerid])
		{
			new	seat = GetPlayerVehicleSeat(playerid);
			ClearAnimations(playerid);
			new	ret = SetPlayerSkin(playerid, skinid);
			PutPlayerInVehicle(playerid, nCarID[playerid], seat);
			return ret;
		}
	}
	//if(!IsPlayerConnectedEx(playerid)) return PlayerInfo[playerid][pModel];
	ClearAnimations(playerid);
	PlaySoundForPlayer(playerid, SOUND_CLOTHES_DRESSING_WARDROBE);
	PlayerInfo[playerid][pModel] = skinid;
	return SetPlayerSkin(playerid, skinid);
}

//stock TogglePlayerControllableEx(playerid, toggle)
forward TogglePlayerControllableEx(playerid, toggle);
public TogglePlayerControllableEx(playerid, toggle)
{   //toggle - 0 or 1, (1 - thawed, 0 - frozen)
	/*if(CHECKING == 1)
	{
		//////new strings[MAX_STRING];
		format(strings, sizeof(strings), "gControllable[playerid]: %d[%d](0-frozen[1-free])", toggle, IsPlayerControllable[playerid]);
		SendClientMessageToAll(COLOR_YELLOW, strings);
	}*/

    if(toggle == 0 && IsPlayerControllable[playerid] == 0)
    {	//���� ������ �� �������������� � ����� ��� ���������
		IsPlayerControllable[playerid] = 1;
		SetPVarInt(playerid, "gWorldBounds", 2);//��� UnFreezeTimer
		if(CurState[playerid] == PLAYER_STATE_DRIVER)
		{
			SetVehicleVelocity(nCarID[playerid], 0.0, 0.0, 0.0);
			//��� ������� �� ����� ������� � ��������� ������� � � �������.
		}
		else SetPlayerVelocity(playerid, 0.0, 0.0, 0.0);
		TogglePlayerControllable(playerid, 0);//false - �������������
    }
    else if(toggle == 1 && IsPlayerControllable[playerid] == 1)
    {   //���� ������ �� ������������ � ����� ��� ����������
		//if(	PlayerTazed[playerid] == 0
		//	&& PlayerCuffed[playerid] == MAX_PLAYERS-1
		//	&& PlayerTied[playerid] == 0)//&& FollowBy[playerid] == MAX_PLAYERS-1
		//{   //���� ����� �� ���������� ������� ��� �����
			IsPlayerControllable[playerid] = 0;
			SetPVarInt(playerid, "gWorldBounds", 0);
			TogglePlayerControllable(playerid, 1);//true - �����������
		//}
	}
}


/*stock SetPlayerSpecialActionEx(playerid, actionid)
{

}*/

stock GameTextForPlayerEx(playerid, const message[], time, style)
{   //���������� GameTextForPlayer ����� gGameText == 0
//� 5 ����� �� �������� ������ �������
//style 4 - ����������� ������ ����������� �����, ����� ���������� ��� � 3, 4 � 5
//style 3 - ������� ��������� ����� 4 � 5 ������, ����� ���������� ��� � 3, 4 � 5
//style 5 - ����������� ����� ����������� �����, ����� ���������� ��� � 3, 4 � 5

	if(gGameText[playerid] != 0) return 1;
	if(strlen(message) > 128) return 1;
	//�.�. �� ���������� ��� GameText ���� gGameText == 1
	//���������� ������ �� GameText, ��� �� ���������� ����� GameTextForPlayerEx
	return GameTextForPlayer(playerid, message, time, style);
}
/*
stock GetTickCountEx()
{
#if defined Windows
	return tickcount();
#else
	return GetTickCount();
#endif
}
*/
stock SetPlayerWorldBoundsEx(playerid, Float:x_max,Float:x_min,Float:y_max,Float:y_min)
{
	//if(PlayerInfo[playerid][pAdmin] == 9) return -1;
	if (x_max <= x_min || y_max <= y_min) return -1;
	WorldBoundsPos[playerid][1] = x_min-3.0;
	WorldBoundsPos[playerid][3] = y_min-3.0;
	WorldBoundsPos[playerid][0] = x_max+3.0;
	WorldBoundsPos[playerid][2] = y_max+3.0;
	return SetPlayerWorldBounds(playerid, x_max+3.0,x_min-3.0,y_max+3.0,y_min-3.0);
}
stock SendClientMessageEx(playerid, color, const message[])
{
	if( !IsPlayerConnected(playerid) ) return 1;
	if( IsPlayerNPC(playerid) ) return 1;

	//if(AFK_IdleTime[playerid] >= 3) return 1;
	if(!strlen(message)) return 1;
	return SendClientMessage(playerid, color, message);
}

stock SetSpawnInfoEx(playerid, team, skin,
	Float:x, Float:y, Float:z, Float:rotation,
	weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo)
{
	//TogglePlayerControllableEx(playerid, 1);//�����������

	spawnPos[0][playerid] = x;
	spawnPos[1][playerid] = y;
	spawnPos[2][playerid] = z;

	if(CHECKING[PlayerSpawn])
	{
		format(strings, sizeof(strings), "SetSpawnInfo(team:%d, skin:%d, x:%.4f, y:%.4f, z:%.4f, a:%.4f)",
			team, skin, x, y, z, rotation);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	
	//CurPos[0][playerid] = x;
	//CurPos[1][playerid] = y;
	//CurPos[2][playerid] = z;
	//checkcheat[playerid] = CHEATLIM;
	return SetSpawnInfo(playerid, team, skin, x, y, z, rotation,
		weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
}

stock TogglePlayerSpectatingEx(playerid, toggle)
{   //toggle - 0 or 1, (1 - on, 0 - off)
    if(toggle == 1)
    {
		SetPVarInt(playerid, "gSpectating", 1);
		return TogglePlayerSpectating(playerid, 1);//true - �������� ����� ����������
	}
    else
    {
		SetPVarInt(playerid, "gSpectating", 0);
		return TogglePlayerSpectating(playerid, 0);//false - ����������
    }
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "gControllable[playerid]: %d", gControllable[playerid]);
	//SendClientMessageToAll(COLOR_YELLOW, strings);
}
//native PlayCrimeReportForPlayer(playerid, suspectid, crime);
stock SetPlayerWantedLevelEx(playerid, suspectid, level)//suspectid - �������������
{
	WantedLevel[suspectid] = level;
	PlayCrimeReportForPlayer(playerid, suspectid, 2+level);
	PlayCrimeReportForPlayer(suspectid, playerid, 2+level);
	SetPlayerWantedLevel(suspectid, level);
}
//==============================================================================
stock SetPlayerTeamEx(playerid, teamid)
{
	PlayerInfo[playerid][pTeam] = teamid;
	SetPlayerTeam(playerid, teamid);
	format(strings, sizeof(strings), "   B� ������������ � ����� %d", teamid);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	/*format(strcmd, sizeof(strcmd), "   B� ������������ %s � ����� %d.", PlayerName(giveplayerid), teamid);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
	format(strcmd, sizeof(strcmd), "AdmCmd: %s ����������� %s'� � ����� %d.", PlayerName(playerid), PlayerName(giveplayerid), teamid);
	Log(ADMINLOG, strcmd);*/
}


//##############################################################################//
//                                                                              //
//                   ������������� ������� ��� ������ ��������                  //
//                                                                              //
//##############################################################################//

forward GetPlayerMoneyB(playerid);
public GetPlayerMoneyB(playerid)//��� ������ ���������� ����� � pCash
{   //����������� ����������� �-�� GivePlayerMoney
	return PlayerInfo[playerid][pBank];
}


forward GetPlayerMoneyH(playerid);
public GetPlayerMoneyH(playerid)
{
	return PlayerInfo[playerid][pCash];
}


//stock GivePlayerMoneyB(operation, playerid, money)//��� ������ ���������� ����� � pCash
forward GivePlayerMoneyB(operation, playerid, money);
public GivePlayerMoneyB(operation, playerid, money)
{   //����������� ����������� �-�� GivePlayerMoney
	new timers = GetTickCount();
	if(PlayerInfo[playerid][pBank] + money >= 2147483647) return 1;
	new strtmp[11+10];
	if(money > 0)
	{
		//if(money >= 1000) FinaceList(playerid, money, 0, operation);//������� � ���� ������ ��� ������� ���� �������� ��������
		//if(sound == 1)
		PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
		format(strtmp, sizeof(strtmp), "~b~+~g~%s$", NiceMoney(money));
	}
	else
	{
		//if(money <= -1000) FinaceList(playerid, 0,  money, operation);//������� � ���� ������ ��� ������� ���� �������� ��������
		//if(sound == 1)
		PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		//format(strings, sizeof(strings), "~r~-~y~%d$", floatabs(float(money)));
		format(strtmp, sizeof(strtmp), "~r~%s$", NiceMoney(money));
	}
	GameTextForPlayerEx(playerid, strtmp, 1000, 1);
  	PlayerInfo[playerid][pBank] += money;

	//OnPlayerInCheckLocation(playerid, PlayerGiveMoney);

	format(strtmp, sizeof(strtmp), "$%08d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strtmp);

	TestLog(OPTIM, "GivePlayerMoneyB", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}



//stock GivePlayerMoneyH(operation, playerid, money)
forward GivePlayerMoneyH(operation, playerid, money);
public GivePlayerMoneyH(operation, playerid, money)//��� ������ ���������� ����� � pCash
{   //����������� ����������� �-�� GivePlayerMoney


	new timers = GetTickCount();
	if(PlayerInfo[playerid][pCash] + money >= 2147483647) return 1;
	new strtmp[11+10];
	if(money > 0)
	{
		//if(money >= 1000) FinaceList(playerid, money, 0, operation);
		//if(sound == 1)
		PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
		format(strtmp, sizeof(strtmp), "~b~+~g~%s$", NiceMoney(money));
	}
	else
	{
		//if(money <= -1000) FinaceList(playerid, 0, money, operation);
		//if(sound == 1)
		PlaySoundForPlayer(playerid, SOUND_RESTAURANT_CJ_PUKE);
		//format(strings, sizeof(strings), "~r~-~y~%d$", floatabs(float(money)));
		format(strtmp, sizeof(strtmp), "~r~%s$", NiceMoney(money));
	}
	GameTextForPlayerEx(playerid, strtmp, 1000, 1);
	PlayerInfo[playerid][pCash] += money;
	//SetPlayerMoneyH(playerid, money);

	ResetPlayerMoney(playerid);//����� �� ���������� ������� -100 ��� ������ ������
	gConsumingMoney[playerid] = 2;
	GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
	//SetPVarInt(playerid, "LastMoney", PlayerInfo[playerid][pCash]);
	LastMoney[playerid] = PlayerInfo[playerid][pCash];
	TestLog(OPTIM, "GivePlayerMoneyH", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}


stock SetPlayerHealthEx(playerid, Float:health)
{
	//new Float:hp; GetPlayerHealth(playerid, hp);
 	/*if(floatsub(health, LastHealth[playerid]) > 2.0)
	{//���� ��������� ��������� �������� � ������� �������
		if(IsPlayerWalking(playerid) &&
			health >= PlayerInfo[playerid][pSHealth] )
		{
			//SetPlayerWalkingStyle(playerid, WALK_NORMAL);
			TogglePlayerWalking(playerid, false);
			//SendClientMessage(playerid, COLOR_PINK, "������: ���� �������� ����������! �� ������ ������ !");
		}
	}
 	else if(floatsub(LastHealth[playerid], health) > 2.0)
	{//���� ��������� ��������� �������� � ������� �������
		if(//!IsPlayerWalking(playerid) &&
			health < PlayerInfo[playerid][pSHealth] )
		{
			//SetPlayerWalkingStyle(playerid, WALK_GANGSTA2);
			TogglePlayerWalking(playerid, true);
			//new strtmp[MAX_STRING];
			//format(strtmp, sizeof(strtmp), "������: �� �� ������ ������, ���� ���� �������� ������: %.0f",
			//	floatadd(PlayerInfo[playerid][pSHealth], 50.0) );
			//SendClientMessage(playerid, COLOR_PINK, strtmp);
		}
	}*/
	DetectedHealth[playerid] = 1;
	LastHealth[playerid] = health;

	new strtmp[5+3];
	format(strtmp, sizeof(strtmp), "%.0f", health);
	PlayerTextDrawSetString(playerid, txdPlayerHealth[playerid], strtmp);
	return SetPlayerHealth(playerid, health);
}
new DetectedArmour[MAX_PLAYERS];
stock SetPlayerArmourEx(playerid, Float:armour)
{
	DetectedArmour[playerid] = 1;
	LastArmour[playerid] = armour;
	//new Float:armour;
	//GetPlayerArmour(playerid, armour);
	gTextDrawShowArmour[playerid] = true;
	OnPlayerTextDrawStateChange(playerid);
	new strtmp[5+3];
	format(strtmp, sizeof(strtmp),"%.0f", armour);
	PlayerTextDrawSetString(playerid, txdPlayerArmour[playerid], strtmp);
	return SetPlayerArmour(playerid, armour);
}

stock SetPlayerArmedWeaponEx(playerid, weaponid)
{
    SetPlayerArmedWeapon(playerid, weaponid);
    gCheckArmedWeapon[playerid] = 1;

	/*if(CHECKING == 2)
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "SetPlayerArmedWeapon(playerid: %d, weaponid: %d)", playerid, weaponid);
		SendClientMessage(playerid, COLOR_RED, strings);
	}*/
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "SetPlayerArmedWeapon(playerid: %d, weaponId: %d)", playerid, weaponId);
	//ABroadCast(ADMINS_MESSAGE_COLOR, strings, 1);
	//SendClientMessageToAll(COLOR_YELLOW, strings);
	//return ResetPlayerWeapons(playerid);
}



stock ResetPlayerWeaponsEx(playerid)//�������� ������
{
	ResetPlayerWeapons(playerid);//������� ���������� ������

	//� ����� �������� ����������,
	//�.�. ��-�� �������� ����� ��� ������ ��� ���� � ���������� ��� ��������
	for(new w = 0; w <= MAX_WEAPONS; w++)
	{
		DetectedGun[playerid][w] = 1;//0
		LastAmmo[playerid][w] = 0;
		if(w <= 12) LastWeaponInSlot[playerid][w] = 0;
	}
	/*if(CHECKING == 2)
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "ResetPlayerWeapons(playerid: %d)", playerid);
		SendClientMessage(playerid, COLOR_RED, strings);
	}*/
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "ResetPlayerWeapons(playerid: %d)", playerid);
	//ABroadCast(ADMINS_MESSAGE_COLOR, strings, 1);
	//SendClientMessageToAll(COLOR_YELLOW, strings);
	//return ResetPlayerWeapons(playerid);
}

stock SetPlayerGunSkillEx(playerid, Gun, Skill)
{
	new skill = Gun;
	new level = Skill;
	if(Gun == 22)
	{   //PISTOL
		skill = 0;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun22Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 40) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[22] - ��������� ������� ��������. �������� ������ �������� � �������� ��������.");
		else if(level == 200) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[22] ��������. ����������� ��� � ���������� ������ �������, ��� ���� ����������� ������������ 2 ���������.");
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[22] ��������. ����������� ��� � ���������� ������ �������, ��� ���� ����������� ������������ 2 ���������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[22] ��������. ����������� ��� � ���������� ������ �������, ��� ���� ����������� ������������ 2 ���������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[22] ��������. ����������� ��� � ���������� ������ �������, ��� ���� ����������� ������������ 2 ���������.");
		else if(level == 999) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[22] - ��������� ������� �������. ������ ����� ������������ ��� ��������� ������������.");
	}
	else if(Gun == 23)
	{   //PISTOL_SILENCED
		skill = 1;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun23Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����� ����������[23] ��������. ����������� ��� � ���������� ������ ��������.");
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����� ����������[23] ��������. ����������� ��� � ���������� ������ ��������..");
		else if(level == 500)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ����� ����������[23] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����� ����������[23] ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����� ����������[23] ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ����� ����������[23] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 24)
	{
//DESERT_EAGLE
		skill = 2;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun24Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "������ ���������� ����[24] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "������ ���������� ����[24] - ��������. ��������� ���������� � �� ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "������ ���������� ����[24] - ��������. ��������� ���������� � �� ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "������ ���������� ����[24] - ��������. ��������� ���������� � �� ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "������ ���������� ����[24] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 25)
	{   //SHOTGUN
		skill = 3;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun25Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[25] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[25] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[25] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[25] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������[25] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 26)
	{   //SAWNOFF_SHOTGUN
		skill = 4;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun26Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� �������[26] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� �������[26] - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ ��� ������ ������������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� �������[26] - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ ��� ������ ������������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� �������[26] - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ ��� ������ ������������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� �������[26] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 27)
	{   //SPAS12_SHOTGUN
		skill = 5;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun27Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "������ ������� ���������[27] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "������ ������� ���������[27] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "������ ������� ���������[27] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "������ ������� ���������[27] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "������ ������� ���������[27] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 28 || Gun == 32)
	{   //MICRO_UZI //TEC-9
		skill = 6;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun28Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 50)
		{
			format(strings, sizeof(strings), "�������� �������������[%d] - ��������� ������� ��������.", Gun);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ������ ���������, �������� � ��������.");
		}
		else if(level == 200) SendClientMessage(playerid, COLOR_YELLOW, "�������� ������������� - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ 2 �������� ������������.");
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� ������������� - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ 2 �������� ������������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� ������������� - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ 2 �������� ������������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� ������������� - ��������. ����������� ��� � ���������� ������ �������. �� ������� ������ 2 �������� ������������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ������������� - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 29)
	{   //MP5
		skill = 7;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun29Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		//0 - �������
		if(level == 250)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� SMG[29] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� SMG[29] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� SMG[29] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� SMG[29] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� SMG[29] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 30)
	{   //AK47
		skill = 8;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun30Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ��-47[30] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� ��-47[30] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� ��-47[30] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� ��-47[30] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ��-47[30] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 31)
	{   //M4
		skill = 9;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun31Skill] = Skill;
/*#if defined FILTERSCRIPT

#else
		//SetPlayerShowBattery(playerid, 2, level, 999);
#endif*/
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� M4[31] - ��������� ������� ��������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ ���������, ��� ����, ��������� ���������. �������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� M4[31] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� M4[31] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� M4[31] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� M4[31] - ��������� ������� �������.");
			SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	else if(Gun == 34)
	{   //SNIPERRIFLE
		skill = 10;
		SetPlayerSkillLevelEx(playerid, skill, level);
		PlayerInfo[playerid][pGun34Skill] = Skill;
		//SetPlayerShowBattery(playerid, 2, level, 999);
		if(level == 200)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������� ������[34] - ��������� ������� ��������.");
			//SendClientMessage(playerid, COLOR_YELLOW, "�������� ������ ���������, �������� � ��������.");
		}
		else if(level == 400) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������� ������[34] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 600) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������� ������[34] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 800) SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������� ������[34] - ��������. ����������� ��� � ���������� ������ �������.");
		else if(level == 999)
		{
			SendClientMessage(playerid, COLOR_YELLOW, "�������� ����������� ������[34] - ��������� ������� �������.");
			//SendClientMessage(playerid, COLOR_YELLOW, "������ �� ������ �������� � ��������. �������� ������ ���������, �������� � ��������.");
		}
	}
	return 1;
}


stock IsPermitToRider(playerid)//���������� ������ �� ������
{
	if(CurState[playerid] != PLAYER_STATE_DRIVER) return 0;
	if(PlayerInfo[playerid][pJob] == CARJACKER || PlayerInfo[playerid][pMember] == DoT)
	{
		new vehicleid = nCarID[playerid];
		if(	VehInfo[vehicleid][cPark] == 0 &&//�� �����������
			VehInfo[vehicleid][cType] >= 1000)//�� ��������
		 return 1;
	}
	return 0;
}
