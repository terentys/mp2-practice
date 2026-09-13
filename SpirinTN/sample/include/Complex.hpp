#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex {
    float re;
    float im;

    Complex() noexcept : re(0.0f), im(0.0f) {}
    Complex(float re, float im) noexcept : re(re), im(im) {}

    const Complex& operator= (const Complex& c);
    const Complex& operator+= (const Complex& c);

    Complex operator+ (const Complex& c) const;
    Complex operator- (const Complex& c) const;
    Complex operator* (const Complex& c) const;
    Complex operator/ (const Complex& c) const;

    bool operator== (const Complex& c) const;
    bool operator!= (const Complex& c) const;

    friend std::istream& operator>> (std::istream& is, Complex& c);
    friend std::ostream& operator<< (std::ostream& os, const Complex& c);
};

#endif