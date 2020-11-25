#include "../include/textdraw/txd_LOAD_TEXTURE.pwn"

new load_TX[MAX_PLAYERS];
new load_TX_progres[MAX_PLAYERS];
new Float:load_TX_i_progress1[MAX_PLAYERS];
new screensaver[MAX_PLAYERS] = -1;

const Float:load_TextureBoxPlus = 32.45;

stock SetLoadTexture(playerid)
{
	if(load_TX[playerid] == 1)
	{
	    PlayerTextDrawTextSize(playerid, LOAD_TEXTURE_PTD[playerid], -1.589998, 0.000000);
	    
	    PlayerTextDrawHide(playerid, LOAD_TEXTURE_PTD[playerid]);
	    load_TX_progres[playerid] = 0;
	    load_TX[playerid] = 0;
		for(new i; i < sizeof(LOAD_TEXTURE_TD); i ++)
		{
			TextDrawHideForPlayer(playerid, LOAD_TEXTURE_TD[i]);
		}
		PlayerTextDrawHide(playerid, LOAD_TEXTURE_PTD[playerid]);
	}

	ScreenSaver();
	for(new i; i < sizeof(LOAD_TEXTURE_TD); i ++)
	{
		TextDrawShowForPlayer(playerid, LOAD_TEXTURE_TD[i]);
	}
	
	ScreenSaverBar(playerid);
	PlayerTextDrawTextSize(playerid, LOAD_TEXTURE_PTD[playerid], -1.589998, 0.000000);//вернули начальную ширинку ползунка
	PlayerTextDrawShow(playerid, LOAD_TEXTURE_PTD[playerid]);
	
	load_TX[playerid] = 1;
    TogglePlayerControllableEx(playerid, 0);
	if(screensaver[playerid] != -1) { KillTimer(screensaver[playerid]); screensaver[playerid] = -1; }
	else screensaver[playerid] = SetTimerEx("LoadedScreenSaver", 100, true, "i", playerid); ////запускается постоянно каждые 250 мc до уничтожения
	return 1;
}
	
forward LoadedScreenSaver(playerid);
public LoadedScreenSaver(playerid)
{
	if(load_TX[playerid] == 1) LoadedTexture(playerid);
}
stock LoadedTexture(playerid)
{
	if(load_TX_progres[playerid] >= 20)
	{
	    PlayerTextDrawTextSize(playerid, LOAD_TEXTURE_PTD[playerid], -1.589998, 0.000000);
	    PlayerTextDrawHide(playerid, LOAD_TEXTURE_PTD[playerid]);
	    load_TX_progres[playerid] = 0;
	    load_TX[playerid] = 0;
		for(new i; i < sizeof(LOAD_TEXTURE_TD); i ++)
		{
			TextDrawHideForPlayer(playerid, LOAD_TEXTURE_TD[i]);
		}
		PlayerTextDrawHide(playerid, LOAD_TEXTURE_PTD[playerid]);
		TogglePlayerControllableEx(playerid, 1);
		
		KillTimer(screensaver[playerid]); screensaver[playerid] = -1;
	    return 1;
	}
    load_TX_i_progress1[playerid] = load_TextureBoxPlus * load_TX_progres[playerid];

	PlayerTextDrawTextSize(playerid, LOAD_TEXTURE_PTD[playerid], load_TX_i_progress1[playerid], 0.000000);
	PlayerTextDrawShow(playerid, LOAD_TEXTURE_PTD[playerid]);

	load_TX_progres[playerid] ++;
	return 1;
}

new PosTimer[MAX_PLAYERS];
stock SetPlayerPosC(playerid, Float:x, Float:y, Float:z, Float:ang)
{
	CurPos[0][playerid] = x;
	CurPos[1][playerid] = y;
	CurPos[2][playerid] = z;

	SetPlayerFacingAngle(playerid, ang);
	SetCameraBehindPlayer(playerid);
	ApplyAnimation(playerid, "PED", "Walk_Wuzi", 4.1, 0, 1, 1, 0, 2000);//1273
    TogglePlayerControllableEx(playerid, 0);//обездиживает
	if(PosTimer[playerid] != -1)
	{
	    KillTimer(PosTimer[playerid]);
	    PosTimer[playerid] = -1;
	}
	PosTimer[playerid] = SetTimerEx("@Pos_Timer", 2000, false, "d", playerid);
	return SetPlayerPos(playerid, x,y,z);
}
@Pos_Timer(playerid); @Pos_Timer(playerid)
{
	//if(check_lcn_tog[playerid] != 0) check_lcn_tog[playerid] = 0;
    TogglePlayerControllableEx(playerid, 1);
    KillTimer(PosTimer[playerid]);
    PosTimer[playerid] = -1;
	return 1;
}
