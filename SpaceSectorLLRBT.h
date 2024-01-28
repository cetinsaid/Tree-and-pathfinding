#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <unordered_map>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    Sector * rotateRight(Sector* sector);
    Sector * rotateLeft(Sector* sector);
    void flipColor(Sector* sector);
    Sector* insert(Sector* &root, Sector* newSector);
    std::unordered_map<std::string , Sector* > sectorMap;
    Sector* search(Sector* Root, std::string sectorCode);
    Sector* searchBySector(Sector* Root, Sector* sector);
    void testPath(Sector* Root , Sector* sectorToFind , std::vector<Sector*> & path);
    Sector* test123(Sector* Root , Sector* earth , std::string destination , Sector* &destSec , std::vector<Sector*> & path , Sector* & parent);

    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    void deleteTree(Sector* Root);
};

#endif // SPACESECTORLLRBT_H
