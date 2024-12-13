class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;  // Perform the operation
    virtual void undo() = 0;     // Revert the operation (optional)
};

