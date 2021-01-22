//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"", "mem-cpu", 1, 0},
	{"", "volume", 1, 0},
	{"", "clock", 1, 0},
	{"", "kernel", 1, 0},
	{"", "connection", 1, 0},
	{"", "battery", 1, 0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "";
static unsigned int delimLen = 2;
