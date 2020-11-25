//##############################################################################//
//                                                                              //
//                                 СИСТЕМА ПВО                                  //
//                                                                              //
//##############################################################################//


//#include <a_samp>
//#include "../include/vw_color"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Для системы ПВО
//Обьявляем константы
#define MAX_SPHERE 5 //максимально может быть только 5 целей в зоне досягаемости
#define KEY_SHIFT 40
/////////////////////
enum Sphere_Rocket_Target
{

	s_Player_ID = 900,
	s_Radius,
	Float:f_Coordinates_Center_X,
	Float:f_Coordinates_Center_Y,
	Float:f_Coordinates_Center_Z,

};
new ARRAY_SPHERE[MAX_SPHERE][Sphere_Rocket_Target];
new COUNT = 0;
new bool:InZone[MAX_PLAYERS];
new bool:InTurret[MAX_PLAYERS] ;
new TURRET_POSITION[MAX_PLAYERS];

new Float:ARRAY_POS[] = {-67.1003,144.5304,30.1875,	431.3137,1644.4519,2134.5322};//координаты зоны51

new Float:ARRAY_POS_PLAYER[3];
new Float:ARRAY_POS_PLAYER_TWO[3];
//для входов и выходов в туррели


#define MAX_ROCKET 16 //по 4 на каждой установке
enum ROCKET_INFO
{
	rUseRock,//идентифик
	rObject,//для создания обьекта самой ракеты Обьект создается при старте
	rObjectSecond,//для создания второго обьекта
	rObjectThird,
	rIdModel,//id обьекта ракеты
	rSpeed,//скорость
	rTime,//время полета в секундах
	rPower,//мощность взрыва
	rAction,//статус действия 0 - не активна , 1 в полете
	
	Float:rStartX,//координаты старта
	Float:rStartY,
	Float:rStartZ,
	
	Float:rRotX,//угол поворота на стартовой площадке
	Float:rRotY,
	Float:rRotZ,
	
	rIdTarget,//id цели
	rLock,//есть ли захват цели , по умолчанию 0 = т.е нету
	
	Float:rCurrentX,//текущие координаты ракеты
	Float:rCurrentY,
	Float:rCurrentZ,
}
new ARRAY_ROCKET[MAX_ROCKET][ROCKET_INFO] = {
{0,0,0,0,3790,100,4,3,0,	238.3880,1697.2030,25.6,	1.77,28.01,267.06,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	238.3843,1697.6912,25.1,	0.00,28.00,272.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	237.0129,1697.4990,25.1,	0.00,30.00,270.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	237.0126,1697.4674,25.6,	0.00,30.00,272.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	16.3136,1719.7430,25.1,		0.00,30.00,272.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	16.2805,1719.4083,25.6,		351.18,28.37,274.73,900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	14.9729,1719.4016,25.6,		0.00,32.00,270.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	14.9162,1719.8699,25.1,		0.00,28.00,268.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	188.8492,2082.1545,25.6,	0.00,30.00,268.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	188.8939,2082.6765,25.1,	0.00,32.00,270.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	187.5300,2081.9507,25.6,	0.00,28.00,270.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	187.5521,2082.3611,25.1,	0.00,30.00,266.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	355.0659,2028.9161,25.6,	0.00,28.00,270.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	355.0786,2029.1095,25.1,	0.00,30.00,268.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	353.7913,2028.9417,25.6,	0.00,30.00,268.00,	900,0,	0.0,0.0,0.0},
{0,0,0,0,3790,100,4,3,0,	353.6704,2029.1030,25.1,	0.00,30.00,268.00,	900,0,	0.0,0.0,0.0}
};

#define MAX_TURRET 4
enum TURRET_INFO
{
	tTime,//идентификатор таймера
	tAmount,//количество выстреленных ракет
	tStartOfRocket,
	tEndOfRocket,
	tPlayer_ID,//ид стрелка
	tReserve,//запас выстрелов в каждой туреле
	tAction,//статус её активности , 0 - не активная, 1 - в работе , 3 - пустая .
	tDriver[128],//текущий управляющий турелью
	Float:tEnterX,//координаты входа
	Float:tEnterY,
	Float:tEnterZ,
	Float:tTurretX,//координаты самой турели
	Float:tTurretY,
	Float:tTurretZ,
};
new ARRAY_TURRET[MAX_TURRET][TURRET_INFO] = {
{0,0,4,7,900,50,0,"His name:NONE",	14.9797,1735.5975,22.1952,	15.6172,1719.1641,25.2000},
{0,0,0,3,900,50,0,"His name:NONE",	237.8669,1717.3706,22.7813,	237.6953,1696.8750,25.2000},
{0,0,12,15,900,50,0,"His name:NONE",354.3315,2019.4357,22.6406,	354.4297,2028.4922,25.2000},
{0,0,8,11,900,50,0,"His name:NONE",	187.3271,2085.2751,22.6468,	188.2422,2081.6484,25.2000}
};

new Text3D:ARRAY_TEXT[MAX_TURRET];
//для создания текст дравов
new Text:txtSprite1;
new Text:txtSprite2;
new Text:txtSprite3;
new Text:txtSprite4;
new Text:txtSprite5;
//для вращения платформы
new TURRET_OBJECT[MAX_TURRET];
//для работы с векторами
new TLOCKED[MAX_PLAYERS] = 0 ;

