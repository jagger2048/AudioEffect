#include "stdafx.h"
//#include "wavfile.h"

int WAVFILE::read(string file_name)
{
	ifstream fi(file_name, ios::binary);
	if (!fi.is_open()) std::cout << "Cannot open the file!\n";

	// 前44字节是 wav文件的头部
	//  cnstart to read the wav file.
	// read the wav file's header
	fi.seekg(0);
	fi.read((char*)&chunk_ID, sizeof(chunk_ID) );
	fi.read((char*)&chunk_size, sizeof(chunk_size));
	fi.read((char*)&format, sizeof(format));
	fi.read((char*)&fmt_chunk_marker, sizeof(fmt_chunk_marker));
	fi.read((char*)&length_of_fmt, sizeof(length_of_fmt));
	fi.read((char*)&format_type, sizeof(format_type));
	fi.read((char*)&channels, sizeof(channels));
	fi.read((char*)&sample_rate, sizeof(sample_rate));
	fi.read((char*)&byte_rate, sizeof(byte_rate));
	fi.read((char*)&block_align, sizeof(block_align));
	fi.read((char*)&bits_per_sample, sizeof(bits_per_sample));
	fi.read((char*)&data_chunk_header, sizeof(data_chunk_header));
	fi.read((char*)&data_size, sizeof(data_size));

	sample_numbers = data_size / bits_per_sample; // bits_per_sample 16 bits=2

	// 增加文件错误处理函数
	if (int( fi.tellg() ) != 44) {
		cout << " Cannot read the wac file's header";
	}
	pcm_left = new  char[data_size];
	pcm_right = new  char[data_size];
	
	// read the wav file's PCM data
	if (channels != 1) {
		// stereo
		bool channel_select = true;

		size_t countL = 0;
		size_t countR = 0;
		while (fi.good()) {
			if (channel_select) {
				fi.read((char*)&pcm_left + (countL++) * bits_per_sample, bits_per_sample);
				channel_select = false;
			}
			else {
				channel_select = true;
				fi.read(pcm_right + (countR++) * bits_per_sample, bits_per_sample);
			}
		}

		decode_pcm(pcm_left, data_left);
		decode_pcm(pcm_right, data_right);

	}
	else {
		// mono

		//char *temp = new char[data_size];	// 此处有无问题？
		pcm_left = new char[data_size];		// 需要重新分配空间，才能往里边写入
		//fi.read( temp, sizeof(char) * data_size);
		fi.read( pcm_left, sizeof(char) * data_size);

		//memcpy((char*)pcm_left, (char *)temp, data_size);

		//delete[] temp;


		decode_pcm(pcm_left, data_left);
	}

	fi.close();
	return 0;
}

int WAVFILE::write(string file_name)
{
	ofstream fo(file_name);
	//fo.seekp(0);
	fo.write((char*)&chunk_ID, sizeof(chunk_ID[0]));
	fo.write((char*)&chunk_ID, sizeof(chunk_ID[0]));
	fo.write((char*)&format, sizeof(format[0]));
	fo.write((char*)&fmt_chunk_marker, sizeof(fmt_chunk_marker[0]));
	fo.write((char*)&length_of_fmt, sizeof(length_of_fmt));
	fo.write((char*)&length_of_fmt, sizeof(length_of_fmt));
	fo.write((char*)&format_type, sizeof(format_type));
	fo.write((char*)&channels, sizeof(channels));
	fo.write((char*)&sample_rate, sizeof(sample_rate));
	fo.write((char*)&byte_rate, sizeof(byte_rate));
	fo.write((char*)&block_align, sizeof(block_align));
	fo.write((char*)&bits_per_sample, sizeof(bits_per_sample));
	fo.write((char*)&data_chunk_header, sizeof(data_chunk_header[0]));

	fo.write((char*)&data_size, sizeof(data_size));

	//fo.write((char*)&pcm_recode, sizeof(pcm_recode[0]));

	return 0;
}

int WAVFILE::decode_pcm(char * pcm_data, float *data)
{
	//DecodePcm
	data = new float[data_size / bits_per_sample];	// 点数 = PCM 总长 / 比特率
	unsigned short decode_temp = 0;// default 16 bite

	cout << "start decode\n";

	cout << " data: \n";
	// bits_per_sample = 2
	double dt = 0;
	int data_index = 0;
	for (size_t nn = 0; nn != data_size; nn += 2) {
		//data[data_index++] = (pcm_left[nn + 1] << 8 | pcm_left[nn]) / 32768.0;
		data[data_index++] = 0.6;// 有问题
		//cout << "No " << nn / 2 << " :" << dt << endl;
	}

	cout << "Decoded\n";
	return 0;

}

WAVFILE::~WAVFILE()
{
	delete [] pcm_left;						
	delete[] pcm_right;
	delete[] data_left;
	delete[] data_right;
}
