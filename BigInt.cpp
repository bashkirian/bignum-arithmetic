#include <iostream>
#include <string>

using namespace std;

class BigInt
{
private:
    int* arr;
    int length;
public:
    BigInt() {
        arr = nullptr;
        length = 0;
    }

    BigInt(string number)
    {
        length = number.length();
        arr = new int[length];
        for (int i = 0; i < length; i++)
        {
            arr[i] = ((int)number[i] - 48);
        }
    }

    BigInt(const BigInt& other)
    {
        this->length = other.length;
        this->arr = new int[length];
        for (int i = 0; i < length; i++)
        {
            this->arr[i] = other.arr[i];
        }
    }

    BigInt(int* arr, int length)
    {
        this->arr = arr;
        this->length = length;
    }

    BigInt& operator + (const BigInt& other);

    BigInt& operator - (const BigInt& other);

    BigInt& operator * (const BigInt& other);

    BigInt& operator ^ (const BigInt& other);

    friend ostream& operator<< (ostream& out, const BigInt& number);

    ~BigInt()
    {
        delete[] this->arr;
    }
};

ostream& operator<< (ostream& out, const BigInt& number) {
    for (int i = 0; i < number.length; i++)
    {
        out << number.arr[i];
    }
    return out;
}

BigInt& BigInt::operator+(const BigInt& other)
{
    int increase = 0;
    BigInt s;
    if (this->length > other.length)
    {
        int* sum = new int[this->length + 1];
        int i;
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
            s.arr = sum + 1;
            s.length = this->length;
        }
        else
        {
            s.arr = sum;
            s.length = this->length + 1;
        }
    }
    else
    {
        int* sum = new int[other.length + 1];
        int i;
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
            s.arr = sum + 1;
            s.length = other.length;
        }
        else
        {
            s.arr = sum;
            s.length = other.length + 1;
        }
    }
    return s;
};

int main()
{
    string first, second;
    cin >> first;
    cin >> second;
    BigInt number_one(first);
    BigInt number_two(second);
    BigInt sum = number_one + number_two;
    cout << sum;
    return 0;
}
 

