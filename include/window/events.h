//
// Created by Scoot on 14/02/2021.
//

#ifndef ENGINE_TEST_EVENTS_H
#define ENGINE_TEST_EVENTS_H

#include "window.h"

typedef unsigned int uint;

class Events {
public:
    static bool* m_bKeys;
    static uint* m_nFrames;
    static uint m_nCurrentFrame;
    static float m_fDeltaX;
    static float m_fDeltaY;
    static float m_fAxisX;
    static float m_fAxisY;
    static bool m_bCursorLocked;
    static bool m_bCursorStarted;

public:
    static int initialize();
    static void pullEvents();

    static bool isPressed(int keycode);
    static bool justPressed(int keycode);

    static bool isClicked(int button);
    static bool justClicked(int button);

    static void toogleCursor();
};

#endif //ENGINE_TEST_EVENTS_H
