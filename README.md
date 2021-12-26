
### 1、demo说明

使用开源项目opencore-amr中test目录下的`wavwriter.c/wavwriter.h`和`wavreader.c/wavreader.h`文件，将PCM和WAV格式的音频文件进行相互转换。
（注：PCM只是WAV封装规范所支持的其中一种格式，两者不是等价关系。此程序中的wavwriter只支持PCM（format=0x0001）。）

### 2、编译

```bash
$ make  					# 或者交叉编译 make CC=your-crosscompile-gcc
$ ls -l pcm2wav wav2pcm 	# 编译生成的文件 
```

### 3、使用

```bash
$ ./pcm2wav ./audio/test_8000_16_1.pcm 8000 16 1 ./out_8000_16_1.wav
$ ./pcm2wav ./audio/test_44100_16_2.pcm 44100 16 2 ./out_44100_16_2.wav
$ ./wav2pcm ./audio/test_8000_16_1.wav ./out_8000_16_1.pcm
$ ./wav2pcm ./audio/test_44100_16_2.wav ./out_44100_16_2.pcm
```

### 4. 参考文章

 - [PCM音频数据 - 简书](https://www.jianshu.com/p/fd43c1c82945)

 - [wav文件格式分析与详解 - nigaopeng - 博客园](https://www.cnblogs.com/ranson7zop/p/7657874.html)


### 附录：目录架构

```bash
$ tree
.
├── audio
│   ├── test_44100_16_2.pcm
│   ├── test_44100_16_2.wav
│   ├── test_8000_16_1.pcm
│   └── test_8000_16_1.wav
├── docs
│   ├── PCM音频数据 - 简书.mhtml
│   ├── WAV文件格式分析.pdf
│   └── wav文件格式分析与详解 - nigaopeng - 博客园.mhtml
├── Makefile
├── README.md
├── src_pcm2wav
│   ├── main.c
│   ├── wavwriter.c
│   └── wavwriter.h
└── src_wav2pcm
    ├── main.c
    ├── wavreader.c
    └── wavreader.h
```

