
//##############################################################################//
//                                                                              //
//                     ИДЕНТИФИКАТОРЫ ОБРАБОТЧИКОВ СОБЫТИЙ                      //
//                                                                              //
//##############################################################################//
//идентификаторы обрыботчика который вызвал срабатывание OnPlayerInfoChange



//#define	GameModeInit			1
//#define	GameModeExit			2
//#define	FilterScriptInit		3
//#define	FilterScriptExit		4
#define	PlayerConnect    1
#define	PlayerDisconnect   2
#define	PlayerSpawn     3
#define	PlayerDeath     4
#define	VehicleSpawn    5
#define	VehicleDeath    6
#define	PlayerTxt     7
#define	PlayerCommandText   8
#define	PlayerRequestClass   9
#define	PlayerEnterVehicle   10
#define	PlayerExitVehicle   11
#define	PlayerStateChange   12
#define	PlayerEnterCheckpoint  13
#define	PlayerLeaveCheckpoint  14
#define	PlayerEnterRaceCheckpoint 15
#define	PlayerLeaveRaceCheckpoint 16
#define	RconCommand     17
#define	PlayerRequestSpawn   18
#define	ObjectMoved     19
#define	PlayerObjectMoved   20
#define	PlayerPickUpPickup   21
#define	VehicleMod     22
#define	EnterExitModShop   23
#define	VehiclePaintjob    24
#define	VehicleRespray    25
#define	VehicleDamageStatusUpdate 26
#define	UnoccupiedVehicleUpdate  27
#define	PlayerSelectedMenuRow  28
#define	PlayerExitedMenu   29
#define	PlayerInteriorChange  30
#define	PlayerKeyStateChange  31
#define	RconLoginAttempt   32
#define	PlayerUpdate    33
#define	PlayerStreamIn    34
#define	PlayerStreamOut    35
#define	VehicleStreamIn    36
#define	VehicleStreamOut   37
#define	ActorStreamIn    38
#define	ActorStreamOut    39
#define	DialogResponse    40
#define	PlayerTakeDamage   41
#define	PlayerGiveDamage   42
#define	PlayerGiveDamageActor  43
#define	PlayerClickMap    44
#define	PlayerClickTextDraw   45
#define	PlayerClickPlayerTextDraw 46
#define	IncomingConnection   47
#define	TrailerUpdate				48
#define	VehicleSirenStateChange     49
#define	PlayerClickPlayer			50
#define	PlayerEditObject			51
#define	PlayerEditAttachedObject	52
#define	PlayerWeaponShot			53
#define PlayerGiveMoney 			54
#define PlayerSelectObject          55
#define PlayerInfoChange    56
#define AllPublic 57
//кто вызвал OnPlayerInfoChange

#define	MAX_CALLBACK 60
new bool:CHECKING[MAX_CALLBACK] = {false, ...};//1- включит информирование по умолчанию, если будет выключен vw_checking



//##############################################################################//
//                                                                              //
//                            ОПРЕДЕЛЕНИЯ КОНСТАНТ                              //
//                                                                              //
//##############################################################################//
//не трогать
//#if defined MAX_PLAYERS
//	#undef MAX_PLAYERS
//#endif
//#define MAX_PLAYERS 470//170//100+16+4=120


//#if defined MAX_VEHICLES
//	#undef MAX_VEHICLES
//#endif
//#define MAX_VEHICLES 		2000//700//900



#define MAX_STRING			168 //128 + 5*8
new strings[MAX_STRING];

#define MAX_WEAPONS			46
#define MAX_SLOT_WEAPONS	13
#define MAX_PLAYER_ICONS 	99

#define FREEROAM 			999//MAX_HOUSE+MAX_BIZ+MAX_SBIZ+MAX_INT = 99+92+59

#define MAX_HOUSE 99//52//34
#define MAX_BIZ 92//84//82
#define MAX_SBIZ 59//51//17+19=36 +11=47

#define MAX_PLAYER_ICONS 	99//максимальное число одновременно отображаемых иконок

#define NOT_ZONES 			999

#define WEAPONSTATE_SHOOTING 	4
#define PLAYER_STATE_KILLED 	10
#define PLAYER_STATE_ENTER_INT 	11
#define PLAYER_STATE_ENTER_CP 	12
#define PLAYER_STATE_SURFING	13


#define CIVILIAN 			0
#define NOT_KEY 			255	//MAX_HOUSE+MAX_BIZ+MAX_SBIZ
#define MAX_PAPERNUMBER 	999
#define IsNotBeenIll 		255//нет медосмотра

//ID 	Body Part
//для  OnPlayerGiveDamage, OnPlayerTakeDamage
#define BODY_PART_TORSO 	3
#define BODY_PART_GROIN 	4
#define BODY_PART_LEFT_ARM 	5
#define BODY_PART_RIGHT_ARM 6
#define BODY_PART_LEFT_LEG 	7
#define BODY_PART_RIGHT_LEG 8
#define BODY_PART_HEAD 		9