new airPickupID[MAX_TURRET];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
stock airdefence_OnGameModeInit()
{
	//для установки входов в туррели
	new Info_Str[64];
	for(new i ; i < MAX_TURRET ; i++)
	{
		airPickupID[i] = SetPickupEx(1254, 23, ARRAY_TURRET[i][tEnterX] , ARRAY_TURRET[i][tEnterY], ARRAY_TURRET[i][tEnterZ], 0);
		format(Info_Str,sizeof(Info_Str),"{ %s }",ARRAY_TURRET[i][tDriver]);
		
 	    ARRAY_TEXT[i] = Create3DTextLabelEx(Info_Str,COLOR_GREEN,ARRAY_TURRET[i][tEnterX] , ARRAY_TURRET[i][tEnterY], ARRAY_TURRET[i][tEnterZ]+1, 50.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);
	}
	for (new i =0 ; i < MAX_ROCKET ; i++)
	{
		ARRAY_ROCKET[i][rIdTarget] = 900;
	}
	//для создания самих обьектов турели
	for (new i =0 ; i < MAX_SPHERE ; i++)
	{
		ARRAY_SPHERE[i][s_Player_ID] = 900;
	}
	for (new i = 0 ; i < MAX_TURRET ; i++)
	{
		TURRET_OBJECT[i] = CreateObjectEx(3267, ARRAY_TURRET[i][tTurretX],ARRAY_TURRET[i][tTurretY],ARRAY_TURRET[i][tTurretZ]-1.5,0,0,0);
	}
	CreateObjectEx(3277, 188.2422,2081.6484,23.7, 0.0,0.0,0.0);//первая
	CreateObjectEx(3277, 354.4297,2028.4922,23.7, 0.0,0.0,0.0);//вторая
	CreateObjectEx(3277, 15.6172,1719.1641,23.7, 0.0,0.0,0.0);//третья
	CreateObjectEx(3277, 237.6953,1696.8750,23.7, 0.0,0.0,0.0);//четвёртая

	OnCreateTextDraw();
}

stock airdefence_OnPlayerConnect(playerid)
{
	RemoveBuildingForPlayer(playerid, 3267, 188.2422, 2081.6484, 22.4453, 1.25);//первая
	//Подставки нету (1)
	RemoveBuildingForPlayer(playerid, 3267, 354.4297, 2028.4922, 22.4141, 1.25);//вторая

	RemoveBuildingForPlayer(playerid, 3267, 15.6172, 1719.1641, 22.4141, 1.25);//третья

	RemoveBuildingForPlayer(playerid, 3267, 237.6953, 1696.8750, 22.4141, 1.25);//четвёртая

	InZone[playerid] = false;
	InTurret[playerid] = false;
}

stock airdefence_OnPlayerDisconnect(playerid)
{
	ChangeArray(playerid);
	OnPlayerExitTurret(playerid);
}

stock airdefence_OnPlayerExitVehicle(playerid)
{
	ChangeArray(playerid);
}

stock airdefence_OnPlayerDeath(playerid)
{
	ChangeArray(playerid);
	OnPlayerExitTurret(playerid);
}
stock airdefence_OnGameModeExit()
{
	TextDrawDestroyEx(txtSprite1);
	TextDrawDestroyEx(txtSprite2);
	TextDrawDestroyEx(txtSprite3);
	TextDrawDestroyEx(txtSprite4);
	TextDrawDestroyEx(txtSprite5);
}

stock OnCreateTextDraw()
{
	txtSprite1 = TextDrawCreateEx(0,0, "LD_DUAL:black");
	TextDrawFont(txtSprite1, 4);
	TextDrawTextSize(txtSprite1,640.0,50.0);


	txtSprite2 = TextDrawCreateEx(0,310, "LD_DUAL:black");
	TextDrawFont(txtSprite2, 4);
	TextDrawTextSize(txtSprite2,640.0,170.0);


	txtSprite3 = TextDrawCreateEx(0,0, "LD_DUAL:black");
	TextDrawFont(txtSprite3, 4);
	TextDrawTextSize(txtSprite3,50.0,480.0);


	txtSprite4 = TextDrawCreateEx(590,0, "LD_DUAL:black");
	TextDrawFont(txtSprite4, 4);
	TextDrawTextSize(txtSprite4,50.0,480.0);


	txtSprite5 = TextDrawCreateEx(280,200, "LD_BEAT:cring");
	TextDrawFont(txtSprite5, 4);
	TextDrawTextSize(txtSprite5,80.0,80.0);
}

stock airdefence_OnPlayerUpdate(playerid)
{
	OnPlayerEntryArea(playerid);//определяем находится ли игрок в пространстве над зоной
	OnLookAtPlayer();//определяем находится ли цель в прицеле
	SetRotObject();//устанавливаем всем летящим ракетам нужный угол и градус поворота к обьекту
	MoveObjectToTarget();//двигаем все активные ракеты к цели
	ExplUpdate();//проверяем расстояние, на то что бы определить столкновение
}

stock airdefence_OneSecondTimers()
{
	CreateExpl();
	OnPlayerExitArea();
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		TLOCKED[i] = 0;
	}
}

