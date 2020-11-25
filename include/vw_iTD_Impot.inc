#include <a_samp>

//#define ShowPlayerDialogEx(%0,%1,%2) ShowPlayerDialog(%0, %1, %2);
//#define ShowPlayerDialog(%0,%1,%2) ShowPlayerDialogEx(%0, %1, %2);
//==============================================================================
#define Project_Prefix			"iTD/Projects/"
#define ITD                     "{62E300}iTD: {FFFFFF}"
#define ITD_E                   "{62E300}iTD: {FF0000}(Ошибка) {FFFFFF}"
#define ITD_W                   "{62E300}iTD: {FFB429}(Предупреждение) {FFFFFF}"
#define ITD_I                   "{62E300}iTD: {00FF00}(Информация) {FFFFFF}"
#define INVALID_INDEX_ID        (-1)
#define MAX_PROJECT_TEXTDRAWS   (120)
#define MAX_UNDO_STATES         (1000)

#define Send(%0,%1,%2)          SendClientMessage(%0, %1, %2)
#define LoopProjectTextdraws    for (new i = 0; i < MAX_PROJECT_TEXTDRAWS; i++)
#define CountRange(%0,%1)       for (new c = %0; c < %1; c++)
#define EmptyString(%0)         %0[0] = '\0'
//#define iShowPlayerDialog       DialogShown = true, ShowPlayerDialog

enum E_TD_STRUCT
{
	Text:iTextdraw,
	iText[256+1],
	Float:iPositionX,
	Float:iPositionY,
	Float:iLetterX,
	Float:iLetterY,
	Float:iTextX,
	Float:iTextY,
	iAlignment,
	iColor,
	iVehCol1,
	iVehCol2,
	iUsebox,
	iBoxcolor,
	iShadow,
	iOutline,
	iBackgroundcolor,
	iFont,
	iPreviewModel,
	iModelID,
	Float:iMRotX,
	Float:iMRotY,
	Float:iMRotZ,
	Float:iMZoom,
	iProportion,
	iSelectable,
	iType
};
new	Project[MAX_PROJECT_TEXTDRAWS][E_TD_STRUCT];

/*enum E_KEY_STRUCT
{
	bool:KEY_PRESSED,
	KEY_CODE,
};
new VirtualKeys[36][E_KEY_STRUCT];*/

new
	//Float:OffsetZ = 415.0,
	//Text:TD_Menu[34] = {Text:INVALID_TEXT_DRAW, ...},
	//Text:TD_MenuPM[2] = {Text:INVALID_TEXT_DRAW, ...},

	File:Handler,
	ProjectEditor,
	ProjectFile[64] = "iphone.itd",
	//Font5Edit[MAX_PLAYERS],

	//bool:DialogShown,
	//bool:MenuShown,
	//bool:MenuHidden,
	//bool:EditEnabled,
	//Float:EditSpeed = 1.0,

	//EditMode,
	//EditIndex,
	//ColorMode,
	//Colors[4],

	//String_Large[3584],
	String_Textdraw[512],
	String_Message[128],
	//String_Normal[96],

	States[MAX_UNDO_STATES][sizeof String_Textdraw]

	//UpdateTimer
	//CursorOX, CursorOY,
	//CursorX, CursorY,
	//ScreenWidth, ScreenHeight
;
/*enum
{
	EDITMODE_NONE,
	EDITMODE_TEXTDRAW,
	EDITMODE_USEBOX,
	EDITMODE_TEXTUREBOX,
	EDITMODE_TEXTUREBOX2,
	EDITMODE_TEXTUREBOX3,
	EDITMODE_TEXTUREBOX4,
	EDITMODE_TEXTUREBOX5,
	EDITMODE_TEXTUREBOX6,
	EDITMODE_TEXTUREBOX7,
	EDITMODE_TEXTUREBOX8,
	EDITMODE_TEXTUREBOX9,
	EDITMODE_TEXTUREBOX10,
	EDITMODE_POSITION,
	EDITMODE_SIZE,
	EDITMODE_LETTERSIZE,
	EDITMODE_COLOR,
	EDITMODE_BGCOLOR,
	EDITMODE_BOXCOLOR,
	EDITMODE_OUTLINE,
	EDITMODE_SHADOW,
	EDITMODE_PROPORTION,
	EDITMODE_SELECTABLE,
	EDITMODE_FONT,
	EDITMODE_ALIGNMENT,
	EDITMODE_BOX,
	EDITMODE_TYPE,
	EDITMODE_FONT5,
	EDITMODE_REMOVE
};*/
/*enum
{
	COLORMODE_NONE,
	COLORMODE_RED,
	COLORMODE_GREEN,
	COLORMODE_BLUE,
	COLORMODE_ALPHA
};*/

