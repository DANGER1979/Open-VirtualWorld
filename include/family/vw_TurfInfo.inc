#define GANGAREA_WARNINGS 1 //����������� ���-�� ������� ��� ������ ��������
#define GANGAREA_TAKE 2 //����������� ���-�� ������� ��� ���������� ����
#define REOWN_TURF 3   //����������� ���-�� ������� ��� ������� ����

enum zInfo
{
	zFlash,//��������� ���� ���������� ����� ����� ��� ������� ����������� ���
	zName[20],//��� ����
	zOwner[20],//��� ����� ��������� �����
	zColor[10],//���� ���� �� �������� ��������� �� �����
	zFamily,//����� ����� ��������� �����
};
new TurfInfo[MAX_TURFS][zInfo];
new Turfs[MAX_TURFS];//������������� ���� ���

//------------------------------------------------------------------------------
stock TurfInfo_Load()
{
	new time = GetTickCount();
	if( !fexist("property/turf.info") )
	{
		TurfInfo_Save();//���� ����� ���, �� �������
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
	for(new j=0; j<MAX_TURFS; j++)//��� ��� ���� 230 MAX_TURFS
	{
//������� 355 ����� ��� � ������ �������
		Turfs[j] = GangZoneCreate(regions[j][region_minx], regions[j][region_miny], regions[j][region_maxx], regions[j][region_maxy]);//������� ����� ���� � ������ �������
		taketurfcount[j] = TimeTakeZone;//���� ����� ���������� ����� �������

//������������� ���� ����� �������������� ����� � ����. � ������ �����
		if(TurfInfo[j][zFamily] == 255 || TurfInfo[j][zFamily] == 0) TurfInfo[j][zColor] = FamilyInfo[0][fColor];
		else TurfInfo[j][zColor] = FamilyInfo[TurfInfo[j][zFamily]][fColor];
		//TurfInfo[j][zFamily] = 0;//��������
		//strmid(TurfInfo[j][zName], regions[j][region_name], 0, strlen(regions[j][region_name]), 255);
		//strlen - ��� ������� ����� ���� ������������ ��� �������� ����� ��������� ������.

//������� ���� ������������� �����
		for(new b=0; b<MAX_BIZ; b++)
		{   //��������� ��� ���� ��� ��������� � ������ ����
			if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], j) )//���� ��� ��������� � ����������� �� ������ j �� ������� zones
			{   //���� ��� ��������� � ������ ����
				BizInfo[b][bExtortion] = TurfInfo[j][zFamily];
				//break;
			}
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{   //��������� ��� ���� ��� ��������� � ������ ����
			if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], j) )//���� ��� ��������� � ����������� �� ������ j �� ������� zones
			{   //���� ��� ��������� � ������ ����
				SBizInfo[sb][sbExtortion] = TurfInfo[j][zFamily];
				//break;
			}
		}
	}
	//SaveTurfsSQL();//��������
	printf("8/19. [�������� � �������� ���]: ���� ��������� - %d, ��������� - %d (ms)", idx, (GetTickCount()-time));
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
		fclose(hFile);//��������� ���� �� ��������� file2
	}
	//��������������
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "8/19. [���������� ���]: ���� ��������� - %d, ��������� - %d (ms)", MAX_TURFS, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}

