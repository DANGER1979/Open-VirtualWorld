//http://www.samp-rus.com/forum/31-22428-1
//Новая экономика

//БИРЖА - возможность выставить свой товар на продажу или сделать заявку на покупку сырья
//для экономики
enum demands_info
{//список заявок для биржи
	dOwned,//кто выставил заявку
	dOperation,//0-выполнена или стёк срок, 1-продажа, 2-покупка
	dType[2],//1. Металл:	2. Текстиль:	3. Продовольствие	4. Древесина	5. Нефть	6. Товар:
	dAmount[2],//кол-во
	Float: dPrice[2],//цена
	dPeriod[2],//время
}
new Demand[MAX_BIZ][demands_info];


stock EXCHANGE(playerid)
{
	new bizid = GetPVarInt(playerid, "Bouse");
    new caption[14+24+4];
	format(caption, sizeof(caption), "БИРЖА. %s[%d]", 	BizInfo[bizid][bDiscription], bizid);
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_LIST, caption, "\n1. Заявки продавцов\n2. Заявки покупателей\n3. Продать\n4. Купить", "OK", "Назад");
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
	{//выйти из диалога БИРЖА и перейти в диалог МЕНЮ УПРАВЛЕНИЯ
		//PlaySoundForPlayer(playerid, SOUND_BEE_TRACK_STOP);
		//SetPVarInt(playerid, "Bouse", FREEROAM);
		biz_ControlMenu(playerid, GetPVarInt(playerid, "Bouse") );
		return 1;
	}
	new bouse = GetPVarInt(playerid, "Bouse");
//==============================================================================
	if(MenuOperation[playerid] == 147)//БИРЖА
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		//new msgitem[28 + 6*(24 + 2+20+24+24+3)];
	    if(listitem == 0)//1. Заявки продавцов Sellers ' requests
	    {
	    	SetPVarInt(playerid, "TypeOperation", 1);
    	 	MenuOperation[playerid] = 150;
	    	Proposal(playerid, bouse);
	    }
	    else if(listitem == 1)//2. Заявки покупателей //Customer requests
	    {
	    	SetPVarInt(playerid, "TypeOperation", 2);
 	   		MenuOperation[playerid] = 150;
	    	Proposal(playerid, bouse);
	    }
	    else if(listitem == 2)//3. Продать
	    {
	        SetPVarInt(playerid, "TypeOperation", 1);
	        MenuOperation[playerid] = 152;
	        SelectTypeMaterial(playerid, bouse);
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"),	GetPVarInt(playerid, "Volume"));
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	    }
	    else if(listitem == 3)//4. Купить
	    {
	    	SetPVarInt(playerid, "TypeOperation", 2);
	    	MenuOperation[playerid] = 152;
	    	SelectTypeMaterial(playerid, bouse);
	    }
	}
	//--------------------------------------------------------------------------
//начало просмотра заявок
	else if(MenuOperation[playerid] == 150)//1. Заявки продавцов //2. Заявки покупателей
	{
		if(!response)
		{//если нажали назад в менюшке //1. Заявки продавцов //2. Заявки покупателей
			MenuOperation[playerid] = 147;
			EXCHANGE(playerid);
			return 1;
		}
		MenuOperation[playerid] = 151;
		PlayerDemands(playerid, bouse, listitem);//отобразить заявки согласно TypeOperation
	}
	else if(MenuOperation[playerid] == 151)
	{
		if(!response)
		{//если отказались от выбора в менюшке  //1. Заявки продавцов //2. Заявки покупателей
		   	MenuOperation[playerid] = 150;
	    	Proposal(playerid, bouse);
			return 1;
		}
//обрабатываем заявки
//но пока мы можем только смотреть и делать встречную покупку
	}
