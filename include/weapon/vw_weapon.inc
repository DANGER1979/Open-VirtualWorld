new WEAPON = 0;//1 - ��������� �������������� �� ������
new iLastScrollWeapon[MAX_PLAYERS];




//stock CheckWeaponStateChangeUpdate(playerid)
stock weapon_OnPlayerUpdate(playerid)
{	//���������� �� public OnPlayerUpdate
	//if(ANTICHEAT == 0) return 1;
	new weaponid = GetPlayerWeapon(playerid); // Return the player's current weapon
	if(	IsFireArm(weaponid) )
	{   //���� � ������ ������������� ������
		if(
			( PlayerInfo[playerid][pGunLic] != 1 || (!gAnticheat[playerid] && !strcmp(php_host, "gta.strikearena.ru", true)) )
			&& !gRealWar)
		{ //���� � ������ ���� ����� �� � �������������� ������ �� ������ ����
		    if(gCheckArmedWeapon[playerid] == 1 && CheckInCar[playerid] != -1)
		    {//���� ����� ������ ��� ��������� //, � ����� �� ���������� ������� � ����
		        if(weaponid != LastWeapon[playerid] && weaponid == 0)
		        {   //���� ������ �� ����� ����������� � ����� ������
		            LastWeapon[playerid] = 0;
		            gCheckArmedWeapon[playerid] = 0;
		        }
		        else
		        {
					if(IsKicked[playerid] == 0 && !gAnticheat[playerid])
					{
						strmid(ReasonPunishment[playerid], "NOP SetPlayerArmedWeapon", 0, strlen("NOP SetPlayerArmedWeapon"), 64);
			        	new strtmp[34 + 24+3 +64];
						format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] ��� ������, �������: %s",
							PlayerName(playerid),playerid, ReasonPunishment[playerid]);
						//Log(CHEAT, strtmp);
				    	SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
						IsKicked[playerid] = 1;
					}
		        }
		    }
			SetPlayerArmedWeaponEx(playerid, 0);
		}
		//======================================================================
//�������� ������ � ���� �� ����� ������� ��� ���� ��������
		if(
			PlayerInfo[playerid][pInt] != 0 || //GetPlayerInterior(playerid) != 0 ||//� ����������
			(IsPlayerInArea(playerid, specialzone[6]) && PlayerInfo[playerid][pMember] != Hitman) ||//������� Hitman
			(IsPlayerInArea(playerid, specialzone[8]) && PlayerInfo[playerid][pJob] != CARDEALER) ||//AutoSalon
			(IsAtHospital(playerid) && PlayerInfo[playerid][pMember] != DoH) ||//Hospital
			(PlayerInfo[playerid][pJob] == MINER && gJobDuty[playerid])//��� �������
		  )
		{
			SetPlayerArmedWeaponEx(playerid, 0);
		}

		new weaponstate = GetPlayerWeaponState(playerid);
		if(weaponstate != LastStateWeapon[playerid])
		{
			if(WEAPON) { OnPlayerWeaponStateChange(playerid, weaponid, weaponstate, LastStateWeapon[playerid]);	}
			LastStateWeapon[playerid] = weaponstate;
		}
	}
	//==========================================================================
    if(weaponid != LastWeapon[playerid]) // If he changed weapons since the last update
    {
        // Lets call a callback named OnPlayerChangeWeapon
        //if(WEAPON)
		//CallLocalFunction("OnPlayerChangeWeapon", "ddd", playerid, weaponid, LastWeapon[playerid]);
		OnPlayerChangeWeapon(playerid, weaponid, LastWeapon[playerid]);
     	LastWeapon[playerid] = weaponid;//Update the weapon variable
    }
    return 1; // Send this update to other players.
}

