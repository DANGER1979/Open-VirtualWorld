//для динамических циклов
//система PLIDs формирует массив ИД игроков только тех кто находятся на сервере и не хранит пропущенные ИДы
//в отличии от GetPlayerPoolSize, который просто хранит максимальный ИД игрока в игре
//PLIDs для оптмизации циклов for(new i=0; i<MAX_PLAYERS; i++)//GetMaxPlayers()//HighestPlayerID
new PLIDs[MAX_PLAYERS] = {-1,...};
new MaxPlayers = 0;//кол-во зашедших в игру игроков
//StreamedVehicle для оптмизации циклов for(new vid = 1; vid<=MAX_VEHICLES; vid++)
#define MAX_STREAMEDCARS MAX_VEHICLES //1000 Максимальное количество тачек, которое может находится рядом возле игрока.
new StreamedVehicle[MAX_PLAYERS][MAX_STREAMEDCARS];//массив тачек попавших в поле радара
new StreamVehCount[MAX_PLAYERS];//кол-во тачек попавших в поле радара

//##############################################################################//
//                                                                              //
//                              ФУНКЦИИ ОПТИМИЗАЦИИ                             //
//                                                                              //
//##############################################################################//
//функции которые предназначены не для игры, а для оптимизации кода и решения проблем
//для оптмизации циклов for(new i=0; i<MAX_PLAYERS; i++)//GetMaxPlayers()//HighestPlayerID
// PLIDs
stock plids_OnGameModeInit()
{
	Itter_InitInternal(StreamedVehicle, MAX_PLAYERS, MAX_STREAMEDCARS);//для динамических циклов
}
stock plids_OnGameModeExit()
{

}
stock plids_OnPlayerConnect(playerid)
{
	PLIDs[MaxPlayers] = playerid;
	MaxPlayers++;

	new start;//для динамических циклов
	Itter_ClearInternal(start, StreamVehCount[playerid], StreamedVehicle[playerid]);
}
stock plids_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	for(new i=0; i<MaxPlayers; i++)
	{
		if(PLIDs[i] == playerid)
		{//если в массиве есть такой ИД, т.е. игрок вошёл на сервер
			MaxPlayers --;
			PLIDs[i] = PLIDs[MaxPlayers];
			PLIDs[MaxPlayers] = -1;
			break;
		}
	}
}
// PLIDs конец
//------------------------------------------------------------------------------
//для оптмизации циклов for(new i=1; i<=MAX_VEHICLES; i++)//GetMaxVehicles
// PLIDs
stock plids_OnVehicleStreamIn(vehicleid, forplayerid)
{   //Вызывается при появлении тачки vehicleid в поле зрения игрока forplayerid.
// Добавляем в динамическии цикл новую итерацию для этого игрока.
	new start;//StreamVehStart[forplayerid]
	Itter_AddInternal(start, StreamVehCount[forplayerid], StreamedVehicle[forplayerid], vehicleid);//для динамических циклов
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
stock plids_OnVehicleStreamOut(vehicleid, forplayerid)
{   //Вызывается при исчезновении стрим тачки в поле зрения игрока.
// Удаляем итерацию для этого игрока.
	new start;//StreamVehStart[forplayerid]
    Itter_RemoveInternal(start, StreamVehCount[forplayerid], StreamedVehicle[forplayerid], vehicleid);//для динамических циклов
}


//##############################################################################//
//                                                                              //
//                              ДИНАМИЧЕСКИЕ ЦИКЛЫ                              //
//                                                                              //
//##############################################################################//

//для оптмизации циклов for(new vid = 1; vid<=MAX_VEHICLES; vid++)
/*----------------------------------------------------------------------------*-
Function: Itter_InitInternal
Params:
	array[][] - Itterator array to initialise.
	s0 - Размер первого измерения.
	s1 - Размер второго измерения.
Return:	-
Notes: Multi-dimensional arrays can't be initialised at compile time, so need to be
	done at run time, which is slightly annoying.
-*----------------------------------------------------------------------------*/
stock Itter_InitInternal(arr[][], size1, size2)
{
	for(new i = 0; i != size1; ++i)
	{
		for(new j = 0; j != size2; ++j)
		{
			arr[i][j] = -1;
		}
	}
}
/*----------------------------------------------------------------------------*-
//для динамических циклов начало
Function: Itter_AddInternal
Params:
	&start - Стартовый индекс Массива.
	&count - Количество записей.
	array[] - Массив.
	value - Значение для добавления.
Return:	-
Notes:	Adds a value to a given itterator set.
-*----------------------------------------------------------------------------*/
stock Itter_AddInternal(&start, &count, array[], value)
{   //вызывается из OnVehicleStreamIn
	if(array[value] != -1)
	{   //выйти из цыкла если ячейка в которую мы хотим записать НЕ пустая
		return 0;
	}
//////new strings[MAX_STRING];
	++count;
	if(start == -1)
	{   //ни когда не выполнится
		start = value;
		//printf("start: %d", start);
	}
	else if(start > value)
	{   //ни когда не выполнится
		array[value] = start;
		start = value;
	}
	else //if(start != -1 && start <= value)
	{
		new	cur = start, last;
		//new	cur, last;
		do
		{   //делать пока не дойдём до свободной ячейки
			last = cur;
			cur = array[cur];
			if(cur > value)
			{   //если добавочное значение больше самого максимального
				array[value] = cur;//записать текущее
				array[last] = value;
//printf("1. start:%d,count:%d, array[value:%d]: %d, array[last:%d]: %d", start, count, value, array[value], last, array[last]);
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "count: %d, array[value:%d]: %d, array[last:%d]: %d", count, value, array[value], last, array[last]);
	//ABroadCast(COLOR_GREEN,strings,9);
				return 1;
			}
		}
		while(cur != -1);//выйти из цыкла как только cur
		array[last] = value;
//printf("2. start:%d,count:%d, array[last:%d]: %d", start, count, last, array[last]);
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "count: %d, array[value:%d]: %d, array[last:%d]: %d", count, value, array[value], last, array[last]);
	//ABroadCast(COLOR_BRIGHTLYGREEN,strings,9);
	}
	return 1;
}
/*----------------------------------------------------------------------------*-
Function:	Itter_RemoveInternal
Params:
	&start - Array start index.
	&count - Number of items in the itterator.
	array[] - Itterator data.
	value - Item to remove.
Return:	-
Notes:	Removes a value from an itterator.
-*----------------------------------------------------------------------------*/
stock Itter_RemoveInternal(&start, &count, array[], value)
{   //вызывается из OnVehicleStreamOut
	if(start == -1)
	{
		return 0;
	}
//////new strings[MAX_STRING];
	if(start == value)
	{
		start = array[value];
	}
	else
	{
		new	cur = start;
		while(array[cur] != value)
		{
			cur = array[cur];
			if(cur == -1)
			{
				return 0;
			}
		}
		array[cur] = array[value];
		//переместили на 1 уровень вверх
//printf("3. start:%d,count:%d, array[cur:%d]: %d, array[value:%d]: %d", start, count, cur, array[cur], value, array[value]);
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "count: %d, array[cur:%d]: %d, array[value:%d]: %d", count, cur, array[cur], value, array[value]);
	//ABroadCast(COLOR_RED,strings,9);
	}
	array[value] = -1;//освободили ячейку
	--count;
