//каталог инфы по тачкам

//см. vw_changer.inc

/*
#if defined vw_changer//#endif

#else
	new PlayerText:gSelectionItems[MAX_PLAYERS];//хранит ИД текстдровов ячеек
#endif*/
/*
stock ospawner(playerid)
{
	gSelectionItems[playerid] = PlayerText:INVALID_TEXT_DRAW;
	return 1; // Allow other scripts to keep processing OnPlayerConnect
}
stock carinfo_OnPlayerConnect(playerid)
{
	ospawner(playerid);
}
*/


// Удаляет ячейку предварительного просмотра модели
/*stock DestroyPlayerModelPreviews(playerid)
{
    if(gSelectionItems[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, gSelectionItems[playerid]);
		gSelectionItems[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
}*/



stock CarInfo(playerid)
{
	MenuOperation[playerid] = 136;
	new listitems[] = "по Модели\nпо Названию\nпо Категории\nпо Модификации\nпо Макс. Цене\nпо Объёму бака\nпо Уровню";
	ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "Поиск транспорта", listitems, "OK", "Cancel");
}

stock carinfo_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{   //dialogid  - диалог на который выйдем
	//#pragma unused listitem
	//#pragma unused inputtext
#if defined vw_changer//#endif
	DestroyPlayerModelPreviews(playerid);
#endif

	AutoSalon_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	if(dialogid != CARINFO_DIALOG) return 1;
	new modelid, vehname[32];//, categor=255,
	new modific=255;//, MinPrice, MaxPrice, MinFuel, MaxFuel;
//printf("1. MenuOperation: %d response: %d listitem: %d inputtext: %s", MenuOperation[playerid], response, listitem, inputtext);
	if(MenuOperation[playerid] == 136)
	{//ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите секцию",listitems, "OK", "Cancel");
		if(response)
		{
			if(listitem == 0)//Model
			{
				MenuOperation[playerid] = 137;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите номер модели от 400 до 611. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
//printf("2. MenuOperation: %d", MenuOperation[playerid]);
			}
			else if(listitem == 1)//Name
			{
				MenuOperation[playerid] = 138;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите название транспорта. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			}
			else if(listitem == 2)//Category
			{
				new listitems[83+87+88+97];
				strcat(listitems, "1. Самолёты\n2. Классические\n3. Вертолёты\n4. Ловрайдеры\n5. Роскошные\n");
				strcat(listitems, "6. Мотоциклы\n7. Внедорожники\n8. Гоночные тачки\n9. Фургоны\n10. Спорт. тачки\n11. Велосипеды\n");
				strcat(listitems, "12. Лодки\n13. Промышленные\n14. Грузовики\n15. Рабочие\n16. Рельсовые\n");
				strcat(listitems, "17. Игрушки\n18. Скутеры\n19. Служебные\n20. Прицепы\n21. Уникальные\n");

				MenuOperation[playerid] = 139;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите категорию", listitems, "OK", "Cancel");
//printf("3. MenuOperation: %d", MenuOperation[playerid]);
			}
			else if(listitem == 3)//Modifications
			{
				new listitems[63];
				strcat(listitems, "None\nTrans_Fender\nLoco_Low_Co\nWheel_Arch_Angels\nStandard\n");
				MenuOperation[playerid] = 140;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите модификацию",listitems, "OK", "Cancel");
			}
			else if(listitem == 4)//MaxPrice
			{
				MenuOperation[playerid] = 141;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите цену максимально доступную вашему кошельку\nдо 200к . \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			}
			else if(listitem == 5)//GasMax
			{
				MenuOperation[playerid] = 143;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите верхний предел диапазона вместимости бака \nдо 43400 л. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			}
			else if(listitem == 6)//Level
			{
				MenuOperation[playerid] = 146;
				ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите требуемый уровень транспорта (1-17).\
\n{8CAA63}Примечание:\
\n\t- Вы не сможете купить транспорт выше чем ваш уровень.\
\n\tПо окончанию ввода нажмите OK.", "OK", "Cancel");
			}
		}
	}
	else if(MenuOperation[playerid] == 137)//Model
	{
		if(!response)
		{
			CarInfo(playerid);
			return 1;
		}
//printf("7. MenuOperation: %d", MenuOperation[playerid]);
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 137;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите номер модели от 400 до 611. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		modelid = strval(inputtext);
		if(modelid < 400 || modelid > 611)
		{
			MenuOperation[playerid] = 137;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите номер модели от 400 до 611. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}

		//new ind = 0;//счётчик найденных по данной категории
		new listitems[32+3];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
			if(VehicleArray[i][ModelID] == modelid)
			{
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
				//SetPVarInt(playerid, "CarLine", i);
//printf("8. modelid: %d %s", modelid, VehicleArray[i][Vehicle_Name]);
				break;
			}
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите модель транспорта",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 138)//Name
	{
		if(!response)
		{
			new listitems[57];
			strcat(listitems, "Модель\nНазвание\nКатегория\nМодификация\nМакс. Цена\nОбъём бака\n");
			MenuOperation[playerid] = 136;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите секцию",listitems, "OK", "Cancel");
			return 1;
		}
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 138;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите название транспорта. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		strmid(vehname, inputtext, 0, strlen(inputtext), 32);
		//new ind = 0;//счётчик найденных по данной категории
 		new listitems[32+3];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
	        if( !strcmp(vehname, VehicleArray[i][Vehicle_Name], true) )
	        {   //если введеное имя и имя из массива совпадают
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
				//SetPVarInt(playerid, "CarLine", i);
   				break;
   			}
		}
		if(!strlen(listitems))
		{//если такого транспорта не существует
			MenuOperation[playerid] = 138;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите название транспорта. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите название транспорта",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 139)//Category
	{
		if(!response)
		{
			CarInfo(playerid);
			return 1;
		}
		new ind = 0;//счётчик найденных по данной категории
	 	new listitems[35*20];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
			if(VehicleArray[i][Category] == listitem+1)
		    {
		    	ind ++;
		    	if(ind > 20) break;
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
				//SetPVarInt(playerid, "CarLine", i);
	   			//break;
			}
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите категорию транспорта",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 140)
	{
		if(!response)
		{
			CarInfo(playerid);
			return 1;
		}
		modific = listitem;
		new ind = 0;//счётчик найденных по данной категории
		new listitems[35*20];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
			if(VehicleArray[i][Modifications] == modific)
		    {
		    	ind ++;
		    	if(ind > 20) break;
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
	   			//break;
			}
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выберите модификацию транспорта",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 141)
	{
		if(!response)
		{
			CarInfo(playerid);
			return 1;
		}
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 141;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по цене", "Введите цену максимально доступную вашему кошельку\nдо 200к . \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		SetPVarInt(playerid, "MaxPrice", strval(inputtext));
		MenuOperation[playerid] = 142;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по цене", "Введите нижний предел диапазона цен. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 142)
	{
		if(!response)
		{
			//CarInfo(playerid);
			return 1;
		}
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 142;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по цене", "Введите нижний предел диапазона цен. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		SetPVarInt(playerid, "MinPrice", strval(inputtext));

		new ind = 0;//счётчик найденных по данной категории
		new listitems[35*20];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
		    if(VehicleArray[i][Virtual_Price] >= GetPVarInt(playerid, "MinPrice") && VehicleArray[i][Virtual_Price] <= GetPVarInt(playerid, "MaxPrice")
				&& VehicleArray[i][Category] != Rail_Transport && VehicleArray[i][Category] != RC_Vehicles
			 	&& VehicleArray[i][Category] != Trailers && VehicleArray[i][Category] != Not_Used)
		    {
				//format(strcmd, sizeof(strcmd), "%s[%d]: $%d", PlayerName(i), i, money);
	           	//SendClientMessage(playerid, COLOR_GREEN, strcmd);
	           	ind ++;
		    	if(ind > 20) break;
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
				//SetPVarInt(playerid, "CarLine", i);
		    }
		}
		if(!strlen(listitems))
		{//если ни чего не нашли
			CarInfo(playerid);
			return 1;
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выбор транспорта по цене",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 143)
	{
		if(!response)
		{
			CarInfo(playerid);
			return 1;
		}
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 143;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по вместимости бака", "Введите верхний предел диапазона вместимости бака \nдо 43400 л. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		SetPVarInt(playerid, "MaxFuel", strval(inputtext));

		MenuOperation[playerid] = 144;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по вместимости бака", "Введите нижний предел диапазона вместимости бака. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 144)
	{
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 144;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по вместимости бака", "Введите нижний предел диапазона вместимости бака. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		SetPVarInt(playerid, "MinFuel", strval(inputtext));

		new ind = 0;//счётчик найденных по данной категории
		new listitems[35*20];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
		    if(VehicleArray[i][GasMax] >= GetPVarInt(playerid, "MinFuel") && VehicleArray[i][GasMax] <= GetPVarInt(playerid, "MaxFuel"))
		    {
				//format(strcmd, sizeof(strcmd), "%s[%d]: $%d", PlayerName(i), i, money);
            	//SendClientMessage(playerid, COLOR_GREEN, strcmd);
            	ind ++;
 		    	if(ind > 20) break;
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
				//SetPVarInt(playerid, "CarLine", i);
		    }
		}
		if(!strlen(listitems))
		{//если ни чего не нашли
			MenuOperation[playerid] = 144;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO *** выбор транспорта по вместимости бака", "Введите нижний предел диапазона вместимости бака. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выбор транспорта по вместимости бака",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 146)
	{
		if(!strlen(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 17)
		{
			MenuOperation[playerid] = 146;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите требуемый уровень транспорта (1-17).\
\n{8CAA63}Примечание:\
\n\t- Вы не сможете купить транспорт выше чем ваш уровень.\
\n\tПо окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		SetPVarInt(playerid, "Level", strval(inputtext));

		new ind = 0;//счётчик найденных по данной категории
		new listitems[35*20];
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
		    if(VehicleArray[i][Level] == GetPVarInt(playerid, "Level"))
		    {
				//format(strcmd, sizeof(strcmd), "%s[%d]: $%d", PlayerName(i), i, money);
            	//SendClientMessage(playerid, COLOR_GREEN, strcmd);
            	ind ++;
 		    	if(ind > 20) break;
				strcat(listitems, VehicleArray[i][Vehicle_Name]);
				strcat(listitems, "\n");
				//SetPVarInt(playerid, "CarLine", i);
		    }
		}
		if(!strlen(listitems))
		{//если ни чего не нашли
			MenuOperation[playerid] = 146;
			ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите требуемый уровень транспорта (1-17).\
\n{8CAA63}Примечание:\
\n\t- Вы не сможете купить транспорт выше чем ваш уровень.\
\n\tПо окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		MenuOperation[playerid] = 145;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_LIST, "*** CAR INFO *** выбор транспорта по уровню",listitems, "OK", "Cancel");
	}
	else if(MenuOperation[playerid] == 145)
	{//*** CAR INFO *** выберите транспорт
		if(!response)
		{
			CarInfo(playerid);
			return 1;
		}

	    new modelid_line = -1;
		for(new i=0; i<212; i++)//sizeof(VehicleArray)
		{
	        if( !strcmp(inputtext, VehicleArray[i][Vehicle_Name], true) )
	        {
				modelid_line = i;
  				break;
   			}
		}
#if defined vw_changer//#endif
	#define DIALOG_WIDTH2    	145.0
	#define DIALOG_HEIGHT2   	145.0
		new Float:BaseX = 320.0 - DIALOG_WIDTH2/2.0;
		new Float:BaseY = 240.0 - (DIALOG_HEIGHT2 + DIALOG_HEIGHT2/2.0) + 7.0;
		gSelectionItems[playerid][0] = CreateModelPreviewTextDraw(playerid, 400+modelid_line, BaseX, BaseY, DIALOG_WIDTH2, DIALOG_HEIGHT2);
#endif

		new msgitem[526];//360 + 32+20+20 + 10+3+6 + 6+4+5 + 60 = 526
	    format(msgitem, sizeof(msgitem), "{0080FF}Прототип: {FFFFFF}%s\
\n{0080FF}Категория: {FFFFFF}%s\
\n{0080FF}Тюн: {FFFFFF}%s {0080FF}Уровень: {FFFFFF}%d\
\n{0080FF}Цена: {33AA33}$%d {0080FF}Мест: {FFFFFF}%d\
\n{0080FF}Бак: {FFFFFF}%d л {0080FF}Скорость: {FFFFFF}%d км/ч\
\n{0080FF}Расход:{FFFFFF}%d л/100км {0080FF}Грузоподъёмность: {FFFFFF}%d кг\
\n\n{AFAFAF}Нажмите Accept, чтобы принять.",
				VehicleArray[modelid_line][Prototype],
				GetCarCategory(modelid_line),
				GetCarModifications(modelid_line),
				VehicleArray[modelid_line][Level],
				VehicleArray[modelid_line][Virtual_Price],
				VehicleArray[modelid_line][SeatID],
				VehicleArray[modelid_line][GasMax],
				VehicleArray[modelid_line][LineSpeed],
				VehicleArray[modelid_line][fuelConsumption],
				VehicleArray[modelid_line][Weight]/2);
		strcat(msgitem, "\n{AFAFAF}_________________________________________________");
		new caption[32+10];
	    format(caption, sizeof(caption), "%s[modelid: %d]", VehicleArray[modelid_line][Vehicle_Name], VehicleArray[modelid_line][ModelID]);
		if( IsPlayerInRangeOfPoint(playerid, 2.0, -1663.8074,1207.7589,7.2546)
		|| IsPlayerInRangeOfPoint(playerid, 2.0, 415.6489,2533.6672,19.1484)
		|| IsPlayerInRangeOfPoint(playerid, 2.0, 718.5229,-1476.4646,5.4688) )
		{
			SetPVarInt(playerid, "ModelID", VehicleArray[modelid_line][ModelID]);
			ShowPlayerDialogGap(playerid, AutoSalon_DIALOG, DIALOG_STYLE_MSGBOX, caption, msgitem, "Accept", "Cancel");
		}
		else
		{
			ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, msgitem, "Accept", "Cancel");
		}
		//return VehicleArray[modelid_line][ModelID];
	}
	return 1;
}


stock AutoSalon_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != AutoSalon_DIALOG) return 1;
	if(!response) return 1;
	new msgitem[336];//53+49+76+44   +32+3+10 + 6+3+6+3 + 51 = 336
//new giveplayerid;
//для покупки авто
//ShowPlayerDialogGap(playerid, DialogID[playerid][0], DIALOG_STYLE_MSGBOX, caption, msgitem, "Accept", "Cancel");
//new modelid = strval(inputtext);
	new modelid = GetPVarInt(playerid, "ModelID");
	//new modelid = CarInfo(playerid, dialogid, response, listitem, inputtext);
	if(modelid < 400 || modelid > 611)
	{
		SendClientMessage(playerid, COLOR_GREY, "   ID Модели Транспорта не может быть ниже 400 или выше 611 !");
		MenuOperation[playerid] = 137;
		ShowPlayerDialogGap(playerid, CARINFO_DIALOG, DIALOG_STYLE_INPUT, "*** CAR INFO ***", "Введите номер модели от 400 до 611. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		return 1;
	}
	if(modelid == 460 || modelid == 539)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Этот Транспорт забагован при соприкосновении с водой !");
		CarInfo(playerid);
		return 1;
	}
	if(	VehicleArray[modelid-400][Category] == Rail_Transport ||
		//VehicleArray[modelid-400][Category] == Trailers ||
		VehicleArray[modelid-400][Category] == Not_Used ||
		VehicleArray[modelid-400][Category] == RC_Vehicles ||
		modelid == 406 || modelid == 532)
	{   //"Dumper",Industrial
		SendClientMessage(playerid, COLOR_GREY, "   Этот транспорт запрещён к продаже !");
		CarInfo(playerid);
		return 1;
	}
	//----------------------------------------------------------------------
   	if(!IsPlayerInRangeOfPoint(playerid, 5.0,415.6489,2533.6672,19.1484) &&
		VehicleArray[modelid-400][Category] == Airplane )
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться на Заброшенном Аэро !");
		CarInfo(playerid);
		return 1;
	}
    	else if(!IsPlayerInRangeOfPoint(playerid, 5.0,415.6489,2533.6672,19.1484) &&
		VehicleArray[modelid-400][Category] == Helicopters )
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться на Заброшенном Аэро !");
		CarInfo(playerid);
		return 1;
	}
    	else if(!IsPlayerInRangeOfPoint(playerid, 5.0,718.5229,-1476.4646,5.4688) &&
	 	VehicleArray[modelid-400][Category] == Boats)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться на Лодочной станции TR !");
		CarInfo(playerid);
		return 1;
	}
	//----------------------------------------------------------------------
	if( (modelid==427 || modelid==430 || modelid==472 || modelid==490 ||
		modelid==497 || modelid==523 || modelid==528 ||
		(modelid>=596&&modelid<=599) || modelid==601) && !IsACop(playerid) && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить транспорт полиции!");
		CarInfo(playerid);
		return 1;
	}
  	else if( (modelid==425 || modelid==432 || modelid==433 || modelid==470 ||
		modelid==520 || modelid==548 || modelid==595) && PlayerInfo[playerid][pMember] != DoD && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить военную технику!");
		CarInfo(playerid);
		return 1;
	}
   	else if( (modelid==416 || modelid==447 || modelid==563 || modelid==407 || modelid==544) &&
	 	PlayerInfo[playerid][pMember] != DoH && PlayerInfo[playerid][pJob] != FIREMAN && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить спасательную технику!");
		CarInfo(playerid);
		return 1;
	}
   	else if( (modelid==488 || modelid==582) && PlayerInfo[playerid][pMember] != SAN && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить транспорт Агества Новостей!");
		CarInfo(playerid);
		return 1;
	}
	else if(modelid == 405 && PlayerInfo[playerid][pMember] != DoE && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить транспорт школы вождения!");
		CarInfo(playerid);
		return 1;
	}
   	else if(modelid == 552 && PlayerInfo[playerid][pJob] != ROADWORKER && PlayerInfo[playerid][pJob] != TRUCKER && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить ремонто-дорожный транспорт!");
		CarInfo(playerid);
		return 1;
	}
   	else if(modelid == 525 && PlayerInfo[playerid][pJob] != CARMECHANIC && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить буксир!");
		CarInfo(playerid);
		return 1;
	}
   	else if( (modelid == 428) && PlayerInfo[playerid][pJob] != INKASSATOR && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить служебный транспорт!");
		CarInfo(playerid);
		return 1;
	}
   	else if( (modelid == 420 || modelid == 438) && PlayerInfo[playerid][pJob] != TAXIDRIVER && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить служебный транспорт!");
		CarInfo(playerid);
		return 1;
	}
   	else if( (modelid == 431 || modelid == 437) && PlayerInfo[playerid][pJob] != BUSDRIVER && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить служебный транспорт!");
		CarInfo(playerid);
		return 1;
	}
   	else if( (modelid == 403 || modelid == 514 || modelid == 515) && PlayerInfo[playerid][pJob] != TRUCKER && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить тягач!");
		CarInfo(playerid);
		return 1;
	}
   	else if(modelid == 514 && PlayerInfo[playerid][pJob] == TRUCKER && PlayerInfo[playerid][pTruckSkill] < 50 && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы пока не можете купить данный тягач!");
		CarInfo(playerid);
		return 1;
	}
   	else if(modelid == 515 && PlayerInfo[playerid][pJob] == TRUCKER && PlayerInfo[playerid][pTruckSkill] < 400 && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы пока не можете купить данный тягач!");
		CarInfo(playerid);
		return 1;
	}
	//----------------------------------------------------------------------
	new color1 = random(127);
	new color2 = random(127);
	//----------------------------------------------------------------------
	//CarPrice[playerid] = VehicleArray[modelid-400][Virtual_Price]*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])/(2+2);
	CarPrice[playerid] = VehicleArray[modelid-400][Virtual_Price];
	if(GetPlayerMoneyH(playerid) < CarPrice[playerid])
	{
		format(msgitem, sizeof(msgitem), "   У вас не достаточно денег на руках. Цена автомобиля: $%d !", CarPrice[playerid]);
		SendClientMessage(playerid, COLOR_GREY, msgitem);
		CarPrice[playerid] = 0;
		CarInfo(playerid);
		return 1;
	}
	//----------------------------------------------------------------------
	if(	MyCar[playerid][0] != 0 &&
		MyCar[playerid][1] != 0 &&
		MyCar[playerid][2] != 0)
    {
        SendClientMessage(playerid, COLOR_GREY, "   Вы уже имеете максимальное кол-во транспортных средств !");
        return 1;
    }
   	if(VehicleArray[modelid-400][Level] > PlayerInfo[playerid][pLevel])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить транспорт выше своего уровня!");
		CarInfo(playerid);
		return 1;
	}
    //format(msgitem, sizeof(msgitem), "* Вы решили купить %s за $%d?", VehicleArray[modelid-400][Vehicle_Name], VehicleArray[modelid-400][Virtual_Price]);
	//SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	Offer[playerid] = playerid;
	CarModel[playerid] = modelid;
	CarColor1[playerid] = color1;
	CarColor2[playerid] = color2;
	//new msgitem[336];//53+49+76+44   +32+3+10 + 6+3+6+3 + 51 = 336
	format(msgitem, sizeof(msgitem), "{0080FF}Ваш автомобиль {FFFFFF}%s{0080FF} доставлен\
\n[modelid: {FFFFFF}%d{0080FF}] за {33AA33}$%d.\
\n{%06x}Основной цвет - {FFFFFF}%d. {%06x}Дополнительный цвет - {FFFFFF}%d\
\n\n{AFAFAF}Нажмите Accept, чтобы оплатить.",
			VehicleArray[modelid-400][Vehicle_Name],modelid,CarPrice[playerid],
			VehicleColor[color1] >>> 72,color1,VehicleColor[color2] >>> 72,color2);
	strcat(msgitem, "\n{AFAFAF}_________________________________________________");
	MenuOperation[playerid] = 12;
	ShowPlayerDialogGap(playerid, ACCEPT_DIALOG, DIALOG_STYLE_MSGBOX, "Автодилер", msgitem, "Accept", "Cancel");
	return 1;
}
