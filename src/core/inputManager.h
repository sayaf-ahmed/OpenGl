#pragma once
#include <memory.h>
#include <utility>
#include <map>
#include "glfwinc.h"







enum class keys
{
    
    KEY_SPACE     = 0, 
    KEY_APOSTROPHE   , 
    KEY_COMMA        , 
    KEY_MINUS        , 
    KEY_PERIOD       , 
    KEY_SLASH        , 
    KEY_0            , 
    KEY_1            , 
    KEY_2            , 
    KEY_3            , 
    KEY_4            , 
    KEY_5            , 
    KEY_6            , 
    KEY_7            , 
    KEY_8            , 
    KEY_9            , 
    KEY_A            , 
    KEY_B            , 
    KEY_C            , 
    KEY_D            , 
    KEY_E            , 
    KEY_F            , 
    KEY_G            , 
    KEY_H            , 
    KEY_I            , 
    KEY_J            , 
    KEY_K            , 
    KEY_L            , 
    KEY_M            , 
    KEY_N            , 
    KEY_O            , 
    KEY_P            , 
    KEY_Q            , 
    KEY_R            , 
    KEY_S            , 
    KEY_T            , 
    KEY_U            , 
    KEY_V            , 
    KEY_W            , 
    KEY_X            , 
    KEY_Y            , 
    KEY_Z            , 
    KEY_LEFT_BRACKET , 
    KEY_BACKSLASH    , 
    KEY_RIGHT_BRACKET, 
    KEY_ESCAPE       , 
    KEY_ENTER        , 
    KEY_TAB          , 
    KEY_BACKSPACE    , 
    KEY_INSERT       , 
    KEY_DELETE       , 
    KEY_RIGHT        , 
    KEY_LEFT         , 
    KEY_DOWN         , 
    KEY_UP           , 
    KEY_PAGE_UP      , 
    KEY_PAGE_DOWN    , 
    KEY_F1           , 
    KEY_F2           , 
    KEY_F3           , 
    KEY_F4           , 
    KEY_F5           , 
    KEY_F6           , 
    KEY_F7           , 
    KEY_F8           , 
    KEY_F9           , 
    KEY_F10          , 
    KEY_F11          , 
    KEY_F12          , 
    KEY_LEFT_SHIFT   , 
    KEY_LEFT_CONTROL , 
    KEY_LEFT_ALT     , 
    KEY_RIGHT_SHIFT  , 
    KEY_RIGHT_CONTROL, 
    KEY_RIGHT_ALT    , 
    KEY_RIGHT_SUPER  , 

                                                                    
    
};

enum class buttons: char 
{
    left = 0, 
    right = 1,
    middle = 2
};

class inputManager
{
public:
	enum class keyState :char
	{
		none = -1,
		pressed = 0,
		released = 1,
		held = 2
	};
private:
    std::map<int, int> keyMap = 
    {
        {32 ,  0 },
        {39 ,  1 },
        {44 ,  2 },
        {45 ,  3 },
        {46 ,  4 },
        {47 ,  5 },
        {48 ,  6 },
        {49 ,  7 },
        {50 ,  8 },
        {51 ,  9 },
        {52 ,  10},
        {53 ,  11},
        {54 ,  12},
        {55 ,  13},
        {56 ,  14},
        {57 ,  15},
        {65 ,  16},
        {66 ,  17},
        {67 ,  18},
        {68 ,  19},
        {69 ,  20},
        {70 ,  21},
        {71 ,  22},
        {72 ,  23},
        {73 ,  24},
        {74 ,  25},
        {75 ,  26},
        {76 ,  27},
        {77 ,  28},
        {78 ,  29},
        {79 ,  30},
        {80 ,  31},
        {81 ,  32},
        {82 ,  33},
        {83 ,  34},
        {84 ,  35},
        {85 ,  36},
        {86 ,  37},
        {87 ,  38},
        {88 ,  39},
        {89 ,  40},
        {90 ,  41},
        {91 ,  42},
        {92 ,  43},
        {93 ,  44},
        {256,  45},
        {257,  46},
        {258,  47},
        {259,  48},
        {260,  49},
        {261,  50},
        {262,  51},
        {263,  52},
        {264,  53},
        {265,  54},
        {266,  55},
        {267,  56},
        {290,  57},
        {291,  58},
        {292,  59},
        {293,  60},
        {294,  61},
        {295,  62},
        {296,  63},
        {297,  64},
        {298,  65},
        {299,  66},
        {300,  67},
        {301,  68},
        {340,  69},
        {341,  70},
        {342,  71},
        {344,  72},
        {345,  73},
        {346,  74},
        {347,  75},
    };
	struct keyBoardState
	{
		keyState currState[86];
		keyState preState [86];
		
        keyBoardState()
        {
            memset(currState, -1, 86 * sizeof(keyState));
            memset(preState,  -1, 86 * sizeof(keyState));

        }

	} keyboard;

    struct mouseState
    {
        int x, y, relX, relY;

        keyState buttons[3];

        mouseState()
        {
            memset(buttons, -1, 3 * sizeof(keyState));
        }
    }mouse;


    void updateKeyState(int keyId, const keyState& updateState);
    keyState getKeyState(char keyId);

    void updateMouse(int newX, int newY);
    void updateMouseRel(int newX, int newY);

    void updateMouseButton(int button, keyState newState);
	
    static inputManager* m_instance ;
    void clearKeys();
public:

    bool getKeyPressed(const keys& keyName);

    bool getKeyReleased(const keys& keyName);

    bool getMousePressed(const buttons& mouseButton);

    bool getMouseReleased(const buttons& mouseButton);


    bool getKeyHeld(const keys& keyName);
    static inputManager* getInstance();

    std::pair<int, int> getMouse()const;
    std::pair<int, int> getRelMouse() const;

    ~inputManager();
    friend class program;

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    int translateScanCode(int key)
    {
        return keyMap[key];
    }
};























































































































































/*struct mouseState
	{
		int x, y;
		keyBoardState currMouse[3];
		keyBoardState preMouse[3];

		void updateMouseKeyState(int keyId, const keyState& currState);
		void getMouseKeyState(int keyId);
	};*/



//
//if (cs == updateState || (cs == keyState::held && updateState == keyState::pressed))
//{
//    if (updateState == keyState::pressed || (updateState == keyState::held))
//    {
//        currState[keyId] = keyState::held;
//        preState[keyId] = keyState::none;
//        return;
//    }
//
//    else if (updateState == keyState::released)
//    {
//        currState[keyId] = keyState::none;
//        preState[keyId] = keyState::none;
//        return;
//
//    }
//
//}