//index SetPlayerAttachedObject
//The index of the object (0-9 in 0.3d). This is basically an ID.
#define OBJECT_SLOT         0//разные объекты
#define DUTY_SLOT 			1//объекты дающиеся при выходе на дежурство
//#define SEED_SLOT 		2//для фермеров //может быть только при выходе на дежурство
#define TAZER_SLOT          3//шокер может быть только при выходе на дежурство но во многих фракциях
//#define TRASHPACKET_SLOT	4//для мусорщиков //может быть только при выходе на дежурство
#define MOBILE_SLOT 		5//объект телефона
#define EAT_SLOT 			6//объекты еды
#define FIRE_OBJECT_SLOT	7//объект огня - если загорелся может быть при любом состоянии. the slot used with SetPlayerAttachedObject and RemovePlayerAttachedObject
#define BAG_SLOT 			8//для грузчиков //для шахтёров //может быть у всех кто решил подработать
#define CUFF_SLOT          	9//наручники -  могут быть у всех при разных ситуациях

//bone SetPlayerAttachedObject
#define Not_usable 		0
#define Spine 			1
#define Head 			2
#define Left_upper_arm 	3
#define Right_upper_arm 4
#define Left_hand 		5
#define Right_hand 		6
#define Left_thigh 		7
#define Right_thigh 	8
#define Left_foot 		9
#define Right_foot 		10
#define Right_calf 		11
#define Left_calf 		12
#define Left_forearm 	13
#define Right_forearm 	14
#define Left_clavicle 	15
#define Right_clavicle 	16
#define Neck 			17
#define Jaw 			18



//для финансов
//operation - константа для сортировки  для FinaceList и public GivePlayerMoneyB(operation, playerid, money)
#define fhouse 		0
#define fbiz 		100
#define fsbiz 		200

#define fjob        300
#define ffamily 	350
#define fclan 		370

#define fwithdraw 	402
#define ftransfer  	403
#define fdeposit 	404
#define fredraft 	405
#define ftax 		406
#define fjackpot 	407
#define fbox 		408
#define fpunish 	409
#define ftut 		410
#define f8ball 		411
#define fbloodbowl 	412
#define fkickstart 	413
#define frace 		414
#define fCS 		415
#define fcar 		416
#define fdonat 		417
#define fgun 		418
#define fhotel 		419

#define fadmin 		450

#define fpay 		500

//#define consuption_houme 0-60
//#define consuption_biz 100-180
//#define consuption_sbiz 200-260


#define MAX_QUEUE_LINES 50 // Максимальное кол-во строк в списке очереди.
#define STAIRWAYS 35//для лестниц



#define MAX_TURFS 229//230//320//340//360//132	//MAX_REGIONS=360  LV-87 SF-62 LS-132 RC-39 BC-14 TR-15 WS-4 FC-7

#define GAS_STATION 18//ID первой заправки в массиве SBizInfo
#define PARKING 40//ID первой парковки в массиве SBizInfo
//##############################################################################//
//                                                                              //
//                            ИДЕНТИФИКАТОРЫ ФРАКЦИЙ                             //
//                                                                              //
//##############################################################################//
/*#define MAX_HOUSE 99//52//34
#define MAX_BIZ 92//84//82
#define MAX_SBIZ 59//51//17+19=36 +11=47
*/
const TEAM_NONE = 0;
const TEAM_GROVE = 1;
const TEAM_BALLAS = 2;
const TEAM_AZTEC = 3;
const TEAM_VAGOS = 4;
const TEAM_RIFA = 5;
const TEAM_NANG = 6;
const TEAM_TRIAD = 7;
const TEAM_BIKER = 8;
const TEAM_MAFIA = 9;

const DoT = 10;
const FBI = 11;
const DoD = 12;
const DoH = 13;//12-14
const LCN = 14;
const Yakuza = 15;
const DoJ = 16;
const Hitman = 17;
const SAN = 18;
const DoE = 19;



#define iEntrance_Bank 	1570.4503,-1337.4324,16.6844//,0.0
#define iEntrance_Port  2731.6685,-2416.8745,13.6278//,0.0
#define iEntrance_Store -18.9624,-270.4885,5.4297//,0.0,
#define iEntrance_Accessor 1567.9293,-1897.5781,13.5608//,355.4098		//479.9734,-1538.2500,19.3908//,296.8976

#define iEntrance_Grove 	2486.2773,-1645.4177,14.1772
#define iEntrance_Ballas 	2022.8832,-1120.2643,26.4210
#define iEntrance_Aztecas 	1673.7352,-2122.5212,14.1460
#define iEntrance_Vagos 	2259.6941,-1019.3934,59.2949
#define iEntrance_Rifa 		2185.8599,-1815.1583,13.546

#define iEntrance_Nang 		-2129.0291,715.6000,69.5625//,86.1231
#define iEntrance_Triad 	1022.2596,-1122.2277,23.8710//,172.2558
#define iEntrance_Biker 	672.8884,-635.0313,16.3359//,277.2347
#define iEntrance_Mafia 	1726.9087,-1636.4215,20.2171//,5.4719


