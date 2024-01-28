#include <cmath>
#include <stack>
#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    std::ifstream sectorFile(filename);
    std::string line;
    if(sectorFile.is_open()) {
        std::string dummy;
        std::getline(sectorFile, dummy);
        while (std::getline(sectorFile, line)) {
            std::vector<int> index;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ',') {
                    index.push_back(i);
                }
            }
            int x = std::stoi(line.substr(0, index[0]));
            int y = std::stoi(line.substr(index[0] + 1, index[1] - index[0] - 1));
            int z = std::stoi(line.substr(index[1] + 1));
//
//            int eucDis = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
//            Sector *sector = new Sector(x, y, z);
//            sector->distance_from_earth = eucDis;
//            sector->sector_code += std::to_string(eucDis);
//            if (x > 0) {
//                sector->sector_code += "R";
//            } else if (x < 0) {
//                sector->sector_code += "L";
//            } else {
//                sector->sector_code += "S";
//            }
//
//            if (y > 0) {
//                sector->sector_code += "U";
//            } else if (y < 0) {
//                sector->sector_code += "D";
//            } else {
//                sector->sector_code += "S";
//            }
//
//            if (z > 0) {
//                sector->sector_code += "F";
//            } else if (z < 0) {
//                sector->sector_code += "B";
//            } else {
//                sector->sector_code += "S";
//            }
//            sectorMap[sector->sector_code] = sector;
            insertSectorByCoordinates(x,y,z);
//            if(root == nullptr){
//                root = sector;
//                root->color = false;
//            }
//            else{
//                insert(root , sector);
//            }
        }
    }

    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    deleteTree(root);
    // TODO: Free any dynamically allocated memory in this class.
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    double eucDis = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    Sector *sector = new Sector(x, y, z);
    sector->distance_from_earth = eucDis;
    sector->sector_code += std::to_string(static_cast<int>(std::floor(eucDis)));
    if (x > 0) {
        sector->sector_code += "R";
    } else if (x < 0) {
        sector->sector_code += "L";
    } else {
        sector->sector_code += "S";
    }

    if (y > 0) {
        sector->sector_code += "U";
    } else if (y < 0) {
        sector->sector_code += "D";
    } else {
        sector->sector_code += "S";
    }

    if (z > 0) {
        sector->sector_code += "F";
    } else if (z < 0) {
        sector->sector_code += "B";
    } else {
        sector->sector_code += "S";
    }
    if(root == nullptr){
        root = sector;
        root->color = false;
    }else{
        insert(root , sector);
    }






    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    std::vector<Sector*> stack;
    Sector* inOrder = root;
    Sector* current = inOrder;
    std::cout << "Space sectors inorder traversal:" << std::endl;
    while (!stack.empty() || current != nullptr){
        if(current == nullptr){
            current = stack[stack.size()-1];
            stack.pop_back();
            if(current->color == 1){
                std::cout <<"RED" << " sector: " << current->sector_code << std::endl;
            }else{
                std::cout <<"BLACK" << " sector: " << current->sector_code << std::endl;

            }
            current = current->right;

        }else{
            stack.push_back(current);
            current = current->left;
        }
    }
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:" << std::endl;

    Sector* preOrder = root;
    std::vector<Sector*> stack;
    if(preOrder != nullptr){
        stack.push_back(preOrder);
    }
    while(!stack.empty()){
        Sector* top = stack[stack.size() -1];
        if(top->color == 1){
            std::cout <<"RED" << " sector: " << top->sector_code << std::endl;
        }else{
            std::cout <<"BLACK" << " sector: " << top->sector_code << std::endl;

        }
        stack.pop_back();
        if(top->right != nullptr){
            stack.push_back(top->right);
        }
        if(top->left != nullptr){
            stack.push_back(top->left);
        }
    }
    std::cout << std::endl;
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:" << std::endl;
    Sector* current = root;
    std::vector<Sector*> stack;
    Sector* prev = nullptr;
    while(!stack.empty() || current != nullptr){
        if(current != nullptr){
            stack.push_back(current);
            current = current->left;
        }
        else{
            Sector* temp = stack[stack.size()-1];
            if(temp->right != nullptr && temp->right != prev){
                current = temp->right;
            }
            else{
                if(temp->color == 1){
                    std::cout <<"RED" << " sector: " << temp->sector_code << std::endl;
                }else{
                    std::cout <<"BLACK" << " sector: " << temp->sector_code << std::endl;

                }
                prev = temp;
                stack.pop_back();
            }
        }
    }
    std::cout << std::endl;


    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* tempEarth = new Sector(0,0,0);
    Sector* tempDest = nullptr;
    Sector* parent = nullptr;
    Sector* earth = test123(root , tempEarth , sector_code , tempDest , path , parent);
    if(tempDest == nullptr){
        Sector* temp = earth;
        Sector* dest = search(temp , sector_code);
        if(dest != nullptr){
            while(*temp != *dest){
                if(*dest > *temp){
                    path.push_back(temp);
                    temp = temp->right;
                }
                else{
                    path.push_back(temp);
                    temp = temp->left;
                }
            }
            path.push_back(temp);
        }
    }
    else{
        std::vector<Sector*> revDest;
        Sector* temp = earth;
        Sector* dest = tempDest;
        while(*temp != *parent){
            path.push_back(temp);
            temp = temp->parent;
        }
        path.push_back(parent);
        while(*dest != *parent){
            revDest.push_back(dest);
            dest = dest->parent;
        }
        for (int i = revDest.size()-1; i >= 0  ; --i) {
            path.push_back(revDest[i]);
        }

    }
    delete tempEarth;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    if(path.size() != 0){
        std::cout << "The stellar path to Dr. Elara: ";
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i]->sector_code;
            if(i != path.size()-1){
                std::cout << "->";
            }

        }
    }
    else{
        std::cout << "A path to Dr. Elara could not be found.";
    }
    std::cout << std::endl;
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}

