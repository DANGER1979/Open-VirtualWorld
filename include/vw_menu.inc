new MenuCounter;//счётчик загруженных меню, т.к. меню в процессе игры лучше не создавать

//##############################################################################//
//                                                                              //
//                            ИДЕНТИФИКАТОРЫ MENU                               //
//                                                                              //
//##############################################################################//
#define MAX_MENU 37
new Menu:mBank;//0
new Menu:mAmmuNation;
new Menu:mOtherAmmuNation;
new Menu:mPoliceDepartment;

new Menu:mBar;//4
new Menu:mRestaurant;
new Menu:mBurgerShot;
new Menu:mCluckinBell;
new Menu:mStackedPizza;

new Menu:mJobMenu1_9;//для устройства на работу
new Menu:mJobMenu10_19;//для устройства на работу
new Menu:mGangsVacancies;
new Menu:mVacancies;//для автоназначения лидеров

new Menu:mClothMenu;
new Menu:mMale;
new Menu:mFemale;
new Menu:mOrganization;
new Menu:mGangs;
new Menu:mPaid;

new Menu:mTuningMenu;
new Menu:mColors;
new Menu:mPaintJob;
new Menu:mNitro;
new Menu:mWheels;
new Menu:mHydraulics;
new Menu:mSpoiler;
new Menu:mFrontBumper;
new Menu:mRearBumper;
new Menu:mSideskirt;
new Menu:mRoof;
new Menu:mExhaust;

//new Menu:mOthers;
new Menu:mNeon;
//new Menu:mBullbarsFront;
//new Menu:mBullbarsRear;
//new Menu:mHood;
//new Menu:mVents;
//new Menu:mLamps;

new Menu:mPunish;


//==============================================================================

