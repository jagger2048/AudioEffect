// wav.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstring>		// memcpy
#include "wavfile.h"
#include "AudioFile.cpp"
using namespace std;
int main()
{
	string file_name = "decode.wav";
	//***********原先用于测试的***********//
	//WAVFILE wav;
	//wav.read(file_name);
	AudioFile<double> af;
	af.load(file_name);
	for (size_t i = 0; i != 200; ++i) {
		af.samples[0][i] = 0.6;
	}
	vector<vector<double>> toStore(af.samples.begin(), af.samples.end());	
	af.setAudioBuffer(toStore);
	af.save("saveTest.wav");
	cout << "Saved.\n";
	//af.samples[0]




	//cout << wav.sample_rate << endl;
	//cout << ((wav.pcm_left[2] << 8) + wav.pcm_left[3]) << endl;
	//cout << sizeof(wav.pcm_left)/ sizeof(wav.pcm_left[0]) << endl;
	//***********原先用于测试的***********//


	//ifstream fi(file_name);

	//fi.seekg(44);
	//// wav文件的大小
	//char *temp = new char[40];	// 40 个字节,前20个数

	//fi.read( (char* )temp,40);
	//double t = 0;
	//for (size_t n = 0; n != 40; n += 2) {
	//	t = ((temp[n+1]<<8) + temp[n] ) / 32768.0; // 小端
	//	cout << " t is: " << t << endl;

	//}
	//memcpy((char *)&t, (char *)p, 2 );




	//for (size_t n = 0; n != 10; ++n) {
	//	cout << wav.data_left[n] << " ";
	//}
    return 0;
}

