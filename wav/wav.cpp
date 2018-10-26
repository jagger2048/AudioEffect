// wav.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include "wavfile.h"
#include "wavfile.cpp"

using namespace std;
int main()
{
	string file_name = "denoise_3.wav";
	WAV wav;
	wav.read(file_name);
	cout << wav.sample_rate << endl;
	for (size_t n = 0; n != 1000; ++n) {
		cout << wav.data_left[n] << " ";
	}
    return 0;
}

