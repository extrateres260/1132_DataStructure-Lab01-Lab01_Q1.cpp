#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
// Function to merge two sorted arrays nums1 and nums2, the final merged array should be stored in nums1.
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int i = m-1; 
        int j = n-1; 
        int k = m + n-1; 

        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        // If there are remaining elements in nums2, copy them
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};
