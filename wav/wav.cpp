// wav.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstring>		// memcpy
//#include "wavfile.h"
#include "AudioFile.cpp"
#pragma comment(lib, "..\\debug\\DLLDemo1.lib")
using namespace std;
int main()
{
	string file_name = "decode.wav";
	//***********测试audio file***********//
	AudioFile<double> af;
	af.load(file_name);
	for (size_t i = 0; i != 200; ++i) {
		af.samples[0][i] = 0.6;
	}
	vector<vector<double>> toStore(af.samples.begin(), af.samples.end());	
	af.setAudioBuffer(toStore);
	af.save("saveTest.wav");
	cout << "Saved.\n";
	//***********测试audio file***********//

    return 0;
}

