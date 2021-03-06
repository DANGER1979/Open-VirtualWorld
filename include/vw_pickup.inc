//http://objects.multiworldsserver.ru/index.php?category=64

//==============================================================================
//��� ��������� ������� ������

new PickupID[MAX_PICKUPS];//�� ������� ������������ �� pickupid MAX_PICKUPS=4096
new Text3D: Text3DPickupID[MAX_PICKUPS];//�� MAX_3DTEXT_PLAYER=1024

enum pickupsinfo
{
    //p_ID,
	p_model,
    p_type,
    Float:p_x,
    Float:p_y,
    Float:p_z,
    p_vw
}
new Pickups[MAX_PICKUPS][pickupsinfo];//������ ��������� ������� ��� ������������� �-�� SetPickupEx

//��� �������� ����� � ����� ���� �� ������ //����������� ������ �������.
enum picInfo
{
    picID,
    Float:picX,
    Float:picY,
    Float:picZ
};//����� ������������ ��� AddStaticPickupEx
//������ �� � ���������� ������ � ������� ����� ������ ��� �����
new PickUpPickup[MAX_PLAYERS][picInfo];//��� �������� ������� ������ ��� ������������ ������



#define MAX_VEHICLE_PICKUPS 1
new VehiclePickups[MAX_VEHICLE_PICKUPS][pickupsinfo] = {//���������� �������
//������� ���� ���� �������
{3096,14,-126.7453,-1264.7269,3.7841}//3.7841 32 ��� ������������� � ���������� 3.1835
};

//#define MAX_PICKUP 5
enum derbypickupsinfo {
	dp_model,
    dp_type,
    Float:dp_x,
    Float:dp_y,
    Float:dp_z
}
new RepairPickups[][derbypickupsinfo] = {//���������� �������
{3096, 14, -1441.35, 1045.15, 1034.56},
{3096, 14, -1451.36, 1019.85, 1026.57},
{3096, 14, -1419.28, 996.60, 1024.54},
{3096, 14, -1357.30, 946.79, 1031.80},
{3096, 14, -1451.12, 992.29, 1024.81}
};



//��� ��������� �������
#define MAX_PLAYER_PICKUPS 96//83//21+4+2+6+6+5+70+6+4+8+3+10+23=168 //206//154
enum pickupinfo
{
    //p_ID,
	p_model,
    p_type,
    Float:p_x,
    Float:p_y,
    Float:p_z,
    p_v,
    
