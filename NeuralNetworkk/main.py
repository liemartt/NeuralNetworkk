import os
from PIL import Image
def digits0to9():
    for i in range(10):
        im = Image.open(f"{i}.jpg")
        coordinate = x, y = 20, 20
        with open('convertImage.txt', 'w') as f:
            for y in range(28):
                for x in range(28):
                    coordinate = x, y
                    f.write(str(255 - abs(int(sum(im.getpixel(coordinate)) / len(im.getpixel(coordinate)))) - 3))
                    f.write(' ')
                f.write('\n')
        os.system('C:/Users/artemm/Desktop/Learning/NeuralNetworkk/x64/Release/NeuralNetworkk.exe')
        print('Правильная цифра: ', i)
def drawdigit():
    os.system(f'test.jpg')
    im = Image.open(f"test.jpg")
    coordinate = x, y = 20, 20
    with open('convertImage.txt', 'w') as f:
        for y in range(28):
            for x in range(28):
                coordinate = x, y
                f.write(str(255-abs(int(sum(im.getpixel(coordinate))/len(im.getpixel(coordinate))))-3))
                f.write(' ')
            f.write('\n')
    os.system('C:/Users/artemm/Desktop/Learning/NeuralNetworkk/x64/Release/NeuralNetworkk.exe')
drawdigit()