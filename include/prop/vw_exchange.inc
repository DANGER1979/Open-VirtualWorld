//http://www.samp-rus.com/forum/31-22428-1
//����� ���������

//����� - ����������� ��������� ���� ����� �� ������� ��� ������� ������ �� ������� �����
//��� ���������
enum demands_info
{//������ ������ ��� �����
	dOwned,//��� �������� ������
	dOperation,//0-��������� ��� ��� ����, 1-�������, 2-�������
	dType[2],//1. ������:	2. ��������:	3. ��������������	4. ���������	5. �����	6. �����:
	dAmount[2],//���-��
	Float: dPrice[2],//����
	dPeriod[2],//�����
}
new Demand[MAX_BIZ][demands_info];


stock EXCHANGE(playerid)
{
	new bizid = GetPVarInt(playerid, "Bouse");
    new caption[14+24+4];
	format(caption, sizeof(caption), "�����. %s[%d]", 	BizInfo[bizid][bDiscription], bizid);
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_LIST, caption, "\n1. ������ ���������\n2. ������ �����������\n3. �������\n4. ������", "OK", "�����");
}


stock exchange_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext

	if(dialogid != EXCHANGE_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	//new msgitem[256+1];
	//new giveplayerid;
	if(!response && MenuOperation[playerid] == 147)
	{//����� �� ������� ����� � ������� � ������ ���� ����������
		//PlaySoundForPlayer(playerid, SOUND_BEE_TRACK_STOP);
		//SetPVarInt(playerid, "Bouse", FREEROAM);
		biz_ControlMenu(playerid, GetPVarInt(playerid, "Bouse") );
		return 1;
	}
	new bouse = GetPVarInt(playerid, "Bouse");
//==============================================================================
	if(MenuOperation[playerid] == 147)//�����
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		//new msgitem[28 + 6*(24 + 2+20+24+24+3)];
	    if(listitem == 0)//1. ������ ��������� Sellers ' requests
	    {
	    	SetPVarInt(playerid, "TypeOperation", 1);
    	 	MenuOperation[playerid] = 150;
	    	Proposal(playerid, bouse);
	    }
	    else if(listitem == 1)//2. ������ ����������� //Customer requests
	    {
	    	SetPVarInt(playerid, "TypeOperation", 2);
 	   		MenuOperation[playerid] = 150;
	    	Proposal(playerid, bouse);
	    }
	    else if(listitem == 2)//3. �������
	    {
	        SetPVarInt(playerid, "TypeOperation", 1);
	        MenuOperation[playerid] = 152;
	        SelectTypeMaterial(playerid, bouse);
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"),	GetPVarInt(playerid, "Volume"));
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	    }
	    else if(listitem == 3)//4. ������
	    {
	    	SetPVarInt(playerid, "TypeOperation", 2);
	    	MenuOperation[playerid] = 152;
	    	SelectTypeMaterial(playerid, bouse);
	    }
	}
	//--------------------------------------------------------------------------
//������ ��������� ������
	else if(MenuOperation[playerid] == 150)//1. ������ ��������� //2. ������ �����������
	{
		if(!response)
		{//���� ������ ����� � ������� //1. ������ ��������� //2. ������ �����������
			MenuOperation[playerid] = 147;
			EXCHANGE(playerid);
			return 1;
		}
		MenuOperation[playerid] = 151;
		PlayerDemands(playerid, bouse, listitem);//���������� ������ �������� TypeOperation
	}
	else if(MenuOperation[playerid] == 151)
	{
		if(!response)
		{//���� ���������� �� ������ � �������  //1. ������ ��������� //2. ������ �����������
		   	MenuOperation[playerid] = 150;
	    	Proposal(playerid, bouse);
			return 1;
		}
//������������ ������
//�� ���� �� ����� ������ �������� � ������ ��������� �������
	}
