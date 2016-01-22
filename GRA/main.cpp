#include "Timer.h"
#include "WorldMap.h"
#include "CharacterController.h"
#include "Draw.h"
using namespace std;
using namespace QuickCG;

int main(int argc, char* argv[]) {
  // Zmienne lokalne
  bool isPlaying = false;

  WorldMap map = WorldMap(argv[1]);
  cout << "Wczytano wymiary tabicy: " << map.getXSize() << " " << map.getYSize()
       << endl;

  double posX = map.xStart + 0.5, //x'owa pozycja startowa
         posY = map.yStart + 0.5; //y'kowa pozycja startowa
  double dirX = -1, dirY = 0;        //wartość rektora kierunku
  double planeX = 0, planeY = 0.66;  //parametry płaszczyzny kamery
  double frameTime = 0.015;
 
  //inicjalizacja głównego okna
  Draw::initScreen(1024, 640, 0, "Labirynt 3D");
  ofstream myfile;
      myfile.open("../GRA/wynik.log");
      myfile << "0";
      myfile.close();
  //główna pętla programu, po naciśnięciu klawisza ESC kończymy gre lub po zbliżeniu się do ściany wyjścia z labiryntu
  while (!done() && !isPlaying) {
    //warunek sprawdzający czy gracz podszedł do ściany wyjścia
    if (posX >= map.xEnd - 0.1 && posX <= map.xEnd + 1.1 &&
        posY >= map.yEnd + 0.1 && posY <= map.yEnd + 0.9) {
      //obliczanie czasu gry
      Timer::setActualTime();
      std::ostringstream out;
      out << std::setprecision(3) << Timer::getActualTime();
      std::cout << "Czas gry: " << out.str() << "s" << std::endl;
      
      ofstream myfile;
      myfile.open("../GRA/wynik.log");
      myfile << "Czas gry: " << out.str() << "s.\n";
      myfile.close();
            
      isPlaying = true;
    }
    //pętla renderująca
    for (int x = 0; x < w; x++) {
      //wyliczanie kierunku i ray'a
      double cameraX = 2 * x / double(w) - 1;  // x-coordinate in camera space
      double rayPosX = posX;  //pozycja x
      double rayPosY = posY;  // pozycja y
      double rayDirX = dirX + planeX * cameraX; //wyznaczanie kierunku x raya
      double rayDirY = dirY + planeY * cameraX; //wyznaczanie kierunku y raya
      //
      int mapX = int(rayPosX);  //x'owa współrzędna na naszej mapie
      int mapY = int(rayPosY);  // y'kowa współrzędna na naszej mapie

      // długość raya do najbliższej ściany 
      double sideDistX; 
      double sideDistY; 

      //długość raya z jednego x'a lub y'ka ściany do następnego x'a lub y'ka ściany
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      double perpWallDist;

      // kierunki kroku x i y
      int stepX;
      int stepY;

      bool hit = false;  // flaga uderzenia w sciane
      int side;     // strona ściany która została uderzona
      // kalkulacja kroku i calculate step and initial sideDist
      if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (rayPosX - mapX) * deltaDistX;
      } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
      }
      if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (rayPosY - mapY) * deltaDistY;
      } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
      }
      // algorytm Digitam differential analyzer
      while (hit == 0) {
        // skok to następnego kwadratu na mapie na pozycji x lub y 
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        // warunek sprawdzający czy ray uderzył w ściane
        if (map.worldMap[mapX][mapY] > 0)
          hit = true;
      }

      //wyliczanie dystansu wyświetlanego widoku
      if (side == 0)
        perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
      else
        perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

     
      //wyliczanie wysokości linii rysowanych na obrazie
      int lineHeight = abs(int(h / perpWallDist));

      // wyliczanie najniższego i najwyższego pixela do wypełniania
      int drawStart = -lineHeight / 2 + h / 2;
      if (drawStart < 0)
        drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if (drawEnd >= h)
        drawEnd = h - 1;

      //wybór koloru ściany
      ColorRGB color = Draw::setWallColor(map.worldMap[mapX][mapY]);

      //zmiana koloru x'owej ściany w celu odróżnienia od y'kowej
      if (side == 1) {
        color = color / 2;
      }

      //wysowanie ściany
      Draw::drawVerticalLine(x, drawStart, drawEnd, color);
    }
    //liczenie czasu gry
    if (Timer::getTimerOn()) {
      Timer::setActualTime();
      std::ostringstream out;
      out << std::setprecision(3) << Timer::getActualTime();
      print("Czas gry: " + out.str() + "s", 0, 0);
    }
    Draw::updateScreen();
    Draw::clearScreenToBlack();

    //zmienna prędkości poruszania się gracza
    double moveSpeed =
        frameTime * 5.0;
    //zmienna prędkości obracania kamery
    double rotSpeed =
        frameTime * 3.0;

    //funkcja nasłuchująca naciskanie klawiszy
      readKeys();
    // warunek pozwalający się poruszać do przeodu jeśli przed nami nie ma ściany
    if (keyDown(SDLK_UP)) {
      if (Timer::getTimerOn() == false) {
        Timer::setTimerOn(true);
        Timer::start();
      }
      CharacterController::moveForward(map, posX, dirX, posY, dirY, moveSpeed);
    }
    // warunek pozwalający się poruszać do tyłu jeśli za nami nie ma ściany
    if (keyDown(SDLK_DOWN)) {
      CharacterController::moveBackward(map, posX, dirX, posY, dirY, moveSpeed);
    }
    // obracanie kamery w prawo
    if (keyDown(SDLK_RIGHT)) {
      CharacterController::rotateRight(dirX, dirY, planeX, planeY, rotSpeed);
    }
    // obracanie kamery w lewo
    if (keyDown(SDLK_LEFT)) {
      CharacterController::rotateLeft(dirX, dirY, planeX, planeY, rotSpeed);
    }
    if (keyDown(SDLK_LSHIFT)) {
      // przyśpieszenie gracza klawiszem shift
      frameTime = CharacterController::run();
    } else
      frameTime = CharacterController::walk();
    if (keyDown(SDLK_a))  // zmniejsznie szerokości pola widzenia (min 45*)
    {
      CharacterController::narrowing(planeX, planeY);
     // std::cout << planeY << std::endl;
     // std::cout << planeX << std::endl;
    }

    if (keyDown(SDLK_d))  // zwiekszanie szerokości pola widzenia (max 120*)
    {
      CharacterController::widening(planeX, planeY);
     // std::cout << planeY << std::endl;
    //  std::cout << planeX << std::endl;
    }
  }
}
