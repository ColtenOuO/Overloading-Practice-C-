#include <iostream>

using namespace std;

long long gcd(long long a,long long b);
long long lcm(long long a,long long b);

class Fraction{
    private:
        long long whole,numerator,denominator; // whole numerator/denominator
    public:
        Fraction(long long x,long long y,long long z) : whole(x) , numerator(y) , denominator(z) {} // Constructure
        Fraction operator+(Fraction&);
        Fraction operator-(Fraction&);
        Fraction operator*(Fraction&);
        Fraction operator/(Fraction&);
        Fraction operator=(Fraction&);
        Fraction operator<(Fraction&);
        Fraction operator>(Fraction&);
        Fraction operator==(Fraction&);
        Fraction operator<=(Fraction&);
        Fraction operator>=(Fraction&);
        Fraction operator!=(Fraction&);
    
    friend istream &operator>>(istream &s,Fraction &input);
    friend ostream &operator<<(ostream &s,Fraction p); 
};
Fraction Fraction::operator+(Fraction &y)
{
    Fraction* x = this;
    x -> numerator = ( x -> numerator ) + ( x -> whole ) * ( x -> denominator );
    y.numerator = y.numerator + y.whole  * y.denominator;
    
    long long g = lcm( x -> denominator , y.denominator );

    return Fraction( 0LL , ( x -> numerator ) * ( g / ( x -> denominator ) ) + y.numerator * ( g / y.denominator ) , g  );
}
Fraction Fraction::operator-(Fraction &y)
{
    Fraction* x = this;
    x -> numerator = ( x -> numerator ) + ( x -> whole ) * ( x -> denominator );
    y.numerator = y.numerator + y.whole * y.denominator;

    long long g = lcm( x -> denominator , y.denominator );

    return Fraction( 0LL , ( x -> numerator ) * ( g / ( x -> denominator ) ) - y.numerator * ( g / y.denominator ) , g );
}
istream &operator>>(istream &s,Fraction &input)
{
    input.whole = 0; // init
    
    char c;
    string str;
    while( cin >> str )
    {
        long long num = 0;
        bool slash = false;
        for(int i=0;i<str.size();i++)
        {
            if( str[i] >= '0' && str[i] <= '9' ) num *= 10 , num += str[i] - '0';
            if( str[i] == '/' ) input.numerator = num , num = 0 , slash = true;
        }

        if( slash == false ) // 分數還沒讀取完，現在只讀取到帶分數的數字而已
        {
            input.whole = num;
            continue;
        } 
        else
        {
            input.denominator = num;
            break;
        }
    }

    return s;
}
ostream &operator<<(ostream &s, Fraction p) { 
    s << p.whole << " " << p.numerator << " " << p.denominator;
    return s; 
}
long long gcd(long long a,long long b)
{
    while( b != 0 )
    {
        long long c = a % b;
        a = b;
        b = c;
    }

    return a;
}
long long lcm(long long a,long long b)
{
    return a * b / gcd(a,b);
}
int main()
{
    Fraction x(0LL,0LL,0LL),y(0LL,0LL,0LL),z(0LL,0LL,0LL);
    cout << "請輸入兩個分數\n";
    cin >> x >> y;

    cout << ( x + y ) << "\n";
}
