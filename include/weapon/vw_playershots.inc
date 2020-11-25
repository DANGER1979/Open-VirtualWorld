stock playershots_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(WEAPON == 1)
	{

		//new Float:health;
		new Float:health; GetPlayerHealth(playerid, health);
		format(strings, sizeof(strings), "take %.1f damage from %s[%d], weapon: %s[%d] health:%.1f",
			amount, PlayerName(issuerid), issuerid, WeaponName(weaponid), weaponid,
			health);//, LastHealth[playerid]
		//SendClientMessageToAll(COLOR_RED, strings);
		//SendAllAdminMessage(COLOR_RED, strings, 3);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
		//ABroadCast(COLOR_RED, strings, 3);

		new File:file = fopen("playershots.txt",io_append);
	 	new message[256+1];

		if(issuerid != INVALID_PLAYER_ID) {
			format(message, 256, "PlayerTakeDamage(%d) from Player(%d) (%f)hp using weapon: %d bodypart: %d\r\n", playerid, issuerid, amount, weaponid, bodypart);
			SendClientMessage(playerid, 0xFFFFFFFF, message);
		}
		else {
//Explosion	-	51
//Splat	WEAPON_COLLISION -	54

			format(message, 256, "PlayerTakeDamage(%d) (%f)hp using weapon: %d\r\n", playerid, amount, weaponid);
			SendClientMessage(playerid, 0xFFFFFFFF, message);
		}

		fwrite(file, message);
		fclose(file);
	}
}

stock playershots_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(WEAPON)
	{
	    new message[256+1];
	    new weaponname[64+1];
		new File:file = fopen("playershots.txt",io_append);

		GetWeaponName(weaponid, weaponname, 64);
		if(hittype == BULLET_HIT_TYPE_PLAYER) {
			format(message,256,"Shooter(%d) hit Player(%d) PlayerAnim: %d Using: %s [%.2f, %.2f, %.2f]\r\n", playerid, hitid,
				   //GetPlayerAnimationIndex(hitid), weaponname, fX, fY, fZ);
				   PlayerLastAnimation[hitid], weaponname, fX, fY, fZ);
		}
		else if(hittype == BULLET_HIT_TYPE_VEHICLE) {
		    format(message,256,"Shooter(%d) hit Vehicle(%d) Using: %s [%.2f, %.2f, %.2f]\r\n",playerid, hitid, weaponname, fX, fY, fZ);
		}
		else if(hittype == BULLET_HIT_TYPE_NONE) {
		    format(message,256,"Shooter(%d) hit World Using: %s [%.2f, %.2f, %.2f]\r\n",playerid,weaponname,fX,fY,fZ);
		}
		else {
		    format(message,256,"Shooter(%d) hit Object(%d) Using: %s [%.2f, %.2f, %.2f]\r\n",playerid, hitid, weaponname, fX, fY, fZ);
		}
		SendClientMessage(playerid, 0xFFFFFFFF, message);
		fwrite(file, message);
		fclose(file);

		/*
		new LastVectors[128+1];
		new Float:OriginX, Float:OriginY, Float:OriginZ;
		new Float:HitX, Float:HitY, Float:HitZ;
		GetPlayerLastShotVectors(playerid, OriginX, OriginY, OriginZ, HitX, HitY, HitZ);
		format(LastVectors, 128, "Last Vectors: [%.2f, %.2f, %.2f] [%.2f, %.2f, %.2f]", OriginX, OriginY, OriginZ, HitX, HitY, HitZ);
		SendClientMessage(playerid, 0xFFFFFFFF, LastVectors);*/
	}
}
