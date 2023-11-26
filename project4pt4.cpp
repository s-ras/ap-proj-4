#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Number{
    public:
        virtual void print() const = 0;
        virtual int type() const = 0;
        static bool isEqual(Number*, Number*);
};

class Complex :public Number{
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
        virtual void print() const;
        virtual int type() const;
        static Complex sum(Complex, Complex);
        static Complex sub(Complex, Complex);
        static Complex mux(Complex, Complex);
        static Complex div(Complex, Complex);
        static bool isEqual(Complex, Complex);
};

class Rational :public Number{
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
        virtual void print() const;
        virtual int type() const;
        double to_double() const;
        bool isNaN() const;
        static Rational sum(Rational, Rational);
        static Rational sub(Rational, Rational);
        static Rational mux(Rational, Rational);
        static Rational div(Rational, Rational);
        static bool isEqual(Rational, Rational);
};

struct Node{
    Number* data;
    Node* next = NULL;
};

class NumberSet{
    private: 
        Node* list;
    public: 
        NumberSet();
        bool search(Number*) const;
        void add(Number*);
        void remove(Number*);
        void removeByType(int);
        void clear();
        int size() const;
        void print() const;
        void printByType(int) const;
        Complex complexSum() const;
        static NumberSet myUnion(NumberSet, NumberSet);
        static NumberSet myIntersect(NumberSet, NumberSet);
        static NumberSet mySubtraction(NumberSet, NumberSet);
};

int gcd(int, int);
int menu();
Number* getInput();
NumberSet* selectSet(NumberSet*, NumberSet*);
int selectType();

int main(){
    NumberSet A, B;
    while (true){
        int choice = menu();
        switch (choice){
            case 1:
                selectSet(&A, &B)->print();
                break;
            case 2:
                selectSet(&A, &B)->printByType(selectType());
                break;
            case 3:{
                if (selectSet(&A, &B)->search(getInput())){
                    cout << "Member exists in set" << endl;
                } else {
                    cout << "Member doesn't exists in set" << endl;
                }
                break;
            }
            case 4:
                selectSet(&A, &B)->add(getInput());
                break;
            case 5:
                selectSet(&A, &B)->remove(getInput());
                break;
            case 6:
                selectSet(&A, &B)->removeByType(selectType());
                break;
            case 7:
                cout << selectSet(&A, &B)->complexSum().to_str() << endl;
                break;
            case 8:
                selectSet(&A, &B)->clear();
                break;
            case 9:
                NumberSet::myUnion(A, B).print();
                break;
            case 10:
                NumberSet::myIntersect(A, B).print();
                break;
            case 11:
                NumberSet::mySubtraction(A, B).print();
                break;
            case 12:
                NumberSet::mySubtraction(B, A).print();
                break;
            case 13:
                exit(0);
            default:
                break;
        }
    }
}

bool Number::isEqual(Number* n1, Number* n2){
    if (n1->type() != n2->type()){
        return false;
    } 
    if (n1->type() == 1){
        Rational* r1 = (Rational*) n1, *r2 = (Rational*) n2;
        return Rational::isEqual(*r1, *r2);
    }
    if (n1->type() == 2){
        Complex* c1 = (Complex*) n1, *c2 = (Complex*) n2;
        return Complex::isEqual(*c1, *c2);
    }
    return false;
}

Complex::Complex(float inp1 = 0, float inp2 = 0){
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
    cout << this->to_str();
}

