//https://gta.fandom.com/ru/wiki/%D0%A2%D1%80%D0%B8%D0%B0%D0%B4%D1%8B_%D0%A1%D0%B0%D0%BD-%D0%A4%D0%B8%D0%B5%D1%80%D1%80%D0%BE
//https://gta.fandom.com/ru/wiki/%D0%9A%D0%B0%D1%82%D0%B5%D0%B3%D0%BE%D1%80%D0%B8%D1%8F:%D0%91%D0%B0%D0%BD%D0%B4%D1%8B_%D0%B2_GTA_San_Andreas
#define MAX_FAMILY 21
enum fInfo
{
	NumberFamily,//номер банды NumberFamily
	fName[20],//название банды
	fMOTD[128],//приветствие в банде при заходе на сервер
	fColor,//[10],//цвет банды
	fLeader[MAX_PLAYER_NAME],//имя лидера банды
	fMembers,//кол-во членов в банде
	
	Float:fSpawns[4],//место спауна членов
	
	fInterior,//интерьер места спауна
	fWorld,//мир места спауна
	fLocal,//локация места спауна
	fBank,//общак банды
	fRank,//максимальный ранг для прокачки
	fAlliance,//[20],//с кем союз
	fWar,//[20],//с кем вражда
	fMaterial
};

