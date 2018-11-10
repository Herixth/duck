#ifndef TRAIN_ID3
#define TRAIN_ID3

#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <map>

const double Ln2 = log(2);

//#define DEBUG

/**
 * @Brief store the attribute(col) in the sample
 */
class Attr {
public:
    int colIndex;   // which col
    int typeNum;    // how many types of the attr
    double conEntroy, InforGain;
    std::string attribute; 
    std::vector<std::string> attriValue;
    std::map<std::string, double> typeEntropy;   // init 0.0
    std::map<std::string, unsigned int> typeCnt; // from 1 begin
    std::map<std::string, std::map<std::string, unsigned int> > attriValue_to_result;

    Attr(int col = 0, std::string str = ""):
        colIndex(col), typeNum(0), conEntroy(0), InforGain(0), attribute(str) { }
    ~Attr() { }
};

/**
 * @Brief define the node infor
 */
class TreeNode {
public:
    std::string attri;    // current attribute Infor
    std::map<std::string, TreeNode *> attri_To_Children;
    std::vector<Attr> Table;
    int rowNum, colNum;
    double InforGain;
    int biggestIGidx;
    bool isLeaf;

    TreeNode(): biggestIGidx(0), InforGain(0.0),
    isLeaf(true), rowNum(0), colNum(0) { }
    ~TreeNode() { }

    void chooseIG();
    void clearCol();
};

/**
 * @Brief define the decision tree
 */
class DecisionTree {
public:
    DecisionTree() { root = new TreeNode; }
    ~DecisionTree() { removeAll(root); }

    void BuildTree() { builder(root); }
    void ReadTable(std::ifstream &);
    void testTree() { testTreeHelp(root); }
    void printTree() { printTreeHelp(root, "NULL"); };
private:
    void removeAll(TreeNode *);
    void printSample(TreeNode *);
    void computeEntropyFir(TreeNode *);
    void computeEntropySec(TreeNode *);
    void builder(TreeNode *);
    void processSample(TreeNode *);
    void divideChild(TreeNode *);
    void testTreeHelp(TreeNode *);
    void printTreeHelp(TreeNode *, std::string);

    TreeNode *root;
};

#endif // !TASK3


void DecisionTree::ReadTable(std::ifstream &Input) {
    std::string line;
    // Process headline
    std::getline(Input, line);
    int front = 0, last = 0;
    while (front < line.length() && line.find_first_not_of(' ', front) != std::string::npos) {
        front = line.find_first_not_of(' ', front);
        last  = line.find_first_of(' ', front) != std::string::npos ?
                line.find_first_of(' ', front) : line.length();
        root->Table.push_back(Attr(root->colNum++, line.substr(front, last - front)));
        front = last + 1;
    }
    
    // Process infor
    int cnt = 0;
    while (Input >> line) {
        root->Table[(cnt++) % root->colNum].attriValue.push_back(line);
    }
    root->rowNum = (*root->Table.begin()).attriValue.size();
}

