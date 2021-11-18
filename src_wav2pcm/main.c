#include <stdio.h>
#include <stdlib.h>

#include "wavreader.h"

#define BUF_SIZE    1024



int main(int argc, char *argv[])
{
    int format = 0;
    int channels = 0;
    int sample_rate = 0;
    int bits_per_sample = 0;
    int data_length = 0;
    void *vpWav = NULL;
    FILE *fpPcm = NULL;
    unsigned char *pucBuf = (unsigned char *)malloc(BUF_SIZE);
    int iReadBytes = 0;

    if(argc != 3)
    {
        printf("Usage: %s <input.wav> <output.pcm>\n", argv[0]);
		printf("such as: %s ./audio/test_8000_16_1.wav ./out_8000_16_1.pcm\n", argv[0]);
        return -1;
    }

    /* PCM操作 1/3：打开文件 */
    fpPcm = fopen(argv[2], "wb");
    if(fpPcm == NULL)
    {
        perror("argv[2]");
        return -1;
    }

    /* wav操作 1/4：打开文件 */
    vpWav = wav_read_open(argv[1]);
    if(vpWav == NULL)
    {
        printf("wav_read_open(...) error!\n");
        fclose(fpPcm);
        free(pucBuf);
        return -1;
    }


    /* wav操作 2/4（可选）：获取文件头部--音频数据信息 */
    wav_get_header(vpWav, &format, &channels, &sample_rate, &bits_per_sample, &data_length);
    printf("\n**************************************\n"
           "%s info: \n"
           "\t format: %s\n"
           "\t sample rate: %d Hz\n"
           "\t sample bits: %d bits\n"
           "\t chanels: %d\n"
           "\t data length: %d bytes\n"
           "**************************************\n\n",
           argv[1], (format == 1) ? "PCM" : "unknown", /* 注：PCM只是wav支持的其中一种格式 */
           sample_rate, bits_per_sample, channels, data_length);

    while(1)
    {
        /* wav操作 3/4：读取数据 */
        iReadBytes = wav_read_data(vpWav, pucBuf, BUF_SIZE);
        if(iReadBytes <= 0)
        {
            break;
        }

        /* PCM操作 2/3：写入数据 */
        fwrite(pucBuf, 1, iReadBytes, fpPcm);
    }

    /* wav操作 4/4：关闭文件 */
    wav_read_close(vpWav);

    /* PCM操作 3/3：关闭文件 */
    fclose(fpPcm);

    free(pucBuf);
    printf("\n\033[32m%s -> %s Success!\033[0m\n", argv[1], argv[2]);

    return 0;
}
