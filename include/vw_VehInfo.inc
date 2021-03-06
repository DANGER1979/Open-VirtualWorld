//���������, �������������, �������� � ���������� ������� VehInfo
//��� ���������� ����������� ��� ������ � �������
//------------------------------------------------

//==============================================================================
enum cInfo
{
	cIND,
	cID,
	cKey[12],
	cModel,
	cType,
	cOwned,
	cOwner[MAX_PLAYER_NAME],
	Float:cLocX,
	Float:cLocY,
	Float:cLocZ,
	Float:cAng,
	cInt,
	cVirt,
	cLock,//1 - ������
	cPark,//1 - ����������, 2- �� ������, >=40(#PARKING) �� ���������� �� ��������
	cAttach,//��� ���������� �� ����� ��������
	cInsur,//��������� �����
	cDist,//������� ������� �������
	Float: cFuel,//������� ������� �������
	cLoad,//������� ������� ��������
	cLoadType,//��� �����
	cWhere,
	cDate,
//������
	cColor1,//15
	cColor2,
	cPaintjob,//17
	cSpoiler,
	cHood,
	cRoof,
	cSideskirt,
	cLamps,
	cNitro,
	cExhaust,
	cWheels,
	cStereos,
	cHydraulics,
	cFrontBumper,
	cRearBumper,
	cVentRight,
	cVentLeft,//31
	cNeonl,
	cNeonr,
	Float: cHealth,
//������� �����������
	DamagePanels,
	DamageDoors,
	DamageLights,
	DamageTires
};
new VehInfo[MAX_VEHICLES+1][cInfo];

//==============================================================================

//stock VehInfo_OnCarInit(vehicleid)
forward VehInfo_OnCarInit(vehicleid);
public VehInfo_OnCarInit(vehicleid)//�-�� ��������� ������� VehInfo, ����� ����� ����� �� ��������� �������� ������� � �� �� ������ ����
{//���������� �� public DestroyVehicleEx
	VehInfo[vehicleid][cIND] = 0;
	VehInfo[vehicleid][cID] = 0;
	//strmid(VehInfo[vehicleid][cKey], "", 0, strlen(""), 12);
	//VehInfo[vehicleid][cModel] = 0;
	//VehInfo[vehicleid][cType] = 1000;
	VehInfo[vehicleid][cOwned] = 0;

 	VehInfo[vehicleid][cLocX] = 0.0;
 	VehInfo[vehicleid][cLocY] = 0.0;
	VehInfo[vehicleid][cLocZ] = 0.0;
	VehInfo[vehicleid][cAng] = 0.0;

	VehInfo[vehicleid][cInt] = 0;
	VehInfo[vehicleid][cVirt] = 0;
	//UnLockCar(vehicleid);
	VehInfo[vehicleid][cLock] = 0;
	VehInfo[vehicleid][cPark] = 0;
	VehInfo[vehicleid][cInsur] = 0;
	VehInfo[vehicleid][cFuel] = 1.0;//������ ����� ��������� ��� ��� ���������� ����� �����
	VehInfo[vehicleid][cLoad] = 0;
	VehInfo[vehicleid][cLoadType] = 0;
	VehInfo[vehicleid][cDate] = 0;
	VehInfo[vehicleid][cColor1] = -1;
	VehInfo[vehicleid][cColor2] = -1;
	VehInfo[vehicleid][cPaintjob] = 255;
	VehInfo[vehicleid][cSpoiler] = 0;
	VehInfo[vehicleid][cHood] = 0;
	VehInfo[vehicleid][cRoof] = 0;
	VehInfo[vehicleid][cSideskirt] = 0;
	VehInfo[vehicleid][cLamps] = 0;
	VehInfo[vehicleid][cNitro] = 0;
	VehInfo[vehicleid][cExhaust] = 0;
	VehInfo[vehicleid][cWheels] = 0;
	VehInfo[vehicleid][cStereos] = 0;
	VehInfo[vehicleid][cHydraulics] = 0;
	VehInfo[vehicleid][cFrontBumper] = 0;
	VehInfo[vehicleid][cRearBumper] = 0;
	VehInfo[vehicleid][cVentRight] = 0;
	VehInfo[vehicleid][cVentLeft] = 0;

	VehInfo[vehicleid][cNeonl] = 0;
	VehInfo[vehicleid][cNeonr] = 0;

	VehInfo[vehicleid][cHealth] = 260.0;//������ �� ��������

	VehInfo[vehicleid][DamagePanels] = 0;
	VehInfo[vehicleid][DamageDoors] = 0;
	VehInfo[vehicleid][DamageLights] = 0;
	VehInfo[vehicleid][DamageTires] = 0;
	gVehicleSpawn[vehicleid] = 0;
}

//==============================================================================


