import Maze
import queue
from copy import *
from PIL import Image,ImageDraw
import os

class BFS:
    VISITED = 11
    SHORTEST = 55

    def __init__(self, mapdata, start, goal):
        self.nodeQ = queue.Queue()
        self.mapdata = deepcopy(mapdata)
        self.path = {}
        self.start = deepcopy(start)
        self.goal = deepcopy(goal)
        (self.nowX, self.nowY) = self.goal
        (self.maxX, self.maxY) = (len(self.mapdata[0]), len(self.mapdata))
        self.gifimg = []

        self.mapdata[self.start[1]][self.start[0]] = BFS.VISITED
        self.nodeQ.put(self.start)

    def Start_Search(self,giflog=False):
        print("幅優先探索中・・・")
        while self.Add_Queue():
            if giflog:
                self.gifimg.append(self.Save_Search(giflog,gifreturn=True))

        while not (self.nowX,self.nowY) == self.start:
            self.mapdata[self.path[(self.nowX,self.nowY)][1]][self.path[(self.nowX,self.nowY)][0]] = BFS.SHORTEST
            (self.nowX,self.nowY) = self.path[(self.nowX,self.nowY)]
        self.mapdata[self.start[1]][self.start[0]] = Maze.Maze.START
        self.mapdata[self.goal[1]][self.goal[0]] = Maze.Maze.GOAL

        print("探索完了")

        print("giflogを保存中・・・")
        self.gifimg[0].save(giflog,save_all=True, append_images=self.gifimg[1:], optimize=False, duration=20, loop=0)
        print("giflogを保存しました")

    def Add_Queue(self):
        if not self.nodeQ.empty():
            queueTmp = self.nodeQ.get()

            if self.mapdata[queueTmp[1] - 1][queueTmp[0]] == Maze.Maze.ROAD or self.mapdata[queueTmp[1] - 1][queueTmp[0]] == Maze.Maze.GOAL:
                self.nodeQ.put((queueTmp[0],queueTmp[1] - 1))
                self.mapdata[queueTmp[1] - 1][queueTmp[0]] = BFS.VISITED
                self.path[(queueTmp[0],queueTmp[1] - 1)] = queueTmp

            if self.mapdata[queueTmp[1]][queueTmp[0] + 1] == Maze.Maze.ROAD or self.mapdata[queueTmp[1]][queueTmp[0] + 1] == Maze.Maze.GOAL:
                self.nodeQ.put((queueTmp[0] + 1,queueTmp[1]))
                self.mapdata[queueTmp[1]][queueTmp[0] + 1] = BFS.VISITED
                self.path[(queueTmp[0] + 1,queueTmp[1])] = queueTmp

            if self.mapdata[queueTmp[1] + 1][queueTmp[0]] == Maze.Maze.ROAD or self.mapdata[queueTmp[1] + 1][queueTmp[0]] == Maze.Maze.GOAL:
                self.nodeQ.put((queueTmp[0],queueTmp[1] + 1))
                self.mapdata[queueTmp[1] + 1][queueTmp[0]] = BFS.VISITED
                self.path[(queueTmp[0],queueTmp[1] + 1)] = queueTmp

            if self.mapdata[queueTmp[1]][queueTmp[0] - 1] == Maze.Maze.ROAD or self.mapdata[queueTmp[1]][queueTmp[0] - 1] == Maze.Maze.GOAL:
                self.nodeQ.put((queueTmp[0] - 1,queueTmp[1]))
                self.mapdata[queueTmp[1]][queueTmp[0] - 1] = BFS.VISITED
                self.path[(queueTmp[0] - 1,queueTmp[1])] = queueTmp

            return True
        else:
            return False

    def Save_Search(self, imagename, gifreturn=False):
        PIXELSIZE = 15

        img = Image.new("RGB",(self.maxX * PIXELSIZE + 1,self.maxY * PIXELSIZE + 1),(0))
        draw = ImageDraw.Draw(img)

        for i, nameY in enumerate(self.mapdata):
            for j, nameX in enumerate(nameY):
                draw.rectangle((j * PIXELSIZE,i * PIXELSIZE,j * PIXELSIZE + PIXELSIZE,i * PIXELSIZE + PIXELSIZE),fill=Maze.Maze.FillCol(nameX,visited=BFS.VISITED,shortest=BFS.SHORTEST),outline=Maze.Maze.FillCol(nameX,visited=BFS.VISITED,shortest=BFS.SHORTEST))

        if not imagename.rfind('/') == -1:
            os.makedirs(imagename[:imagename.rfind('/')],exist_ok=True)
        if gifreturn:
            return img
        img.save(imagename, quality=95)