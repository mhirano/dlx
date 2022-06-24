//
// Created by Masahiro Hirano <masahiro.dll@gmail.com>
//

#ifndef ISLAY_APPMSG_H
#define ISLAY_APPMSG_H

#include <opencv2/opencv.hpp>
#include <map>
#include <memory>
#include <islay/InterThreadMessenger.hpp>

#include <NatNetTypes.h>

struct DispMsg : public MsgData {
    std::map<std::string, cv::Mat> pool;
};

struct OptiTrackDataMsg : public MsgData {
    sDataDescriptions optiTrackDataDescriptions;
    sFrameOfMocapData optiTrackData;
};

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
        optiTrackDataMessenger(new InterThreadMessenger<OptiTrackDataMsg>),
        optiTrackVerboseMessenger(new InterThreadMessenger<OptiTrackVerboseMsg>)
    {};
    InterThreadMessenger<DispMsg>* displayMessenger;

    // OptiTrack (in OptiTrack thread) ----> GalvanoMirror (in GalvanoMirror thread)
// For sending OptiTrack's retrieved data
    InterThreadMessenger<OptiTrackDataMsg>* optiTrackDataMessenger;

    // EngineOffline (in main thread) ----> OptiTrack (in OptiTrack thread)
// For sending termination request of OptiTrack
    InterThreadMessenger<RequestMsg>* optiTrackTerminationRequestMessenger;

    // Application (in main thread) ----> OptiTrack (in OptiTrack thread)
    // For sending if verbose is set
    InterThreadMessenger<OptiTrackVerboseMsg>* optiTrackVerboseMessenger;


    void close(){
        displayMessenger->close();
        optiTrackDataMessenger->close();
        optiTrackTerminationRequestMessenger->close();
        optiTrackVerboseMessenger->close();
    };
};

using AppMsgPtr = std::shared_ptr<AppMsg>;

#endif //ISLAY_APPMSG_H
