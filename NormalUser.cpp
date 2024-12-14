#include "NormalUser.h"
#include "NormalUserState.h"

NormalUser::NormalUser(const string& username, const string& password, Customer* customer) : User(username, password) {
    state = new NormalUserState(customer);
}

NormalUser::NormalUser(const string& username, const string& password) : User(username, password) {
    state = new NormalUserState;
}

Customer* NormalUser::getCustomer() {
    return state->getCustomer();
}

string NormalUser::getCustomerName() {
    return state->getCustomerName();
}

string NormalUser::getType() const {
    return "customer";
}

NormalUser::~NormalUser() {
    delete state;
}