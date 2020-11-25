new levelexp = 4;//4//коэф. для получения очков уважения


new MyBizz[MAX_PLAYERS][10];

new bEntrancePickupID[MAX_BIZ];
new Text3D: bEntranceText3D[MAX_BIZ];
new bExitPickupID[MAX_BIZ];
new Text3D: bExitText3D[MAX_BIZ];

stock biz_OnGameModeInit()
{
	//НАЧАЛО УСТАНОВКИ ПИКАПОВ c надписями
	new text_info[128];//19+20+24
	for(new b = 0; b < MAX_BIZ; b++)
	{
		if(BizInfo[b][bOwned] == 0)
		{   //если биз не куплен
			bEntrancePickupID[b] = SetPickupEx(1273, 23, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], 0);

		    format(text_info, sizeof(text_info), "[ %s ]", BizInfo[b][bDiscription]);
			bEntranceText3D[b] = Create3DTextLabelEx(text_info, 0xEEEE88FF,
					BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]+0.75,
					60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		else //if(BizInfo[b][bOwned] > 0)
		{   //если биз куплен
			if(b == 0) bEntrancePickupID[b] = SetPickupEx(1274, 23, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]);
			else bEntrancePickupID[b] = SetPickupEx(19522, 23, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]);

		    format(text_info, sizeof(text_info), "[ %s ]\n{FFFFFF}%s", BizInfo[b][bDiscription], BizInfo[b][bOwner]);
			bEntranceText3D[b] = Create3DTextLabelEx(text_info, 0xAAAAFFFF,
					BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]+0.75,
					30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		}
		//----------------------------------------------------------------------
		bExitPickupID[b] = SetPickupEx(1559, 23, BizInfo[b][bExitX], BizInfo[b][bExitY], BizInfo[b][bExitZ]+0.1, MAX_HOUSE+b);//маркер на выходе
		bExitText3D[b] = Create3DTextLabelEx("Выход {FF0000}[EXIT]", 0xBFF600FF,
					BizInfo[b][bExitX], BizInfo[b][bExitY], BizInfo[b][bExitZ]+0.75,
					80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, MAX_HOUSE+b);
	}

//Актёры с управляемым 3D текстом
//устанавливаем 3д текст всем актёрам в бизах
	for(new i = 0 ; i<MAX_BIZ ; i++)
	{
		//if(i == bizactorcor[i][vwAC])
		if(bizactorcor[i][skinAC] != -1)
		{//ставим актёров по всему массиву где прописан виртуальный мир
			//ActorID[i] = CreateActor(bizactorcor[i][skinAC], bizactorcor[i][XAC],bizactorcor[i][YAC],bizactorcor[i][ZAC],bizactorcor[i][AAC]);
			//SetActorVirtualWorld(ActorID[i], i);
/*
	   		ActorID[i] = CreateDynamicActor(bizactorcor[i][skinAC], bizactorcor[i][XAC],bizactorcor[i][YAC],bizactorcor[i][ZAC],bizactorcor[i][AAC], true, 100.0, i+1);//bizactorcor[i][vwAC]
			if(i+1 == 82) ApplyDynamicActorAnimation(ActorID[i], "PED", "SEAT_DOWN", 4.1, 0, 0, 0, 1, 0);
			//"Здравствуйте, {FFFB00}%s,{FFFFFF} что желаете приобрести?", sendername);
			new str[24+47];
			strcat(str, BizInfo[i][bDiscription]);
			if(i == 89) strcat(str, "\nНажмите {FF0000}Y{FFFFFF} для взаимодействия");
			Text_Actor[i] = Create3DTextLabelEx(str, 0xFFFFFFFF, bizactorcor[i][XAC],bizactorcor[i][YAC],bizactorcor[i][ZAC]+1, 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, i+1);
*/
			//printf("actorid %d, vwid %d ", ActorID[i], i);

			new str[24+47];
			strcat(str, BizInfo[i][bDiscription]);
			if(i == 89) strcat(str, "\nНажмите {FF0000}Y{FFFFFF} для взаимодействия");//в магазине аксессуаров
			//Text_Actor[i] = Create3DTextLabelEx(BizInfo[i][bDiscription], 0xFFFFFFFF, bizactorcor[i][XAC],bizactorcor[i][YAC],bizactorcor[i][ZAC]+1, 10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, i+1);
		    ActorID[i] = CreateDynamicActorExY(str, bizactorcor[i][skinAC], bizactorcor[i][XAC],bizactorcor[i][YAC],bizactorcor[i][ZAC],bizactorcor[i][AAC], true, 100.0, MAX_HOUSE+i, BizInfo[i][bInt]);// актер в мэрии
		    if(i == 81 || i == 83) ApplyDynamicActorAnimation(ActorID[i], "PED", "SEAT_DOWN", 4.1, 0, 0, 0, 1, 0);//порт  || клубе последняя ночь

		}
	}

	new strtmp[368 + 5*4 + 2+10 + 10+10+10];
	format(strtmp, sizeof(strtmp), "[ Склад ]\n\
\n{FF6600}Металл: {FFFFFF}%d\
\n{FF6600}Текстиль: {FFFFFF}%d\
\n{FF6600}Продовольствие: {FFFFFF}%d\
\n{FF6600}Древесина: {FFFFFF}%d\
\n{FF6600}Топливо: {FFFFFF}%d\
\n{FF6600}Товаров: {FFFFFF}%d\
\n{FF6600}Рабочих: {FFFFFF}%d\
\n{FF6600}Оплата: {33AA33}$%d\
\n{FF6600}В Кассе: {33AA33}$%d",
		BizInfo[80][bMetal],BizInfo[80][bTextiles],BizInfo[80][bProvisions],BizInfo[80][bTree],BizInfo[80][bFuel],
		BizInfo[80][bProducts],
		BizInfo[80][bWorker],	BizInfo[80][bSalary],
		//BizInfo[80][bImport],	BizInfo[80][bExport],
		//BizInfo[80][bExport]-BizInfo[80][bImport]
		BizInfo[80][bTill]);
	StoreHouseInfo = Create3DTextLabelEx(strtmp, 0xEEEE88FF, -18.9624,-270.4885,5.4297+10.0, 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0); 

	//new strtmp[431];//369 + 5*4 + 2+10 + 10+10+10 = 431
	format(strtmp, sizeof(strtmp), "[ Порт ]\n\
\n{FF6600}Металл: {FFFFFF}%d\
\n{FF6600}Текстиль: {FFFFFF}%d\
\n{FF6600}Продовольствие: {FFFFFF}%d\
\n{FF6600}Древесина: {FFFFFF}%d\
\n{FF6600}Топливо: {FFFFFF}%d\
\n{FF6600}Товаров: {FFFFFF}%d\
\n{FF6600}Рабочих: {FFFFFF}%d\
\n{FF6600}Оплата: {33AA33}$%d\
\n{FF6600}В Кассе: {33AA33}$%d",
		BizInfo[81][bMetal],BizInfo[81][bTextiles],BizInfo[81][bProvisions],BizInfo[81][bTree],BizInfo[81][bFuel],
		BizInfo[81][bProducts],
		BizInfo[81][bWorker], BizInfo[81][bSalary],
		//BizInfo[81][bImport], BizInfo[81][bExport],
		//BizInfo[81][bExport]-BizInfo[81][bImport]
		BizInfo[81][bTill]);
	OceanDockInfo = Create3DTextLabelEx(strtmp, 0xEEEE88FF, 2731.6685,-2416.8745,13.6278, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);


//для шахтёров
	format(strtmp, sizeof(strtmp), "[ Шахта ]\n\n{FF6600}Соли: {FFFFFF}%d{FF6600}\nВ Кассе: {33AA33}$%d", SBizInfo[55][sbProducts], SBizInfo[55][sbTill]);
	MineInfo = Create3DTextLabelEx(strtmp, 0xEEEE88FF,	585.5980,874.7810,-42.4970-0.75, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);
}

stock biz_OnPlayerKeyState_YES(playerid)
{
	new bizid = GetBizLocation(playerid)-1;
	new bouse = GetPlayerVirtualWorld(playerid)-MAX_HOUSE;
	if(bouse >= 0 && bouse <= 80)
	{
		if(bizactorcor[bouse][skinAC] == 217 && IsPlayerInRangeOfPoint(playerid, 3.0, bizactorcor[bouse][XAC],bizactorcor[bouse][YAC],bizactorcor[bouse][ZAC]))//Для амуниций
		{
			if(BizInfo[bizid][bProducts] <= 0 && PlayerInfo[playerid][pLevel] > 3 && !gTutorial[playerid] && !gRealWar) {
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Shop 24-7", 5000, 1);
			}
			if(GetPlayerMoneyH(playerid) < 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас нет $10 наличных !");
				return 1;
			}
			//TogglePlayerControllableEx(playerid, 0);//обездвиживает
			//ShowMenuForPlayerEx(mShop, playerid);
			new sendername[MAX_PLAYER_NAME];
			new nsa[144];
			new vww = GetPlayerVirtualWorld(playerid);
			GetPlayerName(playerid, sendername, sizeof(sendername));
			format(nsa, sizeof(nsa), "Здравствуйте, {FFFB00}%s,{FFFFFF} что желаете приобрести?", sendername);
			Update3DTextLabelText(Text_Actor[vww], 0xFFFFFFFF, nsa);
			ApplyActorAnimation(ActorID[vww], "PED", "IDLE_CHAT",4.1,1,1,1,0,0);

			SetTimerEx("ClearTextActor", 3000, false, "d", vww);
			ShopMenu(playerid);
		}
		if(bizactorcor[bouse][skinAC] == 179 && IsPlayerInRangeOfPoint(playerid, 3.0, bizactorcor[bouse][XAC],bizactorcor[bouse][YAC],bizactorcor[bouse][ZAC]))//Для амуниций
		{
			if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие!");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) <= 500) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
			//TogglePlayerControllableEx(playerid, 0);//обездвиживает
			//ShowMenuForPlayerEx(mAmmuNation, playerid);
			//GameTextForPlayer(playerid, "~w~Press ~g~'H'", 5000, 5);
			new sendername[MAX_PLAYER_NAME];
			new nsa[144];
			new vww = GetPlayerVirtualWorld(playerid);
			GetPlayerName(playerid, sendername, sizeof(sendername));
			format(nsa, sizeof(nsa), "Здравствуйте, {FFFB00}%s,{FFFFFF} что желаете приобрести?", sendername);
			Update3DTextLabelText(Text_Actor[vww], 0xFFFFFFFF, nsa);
			ApplyActorAnimation(ActorID[vww], "PED", "IDLE_CHAT",4.1,1,1,1,0,0);

			SetTimerEx("ClearTextActor", 3000, false, "d", vww);

			ShowPlayerDialogEx(playerid, WEAPONMAG_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{E6D200}Weapon",
				"Оружие\tЦена\n\
				{FFFFFF}9mm\t{0E8C00}$200\n\
				{FFFFFF}Silenced\t{0E8C00}$600\n\
				{FFFFFF}Desert Eagle\t{0E8C00}$1200\n\
				{FFFFFF}Shotgun\t{0E8C00}$600\n\
				{FFFFFF}Combat Shotgun\t{0E8C00}$1000\n\
				{FFFFFF}Rifle\t{0E8C00}$1000\n\
				{FFFFFF}SMG\t{0E8C00}$2000\n\
				{FFFFFF}AK47\t{0E8C00}$3500\n\
				{FFFFFF}M4\t{0E8C00}$4500\n\
				{FFFFFF}Bomb\t{0E8C00}$4500\n\
				{FFFFFF}Other Weapon",
				"OK", "Cancel");//9mm 200, Silenced 9mm 600, Desert Eagle 1200, Shotgun 600, Combat Shotgun 1000, Rifle 1000, SMG 2000, AK47 3500, M4 4500, Bomb +
		}
		if(bizactorcor[bouse][skinAC] == 240 && IsPlayerInRangeOfPoint(playerid, 3.0, bizactorcor[bouse][XAC],bizactorcor[bouse][YAC],bizactorcor[bouse][ZAC]))//для баров
		{
			//if(PlayerDrunk[playerid] < 50)
			if(GetPlayerDrunkLevel(playerid) < 50000)
			{	//если ты ещё не достаточно пьян
				if(BizInfo[bizid][bProducts] <= 0 && !gTutorial[playerid] && !gRealWar) {
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Bar", 5000, 1);
				}
				if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
				new sendername[MAX_PLAYER_NAME];
				new nsa[144];
				new vww = GetPlayerVirtualWorld(playerid);
				GetPlayerName(playerid, sendername, sizeof(sendername));
				format(nsa, sizeof(nsa), "Здравствуйте, {FFFB00}%s,{FFFFFF} что желаете приобрести?", sendername);
				Update3DTextLabelText(Text_Actor[vww], 0xFFFFFFFF, nsa);
				ApplyActorAnimation(ActorID[vww], "PED", "IDLE_CHAT",4.1,1,1,1,0,0);

				SetTimerEx("ClearTextActor", 3000, false, "d", vww);
				ShowPlayerDialogEx(playerid, BAR_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{E6D200}Бар",
					"Предмет\tЦена\n\
					{FFFFFF}Бокал пива\t{0E8C00}$6\n\
					{FFFFFF}Рюмка водки\t{0E8C00}$8\n\
					{FFFFFF}Бокал виски\t{0E8C00}$10\n\
					{FFFFFF}Стакан воды\t{0E8C00}$2\n\
					{FFFFFF}Бутылка пива\t{0E8C00}$12",
					"OK", "Cancel");
			}
			else return SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
		}
		if(bizactorcor[bouse][skinAC] == 172 && IsPlayerInRangeOfPoint(playerid, 3.0, bizactorcor[bouse][XAC],bizactorcor[bouse][YAC],bizactorcor[bouse][ZAC])
		|| bizactorcor[bouse][skinAC] == 167 && IsPlayerInRangeOfPoint(playerid, 3.0, bizactorcor[bouse][XAC],bizactorcor[bouse][YAC],bizactorcor[bouse][ZAC]))
		{
			if(BizInfo[bizid][bProducts] <= 0 && !gTutorial[playerid] && !gRealWar) {
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Restaurant", 5000, 1);
			}
			if(GetPlayerMoneyH(playerid) < 500) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
			//TogglePlayerControllableEx(playerid, 0);//обездвиживает
			//ShowMenuForPlayerEx(mRestaurant, playerid);
			new sendername[MAX_PLAYER_NAME];
			new nsa[144];
			new vww = GetPlayerVirtualWorld(playerid);
			GetPlayerName(playerid, sendername, sizeof(sendername));
			format(nsa, sizeof(nsa), "Здравствуйте, {FFFB00}%s,{FFFFFF} что желаете приобрести?", sendername);
			Update3DTextLabelText(Text_Actor[vww], 0xFFFFFFFF, nsa);
			ApplyActorAnimation(ActorID[vww], "PED", "IDLE_CHAT",4.1,1,1,1,0,0);

			SetTimerEx("ClearTextActor", 3000, false, "d", vww);
			ShowPlayerDialogEx(playerid, REST_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{E6D200}Ресторан",
				"Предмет\tЦена\n\
				{FFFFFF}Sprak Grill\t{0E8C00}$125\n\
				{FFFFFF}The Palm\t{0E8C00}$100\n\
				{FFFFFF}Companile\t{0E8C00}$75\n\
				{FFFFFF}Madeo\t{0E8C00}$50\n\
				{FFFFFF}Matsuhisa\t{0E8C00}$25",
				"OK", "Cancel");//Sprak Grill 125, The Palm 100, Companile 75, Madeo 50, Matsuhisa 25
		}
		if(bizactorcor[bouse][skinAC] == 155 && IsPlayerInRangeOfPoint(playerid, 3.0, bizactorcor[bouse][XAC],bizactorcor[bouse][YAC],bizactorcor[bouse][ZAC]))	//Для закусочных
		{	//если игрок вошел в контрольную отметку
			if(BizInfo[bizid][bProducts] <= 0 && !gRealWar) {
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~BurgerShot", 5000, 1);
			}
			if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
			//TogglePlayerControllableEx(playerid, 0);//обездвиживает
			//ShowMenuForPlayerEx(mBurgerShot, playerid);
			new sendername[MAX_PLAYER_NAME];
			new nsa[144];
			new vww = GetPlayerVirtualWorld(playerid);
			GetPlayerName(playerid, sendername, sizeof(sendername));
			format(nsa, sizeof(nsa), "Здравствуйте, {FFFB00}%s,{FFFFFF} что желаете приобрести?", sendername);
			Update3DTextLabelText(Text_Actor[vww], 0xFFFFFFFF, nsa);
			ApplyActorAnimation(ActorID[vww], "PED", "IDLE_CHAT",4.1,1,1,1,0,0);

			SetTimerEx("ClearTextActor", 3000, false, "d", vww);
			ShowPlayerDialogEx(playerid, BURGER_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "{E6D200}Food",
				"Предмет\tЦена\n\
				{FFFFFF}Moo Kids Meal\t{0E8C00}$2\n\
				{FFFFFF}Beef Tower\t{0E8C00}$5\n\
				{FFFFFF}Meat Stack\t{0E8C00}$10\n\
				{FFFFFF}Salad Meal\t{0E8C00}$10\n\
				{FFFFFF}Buy Hamburger\t{0E8C00}$1000",
				"OK", "Cancel");//Moo Kids Meal 2, Beef Tower 5, Meat Stack 10, Salad Meal 10, Buy Hamburger 1000
		}
	}
	return 1;
}


