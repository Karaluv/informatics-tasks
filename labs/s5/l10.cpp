#include <iostream>
#include <random>
#include <cmath>
#include "l10_rect.cpp"

using namespace std;

template <typename T>
struct Comparator
{
    virtual bool operator()(T const &, T const &) const = 0;
};
template <>
struct Comparator<int>
{
    bool operator()(int const &Iha, int const &rha) const
    {
        return Iha < rha;
    }
};
template <>
struct Comparator<Rectangle>
{
    bool operator()(Rectangle const &Iha, Rectangle const &rha) const
    {
        return (Iha.X_Coord * Iha.Y_Coord < rha.X_Coord * rha.Y_Coord);
    }
};

template <class T>
T *partion(T *arr_begin, T *arr_end, T value)
{
    Comparator<T> Compar;
    int length = static_cast<int>(arr_end - arr_begin);

    int i = 0;
    int j = length - 1;

    while (true)
    {
        // while (*(arr_begin + i) < value)
        while (Compar(*(arr_begin + i), value))
            i = i + 1;
        // while (*(arr_begin + j) > value)
        while (Compar(*(arr_begin + j), value))

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
    int length = static_cast<int>(arr_end - arr_begin);

    if (arr_end <= arr_begin)
        return;

    T *split = partion(arr_begin, arr_end, *(arr_begin + (length - 1) / 2));

    if (split + 1 < arr_end)
    {
        sort(arr_begin, split + 1);
        sort(split + 1, arr_end);
    }
}

int main()
{
    std::mt19937 rng(std::random_device{}());

    int test1[10] = {10, -3, 44, 58, 7, 141, 8, 653, -10, 12};
    sort(test1, test1 + 10);
    for (int i = 0; i < 10; i++)
        cout << test1[i] << ' ';
    cout << '\n';

    Rectangle recs[10];

    for (int i = 0; i < 10; ++i)
        cout << recs[i] << ' ';
    cout << '\n';

    sort(recs, recs + 10);
    for (int i = 0; i < 10; ++i)
        cout << recs[i] << ' ';
    cout << '\n';

    system("pause");
    return 0;
}