//��� ������������ ������
//������� PLIDs ��������� ������ �� ������� ������ ��� ��� ��������� �� ������� � �� ������ ����������� ���
//� ������� �� GetPlayerPoolSize, ������� ������ ������ ������������ �� ������ � ����
//PLIDs ��� ���������� ������ for(new i=0; i<MAX_PLAYERS; i++)//GetMaxPlayers()//HighestPlayerID
new PLIDs[MAX_PLAYERS] = {-1,...};
new MaxPlayers = 0;//���-�� �������� � ���� �������
//StreamedVehicle ��� ���������� ������ for(new vid = 1; vid<=MAX_VEHICLES; vid++)
#define MAX_STREAMEDCARS MAX_VEHICLES //1000 ������������ ���������� �����, ������� ����� ��������� ����� ����� ������.
new StreamedVehicle[MAX_PLAYERS][MAX_STREAMEDCARS];//������ ����� �������� � ���� ������
new StreamVehCount[MAX_PLAYERS];//���-�� ����� �������� � ���� ������

//##############################################################################//
//                                                                              //
//                              ������� �����������                             //
//                                                                              //
//##############################################################################//
//������� ������� ������������� �� ��� ����, � ��� ����������� ���� � ������� �������
//��� ���������� ������ for(new i=0; i<MAX_PLAYERS; i++)//GetMaxPlayers()//HighestPlayerID
// PLIDs
stock plids_OnGameModeInit()
{
	Itter_InitInternal(StreamedVehicle, MAX_PLAYERS, MAX_STREAMEDCARS);//��� ������������ ������
}
stock plids_OnGameModeExit()
{

}
stock plids_OnPlayerConnect(playerid)
{
	PLIDs[MaxPlayers] = playerid;
	MaxPlayers++;

	new start;//��� ������������ ������
	Itter_ClearInternal(start, StreamVehCount[playerid], StreamedVehicle[playerid]);
}
stock plids_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	for(new i=0; i<MaxPlayers; i++)
	{
		if(PLIDs[i] == playerid)
		{//���� � ������� ���� ����� ��, �.�. ����� ����� �� ������
			MaxPlayers --;
			PLIDs[i] = PLIDs[MaxPlayers];
			PLIDs[MaxPlayers] = -1;
			break;
		}
	}
}
// PLIDs �����
//------------------------------------------------------------------------------
//��� ���������� ������ for(new i=1; i<=MAX_VEHICLES; i++)//GetMaxVehicles
// PLIDs
stock plids_OnVehicleStreamIn(vehicleid, forplayerid)
{   //���������� ��� ��������� ����� vehicleid � ���� ������ ������ forplayerid.
// ��������� � ������������ ���� ����� �������� ��� ����� ������.
	new start;//StreamVehStart[forplayerid]
	Itter_AddInternal(start, StreamVehCount[forplayerid], StreamedVehicle[forplayerid], vehicleid);//��� ������������ ������
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
stock plids_OnVehicleStreamOut(vehicleid, forplayerid)
{   //���������� ��� ������������ ����� ����� � ���� ������ ������.
// ������� �������� ��� ����� ������.
	new start;//StreamVehStart[forplayerid]
    Itter_RemoveInternal(start, StreamVehCount[forplayerid], StreamedVehicle[forplayerid], vehicleid);//��� ������������ ������
}


//##############################################################################//
//                                                                              //
//                              ������������ �����                              //
//                                                                              //
//##############################################################################//

//��� ���������� ������ for(new vid = 1; vid<=MAX_VEHICLES; vid++)
/*----------------------------------------------------------------------------*-
Function: Itter_InitInternal
Params:
	array[][] - Itterator array to initialise.
	s0 - ������ ������� ���������.
	s1 - ������ ������� ���������.
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
//��� ������������ ������ ������
Function: Itter_AddInternal
Params:
	&start - ��������� ������ �������.
	&count - ���������� �������.
	array[] - ������.
	value - �������� ��� ����������.
Return:	-
Notes:	Adds a value to a given itterator set.
-*----------------------------------------------------------------------------*/
stock Itter_AddInternal(&start, &count, array[], value)
{   //���������� �� OnVehicleStreamIn
	if(array[value] != -1)
	{   //����� �� ����� ���� ������ � ������� �� ����� �������� �� ������
		return 0;
	}
//////new strings[MAX_STRING];
	++count;
	if(start == -1)
	{   //�� ����� �� ����������
		start = value;
		//printf("start: %d", start);
	}
	else if(start > value)
	{   //�� ����� �� ����������
		array[value] = start;
		start = value;
	}
	else //if(start != -1 && start <= value)
	{
		new	cur = start, last;
		//new	cur, last;
		do
		{   //������ ���� �� ����� �� ��������� ������
			last = cur;
			cur = array[cur];
			if(cur > value)
			{   //���� ���������� �������� ������ ������ �������������
				array[value] = cur;//�������� �������
				array[last] = value;
//printf("1. start:%d,count:%d, array[value:%d]: %d, array[last:%d]: %d", start, count, value, array[value], last, array[last]);
	//��������������
	//format(strings, sizeof(strings), "count: %d, array[value:%d]: %d, array[last:%d]: %d", count, value, array[value], last, array[last]);
	//ABroadCast(COLOR_GREEN,strings,9);
				return 1;
			}
		}
		while(cur != -1);//����� �� ����� ��� ������ cur
		array[last] = value;
//printf("2. start:%d,count:%d, array[last:%d]: %d", start, count, last, array[last]);
	//��������������
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
{   //���������� �� OnVehicleStreamOut
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
		//����������� �� 1 ������� �����
//printf("3. start:%d,count:%d, array[cur:%d]: %d, array[value:%d]: %d", start, count, cur, array[cur], value, array[value]);
	//��������������
	//format(strings, sizeof(strings), "count: %d, array[cur:%d]: %d, array[value:%d]: %d", count, cur, array[cur], value, array[value]);
	//ABroadCast(COLOR_RED,strings,9);
	}
	array[value] = -1;//���������� ������
	--count;
//printf("4. start:%d,count:%d, array[value:%d]: %d", start, count, value, array[value]);
	//��������������
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
{   //���������� �� OnPlayerInit
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
Params:	start - ��������� ����� Itterator.
	members[] - ���������� Itterator.
	size - ����� ������� itterator
Return:	-
Notes:	Pure debug function.  Has regular prints not debug prints
	as it's only called when debug is on.
-*----------------------------------------------------------------------------*/
stock Itter_ShowArray(start, members[], size)
{   //������� ������ ���� �����-����� ������
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
//��� ������������ ������ �����
