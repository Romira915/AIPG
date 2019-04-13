import Maze
import BFS

print("(x, y) = ")
(x, y) = (int(input()), int(input()))

maze = Maze.Maze(x,y)

mapdata, start, goal = maze.Generating()
maze.Save_maping("maze.jpg")
print(start,goal)
maze.Show_maping()

bfs = BFS.BFS(mapdata, start, goal)

bfs.Start_Search(giflog="BFS.gif")
bfs.Save_Search("Result.jpg")