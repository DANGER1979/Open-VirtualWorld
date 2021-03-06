//�������� ����

#define MAX_SPIKESTRIPS 30
enum sInfo
{
    sObject,
    Float:sX,
    Float:sY,
    Float:sZ,
	sCreated
};
new SpikeInfo[MAX_SPIKESTRIPS][sInfo];//������ ����������� ����� �������� ��� �������� �������


//������ ���������� ����� �� �������, ����� �� ������
enum ss_info
{
	bool: oShow,//false -���� ������ �������� � �������� ����,true - ���� ������ ����� ���������� ��� ������� ����
	oModel,
	Float:oX,
	Float:oY,
	Float:oZ,
	Float:orX,
	Float:orY,
	Float:orZ
}
new SaticSpikeInfo[14][ss_info] = {//77	//32//32	//134
{true, 2899, -1020.73,932.05,33.67, 0.00,0.00,34.00},//166
{true, 2899, -1024.17,937.36,33.67, 0.00,0.00,34.00},
{true, 2899, -1021.53,933.34,33.67, 0.00,0.00,34.00},
{true, 2899, -1937.14,216.32,24.25, 0.00,0.00,82.00},
{true, 2899, -1943.51,217.18,24.26, 0.00,0.00,82.00},
{true, 2899, -1938.80,216.47,24.26, 0.00,0.00,82.00},
{true, 2899, 93.41,-1026.90,21.06, 0.00,0.00,0.00},
{true, 2899, 93.68,-1017.29,21.06, 0.00,0.00,0.00},
{true, 2899, 93.54,-1022.11,21.06, 0.00,0.00,0.00},
{true, 2899, 2769.42,415.55,7.48, 0.00,0.00,90.00},
{true, 2899, 2764.57,415.54,7.48, 0.00,0.00,90.00},
{true, 2899, -483.35,1220.03,28.56, 0.00,0.00,11.00},
{true, 2899, -481.58,1210.45,28.56, 0.00,0.00,11.00},
{true, 2899, -482.49,1215.27,28.56, 0.00,0.00,11.00}//179
};

//������� ����������� �����
enum damage_info
{
	flpanel,
	frpanel,
	rlpanel,
	rrpanel,
	windshields,
	fbumper,
	rbumper,
	fbonnet,
	rboot,
	door0,
	door1,
	door2,
	door3,
	fllight,
	brlight2,
	frlight,
	brlight4,
	rrtire,
	frtire,
	rltire,
	fltire
};
new DamageStatus[MAX_VEHICLES+1][damage_info];

stock spike_OnGameModeInit()///�������� ���������� ��������
{
	for(new ss=0; ss<14; ss++)
	{
		CreateDynamicObject(SaticSpikeInfo[o][oModel],SaticSpikeInfo[o][oX],SaticSpikeInfo[o][oY],SaticSpikeInfo[o][oZ],
							SaticSpikeInfo[o][orX],SaticSpikeInfo[o][orY],SaticSpikeInfo[o][orZ], 0, 0, -1, 300.0, 300.0);
		idx[o]++;
	}
}

stock spike_OnPlayerUpdate(playerid, newstate)//��� ���������� ����
{   //���������� �� OnPlayerUpdate
	//if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	if(IsInPlane(nCarID[playerid])) return 1;
	if(IsInBoat(nCarID[playerid])) return 1;

	
	for(new st = 0; st < 14; st++)//���� �� �������
	{
		if(!IsVehicleInRangeOfPoint(nCarID[playerid], 5.0,
			SaticSpikeInfo[st][oX],
			SaticSpikeInfo[st][oY],
			SaticSpikeInfo[st][oZ])) continue;
		//if(SpikeInfo[st][sCreated] != 1) continue;
		//CrashDetected[playerid] = 1162;

		new panel, door, light, tire;
		GetVehicleDamageStatus(nCarID[playerid], panel, door, light, tire);//�������� ������ � ������������:
		DamageStatus[nCarID[playerid]][frtire] = 1;
		DamageStatus[nCarID[playerid]][fltire] = 1;
		DamageStatus[nCarID[playerid]][rrtire] = 1;
		DamageStatus[nCarID[playerid]][rltire] = 1;
		tire = encode_tires(	DamageStatus[nCarID[playerid]][rrtire],
								DamageStatus[nCarID[playerid]][frtire],
								DamageStatus[nCarID[playerid]][rltire],
								DamageStatus[nCarID[playerid]][fltire]);
		VehInfo[nCarID[playerid]][DamageTires] = tire;
		UpdateVehicleDamageStatus(nCarID[playerid], panel, door, light, tire);//�������� ����������� ����������:
		break;
	}
	for(new st = 0; st < sizeof(SpikeInfo); st++)//���� ������������ �� �������
	{
		if(!IsVehicleInRangeOfPoint(nCarID[playerid], 2.5,
			SpikeInfo[st][sX],
			SpikeInfo[st][sY],
			SpikeInfo[st][sZ])) continue;
		if(SpikeInfo[st][sCreated] != 1) continue;
		//CrashDetected[playerid] = 1161;

		new panel, door, light, tire;
		GetVehicleDamageStatus(nCarID[playerid], panel, door, light, tire);//�������� ������ � ������������:
		DamageStatus[nCarID[playerid]][frtire] = 1;
		DamageStatus[nCarID[playerid]][fltire] = 1;
		DamageStatus[nCarID[playerid]][rrtire] = 1;
		DamageStatus[nCarID[playerid]][rltire] = 1;
		tire = encode_tires(	DamageStatus[nCarID[playerid]][rrtire],
								DamageStatus[nCarID[playerid]][frtire],
								DamageStatus[nCarID[playerid]][rltire],
								DamageStatus[nCarID[playerid]][fltire]);
		VehInfo[nCarID[playerid]][DamageTires] = tire;
		UpdateVehicleDamageStatus(nCarID[playerid], panel, door, light, tire);//�������� ����������� ����������:
		break;
	}
	return 1;
}


