//https://wiki.sa-mp.com/wiki/Animations
//https://wiki.sa-mp.com/wiki/AnimationsTable
//https://sampawno.ru/viewtopic.php?t=65 � ������������ �� �������



stock anim_OnPlayerSpawn(playerid)
{
	PreloadAnimLibEx(playerid);
}

//stock anim_OnPlayerKeyState(playerid, newkeys, oldkeys)
stock anim_OnPlayerKeyState_SPRINT(playerid)
{
	//��� ��������
	//if(IsKeyJustDown(KEY_SPRINT, newkeys, oldkeys))
	//if( !PRESSED(KEY_SPRINT) ) return 1;
	if(GetPVarInt(playerid, "UseLoopAnim") == 1)
	{
    	StopLoopingAnim(playerid);
       	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}

	if( GetPVarInt(playerid, "Intro") > 0 )//introtimer[playerid] != -1 )
	{//���� ������ ������ �� ����� �����������
	    for(new i; i < sizeof(Intro); i++)
	    {
			TextDrawHideForPlayer(playerid, Intro[i]);
		}
		PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
       	RegisterDialog(playerid);
       	return 1;
	}
	return 1;
}
//------------------------------------------------------------------------------
//��� ��������
stock OnePlayAnim(playerid, animlib[],animname[], Float:animspeed, looping, lockx, locky, freeze, time, forcesync = 1)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;
	if( IsPlayerControllable[playerid] == 1 ) return 1;
    //if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll) return 1;
    //if(FollowBy[playerid] != MAX_PLAYERS-1) return 1;
    
	ClearAnimations(playerid, 1);
	return ApplyAnimation(playerid, animlib, animname, animspeed, looping, lockx, locky, freeze, time, forcesync);//���������� �������� ��� ������
	//animlib - �������� ���������� ��������
	//animname - �������� ��������
	//animspeed - �������� ��������.
	//looping - ����������� (1) ��� ��� (0)
	//lockx - (0) - ������������ � ���. �������
	//locky - (0) - ������������ � ���. �������
	//� �������� ������ ������� ������ ����� �� ��������� ���������, ������� ������� �����������.
	//����� ��������� �������, ��� ������������� � �������� ������� �� ���������, ���� ����������� �� 0.
	//��������������� ������ ���� ������������ �� 1. ��� ����������� ���������� lockx - (1) � locky - (1)
	//freeze - ��������� ������ (1) � �������, ��������� (0)
	//time - ����� ������� ����������� ����� �� ����� ��� ��������� ��������. ������ � �������������. ��� ������������ ����� ������ ���� 0.
	//forcesync - ������������ �� 1, ����� ���������� playerid, ����� ���������������� �������� � ������� �������� �� ���� �������� (��������������)
}

stock LoopingAnim(playerid, animlib[],animname[], Float:animspeed, looping, lockx, locky, freeze, time, forcesync = 1)
{
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;
	//if( IsPlayerControllable[playerid] == 1 ) return 1;
    //if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll
	//	&& strcmp(animname, "BED_Loop_L", true) && strcmp(animname, "BED_Loop_R", true) ) return 1;
    //if(FollowBy[playerid] != MAX_PLAYERS-1) return 1;

    SetPVarString(playerid, "animlib", animlib);
    SetPVarString(playerid, "animname", animname);
    SetPVarFloat(playerid, "animspeed", animspeed);
    SetPVarInt(playerid, "looping", looping);
    SetPVarInt(playerid, "freeze", freeze);
    SetPVarInt(playerid, "time", time);
    
    SetPVarInt(playerid, "UseLoopAnim", 1);
     //forsync 2 - ����� ����������� ������� � ���,  � ������ �� ��������� ������ ��������
	//TextDrawShowForPlayer(playerid, G_ANIM_TD[0]);
	GameTextForPlayerEx(playerid, " Press ~b~~k~~PED_SPRINT~ ~n~~g~|~w~to stop the animation~g~|", 1000, 1);
	return ApplyAnimation(playerid, animlib, animname, animspeed, looping, lockx, locky, freeze, time, forcesync);
}
stock StopLoopingAnim(playerid)
{
	//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	SetPVarInt(playerid, "UseLoopAnim", 0);
	ClearAnimations(playerid, 1);
	return ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
}
stock PreloadAnimLibEx(playerid)
{
	if(GetPVarInt(playerid, "AnimLibsPreloaded") == 0)
	{
		PreloadAnimLib(playerid, "BASEBALL");
   		PreloadAnimLib(playerid, "BEACH");
		PreloadAnimLib(playerid, "benchpress");
		PreloadAnimLib(playerid, "BD_FIRE");
   		PreloadAnimLib(playerid, "BOMBER");
   		PreloadAnimLib(playerid, "CAMERA");
		PreloadAnimLib(playerid, "CAR_CHAT");
		PreloadAnimLib(playerid, "CARRY");
		PreloadAnimLib(playerid, "CASINO");
		PreloadAnimLib(playerid, "COP_AMBIENT");
 		PreloadAnimLib(playerid, "CRACK");
		PreloadAnimLib(playerid, "DAM_JUMP");
    	PreloadAnimLib(playerid, "DEALER");
		PreloadAnimLib(playerid, "DODGE");
    	PreloadAnimLib(playerid, "FOOD");
		PreloadAnimLib(playerid, "GANGS");
		PreloadAnimLib(playerid, "GRAVEYARD");
		PreloadAnimLib(playerid, "HEIST9");
		PreloadAnimLib(playerid, "INT_HOUSE");
		PreloadAnimLib(playerid, "INT_OFFICE");
		PreloadAnimLib(playerid, "KISSING");
		PreloadAnimLib(playerid, "LOWRIDER");
		PreloadAnimLib(playerid, "MD_CHASE");
    	PreloadAnimLib(playerid, "ON_LOOKERS");
		PreloadAnimLib(playerid, "PARK");
		PreloadAnimLib(playerid, "PAULNMAC");
		PreloadAnimLib(playerid, "PED");
		PreloadAnimLib(playerid, "RYDER");
   		PreloadAnimLib(playerid, "RAPPING");
   		PreloadAnimLib(playerid, "RIOT");
    	PreloadAnimLib(playerid, "SHOP");
   		PreloadAnimLib(playerid, "SMOKING");
		PreloadAnimLib(playerid, "SNM");
		PreloadAnimLib(playerid, "STRIP");
		PreloadAnimLib(playerid, "SUNBATHE");
		PreloadAnimLib(playerid, "SWAT");
    	PreloadAnimLib(playerid, "SWEET");
		SetPVarInt(playerid, "AnimLibsPreloaded", 1);
	}
}
stock PreloadAnimLib(playerid, animlib[])
{
	return ApplyAnimation(playerid, animlib,"null",0.0,0,0,0,0,0,1);
}


