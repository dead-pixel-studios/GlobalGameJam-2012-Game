#include <windows.h>

#include "ALOutput.h"
#include "CWaves.h"
#include "alut.h"

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

	ALuint sfxSources[MAX_FILES];
	ALuint sfxBuffers[MAX_FILES];

	int sfxPos;

	int fileCount;

	WAVEID LoadMusic(char* szFilename);
	void QueueMusic(WAVEID file);
	WAVEID QueueAdvance();

	int startPos;
	int endPos;
	int curPos;

	ALuint LoadSFX(const char *fileName);
	void PlaySFX(ALuint sfx);
};