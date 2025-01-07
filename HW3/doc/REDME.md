# HW3 Linkless

## 1.解題說明

多項式表示方式：每個多項式的輸入形式為一組 (n, coef, exp)，n 為多項
式的項數；oef 為係數；xp 為指數。

鏈結串列：讓頭節點方便地指向自己，並且能夠輕鬆進行插入和刪除操作。
coef：係數；exp：指數；link：指向下一個節點的指標。 

## 2.程式實作

### (a)

```cpp
istream& operator>>(istream& is, Polynomial& x) {
    int n, coef, exp;
    is >> n;
    for (int i = 0; i < n; ++i) {
        is >> coef >> exp;
        x.InsertTerm(coef, exp);
    }
    return is;
}
```

### (b)

```cpp
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
```

### (c)

```cpp
Polynomial::Polynomial(const Polynomial& a) {
    head = new Node();
    head->link = head;
    Node* current = a.head->link;
    while (current != a.head) {
        InsertTerm(current->coef, current->exp);
        current = current->link;
    }
}
```

### (d)

```cpp
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
```

### (e)

```cpp
Polynomial::~Polynomial() {
    Clear();
    delete head;
}
```

### (f)

```cpp
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
```

### (g)

```cpp
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Node* bPtr = b.head->link;
    while (bPtr != b.head) {
        result.InsertTerm(-bPtr->coef, bPtr->exp);
        bPtr = bPtr->link;
    }
    return *this + result;
}
```

### (h)

```cpp
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
```

### (i)

```cpp
float Polynomial::Evaluate(float x) const {
    float result = 0;
    Node* current = head->link;
    while (current != head) {
        result += current->coef * std::pow(x, current->exp);
        current = current->link;
    }
    return result;
}
```

## 3.效能分析

### 空間複雜度

Add: O( $n1+n2$ ) 其中 n1 和 n2 分別是兩個多項式的非零項數量。

Mult: O( $n1 \times n2$ )

Eval: O( $1$ )

### 時間複雜度

Add: O( $n1+n2$ )

Mult: O( $n1 \times n2$ )

Eval: O( $n$ )
## 4.測試與驗證

```
輸入第一個多項式:
輸入非零項的數量: 3
輸入第1項的係數和指數: 4 2
輸入第2項的係數和指數: 3 1
輸入第3項的係數和指數: 2 0
輸入第二個多項式:
輸入非零項的數量: 3
輸入第1項的係數和指數: 4 2
輸入第2項的係數和指數: 3 1
輸入第3項的係數和指數: 2 0
第一個多項式: 4x^2+3x^1+2x^0
第二個多項式: 4x^2+3x^1+2x^0
多項式的和: 8x^2+6x^1+4x^0
多項式的積: 16x^4+24x^3+25x^2+12x^1+4x^0
輸入一個值給p1代入:3
p1(3) = 47
```

## 5.心得討論

這次的作業我學到了好多東西，而且也更精進了自己編寫程式碼的邏輯與思維，老師說學一個東西都是要從基礎開始打，
不然後面更難的實作要怎麼辦，我覺得說得很對，所以透過這次打好基礎之後，我感覺我可以更進一步挑戰更難的問題了。
