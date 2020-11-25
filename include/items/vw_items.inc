//https://gta.fandom.com/ru/wiki/Didier_Sachs

//==============================================================================
stock Items(playerid)
{
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
 	/*if(	gPlayerBoxing[playerid] == 1 ||
	 	gInTerrorsCount[playerid] || gInCTerrorsCount[playerid])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вам пока запрещено данное меню !");
		return 1;
	}*/
	//new strings[MAX_STRING];
   	new bigmsgitem[2234];//20*70 = 1400
    new strtmp[70+16];//, text1[70+16], sGun[9+32+100];
	new DialogIDCounter = 0; for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;
	strcat(bigmsgitem, "№\tНаименование\tКол-во\n");

	format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Денег: \t{33AA33}$%d\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pCash]);
 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
	DialogID[playerid][0] = DialogIDCounter;
	DialogIDCounter ++;

    if(PlayerInfo[giveplayerid][pGPS] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}GPS-Навигатор\n", DialogIDCounter+1);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][1] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pDrugs] > 0)
    {
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Наркотики: \t{00FF00}%d г\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pDrugs]);
	 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
	 	DialogID[playerid][2] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pCigars] > 0)
    {
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Сигары: \t{00FF00}%d шт\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pCigars]);
 		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
 		DialogID[playerid][3] = DialogIDCounter;
 		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pDice] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Игральные кости\n", DialogIDCounter+1);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][4] = DialogIDCounter;
		DialogIDCounter ++;
	}
	if(PlayerInfo[giveplayerid][pFuel] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Канистра 20л: \t{00FF00}%d шт\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pFuel]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][5] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pCDPlayer] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Радио\n", DialogIDCounter+1);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][6] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(Groceries[giveplayerid][gChickens] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Цыпленок: \t{00FF00}%d шт\n", DialogIDCounter+1, Groceries[giveplayerid][gChickens]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][7] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(Groceries[giveplayerid][gHamburgers] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Гамбургер: \t{00FF00}%d шт\n", DialogIDCounter+1, Groceries[giveplayerid][gHamburgers]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][8] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(Groceries[giveplayerid][gPizzas] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Пицца: \t{00FF00}%d шт\n", DialogIDCounter+1, Groceries[giveplayerid][gPizzas]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][9] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(Groceries[giveplayerid][gBeer] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Пиво: \t{00FF00}%d бутылок\n", DialogIDCounter+1, Groceries[giveplayerid][gBeer]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][10] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(VehInfo[LastCar[giveplayerid]][cInsur] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Доставок Транспорта: {00FF00}%d раз\n", DialogIDCounter+1, VehInfo[LastCar[giveplayerid]][cInsur]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][11] = DialogIDCounter;
		DialogIDCounter ++;
	}
	//для попугая
    /*if(pHasParrot[playerid] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{00FF00}Crazy Parrot\n", DialogIDCounter+1);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][11] = DialogIDCounter;
		DialogIDCounter ++;
	}*/
	//--------------------------------------------------------------------------
	if(PlayerInfo[giveplayerid][pMats] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Материалов: \t{00FF00}%d\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pMats]);
	 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][12] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(Fishes[giveplayerid][pWeight][0] > 0 || Fishes[giveplayerid][pWeight][1] > 0
	|| Fishes[giveplayerid][pWeight][2] > 0 || Fishes[giveplayerid][pWeight][3] > 0
	|| Fishes[giveplayerid][pWeight][4] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Рыбы: \t{00FF00}%d кг\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pFishes]);
	 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
	 	DialogID[playerid][13] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pMushroom] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Грибов: \t{00FF00}%d кг\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pMushroom]);
	 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
	 	DialogID[playerid][14] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pLottoNr] > 0)
    {
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Лотерейка: \t{00FF00}№%d\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pLottoNr]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][15] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pHelmet] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Шлем: \t{00FF00}%d\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pHelmet]);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][16] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(GetPVarInt(playerid, "SkeletonKey") > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Отмычек: \t{00FF00}%d\n", DialogIDCounter+1, GetPVarInt(giveplayerid, "SkeletonKey"));
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][17] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pAntiradar] > 0)
	{
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Антирадар\n", DialogIDCounter+1);
		strins(bigmsgitem, strtmp, strlen(bigmsgitem));
		DialogID[playerid][18] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pPnumber] > 1000)
    {
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Телефон: \t{00FF00}%d\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pPnumber]);
	 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
	 	DialogID[playerid][19] = DialogIDCounter;
		DialogIDCounter ++;
	}
    if(PlayerInfo[giveplayerid][pAdrenalin] > 0)
    {
		format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}Адреналин: \t{00FF00}%d\n", DialogIDCounter+1, PlayerInfo[giveplayerid][pAdrenalin]);
	 	strins(bigmsgitem, strtmp, strlen(bigmsgitem));
	 	DialogID[playerid][20] = DialogIDCounter;
		DialogIDCounter ++;
	}
	new weapons[12], ammo;
	for(new slot=1; slot<=9; slot++)
	{
		GetPlayerWeaponData(giveplayerid, slot, weapons[slot], ammo);
		if(ammo > 0)
		{
			format(strtmp, sizeof(strtmp), "{FFFFFF}%d: \t{0080FF}%s[{00FF00}%d{0080FF}]\n", DialogIDCounter+1, WeaponName(weapons[slot]), ammo);
			strins(bigmsgitem, strtmp, strlen(bigmsgitem));
			DialogID[playerid][(20+slot)] = DialogIDCounter;
			DialogIDCounter ++;
		}
	}
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		format(strtmp, sizeof(strtmp), "Error: Items by %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strtmp);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Items пуст");//COLOR_BLUEGREY
		help_OnPlayerKeyStateChange(playerid);
		return 1;
	}
	new caption[29+MAX_PLAYER_NAME+3+3+3];
    format(caption, sizeof(caption), "Рюкзак %s[%d] загружен %d/%d", PlayerName(giveplayerid), giveplayerid, DialogIDCounter, MAX_DLGITEMS);
	ShowPlayerDialogGap(playerid, ITEMS_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, bigmsgitem, "OK", "Назад");
	return 1;
}
//==============================================================================

