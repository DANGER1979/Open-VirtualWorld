/*
 *            vw_attachments.pwn v1.0
 *       (c) Copyright 2009-2012 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 15.04.2020
 * @update    : 15.04.2020
 *
 * This file is provided as is (no warranties).
 *
 */

//-------------------------------------------------
//
// This is an example of using the EditAttachedObject functions
// to allow the player to customize their character.
//
// h02 2012
//
// SA-MP 0.3e and above
//
//-------------------------------------------------

//#include <a_samp>

#define DIALOG_ATTACH_INDEX             13500
#define DIALOG_ATTACH_INDEX_SELECTION   DIALOG_ATTACH_INDEX+1
#define DIALOG_ATTACH_EDITREPLACE       DIALOG_ATTACH_INDEX+2
#define DIALOG_ATTACH_MODEL_SELECTION   DIALOG_ATTACH_INDEX+3
#define DIALOG_ATTACH_BONE_SELECTION    DIALOG_ATTACH_INDEX+4

#define MAX_ATTACH_OBJECTS 164//276 //Edit this in case you want less/more cameras

enum AttachmentEnum
{
    attachmodel,
    attachname[24]
}
new AttachmentObjects[][AttachmentEnum] = {
{11735, "�����"},
{11749, "��������� 1"},
{18632, "������"},
{18633, "�������� ���� 1"},
{18634, "���������� 1"},
{18635, "������� 1"},
{18636, "����������� ������� 1"},
{18637, "����������� ��� 1"},
{18638, "����� 1"},
{18639, "������ ����� 1"},
{18640, "������ 1"},
{18641, "������� 1"},
{18642, "������������ 1"},
{18643, "�������� ������ 1"},
{18644, "�������� 1"},
{18645, "�������� 1"},
{18865, "��������� 1"},
/*{18866, "��������� 2"},
{18867, "��������� 3"},
{18868, "��������� 4"},
{18869, "��������� 5"},
{18870, "��������� 6"},
{18871, "��������� 7"},
{18872, "��������� 8"},
{18873, "��������� 9"},
{18874, "��������� 10"},*/
{18875, "������� 1"},
{18890, "������ 1"},
{18891, "������� 1"},
/*{18892, "������� 2"},
{18893, "������� 3"},
{18894, "������� 4"},
{18895, "������� 5"},
{18896, "������� 6"},
{18897, "������� 7"},
{18898, "������� 8"},
{18899, "������� 9"},
{18900, "������� 10"},
{18901, "������� 11"},
{18902, "������� 12"},
{18903, "������� 13"},
{18904, "������� 14"},
{18905, "������� 15"},
{18906, "������� 16"},
{18907, "������� 17"},
{18908, "������� 18"},
{18909, "������� 19"},
{18910, "������� 20"},*/
{18911, "����� 1"},
/*{18912, "����� 2"},
{18913, "����� 3"},
{18914, "����� 4"},
{18915, "����� 5"},
{18916, "����� 6"},
{18917, "����� 7"},
{18918, "����� 8"},
{18919, "����� 9"},
{18920, "����� 10"},*/
{18921, "����� 1"},
/*{18922, "����� 2"},
{18923, "����� 3"},
{18924, "����� 4"},
{18925, "����� 5"},*/
{18926, "����� 1"},
/*{18927, "����� 2"},
{18928, "����� 3"},
{18929, "����� 4"},
{18930, "����� 5"},
{18931, "����� 6"},
{18932, "����� 7"},
{18933, "����� 8"},
{18934, "����� 9"},
{18935, "����� 10"},*/
{18936, "���� 1"},
{18937, "���� 2"},
{18938, "���� 3"},
{18939, "����� ����� 1"},
{18940, "����� ����� 2"},
{18941, "����� ����� 3"},
{18942, "����� ����� 4"},
{18943, "����� ����� 5"},
{18944, "����� ��������� 1"},
{18945, "����� ��������� 2"},
{18946, "����� ��������� 3"},
{18947, "�����-������� 1"},
{18948, "�����-������� 2"},
{18949, "�����-������� 3"},
{18950, "�����-������� 4"},
{18951, "�����-������� 5"},
{18952, "���������� ���� 1"},
{18953, "����� ������� 1"},
{18954, "����� ������� 2"},
{18955, "����� ��� ������ 1"},
{18956, "����� ��� ������ 2"},
{18957, "����� ��� ������ 3"},
{18958, "����� ��� ������ 4"},
{18959, "����� ��� ������ 5"},
{18960, "����� ������� ����� 1"},
{18961, "����� ������������� 1"},
{18962, "���������� ����� 2"},
{18963, "�� ���� ����� ���"},
{18964, "��������� 1"},
{18965, "��������� 2"},
{18966, "��������� 3"},
{18967, "������� ������� 1"},
{18968, "������� ������� 2"},
{18969, "������� ������� 3"},
{18970, "����� ����� 1"},
{18971, "������ 1"},
{18972, "������ 2"},
{18973, "������ 3"},
{18974, "����� ����� 1"},
{18975, "������ 2"},
{18976, "�������� 2"},
{18977, "�������� 3"},
{18978, "�������� 4"},
{18979, "�������� 5"},
{19006, "���� ����1"},
/*{19007, "���� ����2"},
{19008, "���� ����3"},
{19009, "���� ����4"},
{19010, "���� ����5"},
{19011, "���� ����6"},
{19012, "���� Type7"},
{19013, "���� Type8"},
{19014, "���� Type9"},
{19015, "���� Type10"},
{19016, "���� ���11"},
{19017, "���� ���12"},
{19018, "���� ���13"},
{19019, "���� ���14"},
{19020, "���� ���15"},
{19021, "���� ����16"},
{19022, "���� Type17"},
{19023, "���� Type18"},
{19024, "���� Type19"},
{19025, "���� Type20"},
{19026, "���� ����21"},
{19027, "���� ����22"},
{19028, "���� ����23"},
{19029, "���� ����24"},
{19030, "���� Type25"},
{19031, "���� ����26"},
{19032, "���� Type27"},
{19033, "���� Type28"},
{19034, "���� Type29"},
{19035, "���� Type30"},*/
{19036, "��������� ����� �����"},
{19037, "��������� ����� �������"},
{19038, "��������� ����� �������"},
{19039, "���� ���������� 1"},
/*{19040, "���� ���� 2"},
{19041, "���� ��� 3"},
{19042, "���� ���� 4"},
{19043, "���� ���� 5"},*/
{19044, "���� ����������� 6"},
/*{19045, "���� ���� 7"},
{19046, "���� ���� 8"},
{19047, "���� ���� 9"},
{19048, "���� ���� 10"},
{19049, "���� ���� 11"},
{19050, "���� ���� 12"},
{19051, "���� ���� 13"},
{19052, "���� ���� 14"},
{19053, "���� ���� 15"},*/
{19064, "����� �����"},
{19065, "����� �����"},
{19066, "����� �����"},
{19067, "����� 1"},
{19068, "����� 1"},
{19069, "����� 1"},
{19077, "������ 3"},
{19078, "�������"},
/*{19080, "�������� ������ 2"},
{19081, "�������� ������ 3"},
{19082, "�������� ������ 4"},
{19083, "�������� ������ 5"},
{19084, "�������� ������ 6"},*/
{19085, "������� �� ����� 1"},
{19086, "�����-��������� 1"},
{19090, "������ �����"},
{19091, "������ �������"},
{19092, "������ �������"},
{19093, "����� 2"},
{19094, "BurgerShot Hat 1"},
{19095, "���������� ����� 1"},
{19096, "���������� ����� 3"},
{19097, "���������� ����� 4"},
{19098, "���������� ����� 5"},
{19099, "����������� ������� 2"},
{19100, "����������� ������� 3"},
{19101, "��������� ���� 1"},
/*{19102, "��������� ���� 2"},
{19103, "��������� ���� 3"},
{19104, "��������� ���� 4"},
{19105, "��������� ���� 5"},
{19106, "��������� ���� 6"},
{19107, "��������� ���� 7"},
{19108, "��������� ���� 8"},
{19109, "��������� ���� 9"},
{19110, "��������� ���� 10"},
{19111, "��������� ���� 11"},
{19112, "��������� ���� 12"},*/
{19113, "������ ���� 1"},
{19114, "���� Dont shoot me"},
{19115, "���� Danger"},
{19116, "������� ���� 1"},
{19117, "������� ���� 2"},
{19118, "������� ���� 3"},
{19119, "������� ���� 4"},
{19120, "������� ���� 5"},
{19136, "������+�����+����"},
{19137, "CluckinBell Hat 1"},
{19138, "����������� ���� 1"},
{19139, "����������� ���� 2"},
{19140, "����������� ���� 3"},
{19141, "���� �������� 1"},
{19142, "����� �������� 1"},
{19160, "����� 3"},
{19161, "����������� ����� 1"},
{19162, "����������� ����� 2"},
{19163, "����� ������ 1"},
{19200, "����������� ���� 1"},
{19274, "������ ������"},
{19306, "���� �������"},
{19307, "���� �����"},
{2993, "���� �������"},
{19317, "���-������"},
{19318, "������ Flying V"},
{19319, "������ Warlock"},
{19330, "�������� ����� 1"},
{19331, "�������� ����� 2"},
{19346, "������ 1"},
{19347, "������ ������ 1"},
{19348, "������ 1"},
{19349, "������� 1"},
{19350, "��� 1"},
{19351, "��� 2"},
{19352, "������� 1"},
{19418, "��������� 2"},//11749
{19421, "�������� �����"},
{19422, "�������� ������"},
{19423, "�������� �������"},
{19424, "�������� �����"},
{19469, "�������"},
{19472, "����������"},
{19487, "������� 2"},
{19488, "�����-������� 6"},
{19513, "����� �������"},
{19520, "������� 1"},
{19521, "������� 2"},
//{19522, "����� ������ �������"},
//{19523, "����� ������ ���������"},
//{19524, "����� ������ ������"},
{19528, "����� ��������"},
{19555, "���� �������� L"},
{19556, "���� �������� R"},
{19558, "����� ���������� �����"},
{19559, "������ �������"},
{19578, "�����"},
{19583, "��� ��������"},
{19590, "���"},
{19591, "����"},
/*{19605, "����� ���� �����"},
{19606, "����� ���� ������"},
{19607, "����� ���� �������"},*/
{19610, "��������"},
{19621, "��������"},
{19622, "�����"},
{19623, "�����������"},
{19624, "�������"},
{19626, "������"},
{19627, "������� ����"},
{19631, "�����"},
//{19632, "������� �������"},
{19801, "���������"},
{19904, "����� ���������"},
{19914, "����"},
{19942, "�����"}
};

