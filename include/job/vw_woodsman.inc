new Wood1[MAX_VEHICLES+1]; new Wood2[MAX_VEHICLES+1]; new Wood3[MAX_VEHICLES+1];//��� ����������

//��� ���������� ������
new Float:aRandomWoodsman[13][4] = {
{-569.3035,-97.2541,64.3952,184.1927},
{-565.8554,-68.6582,64.2800,358.3843},
{-569.1985,-118.4964,68.2742,355.2278},
{-534.5602,-152.6068,76.8814,183.4152},
{-541.5112,-165.5502,78.4063,185.5040},
{-523.0903,-194.5022,78.4047,181.1173},
{-481.1960,-153.9977,75.7812,185.1673},
{-478.1623,-128.2985,67.0541,4.1866},
{-475.8801,-115.2853,63.9060,175.3494},
{-472.0418,-86.8622,60.2833,85.1318},
{-489.8714,-88.4371,61.0038,93.9052},
{-450.0172,-48.4292,59.6666,279.0637},
{-432.8930,-49.2886,58.9462,90.1452}
};

stock woodsman_OnPlayerConnect(playerid)
{
//��� ����������
	WoodsmanLoading[playerid] = false;
}

stock woodsman_OnPlayerPickUp(playerid, pickupid)
{
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;

	//if(PlayerInfo[playerid][pJob] != WOODSMAN) return 1;
	//--------------------------------------------------------------------------
//��� ���������� STEP1
	if( (pickupid == PickupID[14] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z])) ||//����������
		(PlayerInfo[playerid][pJob] == WOODSMAN && IsPlayerInRangeOfPoint(playerid, 2.1, SBizInfo[56][sbEntranceX],SBizInfo[56][sbEntranceY],SBizInfo[56][sbEntranceZ]))
      )
	{
		if(gOnDuty[playerid])
		{   //���� ��� � �� �� ��������� � �� � �������
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ��� ������, ����� ����� �� ������!!!!!!");
			return 1;
		}
		if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != WOODSMAN)
		{
			format(strings, sizeof(strings), "������������: {0080FF}�� �� ������ {FFFFFF}%s{0080FF}. ����� ��������� (USE: /quitjob).", GetPlayerJob(playerid) ); //���������
			SendClientMessage(playerid, COLOR_GREEN, strings);
			return 1;
		}
		/*if(gJobDuty[playerid])
		{   //���� ��� � �� �� ��������� � �� � �������
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ��� ������, ����� ����� �� ���������!!!!");
			return 1;
		}*/

        if(SBizInfo[56][sbTill] <= 0)
        {
      		SendClientMessage(playerid, COLOR_GREY, "   ��������, ��������� �������. � ����� ��� �����.");
      		return 1;
        }
		if(gJobDuty[playerid])//if(PlayerInfo[playerid][pJob] == WOODSMAN)
		{
			//MenuOperation[playerid] = 165);
			ShowPlayerDialogGap(playerid, WOODSMAN_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ���������","�� ������������� ������� ��������� ������� ����?","��","���");
		}
		else
		{
			//MenuOperation[playerid] = 166);
			new dlgitem[] = "����� ������ ������ ��������:\
\n1. ������������� � ������� ������\
\n2. ����� ���������� ����� � ��������� ���� (DFT-500)\
\n3. � ����������� ������ ����������� ������(�� ���)\
\n4. ����� ����, ��� �� ��� ���������\
\n��� ������� �������� ��� � ����(�� ���) � ������� �� ���������\
\n\n�� ������ �����������, ����� ������ ������?";
			ShowPlayerDialogGap(playerid, WOODSMAN_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ���������",dlgitem,"��","���");
		}
	}
	return 1;
}

stock woodsman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != WOODSMAN_DIALOG) return 1;//��� ���������� STEP2
//ShowPlayerDialogGap(playerid, WOODSMAN_DIALOG, DIALOG_STYLE_MSGBOX, "������ ��������","�� ������� ������ ������ ��������?","��","���");
    if(!response) return 1;
