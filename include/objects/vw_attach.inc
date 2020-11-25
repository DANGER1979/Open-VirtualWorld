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
{11735, "Сапог"},
{11749, "Наручники 1"},
{18632, "Удочка"},
{18633, "Балонный ключ 1"},
{18634, "Монтировка 1"},
{18635, "Молоток 1"},
{18636, "Полицейская Фуражка 1"},
{18637, "Полицейский Щит 1"},
{18638, "Каска 1"},
{18639, "Черная Шляпа 1"},
{18640, "волосы 1"},
{18641, "Фонарик 1"},
{18642, "электрошокер 1"},
{18643, "Лазерная Указка 1"},
{18644, "Отвертка 1"},
{18645, "Мотошлем 1"},
{18865, "Мобильник 1"},
/*{18866, "Мобильник 2"},
{18867, "Мобильник 3"},
{18868, "Мобильник 4"},
{18869, "Мобильник 5"},
{18870, "Мобильник 6"},
{18871, "Мобильник 7"},
{18872, "Мобильник 8"},
{18873, "Мобильник 9"},
{18874, "Мобильник 10"},*/
{18875, "Пейджер 1"},
{18890, "Грабли 1"},
{18891, "Бандана 1"},
/*{18892, "Бандана 2"},
{18893, "Бандана 3"},
{18894, "Бандана 4"},
{18895, "Бандана 5"},
{18896, "Бандана 6"},
{18897, "Бандана 7"},
{18898, "Бандана 8"},
{18899, "Бандана 9"},
{18900, "Бандана 10"},
{18901, "Бандана 11"},
{18902, "Бандана 12"},
{18903, "Бандана 13"},
{18904, "Бандана 14"},
{18905, "Бандана 15"},
{18906, "Бандана 16"},
{18907, "Бандана 17"},
{18908, "Бандана 18"},
{18909, "Бандана 19"},
{18910, "Бандана 20"},*/
{18911, "Маска 1"},
/*{18912, "Маска 2"},
{18913, "Маска 3"},
{18914, "Маска 4"},
{18915, "Маска 5"},
{18916, "Маска 6"},
{18917, "Маска 7"},
{18918, "Маска 8"},
{18919, "Маска 9"},
{18920, "Маска 10"},*/
{18921, "берет 1"},
/*{18922, "берет 2"},
{18923, "берет 3"},
{18924, "берет 4"},
{18925, "берет 5"},*/
{18926, "шляпа 1"},
/*{18927, "шляпа 2"},
{18928, "шляпа 3"},
{18929, "шляпа 4"},
{18930, "шляпа 5"},
{18931, "шляпа 6"},
{18932, "шляпа 7"},
{18933, "шляпа 8"},
{18934, "шляпа 9"},
{18935, "шляпа 10"},*/
{18936, "шлем 1"},
{18937, "шлем 2"},
{18938, "шлем 3"},
{18939, "Кепка Назад 1"},
{18940, "Кепка Назад 2"},
{18941, "Кепка Назад 3"},
{18942, "Кепка Назад 4"},
{18943, "Кепка Назад 5"},
{18944, "Шляпа Лодочника 1"},
{18945, "Шляпа Лодочника 2"},
{18946, "Шляпа Лодочника 3"},
{18947, "Шляпа-Котелок 1"},
{18948, "Шляпа-Котелок 2"},
{18949, "Шляпа-Котелок 3"},
{18950, "Шляпа-Котелок 4"},
{18951, "Шляпа-Котелок 5"},
{18952, "Боксерский Шлем 1"},
{18953, "Шапка Вязаная 1"},
{18954, "Шапка Вязаная 2"},
{18955, "Кепка Над Глазом 1"},
{18956, "Кепка Над Глазом 2"},
{18957, "Кепка Над Глазом 3"},
{18958, "Кепка Над Глазом 4"},
{18959, "Кепка Над Глазом 5"},
{18960, "Кепка козырек вверх 1"},
{18961, "Шапка дальнобойщика 1"},
{18962, "Ковбойская Шляпа 2"},
{18963, "Си Джей Элвис Хед"},
{18964, "Тюбетейка 1"},
{18965, "Тюбетейка 2"},
{18966, "Тюбетейка 3"},
{18967, "Шляпный Человек 1"},
{18968, "Шляпный Человек 2"},
{18969, "Шляпный Человек 3"},
{18970, "Шляпа Тигра 1"},
{18971, "Панама 1"},
{18972, "Панама 2"},
{18973, "Панама 3"},
{18974, "Маска Зорро 1"},
{18975, "волосы 2"},
{18976, "Мотошлем 2"},
{18977, "Мотошлем 3"},
{18978, "Мотошлем 4"},
{18979, "Мотошлем 5"},
{19006, "Очки Типа1"},
/*{19007, "Очки Типа2"},
{19008, "Очки Типа3"},
{19009, "Очки Типа4"},
{19010, "Очки Типа5"},
{19011, "Очки Типа6"},
{19012, "Очки Type7"},
{19013, "Очки Type8"},
{19014, "Очки Type9"},
{19015, "Очки Type10"},
{19016, "Очки Тип11"},
{19017, "Очки Тип12"},
{19018, "Очки Тип13"},
{19019, "Очки Тип14"},
{19020, "Очки Тип15"},
{19021, "Очки Типа16"},
{19022, "Очки Type17"},
{19023, "Очки Type18"},
{19024, "Очки Type19"},
{19025, "Очки Type20"},
{19026, "Очки Типа21"},
{19027, "Очки Типа22"},
{19028, "Очки Типа23"},
{19029, "Очки Типа24"},
{19030, "Очки Type25"},
{19031, "Очки Типа26"},
{19032, "Очки Type27"},
{19033, "Очки Type28"},
{19034, "Очки Type29"},
{19035, "Очки Type30"},*/
{19036, "Хоккейная Маска белая"},
{19037, "Хоккейная Маска красная"},
{19038, "Хоккейная Маска зеленая"},
{19039, "Часы стрелочные 1"},
/*{19040, "Часы Типа 2"},
{19041, "Часы Тип 3"},
{19042, "Часы Типа 4"},
{19043, "Часы Типа 5"},*/
{19044, "Часы электронные 6"},
/*{19045, "Часы Типа 7"},
{19046, "Часы Типа 8"},
{19047, "Часы Типа 9"},
{19048, "Часы Типа 10"},
{19049, "Часы Типа 11"},
{19050, "Часы Типа 12"},
{19051, "Часы Типа 13"},
{19052, "Часы Типа 14"},
{19053, "Часы Типа 15"},*/
{19064, "Шапка санты"},
{19065, "Шапка санты"},
{19066, "Шапка санты"},
{19067, "Шапка 1"},
{19068, "Шапка 1"},
{19069, "Шапка 1"},
{19077, "Волосы 3"},
{19078, "Попугай"},
/*{19080, "Лазерная Указка 2"},
{19081, "Лазерная Указка 3"},
{19082, "Лазерная Указка 4"},
{19083, "Лазерная Указка 5"},
{19084, "Лазерная Указка 6"},*/
{19085, "повязка на глазу 1"},
{19086, "Фалло-Бензопила 1"},
{19090, "Помпон Синий"},
{19091, "Помпон Красный"},
{19092, "Помпон Зеленый"},
{19093, "Каска 2"},
{19094, "BurgerShot Hat 1"},
{19095, "Ковбойская Шляпа 1"},
{19096, "Ковбойская Шляпа 3"},
{19097, "Ковбойская Шляпа 4"},
{19098, "Ковбойская Шляпа 5"},
{19099, "Полицейская Фуражка 2"},
{19100, "Полицейская Фуражка 3"},
{19101, "Армейский Шлем 1"},
/*{19102, "Армейский Шлем 2"},
{19103, "Армейский Шлем 3"},
{19104, "Армейский Шлем 4"},
{19105, "Армейский Шлем 5"},
{19106, "Армейский Шлем 6"},
{19107, "Армейский Шлем 7"},
{19108, "Армейский Шлем 8"},
{19109, "Армейский Шлем 9"},
{19110, "Армейский Шлем 10"},
{19111, "Армейский Шлем 11"},
{19112, "Армейский Шлем 12"},*/
{19113, "Глупый Шлем 1"},
{19114, "Шлем Dont shoot me"},
{19115, "Шлем Danger"},
{19116, "Обычный Шлем 1"},
{19117, "Обычный Шлем 2"},
{19118, "Обычный Шлем 3"},
{19119, "Обычный Шлем 4"},
{19120, "Обычный Шлем 5"},
{19136, "волосы+шляпа+очки"},
{19137, "CluckinBell Hat 1"},
{19138, "Полицейские Очки 1"},
{19139, "Полицейские Очки 2"},
{19140, "Полицейские Очки 3"},
{19141, "шлем спецназа 1"},
{19142, "броня спецназа 1"},
{19160, "Каска 3"},
{19161, "Полицейская Шляпа 1"},
{19162, "Полицейская Шляпа 2"},
{19163, "Маска горилы 1"},
{19200, "Полицейский Шлем 1"},
{19274, "волосы клоуна"},
{19306, "Флаг красный"},
{19307, "Флаг синий"},
{2993, "Флаг зеленый"},
{19317, "Бас-гитара"},
{19318, "Гитара Flying V"},
{19319, "Гитара Warlock"},
{19330, "Пожарная каска 1"},
{19331, "Пожарная каска 2"},
{19346, "хотдог 1"},
{19347, "значок шерифа 1"},
{19348, "трость 1"},
{19349, "монокль 1"},
{19350, "усы 1"},
{19351, "усы 2"},
{19352, "цилиндр 1"},
{19418, "Наручники 2"},//11749
{19421, "Наушники серые"},
{19422, "Наушники черные"},
{19423, "Наушники красные"},
{19424, "Наушники синие"},
{19469, "Галстук"},
{19472, "Противогаз"},
{19487, "цилиндр 2"},
{19488, "Шляпа-Котелок 6"},
{19513, "белый телефон"},
{19520, "Фуражка 1"},
{19521, "Фуражка 2"},
//{19522, "Пипак домика красный"},
//{19523, "Пипак домика оранжевый"},
//{19524, "Пипак домика желтый"},
{19528, "Шляпа незнайки"},
{19555, "Бокс Перчатка L"},
{19556, "Бокс Перчатка R"},
{19558, "Кепка развозчика пиццы"},
{19559, "Рюкзак туриста"},
{19578, "банан"},
{19583, "Нож кухонный"},
{19590, "Меч"},
{19591, "Веер"},
/*{19605, "Конус вниз синий"},
{19606, "Конус вниз зелёный"},
{19607, "Конус вниз красный"},*/
{19610, "Микрофон"},
{19621, "Масленка"},
{19622, "Метла"},
{19623, "Фотоаппарат"},
{19624, "Чемодан"},
{19626, "Лопата"},
{19627, "Гаечный ключ"},
{19631, "Молот"},
//{19632, "Паленья горящие"},
{19801, "Балаклава"},
{19904, "Жилет аранжевый"},
{19914, "Бита"},
{19942, "Рация"}
};

