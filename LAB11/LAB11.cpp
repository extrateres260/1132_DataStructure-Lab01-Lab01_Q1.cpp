#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
using namespace std;

// 定義一個 MaxHeap 類別
class MaxHeap {
public:
    vector<int> heap;  // 用來儲存堆的元素

    // 建立 Max Heap
    void buildMaxHeap(vector<int>& arr) {
        heap = arr;  // 將傳入的陣列複製到內部 heap 向量

        // 從最後一個非葉子節點開始向上堆化
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    // 維護堆的性質：以節點 i 為根的子樹要符合最大堆性質
    void heapify(int i) {
        int largest = i;           // 目前假設 i 是最大值
        int left = 2 * i + 1;      // 左子節點
        int right = 2 * i + 2;     // 右子節點

        // 若左子節點比目前最大值大，更新最大值索引
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        // 若右子節點也比目前最大值大，再次更新
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        // 如果最大值不是原本的節點 i，就交換並遞迴處理被影響的子樹
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);  // 遞迴處理
        }
    }

    // 從堆中取出最大值（根節點）
    int extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty"); // 錯誤處理
        }

        int maxElement = heap[0];    // 取出根節點（最大值）
        heap[0] = heap.back();       // 用最後一個節點覆蓋根
        heap.pop_back();             // 移除最後一個節點
        heapify(0);                  // 從根重新堆化

        return maxElement;           // 返回最大值
    }

    // Sort products using QuickSort
    void quicksort(vector<string>& names, vector<int>& expiration, vector<int>& popularity, int low, int high) {
        if (low < high) {
            int pi = partition(names, expiration, popularity, low, high);
            quicksort(names, expiration, popularity, low, pi - 1);
            quicksort(names, expiration, popularity, pi + 1, high);
        }
    }
    
    // Partition function for three parallel vectors
    int partition(vector<string>& names, vector<int>& expiration, vector<int>& popularity, int low, int high) {
        int pivotExp = expiration[high];
        int pivotPop = popularity[high];
        string pivotName = names[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            // Sort by expiration ascending, then popularity descending
            if (expiration[j] < pivotExp || (expiration[j] == pivotExp && popularity[j] > pivotPop)) {
                i++;
                swap(expiration[i], expiration[j]);
                swap(popularity[i], popularity[j]);
                swap(names[i], names[j]);
            }
        }
        swap(expiration[i + 1], expiration[high]);
        swap(popularity[i + 1], popularity[high]);
        swap(names[i + 1], names[high]);
        return i + 1;
    } 

};


int main() {
    string filename = "input1.txt"; //請貼上input檔案的正確路徑
    if (filename.empty()) {
        cerr << "Error: Filename cannot be empty." << endl;
        return 1;
    }

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    int N;
    infile >> N;
    infile.ignore(); // Ignore the newline after N
    if (N <= 0) {
        cerr << "Error: N must be a positive integer." << endl;
        return 1;
    }
    vector<string> names(N);
    vector<int> exp(N);
    vector<int> pop(N);
    for (int i = 0; i < N; i++) {
        string line;
        getline(infile, line);
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) tokens.push_back(token);

        exp[i] = stoi(tokens[tokens.size() - 2]);
        pop[i] = stoi(tokens[tokens.size() - 1]);
        names[i].clear();
        for (size_t j = 0; j < tokens.size() - 2; ++j) {
            names[i] += tokens[j];
            if (j != tokens.size() - 3) names[i] += " ";
        }
    }
    infile.close();

    MaxHeap maxHeap;
    maxHeap.buildMaxHeap(exp); // Build the max heap based on expiration dates
    maxHeap.quicksort(names, exp, pop, 0, N - 1); // Sort the three parallel vectors
    cout << "Sorted Products:" << endl;

    for (int i = 0; i < N; i++) {
        cout << names[i] << endl;
    }       
    return 0;
}
