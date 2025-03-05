class Solution {
public:
   vector<int> runningSum(vector<int>& nums) {
      int n =nums.size();  // this an integer to take the size of the vector nums
      vector<int> result(n); // This vector will store the results of the running sum
     
      result[0]=nums[0];  // We initialize the first element of the ressult vector to the first element of the input vector
     
     // We loop through the nums vector, sum each element to the last element of the result vector, and store it to the result vector
      for(int i=1; i<n; i++) {
         result[i]=result[i-1]+nums[i];
      }
     return result; // return the vector running sum
   }
};
