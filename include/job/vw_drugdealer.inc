

stock drugdealer_OnPlayerPickUp(playerid)
{
	if(PlayerInfo[playerid][pJob] != DRUGDEALER) return 1;
	if( IsPlayerInRangeOfPoint(playerid, 2.1, -1210.1460,-1043.3667,128.3897) )
	{
//��� ������������ STEP1 ��������� �������
		if(PlayerInfo[playerid][pMats] == 0)
		{	//factory production Material
			if(SBizInfo[52][sbProducts] <= 0)
			{
    			format(strings, sizeof(strings), "~r~Out Of Stock in ~p~%s", SBizInfo[52][sbDiscription]);
				GameTextForPlayerEx(playerid, strings, 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			//GameTextForPlayerEx(playerid, "~y~Welcome to the ~n~Factory~n~~b~Use (~w~/materials get~b~)~n~~g~to take a Materials Packages", 5000, 3);
			new level = PlayerInfo[playerid][pDrugsSkill];
			new package;//��� ���������
			if(level < 250) { package = 30; }
			else if(level >= 250 && level < 500) { package = 34; }
			else if(level >= 500 && level < 1000) { package = 37; }
			else if(level >= 1000 && level < 2000) { package = 39; }
			else if(level >= 2000) { package = 40; }
			//new price = package * pricepackage;
			new price = floatround(package*compcost*(100+SBizInfo[52][sbSellProd])/100.0, floatround_ceil);
//new pricepackage = 7;//���� ������
//new amountmaterials = 30;//���-�� ������� � ����� ������

			//���� ������� 30*100=$3000 �� amountmaterials*package = 50*30=1500 �����
			//33*100=$3300 �� 50*33=1650 �����
			//30*100=$3000 �� 50*30=1500 �����
			//28*100=$2800 �� 50*28=1400 �����

			new dlgitem[87 + 2+4];
			format(dlgitem, sizeof(dlgitem), "�� ������ ���������� \n{FFFFFF}%d{0080FF} ������� � ������� \n���������� {33AA33}$%d?",
				package, price);
			//strcat(dlgitem, "\n�� ������ ���������� %d ������� � ������� �� $%d.?");
			ShowPlayerDialogGap(playerid, FERMA_DIALOG, DIALOG_STYLE_MSGBOX, "����� �����", dlgitem, "���", "��");
			//GameTextForPlayerEx(playerid, "~w~Welcome to the ~~y~Factory~n~~g~You have got 10 Packages a Material", 5000, 3);
		}
	}
	else if( IsPlayerInRangeOfPoint(playerid, 2.1, 323.0342,1118.5804,1083.8828) )
	{	//��� ������������ STEP3 ��������� �����
	    //GameTextForPlayerEx(playerid, "~w~Type ~r~/get drugs, ~w~to get some ~r~Drugs~y~~n~Skill Level matters to price", 1000, 3);
		if(PlayerInfo[playerid][pJob] == DRUGDEALER)
		{   //���� �� ���������� � ���� ������, �� ��������� �����
			if(PlayerInfo[playerid][pMats] > 0)
			{
		        //�� 522 = 97 ������ //�� ��������� 83
		        //GetTickCount();
				//if(PlayerInfo[playerid][pCarTime] > 0) { PlayerInfo[playerid][pDrugsSkill] = 0; PlayerInfo[playerid][pMats] = 0;}
				if(GetTickCount() < (checktimedeliver[playerid]+60000) && !gAnticheat[playerid])
				{
					format(strings, sizeof(strings), "%s[%d] Reset DrugsSkill:%d Mats:%d checktimedeliver:%d[%d] sec",
						PlayerName(playerid),playerid, PlayerInfo[playerid][pDrugsSkill], PlayerInfo[playerid][pMats], (GetTickCount()-checktimedeliver[playerid])/1000, 60);
					Log(JOB, strings);
					PlayerInfo[playerid][pDrugsSkill] = 0;
					PlayerInfo[playerid][pMats] = 0;
					SendClientMessage(playerid, COLOR_GREY, strings);
					return 1;
				}
				//format(strings, sizeof(strings), "%s[%d] DrugsSkill:%d checktimedeliver:%d sec",
				//	PlayerName(playerid),playerid, PlayerInfo[playerid][pDrugsSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
				//Log(JOB, strings);

//���� ����� ��������� ������ ��� �� 120 ������, �.�. 120 ������ ��� �� ������, � �� ��� ����� �� �����, �� �������� ����, �.�. ��� �����
		        //PlayerInfo[playerid][pCarTime] = 60*2;//��� ����� ������� �� 120 ������
		        //--------------------------------------------------------------
				/*new skill;//��� ���������
				new level = PlayerInfo[playerid][pDrugsSkill];
				if(level < 500) { skill = 1; }
				else if(level >= 500 && level < 1000) { skill = 2; }
				else if(level >= 1000 && level < 2000) { skill = 3; }
				else if(level >= 2000 && level < 4000) { skill = 4; }
				else if(level >= 4000) { skill = 5; }*/

			/*new level = PlayerInfo[playerid][pDrugsSkill];
			new package;//��� ���������
			if(level < 500) { package = 30; }
			else if(level >= 500 && level < 1000) { package = 34; }
			else if(level >= 1000 && level < 2000) { package = 37; }
			else if(level >= 2000 && level < 4000) { package = 39; }
			else if(level >= 4000) { package = 40; }
			new price = package * pricepackage;*/

				//new Float: pricematerials = float(pricepackage)/amountmaterials;//���� ������ ����� 0.23$ - �� ���� �� 1 �����
//new pricepackage = 7;//���� ������
//new amountmaterials = 30;//���-�� ������� � ����� ������
				//new price = floatround((1.0+skill/(1.0 + skill))*pricematerials*PlayerInfo[playerid][pMats] );
				new price = floatround(PlayerInfo[playerid][pMats]*(100+SBizInfo[52][sbSellProd])/100.0, floatround_ceil);//(1.0+skill/(1.0 + skill)*compcost*

				//(1.0+1/(1 + 1))*0.23*900 = (311-30*7)*13 - 338(�� �������) = 975 //�� ��� ������� �� 1 �����
				//(1.0+5/(1 + 5))*0.23*1200 = (506-30*7)*13 - 338(�� �������) = 3510 //�� ��� ������� �� 5 �����

				if(	IsAGangs(playerid) )
				{
					PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
					format(strings, sizeof(strings), "~r~%d$", price);
					GameTextForPlayerEx(playerid, strings, 1000, 1);
					FamilyInfo[PlayerInfo[playerid][pMember]][fBank] += price/2;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, price/2 );
					//SaveFamiliesSQL(PlayerName(playerid));//������� ����� ����������
					format(strings, sizeof(strings), "%s, ������ ������� $%d �� %d ����� �������. �������� � �����.", PlayerName(playerid), price/2, PlayerInfo[playerid][pMats]);
				}
				else if(PlayerInfo[playerid][pMember] == LCN)
				{
					PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
					format(strings, sizeof(strings), "~r~%d$", price);
					GameTextForPlayerEx(playerid, strings, 1000, 1);
					FamilyInfo[0+PlayerInfo[playerid][pMember]][fBank] += price/2;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, price/2);
					//SaveFamiliesSQL(PlayerName(playerid));//������ ����� ����������
					format(strings, sizeof(strings), "%s, ������ ������� $%d �� %d ����� �������. �������� � �����.", PlayerName(playerid), price/2, PlayerInfo[playerid][pMats]);
				}
				else if(PlayerInfo[playerid][pMember] == Yakuza)
				{
					PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
					format(strings, sizeof(strings), "~r~%d$", price);
					GameTextForPlayerEx(playerid, strings, 1000, 1);
					FamilyInfo[0+PlayerInfo[playerid][pMember]][fBank] += price/2;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, price/2);
					//SaveFamiliesSQL(PlayerName(playerid));//������ ����� ����������
		            format(strings, sizeof(strings), "%s, ������ ������� $%d �� %d ����� �������. �������� � �����.", PlayerName(playerid), price/2, PlayerInfo[playerid][pMats]);
				}
				else
				{
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, price);
		            format(strings, sizeof(strings), "%s, ������ ������� $%d �� %d ����� �������.", PlayerName(playerid), price, PlayerInfo[playerid][pMats]);
				}
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
				Log(PACKET, strings);

				PlayerInfo[playerid][pDrugsSkill] += PlayerInfo[playerid][pMats]/100;
				if(PlayerInfo[playerid][pDrugsSkill] == 250)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ����������� ������ ������ 2, �� ������ ������ ������ ������� � �������."); }
				else if(PlayerInfo[playerid][pDrugsSkill] == 500)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ����������� ������ ������ 3, �� ������ ������ ������ ������� � �������."); }
				else if(PlayerInfo[playerid][pDrugsSkill] == 1000)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ����������� ������ ������ 4, �� ������ ������ ������ ������� � �������."); }
				else if(PlayerInfo[playerid][pDrugsSkill] == 2000)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* ��� ����� ����������� ������ ������ 5, �� ������ ������ ������ ������� � �������."); }

				PlayerInfo[playerid][pMats] = 0;
			}
	        else
	        {   //���� ������� ���, �� ������ �������
				//SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ������ ������� � ������� !");
	 			//GameTextForPlayerEx(playerid, "~w~Welcome to the ~y~Gun Plant~n~~g~You have got Packet", 5000, 3);
		        new tel;//���� �� 1 �����
			    new ammount;
				new level = PlayerInfo[playerid][pDrugsSkill];
				if(level < 250)	{ tel = 30; ammount = 6; }//��� ���������
				else if(level >= 250 && level < 500)	{ tel = 25; ammount = 12; }
				else if(level >= 500 && level < 1000) { tel = 20; ammount = 20; }
				else if(level >= 1000 && level < 2000) { tel = 15; ammount = 30; }
				else if(level >= 2000) { tel = 10; ammount = 100; }
				format(strings, sizeof(strings), "��� ����� ��������� �������� \n�� ����� %d ����� ���������� \n�� ����� $%d \n�� ���� $%d �� �����.\
					\n������� �������� ���������� �����. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", ammount, ammount*tel, tel);
				MenuOperation[playerid] = 41;
				ShowPlayerDialogEx(playerid, DRUG_DIALOG, DIALOG_STYLE_INPUT, "Cracker House",strings, "OK", "Cancel");
			}
		}
	}
	return 1;
}


