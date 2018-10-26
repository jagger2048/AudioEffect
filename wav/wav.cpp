// wav.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstring>  // memcpu
#include "wavfile.h"

using namespace std;
int main()
{
	string file_name = "denoise_3.wav";
	WAVFILE wav;
	wav.read(file_name);
	cout << wav.sample_rate << endl;
	cout << ((wav.pcm_left[2] << 8) + wav.pcm_left[3]) << endl;
	cout << sizeof(wav.pcm_left)/ sizeof(wav.pcm_left[0]) << endl;
	//for (size_t n = 0; n != 10; ++n) {
	//	cout << wav.data_left[n] << " ";
	//}
    return 0;
}