new AttachmentBones[18][24] = {
{"1. Спина"},
{"2. Голова"},
{"3. Левое плечо"},
{"4. Правое плечо"},
{"5. Левая рука"},
{"6. Правая рука"},
{"7. Левое бедро"},
{"8. Правое бедро"},
{"9. Левая нога"},
{"10. Правая нога"},
{"11. Правые икры"},
{"12. Левые икры"},
{"13. Левое предплечье"},
{"14. Правое предплечье"},
{"15. Левая ключица"},
{"16. Правая ключица"},
{"17. Шея"},
{"18. Челюсть"}
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
//максимально 10 слотов 0-9,т.е. к игроку можно максимум прикрепить 10 объектов
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
	print("  vw_attach.inc Самообучаемая система прикрепления объектов By: DANGER1979");
	print("_____________________________________________");
	print(" ");
	return 1;
}
//forward LoadAttachObjectsDb();
stock LoadAttachObjectsDb()
{//вызывается из OnFilterScriptInit()
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

//записываем
	SaveAttachObjectsDb(response, GetPlayerSkin(playerid), modelid, boneid,
						fOffsetX, fOffsetY, fOffsetZ,
						fRotX, fRotY, fRotZ,
						fScaleX, fScaleY, fScaleZ);
//print(debug_string);
//SendClientMessage(playerid, 0xFFFFFFFF, debug_string);

    SetPlayerAttachedObjectExx(playerid,index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);
    SendClientMessage(playerid, 0xFFFFFFFF, "Вы закончили редактирование прикреплённого объекта");
    return 1;
}