//всё равно придётся делать через таймер, т.к. надо чтобы пикапы подбирались как пешком так и на тачке
stock biz_OnPlayerPickUpPickup(playerid, pickupid)
//stock PropertyOnPlayerPickUp(playerid, pickupid)
{   //вызывается из OnPlayerPickUpPickup только при подборе пикапа
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return 1; }
	//if(pickupid < (STAIRWAYS*2-2) || pickupid >= (STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ)) return 1;
//STAIRWAYS*2 + (MAX_HOUSE*2+12)+MAX_BIZ*2+MAX_SBIZ + MAX_VEHICLE_PICKUPS	//35*2 + (52*2+12)+82*2+59 = 409
//12 - максимальное кол-во раздевалок

	//для магазинов одежды
	if( IsAtClothShop(playerid) )
	{   //выполняется при подборе синей иконки футболки
		if(spectateid[playerid] < MAX_PLAYERS-1) { return 1; }//чтобы не появлялась у того кто наблюдает

		if(GetPVarInt(playerid, "ShowMenu") == 0)
		{
			if(GetPlayerMoneyH(playerid) < 550)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас нет $550 на руках !!!");
				return 1;
			}
			TogglePlayerControllableEx(playerid, 0);//обездвиживает
			SetPVarInt(playerid, "OldSkin", GetPlayerSkin(playerid));
			if( !IsValidSkin( GetPVarInt(playerid, "OldSkin") ) ) SetPVarInt(playerid, "OldSkin", SKIN_DEFAULT);
			ShowMenuForPlayerEx(mClothMenu, playerid);
		}
	}

	//new local = PlayerInfo[playerid][pLocal];
	new msgitem[868];//542+52+57+57 + 38+32+25+35+3+3+5+5 + 14 = 868

	new tregion[20];
	strmid(tregion, "Unknown_Region", 0, strlen("Unknown_Region"), 20);
	new bouse;//оставляем по нулям, чтобы не было за пределами массива
	
	for(new b = 0; b < MAX_BIZ; b++)
	{   //опеделяем у какого биза стоит игрок
		//if(IsPlayerInRangeOfPoint(playerid, 4.1, HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]))
		if(pickupid == bEntrancePickupID[b])
		{
			bouse = b; SetPVarInt(playerid, "Bouse", b);
			break;
		}
		//else if(IsPlayerInRangeOfPoint(playerid, 4.0, HouseInfo[h][hExitX], HouseInfo[h][hExitY], HouseInfo[h][hExitZ])
		else if(pickupid == bExitPickupID[b]
		&& PlayerInfo[playerid][pVirtual] == MAX_HOUSE+b)//если вдруг появятся бизы с одним и тем же интерьером
		{
			bouse = b; SetPVarInt(playerid, "Bouse", b);
			break;
		}
	}
	//==========================================================================
	if(gDialogStatus[playerid][1] <= 0 &&
		//IsPlayerInRangeOfPoint(playerid, 1.4, BizInfo[bouse][bEntranceX], BizInfo[bouse][bEntranceY], BizInfo[bouse][bEntranceZ]))
		pickupid == bEntrancePickupID[bouse])
	{
		for(new j=0; j<MAX_TURFS; j++)
		{
			if( IsPointInRegion(BizInfo[bouse][bEntranceX], BizInfo[bouse][bEntranceY], BizInfo[bouse][bEntranceZ], j) )//если дом находится в координатах по строке j из массива zones
			{
				strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 255);//Извлекает диапазон символов из строки.
				break;
			}
		}
		strins(msgitem, "\n{ffffff}_______________________________________________", strlen(msgitem));
		if(BizInfo[bouse][bOwned] > 0)
		{//{0080FF}Описание:\t{FFFFFF}%s\n
			if(bouse == 80)
			{
				format(msgitem, sizeof(msgitem), "{0080FF}Район:\t\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t\t{FFFFFF}%s\
\n{0080FF}Контроль:\t\t{FFFFFF}%s\
\n{0080FF}Цена входа:\t\t{33AA33}$%d\
\n{0080FF}Покупку сырья:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Продажа сырья:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Покупку товаров:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Продажа товаров:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Товаров на складе:\t{FFFFFF}%d",
					tregion, bouse+1, BizInfo[bouse][bOwner],
					GetFamilyName(BizInfo[bouse][bExtortion]),
					BizInfo[bouse][bEntranceCost],
					compcost*(100+BizInfo[bouse][bBuyProd])/100.0, 100+BizInfo[bouse][bBuyProd],
					compcost*(100+BizInfo[bouse][bSellProd])/100.0, 100+BizInfo[bouse][bSellProd],
					compcost*(100+BizInfo[bouse][bBuyProd]*3)/100.0, 100+BizInfo[bouse][bBuyProd]*3,
					compcost*(100+BizInfo[bouse][bBuyProd]*3+10)/100.0, 100+BizInfo[bouse][bBuyProd]*3+10,
					BizInfo[bouse][bProducts]);
			}
			else
			{
				format(msgitem, sizeof(msgitem), "{0080FF}Район:\t\t\t{FFFFFF}%s, %d\
\n{0080FF}Владелец:\t\t{FFFFFF}%s\
\n{0080FF}Контроль:\t\t{FFFFFF}%s\
\n{0080FF}Цена входа:\t\t{33AA33}$%d\
\n{0080FF}Покупка продуктов:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}Продажа товаров:\t{33AA33}$%.2f{FFFFFF}[%d %%]\
\n{0080FF}%s/Товаров на складе:\t{FFFFFF}%d/%d",
					tregion, bouse+1, BizInfo[bouse][bOwner],
					GetFamilyName(BizInfo[bouse][bExtortion]),
					BizInfo[bouse][bEntranceCost],
					compcost*(100+BizInfo[bouse][bBuyProd])/100.0, 100+BizInfo[bouse][bBuyProd],
					compcost*(100+BizInfo[bouse][bSellProd])/100.0, 100+BizInfo[bouse][bSellProd],
					TypeCargo(BizInfo[bouse][bBranch]), GetProducts(bouse), BizInfo[bouse][bProducts]);
			}
			format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t\t{FFFFFF}%d\
\n{0080FF}Экспорт/Импорт:\t{33AA33}$%d{FFFFFF}/$%d\
\n{0080FF}Зарплата:\t\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}В Кассе:\t\t{33AA33}$%d",
				msgitem,
				BizInfo[bouse][bWorker],
				BizInfo[bouse][bExport],BizInfo[bouse][bImport],
				BizInfo[bouse][bSalary],
				BizInfo[bouse][bExpenses],
				//BizInfo[bouse][bExport]-BizInfo[bouse][bWorker]*BizInfo[bouse][bSalary]-BizInfo[bouse][bExpenses]);
				BizInfo[bouse][bTill]);
		}
		else {//\n{0080FF}Описание:\t{FFFFFF}%s
			format(msgitem, sizeof(msgitem), "Этот Бизнес - для продажи\
\n{0080FF}Район:\t\t\t{FFFFFF}%s, %d\
\n{0080FF}Стоимость:\t\t{33AA33}$%d\
\n{0080FF}Цена входа:\t\t{33AA33}$%d\
\n{0080FF}%s/Товаров на складе:\t{FFFFFF}%d/%d",
				tregion, bouse+1, BizInfo[bouse][bBuyPrice],
				BizInfo[bouse][bEntranceCost],
				TypeCargo(BizInfo[bouse][bBranch]), GetProducts(bouse), BizInfo[bouse][bProducts]);
			format(msgitem, sizeof(msgitem), "%s\
\n\n{0080FF}Работников:\t\t{FFFFFF}%d\
\n{0080FF}Экспорт[Импорт]:\t{33AA33}$%d{FFFFFF}[$%d]\
\n{0080FF}Зарплата:\t\t{33AA33}$%d\
\n{0080FF}Содержание в час:\t{33AA33}$%d\
\n{0080FF}Баланс:\t\t{33AA33}$%d",
				msgitem,
				BizInfo[bouse][bWorker],
				BizInfo[bouse][bExport],BizInfo[bouse][bImport],
				BizInfo[bouse][bSalary],
				BizInfo[bouse][bExpenses],
				//BizInfo[bouse][bExport]-BizInfo[bouse][bWorker]*BizInfo[bouse][bSalary]-BizInfo[bouse][bExpenses]);
				BizInfo[bouse][bExport]-BizInfo[bouse][bImport]);
			strins(msgitem, "\n\n{AFAFAF}Для покупки введите /buy. \nСтоимость пойдет в Банк", strlen(msgitem));
		}
		strins(msgitem, "\n{ffffff}_______________________________________________", strlen(msgitem));
		strins(msgitem, "\n{0080FF}Вы желаете войти в помещение ?", strlen(msgitem));
		if(strlen(msgitem) > sizeof(msgitem))
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "Error19: Business Info - %s[%d], strlen(msgitem): %d, sizeof(msgitem): %d", PlayerName(playerid), playerid, strlen(msgitem), sizeof(msgitem));
			Log(ERROR, strings);
			return 1;
		}
		new caption[70];
		format(caption, sizeof(caption), "%s {0080FF}Уровень:\t{FFFFFF}%d %s", BizInfo[bouse][bDiscription], BizInfo[bouse][bLevel], TypeBranch(BizInfo[bouse][bBranch]));
		ShowPlayerDialogGap(playerid, BIZ_DIALOG, DIALOG_STYLE_MSGBOX, caption, msgitem, "YES", "NO");
		gDialogStatus[playerid][1] = 5;//таймер на 5 секунд
		
		if(CHECKING[PlayerPickUpPickup])
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "biz_OnPlayerPickUpPickup(playerid:%d, bouse:%d)", playerid, bouse);
			//SendClientMessageToAll(COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
		
	}
	//--------------------------------------------------------------------------
	else if(gDialogStatus[playerid][1] <= 0 &&
		//IsPlayerInRangeOfPoint(playerid, 1.4, BizInfo[bouse][bExitX], BizInfo[bouse][bExitY], BizInfo[bouse][bExitZ]))
		pickupid == bExitPickupID[bouse])
	{
		strins(msgitem, "\n{0080FF}Вы желаете выйти из помещения ?", strlen(msgitem));
		ShowPlayerDialogGap(playerid, BIZ_DIALOG, DIALOG_STYLE_MSGBOX, BizInfo[bouse][bDiscription],msgitem, "YES", "NO");
		gDialogStatus[playerid][1] = 5;//таймер на 5 секунд
	}

	return 1;
}

stock biz_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	ShopMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	BizControlMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
//==============================================================================
	if(dialogid != BIZ_DIALOG) return 1;
	//new msgitem[256+1];
	//new giveplayerid;
	if(!response)
	{
		PlaySoundForPlayer(playerid, SOUND_BEE_TRACK_STOP);
		SetPVarInt(playerid, "Bouse", FREEROAM);
		return 1;
	}
	new b = GetPVarInt(playerid, "Bouse");
