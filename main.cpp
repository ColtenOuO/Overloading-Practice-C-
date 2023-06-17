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
        bool operator<(Fraction&);
        bool operator>(Fraction&);
        bool operator==(Fraction&);
        bool operator<=(Fraction&);
        bool operator>=(Fraction&);
        bool operator!=(Fraction&);

        void Setter(long long x,long long y,long long z)
        {
            whole = x , numerator = y , denominator = z;
        }
        Fraction Getter()
        {
            return Fraction(whole,numerator,denominator);
        }
        void reduction() // 約分
        {
            long long more = numerator / denominator;
            long long mod = numerator % denominator;

            whole += more;
            numerator = mod;

            int g = gcd(numerator,denominator);
            numerator /= g , denominator /= g;
        }
    
    friend istream &operator>>(istream &s,Fraction &input); // 讓 ifstream 與 ostream 能夠存取 Fraction 的 private member
    friend ostream &operator<<(ostream &s,Fraction p); 
};
void validate_overloading(Fraction x,Fraction y)
{
    Fraction s(1,2,3);
    s.Setter(2,3,4); // Setter 驗證
    Fraction a = x , b = y;
    cout << "驗證 " << a.Getter() << "與" << b.Getter() << " 兩個分數的各個操作\n\n"; // 驗證 Getter

    cout << a + b << "\n";
    a = x , b = y; // 因為 pass by reference 所以可能有動到原本分數的樣子，還原回去
    cout << a - b << "\n";
    a = x , b = y; // 因為 pass by reference 所以可能有動到原本分數的樣子，還原回去
    cout << a * b << "\n";
    a = x , b = y; // 因為 pass by reference 所以可能有動到原本分數的樣子，還原回去
    cout << a / b << "\n";
    a = x , b = y; // 因為 pass by reference 所以可能有動到原本分數的樣子，還原回去

    if( a < b ) cout << x << "<" << y << " 成立\n";
    else cout << x << "<" << y << " 不成立\n";

    if( a > b ) cout << x << ">" << y << " 成立\n";
    else cout << x << ">" << y << " 不成立\n";

    if( a <= b ) cout << x << "<=" << y << " 成立\n";
    else cout << x << "<=" << y << " 不成立\n";

    if( a >= b ) cout << x << ">=" << y << " 成立\n";
    else cout << x << ">=" << y << " 不成立\n";

    if( a == b ) cout << x << "==" << y << " 成立\n";
    else cout << x << "==" << y << " 不成立\n";

    if( a != b ) cout << x << "!=" << y << " 成立\n";
    else cout << x << "!=" << y << " 不成立\n";

    return;
}
Fraction Fraction::operator+(Fraction &y)
{
    cout << "進行通分相加:" << *this << " " << y << "\n\n";

    Fraction save1 = *this , save2 = y;

    Fraction* x = this;
    
    long long g = lcm( x -> denominator , y.denominator );

    x -> numerator *= ( ( g / ( x -> denominator ) ) );
    y.numerator *= ( g / y.denominator );
    Fraction z( ( x -> whole ) + y.whole , ( x -> numerator ) + y.numerator , g ); // 透過 Constructure 初始化

    if( ( this -> denominator ) != y.denominator )
    {
        x -> denominator = y.denominator = g;
        cout << "異分母分數相加，進行通分。分母是" << g << "\n";
        cout << save1 << "+" << save2 << "=" << *x << "+" << y << "=" << z << "\n";
        cout << "最終分數是: ";
    }
    else
    {
        x -> denominator = y.denominator = g;
        cout << "同分母分數相加。分母是" << g << "\n";
        cout << save1 << "+" << save2 << "=" << z << "\n";
        cout << "最終分數是: ";
    }

    x -> denominator = y.denominator = g;

    z.reduction();
    return z;
}
Fraction Fraction::operator-(Fraction &y)
{
    cout << "進行通分相減:" << *this << " " << y << "\n\n";

    Fraction save1 = *this , save2 = y;

    Fraction* x = this;
    
    long long g = lcm( x -> denominator , y.denominator );

    x -> numerator *= ( ( g / ( x -> denominator ) ) );
    y.numerator *= ( g / y.denominator );
    Fraction z( ( x -> whole ) - y.whole , ( x -> numerator ) - y.numerator , g ); // 透過 Constructure 初始化

    if( ( this -> denominator ) != y.denominator )
    {

        x -> denominator = y.denominator = g;
        cout << "異分母分數相減，進行通分。分母是" << g << "\n";
        cout << save1 << "-" << save2 << "=" << *x << "-" << y << "=" << z << "\n";
        cout << "最終分數是: ";
    }
    else
    {
        x -> denominator = y.denominator = g;
        cout << "同分母分數相減。分母是" << g << "\n";
        cout << save1 << "-" << save2 << "=" << z << "\n";
        cout << "最終分數是: ";
    }

    x -> denominator = y.denominator = g;

    z.reduction();
    return z;
}
Fraction Fraction::operator*(Fraction &y)
{
    Fraction* x = this;

    Fraction z(0LL,0LL,0LL);

    cout << *this << "*" << y << "=";

    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );

    z.denominator = ( x -> denominator ) * y.denominator;
    z.numerator = ( x -> numerator ) * y.numerator;

    x -> whole = 0 , y.whole = 0;

    z.reduction();
    return z;
}
Fraction Fraction::operator/(Fraction &y)
{
    Fraction* x = this;

    Fraction z(0LL,0LL,0LL);

    cout << *this << "/" << y << "=";

    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );

    swap(y.numerator,y.denominator); // 除法倒數

    z.denominator = ( x -> denominator ) * y.denominator;
    z.numerator = ( x -> numerator ) * y.numerator;

    x -> whole = 0 , y.whole = 0;

    z.reduction();
    return z;
}
bool Fraction::operator<(Fraction &y)
{
    Fraction* x = this;
    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );
    x -> whole = 0 , y.whole = 0;

    return ( x -> numerator * y.denominator ) < ( x -> denominator * y.numerator ); // 交叉相乘比大小，避免使用浮點數導致誤差
}
bool Fraction::operator>(Fraction &y)
{
    Fraction* x = this;
    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );
    x -> whole = 0 , y.whole = 0;

    return ( x -> numerator * y.denominator ) > ( x -> denominator * y.numerator ); // 交叉相乘比大小，避免使用浮點數導致誤差
}
bool Fraction::operator<=(Fraction &y)
{
    Fraction* x = this;
    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );
    x -> whole = 0 , y.whole = 0;

    return ( x -> numerator * y.denominator ) <= ( x -> denominator * y.numerator ); // 交叉相乘比大小，避免使用浮點數導致誤差
}
bool Fraction::operator>=(Fraction &y)
{
    Fraction* x = this;
    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );
    x -> whole = 0 , y.whole = 0;

    return ( x -> numerator * y.denominator ) >= ( x -> denominator * y.numerator ); // 交叉相乘比大小，避免使用浮點數導致誤差
}
bool Fraction::operator==(Fraction &y)
{
    Fraction* x = this;
    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );
    x -> whole = 0 , y.whole = 0;

    return ( x -> numerator * y.denominator ) == ( x -> denominator * y.numerator ); // 交叉相乘比大小，避免使用浮點數導致誤差
}
bool Fraction::operator!=(Fraction &y)
{
    Fraction* x = this;
    x-> numerator += ( x -> whole ) * ( x -> denominator );
    y.numerator += ( y.whole ) * ( y.denominator );
    x -> whole = 0 , y.whole = 0;

    return ( x -> numerator * y.denominator ) != ( x -> denominator * y.numerator ); // 交叉相乘比大小，避免使用浮點數導致誤差
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
    s << p.whole << " " << p.numerator << "/" << p.denominator;
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
    int opt;

    cout << "請輸入 1 (從 fraction.txt 檔案讀取兩個分數) 或 2: (自行手動輸入兩個分數,不用添加運算符號,會列出所有結果)\n";   
    
    cin >> opt;
    if( opt == 1 )
    {
        freopen("fraction.txt","r",stdin);
        char u;
        while( cin >> x >> u >> y )
        {
            if( u == '+' ) cout << x + y << "\n";
            else if( u == '-' ) cout << x - y << "\n";
            else if( u == '*' ) cout << x * y << "\n";
            else if( u == '/' ) cout << x / y << "\n";
        }
    }
    else{
        cout << "請輸入兩個分數\n";
         cin >> x >> y;
    
         validate_overloading(x,y); // 跑出所有運算子 overloading 後的運算結果
   }
    return 0;
}