//����� ��������� ������
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 152)//�������//������
	{
		if(!response)
		{//���� ������ ����� � ������� //3. ������� //4. ������
			MenuOperation[playerid] = 147;
			EXCHANGE(playerid);
			return 1;
		}
		SetPVarInt(playerid, "TypeMaterial", listitem+1);//���������� ����� ���� ���������
		
	    new caption[28+24+3+16];
    	MenuOperation[playerid] = 153;
   		new typeOperation = GetPVarInt(playerid, "TypeOperation");
		if(typeOperation == 1)
		{
			format(caption, sizeof(caption), "%s[%d].������� �� ����� - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
			ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "������� ����� �������: \n\n�� ��������� ����� ������� �����", "�����", "�����");
		}
		else if(typeOperation == 2)
		{
			format(caption, sizeof(caption), "%s[%d].������� �� ������ - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
			ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "������� ����� �������: \n\n�� ��������� ����� ������� �����", "�����", "�����");
		}

//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"),	GetPVarInt(playerid, "Volume"));
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//stock EnterVolumeMaterial(playerid, bouse)

 	}
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 153)//�������//������
	{//������� ����� �������/�������
		if(!response)
		{//���� ������ ����� � �������
			MenuOperation[playerid] = 152;
			SelectTypeMaterial(playerid, bouse);
		    return 1;
		}
		MenuOperation[playerid] = 154;
		GetVolumeMaterial(playerid, bouse, inputtext);//, GetPVarInt(playerid, "TypeMaterial"));
		
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"),GetPVarInt(playerid, "Volume"));
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//SendClientMessageToAll(COLOR_GREY, strings);
	}
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 154)//�������//������
	{//GetVolumeMaterial
		if(!response)
		{
			MenuOperation[playerid] = 153;
		    new caption[28+24+3+16];
		  	new typeOperation = GetPVarInt(playerid, "TypeOperation");
			if(typeOperation == 1)
			{
				format(caption, sizeof(caption), "%s[%d].������� �� ����� - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(GetPVarInt(playerid, "TypeMaterial")) );
				ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "������� ����� �������: \n\n�� ��������� ����� ������� �����", "�����", "�����");
			}
			else if(typeOperation == 2)
			{
				format(caption, sizeof(caption), "%s[%d].������� �� ������ - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(GetPVarInt(playerid, "TypeMaterial")) );
				ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "������� ����� �������: \n\n�� ��������� ����� ������� �����", "�����", "�����");
			}
		    return 1;
		}
		MenuOperation[playerid] = 155;
		OrderIsAccepted(playerid, bouse, inputtext);
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d, Price: %.2f",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"), GetPVarInt(playerid, "Volume"), GetPVarFloat(playerid, "Price") );
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//SendClientMessageToAll(COLOR_GREY, strings);
	}
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 155)
	{//����� ��������� �� �������//����� ������
		/*if(!response)
		{
			MenuOperation[playerid] = 154;
			SelectTypeMaterial(playerid, bouse);
		    return 1;
		}*/
		MenuOperation[playerid] = 156;
	}
	return 1;
}
//������ ��������� ������
stock Proposal(playerid, bouse)
{//����� �� ������ ���� ����� �������������
	#pragma unused bouse
	new caption[34];
	new typeOperation = GetPVarInt(playerid, "TypeOperation");
	if(typeOperation == 1) caption = "������ ���������. �������� ���.";
	else if(typeOperation == 2) caption = "������ �����������. �������� ���.";

   	new msgitem[28+6*(24+2+20+24+24+24)];
	strcat(msgitem, "�\t���\t�������\t��������\n");
	for(new t = 1; t <= 6; t++)
	{
		format(msgitem, sizeof(msgitem),   "%s%d.\t%s\t%s\t%s[%d]\n",
			msgitem, t, TypeCargo(t), TypeBranch(t), VehicleArray[GetTruckType(t)-400][Vehicle_Name], GetTruckType(t));
	}
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, msgitem, "OK", "�����");
}
stock PlayerDemands(playerid, bouse, listitem)//������ ��������� � �����������
{
	//#pragma unused bouse
	//new material[] = TypeCargo(listitem+1);
    //--------------------------------------------------------------------------
	new ind;
	new bigmsgitem[41+10*(35+10+6+6+4)];
	new typeOperation = GetPVarInt(playerid, "TypeOperation")-1;
	new typeMaterial = listitem+1;//GetPVarInt(playerid, "TypeMaterial");
	
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "PlayerDemands(typeOperation: %d, typeMaterial: %d)", typeOperation+1, typeMaterial);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	
	strcat(bigmsgitem, "���-��\t���� �� ��.\t�����\t��������\n");
	for(new b = 1; b < MAX_BIZ; b++)
	{
		if(ind > 10) break;
		//if(Demand[b][dOwned] == 0) continue;//��������� ������ ������ �� ��������� �����
		if(Demand[b][dOperation] != typeOperation) continue;//��������� ��� ���� � ��������� ��� �� �������
		if(Demand[b][dType][typeOperation] != typeMaterial) continue;//��������� ��� ���� � ������ ���������� �� ������� ���������� ������
		if(Demand[b][dAmount][typeOperation] <= 0) continue;//��������� ��� ���� c ������������ ���-�� ������ 0

		format(bigmsgitem, sizeof(bigmsgitem), "%s%d ��\t%.1f $\t%d $\t%d ���\n", bigmsgitem,
			Demand[b][dAmount][typeOperation],
			Demand[b][dPrice][typeOperation],
			floatround(Demand[b][dAmount][typeOperation]*Demand[b][dPrice][typeOperation]),
			Demand[b][dPeriod][typeOperation]);
		ind++;
		
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "%d.PlayerDemands(Owned: %d, Operation: %d, Type: %d, Amount: %d, Price: %.2f, Period: %d)",
//		ind, Demand[b][dOwned],
//		typeOperation+1,
//		Demand[b][dType][typeOperation],
//		Demand[b][dAmount][typeOperation],
//		Demand[b][dPrice][typeOperation],
//		Demand[b][dPeriod][typeOperation]);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//SendClientMessageToAll(COLOR_GREY, strings);
		//break;
	}

	if(strlen(bigmsgitem) > sizeof(bigmsgitem) || strlen(bigmsgitem) <= 0)
	{
		//��������������
		format(strings, sizeof(strings), "Error: Demands - %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	/*if(strlen(bigmsgitem) <= 0)
	{
		EXCHANGE(playerid);
	}*/
    new caption[29+24+3+10];
	if(typeOperation == 0) format(caption, sizeof(caption), "%s[%d]. ������ ���������: %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
	else if(typeOperation == 1) format(caption, sizeof(caption), "%s[%d]. ������ �����������: %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, bigmsgitem, "OK", "�����");

//SendClientMessageToAll(COLOR_GREY, strings);
    return 1;
}//����� ��������� ������
//==============================================================================
//������ ������ ������
stock SelectTypeMaterial(playerid, bouse)
{
	new msgitem[148+6*10];
	strcat(msgitem, "���\t�� ������\t�� ����� ������\n");
	
	format(msgitem, sizeof(msgitem),"%s1. ������:\t%d\t%d\n\
									2. ��������:\t%d\t%d\n\
									3. ��������������:\t%d\t%d\n\
									4. ���������:\t%d\t%d\n\
									5. �����:\t%d\t%d\n\
									6. �����:\t%d\t%d",msgitem,
		BizInfo[bouse][bMetal],BizInfo[80][bMetal],
		BizInfo[bouse][bTextiles],BizInfo[80][bTextiles],
		BizInfo[bouse][bProvisions],BizInfo[80][bProvisions],
		BizInfo[bouse][bTree],BizInfo[80][bTree],
		BizInfo[bouse][bFuel],BizInfo[80][bFuel],
		BizInfo[bouse][bProducts],BizInfo[80][bProducts]);
		
	new caption[50+20+3];
	if(GetPVarInt(playerid, "TypeOperation") == 1) format(caption, sizeof(caption), "%s[%d]. ������� �� �����. �������� ��� ���������", BizInfo[bouse][bDiscription], bouse);
	else format(caption, sizeof(caption), "%s[%d]. ������� �� ������. �������� ��� ���������", BizInfo[bouse][bDiscription], bouse);
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, msgitem, "OK", "�����");
}


stock GetVolumeMaterial(playerid, bouse, inputtext[])//, typematerial)
{//������ ����� ���-��, ������ ������� ��� �������
	new typeOperation = GetPVarInt(playerid, "TypeOperation");//������� ��� �������
	new typeMaterial = GetPVarInt(playerid, "TypeMaterial");//1-6
	new Volume = strval(inputtext);	SetPVarInt(playerid, "Volume", Volume);

	new Spares = GetProducts(bouse);//�����
	new MarketValue = GetMarketValue(typeMaterial);//�������� ���������

	new branch[24];
    strmid(branch, TypeBranch(typeMaterial), 0, 24, 255);

    new material[20];
    strmid(material, TypeCargo(typeMaterial), 0, 24, 255);

    new bigmsgitem[41+(33*10)];
	if(typeMaterial == 6)
	{
		format(bigmsgitem, sizeof(bigmsgitem), "�������� ������: %s[%d]", material, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n�������: %s[%d]", bigmsgitem, branch, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n������� ���������: %s", bigmsgitem, "�������");
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n��������� ������: %d ��", bigmsgitem, Spares);

		if(typeOperation == 1) format(bigmsgitem, sizeof(bigmsgitem), "%s\n����� �������: %d", bigmsgitem, Volume);
		else if(typeOperation == 2) format(bigmsgitem, sizeof(bigmsgitem), "%s\n����� �������: %d", bigmsgitem, Volume);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n\n�������� ���������: $%d. \n������������ �����: %d %%", bigmsgitem, MarketValue, 1);

		//format(bigmsgitem, sizeof(bigmsgitem), "%s\n������ �������: �������� ����� �������� �� %d%", bigmsgitem, 25);
		//strcat(bigmsgitem, "\n�������� ������:	������� ���������, \n������������� ��������� ��������, \n� ��������� �������-������������� \n� ����� �����������.");
		//if(typeOperation == 1) strcat(bigmsgitem, "\n����� �����: ������� �������,������� �������");
		if(typeOperation == 1)
		{
			strcat(bigmsgitem, "\n���������: ������ ���� ������� ���� ��������, \n�� ������� ������� ������� ���� �����.");
			strcat(bigmsgitem, "\n\n������� ���������:");
		}
		else if(typeOperation == 2)
		{
			strcat(bigmsgitem, "\n���������:���� �� ���������� \n���������� ���� ���� ��������, \n�� ������� ������� ������ ������ ��� �����.");
			strcat(bigmsgitem, "\n������� ���������� ���� �� �����:");
		}
	}
	else
	{
		format(bigmsgitem, sizeof(bigmsgitem), "�������� �����: %s[%d]", material, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n�������: %s[%d]", bigmsgitem, branch, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n��������� ������: %d", bigmsgitem, Spares);
		if(typeOperation == 1) format(bigmsgitem, sizeof(bigmsgitem), "%s\n����� �������: %d", bigmsgitem, Volume);
		else if(typeOperation == 2) format(bigmsgitem, sizeof(bigmsgitem), "%s\n����� �������: %d", bigmsgitem, Volume);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n\n�������� ���������: $%d. \n������������ �����: %d %%", bigmsgitem, MarketValue, 1);
		if(typeOperation == 1)
		{
			strcat(bigmsgitem, "\n���������: ������ ���� ������� ���� ��������, \n�� ������� ������� ������� ���� �����.");
			strcat(bigmsgitem, "\n\n������� ���������:");
		}
		else if(typeOperation == 2)
		{
			strcat(bigmsgitem, "\n���������:���� �� ���������� \n���������� ���� ���� ��������, \n�� ������� ������� ������ ������ ��� �����.");
			strcat(bigmsgitem, "\n\n������� ���������� ���� �� �����:");
		}
	}
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//��������������
		format(strings, sizeof(strings), "Error: �������/������� �� ������ by %s[%d], strlen: %d, sizeof: %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	
    new caption[44+24+3];
	if(typeOperation == 1)
	{
		format(caption, sizeof(caption), "%s[%d]. ������� �� ����� - %s", BizInfo[bouse][bDiscription], bouse, material );
		ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, bigmsgitem, "�������", "�����");
	}
	else if(typeOperation == 2)
	{
		format(caption, sizeof(caption), "%s[%d]. ������� �� ������ - %s", BizInfo[bouse][bDiscription], bouse, material );
		ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, bigmsgitem, "������", "�����");
	}
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "GetVolumeMaterial(typeOperation: %d, typeMaterial: %d, Volume: %d)", typeOperation, typeMaterial, Volume);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	return 1;
}