stock SaveAttachObjectsDb( 	response, skinid, modelid, boneid,
							Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
							Float:fRotX, Float:fRotY, Float:fRotZ,
							Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{//вызывается из OnPlayerEditAttachedObject
	if(!response) return 1;

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

//если в базе нету записи по этому скину, этой модели и на этой части тела,то добавить запись
	new query[82+159 + 3+5+2+9*8];//
//INSERT INTO `players` (`Name`,`Password`,`Mail`,`IP`,`Sex`,`Age`,`Origin`,`Interior`,`Virtual`,`Local`) VALUES ('Duncan_Macleod', '123', 'danger1979@mail.ru', '192.168.1.1', 1, '1979-04-05', 4, 0, 0, 0)
	format(query,sizeof(query),"SELECT * FROM `attachobjects` WHERE `skinid`=%d AND `modelid`=%d AND `boneid`=%d LIMIT 1", skinid, modelid, boneid);
	new DBResult:db_result = db_query(db_AttachObjects,query);

	if(db_num_rows(db_result))
	{//если в базе есть одна запись для данного скина установленного объекта в данну часть тела
  		db_free_result(db_result);
		//UpdateAttachObjectsDb(skinid, modelid, boneid);//то обновить координаты
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
	{//иначе добавить в базу новую запись
//наполнение базы
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
	strcat(string, "Слот \tИспользуется?\tModelID\n");
	for(new x;x<MAX_PLAYER_ATTACHED_OBJECTS;x++)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, x)) format(string, sizeof(string), "%s%d\tДА\t%d\n", string, x, AttachedObject[playerid][Modelid][x]);
		else format(string, sizeof(string), "%s%d\tНЕТ\t - \n", string, x);
	}
	ShowPlayerDialog(playerid, DIALOG_ATTACH_INDEX_SELECTION, DIALOG_STYLE_TABLIST_HEADERS, \
		"{FF0000}Attachment Modification - Index Selection", string, "Select", "Exit");
}

