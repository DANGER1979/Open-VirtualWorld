//RegistrationSTEP7
forward HTTP_CheckOnMail(playerid, response_code, data[]);
public HTTP_CheckOnMail(playerid, response_code, data[])
{   //���������� �� OnDialogResponse
//response_code - ��� ������ ��� ��������� ������
//data - ��������� ����������, ������� �������� ���������� �������� � ���������� �������
	new timers = GetTickCount();
    if(response_code == 200)
    {
		new GotResult = strval(data);
		if(!GotResult)
		{
		    //format(dlgitem, sizeof(dlgitem), "data: %s", data);
			//SendClientMessage(playerid, COLOR_RED, dlgitem);
	        new strtmp[256+1];
	        format(strtmp, sizeof(strtmp), "HTTP_CheckOnMail: %s[%d] ���������� ������ �� �������������� email %d", PlayerName(playerid), playerid, response_code);
	        SendAllAdminMessage(COLOR_MAROON, strtmp, 1);
	        //Log(ERROR, strtmp);

			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}����������, ������� ������������ email (���������� �� mail.ru)!!!");
			RegistrationSTEP6(playerid);
			return 1;
		}
		SetPVarInt(playerid, "gOoc", 1);//����� ��� ��������
		SetPVarInt(playerid, "gNews", 1);//����� �������� ��������
		SetPVarInt(playerid, "gFam", 1);//�������� ��� ��������
		SetPVarInt(playerid, "gSport", 1);//��� ����� ��������
		SetPVarInt(playerid, "gJob", 1);//��� ������� �� ���������

		RegistrationSTEP8(playerid);
    }
    else
    {
    	//SendClientMessage(playerid, COLOR_LIGHTBLUE, "������ ������� �������� �������� ��������� �����. ��������� � ��������������.");

		RegistrationSTEP8(playerid);

		new response[30];
		if(response_code == HTTP_ERROR_BAD_HOST)//1
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), 30);
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)//2
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), 30);
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)//3
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), 30);
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)//4
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), 30);
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)//5
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), 30);
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)//6
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), 30);
        }
        //new strings[MAX_STRING];
        //format(strings, sizeof(strings), "%s[%d] �������� �������� ������ HTTP_CheckOnMail: %s", PlayerName(playerid), playerid, response);
        //SendAllAdminMessage(COLOR_MAROON, strings, 1);
        //Log(ERROR, strings);
    }
	TestLog(OPTIM, "HTTP_CheckOnMail", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}
//404 (Page not found),
//500 (Server error) or 403 (forbidden)


