/*
	SA-MP MySQL plugin R5
	Copyright (c) 2008-2010, G-sTyLeZzZ 
*/

#if defined mysql_included
	#endinput
#endif
#define mysql_included

//Common error codes (http://dev.mysql.com/doc/refman/5.0/en/error-messages-(client|server).html)

#define ER_DBACCESS_DENIED_ERROR 1044
#define ER_ACCESS_DENIED_ERROR 1045
#define ER_UNKNOWN_TABLE 1109
#define ER_SYNTAX_ERROR 1149
#define CR_SERVER_GONE_ERROR 2006
#define CR_SERVER_LOST 2013
#define CR_COMMAND_OUT_OF_SYNC 2014
#define CR_SERVER_LOST_EXTENDED 2055

//Native functions

#define mysql_fetch_row(%1) mysql_fetch_row_format(%1,"|")
#define mysql_next_row() mysql_retrieve_row()
#define mysql_get_field(%1,%2) mysql_fetch_field_row(%2,%1)

native mysql_connect(const host[],const user[],const database[],const password[]);//DB:db_open(name[]);
native mysql_close(connectionHandle = 1);//db_close(DB:db);
native mysql_query(query[],resultid = (-1),extraid = (-1),connectionHandle = 1);//DBResult:db_query(DB:db, query[]);//������ ������
native mysql_num_rows(connectionHandle = 1);//db_num_rows(DBResult:dbresult);

//�� ������������
native mysql_num_fields(connectionHandle = 1);//���������� ���������� �������� � �������������� ������.
//db_num_fields(DBResult:dbresult); //��������� ������ ���������� ����� ���������� �������.


native mysql_fetch_row_format(string[],const delimiter[] = "|",connectionHandle = 1);//�-�� ���������� ������ ��������� �� ����������� "|"//������� ������ ��� ��������� ������ ������ �� ���������� �������
native mysql_retrieve_row(connectionHandle = 1);//�������� ������, � ���� ������ ��� - ��� ����, ������ ��� �������� �� ��������� ����� //����������� ��� ������� ��� ����������� ����������� ��������� ������ �� ��������� ������.
//�� ����� �� � �������� ������� ��� ������� mysql_next_row (). ��� ������� ����� �������, ����� �� ��������� ������������ mysql_fetch_field() ��� mysql_fetch_field_row() �����, ������� ��� �� ����� ��������� ���� ��������� � Pawno.
//db_next_row(DBResult:dbresult);//��������� � ��������� ������ ����������, ����������� �� db_query. ������: while(db_next_row(db_result));


native mysql_fetch_field_row(string[],const fieldname[],connectionHandle = 1);//����������� ��� ������� ��� ��������� ������ � ���� string, ������������ �� ��� ����� fieldname. //�������� ������ �� ���������� ������� fieldname � ���������� � string
//db_get_field_assoc(DBResult:dbresult, const field[], result[], maxlength);//��������� ������ ���������� ���� � ���� ������ ������ � ��������� ������ field � ���������� � ��������� ���������� result
//db_get_field_assoc_int(DBResult:result, const field[]);//�������� ���������� ���� � ���� ������ ����� � ��������� ������ field
//db_get_field_assoc_float(DBResult:result, const field[]);//�������� ���������� ���� � ���� ������������� ����� � ��������� ������ field


native mysql_free_result(connectionHandle = 1);//db_free_result(DBResult:dbresult);//������� ������������ ��� ������� ���������� ����� ������������� mysql_store_result ��� ����� ������� SELECT
native mysql_insert_id(connectionHandle = 1);//���������� ������ ������ ��������� � ���� ����� ������� INSERT


//------------------------------------------------------------------------------
//�� ������������ � SQLite
native mysql_store_result(connectionHandle = 1);////�������� ��������� //��������� ��������� � �����. ������ ���������� ������� //������ ������� �� mysql_query ���� ������ SELECT
native mysql_affected_rows(connectionHandle = 1);
native mysql_debug(enable = 1);
native mysql_errno(connectionHandle = 1);

//db_field_name(DBResult:dbresult, field, result[], maxlength);//�������� �������� ���� �� ��� �������, �.�. ������ �������
native mysql_fetch_field(number,dest[],connectionHandle = 1);//����������� ��� �������, ����� �������� ��� ����������� ���� �� ������ number, ������� ��������� � dest

native mysql_fetch_int(connectionHandle = 1);//����������� ��� ������� ��� ���������� ������!!! ������ ����� (�������������� �����) �� ��������������� ������.
native mysql_fetch_float(&Float:result,connectionHandle = 1);//����������� ��� ������� ��� ���������� ������!!! �������� � ��������� ������ �� ��������������� ������.
/*mysql_query("SELECT health FROM players LIMIT 1");mysql_store_result();
new Float:health;
mysql_fetch_float(health);
mysql_free_result();*/

native mysql_field_count(connectionHandle = 1);//����������� ��� �������, ����� �������� ���������� �������� ��� ������ ���������� ������� �� ����������.

native mysql_set_charset(charset[],connectionHandle = 1);
native mysql_get_charset(destination[],connectionHandle = 1);
native mysql_ping(connectionHandle = 1);
native mysql_real_escape_string(const source[],destination[],connectionHandle = 1);
native mysql_query_callback(index,query[],callback[],extraid = (-1),connectionHandle = 1);
native mysql_reconnect(connectionHandle = 1);
native mysql_reload(connectionHandle = 1);
native mysql_stat(const destination[],connectionHandle = 1);
native mysql_warning_count(connectionHandle = 1);

//forward declarations

forward OnQueryFinish(query[], resultid, extraid, connectionHandle);
forward OnQueryError(errorid, error[], resultid, extraid, callback[], query[], connectionHandle);
/*------------------------------------------------------------------------------
//�� ������������ � mysql
//db_get_field(DBResult:dbresult, field, result[], maxlength);//��������� ������ ���������� ���� � ���� ������ ������ �� ��� ����������� ������ field.
//db_get_field_int(DBResult:result, field = 0);//��������� ������ ���������� ���� � ���� ������ ����� �� ��� ����������� ������ field.
//Float:db_get_field_float(DBResult:result, field = 0);//��������� ������ ���������� ���� � ���� ������������� ����� �� ��� ����������� ������ field.

native db_get_mem_handle(DB:db);
native db_get_result_mem_handle(DBResult:result);

native db_debug_openfiles();
native db_debug_openresults();

#define MAX_INI_ENTRY_TEXT 80
stock DB_Escape(text[])
{
	new	ret[MAX_INI_ENTRY_TEXT * 2], ch, i,	j;
	while ((ch = text[i++]) && j < sizeof (ret))
	{
		if (ch == '\'')
		{
			if (j < sizeof (ret) - 2)
			{
				ret[j++] = '\'';
				ret[j++] = '\'';
			}
		}
		else if (j < sizeof (ret)) ret[j++] = ch;
		else j++;
	}
	ret[sizeof (ret) - 1] = '\0';
	return ret;
}*/
