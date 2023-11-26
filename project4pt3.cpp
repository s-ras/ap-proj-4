#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Complex{
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
        static bool isEqual(Complex, Complex);
};

struct Node{
    Complex data;
    Node* next = NULL;
};

class MySet{
    private: 
        Node* list;
    public: 
        MySet();
        bool search(Complex) const;
        void add(Complex);
        void remove(Complex);
        void clear();
        int size() const;
        void print() const;
        Complex setSum() const;
        static MySet myUnion(MySet, MySet);
        static MySet myIntersect(MySet, MySet);
        static MySet mySubtraction(MySet, MySet);
};

int menu();
Complex getInput();

int main(){

    MySet A, B;

    while (true){
        int choice = menu();
        switch (choice){
            case 1:
                A.print();
                break;
            case 2:
                B.print();
                break;
            case 3:
                A.add(getInput());
                break;
            case 4:
                B.add(getInput());
                break;
            case 5:
                A.remove(getInput());
                break;
            case 6:
                B.remove(getInput());
                break;
            case 7:
                cout << "Summation of members of A set is " << A.setSum().to_str() << "." << endl;
                break;
            case 8:
                cout << "Summation of members of B set is " << B.setSum().to_str() << "." << endl;
                break;
            case 9:
                A.clear();
                break;
            case 10:
                B.clear();
                break;
            case 11:
                MySet::myUnion(A, B).print();
                break;
            case 12:
                MySet::myIntersect(A, B).print();
                break;
            case 13:
                MySet::mySubtraction(A, B).print();
                break;
            case 14:
                MySet::mySubtraction(B, A).print();
                break;
            case 15:
                exit(0);
            default:
                break;
        }
    }

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

int listSize(Node* list){
    int counter = 0;
    Node* current = list;
    while (current){
        counter++;
        current->next;
    }
    return counter;
}

bool IsInList(Node* list, Complex data){
    Node* current = list;
    while (current){
        if (Complex::isEqual(current->data, data)){
            return true;
        }
    }
    return false;
}

Node* insertDown(Node* head, Complex data){
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

Node* removeItem(Node* head, Complex data){
    if (! head){
        return NULL;
    }
    if (Complex::isEqual(head->data, data)){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    Node* p = head, *q = head->next;
    while (q){
        if (Complex::isEqual(q->data, data)){
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

Complex itemsSum(Node* list){
    Complex result(0, 0);
    Node* current = list;
    while (current){
        result = Complex::sum(result, current->data);
        current = current->next;
    }
    return result;
}

MySet::MySet(){
    this->list = NULL;
}

bool MySet::search(Complex query) const{
    if (IsInList(this->list, query)){
        return true;
    }
    return false;
}

void MySet::add(Complex input){
    if (! this->search(input)){
        this->list = insertDown(this->list, input);
    }
}

void MySet::remove(Complex input){
    this->list = removeItem(this->list, input);
}

void MySet::clear(){
    clearList(this->list);
}

int MySet::size() const{
    return listSize(this->list);
}

void MySet::print() const{
    Node* current = this->list;
    cout << "{";
    while (current){
        current->data.print();
        cout << " ,";
        current = current->next;
    }
    cout << "}\n";
}

Complex MySet::setSum() const{
    return itemsSum(this->list);
}

MySet MySet::myUnion(MySet s1, MySet s2){
    MySet result;
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

MySet MySet::myIntersect(MySet s1, MySet s2){
    MySet result;
    Node* current = s1.list;
    while (current){
        if (s2.search(current->data)){
            result.add(current->data);
        }
        current = current->next;
    }
    return result;
}

MySet MySet::mySubtraction(MySet s1, MySet s2){
    MySet result;
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
        cout << "1-Show set A\n2-Show set B\n3- Add to set A\n4- Add to set B\n5- Remove from set A\n6- Remove from set B\n7- Calculate summation of set A\n8- Calculate summation of set B\n9- Clear set A\n10- Clear set B\n11- A U B\n12- A n B\n13- A-B\n14- B-A\n15- exit\noption?...\t";
        cin >> choice;
        if (choice > 15 || choice < 1){
            cout << "Invalid option!" << endl;
        }
    } while (choice > 15 || choice < 1);
    return choice;
}

Complex getInput(){
    float x, y;
    cout << "Z = X + iY" << endl;
    cout << "X:\t";
    cin >> x;
    cout <<"Y:\t";
    cin >> y;
    return Complex(x, y);
}