//printf("4. start:%d,count:%d, array[value:%d]: %d", start, count, value, array[value]);
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "count: %d, array[cur:%d]: %d, array[value:%d]: %d", count, cur, array[cur], value, array[value]);
	//ABroadCast(COLOR_GREY,strings,9);
	return 1;
}
/*----------------------------------------------------------------------------*-
Function:
	Itter_ClearInternal
Params:
	&start - Array start index.
	&count - Number of items in the itterator.
	array[] - Itterator data.
Return:
	-
Notes:
	Resets an iterator.
-*----------------------------------------------------------------------------*/
stock Itter_ClearInternal(&start, &count, array[])
{   //вызывается из OnPlayerInit
	if(start != -1)
	{
		new	cur = start, next = array[cur];
		start = -1;	count = 0;
		while(next != -1)
		{
			array[cur] = -1;
			cur = next;
			next = array[cur];
		}
	}
}
/*----------------------------------------------------------------------------*-
Function:	Itter_ShowArray
Params:	start - Стартовая точка Itterator.
	members[] - Содержание Itterator.
	size - Номер величин itterator
Return:	-
Notes:	Pure debug function.  Has regular prints not debug prints
	as it's only called when debug is on.
-*----------------------------------------------------------------------------*/
stock Itter_ShowArray(start, members[], size)
{   //выводит массив всех стрим-тачек вокруг
	static sString[61];
	new	i,	j = 10;
	printf("Start: %d", start);
	printf("Size:  %d", size);
	while (i < size)
	{
		sString[0] = '\0';
		while (i < j && i < size)
		{
			format(sString, sizeof (sString), "%s, %d", sString, members[i]);
			i ++;
		}
		printf("Array (%d): %s", j, sString);
		j += 10;
	}
}
//для динамических циклов конец
