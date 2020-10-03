#include <iostream>
#include <string>
#define base 1000000000
class BigInt
{
private:
    int* arr;
    int length;
    bool negative;
public:
    BigInt() // default constructor
    {
        arr = nullptr;
        length = 0;
        negative = false;
    }
    BigInt(std::string number) // constructor for input data
    {
        length = number.length();
        arr = new int[length];
        negative = false;
        for (int i = 0; i < length; i++)
        {
            arr[i] = ((int)number[length - i - 1] - 48);
        }
    }
    BigInt(const BigInt& other) // copy constructor
    {
        this->length = other.length;
        this->arr = new int[length];
        this->negative = other.negative;
        for (int i = 0; i < length; i++)
        {
            this->arr[i] = other.arr[i];
        }
    }
    BigInt(BigInt&& other)
    {
        this->length = other.length;
        this->arr = other.arr;
        other.arr = nullptr;
    }

    bool ifNull(const BigInt& number)
    {
        return (number.length == 1 && number.arr[0] == 0) ? true : false;
    }
    void difference(int* greater, int* smaller, int* result, int greater_length, int smaller_length)
    {
        for (int i = 0; i < smaller_length; i++)
        {
            result[i] = greater[i] - smaller[i];
        }
        for (int i = smaller_length; i < greater_length; i++)
            result[i] = greater[i];
        for (int i = 0; i < greater_length - 1; i++)
        {
            if (result[i] < 0)
            {
                result[i] += 10;
                --result[i + 1];
            }
        }
    }

    BigInt operator + (BigInt& other);
    BigInt operator += (BigInt& other);
    BigInt operator = (BigInt other);
    BigInt operator - (BigInt& other);
    BigInt operator -- ();
    BigInt operator * (int other);
    BigInt operator ^ (BigInt& other);
    bool operator > (BigInt& other);
    bool operator < (BigInt& other);
    bool operator == (BigInt& other);
    bool operator >= (BigInt& other);
    bool operator <= (BigInt& other);
    friend std::ostream& operator<< (std::ostream& out, const BigInt& number); // overloading of output operator

    ~BigInt()
    {
        delete[] arr;
    }
};

std::ostream& operator<< (std::ostream& out, const BigInt& number) {
    int i = number.length - 1;
    for (; i > 0; i--)
    {
        if (number.arr[i] != 0) break;
    }
    if (number.negative == true) std::cout << "-";
    for (; i >= 0; i--)
    {
        out << number.arr[i];
    }
    return out;
}

BigInt BigInt::operator=(BigInt other)
{
    if (this->arr != nullptr)
    {
        delete[] arr;
    }
    length = other.length;
    this->arr = new int[length];
    for (int i = 0; i < length; i++)
    {
        this->arr[i] = other.arr[i];
    }
    return *this;
}

BigInt BigInt::operator-(BigInt& other)
{
    int k = 3;
    BigInt d;
    int g_len = this->length;
    int s_len = other.length;
    if (*this > other) k = 2;
    else
    {
        if (*this < other)
        {
            k = 1;
            g_len = other.length;
            s_len = this->length;
        }
        else k = 3;
    }
    int* diff = new int[g_len];
    if (k == 1)
    {
        difference(other.arr, this->arr, diff, g_len, s_len);
        d.arr = new int[g_len];
        for (int i = 0; i < g_len; i++)
        {
            d.arr[i] = diff[i];
        }
        d.length = g_len;
    }
    if (k == 2)
    {
        difference(this->arr, other.arr, diff, g_len, s_len);
        d.arr = new int[g_len];
        for (int i = 0; i < g_len; i++)
        {
            d.arr[i] = diff[i];
        }
        d.length = g_len;
        d.negative = true;
    }
    if (k == 3)
    {
        d.arr = new int[1];
        d.length = 1;
        d.arr[0] = 0;
    }
    delete[] diff;
    return d;
}

