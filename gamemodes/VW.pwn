//https://gta.ag.ru/sa/professions
//https://pawnokit.ru/spec_symbols
//https://pawnokit.ru/text_conv

/*
 *            Virtual World v1.0
 *       (c) Copyright 2017-2018 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 26.01.2017
 * @update    : 24.11.2020
 *
 * This file is provided as is (no warranties).
 *
 */
#define VERSION 				"v8.0.689" //������ ����, �.�. ���������� ����������� ����������� ������ ����
#define DEFAULT_COLOR			-1
#define	GAME_EDITOR				"1.0"   //������ ������������, �.�. ������� �����

/*
/rcon login [������] - ����� � RCON ������
/rcon cmdlist - �������� ������ RCON ������
/rcon exit - ������� ������
/rcon varlist - ���������� ������ ������� ��������
/rcon kick [ID] - ������� ������������ �� ��� ID (������: /rcon kick 3)
/rcon ban [ID] - �������� ������������ �� ��� ID (������: /rcon ban 3)
/rcon banip [IP] - �������� IP (������: /rcon banip 127.0.0.1)
/rcon unbanip [IP] - ��������� IP (������: /rcon unbanip 127.0.0.1)
/rcon reloadbans - ������������� samp.ban, � ������� ���������� ���������� IP
/rcon reloadlog - �������� ��� �������
/rcon exec [��� �����] - ������� ���� .cfg (������: /rcon exec blah.cfg)
/rcon say [�����] - ������� � ����� ��� �� ���� ������ (������: /rcon say Hello)
/rcon players - �������� ���� ������� �� ������� � �� �������, ip � ������
/rcon gravity - �������� ���������� �� ������� - (������: /rcon gravity 0.008)
/rcon weather [ID] - �������� ������ �� ������� (������: /rcon weather 2)
/rcon worldtime [�����] - �������� ����� �� ������� (������: /rcon worldtime 2)
/rcon maxplayers - �������� ����. ���������� ���� �� �������
/rcon timestamp - ���������� ������� ����
/rcon plugins - ���������� ������ ���� ������������� ��������
/rcon filterscripts - ���������� ������ ���� ������������� ��������������
/rcon loadfs [��������] - ��������� ������������ (������: /rcon loadfs [�������� FS])
/rcon unloadfs [��������] - ��������� ������������ (������: /rcon unloadfs [�������� FS])
/rcon reloadfs [��������] - ������������� ������������ (������: /rcon reloadfs [�������� FS])
/rcon password [������] - ���������� ������ �� ������� (������: /rcon password 123456)
/rcon rcon_password [������] - ���������� ����� RCON ������ (������: /rcon rcon_password 123456)
/rcon changemode [��������] - �������� ����� ���� �� ������� �� ��������
/rcon gmx - ����� �� �������� ������ ���� � ������ ���������, �������� ������������ � server.cfg
/rcon hostname [��������] - �������� �������� ������� (������: /rcon hostname my server)
/rcon gamemodetext [��������] - �������� �������� ���� (������: /rcon gamemodetext Samp-Mods)
/rcon mapname [��������] - �������� �������� ����� (������: /rcon mapname San Andreas)
/rcon gamemode[1-15] - ���������� ������� ����-����� (������: /rcon gamemode1 sftdm)
/rcon instagib [bool] - �������� ������� �������� � ����� ���� (������: /rcon instagib 0)
/rcon lanmode [bool] - ���������� LAN (������: /rcon lanmode 1)
/rcon port - �������� ����
/rcon version - ���������� ������ �������
/rcon weburl [���] - ���������� ��� ����� �� ������� (������: /rcon weburl www.samp-mods.com)
*/

//��������� ���������
//������� ��������/���������� �� ������
//�������� �����
//������� ������� � vw_PlayerInfo.inc � vw_player.inc

//1 ������ � ���� = 1 ��� � �����
//60 ����� = 60 ��� || ��� � ���� = ��� � �����
//24 ���� = 24 ��� || c���� � ���� = 24 ����� � �����
//168 ����� = 168 ��� || ������ = 2 ���� 48 ���
//720 ����� = 720 ��� || ����� = 12 �����
//8760 � = 8760 ��� || ��� = 146 ����� = 6 �����


//##############################################################################//
//                                                                              //
//                        ����� �������������� ���������                        //
//                                                                              //
//##############################################################################//
#define LOCAL//��. vw_config
//#define NPCs

//������ ���� ������ ����� ��� include ������� ���������� ������ ���������
//��������������� ��� ����������
//#define samp03DL//��������������� ���� �� ����������� samp03DL_svr_R1_win32

//��������� ��������� ����� �������
#define vw_checking//��������������� ���� �� ����� �������� ������������ ��������
#define vw_weapons//��������������� ���� �� ����� ������
#define vw_objects//��������������� ���� �� ����� �������
////#define vw_races//��������������� ���� �� ����� �����
#define vw_props//��������������� ���� �� ����� �������������
#define vw_sql//��������������� ���� �� ����� ���� ������
#define vw_rega//��������������� ���� �� ����� �����������
#define vw_login//��������������� ���� �� ����� �����������
#define vw_jobs//��������������� ���� �� ����� ������

#define vw_fuel//��������������� ���� �� ����� ������� ���������� �������
#define vw_speedometer//��������������� ���� �� ����� ����������� ����������
#define vw_tuning //��������������� ���� �� ����� ������ �����
#define vw_vehmenu //��������������� ���� �� ����� ������� ���������� ����������� �����
#define vw_changer//��������������� ���� �� ����� ������� ������ ������, ����� � ��������
//#define vw_gps
#define grandlarc
//#defined RRG_is_include
//##############################################################################//
//                                                                              //
//              ����������� ������������� ���������(filterscripts)              //
//                                                                              //
//##############################################################################//


//��� ���� �� ������ ����������, ��� ������ ������� ��� ���������� ���� �������
#include <crashdetect>
#include <a_samp>
#include <sqlitei>//�������� a_sampdb

#include <a_http>
//#include <AntiDeAMX>
//#include <sscanf2>
#include <streamer>
//#include <RouteConnector>
//#include <FCNPC>
//#include <geolocation>

//#include <nex-ac>
//#include <rakcheat>
//#include <sampvoice>
//#include <fix_doors>
//------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////
// Fixes
//////////////////////////////////////////////////////////////

// No comment..
#if !defined IsValidVehicle
	native IsValidVehicle(vehicleid);
#endif

#if !defined GetGravity
	native Float:GetGravity();
#endif

#if !defined GetWeather
	#define GetWeather() GetConsoleVarAsInt("weather")
#endif

//##############################################################################//
//                                                                              //
//                                 �ר�����                                     //
//                                                                              //
//##############################################################################//
//�������� ����� ��� OnPlayerUpdate(playerid)
new oneseconds[MAX_PLAYERS];//������� ��� 1-����������� ���������
//new twoseconds[MAX_PLAYERS];//������� ��� 2-����������� �������
new oneminuts[MAX_PLAYERS];
new fiveminuts[MAX_PLAYERS];
new fifteenminuts[MAX_PLAYERS];
new onehour[MAX_PLAYERS];

#include "../include/vw_color.inc"//PlayerColors, VehicleColor
//------------------------------------------------------------------------------

#include "../include/vw_defines.inc"//���������

//---------------------------------------------------------

#include "../include/vw_specialkeys.inc"//������� �������� ������
#include "../include/vw_virtualkey.inc"

#include "../include/vw_menu.inc"
#include "../include/vw_config.inc"//��������� �������
#include "../include/vw_plids.inc"//����������� ������ /vw_Itter"//�-�� ��� ����������� �������� � ������� ��������


//#include "../include/vw_sampvoice.inc"


//����������� �������
#include "../include/vw_arrays.inc"//����� ������� VehicleArray, �.�. ���� � ��� �� ������ ����� ����������� �� ���� ��������
#include "../include/vw_player.inc"//���������� ������ � �� ������������� �� ������� ������� PlayerInfo
//---------------------

#include "../include/vw_log.inc"//�-�� �����������

//��������� ������������ dialog
#include "../include/vw_dialog.inc"
#include "../include/vw_sound.inc"//vw_dialog.inc"

#include "../include/other/vw_marriage.inc"

#if defined vw_checking //#endif ���� �-�� ���������� ��������� �� ������ include
	#include "../include/vw_checking.inc"//vw_player vw_arrays
#endif

//�-�� �� ������������ ������� ������� PlayerInfo, VehInfo
#include "../include/vw_functions.inc"//����� �-��
#include "../include/vw_get.inc"//�-�� ���������


#include "../include/vw_audio.inc"//�-�� ������������ ������, ������
#include "../include/vw_check.inc"//vw_respray.inc �-�� �������� Is //vw_needs //�-�� �������� �� ������������ PlayerInfo

#include "../include/other/vw_walking.inc"

//------------------------------------------------------------------------------
//������������ �������, ���������� ����������������
#include "../include/vw_PlayerInfo.inc"//������ �� ������� ������, ��� �������� ������ � ����������� �����������

#include "../include/vw_VehInfo.inc"//������ �� ���� ����������� ������, ��� �������� ����� � ����������� �����������
#include "../include/vw_ParkingInfo.inc"

#include "../include/prop/vw_HouseInfo.inc"//����, ������ ������, ���������� � ��������
#include "../include/prop/vw_BizInfo.inc"//�������, ������ ������, ���������� � ��������
#include "../include/prop/vw_SBizInfo.inc"//��������, ������ ������, ���������� � ��������

#include "../include/family/vw_FamilyInfo.inc"//�����, ������ ������, ���������� � ��������
#include "../include/family/vw_ClanInfo.inc"//�������, ������ ������, ���������� � ��������
#include "../include/family/vw_TurfInfo.inc"//����-����, ������ ������, ���������� � ��������
//------------------------------------------------------------------------------

//#if defined grandlarc//#endif
#include "../include/grandlarc/gl_common.inc"
//#include "../include/grandlarc/gl_spawns.inc"
#include "../include/grandlarc/gl_grandlarc.inc"//��������� ����: ����� ������, ����� �����, �������� ��������� ����� � �.�.
//#endif

#include "../include/features/vw_ladder.inc"//������ ������ ���������

//��������� ������������ textdraw
#include "../include/vw_textdraw.inc"//vw_ladder.inc"

#include "../include/objects/vw_fbi.inc"

#include "../include/car/vw_vehicle.inc"
#include "../include/car/vw_trailer.inc"
#include "../include/vw_text3D.inc"
#include "../include/vw_pickup.inc"
#include "../include/vw_skin.inc"//������ SkinArray ���������� vw_PlayerInfo


#include "../include/vw_PlayerInfoMenu.inc"

#include "../include/other/vw_online.inc"
#include "../include/other/vw_anekdot.inc"

#include "../include/features/vw_vote.inc"



#include "../include/textdraw/vw_begunok.inc"//������ ������ ���������

//#include "../include/car/vw_speedometer"//���������� vw_textdraw vw_radar
#include "../include/car/vw_advisor.inc"//���������� vw_textdraw

#include "../include/vw_mapicon.inc"//���������� vw_textdraw vw_radar


#include "../include/vw_message.inc"//���������� vw_plids vw_player vw_PlayerInfo vw_checkpoint vw_textdraw
#include "../include/vw_weather.inc"

//#include "../include/other/vw_looking"
//SendSystemMessage
#include "../include/features/vw_adminchat.inc"//vw_textdraw

#include "../include/other/vw_irc.inc"//������ ������ ���������
#include "../include/other/vw_adventure.inc"//������ ������ ���������
#include "../include/other/vw_ad.inc"//������ ������ ���������


#include "../include/anti/vw_antiswear.inc"//������ ������ ���������
#include "../include/anti/vw_anticheat.inc"//������ ������ ���������
#include "../include/anim/aview.inc"


//������������� �-��
#include "../include/vw_PlayerEx.inc"//���������� vw_PlayerInfo
#include "../include/vw_VehEx.inc"//���������� VehInfo


#include "../include/items/vw_phone.inc"
#include "../include/service/vw_respray.inc"

#include "../include/features/vw_migalka.inc"
#include "../include/vw_checkpoint.inc"//vw_textdraw vw_advisor

#include "../include/help/vw_help.inc"//vw_donat
#include "../include/other/vw_marker.inc"
//------------------------------------------------------------------------------
//��������� �� ��������

#include "../include/help/vw_donat.inc"
#include "../include/help/vw_aboutserver.inc"


#include "../include/help/vw_command.inc"
//------------------------------------------------------------------------------
//��������� ������������ ��������
#include "../include/features/vw_follow.inc"


#include "../include/features/vw_needs.inc"
#include "../include/features/vw_drunk.inc"
//------------------------------------------------------------------------------
//��������� ������������ ������
#if defined vw_weapons//#endif
	#include "../include/weapon/vw_weapon.inc"
	#include "../include/weapon/vw_backweapon.inc"
	#include "../include/weapon/vw_dropweapon.inc"
	#include "../include/weapon/vw_bullet.inc"
	#include "../include/weapon/vw_shoot.inc"
#endif
#include "../include/weapon/vw_gunchange.inc"//�������� ������ ������
//------------------------------------------------------------------------------
#include "../include/objects/vw_radar.inc"

#include "../include/objects/vw_object.inc"//vw_radar

#if defined vw_objects//#endif
//��� ������� ��� ������� ����� ������� �������

	#include "../include/objects/vw_hotel.inc"
	#include "../include/objects/vw_LCN.inc"

	//#include "../include/objects/vw_CNN.inc"//�� ������ ����-��� ��������
	#include "../include/objects/vw_attach.inc"
	#include "../include/objects/vw_accessories.inc"//vw_attach.inc
	#include "../include/objects/vw_elevator.inc"//vw_config.inc vw_sound.inc vw_dialog
	#include "../include/objects/vw_ATMS.inc"//���������
	#include "../include/objects/vw_bench.inc"//��������
	#include "../include/objects/vw_cargoship.inc"//��� ���������
	#include "../include/objects/vw_gate.inc"//vw_family
	//#include "../include/objects/vw_poster"
	#include "../include/objects/vw_spike"//������ spike �� ��������� ��������� �����  � DamageStatus �� ������������ ����������� �����
	#include "../include/objects/vw_ferriswheel"
	//#include "../include/objects/vw_island"

	#include "../include/objects/vw_roadblock.inc"//�������� �����
#endif


#include "../include/objects/vw_DoJ.inc"
#include <a_actor_ex>
#include "../include/actor/vw_actor.inc"
#include "../include/actor/OP_actor.inc"
	
#include "../include/help/vw_gpsitem.inc"//vw_checkpoint

#include "../include/vw_wanted.inc"
#include "../include/features/vw_jail.inc"

#include "../include/anim/vw_animation.inc"//vw_wanted.inc

#include "../include/cam/camstate.inc"
//#include "../include/cam/recon.inc"
#include "../include/cam/vw_spectate.inc"//vw_wanted.inc
#include "../include/cam/cameditor.inc"

#include "../include/help/vw_tutorial.inc"//vw_spectate.inc
#include "../include/help/vw_rules.inc"

#if defined vw_fuel
	#include "../include/car/vw_fuel.inc"
#endif

#if defined vw_tuning //���� �-�� ���������� ��������� �� ������ include
	#include "../include/service/vw_tuning.inc" //���������� vw_object vw_menu
#endif

	
#if defined vw_changer
	#include "../include/vw_changer.inc"//�������� ������ ������, ����� � �������� //���������� vw_skin
#endif
//------------------------------------------------------------------------------
//��������� ������������ race
#if defined vw_races//#endif
	#include "../include/race/vw_race.inc"//���������� vw_textdraw
	#include "../include/race/vw_bloodbowl.inc"
	#include "../include/race/vw_derbiLS.inc"
	#include "../include/race/vw_kickstart.inc"
#endif
//#include "../include/race/RandomRaceGenerator.inc>
//------------------------------------------------------------------------------
//��������� ������������ prop
#include "../include/family/vw_family.inc"
#include "../include/family/vw_gangs.inc"
#include "../include/family/vw_clans.inc"

//#if defined vw_props//#endif
	#include "../include/prop/vw_house.inc"//vw_text3D
	#include "../include/prop/vw_exchange.inc"//�����
	#include "../include/prop/vw_biz.inc"//vw_text3D vw_family vw_drunk vw_exchange
	#include "../include/prop/vw_sbiz.inc"//vw_text3D vw_family w_parking
//#endif

#include "../include/prop/vw_prop.inc"//vw_playermenu vw_family
#include "../include/vw_interior.inc"//������ InteriorInfo ���������� vw_PlayerInfo

#include "../include/other/vw_clear.inc"

//#if defined vw_rega//#endif
	#include "../include/rega/vw_login.inc"
	#include "../include/rega/vw_rega.inc"//vw_skin.inc
