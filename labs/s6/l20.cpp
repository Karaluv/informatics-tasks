/**
 * @file l20.cpp
 * @author karaluv (egr.vrn@gmail.com)
 * @brief multidimensional grid class
 * @details multidimensional grid class with methods and operators and some tests
 * @version 0.1
 * @date 2022-10-14
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "l10_rect.cpp"

using namespace std;

/**
 * @brief Class for manipulating with 2D arrays
 * @details Class for manipulating with 2D arrays based on template
 * @param T - type of array elements
 * @param size_x - size of array in x dimension
 * @param size_y - size of array in y dimension
 */
template <typename T>
class Grid final
{
    using value_type = T;
    using size_type = unsigned;

private:
    T *data;

protected:
    size_type y_size, x_size;

public:
    /**
     * @brief default constructor for 2D Grid class
     * @details default Constructor for 2D Grid class, creates 1x1 array with default value
     */
    Grid()
        : data(new T[1]), y_size(1), x_size(1) {}
    /**
     * @brief Constructor for 2D Grid class with parameter
     * @details Constructor for 2D Grid class with parameter, creates 1x1 array with given value
     * @param value - value to fill array with
     */
    Grid(T const &value)
        : data(new T[1]), y_size(1), x_size(1)
    {
        data[0] = value;
    }
    /**
     * @brief Constructor for 2D Grid class with parameters
     * @details Constructor for 2D Grid class with parameters, creates array with given x and y sizes and default value
     * @param y_size - size of array in y dimension
     * @param x_size - size of array in x dimension
     */
    Grid(size_type const y_size, size_type const x_size)
        : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
    }
    /**
     * @brief Constructor for 2D Grid class with parameters
     * @details Constructor for 2D Grid class with parameters, creates array with given x and y sizes and given value
     * @param value - value to fill array with
     * @param y_size - size of array in y dimension
     * @param x_size - size of array in x dimension
     */
    Grid(T const &value, size_type const y_size, size_type const x_size)
        : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = value;
    }
    /**
     * @brief default destructor for 2D Grid class
     * @details default destructor for 2D Grid class
     */
    ~Grid()
    {
        cout << "Grid destructor called" << endl;
        delete[] data;
    }
    /**
     * @brief copy constructor for 2D Grid class
     * @details copy constructor for 2D Grid class, creates array with same values as other array
     * @param other - array to copy
     */
    Grid(Grid const &other)
        : data(new T[other.y_size * other.x_size]), y_size(other.y_size), x_size(other.x_size)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = other.data[i];
    }
    /**
     * @brief copy assignment operator for 2D Grid class
     * @details copy assignment operator for 2D Grid class, copies values from other array
     * @param other - array to copy
     * @return reference to this array
     */
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
    /**
     * @brief move constructor for 2D Grid class
     * @details move constructor for 2D Grid class, creates array with same values as other array and sets other array to default
     * @param other - array to move
     */
    Grid(Grid &&other)
        : data(other.data), y_size(other.y_size), x_size(other.x_size)
    {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }
    /**
     * @brief move assignment operator for 2D Grid class
     * @details move assignment operator for 2D Grid class, moves values from other array and sets other array to default
     * @param other - array to move
     * @return reference to this array
     */
    Grid &operator=(Grid &&other)
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            // other.data = nullptr;
        }
        return *this;
    }

    /**
     * @brief operator which sets all values in array to given value
     * @details operator which sets all values in array to given value
     * @param value - value to set
     * @return reference to this array
     */
    Grid &operator=(T const &value)
    {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = value;
        return *this;
    }

    /**
     * @brief provides access to array row
     * @details provides access to array row with help of operator [] using proxy class
     * @param y - row number
     * @return proxy class
     */
    class Proxy final
    {
        T *data;
        size_type const x_size;

    public:
        /**
         * @brief default constructor for proxy class
         * @details default constructor for proxy class
         * @param data - pointer to array
         * @param x_size - size of array in x dimension
         */
        Proxy(T *data, size_type const x_size)
            : data(data), x_size(x_size)
        {
        }
        /**
         * @brief default destructor for proxy class
         * @details default destructor for proxy class
         */
        ~Proxy() = default;
        /**
         * @brief provides access to array element
         * @details provides access to array element with help of operator []
         * @param x - element number
         * @return reference to element
         */
        T &operator[](size_type const x)
        {
            assert(x < x_size);
            return data[x];
        }
        /**
         * @brief gives size of array in x dimension
         * @details gives size of array in x dimension
         * @return size of array in x dimension
         */
        size_type get_size() const
        {
            return x_size;
        }
    };
    /**
     * @brief provides access to array row
     * @details provides access to array row with help of operator [] using proxy class
     * @param y - row number
     * @return proxy class
     */
    Proxy operator[](size_type const y)
    {
        assert(y < y_size);
        return Proxy(data + y * x_size, x_size);
    }

    /**
     * @brief gives size of array in y dimension
     * @details gives size of array in y dimension
     * @return size of array in y dimension
     */
    size_type get_size() const { return y_size; }
};

/**
 * @brief Class for manipulating with n-dimensional arrays
 * @details Class for manipulating with n-dimensional arrays based on template and recursion
 * @param T - type of array elements
 * @param N - number of dimensions
 * @param MySize - size of array in N dimension
 * @param data - pointer to array of N-1 dimension grid
 * @method get_size - size of array in N dimension
 * @operator [] - returns array row of N-1 dimension grid
 */