stock OnPlayerKeyAirDefence(playerid, newkeys, oldkeys)
{
	//перехватываем у игрока все нажатые клавиши , что бы он не сдвинулся пока сидит в турельке )
	if(newkeys == KEY_WALK)
	{
		CheckForPressing(playerid);
	}
	if(newkeys == KEY_HANDBRAKE)
	{
		ReturnPlayerPos(playerid);
	}
	if(newkeys == KEY_JUMP)
	{
		ReturnPlayerPos(playerid);
	}
	if(oldkeys == KEY_JUMP)
	{
		ReturnPlayerPos(playerid);
	}
	if(oldkeys == KEY_SHIFT)
	{
		ReturnPlayerPos(playerid);
	}
	if(newkeys == KEY_SHIFT)
	{
		ReturnPlayerPos(playerid);
	}
	if(newkeys == KEY_SPRINT)
	{
		ReturnPlayerPos(playerid);
	}
	if(newkeys == KEY_FIRE)
	{
		if (InTurret[playerid] == true)
		{
			if (TLOCKED[playerid] == 1)
			{
				StartRocket(playerid);
			}
			ReturnPlayerPos(playerid);
		}
	}
	if(newkeys == KEY_CROUCH)
	{
		ReturnPlayerPos(playerid);
	}
	if(newkeys == 65408)
	{
		ReturnPlayerPos(playerid);
	}
	if(newkeys == 65416)
	{
		ReturnPlayerPos(playerid);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
stock OnPlayerEntryArea(playerid)//выполняется если игрок оказался в воздушном пространстве над зоной , если он уже есть в над зоной то считываем его координаты
{
	if( !IsPlayerInAnyVehicle(playerid) ) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)  return 1;
	if ( InZone[playerid] == false)
	{
		GetPlayerPos(playerid,ARRAY_POS_PLAYER[0],ARRAY_POS_PLAYER[1],ARRAY_POS_PLAYER[2]);
		if(	(ARRAY_POS_PLAYER[0] > ARRAY_POS[0] && ARRAY_POS_PLAYER[0] < ARRAY_POS[3]) &&
			(ARRAY_POS_PLAYER[1] > ARRAY_POS[4] && ARRAY_POS_PLAYER[1] < ARRAY_POS[2] && ARRAY_POS_PLAYER[2] < ARRAY_POS[1])
			)
		{
			COUNT++;
			ARRAY_SPHERE[COUNT][s_Player_ID] = playerid;
			InZone[playerid] = true;
			
			new str[256];
			format(str,sizeof(str),"Внимание всем постам , проникновение в воздушное пространство зоны его ID = %d ",ARRAY_SPHERE[COUNT][s_Player_ID]);
			SendFamilyMessage(DoD, str);
			//continue;
		}
	}
	else //if (InZone[playerid] == true )
	{
		GetPlayerPos(playerid,ARRAY_POS_PLAYER[0],ARRAY_POS_PLAYER[1],ARRAY_POS_PLAYER[2]);
		if(	(ARRAY_POS_PLAYER[0] > ARRAY_POS[0] && ARRAY_POS_PLAYER[0] < ARRAY_POS[3]) &&
			(ARRAY_POS_PLAYER[1] > ARRAY_POS[4] && ARRAY_POS_PLAYER[1] < ARRAY_POS[2] && ARRAY_POS_PLAYER[2] < ARRAY_POS[1])
			)
		{
			for (new j = 1 ; j <= COUNT ;j++)
			{
				if ( playerid == ARRAY_SPHERE[j][s_Player_ID])
				{
					//GetPlayerPos(playerid,ARRAY_POS_PLAYER[0],ARRAY_POS_PLAYER[1],ARRAY_POS_PLAYER[2]);
					ARRAY_SPHERE[j][f_Coordinates_Center_X] = ARRAY_POS_PLAYER[0];
					ARRAY_SPHERE[j][f_Coordinates_Center_Y] = ARRAY_POS_PLAYER[1];
					ARRAY_SPHERE[j][f_Coordinates_Center_Z] = ARRAY_POS_PLAYER[2];
				}
			}
		}
	}
	return 1;
}


stock OnPlayerExitArea()//выполняется если игрок покинул зону
{
	for(new i = 0; i <= COUNT; i++)
	{
		if(IsPlayerInAnyVehicle(ARRAY_SPHERE[i][s_Player_ID]) && GetPlayerState(ARRAY_SPHERE[i][s_Player_ID])==PLAYER_STATE_DRIVER)
		{
			if (InZone[ARRAY_SPHERE[i][s_Player_ID]] == true )
			{
				GetPlayerPos(ARRAY_SPHERE[i][s_Player_ID],ARRAY_POS_PLAYER_TWO[0],ARRAY_POS_PLAYER_TWO[1],ARRAY_POS_PLAYER_TWO[2]);
				if((ARRAY_POS_PLAYER_TWO[0] < ARRAY_POS[0] || ARRAY_POS_PLAYER_TWO[0] > ARRAY_POS[3]) || (ARRAY_POS_PLAYER_TWO[1] < ARRAY_POS[4] || ARRAY_POS_PLAYER_TWO[1] >ARRAY_POS[5]))
				{
					SendFamilyMessage(DoD, "Цель покинула зону");
					for(new l = 0; l < MAX_ROCKET; l++)
					{
						if (ARRAY_ROCKET[l][rAction] == 1)
						{
							if (ARRAY_ROCKET[l][rIdTarget] == ARRAY_SPHERE[i][s_Player_ID])
							{
								ARRAY_ROCKET[l][rIdTarget] = 900;
								ARRAY_ROCKET[l][rAction] = 0;
								DestroyObjectEx(ARRAY_ROCKET[l][rObject]);
								DestroyObjectEx(ARRAY_ROCKET[l][rObjectSecond]);
								DestroyObjectEx(ARRAY_ROCKET[l][rObjectThird]);
								break;
							}
						}
					}
					if (i == COUNT )
					{
						COUNT --;
						InZone[ARRAY_SPHERE[i][s_Player_ID]] = false ;
						ARRAY_SPHERE[i][s_Player_ID] = 900;
						ARRAY_SPHERE[i][f_Coordinates_Center_X] = 0;
						ARRAY_SPHERE[i][f_Coordinates_Center_Y] = 0;
						ARRAY_SPHERE[i][f_Coordinates_Center_Z] = 0;
					}
					else//иначе двигаем весь массив влево на 1 элемент ( что бы все значения хранились корректно в нем )
					{
						InZone[ARRAY_SPHERE[i][s_Player_ID]] = false ;
						for(new l = i; l < COUNT ; l++)
						{
							ARRAY_SPHERE[l][s_Player_ID] = ARRAY_SPHERE[l+1][s_Player_ID];
							ARRAY_SPHERE[l][f_Coordinates_Center_X] = ARRAY_SPHERE[l+1][f_Coordinates_Center_X];
							ARRAY_SPHERE[l][f_Coordinates_Center_Y] = ARRAY_SPHERE[l+1][f_Coordinates_Center_Y];
							ARRAY_SPHERE[l][f_Coordinates_Center_Z] = ARRAY_SPHERE[l+1][f_Coordinates_Center_Z];
							ARRAY_SPHERE[l+1][s_Player_ID] = 900;
							ARRAY_SPHERE[l+1][f_Coordinates_Center_X] = 0;
							ARRAY_SPHERE[l+1][f_Coordinates_Center_Y] = 0;
							ARRAY_SPHERE[l+1][f_Coordinates_Center_Z] = 0;
						}
						COUNT --;
					}
				}
			}
		}
	}
}



stock ChangeArray(playerid)
{
	for(new i = 1; i <= COUNT; i++)
	{
		if( playerid == ARRAY_SPHERE[i][s_Player_ID])
		{
			for(new l = 0; l < MAX_ROCKET; l++)
			{
				if (ARRAY_ROCKET[l][rAction] == 1)
				{
					if (ARRAY_ROCKET[l][rIdTarget] == playerid)
					{
						ARRAY_ROCKET[l][rIdTarget] = 900;
						ARRAY_ROCKET[l][rAction] = 0;
						DestroyObjectEx(ARRAY_ROCKET[l][rObject]);
						DestroyObjectEx(ARRAY_ROCKET[l][rObjectSecond]);
						DestroyObjectEx(ARRAY_ROCKET[l][rObjectThird]);
						break;
					}
				}
			}
			if (i == COUNT )
			{
				COUNT --;
				InZone[playerid] = false ;
				ARRAY_SPHERE[i][s_Player_ID] = 900;
				ARRAY_SPHERE[i][f_Coordinates_Center_X] = 0;
				ARRAY_SPHERE[i][f_Coordinates_Center_Y] = 0;
				ARRAY_SPHERE[i][f_Coordinates_Center_Z] = 0;
				SendFamilyMessage(DoD, "Цель покинула зону");
			}
			else
			{
				InZone[playerid] = false ;
				for(new l = i; l < COUNT ; l++)
				{
					ARRAY_SPHERE[l][s_Player_ID] = ARRAY_SPHERE[l+1][s_Player_ID];
					ARRAY_SPHERE[l][f_Coordinates_Center_X] = ARRAY_SPHERE[l+1][f_Coordinates_Center_X];
					ARRAY_SPHERE[l][f_Coordinates_Center_Y] = ARRAY_SPHERE[l+1][f_Coordinates_Center_Y];
					ARRAY_SPHERE[l][f_Coordinates_Center_Z] = ARRAY_SPHERE[l+1][f_Coordinates_Center_Z];
					ARRAY_SPHERE[l+1][s_Player_ID] = 900;
					ARRAY_SPHERE[l+1][f_Coordinates_Center_X] = 0;
					ARRAY_SPHERE[l+1][f_Coordinates_Center_Y] = 0;
					ARRAY_SPHERE[l+1][f_Coordinates_Center_Z] = 0;
					SendFamilyMessage(DoD, "Цель покинула зону");
				}
				COUNT --;
			}
		}
	}
}



stock CheckForPressing(playerid)
{
	new H_NAME[MAX_PLAYER_NAME];
	new STR_UPDATE[128];
	if (InTurret[playerid] == false )
	{//вход в турель
		for(new t =0; t < MAX_TURRET ; t++)
		{
			if(IsPlayerInRangeOfPoint(playerid,2,ARRAY_TURRET[t][tEnterX] , ARRAY_TURRET[t][tEnterY], ARRAY_TURRET[t][tEnterZ]))
			{
				if (ARRAY_TURRET[t][tAction] == 1)
				{
					SendClientMessage(playerid,COLOR_RED,"Турель уже занята, вы не можете в неё сесть ");
					return 1;
				}

				SetPlayerPos(playerid,ARRAY_TURRET[t][tTurretX],ARRAY_TURRET[t][tTurretY],ARRAY_TURRET[t][tTurretZ]);
				ApplyAnimation(playerid,"INT_OFFICE","FF_Dam_Fwd", 4.1, 1, 0, 0, 1, 1,1);
				AttachObjectToPlayerEx(TURRET_OBJECT[t],playerid, 0.0,0.0,-2.0, 0.0,0.0,0.0);
				GetPlayerName(playerid,H_NAME,sizeof(H_NAME));
				//присвоили различные статусы переменным
				InTurret[playerid] = true ;
				TURRET_POSITION[playerid] = t;
				ARRAY_TURRET[t][tAction] = 1;//значит турель стала активна
				ARRAY_TURRET[t][tPlayer_ID] = playerid;
				//прорисовали текст дравы
				TextDrawShowForPlayer(playerid,txtSprite1);
				TextDrawShowForPlayer(playerid,txtSprite2);
				TextDrawShowForPlayer(playerid,txtSprite3);
				TextDrawShowForPlayer(playerid,txtSprite4);
				TextDrawShowForPlayer(playerid,txtSprite5);
				//обновили 3D text
				format(STR_UPDATE,sizeof(STR_UPDATE),"On duty : %s ",H_NAME);
				UpdateDynamic3DTextLabelText(ARRAY_TEXT[t], COLOR_RED, STR_UPDATE);
				//добавили звук
				//PlayAudioStreamForPlayer(playerid,"");
			}
		}
	}
	else if (InTurret[playerid] == true )
	{
		//new str[256];
		SetPlayerPos(playerid,ARRAY_TURRET[TURRET_POSITION[playerid]][tEnterX] , ARRAY_TURRET[TURRET_POSITION[playerid]][tEnterY], ARRAY_TURRET[TURRET_POSITION[playerid]][tEnterZ]);
		//обновили 3D text
		format(STR_UPDATE,sizeof(STR_UPDATE),"His Name:NONAME");
		UpdateDynamic3DTextLabelText(ARRAY_TEXT[TURRET_POSITION[playerid]], COLOR_GREEN, STR_UPDATE);
		//разрушили за аттачиный обьект
		DestroyObjectEx(TURRET_OBJECT[TURRET_POSITION[playerid]]);
		TURRET_OBJECT[TURRET_POSITION[playerid]] = CreateObjectEx(3267,ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretX],ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretY],ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretZ]-2,0,0,0);
		//изменили перемнные статусов (так сказать флаги )

		ARRAY_TURRET[TURRET_POSITION[playerid]][tAction] = 0;
		ARRAY_TURRET[TURRET_POSITION[playerid]][tPlayer_ID] = 900;

		InTurret[playerid] = false ;
		TURRET_POSITION[playerid] = 900;

		//скрыли текстдравы
		TextDrawHideForPlayer(playerid,txtSprite1);
		TextDrawHideForPlayer(playerid,txtSprite2);
		TextDrawHideForPlayer(playerid,txtSprite3);
		TextDrawHideForPlayer(playerid,txtSprite4);
		TextDrawHideForPlayer(playerid,txtSprite5);
		
		//отчистили аимацию
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 0);
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
		ClearAnimations(playerid);
	}
	return 1;
}