//#endif
//------------------------------------------------------------------------------
//��������� ������������ job
#include "../include/job/vw_jobs.inc"//vw_roadblock
#if defined vw_jobs//#endif
	#include "../include/vw_spawn.inc"
	#include "../include/other/vw_payday.inc"//vw_PlayerInfo vw_prop
	#include "../include/job/vw_skill.inc"
	//#include "../include/features/vw_gps.inc"
	#include "../include/job/vw_trucker.inc"//vw_race vw_gps
	#include "../include/job/vw_armsdealer.inc"
	//#include "../include/job/vw_autobuyer"
	#include "../include/job/vw_bookmaker.inc"
	#include "../include/job/vw_box.inc"
	#include "../include/job/vw_bus.inc"
	#include "../include/job/vw_cardealer.inc"
	#include "../include/job/vw_carjacker.inc"//vw_vehmenu
	//#include "../include/job/vw_cooker"
	#include "../include/job/vw_drugdealer.inc"
	#include "../include/job/vw_farmer.inc"
	#include "../include/job/vw_fireman.inc"
	#include "../include/job/vw_fisher.inc"
	#include "../include/job/vw_hitman.inc"
	#include "../include/job/vw_inkas.inc"
	//#include "../include/job/vw_lawyer"
	#include "../include/job/vw_loader.inc"//vw_cargoship
	#include "../include/job/vw_mechanic.inc"
	#include "../include/job/vw_medic.inc"//vw_drunk
	#include "../include/job/vw_miner.inc"
	#include "../include/job/vw_mushroomer.inc"
	#include "../include/job/vw_papers.inc"
	#include "../include/job/vw_police.inc"
	#include "../include/job/vw_roadworker.inc"
	#include "../include/job/vw_school.inc"
	#include "../include/job/vw_taxi.inc"
	#include "../include/job/vw_trashman.inc"
	#include "../include/job/vw_woodsman.inc"
#endif

#include "../include/service/vw_service.inc"//������� �������� ����� �� �����

#include "../include/help/vw_help.inc"//vw_donat
#include "../include/vw_playermenu.inc"//vw_playemenu"
//#include "../include/vw_playerselect.inc"
#include "../include/items/vw_items.inc"

#if defined vw_vehmenu
	#include "../include/car/vw_parking.inc"
	#include "../include/car/vw_firstlook.inc"//���������� vw_object, vw_color
	#include "../include/car/vw_vehmenu.inc"//vw_firstlook vw_parking
	#include "../include/car/vw_carinfo.inc"
#endif


#include "../include/vw_timers.inc"
#include "../include/other/vw_remote"//vw_timers
#include "../include/anti/vw_antidm.inc"

#include "../include/other/vw_level.inc"

#if defined vw_sql//#endif
	//#include "../include/sql/vw_mysql"
	#include "../include/sql/vw_sql.inc"
	//#include "../include/sql/vw_list"//������ ������ � ����������
#endif

#include "../include/help/vw_info.inc"//ServerInfo TabInfo FinanceInfo

#include "../include/vw_AdminMenu.inc"
#include "../include/vw_clock.inc"
#include "../include/vw_admin.inc"//���������� ��� ����������� ����������
#include "../include/vw_prints.inc"

#pragma dynamic 16384//150000/115000//16384 �������� ������������ ������
//##############################################################################//
//                                                                              //
//                           ������ �������� �������                            //
//                                                                              //
//##############################################################################//
new load_time;

//��������: ������� ����������� ������ ��� ��� � �������� �� ���������� �������. ��� �������� ���� �� �������������
main()
{
	print("\n---------------------------------------");
	print("Running Virtual World v1.0 - by by Hidden -=DANGER=-\n");
	print("---------------------------------------\n");
}

public OnGameModeInit() //����������� ����������� 	SendRconCommand("reloadfs GE");
//public OnFilterScriptInit()
{
	load_time = GetTickCount();
	
#if defined samp03DL//samp03DL_svr_R1_win32
	AddSimpleModel(-1, 19379, -2004, "wallzzz.dff", "ESC15.txd");//samp03DL_svr_R1_win32
	AddSimpleModel(-1, 19379, -2005, "wallzzz.dff", "weapons.txd");//samp03DL_svr_R1_win32
#else//samp037svr_win32

	//sampvoice_OnGameModeInit();
#endif

#if defined vw_objects//#endif
//��������� ������������ �������
//##############################################################################//
//#                                                                            #//
//#                     �������� ����������� ����������                        #//
//#                                                                            #//
//##############################################################################//
//��������� 25 1000 500 500 - ������� �������� � ���������� ���������
//��������� ��������, ������� �������� �� ����� ���������
	Streamer_TickRate(25);
//������� ����� �� ������������ ����� ������-���� ����������� ��������� ������� � ����������� � ����������� �� �������������� �������� �������.
//���� �������� ����������� ������� ��������, ��������� ������� �����; ���� �������� ���������� ���������� ������� �������, ��������� ������� �����. ��� �� ��������� ���������� 50.
    //Streamer_MaxItems(type, items) - ������������ ����� ������������ ��������. �� ��������� - �� �����������.
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 1000, -1);// - ����� ������������ ��������, ������� �������� ������. �������� �������� ������������ ���������� SA-MP'�.
//���������� ������������ ���������� ���������, ������� ����� ���� ����� ��� ����������� ������ � ����� �����, ��� ������������� ����.
//�������� �� ���������: 500 ��������, 4096 ������� � 1024 ���������� ��������� �����.
	Streamer_CellDistance(500);//��� ������� ������������ ��� ����������� ������������� ��������� �������� � ������ ��� ����� ���������������� ����������. �������� �� ��������� - 600.0.
//���� ��������� ���������� �������� (���, � ������ ��������, ������ ��������) ��������� ���������� �� ������, ��� ����� �������� �� ����� ����� �� �����.
//��������, ���� ��� ���������� ���������� ������ ����� ����������� �������� 100,0, ��� ����� ����� ������ � ��� ������, ���� ����� ��������� � ��� �� ������,
//��� � ������ �����, ��� � �������� ������ (��� �������, ��� ���������� �� ��������� ��� ������ 600,0 �� ���� ��������).
//������, ���� ��� ���������� ���������� ������ ����� ����������� �������� 1000.0, ��� ����� ����� ���������� �� ����, ��� ��������� �����.
	Streamer_CellSize(500);//��� ������� ������������ ��� ����������� ������� ������ ������ � �����. �� ��������� 300.0.

//�������� ��������, ��� Streamer_CellDistance � Streamer_CellSize ������������ ����� ������ ��� ��� ����������, ������� ����������� �� ������ ��� �������������.
//�������� �� ���������, ����� ��������� ������������, ������� � ����������� �������, ������������� ������ �������� ���� �������� � �����, ���� ������ ������������� �� ���������.
//�������� ����� ���� ������������� ������, ��������� y_groups (����� YSI ���������� ).

	new types[STREAMER_MAX_TYPES] =
	{
		STREAMER_TYPE_OBJECT,        //(STREAMER_TYPE_OBJECT = 0) - ��������
		STREAMER_TYPE_PICKUP,         //(STREAMER_TYPE_PICKUP = 1)
		STREAMER_TYPE_3D_TEXT_LABEL, //(STREAMER_TYPE_3D_TEXT_LABEL = 5) - ������
		STREAMER_TYPE_ACTOR,         //(STREAMER_TYPE_ACTOR = 7) - ����� ���������

		STREAMER_TYPE_CP,            //(STREAMER_TYPE_CP = 2) - ���� ����� ����������� �������
		STREAMER_TYPE_RACE_CP,       //(STREAMER_TYPE_RACE_CP = 3) - ���� ��� ����� ����������� ������
		STREAMER_TYPE_MAP_ICON,      //(STREAMER_TYPE_MAP_ICON ���������� ��� 4) - ���� ��� ����� ����������� ����� ������
		STREAMER_TYPE_AREA,          //(STREAMER_TYPE_AREA = 6) - �������
	};
	Streamer_SetTypePriority(types, sizeof types);
	//==========================================================================
	print(" ");
	print("=============================================");
	print("  ������ �������� ��������");
	print(" ");
	new mapping_time = GetTickCount();
//������
	new tmpobjid;
	new object_world, object_int;
/*
	object_world = -1, object_int = -1;
	#include "../include/mapping/vw_carriage.inc"//�����
	
	object_world = -1, object_int = -1;
	#include "../include/mapping/PreSkin.inc"

	object_world = -1, object_int = -1;
	#include "../include/mapping/MRP_Reg.inc"
*/
	new map_world = 0, map_int = 0;
	#include "../include/mapping/vw_station.inc"//����� ������ ��������

// ������� �����������
	map_world = ACCESSOR_WORLD;//20;
	map_int = 8;//1
	#include "../include/mapping/TRM_accessories.inc"

	object_world = HOTEL_WORLD; object_int = HOTEL_INT;
	#include "../include/mapping/vw_reception.inc"
	object_world = -1; object_int = HOTEL_INT;
	#include "../include/mapping/vw_lux.inc"
	object_world = -1; object_int = HOTEL_INT;
	#include "../include/mapping/vw_econom.inc"

	object_world = 248, object_int = -1;
	#include "../include/mapping/DRP_IntHotel.inc"

	//#include "../include/mapping/vw_rifa.inc"//����� ������������ ��� ����� ����� ��� ���

	object_world = MAX_HOUSE+MAX_BIZ+TEAM_GROVE, object_int = TEAM_GROVE;
	#include "../include/mapping/ERP_Grove.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_BALLAS, object_int =TEAM_BALLAS;
	#include "../include/mapping/ERP_Ballas.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_AZTEC, object_int = TEAM_AZTEC;
	#include "../include/mapping/ERP_Aztecas.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_VAGOS, object_int = TEAM_VAGOS;
	#include "../include/mapping/ERP_Vagos.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_RIFA, object_int = TEAM_RIFA;
	#include "../include/mapping/ERP_Rifa.inc"

	object_world = MAX_HOUSE+MAX_BIZ+TEAM_NANG, object_int = TEAM_NANG;
	#include "../include/mapping/vw_grove.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_TRIAD, object_int = TEAM_TRIAD;
	#include "../include/mapping/vw_ballas.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_BIKER, object_int = TEAM_BIKER;
	#include "../include/mapping/vw_aztec.inc"
	object_world = MAX_HOUSE+MAX_BIZ+TEAM_MAFIA, object_int = TEAM_MAFIA;
	#include "../include/mapping/vw_vagos.inc"

	object_world = POLICE_LS_WORLD, object_int = DoT;
	#include "../include/mapping/vw_LSPD.inc"
	object_world = POLICE_SF_WORLD, object_int = DoT;
	#include "../include/mapping/vw_SFPD.inc"

	object_world = 0, object_int = 0;
	#include "../include/mapping/fbi_ex.inc"
	object_world = FBI_SF_PARK, object_int = 0;
	#include "../include/mapping/fbi_park.inc"
	object_world = FBI_SF_WORLD0, object_int = 0;
	#include "../include/mapping/fbi_0.inc"
	object_world = FBI_SF_WORLD1, object_int = 0;
	#include "../include/mapping/fbi_1.inc"
	object_world = FBI_SF_WORLD2, object_int = 0;
	#include "../include/mapping/fbi_2.inc"

	object_world = MAX_HOUSE+MAX_BIZ+DoD, object_int = -1;
	#include "../include/mapping/vw_barracks.inc"//������ �� ����
	object_world = MAX_HOUSE+MAX_BIZ+DoD, object_int = DoD;
	#include "../include/mapping/DRP_Alcatraz.inc"

	object_world = 0, object_int = 0;
	#include "../include/mapping/MRP_Hospital_Ex.inc"
	object_world = 0, object_int = 0;
	#include "../include/mapping/DRP_Hospital_Ex.inc"
	//object_world = 12-14, object_int = DoH;
	#include "../include/mapping/vw_1_hospital.inc"
	#include "../include/mapping/vw_2_hospital.inc"


	object_world = MCSA_LS_WORLD1, object_int = DoH;
	#include "../include/mapping/DRP_1_Hospital.inc"
	object_world = MCSA_LS_WORLD2, object_int = DoH;
	#include "../include/mapping/DRP_2_Hospital.inc"
	object_world = MCSA_LS_WORLD3, object_int = DoH;
	#include "../include/mapping/DRP_3_Hospital.inc"


	object_world = MAX_HOUSE+MAX_BIZ+LCN, object_int = LCN;
	#include "../include/mapping/TRM_int_lcn.inc"
	#include "../include/mapping/TRM_ext_lcn.inc"

	object_world = MAX_HOUSE+MAX_BIZ+Yakuza, object_int = Yakuza;
	#include "../include/mapping/SRP_Yakuza.inc"

	object_world = DOJ_LS_WORLD1; object_int = DoJ;
	#include "../include/mapping/vw_govhall.inc"
	object_world = DOJ_LS_WORLD2; object_int = 0;
	#include "../include/mapping/vw_cityhall_2.inc"
	object_world = DOJ_LS_WORLD3; object_int = 0;
	#include "../include/mapping/vw_mayoroffice.inc"

	//object_world = SAN, object_int = SAN;//DoJ+2
	//#include "../include/mapping/CNNStudio.inc"//5 ������� ��������
	object_world = MAX_HOUSE+MAX_BIZ+SAN, object_int = 0;//SAN
	#include "../include/mapping/NewsAgency.inc"

	object_world = 0, object_int = 0;
	#include "../include/mapping/MRP_News_Ex.inc"
	object_world = MAX_HOUSE+MAX_BIZ+41, object_int = SAN;
	#include "../include/mapping/MRP_Int_News.inc"

	object_world = MAX_HOUSE+MAX_BIZ+DoE, object_int = DoE;//3
	#include "../include/mapping/aSchool_Int.inc"
	object_world = 0, object_int = 0;
	//#include "../include/mapping/ARP_AutoS.inc"
	#include "../include/mapping/Ext_School.inc"
	#include "../include/mapping/aSchool_Ext_Old"

	object_world = 0, object_int = 0;
	#include "../include/mapping/vw_roadworker_base.inc"

	object_world = MAX_HOUSE+MAX_BIZ+44, object_int = 4;//14
	#include "../include/mapping/PP_Airport.inc"


//------------------------------------------------------------------------------
//��������� ����� ��������
	object_world = BANK_WORLD, object_int = BANK_WORLD;
	#include "../include/mapping/vw_bank.inc"


	object_world = MAX_HOUSE+82, object_int = 1;
	#include "../include/mapping/DRP_247.inc"

	object_world = MAX_HOUSE+83, object_int = 2;
	//object_world = -1, object_int = -1;
	#include "../include/mapping/DRP_Club.inc" //Club Final Night"

	object_world = MAX_HOUSE+84, object_int = 3;
	#include "../include/mapping/DRP_TKinta.inc"

	object_world = MAX_HOUSE+85, object_int = 4;
	#include "../include/mapping/DRP_Restoraunt.inc"
	
	object_world = MAX_HOUSE+86, object_int = 5;
	#include "../include/mapping/DRP_HRepair.inc"

	object_world = MAX_HOUSE+87, object_int = 6;
	#include "../include/mapping/DRP_Bar.inc" //Porchlight
	
	object_world = MAX_HOUSE+88, object_int = 7;
	#include "../include/mapping/Drugstore.inc"//������

	object_world = -1, object_int = 0;
	#include "../include/mapping/CoffeeHouse.inc"

	object_world = MAX_HOUSE+MAX_BIZ, object_int = 0;
	#include "../include/mapping/DRP_Cards.inc"


	object_world = 0, object_int = 0;
	#include "../include/mapping/DRP_Market.inc"
	//object_world = 5, object_int = 0;
	//#include "../include/mapping/DRP_Mechanic.inc"

	object_world = 0, object_int = 0;
	#include "../include/mapping/DRP_AutoRinok.inc"

	object_world = 0, object_int = 0;
	#include "../include/mapping/bar.inc"//������� ������, ������ ����, � ������� �� �������

	object_world = 0, object_int = 0;
	#include "../include/mapping/Autosalon.inc"//����� �����, ������� ����� �����������, ��������� �������

//for(new i = MAX_HOUSE+MAX_BIZ+MAX_INT; i <= MAX_HOUSE+MAX_BIZ+MAX_INT+20; i ++)//99+92+66�=�257
	object_world = -1, object_int = 0;
	#include "../include/mapping/DRP_Office_Int.inc"
	object_world = 0, object_int = 0;
	#include "../include/mapping/DRP_Ext_Office.inc"

	object_world = PORT_WORLD, object_int = 1;
	#include "../include/mapping/vw_port_int.inc"
	object_world = 0, object_int = 0;
	#include "../include/mapping/vw_ext_port.inc"

	print(" ");
	new strtmp[70+2+6];
	format(strtmp, sizeof(strtmp), "  ����� �������� ��������: ���� ��������� - %d, ��������� - %d (ms)", 69, (GetTickCount()-mapping_time));
	print(strtmp);
	print("=============================================");
	print(" ");
#endif
//------------------------------------------------------------------------------
#if defined grandlarc//#endif
	grandlarc_OnGameModeInit();//0/19
