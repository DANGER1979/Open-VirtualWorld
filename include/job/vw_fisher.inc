//для рыбаловов
enum pFishing
{
	pFish1[20],//название рыбы в первом слоте
	pFish2[20],
	pFish3[20],
	pFish4[20],
	pFish5[20],
	pWeight[5],//вес пойманной рыбы в первом слоте
	pFid1,//номер рыбы (тип) в массиве FishNames для готовки
	pFid2,
	pFid3,
	pFid4,
	pFid5,
	pLastFish,//указывает номер слота последнее пойманной рыбы
	pFishID,
	pLastWeight//вес последней спойманной рыбы
};
new Fishes[MAX_PLAYERS][pFishing];


#define MAX_FISHES 17
new FishNames[MAX_FISHES][19] = {
{"Mешок Денег"},{"Oбувь"},{"Mусор"},{"Kуртку"},{"Tрусы"},{"Kонсервную банку"},{"Брюки"},{"Наушники"},
{"Mорскую звезду"},{"Жёлтого полосатика"},{"Рыбу-бабочку"},{"Астронотуса"},{"Дискуса"},{"Dельфина"},{"Aкулу"},{"4ерепаху"},{"Tунца"}
};





stock IsAtFishPlace(playerid)//возвращает 1 если игрок в одной из зон для рыбалки
{
    new Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	if(angle >= 175.0 && angle <= 185.0)
	{
	    if(IsPlayerInRangeOfPoint(playerid, 1.8, 403.8266,-2088.7598,7.8359) || IsPlayerInRangeOfPoint(playerid, 1.8, 398.7553,-2088.7490,7.8359))
		{//Fishplace at the bigwheel
		    return 1;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, 396.2197,-2088.6692,7.8359) || IsPlayerInRangeOfPoint(playerid, 1.8, 391.1094,-2088.7976,7.8359))
		{//Fishplace at the bigwheel
		    return 2;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, 383.4157,-2088.7849,7.8359) || IsPlayerInRangeOfPoint(playerid, 1.8, 374.9598,-2088.7979,7.8359))
		{//Fishplace at the bigwheel
		    return 3;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, 369.8107,-2088.7927,7.8359) || IsPlayerInRangeOfPoint(playerid, 1.8, 367.3637,-2088.7925,7.8359))
		{//Fishplace at the bigwheel
		    return 4;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, 362.2244,-2088.7981,7.8359) || IsPlayerInRangeOfPoint(playerid, 1.8, 354.5382,-2088.7979,7.8359))
		{//Fishplace at the bigwheel
		    return 5;
		}
	}
	if(angle >= 85.0 && angle <= 95.0)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,484.2672,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,482.7295,4.9141))
		{//Fishplace at the sf pier
			return 6;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,481.4020,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,479.8679,4.9141))
		{//Fishplace at the sf pier
			return 7;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,478.3723,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,476.8276,4.9141))
		{//Fishplace at the sf pier
			return 8;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,475.5346,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,474.2108,4.9141))
		{//Fishplace at the sf pier
			return 9;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,472.9091,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,471.7226,4.9141))
		{//Fishplace at the sf pier
			return 10;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,470.5499,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,469.3314,4.9141))
		{//Fishplace at the sf pier
			return 11;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,468.2096,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,466.8542,4.9141))
		{//Fishplace at the sf pier
			return 12;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,465.7455,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,464.3201,4.9141))
		{//Fishplace at the sf pier
			return 13;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,463.1885,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,461.9476,4.9141))
		{//Fishplace at the sf pier
			return 14;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,460.8008,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,459.6024,4.9141))
		{//Fishplace at the sf pier
			return 15;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,458.3021,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,456.9173,4.9141))
		{//Fishplace at the sf pier
			return 16;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7793,455.5937,4.9141) || IsPlayerInRangeOfPoint(playerid, 1.8, -2996.7786,482.7582,4.9141))
		{//Fishplace at the sf pier
			return 17;
		}
	}
	return 0;
}


