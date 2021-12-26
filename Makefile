all: pcm2wav wav2pcm

CC := gcc
CFLAG := 

PCM2WAV_DIR := ./src_pcm2wav
WAV2PCM_DIR := ./src_wav2pcm

pcm2wav: $(PCM2WAV_DIR)/main.c $(PCM2WAV_DIR)/wavwriter.c $(PCM2WAV_DIR)/wavwriter.h
	$(CC) $^ $(CFLAG) -o $@

wav2pcm: $(WAV2PCM_DIR)/main.c $(WAV2PCM_DIR)/wavreader.c $(WAV2PCM_DIR)/wavreader.h
	$(CC) $^ $(CFLAG) -o $@

clean :
	rm -rf pcm2wav wav2pcm out*
.PHONY := clean

