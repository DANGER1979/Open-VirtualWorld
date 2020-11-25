#define GANGAREA_WARNINGS 1 //необходимое кол-во убийств Для начала моргания
#define GANGAREA_TAKE 2 //необходимое кол-во убийств для отвоевания зоны
#define REOWN_TURF 3   //необходимое кол-во убийств для захвата зоны

enum zInfo
{
	zFlash,//состояние зоны необходимо после вайпа при наличии нейтральных зон
	zName[20],//имя зоны
	zOwner[20],//имя банды владеющей зоной
	zColor[10],//цвет зоны не возможно загрузить из файла
	zFamily,//номер банды владеющей зоной
};
new TurfInfo[MAX_TURFS][zInfo];
new Turfs[MAX_TURFS];//идентификатор всех зон

//------------------------------------------------------------------------------
stock TurfInfo_Load()
{
	new time = GetTickCount();
	if( !fexist("property/turf.info") )
	{
		TurfInfo_Save();//если файла нет, то создать
		return 1;
	}
	new idx;
	new File: pFile = fopen("property/turf.info", io_read);//io_readwrite
	if(pFile)
	{
		new arrCoords[3][MAX_PLAYER_NAME];
		new strFromFile[648];
		for(idx=0; idx<MAX_TURFS; idx++)
		{
			fread(pFile, strFromFile);
			split(strFromFile, arrCoords, ',');

			strmid(TurfInfo[idx][zName], regions[idx][region_name], 0, 20, 32);
			TurfInfo[idx][zFamily] = strval(arrCoords[0]);
			HouseInfo[idx][hRooms] = strval(arrCoords[1]);
		}
		fclose(pFile);
	}
	//==========================================================================

	// Zones
	for(new j=0; j<MAX_TURFS; j++)//для зон банд 230 MAX_TURFS
	{
//Создали 355 новых зон в памяти сервера
		Turfs[j] = GangZoneCreate(regions[j][region_minx], regions[j][region_miny], regions[j][region_maxx], regions[j][region_maxy]);//Создать новую зону в памяти сервера
		taketurfcount[j] = TimeTakeZone;//всем зонам установили время захвата

//устанавливаем всем зонам первоначальные цвета в соот. с цветом банды
		if(TurfInfo[j][zFamily] == 255 || TurfInfo[j][zFamily] == 0) TurfInfo[j][zColor] = FamilyInfo[0][fColor];
		else TurfInfo[j][zColor] = FamilyInfo[TurfInfo[j][zFamily]][fColor];
		//TurfInfo[j][zFamily] = 0;//временно
		//strmid(TurfInfo[j][zName], regions[j][region_name], 0, strlen(regions[j][region_name]), 255);
		//strlen - Эта функция может быть использована для проверки длины указанной строки.

//каждому бизу устанавливаем крышу
		for(new b=0; b<MAX_BIZ; b++)
		{   //сканируем все бизы что находятся в данной зоне
			if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], j) )//если биз находится в координатах по строке j из массива zones
			{   //если биз находится в данной зоне
				BizInfo[b][bExtortion] = TurfInfo[j][zFamily];
				//break;
			}
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{   //сканируем все бизы что находятся в данной зоне
			if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], j) )//если биз находится в координатах по строке j из массива zones
			{   //если биз находится в данной зоне
				SBizInfo[sb][sbExtortion] = TurfInfo[j][zFamily];
				//break;
			}
		}
	}
	//SaveTurfsSQL();//временно
	printf("8/19. [Загрузка и создание зон]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
}


stock TurfInfo_Save()
{
	new time = GetTickCount();
	new File: hFile = fopen("property/turf.info", io_write);
	new idx;
	if( !fexist("property/turf.info") ) hFile = fopen("property/turf.info", io_write);
	else hFile = fopen("property/turf.info", io_append);
	if(hFile)
	{
		while(idx < sizeof(TurfInfo))
		{
			new coordsstring[512];
			format(coordsstring, sizeof(coordsstring),"%d,'%s','%s','%s',%d,\n",
				TurfInfo[idx][zFlash],
				TurfInfo[idx][zName],
				TurfInfo[idx][zOwner],
				TurfInfo[idx][zColor],
				TurfInfo[idx][zFamily]);
			//fwrite(hFile, coordsstring);
		    for(new c=0; c<strlen(coordsstring); c++)
			{
		        fputchar(hFile, coordsstring[c], false);
		    }
			idx ++;
		}
		fclose(hFile);//закрываем файл по указателю file2
	}
	//ИНФОРМИРОВАНИЕ
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "8/19. [Сохранение зон]: Было сохранено - %d, потрачено - %d (ms)", MAX_TURFS, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}

