
new robcountdown[MAX_PLAYERS];

stock carjacker_OnPlayerPickUp(playerid, pickupid)
{
	#pragma unused pickupid
	if( IsPlayerInRangeOfPoint(playerid, 2.1, 2259.0122,-70.9235,31.6016) )
	{	//��� ������������� STEP1 ��������� �������
		if(PlayerInfo[playerid][pJob] == CARJACKER && MatsHolding[playerid] == 0)
		{	//factory production Material
			//GameTextForPlayerEx(playerid, "~y~Welcome to the ~n~Factory~n~~b~Use (~w~/materials get~b~)~n~~g~to take a Materials Packages", 5000, 3);
			new level = PlayerInfo[playerid][pJackSkill];
			new package;//��� ���������
			if(level < 50) { package = 30; }
			else if(level >= 50 && level < 100) { package = 34; }
			else if(level >= 100 && level < 200) { package = 37; }
			else if(level >= 200 && level < 400) { package = 39; }
			else if(level >= 400) { package = 40; }

			//new price = package * pricepackage;//���� �������
			//���� ������� 25*100=$2500 �� amountmaterials*package = 50*10=1250 ���-�� �������

			//amountmaterials*package - ���-�� ������� � �������
			//50*30=1500 ���������� �� 1 �����
			//50*10=500 ������� �� 5 �����

			//pricepackage*package  - ���� �������
			//100*30=$3000 - ���� ������� �� 1 �����
			//100*10=$1000 - ���� ������� �� 5 �����

			//12 - ���-�� ������ �� ���
			//pricepackage/amountmaterials=100/50=2
			//(1.0+1/(10.0))*2*1500 = 3300 - 3000 = 300*12 - 1500(�� �������) = 2100 �� � ��� �� 1 �����
			//(1.0+5/(10.0))*2*500 = 1500 - 1000 = 500*12 - 1500(�� �������) = 4500 �� � ��� �� 5 �����
			//new price = floatround((1+skill/(10.0))*pricematerials*PlayerInfo[playerid][pMats]);


			//if(GetPlayerMoneyH(playerid) > price)
			//{
		    //GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, -price);
		    //format(strings, sizeof(strings), "* �� ������ %d ������� � ����������� �� $%d.", package, price);
		    //SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

		    format(strings, sizeof(strings), "* �� �������� %d ������� � �����������.", package);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

			checktimedeliver[playerid] = GetTickCount();
		    format(strings, sizeof(strings), "��� �������� ������� ��� �� %d ������ � ��� ��������� �����.", MinTimeCheckpoint[playerid]/1000);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

		    //SBizInfo[9][sbTill] += price/2;//����������� ������ � ��� General Store �� ������� ������� �������������
		    //BizInfo[0][bProducts] += price/2;//����������� ������ � ����
		    MatsHolding[playerid] = package;
			//GameTextForPlayerEx(playerid, "~w~Welcome to the ~~y~Factory~n~~g~You have got 10 Packages a Material", 5000, 3);
		}
		//return 1;
	}
	else if( IsPlayerInRangeOfPoint(playerid, 2.1, 1489.18,-1720.06,8.24) )
	{   //��� ������������� STEP2 ��������� �������
		if(PlayerInfo[playerid][pJob] == CARJACKER)
		{
	        if(MatsHolding[playerid] > 0)
	        {
		        //�� ����� ��� ������������ 1 ��� 58 ��� //������������� 487  � 462 ������������ 75 ������
   				//if(PlayerInfo[playerid][pCarTime] > 0) { PlayerInfo[playerid][pJackSkill] = 0; }
   				if(GetTickCount() < (checktimedeliver[playerid]+75000) && !gAnticheat[playerid])
  				{
					format(strings, sizeof(strings), "%s[%d] Reset JackSkill:%d Mats:%d checktimedeliver:%d[%d] sec",
						PlayerName(playerid),playerid, PlayerInfo[playerid][pJackSkill], PlayerInfo[playerid][pMats], (GetTickCount()-checktimedeliver[playerid])/1000, 75);
					Log(JOB, strings);
					PlayerInfo[playerid][pJackSkill] = 0;
					PlayerInfo[playerid][pMats] = 0;
					MatsHolding[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, strings);
					return 1;
				}
				//format(strings, sizeof(strings), "%s[%d] JackSkill:%d checktimedeliver:%d sec",
				//	PlayerName(playerid),playerid, PlayerInfo[playerid][pJackSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
				//Log(JOB, strings);
//���� ����� ��������� ������ ��� �� 120 ������, �.�. 120 ������ ��� �� ������, � �� ��� ����� �� �����, �� �������� ����, �.�. ��� �����
		        //PlayerInfo[playerid][pCarTime] = 2*45*2;//��� ����� ������� �� 240 ������

	            new payout = amountmaterials*MatsHolding[playerid];//new amountmaterials = 30;
	            format(strings, sizeof(strings), "* ����� ������� ��� %d ������� �� %d ������������ ������� � �����������.", payout, MatsHolding[playerid]);
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	            PlayerInfo[playerid][pMats] += payout;
	            MatsHolding[playerid] = 0;

				PlayerInfo[playerid][pJackSkill] += 1;//floatround(PlayerInfo[playerid][pMats]/10.0);
				if(PlayerInfo[playerid][pJackSkill] == 50)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ������������ ������ ������ 2, �� ������ ������ ������ ������� � �������."); }
				else if(PlayerInfo[playerid][pJackSkill] == 100)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ������������ ������ ������ 3, �� ������ ������ ������ ������� � �������."); }
				else if(PlayerInfo[playerid][pJackSkill] == 200)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ������������ ������ ������ 4, �� ������ ������ ������ ������� � �������."); }
				else if(PlayerInfo[playerid][pJackSkill] == 400)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ������������ ������ ������ 5, �� ������ ������ ������ ������� � �������."); }
	        }
	        else SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ������ ������� � ����������� !");
 			GameTextForPlayerEx(playerid, "~w~Welcome to the ~y~SkeletonKey Plant~n~~g~You have got Material for SkeletonKey", 5000, 3);
		}

	}
	return 1;
}

