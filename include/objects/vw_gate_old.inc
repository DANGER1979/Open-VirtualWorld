/*
#include <a_samp>
#include "../vw_defines"//���������
#include "../vw_plids"//����������� ������ /vw_Itter"//�-�� ��� ����������� �������� � ������� ��������
#include "../vw_arrays"//����� ������� VehicleArray, �.�. ���� � ��� �� ������ ����� ����������� �� ���� ��������
#include "../vw_player"
#include "../vw_sound"//�-�� �� ������ �� ������
#include "../objects/vw_object"//vw_radar
*/

//##############################################################################//
//                                                                              //
//                         ������� ��������� ��������                           //
//               ����������� �� ������� ������� F ��� ������� ����              //
//                                                                              //
//##############################################################################//

new bool:gAeroGate[MAX_PLAYERS][4];//��� �������� ��������� �����
new gGateStatus[27];//��� �������� ��������� �����

//##############################################################################//
//                                                                              //
//                          �������������� ��������                             //
//                                                                              //
//##############################################################################//
new oPDgateLS, oPDbarrierLS, oPDgateSF, oPDbarrierUpSF, oPDbarrierDownSF;
new oNGgate1, oNGgate2, oNGgate3, oNGgate4, oNGgate5, oNGgate6, oNGgate7, oNGgate8, oNGgate9, oNGgate10, oNGgate11;
new oLSAeroGate1, oLSAeroGate2; //Los Santos Airport
new oSF1AeroGate1, oSF1AeroGate2; //San Fierro Airport
new oSF2AeroGate1, oSF2AeroGate2; //San Fierro Airport2
new oLVAeroGate1, oLVAeroGate2; //Las Venturas Airport
new oHitmanDoor1, oHitmanDoor2;//ID ������
new oMedic1; //������ �� ���� �������
new oLCN1; //��� ���� LCN
new oYakuza1, oYakuza2; //��� ���� �����
new oHitman1; //��� ���� ��������
new oCityHallbarrier;
new oSAN;//SAN STUDIO GARAGE

new oLICgate1, oLICgate2, oLICbar;


new oAutoBuyer1, oAutoBuyer2, oAutoBuyer3, oAutoBuyer4, oAutoBuyer5; //��� ���� ���������



/*enum gate_object_INFO
{
	Float:fbiDist,//0 ��������� ��� ��������
//IsPlayerInRangeOfPoint ������ ����� �������� (����� ��������)
	Float:fbiX1,//1
	Float:fbiY1,
	Float:fbiZ1,
//IsPlayerInRangeOfPoint ������ ����� �������� (�� ��������)
	Float:fbiX2,//4
	Float:fbiY2,
	Float:fbiZ2,


//MoveObjectEx �������� ���������� �� ���������
	Float:fXfbi,//7
	Float:fY,
	Float:fZ,
	Float:frXfbi,//10
	Float:frY,
	Float:frZ,

//MoveObjectEx ���������� �� ��������
	Float:fX,//13
	Float:fY,
	Float:fZ,
	Float:frX,//16
	Float:frY,
	Float:frZ//18






}
static const stock Float:gate_object_moved[max_gate_obj][] = {
{1.5, -2460.719970, 527.817382, 54.034049, 	-2460.719970, 527.817382, 54.034049, 	-2460.719970, 527.817382, 54.034049, 0.000000, 0.000012, 179.999954, -2460.7200, 527.8174, 53.0101, 0.000000, 0.000012, 179.999954}, 

}*/

//##############################################################################//
//                                                                              //
//                      �������� ������������� ����������                       //
//                                                                              //
//##############################################################################//

new DoDgateCloseTimer;
new LICbarriertimer, LICbarriertimer1;
new PDgateCloseLStimer;
new PDbarrierCloseSFtimer;

forward tPDgateCloseLS();
forward tPDbarrierCloseSF();
forward tDoDgateClose();
forward tHallbarrier();

forward tLICClose();
forward tLICClose1();

