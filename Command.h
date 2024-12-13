#pragma once
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;  // Perform the operation
    virtual Order* getLastOrder() const { return nullptr; }  // Return the last order (optional)
    virtual void undo() = 0;     // Revert the operation (optional)
};