//stock LoadMenus()
stock menu_OnGameModeInit()
{
	new time = GetTickCount();
	//==========================================================================
	//для меню начало
	mBank = CreateMenuEx("Bank",1,10.0,120.0,100.0,0.0);
    AddMenuItem(mBank, 0, "Balance");
    //AddMenuItem(mBank, 0, "Transfer");
    AddMenuItem(mBank, 0, "Deposit");
    AddMenuItem(mBank, 0, "Credit");
    AddMenuItem(mBank, 0, "Withdraw");
    //--------------------------------------------------------------------------
	mAmmuNation = CreateMenuEx("AmmuNation", 2, 10.0, 120.0, 90.0, 90.0);
	SetMenuColumnHeader(mAmmuNation, 0,	"Weapon");
	SetMenuColumnHeader(mAmmuNation, 1,	"        Cost");
	AddMenuItem(mAmmuNation, 0, "9mm");//Colt 45
	AddMenuItem(mAmmuNation, 1, "        $200");//Colt 45
	AddMenuItem(mAmmuNation, 0, "Silenced 9mm");//Colt 45 (Silenced)
	AddMenuItem(mAmmuNation, 1, "        $600");//Colt 45 (Silenced)
	AddMenuItem(mAmmuNation, 0, "Desert Eagle");
	AddMenuItem(mAmmuNation, 1, "        $1200");
	AddMenuItem(mAmmuNation, 0, "Shotgun");
	AddMenuItem(mAmmuNation, 1, "        $600");
	AddMenuItem(mAmmuNation, 0, "Combat Shotgun");
	AddMenuItem(mAmmuNation, 1, "        $1000");
	AddMenuItem(mAmmuNation, 0, "Rifle");//Country Rifle
	AddMenuItem(mAmmuNation, 1, "        $1000");//Country Rifle
	AddMenuItem(mAmmuNation, 0, "SMG");
	AddMenuItem(mAmmuNation, 1, "        $2000");
	AddMenuItem(mAmmuNation, 0, "AK47");
	AddMenuItem(mAmmuNation, 1, "        $3500");
	AddMenuItem(mAmmuNation, 0, "M4");
	AddMenuItem(mAmmuNation, 1, "        $4500");
	AddMenuItem(mAmmuNation, 0, "Bomb");
	AddMenuItem(mAmmuNation, 1, "        $4500");
	AddMenuItem(mAmmuNation, 0, "Other");
	AddMenuItem(mAmmuNation, 1, "     Weapon");

	mOtherAmmuNation = CreateMenuEx("AmmuNation", 2, 10.0, 120.0, 90.0, 90.0);
	SetMenuColumnHeader(mOtherAmmuNation, 0,	"Weapon");
	SetMenuColumnHeader(mOtherAmmuNation, 1,	"        Cost");
	AddMenuItem(mOtherAmmuNation, 0, "Grenade");
	AddMenuItem(mOtherAmmuNation, 1, "        $300");
	AddMenuItem(mOtherAmmuNation, 0, "Tear Gas");
	AddMenuItem(mOtherAmmuNation, 1, "        $400");
	AddMenuItem(mOtherAmmuNation, 0, "Molotov Cocktail");
	AddMenuItem(mOtherAmmuNation, 1, "        $500");
	AddMenuItem(mOtherAmmuNation, 0, "Fire Extinguisher");
	AddMenuItem(mOtherAmmuNation, 1, "        $1000");
	AddMenuItem(mOtherAmmuNation, 0, "FlameThrower");//Огнемёт
	AddMenuItem(mOtherAmmuNation, 1, "        $7050");
	AddMenuItem(mOtherAmmuNation, 0, "RocketLauncher");//РПГ-7
	AddMenuItem(mOtherAmmuNation, 1, "        $21150");
	AddMenuItem(mOtherAmmuNation, 0, "HeatSeeker");//Stinger Missile System
	AddMenuItem(mOtherAmmuNation, 1, "        $21150");
    //--------------------------------------------------------------------------
	mBar = CreateMenuEx("Bar", 2, 10.0, 120.0, 70.0, 50.0);
	SetMenuColumnHeader(mBar, 0,	"Drink");
	SetMenuColumnHeader(mBar, 1,	"        Cost");
	AddMenuItem(mBar, 0, "Drink Beer");
    AddMenuItem(mBar, 1, "    $6");
    AddMenuItem(mBar, 0, "Drink Vodka");
    AddMenuItem(mBar, 1, "    $8");
	AddMenuItem(mBar, 0, "Drink Whiskey");
    AddMenuItem(mBar, 1, "    $10");
    AddMenuItem(mBar, 0, "Drink Water");
    AddMenuItem(mBar, 1, "    $2");
    AddMenuItem(mBar, 0, "Buy Beer");
    AddMenuItem(mBar, 1, "    $12");
    //AddMenuItem(mBar, 0, "Buy Vodka       $16");
    //--------------------------------------------------------------------------
 	//mRestaurant = CreateMenuEx("Restaurant", 1, 10.0, 120.0, 140.0, 140.0);
 	mRestaurant = CreateMenuEx("Restaurant", 2, 10.0, 120.0, 70.0, 50.0);
	SetMenuColumnHeader(mRestaurant,0, "Meal");
	SetMenuColumnHeader(mRestaurant,1, "    Cost");
	AddMenuItem(mRestaurant, 0, "Spark Grill");//для экономики
    AddMenuItem(mRestaurant, 1, "    $125");
    AddMenuItem(mRestaurant, 0, "The Palm");
    AddMenuItem(mRestaurant, 1, "    $100");
	AddMenuItem(mRestaurant, 0, "Campanile");
    AddMenuItem(mRestaurant, 1, "    $75");
    AddMenuItem(mRestaurant, 0, "Madeo");
    AddMenuItem(mRestaurant, 1, "    $50");
    AddMenuItem(mRestaurant, 0, "Matsuhisa");
    AddMenuItem(mRestaurant, 1, "    $25");
    //AddMenuItem(mRestaurant, 0, "Buy Soda        $4");
    //--------------------------------------------------------------------------
	mPoliceDepartment = CreateMenuEx("Police",1,10.0,120.0,100.0,0.0);
    //AddMenuItem(mPoliceDepartment, 0, "On/Off Duty");
    AddMenuItem(mPoliceDepartment, 0, "Wanted List");
    AddMenuItem(mPoliceDepartment, 0, "Clear Wanted");
    AddMenuItem(mPoliceDepartment, 0, "DataComputer");
    AddMenuItem(mPoliceDepartment, 0, "Lock Door");
	//AddMenuItem(mPoliceDepartment, 0, "Pay Fine");
    //--------------------------------------------------------------------------
	//mBurgerShot = CreateMenuEx("Food", 2, 10.0, 120.0, 70.0, 70.0);
	mBurgerShot = CreateMenuEx("BurgerShot", 2, 10.0, 120.0, 70.0, 50.0);
	SetMenuColumnHeader(mBurgerShot,0, "Meal");
	SetMenuColumnHeader(mBurgerShot,1, "    Cost");
    AddMenuItem(mBurgerShot, 0, "Moo Kids Meal");
    AddMenuItem(mBurgerShot, 1, "    $2");
    AddMenuItem(mBurgerShot, 0, "Beef Tower");
    AddMenuItem(mBurgerShot, 1, "    $5");
	AddMenuItem(mBurgerShot, 0, "Meat Stack");
	AddMenuItem(mBurgerShot, 1, "    $10");
    AddMenuItem(mBurgerShot, 0, "Salad Meal");
    AddMenuItem(mBurgerShot, 1, "    $10");
	AddMenuItem(mBurgerShot, 0,	"Buy Hamburger");
	AddMenuItem(mBurgerShot, 1,	"    $1000");

	mCluckinBell = CreateMenuEx("CluckinBell", 2, 10.0, 120.0, 70.0, 50.0);
	SetMenuColumnHeader(mCluckinBell,0, "Meal");
	SetMenuColumnHeader(mCluckinBell,1, "    Cost");
    AddMenuItem(mCluckinBell, 0, "Little Meal");
    AddMenuItem(mCluckinBell, 1, "    $2");
    AddMenuItem(mCluckinBell, 0, "Big Meal");
    AddMenuItem(mCluckinBell, 1, "    $5");
	AddMenuItem(mCluckinBell, 0, "Huge Meal");
	AddMenuItem(mCluckinBell, 1, "    $10");
    AddMenuItem(mCluckinBell, 0, "Salad Meal");
    AddMenuItem(mCluckinBell, 1, "    $10");
	AddMenuItem(mCluckinBell, 0, "Buy Chicken");
	AddMenuItem(mCluckinBell, 1, "    $1000");

	mStackedPizza = CreateMenuEx("StackedPizza", 2, 10.0, 120.0, 70.0, 50.0);
	SetMenuColumnHeader(mStackedPizza,0, "Meal");
	SetMenuColumnHeader(mStackedPizza,1, "    Cost");
    AddMenuItem(mStackedPizza, 0, "Buster");
    AddMenuItem(mStackedPizza, 1, "    $2");
    AddMenuItem(mStackedPizza, 0, "Doble D-Luxe");
    AddMenuItem(mStackedPizza, 1, "    $5");
	AddMenuItem(mStackedPizza, 0, "Full Rack");
	AddMenuItem(mStackedPizza, 1, "    $10");
    AddMenuItem(mStackedPizza, 0, "Salad Meal");
    AddMenuItem(mStackedPizza, 1, "    $10");
	AddMenuItem(mStackedPizza, 0, "Buy Pizza");
	AddMenuItem(mStackedPizza, 1, "    $1000");
    //--------------------------------------------------------------------------
	//Для устройства на работу
	mJobMenu1_9 = CreateMenuEx("Job", 1, 10.0, 120.0, 100.0, 100.0);
    //AddMenuItem(mJobMenu1_9, 0, "Miner");//0 Miner Registration
    AddMenuItem(mJobMenu1_9, 0, "Lawyer");//1 Lawyer Registration
	AddMenuItem(mJobMenu1_9, 0, "RoadWorker");//2 RoadWorker Registration
    AddMenuItem(mJobMenu1_9, 0, "DrugDealer");//3 DrugDealer Registration
    AddMenuItem(mJobMenu1_9, 0, "CarJacker");//5 CarJacker Registration
    AddMenuItem(mJobMenu1_9, 0, "AutoBuyer");//6
    AddMenuItem(mJobMenu1_9, 0, "CarMechanic");//7 CarMechanic Registration
    //AddMenuItem(mJobMenu1_9, 0, "Farmer");//8 BodyGuard Registration
    AddMenuItem(mJobMenu1_9, 0, "ArmsDealer");//9 ArmsDealer Registration
	AddMenuItem(mJobMenu1_9, 0, "Others Job");
    AddMenuItem(mJobMenu1_9, 0, "Gangs");//11
	AddMenuItem(mJobMenu1_9, 0, "Vacancies");

	mJobMenu10_19 = CreateMenuEx("Job", 1, 10.0, 120.0, 100.0, 100.0);
	AddMenuItem(mJobMenu10_19, 0, "CarDealer");//10 CarDealer Registration
    AddMenuItem(mJobMenu10_19, 0, "Inkassator");//11 Inkassator Registration
    //AddMenuItem(mJobMenu10_19, 0, "Bookmaker");//12 Bookmaker Registration
	AddMenuItem(mJobMenu10_19, 0, "TaxiDriver");//13 Taxi Registration
    AddMenuItem(mJobMenu10_19, 0, "BusDriver");//14 BusDriver Registration
	AddMenuItem(mJobMenu10_19, 0, "PaperBoy");//для курьеров //15 PaperBoy Registration
    AddMenuItem(mJobMenu10_19, 0, "Trucker");//16 Trucker Registration
    AddMenuItem(mJobMenu10_19, 0, "Trashman");//17 Trashman Registration
	//AddMenuItem(mJobMenu10_19, 0, "Fisher");//17 Fisher Registration
    //AddMenuItem(mJobMenu10_19, 0, "Cooker");//18 Cooker Registration
    //AddMenuItem(mJobMenu10_19, 0, "Loader");//19 Loader Registration

	mGangsVacancies = CreateMenuEx("Gangs", 1, 10.0, 120.0, 100.0, 100.0);
	AddMenuItem(mGangsVacancies, 0, "Grove Street");//1
    AddMenuItem(mGangsVacancies, 0, "The Ballas");//2
    AddMenuItem(mGangsVacancies, 0, "Varios Los Aztecas");//3
	AddMenuItem(mGangsVacancies, 0, "Los Santos Vagos");//4
    AddMenuItem(mGangsVacancies, 0, "Da Nang Boys");//5
	AddMenuItem(mGangsVacancies, 0, "San Fierro Rifa");//6
    AddMenuItem(mGangsVacancies, 0, "The Traids");//7
    AddMenuItem(mGangsVacancies, 0, "Bikers");//8
	AddMenuItem(mGangsVacancies, 0, "The Mafia");//9
    AddMenuItem(mGangsVacancies, 0, "UnInvite");//10

	mVacancies = CreateMenuEx("Vacancies", 1, 10.0, 120.0, 100.0, 100.0);
	AddMenuItem(mVacancies, 0, "Road Police");//1
    AddMenuItem(mVacancies, 0, "FBI");//2
    AddMenuItem(mVacancies, 0, "National Guard");//3
	AddMenuItem(mVacancies, 0, "Ambulance");//4
    AddMenuItem(mVacancies, 0, "La Cosa Nostra");//5
	AddMenuItem(mVacancies, 0, "Yakuza");//6
    AddMenuItem(mVacancies, 0, "Government");//7
    AddMenuItem(mVacancies, 0, "Hitmans Agency");//8
	AddMenuItem(mVacancies, 0, "CNN Studio");//9
    AddMenuItem(mVacancies, 0, "License Faction");//10
    AddMenuItem(mVacancies, 0, "UnInvite");//11
    //--------------------------------------------------------------------------
	//	начало
	mClothMenu = CreateMenuEx("Cloth", 1, 10.0, 120.0, 100.0, 100.0);
    AddMenuItem(mClothMenu, 0, "Civilian");
    //AddMenuItem(mClothMenu, 0, "Female");
	AddMenuItem(mClothMenu, 0, "Organization");
    AddMenuItem(mClothMenu, 0, "Gangs");

	mMale = CreateMenuEx("Cloth", 1, 10.0, 120.0, 100.0, 100.0);
	SetMenuColumnHeader(mMale, 0, "Male Skin");
	AddMenuItem(mMale, 0, "BechVisitor");
	AddMenuItem(mMale, 0, "Homeless");
    AddMenuItem(mMale, 0, "Normal");
    AddMenuItem(mMale, 0, "Farmer");
    AddMenuItem(mMale, 0, "Sport");
    AddMenuItem(mMale, 0, "Public Service");
    AddMenuItem(mMale, 0, "Other");

	mFemale = CreateMenuEx("Cloth", 1, 10.0, 120.0, 100.0, 100.0);
	SetMenuColumnHeader(mFemale, 0, "Female Skin");
	AddMenuItem(mFemale, 0, "BechVisitor");
	AddMenuItem(mFemale, 0, "Homeless");
    AddMenuItem(mFemale, 0, "Normal");
	AddMenuItem(mFemale, 0, "Whore");
    AddMenuItem(mFemale, 0, "Farmer");
    AddMenuItem(mFemale, 0, "Girlfriend");
    AddMenuItem(mFemale, 0, "Public Service");
    AddMenuItem(mFemale, 0, "Other");

	mOrganization = CreateMenuEx("Cloth", 1, 10.0, 120.0, 100.0, 100.0);
    SetMenuColumnHeader(mOrganization, 0, "Forces Skin");
	AddMenuItem(mOrganization, 0, "Road Police");
	AddMenuItem(mOrganization, 0, "Federal Agents");
    AddMenuItem(mOrganization, 0, "National Guard");
	AddMenuItem(mOrganization, 0, "Ambulance Personnel");
	AddMenuItem(mOrganization, 0, "Fire Brigade");
	AddMenuItem(mOrganization, 0, "La Cosa Nostra");
	AddMenuItem(mOrganization, 0, "Yakuza");
    AddMenuItem(mOrganization, 0, "Government");
	AddMenuItem(mOrganization, 0, "Hitmans Agency");
	AddMenuItem(mOrganization, 0, "News Reporters");
	AddMenuItem(mOrganization, 0, "License Faction");

	mGangs = CreateMenuEx("Cloth", 1, 10.0, 120.0, 100.0, 100.0);
    SetMenuColumnHeader(mGangs, 0, "Gang Skin");
	AddMenuItem(mGangs, 0, "Grove Street");
	AddMenuItem(mGangs, 0, "The Ballas");
    AddMenuItem(mGangs, 0, "Varios Los Aztecas");
    AddMenuItem(mGangs, 0, "Los Santos Vagos");
    AddMenuItem(mGangs, 0, "Da Nang Boys");
	AddMenuItem(mGangs, 0, "San Fierro Rifa");
	AddMenuItem(mGangs, 0, "The Traids");
	AddMenuItem(mGangs, 0, "Biker");
    AddMenuItem(mGangs, 0, "The Mafia");

	mPaid = CreateMenuEx("Cloth", 1, 10.0, 120.0, 100.0, 100.0);
	SetMenuColumnHeader(mPaid,0, "Select Skin");
	AddMenuItem(mPaid,0, "Next");
	AddMenuItem(mPaid,0, "Buy $500");
	//для магазинов одежды конец
    //--------------------------------------------------------------------------
	//для тюнинга начало
	mTuningMenu = CreateMenuEx("Tuning",1,10.0,120.0,120.0,120.0);
	AddMenuItem(mTuningMenu,0, "Colour");
	AddMenuItem(mTuningMenu,0, "Paint Job");
	AddMenuItem(mTuningMenu,0, "Nitro");
	AddMenuItem(mTuningMenu,0, "Wheels");
	AddMenuItem(mTuningMenu,0, "Hydraulics");
	AddMenuItem(mTuningMenu,0, "Spoiler");
	AddMenuItem(mTuningMenu,0, "Front Bumper");
	AddMenuItem(mTuningMenu,0, "Rear Bumper");
	AddMenuItem(mTuningMenu,0, "Sideskirt");
	AddMenuItem(mTuningMenu,0, "Roof");
	AddMenuItem(mTuningMenu,0, "Exhaust");
	AddMenuItem(mTuningMenu,0, "Neon");

	mPaintJob = CreateMenuEx("Paint Job",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mPaintJob,0, "Improvements");
	AddMenuItem(mPaintJob,0, "Paint Job 1");
	AddMenuItem(mPaintJob,0, "Paint Job 2");
	AddMenuItem(mPaintJob,0, "Paint Job 3");
	//AddMenuItem(mPaintJob,0, "Paint Job 4");
	//AddMenuItem(mPaintJob,0, "Paint Job 5");
	//AddMenuItem(mPaintJob,0, "Paint Job 6");
	AddMenuItem(mPaintJob,0, "Buy $500");

	mColors = CreateMenuEx("Colour",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mColors,0, "Improvements");
	AddMenuItem(mColors,0, "Colour car 1");
	AddMenuItem(mColors,0, "Colour car 2");
	AddMenuItem(mColors,0, "Buy $150");

	/*mNitro = CreateMenuEx("Nitro",1,10.0,120.0,130.0,130.0);
	SetMenuColumnHeader(mNitro,0, "Improvements    Price");
	AddMenuItem(mNitro,0, "Nitric Booster 2x $200");
	AddMenuItem(mNitro,0, "Nitric Booster 5x $770");
	AddMenuItem(mNitro,0, "Nitric Booster 10x $1000");*/
	mNitro = CreateMenuEx("Nitro",2,10.0,120.0,80.0,80.0);
	SetMenuColumnHeader(mNitro,0, "Improvements");
	SetMenuColumnHeader(mNitro,1, "        Price");
	AddMenuItem(mNitro,0, "Nitric Booster 2x");
	AddMenuItem(mNitro,1, "        $200");
	AddMenuItem(mNitro,0, "Nitric Booster 5x");
	AddMenuItem(mNitro,1, "        $770");
	AddMenuItem(mNitro,0, "Nitric Booster 10x");
	AddMenuItem(mNitro,1, "        $1000");

	mWheels = CreateMenuEx("Wheels",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mWheels,0, "Improvements");
	AddMenuItem(mWheels,0, "Next");
	AddMenuItem(mWheels,0, "Buy $770");

	mHydraulics = CreateMenuEx("Hydraulics",2,10.0,120.0,80.0,80.0);
	SetMenuColumnHeader(mHydraulics,0, "Improvements");
	SetMenuColumnHeader(mHydraulics,1, "        Price");
	AddMenuItem(mHydraulics,0, "Hydraulics");
	AddMenuItem(mHydraulics,1, "        $1500");

	mSpoiler = CreateMenuEx("Spoiler",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mSpoiler,0, "Improvements");
	AddMenuItem(mSpoiler,0, "Alien");
	AddMenuItem(mSpoiler,0, "X-Flow");
	AddMenuItem(mSpoiler,0, "Buy $550");

	mFrontBumper = CreateMenuEx("Bumper",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mFrontBumper,0, "Improvements");
	AddMenuItem(mFrontBumper,0, "Alien");
	AddMenuItem(mFrontBumper,0, "X-Flow");
	AddMenuItem(mFrontBumper,0, "Buy $950");

	mRearBumper = CreateMenuEx("Bumper",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mRearBumper,0, "Improvements");
	AddMenuItem(mRearBumper,0, "Alien");
	AddMenuItem(mRearBumper,0, "X-Flow");
	AddMenuItem(mRearBumper,0, "Buy $950");

	mSideskirt = CreateMenuEx("Sideskirt",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mSideskirt,0, "Improvements");
	AddMenuItem(mSideskirt,0, "Alien");
	AddMenuItem(mSideskirt,0, "X-Flow");
	AddMenuItem(mSideskirt,0, "Buy $450");

	mRoof = CreateMenuEx("Roof",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mRoof,0, "Improvements");
	AddMenuItem(mRoof,0, "Alien");
	AddMenuItem(mRoof,0, "X-Flow");
	AddMenuItem(mRoof,0, "Buy $150");

	mExhaust = CreateMenuEx("Exhaust",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mExhaust,0, "Improvements");
	AddMenuItem(mExhaust,0, "Alien");
	AddMenuItem(mExhaust,0, "X-Flow");
	AddMenuItem(mExhaust,0, "Buy $650");

	/*mOthers = CreateMenuEx("Others",1,10.0,120.0,120.0,120.0);
	AddMenuItem(mOthers,0, "Front Bullbars");
	AddMenuItem(mOthers,0, "Rear Bullbars");
	AddMenuItem(mOthers,0, "Hood");
	AddMenuItem(mOthers,0, "Vents");
	AddMenuItem(mOthers,0, "Lamps");*/

	mNeon = CreateMenuEx("Neon",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mNeon,0, "Improvements");
	AddMenuItem(mNeon,0, "Next");
	AddMenuItem(mNeon,0, "Buy $1500");
	
	/*mBullbarsFront = CreateMenuEx("Bullbars",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mBullbarsFront,0, "Improvements");
	AddMenuItem(mBullbarsFront,0, "Alien");
	AddMenuItem(mBullbarsFront,0, "X-Flow");
	AddMenuItem(mBullbarsFront,0, "Buy $950");

	mBullbarsRear = CreateMenuEx("Bullbars",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mBullbarsRear,0, "Improvements");
	AddMenuItem(mBullbarsRear,0, "Alien");
	AddMenuItem(mBullbarsRear,0, "X-Flow");
	AddMenuItem(mBullbarsRear,0, "Buy $950");

	mHood = CreateMenuEx("Hood",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mHood,0, "Improvements");
	AddMenuItem(mHood,0, "Alien");
	AddMenuItem(mHood,0, "X-Flow");
	AddMenuItem(mHood,0, "Buy $150");

	mVents = CreateMenuEx("Vents",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mVents,0, "Improvements");
	AddMenuItem(mVents,0, "Alien");
	AddMenuItem(mVents,0, "X-Flow");
	AddMenuItem(mVents,0, "Buy $150");

	mLamps = CreateMenuEx("Lamps",1,10.0,120.0,120.0,120.0);
	SetMenuColumnHeader(mLamps,0, "Improvements");
	AddMenuItem(mLamps,0, "Alien");
	AddMenuItem(mLamps,0, "X-Flow");
	AddMenuItem(mLamps,0, "Buy $150");//для тюнинга конец*/

	//для меню конец
	printf("7/19. [Загрузка меню]: Было загружено - %d, потрачено - %d (ms)", MenuCounter, (GetTickCount()-time));
}