forward OnPlayerWeaponStateChange(playerid, weaponid, newstate, oldstate);
public OnPlayerWeaponStateChange(playerid, weaponid, newstate, oldstate)
{   //���������� ������ ��� ����� � ������ ���������� ��������� ������
//WEAPONSTATE_UNKNOWN			-1//����� ����� ��������� � Spectate ��� ����� � �����
//WEAPONSTATE_NO_BULLETS		0//����� ������ �� ����� ��������, �� ����� � ����� �� -1
//WEAPONSTATE_LAST_BULLET		1//����� � ������ � ������ ������� ���� ������ ��� �� ����� � ������ ������ ���� ������ (Grenades, Shotgun, Sniper...)
//WEAPONSTATE_MORE_BULLETS		2//����� � ������ � ������ > 1 �������
//WEAPONSTATE_RELOADING			3//����� ������ ��������������
//WEAPONSTATE_SHOOTING          4//����� ������ ��������
	if(newstate == WEAPONSTATE_RELOADING && oldstate == WEAPONSTATE_MORE_BULLETS)
	{
	    if(WEAPON) GameTextForPlayerEx(playerid, "~p~RELOADING ~r~BEGIN", 1000, 3);
	}
	else if(newstate == WEAPONSTATE_MORE_BULLETS && oldstate == WEAPONSTATE_RELOADING)
	{
	    if(WEAPON) GameTextForPlayerEx(playerid, "~p~RELOADING ~g~END", 1000, 3);
	}
	else if(newstate == WEAPONSTATE_SHOOTING)// && oldstate == WEAPONSTATE_MORE_BULLETS
	{
    	if(WEAPON) GameTextForPlayerEx(playerid, "~p~SHOOTING ~r~BEGIN", 1000, 3);
		//AntiDB_OnPlayerStateChange(playerid);
	}
	else if(newstate == WEAPONSTATE_MORE_BULLETS && oldstate == WEAPONSTATE_SHOOTING)
	{
		//if(WEAPON) GameTextForPlayerEx(playerid, "~p~SHOOTING ~r~END", 1000, 3);
	}
	else
	{
		//if(WEAPON) shoot_OnPlayerWeaponShot(playerid, weaponid, BULLET_HIT_TYPE_NONE);

		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "NewWeaponState={00ff00}%d {A5C3E7}OldWeaponState={00ff00}%d", newstate, oldstate);
		SendClientMessage(playerid, COLOR_SYSTEM, strings);//{800000}
	}
	//return 1;
}

forward OnPlayerChangeWeapon(playerid, newweapon, oldweapon);
public OnPlayerChangeWeapon(playerid, newweapon, oldweapon)
{//���� ����� ������ ��� ������
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "You changed weapon from %s to %s!", WeaponName(oldweapon), WeaponName(newweapon));
	//SendClientMessage(playerid, COLOR_SYSTEM, strings);

	if(GetPVarInt(playerid, "Tazer") == 1 && newweapon != 0)
	{
		SetPVarInt(playerid, "Tazer", 0);
        if(IsPlayerAttachedObjectSlotUsed(playerid, TAZER_SLOT))
        {
            RemovePlayerAttachedObject(playerid, TAZER_SLOT);
        }
	}
}

