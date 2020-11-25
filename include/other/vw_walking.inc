/*
 * Name: walking (запретить игроку бегать)
 * Type: Include
 * Author: NoGravity
 * Version: 0.1.1 R2
 *
 * All rights reserved!
 *
 * natives:
native TogglePlayerWalking(playerid, bool:toggle);
native bool:IsPlayerWalking(playerid);
native walking_OnPlayerUpdate(playerid);
native walking_OnPlayerDisconnect(playerid);
native walking_OnPlayerEnterVehicle(playerid);
 *
 * forwards:
 */
//No forwards



 /*
 * vars & arrays:
 *
 */
new bool:PlayerWalking[MAX_PLAYERS];
new bool:AnimTurned[MAX_PLAYERS];



/*
 *
 * define:
 *
 */
#define OnLeft(%1,%2) ((%1 < 0) && (%2 != 0))
#define OnRight(%1,%2) ((%1 > 0) && (%2 != 0))
#define OnOnlyLeft(%1,%2) ((%1 < 0) && (!%2))
#define OnOnlyRight(%1,%2) ((%1 > 0) && (!%2))



/*
 * stocks: 
 *
 */
stock TogglePlayerWalking(playerid, bool:toggle)
{
	if(!IsPlayerConnected(playerid) || IsPlayerInAnyVehicle(playerid)) return;
	PlayerWalking[playerid] = toggle;
}

stock bool:IsPlayerWalking(playerid)
{
	if(!IsPlayerConnected(playerid) || IsPlayerInAnyVehicle(playerid)) return false;
	return PlayerWalking[playerid];
}

//new Float:g_fSpeedCap[ MAX_PLAYERS ] = { 0.0, ... };

//stock walking_OnPlayerUpdate(playerid, newkeys, oldkeys)
stock walking_OnPlayerUpdate(playerid)
{
	//#pragma unused oldkeys
	if(!PlayerWalking[playerid]) return 1;
	if(IsPlayerInAnyVehicle(playerid)) return 1;
 	if(gPlayerBoxing[playerid] != 0) return 1;
	if(gInTerrorsCount[playerid] != 0) return 1;
	if(gInCTerrorsCount[playerid] != 0) return 1;

    new Float: v[3];
    GetPlayerVelocity(playerid, v[0], v[1], v[2]);
	if(v[2] > 0.1) return 1;
	new speed = floatround(
				floatsqroot
				(
					floatpower(v[0]*100.0,2)
					+ floatpower(v[1]*100.0,2)
					+ floatpower(v[2]*100.0,2)
				), floatround_floor//округляем в нижнее значение
			);
	/*if(speed <= 10) 
	{
		if(AnimTurned[playerid])
		{
			ClearAnimations(playerid);
			AnimTurned[playerid] = false;	
			return 1;
		}
	}*/
	
	//if( GetPVarInt(playerid, "IsShooting") ) return 1;
	
	new Keys, UpDown, LeftRight;
	GetPlayerKeys(playerid, Keys, UpDown, LeftRight);
//ВНИМАНИЕЖ: 
//при нажатии 'A' LeftRight возвращает -128
//при нажатии 'W' UpDown возвращает -128
//при нажатии 'S' UpDown возвращает 128
//при нажатии 'D' LeftRight возвращает 128
//Keys всё время равно 0

	//new anim_id = GetPlayerAnimationIndex(playerid);
	//if(anim_id != 971 && anim_id != 963 && anim_id != 965 && anim_id != 978 && anim_id != 976) return 1;//анимации при открытом парашуте
	//new newspeed = 3;//Новая скорость игрока
	
	if( (UpDown != 0) || ((LeftRight != 0)&&(UpDown == 0)) )
	{//если клавиши нажаты, т.е. есть движение, т.к. игрок не вертится вокруг оси
		if(!AnimTurned[playerid])
		{
			//ClearAnimations(playerid);
			//ApplyAnimation(playerid, "PED", "null", 1.0, 1, 1, 1, 0, 0);
			//ApplyAnimation(playerid, "PED", "WALK_PLAYER", 2.0, 1, 1, 1, 0, 0);
			//ApplyAnimation(playerid, "PED", "WALK_GANG2", 2.0, 1, 1, 1, 0, 0);	
	/*if(floatabs(v[0]) > floatabs(v[1]))
		SetPlayerVelocity( playerid, v[0]*newspeed*0.01/floatabs(v[0]), v[1]*newspeed*0.01/floatabs(v[0]), v[2] );
	else
		SetPlayerVelocity( playerid, v[0]*newspeed*0.01/floatabs(v[1]), v[1]*newspeed*0.01/floatabs(v[1]), v[2] );*/
			static
				Float:s_fX,
				Float:s_fY,
				Float:s_fZ,
				Float:s_fVX,
				Float:s_fVY,
				Float:s_fVZ;
						
			GetPlayerPos(playerid, s_fX, s_fY, s_fZ );
			GetPlayerVelocity(playerid, s_fVX, s_fVY, s_fVZ );
								
			static Float:s_fLength;
 
			s_fLength = floatsqroot( ( s_fVX * s_fVX ) + ( s_fVY * s_fVY ) + ( s_fVZ * s_fVZ ) );
 
			s_fVX = ( s_fVX / s_fLength ) * 0.1;
			s_fVY = ( s_fVY / s_fLength ) * 0.1;
			s_fVZ = ( s_fVZ / s_fLength ) * 0.1;
 
			SetPlayerVelocity( playerid, s_fVX, s_fVY, s_fVZ );
			AnimTurned[playerid] = true;//как только нажата клавиша равна 1
		}
	}
	else
	{//убираем анимацию после отпускания клавиш, иначе анимация будет проигрываться всё время и пед будет всё время идти
		//ClearAnimations(playerid);
		AnimTurned[playerid] = false;//становится равной 0 как только отпускается клавиша
	}

//чтобы при анимации можно было поворачиваться, иначе пед будет идти только прямо
	/*new Float: fa;	GetPlayerFacingAngle(playerid, fa);
	if(OnLeft(LeftRight, UpDown)) SetPlayerFacingAngle(playerid, fa+5.0);
	else if(OnRight(LeftRight, UpDown)) SetPlayerFacingAngle(playerid, fa-5.0);
	else if(OnOnlyLeft(LeftRight, UpDown)) SetPlayerFacingAngle(playerid, fa+20.0);
	else if(OnOnlyRight(LeftRight, UpDown)) SetPlayerFacingAngle(playerid, fa-20.0);*/

	if(CHECKING[PlayerKeyStateChange])
	{
		new strtmp[MAX_STRING];	
		format(strtmp, sizeof(strtmp), "walking_OnPlayerUpdate(playerid:%d, Keys:%d, UpDown:%d, LeftRight:%d) AnimTurned:%d speed:%d",
			playerid, Keys, UpDown, LeftRight, AnimTurned[playerid], speed);
		SendClientMessage(playerid, 0xFFFF00FF, strtmp);
	}
	return 1;
}

stock walking_OnPlayerDisconnect(playerid)
{
	ClearAnimations(playerid);
	PlayerWalking[playerid] = false;
	AnimTurned[playerid] = false;
}

stock walking_OnPlayerEnterVehicle(playerid)
{
	PlayerWalking[playerid] = false;
	AnimTurned[playerid] = false;
}
