
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

//klasa reprezentująca mapę
class WorldMap {
 public:
 //funkcja inicjalizująca mapę wczytaną z pliku
  WorldMap(std::string plik);
  inline int getXSize() const { return xSize; }
  inline int getYSize() const { return ySize; }
  //wspłórzędna x'owa startu gry
  int xStart;
  //współrzędna x'owa końca gry
  int xEnd;
  //współrzędna y'kowa startu gry
  int yStart;
  //współrzędna y'kowa końca gry
  int yEnd;
  std::vector<char> fileMapArr;
  std::vector<std::vector<int> > worldMap;
  // Zmienne pomocnicze (rozmiary mapy)
 private:
  int xSize;
  int ySize;
};