new AttachmentBones[18][24] = {
{"1. �����"},
{"2. ������"},
{"3. ����� �����"},
{"4. ������ �����"},
{"5. ����� ����"},
{"6. ������ ����"},
{"7. ����� �����"},
{"8. ������ �����"},
{"9. ����� ����"},
{"10. ������ ����"},
{"11. ������ ����"},
{"12. ����� ����"},
{"13. ����� ����������"},
{"14. ������ ����������"},
{"15. ����� �������"},
{"16. ������ �������"},
{"17. ���"},
{"18. �������"}
};

enum attachobject_info//SetPlayerAttachedObject
{
	Modelid[10],
	Bone[10],
	Float:aOffsetX[10],
	Float:aOffsetY[10],
	Float:aOffsetZ[10],
	Float:aRotX[10],
	Float:aRotY[10],
	Float:aRotZ[10],
	Float:aScaleX[10],
	Float:aScaleY[10],
	Float:aScaleZ[10],
	Materialcolor1[10],
	Materialcolor2[10]
}
new AttachedObject[MAX_PLAYERS][attachobject_info];


new DB:db_AttachObjects;

enum ao_Info
{
//����������� 10 ������ 0-9,�.�. � ������ ����� �������� ���������� 10 ��������
	ao_SkinID,
	ao_index,
	ao_modelid,
	ao_boneid,
	
