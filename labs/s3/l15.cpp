#include <iostream>
#include <random>
#include <cmath>

using namespace std;

template <class T>
class Queue
{

private:
    T *data_array;
    int *priority_array;
    int count = 0;

public:
    T pop()
    {
        if (count == 0)
            return 0;

        T *new_data_array;
        int *new_priority_array;

        new_data_array = new T[count - 1];
        new_priority_array = new int[count - 1];

        T item;
        item = data_array[0];

        for (int i = 0; i < count - 1; i++)
        {
            new_data_array[i] = data_array[i + 1];
            new_priority_array[i] = priority_array[i + 1];
        }

        if (count != 0)
        {
            delete[] data_array;
            delete[] priority_array;
        }

        --count;

        data_array = new_data_array;
        priority_array = new_priority_array;

        return item;
    }

    void push(T item, int priority)
    {

        T *new_data_array = (T *)new T[count + 1];
        int *new_priority_array = (int *)new int[count + 1];

        int pos = 0;

        for (pos; pos < count; ++pos)
            if (priority_array[pos] < priority)
                break;

        for (int i = 0; i < pos; ++i)
        {
            new_data_array[i] = data_array[i];
            new_priority_array[i] = priority_array[i];
        }

        new_data_array[pos] = item;
        new_priority_array[pos] = priority;

        for (int i = pos; i < count; ++i)
        {
            new_data_array[i + 1] = data_array[i];
            new_priority_array[i + 1] = priority_array[i];
        }

        if (count != 0)
        {
            delete[] data_array;
            delete[] priority_array;
        }

        data_array = new_data_array;
        priority_array = new_priority_array;

        ++count;

        return;
    }

    void print_me()
    {
        for (int i = 0; i < count; i++)
            cout << data_array[i] << ' ' << priority_array[i] << '\n';
        cout << '\n';

        return;
    }

    void delete_data()
    {
        if (count != 0)
        {
            delete[] data_array;
            delete[] priority_array;
        }
    }
};

int main()
{
    Queue<float> test;
    test.push(1.10, 2);
    test.push(2.22, 15);
    test.push(4.4, 10);
    test.push(3.3, 11);
    test.push(24.3, 15);

    test.print_me();
    cout << " " << test.pop() << " " << '\n';
    test.print_me();
}
