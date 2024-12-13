#pragma once

#include "ManageSys.h"
#include "CommandInvoker.h"
#include "AddToCartCommand.h"
#include "Command.h"
#include "ConfirmationCommand.h"
#include "CheckOutCommand.h"
#include "CreditCard.h"
#include "BankTransfer.h"
#include "EWallet.h"
#include "COD.h"
#include "PaymentStrategy.h"
#include "CancelOrderCommand.h"
#include "ViewOrderDetailsCommand.h"
#include "ViewAllOrderCommand.h"

class NormalUserState : public UserState {
public:
    void showMenu() override;
    void orderManagementMenu(Customer* customer, CommandInvoker& invoker);
    void confirmationMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker);
    void searchBooksMenu(ManageSys* manageSys);
    void viewBookDetails(const string& command, ManageSys* manageSys);
    void addToCartMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker);
    void checkOutMenu(ManageSys* manageSys, Order* order, CommandInvoker& invoker);
    void accountManagementMenu(ManageSys* manager, User* user);
    void changePassword(ManageSys* manager, User* user);
};



