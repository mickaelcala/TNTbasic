#ifndef __MACH_R__    #include "MacTypes.r"    #include "Dialogs.r"    #include "Menus.r"#endifresource 'MBAR' (128) {	{	/* array MenuArray: 4 elements */		/* [1] */		128;		/* [2] */		129;		/* [3] */		130;		/* [4] */		131	}};resource 'MENU' (128) {	128,	textMenuProc,	allEnabled,	enabled,	apple,	{	/* array: 1 elements */		/* [1] */		"About NSpTest2…", noIcon, noKey, noMark, plain;	}};resource 'MENU' (129) {	129,	textMenuProc,	0x7FFFFFF7,	enabled,	"File",	{	/* array: 5 elements */		/* [1] */		"Host", noIcon, "H", noMark, plain;		/* [2] */		"Join", noIcon, "J", noMark, plain;		/* [3] */		"Leave", noIcon, "L", noMark, plain;		/* [4] */		"-", noIcon, noKey, noMark, plain;		/* [5] */		"Quit", noIcon, "Q", noMark, plain	}};resource 'MENU' (130) {	130,	textMenuProc,	0x7FFFFE00,	enabled,	"Edit",	{	/* array: 9 elements */		/* [1] */		"Undo", noIcon, "Z", noMark, plain;		/* [2] */		"-", noIcon, noKey, noMark, plain;		/* [3] */		"Cut", noIcon, "X", noMark, plain;		/* [4] */		"Copy", noIcon, "C", noMark, plain;		/* [5] */		"Paste", noIcon, "V", noMark, plain;		/* [6] */		"Clear", noIcon, noKey, noMark, plain;		/* [7] */		"Select All", noIcon, "A", noMark, plain;		/* [8] */		"-", noIcon, noKey, noMark, plain;		/* [9] */		"Preferences…", noIcon, noKey, noMark, plain	}};resource 'MENU' (131, "Client") {	131,	textMenuProc,	0x7FFDFBD7,	enabled,	"Client",	{	/* array: 19 elements */		/* [1] */		"Junk", noIcon, noKey, check, plain;		/* [2] */		"Normal", noIcon, noKey, check, plain;		/* [3] */		"Registered", noIcon, noKey, check, plain;		/* [4] */		"-", noIcon, noKey, noMark, plain;		/* [5] */		"Blocking", noIcon, noKey, check, plain;		/* [6] */		"-", noIcon, noKey, noMark, plain;		/* [7] */		"1x Per Second", noIcon, noKey, check, plain;		/* [8] */		"10x Per Second", noIcon, noKey, check, plain;		/* [9] */		"30x", noIcon, noKey, check, plain;		/* [10] */		"No Limit", noIcon, noKey, check, plain;		/* [11] */		"-", noIcon, noKey, noMark, plain;		/* [12] */		"4 bytes", noIcon, noKey, check, plain;		/* [13] */		"16 bytes", noIcon, noKey, check, plain;		/* [14] */		"400 bytes", noIcon, noKey, check, plain;		/* [15] */		"1K", noIcon, noKey, check, plain;		/* [16] */		"10K", noIcon, noKey, check, plain;		/* [17] */		"100K", noIcon, noKey, check, plain;		/* [18] */		"-", noIcon, noKey, noMark, plain;		/* [19] */		"Enumerate Players", noIcon, noKey, noMark, plain	}};resource 'MENU' (132, "Host") {	132,	textMenuProc,	0x7FFDFBD7,	enabled,	"Host",	{	/* array: 19 elements */		/* [1] */		"Junk", noIcon, noKey, check, plain;		/* [2] */		"Normal", noIcon, noKey, check, plain;		/* [3] */		"Registered", noIcon, noKey, check, plain;		/* [4] */		"-", noIcon, noKey, noMark, plain;		/* [5] */		"Blocking", noIcon, noKey, check, plain;		/* [6] */		"-", noIcon, noKey, noMark, plain;		/* [7] */		"1x Per Second", noIcon, noKey, check, plain;		/* [8] */		"10x Per Second", noIcon, noKey, check, plain;		/* [9] */		"30x", noIcon, noKey, check, plain;		/* [10] */		"No Limit", noIcon, noKey, check, plain;		/* [11] */		"-", noIcon, noKey, noMark, plain;		/* [12] */		"4 bytes", noIcon, noKey, check, plain;		/* [13] */		"16 bytes", noIcon, noKey, check, plain;		/* [14] */		"400 bytes", noIcon, noKey, check, plain;		/* [15] */		"1K", noIcon, noKey, check, plain;		/* [16] */		"10K", noIcon, noKey, check, plain;		/* [17] */		"100K", noIcon, noKey, check, plain;		/* [18] */		"-", noIcon, noKey, noMark, plain;		/* [19] */		"Enumerate Players", noIcon, noKey, noMark, plain	}};resource 'ALRT' (128, "About", purgeable) {	{40, 40, 150, 332},	128,	{	/* array: 4 elements */		/* [1] */		OK, visible, silent;		/* [2] */		OK, visible, silent;		/* [3] */		OK, visible, silent;		/* [4] */		OK, visible, silent	},	alertPositionMainScreen};resource 'DITL' (128) {	{	/* array DITLarray: 3 elements */		/* [1] */		{77, 216, 97, 274},		Button {			enabled,			"OK"		};		/* [2] */		{13, 58, 44, 281},		StaticText {			disabled,			"NetSprocket Test Applicsation #2."		}	}};resource 'DLOG' (129, "Error", purgeable) {	{0, 0, 193, 339},	dBoxProc,	invisible,	noGoAway,	0x0,	129,	"",	centerParentWindowScreen};resource 'DITL' (129, purgeable) {	{	/* array DITLarray: 8 elements */		/* [1] */		{160, 197, 180, 255},		Button {			enabled,			"Fatal"		};		/* [2] */		{160, 268, 180, 326},		Button {			enabled,			"Ok"		};		/* [3] */		{13, 23, 45, 55},		Icon {			disabled,			2		};		/* [4] */		{14, 88, 44, 295},		StaticText {			disabled,			"An error has occurred!\nError#: ^0"		};		/* [5] */		{61, 35, 79, 144},		StaticText {			disabled,			"Error message : "		};		/* [6] */		{78, 33, 139, 315},		StaticText {			disabled,			"^1"		};		/* [7] */		{11, 78, 48, 326},		UserItem {			disabled		};		/* [8] */		{69, 23, 147, 326},		UserItem {			disabled		}	}};resource 'STR ' (128, purgeable) {	"Message unavailable!!"};resource 'STR ' (129, purgeable) {	"Bus error !!"};resource 'STR ' (130, purgeable) {	"Address error!!"};resource 'STR ' (135, purgeable) {	"Priveledge violation error!!"};resource 'STR ' (139, purgeable) {	"Misc. hardware error!!"};resource 'STR ' (142, purgeable) {	"I/O core error!!"};resource 'STR ' (153, purgeable) {	"Out of memory!!"};resource 'STR ' (154, purgeable) {	"Can't launch file error!!"};resource 'STR ' (155, purgeable) {	"System is trashed!!"};resource 'STR ' (230, purgeable) {	"System too old for ROM error!!"};resource 'STR ' (361, purgeable) {	"Directory full error!!"};resource 'STR ' (362, purgeable) {	"Disk full error!!"};resource 'STR ' (364, purgeable) {	"I/O error!!"};resource 'STR ' (365, purgeable) {	"Bad file name error!!"};resource 'STR ' (369, purgeable) {	"Out of memory (file too big) error!!"};resource 'STR ' (372, purgeable) {	"Volume is locked error!!"};resource 'STR ' (373, purgeable) {	"File is locked error!!"};resource 'STR ' (436, purgeable) {	"File too large error!!"};resource 'STR ' (929, purgeable) {	"Not enough memory to Application."};resource 'STR ' (4429, purgeable) {	"Printer not found!!"};resource 'STR ' (377, purgeable) {	"File in use!! "};resource 'STR ' (371, purgeable) {	"Target not Found."};resource 'WIND' (128) {	{109, 115, 250, 388},	noGrowDocProc,	visible,	goAway,	0x0,	"",	noAutoCenter};resource 'vers' (1, purgeable) {	0x2,	0x0,	release,	0x0,	0,	"© Apple",	"© Apple Computer, Inc. 1992-2002"};