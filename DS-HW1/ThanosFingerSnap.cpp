#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int toBeDeletedHeight;
vector<int>stree;
vector<int>vtree;
int countS, countV;

class ThanosBST {
private:
    int data;
    ThanosBST* right;
    ThanosBST* left;
public:
    ThanosBST();
    ThanosBST(int);
    ThanosBST* insert(ThanosBST* root, int data);
    ThanosBST* deleteNode(ThanosBST* root, int key);
    void postOrder(ThanosBST* root, int thanos);
    int height(ThanosBST* node);
    void printGivenLevel(ThanosBST* root, int level, int meaxheight);
    void inorderS(ThanosBST* root);
    void preorderV(ThanosBST* root);
    void printSV(ThanosBST* root);
};

ThanosBST::ThanosBST() :data(0), left(NULL), right(NULL) {} //default constructor
ThanosBST::ThanosBST(int value) {
    data = value;
    left = right = NULL;
}

ThanosBST* ThanosBST::insert(ThanosBST* root, int data) {

    if (!root)
    {
        // Insert the first node, if root is NULL. 
        return new ThanosBST(data);
    }

    // Insert data. 
    if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    else
    {
        root->left = insert(root->left, data);
    }
    return root;
}

ThanosBST* ThanosBST::deleteNode(ThanosBST* root, int key) {
    if (!root) {
        return root;
    }
    if (root->data > key) {
        root->left = deleteNode(root->left, key);
        return root;
    }
    else if (root->data < key) {
        root->right = deleteNode(root->right, key);
        return root;
    }
    if (root->left == NULL) {
        ThanosBST* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        ThanosBST* temp = root->left;
        delete root;
        return temp;
    }

    // If both children exist
    else {

        ThanosBST* succParent = root;

        // Find successor
        ThanosBST* succ = root->left;
        while (succ->right != NULL) {
            succParent = succ;
            succ = succ->right;
        }
        if (succParent != root)
            succParent->right = succ->left;
        else
            succParent->right = succ->left;

        // Copy Successor Data to root
        root->data = succ->data;

        // Delete Successor and return root
        delete succ;
        return root;
    }
}
void ThanosBST::printGivenLevel(ThanosBST* root, int level, int maxheight)
{
    if (root == NULL)return;
    if (level == 1) {
        if (maxheight == toBeDeletedHeight / 2)stree.push_back(root->data);
        else if (maxheight > toBeDeletedHeight / 2) {
            vtree.push_back(root->data);
        }
    }
    else if (level > 1) {
        printGivenLevel(root->left, level - 1, maxheight);
        printGivenLevel(root->right, level - 1, maxheight);
    }
}

int ThanosBST::height(ThanosBST* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight + 1);
        else return(rheight + 1);
    }
}
void ThanosBST::postOrder(ThanosBST* root, int thanos)
{
    if (!root) {
        return;
    }
    postOrder(root->left,thanos);
    postOrder(root->right,thanos);
    cout << root->data;
    if (root->data != thanos) {
        cout << " ";
    }
}
void ThanosBST::inorderS(ThanosBST* root) {
    if (root != NULL) {
        inorderS(root->left);
        int i = 0;
        for (i = 0; i < stree.size(); i++) {
            if (root->data == stree[i]) {
                cout << root-> data;
                if (countS != stree.size() - 1)cout << " ";
                countS++;
            }
        }
        inorderS(root->right);
    }
}

void ThanosBST::preorderV(ThanosBST* root) {
    if (root != NULL) {
        int i = 0;
        for (i = 0; i < vtree.size(); i++) {
            if (root->data == vtree[i]) {
                cout << root->data;
                if (countV != vtree.size() - 1)cout << " ";
                countV++;
            }
        }
        preorderV(root->left);
        preorderV(root->right);
    }
}

void ThanosBST::printSV(ThanosBST* root) {
    int sheight = toBeDeletedHeight / 2;
    int vheight = height(root);
    int i;
    for (i = 1; i <= sheight; i++) {
        printGivenLevel(root, i, sheight);
    }
    inorderS(root);
    cout << endl;
    for (i = sheight + 1; i <= vheight; i++) {
        printGivenLevel(root, i, vheight);
    }
    preorderV(root);
}


int main() {
    ThanosBST bst = NULL;
    ThanosBST* root = NULL;
    int Thanos, input;
    string citizen;
    string avengers;

    //read Thanos
    cin >> Thanos;
    //read citizen
    getline(cin, citizen);
    stringstream citizenSS(citizen);
    //read avengers
    getline(cin, avengers);
    stringstream avengerSS(avengers);

    //insert Thanos
    root = bst.insert(root, Thanos);

    //insert citizen
    while (citizenSS >> input) {
        bst.insert(root, input);
    }

    bst.postOrder(root,Thanos);
    cout << endl;

    toBeDeletedHeight = bst.height(root);
    if (toBeDeletedHeight % 2 != 0) {
        toBeDeletedHeight -= 3;
    }

    //delete avengers
    while (avengerSS >> input) {
        bst.deleteNode(root, input);
    }
    //cut tree
    bst.printSV(root);
}