//для рыбаловов
stock OnFishWaiting(playerid)//вызывается из секундного таймера OneSecondTimers
{
	if(IsPlayerInAnyVehicle(playerid))
	{
   		gGameText[playerid] = 0;
		FishCount[playerid] = 0;
		return 1;
	}
	//if(	GasCounter[playerid] == 1 || GasCounter[playerid] == 3 ||
	//	GasCounter[playerid] == 5) PlaySoundForPlayer(playerid, SOUND_BUY_CAR_RESPRAY);//звук спрэя
	gGameText[playerid] = 1;
	SetPlayerGameTextScale(playerid, "Fish Waiting", FishCount[playerid], 8);

	if(!IsEvenNumber(FishCount[playerid]))
	{
		if(FishCount[playerid] > 2) ApplyAnimation(playerid, "SWORD", "sword_block", 4.1,0,0,0,1,0, 1);
	}
	else ApplyAnimation(playerid, "SWORD", "SWORD_IDLE", 4.1,1,0,0,1,5000, 1);
	
	FishCount[playerid] ++;
 	if(FishCount[playerid] > 8)
	{
   		gGameText[playerid] = 0;
		FishCount[playerid] = 0;

		//TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться
		ExtendFishingRod(playerid);
	}
	return 1;
}

stock ExtendFishingRod(playerid)
{//подсекание удочки
	new Caught;
	new level = PlayerInfo[playerid][pFishSkill];
	if(level < 50) { Caught = random(20)-5; }//для экономики
	else if(level >= 50 && level < 250) { Caught = random(40)-10; }
	else if(level >= 250 && level < 500) { Caught = random(60)-15; }
	else if(level >= 500 && level < 1000) { Caught = random(80)-20; }
	else if(level >= 1000) { Caught = random(100)-25; }

	if(Caught <= 0)
	{
		format(strings, sizeof(strings), "* У %s'а Порвалась Леска !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "Sword_Hit_3",4.1,0,1,1,0,0, 1);
		return 1;
	}

	new rand = random(MAX_FISHES);//17//выбираем рандомно тип рыбы
	if(rand == 0)
	{
		new mrand = random(1001);//для экономики
		format(strings, sizeof(strings), "* %s поймал Мешок с деньгами, содержащий $%d !", PlayerName(playerid), mrand);
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "Sword_Hit_2",4.1,0,1,1,0,0, 1);
		GivePlayerMoneyH(fjackpot, playerid, mrand);
		return 1;
	}
	/*else if(rand == 1)
	{
		format(strings, sizeof(strings), "* %s поймал пару Туфель и бросил их обратно !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}*/
	else if(rand == 2)
	{
		format(strings, sizeof(strings), "* %s поймал немного Мусора и выбросил !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}
	/*else if(rand == 3)
	{
		format(strings, sizeof(strings), "* %s поймал Куртку и выбросил её !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}
	else if(rand == 4)
	{
		format(strings, sizeof(strings), "* %s вытащил Трусы и бросил их обратно !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}*/
	else if(rand == 5)
	{
		format(strings, sizeof(strings), "* %s вытащил Консервную банку и выбросил её !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}
	/*else if(rand == 6)
	{
		format(strings, sizeof(strings), "* %s вытащил Брюки и бросил их обратно !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}
	else if(rand == 7)
	{
		format(strings, sizeof(strings), "* %s вытащил Наушники и выбросил их !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		ApplyAnimation(playerid, "SWORD", "sword_part",4.1,0,1,1,0,0, 1);
		return 1;
	}*/

	if(PlayerInfo[playerid][pFishLic] < 1)
	{
		WantedPoints[playerid] += 6;
		SetPlayerCriminal(FBI, playerid, INVALID_PLAYER_ID, " Незаконное Рыболовство");
		SendFamilyMessage(FBI, "   USE: /pun [581] [1] [playerid/PartOfName]");
	}

	new fstring[20];
    format(fstring, sizeof(fstring), "%s", FishNames[rand]);
	if(Fishes[playerid][pWeight][0] == 0)
	{   //если первый карман пуст, т.е. имеет нулевой вес
		Fishes[playerid][pLastFish] = 1;
		strmid(Fishes[playerid][pFish1], fstring, 0, strlen(fstring), 20);
		Fishes[playerid][pWeight][0] = Caught;
		Fishes[playerid][pFid1] = rand;
	}
	else if(Fishes[playerid][pWeight][1] == 0)
	{
		Fishes[playerid][pLastFish] = 2;
		strmid(Fishes[playerid][pFish2], fstring, 0, strlen(fstring), 20);
		Fishes[playerid][pWeight][1] = Caught;
		Fishes[playerid][pFid2] = rand;
	}
	else if(Fishes[playerid][pWeight][2] == 0)
	{
		Fishes[playerid][pLastFish] = 3;
		strmid(Fishes[playerid][pFish3], fstring, 0, strlen(fstring), 20);
		Fishes[playerid][pWeight][2] = Caught;
		Fishes[playerid][pFid3] = rand;
	}
	else if(Fishes[playerid][pWeight][3] == 0)
	{
		Fishes[playerid][pLastFish] = 4;
		strmid(Fishes[playerid][pFish4], fstring, 0, strlen(fstring), 20);
		Fishes[playerid][pWeight][3] = Caught;
		Fishes[playerid][pFid4] = rand;
	}
	else if(Fishes[playerid][pWeight][4] == 0)
	{
		Fishes[playerid][pLastFish] = 5;
		strmid(Fishes[playerid][pFish5], fstring, 0, strlen(fstring), 20);
		Fishes[playerid][pWeight][4] = Caught;
		Fishes[playerid][pFid5] = rand;
	}
	/*else
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Вы не находитесь в месте Рыбалки !");
	    return 1;
	}*/
	PlayerInfo[playerid][pFishes] += Caught;
	/*PlayerInfo[playerid][pFishes] ++;
	if( check_number(PlayerInfo[playerid][pFishes], 5) )
		{   //если кратно 5, то прервать
		if(level < 50) {
			//skill = 1; money = (100 + random(100));
			FishCount[playerid] = 20;//
		}
		else if(level >= 50 && level < 250) {
			//skill = 2; money = (200 + random(100));
			FishCount[playerid] = 18;
		}
		else if(level >= 250 && level < 500) {
			//skill = 3; money = (300 + random(100));
			FishCount[playerid] = 16;
		}
		else if(level >= 500 && level < 1000) {
			//skill = 4; money = (400 + random(100));
			FishCount[playerid] = 14;
		}
		else if(level >= 1000) {
			//skill = 5; money = RANDMONEY5;
			FishCount[playerid] = 12;
		}
	}*/
	
	format(strings, sizeof(strings), "* %s поймал %s, весом %d кг !", PlayerName(playerid), fstring, Caught);
	ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
	Fishes[playerid][pLastWeight] = Caught;
	Fishes[playerid][pFishID] = rand;
	if(Caught > PlayerInfo[playerid][pBiggestFish])
	{
		format(strings, sizeof(strings), "* %s поймал Рыбу весом %d кг и побил свой старый рекорд %d кг !", PlayerName(playerid), Caught, PlayerInfo[playerid][pBiggestFish]);
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		PlayerInfo[playerid][pBiggestFish] = Caught;
	}

	if(level <= 1001) PlayerInfo[playerid][pFishSkill] ++;
	if(PlayerInfo[playerid][pFishSkill] == 50)
	{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Умение Ловить Рыбу поднялось до Уровня 2, Вы можете теперь споймать Рыбу побольше."); }
	else if(PlayerInfo[playerid][pFishSkill] == 250)
	{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Умение Ловить Рыбу поднялось до Уровня 3, Вы можете теперь споймать Рыбу побольше."); }
	else if(PlayerInfo[playerid][pFishSkill] == 500)
	{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Умение Ловить Рыбу поднялось до Уровня 4, Вы можете теперь споймать Рыбу побольше."); }
	else if(PlayerInfo[playerid][pFishSkill] == 1000)
	{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Умение Ловить Рыбу поднялось до Уровня 5, Вы можете теперь споймать Рыбу самую большую рыбу."); }

	ClearAnimations(playerid, 1);
	if(IsPlayerAttachedObjectSlotUsed(playerid, OBJECT_SLOT)) RemovePlayerAttachedObject(playerid, OBJECT_SLOT);
	return 1;
}


stock ClearFishes(playerid)//вызывается из ф-ии OnPlayerConnect
{
	new strtmp[8];
	format(strtmp, sizeof(strtmp), "None");
	strmid(Fishes[playerid][pFish1], strtmp, 0, strlen(strtmp), 20);
	strmid(Fishes[playerid][pFish2], strtmp, 0, strlen(strtmp), 20);
	strmid(Fishes[playerid][pFish3], strtmp, 0, strlen(strtmp), 20);
	strmid(Fishes[playerid][pFish4], strtmp, 0, strlen(strtmp), 20);
	strmid(Fishes[playerid][pFish5], strtmp, 0, strlen(strtmp), 20);

	Fishes[playerid][pWeight][0] = 0;
	Fishes[playerid][pWeight][1] = 0;
	Fishes[playerid][pWeight][2] = 0;
	Fishes[playerid][pWeight][3] = 0;
	Fishes[playerid][pWeight][4] = 0;
	
    Fishes[playerid][pFid1] = 0;
	Fishes[playerid][pFid2] = 0;
	Fishes[playerid][pFid3] = 0;
	Fishes[playerid][pFid4] = 0;
	Fishes[playerid][pFid5] = 0;
	
	Fishes[playerid][pLastFish] = 0;
	Fishes[playerid][pFishID] = 0;
	//PlayerInfo[playerid][pFishes] = 0;
}


stock ClearFishID(playerid, fish)
{
	new strtmp[8];//MAX_PLAYER_NAME
	format(strtmp, sizeof(strtmp), "None");
	switch(fish)
	{
	    case 1:
	    {
	        strmid(Fishes[playerid][pFish1], strtmp, 0, strlen(strtmp), 20);
	        Fishes[playerid][pWeight][0] = 0;
	        Fishes[playerid][pFid1] = 0;
	    }
	    case 2:
	    {
	        strmid(Fishes[playerid][pFish2], strtmp, 0, strlen(strtmp), 20);
	        Fishes[playerid][pWeight][1] = 0;
	        Fishes[playerid][pFid2] = 0;
	    }
	    case 3:
	    {
	        strmid(Fishes[playerid][pFish3], strtmp, 0, strlen(strtmp), 20);
	        Fishes[playerid][pWeight][2] = 0;
	        Fishes[playerid][pFid3] = 0;
	    }
	    case 4:
	    {
	        strmid(Fishes[playerid][pFish4], strtmp, 0, strlen(strtmp), 20);
	        Fishes[playerid][pWeight][3] = 0;
	        Fishes[playerid][pFid4] = 0;
	    }
		case 5:
	    {
	        strmid(Fishes[playerid][pFish5], strtmp, 0, strlen(strtmp), 20);
	        Fishes[playerid][pWeight][4] = 0;
	        Fishes[playerid][pFid5] = 0;
	    }
	}
	Fishes[playerid][pLastFish] = 0;
	Fishes[playerid][pFishID] = 0;
	/*if(	Fishes[playerid][pWeight][0] <= 0 &&
		Fishes[playerid][pWeight][1] <= 0 &&
		Fishes[playerid][pWeight][2] <= 0 &&
		Fishes[playerid][pWeight][3] <= 0 &&
		Fishes[playerid][pWeight][4] <= 0) { ClearFishes(playerid); }
*/
}

//для экономики
stock FishCost(fish)//для рыбаловов //вызывается по команде /sell fish
{   //сопостовление цен на рыбы
	new cost = 0;
	switch(fish)
	{//цена 1 кг
	    case 1: cost = 1;//"Pыбу-Янтарь" - 1
	    case 2: cost = 3;//"Mорского Окуня" - 3
	    case 3: cost = 3;//"Kрасного Люциана" - 3
	    case 5: cost = 5;//"Fорель" - 5
	    case 6: cost = 2;//"Mарлинь голубой" - 2
	    case 8: cost = 8;//"Cкумбрию" - 8
	    case 9: cost = 12;//"3убатку" - 12
	    case 11: cost = 9;//"6ольшую Щуку" - 9
	    case 12: cost = 7;//"Pыбу-Парус" - 7
	    case 14: cost = 12;//"Tунца" - 12
	    case 15: cost = 9;//"Mорского Угря" - 9
	    case 16: cost = 7;//"Dельфина" - 7
	    case 17: cost = 7;//"Aкулу - 7
	    case 18: cost = 10;//"4ерепаху" - 10
	    case 19: cost = 4;//"Cома" - 4
	    case 21: cost = 3;//"Pыбу-Меч" - 3
	}
	return cost;
}

stock fisher_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_DRIVER) //buggy dont finnish  //если ID нового состояния равно состоянию за рулём
	{	//если ID нового состояния равно состоянию 2
	//для рыбаловов
		if(FishCount[playerid] > 0)
		{
	   		gGameText[playerid] = 0;
			FishCount[playerid] = 0;
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{   //если ID нового состояния равно состоянию 3 - пассажир
		//для рыбаловов
		if(FishCount[playerid] > 0)
		{
	   		gGameText[playerid] = 0;
			FishCount[playerid] = 0;
		}
	}
}

stock fisher_OnPlayerPickUp(playerid)
{
	if( IsPlayerInRangeOfPoint(playerid, 2.1, 359.9126,-2032.1475,7.8359))
	{//Feris Wheel
	    new dlgitem[59+5*35+5*20+5*3+50+38];
        strcat(dlgitem, "{ffffff}_________________ Fishes _________________{8D8DFF}");
        format(dlgitem, sizeof(dlgitem), "%s\n** (1) Карман: %s. Вес: %d кг\
\n** (2) Карман: %s. Вес: %d кг\
\n** (3) Карман: %s. Вес: %d кг\
\n** (4) Карман: %s. Вес: %d кг\
\n** (5) Карман: %s. Вес: %d кг", dlgitem,
			Fishes[playerid][pFish1], Fishes[playerid][pWeight][0],
			Fishes[playerid][pFish2], Fishes[playerid][pWeight][1],
			Fishes[playerid][pFish3], Fishes[playerid][pWeight][2],
			Fishes[playerid][pFish4], Fishes[playerid][pWeight][3],
			Fishes[playerid][pFish5], Fishes[playerid][pWeight][4]);
        strcat(dlgitem, "\n{ffffff}_________________________________________");
		strcat(dlgitem, "\n\n{8D8DFF}Введите номер кармана (1-5):");
	    ShowPlayerDialogGap(playerid, FishVault_DIALOG, DIALOG_STYLE_INPUT, "Магазин Охотника и Рыбалова", dlgitem, "Accept", "Cancel");
		//return 1;
	}
}


stock fisher_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != FishVault_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		return 1;
	}
    if(!strlen(inputtext))
    {
	    new dlgitem[59+5*35+5*20+5*3+50+38];
        strcat(dlgitem, "{ffffff}_________________ Fishes _________________{8D8DFF}");
        format(dlgitem, sizeof(dlgitem), "%s\n** (1) Карман: %s. Вес: %d кг\
\n** (2) Карман: %s. Вес: %d кг\
\n** (3) Карман: %s. Вес: %d кг\
\n** (4) Карман: %s. Вес: %d кг\
\n** (5) Карман: %s. Вес: %d кг", dlgitem,
			Fishes[playerid][pFish1], Fishes[playerid][pWeight][0],
			Fishes[playerid][pFish2], Fishes[playerid][pWeight][1],
			Fishes[playerid][pFish3], Fishes[playerid][pWeight][2],
			Fishes[playerid][pFish4], Fishes[playerid][pWeight][3],
			Fishes[playerid][pFish5], Fishes[playerid][pWeight][4]);
        strcat(dlgitem, "\n{ffffff}_________________________________________");
		strcat(dlgitem, "\n\n{8D8DFF}Введите номер кармана (1-5):");
	    ShowPlayerDialogGap(playerid, FishVault_DIALOG, DIALOG_STYLE_INPUT, "Магазин Охотника и Рыбалова", dlgitem, "Accept", "Cancel");
	    return 1;
	}
	new fishid = strval(inputtext);
	if(fishid < 1 || fishid > 5) { SendClientMessage(playerid, COLOR_GREY, "   Номер кармана может быть от 1 до 5 !"); return 1; }

	else if(fishid == 1 && Fishes[playerid][pWeight][0] < 1) { SendClientMessage(playerid, COLOR_GREY, "   Вы не имеете Рыбы в кармане под номером (1) !"); return 1; }
	else if(fishid == 2 && Fishes[playerid][pWeight][1] < 1) { SendClientMessage(playerid, COLOR_GREY, "   Вы не имеете Рыбы в кармане под номером (2) !"); return 1; }
	else if(fishid == 3 && Fishes[playerid][pWeight][2] < 1) { SendClientMessage(playerid, COLOR_GREY, "   Вы не имеете Рыбы в кармане под номером (3) !"); return 1; }
	else if(fishid == 4 && Fishes[playerid][pWeight][3] < 1) { SendClientMessage(playerid, COLOR_GREY, "   Вы не имеете Рыбы в кармане под номером (4) !"); return 1; }
	else if(fishid == 5 && Fishes[playerid][pWeight][4] < 1) { SendClientMessage(playerid, COLOR_GREY, "   Вы не имеете Рыбы в кармане под номером (5) !"); return 1; }

	new Caught;
	new level = PlayerInfo[playerid][pFishSkill];
	if(level < 50) { Caught = 3; }//для экономики
	else if(level >= 50 && level < 250) { Caught = 7; }
	else if(level >= 250 && level < 500) { Caught = 10; }
	else if(level >= 500 && level < 1000) { Caught = 13; }
	else if(level >= 1000) { Caught = 17; }

	if(Fishes[playerid][pWeight][fishid-1] < Caught)
	{
       	format(strings, sizeof(strings), "   Мы интересуемся только Рыбами, весом %d кг или больше.", Caught);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	new price;	new Fish[20];
	switch(fishid)
	{
	    case 1:
	    {
			price = FishCost(Fishes[playerid][pFid1])* Fishes[playerid][pWeight][fishid-1];
			Fish = Fishes[playerid][pFish1];
			strmid(Fish, Fishes[playerid][pFish1], 0, 20, 20);
	    }
	    case 2:
	    {
			price = FishCost(Fishes[playerid][pFid2])*Fishes[playerid][pWeight][fishid-1];
			strmid(Fish, Fishes[playerid][pFish2], 0, 20, 20);
	    }
	    case 3:
	    {
			price = FishCost(Fishes[playerid][pFid3])* Fishes[playerid][pWeight][fishid-1];
			strmid(Fish, Fishes[playerid][pFish3], 0, 20, 20);
	    }
	    case 4:
	    {
			price = FishCost(Fishes[playerid][pFid4])*Fishes[playerid][pWeight][fishid-1];
			strmid(Fish, Fishes[playerid][pFish4], 0, 20, 20);
	    }
	    case 5:
	    {
			price = FishCost(Fishes[playerid][pFid5])*Fishes[playerid][pWeight][fishid-1];
			strmid(Fish, Fishes[playerid][pFish5], 0, 20, 20);
	    }
	}
	//--------------------------------------------------------------
	if(PlayerInfo[playerid][pTraderPerk] > 0)
	{
		new payout = floatround(price*5/100.0);
		price += payout;
	}
	if(SBizInfo[53][sbTill] > price)
	{
		//GameTextForPlayerEx(playerid, "~g~Fish~n~~r~Sold", 3000, 1);
		SBizInfo[53][sbProducts] += Fishes[playerid][pWeight][fishid-1];
		SBizInfo[53][sbTill] -= price;
		SBizInfo[53][sbImport] += price;
		format(strings, sizeof(strings), "* Вы продали %s весом %d кг, за $%d.", Fish, Fishes[playerid][pWeight][fishid-1], price);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		GivePlayerMoneyB(fsbiz+53, playerid, price);
		ClearFishID(playerid, fishid);
	}
	else SendClientMessage(playerid, COLOR_GREY, "   Извените, в кассе нет больше денег.");
	return 1;
}

stock fisher_OneSecondTimers(playerid)
{
	if( AFK_IdleTime[playerid] >= 3) return 1;
	//для рыбаловов
	if(FishCount[playerid] > 0)
    {
    	OnFishWaiting(playerid);
    }
	return 1;
}