	Float:ao_fOffsetX,
	Float:ao_fOffsetY,
	Float:ao_fOffsetZ,
	
	Float:ao_fRotX,
	Float:ao_fRotY,
	Float:ao_fRotZ,

	Float:ao_fScaleX,
	Float:ao_fScaleY,
	Float:ao_fScaleZ
};
new objInfo[MAX_ATTACH_OBJECTS][ao_Info];


//public OnFilterScriptInit()
stock attach_OnGameModeInit()
{
	LoadAttachObjectsDb();
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		SendClientMessage(i, -1, "Attached Object {FFFFFF}(USE: /attachments || /ao)");
	}
	//--------------------------------------------------------------------------
	print("  vw_attach.inc ������������� ������� ������������ �������� By: DANGER1979");
	print("_____________________________________________");
	print(" ");
	return 1;
}
//forward LoadAttachObjectsDb();
stock LoadAttachObjectsDb()
{//���������� �� OnFilterScriptInit()
	// Create a connection to the database
	db_AttachObjects = db_open("attachobjects.db");
	if(db_AttachObjects == DB:0)
	{
		// Error
		print("Failed to open a connection to \"attachobjects.db\".");
		SendRconCommand("exit");
	}
	else
	{	//Creating database if does not exist
		// Success
		// Creates a "player spawn log" table, if it doesn't exists, and frees the result
		//db_free_result(db_query(db_handle, "CREATE TABLE IF NOT EXISTS `spawn_log`(`ID` INTEGER PRIMARY KEY AUTOINCREMENT,`PlayerID` INTEGER NOT NULL,`PlayerName` VARCHAR(24) NOT NULL)"));

		/*new query[560];
		strcat(query, "CREATE TABLE `attachobjects`(`skinid` INTEGER NOT NULL,\
  `index` INTEGER NOT NULL,\
  `modelid` INTEGER NOT NULL,\
  `boneid` INTEGER NOT NULL,\
  `fOffsetX` FLOAT(8, 4) NOT NULL,\
  `fOffsetY` FLOAT(8, 4) NOT NULL,\
  `fOffsetZ` FLOAT(8, 4) NOT NULL,\
  `fRotX` FLOAT(8, 4) NOT NULL,\
  `fRotY` FLOAT(8, 4) NOT NULL,\
  `fRotZ` FLOAT(8, 4) NOT NULL,\
  `fScaleX` FLOAT(8, 4) NOT NULL,\
  `fScaleY` FLOAT(8, 4) NOT NULL,\
  `fScaleZ` FLOAT(8, 4) NOT NULL,");
		strcat(query, "`date` DATE NOT NULL DEFAULT '0000-00-00',\
  `time` TIME NOT NULL DEFAULT '00:00:00')");
		db_free_result(db_query(db_AttachObjects,query));*/
		print("Successfully created a connection to \"attachobjects.db\".");
	}
	return 1;
}

