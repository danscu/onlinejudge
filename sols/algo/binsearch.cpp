#include <stdio.h>
#include <stdlib.h>

bool in_array(int what_to_find, const int *array, int array_size, bool sorted)
{
    int i, j;
    if (!sorted) {
        for (i = 0; i < array_size; i++)
            if (array[i] == what_to_find)
                return true;
        return false;
    } else {
        // binary search
        if (array_size == 0)
            return false;
        i = 0; j = array_size - 1;
        while (i < j) {
            int m = (i + j) / 2;
            if (what_to_find < array[m])
                j = m - 1;
            else if (what_to_find > array[m])
                i = m + 1;
            else
                return true;
        }
        return array[i] == what_to_find;
    }
}

int main() {
    int arr[] = {1, 4, 5, 7, 7, 8, 9, 10};

    for (int i = 0; i <= 12; i++) {
        printf("in_array(%d) = %d\n", i,
                in_array(i, arr, sizeof(arr) / sizeof(arr[0]), true));
    }

    return 0;
}