//stock UnLoadMenus()
stock menu_OnGameModeExit()
{
	DestroyMenuEx(mBank);
	DestroyMenuEx(mAmmuNation);
	DestroyMenuEx(mOtherAmmuNation);
	DestroyMenuEx(mPoliceDepartment);

	DestroyMenuEx(mBar);
	DestroyMenuEx(mRestaurant);
	DestroyMenuEx(mBurgerShot);
	DestroyMenuEx(mCluckinBell);
	DestroyMenuEx(mStackedPizza);

	DestroyMenuEx(mJobMenu1_9);//для устройства на работу
	DestroyMenuEx(mJobMenu10_19);//для устройства на работу
	DestroyMenuEx(mGangsVacancies);
	DestroyMenuEx(mVacancies);//для автоназначения лидеров

	DestroyMenuEx(mClothMenu);
	DestroyMenuEx(mMale);
	DestroyMenuEx(mFemale);
	DestroyMenuEx(mOrganization);
	DestroyMenuEx(mGangs);
	DestroyMenuEx(mPaid);

	DestroyMenuEx(mTuningMenu);
	DestroyMenuEx(mColors);
	DestroyMenuEx(mPaintJob);
	DestroyMenuEx(mNitro);
	DestroyMenuEx(mWheels);
	DestroyMenuEx(mHydraulics);
	DestroyMenuEx(mSpoiler);
	DestroyMenuEx(mFrontBumper);
	DestroyMenuEx(mRearBumper);
	DestroyMenuEx(mSideskirt);
	DestroyMenuEx(mRoof);
	DestroyMenuEx(mExhaust);
	DestroyMenuEx(mNeon);

	DestroyMenuEx(mPunish);
}


