//
// Created by Hirano Masahiro <masahiro.dll@gmail.com>
//

#ifndef ISLAY_WORKERSAMPLE_H
#define ISLAY_WORKERSAMPLE_H

#include <islay/Worker.h>

/**
 * @brief Your main code comes here!
 */
class WorkerMain : public WorkerBase {
public:
    explicit WorkerMain (AppMsgPtr appMsg): WorkerBase(appMsg){};
    bool run(const std::shared_ptr<void> data);
};

/**
 * @brief OptiTrack server
 */
class WorkerOptiTrackServer : public WorkerBase {
public:
    explicit WorkerOptiTrackServer(AppMsgPtr appMsg) : WorkerBase(appMsg) {};
    bool run(const std::shared_ptr<void> data);
};

/**
 * @brief OptiTrack client
 */
class WorkerOptiTrackClient : public WorkerBase {
public:
    explicit WorkerOptiTrackClient(AppMsgPtr appMsg) : WorkerBase(appMsg) {};
    bool run(const std::shared_ptr<void> data);
};



#endif //ISLAY_WORKERSAMPLE_H
