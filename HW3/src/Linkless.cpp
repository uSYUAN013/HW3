#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Node {
public:
    int coef;
    int exp;
    Node* link;

    Node(int c = 0, int e = 0) : coef(c), exp(e), link(NULL) {}
};

class Polynomial {
private:
    Node* head;

public:
    Polynomial();
    Polynomial(const Polynomial& a);
    ~Polynomial();
    const Polynomial& operator=(const Polynomial& a);

    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, const Polynomial& x);

    Polynomial operator+(const Polynomial& b) const;
    Polynomial operator-(const Polynomial& b) const;
    Polynomial operator*(const Polynomial& b) const;
    float Evaluate(float x) const;

private:
    void InsertTerm(int coef, int exp);
    void Clear();
};

// Default Constructor
Polynomial::Polynomial() {
    head = new Node();
    head->link = head;
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial& a) {
    head = new Node();
    head->link = head;
    Node* current = a.head->link;
    while (current != a.head) {
        InsertTerm(current->coef, current->exp);
        current = current->link;
    }
}

// Destructor
Polynomial::~Polynomial() {
    Clear();
    delete head;
}

// Assignment Operator
const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) {
        Clear();
        Node* current = a.head->link;
        while (current != a.head) {
            InsertTerm(current->coef, current->exp);
            current = current->link;
        }
    }
    return *this;
}

// Input Operator
istream& operator>>(istream& is, Polynomial& x) {
    int n, coef, exp;
    is >> n;
    for (int i = 0; i < n; ++i) {
        is >> coef >> exp;
        x.InsertTerm(coef, exp);
    }
    return is;
}

// Output Operator with improved format
ostream& operator<<(ostream& os, const Polynomial& x) {
    Node* current = x.head->link;
    bool firstTerm = true;
    while (current != x.head) {
        if (current->coef > 0 && !firstTerm) {
            os << " + ";
        } else if (current->coef < 0) {
            os << " - ";
        }

        int absCoef = abs(current->coef);
        if (absCoef != 1 || current->exp == 0) {
            os << absCoef;
        }

        if (current->exp != 0) {
            os << "x";
            if (current->exp != 1) {
                os << "^" << current->exp;
            }
        }

        current = current->link;
        firstTerm = false;
    }
    return os;
}

// Insert a term in decreasing order of exponents
void Polynomial::InsertTerm(int coef, int exp) {
    if (coef == 0) return;
    Node* prev = head;
    Node* current = head->link;

    while (current != head && current->exp > exp) {
        prev = current;
        current = current->link;
    }

    if (current != head && current->exp == exp) {
        current->coef += coef;
        if (current->coef == 0) {
            prev->link = current->link;
            delete current;
        }
    } else {
        Node* newNode = new Node(coef, exp);
        newNode->link = current;
        prev->link = newNode;
    }
}

// Clear the polynomial
void Polynomial::Clear() {
    Node* current = head->link;
    while (current != head) {
        Node* temp = current;
        current = current->link;
        delete temp;
    }
    head->link = head;
}

// Addition
Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Node* aPtr = head->link;
    Node* bPtr = b.head->link;

    while (aPtr != head || bPtr != b.head) {
        if (aPtr == head) {
            result.InsertTerm(bPtr->coef, bPtr->exp);
            bPtr = bPtr->link;
        } else if (bPtr == b.head) {
            result.InsertTerm(aPtr->coef, aPtr->exp);
            aPtr = aPtr->link;
        } else if (aPtr->exp > bPtr->exp) {
            result.InsertTerm(aPtr->coef, aPtr->exp);
            aPtr = aPtr->link;
        } else if (aPtr->exp < bPtr->exp) {
            result.InsertTerm(bPtr->coef, bPtr->exp);
            bPtr = bPtr->link;
        } else {
            result.InsertTerm(aPtr->coef + bPtr->coef, aPtr->exp);
            aPtr = aPtr->link;
            bPtr = bPtr->link;
        }
    }

    return result;
}

// Subtraction
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Node* bPtr = b.head->link;
    while (bPtr != b.head) {
        result.InsertTerm(-bPtr->coef, bPtr->exp);
        bPtr = bPtr->link;
    }
    return *this + result;
}

// Multiplication
Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;
    Node* aPtr = head->link;
    while (aPtr != head) {
        Node* bPtr = b.head->link;
        while (bPtr != b.head) {
            result.InsertTerm(aPtr->coef * bPtr->coef, aPtr->exp + bPtr->exp);
            bPtr = bPtr->link;
        }
        aPtr = aPtr->link;
    }
    return result;
}

// Evaluate polynomial at x
float Polynomial::Evaluate(float x) const {
    float result = 0;
    Node* current = head->link;
    while (current != head) {
        result += current->coef * std::pow(x, current->exp);
        current = current->link;
    }
    return result;
}

// Main function for testing
int main() {
    Polynomial p1, p2;
    cout << "Enter the first polynomial (n, coef, exp): ";
    cin >> p1;
    cout << "Enter the second polynomial (n, coef, exp): ";
    cin >> p2;

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "p1 + p2: " << sum << endl;
    cout << "p1 - p2: " << diff << endl;
    cout << "p1 * p2: " << prod << endl;

    float x;
    cout << "Enter a value to evaluate p1: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}

