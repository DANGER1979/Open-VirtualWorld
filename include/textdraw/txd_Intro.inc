
	Intro[0] = TextDrawCreateEx(642.0, 1.0, "~n~");//чёрный экран
	TextDrawLetterSize(Intro[0], 0.5, 49.5);
	TextDrawUseBox(Intro[0], 1);
	TextDrawBoxColor(Intro[0], 0x000000FF);
	TextDrawTextSize(Intro[0], -2.0, 0.0);

	format(strtmp, sizeof(strtmp), "~p~~h~%s", CREATOR);
	Intro[1] = TextDrawCreateEx(195.000000, 170.000000, strtmp);
	TextDrawFont(Intro[1], 1);
	TextDrawLetterSize(Intro[1], 0.6, 1.8);

	Intro[2] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[2], 0);
	TextDrawColor(Intro[2], 0xFFFFFF22);
	TextDrawLetterSize(Intro[2], 0.6, 1.8);

	Intro[3] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[3], 0);
	TextDrawColor(Intro[3], 0xFFFFFF44);
	TextDrawLetterSize(Intro[3], 0.6, 1.8);

	Intro[4] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[4], 0);
	TextDrawColor(Intro[4], 0xFFFFFF66);
	TextDrawLetterSize(Intro[4], 0.6, 1.8);

	Intro[5] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[5], 0);
	TextDrawColor(Intro[5], 0xFFFFFF88);
	TextDrawLetterSize(Intro[5], 0.6, 1.8);

	Intro[6] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[6], 0);
	TextDrawColor(Intro[6], 0xFFFFFFAA);
	TextDrawLetterSize(Intro[6], 0.6, 1.8);

	Intro[7] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[7], 0);
	TextDrawColor(Intro[7], 0xFFFFFFCC);
	TextDrawLetterSize(Intro[7], 0.6, 1.8);

	Intro[8] = TextDrawCreateEx(310.0, 190.0, "present...");
	TextDrawFont(Intro[8], 0);
	TextDrawColor(Intro[8], 0xFFFFFFFF);
	TextDrawLetterSize(Intro[8], 0.6, 1.8);

	Intro[9] = TextDrawCreateEx(190.0, 202.0, ".");
	TextDrawFont(Intro[9], 1);
	TextDrawLetterSize(Intro[9], 30.0, 1.0);
	
	format(strtmp, sizeof(strtmp), "~y~~h~%s", SERVERNAME);
	//format(strtmp, sizeof(strtmp), "%s", SERVERNAME);
	Intro[10] = TextDrawCreateEx(304.00, 223.0, strtmp);
	TextDrawFont(Intro[10], 2);
	TextDrawLetterSize(Intro[10], 0.35, 1.0);

	format(strtmp, sizeof(strtmp), "~g~~h~%s", HostName);
	Intro[11] = TextDrawCreateEx(331.0, 235.0, strtmp);
	TextDrawFont(Intro[11], 2);
	TextDrawLetterSize(Intro[11], 0.35, 1.0);
	
	

new Float:p_FromX, Float:p_FromY, Float:p_FromZ;
new Float:p_ToX, Float:p_ToY, Float:p_ToZ;
new p_time;
stock InterpolateCameraPosEx(playerid, Float:FromX,Float:FromY,Float:FromZ, Float:ToX,Float:ToY,Float:ToZ, time, cut = CAMERA_CUT)
{
	p_FromX = FromX, p_FromY = FromY, p_FromZ = FromZ;
	p_ToX = ToX, p_ToY = ToY, p_ToZ = ToZ;
	p_time = time;//, p_cut = cut;
	InterpolateCameraPos(playerid, FromX,FromY,FromZ, ToX,ToY,ToZ, time, cut);
}



