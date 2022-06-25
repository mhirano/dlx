//
// Created by Hirano Masahiro <masahiro.dll@gmail.com>
//

#include "Engine.h"
#include "WorkerSample.h"

#include <opencv2/opencv.hpp>
#include <OptiTrack.h>

bool Engine::run() {
    return true;
}

bool Engine::runWorkerSampleWithAppMsg() {
    /*
     * Register a worker with its name
     */
    registerWorkerWithAppMsg<WorkerMain>("WorkerMain");

    /*
     * You can pass a variable to the worker as a shared pointer.
     */
    std::shared_ptr<int> hoge(new int(123));

    /*
     * Run the worker
     */
    runWorker("WorkerMain", hoge);

    return true;
}



/**
 * OptiTrack
 */

bool Engine::runOptiTrackServer() {

    registerWorkerWithAppMsg<WorkerOptiTrackServer>("OptiTrackServer");
    runWorker("OptiTrackServer");

    return true;
}

/**
 *
 */
 bool Engine::runOptiTrackClient() {
    registerWorkerWithAppMsg<WorkerOptiTrackClient>("OptiTrackClient");
    runWorker("OptiTrackClient");

    return true;
 }