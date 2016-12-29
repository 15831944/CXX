// JmsMsgSender.cpp: implementation of the JmsMsgSender class.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#pragma warning(disable : 4018)
#include "JmsMsgSender.h"
#include "Log.h"


#define LOG_MODULE_NAME			"JmsMsgSender"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma comment(lib,"jmsc.lib")

#ifdef _DEBUG
#	pragma comment(lib,"jmscpp_d.lib")
#else
#	pragma comment(lib,"jmscpp.lib")
#endif

using namespace ZQ::common;
using namespace ZQ::JMSCpp;



JmsMsgSender::JmsMsgSender()
{
	m_pJmsContext=NULL;
	m_bJmsInitializeOK=false;
	m_bConnectionOK=false;
	m_iNoneSendMsgFlushCount=1000;
	ZeroMemory(&m_MsgOption,sizeof(ProducerOptions));
	m_lConnectionLostTime=0;
}

JmsMsgSender::~JmsMsgSender()
{

}


void JmsMsgSender::SetLastLostTime(long lTime)
{
	m_lConnectionLostTime=lTime;
}

bool JmsMsgSender::init(InitInfo& initInfo)
{
	m_strNamingContext = initInfo.strNamingCtx;
	m_iReconnectCount = initInfo.nReConnectCount;
	m_strDestinationName = initInfo.strDestName;		
	m_strConnectionFactory = initInfo.strConnFactory;
	m_strServerAddress = initInfo.strSrvIpPort;
	m_strMsgStoreFile = initInfo.strSafestoreFile;
	m_iReconnectInterval = initInfo.nReConnectInterval;
	m_iNoneSendMsgFlushCount = initInfo.nFlushToFileCount;

	if (!m_iReconnectCount)
	{
		glog(Log::L_DEBUG, "set ReconnectCount to default 5");
		m_iReconnectCount=5;
	}

	//Get re-connect interval
	if(!m_iReconnectInterval)
	{
		glog(Log::L_DEBUG, "set ReconnectInterval to default 10*1000 ms");
		m_iReconnectInterval=10*1000;
	}
	
	//Get storage file path
	if(m_strMsgStoreFile.empty())
	{
		glog(Log::L_DEBUG,  "set SafestoreFile to default c:\\storageFile.txt");
		m_strMsgStoreFile="c:\\storageFile.txt";
	}
	
	//Get flush count
	if(!m_iNoneSendMsgFlushCount)
	{
		glog(Log::L_DEBUG,  "set NoneSendMsgFlushCount to default 100");
		m_iNoneSendMsgFlushCount=100;

	}

	//get keep alive time
	m_MsgOption.flags=PO_TIMETOLIVE;
	m_MsgOption.timeToLive = initInfo.nKeepAliveTime;

	if (!InitializeJMS())
	{
		glog(Log::L_DEBUG,"JMS init failed");
		return false;
	}

	glog(Log::L_DEBUG,"JMS init successfully");
	
	return true;
}

void JmsMsgSender::UnInitializeJMS()
{
	if(m_pJmsContext)
	{
		if(m_bConnectionOK)
			m_JmsConnection.stop();
		delete m_pJmsContext;
		m_pJmsContext=NULL;
	}
}

