#include <iostream>
#include <string>
#include <vector>

#include "l10_rect.cpp"

using namespace std;

template <typename T>
struct Converter
{
    virtual void operator()(string str) const = 0;
};
template <>
struct Converter<int>
{
    int operator()(string str) const
    {
        return stoi(str);
    }
};
template <>
struct Converter<Rectangle>
{
    Rectangle operator()(string str) const
    {
        return Rectangle(str);
    }
};

template <typename T>
class Calculator
{
public:
    Calculator(string expression)
    {
        this->expression = expression;
    }
    ~Calculator()
    {
    }
    T evaluate()
    {
        vector<T> numbers;
        vector<char> operators;

        string number = "";

        Converter<T> Convert;
        // read numbers and operators from expression
        for (int i = 0; i < expression.length(); i++)
        {

            if (expression[i] == '+' || expression[i] == '*')
            {
                numbers.push_back(Convert(number));
                operators.push_back(expression[i]);
                number = "";
            }
            else if (true)
            {
                number += expression[i];
            }
        }
        numbers.push_back(Convert(number));

        for (int i = 0; i < operators.size(); ++i)
        {
            if (operators[i] == '*')
            {
                numbers[i] = numbers[i] * numbers[i + 1];
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < operators.size(); ++i)
        {
            if (operators[i] == '+')
            {
                numbers[i] = numbers[i] + numbers[i + 1];
                numbers.erase(numbers.begin() + i + 1);
                operators.erase(operators.begin() + i);
                i--;
            }
        }
        return numbers[0];
    }

private:
    string expression;
};

int main()
{
    string str = "1+2*3+3*7";
    Calculator<int> calc(str);
    cout << calc.evaluate() << endl;

    string str2 = "(7,1)*(5,8)+(3,4)*(5,6)+(2,1)";
    Calculator<Rectangle> calc2(str2);
    cout << calc2.evaluate() << endl;

    cout << "Success" << endl;

    Rectangle rect("(1,2)");
    cout << rect << endl;

    cout << "Hello World!" << endl;
    cin >> rect;
    cout << rect << '\n';

    cout << "End Program" << endl;
    return 0;
}