stock drugdealer_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != DRUG_DIALOG) return 1;//service
	#pragma unused listitem
	//#pragma unused inputtext
	SetPVarInt(playerid, "gShowDialog", -1);
	new msgitem[256+1];
	//new giveplayerid;
	if(!response) return 1;
	if(MenuOperation[playerid] == 41)//��� ������������
	{
        if(PlayerInfo[playerid][pDrugs] > 100)
        {
            format(msgitem, sizeof(msgitem), "   � ��� ��� ����� %d ����� ���������� ��� �������. ��������� ����� !", PlayerInfo[playerid][pDrugs]);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
            return 1;
        }
        new tel;
		new level = PlayerInfo[playerid][pDrugsSkill];
		new ammount = strval(inputtext);
		if(level < 250)//��� ���������
		{ tel = 30; if(ammount < 1 || ammount > 6) { SendClientMessage(playerid, COLOR_GREY, "   ��� ����� �� ��������� ������ ������ 6 �����!"); return 1; } }
		else if(level >= 250 && level < 500)
		{ tel = 25; if(ammount < 1 || ammount > 12) { SendClientMessage(playerid, COLOR_GREY, "   ��� ����� �� ��������� ������ ������ 12 �����!"); return 1; } }
		else if(level >= 500 && level < 1000)
		{ tel = 20; if(ammount < 1 || ammount > 20) { SendClientMessage(playerid, COLOR_GREY, "   ��� ����� �� ��������� ������ ������ 20 �����!"); return 1; } }
		else if(level >= 1000 && level < 2000)
		{ tel = 15; if(ammount < 1 || ammount > 30) { SendClientMessage(playerid, COLOR_GREY, "   ��� ����� �� ��������� ������ ������ 30 �����!"); return 1; } }
		else if(level >= 2000)
		{ tel = 10; if(ammount < 1 || ammount > 100) { SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ��������� ��� ����� �� 1 �� 100 �����!"); return 1; } }
	    new price = ammount*tel;
	    if(GetPlayerMoneyH(playerid) > price)
	    {
	        format(msgitem, sizeof(msgitem), "* �� ������ %d ����� �� {33AA33}$%d.", ammount, price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	        GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, -price);
			FamilyInfo[LCN][fBank] += price/2;
			FamilyInfo[Yakuza][fBank] += price/2;
			PlayerInfo[playerid][pDrugs] = ammount;
	    }
	    else
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� ��������� !");
	    }
    }
    return 1;
}
		
