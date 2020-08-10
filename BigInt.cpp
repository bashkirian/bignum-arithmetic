#include <iostream>
#include <string>

using namespace std;

class BigInt
{
private:
    int* arr;
    int length;
public:
    BigInt() // default constructor
    {
        arr = nullptr;
        length = 0;
    }

    BigInt(string number) // constructor for input data
    {
        length = number.length();
        arr = new int[length];
        for (int i = 0; i < length; i++)
        {
            arr[i] = ((int)number[i] - 48);
        }
    }

    BigInt(int* arr, int length) // another constructor for binary operations
    {
        this->arr = arr;
        this->length = length;
    }

    BigInt(const BigInt& other) // copy constructor
    {
        this->length = other.length;
        this->arr = new int[length];
        for (int i = 0; i < length; i++)
        {
            this->arr[i] = other.arr[i];
        }
    }

    bool ifNull(const BigInt& number)
    {
        (number.length == 1 && number.arr[0] == 0) ? true : false;
    }

    BigInt operator + (const BigInt& other); 
    BigInt& operator = (const BigInt& other);
    BigInt operator - (const BigInt& other);
    BigInt operator -- ();
    BigInt operator * (const BigInt& other);
    BigInt operator ^ (const BigInt& other);
    bool operator > (const BigInt& other);
    bool operator < (const BigInt& other);
    bool operator == (const BigInt& other);
    bool operator >= (const BigInt& other);
    bool operator <= (const BigInt& other);
    friend ostream& operator<< (ostream& out, const BigInt& number); // overloading of output operator

    ~BigInt()
    {
        delete[] arr;
    }
};

ostream& operator<< (ostream& out, const BigInt& number) {
    for (int i = 0; i < number.length; i++)
    {
        out << number.arr[i];
    }
    return out;
}

BigInt& BigInt::operator=(const BigInt& other)
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

//BigInt BigInt::operator-(const BigInt& other)
//{
//    int decrease = 0;
//    BigInt d;
//    int i;
//    if (*this >= other)
//    {
//        int* diff = new int[this->length];
//        for (i = this->length - 1; i >= this->length - other.length; i--)
//        {
//            if (decrease > 0) this->arr[i] -= decrease;
//            else 
//            if (this->arr[i] >= other.arr[i])
//            {
//                diff[i] = this->arr[i] - other.arr[i];
//                decrease = 0;
//            }
//            else
//            {
//                diff[i] = -(this->arr[i] - other.arr[i]);
//                decrease = 1;
//            }
//        }
//    }
//    else
//    {
//        cout << '-';
//
//    }
//}
//
//BigInt BigInt::operator--()
//{
//    return *this - 1;
//}

bool BigInt::operator>(const BigInt& other)
{
    if (this->length > other.length) return true;
    if (other.length > this->length) return false;
    if (this->length == other.length)
    {
        for (int i = 0; i < other.length; i++)
        {
            if (this->arr[i] < other.arr[i]) return false;
        }
        return true;
    }
}

BigInt BigInt::operator+(const BigInt& other)
{
    int increase = 0;
    BigInt s;
    int i;
    if (this->length > other.length)
    {
        int* sum = new int[this->length + 1];
        for (i = this->length - 1; i >= this->length - other.length; i--)
        {
            sum[i + 1] = (this->arr[i] + other.arr[i - (this->length - other.length)] + increase) % 10;
            increase = (this->arr[i] + other.arr[i - (this->length - other.length)] + increase) / 10;
        }
        for (i = this->length - other.length - 1; i >= 0; i--)
        {
            sum[i + 1] = (this->arr[i] + increase) % 10;
            increase = (this->arr[i] + increase) / 10;
        }
        sum[0] = increase;
        if (sum[0] == 0)
        {
            s.arr = new int[this->length];
            for (i = 0; i < this->length; i++)
            {
                s.arr[i] = sum[i + 1];
            }
            s.length = this->length;
        }
        else
        {
            s.arr = new int[this->length + 1];
            for (i = 0; i <= this->length; i++)
            {
                s.arr[i] = sum[i];
            }
            s.length = this->length + 1;
        }
        delete[] sum;
        return s;
    }
    else
    {
        int* sum = new int[other.length + 1];
        for (i = other.length - 1; i >= other.length - this->length; i--)
        {
            sum[i + 1] = (other.arr[i] + this->arr[i - (other.length - this->length)] + increase) % 10;
            increase = (other.arr[i] + this->arr[i - (other.length - this->length)] + increase) / 10;
        }
        for (i = other.length - this->length - 1; i >= 0; i--)
        {
            sum[i + 1] = (other.arr[i] + increase) % 10;
            increase = (other.arr[i] + increase) / 10;
        }
        sum[0] = increase;
        if (sum[0] == 0)
        {
            s.arr = new int[other.length];
            for (i = 0; i < other.length; i++)
            {
                s.arr[i] = sum[i + 1];
            }
            s.length = other.length;
        }
        else
        {
            s.arr = new int[other.length + 1];
            for (i = 0; i <= other.length; i++)
            {
                s.arr[i] = sum[i];
            }
            s.length = other.length + 1;
        }
        delete[] sum;
        return s;
    }
}

bool BigInt::operator<(const BigInt& other)
{
    return !(*this > other);
}

bool BigInt::operator==(const BigInt& other)
{
    if (this->length > other.length) return false;
    if (other.length > this->length) return false;
    if (this->length == other.length)
    {
        for (int i = 0; i < other.length; i++)
        {
            if (this->arr[i] > other.arr[i] || this->arr[i] < other.arr[i]) return false;
        }
        return true;
    }
}

bool BigInt::operator>=(const BigInt& other)
{
    return (*this > other || *this == other);
}

bool BigInt::operator<=(const BigInt& other)
{
    return (*this < other || * this == other);
}

//BigInt BigInt::operator*(const BigInt& other)
//{
//    BigInt product;
//    if (ifNull(other))
//    {
//        product.length = 1;
//        product.arr = new int[1];
//        product.arr[0] = 0;
//        return product;
//    }
//    while (!ifNull(other))
//    {
//        product = *this + other;
//        --other;
//    }
//    return product;
//}

BigInt BigInt::operator^(const BigInt& other)
{
    return BigInt();
}

int main()
{
    string first, second, third;
    cin >> first;
    cin >> second;
    cin >> third;
    BigInt number_one(first);
    BigInt number_two(second);
    BigInt number_three(third);
    BigInt sum = number_one + number_two;
    if (number_one >= number_two)
    {
        if (number_one >= number_three) cout << number_one;
        else cout << number_three;
    }
    else
    {
        if (number_two >= number_three) cout << number_two;
        else cout << number_three;
    }
    return 0;
}
 

