#include <iostream>
#include <random>
#include <cmath>

using namespace std;
template <class T>

T *partion(T *arr_begin, T *arr_end, T value)
{
    int length = arr_end - arr_begin;

    int i = 0;
    int j = length - 1;

    while (true)
    {
        while (*(arr_begin + i) < value)
            i = i + 1;
        while (*(arr_begin + j) > value)
            j = j - 1;
        if (j <= i)
            return (arr_begin + j);

        swap(*(arr_begin + i), *(arr_begin + j));
        i++;
        j--;
    }
}

template <class T>
void sort(T *arr_begin, T *arr_end)
{
    int length = arr_end - arr_begin;

    if (arr_end <= arr_begin)
        return;

    T *split = partion(arr_begin, arr_end, *(arr_begin + (length - 1) / 2));

    if (split + 1 < arr_end)
    {
        sort(arr_begin, split);
        sort(split + 1, arr_end);
    }
}

int main()
{
    int test1[10] = {10, -3, 44, 58, 7, 141, 8, 653, -10, 12};
    sort(test1, test1 + 10);
    for (int i = 0; i < 10; i++)
        cout << test1[i] << ' ';
    cout << '\n';

    char test2[7] = {'z', 'e', 't', 'a', 'g', 'a', 'p'};

    sort(test2, test2 + 7);
    for (int i = 0; i < 7; ++i)
        cout << (int)test2[i] << ' ';
    cout << '\n';

    return 0;
}