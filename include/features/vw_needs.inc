//��� ��������
#if !defined SPECIAL_ACTION_PISSING
	#define SPECIAL_ACTION_PISSING 68
#endif


//##############################################################################//
//                                                                              //
//                             ������� ������������                             //
//                                                                              //
//##############################################################################//
//�����: ����� ���������� ����� 3 ����
//�����: ����� ���������� ����� 4 ����
//�������: ����� ���������� �����  5 �����
//������: ����� ���������� ����� 6 �����
//��������: ����� ���������� ����� 7 �����

//������ �����
new operator1 = 100;
new operator2 = 50;
new operator3 = 30;
new operator4 = 20;
new operator5 = 15;

//��� ������������ �����
new gParameter1[MAX_PLAYERS];//�����
new gParameter2[MAX_PLAYERS];//������
new gParameter3[MAX_PLAYERS];//�������
new gParameter4[MAX_PLAYERS];//������
new gParameter5[MAX_PLAYERS];//��������
//���� 1 ������ ��������� �����������



new gTogNeed = 1;//0

//##############################################################################//
//                                                                              //
//                                 �ר�����                                     //
//                                                                              //
//##############################################################################//


new TickCount1[MAX_PLAYERS];//������� ��� 1-� ���������� ���������
new TickCount2[MAX_PLAYERS];
new TickCount3[MAX_PLAYERS];
new TickCount4[MAX_PLAYERS];
new TickCount5[MAX_PLAYERS];

//##############################################################################//
stock IsNeeds(playerid)
{
	if(gParameter2[playerid] == 1)
	{
		 return 1;
	}
	return 0;
}

stock needs_OnPlayerConnect(playerid)
{

//��� ������������
	gParameter1[playerid] = 0;
	gParameter2[playerid] = 0;
	gParameter3[playerid] = 0;
	gParameter4[playerid] = 0;
	gParameter5[playerid] = 0;
	PlayerInfo[playerid][pParam1] = 0;
	PlayerInfo[playerid][pParam2] = 0;
	PlayerInfo[playerid][pParam3] = 0;
	PlayerInfo[playerid][pParam4] = 0;
	PlayerInfo[playerid][pParam5] = 0;
	TickCount1[playerid] = 0;
	TickCount2[playerid] = 0;
	TickCount3[playerid] = 0;
	TickCount4[playerid] = 0;
	TickCount5[playerid] = 0;
}