//stock IncreasesGunSkill(playerid, killed, reason)
stock weapon_OnPlayerDeath(playerid, killerid, reason)
{   //���������� �� OnPlayerDeath
	if( gRealWar ) return 1;
	if(PlayerInfo[playerid][pGunLic] != 1) return 1;
	if(PlayerInfo[killerid][pGunLic] != 1) return 1;
	if(PlayerInfo[playerid][pJailed] != 0) return 1;
	if(PlayerInfo[killerid][pJailed] != 0) return 1;
	if( !IsFireArm(reason) ) return 1;

	if(	killerid == INVALID_PLAYER_ID) return 1;//65535//���� ������ ������ �� �������, �.�. ����� ���� ���
	if(	reason == 37) return 1;//��� ������
	if(	reason == 53) return 1;//��� ������
	if(	reason == 54) return 1;//��� ����

	new exp = 1;
	new weapon = LastWeapon[killerid];
	if(weapon == 22) exp = PlayerInfo[killerid][pGun22Skill];
	else if(weapon == 23) exp = PlayerInfo[killerid][pGun23Skill];
	else if(weapon == 24) exp = PlayerInfo[killerid][pGun24Skill];
	else if(weapon == 25) exp = PlayerInfo[killerid][pGun25Skill];
	else if(weapon == 26) exp = PlayerInfo[killerid][pGun26Skill];
	else if(weapon == 27) exp = PlayerInfo[killerid][pGun27Skill];
	else if(weapon == 28) exp = PlayerInfo[killerid][pGun28Skill];
	else if(weapon == 29) exp = PlayerInfo[killerid][pGun29Skill];
	else if(weapon == 30) exp = PlayerInfo[killerid][pGun30Skill];
	else if(weapon == 31) exp = PlayerInfo[killerid][pGun31Skill];
	else if(weapon == 34) exp = PlayerInfo[killerid][pGun34Skill];

	if(reason == 22 && PlayerInfo[playerid][pGun22Skill] < 999
	&& PlayerInfo[playerid][pGun22Skill] > exp) { PlayerInfo[playerid][pGun22Skill]	++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun22Skill]); return 1; }//PISTOL
	else if(reason == 23 && PlayerInfo[playerid][pGun23Skill] < 999
	&& PlayerInfo[playerid][pGun23Skill] > exp) { PlayerInfo[playerid][pGun23Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun23Skill]); return 1; }//PISTOL_SILENCED
	else if(reason == 24 && PlayerInfo[playerid][pGun24Skill] < 999
	&& PlayerInfo[playerid][pGun24Skill] > exp) { PlayerInfo[playerid][pGun24Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun24Skill]); return 1; }//DESERT_EAGLE
	else if(reason == 25 && PlayerInfo[playerid][pGun25Skill] < 999
	&& PlayerInfo[playerid][pGun25Skill] > exp) { PlayerInfo[playerid][pGun25Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun25Skill]); return 1; }//SHOTGUN
	else if(reason == 26 && PlayerInfo[playerid][pGun26Skill] < 999
	&& PlayerInfo[playerid][pGun26Skill] > exp) { PlayerInfo[playerid][pGun26Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun26Skill]); return 1; }//SAWNOFF_SHOTGUN
	else if(reason == 27 && PlayerInfo[playerid][pGun27Skill] < 999
	&& PlayerInfo[playerid][pGun27Skill] > exp) { PlayerInfo[playerid][pGun27Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun27Skill]); return 1; }//SPAS12_SHOTGUN
	else if((reason == 28 || reason == 32) && PlayerInfo[playerid][pGun28Skill] < 999
	&& PlayerInfo[playerid][pGun28Skill] > exp) { PlayerInfo[playerid][pGun28Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun28Skill]); return 1; }//MICRO_UZI
	else if(reason == 29 && PlayerInfo[playerid][pGun29Skill] < 999
	&& PlayerInfo[playerid][pGun29Skill] > exp) { PlayerInfo[playerid][pGun29Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun29Skill]); return 1; }//MP5
	else if(reason == 30 && PlayerInfo[playerid][pGun30Skill] < 999
	&& PlayerInfo[playerid][pGun30Skill] > exp) { PlayerInfo[playerid][pGun30Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun30Skill]); return 1; }//AK47
	else if(reason == 31 && PlayerInfo[playerid][pGun31Skill] < 999
	&& PlayerInfo[playerid][pGun31Skill] > exp) { PlayerInfo[playerid][pGun31Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun31Skill]); return 1; }//M4
	else if(reason == 34 && PlayerInfo[playerid][pGun34Skill] < 999
	&& PlayerInfo[playerid][pGun34Skill] > exp) { PlayerInfo[playerid][pGun34Skill] ++; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun34Skill]); return 1; }//SNIPERRIFLE

 	if(gPlayerBoxing[playerid] != 0) return 1;
	if(gPlayerBoxing[killerid] != 0) return 1;
	if(gInTerrorsCount[playerid] != 0) return 1;
	if(gInTerrorsCount[killerid] != 0) return 1;
	if(gInCTerrorsCount[playerid] != 0) return 1;
	if(gInCTerrorsCount[killerid] != 0) return 1;

	if(exp <= 10) exp = 10;

	if(LastKill[playerid] == killerid) return 1;

	if(reason == 22 && PlayerInfo[playerid][pGun22Skill] < 999
	&& PlayerInfo[playerid][pGun22Skill] <= exp) { PlayerInfo[playerid][pGun22Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun22Skill]); }//PISTOL
	else if(reason == 23 && PlayerInfo[playerid][pGun23Skill] < 999
	&& PlayerInfo[playerid][pGun23Skill] <= exp) { PlayerInfo[playerid][pGun23Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun23Skill]); }//PISTOL_SILENCED
	else if(reason == 24 && PlayerInfo[playerid][pGun24Skill] < 999
	&& PlayerInfo[playerid][pGun24Skill] <= exp) { PlayerInfo[playerid][pGun24Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun24Skill]); }//DESERT_EAGLE
	else if(reason == 25 && PlayerInfo[playerid][pGun25Skill] < 999
	&& PlayerInfo[playerid][pGun25Skill] <= exp) { PlayerInfo[playerid][pGun25Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun25Skill]); }//SHOTGUN
	else if(reason == 26 && PlayerInfo[playerid][pGun26Skill] < 999
	&& PlayerInfo[playerid][pGun26Skill] <= exp) { PlayerInfo[playerid][pGun26Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun26Skill]); }//SAWNOFF_SHOTGUN
	else if(reason == 27 && PlayerInfo[playerid][pGun27Skill] < 999
	&& PlayerInfo[playerid][pGun27Skill] <= exp) { PlayerInfo[playerid][pGun27Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun27Skill]); }//SPAS12_SHOTGUN
	else if((reason == 28 || reason == 32) && PlayerInfo[playerid][pGun28Skill] < 999
	&& PlayerInfo[playerid][pGun28Skill] <= exp) { PlayerInfo[playerid][pGun28Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun28Skill]); }//MICRO_UZI
	else if(reason == 29 && PlayerInfo[playerid][pGun29Skill] < 999
	&& PlayerInfo[playerid][pGun29Skill] <= exp) { PlayerInfo[playerid][pGun29Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun29Skill]); }//MP5
	else if(reason == 30 && PlayerInfo[playerid][pGun30Skill] < 999
	&& PlayerInfo[playerid][pGun30Skill] <= exp) { PlayerInfo[playerid][pGun30Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun30Skill]); }//AK47
	else if(reason == 31 && PlayerInfo[playerid][pGun31Skill] < 999
	&& PlayerInfo[playerid][pGun31Skill] <= exp) { PlayerInfo[playerid][pGun31Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun31Skill]); }//M4
	else if(reason == 34 && PlayerInfo[playerid][pGun34Skill] < 999
	&& PlayerInfo[playerid][pGun34Skill] <= exp) { PlayerInfo[playerid][pGun34Skill] += exp/10; SetPlayerGunSkillEx(playerid, reason, PlayerInfo[playerid][pGun34Skill]); }//SNIPERRIFLE
	return 1;
}


