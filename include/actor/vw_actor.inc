new sync_anim;

new crage_actor;
new Text3D:crage_text;

new duglas_actor;
new Text3D:duglas_text;

new narko_actor;
new Text3D:narko_actor_text;

//new william_actor;

new ActAvtosalon;
new Text3D: ActAvtosalon_Text;

new ActLIC;
new Text3D: ActLIC_Text;

new ActLSPD;
new Text3D: ActLSPD_Text;

new ActLSPDVN;
new Text3D: ActLSPDVN_Text;

new ActLSPDVN2;
new Text3D: ActLSPDVN2_Text;

#define	MAX_ACTOR MAX_BIZ
new ActorID[MAX_ACTOR];
new Text3D: Text_Actor[MAX_ACTOR];

new NarkInfoCash[MAX_PLAYERS];

enum actor_info
{
	acID,
	//acSkin,
	Float:acX,
	Float:acY,
	Float:acZ,
	//Float:acA
	Float:acVW
}
new ActorsY[MAX_ACTORS][actor_info];


//������ ������ ������ ����� �������� �������
stock actor_OnGameModeInit()
{
	new time = GetTickCount();

	crage_text = duglas_text = narko_actor_text = Text3D:-1;
	
    Create3DTextLabelEx("����� �������\n�������{FF0000} Y{FFFFFF}",-1, 1401.7637,-3.6995,1000.9169, 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, -1);//����� �� ����� ������ � LCN
    Create3DTextLabelEx("����� �������\n�������{FF0000} Y{FFFFFF}",-1, 1402.6674,-3.6663,1000.9169, 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, -1);
	Create3DTextLabelEx("[������]", -1, 1404.9845,-6.8920,1000.9169, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);//����� � ��������� ������ LCN

    Create3DTextLabelEx("[������]", -1, -2160.29883, 639.83508, 1055.68616,5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);//������ ����� � ��������� ������ Yakuza
    
 //------------------------------------------------------------------------------

    
    ActLIC = CreateDynamicActorExY("{EE66EE}�������� �����������{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 148, 1479.5929,-1747.3983,2106.1101,180.0, true, 100.0, DoJ);// ����� � �����
    ApplyDynamicActorAnimation(ActLIC, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);
	ActLIC_Text = Create3DTextLabelEx("", 0xFFFFFFFF, 1479.5929,-1747.3983,2106.1101+1, 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, DoJ);

    
//------------------------------------------------------------------------------
//����� ��� 3D ������
 	ActLSPD = CreateDynamicActor(300, 1543.8280,-1631.9215,13.3828,91.4747, true, 100.0, 0); ActorCounter ++;//�������� �� ���������
	ActLSPD_Text = Create3DTextLabelEx("", 0xFFFFFFFF,1543.8280,-1631.9215,13.3828+1.0, 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0, 0);

 	ActLSPDVN = CreateDynamicActor(281, 342.3164,-316.0239,1024.6853,177.8985, true, 100.0, POLICE_LS_WORLD, DoT); ActorCounter ++;//�������� ��������
	ActLSPDVN_Text = Create3DTextLabelEx("", 0xFFFFFFFF, 342.3164,-316.0239,1024.6853+1.0, 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, POLICE_LS_WORLD);
    ApplyDynamicActorAnimation(ActLSPDVN, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);
    //ActLSPDVN = CreateDynamicActorExY("{EE66EE}��������{FFFFFF}\n�������{FF0000} Y{FFFFFF} ��� ���������", 81,342.3164,-316.0239,1024.6853,177.8985, true, 100.0, POLICE_LS_WORLD, DoT);


 	ActLSPDVN2 = CreateDynamicActor(281, 322.3671,-312.5731,1024.6953,179.1870, true, 100.0, POLICE_LS_WORLD, DoT); ActorCounter ++;//������ ������
	ActLSPDVN2_Text = Create3DTextLabelEx("", 0xFFFFFFFF, 322.3671,-312.5731,1024.6953+1, 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0, POLICE_LS_WORLD);
	//Create3DTextLabelEx("������� {1EFF00}'Y' {FFFFFF}��� ��������������",0xFFFFFFFF, 322.2426,-313.8495,1024.6902, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1); // pd

	sync_anim = CreateDynamicActor(266, 336.1475,-314.0885,1024.6853,116.5610, true, 100.0, POLICE_LS_WORLD, DoT);  ActorCounter ++;  //����� � ���� ������� ������� �� ������
    //sync_anim = CreateDynamicActorExY("{EE66EE}��������{FFFFFF}\n�������{FF0000} Y{FFFFFF} ��� ���������", 266, 336.1475,-314.0885,1024.6853,116.5610, true, 100.0, POLICE_LS_WORLD, DoT);
    ApplyDynamicActorAnimation(sync_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);
	//Create3DTextLabelEx("������� {1EFF00}'Y' {FFFFFF}��� ��������������",0xFFFFFFFF, 342.3429,-317.8935,1024.6765, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,POLICE_LS_WORLD);
	

//------------------------------------------------------------------------------
//����� � ������������� 3D �������
    narko_actor = CreateDynamicActorExY("{EE66EE}������� �����{FFFFFF}\n�������{FF0000} Y{FFFFFF} ��� ���������",30, 325.6152,1124.7094,1083.8828,179.7101, true, 100.0, -1);
    duglas_actor = CreateDynamicActorExY("{EE66EE}���� �����{FFFFFF}\n�������{FF0000} Y{FFFFFF} ��� ���������",30, 312.3281,1123.9722,1083.8828,270.9613, true, 100.0, -1);
    crage_actor = CreateDynamicActorExY("{EE66EE}������� �����{FFFFFF}\n�������{FF0000} Y{FFFFFF} ��� ���������",29, -1211.7333,-1050.4645,128.2656,268.6740, true, 100.0, 0); // ����� �� ����� �������� �����
    //william_actor =
	CreateDynamicActorExY("{EE66EE}������{FFFFFF}\n�������{FF0000} Y{FFFFFF} ��� ���������",27, 2726.2383,-2417.5476,13.6480,5.1817, true, 100.0, 0); // ����� �� ��������� �� �����

	//sync_anim = CreateDynamicActorExY("\n\nLucy\n�������{FF0000} Y{FFFFFF} ��� ���������", 225, 2697.3318,-2438.1860,1013.7231,274.8445, true, 100.0, 81);// ����� �� ��������� � ���������
    //ApplyDynamicActorAnimation(sync_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);


    sync_anim = CreateDynamicActorExY("{EE66EE}MedicalCenter LS{FFFFFF}\n�������{FF0000} Y{FFFFFF}",308, -20.2510,1855.6536,17.6756,89.0879, true, 100.0, MCSA_LS_WORLD1, DoH);//����� � MedicalCenter LS


//������ � ��
    sync_anim = CreateDynamicActorExY("{EE66EE}������� ���� ���������{FFFFFF}\n�������{FF0000} Y{FFFFFF}",12, 1699.4147,855.6198,1008.4514,181.8802, true, 100.0, DoE);//����� � ��
    ApplyDynamicActorAnimation(sync_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    sync_anim = CreateDynamicActorExY("{EE66EE}������� ���� ��������{FFFFFF}\n�������{FF0000} Y{FFFFFF}",48, 1712.1937,848.8616,1008.4514,91.4708, true, 100.0, DoE);//����� � ��
    ApplyDynamicActorAnimation(sync_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    sync_anim = CreateDynamicActorExY("{EE66EE}������ ����� ���������{FFFFFF}\n�������{FF0000} Y{FFFFFF}",59, 1712.3378,858.2733,1008.4514,78.9139, true, 100.0, DoE);//����� � ��
    ApplyDynamicActorAnimation(sync_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

//������ � ����� 1040.9122
    new ap_anim;
    
	new line[64];
    line = "-1502.504272, 769.867492, 1039.890014, -28.000087"; new idx;//���������� ����� �������� ������ �� ������ �������
	new Array[4][MAX_STRING]; new Float: X, Float: Y, Float: Z, Float: Ang;
  	Array[0] = strtoko(line, idx, ',');   	X = floatstr(Array[0]);
  	Array[1] = strtoko(line, idx, ',');   	Y = floatstr(Array[1]);
   	Array[2] = strtoko(line, idx, ',');   	Z = floatstr(Array[2])+0.6;//1040.4899
  	Array[3] = strtoko(line, idx, ',');   	Ang = floatstr(Array[3])+180.0;	GetXYInFrontOfPoint(0.8, Ang, X,Y);
    ap_anim = CreateDynamicActorExY("{EE66EE}����� 1{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 11, X,Y,Z,Ang, false, 100.0, BANK_WORLD);// ����� � ����� 1
    ApplyDynamicActorAnimation(ap_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    line = "-1500.210571, 763.714172, 1039.890014, -79.399963"; idx = 0;
  	Array[0] = strtoko(line, idx, ','); 	X = floatstr(Array[0]);
	Array[1] = strtoko(line, idx, ',');  	Y = floatstr(Array[1]);
	Array[2] = strtoko(line, idx, ',');  	Z = floatstr(Array[2])+0.6;
	Array[3] = strtoko(line, idx, ',');  	Ang = floatstr(Array[3])+180.0; 	GetXYInFrontOfPoint(0.81, Ang, X,Y);
    ap_anim = CreateDynamicActorExY("{EE66EE}����� 2{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 172, X,Y,Z,Ang, false, 100.0, BANK_WORLD);// ����� � ����� 2
    ApplyDynamicActorAnimation(ap_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    line = "-1502.065307, 757.547546, 1039.890014, -129.900024"; idx = 0;
  	Array[0] = strtoko(line, idx, ','); 	X = floatstr(Array[0]);
	Array[1] = strtoko(line, idx, ',');  	Y = floatstr(Array[1]);
	Array[2] = strtoko(line, idx, ',');  	Z = floatstr(Array[2])+0.5;
	Array[3] = strtoko(line, idx, ',');  	Ang = floatstr(Array[3])+180.0; 	GetXYInFrontOfPoint(0.82, Ang, X,Y);
    ap_anim = CreateDynamicActorExY("{EE66EE}����� 3{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 194, X,Y,Z,Ang, false, 100.0, BANK_WORLD);// ����� � ����� 3
    ApplyDynamicActorAnimation(ap_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    line = "-1525.646118, 769.294189, 1039.890014, 50.099952"; idx = 0;
  	Array[0] = strtoko(line, idx, ','); 	X = floatstr(Array[0]);
	Array[1] = strtoko(line, idx, ',');  	Y = floatstr(Array[1]);
	Array[2] = strtoko(line, idx, ',');  	Z = floatstr(Array[2])+0.5;
	Array[3] = strtoko(line, idx, ',');  	Ang = floatstr(Array[3])+180.0; 	GetXYInFrontOfPoint(0.82, Ang, X,Y);
    ap_anim = CreateDynamicActorExY("{EE66EE}����� 4{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 194, X,Y,Z,Ang, false, 100.0, BANK_WORLD);// ����� � ����� 6
    ApplyDynamicActorAnimation(ap_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    line = "-1527.500854, 763.127502, 1039.890014, 100.599960"; idx = 0;
  	Array[0] = strtoko(line, idx, ','); 	X = floatstr(Array[0]);
	Array[1] = strtoko(line, idx, ',');  	Y = floatstr(Array[1]);
	Array[2] = strtoko(line, idx, ',');  	Z = floatstr(Array[2])+0.6;//+0.4
	Array[3] = strtoko(line, idx, ',');  	Ang = floatstr(Array[3])+180.0; 	GetXYInFrontOfPoint(0.7, Ang, X,Y);
    ap_anim = CreateDynamicActorExY("{EE66EE}����� 5{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 11, X,Y,Z,Ang, false, 100.0, BANK_WORLD);// ����� � ����� 5
    ApplyDynamicActorAnimation(ap_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

    line = "-1525.207153, 756.974304, 1039.890014, 151.999908"; idx = 0;
  	Array[0] = strtoko(line, idx, ','); 	X = floatstr(Array[0]);
	Array[1] = strtoko(line, idx, ',');  	Y = floatstr(Array[1]);
	Array[2] = strtoko(line, idx, ',');  	Z = floatstr(Array[2])+0.5;
	Array[3] = strtoko(line, idx, ',');  	Ang = floatstr(Array[3])+180.0; 	GetXYInFrontOfPoint(0.88, Ang, X,Y);
    ap_anim = CreateDynamicActorExY("{EE66EE}����� 6{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 172, X,Y,Z,Ang, false, 100.0, BANK_WORLD);// ����� � ����� 4
    ApplyDynamicActorAnimation(ap_anim, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

  	//new TutorialActor =
	CreateDynamicActorExY("{EE66EE}������{FFFFFF}\n������� {ff0000}Y {ffffff}��� ���������\n\n{724CA2}��������� ��������", 291, 1760.6124,-1882.3013,13.5850,91.1343, true, 100.0, 0);
	//Create3DTextLabelEx("������\n������� {ff0000}Y {ffffff}��� ���������\n\n{724CA2}��������� ��������",0xFFFFFFFF, 1760.6124,-1882.3013,13.5850, 10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0);
//------------------------------------------------------------------------------
//����� � ����������� 3D �������

 	//ActAvtosalon = CreateDynamicActor(15,-1664.8425,1206.2001,7.2546,327.5143, true, 100.0, 0);
	//ActAvtosalon_Text = Create3DTextLabelEx("", 0xFFFFFFFF, -1664.8425,1206.2001,7.2546+1, 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, 0);
	//Create3DTextLabelEx("������� {1EFF00}'Y' {FFFFFF}��� ��������������",0xFFFFFFFF, -1663.8074,1207.7589,7.2546, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);
    ActAvtosalon = CreateDynamicActorExY("{EE66EE}����������{FFFFFF}\n�������{FF0000} Y{FFFFFF}", 15, -1664.8425,1206.2001,7.2546,327.5143, true, 100.0, 0);

	printf("18/19. [�������� ������]: ���� ��������� - %d[%d], ��������� - %d (ms)", ActAvtosalon, ActorCounter, GetTickCount() - time);//new time = GetTickCount();
}

public OnPlayerTargetActor(playerid, newtarget, oldtarget)
{
    if (newtarget != INVALID_ACTOR_ID)
    {
        ApplyActorAnimation(newtarget, "PED", "handsup", 4.1, 0, 0, 0, 0, 0);
    }
    if (oldtarget != INVALID_ACTOR_ID)
    {
        ClearActorAnimations(oldtarget);
    }
}
/*
				TogglePlayerControllableEx(playerid, 1);
				MenuOperation[playerid] = 4;
				format(strings, sizeof(strings), "� ��� �� �����: $%d\
\n������� ����� �������������. \
\n\n\t{8CAA63}�� ��������� ����� ������� OK.", PlayerInfo[playerid][pBank]);
				ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "ATM: ������ �����", strings, "OK", "Cancel");
*/

stock bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != BANK_DIALOG) return 1;
	
	new msgitem[256+1];
	//new giveplayerid;
//ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "Transfer", "������� ����� ��������.\n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
//ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "BANK: ������� �����", strings, "OK", "Cancel");
//ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "Credit", "������� ����� �������������.\n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
//ShowPlayerDialogEx(playerid, BANKOMAT_DIALOG, DIALOG_STYLE_INPUT, "BANK: ������ �����", strings, "OK", "Cancel");
	if(!response)
	{
		DeletePVar(playerid, "Action");
		//new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}

//==============================================================================
	if(GetPVarInt(playerid, "Action") == 0)
	{//���� �������� ��� �� �������, �.�. ��� ���� ������� ���������
	    //�� ������ �������� ��� ��������� ����� ����������
		SetPVarInt(playerid, "Action", listitem+1);//�������� ��������� ��������
		DeletePVar(playerid, "InputCounter");//�������� �� ���������� ��������
	}
	new operation = GetPVarInt(playerid, "Action");
	if(operation == 1)//����� ������
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "������� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
		}
		else
		{
			if(strlen(inputtext) < 1 || strlen(inputtext) > 11)
			{
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "C���� ������� �� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
				return 1;
			}
			if(strval(inputtext) > PlayerInfo[playerid][pBank])
			{
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "� ��� ��� ������� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");
			new money = strval(inputtext);
			//--------------------------------------------------------------
			//GivePlayerMoneyH(fwithdraw, playerid, cashdeposit);
			if(PlayerInfo[playerid][pCash] + money < 2147483647)
			{
				new strtmp[11+10];
				PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
				format(strtmp, sizeof(strtmp), "~b~+~g~%s$", NiceMoney(money));
				GameTextForPlayerEx(playerid, strtmp, 1000, 1);
				PlayerInfo[playerid][pCash] += money;
				ResetPlayerMoney(playerid);//����� �� ���������� ������� -100 ��� ������ ������
				gConsumingMoney[playerid] = 2;
				GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
				LastMoney[playerid] = PlayerInfo[playerid][pCash];
			}
			//--------------------------------------------------------------
			new curfunds = PlayerInfo[playerid][pBank];
			//--------------------------------------------------------------
			if(PlayerInfo[playerid][pBank] + money < 2147483647)
			{
				new strtmp[11+10];
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				format(strtmp, sizeof(strtmp), "~r~%s$", NiceMoney(money));
				GameTextForPlayerEx(playerid, strtmp, 1000, 1);
			  	PlayerInfo[playerid][pBank] += (-1*money);
				format(strtmp, sizeof(strtmp), "$%08d", PlayerInfo[playerid][pBank]);
				PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strtmp);
			}
			//--------------------------------------------------------------
			SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
			format(msgitem, sizeof(msgitem), "  ������ ������: {33AA33}$%d", curfunds);
			SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
			format(msgitem, sizeof(msgitem), "  ����� ������: {33AA33}$%d", strval(inputtext));
			SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
			format(msgitem, sizeof(msgitem), "  ����� ������: {33AA33}$%d", PlayerInfo[playerid][pBank]);
			SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
			SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
		}
	}
	else if(operation == 2)//��������� ������
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "������� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
		}
		else
		{
			if(strlen(inputtext) < 1 || strlen(inputtext) > 11)
			{
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "C���� ������� �� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
				return 1;
			}
			new cashdeposit = strval(inputtext);
			if(cashdeposit > GetPlayerMoneyH(playerid) || cashdeposit < 1000//��� ���������
				|| PlayerInfo[playerid][pDeposit] + cashdeposit >= 2147483647)
			{   //���� ����� ������ ����� �� �����
				SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ������� ����� ��� ����� ������ $1000 !");
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "� ��� ��� ������� ����� ��� ����� ������ $1000. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new curfunds = PlayerInfo[playerid][pBank];
			GivePlayerMoneyH(fdeposit, playerid, -cashdeposit);
			PlayerInfo[playerid][pBank] += cashdeposit;

			SendClientMessage(playerid, COLOR_HERBAL, "|____________ BANK STATMENT ____________|");
			format(msgitem, sizeof(msgitem), "  ������ ������: {33AA33}$%d", curfunds);
			SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
			format(msgitem, sizeof(msgitem), "  ����� ����������: {33AA33}$%d",cashdeposit);
			SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
			format(msgitem, sizeof(msgitem), "  ����� ������: {33AA33}$%d", PlayerInfo[playerid][pBank]);
			SendClientMessage(playerid, COLOR_SYSTEM, msgitem);
			SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
		}
	}
	else if(operation == 3)//���������� �������
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			/*if(PlayerInfo[playerid][pMember] != SAN)
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� �������!");
			    return 1;
			}*/
			if(PlayerInfo[playerid][pLevel] < 5)
			{
				ShowBankMenu(playerid);
				return 1;
			}
			ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "������� ID ������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
		}
		else if(GetPVarInt(playerid, "InputCounter") == 1)
		{
			//SetPVarInt(playerid, "InputValue", strval(inputtext));
			new giveplayerid = strval(inputtext);
		    if( !IsPlayerConnected(giveplayerid) ||	gPlayerSpawned[giveplayerid] == 0 || gPlayerLogged[giveplayerid] == 0 )
			{
				format(msgitem, sizeof(msgitem), "ID:%d ����������� �� �������. \n������� ID ������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", giveplayerid);
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, msgitem, "OK", "Cancel");
				return 1;
			}
			SetPVarInt(playerid, "ForPlayerID", strval(inputtext));
			ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "������� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
		}
		else
		{
			if(strlen(inputtext) < 1 || strlen(inputtext) > 11 || strlen(inputtext) > PlayerInfo[playerid][pBank])
			{
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "C���� ������� �� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
				return 1;
			}
			new moneys = strval(inputtext);
			if(moneys < 1000 || moneys > 1000000)//80000
			{
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "����� ������ ���� �� ���� 1000, � �� ���� 1000000. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			    return 1;
			}
			if(strval(inputtext) > PlayerInfo[playerid][pBank])
			{
				ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_INPUT, inputtext, "� ��� ��� ������� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");
			
			new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
			GivePlayerMoneyB(ftransfer, playerid, -moneys);
			GivePlayerMoneyB(ftransfer, giveplayerid, moneys);
			format(strings, sizeof(strings), "   B� �������� $%d �� ���� %s'� (ID:%d)", moneys, PlayerName(giveplayerid),giveplayerid);
			PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			format(strings, sizeof(strings), "   B� �������� $%d �� ���� ���� �� %s'� (ID:%d)", moneys, PlayerName(playerid), playerid);
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);
			format(strings, sizeof(strings), "%s[%d] transfered $%d to %s[%d]", PlayerName(playerid), playerid, moneys, PlayerName(giveplayerid), giveplayerid);
			if(moneys >= 100000) SendAllAdminMessage(COLOR_MAROON, strings, 1);
			Log(PAY,strings);
		}
	}
	else DeletePVar(playerid, "Action");
	GivePVarInt(playerid, "InputCounter", +1);//������� ���-�� ������ � ������ ���������
	//format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, Action:%d, InputCounter:%d)", playerid, giveplayerid, GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter") );
	//SendClientMessage(playerid, COLOR_GREEN, strings);
	return 1;
}

stock ShowBankMenu(playerid)
{
	new dlgitem[] = "����� ������\n\
��������� ������\n\
���������� �������\n\
������ ���������� ��������\n\
�������� ������\n\
�������� ���\n\
�������� ������\n\
�������������������\n\
����� ������ � ������� �������\n\
��������� ������ �����������\n\
����� ������ � ������� �����\n\
��������� ������ �����";
	new caption[29+11];
	format(caption, sizeof(caption), "U.S. Bank Tower. ������: $%d", PlayerInfo[playerid][pBank]);
	ShowPlayerDialogEx(playerid, BANK_DIALOG, DIALOG_STYLE_LIST, caption, dlgitem, "�������", "������");
}

stock actor_OnPlayerKeyState_YES(playerid)
{
	//if(fix_fbi_spam[playerid] >= gettime())  return 1;
    new found;
	for(new ac = 0; ac < MAX_ACTORS; ac++)
	{
	    //actorid = ActorsY[ac][acID];
		if(!IsPlayerInRangeOfPoint(playerid, 5.0, ActorsY[ac][acX],ActorsY[ac][acY],ActorsY[ac][acZ])) continue;
		if(ActorsY[ac][acVW] != BANK_WORLD) continue;
//printf("3_%d. acID:%d, acX:%.4f,acY:%.4f,acZ:%.4f", ac, ActorsY[ac][acID],ActorsY[ac][acX],ActorsY[ac][acY],ActorsY[ac][acZ]);
		found ++;
		break;
	}
	if(found)
	{
		//strcat(dlgitem, "{0088ff}/fish {ffffff}- �������� ������\n");
		ShowBankMenu(playerid);
	}

	if(IsPlayerInRangeOfPoint(playerid, 2.0, 325.6152,1124.7094,1083.8828))
	{
	    if(!IsAGangs(playerid) && !IsAFamilyMember(playerid))
	    {
			if(narko_actor_text == Text3D:-1)
			{
			    narko_actor_text = Create3DTextLabelEx("��, ����-���� ���� ����? ��� ������, ���� ���.",-1,
					325.6152,1124.7094,1083.8828 + 1,10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);
				SendClientMessage(playerid, -1, "�������������: ��, ����-���� ���� ����? ��� ������, ���� ���.");
				SetTimer("@del_narko_actor_text", 5000, false);
				ApplyDynamicActorAnimation(narko_actor, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 1, 1);
				return 1;
			}
			else return 1;
	    }
	    new tel;//���� �� 1 �����
	    new ammount;
		new level = PlayerInfo[playerid][pDrugsSkill];
	    if(level < 250)	{ tel = 30; ammount = 6; }
		else if(level >= 250 && level < 500)	{ tel = 25; ammount = 12; }
		else if(level >= 500 && level < 1000) { tel = 20; ammount = 20; }
		else if(level >= 1000 && level < 2000) { tel = 15; ammount = 30; }
		else if(level >= 2000) { tel = 10; ammount = 100; }
		NarkInfoCash[playerid] = ammount*tel;
		format(strings, sizeof(strings), "��� ����� ��������� �������� \n�� ����� %d ����� ���������� \n�� ����� $%d \n�� ���� $%d �� �����.\
			\n������� �������� ���������� �����. \n\n\t{2680C0}�� ��������� ����� ������� OK.", ammount, ammount*tel, tel);
		MenuOperation[playerid] = 41;
		ShowPlayerDialogEx(playerid, DRUG_DIALOG, DIALOG_STYLE_INPUT, "Cracker House",strings, "OK", "Cancel");
		return 1;
	}

	if(IsPlayerInRangeOfPoint(playerid, 2.0, 1479.6161,-1749.3159,2106.1101))
	{//� �����
		new bool:onlinesot;
		for(new i; i <= GetPlayerPoolSize(); i++)
		{
			if(PlayerInfo[i][pMember] == DoJ && PlayerInfo[i][pRank] >= 9)
			{
				onlinesot = true;
				break;
			}
		}
		new sendername[MAX_PLAYER_NAME];
		new nsa[200];
		GetPlayerName(playerid, sendername, sizeof(sendername));
		if(onlinesot == false) format(nsa, 200, "������������, {FFFB00}%s,{FFFFFF} ����� �������� ������� ����������?", sendername);
		else format(nsa, 200, "������������, {FFFB00}%s.{FFFFFF} � ������ ������ � ����� ��������� �������,\n������� ����� ������ ��� ��������, ���������� � ����.", sendername);
		Update3DTextLabelEx(ActLIC_Text, 0xFFFFFFFF, nsa);
		ApplyDynamicActorAnimation(ActLIC, "PED", "IDLE_CHAT",4.1,1,1,1,0,0);
		SetTimer("CC_TEXT_ACTOR_LIC", 3000, false);
		if(onlinesot == true) return 1;

		ShowPlayerDialogEx(playerid, LIC_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{0E8C00}������� ��������",
"��������\t����\n\
{FFFFFF}�������� �� ������� ����\t{0E8C00}$10000\n\
{FFFFFF}�������� �� ������� �������\t{0E8C00}$5000\n\
{FFFFFF}�������� �� ������� ��������\t{0E8C00}$15000",
"OK", "Cancel");
		return 1;
	}
	return 1;
}



stock actor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == LIC_DIALOG)
	{
		#pragma unused inputtext
		
		if(!response) return 1;//PlaySoundForPlayer(playerid, 5202);
		//new Float:health = LastHealth[playerid];
		/*new ToBase[74+24+2];
		format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), DoJ);
		mysql_query(g_SQL, ToBase);
		if(cache_num_rows() > 0)
	 	{
	   		SendClientMessage(playerid, COLOR_GREY, "   �� ���������� � ׸���� ������!");
			return 1;
		}*/

		new permit = listitem+1;
		new family = DoJ;//1-house 10000,2-biz 5000,3-sbiz 15000

		if(permit == 1 && GetPlayerMoneyH(playerid) > 10000)
		{
			if(GetPVarInt(playerid, "gGotPermitHOUSE") > 0) return SendClientMessage(playerid, COLOR_GREY, "�� ��� �������� ����������");
			GivePlayerMoneyH(ffamily+PlayerInfo[playerid][pMember], playerid, -10000);
			FamilyInfo[family][fBank] += 10000/2;
			//GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, 10000/2);
		}
		else if(permit == 2 && GetPlayerMoneyH(playerid) > 5000)
		{
			if(GetPVarInt(playerid, "gGotPermitBIZ") > 0) return SendClientMessage(playerid, COLOR_GREY, "�� ��� �������� ����������");
			GivePlayerMoneyH(ffamily+PlayerInfo[playerid][pMember], playerid, -5000);
			FamilyInfo[family][fBank] += 5000/2;
			//GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, 5000/2);
		}
		else if(permit == 3 && GetPlayerMoneyH(playerid) > 15000)
		{
			if(GetPVarInt(playerid, "gGotPermitSBIZ") > 0) return SendClientMessage(playerid, COLOR_GREY, "�� ��� �������� ����������");
			GivePlayerMoneyH(ffamily+PlayerInfo[playerid][pMember], playerid, -15000);
			FamilyInfo[family][fBank] += 15000/2;
			//GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, 15000/2);
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ������� �����!");
			return 1;
		}
		new strcmd[144];
		format(strcmd, sizeof(strcmd), "��������� ������������� ����� %s'� ���������� �� ������� ������������ ������ %d.", PlayerName(playerid), permit);
		ProxDetector(playerid, 30.0, strcmd, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		switch(permit)
		{
			case 1: SetPVarInt(playerid, "gGotPermitHOUSE", permit);
			case 2: SetPVarInt(playerid, "gGotPermitBIZ", permit);
			case 3: SetPVarInt(playerid, "gGotPermitSBIZ", permit);
		}
		OnePlayAnim(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 1, 1, 0, 0); // Deal Drugs
		return 1;
	}
	return 1;
}




stock CreateDynamicActorExY(name[], modelid, Float:x, Float:y, Float:z, Float:r,
	invulnerable = true, Float:health = 100.0,	worldid = -1,
	interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_ACTOR_SD)//�������������� ���������
{
 	//new dynamicActor = CreateActor(modelid,  x, y, z, r);     SetActorVirtualWorld(dynamicActor, world);
 	if(interiorid == -1) interiorid = worldid;

 	new dynamicActor = CreateDynamicActor(modelid, x, y, z, r, invulnerable, health, worldid, interiorid, playerid,	streamdistance);//ActorID[i] =
	ActorsY[dynamicActor][acID] = dynamicActor,
	ActorsY[dynamicActor][acX] = x;
	ActorsY[dynamicActor][acY] = y;
	ActorsY[dynamicActor][acZ] = z;
	ActorsY[dynamicActor][acVW] = worldid;
	ActorCounter ++;
	
    Create3DTextLabelEx(name, -1, x, y, z+1.0, 30.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, worldid);//Text_Actor[i]
	return dynamicActor;
}


@del_narko_actor_text();
@del_narko_actor_text()
{
	if(narko_actor_text != Text3D:-1)
	{
		DestroyDynamic3DTextLabel(narko_actor_text);
		narko_actor_text = Text3D:-1;
	}
	ApplyDynamicActorAnimation(narko_actor,"CARRY","crry_prtial",4.0, 0,0,0,0,0);
}

@del_duglas_text();
@del_duglas_text()
{
	if(duglas_text != Text3D:-1)
	{
		DestroyDynamic3DTextLabel(duglas_text);
		duglas_text = Text3D:-1;
	}
	ApplyDynamicActorAnimation(duglas_actor,"CARRY","crry_prtial",4.0, 0,0,0,0,0);
	return 1;
}

@del_crage_text();
@del_crage_text()
{
	if(crage_text != Text3D:-1)
	{
		DestroyDynamic3DTextLabel(crage_text);
		crage_text = Text3D:-1;
	}
	ApplyDynamicActorAnimation(crage_actor,"CARRY","crry_prtial",4.0, 0,0,0,0,0);
	return 1;
}


forward CC_TEXT_ACTOR_LSPDVN2();
public CC_TEXT_ACTOR_LSPDVN2()
{
	//ClearActorAnimations(ActLSPDVN2);
	//return Update3DTextLabelText(ActLSPDVN2_Text, 0xFFFFFFFF, "");
	ClearDynamicActorAnimations(ActLSPDVN2);
	return UpdateDynamic3DTextLabelText(ActLSPDVN2_Text, 0xFFFFFFFF, "");
}
forward CC_TEXT_ACTOR_LSPDVN();
public CC_TEXT_ACTOR_LSPDVN()
{
	//ClearActorAnimations(ActLSPDVN);
	//return Update3DTextLabelText(ActLSPDVN_Text, 0xFFFFFFFF, "");
	ClearDynamicActorAnimations(ActLSPDVN);
	return UpdateDynamic3DTextLabelText(ActLSPDVN_Text, 0xFFFFFFFF, "");
}
forward CC_TEXT_ACTOR_LSPD();
public CC_TEXT_ACTOR_LSPD()
{
	//ClearActorAnimations(ActLSPD);
	//return Update3DTextLabelText(ActLSPD_Text, 0xFFFFFFFF, "");
	ClearDynamicActorAnimations(ActLSPD);
	return UpdateDynamic3DTextLabelText(ActLSPD_Text, 0xFFFFFFFF, "");
}
forward CC_TEXT_ACTOR_LIC();
public CC_TEXT_ACTOR_LIC()
{
	//ClearActorAnimations(ActLIC);
	//return Update3DTextLabelText(ActLIC_Text, 0xFFFFFFFF, "");
	ClearDynamicActorAnimations(ActLIC);
	return UpdateDynamic3DTextLabelText(ActLIC_Text, 0xFFFFFFFF, "");
}
forward CC_TEXT_ACTOR();
public CC_TEXT_ACTOR()
{
	//ClearActorAnimations(ActAvtosalon);
	//return Update3DTextLabelText(ActAvtosalon_Text, 0xFFFFFFFF, "");
	ClearDynamicActorAnimations(ActAvtosalon);
	return UpdateDynamic3DTextLabelText(ActAvtosalon_Text, 0xFFFFFFFF, "");
}
forward ClearTextActor(id);
public ClearTextActor(id)
{//������ �� 3 ���
	//ClearActorAnimations(ActorID[id]);
	//return Update3DTextLabelText(Text_Actor[id], 0xFFFFFFFF, "");
	ClearDynamicActorAnimations(ActorID[id]);
	return UpdateDynamic3DTextLabelText(Text_Actor[id], 0xFFFFFFFF, "");
}
forward ClearAnimText(playerid);
public ClearAnimText(playerid)
{
	ApplyAnimation(playerid,"CARRY","crry_prtial",4.0, 0,0,0,0,0,1);
	return 1;
}
