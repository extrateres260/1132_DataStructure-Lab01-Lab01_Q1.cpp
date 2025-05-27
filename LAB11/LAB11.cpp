#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
using namespace std;

// Define a MaxHeap class
class MaxHeap {
public:
    vector<int> heap;  // Used to store heap elements


    // Build a Max Heap
    void buildMaxHeap(vector<int>& arr) {
        heap = arr;  // Copy the given array into the internal heap vector

        // Start heapifying from the last non-leaf node upwards
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    // Maintain heap properties: The subtree rooted at node i must satisfy the max-heap property
    void heapify(int i) {
        int largest = i;           // Assume i is the largest value
        int left = 2 * i + 1;      // Left child node
        int right = 2 * i + 2;     // Right child node

        // If the left child node is larger than the current largest value, update the largest index
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        // If the right child node is also larger, update again
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        // If the largest value is not the original node i, swap and recursively process the affected subtree
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);  // Recursively process
        }
    }

    // Extract the maximum value (root node) from the heap
    int extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty"); // Error handling
        }

        int maxElement = heap[0];    // Extract the root node (maximum value)
        heap[0] = heap.back();       // Replace the root with the last node
        heap.pop_back();             // Remove the last node
        heapify(0);                  // Re-heapify starting from the root

        return maxElement;           // Return the maximum value
    }

    // Quicksort for three parallel vectors
    void quicksort(vector<string>& names, vector<int>& exp, vector<int>& pop, int low, int high) {
        if (low < high) {
            int pi = partition(names, exp, pop, low, high);
            quicksort(names, exp, pop, low, pi - 1);
            quicksort(names, exp, pop, pi + 1, high);
        }
    }

    // Partition function for three parallel vectors
    int partition(vector<string>& names, vector<int>& exp, vector<int>& pop, int low, int high) {
        int pivotExp = exp[high];
        int pivotPop = pop[high];
        string pivotName = names[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            // Sort by expiration ascending, then popularity descending
            if (exp[j] < pivotExp || (exp[j] == pivotExp && pop[j] > pivotPop)) {
                i++;
                swap(exp[i], exp[j]);
                swap(pop[i], pop[j]);
                swap(names[i], names[j]);
            }
        }
        swap(exp[i + 1], exp[high]);
        swap(pop[i + 1], pop[high]);
        swap(names[i + 1], names[high]);
        return i + 1;
    }
};



int main() {
    string filename = "input3.txt"; //請貼上input檔案的正確路徑
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
    cout << "Sorted data:" << endl;

    for (int i = 0; i < N; i++) {
        cout << names[i] << endl;
    }
    cout << "Max expiration date: " << maxHeap.extractMax() << endl; // Extract and print the maximum expiration date
    return 0;
}
