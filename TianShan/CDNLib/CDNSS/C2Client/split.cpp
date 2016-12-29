#include<string>
using namespace std;
namespace C2Streamer{
	void splitFileName(const std::string& pathname, std::string& pid, std::string& paid, std::string& ext)
	{
		std::string filename = pathname;
		size_t pos = filename.find_last_of('.');
		ext = "";
		if (std::string::npos != pos)
		{
			ext = filename.substr(pos + 1);
			if (0 != ext.compare("index") && std::string::npos == ext.find_first_of("XFRVC0123456789ABCDEF")) // make sure if it is the reserved extname
				ext = "";
			else filename = filename.substr(0, pos);
		}

		paid = filename;
		pid = "";
		pos = filename.find('_');
		if (std::string::npos != pos)
		{
			paid = filename.substr(0, pos);
			pid = filename.substr(pos + 1);
		}
		else if (filename.length() >20)
		{
			paid = filename.substr(0, 20);
			pid = filename.substr(20);
		}
	}
}//namespace C2Streamer
