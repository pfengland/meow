#ifndef H_MEOWKEYBOARD
#define H_MEOWKEYBOARD

#define MeowKeyboard_channelCount 16
#define MeowKeyboard_noteCount 128

typedef struct Note_s Note;
struct Note_s {
     int on;
     int velo;
};

typedef struct Channel_s Channel;
struct Channel_s {
     Note notes[MeowKeyboard_noteCount];
};

typedef struct MeowKeyboard_s MeowKeyboard;
struct MeowKeyboard_s {
     Channel channels[MeowKeyboard_channelCount];
};

MeowKeyboard* MeowKeyboard_create(void);
void MeowKeyboard_free(MeowKeyboard *keys);

#endif
