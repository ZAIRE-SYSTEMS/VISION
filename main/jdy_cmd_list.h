#ifndef JDY_CMD_LIST_H
#define JDY_CMD_LIST_H

#include <stdint.h>

//Media Player
#define PLAYER_PLAY_PAUSE       "COM+PP\r\n"
#define PLAYER_VOL_UP           "COM+VP\r\n"
#define PLAYER_VOL_DWN          "COM+VD\r\n"
#define PLAYER_MEDIA_NXT        "COM+PN\r\n"
#define PLAYER_MEDIA_PRV        "COM+PV\r\n"

//HFP
#define HFP_ANSWER_CALL         "COM+CA\r\n"
#define HFP_DECLINCE_CALL       "COM+CJ\r\n"
#define HFP_HANGUP_CALL         "COM+CE\r\n"
#define HFP_RD_LAST_CALL        "COM+CR\r\n"

#endif // JDY_CMD_LIST_H