forward ShowIntro(playerid);
public ShowIntro(playerid)//разовый таймер
{   //запускается из OnPlayerConnect(playerid)
	SetPVarInt(playerid, "Intro", GetPVarInt(playerid, "Intro") + 1);
	new iteration = GetPVarInt(playerid, "Intro");
	switch(iteration)
	{
		case 1://0.5 sec
		{
			for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");
		    //TextDrawHideForPlayer(playerid, Intro[1]);
            TextDrawShowForPlayer(playerid, Intro[2]);//intro[2] = TextDrawCreateEx(310.0, 190.0, "present...");
		}
		case 2://0.75 sec
		{
		    TextDrawHideForPlayer(playerid, Intro[2]);
		    TextDrawShowForPlayer(playerid, Intro[3]);
		}
		case 3://1.0 sec
		{
		    TextDrawHideForPlayer(playerid, Intro[3]);
		    TextDrawShowForPlayer(playerid, Intro[4]);
		}
		case 4://1.25 sec
		{
		    TextDrawHideForPlayer(playerid, Intro[4]);
		    TextDrawShowForPlayer(playerid, Intro[5]);
		}
		case 5://1.5 sec
		{
		    TextDrawHideForPlayer(playerid, Intro[5]);
		    TextDrawShowForPlayer(playerid, Intro[6]);
		}
		case 6://1.75 sec
		{
		    TextDrawHideForPlayer(playerid, Intro[6]);
		    TextDrawShowForPlayer(playerid, Intro[7]);
		}
		case 7://2.0 sec
		{
		    TextDrawHideForPlayer(playerid, Intro[7]);
		    TextDrawShowForPlayer(playerid, Intro[8]);
		}

		case 8://4.0 sec
		{
		    TextDrawShowForPlayer(playerid, Intro[9]);//Intro[9] = TextDrawCreateEx(190.0, 202.0, ".");
		}

		case 9://8.0 sec
		{
		    TextDrawShowForPlayer(playerid, Intro[10]);
		}
		case 10://10.0 sec
		{
		    TextDrawShowForPlayer(playerid, Intro[11]);
		}
	}
	if(1 <= GetPVarInt(playerid, "Intro") < 7)
	{
		introtimer[playerid] = SetTimerEx("ShowIntro", 250, 0, "d", playerid);
	}
	else if(GetPVarInt(playerid, "Intro") == 7)//устанавливаем время через сколько запуститься Intro[9]
	{
		introtimer[playerid] = SetTimerEx("ShowIntro", 2000+500, 0, "d", playerid);
	}
	else if(GetPVarInt(playerid, "Intro") == 8)//устанавливаем время через сколько запуститься Intro[10]
	{
        introtimer[playerid] = SetTimerEx("ShowIntro", 3000+500, 0, "d", playerid);
	}
	else if(GetPVarInt(playerid, "Intro") == 9)
	{
        introtimer[playerid] = SetTimerEx("ShowIntro", 1000+500, 0, "d", playerid);
	}
	else if(GetPVarInt(playerid, "Intro") == 10)
	{
        introtimer[playerid] = SetTimerEx("ShowIntro", 3000+500, 0, "d", playerid);
	}
	else
	{
	    for(new i; i < sizeof(Intro); i++)
	    {
			TextDrawHideForPlayer(playerid, Intro[i]);
		}
		//TogglePlayerSpectating(playerid, 0);
		//ForceClassSelection(playerid);

	    PlayAudioStreamForPlayerEx(playerid, "GTAV_titles.mp3");
	    //PlayAudioStreamForPlayer(playerid, "https://dl.dropboxusercontent.com/s/z834k2bgngbcmm6/kbgdHubwVdkG.128.mp3");
		//SetTimerEx("StopAudioStreamForPlayerEx", 154000, 0, "i", playerid);

		SetPlayerTime(playerid, 5, 0); //SetPlayerWeather(playerid, 18);

	    SetPlayerPosEx(playerid, 155.3337, -1776.4384, 14.8978+5.0, 0);
	    SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);

		SetPlayerCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128);
		InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128, 156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);

		if(introtimer[playerid] != -1) { KillTimer(introtimer[playerid]); introtimer[playerid] = -1; }
		introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 0);
		//PlayerTextDrawShow(playerid, roleplay[playerid]);
		for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");
	}
	return 1;
}

