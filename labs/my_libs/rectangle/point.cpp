
#include <iostream>
/**
 * @brief Class for storing and manipulating with points
 * @details Class for storing and manipulating with points
 * @param x - x coordinate
 * @param y - y coordinate
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
        // std::cout << "Point destructor called" << std::endl;
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
    return (p1.get_x() < p2.get_x() || (p1.get_x() == p2.get_x() && p1.get_y() < p2.get_y())) ? p1 : p2;
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
    return (p1.get_x() > p2.get_x() || (p1.get_x() == p2.get_x() && p1.get_y() > p2.get_y())) ? p1 : p2;
}