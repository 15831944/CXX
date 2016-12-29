#include <string>
#include <iostream>
#include <FileLog.h>

#pragma comment(lib, "Ws2_32.lib")

ZQ::common::FileLog g_log("testC2.log", ZQ::common::Log::L_DEBUG);

int main(int argc, char **argv)
{
    /*const std::string filename = "CDNTEST1234567892001xor.com.index";
    const int bufSize = 1024*1024*2;
    const int bufNum  = 1;
    const int sendNum = 71;
    const int skipNum = 1;
    uint64 offset = bufSize * skipNum;
    
    std::vector<C2Streamer::Buffer*> bufs;
    TestC2Request::Ptr testC2Ptr = new TestC2Request(g_log);

    ZQ::StreamService::RequestParams params;
    params.locateIP = "10.15.10.74";
    params.locatePort = 10080;
    params.url = "/vodadi.cgi";
    params.upstreamIP = "192.168.81.107";
    params.clientTransfer = "192.168.81.107";
    params.defaultGetPort = 12000;
    params.transferRate = "3750000";

    params.waitBufferTime = 10000;
    params.indexTimeout = 500;
    params.indexRetryTimes = 0;
    params.mainfileTimeout = 2000;
    params.mainfileRetryTimes = 0;
    params.transferDelete = true;

    params.contentName = "";
    params.subType = "";*/


    //ZQ::StreamService::ReadClient::Ptr = new ZQ::StreamService::ReadClient(testC2Ptr.get(), g_log, )

    return 0;
}