#include "../include/ioManager.h"

int *IOManager::countFrequencies(std::ifstream &input)
{
    int *ascii = new int[128];
    char c = '\0';

    while (input.get(c)) {
        if ((int) c == 10)
            continue;

        ascii[(int) c] +=1;
    }
    
    for (int i = 0; i < 128; ++i) {
       if(ascii[i] != 0){
        c = i;
        std::cout << c << " " << ascii[i] << std::endl;
       }
    }
    return ascii;
}

void IOManager::readFile(std::ifstream &input)
{
    int *ascii = countFrequencies(input);
    std::vector<Node*> orderedNodes;

    for (int i = 0; i < 128; ++i) {
        if (ascii[i] != 0) {
            char character = i;
            Node *node = new Node(ascii[i], character);
            insertOrd(orderedNodes, node, pred);
        }
    }

    insertOrd(orderedNodes, new Node(1, '$'), pred);

    tree = new HuffmanTree(orderedNodes);
    tree->printTree();
    tree->fillMap();

    delete ascii;
}

/* TODO: get the string generated by the preOrder() method from the tree,
   compact it like it was done with the text in the compact() method and insert
   it in the beginning of the file, using '$' or some other char as the
   delimiter between where the tree starts and where the text starts */
void IOManager::encodeTree(std::ofstream &output)
{
    std::string treeString = tree->preOrder();
    std::string encodedString = "";
    std::istringstream input(treeString);
    
    
    std::cout << tree->preOrder() << std::endl;

    char c = '\0';

    while(input.get(c)){
        if(c != '0' and c != '1')
            encodedString += tree->findLetterPath(c);
        else 
            encodedString += c;
    }

    std::cout << encodedString << std::endl;
    
    for (size_t i = 0; i < encodedString.size(); ++i) {
        if (encodedString[i] == '1') {
            c = c << 1;
            c += 1;
        }
        else {
            c = c << 1;
        }

        /*if(i == encodedString.size()) {
       
            if( i % 8 == 0){
                while(++i % 8 != 0){
                    c << 1;
                std::cout << " PORRA" << std::endl;
                }

            }
            output << c;
        }*/

        /*else*/
        if ((i != 0 and (i + 1) % 8 == 0) or (i + 1) == encodedString.size()) {
            output << c;
            c = '\0';
        }
        
    }
}

void IOManager::compact(std::ifstream &input, std::ofstream &output)
{
    std::cout << tree->preOrder() << std::endl;

    // reset file stream
    input.clear();
    input.seekg(0, std::ios::beg);

    char c = '\0';
    std::string encodedString = "";

    while (input.get(c))
        encodedString += tree->findLetterPath(c);

    std::cout << encodedString << std::endl;

    c = '\0';
    for (size_t i = 0; i < encodedString.size(); ++i) {
        if (encodedString[i] == '1') {
            c = c << 1;
            c += 1;
        }
        else {
            c = c << 1;
        }

        if ((i != 0 and (i + 1) % 8 == 0) or (i + 1) == encodedString.size()) {
            output << c;
            c = '\0';
        }
    }
}