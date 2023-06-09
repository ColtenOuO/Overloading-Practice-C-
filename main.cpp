#include <iostream>

using namespace std;

class Function{

    private:
        int a,b,c; // a b/c

    friend istream &operator>>(istream &s,Function &input);
    friend ostream &operator<<(ostream &s,Function p); 
};
istream &operator>>(istream &s,Function &input)
{
    input.a = 0; // init
    string str;
    getline(cin,str);
    int num = 0;
    for(int i=0;i<str.size();i++)
    {
        if( str[i] >= '0' && str[i] <= '9' ) num *= 10 , num += str[i] - '0';
        else if( str[i] == ' ' ) input.a = num , num = 0;
        else if( str[i] == '/' ) input.b = num , num = 0;
        
        if( i == str.size() - 1 ) input.c = num;
    }

    return s;
}
ostream &operator<<(ostream &s, Function p) { 
    s << p.a << " " << p.b << " " << p.c;
    return s; 
} 
int main()
{
    Function x,y;
    cout << "請輸入兩個分數\n";
    cin >> x >> y;
    cout << x << " " << y << "\n";
}