forward RobCountdown(playerid, vehicleid);
public RobCountdown(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == CARJACKER)
	{
		if(CurState[playerid] != PLAYER_STATE_ONFOOT)
		{ KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1; robcountdown[playerid] = 0; return 1; }

		robcountdown[playerid] ++;
		if(robcountdown[playerid] >= 60)
		{
			robcountdown[playerid] = 0;
			KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1;//� ����� �������
			RemovePlayerAttachedObject(playerid, BAG_SLOT);
			ClearAnimations(playerid);
			GameTextForPlayerEx(playerid, "~w~Vehicle ~g~Unlocked", 5000, 6);
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			UnLockCar(vehicleid);
		}
		else SetPlayerGameTextScale(playerid, "ROBBERY", robcountdown[playerid], 60);
	}
	else //if(PlayerInfo[playerid][pJob] != CARJACKER)
	{
		if(CurState[playerid] != PLAYER_STATE_ONFOOT)
		{ KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1; robcountdown[playerid] = 0; return 1; }

		robcountdown[playerid] ++;
		if(robcountdown[playerid] >= 10)
		{
			robcountdown[playerid] = 0;
			KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1;//� ����� �������
			//RemovePlayerAttachedObject(playerid, BAG_SLOT);
			ClearAnimations(playerid);
			GameTextForPlayerEx(playerid, "~w~Detach Trailer ~g~From Vehicle", 5000, 6);
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//==================================================================
//format(strings, sizeof(strings), "IsTrailerAttach[trailerid:%d]: %d", SurfingVehicleID, IsTrailerAttach[SurfingVehicleID]);//, PlayerName(playerid)
//SendClientMessage(playerid, -1, strings);
			//if(IsTrailerAttach[SurfingVehicleID] != 0)
			if(IsTrailerAttachedToVehicle(vehicleid))
			{
				if(gLoading[LastDriver[vehicleid]]) { return 1; }//�� �������� ���� �����������
				if(gUnLoading[LastDriver[vehicleid]]) { return 1; }//�� �������� ���� ������������

				DetachTrailerFromVehicleEx(vehicleid);
				//SendClientMessage(playerid, COLOR_GREY, "DetachTrailerFromVehicleEx");
				//gTrailerAttached[playerid] = 0;
				//nTrailerID[playerid] = 0;
				//nTrailerModel[playerid] = 0;
				//DeletePVar(playerid, "VehicleID");
//format(strings, sizeof(strings), "DetachTrailerFromVehicleEx(%d)",  SurfingVehicleID);//, PlayerName(playerid)
//SendClientMessage(playerid, -1, strings);
			}
		}
		else SetPlayerGameTextScale(playerid, "ROBBERY", robcountdown[playerid], 10);
	}
	return 1;
}