//конец просмотра заявок
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 152)//Продать//Купить
	{
		if(!response)
		{//если нажали назад в менюшке //3. Продать //4. Купить
			MenuOperation[playerid] = 147;
			EXCHANGE(playerid);
			return 1;
		}
		SetPVarInt(playerid, "TypeMaterial", listitem+1);//записываем выбор типа материала
		
	    new caption[28+24+3+16];
    	MenuOperation[playerid] = 153;
   		new typeOperation = GetPVarInt(playerid, "TypeOperation");
		if(typeOperation == 1)
		{
			format(caption, sizeof(caption), "%s[%d].Продажа на Склад - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
			ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "Введите Объем продажи: \n\nПо окончанию ввода нажмите Далее", "Далее", "Назад");
		}
		else if(typeOperation == 2)
		{
			format(caption, sizeof(caption), "%s[%d].Покупка со Склада - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
			ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "Введите Объем покупки: \n\nПо окончанию ввода нажмите Далее", "Далее", "Назад");
		}

//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"),	GetPVarInt(playerid, "Volume"));
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//stock EnterVolumeMaterial(playerid, bouse)

 	}
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 153)//Продать//Купить
	{//Введите Объем продажи/покупки
		if(!response)
		{//если нажали назад в менюшке
			MenuOperation[playerid] = 152;
			SelectTypeMaterial(playerid, bouse);
		    return 1;
		}
		MenuOperation[playerid] = 154;
		GetVolumeMaterial(playerid, bouse, inputtext);//, GetPVarInt(playerid, "TypeMaterial"));
		
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"),GetPVarInt(playerid, "Volume"));
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//SendClientMessageToAll(COLOR_GREY, strings);
	}
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 154)//Продать//Купить
	{//GetVolumeMaterial
		if(!response)
		{
			MenuOperation[playerid] = 153;
		    new caption[28+24+3+16];
		  	new typeOperation = GetPVarInt(playerid, "TypeOperation");
			if(typeOperation == 1)
			{
				format(caption, sizeof(caption), "%s[%d].Продажа на Склад - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(GetPVarInt(playerid, "TypeMaterial")) );
				ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "Введите Объем продажи: \n\nПо окончанию ввода нажмите Далее", "Далее", "Назад");
			}
			else if(typeOperation == 2)
			{
				format(caption, sizeof(caption), "%s[%d].Покупка со Склада - %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(GetPVarInt(playerid, "TypeMaterial")) );
				ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, "Введите Объем покупки: \n\nПо окончанию ввода нажмите Далее", "Далее", "Назад");
			}
		    return 1;
		}
		MenuOperation[playerid] = 155;
		OrderIsAccepted(playerid, bouse, inputtext);
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "MenuOperation: %d, TypeOperation: %d, TypeMaterial: %d, Volume: %d, Price: %.2f",
//			MenuOperation[playerid], GetPVarInt(playerid, "TypeOperation"),GetPVarInt(playerid, "TypeMaterial"), GetPVarInt(playerid, "Volume"), GetPVarFloat(playerid, "Price") );
//SendClientMessageEx(playerid, COLOR_GREY, strings);
//SendClientMessageToAll(COLOR_GREY, strings);
	}
	//--------------------------------------------------------------------------
	else if(MenuOperation[playerid] == 155)
	{//Товар выставлен на продажу//Заказ принят
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
//начало просмотра заявок
stock Proposal(playerid, bouse)
{//выбор по какому типу будем просматривать
	#pragma unused bouse
	new caption[34];
	new typeOperation = GetPVarInt(playerid, "TypeOperation");
	if(typeOperation == 1) caption = "Заявки продавцов. Выберите тип.";
	else if(typeOperation == 2) caption = "Заявки покупателей. Выберите тип.";

   	new msgitem[28+6*(24+2+20+24+24+24)];
	strcat(msgitem, "№\tТип\tОтрасль\tГрузовик\n");
	for(new t = 1; t <= 6; t++)
	{
		format(msgitem, sizeof(msgitem),   "%s%d.\t%s\t%s\t%s[%d]\n",
			msgitem, t, TypeCargo(t), TypeBranch(t), VehicleArray[GetTruckType(t)-400][Vehicle_Name], GetTruckType(t));
	}
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, msgitem, "OK", "Назад");
}
stock PlayerDemands(playerid, bouse, listitem)//Заявки продавцов и покупателей
{
	//#pragma unused bouse
	//new material[] = TypeCargo(listitem+1);
    //--------------------------------------------------------------------------
	new ind;
	new bigmsgitem[41+10*(35+10+6+6+4)];
	new typeOperation = GetPVarInt(playerid, "TypeOperation")-1;
	new typeMaterial = listitem+1;//GetPVarInt(playerid, "TypeMaterial");
	
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "PlayerDemands(typeOperation: %d, typeMaterial: %d)", typeOperation+1, typeMaterial);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	
	strcat(bigmsgitem, "Кол-во\tЦена за шт.\tИтого\tИстекает\n");
	for(new b = 1; b < MAX_BIZ; b++)
	{
		if(ind > 10) break;
		//if(Demand[b][dOwned] == 0) continue;//сканируем только заявки от купленных бизов
		if(Demand[b][dOperation] != typeOperation) continue;//сканируем все бизы с операцией что мы выбрали
		if(Demand[b][dType][typeOperation] != typeMaterial) continue;//сканируем все бизы с типами материалов по данномы выбронному пункту
		if(Demand[b][dAmount][typeOperation] <= 0) continue;//сканируем все бизы c выставленным кол-ом больше 0

		format(bigmsgitem, sizeof(bigmsgitem), "%s%d кг\t%.1f $\t%d $\t%d мин\n", bigmsgitem,
			Demand[b][dAmount][typeOperation],
			Demand[b][dPrice][typeOperation],
			floatround(Demand[b][dAmount][typeOperation]*Demand[b][dPrice][typeOperation]),
			Demand[b][dPeriod][typeOperation]);
		ind++;
		
//ИНФОРМИРОВАНИЕ
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
		//ИНФОРМИРОВАНИЕ
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
	if(typeOperation == 0) format(caption, sizeof(caption), "%s[%d]. Заявки продавцов: %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
	else if(typeOperation == 1) format(caption, sizeof(caption), "%s[%d]. Заявки покупателей: %s", BizInfo[bouse][bDiscription], bouse, TypeCargo(listitem+1));
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, bigmsgitem, "OK", "Назад");

//SendClientMessageToAll(COLOR_GREY, strings);
    return 1;
}//конец просмотра заявок
//==============================================================================
//начало подачи заявки
stock SelectTypeMaterial(playerid, bouse)
{
	new msgitem[148+6*10];
	strcat(msgitem, "Тип\tНа складе\tНа общем складе\n");
	
	format(msgitem, sizeof(msgitem),"%s1. Металл:\t%d\t%d\n\
									2. Текстиль:\t%d\t%d\n\
									3. Продовольствие:\t%d\t%d\n\
									4. Древесина:\t%d\t%d\n\
									5. Нефть:\t%d\t%d\n\
									6. Товар:\t%d\t%d",msgitem,
		BizInfo[bouse][bMetal],BizInfo[80][bMetal],
		BizInfo[bouse][bTextiles],BizInfo[80][bTextiles],
		BizInfo[bouse][bProvisions],BizInfo[80][bProvisions],
		BizInfo[bouse][bTree],BizInfo[80][bTree],
		BizInfo[bouse][bFuel],BizInfo[80][bFuel],
		BizInfo[bouse][bProducts],BizInfo[80][bProducts]);
		
	new caption[50+20+3];
	if(GetPVarInt(playerid, "TypeOperation") == 1) format(caption, sizeof(caption), "%s[%d]. Продажа на Склад. Выберите тип материала", BizInfo[bouse][bDiscription], bouse);
	else format(caption, sizeof(caption), "%s[%d]. Покупка со Склада. Выберите тип материала", BizInfo[bouse][bDiscription], bouse);
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, msgitem, "OK", "Назад");
}


