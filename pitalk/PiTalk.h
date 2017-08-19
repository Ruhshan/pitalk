#ifndef PiTalkTypes_h
#define PiTalkTypes_h

#define MAX_COMMAND_LENGTH 255

char* replyOK = {"OK\n"};

char resetByte = '!';
char stopByte = '#';

char* commandLEDOn = {"LEDON"};
char* commandLEDOff = {"LEDOFF"};
//mycommands
char* commandTAKETEMP={"TAKETEMP"};
char* commandTAKEBP={"TAKEBP"};
char* commandPULSIOXY={"TAKEPULSIOXY"};
#endif
