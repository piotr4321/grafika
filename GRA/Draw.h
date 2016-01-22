
#pragma once
#include <cstdlib>
#include "quickcg.h"

//klasa reprezentujaca operacje rysowania
class Draw {
 public:
 //funkcja inicjalizująca okno gry
  static void initScreen(int width, int height, bool fullscreen, const std::string& text);
  //funkcja rysująca nową klatkę
  static void updateScreen(); 
//funkcja czyszcząca ekran
  static void clearScreenToBlack(); 
  //funkcja rysująca ściane
  static void drawVerticalLine(int x, int y1, int y2, const QuickCG::ColorRGB& color);
//wybór kolory ściany
  static QuickCG::ColorRGB setWallColor(int n);
};