stock GetVolumeMaterial(playerid, bouse, inputtext[])//, typematerial)
{//диалог ввода кол-ва, объема продажи или покупки
	new typeOperation = GetPVarInt(playerid, "TypeOperation");//покупка или продажа
	new typeMaterial = GetPVarInt(playerid, "TypeMaterial");//1-6
	new Volume = strval(inputtext);	SetPVarInt(playerid, "Volume", Volume);

	new Spares = GetProducts(bouse);//запас
	new MarketValue = GetMarketValue(typeMaterial);//рыночная стоимость

	new branch[24];
    strmid(branch, TypeBranch(typeMaterial), 0, 24, 255);

    new material[20];
    strmid(material, TypeCargo(typeMaterial), 0, 24, 255);

    new bigmsgitem[41+(33*10)];
	if(typeMaterial == 6)
	{
		format(bigmsgitem, sizeof(bigmsgitem), "Название товара: %s[%d]", material, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\nОтрасль: %s[%d]", bigmsgitem, branch, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\nУровень продукции: %s", bigmsgitem, "Обычный");
		format(bigmsgitem, sizeof(bigmsgitem), "%s\nСкладские запасы: %d кг", bigmsgitem, Spares);

		if(typeOperation == 1) format(bigmsgitem, sizeof(bigmsgitem), "%s\nОбъем продажи: %d", bigmsgitem, Volume);
		else if(typeOperation == 2) format(bigmsgitem, sizeof(bigmsgitem), "%s\nОбъем закупки: %d", bigmsgitem, Volume);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n\nРыночная стоимость: $%d. \nКомиссионные бирже: %d %%", bigmsgitem, MarketValue, 1);

		//format(bigmsgitem, sizeof(bigmsgitem), "%s\nОсобые эффекты: Повышает доход магазина на %d%", bigmsgitem, 25);
		//strcat(bigmsgitem, "\nОписание товара:	Дешевая продукция, \nзабракованная контролем качества, \nи проданная заводом-изготовителем \nв обход госконтроля.");
		//if(typeOperation == 1) strcat(bigmsgitem, "\nРынок сбыта: Продать игрокам,Продать системе");
		if(typeOperation == 1)
		{
			strcat(bigmsgitem, "\nПодсказка: Указав цену продажи ниже рыночной, \nвы сможете быстрее продать свой товар.");
			strcat(bigmsgitem, "\n\nВведите Стоимость:");
		}
		else if(typeOperation == 2)
		{
			strcat(bigmsgitem, "\nПодсказка:Если вы предложите \nзакупочную цену выше рыночной, \nто сможете быстрее купить нужный вам товар.");
			strcat(bigmsgitem, "\nВведите закупочную цену за штуку:");
		}
	}
	else
	{
		format(bigmsgitem, sizeof(bigmsgitem), "Название сырья: %s[%d]", material, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\nОтрасль: %s[%d]", bigmsgitem, branch, typeMaterial);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\nСкладские запасы: %d", bigmsgitem, Spares);
		if(typeOperation == 1) format(bigmsgitem, sizeof(bigmsgitem), "%s\nОбъем продажи: %d", bigmsgitem, Volume);
		else if(typeOperation == 2) format(bigmsgitem, sizeof(bigmsgitem), "%s\nОбъем покупки: %d", bigmsgitem, Volume);
		format(bigmsgitem, sizeof(bigmsgitem), "%s\n\nРыночная стоимость: $%d. \nКомиссионные бирже: %d %%", bigmsgitem, MarketValue, 1);
		if(typeOperation == 1)
		{
			strcat(bigmsgitem, "\nПодсказка: Указав цену продажи ниже рыночной, \nвы сможете быстрее продать свой товар.");
			strcat(bigmsgitem, "\n\nВведите Стоимость:");
		}
		else if(typeOperation == 2)
		{
			strcat(bigmsgitem, "\nПодсказка:Если вы предложите \nзакупочную цену выше рыночной, \nто сможете быстрее купить нужный вам товар.");
			strcat(bigmsgitem, "\n\nВведите закупочную цену за штуку:");
		}
	}
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: Покупка/Продажа со Склада by %s[%d], strlen: %d, sizeof: %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	
    new caption[44+24+3];
	if(typeOperation == 1)
	{
		format(caption, sizeof(caption), "%s[%d]. Продажа на Склад - %s", BizInfo[bouse][bDiscription], bouse, material );
		ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, bigmsgitem, "Продать", "Назад");
	}
	else if(typeOperation == 2)
	{
		format(caption, sizeof(caption), "%s[%d]. Покупка со Склада - %s", BizInfo[bouse][bDiscription], bouse, material );
		ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_INPUT, caption, bigmsgitem, "Купить", "Назад");
	}
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "GetVolumeMaterial(typeOperation: %d, typeMaterial: %d, Volume: %d)", typeOperation, typeMaterial, Volume);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	return 1;
}