forward OnPlayerFinishInterpolateCamera(playerid, step);
public OnPlayerFinishInterpolateCamera(playerid, step)
{   //запускается из ShowIntro --> OnPlayerConnect(playerid)
	switch(step)
	{
	    case 0:
		{
			SetPlayerTime(playerid, 6, 0);

		    //InterpolateCameraPos(playerid, 187.600982,-1791.727050,119.087432, 193.731567,-1789.235473,118.845245, 8000);
			//InterpolateCameraLookAt(playerid, p_FromX+1.40596, p_FromY+1.447265, p_FromZ+(-4.574791), p_ToX+1.325577, p_ToY+0.722656, p_ToZ+(-4.766625), p_time);
			InterpolateCameraPos(playerid, -2188.896240, -414.573028, 56.314990, -2145.781494, -442.977966, 40.509956, 8000);
			InterpolateCameraLookAt(playerid, -2184.333251, -415.880432, 54.743148, -2140.858642, -442.700225, 39.680477, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 1);

			//PlayerTextDrawLetterSize(playerid, txdPositionAppend[playerid], 0.586340, 3.052500);
			//PlayerTextDrawAlignment(playerid, txdPositionAppend[playerid], 2);
			//PlayerTextDrawColor(playerid, txdPositionAppend[playerid], -1);
			//PlayerTextDrawSetShadow(playerid, txdPositionAppend[playerid], -258);
			//PlayerTextDrawSetOutline(playerid, txdPositionAppend[playerid], 0);
			//PlayerTextDrawBackgroundColor(playerid, txdPositionAppend[playerid], -2139062017);
			//PlayerTextDrawFont(playerid, txdPositionAppend[playerid], 1);
			//PlayerTextDrawSetProportional(playerid, txdPositionAppend[playerid], 1);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "BloodBowl");
			PlayerTextDrawShow(playerid, txdPositionAppend[playerid]);
			//SetPlayerPosEx(playerid, -2008.220825, -102.025253, 39.343868, 0);

			GameTextForPlayerEx(playerid, " Press ~b~~k~~PED_SPRINT~ ~n~~w~to stop the presentation", 5000, 1);
		}
		case 1:
		{
			SetPlayerTime(playerid, 7, 0);

		    //InterpolateCameraPos(playerid, 300.803771, -1753.841796, 59.482250, 332.887237, -1753.466674, 60.534908, 4000);
			//InterpolateCameraLookAt(playerid, 302.467315, -1749.504394, 57.633026, 334.005126, -1748.907470, 58.813385, 4000);
			InterpolateCameraPos(playerid, -2008.220825, -102.025253, 39.343868, -2012.697143, -75.749816, 38.794345, 8000);
			InterpolateCameraLookAt(playerid, -2012.756958, -99.976760, 38.866729, -2015.363525, -79.848571, 37.750007, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 2);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "AutoSchool");
			//SetPlayerPosEx(playerid, -1997.691284,66.121589,31.389497, 0);
		}
		case 2:
		{
			SetPlayerTime(playerid, 8, 0);

		    //InterpolateCameraPos(playerid, 350.840972, -1794.716308, 13.146982, 346.193756, -1800.415649, 10.697548, 8000);
			//InterpolateCameraLookAt(playerid, 348.053558, -1790.653564, 12.295993, 342.141357, -1797.657592, 9.712170, 8000);
			InterpolateCameraPos(playerid, -1997.691284, 66.121589, 31.389497, -1994.008666, 96.354034, 37.039913, 5000);
			InterpolateCameraLookAt(playerid, -2002.644897, 66.191078, 30.713191, -1997.939331, 93.838455, 35.244953, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 3);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Fire Dept");
			//SetPlayerPosEx(playerid, -2394.341796, 318.923553, 36.965881, 0);
		}
		case 3:
		{
			SetPlayerTime(playerid, 9, 0);

		    //InterpolateCameraPos(playerid, 169.602859, -1775.647705, 6.933395, 169.617141, -1776.156250, 12.790164, 8000);
			//InterpolateCameraLookAt(playerid, 169.547332, -1770.651367, 7.117267, 169.588928, -1771.159301, 12.618641, 8000);
			InterpolateCameraPos(playerid, -2394.341796, 318.923553, 36.965881, -2378.807617, 343.265960, 35.953727, 8000);
			InterpolateCameraLookAt(playerid, -2398.629394, 321.341552, 36.087959, -2383.622314, 342.355438, 34.959415, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 4);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "CityHall");
			//SetPlayerPosEx(playerid, -2499.860107, 553.095642, 49.8656731, 0);
		}
		case 4:
		{
			SetPlayerTime(playerid, 10, 0);

		    //InterpolateCameraPos(playerid, 386.273284, -2030.129516, 59.993469, 395.822113, -2044.595703, 59.993469, 8000);
			//InterpolateCameraLookAt(playerid, 386.591949, -2029.832275, 55.012496, 396.252319, -2044.526245, 55.012496, 8000);
			InterpolateCameraPos(playerid, -2499.860107, 553.095642, 49.865673, -2496.180664, 572.490905, 49.608467, 5000);
			InterpolateCameraLookAt(playerid, -2504.221923, 555.330017, 48.874877, -2500.965820, 573.506225, 48.573043, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 5);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Hospital");
			//SetPlayerPosEx(playerid, -1567.417114, 679.081054, 54.204818, 0);
		}
		case 5:
		{
			SetPlayerTime(playerid, 11, 0);

		    //InterpolateCameraPos(playerid, 341.018402, -2095.904052, 6.937077, 342.805603, -2096.498535, 6.648118, 8000);
			//InterpolateCameraLookAt(playerid, 345.258972, -2093.501220, 5.821543, 347.304443, -2094.563964, 5.639461, 8000);
			InterpolateCameraPos(playerid, -1567.417114, 679.081054, 54.204818, -1574.820190, 755.655090, 56.388893, 8000);
			InterpolateCameraLookAt(playerid, -1571.126342, 678.303833, 50.943328, -1576.638305, 752.084899, 53.397533, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 6);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Police");

		}
		case 6:
		{
			SetPlayerTime(playerid, 12, 0);

		    //InterpolateCameraPos(playerid, 481.641052, -1804.006835, 6.803627, 484.250549, -1802.375244, 6.660738, 8000);
			//InterpolateCameraLookAt(playerid, 485.734344, -1801.318481, 5.794973, 488.679290, -1800.236572, 5.759444, 8000);
			InterpolateCameraPos(playerid, -1638.299194, 1200.744628, 8.852679, -1653.382568, 1207.741943, 8.064419, 5000);
			InterpolateCameraLookAt(playerid, -1642.660522, 1203.183349, 8.675631, -1658.266601, 1208.768920, 7.762429, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 7);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "AutoSalon");

		}
		case 7:
		{
			SetPlayerTime(playerid, 13, 0);

		    //InterpolateCameraPos(playerid, 662.689147, -1868.981201, 6.513285, 665.048583, -1870.174438, 6.864079, 8000);
			//InterpolateCameraLookAt(playerid, 658.142028, -1867.027709, 5.800874, 661.006286, -1867.294311, 6.260089, 8000);
			InterpolateCameraPos(playerid, -77.575767, -358.371948, 9.263011, -31.978124, -342.718688, 8.817116, 8000);
			InterpolateCameraLookAt(playerid, -73.415718, -356.873199, 6.928972, -31.518564, -337.789794, 8.113728, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 8);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Store House");

		}
		case 8:
		{
			SetPlayerTime(playerid, 14, 0);

		    //InterpolateCameraPos(playerid, 542.343933, -1901.457519, 2.008791, 544.523376, -1901.883666, 2.085470, 8000);
			//InterpolateCameraLookAt(playerid, 544.995666, -1897.256958, 2.577868, 546.892395, -1897.521118, 2.681705, 8000);
			InterpolateCameraPos(playerid, -856.736022, 1470.470214, 30.810400, -841.291870, 1488.731445, 25.552244, 5000);
			InterpolateCameraLookAt(playerid, -853.816406, 1474.378051, 29.712642, -838.233825, 1492.599365, 24.722761, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 9);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Bank");

		}
		case 9:
		{
			SetPlayerTime(playerid, 15, 0);

		    InterpolateCameraPos(playerid, 542.945800, -1863.699707, 4.435829, 539.996215, -1863.695556, 4.304386, 8000);
			InterpolateCameraLookAt(playerid, 537.950744, -1863.694213, 4.213245, 535.009887, -1863.990478, 4.081802, 8000);
			InterpolateCameraPos(playerid, 117.464828, 1913.241699, 94.821311, 321.959625, 1946.007202, 69.163063, 8000);
			InterpolateCameraLookAt(playerid, 120.362663, 1911.853393, 90.990486, 318.421752, 1943.527954, 66.645744, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 10);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Zone51");

		}
		case 10:
		{
			SetPlayerTime(playerid, 16, 0);

		    //InterpolateCameraPos(playerid, 329.131469, -1791.461791, 15.695193, 326.005981, -1793.169311, 15.695193, 3000);
			//InterpolateCameraLookAt(playerid, 326.451660, -1787.321044, 14.874702, 323.228546, -1789.171630, 14.553024, 3000);
			InterpolateCameraPos(playerid, 2054.914794, 2472.728271, 13.130291, 2052.286376, 2475.796386, 51.379493, 8000);
			InterpolateCameraLookAt(playerid, 2057.479492, 2468.452392, 12.758556, 2055.796875, 2472.270263, 50.886718, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 11);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Parking");

		}
		case 11:
		{
			SetPlayerTime(playerid, 17, 0);

		    //InterpolateCameraPos(playerid, 514.983886, -1760.605102, 17.303379, 514.898010, -1760.553955, 18.443613, 3000);
			//InterpolateCameraLookAt(playerid, 519.002807, -1762.556640, 15.058471, 519.071899, -1762.496826, 16.493217, 3000);
			InterpolateCameraPos(playerid, 1027.923950, 1198.372436, 41.781417, 1068.348876, 1107.852539, 20.557806, 8000);
			InterpolateCameraLookAt(playerid, 1028.435913, 1193.679321, 40.134288, 1066.504150, 1103.207763, 20.711338, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 12);
            PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "CNN Studio");

		}
		case 12:
		{
			SetPlayerTime(playerid, 18, 0);

		    //InterpolateCameraPos(playerid, 524.473022, -1763.555786, 14.948656, 524.520751, -1763.556152, 15.495350, 8000);
			//InterpolateCameraLookAt(playerid, 519.486999, -1763.304687, 14.671454, 519.540893, -1763.958007, 15.296504, 8000);
			InterpolateCameraPos(playerid, 1097.799438, 1706.247436, 12.708006, 1098.139404, 1625.411987, 14.500066, 8000);
			InterpolateCameraLookAt(playerid, 1098.240600, 1701.282714, 12.312586, 1098.336303, 1620.416381, 14.432359, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 13);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Kickstart");

		}
		case 13:
		{
			SetPlayerTime(playerid, 19, 0);

		    //InterpolateCameraPos(playerid, 545.416076, -1772.326171, 8.179362, 547.233886, -1774.291870, 8.147984, 8000);
			//InterpolateCameraLookAt(playerid, 548.811035, -1775.996459, 8.120770, 550.628845, -1777.962158, 8.089392, 8000);
			InterpolateCameraPos(playerid, 559.115112, 855.767272, -40.057350, 589.851440, 853.619628, -39.648780, 8000);
			InterpolateCameraLookAt(playerid, 559.142272, 860.733825, -40.634189, 588.859924, 858.452697, -40.460281, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 14);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "SaltMine");

		}
		case 14:
		{
			SetPlayerTime(playerid, 20, 0);

		    //InterpolateCameraPos(playerid, 550.013793, -1772.057128, 16.024028, 552.169799, -1772.079223, 16.285087, 8000);
			//InterpolateCameraLookAt(playerid, 546.803894, -1768.331054, 15.122734, 548.959899, -1768.353149, 15.383792, 8000);
			InterpolateCameraPos(playerid, -511.743469, -78.796165, 66.108871, -511.545715, -65.152145, 66.108871, 5000);
			InterpolateCameraLookAt(playerid, -516.705871, -78.697395, 65.504882, -516.500793, -65.533012, 65.559204, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 15);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Sawmill");
		}
		case 15:
		{
			SetPlayerTime(playerid, 21, 0);

		    //InterpolateCameraPos(playerid, 550.013793, -1772.057128, 16.024028, 552.169799, -1772.079223, 16.285087, 8000);
			//InterpolateCameraLookAt(playerid, 546.803894, -1768.331054, 15.122734, 548.959899, -1768.353149, 15.383792, 8000);
			InterpolateCameraPos(playerid, -1184.503540, -1056.001220, 134.057418, -1185.083862, -1044.250976, 134.057418, 5000);
			InterpolateCameraLookAt(playerid, -1189.403198, -1056.173706, 133.075561, -1189.978759, -1044.557495, 133.084503, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 16);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Farm");
		}
		case 16:
		{
			SetPlayerTime(playerid, 22, 0);

		    //InterpolateCameraPos(playerid, 545.416076, -1772.326171, 8.179362, 547.233886, -1774.291870, 8.147984, 8000);
			//InterpolateCameraLookAt(playerid, 548.811035, -1775.996459, 8.120770, 550.628845, -1777.962158, 8.089392, 8000);
			InterpolateCameraPos(playerid, 2757.517333, -2404.260498, 21.832336, 2756.082763, -2408.133544, 32.044303, 8000);
			InterpolateCameraLookAt(playerid, 2754.787597, -2407.933593, 19.818292, 2759.926025, -2411.074462, 30.787111, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 17);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Ocean Dock");

		}
		case 17:
		{
			SetPlayerTime(playerid, 23, 0);

		    //InterpolateCameraPos(playerid, 550.013793, -1772.057128, 16.024028, 552.169799, -1772.079223, 16.285087, 8000);
			//InterpolateCameraLookAt(playerid, 546.803894, -1768.331054, 15.122734, 548.959899, -1768.353149, 15.383792, 8000);
			InterpolateCameraPos(playerid, 2692.762207, -1926.317138, 34.247703, 2711.667724, -1876.023803, 12.873633, 8000);
			InterpolateCameraLookAt(playerid, 2694.021728, -1921.762084, 32.615425, 2713.234130, -1871.310058, 12.302284, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 18);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "8ball Track");
		}
		case 18:
		{
			SetPlayerTime(playerid, 0, 0);

		    //InterpolateCameraPos(playerid, 550.013793, -1772.057128, 16.024028, 552.169799, -1772.079223, 16.285087, 8000);
			//InterpolateCameraLookAt(playerid, 546.803894, -1768.331054, 15.122734, 548.959899, -1768.353149, 15.383792, 8000);
			InterpolateCameraPos(playerid, 428.604797, -2011.795898, 25.746875, 428.721282, -2051.508056, 25.746875, 8000);
			InterpolateCameraLookAt(playerid, 423.993927, -2012.983642, 24.220754, 424.074645, -2050.468994, 24.220754, 8000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 8000-600, 0, "id", playerid, 19);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Fish Vault");
		}
		case 19:
		{
			SetPlayerTime(playerid, 1, 0);

		    //InterpolateCameraPos(playerid, 550.013793, -1772.057128, 16.024028, 552.169799, -1772.079223, 16.285087, 8000);
			//InterpolateCameraLookAt(playerid, 546.803894, -1768.331054, 15.122734, 548.959899, -1768.353149, 15.383792, 8000);
			InterpolateCameraPos(playerid, 2208.699951, -1135.963012, 29.401437, 2217.816162, -1119.045410, 35.903774, 5000);
			InterpolateCameraLookAt(playerid, 2211.994140, -1139.263793, 27.597974, 2217.904785, -1123.767700, 34.262878, 5000);
			introtimer[playerid] = SetTimerEx("OnPlayerFinishInterpolateCamera", 5000-600, 0, "id", playerid, 20);
			PlayerTextDrawSetStringEx(playerid, txdPositionAppend[playerid], "Motel");
		}
		case 20:
		{
			SetPlayerTime(playerid, 2, 0);
			PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);

			//LoginPrepare(playerid);//запускаем проверку на наличие в базе аккаунта
		}
	}
	for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");
}


