// VV2Parser.cpp: implementation of the VV2Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "Log.h"
#include "VV2Parser.h"

#if !defined(NAS)
#include "vstrmuser.h"
#endif
#include <vsiolib.h>

#include <assert.h>


#define CRLF				"\r\n"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifndef NAS
HANDLE VV2Parser::_vstrmClass = INVALID_HANDLE_VALUE;
#endif

VV2Parser::VV2Parser()
{
//	_vstrmClass = INVALID_HANDLE_VALUE;
}

VV2Parser::~VV2Parser()
{

}

bool VV2Parser::parseFile(FILE* fp)
{
	if (fp == NULL)
		return false;

	char buf[1024];
	memset(buf, 0, 1024);
	
	bool result = false;
	do 
	{

		if (fgets(buf, sizeof(buf), fp) == NULL)
			break;
		if (strcmp(buf, "SOH"CRLF))
		 	break;

		if (fgets(buf, sizeof(buf), fp) == NULL)
			break;
		if (strcmp(buf, "DRIVERFLAVOR:TSOVERIP"CRLF))
			break;

		if (fgets(buf, sizeof(buf), fp) == NULL)
			break;
		if (strcmp(buf, "NO_EMBEDDED_HINTS"CRLF)){
			if(strcmp(buf, "INDXRECFMT:2"CRLF)){
				break;
			}
		}
		else{
			if (fgets(buf, sizeof(buf), fp) == NULL)
				break;
			if (strcmp(buf, "INDXRECFMT:3"CRLF))
				break;
		}

		// read FILE header
		int index;
		struct SubFileInfo subFileInfo;

		while (fgets(buf, sizeof(buf), fp)) {
			if (strncmp(buf, "FILE", 4))
				break;

			if (!readSubFileRecord(buf, subFileInfo, index)) {
				fclose(fp);
				return false;
			}

			_subFileInfoVec.push_back(subFileInfo);
		}

		if (!sscanf(buf, "BITRATE_HEX:0:%lX"CRLF, &_bitrate))
			break;

		while (fgets(buf, sizeof(buf), fp)) {
			if (strncmp(buf, "BITRATE_HEX", strlen("BITRATE_HEX")))
				break;
		}
		char szPlayTime[256];
		memset(szPlayTime,0,sizeof(szPlayTime));
		if (!sscanf(buf, "PLAYDURATIONMSECS_HEX:%s"CRLF, &szPlayTime))
			break;
		if( strcmp("TBD",szPlayTime) == 0 )
		{
			//Must pass the last line to get the play duration
			bool bGetPlaytime = false;
			while( fgets(buf,sizeof(buf),fp ) )
			{
				if(strncmp(buf,"EOD:PLAYDURATIONMSECS_HEX:",26)==0)
				{
					sscanf(buf,"EOD:PLAYDURATIONMSECS_HEX:%lX",&_playTime );
					bGetPlaytime = true;
					break;
				}
			}
			if(!bGetPlaytime)
				break;
		}
		else
		{
			sscanf( szPlayTime, "%lX", &_playTime );
		}

		result = true;
	} while(0);
	
	return result;
}

bool VV2Parser::parseFromNtfs(const char* fileName) {
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL)
		return false;

	bool result = parseFile(fp);
	fclose(fp);
	return result;
}

#ifndef NAS 
bool VV2Parser::vsmInit(HANDLE vstrmClass)
{
	_vstrmClass = vstrmClass;
	return true;
}

