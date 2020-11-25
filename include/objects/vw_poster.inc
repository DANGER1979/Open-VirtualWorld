


//СПИСОК градиентных цветов: R G B
#define COLOR_FONT0		0xFFFFFF00//255 0 0 	//Белый
#define COLOR_FONT1		0xFF000000//255 0 0 	//Красный
#define COLOR_FONT2 	0xFF870000//255 135 0 	//Оранжевый
#define COLOR_FONT3 	0xFFFF0000//255 255 0   //Жёлтый
#define COLOR_FONT4 	0x6EFF0000//110 255 0   //Салатовый
#define COLOR_FONT5 	0x00FF1900//0 255 25    //Зелёный
#define COLOR_FONT6 	0x00FF9B00//0 255 155   //Травяной
#define COLOR_FONT7 	0x00E1FF00//0 225 255   //Бирюзовый
#define COLOR_FONT8 	0x0055FF00//0 85 255    //Синий
#define COLOR_FONT9 	0x3200FF00//50 0 255 	//Тёмно синий
#define COLOR_FONT10 	0xB400FF00//180 0 255   //Фиолетовый
#define COLOR_FONT11 	0xFF00C800//255 0 200   //Розовый
#define COLOR_FONT12 	0xFF003C00//255 0 60    //Коричневый
#define COLOR_FONT13 	0x00000000//255 0 60 	//Чёрный


#define COLOR_RAINBOW0	0xFFFFFFFF//255 0 0 //белый
#define COLOR_RAINBOW1	0xFFFF0000//255 0 0 //красный
#define COLOR_RAINBOW2 	0xFFFF8700//255 135 0
#define COLOR_RAINBOW3 	0xFFFFFF00//255 255 0
#define COLOR_RAINBOW4 	0xFF6EFF00//110 255 0
#define COLOR_RAINBOW5 	0xFF00FF19//0 255 25
#define COLOR_RAINBOW6 	0xFF00FF9B//0 255 155
#define COLOR_RAINBOW7  0xFF00E1FF//0 225 255
#define COLOR_RAINBOW8 	0xFF0055FF//0 85 255
#define COLOR_RAINBOW9 	0xFF3200FF//50 0 255 //тёмно синий
#define COLOR_RAINBOW10 0xFFB400FF//180 0 255
#define COLOR_RAINBOW11 0xFFFF00C8//255 0 200
#define COLOR_RAINBOW12 0xFFFF003C//255 0 60
#define COLOR_RAINBOW13 0xFF000000//255 0 60 //чёрный

#define MAX_POST 18
enum apInfo
{
	ppObjectID,//ИД подложки
	ppModelID,//модель подложки
	ppMaker[24],
	ppText[128],
	ppFont[16],//шрифт
	ppSize,//размер
	ppColor,//номер цвета текста
	ppBack,//номер цвета фона

	Float:ppX,//позиция подложки
	Float:ppY,
	Float:ppZ,
	Float:ppR,

	Float:postpX,//позиция чекпоинта или пикапа
	Float:postpY,
	Float:postpZ,
	ppDate //дата
};
//массив подложек для ввода текста
new PosterInfo[MAX_POST][apInfo] = {
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	1538.39101,-1609.82288, 25.96360,-60.0,	1538.1398,-1609.9478,13.5469,0},//1
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	1414.5201, -1719.6279, 34.0400,167.5, 	1416.4730,-1717.3417,13.5469,0},//2
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	1414.3455, -1724.7991, 33.6440,2.6, 	1409.4049,-1724.1411,13.5469,0},//3
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	778.4357,-1028.6727,43.3438,134.1, 		786.6330,-1025.4648,25.7949,0},//4
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	885.6876, -971.1815, 54.5695,147.7, 	888.3094,-969.1498,36.8958,0},//5
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	703.5797, -1115.6500, 32.9493,5.0, 		697.8063,-1110.9402,18.2241,0},//6
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	193.6062,-1452.7160,30.9723,134.4, 		197.9580,-1463.3606,12.9279,0},//7
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	2233.60840, -1126.76672,42.95730,1.980, 	2233.4109,-1127.7311,25.7969,0},//8
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	2748.81494, -2392.28784, 31.21650,30.0, 2748.2842,-2392.5872,13.6440,0},//9
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	2079.76538, 2445.58228, 28.29800,210.2, 2079.8906,2446.1396,10.8203,0},//10
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-1579.31934, 1184.47217, 28.19920,22.6, -1577.4679,1181.5476,7.1886,0},//11
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-1579.45520, 1188.28406,28.19920,218.0, -1579.7885,1192.3248,7.1953,0},//12
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-1989.77917, 437.38391, 55.9600,23.3, 	-1988.8976,433.1394,35.1719,0},//13
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-1989.37219, 441.32239, 55.9600,217.9, 	-1989.0319,444.7035,35.1719,0},//14
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-1994.04285, -88.95930, 56.9600,22.8, 	-1993.8274,-93.0932,35.9986,0},//15
{0,19479, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-1993.83435, -84.95710, 56.9600,217.9, 	-1993.7859,-82.6846,35.8721,0},//16
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-127.54893, -1159.79321, 20.155,188.5, 	-127.3438,-1159.2668,3.1029,0},//17
{0,19480, "None", "Сдесь могла \nбыть ваша реклама.\n\tDanger_Hidden", "Arial", 60, 14,0,	-83.9513, -370.4231, 18.5692,300.2,		-84.7717, -370.5902, 1.2405,0}//18
};
new LastPosterInfo[MAX_POST][apInfo];

