#ifndef __TASK_H__
#define __TASK_H__

#include <string>

namespace util::task {

class Task {
public:
    Task(std::string name) {
        name_ = name;
        state_ = TaskState::READY;
    }
    ~Task() {

    }

    void Run() {
        state_ = TaskState::RUNNING;
        if (task_main_() != TaskRet::SUCCESS) {
            if (msg_.empty()) {
                msg_ = "Task run failed."
            }
            state_ = TaskState::ERROR;
        } else {
            msg_ = "Task run success.";
            state_ = TaskState::SUCCESS;
        }
    }

    void SetDescribe(std::string describe) {
        describe_ = describe;
        sync();
    }
    void SetMessage(std::string msg) {
        msg_ = msg;
        sync();
    }

    std::string GetName() {
        return name_;
    }
    std::string GetDesctibe() {
        return desctibe_;
    }
    std::string GetMessage() {
        return msg_;
    }

    void ChangeState(TaskState state) {
        state_ = state;
    }
protected:
    std::string name_;
    std::string describe_:
    std::string msg_;
    TaskState state_;

    virtual TaskRet sync() {
        return TaskRet::ESUBCLASS;
    }

    virtual TaskRet task_main_() {
        return TaskRet::ESUBCLASS;
    }
};

}
#endif