//public OnFilterScriptExit()
stock attach_OnGameModeExit()
{
	// If there is a database connection, close it
	if(db_AttachObjects) db_close(db_AttachObjects);

	return 1;
}


/*public OnPlayerEditAttachedObject( playerid, response, index, modelid, boneid,
                                   Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
                                   Float:fRotX, Float:fRotY, Float:fRotZ,
                                   Float:fScaleX, Float:fScaleY, Float:fScaleZ )*/
stock attach_OnPlayerEditAttachedObj( playerid, response, index, modelid, boneid,
                                   Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
                                   Float:fRotX, Float:fRotY, Float:fRotZ,
                                   Float:fScaleX, Float:fScaleY, Float:fScaleZ )
{

//new debug_string[256+1];
//format(debug_string,256,"OnPlayerEditAttachedObject(response:%d,index:%d,modelid:%d,boneid:%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f)",
//           response,index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);

//����������
	SaveAttachObjectsDb(response, GetPlayerSkin(playerid), modelid, boneid,
						fOffsetX, fOffsetY, fOffsetZ,
						fRotX, fRotY, fRotZ,
						fScaleX, fScaleY, fScaleZ);
//print(debug_string);
//SendClientMessage(playerid, 0xFFFFFFFF, debug_string);

    SetPlayerAttachedObjectExx(playerid,index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);
    SendClientMessage(playerid, 0xFFFFFFFF, "�� ��������� �������������� ������������� �������");
    return 1;
}