#define MAX_STAND 8
enum stInfo
{
	ObjectID,
	ModelID,
	Float:stX,
	Float:stY,
	Float:stZ,
	Float:stR,
};
//массив стоек бигбордов, 1260-одинарный, 1267-двойной = 5+3*2=11
new BillBoard[MAX_STAND][stInfo] = {
{0,1260,	2233.5000,-1127.0000,36.9000, 62.0},
{0,1260,	-84.2000,-370.2999,13.3000, 0.0},
{0,1260,	2748.8005,-2392.5000,25.5000, 90.0},
{0,1260,	2079.6999,2445.80050,22.5000, 270.0},
{0,1260,	-127.5000,-1159.90020,14.2000, 248.0},
{0,1267,	-1993.6999,-87.0000,51.1000, 90.0},
{0,1267,	-1989.500,439.3999,50.2000, 90.0},
{0,1267,	-1579.000,1186.3005,22.3000, 90.0}
};
//new BillBoard[MAX_STAND];//ид объектов бигбордов

new NP[MAX_PLAYERS],//NumberPosterномер рекламного щита
	//Plate[MAX_POST][10],
	PosterEditStatus[MAX_PLAYERS];//1 - добавление, 2 - редактирование позиции
//==============================================================================
/*stock ClearPoster(Poster)//вызывается по команде /Poster delete
{
    new strtmp[8];//MAX_PLAYER_NAME
	format(strtmp, sizeof(strtmp), "None");
	PosterInfo[Poster][PosterUsed] = 0;
	strmid(PosterInfo[Poster][PosterMaker], strtmp, 0, strlen(strtmp), MAX_PLAYER_NAME);
	strmid(PosterInfo[Poster][PosterTitle], strtmp, 0, strlen(strtmp), 32);
	strmid(PosterInfo[Poster][PosterText1], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText2], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText3], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText4], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText5], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText6], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText7], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText8], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText9], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText10], strtmp, 0, strlen(strtmp), 70);
	strmid(PosterInfo[Poster][PosterText11], strtmp, 0, strlen(strtmp), 70);
	PosterInfo[Poster][PosterDate] = 0;
}*/

stock LoadPosters()//ызывается из poster_OnGameModeInit()
{
	new time = GetTickCount();
	new File: pFile = fopen("Logs/billboard.cfg", io_read);//io_readwrite
	if(pFile)
	{
		new arrCoords[12][128];
		new strFromFile[268];//46 + 4+24+128+16+3+10+10+6*4+3 = 268
		for(new idx=0; idx<MAX_POST; idx++)
		{
			fread(pFile, strFromFile);
			split(strFromFile, arrCoords, '|');
			PosterInfo[idx][ppModelID] = strval(arrCoords[0]);
			strmid(PosterInfo[idx][ppMaker], arrCoords[1], 0, strlen(arrCoords[1]), 24);
			strmid(PosterInfo[idx][ppText], replaceString(arrCoords[2], ",", "\n"), 0, 128, 255);
			strmid(PosterInfo[idx][ppFont], arrCoords[3], 0, strlen(arrCoords[3]), 16);
			PosterInfo[idx][ppSize] = strval(arrCoords[4]);
			PosterInfo[idx][ppColor] = strval(arrCoords[5]);
			PosterInfo[idx][ppBack] = strval(arrCoords[6]);
			PosterInfo[idx][ppX] = floatstr(arrCoords[7]);
			PosterInfo[idx][ppY] = floatstr(arrCoords[8]);
			PosterInfo[idx][ppZ] = floatstr(arrCoords[9]);
			PosterInfo[idx][ppR] = floatstr(arrCoords[10]);
			PosterInfo[idx][ppDate] = strval(arrCoords[11]);
			
			/*printf("%d|%s|%s|%s|%d|%d|%d|%.4f|%.4f|%.4f|%.4f|%d\n",
				PosterInfo[idx][ppModelID],
				PosterInfo[idx][ppMaker],
				PosterInfo[idx][ppText],
				PosterInfo[idx][ppFont],
				PosterInfo[idx][ppSize],
				PosterInfo[idx][ppColor],
				PosterInfo[idx][ppBack],
				PosterInfo[idx][ppX],
				PosterInfo[idx][ppY],
				PosterInfo[idx][ppZ],
				PosterInfo[idx][ppR],
				PosterInfo[idx][ppDate]);*/
		}
		fclose(pFile);
	}
	printf("17/19. [Загрузка рекламных щитов]: Было загружено - %d, потрачено - %d (ms)", MAX_POST, (GetTickCount()-time));
}

