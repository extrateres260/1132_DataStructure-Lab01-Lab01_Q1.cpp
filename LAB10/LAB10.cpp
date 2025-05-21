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

    // 計算指定層的總和
    void level_Sum(int layer){ 
        if (layer < 0) { // If the input layer is negative, output  an error message
            cout << "Error: Layer cannot be negative." << endl;
            return;
        } 
        
        // BFS to find the sum of the specified layer
        queue<TreeNode*> q; // Queue to store nodes at each level
        q.push(root);       // Start with the root node
        int currentLayer = 0; // The current layer being processed
        int sum = 0;
    
        while (!q.empty()) {          // Process each layer
            int size = q.size();     // Number of nodes at the current layer
            if (currentLayer == layer) {         // If we are at the desired layer, iterate through all nodes at this layer, add the value of the current node to the sum
                for (int i = 0; i < size; i++) { 
                    TreeNode* current = q.front(); 
                    q.pop();
                    sum += current->value; 
                }
                cout << "Sum of layer " << layer << ": " << sum << endl; // Output the sum of the layer
                return; // Exit after processing 
            }
            for (int i = 0; i < size; i++) {  // If we are not at the desired layer, continue to the next layer 
                TreeNode* current = q.front();
                q.pop();
                if (current->left) q.push(current->left); 
                if (current->right) q.push(current->right); 
            }
            currentLayer++;
        }
        // If we exit the loop, the layer does not exist
        cout << "Error: number of layer exceeded" << endl;
    }


   // Helper function to sum all nodes in a subtree
    int sumSubtree(TreeNode* node) {
        if (node == nullptr) return 0;
        return node->value + sumSubtree(node->left) + sumSubtree(node->right);
    }

    // Calculates and prints the sum of left and right subtrees of a given node value
    bool SumLeftRightChildren(TreeNode* node, int target) {
        if (node == nullptr) return false; // If the node is null, return false

        if (node->value == target) { // If the current node is the desired node
            if (node->left == nullptr && node->right == nullptr) { // If it's a leaf node, show a message
                cout << node->value << " is a Leaf Node! " << endl;
                return true;
            }
            if (node->left == nullptr) { // If there's no left child, show a message
                cout << "No left child for node " << node->value << endl;
            } else {
                cout << "Sum of left subtree: " << sumSubtree(node->left) << endl; // Ortherwise, call the helper function Sumsubtree to calculate the sum of the left subtree
            }
            if (node->right == nullptr) { // If there's no right child, show a message
                cout << "No right child for node " << node->value << endl;
            } else {
                cout << "Sum of right subtree: " << sumSubtree(node->right) << endl; // Ortherwise, call the helper function Sumsubtree to calculate the sum of the right subtree
            }
            // Compare the sum of left and right subtrees
            if(sumSubtree(node->left)>sumSubtree(node->right)) { 
                cout << "Sum of Left subtree is larger" << endl;
            }
            if (sumSubtree(node->right)>sumSubtree(node->left)) {
                cout << "Sum of Right subtree is larger" << endl;
            }
            return true; // Return true if the target node is found
        }
        // Recursively search in the left and right subtrees
        return SumLeftRightChildren(node->left, target) || SumLeftRightChildren(node->right, target);
    }

};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, 10, 11, -1, -1 };
    tree.buildTree(arr);

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
    if (!tree.SumLeftRightChildren(tree.root, target)) { // If the target node is not found
        cout << "Node with value " << target << " not found." << endl;
    }
    return 0;
}