//����� �������� ������ ���������� � ����� ������� ��� ��������� ������ �� �������������� ����
//����� �������� ������ ��� ��������� ������ � ������� ���-��� ��������
stock OnPlayerSetDutyWeapons(playerid)//����������� �� �������� /duty /givegun /
{   //��� ��������� ������ ������� ������ ��� ������
	if( !IsPlayerConnectedEx(playerid) ) return 1;
	CrashDetected[playerid] = 84;

	if(gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "    ������������� ����� ���� RealWar ! �� �� ������ �������� ������ !");
		return 1;
	}

	if( PlayerInfo[playerid][pGunLic] != 1 && !gRealWar) return 1;

	if( gParameter5[playerid] == 1 )
	{
		SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���, ����� ������� ������!");
		SendClientMessage(playerid, COLOR_GREY, "   ��� ���������� ��������� �� ������� � �������!");
		return 1;
	}

    ResetPlayerWeaponsEx(playerid);//�������� ������
    if(PlayerInfo[playerid][pJailed] != 0) return 1;
    //if(PlayerInfo[playerid][pGunLic] != 1) return 1;//�� ����� �������� � ��� ���� � ����

	//new Float:health = LastHealth[playerid];//�.�. ������������ duty ��� �������
	if(PlayerInfo[playerid][pMember] == DoT)//Cops & FBI/ATF  && gOnDuty[playerid] == 1
	{   //gOnDuty, ����� �� ������������� ��� ����� � ����
		//if(health < 100.0) SetPlayerHealthEx(playerid, 100.0);
		GivePlayerWeaponEx(playerid, 3, 1);//�������
	    GivePlayerWeaponEx(playerid, 41, 100); //�������� � �������
		if(PlayerInfo[playerid][pRank] >= 8)
		{
			GivePlayerWeaponEx(playerid, 24, 21);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 29, 150);//������� MP5
		}
		else if(PlayerInfo[playerid][pRank] >= 6)
		{
			GivePlayerWeaponEx(playerid, 24, 14);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 29, 115);//������� MP5
		}
		else if(PlayerInfo[playerid][pRank] >= 4)
		{
			GivePlayerWeaponEx(playerid, 24, 14);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 29, 100);//������� MP5
		}
		else if(PlayerInfo[playerid][pRank] >= 2)
		{
			GivePlayerWeaponEx(playerid, 22, 15);//��������
  			GivePlayerWeaponEx(playerid, 29, 90);//������� MP5
		}
	}
	else if(PlayerInfo[playerid][pMember] == FBI)//Cops & FBI/ATF  && gOnDuty[playerid] == 1
	{   //gOnDuty, ����� �� ������������� ��� ����� � ����
		//if(health < 100.0) SetPlayerHealthEx(playerid, 100.0);
		if(PlayerInfo[playerid][pRank] == 1)
		{
			GivePlayerWeaponEx(playerid, 3, 1);//�������
	        GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			GivePlayerWeaponEx(playerid, 22, 15);//��������
			GivePlayerWeaponEx(playerid, 29, 90);//������� MP5
		}
		else if(PlayerInfo[playerid][pRank] == 2)
		{
			GivePlayerWeaponEx(playerid, 3, 1);//�������
	        GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			GivePlayerWeaponEx(playerid, 22, 15);//��������
			GivePlayerWeaponEx(playerid, 29, 90);//������� MP5
		}
		else if(PlayerInfo[playerid][pRank] == 3)
		{
			GivePlayerWeaponEx(playerid, 3, 1);//�������
	        GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			GivePlayerWeaponEx(playerid, 23, 17);//�������� � ����������
			GivePlayerWeaponEx(playerid, 29, 90);//������� MP5
			GivePlayerWeaponEx(playerid, 43, 36);//�����������
		}
		else if(PlayerInfo[playerid][pRank] == 4)
		{
			SetPlayerArmourEx(playerid, 100.0);//armour
			GivePlayerWeaponEx(playerid, 4, 1);//���
			GivePlayerWeaponEx(playerid, 24, 21);//�������� "��������� ���"
    		GivePlayerWeaponEx(playerid, 31, 75);//���. �������� M4
		}
		else if(PlayerInfo[playerid][pRank] == 5)
		{   //CID
			GivePlayerWeaponEx(playerid, 3, 1);//�������
	    	GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			GivePlayerWeaponEx(playerid, 23, 23);//�������� � ����������
			GivePlayerWeaponEx(playerid, 29, 95);//������� MP5
			GivePlayerWeaponEx(playerid, 43, 36);//�����������
		}
		else if(PlayerInfo[playerid][pRank] == 6)
		{   //SWAT
			SetPlayerArmourEx(playerid, 100.0);//armour
			GivePlayerWeaponEx(playerid, 4, 1);//���
			GivePlayerWeaponEx(playerid, 24, 21);//�������� "��������� ���"
    		GivePlayerWeaponEx(playerid, 31, 100);//���. �������� M4
		}
		else if(PlayerInfo[playerid][pRank] == 7)
		{   //CID
			GivePlayerWeaponEx(playerid, 3, 1);//�������
			GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			GivePlayerWeaponEx(playerid, 23, 30);//�������� � ����������
			GivePlayerWeaponEx(playerid, 29, 110);//������� MP5
			GivePlayerWeaponEx(playerid, 43, 36);//�����������
		}
		else if(PlayerInfo[playerid][pRank] == 8)
		{   //SWAT
			SetPlayerArmourEx(playerid, 105.0);//armour
			GivePlayerWeaponEx(playerid, 4, 1);//���
			GivePlayerWeaponEx(playerid, 31, 75);//���. �������� M4
			GivePlayerWeaponEx(playerid, 34, 40);//����������� �������� � ���������� ��������
		}
		else if(PlayerInfo[playerid][pRank] == 9)
		{   //CID
			GivePlayerWeaponEx(playerid, 3, 1);//�������
			GivePlayerWeaponEx(playerid, 24, 21);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 29, 120);//������� MP5
			GivePlayerWeaponEx(playerid, 43, 36);//�����������
		}
		else if(PlayerInfo[playerid][pRank] == 10)
		{   //SWAT
			SetPlayerArmourEx(playerid, 110.0);//armour
			GivePlayerWeaponEx(playerid, 4, 1);//���
			GivePlayerWeaponEx(playerid, 24, 28);//�������� "��������� ���"
    		GivePlayerWeaponEx(playerid, 31, 150);//���. �������� M4
			GivePlayerWeaponEx(playerid, 34, 5);//����������� �������� � ���������� ��������
		}
		else if(PlayerInfo[playerid][pRank] >= 11)
		{
			GivePlayerWeaponEx(playerid, 3, 1);//�������
	    	GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			GivePlayerWeaponEx(playerid, 24, 28);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 29, 150);//������� MP5
		}
	}
	else if(PlayerInfo[playerid][pMember] == DoD)//National Guard
	{
		//if(health < 100.0) SetPlayerHealthEx(playerid, 100.0);
	    GivePlayerWeaponEx(playerid, 4, 1);//���
		if(PlayerInfo[playerid][pRank] >= 7)//PlayerInfo[playerid][pChar] == 285 - ���� ���� SWAT
		{
			SetPlayerArmourEx(playerid, 105.0);//armour
    		GivePlayerWeaponEx(playerid, 24, 21);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 31, 150);//���. �������� M4
			GivePlayerWeaponEx(playerid, 16, 5);//�������
			GivePlayerWeaponEx(playerid, 34, 20);//����������� �������� � ���������� ��������
		}
		else if(PlayerInfo[playerid][pRank] >= 4)
		{
    		GivePlayerWeaponEx(playerid, 24, 14);//�������� "��������� ���"
			GivePlayerWeaponEx(playerid, 31, 100);//���. �������� M4
			GivePlayerWeaponEx(playerid, 16, 2);//�������
			GivePlayerWeaponEx(playerid, 43, 2);//�����������
		}
		else if(PlayerInfo[playerid][pRank] >= 2)//PlayerInfo[playerid][pChar] == 285 - ���� ���� SWAT
		{
			GivePlayerWeaponEx(playerid, 22, 30);//��������
			GivePlayerWeaponEx(playerid, 27, 28);//������� ��������
			GivePlayerWeaponEx(playerid, 43, 2);//�����������
		}
	}
	else //if(PlayerInfo[playerid][pMember] == 0 || PlayerInfo[playerid][pMember] >= 4)//���� �� ����������� ��� � ����� ��� ... �� �� �����?
	{   //������� �����: ������ ������ ������ � ������� ����������� ��������
	    //������ ������ ����������� � ����
		if(IsAGangs(playerid))
		{
		    //GivePlayerWeaponEx(playerid, 8, 1);//������
			if(PlayerInfo[playerid][pRank] >= 8)
			{
				GivePlayerWeaponEx(playerid, 27, 49);//������� ��������
			}
			else if(PlayerInfo[playerid][pRank] >= 6)
			{
				GivePlayerWeaponEx(playerid, 27, 42);//������� ��������
			}
			else if(PlayerInfo[playerid][pRank] >= 4)
			{
				GivePlayerWeaponEx(playerid, 27, 35);//������� ��������
			}
			else if(PlayerInfo[playerid][pRank] >= 2)
			{
				GivePlayerWeaponEx(playerid, 27, 28);//������� ��������
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoH)//Medic
		{
		    GivePlayerWeaponEx(playerid, 42, 100);//������������
		}
		else if(PlayerInfo[playerid][pMember] == LCN)//LCN
		{
		    GivePlayerWeaponEx(playerid, 2, 1);//������ ��� ������
			/*if(PlayerInfo[playerid][pRank] >= 8)
			{
				GivePlayerWeaponEx(playerid, 24, 35);//�������� "��������� ���"
				GivePlayerWeaponEx(playerid, 32, 150);//TEC-9
				GivePlayerWeaponEx(playerid, 34, 20);//����������� �������� � ���������� ��������
			}
			else if(PlayerInfo[playerid][pRank] >= 6)
			{
				GivePlayerWeaponEx(playerid, 24, 28);//�������� "��������� ���"
				GivePlayerWeaponEx(playerid, 32, 150);//TEC-9
			}
			else if(PlayerInfo[playerid][pRank] >= 4)
			{
				GivePlayerWeaponEx(playerid, 24, 28);//�������� "��������� ���"
				GivePlayerWeaponEx(playerid, 32, 100);//TEC-9
			}
			else if(PlayerInfo[playerid][pRank] >= 2)
			{
				GivePlayerWeaponEx(playerid, 22, 90);//��������
			    GivePlayerWeaponEx(playerid, 32, 100);//TEC-9
			}*/
		}
		else if(PlayerInfo[playerid][pMember] == Yakuza)//Yakuza
		{
		    GivePlayerWeaponEx(playerid, 8, 1);//������
			/*if(PlayerInfo[playerid][pRank] >= 8)
			{
				GivePlayerWeaponEx(playerid, 24, 35);//�������� "��������� ���"
				GivePlayerWeaponEx(playerid, 28, 150);//UZI
				GivePlayerWeaponEx(playerid, 34, 20);//����������� �������� � ���������� ��������
			}
			else if(PlayerInfo[playerid][pRank] >= 6)
			{
				GivePlayerWeaponEx(playerid, 24, 28);//�������� "��������� ���"
				GivePlayerWeaponEx(playerid, 28, 150);//UZI
			}
			else if(PlayerInfo[playerid][pRank] >= 4)
			{
				GivePlayerWeaponEx(playerid, 23, 28);//�������� � ����������
				GivePlayerWeaponEx(playerid, 28, 100);//UZI
			}
			else if(PlayerInfo[playerid][pRank] >= 2)
			{
				GivePlayerWeaponEx(playerid, 22, 90);//��������
			    GivePlayerWeaponEx(playerid, 28, 100);//UZI
			}*/
		}
		else if(PlayerInfo[playerid][pMember] == DoJ)//Cops & FBI/ATF  && gOnDuty[playerid] == 1
		{   //gOnDuty, ����� �� ������������� ��� ����� � ����
			//SetPlayerHealthEx(playerid, 100.0);
			if(PlayerInfo[playerid][pRank] == 1)
			{
				SetPlayerArmourEx(playerid, 100.0);//armour
				GivePlayerWeaponEx(playerid, 3, 1);//�������
		    	GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
				GivePlayerWeaponEx(playerid, 24, 14);//�������� "��������� ���"
				GivePlayerWeaponEx(playerid, 29, 60);//������� MP5
			}
			else if(PlayerInfo[playerid][pRank] == 5)
			{   //CID
				GivePlayerWeaponEx(playerid, 3, 1);//�������
		    	GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
				GivePlayerWeaponEx(playerid, 43, 36);//�����������
			}
			else
			{
				GivePlayerWeaponEx(playerid, 3, 1);//�������
			    GivePlayerWeaponEx(playerid, 41, 100);//�������� � �������
			}
		}
		else if(PlayerInfo[playerid][pMember] == SAN)//CNN
		{
		    GivePlayerWeaponEx(playerid, 43, 36);//�����������
		    GivePlayerWeaponEx(playerid, 15, 1);//������
		}
		else if(PlayerInfo[playerid][pMember] == DoE)//DoE
		{
			GivePlayerWeaponEx(playerid, 41, 100); //�������� � �������
		}
		else GivePlayerWeaponEx(playerid, 5, 1);//����������� ����
	}//5-ID ������, ��������� ������  1-���������� ���������, �������� ������ ������ � �������
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "OnPlayerSetDutyWeapons(%d)", playerid);
	//ABroadCast(COLOR_MAROON, strings, 10);
	CrashDetected[playerid] = 85;
	return 1;
}//end OnPlayerSetDutyWeapons(playerid)



