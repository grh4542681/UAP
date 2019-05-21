#ifndef __TASK_STATE_H__
#define __TASK_STATE_H__

namespace util::task {

enum class TaskState {
    READY,
    WAIT,
    RUNNING,
    ERROR,
    SUCCESS,
};

}

#endif