stock gate_OnGameModeInit()
{
	new time = GetTickCount();
//��� ����� ������

//������ ��������
	oPDgateLS = CreateObjectEx(969, 1584.700,-1638.058,12.550, 0.0,0.0,0.0);//������������� ����������
//oPDbarrierLS = CreateObjectEx(2920, 1544.700,-1630.7911,13.100,90.0,0.0,180.0);//2920 - �������� �����������
	oPDbarrierLS = CreateObjectEx(968, 1544.700,-1630.7911,13.100,0.0,90.0,90.0);//968 - ��������.

	oPDgateSF = CreateObjectEx(10184,-1631.5000,688.2000,8.8000, 0.0,0.0,90.0);
	oPDbarrierDownSF = CreateObjectEx(968,-1572.230,658.800,6.900, 0.0,90.0,90.0);//968 - �������� ������
	oPDbarrierUpSF = CreateObjectEx(968,-1701.430,687.700,24.700,0.0,90.0,270.0);//968 - �������� ������
//������ ����
	oNGgate1 = CreateObjectEx(988, 96.800,1921.0000,18.200, 0.0,0.0,270.0);//������ ������
	oNGgate2 = CreateObjectEx(10671,213.9,1875.4,14.0,0.0,0.0,270.0);//������� ������
	oNGgate3 = CreateObjectEx(5856,238.45,1872.2806,10.6,0.0,0.0,0.0);//������
	oNGgate4 = CreateObjectEx(10671,256.3,1843.6,9.6,0.0,0.0,180.0);//������� ������
	oNGgate5 = CreateObjectEx(5856,248.7,1841.9,8.2,0.0,0.0,90.0);//������ ����� � ��������
	oNGgate6 = CreateObjectEx(5856,233.7,1823.0,6.8,0.0,0.0,0.0);//������ � ����
	oNGgate7 = CreateObjectEx(5856,283.35,1869.5,9.5,0.0,0.0,0.0);//������
	oNGgate8 = CreateObjectEx(5856,268.7,1864.0,8.5,0.0,0.0,90.0);//������ �� ������ ������� ����
	oNGgate9 = CreateObjectEx(1495,262.98,1819.5,1.0,0.0,0.0,0.0);//����� � ������
	oNGgate10 = CreateObjectEx(19313, 135.1046, 1941.5570, 21.7132, 0.0,0.0,0.0);//������ ������� ����� �������
	oNGgate11 = CreateObjectEx(19313, 286.0753, 1821.1231, 20.0406, 0.0,0.0,90.0);//������ ������� �� ���� ����� � ���� ���������
	oMedic1 = CreateObjectEx(2990, -2590.1101, 619.0, 17.3671, 0.0, 0.0, 0.0);
	oLCN1 = CreateObjectEx(980, 1264.1550, -2048.7988, 61.4840, 0, 0, 178.7255);
	oYakuza1 = CreateObjectEx(976, -2486.2579,-615.8809,131.7000, 0.0,0.0,267.0);
	oYakuza2 = CreateObjectEx(976, -2485.8579,-607.0078,131.7000, 0.0,0.0,267.0);
	oHitmanDoor1 = CreateObjectEx(1569,-689.63,943.5,12.45,0.0,0.0,0.0);//��� ��������
	oHitmanDoor2 = CreateObjectEx(1569,-686.63,943.5,12.45,0.0,0.0,180.0);
	oHitman1 = CreateObjectEx(980, -709.0244,962.9394,14.2305, 0.0,0.0,90.0384);
	oCityHallbarrier = CreateObjectEx(968, -2502.04,393.05,27.47,   0.00,270.00,18.38);
	oSAN = CreateObjectEx(2938, 983.9698,1123.7445,12.4668, 0.0,0.0,90.0);//����
	
	//oLICgate1 = CreateObjectEx(8229, -2036.2152, -102.8696, 36.7000,   0.00, 0.00, 0.00);
	//oLICgate2 = CreateObjectEx(8229, -2058.2986, -102.8593, 36.6000,   0.00, 0.00, 0.00);
	//oLICbar = CreateObjectEx(968, -2058.0767, -100.1775, 34.9824,   0.00, 90.00, 90.00);
//��� ���������
	oAutoBuyer1 = CreateObjectEx(10184, 2061.7102,2437.3999,12.3, 0.0,0.0,269.8999);//LV
	oAutoBuyer2 = CreateObjectEx(2885, 2813.3701,-1468.1800,19.0, 0.0,0.0,0.0);//LS
	oAutoBuyer3 = CreateObjectEx(2938, -1820.4499,1298.9293,18.7999, 0.0,0.0,272.6606);//SF
	oAutoBuyer4 = CreateObjectEx(2938, -1808.4699,1299.4873,18.7999, 0.0,0.0,272.6586);//SF
	oAutoBuyer5 = CreateObjectEx(10184, 2318.8125,1926.8,6.8342, 0.0,0.0,270.0);//LV
//oAutoBuyer5 = CreateObjectEx(10184, 2061.7102,2437.3999,12.3, 0.0,0.0,269.8999);
	oLSAeroGate1 = CreateObjectEx(988, 1964.342, -2189.776, 13.533, 0.0, 0.0, 180.0);
	oLSAeroGate2 = CreateObjectEx(988, 1958.851, -2189.777, 13.553, 0.0, 0.0, 180.0);
	oSF1AeroGate1 = CreateObjectEx(988, -1543.742, -432.703, 6.039, 0.0, 0.0, -45.0);
	oSF1AeroGate2 = CreateObjectEx(988, -1547.625, -428.82, 6.039, 0.0, 0.0, -45.0);
	oSF2AeroGate1 = CreateObjectEx(988, -1222.953, 53.826, 14.134, 0.0, 0.0, -135.0);
	oSF2AeroGate2 = CreateObjectEx(988, -1218.206, 68.883, 14.134, 0.0, 0.0, -135.0);
	oLVAeroGate1 = CreateObjectEx(988, 1704.777, 1605.165, 10.058, 0.0, 0.0, 73.0);
	oLVAeroGate2 = CreateObjectEx(988, 1706.364, 1610.422, 10.058, 0.0, 0.0, 73.0);
//��� ����� �����

	printf("11/19. [�������� MoveObject]: ���� ��������� - %d, ��������� - %d (ms)", oLVAeroGate2, GetTickCount() - time);//new time = GetTickCount();
}

stock gate_OnPlayerConnect(playerid)
{
	gAeroGate[playerid][0] = false; gAeroGate[playerid][1] = false; gAeroGate[playerid][2] = false; gAeroGate[playerid][3] = false;//��� �������� ��������� �����

}

//##############################################################################//
//#                                                                            #//
//#                      ���������������� ������� �������                      #//
//#                                                                            #//
//##############################################################################//
public tPDgateCloseLS()//����������� ����� 10 ������ 1 ��� �� ������� /gate
{
	MoveObjectEx(oPDgateLS, 1584.700,-1638.058,12.550, 0.5);//���������

	//SetObjectRot(oPDbarrierLS, 0.0,90.0,90.0);
	//StopObjectEx(oPDbarrierLS);
	MoveObjectEx(oPDbarrierLS, 1544.700,-1630.7911,13.100, 0.001, 0.0,90.0,90.0);//���������
	KillTimer(PDgateCloseLStimer);
	PDgateCloseLStimer = -1;
	gGateStatus[10] = 0;
	return 1;
}
public tPDbarrierCloseSF()//����������� ����� 5 ������ 1 ��� �� ������� /gate
{
	MoveObjectEx(oPDgateSF, -1631.5000,688.2000,8.8000, 0.5);//���������
	//SetObjectRot(oPDbarrierDownSF, 0.0,90.0,90.0);
	MoveObjectEx(oPDbarrierDownSF, -1572.230,658.800,6.900, 0.001, 0.0,90.0,90.0);//���������
	//SetObjectRot(oPDbarrierUpSF, 0.0,90.0,-90.0);
	MoveObjectEx(oPDbarrierUpSF, -1701.430,687.700,24.700, 0.001, 0.0,90.0,270.0);//���������
	KillTimer(PDbarrierCloseSFtimer);
	PDbarrierCloseSFtimer = -1;
	gGateStatus[11] = 0;
	return 1;
}
public tDoDgateClose()//����������� ����� 120 ������ 1 ���
{
	MoveObjectEx(oNGgate2,213.9,1875.4,14.0, 0.5);
	gGateStatus[2] = 0;//�������
	KillTimer(DoDgateCloseTimer);
	DoDgateCloseTimer = -1;
	return 1;
}
public tHallbarrier()//����������� ����� 10 ������ 1 ���
{
	MoveObjectEx(oCityHallbarrier, -2502.04,393.05,27.47, 0.001, 0.00,270.00,18.38);//���������
	gGateStatus[24] = 0;
	return 1;
}

