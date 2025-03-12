#include <iostream>
#include <cmath>

using namespace std;

const int MaxDegree = 4;  // Maximum degree of the polynomial

class Polynomial {
private:
    int degree;  
    float coef[MaxDegree + 1];  

public:
    // Constructor to Initialize polynomial with a specific degree and coefficient
    Polynomial(int deg) : degree(deg) {
        for (int i = 0; i <= MaxDegree; i++) {
            coef[i] = 0;
        }
    }

    // Set the coefficient of the polynomial at a particular degree
    void setCoefficient(int deg, float coefficient) {
        if (deg <= degree && deg <= MaxDegree && deg >= 0) {
            coef[deg] = coefficient;
        } else {
            cout << " Wrong degree!" << endl;
        }
    }

    // Add two polynomials
    Polynomial Add(const Polynomial& other) {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; i++) {
            if (i <= degree) result.coef[i] += coef[i];
            if (i <= other.degree) result.coef[i] += other.coef[i];
        }
        return result;
    }

    // Multiply two polynomials
    Polynomial Mult(const Polynomial& other) {
        Polynomial result(degree + other.degree);  // Degree of the product

        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= other.degree; j++) {
                if (i + j <= MaxDegree) {
                    result.coef[i + j] += coef[i] * other.coef[j];
                }
            }
        }
        return result;
    }

    // Evaluate the polynomial for a given value of x
    float Eval(float x) {
        float result = 0;
        for (int i = 0; i <= degree; i++) {
            result += coef[i] * pow(x, i);
        }
        return result;
    }

    // Function to display the polynomial
    void print() {
        bool firstTerm = true;
        for (int i = degree; i >= 0; i--) {
            if (coef[i] != 0) {
                if (!firstTerm) {
                    cout << (coef[i] > 0 ? " + " : " - ");
                } else {
                    if (coef[i] < 0) cout << "-";
                    firstTerm = false;
                }
                if (i == 0 || abs(coef[i]) != 1) {
                    cout << abs(coef[i]);
                }
                if (i > 0) {
                    cout << "x";
                    if (i > 1) {
                        cout << "^" << i;
                    }
                }
            }
        }
        cout << endl;
    }
};

// Function to handle inputs
Polynomial inputPolynomial() {
    int degree;
    cout << "Enter the degree of the polynomial : ";
    cin >> degree;
    Polynomial poly(degree);

    for (int i = degree; i >= 0; i--) {
        float coef;
        cout << "Enter coefficient for x^" << i << ": ";
        cin >> coef;
        poly.setCoefficient(i, coef);
    }
    return poly;
}

int main() {
    // Input polynomials
    Polynomial poly1 = inputPolynomial();
    Polynomial poly2 = inputPolynomial();

    // Print the polynomials
    cout << "Polynomial 1: ";
    poly1.print();
    cout << "Polynomial 2: ";
    poly2.print();

    // Add polynomials and print result
    Polynomial sum = poly1.Add(poly2);
    cout << " The sum is: ";
    sum.print();

    // Multiply polynomials and print result
    Polynomial product = poly1.Mult(poly2);
    cout << "The Product is: ";
    product.print();

    // Evaluate polynomials at a given number (e.g., x = 2)
    float x;
    cout << "Enter a value to evaluate the polynomials at: ";
    cin >> x;

    cout << "Evaluation of Polynomial 1 at x = " << x << ": " << poly1.Eval(x) << endl;
    cout << "Evaluation of Polynomial 2 at x = " << x << ": " << poly2.Eval(x) << endl;

    return 0;
}

