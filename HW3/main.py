from PySide6.QtWidgets import QApplication, QWidget, QFileDialog
from PySide6.QtGui import QImage, QPixmap
from ui_untitled import Ui_Form
from HW3 import *

class MyWidget(QWidget):

    def __init__(self):
        super().__init__()
        self.ui = Ui_Form()
        self.ui.setupUi(self)

def image_processing():

    RGB = RGB()
    RGB.R, RGB.G, RGB.B = create_images()
    RGB.R_N = mat_calc(RGB.R, 28)
    RGB.G_N = mat_calc(RGB.G, -30)

    splits = int(input("Please input the number of splits: "))

    All_interval, RGB.R_SplitN = split_count(splits, RGB.R_N)
    _, RGB.G_SplitN = split_count(splits, RGB.G_N)
    _, RGB.B_SplitN = split_count(splits, RGB.B)
    
    plot_hist(All_interval, RGB)

if __name__ == "__main__":

    app = QApplication([])
    widget = MyWidget()
    widget.show()
    # Your coed here
    image_processing()
    app.exec()