stock anim_List(playerid)
{
	new listitems[2882];
	strins(listitems, "1\t/dance - ����� ������", strlen(listitems));
	strins(listitems, "\n2\t/strip - ����� ��������-�����", strlen(listitems));
	strins(listitems, "\n3\t/kiss - ������������� ��������", strlen(listitems));
	strins(listitems, "\n4\t/walk - ����� ������ ��� ������� ������� "#SNEAK_ABOUT, strlen(listitems));
	strins(listitems, "\n5\t/chat - ������������� ������ ", strlen(listitems));
	strins(listitems, "\n6\t/laugh - ������� ������ ����� �� ������ ����", strlen(listitems));
	strins(listitems, "\n7\t/shifty - ������� ���-������ �� ������� � ������", strlen(listitems));
	strins(listitems, "\n8\t/threat - ������ ���� ���������� ������", strlen(listitems));
	strins(listitems, "\n9\t/coplook - ���������� ���� �� �����", strlen(listitems));
	strins(listitems, "\n10\t/lay - ������� �� ����� �������� �� �����", strlen(listitems));
	strins(listitems, "\n11\t/cower - ������� �� �������� � ����� ���� �� ������", strlen(listitems));
	strins(listitems, "\n12\t/vomit - ������", strlen(listitems));
	strins(listitems, "\n13\t/wave - ��������� ����� ���� ����� � ������ �����", strlen(listitems));
	strins(listitems, "\n14\t/slapass - ������� ����� ����� �� ������� �����", strlen(listitems));
	strins(listitems, "\n15\t/deal - ������� �����������", strlen(listitems));
	strins(listitems, "\n16\t/crack - ������������� ����������", strlen(listitems));
	strins(listitems, "\n17\t/smoke(f) - �������� � �����", strlen(listitems));
	strins(listitems, "\n18\t/groundsit - �������, �������� �� ������ ���� (��� ������)", strlen(listitems));
	strins(listitems, "\n19\t/taichi - �������� � ����� ��������� �����������", strlen(listitems));
	strins(listitems, "\n20\t/bedr - ������� �� ����� ���", strlen(listitems));
	strins(listitems, "\n21\t/bedl - ������� �� ������ ���", strlen(listitems));
	strins(listitems, "\n22\t/sexM - ������� ������� � �����", strlen(listitems));
	strins(listitems, "\n23\t/sexF - ������� ������� � �����", strlen(listitems));
	strins(listitems, "\n24\t/drugbuy - ������������� ���������", strlen(listitems));
	strins(listitems, "\n25\t/lowri - ����������� ������", strlen(listitems));
	strins(listitems, "\n26\t/wof - ������� ����� �����", strlen(listitems));
	strins(listitems, "\n27\t/death - ���������� �����", strlen(listitems));
	strins(listitems, "\n28\t/sit - ������� �� ����", strlen(listitems));
	strins(listitems, "\n29\t/arrested - ������� � ���������", strlen(listitems));
	strins(listitems, "\n30\t/atm - ���������� ���������", strlen(listitems));
	strins(listitems, "\n31\t/climb - ��������� ���� �����", strlen(listitems));
	strins(listitems, "\n32\t/damarm - �������� ��������", strlen(listitems));
	strins(listitems, "\n33\t/dive - ������ � ��������", strlen(listitems));
	strins(listitems, "\n34\t/floor - ���� �� �����", strlen(listitems));
	strins(listitems, "\n35\t/taxi - �������� �� ������", strlen(listitems));
	strins(listitems, "\n36\t/shotface - ������� ���� � ���� ", strlen(listitems));
	strins(listitems, "\n37\t/shotfront - ���� �� �����", strlen(listitems));
	strins(listitems, "\n38\t/shotstom - ������� � �����", strlen(listitems));
	strins(listitems, "\n39\t/shove - ����������� � �����", strlen(listitems));
	strins(listitems, "\n40\t/idlestance - ������ ��� ������", strlen(listitems));
	strins(listitems, "\n41\t/laybac - ��������", strlen(listitems));
	strins(listitems, "\n42\t/direction - �������� ����� �����", strlen(listitems));
	strins(listitems, "\n43\t/parksita - ����������� �������", strlen(listitems));
	strins(listitems, "\n44\t/parksitb - ����������� �������", strlen(listitems));
	strins(listitems, "\n45\t/tgangs - �����������", strlen(listitems));
	strins(listitems, "\n46\t/lkt - ����� ����� �����", strlen(listitems));
	strins(listitems, "\n47\t/breach - ��������", strlen(listitems));
	strins(listitems, "\n48\t/katana - ������� � ����� ������", strlen(listitems));
	strins(listitems, "\n49\t/bathit - ���� �� �����", strlen(listitems));
	strins(listitems, "\n50\t/rap - ������ ���", strlen(listitems));
	strins(listitems, "\n51\t/crackdeth - ����������", strlen(listitems));
	strins(listitems, "\n52\t/graveyard - ������ ������ ����", strlen(listitems));
	strins(listitems, "\n53\t/point - ������� �����������", strlen(listitems));
	strins(listitems, "\n54\t/lndroll - ��������", strlen(listitems));
	strins(listitems, "\n55\t/nut - ����� ��� ������", strlen(listitems));
	strins(listitems, "\n56\t/wank - ��������� �������", strlen(listitems));
	strins(listitems, "\n57\t/piss - ������", strlen(listitems));
	strins(listitems, "\n58\t/govduty - ����� �� ������ �����������", strlen(listitems));
	strins(listitems, "\n59\t/fuck - ���������� �������", strlen(listitems));
	strins(listitems, "\n60\t/fucku - �����������", strlen(listitems));
	strins(listitems, "\n61\t/seatdown - ��������", strlen(listitems));
	strins(listitems, "\n62\t/barserve - �������� �� ������ ��� �������", strlen(listitems));
	strins(listitems, "\n63\t/barman - �������� �� ������ ��� �������", strlen(listitems));
	strins(listitems, "\n64\t/dieb - ������ �� ������ (������� 1)", strlen(listitems));
	strins(listitems, "\n65\t/dief - ������ �� ������ (������� 2)", strlen(listitems));
	strins(listitems, "\n66\t/diel - ������ �� ������ (������� 3)", strlen(listitems));
	strins(listitems, "\n67\t/angry - �����������", strlen(listitems));
	strins(listitems, "\n68\t/chant - ������������", strlen(listitems));
	strins(listitems, "\n69\t/punches - ������� � ����", strlen(listitems));
	strins(listitems, "\n70\t/sitinw - �����, �������� �� ��� ����", strlen(listitems));
	strins(listitems, "\n71\t/camcrch- ������� ��������� ����", strlen(listitems));
	strins(listitems, "\n72\t/piccrch - ���� ���������������", strlen(listitems));
	strins(listitems, "\n73\t/damdive - ������ �� �����", strlen(listitems));
	strins(listitems, "\n74\t/heist - ���������� ��������� � �������� �� ���\0", strlen(listitems));

	if(strlen(listitems) > sizeof(listitems))
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error: ������ �������� %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(listitems), sizeof(listitems));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(listitems) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   ������ �������� ����");
		return 1;
	}
	ShowPlayerDialogEx(playerid, ANIM_DIALOG, DIALOG_STYLE_LIST, "������ ��������:", listitems, "OK", "�����");
	return 1;
}