forward HTTP_SendMail(playerid, response_code, data[]);
public HTTP_SendMail(playerid, response_code, data[])//RegistrationSTEP13
{   //���������� �� OnPlayerRegister
	//print(data);
	new timers = GetTickCount();
    if(response_code == 200)
    {
        new GotResult = strval(data);
		if(GotResult)
		{
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: {33AA33}������ '{0080FF}%s'", PlayerInfo[playerid][pKey]);//�� �������� (a..z1..2)
			SendClientMessage(playerid, COLOR_RED, strings);
			format(strings, sizeof(strings), "������� ��������� �� '%s'. {FF0000}��������� �����.", PlayerInfo[playerid][pMail]);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "������� ������ (USE: /changepass) �� ������ ����� ����� � ���� � ������ ������.");
			//format(strings, sizeof(strings), "������ '%s' ������� ��������� �� '%s'. ��������� �����.", PlayerInfo[playerid][pKey], PlayerInfo[playerid][pMail]);
			//AudioMessage(playerid, strings);

//OnPlayerCreateAccount(playerid);
		}
		/*else
		{
		    // ........... ����� ����� ������� ������ ����������� ������ ......................
		    RegistrationSTEP6(playerid);
		}*/
    }
    else
    {
     	//SendClientMessage(playerid, COLOR_LIGHTBLUE, "������ ������� �������� ��������������� ������ �� �������� ����. ��������� � ��������������.");

/*
http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BA%D0%BE%D0%B4%D0%BE%D0%B2_%D1%81%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F_HTTP#500
#define HTTP_ERROR_BAD_HOST				1
#define HTTP_ERROR_NO_SOCKET			2
#define HTTP_ERROR_CANT_CONNECT			3
#define HTTP_ERROR_CANT_WRITE			4
#define HTTP_ERROR_CONTENT_TOO_BIG		5
#define HTTP_ERROR_MALFORMED_RESPONSE	6

    500 Internal Server Error � ����� ���������� ������ �������, ������� �� ������ � ����� ��������� ������ ������. �������� � HTTP/1.0.
������ �������� �� ����� ���������� ����������� ��������.

	501 Not Implemented � ������ �� ������������ ������������, ����������� ��� ��������� �������. �������� ����� ��� �������, ����� ������ �� �������� ��������� � ������� �����. ���� �� ����� ������� ��������, �� �� �� �������� � ������� �������, �� ����� ������� ����� 405. �������� � HTTP/1.0.
    502 Bad Gateway � ������ � ���� ����� ��� ������-������� ������� ��������� � ��������� ���������� ������������� ��������. �������� � HTTP/1.0.
    503 Service Unavailable � ������ �������� �� ����� ����������� ������������ ������� �� ����������� �������� (������������, ���������� � ������). � ���� Retry-After ��������� ������ ����� ������� �����, ����� ������� ������� ������������� ��������� ������. ���� �� ����� ���������� ��������� ������� ����� ��������� ����������, ����������� ����� ��������� ��������� �������� �������� ���� Retry-After ��� ���������� ������� ���������� ��������. �������� � HTTP/1.0.
    504 Gateway Timeout � ������ � ���� ����� ��� ������-������� �� �������� ������ �� ������������ ������� ��� ���������� �������� �������. �������� � HTTP/1.1.
    505 HTTP Version Not Supported � ������ �� ������������ ��� ������������ ������������ ��������� � ������� ������ ��������� HTTP. �������� � HTTP/1.1.
    506 Variant Also Negotiates � � ���������� ��������� ������������ ��������� ������� ��������� ��� �� ����, ��-�� ���� ������� ���������� �����������. �����������������. ������� � RFC 2295 ��� ���������� ��������� HTTP ����������� Transparent Content Negotiation.
    507 Insufficient Storage � �� ������� ����� ��� ���������� �������� �������. �������� ����� ���� ���������. ������� � WebDAV.
    509 Bandwidth Limit Exceeded � ������������ ��� ���������� ���-��������� ���������� �� ����������� �� ����������� �������. � ������ ������ ��������� �������� ������� ���������� � ������ �������-����������. � ��������� ������ ������ ��� �� ������ �� � ����� RFC � ������������ ������ ������� �bw/limited�, �������� � ������ ���������� ��������� cPanel, ��� � ��� �����.
    510 Not Extended � �� ������� ����������� ����������, ������� ������ ������������ ������. ������ ����� ������������� �������� ���������� � ��������� ��� �����������. ������� � RFC 2774 ��� ���������� ��������� HTTP ���������� ����������.


*/
		/*new response[30];
		if(response_code == HTTP_ERROR_BAD_HOST)
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        else if(response_code == 500)
		{
			strmid(response, "���������� ������ �������", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
		//new strings[MAX_STRING];
        format(strings, sizeof(strings), "%s[%d] �������� �� HTTP �������� ������ SendMail: %s[%d]", PlayerName(playerid), playerid, response, response_code);
        //SendAllAdminMessage(COLOR_MAROON, strings, 1);
        Log(ERROR, strings);*/
    }
	TestLog(OPTIM, "HTTP_SendMail", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}