stock OnPlayerExitTurret(playerid)
{
	if (InTurret[playerid] == true )
	{
		new STR_UPDATE[128];
		format(STR_UPDATE,sizeof(STR_UPDATE),"His Name:NONAME");
		UpdateDynamic3DTextLabelText(ARRAY_TEXT[TURRET_POSITION[playerid]], COLOR_GREEN, STR_UPDATE);
		DestroyObjectEx(TURRET_OBJECT[TURRET_POSITION[playerid]]);
		TURRET_OBJECT[TURRET_POSITION[playerid]] = CreateObjectEx(3267,ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretX],ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretY],ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretZ]-2,0,0,0);
		ARRAY_TURRET[TURRET_POSITION[playerid]][tAction] = 0;
		ARRAY_TURRET[TURRET_POSITION[playerid]][tPlayer_ID] = 900;
		InTurret[playerid] = false ;
		TURRET_POSITION[playerid] = 900;
		
		TextDrawHideForPlayer(playerid,txtSprite1);
		TextDrawHideForPlayer(playerid,txtSprite2);
		TextDrawHideForPlayer(playerid,txtSprite3);
		TextDrawHideForPlayer(playerid,txtSprite4);
		TextDrawHideForPlayer(playerid,txtSprite5);
	}
}

stock ReturnPlayerPos(playerid)
{//выход из турели
	if (InTurret[playerid] == true)
	{
		SetPlayerPos(playerid, ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretX],
								ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretY],ARRAY_TURRET[TURRET_POSITION[playerid]][tTurretZ]);
		ApplyAnimation(playerid,"INT_OFFICE","FF_Dam_Fwd", 4.1, 1, 0, 0, 1, 1);
	}
}