//------------------------------------------------------------------------------
//для входов //для выходов
//ИНФОРМИРОВАНИЕ
//new strings[MAX_STRING];
/*format(strings, sizeof(strings), "biz_OnDialogResponse(playerid:%d, dialogid:%d, Bouse:%d[%d]) pVirtual:%d pLocal:%d",
		playerid, dialogid, GetPVarInt(playerid, "Bouse"),
		IsPlayerInRangeOfPoint(playerid, 3.0,
			BizInfo[b][bEntranceX],
			BizInfo[b][bEntranceY],
			BizInfo[b][bEntranceZ]),
		PlayerInfo[playerid][pVirtual],PlayerInfo[playerid][pLocal]	);
SendClientMessage(playerid, -1, strings);*/
	
//"/exit" - начало
	//сначало обязательно сканируем по мирам т.к. может быть одна и таже точка в одном месте
	if(IsPlayerInRangeOfPoint(playerid, 2.1,
		BizInfo[b][bExitX],
		BizInfo[b][bExitY],
		BizInfo[b][bExitZ])
		&& PlayerInfo[playerid][pVirtual] == MAX_HOUSE+b //чтобы выход не определился как вход
		//&& PlayerInfo[playerid][pLocal] == 100+b
	  )
	{//если интерьер совпадает с виртуальным миром в котором находится игрок
		SetPlayerVirtualWorldEx(playerid, 0);
		SetPlayerInteriorEx(playerid, 0);

		new Float:X = BizInfo[b][bEntranceX];
		new Float:Y = BizInfo[b][bEntranceY];
		new Float:Z= BizInfo[b][bEntranceZ];
		new Float:Ang = BizInfo[b][bEntranceA];
		GetXYInFrontOfPoint(2.0, Ang, X,Y);
		SetPlayerPosEx(playerid, X,Y,Z, Ang);

		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetPVarInt(playerid, "Bouse", FREEROAM);

		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		SetPlayerTime(playerid, lH, lM);//возвращаем время в мире
		SetWeather(weathers[wethindex]);//возвращаем погоду
		StopAudioStreamForPlayer(playerid);
		PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0,BizInfo[b][bEntranceX],BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]);
	}
//"/exit" - конец
//------------------------------------------------------------------------------
//"/enter" - начало
	else if(IsPlayerInRangeOfPoint(playerid, 2.1,
				BizInfo[b][bEntranceX],
				BizInfo[b][bEntranceY],
				BizInfo[b][bEntranceZ])
			&& PlayerInfo[playerid][pVirtual] == 0
			//&& PlayerInfo[playerid][pLocal] == FREEROAM
		)
	{
		//для владения несколькими бизами
		//for(new limit = 0; limit < 10; limit++)
		//{
		//	if(MyBizz[playerid][limit] != b) continue;
		//	goto Mark2;//Mark2:
		//}

		/*if(	GetPlayerMoneyH(playerid) >= BizInfo[b][bEntranceCost] ||
			//gTutorial[playerid] ||
			b == 81)
		{
			if(BizInfo[b][bLock] == 1 && PlayerInfo[playerid][pLevel] > 10)
			{//Закрытие бизнеса должно влияет только на ввоз дальнобойщиками сырья и вывоз денег инкассаторами
				GameTextForPlayerEx(playerid, "~r~Closed", 5000, 1);//по англ обязательно
				return 1;
			}
			if(	BizInfo[b][bProducts] <= 0 && b != 0 && b != 81 &&
				PlayerInfo[playerid][pLevel] > 3 //&& !gTutorial[playerid] && !gRealWar
				)
			{
				GameTextForPlayerEx(playerid, "~r~Out Of Stock", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			if(PlayerInfo[playerid][pLevel] > 3 //&& !gTutorial[playerid]
				)
			{
				GivePlayerMoneyH(fbiz+b, playerid, -BizInfo[b][bEntranceCost]);

				OnGangsExtortionBiz(b, BizInfo[b][bEntranceCost]);
				//BizInfo[b][bProducts] --;//продукты снимаются только за вход
			}
			if(b == 61 || b == 63)
			{
				ResetPlayerWeaponsEx(playerid);
				PlayerInfo[playerid][pDrugs] = 0;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Управляющий: Оружие и наркотики конфискованы.");
			}
		}
		else
		{
			GameTextForPlayerEx(playerid, "~r~You dont have the cash", 5000, 1);
			return 1;
		}*/
//Mark2:
		SetPlayerTime(playerid, 12, 0);
		SetPlayerWeather(playerid, 1);

		if(b == 83)//если это клуб, то включить саундтрек
		{
			//PlayAudioStreamForPlayerEx(playerid, "http://127.0.0.1/soundVW/Sick Individuals - Lost & Found (Radio Edit).mp3");
			PlayAudioStreamForPlayer(playerid, "http://samp.vpn.by/SoundVW/Sick Individuals - Lost&Found.mp3",
				1263.3727,-15.9370,1000.9175, 40.0, 1);
		}
		else if(b == 85)//если это ресторан, то включить саундтрек
		{
			//PlayAudioStreamForPlayerEx(playerid, "http://127.0.0.1/soundVW/Sick Individuals - Lost & Found (Radio Edit).mp3");
			PlayAudioStreamForPlayer(playerid, "http://samp.vpn.by/SoundVW/Dylan Cifuentes - Requiem in Cello.mp3",
				1369.7311,-24.2673,1005.1813, 40.0, 1);
		}
		/*if(//!IsPlayerInRangeOfPoint(playerid, 2.0, 1328.4407,-1557.9713,13.5469) &&  //для всех кроме SIMCARDS
			!IsPlayerInRangeOfPoint(playerid, 2.0, 1952.7180,-2004.0569,13.5469)	)//для всех кроме кофейни (очень близко координаты входа и выхода)
		{
			SetPlayerVirtualWorldEx(playerid, b+MAX_HOUSE);
		}
		else*/
		if(b == MAX_BIZ-1) SetPlayerVirtualWorldEx(playerid, 0);//для кофейни
		else SetPlayerVirtualWorldEx(playerid, MAX_HOUSE+b);

	    //записываем в координаты спауна при входе
		PlayerInfo[playerid][pPos_x] = BizInfo[b][bEntranceX],
		PlayerInfo[playerid][pPos_y] = BizInfo[b][bEntranceY],
		PlayerInfo[playerid][pPos_z] = BizInfo[b][bEntranceZ];

		SetPlayerInteriorEx(playerid, BizInfo[b][bInt]);
		new Float:X = BizInfo[b][bExitX];
		new Float:Y = BizInfo[b][bExitY];
		new Float:Z= BizInfo[b][bExitZ];
		new Float:Ang = BizInfo[b][bExitA];
		GetXYInFrontOfPoint(2.0, Ang, X,Y);
		SetPlayerPosEx(playerid, X,Y,Z, Ang);

		//OnePlayAnim(playerid, "PED", "WALK_CIVI", 4.1, 0, 1, 1, 0, 0);
		PlayerInfo[playerid][pLocal] = MAX_HOUSE+b;//(0-4)+100=104
		SetPVarInt(playerid, "Bouse", b);
		PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0,BizInfo[b][bExitX],BizInfo[b][bExitY], BizInfo[b][bExitZ]);
		//break;
	}
//"/enter" - конец
	return 1;
}

stock OnBizInit(bizid)
{//вызывается при продаже или при сносе если игрок не играет
	BizInfo[bizid][bOwned] = 0;
	strmid(BizInfo[bizid][bOwner], "Банк", 0, strlen("Банк"), 20);//меняем имя владельца на The State
	//strmid(BizInfo[bizid][bExtortion], "No-One", 0, strlen("No-One"), 20);//меняем имя владельца на The State
	BizInfo[bizid][bExtortion] = 0;
	BizInfo[bizid][bEntranceCost] = 0;
	BizInfo[bizid][bTill] = 1000+random(9000);
	BizInfo[bizid][bLevel] = 1;
	BizInfo[bizid][bLock] = 0;//открыт
	BizInfo[bizid][bMetal] = 100+random(900);//временно
	BizInfo[bizid][bTextiles] = 100+random(900);//временно
	BizInfo[bizid][bProvisions] = 100+random(900);//временно
	BizInfo[bizid][bTree] = 100+random(900);//временно
	BizInfo[bizid][bFuel] = 1000+random(9000);//временно
	BizInfo[bizid][bProducts] = 1000+random(9000);//временно
	BizInfo[bizid][bBuyProd] = 40;
	BizInfo[bizid][bSellProd] = 50;//15 для экономики
	BizInfo[bizid][bDate] = getdate();
	BizInfo[bizid][bInkas] = 1000;//временно
	BizInfo[bizid][bImport] = 0;//сколько денег потратил на покупку продуктов
	BizInfo[bizid][bExport] = 0;//сколько денег заработал на экспорте
	BizInfo[bizid][bWorker] = 0;
	BizInfo[bizid][bSalary] = 1;
}


stock biz_ControlMenu(playerid, bizid)//Business Management Menu
{
	new listitems[] = " - информация по бизнесу\t/bizinfo\n\
 - продать бизнес\t/sellbiz\n\
 - открыть/закрыть бизнес\t/open\n\
 - установить входную плату\t/bizfee\n\
 - установить цену покупки продуктов\t/bizbuyprods\n\
 - установить цену продажи товаров\t/bizsellprods\n\
 - пополнить денежную кассу\t/bizbank\n\
 - установить минимальный остаток денег\t/bizinkas\n\
 - биржа\t/exchange\n\
 - пригласить сотрудников(не готово)\t/invite\n\
 - установить оплату\t/paycheck";
	DialogID[playerid][0] = bizid+100; //SetPVarInt(playerid, "Bouse", bizid);
	MenuOperation[playerid] = 123;

	new caption[24+32+3];
	format(caption, sizeof(caption), "МЕНЮ УПРАВЛЕНИЯ: %s[%d]", BizInfo[bizid][bDiscription], bizid);
	ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_TABLIST, caption, listitems, "OK", "Назад");//BIZ_CONTROL_MENU
}


