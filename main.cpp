#include <iostream>

using namespace std;

long long gcd(long long a,long long b);
long long lcm(long long a,long long b);

class Function{
    private:
        long long a,b,c; // a b/c
    public:
        Function(long long x,long long y,long long z) : a(x) , b(y) , c(z) {} // Constructure
        Function operator+(Function&);
        Function operator-(const Function&);
        Function operator*(const Function&);
        Function operator/(const Function&);
        Function operator=(const Function&);
        Function operator<(const Function&);
        Function operator>(const Function&);
        Function operator==(const Function&);
        Function operator<=(const Function&);
        Function operator>=(const Function&);
        Function operator!=(const Function&);
    
    friend istream &operator>>(istream &s,Function &input);
    friend ostream &operator<<(ostream &s,Function p); 
};
Function Function::operator+(Function &y)
{
    Function* x = this;
    x -> b = ( x -> b ) + ( x -> a ) * ( x -> c );
    y.b = y.b + y.a  * y.c;
    
    long long g = lcm( x -> c , y.c );

    return Function( 0LL , ( x -> b ) * ( g / ( x -> c ) ) + y.b * ( g / ( y.c ) ) , g  );
}
istream &operator>>(istream &s,Function &input)
{
    input.a = 0; // init
    
    char c;
    string str;
    while( cin >> str )
    {
        long long num = 0;
        bool slash = false;
        for(int i=0;i<str.size();i++)
        {
            if( str[i] >= '0' && str[i] <= '9' ) num *= 10 , num += str[i] - '0';
            if( str[i] == '/' ) input.b = num , num = 0 , slash = true;
        }

        if( slash == false ) // 分數還沒讀取完，現在只讀取到帶分數的數字而已
        {
            input.a = num;
            continue;
        } 
        else
        {
            input.c = num;
            break;
        }
    }

    return s;
}
ostream &operator<<(ostream &s, Function p) { 
    s << p.a << " " << p.b << " " << p.c;
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
    Function x(0LL,0LL,0LL),y(0LL,0LL,0LL),z(0LL,0LL,0LL);
    cout << "請輸入兩個分數\n";
    cin >> x >> y;

    cout << ( x + y ) << "\n";
}