#endif

	//AntiDeAMX();

#if defined vw_checking //#endif
	checking_OnGameModeInit();
#endif

	config_OnGameModeInit();//1/19. [�������� ��������] ���������� ���� � ��������� ���������

	//player_OnFilterScriptInit();//1
	arrays_SetVirtualPrice();//�-�� ��������� ���� ���� ������� ����� � ����������� �� �� �����������������

	vehicle_OnGameModeInit();//2/19. [�������� �������� ����] //����� ������� �-��
	plids_OnGameModeInit();//������������� ������� -1. ������ ������ ���� ����� �������� �����
//-----------------------------------------------------------------------------
	cameditor_OnGameModeInit();

	//recon_OnGameModeInit();
	aview_OnGameModeInit();//Animation Browser v1.0 by SoNik"

	/*if(GetPVarInt(playerid, "RegActor"))
	{
		DestroyDynamicActor( GetPVarInt(playerid, "RegActor") );
		DeletePVar(playerid, "RegActor");
	}*/
	//new train_act = CreateDynamicActor(26, 2989.1980,1071.5,103.4825,98.0, true, 100.0, 0);//worldid);
    //ApplyDynamicActorAnimation(train_act, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);
	//SetPVarInt(playerid, "RegActor", train_act);


#if defined vw_changer
	changer_OnGameModeInit();
	gunchange_OnGameModeInit();
#endif

#if defined vw_vehmenu
	firstlook_OnFilterScriptInit();////firstlook_OnGameModeInit();
#endif

#if defined vw_fuel
	fuel_OnGameModeInit();
#endif

#if defined vw_objects//#endif
	bench_OnGameModeInit();
	attach_OnGameModeInit();
	//bank_OnGameModeInit();

	DoJ_OnGameModeInit();
	LCN_OnGameModeInit();
	access_OnGameModeInit();
	//poster_OnGameModeInit();

	elevator_OnGameModeInit();
	cargoship_OnGameModeInit();
	ferriswheel_OnGameModeInit();
	//island_OnGameModeInit();
#endif


#if defined vw_weapons//#endif
	backweapon_OnGameModeInit();
	shoot_OnGameModeInit();
	bullet_OnGameModeInit();
#endif

	migalka_OnGameModeInit();
	timers_OnGameModeInit();
 	clock_OnGameModeInit();
 	
//==============================================================================
#if defined vw_speedometer
	advisor_OnGameModeInit();//speedometer_OnGameModeInit();
#endif

#if defined vw_races//#endif
	race_OnGameModeInit();
#endif

#if defined vw_jobs//#endif
	police_OnGameModeInit();
 	medic_OnGameModeInit();
	miner_OnGameModeInit();
	trashman_OnGameModeInit();
	trucker_OnGameModeInit();//��� �������������� STEP0
	farmer_OnGameModeInit();
	fireman_OnGameModeInit();
	mushroomer_OnGameModeInit();
	school_OnGameModeInit();
	loader_OnGameModeInit();
	roadworker_OnGameModeInit();
#endif

#if defined vw_props//#endif
	prop_OnGameModeInit();
	house_OnGameModeInit();//3/19. [�������� �����]
	biz_OnGameModeInit();//4/19. [�������� ��������]
	sbiz_OnGameModeInit();//5/19. [�������� ��������]
#endif

	anekdot_OnGameModeInit();//6/19. [�������� ���������]
	menu_OnGameModeInit();//7/19. [�������� ����]	//LoadMenus();
	OP_actor_OnGameModeInit();//8/19. [�������� OP ������]
	
#if defined vw_objects//#endif
	object_OnGameModeInit();//9/19. [�������� ��������]//��� �������� ������ ���� ����� �����
	radar_OnGameModeInit();//10/19. [�������� �������]
	atm_OnGameModeInit();//11/19. [�������� ����������]
	gate_OnGameModeInit();//12/19. [�������� MoveObject]
	hotel_OnGameModeInit();//13/19. [�������� ������� �����]
	fbi_OnGameModeInit();//14/19. [�������� FBI_object_moved]
#endif

#if defined vw_jobs//#endif
	family_OnGameModeInit();//15/19. [�������� ���� � �������]
	gangs_OnGameModeInit();//16/19. [�������� ���]
	clans_OnGameModeInit();//17/19. [�������� ������]
#endif

//����� ������ 3������� � ���������� � �����, ����� ������ ������� ������� �� �����������
	actor_OnGameModeInit();//18/19. [�������� ������] ��������� ����� �������
	pickup_OnGameModeInit();//19/19. [�������� �������[3D�������]]//��� ������� ������ ���� ����� �����
	interior_OnGameModeInit();//20/19. [�������� ������� ����������]
	//text3D_OnGameModeInit();
	textdraw_OnGameModeInit();//21/19. [�������� TextDraw]

	//--------------------------------------------------------------------------
	prints_OnFilterScriptInit();
	printf("22/22. [�������� ���������]: ��������� - %d (ms)", (GetTickCount()-load_time));
	print("  Game Editor v"#GAME_EDITOR" By: Danger_Hidden");
	print("_____________________________________________");
	print(" ");
	return 1;
}


public OnGameModeExit()
//public OnFilterScriptExit()
{//��� ��������� ������� ���� �������� ������ ���� ����������, �� �� ��������� ������� ��������� �����

#if defined vw_props//#endif
	prop_OnGameModeExit();
#endif

	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		DeletePVar(i, "Action");
		DeletePVar(i, "InputValue");
		DeletePVar(i, "InputCounter");
	}

	textdraw_OnGameModeExit();
 	menu_OnGameModeExit();//UnLoadMenus();
	gunchange_OnGameModeExit();
	cameditor_OnGameModeExit();
	//recon_OnGameModeExit();
	aview_OnGameModeExit();
	OP_actor_OnGameModeExit();

#if defined vw_changer
	changer_OnGameModeExit();
#endif

#if defined vw_vehmenu
	firstlook_OnFilterScriptExit();
#endif

#if defined vw_objects//#endif
	elevator_OnGameModeExit();
	ferriswheel_OnGameModeExit();
	//poster_OnGameModeExit();
	//island_OnGameModeExit();
	attach_OnGameModeExit();
#endif

#if defined vw_weapons//#endif
	dropweapon_OnGameModeExit();
	backweapon_OnGameModeExit();
#endif

#if defined vw_speedometer
	//speedometer_OnGameModeExit();
	advisor_OnGameModeExit();
#endif

#if defined vw_sql//#endif
	db_OnGameModeExit();
#endif

	//timers_OnGameModeExit();
	//UnloadContent();//�������� ��, � ����, � �������
	print("OnFilterScriptExit: Game Editor v"#GAME_EDITOR);
	return 1;
}

//##############################################################################//
//                                                                              //
//                            �������������� �������                            //
//                             ����������� �������                              //
//                                                                              //
//##############################################################################//