public tLICClose()//����������� ����� 5 ������ 1 ��� �� ������� /gate
{
    MoveObjectEx(oLICgate1,-2036.2152, -102.8696, 36.7000, 1.0);
    MoveObjectEx(oLICgate2,-2058.2986, -102.8593, 36.6000, 1.0);
	KillTimer(LICbarriertimer);
	LICbarriertimer = -1;
	gGateStatus[25] = 0;
	return 1;
}
public tLICClose1()//����������� ����� 5 ������ 1 ��� �� ������� /gate
{
    MoveObjectEx(oLICbar, -2058.0767,-100.1775,34.9824, 0.001, 0.00,90.00,90.00);
    KillTimer(LICbarriertimer1);
 	LICbarriertimer1 = -1;
	gGateStatus[26] = 0;
	return 1;
}
//��� ����� ������
stock gate_OnPlayerKeyState_DRIVER(playerid)
{//���� ����� ����������
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	    if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	    if(IsPlayerControllable[playerid] == 1) return 1;
		//----------------------------------------------------------------------
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, COLOR_GREY, "  �� ������ ���������� �� ���� ������������� ��������!");
			return 1;
		}
		if(IsACop(playerid) || IsAMilitary(playerid))//PlayerInfo[playerid][pMember] == DoD)
		{
			if(IsPlayerInRangeOfPoint(playerid, 8.0, 96.8000,1924.6000,18.1420))
			{
			   	if(gGateStatus[1] == 0)
			   	{   //������ �� ������� ����
					MoveObjectEx(oNGgate1,96.800,1924.600,18.200, 2.5);
					gGateStatus[1] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oNGgate1,96.800,1921.0000,18.200, 1.0);
					gGateStatus[1] = 0;//�������
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 8.0, 135.1046, 1941.5570, 21.7132))
			{
			   	if(gGateStatus[22] == 0)
			   	{   //������ �� ������� ����
					MoveObjectEx(oNGgate10,121.6946, 1941.5570, 21.7132, 2.5);
					gGateStatus[22] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oNGgate10,135.1046, 1941.5570, 21.7132, 1.0);
					gGateStatus[22] = 0;//�������
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 8.0, 286.0753, 1821.1231, 20.0406))
			{
			   	if(gGateStatus[23] == 0)
			   	{   //������ �� ������� ����
					MoveObjectEx(oNGgate11,286.0753, 1833.9332, 20.0406, 2.5);
					gGateStatus[23] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oNGgate11,286.0753, 1821.1231, 20.0406, 1.0);
					gGateStatus[23] = 0;//�������
				}
			}
	   		else if(gGateStatus[10] == 0 &&
			   		(IsPlayerInRangeOfPoint(playerid, 8.0, 1592.200, -1638.058, 12.600) ||
		 			IsPlayerInRangeOfPoint(playerid, 8.0, 1544.700,-1630.7911,13.100)) )
			{
				gGateStatus[10] = 1;
				MoveObjectEx(oPDgateLS, 1592.200, -1638.058, 12.600, 3.0);//���������
				MoveObjectEx(oPDbarrierLS, 1544.700,-1630.7911,13.100+0.01, 0.001, 0.0,0.0,90.0);//���������

				PDgateCloseLStimer = SetTimer("tPDgateCloseLS", 10000, 0);//��������� ����� 10 ������ 1 ���
				SendClientMessage(playerid, COLOR_YELLOW, "������ � ����� ��������� ����� 10 ������");
			}
	   		else if(gGateStatus[11] == 0 &&
					(IsPlayerInRangeOfPoint(playerid, 8.0, -1572.230,658.800,6.900) ||
					IsPlayerInRangeOfPoint(playerid, 8.0, -1701.430,687.700,24.700) ||
					IsPlayerInRangeOfPoint(playerid, 8.0, -1631.0752,688.7227,7.1875))
			  )
			{
				gGateStatus[11] = 1;
				MoveObjectEx(oPDgateSF, -1631.5000,688.2000,12.8000, 3.0);//���������
				MoveObjectEx(oPDbarrierDownSF, -1572.230,658.800,6.900+0.01, 0.001, 0.0,0.0,90.0);//���������
				MoveObjectEx(oPDbarrierUpSF, -1701.430,687.700,24.700+0.01, 0.001, 0.0,0.0,270.0);//���������

				PDbarrierCloseSFtimer =	SetTimer("tPDbarrierCloseSF", 10000, 0);
				SendClientMessage(playerid, COLOR_YELLOW, "�������� ��������� ����� 10 ������");
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoH)
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, -2590.1101, 619.0, 17.3671))
			{
			   	if(gGateStatus[12] == 0)
			   	{   //������ �� ���� �������
					MoveObjectEx(oMedic1, -2590.1101, 619.0, 24.1, 2.5);
					gGateStatus[12] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oMedic1, -2590.1101, 619.0, 17.3671, 1.0);
					gGateStatus[12] = 0;//�������
				}
			}
		}
		else if(PlayerInfo[playerid][pMember] == LCN || (PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1))
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, 1264.1550, -2048.7988, 61.4840))
			{
			   	if(gGateStatus[13] == 0)
			   	{   //������ �� ���� ����
					MoveObjectEx(oLCN1, 1264.1550, -2048.7988, 66.7440, 2.5);
					gGateStatus[13] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oLCN1, 1264.1550, -2048.7988, 61.4840, 1.0);
					gGateStatus[13] = 0;//�������
				}
			}
		}
		else if(PlayerInfo[playerid][pMember] == Yakuza || (PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1))
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, -2486.2197,-615.9622,132.5676))
			{
			   	if(gGateStatus[14] == 0)
			   	{   //������ �� ���� �����
					MoveObjectEx(oYakuza1,-2486.2579, -620.4809, 131.7000, 2.5);
					MoveObjectEx(oYakuza2,-2485.8579, -602.3078, 131.7000, 2.5);
					gGateStatus[14] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oYakuza1,-2486.2579, -615.8809, 131.7000, 1.0);
					MoveObjectEx(oYakuza2,-2485.8579, -607.0078, 131.7000, 1.0);
					gGateStatus[14] = 0;//�������
				}
			}
		}
		else if(PlayerInfo[playerid][pMember] == Hitman || (PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1))
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, -709.0244, 962.9394, 14.2305))
			{
			   	if(gGateStatus[15] == 0)
			   	{   //������ �� ���� �����
					MoveObjectEx(oHitman1,-709.0244,962.9384,19.9500, 2.5);
					gGateStatus[15] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oHitman1,-709.0244, 962.9394, 14.2305, 1.0);
					gGateStatus[15] = 0;//�������
				}
			}
		}
		else if(PlayerInfo[playerid][pMember] == SAN)
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, 983.9698,1123.7445,12.4668))
			{
			   	if(gGateStatus[16] == 0)
			   	{
					MoveObjectEx(oSAN,983.9698,1123.7445,17.4668, 2.5);
					gGateStatus[16] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oSAN,983.9698,1123.7445,12.4668, 1.0);
					gGateStatus[16] = 0;//�������
				}
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoJ)
		{
			if(gGateStatus[24] == 0 &&
				IsPlayerInRangeOfPoint(playerid, 10.0, -2505.3914, 391.6142, 26.7614))
			{
				gGateStatus[24] = 1;
				MoveObjectEx(oCityHallbarrier, -2502.04,393.05,27.47+0.01, 0.001, 0.00,0.00,18.38);//���������

				SetTimer("tHallbarrier", 10000, 0);
				SendClientMessage(playerid, COLOR_YELLOW, "�������� ��������� ����� 10 ������");
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoE)
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, -2047.4301, -102.3202, 33.8409))
			{
				gGateStatus[25] = 1;
				MoveObjectEx(oLICgate1,-2036.2152+5.0, -102.8696, 36.7000, 2.5, 0.00, 0.00, 0.00);
				MoveObjectEx(oLICgate2,-2058.2986-5.0, -102.8593, 36.6000, 2.5, 0.00, 0.00, 0.00);
				LICbarriertimer = SetTimer("tLICClose", 10000, 0);
				SendClientMessage(playerid, COLOR_YELLOW,"������ ��������� ����� 10 ������");
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10.0, -2057.8062, -96.8301, 34.1287))
			{
				gGateStatus[26] = 1;
				MoveObjectEx(oLICbar, -2058.0767, -100.1775, 34.9824+0.01, 0.001, 0.00,0.00,90.00);
				LICbarriertimer1 = SetTimer("tLICClose1", 10000, 0);
				SendClientMessage(playerid, COLOR_YELLOW,"�������� ��������� ����� 10 ������");
				return 1;
			}
		}
		else if(PlayerInfo[playerid][pJob] == CARJACKER ||	PlayerInfo[playerid][pJob] == AUTOBUYER)
		{//��� ������������� //��� ���������
			if(IsPlayerInRangeOfPoint(playerid, 10.0, 2061.7102,2437.3999,12.3))
			{
			   	if(gGateStatus[17] == 0)
			   	{   //������ � ������� LV
					MoveObjectEx(oAutoBuyer1,2061.7102,2437.3999,15.8900, 2.5);
					gGateStatus[17] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oAutoBuyer1,2061.7102,2437.3999,12.3, 1.0);
					gGateStatus[17] = 0;//�������
				}
			}
 		}
		else
		{//��� ������������� //��� ���������
			if(IsPlayerInRangeOfPoint(playerid, 10.0, 2813.3701,-1468.1800,19.0))
			{
			   	if(gGateStatus[18] == 0)
			   	{   //������ � ������� SF
					MoveObjectEx(oAutoBuyer2,2813.3701,-1468.1800,15.1, 2.5);
					gGateStatus[18] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oAutoBuyer2,2813.3701,-1468.1800,19.0, 1.0);
					gGateStatus[18] = 0;//�������
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1820.4499,1298.9293,18.7999))
			{
			   	if(gGateStatus[19] == 0)
			   	{   //������ � ������� SF2.1
					MoveObjectEx(oAutoBuyer3,-1820.4499,1298.9293,13.7000, 2.5);
					gGateStatus[19] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oAutoBuyer3,-1820.4499,1298.9293,18.7999, 1.0);
					gGateStatus[19] = 0;//�������
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1808.4699,1299.4873,18.7999))
			{
			   	if(gGateStatus[20] == 0)
			   	{    //������ � ������� SF2.2
					MoveObjectEx(oAutoBuyer4,-1808.4699,1299.4873,13.7000, 2.5);
					gGateStatus[20] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oAutoBuyer4,-1808.4699,1299.4873,18.7999, 1.0);
					gGateStatus[20] = 0;//�������
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10.0, 2318.8125,1926.8,6.8342))
			{
			   	if(gGateStatus[21] == 0)
			   	{   //������ � ������� LV2
					MoveObjectEx(oAutoBuyer5,2318.8125,1926.8,1.8000, 2.5);
					gGateStatus[21] = 1;//�������
				}
			   	else
				{
					MoveObjectEx(oAutoBuyer5,2318.8125,1926.8,6.8342, 1.0);
					gGateStatus[21] = 0;//�������
				}
			}
		}
		return 1;
}
//��� ������� ������
stock gate_OnPlayerKeyState_SECONDARY(playerid)
{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;
    	if(IsPlayerControllable[playerid] == 1) return 1;
	    if(PlayerInfo[playerid][pVirtual] != 0)
	    {
			 //SendClientMessage(playerid, COLOR_GREY, "   � ���� ����������� ���� �� �� ������ ������� ������ !");
	        return 1;
	    }
		if(PlayerInfo[playerid][pJailed] == 10) return 1;
		if(IsPlayerInRangeOfPoint(playerid, 2.0, -688.0873,943.46135,13.6328))
		{

			if(PlayerInfo[playerid][pMember] == Hitman || (PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1))
			{
			   	if(gGateStatus[9] == 0)
			   	{   //������� ������� ������
      				//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oHitmanDoor1,-690.7,943.5,12.45, 1.0);
					MoveObjectEx(oHitmanDoor2,-685.55,943.5,12.45, 1.0);
					gGateStatus[9] = 1;//�������
					return 1;
				}
			   	else
				{
      				//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oHitmanDoor1,-689.63,943.5,12.45, 1.0);
					MoveObjectEx(oHitmanDoor2,-686.63,943.5,12.45, 1.0);
					gGateStatus[9] = 0;//�������
					return 1;
				}
			}
		}
		else if((IsPlayerInRangeOfPoint(playerid, 1.3, 210.2442,1876.5923,13.1406) ||
				IsPlayerInRangeOfPoint(playerid, 1.3, 218.0229,1873.9290,13.1470))
				&& IsAMilitary(playerid))//����� ������� �����
		{
		   	if(gGateStatus[2] == 0)
		   	{   //������� ������� ������
   				ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate2,213.9,1875.4,10.0, 0.5);
				gGateStatus[2] = 1;//�������

				DoDgateCloseTimer =	SetTimer("tDoDgateClose", 120000, 0);//��������� ����� 10 ������ 1 ���
				SendClientMessage(playerid, COLOR_YELLOW, "������ ��������� ����� 120 ������");
				return 1;
			}
		   	else
			{
       			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate2,213.9,1875.4,14.0, 0.5);
				gGateStatus[2] = 0;//�������
				return 1;
			}
		}
		else if((IsPlayerInRangeOfPoint(playerid, 1.3, 237.6213,1871.4099,11.4609) ||
				IsPlayerInRangeOfPoint(playerid, 1.3, 239.0206,1874.5546,11.4609))
				&& IsAMilitary(playerid))//�����
		{
		   	if(gGateStatus[3] == 0)
		   	{   //������ �� ������ ������ ��� ����������
		   		ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
   				//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate3,238.45,1872.2806,14.5, 0.5);
				gGateStatus[3] = 1;//�������
				return 1;
			}
		   	else
			{
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
       			//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate3,238.45,1872.2806,10.6, 0.5);
				gGateStatus[3] = 0;//�������
				return 1;
			}
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.3, 258.9297,1848.2714,8.5305)
				&& IsAMilitary(playerid))//�����
		{
		   	if(gGateStatus[4] == 0)
		   	{   //������� ������ ����. �������
		   		ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
   				//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate4,256.3,1843.6,5.8, 0.5);
				gGateStatus[4] = 1;//�������
				return 1;
			}
		   	else
			{
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
       			//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate4,256.3,1843.6,9.6, 0.5);
				gGateStatus[4] = 0;//�������
				return 1;
			}
		}
		else if(IsPlayerInRangeOfPoint(playerid, 1.3, 246.5218,1842.6549,8.7578)
				&& IsAMilitary(playerid))//�����
		{
		   	if(gGateStatus[5] == 0)
		   	{   //������ ����� � �������� ����. �������
		   		ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
   				//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate5,248.7,1841.9,12.1, 0.5);
				gGateStatus[5] = 1;//�������
				return 1;
			}
		   	else
			{
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
       			//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate5,248.7,1841.9,8.2, 0.5);
				gGateStatus[5] = 0;//�������
				return 1;
			}
		}
		else if( IsPlayerInRangeOfPoint(playerid, 2.0, 234.1830,1821.2523,7.4140)
				//&& PlayerInfo[playerid][pMember] == DoD && PlayerInfo[playerid][pRank] > 6
				&& IsAMilitary(playerid))//�����
		{
			if(PlayerInfo[playerid][pRank] < 7)
	        {
	            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ����� !");
	            return 1;
	        }
		   	if(gGateStatus[6] == 0)
		   	{   //������ � ����
		   		ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
   				//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate6,233.7,1823.0,10.7, 0.5);
				gGateStatus[6] = 1;//�������
				return 1;
			}
		   	else
			{
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
       			//OnePlayAnim(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate6,233.7,1823.0,6.8, 0.5);
				gGateStatus[6] = 0;//�������
				return 1;
			}
		}
		else if((IsPlayerInRangeOfPoint(playerid, 1.3, 284.2031,1871.3516,8.7578) ||
				IsPlayerInRangeOfPoint(playerid, 1.3, 282.4491,1866.6565,8.7578))
				&& IsAMilitary(playerid))//�����
		{
		   	if(gGateStatus[7] == 0)
		   	{   //������ �� ����� �����
   				ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate7,283.35,1869.5,12.5, 0.5);
				gGateStatus[7] = 1;//�������
				return 1;
			}
		   	else
			{
       			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate7,283.35,1869.5,9.5, 0.5);
				gGateStatus[7] = 0;//�������
				return 1;
			}
		}
 		else if(IsPlayerInRangeOfPoint(playerid, 1.3, 266.9619,1863.3983,8.7649)
		 		//&& PlayerInfo[playerid][pMember] == DoD
				&& IsAMilitary(playerid))
   		{ 	//CreateObjectEx(5856,268.7,1864.0,8.5,0.0,0.0,90.0);//������ �� ������ ������� ����
			if(PlayerInfo[playerid][pRank] < 7)
	        {
	            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ����� !");
	            return 1;
	        }
		   	if(gGateStatus[8] == 0)
		   	{   //������ �� ������ �������
       			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate8,268.7,1864.0,12.3, 1.5);
				gGateStatus[8] = 1;//�������
				return 1;
			}
		   	else
			{
       			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate8,268.7,1864.0,8.5, 2.5);
				gGateStatus[8] = 0;//�������
				return 1;
			}
		}
		//else SendClientMessage(playerid, COLOR_GREY, "   �� �� ����� ������ ������������ ���� 51 !");
  		else if(IsPlayerInRangeOfPoint(playerid, 1.3, 2053.6328,2436.7680,11.3907) ||
	  			IsPlayerInRangeOfPoint(playerid, 1.3, 2053.6328,2438.2031,11.3907) )
		{
			//GivePlayerMoneyH(1, playerid, -10);
			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
		   	if(gGateStatus[17] == 0)
		   	{   //������ � �������
				MoveObjectEx(oAutoBuyer1,2061.7102,2437.3999,15.8900, 2.5);
				gGateStatus[17] = 1;//�������
				return 1;
			}
		   	else
			{
				MoveObjectEx(oAutoBuyer1,2061.7102,2437.3999,12.3, 1.0);
				gGateStatus[17] = 0;//�������
				return 1;
			}
		}
		return 1;
}


