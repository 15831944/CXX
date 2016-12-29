#include "stdafx.h"
#include "ClientSockets.h"
#include <iostream>
#include "TianShanDefines.h"

#define  Char2Byte(x) ((x>='a')?(x-'a'+10):(x-'0'))

void HexToByte(const char* szHex, int hexLength, char* pbBuf)
{
	if(!szHex) 
		return;
	if (hexLength<=0 || 0!=hexLength%2) 
		return;
	for (int i=0;i<hexLength/2;i++)
	{
		int tmp1 =  (int)(szHex[i*2]);
		tmp1 = Char2Byte(tmp1);
		if(tmp1>=16) 
			return;
		int tmp2 = (int)szHex[i*2+1];
		tmp2 = Char2Byte(tmp2);
		if(tmp2>=16)
			return;
		pbBuf[i] = (tmp1*16+tmp2);
	}
}

void ClientDialogFactory::onClose( CommunicatorS& comms )
{
	
}

ZQ::DataPostHouse::IDataDialogPtr ClientDialogFactory::onCreateDataDialog( ZQ::DataPostHouse::IDataCommunicatorPtr communicator ) 
{	
	return new ClientDialog(mThPool,mLog);
}

void ClientDialogFactory::onReleaseDataDialog( ZQ::DataPostHouse::IDataDialogPtr dialog , ZQ::DataPostHouse::IDataCommunicatorPtr communicator ) 
{
	
}

bool	ClientSockets::start( int recvThPoolSize , int socketsCount ,uint64 interval )
{
	if(!mDak)
	{
		delete mDak;
		mDak = 0;
	}
	mDialogFactoryPtr = new ClientDialogFactory(mThPool,mLog);
	mDakEnv.mLogger = &mLog;
	mDakEnv.dataFactory = mDialogFactoryPtr;

	mDak = new ZQ::DataPostHouse::DataPostDak(mDakEnv,mDialogFactoryPtr);
	mDak->startDak(recvThPoolSize);

	for(int i = 0;i < socketsCount;i++)
	{
		ZQ::DataPostHouse::AClientSocketTcp* client = new ZQ::DataPostHouse::AClientSocketTcp(*mDak,mDakEnv,mDialogFactoryPtr);
		mClientSockets.push_back(client);
		char port[256] = "";
		memset(port,0,sizeof(port));
		itoa(mClientSocketInfo._remotePort,port,10);
		if(!client->connectTo(mClientSocketInfo._remoteIp,port))
		{
			glog(ZQ::common::Log::L_ERROR,CLOGFMT(ClientSockets,"bad server"));
			return 0;
		}
		client->addToDak();
		Sleep(interval);
	}
	
	return true;
}

bool    ClientSockets::setSocketPara(std::string remoteIP,int remotePort)
{
	if(remoteIP.length() == 0 ||  remotePort == 0)
		return false;
	mClientSocketInfo._remoteIp = remoteIP;
	mClientSocketInfo._remotePort = remotePort;

	return true;
}

char* openMsg = (char*)malloc(4096);
char* updateMsg = (char*)malloc(4096);
char* keepAliveMsg  = (char*)malloc(10);
int openMsgSize = 0;
int updateMsgSize = 0;
int keepAliveMsgSize = 0;

ClientSockets::~ClientSockets(void)
{
	delete openMsg;
	delete updateMsg;
	delete keepAliveMsg;
}

extern void show(uint8* buf,uint16 size);

bool	ClientSockets::createMsg(uint16 holdTime)
{
	FILE* streamOpen = fopen("openMsg.txt","r");
	FILE* streamUpdate = fopen("updateMsg.txt","r");
	FILE* streamKeepAlive = fopen("keepAliveMsg.txt","r");

	if(!streamOpen || !streamUpdate || !streamKeepAlive)
	{
		printf("[ClientSockets::readMsgFromFile]	open message failed\n");
		return false;
	}
	size_t fileSize = 0;
	size_t ret = 0;

	/*
	//create open request
	ZQ::ERRP::StringMap metadata;
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_MsgType,"1");
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenVersion,"1");
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenReserved,"0");
	char buf[25];
	memset(buf,0,sizeof(buf));
	itoa(holdTime,buf,10);
	std::string strHoldTime(buf);
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenHoldTime,strHoldTime);
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenAdddressDomain,"0");
	std::string errpId = "1921688199";

	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenErrpIdentifier,errpId);

	std::string streamingZone = "zone.local";
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenStreamingZone,streamingZone);
	std::string componentName = "absdas";
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpencomponetName,componentName);

	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenCapabilityCode,"1");
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenAddressFamiliy,"32769");
	MAPSET(ZQ::ERRP::StringMap,metadata,ERRPMD_OpenAppProtocol,"32766");

	ZQ::ERRP::ERRPMsg::HardHeader head;
	ZQ::ERRP::ERRPMsg::Ptr pMsg = new ZQ::ERRP::OpenRequest(head);
	pMsg->readMetaData(metadata);
	openMsgSize = pMsg->toMessage((uint8*)openMsg,4096);
	if(!openMsgSize)
	{
		printf("create open request message failed\n");
		return 0;
	}
	*/

	//read open message
	fseek(streamOpen,0,SEEK_END);
	openMsgSize = ftell(streamOpen);
	fseek(streamOpen,0,SEEK_SET);
	char temp[4096] = {0};
	ret = fread(temp,1,openMsgSize,streamOpen);

	if(ret != openMsgSize)
	{
		printf("[ClientSockets::readMsgFromFile]   fread open message failed\n");
		return false;
	}

	HexToByte(temp,openMsgSize,openMsg);
	openMsgSize = openMsgSize/2;

	//read update message
	fseek(streamUpdate,0,SEEK_END);
	updateMsgSize = ftell(streamUpdate);
	fseek(streamUpdate,0,SEEK_SET);
	memset(temp,0,sizeof(temp));
	ret = fread(temp,1,updateMsgSize,streamUpdate);
	if(ret != updateMsgSize)
	{
		printf("[ClientSockets::readMsgFromFile]	fread update message failed\n");
		return false;
	}

	HexToByte(temp,updateMsgSize,updateMsg);
	updateMsgSize = updateMsgSize/2;

	//read keepAlive message
	fseek(streamKeepAlive,0,SEEK_END);
	keepAliveMsgSize = ftell(streamKeepAlive);
	fseek(streamKeepAlive,0,SEEK_SET);
	memset(temp,0,sizeof(temp));
	ret = fread(temp,1,keepAliveMsgSize,streamKeepAlive);
	if(ret != keepAliveMsgSize)
	{
		printf("[ClientSockets::readMsgFromFile]	fread keepAlive message failed\n");
		return false;
	}

	HexToByte(temp,keepAliveMsgSize,keepAliveMsg);
	keepAliveMsgSize = keepAliveMsgSize/2;

	fclose(streamOpen);
	fclose(streamUpdate);
	fclose(streamKeepAlive);

	return true;
}

void	ClientSockets::stop()
{
	glog(ZQ::common::Log::L_INFO,CLOGFMT(ClientSockets,"stop clientSockets"));
#ifdef _DEBUG
	printf("stop clientSockets\n");
#endif
	if(mDialogFactoryPtr)
		mDialogFactoryPtr->close();
	if(mDak)
		mDak->stopDak();
	
	//ClientDialog::stopHeartbeat();
	std::list<ZQ::DataPostHouse::AClientSocketTcpPtr>::iterator iter = mClientSockets.begin();
	for(iter;iter != mClientSockets.end();iter++)
	{
		if(*iter)
			(*iter)->close();
	}
}