//Заявка принята
stock OrderIsAccepted(playerid, bouse, inputtext[])
{//ввели цену
	new typeOperation = GetPVarInt(playerid, "TypeOperation")-1;//-1 т.к. массив начинается от нуля
	new typeMaterial = GetPVarInt(playerid, "TypeMaterial");
	new Volume = GetPVarInt(playerid, "Volume");
	new Float: price = strval(inputtext);
	SetPVarFloat(playerid, "Price", price); //SetPVarInt(playerid, "Price", price);

	/*if(typeOperation == 1)
	{
		BizInfo[bouse][bTill] += price;
	    if(typeMaterial == 1)//1. Металл
	    {
			BizInfo[bouse][bMetal] -= Volume;
	    }
	    else if(typeMaterial == 2)//2. Текстиль
	    {
			BizInfo[bouse][bTextiles] -= Volume;
	    }
	    else if(typeMaterial == 3)//3. Продовольствие
	    {
			BizInfo[bouse][bProvisions] -= Volume;
	    }
	    else if(typeMaterial == 4)//4. Древесина
	    {
			BizInfo[bouse][bTree] -= Volume;
	    }
	    else if(typeMaterial == 5)//5. Нефть
	    {
			BizInfo[bouse][bFuel] -= Volume;
	    }
	    else if(typeMaterial == 6)//6. Товар
	    {
			BizInfo[bouse][bProducts] -= Volume;
	    }
	}
	else if(typeOperation == 2)
	{
		BizInfo[bouse][bTill] -= price;
	    if(typeMaterial == 1)//1. Металл
	    {
			BizInfo[bouse][bMetal] += Volume;
	    }
	    else if(typeMaterial == 2)//2. Текстиль
	    {
			BizInfo[bouse][bTextiles] += Volume;
	    }
	    else if(typeMaterial == 3)//3. Продовольствие
	    {
			BizInfo[bouse][bProvisions] += Volume;
	    }
	    else if(typeMaterial == 4)//4. Древесина
	    {
			BizInfo[bouse][bTree] += Volume;
	    }
	    else if(typeMaterial == 5)//5. Нефть
	    {
			BizInfo[bouse][bFuel] += Volume;
	    }
	    else if(typeMaterial == 6)//6. Товар
	    {
			BizInfo[bouse][bProducts] += Volume;
	    }
	}*/
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "OrderIsAccepted(typeOperation: %d, typeMaterial: %d, Volume: %d, price: %d)", typeOperation+1, typeMaterial, Volume, price);
//SendClientMessageEx(playerid, COLOR_GREY, strings);

