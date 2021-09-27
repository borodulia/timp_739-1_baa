#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printFile(int *arr, int n, char *fileName)
{
  FILE *fout;
  fout = fopen(fileName, "a+");
  for (int i = 0; i < n; ++i)
    fprintf(fout, "%d ", arr[i]);
  fprintf(fout, "\n");
  fclose(fout);
}

void quickSort(int *array, int left, int right, int size)
{
  int i = left;
  int j = right;
  int privot = array[right + (left - right) / 2];
  do
  {
    while (array[i] < privot)
      i++;
    while (array[j] > privot)
      j--;
    if (i <= j)
    {
      if (array[i] > array[j])
      {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
      i++;
      if (j > 0)
        j--;
      printFile(array, size, "quicksort.log");
    }
  } while (i <= j);
  if (i < right)
    quickSort(array, i, right, size);
  if (j > left)
    quickSort(array, left, j, size);
}

void siftDown(int *numbers, int root, int bottom, int size)
{
  printFile(numbers, size, "heapsort.log");
  int maxChild;
  int done = 0;
  while ((root * 2 <= bottom) && (!done))
  {
    if (root * 2 == bottom)
      maxChild = root * 2;
    else if (numbers[root * 2] > numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    if (numbers[root] < numbers[maxChild])
    {
      int temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

void heapSort(int *numbers, int array_size)
{
  for (int i = (array_size / 2); i >= 0; i--)
  {
    siftDown(numbers, i, array_size - 1, array_size);
  }
  for (int i = array_size - 1; i >= 1; i--)
  {
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDown(numbers, 0, i - 1, array_size);
  }
}

int main()
{
  int size;
  scanf("%d", &size);
  int *arr = (int *)malloc(arr, size * sizeof(int));
  int *sortArr = (int *)malloc(sortArr, size * sizeof(int));
  for (int i = 0; i < size; i++)
  {
    scanf("%d", &sortArr[i]);
    arr[i] = sortArr[i];
  }
  quickSort(sortArr, 0, size - 1, size);
  heapSort(arr, size);
  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}