bool VV2Parser::parseFromVstrm(const char* fileName)
{
	VHANDLE fileHandle = INVALID_HANDLE_VALUE;
	OBJECT_ID tempId ;
	if( 1 )
	{
		VSTATUS ret = VsOpenEx( &fileHandle , (char*)fileName ,
								GENERIC_READ , FILE_SHARE_READ | FILE_SHARE_WRITE,
								OPEN_EXISTING,
								FILE_FLAG_CACHED,
								0,
								&tempId);
		if( !IS_VSTRM_SUCCESS(ret) )
		{
			return false;
		}
	}
	else
	{
		VHANDLE fileHandle = VstrmCreateFile(_vstrmClass, fileName, 
			GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, 
			OPEN_EXISTING, 0, 0);
		if (fileHandle == INVALID_HANDLE_VALUE){
			char msg[256] = {0};
			DWORD status = VstrmGetLastError();

			VstrmClassGetErrorText(_vstrmClass, status, msg, 255);

			glog(ZQ::common::Log::L_INFO, "(%s) VstrmCreateFile failed: (%s)", fileName, msg);

			return false;
		}
	}

	

	FILE* fp = tmpfile();
	if (fp == NULL)
	{
		if(1)
		{
			VsClose( fileHandle , tempId );
		}
		else
		{
			VstrmCloseHandle(_vstrmClass, fileHandle);
		}
		return false;
	}

	char buf[64*1024];
	unsigned long readSize;
	while (true)
	{
		if(1)
		{
			readSize = 0;
			if (!VsRead(  fileHandle, buf, sizeof(buf), &readSize , 0)) 
			{
				break;
			}
		}
		else
		{
			readSize = 0;
			if (!VstrmReadFile(_vstrmClass, fileHandle, buf, sizeof(buf), 
				&readSize, 0)) 
			{
					break;
			}
		}

		fwrite(buf, readSize, 1, fp);
	}
	fflush(fp);

	if(1)
	{
		VsClose( fileHandle , tempId );
	}
	else
	{
		VstrmCloseHandle(_vstrmClass, fileHandle);
	}

	fseek(fp, 0, 0); 
	bool result = parseFile(fp);
	fclose(fp);
	return result;
}
#endif

bool VV2Parser::parse(const char* fileName, bool fromNtfs /* = false */)
{
	if (fromNtfs)
		return parseFromNtfs(fileName);
	else {
#ifdef NAS 
		return false;
#else
		return parseFromVstrm(fileName);
#endif
	} 
}

static const char* skipWord(const char* lineBuf, const char* word)
{
	if (!strstr(lineBuf, word))
		return NULL;

	return lineBuf + strlen(word);
}

static size_t readWord(const char* lineBuf, char endChar, char* buf, size_t len)
{
	const char* c = lineBuf;
	while (*c && *c != endChar) {

		c ++;
	}

	size_t wordLen = c - lineBuf;
	if (wordLen > len)
		return 0;
	
	strncpy(buf, lineBuf, wordLen);
	buf[wordLen] = 0;
	return wordLen;
}

bool VV2Parser::readSubFileRecord(const char* linebuf, SubFileInfo& info, 
								  int& index)
{
	const char* c = skipWord(linebuf, "FILE:#");
	if (c == NULL)
		return false;

	char word[80];
	size_t wordLen = readWord(c, ':', word, sizeof(word));

	strncpy(info.ext, word, std::min<size_t>(sizeof(info.ext), strlen(word)));
	info.ext[strlen(word)] = 0;
	c += wordLen + 1;

	wordLen = readWord(c, ':', word, sizeof(word));
	if (!wordLen)
		return false;
	sscanf(word, "%X", &index);
	c += wordLen + 1;

	wordLen = readWord(c, ':', word, sizeof(word));
	if (!wordLen)
		return false;
	sscanf(word, "%lX", &info.numerator);
	c += wordLen + 1;

	wordLen = readWord(c, ':', word, sizeof(word));
	if (!wordLen)
		return false;
	sscanf(word, "%lX", &info.denominator);
	c += wordLen + 1;

	wordLen = readWord(c, ':', word, sizeof(word));
	if (!wordLen)
		return false;
	if (strncmp(word, "F", 1) == 0)
		info.direction = 1;
	else
		info.direction = -1;

	return true;
}

#ifdef _DEBUG

#if defined(ZQ_OS_MSWIN)
extern "C" void test()
{
	VV2Parser vv2Parser;
	vv2Parser.parse(__argv[1]);
}
#endif

#endif