stock gate_IsAtGate(playerid)
{
	if( IsPlayerInRangeOfPoint(playerid, 8.0, 96.8000,1924.6000,18.1420) ) return 1;//������ �� ������� ����
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, 1592.200, -1638.058, 12.600) ||
			IsPlayerInRangeOfPoint(playerid, 8.0, 1544.700,-1630.7911,13.100)
			) return 2;//������ � ����� LS
	else if(IsPlayerInRangeOfPoint(playerid, 8.0, -1572.230,658.800,6.900) ||
			IsPlayerInRangeOfPoint(playerid, 8.0, -1701.430,687.700,24.700) ||
			IsPlayerInRangeOfPoint(playerid, 8.0, -1631.0752,688.7227,7.1875)
			)  return 3;//tPDbarrierCloseSF
	else if( IsPlayerInRangeOfPoint(playerid, 8.0, 135.1046, 1941.5570, 21.7132) )  return 4;//������ ������� ����� �������
	else if( IsPlayerInRangeOfPoint(playerid, 8.0, 286.0753, 1821.1231, 20.0406) )  return 5;//������ ������� �� ���� ����� � ���� ���������
	else if( IsPlayerInRangeOfPoint(playerid, 10.0, -2590.1101, 619.0, 17.3671) )  return 6;//������ �� ���� �������
	else if( IsPlayerInRangeOfPoint(playerid, 10.0, 1264.1550, -2048.7988, 61.4840) ) return 7;//������ �� ���� ����
	else if( IsPlayerInRangeOfPoint(playerid, 10.0, -2486.2197,-615.9622,132.5676) )  return 8; //������ �� ���� �����
	else if( IsPlayerInRangeOfPoint(playerid, 10.0, -709.0244, 962.9394, 14.2305) )  return 9;//������ �� ���� �������
	else if( IsPlayerInRangeOfPoint(playerid, 10.0, 983.9698,1123.7445,12.4668) )  return 10;//������ ���������
	else if( IsPlayerInRangeOfPoint(playerid, 10.0, -2590.1101, 619.0, 17.3671) )  return 11;//������ �� ���� �������
	return 0;
}