stock spike_OnPlayerKeyState_UP(playerid)
{
		if(!IsACop(playerid)) return 1;
	    if(gOnDuty[playerid] != 1)
	    {
	        //SendClientMessage(playerid, COLOR_GREY, "   �� - �� �� ��������� !");
	       	return 1;
	    }
		if(PlayerInfo[playerid][pRank] < 4)
		{
			SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ���� 4, ����� ������������� �������� ���� !");
			return 1;
		}
		if( !IsInCopCar(nCarID[playerid]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� �� ���� ���������� ������������� �������� !");
			return 1;
		}
		if( IsInPlane(nCarID[playerid]) || IsInBoat(nCarID[playerid]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� ������ ���������� � ������ !");
			return 1;
		}
		if(IsPlayerInArea(playerid, specialzone[0]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   � ���� ����� ��������� ��������� ����� !");
			return 1;
		}
		//��� �����
	    //new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
        //GetPlayerPos(playerid, plocx, plocy, plocz);
        //GetPlayerFacingAngle(playerid, ploca);
		new Float:x,Float:y,Float:z, Float:rotX,Float:rotY,Float:rotZ, Float:angle;
		GetVehiclePos(nCarID[playerid], x, y, z);
		GetVehicleZAngle(nCarID[playerid], angle);
		//GetVehicleRotation(nCarID[playerid], rotZ, rotX, rotY);
		GetVehicleRotation(nCarID[playerid], rotX, rotY, rotZ);

		GetXYZInrear(3.5, angle, rotY, x, y, z);
		//��������������
		//format(strings, sizeof(strings), "GetXYZInrear(3.5, angle:%.0f, pitch:%.0f, x:%.0f, y:%.1f, z:%.1f)", angle, rotY, x, y, z);
		//ABroadCast(COLOR_RED, strings, 1);
		//SendClientMessageToAll(COLOR_YELLOW, "��������");

		//pStinger[stCounter] = CreateObjectEx(1593, x, y, z-0.65, 0.0, 0.0, A-90.0);
		//GetObjectPos(pStinger[stCounter],Stinger[stCounter][objX],Stinger[stCounter][objY],Stinger[stCounter][objZ]);
		for(new st = 0; st < sizeof(SpikeInfo); st++)
		{
			if(SpikeInfo[st][sCreated] == 0)
			{
				SpikeInfo[st][sCreated] = 1;
				SpikeInfo[st][sX] = x;
				SpikeInfo[st][sY] = y;
				SpikeInfo[st][sZ] = z-0.6;//0.65
				//��������������
				//format(strings, sizeof(strings), "CreateObjectEx(2899, x:%.0f, y:%.0f, z:%.0f, rotX:%.1f, rotY:%.1f, rotZ:%.1f, 200.0)", x, y, z-0.6, rotX, rotY, angle-90.0);
				//ABroadCast(COLOR_RED, strings, 1);
				//SendClientMessageToAll(COLOR_YELLOW, "��������");
				SpikeInfo[st][sObject] = CreateObjectEx(2899, x, y, z-0.6, rotX, rotY, angle-90.0);//angle-90.0
				break;
			}
		}
		return 1;
}
	
stock spike_OnPlayerKeyState_DOWN(playerid)
{
		if(!IsACop(playerid)) return 1;
	    if(gOnDuty[playerid] != 1)
	    {
	        //SendClientMessage(playerid, COLOR_GREY, "   �� - �� �� ��������� !");
	       	return 1;
	    }
		if( !IsInCopCar(nCarID[playerid]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� �� ���� ���������� ������������� �������� !");
			return 1;
		}
		if( IsInPlane(nCarID[playerid]) || IsInBoat(nCarID[playerid]) )
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� ������ ���������� � ������ !");
			return 1;
		}
	    for(new st = 0; st < sizeof(SpikeInfo); st++)
	  	{
	  	    if(!IsPlayerInRangeOfPoint(playerid, 30.0, SpikeInfo[st][sX], SpikeInfo[st][sY], SpikeInfo[st][sZ])) continue;
  	        if(SpikeInfo[st][sCreated] != 1) continue;
			SpikeInfo[st][sCreated] = 0;
			SpikeInfo[st][sX] = 0.0;
			SpikeInfo[st][sY] = 0.0;
			SpikeInfo[st][sZ] = 0.0;
			DestroyObjectEx(SpikeInfo[st][sObject], 7);
			//return 1;//����� ��������� ��� ���� �����
	  	}
		return 1;
}

