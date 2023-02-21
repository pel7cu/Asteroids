#pragma once

#include <entt.hpp>
#include <unordered_map>
#include <string>


namespace GameDev2D
{
    class GameWindow;

    enum class KeyState
    {
        Down = 0,
        Up,
        Repeat
    };

    enum class KeyCode
    {
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		Zero = 48, /* 0 */
		One = 49, /* 1 */
		Two = 50, /* 2 */
		Three = 51, /* 3 */
		Four = 52, /* 4 */
		Five = 53, /* 5 */
		Six = 54, /* 6 */
		Seven = 55, /* 7 */
		Eight = 56, /* 8 */
		Nine = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
    };

  
    class Keyboard
    {
    public:
        Keyboard();
        ~Keyboard();

        entt::sink<void(KeyCode, KeyState)> KeyEventSlot;

        struct State
        {
            State() : 
                duration(0.0f),
                keyState(KeyState::Up)
            {
            }

            State(const State& state) :
                duration(state.duration),
                keyState(state.keyState)
            {
            }

			float duration;
            KeyState keyState;
        };

        //Returns the State for a specific key
        State GetState(KeyCode keyCode);
        
		//Converts a KeyState to a string
        static std::string KeyStateToString(KeyState keyState);

		//Converts a KeyCode to a string
        static std::string KeyCodeToString(KeyCode keyCode);

    private:
		friend class GameWindow;

		//Updates the key data, specifically to update the duration a
		//key has been pressed for.
		void OnUpdate(float delta);
		void OnWindowFocusChange(bool isFocused);

        //Handle key events, called from GameWindow
        void HandleKeyEvent(KeyCode keyCode, KeyState keyState);

        //Member variable
        std::unordered_map<KeyCode, State> m_KeyStates;
        entt::sigh<void(KeyCode, KeyState)> m_KeyEventSignal;
    };
}

