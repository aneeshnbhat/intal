#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"


static int max(int a, int b){
    return (a>b)? a:b;
}

static int min(int a, int b){
    return (a<b)? a:b;
}


static int numberOfDigits(int n) {
  int count = 0;
  while(n) {
    n/=10;
    count++;
  }
  return count;
}

static char* removeLeadingZeros(char* result, int n) {

  int i=0,k = 0;
	while(result[i] == '0') {
		k++;
		i++;
	}
  char* newchar;
  if(k<n) {
    int size = (n - k);

    newchar = (char*)calloc(size,sizeof(char));
    for(i = 0;i < size;i++) {
  		newchar[i] = result[i+k];
  	}
    newchar[i]='\0';
  } else {
    newchar = (char*)calloc(1,sizeof(char));
    newchar[0] = '0';
    newchar[1] = '\0';
  }

  free(result);
  result = newchar;
  return newchar;

}

static char* deepCopy(const char* intal, int n) {
  char* temp = (char*)malloc(n*sizeof(char));
  int i;
  for(i=0;i<n;i++) {
    temp[i] = intal[i];
  }
  temp[i]='\0';
  return temp;
}



// Returns the sum of two intals.
char* intal_add(const char* intal1, const char* intal2) {

    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    int size3 = max(size1,size2)+1;

    char* addResult = (char*)calloc(size3,sizeof(char));

    int i,j,k,temp,carry=0;
    for(int i=0;i<size3;i++){
        addResult[i]='0';
    }

    for(i=size1-1,j=size2-1,k=size3-1; i>=0 && j>=0; i--, j--, k--) {
        temp = carry + intal1[i]-'0' + intal2[j]-'0';
        carry = temp/10;
        temp = temp%10;
        addResult[k] = temp + '0';
    }
    if(i>j){
        for( ; i>=0; i--,k--){
            temp = carry + intal1[i]-'0';
            carry = temp/10;
            temp = temp%10;
            addResult[k] = temp+'0';
        }
    }else if(j>i){
        for( ; j>=0; j--,k--) {
            temp = carry + intal2[j]-'0';
            carry = temp/10;
            temp = temp%10;
            addResult[k] = temp+'0';
        }
    }
    addResult[k] = carry+'0';
    addResult = removeLeadingZeros(addResult, size3);

    return addResult;
}

// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char* intal1, const char* intal2) {
    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    int i,isEqual = 0;
    if(size1 > size2){
      return 1;
    }else if(size2 > size1) {
      return -1;
    }else {
      for(i=0;i<size1;i++) {
        if(intal1[i] > intal2[i]) {
          isEqual = 1;
          break;
        } else if(intal1[i] < intal2[i]) {
          isEqual = -1;
          break;
        }
      }
    }
    return isEqual;
}

static void subAns(const char* num1, int size1, const char* num2, int size2, char* subResult) {

  char* intal1 = deepCopy(num1,size1);
  char* intal2 = deepCopy(num2,size2);
  int i,j,k,temp;

  if(size1==size2) { // when both have equal size
    for(i=size1-1;i>=0;i--) {
      if(intal1[i] > intal2[i]) {
        temp = intal1[i] - intal2[i];
      } else if(intal1[i] < intal2[i]) {
        k=i-1;
        while (intal1[k]=='0' && k>=0) {
          intal1[k] = '9';
          k--;
        }
        intal1[k]--;
        temp =  (10 + intal1[i] -'0') - (intal2[i] - '0');

      } else {
        temp = 0;
      }

      subResult[i] = temp + '0';
    }
  } else { // when size(intal1) > size(intal2)

    for(i=size1-1,j=size2-1; i>=0 && j>=0; i--, j--) {

      if(intal1[i] > intal2[j]) {
        temp = intal1[i] - intal2[j];
      } else if(intal1[i] < intal2[j]) {

        k=i-1;
        while (intal1[k]=='0' && k>=0) {
          intal1[k] = '9';
          k--;
        }
        intal1[k]--;

        temp = (10 + intal1[i] - '0') - (intal2[j] - '0');

      } else {
        temp = 0;
      }
      subResult[i] = temp + '0';
    }
    for(i=size1-size2-1;i>=0;i--){
      subResult[i] = intal1[i];
    }
  }
  free(intal1);
  free(intal2);
}

// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(const char* intal1, const char* intal2) {
    int cmp = intal_compare(intal1, intal2);

    int size1 = strlen(intal1);
    int size2 = strlen(intal2);
    int size3 = max(size1,size2);

    char* subResult;

    if(cmp==1) {
      subResult = (char*)malloc(size3*sizeof(char));
      for(int i=0;i<size3;i++) {
          subResult[i]='0';
      }
      subAns(intal1,size1, intal2,size2, subResult);

    } else if(cmp==-1) {
      subResult = (char*)malloc(size3*sizeof(char));
      for(int i=0;i<size3;i++) {
          subResult[i]='0';
      }
      subAns(intal2,size2, intal1,size1, subResult);

    } else {
      char *r = (char*)malloc(sizeof(char));
      r[0] = '0';
      return r;
    }
    subResult = removeLeadingZeros(subResult, size3);
    return subResult;
}

// Returns the product of two intals.
char* intal_multiply(const char* intal1, const char* intal2) {
  int size1 = strlen(intal1);
  int size2 = strlen(intal2);
  int size3 = size1+size2;
  int i,j,temp;

  int* aux =(int*)calloc((size3),sizeof(int));
  char* mulResult =(char*)malloc((size3)*sizeof(char));
  for(int i=0;i<size3;i++) {
      mulResult[i]='0';
  }


  if (!strcmp(intal1,"0") || !strcmp(intal1 , "0")) {
    free(mulResult);
    free(aux);
    char *r = (char*)malloc(sizeof(char));
    r[0] = '0';
    return r;
  }


  for(j=size2-1; j>=0; j--) {
    for(i=size1-1; i>=0; i--) {
      aux[i+j+1] += (intal1[i] - '0')*(intal2[j] - '0');
    }
  }


  for(i=(size3-1); i>=0; i--) {
    temp = aux[i]/10; // carry
    aux[i] = aux[i]%10;
    if(i) {
      aux[i-1] = aux[i-1] + temp;
    }
  }

  for(i = 0; i<size3; i++) {
    mulResult[i] = aux[i] + '0';
  }
  free(aux);
  aux = NULL;

  mulResult = removeLeadingZeros(mulResult,size3);

  return mulResult;
}


static char* reduceIntal(char* intal1,int size1, char* intal2) {

  int i;
  char* ten = (char*)malloc(2*sizeof(char));
  ten[0] = '1';
  ten[1] = '0';
  char* intal1Mod = (char*)malloc(sizeof(char));
  intal1Mod[0] = '0';
  char* temp;
  char* tempAdd = (char*)malloc(sizeof(char));;

  for(i=0; i<size1; i++) {
    // the basic idea is --> intal1Mod = (intal1Mod*10 + intal1[i])%intal2
    temp = intal1Mod;
    intal1Mod = intal_multiply(temp,ten);

    free(temp);

    temp = intal1Mod;
    tempAdd[0] = intal1[i];
    intal1Mod = intal_add(temp, tempAdd);

    free(temp);

    temp = intal1Mod;
    intal1Mod = intal_mod(temp,intal2);

    free(temp);
  }
  free(tempAdd);

  return intal1Mod;
}


// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
char* intal_mod(const char* intal1, const char* intal2) {
  int size1 = strlen(intal1);
  int size2 = strlen(intal2);

	char* num1 = deepCopy(intal1, size1);
	char* num2 = deepCopy(intal2, size2);
  char* tempch;

	int cmp;
  char* modResult=NULL;
	cmp = intal_compare(intal1,intal2);

  if(cmp == 0) {
    char *r = (char*)malloc(sizeof(char));
    r[0] = '0';
    free(num1);
    free(num2);

    return r;
  } else if(cmp == 1) {
    if(size1-size2 >= 2) {
        modResult = reduceIntal(num1,size1, num2); // recursive function
        free(num1);
    } else {
      while (intal_compare(num1,num2) >= 0) {
        tempch = num1;
        num1 = intal_diff(tempch,num2);
        free(tempch);
      }
      modResult = num1;
    }

    free(num2);

  } else {
    free(num2);
    modResult = num1;

  }
  free(tempch);

  return modResult;
}

// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
// Implement a O(log n) intal multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit.
char* intal_pow(const char* intal1, unsigned int n) {

  int size1 = strlen(intal1);

  char* powResult = (char*)malloc(sizeof(char));
  powResult[0] = '1';
  int power = n;
  char* num1 = deepCopy(intal1, size1);
  char* temp;

  char* zero =(char*)malloc(sizeof(char));
  zero[0] = '0';

  if(intal_compare(intal1,zero) == 0 && n == 0) {
    char *r = (char*)malloc(sizeof(char));
    r[0] = '1';
    return r;
  } else if(intal_compare(intal1, zero) == 0) {
    char *r = (char*)malloc(sizeof(char));
    r[0] = '0';
    return r;
  } else if(n == 0) {
    char *r = (char*)malloc(sizeof(char));
    r[0] = '1';
    return r;
  } else {

    while(power > 0) {
      if(power & 1) {
        temp = powResult;
        powResult = intal_multiply(powResult,num1);
        free(temp);
      }
      power >>= 1;

      temp = num1;
      num1 = intal_multiply(num1,num1);
      free(temp);

    }

    free(zero);
    free(num1);

    zero = NULL;
    num1 = NULL;

    return powResult;
  }
}


// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if both intal1 and intal2 are "0" even though it is undefined, mathematically.
// Use Euclid's theorem to not exceed the time limit.
char* intal_gcd(const char* intal1, const char* intal2) {
  int size1 = strlen(intal1);
  int size2 = strlen(intal2);

  char* num1 = deepCopy(intal1, size1);
  char* num2 = deepCopy(intal2, size2);
  char* temp;
  char* remainder = (char*)malloc(sizeof(char));
  remainder[0] = '0';
  char* zero =(char*)malloc(sizeof(char));
  zero[0] = '0';

  if((intal_compare(num1, zero) == 0) || (intal_compare(num2, zero) == 0)) {
    return zero;
  }

  while((intal_compare(num1,zero) != 0) && (intal_compare(num2,zero) != 0)) {
    if(intal_compare(num1,num2) == 1) {
      temp = num1;
      num1 = reduceIntal(num1,strlen(num1),num2);

      free(temp);
    } else {
      temp = num2;
      num2 = reduceIntal(num2,strlen(num2),num1);

      free(temp);
    }
  }
  if(intal_compare(num1,zero) == 0) {
    return num2;
  } else {
    return num1;
  }

  return num1;

}

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char* intal_fibonacci(unsigned int n) {
  char one = '1';
  char** fibo = (char**)malloc(n*sizeof(char*));
  char* fiboResult;

  fibo[0] = deepCopy(&one,1);

  fibo[1] = deepCopy(&one,1);


  int i;
  if(n<=2) {
    free(fibo[1]);
    fiboResult = fibo[0];
    free(fibo);
    return fiboResult;
  }

  for(i=2;i<n;i++) {
    if(i>2) {
      free(fibo[i-3]);
    }
    fibo[i] = intal_add(fibo[i-1],fibo[i-2]);
  }
  if(n>1) {
    free(fibo[n-2]);
  }
  if(n>2) {
    free(fibo[n-3]);
  }

  fiboResult = fibo[n-1];
  free(fibo);

  return fiboResult;
}


// Returns the factorial of n.
char* intal_factorial(unsigned int n) {

  char* factResult = NULL;
  int sizeOfN = numberOfDigits(n);
  char* temp;
  char* tempNumber;
  char* number = (char*)malloc(sizeOfN*sizeof(char));

  char* one = (char*)malloc(sizeof(char));
  one[0] = '1';

  if(n==0){
    char *r = (char*)malloc(sizeof(char));
    r[0] = '1';

    return r;
  } else {

    sprintf(number,"%d",n);

    factResult = number;
    number = intal_diff(number,one);

    temp = factResult;
    tempNumber = number;

    for(int i=0;i<n-1;i++) {
      factResult = intal_multiply(temp,number);
      free(temp);
      temp = factResult;

      number = intal_diff(tempNumber,one);
      free(tempNumber);
      tempNumber = number;
    }

    free(number);
    free(one);
    one = NULL;
    number = NULL;
    tempNumber = NULL;
    temp = NULL;

    return factResult;
  }
  return NULL;
}

// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n,k).
// Use Dynamic Programming. Use extra space of not more than O(k) number of intals. Do not allocate the whole O(nk) DP table.
// Don't let C(1000,900) take more time than C(1000,500). Time limit may exceed otherwise.
char* intal_bincoeff(unsigned int n, unsigned int k) {
  if(k>n/2) {
    k = n-k;
  }

  char** bincoeffResult = (char**)malloc((k+1)*sizeof(char*));
  char* bincoeffRes;
  char* temp;
  int i,j;
  char* zero =(char*)malloc(sizeof(char));
  zero[0] = '0';
  char* one = (char*)malloc(sizeof(char));
  one[0] = '1';

  for(i=0;i<k+1;i++) {
    bincoeffResult[i] = deepCopy(zero,1);
  }

  free(bincoeffResult[0]);
  bincoeffResult[0] = deepCopy(one,1);

  for(i=1; i<=n; i++) {
    for(j = min(i, k); j>0; j--) {
      temp = bincoeffResult[j];
      bincoeffResult[j] = intal_add(bincoeffResult[j], bincoeffResult[j-1]);
      free(temp);
    }
  }

  bincoeffRes = deepCopy(bincoeffResult[k], strlen(bincoeffResult[k]));
  for(i=0;i<k+1;i++) {
    free(bincoeffResult[i]);
  }
  free(bincoeffResult);
  free(one);
  free(zero);

  return bincoeffRes;

}

// Returns the offset of the largest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n) {
  char* maxNumber = arr[0];
  int maxIndex = 0;
  for(int i = 0; i<n; i++) {
    if(intal_compare(arr[i],maxNumber) == 1) {
      maxNumber = arr[i];
      maxIndex = i;
    }
  }
  maxNumber = NULL;
  return maxIndex;
}

// Returns the offset of the smallest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n) {
  char* minNumber = arr[0];
  int minIndex = 0;
  for(int i = 0; i<n; i++) {
    if(intal_compare(arr[i],minNumber) == -1) {
      minNumber = arr[i];
      minIndex = i;
    }
  }
  minNumber = NULL;
  return minIndex;
}

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char* key) {
  int i,searchResult = -1;
  for(i=0;i<n;i++) {
    if(intal_compare(arr[i],key) == 0) {
      searchResult = i;
      break;
    }
  }
  return searchResult;
}

static void merge(char **arr, int l, int m, int r) {
  int i,j,k;
  int n1 = m-l+1;
  int n2 = r-m;
  char* temp;

  char** L = (char**)malloc(n1*sizeof(char*));
	for(i=0; i<n1; i++) {
		L[i] = deepCopy(arr[l+i], strlen(arr[l+i]));
	}

  char** R = (char**)malloc(n2*sizeof(char*));
  for(j=0; j<n2; j++) {
    R[j] = deepCopy(arr[m+1+j], strlen(arr[m+1+j]));
  }

  i=j=0;
  k=l;
  while(i<n1 && j<n2) {
    if(intal_compare(L[i],R[j]) <= 0) {
      temp = arr[k];
      arr[k] = L[i];
      free(temp);
      i++;

    } else {
      temp = arr[k];
      arr[k] = R[j];
      free(temp);
      j++;
    }
    k++;
  }

  while (i<n1) {
    temp = arr[k];
    arr[k] = L[i];
    free(temp);
    i++;
    k++;
  }

  while(j<n2) {
    temp = arr[k];
    arr[k] = R[j];
    free(temp);
    j++;
    k++;
  }

  free(L);
  free(R);
}

static void mergeSort(char **arr, int l, int r) {
  if(l<r) {
    int m = l + (r-l)/2; // (l+r)/2;

    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);

    merge(arr, l, m, r);
  }
}


// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
void intal_sort(char **arr, int n) {
    mergeSort(arr, 0, n-1);
}

static int binarySearch(char **arr, int l, int r, const char* key) {
  while(l<=r) {
    int m = l+(r-l)/2;
    if(intal_compare(arr[m],key) == 0) {
      return m;
    } else if(intal_compare(arr[m],key) == -1) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return -1;
}

// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
int intal_binsearch(char **arr, int n, const char* key) {
  return binarySearch(arr, 0, n-1, key);
}

// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char* coin_row_problem(char **arr, int n) {

  char* zero =(char*)malloc(sizeof(char));
  zero[0] = '0';
  int i;
  char* temp;

  char** F = (char**)malloc((n+1)*sizeof(char*));

  F[0] = zero;
  F[1] = deepCopy(arr[0],strlen(arr[0]));
  if(n>=2) {
    for(i=2; i<=n; i++) {

      // F[i] = max(C[i] + F[i - 2], F[i - 1]);
      temp = intal_add(arr[i-1],F[i-2]);
      if(intal_compare(temp,F[i-1]) == 1) {
        free(F[i]);
        F[i] = temp;
      } else {
        F[i] = F[i-1];
      }
    }
    free(zero);

    return F[n];
  } else if(n==1) {
    free(zero);
    return F[1];
  } else {
    free(F[1]);
    free(F);
    return zero;
  }
}