#define iEntrance_PoliceLS 	1555.5002,-1674.9253,16.2953
#define iEntrance_PoliceSF 	-1605.5630,710.7082,14.0672
#define iEntrance_PoliceLV 	2337.0901,2459.3225,15.0688
#define iEntrance_FBI 		-2456.1482,503.9088,30.0781

#define iEntrance_Barracks 	193.0012,1931.4508,18.0406//,91.2041

#define iEntrance_HospitalLS 	1172.2830,-1323.3102,15.3943//,270.0
#define iEntrance_HospitalSF 	-2654.9561,640.0498,14.5531
#define iEntrance_HospitalLV 	1607.2955,1815.3499,10.9203

#define iEntrance_LCN 		691.2914,-1275.9727,13.5571//,89.9549
#define iEntrance_Yakudza 	-2521.0908,-624.9518,132.8842//,0.0		979.8750,-676.5195,121.9763//,33.9856

#define iEntrance_CityHallLS 1481.1011,-1770.8237,18.8957//,0.0

#define iEntrance_CNNStudio 647.8930,-1355.4053,13.5617//,90.5336			1654.0929,-1655.2439,22.5156//,179.4302	//1093.8170,-806.4594,107.4194//,7.5031

#define iEntrance_SchoolSF -2077.8477,-114.1004,35.4840//,178.2964	//-2041.5964,-117.9192,35.7159//,87.0346 //		-2026.6433,-101.5586,35.2641//,0.0


//#define iEntrance_CoffeeHouse

enum
{
//бизы
	//GroveStreet,
	//AccessoriesStore
//MAX_HOUSE+MAX_BIZ+MAX_SBIZ+MAX_INT = 99+92+59+66
	BANK_WORLD = MAX_HOUSE+0,
	PORT_WORLD = MAX_HOUSE+81,
//.....
	ACCESSOR_WORLD = MAX_HOUSE+89,
//----------------------------
//ВНИМАНИЕ общественные интерьеры не должны превышать см. const MAX_INT_BENCH = 30;
// Система отеля
	HOTEL_INT = 7, //7 интерьер в отеле
	HOTEL_WORLD = MAX_HOUSE+MAX_BIZ, //30 вирт мир в отеле

    POLICE_LS_WORLD = MAX_HOUSE+MAX_BIZ+12,//10 //99+92 = 191+12 = 203
    POLICE_SF_WORLD = MAX_HOUSE+MAX_BIZ+14,//11
    POLICE_LV_WORLD = MAX_HOUSE+MAX_BIZ+16,//12

	FBI_SF_PARK = MAX_HOUSE+MAX_BIZ+19,//24
	FBI_SF_WORLD0 = MAX_HOUSE+MAX_BIZ+18,//20
	FBI_SF_WORLD1 = MAX_HOUSE+MAX_BIZ+20,//21
	FBI_SF_WORLD2 = MAX_HOUSE+MAX_BIZ+21,//22
    
//система больницы
    MEDIC_LS_WORLD1 = MAX_HOUSE+MAX_BIZ+22,//13+20=33
    MEDIC_SF_WORLD1 = MAX_HOUSE+MAX_BIZ+23,//14
    MEDIC_LV_WORLD1 = MAX_HOUSE+MAX_BIZ+24,//15

    MEDIC_LS_WORLD2 = MAX_HOUSE+MAX_BIZ+25,//16
    MEDIC_SF_WORLD2 = MAX_HOUSE+MAX_BIZ+26,//17
    MEDIC_LV_WORLD2 = MAX_HOUSE+MAX_BIZ+27,//18
    
    MCSA_LS_WORLD1 = MAX_HOUSE+MAX_BIZ+30,
    MCSA_LS_WORLD2 = MAX_HOUSE+MAX_BIZ+31,
    MCSA_LS_WORLD3 = MAX_HOUSE+MAX_BIZ+32,
    
	DOJ_LS_WORLD1 = MAX_HOUSE+MAX_BIZ+39,
	DOJ_LS_WORLD2 = MAX_HOUSE+MAX_BIZ+40,
	DOJ_LS_WORLD3 = MAX_HOUSE+MAX_BIZ+41
}

//MAX_HOUSE+MAX_BIZ+1

//##############################################################################//
//                                                                              //
//                            ИДЕНТИФИКАТОРЫ РАБОТ                              //
//                                                                              //
//##############################################################################//
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







//##############################################################################//
//                                                                              //
//                            ИДЕНТИФИКАТОРЫ ЧАТОВ                              //
//                                                                              //
//##############################################################################//
enum
{
	Off,
	HQChat,
	AdminsChat,
	GovernmentChat,
	DepartmentsChat,
	RadioChat,
	FamilyChat,
	MegaphoneChat,
	WalkietalkieChat,
	WhisperChat,
	ShoutChat,
	OOChat,
	LocalChat,
	RPChat,
	MEChat,
	NewsChat
}
