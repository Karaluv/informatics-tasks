#include <iostream>
#include <random>
#include <cmath>

using namespace std;

// class point using ints
class Point
{
private:
    int x, y;

public:
    // default constructor
    Point()
    {
        x = 0;
        y = 0;
    }
    // constructor
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    // destructor
    ~Point()
    {
        // cout << "Point destructor called" << endl;
    }
    // copy constructor
    Point(Point const &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    // copy assignment operator
    Point &operator=(Point const &other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    // move constructor
    Point(Point &&other)
    {
        this->x = other.x;
        this->y = other.y;
        other.x = 0;
        other.y = 0;
    }
    // move assignment operator
    Point &operator=(Point &&other)
    {
        this->x = other.x;
        this->y = other.y;
        other.x = 0;
        other.y = 0;
        return *this;
    }
    // getters
    int get_x() const { return x; }
    int get_y() const { return y; }
    // setters
    void set_x(int x) { this->x = x; }
    void set_y(int y) { this->y = y; }
};

// function min, max which return new point with min, max x and y
Point min(Point const &p1, Point const &p2)
{
    return Point(min(p1.get_x(), p2.get_x()), min(p1.get_y(), p2.get_y()));
}
Point max(Point const &p1, Point const &p2)
{
    return Point(max(p1.get_x(), p2.get_x()), max(p1.get_y(), p2.get_y()));
}

// class rectangle which inherits from point
class Rectangle : public Point
{
private:
public:
    // default constructor
    Rectangle()
    {
        set_x(0);
        set_y(0);
    }
    // constructor
    Rectangle(int x, int y)
        : Point(x, y)
    {
    }
    // destructor
    ~Rectangle()
    {
        // cout << "Rectangle destructor called" << endl;
    }
    // copy constructor
    Rectangle(Rectangle const &other)
        : Point(other)
    {
    }
    // copy assignment operator
    Rectangle &operator=(Rectangle const &other)
    {
        Point::operator=(other);
        return *this;
    }
    // move constructor
    Rectangle(Rectangle &&other)
        : Point(other)
    {
    }
    // move assignment operator
    Rectangle &operator=(Rectangle &&other)
    {
        Point::operator=(other);
        return *this;
    }
    // getters
    int get_x() const { return Point::get_x(); }
    int get_y() const { return Point::get_y(); }
    // setters
    void set_x(int x) { Point::set_x(x); }
    void set_y(int y) { Point::set_y(y); }
    // function area which returns area of rectangle
    int area() const
    {
        return get_x() * get_y();
    }
};

// operator << which prints point
ostream &operator<<(ostream &os, Point const &p)
{
    os << "(" << p.get_x() << ", " << p.get_y() << ")";
    return os;
}
// operator << which prints rectangle
ostream &operator<<(ostream &os, Rectangle const &r)
{
    os << "(" << r.get_x() << ", " << r.get_y() << ")";
    return os;
}
// operator >> which reads point
istream &operator>>(istream &is, Point &p)
{
    int x, y;
    is >> x >> y;
    p.set_x(x);
    p.set_y(y);
    return is;
}
// operator >> which reads rectangle
istream &operator>>(istream &is, Rectangle &r)
{
    int x, y;
    is >> x >> y;
    r.set_x(x);
    r.set_y(y);
    return is;
}
// operator == which checks if two points are equal
bool operator==(Point const &p1, Point const &p2)
{
    return p1.get_x() == p2.get_x() && p1.get_y() == p2.get_y();
}
// operator == which checks if two rectangles area equal
bool operator==(Rectangle const &r1, Rectangle const &r2)
{
    return r1.area() == r2.area();
}
// operator != which checks if two points are not equal
bool operator!=(Point const &p1, Point const &p2)
{
    return !(p1 == p2);
}
// operator != which checks if two rectangles area not equal
bool operator!=(Rectangle const &r1, Rectangle const &r2)
{
    return !(r1 == r2);
}
// operator < which checks if first rectangle area is less than second
bool operator<(Rectangle const &r1, Rectangle const &r2)
{
    return r1.area() < r2.area();
}
// operator > which checks if first rectangle area is greater than second
bool operator>(Rectangle const &r1, Rectangle const &r2)
{
    return r1.area() > r2.area();
}
// operator <= which checks if first rectangle area is less or equal than second
bool operator<=(Rectangle const &r1, Rectangle const &r2)
{
    return r1.area() <= r2.area();
}
// operator >= which checks if first rectangle area is greater or equal than second
bool operator>=(Rectangle const &r1, Rectangle const &r2)
{
    return r1.area() >= r2.area();
}
// operator + which returns new rectangle with max x and y of two rectangles
Rectangle operator+(Rectangle const &r1, Rectangle const &r2)
{
    return Rectangle(max(r1, r2));
}
// operator * which returns new rectangle with min x and y of two rectangles
Rectangle operator*(Rectangle const &r1, Rectangle const &r2)
{
    return Rectangle(min(r1, r2));
}