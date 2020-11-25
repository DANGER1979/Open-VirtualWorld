//https://youtu.be/Ts8J8u3jQuw
//Personality Accessories

//AddPlayerClass(133,445.1453,502.3073,1001.4495,98.0743,0,0,0,0,0,0); // acces min
//AddPlayerClass(133,456.4319,515.8829,1006.4753,333.0531,0,0,0,0,0,0); // acces max

//надо добавить объекты https://dev.prineside.com/ru/gtasa_samp_model_id/tag/260-sa-mp-0-3c-rc4/
//19469, 19085, 19555

#include "../include/textdraw/txd_Accessories.pwn"

#define SCMF(%0,%1,%2,%3) 		format(format_string, 144, %2,%3) && SendClientMessage(%0, %1, format_string)
new format_string [144];


//new PlayerText:mask_PTD[MAX_PLAYERS];

//new open_you_baners[MAX_PLAYERS char];

// система покупки скинов
new accShowSkin[MAX_PLAYERS];
new skins_shop[MAX_PLAYERS];//если делать скины на диалогах
// система аксессуаров
new timetobuy2[MAX_PLAYERS];
#define MAX_INV_TYPE 471
enum InvTypeInfo
{
	invMax,
	invObj,
	invDropObj,
	bool:invUsed,
	invTitle[25],
	invText[128],
	Float:invRot[4],
	Float:invDropParam[6],
	bool:invOnDrop
}

new ItemsId[][] =
{
	{ 19423, 19424, 19421, 19422,1}, //Наушники
	{ 18953, 18954,1},//Шапки
	{ 18969, 18968, 18967,1},//Панамки
	{ 18933, 18929, 18030, 18931, 18932, 18934, 18935,1},//Кепки
	{ 19107, 19108, 19109, 19110, 19111, 19112,1},//Каски
	{ 18921, 18922, 18923, 18924, 18925,1},//Береты
	{ 19274, 19518, 19519,1},//Парики
	{ 19006, 19007, 19008, 19009, 19010, 19011, 19012, 19013, 19014,
	19015, 19016, 19017, 19018, 19019, 19020, 19021, 19022,
	19023, 19024, 19025, 19026, 19027, 19028, 19029, 19030,
	19031, 19032, 19033, 19034, 19035, 19138, 19139,1},//Очки
	{ 18919, 18912, 18913, 18914, 18915, 18916,
	18917, 18918, 18911, 18920,1 }, //Банданы
	{ 18947, 18948, 18949, 18950, 18951, 19488,1 }, //Шляпы
	{ 19039, 19042, 19053, 19052, 19051, 19050, 19049, 19048, 19047, 19046, 19045, 19044, 19043, 19041, 19040,1 }, //Часы
	{ 19559,19624, 11745, 1210,1 },//портфели
	{ 19317, 19318, 19319,1 }//гитары
};
// цена за аксессуары
new ItemsCost[][] =
{
	{ 20,30,25,30,1}, //Наушники
	{ 20,20,1},//Шапки
	{ 15,15,15,1},//Панамки
	{ 10,10,10,20,20,15,1},//Кепки
	{ 25,25,30,30,30,30,1},//Каски
	{ 20,22,22,20,30,1},//Береты
	{ 30,30,30,1},//Парики
	{ 50,20,50,70,12,18,28,28,28,30,30,30,30,30,20,21,210,40,70,70,70,70,70,70,70,70,70,70,70,70,70,70,1},//Очки
	{ 20,10,10,17,17,17,13,10,10,17,1 }, //Банданы
	{ 21,21,21,21,21,21,1 }, //Шляпы
	{ 40,30,45,50,60,40,40,40,50,55,50,52,54,50,50,1 }, //Часы
	{ 400,400,400,400,1},//портфели
	{ 700,700,700,1}//гитары
};
static const stock Float:accCamPos[][] =
{
	{444.9884, 513.2505, 1001.9797, 444.9812, 514.2491, 1001.9891}, // головные уборы
	{444.9503, 513.8736, 1001.7573, 444.9014, 514.8711, 1001.5515}, // руки
	{446.8735, 515.3788, 1001.7285, 445.8989, 515.5946, 1001.452} // сумки
};
new Buyitem[MAX_PLAYERS] = {-1, ...};
//new fix_t_cell[MAX_PLAYERS];
new accCheck[MAX_PLAYERS];
new accCam[MAX_PLAYERS];
new accShowTD[MAX_PLAYERS];

const max_items = 29;
new items_name[max_items][30] =
{
	{"GPS"},
	{"Наркотики"},
	{"Сигары"},
	{"Игральные кости"},
	{"Канистры"},
	{"Радио"},
	{"Цыплёнок"},
	{"Гамбургер"},
	{"Пицца"},
	{"Пиво"},
	{"Доставка транспорта"},
	{"Головной убор"}, // 0
	{"Очки"}, // 1
	{"Часы"}, // 2
	{"Бандана"}, // 3
	{"Наушники"}, // 4
	{"Сумка/гитара"}, // 5
	{"Материалы"},
	{"Грибы"},
	{"Лотерейки"},
	{"Шлем"},
	{"Отмычки"},
	{"Антирадар"},
	{"Телефон"},
	{"Адреналин"},
	{"Аптечки"},
	{"Патроны"},
	{"Рыба"}, //27
	{"Маски"}
};
/*new items_max[max_items] =
{
	1, // gps
	100, // нарко
	3, // ссигары
	5,
	5,
	1,
	5,
	5,
	5,
	5,
	5,
	0,
	0,
	0,
	0,
	0,
	0,
	5000,
	5,
	5,
	5,
	0,
	1,
	1,
	0,
	5,
	5,
	5000,
	3
};*/
new ITEMS_SLOT[MAX_PLAYERS][max_items];
//new items_select[MAX_PLAYERS];
//new mMaskedTimer[MAX_PLAYERS];

