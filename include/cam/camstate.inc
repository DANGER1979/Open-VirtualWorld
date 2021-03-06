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
camera 3: tram/train passenger entering camera (??!), tram/train driver camera - ������� � �����/�������
camera 4: normal onfoot chasing camera (several variable distances) - ���������� ������ �� ����� (5,6 - � ������ �������)
camera 7: sniper aiming mode - ������� �� ���������
camera 8: rpg aiming mode - ������� �� ���
camera 15: chase cinematic camera (also spray garage camera) - �������������� ������ | � ��� �� ������ ��� ������ � ��������
camera 16: front closeup camera attached on car (+skimmer+heli+airplane) - ������ "�� �������"
camera 18: normal car (+skimmer+helicopter+airplane) chase camera (several variable distances) - ���������� ������ � ������ (19,20,21 - � ������ ������)
camera 22: normal boat chase camera (several variable distances) - ������ �� ������
camera 46: picture-camera camera mode - ����� ��� ������ �������������
camera 51: heatseeker aiming mode - ��� � ����� ����� ����� ������� �� ������ | ����� ������� � �������������� �����������)
camera 53: over-shoulder on-foot aiming with a weapon (any, including minigun) - ������� � ������ ������� ������
camera 55: passenger window-driveby mode - �������� ��������� �� ���� ������
camera 56: news-reporter style chase cinematic camera (wobbbling and zooming) - ���� �����-�� �������������� ������, ������� ����� ��������.
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
