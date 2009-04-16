#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/* These are in charge of maintaining our sine function */
float sinPos;
float sinStep;

/* These are the audio card settings */
#define FREQ 44100
#define SAMPLES 8192 

/* This is basically an arbitrary number */
#define VOLUME 10.0

void populate(void* data, Uint8 *stream, int len) {
	for (int i=0; i<len; i++) {
		/* Just fill the stream with sine! */
		stream[i] = (Uint8) (VOLUME * sinf(sinPos));
		sinPos += sinStep;
	}
}

int main(int argc, char* argv[]) {
	/* This will hold our data */
	SDL_AudioSpec spec;
	/* This will hold the requested frequency */
	int reqFreq = 440;
	/* This is the duration to hold the note for */
	int duration = 1;

	/* Set up the requested settings */
	spec.freq = FREQ;
	spec.format = AUDIO_U8;
	spec.channels = 1;
	spec.samples = SAMPLES;
	spec.callback = (*populate);
	spec.userdata = NULL;

	/* Open the audio channel */
	if (SDL_OpenAudio(&spec, NULL) < 0) { 
		/* FAIL! */
		fprintf(stderr, "Failed to open audio: %s \n", SDL_GetError());
		exit(1); 
	} 

	/* Initialize the position of our sine wave */
	sinPos = 0;
	/* Calculate the step of our sin wave */
	sinStep = 2 * M_PI * reqFreq / FREQ;

	/* Now, run this thing */
	SDL_PauseAudio(0); 
	/* Delay for the requested number of seconds */
	sleep(duration);
	/* Then turn it off again */
	SDL_PauseAudio(1);

	/* Close audio channel */
	SDL_CloseAudio();
}