stock SaveAttachObjectsDb( 	response, skinid, modelid, boneid,
							Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
							Float:fRotX, Float:fRotY, Float:fRotZ,
							Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{//���������� �� OnPlayerEditAttachedObject
	if(!response) return 1;

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

//���� � ���� ���� ������ �� ����� �����, ���� ������ � �� ���� ����� ����,�� �������� ������
	new query[82+159 + 3+5+2+9*8];//
//INSERT INTO `players` (`Name`,`Password`,`Mail`,`IP`,`Sex`,`Age`,`Origin`,`Interior`,`Virtual`,`Local`) VALUES ('Duncan_Macleod', '123', 'danger1979@mail.ru', '192.168.1.1', 1, '1979-04-05', 4, 0, 0, 0)
	format(query,sizeof(query),"SELECT * FROM `attachobjects` WHERE `skinid`=%d AND `modelid`=%d AND `boneid`=%d LIMIT 1", skinid, modelid, boneid);
	new DBResult:db_result = db_query(db_AttachObjects,query);

	if(db_num_rows(db_result))
	{//���� � ���� ���� ���� ������ ��� ������� ����� �������������� ������� � ����� ����� ����
  		db_free_result(db_result);
		//UpdateAttachObjectsDb(skinid, modelid, boneid);//�� �������� ����������
	    //new query[194+6*8+3*3];
		format(query,sizeof(query),"UPDATE `attachobjects` SET `fOffsetX`=%.4f,`fOffsetY`=%.4f,`fOffsetZ`=%.4f,\
`fRotX`=%.4f,`fRotY`=%.4f,`fRotZ`=%.4f,`fScaleX`=%.4f,`fScaleY`=%.4f,`fScaleZ`=%.4f,`date`='%s',`time`='%s' WHERE `skinid`=%d AND `modelid`=%d AND `boneid`=%d",
			fOffsetX, fOffsetY, fOffsetZ,
			fRotX, fRotY, fRotZ,
			fScaleX, fScaleY, fScaleZ,
			skinid, modelid, boneid, date, time);
		db_free_result(db_query(db_AttachObjects,query));

//new debug_string[256+1];
//format(debug_string,256,"UpdateAttachObjectsDb(skinid:%d,modelid:%d,boneid:%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f)",
//	skinid,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);
//print(debug_string);
	}
	else
	{//����� �������� � ���� ����� ������
//���������� ����
		db_free_result(db_result);
		//InsertAttachObjectsDb(skinid, modelid, boneid);
    	//new query[233+3*3+6*8];
		format(query,sizeof(query),"INSERT INTO `attachobjects` (`skinid`,`modelid`,`boneid`,`fOffsetX`,`fOffsetY`,`fOffsetZ`,`fRotX`,`fRotY`,`fRotZ`,`fScaleX`,`fScaleY`,`fScaleZ`,`date`,`time`) \
VALUES(%d,%d,%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,'%s','%s')",
			//objInfo[modelid][ao_SkinID],objInfo[modelid][ao_modelid],objInfo[modelid][ao_boneid],
			//objInfo[modelid][ao_fOffsetX], objInfo[modelid][ao_fOffsetY],objInfo[modelid][ao_fOffsetZ],
			//objInfo[modelid][ao_fRotX],objInfo[modelid][ao_fRotY],objInfo[modelid][ao_fRotZ],
			//objInfo[modelid][ao_fScaleX],objInfo[modelid][ao_fScaleY],objInfo[modelid][ao_fScaleZ]);
			skinid, modelid, boneid,
			fOffsetX, fOffsetY, fOffsetZ,
			fRotX, fRotY, fRotZ,
			fScaleX, fScaleY, fScaleZ, date, time);
		db_free_result(db_query(db_AttachObjects,query));
	}
	return 1;
}

/*stock InsertAttachObjectsDb(skinid, modelid, boneid)
{
    new query[233+3*3+9*8];
	format(query,sizeof(query),"INSERT INTO `attachobjects` (`skinid`,`modelid`,`boneid`,`fOffsetX`,`fOffsetY`,`fOffsetZ`,`fRotX`,`fRotY`,`fRotZ`,`fScaleX`,`fScaleY`,`fScaleZ`) \
VALUES('%d','%d','%d','%.4f','%.4f','%.4f','%.4f','%.4f','%.4f','%.4f','%.4f','%.4f')",
		objInfo[modelid][ao_SkinID],objInfo[modelid][ao_modelid],objInfo[modelid][ao_boneid],
		objInfo[modelid][ao_fOffsetX], objInfo[modelid][ao_fOffsetY],objInfo[modelid][ao_fOffsetZ],
		objInfo[modelid][ao_fRotX],objInfo[modelid][ao_fRotY],objInfo[modelid][ao_fRotZ],
		objInfo[modelid][ao_fScaleX],objInfo[modelid][ao_fScaleY],objInfo[modelid][ao_fScaleZ]);
}
stock UpdateAttachObjectsDb(skinid, modelid, boneid)
{
    new query[194+9*8+3*3];
	format(query,sizeof(query),"UPDATE `attachobjects` SET `fOffsetX` = '%f', `fOffsetY` = '%f', `fOffsetZ` = '%f' WHERE `skinid` = '%d' AND `modelid` = '%d' AND `boneid` = '%d'",
		objInfo[modelid][ao_fOffsetX],objInfo[modelid][ao_fOffsetY],objInfo[modelid][ao_fOffsetZ],
		skinid, modelid, boneid);

	format(query,sizeof(query),"UPDATE `attachobjects` SET `fRotX` = '%f', `fRotY` = '%f', `fRotZ` = '%f' WHERE `skinid` = '%d' AND `modelid` = '%d' AND `boneid` = '%d'",
		objInfo[modelid][ao_fRotX],objInfo[modelid][ao_fRotY],objInfo[modelid][ao_fRotZ],
		skinid, modelid, boneid);

	format(query,sizeof(query),"UPDATE `attachobjects` SET `fScaleX` = '%f', `fScaleY` = '%f', `fScaleZ` = '%f', WHERE `skinid` = '%d' AND `modelid` = '%d' AND `boneid` = '%d'",
		objInfo[modelid][ao_fScaleX], objInfo[modelid][ao_fScaleY], objInfo[modelid][ao_fScaleZ],
		skinid, modelid, boneid);
}*/

/*public OnPlayerCommandText(playerid, cmdtext[])
{
    if(!strcmp(cmdtext, "/attachments", true) || !strcmp(cmdtext, "/ao", true))
    {
        attach_IndexSelection(playerid);
        return 1;
    }
    return 0;
}*/

stock attach_IndexSelection(playerid)
{
	new string[10*(14+1)];
	strcat(string, "���� \t������������?\tModelID\n");
	for(new x;x<MAX_PLAYER_ATTACHED_OBJECTS;x++)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, x)) format(string, sizeof(string), "%s%d\t��\t%d\n", string, x, AttachedObject[playerid][Modelid][x]);
		else format(string, sizeof(string), "%s%d\t���\t - \n", string, x);
	}
	ShowPlayerDialog(playerid, DIALOG_ATTACH_INDEX_SELECTION, DIALOG_STYLE_TABLIST_HEADERS, \
		"{FF0000}Attachment Modification - Index Selection", string, "Select", "Exit");
}