forward Menu: CreateMenuEx(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width);
public Menu:CreateMenuEx(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width)
{
	MenuCounter++;
	return CreateMenu(title, columns, x, y, col1width, col2width);
}

forward DestroyMenuEx(Menu:menuid);
public DestroyMenuEx(Menu:menuid)
{
	MenuCounter--;
	return DestroyMenu(menuid);
}

stock ShowMenuForPlayerEx(Menu:menuid, playerid)
{
	/*if(CHECKING[PlayerSelectedMenuRow])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "ShowMenuForPlayerEx(menuid:%d, playerid:%d) ShowMenu:%d", menuid, playerid, GetPVarInt(playerid, "ShowMenu"));
		SendClientMessage(playerid, COLOR_PURPLE, strings);
	}*/
		
	if(!IsPlayerConnected(playerid)) return 0;
	//if(IsValidMenu(menuid))
	//if(GetPVarInt(playerid, "ShowMenu") == 1) SetPVarInt(playerid, "ShowMenu", 1); HideMenuForPlayer(menuid, playerid);
	if(GetPVarInt(playerid, "ShowMenu") == 0)
	{
	//format(strings, sizeof(strings), "ShowMenuForPlayerEx(playerid:%d)", playerid);
	//SendClientMessage(playerid, COLOR_PURPLE, strings);
	
		//HideTextDrawShowScale(playerid);
		/*if(GetPlayerMoneyH(playerid) <= 0) {
			//ShowMenuForPlayerEx(menuid, playerid);
//если игроку меню не показалось, т.к. нету денег, то размарозить
			TogglePlayerControllableEx(playerid, 1);//освободить
			return 0;
		}*/
		SetPVarInt(playerid, "ShowMenu", 1);
		return ShowMenuForPlayer(menuid, playerid);
	}
	return 0;
}
stock HideMenuForPlayerEx(Menu:menuid, playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	//if(IsValidMenu(menuid))
	if(GetPVarInt(playerid, "ShowMenu") == 1)
	{
		//HideTextDrawShowScale(playerid);
		SetPVarInt(playerid, "ShowMenu", 0);
		return HideMenuForPlayer(menuid, playerid);
	}
	return 0;
}
