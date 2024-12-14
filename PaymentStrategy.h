#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <string>
using namespace std;

class PaymentStrategy {
public:
    PaymentStrategy() = default;
    virtual ~PaymentStrategy() = default;
    virtual void input() = 0;
    virtual bool pay(float amount) = 0;
    virtual string getPaymentMethod() = 0;
    virtual PaymentStrategy* clone() const = 0;
};

#endif // PAYMENTSTRATEGY_H
