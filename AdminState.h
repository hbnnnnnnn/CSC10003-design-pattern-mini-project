#pragma once

#include "ManageSys.h"
#include "UserState.h"

using namespace std;

class AdminState : public UserState {
    ManageSys* manageSys;

public:
    AdminState(ManageSys* manageSys) : manageSys(manageSys) {}

    void showMenu() override;
    void orderManagementMenu();
    void bookManagementMenu();
    void authorManagementMenu();
    void reportManagementMenu();
    void importManagementMenu();
};
