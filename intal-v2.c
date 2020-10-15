#include<stdio.h>
#include<stdlib.h>
#include<string.h>


static int same(const char *a,const char *b) //used in intal_search function
{
  int x=strlen(a);
  int y=strlen(b);
  if (x!=y){
    return 0;
  }else{
    for (int i=0;i<y;i++){
      if (a[i]!=b[i]){
        return 0;
      }
    }
  }
  return 1;
}

char* intal_add(const char* intal1, const char* intal2){

  char *result = (char*)malloc(1001*sizeof(char));

  if(0 == (intal1[0]-'0')) // if second number is zero
  {
      strcpy(result,intal2);
      return result;
  }
  else if(0 == (intal2[0]-'0')) // if first  number is zero
  {
      strcpy(result,intal1);
      return result;
  }

  int larger = strlen(intal1);
  int smaller = strlen(intal2);

  char *larger_intal = (char*)malloc(1001*sizeof(char));
  char *smaller_intal = (char*)malloc(1001*sizeof(char));

  strcpy(larger_intal,intal1);
  strcpy(smaller_intal,intal2);

  if(smaller > larger) // to fit larger length intal correctly
  {
      int temp = larger;
      larger = smaller;
      smaller = temp;
      strcpy(larger_intal,intal2);
      strcpy(smaller_intal,intal1);
  }

  int diff = larger-smaller;

  for(int i=larger-1;i>=diff;i--){
      int num1 = larger_intal[i]-'0';
      int num2 = smaller_intal[i-diff]-'0';
      result[i] = (num1+num2)+'0';
  }
  for(int i=diff-1;i>=0;i--){
      result[i] = larger_intal[i];
  }

  for(int i=larger-1;i>0;i--){
      int num = result[i]-'0';
      if(num>9){
          result[i] = (num-10)+'0';
          int temp = result[i-1]-'0';
          result[i-1] = (temp+1)+'0';
      }
  }

  if((result[0]-'0')>9){
      int temp=result[0]-'0';
      for(int i=larger;i>=1;i--)
          result[i] = result[i-1];
      result[1] = (temp-10)+'0';
      result[0] = '1';
      result[larger+1] = '\0';
  }
  else
      result[larger]='\0';

  free(larger_intal);
  free(smaller_intal);
  return result;

}


int intal_compare(const char* intal1, const char* intal2){
  int len1=strlen(intal1);
  int len2=strlen(intal2);
  if (len1>len2) // greater the len of string greater the number
  {
    return 1;
  }
  else if (len1<len2){
    return -1;
  }
  else // when same length check for each number
  {
    for (int i=0;i<len1;i++){
      if (intal1[i]>intal2[i]){
        return 1;
      }
      else if (intal1[i]<intal2[i]){
        return -1;
      }
    }
  }
  return 0;
}


char* intal_diff(const char* intal1, const char* intal2){
  char *result = (char*)malloc(1001*sizeof(char));
  int larger;
  int smaller;
  char *larger_intal = (char*)malloc(1001*sizeof(char));
  char *smaller_intal = (char*)malloc(1001*sizeof(char));
  int flag = 0;
  if(0 == (intal1[0]-'0')) //check if one number is zero and return the other
  {
      strcpy(result,intal2);
      return result;
  }
  else if(0 == (intal2[0]-'0')){
      strcpy(result,intal1);
      return result;
  }

  flag = intal_compare(intal1,intal2); // compare the two to know which is bigger

  if(flag == 1){
      larger = strlen(intal1);
      smaller  = strlen(intal2);
      strcpy(larger_intal,intal1);
      strcpy(smaller_intal,intal2);
  }else if(flag == -1){
      larger = strlen(intal2);
      smaller  = strlen(intal1);
      strcpy(larger_intal,intal2);
      strcpy(smaller_intal,intal1);
  }else{
      result[0] = '0';
      result[1] = '\0';
      free(larger_intal);
      free(smaller_intal);
      return result;
  }

  int borrow = 0;// calculate borrow and use it for subtracting
  int diff = larger - smaller;
  for(int i=larger-1;i>=diff;i--){
      int num1 = larger_intal[i]-'0';
      int num2 = smaller_intal[i-diff]-'0';
      int term = num1-num2-borrow;
      if(term < 0){
          result[i] = (10+term)+'0';
          borrow = 1;
      }else{
          result[i] = term+'0';
          borrow = 0;
      }
  }

  for(int i=diff-1;i>=0;i--){
      int num1 = larger_intal[i]-'0';
      int term = num1-borrow;
      if(term < 0){
          result[i] = (10+term)+'0';
          borrow = 1;
      }else{
          result[i] = term+'0';
          borrow = 0;
      }
  }

  int pos = larger;
  while(0 == (result[0]-'0')){
      --pos;
      for(int i=0;i<pos;i++)
          result[i] = result[i+1];
  }
  result[pos] = '\0';
  free(larger_intal);
  free(smaller_intal);
  return result;
}