//������ �������
stock OrderIsAccepted(playerid, bouse, inputtext[])
{//����� ����
	new typeOperation = GetPVarInt(playerid, "TypeOperation")-1;//-1 �.�. ������ ���������� �� ����
	new typeMaterial = GetPVarInt(playerid, "TypeMaterial");
	new Volume = GetPVarInt(playerid, "Volume");
	new Float: price = strval(inputtext);
	SetPVarFloat(playerid, "Price", price); //SetPVarInt(playerid, "Price", price);

	/*if(typeOperation == 1)
	{
		BizInfo[bouse][bTill] += price;
	    if(typeMaterial == 1)//1. ������
	    {
			BizInfo[bouse][bMetal] -= Volume;
	    }
	    else if(typeMaterial == 2)//2. ��������
	    {
			BizInfo[bouse][bTextiles] -= Volume;
	    }
	    else if(typeMaterial == 3)//3. ��������������
	    {
			BizInfo[bouse][bProvisions] -= Volume;
	    }
	    else if(typeMaterial == 4)//4. ���������
	    {
			BizInfo[bouse][bTree] -= Volume;
	    }
	    else if(typeMaterial == 5)//5. �����
	    {
			BizInfo[bouse][bFuel] -= Volume;
	    }
	    else if(typeMaterial == 6)//6. �����
	    {
			BizInfo[bouse][bProducts] -= Volume;
	    }
	}
	else if(typeOperation == 2)
	{
		BizInfo[bouse][bTill] -= price;
	    if(typeMaterial == 1)//1. ������
	    {
			BizInfo[bouse][bMetal] += Volume;
	    }
	    else if(typeMaterial == 2)//2. ��������
	    {
			BizInfo[bouse][bTextiles] += Volume;
	    }
	    else if(typeMaterial == 3)//3. ��������������
	    {
			BizInfo[bouse][bProvisions] += Volume;
	    }
	    else if(typeMaterial == 4)//4. ���������
	    {
			BizInfo[bouse][bTree] += Volume;
	    }
	    else if(typeMaterial == 5)//5. �����
	    {
			BizInfo[bouse][bFuel] += Volume;
	    }
	    else if(typeMaterial == 6)//6. �����
	    {
			BizInfo[bouse][bProducts] += Volume;
	    }
	}*/
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "OrderIsAccepted(typeOperation: %d, typeMaterial: %d, Volume: %d, price: %d)", typeOperation+1, typeMaterial, Volume, price);
//SendClientMessageEx(playerid, COLOR_GREY, strings);

