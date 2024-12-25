List<List<int>> maze = new();

const int MAX_CHEATING_WINDOW = 20;
const int CHEATING_THRESHOLD = 100;

// until EOF read the maze

while (true)
{
    var line = Console.ReadLine();
    if (line == null)
    {
        break;
    }
    maze.Add(line.ToCharArray().Select(t => t == '#' ? -1 : (t == 'S' ? 1 : (t == 'E' ? 2 : 0))).ToList());
}

int N = maze.Count;
int M = maze[0].Count;

// find the start and end points (S and E)
int startX = 0, startY = 0, endX = 0, endY = 0;
for (int i = 0; i < N; i++)
{
    for (int j = 0; j < M; j++)
    {
        if (maze[i][j] == 1)
        {
            startX = i;
            startY = j;
            maze[i][j] = 1;
            
        }
        if (maze[i][j] == 2)
        {
            endX = i;
            endY = j;
            maze[i][j] = 0;
        }
    }
}

List<(int dx, int dy)> directions = [ (0, 1), (1, 0), (0, -1), (-1, 0) ];

var getCheats = (int x, int y) => {
  HashSet<(int x, int y)> visited = new();
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      var distance = Math.Abs(i - x) + Math.Abs(j - y);
      if(distance > MAX_CHEATING_WINDOW) {
        continue;
      }
      if(maze[i][j] - maze[x][y] - distance >= CHEATING_THRESHOLD) {
        visited.Add((i, j));
      }
    }
  }

  return visited.Count;
};

var fillBestPath = () => {
  (int x, int y) currentPoint = (startX, startY);

  while (currentPoint != (endX, endY))
  {
      foreach (var direction in directions)
      {
          (int x, int y) next = (currentPoint.x + direction.dx, currentPoint.y + direction.dy);

          if (maze[next.x][next.y] == 0 && next != (startX, startY))
          {
              maze[next.x][next.y] = maze[currentPoint.x][currentPoint.y] + 1;
              currentPoint = next;
              break;
          }
      }
  } 
};


fillBestPath();

var result = 0L;

for(int i = 0; i < N; i++) {
  for(int j = 0; j < M; j++) {
    if(maze[i][j] < 0) {
      continue;
    }

    result += getCheats(i, j);
  }
}

Console.WriteLine($"Result: {result}");