static void reverseString(char *a) // used in intal_multiply
{
  int n = strlen(a);
  for (int i = 0; i < n / 2; i++){
    char b=a[i];
    a[i]=a[n-i-1];
    a[n-i-1]=b;
  }
}

char* intal_multiply(const char* intal1, const char* intal2){
  if(intal1[0]==48||intal2[0]==48){
  char *r=(char*)malloc(sizeof(char)*2);
  r[0]=48;
  r[1]='\0';
  return r;}
  int a=strlen(intal1);
  int b=strlen(intal2);
      char *rult = malloc(sizeof(char)*(a+b+2)); // array for the rsult of both the numbers
      int i_n1 = 0;
      int i_n2 = 0;
      int i;
      for(int i=0;i<a+b+2;i++){
  		    rult[i]=48;
      }
      for (i = a - 1; i >= 0; i--){
          int c = 0;
          int n1 = intal1[i] - '0';
          i_n2 = 0;
          for (int j = b - 1; j >= 0; j--){
              int n2 = intal2[j] - '0';

              int s = n1 * n2 + (rult[i_n1 + i_n2]-'0') + c;
              c = s / 10;
              rult[i_n1 + i_n2] = 48+(s % 10);

              i_n2++;
          }

          if (c > 0)
              rult[i_n1 + i_n2] = 48+rult[i_n1+i_n2]-'0'+c;

          i_n1++;
      }
  int v=i_n1+i_n2;
  v--;
  while(rult[v]==48){
    v--;
  }

  rult[v+1]='\0';

  reverseString(rult);
  return rult;
}


static char* adding_zeroes(char* a, int n){
    if(n < 1){
        char* temp = (char*)malloc(sizeof(char)*(strlen(a)+1));
        strcpy(temp, a);
        return temp;
    }
    int i;
    char* temp = (char*)malloc(sizeof(char)*(strlen(a)+1+n));
    for(i = 0; i < strlen(a); i++)
        temp[i] = a[i];
    for(int j = 0; j < n; j++)
        temp[i++] = '0';
    temp[i] = '\0';
    return temp;
}