stock gate_OnPlayerCommandText(playerid)
{
		if( IsPlayerInRangeOfPoint(playerid, 8.0, 96.8000,1924.6000,18.1420) &&
			IsAMilitary(playerid))//PlayerInfo[playerid][pMember] == DoD)
		{   //������ ��� �������
		   	if(gGateStatus[1] == 0)
		   	{   //������ �� ������� ����
				MoveObjectEx(oNGgate1,96.800,1924.600,18.200, 2.5);
				gGateStatus[1] = 1;//�������
			}
		   	else
			{
				MoveObjectEx(oNGgate1,96.800,1921.0000,18.200, 1.0);
				gGateStatus[1] = 0;//�������
			}
			//return 1;
		}
		else if(IsACop(playerid) ||
				PlayerInfo[playerid][pMember] == DoD)//IsAMilitary(playerid)
		{
       		if(gGateStatus[10] == 0 &&
			   (IsPlayerInRangeOfPoint(playerid, 8.0, 1592.200, -1638.058, 12.600) ||
				IsPlayerInRangeOfPoint(playerid, 8.0, 1544.700,-1630.7911,13.100)) )
			{
				gGateStatus[10] = 1;
				MoveObjectEx(oPDgateLS, 1592.200, -1638.058, 12.600, 3.0);//���������
				//SetObjectRot(oPDbarrierLS, 0.0, 0.0, 90.0);
				//StopObjectEx(oPDbarrierLS);
				MoveObjectEx(oPDbarrierLS, 1544.700,-1630.7911,13.100+0.01, 0.001, 0.0,0.0,90.0);//���������

				PDgateCloseLStimer = SetTimer("tPDgateCloseLS", 10000, 0);//��������� ����� 10 ������ 1 ���
				SendClientMessage(playerid, COLOR_YELLOW, "������ � ����� LS ��������� ����� 10 ������");
			}
       		else if( gGateStatus[11] == 0 &&
					(IsPlayerInRangeOfPoint(playerid, 8.0, -1572.230,658.800,6.900) ||
					IsPlayerInRangeOfPoint(playerid, 8.0, -1701.430,687.700,24.700) ||
					IsPlayerInRangeOfPoint(playerid, 8.0, -1631.0752,688.7227,7.1875))  )
			{
				gGateStatus[11] = 1;
				MoveObjectEx(oPDgateSF, -1631.5000,688.2000,12.8000, 3.0);//���������

				//SetObjectRot(oPDbarrierDownSF, 0.0, 0.0, 90.0);
				MoveObjectEx(oPDbarrierDownSF, -1572.230,658.800,6.900+0.01, 0.001, 0.0,0.0,90.0);//���������

				//SetObjectRot(oPDbarrierUpSF, 0.0, 0.0, 90.0);
				MoveObjectEx(oPDbarrierUpSF, -1701.430,687.700,24.700+0.01, 0.001, 0.0,0.0,270.0);//���������

				PDbarrierCloseSFtimer =	SetTimer("tPDbarrierCloseSF", 10000, 0);
				SendClientMessage(playerid, COLOR_YELLOW, "�������� ��������� ����� 10 ������");
			}
       		else if(IsPlayerInRangeOfPoint(playerid, 8.0, 135.1046, 1941.5570, 21.7132))
			{   //������ �� ������� ��� //������ ������� ����� �������
			   	if(gGateStatus[22] == 0)
			   	{   //������ �� ������� ����
			   		ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate10,121.6946, 1941.5570, 21.7132, 2.5);
					gGateStatus[22] = 1;//�������
				}
			   	else
				{
					ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate10,135.1046, 1941.5570, 21.7132, 1.0);
					gGateStatus[22] = 0;//�������
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 8.0, 286.0753, 1821.1231, 20.0406))
			{   //������ �� ������� ���//������ ������� �� ���� ����� � ���� ���������
			   	if(gGateStatus[23] == 0)
			   	{   //������ �� ������� ����
			   		ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate11,286.0753, 1833.9332, 20.04062, 2.5);
					gGateStatus[23] = 1;//�������
				}
			   	else
				{
					ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate11,286.0753, 1821.1231, 20.0406, 1.0);
					gGateStatus[23] = 0;//�������
				}
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoH &&
				IsPlayerInRangeOfPoint(playerid, 10.0, -2590.1101, 619.0, 17.3671))
		{
		   	if(gGateStatus[12] == 0)
		   	{   //������ �� ���� �������
				MoveObjectEx(oMedic1, -2590.1101, 619.0, 24.1, 2.5);
				gGateStatus[12] = 1;//�������
			}
		   	else
			{
				MoveObjectEx(oMedic1, -2590.1101, 619.0, 17.3671, 1.0);
				gGateStatus[12] = 0;//�������
			}
		}
		else if(	(
						PlayerInfo[playerid][pMember] == LCN  ||
						(PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1)
					) &&
					IsPlayerInRangeOfPoint(playerid, 10.0, 1264.1550, -2048.7988, 61.4840)
				)
		{
		   	if(gGateStatus[13] == 0)
		   	{   //������ �� ���� ����
				MoveObjectEx(oLCN1, 1264.1550, -2048.7988, 66.7440, 2.5);
				gGateStatus[13] = 1;//�������
			}
		   	else
			{
				MoveObjectEx(oLCN1, 1264.1550, -2048.7988, 61.4840, 1.0);
				gGateStatus[13] = 0;//�������
			}
		}
		else if(IsPlayerInRangeOfPoint(playerid, 10.0, -2486.2197,-615.9622,132.5676) &&
				(PlayerInfo[playerid][pMember] == Yakuza ||
				(PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1))
			   )
		{
		   	if(gGateStatus[14] == 0)
		   	{   //������ �� ���� �����
				MoveObjectEx(oYakuza1,-2486.2579, -620.4809, 131.7000, 2.5);
				MoveObjectEx(oYakuza2,-2485.8579, -602.3078, 131.7000, 2.5);
				gGateStatus[14] = 1;//�������
			}
		   	else
			{
				MoveObjectEx(oYakuza1,-2486.2579, -615.8809, 131.7000, 1.0);
				MoveObjectEx(oYakuza2,-2485.8579, -607.0078, 131.7000, 1.0);
				gGateStatus[14] = 0;//�������
			}
		}
		else if(	(
						PlayerInfo[playerid][pMember] == Hitman ||
						(PlayerInfo[playerid][pMember] == FBI && gGotOrder[playerid] != MAX_PLAYERS-1)
					) &&
					IsPlayerInRangeOfPoint(playerid, 10.0, -709.0244, 962.9394, 14.2305)
				)
		{
		   	if(gGateStatus[15] == 0)
		   	{   //������ �� ���� �����
				MoveObjectEx(oHitman1,-709.0244,962.9384,19.9500, 2.5);
				gGateStatus[15] = 1;//�������
			}
		   	else
			{
				MoveObjectEx(oHitman1,-709.0244, 962.9394, 14.2305, 1.0);
				gGateStatus[15] = 0;//�������
			}
		}
		else if(IsPlayerInRangeOfPoint(playerid, 10.0, 983.9698,1123.7445,12.4668) &&
				PlayerInfo[playerid][pMember] == SAN)
		{
		   	if(gGateStatus[16] == 0)
		   	{   //������ �� ���� �����
				MoveObjectEx(oSAN,983.9698,1123.7445,17.4668, 2.5);
				gGateStatus[16] = 1;//�������
			}
		   	else
			{
				MoveObjectEx(oSAN,983.9698,1123.7445,12.4668, 1.0);
				gGateStatus[16] = 0;//�������
			}
		}
}
//------------------------------------------------------------------------------
//��� ����� ������
stock gate_OnPlayerUpdate(playerid)//���������� �� OnPlayerUpdate
{
	if(PlayerInfo[playerid][pInt] != 0) { return 1; }
    //new Float:x, Float:y, Float:z;
	//GetPlayerPos(playerid, Float:x, Float:y, Float:z);
	if(PlayerInfo[playerid][pFlyLic] == 1 || IsPlayerNPC(playerid) ||
		(PlayerInfo[playerid][pJob] == TRUCKER && PlayerInfo[playerid][pCarTime] > 0
		/*&& (Cargo[ nTrailerID[playerid] ][tWhere] == 37 ||
		Cargo[ nTrailerID[playerid] ][tWhere] == 38 ||
		Cargo[ nTrailerID[playerid] ][tWhere] == 39)*/
		)
	  )
	{ //return 1;
	   	if(!gAeroGate[playerid][0] && IsPlayerInRangeOfPoint(playerid, 30.0, 1961.634, -2189.7765, 13.553)) 	// Los Santos Airport
	   	{
			MoveObjectEx(oLSAeroGate1, 1968.697, -2189.776, 13.553, 3);
			MoveObjectEx(oLSAeroGate2, 1954.571, -2189.777, 13.553, 3);
			gAeroGate[playerid][0] = true;//�������
		}
	   	else if(gAeroGate[playerid][0] && !IsPlayerInRangeOfPoint(playerid, 30.0, 1961.634, -2189.7765, 13.553))
		{
			CloseAPGate(1, playerid); gAeroGate[playerid][0] = false;
		}
	 	else if(!gAeroGate[playerid][1] && IsPlayerInRangeOfPoint(playerid, 30.0, -1545.6835, -430.7615, 6.039)) 	// San Fierro Airport
	   	{
			MoveObjectEx(oSF1AeroGate1, -1540.66, -435.786, 6.039, 3);
			MoveObjectEx(oSF1AeroGate2, -1550.709, -425.736, 6.039, 3);
			gAeroGate[playerid][1] = true;//�������
		}
	   	else if(gAeroGate[playerid][1] && !IsPlayerInRangeOfPoint(playerid, 30.0, -1545.6835, -430.7615, 6.039))
		{
			CloseAPGate(21, playerid); gAeroGate[playerid][1] = false;
		}
	   	else if(!gAeroGate[playerid][2] && IsPlayerInRangeOfPoint(playerid, 30.0, -1220.491, 61.443, 14.134)) 		// San Fierro Airport 2
	   	{
			MoveObjectEx(oSF2AeroGate1, -1226.59, 50.189, 14.134, 3);
			MoveObjectEx(oSF2AeroGate2, -1214.392, 72.697, 14.134, 3);
			gAeroGate[playerid][2] = true;//�������
		}
	   	else if(gAeroGate[playerid][2] && !IsPlayerInRangeOfPoint(playerid, 30.0, -1220.491, 61.443, 14.134))
  		{
		  	CloseAPGate(22, playerid); gAeroGate[playerid][2] = false;
			return 1;
		}
	   	else if(!gAeroGate[playerid][3] && IsPlayerInRangeOfPoint(playerid, 30.0, 1705.5705, 1607.7935, 10.058)) 	// Las Venturas Airport
	   	{
			MoveObjectEx(oLVAeroGate1, 1703.4, 1600.518, 10.058, 3);
			MoveObjectEx(oLVAeroGate2, 1707.722, 1614.937, 10.058, 3);
			gAeroGate[playerid][3] = true;//�������
		}
	   	else if(gAeroGate[playerid][3] && !IsPlayerInRangeOfPoint(playerid, 30.0, 1705.5705, 1607.7935, 10.058))
		{
			CloseAPGate(3, playerid); gAeroGate[playerid][3] = false;
		}
	}
	return 1;
}

