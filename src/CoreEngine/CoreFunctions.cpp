#include "CoreFunctions.h"

GLenum CoreFunctions::PixelFormatToTextureFormat(SDL_PixelFormat * PixelFormat)
{
	if (PixelFormat->BytesPerPixel == 4)
	{
		if (PixelFormat->Rmask == 0x000000ff)
			return GL_RGBA;
		else
			return GL_BGRA;
	}
	else if (PixelFormat->BytesPerPixel == 3)
	{
		if (PixelFormat->Rmask == 0x000000ff)
			return GL_RGB;
		else
			return GL_BGR;
	}
	return NULL;
}

int CoreFunctions::Round(double rnd)
{
	return (int)(rnd + 0.5);
}

int CoreFunctions::NextPowerOf2(int val)
{
	double logbase2 = (double)log((double)val) / (double)log((double)2);
	return Round(pow(2,ceil(logbase2)));
}

string CoreFunctions::addIntToString(string mainString, int num) {
	string returnString;
	string intString;
	returnString = mainString;

	stringstream intStream;
	intStream << num;
	intStream >> intString;

	returnString += intString;

	return returnString;
}

string CoreFunctions::GetAppPath()
{
	return current_path().string();
}

void CoreFunctions::WriteLog(string log)
{
	boost::filesystem::ofstream debugStream;
	path debugFilePath(GetAppPath() + "//debug.log");

	debugStream.open(debugFilePath,ios::out);

	debugStream.write(log.c_str(),log.length());

	debugStream.close();
}

void CoreFunctions::ClearLog()
{
	path debugFilePath(GetAppPath() + "//debug.log");
	remove(debugFilePath);
}

string CoreFunctions::ConvertIntToString(int intToConvert)
{
	string intString;
	stringstream intStream;
	intStream << intToConvert;
	intStream >> intString;
	return intString;
}

void CoreFunctions::Tokenize(string input, string tokens, vector<string> * output)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(tokens.c_str());
	tokenizer tokenList(input, sep);

	for (tokenizer::iterator tok_iter = tokenList.begin(); tok_iter != tokenList.end(); ++tok_iter)
	{
		string token = *tok_iter;
		boost::trim(token);
		output->push_back(token);
	}
}

SDL_Color CoreFunctions::ConvertColorNodeToSDLColor(pugi::xml_node ColorNode)
{
	SDL_Color retColor;
	pugi::xml_node rNode = ColorNode.child("r").first_child();
	pugi::xml_node gNode = ColorNode.child("g").first_child();
	pugi::xml_node bNode = ColorNode.child("b").first_child();
	pugi::xml_node aNode = ColorNode.child("a").first_child();
	
	retColor.r = atoi(rNode.value());
	retColor.g = atoi(gNode.value());
	retColor.b = atoi(bNode.value());
	retColor.unused = atoi(aNode.value());

	return retColor;
}