// координаты новых пикапов (НЕ ЗАБЫВАТЬ ПОМЕЩАТЬ ТИП ПИКАПА В МАССИВ n_CreatePickup_cords_check)
//new check_new_cp[MAX_PLAYERS];
const MAX_FOREACH_N_PICKUP = 18;
// [ Типы пикапов ]
// 0 - банк
static const stock n_CreatePickup_cords_check[MAX_FOREACH_N_PICKUP] =
{
	0,
	0,
	0,
	0,
	0,
	0,
	1,//6
	2,//7
	3,
	4,
	6,
	7,//11
	999,
	999,
	14, // lcn
	15, // yakuza
	16,
	16
};
static const stock Float:n_CreatePickup_cords[MAX_FOREACH_N_PICKUP][3] =
{
	//банк
	{-1524.12146, 758.82251, 1039.02136},
	{-1525.41199, 763.32660, 1039.02136},
	{-1524.10425, 767.85260, 1039.02136},
	{-1503.69934, 767.89929, 1039.02136},
	{-1502.35913, 763.45551, 1039.02136},
	{-1503.61084, 758.98456, 1039.02136},
	//общаки банд
	{-35.90501, -827.14844, 1014.55237}, // грув
	{895.50427, -1145.11157, 1025.19165}, // баллас
	{-1975.47571, 1062.39514, 1061.25012}, //ацтек
	{340.22153, -1586.51611, 1036.79150}, // Вагос
	{-2599.85449, -29.44750, 1005.1467}, // рифа
	{452.20410, 512.34918, 999.49731}, //типа пикап объект 1317 в магазине аксессуаров
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	//общаки мафий
	{1407.17810, -3.37890, 998.98474},// лкн
	{-2160.23828, 646.36462, 1055.73718},//якудза
	{1404.97986, -6.91014, 998.98474}, // лкн второй чекпоинт
	{-2160.29883, 639.83508, 1055.68616} // якудза второй чекпоинт
};

stock n_CreatePickup(Float:x, Float:y, Float:z)
{
	new sync_object = CreateDynamicObject(1317, x,y,z, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	return SetDynamicObjectMaterial(sync_object, 0, 19655, "mattubes", "bluedirt1", 0x00000000);
}

stock access_OnGameModeInit()
{
	LoadAccTD();

	for(new i; i < MAX_FOREACH_N_PICKUP; i ++)
	{
	    n_CreatePickup(n_CreatePickup_cords[i][0], n_CreatePickup_cords[i][1], n_CreatePickup_cords[i][2]);
	}
	
	print("   Система аксессуаров 1.0 by DANGER1979");
	print("_____________________________________________");
	print(" ");
}


stock access_OnPlayerConnect(playerid)
{
	LoadAccPTD(playerid);
	
	//магазин аксессуаров
	RemoveBuildingForPlayerEx(playerid, 1743, 443.882, 513.781, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1740, 446.539, 513.750, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1794, 447.414, 512.671, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1740, 449.328, 513.734, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 14479, 450.257, 516.390, 1002.059, 0.250);
	RemoveBuildingForPlayerEx(playerid, 14482, 450.390, 516.390, 1001.849, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1743, 451.328, 515.843, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1786, 452.546, 515.031, 1001.659, 0.250);
	RemoveBuildingForPlayerEx(playerid, 14481, 457.148, 515.015, 1002.260, 0.250);
	RemoveBuildingForPlayerEx(playerid, 14480, 456.171, 514.125, 1001.010, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1738, 454.031, 511.804, 1001.059, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1744, 452.960, 511.781, 1001.260, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1759, 451.539, 507.531, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 2236, 450.109, 508.625, 1000.400, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1763, 448.406, 507.562, 1000.409, 0.250);
	RemoveBuildingForPlayerEx(playerid, 1759, 443.937, 507.335, 1000.409, 0.250);
}

stock access_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == Accessories[8]) // кнопка вперёд
	{
		if(accShowSkin[playerid] == 1)
		{
		    SkinShopNext(playerid);
		}
	    if(accShowTD[playerid] == 1)
		{
			next_item(playerid);
		}
		/*if(open_you_baners[playerid] == 1)
		{
		    BannerNext(playerid);
		    NextBanner(playerid, __Player_ID_Banner[playerid]);
		}*/
	}
	else if(clickedid == Accessories[16]) // кнопка купить
	{
	    if(accShowTD[playerid] == 1)
	    {
	        BuyItemss(playerid);
		}
		if(accShowSkin[playerid] == 1)
		{
		    BuySkinShop(playerid);
		}
		/*if(open_you_baners[playerid] == 1)
		{
		    BannerBuy(playerid);
		}*/
	}
	else if(clickedid == Accessories[15]) // кнопка выход
	{
	    if(accShowTD[playerid] == 1)
	    {
			HIDE_ACCSES_SELECT(playerid);
			ResetAcc(playerid);
			STOP_ACCSES(playerid);
			START_ACCSES(playerid);
		}
		if(accShowSkin[playerid] == 1)
		{
            HideSkinSelect(playerid);
		   	ShowSkinShop1(playerid);
		}
 		/*if(open_you_baners[playerid] == 1)
		{
		    StopBanners(playerid);
		}*/
	}
	else if(clickedid == Accessories[7]) // кнопка назад
	{
		if(accShowSkin[playerid] == 1)
		{
		    SkinShopBack(playerid);
		}
	    if(accShowTD[playerid] == 1)
		{
			back_item(playerid);
		}
  		/*if(open_you_baners[playerid] == 1)
		{
		    BannerBack(playerid);
		    NextBanner(playerid, __Player_ID_Banner[playerid]);
		}*/
	}
	else if(_:clickedid == INVALID_TEXT_DRAW)
	{
		HideTD(playerid);
	}
    return 0;
}



