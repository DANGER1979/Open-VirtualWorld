stock npc_OnPlayerEnterVehicle(playerid, vehicleid)
{
//��� ������� ������ �� ����������� �����
	new modelid = GetVehicleModel(vehicleid);
	if( IsInNPCVehicle(vehicleid) )
	{   //���� ��� ��� //577, "AT-400", //453, "Reefer"	//473, "Dinghy"
		for(new seat=2; seat<500; seat++)//500 � ���������
		{   //VehicleArray[modelid-400][SeatID]-1
		    if(GetSeatVehiclePlayer(vehicleid, seat) == INVALID_PLAYER_ID &&
				seat > (VehicleArray[modelid-400][SeatID]-1))
		    {   //���� ��������� ����� ������, �� ������ �� �����������
				//format(strings, sizeof(strings), "GetSeatVehiclePlayer: %d, Seat: %d", GetSeatVehiclePlayer(vehicleid, seat), seat);
				//ABroadCast(COLOR_GREEN, strings, 9);
	    		PutPlayerInVehicleEx(playerid, vehicleid, seat);
    			break;
		    }
	    }
	}
}


stock npc_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	//if(IsKeyJustDown(KEY_ANALOG_UP,newkeys,oldkeys))//num8
	if( PRESSED(KEY_ANALOG_UP))
	{	//~k~~VEHICLE_TURRETUP~
//��� ������ ����� ������
		// Start recording vehicle data (/vrecord recording_name[])
		// Find the recording_name[] file in /scriptfiles/
		if(PlayerInfo[playerid][pAdmin] == 9 && PlayerInfo[playerid][pJob] != ROADWORKER && PlayerInfo[playerid][pJob] != CARMECHANIC && PlayerInfo[playerid][pJob] != TRUCKER)
		{
	        static npc_counter;//�������
			npc_counter ++;
	        if(CurState[playerid] == PLAYER_STATE_DRIVER)
		    {
			    //new vrecord[512] = "mynpc";
				format(strings, sizeof(strings), "%s[%d] - %d", VehicleArray[nCarModel[playerid]-400][Vehicle_Name], nCarID[playerid], npc_counter);//, PlayerName(playerid)
				StartRecordingPlayerData(playerid, PLAYER_RECORDING_TYPE_DRIVER,strings);
				format(strings, sizeof(strings), "Recording: %s.rec. Started NPC in vehicle.", strings);//, PlayerName(playerid)
				SendClientMessage(playerid, 0xFF0000FF,strings);
				return 1;
			}
		 	else if(CurState[playerid] == PLAYER_STATE_ONFOOT)
			{
			    //new ofrecord[512] = "mynpc";
				format(strings, sizeof(strings), "%s - %d", PlayerName(playerid), npc_counter);//,
				StartRecordingPlayerData(playerid, PLAYER_RECORDING_TYPE_ONFOOT,strings);
				format(strings, sizeof(strings), "Recording: %s.rec. Started NPC on foot.", strings);//, PlayerName(playerid)
				SendClientMessage(playerid, 0xFF0000FF,strings);
				return 1;
			}
		}
//��� ������ ����� �����
		//return 1;
	}
//==============================================================================
	//if(IsKeyJustDown(KEY_ANALOG_DOWN,newkeys,oldkeys))
	else if( PRESSED(KEY_ANALOG_DOWN) )
	{	//~k~~VEHICLE_TURRETDOWN~
//��� ������ ����� ������

		if(PlayerInfo[playerid][pAdmin] == 9 && PlayerInfo[playerid][pJob] != ROADWORKER && PlayerInfo[playerid][pJob] != CARMECHANIC && PlayerInfo[playerid][pJob] != TRUCKER)
		{   // Stop recording any data
			StopRecordingPlayerData(playerid);
			SendClientMessage(playerid, 0xFF0000FF, "Recording stopped.");
		}
//��� ������ ����� �����
		//return 1;
	}
	return 1;
}

stock npc_OnPlayerExitVehicle(playerid)
{
	if( IsInNPCVehicle(vehicleid) && CheckInCar[playerid] == 2)//��� ������ �� ����� � ������������ �����
	{   //���� ��� ��� � �� ������ �� �����
		new modelid = GetVehicleModel(vehicleid);
   		if(GetPlayerVehicleSeat(playerid) > VehicleArray[modelid-400][SeatID]-1 &&
		   VehicleArray[modelid-400][SeatID] >= 2)
   		{
   			PutPlayerInVehicleEx(playerid, vehicleid, 1);
   			RemovePlayerFromVehicleEx(playerid);
   			SetCameraBehindPlayer(playerid);
		}
	}
}
