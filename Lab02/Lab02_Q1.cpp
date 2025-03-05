Class solution{
  Public:
     int findLucky(vector<int>& arr) {
     // I sort the array first
     sort(arr.begin(), arr.end());

     int lucky_integer = -1; // I suppose there is no lucky integer yet
     // Loop through the array while calculating the frequence of every integer
     for ( int i = 0; i < arr.size(); i++) {
       int freq = 0;
       for (int j = 0; j< arr.size(); j++) { 
           if(arr[j] = arr[i]) {  // if an integer is equal to the previous one, its frequence grows by 1
             freq++;
           }
       }
         // Check if the number is equal to its frequence, if yes it is lucky 
        if(arr[i] == freq) {
           lucky_integer = max(lucky_integer, arr[i]);  // We keep the greather integer between this number and the previous lucky number
         }

         // While looping through the array, if the next integer is equal to the previous one, just skip it
         while( i+1 < arr.size() && arr[i] == arr[i+1] {
              i++;
         }
       }
     retun lucky_integer; // return the lucky integer
  }
