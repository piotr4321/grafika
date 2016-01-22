#include <iostream>
#include <chrono>
//klasa reprezentująca licznik czasu
class Timer {
 public:
  static void setActualTime();
  inline static double getActualTime() { return actualTime;}
  inline static void start() {startTime = std::chrono::high_resolution_clock::now(); }
  inline static bool getTimerOn() { return timerOn;}
  inline static bool setTimerOn(bool flag) {timerOn = flag;}
 private:
  static std::chrono::time_point<std::chrono::system_clock>
      startTime;  // zmiena reprezentujaca poczatkowy czas
  static double actualTime;  // zmienna reprezentujaca koncowy czas
  static bool timerOn;
};