stock BizControlMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{

//printf("BizListItem - playerid: %d, bouse: %d, listitem: %d, inputtext: %s, Operation: %d", playerid, bouse, listitem, inputtext, MenuOperation[playerid]);
	if(dialogid != BIZ_CONTROL_MENU) return 1;//для владения несколькими бизами
	if(!response)
	{
		PropertyHelp(playerid);//если вошли в //biz_ControlMenu
		return 1;
	}
	new bouse = GetPVarInt(playerid, "Bouse");
	if(MenuOperation[playerid] == 123)
	{//начальный вход в меню
//ОБРАБОТКА ВЫБОРА ПУНКТА
		if(listitem == 0)
		{
			PrintBizInfo(playerid, bouse);///bizinfo - информация по бизнесу
		}
		else if(listitem == 1)///sellbiz - продать бизнес\n
		{
			if( response &&
				!IsPlayerInRangeOfPoint(playerid, 8.0, BizInfo[bouse][bEntranceX],BizInfo[bouse][bEntranceY],BizInfo[bouse][bEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 100.0, BizInfo[bouse][bExitX],BizInfo[bouse][bExitY],BizInfo[bouse][bExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от вашего бизнеса !");
				return 1;
			}
			MenuOperation[playerid] = 1232;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_MSGBOX, BizInfo[bouse][bDiscription], "Вы действительно хотите \nпродать свой бизнес?", "OK", "Cancel");
		}
		else if(listitem == 2)//open - открыть/закрыть бизнес
		{
			if( response &&
				!IsPlayerInRangeOfPoint(playerid, 8.0, BizInfo[bouse][bEntranceX],BizInfo[bouse][bEntranceY],BizInfo[bouse][bEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 100.0,BizInfo[bouse][bExitX],BizInfo[bouse][bExitY],BizInfo[bouse][bExitZ]) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от вашего бизнеса !");
				return 1;
			}
			if( !(BizInfo[bouse][bMetal] > 48 && BizInfo[bouse][bTextiles] > 48 && BizInfo[bouse][bProvisions] > 48 && BizInfo[bouse][bTree] > 48) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Чтобы открыть, в бизнесе должны быть материалы для производства товаров, не менее 48 шт. каждого вида !");
				return 1;
			}
			if(BizInfo[bouse][bLock] == 1)
			{
				BizInfo[bouse][bLock] = 0;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				BizInfo[bouse][bLock] = 1;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if(listitem == 3)///bizfee - установить входную плату
		{
			format(strings, sizeof(strings), "Сумма входной платы - $%d.\n\
				Введите сумму входной платы.\n\
				Минимум - $1, Максимум - $1000.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bEntranceCost]);
			MenuOperation[playerid] = 124;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 4)///bizbuyprods - установить цену покупки продуктов
		{
			format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
				Введите процент покупки.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bBuyProd]);
			MenuOperation[playerid] = 125;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 5)///bizsellprods - установить цену продажи товаров
		{
			format(strings, sizeof(strings), "Процент продажи товаров = %d%%.\n\
				Введите процент продажи.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSellProd]);
			MenuOperation[playerid] = 126;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 6)///bizbank - пополнить денежную кассу
		{
			format(strings, sizeof(strings), "B кассе $%d.\n\
				Введите сумму перевода на счёт вашего бизнеса.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bTill], PlayerInfo[playerid][pBank]);
			MenuOperation[playerid] = 127;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 7)///bizinkas - установить минимальный остаток денег";
		{
			format(strings, sizeof(strings), "Мин. размер инкасации = $%d.\n\
				Введите ограничение для вывоза денег.\n\
				Минимум - $0, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bInkas], BizInfo[bouse][bTill]);
			MenuOperation[playerid] = 128;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
		}
		else if(listitem == 8)//exchange - биржа
		{
			MenuOperation[playerid] = 147;
	        EXCHANGE(playerid);//	MenuOperation[playerid] = 147;//146 свободная
		}
		else if(listitem == 9)//invite - пригласить сотрудников
		{
			MenuOperation[playerid] = 148;
			format(strings, sizeof(strings), "Кол-во работников - %d.\n\
				Введите ID игрока [playerid] \nили часть имени [PartOfName], \nкоторого хотите пригласить на работу.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bWorker]);
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, "ОТДЕЛ КАДРОВ", strings, "OK", "Cancel");
		}
		else if(listitem == 10)//paycheck - установить оплату
		{
			MenuOperation[playerid] = 149;
			format(strings, sizeof(strings), "Оплата работникам = $%d.\n\
				Введите сумму оплаты перевозчикам за рейс.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSalary], 1000*BizInfo[bouse][bLevel]);
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, "ОТДЕЛ КАДРОВ", strings, "OK", "Cancel");
		}
	}

//НАЧАЛО ОБРАБОТКИ ПУНКТОВ
	else if(MenuOperation[playerid] == 1232)///sellbiz - продать бизнес\n
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		//--------------------------------------------------------------
		if(PlayerInfo[playerid][pPurposeMurder] == 100+bouse) PlayerInfo[playerid][pPurposeMurder] = 0;
		//GivePlayerMoneyB(fbiz+bouse, playerid, BizInfo[bouse][bBuyPrice]/2);
		if(BizInfo[bouse][bTill] < 0) { GivePlayerMoneyB(fbiz+bouse, playerid, BizInfo[bouse][bTill]); BizInfo[bouse][bTill] = 0; }
		//оплачивает минус
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] != bouse) continue;
			MyBizz[playerid][limit] = NOT_KEY;
			break;
		}
		//OnPlayerStatsUpdate(playerid);
		format(strings, sizeof(strings), "%s has sell biz %d", PlayerName(playerid), bouse);
		Log(BUY,strings);

		new text_info[19+20+24];
	   	format(text_info, sizeof(text_info), "[ %s ]",BizInfo[bouse][bDiscription]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+bouse], 0xEEEE88FF, strings);
		Update3DTextLabelEx(bEntranceText3D[bouse], 0xEEEE88FF, text_info);

		OnBizInit(bouse);//начальная инициализация переменных
#if defined vw_sql//#endif
		SaveBiz(bouse);
#endif
		//format(strings, sizeof(strings), "~y~Congratulations~n~~w~You have sold your property for ~n~~g~$%d", BizInfo[bouse][bBuyPrice]/2);
		GameTextForPlayerEx(playerid, "~y~Congratulations~n~~w~You have sold your property", 10000, 3);
	}
	//------------------------------------------------------------------

	else if(MenuOperation[playerid] == 124)///bizfee
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		if( response &&
			(strval(inputtext) < 1 || strval(inputtext) > 1000))//для экономики
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Минимальная цена входа - $1, Максимальная цена входа - $1000.");
			format(strings, sizeof(strings), "Сумма входной платы - $%d.\n\
				Введите сумму входной платы.\n\
				Минимальная цена входа - $1, \nМаксимальная цена входа - $1000.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bEntranceCost]);
			MenuOperation[playerid] = 124;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		BizInfo[bouse][bEntranceCost] = strval(inputtext);
		format(strings, sizeof(strings), "Cтоимость входа установлена в $%d.", BizInfo[bouse][bEntranceCost]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 125)///bizbuyprods - установить цену покупки продуктов
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		if( response &&
			(strval(inputtext) < 10 || strval(inputtext) > 90))//для экономики
		{
			format(strings, sizeof(strings), "Процент покупки продуктов = %d%%.\n\
				Введите процент покупки продуктов.\n\
				Минимальное значение - 10%%, \nМаксимальное значение - 90%%.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bBuyProd]);
			MenuOperation[playerid] = 125;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		if(BizInfo[bouse][bTill] < 2250 && strval(inputtext) > BizInfo[bouse][bBuyProd])
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы не можете повышать процент покупки при наличии в кассе менее $2250");
			return 1;
		}
		if(bouse == 80)
		{//если Склад, то покупать не дешевле чем продаёт Порт
		    if(strval(inputtext) < BizInfo[81][bSellProd]+5 || strval(inputtext) > 30)
		    {
				format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bBuyProd], BizInfo[81][bSellProd]+5, 30);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else if(bouse == 81)
		{//если Порт, то покупать не дешевле чем продаёт Склад в тройном размере
		    if(strval(inputtext) < BizInfo[80][bBuyProd]*3+10+5 || strval(inputtext) > 100)
		    {
				format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bBuyProd], BizInfo[80][bBuyProd]*3+10+5, 100);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else //if(bouse != 80)
		{//если любой другой бизд, то покупать не дешевле чем продаёт Склад
		    if(strval(inputtext) < BizInfo[80][bSellProd]+10 || strval(inputtext) > 49)
		    {
				format(strings, sizeof(strings), "Процент покупки сырья = %d%%.\n\
					Введите процент покупки.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bBuyProd], BizInfo[80][bSellProd]+10, 49);
				MenuOperation[playerid] = 125;
				ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		BizInfo[bouse][bBuyProd] = strval(inputtext);
		format(strings, sizeof(strings), "Процент покупки продуктов установлен - %d%%\%%.", BizInfo[bouse][bBuyProd]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 126)///bizsellprods - установить цену продажи товаров
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		if( response &&
			(strval(inputtext) < 20 || strval(inputtext) > 100))//для экономики
		{
			format(strings, sizeof(strings), "Процент продажи товаров = %d%%.\n\
				Введите процент продажи.\n\
				Минимальное значение - 20%%, \nМаксимальное значение - 100%%.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSellProd]);
			MenuOperation[playerid] = 126;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		if(bouse == 80)
		{//если Порт, то продовать не больше чем покупает Склад
			if(strval(inputtext) < 1 || strval(inputtext) > 35)
			{
				format(strings, sizeof(strings), "Процент продажи товаров = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSellProd], 1, 35);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else if(bouse == 81)
		{//если Порт, то продовать не больше чем покупает Склад
			if(strval(inputtext) < 1 || strval(inputtext) > BizInfo[80][bBuyProd]-5)
			{
				format(strings, sizeof(strings), "Процент продажи товаров = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSellProd], 1, BizInfo[80][bBuyProd]-5);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		else //if(bouse != 81 &&
		{//если Биз, то продовать не больше чем покупает Склад помноженный на 3
			if(strval(inputtext) < 1 || strval(inputtext) > BizInfo[80][bBuyProd]*3-10)
			{
				format(strings, sizeof(strings), "Процент продажи товаров = %d%%.\n\
					Введите процент продажи.\n\
					Минимум - %d%%, Максимум - %d%%.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSellProd], 1, BizInfo[80][bBuyProd]*3-10);
				MenuOperation[playerid] = 126;
				ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
				return 1;
			}
		}
		BizInfo[bouse][bSellProd] = strval(inputtext);
		format(strings, sizeof(strings), "Процент продажи товаров (оплаты покупателем) установлен на %d%%\%%.", BizInfo[bouse][bSellProd]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 127)///bizbank
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		new cashdeposit = strval(inputtext);
		if(	response &&
			(PlayerInfo[playerid][pBank] < cashdeposit || cashdeposit < 1) )
		{
			//SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько наличных для этого !");
			format(strings, sizeof(strings), "У вас нет столько наличных для этого !\n\
				B кассе $%d.\n\
				Введите сумму перевода на счёт вашего бизнеса.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bTill], PlayerInfo[playerid][pBank]);
			MenuOperation[playerid] = 127;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		if( response &&
			!IsPlayerInRangeOfPoint(playerid, 8.0, BizInfo[bouse][bEntranceX],BizInfo[bouse][bEntranceY],BizInfo[bouse][bEntranceZ]) &&
			!IsPlayerInRangeOfPoint(playerid, 100.0, BizInfo[bouse][bExitX],BizInfo[bouse][bExitY],BizInfo[bouse][bExitZ]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от вашего бизнеса !");
			return 1;
		}
		GivePlayerMoneyB(fbiz+bouse, playerid, -cashdeposit);
		//OnGangsExtortionBiz(bouse, cashdeposit);
		BizInfo[bouse][bTill] += cashdeposit;
		format(strings, sizeof(strings), "  Bы пополнили вашу кассу на $%d. Итого: $%d ", cashdeposit, BizInfo[bouse][bTill]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		//SaveBiz(bouse);
	}
	else if(MenuOperation[playerid] == 128)///bizinkas - установить минимальный остаток денег";
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		if( response &&
			(strval(inputtext) < 1 || strval(inputtext) > BizInfo[bouse][bTill]) )
		{
			format(strings, sizeof(strings), "Мин. размер инкасации = $%d.\n\
				Введите ограничение для вывоза денег.\n\
				Минимум - $0, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bInkas], BizInfo[bouse][bTill]);
			MenuOperation[playerid] = 128;
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		BizInfo[bouse][bInkas] = strval(inputtext);
		format(strings, sizeof(strings), "* Минимальное кол-во денег в бизе установлено $%d.", BizInfo[bouse][bInkas]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}

	else if(MenuOperation[playerid] == 148)//invite - пригласить сотрудников
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }

		if( response &&
			(strval(inputtext) < 1 || strval(inputtext) > 10))
		{
			MenuOperation[playerid] = 148;
			format(strings, sizeof(strings), "Кол-во работников - %d.\n\
				Введите ID игрока [playerid] \nили часть имени [PartOfName], \nкоторого хотите пригласить на работу.\n\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bWorker]);
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		//BizInfo[bouse][bWorker] ++;

		new giveplayerid = ReturnUser(inputtext);
		if( !IsPlayerConnected(giveplayerid) )
		{
			format(strings, sizeof(strings), "   ID:%d отсутствует на сервере.", giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
		}
		//BizInfo[bouse][bWorker] = strval(inputtext);
		//format(strings, sizeof(strings), "Кол-во работников установлено - %d.", BizInfo[bouse][bWorker]);
		//SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	else if(MenuOperation[playerid] == 149)//paycheck - установить оплату
	{
		if(!response) { biz_ControlMenu(playerid, bouse); return 1; }
		if( response &&
			(strval(inputtext) < 1 || strval(inputtext) > 1000*BizInfo[bouse][bLevel]))
		{
			MenuOperation[playerid] = 149;
			format(strings, sizeof(strings), "Оплата работникам = $%d.\n\
				Введите сумму оплаты перевозчикам за рейс.\n\
				Минимум - $1, Максимум - $%d.\
				\n\n\t{8CAA63}По окончанию ввода нажмите OK.", BizInfo[bouse][bSalary], 1000*BizInfo[bouse][bLevel]);
			ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_INPUT, BizInfo[bouse][bDiscription], strings, "OK", "Cancel");
			return 1;
		}
		BizInfo[bouse][bSalary] = strval(inputtext);
		//if(bouse == 81) compcost = BizInfo[81][bSalary];
		format(strings, sizeof(strings), "Оплата работникам установлена - $%d.", BizInfo[bouse][bSalary]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}

	return 1;
}


stock PrintBizInfo(playerid, bizid)//вызывается по команде bizinfo
{
	new msgitems[8*(128+1+3+10+10+10)];
	new coordsstring[128+1+3+10+10+10];

	new locked[8];
	if(BizInfo[bizid][bLock] == 1) locked = "Закрыт";
	else locked = "Открыт";
//*** Ammunation 6. 5 уровень Индустрии развлечений. Закрыт ***
//до следующего уровня
//(level+1)*levelexp*10000 + SBizInfo[sbiz][sbImport] = (5+1)*4*10000 = 240000 + SBizInfo[sbiz][sbImport]
//(SBizInfo[sbiz][sbExport] - SBizInfo[sbiz][sbImport]) = 240000
	new caption[47+64+4+24+8];
	format(caption, sizeof(caption), "*** {FFFFFF}%s. %d уровень %s. %s {0080FF}***",
		BizInfo[bizid][bDiscription], BizInfo[bizid][bLevel], TypeBranch(BizInfo[bizid][bBranch]), locked);

	strcat(msgitems, "_______________________________________\n"); //SendClientMessage(playerid, COLOR_GREEN, "_______________________________________");

	format(coordsstring, sizeof(coordsstring), "{FF6600}Цена за вход: {33AA33}$%d\t{FF6600}В Кассе: {33AA33}$%d\t{FF6600}Резерв: {33AA33}$%d\n",//%%\%%
		BizInfo[bizid][bEntranceCost], BizInfo[bizid][bTill], BizInfo[bizid][bInkas]);
	strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

	format(coordsstring, sizeof(coordsstring), "{FF6600}Металл:{FFFFFF}%d\t{FF6600}Текстиль:{FFFFFF}%d\t{FF6600}Прод-ие:{FFFFFF}%d\t{FF6600}Древесина:{FFFFFF}%d\t{FF6600}Топливо:{FFFFFF}%d\n",
		BizInfo[bizid][bMetal],BizInfo[bizid][bTextiles],BizInfo[bizid][bProvisions],BizInfo[bizid][bTree],BizInfo[bizid][bFuel]);
	strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

	new Float: buyprice = (compcost*(100+BizInfo[bizid][bBuyProd])/100.0);//цена покупки сырья
	new Float: sellprice = (compcost*(100+BizInfo[bizid][bSellProd])/100.0);//цена продажи товаров
	format(coordsstring, sizeof(coordsstring), "{FF6600}Товаров:{FFFFFF}%d\t{FF6600}Покупка:{33AA33}$%.2f{FFFFFF}[%d %%]\t{FF6600}Продажа:{33AA33}$%.2f{FFFFFF}[%d %%]\n",
		BizInfo[bizid][bProducts], buyprice, BizInfo[bizid][bBuyProd], sellprice, BizInfo[bizid][bSellProd]);
	strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

	format(coordsstring, sizeof(coordsstring), "{FF6600}Рабочих:{FFFFFF}%d {FF6600}Оплата:{33AA33}$%d\n{FF6600}Импорт:{33AA33}$%d {FF6600}Экспорт:{33AA33}$%d {FF6600}Баланс:{33AA33}$%d\n",
		BizInfo[bizid][bWorker], BizInfo[bizid][bSalary],
		BizInfo[bizid][bImport], BizInfo[bizid][bExport],
		(BizInfo[bizid][bExport]-BizInfo[bizid][bImport]));
	strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);

	format(coordsstring, sizeof(coordsstring), "{FF6600}Дата покупки: {FFFFFF}%s[%d]\n{FF6600}Содержание в час: {33AA33}$%d\n",
		getDate(BizInfo[bizid][bDate]), BizInfo[bizid][bDate], BizInfo[bizid][bExpenses]);
	strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);


	new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
	new olddate = BizInfo[bizid][bDate];
//если в кассе денег хватает на покупку 100 продуктов
	if(BizInfo[bizid][bLevel] <= 1 && (curdate-olddate) <= gCheckProp)//gCheckProp = 7
	{
		format(coordsstring, sizeof(coordsstring), "{0080FF}Требуется поднять уровень, чтобы бизнес не обанкротился.\n{FFFFFF}Осталось %d дней.\n",
			gCheckProp-(curdate-olddate));
		strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}
	//if(GetProducts(b, BizInfo[b][bBranch]) >= 8*24) continue;
	new Float: price = compcost*(100+BizInfo[bizid][bBuyProd])/100.0;
	if( BizInfo[bizid][bProducts] < 100 || BizInfo[bizid][bTill] < floatround(100*price, floatround_floor) )
//если в бизнесе менее 100 товаров, то забрать //если в кассе денег не хватает на покупку 100 продуктов, то забрать
	{//если бизнес куплен больше 15 дней и до сих пор не вышел из нулевой рентабельности, то забрать

		format(coordsstring, sizeof(coordsstring), "Требуется {FFFFFF}%d{FF6600} товаров или {33AA33}$%d{FF6600},\nчтобы бизнес не обанкротился.\n",
			100-BizInfo[bizid][bProducts], floatround(100*price, floatround_floor)-BizInfo[bizid][bTill]);
		strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	}

	new export = (BizInfo[bizid][bLevel]+1)*levelexp*10000 - (BizInfo[bizid][bExport]-BizInfo[bizid][bImport]);//рентабильность = сколько надо - сколько есть
//((5+1)*4*10000) - (2478048-2321532) = 83484
	new Float: prod_export = export/sellprice;//кол-во товаров для экспорта = рентабильность/цена продажи ед. товара
////(((5+1)*4*10000) - (2478048-2321532))/(15*(100+50)/100) = 3710

	new Float: prod_onehour = 8*24*(100+BizInfo[bizid][bLevel])/100.0 - 1;//товаров в час производится
//8*24*(100+2)/100 - 1 = 194,84
	new money_hours = floatround((prod_onehour - 8*24)*sellprice + 8*24*(sellprice-buyprice)); // прибыль в час 355.5$
//new hours = floatround(prod/prod_onehour, floatround_ceil);//кол-во часов необходимое, чтобы получить недостающие товары
	new hours = floatround((export - BizInfo[bizid][bProducts]*sellprice - GetProducts(bizid)*buyprice)/money_hours, floatround_ceil);
//кол-во часов необходимое, чтобы получить новый уровень 7033/355.5=19ч

 	/*new prod;//недостоющее кол-во товаров
	if(BizInfo[bizid][bProducts] < prod_export) prod = floatround(prod_export, floatround_ceil) - BizInfo[bizid][bProducts];
	else prod = 0;*/

 	new resurs = 8*24*hours;//кол-во затраченного сырья для производства недостающего кол-ва товаров
	if(GetProducts(bizid) < resurs) resurs = resurs - GetProducts(bizid);
	else resurs = 0;// - кол-во недостающего сырья

	if(hours <= 0)
	{
		format(coordsstring, sizeof(coordsstring), "До %d-го уровня требуется: {FFFFFF}продать %.0f товаров\nи получить с этого $%d дохода.\n", (BizInfo[bizid][bLevel]+1),
			prod_export, export);
	}
	else
	{
		format(coordsstring, sizeof(coordsstring), "До %d-го уровня требуется: {FFFFFF}%d часов\nи купить %d сырья\n", (BizInfo[bizid][bLevel]+1),
			hours, resurs);
	}
	strcat(msgitems, coordsstring); //SendClientMessage(playerid, COLOR_ORANGE, coordsstring);
	strcat(msgitems, "_______________________________________\n"); //SendClientMessage(playerid, COLOR_GREEN, "_______________________________________");

	if(strlen(msgitems) > sizeof(msgitems))
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error19: Business Info - %s[%d], strlen(msgitem): %d, sizeof(msgitem): %d", PlayerName(playerid), playerid, strlen(msgitems), sizeof(msgitems));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogGap(playerid, BIZ_CONTROL_MENU, DIALOG_STYLE_MSGBOX, caption, msgitems, "OK", "Назад");
	gDialogStatus[playerid][1] = 5;//таймер на 5 секунд
	return 1;
}





stock OnSaveDateBizz(playerid, biz)//вызывается из ShowPlayerDialogGap(playerid, HOUSE_DIALOG, DIALOG_STYLE_MSGBOX, BizInfo[bouse][bDiscription],msgitem, "YES", "NO");
{   //для учета посещения недвижимости, чтобы отобрать её при долгом отсутствии
	#pragma unused playerid
	new curdate = getdate();//Получает текущий день в году
	BizInfo[biz][bDate] = curdate;//записать день захода в бизнесс(на сервер)
	new strings[MAX_STRING];
	format(strings, sizeof(strings), "МЕНЕДЖЕР: До свидание %s. Не забывайте посещать нас. (curdate=%d)", PlayerName(playerid), curdate);
	SendClientMessage(playerid, COLOR_YELLOW, strings);
	//SaveBiz(biz);
}

stock OnCheckBizz()//вызывается из SyncTime()
{   //проверка собственности каждый час, т.е. купленных бизов
	for(new b = 1; b < MAX_BIZ-2; b++)
	{   //кроме банка
		if(BizInfo[b][bOwned] == 0) continue;
		if(GetProducts(b) >= 8*24) continue;
		new Float: price = compcost*(100+BizInfo[b][bBuyProd])/100.0;
		new olddate = BizInfo[b][bDate];
		new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
//если в кассе денег хватает на покупку 100 продуктов
		if( (BizInfo[b][bProducts] < 100 && BizInfo[b][bTill] < floatround(100*price, floatround_floor)) ||
			(BizInfo[b][bLevel] <= 1 && curdate-olddate > gCheckProp)
		  )//если в бизнесе менее 100 товаров, то забрать //если в кассе денег не хватает на покупку 100 продуктов, то забрать
		{//если бизнес куплен больше 15 дней и до сих пор не вышел из нулевой рентабельности, то забрать

			new strtmp[193];//106 + 24+2+24+3+3+1+10+10+10 = 193
			new playername[MAX_PLAYER_NAME];
			strmid(playername, BizInfo[b][bOwner], 0, strlen(BizInfo[b][bOwner]), MAX_PLAYER_NAME);
			//mysql_real_escape_string(playername, playername);
			new giveplayerid = ReturnUser( playername );
			if( !IsPlayerConnected(giveplayerid) )
			{
				if(CheckExistPlayer(giveplayerid, playername) > 0) //return 1;
				{
		    		giveplayerid = MAX_PLAYERS-2;
		    		//new ToBase[107+10+24+3];
					//format(ToBase, sizeof(ToBase), "SELECT `ID`,`Name`,`Account`,`Bank`,`Bizz` FROM `players` WHERE `ID`=%d AND `Name`='%s' AND `Account`<%d", BizInfo[b][bOwned], playername, getdate());
					//if(mysql_num_rows() == 1) //дополнительно проверяем на данный момент принадлежность

		    		new ToBase[113];//71+24+3 = 98
					format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE `Name`='%s' AND `Account`>=%d LIMIT 1", playername, getdate());
					mysql_query(ToBase); mysql_store_result();
					if(mysql_num_rows()) //дополнительно проверяем на данный момент принадлежность
					{  //пропускаем бизы с премиум аккаунтами
						mysql_free_result();
						continue; //т.к. надо проверить бизы всех игроков
					}
					else mysql_free_result();

					/*format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bizz`="#NOT_KEY" WHERE `ID`=%d AND `Name`='%s'",
						sb, playername);
					mysql_query(ToBase);*/
				}
			}
			else
			{
				if(PlayerInfo[giveplayerid][pAccount] != 0) continue; //return 1;

				for(new limit = 0; limit < 10; limit++)
				{
					if(MyBizz[giveplayerid][limit] != b) continue;
					MyBizz[giveplayerid][limit] = NOT_KEY;
				}
				PlayerInfo[giveplayerid][pBizz] = NOT_KEY;
				//PlayerInfo[giveplayerid][pBank] += BizInfo[b][bBuyPrice];
				if(BizInfo[b][bTill] < 0) { GivePlayerMoneyB(fbiz+b, giveplayerid, BizInfo[b][bTill]); BizInfo[b][bTill] = 0; }
			}
			//--------------------------------------------------------------
			format(strtmp, sizeof(strtmp), "БАНКРОТ: Бизнесс %s[%d] %s'а был выставлен на аукцион и продан (Level=%d, Products=%d<100, Till=$%d<$100*%.1f)",
				BizInfo[b][bDiscription], b, BizInfo[b][bOwner], BizInfo[b][bLevel], BizInfo[b][bProducts], BizInfo[b][bTill], price);
			SendClientMessageToAll(0xEEEE88FF, strtmp);

			//ИНФОРМИРОВАНИЕ
			format(strtmp, sizeof(strtmp), "REAL ESTATE: %s has sell biz %d (Level=%d, curdate:%d-olddate:%d>%d, Products=%d<100, Till=$%d<$100*%.1f)",
				playername, b, BizInfo[b][bLevel], curdate,olddate,gCheckProp, BizInfo[b][bProducts], BizInfo[b][bTill], price);
			Log(BUY,strtmp);

			OnBizInit(b);
#if defined vw_sql//#endif
			SaveBiz(b);
#endif
			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]",BizInfo[b][bDiscription]);
			//Update3DTextLabelText(text3D[MAX_HOUSE+b], 0xEEEE88FF, strtmp);
			Update3DTextLabelEx(bEntranceText3D[b], 0xEEEE88FF, text_info);
		}
	}
	return 1;
}


//Для бизнесов
stock OnGangsExtortionBiz(bizid, money)//вызывается при изменении денег в бизе
//bizid - ID входящего, money - сумма денег которую потратил входящий
{
	if(money <= 0) return 1;
	//if(BizInfo[bizid][bOwned] > 0)
	if(!(bizid >= 4 && bizid <= 14))
	{//если это оружейка
		BizInfo[bizid][bTill] += money;//перечисляем всю сумму, чтобы потом отнять половину
		//BizInfo[bizid][bExport] += money;
	}
	else {
		BizInfo[0][bTill] += money; //BizInfo[0][bExport] += money;
	}
	//else BizInfo[0][bProducts] += money;
//Биз сам себя окупает на продаже и покупке продуктов, т.е. дальнобои работают
//но чтобы люди не скупали бизы и не выкачивали кассу.
	//--------------------------------------------------------------------------
    //if(!strcmp(BizInfo[bizid][bExtortion], "No-One", true))//Сравнивает две строки друг с другом
    if(BizInfo[bizid][bExtortion] == 0)//Сравнивает две строки друг с другом
	{   //если ни кем не контролируется
	    return 1;
	}
	//new gangsname[20];
	for(new i = 1; i <= TEAM_MAFIA; i++)
	{   //сканируем все банды
		//strmid(gangsname, FamilyInfo[i][fName], 0, strlen(FamilyInfo[i][fName]), sizeof(gangsname));
		//Извлекает диапазон символов из строки.
		//if(!strcmp(BizInfo[bizid][bExtortion], FamilyInfo[i][fName], true))//если вошёл в биз совладелец
		//если имя контролирующей банды этот бизнес совпало с найденным
		if(i == BizInfo[bizid][bExtortion])//FamilyInfo[i][NumberFamily]
		{
		    //для экономики
		    new value = floatround(money*50/100);//50 процентов от суммы перечислить в общак банды
		    if(BizInfo[bizid][bOwned] > 0)
		    {
		    	FamilyInfo[i][fBank] += value;
				if(!(bizid >= 4 && bizid <= 14))
				{//если это оружейка
					BizInfo[bizid][bTill] -= value;//уменьшить на эту сумму количество денег в бизе
					BizInfo[bizid][bExport] -= value;
				}
				else {
					BizInfo[0][bTill] -= value; //BizInfo[0][bImport] += value;
				}
			}
		    //else BizInfo[0][bTill] -= value;
			//format(strings, sizeof(strings), "Вам было перечислено $%d в общак.", value);
			//SendFamilyMessage(i, strings);
			break;
		}
	}
	return 1;
}




stock ShopMenu(playerid)//замены устаревшей ф-ии ShowMenuForPlayerEx(mShop, playerid);
{//вызывается из biz_OnEnterCheckpoint(playerid)
	new bigmsgitem[336+229+1];
	strcat(bigmsgitem, "№\tНаименование\tЦена\n");
	strcat(bigmsgitem, "{FFFFFF}1.\t{00FF00}Телефон \t{33AA33}$50\
\n{FFFFFF}2.\t{00FF00}Лотерейка \t{33AA33}$150\
\n{FFFFFF}3.\t{00FF00}Шлем \t{33AA33}$500\
\n{FFFFFF}4.\t{00FF00}Игральные кости \t{33AA33}$50\
\n{FFFFFF}5.\t{00FF00}Отмычка \t{33AA33}$100\
\n{FFFFFF}6.\t{00FF00}Противоугонка \t{33AA33}$1000\
\n{FFFFFF}7.\t{00FF00}Антирадар \t{33AA33}$1200");

	strcat(bigmsgitem, "\n{FFFFFF}8.\t{00FF00}GPS-Навигатор \t{33AA33}$2500\
\n{FFFFFF}9.\t{00FF00}Радио \t{33AA33}$2500\
\n{FFFFFF}10.\t{00FF00}Фотокамера \t{33AA33}$500\
\n{FFFFFF}11.\t{00FF00}Цветы \t{33AA33}$20\
\n{FFFFFF}12.\t{00FF00}Сигары: \t{33AA33}$100");
	//new caption[70];
	//format(caption, sizeof(caption), "Shop 24-7: %s[%d]", PlayerName(playerid), playerid);
	return  ShowPlayerDialogGap(playerid, SHOP_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "Shop 24-7", bigmsgitem, "Купить", "Выход");
}

stock ShopMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != SHOP_DIALOG) return 1;
	if(!response) return 1;
	//new msgitem[256+1];
	new bizid = GetBizLocation(playerid)-1;
	new payout;
	//new paycheck = -1;
    if(BizInfo[bizid][bProducts] <= 0)
    {
		GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Shop 24-7", 5000, 1);
    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
    	return 1;
	}
	if(listitem == 0)
	{
        payout = 50;
		if(GetPlayerMoneyH(playerid) > payout)
		{
		    if(PlayerInfo[playerid][pPnumber] > 1000)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Мобильный Tелефон !");
		        ShopMenu(playerid);
		        return 1;
		    }
		    else
		    {
			    if(PlayerInfo[playerid][pTraderPerk] > 0)
			    {
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
			    }
				new randphone = random(7999999);//minimum 10000  max 99999
				if(randphone < 8000000) randphone = 1000000 + randphone;
				PlayerInfo[playerid][pPnumber] = randphone;
				format(strings, sizeof(strings), "Hовый номер вашего мобильного теперь %d", randphone);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
				SendClientMessage(playerid, COLOR_GREY, "   Вы можете узнать его в любое время введите /items");
				SendClientMessage(playerid, COLOR_GREY, "Подсказка: Теперь вы можете ввести /phonehelp, чтобы увидеть ваши команды для мобильника.");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	
	else if(listitem == 1)
	{
	        payout = 150;
			if(GetPlayerMoneyH(playerid) > payout)
			{
			    if(PlayerInfo[playerid][pLottoNr] > 0)
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Лотерейный Билет !");
			        ShopMenu(playerid);
			        return 1;
			    }
			    else
			    {
				    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    {
						payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
					}
					new lottonr = random(80);
					PlayerInfo[playerid][pLottoNr] = lottonr;
					format(strings, sizeof(strings), "Bы купили Лотерейный Билет с номером: %d.", lottonr);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
					//paycheck = row;
				}
			}
			else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег!");
	}
	else if(listitem == 2)
	{//Helmet
        payout = 500;
		if(GetPlayerMoneyH(playerid) > payout)
		{
		    if(PlayerInfo[playerid][pHelmet] > 1)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Шлем !");
		        ShopMenu(playerid);
		        return 1;
		    }
		    else
		    {
			    if(PlayerInfo[playerid][pTraderPerk] > 0)
			    {
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
                PlayerInfo[playerid][pHelmet] = 18645;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Шлем приобретен. Вы можете снять его в любое время !");
				//SendClientMessage(playerid, COLOR_GREY, "Подсказка: Введите /number <id/name>.");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 3)
	{//Helmet
        payout = 50;
		if(GetPlayerMoneyH(playerid) > payout)
		{
		    if(PlayerInfo[playerid][pDice] != 0)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Игральные Kости !");
		        ShopMenu(playerid);
		        return 1;
		    }
			else
			{
				if(PlayerInfo[playerid][pTraderPerk] > 0)
			    {
					payout -= PlayerInfo[playerid][pTraderPerk]/100;
				}
				PlayerInfo[playerid][pDice] = 1;//для сохранения
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Kости Игральные приобретены теперь вы можете их бросить.");
				SendClientMessage(playerid, COLOR_GREY, "Подсказка: Введите /dice ");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 4)
	{//AddMenuItem(mShop, 0, 		"Skeleton Key  $100");
        payout = 100;
        if(PlayerInfo[playerid][pJob] != CARJACKER)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы - не АвтоУгонщик !");
	        ShopMenu(playerid);
	        return 1;
		}
		else if(GetPlayerMoneyH(playerid) > payout)
		{
			if(PlayerInfo[playerid][pTraderPerk] > 0)
	    	{
				payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
			}
			GivePVarInt(playerid, "SkeletonKey", +1);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Отмычка приобретена. Вы можете открыть чужую машину.");
			SendClientMessage(playerid, COLOR_GREY, "Подсказка: для взлома машины введите /steal ");
			//paycheck = row;
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 5)
	{//	AddMenuItem(mShop, 0, 		"Vehicle Lock   $1000");
		new carid = LastCar[playerid];
		if(carid <= 0)//!! ДОРАБОТАТЬ добавить проверку по типу на грузовички
		{
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет подходящей Машины !");
	        ShopMenu(playerid);
	        return 1;
		}
		else
		{
	        payout = 1000;
			if(GetPlayerMoneyH(playerid) > payout)
			{
			    if(VehInfo[carid][cLock] >= 10)
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   На эту машину уже установлен Замок !");
			        ShopMenu(playerid);
			        return 1;
			    }
			    else
			    {
					if(PlayerInfo[playerid][pTraderPerk] > 0)
			    	{
						payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
					}
					VehInfo[carid][cLock] = 10;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "Противоугонная система на ваш автомобиль установлена.");
					SendClientMessage(playerid, COLOR_GREY, "Подсказка: для закрытия машины введите /lock или нажмите клавишы "#SNEAK_ABOUT"+"#PED_SPRINT);	//ALT+SPACE ~k~~SNEAK_ABOUT~ + ~k~~PED_SPRINT~
					//paycheck = row;
				}
			}
			else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
		}
	}
	else if(listitem == 6)
	{
        payout = 1200;
		if(GetPlayerMoneyH(playerid) > payout)//для антирадара
		{
		    if(PlayerInfo[playerid][pAntiradar] != 0)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Aнтирадар !");
		        ShopMenu(playerid);
		        return 1;
		    }
		    else
			{
				if(PlayerInfo[playerid][pTraderPerk] > 0)
			    {
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
				PlayerInfo[playerid][pAntiradar] = 1;//для сохранения
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Aнтирадар приобретен !");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 7)
	{
        payout = 2500;
		if(GetPlayerMoneyH(playerid) > payout)
		{
		    if(PlayerInfo[playerid][pGPS] != 0)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть GPS-Навигатор !");
		        ShopMenu(playerid);
		        return 1;
		    }
		    else
			{
			    if(PlayerInfo[playerid][pTraderPerk] > 0)
		    	{
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
				PlayerInfo[playerid][pGPS] = 1;//для сохранения
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "GPS-Навигатор приобретен.");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 8)
	{//MP3-Player
        payout = 2500;
		if(GetPlayerMoneyH(playerid) > payout)
		{
		    if(PlayerInfo[playerid][pCDPlayer] == 1)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть MP3-проигрыватель !");
		        ShopMenu(playerid);
		        return 1;
		    }
		    else
		    {
			    if(PlayerInfo[playerid][pTraderPerk] > 0)
		    	{
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
				PlayerInfo[playerid][pCDPlayer] = 1;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "MP3-проигрыватель приобретен.");
				SendClientMessage(playerid, COLOR_GREY, "Подсказка: Введите /music");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 9)
	{//PhotoCamera
        payout = 500;
		if(GetPlayerMoneyH(playerid) > payout)
		{
			new Gun, Ammo;
			GetPlayerWeaponData(playerid, 9, Gun, Ammo);
			if(Gun == 43 && Ammo > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть фотокамера !");
		        ShopMenu(playerid);
		        return 1;
			}
		    else
		    {
			    if(PlayerInfo[playerid][pTraderPerk] > 0)
		    	{
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
				GivePlayerWeaponEx(playerid, 43, 36);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Фотокамера приобретена.");
				//SendClientMessage(playerid, COLOR_GREY, "Подсказка: Введите /music");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 10)
	{//Flowers
        payout = 20;
	    if(GetPlayerMoneyH(playerid) > payout)
		{
			new Gun, Ammo;
			GetPlayerWeaponData(playerid, 10, Gun, Ammo);
			if(Gun == 14)// && Ammo > 0
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть цветы !");
		        ShopMenu(playerid);
		        return 1;
			}
		    else
		    {
			    if(PlayerInfo[playerid][pTraderPerk] > 0)
		    	{
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
				GivePlayerWeaponEx(playerid, 14, 1);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вы купили букет цветов.");
				//SendClientMessage(playerid, COLOR_GREY, "Подсказка: Введите /music");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	else if(listitem == 11)
	{//Cigars
        payout = 100;
	    if(GetPlayerMoneyH(playerid) > payout)
		{
		    if(PlayerInfo[playerid][pCigars] >= 9)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Сигары !");
		        ShopMenu(playerid);
		        return 1;
		    }
			else
			{
				if(PlayerInfo[playerid][pTraderPerk] > 0)
			    {
					payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
				}
				PlayerInfo[playerid][pCigars] += 1;//для сохранения
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Сигары приобретены теперь вы можете их курить.");
				SendClientMessage(playerid, COLOR_GREY, "Подсказка: Введите /smoke потом /smokef");
				//paycheck = row;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
	}
	if(GetPlayerMoneyH(playerid) > payout && listitem != -1)
	{
		GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
		if(SBizInfo[9][sbProducts] > 0)
		{//General Store
			OnGangsExtortionSBiz(9, payout/2);
			SBizInfo[9][sbProducts] --;
		}
		OnGangsExtortionBiz(bizid, payout/2);
		//BizInfo[bizid][bProducts] --;
		//listitem = -1;
	}
	ShopMenu(playerid);
/*
	MenuOperation[playerid] = 121;
	new caption[16+36];
	format(caption, sizeof(caption), "Для фракции: %s", GetFamilyName(GetPVarInt(playerid, "Family")) );
	ShowPlayerDialogEx(playerid, TRANSFER_DIALOG, DIALOG_STYLE_INPUT, caption, "Введите сумму перевода. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
*/
	return 1;
}


stock biz_OnEnterCheckpoint(playerid)
{
	new bizid = GetBizLocation(playerid)-1;
	if(GetCheckpointType(playerid) == CP_BANK)//для банка
	{
 		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mBank, playerid);
	}
 	else if(	GetCheckpointType(playerid) == CP_AMMU1 || GetCheckpointType(playerid) == CP_AMMU2 ||
		GetCheckpointType(playerid) == CP_AMMU3 || GetCheckpointType(playerid) == CP_AMMU4 ||
		GetCheckpointType(playerid) == CP_AMMU5)//Для амуниций
	{
		/*if(BizInfo[bizid][bProducts] <= 0)
	    {
	        GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
	        PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return 1;
	    }*/
		if(PlayerInfo[playerid][pGunLic] != 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие!");
			return 1;
		}
		if(GetPlayerMoneyH(playerid) <= 500) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mAmmuNation, playerid);
	}
	//--------------------------------------------------------------------------
	else if(GetCheckpointType(playerid) == CP_SHOP1 || GetCheckpointType(playerid) == CP_SHOP2 ||
            GetCheckpointType(playerid) == CP_SHOP3 || GetCheckpointType(playerid) == CP_SHOP4 ||
            GetCheckpointType(playerid) == CP_SHOP5 || GetCheckpointType(playerid) == CP_SHOP6
			 || GetCheckpointType(playerid) == CP_SHOP13)//Для магазинов 24-7
	{    //если игрок вошел в контрольную отметку
	    if(BizInfo[bizid][bProducts] <= 0 && PlayerInfo[playerid][pLevel] > 3 //&& !gTutorial[playerid] && !gRealWar
			) {
	    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Shop 24-7", 5000, 1);
		}
		if(GetPlayerMoneyH(playerid) < 10)
		{
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет $10 наличных !");
			return 1;
		}
		//TogglePlayerControllableEx(playerid, 0);//обездвиживает
		//ShowMenuForPlayerEx(mShop, playerid);
		ShopMenu(playerid);
	}
	//==========================================================================
	else if(GetCheckpointType(playerid) == CP_BAR || GetCheckpointType(playerid) == CP_PUMP || GetCheckpointType(playerid) == CP_INN ||
			GetCheckpointType(playerid) == CP_PIGPEN || GetCheckpointType(playerid) == CP_STRIP ||
			GetCheckpointType(playerid) == CP_ALHAMBRA || GetCheckpointType(playerid) == CP_JIZZY)//для баров
	{
		//if(PlayerDrunk[playerid] < 50)
		if(GetPlayerDrunkLevel(playerid) < 50000)
		{   //если ты ещё не достаточно пьян
		    if(BizInfo[bizid][bProducts] <= 0 //&& !gTutorial[playerid] && !gRealWar
			) {
		    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Bar", 5000, 1);
			}
	   		if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
	 		TogglePlayerControllableEx(playerid, 0);//обездвиживает
			ShowMenuForPlayerEx(mBar, playerid);
		}
		else return SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
	}
	else if(GetCheckpointType(playerid) == CP_LCN || GetCheckpointType(playerid) == CP_YAKUZA)//для баров
	{
		Job2Menu(playerid);
	}
	//==========================================================================
	else if(GetCheckpointType(playerid) == CP_RESTAURANT_LS ||
			GetCheckpointType(playerid) == CP_RESTAURANT_SF ||
			GetCheckpointType(playerid) == CP_RESTAURANT_LV)
	{
	    if(BizInfo[bizid][bProducts] <= 0 //&& !gTutorial[playerid] && !gRealWar
		) {
	    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Restaurant", 5000, 1);
		}
		if(GetPlayerMoneyH(playerid) < 500) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
 		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mRestaurant, playerid);
	}
	//==========================================================================
	else if(GetCheckpointType(playerid) == CP_BURGER)	//Для закусочных
	{    //если игрок вошел в контрольную отметку
	    if(BizInfo[bizid][bProducts] <= 0) {
	        PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~BurgerShot", 5000, 1);
		}
		if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mBurgerShot, playerid);
	}
	else if(GetCheckpointType(playerid) == CP_CLUCKIN)//Для закусочных
	{
	    if(BizInfo[bizid][bProducts] <= 0) {
	    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~CluckinBell", 5000, 1);
		}
		if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mCluckinBell, playerid);
	}
	else if(GetCheckpointType(playerid) == CP_PIZZA)	//Для закусочных
	{
	    if(BizInfo[bizid][bProducts] <= 0) {
	    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~StackedPizza", 5000, 1);
		}
		if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mStackedPizza, playerid);
	}
	//==========================================================================
	else if(GetCheckpointType(playerid) == CP_LSPD || GetCheckpointType(playerid) == CP_SFPD
			|| GetCheckpointType(playerid) == CP_LVPD_UPFLOOR || GetCheckpointType(playerid) == CP_LVPD_DOWNFLOOR)
	{
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		ShowMenuForPlayerEx(mPoliceDepartment, playerid);
	}
	//==========================================================================

	else if(GetCheckpointType(playerid) == CP_CITYHALL_LS ||
		GetCheckpointType(playerid) == CP_CITYHALL_SF)//для устройства на работу
	{
		//if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1) return SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
		if(gParameter2[playerid] == 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "    В отчаянии Вы не можете получить работу !");
			SendClientMessage(playerid, COLOR_GREY, "    Вам необходимо развлечься: посетите клубы и потанцуйте !");
			return 1;
		}
 		//TogglePlayerControllableEx(playerid, 0);//обездвиживает
		//ShowMenuForPlayerEx(mJobMenu1_9, playerid);

		JobMenu(playerid);
	}
	return 1;
}


stock biz_OnEnterExitModShop(playerid, enterexit, interiorid)
{
	if(enterexit == 0) return 1;//1 - player entered// 0 - exited
//you exited the modshop
	if(interiorid == 1)
	{   //TransFender   //14 //16 //18
		//PlayerInfo[playerid][pCash] -= SBizInfo[16][sbEntranceCost];
		GivePlayerMoneyH(fsbiz+14, playerid, -SBizInfo[14][sbEntranceCost]);
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(14, SBizInfo[14][sbEntranceCost]);
			SBizInfo[14][sbProducts] --;
		}
	}
	else if(interiorid == 2)
	{   //LocoLowCo
		//PlayerInfo[playerid][pCash] -= SBizInfo[15][sbEntranceCost];
		GivePlayerMoneyH(fsbiz+15, playerid, -SBizInfo[15][sbEntranceCost]);
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(15, SBizInfo[15][sbEntranceCost]);
			SBizInfo[15][sbProducts] --;
		}
	}
	else if(interiorid == 3)
	{   //Wheel_Arch_Angel
		//PlayerInfo[playerid][pCash] -= SBizInfo[17][sbEntranceCost];
		GivePlayerMoneyH(fsbiz+16, playerid, -SBizInfo[16][sbEntranceCost]);
		if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(16, SBizInfo[16][sbEntranceCost]);
			SBizInfo[16][sbProducts] --;
		}
	}
	return 1;
}





stock biz_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	/*if(CHECKING[PlayerSelectedMenuRow])
	{
		format(strings, sizeof(strings), "biz_OnPlayerSelectedMenuRow(playerid:%d row:%d menuid:%d",  playerid, row, Current);
		SendClientMessage(playerid, COLOR_PURPLE, strings);
	}*/

	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	new Float:health = LastHealth[playerid];//для баров и закусочных
	//GetPlayerHealth(playerid, health);
	if(Current == mAmmuNation)//для магазинов оружия
	{
		new payout;
		new bizid = GetBizLocation(playerid)-1;
		new paycheck = -1;
		switch(row)
		{
			case 0://9mm $200
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
		        payout = 200;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else*/
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 2, Gun, Ammo);
					if(Ammo > 970)//Gun == 22 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 22, 30);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 1://Silenced 9mm $600
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
        		payout = 600;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 2, Gun, Ammo);
					if(Ammo > 970)//Gun == 23 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 23, 30);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 2://Desert Eagle
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
        		payout = 1200;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 2, Gun, Ammo);
					if(Ammo > 985)//Gun == 24 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 24, 15);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 3://Shotgun
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
        		payout = 600;
 				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 3, Gun, Ammo);
					if(Ammo > 985)//Gun == 25 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 25, 15);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 4://Combat Shotgun
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
        		payout = 1000;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 3, Gun, Ammo);
					if(Ammo > 990)//Gun == 27 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 27, 10);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 5://Rifle
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 1000;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 6, Gun, Ammo);
					if(Ammo > 980)//Gun == 33 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 33, 20);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 6://SMG
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 2000;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 4, Gun, Ammo);
					if(Ammo > 910)//Gun == 29 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 29, 90);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 7://AK47
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 3500;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 880)//Gun == 30 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 30, 120);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 8://M4
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 4500;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 850)//Gun == 31 &&
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 31, 150);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 9://Bomb
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 3000;
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 8, Gun, Ammo);
					if(Gun == 39 && Ammo > 0)//
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше взрывпакетов !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 39, 1);
						paycheck = row;
					}

					GetPlayerWeaponData(playerid, 12, Gun, Ammo);
					if(Gun == 40 && Ammo > 0)//
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше детанаторов !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 40, 1);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mAmmuNation, playerid);
			}
			case 10://Other
			{
				if(!gRealWar) {
					//DisableMenuRow(mOtherAmmuNation, 9); //DisableMenu(mOtherAmmuNation);
					ShowMenuForPlayerEx(mAmmuNation, playerid);
				}
				else
				{
					HideMenuForPlayerEx(mAmmuNation, playerid);
					ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
				}
			}
		}
		if(row != 10)
		{
			if(GetPlayerMoneyH(playerid) > payout && paycheck != -1)
			{
				GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
				/*if(SBizInfo[9][sbProducts] > 0)
				{
					OnGangsExtortionSBiz(9, payout);
					SBizInfo[9][sbProducts] --;
				}*/

				if( PlayerInfo[playerid][pLocal] == 243)
				{ FamilyInfo[LCN][fBank] += payout; }
				else if( PlayerInfo[playerid][pLocal] == 244)
				{ FamilyInfo[Yakuza][fBank] += payout; }
				else { OnGangsExtortionBiz(bizid, payout); }
				//посчитаем сколько продов мог продать биз на эту сумму payout
				//new Float: price = compcost*(100+BizInfo[bizid][bSellProd])/100.0;//10*(100+40)/100=14
				//new iMaterials = floatround(payout/price, floatround_ceil);
				//BizInfo[bizid][bProducts] -= iMaterials;
				paycheck = -1;
			}
		}
	}
	else if(Current == mOtherAmmuNation)//для магазинов оружия
	{
        new bizid = GetBizLocation(playerid)-1;
        new payout;
        new paycheck = -1;
		switch(row)
		{
			case 0://Grenade
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 300;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 998)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 16, 1);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
			case 1://Tear Gas
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 400;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 998)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 17, 1);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
			case 2://Molotov Cocktail
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 500;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 998)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 18, 1);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
			case 3://Fire Extinguisher
			{
       			payout = 1000;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 500)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 42, 500);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
			case 4://FlameThrower
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 7050;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 500)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 37, 500);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
			case 5://RocketLauncher
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 21150;
				/*if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else */
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 998)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 35, 1);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
			case 6://HeatSeeker
			{
				if(PlayerInfo[playerid][pGunLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас отсутствует лицензия на оружие !");
					ShowMenuForPlayerEx(mAmmuNation, playerid);
					return 1;
				}
       			payout = 21150;
				if(BizInfo[bizid][bProducts] <= 0)
				{
		        	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Ammunation", 5000, 1);
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				    return 1;
				}
				if(GetPlayerMoneyH(playerid) > payout)
				{
					new Gun, Ammo;
					GetPlayerWeaponData(playerid, 5, Gun, Ammo);
					if(Ammo > 998)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Вы не можете купить больше оружия !");
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							payout -= payout*PlayerInfo[playerid][pTraderPerk]/100;
						}
						GivePlayerWeaponEx(playerid, 36, 1);
						paycheck = row;
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mOtherAmmuNation, playerid);
			}
		}
		if(GetPlayerMoneyH(playerid) > payout && paycheck != -1)
		{
			GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
			if(PlayerInfo[playerid][pLocal] != 243 && PlayerInfo[playerid][pLocal] != 244) OnGangsExtortionBiz(bizid, payout);
			else if(IsAFamilyMember(playerid)) FamilyInfo[PlayerInfo[playerid][pMember]][fBank] += payout;
			//посчитаем сколько продов мог продать биз на эту сумму payout
			//new Float: price = compcost*(100+BizInfo[bizid][bSellProd])/100.0;//10*(100+40)/100=14
			//new iMaterials = floatround(payout/price, floatround_ceil);
			//BizInfo[bizid][bProducts] -= iMaterials;
			paycheck = -1;
		}
	}
