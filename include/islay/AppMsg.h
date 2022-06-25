//
// Created by Masahiro Hirano <masahiro.dll@gmail.com>
//

#ifndef ISLAY_APPMSG_H
#define ISLAY_APPMSG_H

#include <DeviceSetting.h>

#include <opencv2/opencv.hpp>
#include <map>
#include <memory>
#include <islay/InterThreadMessenger.hpp>

#if WITH_OPTI
#include <NatNetTypes.h>
#endif

struct DispMsg : public MsgData {
    std::map<std::string, cv::Mat> pool;
};

#if WITH_OPTI
struct OptiTrackDataMsg : public MsgData {
    sDataDescriptions optiTrackDataDescriptions;
    sFrameOfMocapData optiTrackData;
};
#endif

struct OptiTrackVerboseMsg : public MsgData {
    bool isVerbose; // show all OptiTrack messages as in the distributed sample code.
};

struct RequestMsg : public MsgData {
    bool isRequested = false;
};

class AppMsg{
public:
    AppMsg():
        displayMessenger(new InterThreadMessenger<DispMsg>),
        optiTrackTerminationRequestMessenger(new InterThreadMessenger<RequestMsg>),
#if WITH_OPTI
        optiTrackDataMessenger(new InterThreadMessenger<OptiTrackDataMsg>),
#endif
        optiTrackVerboseMessenger(new InterThreadMessenger<OptiTrackVerboseMsg>)
    {};
    InterThreadMessenger<DispMsg>* displayMessenger;

#if WITH_OPTI
    // OptiTrack (in OptiTrack thread) ----> GalvanoMirror (in GalvanoMirror thread)
// For sending OptiTrack's retrieved data
    InterThreadMessenger<OptiTrackDataMsg>* optiTrackDataMessenger;
#endif

    // EngineOffline (in main thread) ----> OptiTrack (in OptiTrack thread)
// For sending termination request of OptiTrack
    InterThreadMessenger<RequestMsg>* optiTrackTerminationRequestMessenger;

    // Application (in main thread) ----> OptiTrack (in OptiTrack thread)
    // For sending if verbose is set
    InterThreadMessenger<OptiTrackVerboseMsg>* optiTrackVerboseMessenger;


    void close(){
        displayMessenger->close();
#if WITH_OPTI
        optiTrackDataMessenger->close();
#endif
        optiTrackTerminationRequestMessenger->close();
        optiTrackVerboseMessenger->close();
    };
};

using AppMsgPtr = std::shared_ptr<AppMsg>;

#endif //ISLAY_APPMSG_H