stock StartRocket(playerid)
{
	if ( (ARRAY_TURRET[0][tAction] + ARRAY_TURRET[1][tAction] + ARRAY_TURRET[2][tAction] + ARRAY_TURRET[3][tAction] )!= 0 )//если задействоана хотя бы 1 турель , и есть хотя бы одна цель
	{
		if ( COUNT != 0 )
		{
			for(new l = ARRAY_TURRET[TURRET_POSITION[playerid]][tStartOfRocket] ; l <=ARRAY_TURRET[TURRET_POSITION[playerid]][tEndOfRocket] ; l++)
			{
				if (ARRAY_ROCKET[l][rAction] == 0 )
				{
					if ( ARRAY_TURRET[TURRET_POSITION[playerid]][tAmount] < 4)
					{
						if(ARRAY_ROCKET[l][rUseRock] == 0)
						{
							new Float:ang ;
							new str[256];
							//PlayAudioStreamForPlayer(playerid,"http://doctorjohansen.narod2.ru/Stinger_fire_1p.mp3");
							GetPlayerFacingAngle(playerid,ang);
							ARRAY_ROCKET[l][rAction] = 1 ;
							ARRAY_ROCKET[l][rUseRock] = 1;
							format(str,sizeof(str),"{339933}Выстрел произведен , осталось %d ракет ",(3 - ARRAY_TURRET[TURRET_POSITION[playerid]][tAmount]));
							SendClientMessage(playerid,COLOR_RED,str);
							ARRAY_TURRET[TURRET_POSITION[playerid]][tAmount]++;

							ARRAY_ROCKET[l][rObject] = CreateObjectEx(ARRAY_ROCKET[l][rIdModel],ARRAY_ROCKET[l][rStartX],ARRAY_ROCKET[l][rStartY],ARRAY_ROCKET[l][rStartZ],ARRAY_ROCKET[l][rRotX],ARRAY_ROCKET[l][rRotY],ang-90);

							ARRAY_ROCKET[l][rObjectSecond] = CreateObjectEx(18727,0,0,0,0,0,0);
							ARRAY_ROCKET[l][rObjectThird] = CreateObjectEx(18727,0,0,0,0,0,0);
							AttachObjectToObjectEx(ARRAY_ROCKET[l][rObjectSecond],ARRAY_ROCKET[l][rObject],0,0,-2,0,0,0,1);
							AttachObjectToObjectEx(ARRAY_ROCKET[l][rObjectThird],ARRAY_ROCKET[l][rObject],0,0,-3,0,0,0,1);

							break;
						}
					}
					else if(ARRAY_TURRET[TURRET_POSITION[playerid]][tAmount] == 4)
					{
						SendClientMessage(playerid,COLOR_RED,"{FFFF66}Производится перезарядка ");
						ARRAY_TURRET[TURRET_POSITION[playerid]][tTime] = SetTimerEx("Reload", 4000, false, "i", playerid);
						break;
					}
				}
			}
		}
	}
}
forward Reload(playerid);
public Reload(playerid)
{
	for(new l = ARRAY_TURRET[TURRET_POSITION[playerid]][tStartOfRocket] ; l <=ARRAY_TURRET[TURRET_POSITION[playerid]][tEndOfRocket] ; l++)
	{
		ARRAY_ROCKET[l][rUseRock] = 0;
	}
	ARRAY_TURRET[TURRET_POSITION[playerid]][tAmount] = 0;
	SendClientMessage(playerid,COLOR_RED,"{FFFF66}Произведена успешно ");
	//PlayAudioStreamForPlayer(playerid,"http://doctorjohansen.narod2.ru/Reload_Missile.mp3");
	KillTimer(ARRAY_TURRET[TURRET_POSITION[playerid]][tTime]);
}