//==============================================================================
new TEXT_DRAWS_COUNTER = -1;
forward Text:iTD_TextDrawCreate(Float:x, Float:y, text[]);
public Text:iTD_TextDrawCreate(Float:x, Float:y, text[])
{
	TEXT_DRAWS_COUNTER ++;
	new i = TEXT_DRAWS_COUNTER;
	format(Project[i][iText], 256+1, "%s", text);
	Project[i][iPositionX] = x,	Project[i][iPositionY] = y;
	Project[i][iType] = 0;
	return TextDrawCreate(x, y, text);
}
/*
	#if defined TextDrawCreateEx
		return TextDrawCreate(x, y, text);
	#endif
}

#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif
#define TextDrawCreate TextDrawCreateEx
#if defined TextDrawCreateEx
	forward Text:TextDrawCreate(Float:x, Float:y, text[]);
#endif
*/


stock iTD_TextDrawLetterSize(Text:text, Float:x, Float:y)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iLetterX] = x, 	Project[i][iLetterY] = y;
	TextDrawLetterSize(text, x, y);
}
stock iTD_TextDrawTextSize(Text:text, Float:x, Float:y)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iTextX] = x,		Project[i][iTextY] = y;
	TextDrawTextSize(text, x, y);
}
stock iTD_TextDrawAlignment(Text:text, alignment)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iAlignment] = alignment;
	TextDrawAlignment(text, alignment);
}
stock iTD_TextDrawColor(Text:text, color)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iColor] = color;
	TextDrawColor(text, color);
}
stock iTD_TextDrawUseBox(Text:text, use)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iUsebox] = use;
	TextDrawUseBox(text, use);
}
stock iTD_TextDrawBoxColor(Text:text, color)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iBoxcolor] = color;
	TextDrawBoxColor(text, color);
}
stock iTD_TextDrawSetShadow(Text:text, size)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iShadow] = size;
	TextDrawSetShadow(text, size);
}
stock iTD_TextDrawSetOutline(Text:text, size)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iOutline] = size;
	TextDrawSetOutline(text, size);
}
stock iTD_TextDrawBackgroundColor(Text:text, color)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iBackgroundcolor] = color;
	TextDrawBackgroundColor(text, color);
}
stock iTD_TextDrawFont(Text:text, font)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iFont] = font;
	TextDrawFont(text, font);
}
stock iTD_TextDrawSetSelectable(Text:text, set)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iSelectable] = set;
	TextDrawSetSelectable(text, set);
}

//==============================================================================
//new PLAYER_TEXT_DRAWS_COUNTER[MAX_PLAYERS] = -1;
forward PlayerText:iTD_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[]);
public PlayerText:iTD_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[])
{
	TEXT_DRAWS_COUNTER ++;//PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;
	new i = TEXT_DRAWS_COUNTER;
	format(Project[i][iText], 256+1, "%s", text);
	Project[i][iPositionX] = x,	Project[i][iPositionY] = y;
	Project[i][iType] = 1;
	return CreatePlayerTextDraw(playerid, x, y, text);
}
stock iTD_PlayerTextDrawLetterSize(playerid, PlayerText:text, Float:x, Float:y)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iLetterX] = x, 	Project[i][iLetterY] = y;
	PlayerTextDrawLetterSize(playerid, text, x, y);
}
stock iTD_PlayerTextDrawTextSize(playerid, PlayerText:text, Float:x, Float:y)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iTextX] = x,		Project[i][iTextY] = y;
	PlayerTextDrawTextSize(playerid, text, x, y);
}
stock iTD_PlayerTextDrawAlignment(playerid, PlayerText:text, alignment)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iAlignment] = alignment;
	PlayerTextDrawAlignment(playerid, text, alignment);
}
stock iTD_PlayerTextDrawColor(playerid, PlayerText:text, color)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iColor] = color;
	PlayerTextDrawColor(playerid, text, color);
}
stock iTD_PlayerTextDrawUseBox(playerid, PlayerText:text, use)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iUsebox] = use;
	PlayerTextDrawUseBox(playerid, text, use);
}
stock iTD_PlayerTextDrawBoxColor(playerid, PlayerText:text, color)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iBoxcolor] = color;
	PlayerTextDrawBoxColor(playerid, text, color);
}
stock iTD_PlayerTextDrawSetShadow(playerid, PlayerText:text, size)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iShadow] = size;
	PlayerTextDrawSetShadow(playerid, text, size);
}
stock iTD_PlayerTextDrawSetOutline(playerid, PlayerText:text, size)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iOutline] = size;
	PlayerTextDrawSetOutline(playerid, text, size);
}
stock iTD_PlayerTextDrawBackgroundCol(playerid, PlayerText:text, color)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iBackgroundcolor] = color;
	PlayerTextDrawBackgroundColor(playerid, text, color);
}
stock iTD_PlayerTextDrawFont(playerid, PlayerText:text, font)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iFont] = font;
	PlayerTextDrawFont(playerid, text, font);
}
stock iTD_PlayerTextDrawSetSelectable(playerid, PlayerText:text, set)
{
	new i = TEXT_DRAWS_COUNTER;
	Project[i][iSelectable] = set;
	PlayerTextDrawSetSelectable(playerid, text, set);
}