stock OnPlayerSetHomeWeapons(playerid)//����������� �� �������� /givegun � ����
{
	if( !IsPlayerConnectedEx(playerid) ) return 1;
	CrashDetected[playerid] = 86;
	if(gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "    ������������� ����� ���� RealWar ! �� �� ������ �������� ������ !");
		return 1;
	}
	if( PlayerInfo[playerid][pGunLic] != 1 && !gRealWar) return 1;
	if( gParameter5[playerid] == 1 )
	{
		SendClientMessage(playerid, COLOR_GREY, "   � ��� ���� ���, ����� ������� ������!");
		SendClientMessage(playerid, COLOR_GREY, "   ��� ���������� ��������� �� ������� � �������!");
		return 1;
	}

    ResetPlayerWeaponsEx(playerid);//�������� ������
    if(PlayerInfo[playerid][pJailed] != 0) return 1;
	if(PlayerInfo[playerid][pGun1] > 0 && 0 < PlayerInfo[playerid][pAmmo1] < 1000)
	{   //���� 2: ���������
		GivePlayerWeaponEx(playerid, PlayerInfo[playerid][pGun1], PlayerInfo[playerid][pAmmo1]);
	}
	if(PlayerInfo[playerid][pGun2] > 0 && 0 < PlayerInfo[playerid][pAmmo2] < 1000)
	{   //���� 3: ���������
		GivePlayerWeaponEx(playerid, PlayerInfo[playerid][pGun2], PlayerInfo[playerid][pAmmo2]);
	}
	if(PlayerInfo[playerid][pGun3] > 0 && 0 < PlayerInfo[playerid][pAmmo3] < 1000)
	{   //���� 4: ������������
		GivePlayerWeaponEx(playerid, PlayerInfo[playerid][pGun3], PlayerInfo[playerid][pAmmo3]);
	}
	if(PlayerInfo[playerid][pGun4] > 0 && 0 < PlayerInfo[playerid][pAmmo4] < 1000)
	{   //���� 5: ��������� ��������
		GivePlayerWeaponEx(playerid, PlayerInfo[playerid][pGun4], PlayerInfo[playerid][pAmmo4]);
	}
	GivePlayerWeaponEx(playerid, 5, 1);//����������� ����

	//���������� ����������, ����� �� ����������� �� ������, � ��� �� ���� ������ ��� ������������
	PlayerInfo[playerid][pGun1] = 0; PlayerInfo[playerid][pAmmo1] = 0;
	PlayerInfo[playerid][pGun2] = 0; PlayerInfo[playerid][pAmmo2] = 0;
	PlayerInfo[playerid][pGun3] = 0; PlayerInfo[playerid][pAmmo3] = 0;
	PlayerInfo[playerid][pGun4] = 0; PlayerInfo[playerid][pAmmo4] = 0;

	SetPVarInt(playerid, "gGetHomeWeapon", 1);
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "OnPlayerSetHomeWeapons(%d)", playerid);
	//ABroadCast(COLOR_MAROON, strings, 10);
	return 1;//myadd
}//end OOnPlayerSetHomeWeapons(playerid)