/*
stock SendMessageToICQ(playerid, const message[])//������
{
	new strings[55+128+12+24+4+3 + 12];
	format(strings, sizeof(strings), "gta.strikearena.ru/SendMailVW/SendMessageFromICO.php?Message=%s&PlayerName=%s&ID=%d",
		message, PlayerName(playerid), playerid);
	//print(strings);
	HTTP(playerid, HTTP_GET, strings, "", "");
	//HTTP(playerid, HTTP_HEAD, strings, "", "");
	return 1;
}*/
forward HTTP_PasswordSendToMail(playerid, response_code, data[]);
public HTTP_PasswordSendToMail(playerid, response_code, data[])
{
	new timers = GetTickCount();
    if(response_code == 200)
    {
    	new GotResult = strval(data);
		if(GotResult)
		{
			SetPVarInt(playerid, "PasswordHasEdited", getdate());
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "����� � ����� ������� ���� ������� ���������� �� ��� �������� �����!");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "��������� �������� ���� (�������� ��� ����)!");
		}
		else return SendClientMessage(playerid, COLOR_LIGHTBLUE, "���������� ������� ����� � ����� ������� �� ��� �������� �����.");
    }
    else
    {
		//SendClientMessage(playerid, COLOR_LIGHTBLUE, "������ ������� �������� ������ ������ �� �������� ����. ��������� � ��������������.");

		new response[30];
		if(response_code == HTTP_ERROR_BAD_HOST)
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        else if(response_code == 500)
		{
			strmid(response, "���������� ������ �������", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "%s[%d] �������� �� HTTP �������� ������ PasswordSendToMail: %s[%d]", PlayerName(playerid), playerid, response, response_code);
		Log(ERROR, strings);
    }
	TestLog(OPTIM, "HTTP_PasswordSendToMail", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}

forward HTTP_RememberPassword(playerid, response_code, data[]);
public HTTP_RememberPassword(playerid, response_code, data[])
{   //���������� ��� ������� ������ REMINDER
	new timers = GetTickCount();
    if(response_code == 200)
    {
    	new GotResult = strval(data);
		if(GotResult)
		{
			SetPVarInt(playerid, "PasswordHasEdited", getdate());
			//return SendClientMessage(playerid, COLOR_LIGHTBLUE, "����� � ������� ���� ������� ���������� �� ��� �������� �����!");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}���� ������ ���� ���������� �� ��� �������� ���� ��������� ��� �����������.");
			SendClientMessage(playerid, COLOR_RED, "��������� �������� ���� (� ������� ����)!");
		}
		else return SendClientMessage(playerid, COLOR_LIGHTBLUE, "���������� ������� ����� � ������� �� ��� �������� �����.");
    }
    else
    {
  		new response[40];
 		if(response_code == 404)
		{
//404 Not Found � ����� ���������������� ������ ��� ����������� ����������,
//�������� ������� � ������ � ��������� ������ Web-��������.
//������ ����� ������, �� �� ����� ���������������� ������� �� ���������� URI.
//���� ������� ��������, ��� �� ����� ������ ��� ��������, �� ��� ���������� ������������ ��� 410.
//����� 404 ����� �������������� ������ 403, ���� ��������� ��������� ������ �� ����������� ���� ����������� �������. �������� � HTTP/1.0.
			strmid(response, "������ � ��������� ������ Web-��������", 0, strlen("������ � ��������� ������ Web-��������"), sizeof(response));
        }
		//SendClientMessage(playerid, COLOR_LIGHTBLUE, "������ ������� �������� ������ �� �������� ����. ��������� � ��������������.");

/*
http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BA%D0%BE%D0%B4%D0%BE%D0%B2_%D1%81%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F_HTTP#500
#define HTTP_ERROR_BAD_HOST				1
#define HTTP_ERROR_NO_SOCKET			2
#define HTTP_ERROR_CANT_CONNECT			3
#define HTTP_ERROR_CANT_WRITE			4
#define HTTP_ERROR_CONTENT_TOO_BIG		5
#define HTTP_ERROR_MALFORMED_RESPONSE	6

    500 Internal Server Error � ����� ���������� ������ �������, ������� �� ������ � ����� ��������� ������ ������. �������� � HTTP/1.0.
    501 Not Implemented � ������ �� ������������ ������������, ����������� ��� ��������� �������. �������� ����� ��� �������, ����� ������ �� �������� ��������� � ������� �����. ���� �� ����� ������� ��������, �� �� �� �������� � ������� �������, �� ����� ������� ����� 405. �������� � HTTP/1.0.
    502 Bad Gateway � ������ � ���� ����� ��� ������-������� ������� ��������� � ��������� ���������� ������������� ��������. �������� � HTTP/1.0.
    503 Service Unavailable � ������ �������� �� ����� ����������� ������������ ������� �� ����������� �������� (������������, ���������� � ������). � ���� Retry-After ��������� ������ ����� ������� �����, ����� ������� ������� ������������� ��������� ������. ���� �� ����� ���������� ��������� ������� ����� ��������� ����������, ����������� ����� ��������� ��������� �������� �������� ���� Retry-After ��� ���������� ������� ���������� ��������. �������� � HTTP/1.0.
    504 Gateway Timeout � ������ � ���� ����� ��� ������-������� �� �������� ������ �� ������������ ������� ��� ���������� �������� �������. �������� � HTTP/1.1.
    505 HTTP Version Not Supported � ������ �� ������������ ��� ������������ ������������ ��������� � ������� ������ ��������� HTTP. �������� � HTTP/1.1.
    506 Variant Also Negotiates � � ���������� ��������� ������������ ��������� ������� ��������� ��� �� ����, ��-�� ���� ������� ���������� �����������. �����������������. ������� � RFC 2295 ��� ���������� ��������� HTTP ����������� Transparent Content Negotiation.
    507 Insufficient Storage � �� ������� ����� ��� ���������� �������� �������. �������� ����� ���� ���������. ������� � WebDAV.
    509 Bandwidth Limit Exceeded � ������������ ��� ���������� ���-��������� ���������� �� ����������� �� ����������� �������. � ������ ������ ��������� �������� ������� ���������� � ������ �������-����������. � ��������� ������ ������ ��� �� ������ �� � ����� RFC � ������������ ������ ������� �bw/limited�, �������� � ������ ���������� ��������� cPanel, ��� � ��� �����.
    510 Not Extended � �� ������� ����������� ����������, ������� ������ ������������ ������. ������ ����� ������������� �������� ���������� � ��������� ��� �����������. ������� � RFC 2774 ��� ���������� ��������� HTTP ���������� ����������.


*/
		if(response_code == HTTP_ERROR_BAD_HOST)
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        else if(response_code == 500)
		{
			strmid(response, "���������� ������ �������", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        
		//new strings[MAX_STRING];
        format(strings, sizeof(strings), "RememberPassword %s[%d]: %s[%d]", PlayerName(playerid), playerid, response, response_code);
        //SendAllAdminMessage(COLOR_MAROON, strings, 1);
        Log(ERROR, strings);
    }
	TestLog(OPTIM, "HTTP_RememberPassword", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}