//==============================================================================
	else if(Current == mBar)//для баров
	{
		new drink[20];
        new bizid = GetBizLocation(playerid)-1;
        //new payout;
		switch(row)
		{
			case 0://beer
			{
				//payout = 6;
				if(PlayerDrunk[playerid] < 50)
				{   //если ты ещё не достаточно пьян
					SetPlayerDrunkInBar(playerid, 6, 15.0, "beer");
					//PlayerInfo[playerid][pParam2] -= 30;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
				}
				ShowMenuForPlayerEx(mBar, playerid);
			}
			case 1://vodka
			{
				//payout = 8;
			    if(GetAgePlayer(PlayerInfo[playerid][pAge])+18+PlayerInfo[playerid][pConnectTime]/12 < 18)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "Бармен: Извините, Вам должно быть 18 лет, чтобы употреблять спиртные напитки.");
				}
				else if(PlayerDrunk[playerid] < 50)
				{   //если ты ещё не достаточно пьян
					SetPlayerDrunkInBar(playerid, 8, 25.0, "vodka");
					//PlayerInfo[playerid][pParam2] -= 50;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
				}
				ShowMenuForPlayerEx(mBar, playerid);
			}
			case 2://whiskey
			{
				//payout = 10;
			    if(GetAgePlayer(PlayerInfo[playerid][pAge])+18+PlayerInfo[playerid][pConnectTime]/12 < 18)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "Бармен: Извините, Вам должно быть 18 лет, чтобы употреблять спиртные напитки.");
				}
				else if(PlayerDrunk[playerid] < 50)
				{   //если ты ещё не достаточно пьян
					SetPlayerDrunkInBar(playerid, 10, 27.0, "whiskey");
					//PlayerInfo[playerid][pParam2] -= 50;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
				}
				ShowMenuForPlayerEx(mBar, playerid);
			}
			case 3://water
			{
				if(GetPlayerMoneyH(playerid) < 2)
				{
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else if(PlayerInfo[playerid][pLocal] != 243 && PlayerInfo[playerid][pLocal] != 244)
				{   //если это не Особняк LCN или Особняк Yakudza
					if(BizInfo[bizid][bProducts] <= 0)
					{   //BizInfo[243-100=143][bProducts], а у нас только 78,
				        GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Bar", 5000, 1);
					    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				    }
				    else
					{
						PlayerInfo[playerid][pCash] -= 2;
						PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
						ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
						gConsumingMoney[playerid] = 2;
						GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
						LastMoney[playerid] = PlayerInfo[playerid][pCash];

			   			if(health > 100.0-5.0) { PlayerInfo[playerid][pParam1] -= 5; } //SetPlayerHealthEx(playerid, 100.0);
			   			else SetPlayerHealthEx(playerid, health+5.0);
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
						OnGangsExtortionBiz(bizid, 2);
						//BizInfo[bizid][bProducts] --;
						drink = "water";
						ApplyAnimation(playerid, "BAR", "dnk_stndM_loop",4.1,0,1,1,0,0);
						format(strings, sizeof(strings), "* %s drinks a %s.", PlayerName(playerid), drink);//не переводить
						ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
					}
				}
				else
				{
					PlayerInfo[playerid][pCash] -= 2;
					PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
					ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
					gConsumingMoney[playerid] = 2;
					GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
					LastMoney[playerid] = PlayerInfo[playerid][pCash];


		   			if(health > 100.0-5.0) { PlayerInfo[playerid][pParam1] -= 5; } //SetPlayerHealthEx(playerid, 100.0);
		   			else SetPlayerHealthEx(playerid, health+5.0);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
					drink = "water";
					ApplyAnimation(playerid, "BAR", "dnk_stndM_loop",4.1,0,1,1,0,0);
					format(strings, sizeof(strings), "* %s drinks a %s.", PlayerName(playerid), drink);//не переводить
					ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				}
				ShowMenuForPlayerEx(mBar, playerid);
			}
			case 4://beer
			{
				new payout = 12;
			    if(GetAgePlayer(PlayerInfo[playerid][pAge])+18+PlayerInfo[playerid][pConnectTime]/12 < 18)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "Бармен: Извините, Вам должно быть 18 лет, чтобы употреблять спиртные напитки.");
				}
				else if(GetPlayerMoneyH(playerid) > payout)
				{
				    if(Groceries[playerid][gBeer] >= 9)
				    {
				        SendClientMessage(playerid, COLOR_WHITE, "   У вас есть 9 бутылок пива !");
				    }
					else if(BizInfo[bizid][bProducts] <= 0)
					{
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							new skill = payout / 100;
							new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
							payout = payout - price;
							GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
							OnGangsExtortionBiz(bizid, payout);
						}
						else
						{
						    GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
							OnGangsExtortionBiz(bizid, payout);
						}
						//BizInfo[bizid][bProducts] --;
						Groceries[playerid][gBeer] ++;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "Бутылка Пива приобретена.");
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mBar, playerid);
			}
			/*case 5://vodka
			{
				ShowMenuForPlayerEx(mBar, playerid);
			}
			case 6://soda
			{
				if(GetPlayerMoneyH(playerid) < 2)
				{
				    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				}
				else if(location != 243 && location != 244)
				{   //если это не Особняк LCN или Особняк Yakudza
					if(BizInfo[bizid][bProducts] <= 0)
					{   //BizInfo[243-100=143][bProducts], а у нас только 78,
				        GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Bar", 5000, 1);
					    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				    }
				    else
					{
						PlayerInfo[playerid][pCash] -= 2;
						PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
						ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
						gConsumingMoney[playerid] = 2;
						GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
						LastMoney[playerid] = PlayerInfo[playerid][pCash];


			   			if(health > 100.0-5.0) { PlayerInfo[playerid][pParam1] -= 5; }//SetPlayerHealthEx(playerid, 100.0);
			   			else SetPlayerHealthEx(playerid, health+5.0);
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
						OnGangsExtortionBiz(bizid, 2);
						//BizInfo[bizid][bProducts] --;
						drink = "soda";
						ApplyAnimation(playerid, "BAR", "dnk_stndM_loop",4.1,0,1,1,0,0);
						format(strings, sizeof(strings), "* %s drinks a %s.", PlayerName(playerid), drink);//не переводить
						ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
					}
				}
				else //если это Особняк LCN или Особняк Yakudza
				{
					PlayerInfo[playerid][pCash] -= 2;
					PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
					ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
					gConsumingMoney[playerid] = 2;
					GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
					LastMoney[playerid] = PlayerInfo[playerid][pCash];

		   			if(health > 100.0-5.0) { }//SetPlayerHealthEx(playerid, 100.0);
		   			else SetPlayerHealthEx(playerid, health+5.0);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
					drink = "soda";
					ApplyAnimation(playerid, "BAR", "dnk_stndM_loop",4.1,0,1,1,0,0);
					format(strings, sizeof(strings), "* %s drinks a %s.", PlayerName(playerid), drink);//не переводить
					ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				}
				ShowMenuForPlayerEx(mBar, playerid);
			}*/
   /*AddMenuItem(mBar, 0, "Buy Beer        $12");
    AddMenuItem(mBar, 0, "Buy Vodka       $16");
    AddMenuItem(mBar, 0, "Buy Soda        $4");*/

	    }
		//if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
		//if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
		//SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);//Голод

		if(PlayerInfo[playerid][pParam2] < operator2) gParameter2[playerid] = 0;
		if(PlayerInfo[playerid][pParam2] <= 0) PlayerInfo[playerid][pParam2] = 0;
		SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);//Досуг
	}
	//==========================================================================