//stock GivePlayerWeaponEx(playerid, weaponid, ammo)
forward GivePlayerWeaponEx(playerid, weaponid, ammo);
public GivePlayerWeaponEx(playerid, weaponid, ammo)
{   //��� ���������� ������������� ������ ������� �� ����������� �� ���������, � �����������
	//if(PlayerInfo[playerid][pGunLic] != 1) return 1;//������, �.�. �� ����� �������� ������ � �����

	new Gun, Ammo;
	new slot = GetWeaponSlot(weaponid);
	GetPlayerWeaponData(playerid, slot, Gun, Ammo);
	if(Ammo > (999 - ammo))
	{   //��������� ������� �������� � ���� �����
	    //new strings[MAX_STRING];
		format(strings, sizeof(strings), "   �� �� ������ ����� ������ ����������� (ammo: %d)!", Ammo);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	DetectedGun[playerid][weaponid] = 1;
	iLastScrollWeapon[playerid] = weaponid;
	if(	(weaponid >= 1 && weaponid <= 15)
	|| weaponid == 40 || weaponid == 39 ||
		(weaponid >= 44 && weaponid <= 46))
	{   //���� ������ �� ����� ����� �������� ������ 1, �� ����������� 1
	    if(	(weaponid >= 1 && weaponid <= 9)
		|| weaponid == 40 || weaponid == 39 ||
			(weaponid >= 44 && weaponid <= 46))
	    {
			LastAmmo[playerid][weaponid] += ammo;//���� ��������� ������ ���������� �����,
			//ammo += 1;//??? �� ���������� ���-�� ��������
	    }
	    else// if(weaponid >= 10 && weaponid <= 15)
	    {
			LastAmmo[playerid][weaponid] = 1;
			ammo = 1;
	    }
	    LastWeaponInSlot[playerid][slot] = weaponid;
	}
	else if((weaponid >= 16 && weaponid <= 38)//39)
	|| (weaponid >= 41 && weaponid <= 43))
	{   //���� ������ ����� ����� �������� ������ 1, �� ����������
	    if(weaponid >= 25 && weaponid <= 27)
	    {
	        //���������� �� ��� ����� �� ����� �����,
			//�.�. ���� ��������� ������� �� ���� �����
			LastAmmo[playerid][25] += ammo;
			LastAmmo[playerid][26] += ammo;
			LastAmmo[playerid][27] += ammo;
			LastWeaponInSlot[playerid][3] = weaponid;
		}
	    else if(weaponid == 28 || weaponid == 29 || weaponid == 32)
	    {
			LastAmmo[playerid][28] += ammo;
			LastAmmo[playerid][29] += ammo;
			LastAmmo[playerid][32] += ammo;
			LastWeaponInSlot[playerid][4] = weaponid;
		}
	    else if(weaponid == 30 || weaponid == 31)
	    {
			LastAmmo[playerid][30] += ammo;
			LastAmmo[playerid][31] += ammo;
			LastWeaponInSlot[playerid][5] = weaponid;
		}
		else
		{
			LastAmmo[playerid][weaponid] += ammo;
			LastWeaponInSlot[playerid][slot] = weaponid;
		}
/*
		if(slot == 2) { PlayerInfo[playerid][pGun1] = weaponid; PlayerInfo[playerid][pAmmo1] = LastAmmo[playerid][weaponid]; }
		else if(slot == 3) { PlayerInfo[playerid][pGun2] = weaponid; PlayerInfo[playerid][pAmmo2] = LastAmmo[playerid][weaponid]; }
		else if(slot == 4) { PlayerInfo[playerid][pGun3] = weaponid; PlayerInfo[playerid][pAmmo3] = LastAmmo[playerid][weaponid]; }
		else if(slot == 5) { PlayerInfo[playerid][pGun4] = weaponid; PlayerInfo[playerid][pAmmo4] = LastAmmo[playerid][weaponid]; }
*/
	}
	/*else
	{
		LastAmmo[playerid][weaponid] = 0;
	}*/

	GivePlayerWeapon(playerid, weaponid, ammo);
	DetectedGun[playerid][weaponid] = 1;
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "GivePlayerWeapon(playerid: %d, weaponid: %d, ammo: %d) - LastAmmo: %d", playerid, weaponid, ammo, LastAmmo[playerid][weaponid]);
	//ABroadCast(ADMINS_MESSAGE_COLOR, strings, 1);
	//SendClientMessageToAll(COLOR_YELLOW, strings);
	return 1;
}


stock GetWeaponAmmoInSlot(weaponid)
{   //���������� ������������ ���-�� �������� � ������ ������
	if(weaponid == 0 || weaponid == 1) return 1;
	else if(2 <= weaponid <= 9) return 1;
	else if(weaponid == 22) return 15;
	else if(weaponid == 23) return 17;
	else if(weaponid == 24) return 7;

	else if(weaponid == 25) return 1;
	else if(weaponid == 26) return 2;
	else if(weaponid == 27) return 7;

	else if(weaponid == 28) return 50;
	else if(weaponid == 29) return 30;
	else if(weaponid == 32) return 50;

	else if(weaponid == 30) return 30;
	else if(weaponid == 31) return 50;

	else if(weaponid == 33) return 10;
	else if(weaponid == 34) return 1;

	else if(35 <= weaponid <= 38) return 500;
	else if(16 <= weaponid <= 18) return 1;
	else if(weaponid == 39) return 1;
	else if(41 <= weaponid <= 42) return 500;
	else if(weaponid == 43) return 2;

	else if(10 <= weaponid <= 15) return 1;
	else if(44 <= weaponid <= 46) return 1;
	else if(weaponid == 40) return 1;
	else return 0;
}