stock access_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	//==========================================================================
	switch(dialogid)
	{
		case d_accses4:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0:
				    {
				        if(PlayerInfo[playerid][pOther][PlayerInfo[playerid][pType2] + 11] == 0) return n_items(playerid);
				        switch(PlayerInfo[playerid][pType2])
		                {
		                    case 0: if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid, 0); else AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][11]);
		                    case 1: if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1); else AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][12]);
							case 2: if(IsPlayerAttachedObjectSlotUsed(playerid, 2)) RemovePlayerAttachedObject(playerid, 2); else AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][13]);
							case 3: if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) RemovePlayerAttachedObject(playerid, 3); else AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][14]);
							case 4: if(IsPlayerAttachedObjectSlotUsed(playerid, 4)) RemovePlayerAttachedObject(playerid, 4); else AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][15]);
							case 5: if(IsPlayerAttachedObjectSlotUsed(playerid, 5)) RemovePlayerAttachedObject(playerid, 5); else AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][16]);
		                }
					}
					case 1:
					{
				        switch(PlayerInfo[playerid][pType2])
		                {
		                    case 0: if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid, 0);
		                    case 1: if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
							case 2: if(IsPlayerAttachedObjectSlotUsed(playerid, 2)) RemovePlayerAttachedObject(playerid, 2);
							case 3: if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) RemovePlayerAttachedObject(playerid, 3);
							case 4: if(IsPlayerAttachedObjectSlotUsed(playerid, 4)) RemovePlayerAttachedObject(playerid, 4);
							case 5: if(IsPlayerAttachedObjectSlotUsed(playerid, 5)) RemovePlayerAttachedObject(playerid, 5);
		                }
		                PlayerInfo[playerid][pOther][PlayerInfo[playerid][pType2] + 11]=0;
					    UpdatePlayerDataH(playerid, "SlotItem0", PlayerInfo[playerid][pOther][11]);
					    UpdatePlayerDataH(playerid, "SlotItem1", PlayerInfo[playerid][pOther][12]);
					    UpdatePlayerDataH(playerid, "SlotItem2", PlayerInfo[playerid][pOther][13]);
					    UpdatePlayerDataH(playerid, "SlotItem3", PlayerInfo[playerid][pOther][14]);
					    UpdatePlayerDataH(playerid, "SlotItem4", PlayerInfo[playerid][pOther][15]);
					    UpdatePlayerDataH(playerid, "SlotItem5", PlayerInfo[playerid][pOther][16]);
		                ApplyAnimation(playerid, "goggles", "goggles_put_on",4.1,0,0,0,0,0,1);
		                n_items(playerid);
					}
				}
			}
			else n_items(playerid);

			PlayerInfo[playerid][pType2] = -1;
		}
		case d_accses2:
		{
			if(response)
			{
		        PlayerInfo[playerid][pType] = listitem;
		  		switch(listitem)
		        {
		            case 0: PlayerInfo[playerid][pType2] = 4;
					// [ шапки ]
		            case 1: PlayerInfo[playerid][pType2] = 0;
		            case 2: PlayerInfo[playerid][pType2] = 0;
		            case 3: PlayerInfo[playerid][pType2] = 0;
		            case 4: PlayerInfo[playerid][pType2] = 0;
		            case 5: PlayerInfo[playerid][pType2] = 0;
		            case 6: PlayerInfo[playerid][pType2] = 0;
		            case 7: PlayerInfo[playerid][pType2] = 1;
		            case 8: PlayerInfo[playerid][pType2] = 3;
		            case 9: PlayerInfo[playerid][pType2] = 0;
		            case 10: PlayerInfo[playerid][pType2] = 2;
		            case 11: PlayerInfo[playerid][pType2] = 5;
		            case 12: PlayerInfo[playerid][pType2] = 5;
		        }
		  		SetPlayerBuyItem(playerid);
			}
			else
			{
				HideTD(playerid);
				STOP_ACCSES(playerid);
			}
			return true;
		}
	    case d_accses1:
	    {
	        if(response) START_ACCSES(playerid);
	    }
	}
	return 1;
}

stock DefaultSkin(playerid)
{
	if(PlayerInfo[playerid][pSex] == Male)
		return 26;

	else if(PlayerInfo[playerid][pSex] == Female)
		return 41;

	return 0;
}



