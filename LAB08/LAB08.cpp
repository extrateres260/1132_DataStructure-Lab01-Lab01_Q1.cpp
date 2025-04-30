#include <iostream>
using namespace std;

// ========================
// 樹的節點類別
// ========================
class TreeNode {
public:
    int data;           // 節點儲存的資料
    TreeNode* left;     // 指向左子節點
    TreeNode* right;    // 指向右子節點

    // 節點建構子：設定資料並初始化左右指標為空
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ========================
// 二元搜尋樹類別
// ========================
class BinarySearchTree {
private:
    TreeNode* root; // 根節點指標

    // --- 私有的遞迴插入方法 ---
    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val); // 找到插入位置，建立新節點
        }

        if (val < node->data) {
            node->left = insert(node->left, val); // 插入左子樹
        }
        else if (val > node->data) {
            node->right = insert(node->right, val); // 插入右子樹
        }
        // 如果 val == node->data，不插入（避免重複）

        return node; // 回傳更新後的節點
    }

    // --- 私有的遞迴搜尋方法 ---
    bool search(TreeNode* node, int target) {
        if (node == nullptr) return false;

        if (node->data == target) return true;
        else if (target < node->data) return search(node->left, target); // 繼續在左子樹找
        else return search(node->right, target);// 繼續在右子樹找
    }

    // --- 私有的中序遍歷方法（左-根-右）---
    void inOrderTraversal(TreeNode* node) {
        if (node == nullptr) return;

        inOrderTraversal(node->left);   // 先走訪左子樹
        cout << node->data << " ";   // 印出目前節點的資料
        inOrderTraversal(node->right); // 再走訪右子樹
    }

    // --- 私有的刪除方法 ---
    TreeNode* deleteNode(TreeNode* node, int val) {
        if (node == nullptr) return nullptr; // node not found, return null 

        if(val<node->data) node->left = deleteNode(node->left,val); //  target value is smaller , search on the left substree

        else if (val>node->data) node->right = deleteNode(node->right, val); // target value is larger, search on the right substree
        
        else{ 
             // node found

            // if the node has only the rigth child
            if(node->left==nullptr) {
                TreeNode* temp = node->right; // it becomes the parent's new right child
                delete node; // delete current node
                return temp; 
            }
            // if node has only the left child 
            else if (node->right == nullptr) {
                TreeNode* temp = node->left; // it becomes the parent's new left child by recursion
                delete node; // delete the cuurent node
                return temp; 
            }

            //  Node has both left child and right child
            node->data = findMin(node->right)->data;  // we find the minimum value on the right(The In-order successor), and set it as the new node value
            node->right = deleteNode(node->right, node->data); // delete the in-order successor
            
        }

        return node; // return the node value for maitain the recursion

        
    }

    // --- 私有的找最小值方法 ---
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    // --- 建構子：初始化為空樹 ---
    BinarySearchTree() : root(nullptr) {}

    // --- 公開插入方法 ---
    void insert(int val) {
        root = insert(root, val);
    }

    // --- 公開搜尋方法 ---
    bool search(int target) {
        return search(root, target);
    }

    // --- 公開中序遍歷方法 ---
    void displayInOrder() {
        cout << "The results of the in-order traversal of the tree:" << endl;
        inOrderTraversal(root);
        cout << endl;
    }

    // --- 公開刪除方法 ---
    void deleteValue(int val) {
        root = deleteNode(root, val);
    }
};

int main() {
    BinarySearchTree bst; // 建立一棵空的樹

    // 預設插入的資料
    int values[] = { 7, 1, 4, 2, 8, 13, 12, 11, 15, 9, 5 };
    int n = sizeof(values) / sizeof(values[0]);

    // 把資料插入樹中
    for (int i = 0; i < n; ++i) {
        bst.insert(values[i]);
    }

    // 讓使用者輸入要插入的鍵值
    int key;
    cout << "Please enter the value to search for/insert: ";
    cin >> key;

    if (bst.search(key)) {
        cout << "Value " << key << " It already exists in the tree and is not added newly。" << endl;
    }
    else {
        cout << "Value " << key << " does not exist, has been newly inserted in the tree." << endl;
        bst.insert(key);
    }

    // 顯示目前樹的中序遍歷結果
    bst.displayInOrder();

    // 讓使用者輸入要刪除的鍵值
    int deleteKey;
    cout << "Please enter the value you want to delete: ";
    cin >> deleteKey;

    // 刪除節點
    bst.deleteValue(deleteKey);

    // 顯示刪除後的樹
    cout << "Deleted Tree (Medium Traversal): " << endl;
    bst.displayInOrder();

    return 0;
}
