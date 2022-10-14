/**
 * @file l10_rect.cpp
 * @author karaluv (egr.vrn@gmail.com)
 * @brief rectangle and point classes
 * @details rectangle and point classes with methods and operators
 * @version 0.1
 * @date 2022-10-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

/**
 * @brief Class for storing and manipulating with points
 * @details Class for storing and manipulating with points
 * @param x - x coordinate
 * @param y - y coordinate
 * @method get_x - returns x coordinate
 * @method get_y - returns y coordinate
 * @method set_x - sets x coordinate
 * @method set_y - sets y coordinate
 * @constructor Point - creates point with given coordinates
 */
class Point
{
private:
    int x, y;

public:
    /**
     * @brief default constructor for Point class
     * @details default Constructor for Point class, creates point with coordinates (0, 0)
     */
    Point()
    {
        x = 0;
        y = 0;
    }
    /**
     * @brief Constructor for Point class with parameters
     * @details Constructor for Point class with parameters, creates point with given coordinates
     * @param x - x coordinate
     * @param y - y coordinate
     */
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    /**
     * @brief default destructor for Point class
     * @details default destructor for Point class
     */
    ~Point()
    {
        cout << "Point destructor called" << endl;
    }
    /**
     * @brief copy constructor for Point class
     * @details copy constructor for Point class, creates point with coordinates of other point
     * @param other - point to copy
     */
    Point(Point const &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    /**
     * @brief copy assignment operator for Point class
     * @details copy assignment operator for Point class, which copies coordinates from other point
     * @param other - point to copy coordinates from
     * @return reference to this point
     */
    Point &operator=(Point const &other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    /**
     * @brief move constructor for Point class
     * @details move constructor for Point class, creates point with coordinates of other point
     * and sets coordinates of other point to (0, 0)
     * @param other - point to move
     * @return new point with coordinates of other point
     */
    Point(Point &&other)
    {
        this->x = other.x;
        this->y = other.y;
        other.x = 0;
        other.y = 0;
    }
    /**
     * @brief move assignment operator for Point class
     * @details move assignment operator for Point class, which copies coordinates from other point
     * and sets other point coordinates to (0, 0)
     * @param other - point to copy coordinates from
     * @return reference to this point
     */
    Point &operator=(Point &&other)
    {
        this->x = other.x;
        this->y = other.y;
        other.x = 0;
        other.y = 0;
        return *this;
    }
    /**
     * @brief Returns x coordinate
     * @return x coordinate
     */
    int get_x() const { return x; }
    /**
     * @brief Returns y coordinate
     * @return y coordinate
     */
    int get_y() const { return y; }
    /**
     * @brief Sets x coordinate
     * @param x - x coordinate
     */
    void set_x(int x) { this->x = x; }
    /**
     * @brief Sets y coordinate
     * @param y - y coordinate
     */
    void set_y(int y) { this->y = y; }
};

/**
 * @brief Function for finding point with min x and y
 * @details Function for finding point with min x and y
 * @param p1 - first point
 * @param p2 - second point
 * @return Point - point with min x and y
 */
Point min(Point const &p1, Point const &p2)
{
    return Point(min(p1.get_x(), p2.get_x()), min(p1.get_y(), p2.get_y()));
}
/**
 * @brief Function for finding point with max x and y
 * @details Function for finding point with max x and y
 * @param p1 - first point
 * @param p2 - second point
 * @return Point - point with max x and y
 */
Point max(Point const &p1, Point const &p2)
{
    return Point(max(p1.get_x(), p2.get_x()), max(p1.get_y(), p2.get_y()));
}

/**
 * @brief Class for storing and manipulating with rectangles
 * @details Class for storing and manipulating with rectangles
 */
class Rectangle : public Point
{
private:
public:
    /**
     * @brief default constructor
     * @details default constructor, creates rectangle with coordinates (0, 0)
     */
    Rectangle()
    {
        set_x(0);
        set_y(0);
    }
    /**
     * @brief constructor with parameters
     * @details constructor with parameters, creates rectangle with given coordinates
     * @param x - x coordinate
     * @param y - y coordinate
     */
    Rectangle(int x, int y)
        : Point(x, y)
    {
    }
    /**
     * @brief default destructor
     */
    ~Rectangle()
    {
        cout << "Rectangle destructor called" << endl;
    }
    /**
     * @brief copy constructor
     * @details copy constructor, which copies coordinates from other rectangle
     * @param other - other rectangle
     */
    Rectangle(Rectangle const &other)
        : Point(other)
    {
    }
    /**
     * @brief copy assignment operator
     * @details copy assignment operator, which copies coordinates from other rectangle
     * @param other - other rectangle
     * @return reference to this rectangle
     */
    Rectangle &operator=(Rectangle const &other)
    {
        Point::operator=(other);
        return *this;
    }
    /**
     * @brief move constructor
     * @details move constructor, which copies coordinates from other rectangle
     * and sets coordinates of other rectangle to (0, 0)
     * @param other - other rectangle
     */
    Rectangle(Rectangle &&other)
        : Point(other)
    {
    }
    /**
     * @brief move assignment operator
     * @details move assignment operator, which copies coordinates from other rectangle
     * and sets coordinates of other rectangle to (0, 0)
     * @param other - other rectangle
     * @return reference to this rectangle
     */
    Rectangle &operator=(Rectangle &&other)
    {
        Point::operator=(other);
        return *this;
    }
    /**
     * @brief gets x coordinate of the right upper corner
     * @details gets x coordinate of the right upper corner
     * @return x coordinate of the right upper corner
     */
    int get_x() const { return Point::get_x(); }
    /**
     * @brief gets y coordinate of the right upper corner
     * @details gets y coordinate of the right upper corner
     * @return y coordinate of the right upper corner
     */
    int get_y() const { return Point::get_y(); }
    /**
     * @brief sets x coordinate of the right upper corner
     * @details sets x coordinate of the right upper corner
     * @param x - x coordinate of the right upper corner
     */
    void set_x(int x) { Point::set_x(x); }
    /**
     * @brief sets y coordinate of the right upper corner
     * @details sets y coordinate of the right upper corner
     * @param y - y coordinate of the right upper corner
     */
    void set_y(int y) { Point::set_y(y); }
    /**
     * @brief calculates area of the rectangle
     * @details calculates area of the rectangle with coordinates of the right upper corner
     * @return area of the rectangle
     */
    int area() const
    {
        return get_x() * get_y();
    }
};

ostream &operator<<(ostream &os, Point const &p)
{
    os << "(" << p.get_x() << ", " << p.get_y() << ")";
    return os;
}
ostream &operator<<(ostream &os, Rectangle const &r)
{
    os << "Rectangle(" << r.get_x() << ", " << r.get_y() << ")";
    return os;
}
istream &operator>>(istream &is, Point &p)
{
    int x, y;
    is >> x >> y;
    p.set_x(x);
    p.set_y(y);
    return is;
}
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