//для баров
	else if(Current == mRestaurant)
	{
		new bizid = GetBizLocation(playerid)-1;
		switch(row)
		{
			case 0://Spark Grill
			{
	   			if(health > 250.0-50.0)	{ SetPlayerHealthEx(playerid, 250.0); PlayerInfo[playerid][pParam1] = 0; }
	   			else { SetPlayerHealthEx(playerid, health+50.0); PlayerInfo[playerid][pParam1] -= 50; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -125);
				OnGangsExtortionBiz(bizid, 125);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$125", 1000, 1);
				TogglePlayerControllableEx(playerid, 1);//размораживает
				ApplyAnimation(playerid, "FOOD", "EAT_Burger",4.1,0,1,1,0,0);
				ShowMenuForPlayerEx(mRestaurant, playerid);
			}
			case 1://The Palm
			{
	   			if(health > 240.0-40.0)	{ SetPlayerHealthEx(playerid, 240.0); PlayerInfo[playerid][pParam1] = 0; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -100);
				OnGangsExtortionBiz(bizid, 100);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$100", 1000, 1);
				TogglePlayerControllableEx(playerid, 1);//размораживает
				ApplyAnimation(playerid, "FOOD", "EAT_Pizza",4.1,0,1,1,0,0);
				ShowMenuForPlayerEx(mRestaurant, playerid);
			}
			case 2://Campanile
			{
	   			if(health > 230.0-30.0)	{ SetPlayerHealthEx(playerid, 230.0); PlayerInfo[playerid][pParam1] = 0; }
	   			else { SetPlayerHealthEx(playerid, health+30.0); PlayerInfo[playerid][pParam1] -= 30; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -75);
				OnGangsExtortionBiz(bizid, 75);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$75", 1000, 1);
				TogglePlayerControllableEx(playerid, 1);//размораживает
				ApplyAnimation(playerid, "FOOD", "EAT_Chicken",4.1,0,1,1,0,0);
				ShowMenuForPlayerEx(mRestaurant, playerid);
			}
			case 3://Madeo
			{
	   			if(health > 220.0-20.0)	{ SetPlayerHealthEx(playerid, 220.0); PlayerInfo[playerid][pParam1] = 0; }
	   			else { SetPlayerHealthEx(playerid, health+20.0); PlayerInfo[playerid][pParam1] -= 20; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -50);
				OnGangsExtortionBiz(bizid, 50);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$50", 1000, 1);
				TogglePlayerControllableEx(playerid, 1);//размораживает
				ApplyAnimation(playerid, "FOOD", "EAT_Burger",4.1,0,1,1,0,0);
				ShowMenuForPlayerEx(mRestaurant, playerid);
			}
			case 4://Matsuhisa
			{
	   			if(health > 210.0-10.0)	{ SetPlayerHealthEx(playerid, 210.0); PlayerInfo[playerid][pParam1] = 0; }
	   			else { SetPlayerHealthEx(playerid, health+10.0); PlayerInfo[playerid][pParam1] -= 10; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -25);
				OnGangsExtortionBiz(bizid, 25);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$25", 1000, 1);
				TogglePlayerControllableEx(playerid, 1);//размораживает
				ApplyAnimation(playerid, "FOOD", "EAT_Pizza",4.1,0,1,1,0,0);
				ShowMenuForPlayerEx(mRestaurant, playerid);
			}
			//ShowMenuForPlayerEx(mRestaurant, playerid);
	    }
		if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
		if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
		SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);//Голод
	}