stock MoveObjectToTarget()
{
	for(new l = 0 ; l < MAX_ROCKET; l++)
	{
		if (ARRAY_ROCKET[l][rAction] != 1) continue;
		for (new j =1 ; j <= COUNT ; j++)
		{
			if (ARRAY_ROCKET[l][rIdTarget] == ARRAY_SPHERE[j][s_Player_ID])
			{
				MoveObjectEx(ARRAY_ROCKET[l][rObject],ARRAY_SPHERE[j][f_Coordinates_Center_X]-0.2,ARRAY_SPHERE[j][f_Coordinates_Center_Y]-0.2,ARRAY_SPHERE[j][f_Coordinates_Center_Z],ARRAY_ROCKET[l][rSpeed]);
			}
		}
	}
}


stock OnLookAtPlayer()
{
	if ( (ARRAY_TURRET[0][tAction] + ARRAY_TURRET[1][tAction] + ARRAY_TURRET[2][tAction] + ARRAY_TURRET[3][tAction] )!= 0 )//если задействоана хотя бы 1 турель , и есть хотя бы одна цель
	{
		for(new i = 0; i < MAX_TURRET; i++)
		{
			for(new j = 1 ; j <= COUNT ; j++)
			{
				if ( ARRAY_TURRET[i][tAction] != 1) continue;
				if (IsPlayerLookingAtPlayer(ARRAY_TURRET[i][tPlayer_ID],ARRAY_SPHERE[j][s_Player_ID]) == 1 )
				{
					TLOCKED[ARRAY_TURRET[i][tPlayer_ID]] = 1;
					for(new l = ARRAY_TURRET[i][tStartOfRocket] ; l <=ARRAY_TURRET[i][tEndOfRocket] ; l++)
					{
						ARRAY_ROCKET[l][rIdTarget] = ARRAY_SPHERE[j][s_Player_ID];
					}
				}
			}
		}
	}
}

stock IsPlayerLookingAtPlayer(player1, player2)
{ //возварщает верно (1) если игрок player2 находится в поле зрения игрока player1
// @player1 : The playerid of the player who is looking at someone.
//playerid Игрока, который смотрит на кого-нибудь.
// @player2 : The playerid of the player who is being seen.
//playerid Игрока, который увиден.
	if (!IsPlayerConnected(player1) || !IsPlayerConnected(player2) || player1 == player2) return 0;

	new
	Float: distance,
	Float: vectorX,
	Float: vectorY,
	Float: vectorZ,
	Float: plyrPos[2][3],
	Float: projPos[3];

	GetPlayerCameraFrontVector(player1, vectorX, vectorY, vectorZ);
	GetPlayerCameraPos(player1, plyrPos[0][0], plyrPos[0][1], plyrPos[0][2]);

	GetPlayerPos(player2, plyrPos[1][0], plyrPos[1][1], plyrPos[1][2]);

#define SQUARE(%1) ((%1)*(%1))
	// Looks like we need distance, damnit! This is the 3D distance since we are working in a 3D space.
	distance = floatsqroot(SQUARE(plyrPos[1][0]-plyrPos[0][0]) + SQUARE(plyrPos[1][1]-plyrPos[0][1]) + SQUARE(plyrPos[1][2]-plyrPos[0][2]) );

	projPos[0] = plyrPos[0][0] + vectorX * distance;
	projPos[1] = plyrPos[0][1] + vectorY * distance;
	projPos[2] = plyrPos[0][2] + vectorZ * distance;

	return (
		( SQUARE(plyrPos[1][0]-projPos[0]) +
		SQUARE(plyrPos[1][1]-projPos[1]) +
		SQUARE(plyrPos[1][2]-projPos[2])
		) <= SQUARE(distance / 6)	);
	// Is the projected position within a virtual sphere around player2?
#undef SQUARE
}

