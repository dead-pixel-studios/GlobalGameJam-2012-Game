#pragma once


#include "CoreSize.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/any.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/compare.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <math.h>
#include <string>
#include <list>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include "../Bytelink/GUI/Animations/GUI_Animation.h"

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;

#define foreach BOOST_FOREACH

class GUI_Animation;
struct SkinImage;

class CoreFunctions
{
public:
	static GLenum PixelFormatToTextureFormat(SDL_PixelFormat * PixelFormat);
	static int Round(double rnd);
	static int NextPowerOf2(int val);
	static string addIntToString(string mainString, int num);
	static string ConvertIntToString(int convert);
	static string GetAppPath();
	static void WriteLog(string log);
	static void ClearLog();
	static void Tokenize(string input, string tokens, vector<string> * output);
	static GUI_Animation::AnimType ConvertStringToAnimType(string type);
	static SDL_Color ConvertColorNodeToSDLColor(pugi::xml_node ColorNode);
	static SkinImage ConvertImageNodeToSkinImage(pugi::xml_node ImageNode);
};

#include "../Bytelink/GUI/GUI_Skin.h"