
//��� �������� ������
//new TutTimeCounter[MAX_PLAYERS];//������� � ������� ��������� � ������� ��������
//==============================================================================
//RegistrationSTEP4
stock Tutorial(playerid)//��� ��������
{
	if( TutTimeCounter[playerid] == 0 || TutTimeCounter[playerid] > 14 ) return 1;
	new bigmsgitem[1342];
	new caption[65];
    if(TutTimeCounter[playerid] == 1)
    {
    	SetPlayerTime(playerid, 5, 0);

		PlayAudioStreamForPlayerEx(playerid, "GTAtitles.mp3");
		SetTimerEx("StopAudioStreamForPlayerEx", 89000, 0, "i", playerid);

		strmid(caption, "1/14. ��������� ���������.", 0, 65, 65);
        //SetPlayerCameraPos(playerid, 1528.2993,-984.7744,100.2264);
		//SetPlayerCameraLookAt(playerid, 1313.8358,-779.9300,89.8182, CAMERA_CUT);

		TogglePlayerSpectatingEx(playerid, 1);//����������� ������ � ����� �������
		GetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
/*
	    SetPlayerPos(playerid, 155.3337, -1776.4384, 14.8978);//������������� ����� ��������� ��������
	    //TogglePlayerControllableEx(playerid, 0);//������������� ����� �� �����

	    SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);
		InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128,
			156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);
*/
	    SetPlayerPosEx(playerid, 155.3337, -1776.4384, 14.8978+5.0, 0);
	    SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);

		SetPlayerCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128);
		InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128, 156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);


		//for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");

		strins(bigmsgitem, "������������, ��������� �����. �� ���� �������������� ��� �� ������� ", strlen(bigmsgitem));
		strins(bigmsgitem, SERVERNAME, strlen(bigmsgitem));
        strins(bigmsgitem, "\n����������� �������������� ����������� ��������� �����. ���� ������", strlen(bigmsgitem));
        strins(bigmsgitem, "\n����� � ��� ��� - ������� �� �������� � ��������������� ����. ��� e-mail �� ������ ��������� 34 �������. ����� ����, ", strlen(bigmsgitem));
        strins(bigmsgitem, "\n�� ����� �������� �� ��������� ������� ������. ���������� - ������� F8. ����� �� ��, �� �������� ��������, �������", strlen(bigmsgitem));
        strins(bigmsgitem, "\n���������� � ����� 'GTA San Andreas User Files' � '���� ����������'. ����� ������ ������ ������, �.�. � ������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� ����� ����� ������, ������� ������ ���������. ������� �������� ����� ����������� - ��� �������� ���������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����. �� ������ �� ������� � ������� �������, � ��� ������������, � ���, ��� �� ����������. �� ��������� ���", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� �������� �����������, � ���������� ������� �����, � ������� ������� � '��������'. �� ������� ��� ������������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������, ���������; ��� ������� ����� � �� �����������. ������, ������� �������� - � ��� ����� ����� ������ ������.", strlen(bigmsgitem));
		SetPlayerWeather(playerid, 13);
    }
	else if(TutTimeCounter[playerid] == 2)
	{
		SetPlayerTime(playerid, 7, 0);
		strmid(caption, "2/14. ����� �������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 810.7180,-1574.1024,64.0412);//��
		//SetPlayerCameraLookAt(playerid, 1092.4534,-1425.0264,30.4647, CAMERA_CUT);

	    InterpolateCameraPos(playerid, 187.600982,-1791.727050,119.087432, 193.731567,-1789.235473,118.845245, 5000);
		InterpolateCameraLookAt(playerid, 189.006942, -1790.279785, 114.512641, 195.057144, -1788.512817, 114.078620, 5000);

		strins(bigmsgitem, "���� ������� ����� ���������� ��� '���������-������������� ��������� �����'. �� ���� � ����� �� ������������ ������ -", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ��������. ���� ������������� ��������� � ���, ������� ������ ���������� � �������� ������. ���������� ����������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ����������� ���� ����������� ������������. ��� ����� �������� �����, ��� � ���. ������ �� ��������� ����� ���, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� ������, ����������� ������ ��������. ������ ��� �������� ��������� ������� � ��������� � ����������. ������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����� ���� ��� ���� ������� ������� - ��� ���������� ����� � ������� �����, �������������� �������, ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������, ����������. ����������� � ������������ ����� ����������� �����. �� �� - ��������, ������������, ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������, ����������, ��������� ������������ � ���������� - ��������� ��������, ����� ���������� � �������� �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������. �� ������� � ����������, ��������� � ������� ��� ����� � ���. �� ������� �� �������� � ������, ����������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����������� �����, ������ �� �����, ����� � �������� � ��������, �������� �����. ������, ���� ����� ������.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 3)
	{
		SetPlayerTime(playerid, 9, 0);
		strmid(caption, "3/14. ������������� �����.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -1078.7716,1340.1995,52.3930);//��
		//SetPlayerCameraLookAt(playerid, -1617.2352,945.8327,29.4766, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 300.803771, -1753.841796, 59.482250, 332.887237, -1753.466674, 60.534908, 4000);
		InterpolateCameraLookAt(playerid, 302.467315, -1749.504394, 57.633026, 334.005126, -1748.907470, 58.813385, 4000);

		strins(bigmsgitem, "���������� ����� ����� �������� SA-MP, �� ����� ����� ����� ������� ��� ���� ������ ", strlen(bigmsgitem));
		strins(bigmsgitem, SERVERNAME, strlen(bigmsgitem));
		strins(bigmsgitem, ". ������ ��", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������, ��� ��� ������ ���������� �� ���� ���������. � ��� ���� ����������� ����, �� ������� ����� ����� ���", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ����������. ���� ���������� ��� ����������� ������ ��� �������������� ������ ������. ������� � ������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ��������������.  ��� ��������� ��������������, ������ ����������� �������������� � ������������ �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n � ��������� �� � �����. �������� ������� ����� ��������� � ��������� ���������������, ��� ��� �����������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������������ �������� � ��������� �� ���� �������. ��� ��������� �������� � ��� ���� ������� ����� � �����. ���� �� ������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����������,�� Paintball Arena ��� ���. �������� ��� ������������� ��������, ������� � ������� ����� ���������� � ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� �������. ������ ���, ��� ������� ������� � ���� ����� ����� � ���������� ��������.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 4)
	{
		SetPlayerTime(playerid, 13, 0);
		//SetPlayerCameraPos(playerid, -1947.2998,-33.9289,77.7945);//��
		//SetPlayerCameraLookAt(playerid, -2053.7312,-103.1463,40.7889, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 169.602859, -1775.647705, 6.933395, 169.617141, -1776.156250, 12.790164, 5000);
		InterpolateCameraLookAt(playerid, 169.547332, -1770.651367, 7.117267, 169.588928, -1771.159301, 12.618641, 5000);

		strmid(caption, "4/14. ������� �������� �����������.", 0, 65, 65);

		strins(bigmsgitem, "����� ��������� �������� ���������� ��� ���������� ����. ���� ����� ����� ������� ����� ��������� ���������� ��� ������� ���� ��� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ����� ������ ����� � ����������� � ���������� ���-������ ��� ����������� � �������� ���-���������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� /carinfo �������� ������ � ��� ��������� ���������� � ��� ����. ����� ���, ��� �������� ������ - �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ���� � /carinfo, ����� �� ���� ��������� �����������. ��� ����, ����� ��������� ��������, �� ����� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ���� �� �� ������ ������ ��� ������� �����, �� ��� ���������� �������� ��������� � ���-������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� �� ���������� �������� � 1 ������, �������� �� ����� � ������������� �������� �", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� - �� 2 ������, �������� �� �������� - � 10 ������. ��������� ������, ������ ����� ��� �� � �������� 24/7.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ��� ������ ��������� ��������� ������. �� ��������� ������������ �� �������������� ��������� �� ����� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ����� ����������� �������� /parking ��� �������� num4. ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� � �� ����������� (/unparking ��� �������� num6), � ��� ������ �� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� /lock(Alt+Space) ����� �������/������� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� (/engine) ������� ���������. ��� ����������� �������� �������� (2)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� �������������. �� ��������������� ������, ���� ����� ����� �����������.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 5)
	{
		SetPlayerTime(playerid, 15, 0);
		strmid(caption, "5/14. ���������� �������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -866.9181,1477.3292,36.4689);//����
		//SetPlayerCameraLookAt(playerid, -824.9084,1504.1040,19.8339, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 386.273284, -2030.129516, 59.993469, 395.822113, -2044.595703, 59.993469, 5000);
		InterpolateCameraLookAt(playerid, 386.591949, -2029.832275, 55.012496, 396.252319, -2044.526245, 55.012496, 5000);

		strins(bigmsgitem, "����������� ������� ��������� ������. ������ - �������� ������ ����� ����. �������� �� ������ �������������� �� ���", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ������� � ���������; �� ������ ����� ���������� ����������, ���, ������ ��� ��������������� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ������ �����, ����������� �� ���� �� ����� � ����� ���� ����� �� ������� ��� �����. ����� ����, �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������� ������������� ����� ���������� ������ ����������� ��������� � �����. ������� �� ������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����� ��������� ��������������� ����. ������� ������ ������ ����� ������������ ��� �������� �����: ������ - �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ��� � �������, ������� - �����, ������� �� ����� � �����. ���������� ����� �������� ������� ������ ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/pay id �����. ������������ ������ ������������ ����� - 1.000.000 �������� �� 3 ������. ���������� �� ����� � �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������� ������, �� �������� ����������� ��������� ������������� ������ ��������: ���������� �� �� ���� �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������, ������ �� �� ������� � �������� ��������. ������, ��������� ������ ���� ����������� ������� ����������.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 6)
	{
		SetPlayerTime(playerid, 17, 0);
		strmid(caption, "6/14. ������������ ��������� � ���������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -2410.1316,152.6538,101.9643);//�����
		//SetPlayerCameraLookAt(playerid, -2420.5745,334.9571,46.6400, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 341.018402, -2095.904052, 6.937077, 342.805603, -2096.498535, 6.648118, 5000);
		InterpolateCameraLookAt(playerid, 345.258972, -2093.501220, 5.821543, 347.304443, -2094.563964, 5.639461, 5000);

		strins(bigmsgitem, "� ����� �������� ���������� ��������������� ������������ ���������: �������, ������, �������� � �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� �������� �������������: ������� ������ ����� �������� ������ ������� �������, � ������ ����� �������� �� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ������ ����� �������� � �������� ������ �������� 2 ����� � 1 �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������� ����� ����� � �����, ������� �������� ��� � ��������� �����, �������� ������� ������, ��� �� �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ��� �������� � ��������. ������������ ���������(����� ������� � ��������) ����� ��������������� �� ������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ������� ����������. ������ ������ �� ������ �������� �� ���� ��������, ����� ����� ��� ������� ��� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ��������� ����������� /gps. ����� ����� ���� ������� �� ������� �������, ������� �������� ���������� ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� ����� �����, ��������������� �� �������. ��������, ����� �������� �����, ������� /gps 1014.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 7)
	{
		SetPlayerTime(playerid, 19, 0);
		strmid(caption, "7/14. ������� ������� � ������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -2027.1156,112.4540,49.6482);//������ ��
		//SetPlayerCameraLookAt(playerid, -1978.6957,138.3720,27.6875, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 481.641052, -1804.006835, 6.803627, 484.250549, -1802.375244, 6.660738, 5000);
		InterpolateCameraLookAt(playerid, 485.734344, -1801.318481, 5.794973, 488.679290, -1800.236572, 5.759444, 5000);
/*
		strins(bigmsgitem, "����� �� ������ � ����� /stats, �� �������, ��� � ��� 0 �������. ������� � ���� ���, �� �������� 10 ����� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ����� ��� ���������� ������������ ���-�� �����. ���� ������ �� ������, ������, ����� ���� � �.�. ���� ����� ���������� �", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ������� � ����������. ������� ���������� �������������. ������ ���� ������������: �� 2-�� ����� ������ �������� ��", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�����, ������������� � �������. �� 3-�� ����������� ������ ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������. � 10-�� ������ �������� �������� �� �������������. ������� �������, ��� ����� ������� ������ �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������: ��� ���� �������, ��� ������ ��� ����� ������� �� �������, ��� ���� ������ �� ��������� ���, ��� ���� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ����, ���� �� ������� ���������� �� ����������� �������. ��� ���� ��� ������� - ��� ���� ������� ����, �, �������������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� �������������.�� ��� ���������� 24 ������ �� ������� ������ ��� ������ ������.
*/
/*
		strins(bigmsgitem, "����� �� ������ � ����� /stats, �� �������, ��� � ��� 1 �������. ������� � ���� ���, �� �������� ���� ���� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ 8 ����� ����� � ���� 5.000, �� ������� �������� ���� ������� �� �������. �� �������� ������ - 12 ����� �", strlen(bigmsgitem));
		strins(bigmsgitem, "\n7.500, ��� ��������� - 16 ����� � 10.000 � ��� �����. ������ ���� ������������: �� 2-�� ����� ������ �������� ��", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�����, ������������� � �������. �� 3-�� �� ��������� ����� ���������� �� ������� � ����������� ������ ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������. � 10-�� ������ �������� �������� �� �������������. ������� �������, ��� ����� ������� ������ �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������: ��� ���� �������, ��� ������ ��� ����� ������� �� �������, ��� ���� ������ �� ��������� ���, ��� ���� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ����, ���� �� ������� ���������� �� ����������� �������. ��� ���� ��� ������� - ��� ���� ������� ����, �, �������������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� ������������� ����� ����� �������, �� ��� ���� ����� ����� ����� � ���� �������������. ����� ������ � ������ �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ��������� ���������������� ������ ���������. ����, ��������, ����, ��������� � �������, �� ������ ��������� �������� � �.�.", strlen(bigmsgitem));
*/

		strins(bigmsgitem, "����� �� ������ � ����� /stats, �� �������, ��� � ��� 1 �������. ������� � ���� 55 ����� ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����������� ��� � ���������� ���� � ������ ����� ����������. ������� ����� ��� ���������� ������������ ���-�� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ������ �� ����, ������, ��������, ������, ������, �� �� ������ ��� ���������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ����� ���������� ��� ������ ������� /score ��� � ����������. ������ ���� ������������: �� 2-�� ����� ������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� �� �����, ������������� � �������. �� 3-�� �� ��������� ����� ���������� �� ������� � ����������� ������ ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������. � 10-�� ������ �������� �������� �� �������������. ������� �������, ��� ����� ������� ������ �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������: ��� ���� �������, ��� ������ ��� ����� ������� �� �������, ��� ���� ������ �� ��������� ���, ��� ���� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ����, ���� �� ������� ���������� �� ����������� �������. ��� ���� ��� ������� - ��� ���� ������� ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������ ���� ��������� � ��� ���� ����� ����� ����� � ���� �������������. ����� ������ � ������ �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ��������� ���������������� ������ ���������. ����, ��������, ����, ��������� � �������, �� ������ ��������� �������� � �.�.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 8)
	{
		SetPlayerTime(playerid, 21, 0);
		strmid(caption, "8/14. ������������ �� �������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 1488.6250,-1612.5281,29.8676);//������� ��
		//SetPlayerCameraLookAt(playerid, 1553.9508,-1672.4800,16.6719, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 662.689147, -1868.981201, 6.513285, 665.048583, -1870.174438, 6.864079, 5000);
		InterpolateCameraLookAt(playerid, 658.142028, -1867.027709, 5.800874, 661.006286, -1867.294311, 6.260089, 5000);

		strins(bigmsgitem, "������� - ����� ������ �������, ������� �� ������. ����� ��������� ��� ��������� SMS, ������� TAB � ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������. ���� ��� ������, ��������� ������, ����� /h (����� �������� - /p). �� ������� �������� ����� ������� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ������� ���-������ � ������� 30 ������, �������� ������� (F6), �������� ������ ����� � ������� �� Enter.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ���� ����� '��������' � ������� 60 ������ - � ������� ������� /s ������ �����. ���� �� ������ �������� ���-������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� - ��� ����� '�����': /w id ������ �����. ������ ����� ��������� - 8 ������, � ������ ������ �� ����� �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���. ���������� ��� ���, ������� �������� ������������ ��� ������� ��������� - /me ������ �����. ���� ��� ����� ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n'����������' ��������� ��� ������, �� ����� ������ ��� ������� /s ����� �������, �.�. �������� ��� ������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ �������� ��������� ���� �������� ������ ������ ����� �����. ��� ����, ����� ������� ������� ��� - ������� /0.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ������� ��� ��������, ���� �� ����� ��������� ����� ��������� �����. ����������� ����� ����� ���������.", strlen(bigmsgitem));

		strins(bigmsgitem, "\n��� �� �� ������ ���������� ��������� ������. ������� � ���������(����� ������� �� ����� � �����)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����� � ���������� ����� ����� ������ �� ������ ��������� ������ ������, ������ ��� ��� � TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ���� ������ ����� ���������, ����� �� ������ ������ �����.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 9)
	{
		SetPlayerTime(playerid, 23, 0);
		strmid(caption, "9/14. �������� ������� � ����������, ������������ � ����.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 233.0978,1934.6124,39.0344);//���� 51
		//SetPlayerCameraLookAt(playerid, 203.6889,1866.8608,18.5625, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 542.343933, -1901.457519, 2.008791, 544.523376, -1901.883666, 2.085470, 5000);
		InterpolateCameraLookAt(playerid, 544.995666, -1897.256958, 2.577868, 546.892395, -1897.521118, 2.681705, 5000);

		strins(bigmsgitem, "���-������ (��, 1-�� �����) - �����, � ������� �� ���������, ����� �� ������. �������� ������: ������ �����������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ CNN ��� ��������, �����������, ����� 8ball. ���-������ (��, 2-�� �����) - �����, � ������� ����������� �����, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������, ���������. ���-�������� (��, 3-�� �����) - �����, � ������� ��������� �������, ������ ���. ��������� - ��.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����������� �������� (��) ���� � ������ ������. ����� ����� - '������ � �� ��'. ������� - ����� ��������� �� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nID - ����������������� �����, ������������� ������� ������, ��������� �� ������. ��� ����� ����� �������, ����� ��", strlen(bigmsgitem));
		strins(bigmsgitem, "\n'TAB'. ����� - �����, ������ ������. ���������� � �������� ������ � ��� ������������. ������� - ���� �����, �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� �������� �� ���������� ���. ����� - ������� ������� ���������. �� - ���������� ��������. ����� - �������������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������������� �������. �� (������������ �������) - ����� �����. �� - ������, ���-���������, ������ ����������. �� -", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������, ���-���������, ������������� ��������. �� - ���������������� ���������.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 10)
	{
		SetPlayerTime(playerid, 3, 0);
		strmid(caption, "10/14. ������� ������������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 1243.6803,-1273.6001,40.6886);
		//SetPlayerCameraLookAt(playerid, 1176.9855,-1322.7911,14.0483, CAMERA_CUT);
		InterpolateCameraPos(playerid, 329.131469, -1791.461791, 15.695193, 326.005981, -1793.169311, 15.695193, 3000);
		InterpolateCameraLookAt(playerid, 326.451660, -1787.321044, 14.874702, 323.228546, -1789.171630, 14.553024, 3000);

		strins(bigmsgitem, "������ ����� - ���������� ��������, ������� ����� ������ ������������: �����, �����, �������, ������, ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �������� ��������� ������ �����������, �� ������ ����������� ���������� ���� ����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ������� ������� ������������ ������� ������� Alt, �������� ��� ����������. �������� ������������:", strlen(bigmsgitem));
		strins(bigmsgitem, "\n1) �����. ��� ���������� ������ ������ �������� ���������� ��������: �� 10 ������ � ������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� ������ ����������� �����, � ���������� � ����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����, �������� �� ��������� � ����� ������. ����� ���������� ����� 3 ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n2) �����. ��� ���������� ������ ����� �� ����� ����� �� ���������, c���� � ����. ����� ���������� ����� 4 �. ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������: �������� � ����� (/dance 1-4) 2 ���. ��� ������ ��������: ���� ����� 10 ������ ������ �� 50.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n3) �������. ��� ���������� ����� ���������� ������������ ������ (/me, /s � �.�.). ����� ���������� ����� 5 �.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ��������� ���� ��������� �� ������� ��������. �������� ����������� ����� ��������� �� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n4) ������.��� ���������� ����� ��������� ��������� � ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������: �������� /piss � ������� 1 ���. ����� ���������� ����� 6 �.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n5) ��������.�������� ���������� �����: ��������� � ��� � ���������� ����������� �� �������� � ������� 5 ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������: �������� � ���(������), ����������� �� �������, ����� 1 ������(/bedl, /bedr). ����� ���������� ����� 7 �.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 11)
	{
		SetPlayerTime(playerid, 5, 0);
		//SetPlayerCameraPos(playerid, 2213.1982,-1103.3405,54.7576);//������ ��
		//SetPlayerCameraLookAt(playerid, 2201.2935,-1137.9199,38.1016, CAMERA_CUT);
		InterpolateCameraPos(playerid, 514.983886, -1760.605102, 17.303379, 514.898010, -1760.553955, 18.443613, 3000);
		InterpolateCameraLookAt(playerid, 519.002807, -1762.556640, 15.058471, 519.071899, -1762.496826, 16.493217, 3000);

        strmid(caption, "11/14. ������� ���������", 0, 65, 65);

		strins(bigmsgitem, "�� ����� ������� ����������� ������� ���������, �.�. ��� ����� �� �� ������ ������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���-����� ������� ��� ��� ������. �� �� ��������, ���������� � �����, �� ����������� � ������� ���-���", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������, �������� ��������� �����. ����� ������������� � �������, �������� ��� ��� � TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� 2 ���� �� ����, � ����������� ������ �������� ����� '�������������'.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ���� � ������ ������. ��������� � ������, ���������� �� ���� ������ ������� ����(������)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����� ������� ����� ������ ����(������� �����). ����� ���� �� �� �� ������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n �������� ����� '�������������'. ������ ����� ������ ��� ���-����. ����� �� ������� ��� ������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n �� ������ � ���� �������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �� ����� ������������ ������ ����� �������� ������ ������, �������� ��������/���������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������������ ��� ��������, �������� �������.", strlen(bigmsgitem));
    }
	else if(TutTimeCounter[playerid] == 12)
	{
		SetPlayerTime(playerid, 11, 0);
		//SetPlayerCameraPos(playerid, 2100.5708,1830.5414,60.7640);//��
		//SetPlayerCameraLookAt(playerid, 2250.2195,1899.3684,10.8203, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 350.840972, -1794.716308, 13.146982, 346.193756, -1800.415649, 10.697548, 8000);
		InterpolateCameraLookAt(playerid, 348.053558, -1790.653564, 12.295993, 342.141357, -1797.657592, 9.712170, 8000);

		strmid(caption, "12/14. ����, C���������, ����� � TeamSpeak.", 0, 65, 65);

		strins(bigmsgitem, "���������� �������: http://", strlen(bigmsgitem));
		strins(bigmsgitem, HostName, strlen(bigmsgitem));

		strins(bigmsgitem, "\nWiki: http://sa-mp.iam.by/wiki/index.php/VirtualWorld", strlen(bigmsgitem));

		strins(bigmsgitem, "\nForum: ", strlen(bigmsgitem));
		strins(bigmsgitem, FORUM, strlen(bigmsgitem));

	    //strins(bigmsgitem, "\nTeamSpeak3 BY Server Address: vpn.by:9990. Channel: GTA:SA Virtual World", strlen(bigmsgitem));
	    //strins(bigmsgitem, "\nTeamSpeak3 RU Server Address: ts.strikearena.ru. Channel: SAMP Virtual Word", strlen(bigmsgitem));

		strins(bigmsgitem, "\n���������� ������ ������� ��� ��� ���������� � ������ ������: �������, ���������� �����, �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����, �������, ����������, ���������� �������, ������� � �������. ������, ��, ��� ����� �����������. ����� ����, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����� ���������� ������ �������, ������ ����������, � ����� '��� �����' - ������ � ���� ���� ��������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ������� ���� Wiki(������������ ����������� ������ ����).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� �������� ��� ����������� ���������� ��� ���������� ����: �����������, FAQ, �����������, ������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ���������� �������, ��������� � ���������������� �������, ��������� ����� � ������ ������.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 13)
	{
		SetPlayerTime(playerid, 1, 0);
		strmid(caption, "13/14. ������ �������.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 1528.2993,-984.7744,100.2264);//��
		//SetPlayerCameraLookAt(playerid, 1313.8358,-779.9300,89.8182, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 542.945800, -1863.699707, 4.435829, 539.996215, -1863.695556, 4.304386, 5000);
		InterpolateCameraLookAt(playerid, 537.950744, -1863.694213, 4.213245, 535.009887, -1863.990478, 4.081802, 5000);

		strins(bigmsgitem, "��� �������, � �� ������� ������� ������ �������. �������� ��� ����� ������������, ��� �� ���������� ����� �����. ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ������, �� �� ����� �������� ���� ����� �����. ������� ���-�� ������������ ��������� ��� ��� ���������� ��", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������. ���� ��� �� ���� ���� ������ ������� - �������, ����� ���������� ����� ������� �� ���� ������� �������, ����� ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ����� ������. ������ ����� ������� ��������� ��� �������� ������� - ����� ���������� �� �������� �� ������ �", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� ���� ������ �����������. ������, �������� ���� ���� � ���������� ��������������� ��. � �������� � ��������������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� �������, �� ����������� ����� � ������ - � �� �������� � ��� �������� ������� ������. �� � ���� ������ �� �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������������ ���-���������, �.�. ��� ���� ��� ������ ������, � ��� ������ ������ ��������� � �������. �������, ��� �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �������� ��������� ������������, ������� � �������� � ���������, �������� ���������� ������� � ������� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ��� ����� � ���������� ���� ����. ���������� �� ��������. ������� ����.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 14)
	{
		SetPlayerTime(playerid, 5, 0);
		//SetPlayerCameraPos(playerid, 2213.1982,-1103.3405,54.7576);//������ ��
		//SetPlayerCameraLookAt(playerid, 2201.2935,-1137.9199,38.1016, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 514.983886, -1760.605102, 17.303379, 514.898010, -1760.553955, 18.443613, 3000);
		InterpolateCameraLookAt(playerid, 519.002807, -1762.556640, 15.058471, 519.071899, -1762.496826, 16.493217, 3000);

        strmid(caption, "14/14. � ����������.", 0, 65, 65);

		strins(bigmsgitem, "�������� �������� � �����. �� � ���� �� ����, ����� ������ �����������. ���� ���� ����� ���� ��� ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�����������, ����� ��������� ��������� �������� �� ���� ����. ������ �� ����� Helper`a�, ����� /question.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ������� - � ��� �������. � ��� ����� ��������� ������ �� ������� ����� ����� �����������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����� ���� ������� /accept referal. �� ������� �������� ��� �������, ����� /re �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ������� ������ �������� ����� �������� /help. �� ��������� ������� ������� /rules, ������� ������, �� ���������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� ���-��������. ����� ���� ������� ��� ������: ������� ����������� ���������� ������ ��� ������ ������������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ������� ����������� ��� ������������. ��������, ��� ���������� ������� ������� ������ ������ ��� ���������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� �������. �������, ������� ���� - �������� ������������ �� ����, ����� ������ � ������, ������� ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� � ������� ��������. ������ ��� ����� � ���������� ���� ����. ������� �� ��������. ������� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n\n���� �� � ���� ������� ����� �������:", strlen(bigmsgitem));
		strins(bigmsgitem, "\n{FF0000}CEPBEP: [��� ���] ��� �������, �������: ...", strlen(bigmsgitem));
		strins(bigmsgitem, "\n{A9C4E4}�� ����������� �������� �������� �������� F8, ����� ��� ��� �������� �� ����.", strlen(bigmsgitem));
    }
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error8: Tutorial %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, TUTORIAL_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "�����", "�����");//RegistrationSTEP5
	return 1;
}

stock tutorial_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != TUTORIAL_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
//ShowPlayerDialogEx(playerid, TUTORIAL_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "�����", "�����");
	if(response)
	{//���� ������ �����
	    TutTimeCounter[playerid] --;//�������
	    if(TutTimeCounter[playerid] < 1) TutTimeCounter[playerid] = 1;
		Tutorial(playerid);
		return 1;
	}
//���� ������ �����
    TutTimeCounter[playerid] ++;//�������
	if(TutTimeCounter[playerid] > 14)
	{
	    //InterpolateCameraPos(playerid, 524.473022, -1763.555786, 14.948656, 524.520751, -1763.556152, 15.495350, 5000);
		//InterpolateCameraLookAt(playerid, 519.486999, -1763.304687, 14.671454, 519.540893, -1763.958007, 15.296504, 5000);
		//StopAudioStreamForPlayer(playerid);
//TutTimeCounter[playerid] = 0;
	 	//if(GetPVarInt(playerid, "gStatusRegistration"))
	 	/*if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
	 	{
	    	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ����, ���������� ��������, �� ������ ������ �����������. ");
			SetPVarInt(playerid, "gOoc", 0); SetPVarInt(playerid, "gNews", 0);
			SetPVarInt(playerid, "gFam", 0); SetPVarInt(playerid, "gHidePM", 0);
			SetPVarInt(playerid, "gSport", 0); SetPVarInt(playerid, "gJob", 0);//��� ����
			//gMedicBill[playerid] = 0;
			//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}����������, ������� ���� ������� email (�� ����� 34 ��������) � ������� REGISTER !!!!");
			//AudioMessage(playerid, "����������, ������� ���� ������� email � ������� REGISTER.");
			RegistrationSTEP6(playerid);
		}
		else
		{*/
			TogglePlayerSpectatingEx(playerid, 0);//����������� ������ �� ������ �������
   			SetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
   			TogglePlayerControllableEx(playerid, 1);//�����������
			SetCameraBehindPlayer(playerid);
		//}
	}
	else
	{
		Tutorial(playerid);
	}
	return 1;
}