stock anim_OnPlayerUpdate(playerid, animationid, newstate)
{   //���������� �� OnPlayerUpdate
	//new anim_id = GetPlayerAnimationIndex(playerid);
	if(animationid && !IsPlayerInAnyVehicle(playerid))
	{
		new animlib[32]; new animNew[32];
		GetAnimationName(animationid, animlib, 32, animNew, 32);
		//if(	strcmp(animOld[playerid], animNew, true) )
		if(	animationid != PlayerLastAnimation[playerid])
		//if(	anim_id !=  GetPVarInt(playerid, "iPlayerAnim"))
		{
			if(CHECKING[PlayerAnimationChange])
			{
				OnPlayerAnimationChange(playerid, animationid, animlib, animNew, animOld[playerid]);
			}
			//=================================================================
			/*new Float: health = LastHealth[playerid];
			if( (strfind(animNew, "RUN", true) != -1 || strfind(animNew, "SPRINT", true) != -1) &&
				health < 100.0) 
			{  //���� � �������� ����������� RUN ��� SPRINT
				TogglePlayerWalking(playerid, true);
	    		//SetPlayerWalkingStyle(playerid, WALK_GANGSTA2);				
			}*/
			//=================================================================
			//IsValidSkin(GetPlayerSkin(playerid)) && GetPlayerSkin(playerid) != 0 &&
			if(ANTICHEAT == 1)
			{
				if( newstate == PLAYER_STATE_ONFOOT && //������ ����������� ����� ������
					GetPlayerSpeed(playerid) >= 10 && GetPlayerSkin(playerid) != 0 && !gAnticheat[playerid] && (
					//���������� ����� �������� �� ����� ����������
					( !strcmp(animNew, "SPRINT_CIVI", true) && !strcmp(animOld[playerid], "RUN_PLAYER", true) ) ||
					( !strcmp(animNew, "WALK_PLAYER", true)) && !strcmp(animOld[playerid], "SPRINT_CIVI", true) )
				  )
				{
					format(ReasonPunishment[playerid], 64, "SPRINT CJ (Skin:%d, Speed:%d)", GetPlayerSkin(playerid), GetPlayerSpeed(playerid));

					TogglePlayerControllableEx(playerid, 0);//������������� ����� �� � ������
					PlayerTazed[playerid] = 1;
					PlayerTazeTime[playerid] = 30;
					//new strings[MAX_STRING];
					format(strings, sizeof(strings), "* %s ����������� �� %d ������, reason: %s", PlayerName(playerid), PlayerTazeTime[playerid], ReasonPunishment[playerid]);
					ProxDetector(playerid, 30.0,  strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

					GameTextForPlayerEx(playerid, "~r~Tazed", 2500, 3);
				}
				//==================================================================
				OnPlayerIsAtMachines(playerid, animationid);
				//==================================================================
			}
		}
		PlayerLastAnimation[playerid] = animationid;
		strmid(animOld[playerid], animNew, 0, strlen(animNew), 32);
		//SetPVarInt(playerid, "iPlayerAnim", anim_id);
	}
//==============================================================================
	if(ANTICHEAT == 0) return 1;
	if(gAnticheat[playerid] == 1) return 1;
//���� ���� ������� ������ ����
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid, x,y,z);
	if(	x != CurPos[0][playerid] && y != CurPos[1][playerid] && CurPos[2][playerid] > 19.0 &&
		(animationid >= 1538 && animationid < 1544) &&//nim_id == 1250
		!IsPlayerInArea(playerid, specialzone[15]) &&
		PlayerInfo[playerid][pInt] == 0 &&
		!IsPlayerInRangeOfPoint(playerid, 45.0,1971.0957,-1197.7554,17.4500) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,2531.7014,1566.1423,8.4171) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,2581.5244,2384.0850,15.8500) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,227.0786,-1186.5819,73.4500) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,2133.4072,1113.7994,7.0128) &&
		!IsPlayerInRangeOfPoint(playerid, 140.0,1988.5143,1566.2893,8.0484) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,2102.2126,1921.1638,9.0792) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,195.3366,-1231.1996,76.5034) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,-1472.9652,-2126.6211,-0.5448) &&
		!IsPlayerInRangeOfPoint(playerid, 20.0,2314.0916,-1417.5372,21.6150)
	  )
	{
		if(IsKicked[playerid] == 0)
		{
			format(ReasonPunishment[playerid], 64, "FLY %d[%.1f]", animationid, CurPos[2][playerid]);
        	new strtmp[56 + 24+3 + 64];//34 + 24+3 +64�=�125
			/*if(gVoteKicked == MAX_PLAYERS-1)
			{
				gVoteKicked = playerid;
				format(strtmp, sizeof(strtmp), "CEPBEP: ����������� �� ��� %s[%d] - %s (USE: /votekick)",
					PlayerName(playerid), playerid, ReasonPunishment[playerid]);
				SendClientMessageToAll(COLOR_MAROON, strtmp);
				return 1;
			}
			else
			{*/
			format(strtmp, sizeof(strtmp), "CEPBEP: %s[%d] kicked, reason: %s",
				PlayerName(playerid),playerid, ReasonPunishment[playerid]);
			Log(CHEAT, strtmp);
    		SendAllAdminMessage(COLOR_MAROON, strtmp, 3);
			IsKicked[playerid] = 1;
			return 1;
			//}
		}
	}
	return 1;
}