stock access_OnPlayerKeyState_YES(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.0, 452.2041,512.3492,1001.4495)) {
	//if(check_new_cp[playerid] != -1) return 1;
	/*for(new i; i < MAX_FOREACH_N_PICKUP; i ++)
	{
	    if(!IsPlayerInRangeOfPoint(playerid, 3.0, n_CreatePickup_cords[i][0],n_CreatePickup_cords[i][1], n_CreatePickup_cords[i][2])) continue;
        if(n_CreatePickup_cords_check[i] == 999) continue;
        check_new_cp[playerid] = i;
		if(n_CreatePickup_cords_check[i] != 7) continue;*/
		ShowPlayerDialogEx(playerid, d_accses1, DIALOG_STYLE_MSGBOX, "Аксессуары | {DC143C}Покупка", "Вы действительно хотите перейти к покупке аксессуаров?", "Принять", "Отмена");
	}
	return 1;
}

stock Dialog_ACCSES(playerid)
{
	//if(n_CreatePickup_cords_check[i] == 7)
	//{

	//}
}

stock START_ACCSES(playerid)
{//вызывается из SHOW_ACCSES_SELECT <- SetPlayerBuyItem(playerid) <- access_OnDialogResponse
	if(accCheck[playerid] == 1) return SendClientMessage(playerid, COLOR_ERROR, "Сначала закончите сеанс покупки аксессуаров");
	accCam[playerid] = 0;
	SetPlayerPosEx(playerid, 444.9340,515.6989,1001.4495,182.8980);// тпшим игрока перед зеркалом

	//устанавливаем координаты камеры
	SetPlayerCameraPos(playerid, accCamPos[accCam[playerid]][0], accCamPos[accCam[playerid]][1], accCamPos[accCam[playerid]][2]);
	SetPlayerCameraLookAt(playerid, accCamPos[accCam[playerid]][3], accCamPos[accCam[playerid]][4], accCamPos[accCam[playerid]][5]);
//остальное
	accCheck[playerid] = 1; // Устанавливаем то, что игрок покупает аксессуар
	TogglePlayerControllableEx(playerid, 0); // Заморозим игрока
	//SetPlayerInteriorEx(playerid, 8);
	//SetPlayerVirtualWorldEx(playerid, 90);
/*
		            case 0: PlayerInfo[playerid][pType2] = 4;
					// [ шапки ]
		            case 1: PlayerInfo[playerid][pType2] = 0;
		            case 2: PlayerInfo[playerid][pType2] = 0;
		            case 3: PlayerInfo[playerid][pType2] = 0;
		            case 4: PlayerInfo[playerid][pType2] = 0;
		            case 5: PlayerInfo[playerid][pType2] = 0;
		            case 6: PlayerInfo[playerid][pType2] = 0;
		            case 7: PlayerInfo[playerid][pType2] = 1;
		            case 8: PlayerInfo[playerid][pType2] = 3;
		            case 9: PlayerInfo[playerid][pType2] = 0;
		            case 10: PlayerInfo[playerid][pType2] = 2;
		            case 11: PlayerInfo[playerid][pType2] = 5;
		            case 12: PlayerInfo[playerid][pType2] = 5;
*/
    Buyitem[playerid] = 0;
	ShowPlayerDialogEx(playerid, d_accses2, DIALOG_STYLE_TABLIST,"Аксессуары | {DC143C}Покупка",
"- Наушники\n- Шапки\n- Панамки\n- Кепки\n- Каски\n- Береты\n- Парики\n- Очки\n- Банданы\n- Шляпы\n- Часы\n- Сумки\n- Гитары","Принять","Отмена");
	return 1;
}
stock START_ACCSES1(playerid)
{
    if(accCheck[playerid] == 1) return SendClientMessage(playerid, COLOR_ERROR, "Сначала закончите сеанс покупки аксессуаров");
	return 1;
}

stock STOP_ACCSES(playerid)
{
    if(accCheck[playerid] == 0) return 1;
	//SetPlayerInteriorEx(playerid, 8);
	//SetPlayerVirtualWorldEx(playerid, 90);
    SetPlayerPosEx(playerid, 452.2041,512.3492,1001.4495,0.0);

	SetPlayerTime(playerid, 12, 0);
	SetPlayerWeather(playerid, 6);

    TogglePlayerControllableEx(playerid, 1); // Разморозим игрока
    SetCameraBehindPlayer(playerid);
    
	ResetAcc(playerid);
	
    Buyitem[playerid] = -1;
	accCheck[playerid] = 0;
	timetobuy2[playerid] = 0;
	timetobuy2[playerid] = 0;
	return 1;
}
stock ResetAcc(playerid)
{
	for(new i; i < 6; i ++)
	{
	    RemovePlayerAttachedObject(playerid, i);
	    if(PlayerInfo[playerid][pOther][11 + i] != 0)
	    {
	        AttachObjectToSkin(playerid,PlayerInfo[playerid][pOther][11 + i]);
	    }
	}
	return 1;
}
stock SetPlayerBuyItem(playerid)
{//вызывается из access_OnDialogResponse
    SHOW_ACCSES_SELECT(playerid);
	return true;
}