stock SetRotObject()
{
	if ( (ARRAY_TURRET[0][tAction] + ARRAY_TURRET[1][tAction] + ARRAY_TURRET[2][tAction] + ARRAY_TURRET[3][tAction] )!= 0 )
	{//если задействована хотя бы 1 турель , и есть хотя бы одна цель
		for(new i = 0 ; i < MAX_ROCKET;i++)
		{
			if(ARRAY_ROCKET[i][rAction] != 1) continue;
			GetObjectPos(ARRAY_ROCKET[i][rObject],ARRAY_ROCKET[i][rCurrentX],ARRAY_ROCKET[i][rCurrentY],ARRAY_ROCKET[i][rCurrentZ]);
			for (new j =1 ; j <= COUNT ; j++)
			{
				if (ARRAY_ROCKET[i][rIdTarget] == ARRAY_SPHERE[j][s_Player_ID])
				{
					ARRAY_ROCKET[i][rRotY] = GetAngleZBeetwenPoint(ARRAY_ROCKET[i][rStartX],ARRAY_ROCKET[i][rStartY],ARRAY_ROCKET[i][rStartZ],
					ARRAY_SPHERE[j][f_Coordinates_Center_X],ARRAY_SPHERE[j][f_Coordinates_Center_Y],ARRAY_SPHERE[j][f_Coordinates_Center_Z]);
					ARRAY_ROCKET[i][rRotZ] = GetAngleBetweenPoint(ARRAY_ROCKET[i][rStartX],ARRAY_ROCKET[i][rStartY],
					ARRAY_SPHERE[j][f_Coordinates_Center_X],ARRAY_SPHERE[j][f_Coordinates_Center_Y]);
					SetObjectRot(ARRAY_ROCKET[i][rObject],0,ARRAY_ROCKET[i][rRotY],ARRAY_ROCKET[i][rRotZ]-90);
				}
			}
		}
	}
}

stock ExplUpdate()
{
	if ( (ARRAY_TURRET[0][tAction] + ARRAY_TURRET[1][tAction] + ARRAY_TURRET[2][tAction] + ARRAY_TURRET[3][tAction] ) != 0 )
	{//если задействоана хотя бы 1 турель , и есть хотя бы одна цель
		for(new i =0;i < MAX_ROCKET; i++)
		{
			if (ARRAY_ROCKET[i][rAction] != 1) continue;
			for (new j =1 ; j <= COUNT ; j++)
			{
				if (ARRAY_ROCKET[i][rIdTarget] == ARRAY_SPHERE[j][s_Player_ID])
				{
					if (GetDistanceBeetweenPoint(ARRAY_ROCKET[i][rCurrentX],ARRAY_ROCKET[i][rCurrentY],ARRAY_ROCKET[i][rCurrentZ],
						ARRAY_SPHERE[j][f_Coordinates_Center_X],ARRAY_SPHERE[j][f_Coordinates_Center_Y],ARRAY_SPHERE[j][f_Coordinates_Center_Z]) < 3)
					{
						ARRAY_ROCKET[i][rAction] = 0;
						DestroyObjectEx(ARRAY_ROCKET[i][rObject]);
						DestroyObjectEx(ARRAY_ROCKET[i][rObjectSecond]);
						DestroyObjectEx(ARRAY_ROCKET[i][rObjectThird]);
						ARRAY_ROCKET[i][rIdTarget] = 900;
						ARRAY_ROCKET[i][rTime] = 4;
						CreateExplosion(ARRAY_ROCKET[i][rCurrentX],ARRAY_ROCKET[i][rCurrentY],ARRAY_ROCKET[i][rCurrentZ],6,10);
					}
				}
			}
		}
	}
}

stock CreateExpl()
{
	if ( (ARRAY_TURRET[0][tAction] + ARRAY_TURRET[1][tAction] + ARRAY_TURRET[2][tAction] + ARRAY_TURRET[3][tAction] )!= 0 )//если задействоана хотя бы 1 турель , и есть хотя бы одна цель
	{
		for(new i =0; i < MAX_ROCKET; i++)
		{
			if (ARRAY_ROCKET[i][rAction] == 1)
			{
				ARRAY_ROCKET[i][rTime] --;
				if (ARRAY_ROCKET[i][rTime] == 0 )
				{
					ARRAY_ROCKET[i][rAction] = 0;
					DestroyObjectEx(ARRAY_ROCKET[i][rObject]);
					DestroyObjectEx(ARRAY_ROCKET[i][rObjectSecond]);
					DestroyObjectEx(ARRAY_ROCKET[i][rObjectThird]);
					ARRAY_ROCKET[i][rIdTarget] = 900;
					ARRAY_ROCKET[i][rTime] = 4;
					CreateExplosion(ARRAY_ROCKET[i][rCurrentX],ARRAY_ROCKET[i][rCurrentY],ARRAY_ROCKET[i][rCurrentZ],6,10);
				}
			}
		}
	}
}