//if(MenuOperation[playerid] == 166)
 	if(PlayerInfo[playerid][pJob] == WOODSMAN)//��� ���������� STEP10
	{
       	PlayerInfo[playerid][pJob] = 0;	gJobDuty[playerid] = 0;
       	WoodsmanLoading[playerid] = false;
		SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� �������� ������ ��������!");
		if(IsPlayerAttachedObjectSlotUsed(playerid, OBJECT_SLOT)) RemovePlayerAttachedObject(playerid, OBJECT_SLOT);
		DisablePlayerCheckpointEx(playerid);
		//nCarID[playerid] = 0; nCarModel[playerid] = 0;
		JobAmmount[playerid] = 0;
	}
	else //if(PlayerInfo[playerid][pJob] != WOODSMAN)
	{
		PlayerInfo[playerid][pJob] = WOODSMAN; gJobDuty[playerid] = 1;
   		SetPlayerSkinEx(playerid, 16);
      	SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� ������ ������ ��������!");
      	//SendClientMessage(playerid, COLOR_WHITE, "{007700}������������: {009900}������ � Packer(������: 443).");
      	SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������ � DFT-30(������: 578)!");
	}
	return 1;
}


stock woodsman_OnPlayerStateChange(playerid, newstate)
{
	if(newstate != PLAYER_STATE_DRIVER) return 1;
//���� ID ������ ��������� ����� ��������� 2
	if(PlayerInfo[playerid][pJob] != WOODSMAN) return 1;
	if(CP[playerid] == CP_WOODSMAN_3) return 1;
    //nCarID[playerid] = GetPlayerVehicleID(playerid);
    //nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);
	if(nCarModel[playerid] != 578)
	{
		SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������ � DFT-30(������: 578)!!");
		return 1;
	}
	if(JobAmmount[playerid] == 3)//��� ���������� STEP8
	{//��������� ������ ������
	    CP[playerid] = CP_WOODSMAN_3;
	    //�� ���������
		SetPlayerCheckpointEx(playerid, SBizInfo[56][sbEntranceX],SBizInfo[56][sbEntranceY],SBizInfo[56][sbEntranceZ], 3.0);
		checktimedeliver[playerid] = GetTickCount();
		format(strings, sizeof(strings), "��� �������� ������� ��� �� %d ������ � ��� ��������� �����.", MinTimeCheckpoint[playerid]/1000);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
    }
    else
    {
        new rand = random(sizeof(aRandomWoodsman));
        SetPVarInt(playerid, "Random", rand);
        CP[playerid] = CP_WOODSMAN_2;
        //�� ������ ������
        SetPlayerCheckpointEx(playerid, aRandomWoodsman[rand][0],aRandomWoodsman[rand][1],aRandomWoodsman[rand][2], 1.0);
	    SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������������� �� ����� ��������� �� ������!");
    }
	return 1;
}