stock ModelSelection(playerid, listitem)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, listitem))
	{
		ShowPlayerDialog(playerid, DIALOG_ATTACH_EDITREPLACE, DIALOG_STYLE_MSGBOX, \
		"{FF0000}Attachment Modification", "Вы хотите отредактировать прикреп. объект в слоте\n или удалить его?", "Edit", "Delete");
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
	SetPVarInt(playerid, "AttachmentIndexSel", listitem);//записываем номер выбранного слота
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
//			EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));//вызывает паблик OnPlayerEditAttachedObject и появляется система работы собъектом
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
{//вызывается из OnPlayerEditAttachedObject и из DIALOG_ATTACH_BONE_SELECTION
	new bool: found = false;

	AttachedObject[playerid][Modelid][index] = modelid;
	AttachedObject[playerid][Bone][index] = boneid;
	AttachedObject[playerid][aOffsetX][index] = fOffsetX;
	AttachedObject[playerid][aOffsetY][index] = fOffsetY;
	AttachedObject[playerid][aOffsetZ][index] = fOffsetZ;
	AttachedObject[playerid][aRotX][index] = fRotX;
	AttachedObject[playerid][aRotY][index] = fRotY;
	AttachedObject[playerid][aRotZ][index] = fRotZ;
	
//проверяем если в базе для нашего скина такой объект установленный в эту часть тела то загружаем его в нужном положении
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
	EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));//вызывает паблик OnPlayerEditAttachedObject и появляется система работы собъектом
	return 1;
}

