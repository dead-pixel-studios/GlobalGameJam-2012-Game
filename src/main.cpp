#include "CoreEngine/CoreEngine.h"

int main( int argc, char* argv[] )
{
	CoreEngine * cEngine = CoreEngine::Instance();
	cEngine->Start();
	return 1;
}