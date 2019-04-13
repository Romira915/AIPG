from random import *
from PIL import Image,ImageDraw
from time import *
from copy import *
import os

class Maze:
    WALL = 0
    ROAD = 1
    START = 9
    GOAL = 5

    def __init__(self, width=11,height=11):
        if width % 2 == Maze.WALL:
            width += 1
        if height % 2 == Maze.WALL:
            height += 1

        # クラスのメンバ関数
        self.maxX = width
        self.maxY = height
        self.maping = [[Maze.WALL] * self.maxX for i in range(self.maxY)]
        self.start = ()
        self.goal = ()
        self.nowX = 0
        self.nowY = 0
        self.history = [()]
        self.digcount = 0
        self.gifimg = []

        for i, name in enumerate(self.maping):
            if i == 0 or i == self.maxY - 1:
                for j, name in enumerate(self.maping[0]):
                    self.maping[i][j] = Maze.ROAD

            self.maping[i][0] = Maze.ROAD
            self.maping[i][self.maxX - 1] = Maze.ROAD

    def Generating(self, log=False, giflog=False):
        notfindcount = 0

        self.start = randrange(2,self.maxX - 2,2) , randrange(2,self.maxY - 2,2)
        self.maping[self.start[1]][self.start[0]] = Maze.ROAD
        (self.nowX, self.nowY) = self.start
        self.history[0] = deepcopy(self.start)

        print("迷路生成中")
        while True:
            if self.__DigCheck(log=log, giflog=giflog):
                pass
            else:
                (self.nowX, self.nowY) = self.history[randrange(len(self.history))]
                notfindcount += 1

            print("\r工程数 %d / " % self.digcount + str(((self.maxX - 4) // 2 + 1) * ((self.maxY - 4) // 2 + 1) - 1),end='')

            # 穴掘り法の工程数 (未開拓の奇数マスにしか移動しないことから導出。)
            # -1はstart地点を換算していないため
            if self.digcount == ((self.maxX - 4) // 2 + 1) * ((self.maxY - 4) // 2 + 1) - 1:
                print("\n生成完了")
                break

        self.maping[self.start[1]][self.start[0]] = Maze.START
        self.maping[self.nowY][self.nowX] = Maze.GOAL
        self.goal = (self.nowX, self.nowY)

        if giflog:
            print("giflogを保存中・・・")
            self.gifimg[0].save(giflog,save_all=True, append_images=self.gifimg[1:], optimize=False, duration=40, loop=0)
            print("giflogを保存しました")

        return self.maping, self.start, self.goal

    def __DigCheck(self, dir_all=False, log=False, giflog=False):
        dir = randrange(4)
        if dir_all:
            dir = 4
        boolean = False
        if dir == 0 or dir == 4:
            if self.maping[self.nowY - 1][self.nowX] == Maze.WALL and self.maping[self.nowY - 2][self.nowX] == Maze.WALL:
                self.maping[self.nowY - 1][self.nowX] = Maze.ROAD
                self.maping[self.nowY - 2][self.nowX] = Maze.ROAD
                self.nowY -= 2
                boolean = True
            else:
                boolean = False
        elif dir == 1 or dir == 4:
            if self.maping[self.nowY][self.nowX + 1] == Maze.WALL and self.maping[self.nowY][self.nowX + 2] == Maze.WALL:
                self.maping[self.nowY][self.nowX + 1] = Maze.ROAD
                self.maping[self.nowY][self.nowX + 2] = Maze.ROAD
                self.nowX += 2
                boolean = True
            else:
                boolean = False
        elif dir == 2 or dir == 4:
            if self.maping[self.nowY + 1][self.nowX] == Maze.WALL and self.maping[self.nowY + 2][self.nowX] == Maze.WALL:
                self.maping[self.nowY + 1][self.nowX] = Maze.ROAD
                self.maping[self.nowY + 2][self.nowX] = Maze.ROAD
                self.nowY += 2
                boolean = True
            else:
                boolean = False
        elif dir == 3 or dir == 4:
            if self.maping[self.nowY][self.nowX - 1] == Maze.WALL and self.maping[self.nowY][self.nowX - 2] == Maze.WALL:
                self.maping[self.nowY][self.nowX - 1] = Maze.ROAD
                self.maping[self.nowY][self.nowX - 2] = Maze.ROAD
                self.nowX -= 2
                boolean = True
            else:
                boolean = False

        if boolean:
            self.history.append((self.nowX, self.nowY))
            if log:
                self.Save_maping(log[:log.find('.')] + '%d' % self.digcount + log[log.find('.'):])
            if giflog:
                self.gifimg.append(self.Save_maping(giflog, gifreturn=True))
            self.digcount += 1

        return boolean

    def Show_maping(self):
        for i, nameY in enumerate(self.maping):
            print(nameY)

    def Save_maping(self, imagename, gifreturn=False):
        PIXELSIZE = 15

        img = Image.new("RGB",(self.maxX * PIXELSIZE + 1,self.maxY * PIXELSIZE + 1),(0))
        draw = ImageDraw.Draw(img)

        for i, nameY in enumerate(self.maping):
            for j, nameX in enumerate(nameY):
                draw.rectangle((j * PIXELSIZE,i * PIXELSIZE,j * PIXELSIZE + PIXELSIZE,i * PIXELSIZE + PIXELSIZE),fill=Maze.FillCol(nameX),outline=Maze.FillCol(nameX))

        if not imagename.rfind('/') == -1:
            os.makedirs(imagename[:imagename.rfind('/')],exist_ok=True)
        if gifreturn:
            return img
        img.save(imagename, quality=95)

    @classmethod
    def FillCol(cls, point, visited=11, shortest=55):
        if point == cls.WALL:
            return 0
        elif point == cls.ROAD:
            return (255,255,255)
        elif point == cls.START:
            return (0,0,255)
        elif point == cls.GOAL:
            return (255,255,0)
        elif point == visited:
            return (0,255,255)
        elif point == shortest:
            return (255,0,0)