//формируем заявку от данного биза
	Demand[bouse][dOwned] = BizInfo[bouse][bOwned];//bиз куплен
	Demand[bouse][dOperation] = typeOperation;//указываем что данная заявка на продаже или по покупке
	Demand[bouse][dType][typeOperation] = typeMaterial;
	Demand[bouse][dAmount][typeOperation] = Volume;
	Demand[bouse][dPrice][typeOperation] = price;
	Demand[bouse][dPeriod][typeOperation] = 1140;//1440 минут //24 часа;
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "OrderIsAccepted(Owned: %d, Operation: %d, Type: %d, Amount: %d, Price: %.2f, Period: %d)",
//	Demand[bouse][dOwned], typeOperation+1, Demand[bouse][dType][typeOperation], Demand[bouse][dAmount][typeOperation],
//	Demand[bouse][dPrice][typeOperation], Demand[bouse][dPeriod][typeOperation]);
//SendClientMessageEx(playerid, COLOR_GREY, strings);
	new msgitem[66+20+10+10];
	if(typeOperation == 0)
	{
		format(msgitem, sizeof(msgitem), "%s выставлен на продажу.\n\nСумма сделки: $%.1f \nПродажа %d кг.", TypeCargo(typeMaterial), price, Volume);
	}
	else if(typeOperation == 1)
	{
		format(msgitem, sizeof(msgitem), "Заказ %s принят.\n\nСумма сделки: $%.1f \nПокупка %d кг.", TypeCargo(typeMaterial), price, Volume);
	}
    new caption[35+24+3];
	format(caption, sizeof(caption), "%s[%d]", BizInfo[bouse][bDiscription], bouse);
	ShowPlayerDialogGap(playerid, EXCHANGE_DIALOG, DIALOG_STYLE_MSGBOX, caption, msgitem, "OK", "");
}