stock CloseAPGate(airportid, playerid)//���������� �� CheckAPGates
{
	//new Float:x, Float:y, Float:z;
	//GetPlayerPos(playerid, Float:x, Float:y, Float:z);
	if(airportid == 1 && !IsPlayerInRangeOfPoint(playerid, 30.0, 1961.634, -2189.7765, 13.553))
	{   // Los Santos Airport
		MoveObjectEx(oLSAeroGate1, 1964.342, -2189.776, 13.533, 1);
		MoveObjectEx(oLSAeroGate2, 1958.851, -2189.777, 13.553, 1);
		//SendClientMessage(playerid, COLOR_GREEN, "airportid == 1 && !IsPlayerInRangeOfPoint");
		return 1;
	}
	if(airportid == 21 && !IsPlayerInRangeOfPoint(playerid, 30.0, -1545.6835, -430.7615, 6.039))
	{	// San Fierro Airport
		MoveObjectEx(oSF1AeroGate1, -1543.742, -432.703, 6.039, 1);
		MoveObjectEx(oSF1AeroGate2, -1547.625, -428.82, 6.039, 1);
		//SendClientMessage(playerid, COLOR_GREEN, "airportid == 21 && !IsPlayerInRangeOfPoint");
       	return 1;
	}
	if(airportid == 22 && !IsPlayerInRangeOfPoint(playerid, 30.0, -1220.491, 61.443, 14.134))
	{	// San Fierro Airport 2
		MoveObjectEx(oSF2AeroGate1, -1222.953, 53.826, 14.134, 1);
		MoveObjectEx(oSF2AeroGate2, -1218.206, 68.883, 14.134, 1);
		//SendClientMessage(playerid, COLOR_GREEN, "airportid == 22 && !IsPlayerInRangeOfPoint");
    	return 1;
	}
	if(airportid == 3 && !IsPlayerInRangeOfPoint(playerid, 30.0, 1705.5705, 1607.7935, 10.058))
	{	// Las Venturas Airport
		MoveObjectEx(oLVAeroGate1, 1704.777, 1605.165, 10.058, 1);
		MoveObjectEx(oLVAeroGate2, 1706.364, 1610.422, 10.058, 1);
		//SendClientMessage(playerid, COLOR_GREEN, "airportid == 3 && !IsPlayerInRangeOfPoint");
		return 1;
	}
	return 1;
}
//��� ����� �����
