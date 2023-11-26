#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Rational{
    private:
        int numerator;
        int denominator;
        bool myNaN = false;
    public:
        Rational(int, int);
        void set_nom(int);
        void set_denom(int);
        int get_num() const;
        int get_denom() const;
        void simplify();
        string to_str() const;
        void print() const;
        double to_double() const;
        bool isNaN() const;
        static Rational sum(Rational, Rational);
        static Rational sub(Rational, Rational);
        static Rational mux(Rational, Rational);
        static Rational div(Rational, Rational);
};

class Complex{
    friend Complex sum(Complex, Complex);
    friend Complex sub(Complex, Complex);
    friend Complex mux(Complex, Complex);
    friend Complex div(Complex, Complex);
    private: 
        Rational x;
        Rational y;
    public:
        Complex(Rational, Rational);
        void set_x(Rational);
        void set_y(Rational);
        Rational get_x() const;
        Rational get_y() const;
        string to_str() const;
        void print() const;
        static Complex sum(Complex, Complex);
        static Complex sub(Complex, Complex);
        static Complex mux(Complex, Complex);
        static Complex div(Complex, Complex);
};

int gcd(int, int);

int main(){

    Complex::sum(Complex(Rational(-2, 5), Rational(3, 6)), Complex(Rational(-1, 7), Rational(4, -3))).print();
    Complex::sub(Complex(Rational(-2, 5), Rational(3, 6)), Complex(Rational(-1, 7), Rational(4, -3))).print();
    Complex::mux(Complex(Rational(-2, 5), Rational(3, 6)), Complex(Rational(-1, 7), Rational(4, -3))).print();
    Complex::div(Complex(Rational(-2, 5), Rational(3, 6)), Complex(Rational(-1, 7), Rational(4, -3))).print();
    
    cout << "------------------------------" << endl;

    Complex::div(Complex(Rational(-2, 5), Rational(3, 6)), Complex(Rational(0, 0), Rational(0, 0))).print();

    return 0;

}

int gcd(int a, int b){
    if (b == 0){
        return a;
    }
    return gcd(b, a%b);
}

Rational::Rational(int inp1 = 0, int inp2 = 0){
    set_nom(inp1);
    set_denom(inp2);
    simplify();
}

void Rational::set_nom(int inp){
    numerator = inp;
}

void Rational::set_denom(int inp){
    if (inp){
        denominator = inp;
    } else if (numerator == 0){
        denominator = inp;
    } else {
        myNaN = true;
    }
}

int Rational::get_num() const{
    if (! myNaN){
        return numerator;
    }
    return 0;
}

int Rational::get_denom() const{
    if (! myNaN){
        return denominator;
    }
    return 0;
}

void Rational::simplify(){
    if (myNaN){
        return;
    }
    bool isNegative = false;
    if ((numerator < 0 && denominator > 0) || (denominator < 0 && numerator > 0)){
        isNegative = true;
    }
    numerator = abs(numerator);
    denominator = abs(denominator);
    int myGCD = gcd(numerator, denominator);
    if (myGCD != 0){
        numerator /= myGCD;
        denominator /= myGCD;
    }
    if (isNegative){
        numerator *= -1;
    }
}

string Rational::to_str() const{
    if (myNaN){
        return "NaN";
    }
    if (numerator == 0){
        return "0";
    }
    stringstream stream;
    if (denominator == 1){
        stream << numerator;
    } else {
        stream << numerator << "/" << denominator;
    }
    return stream.str();
}

void Rational::print() const{
    cout << this->to_str();
}

double Rational::to_double() const{
    return (double) numerator / denominator;
}

bool Rational::isNaN() const{
    return myNaN;
}

Rational Rational::sum(Rational a, Rational b){  
    if (a.myNaN || b.myNaN){
        Rational result(0,0);
        result.myNaN = true;
        return result;
    }
    return Rational(((a.numerator*b.denominator) + (a.denominator * b.numerator)), (a.denominator * b.denominator));
}

Rational Rational::sub(Rational a, Rational b){  
    if (a.myNaN || b.myNaN){
        Rational result(0,0);
        result.myNaN = true;
        return result;
    }
    return Rational(((a.numerator*b.denominator) - (a.denominator * b.numerator)), (a.denominator * b.denominator));
}

Rational Rational::mux(Rational a, Rational b){  
    if (a.myNaN || b.myNaN){
        Rational result(0,0);
        result.myNaN = true;
        return result;
    }
    return Rational((a.numerator*b.numerator), (a.denominator * b.denominator));
}

Rational Rational::div(Rational a, Rational b){  
    if (a.myNaN || b.myNaN){
        Rational result(0,0);
        result.myNaN = true;
        return result;
    }
    return Rational((a.numerator*b.denominator), (a.denominator * b.numerator));
}

Complex::Complex(Rational inp1, Rational inp2){
    set_x(inp1);
    set_y(inp2);
}

void Complex::set_x(Rational inp){
    x = inp;
}

void Complex::set_y(Rational inp){
    y = inp;
}

Rational Complex::get_x() const{
    return x;
}

Rational Complex::get_y() const{
    return y;
}

string Complex::to_str() const{
    if(x.isNaN() || y.isNaN()){
        return "NaN";
    }
    stringstream stream;
    if (abs(x.to_double()) > 10e-6){
        stream << x.to_str();
    } 
    if (abs(y.to_double()) > 10e-6){
        if (y.get_num() > 0 && abs(x.to_double()) > 10e-6){
            stream << "+";
        }
        if (y.to_double() == 1.0){
            stream << "i";
        } else if (y.to_double() == -1.0){
            stream << "-i";
        } else {
            stream << y.to_str() << "i";
        }
    }
    return stream.str();
} 

void Complex::print() const{
    cout << this->to_str() << endl;
}

Complex Complex::sum(Complex a, Complex b){
    return Complex(Rational::sum(a.x, b.x), Rational::sum(a.y, b.y));
}

Complex Complex::sub(Complex a, Complex b){
    return Complex(Rational::sub(a.x, b.x), Rational::sub(a.y,b.y));
}

Complex Complex::mux(Complex a, Complex b){
    Rational new_x = Rational::sub(Rational::mux(a.x, b.x), Rational::mux(a.y, b.y));
    Rational new_y = Rational::sum(Rational::mux(a.x, b.y), Rational::mux(a.y, b.x));
    return Complex(new_x, new_y);
}

Complex Complex::div(Complex a, Complex b){
    Rational denominator = Rational::sum(Rational::mux(b.x, b.x), Rational::mux(b.y, b.y));
    Rational new_x = Rational::div((Rational::sum(Rational::mux(a.x, b.x), Rational::mux(a.y, b.y))), denominator);
    Rational new_y = Rational::div(Rational::sub(Rational::mux(a.y, b.x), Rational::mux(a.x, b.y)), denominator);
    return Complex(new_x, new_y);
}