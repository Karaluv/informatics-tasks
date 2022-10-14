#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <vector>
#include "l10_rect.cpp"

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
template <typename T>
class MyVector
{
private:
    int Size = 0;
    T *arr = new T[Size];

public:
    MyVector() {}
    ~MyVector()
    {
        delete[] arr;
    }
    void push_back(T const &value)
    {
        T *temp = new T[Size + 1];
        for (int i = 0; i < Size; i++)
        {
            temp[i] = arr[i];
        }
        temp[Size] = value;
        delete[] arr;
        arr = temp;
        Size++;
    }
    void pop_back()
    {
        T *temp = new T[Size - 1];
        for (int i = 0; i < Size - 1; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        Size--;
    }
    T &operator[](int index)
    {
        return arr[index];
    }
    int size()
    {
        return Size;
    }
    // empty
    bool empty()
    {
        return Size == 0;
    }
    // clear
    void clear()
    {
        delete[] arr;
        Size = 0;
    }
};

template <typename T>
class Tree
{
private:
    int Size = 0;
    MyVector<T> heap;
    // vector<T> heap;
    Comparator<T> comp;

public:
    Tree()
    {

        // heap.push_back(None)
    }
    void push(T n)
    {
        int i = Size;
        int parent = (i - 1) / 2;

        heap.push_back(n);
        while ((i > 0) && (parent >= 0))
        {
            if (!(comp(heap[i], heap[parent])))
                std::swap(heap[i], heap[parent]);
            i = parent;
            parent = (parent - 1) / 2;
        }
        Size++;
    }
    void print()
    {
        int i = 0;
        int j = 1;
        while (i < Size)
        {
            while ((i < j) && (i < Size))
            {
                std::cout << heap[i] << '\t';
                ++i;
            }
            j = j * 2 + 1;
            std::cout << '\n';
        }
    }
    void ReAlign(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < Size)
        {
            if (heap[i] < heap[left])
            {
                std::swap(heap[i], heap[left]);
                ReAlign(left);
            }

            if (right < Size)
                if (comp(heap[i], heap[right]))
                {
                    std::swap(heap[i], heap[right]);
                    ReAlign(right);
                }
        }
    }
    void point(void)
    {
        Size--;
        //   heap.erase(heap.begin());
        heap.empty();
        ReAlign(0);
    }
    T pick()
    {
        return heap[0];
    }
    bool is_empty()
    {
        if (Size == 0)
            return false;

        if (Size > 0)
            return true;

        std::cout << "error";
        return 0;
    }

    void free()
    {
        // heap.erase(heap.begin() + Size - 1);
        // heap.EraseMe();
        Size = 0;
    }
};
int main()
{

    static std::default_random_engine rng(100);
    static std::uniform_int_distribution<int> dstr(0, 100);

    Tree<int> T1;
    T1.print();
    std::cout << T1.is_empty() << '\n';
    for (int i = 0; i < 7; i++)
    {
        T1.push(dstr(rng));
    }

    T1.print();
    std::cout << T1.is_empty() << '\n';
    std::cout << "root " << T1.pick() << '\n';
    T1.point();
    T1.print();
    std::cout << "root " << T1.pick() << '\n';
    T1.free();
    T1.is_empty();
    return 0;
}