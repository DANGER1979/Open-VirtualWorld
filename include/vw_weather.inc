//https://dev.prineside.com/ru/gtasa_weather_id/

//СИСТЕМА СМЕНЫ ПОГОДЫ
//СИСТЕМА БОЛЕЗНЕЙ


new LevelToEpidemics = 0;
//------------------------------------------------------------------------------
//для погоды //по степени ухудшения
//new weathers[] = {17,18,3,10,5,6,11,1,14,0,13,2,4,9,12,15,7,8,21,22,18,20,19};
new weathers[] = {17,18,3,10,5,6,11,1,14,0,13,2,9,12,15,7,8,18,19};//8,16   ,30,38-красная, 4 - текстуры пропадают
new wethindex = 0;//счётчик минут и индекс погоды


new STD[10][66] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 10},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7}
};//Вероятность заболеть 43%
/*Список болезней:
3)Бессонница 1хп
1)Ангина 4хп
2)Артрит 6хп
4)Бронхит 7хп
5)Ветряная оспа 4хп
6)Гастрит 3хп
7)Геморрой 4хп
8)Гонорея
9)Грипп
13)Корь
14)Лихорадка
15)Малярия
16)Мигрень
18)Отёк лёгких
19)Отравление
20)Пороки сердца
21)Проказа
22)Простуда
23)Психоз
24)Рак
25)Сахарный диабет
26)Сибирская язва
27)Сифилис
28)Туберкулёз
29)Цирроз печени
30)Чесотка
31)Чума
*/

//для погоды
stock GisMeteoMessage(weatherid)
{
	new wtext[128];
	if(weatherid == 0) { strmid(wtext, "синее небо, видимость - большая", 0, strlen("синее небо, видимость - большая"), 128); }
	else if(weatherid == 1) { strmid(wtext, "синее небо, видимость - средняя", 0, strlen("синее небо, видимость - средняя"), 128); }
	else if(weatherid == 2) { strmid(wtext, "голубое небо, видимость - большая", 0, strlen("голубое небо, видимость - большая"), 128); }
	else if(weatherid == 3) { strmid(wtext, "голубое небо, видимость - средняя", 0, strlen("голубое небо, видимость - средняя"), 128); }
	else if(weatherid == 4) { strmid(wtext, "голубое облачное небо, видимость - средняя", 0, strlen("голубое облачное небо, видимость - средняя"), 128); }
	else if(weatherid == 5) { strmid(wtext, "пасмурное синее небо, видимость - низкая", 0, strlen("пасмурное синее небо, видимость - низкая"), 128); }
	else if(weatherid == 6) { strmid(wtext, "синее небо, видимость - низкая", 0, strlen("синее небо, видимость - низкая"), 128); }
	else if(weatherid == 7) { strmid(wtext, "светло-серое пасмурное небо, видимость - большая", 0, strlen("светло-серое пасмурное небо, видимость - большая"), 128); }
	else if(weatherid == 8) { strmid(wtext, "дождь с грозой, видимость - средняя", 0, strlen("дождь с грозой, видимость - средняя"), 128); }
	else if(weatherid == 9) { strmid(wtext, "туман, видимость - низкая", 0, strlen("туман, видимость - низкая"), 128); }
	else if(weatherid == 10) { strmid(wtext, "ясное синее небо, видимость - большая", 0, strlen("ясное синее небо, видимость - большая"), 128); }
	else if(weatherid == 11) { strmid(wtext, "чистое голубое небо, видимость - средняя", 0, strlen("чистое голубое небо, видимость - средняя"), 128); }
	else if(weatherid == 12) { strmid(wtext, "светло-серое пасмурное небо, видимость - большая", 0, strlen("светло-серое пасмурное небо, видимость - большая"), 128); }
	else if(weatherid == 13) { strmid(wtext, "синее небо, видимость - большая", 0, strlen("синее небо, видимость - большая"), 128); }
	else if(weatherid == 14) { strmid(wtext, "градиентное синее небо, видимость - большая", 0, strlen("градиентное синее небо, видимость - большая"), 128); }
	else if(weatherid == 15) { strmid(wtext, "светло-серое пасмурное небо, видимость - большая", 0, strlen("светло-серое пасмурное небо, видимость - большая"), 128); }
	else if(weatherid == 16) { strmid(wtext, "дождь с грозой, видимость - средняя", 0, strlen("дождь с грозой, видимость - средняя"), 128); }
	else if(weatherid == 17) { strmid(wtext, "розовое небо, видимость - большая", 0, strlen("низко розовое небо, видимость - большая"), 128); }
	else if(weatherid == 18) { strmid(wtext, "низко розовое небо, видимость - большая", 0, strlen("низко розовое небо, видимость - большая"), 128); }
	else if(weatherid == 19) { strmid(wtext, "песчаная буря, видимость - низкая", 0, strlen("песчаная буря, видимость - низкая"), 128); }
	else if(weatherid == 20) { strmid(wtext, "тёмно-серое пасмурное небо, видимость - ниже среднего", 0, strlen("тёмно-серое пасмурное небо, видимость - ниже среднего"), 128); }
	else if(weatherid == 21) { strmid(wtext, "градиентное фиолетовое небо, видимость - средняя", 0, strlen("градиентное фиолетовое небо, видимость - средняя"), 128); }
	else if(weatherid == 22) { strmid(wtext, "градиентное серое небо, видимость - средняя", 0, strlen("градиентное серое небо, видимость - средняя"), 128); }
	else if(weatherid == 42) { strmid(wtext, "надвижение песчаной бури, видимость - низкая", 0, strlen("надвижение песчаной бури, видимость - низкая"), 128); }
	return wtext;
}

