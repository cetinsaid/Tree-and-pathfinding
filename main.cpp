#include "SpaceSectorBST.h"
#include "SpaceSectorLLRBT.h"
#include "kNN_DAT_Parser.h"
#include "kNN.h"
#include "KD_Tree.h"
#include "KDT_Node.h"
#include "kNN_Data.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char**argv) {
    std::string file = "C:\\Users\\said5\\CLionProjects\\Assignment4\\testsIO\\inputs\\sectors_1.dat";
    SpaceSectorLLRBT sectorLlrbt;
    sectorLlrbt.readSectorsFromFile(file);
    sectorLlrbt.displaySectorsPreOrder();
    std::vector<Sector*> stellarPath = sectorLlrbt.getStellarPath("89RDF");
    sectorLlrbt.printStellarPath(stellarPath);
//    SpaceSectorBST sector_map_BST;
//    sector_map_BST.readSectorsFromFile(file);
//    sector_map_BST.displaySectorsInOrder();
//    sector_map_BST.deleteSector("111RUB");
//    sector_map_BST.deleteSector("106LDF");
//    sector_map_BST.deleteSector("112RDB");
//    sector_map_BST.deleteSector("81RUB");
//    sector_map_BST.deleteSector("117RUF");
//
//
//    cout << "\n\n\n\n";
//    sector_map_BST.displaySectorsInOrder();



//    std::string sectorFile("C:\\Users\\said5\\CLionProjects\\Assignment4\\sampleIO\\sectors.dat");
//    std::string sectorFile1("C:\\Users\\said5\\CLionProjects\\Assignment4\\sampleIO\\sectors_sorted.dat");
//    std::string knn("C:\\Users\\said5\\CLionProjects\\Assignment4\\sampleIO\\simple_planet_train.dat");
//    string TESTS_PATH = "testsIO/inputs/sectors_1.dat";
//    string TESTS_PATH1 = "testsIO/inputs/sectors_2.dat";
//    string TESTS_PATH2 = "testsIO/inputs/sectors_3.dat";
//
//
//
//
//    //************ Task 1: Space Sector Mapping ***********//
//    SpaceSectorBST sector_map_BST;
//    sector_map_BST.readSectorsFromFile(TESTS_PATH);
////    sector_map_BST.deleteSector("107LDB");
////    sector_map_BST.deleteSector("111LUF");
////    sector_map_BST.deleteSector("144RUF");
////    sector_map_BST.deleteSector("124LDB");
////    sector_map_BST.deleteSector("118LUF");
////    sector_map_BST.deleteSector("118LUF");
////    sector_map_BST.deleteSector("93LUB");
////    sector_map_BST.deleteSector("59LUB");
//
////    sector_map_BST.deleteSector("18RUB");
////    sector_map_BST.deleteSector("37RUF");
////    sector_map_BST.displaySectorsPreOrder();
////    sector_map_BST.deleteSector("25RUS");
////    sector_map_BST.displaySectorsPreOrder();
////    sector_map_BST.deleteSector("45RDF");
////    sector_map_BST.deleteSector("43RDF");
////    sector_map_BST.deleteSector("70RUF");
////    sector_map_BST.displaySectorsInOrder();
////    sector_map_BST.displaySectorsPreOrder();
////    sector_map_BST.deleteSector("0SSS");
////    sector_map_BST.displaySectorsPreOrder();
//
////    sector_map_BST.deleteSector("0SSS");
//////    sector_map_BST.deleteSector("37RUF");
////    sector_map_BST.displaySectorsPostOrder();
////    sector_map_BST.displaySectorsInOrder();
//
//    std::vector<Sector*> stellar_path = sector_map_BST.getStellarPath("124RDF");
////    sector_map_BST.displaySectorsPreOrder();
//    sector_map_BST.printStellarPath(stellar_path);
//
//    cout << endl;
//
//    stellar_path = sector_map_BST.getStellarPath("121RDB");
//    sector_map_BST.printStellarPath(stellar_path);
////    sector_map_BST.deleteSector("37RUF");
//
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("23RDB");
//    sector_map_BST.printStellarPath(stellar_path);
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("89RDF");
//    sector_map_BST.printStellarPath(stellar_path);
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("71LUB");
//    sector_map_BST.printStellarPath(stellar_path);
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("106RDB");
//    sector_map_BST.printStellarPath(stellar_path);
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("66RUF");
//    sector_map_BST.printStellarPath(stellar_path);
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("0SSS");
//    sector_map_BST.printStellarPath(stellar_path);
//    cout << endl;
//    stellar_path = sector_map_BST.getStellarPath("128LDB");
//    sector_map_BST.printStellarPath(stellar_path);
//    //************ Task 2: Optimizing Space Sector Mapping ***********//
////    SpaceSectorLLRBT sector_map_LLRBT;
////    sector_map_LLRBT.readSectorsFromFile(TESTS_PATH);
////    sector_map_LLRBT.displaySectorsInOrder();
////    sector_map_LLRBT.displaySectorsPreOrder();
////    sector_map_LLRBT.displaySectorsPostOrder();
////
////    std::vector<Sector*> stellar_path_2 = sector_map_LLRBT.getStellarPath("31SUF");
////    sector_map_LLRBT.printStellarPath(stellar_path_2);
////
////    cout << endl;
////
////    stellar_path_2 = sector_map_LLRBT.getStellarPath("45RDF");
////    sector_map_LLRBT.printStellarPath(stellar_path_2);
////
////    cout << endl;
//    //************ BONUS Task 3: Planetary Classification System (for extra 20 pts.) ***********//
////
////    // get the filename from the 2nd command line arg
////    std::string trainingDataFileName = knn;
////
////    // Example:
////    // Create an instance of the kNN_Dat_Parser
////    kNN_Dat_Parser parser;
////    // Parse the dataset
////    Dataset data = parser.parse(trainingDataFileName);
////    int k = 2;
////    KNN knnClassifier(k, data.threshold);
////    knnClassifier.train(data);
////    // get the tree
////    KD_Tree tree = knnClassifier.tree;
////    // test instance
////    std::vector<double> testFeatures = {1.3232202558909871, 3.172770177200133, 18.57605415623152, 0.22339666018454057, 81.15184706218832, 695.926406517461, 0.9139624956958795};
////    Point testPoint(testFeatures, "");
////    // predict the label
////    int predictedLabel = knnClassifier.predict(testPoint); // Expected value = 0
    return 0;
}