//для закусочных
	else if(Current == mBurgerShot)
	{
		new bizid = GetBizLocation(playerid)-1;
		switch(row)
		{
			case 0://Moo Kids Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 20; }
	   			else { SetPlayerHealthEx(playerid, health+20.0); PlayerInfo[playerid][pParam1] -= 20; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -2);
				OnGangsExtortionBiz(bizid, 2);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$2", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);//2880//2355
				ApplyAnimation(playerid, "FOOD", "EAT_Burger",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mBurgerShot, playerid);
			}
			case 1://Beef Tower
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 40; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -5);
				OnGangsExtortionBiz(bizid, 5);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$5", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Burger",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mBurgerShot, playerid);
			}
			case 2://Meat Stack
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 70; }
	   			else { SetPlayerHealthEx(playerid, health+70.0); PlayerInfo[playerid][pParam1] -= 70; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -10);
				OnGangsExtortionBiz(bizid, 10);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$10", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Burger",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mBurgerShot, playerid);
			}
			case 3://Salad Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 40; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -10);
				OnGangsExtortionBiz(bizid, 10);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$10", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2355, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Burger",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mBurgerShot, playerid);
			}
			case 4://Buy Hamburger
			{
				if(GetPlayerMoneyH(playerid) > 1000)
				{
				    if(Groceries[playerid][gHamburgers] >= 9)
				    {
				        SendClientMessage(playerid, COLOR_WHITE, "   У вас есть 9 гамбургеров. Разогрейте их на кухне для употребления !");
				    }
					else if(BizInfo[bizid][bProducts] <= 0)
					{
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							new skill = 1000 / 100;
							new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
							new payout = 1000 - price;
							GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
							OnGangsExtortionBiz(bizid, payout);
						}
						else
						{
						    GivePlayerMoneyH(fbiz+bizid, playerid, -1000);
							OnGangsExtortionBiz(bizid, 1000);
						}
						//BizInfo[bizid][bProducts] --;
						new rand = random(15);
						Groceries[playerid][gHamburger] += (1+rand);
						Groceries[playerid][gHamburgers] ++;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "3амороженный Гамбургер приобретен.");
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mBurgerShot, playerid);
			}
		}
		if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
		if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
		SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);//Голод
	}
	else if(Current == mCluckinBell)
	{
		new bizid = GetBizLocation(playerid)-1;
		switch(row)
		{
			case 0://Cluckin' little Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 20; }
	   			else { SetPlayerHealthEx(playerid, health+20.0); PlayerInfo[playerid][pParam1] -= 20; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -2);
				OnGangsExtortionBiz(bizid, 2);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$2", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Chicken",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mCluckinBell, playerid);
			}
			case 1://Cluckin' Big Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 40; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -5);
				OnGangsExtortionBiz(bizid, 5);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$5", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Chicken",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mCluckinBell, playerid);
			}
			case 2://Cluckin' Huge Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 70; }
	   			else { SetPlayerHealthEx(playerid, health+70.0); PlayerInfo[playerid][pParam1] -= 70; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -10);
				OnGangsExtortionBiz(bizid, 10);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$10", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2880, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Chicken",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mCluckinBell, playerid);
			}
			case 3://Salad Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 40; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -10);
				OnGangsExtortionBiz(bizid, 10);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$10", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2354, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Chicken",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mCluckinBell, playerid);
			}
			case 4:
			{
				if(GetPlayerMoneyH(playerid) > 1000)
				{
				    if(Groceries[playerid][gChickens] >= 9)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть 9 цыплят. Разогрейте их на кухне для употребления !");
				    }
					else if(BizInfo[bizid][bProducts] <= 0)
					{
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							new skill = 1000 / 100;
							new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
							new payout = 1000 - price;
							GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
							OnGangsExtortionBiz(bizid, payout);
						}
						else
						{
						    GivePlayerMoneyH(fbiz+bizid, playerid, -1000);
							OnGangsExtortionBiz(bizid, 1000);
						}
						//BizInfo[bizid][bProducts] --;
						new rand = random(15);
						Groceries[playerid][gChicken] += (1+rand);
						Groceries[playerid][gChickens] ++;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "3амороженный Цыпленок приобретен.");
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mCluckinBell, playerid);
			}
		}
		if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
		if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
		SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);//Голод
	}
	else if(Current == mStackedPizza)
	{
		new bizid = GetBizLocation(playerid)-1;
		switch(row)
		{
			case 0://Buster
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 20; }
	   			else { SetPlayerHealthEx(playerid, health+20.0); PlayerInfo[playerid][pParam1] -= 20; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -2);
				OnGangsExtortionBiz(bizid, 2);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$2", 1000, 1);

				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2881, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Pizza",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mStackedPizza, playerid);
			}
			case 1://Doble D-Luxe
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 40; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
				GivePlayerMoneyH(fbiz+bizid, playerid, -5);
				OnGangsExtortionBiz(bizid, 5);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$5", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2881, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Pizza",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mStackedPizza, playerid);
			}
			case 2://Full Rack
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 70; }
	   			else { SetPlayerHealthEx(playerid, health+70.0); PlayerInfo[playerid][pParam1] -= 70; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -10);
				OnGangsExtortionBiz(bizid, 10);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$10", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2881, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Pizza",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mStackedPizza, playerid);
			}
			case 3://Salad Meal
			{
	   			if(health >= 100.0)	{ PlayerInfo[playerid][pParam1] -= 40; }
	   			else { SetPlayerHealthEx(playerid, health+40.0); PlayerInfo[playerid][pParam1] -= 40; }
			    GivePlayerMoneyH(fbiz+bizid, playerid, -10);
				OnGangsExtortionBiz(bizid, 10);
				//BizInfo[bizid][bProducts] --;//99-99=0
				GameTextForPlayerEx(playerid, "~r~-$10", 1000, 1);
				SetPlayerAttachedObjectEx(playerid, EAT_SLOT, 2353, Right_hand);
				ApplyAnimation(playerid, "FOOD", "EAT_Pizza",3.0,0,1,1,0,0);
				ShowMenuForPlayerEx(mStackedPizza, playerid);
			}
			case 4:
			{
				if(GetPlayerMoneyH(playerid) > 1000)
				{
				    if(Groceries[playerid][gPizzas] >= 9)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   У вас есть 9 пицц. Разогрейте их на кухне для употребления !");
				    }
					else if(BizInfo[bizid][bProducts] <= 0)
					{
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					}
				    else
				    {
					    if(PlayerInfo[playerid][pTraderPerk] > 0)
				    	{
							new skill = 1000 / 100;
							new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
							new payout = 1000 - price;
							GivePlayerMoneyH(fbiz+bizid, playerid, -payout);
							OnGangsExtortionBiz(bizid, payout);
						}
						else
						{
						    GivePlayerMoneyH(fbiz+bizid, playerid, -1000);
							OnGangsExtortionBiz(bizid, 1000);
						}
						//BizInfo[bizid][bProducts] --;
						new rand = random(15);
						Groceries[playerid][gPizza] += (1+rand);
						Groceries[playerid][gPizzas] ++;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "3амороженная пицца приобретена.");
					}
				}
				else SendClientMessage(playerid, COLOR_GREY, "   У вас не хватает денег !");
				ShowMenuForPlayerEx(mStackedPizza, playerid);
			}
		}
		if(PlayerInfo[playerid][pParam1] < operator1) gParameter1[playerid] = 0;
		if(PlayerInfo[playerid][pParam1] <= 0) PlayerInfo[playerid][pParam1] = 0;
		SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);//Голод
	}
	return 1;
}

