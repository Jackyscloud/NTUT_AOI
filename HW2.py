# HW2
import numpy as np
import matplotlib.pyplot as plt

class RGB:
    def __init__(self, R=None, G=None, B=None, R_N=None, G_N=None, B_N=None):
        self.R = R
        self.G = G
        self.B = B
        self.R_N = R_N
        self.G_N = G_N
        self.B_N = B_N

def create_images():

    R = [[247,  67,  32, 187, 240],
        [122,  41,  21,  16, 154],
        [ 52,  35,  79,  21,  93],
        [ 27,  22,  35, 154,  75]]
    
    G = [[ 14, 145, 132,  25,  40],
        [212, 221, 121,  54,  14],
        [132, 235, 178,  19,  14],
        [122, 122, 133,  54,  47]]
    
    B = [[17,  44,  32, 127, 240],
        [22,  231,  21,  156, 124],
        [32,  35,  78,  21,  194],
        [127,  22,  33, 54,  45]]

    R = np.array(R)
    G = np.array(G)
    B = np.array(B)

    return R, G, B

def mat_calc(array, number):

    array_new = np.clip(array + number, 0, 255)
    return  array_new

def mat_avg(array):

    mean = np.mean(array)
    std = np.std(array)
    print(mean, std)
    array_new = np.where(array > mean + std, 255, np.where(array < mean - std, 0, array))

    return array_new

def plot_RGB(channels):

    plt.figure(figsize=(10, 5))

    plt.subplot(2, 4, 1)
    plt.imshow(channels.R, cmap='Reds', interpolation='none')
    plt.title('Original Array R')
    plt.colorbar()

    plt.subplot(2, 4, 5)
    plt.imshow(channels.R_N, cmap='Reds', interpolation='none')
    plt.title('Processed Array R')
    plt.colorbar()

    plt.subplot(2, 4, 2)
    plt.imshow(channels.G, cmap='Greens', interpolation='none')
    plt.title('Original Array G')
    plt.colorbar()

    plt.subplot(2, 4, 6)
    plt.imshow(channels.G_N, cmap='Greens', interpolation='none')
    plt.title('Processed Array G')
    plt.colorbar()

    plt.subplot(2, 4, 3)
    plt.imshow(channels.B, cmap='Blues', interpolation='none')
    plt.title('Original Array B')
    plt.colorbar()

    plt.subplot(2, 4, 7)
    plt.imshow(channels.B_N, cmap='Blues', interpolation='none')
    plt.title('Processed Array B')
    plt.colorbar()

    plt.subplot(2, 4, 4)
    rgb_image = np.stack((channels.R, channels.G, channels.B), axis=-1)
    plt.imshow(rgb_image)
    plt.title('Original Image')
    plt.colorbar()

    plt.subplot(2, 4, 8)
    rgb_image = np.stack((channels.R_N, channels.G_N, channels.B_N), axis=-1)
    plt.imshow(rgb_image)
    plt.title('Processed Image')
    plt.colorbar()

    plt.tight_layout()
    plt.show()

if __name__ == '__main__':

    RGB = RGB()
    RGB.R, RGB.G, RGB.B = create_images()
    RGB.R_N = mat_calc(RGB.R, 30)
    RGB.G_N = mat_calc(RGB.G, -20)
    RGB.B_N = mat_avg(RGB.B)

    plot_RGB(RGB)


    
