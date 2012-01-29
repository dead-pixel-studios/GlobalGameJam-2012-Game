#include "ALSequencer.h"

ALSequencer::ALSequencer()
{
	bInitialised = false;
	bDestroying = false;

	fileCount = 0;
	startPos =
	endPos = 0;
	curPos = MAX_SEQUENCE;
	sfxPos = 0;

	pWaveLoader = NULL;

	bPlay = false;

	flEffectSends[0] = 
	flEffectSends[1] = 
	flEffectSends[2] = 
	flEffectSends[3] = 0.0f;

	ulOutputChannels = 0;
	ulNumEffects = 0;
	ulNumSamples = 0;
	ulBuffersProcessed = 0;

	pOutput = 0;
	pEffectOutput[0] = 
	pEffectOutput[1] = 
	pEffectOutput[2] = 
	pEffectOutput[3] = 0;

	if (InitializeOpenAL(NULL, 2, 4, 10240, 44100)) {
		alutInitWithoutContext(NULL, NULL);

		ulOutputChannels = GetNumOutputChannels();
		ulNumEffects = GetNumEffects();
		ulNumSamples = GetNumSamplesPerBuffer();

		bOutOfMemory = false;
		pOutput = malloc(ulOutputChannels * ulNumSamples * 2);
		for (unsigned long ulLoop = 0; ulLoop < ulNumEffects; ulLoop++)
		{
			pEffectOutput[ulLoop] = malloc(ulNumSamples * 2);
			if (pEffectOutput[ulLoop] == NULL)
				bOutOfMemory = true;
		}

		pWaveLoader = new CWaves();

		bInitialised = true;

		if (pWaveLoader && pOutput && !bOutOfMemory) {
			Start();

			EFXEAXREVERBPROPERTIES EFXEAXReverb[1] = { EFX_EAX_REVERB_HANGAR };

			SetEFXEAXReverbProperties(&EFXEAXReverb[0], 0);

			hThread = CreateThread(NULL, 0, ALSequencer::ThreadFuncWrapper, this, 0, &dwThreadId);
		}
	}
}

ALSequencer::~ALSequencer()
{
	bDestroying = true;

	WaitForSingleObject(hThread, INFINITE);

	Stop();

	alutExit();

	ShutdownOpenAL();

	if (pOutput)
		free(pOutput);

	for (unsigned long ulLoop = 0; ulLoop < ulNumEffects; ulLoop++)
	{
		if (pEffectOutput[ulLoop])
			free(pEffectOutput[ulLoop]);
	}

	if (pWaveLoader)
	{
		for (int i = 0; i < fileCount; i++) {
			if (pWaveLoader->IsWaveID(files[i]))
				pWaveLoader->DeleteWaveFile(files[i]);
		}

		delete pWaveLoader;
	}
}

DWORD WINAPI ALSequencer::ThreadFuncWrapper(LPVOID lpThreadParameter)
{
	return ((ALSequencer*)lpThreadParameter)->ThreadFunc();
}

DWORD ALSequencer::ThreadFunc()
{
	while (!bDestroying) {
		ulBuffersProcessed = GetBuffersProcessed();
		while (ulBuffersProcessed)
		{
			MixData(ulNumSamples, ulOutputChannels, pOutput, ulNumEffects, &pEffectOutput[0]);
			CommitData(pOutput, &pEffectOutput[0]);
			ulBuffersProcessed--;
		}
		Sleep(50);
	}

	return 0;
}

void ALSequencer::MixData(unsigned long ulNumSamples, unsigned long ulOutputChannels, void *pOutput, unsigned long ulNumEffects, void **pEffectOutput)
{
	unsigned long ulRequestedBytes;
	unsigned long ulBytesWritten = 0;
	unsigned long ulSample;
	unsigned long ulChannel;

	// Fill Dry Buffer with audio
	ulRequestedBytes = ulNumSamples * ulOutputChannels * 2;
	while (ulRequestedBytes) {
		if (bPlay) {
			// Data for Dry Buffer
			pWaveLoader->ReadWaveData(curPos, (char*)pOutput + ulBytesWritten, ulRequestedBytes, &ulBytesWritten);
			ulRequestedBytes -= ulBytesWritten;
			if (ulRequestedBytes) {
				pWaveLoader->SetWaveDataOffset(QueueAdvance(), 0);
			}
		}
		else {
			// Silence for Dry Buffer
			memset(pOutput, 0, ulRequestedBytes);
			ulRequestedBytes = 0;
		}
	}

	// Fill Effect Buffers with audio
	ulRequestedBytes = ulNumSamples * 2;
	for (unsigned long ulEffectBuffers = 0; ulEffectBuffers < ulNumEffects; ulEffectBuffers++)
	{
		if (bPlay && (flEffectSends[ulEffectBuffers] != 0.0f))
		{
			for (ulSample = 0; ulSample < ulNumSamples; ulSample++)
			{
				float flMixSample = 0.0f;
				for (ulChannel = 0; ulChannel < ulOutputChannels; ulChannel++)
					flMixSample += ((short*)(pOutput))[(ulSample * ulOutputChannels) + ulChannel];

				if (flMixSample < -32768.0f)
					flMixSample = -32768.0f;
				else if (flMixSample > 32767.0f)
					flMixSample = 32767.0f;

				((short*)(pEffectOutput[ulEffectBuffers]))[ulSample] = (short)(flMixSample * flEffectSends[ulEffectBuffers]);
			}
		}
		else
		{
			// Silence for Effect Buffers
			memset(pEffectOutput[ulEffectBuffers], 0, ulRequestedBytes);
		}
	}
}

WAVEID ALSequencer::LoadMusic(char* szFilename)
{
	if (fileCount == MAX_FILES) {
		return -1;
	}
	files[fileCount] = fileCount;
	pWaveLoader->OpenWaveFile(szFilename, &files[fileCount]);
	return files[fileCount++];
}

void ALSequencer::QueueMusic(WAVEID file)
{
	queue[endPos] = file;
	endPos++;
}

WAVEID ALSequencer::QueueAdvance()
{
	curPos++;
	if (curPos >= endPos) {
		curPos = startPos;
	}
	return curPos;
}

ALuint ALSequencer::LoadSFX(const char *fileName)
{
  sfxBuffers[sfxPos] = alutCreateBufferFromFile(fileName);
  alGenSources(1, &sfxSources[sfxPos]);
  alSourcei(sfxSources[sfxPos], AL_BUFFER, sfxBuffers[sfxPos]);
  return sfxPos++;  
}

void ALSequencer::PlaySFX(ALuint sfx)
{
	alSourcePlay(sfxSources[sfx]);
}