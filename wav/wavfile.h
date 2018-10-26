#pragma once
 //www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html 
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//#include <cstring>

using namespace std;

class WAVFILE {
public:
	/* WAV-header parameters				Memory address - Occupied space - Describes */
	char chunk_ID[4];                           // 0x00 4 byte - RIFF string
	std::uint32_t  chunk_size;                  // 0x04 4 byte - overall size of
	char format[4];                             // 0x08 4 byte - WAVE string
	char fmt_chunk_marker[4];                   // 0x0c 4 byte - fmt string with trailing null char
	std::uint32_t length_of_fmt;                // 0x10 4 byte - length of the format data,the next part
	std::uint16_t  format_type;                 // 0x14 2 byte - format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	std::uint16_t  channels;                    // 0x16 2 byte - nunbers of channels
	std::uint32_t  sample_rate;                 // 0x18 4 byte - sampling rate (blocks per second)
	std::uint32_t  byte_rate;                   // 0x1c 4 byte - SampleRate * NumChannels * BitsPerSample/8 [比特率]
	std::uint16_t  block_align;                 // 0x20 2 byte - NumChannels * BitsPerSample/8 [块对齐=通道数*每次采样得到的样本位数/8]
	std::uint16_t  bits_per_sample;             // 0x22 2 byte - bits per sample, 8- 8bits, 16- 16 bits etc [位宽]
	char data_chunk_header[4];					// 0x24 4 byte - DATA string or FLLR string
	std::uint32_t  data_size;                   // 0x28 4 byte - NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk 
												//				that will be read,that is the size of PCM data.

	std::uint16_t  sample_numbers;

	vector<char> PCM;			// store the pcm data

	//
	//unsigned char *data;						// a pointer 
	char *pcm_left ;							// a pointer 
	char *pcm_right = nullptr;					// a pointer 
	float *data_left ;
	float *data_right = nullptr;

	int read(string file_name);
	int write(string file_name);
	int decode_pcm(char * pcm_data, float *data);	// decode pcm to float
	int recode_pcm(float*data, char *pcm_recode);	// encode float data to pcm
	uint16_t getChannels();
	uint16_t getSampleRate();
	uint16_t getByteRate();

	~WAVFILE();
}; 
