#include "inputManager.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"

inputManager* inputManager::m_instance = nullptr;



void inputManager::updateKeyState(int keyId, const keyState& updateState)
{
    keyId = translateScanCode(keyId);
    keyState cs = keyboard.currState[keyId], ps = keyboard.preState[keyId];

    if (updateState == keyState::pressed)
    {
        switch (ps)
        {
        case inputManager::keyState::held:
        case inputManager::keyState::pressed:
            keyboard.currState[keyId] = keyState::held;

            break;
        case inputManager::keyState::none:
        case inputManager::keyState::released:
            keyboard.currState[keyId] = keyState::pressed;
            break;

        }
    }
    else if (updateState == keyState::released)
    {
        switch (ps)
        {
        case inputManager::keyState::none:
        case inputManager::keyState::held:
        case inputManager::keyState::pressed:
            keyboard.currState[keyId] = keyState::released;
            keyboard.currState[keyId] = keyState::released;
            break;
        case inputManager::keyState::released:
        default:
            keyboard.currState[keyId] = keyState::none;
            break;
        }
    }else if (updateState == keyState::none)
        keyboard.currState[keyId] = keyState::none;


    //
    //keyboard.preState[keyId] = cs;
    //	currState[keyId] = updateState;


}

inputManager::keyState inputManager::getKeyState(char keyId)
{

    return keyboard.currState[keyId];
}

void inputManager::updateMouse(int newX, int newY)
{
    mouse.x = newX;
    mouse.y = newY;
}

void inputManager::updateMouseRel(int newX, int newY)
{
    
    mouse.relX = newX;
    mouse.relY = newY;
}

void inputManager::updateMouseButton(int button, keyState newState)
{
    mouse.buttons[button] = newState;
}

void inputManager::clearKeys()
{
    memset(keyboard.currState, -1, sizeof(keyboard.currState));
    memset(keyboard.preState, -1, sizeof(keyboard.preState));
}

bool inputManager::getKeyPressed(const keys& keyName)
{
    keyState state = getKeyState((char)keyName);

    if (state == keyState::pressed)
        return true;

    return false;
}

bool inputManager::getKeyReleased(const keys& keyName)
{

    keyState state = getKeyState((char)keyName);

    if (state == keyState::released)
    {


        int id = 0;
        for (auto [key, value] : keyMap)
        {
            if (value == (int)keyName)
            {
                id = key;
                break;
            }
        }


        updateKeyState(id, keyState::none);
        return true;
    }

    return false;
}

bool inputManager::getMousePressed(const buttons& mouseButton)
{
    keyState state = mouse.buttons[(int)mouseButton];

    if (state == keyState::pressed || state == keyState::held)
        return true;

    return false;
}

bool inputManager::getMouseReleased(const buttons& mouseButton)
{
    keyState state = mouse.buttons[(int)mouseButton];

    if (state == keyState::released)
    {
        updateMouseButton((int)mouseButton, keyState::none);
        return true;
    }

    return false;
}

bool inputManager::getKeyHeld(const keys& keyName)
{
    keyState state = getKeyState((char)keyName);

    if (state == keyState::held)
        return true;

    return false;
}

inputManager* inputManager::getInstance()
{
    if (m_instance == nullptr)
        m_instance = new inputManager();

    return m_instance;
}

std::pair<int, int> inputManager::getMouse() const
{
    return std::pair<int, int>(mouse.x, mouse.y);
}

std::pair<int, int> inputManager::getRelMouse() const
{
    return std::pair<int, int>(mouse.relX, mouse.relY);
}

inputManager::~inputManager()
{
    delete m_instance;
}

void inputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyState state = keyState::none;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
        state = keyState::pressed;
    else
        state = keyState::released;
    m_instance->updateKeyState(key, state);

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);


}

void inputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    keyState state = keyState::none;
    state = (action == GLFW_PRESS) ? keyState::pressed : keyState::released;
    m_instance->updateMouseButton(button, state);
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void inputManager::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    m_instance->updateMouse((int)xpos, (int)ypos);
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}