stock ModelSelection(playerid, listitem)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, listitem))
	{
		ShowPlayerDialog(playerid, DIALOG_ATTACH_EDITREPLACE, DIALOG_STYLE_MSGBOX, \
		"{FF0000}Attachment Modification", "�� ������ ��������������� �������. ������ � �����\n ��� ������� ���?", "Edit", "Delete");
	}
	else
	{//DIALOG_STYLE_LIST
		new string[166*24];//MAX_ATTACH_OBJECTS = 276 276*(12+5+28)
		//strcat(string, "attachmodel \tattachname\n");
		for(new x;x<MAX_ATTACH_OBJECTS;x++)//sizeof(AttachmentObjects)
		{
			format(string, sizeof(string), "%s%s\n", string, AttachmentObjects[x][attachname]);//AttachmentObjects[x][attachmodel],
		}
		ShowPlayerDialog(playerid, DIALOG_ATTACH_MODEL_SELECTION, DIALOG_STYLE_LIST, "{FF0000}Attachment Modification - Model Selection", string, "Select", "Back");
	}
	SetPVarInt(playerid, "AttachmentIndexSel", listitem);//���������� ����� ���������� �����
}

//public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
stock attach_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
    switch(dialogid)
    {
        case DIALOG_ATTACH_INDEX_SELECTION:
        {
            if(!response) { return 1; }
			ModelSelection(playerid, listitem);
            return 1;
        }
        case DIALOG_ATTACH_EDITREPLACE:
        {
            if(!response)//"Delete"
			{
				RemovePlayerAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel") );
				attach_IndexSelection(playerid);
			}
            else //"Edit"
			{
				EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
			}
            DeletePVar(playerid, "AttachmentIndexSel");
            return 1;
        }
        case DIALOG_ATTACH_MODEL_SELECTION:
        {
            if(!response) {  DeletePVar(playerid, "AttachmentIndexSel"); attach_IndexSelection(playerid); return 1; }
			if(GetPVarInt(playerid, "AttachmentUsed") == 1) { EditAttachedObject(playerid, listitem); }
			else
			{
				SetPVarInt(playerid, "AttachmentModelSel", AttachmentObjects[listitem][attachmodel]);
				new string[18*(24+7)];
				for(new x;x<18;x++)//sizeof(AttachmentBones)
				{
					format(string, sizeof(string), "%s%s\n", string, AttachmentBones[x]);
				}
				ShowPlayerDialog(playerid, DIALOG_ATTACH_BONE_SELECTION, DIALOG_STYLE_LIST, \
                    "{FF0000}Attachment Modification - Bone Selection", string, "Select", "Back");
			}
            return 1;
        }
        case DIALOG_ATTACH_BONE_SELECTION:
        {
        	if(!response) {  DeletePVar(playerid, "AttachmentIndexSel"); DeletePVar(playerid, "AttachmentModelSel"); ModelSelection(playerid, listitem); return 1; }
			SetPlayerAttachedObjectExx(playerid, GetPVarInt(playerid, "AttachmentIndexSel"), GetPVarInt(playerid, "AttachmentModelSel"), listitem+1);
//			EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));//�������� ������ OnPlayerEditAttachedObject � ���������� ������� ������ ���������
			SendClientMessage(playerid, 0xFFFFFFFF, "Hint: Use {FFFF00}~k~~PED_SPRINT~{FFFFFF} to look around.");

            DeletePVar(playerid, "AttachmentIndexSel");
            DeletePVar(playerid, "AttachmentModelSel");
            return 1;
        }
    }
    return 0;
}