	lText[128],//19+20+24+1
	lColor,
	Float:lDist,//��������� ���������
	lLos//����� �� ����� ����� �����
}
/*
#define MINER 		1
#define LAWYER 		2
#define ROADWORKER  3
#define DRUGDEALER  4
#define CARJACKER   5
#define AUTOBUYER   6
#define CARMECHANIC 7
#define FARMER 		8
#define ARMSDEALER	9
#define CARDEALER	10
#define INKASSATOR  11
#define BOOKMAKER 	12
#define TAXIDRIVER 	13
#define BUSDRIVER 	14
#define PAPERBOY 	15
#define TRUCKER     16
#define TRASHMAN  	17
#define LOADER 		18
#define WOODSMAN  	19
#define FISHER  	20
#define FIREMAN		21
#define COOKER  	22

\n1.\t ��������� �����\
\n2.\t �����������\
\n3.\t �����������\
\n4.\t ���������\
\n5.\t ����������\
\n6.\t �������\
\n7.\t �������� ��������\
\n8.\t ������\
\n9.\t ������������\
\n10.\t �������� ����������\
*/
new PlayerPickups[MAX_PLAYER_PICKUPS][pickupinfo] = {//���������� �������
//21 ����� ��� ������ �� ���������
{1275, 23, 570.5000,874.9000,-43.5000, 0, "[ ������ ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//0
{1275, 23, -253.5860,2596.9019,62.8582, 0,  "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//1 //��� �����������
{1275, 23, -105.2947,-1264.2655,3.1635, 0,  "[ ����������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//2 //��� �������������
{1275, 23, -1216.0327,-1055.8462,128.7905, 0, "[ ������ ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//3
{1275, 23, 756.6287,8.5151,1000.7009, MAX_HOUSE+63, "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//4
{1275, 23, 754.7563,-40.2664,1000.5859, MAX_HOUSE+64, "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//5
{1275, 23, 758.0054,-77.7364,1000.6500, MAX_HOUSE+65, "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//6
{1239, 23, -29.3382,-270.6810,5.4429, 0, "[ ������������ ]\n{CFD9FF}������ �� ������", 0xCFD9FFAA, 30.0, 1},//7
{1275, 23, 2200.1199,-1970.2765,13.7841, 0, "[ �������� ���������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//8
//------------------------------------------------------------------------------
{1275, 23, 2744.1611,-2453.8428,13.8623, 0, "[ ������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//9
//{1274, 23, 2127.5701,-2275.1938,20.6719, 0, "[ ������� ]\n{C4FF51}�����", 0xCFD9FFAA, 30.0, 1},//10 ��� ���������
{1212, 23, 2700.2095,-2438.2773,1013.7231, 81+MAX_HOUSE, "[ ������� ]\n{C4FF51}�����", 0xCFD9FFAA, 30.0, 1},//10 ��� ��������� //2700.2095,-2438.2773,1013.7231,86.6173
{1239, 23, 2725.4158,-2416.6150,13.6277, 0, "[ ������� ]\n{CFD9FF}������ �� ������", 0xCFD9FFAA, 30.0, 1},//11 ��� ���������
{1220, 23, 2813.5637,-2464.8813,13.8558, 0, "none", -1, 0.0, 1},//12//LS ��� ��������� ������� �� �������
{1220, 23, 2797.0952,-2427.0461,13.6314, 0, "none", -1, 0.0, 1},//13//LS ��� ��������� ������� �� ��������
//------------------------------------------------------------------------------
{1275, 23, -537.1129,-78.4571,62.8672, 0, "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//14
{1275, 23, -2026.2488,67.1534,28.6916, 0, "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 40.0, 1},//15
//==============================================================================
//{1275, 23, 254.4151,79.1228,1003.6406, POLICE_LS_WORLD,  "[ ������� LS ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0}, //�� �������
//{1275, 23, 236.2644,120.0462,1003.2188, POLICE_SF_WORLD,  "[ ������� SF ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0}, //�� �������
//{1275, 23, 215.6492,182.4046,1003.0313, POLICE_LV_WORLD,  "[ ������� LV ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0}, //�� �������
{1275, 23, 330.0488,-312.5763,1024.6902, POLICE_LS_WORLD,  "[ ������� LS ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//16 //�� �������
{1275, 23, 236.2644,120.0462,1003.2188, POLICE_SF_WORLD,  "[ ������� SF ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//17 //�� �������
{1275, 23, 215.6492,182.4046,1003.0313, POLICE_LV_WORLD,  "[ ������� LV ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//18 //�� �������

{1275, 23, -2466.3848,513.0441,54.5687, FBI_SF_WORLD1,  "[ FBI ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//19 //���
{1275, 23, 216.2147,1937.9592,13.9359, DoD,  "[ NG ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},// NG duty
{1275, 23, -1349.3029,500.9380,18.2344, 0,  "[ ��� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},// NG duty
{1275, 23, 1165.7561,1353.2611,10.9219, -1,  "[ ����� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//������
{1275, 23, 355.0240,212.9054,1008.3828, DoJ,  "[ ���������� SF ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//���������� SF
{1275, 23, 1462.1010,-1750.6566,106.1200, MAX_HOUSE+MAX_BIZ+DoJ,  "[ ���������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 1},//���������� LS
{1275, 23, 2161.7534,1606.5365,999.9727, MAX_HOUSE+MAX_BIZ+SAN,  "[ �������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//���������
{1275, 23, -2036.0894,-116.7846,1035.1719, MAX_HOUSE+MAX_BIZ+DoE,  "[ ���������� ]\n{C4FF51}����������", 0xCFD9FFAA, 80.0, 0},//26 //���������

//------------------------------------------------------------------------------
//6 ��� ��������� ������
{1275, 23, 181.4370,-88.0596,1002.0234, -1, "none", -1, 0.0, 1},//27 //����� ������ �������� Zip
{1275, 23, 215.7261,-155.5914,1000.5234, -1, "none", -1, 0.0, 1}, //����� ������ �������� Didier Sachs
//{1275, 23, 217.4765,-98.6483,1005.2578, -1, "none", -1, 0.0, 1}, //����� ������ �������� Binco
{1275, 23, 218.6470,-98.5617,1005.2578, -1, "none", -1, 0.0, 1}, //����� ������ �������� Binco
{1275, 23, 214.3295,-41.4755,1002.0234, -1, "none", -1, 0.0, 1}, //����� ������ �������� SubUrban
{1275, 23, 199.8198,-127.5023,1003.5152, -1, "none", -1, 0.0, 1}, //����� ������ �������� ProLaps
{1275, 23, 258.8886,-41.5371,1002.0234, -1, "none", -1, 0.0, 1},//32 //����� ������ �������� ProLaps

{1239, 23, 2219.3604,-1154.4863,26.2266, 0, "[ ������ ��� �������� ]\n{CFD9FF}���������", 0xCFD9FFAA, 30.0, 0},//33
{1559, 23, 254.3039,-41.5549,1002.2234, -1, "Clothes {FF0000}[EXIT]", 0xBFF600FF, 60.0, 0},//Clothes Exit int14 //��� ����������
//------------------------------------------------------------------------------
//6 ������
{1241, 23, 1389.1354,-4.9561,1000.9175, MEDIC_LS_WORLD1, "none", -1, 0.0, 1},//35 //INT_MEDIC_LS
{1241, 23, 1389.1354,-4.9561,1000.9175, MEDIC_SF_WORLD1, "none", -1, 0.0, 1}, //INT_MEDIC_SF
{1241, 23, 1389.1354,-4.9561,1000.9175, MEDIC_LV_WORLD1, "none", -1, 0.0, 1}, //INT_MEDIC_LV
//{1241, 23, 2029.5945,-1404.6426,17.2512, 0, "none", -1, 0.0, 1},//34 //Hospital pill LS near speedway
{1241, 23, -22.6617,1860.2069,17.6476, MCSA_LS_WORLD1, "none", -1, 0.0, 1},//38 //Hospital pill LS near speedway

//{1241, 23, 1174.3177,1350.9894,10.9219, 0, "none", -1, 0.0, 1}, //Hospital pill
{1241, 23, 217.8277,1855.0547,12.9288, 0, "none", -1, 0.0, 1},//39 //Hospital Area51 pill
{1241, 23, -2203.3616,-2310.0723,31.3750, 0, "none", -1, 0.0, 1}, //Angel Pine Medical Center pill
{1241, 23, -1514.8284, 2519.9355,55.9960, 0, "none", -1, 0.0, 1}, //Medical Center El Quebrados pill
{1241, 23, -320.1530,1049.2471,20.3403, 0, "none", -1, 0.0, 1},//42 //Fort Carson Medical Center pill
//------------------------------------------------------------------------------
{1279, 23, 113.8925,1874.9440,17.8359, 0, "none", -1, 0.0, 1},//43// ����� ��� ��������� �����
{1247, 23, 338.2149,-317.9557,1024.6765, 0, "��������� �������� �� ������", 0xCFD9FFAA, 30.0, 0},// ����� ������� �������� lspd

//4 ����������
{1239, 23, -1663.8074,1207.7589,7.2546, 0, "AutoSalon", -1, 0.0, 1},//45 //AutoSalon
{1239, 23, 415.6489,2533.6672,19.1484, 0, "AutoSalon", -1, 0.0, 1}, //AutoSalon �� ����������� ����
//{1239, 23, -2188.1199,2415.8857,5.1563, 0, "AutoSalon", -1, 0.0, 1},//AutoSalon �� �������� �������
{1239, 23, 718.5229,-1476.4646,5.4688, 0, "AutoSalon", -1, 0.0, 1},//AutoSalon �� �������� ������� 

{2894, 23, 275.0578,1872.7856,8.7649, 0, "none", -1, 0.0, 1},//48 //��� ������ ��� �����

//8 ��� ������� ������
{1239, 19, 1381.0413,-1088.8511,27.3906, 0, "Bill Board", -1, 0.0, 1},//49 //Bill Board {old Job Department)
{1239, 19, 373.3568,183.6583,1008.3828, 0, "������������� �����", -1, 0.0, 1},//�������������
{1239, 19, 2164.0403,-103.3415,2.7500, 0, "��� ������", -1, 0.0, 1},//����
{1239, 23, -1439.7546,-2100.7080,-6.6824, 0, "Shady Creeek", 0xCFD9FFAA, 80.0, 1}, //Shady Creeek
//{1239, 23, 359.9126,-2032.1475,7.8359, 0, "none", -1, 0.0, 1}, //Feris Wheel
{1239, 23, 2005.7971,-37.1993,1.2597, 0, "C������� �����", 0xCFD9FFAA, 80.0, 1}, //Fisher's Lagoon �������� �����
{1239, 23, 2101.6453,-104.7360,2.2753, 0, "��������� �����", 0xCFD9FFAA, 80.0, 1}, //Fisher's Lagoon ��������� �����
{1239, 23, 2053.2734,-251.4215,2.1429, 0, "����� �����", 0xCFD9FFAA, 80.0, 1}, //Fisher's Lagoon ����� �����
{1239, 23, 1896.5764,-112.1714,16.9377, 0, "�������� �����", 0xCFD9FFAA, 80.0, 1}, //56//Fisher's Lagoon �������� �����

//3
{2894, 19, 2164.4080,1600.1506,999.977, 0, "�������� ������", -1, 0.0, 1},//57 //����� ��� ��������� �����
//{1239, 2, -2050.8962,460.0262,35.1719, 0, "none", -1, 0.0, 1}, //����� ��� ������ �����
//{3096, 23, -126.7453,-1264.7269,3.7841, 0, "none", -1, 0.0, 1}, //��� ������������� � ����������
{1239, 23, -1816.4215,585.4880,35.2703, 0, "none", -1, 0.0, 1}, // /lift
{1239, 23, -1816.3951,585.4965,235.6703, 0, "none", -1, 0.0, 1}, //59    /lift

//10 ��� �������� �������
{19134, 23, 2118.6191,2416.6548,11.0203, 0, "[ Level 1 ]", 0xBFF600FF, 60.0, 1},//60//Level 1
{19130, 23, 2118.6228,2416.6250,15.1172, 0, "[ Level 2 ]", 0xBFF600FF, 60.0, 1},
{19605, 23, 2118.6272,2416.6191,19.4219, 0, "[ Level 3 ]", 0xBFF600FF, 60.0, 1},
{19606, 23, 2118.6274,2416.7107,23.7188, 0, "[ Level 4 ]", 0xBFF600FF, 60.0, 1},
{19607, 23, 2118.6260,2416.6655,28.0234, 0, "[ Level 5 ]", 0xBFF600FF, 60.0, 1},
{19902, 23, 2118.5996,2416.6738,32.3203, 0, "[ Level 6 ]", 0xBFF600FF, 60.0, 1},
{19902, 23, 2118.6252,2416.6750,36.6172, 0, "[ Level 7 ]", 0xBFF600FF, 60.0, 1},//19945 ����� ������� �������, ������ 2 ����� ��������
{19902, 23, 2118.6274,2416.6843,40.9219, 0, "[ Level 8 ]", 0xBFF600FF, 60.0, 1},
{19902, 23, 2118.6245,2416.7009,45.2188, 0, "[ Level 9 ]", 0xBFF600FF, 60.0, 1},
{19133, 23, 2118.6169,2416.6995,49.5234, 0, "[ Level 10 ]", 0xBFF600FF, 60.0, 1},//69//Level 10
//{1559, 23, 2117.0286,2416.7971,60.5169, "none", -1, 0.0, 1},

//���� � ���
//{19134, 23, -2500.6821,526.4040,2556.0002, 9, "FBI ��������", 0xBFF600FF, 60.0, 0},//65 //int24 // ����� ����� ��������
//{19135, 23, -2485.6914,527.7474,1054.7067, 10, "FBI ��������� ����", 0xBFF600FF, 60.0, 0},//int20  // ����� ����� 0 ����
//{19135, 23, -2485.8547,527.7435,54.7067, 11, "FBI ������ ����", 0xBFF600FF, 60.0, 0},//int21 // ����� ����� 1 ����
//{1318, 23, -2486.2859,527.7953,74.7067, 12, "FBI ������ ����", 0xBFF600FF, 60.0, 0},//int22  // ����� ����� 2 ����
{19134, 23, PICKUP_FBI_PARK, FBI_SF_PARK, "FBI ��������", 0xBFF600FF, 60.0, 0},//70 //int24 // ����� ����� ��������
{19135, 23, PICKUP_FBI_0, FBI_SF_WORLD0, "FBI ��������� ����", 0xBFF600FF, 60.0, 0},//int20  // ����� ����� 0 ����
{19135, 23, PICKUP_FBI_1, FBI_SF_WORLD1, "FBI ������ ����", 0xBFF600FF, 60.0, 0},//int21 // ����� ����� 1 ����
{1318, 23, PICKUP_FBI_2, FBI_SF_WORLD2, "FBI ������ ����", 0xBFF600FF, 60.0, 0},//int22  // ����� ����� 2 ����

//{516, "FBI Level 0", -2500.6821,526.4040,2556.0002, 0.0, 			0,-2485.7607,527.6843,1054.7067, 0.0,	0,0,0},// ����� ����� �������� - ����� ����� 0 ����
//{21, "FBI Level 1", -2486.0420,527.7905,54.7067, 0.0, 				0,-2486.0864,528.1338,74.7067, 0.0,	0,0,0},// ����� ����� 1 ���� - ����� ����� 2 ����
//{517, "FBI Level 2", -2485.7607,527.6843,1054.7067, 0.0, 			0,-2486.0420,527.7905,54.7067, 0.0,	0,0,0},// ����� ����� 0 ���� - ����� ����� 1 ����

{19134, 23, 1492.3281,-1756.6941,2106.2101, DOJ_LS_WORLD1, "FLOOR 1", 0xBFF600FF, 60.0, 1},//74//vw2 //69
{19135, 23, 1485.7433,-1748.6017,106.1200, DOJ_LS_WORLD2, "FLOOR 2", 0xBFF600FF, 60.0, 1},//vw7
{1318, 23, 1490.9055,-1753.7274,106.1200, DOJ_LS_WORLD3, "FLOOR 3", 0xBFF600FF, 60.0, 1},//vw5
//------------------------------------------------------------------------------

//
{1279, 19, 323.0342,1118.5804,1083.8828, 0, "none", -1, 0.0, 1},//77 //Getting Drugs for DrugDealers int5
{1210, 19, -684.9224,939.5638,13.6328, 0, "Hitman Agency", -1, 0.0, 1},// Hitman Agency entrance ��������
//{1220, 19, 960.9897,2099.9397,1011.0253, "none", -1, 0.0, 1},//Materials Package building �������� �������
//{1220, 19, 2419.8484,2778.5667,10.8203, "none", -1, 0.0, 1},//Materials Package building �������� �������
{1220, 19, 246.2071,1825.1620,7.5547, 0, "none", -1, 0.0, 1},//Materials Package building �������� �������
{1221, 19, -2185.6946,-262.7819,40.7195, 0, "none", -1, 0.0, 1},//Factory Package building �������� �������

{1220, 19, 2259.0122,-70.9235,31.6016, 0, "none", -1, 0.0, 1},//81//��� �������������
{1221, 19, 1489.18,-1720.06,8.24, 0, "none", -1, 0.0, 1},//��� �������������

//{1220, 19, -2112.6499,-2407.2903,31.30601, "none", -1, 0.0, 1},//Angel Pine REPAIR_ROAD
//{1220, 19, 2563.7883,789.9964,10.9545, "none", -1, 0.0, 1},//LV REPAIR_ROAD
//{1220, 19, 2730.5715,-2451.3306,17.5937, "none", -1, 0.0, 1},//LS REPAIR_ROAD
{1220, 19, 214.4123,-230.1332,1.5581, 0, "Blueberry", -1, 0.0, 1},//83//Blueberry truck terminal

{371, 15, 1536.0,-1360.0,1150.0, 0, "none", -1, 0.0, 1},//84//������� LS towertop ��� ������� /skydive � �.�.
{371, 2, 1541.5859,-1366.8794,326.2109, 0, "none", -1, 0.0, 1},//������� LS towertop
{371, 2, 1541.6334,-1364.3872,326.2109, 0, "none", -1, 0.0, 1},//������� LS towertop
{371, 15, -1778.4277,577.2136,234.8906, 0, "none", -1, 0.0, 1},//������� SF towertop
{371, 2, -1804.4526,526.4271,234.8906, 0, "none", -1, 0.0, 1},//������� SF towertop
{371, 2, -1835.7421,572.0619,234.8874, 0, "none", -1, 0.0, 1},//������� SF towertop
{371, 2, 319.3416, 1020.7169,1950.6696, 0, "none", -1, 0.0, 1},// Parachutes in plane
{371, 15, 312.6138, 1020.7346,1950.6655, 0, "none", -1, 0.0, 1},//91// Parachutes in plane

{1240, 2, 279.3000,1853.5619,8.7649, 0, "none", -1, 0.0, 1},//92//������ �������� area51 ��� �����
{1240, 2, 211.2388,1808.9071,21.8672, 0, "none", -1, 0.0, 1},//������ �������� �� ������
{1240, 2, 2788.4929,-2436.3022,13.7721, 0, "none", -1, 0.0, 1},//������ �������� � �����

{1316, 23, 315.8682,1038.4993,1943.7225, 0, "none", -1, 0.0, -1}//95 //1316 ����� �� ��������� ������ ��� ������� /jump ��� �������


//{1239, 23, 2788.4929,-2436.3022,13.7721},//LOS_SANTOS 13.6335
//{1239, 23, -1831.2034,1407.7167,7.3070},//SAN_FIERRO
//{1239, 23, 1087.2208,1889.5250,10.9336},//LAS_VENTURAS
//{1239, 23, -535.5635,-543.7636,25.6448}//RED_COUNTY
//�����

//1277 - save disk 52 ��.
/*
{1277, 23, 248.3686,302.3440,999.1484, 0},
{1277, 23, 0.2169,3.6012,999.4284, 0},
{1277, 23, 272.7188,306.3148,999.1484, 0},
{1277, 23, 348.4954,306.0431,999.1484, 0},
{1277, 23, 416.1391,2536.8928,10.0000, 0},
{1277, 23, 1523.8143,-44.7454,1002.1310, 0},
{1277, 23, 329.7103,1489.7341,1084.4449, 0},
{1277, 23, 308.9582,307.0134,1003.3047, 0},
{1277, 23, 447.9183,512.4609,1001.4195, 0},
{1277, 23, 374.0598,1471.6753,1080.1875, 0},
{1277, 23, 220.3442,1157.5728,1082.6094, 0},
{1277, 23, -276.3099,1456.8099,1084.3672, 0},
{1277, 23, -68.8125,1364.2991,1080.2109, 0},
{1277, 23, 263.7795,1248.5276,1084.2578, 0},
{1277, 23, 754.5298,1437.9575,1102.7031, 0},
{1277, 23, 360.8032,1416.4154,1081.3356, 0},
{1277, 23, 225.7645,1292.7719,1082.1406, 0},
{1277, 23, -295.0881,1471.1898,1088.8750, 0},
{1277, 23, 2247.9729,-1136.1852,1050.6328, 0},
{1277, 23, 2263.9006,-1137.3846,1050.6328, 0},
{1277, 23, 437.8639,1409.0885,1084.3047, 0},
{1277, 23, 290.6292,1480.8833,1080.2578, 0},
{1277, 23, 489.3175,1402.8656,1084.4146, 0},
{1277, 23, 237.3879,1119.0466,1080.9922, 0},
{1277, 23, 230.5683,1048.4950,1084.0132, 0},
{1277, 23, -49.5355,1407.9819,1084.4297, 0},
{1277, 23, 2451.8784,-1701.7177,1014.0477, 0},
{1277, 23, 2181.9272,1622.3801,1043.4034, 0},
{1277, 23, 1527.3280,-12.0935,1002.0971, 0},
{1277, 23, 512.8957,-17.8899,1001.5653, 0},
{1277, 23, 231.1781,1246.7787,1082.1406, 0},
{1277, 23, 266.2554,1292.5088,1080.2578, 0},
{1277, 23, 28.7638,1342.1178,1088.8750, 0},
{1277, 23, 2534.9082,-1679.3743,1015.4986, 0},
{1277, 23, 29.8312,1405.8163,1084.4297, 0},
{1277, 23, 232.7386,1191.0868,1084.4135, 0},
{1277, 23, 151.3013,1371.7556,1083.8594, 0},
{1277, 23, 84.7224,1333.7493,1088.3667, 0},
{1277, 23, 233.6086,1072.0833,1084.1943, 0},
{1277, 23, 2345.8171,-1174.7892,1027.9834, 0},
{1277, 23, 2319.2654,-1210.3323,1049.0234, 0},
{1277, 23, 2206.2063,-1075.1625,1050.4844, 0},
{1277, 23, 2233.1362,-1106.7572,1050.8828, 0},
{1277, 23, 2333.2166,-1064.6560,1049.0234, 0},
{1277, 23, 2237.3833,-1069.9404,1049.0234, 0},
{1277, 23, 2278.5471,-1139.5052,1050.8984, 0},
{1277, 23, 2495.8401,-1708.4146,1014.7422, 0},
{1277, 23, 2366.3479,-1122.3223,1050.8750, 0},
{1277, 23, 2250.1536,-1209.1912,1049.0234, 0},
{1277, 23, 2319.5483,-1014.8467,1054.7153, 0},
{1277, 23, 2324.4927,-1141.7772,1050.9835, 0},
{1277, 23, 2184.1284,-1206.0503,1049.0234, 0}
*/
};


stock IsAtHospitalPill(playerid)//���������� 1 ���� ����� ����� ������
{
	if(IsPlayerInRangeOfPoint(playerid, 2.1, 1389.1354,-4.9561,1000.9175)) { return MEDIC_LS_WORLD1; }//Hospital pill
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 1389.1354,-4.9561,1000.9175)) { return MEDIC_SF_WORLD1; }//Hospital pill
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 1389.1354,-4.9561,1000.9175)) { return MEDIC_LV_WORLD1; }//Hospital pill
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, -22.6617,1860.2069,17.6476)) { return MCSA_LS_WORLD1; }//Hospital LS near speedway

	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 217.8277,1855.0547,12.9288))  return 5;//Hospital Area51
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, -2203.3616,-2310.0723,31.3750))  return 6;//Angel Pine Medical Center pill
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, -1514.8284, 2519.9355,55.9960))  return 7;//El Quebrados Medical Center  pill
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, -320.1530,1049.2471,20.3403))  return 8;//Fort Carson Medical Center pill
	return 0;
}

//������� ��������� �������





/*
Weapon pickups
321 - Regular Dildo
322 - White Dildo
323 - Vibrator
324 - Another Vibrator
325 - Flowers
326 - Cane
330 - CJ's Phone
331 - Brass Knuckles
333 - Golf Club
334 - Police Trungeon/Night Stick (Depending on where you're from)
335 - Combat Knife
336 - Baseball Bat
337 - Shovel
338 - Pool Cue
339 - Katana
341 - Chainsaw
342 - Frag Grenade
343 - Tear Gas Grenade
344 - Molotov Cocktail
346 - Colt 45 Pistol
347 - Silenced Colt 45 Pistol
348 - Desert Eagle
349 - Regular Shotgun
350 - Sawn-Off Shotgun
351 - SPAZ-12 Shotgun
352 - Mac-10 (Or Micro-UZI)
353 - MP5
354 - Hydra Flare(������� ���������� ������)
355 - AK47 Assault Rifle
356 - M4 Assault Rifle
357 - Country Rifle
358 - Sniper Rifle
359 - Rocket Launcher
360 - Heat Seeking Rocket Launcher
361 - Flamethrower(�������)
362 - Minigun
363 - Satchel Charges
364 - Detonator <---- Seemingly Useless.
365 - Spray Paint Can(��������)
366 - Fire Extinguisher(������������)
367 - Camera(����������)
368 - Night Vision Goggles(������ ������� �������)
369 - Infra-Red Goggles(����������)
370 - Jetpack
371 - Parachute
372 - Tec-9

Pickup model ID's
1210 - Briefcase(��������)
1212 - Money(������� �����)
1239 - Information(������ i)
1240 - Heart(������)
1241 - Adrenaline pill(������)
1242 - Armor(����������)
1247 - Bribe(������, ������)
1248 - Gta 3 logo
1252 - Grey bomb(2 ������ � �����������)
1253 - Photo Op(����� ��������� - �������)
1254 - rampage(�����)
1269 - ����� ���������� ������
1270 - ������� ���������� ������
1272 - blue house
1273 - green house
1274 - dollar
1275 - blue t-shirt(����� ��������)
1276 - tiki(��������)
1277 - save disk(��������)
1279 - drug bundle(����� ����������)
1313 - 2 skulls icon (2 ������)
1314 - 2 player
1316 - Corona (�������������� ������)
1317 - Checkpoint (��������� ������)
1318 - White arrow (����� ������� ��������� ����)
1559 - Interior enter/exit diamond
1582 - Pizza Box(������� � ������)
2894 - Madd Dogg's rhyme book (����� ���� Madd Dogg�)
 */
/*
Available Pickup Types
 0 The pickup does not display. �� �����������, �� ������������.
 1 Not pickupable, exists all the time. �� �����������, ���������� ��� �����.(Suitable for completely scripted pickups using OnPlayerPickUpPickup)
 2 Pickupable, respawns after some time.  �����������, ����������� ����� 30 ���. �������. ������
 3 Pickupable, respawns after death. �����������, ���������, ���������� ��� ��������� � �����
 4 Disappears shortly after created (perhaps for weapon drops?) �������� ������ ����� ��������
 5 Disappears shortly after created (perhaps for weapon drops?) �������� ������ ����� ��������
 8 Pickupable, but has no effect. Disappears automatically. �����������, ���������, ���������� ��� ��������� � �����
//9 - ������ ������ � ������, �� ����������
//10 - ������ ������ � ������, �� ����������
 11 Blows up a few seconds after being created (bombs?) ���������� ����� 10 ������ ����� ����, ��� ��������
 12 Blows up a few seconds after being created. ���������� ����� 10 ������ ����� ����, ��� ��������
 13 Slowly decends to the ground. �������� ������ �� �����, �� ���������� (���������, � ������ ��� �����)
 14 Pickupable, but only when in a vehicle. ����������� ������ ����� � ������, �� �� ��������. Falls through objects made with CreateObjectEx, etc.
 15 Pickupable, respawns after death. �����������, ���������, ���������� ����� ������ (��� ��������� � �����)
//16-18 - �� ������.
 19 Pickupable, but has no effect (information icons) �����������, ���������, ���������� ��� ��������� � �����
//20,21 - �� ������.
 22 Pickupable, respawns after death. �����������, ���������, ���������� ����� ������ (��� ��������� � �����)
 23 Pickupable, but doesn't disappear on pickup. �����������, �� �� ��������.

 //��������!!!: ��� ����������� ������ ����������� ID, �.�. ������� �� �� ����
*/


//==============================================================================
stock pickup_OnGameModeInit()
{
	new time = GetTickCount();
	//==========================================================================
	for(new pic = 0; pic < MAX_PLAYER_PICKUPS; pic++)
	{   //��� ��������� ������� �� ����������� � ��
		if(PlayerPickups[pic][p_model] != -1)
		{
		    /*if(PlayerPickups[pic][p_model] == 19902 || (PlayerPickups[pic][p_model] >= 19605 && PlayerPickups[pic][p_model] <= 19607))
			{
		    	PickupID[pic] = SetPickupEx(PlayerPickups[pic][p_model], PlayerPickups[pic][p_type],
					PlayerPickups[pic][p_x], PlayerPickups[pic][p_y], PlayerPickups[pic][p_z], PlayerPickups[pic][p_v]);
			}
			else {*/
			PickupID[pic] = SetPickupEx(PlayerPickups[pic][p_model], PlayerPickups[pic][p_type],
				PlayerPickups[pic][p_x], PlayerPickups[pic][p_y], PlayerPickups[pic][p_z], PlayerPickups[pic][p_v]);
			//}

		}
		if(PlayerPickups[pic][lColor] != -1)
		{//������������� 3������ ������ ��� ������� � ������� �������� ���� � �����
			Text3DPickupID[pic] = Create3DTextLabelEx(PlayerPickups[pic][lText],
				PlayerPickups[pic][lColor], PlayerPickups[pic][p_x], PlayerPickups[pic][p_y], PlayerPickups[pic][p_z]+0.75,
				PlayerPickups[pic][lDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, PlayerPickups[pic][lLos], PlayerPickups[pic][p_v]);
		}
	}//143-205=62
	//==========================================================================
//��� ��������� ������ �������� ����� �� ���� �������
	new pic = MAX_VEHICLE_PICKUPS-1;
	SetPickupEx(VehiclePickups[pic][p_model], VehiclePickups[pic][p_type], VehiclePickups[pic][p_x], VehiclePickups[pic][p_y], VehiclePickups[pic][p_z]);
	Text3DPickupID[pic] = Create3DTextLabelEx("[ ���������� ���� ]", 0xAAAAFFFF,
		VehiclePickups[pic][p_x], VehiclePickups[pic][p_y], VehiclePickups[pic][p_z]+1.75, 130.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);

//��� ����� BloodBowl
	new rand = random(sizeof(RepairPickups));
	PickupID[MAX_PLAYER_PICKUPS] = SetPickupEx(RepairPickups[rand][dp_model], RepairPickups[rand][dp_type], RepairPickups[rand][dp_x],RepairPickups[rand][dp_y],RepairPickups[rand][dp_z],15);

	printf("19/19. [�������� �������[3D�������]]: ���� ��������� - %d[%d], ��������� - %d (ms)", PickupCounter, Counter3DText, GetTickCount() - time);//new time = GetTickCount();
}


stock pickup_OnPlayerConnect(playerid)
{
	PickUpPickup[playerid][picID] = -1;
	//PickupsInstalled[playerid] = 999;//��� ��������� �������
}

//stock PlayerEnterPickups(playerid, pickupid)
stock pickup_OnPlayerPickUpPickup(playerid, pickupid)
{
//��� �������� ����������� OnPlayerLeavePickUp
	if(PickUpPickup[playerid][picID] != -1) return 1;// && pickupid != 0
	PickUpPickup[playerid][picID] = pickupid;
	if(IsPlayerInAnyVehicle(playerid))
	{
	    GetVehiclePos(GetPlayerVehicleID(playerid), PickUpPickup[playerid][picX], PickUpPickup[playerid][picY], PickUpPickup[playerid][picZ]);
	}
	else GetPlayerPos(playerid, PickUpPickup[playerid][picX], PickUpPickup[playerid][picY], PickUpPickup[playerid][picZ]);
//==============================================================================
    new curstate = GetPlayerState(playerid);
    if(curstate == PLAYER_STATE_ONFOOT)
    {//p_type: = 14
		PlayerEnterPickUp(playerid, pickupid);//�������� ������ �� �����
		interior_OnPlayerPickUp(playerid, pickupid);
	}
    else if(curstate == PLAYER_STATE_DRIVER)
    {
		VehicleEnterPickUp(playerid, pickupid);//�������� ������ ���� � �����
		//interior_OnPlayerPickUp(playerid, pickupid);
	}
	return 1;
}

stock AntiRepetitionMenuPrepare(playerid)
//stock prop_OneSecondTimers2(playerid)
{   //���������� �� OneSecondTimers2
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return 1; }
	if(	//!IsPlayerInRangeOfPoint(playerid, 2.1,  HouseInfo[house][hEntranceX], HouseInfo[house][hEntranceY], HouseInfo[house][hEntranceZ]) &&
		gDialogStatus[playerid][0] > 0)
	{   //���� ������� ����������� � ����� �� ��������� � 6 ������ �� ����� � ���
		gDialogStatus[playerid][0] --;
	}
	else if(//!IsPlayerInRangeOfPoint(playerid, 2.1, BizInfo[bouse][bEntranceX], BizInfo[bouse][bEntranceY], BizInfo[bouse][bEntranceZ]) &&
		gDialogStatus[playerid][1] > 0)
	{
		gDialogStatus[playerid][1] --;
	}
	else if(//!IsPlayerInRangeOfPoint(playerid, 2.1, SBizInfo[sbouse][sbEntranceX], SBizInfo[sbouse][sbEntranceY], SBizInfo[sbouse][sbEntranceZ]) &&
		gDialogStatus[playerid][2] > 0)
	{
		gDialogStatus[playerid][2] --;
	}
	return 1;
}
//stock OnPlayerPickupTimer(playerid)
stock pickup_OneSecondTimers2(playerid)
{   //��� �������� ����� � ����� ���� �� ������ //����������� ������ �������.
	AntiRepetitionMenuPrepare(playerid);
	//==========================================================================
   	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
   	{//������� ����� ��������
		trucker_SendBuySale(playerid);//��� �������������� STEP0
	}
	//==========================================================================
	if(PickUpPickup[playerid][picID] == -1) { return 1; }
	if(	!IsPlayerInRangeOfPoint(playerid, 2.1, PickUpPickup[playerid][picX], PickUpPickup[playerid][picY], PickUpPickup[playerid][picZ]) )
	{//��� �������� ����������� OnPlayerLeavePickUp
		OnPlayerLeavePickUp(playerid, PickUpPickup[playerid][picID]);
		PickUpPickup[playerid][picID] = -1;
	}
	return 1;
}//End OnPlayerPickupTimer(playerid)()





//##############################################################################//
//                                                                              //
//                             ������������� �������                            //
//                                                                              //
//##############################################################################//
//�-�� ������� �� ����� ����� Ex, ������ ������� ����� ���������������� ����������

/*stock AddStaticPickupEx(model,type,Float:spawn_x,Float:spawn_y,Float:spawn_z, virtualworld=0)
{   //�� ���������� �� ������ ��� ������������ //�� ������ ID ������
	//if(virtualworld == 0)
	//AddStaticPickup(model,type,spawn_x,spawn_y,spawn_z, -1);//����� ����� ��� ���� ����������� �����.
	//else
	//AddStaticPickup(model,type,spawn_x,spawn_y,spawn_z, virtualworld);//������� ������ � ��������� ���� ����
	CreateDynamicPickup(model,type,spawn_x,spawn_y,spawn_z, virtualworld);
	//pickupModel[PickupCounter] = model;
	PickupCounter ++;
}*/
stock SetPickupEx(model, type, Float:spawn_x,Float:spawn_y,Float:spawn_z, virtualworld=0)
{
	if(spawn_x == 0.0 && spawn_y == 0.0) return 0;
	if(spawn_x >= 4096.0 || spawn_y >= 4096.0 || spawn_x <= -4096.0 || spawn_y <= -4096.0 ) return 0;

	//new pickupid = CreatePickup(model,type,spawn_x,spawn_y,spawn_z, virtualworld);//�� ������ ID ������
	new pickupid = CreateDynamicPickup(model,type,spawn_x,spawn_y,spawn_z, virtualworld);//������ ����� � �������������� ������
 	//CreateDynamicPickup(modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_PICKUP_SD, areaid = -1, priority = 0)
	//Pickups[pickupid][p_ID] = pickupid;//�� ������������ �.�. ��� ������ ������ ���� ������, ����� �� ������ ������� ������ ���� �������
	Pickups[pickupid][p_model] = model;
	Pickups[pickupid][p_type] = type;
	Pickups[pickupid][p_x] = spawn_x;
	Pickups[pickupid][p_y] = spawn_y;
	Pickups[pickupid][p_z] = spawn_z;
	Pickups[pickupid][p_vw] = virtualworld;
	//pickupModel[PickupCounter] = model;
	PickupCounter ++;

	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "SetPickupEx: %d", pickupid);
	//SendClientMessageEx(playerid, COLOR_GREY, strings);
	//SendClientMessageToAll(COLOR_GREY, strings);
	return pickupid;
}
stock DestroyPickupEx(pickupid)
{
	//DestroyPickup(pickupid);
	DestroyDynamicPickup(pickupid);
	if(PickupCounter > 0) PickupCounter --;
}
