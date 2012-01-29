#include <windows.h>

#include "ALOutput.h"
#include "CWaves.h"

const int MAX_SEQUENCE = 1024;
const int MAX_FILES = 1024;

class ALSequencer
{
public:
	ALSequencer();
	~ALSequencer();

	void MixData(unsigned long ulNumSamples, unsigned long ulOutputChannels, void *pOutput, unsigned long ulNumEffects, void **pEffectOutput);

	unsigned long ulOutputChannels;
	unsigned long ulNumEffects;
	unsigned long ulNumSamples;
	unsigned long ulBuffersProcessed;

	CWaves *pWaveLoader;

	bool bPlay;
	float flEffectSends[4];

	void* pOutput;
	void* pEffectOutput[4];

	bool bInitialised;
	bool bOutOfMemory;
	bool bDestroying;

	HANDLE hThread;
	DWORD dwThreadId;

	static DWORD WINAPI ThreadFuncWrapper(LPVOID lpThreadParameter);
	DWORD ThreadFunc();

	WAVEID files[MAX_FILES];
	WAVEID queue[MAX_SEQUENCE];

	int fileCount;

	WAVEID LoadFile(char* szFilename);
	void QueueFile(WAVEID file);
	WAVEID QueueAdvance();

	int startPos;
	int endPos;
	int curPos;

};