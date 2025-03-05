// Method 1
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) { 
       int count[101]={0};//計數陣列,範圍 0-100
       int n=num.size();//陣列長度
       counter++; // for assignement 
       counter++; // for assignement 
      
       vector<int> result(n);//vector<int>是動態陣列,在執行分配記憶體時,可以根據 num.size()自動調整大小
      
       //計算每個數字的出現次數,此迴圈遍歷 nums,並統計每個數字 num 出現的次數
      
       for(int num:nums){ count[num]++;}
          counter++; // for the fo loop
        //計算比當前數字小的數量
        for(int i=1; i<101; i++){
          counter++; // for the for loop
          count[i]+=count[i-1];
          counter++; // for assignement
        }
         counter++; // last execution of the loop
       //計算 result 陣列
      for(int i=0; i<n; i++){
        counter++; // for the loop
        result[i]=(nums[i]==0)?0:count[nums[i]-1];
         //count[nums[i]-1]代表比 nums[i]小的數的數量,nums[i]==0 時則直接返回 0
        counter++; // for assignment
      }
      counter++; // last execution of the loop
      counter++; // for return
      return result;
    }
};


// Method 2
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> result; // 存結果
        int count; // 計數器

        // 外層迴圈遍歷 nums 陣列中的每個元素
        for (int i = 0; i < nums.size(); i++) {
          counter++; // for the loop
          count = 0; // 每次重新計算當前元素的較小數量
          counter++; // for assignment

            // 內層迴圈再次遍歷 nums 陣列,統計比 nums[i] 小的元素數量
            for (int j = 0; j < nums.size(); j++) {
              counter++; // for the loop
              counter++; // for if condition
               if (nums[j] < nums[i]) { count++; } // 如果 nums[j] 比nums[i] 小,則計數器 +1
              count++; // for assignment 

             }
             counter++; // last execution of for
             result.push_back(count); // 將計算出的數量存入 result
             counter++; // for assignment
          }
         counter++; // last execution of for
         counter++; // for return
         return result;
      }
};
