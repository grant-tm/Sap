#ifndef KBDIO_H
#define KBDIO_H

#include <windows.h>
#include <chrono>

#include <mutex>
#include <condition_variable>

#include "SystemUtilities.h"

#define NUM_KEYS 256

// commands
#define KBD_CTRL_S 19
#define KBD_CTRL_R 18
#define KBD_CTRL_T 20
#define KBD_CTRL_Q 17

// non-printable characters
#define KBD_RETURN 10
#define KBD_BACKSPACE 8
#define KBD_DELETE 127
#define KBD_SHIFT 16

namespace chrono = std::chrono;

class KBDIO {
public:
    
    KBDIO (void) {};

    // Enforce singleton type
    KBDIO(KBDIO const&) = delete;
    void operator=(KBDIO const&) = delete;
    static KBDIO& kdb_get_handle (void) {
        static KBDIO inst;
        return inst;
    }

    // input
    void kbd_poll_inputs (void);
    char kbd_listener    (void);

    // conversions
    inline char kbd_code_to_char (int kbd_code);
    inline int  kbd_char_to_code (char c);

    // thread safe state checks
    inline bool kbd_is_pressed  (char c);
    inline bool kbd_is_held     (char c);
    inline bool kbd_is_fresh    (char c);
    inline bool kbd_is_pressed  (int kbd_code);
    inline bool kbd_is_held     (int kbd_code);
    inline bool kbd_is_fresh    (int kbd_code);

private:
    
    // input state
    bool pressed[NUM_KEYS] = {false};
    bool held[NUM_KEYS] = {false};
    int hold_time[NUM_KEYS] = {0};

    // thread safeing
    std::mutex mutex;
    std::condition_variable cv;
};

#endif // KBDIO_H