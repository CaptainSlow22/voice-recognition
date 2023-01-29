#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <complex>
#include <numeric>
#include <algorithm>



#define M_PI 3.14159265358979323846

class WavFile {
  public:
    WavFile(std::string fileName)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file.");
        }
        file.read((char*)&header, sizeof(header));
        data.resize(header.subChunk2Size / sizeof(short));
        file.read((char*)data.data(), header.subChunk2Size);
    }

    void writeDataForSpectrogram(std::string fileName) const
    {
        std::ofstream file(fileName);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file.");
        }
        file << header.numChannels << " " << header.sampleRate << " " << header.bitsPerSample << std::endl;
        int dataSize = header.subChunk2Size / sizeof(short);
        for (int i = 0; i < dataSize; i++)
        {
            file << data[i] << std::endl;
        }
        file.close();
    }
    //Cooley-Tukey algorithm
    void FFT(std::vector<std::complex<double>>& data)
    {
        int n = data.size();
        if (n == 1)
        {
            return;
        }

        std::vector<std::complex<double>> even(n / 2);
        std::vector<std::complex<double>> odd(n / 2);
        for (int i = 0; i < n / 2; i++)
        {
            even[i] = data[2 * i];
            odd[i] = data[2 * i + 1];
        }

        FFT(even);
        FFT(odd);

        for (int k = 0; k < n / 2; k++)
        {
            std::complex<double> t = std::polar(1.0, -2 * M_PI * k / n) * odd[k];
            data[k] = even[k] + t;
            data[k + n / 2] = even[k] - t;
        }
    }

    double calculateSimilarity(const WavFile& other) const {
        if (data.size() != other.data.size())
        {
            int size = (std::min)(data.size(), other.data.size());
            double sum = 0;
            for (int i = 0; i < size; i++)
            {
                sum += std::pow(data[i] - other.data[i], 2);
            }
            return std::sqrt(sum) / size;
        }
        else
        {
            double sum = 0;
            for (int i = 0; i < data.size(); i++)
            {
                sum += std::pow(data[i] - other.data[i], 2);
            }
            return std::sqrt(sum) / data.size();
        }
    }

  private:
    struct WavHeader
    {
        char chunkId[4];
        int chunkSize;
        char format[4];
        char subChunk1Id[4];
        int subChunk1Size;
        short audioFormat;
        short numChannels;
        int sampleRate;
        int byteRate;
        short blockAlign;
        short bitsPerSample;
        char subChunk2Id[4];
        int subChunk2Size;
    };

    WavHeader header;
    std::vector<short> data;
};

int main()
{
    int choice;
    std::cout<<"Voice Recognition Software"<<std::endl;
    std::cout<<"##########################"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Case 1: Same female voice reading different text"<<std::endl;
    std::cout<<"Case 2: Different male voice"<<std::endl;
    std::cout<<"Case 3: Male voice/ female voice"<<std::endl;
    std::cout<<"Case 4: Same female voice reading the same text"<<std::endl;
    std::cout<<"Case 5: Same male voice reading the same text"<<std::endl;
    std::cout<<" -> Please enter the number of the case: ";
    std::cin>>choice;
    std::cout<<"--------------------------"<<std::endl;
    switch (choice)
    {
    case 1:
        {
            try {
                WavFile file1("case1\\file1.wav");
                WavFile file2("case1\\file2.wav");

                file1.writeDataForSpectrogram("file1_spectrogram.txt");
                file2.writeDataForSpectrogram("file2_spectrogram.txt");
                double similarity = file1.calculateSimilarity(file2);
                std::cout << "Similarity index: "<< similarity <<" (values above 0 are indicating differences)"<< std::endl;

                if (similarity <= 4) {
                    std::cout << "The voices in the two Wav files belong to the same person." << std::endl;
                }
                else {
                    std::cout << "The voices in the two Wav files do not belong to the same person." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
        break;
    case 2: 
        {
            try
            {
                WavFile file1("case2\\file1.wav");
                WavFile file2("case2\\file2.wav");

                file1.writeDataForSpectrogram("file1_spectrogram.txt");
                file2.writeDataForSpectrogram("file2_spectrogram.txt");
                double similarity = file1.calculateSimilarity(file2);
                std::cout << "Similarity index: "<< similarity <<" (values above 0 are indicating differences)"<< std::endl;

                if (similarity <= 4) {
                    std::cout << "The voices in the two Wav files belong to the same person." << std::endl;
                }
                else {
                    std::cout << "The voices in the two Wav files do not belong to the same person." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
    break;
    case 3:
        {
            try
            {
                WavFile file1("case3\\file1.wav");
                WavFile file2("case3\\file2.wav");

                file1.writeDataForSpectrogram("file1_spectrogram.txt");
                file2.writeDataForSpectrogram("file2_spectrogram.txt");
                double similarity = file1.calculateSimilarity(file2);
                std::cout << "Similarity index: "<< similarity <<" (values above 0 are indicating differences)"<< std::endl;

                if (similarity <= 4) {
                    std::cout << "The voices in the two Wav files belong to the same person." << std::endl;
                }
                else {
                    std::cout << "The voices in the two Wav files do not belong to the same person." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
    break;
    case 4:
        {
            try
            {
                WavFile file1("case4\\file1.wav");
                WavFile file2("case4\\file2.wav");

                file1.writeDataForSpectrogram("file1_spectrogram.txt");
                file2.writeDataForSpectrogram("file2_spectrogram.txt");
                double similarity = file1.calculateSimilarity(file2);
                std::cout << "Similarity index: "<< similarity <<" (values above 0 are indicating differences)"<< std::endl;

                if (similarity <= 4) {
                    std::cout << "The voices in the two Wav files belong to the same person." << std::endl;
                }
                else {
                    std::cout << "The voices in the two Wav files do not belong to the same person." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
    break;

    case 5:
        {
            try {
                WavFile file1("case5\\file1.wav");
                WavFile file2("case5\\file2.wav");

                file1.writeDataForSpectrogram("file1_spectrogram.txt");
                file2.writeDataForSpectrogram("file2_spectrogram.txt");
                double similarity = file1.calculateSimilarity(file2);
                std::cout << "Similarity index: "<< similarity <<" (values above 0 are indicating differences)"<< std::endl;

                if (similarity <= 4) {
                    std::cout << "The voices in the two Wav files belong to the same person." << std::endl;
                }
                else {
                    std::cout << "The voices in the two Wav files do not belong to the same person." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
        break;

    default:
        throw std::runtime_error("Invalid case");
    }
    
    return 0;
}
