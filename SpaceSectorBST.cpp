#include "SpaceSectorBST.h"
#include "fstream"
#include "cmath"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    deleteTree(root);
    // Free any dynamically allocated memory in this class.
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    std::ifstream sectorFile(filename);
    std::string line;
    if(sectorFile.is_open()){
        std::string dummy;
        std::getline(sectorFile, dummy);
        while(std::getline(sectorFile,line)){
            std::vector<int> index;
            for (int i = 0; i < line.size(); ++i) {
                if(line[i] == ','){
                    index.push_back(i);
                }
            }
            int x = std::stoi(line.substr(0 , index[0]));
            int y = std::stoi(line.substr(index[0] + 1 , index[1] - index[0] -1));
            int z = std::stoi(line.substr(index[1] +1));
            insertSectorByCoordinates(x,y,z);

        }
    }
//    insertVector();
//    for (int i = 0; i < sectors.size(); ++i) {
//        std::cout << sectors[i]->x << " " << sectors[i]->y << " " << sectors[i]->z << " "<< sectors[i]->sector_code <<  std::endl;
//    }
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    double eucDis = std::sqrt(std::pow(x,2) + std::pow(y , 2) + std::pow(z ,2));
    Sector* sector = new Sector(x, y, z);
    sector->distance_from_earth = eucDis;
    sector->sector_code += std::to_string(static_cast<int>(std::floor(eucDis)));
    if(x>0){
        sector->sector_code += "R";
    }else if(x <0 ){
        sector->sector_code += "L";
    }else{
        sector->sector_code += "S";
    }

    if(y>0){
        sector->sector_code += "U";
    }else if(y <0 ){
        sector->sector_code += "D";
    }else{
        sector->sector_code += "S";
    }

    if(z>0){
        sector->sector_code += "F";
    }else if(z <0 ){
        sector->sector_code += "B";
    }else{
        sector->sector_code += "S";
    }

    insertSectors(root , sector);

    // Instantiate and insert a new sector into the space sector BST map according to the
    // coordinates-based comparison criteria.
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    std::vector<std::string> path;
    Sector* temp = root;
    Sector* removeSec = search(root,sector_code);
    if(removeSec != nullptr){
        deleteSector(temp ,removeSec);
    }





    // TODO: Delete the sector given by its sector_code from the BST.
}

void SpaceSectorBST::displaySectorsInOrder() {
    std::vector<Sector*> stack;
    Sector* inOrder = root;
    Sector* current = inOrder;
    std::cout << "Space sectors inorder traversal:" << std::endl;
    while (!stack.empty() || current != nullptr){
        if(current == nullptr){
            current = stack[stack.size()-1];
            stack.pop_back();
            std::cout << current->sector_code << std::endl;
            current = current->right;

        }else{
            stack.push_back(current);
            current = current->left;
        }
    }
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in-order and print the sectors
    // to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:" << std::endl;
    std::vector<Sector*> stack;
    Sector* preOrder = root;
    if(preOrder != nullptr){
        stack.push_back(preOrder);
    }
    while(!stack.empty()){
        Sector* top = stack[stack.size() -1];
        std::cout << top->sector_code << std::endl;
        stack.pop_back();
        if(top->right != nullptr){
            stack.push_back(top->right);
        }
        if(top->left != nullptr){
            stack.push_back(top->left);
        }
    }
    std::cout << std::endl;

    // TODO: Traverse the space sector BST map in pre-order traversal and print
    // the sectors to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPostOrder() {
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
               std::cout << temp->sector_code << std::endl;
               prev = temp;
               stack.pop_back();
           }
       }
   }
    std::cout << std::endl;
    // TODO: Traverse the space sector BST map in post-order traversal and print
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* wantedSector = search(root,sector_code);
    if(wantedSector != nullptr){
        pathTest(root , wantedSector , path);
    }
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
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

Sector * SpaceSectorBST::insertSectors(Sector* rootTest , Sector* insertNode) {
    if(root == nullptr){
        root = insertNode;
    }
    if(rootTest == nullptr){
        return insertNode;
    }
    else{
        if(*insertNode > *rootTest){
            rootTest->right = insertSectors(rootTest->right , insertNode);
        }else{
            rootTest->left = insertSectors(rootTest->left , insertNode);
        }
    }
    return rootTest;
}


Sector *SpaceSectorBST::deleteSector(Sector *rootTest, Sector *deleteNode) {
    if(rootTest == nullptr){
        return rootTest;
    }
    else if(*deleteNode > * rootTest && *deleteNode != *rootTest){
        rootTest->right = deleteSector(rootTest->right , deleteNode );
        return rootTest;
    }
    else if(!(*deleteNode > *rootTest) && *deleteNode != *rootTest){
        rootTest->left = deleteSector(rootTest->left , deleteNode);
        return rootTest;
    }
    else{
        if(rootTest->left == nullptr && rootTest->right != nullptr){
            Sector* temp = rootTest->right;
            bool isRoot = (*rootTest == *root);
            delete rootTest;
            if(isRoot){
                root = temp;
            }
            return temp;
        }
        else if(rootTest->left != nullptr && rootTest->right == nullptr){
            Sector* temp = rootTest->left;
            bool isRoot = (*rootTest == *root);
            delete rootTest;
            if(isRoot){
                root = temp;
            }
            return temp;
        }
        else if(rootTest->left == nullptr && rootTest->right == nullptr){
            delete rootTest;
            if(*rootTest == *root){
                root = nullptr;
            }
            return nullptr;
        }
        else{
            Sector* firstRight = rootTest->right;
            Sector* furthestLeft = nullptr;
            if(firstRight->left != nullptr){
                furthestLeft = firstRight->left;
                while(firstRight->left->left != nullptr){
                    furthestLeft = furthestLeft->left;
                    firstRight = firstRight->left;
                }
                bool isRoot = (*rootTest == *root);
                Sector* temp  = furthestLeft;
                if(furthestLeft->right != nullptr){
                    firstRight->left = furthestLeft->right;
                }else{
                    firstRight->left = nullptr;
                }
                temp->right = rootTest->right;
                temp->left = rootTest->left;
                delete rootTest;
                if(isRoot){
                    root = temp;
                }
                return temp;
            }else{
                bool isRoot = (*rootTest == *root);
                Sector* temp = firstRight;
                temp->left = rootTest->left;
                if(isRoot){
                    root = temp;
                }
                return temp;
            }
        }

    }

    return rootTest;
}

Sector *SpaceSectorBST::search(Sector *Root, std::string sectorCode) {
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

Sector *SpaceSectorBST::pathTest(Sector *Root, Sector *wanted , std::vector<Sector*> & sector) {
    if((*wanted > *Root) && *wanted != *Root){
        sector.push_back(Root);
        Root->right = pathTest(Root->right , wanted , sector);
    }
    else if(!(*wanted > *Root) && *wanted != *Root){
        sector.push_back(Root);
        Root->left = pathTest(Root->left , wanted , sector);
    }
    else{
        sector.push_back(Root);
    }
    return Root;

}

void SpaceSectorBST::deleteTree(Sector *Root) {
    if(Root == nullptr){
        return;
    }
    deleteTree(Root->left);
    deleteTree(Root->right);
    delete Root;

}