stock SavePoster()//Выполняется при введении игроком текста в чат в ф-ии OnPlayerText
{
	new File: pFile = fopen("Logs/billboard.cfg", io_write);
	if(pFile)
	{
		for(new idx=0; idx<MAX_POST; idx++)
		{
			new coordsstring[268];//46 + 4+24+128+16+3+10+10+6*4+3 = 268
			format(coordsstring, sizeof(coordsstring), "%d|%s|%s|%s|%d|%d|%d|%.4f|%.4f|%.4f|%.4f|%d\n",
			PosterInfo[idx][ppModelID],
			PosterInfo[idx][ppMaker],
			replaceString(PosterInfo[idx][ppText], "\n", ","),
			PosterInfo[idx][ppFont],
			PosterInfo[idx][ppSize],
			PosterInfo[idx][ppColor],
			PosterInfo[idx][ppBack],
			PosterInfo[idx][ppX],
			PosterInfo[idx][ppY],
			PosterInfo[idx][ppZ],
			PosterInfo[idx][ppR],
			PosterInfo[idx][ppDate]);
		    for(new c=0; c<strlen(coordsstring); c++)
			{   //записывам от нулевого символа до конца строки
		        fputchar(pFile, coordsstring[c], false);
		    }
		}
		fclose(pFile);
	}
	//SendFamilyMessage(SAN, COLOR_GOLDEN, "Сохранение рекламных щитов успешно завершено");
	SendClientMessageToAll(COLOR_WHITE, "Сохранение рекламных щитов успешно завершено");
}
//==============================================================================

stock poster_OnGameModeInit()
{
//ставим бигборды
	for(new st = 0; st < MAX_STAND; st++)
	{
		BillBoard[st][ObjectID] = CreateObjectEx(BillBoard[st][ModelID], BillBoard[st][stX],BillBoard[st][stY],BillBoard[st][stZ], 0.0,0.0,BillBoard[st][stR]);
	}
	LoadPosters();
//добавляем подложки чтобы было видно где какой постер
    for(new pp = 0; pp < MAX_POST; pp++)
	{
		//PosterInfo[pp][ppColor] = COLOR_RAINBOW7;//0xFF000000;//COLOR_FONT0
		//PosterInfo[pp][ppBack] = 0xFFFFFFFF;//COLOR_RAINBOW7;
		
		new FontColor;
		new fontcolor = PosterInfo[pp][ppColor];
		if(fontcolor == 0) FontColor = COLOR_RAINBOW0;
		else if(fontcolor == 1) FontColor = COLOR_RAINBOW1;
		else if(fontcolor == 2) FontColor = COLOR_RAINBOW2;
		else if(fontcolor == 3) FontColor = COLOR_RAINBOW3;
		else if(fontcolor == 4) FontColor = COLOR_RAINBOW4;
		else if(fontcolor == 5) FontColor = COLOR_RAINBOW5;
		else if(fontcolor == 6) FontColor = COLOR_RAINBOW6;
		else if(fontcolor == 7) FontColor = COLOR_RAINBOW7;
		else if(fontcolor == 8) FontColor = COLOR_RAINBOW8;
		else if(fontcolor == 9) FontColor = COLOR_RAINBOW9;
		else if(fontcolor == 10) FontColor = COLOR_RAINBOW10;
		else if(fontcolor == 11) FontColor = COLOR_RAINBOW11;
		else if(fontcolor == 12) FontColor = COLOR_RAINBOW12;
		else if(fontcolor == 13) FontColor = COLOR_RAINBOW13;
		
		new BackColor;
		new backcolor = PosterInfo[pp][ppBack];
		if(backcolor == 0) BackColor = COLOR_RAINBOW0;
		else if(backcolor == 1) BackColor = COLOR_RAINBOW1;
		else if(backcolor == 2) BackColor = COLOR_RAINBOW2;
		else if(backcolor == 3) BackColor = COLOR_RAINBOW3;
		else if(backcolor == 4) BackColor = COLOR_RAINBOW4;
		else if(backcolor == 5) BackColor = COLOR_RAINBOW5;
		else if(backcolor == 6) BackColor = COLOR_RAINBOW6;
		else if(backcolor == 7) BackColor = COLOR_RAINBOW7;
		else if(backcolor == 8) BackColor = COLOR_RAINBOW8;
		else if(backcolor == 9) BackColor = COLOR_RAINBOW9;
		else if(backcolor == 10) BackColor = COLOR_RAINBOW10;
		else if(backcolor == 11) BackColor = COLOR_RAINBOW11;
		else if(backcolor == 12) BackColor = COLOR_RAINBOW12;
		else if(backcolor == 13) BackColor = COLOR_RAINBOW13;
		
		PosterInfo[pp][ppObjectID] = CreateObjectEx(PosterInfo[pp][ppModelID], PosterInfo[pp][ppX],PosterInfo[pp][ppY],PosterInfo[pp][ppZ], 0.0,0.0,PosterInfo[pp][ppR]-120.0);
    	SetObjectMaterialText(PosterInfo[pp][ppObjectID], PosterInfo[pp][ppText], 0, OBJECT_MATERIAL_SIZE_512x256,
			PosterInfo[pp][ppFont], PosterInfo[pp][ppSize], 1, FontColor, BackColor,
		OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

		/*format(strings, sizeof(strings), "SetObjectMaterialText(fontcolor: %s[%x], backcolor: %s[%x])",
			PosterInfo[pp][ppColor], PosterInfo[pp][ppColor],
			PosterInfo[pp][ppBack], PosterInfo[pp][ppBack]);
		print(strings);*/
	}
	print("   vw_poster.inc v1.5 By: Maksim_Edishions & Danger_Hidden");//Maksim_Edishions
	print("_____________________________________________");
	print(" ");
	return 1;
}

stock poster_OnGameModeExit()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
    	NP[i] = 0;
		MenuOperation[i] = 0;
     	Offer[i] = MAX_PLAYERS-1;
    	PosterEditStatus[i] = 0;
	}
    for(new bb = 0; bb < MAX_STAND; bb++)
	{
		DestroyObjectEx(BillBoard[bb][ObjectID]);
	}
    for(new pp = 0; pp < MAX_POST; pp++)
	{
		DestroyObjectEx(PosterInfo[pp][ppObjectID]);
	}
	return 1;
}