char* intal_mod(const char* intal1, const char* intal2){
  if(intal_compare(intal1, intal2) == -1){
        char* result = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(result, intal1);
        return result;
    }
    if(intal_compare(intal2, "1") == 0 || intal_compare(intal1, intal2) == 0){
        char* result = (char*)malloc(sizeof(char)*2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    char* a = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
    char* b = (char*)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(a, intal1);
    strcpy(b, intal2);

    int m = strlen(intal1);
    int n = strlen(intal2);

    int range = m-n;
    int comp = 0;

    while(1){
        if(range > 0){
            char* temp = adding_zeroes(b, range--);
            free(b);
            b = temp;
        }

        comp = (intal_compare(a, b) == -1) ? 1 : 0;

        while(intal_compare(a, b) == 1){
            char* temp = intal_diff(a, b);
            free(a);
            a = temp;

            int comp1 = intal_compare(a, intal2);
            if(comp1 == -1 || comp1 == 0){
                if(!comp)
                    break;
                else
                    comp = 0;
            }

        }

        strcpy(b, intal2);
        int res = intal_compare(a, b);
        if(res == 0){
            char* result = intal_diff(a, b);
            free(a);
            free(b);
            return result;
        }
        else if(res == -1){
            free(b);
            return a;
        }
    }
}


char* intal_pow(const char* intal1, unsigned int n){
  if(n == 0 && intal_compare(intal1, "0") == 0){
        char* result = (char*)malloc(sizeof(char)*2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if(n == 1){
        char* result = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(result, intal1);
        return result;
    }else if(n == 0 || intal_compare(intal1, "1") == 0){
        char* result = (char*)malloc(sizeof(char)*2);
        result[0] = '1';
        result[1] = '\0';
        return result;
    }else{
        if(n % 2 == 1){
            char* temp1 = intal_pow(intal1, n/2);
            char* temp2 = intal_multiply(temp1, temp1);  // repatative multiply and recurrsive function
            free(temp1);

            char* result = intal_multiply(temp2, intal1);
            free(temp2);

            return result;
        }else{
            char* temp = intal_pow(intal1, n/2);
            char* result = intal_multiply(temp, temp);
            free(temp);

            return result;
        }
    }
}


char* intal_gcd(const char* intal1, const char* intal2) // normal euclidean approach
{
  char* a = (char*)malloc((strlen(intal1) + 1) * sizeof(char));
  strcpy(a, intal1);
  char* b = (char*)malloc((strlen(intal2) + 1) * sizeof(char));
  strcpy(b, intal2);

  int value = strcmp(a, "0");
  while(value != 0){
    char* tmp = b;
    b = a;
    a = intal_mod(tmp, a);
    free(tmp);
    value = strcmp(a, "0");
  }

  free(a);
  return b;
}


char* intal_fibonacci(unsigned int n) // takeing to array and using intal_add to add and get new value
{
  char *l1=(char*)calloc(2,sizeof(char));
  l1[0]=48;
  char *l2=(char *)calloc(2,sizeof(char));
  l2[0]=49;
  if (n==0){
    free(l2);
    return l1;
  }else{
    char *temp;
    for (int i=2;i<=n;i++){
      temp=intal_add(l1,l2);
      free(l1);
      l1=l2;
      l2=temp;
    }
  }
  free(l1);
  return l2;
}


char* intal_factorial(unsigned int n){
  char* start = (char*)malloc(2 * sizeof(char));
  start[0] = '1';
  start[1] = '\0';

  if(n < 2)
    return start;

  char* result = (char*)malloc(2 * sizeof(char));
  result[0] = '1';
  result[1] = '\0';

  char* step = (char*)malloc(2 * sizeof(char));
  step[0] = '1';
  step[1] = '\0';

  for(int i = 1; i <n; ++i){
    char* tmp = start;
    start = intal_add(start, step);
    free(tmp);

    tmp = result;
    result = intal_multiply(start, result);
    free(tmp);
  }

  free(start);
  free(step);

  return result;
}

char* intal_bincoeff(unsigned int n, unsigned int k){
  if(k > n-k)
		k = n-k;
  char** c = (char**)malloc((k+1) * sizeof(char*));
  for(int i = 0; i < k + 1; ++i){
    c[i] = (char*)malloc(2 * sizeof(char));
    c[i][0] = '0';
    c[i][1] = '\0';
  }

  c[0][0] = '1';

  for(int i = 1; i < n + 1; ++i){
    int j = (i > k)? k: i;
    while(j > 0) {
      char* tmp = c[j];
      c[j] = intal_add(c[j], c[j - 1]);
      free(tmp);
      --j;
    }
  }

  char* result = (char*)malloc((strlen(c[k]) + 1) * sizeof(char));
  strcpy(result, c[k]);

  for(int i = 0; i < k + 1; ++i) {
    free(c[i]);
  }
  free(c);

  return result;
}


int intal_max(char **arr, int n) //iteratively find max
{
  int r=0;
  for (int i=1;i<n;i++){
    if (intal_compare(arr[i],arr[r])==1){
      r=i;
    }
  }
  return r;
}


int intal_min(char **arr, int n)//iteratively find min
{
  int r=0;
  for (int i=1;i<n;i++){
    if (intal_compare(arr[i],arr[r])==-1){
      r=i;
    }
  }
  return r;
}

int intal_search(char **arr, int n, const char* key)// uses same hlper function
{
  int r=-1;
  for (int i=0;i<n;i++){
    if (same(arr[i],key)==1){
      r=i;
      return r;
    }
  }
  return r;
}

static int binsearch(char **arr, int left, int right,const char *key){
  if (right>=left){
    int mid=left+(right-left)/2;

    if (intal_compare(arr[mid],key)==0){
      while(mid>0 && arr[mid-1]==key) // to get first occurrence
      {
        mid--;
      }
      return mid;
    }
    if (intal_compare(arr[mid],key)==1){
      return binsearch(arr,left,mid-1,key);
    }
    return binsearch(arr,mid+1,right,key);
  }
  return -1;
}

int intal_binsearch(char **arr, int n, const char* key){
  return binsearch(arr,0,n-1,key); // recurrsive function

}

static int partition(char** arr, int low, int high)// used for quicksort partition of array
{
  int i = low - 1;
  char* pivot = arr[high];

  for(int k = low; k < high; ++k){
    if(intal_compare(arr[k], pivot) < 0){
      ++i;
      char* temp = arr[i];
      arr[i] = arr[k];
      arr[k] = temp;
    }
  }

  char* temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;

  return (i + 1);
}

static void quicksort_function(char** arr, int low, int high) // helper function for recurrsion.
{
  if(low < high){
    int partition_index = partition(arr, low, high);
    quicksort_function(arr, low, partition_index - 1);
    quicksort_function(arr, partition_index + 1, high);
  }
}

void intal_sort(char **arr, int n){
  quicksort_function(arr, 0, n - 1);
}


char* coin_row_problem(char **arr, int n){
  char** f = (char**)malloc((n + 1) * sizeof(char*));
  f[0] = (char*)malloc(2 * sizeof(char));
  f[0][0] = '0';
  f[0][1] = '\0';

  for(int i = 0; i < n; ++i){
    f[i + 1] = (char*)malloc((strlen(arr[i]) + 1) * sizeof(char));
    strcpy(f[i + 1], arr[i]);
  }

  for(int i = 2; i < n + 1; ++i){
    char* val = intal_add(arr[i -1], f[i - 2]);
    if(intal_compare(val, f[i - 1]) > 0){
      char* tmp = f[i];
      f[i] = val;
      free(tmp);
    }else{
        free(f[i]);
        f[i] = (char*) malloc((strlen(f[i - 1]) + 1) * sizeof(char));
        strcpy(f[i], f[i - 1]);
        free(val);
    }
  }

  char* result = (char*)malloc((strlen(f[n]) + 1) * sizeof(char));
  strcpy(result, f[n]);

  for(int i = 0; i < n + 1; ++i) {
    free(f[i]);
  }
  free(f);

  return result;
}