stock HIDE_ACCSES_SELECT(playerid)
{
	if(accShowTD[playerid] == 0) return true;
	for(new i; i < 34; i ++)
	{
	    TextDrawHideForPlayer(playerid, Accessories[i]);
	}
	PlayerTextDrawHide(playerid, AccessoriesP[playerid]);
	CancelSelectTextDraw(playerid);
	accShowTD[playerid] = 0;
	return true;
}
stock SHOW_ACCSES_SELECT(playerid)
{//вызывается из SetPlayerBuyItem(playerid) <- access_OnDialogResponse
	if(accShowTD[playerid] == 1) return true;
	if(AttachObjectToSkin(playerid, ItemsId[ PlayerInfo[playerid][pType] ] [Buyitem[playerid]]) == -1)
	{
	    accCheck[playerid] = 0;
	    ResetAcc(playerid);
		START_ACCSES(playerid);
		return 1;
	}
	for(new i; i < 34; i ++)
	{
	    TextDrawShowForPlayer(playerid, Accessories[i]);
	}
	PlayerTextDrawShow(playerid, AccessoriesP[playerid]);
	SelectTextDraw(playerid, 0xFF0000FF);
	accShowTD[playerid] = 1;
	switch(PlayerInfo[playerid][pType2])
	{
	    case 2:
	    {
			SetPlayerCameraPos(playerid, accCamPos[1][0], accCamPos[1][1], accCamPos[1][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[1][3], accCamPos[1][4], accCamPos[1][5]);
	    }
	    case 5:
	    {
			SetPlayerCameraPos(playerid, accCamPos[2][0], accCamPos[2][1], accCamPos[2][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[2][3], accCamPos[2][4], accCamPos[2][5]);
	    }
	    default:
	    {
			SetPlayerCameraPos(playerid, accCamPos[0][0], accCamPos[0][1], accCamPos[0][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[0][3], accCamPos[0][4], accCamPos[0][5]);
	    }
	}
	new price = ItemsCost[PlayerInfo[playerid][pType]][Buyitem[playerid]];
    AttachObjectToSkin(playerid, ItemsId[ PlayerInfo[playerid][pType] ] [Buyitem[playerid]] );
    new string[10];
	format(string, sizeof(string), RusToGame("$%d"), price);
	PlayerTextDrawSetString(playerid, AccessoriesP[playerid], string);
	return true;
}
stock next_item(playerid)
{//вызывается из access_OnPlayerClickTextDraw
    if(accShowTD[playerid] == 0) return true;

    new string[124];
	if(ItemsId[PlayerInfo[playerid][pType]][Buyitem[playerid]+1]==1) return 0;
	if(AttachObjectToSkin(playerid, ItemsId[ PlayerInfo[playerid][pType] ] [Buyitem[playerid]]) == -1)
	{
	    accCheck[playerid] = 0;
	    ResetAcc(playerid);
		START_ACCSES(playerid);
		return 1;
	}
	Buyitem[playerid] ++;
	new price = ItemsCost[PlayerInfo[playerid][pType]][Buyitem[playerid]];
	AttachObjectToSkin(playerid, ItemsId[ PlayerInfo[playerid][pType] ] [Buyitem[playerid]] );
	format(string, sizeof(string), RusToGame("$%d"), price);
	PlayerTextDrawSetString(playerid, AccessoriesP[playerid], string);
	switch(PlayerInfo[playerid][pType2])
	{
	    case 2:
	    {
			SetPlayerCameraPos(playerid, accCamPos[1][0], accCamPos[1][1], accCamPos[1][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[1][3], accCamPos[1][4], accCamPos[1][5]);
	    }
	    case 5:
	    {
			SetPlayerCameraPos(playerid, accCamPos[2][0], accCamPos[2][1], accCamPos[2][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[2][3], accCamPos[2][4], accCamPos[2][5]);
	    }
	    default:
	    {
			SetPlayerCameraPos(playerid, accCamPos[0][0], accCamPos[0][1], accCamPos[0][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[0][3], accCamPos[0][4], accCamPos[0][5]);
	    }
	}
	return true;
}
stock back_item(playerid)
{//вызывается из access_OnPlayerClickTextDraw
    if(accShowTD[playerid] == 0) return true;
    new string[124];
	if(ItemsId[PlayerInfo[playerid][pType]][Buyitem[playerid]-1]==1) return 0;
	if(AttachObjectToSkin(playerid, ItemsId[ PlayerInfo[playerid][pType] ] [Buyitem[playerid]]) == -1)
	{
	    accCheck[playerid] = 0;
	    ResetAcc(playerid);
		START_ACCSES(playerid);
		return 1;
	}
	Buyitem[playerid] --;
	new price = ItemsCost[PlayerInfo[playerid][pType]][Buyitem[playerid]];
	AttachObjectToSkin(playerid, ItemsId[ PlayerInfo[playerid][pType] ] [Buyitem[playerid]] );
	format(string, sizeof(string), RusToGame("$%d"), price);
	PlayerTextDrawSetString(playerid, AccessoriesP[playerid], string);
	switch(PlayerInfo[playerid][pType2])
	{
	    case 2:
	    {
			SetPlayerCameraPos(playerid, accCamPos[1][0], accCamPos[1][1], accCamPos[1][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[1][3], accCamPos[1][4], accCamPos[1][5]);
	    }
	    case 5:
	    {
			SetPlayerCameraPos(playerid, accCamPos[2][0], accCamPos[2][1], accCamPos[2][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[2][3], accCamPos[2][4], accCamPos[2][5]);
	    }
	    default:
	    {
			SetPlayerCameraPos(playerid, accCamPos[0][0], accCamPos[0][1], accCamPos[0][2]);
			SetPlayerCameraLookAt(playerid, accCamPos[0][3], accCamPos[0][4], accCamPos[0][5]);
	    }
	}
	return true;
}


stock n_items(playerid)
{
	strings = "Название\tКол-во\n"; new check_slot = 1;
	for(new i; i < max_items; i ++)
	{
	    ITEMS_SLOT[playerid][i] = -1;
	}
	for(new i; i < max_items; i ++)
	{
	    IsAtAccses(i);
	    new idx[40];
	    if(i == 0)
	    {
	        strcat(strings, "GPS\t{59A951}Имеется\n");
	    }
		ITEMS_SLOT[playerid][0] = 0;
		if(PlayerInfo[playerid][pOther][i] != 0)
		{
			if(i == 11 || i == 12 || i == 13 || i == 14 || i == 15 || i == 16 || i == 20 || i == 23 || i == 19)
			{
				format(idx, sizeof idx, "%s\t%s\n", items_name[i], (PlayerInfo[playerid][pOther][i] == 0) ? ("{DC143C}Не имеется") : ("{59A951}Имеется"));
				strcat(strings, idx);
			}
			else
			{
				format(idx, sizeof idx, "%s\t%d\n", items_name[i], PlayerInfo[playerid][pOther][i]);
				strcat(strings, idx);
			}
            ITEMS_SLOT[playerid][check_slot] = i; // запишем номер слота
            check_slot ++;
		}
	}
	ShowPlayerDialogEx(playerid, d_items1, DIALOG_STYLE_TABLIST_HEADERS, "Выберите", strings, "Выбрать", "Отмена");
	return true;
}
stock IsAtAccses(w)
{
	if(w == 11 || w == 12 || w == 13 || w == 14 || w == 15 || w == 16) return 1;
	return 0;
}



stock BuyItemss(playerid)
{//вызывается из access_OnPlayerClickTextDraw
    new race = PlayerInfo[playerid][pType], slot = PlayerInfo[playerid][pType2], price = ItemsCost[race][Buyitem[playerid]];
    new item = ItemsId[race][Buyitem[playerid]];//,skin = GetPlayerSkin(playerid);
    if(PlayerInfo[playerid][pCash]<price)return SendClientMessage(playerid, COLOR_ERROR, "У вас недостаточно денег");
    if(AttachObjectToSkin(playerid, item) == -1)
    {
	    accCheck[playerid] = 0;
	    ResetAcc(playerid);
		START_ACCSES(playerid);
		return 1;
    }
	if(PlayerInfo[playerid][pOther][slot + 11] != 0 && timetobuy2[playerid] == 0)
	{
		timetobuy2[playerid] = 1;
		SCMF(playerid, 0xE9E44BFF, "У вас имеется такой предмет в {32CD32}%d{E9E44B} слоте. Нажмите 'Купить' еще раз, Чтобы заменить старый.", slot);
		return 0;
	}
    AttachObjectToSkin(playerid,item);
    SendClientMessage(playerid, -1, "Спасибо за покупку, приходите еще!");
    ApplyAnimation(playerid,"goggles","goggles_put_on",4.1,0,0,0,0,0,1);
    UpdatePlayerDataH(playerid, "SlotItem0", PlayerInfo[playerid][pOther][11]);
    UpdatePlayerDataH(playerid, "SlotItem1", PlayerInfo[playerid][pOther][12]);
    UpdatePlayerDataH(playerid, "SlotItem2", PlayerInfo[playerid][pOther][13]);
    UpdatePlayerDataH(playerid, "SlotItem3", PlayerInfo[playerid][pOther][14]);
    UpdatePlayerDataH(playerid, "SlotItem4", PlayerInfo[playerid][pOther][15]);
    UpdatePlayerDataH(playerid, "SlotItem5", PlayerInfo[playerid][pOther][16]);

	GivePlayerMoneyH(fadmin, playerid, -price);
	
	PlayerInfo[playerid][pOther][slot + 11] = item;
    TogglePlayerControllableEx(playerid, true);
    PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
	Buyitem[playerid] = -1;
	SendClientMessage(playerid, COLOR_ERROR, "Если предмет не отображается, значит он не поддерживается на вашем скине");
	PlayerInfo[playerid][pType] = -1;
	timetobuy2[playerid] = 0;
	
    HIDE_ACCSES_SELECT(playerid);
    STOP_ACCSES(playerid);
    START_ACCSES(playerid);
    
	CancelSelectTextDraw(playerid);
	TogglePlayerControllableEx(playerid, true);
	SaveInv(playerid);
	return 1;
}

stock SaveInv(playerid)
{
    UpdatePlayerDataH(playerid, "SlotItem0", PlayerInfo[playerid][pOther][11]);
    UpdatePlayerDataH(playerid, "SlotItem1", PlayerInfo[playerid][pOther][12]);
    UpdatePlayerDataH(playerid, "SlotItem2", PlayerInfo[playerid][pOther][13]);
    UpdatePlayerDataH(playerid, "SlotItem3", PlayerInfo[playerid][pOther][14]);
    UpdatePlayerDataH(playerid, "SlotItem4", PlayerInfo[playerid][pOther][15]);
    UpdatePlayerDataH(playerid, "SlotItem5", PlayerInfo[playerid][pOther][16]);
	return 1;
}


stock ShowSkinShop1(playerid)
{
    ShowPlayerDialogEx(playerid, d_male_shop1, DIALOG_STYLE_LIST, "Выберите", "Civilian\nOrganization\nGangs", "Принять", "Отмена");

}

stock SkinShopNext(playerid)
{
    if(accShowSkin[playerid] != 1) return true;
    new SkinID;
    new ind, Found, Clothes[MAX_SKINS];
	for(new i=0; i<MAX_SKINS; i++)//сканируем все скины
	{
		if(	SkinArray[i][Type_Ped] == GetPVarInt(playerid, "TypePed") &&
			SkinArray[i][Gender] == PlayerInfo[playerid][pSex])
		{	//создаем список доступных скинов
			Clothes[ind] = i; ind ++; Found = 1;
		}//записали в массив тот ID соотв. например муж. посетителю пляжа
	}
	if(skins == ind) skins = 0;
	if(Found == 1)
	{
		if(skins_shop[playerid] + 1 < ind) skins_shop[playerid] += 1;	//если нашли
		SkinID = SkinArray[Clothes[skins_shop[playerid]]][Skin_ID];
		SetPlayerSkinEx(playerid, SkinID);
		SetPVarInt(playerid, "IsPaid", 0);
	}
	ApplyAnimation(playerid, "CLOTHES", "CLO_Pose_Torso",4.1,0,1,1,0,0);
	return 1;
}
stock SkinShopBack(playerid)
{
    if(accShowSkin[playerid] != 1) return true;
    new SkinID;
    new ind, Found, Clothes[MAX_SKINS];
	for(new i=0; i<MAX_SKINS; i++)//сканируем все скины
	{
		if(	SkinArray[i][Type_Ped] == GetPVarInt(playerid, "TypePed") &&
			SkinArray[i][Gender] == PlayerInfo[playerid][pSex])
		{	//создаем список доступных скинов
			Clothes[ind] = i; ind ++; Found = 1;
		}//записали в массив тот ID соотв. например муж. посетителю пляжа
	}
	if(skins == ind) skins = 0;
	if(Found == 1)
	{
		if(skins_shop[playerid] != 0) skins_shop[playerid] --;	//если нашли
		SkinID = SkinArray[Clothes[skins_shop[playerid]]][Skin_ID];
		SetPlayerSkinEx(playerid, SkinID);
		SetPVarInt(playerid, "IsPaid", 0);
	}
	ApplyAnimation(playerid, "CLOTHES", "CLO_Pose_Torso",4.1,0,1,1,0,0);
	return 1;
}
stock BuySkinShop(playerid)
{
	if(GetPlayerMoneyH(playerid) < 500)
	{
		PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		ShowSkinShop1(playerid); //return 1;
	}
	else if(BizInfo[GetBizLocation(playerid)-100][bProducts] <= 0 && !gRealWar
			&& !IsPlayerInRangeOfPoint(playerid, 7.5,256.8213,-41.5293,1002.0234))
	{
		GameTextForPlayerEx(playerid, "~r~Out Of Stock", 5000, 1);
		PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		ShowSkinShop1(playerid); //return 1;
	}
	else
	{
		//ClearAnimations(playerid, 1);
		HideMenuForPlayerEx(mPaid, playerid);
		GivePlayerMoneyH(fbiz+GetBizLocation(playerid)-100, playerid, -500);
		if( IsPlayerInRangeOfPoint(playerid, 7.5,256.8213,-41.5293,1002.0234) )
		{
			HouseInfo[GetHouseLocation(playerid)][hTill] += 500;
		}
		else
		{
			OnGangsExtortionBiz(GetBizLocation(playerid)-100, 500);
			//BizInfo[bizid][bProducts] --;//99-99=0
		}
		PlaySoundForPlayer(playerid, SOUND_SHOP_BUY);
		newskin = GetPlayerSkin(playerid);
		if(!IsValidSkin(newskin)) newskin = DefaultSkin(playerid);
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
		ApplyAnimation(playerid, "CLOTHES", "CLO_Buy",4.1,0,1,1,0,0);
		HideSkinSelect(playerid);
		ExitShopSkin(playerid);
	}
	return 1;
}
stock ExitShopSkin(playerid)
{
    SetCameraBehindPlayer(playerid);
   	TogglePlayerControllableEx(playerid, 1);
   	accShowSkin[playerid] = 0;
	if(GetPVarInt(playerid, "IsPaid") == 0)
	{
		SetPlayerSkinEx(playerid, GetPVarInt(playerid, "OldSkin"));
	}
	return 1;
}

stock HideSkinSelect(playerid)
{
	for(new i; i < 34; i ++)
	{
	    TextDrawHideForPlayer(playerid, Accessories[i]);
	}
	PlayerTextDrawHide(playerid, AccessoriesP[playerid]);
	CancelSelectTextDraw(playerid);
	accShowSkin[playerid] = 0;
	return 1;
}

stock UpdatePlayerDataH(playerid, stolb[], znach)
{
	//new Query[200];
	//mysql_format(g_SQL, Query, 200, "UPDATE `players` SET  %s = '%d' WHERE `ID` = '%d' LIMIT 1", stolb, znach, PlayerInfo[playerid][pSQLID]);
	//mysql_pquery(g_SQL, Query, "", "");
	new ToBase[52+13+5+11];
	format(ToBase, sizeof(ToBase), "UPDATE `players` SET  `%s` = '%d' WHERE `ID` = '%d'", stolb, znach, PlayerInfo[playerid][pSQLID]);
	db_free_result(db_query(db_VW, ToBase));
	return 1;
}

stock HideTD(playerid)
{
    if(accShowTD[playerid] == 1)
    {
        HIDE_ACCSES_SELECT(playerid);
        Buyitem[playerid] = 0;
        ShowPlayerDialogEx(playerid,d_accses2,DIALOG_STYLE_TABLIST, "Аксессуары | {DC143C}Покупка",
"- Наушники\n- Шапки\n- Панамки\n- Кепки\n- Каски\n- Береты\n- Парики\n- Очки\n- Банданы\n- Шляпы\n- Часы\n- Сумки\n- Гитары","Принять","Отмена");
//"- Наушники\n- Шапки\n- Панамки\n- Кепки\n- Каски\n- Береты\n- Парики\n- Очки\n- Банданы\n- Круглые шляпы\n- Часы\n- Сумки\n- Шляпы 2\n- Банданы на голову","Принять","Отмена");
    }
	if(accShowSkin[playerid] == 1)
	{
	    HideSkinSelect(playerid);
	    ShowSkinShop1(playerid);
	}
	/*if(open_you_baners[playerid] == 1)
	{
		for(new i; i < 34; i ++)
		{
		    TextDrawHideForPlayer(playerid, Accessories[i]);
		}
		PlayerTextDrawHide(playerid, AccessoriesP[playerid]);
		TogglePlayerControllableEx(playerid,true);
		SetPlayerPosEx(playerid, 2165.9031,1606.8743,999.9717,0);
		SetPlayerFacingAngle(playerid, 229.869);
		CancelSelectTextDraw(playerid);
		__Player_ID_Banner[playerid] = 0;
		__Player_Number_Banner[playerid] = 0;
		SetCameraBehindPlayer(playerid);
		icon_banner[playerid] = 0;
		SetPlayerVirtualWorldEx(playerid, 249);
		SetPlayerInteriorEx(playerid, 1);
	}*/
    return 1;
}

stock AttachObjectToSkin(playerid, modelid)
{
	new bool: found = false;
//проверяем если в базе для нашего скина такой объект установленный в эту часть тела то загружаем его в нужном положении
	new query[233+3*3+9*8];
	format(query,sizeof(query),"SELECT * FROM `attachobjects` WHERE `skinid`=%d AND `modelid`=%d LIMIT 1", GetPlayerSkin(playerid), modelid);
	new DBResult:db_result = db_query(db_AttachObjects,query);
	new index;
	if(db_num_rows(db_result))
	{
		new field[50]; 
		db_get_field_assoc(db_result, "index", field, sizeof(field) );	index = strval(field);
		//new index = objInfo[index][ao_index];//GetPVarInt(playerid, "AttachmentIndexSel");
	
		//db_get_field_assoc(db_result, "skinid", field, sizeof(field) );	objInfo[index][ao_SkinID] = strval(field);
		//db_get_field_assoc(db_result, "modelid", field, sizeof(field) ); objInfo[index[ao_modelid] = strval(field);
		db_get_field_assoc(db_result, "boneid", field, sizeof(field) ); objInfo[index][ao_boneid] = strval(field);

		db_get_field_assoc(db_result, "fOffsetX", field, sizeof(field) ); objInfo[index][ao_fOffsetX] = floatstr(field);
		db_get_field_assoc(db_result, "fOffsetY", field, sizeof(field) ); objInfo[index][ao_fOffsetY] = floatstr(field);
		db_get_field_assoc(db_result, "fOffsetZ", field, sizeof(field) ); objInfo[index][ao_fOffsetZ] = floatstr(field);

		db_get_field_assoc(db_result, "fRotX", field, sizeof(field) ); objInfo[index][ao_fRotX] = floatstr(field);
		db_get_field_assoc(db_result, "fRotY", field, sizeof(field) ); objInfo[index][ao_fRotY] = floatstr(field);
		db_get_field_assoc(db_result, "fRotZ", field, sizeof(field) ); objInfo[index][ao_fRotZ] = floatstr(field);

		db_get_field_assoc(db_result, "fScaleX", field, sizeof(field) ); objInfo[index][ao_fScaleX] = floatstr(field);
		db_get_field_assoc(db_result, "fScaleY", field, sizeof(field) ); objInfo[index][ao_fScaleY] = floatstr(field);
		db_get_field_assoc(db_result, "fScaleZ", field, sizeof(field) ); objInfo[index][ao_fScaleZ] = floatstr(field);

		found = true;
	}
	db_free_result(db_result);
	if(found == true)
	{
		SetPlayerAttachedObjectEx(playerid, index, modelid, objInfo[index][ao_boneid],
					objInfo[index][ao_fOffsetX],objInfo[index][ao_fOffsetY],objInfo[index][ao_fOffsetZ],
					objInfo[index][ao_fRotX],objInfo[index][ao_fRotY],objInfo[index][ao_fRotZ],
					objInfo[index][ao_fScaleX],objInfo[index][ao_fScaleY],objInfo[index][ao_fScaleZ]);
	}
	else {  SendClientMessage(playerid,COLOR_ERROR,"Данный аксессуар не будет отображаться на этом скине!"); return -1;  }
	return 1;
}