//==============================================================================
stock SaveProject(bool:response = false)
{
	if(!strlen(ProjectFile)) return Send(ProjectEditor, -1, #ITD_E"Никакой проект не открыт, чтобы сохранить его");
//print("SaveProject: iTD/Projects/"#ProjectFile);
//print(ProjectFile);
	new path[16+64];
	strcat(path, Project_Prefix);
	strcat(path, ProjectFile);
    //if(fexist(path)) fremove(path);

	Handler = fopen(path, io_write);
    //if(!Handler) return Send(ProjectEditor, -1, #ITD_E"Произошла ошибка при сохранении файла (.iTD)");
    if(!Handler) return print(#ITD_E"Произошла ошибка при сохранении файла (.iTD)");

    LoopProjectTextdraws//for (new i = 0; i < MAX_PROJECT_TEXTDRAWS; i++)
	{
	    //if(Project[i][iTextdraw] == Text:INVALID_TEXT_DRAW) continue;

	    format(String_Textdraw, sizeof String_Textdraw,
		"%f|%f|%f|%f|%f|%f|%f|%f|%f|%f|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%s\r\n",
	    Project[i][iPositionX], 		Project[i][iPositionY],
		Project[i][iLetterX], 			Project[i][iLetterY],
		Project[i][iTextX], 			Project[i][iTextY],
		Project[i][iMRotX], 			Project[i][iMRotY],
		Project[i][iMRotZ] ,			Project[i][iMZoom],
		Project[i][iModelID],
		Project[i][iAlignment], 		Project[i][iColor],
		Project[i][iUsebox], 			Project[i][iBoxcolor],
		Project[i][iShadow], 			Project[i][iOutline],
		Project[i][iBackgroundcolor], 	Project[i][iFont],
		Project[i][iProportion], 		Project[i][iSelectable],
		Project[i][iType], 				Project[i][iText]);//RusToGame(Project[i][iText]));//Project[i][iText]);
		//fwrite(Handler, String_Textdraw);
	    for(new c=0; c<strlen(String_Textdraw); c++)
		{   //записывам от нулевого символа до конца строки
	        fputchar(Handler, String_Textdraw[c], false);
	    }
	}
    fclose(Handler);

	if(response)
	{
	    format(String_Message, 128, "%s Проект: '%s' сохранен!", ITD, ProjectFile);
	    Send(ProjectEditor, -1, String_Message);
	    print(String_Message);
	}
	return true;
}


stock CloseProject(bool:response = false)
{
    if(!strlen(ProjectFile)) return Send(ProjectEditor, -1, #ITD_E"Вы не открывали проект, по-этому закрыть не возможно!");

    SaveProject();
    LoopProjectTextdraws RemoveTextDraw(i);

    if(response)
	{
	    format(String_Message, 128, "%s Проект: '%s' закрыт!", ITD, ProjectFile);
	    Send(ProjectEditor, -1, String_Message);
	}

	//EditIndex = INVALID_INDEX_ID;
	//EditMode = EDITMODE_NONE;
	//ColorMode = COLORMODE_NONE;
	EmptyString(ProjectFile);
	CountRange(0, sizeof States) EmptyString(States[c]);
	//ShowEditor();
    return true;
}

stock RemoveTextDraw(Index)
{
    if(!(0 <= Index < sizeof Project)) return;

	//TextDrawDestroy(Project[Index][iTextdraw]);
	format(Project[Index][iText], 256, " ");
	Project[Index][iTextdraw] = Text:INVALID_TEXT_DRAW;
	Project[Index][iLetterX] = 0.0;
	Project[Index][iLetterY] = 0.0;
	Project[Index][iTextX] = 0.0;
	Project[Index][iTextY] = 0.0;
	Project[Index][iAlignment] = 1;
	Project[Index][iColor] = 0;
	Project[Index][iUsebox] = 0;
	Project[Index][iBoxcolor] = 0;
	Project[Index][iShadow] = 0;
	Project[Index][iOutline] = 0;
	Project[Index][iBackgroundcolor] = 0;
	Project[Index][iFont] = 0;
	Project[Index][iProportion] = 1;
	Project[Index][iSelectable] = 0;

	/*if(EditIndex == Index)
	{
	    EditMode = EDITMODE_NONE;
	    EditIndex = INVALID_INDEX_ID;
	}*/
}