/*1)  ������� (��������������� ����������� [1], �������� ������ � ����������� ���������
�������� �������� ������������� ��� ���������� ������� � ����������� �������� �������� ���� � �����
(����� � �����) �������� ������. �������� ������� ����� �������������� ����������
(������������, ���������������������� � ������ �����), ���������� � ������������
(������������, ���������������������� � ������� ������), �����������
(���������������������� � ����������� � �������), ��������, ������ ������,
������� ���������������� ���������� � ���������������. ����� ����������� ������
����������������� (��������) ��� ���������, ����������� ����������, �����������
��� ����������, �������. ������������� ������� - ������������� �������� �������
������������ ��������� �������: ������, ������� � ���������� ��������������,
������� ������� (���, �������, �����, ����), �������� (���� ����� ���� � �������
����, ����������), ������������ ������� (������������� ����, ����� ��������������),
��� (���������� ��� �������), �������� ������� (����� ������, ����� ������������� �������) )
1�� + ����� ��������������

2)  ���� (���������������� ������ �������� ����������� ������� ����������� �����,
� ���� �������� ����������� ����� �������������� ������������� ��������.
�������� �������� ���� � �������, ������, �������, �������� ����, ���� � �����, ���������.)
2�� + ����� �������������� + �������� ������ ������ 5 ����� (/heist)

3)  ������� (������������� �������, ������������ ��� ����������� ��������� �� �������������
� ������� �������������� � �������������� ��������� ��������� �������� �������)
3�� + �������� ����� ������ 5 ����� (/vomit)

4)  ���������� ����
������� 4 �� + �������� ������ 5 ����� (/piss)

5)  ����������� ������������ (��������� �������, �������� �� �����������/���������. )
������� 5��  + �������� ��� ����� ��������� ������ 5 �����(/nut)

6)  ��������� (������������ ����� ����������� �������������������� �����������,
����������������� ����������� � ������������� ��������� ���������. )
6�� + �������� �������� �� ���� ������ 5 ����� (/crack)

7)  ������ (������������� ����������� ����� �������� (���������) ��������.
����������� ������� - ��� ���� ������� ������������ ����, �������� ������� ������� �� ���� �������.
����� ��� �������� ���������� ����������� ����, ����������� ����������� � �������, ��������� ��� �����.
����� ������������ ������� ������� ������������� ������� ��� ��������.
�������, �������� ��������, ����� ���������� ��������� � �������, ���� ����� ��������� ���������� ����.)
������� 7 �� + �������������� ������ 5 ����� (/heist)

8)  ����� (����������� �������������� ����������� ����������� �����, � �������
��������� ������� ������ ������ � ��������� ��������. ����������� ����������
������������� �������� ������������ �����������������, ������� �������� � �������������
�������� ��������� ������, ������, ������� ������������ � ����� � �����, ��������
�� ����� � ������ �����. ��� ������� ������ ������� � ����������������, �� ������������
�� ����� ������������ ���������� ����������� ����� � �����, ������� ����� ������
�������� ���� ���������, ���� ��� ��������� �������. ������������� �������.
- ��������� ����, ���, ���������� ���������, ������� ��������� � ��.
����������� ������� - ��������� ���������� ������������ ����� �������� ������� ������,
��������� �����, ������ � ������������ � ������� ������. )
8 �� + �������������� + �������� ������� ������ 5 �����.

9)  ��� (��� ��������������� �������, ������������� �� ������ ������������� �����
��������� ������� (����, ��������� �������� � ������ ���������� �������).
����������� ���������� - ������������ ���� ������� ������� ������� �� ����������������� �������,
�� ������ � �����, ������� ����������. �������� ������� ���������� ��������:
��������� ������ �������� �� ������������ ������� � ���� �������� �����������, ��������� ������ ���������.
����������� ����� ������������, ������� �������� ����, ���������������� � �������.
��������� ������ ������, ����������� �������� ��� ����������� ���� ����� �������,
������� ������, ���� � ������� ������� ������ ��� ������. ������ ����, �������� ��������,
���������������� ��������, ������� ��������� ����������� ����, ������,
���������� �������� ������ � ����������� ��������� �� �����, ����������� ��������� �� �������� ������,
����������� �������������� � �. �.)
������� 9�� + ������� �������������� + ������ �������� ������ 5 ����� (tazer)

10)  ��������� (���������� ������� ����� ������������� �������������
� ���������������� ���������� ������� � ���������������� ����� �������.
���������� ��������� ��������������� ������ �������� �����������, ������ � �������� ���������� ������� �������
� � ��������� ������� ����������� ����. ��� ������������: ���������� ������������ �����,
������� �������, �����������, ��������� ��������� ��������, ������� �����, � ����� �������,
������������� �����, ���������� �� ��������������)
10 �� + �������� ������ ������ 5 ����� (/heist) + ���������� ������

<19:02:02> "���.���. CID Nikalas_Ferpoint":
/animdozer 1, 2  - ��������
ApplyAnimation(playerid, "DOZER", "DOZER_Align_LHS",4.1,0,1,1,1,1);
ApplyAnimation(playerid, "DOZER", "DOZER_Align_RHS",4.1,0,1,1,1,1);

/animghetto 5
/animgraveyard 1 - ������
/animmedic - ���������� ��� ������
/animmisc 35 - ��������
/animpaulnmac - ��������
/scratching - �������
/animwuzi - �����

	ApplyAnimation(playerid, animlib, animname, animspeed, looping, lockx, locky, lockz, lp);//���������� �������� ��� ������
	//animlib - �������� ���������� ��������
	//animname - �������� ��������
	//animspeed - �������� ��������.
	//looping - ����������� (1) ��� ��� (0)
	//lockx - (0) - ������������ � ���. �������
	//locky - LockY - � �������� ������ ������� ������ ����� �� ��������� ���������,
	//������� ������� �����������. ����� ��������� �������,
	//��� ������������� � �������� ������� �� ���������, ���� ����������� �� 0.
	//��������������� ������ ���� ������������ �� 1.
	//lockz - ��������� ������ (1) � �������, ��������� (0)
	//lp - ����� ������� ����� ����� �� ����� ��� ��������� ��������. ������ � �������������. ��� ������������ ����� ������ ���� 0.
*/

