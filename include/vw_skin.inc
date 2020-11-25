//##############################################################################//
//                                                                              //
//                           ИДЕНТИФИКАТОРЫ СКИНОВ                               //
//                                                                              //
//##############################################################################//

//#define Not_Used 0
#define BeachVisitor 20
#define Homeless 21
#define NormalPed 22
#define DrugDealer 23
#define Farmer 24
#define Sport 25
#define PublicService 26
#define Whore 27
#define GirlFriend 28
#define Other 29
#define Fire_Brigade 41
//---------------------------
#define San_Andreas 0
#define Los_Santos 1
#define San_Fierro 2
#define Las_Venturas 3
//---------------------------
#define Male 1
#define Female 2


//для магазинов одежды

enum skininfo
{
	Skin_ID,
	Skin_Name[32],
	Type_Ped,
	Location,
	Gender
};
#define MAX_SKINS 311//299//273 //284
new SkinArray[MAX_SKINS][skininfo] = {
//mGangs
{0, "cj",TEAM_GROVE,Los_Santos,Male},
{105, "fam1",TEAM_GROVE,Los_Santos,Male},
{106, "fam2",TEAM_GROVE,Los_Santos,Male},
{107, "fam3",TEAM_GROVE,Los_Santos,Male},
{269, "Big Smoke",TEAM_GROVE,San_Andreas,Male},//5 leader - La Cosa Nostra
{270, "Sweet",TEAM_GROVE,San_Andreas,Male},//newadd
{271, "Ryder",TEAM_GROVE,San_Andreas,Male},//newadd
{102, "ballas1",TEAM_BALLAS,Los_Santos,Male},
{103, "ballas2",TEAM_BALLAS,Los_Santos,Male},
{104, "ballas3",TEAM_BALLAS,Los_Santos,Male},
{114, "vla1",TEAM_AZTEC,Los_Santos,Male},
{115, "vla2",TEAM_AZTEC,Los_Santos,Male},
{116, "vla3",TEAM_AZTEC,Los_Santos,Male},
{292, "Cesar",TEAM_AZTEC,San_Andreas,Male},//Not_Used
{108, "lsv1",TEAM_VAGOS,Los_Santos,Male},
{109, "lsv2",TEAM_VAGOS,Los_Santos,Male},
{110, "lsv3",TEAM_VAGOS,Los_Santos,Male},
{121, "dnb1",TEAM_NANG,San_Fierro,Male},
{122, "dnb2",TEAM_NANG,San_Fierro,Male},
{123, "dnb3",TEAM_NANG,San_Fierro,Male},
{173, "sfr1",TEAM_RIFA,San_Fierro,Male},
{174, "sfr2",TEAM_RIFA,San_Fierro,Male},
{175, "sfr3",TEAM_RIFA,San_Fierro,Male},
{117, "triada",TEAM_TRIAD,San_Fierro,Male},
{118, "triadb",TEAM_TRIAD,San_Fierro,Male},
{120, "triboss",TEAM_TRIAD,San_Fierro,Male},
{100, "wmycr",PublicService,San_Andreas,Male},//TEAM_BIKER
{247, "bikera",TEAM_BIKER,San_Andreas,Male},
{248, "bikerb",TEAM_BIKER,San_Andreas,Male},
{254, "bikdrug",TEAM_BIKER,San_Andreas,Male},
{111, "maffa",TEAM_MAFIA,Las_Venturas,Male},
{112, "maffb",TEAM_MAFIA,Las_Venturas,Male},
{113, "mafboss",TEAM_MAFIA,Las_Venturas,Male},
{124, "vmaff1",TEAM_MAFIA,Las_Venturas,Male},
{125, "vmaff2",TEAM_MAFIA,Las_Venturas,Male},
{126, "vmaff3",TEAM_MAFIA,Las_Venturas,Male},
{127, "vmaff4",TEAM_MAFIA,Las_Venturas,Male},
//mOrganization
//POLICE_FORCE
{265, "tenpen",DoT,San_Andreas,Male},//newadd
{266, "pulaski",DoT,San_Andreas,Male},//newadd
{267, "hern",DoT,San_Andreas,Male},//newadd
{280, "lapd1",DoT,Los_Santos,Male},//invite
{281, "sfpd1",DoT,San_Fierro,Male},
{282, "lvpd1",DoT,Las_Venturas,Male},
{283, "csher",DoT,San_Andreas,Male},
{284, "lapdm1",DoT,San_Andreas,Male},
{288, "dsher",DoT,San_Andreas,Male},//1 leader - Police Force
//FBI/ATF
{164, "wmyboun",FBI,San_Andreas,Male},
{165, "wmomib",FBI,San_Andreas,Male},//2 leader - FBI/ATF
{166, "bmymib",FBI,San_Andreas,Male},
{217, "wmyclot",FBI,San_Andreas,Male},//replace PublicService
{285, "swat",FBI,San_Andreas,Male},//replace S.W.A.T_Special_Forces
{286, "fbi",FBI,San_Andreas,Male},
{211, "wfyclot",FBI,San_Andreas,Female},//replace PublicService
//NATIONAL_GUARD
{73, "swmyhp2",DoD,San_Andreas,Male},//replace Other
{179, "wmyammo",DoD,San_Andreas,Male},//replace PublicService
{206, "vwmycd",DoD,San_Andreas,Male},//replace NormalPed
{287, "army",DoD,San_Andreas,Male},//3 leader - National Guard
{191, "gungrl3",DoD,Los_Santos,Female},//GirlFriend
//FIRE/AMBULANCE
{70, "wmosci",DoH,Las_Venturas,Male},//4 leader - Fire/Ambulance
{71, "wmysgrd",PublicService,San_Andreas,Male},//Inkassator newadd
{176, "bmybar",DoH,San_Andreas,Male},//replace PublicService
{177, "wmybar",DoH,San_Andreas,Male},//replace PublicService
{268, "Dwayne",DoH,San_Andreas,Male},//newadd
{274, "laemt1",DoH,Los_Santos,Male},//DoH
{275, "lvemt1",DoH,Las_Venturas,Male},//DoH
{276, "sfemt1",DoH,San_Fierro,Male},//DoH
//для пожарников
{277, "lafd1",DoH,Los_Santos,Male},//Fire_Brigade
{278, "lvfd1",DoH,Las_Venturas,Male},//Fire_Brigade
{279, "sffd1",DoH,San_Fierro,Male},//Fire_Brigade
{216, "swfyri",DoH,San_Andreas,Female},//replace NormalPed
//LCN
{46, "hmyri",LCN,San_Andreas,Male},//NormalPed
{98, "wmyri",LCN,San_Andreas,Male},//replace NormalPed
{223, "shmycr",LCN,San_Andreas,Male},//NormalPed
{258, "heck1",LCN,San_Andreas,Male},
{259, "heck2",LCN,San_Andreas,Male},
{233, "swfyst",LCN,San_Andreas,Female},//NormalPed
{272, "Forelli",LCN,San_Andreas,Male},//newadd
//Yakuza 227 57 186 187 59 240 59
{49, "omokung",Yakuza,San_Andreas,Male},//6 leader - Yakuza
{228, "somori",Yakuza,San_Andreas,Male},
{187, "somybu",Yakuza,San_Andreas,Male},//SAN
{186, "somyri",Yakuza,San_Andreas,Male},//Hitman
{59, "omyri",Yakuza,San_Andreas,Male},//replace NormalPed
{169, "sofyri",Yakuza,San_Andreas,Female},//replace NormalPed
{263, "vwfywa2",Yakuza,San_Andreas,Female},//replace NormalPed
//DoJ
{147, "wmybu",DoJ,San_Andreas,Male},//7 leader - Mayor
{296, "Jizzy",DoJ,San_Andreas,Male},//replace Not_Used
{17, "bmybu",DoJ,San_Andreas,Male},//Lawyer PublicService
{150, "wfybu",DoJ,San_Andreas,Female},//replace NormalPed PublicService
{295, "torino",DoJ,San_Andreas,Male},//Hitman
{57, "omori",DoJ,San_Andreas,Male},//DoE 11 leader - Driving/Flying School
{148, "bfybu",DoJ,San_Andreas,Female},//replace PublicService
{163, "bmyboun",DoJ,San_Andreas,Male},//FBI
//Hitman
{68, "wmoprea",Hitman,Las_Venturas,Male},//8 replace PublicService //leader - Hitmans
{290, "Rosie",Hitman,San_Andreas,Male},//replace Not_Used
{294, "Woozie",Hitman,San_Andreas,Male},
{299, "Claude",Hitman,San_Andreas,Male},//FBI
{55, "ofyri",Hitman,San_Andreas,Female},//replace NormalPed
//SAN
{188, "swmyst",SAN,San_Andreas,Male},//replace NormalPed
{227, "somobu",SAN,San_Andreas,Male},//9 leader - News Reporters
{185, "sbmyri",SAN,San_Andreas,Male},//replace NormalPed
{20, "bmyri",NormalPed,San_Andreas,Male},//replace NormalPed
{184, "vhmycr",SAN,San_Andreas,Male},//replace NormalPed
{12, "bfyri",SAN,San_Andreas,Female},//replace NormalPed
{93, "wfyst",NormalPed,San_Andreas,Female},//replace NormalPed
{24, "wbdyg1",SAN,San_Andreas,Male},//replace NormalPed
{261, "wmycd1",SAN,San_Andreas,Male},//replace NormalPed
//TAXI_CAB_COMPANY
{61, "wmyplt",PublicService,San_Andreas,Male},//10 leader - TAXI_CAB_COMPANY
{253, "bmosec",PublicService,San_Fierro,Male},
{255, "wmych",PublicService,San_Andreas,Male},
//DRIVING/FLYING_SCHOOL
{60, "omyst",DoE,San_Andreas,Male},//replace NormalPed
{141, "sofybu",DoE,San_Andreas,Female},//replace PublicService
{170, "somyst",DoE,San_Andreas,Male},//replace NormalPed
{171, "vwmybjd",DoE,San_Andreas,Male},//replace PublicService
{172, "vwfycrp",DoE,San_Andreas,Female},//replace PublicService
{189, "wmyva",DoE,San_Andreas,Male},//replace PublicService
{240, "swmyri",DoE,San_Andreas,Male},//replace NormalPed
{250, "swmycr",DoE,San_Andreas,Male},//replace NormalPed
{194, "crogrl3",DoE,Las_Venturas,Female},//replace GirlFriend
//------------------------------------------------------------------------------
{1, "Truth",NormalPed,San_Andreas,Male},
{2, "Maccer",NormalPed,San_Andreas,Male},
{3, "andre",NormalPed,San_Andreas,Male},
{4, "bbthin",NormalPed,Los_Santos,Male},
{5, "bb",NormalPed,Los_Santos,Male},
{6, "emmet",NormalPed,Los_Santos,Male},
{7, "male01",NormalPed,San_Andreas,Male},
{8, "janitor",NormalPed,San_Andreas,Male},
{9, "bfori",NormalPed,San_Andreas,Female},
{10, "bfost",NormalPed,San_Andreas,Female},
{11, "vbfycrp",PublicService,San_Andreas,Female},

{13, "bfyst",Sport,San_Andreas,Female},
{14, "bmori",NormalPed,San_Andreas,Male},
{15, "bmost",PublicService,San_Andreas,Male},//CarDealer replace NormalPed
{16, "bmyap",PublicService,San_Fierro,Male},

{18, "bmybe",BeachVisitor,San_Andreas,Male},
{19, "bmydj",NormalPed,San_Andreas,Male},

{21, "bmycr",NormalPed,San_Andreas,Male},
{22, "bmyst",Sport,San_Andreas,Male},//NormalPed
{23, "wmybmx",Sport,Los_Santos,Male},

{25, "wbdyg2",NormalPed,San_Andreas,Male},
{26, "wmybp",Sport,San_Andreas,Male},
{27, "wmycon",PublicService,San_Fierro,Male},
{28, "bmydrug",PublicService,San_Andreas,Male},//CarJaker replace NormalPed
{29, "wmydrug",PublicService,San_Andreas,Male},//DrugDealer
{30, "hmydrug",NormalPed,San_Andreas,Male},
{31, "dwfolc",Farmer,San_Andreas,Female},
{32, "dwmolc1",Farmer,San_Andreas,Male},
{33, "dwmolc2",Farmer,San_Andreas,Male},
{34, "dwmylc1",Farmer,San_Andreas,Male},
{35, "hmogar",NormalPed,San_Andreas,Male},
{36, "wmygol1",NormalPed,San_Andreas,Male},
{37, "wmygol2",NormalPed,San_Andreas,Male},
{38, "hfori",NormalPed,San_Andreas,Female},
{39, "hfost",NormalPed,San_Andreas,Female},
{40, "hfyri",NormalPed,San_Andreas,Female},
{41, "hfyst",NormalPed,San_Andreas,Female},
{42, "jethro",NormalPed,San_Fierro,Male},
{43, "hmori",NormalPed,San_Andreas,Male},
{44, "hmost",NormalPed,San_Andreas,Male},
{45, "hmybe",BeachVisitor,San_Andreas,Male},

{47, "hmycr",NormalPed,San_Andreas,Male},
{48, "hmyst",NormalPed,San_Andreas,Male},

{50, "wmymech",PublicService,San_Andreas,Male},//CarMechanic
{51, "bmymoun",Sport,San_Andreas,Male},
{52, "wmymoun",Sport,San_Andreas,Male},
{53, "ofost",NormalPed,San_Andreas,Female},
{54, "ofost",NormalPed,San_Andreas,Female},

{56, "ofyst",NormalPed,San_Andreas,Female},

{58, "omost",NormalPed,San_Andreas,Male},

{62, "wmopj",PublicService,San_Andreas,Male},//NormalPed для заключенных
{63, "bfypro",Whore,San_Andreas,Female},
{64, "hfypro",Whore,San_Andreas,Female},
{65, "kendl",NormalPed,San_Andreas,Female},
{66, "bmypol1",NormalPed,San_Andreas,Male},//replace Other
{67, "bmypol2",NormalPed,San_Andreas,Male},

{69, "sbfyst",NormalPed,San_Andreas,Female},

{72, "swmyhp1",NormalPed,San_Andreas,Male},

{75, "swfopro",Whore,San_Andreas,Female},
{76, "wfystew",NormalPed,San_Andreas,Female},//replace NormalPed
{77, "swmotr1",Homeless,San_Andreas,Female},
{78, "wmotr1",Homeless,San_Andreas,Male},
{79, "bmotr1",Homeless,San_Andreas,Male},
{80, "vbmybox",Sport,San_Andreas,Male},
{81, "vwmybox",PublicService,San_Andreas,Male},//Boxer
{82, "vhmyelv",Other,San_Andreas,Male},
{83, "vbmyelv",Other,San_Andreas,Male},
{84, "vimyelv",Other,San_Andreas,Male},
{85, "vwfypro",Whore,San_Andreas,Female},
{86, "ryder3",NormalPed,Los_Santos,Male},
{87, "vwfyst1",Whore,San_Andreas,Female},
{88, "wfori",NormalPed,San_Andreas,Female},
{89, "wfost",NormalPed,San_Andreas,Female},
{90, "wfyjg",Whore,San_Andreas,Female},
{91, "wfyri",NormalPed,San_Andreas,Female},
{92, "wfyro",BeachVisitor,San_Andreas,Female},

{94, "wmori",NormalPed,San_Andreas,Male},
{95, "wmost",NormalPed,San_Andreas,Male},
{96, "wmyjg",Sport,San_Andreas,Male},
{97, "wmylg",BeachVisitor,San_Andreas,Male},

{99, "wmyro",Sport,San_Andreas,Male},

{101, "wmyst",NormalPed,San_Andreas,Male},

{119, "sindaco",NormalPed,Las_Venturas,Male},

{128, "dnmylc",Farmer,San_Andreas,Male},
{129, "dnfolc1",Farmer,San_Andreas,Female},
{130, "dnfolc2",Farmer,San_Andreas,Female},
{131, "dnfylc",Farmer,San_Andreas,Female},
{132, "dnmolc1",Farmer,San_Andreas,Male},
{133, "dnmolc2",PublicService,San_Andreas,Male},//Trucker
{134, "sbmotr2",Homeless,San_Andreas,Male},
{135, "swmotr2",Homeless,San_Andreas,Male},
{136, "sbmytr3",Homeless,San_Andreas,Male},
{137, "swmotr3",Homeless,San_Andreas,Male},
{138, "wfybe",BeachVisitor,San_Andreas,Female},
{139, "bfybe",BeachVisitor,San_Andreas,Female},
{140, "hfybe",BeachVisitor,San_Andreas,Female},

{142, "sbmyst",NormalPed,San_Andreas,Male},
{143, "sbmycr",NormalPed,San_Andreas,Male},
{144, "bmycg",NormalPed,San_Andreas,Male},
{145, "wfycrk",BeachVisitor,San_Andreas,Female},
{146, "hmycm",BeachVisitor,San_Andreas,Male},

{149, "smokev",NormalPed,Los_Santos,Male},

{151, "dwfylc1",NormalPed,San_Andreas,Female},
{152, "wfypro",Whore,San_Andreas,Female},
{153, "wmyconb",PublicService,San_Andreas,Male},
{154, "wmybe",BeachVisitor,San_Andreas,Male},
{155, "wmypizz",PublicService,San_Andreas,Male},
{156, "bmobar",PublicService,San_Andreas,Male},//Detective
{157, "cwfyhb",Farmer,San_Andreas,Female},
{158, "cwmofr",Farmer,San_Andreas,Male},
{159, "cwmohb1",Farmer,San_Andreas,Male},
{160, "cwmohb2",Farmer,San_Andreas,Male},
{161, "cwmyfr",Farmer,San_Andreas,Male},
{162, "cwmyhb1",Farmer,San_Andreas,Male},

{167, "wmybell",PublicService,San_Andreas,Male},
{168, "bmochil",NormalPed,San_Andreas,Male},

{178, "wfysex",Whore,San_Andreas,Female},
{180, "bmytatt",Sport,San_Andreas,Male},
{181, "vwmycr",Other,San_Andreas,Male},
{182, "vbmocd",NormalPed,San_Andreas,Male},
{183, "vbmycr",NormalPed,San_Andreas,Male},

{190, "copgrl3",GirlFriend,Las_Venturas,Female},

{192, "mecgrl3",GirlFriend,San_Fierro,Female},
{193, "nurgrl3",GirlFriend,San_Fierro,Female},

{195, "gangrl3",GirlFriend,Los_Santos,Female},
{196, "cwfofr",Farmer,San_Andreas,Female},
{197, "cwfohb",Farmer,San_Andreas,Female},
{198, "cwfyfr1",Farmer,San_Andreas,Female},
{199, "cwfyfr2",Farmer,San_Andreas,Female},
{200, "cwmyhb2",Farmer,San_Andreas,Male},
{201, "dwfylc2",Farmer,San_Andreas,Female},
{202, "dwmylc2",Farmer,San_Andreas,Male},
{203, "omykara",Sport,San_Andreas,Male},
{204, "wmykara",Sport,San_Andreas,Male},
{205, "wfyburg",PublicService,San_Andreas,Female},

{207, "vhfypro",Whore,San_Andreas,Female},
{208, "suzie",NormalPed,San_Fierro,Male},
{209, "omonood",PublicService,San_Andreas,Male},
{210, "omoboat",NormalPed,San_Andreas,Male},

{212, "vwmotr1",Homeless,San_Andreas,Male},
{213, "vwmotr2",Homeless,San_Andreas,Male},
{214, "vwfywai",NormalPed,San_Andreas,Female},
{215, "sbfori",NormalPed,San_Andreas,Female},

{218, "sbfost",NormalPed,San_Andreas,Female},
{219, "sbfyri",PublicService,San_Andreas,Female},
{220, "sbmocd",NormalPed,San_Andreas,Male},
{221, "sbmori",NormalPed,San_Andreas,Male},
{222, "sbmost",NormalPed,San_Andreas,Male},

{224, "sofori",NormalPed,San_Andreas,Female},//replace Yakuza
{225, "sofost",NormalPed,San_Andreas,Female},
{226, "sofyst",NormalPed,San_Andreas,Female},

{229, "somost",NormalPed,San_Andreas,Male},

{230, "swmotr5",Homeless,San_Andreas,Male},
{231, "swfori",NormalPed,San_Andreas,Female},
{232, "swfost",NormalPed,San_Andreas,Female},

{234, "swmocd",NormalPed,San_Andreas,Male},
{235, "swmori",NormalPed,San_Andreas,Male},
{236, "swmost",NormalPed,San_Andreas,Male},
{237, "shfypro",Whore,San_Andreas,Female},
{238, "sbfypro",Whore,San_Andreas,Female},
{239, "swmotr4",PublicService,San_Andreas,Male},//Homeless для амнистированных
{241, "smyst",NormalPed,San_Andreas,Male},//replace Yakuza
{242, "smyst2",NormalPed,San_Andreas,Male},//replace Yakuza
{243, "sfypro",Whore,San_Andreas,Female},
{244, "vbfyst2",Whore,San_Andreas,Female},
{245, "vbfypro",Whore,San_Andreas,Female},
{246, "vhfyst3",Whore,San_Andreas,Female},
{249, "bmypimp",PublicService,San_Fierro,Male},
{251, "wfylg",BeachVisitor,San_Andreas,Female},
{252, "wmyva2",BeachVisitor,Los_Santos,Male},

{256, "sbfystr",Whore,San_Andreas,Female},
{257, "swfystr",Whore,San_Andreas,Female},

{260, "bmycon",PublicService,San_Fierro,Male},
{262, "bmocd",NormalPed,San_Andreas,Male},

{264, "wmoice",Other,San_Andreas,Male},

{273, "tbone",NormalPed,San_Fierro,Male},

{289, "zero",NormalPed,San_Fierro,Male},

{291, "Kent Paul",NormalPed,San_Andreas,Male},
{293, "OG Loc",NormalPed,San_Andreas,Male},
{297, "Maddog",NormalPed,San_Andreas,Male},
{298, "Catalina",GirlFriend,San_Andreas,Female},//newadd GirlFriend

{300, "lapdna",FBI,Los_Santos,Male},
{301, "sfpdn",FBI,San_Fierro,Male},
{302, "lvpdna",DoT,Las_Venturas,Male},
{303, "lapdpc",DoT,Los_Santos,Male},
{304, "lapdpd",DoT,Los_Santos,Male},
{305, "lvpdpc",DoT,Las_Venturas,Male},
{306, "WFYCLPD",FBI,Los_Santos,Female},
{307, "VBFYCPD",FBI,San_Fierro,Female},
{308, "WFYCLEM",DoH,San_Fierro,Female},
{309, "WFYCLLV",DoT,Las_Venturas,Female},
{310, "csherna",DoT,Los_Santos,Male},
{311, "dsherna",DoT,Las_Venturas,Male}
};