Sector * SpaceSectorLLRBT::rotateRight(Sector *sector) {
    Sector* left = sector->left;
    if(sector != root){
        left->parent = sector->parent;
    }else{
        left->parent = nullptr;
    }
    if(left->right != nullptr){
        left->right->parent = sector;
    }
    sector->left = left->right;
    left->right = sector;
    sector->parent = left;
    sector->color = left->color;
    if(left->parent == nullptr){
        left->color = false;
    }else{
        left->color = true;
    }
    return left;
}

Sector * SpaceSectorLLRBT::rotateLeft(Sector *sector) {
    Sector* right = sector->right;
    if(sector != root){
        right->parent = sector->parent;
    }else{
        right->parent = nullptr;
    }
    if(right->left != nullptr){
        right->left->parent = sector;
    }
    sector->right = right->left;
    right->left = sector;
    sector->parent = right;
    right->color = sector->color;
    sector->color = true;
    return right;
}

void SpaceSectorLLRBT::flipColor(Sector *sector) {
    if(sector != root){
        sector->color = true;
    }
    sector->right->color = false;
    sector->left->color = false;

}

Sector *SpaceSectorLLRBT::insert(Sector *&Root, Sector *newSector) {
    if(root == nullptr){
        root = newSector;
        root->color = false;
    }
    else if(Root == nullptr){
        return  newSector;
    }
    else if(*newSector > *Root){
        Root->right = insert(Root->right , newSector);
        Root->right->parent = Root;
    } else{
        Root->left = insert(Root->left , newSector);
        Root->left->parent = Root;
    }

    if((Root->right && Root->right->color) &&  (!Root->left || !Root->left->color)){
        Root = rotateLeft(Root);
    }
    if((Root->left &&  Root->left->color) && (Root->left->left && Root->left->left->color)){
        Root = rotateRight(Root);
    }
    if((Root->left && Root->left->color) && (Root->right && Root->right->color)){
        flipColor(Root);
    }
    return Root;
}

Sector *SpaceSectorLLRBT::search(Sector *Root, std::string sectorCode) {
    if(Root == nullptr){
        return nullptr;
    }
    else if(Root->sector_code == sectorCode){
        return Root;
    }
    else{
        Sector* left = search(Root->left,sectorCode);
        Sector* right = search(Root->right, sectorCode);
        if(left != nullptr){
            return left;
        }else if(right != nullptr){
            return right;
        }else{
            return nullptr;
        }
    }
}

void SpaceSectorLLRBT::testPath(Sector *Root, Sector *sectorToFind , std::vector<Sector*> & path) {
    if(*Root == *sectorToFind){
        path.push_back(sectorToFind);
        return;
    }
    else if(*sectorToFind > *Root){
        path.push_back(Root);
        testPath(Root->right , sectorToFind , path);
    }
    else{
        path.push_back(Root);
        testPath(Root->left , sectorToFind , path);
    }
}

Sector *SpaceSectorLLRBT::searchBySector(Sector *Root, Sector *sector) {
    if(Root == nullptr){
        return nullptr;
    }
    if(*Root == *sector){
        return sector;
    }
    else if(*sector > *Root ){

    }
    return nullptr;
}

Sector *SpaceSectorLLRBT::test123(Sector *Root, Sector *earth, std::string destination , Sector* &destSec , std::vector<Sector*> & path , Sector* & parent) {
    if(*Root == *earth){
        return Root;
    }
    else if(*earth > *Root){
        if(destSec == nullptr){
            destSec = search(Root->left , destination);
            if(destSec != nullptr){
                parent = Root;
            }
        }
        return test123(Root->right , earth , destination, destSec ,path , parent);
    }
    else{
        if(destSec == nullptr){
            destSec = search(Root->right , destination);
            if(destSec != nullptr){
                parent = Root;
            }
        }
        return test123(Root->left , earth , destination, destSec , path , parent);
    }
}

void SpaceSectorLLRBT::deleteTree(Sector *Root) {
    if(Root == nullptr){
        return;
    }
    deleteTree(Root->left);
    deleteTree(Root->right);
    delete Root;

}
