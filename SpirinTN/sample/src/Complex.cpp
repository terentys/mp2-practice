#include <iostream>
#include <stdexcept>

#include "../include/Complex.hpp"

const Complex& Complex::operator= (const Complex& c) {
    if (&c == this) return *this;
    re = c.re;
    im = c.im;
    return *this;
}

const Complex& Complex::operator+= (const Complex& c) {
    re += c.re;
    im += c.im;
    return *this;
}

Complex Complex::operator+ (const Complex& c) const {
    return Complex(re + c.re, im + c.im);
}

Complex Complex::operator- (const Complex& c) const {
    return Complex(re - c.re, im - c.im);
}

Complex Complex::operator* (const Complex& c) const {
    return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
}

Complex Complex::operator/ (const Complex& c) const {
    if (c.re == 0.0f && c.im == 0.0f) {
        throw std::invalid_argument("division by zero");
    }
    float denominator = c.re * c.re + c.im * c.im;
    return Complex((re * c.re + im * c.im) / denominator, (c.re * im - re * c.im) / denominator);
}

bool Complex::operator== (const Complex& c) const {
    return re == c.re && im == c.im;
}
bool Complex::operator!= (const Complex& c) const {
    return re != c.re || im != c.im;
}

std::istream& operator>> (std::istream& is, Complex& c) {
    is >> c.re >> c.im;
    return is;
}

std::ostream& operator<< (std::ostream& os, const Complex& c) {
    os << c.re << " + " << c.im << "i";
    return os;
}