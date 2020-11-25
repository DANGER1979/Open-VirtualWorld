stock camstate_OnPlayerUpdate(playerid)
//stock CheckCameraMode(playerid)
{
	new cameramode = GetPlayerCameraMode(playerid);
	static CameraMode[MAX_PLAYERS];
	if(cameramode != CameraMode[playerid])
	{
		CallLocalFunction("OnPlayerCameraStateChange", "ddd", playerid, cameramode, CameraMode[playerid]);
		CameraMode[playerid] = cameramode;
	}
}


forward OnPlayerCameraStateChange(playerid, newstate, oldstate);
public OnPlayerCameraStateChange(playerid, newstate, oldstate)
{
/*
camera 3: tram/train passenger entering camera (??!), tram/train driver camera - посадка в поезд/трамвай
camera 4: normal onfoot chasing camera (several variable distances) - нормальная камера на земле (5,6 - её другие позиции)
camera 7: sniper aiming mode - целимся из снайперки
camera 8: rpg aiming mode - целимся из РПГ
camera 15: chase cinematic camera (also spray garage camera) - кинематическая камера | А так же камера при заезде в покраски
camera 16: front closeup camera attached on car (+skimmer+heli+airplane) - камера "на бампере"
camera 18: normal car (+skimmer+helicopter+airplane) chase camera (several variable distances) - нормальная камера в машине (19,20,21 - её другие режимы)
camera 22: normal boat chase camera (several variable distances) - камера на катере
camera 46: picture-camera camera mode - режим при съемке фотоаппаратом
camera 51: heatseeker aiming mode - как я понял режим когда нацелен на игрока | Когда целишся с самонаводящего гранатомета)
camera 53: over-shoulder on-foot aiming with a weapon (any, including minigun) - целимся с любого другого оружия
camera 55: passenger window-driveby mode - пассажир высунулся из окна машины
camera 56: news-reporter style chase cinematic camera (wobbbling and zooming) - тоже какая-то кинематическая камера, сказано режим новостей.
*/
	if(newstate == 3)
	{
	    GameTextForPlayerEx(playerid, "~p~tram/train passenger exit/entering camera~r~3", 2000, 3);
	}
	else if(newstate == 4 || newstate == 5 || newstate == 6)
	{
	    //new strings[MAX_STRING];
		format(strings, sizeof(strings), "~p~normal onfoot chasing camera~r~%d", newstate);
	    GameTextForPlayerEx(playerid, strings, 1000, 3);
	}
	else if(newstate == 7)
	{
	    GameTextForPlayerEx(playerid, "~p~sniper aiming mode~r~7", 2000, 3);
	}
	else if(newstate == 8)
	{
	    GameTextForPlayerEx(playerid, "~p~rpg aiming mode~r~8", 2000, 3);
	}
	else if(newstate == 15)
	{
	    GameTextForPlayerEx(playerid, "~p~chase cinematic camera~r~15", 2000, 3);
	}
	else if(newstate == 16)
	{
	    GameTextForPlayerEx(playerid, "~p~front closeup camera attached on car~r~16", 2000, 3);
	}
	else if(newstate == 18)
	{
	    GameTextForPlayerEx(playerid, "~p~normal car chase camera~r~18", 2000, 3);
	}
	else if(newstate == 22)
	{
	    GameTextForPlayerEx(playerid, "~p~normal boat chase camera~r~22", 2000, 3);
	}
	else if(newstate == 46)
	{
	    GameTextForPlayerEx(playerid, "~p~picture-camera camera mode~r~46", 2000, 3);
	}
	else if(newstate == 51)
	{
	    GameTextForPlayerEx(playerid, "~p~heatseeker aiming mode~r~51", 2000, 3);
	}
	else if(newstate == 53)
	{
	    GameTextForPlayerEx(playerid, "~p~over-shoulder on-foot aiming with a weapon~r~53", 2000, 3);
	}
	else if(newstate == 55)
	{
	    GameTextForPlayerEx(playerid, "~p~passenger window-driveby mode~r~55", 2000, 3);
	}
	else if(newstate == 56)
	{
	    GameTextForPlayerEx(playerid, "~p~news-reporter style chase cinematic camera~r~56", 2000, 3);
	}
	else
	{

	    //new strings[MAX_STRING];
		format(strings, sizeof(strings), "~p~Unknown CameraMode ~r~%d", newstate);
	    GameTextForPlayerEx(playerid, strings, 3000, 3);
	}

}
