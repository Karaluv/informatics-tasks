#include <iostream>
#include <string>
#include <random>

#include "l10_rect.cpp"

template <typename T>
class Comparator
{
public:
    bool operator()(T &a, T &b)
    {
        return a < b;
    }
};

template <typename T>
class MyVector
{
private:
    T *arr;
    int size;
    int capacity;

public:
    MyVector()
    {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }
    ~MyVector()
    {
        // check if arr is not null

        if (size != 0)
        {
            delete[] arr;
        }
    }
    void push_back(T &t)
    {
        if (size == capacity)
        {
            capacity *= 2;
            T *temp = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        arr[size++] = t;
    }
    void pop_back()
    {
        if (size > 0)
        {
            size--;
        }
    }
    void clear()
    {
        delete[] arr;
        arr = new T[0];

        size = 0;
    }
    T &operator[](int index)
    {
        return arr[index];
    }
    friend std::istream &operator>>(std::istream &in, MyVector<T> &v)
    {
        in >> v.size;
        for (int i = 0; i < v.size; i++)
        {
            in >> v.arr[i];
        }
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, MyVector<T> &v)
    {
        out << v.size << std::endl;
        for (int i = 0; i < v.size; i++)
        {
            out << v.arr[i] << " ";
        }
        return out;
    }
    MyVector(MyVector<T> &other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }
    MyVector<T> &operator=(MyVector<T> &other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
        return *this;
    }
    MyVector(MyVector<T> &&other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = other.arr;
        other.arr = nullptr;
    }
    MyVector<T> &operator=(MyVector<T> &&other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = other.arr;
        other.arr = nullptr;
        return *this;
    }
};

template <typename T, typename Comparator>
class BinaryHeap
{
private:
    MyVector<T> v;
    Comparator comp;
    int Size;

public:
    BinaryHeap()
    {
        Size = 0;
    }
    ~BinaryHeap()
    {
        // delete v
    }
    void push_back(T &t)
    {
        v.push_back(t);
        Size++;
        int index = Size - 1;
        while (index > 0 && comp(v[index], v[(index - 1) / 2]))
        {
            T temp = v[index];
            v[index] = v[(index - 1) / 2];
            v[(index - 1) / 2] = temp;
            index = (index - 1) / 2;
        }
    }
    void pop_back()
    {
        if (Size > 0)
        {
            v[0] = v[Size - 1];
            Size--;
            int index = 0;
            while (index < Size)
            {
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                int min = index;
                if (left < Size && comp(v[left], v[min]))
                {
                    min = left;
                }
                if (right < Size && comp(v[right], v[min]))
                {
                    min = right;
                }
                if (min != index)
                {
                    T temp = v[index];
                    v[index] = v[min];
                    v[min] = temp;
                    index = min;
                }
                else
                {
                    break;
                }
            }
        }
    }
    void print()
    {
        int level = 0;
        int count = 0;
        for (int i = 0; i < Size; i++)
        {
            std::cout << v[i] << " ";
            count++;
            if (count == pow(2, level))
            {
                std::cout << std::endl;
                level++;
                count = 0;
            }
        }
        std::cout << std::endl;
    }
    int size()
    {
        return Size;
    }

    bool empty()
    {
        return Size == 0;
    }
    T top()
    {
        return v[0];
    }
    void clear()
    {
        Size = 0;
        v.clear();
    }
    MyVector<T> getVector()
    {
        return v;
    }
};

int main()
{
    {
        BinaryHeap<int, Comparator<int>> heap;
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;
        int e = 5;
        heap.push_back(a);
        heap.push_back(b);
        heap.push_back(c);
        heap.push_back(d);
        heap.push_back(e);
        heap.print();
        std::cout << "Test has passed" << std::endl;
    }

    {
        BinaryHeap<Rectangle, Comparator<Rectangle>> heap1;

        Rectangle r1(1, 2);
        Rectangle r2(3, 3);
        Rectangle r3(3, 1);
        Rectangle r4(4, 4);
        Rectangle r5(5, 1);
        heap1.push_back(r5);
        heap1.push_back(r3);
        heap1.push_back(r4);
        heap1.push_back(r2);
        heap1.push_back(r1);
        heap1.print();
        heap1.pop_back();
        heap1.print();
        heap1.top();
        heap1.empty();
        heap1.size();
        MyVector<Rectangle> v = heap1.getVector();
        std::cout << v << std::endl;
        std::cout << v << std::endl;
        heap1.print();
        heap1.clear();
        heap1.print();
        std::cout << "Rectangle tests passed" << std::endl;
    }
    {
        Rectangle r1(1, 2);
        Rectangle r2(3, 4);
        Rectangle r3(5, 6);
        Rectangle r4(7, 8);
        Rectangle r5(9, 10);
        Comparator<Rectangle> comp;
        std::cout << comp(r1, r2) << std::endl;
        std::cout << comp(r2, r1) << std::endl;
        std::cout << comp(r1, r1) << std::endl;
        std::cout << r1 << std::endl;
        std::cout << r2 << std::endl;
        std::cout << r3 << std::endl;
        std::cout << r4 << std::endl;
        std::cout << r5 << std::endl;
        std::cout << (r1 == r2) << std::endl;
        std::cout << (r1 == r1) << std::endl;
        std::cout << (r1 != r2) << std::endl;
        std::cout << (r1 != r1) << std::endl;
        std::cout << (r1 < r2) << std::endl;
        std::cout << (r1 < r1) << std::endl;
        std::cout << (r1 > r2) << std::endl;
        std::cout << (r1 > r1) << std::endl;
        std::cout << (r1 <= r2) << std::endl;
        std::cout << (r1 <= r1) << std::endl;
        std::cout << (r1 >= r2) << std::endl;
        std::cout << (r1 >= r1) << std::endl;
        // std::cout << (r1 + r2) << std::endl;
        // std::cout << (r1 - r2) << std::endl;
        // std::cout << (r1 * r2) << std::endl;
    }

    std::cout << "test successful" << std::endl;
    std::system("pause");
    return 0;
}