template <typename T, unsigned N>
class NGrid final
{
    using value_type = T;
    using size_type = unsigned;

private:
    size_type MySize;
    using GridType = typename std::conditional<N == 3, Grid<T>, NGrid<T, N - 1>>::type;
    GridType *data;

public:
    /**
     * @brief Default constructor
     * @details Default constructor which creates empty grid with size 1
     */
    NGrid()
    {
        MySize = 1;
        data = new GridType[MySize];
    }
    /**
     * @brief Constructor which takes single element and copies it to (1,...,1) grid
     * @details Constructor which takes single element and copies it to (1,...,1) grid
     * @param value - single element
     */
    NGrid(T const &value)
    {
        cout << N << endl;
        MySize = 1;
        data = new GridType[MySize];
        data[0] = value;
    }
    /**
     * @brief Constructor which takes size of array in N dimension and creates grid field with single element
     * @details Constructor which takes size of array in N dimension and creates grid field with single element
     * @param value - single element
     * @param size - size of array in N dimension
     * @param args - size of array in N-1 dimensions
     */
    template <typename... Args>
    NGrid(T const &value, size_type const size, Args... args)
    {
        MySize = size;
        data = new GridType[MySize];
        for (size_type i = 0; i < MySize; ++i)
        {
            GridType temp(value, args...);
            data[i] = temp;
        }
    }
    /**
     * @brief destructor
     * @details destructor which deletes grid field
     */
    ~NGrid()
    {
        cout << "NGrid destructor called" << endl;
        delete[] data;
    }
    /**
     * @brief copy constructor
     * @details copy constructor which copies grid field
     * @param other - grid field to copy
     */
    NGrid(NGrid const &other)
    {
        MySize = other.MySize;
        data = new GridType[MySize];
        for (size_type i = 0; i < MySize; ++i)
            data[i] = other.data[i];
    }
    /**
     * @brief copy assignment operator
     * @details copy assignment operator which copies grid field
     * @param other - reference to NGrid object
     * @return reference to NGrid object
     */
    NGrid &operator=(NGrid const &other)
    {
        if (this != &other)
        {
            delete[] data;
            MySize = other.MySize;
            data = new GridType[MySize];
            for (size_type i = 0; i < MySize; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    /**
     * @brief move constructor
     * @details move constructor which moves grid field
     * @param other - grid field to move
     * @return reference to NGrid object
     */
    NGrid(NGrid &&other)
    {
        MySize = other.MySize;
        data = other.data;
        other.data = nullptr;
    }
    /**
     * @brief move assignment operator
     * @details move assignment operator which moves grid field
     * @param other - reference to NGrid object
     * @return reference to NGrid object
     */
    NGrid &operator=(NGrid &&other)
    {
        if (this != &other)
        {
            delete[] data;
            MySize = other.MySize;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
    /**
     * @brief method which returns size of array in N dimension
     * @details method which returns size of array in N dimension
     * @return size of array in N dimension
     */
    size_type get_size() const { return MySize; }

    /**
     * @brief operator [] which returns N-1 dimension grid
     * @details operator [] which returns N-1 dimension grid
     * @param idx - index of N-1 dimension grid
     * @return N-1 dimension grid
     */
    GridType &operator[](size_type const idx)
    {
        assert(idx < MySize);
        return data[idx];
    }
};

int main()
{
    // create some tests
    {
        // 3 dimensional grid
        NGrid<int, 3> grid;
        assert(grid.get_size() == 1);
    }
    cout << "Test 1 passed" << endl;
    {
        NGrid<int, 3> grid(2);
        // test
        assert(grid.get_size() == 1);
    }
    // print tests passed
    cout << "Test 2 passed" << endl;
    {
        // test for 4 dimensional grid
        NGrid<string, 4> grid("test");
        assert(grid.get_size() == 1);
    }
    cout << "Test 3 passed" << endl;
    {
        NGrid<string, 3> grid("test", 2, 1, 1);
    }
    cout << "Test 4 passed" << endl;
    {

        NGrid<Rectangle, 4> grid(Rectangle(1, 1), 3, 2, 1, 1);

        assert(grid.get_size() == 3);
        assert(grid[0].get_size() == 2);
        assert(grid[0][0].get_size() == 1);
        assert(grid[0][0][0].get_size() == 1);
    }
    cout << "Test 5 passed" << endl;
    {
        Rectangle rect1(1, 1);
        Rectangle rect2(2, 2);
        Rectangle rect3(3, 3);
        Rectangle rect4(4, 4);

        NGrid<Rectangle, 5> grid(rect1, 2, 2, 2, 2, 2);

        grid[0][0][0][0][0] = rect2;
        grid[1][1][1][1][1] = rect3;

        assert(grid[0][0][0][0].get_size() == 2);

        grid[1][0][0][0][0] = rect3;

        assert(grid[1][0][0][0].get_size() == 2);

        assert(grid[0][0][0][0][0] == rect2);
        assert(grid[1][1][1][1][1] == rect3);

        rect2 = Rectangle(4, 4);

        assert(grid[0][0][0][0][0] != rect2);

        rect2 = grid[0][0][0][0][0];

        assert(grid[0][0][0][0][0] == rect2);
    }
    cout << "Test 6 passed" << endl;
    cout << "All tests passed!!!" << endl;
    return 0;
}