void DecisionTree::printTreeHelp(TreeNode *root, std::string fat = "NULL") {
    if (root->isLeaf) {
        std::cout << "Leaf Node: " << std::endl;
        std::cout << "    >> father: " << fat << std::endl;
        std::cout << "    >> result: " << root->attri << std::endl;
        std::cout << "------------------------------------" << std::endl;
        return;
    }

    std::cout << "Attribute Node: " << std::endl;
    std::cout << "    >> father: " << fat << std::endl;
    std::cout << "    >> attribute: " << root->attri << std::endl;
    std::map<std::string, TreeNode *>::iterator iter = root->attri_To_Children.begin();
    for (; iter != root->attri_To_Children.end(); iter++) {
        std::cout << "    >> attribute value: " << (*iter).first << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
    for (iter = root->attri_To_Children.begin(); 
        iter != root->attri_To_Children.end(); iter++) {
        printTreeHelp((*iter).second, (*iter).first);
    }
}

void DecisionTree::testTreeHelp(TreeNode *root) {
    const std::string quit = "quit";
    const std::string prev = "prev";
    std::string op = "";
    TreeNode *tranv = root;
    while (op != quit && op != prev) {
        if (tranv->isLeaf) {
            std::cout << std::endl << ">> " << tranv->Table[tranv->colNum - 1].attribute << ": " << tranv->attri << std::endl;
            std::cout << "----------- test over --------------" << std::endl;
            return;
        }
        std::cout << "current attribute is " << tranv->attri << " Input:"<< std::endl;
        std::map<std::string, TreeNode *>::iterator iter = tranv->attri_To_Children.begin();
        for (; iter != tranv->attri_To_Children.end(); iter++) {
            std::cout << "----> " << (*iter).first << std::endl;
        }
        std::cout << ">> ";
        getline(std::cin, op);
        for (iter = tranv->attri_To_Children.begin(); iter != tranv->attri_To_Children.end(); iter++) {
            if (op == (*iter).first) {
                testTreeHelp((*iter).second);
                break;
            }
        }
    }
}

void TreeNode::chooseIG() {
    for (int col = 1; col < colNum - 1; col++) {
        if (InforGain < Table[col].InforGain) {
            InforGain = Table[col].InforGain;
            attri = Table[col].attribute;
            biggestIGidx = col;
        }
    }
#ifdef DEBUG
    std::cout << "Node attribute: <" << attri << "> with IG: " << InforGain << std::endl;
    std::cout << "------------------------------------" << std::endl;
#endif // DEBUG
}

void TreeNode::clearCol() {
    this->attri.clear(); this->attri_To_Children.clear();
    this->InforGain = 0.0, this->isLeaf = true, this->biggestIGidx = 0;
    for (int col = 0; col < colNum; col++) {
        Table[col].attriValue.clear();
        Table[col].attriValue_to_result.clear();
        Table[col].conEntroy = 0.0, Table[col].InforGain = 0.0;
        Table[col].typeCnt.clear(), Table[col].typeEntropy.clear();
        Table[col].typeNum = 0;
    }
}

// self test function
void DecisionTree::removeAll(TreeNode *root) {
    std::map<std::string, TreeNode *>::iterator iter = root->attri_To_Children.begin();
    for (; iter != root->attri_To_Children.end(); iter ++) {
        removeAll((*iter).second);
    }
    delete root;
}

void DecisionTree::printSample(TreeNode *root) {
    for (int col = 0; col < root->colNum; col++)
        std::cout << root->Table[col].attribute << " ";
    std::cout << std::endl;
    for (int row = 1; row <= root->rowNum; row++) {
        for (int col = 0; col < root->colNum; col++) {
            std::cout << root->Table[col].typeCnt[root->Table[col].attriValue[row - 1]] << " ";
        }
        std::cout << std::endl;
    }

    for (int row = 0; row < root->rowNum; row++) {
        for (int col = 0; col < root->colNum; col++) {
            std::cout << root->Table[col].attriValue[row] << " ";
        }
        std::cout << std::endl;
    }

}

void DecisionTree::computeEntropyFir(TreeNode *root) {
    // Entropy(s)
    std::map<std::string, unsigned int>::iterator iter = root->Table[root->colNum - 1].typeCnt.begin();
    for (; iter != root->Table[root->colNum - 1].typeCnt.end(); iter++) {
        double part = (*iter).second * 1.0 / root->rowNum;
        root->Table[root->colNum - 1].conEntroy += part ? -part * log(part) / Ln2 : 0;
    }

#ifdef DEBUG
    std::cout << "Entropy(" << root->Table[root->colNum - 1].attribute << ") = ";
    std::cout << root->Table[root->colNum - 1].conEntroy << std::endl << std::endl;
#endif // DEBUG
}

void DecisionTree::computeEntropySec(TreeNode *root) {
    // for every attribute, col = 0 is index jump
    for (int col = 1; col < root->colNum - 1; col++) {
        // tranverse all rows about current col and last col
        for (int row = 0; row < root->rowNum; row++) {
            std::string curr = root->Table[col].attriValue[row];
            std::string last = root->Table[root->colNum - 1].attriValue[row];
            if (root->Table[col].attriValue_to_result.find(curr) != root->Table[col].attriValue_to_result.end()) {
                if (root->Table[col].attriValue_to_result[curr].find(last) != root->Table[col].attriValue_to_result[curr].end())
                    root->Table[col].attriValue_to_result[curr][last]++;
                else
                    root->Table[col].attriValue_to_result[curr][last] = 1;
            }
            else {
                root->Table[col].attriValue_to_result[curr] = std::map<std::string, unsigned int> { { last, 1 } };
            }
        }
        // add none result for overcast
        std::map<std::string, unsigned int>::iterator incer;
        for (incer = root->Table[root->colNum - 1].typeCnt.begin(); 
            incer != root->Table[root->colNum - 1].typeCnt.end(); incer++) {
            std::map<std::string, std::map<std::string, unsigned int> >::iterator snter;
            for (snter = root->Table[col].attriValue_to_result.begin(); 
                snter != root->Table[col].attriValue_to_result.end(); snter++) {
                if ((*snter).second.find((*incer).first) == (*snter).second.end()) {
                    (*snter).second[(*incer).first] = 0;
                }
            }
        }

        //computer entropy for all type in current attribute
        std::map<std::string, std::map<std::string, unsigned int> >::iterator iter;
        for (iter = root->Table[col].attriValue_to_result.begin(); 
            iter != root->Table[col].attriValue_to_result.end(); iter++) {
            std::string curr = (*iter).first;
            std::map<std::string, unsigned int>::iterator snter;
            for (snter = (*iter).second.begin(); snter != (*iter).second.end(); snter++) {
                double part = (*snter).second * 1.0 / root->Table[col].typeCnt[(*iter).first];
                root->Table[col].typeEntropy[curr] += part ? -part * log(part) / Ln2 : 0;
            }
        }
        //computer conditional entropy and IG
        std::map<std::string, double>::iterator snter = root->Table[col].typeEntropy.begin();
        for (; snter != root->Table[col].typeEntropy.end(); snter++) {
            root->Table[col].conEntroy += root->Table[col].typeCnt[(*snter).first] * (*snter).second / root->rowNum;
            root->Table[col].InforGain = root->Table[root->colNum - 1].conEntroy - root->Table[col].conEntroy;
        }

#ifdef DEBUG
        //test print
        std::cout << "attribute: " << root->Table[col].attribute << std::endl;
        for (iter = root->Table[col].attriValue_to_result.begin();
            iter != root->Table[col].attriValue_to_result.end(); iter++) {
            std::cout << "    >> " << (*iter).first << std::endl;
            std::string curr = (*iter).first;
            std::map<std::string, unsigned int>::iterator snter;
            for (snter = (*iter).second.begin(); snter != (*iter).second.end(); snter++) {
                std::cout << "       >> " << (*snter).first << ": " << (*snter).second << std::endl;
            }
        }
        std::map<std::string, double>::iterator iters = root->Table[col].typeEntropy.begin();
        for (; iters != root->Table[col].typeEntropy.end(); iters ++) {
            std::cout << "    ->Entropy(" << (*iters).first << ") = " << (*iters).second << std::endl;
        }
        std::cout << "->Entropy(" << root->Table[root->colNum - 1].attribute << "|" << root->Table[col].attribute << ") = ";
        std::cout << root->Table[col].conEntroy << std::endl;
        std::cout << "->IG(" << root->Table[root->colNum - 1].attribute << "|" << root->Table[col].attribute << ") = ";
        std::cout << root->Table[col].InforGain << std::endl << std::endl;
#endif // DEBUG
    }
}

void DecisionTree::processSample(TreeNode *root) {
    std::vector<Attr>::iterator iter = root->Table.begin();
    for (; iter != root->Table.end(); iter ++) { //col
        std::vector<std::string>::iterator snter = (*iter).attriValue.begin();
        for (; snter != (*iter).attriValue.end(); snter ++) { //row
            if ((*iter).typeCnt.find(*snter) != (*iter).typeCnt.end()) {
                (*iter).typeCnt[*snter] ++;
            }
            else {
                (*iter).typeEntropy[*snter] = 0.0;
                (*iter).typeCnt[*snter] = 1; (*iter).typeNum++;
            }
        }
    }
}

void DecisionTree::builder(TreeNode *root) {
    // Ending condition
    // if the same, isLeaf init true
    std::vector<std::string>::iterator iter = root->Table[root->colNum - 1].attriValue.begin();
    for (; iter + 1 != root->Table[root->colNum - 1].attriValue.end(); iter++) {
        if ((*iter) != (*(iter + 1))) {
            root->isLeaf = false; break;
        }
    }
    if (root->isLeaf) {   // only if result all same
        root->attri = (* root->Table[root->colNum - 1].attriValue.begin());
        return;
    }

    // process form
    processSample(root);
    
    // compute entropy
    computeEntropyFir(root);
    computeEntropySec(root);

    // choose the biggest IG
    // from col 1 -> colNum - 2
    root->chooseIG();

    if (root->rowNum <= 2) {  //only two types trainning
        std::map<std::string, std::map<std::string, unsigned int> >::iterator iter;
        for (iter = root->Table[root->biggestIGidx].attriValue_to_result.begin();
            iter != root->Table[root->biggestIGidx].attriValue_to_result.end(); iter++) {
            root->attri_To_Children[(*iter).first] = new TreeNode;
            unsigned int numberPivot = 0;
            std::map<std::string, unsigned int>::iterator snter = (*iter).second.begin();
                //(*(*iter).second.begin()).first;
            for (; snter != (*iter).second.end(); snter++) {
                if ((*snter).second >= numberPivot) {
                    root->attri_To_Children[(*iter).first]->attri = (*snter).first;
                    numberPivot = (*snter).second;
                }
            }
        }
        return;
    }

    divideChild(root);
}

void DecisionTree::divideChild(TreeNode *root) {
    // for every attribute value of the key attribute
    std::map<std::string, unsigned int>::iterator iter;
    for (iter = root->Table[root->biggestIGidx].typeCnt.begin();
        iter != root->Table[root->biggestIGidx].typeCnt.end(); iter++) {
        std::string curr = (*iter).first;   // current attribute
        root->attri_To_Children[curr] = new TreeNode;
        root->attri_To_Children[curr]->colNum = root->colNum;
        root->attri_To_Children[curr]->rowNum = (*iter).second;
        root->attri_To_Children[curr]->Table.assign(root->Table.begin(), root->Table.end());
        root->attri_To_Children[curr]->clearCol();

        // row -> rowNum
        for (int row = 0; row < root->rowNum; row++) {
            if (root->Table[root->biggestIGidx].attriValue[row] == curr) {
                // col -> colNum  copy
                for (int col = 0; col < root->colNum; col++) {
                    root->attri_To_Children[curr]->Table[col].attriValue.push_back(
                        root->Table[col].attriValue[row]
                    );
                }
            }
        }
        builder(root->attri_To_Children[curr]);
    }
}