stock weather_OneMinutsTimer()
{
//для погоды начало
	new setpog = 0;
	if(ChangeWeath == 0)
	{	//если дошли до конца, смена погоды
	    wethindex ++;//номер ячейки погоды
	    if(wethindex >= sizeof(weathers)) wethindex = 0;
	    SetWeather(weathers[wethindex]);//из массива weathers установить погоду следующую по списку
	    ChangeWeath = WEATHCHANGE;//обнулить
	    setpog = 1;//поднять флаг для переключения погоды
		if(weathers[wethindex+1] == 8 || weathers[wethindex+1] == 9 || weathers[wethindex+1] == 16 || weathers[wethindex+1] == 19)
		{
			format(strings, sizeof(strings), "GisMeteoMessage: В ближайшее время в штате San Andreas ожидается %s[%d].", GisMeteoMessage(weathers[wethindex+1]), weathers[wethindex+1]);
			SendFamilyMessage(SAN, strings);
		}
		if(weathers[wethindex] == 8 || weathers[wethindex] == 16)
		{
			SBizInfo[51][sbProducts] += 500;
		}
	}
	else if(ChangeWeath > 0) { ChangeWeath --; }//таймер минут
	
	for(new j=0, i; j<MaxPlayers; j++)
	{
		i = PLIDs[j];
		//if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
		if( !gPlayerLogged[i] ) continue;
		if( !gPlayerSpawned[i] ) continue;
		
		if(setpog == 1 && PlayerInfo[i][pVirtual] == 0)	SetPlayerWeather(i, weathers[wethindex]);
		OnPlayerCheckInRain(i);
	}
	
//для погоды конец
}


//для болезней начало
stock OnPlayerCheckInRain(playerid)
{	//вызывается из минутного таймера
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(weathers[wethindex] != 8 && weathers[wethindex] != 16) return 1;
	if(PlayerInfo[playerid][pLevel] <= 1) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(spectateid[playerid] != MAX_PLAYERS-1) return 1;
	if(PlayerInfo[playerid][pSTD] != 0 || PlayerInfo[playerid][pAccount] != 0) return 1;

	if(IsInAmbulanceCar(playerid) || IsPlayerInAnyVehicle(playerid) ||
		IsAtHospital(playerid) ) return 1;
	if( IsPlayerInArea(playerid, specialzone[2]) ||//военная база только нижний уровень
		IsPlayerInArea(playerid, specialzone[6]) || //особняк Hitman
		IsPlayerInArea(playerid, specialzone[8]) || //CarDealer
		IsPlayerInArea(playerid, specialzone[10])) return 1;

	if(LastHealth[playerid] < 50.0) return 1;
	new rand = random(66);//выбираем из массив болезнь с малой вероятностью заболеть
	PlayerInfo[playerid][pSTD] = STD[PlayerInfo[playerid][pDrugPerk]][rand];//43% // STD4 - 29% вероятность
	if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll)
	{   //если игрок хватанул вирус
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "* %s заболел", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		LevelToEpidemics ++;
	}
	return 1;
}

