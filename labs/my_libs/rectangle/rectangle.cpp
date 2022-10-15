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
#include <point.cpp>

using namespace std;

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
        // cout << "Rectangle destructor called" << endl;
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