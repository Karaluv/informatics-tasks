// include standard library
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
// include our library
#include "l10_rect.cpp"

using namespace std;

template <typename T>
class Grid final
{
    using value_type = T;
    using size_type = unsigned;

protected:
    size_type const y_size, x_size;

public:
    // default constructor
    Grid()
        : data(new T[1]), y_size(1), x_size(1)
    {
        // create full copy of value value

        data[0] = value;
    }
    // constructor which takes single element and copies it to (1,1) grid
    Grid(T const &value)
        : data(new T[1]), y_size(1), x_size(1)
    {
        // create full copy of value value

        data[0] = value;
    }
    // constructor which takes y_size and x_size and creates empty grid
    Grid(size_type const y_size, size_type const x_size)
        : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
    }
    // constructor which takes single element and copies it to all elements
    Grid(T const &value, size_type const y_size, size_type const x_size)
        : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = value;
    }
    // destructor
    ~Grid()
    {
        cout << "Grid destructor called" << endl;
        delete[] data;
    }
    // copy constructor
    Grid(Grid const &other)
        : data(new T[other.y_size * other.x_size]), y_size(other.y_size), x_size(other.x_size)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = other.data[i];
    }
    // copy assignment operator
    Grid &operator=(Grid const &other)
    {
        if (this != &other)
        {
            delete[] data;
            data = new T[other.y_size * other.x_size];
            y_size = other.y_size;
            x_size = other.x_size;
            for (size_type i = 0; i < y_size * x_size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    // move constructor
    Grid(Grid &&other)
        : data(other.data), y_size(other.y_size), x_size(other.x_size)
    {
        other.data = nullptr;
    }
    // move assignment operator
    Grid &operator=(Grid &&other)
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
        }
        return *this;
    }

    // operator = which takes single element and copies it to all elements
    Grid &operator=(T const &value)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = value;
        return *this;
    }

    // operator [][] which returns proxy class
    class Proxy final
    {
        T *data;
        size_type const x_size;

    public:
        Proxy(T *data, size_type const x_size)
            : data(data), x_size(x_size)
        {
        }
        T &operator[](size_type const x)
        {
            assert(x < x_size);
            return data[x];
        }
    };
    // operator [] which returns proxy class
    Proxy operator[](size_type const y)
    {
        assert(y < y_size);
        return Proxy(data + y * x_size, x_size);
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

private:
    T *const data;

    T operator()(size_type y_idx, size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }
    T &operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }
};

int main()
{
    // create some tests
    {
        Grid<int> grid(1);
        // cout << grid[0][0];
        assert(grid[0][0] == 1);
        grid[0][0] = 2;
        assert(grid[0][0] == 2);
        grid = 3;
        assert(grid[0][0] == 3);
    }
    // print "tests passed" to console
    cout << "tests passed" << endl;
    {
        Grid<int> grid2(2, 2);
        grid2[0][0] = 1;
        grid2[0][1] = 2;
        grid2[1][0] = 3;
        grid2[1][1] = 4;
        assert(grid2[0][0] == 1);
        assert(grid2[0][1] == 2);
        assert(grid2[1][0] == 3);
        assert(grid2[1][1] == 4);
    }
    // print "tests passed" to console
    cout << "tests passed" << endl;
    {
        // test with string
        Grid<string> grid3("test", 2, 2);
        assert(grid3[0][0] == "test");
        assert(grid3[0][1] == "test");
        assert(grid3[1][0] == "test");
        assert(grid3[1][1] == "test");
    }
    // print "tests passed" to console
    cout << "tests passed" << endl;
    {
        // create rectangle
        Rectangle rect(1, 2);
        // create grid with rectangle
        Grid<Rectangle> grid4(rect, 2, 2);
        // check if grid has correct values
        assert(grid4[0][0] == rect);
        assert(grid4[0][1] == rect);
        assert(grid4[1][0] == rect);
        assert(grid4[1][1] == rect);
        // update rectangle
        rect.set_x(3);
        rect.set_y(4);
        // check if grid has correct values
        assert(grid4[0][0] != rect);
        assert(grid4[0][1] != rect);
        assert(grid4[1][0] != rect);
        assert(grid4[1][1] != rect);

        grid4 = rect;
        // check if grid has correct values
        assert(grid4[0][0] == rect);
        assert(grid4[0][1] == rect);
        assert(grid4[1][0] == rect);
        assert(grid4[1][1] == rect);
    }
    // print "tests passed" to console
    cout << "tests passed" << endl;

    return 0;
}