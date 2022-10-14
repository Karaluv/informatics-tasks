#include <iostream>
#include <random>
#include <cmath>

using namespace std;

struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

class Rectangle
{
public:
    Point Coords;
    int X_Coord;
    int Y_Coord;

public:
    Rectangle(Point p)
    {
        Coords = p;
        X_Coord = p.x;
        Y_Coord = p.y;
    }
    Rectangle(int x, int y)
    {
        Coords = Point(x, y);
        X_Coord = x;
        Y_Coord = y;
    }
    // constructor which takes string (e.g. "(1,2)") and creates rectangle
    Rectangle(string str)
    {
        // create variables
        int x = 0;
        int y = 0;
        int i = 0;
        // loop through string
        for (i = 1; i < str.length(); i++)
        {
            // if char is digit
            if (isdigit(str[i]))
            {
                // add to x
                x = x * 10 + (str[i] - '0');
            }
            // if char is comma
            else if (str[i] == ',')
            {
                // break
                break;
            }
        }
        // loop through string
        for (i = i + 1; i < str.length(); i++)
        {
            // if char is digit
            if (isdigit(str[i]))
            {
                // add to y
                y = y * 10 + (str[i] - '0');
            }
            // if char is )
            else if (str[i] == ')')
            {
                // break
                break;
            }
        }
        // set coords
        Coords = Point(x, y);
        X_Coord = x;
        Y_Coord = y;
    }
    Rectangle()
    {
        // X_Coord = 0;
        // Y_Coord = 0;
        // Coords = Point(0, 0);
        static std::default_random_engine rng(10);
        static std::uniform_int_distribution<int> dstr(0, 10);
        X_Coord = dstr(rng);
        Y_Coord = dstr(rng);
    }
    void Update_Coords(int X, int Y)
    {
        X_Coord = X;
        Y_Coord = Y;
    }
    ~Rectangle() {}
};

Point min(Point p_1, Point p_2)
{
    return Point(min(p_1.x, p_2.x), min(p_1.y, p_2.y));
}
Point max(Point p_1, Point p_2)
{
    return Point(max(p_1.x, p_2.x), max(p_1.y, p_2.y));
}

// add operator < > == != >= <=, which compares the area of the rectangles
bool operator<(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return rectangle_1.X_Coord * rectangle_1.Y_Coord < rectangle_2.X_Coord * rectangle_2.Y_Coord;
}
bool operator>(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return rectangle_1.X_Coord * rectangle_1.Y_Coord > rectangle_2.X_Coord * rectangle_2.Y_Coord;
}
bool operator==(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return rectangle_1.X_Coord * rectangle_1.Y_Coord == rectangle_2.X_Coord * rectangle_2.Y_Coord;
}
bool operator!=(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return rectangle_1.X_Coord * rectangle_1.Y_Coord != rectangle_2.X_Coord * rectangle_2.Y_Coord;
}
bool operator<=(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return rectangle_1.X_Coord * rectangle_1.Y_Coord <= rectangle_2.X_Coord * rectangle_2.Y_Coord;
}
bool operator>=(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return rectangle_1.X_Coord * rectangle_1.Y_Coord >= rectangle_2.X_Coord * rectangle_2.Y_Coord;
}
// add operator + which returns maximum of x,y coordinates of two rectangles
Rectangle operator+(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return Rectangle(max(rectangle_1.Coords, rectangle_2.Coords));
}
// add operator * which returns minimum  of x,y coordinates of two rectangles
Rectangle operator*(Rectangle rectangle_1, Rectangle rectangle_2)
{
    return Rectangle(min(rectangle_1.Coords, rectangle_2.Coords));
}
// add operator *=, += which updates the coordinates of the rectangle
Rectangle operator*=(Rectangle &rectangle_1, Rectangle rectangle_2)
{
    rectangle_1.Update_Coords(min(rectangle_1.Coords, rectangle_2.Coords).x, min(rectangle_1.Coords, rectangle_2.Coords).y);
    return rectangle_1;
}
Rectangle operator+=(Rectangle &rectangle_1, Rectangle rectangle_2)
{
    rectangle_1.Update_Coords(max(rectangle_1.Coords, rectangle_2.Coords).x, max(rectangle_1.Coords, rectangle_2.Coords).y);
    return rectangle_1;
}

// create cout operator for rectangle
ostream &operator<<(ostream &os, const Rectangle &rec)
{
    os << '(' << rec.X_Coord << ", " << rec.Y_Coord << ')';
    return os;
}
// create cin operator for rectangle which uses rectangle constructor
istream &operator>>(istream &is, Rectangle &rec)
{
    string str;
    is >> str;
    rec = Rectangle(str);
    return is;
}