BigInt BigInt::operator--()
{
    BigInt one;
    one.arr = new int[1];
    one.length = 1;
    one.arr[0] = 1;
    *this = *this - one;
    return *this;
}

bool BigInt::operator>(BigInt& other)
{
    if (this->length > other.length) return true;
    if (other.length > this->length) return false;
    if (this->length == other.length)
    {
        if (*this == other) return false;
        for (int i = other.length - 1; i >= 0; i--)
        {
            if (this->arr[i] > other.arr[i]) break;
            if (this->arr[i] < other.arr[i]) return false;
        }
        return true;
    }
}

BigInt BigInt::operator+(BigInt& other)
{
    int increase = 0;
    BigInt s;
    int i;
    if (this->length > other.length)
    {
        int* sum = new int[this->length + 1];
        for (i = 0; i < other.length; i++)
        {
            sum[i] = (this->arr[i] + other.arr[i] + increase) % 10;
            increase = (this->arr[i] + other.arr[i] + increase) / 10;
        }
        for (i = other.length; i < this->length; i++)
        {
            sum[i] = (this->arr[i] + increase) % 10;
            increase = (this->arr[i] + increase) / 10;
        }
        sum[this->length] = increase;
        s.arr = new int[this->length + 1];
        for (i = 0; i <= this->length; i++)
        {
            s.arr[i] = sum[i];
        }
        s.length = this->length + 1;
        delete[] sum;
        return s;
    }
    else
    {
        int* sum = new int[other.length + 1];
        for (i = 0; i < this->length; i++)
        {
            sum[i] = (other.arr[i] + this->arr[i] + increase) % 10;
            increase = (other.arr[i] + this->arr[i] + increase) / 10;
        }
        for (i = this->length; i < other.length; i++)
        {
            sum[i] = (other.arr[i] + increase) % 10;
            increase = (other.arr[i] + increase) / 10;
        }
        sum[other.length] = increase;
        s.arr = new int[other.length + 1];
        for (i = 0; i <= other.length; i++)
        {
            s.arr[i] = sum[i];
        }
        s.length = other.length + 1;
        delete[] sum;
        return s;
    }
}

BigInt BigInt::operator+=(BigInt& other)
{
    return other + *this;
}

bool BigInt::operator<(BigInt& other)
{
    if (this->length > other.length) return false;
    if (other.length > this->length) return true;
    if (this->length == other.length)
    {
        if (*this == other) return false;
        for (int i = other.length - 1; i >= 0; i--)
        {
            if (this->arr[i] < other.arr[i]) break;
            if (this->arr[i] > other.arr[i]) return false;
        }
        return true;
    }
}

bool BigInt::operator==(BigInt& other)
{
    if (this->length > other.length) return false;
    if (other.length > this->length) return false;
    if (this->length == other.length)
    {
        for (int i = other.length - 1; i >= 0; i--)
        {
            if (this->arr[i] > other.arr[i] || this->arr[i] < other.arr[i]) return false;
        }
        return true;
    }
}

bool BigInt::operator>=(BigInt& other)
{
    return (*this > other || *this == other);
}

bool BigInt::operator<=(BigInt& other)
{
    return (*this < other || *this == other);
}

BigInt BigInt::operator*(int num)
{
    BigInt product = *this;
    if (ifNull(*this))
    {
        product.length = 1;
        product.arr = new int[1];
        product.arr[0] = 0;
        return product;
    }
    if (this->arr[0] == 1 && this->length == 1)
    {
        return product;
    }
    while (num != 1)
    {
        product = product + *this;
        --num;
    }
    return product;
}

BigInt BigInt::operator^(BigInt& other)
{
    return BigInt();
}

int main()
{
    std::string first;
    int multiplier;
    std::cin >> first;
    std::cin >> multiplier;
    BigInt number(first);
    BigInt sum = number * multiplier;
    std::cout << sum;
    return 0;
}