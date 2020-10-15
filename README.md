1.Introduction
i. Intal is a nonnegative integer of arbitrary length,(similar to BigInteger in Java) which can support 1000 decimal
   digits, all the numbers are stored in the form of character array rather than int or long int or long long int.
ii. Since Intal stores the data in character array format it can hold integers which are too long for datatypes like int, long long int.
iii. Intal can be used for addition,subtraction,multiplication,mod,gcd,factorial etc... of large numbers.
     Operations of large numbers is useful in the field of Mathematics, Cryptography, Cosmology and Statistical Mechanics.



2.Approach

Helper Functions :-
1. max: returns max of two numbers
2. min: returns min of two numbers

3.copy: This creates new intal from the given intal, allocating a new memory in the heap and returns this new copy of intal.

4.subAns: This helper function is used by intal_diff it assumes that intal1 > intal2, and it is the responsibility of intal_diff to do so, first a deepCopy of both the intals are made, and are used, if the length
	  of the two are same then both the intals are parsed from end to the start, if intal1[i] > intal2[i] then their difference is stored into the result, if intal1[i] < intal2[i] then any digit to the extreme
	left of intal1[i] is decreased by one and is used as borrow, if the extreme left of intal1[i] is a 0 then it is converted to 9 and the next digit is used for borrow this process repeats until a non zero
	digit is encountered, the borrow is used and normal subtraction takes place between intal1[i] and intal2[i] and is saved into the result. If both have same digit then 0 is saved into the result.
	If both have unequal lengths, then in the first part they follow the same procedure as above, then the remaining digits of intal1 gets copied to the result, and the result is returned.

5.reduceIntal: It is used as a helper function for mod. intal1 gets reduced, and becomes less than intal2.The idea is to process all digits one by one and use the property that xy(mod a) ≡ ((x(mod a)*y)(mod a)).
	       So each digit of intal1 is taken and its mod is used along with the next digit of intal1, the process continues until all the digits have been processed.It uses intal_multiply, intal_add and intal_mod
	       and returns intal1%intal2.
 
6.merge: It takes in a slice of array of intals, left,mid,right index, and splits the array into two halves, and merges them back together in the sorted order using a while loop, and if it has any leftover intals
	 it appends them using a for loop, and returns the sorted slice of the array.

7.mergeSort: It takes in the array to be sorted, and the left and right index of the array. It splits the array into two halves and uses them and calls itself, after both the left and right arrays have been split, it 
	     calls merge function to merge and sort them, and returns sorted array.

8.binarySearch: It takes in the array and uses an iterative binary search algorithm, where the mid index is half of sum of left and right index, and compares it to the key, if it is same then returns the mid index,
		If it is less than the key then it updates left to mid+1 else right is updated to mid-1, this process is continued as long as left is less than or equal to right, if it is unable to find the key
		then it returns -1

Main intal functions :-

intal_add: This uses max of the length of two intals to calulate the length of the resulting intal, then the two given numbers are parsed from the end to the start and the corresponding digits are being added to a 
           newely created array, and the carry of each digit pair is passed to the next one until both the numbers have been parsed completely, the resulting sum is sent to removeLeadingZeros which removes the leading 
           zeros and the result is returned.

intal_compare: First the length of the two given intals is compared, if length of intal1 is more than length of intal two then 1 is returned, if it is the other way around then -1 is returned, if
	      both have same length then they are parsed from the beginning to the end and each of their digits are compared, if intal1 is greater then 1 is returned, -1 is returned if intal2 is greater,
	      else if both are same then 0 is returned.

intal_diff: This uses max function to calculate the size for the resulting intal,and then uses intal_compare to compare two intals, if intal1 > intal2 then it is passed to subAns(intal1,intal2,subResult) 
	     and if intal2 > intal1 the it is passed as subAns(intal2,intal1,subResult), and then the result is returned after filtering through removeLeadingZeroes, If intal1 is equal to intal2 then simply 0 is returned.

intal_multiply: The sum of the lengths of the two intals is used as size for creating the resulting intal. First it is checked if either of the two intals is one, if yes then 0 is returned.An auxilary int array is created
		whose length is same as that of the resulting intal.A for loop nested inside another for loop is used and normal multiplication of digits is carried out and is saved as a sum in aux array at the index of
		of sum of the two indices +1.
		Now this aux array is parsed from end to beginnig and a carry of ith index is added to (i-1)th index of aux array, aux[i] is replaced by aux[i]%10 so that only one digit is saved at any given index i.
		The digits in the aux array are converted to the character type and is saved into the resulting intal, which is filtered through removeLeadingZeros and then the result returned.

intal_mod: DeepCopy of both intals are created and are used. First both the intals are compared, if intal1 > intal2 and if length of intal1 is (length of intal2 + 2) or greater then it calls reduceIntal helper function
	   else intal2 is repeatedly subtracted until intal1 becomes less than intal2, and this is returned.If intal1 < intal2 then intal1 is returned without any other calculation. If both are same then 0 is returned.

intal_pow: DeepCopy of both intals are created and are used. If both intal1 and intal2 are 0 then 1 is returned, If only intal1 is 0 then, 0 is returned, If only intal2 is 0 then 1 is returned.
	   Else using a while loop is used. if power is odd number then powResult, which is the resulting intal, gets multiplied by intal1, then despite of power being odd or even it gets divided by 2 and intal1 is 
	   multiplied to itself. This process is continued until power becomes 0, then powResult is returned.

intal_gcd: DeepCopy of both intals are created and are used. Euclid's theorem is used here, and insted of calling intal_mod, reduceIntal helper function is called for mod operation, which internally calls intal_mod, to
	   optimize the calculation speed, and the result is returned.

intal_fibonacci:It uses the property of fibonacci series that fib(n) = fib(n-1) + fib(n-2). Using this property fibonacci of the given number is calculated and is returned back.

intal_factorial: It uses the basic factorial function, that is fact(n) = n*(n-1)*...*1. Using this property factorial of the given number is calculated and is returned back.

intal_bincoeff: It uses an array of intals of length k+1. C(n,k) is calculated using pascal's triangle, where every next row depends on the sum of two elements from the previous row. It uses a for loop nested inside
		another for loop to compute a row of pascals triangle from previous row. Last element of the array is returned.

intal_max: It uses a for loop and finds the max element, and returns its offset.

intal_min: It uses a for loop and finds the min elemens, and returns its offset.

intal_search: It uses a for loop and finds the given key, and returns its offset, if it was unable to find the key then it returns -1.

intal_sort: It uses mergeSort helper function to sort the array, then returns the sorted array.

intal_binarysearch: It uses binarySearch helper function to find the key, and returns the offset, given by the helper function.

coin_row_problem: It is implemeted using memoization in dynamic programming. It uses the basic idea of maximising the value of coins by storing the values in an array in the given pattern.
		  arr[i] = max((value present at ith location + max of values till (i-2)th element) , max of values till (i-1)th element) that is arr[i] = max((Coins[i] + arr[i-2]), arr[i-1])
		  arr[n] is returned.



3.Future work
Intal library's functionalities can be extended by adding operations for permutation and combination.
It can also be extended for operating on floating point numbers.
If I had no restrictions then i would have used some external libraries to replace my helper functions for optimising the calculation time.