//��������� ������ �� ������� ����
	Demand[bouse][dOwned] = BizInfo[bouse][bOwned];//b�� ������
	Demand[bouse][dOperation] = typeOperation;//��������� ��� ������ ������ �� ������� ��� �� �������
	Demand[bouse][dType][typeOperation] = typeMaterial;
	Demand[bouse][dAmount][typeOperation] = Volume;
	Demand[bouse][dPrice][typeOperation] = price;
	Demand[bouse][dPeriod][typeOperation] = 1140;//1440 ����� //24 ����;
//��������������
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "OrderIsAccepted(Owned: %d, Operation: %d, Type: %d, Amount: %d, Price: %.2f, Period: %d)",
//	Demand[bouse][dOwned], typeOperation+1, Demand[bouse][dType][typeOperation], Demand[bouse][dAmount][typeOperation],
//	Demand[bouse][dPrice][typeOperation], Demand[bouse][dPeriod][typeOperation]);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	new msgitem[66+20+10+10];
	if(typeOperation == 0)
	{
		format(msgitem, sizeof(msgitem), "%s ��������� �� �������.\n\n����� ������: $%.1f \n������� %d ��.", TypeCargo(typeMaterial), price, Volume);
	}
	else if(typeOperation == 1)
	{
		format(msgitem, sizeof(msgitem), "����� %s ������.\n\n����� ������: $%.1f \n������� %d ��.", TypeCargo(typeMaterial), price, Volume);
	}
    new caption[35+24+3];
	format(caption, sizeof(caption), "%s[%d]", BizInfo[bouse][bDiscription], bouse);
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_MSGBOX, caption, msgitem, "OK", "");
}
