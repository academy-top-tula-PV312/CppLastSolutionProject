#include <iostream>

int** MatrixCreate(int rows, int cols);

class Money
{
    int rub;
    unsigned int kop;

    void Normalize();
public:
    Money();
    Money(int rub, unsigned int kop);
    Money(int amount); // amount - kops
    Money(double amount);

    Money Add(Money money);
    Money Mult(double k);
    Money Percent(int p);

    friend Money operator+(Money money1, Money money2);
    friend Money operator-(Money money1, Money money2);
    friend Money operator*(Money money, double);
    friend Money operator*(double, Money money);
    friend double operator/(Money money1, Money money2);
    friend Money operator%(Money money, int p);

    friend std::ostream& operator<<(std::ostream& out, const Money& money);
};

int main()
{
    //int** matrix = MatrixCreate(3, 4);

    Money m1(5.0);

    std::cout << m1 % 10 << "\n";
}

int** MatrixCreate(int rows, int cols)
{
    int** result = new int*[rows];
    for (int row{}; row < rows; row++)
        result[row] = new int[cols];
    return result;
}

Money operator%(Money money, int p)
{
    return Money(0, (p * (money.rub * 100 + money.kop) / 100));
}

std::ostream& operator<<(std::ostream& out, const Money& money)
{
    out << money.rub << "R, " << money.kop << "K";
    return out;
}

void Money::Normalize()
{
    rub += kop / 100;
    kop = kop % 100;
}

Money::Money(int rub, unsigned int kop) : rub{ rub }, kop{ kop } { Normalize(); }
Money::Money() : Money(0, 0) {}
Money::Money(int amount) : Money(0, amount) {}
Money::Money(double amount)
    : rub{ (int)amount }
{
    kop = (unsigned int)std::round(amount - rub) * 100;
}

Money Money::Add(Money money)
{
    kop = (rub * 100 + kop) + (money.rub * 100 + money.kop);
    rub = 0;
    Normalize();
    return *this;
}

Money Money::Mult(double k)
{
    kop = (rub * 100 + kop) * k;
    rub = 0;
    Normalize();
    return *this;
}

Money Money::Percent(int p)
{
    return Money(0, (p * (rub * 100 + kop) / 100));
}