stock SetPlayerAttachedObjectExx(playerid, index, modelid, boneid,
	Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0,
	Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0,
	Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0,
	materialcolor1 = 0, materialcolor2 = 0)
{//���������� �� OnPlayerEditAttachedObject � �� DIALOG_ATTACH_BONE_SELECTION
	new bool: found = false;

	AttachedObject[playerid][Modelid][index] = modelid;
	AttachedObject[playerid][Bone][index] = boneid;
	AttachedObject[playerid][aOffsetX][index] = fOffsetX;
	AttachedObject[playerid][aOffsetY][index] = fOffsetY;
	AttachedObject[playerid][aOffsetZ][index] = fOffsetZ;
	AttachedObject[playerid][aRotX][index] = fRotX;
	AttachedObject[playerid][aRotY][index] = fRotY;
	AttachedObject[playerid][aRotZ][index] = fRotZ;
	
//��������� ���� � ���� ��� ������ ����� ����� ������ ������������� � ��� ����� ���� �� ��������� ��� � ������ ���������
	new query[233+3*3+9*8], DBResult:db_result;
	format(query,sizeof(query),"SELECT * FROM `attachobjects` WHERE `skinid`=%d AND `modelid`=%d AND `boneid`=%d LIMIT 1", GetPlayerSkin(playerid), modelid, boneid);
	db_result = db_query(db_AttachObjects,query);
	new listitem = GetPVarInt(playerid, "AttachmentIndexSel");
	if(db_num_rows(db_result))
	{
		new field[50];
		db_get_field_assoc(db_result, "skinid", field, sizeof(field) );	objInfo[listitem][ao_SkinID] = strval(field);
		//objInfo[listitem][ao_SkinID] = db_get_field_assoc_int(db_result, "skinid");
		db_get_field_assoc(db_result, "modelid", field, sizeof(field) ); objInfo[listitem][ao_modelid] = strval(field);
		//objInfo[listitem][ao_modelid] = db_get_field_assoc_int(db_result, "modelid");
		db_get_field_assoc(db_result, "boneid", field, sizeof(field) ); objInfo[listitem][ao_boneid] = strval(field);
		//objInfo[listitem][ao_boneid] = db_get_field_assoc_int(db_result, "boneid");
		
		db_get_field_assoc(db_result, "fOffsetX", field, sizeof(field) ); objInfo[listitem][ao_fOffsetX] = floatstr(field);
		db_get_field_assoc(db_result, "fOffsetY", field, sizeof(field) ); objInfo[listitem][ao_fOffsetY] = floatstr(field);
		db_get_field_assoc(db_result, "fOffsetZ", field, sizeof(field) ); objInfo[listitem][ao_fOffsetZ] = floatstr(field);
		
		db_get_field_assoc(db_result, "fRotX", field, sizeof(field) ); objInfo[listitem][ao_fRotX] = floatstr(field);
		db_get_field_assoc(db_result, "fRotY", field, sizeof(field) ); objInfo[listitem][ao_fRotY] = floatstr(field);
		db_get_field_assoc(db_result, "fRotZ", field, sizeof(field) ); objInfo[listitem][ao_fRotZ] = floatstr(field);

		db_get_field_assoc(db_result, "fScaleX", field, sizeof(field) ); objInfo[listitem][ao_fScaleX] = floatstr(field);
		db_get_field_assoc(db_result, "fScaleY", field, sizeof(field) ); objInfo[listitem][ao_fScaleY] = floatstr(field);
		db_get_field_assoc(db_result, "fScaleZ", field, sizeof(field) ); objInfo[listitem][ao_fScaleZ] = floatstr(field);

		found = true;
//if(Debug)
//printf("[Debug]:AttachObjects %d loaded.",i);
	}
	db_free_result(db_result);
	if(found == true)
	{
/*new strings[256];
format(strings, sizeof(strings), "SetPlayerAttachedObject(%d, %d, %d, %.4f,%.4f,%.4f, %.4f,%.4f,%.4f, %.4f,%.4f,%.4f);",
		index, objInfo[listitem][ao_modelid],objInfo[listitem][ao_boneid],
		//objInfo[modelid][ao_SkinID],objInfo[modelid][ao_modelid],objInfo[modelid][ao_boneid],
		objInfo[listitem][ao_fOffsetX], objInfo[listitem][ao_fOffsetY],objInfo[listitem][ao_fOffsetZ],
		objInfo[listitem][ao_fRotX],objInfo[listitem][ao_fRotY],objInfo[listitem][ao_fRotZ],
		objInfo[listitem][ao_fScaleX],objInfo[listitem][ao_fScaleY],objInfo[listitem][ao_fScaleZ]);
		//index, modelid, bone,
		//fOffsetX, fOffsetY, fOffsetZ,
		//fRotX, fRotY, fRotZ,
		//fScaleX, fScaleY, fScaleZ);
SendClientMessage(playerid, -1, strings);*/

		SetPlayerAttachedObject(playerid, index, objInfo[listitem][ao_modelid], objInfo[listitem][ao_boneid],
					objInfo[listitem][ao_fOffsetX],objInfo[listitem][ao_fOffsetY],objInfo[listitem][ao_fOffsetZ],
					objInfo[listitem][ao_fRotX],objInfo[listitem][ao_fRotY],objInfo[listitem][ao_fRotZ],
					objInfo[listitem][ao_fScaleX],objInfo[listitem][ao_fScaleY],objInfo[listitem][ao_fScaleZ],
					materialcolor1,materialcolor2);
		return 1;
	}

	SetPlayerAttachedObject(playerid, index, modelid, boneid,
		fOffsetX,fOffsetY,fOffsetZ,
		fRotX,fRotY,fRotZ,
		fScaleX,fScaleY,fScaleZ,
		materialcolor1,materialcolor2);
	EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));//�������� ������ OnPlayerEditAttachedObject � ���������� ������� ������ ���������
	return 1;
}

