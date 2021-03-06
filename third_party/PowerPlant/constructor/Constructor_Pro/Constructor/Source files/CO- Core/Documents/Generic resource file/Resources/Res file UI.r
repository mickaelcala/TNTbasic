data 'Txtr' (15000, "Geneva 9") {
	$"0009 0000 0000 0001 0000 0000 0000 0003"            /* .?.............. */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (15002, "Geneva 9 (right)") {
	$"0009 0000 FFFF 0001 0000 0000 0000 0003"            /* .?..??.......... */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (15001, "Geneva 9 (bold)") {
	$"0009 0001 0000 0001 0000 0000 0000 0003"            /* .?.............. */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'Txtr' (15003, "Geneva 9 (bold, right)") {
	$"0009 0001 FFFF 0001 0000 0000 0000 0003"            /* .?..??.......... */
	$"0647 656E 6576 61"                                  /* .Geneva */
};

data 'WIND' (15000, "Project window", purgeable) {
	$"002A 0004 0130 0149 0008 0000 01FF 0000"            /* .*...0.I.....?.. */
	$"0000 0E50 726F 6A65 6374 2057 696E 646F"            /* ...Project Windo */
	$"7700 0000"                                          /* w... */
};

data 'WIND' (15050, "Save before closing", purgeable) {
	$"0028 0010 0093 017C 0001 0000 0000 0000"            /* .(...?.|........ */
	$"0000 1244 6F63 756D 656E 7420 4E6F 7420"            /* ...Document Not  */
	$"5361 7665 6400 300A"                                /* Saved.0? */
};

data 'WIND' (15080, "Duplicate resource ID") {
	$"0028 0010 010D 0175 0001 0000 0000 0000"            /* .(.....u........ */
	$"0000 1752 6573 6F75 7263 6520 416C 7265"            /* ...Resource Alre */
	$"6164 7920 4578 6973 7473 300A"                      /* ady Exists0? */
};

data 'WIND' (15300, "New resource") {
	$"0028 0010 00B3 0152 0005 0000 0000 0000"            /* .(...?.R........ */
	$"0000 1343 7265 6174 6520 4E65 7720 5265"            /* ...Create New Re */
	$"736F 7572 6365 300A"                                /* source0? */
};

data 'PPob' (15050, "Save before closing", purgeable) {
	$"0002 646F 706C 646C 6F67 6F62 6A64 0000"            /* ..dopldlogobjd.. */
	$"0024 6764 6C67 3ACA 0000 0062 0000 0040"            /* .$gdlg:?...b...@ */
	$"0040 FFFF FFFF FFFF FFFF 0000 0000 5341"            /* .@????????....SA */
	$"5645 434E 434C 6265 6773 6F62 6A64 0000"            /* VECNCLbegsobjd.. */
	$"0012 7774 6861 FFFF FFFE 0101 0001 0002"            /* ..wtha????...... */
	$"0001 0002 6F62 6A64 0000 0039 6963 746C"            /* ....objd...9ictl */
	$"0000 0000 0020 0020 0101 0000 0000 0000"            /* ..... . ........ */
	$"0017 0000 000D 0000 0000 FFFF FFFF 0000"            /* ..........????.. */
	$"0000 0000 0002 0000 0000 0000 0000 0143"            /* ...............C */
	$"0000 0000 056F 626A 6400 0000 7373 7478"            /* .....objd...sstx */
	$"744D 5347 2001 1100 3001 0100 0000 0000"            /* tMSG ...0....... */
	$"0000 4E00 0000 0900 0000 00FF FFFF FF00"            /* ..N...?....????. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 003C 5361 7665 2063 6861 6E67 6573"            /*  ..<Save changes */
	$"2074 6F20 7468 6520 436F 6E73 7472 7563"            /*  to the Construc */
	$"746F 7220 646F 6375 6D65 6E74 20D2 2AD3"            /* tor document ?*? */
	$"2062 6566 6F72 6520 636C 6F73 696E 673F"            /*  before closing? */
	$"6F62 6A64 0000 0042 7075 7368 444F 4E54"            /* objd...BpushDONT */
	$"005A 0014 0101 0000 0000 0000 004E 0000"            /* .Z...........N.. */
	$"004A 0000 0000 FFFF FFFF 0000 03E7 0000"            /* .J....????...?.. */
	$"0000 0000 0000 0000 0000 0170 0000 0A44"            /* ...........p..?D */
	$"6F6E D574 2053 6176 6500 6F62 6A64 0000"            /* on?t Save.objd.. */
	$"003E 7075 7368 434E 434C 0044 0014 0101"            /* .>pushCNCL.D.... */
	$"0000 0000 0000 00CB 0000 004A 0000 0000"            /* .......?...J.... */
	$"FFFF FFFF 0000 0385 0000 0000 0000 0000"            /* ????...?........ */
	$"0000 0000 0170 0000 0643 616E 6365 6C00"            /* .....p...Cancel. */
	$"6F62 6A64 0000 003C 7075 7368 5341 5645"            /* objd...<pushSAVE */
	$"0044 0014 0101 0000 0000 0000 011D 0000"            /* .D.............. */
	$"004A 0000 0000 FFFF FFFF 0000 0384 0000"            /* .J....????...?.. */
	$"0000 0000 0000 0000 0000 0170 0000 0453"            /* ...........p...S */
	$"6176 6501 656E 6473 656E 642E"                      /* ave.endsend. */
};

data 'PPob' (15080, "Duplicate resource ID") {
	$"0002 646F 706C 646C 6F67 6F62 6A64 0000"            /* ..dopldlogobjd.. */
	$"0024 6764 6C67 3AE8 0000 0062 0000 0040"            /* .$gdlg:?...b...@ */
	$"0040 FFFF FFFF FFFF FFFF 0000 0000 554E"            /* .@????????....UN */
	$"4951 434E 434C 6265 6773 6F62 6A64 0000"            /* IQCNCLbegsobjd.. */
	$"0012 7774 6861 FFFF FFFE 0101 0001 0002"            /* ..wtha????...... */
	$"0001 0002 6F62 6A64 0000 0004 7461 6267"            /* ....objd....tabg */
	$"6265 6773 6F62 6A64 0000 0039 6963 746C"            /* begsobjd...9ictl */
	$"0000 0000 0020 0020 0101 0000 0000 0000"            /* ..... . ........ */
	$"0017 0000 000D 0000 0000 FFFF FFFF 0000"            /* ..........????.. */
	$"0000 0000 0000 0000 0000 0000 0000 0143"            /* ...............C */
	$"0000 0000 056F 626A 6400 0000 6773 7478"            /* .....objd...gstx */
	$"7400 0000 0000 FD00 2001 0100 0000 0000"            /* t.....?. ....... */
	$"0000 4400 0000 0900 0000 00FF FFFF FF00"            /* ..D...?....????. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"2000 0030 4120 7265 736F 7572 6365 2077"            /*  ..0A resource w */
	$"6974 6820 7468 6973 2074 7970 6520 616E"            /* ith this type an */
	$"6420 4944 2061 6C72 6561 6479 2065 7869"            /* d ID already exi */
	$"7374 732E 6F62 6A64 0000 0049 7374 7874"            /* sts.objd...Istxt */
	$"0000 0000 0068 000C 0101 0000 0000 0000"            /* .....h.......... */
	$"0044 0000 0036 0000 0000 FFFF FFFF 0000"            /* .D...6....????.. */
	$"0000 0000 0000 0000 0000 0000 0000 0120"            /* ...............  */
	$"3A99 1245 7869 7374 696E 6720 5265 736F"            /* :?.Existing Reso */
	$"7572 6365 3A6F 626A 6400 0000 4F73 7478"            /* urce:objd...Ostx */
	$"7452 5352 4300 A400 2001 0100 0000 0000"            /* tRSRC.?. ....... */
	$"0000 B000 0000 3600 0000 00FF FFFF FF00"            /* ..?...6....????. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"203A 9818 5050 6F62 2031 3238 2C20 D253"            /*  :?.PPob 128, ?S */
	$"616D 706C 6520 5469 746C 65D3 6F62 6A64"            /* ample Title?objd */
	$"0000 0037 7365 706C 0000 0000 0114 0003"            /* ...7sepl........ */
	$"0101 0101 0100 0000 0044 0000 0058 0000"            /* .........D...X.. */
	$"0000 FFFF FFFF 0000 0000 0000 0000 0000"            /* ..????.......... */
	$"0000 0000 0000 0090 0000 006F 626A 6400"            /* .......?...objd. */
	$"0000 4673 7478 7400 0000 0000 7C00 1001"            /* ..Fstxt.....|... */
	$"0100 0000 0000 0000 4400 0000 6400 0000"            /* ........D...d... */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .????........... */
	$"0000 0000 0001 2000 000F 446F 2079 6F75"            /* ...... ...Do you */
	$"2077 616E 7420 746F C96F 626A 6400 0000"            /*  want to?objd... */
	$"4170 7573 6855 4E49 5100 5400 1401 0100"            /* ApushUNIQ.T..... */
	$"0000 0000 0000 4400 0000 8200 0000 00FF"            /* ......D...?....? */
	$"FFFF FF55 4E49 5100 0000 0000 0000 0000"            /* ???UNIQ......... */
	$"0000 0001 7000 0009 556E 6971 7565 2049"            /* ....p..?Unique I */
	$"4401 6F62 6A64 0000 003F 7075 7368 5245"            /* D.objd...?pushRE */
	$"504C 0054 0014 0101 0000 0000 0000 0044"            /* PL.T...........D */
	$"0000 00A2 0000 0000 FFFF FFFF 5245 504C"            /* ...?....????REPL */
	$"0000 0000 0000 0000 0000 0000 0170 0000"            /* .............p.. */
	$"0752 6570 6C61 6365 006F 626A 6400 0000"            /* .Replace.objd... */
	$"3E70 7573 6843 4E43 4C00 5400 1401 0100"            /* >pushCNCL.T..... */
	$"0000 0000 0000 4400 0000 C200 0000 00FF"            /* ......D...?....? */
	$"FFFF FF00 0003 8500 0000 0000 0000 0000"            /* ???...?......... */
	$"0000 0001 7000 0006 4361 6E63 656C 006F"            /* ....p...Cancel.o */
	$"626A 6400 0000 8273 7478 7400 0000 0000"            /* bjd...?stxt..... */
	$"B400 1901 0100 0000 0000 0000 A600 0000"            /* ?...........?... */
	$"7F00 0000 00FF FFFF FF00 0000 0000 0000"            /* .....????....... */
	$"0000 0000 0000 0000 0001 203A 984B 4173"            /* .......... :?KAs */
	$"7369 676E 2061 2075 6E69 7175 6520 4944"            /* sign a unique ID */
	$"2074 6F20 7468 6520 6E65 7720 7265 736F"            /*  to the new reso */
	$"7572 6365 2E20 4C65 6176 6520 6578 6973"            /* urce. Leave exis */
	$"7469 6E67 2072 6573 6F75 7263 6573 2075"            /* ting resources u */
	$"6E74 6F75 6368 6564 2E6F 626A 6400 0000"            /* ntouched.objd... */
	$"7973 7478 7400 0000 0000 B400 1901 0100"            /* ystxt.....?..... */
	$"0000 0000 0000 A600 0000 A000 0000 00FF"            /* ......?...?....? */
	$"FFFF FF00 0000 0000 0000 0000 0000 0000"            /* ???............. */
	$"0000 0001 203A 9842 4465 6C65 7465 2074"            /* .... :?BDelete t */
	$"6865 2065 7869 7374 696E 6720 7265 736F"            /* he existing reso */
	$"7572 6365 2061 6E64 2072 6570 6C61 6365"            /* urce and replace */
	$"2069 7420 7769 7468 2074 6865 206E 6577"            /*  it with the new */
	$"2072 6573 6F75 7263 652E 6F62 6A64 0000"            /*  resource.objd.. */
	$"0064 7374 7874 0000 0000 00B4 0019 0101"            /* .dstxt.....?.... */
	$"0000 0000 0000 00A6 0000 00BF 0000 0000"            /* .......?...?.... */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ????............ */
	$"0000 0000 0120 3A98 2D4C 6561 7665 2074"            /* ..... :?-Leave t */
	$"6865 2072 6573 6F75 7263 6520 4944 7320"            /* he resource IDs  */
	$"6173 2074 6865 7920 6172 6520 6375 7272"            /* as they are curr */
	$"656E 746C 792E 656E 6473 656E 6473 656E"            /* ently.endsendsen */
	$"642E"                                               /* d. */
};

data 'PPob' (15000, "Project window", purgeable) {
	$"0002 6F62 6A64 0000 001C 7769 6E64 3A98"            /* ..objd....wind:? */
	$"0002 1F76 0000 0145 0064 0145 FFFF 0145"            /* ...v...E.d.E??.E */
	$"FFFF 0000 0000 6265 6773 6F62 6A64 0000"            /* ??....begsobjd.. */
	$"0012 7774 6861 FFFF FFFE 0101 000F 000F"            /* ..wtha????...... */
	$"0000 0000 6F62 6A64 0000 0012 7770 6F73"            /* ....objd....wpos */
	$"FFFF FFFE 0101 3A98 0096 0008 0100 6F62"            /* ????..:?.?....ob */
	$"6A64 0000 000B 4777 6D6E FFFF FFFE 0101"            /* jd....Gwmn????.. */
	$"016F 626A 6400 0000 1C6C 7072 74FF FFFF"            /* .objd....lprt??? */
	$"FE01 015C F850 686F 6C54 6261 7252 536F"            /* ?..\?PholTbarRSo */
	$"7454 6261 726F 626A 6400 0000 3C47 6261"            /* tTbarobjd...<Gba */
	$"6E00 0000 0001 4700 1101 0101 0101 00FF"            /* n.....G........? */
	$"FFFF FFFF FFFF FF00 0000 00FF FFFF FF00"            /* ???????....????. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0100 0000 0100 0062 6567 736F 626A"            /* .........begsobj */
	$"6400 0000 3C76 6965 7754 6261 7201 3700"            /* d...<viewTbar.7. */
	$"1101 0101 0101 0100 0000 0000 0000 0000"            /* ................ */
	$"0000 00FF FFFF FF00 0000 0000 0000 0000"            /* ...????......... */
	$"0000 0000 0000 0000 0000 0100 0000 0100"            /* ................ */
	$"0062 6567 736F 626A 6400 0000 3D73 7478"            /* .begsobjd...=stx */
	$"7449 4420 2000 3100 0D01 0100 0101 0000"            /* tID  .1......... */
	$"0000 F100 0000 0200 0000 00FF FFFF FF00"            /* ..?........????. */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"203A 9A06 5265 7320 4944 6F62 6A64 0000"            /*  :?.Res IDobjd.. */
	$"004D 7374 7874 0000 0000 0074 000D 0101"            /* .Mstxt.....t.... */
	$"0101 0000 0000 0021 0000 0002 0000 0000"            /* .......!........ */
	$"FFFF FFFF 0000 0000 0000 0000 0000 0000"            /* ????............ */
	$"0000 0000 0120 3A98 1652 6573 6F75 7263"            /* ..... :?.Resourc */
	$"6520 5479 7065 2061 6E64 204E 616D 6565"            /* e Type and Namee */
	$"6E64 7365 6E64 736F 626A 6400 0000 4973"            /* ndsendsobjd...Is */
	$"636C 7600 0000 0101 4700 F801 0101 0101"            /* clv.....G.?..... */
	$"01FF FFFF FF00 0000 0F00 0000 00FF FFFF"            /* .????........??? */
	$"FF00 0000 1000 0000 0100 0000 0000 0000"            /* ?............... */
	$"0000 0000 0000 0000 0000 0000 1300 0F00"            /* ................ */
	$"0000 0F52 536F 7401 6265 6773 646F 706C"            /* ...RSot.begsdopl */
	$"5253 6F74 6F62 6A64 0000 0040 6F74 6162"            /* RSotobjd...@otab */
	$"5253 6F74 0136 00E7 0101 0101 0101 0000"            /* RSot.6.?........ */
	$"0001 0000 0001 0000 0000 FFFF FFFF 0000"            /* ..........????.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0010 0000 0010 0001 3A98 0020 656E 6473"            /* ........:?. ends */
	$"646F 706C 5052 4F4A 6F62 6A64 0000 0032"            /* doplPROJobjd...2 */
	$"636E 746C 5052 4F4A 0014 0010 0101 0100"            /* cntlPROJ........ */
	$"0001 FFFF FFFF 0000 00F7 0000 0000 FFFF"            /* ..????...?....?? */
	$"FFFF 5052 4F4A 0000 0000 0000 0000 0000"            /* ??PROJ.......... */
	$"0000 656E 6473 656E 642E"                           /* ..endsend. */
};

data 'PPob' (15300, "New resource") {
	$"0002 646F 706C 646C 6F67 6F62 6A64 0000"            /* ..dopldlogobjd.. */
	$"0024 6764 6C67 3BC4 0000 0862 0000 0040"            /* .$gdlg;?...b...@ */
	$"0040 FFFF FFFF FFFF FFFF 0000 0000 4F4B"            /* .@????????....OK */
	$"2020 434E 434C 6265 6773 6F62 6A64 0000"            /*   CNCLbegsobjd.. */
	$"0012 7774 6861 FFFF FFFE 0101 0005 0006"            /* ..wtha????...... */
	$"0005 0006 6F62 6A64 0000 0012 7770 6F73"            /* ....objd....wpos */
	$"FFFF FFFE 0101 0640 0010 0010 0100 6F62"            /* ????...@......ob */
	$"6A64 0000 0004 7461 6267 6265 6773 6F62"            /* jd....tabgbegsob */
	$"6A64 0000 0045 7374 7874 0000 0000 005E"            /* jd...Estxt.....^ */
	$"000E 0101 0000 0000 0000 0004 0000 003F"            /* ...............? */
	$"0000 0000 FFFF FFFF 0000 0000 0000 0000"            /* ....????........ */
	$"0000 0000 0000 0000 0120 3A9B 0E52 6573"            /* ......... :?.Res */
	$"6F75 7263 6520 4E61 6D65 3A6F 626A 6400"            /* ource Name:objd. */
	$"0000 4573 7478 7400 0000 0000 5E00 0E01"            /* ..Estxt.....^... */
	$"0100 0000 0000 0000 0300 0000 0B00 0000"            /* ................ */
	$"00FF FFFF FF00 0000 0000 0000 0000 0000"            /* .????........... */
	$"0000 0000 0001 203A 9B0E 5265 736F 7572"            /* ...... :?.Resour */
	$"6365 2054 7970 653A 6F62 6A64 0000 003C"            /* ce Type:objd...< */
	$"7374 7874 0000 0000 005E 000E 0101 0000"            /* stxt.....^...... */
	$"0000 0000 0004 0000 0022 0000 0000 FFFF"            /* ........."....?? */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ??.............. */
	$"0000 0120 3A9B 054B 696E 643A 6F62 6A64"            /* ... :?.Kind:objd */
	$"0000 003D 706F 7062 4D53 5452 00CD 0012"            /* ...=popbMSTR.?.. */
	$"0101 0000 0000 0000 0069 0000 0020 0000"            /* .........i... .. */
	$"0000 FFFF FFFF 0000 0000 0000 01FF 0000"            /* ..????.......?.. */
	$"3BC5 0000 0000 0190 3A98 003F 3F3F 3F00"            /* ;?.....?:?.????. */
	$"026F 626A 6400 0000 3F65 7478 7449 4420"            /* .objd...?etxtID  */
	$"2000 3000 1401 0100 0000 0000 0000 6A00"            /*  .0...........j. */
	$"0000 5200 0000 00FF FFFF FF00 0000 0000"            /* ..R....????..... */
	$"0000 0000 0000 0000 0000 0001 103A 9804"            /* .............:?. */
	$"3130 3030 0006 0001 6F62 6A64 0000 0043"            /* 1000....objd...C */
	$"7374 7874 4944 4341 005E 000E 0101 0000"            /* stxtIDCA.^...... */
	$"0000 0000 0004 0000 0054 0000 0000 FFFF"            /* .........T....?? */
	$"FFFF 0000 0000 0000 0000 0000 0000 0000"            /* ??.............. */
	$"0000 0120 3A9B 0C52 6573 6F75 7263 6520"            /* ... :?.Resource  */
	$"4944 3A6F 626A 6400 0000 3D70 6F70 6254"            /* ID:objd...=popbT */
	$"5950 4500 CD00 1201 0100 0000 0000 0000"            /* YPE.?........... */
	$"6900 0000 0900 0000 00FF FFFF FF54 5950"            /* i...?....????TYP */
	$"4500 0001 FF00 003B C400 0000 0001 903A"            /* E...?..;?.....?: */
	$"9800 3F3F 3F3F 0002 6F62 6A64 0000 003E"            /* ?.????..objd...> */
	$"7075 7368 4F4B 2020 0044 0014 0101 0000"            /* pushOK  .D...... */
	$"0100 0000 00F2 0000 006E 0000 0000 FFFF"            /* .....?...n....?? */
	$"FFFF 0000 0384 0000 0000 0000 0000 0000"            /* ??...?.......... */
	$"0000 0170 0000 0643 7265 6174 6501 6F62"            /* ...p...Create.ob */
	$"6A64 0000 003E 7075 7368 434E 434C 0044"            /* jd...>pushCNCL.D */
	$"0014 0101 0000 0100 0000 00A0 0000 006E"            /* ...........?...n */
	$"0000 0000 FFFF FFFF 0000 0385 0000 0000"            /* ....????...?.... */
	$"0000 0000 0000 0000 0170 0000 0643 616E"            /* .........p...Can */
	$"6365 6C00 6F62 6A64 0000 003B 6574 7874"            /* cel.objd...;etxt */
	$"4E41 4D45 00CC 0014 0101 0000 0000 0000"            /* NAME.?.......... */
	$"006A 0000 003D 0000 0000 FFFF FFFF 0000"            /* .j...=....????.. */
	$"0000 0000 0000 0000 0000 0000 0000 0110"            /* ................ */
	$"3A98 0000 FF60 0365 6E64 7365 6E64 7365"            /* :?..?`.endsendse */
	$"6E64 2E"                                            /* nd. */
};

data 'RidL' (15000, "Project window", purgeable) {
	$"0002 4944 2020 5052 4F4A"                           /* ..ID  PROJ */
};

data 'RidL' (15050, "Save before closing", purgeable) {
	$"0004 4D53 4720 444F 4E54 434E 434C 5341"            /* ..MSG DONTCNCLSA */
	$"5645"                                               /* VE */
};

data 'RidL' (15080, "Duplicate resource ID") {
	$"0004 5253 5243 554E 4951 5245 504C 434E"            /* ..RSRCUNIQREPLCN */
	$"434C"                                               /* CL */
};

data 'RidL' (15300, "New resource") {
	$"0007 4D53 5452 4944 2020 4944 4341 5459"            /* ..MSTRID  IDCATY */
	$"5045 4F4B 2020 434E 434C 4E41 4D45"                 /* PEOK  CNCLNAME */
};

data 'wctb' (15050, "Save before closing") {
	$"0000 0000 0000 0000 0000 DDDD DDDD DDDD"            /* ..........?????? */
};

data 'wctb' (15080, "Duplicate resource ID") {
	$"0000 0000 0000 0000 0000 DDDD DDDD DDDD"            /* ..........?????? */
};

data 'wctb' (15300, "New resource") {
	$"0000 0000 0000 0000 0000 DDDD DDDD DDDD"            /* ..........?????? */
};

data 'CURS' (15151, "CKID locked file") {
	$"0000 6000 3070 1888 0CC8 0738 0310 0390"            /* ..`.0p.?.?.8...? */
	$"02E0 0460 0470 0798 070C 0606 BC00 0000"            /* .?.`.p.?....?... */
	$"0000 6000 3070 18F8 0CF8 07F8 03F0 03F0"            /* ..`.0p.?.?.?.?.? */
	$"03E0 07E0 07F0 0798 070C 0606 BC00 0000"            /* .?.?.?.?....?... */
	$"000E 0005"                                          /* .... */
};

data 'CURS' (15154, "Finder locked file") {
	$"0000 0000 0000 01C0 0220 0220 0220 07F0"            /* .......?. . . .? */
	$"07F0 07F0 07F0 07F0 07F0 0000 0000 0000"            /* .?.?.?.?.?...... */
	$"0000 0000 03E0 07F0 07F0 0770 0FF8 0FF8"            /* .....?.?.?.p.?.? */
	$"0FF8 0FF8 0FF8 0FF8 0FF8 0FF8 0000 0000"            /* .?.?.?.?.?.?.... */
	$"0009 0008"                                          /* .?.. */
};

data 'CURS' (15155, "CKID damaged") {
	$"0000 0000 0000 0000 0820 1650 1150 2288"            /* ......... .P.P"? */
	$"2288 4444 444C 7832 7022 601C 0000 0000"            /* "?DDDLx2p"`..... */
	$"0000 0000 0000 0820 1E70 3FF8 3FF8 7FFC"            /* ....... .p????.? */
	$"7FFC FEFE FEFE FC7F F87F F03E 601C 0000"            /* .??????.?.?>`... */
	$"000D 0001"                                          /* .... */
};

data 'ics#' (15152, "CKID writeable file", purgeable) {
	$"0000 0000 0070 0088 00C8 0130 0110 0220"            /* .....p.?.?.0...  */
	$"0220 0440 0440 0780 0700 2E00 0000 0000"            /* . .@.@.?........ */
	$"0000 0000 0070 00F8 00F8 01F0 01F0 03E0"            /* .....p.?.?.?.?.? */
	$"03E0 07C0 07C0 0780 0700 2E00 0000 0000"            /* .?.?.?.?........ */
};

data 'ics#' (15151, "CKID locked file", purgeable) {
	$"0000 0000 3070 1888 0CC8 0738 0310 0390"            /* ....0p.?.?.8...? */
	$"02E0 0460 0470 0798 070C 2E04 0000 0000"            /* .?.`.p.?........ */
	$"0000 0000 3070 18F8 0CF8 07F8 03F0 03F0"            /* ....0p.?.?.?.?.? */
	$"03E0 07E0 07F0 0798 070C 2E04 0000 0000"            /* .?.?.?.?........ */
};

data 'ics#' (15153, "CKID modified read only", purgeable) {
	$"0000 8000 8070 0088 10C8 1138 0110 0210"            /* ..?.?p.?.?.8.... */
	$"0220 0440 0448 0788 0700 2E01 0001 0000"            /* . .@.H.?........ */
	$"0000 8000 8070 00F8 10F8 11F8 01F0 03F0"            /* ..?.?p.?.?.?.?.? */
	$"03E0 07C0 07C8 0788 0700 2E01 0001 0000"            /* .?.?.?.?........ */
};

data 'ics#' (15154, "Finder locked file", purgeable) {
	$"0000 0000 0000 01C0 0220 0220 0220 07F0"            /* .......?. . . .? */
	$"07F0 07F0 07F0 07F0 07F0 0000 0000 0000"            /* .?.?.?.?.?...... */
	$"0000 0000 0000 01C0 0220 0220 0220 07F0"            /* .......?. . . .? */
	$"07F0 07F0 07F0 07F0 07F0 0000 0000 0000"            /* .?.?.?.?.?...... */
};

data 'ics#' (15155, "CKID damaged", purgeable) {
	$"0000 0000 0000 0410 0B28 08A8 1144 1144"            /* .........(.?.D.D */
	$"2222 2226 3C19 3811 300E 0000 0000 0000"            /* """&<.8.0....... */
	$"0000 0000 0000 0410 0F38 0FB8 1F7C 1F7C"            /* .........8.?.|.| */
	$"3E3E 3E3E 3C1F 381F 300E 0000 0000 0000"            /* >>>><.8.0....... */
};

data 'ics4' (15152, "CKID writeable file", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0FFF 0000 0000 0000 F222 F000"            /* .....?......?"?. */
	$"0000 0000 FF22 F000 0000 000F 11FF 0000"            /* ....?"?......?.. */
	$"0000 000F 111F 0000 0000 00F1 11F0 0000"            /* ...........?.?.. */
	$"0000 00F1 11F0 0000 0000 0F11 1F00 0000"            /* ...?.?.......... */
	$"0000 0F11 1F00 0000 0000 0FFF F000 0000"            /* ...........??... */
	$"0000 0FFF 0000 0000 00F0 FFF0 0000 0000"            /* ...?.....???.... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'ics4' (15151, "CKID locked file", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"00FF 0000 0FFF 0000 000F F000 F222 F000"            /* .?...?....?.?"?. */
	$"0000 FF00 FF22 F000 0000 0FFF 11FF F000"            /* ..?.?"?....?.??. */
	$"0000 00FF 111F 0000 0000 00FF F11F 0000"            /* ...?.......??... */
	$"0000 00F1 FFF0 0000 0000 0F11 1FF0 0000"            /* ...???.......?.. */
	$"0000 0F11 1FFF 0000 0000 0FFF F00F F000"            /* .....?.....??.?. */
	$"0000 0FFF 0000 FF00 00F0 FFF0 0000 0F00"            /* ...?..?..???.... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'ics4' (15153, "CKID modified read only", purgeable) {
	$"0000 0000 0000 0000 F000 0000 0000 0000"            /* ........?....... */
	$"F000 0000 0FFF 0000 0000 0000 F222 F000"            /* ?....?......?"?. */
	$"000F 0000 FF22 F000 000F 000F 11FF F000"            /* ....?"?......??. */
	$"0000 000F 111F 0000 0000 00F1 111F 0000"            /* ...........?.... */
	$"0000 00F1 11F0 0000 0000 0F11 1F00 0000"            /* ...?.?.......... */
	$"0000 0F11 1F00 F000 0000 0FFF F000 F000"            /* ......?....??.?. */
	$"0000 0FFF 0000 0000 00F0 FFF0 0000 000F"            /* ...?.....???.... */
	$"0000 0000 0000 000F 0000 0000 0000 0000"            /* ................ */
};

data 'ics4' (15155, "CKID damaged", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0F00 000F 0000"            /* ................ */
	$"0000 F1FF 00F1 F000 0000 F111 F0F1 F000"            /* ..??.??...?.???. */
	$"000F 111F 0F11 1F00 000F 111F 0F11 1F00"            /* ................ */
	$"00F1 11F0 00F1 11F0 00F1 11F0 00F1 1FF0"            /* .?.?.?.?.?.?.?.? */
	$"00FF FF00 000F F22F 00FF F000 000F 222F"            /* .??...?/.??..."/ */
	$"00FF 0000 0000 FFF0 0000 0000 0000 0000"            /* .?....??........ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'ics8' (15152, "CKID writeable file", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 00FF FFFF 0000 0000"            /* .........???.... */
	$"0000 0000 0000 0000 FF16 1616 FF00 0000"            /* ........?...?... */
	$"0000 0000 0000 0000 FFFF 1616 FF00 0000"            /* ........??..?... */
	$"0000 0000 0000 00FF 0505 FFFF 0000 0000"            /* .......?..??.... */
	$"0000 0000 0000 00FF 0505 05FF 0000 0000"            /* .......?...?.... */
	$"0000 0000 0000 FF05 0505 FF00 0000 0000"            /* ......?...?..... */
	$"0000 0000 0000 FF05 0505 FF00 0000 0000"            /* ......?...?..... */
	$"0000 0000 00FF 0505 05FF 0000 0000 0000"            /* .....?...?...... */
	$"0000 0000 00FF 0505 05FF 0000 0000 0000"            /* .....?...?...... */
	$"0000 0000 00FF FFFF FF00 0000 0000 0000"            /* .....????....... */
	$"0000 0000 00FF FFFF 0000 0000 0000 0000"            /* .....???........ */
	$"0000 FF00 FFFF FF00 0000 0000 0000 0000"            /* ..?.???......... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'ics8' (15151, "CKID locked file", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 FFFF 0000 0000 00FF FFFF 0000 0000"            /* ..??.....???.... */
	$"0000 00FF FF00 0000 FF16 1616 FF00 0000"            /* ...??...?...?... */
	$"0000 0000 FFFF 0000 FFFF 1616 FF00 0000"            /* ....??..??..?... */
	$"0000 0000 00FF FFFF 0505 FFFF FF00 0000"            /* .....???..???... */
	$"0000 0000 0000 FFFF 0505 05FF 0000 0000"            /* ......??...?.... */
	$"0000 0000 0000 FFFF FF05 05FF 0000 0000"            /* ......???..?.... */
	$"0000 0000 0000 FF05 FFFF FF00 0000 0000"            /* ......?.???..... */
	$"0000 0000 00FF 0505 05FF FF00 0000 0000"            /* .....?...??..... */
	$"0000 0000 00FF 0505 05FF FFFF 0000 0000"            /* .....?...???.... */
	$"0000 0000 00FF FFFF FF00 00FF FF00 0000"            /* .....????..??... */
	$"0000 0000 00FF FFFF 0000 0000 FFFF 0000"            /* .....???....??.. */
	$"0000 FF00 FFFF FF00 0000 0000 00FF 0000"            /* ..?.???......?.. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'ics8' (15153, "CKID modified read only", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"FF00 0000 0000 0000 0000 0000 0000 0000"            /* ?............... */
	$"FF00 0000 0000 0000 00FF FFFF 0000 0000"            /* ?........???.... */
	$"0000 0000 0000 0000 FF16 1616 FF00 0000"            /* ........?...?... */
	$"0000 00FF 0000 0000 FFFF 1616 FF00 0000"            /* ...?....??..?... */
	$"0000 00FF 0000 00FF 0505 FFFF FF00 0000"            /* ...?...?..???... */
	$"0000 0000 0000 00FF 0505 05FF 0000 0000"            /* .......?...?.... */
	$"0000 0000 0000 FF05 0505 05FF 0000 0000"            /* ......?....?.... */
	$"0000 0000 0000 FF05 0505 FF00 0000 0000"            /* ......?...?..... */
	$"0000 0000 00FF 0505 05FF 0000 0000 0000"            /* .....?...?...... */
	$"0000 0000 00FF 0505 05FF 0000 FF00 0000"            /* .....?...?..?... */
	$"0000 0000 00FF FFFF FF00 0000 FF00 0000"            /* .....????...?... */
	$"0000 0000 00FF FFFF 0000 0000 0000 0000"            /* .....???........ */
	$"0000 FF00 FFFF FF00 0000 0000 0000 00FF"            /* ..?.???........? */
	$"0000 0000 0000 0000 0000 0000 0000 00FF"            /* ...............? */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'ics8' (15155, "CKID damaged", purgeable) {
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 00FF 0000 0000 00FF 0000 0000"            /* .....?.....?.... */
	$"0000 0000 FF05 FFFF 0000 FF05 FF00 0000"            /* ....?.??..?.?... */
	$"0000 0000 FF05 0505 FF00 FF05 FF00 0000"            /* ....?...?.?.?... */
	$"0000 00FF 0505 05FF 00FF 0505 05FF 0000"            /* ...?...?.?...?.. */
	$"0000 00FF 0505 05FF 00FF 0505 05FF 0000"            /* ...?...?.?...?.. */
	$"0000 FF05 0505 FF00 0000 FF05 0505 FF00"            /* ..?...?...?...?. */
	$"0000 FF05 0505 FF00 0000 FF05 05FF FF00"            /* ..?...?...?..??. */
	$"0000 FFFF FFFF 0000 0000 00FF FF16 16FF"            /* ..????.....??..? */
	$"0000 FFFF FF00 0000 0000 00FF 1616 16FF"            /* ..???......?...? */
	$"0000 FFFF 0000 0000 0000 0000 FFFF FF00"            /* ..??........???. */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
};

data 'MENU' (15300, "Resource type") {
	$"3BC4 0000 0000 0000 0000 FFFF FFFF 0D52"            /* ;?........????.R */
	$"6573 6F75 7263 6520 5479 7065 00"                   /* esource Type. */
};

data 'MENU' (15301, "Resource master") {
	$"3BC5 0000 0000 0000 0000 FFFF FFFF 0949"            /* ;?........?????I */
	$"7465 6D20 5479 7065 00"                             /* tem Type. */
};

data 'Mcmd' (15300) {
	$"0000"                                               /* .. */
};

data 'Mcmd' (15301, "Resource master") {
	$"0000"                                               /* .. */
};

