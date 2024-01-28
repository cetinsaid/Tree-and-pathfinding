#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
//    Sector* insertRoot = nullptr;
//    Sector* inOrder = nullptr;
//    Sector* preOrder = nullptr;
//    Sector* postOrder = nullptr;
    SpaceSectorBST();
    ~SpaceSectorBST();
    int index = 0;
    void insertVector();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    Sector * insertSectors(Sector* rootTest , Sector* insertNode);
    Sector * deleteSector(Sector* rootTest , Sector* insertNode);
    Sector* pathTest(Sector* Root , Sector* wanted , std::vector<Sector*> & sector);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> stellarPath;
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    std::vector<Sector*> sectors;
    std::vector<std::string> vectors;
    std::vector<Sector*> postOrderStack;
    std::unordered_map<std::string , Sector*> sectorMap;
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* search(Sector* root , std::string sectorCode);
    void deleteTree(Sector* Root);

};

#endif // SPACESECTORBST_H
