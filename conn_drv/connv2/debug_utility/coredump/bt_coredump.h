#ifndef _BT_COREDUMP_H
#define _BT_COREDUMP_H

void btdumpUeventInit(void);
void btdumpUeventDeinit(void);
void btdumpSendUeventHandler(char* subtype);

#endif
