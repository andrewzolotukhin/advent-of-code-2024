string[] numPad = [ "789", "456", "123", "#0A" ];
string[] arrowPad =[ "#^A", "<v>" ]; 
string [] input= [ "480A", "143A", "983A", "382A", "974A" ];

var stateMap = new Dictionary<(char from, char to), IList<string>>();

Solution.GenerateStateMap(numPad, stateMap);
Solution.GenerateStateMap(arrowPad, stateMap);

long result = 0;
foreach (var code in input) {
  var sequence = Solution.GetBestSequenceLength(code, stateMap, 26);
  var num = long.Parse(code.Replace("A", ""));
  result += sequence * num;
}

Console.WriteLine(result);


static class Solution {
  public static List<string> EmptyStateMap = ["A"];
  public static IEnumerable<(int row, int col)> GetPositionsWithValue(string[] layout) {
    for(int i = 0; i < layout.Length; i++) {
      for(int j = 0; j < layout[0].Length; j++) {
        if(layout[i][j] != '#') {
          yield return (i, j);
        }
      }
    }
  }

  public static Dictionary<(string seq, int layer), long> Cache = new Dictionary<(string seq, int layer), long>();

  public static long GetBestSequenceLength(string input, IDictionary<(char from, char to), IList<string>> stateMap, int layer) {

    if(Cache.ContainsKey((input, layer))) {
      return Cache[(input, layer)];
    }

    if(layer == 0) {
      return input.Length;
    }

    var result = 0L;
    var currentState = 'A';
    var nextState = input[0];

    for(int i = 0; i < input.Length; i++) {
      nextState = input[i];
      long shortestSequenceLength = long.MaxValue;
      foreach(var seq in stateMap[(currentState, nextState)]) {
        var r = GetBestSequenceLength(seq, stateMap, layer - 1);
        if(r < shortestSequenceLength) {
          shortestSequenceLength = r;
        }
      }
      result += shortestSequenceLength;
      currentState = nextState;
    }

    Cache[(input, layer)] = result;
    return result;
  }

  public static List<(int dx, int dy)> Directions = [(0, 1), (0, -1), (1, 0), (-1, 0)];
  public static Dictionary<(int dx, int dy), char> DirectionsToMove => new Dictionary<(int dx, int dy), char> {
      [(0, 1)] = '>',
      [(0, -1)] = '<',
      [(1, 0)] = 'v',
      [(-1, 0)] = '^'
    };

  public static IEnumerable<string> GetPaths(string[] layout, (int row, int col) from, (int row, int col) to) {
    if(from == to) {
     yield break;
    }

    List<(int row, int col, int dist, string path, string visited)> queue = [(from.row, from.col, 0 , "", "")];

    while(queue.Count > 0) {
      var item = queue[0];
      queue.RemoveAt(0);

      if(item.dist > Math.Abs(to.row - from.row) + Math.Abs(to.col - from.col)) {
        continue;
      }

      if(item.row == to.row && item.col == to.col) {
        yield return item.path;
        continue;
      }

      foreach(var dir in Directions) {
        var newRow = item.row + dir.dx;
        var newCol = item.col + dir.dy;

        if(newRow < 0 || newRow >= layout.Length || newCol < 0 || newCol >= layout[0].Length) {
          continue;
        }

        if(layout[newRow][newCol] == '#') {
          continue;
        }

        if(!item.visited.Contains(layout[newRow][newCol])) {
          queue.Add((newRow, newCol, item.dist + 1, item.path + DirectionsToMove[dir], item.visited + layout[item.row][item.col]));
        }
      }
    }
  }

  public static void GenerateStateMap(string[] layout, Dictionary<(char from, char to), IList<string>> stateMap) {
    var allPositions = GetPositionsWithValue(layout).ToList();
    for(int i = 0; i < allPositions.Count; i++) {
      for(int j = 0; j < allPositions.Count; j++) {
        var from = allPositions[i];
        var to = allPositions[j];
        var fromValue = layout[from.row][from.col];
        var toValue = layout[to.row][to.col];

        if(i == j) {
          stateMap[(fromValue, toValue)] = EmptyStateMap;
          continue;
        }

        if(fromValue == '#' || toValue == '#') {
          continue;
        }

        stateMap[(fromValue, toValue)] = GetPaths(layout, from, to).Select(t => $"{t}A").ToList();
      }
    }
  }
  
}