stock OnPlayerKeyCheckWood(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_HANDBRAKE))
	{//��� ������� ���
	 	if(PlayerInfo[playerid][pJob] != WOODSMAN) return 1;
	 	if(WoodsmanLoading[playerid] == false) return 1;
		//if(nCarID[playerid] == 0 || nCarModel[playerid] != 578) { SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������ � DFT-30(������: 578)!!"); return 1; }

		new carid = LastCar[playerid];
		new modelid;
		if(carid > 0) modelid = GetVehicleModel(carid);
		if(modelid != 578) { SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������ � DFT-30(������: 578)!!"); return 1; }

	    new Float:vehx, Float:vehy, Float:vehz;
        GetVehiclePos(LastCar[playerid], vehx, vehy, vehz);
  		new Float: size_X, Float: size_Y, Float: size_Z;
  		//GetVehicleSize(modelID, size_X, size_Y, size_Z);
		GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, size_X, size_Y, size_Z);
		//format(strings, sizeof(strings), "GetVehicleInfo(%d, %.4f, %.4f, %.4f)", vehicleid, size_X, size_Y, size_Z);
		//SendClientMessage(playerid, COLOR_GREEN, strings);
		if(!IsPlayerInRangeOfPoint(playerid, size_Y/2.0, vehx, vehy, vehz)) return 1;

        JobAmmount[playerid]++;
		new strtmp[16+1];
	    format(strtmp, sizeof(strtmp), "~w~%d ~y~/~r~%d", JobAmmount[playerid], 3);
	    GameTextForPlayerEx(playerid, strtmp, 2000, 4);

        if(IsPlayerAttachedObjectSlotUsed(playerid, OBJECT_SLOT)) RemovePlayerAttachedObject(playerid, OBJECT_SLOT);

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        //ApplyAnimation(playerid, "PED","IDLE_tired",4.1,1,0,0,0,2500);

        if(JobAmmount[playerid] == 1)//��� ���������� STEP6
        {//��������� �� ������� ������ ������
	        Wood1[carid] = CreateObjectEx(684, 0.0,0.0,0.0, 0.0,0.0,0.0);
	        AttachObjectToVehicleEx(Wood1[carid], carid, -0.5,-1.7,0.2, 0.0,0.0,0.0);
			new rand = GetPVarInt(playerid, "Random");
		    CP[playerid] = CP_WOODSMAN_2;
		    //�� ������ ������
			SetPlayerCheckpointEx(playerid, aRandomWoodsman[rand][0],aRandomWoodsman[rand][1],aRandomWoodsman[rand][2], 1.0);
	        SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}��������� ������!");
        }
        else if(JobAmmount[playerid] == 2)//��� ���������� STEP7
        {//��������� ������ ������
	        Wood2[carid] = CreateObjectEx(684, 0.0,0.0,0.0, 0.0,0.0,0.0);
	        AttachObjectToVehicleEx(Wood2[carid], carid, 0.5,-1.7,0.2, 0.0,0.0,0.0);
			new rand = GetPVarInt(playerid, "Random");
		    CP[playerid] = CP_WOODSMAN_2;
		    //�� ������ ������
			SetPlayerCheckpointEx(playerid, aRandomWoodsman[rand][0],aRandomWoodsman[rand][1],aRandomWoodsman[rand][2], 1.0);
	        SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}��������� ������!!");
        }
        else if(JobAmmount[playerid] == 3)//��� ���������� STEP8
		{//��������� ������ ������
	        Wood3[carid] = CreateObjectEx(684, 0.0,0.0,0.0, 0.0,0.0,0.0);
	        AttachObjectToVehicleEx(Wood3[carid], carid, 0.0,-1.7,0.8, 0.0,0.0,0.0);

			/*CP[playerid] = CP_WOODSMAN_3;
		    //�� ���������
			SetPlayerCheckpointEx(playerid, SBizInfo[56][sbEntranceX],SBizInfo[56][sbEntranceY],SBizInfo[56][sbEntranceZ], 3.0);

			checktimedeliver[playerid] = GetTickCount();
			format(strings, sizeof(strings), "��� �������� ������� ��� �� %d ������ � ��� ��������� �����.", MinTimeCheckpoint[playerid]/1000);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);*/

	        SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� ��������� ����������� ���������� ������. ������������� �� ���������.");
	    }
		WoodsmanLoading[playerid] = false;
		if(KEYSTATE == 1)
		{
			format(strings, sizeof(strings), "OnPlayerKeyCheckWood(newkeys:%d, oldkeys:%d)", newkeys, oldkeys);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
	}
	return 1;
}

stock woodsman_OnEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pJob] != WOODSMAN) return 1;
//��� ���������� ������
	if(CP[playerid] == CP_WOODSMAN_2)//��� ���������� STEP4
	{
 	 	if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ���������� �� ���� ������������� �������� !");
		    return 1;
		}
        DisablePlayerCheckpointEx(playerid);
        new rand = GetPVarInt(playerid, "Random");
        SetPlayerFacingAngle(playerid, aRandomWoodsman[rand][3]);
        
        
		ClearAnimations(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ApplyAnimation(playerid, "CHAINSAW","CSAW_PART",4.1,1,0,0,1,6000);//������ �� 6 ������
       	GivePlayerWeaponEx(playerid, 9, 1);//��� ����

		SetTimerEx("Woodsman_Timer", 5000, 0, "i", playerid);
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.7 ", GetTickCount(), timers);
	}
	else if(CP[playerid] == CP_WOODSMAN_3)//��� ���������� STEP9
	{
		if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER || nCarModel[playerid] != 578)
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� ������ ��������� �� ���� �������� DFT-30(������: 578)!");
		    return 1;
		}
		/*if(GetTickCount() < (checktimedeliver[playerid]+MinTimeCheckpoint[playerid]) && !gAnticheat[playerid])
		{
			format(strings, sizeof(strings), "%s[%d] Reset WoodSkill:%d Mats:%d checktimedeliver:%d[%d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pWoodSkill], JobAmmount[playerid],
				(GetTickCount()-checktimedeliver[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
			Log(JOB, strings);
			PlayerInfo[playerid][pWoodSkill] = 0;
			JobAmmount[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, strings);
		    return 1;
		}*/
		//format(strings, sizeof(strings), "%s[%d] WoodSkill:%d checktimedeliver:%d sec",
		//	PlayerName(playerid),playerid, PlayerInfo[playerid][pWoodSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
		//Log(JOB, strings);

		new skill;
		new level = PlayerInfo[playerid][pWoodSkill];
		if(level < 50) { skill = 50; /*money = 100 + random(100); PlayerInfo[playerid][pCarTime] = 600;*/}
		else if(level >= 50 && level < 100) { skill = 60; /*money = 200 + random(100); PlayerInfo[playerid][pCarTime] = 540;*/}
		else if(level >= 100 && level < 200) { skill = 75; /*money = 300 + random(100); PlayerInfo[playerid][pCarTime] = 480;*/}
		else if(level >= 200 && level < 400) { skill = 90; /*money = 400 + random(100); PlayerInfo[playerid][pCarTime] = 420;*/}
		else if(level >= 400) { skill = 100; /*money = RANDMONEY5; PlayerInfo[playerid][pCarTime] = 360;*/}

 		new Float: price = compcost*(100+SBizInfo[56][sbBuyProd])/100.0;//10*(100.0+1)/100.0�=�10.1
 		//new price = SBizInfo[56][sbSalary];