new FamilyInfo[MAX_FAMILY][fInfo];/* = {
//ID	Name	MOTD	Leader	Members	SpawnX	SpawnY	SpawnZ	SpawnA	Int	World	Local	Bank	Rank	Alliance	War	Material
{TEAM_NONE,	"No-One","No-One",TEAM_NONE_COLOR,"No-One",0,			0.0, 0.0, 0.0, 0.0,		0,0,0,0,0,TEAM_NONE,TEAM_NONE,0},
{TEAM_GROVE,"Grove Street","Welcome to Grove Street",TEAM_GROVE_COLOR,"No-One",0,			1146.5,	-1989.0, 68.0, 41.0,		0,0,255,49278,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_BALLAS,"The Ballas","Welcome to the Ballas",TEAM_BALLAS_COLOR,"No-One",0,			2285.8,	2407.6,	11.8, 181.8,	0,0,255,600,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_AZTEC,"Varios Los Aztecas","Welcome to Varios Los Aztecas",TEAM_AZTECAS_COLOR,"No-One",0,		2242.3,	-1411.4, 24.0, 268.7,	0,0,255,0,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_VAGOS,"Los Santos Vagos","Welcome to Los Santos Vagos",TEAM_VAGOS_COLOR,"No-One",0,	1137, -1979.5, 22.0, 159.1,		0,0,255,149,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_NANG,	"Da Nang Boys","Welcome to Da Nang Boys",TEAM_NANG_COLOR,"No-One",0,			-2425, -418.7, 85.4, 325.7,		0,0,255,0,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_RIFA,	"San Fierro Rifa","Welcome to San Fierro Rifa",TEAM_RIFA_COLOR,"No-One",0,	1136.4,	-1992.5, 69.5, 190.8,	0,0,255,0,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_TRIAD,"The Traids","Welcome to the Traids",TEAM_TRIADS_COLOR,"No-One",0,				-2172, -4505, 35.0, 74.8,		0,0,255,19439,11,TEAM_NONE,TEAM_NONE,0},
{TEAM_BIKER,"Bikers","Welcome to the Bikers",TEAM_BIKERS_COLOR,"No-One",0,					1134.9,	-1994.3, 69.0, 133.3,	0,0,255,204129,3,0,0,10000},
{TEAM_MAFIA,"The Mafia","Welcome to the Mafia",TEAM_MAFIA_COLOR,"No-One",0,				-2040.5, -92.8, 35.0, 14.1,		0,0,255,22601,11,TEAM_NONE,TEAM_NONE,0},
{DoT,		"DoT","Welcome to the Department of Transport",COLOR_DARKTURQUOISE,"No-One",0,	1568, -1693.5, 5.9, 177.1,		0,0,255,392023,4,TEAM_NONE,TEAM_NONE,0},
{FBI,		"FBI","Welcome to the Federal Bureau of Investigation",COLOR_PALEPURPLE,"No-One",0,	-1604.8, 732.9, -5.0, 37.5,	0,0,255,1161934,4,TEAM_NONE,TEAM_NONE,0},
{DoD,		"DoD","Welcome to the Department of Defense",COLOR_EMERALD,"No-One",0,		283.2, 2036.9, 17.6, 176.6,		0,0,255,14018,11,0,0,501554},
{DoH,		"DoH","Welcome to the Department of Health",COLOR_MAUVE,"No-One",0,		-2656.0, 635.0, 14.5, 180.0,	0,202,202,9461275,5,TEAM_NONE,TEAM_NONE,0},
{TEAM_NONE,"No-One","No-One",TEAM_NONE_COLOR,"No-One",0,			0.0, 0.0, 0.0, 0.0,		0,0,0,0,0,TEAM_NONE,TEAM_NONE,0},
{LCN,		"LCN","Welcome to the La Cosa Nostra",COLOR_VIOLET,"No-One",0,			960.7, -53.9, 1001.0, 95.0,		3,0,243,1000495,11,TEAM_NONE,TEAM_NONE,0},
{Yakuza,	"Yakuza","Welcome to the Yakuza",COLOR_CERISE,"No-One",0,					-2158.1, 644.0, 1057.5, 93.5,	1,0,244,35171,11,0,0,111},
{DoJ,		"DoJ","Welcome to the Department of Justice",COLOR_HERBAL,"No-One",0,		346.7, 162.3, 1025.8, 90.0,		3,0,241,1282090,3,TEAM_NONE,TEAM_NONE,0},
{Hitman,	"Hitman","Welcome to the Hitman Agency",COLOR_BROWN,"No-One",0,			-688.0, 936.7, 13.6, 0.0,		0,0,0,0,11,TEAM_NONE,TEAM_NONE,0},
{SAN,		"SAN","Welcome to the San Andreas News",COLOR_LIGHTORANG,"No-One",0,			2164.0, 1605.0, 1000.0, 133.1,	1,249,249,2296919,11,TEAM_NONE,TEAM_NONE,0},
{DoE,		"DoE","Welcome to the Ministry Of Education",COLOR_LIGHTBROWN,"No-One",0,		-2032.5, -117.5, 1035, 275.1,	3,3,255,147181,9,TEAM_NONE,TEAM_NONE,0}
};*/
/*
//https://gta.fandom.com/ru/wiki/%D0%9A%D0%B0%D1%82%D0%B5%D0%B3%D0%BE%D1%80%D0%B8%D1%8F:%D0%91%D0%B0%D0%BD%D0%B4%D1%8B_%D0%B2_GTA_San_Andreas
enum fInfo
{
	FamilyTaken,//номер банды
	FamilyName[20],//название банды
	FamilyMOTD[128],//приветствие в банде при заходе на сервер
	FamilyColor[10],//цвет банды
	FamilyLeader[MAX_PLAYER_NAME+1],//имя лидера банды
	FamilyMembers,//кол-во членов в банде
	Float:FamilySpawn[4],//место спауна членов банды
	FamilyInterior,//интерьер места спауна
	FamilyBank//общак банды
};
new FamilyInfo[10][fInfo];
0,None,None,No-one,28509,0.0000,0.0000,0.0000,0.0000,13995,255
1,Grove Street,Welcome to Grove Street,No-one,0,307.1209,-1480.5461,24.5937,231.4125,0,62716
2,The Ballas,Welcome to the Ballas,No-one,0,1447.9637,-1094.0327,17.6702,282.8106,0,9750
3,Varios Los Aztecas,Welcome to Varios Los Aztecas,No-one,0,-2147.9582,255.0254,34.9692,268.3825,0,24995
4,Los Santos Vagos,Welcome to Los Santos Vagos,No-one,0,2583.3139,-953.3883,81.3889,191.5007,0,7851
5,Da Nang Boys,Welcome to Da Nang Boys,No-one,0,2107.2407,1005.0432,11.0381,177.2783,0,40271
6,San Fierro Rifa,Welcome to San Fierro Rifa,No-one,0,-1870.8016,-877.5139,31.8171,269.1607,0,30576
7,The Traids,Welcome to the Traids,No-one,0,1182.8253,-1319.3149,13.2487,44.8204,0,104667
8,Bikers,Welcome to the Bikers,No-one,0,682.7282,-476.3233,16.3358,176.6501,0,1932
9,The Mafia,Welcome to the Mafia,No-one,0,1971.5250,2420.6411,10.4062,268.5617,0,4456
*/
