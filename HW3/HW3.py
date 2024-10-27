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
    plt.subplot(2, 3, 1)
    plt.bar(range(len(All_interval)), RGB.R_SplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='red')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Red Channel')
    
    plt.subplot(2, 3, 2)
    plt.bar(range(len(All_interval)), RGB.G_SplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='green')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Green Channel')

    plt.subplot(2, 3, 3)
    plt.bar(range(len(All_interval)), RGB.B_SplitN, tick_label=[f"{max - All_interval[0]}-{max}" for max in All_interval], color='blue')
    plt.xlabel('Intervals')
    plt.ylabel('Number of elements')
    plt.title('Element Distribution in Blue Channel')

    plt.subplot(2, 3, 4)
    rgb_image = np.stack((RGB.R, RGB.G, RGB.B), axis=-1)
    plt.imshow(rgb_image)
    plt.title('Orignal Image')
    plt.colorbar()

    plt.subplot(2, 3, 6)
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

def split_count(split, array):
    
    interval = 255 // split
    All_interval = []
    
    for i in range(split):

        max = interval * (i + 1) + i
        if max > 255:
            max = 255
        All_interval.append(max)

    print(All_interval)

    return All_interval, count(All_interval, array)

if __name__ == '__main__':

    RGB = RGB()
    RGB.R, RGB.G, RGB.B = create_images()
    RGB.R_N = mat_calc(RGB.R, 28)
    RGB.G_N = mat_calc(RGB.G, -30)

    splits = int(input("Please input the number of splits: "))

    All_interval, RGB.R_SplitN = split_count(splits, RGB.R_N)
    _, RGB.G_SplitN = split_count(splits, RGB.G_N)
    _, RGB.B_SplitN = split_count(splits, RGB.B)
    
    plot_hist(All_interval, RGB)


    
