#include "Draw.h"
using namespace QuickCG;

void Draw::initScreen(int width, int height, bool fullscreen, const std::string& text) {
	screen(width, height, fullscreen, text);
}


void Draw::updateScreen(){
	redraw();
}


void Draw::clearScreenToBlack() {
	cls();
}


void Draw::drawVerticalLine(int x, int y1, int y2, const ColorRGB& color) {
	verLine(x, y1, y2, color);
}


ColorRGB Draw::setWallColor(int n) {
ColorRGB color;
switch (n) {
        case 1:
          color = RGB_Red;
          break;  // czerwony
        case 2:
          color = RGB_Green;
          break;  // zielony
        case 3:
          color = RGB_Blue;
          break;  // niebieski
        case 4:
          color = RGB_Olive;
          break;  // oliwkowy
        case 5:
          color = RGB_Purple;
          break; //purpurowy
        default:
          color = RGB_Yellow;
          break;  // żółty
      }
return color;
}