bool JmsMsgSender::InitializeJMS()
{
	if(m_pJmsContext)
	{//if the m_pJmsContext is initialized,destroy it
		delete m_pJmsContext;
		m_pJmsContext=NULL;
	}
	glog(Log::L_DEBUG,"BOOL JmsMsgSender::InitializeJMS():: before Create Context with Server Address =%s  and NamingContext=%s",m_strServerAddress.c_str(),m_strNamingContext.c_str());
	m_pJmsContext=new Context(m_strServerAddress.c_str(),m_strNamingContext.c_str());
	if(!m_pJmsContext )
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::InitilizeJMS()::can't initialize JmsContext with server address is %s and server namingContext is %s and ErrCode is %d",m_strServerAddress.c_str(),m_strNamingContext.c_str(),getLastJmsError());
		return false;
	}
	glog(Log::L_DEBUG,"BOOL JmsMsgSender::InitializeJMS():: after Create Context with Server Address =%s  and NamingContext=%s",m_strServerAddress.c_str(),m_strNamingContext.c_str());

	if( !m_pJmsContext->_context)
	{
		if(m_pJmsContext)
		{
			delete m_pJmsContext;
			m_pJmsContext=NULL;
		}
		glog(Log::L_ERROR,"BOOL JmsMsgSender::InitilizeJMS()::can't initialize JmsContext with server address is %s and server namingContext is %s",m_strServerAddress.c_str(),m_strNamingContext.c_str());
		return false;
	}
	m_bJmsInitializeOK=true;
	glog(Log::L_DEBUG,"BOOL JmsMsgSender::InitializeJMS():: Create Context succesfully  with Server Address =%s  and NamingContext=%s",m_strServerAddress.c_str(),m_strNamingContext.c_str());

	return true;
}

bool JmsMsgSender::ClearConnInstance()
{
	ZQ::common::MutexGuard gd(m_sendMutex);
	m_JmsTxtMessage.DestroyMessage();
	m_JmsProducer.close();
	m_JmsDestination.destroy();
	m_JmsSession.close();
	m_JmsConnection.close();
	m_JmsCNFactory.Destroy();
	
	return true;
}

bool JmsMsgSender::ConnectToServer()
{
	glog(Log::L_DEBUG,"BOOL JmsMsgSender::ConnetToHost()::Begin to connect to server");

	//Create connection factory
	ClearConnInstance();
	glog(Log::L_DEBUG,"ConnectToServer():create connectionFactory with string =%s",m_strConnectionFactory.c_str());
	if(!m_pJmsContext->createConnectionFactory(m_strConnectionFactory.c_str(),m_JmsCNFactory))
	{		
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::can't create connnectionfactory with factory=%s And errCode=%d","ConnectionFactory",getLastJmsError());
		return false;
	}

	//create connection	
	if(!m_JmsCNFactory.createConnection(m_JmsConnection))
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::Can't create connection using JMSConnectionFactory and ErrCode=%d",getLastJmsError());
		return false;
	}
	
	m_JmsConnection.SetConnectionCallback(ConnectionMonitor,this);
	
	if(!m_JmsConnection.createSession(m_JmsSession))
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::Can't create session using JMSConnection and ErrCode=%d",getLastJmsError());
		return false;
	}

	glog(Log::L_DEBUG,"ConnectToServer():Create destination with string=%s",m_strDestinationName.c_str());
	if(!m_pJmsContext->createDestination(m_strDestinationName.c_str(),m_JmsDestination))
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::Can't create Destination with destinaition name=%s and ErrCode=%d",m_strDestinationName.c_str(),getLastJmsError());
		return false;
	}

	
	if(!m_JmsSession.createProducer(&m_JmsDestination,m_JmsProducer))
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::Can't create producer using JMS destination and ErrCode=%d",getLastJmsError());
		return false;
	}

	if(!m_JmsConnection.start())
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::JMSCOnnection start fail and errCode=%d",getLastJmsError());
		return false;
	}
	
	if(!m_JmsSession.textMessageCreate("",m_JmsTxtMessage))
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::Create text message fail and ErrCode=%d",getLastJmsError());
		return false;
	}
	if(!CreateMessageProperty())
	{
		glog(Log::L_ERROR,"BOOL JmsMsgSender::ConnetToHost()::## Can't create message property");
		return false;
	}
	//evrything is ok set connection status to TRUE
	SetConnectionStatus(true);

	glog(Log::L_DEBUG,"BOOL JmsMsgSender::ConnetToHost()::End to connect to server  and everything is OK");

	return true;
}