public OnPlayerConnect(playerid)
{
	//SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	if(IsPlayerNPC(playerid)) { return 1; }
	//sampvoice_OnPlayerConnect(playerid);
	//TogglePlayerClock(playerid, 0);
	TogglePlayerClock(playerid, 1);//�������� ����� ����������
	new tickcounter = GetTickCount();
	//TogglePlayerSpectating(playerid, 1);//�� ����������������. ����� �� ��������� public OnPlayerRequestClass
	plids_OnPlayerConnect(playerid);

	//for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " "); //������� ����
	//--------------------------------------------------------------------------
	player_OnPlayerConnect(playerid);//��������� OnPlayerInit
	PlayerInfo_OnPlayerConnect(playerid);

//����� ��������� ������������� 
	prop_OnPlayerConnect(playerid);
	
	vehicle_OnPlayerConnect(playerid);
	mapicon_OnPlayerConnect(playerid);
	//timers_OnPlayerConnect(playerid);

	dialog_OnPlayerConnect(playerid);
	pickup_OnPlayerConnect(playerid);
	textdraw_OnPlayerConnect(playerid);
	needs_OnPlayerConnect(playerid);
	marker_OnPlayerConnect(playerid);
	cameditor_OnPlayerConnect(playerid);
	//recon_OnPlayerConnect(playerid);
	spectate_OnPlayerConnect(playerid);
	phone_OnPlayerConnect(playerid);
	
	
#if defined vw_changer
	changer_OnPlayerConnect(playerid);
#endif

#if defined vw_objects//#endif
	fbi_OnPlayerConnect(playerid);
	LCN_OnPlayerConnect(playerid);
	object_OnPlayerConnect(playerid);
	gate_OnPlayerConnect(playerid);
	ferriswheel_OnPlayerConnect(playerid);
	//poster_OnPlayerConnect(playerid);
	//island_OnPlayerConnect(playerid);
	access_OnPlayerConnect(playerid);
	cargoship_OnPlayerConnect(playerid);
	hotel_OnPlayerConnect(playerid);
	bench_OnPlayerConnect(playerid);
#endif

#if defined vw_weapons//#endif
	dropweapon_OnPlayerConnect(playerid);
#endif
	
#if defined vw_speedometer
	//speedometer_OnPlayerConnect(playerid);
	advisor_OnPlayerConnect(playerid);
	radar_OnPlayerConnect(playerid);
#endif

#if defined vw_vehmenu
	firstlook_OnPlayerConnect(playerid);
#endif

#if defined vw_fuel
	fuel_OnPlayerConnect(playerid);
#endif

#if defined vw_races//#endif
	derbiLS_OnPlayerConnect(playerid);
#endif
	
#if defined vw_jobs//#endif
	family_OnPlayerConnect(playerid);
	//police_OnPlayerConnect(playerid);
	medic_OnPlayerConnect(playerid);
	//gps_OnPlayerConnect(playerid);
	jobs_OnPlayerConnect(playerid);
	box_OnPlayerConnect(playerid);
	trucker_OnPlayerConnect(playerid);
	bus_OnPlayerConnect(playerid);
	fireman_OnPlayerConnect(playerid);
	miner_OnPlayerConnect(playerid);
	school_OnPlayerConnect(playerid);
	taxi_OnPlayerConnect(playerid);
	paperboy_OnPlayerConnect(playerid);
	loader_OnPlayerConnect(playerid);
	roadworker_OnPlayerConnect(playerid);
#endif

//==============================================================================
 	GetPlayerName(playerid, PlayerInfo[playerid][pName], MAX_PLAYER_NAME);// ������ ��� ��������������� ������ � ���������� � ���� ����������.

	rega_OnPlayerConnect(playerid, PlayerInfo[playerid][pName]);
//==============================================================================
	//--------------------------------------------------------------------------
	new strtmp[56+32+3+3];
	format(strtmp, sizeof(strtmp), "OnPlayerConnect: %s[%d] has joined the server (Ping:%d)", PlayerName(playerid), playerid, GetPlayerPing(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	SendClientMessage(playerid, COLOR_RED, strtmp);
	return 1;
}


/*
public OnPlayerRequestClass(playerid, classid)//����������� ��� �������� ����� ������ �� ������ ����������, � ����� ��� ������ ������� ������ (�����).
//����� ��������� ������ ��� ����� ������������ � ����� ��� ��� �� ���������
//������� ����������� ������ ���, ����� ����� �������� "�����" � "������", ����� ������� ������ �����.
//��� ����������� �-��� ForceClassSelection(playerid); SetPlayerHealthEx(playerid, 0);
//��� ����� �������� TogglePlayerSpectating
//playerid	ID ������, ������������ �����.
//classid	ID ������������ ������� ������.
{   //����� GameModeExit() ������ OnPlayerRequestClass ����������� ������ ��� �-�� OnPlayerConnect
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//if(CHECKING == 1)
	//{
		//��������������
		//new strings[MAX_STRING];
format(strings, sizeof(strings), "Begin OnPlayerRequestClass(playerid:%d, classid:%d)", playerid, classid);
//ABroadCast(COLOR_MAROON, strings, 9);
//SendClientMessageToAll(COLOR_YELLOW, strings);
SendClientMessage(playerid, COLOR_RED, strings);
	//}
	//PlayerInfo[playerid][pHealth] = floatadd(PlayerInfo[playerid][pSHealth], 50.0);
	SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth]);//���-�� ������ � ������
	//--------------------------------------------------------------------------
	gPlayerSpawned[playerid] = 0;
	if(gPlayerLogged[playerid] == 0 && CurState[playerid] != PLAYER_STATE_SPECTATING)//!= 9
	{//���� �-�� ����������� �� ������� �����������
//CHECKING = 1;
//���� ����� ����������� � ��� �� ����� LOGIN � �� ��������� � ������ ����������,
//�.�. �-�� OnPlayerRequestClass ����������� ������ ��� OnPlayerLogin
//��� ����� ��������������
//���� ����� ������ �� ���������, � ��� �-�� ����� ��� �� �����������
		//��������������
		//PlayerInfo[playerid][pInt] = GetPVarInt(playerid, "FirstInterior");
		//PlayerInfo[playerid][pVirtual] = GetPVarInt(playerid, "FirstVirtual");
		//PlayerInfo[playerid][pLocal] = GetPVarInt(playerid, "FirstLocal");
format(strings, sizeof(strings), "RequestClassBeforeLogin(player:%s, classid:%d, state:%d!=(SPECTATING:9) Int:%d Virt:%d Loc:%d X:%.1f Y:%.1f Z:%.1f)",
	PlayerName(playerid), classid, CurState[playerid],
	PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual],	PlayerInfo[playerid][pLocal],
	CurPos[0][playerid], CurPos[1][playerid], CurPos[2][playerid]);
SendClientMessage(playerid, COLOR_RESTARTING, strings);

		SetPlayerInteriorEx(playerid, PlayerInfo[playerid][pInt]);
		SetPlayerVirtualWorldEx(playerid, PlayerInfo[playerid][pVirtual]);
		TogglePlayerSpectating(playerid, 1);//����������� ������ � ����� ������� (��������)
		//SetPVarInt(playerid, "gSpectating", 1);
		//return 0;
  	}
	else //if(gPlayerLogged[playerid] == 1)//���� ����� �����������
	{ 	//&& CurState[playerid] != PLAYER_STATE_SPECTATING
//��������������
format(strings, sizeof(strings), "OnPlayerRequestClass(playerid:%d, classid:%d, state:SPECTATING==%d, logged:%d)", playerid, classid, CurState[playerid], gPlayerLogged[playerid]);
SendClientMessage(playerid, COLOR_GREEN, strings);
//���� ����� ����������� � ��� ����� LOGIN � �� ��������� � ������ ���������� (����� ��������� ������ ������ ������)

		//SetPlayerVirtualWorldEx(playerid, 0);
		//SetPlayerInteriorEx(playerid, 0);
		//SetPlayerCameraPos(playerid, 1630.6136,-2286.0298,110.0);
		//SetPlayerCameraLookAt(playerid, 1887.6034,-1682.1442,47.6167);
		//gSpawn[playerid] = 0;
		//SetPVarInt(playerid, "SpawnChange", 0);
		//PlayerInfo[playerid][pReason] = -1;

		if(player_request[playerid] == 0)
		{
		    SetPlayerSpawn(playerid);
			player_request[playerid] = 1;
		}
		SpawnPlayer(playerid);
//��������������
//new strings[MAX_STRING];
format(strings, sizeof(strings), "End OnPlayerRequestClass(playerid:%d, classid:%d)", playerid, classid);
//ABroadCast(COLOR_MAROON, strings, 9);
//SendClientMessageToAll(COLOR_YELLOW, strings);
SendClientMessage(playerid, COLOR_GREEN, strings);
		return 1;
	}
	return 0;//��� ������ ����� �����
}//end OnPlayerRequestClass(playerid, classid)
*/

//������� ���������� � ��������� ������
/*public OnPlayerRequestClass(playerid, classid)//����������� ��� �������� ����� ������ �� ������ ����������, � ����� ��� ������ ������� ������ (�����).
//����� ��������� ������ ��� ����� ������������ � ����� ��� ��� �� ���������
//������� ����������� ������ ���, ����� ����� �������� "�����" � "������", ����� ������� ������ �����.
//��� ����������� �-��� ForceClassSelection(playerid); SetPlayerHealthEx(playerid, 0);
//��� ����� �������� TogglePlayerSpectating
//playerid	ID ������, ������������ �����.
//classid	ID ������������ ������� ������.
{//�����������: 1. ������ ��� ��������, 2. ��� ����� ������ �� ������ ����������, 3. � ����� ������ ��� ������ ������� ������ (�����).
//��������������
//new strtmp[256];
//format(strtmp, sizeof(strtmp), "grandlarc_OnPlayerRequestClass(playerid:%d, classid:%d, state:%d(SPECTATE:9))", playerid, classid, GetPlayerState(playerid));
//SendClientMessage(playerid, -1, strtmp);
	//#pragma unused classid
	if(IsPlayerNPC(playerid)) return 1;

	if(gPlayerHasSpawnSelected[playerid])
	{//���� ����� ������ �����, �� ��������� � ������ ����� ��� ����
		ClassSel_SetupCharSelection(playerid, classid);

		//if(player_request[playerid] == 0)
		//{
		//    SetPlayerSpawn(playerid);
		//	player_request[playerid] = 1;
		//}
		//SpawnPlayer(playerid);

		//TextDrawSetString(txtClassSelHelper,
			//" ������� ~b~~k~~GO_LEFT~ ~w~��� ~b~~k~~GO_RIGHT~ ~w~����� ������� ����.~n~ ������� ~r~~k~~PED_JUMPING~ ~w~����� ������������.");
		//	" Press ~b~~k~~GO_LEFT~ ~w~or ~b~~k~~GO_RIGHT~ ~w~to switch roleplay.~n~ Press ~r~~k~~PED_JUMPING~ ~w~to spawn.");
		return 1;
	}
	else
	{//���� �-�� ����������� ������ �������� � ����� �� � ������ ����������, � ������ ����� � ��������� 0
		if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
			TogglePlayerSpectating(playerid, 1);//�������� ����� ����������

    		TextDrawShowForPlayer(playerid, txtSpawn);
    		TextDrawShowForPlayer(playerid, txtClassSelHelper);//���������� ������ �� ������ ������

    		gPlayerSpawnSelection[playerid] = -1;
		}
  	}
	return 0;
}*/
public OnPlayerRequestClass(playerid, classid)
{
	if(IsPlayerNPC(playerid)) { return 1; }
//��������������
//format(strings, sizeof(strings), "OnPlayerRequestClass(playerid:%d, classid:%d, state:%d(SPECTATE:9), logged:%d)", playerid, classid, CurState[playerid], gPlayerLogged[playerid]);
//SendClientMessage(playerid, COLOR_GREEN, strings);
	/*if(gPlayerLogged[playerid] == 0 && CurState[playerid] != PLAYER_STATE_SPECTATING)//!= 9
	{//���� �-�� ����������� �� ������� �����������
		SetPlayerInteriorEx(playerid, PlayerInfo[playerid][pInt]);
		SetPlayerVirtualWorldEx(playerid, PlayerInfo[playerid][pVirtual]);
		TogglePlayerSpectating(playerid, 1);//����������� ������ � ����� ������� (��������)
		return 0;
  	}*/
/*#if defined vw_jobs//#endif
	box_OnPlayerRequestClass(playerid);
#endif*/
//------------------------------------------------------------------------------
#if defined grandlarc//#endif
	return grandlarc_OnPlayerRequestClass(playerid, classid);
#else
	return 1;
#endif
}



/*public OnPlayerRequestSpawn(playerid)//�����������, ����� ����� �������� "rshift" ��� ������ SPAWN, ����� ���������� ����� ������ ������
{   //F4 //����������� SpawnPlayer(playerid), ������� ������������� ������ � ��������� �������, � ��������� OnPlayerSpawn
	//��������������
	//new strings[MAX_STRING];
//format(strings, sizeof(strings), "OnPlayerRequestSpawn(playerid:%d, state: %d)", playerid, CurState[playerid]);
//SendClientMessage(playerid, COLOR_YELLOW, strings);
	if(IsPlayerNPC(playerid)) return SpawnPlayer(playerid);
	//if(!IsPlayerLogged[playerid]) return false;
	return login_OnPlayerRequestSpawn(playerid);//- 0, ��� ������� �� Shift ������ �� ����������.
}*/

public OnPlayerDisconnect(playerid, reason)
{ 
	new tickcounter = GetTickCount();
	plids_OnPlayerDisconnect(playerid, reason);
	if(IsPlayerNPC(playerid)) { return 1; }
//------------------------------------------------------------------------------
	for(new i; i < sizeof(TD_LOGO); i ++)
	{
	    TextDrawHideForPlayer(playerid, TD_LOGO[i]);
	}
	//sampvoice_OnPlayerDisconnect(playerid);
	
#if defined vw_sql//#endif
	sql_OnPlayerDisconnect(playerid);
	OnPlayerStatsUpdate(playerid, reason);//�������� OnPlayerSaveParameters(playerid, PlayerInfo[playerid][pName]);
#endif
	walking_OnPlayerDisconnect(playerid);
	
#if defined vw_vehmenu
	firstlook_OnPlayerDisconnect(playerid);
#endif

#if defined vw_speedometer
	//speedometer_OnPlayerDisconnect(playerid);
	advisor_OnPlayerDisconnect(playerid);
#endif

	textdraw_OnPlayerDisconnect(playerid);
	//recon_OnPlayerDisconnect(playerid, reason);
	aview_OnPlayerDisconnect(playerid, reason);
	
#if defined vw_races//#endif
	bloodbowl_OnPlayerDisconnect(playerid);
	derbiLS_OnPlayerDisconnect(playerid);
#endif

#if defined vw_objects//#endif
	//island_OnPlayerDisconnect(playerid);
	bench_OnPlayerDisconnect(playerid);
#endif

#if defined vw_jobs//#endif
	jobs_OnPlayerDisconnect(playerid);
	medic_OnPlayerDisconnect(playerid, reason);
	family_OnPlayerDisconnect(playerid, reason);
	//gps_OnPlayerDisconnect(playerid, reason);
	box_OnPlayerDisconnect(playerid);
	fireman_OnPlayerDisconnect(playerid);
	inkas_OnPlayerDisconnect(playerid);
	school_OnPlayerDisconnect(playerid);
	taxi_OnPlayerDisconnect(playerid);
#endif

#if defined vw_weapons//#endif
	backweapon_OnPlayerDisconnect(playerid);
#endif

	player_OnPlayerDisconnect(playerid, reason);//������ ���� � ����� �����
//------------------------------------------------------------------------------
	new strtmp[MAX_STRING]; //new strreason[10];
	format(strtmp, sizeof(strtmp), "OnPlayerDisconnect %s, reason: %s[%d]", PlayerName(playerid), ReasonLeaveServer(playerid, reason), reason);
	TestLog(OPTIM, strtmp, GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	return 1;
}

public OnPlayerSpawn(playerid)//�������� � ��� ������ ���, �.�. ��������� ��������� ��� �������� � ������ ������ �� ��������
{//��� ������������ �� ���������� ������� ���� ������� ����� ������, �.�. �� ��������� ������������������� ��� ��������
	if(IsPlayerNPC(playerid)) { return 1; }
	
	TogglePlayerClock(playerid, 0);//��������� ��� ������
	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}������������ ���� � ���� (Kicked)!"); Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) {  SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}������������ ID ������ (Kicked)!"); Kick(playerid); return 1; }
	//if(TEST[9] != 0) { return 1; }
	login_OnPlayerSpawn(playerid);
	anim_OnPlayerSpawn(playerid);//����������� ����������

	//if(PlayerInfo[playerid][pSQLID] == 0)
	//{//������ ������ ��� ������ �����
	grandlarc_OnPlayerSpawn(playerid);//������ ������, �.�. ���� ����� ���� ���������� �����
//������ � ������� ������
	//}
//------------------------------------------------------------------------------
	player_OnPlayerSpawn(playerid);//SetPlayerToTeamColor ������������� ���������� ������
	gPlayerSpawned[playerid] = 1;//gPlayerSpawned[playerid] = 1;//��������� ���� - ����� �����������
//��������� ������ �� ������� PlayerInfo, ������� �� ��������� ��� ��������� �� ����
	PlayerInfo_OnPlayerSpawn(playerid);

	SetPlayerToTeamColor(0);
	//recon_OnPlayerSpawn(playerid);
	
#if defined vw_speedometer
	//speedometer_OnPlayerSpawn(playerid);
	advisor_OnPlayerSpawn(playerid);
#endif
	textdraw_OnPlayerSpawn(playerid);

#if defined vw_jobs//#endif
	family_OnPlayerSpawn(playerid);
	box_OnPlayerSpawn(playerid);
	hotel_OnPlayerSpawn(playerid);
#endif

#if defined vw_objects//#endif
	//island_OnPlayerSpawn(playerid);
#endif
//------------------------------------------------------------------------------
	clock_OnPlayerSpawn(playerid);
	TestLog(OPTIM, "OnPlayerSpawn", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	TogglePlayerClock(playerid, 0);//��� ��� ��������� ����� ����������
	return 1;
}


public OnPlayerDeath(playerid, killerid, reason)
{
	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(!IsPlayerConnected(killerid)) { Kick(killerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(killerid < 0 || killerid >= MAX_PLAYERS) { Kick(killerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//if(IsPlayerNPC(killerid)) { return 1; }
	login_OnPlayerDeath(playerid);
	player_OnPlayerDeath(playerid, killerid, reason);
	PlayerInfo_OnPlayerDeath(playerid, killerid, reason);
//------------------------------------------------------------------------------
	grandlarc_OnPlayerDeath(playerid, killerid, reason);

	SendDeathMessageEx(killerid, playerid, reason);
	antidm_OnPlayerDeath(playerid, killerid, reason);
	//recon_OnPlayerDeath(playerid, killerid, reason);
	phone_OnPlayerDeath(playerid);

#if defined vw_weapons//#endif
	dropweapon_OnPlayerDeath(playerid);
	weapon_OnPlayerDeath(playerid, killerid, reason);
#endif

#if defined vw_objects
	bench_OnPlayerDeath(playerid, killerid, reason);
#endif

#if defined vw_jobs
	//gps_OnPlayerDeath(playerid, killerid, reason);
	family_OnPlayerDeath(playerid, killerid);
	armsdealer_OnPlayerDeath(playerid, killerid);
	box_OnPlayerDeath(playerid, killerid);
	fireman_OnPlayerDeath(playerid, killerid, reason);
	school_OnPlayerDeath(playerid);
	medic_OnPlayerDeath(playerid);
#endif
//------------------------------------------------------------------------------
	new strtmp[65+24+3+24+3+32+2];
	format(strtmp, sizeof(strtmp), "OnPlayerDeath(player: %s[%d] killer: %s[%d], reason: %s[%d])",
		PlayerName(playerid), playerid, PlayerName(killerid), killerid, GetDeathReason(killerid, reason), reason);
	TestLog(OPTIM, strtmp, GetTickCount(), tickcounter);

	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	new tickcounter = GetTickCount();
	//new modelid = GetVehicleModel(vehicleid);
//------------------------------------------------------------------------------
	vehicle_OnVehicleSpawn(vehicleid);
//------------------------------------------------------------------------------
	TestLog(OPTIM, "OnVehicleSpawn", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{

	if(!IsPlayerConnected(killerid)) { Kick(killerid); return 1; }
	if(killerid < 0 || killerid >= MAX_PLAYERS) { Kick(killerid); return 1; }
	if(IsPlayerNPC(killerid)) { return 1; }
	//if(killerid != 255) {	    if(AFK_IdleTime[killerid] >= 3) return 1;	}
	new tickcounter = GetTickCount();
	//--------------------------------------------------------------------------
	vehicle_OnVehicleDeath(vehicleid, killerid);
#if defined vw_tuning//#endif
	tuning_OnVehicleDeath(vehicleid, killerid);
#endif
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnVehicleDeath", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{

	walking_OnPlayerEnterVehicle(playerid);
#if defined vw_jobs//#endif
	school_OnPlayerEnterVehicle(playerid, vehicleid);
#endif
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
#if defined vw_races//#endif
	bloodbowl_OnPlayerExitVehicle(playerid);
#endif

#if defined vw_jobs//#endif
	mechanic_OnPlayerExitVehicle(playerid, vehicleid);
	school_OnPlayerExitVehicle(playerid, vehicleid);
#endif

	radio_OnPlayerExitVehicle(playerid, vehicleid);

	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)//�����������, ����� ����� ������ ���� ��������� � ���� (��������, ��������, �������)
//playerid	ID ������, ��������� �������� ����������.
//newstate	ID ������ ����������.
//oldstate	ID ������� ���������.
// States
/*#define PLAYER_STATE_NONE						(0)
#define PLAYER_STATE_ONFOOT						(1)
#define PLAYER_STATE_DRIVER						(2)
#define PLAYER_STATE_PASSENGER					(3)
#define PLAYER_STATE_EXIT_VEHICLE				(4) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER		(5) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER	(6) // (used internally)
#define PLAYER_STATE_WASTED						(7)
#define PLAYER_STATE_SPAWNED					(8)
#define PLAYER_STATE_SPECTATING					(9)
#define PLAYER_STATE_KILLED 					(10)*/
{

	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}������������ ���� � ���� (Kicked)!"); Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}������������ ID ������ (Kicked)!"); Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_NONE)
	{   //���� ID ������ ��������� ����� ����� ��������� �� �����(1) ��� �������� �� ����� ����������(9)
		SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}������������ ���� � ���� (Kicked)!");
		SendClientMessage(playerid, COLOR_EMERALD, "����������� /quit, ����� ����� �� ���� (USE: /q)");
	    //if(PlayerInfo[playerid][pAdmin] == 0 && !IsPlayerAdmin(playerid)) { Kick(playerid); //IsKicked[playerid] = 1; }
		return 1;
	}
	if(	newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_PASSENGER )
	{
	    if( LastCar[playerid] > 0 //&& !gAnticheat[playerid]
		&& !IsInNPCVehicle(LastCar[playerid]) )
	    {
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}�� ��� ������ �� ������������� cleo-script");
			format(strings, sizeof(strings), "CEPBEP: %s[%d] kicked, reason: cleo", PlayerName(playerid), playerid);
			
			SendSystemMessage(COLOR_MAROON, strings, 1);
			Log(KICK, strings);
			if(PlayerInfo[playerid][pAdmin] == 0 && !IsPlayerAdmin(playerid))
			{
				Kick(playerid);//IsKicked[playerid] = 1;
				return 1;
			}
		}
	}
	player_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	//if( !gPlayerLogged[playerid] ) return 1;
	//if( !gPlayerSpawned[playerid] ) return 1;

	textdraw_OnPlayerStateChange(playerid, newstate, oldstate);
	//vehicle_OnPlayerStateChange(playerid, newstate, oldstate);//�� ��� ����� � ����� ������� �� ��������
	//recon_OnPlayerStateChange(playerid, newstate, oldstate);
	spectate_OnPlayerStateChange(playerid, newstate);
	
#if defined vw_vehmenu
	firstlook_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

#if defined vw_speedometer
	//speedometer_OnPlayerStateChange(playerid, newstate, oldstate);
	advisor_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

	//--------------------------------------------------------------------------

	if(IsNeeds(playerid))//if(gParameter2[playerid] == 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "    � �������� �� �� ������ �������� �������, ����� � ���� (USE: /service taxi) ��� ����� �� ��������� !");
		SendClientMessage(playerid, COLOR_GREY, "    ��� ���������� ����������: �������� ����� � ���������� !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
#if defined vw_races//#endif
	bloodbowl_OnPlayerStateChange(playerid, newstate);
	derbiLS_OnPlayerStateChange(playerid, oldstate);
	kickstart_OnPlayerStateChange(playerid, newstate);
#endif

#if defined vw_jobs//#endif
	//hitman_OnPlayerStateChange(playerid, newstate);
	//--------------------------------------------------------------------------
	trucker_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	box_OnPlayerStateChange(playerid, newstate);
	//--------------------------------------------------------------------------
	bus_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	farmer_OnPlayerStateChange(playerid, newstate);
	//--------------------------------------------------------------------------
	fireman_OnPlayerStateChange(playerid, newstate);//���������� �� ����� ����������
	//--------------------------------------------------------------------------
	fisher_OnPlayerStateChange(playerid, newstate);
	//--------------------------------------------------------------------------
	inkas_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	loader_OnPlayerStateChange(playerid, newstate);
	//--------------------------------------------------------------------------
	mechanic_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	medic_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	roadworker_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	school_OnPlayerStateChange(playerid, newstate);
	//--------------------------------------------------------------------------
	taxi_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
	trashman_OnPlayerStateChange(playerid, newstate, oldstate);
	//--------------------------------------------------------------------------
#endif
	TestLog(OPTIM, "OnPlayerStateChange", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//if(IsPlayerInCheckpoint(playerid))
	login_OnPlayerEnterCheckpoint(playerid);
	if( !IsPlayerConnectedEx(playerid) ) return 1;
	if(AFK_IdleTime[playerid] >= 3)
	{
   		SendClientMessage(playerid, COLOR_GREY, "   �� ���������� � AFK !!!!!");
	    return 1;
	}


#if defined vw_props//#endif
	biz_OnEnterCheckpoint(playerid);
#endif

#if defined vw_objects//#endif
	//poster_OnEnterCheckpoint(playerid);
#endif

#if defined vw_jobs//#endif
	trucker_OnEnterCheckpoint(playerid);
	farm_OnPlayerEnterCheckpoint(playerid);
	inkas_OnPlayerEnterCheckpoint(playerid);
	loader_OnEnterCheckpoint(playerid);
	mechanic_OnEnterCheckpoint(playerid);
	medic_OnEnterCheckpoint(playerid);
	miner_OnEnterCheckpoint(playerid);
	paperboy_OnEnterCheckpoint(playerid);
	school_OnEnterCheckpoint(playerid);
	taxi_OnEnterCheckpoint(playerid);
	trashman_OnEnterCheckpoint(playerid);
#endif
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{   
#if defined vw_jobs//#endif
	farm_OnPlayerLeaveCheckpoint(playerid);
#endif
 	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{

#if defined vw_races//#endif
	race_OnPlayerEnterCheckpoint(playerid);
	derbiLS_EnterRaceCheckpoint(playerid);
#endif


#if defined vw_jobs//#endif
	bus_EnterRaceCheckpoint(playerid);
#endif
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
#if defined vw_jobs//#endif
	bus_LeaveRaceCheckpoint(playerid);
#endif
	return 1;
}

public OnRconCommand(cmd[])
{   
	//OnPlayerInfoChange(playerid, RconCommand);
	return 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//public OnObjectMoved(objectid)//����������� ����� �������� ������������ ������� ��������� �������� �����
//����������� ����� ������ ��������� ��������� ����� ������ �������� �������� MoveObject() Note: SetObjectPos does not work when used in this callback.
public OnDynamicObjectMoved(objectid)
{
	//OnPlayerInfoChange(playerid, ObjectMoved);
#if defined vw_objects//#endif
	elevator_OnObjectMoved(objectid);
	ferriswheel_OnObjectMoved(objectid);
	cargoship_OnObjectMoved(objectid);
	fbi_OnObjectMoved(objectid);
#endif

#if defined vw_jobs//#endif
	farmer_OnObjectMoved(objectid);
#endif
	return 0;
}


//------------------------------------------------------------------------------
//public OnPlayerPickUpPickup(playerid, pickupid)
public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(CHECKING[PlayerPickUpPickup])
	{//��������������
		format(strings, sizeof(strings),"OnPlayerPickUpDynamicPickup(playerid:%d, pickupid:%d)",
			playerid, pickupid);
		SendClientMessage(playerid, COLOR_GREEN, strings);
	}
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	login_OnPlayerPickUp(playerid);
	if(AFK_IdleTime[playerid] >= 3) { return 1; }
	//--------------------------------------------------------------------------
	pickup_OnPlayerPickUpPickup(playerid, pickupid);//��� �������� ����������� OnPlayerLeavePickUp
//������ ��� ������� PlayerEnterPickUp �  VehicleEnterPickUp
	return 1;
}
//------------------------------------------------------------------------------


forward PlayerEnterPickUp(playerid, pickupid);
public PlayerEnterPickUp(playerid, pickupid)//�������� ������ �� �����
//stock PlayerEnterPickUp(playerid, pickupid)
{//���������� �� pickup_OnPlayerPickUpPickup
	if(IsPlayerControllable[playerid] == 1) return 1;//�� ������������ ������ ���� ����� ����������

#if defined vw_props//#endif
	house_OnPlayerPickUpPickup(playerid, pickupid);
	biz_OnPlayerPickUpPickup(playerid, pickupid);
	sbiz_OnPlayerPickUpPickup(playerid, pickupid);
#endif

	gpsitem_OnPlayerPickUp(playerid, pickupid);
	anekdot_OnPlayerPickUp(playerid, pickupid);

#if defined vw_races//#endif
	bloodbowl_OnPlayerPickUp(playerid);	//��� ����� BloodBowl STEP1
	derbiLS_OnPlayerPickUp(playerid);//��� ����� 8ball
	kickstart_OnPlayerPickUp(playerid);//��� KickStart STEP1
#endif

#if defined vw_objects//#endif
	elevator_OnPlayerPickUp(playerid, pickupid);
	parkinglift_OnPlayerPickUp(playerid, pickupid);
	fbi_OnPlayerPickUp(playerid, pickupid);
	hotel_OnPlayerPickUp(playerid, pickupid);
	DoJ_OnPlayerPickUp(playerid, pickupid);
#endif

#if defined vw_weapons//#endif
	dropweapon_OnPlayerPickUp(playerid, pickupid);
#endif

#if defined vw_fuel//#endif
	fuel_OnPlayerPickUp(playerid, pickupid);
#endif

#if defined vw_jobs//#endif
	family_OnPlayerPickUp(playerid, pickupid);

	trucker_OnPlayerPickUp(playerid, pickupid);
	armsdealer_OnPlayerPickUp(playerid, pickupid);
	bookmaker_OnPlayerPickUp(playerid, pickupid);
	cardealer_OnPlayerPickUp(playerid, pickupid);
	carjacker_OnPlayerPickUp(playerid, pickupid);
	drugdealer_OnPlayerPickUp(playerid);
	farmer_OnPlayerPickUp(playerid, pickupid);
	fireman_OnPlayerPickUp(playerid, pickupid);
	fisher_OnPlayerPickUp(playerid);
	loader_PlayerEnterPickUp(playerid, pickupid);
	medic_OnPlayerPickUpPickup(playerid);
	miner_PlayerEnterPickUp(playerid, pickupid);
	mushroomer_OnPlayerPickUp(playerid, pickupid);
	roadworker_OnPlayerPickUp(playerid, pickupid);
	school_OnPlayerPickUpPickup(playerid);
	trashman_OnPlayerPickUpPickup(playerid, pickupid);
	//woodsman_OnPlayerPickUpPickup(playerid, pickupid);
#endif

	if(CHECKING[PlayerPickUpPickup])
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "PlayerEnterPickUp(playerid:%d, pickupid:%d)",
			playerid, pickupid);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		format(strings, sizeof(strings), "p_model:%d, p_type:%d, p_x:%.1f, p_y:%.1f, p_z:%.1f",
			Pickups[pickupid][p_model], Pickups[pickupid][p_type], Pickups[pickupid][p_x], Pickups[pickupid][p_y], Pickups[pickupid][p_z]);
		//SendClientMessageToAll(COLOR_RED, strings);
		SendClientMessage(playerid, -1, strings);
	}
	return 1;
}

forward VehicleEnterPickUp(playerid, pickupid);
public VehicleEnterPickUp(playerid, pickupid)//�������� ������ ���� � �����
//stock VehicleEnterPickUp(playerid, pickupid)
{   //���������� �� pickup_OnPlayerPickUpPickup
#if defined vw_fuel//#endif
	fuel_VehicleEnterPickUp(playerid, pickupid);
#endif
	//IsPlayerInKickStart(playerid, pickupid);//��� KickStart STEP4
	//if(IsAtGasStation(playerid))
	
#if defined vw_races//#endif
	bloodbowl_VehicleEnterPickUp(playerid, pickupid);
	kickstart_VehicleEnterPickUp(playerid, pickupid);
#endif

#if defined vw_jobs//#endif
	mechanic_VehicleEnterPickUp(playerid);
#endif
	if(CHECKING[PlayerPickUpPickup])
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "VehicleEnterPickUp(playerid:%d, pickupid:%d)",
			playerid, pickupid);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
		format(strings, sizeof(strings), "p_model:%d, p_type:%d, p_x:%.1f, p_y:%.1f, p_z:%.1f",
			Pickups[pickupid][p_model], Pickups[pickupid][p_type], Pickups[pickupid][p_x], Pickups[pickupid][p_y], Pickups[pickupid][p_z]);
		//SendClientMessageToAll(COLOR_RED, strings);
		SendClientMessage(playerid, -1, strings);
	}
	return 1;
}
forward OnPlayerLeavePickUp(playerid, pickupid);
public OnPlayerLeavePickUp(playerid, pickupid)
//stock OnPlayerLeavePickUp(playerid, pickupid)
{

	fuel_OnPlayerLeavePickUp(playerid, pickupid);

	if(CHECKING[PlayerPickUpPickup])
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "OnPlayerLeavePickup(playerid:%d, pickupid:%d)", playerid, pickupid);
		//SendClientMessageToAll(COLOR_GREEN, strings);
		SendClientMessage(playerid, COLOR_GREEN, strings);//COLOR_LIGHTBLUE
	}
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{  
	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//--------------------------------------------------------------------------
	new interiorid = CurInt[playerid];//GetPlayerInterior(playerid);
#if defined vw_tuning//#endif
	tuning_OnVehicleMod(playerid, vehicleid, componentid, interiorid);
#endif
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnVehicleMod", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{   

	new tickcounter = GetTickCount();

	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//--------------------------------------------------------------------------
	new interiorid = CurInt[playerid];//GetPlayerInterior(playerid);

#if defined vw_props//#endif
	prop_OnVehiclePaintjob(playerid, vehicleid, paintjobid, interiorid);
#endif

#if defined vw_tuning
	tuning_OnVehiclePaintjob(playerid, vehicleid, paintjobid, interiorid);
#endif
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnVehiclePaintjob", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	return 1;

}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{   

	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//--------------------------------------------------------------------------
	new interiorid = CurInt[playerid];//GetPlayerInterior(playerid);
#if defined vw_props//#endif
	prop_OnVehicleRespray(playerid);
#endif

#if defined vw_tuning
	tuning_OnVehicleRespray(playerid, vehicleid, color1, color2, interiorid);
#endif
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnVehicleRespray", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{

	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	if(AFK_IdleTime[playerid] >= 3)
	{
   		SendClientMessage(playerid, COLOR_GREY, "   �� ���������� � AFK !!!!!!");
	    return 1;
	}
	login_OnPlayerSelectedMenuRow(playerid);
	//--------------------------------------------------------------------------
	new Menu:Current = GetPlayerMenu(playerid);//�������� ID ����
	SetPVarInt(playerid, "ShowMenu", 0);//��� ������ �������� ����, ����� ������� ����� ����� ������������
	
#if defined vw_props//#endif
	biz_OnPlayerSelectedMenuRow(playerid, row, Current);
#endif

	skin_OnPlayerSelectedMenuRow(playerid, row, Current);
#if defined vw_objects//#endif
	atm_OnPlayerSelectedMenuRow(playerid, row, Current);
#endif

#if defined vw_jobs//#endif
	family_OnPlayerSelectedMenuRow(playerid, row, Current);
	jobs_OnPlayerSelectedMenuRow(playerid, row, Current);
	police_OnPlayerSelectedMenuRow(playerid, row, Current);
#endif


#if defined vw_tuning
	tuning_OnPlayerSelectedMenuRow(playerid, row, Current);
#endif

	//--------------------------------------------------------------------------
	new strtmp[26+24];
	strcat(strtmp, "OnPlayerSelectedMenuRow ");
	//strcat(strtmp, Current);
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	return 1;
}

public OnPlayerExitedMenu(playerid)
{

	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	//--------------------------------------------------------------------------
	new Menu:Current = GetPlayerMenu(playerid);//�������� ID ����

#if defined vw_props//#endif
	biz_OnPlayerExitedMenu(playerid, Current);
#endif

#if defined vw_objects//#endif
	atm_OnPlayerExitedMenu(playerid, Current);
#endif

#if defined vw_tuning
	tuning_OnPlayerExitedMenu(playerid, Current);
#endif

#if defined vw_jobs//#endif
	family_OnPlayerExitedMenu(playerid, Current);
	jobs_OnPlayerExitedMenu(playerid,Current);
	police_OnPlayerExitedMenu(playerid, Current);
#endif
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnPlayerExitedMenu", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{  

	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	if( !IsPlayerConnected(playerid) ) { return 1; }
	if( IsPlayerNPC(playerid) ) return 1;
	new tickcounter = GetTickCount();
	login_OnPlayerInterior(playerid);
	//--------------------------------------------------------------------------
	player_InteriorChange(playerid, newinteriorid, oldinteriorid);
	checkpoint_OnPlayerInterior(playerid);
	//recon_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	spectate_OnPlayerInterior(playerid, newinteriorid, oldinteriorid);

#if defined vw_jobs//#endif
	trucker_OnPlayerInterior(playerid);
	loader_OnPlayerInterior(playerid);
#endif
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnPlayerInteriorChange", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{//��� ������� ����������� ��� ����, �.�. ��������� ��� ������� � �������

	if(!IsPlayerConnected(playerid)) { SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}������������ ID ������ (Kicked)!"); Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	new tickcounter = GetTickCount();
	login_OnPlayerKeyState(playerid);
	//--------------------------------------------------------------------------
	if( PRESSED(KEY_FIRE) )//if(newkeys == KEY_FIRE && oldkeys != KEY_FIRE)
	{//��������� ������ ����� ������� �������  ����� (Mouse1 - LButton)
		cameditor_OnPlayerKey_FIRE(playerid);
#if defined vw_jobs//#endif
		farmer_OnPlayerKeyStateChange(playerid);
		miner_OnPlayerKeyStateChange(playerid);
		loader_OnPlayerKeyStateChange(playerid);
#endif
	}
	else if( PRESSED(KEY_HANDBRAKE) )
	{ //���� ����� ����� Mouse2 - RButton �� ����� ��� ������ � ������
#if defined vw_jobs//#endif
		trashman_OnPlayerKeyStateChange(playerid);
#endif
	}
	else if( PRESSED(KEY_SPRINT) )
	{//���� ����� ����� W � ������ ��� ������ �� �����
		gunchange_OnPlayerKeyState(playerid);
		bench_OnPlayerKeyState_SPRINT(playerid);
		medic_OnPlayerKeyState_SPRINT(playerid);
		anim_OnPlayerKeyState_SPRINT(playerid);
	}
	else if( PRESSED(KEY_JUMP) )
	{//���� ����� �����  ������ (Shift) �� �����
		bench_OnPlayerKeyState_SPRINT(playerid);
		medic_OnPlayerKeyState_JUMP(playerid);
	}
	else if( PRESSED(KEY_SUBMISSION) )
	{//���� ����� ����� � ������ ��������� (2)//PLUS(+) ON KEYPAD**
	 	if(IsPlayerInAnyVehicle(playerid))
	 	{
#if defined vw_vehmenu
			vehmenu_OnPlayerKeyStateChange(playerid);
#endif
		}

	}
	else if( PRESSED(KEY_YES) )
	{//���� ����� ����� Y
		biz_OnPlayerKeyState_YES(playerid);
		bench_OnPlayerKeyState_YES(playerid);
		fbi_OnPlayerKeyState_YES(playerid);
		hotel_OnPlayerKeyState_YES(playerid);
		actor_OnPlayerKeyState_YES(playerid);
		medic_OnPlayerKeyState_YES(playerid);
		LCN_OnPlayerKeyState_YES(playerid);
		access_OnPlayerKeyState_YES(playerid);
		phone_OnPlayerKeyState_YES(playerid);
	}
	else if( PRESSED(KEY_NO) )
	{//���� ����� ����� N
		phone_OnPlayerKeyState_NO(playerid);

	}
	else if( PRESSED(KEY_WALK) )
	{//���� ����� ����� Alt
		//vote_OnPlayerKeyStateChange(playerid);
		needs_OnPlayerKeyState_PRESSED(playerid);
#if defined vw_objects//#endif
		atm_OnPlayerKeyStateChange(playerid);
#endif
	}
	else if( RELEASED(KEY_WALK))
	{
		needs_OnPlayerKeyState_RELEASED(playerid);
	}
	else if( PRESSED(KEY_ANALOG_UP) )
	{//���� ����� ����� ������ ����� (Numpad8)
#if defined vw_jobs//#endif
		trucker_OnPlayerKeyState_UP(playerid);
		mechanic_OnPlayerKeyState_UP(playerid);
		roadworker_OnPlayerKeyState_UP(playerid);
#endif
#if defined vw_objects//#endif
		spike_OnPlayerKeyState_UP(playerid);
#endif
	}
	else if( PRESSED(KEY_ANALOG_DOWN) )
	{//���� ����� ����� ������ ���� (Numpad2)
#if defined vw_jobs//#endif
		mechanic_OnPlayerKeyState_DOWN(playerid);
#endif
		trailer_OnPlayerKeyState(playerid);
#if defined vw_objects//#endif
		spike_OnPlayerKeyState_DOWN(playerid);
#endif
	}
	else if( PRESSED(KEY_ANALOG_RIGHT) )//num6
	{ //���� ����� ����� ������ ������ D (Numpad6)
#if defined vw_jobs//#endif
		trucker_OnPlayerKeyState_RIGHT(playerid);
		police_OnPlayerKeyState_RIGHT(playerid);
#endif
	}
	else if( PRESSED(KEY_ANALOG_LEFT) )
	{//���� ����� ����� ������ �����  A (Numpad4)
#if defined vw_jobs//#endif
		trucker_OnPlayerKeyState_LEFT(playerid);
		police_OnPlayerKeyState_LEFT(playerid);
#endif
	}
	else if( PRESSED(KEY_SECONDARY_ATTACK) )
	{ //���� ����� ����� (F/Enter) ����� �� �� ������������ ������� F6
#if defined vw_objects//#endif
		elevator_OnPlayerKeyStateChange(playerid);
		gate_OnPlayerKeyState_SECONDARY(playerid);
#endif
	}
	else if( PRESSED(KEY_CROUCH) )//2 - ��������  (C) //2 - ����� (H) /SIRENS
	{ //���� ����� ����� (F/Enter) ����� �� �� ������������ ������� F6
#if defined vw_objects//#endif
		gate_OnPlayerKeyState_DRIVER(playerid);
		fbi_OnPlayerKey_DRIVER(playerid);
		LCN_OnPlayerKey_DRIVER(playerid);
#endif
#if defined vw_jobs//#endif
		roadworker_OnPlayerKey_DRIVER(playerid);
#endif
		migalka_OnPlayerKeyState_DRIVER(playerid);
		
		OP_actor_OnPlayerKeyStateChange(playerid);
		if(IsPlayerInAnyVehicle(playerid)) help_OnPlayerKeyStateChange(playerid);
		
	}
	else if( PRESSED(KEY_CTRL_BACK) )//(262144) H	//(262144) DEL || R || ������� ������ ����� �� ���� - ����. ������������
	{//���� ����� ����� H �� ����� ��� ����� (H) /SIRENS � ������
		//admin_OnPlayerKeyStateChange(playerid);//���� ����� �����
		if(!IsPlayerInAnyVehicle(playerid)) help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
	}
	else if( PRESSED(KEY_LOOK_BEHIND) )
	{//#define KEY_FOOT_LOOK_BEHIND	KEY_LOOK_BEHIND		~k~~PED_LOOKBEHIND~ 		//512 - �������� ����� (Mouse3 - MButton)

	}
	else if( RELEASED(KEY_LOOK_BEHIND))
	{
	
	}
	//textdraw_OnPlayerKeySelect(playerid, newkeys, oldkeys);
	//adminchat_OnPlayerKeyState(playerid, newkeys, oldkeys);


	LastKey[playerid] = oldkeys;
	//--------------------------------------------------------------------------
	new str[58+24+6+6];
	format(str, sizeof(str), "OnPlayerKeyStateChange(player:%s, newkeys:%d, oldkeys:%d)", PlayerName(playerid), newkeys, oldkeys);
	TestLog(OPTIM, str, GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 0;
}

//##############################################################################//
//                                                                              //
//                    ����� �������������� ������� SA-MP 0.3a                   //
//                                                                              //
//##############################################################################//

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{//���������� ����� ����� �������� ������ � �������, � �� ����� ����� ������ ���������� �� ������
	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(dialogid < 0 || dialogid >= 32767) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	dialog_OnDialogResponse(playerid, dialogid, inputtext);//��������� gShowDialog
	SetPVarInt(playerid, "gShowDialog", -1);//���������� ���������� ����� ��� ������ ����� ����� ������ � �������, �.�. ����� ������� ������ ����������
	//--------------------------------------------------------------------------
	rega_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	login_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	interior_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	playermenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	//playerselect_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	PlayerInfoMenu_DialogResponse(playerid, dialogid, response, listitem, inputtext);
	sound_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	items_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	access_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	skins_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	service_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	help_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	command_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	about_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	rules_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
 	tutorial_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	gpsitem_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	//vote_OnDialogResponse1(playerid, dialogid, response, listitem, inputtext);
	//vote_OnDialogResponse2(playerid, dialogid, response, listitem, inputtext);

	actor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	anim_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	OP_actor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	cameditor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	aview_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	accept_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

#if defined vw_vehmenu // ��� �� ��������� � ������� vw_vehmenu
	vehmenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	radio_OnDialog(playerid, dialogid, response, listitem, inputtext);
	sellcar_OnDialog(playerid, dialogid, response, listitem, inputtext);
	carinfo_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#endif

#if defined vw_props//#endif
	prop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	house_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	biz_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	exchange_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#endif

#if defined vw_races//#endif
	race_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	bloodbowl_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	derbiLS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#endif

#if defined vw_objects//#endif
	elevator_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	//poster_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	atm_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	fbi_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	hotel_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	DoJ_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	parkinglift_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	attach_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#endif

#if defined vw_jobs//#endif
	family_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	jobs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	skill_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	trucker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	bookmaker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	box_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	bus_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	drugdealer_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	farmer_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	ferma_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	fisher_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	loader_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	mechanic_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	medic_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	miner_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	mushroomer_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	paperboy_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	police_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	school_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	school2_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	school3_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	taxi_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	trashman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#endif
	//--------------------------------------------------------------------------
	new msgitem[256+1];
	format(msgitem, sizeof(msgitem), "OnDialogResponse(playerid:%s, dialogid:%d[%d])", PlayerName(playerid), dialogid, MenuOperation[playerid]);
	TestLog(OPTIM, msgitem, GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnEnterExitModShop(playerid, enterexit, interiorid)//1 if the player entered or 0 if they exited
{    //��� ������� ����������, ����� ����� ������ ��� ������� �� ���-��������.

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnPlayerClickPlayer(playerid, clickedplayerid, source)//��� ���������
{   //����������, ����� ����� ������ �������� �� ������ � TAB.

	//--------------------------------------------------------------------------
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	if(!IsPlayerConnected(clickedplayerid)) { return 0; }
	if(clickedplayerid < 0 || clickedplayerid >= MAX_PLAYERS-1) { return 1; }
	if(IsPlayerNPC(clickedplayerid)) { return 1; }
	new tickcounter = GetTickCount();
	//--------------------------------------------------------------------------
	//HideDialog(playerid);//��������� ������ ��� ������ ������ ������
	if(source == CLICK_SOURCE_SCOREBOARD)
	{
		admin_OnPlayerClick(playerid, clickedplayerid);
		//vote_OnPlayerClickPlayer(playerid, clickedplayerid);
		////playerselect_OnPlayerClick(playerid, clickedplayerid);
	}
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnPlayerClickPlayer", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnPlayerStreamIn(playerid, forplayerid)//�� �������� �� AFK �������
{   //C���������� ������������ � ������ forplayerid �������� ��� ������ playerid �� �����.

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnPlayerStreamOut(playerid, forplayerid)//�� �������� �� AFK �������
{

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnRconLoginAttempt(ip[], password[], success)
{//��� ������� ����������, ����� ���-�� �������� ����� � RCON � ����; ������� ��� ���.
	//OnPlayerInfoChange(playerid, RconLoginAttempt);
	OP_actor_OnRconLoginAttempt(ip, password, success);
	
	return 0;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnVehicleStreamIn(vehicleid, forplayerid)
{   //���������� ��� ��������� ����� vehicleid � ���� ������ ������ forplayerid.

	plids_OnVehicleStreamIn(vehicleid, forplayerid);

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnVehicleStreamOut(vehicleid, forplayerid)
{   //���������� ��� ������������ ����� ����� � ���� ������ ������.

	plids_OnVehicleStreamOut(vehicleid, forplayerid);

	return 1;
}


//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{   //����������� ��� ����������� ����� ������� �� ������������ ������ ��� ��� ����������

 	//checking_OnVehicleDamageStatus(vehicleid, playerid);
	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	//if(IsPlayerNPC(playerid)) { return 1; }
	//if(AFK_IdleTime[playerid] >= 3)  { return 1; }
    if(	!IsPlayerInAnyVehicle(playerid) ) return 1;
	if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	//--------------------------------------------------------------------------
#if defined vw_jobs//#endif
	trucker_DamageStatusUpdate(vehicleid, playerid);
#endif
 	//--------------------------------------------------------------------------
 	TestLog(OPTIM, "OnVehicleDamageStatusUpdate", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

//##############################################################################//
//                                                                              //
//                    ����� �������������� ������� SA-MP 0.3c                   //
//                                                                              //
//##############################################################################//


//This callback was added in SA-MP 0.3c R3 and will not work in earlier versions!
public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z)
{//������� ���������� ����� ����� ������ ������� ������������� �������� � ������� ��� ��������, ��� ����� ����� � ������ ����������(������ �� ������ ����� ���� ���������!)

	new tickcounter = GetTickCount();
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 0; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 0; }
	if(IsPlayerNPC(playerid)) { return 0; }
	if(passenger_seat != 0) return 0;

	new modelid = GetVehicleModel(vehicleid);
	if(	VehicleArray[modelid-400][Category] == Rail_Transport ||
		VehicleArray[modelid-400][Category] == RC_Vehicles ||
	 	VehicleArray[modelid-400][Category] == Trailers ||
	  	VehicleArray[modelid-400][Category] == Not_Used) return 0;
	//if(AFK_IdleTime[playerid] >= 3)  { return 1; }
	//--------------------------------------------------------------------------


 	//--------------------------------------------------------------------------

	TestLog(OPTIM, "OnUnoccupiedVehicleUpdate", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();

	return 1;
}

//##############################################################################//
//                                                                              //
//                    ����� �������������� ������� SA-MP 0.3d                   //
//                                                                              //
//##############################################################################//

//This callback was added in SA-MP 0.3d and will not work in earlier versions!
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)//, Float:ang=0.0
{//OnPlayerClickMap ����������, ����� ����� ������ ���� / ������� ����� �� ����� ���� ����� (������� ������ ������� ����).
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	login_OnPlayerClickMap(playerid);
	
	admin_OnPlayerClickMap(playerid, fX, fY, fZ);
#if defined vw_jobs//#endif
	//gps_OnPlayerClickMap(playerid, fX, fY, fZ);
#endif
	return 1;
}




//This callback was added in SA-MP 0.3d and will not work in earlier versions!
public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{   //���������� ����� ����� playerid ������� ���� ������ damagedid
   	if(damagedid == INVALID_PLAYER_ID) return 1;
    if(playerid == INVALID_PLAYER_ID) return 1;
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { checkcheat[damagedid] = CHEATLIM+3; return 1; }
	if(!IsPlayerConnected(damagedid)) { Kick(damagedid); return 1; }
	if(damagedid < 0 || damagedid >= MAX_PLAYERS) { Kick(damagedid); return 1; }
	if(IsPlayerNPC(damagedid)) { return 1; }
    if(playerid == damagedid) return 1;
 	if(gPlayerBoxing[playerid] != 0) return 1;
	if(gPlayerBoxing[damagedid] != 0) return 1;
	if(gInTerrorsCount[playerid] != 0) return 1;
	if(gInTerrorsCount[damagedid] != 0) return 1;
	if(gInCTerrorsCount[playerid] != 0) return 1;
	if(gInCTerrorsCount[damagedid] != 0) return 1;
	if( amount < 0.3 ) return 1;//������������ � �������� ������� �� 0.3 �����
	if( !IsPlayerConnectedEx(playerid) || !IsPlayerConnectedEx(damagedid) ) return 1;
	if( !gPlayerSpawned[playerid]  || !gPlayerSpawned[damagedid] ) return 1;
	if( GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT) return 1;
	if(	IsPlayerControllable[playerid] != 0 ||
		IsPlayerControllable[damagedid] != 0 ) return 1;//���� ��� ���������
	if(AFK_IdleTime[damagedid] >= 3) return 1;
//	if(AFK_IdleTime[damagedid] > 5)
//	{
//   		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ������ ������������, �.�. ������� ��������� � AFK !");
//	    return 1;
//	}


//��� ��������
    //if(damagedid == INVALID_PLAYER_ID || GetPlayerTargetPlayer(playerid) != INVALID_PLAYER_ID)

	//format(strings, sizeof(strings), "%s ���� ��� %.1f �����",
	//	PlayerName(damagedid), amount);
	//SendClientMessage(playerid, COLOR_DARKRED, strings);
	
	antidm_OnPlayerGiveDamage(playerid, damagedid, weaponid);
	return 1;
}

//This callback was added in SA-MP 0.3d and will not work in earlier versions!
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)//��� ��� ���� � ��� �� ����������
{    //��� ������� ����������, ����� ����� �������� ����.
/*Return Values:

    1 - Callback will not be called in other filterscripts.
    0 - Allows this callback to be called in other filterscripts.
    It is always called first in filterscripts so returning 1 there blocks other filterscripts from seeing it
*/
    if(issuerid == INVALID_PLAYER_ID) return 1;//������ ��������� ����� LastIssuerid[playerid] = INVALID_PLAYER_ID
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	if(!IsPlayerConnected(issuerid)) { Kick(issuerid); return 1; }
	if(issuerid < 0 || issuerid >= MAX_PLAYERS) { Kick(issuerid); return 1; }
	if(IsPlayerNPC(issuerid)) { checkcheat[playerid] = CHEATLIM+3; return 1; }
	
	
	antidm_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
	return 1;
}


//##############################################################################//
//                                                                              //
//                    ����� �������������� ������� SA-MP 0.3e                   //
//                                                                              //
//##############################################################################//
//This callback was added in SA-MP 0.3e and will not work in earlier versions!
public OnPlayerClickTextDraw(playerid, Text:clickedid)
{//��� ������� ����������, ����� ����� �������� �� TextDraw ��� �������� ����� ������ � ������� ������� Escape.


#if defined vw_changer
	changer_OnPlayerClickTextDraw(playerid, clickedid);
#endif
	gunchange_OnPlayerClickTextDraw(playerid, clickedid);
	//recon_OnPlayerClickTextDraw(playerid, clickedid);
	aview_OnPlayerClickTextDraw(playerid, clickedid);
	
	access_OnPlayerClickTextDraw(playerid, clickedid);
	return 1;
}

//This callback was added in SA-MP 0.3e and will not work in earlier versions!
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{//��� ������� ����������, ����� ����� �������� �� ������-TextDraw. ��� �� ����������, ����� ����� �������� ����� ������ (ESC) - ������, OnPlayerClickTextDraw ����.
#if defined vw_changer
	changer_OnPlayerClickPlTextDraw(playerid, playertextid);
#endif

	return 1;
}

//This function was added in SA-MP 0.3e and will not work in earlier versions!
/*public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{//��� ������� ����������, ����� ����� �������� ������ ����� ����, ��� SelectObject ��� �����������.

	return 1;
}*/
public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{//��� ������� ����������, ����� ����� �������� ������ ����� ����, ��� SelectObject ��� �����������.

	return 1;
}

//This callback was added in SA-MP 0.3e and will not work in earlier versions!
/*public OnPlayerEditObject(playerid, playerobject, objectid, response,
	Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{	//���������� ��� ��������� �������������� ������� ��� ����� ������� ����������.
#if defined vw_objects//#endif
	poster_OnPlayerEditObject(playerid, playerobject, objectid, response, fX,fY,fZ, fRotX,fRotY,fRotZ);
#endif
}*/
public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{	//���������� ��� ��������� �������������� ������� ��� ����� ������� ����������.
#if defined vw_objects//#endif
	//poster_OnPlayerEditObject(playerid, objectid, response, x,y,z, rx,ry,rz);
#endif
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{//����������, ����� ����� ����������� �������������� ����������� �������

	attach_OnPlayerEditAttachedObj(playerid,response,index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);

	return 1;
}



//##############################################################################//
//                                                                              //
//                    ����� �������������� ������� SA-MP 0.3z                   //
//                                                                              //
//##############################################################################//

//This callback was added in SA-MP 0.3z and will not work in earlier versions!
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{// ���������� ������ ��� ������ ����������� ������ ����� ���� ��������� ����, ���� �������� � ����, �� ���������� 0 ����������, � ��� ��������� ������ �� ����������
#if defined vw_weapons//#endif
	shoot_OnPlayerWeaponShot(playerid, weaponid, hittype);
	bullet_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX,fY,fZ);
#endif
 	return 1;
}



//This callback was added in SA-MP 0.3z R2-2 and will not work in earlier versions!
public OnIncomingConnection(playerid, ip_address[], port)
{//����������, ����� IP-����� �������� ���������� ���������� � ��������. ��� ����, ����� ����������� �������� ����������, ����������� BlockIpAddress.
//- �������� ������ "OnIncomingConnection".
//�� ��������, ��� ����� �������� ������������ � �������
//(� ������� ������ ��������: Incoming Connection: IP:PORT",
//������ ����� ��������� ���������; ��� ������ �� ����, ��� ��� playerid ���������, �.�. ����� ��� �� ��������� � �� ����� ID)
	//if(IsPlayerNPC(playerid)) { return 0; }
	//if( !strcmp(ip_address, "127.0.0.1", true) ) { return 0; }
	//if( !strcmp(ip_address, IP_ADRESS, true) ) { return 0; }

	//gCheckDisconnect[playerid] = GetTickCount();
	//strmid(PlayerInfo[playerid][pIP], ip_address, 0, 16, 16);

	return 1;
}



//This callback was added in SA-MP 0.3z R4 and will not work in earlier versions!
//�� �������� ��������� ��������� � ���, ��� ������ ����� ������������ ������������� ��������� ��� ����������� ���������� �� ����� ������� ��� ������-���� �������� ��� ����
//- ���� ��������� �������������� �������� ������������ � ��������� �������� �� �������
//- �������� ����� ������ ��� ������������� �������, "�����������" �� ��������
public OnTrailerUpdate(playerid, vehicleid)//vehicleid - ��� ID ��������
{

//������� ���������� ����� ����� "������������" �� �������(������).
//"�����������" ���������� ����� ����� ������� ������� ������� � ������� �� ������� �������, �� ���� ������� ����� ���������� �� ��� �����.
//� OnTrailerUpdate ����� ������� �� ����������� ������� �� ������������.
//��� ����������� ��������� ���������� ������� OnUnoccupiedVehicleUpdate
//��� ��������� �� ���������� OnVehicleSpawn � OnVehicleDeath ��� ��� "������".

//����� �������� ������ � ���������� �������� ����� "������", ����������� � ������ R-4.
//����� ������ "������" ������� ����������(respawn) �� ����� "����� ������", � �� �����, � ����� ����������� ���������� �������.
//��� ������ � ����������� "�������" ������� ����� ��������� ������������ �� ����� ��������.

//���� ��� �� ���������� ������ �����, �� ��� ����� ���������� ���
//���� �� ������������ ������� �� ����� ���� ��� ������������ �� �������, �� ���
	if(nTrailerID[playerid] != vehicleid && nTrailerID[playerid] != 0)
	//if(LastTrailerCarrier[vehicleid] != MAX_PLAYERS-1)
	{//���� �� ������� ������� ���� �����������, � ������ ��������
		format(strings, sizeof(strings), "CEPBEP: {33AA33}������������������� ����������� �� ������� (Kicked)(playerid:%d, trailerid:%d)", playerid, vehicleid);
		//SendClientMessage(playerid, COLOR_RED, strings);
		SendClientMessageToAll(COLOR_RED, strings);
		//Kick(playerid);
		return 1;
	}
	
	//trailer_OnPlayerUpdate(playerid);

	//if(CHECKING == 1)
	//{//��������������
	//format(strings, sizeof(strings), "OnTrailerUpdate(playerid:%d, trailerid:%d)", playerid, vehicleid);
	//SendClientMessage(playerid, COLOR_GREEN, strings);
	//}
	
//0 - ��������� ������������� ��� �������, ����� ���� ������, ��� �������� ��������� �������. ������� �������� ����� ����������� ������ �������.
//1 - ���������� ������������� ����� ����� ��������.
    return 1;
}

//##############################################################################//
//                                                                              //
//                    ����� �������������� ������� SA-MP 0.3.7                  //
//                                                                              //
//##############################################################################//

public OnActorStreamIn(actorid, forplayerid)
{//��� ������� ����������, ����� ����� �������� � ������� ������ �������-������.

	return 1;
}

//This function was added in SA-MP 0.3.7 and will not work in earlier versions!
public OnActorStreamOut(actorid, forplayerid)
{//��� ������� ����������, ����� ����� �������� ������� ������ �������-������.

	return 1;
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float: amount, weaponid, bodypart)
{//����������, ����� ����� ������� ���� ������.

	return 1;
}

//This callback was added in SA-MP 0.3.7 and will not work in earlier versions!
public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{//��� ������� ����������, ����� ������ ������������� �������� �������������.
//playerid	ID ������ ������� ����������� ������ ���� �� ������������ �����
//vehicleid	ID ����� � ������� ������������� ������
//newstate	0 if siren was turned off, 1 if siren was turned on.

    if(newstate) GameTextForPlayer(playerid, "~W~Siren ~G~on", 1000, 3);
    else GameTextForPlayer(playerid, "~W~Siren ~r~off", 1000, 3);
	return 1;
}


//##############################################################################//
//#                                                                            #//
//#                    ���������������� ���������� �������                     #//
//#                                                                            #//
//##############################################################################//

public OnPlayerCommandText(playerid, cmdtext[])//����������� ��� �������� ������� �������.
//playerid	ID ���������� ������� ������.
//cmdtext[]	����� �������.
{
	//new tickcounter = GetTickCount();
	//--------------------------------------------------------------------------
	if(!IsPlayerConnected(playerid)) { Kick(playerid); return 1; }
	if(playerid < 0 || playerid >= MAX_PLAYERS) { Kick(playerid); return 1; }
	if(IsPlayerNPC(playerid)) { return 1; }
	if( strfind(cmdtext, "~", true) != -1 )
	{
		SendClientMessage(playerid, COLOR_GREY, "   ������ ��� ����� ���������� !");
		return 1;
	}
 	if( GetPVarInt(playerid, "gShowDialog") != -1 )
	{
		SendClientMessage(playerid, COLOR_GREY, "   ������ �������� � ������� ������� ������� !");
		return 1;
	}
	admin_OnPlayerCommandText(playerid, cmdtext);
	cameditor_OnPlayerCommandText(playerid, cmdtext);
	OP_actor_OnPlayerCommandText(playerid, cmdtext);
	// Is the player flooding?
	if(ANTIFLOOD == 1 && PlayerInfo[playerid][pAdmin] != 9 && !IsPlayerAdmin(playerid))//��� ��������� ������ ANTIFLOOD=0;
	{
		//if((GetTickCount()-iPlayerChatTime[playerid]) < 2000)
		if((GetTickCount() - GetPVarInt(playerid, "ChatTime")) < 2000)
		{
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}�� ������ ������������ ������� ������ ��� � ��� �������.");
		    return 1;//- 1, ������ ��������� �������.
		}

    }//���� �����
	//--------------------------------------------------------------------------
	new tmp[MAX_STRING], strcmd[MAX_STRING], gMessage[MAX_STRING];
	new cmd[20], idx, giveplayerid;
	cmd = strtok(cmdtext, idx);//����������  �������� ����� �������� ������ � ���������� &index
	/*if(!strcmp(cmd, "/resp", true))
	{
//printf("�������� 0");
		for(new i = GetVehiclePoolSize(); i != 0; --i)
		{
			//if(!IsValidVehicle(i)) continue;//������� �� ������������ ��������.
			//new modelid = GetVehicleModel(i);
			//if(modelid < 400) continue;//���������� �� ������������� �����
//printf("�������� carid:%d ������", i);//�������� �� //747
			if(!SetVehicleToRespawn(i)) break;
//printf("�������� carid:%d ���������", i);
		}
		
		return 1;
	}*/
	if(!strcmp(cmd, "/help", true)) help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
	else if(!strcmp(cmd, "/list", true) || !strcmp(cmd, "/online", true)) LIST(playerid);
	else if(!strcmp(cmd, "/generalcmd", true)) GeneralCMD(playerid);
	else if(!strcmp(cmd, "/jobhelp", true)) job_command(playerid);//JobHelp(playerid);
	else if(!strcmp(cmd, "/othercmd", true)) OtherCMD(playerid);
	
	else if(!strcmp(cmd, "/familycmd", true)) family_command(playerid);

	else if(!strcmp(cmd, "/info", true)) ServerInfo(playerid);
	else if(!strcmp(cmd, "/tdinfo", true)) TextDrawInfo(playerid);
	else if(!strcmp(cmd, "/tab", true)) TabInfo(playerid);
#if defined vw_races//#endif
	else if(!strcmp(cmd, "/kinfo", true) || !strcmp(cmd, "/kickstartinfo", true)) kickstart_OnPlayerCommandText(playerid);//��� KickStart
#endif
	else if(!strcmp(cmd, "/jobmanual", true))
	{
	    /*if(PlayerInfo[playerid][pJob] == 0)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   JobManual ����! �� �� ��� �� ��������� !");
			help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
			return 1;
	    }*/
		JobManual(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "OK", "�����", PlayerInfo[playerid][pJob]);//caption, bigmsgitem,
		return 1;
	}
	else if(!strcmp(cmd, "/phonehelp", true)) PhoneHelp(playerid);
	else if(!strcmp(cmd, "/househelp", true)) HouseHelp(playerid);
	
	else if(!strcmp(cmd, "/property", true) || !strcmp(cmd, "/prop", true)) PropertyHelp(playerid);//��� ������������ STEP1
	else if(!strcmp(cmd, "/buy", true)) prop_CMD_buy(playerid);
	
	else if(!strcmp(cmd, "/leaderhelp", true)) LeaderCMD(playerid);//LeaderHelp(playerid);
	else if(!strcmp(cmd, "/clanhelp", true)) ClanHelp(playerid);
	else if(!strcmp(cmd, "/island", true)) { //island_OnPlayerCommandText(playerid);
	}
	else if(!strcmp(cmd, "/gunchange", true)) gunchange_ShowWeaponMenu(playerid);

	else if(!strcmp(cmd, "/gps", true))
	{
#if defined vw_jobs//#endif
		//gps_OnPlayerCommandText(playerid);//, cmdtext);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/changer", true))
	{
		DeletePVar(playerid, "Action");
   	    SetPVarInt(playerid, "TotalItems", 212); //gTotalItems = 212;
	    if(GetPVarInt(playerid, "page_active") != 3) SetPVarInt(playerid, "chang_page", 0);//19);
		SetPVarInt(playerid, "page_active", 3);//1 - ����� ��� 3 - �����

		//SetPVarInt(playerid, "TotalItems", 311); //gTotalItems = 311;
	    //if(GetPVarInt(playerid, "page_active") != 1) SetPVarInt(playerid, "chang_page", 0); //���� ���������� ���������, ����� ���������� � ������ ��������
	    //SetPVarInt(playerid, "page_active", 1);//1 - ����� ��� 3 - �����
#if defined vw_changer
		changer_CreateSelectionMenu(playerid);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/race", true))//��� ����� STEP1
	{
#if defined vw_races
		race_Menu(playerid);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/gate", true))//��� ����� STEP1
	{
#if defined vw_objects//#endif
		gate_OnPlayerCommandText(playerid);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/firstlook", true))
	{
#if defined vw_vehmenu
		firstlook_OnPlayerCommandText(playerid);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/trafic", true))
	{
#if defined vw_jobs//#endif
		trucker_OnPlayerCommandText(playerid);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/fight", true))
	{
#if defined vw_jobs//#endif
		box_OnPlayerCommandText(playerid);
#endif
		return 1;
	}
	else if(!strcmp(cmd, "/biz", true))
	{
#if defined vw_props//#endif
		if(PlayerInfo[playerid][pAdmin] < 6)
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /biz [number]");
			return 1;
		}
		new bouse = strval(tmp);
		CMD_biz(playerid, bouse);
#endif
		//return 1;
	}
	else if(!strcmp(cmd, "/animlist", true)) anim_List(playerid);
	else if(!strcmp(cmd, "/carhelp", true)) vehmenu_OnPlayerKeyStateChange(playerid);//CarHelp(playerid);
	else if(!strcmp(cmd, "/id", true))
	{
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /id [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d ����������� �� �������.", giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
		format(strcmd, sizeof(strcmd), "%s[%d] - %s", PlayerName(giveplayerid), giveplayerid, PlayerInfo[giveplayerid][pIP]);
		SendClientMessage(playerid, COLOR_GREY, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/ip", true))
	{
		/*if(PlayerInfo[playerid][pAdmin] < 3)
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� �������!");
			return 1;
		}*/
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /ip [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
		/*for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			//new playerIP[16];
			GetPlayerIp(i, PlayerInfo[i][pIP], 16);
			if(!strcmp(tmp, PlayerInfo[i][pIP], true))
			{
				format(strcmd, sizeof(strcmd), "%s[%d] - %s", PlayerName(i), i, PlayerInfo[i][pIP]);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
			}
		}*/
	    new playerIP[16];	GetPlayerIp(playerid, playerIP, 16);
		format(strcmd, sizeof(strcmd), "%s[%d] - %s[%s]", PlayerName(giveplayerid), giveplayerid, PlayerInfo[giveplayerid][pIP], playerIP);
		SendClientMessage(playerid, COLOR_GREY, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/admins", true))
	{
        if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pAccount] == 0)
        {
            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
            return 1;
        }
		AdminsOnline(playerid);
		//return 1;
	}
	else if(!strcmp(cmd, "/report", true))
	{
		if(PlayerInfo[playerid][pMuted] > GetTickCount())
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������, �� ���������!");
			return 1;
		}
		gMessage = strrest(cmdtext, idx);
		if(!strlen(gMessage))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /report [text]");
			return 1;
		}
		new found = -1;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(PlayerInfo[i][pAdmin] != 3) continue;
			found = i;
			break;
		}
		if(found == -1)
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "   �� ������ ������ ���������� ����������� �� �������.");
			return 1;
		}
		format(strcmd, sizeof(strcmd), "Report from %s[%d]: %s", PlayerName(playerid), playerid, gMessage);
		SendClientMessage(playerid, COLOR_YELLOW, strcmd);//"���� ������ ���������� �����������.");
		//ABroadCast(COLOR_RED, strcmd, 5);
		SendAllAdminMessage(COLOR_RED, strcmd, 1);
		//SendClientMessage(playerid, COLOR_YELLOW, "���� ������ ���������� �����������.");
	    //return 1;
	}
	else if(!strcmp(cmd, "/stats", true))
	{
	    SetPVarInt(playerid, "gDocuments", 0);
		OnPlayerShowStats(playerid, playerid);
		//return 1;
	}
 	else if(!strcmp(cmd, "/NPCrestart", true) || !strcmp(cmd, "/NPCres", true))
	{
        if( //PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6 &&//����� ������� ������
			PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
            return 1;
        }
		//foreach(Bot, i)
		for(new i=0; i<GetMaxPlayers(); i++)
		{
			if( !IsPlayerConnected(i) ) continue;
			if( !IsPlayerNPC(i) ) continue;
			CallRemoteFunction("OnRemotePlayerSpawn", "i", i);//����� ������� ������
		}
		format(strcmd, sizeof(strcmd), "AdmCmd: %s ���������� NPC ���������.", PlayerName(playerid));
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 5);
		//SendClientMessage(playerid, -1, strcmd);
	}
	else if(!strcmp(cmd, "/anim", true))
	{
		aview_AnimList(playerid);
	}
	else if(!strcmp(cmd, "/recon", true))
	{   //��� ������ � spectateid - ID ������ �� ������� �� ����������
		spectate_OnPlayerCommandText(playerid, cmdtext);
	}
	else if(!strcmp(cmd, "/music", true))
	{
        if(!PlayerInfo[playerid][pCDPlayer])
		{
		    SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� MP3-Player !");
		    return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp)) {
			SendClientMessage(playerid, COLOR_HERBAL, "|_______________ MusicIndex _______________|");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /music [0 - OFF]");
			SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
			//return 1;
		}
	    if(strlen(tmp) && strval(tmp) == 0)
		{
			StopAudioStreamForPlayer(playerid);
			SetPVarInt(playerid, "Radio", 0);
		    GameTextForPlayerEx(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~MP3-Player OFF", 5000, 5);
			return 1;
		}
		Radio(playerid);
		//return 1;
	}
	else if(!strcmp(cmd, "/fullreset", true))
	{
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
			return 1;
		}
		if(	(!strcmp(tmp, root_pass, true) && strlen(tmp)) ||
			!strcmp(tmp, CREATOR, true)) {	}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
			return 1;
		}
        //CallLocalFunction("OnRemoteResetServer");
        ClearOnline();

        OnRemoteResetServer();
        format(strcmd, sizeof(strcmd), "AdmCmd: %s OnRemoteResetServer", PlayerName(playerid));
		Log(ADMINLOG, strcmd);
		//------------------------------------------------------------------
		//return 1;
	}
	return 1;
	//- 0, ������ ���������� �� ��� �������, ����� ��������� ����� ��������� ���������� �������� 'SERVER: Unknown command'.
//������� ���������: ������������, �������.
//Returning '0' is used to inform the server that the command
//has not been successfully processed, and passes it to other scripts.
//If there hasn't been a successful process, then you will get that
//'SERVER: Unknown Command.' error.
}//end OnPlayerCommandText

//##############################################################################//
//#                                                                            #//
//#                  ���������������� ���������� ���������                     #//
//#                                                                            #//
//##############################################################################//
public OnPlayerText(playerid, text[])//����������� ��� �������� ������� ������ � ���.
//playerid ID ���������� ������.
//text[] �����, ��������� �������.
{

	//vote_OnPlayerText(playerid, text)//��� ������ STEP2
	return 1;
//- 1, ��������� �������, ��������� ��������� � ���.
}// End OnPlayerText(playerid, text[])




//##############################################################################//
//#                                                                            #//
//#                                ��������                                    #//
//#                 ����������� ��� ��������� ������ �� ������                 #//
//#               � ������� �������� � �� ������ � ���� ��������               #//
//#        ��������: ������������� ��� ����������� ����������� ��������        #//
//# �� ����������� ����� ����� ��������� � ������� ��� ���� � ������ ��������  #//
//#                                                                            #//
//##############################################################################//

//�-�� ��� �������� ����������� ������� OnTrailerAttachedToVehicle
//forward trailer_OnPlayerUpdate(playerid);
//public trailer_OnPlayerUpdate(playerid)//��� ��������������
stock trailer_OnPlayerUpdate(playerid)//��� ��������������
{   //���������� �� OnPlayerUpdate, �.�. //� OnTrailerUpdate ����� ������� �� ����������� ������� �� ������������
	//if(!IsPlayerInAnyVehicle(playerid)) { return 1; }
	new newstate = CurState[playerid];
	if(newstate != PLAYER_STATE_DRIVER) { return 1; }

	new carid = nCarID[playerid];//GetPlayerVehicleID(playerid);
	new carmodel = VehInfo[carid][cModel];//VehInfo[carid][cModel];//GetVehicleModel(carid);//VehInfo[carid][cModel];
	if(carid == 0) { LastTrailer[carid] = 0; return 1; }
	if(carmodel != 0 && carmodel != 525 && !IsInHardTruck(carid)) { return 1; }

	new trailerid = GetVehicleTrailer(carid);//���������� 0 ���� ������ �� �����������.////nTrailerID[playerid];//GetVehicleTrailer(carid);
	if(trailerid != LastTrailer[carid])//� ��� ��� �� �� ����� �����������
	{   //���� ��������� ����������
		if(	IsTrailerAttachedToVehicle(carid) )//��� �� �����������
		{
		    if(CHECKING[TrailerUpdate])
		    {
				//new strings[MAX_STRING];
				format(strings, sizeof(strings), "vehicleid: %d currently towing a trailerid: %d.", carid, trailerid);
				SendClientMessage(playerid, COLOR_SYSTEM, strings);
			}
			LastTrailerCarrier[trailerid] = playerid;
			IsTrailerAttach[trailerid] = carid;

			nTrailerID[playerid] = trailerid;
			nTrailerModel[playerid] = GetVehicleModel(trailerid);//VehInfo[trailerid][cModel];//GetVehicleModel(trailerid);

            CallLocalFunction("OnTrailerAttachedToVehicle", "ddd", playerid, carid, trailerid);
			//OnTrailerAttachedToVehicle(playerid, carid, trailerid);
		}
		else//��� �� ����������
		{
		    if(CHECKING[TrailerUpdate])
		    {
				SendClientMessage(playerid, COLOR_SYSTEM, "You are not towing a trailer.");
			}
			IsTrailerAttach[LastTrailer[carid]] = 0;
            LastTrailerCarrier[trailerid] = MAX_PLAYERS-1;//���������� ����������

			DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
			nTrailerID[playerid] = 0;
			nTrailerModel[playerid] = 0;
			
			//PlayerTextDrawHide(playerid, txdTrailerIcon[playerid]);
			
            CallLocalFunction("OnTrailerAttachedToVehicle", "ddd", playerid, carid, trailerid);
			//OnTrailerAttachedToVehicle(playerid, carid, trailerid);//LastTrailer[carid]
			//gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		}
		//�������� ������ ���������
		LastTrailer[carid] = trailerid;
	}
	return 1;
}

forward OnTrailerAttachedToVehicle(playerid, vehicleid, trailerid);//, attachstate
public OnTrailerAttachedToVehicle(playerid, vehicleid, trailerid)//, attachstate//��� ��������������
{   //���������� ������ ����� ������ ������������ � ������ ��� �����������
	if(trailerid != 0)
	{//����������
		if(CarStatus[nCarID[playerid]][st_engine] == VEHICLE_PARAMS_ON)
		{
#if defined vw_speedometer
			//speedometer_OnTrailerAttached(playerid, vehicleid, trailerid);
			advisor_OnTrailerAttached(playerid, vehicleid, trailerid);
#endif
		}
		trucker_OnTrailerAttachedToVeh(playerid, trailerid);
	}
	else
	{ //���������
	 	//gTextDrawHideCarTime[playerid] = true;
#if defined vw_speedometer
		//speedometer_OnTrailerAttached(playerid, vehicleid, trailerid);
		advisor_OnTrailerAttached(playerid, vehicleid, trailerid);
#endif

	}

	if(CHECKING[TrailerUpdate])
	{//��������������
		format(strings, sizeof(strings), "OnTrailerAttachedToVehicle(playerid:%d, vehicleid:%d, trailerid:%d)", playerid, vehicleid, trailerid);
		SendClientMessage(playerid, COLOR_GREEN, strings);
	}
	return 1;
}


stock GetTickCountEx()
{
//#if defined Windows
	//return tickcount();
//#else
	return GetTickCount();
//#endif
}

new bool:OnPlayerUpdate_run = false;
public OnPlayerUpdate(playerid)
{  
	new tickcounter = GetTickCount();
//�� ��� ������� � ��������� � ������������� �� ������ ����� ����������
	//if( !IsPlayerConnected(playerid) ) { return 0; }
	if( IsPlayerNPC(playerid) ) { return 1; }
	//if( !gPlayerLogged[playerid] ) return 1;
	grandlarc_OnPlayerUpdate(playerid, CurState[playerid]);
	
	//if( !gPlayerSpawned[playerid] ) return 1;
    if(OnPlayerUpdate_run == true) print("OnPlayerUpdate: recursion !!!");//��� � ������� ��� �� ����� �� �����, ��� �� ������ ��� �������� ����
    OnPlayerUpdate_run = true;

    if(AFK != 0 && gAFK_ToggleMode[playerid] != 0)
    {
		gAFK_ToggleMode[playerid] = 0;//�������� ���� - ������ ������� �� � ���
		AFK_IdleTime[playerid] = 0;//c�������
	}
	new anim_id = GetPlayerAnimationIndex(playerid);
	//==========================================================================
	trailer_OnPlayerUpdate(playerid);//�-�� ��� �������� ����������� ������� OnTrailerAttachedToVehicle
	player_OnPlayerUpdate(playerid);//��������� ������� ��������� GetPlayerPos
	//==========================================================================
#if defined vw_objects//#endif
	gate_OnPlayerUpdate(playerid);
	//airdefence_OnPlayerUpdate(playerid);
#endif

#if defined vw_weapons
	backweapon_OnPlayerUpdate(playerid);
#endif
	//==========================================================================
	if(GetTickCountEx() >= oneseconds[playerid] + 1000)//��������� ��������, ������ ���������� �������, ����� �� ��������� ������ ��� ��������
	{
		//==============================================================
		AntiSpeedHackTimer(playerid);
		//----------------------------------------------------------------------
		trucker_OneSecondTimers(playerid);

		checkpoint_OneSecondTimers2(playerid);//������� ��������� ���������� � �������� ��������
		pickup_OneSecondTimers2(playerid);//��� �������� ����������� OnPlayerLeavePickUp
//text3D_OneSecondTimers2(playerid);//��� ������� 3� �������
		mapicon_OneSecondTimers(playerid);
		textdraw_OneSecondTimers(playerid);//����� �������� ��� ��� �������

		//vote_OneSecondTimers(playerid);
		spectate_OneSecondTimers(playerid);
		phone_OneSecondTimers(playerid);

#if defined vw_speedometer
//speedometer_OneSecondTimers(playerid);
		advisor_OneSecondTimers(playerid);
		radar_OneSecondTimers(playerid);
#if defined vw_objects//#endif
		roadblock_OneSecondTimers(playerid);
		bench_OneSecondTimers(playerid);
//object_OneSecondTimers2(playerid);//��� ������� ��������
#endif
#endif

#if defined vw_fuel//#endif
		fuel_OneSecondTimers(playerid);
#endif

#if defined vw_races//#endif
		bloodbowl_OneSecondTimers(playerid);
		derbiLS_OneSecondTimers(playerid);
		kickstart_OneSecondTimers(playerid);
#endif

#if defined vw_jobs//#endif

		//----------------------------------------------------------------------
		box_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		bus_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		farmer_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		fireman_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		fisher_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		medic_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		police_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		roadworker_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		taxi_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		medic_OneSecondTimers(playerid);
		//----------------------------------------------------------------------
		clock_OneSecondTimers(playerid);
#endif
		//==============================================================
		oneseconds[playerid] = GetTickCountEx();
	}
	//==========================================================================
	//twoseconds[playerid] = 0;//������� ��� 2-����������� �������
	//==========================================================================
	if(GetTickCountEx() >= oneminuts[playerid] + 60*1000)//�������� ��������, ������ ���������� �������, ����� �� ��������� ������ ��� ��������
	{//
		//----------------------------------------------------------------------
		weather_OneMinutsTimer();
		//----------------------------------------------------------------------
		needs_OneMinutsTimer(playerid, anim_id);
		if(PlayerInfo[playerid][pAccount] == 0 && PlayerInfo[playerid][pLevel] > 2)
		{
			OnPlayerIncreaseParameter(playerid);
		}
		//----------------------------------------------------------------------
#if defined vw_jobs//#endif
		family_OneMinutsTimer(playerid);
#endif
		//----------------------------------------------------------------------
		//��� ���������
		gTextDrawHideBattery[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		//----------------------------------------------------------------------
		oneminuts[playerid] = GetTickCountEx();
	}
	//==========================================================================
	if(GetTickCountEx() >= fiveminuts[playerid] + 5*60*1000)//5�������� ��������
 	{
		payday_OnFiveMinutsTimer(playerid);
		//----------------------------------------------------------------------
#if defined vw_objects//#endif
		roadblock_OnFiveMinutsTimer(playerid);
#endif

#if defined vw_jobs//#endif
		fireman_FiveMinutsTimer();
		school_FiveMinutsTimer(playerid);
		family_OnFiveMinutsTimer(playerid);
		job_OnFiveMinutsTimer(playerid);
#endif
		//----------------------------------------------------------------------
		fiveminuts[playerid] = GetTickCountEx();
	}
	//==========================================================================
	if(GetTickCountEx() >= fifteenminuts[playerid] + 15*60*1000)//15�������� ��������
 	{
		//----------------------------------------------------------------------
		timers_FifteenMinutsTimer(playerid);//PlayerIdleKick15Timer(playerid);
		//----------------------------------------------------------------------
		fifteenminuts[playerid] = GetTickCountEx();
	}
	//==========================================================================
	if(GetTickCountEx() >= onehour[playerid] + 60*60*1000)//������� ��������
 	{
		//----------------------------------------------------------------------
#if defined vw_props//#endif
		prop_OneHourTimer();
#endif

		//vote_OneHourTimer(playerid);
		//----------------------------------------------------------------------
		onehour[playerid] = GetTickCountEx();
	}
	//==========================================================================
	cameditor_OnPlayerUpdate(playerid);
	//virtualkey_OnPlayerUpdate(playerid);//�������� ������ ���� ������ ����� �� �������� �����
	//recon_OnPlayerUpdate(playerid);
	respray_OnPlayerUpdate(playerid, CurState[playerid]);
	CheckPlayerHealthStateUpdate(playerid);
	anim_OnPlayerUpdate(playerid, anim_id, CurState[playerid]);
	walking_OnPlayerUpdate(playerid);
	////playerselect_OnPlayerUpdate(playerid, LastKey[playerid], anim_id, CurState[playerid]);
	weapon_OnPlayerUpdate(playerid);
	camstate_OnPlayerUpdate(playerid);//�������������� � ��������� ������
	spike_OnPlayerUpdate(playerid, CurState[playerid]);//��� ���������� ����
	//==========================================================================
	TestLog(OPTIM, "OnPlayerUpdate", GetTickCount(), tickcounter);//new tickcounter = GetTickCount();
	OnPlayerUpdate_run = false;
	return 1;//- 1, ���������� ����� ����
}//OnPlayerUpdate End

forward OnPlayerAnimationChange(playerid, anim_id, animlib[], newanim[], oldanim[]);
public OnPlayerAnimationChange(playerid, anim_id, animlib[], newanim[], oldanim[])
{   //���������� ��� ����� ��������
	new strtmp[100+4+32+32+32];
	format(strtmp, sizeof(strtmp), "anim_id={00ff00}%d{800000} animlib={00ff00}%s{800000} newanim={00ff00}%s{800000} oldanim={00ff00}%s", anim_id, animlib, newanim, oldanim);
	SendClientMessage(playerid, COLOR_SYSTEM, strtmp);//0x00ff00ff
    //SendSystemMessage(COLOR_MAROON, strings, 9);
	return 1;
}

stock CheckPlayerHealthStateUpdate(playerid)
{   //���������� �� OnPlayerUpdate ��� HEALTH
	new Float: health;	GetPlayerHealth(playerid, health);
	if(health != LastHealth[playerid])
	{
	    CallLocalFunction("OnPlayerChangeHealth", "dff", playerid, health, LastHealth[playerid]);
	    LastHealth[playerid] = health;
	}
}
forward OnPlayerChangeHealth(playerid, Float: newhealth, Float: oldhealth);
public OnPlayerChangeHealth(playerid, Float: newhealth, Float: oldhealth)
{   //���������� ����� ���������� ��������
    // Player health has changed since the last update -> server, so obviously thats the thing updated.
    // Lets do further checks see if he's lost or gained health, anti-health cheat? ;)
    if(newhealth > oldhealth)
    {
        // He has gained health! Cheating? Write your own scripts here to figure how a player
		//gained health!
//SendClientMessage(playerid, COLOR_SYSTEM, "He has gained health!");
    }
    else
    {
        // He has lost health!
//SendClientMessage(playerid, COLOR_SYSTEM, "He has lost health!");
    }
}


#if defined vw_checking //���� �-�� ���������� ��������� �� ������ include
//������������ �� ������������� OnPlayerUpdate.
new counter[MAX_CALLBACK];//������� ������ � ������ �-��
 //��� ������ ���� � server.cfg ��������� filterscripts vw_inspect
 //��� � public OnFilterScriptInit() ��������� SendRconCommand("loadfs vw_inspect");
//���������� ������ ��� ����� ���������� ����� �� ��������, ������� ������ ������ PlayerInfo
forward OnPlayerInfoChange(playerid, callback);
public OnPlayerInfoChange(playerid, callback)
{//������ ��������� �������������� ��� ��������� ���������� � ������.
	counter[callback]++;
	if(	callback == UnoccupiedVehicleUpdate || //callback == PlayerKeyStateChange || callback == TrailerUpdate ||
		callback == PlayerStreamIn || callback == PlayerStreamOut ||
		callback == VehicleStreamIn || callback == VehicleStreamOut)
	{
		return 0;
	}
	
	if(CHECKING[PlayerInfoChange])
	{//��������������
		new str[137+32+3+32+2+6];
		format(str, sizeof(str),
		"Information about player {0080FF}%s{FFFFFF}[%d] has changed. Callback: {0080FF}%s{FFFFFF}[%d] call: {00FF00}%d",
			PlayerName(playerid), playerid, GetNameCallback(callback), callback, counter[callback]);
		SendClientMessage(playerid, -1, str);
		//print(str);
	}
	
	return 0;
}
#endif


stock TextDrawInfo(playerid)
{
	new bigmsgitem[12*32];
	new strcmd[MAX_STRING];
#if defined vw_speedometer
	format(bigmsgitem, sizeof(bigmsgitem), "ShowSpeed: %d[%d/%d]", TextDrawShowSpeed[playerid], gTextDrawShowSpeed[playerid], gTextDrawHideSpeed[playerid]);
#endif
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowCarTime: %d[%d/%d]", bigmsgitem, TextDrawShowCarTime[playerid], gTextDrawShowCarTime[playerid], gTextDrawHideCarTime[playerid]);
#if defined vw_races//#endif
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowRace: %d[%d/%d]", bigmsgitem, TextDrawShowRace[playerid], gTextDrawShowRace[playerid], gTextDrawHideRace[playerid]);
#endif
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowCS: %d[%d/%d]", bigmsgitem, TextDrawShowCS[playerid], gTextDrawShowCS[playerid], gTextDrawHideCS[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowClock: %d[%d/%d]", bigmsgitem, TextDrawShowClock[playerid], gTextDrawShowClock[playerid], gTextDrawHideClock[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowScale: %d[%d/%d]", bigmsgitem, TextDrawShowScale[playerid], gTextDrawShowScale[playerid], gTextDrawHideScale[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowBattery: %d[%d/%d]", bigmsgitem, TextDrawShowBattery[playerid], gTextDrawShowBattery[playerid], gTextDrawHideBattery[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowBlind: %d[%d/%d]", bigmsgitem, TextDrawShowBlind[playerid], gTextDrawShowBlind[playerid], gTextDrawHideBlind[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowSystemMessage: %d[%d/%d]", bigmsgitem, TextDrawShowMessage[playerid], gTextDrawShowMessage[playerid], gTextDrawHideMessage[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowBegunok: %d[%d/%d]", bigmsgitem, TextDrawShowBegunok, gTextDrawShowBegunok, gTextDrawHideBegunok);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowHealthArmour: %d[%d/%d]", bigmsgitem, TextDrawShowArmour[playerid], gTextDrawShowArmour[playerid], gTextDrawHideArmour[playerid]);
	format(bigmsgitem, sizeof(bigmsgitem), "%s\nShowChat: %d[%d/%d]", bigmsgitem, TextDrawShowChat[playerid], gTextDrawShowChat[playerid], gTextDrawHideChat[playerid]);

	if(strlen(bigmsgitem) > sizeof(bigmsgitem) || strlen(bigmsgitem) <= 0)
	{
		//��������������
		format(strcmd, sizeof(strcmd), "Error: TextDrawInfo %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strcmd);
		return 1;
	}
	else ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "TextDrawInfo", bigmsgitem, "OK", "");
	return 1;
}