forward StopAnimationEx(playerid);
public StopAnimationEx(playerid)
{
	RemovePlayerAttachedObject(playerid, EAT_SLOT);
	return 1;
}



stock anim_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != ANIM_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		LIST(playerid);
	 	return 1;
	}
	//new msgitem[256+1];
	//new giveplayerid;
//	ShowPlayerDialogEx(playerid, 36, DIALOG_STYLE_LIST, "������ ��������:", listitems, "OK", "Cancel");
	if(listitem == 0)//strins(listitems, "1\t/dance - ����� ������\n", strlen(listitems), 27);
	{

	}
	else if(listitem == 1)
	{//	strins(listitems, "2\t/strip - ����� ��������-�����\n", strlen(listitems), 35);

	}
	else if(listitem == 2)
	{//	strins(listitems, "3\t/kiss  - ������������� ��������\n", strlen(listitems), 37);

	}
	else if(listitem == 3)
	{//	strins(listitems, "4\t/walk - ����� ������ ��� ������� ������� Alt\n", strlen(listitems), 50);

	}
	else if(listitem == 4)
	{//	strins(listitems, "5\t/chat - ������������� ������ \n", strlen(listitems), 35);
		LoopingAnim(playerid, "PED", "IDLE_CHAT", 4.0, 1, 0, 0, 0, 0);
	}
	else if(listitem == 5)
	{//	strins(listitems, "6\t/laugh - ������� ������ ����� �� ������ ����\n", strlen(listitems), 50);
		OnePlayAnim(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0); // Laugh
	}
	else if(listitem == 6)
	{//	strins(listitems, "7\t/shifty - ������� ���-������ �� ������� � ������\n", strlen(listitems), 54);
		OnePlayAnim(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0); // Rob Lookout
	}
	else if(listitem == 7)
	{//	strins(listitems, "8\t/threat - ������ ���� ���������� ������\n", strlen(listitems), 45);
		OnePlayAnim(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 0); // Rob
	}
	else if(listitem == 8)
	{//	strins(listitems, "9\t/coplook - ���������� ���� �� �����\n", strlen(listitems), 41);
		LoopingAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1); // Arms crossed
	}
	else if(listitem == 9)
	{//	strins(listitems, "10\t/lay - ������� �� ����� �������� �� �����\n", strlen(listitems), 48);
		LoopingAnim(playerid, "SUNBATHE", "Lay_Bac_in", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 10)
	{//	strins(listitems, "11\t/cower - ������� �� �������� � ����� ���� �� ������\n", strlen(listitems), 58);
		LoopingAnim(playerid, "ped", "cower", 4.0, 1, 0, 0, 0, 0); // Taking Cover
	}
	else if(listitem == 11)
	{//	strins(listitems, "12\t/vomit - ������\n", strlen(listitems), 22);
		OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 4.0, 0, 0, 0, 0, 0); // Vomit BAH!
	}
	else if(listitem == 12)
	{//	strins(listitems, "13\t/wave - ��������� ����� ���� ����� � ������ �����\n", strlen(listitems), 56);
		LoopingAnim(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0); // Wave
	}
	else if(listitem == 13)
	{//	strins(listitems, "14\t/slapass - ������� ����� ����� �� ������� �����\n", strlen(listitems), 54);
		OnePlayAnim(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0); // Ass Slapping
	}
	else if(listitem == 14)
	{//	strins(listitems, "15\t/deal - ������� �����������\n", strlen(listitems), 34);
		LoopingAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 1, 0, 0, 0, 0); // Deal Drugs
	}
	else if(listitem == 15)
	{//	strins(listitems, "16\t/crack - �������������\n", strlen(listitems), 17);
		LoopingAnim(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0); // Dieing of Crack
	}
	else if(listitem == 16)
	{//	strins(listitems, "17\t/smoke(f) - �������� � �����\n", strlen(listitems), 35);

	}
	else if(listitem == 17)
	{//	strins(listitems, "18\t/groundsit - ������� �������� �� ������ ���� (��� ������)\n", strlen(listitems), 64);
		LoopingAnim(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0); // Sit
	}
	else if(listitem == 18)
	{//	strins(listitems, "19\t/taichi - �������� � ����� ��������� �����������\n", strlen(listitems), 55);
		LoopingAnim(playerid, "PARK", "Tai_Chi_Loop", 4.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 19)
	{//	strins(listitems, "20\t/bedr - ������� �� ����� ���\n", strlen(listitems), 35);
		LoopingAnim(playerid, "INT_HOUSE", "BED_Loop_R", 4.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 20)
	{//	strins(listitems, "21\t/bedl - ������� �� ������ ���\n", strlen(listitems), 22);
		LoopingAnim(playerid, "INT_HOUSE", "BED_Loop_L", 4.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 21)
	{//	strins(listitems, "22\t/sexM - ������� ������� � �����\n", strlen(listitems), 38);
		LoopingAnim(playerid, "SNM", "SPANKINGP", 4.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 22)
	{//	strins(listitems, "23\t/sexF - ������� ������� � �����\n", strlen(listitems), 38);
		LoopingAnim(playerid, "SNM", "SPANKINGW", 4.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 23)
	{//	strins(listitems, "24\t/drugbuy - ������������� ���������\n", strlen(listitems), 41);
		OnePlayAnim(playerid, "GANGS", "DRUGS_BUY", 4.1, 0, 0, 0, 0, 0);
	}
	else if(listitem == 24)
	{//	strins(listitems, "25\t/lowri - ����������� ������\n", strlen(listitems), 34);
		LoopingAnim(playerid, "LOWRIDER", "RAP_A_Loop", 4.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 25)
	{//	strins(listitems, "26\t/wof - ������� ����� �����\n", strlen(listitems), 33);
		OnePlayAnim(playerid, "CASINO", "wof", 4.1, 0, 0, 0, 0, 0);
	}
	else if(listitem == 26)
	{//	strins(listitems, "27\t/death - ���������� �����\n", strlen(listitems), 32);
		LoopingAnim(playerid, "SWEET", "Sweet_injuredloop", 4.1, 0, 1, 1, 1, 1);
	}
	else if(listitem == 27)
	{//	strins(listitems, "28\t/sit - ������� �� ����\n", strlen(listitems), 29);
		LoopingAnim(playerid, "SUNBATHE", "SitnWait_in_W", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 28)
	{//	strins(listitems, "29\t/arrested - ������� � ���������\n", strlen(listitems), 38);
		LoopingAnim(playerid, "PED", "ARRESTgun", 4.1, 0, 0, 0, 1, 1);
	}
	else if(listitem == 29)
	{//	strins(listitems, "30\t/atm - ���������� ���������\n", strlen(listitems), 34);
		OnePlayAnim(playerid, "PED", "ATM", 4.1, 0, 0, 0, 0, 0);
	}
	else if(listitem == 30)
	{//	strins(listitems, "31\t/climb - ��������� ���� �����\n", strlen(listitems), 36);
   	     LoopingAnim(playerid, "PED", "CLIMB_idle", 4.2, 1, 0, 0, 0, 0);
	}
	else if(listitem == 31)
	{//	strins(listitems, "32\t/damarm - �������� ��������\n", strlen(listitems), 34);
   	     OnePlayAnim(playerid, "PED", "DAM_armR_frmFT", 4.2, 0, 0, 0, 0, 0);
	}
	else if(listitem == 32)
	{//	strins(listitems, "33\t/dive - ������ � ��������\n", strlen(listitems), 30);
   	     OnePlayAnim(playerid, "PED", "EV_dive", 4.2, 0, 0, 0, 0, 0);
	}
	else if(listitem == 33)
	{//	strins(listitems, "34\t/floor - ���� �� �����\n", strlen(listitems), 29);
  	     LoopingAnim(playerid, "PED", "FLOOR_hit", 4.2, 0, 0, 0, 1, 1);
	}
	else if(listitem == 34)
	{//	strins(listitems, "35\t/taxi - �������� �� ������\n", strlen(listitems), 33);
   	     LoopingAnim(playerid, "PED", "IDLE_taxi", 4.1, 0, 0, 0, 0, 0);
	}
	else if(listitem == 35)
	{//	strins(listitems, "36\t/shotface - ������� ���� � ���� \n", strlen(listitems), 39);
   	     LoopingAnim(playerid, "PED", "KO_shot_face", 4.2, 0, 1, 1, 1, 1);
	}
	else if(listitem == 36)
	{//	strins(listitems, "37\t/shotfront - ���� �� �����\n", strlen(listitems), 33);
   	     LoopingAnim(playerid, "PED", "KO_shot_front", 4.2, 0, 1, 1, 1, 1);
	}
	else if(listitem == 37)
	{//	strins(listitems, "38\t/shotstom - ������� � �����\n", strlen(listitems), 34);
   	     LoopingAnim(playerid, "PED", "KO_shot_stom", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 38)
	{//	strins(listitems, "39\t/shove - ����������� � �����\n", strlen(listitems), 36);
   	     OnePlayAnim(playerid, "PED", "Shove_Partial", 4.3, 0, 0, 0, 0, 0);
	}
	else if(listitem == 39)
	{//	strins(listitems, "40\t/idlestance  - ������ ��� ������\n", strlen(listitems), 39);
   	     LoopingAnim(playerid, "PED", "woman_idlestance", 4.3, 1, 0, 0, 0, 0);
	}
	else if(listitem == 40)
	{//	strins(listitems, "41\t/laybac - ��������\n", strlen(listitems), 25);
   	     LoopingAnim(playerid, "SUNBATHE", "Lay_Bac_in", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 41)
	{//	strins(listitems, "42\t//direction - �������� ����� �����\n", strlen(listitems), 41);
   	     OnePlayAnim(playerid, "ON_LOOKERS", "Pointup_in", 4.4, 0, 0, 0, 0, 0);
	}
	else if(listitem == 42)
	{//	strins(listitems, "43\t/parksita - ����-������� �������\n", strlen(listitems), 39);
		LoopingAnim(playerid, "SUNBATHE", "ParkSit_W_idleA", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 43)
	{//	strins(listitems, "44\t/parksitb- ����-������� �������\n", strlen(listitems), 38);
		LoopingAnim(playerid, "SUNBATHE", "ParkSit_W_idleB", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 44)
	{//	strins(listitems, "45\t/tgangs  - �����������\n", strlen(listitems), 29);
		OnePlayAnim(playerid, "GANGS", "hndshkba", 4.3, 0, 0, 0, 0, 0);
	}
	else if(listitem == 45)
	{//	strins(listitems, "46\t/lkt - ����� ����� �����\n", strlen(listitems), 31);
		OnePlayAnim(playerid, "SWAT", "swt_lkt", 4.3, 0, 0, 0, 0, 0);
	}
	else if(listitem == 46)
	{//	strins(listitems, "47\t/breach - ��������\n", strlen(listitems), 25);
		OnePlayAnim(playerid, "SWAT", "swt_breach_01", 4.3, 0, 0, 0, 0, 0);
	}
	else if(listitem == 47)
	{//	strins(listitems, "48\t/katana - ������� � ����� ������\n", strlen(listitems), 39);
		OnePlayAnim(playerid, "BASEBALL", "Bat_block", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 48)
	{//	strins(listitems, "49\t/bathit - ���� �� �����\n", strlen(listitems), 30);
		LoopingAnim(playerid, "BASEBALL", "Bat_Hit_3", 4.3, 0, 1, 1, 1, 1);
	}
	else if(listitem == 49)
	{//	strins(listitems, "50\t/rap - ������ ���\n", strlen(listitems), 24);
		LoopingAnim(playerid, "benchpress", "gym_bp_celebrate", 4.3, 1, 0, 0, 0, 0);
	}
	else if(listitem == 50)
	{//	strins(listitems, "51\t/crackdeth - ����������\n", strlen(listitems), 30);
		LoopingAnim(playerid, "CRACK", "crckdeth1", 4.4, 1, 0, 0, 0, 0);
	}
	else if(listitem == 51)
	{//	strins(listitems, "52\t/graveyard - ������ ������ ����\n", strlen(listitems), 38);
		LoopingAnim(playerid, "GRAVEYARD", "mrnM_loop", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 52)
	{//	strins(listitems, "53\t/point - ������� �����������\n", strlen(listitems), 35);
   	     OnePlayAnim(playerid, "ON_LOOKERS", "point_loop", 4.4, 0, 0, 0, 0, 0);
	}
	else if(listitem == 53)
	{//	strins(listitems, "54\t/lndroll  - ��������\n", strlen(listitems), 27);
   	     LoopingAnim(playerid, "MD_CHASE", "MD_HANG_Lnd_Roll", 4.4, 0, 1, 1, 1, 1);
	}
	else if(listitem == 54)
	{//	strins(listitems, "55\t/nut - ����� ��� ������\n", strlen(listitems), 30);
   	     LoopingAnim(playerid, "PED", "HIT_back", 0.1, 1, 0, 0, 0, 0);
	}
	else if(listitem == 55)
	{//	strins(listitems, "56\t/wank - �����������\n", strlen(listitems), 26);
   	     LoopingAnim(playerid, "PAULNMAC", "wank_loop", 4.4, 1, 0, 0, 0, 0);
	}
	else if(listitem == 56)
	{//	strins(listitems, "57\t/piss - ������\n", strlen(listitems), 21);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
		PlaySoundForPlayerInRange(playerid, SOUND_PISSING, 30.0);
		LoopingAnim(playerid, "PAULNMAC", "Piss_in", 4.4, 1, 0, 0, 0, 0); //������

		/*PlayerInfo[playerid][pParam4] --;
		if(PlayerInfo[playerid][pParam4] < operator4) { gParameter4[playerid] = 0; }
		if(PlayerInfo[playerid][pParam4] <= 0) { PlayerInfo[playerid][pParam4] = 0; }
		SetPlayerShowScale(playerid, 4, PlayerInfo[playerid][pParam4], operator4);*/
	}
	else if(listitem == 57)// && IsPlayerInRangeOfPoint(playerid, 2.0, 359.3396,173.5515,1008.8892)
	{// strins(listitems, "\n58\t/govduty - ����� �� ������ �����������", strlen(listitems), 70);
		//SetPlayerPosEx(playerid, 359.3396,173.5515,1008.8892, 270.0000);

		//SetCameraBehindPlayer(playerid);
		LoopingAnim(playerid, "INT_OFFICE", "FF_Dam_Fwd", 4.0, 0, 0, 0, 1, 1);//4.0, 0, 0, 0, 1, 1
		//LoopingAnim(playerid, "PED", "SEAT_down", 4.0, 0, 1, 1, 1, 0);//4.0, 0, 1, 1, 1, 0
		//OnePlayAnim(playerid, "INT_OFFICE", "FF_Dam_Fwd", 4.0, 0, 0, 0, 1, 1, 1);//���������� �������� ��� ������
		//OnePlayAnim(playerid, "PED", "SEAT_down", 4.0, 0, 1, 1, 1, 0, 1);//���������� �������� ��� ������
		//animlib - �������� ���������� ��������
		//animname - �������� ��������
		//animspeed - �������� ��������.
		//looping - ����������� (1) ��� ��� (0)
		//lockx - (0) - ������������ � ���. �������
		//locky - � �������� ������ ������� ������ ����� �� ��������� ���������,
		//������� ������� �����������. ����� ��������� �������,
		//��� ������������� � �������� ������� �� ���������, ���� ����������� �� 0.
		//��������������� ������ ���� ������������ �� 1.
		//freeze - ��������� ������ (1) � �������, ��������� (0)
		//lp - ����� ������� ����� ����� �� ����� ��� ��������� ��������. ������ � �������������. ��� ������������ ����� ������ ���� 0.
		//forcesync - ������������ �� 1, ����� ���������� playerid, ����� ���������������� �������� � ������� �������� �� ���� �������� (��������������)

	}
	else if(listitem == 58)
	{//	strins(listitems, "59\t/fuck - ���������� �������\n", strlen(listitems), 33);
 //OnePlayAnim(playerid, "RIOT", "RIOT_FUKU", 4.0, 0, 0, 0, 0, 0);
//PlaySoundForPlayer(playerid, 4001);
	}
	else if(listitem == 59)
	{//	strins(listitems, "60\t/fucku - �����������\n", strlen(listitems), 27);
		OnePlayAnim(playerid, "PED", "fucku", 4.1, 0, 0, 0, 0, 0);
	}
	else if(listitem == 60)
	{//	strins(listitems, "61\t/seatdown - ��������\n", strlen(listitems), 27);
		LoopingAnim(playerid, "PED", "SEAT_down", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 61)
	{//	strins(listitems, "62\t/barserve - �������� �� ������ ��� �������\n", strlen(listitems), 49);
		LoopingAnim(playerid, "BAR", "Barserve_loop", 4.0, 1, 0, 0, 0, 0);
	}
	else if(listitem == 62)
	{//	strins(listitems, "63\t/barman - �������� �� ������ ��� �������\n", strlen(listitems), 47);
		LoopingAnim(playerid, "BAR", "BARman_idle", 4.0, 1, 0, 0, 0, 0);
	}
	else if(listitem == 63)
	{//	strins(listitems, "64\t/dieb - ������ �� ������ (������� 1)\n", strlen(listitems), 43);
		LoopingAnim(playerid, "FOOD", "FF_Die_Bkw", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 64)
	{//	strins(listitems, "65\t/dief - ������ �� ������ (������� 2)\n", strlen(listitems), 43);
		LoopingAnim(playerid, "FOOD", "FF_Die_Fwd", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 65)
	{//	strins(listitems, "66\t/diel - ������ �� ������ (������� 3)\n", strlen(listitems), 43);
		LoopingAnim(playerid, "FOOD", "FF_Die_Left", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 66)
	{//	strins(listitems, "67\t/angry - �����������\n", strlen(listitems), 27);
		OnePlayAnim(playerid, "RIOT", "RIOT_ANGRY", 4.0, 0, 0, 0, 0, 0);
	}
	else if(listitem == 67)
	{//	strins(listitems, "68\t/chant - ������������\n", strlen(listitems), 28);
		LoopingAnim(playerid, "RIOT", "RIOT_CHANT", 4.0, 1, 0, 0, 0, 0);
	}
	else if(listitem == 68)
	{//	strins(listitems, "69\t/punches - ������� � ����\n", strlen(listitems), 32);
		OnePlayAnim(playerid, "RIOT", "RIOT_PUNCHES", 4.0, 0, 1, 1, 0, 0);
	}
	else if(listitem == 69)
	{//	strins(listitems, "70\t/sitinw - ����� �������� �� ��� ����\n", strlen(listitems), 43);
		LoopingAnim(playerid, "SUNBATHE", "SitnWait_in_W", 4.0, 0, 1, 1, 1, 0);
	}
	else if(listitem == 70)
	{//	strins(listitems, "71\t/camcrch- ������� ��������� ����\n", strlen(listitems), 39);
		LoopingAnim(playerid, "CAMERA", "camcrch_cmon", 4.0, 0, 0, 0, 1, 0);
	}
	else if(listitem == 71)
	{//	strins(listitems, "72\t/piccrch - ���� ���������������\n", strlen(listitems), 38);
		LoopingAnim(playerid, "CAMERA", "piccrch_in", 4.0, 0, 0, 0, 1, 0);
	}
	else if(listitem == 72)
	{//	strins(listitems, "73\t/damdive - ������ �� �����\n", strlen(listitems), 33);
		LoopingAnim(playerid, "DAM_JUMP", "DAM_Dive_Loop", 4.0, 0, 1, 1, 1, 0);
		//LoopingAnim(playerid, "DAM_JUMP", "DAM_LAUNCH", 4.0,0,1,1,1,0);//�����
	}
	else if(listitem == 73)
	{//	strins(listitems, "74\t/heist - ���������� ��������� � �������� �� ���\n", strlen(listitems), 54);
		LoopingAnim(playerid, "HEIST9", "CAS_G2_GasKO", 4.0, 0, 1, 1, 1, 0);
	}
	return 1;
}

