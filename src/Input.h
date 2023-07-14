/*controla o input vindo da main
Possui controladores de estado para saber se o usuário está em hold ou click
é mais genérico do que precisava, não tem seu potancial totalmente utilizado porque o comportamento do painel é bem simples*/

#ifndef _INPUT_
#define _INPUT_

#define LEFT_BUTTON 0
#define RIGHT_BUTTON 2

#define MOUSE_DOWN 0
#define MOUSE_MOVE -2
#define MOUSE_UP 1

#define ANY_MOUSE -2

#define WHEEL_UP 1
#define WHEEL_DOWN -1

#define CTRL_S 19
#define CTRL_D 4
#define DELETE_K 127

#define LEFT_K 200
#define RIGHT_K 202
#define UP_K 201
#define DOWN_K 203

#define K_NONE -1

#define K_A 97
#define K_B 98
#define K_C 99
#define K_D 100
#define K_E 101
#define K_F 102
#define K_W 119
#define K_S 115

#define K_Q 113

#define K_R 114
#define K_SPACE 32

#include "Basic/Vector.h"
#include <vector>
#include <list>

using namespace std;


enum MouseState
{
    CLICK_DOWN,
    CLICK_UP,
    HOVER,
    HOLD,
    UN_HOLD
};

class Input
{
private:
    static MouseState state;
    static Vector previousPosition;
    static Vector actualPosition;
    static Vector movementDelta;

    static list<int> keysDown;

    /*recebe uma ação do mouse (move, click etc) e calcula o proximo estado baseado
    no estado atual (se click + move -> hold)*/
    static void calc_next_state(int currentAction);
    /*atualiza a direção do movemento do mouse, util para hold*/
    static void att_movement_delta();
    /*chama as funções necessárias dos controladores e do painel, para cada ação desempenhada*/
    static void handle_action();

public:

    static void update();
    /*recebe input do mouse (botão clicado, açao, posicao)*/
    static void att_mouse(int button, int currentAction, int x, int y);
    /*recebe input do teclado, botão pressionado*/
    static void keyboard_down(int key);
    /*recebe input do teclado, botao levantado*/
    static void keyboard_up(int key);
    /*recebe input do mouse, wheel*/
    static void mouse_wheel(int direction);
};

#endif