bool JmsMsgSender::CreateMessageProperty()
{
	if(NULL==m_JmsTxtMessage._message)
	{
		glog(Log::L_ERROR,"bool JmsMsgSender::CreateMessageProperty()## text message instance is not availble");
		return false;
	}

	//propertys in string
	m_strMsgPropery = "string,MESSAGECLASS,NOTIFICATION;int,MESSAGECODE,1101";
	::std::vector<std::string> strTypes, strKeys, strValues;
	int iPropertyCount = 0;
	{
		// parse the string to the vectors
		strTypes.push_back("string");
		strTypes.push_back("int");
		strKeys.push_back("MESSAGECLASS");
		strKeys.push_back("MESSAGECODE");
		strValues.push_back("NOTIFICATION");
		strValues.push_back("1101");
	}
	iPropertyCount = 2;

	glog(Log::L_DEBUG,"bool JmsMsgSender::CreateMessageProperty()## There are %d properties",iPropertyCount);

	for(int i=0;i<iPropertyCount;i++)
	{
		std::string		strKey = strKeys[i];
		std::string		strType = strTypes[i];
		
		if(0==stricmp("int",strType.c_str()))
		{	
			int				iValue = atoi(strValues[i].c_str());
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%d",strKey.c_str(),iValue);
			m_JmsTxtMessage.setIntProperty((char*)strKey.c_str(),iValue);
		}
		else if(0==stricmp("long",strType.c_str()))
		{
			long			lValue = atoi(strValues[i].c_str());
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%d",strKey.c_str(),lValue);
			m_JmsTxtMessage.setLongProperty((char*)strKey.c_str(),lValue);
		}
		else if(0==stricmp("double",strType.c_str()))
		{
			double			dValue=0;
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%lf",strKey.c_str(),dValue);
			m_JmsTxtMessage.setDoubleProperty((char*)strKey.c_str(),dValue);
		}
		else if(0==stricmp("float",strType.c_str()))
		{
			float			fValue=0.0f;
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%f",strKey.c_str(),fValue);
			m_JmsTxtMessage.setFloatProperty((char*)strKey.c_str(),fValue);
		}
		else if(0==stricmp("bool",strType.c_str()))
		{
			bool			bValue=false;
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%d",strKey.c_str(),bValue);
			m_JmsTxtMessage.setBoolProperty((char*)strKey.c_str(),bValue);
		}
		else if(0==stricmp("byte",strType.c_str()))
		{
			unsigned char			byValue = atoi(strValues[i].c_str());
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%d",strKey.c_str(),byValue);
			m_JmsTxtMessage.setByteProperty((char*)strKey.c_str(),byValue);
		}
		else if(0==stricmp("short",strType.c_str()))
		{
			short			sValue = atoi(strValues[i].c_str());
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%d",strKey.c_str(),sValue);
			m_JmsTxtMessage.setShortProperty((char*)strKey.c_str(),sValue);
		}
		else if(0==stricmp("string",strType.c_str()))
		{
			std::string		strValue = strValues[i].c_str();
			glog(Log::L_DEBUG,"Set Message Property with name=%s value=%s",strKey.c_str(),strValue.c_str());
			m_JmsTxtMessage.setStringProperty((char*)strKey.c_str(),(char*)strValue.c_str());
		}
		else 
		{
			glog(Log::L_ERROR,"None support type %s",strType.c_str());
			return false;
		}
	}
	return true;
}

void JmsMsgSender::ConnectionMonitor(int errType,VOID* lpData)
{
	glog(Log::L_ERROR,"VOID JmsMsgSender::ConnectionMonitor()##Some exception was thowed out,Maybe network issue!");
	switch(errType)
	{
	case 0:
	case ISA_JAVA_EXCEPTION:
		{
			JmsMsgSender* pThis=(JmsMsgSender*)lpData;	
			if(pThis)
			{
				pThis->SetConnectionStatus(false);					
				pThis->ClearConnInstance();
				pThis->SetLastLostTime(GetTickCount());	
			}
		}
		break;
	default:
		{
			glog(Log::L_DEBUG,"void JmsMsgSender::ConnectionMonitor()##Not a Java Exception with type = %d",errType);
		}
	}
	
}

