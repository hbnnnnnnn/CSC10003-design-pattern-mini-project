#ifndef NORMALUSERSTATE_H
#define NORMALUSERSTATE_H

#include "ManageSys.h"
#include "CommandInvoker.h"
#include "AddToCartCommand.h"
#include "Command.h"
#include "ConfirmationCommand.h"
#include "CheckOutCommand.h"
#include "CancelOrderCommand.h"
#include "ViewOrderDetailsCommand.h"
#include "ViewAllOrderCommand.h"
#include "Customer.h"

class NormalUserState : public UserState {
    Customer* customer;
public:
    NormalUserState() : customer(nullptr) {}
    NormalUserState(Customer* customer) : customer(customer) {}
    
    void showMenu() override;
    void orderManagementMenu(CommandInvoker& invoker);
    void confirmationMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker);
    void searchBooksMenu(ManageSys* manageSys);
    void viewBookDetails(const string& command, ManageSys* manageSys);
    void addToCartMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker);
    void checkOutMenu(ManageSys* manageSys, Order* order, CommandInvoker& invoker);
    void accountManagementMenu(ManageSys* manager);
    void changePassword(ManageSys* manager, User* user);
};

#endif // NORMALUSERSTATE_H
