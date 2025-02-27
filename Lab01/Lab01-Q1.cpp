class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        int Count = 0;

        bool isincreasing = true;
        bool isdecreasing = true;

        // Two assignments (isincreasing and isdecreasing) : 2 operations
        count++;
        count++;

        // Loop initialization : 1 operation
        count++;

        for (int i = 1; i < nums.size(); i++) {
            // Loop comparison : 1 operation
            count++;

            // Accessing Array twice : 2 operations
            count++;
            count++;

            // Comparison of elements (nums[i] < nums[i - 1]) : 1 operation
            count++;

            // Assignment of isincreasing : 1 operation
            count++;

            if (nums[i] < nums[i - 1]) { // if the precedent number is greater to the one after, it is not increasing
                isincreasing = false;
            }

            // Accessing Array twice : 2 operation
            count++;
            count++;

            // Comparison of elements (nums[i] > nums[i - 1]) : 1 operation
            count++;

            // Assignment of isdecreasing : 1 operation
            count++;

            if (nums[i] > nums[i - 1]) {   // if the following number is greater than the precedent, it is not decreasing
                isdecreasing = false;
            }
        }

        // Increment i++ : 1 operation
        count++;

        // Return operation : 1 operation
        count++

        cout << "Total operations: " << count << endl;

        return isincreasing || isdecreasing; // display either the array if increasing or decreasing
    }
};


