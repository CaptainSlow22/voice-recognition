import numpy as np
import matplotlib.pyplot as plt

def read_spectrogram_data(file_name):
    with open(file_name, 'r') as file:
        num_channels, sample_rate, bits_per_sample = map(int, file.readline().split())
        data = np.array([int(line) for line in file])
    return num_channels, sample_rate, bits_per_sample, data

def draw_spectrogram(ax, num_channels, sample_rate, bits_per_sample, data, title):
    ax.specgram(data, NFFT=256, Fs=sample_rate, noverlap=128)
    ax.set_title(title)
    ax.set_xlabel('Time (s)')
    ax.set_ylabel('Frequency (Hz)')

file1_num_channels, file1_sample_rate, file1_bits_per_sample, file1_data = read_spectrogram_data('file1_spectrogram.txt')
file2_num_channels, file2_sample_rate, file2_bits_per_sample, file2_data = read_spectrogram_data('file2_spectrogram.txt')

fig, (ax1, ax2) = plt.subplots(2, 1)
draw_spectrogram(ax1, file1_num_channels, file1_sample_rate, file1_bits_per_sample, file1_data, 'File 1 Spectrogram')
draw_spectrogram(ax2, file2_num_channels, file2_sample_rate, file2_bits_per_sample, file2_data, 'File 2 Spectrogram')

plt.show()