#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Node
{
    char data;
    struct Node *childL = NULL;
    struct Node *childR = NULL;
};

void insertNode(struct Node* node, char data)
{
    if (node->data != data)
    {
        if (node->data > data)
        {
            if(node->childL == NULL){
                struct Node* temp= new Node();
                temp->data = data;
                node->childL = temp;
                return;
            }else{
                node = node->childL;
                insertNode(node,data);
            }
        }else if (node->data < data){
            if(node->childR == NULL){
                struct Node* temp= new Node();
                temp ->data = data;
                node->childR = temp;
                return;
            }else{
                node = node->childR;
                insertNode(node,data);
            }
        }
    }
    return;
}

struct Node *setup()
{
    ifstream file;
    file.open("binary_tree.txt");
    string text;
    getline(file, text);
    struct Node *root = new Node();
    root->data = text[0];
    for (int index = 2; index < text.length(); index +=2)
    {
        insertNode(root, text[index]);
    }
    file.close();
    return root;
}
vector<char> familyVector(struct Node* node, char data){
    vector<char> familyVectorV;
    if (data == node->data){
        familyVectorV.push_back(data);
        return familyVectorV;
    }else{
        familyVectorV.push_back(node->data);
        if (data < node->data){
            if (node->childL == NULL){
                return familyVectorV;
            }else{
                vector<char> temp = familyVector(node->childL,data);
                familyVectorV.insert(familyVectorV.end(),temp.begin(),temp.end());
            }
        }else if (data > node->data){
            if (node->childR==NULL){
                return familyVectorV;
            }else{
                vector<char> temp = familyVector(node->childR,data);
                familyVectorV.insert(familyVectorV.end(),temp.begin(),temp.end());
            }
        }
    }
    return familyVectorV;
}
void findLCA(struct Node* root,char x,char y){
    vector<char> vector1 = familyVector(root,x);
    vector<char> vector2 = familyVector(root,y);
    int counter =0;
    while(vector1[counter]==vector2[counter]){
        counter++;
        if (counter >= vector1.size() || counter >= vector2.size())
            break;
    }
    if(counter!=0 && (vector1.back()!='\0'&&(vector2.back()!='\0'))){
        counter--;
        cout << vector1[counter] << " is the lowest common ancestor." << endl;
    }else{
        cout << "Lowest common ancestor could not be found." << endl;
    }
}
int main()
{
    struct Node *rootNode = setup();
    findLCA(rootNode,'j','o');
}