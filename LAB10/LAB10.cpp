#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = -1; // 用 NULL 代表沒有節點
class TreeNode {
public:
    int value;// 節點值
    TreeNode* left;// 左子節點
    TreeNode* right;// 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//初始化節點
};

class BinaryTree {
public:
    TreeNode* root;// 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(&root);// 將根節點的指標加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// 添加左子節點
                    q.push(&((*nodePtr)->left));// 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// 添加右子節點
                    q.push(&((*nodePtr)->right));// 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) {//深度優先搜尋
        if (node == nullptr) return;
        cout << node->value << " ";// 訪問當前節點的值
        Depth_first_search(node->left);// 遞迴遍歷左子樹
        Depth_first_search(node->right);// 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將左子節點的指標加入queue
        }
    }

    void level_Sum(int layer){
        if (layer < 0) {
            cout << "Error: Layer cannot be negative." << endl;
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        int currentLayer = 0;
        int sum = 0;
       // BFS to find the sum of the specified layer
        while (!q.empty()) { // 當queue不為空時
            int size = q.size();
            if (currentLayer == layer) { 
                for (int i = 0; i < size; i++) {
                    TreeNode* current = q.front();
                    q.pop();
                    sum += current->value;
                }
                cout << "Sum of layer " << layer << ": " << sum << endl;
                return; // Exit after processing the desired layer
            }
            for (int i = 0; i < size; i++) { 
                TreeNode* current = q.front();
                q.pop();
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            currentLayer++;
        }
        // If we exit the loop, the layer does not exist
        cout << "Error: Layer " << layer << " does not exist in the tree." << endl;

    }

    // Helper function to sum all nodes in a subtree
    int sumSubtree(TreeNode* node) {
        if (node == nullptr) return 0;
        return node->value + sumSubtree(node->left) + sumSubtree(node->right);
    }

    // Calculates and prints the sum of left and right subtrees of a given node value
    void SumLeftRightChildren(TreeNode* node, int target) {
        if (node == nullptr) return;
        if (node->left == nullptr) {
            cout << "No left child for node " << node->value << endl;
            return;
        }
        if (node->right == nullptr) {
            cout << "No right child for node " << node->value << endl;
            return;
        }
        if(node->left == nullptr && node->right == nullptr){
            cout << "No child for node " << node->value << endl;
            return;
        }
        if (node->value == target) {
            int leftSum = sumSubtree(node->left);
            int rightSum = sumSubtree(node->right);
            cout << "Sum of left subtree: " << leftSum << endl;
            cout << "Sum of right subtree: " << rightSum << endl;
            return;
        }
        SumLeftRightChildren(node->left, target);
        SumLeftRightChildren(node->right, target);
    }

};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, 10, 11, -1, -1 };
    tree.buildTree(arr);

    cout << "DFS Result: ";
    tree.Depth_first_search(tree.root);
    cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    int layer;
    cout << "Enter the layer number to calculate the sum: ";
    cin >> layer;
    int sum = 0;
    tree.level_Sum(layer);
    cout << endl;
    int target;
    cout << "Enter the target node value to calculate left and right subtree sums: ";
    cin >> target;
    tree.SumLeftRightChildren(tree.root, target);
    return 0;
}
