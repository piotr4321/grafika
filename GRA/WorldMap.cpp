#include "WorldMap.h"
#include <stdlib.h>
 
WorldMap::WorldMap(std::string plik) {
    srand(time(NULL));
    bool isFirstLine = true;
    std::fstream fp(plik, std::fstream::in);
    std::string line;
    //pętla wczytująca zawartość pliku do wektora
    while (getline(fp, line)) {
      if (isFirstLine) {
        isFirstLine = false;
        this->xSize = std::stoi(line.substr(0, line.find(",")).c_str());
        this->ySize = std::stoi(line.substr(line.find(",") + 1).c_str());
        continue;
      }
      std::vector<char> temp(line.begin(), line.end());
      fileMapArr.insert(fileMapArr.end(), temp.begin(), temp.end());
    }
    fp.close();

    for (int i = 0; i < this->xSize; ++i)
      worldMap.push_back(std::vector<int>());

    int k = 0;
    //inicjalizacja mapy
    for (int i = 0; i < this->xSize; i++)
      for (int j = 0; j < this->ySize; ++j) {
        if (fileMapArr[k] == 'X')
        //losowy kolor ściany
          worldMap[i].push_back(rand()%3+1);
        else if (fileMapArr[k] == 's') {
          xStart = i;
          yStart = j;
          //kolor ściany startowej
          worldMap[i].push_back(4);
        } else if (fileMapArr[k] == 'E') {
          xEnd = i;
          yEnd = j;
          //kolor ściany końcowej
          worldMap[i].push_back(5);
        } else
          worldMap[i].push_back(0);
        k++;
      }
    // wypisywanie mapy
  /*  for (const std::vector<int>& v : worldMap) {
      for (int x : v)
        std::cout << x << ' ';
      std::cout << std::endl;
    }*/
  }
