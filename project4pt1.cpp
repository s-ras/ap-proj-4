#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Complex{
    friend Complex sum(Complex, Complex);
    friend Complex sub(Complex, Complex);
    friend Complex mux(Complex, Complex);
    friend Complex div(Complex, Complex);
    private: 
        float x;
        float y;
    public:
        Complex(float, float);
        void set_x(float);
        void set_y(float);
        float get_x() const;
        float get_y() const;
        string to_str() const;
        void print() const;
        static Complex sum(Complex, Complex);
        static Complex sub(Complex, Complex);
        static Complex mux(Complex, Complex);
        static Complex div(Complex, Complex);
};

int main(){

    Complex z1(5.0, -3.0);
    Complex z2(2.0, 0.0);
    Complex z3(0.0, -6.0);
    Complex z4(-3.0, -8.0);
    Complex z5(0.0, 14.0);
    Complex z6(9.0, 5.0);
    z1.print();
    z2.print();
    z3.print();
    z4.print();
    z5.print();
    z6.print();

    cout << "------------------------------" << endl;

    Complex::sum(z1, z2).print();
    Complex::sum(z6, z4).print();
    Complex::sum(z3, z5).print();
    
    cout << "------------------------------" << endl;

    Complex::sub(z1, z2).print();
    Complex::sub(z6, z4).print();
    Complex::sub(z3, z5).print();

    cout << "------------------------------" << endl;

    Complex::mux(z1, z2).print();
    Complex::mux(z6, z4).print();
    Complex::mux(z3, z5).print();

    cout << "------------------------------" << endl;

    Complex::div(z1, z2).print();
    Complex::div(z6, z4).print();
    Complex::div(z3, z5).print();

    cout << "------------------------------" << endl;

    Complex::div(z3, Complex(0,0)).print();

    cout << "------------------------------" << endl;

    sum(Complex(2, 3), Complex(5, 4)).print();
    sub(Complex(2, 3), Complex(5, 4)).print();
    mux(Complex(2, 3), Complex(5, 4)).print();
    div(Complex(2, 3), Complex(5, 4)).print();

    return 0;

}

Complex::Complex(float inp1, float inp2){
    set_x(inp1);
    set_y(inp2);
}

void Complex::set_x(float inp){
    x = inp;
}

void Complex::set_y(float inp){
    y = inp;
}

float Complex::get_x() const{
    return x;
}

float Complex::get_y() const{
    return y;
}

string Complex::to_str() const{
    if(isnan(x) || isnan(y)){
        return "NaN";
    }
    stringstream stream;
    if (x != 0.0){
        stream << x;
    } 
    if (y != 0.0){
        if (y > 0.0 && x != 0.0){
            stream << "+";
        }
        if (y == 1.0){
            stream << "i";
        } else if (y == -1.0){
            stream << "-i";
        } else {
            stream << y << "i";
        }
    }
    return stream.str();
} 

void Complex::print() const{
    cout << this->to_str() << endl;
}

Complex Complex::sum(Complex a, Complex b){
    return Complex(a.x + b.x, a.y + b.y);
}

Complex Complex::sub(Complex a, Complex b){
    return Complex(a.x - b.x, a.y - b.y);
}

Complex Complex::mux(Complex a, Complex b){
    float new_x = (a.x * b.x) - (a.y * b.y);
    float new_y = (a.x * b.y) + (a.y * b.x);
    return Complex(new_x, new_y);
}

Complex Complex::div(Complex a, Complex b){
    float denominator = (b.x * b.x) + (b.y * b.y);
    float new_x = ((a.x * b.x) + (a.y * b.y)) / denominator;
    float new_y = ((a.y * b.x) - (a.x * b.y)) / denominator;
    return Complex(new_x, new_y);
}

Complex sum(Complex a, Complex b){
    return Complex(a.x + b.x, a.y + b.y);
}

Complex sub(Complex a, Complex b){
    return Complex(a.x - b.x, a.y - b.y);
}

Complex mux(Complex a, Complex b){
    float new_x = (a.x * b.x) - (a.y * b.y);
    float new_y = (a.x * b.y) + (a.y * b.x);
    return Complex(new_x, new_y);
}

Complex div(Complex a, Complex b){
    float denominator = (b.x * b.x) + (b.y * b.y);
    float new_x = 0.0, new_y = 0.0;
    new_x = ((a.x * b.x) + (a.y * b.y)) / denominator;
    new_y = ((a.y * b.x) - (a.x * b.y)) / denominator;
    return Complex(new_x, new_y);
}