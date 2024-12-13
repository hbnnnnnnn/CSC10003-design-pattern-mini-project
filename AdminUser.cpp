#include "ManageSys.h"
#include "AdminUser.h"
#include "AdminState.h"

AdminUser::AdminUser(const string& username, const string& password) : User(username, password) {
    state = new AdminState(ManageSys::getInstance());
}