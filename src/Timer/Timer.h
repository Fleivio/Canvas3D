#ifndef _TIMER_
#define _TIMER_

/*funcao que controla o tempo do jogo*/

#define FIXED_FPS 50
#define FRAME_TIME 1000/FIXED_FPS

#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

class Timer {
private:
    static chrono::time_point<chrono::system_clock> current_time;
    static chrono::time_point<chrono::system_clock> last_time;
    static float delta_time;
    static float acc_time;

    static chrono::time_point<chrono::system_clock> get_now(){
        return chrono::system_clock::now();
    }
public:

    //inicia o timer
    static void init() {
        current_time = get_now();
        last_time = get_now();
        acc_time = 0;
    }

    //atualiza o timer (atual += delta)
    static void update() {
        last_time = current_time;
        current_time = get_now();
        delta_time = std::chrono::duration<float>(current_time - last_time).count();
        acc_time += delta_time;
        if(acc_time < 0) acc_time = 0;
    }

    //sleep para manter o fps
    static void wait_fps(){
        chrono::milliseconds fDur(static_cast<int>(FRAME_TIME));
        std::this_thread::sleep_for(fDur);
    }

    //retorna o delta time
    static float get_delta_time() {
        return delta_time;
    }

    //retorna o tempo atual
    static float get_current_time() {
        return acc_time;
    }
};

#endif