int Complex::type() const{
    return 2;
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

bool Complex::isEqual(Complex a, Complex b){
    if (a.x == b.x && a.y == b.y){
        return true;
    }
    return false;
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

int Rational::type() const{
    return 1;
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

bool Rational::isEqual(Rational a, Rational b){
    if (a.numerator == b.denominator && a.numerator == b.denominator){
        return true;
    }
    return false;
}

int listSize(Node* list){
    int counter = 0;
    Node* current = list;
    while (current){
        counter++;
        current->next;
    }
    return counter;
}

bool IsInList(Node* list, Number* data){
    Node* current = list;
    while (current){
        if (Number::isEqual(current->data, data)){
            return true;
        }
    }
    return false;
}

Node* insertDown(Node* head, Number *data){
    Node* temp = new Node;
    temp->data = data;
    if (! head){
        return temp;
    }
    Node* last = head;
    while (last){
        last = last->next;
    }
    last->next = temp;
    return head;
}

void clearList(Node* head){
    while (head){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

Node* removeItem(Node* head, Number* data){
    if (! head){
        return NULL;
    }
    if (Number::isEqual(head->data, data)){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    Node* p = head, *q = head->next;
    while (q){
        if (Number::isEqual(q->data, data)){
            Node* temp = q;
            q = q->next;
            p->next = q;
            delete temp;
            return head;
        }
        p = q;
        q = q->next;
    }
    return head;
}

Node* removeItemsByType(Node* head, int type){
    while (head && head->data->type() == type){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    if (head == NULL){
        return NULL;
    }
    Node* p = head;
    Node* q = head->next;
    while (q){
        if (q->data->type() == type){
            Node* temp = q;
            q = q->next;
            p->next = q;
            delete temp;
        } else {
            p = q;
            q = q->next;
        }
    }
    return head;
}

NumberSet::NumberSet(){
    this->list = NULL;
}

bool NumberSet::search(Number* query) const{
    if (IsInList(this->list, query)){
        return true;
    }
    return false;
}

void NumberSet::add(Number* input){
    if (! this->search(input)){
        this->list = insertDown(this->list, input);
    }
}

void NumberSet::remove(Number* input){
    this->list = removeItem(this->list, input);
}

void NumberSet::removeByType(int type){
    this->list = removeItemsByType(this->list, type);
}

void NumberSet::clear(){
    clearList(this->list);
}

int NumberSet::size() const{
    return listSize(this->list);
}

void NumberSet::print() const{
    Node* current = this->list;
    cout << "{";
    while (current){
        current->data->print();
        cout << " ,";
        current = current->next;
    }
    cout << "}\n";
}

void NumberSet::printByType(int type) const{
    Node* current = this->list;
    cout << "{";
    while (current){
        if (current->data->type() == type){
            current->data->print();
            cout << " ,";
        }
        current = current->next;
    }
    cout << "}\n";
}

Complex NumberSet::complexSum() const{
    Complex result(0,0);
    Node* current = list;
    while (current){
        if (current->data->type() == 2){
            Complex* cmplxptr = (Complex*) current->data;
            result = Complex::sum(result, *cmplxptr);
        }
        current = current->next;
    }
    return result;
}

NumberSet NumberSet::myUnion(NumberSet s1, NumberSet s2){
    NumberSet result;
    Node* current = s1.list;
    while (current){
        result.add(current->data);
        current = current->next;
    }
    current = s2.list;
    while (current){
        result.add(current->data);
        current = current->next;
    }
    return result;
}

NumberSet NumberSet::myIntersect(NumberSet s1, NumberSet s2){
    NumberSet result;
    Node* current = s1.list;
    while (current){
        if (s2.search(current->data)){
            result.add(current->data);
        }
        current = current->next;
    }
    return result;
}

NumberSet NumberSet::mySubtraction(NumberSet s1, NumberSet s2){
    NumberSet result;
    Node* current = s1.list;
    while (current){
        if (! s2.search(current->data)){
            result.add(current->data);
        }
        current = current->next;
    }
    return result;
}

int menu(){
    int choice;
    do {
        cout << "1- Show set\n2- Show subset\n3- Search set\n4- Add member\n5- Remove member\n6- Remove subset\n7- Calculate summation of Complex subset\n8- Purge set\n9- A U B\n10- A n B\n11- A-B\n12- B-A\n13- Exit\noption?...\t";
        cin >> choice;
        if (choice > 13 || choice < 1){
            cout << "Invalid option!" << endl;
        }
    } while (choice > 13 || choice < 1);
    return choice;
}

Number* getInput(){
    int choice;
    do {
        cout << "1- Rational\n2- Complex\noption?...\t";
        cin >> choice;
        if (choice > 2 || choice < 1){
            cout << "Invalid option!" << endl;
        }
    } while (choice > 2 || choice < 1);
    Number* result;
    if (choice == 2){
        float x, y;
        cout << "Z = X + iY" << endl;
        cout << "X:\t";
        cin >> x;
        cout <<"Y:\t";
        cin >> y;
        Complex* cmplxptr = new Complex(x, y);
        result = cmplxptr;
    } else if (choice == 1){
        int x, y;
        cout << "R = X/Y" << endl;
        cout << "X:\t";
        cin >> x;
        cout <<"Y:\t";
        cin >> y;
        Rational* rtnlptr = new Rational(x, y);
        result = rtnlptr;
    }
    return result;
}

NumberSet* selectSet(NumberSet* A, NumberSet* B){
    int choice;
    do {
        cout << "Select Set:\n1- A\n2- B\noption?...\t";
        cin >> choice;
        if (choice > 2 || choice < 1){
            cout << "Invalid option!" << endl;
        }
    } while (choice > 2 || choice < 1);
    if (choice == 1){
        return A;
    } 
    if (choice == 2){
        return B;
    }
    return NULL;
}

int selectType(){
    int choice;
    do {
        cout << "Select type:\n1- Rational\n2- Complex\noption?...\t";
        cin >> choice;
        if (choice > 2 || choice < 1){
            cout << "Invalid option!" << endl;
        }
    } while (choice > 2 || choice < 1);
    return choice;
}