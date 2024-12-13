#pragma once
#include <stack>
#include "Command.h"
#include <iostream>

using namespace std;

class CommandInvoker {
private:
    stack<Command*> commandHistory;  // Stores executed commands for undo

public:
    void executeCommand(Command* command) {
        command->execute();
        commandHistory.push(command); // Save command to history
    }

    void undoLastCommand() {
        if (!commandHistory.empty()) {
            Command* lastCommand = commandHistory.top();
            lastCommand->undo();
            commandHistory.pop();
            delete lastCommand;  // Clean up the command
        } else {
            cout << "No commands to undo." << endl;
        }
    }

    ~CommandInvoker() {
        // Clean up remaining commands
        while (!commandHistory.empty()) {
            delete commandHistory.top();
            commandHistory.pop();
        }
    }
};