stock biz_OnPlayerExitedMenu(playerid, Menu:Current)
{
	if(Current == mAmmuNation)//для амуниций
	{
		HideMenuForPlayerEx(mAmmuNation, playerid);
		TogglePlayerControllableEx(playerid, 1);//освободить
	}
	else if(Current == mOtherAmmuNation)//для амуниций
	{
		HideMenuForPlayerEx(mOtherAmmuNation, playerid);
		TogglePlayerControllableEx(playerid, 1);//освободить
	}
	//==========================================================================
	else if(Current == mBar)//для баров
	{
		HideMenuForPlayerEx(mBar, playerid);
		TogglePlayerControllableEx(playerid, 1);//освободить
	}
	//==========================================================================
	else if(Current == mRestaurant)
	{
		HideMenuForPlayerEx(mRestaurant,playerid);
		TogglePlayerControllableEx(playerid, 1);//освободить
	}
	//==========================================================================
	else if(Current == mBurgerShot)//для закусочных
	{
		HideMenuForPlayerEx(Current,playerid);
		TogglePlayerControllableEx(playerid, 1);
		RemovePlayerAttachedObject(playerid, EAT_SLOT);
	}
	else if(Current == mCluckinBell)
	{
		HideMenuForPlayerEx(Current,playerid);
		TogglePlayerControllableEx(playerid, 1);
		RemovePlayerAttachedObject(playerid, EAT_SLOT);
	}
	else if(Current == mStackedPizza)
	{
		HideMenuForPlayerEx(Current,playerid);
		TogglePlayerControllableEx(playerid, 1);
		RemovePlayerAttachedObject(playerid, EAT_SLOT);
	}
	//==========================================================================
	//для магазинов одежды начало
	else if(Current == mPaid)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mClothMenu,playerid);
		if(GetPVarInt(playerid, "IsPaid") == 0)
		{
			SetPlayerSkinEx(playerid, GetPVarInt(playerid, "OldSkin"));
		}
	    //ClearAnimations(playerid, 1);
	}
	else if(Current == mMale || Current == mFemale || Current == mGangs || Current == mOrganization)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mClothMenu, playerid);
	    //ClearAnimations(playerid, 1);
	}
	else if(Current == mClothMenu)
	{
		HideMenuForPlayerEx(Current,playerid);
		SetCameraBehindPlayer(playerid);//Восстановить камеру на место позади игрока
	    //ClearAnimations(playerid, 1);
		TogglePlayerControllableEx(playerid, 1);//иначе выйти из меню и освободить чела
	}//для магазинов одежды конец
	else if(Current == mPunish)
	{//ShowMenuForPlayerEx(mPunish, playerid);
		HideMenuForPlayerEx(Current, playerid);
		DestroyMenuEx(Current);
	}
}