stock needs_OneMinutsTimer(playerid, animationid)//OnPlayerDisease1Timer(playerid)//����������� ������ ������
{   //��� �������� � ������
	if(spectateid[playerid] != MAX_PLAYERS-1) return 1;
	//new strings[MAX_STRING];
    new Float: health = LastHealth[playerid];
    //GetPlayerHealth(playerid, health);
	if(	gTogNeed && PlayerInfo[playerid][pJailed] == 0
		&& IsPlayerControllable[playerid] == 0
		&& FollowBy[playerid] == MAX_PLAYERS-1)
	{
//��� ������������
//����� ������ ��������� ��������� �� 97 �����(58000)
//����� ������ ��������� ��������� �� 143 �����(178000)
//������� ������ ��������� ��������� �� 149 �����(298000)
//������ ������ ��������� ��������� �� 199 �����(598000)
//�������� ������ ��������� ��������� �� 240 �����(958000)
/*	new operator1 = 100;
	new operator2 = 50;
	new operator3 = 30;
	new operator4 = 20;
	new operator5 = 15;*/
		/*if(gParameter1[playerid] == 1)
		{
			if(PlayerInfo[playerid][pParam1] <= 0)
			{
				PlayerInfo[playerid][pParam1] = 0;
				gParameter1[playerid] = 0;
				SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], 100);
			}
		}*/
		if(	gParameter1[playerid] == 1 &&
			HUNGER == 1 && PlayerInfo[playerid][pLevel] > 2)
		{
			SetPlayerHealthEx(playerid, (health-10.0));//������ ������ ��������� ��������, ���� �����
			format(strings, sizeof(strings), "%s ������� %d �������� ��-�� ������", PlayerName(playerid), 10);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
		}
		//----------------------------------------------------------------------
		//�����
		if(	(GetCheckpointType(playerid) == CP_BAR || GetCheckpointType(playerid) == CP_PUMP || GetCheckpointType(playerid) == CP_INN ||
			GetCheckpointType(playerid) == CP_PIGPEN || GetCheckpointType(playerid) == CP_STRIP ||
			GetCheckpointType(playerid) == CP_ALHAMBRA || GetCheckpointType(playerid) == CP_JIZZY) &&
			(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE1 ||
			GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE2 ||
   			GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE3 ||
      		GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE4) &&
      		PlayerInfo[playerid][pParam2] > 0 )
		{
			PlayerInfo[playerid][pParam2] -= 25;//30 ����� �������
			if(PlayerInfo[playerid][pParam2] < operator2) gParameter2[playerid] = 0;//�������� - ��� ������ �����������
			if(PlayerInfo[playerid][pParam2] <= 0) PlayerInfo[playerid][pParam2] = 0;//��������
			SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);
		}
		/*else if(PlayerInfo[playerid][pParam2] >= 50)
		{
			if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PAULNMAC","wank_loop",4.1,1,0,0,1,0,1);//������
			PlayerInfo[playerid][pParam2] -= 1;
		}*/
		//----------------------------------------------------------------------
		/*if(PlayerInfo[playerid][pParam3] >= 30)//�������
		{
			//if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "benchpress","gym_bp_celebrate",4.1,1,0,0,1,0,1);
			PlayerInfo[playerid][pParam3] -= 3;
			if(PlayerInfo[playerid][pParam3] <= 0)
			{
				gParameter3[playerid] = 0;
				ClearAnimations(playerid, 1);
				ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
		}*/
		//----------------------------------------------------------------------
		if(	GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_PISSING
			 && PlayerInfo[playerid][pParam4] > 0)//������
		{//���� ������� ������ ����� �������� �����������
			PlayerInfo[playerid][pParam4] -= 20;//1 ������ �������
			if(PlayerInfo[playerid][pParam4] <= 0)
			{
				PlayerInfo[playerid][pParam4] = 0;
				gParameter4[playerid] = 0;
				ClearAnimations(playerid, 1);
				ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
			SetPlayerShowScale(playerid, 4, PlayerInfo[playerid][pParam4], operator4);
		}
		if(gParameter4[playerid] == 1)
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
		         SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
		         PlaySoundForPlayerInRange(playerid, SOUND_PISSING, 30.0);
		   	     ApplyAnimation(playerid, "PAULNMAC","Piss_in",4.1,1,0,0,1,60000,1); //������
			}
		}
		//-----------------------------------------------------------------------
		//��������
		if(	(PlayerInfo[playerid][pLocal] >= 0 && PlayerInfo[playerid][pLocal] < 100) ||
			PlayerInfo[playerid][pLocal] == 243 ||//������� LCN
			PlayerInfo[playerid][pLocal] == 244 ||//������� Yakudza
			PlayerInfo[playerid][pLocal] == 254 ||//������
			PlayerInfo[playerid][pLocal] == 240 //Barracks Officers
			)// && PlayerInfo[playerid][pParam5] > 0

		{   //���� ������� ���� � ���� ��� ������ ��� � �������
			//new anim_id = PlayerLastAnimation[playerid];//GetPlayerAnimationIndex(playerid);
			if(animationid)
			{//���� ������� ����� �� ��������
				new animNew[32]; new animlib[32];//"PED", "FLOOR_hit"
				GetAnimationName(animationid, animlib, 32, animNew, 32);
				if(	strlen(animNew) &&
					(!strcmp(animNew, "FLOOR_hit", true) ||//��� ������� ����� ���������� 0 ���� ����� ������ ������.
					!strcmp(animNew, "BED_LOOP_L", true) ||
					!strcmp(animNew, "BED_LOOP_R", true)) )
				{
					PlayerInfo[playerid][pParam5] = 0;
					gParameter5[playerid] = 0;
					SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);
				}
				strmid(animOld[playerid], animNew, 0, strlen(animNew), 32);
			}
		}
		if(gParameter5[playerid] == 1)//��������
		{   //���� ����������� �������� ���������
			gTextDrawShowBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			SetTimerEx("tHidePlayerBlind", 5000, 0, "d", playerid);
			format(strings, sizeof(strings), "%s ��� ������ ����� �����, ��� �������� ������ � ������ ����� �� 5 ������", PlayerName(playerid));
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
		}
	}
	//==========================================================================
	if(PlayerInfo[playerid][pSTD] <= 0 || PlayerInfo[playerid][pSTD] == IsNotBeenIll) return 1;
	PlayerNowAnimCount[playerid] = CHEATLIM;//�������� 2 �������
	if(PlayerInfo[playerid][pSTD] == 1)
	{
	    SetPlayerHealthEx(playerid, (health-1.0));
		format(strings, sizeof(strings), " %s ������� 1 �������� � ���������� �������.", PlayerName(playerid));
		SetPlayerDrunkLevel(playerid, 3*1000);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "WUZI","CS_Plyr_pt2",4.1,0,0,0,0,0,1);
	}
	else if(PlayerInfo[playerid][pSTD] == 2)
	{
	    SetPlayerHealthEx(playerid, (health-2.0));
		format(strings, sizeof(strings), " %s ������� 2 �������� � ���������� ����.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "GRAVEYARD","mrnF_loop",4.1,0,0,0,0,0,1);
		SetPlayerDrunkLevel(playerid, 5*1000);
	}
	else if(PlayerInfo[playerid][pSTD] == 3)
	{
	    SetPlayerHealthEx(playerid, (health-3.0));
		format(strings, sizeof(strings), " %s ������� 3 �������� � ���������� ��������.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "FOOD","EAT_Vomit_P",4.1,0,0,0,0,5000,1); // Vomit BAH!
		PlaySoundForPlayer(playerid, 32201);//�����
	}
	else if(PlayerInfo[playerid][pSTD] == 4)
	{
	    SetPlayerHealthEx(playerid, (health-4.0));
		format(strings, sizeof(strings), " %s ������� 4 �������� � ���������� ����������.", PlayerName(playerid));//���������� ����
		if(!IsPlayerInAnyVehicle(playerid))
		{
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
			PlaySoundForPlayerInRange(playerid, SOUND_PISSING, 30.0);
			ApplyAnimation(playerid, "PAULNMAC","Piss_in",4.1,1,0,0,0,5000,1); //������
		}
	}
	else if(PlayerInfo[playerid][pSTD] == 5)
	{
	    SetPlayerHealthEx(playerid, (health-5.0));
		format(strings, sizeof(strings), " %s ������� 5 �������� � ���������� ������������ ������������.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PED","HIT_back",0.1,1,0,0,0,10000,1);
		//if(!IsPlayerInAnyVehicle(playerid)) LoopingAnim(playerid, "PED", "HIT_back", 0.1, 1, 0, 0, 0, 0);
	}
	else if(PlayerInfo[playerid][pSTD] == 6)
	{
	    SetPlayerHealthEx(playerid, (health-6.0));
		format(strings, sizeof(strings), " %s ������� 6 �������� � ���������� ���������.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "CRACK","crckdeth2",4.1,1,0,0,0,15000,1); // Dieing of Crack
	}
	else if(PlayerInfo[playerid][pSTD] == 7)
	{
	    SetPlayerHealthEx(playerid, (health-7.0));
		format(strings, sizeof(strings), " %s ������� 7 �������� � ���������� �������.", PlayerName(playerid));
		//if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "SCRATCHING", "scdrdlp", 4.0, 0, 0, 0, 0, 0);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "SWEET","Sweet_injuredloop",4.1,1,0,0,0,15000,1);
	}
	else if(PlayerInfo[playerid][pSTD] == 8)
	{
	    SetPlayerHealthEx(playerid, (health-8.0));
		format(strings, sizeof(strings), " %s ������� 8 �������� � ���������� �����.", PlayerName(playerid));
		SetPlayerDrunkLevel(playerid, 7*1000);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PAULNMAC","PnM_Argue2_A",4.1,0,0,0,0,15000,1);
	}
	else if(PlayerInfo[playerid][pSTD] == 9)
	{
	    SetPlayerHealthEx(playerid, (health-9.0));
		format(strings, sizeof(strings), " %s ������� 9 �������� � ���������� ����.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "CRACK","crckdeth3",4.1,0,1,1,0,15000,1);
		SetPlayerDrunkLevel(playerid, 9*1000);
	}
	else if(PlayerInfo[playerid][pSTD] == 10)
	{
	    SetPlayerHealthEx(playerid, (health-10.0));
		format(strings, sizeof(strings), " %s ������� 10 �������� � ���������� ���������.", PlayerName(playerid));
		//if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "HEIST9", "CAS_G2_GasKO", 4.0, 0, 1, 1, 0, 0);
		//if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "HEIST9", "CAS_G2_GasKO", 4.0, 0, 0, 0, 0, 0);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "SWEET","Sweet_injuredloop",4.1,1,0,0,0,20000,1);//������ �� ������
		PlaySoundForPlayer(playerid, 32201);//���� ���������
		gTextDrawShowBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		SetTimerEx("tHidePlayerBlind", 5000, 0, "d", playerid);
	}
	if(PlayerInfo[playerid][pSTD] >= 1 && PlayerInfo[playerid][pSTD] <= 10) ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
	return 1;
}


//��� ������������ ������
stock OnPlayerIncreaseParameter(playerid)//����������� ������ ������
{
	if(!gTogNeed) return 1;
	//==========================================================================
	//����� ������ ��������� ��������� �� 100 ������������ ��� 108000 ���������� ��� (108000/1000*100)/60=180 ����� ��� 3 ����
	//����� ������ ��������� ��������� �� 50 ������������ ��� 288000 ���������� ��� (288000/1000*50)/60=240 ����� ��� 4 ����
	//������� ������ ��������� ��������� �� 30 ������������ ��� 600000 ������������ ��� (600000/1000*30)/60=300 ����� ��� 5 ����
	//������ ������ ��������� ��������� �� 20 ������������ ��� 1080000 ������������ ��� (1080000/1000*20)/60=360 ����� ��� 6 ����
	//�������� ������ ��������� ��������� �� 15 ������������ ��� 108000 ������������ ��� (1680000/1000*15)/60=420 ����� ��� 7 ����

	/*new operator1 = 100;
	new operator2 = 50;
	new operator3 = 30;
	new operator4 = 20;
	new operator5 = 15;*/

	new ParameterSpeed1 = (3+PlayerInfo[playerid][pHunger])*60 *60/operator1 *1000;//3*60 *60/100 *1000�=�108000;
	new ParameterSpeed2 = (4+PlayerInfo[playerid][pLeisure])*60 *60/operator2 *1000;//288000
	new ParameterSpeed3 = (5+PlayerInfo[playerid][pContact])*60 *60/operator3 *1000;//600000
	new ParameterSpeed4 = (6+PlayerInfo[playerid][pToilet])*60 *60/operator4 *1000;//1080000
	new ParameterSpeed5 = (7+PlayerInfo[playerid][pVigour])*60 *60/operator5 *1000;//1680000

//�����
	if(GetTickCount() >= (TickCount1[playerid] + ParameterSpeed1))//ParameterSpeed1[playerid] ������ ���� ������ 60 ��������
	{ 	//����������� ������ 108 ������	//��������� 100 ��� �� 10800 ������(~180 �����)
		if(PlayerInfo[playerid][pParam1] < operator1)
		{
			PlayerInfo[playerid][pParam1] += 1;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1+PlayerInfo[playerid][pHunger]);
		}
		else gParameter1[playerid] = 1;
		TickCount1[playerid] = GetTickCount();
	}
//�����
	if(GetTickCount() >= (TickCount2[playerid] + ParameterSpeed2))
	{ 										//	+ 178000 //��������� 50 ��� �� 8900 ������ (148 �����)
		if(PlayerInfo[playerid][pParam2] < operator2)
		{
			PlayerInfo[playerid][pParam2] += 1;
			SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);
			//if(PlayerInfo[playerid][pParam2] >= 48) SendClientMessage(playerid, COLOR_MAROON, "�����: ��� ������� � �� ������ � ��������! ��� ���� ������ ���������� � �����!");
			//if(PlayerInfo[playerid][pParam2] >= 48) SendClientMessage(playerid, COLOR_MAROON, "��������: ������� � ������ ������ ������ DJ �����. ������ ������� ���� ����������? ��� ����!");
			if(PlayerInfo[playerid][pParam2] >= 47)
			{
				SendClientMessage(playerid, COLOR_GREY, "�����: ���! �� � ����� � ����. � ����� ����������� �� ��� �� ������ ����� �� �������!");
			 	SendClientMessage(playerid, COLOR_GREY, "���������: ����� ���, ��� ����� �� ������, �������� ���� ��� ���. ���������� (USE: /dance) ��� ���������� ������� �����!");
			 	PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
		}
		else gParameter2[playerid] = 1;
		TickCount2[playerid] = GetTickCount();
	}
//�������
	if(GetTickCount() >= (TickCount3[playerid] + ParameterSpeed3))
	{ 										//	+ 298000 //��������� 30 ��� �� 8940 ������(149 �����)
		if(PlayerInfo[playerid][pParam3] < operator3)
		{
			PlayerInfo[playerid][pParam3] += 1;
			SetPlayerShowScale(playerid, 3, PlayerInfo[playerid][pParam3], operator3);
			if(PlayerInfo[playerid][pParam3] >= 27)	{
				SendClientMessage(playerid, COLOR_GREY, "�����: �� ��������� ����� ����������! ������ � ����� ����� �� ��������. �� ������, � ���� �� ���� �������!");
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
			//if(PlayerInfo[playerid][pParam3] >= 27) SendClientMessage(playerid, COLOR_MAROON, "��������: ��, �� � ����� � ����! �� �� ���� ���� ���� ������� �� ������! ������� ���� ������� � ���������!");
		}
		else gParameter3[playerid] = 1;
		TickCount3[playerid] = GetTickCount();
	}
//������
	if(GetTickCount() >= (TickCount4[playerid] + ParameterSpeed4))
	{ 										//	+ 598000 //��������� 20 ��� �� 11960 ������(199 �����)
		if(PlayerInfo[playerid][pParam4] < operator4)
		{
			PlayerInfo[playerid][pParam4] += 1;
			SetPlayerShowScale(playerid, 4, PlayerInfo[playerid][pParam4], operator4);
			if(PlayerInfo[playerid][pParam4] >= 17) {
				SendClientMessage(playerid, COLOR_GREY, "�����: ��� ������ ���� �������� �����. ��������, ����� ��� �� ��� �� ����� (USE: /piss)!");
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
		}
		else gParameter4[playerid] = 1;
		TickCount4[playerid] = GetTickCount();
	}
//��������
	if(GetTickCount() >= (TickCount5[playerid] + ParameterSpeed5))
	{ 	//����������� ������ 1680 ������	//��������� 15 ��� �� 25200 ������(~420 �����)
		if(PlayerInfo[playerid][pParam5] < operator5 && gParameter5[playerid] == 0)
		{   //���� �������� ���� �����������, � ����� �� ��������� � �����������, �� ��������
			PlayerInfo[playerid][pParam5] += 1;
			SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);
			if(PlayerInfo[playerid][pParam5] >= 12) {
				SendClientMessage(playerid, COLOR_GREY, "�����: ��� ������� � �� ������! ������ �������� �� ������� � ����� (USE: /bedl /bedr)!");
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
		}
		else gParameter5[playerid] = 1;
		TickCount5[playerid] = GetTickCount();
	}
	return 1;
}