// send all none-sent message, true for all none-sent message sent, false for stil exist none-sent message
bool JmsMsgSender::SendAllMsg()
{
	if(!m_bJmsInitializeOK)
	{
		if(!InitializeJMS())
		{			
			return false;
		}
	}

	if(!m_bConnectionOK)
	{
		glog(Log::L_DEBUG,"JmsMsgSender::OnMessage()##Connection is NOT available, reconnect to server");
		SetLastLostTime(GetTickCount());
		ConnectToServer();	

		if(!m_bConnectionOK)
		{		
			return false;
		}
	}
	

	//check if there is any none send message
	while(HasNoneSendMessage())
	{
		std::string		strMsg=PopNoneSendMessage();
		if(!InternalSendMessage(strMsg))
		{
			glog(Log::L_DEBUG,"Push Message head after get none message and send fail::%s",strMsg.c_str());
			PushNoneSendMessage(strMsg,true);
			break;
		}			
	}

	return !(HasNoneSendMessage());
}

void JmsMsgSender::SendMsg(const std::string& strMsg)
{	
	if(!m_bJmsInitializeOK)
	{
		if(!InitializeJMS())
		{
			glog(Log::L_DEBUG,"Push Message tail because JMS initliaze fail::%s",strMsg.c_str());
			
			PushNoneSendMessage(strMsg,false);
			return;
		}
	}
	if(!m_bConnectionOK)
	{
		long test=GetTickCount();
		if(m_lConnectionLostTime!=0&&(test-m_lConnectionLostTime<m_iReconnectInterval))
		{
			glog(Log::L_DEBUG,"Do not need to re-connect to server");
		}
		else
		{
			glog(Log::L_DEBUG,"JmsMsgSender::OnMessage()##Connection is NOT available.reconnect to server");
			//re-connect to server
			int		i=0;
			while(i++<m_iReconnectCount && !m_bConnectionOK)
			{	
				SetLastLostTime(GetTickCount());
				if(ConnectToServer())
					break;				
			}
		}
	}
	
	if(!m_bConnectionOK)
	{
		glog(Log::L_DEBUG,"Push message head because connection is NOT OK::%s",strMsg.c_str());
		PushNoneSendMessage(strMsg,false);
		return ;
	}
	else
	{
		//check if there is any none send message
		while(HasNoneSendMessage())
		{
			std::string		strMsg=PopNoneSendMessage();
			if(!InternalSendMessage(strMsg))
			{
				glog(Log::L_DEBUG,"Push Message head after get none message and send fail::%s",strMsg.c_str());
				PushNoneSendMessage(strMsg,true);
				break;
			}			
		}

		if(!m_bConnectionOK)
		{
			glog(Log::L_ERROR,"void JmsMsgSender::OnMessage()## connection is not available");
			glog(Log::L_DEBUG,"Push message tail when send message and connection is not OK::%s",strMsg.c_str());
			PushNoneSendMessage(strMsg,false);
			return;
		}
		if(!InternalSendMessage(strMsg))
		{
			glog(Log::L_ERROR,"void JmsMsgSender::OnMessage()## can't send the message,So push it into none send message queue");
			glog(Log::L_DEBUG,"Push message tail because internal send fail::%s",strMsg.c_str());
			PushNoneSendMessage(strMsg,false);
			return;
		}		
	}
}
bool JmsMsgSender::HasNoneSendMessage()
{
	bool	bOK=false;
	if(m_vNoneSendMessageHeader.size()>0)
	{
		return true;
	}
	if(HasNoneSendMessageInFile())
	{
		//把文件中的内容读入head
		HANDLE hFile = CreateFileA(m_strMsgStoreFile.c_str(),
									GENERIC_READ,
									FILE_SHARE_READ,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
		if (INVALID_HANDLE_VALUE==hFile)
		{
			glog(Log::L_DEBUG, "bool JmsMsgSender::HasNoneSendMessage()##Fail to open file %s",m_strMsgStoreFile.c_str());			
		}
		else
		{			
#define		BUF_SIZE	4097
			char	szBuf[BUF_SIZE];			
			do 
			{
				ZeroMemory(szBuf,BUF_SIZE);
				unsigned long	dwReadSize=0;
				int		pos=0;
				if(!ReadFile(hFile,szBuf,BUF_SIZE-1,&dwReadSize,NULL))
					break;
				if(dwReadSize<=0)
					break;
				char*	pLine=NULL;
				int		iSkipped;
				char	*pbuf=szBuf;
				while ((iSkipped=GetLineLogContent(pbuf,&pLine))>0)
				{
					pbuf=pbuf+iSkipped;
					pos+=iSkipped;
					std::string		str=pLine;
					m_vNoneSendMessageHeader.push_back(str);
				}
				if(pos<dwReadSize-1)
					SetFilePointer(hFile,pos-dwReadSize-1,0,FILE_CURRENT);
				if(m_vNoneSendMessageHeader.size()>m_iNoneSendMsgFlushCount/2)	
					break;
			} while(1);
			
			long	crntPos=SetFilePointer(hFile,0,0,FILE_CURRENT);
			CloseHandle(hFile);
			if(!DeleteLogContent(crntPos,true))
			{
				glog(Log::L_ERROR,"bool JmsMsgSender::HasNoneSendMessage()##Delete read log fail");				
			}
			return true;
#undef		BUF_SIZE
		}
	}
	if(m_vNoneSendMessageTail.size()>0)
	{
		while(m_vNoneSendMessageTail.size()>0)
		{
			m_vNoneSendMessageHeader.push_front(m_vNoneSendMessageTail[m_vNoneSendMessageTail.size()-1]);
			m_vNoneSendMessageTail.pop_back();
		}
		return true;
	}
	return false;
}
int  JmsMsgSender::GetLineLogContent(char* buf, char** pline)
{
	if (buf == NULL)
		return 0;
	
	*pline = buf;
	bool bValidLine = false;
	
	while (**pline == '\r' || **pline =='\n')
		(*pline)++;
	
	char* q = *pline;
	while (*q != '\r' && *q!= '\n' && *q!='\0')
		q++;
	
	while (*q == '\r' || *q == '\n')
	{
		*q++ = '\0';
		bValidLine = true;
	}
	
	if (bValidLine)
		return (q - buf); // found a valid line
	
	// this is a in-completed line
	int stepped = *pline - buf;
	*pline = NULL;
	return stepped;
}
bool JmsMsgSender::HasNoneSendMessageInFile()
{
	HANDLE hFile = CreateFileA(m_strMsgStoreFile.c_str(),
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	
	if (INVALID_HANDLE_VALUE==hFile)
	{		
		return false;
	}
	else
	{
		long	pos=SetFilePointer(hFile,0,0,FILE_END);
		CloseHandle(hFile);
		if(pos>0)
			return true;
		else 
			return false;			 
	}	
}
std::string	JmsMsgSender::PopNoneSendMessage()
{
	if(!HasNoneSendMessage())
		return NULL;
	std::string		str=m_vNoneSendMessageHeader.front();
	m_vNoneSendMessageHeader.pop_front();
	return str;
}
void	JmsMsgSender::PushNoneSendMessage(const std::string& strMsg,bool bHead)
{
	if(bHead)
		m_vNoneSendMessageHeader.push_front(strMsg);
	else
		m_vNoneSendMessageTail.push_back(strMsg);
	if(m_vNoneSendMessageHeader.size()>m_iNoneSendMsgFlushCount)
	{
		AddLogContent(m_vNoneSendMessageHeader,true);
	}
	if(m_vNoneSendMessageTail.size()>m_iNoneSendMsgFlushCount)
	{
		AddLogContent(m_vNoneSendMessageTail,false);
	}
}
bool JmsMsgSender::InternalSendMessage(std::string strMsg)
{
	ZQ::common::MutexGuard gd(m_sendMutex);
	if(m_JmsTxtMessage._message==NULL)
	{
		//should I set the m_bConnectionOK to false because the instance is not available????
		glog(Log::L_CRIT,"JmsMsgSender::InternalSendMessage():text message instance is not available");
		return false;
	}
	if(!m_JmsTxtMessage.setText((char*)strMsg.c_str()))
	{
		glog(Log::L_CRIT,"JmsMsgSender::InternalSendMessage():Can NOT set text for a jms message with text content =%s",strMsg.c_str());
		return false;
	}
	if(!m_bConnectionOK)
	{
		glog(Log::L_ERROR,"JmsMsgSender::InternalSendMessage()##connection lost.");
		return false;
	}	
	if(!m_JmsProducer.send(&m_JmsTxtMessage,&m_MsgOption))
	{
		glog(Log::L_ERROR,"JmsMsgSender::InternalSendMessage():can't send message");		
		return false;				
	}
	glog(Log::L_DEBUG,"Send the message OK::%s",strMsg.c_str());
	return true;
}
void JmsMsgSender::close()
{
	glog(Log::L_DEBUG,"void JmsMsgSender::close()##Server closed,reserve none send message for next use");
	AddLogContent(m_vNoneSendMessageHeader,true);
	AddLogContent(m_vNoneSendMessageTail,false);
	UnInitializeJMS();
}

bool JmsMsgSender::AddLogContent(std::deque<std::string>& vContent,bool bFront)
{
	HANDLE hFile = CreateFileA(m_strMsgStoreFile.c_str(),
								GENERIC_READ|GENERIC_WRITE,
								0,
								NULL,
								OPEN_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		glog(Log::L_DEBUG,"bool JmsMsgSender::AddLogContent()## can't open file %s",m_strMsgStoreFile.c_str());
		return false;
	}
	//Test	
	if(!bFront)	
	{//add to tail		
	
		SetFilePointer(hFile,0,0,FILE_END);
		unsigned long	lWrite=0;
		while (vContent.size()>0)
		{
			char	szTemp[2]="\r";			
			WriteFile(hFile,vContent.front().c_str(),vContent.front().size(),&lWrite,NULL);
			WriteFile(hFile,szTemp,strlen(szTemp),&lWrite,NULL);
			vContent.pop_front();
		}
		CloseHandle(hFile);
		return true;
	}
	else
	{
		std::string		strNewFile=m_strMsgStoreFile;
		strNewFile+='a';
		HANDLE	hNewFile=CreateFileA(strNewFile.c_str(),
										GENERIC_WRITE|GENERIC_READ,
										0,
										NULL,
										OPEN_ALWAYS,
										FILE_ATTRIBUTE_NORMAL,NULL);
		if(hNewFile==INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			glog(Log::L_ERROR,"bool JmsMsgSender::AddLogContent()## can't open temp file %s",strNewFile.c_str());
			return false;
		}
		SetFilePointer(hNewFile,0,0,FILE_BEGIN);
		SetEndOfFile(hNewFile);
		unsigned long lWrite=0;
		while (vContent.size()>0)
		{
			char	szTemp[2]="\r";
			WriteFile(hNewFile,vContent.front().c_str(),vContent.front().size(),&lWrite,NULL);
			WriteFile(hNewFile,szTemp,strlen(szTemp),&lWrite,NULL);
			vContent.pop_front();
		}
		long pos=SetFilePointer(hNewFile,0,0,FILE_CURRENT);
		if(!CopyFileContent(hFile,0,hNewFile,pos))
		{
			CloseHandle(hNewFile);
			CloseHandle(hFile);
			glog(Log::L_ERROR,"bool JmsMsgSender::AddLogContent()## copy file content fail");
			return false;
		}
		CloseHandle(hNewFile);
		CloseHandle(hFile);
		DeleteFileA(m_strMsgStoreFile.c_str());
		if(0!=rename(strNewFile.c_str(),m_strMsgStoreFile.c_str()))
		{
			glog(Log::L_ERROR,"bool JmsMsgSender::AddLogContent()## rename from %s to %s fail and errno=%d",strNewFile.c_str(),m_strMsgStoreFile.c_str(),errno);
			return false;
		}

		return true;
	}
}
bool JmsMsgSender::DeleteLogContent(long pos,bool bFront)
{
	HANDLE hFile = CreateFileA(m_strMsgStoreFile.c_str(),
								GENERIC_READ,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		glog(Log::L_DEBUG,"bool JmsMsgSender::DeleteLogContent()## can't open file %s",m_strMsgStoreFile.c_str());
		return false;
	}
	//create a temp file
	std::string	strNewFile=m_strMsgStoreFile;
	strNewFile+='a';
	HANDLE hNewFile = CreateFileA(strNewFile.c_str(),
									GENERIC_WRITE,
									FILE_SHARE_READ,
									NULL,
									OPEN_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
	if(hNewFile==INVALID_HANDLE_VALUE)
	{
		glog(Log::L_ERROR,"bool JmsMsgSender::DeleteLogContent()## can't open file %s",strNewFile.c_str());
		return false;
	}
	SetFilePointer(hNewFile,0,0,FILE_BEGIN);
	SetEndOfFile(hNewFile);
	if(bFront)
	{
		if(!CopyFileContent(hFile,pos,hNewFile,0))
		{
			CloseHandle(hFile);
			CloseHandle(hNewFile);

			glog(Log::L_ERROR,"bool JmsMsgSender::DeleteLogContent()## copy file content fail");
			return false;
		}
		CloseHandle(hFile);
		CloseHandle(hNewFile);

		DeleteFileA(m_strMsgStoreFile.c_str());
		if(0!=rename(strNewFile.c_str(),m_strMsgStoreFile.c_str()))
		{
			glog(Log::L_ERROR,"bool JmsMsgSender::DeleteLogContent()##rename from %s to %s fail and errno=%d",strNewFile.c_str(),m_strMsgStoreFile.c_str(),errno);
			return false;
		}
	}
	else
	{
		SetFilePointer(hFile,pos,0,FILE_BEGIN);
		SetEndOfFile(hFile);
		CloseHandle(hFile);
		CloseHandle(hNewFile);
	}
	return true;
}
bool JmsMsgSender::CopyFileContent(HANDLE hSrc,long posSrc,HANDLE hDst,long posDst)
{
	if(hSrc==INVALID_HANDLE_VALUE||hDst==INVALID_HANDLE_VALUE)
	{
		glog(Log::L_ERROR,"bool JmsMsgSender::CopyFileContent()## invalid handle pass in");
		return false;
	}
	SetFilePointer(hSrc,posSrc,0,FILE_BEGIN);
	SetFilePointer(hDst,posDst,0,FILE_BEGIN);

#define		BUF_SIZE	4097
	char	szBuf[BUF_SIZE];
	unsigned long	lRead=0;
	unsigned long	lWrite=0;
	do 
	{
		try
		{		
			if(!ReadFile(hSrc,szBuf,BUF_SIZE-1,&lRead,NULL))
			{
				glog(Log::L_ERROR,"bool JmsMsgSender::CopyFileContent()## read file content fail");
				return false;
			}
			if(!WriteFile(hDst,szBuf,lRead,&lWrite,NULL))
			{
				glog(Log::L_ERROR,"bool JmsMsgSender::CopyFileContent()## write file content fail");
				return false;
			}
		}
		catch (...)  
		{			
			glog(Log::L_DEBUG,"bool JmsMsgSender::CopyFileContent()## Exception was threw out and error code=%d",GetLastError());
		}
	} while(lRead==BUF_SIZE-1);
#undef		BUF_SIZE
	return true;

}