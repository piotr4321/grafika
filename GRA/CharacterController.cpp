#include "CharacterController.h" 
#include <cmath>

  //funkcja przesuwająca gracza do przodu (dodatkowy warunek w if'ie żeby można było ruszyć ze startu)
void CharacterController::moveForward(WorldMap& map,
                          double& posX,
                          double& dirX,
                          double& posY,
                          double& dirY,
                          double& moveSpeed) {
    if (map.worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false ||
        map.worldMap[int(posX + dirX * moveSpeed)][int(posY)] == 4) {
      posX += dirX * moveSpeed;
    }
    if (map.worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false ||
        map.worldMap[int(posX)][int(posY + dirY * moveSpeed)] == 4) {
      posY += dirY * moveSpeed;
    }
  }
  //funkcja przesuwająca gracza do tyłu
void CharacterController::moveBackward(WorldMap& map,
                           double& posX,
                           double& dirX,
                           double& posY,
                           double& dirY,
                           double& moveSpeed) {
    if (map.worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
      posX -= dirX * moveSpeed;
    if (map.worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
      posY -= dirY * moveSpeed;
  }

  //funkcja obracająca kamere w prawo
void CharacterController::rotateRight(double& dirX,
                          double& dirY,
                          double& planeX,
                          double& planeY,
                          double& rotSpeed) {
    double oldDirX = dirX;
    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
  }
   //funkcja obracająca kamere w lewo
void CharacterController::rotateLeft(double& dirX,
                         double& dirY,
                         double& planeX,
                         double& planeY,
                         double& rotSpeed) {
    double oldDirX = dirX;
    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
  }

  //funkcja zawężająca pole widzenia gracza
void CharacterController::narrowing(double& planeX, double& planeY) {
    if (planeY < -0.42 || planeX > 0.42) {
      planeY += 0.001;
      planeX -= 0.001;
    }
  }
  //funkcja rozszerzająca pole widzenia gracza
void CharacterController::widening(double& planeX, double& planeY) {
    if (planeY > -1.75 || planeX < 1.75) {
      planeY -= 0.001;
      planeX += 0.001;
    }
  }