//для магазинов одежды конец

stock IsValidSkin(SkinID)
{
	/*if( (SkinID == 0)||(SkinID == 7)||(SkinID >= 9 && SkinID <= 41)||
		(SkinID >= 43 && SkinID <= 64)||(SkinID >= 66 && SkinID <= 73)||
		(SkinID >= 75 && SkinID <= 85)||(SkinID >= 87 && SkinID <= 118)||
		(SkinID >= 120 && SkinID <= 148)||(SkinID >= 150 && SkinID <= 207)||
		(SkinID >= 209 && SkinID <= 267)||(SkinID >= 274 && SkinID <= 288)||
		(SkinID >= 290 && SkinID <= 299)
	  )*/
	if( SkinID >= 1 && SkinID <= 311 && SkinID != 74 )// && SkinID != 53
	{
		return 1;
	}
	return 0;
}

new newskin = 0;
new skins = 0;  //new pGender = 0;
stock skin_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	//для магазинов одежды начало
	//static newskin;
	//static skins;

    if(Current == mClothMenu)
	{
        switch(row)
		{
            case 0://Civilian
			{
				if(	(PlayerInfo[playerid][pMember] == 0 && !IsAGangs(playerid) && PlayerInfo[playerid][pSex] == Male) ||
					(PlayerInfo[playerid][pMember] != 0  && !gOnDuty[playerid] && PlayerInfo[playerid][pSex] == Male)
					|| PlayerInfo[playerid][pMember] == Hitman
					||(PlayerInfo[playerid][pMember] == FBI &&
						(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
				{
					HideMenuForPlayerEx(mClothMenu, playerid);
					skins = 0;
					ShowMenuForPlayerEx(mMale, playerid);
				}
				else if(PlayerInfo[playerid][pSex] == Female)
				{
					HideMenuForPlayerEx(mClothMenu, playerid);
					skins = 0;
					ShowMenuForPlayerEx(mFemale, playerid);
				}
				else ShowMenuForPlayerEx(mClothMenu, playerid);
			}
            case 1://Organization
			{
				if(PlayerInfo[playerid][pMember] >= DoT)
				{
					HideMenuForPlayerEx(mClothMenu, playerid);
					skins = 0;
					ShowMenuForPlayerEx(mOrganization, playerid);
				}
				else ShowMenuForPlayerEx(mClothMenu, playerid);
			}
			case 2://Gangs
			{
				if(	(IsAGangs(playerid)	&& PlayerInfo[playerid][pSex] == Male) || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
				{
					HideMenuForPlayerEx(mClothMenu, playerid);
					skins = 0;
					ShowMenuForPlayerEx(mGangs, playerid);
				}
				else ShowMenuForPlayerEx(mClothMenu, playerid);
			}
        }
    }
    else if(Current == mMale)
	{
    	switch(row)
		{
			case 0: //BeachVisitor
			{
				HideMenuForPlayerEx(mMale, playerid);
				SetPVarInt(playerid, "TypePed", BeachVisitor);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 1: //Homeless
			{
				HideMenuForPlayerEx(mMale, playerid);
				SetPVarInt(playerid, "TypePed", Homeless);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 2: //NormalPed
			{
				HideMenuForPlayerEx(mMale, playerid);
				SetPVarInt(playerid, "TypePed", NormalPed);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 3: //Farmer
			{
				HideMenuForPlayerEx(mMale, playerid);
				SetPVarInt(playerid, "TypePed", Farmer);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 4: //Sport
			{
				HideMenuForPlayerEx(mMale, playerid);
				SetPVarInt(playerid, "TypePed", Sport);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 5: //Public Service
			{
				if(PlayerInfo[playerid][pAdmin] >= 1)
				{
					HideMenuForPlayerEx(mMale, playerid);
					SetPVarInt(playerid, "TypePed", PublicService);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mClothMenu, playerid);
			}
			case 6: //Other
			{
				HideMenuForPlayerEx(mMale, playerid);
				SetPVarInt(playerid, "TypePed", Other);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
		}
	}
	else if(Current == mFemale)
	{
    	switch(row)
		{
			case 0: //BeachVisitor
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", BeachVisitor);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 1: //Homeless
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", Homeless);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 2: //Normal
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", NormalPed);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 3: //Whore
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", Whore);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 4: //Farmer
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", Farmer);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 5: //CJ'girlfriend
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", GirlFriend);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
			case 6: //Public Service
			{
				if(PlayerInfo[playerid][pAdmin] >= 1)
				{
					HideMenuForPlayerEx(mFemale, playerid);
					SetPVarInt(playerid, "TypePed", PublicService);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mClothMenu, playerid);
			}
			case 7: //Other
			{
				HideMenuForPlayerEx(mFemale, playerid);
				SetPVarInt(playerid, "TypePed", Other);
				ShowMenuForPlayerEx(mPaid, playerid);
			}
		}
	}
	else if(Current == mOrganization)
	{
    	switch(row)
		{
			case 0: //Police Department
			{
                if(PlayerInfo[playerid][pMember] == DoT || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", DoT);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 1: //Federal Agents
			{
                if(PlayerInfo[playerid][pMember] == FBI || PlayerInfo[playerid][pMember] == Hitman)
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", FBI);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 2: //National Guard
			{
                if(PlayerInfo[playerid][pMember] == DoD //|| PlayerInfo[playerid][pMember] == Hitman ||
					//(PlayerInfo[playerid][pMember] == FBI &&
					//(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", DoD);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 3: //Ambulance Personnel
			{
                if( PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == Hitman ||
    				(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", DoH);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 4: //Fire Brigade
			{
                if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", DoH);//Fire_Brigade;
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 5: //La Cosa Nostra
			{
                if(PlayerInfo[playerid][pMember] == LCN || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", LCN);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 6: //Yakuza
			{
                if(PlayerInfo[playerid][pMember] == Yakuza || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", Yakuza);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 7: //Mayor
			{
                if(PlayerInfo[playerid][pMember] == DoJ)
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", DoJ);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 8: //Hitmans
			{
                if(PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", Hitman);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 9: //News Reporters
			{
                if(PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", SAN);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
			case 10: //Driving/Flying School
			{
                if(PlayerInfo[playerid][pMember] == DoE || PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mOrganization, playerid);
					SetPVarInt(playerid, "TypePed", DoE);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mOrganization, playerid);
			}
		}
	}
    else if(Current == mGangs)
	{
    	switch(row)
		{
			case 0: //Grove Street
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_GROVE ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 ||
					PlayerInfo[playerid][pRank] == 7 ||
					PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_GROVE);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 1: //The Ballas
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_BALLAS ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 ||
					PlayerInfo[playerid][pRank] == 7 ||
					PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_BALLAS);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 2: //Varios Los Aztecas
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_AZTEC ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_AZTEC);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 3: //Los Santos Vagos
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_VAGOS ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_VAGOS);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 4: //Da Nang Boys
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_NANG ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_NANG);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 5: //San Fierro Rifa
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_RIFA ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_RIFA);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 6: //The Traids
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_TRIAD ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_TRIAD);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 7: //TEAM_BIKER
			{
                if(	PlayerInfo[playerid][pMember] == TEAM_BIKER ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_BIKER);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
			case 8: //The Mafia
			{
                if( PlayerInfo[playerid][pMember] == TEAM_MAFIA ||
					PlayerInfo[playerid][pMember] == Hitman ||
					(PlayerInfo[playerid][pMember] == FBI &&
					(PlayerInfo[playerid][pRank] == 5 || PlayerInfo[playerid][pRank] == 7 || PlayerInfo[playerid][pRank] == 9))
				  )
                {
					HideMenuForPlayerEx(mGangs, playerid);
					SetPVarInt(playerid, "TypePed", TEAM_MAFIA);
					ShowMenuForPlayerEx(mPaid, playerid);
				}
				else ShowMenuForPlayerEx(mGangs, playerid);
			}
		}
	}
    else if(Current == mPaid)
	{
		new SkinID;
		//new location = PlayerInfo[playerid][pLocal];
    	switch(row)
		{
			case 0://Next
			{
				new ind, Found, Clothes[MAX_SKINS];//массив для хранения найденых
				//pGender = PlayerInfo[playerid][pSex];
				for(new i=0; i<MAX_SKINS; i++)//сканируем все скины
				{
					if(	SkinArray[i][Type_Ped] == GetPVarInt(playerid, "TypePed") &&
						SkinArray[i][Gender] == PlayerInfo[playerid][pSex])
					{   //создаем список доступных скинов
						Clothes[ind] = i; ind ++; Found = 1;
					}//записали в массив тот ID соотв. например муж. посетителю пляжа
				}
				if(skins == ind) skins = 0;
				if(Found == 1)
				{   //если нашли
					SkinID = SkinArray[Clothes[skins]][Skin_ID];
					SetPlayerSkinEx(playerid, SkinID);
					SetPVarInt(playerid, "IsPaid", 0);
				    skins ++;
				}
				ShowMenuForPlayerEx(mPaid, playerid);
				ApplyAnimation(playerid, "CLOTHES", "CLO_Pose_Torso",4.1,0,1,1,0,0);
			}
			case 1://Paid
			{
				if(GetPlayerMoneyH(playerid) < 500)
				{
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					ShowMenuForPlayerEx(mClothMenu, playerid); //return 1;
				}
				/*else if(BizInfo[GetBizLocation(playerid)-100][bProducts] <= 0  && !gRealWar
						&& !IsPlayerInRangeOfPoint(playerid, 7.5,256.8213,-41.5293,1002.0234))
				{
					GameTextForPlayerEx(playerid, "~r~Out Of Stock", 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					ShowMenuForPlayerEx(mClothMenu, playerid); //return 1;
				}*/
				else
				{
		        	//ClearAnimations(playerid, 1);
					HideMenuForPlayerEx(mPaid, playerid);
					GivePlayerMoneyH(fbiz+GetBizLocation(playerid)-100, playerid, -500);
					/*if( IsPlayerInRangeOfPoint(playerid, 7.5,256.8213,-41.5293,1002.0234) )
					{
						HouseInfo[GetHouseLocation(playerid)][hTill] += 500;
					}
					else
					{
						OnGangsExtortionBiz(GetBizLocation(playerid)-100, 500);
						//BizInfo[bizid][bProducts] --;//99-99=0
					}*/
					PlaySoundForPlayer(playerid, SOUND_SHOP_BUY);
					newskin = GetPlayerSkin(playerid);
					if(!IsValidSkin(newskin)) newskin = SKIN_DEFAULT;
					if( PlayerInfo[playerid][pMember] >= DoT
						&& PlayerInfo[playerid][pMember] != LCN
						&& PlayerInfo[playerid][pMember] != Yakuza
						&& gOnDuty[playerid] == 1)
					{
						PlayerInfo[playerid][pChar] = newskin;
					}
					else if(IsAGangs(playerid)
						|| PlayerInfo[playerid][pMember] == LCN
						|| PlayerInfo[playerid][pMember] == Yakuza)
					{
						PlayerInfo[playerid][pModel] = newskin;
						PlayerInfo[playerid][pChar] = newskin;
					}
					else PlayerInfo[playerid][pModel] = newskin;
					SetPVarInt(playerid, "IsPaid", 1);
	 				format(strings, sizeof(strings), "Bаш новый скин: %d. Ваш старый скин: %d", newskin, GetPVarInt(playerid, "OldSkin"));
					SendClientMessage(playerid, COLOR_GREEN, strings);
					ShowMenuForPlayerEx(mClothMenu, playerid);
					ApplyAnimation(playerid, "CLOTHES", "CLO_Buy",4.1,0,1,1,0,0);
				}
			}
		}
	}//для магазинов одежды конец
}

stock skins_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != SKINS_DIALOG) return 1;
	if(!response)
	{

		return 1;
	}
	//new msgitem[256+1];
	new killed = GetPVarInt(playerid, "PlayerID");
	SetPlayerSkinEx(playerid, PlayerInfo[killed][pChar]);
	PlayerInfo[killed][pChar] = PlayerInfo[killed][pModel];
	gOnDuty[killed] = 0;
	return 1;
}
