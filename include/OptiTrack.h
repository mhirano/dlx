//
// Created by Hirano Masahiro <masahiro.dll@gmail.com>
//

#pragma once 

#ifndef OPTITRACK_H
#define OPTITRACK_H

#pragma comment(lib, "NatNetLib")

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#   include <conio.h>
#else
#   include <unistd.h>
#   include <termios.h>
#endif

#include <vector>

#include <opencv2/opencv.hpp>
#include <NatNetTypes.h>
#include <NatNetCAPI.h>
#include <NatNetClient.h>

#include <islay/AppMsg.h>

class OptiTrack {
#ifndef _WIN32
	char getch();
#endif
	void _WriteHeader(FILE* fp, sDataDescriptions* pBodyDefs);
	void _WriteFrame(FILE* fp, sFrameOfMocapData* data);
	void _WriteFooter(FILE* fp);

	void NATNET_CALLCONV ServerDiscoveredCallback(const sNatNetDiscoveredServer* pDiscoveredServer);
	// Interface to NatNetSDK
	static void to_ServerDiscoveredCallback(const sNatNetDiscoveredServer* pDiscoveredServer, void* pUserContext = NULL) {
		return reinterpret_cast<OptiTrack*>(pUserContext)->ServerDiscoveredCallback(pDiscoveredServer);
	}

	void NATNET_CALLCONV DataHandler(sFrameOfMocapData* data);    // receives data from the server
	// Interface to NatNetSDK
	static void to_DataHandler(sFrameOfMocapData* data, void* pUserData) {
		return reinterpret_cast<OptiTrack*>(pUserData)->DataHandler(data);
	}

	static void NATNET_CALLCONV MessageHandler(Verbosity msgType, const char* msg);      // receives NatNet error messages
	void resetClient();
	int ConnectClient();

	ConnectionType kDefaultConnectionType;

	NatNetClient* g_pClient;
	FILE* g_outputFile;

	std::vector< sNatNetDiscoveredServer > g_discoveredServers;
	sNatNetClientConnectParams g_connectParams;
	char g_discoveredMulticastGroupAddr[kNatNetIpv4AddrStrLenMax];
	int g_analogSamplesPerMocapFrame;
	sServerDescription g_serverDescription;

	AppMsgPtr appMsg;

public:
	OptiTrack(AppMsgPtr _appMsg) :
		kDefaultConnectionType(ConnectionType_Multicast),
		g_pClient(NULL),
		g_discoveredMulticastGroupAddr(NATNET_DEFAULT_MULTICAST_ADDRESS),
		g_analogSamplesPerMocapFrame(0),
		appMsg(_appMsg)
	{}

	int run();

	// 作成したが、利用せず
	bool getRigidBodyIDByName(std::string rigidBodyName);
};

#endif //OPTITRACK_H