stock poster_OnPlayerConnect(playerid)
{
    NP[playerid] = 0;
	MenuOperation[playerid] = 0;
    Offer[playerid] = MAX_PLAYERS-1;
    PosterEditStatus[playerid] = 0;
	return 1;
}
stock poster_OnPlayerDisconnect(playerid)
{

	return 1;
}

stock poster_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new dlgitem[232+12*10];
	if(dialogid != BIGBOARD_DIALOG2) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);	                                                                                                                                                                                                                                                                                                     															// Quiz System Filterscript Copyright (c) 2010, [Jazz]
//редактирование
	if(!response && MenuOperation[playerid] <= 3) { SavePoster(); return 1; }
	if(!response && MenuOperation[playerid] > 3)
	{
		format(dlgitem, sizeof(dlgitem), "1.\tТекст\n2.\tШрифт\n3.\tРазмер Шрифта\n4.\tЦвет текста\n5.\tЦвет Фона\n6.\tПозицию");
		MenuOperation[playerid] = 3;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Редактировать", dlgitem, "Выбор", "Отмена");
		//SavePoster();
		return 1;
	}
	if(MenuOperation[playerid] == 1)
	{
		if(strval(inputtext) < 1 || strval(inputtext) > MAX_POST)
		{
    		format(dlgitem, sizeof(dlgitem), "Номер рекламного щита не может быть ниже 1 или выше %d.",MAX_POST);
			SendClientMessage(playerid, COLOR_GREY, dlgitem);
   			MenuOperation[playerid] = 1;
			ShowPlayerDialogEx(playerid,BIGBOARD_DIALOG2,DIALOG_STYLE_INPUT,"PosterEdit","Введите номер рекламного щита","Далее","Отмена");
			return 1;
		}
		if(!IsPlayerInRangeOfPoint(playerid, 100, PosterInfo[strval(inputtext)-1][postpX], PosterInfo[strval(inputtext)-1][postpY], PosterInfo[strval(inputtext)-1][postpZ]))
		{
			SendClientMessage(playerid, COLOR_GREY, "Вы дальше 100м от рекламного щита!");
			return 1;
		}
		//SendClientMessage(playerid, COLOR_GREY, "Ожидайте, пока редактор разместит ваше объявление!");
		//GivePlayerMoneyH(ffamily+SAN, playerid, -GetPVarInt(giveplayerid, "MoneyPlayerPoster"));
		//FamilyInfo[SAN][fBank] += GetPVarInt(giveplayerid, "MoneyPlayerPoster");

    	NP[playerid] = strval(inputtext)-1;

    	//NumberString[playerid] = 0;
		//strdel(PosterInfo[NP[playerid]][ppText], 0, 128);
		format(dlgitem, sizeof(dlgitem), "1.\tТекст\n2.\tШрифт\n3.\tРазмер Шрифта\n4.\tЦвет текста\n5.\tЦвет Фона\n6.\tПозицию");
		MenuOperation[playerid] = 3;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Редактировать", dlgitem, "Выбор", "Отмена");
	}
	else if(MenuOperation[playerid] == 3)
	{
		if(listitem == 0)
		{
   			format(PosterInfo[NP[playerid]][ppText], 128, "%s\n%s", PosterInfo[NP[playerid]][ppText], inputtext);
   			MenuOperation[playerid] = 4;
			ShowPlayerDialogEx(playerid,BIGBOARD_DIALOG2,DIALOG_STYLE_INPUT,"Добавление текста","Введите текст, не более 64 символов\
\nДля разделения между строками используйте ','\n\n\tПо окончанию нажмите OK.","OK","Отмена");
		}
		else if(listitem == 1)
		{
			MenuOperation[playerid] = 5;
			ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите шрифт",
"1.\tArial\n2.\tVerdana\n3.\tCalibri\n4.\tCourier New", "Выбор", "Отмена");
		}
		else if(listitem == 2)
		{
			MenuOperation[playerid] = 6;
			ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите размер шрифта",
"1.\tОчень Маленький(5 строк по 20 символов)\n2.\tМаленький(5 строк по 16 символов)\n3.\tСредний(3 строки по 12 символов)\n4.\tБольшой(2 строки по 8 символов)", "Выбрать", "Отмена");
		}
		else if(listitem == 3)
		{
			format(dlgitem, sizeof(dlgitem), "0\t{%06x}Белый\n1\t{%06x}Красный\n2\t{%06x}Оранжевый\n3\t{%06x}Жёлтый\n4\t{%06x}Салатовый\n5\t{%06x}Зелёный\n6\t{%06x}Травяной\n7\t{%06x}Бирюзовый\
\n8\t{%06x}Синий\n9\t{%06x}Тёмно синий\n10\t{%06x}Фиолетовый\n11\t{%06x}Розовый\n12\t{000000}Коричневый\n13\t{000000}Чёрный",
				COLOR_FONT0 >>> 8,COLOR_FONT1 >>> 8,COLOR_FONT2 >>> 8,COLOR_FONT3 >>> 8,COLOR_FONT4 >>> 8,COLOR_FONT5 >>> 8,COLOR_FONT6 >>> 8,
				COLOR_FONT7 >>> 8,COLOR_FONT8 >>> 8,COLOR_FONT9 >>> 8,COLOR_FONT10 >>> 8,COLOR_FONT11 >>> 8,COLOR_FONT12 >>> 8,COLOR_FONT13 >>> 8);
			MenuOperation[playerid] = 7;
			ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите цвет текста", dlgitem, "Выбор", "Отмена");
		}
		else if(listitem == 4)
		{
			format(dlgitem, sizeof(dlgitem), "0\t{%06x}Белый\n1\t{%06x}Красный\n2\t{%06x}Оранжевый\n3\t{%06x}Жёлтый\n4\t{%06x}Салатовый\n5\t{%06x}Зелёный\n6\t{%06x}Травяной\n7\t{%06x}Бирюзовый\
\n8\t{%06x}Синий\n9\t{%06x}Тёмно синий\n10\t{%06x}Фиолетовый\n11\t{%06x}Розовый\n12\t{000000}Коричневый\n13\t{000000}Чёрный",
				COLOR_RAINBOW0 >>> 8,COLOR_RAINBOW1 >>> 8,COLOR_RAINBOW2 >>> 8,COLOR_RAINBOW3 >>> 8,COLOR_RAINBOW4 >>> 8,COLOR_RAINBOW5 >>> 8,COLOR_RAINBOW6 >>> 8,
				COLOR_RAINBOW7 >>> 8,COLOR_RAINBOW8 >>> 8,COLOR_RAINBOW9 >>> 8,COLOR_RAINBOW10 >>> 8,COLOR_RAINBOW11 >>> 8,COLOR_RAINBOW12 >>> 8,COLOR_RAINBOW13 >>> 8);
			MenuOperation[playerid] = 8;
			ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите цвет фона", dlgitem, "Выбор", "Отмена");
		}
		else if(listitem == 5)
		{
	    	PosterEditStatus[playerid] = 2;
	    	MenuOperation[playerid] = 9;
			EditObject(playerid, PosterInfo[NP[playerid]][ppObjectID]);
		}
	}
	//------------------------------------------------------------------
	else if(MenuOperation[playerid] == 4)
	{//Добавление текста
		if(!strlen(inputtext) || strlen(inputtext) > 128)
		{
   			MenuOperation[playerid] = 4;
			ShowPlayerDialogEx(playerid,BIGBOARD_DIALOG2,DIALOG_STYLE_INPUT,"Добавление текста","Введите текст, не более 128 символов\
\nДля разделения между строками используйте ','\
\n\n\tПо окончанию нажмите OK.","OK","Отмена");
       		return 1;
   	 	}
   	 	strmid(PosterInfo[NP[playerid]][ppMaker], PlayerName(playerid), 0, strlen(PlayerName(playerid)), 24);
   	 	strmid(PosterInfo[NP[playerid]][ppText], replaceString(inputtext, ",", "\n"), 0, 128, 255);
		//SendClientMessage(playerid, -1, PosterInfo[NP[playerid]][ppText]);
				
		SetObjectMaterialTextEx(playerid, PosterInfo[NP[playerid]][ppObjectID], PosterInfo[NP[playerid]][ppText], 0, OBJECT_MATERIAL_SIZE_512x256,
			PosterInfo[NP[playerid]][ppFont], PosterInfo[NP[playerid]][ppSize], 1, PosterInfo[NP[playerid]][ppColor], PosterInfo[NP[playerid]][ppBack],
			OBJECT_MATERIAL_TEXT_ALIGN_CENTER);//OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
		format(dlgitem, sizeof(dlgitem), "1.\tТекст\n2.\tШрифт\n3.\tРазмер Шрифта\n4.\tЦвет текста\n5.\tЦвет Фона\n6.\tПозицию");
		MenuOperation[playerid] = 3;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Редактировать", dlgitem, "Выбор", "Отмена");
	}
	else if(MenuOperation[playerid] == 5)
	{//Изменение шрифта
		if(listitem == 0)
		{
			strmid(PosterInfo[NP[playerid]][ppFont], "Arial", 0, strlen("Arial"), 16);
		}
		else if(listitem == 1)
		{
			strmid(PosterInfo[NP[playerid]][ppFont], "Verdana", 0, strlen("Verdana"), 16);
		}
		else if(listitem == 2)
		{
			strmid(PosterInfo[NP[playerid]][ppFont], "Calibri", 0, strlen("Calibri"), 16);
		}
		else if(listitem == 3)
		{
			strmid(PosterInfo[NP[playerid]][ppFont], "Courier New", 0, strlen("Courier New"), 16);
		}
		SetObjectMaterialTextEx(playerid, PosterInfo[NP[playerid]][ppObjectID], PosterInfo[NP[playerid]][ppText], 0, OBJECT_MATERIAL_SIZE_512x256,
			PosterInfo[NP[playerid]][ppFont], PosterInfo[NP[playerid]][ppSize], 1, PosterInfo[NP[playerid]][ppColor], PosterInfo[NP[playerid]][ppBack],
			OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
					
		MenuOperation[playerid] = 5;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите шрифт",
"1.\tArial\n2.\tVerdana\n3.\tCalibri\n4.\tCourier New", "Выбор", "Отмена");
	}
	else if(MenuOperation[playerid] == 6)
	{//Изменение размера шрифта
		if(listitem == 0) PosterInfo[NP[playerid]][ppSize] = 40;
		else if(listitem == 1) PosterInfo[NP[playerid]][ppSize] = 50;
		else if(listitem == 2) PosterInfo[NP[playerid]][ppSize] = 80;
		else if(listitem == 3) PosterInfo[NP[playerid]][ppSize] = 110;
		SetObjectMaterialTextEx(playerid, PosterInfo[NP[playerid]][ppObjectID], PosterInfo[NP[playerid]][ppText], 0, OBJECT_MATERIAL_SIZE_512x256,
			PosterInfo[NP[playerid]][ppFont], PosterInfo[NP[playerid]][ppSize], 1, PosterInfo[NP[playerid]][ppColor], PosterInfo[NP[playerid]][ppBack],
			OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

		MenuOperation[playerid] = 6;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите размер шрифта",
"1.\tОчень Маленький(5 строк по 20 символов)\n2.\tМаленький(5 строк по 16 символов)\n3.\tСредний(3 строки по 12 символов)\n4.\tБольшой(2 строки по 8 символов)", "Выбрать", "Отмена");
	}
	else if(MenuOperation[playerid] == 7)
	{//Изменение цвета шрифта
		PosterInfo[NP[playerid]][ppColor] = listitem;

		SetObjectMaterialTextEx(playerid, PosterInfo[NP[playerid]][ppObjectID], PosterInfo[NP[playerid]][ppText], 0, OBJECT_MATERIAL_SIZE_512x256,
			PosterInfo[NP[playerid]][ppFont], PosterInfo[NP[playerid]][ppSize], 1, PosterInfo[NP[playerid]][ppColor], PosterInfo[NP[playerid]][ppBack],
			OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
					
		format(dlgitem, sizeof(dlgitem), "0\t{%06x}Белый\n1\t{%06x}Красный\n2\t{%06x}Оранжевый\n3\t{%06x}Жёлтый\n4\t{%06x}Салатовый\n5\t{%06x}Зелёный\n6\t{%06x}Травяной\n7\t{%06x}Бирюзовый\
\n8\t{%06x}Синий\n9\t{%06x}Тёмно синий\n10\t{%06x}Фиолетовый\n11\t{%06x}Розовый\n12\t{000000}Коричневый\n13\t{000000}Чёрный",
			COLOR_FONT0 >>> 8,COLOR_FONT1 >>> 8,COLOR_FONT2 >>> 8,COLOR_FONT3 >>> 8,COLOR_FONT4 >>> 8,COLOR_FONT5 >>> 8,COLOR_FONT6 >>> 8,
			COLOR_FONT7 >>> 8,COLOR_FONT8 >>> 8,COLOR_FONT9 >>> 8,COLOR_FONT10 >>> 8,COLOR_FONT11 >>> 8,COLOR_FONT12 >>> 8,COLOR_FONT13 >>> 8);
		MenuOperation[playerid] = 7;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите цвет текста", dlgitem, "Выбор", "Отмена");
	}
	else if(MenuOperation[playerid] == 8)
	{//Изменение цвета фона
		PosterInfo[NP[playerid]][ppBack] = listitem;
		
		SetObjectMaterialTextEx(playerid, PosterInfo[NP[playerid]][ppObjectID], PosterInfo[NP[playerid]][ppText], 0, OBJECT_MATERIAL_SIZE_512x256,
			PosterInfo[NP[playerid]][ppFont], PosterInfo[NP[playerid]][ppSize], 1, PosterInfo[NP[playerid]][ppColor], PosterInfo[NP[playerid]][ppBack],
			OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
					
		format(dlgitem, sizeof(dlgitem), "0\t{%06x}Белый\n1\t{%06x}Красный\n2\t{%06x}Оранжевый\n3\t{%06x}Жёлтый\n4\t{%06x}Салатовый\n5\t{%06x}Зелёный\n6\t{%06x}Травяной\n7\t{%06x}Бирюзовый\
\n8\t{%06x}Синий\n9\t{%06x}Тёмно синий\n10\t{%06x}Фиолетовый\n11\t{%06x}Розовый\n12\t{000000}Коричневый\n13\t{000000}Чёрный",
			COLOR_RAINBOW0 >>> 8,COLOR_RAINBOW1 >>> 8,COLOR_RAINBOW2 >>> 8,COLOR_RAINBOW3 >>> 8,COLOR_RAINBOW4 >>> 8,COLOR_RAINBOW5 >>> 8,COLOR_RAINBOW6 >>> 8,
			COLOR_RAINBOW7 >>> 8,COLOR_RAINBOW8 >>> 8,COLOR_RAINBOW9 >>> 8,COLOR_RAINBOW10 >>> 8,COLOR_RAINBOW11 >>> 8,COLOR_RAINBOW12 >>> 8,COLOR_RAINBOW13 >>> 8);
		MenuOperation[playerid] = 8;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Выберите цвет фона", dlgitem, "Выбор", "Отмена");
	}
	return 1;
}

//stock poster_OnPlayerEditObject(playerid, playerobject, objectid, response,
stock poster_OnPlayerEditObject(playerid, objectid, response,
	Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	if(PosterEditStatus[playerid] != 2) return 1;
	//#pragma unused playerobject
	#pragma unused objectid
	#pragma unused fRotX
	#pragma unused fRotY
	#pragma unused fRotZ
	
	new dlgitem[232+12*10];
   	if(response == EDIT_RESPONSE_FINAL)//если нажал сохранить после изменения
	{
		PosterInfo[objectid][ppX] = fX;
		PosterInfo[objectid][ppY] = fY;
		PosterInfo[objectid][ppZ] = fZ;
		PosterInfo[objectid][ppR] = fRotZ;
		
		//CancelEdit(playerid);
		format(dlgitem, sizeof(dlgitem), "1.\tТекст\n2.\tШрифт\n3.\tРазмер Шрифта\n4.\tЦвет текста\n5.\tЦвет Фона\n6.\tПозицию");
		MenuOperation[playerid] = 3;
		ShowPlayerDialogEx(playerid, BIGBOARD_DIALOG2, DIALOG_STYLE_LIST, "Редактировать", dlgitem, "Выбор", "Отмена");
		SavePoster();

   	}
   	if(response == EDIT_RESPONSE_CANCEL)//Отмена от редактирования
	{
		format(dlgitem, sizeof(dlgitem), "%s отказался от размещения объявления на рекламный щит !", PlayerName(playerid));
		//ProxDetector(playerid, 30.0, dlgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		NP[Offer[playerid]] = 0;
		NP[playerid] = 0;
		MenuOperation[Offer[playerid]] = 0;
		MenuOperation[playerid] = 0;
		Offer[Offer[playerid]] = MAX_PLAYERS-1;
		Offer[playerid] = MAX_PLAYERS-1;
	}
	PosterEditStatus[playerid] = 0;
	return 1;
}

stock poster_OnEnterCheckpoint(playerid)//Выполняется, когда игрок заходит в чекпойнт (контрольную точку).
//playerid - ID вошедшего в контрольную точку (чекпойнт) игрока
{
	if(IsPlayerNPC(playerid)) return 1;
	if(CP[playerid] == CP_BIGBOARD)
	{
	    DisablePlayerCheckpointEx(playerid);
	    CP[playerid] = 0;
	}
	return 1;
}

//stock SetObjectMaterialTextEx(playerid, objectid, text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128,
//	fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFF000000, backcolor = 0xFFFFFFFF, textalignment = 0)
stock SetObjectMaterialTextEx(playerid, objectid, text[], materialindex, materialsize,
	fontface[], fontsize, bold, fontcolor, backcolor, textalignment)
{
	if(	objectid == LastPosterInfo[NP[playerid]][ppObjectID] &&
		!strcmp(text, LastPosterInfo[NP[playerid]][ppText], true) &&
		!strcmp(fontface, LastPosterInfo[NP[playerid]][ppFont], true) &&
		fontsize == LastPosterInfo[NP[playerid]][ppSize] &&
		fontcolor == LastPosterInfo[NP[playerid]][ppColor] &&
		backcolor == LastPosterInfo[NP[playerid]][ppBack]
	  ) { SendClientMessageEx(playerid, -1, "Ни чего не изменено"); return 0; }
	  
	new timers = GetTickCount();
	if(ANTIFLOOD == 1)
	{
		if((timers - GetPVarInt(playerid, "ObjectMaterial")) < 2000)
		{
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}Вы можете использовать SetObjectMaterialText только раз в две секунды.");
		    return 0;
		}

    }//флуд конец
    
	strmid(PosterInfo[NP[playerid]][ppMaker], PlayerName(playerid), 0, 24, 24);
    
	new FontColor;
	if(fontcolor == 0) FontColor = COLOR_RAINBOW0;
	else if(fontcolor == 1) FontColor = COLOR_RAINBOW1;
	else if(fontcolor == 2) FontColor = COLOR_RAINBOW2;
	else if(fontcolor == 3) FontColor = COLOR_RAINBOW3;
	else if(fontcolor == 4) FontColor = COLOR_RAINBOW4;
	else if(fontcolor == 5) FontColor = COLOR_RAINBOW5;
	else if(fontcolor == 6) FontColor = COLOR_RAINBOW6;
	else if(fontcolor == 7) FontColor = COLOR_RAINBOW7;
	else if(fontcolor == 8) FontColor = COLOR_RAINBOW8;
	else if(fontcolor == 9) FontColor = COLOR_RAINBOW9;
	else if(fontcolor == 10) FontColor = COLOR_RAINBOW10;
	else if(fontcolor == 11) FontColor = COLOR_RAINBOW11;
	else if(fontcolor == 12) FontColor = COLOR_RAINBOW12;
	else if(fontcolor == 13) FontColor = COLOR_RAINBOW13;
	
	new BackColor;
	if(backcolor == 0) BackColor = COLOR_RAINBOW0;
	else if(backcolor == 1) BackColor = COLOR_RAINBOW1;
	else if(backcolor == 2) BackColor = COLOR_RAINBOW2;
	else if(backcolor == 3) BackColor = COLOR_RAINBOW3;
	else if(backcolor == 4) BackColor = COLOR_RAINBOW4;
	else if(backcolor == 5) BackColor = COLOR_RAINBOW5;
	else if(backcolor == 6) BackColor = COLOR_RAINBOW6;
	else if(backcolor == 7) BackColor = COLOR_RAINBOW7;
	else if(backcolor == 8) BackColor = COLOR_RAINBOW8;
	else if(backcolor == 9) BackColor = COLOR_RAINBOW9;
	else if(backcolor == 10) BackColor = COLOR_RAINBOW10;
	else if(backcolor == 11) BackColor = COLOR_RAINBOW11;
	else if(backcolor == 12) BackColor = COLOR_RAINBOW12;
	else if(backcolor == 13) BackColor = COLOR_RAINBOW13;
	
	/*format(strings, sizeof(strings), "SetObjectMaterialText(%d[%d], %s[%s])",
		objectid, LastPosterInfo[NP[playerid]][ppObjectID],
		text, LastPosterInfo[NP[playerid]][ppText]);
	SendClientMessageEx(playerid, -1, strings);

	format(strings, sizeof(strings), "SetObjectMaterialText(fontface: %s[%s], fontsize: %d[%d])",
		fontface, LastPosterInfo[NP[playerid]][ppFont],
		fontsize, LastPosterInfo[NP[playerid]][ppSize]);
	SendClientMessageEx(playerid, -1, strings);

	format(strings, sizeof(strings), "SetObjectMaterialText(fontcolor: %d[%x], backcolor: %d[%x])",
		fontcolor, FontColor,
		backcolor, BackColor);
	SendClientMessageEx(playerid, -1, strings);*/
	
	LastPosterInfo[NP[playerid]][ppObjectID] = objectid;
	strmid(LastPosterInfo[NP[playerid]][ppText], text, 0, 128, 255);
	strmid(LastPosterInfo[NP[playerid]][ppFont], fontface, 0, 16, 255);
	LastPosterInfo[NP[playerid]][ppSize] = fontsize;
	LastPosterInfo[NP[playerid]][ppColor] = fontcolor;
	LastPosterInfo[NP[playerid]][ppBack] = backcolor;

	//SetObjectMaterial(objectid, 0, 0, "none", "none", 0);
	//SetObjectMaterialText(objectid, "none", materialindex, materialsize, "Calibri", 28, 0, 0xFFFF8200, 0xFFFAFAFA, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	SetPVarInt(playerid, "ObjectMaterial", timers);
	
	PosterInfo[NP[playerid]][ppDate] = getdate();
	return SetObjectMaterialText(objectid, text, materialindex, materialsize, fontface, fontsize, bold, FontColor, BackColor, textalignment);
	//return 1;
}
