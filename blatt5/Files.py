def get_cols(file):
    x = []
    y = []
    z = []
    for line in file:
        lineArr = line.split(" ")
        x.append(float(lineArr[0]))
        y.append(float(lineArr[1]) + float(lineArr[2]))
        z.append(float(lineArr[2]))
    return x, y, z


class Solution:
    def __init__(self, path):
        self.file = open(path, "r")
        self.x, self.y, self.z = get_cols(self.file)