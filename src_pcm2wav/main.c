#include <stdio.h>
#include <stdlib.h>

#include "wavwriter.h"

#define BUF_SIZE 	1024



int main(int argc, char *argv[])
{
	FILE *fpPcm = NULL;
	void *vpWav = NULL;
	unsigned char *pucBuf = (unsigned char *)malloc(BUF_SIZE);

	if(argc != 6)
	{
		printf("Usage: %s <input.pcm> <pcm sample rate> <pcm sample bits> <pcm sample channels> <output.wav>\n", argv[0]);
		printf("examples: \n"
			   "   %s ./audio/test_8000_16_1.pcm 8000 16 1 ./out_8000_16_1.wav\n"
			   "   %s ./audio/test_44100_16_2.pcm 44100 16 2 ./out_44100_16_2.wav\n",
				argv[0], argv[0]);
		return -1;
	}
	printf("\n**************************************\n"
		   "input: \n"
		   "\t file name: %s\n"
		   "\t sample rate: %d Hz\n"
		   "\t sample bits: %d bits\n"
		   "\t channels: %d\n"
		   "output: \n"
		   "\t file name: %s\n"
		   "**************************************\n\n",
		  argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

	/* PCM操作 1/3：打开文件 */
	fpPcm = fopen(argv[1], "rb");
	if(fpPcm == NULL)
	{
		perror("argv[1]");
		return -1;
	}
	

	/* wav操作 1/3：以特定参数打开文件（目前支持PCM的音频数据格式） */
	/*            参数:   wav文件名    采样率         采样位数        声道数  */
	vpWav = wav_write_open(argv[5], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	if(vpWav == NULL)
	{
		printf("wav_write_open(...) error!\n");
		free(pucBuf);
		fclose(fpPcm);	
		return -1;
	}

	while(1)
	{
		/* PCM操作 2/3：读取PCM数据 */
		int iReadBytes = 0;
		iReadBytes = fread(pucBuf, 1, BUF_SIZE, fpPcm);
		if(iReadBytes <= 0)
		{
			break;
		}
		
		/* wav操作 2/3：写入数据 */
		/*      参数:  句柄    数据    数据长度 */
		wav_write_data(vpWav, pucBuf, iReadBytes);
	}
	
	/* wav操作 3/3：关闭文件 */
	wav_write_close(vpWav);

	/* PCM操作 3/3：关闭文件 */
	fclose(fpPcm);

	free(pucBuf);

	printf("\n\033[32m%s -> %s Success!\033[0m\n", argv[1], argv[5]);

	return 0;
}