stock items_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{//ShowPlayerDialogGap(playerid, ITEMS_DIALOG, DIALOG_STYLE_LIST, caption, bigmsgitem, "OK", "Назад");
	#pragma unused inputtext
	//backPMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != ITEMS_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	for(new d=0; d<MAX_DLGITEMS; d++)
	{
		if(listitem == DialogID[playerid][d]) continue;//пропускаем выбранный пункт
		DialogID[playerid][d] = -1;//остальные освобождаем, чтобы знать с каким предметом работает игрок
	}
	
	new caption[70];
	if(listitem == 0)
	{   //"%d: \tMoney: \t$%d | Bank: $%d\n"
		//format(caption, sizeof(caption), "{FFFFFF}%d: Money: {33AA33}$%d", DialogID[playerid][0]+1, PlayerInfo[playerid][pCash]);
		return 1;
	}
	else if(listitem == DialogID[playerid][1])
	{ //if(!strcmp(cmd, "/gps", true) == 0 || strcmp(cmd, "/tp", true))
		gpsitem_help(playerid);//GPS(playerid);
		return 1;
	}
	else if(listitem == DialogID[playerid][2])// /drugs
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Наркотики: {FFFFFF}%d", listitem+1, PlayerInfo[playerid][pDrugs]);
	}
	else if(listitem == DialogID[playerid][3])
	{   //"%d: \tCigars: \t%d\n"
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Сигары: {FFFFFF}%d шт", listitem+1, PlayerInfo[playerid][pCigars]);
	}
	else if(listitem == DialogID[playerid][4])
	{   //8: \tИгральные кости\n
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Игральные кости: {FFFFFF}%d", listitem+1, PlayerInfo[playerid][pDice]);
	}
	else if(listitem == DialogID[playerid][5])
	{   //"%d: \tКанистра с топливом\n"
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Канистра с топливом: {FFFFFF}%d л", listitem+1, PlayerInfo[playerid][pFuel]);
	}
	else if(listitem == DialogID[playerid][6])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Радио", listitem+1);
		//return 1;
	}
	else if(listitem == DialogID[playerid][7])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Цыпленок: {FFFFFF}%d кг [%d шт]", listitem+1, Groceries[playerid][gChicken], Groceries[playerid][gChickens]);
	}
	else if(listitem == DialogID[playerid][8])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Гамбургер: {FFFFFF}%d кг [%d шт]", listitem+1, Groceries[playerid][gHamburger], Groceries[playerid][gHamburgers]);
	}
	else if(listitem == DialogID[playerid][9])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Пицца: {FFFFFF}%d кг [%d шт]", listitem+1, Groceries[playerid][gPizza], Groceries[playerid][gPizzas]);
	}
	else if(listitem == DialogID[playerid][10])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Пиво: {FFFFFF}%d бутылок", listitem+1, Groceries[playerid][gBeer]);
	}
	else if(listitem == DialogID[playerid][11])
	{   //callcar
		CallCar(playerid);
		return 1;
	}
	/*else if(listitem == DialogID[playerid][11])
	{   //для попугая
		if(pHasParrot[playerid] == 1)
		{
		    format(msgitem, sizeof(msgitem), "1.%s\n2.%s\n3.%s\n4.%s\n5.%s",
			pParrotSentence[playerid][0],
			pParrotSentence[playerid][1],
			pParrotSentence[playerid][2],
			pParrotSentence[playerid][3],
			pParrotSentence[playerid][4]);
			ShowPlayerDialogGap(playerid, DIALOG_ID_PARROT+1, DIALOG_STYLE_LIST, "Предложения попугая", msgitem, "Изменить", "Отмена");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "У вас нет {F70C47}говорящего попугая.");
		}
	}*/
	else if(listitem == DialogID[playerid][12])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: \t{0080FF}Materials: \t{00FF00}%d\n", listitem+1, PlayerInfo[playerid][pMats]);
	}
	else if(listitem == DialogID[playerid][13])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Рыбы: {FFFFFF}%d кг", listitem+1, PlayerInfo[playerid][pFishes]);
	}
	else if(listitem == DialogID[playerid][14])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Грибов: {FFFFFF}%d кг\n", listitem+1, PlayerInfo[playerid][pMushroom]);
	}
	else if(listitem == DialogID[playerid][15])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: \t{0080FF}Лотерейка: \t{00FF00}№%d\n", listitem+1, PlayerInfo[playerid][pLottoNr]);
	}
	else if(listitem == DialogID[playerid][16])
	{   //Шлем
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Шлем: {FFFFFF}%d", listitem+1, PlayerInfo[playerid][pHelmet]);
	}
	else if(listitem == DialogID[playerid][17])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: \t{0080FF}Отмычек: \t{00FF00}%d\n", listitem+1, GetPVarInt(playerid, "SkeletonKey"));
	}
	else if(listitem == DialogID[playerid][18])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: \t{0080FF}Антирадар\n", listitem+1, PlayerInfo[playerid][pAdrenalin]);
	}
	else if(listitem == DialogID[playerid][19])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: \t{0080FF}Phone: \t{00FF00}%d\n", listitem+1, PlayerInfo[playerid][pPnumber]);
	}
	else if(listitem == DialogID[playerid][20])
	{
		format(caption, sizeof(caption), "{FFFFFF}%d: {00FF00}Адреналина: {FFFFFF}%d шт\n", listitem+1, PlayerInfo[playerid][pAdrenalin]);
	}
	else
	{
		new weapons[12], ammo;
		for(new slot=1; slot<=9; slot++)
		{
			GetPlayerWeaponData(playerid, slot, weapons[slot], ammo);
			if(ammo > 0)
			{
				format(caption, sizeof(caption), "{FFFFFF}%d: \t{0080FF}%s[{00FF00}%d{0080FF}]\n", listitem+1, WeaponName(weapons[slot]), ammo);
			}
		}
	}
	ShowPlayerDialogEx(playerid, USEITEMS_DIALOG, DIALOG_STYLE_LIST, caption, "Использовать\nПередать\nВыбросить", "OK", "Cancel");
	return 1;
}
//==============================================================================
stock useitems_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{//ShowPlayerDialogEx(playerid, USEITEMS_DIALOG, DIALOG_STYLE_LIST, caption, "Использовать\nПередать\nВыбросить", "OK", "Cancel");
	#pragma unused inputtext
	//new giveplayerid;//giveplayerid = Offer[playerid]; //giveplayerid = ReturnUser(inputtext);
	if(dialogid != USEITEMS_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		Items(playerid);
		return 1;
	}
	new msgitem[256+1];
	new item = -1;
	for(new d=0; d<MAX_DLGITEMS; d++)
	{
		if(DialogID[playerid][d] == -1) continue;//пропускаем пустые
		item = d; break;
	}
	if(item == 1)//item == DialogID[playerid][1]
	{
		if(listitem == 0)
		{ //Использовать

		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали ...!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pGPS] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "... выкинуты!");
		}
	}
	else if(item == 2)
	{
		if(listitem == 0)
		{ //Использовать
			PlayerStoned[playerid] += 1/(PlayerInfo[playerid][pDrugPerk]+1);//Игрок Одурманенный наркотиком
			if(PlayerStoned[playerid] >= 5)
			{
				GameTextForPlayerEx(playerid, "~w~You are~n~~p~Stoned", 4000, 1);
			}
			new Float:health = LastHealth[playerid];
			//GetPlayerHealth(playerid, health);
			if(PlayerInfo[playerid][pDrugPerk] > 0)
			{
				new Float:hp = 2*PlayerInfo[playerid][pDrugPerk] + 20.0;
				if(health >= (150.0-hp))	{ SetPlayerHealthEx(playerid, 150); }
				else { SetPlayerHealthEx(playerid, (health+hp)); }
				SetPlayerDrunkLevel(playerid, PlayerStoned[playerid]*1000/PlayerInfo[playerid][pDrugPerk]);
			}
			else
			{
				if(health >= (150.0-20.0))	{ SetPlayerHealthEx(playerid, 150); }
					else { 	SetPlayerHealthEx(playerid, (health+20.0)); }
				SetPlayerDrunkLevel(playerid, PlayerStoned[playerid]*1000);
			}
			PlayerInfo[playerid][pDrugs] -= 2;
			SendClientMessage(playerid, COLOR_GREY, "   2 грамма наркотиков использовано !");
			if(PlayerInfo[playerid][pSTD] >= 2 && PlayerInfo[playerid][pSTD] <= 10)
			{
				PlayerInfo[playerid][pSTD] --;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* У вас увеличен иммунитет к болезня из-за приёма наркотиков !");
			}
			ApplyAnimation(playerid, "PED", "gum_eat",4.1,0,1,1,0,0);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Наркотики!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pDrugs] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Наркотики выкинуты!");
		}
	}
	else if(item == 3)
	{
		if(listitem == 0)
		{ //Использовать
			if(IsPlayerInAnyVehicle(playerid))
			{
				SendClientMessage(playerid, COLOR_GREY, "  Нельзя курить в транспортном средстве!");
				return 1;
			}
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				SendClientMessage(playerid, COLOR_GREY, "  Нельзя курить за рулём транспортного средства!");
				return 1;
			}
			if(PlayerInfo[playerid][pCigars] > 0)
			{
				PlayerInfo[playerid][pCigars] --;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
				LoopingAnim(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0); // Female Smoking
				//LoopingAnim(playerid, "SMOKING", "M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0); // Smoke
			}
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали сигары!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pCigars] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Сигары выкинуты!");
		}
	}
	else if(item == 4)
	{
		if(listitem == 0)
		{ //Использовать
			new dice = random(6)+1;
			format(msgitem, sizeof(msgitem), "* %s Бросил Кубик, на котором выпало %d", PlayerName(playerid),dice);
			ProxDetector(playerid, 5.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали кости!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pDice] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Кости выкинуты!");
		}
	}
	else if(item == 5)
	{
		if(listitem == 0)
		{ //Использовать
			FillCar(playerid);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали канистру!");
		}
		else if(listitem == 2)
		{//Выбросить
			if(PlayerInfo[playerid][pFuel] > 20)
			{
				PlayerInfo[playerid][pFuel] -= 20;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Канистра выкинута!");
			}
			else PlayerInfo[playerid][pFuel] = 0;
		}
	}
	else if(item == 6)
	{
		if(listitem == 0)
		{ //Использовать
			Radio(playerid);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали радио!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pGPS] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Радио выкинуто!");
		}
	}
	else if(item == 7)
	{
		if(listitem == 0)
		{ //Использовать
			//new Float:health = LastHealth[playerid];
		    //SetPlayerHealthEx(playerid, (health + Groceries[playerid][gChicken]));
		    format(strings, sizeof(strings), "* %s съел %d кг Цыплёнка.", PlayerName(playerid), Groceries[playerid][gChicken]);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		    format(strings, sizeof(strings), "* Вы съели Цыплёнка, и утолили голод на %d.", Groceries[playerid][gChicken]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			Groceries[playerid][gChickens] --;

			PlayerInfo[playerid][pParam1] -= Groceries[playerid][gChicken];
			if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
			if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);

			//SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);//2880//2703
			SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2769, Right_hand, 0.0299,0.0540,0.0900, 87.00,0.19,-92.09, 1.00,1.00,1.00);

			ApplyAnimation(playerid, "FOOD", "EAT_Chicken",3.0,0,1,1,0,0);
			SetTimerEx("StopAnimationEx", 5000, 0, "i", playerid);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Цыпленок!");
		}
		else if(listitem == 2)
		{//Выбросить
			Groceries[playerid][gChicken] = 0;
			Groceries[playerid][gChickens] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Цыплёнок выкинут!");
		}
	}
	else if(item == 8)
	{
		if(listitem == 0)
		{ //Использовать
			//new Float:health = LastHealth[playerid];
		    //SetPlayerHealthEx(playerid, (health + Groceries[playerid][gHamburger]));
		    format(strings, sizeof(strings), "* %s съел %d кг Гамбургера.", PlayerName(playerid), Groceries[playerid][gHamburger]);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		    format(strings, sizeof(strings), "* Вы съели Гамбургер, и утолили голод на %d.", Groceries[playerid][gHamburger]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			Groceries[playerid][gHamburgers] --;

			PlayerInfo[playerid][pParam1] -= Groceries[playerid][gHamburger];
			if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
			if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);

			SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2703, Right_hand);//2880//2703
			ApplyAnimation(playerid, "FOOD", "EAT_Burger",3.0,0,1,1,0,0);
			SetTimerEx("StopAnimationEx", 5000, 0, "i", playerid);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Гамбургер!");
		}
		else if(listitem == 2)
		{//Выбросить
			Groceries[playerid][gHamburger] = 0;
			Groceries[playerid][gHamburgers] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Гамбургер выкинут!");
		}
	}
	else if(item == 9)
	{
		if(listitem == 0)
		{ //Использовать
			//new Float:health = LastHealth[playerid];
		    //SetPlayerHealthEx(playerid, (health + Groceries[playerid][gPizza]));
		    format(strings, sizeof(strings), "* %s съел %d кг Пиццы.", PlayerName(playerid), Groceries[playerid][gPizza]);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		    format(strings, sizeof(strings), "* Вы съели Пиццу, и утолили голод на %d.", Groceries[playerid][gPizza]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			Groceries[playerid][gPizzas] --;

			PlayerInfo[playerid][pParam1] -= Groceries[playerid][gPizza];
			if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
			if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);

			SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2702, Right_hand);//2881//2702
			ApplyAnimation(playerid, "FOOD", "EAT_Pizza",3.0,0,1,1,0,0);
			SetTimerEx("StopAnimationEx", 5000, 0, "i", playerid);

		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Пиццу!");
		}
		else if(listitem == 2)
		{//Выбросить
			Groceries[playerid][gPizza] = 0;
			Groceries[playerid][gPizzas] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Пицца выкинута!");
		}
	}
	else if(item == 10)//item == DialogID[playerid][10]
	{
		if(listitem == 0)
		{ //Использовать
//SendClientMessage(playerid, COLOR_GREY, "   ПИВО 1");
			//new Float:health = LastHealth[playerid];
		    //SetPlayerHealthEx(playerid, (health + Groceries[playerid][gPizza]));
		    new increment = 15;
			if(PlayerDrunk[playerid] < 50)
			{   //если ты ещё не достаточно пьян
				SetPlayerDrunkInBar(playerid, 12, 15.0, "beer");
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
			}
			PlayerDrunk[playerid] += 1;
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);//также добавляет опьянение

//SendClientMessage(playerid, COLOR_GREY, "   ПИВО 2");
			new Float:health = LastHealth[playerid];//для баров и закусочных
			if(health >= 100.0) { PlayerInfo[playerid][pParam2] -= floatround(increment); }
			else
			{
				if(PlayerInfo[playerid][pAlcoholPerk] > 0)
				{
					new Float: hp = 2.0*PlayerInfo[playerid][pAlcoholPerk] + increment;
					SetPlayerHealthEx(playerid, (health + hp));
					PlayerInfo[playerid][pParam2] -= floatround(health + hp);
					SetPlayerDrunkLevel(playerid, PlayerDrunk[playerid]*1000/PlayerInfo[playerid][pAlcoholPerk]);
				}
			   	else
				{
					SetPlayerHealthEx(playerid, (health + increment));
					PlayerInfo[playerid][pParam2] -= floatround(health + increment);
					SetPlayerDrunkLevel(playerid, PlayerDrunk[playerid]*1000);
				}
			}
//SendClientMessage(playerid, COLOR_GREY, "   ПИВО 3");
		    //format(strings, sizeof(strings), "* %s выпил бутылку Пива.", PlayerName(playerid));
			//ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		    format(strings, sizeof(strings), "* Вы выпили бутылку Пива, и утолили Досуг на %d.", increment);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			Groceries[playerid][gBeer] --;

			PlayerInfo[playerid][pParam2] -= increment;
			if(PlayerInfo[playerid][pParam2] < operator2) gParameter1[playerid] = 0;
			if(PlayerInfo[playerid][pParam2] <= 0) PlayerInfo[playerid][pParam2] = 0;
			SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);
			
			if(GetPlayerDrunkLevel(playerid) >= 5000)
			{
				GameTextForPlayerEx(playerid, "~w~You are~n~~p~Drunk", 3500, 1);
			}

			ApplyAnimation(playerid, "BAR", "dnk_stndM_loop",4.1,0,1,1,0,0);
			format(strings, sizeof(strings), "* %s drinks a %s.", PlayerName(playerid), "beer");//не переводить
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		}
		else if(listitem == 1)
		{ //Передать
			new giveplayerid = GetPVarInt(playerid, "PlayerID");
		    if( !IsPlayerConnected(giveplayerid) )
			{
				format(strings, sizeof(strings), "   ID:%d отсутствует на сервере.", giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, strings);
				return 1;
			}
			if(	!IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid)
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[giveplayerid] != MAX_PLAYERS-1 )
			{
				format(strings, sizeof(strings), "%s не рядом с Вами, чтобы передать Пиво.", PlayerName(giveplayerid));//не переводить
				SendClientMessage(playerid, COLOR_GREY, strings);
				return 1;
			}
			Groceries[playerid][gBeer] --;
			format(strings, sizeof(strings), "%s передал бутылку с пивом %s'у.", PlayerName(playerid), PlayerName(giveplayerid));//не переводить
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		}
		else if(listitem == 2)
		{//Выбросить
			Groceries[playerid][gBeer] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Бутылка с Пивом выкинута!");
		}
	}
	else if(item == 13)
	{
		if(listitem == 0)
		{ //Использовать
			new Float:health = LastHealth[playerid];
			new payout;

			if(Fishes[playerid][pWeight][0] > 0)
			{
				payout = Fishes[playerid][pWeight][0];
				Fishes[playerid][pWeight][0] = 0;
			}
			else if(Fishes[playerid][pWeight][1] > 0) { payout = Fishes[playerid][pWeight][1]; Fishes[playerid][pWeight][1] = 0; }
			else if(Fishes[playerid][pWeight][2] > 0) { payout = Fishes[playerid][pWeight][2]; Fishes[playerid][pWeight][2] = 0; }
			else if(Fishes[playerid][pWeight][3] > 0) { payout = Fishes[playerid][pWeight][3]; Fishes[playerid][pWeight][3] = 0; }
			else if(Fishes[playerid][pWeight][4] > 0) { payout = Fishes[playerid][pWeight][4]; Fishes[playerid][pWeight][4] = 0; }
			else
			{
				payout = PlayerInfo[playerid][pFishes];
				//SendClientMessage(playerid, COLOR_GREY, "   У вас не осталось рыбы!");
				//return 1;
			}

			SetPlayerHealthEx(playerid, (health + payout));
			format(strings, sizeof(strings), "* %s съел %d кг рыбы.", PlayerName(playerid), payout);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

			PlayerInfo[playerid][pFishes] -= payout;
			PlayerInfo[playerid][pParam1] -= payout;
			if(PlayerInfo[playerid][pParam1] < 100) gParameter1[playerid] = 0;
			if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], 100);

			format(strings, sizeof(strings), "* Вы съели рыбу и утолили голод на %d.", payout);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

			SetPlayerAttachedObject(playerid, EAT_SLOT, 1599, Right_hand, 0.0699,0.0329,0.1109, 80.80,-65.50,1.99, 0.3,0.3,0.3);
			ApplyAnimation(playerid, "FOOD", "EAT_Chicken", 3.0,0,1,1,0,0);
			SetTimerEx("StopAnimationEx", 5000, 0, "i", playerid);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Рыбу!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pFishes] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Рыба выкинута!");
		}
	}
	else if(item == 14)
	{
		if(listitem == 0)
		{ //Использовать
			new Float:health = LastHealth[playerid];
		    SetPlayerHealthEx(playerid, (health + 1.0));
		    format(strings, sizeof(strings), "* %s съел гриб.", PlayerName(playerid));
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		    format(strings, sizeof(strings), "* Вы съели гриб, и утолили голод на %d.", 1);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
			PlayerInfo[playerid][pMushroom] --;

			PlayerInfo[playerid][pParam1] -= 1;
			if(PlayerInfo[playerid][pParam1] < 100) gParameter1[playerid] = 0;
			if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], 100);

			SetPlayerAttachedObject(playerid, EAT_SLOT, 1603, Right_hand, 0.0499,0.0639,0.2310, 0.00,0.00,0.00, 0.25,0.25,0.25);
			ApplyAnimation(playerid, "FOOD", "EAT_Chicken", 3.0,0,1,1,0,0);
			SetTimerEx("StopAnimationEx", 5000, 0, "i", playerid);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Гриб!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pMushroom] --;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Гриб выкинут!");
		}
	}
	else if(item == 16)
	{
		if(listitem == 0)
		{ //Использовать
			if(GetPVarInt(playerid, "Helmet") != 0)
			{
				new slot = GetPVarInt(playerid, "AttachIndex");
				if( IsPlayerAttachedObjectSlotUsed(playerid, slot) ) RemovePlayerAttachedObject(playerid, slot);
				SetPVarInt(playerid, "Helmet", 0);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Шлем снят!");
			}
			else
			{
				//найти первый свободный слот
				new index = -1;
				for(new j=0; j < MAX_PLAYER_ATTACHED_OBJECTS; j++)
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, j)) continue;
					SetPVarInt(playerid, "AttachIndex", j);
					index = j;
					break;
				}
				if(index != -1)
				{
					new skin = GetPlayerSkin(playerid);
					
					SetPlayerHelmet(playerid, index, skin);
					/*SetPlayerAttachedObjectEx(playerid, index, 18645, Head,
						HelmetPos[skin][0], HelmetPos[skin][1], HelmetPos[skin][2],
						HelmetPos[skin][3], HelmetPos[skin][4], HelmetPos[skin][5]);*/
					
					SetPVarInt(playerid, "Helmet", PlayerInfo[playerid][pHelmet]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "Шлем одет!");
				}
			}
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Выберите игрока, которому хотите передать!");
			SendClientMessage(playerid, COLOR_GREY, "   Можно просто кликнуть двойным щелчком в TAB для указания ника.");
			//PlayerInfo[playerid][pHelmet] = 0;
			//SendClientMessage(playerid, COLOR_GREY, "  Вы передали щлем!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pHelmet] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Шлем выкинут!");
		}
	}
	else if(item == 20)
	{
		if(listitem == 0)
		{ //Использовать
			PlayerInfo[playerid][pAdrenalin] --;

			PlayerInfo[playerid][pParam5] -= 1;
			if(PlayerInfo[playerid][pParam5] < operator5)
			{
				gParameter5[playerid] = 0;
				//ClearAnimations(playerid, 1);
				ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
				//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
			if(PlayerInfo[playerid][pParam5] <= 0) PlayerInfo[playerid][pParam5] = 0;
			SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);
			format(strings, sizeof(strings), "* %s вколол дозу адреналина !", PlayerName(playerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		}
		else if(listitem == 1)
		{ //Передать
			SendClientMessage(playerid, COLOR_GREY, "  Вы передали Адреналин!");
		}
		else if(listitem == 2)
		{//Выбросить
			PlayerInfo[playerid][pAdrenalin] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Адреналин выкинут!");
		}
	}
	return 1;
}
