class PaymentStrategy {
public:
    PaymentStrategy() = default;
    virtual ~PaymentStrategy() = default;
    virtual void input() = 0;
    virtual bool pay(float amount) = 0;
    virtual string getPaymentMethod() = 0;
};