//Данная функция принимает позицию x,y,z это есть позиция ракеты,
//принимает позицию x1,y1,z1 это позиция цели,
//так же мы знаем верхний вектор это 0.0.1 и вовращает вектор направления взгляда ракеты,
//осталось повернуть ракеты на нужный градус
stock GetViewVector(Float:x,Float:y,Float:z, Float:x1,Float:y1,Float:z1)
{
	new Float: x2;
	new Float: y2;
	new Float: z2;
	x2 = x1-x;
	y2 = y1-y;
	z2 = z1-z;
	new magn = MagnitudeVector(x2,y2,z2);
	VectorNormalize(x2,y2,z2,magn);
	new str[128];
	format(str,sizeof(str),"x = %f , y = %f , z = %f ",x2,y2,z2);
	SendClientMessageToAll(COLOR_RED,str);
}
//возвращает велечину ( длинну вектора )
stock MagnitudeVector(Float:x2,Float:y2,Float:z2)
{
	return floatround(floatsqroot(floatpower(x2,2)+floatpower(y2,2)+ floatpower(z2,2)));
}
//нормализуем вектор, чтобы получить веткор направления еденичной длинны
stock VectorNormalize(&Float:x2,&Float:y2,&Float:z2, magn)
{
	x2 = x2 / magn;
	y2 = y2 / magn;
	z2 = z2 / magn ;
	return 1;
}


//векторное произведение ( нужно для расчета направления нормали )
stock VectCross(Float:X0,Float:Y0,Float:Z0,Float:X1,Float:Y1,Float:Z1,&Float:X2,&Float:Y2,&Float:Z2)
{//не используется
	X2 = Y0*Z1 - Z0*Y1;
	Y2 = Z0*X1 - X0*Z1;
	Z2 = X0*Y1 - X1*Y0;
	return 1;
}


//вовращает угол между двумя точками
forward Float:GetAngleBetweenPoint(Float:x1,Float:y1,Float:x2,Float:y2);
public Float:GetAngleBetweenPoint(Float:x1,Float:y1,Float:x2,Float:y2)
{
	new Float:RX , Float:RY , Float:t, Float:a;
	//вычитаем вектора
	RX= x2 - x1;//полученные координаты RX , RY и будут являтся
	RY= y2 - y1;//вектором направления
	t = RX/RY;
	if ( t < 0 ) t = t * (-1);//вычисления должны быть по модулю , т.е все время положительные
	a = atan(t);//для перевод из радиан в градусы , а так же вычисления градуса для первой четверти
	if ((RX >= 0 ) && (RY>= 0 )) a = 360 -a;//четвертой четверти
	if ((RX <=0) && (RY<=0)) a = 180-a;//если находим угол в второй четверти окружности
	if ((RX >= 0) && (RY <= 0 )) a = 180+a;//если находим угол в третьей четверти круга
	return a;
}

forward Float:GetDistanceBeetweenPoint(Float:fcxR,Float:fcyR,Float:fczR,Float:fcxT,Float:fcyT,Float:fczT);
public Float:GetDistanceBeetweenPoint(Float:fcxR,Float:fcyR,Float:fczR,Float:fcxT,Float:fcyT,Float:fczT)
{
	new Float:d;
	d = floatsqroot( floatpower(floatsub(fcxR,fcxT),2)+ floatpower(floatsub(fcyR,fcyT),2)+floatpower(floatsub(fczR,fczT),2) );
	return d;
}

//возвращает угол между двумя точками по оси z , используем прямоугольный треугольник , со сторонами ABL
forward Float:GetAngleZBeetwenPoint(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);
public Float:GetAngleZBeetwenPoint(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	new Float:a;
	new Float:AB = GetDistanceBeetweenPoint(x1,y1,z1,x2,y2,z2);//находим длинну стороны AB
	new Float:AL = z2 - z1;//находим длинну стороны AL
	a = asin(AL/AB);//находим угол а между сторонами AB и BL
	return a;
}


stock GetPlayerCameraLookAt(playerid, &Float:X, &Float:Y, &Float:Z)
{ //возвращает координаты точки наблюдения
	new Float:Dis,
	Float:CamX, Float:CamY, Float:CamZ,
	Float:ObjX, Float:ObjY, Float:ObjZ,
	Float:FrX, Float:FrY, Float:FrZ;

	GetPlayerCameraPos(playerid, CamX, CamY, CamZ);
	GetPlayerPos(playerid, ObjX, ObjY, ObjZ);
	GetPlayerCameraFrontVector(playerid, FrX, FrY, FrZ);
	ObjX += 5.0 * floatsin(-GetAngleToPoint(CamX, CamY, ObjX, ObjY), degrees);
	ObjY += 5.0 * floatcos(-GetAngleToPoint(CamX, CamY, ObjX, ObjY), degrees);
	Dis = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));
	X = FrX * Dis + CamX;
	Y = FrY * Dis + CamY;
	Z = FrZ * Dis + CamZ;
}
//возвращает угол между двумя точками
forward Float:GetAngleToPoint(Float:x1, Float:y1, Float:x2, Float:y2);
public Float:GetAngleToPoint(Float:x1, Float:y1, Float:x2, Float:y2)
{
	new Float:Angle;
	Angle = atan2(y2 - y1, x2 - x1) + 270.0;
	return Angle < 360 ? Angle : (Angle - 360);
}



