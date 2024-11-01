# HW3
import numpy as np
import matplotlib.pyplot as plt

class RGB:
    def __init__(self, R=None, G=None, B=None, R_N=None, G_N=None, B_N=None,
                 R_SplitN=None, G_SplitN=None, B_SplitN=None):
        self.R = R
        self.G = G
        self.B = B
        self.R_N = R_N
        self.G_N = G_N
        self.B_N = B_N
        self.R_OSplitN = []
        self.G_OSplitN = []
        self.B_OSplitN = []
        self.R_SplitN = []
        self.G_SplitN = []
        self.B_SplitN = []

def create_images():

    R = [[247,  67,  32, 187, 240],
        [122,  41,  21,  16, 154],
        [ 52,  35,  79,  21,  93],
        [ 27,  22,  35, 154,  75]]
    
    G = [[14, 145, 132,  25,  40],
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

def plot_hist(All_interval, RGB):

    plt.figure(figsize=(15, 15))

    # Plotting the histogram
    plt.subplot(2, 4, 5)
    plt.bar(range(len(All_interval)), RGB.R_SplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='red')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Processed Red')
    
    plt.subplot(2, 4, 6)
    plt.bar(range(len(All_interval)), RGB.G_SplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='green')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Processed Green')

    plt.subplot(2, 4, 7)
    plt.bar(range(len(All_interval)), RGB.B_SplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='blue')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Processed Blue')

    plt.subplot(2, 4, 1)
    plt.bar(range(len(All_interval)), RGB.R_OSplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='red')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Original Red')
    
    plt.subplot(2, 4, 2)
    plt.bar(range(len(All_interval)), RGB.G_OSplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='green')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Original Green')

    plt.subplot(2, 4, 3)
    plt.bar(range(len(All_interval)), RGB.B_OSplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='blue')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Original Blue')
    
    
    plt.subplot(2, 4, 4)
    rgb_image = np.stack((RGB.R, RGB.G, RGB.B), axis=-1)
    plt.imshow(rgb_image)
    plt.title('Orignal Image')
    plt.colorbar()

    plt.subplot(2, 4, 8)
    rgb_image = np.stack((RGB.R_N, RGB.G_N, RGB.B), axis=-1)
    plt.imshow(rgb_image)
    plt.title('Processed Image')
    plt.colorbar()
    
    plt.tight_layout()
    plt.show()

def count(interval, array):
    
    split_numbers = []

    for i in range(len(interval)):
     
        numbers = ((array <= interval[i]) & (array >= interval[i] - interval[0])).sum()
        split_numbers.append(numbers)

    print(split_numbers)

    return split_numbers

def split_count(split, array, array_original):
    
    interval = 255 // split
    All_interval = []
    
    for i in range(split):

        max = interval * (i + 1) + i
        if max > 255:
            max = 255
        All_interval.append(max)

    print(All_interval)

    return All_interval, count(All_interval, array), count(All_interval, array_original)

if __name__ == '__main__':

    RGB = RGB()
    RGB.R, RGB.G, RGB.B = create_images()
    RGB.R_N = mat_calc(RGB.R, 28)
    RGB.G_N = mat_calc(RGB.G, -30)

    splits = int(input("Please input the number of splits: "))

    All_interval, RGB.R_SplitN, RGB.R_OSplitN = split_count(splits, RGB.R_N, RGB.R)
    _, RGB.G_SplitN, RGB.G_OSplitN = split_count(splits, RGB.G_N, RGB.G)
    _, RGB.B_SplitN, RGB.B_OSplitN = split_count(splits, RGB.B, RGB.B)

    plot_hist(All_interval, RGB)