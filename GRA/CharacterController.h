
#include "WorldMap.h"
//klasa reprezentująca poruszanie się gracza po mapie
class CharacterController {
 public:
 //funkcja przesuwająca gracza do przodu 
  static void moveForward(WorldMap& map,
                          double& posX,
                          double& dirX,
                          double& posY,
                          double& dirY,
                          double& moveSpeed);
  //funkcja przesuwająca gracza do tyłu
  static void moveBackward(WorldMap& map,
                           double& posX,
                           double& dirX,
                           double& posY,
                           double& dirY,
                           double& moveSpeed);

  //funkcja obracająca kamere w prawo
  static void rotateRight(double& dirX,
                          double& dirY,
                          double& planeX,
                          double& planeY,
                          double& rotSpeed);
   //funkcja obracająca kamere w lewo
  static void rotateLeft(double& dirX,
                         double& dirY,
                         double& planeX,
                         double& planeY,
                         double& rotSpeed);
  //funkcja odpowiadająca za zwiększenie prędkości gracza (po naciśnięciu lewego shifta)
  inline static double run() { return 0.03; }
  // funkcja spowalniająca gracza po puszczeni klawisza lewy shift
  inline static double walk() { return 0.015; }
  //funkcja zawężająca pole widzenia gracza
  static void narrowing(double& planeX, double& planeY);
  //funkcja rozszerzająca pole widzenia gracza
  static void widening(double& planeX, double& planeY);
};