//printf("compcost(%d)*(100.0+%d)/100.0 = %f", compcost, SBizInfo[56][sbBuyPrice], price);
		new money = floatround(skill*price, floatround_floor);// + SBizInfo[56][sbSalary];//3*100*10.1 + 10�=�3040
//printf("JobAmmount(%d)*10.0*price(%f) + sbSalary(%d) = %d", JobAmmount[playerid], price, SBizInfo[56][sbSalary], money);
		if(SBizInfo[56][sbTill] > money)
		{
			PlayerInfo[playerid][pWoodSkill] ++;
			if(PlayerInfo[playerid][pWoodSkill] == 50)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* ���� ����� �������� ������ ������ 2."); }
			else if(PlayerInfo[playerid][pWoodSkill] == 100)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* ���� ����� �������� ������ ������ 3."); }
			else if(PlayerInfo[playerid][pWoodSkill] == 200)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* ���� ����� �������� ������ ������ 4."); }
			else if(PlayerInfo[playerid][pWoodSkill] == 400)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* ���� ����� �������� ������ ������ 5."); }

			SBizInfo[56][sbProducts] += skill;
			SBizInfo[56][sbTill] -= money;
			SBizInfo[56][sbImport] += money;
			GivePlayerMoneyB(fsbiz+56, playerid, money); ///�������� �� ���� ������ �����
			//UpdateSawmill();

	        format(strings, sizeof(strings), "������������: {0080FF}�� ��������� {FFFFFF}%d{0080FF} ��������� �� ��������� � �������� �� ��� {33AA33}$%d.", JobAmmount[playerid]*100, money);
	        SendClientMessage(playerid, COLOR_GREEN, strings);

	        new rand = random(sizeof(aRandomWoodsman));
	        SetPVarInt(playerid, "Random", rand);
	        CP[playerid] = CP_WOODSMAN_2;
	        SetPlayerCheckpointEx(playerid, aRandomWoodsman[rand][0],aRandomWoodsman[rand][1],aRandomWoodsman[rand][2], 1.0);
	   		SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������������� �� ����� ��������� �� ������!!");
        }
        else
        {
			DisablePlayerCheckpointEx(playerid);
      		SendClientMessage(playerid, COLOR_GREY, "   ��������, � ����� ��� ������ �����.");
       		SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������������� � ����������, ����� �������� ������ (USE: /gps 1050)");
        }
		JobAmmount[playerid] = 0;//������ 3 ������
        if( IsValidObjectEx(Wood1[nCarID[playerid]]) ) DestroyObjectEx(Wood1[nCarID[playerid]], 8);
        if( IsValidObjectEx(Wood2[nCarID[playerid]]) ) DestroyObjectEx(Wood2[nCarID[playerid]], 8);
        if( IsValidObjectEx(Wood3[nCarID[playerid]]) ) DestroyObjectEx(Wood3[nCarID[playerid]], 8);
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.7 ", GetTickCount(), timers);
	}
	return 1;
//��� ���������� �����
}

//��� ���������� STEP5
forward Woodsman_Timer(playerid);
public Woodsman_Timer(playerid)
{
    ResetPlayerWeaponsEx(playerid);
   	SetPlayerAttachedObjectEx(playerid, OBJECT_SLOT, 684, Spine, 0.1259,0.3600,0.0, -87.0,0.0,0.0, 0.4,0.4,0.4);
   	PlaySoundForPlayer(playerid, 32201);//�����

    ClearAnimations(playerid);
  	//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);//������� ��������
   	//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,1,0,0,1,1);
   	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

   	SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}��������� ������ �� �������� (USE: "#KEY_FOOT_AIM_WEAPON").");
   	GameTextForPlayerEx(playerid, "~g~USE: ~y~~k~~PED_LOCK_TARGET~", 5000, 1);//� 5 ����� �� �������� ������ �������
	WoodsmanLoading[playerid] = true;
    return 1;
}
