var numPad = new Pad([ "789", "456", "123", "#0A" ]);


var getBest = (string str) => {
  var minLength = int.MaxValue;
  var result = "";
  var numPadRes = numPad.Type(str);
  var count = 0L;
  foreach(var r in numPadRes) {
    var robotPad1 = new Pad([ "#^A", "<v>" ]);
    foreach(var r2 in robotPad1.Type(r)) {
      var robotPad2 = new Pad([ "#^A", "<v>" ]);
      foreach(var r3 in robotPad2.Type(r2)) {
        if(r3.Length < minLength) {
          minLength = r3.Length;
          result = r3;
        }
        count++;
        if(count % 100_000_000 == 0) {
          Console.WriteLine(count);
        }
      }
    }
  }
  return result;
};

string[] inputTest = ["029A", "980A", "179A", "456A", "379A"];
string [] inputReal = [ "480A", "143A", "983A", "382A", "974A" ];

var input = inputReal;

long result = 0;

foreach(var i in input) {
  Console.WriteLine(i);
  var res = getBest(i);
  var num = int.Parse(i.Replace("A", ""));

  result += res.Length * num;
}

Console.WriteLine(result);

  /**
  789
  456
  123
   0A
  */

class Pad {
  public char State {get; protected set; } = 'A';
  protected string[] Layout = [];
  public Dictionary<(char from, char to), IList<string>> StateMap {get; protected set; } = [];

  protected IEnumerable<(int row, int col)> GetPositionsWithValue() {
    for(int i = 0; i < Layout.Length; i++) {
      for(int j = 0; j < Layout[0].Length; j++) {
        if(Layout[i][j] != '#') {
          yield return (i, j);
        }
      }
    }
  }

  protected List<(int dx, int dy)> Directions = [(0, 1), (0, -1), (1, 0), (-1, 0)];
  protected Dictionary<(int dx, int dy), char> DirectionsToMove { get {
    return new Dictionary<(int dx, int dy), char> {
      [(0, 1)] = '>',
      [(0, -1)] = '<',
      [(1, 0)] = 'v',
      [(-1, 0)] = '^'
    };
  } } 

  protected IEnumerable<string> GetPaths((int row, int col) from, (int row, int col) to) {
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

        if(newRow < 0 || newRow >= Layout.Length || newCol < 0 || newCol >= Layout[0].Length) {
          continue;
        }

        if(Layout[newRow][newCol] == '#') {
          continue;
        }

        if(!item.visited.Contains(Layout[newRow][newCol])) {
          queue.Add((newRow, newCol, item.dist + 1, item.path + DirectionsToMove[dir], item.visited + Layout[item.row][item.col]));
        }
      }
    }
  }

  protected void GenerateStateMap() {
    var allPositions = GetPositionsWithValue().ToList();
    for(int i = 0; i < allPositions.Count; i++) {
      for(int j = 0; j < allPositions.Count; j++) {
        if(i == j) {
          continue;
        }

        var from = allPositions[i];
        var to = allPositions[j];
        var fromValue = Layout[from.row][from.col];
        var toValue = Layout[to.row][to.col];

        if(fromValue == '#' || toValue == '#') {
          continue;
        }

        StateMap[(fromValue, toValue)] = GetPaths(from, to).ToList();
      }
    }
  }

  public Pad(string[] layout) {
    State = 'A';
    Layout = layout;

    GenerateStateMap();
  }

  // public static Dictionary<string, List<string>> Cache = new Dictionary<string, List<string>>();

  private IEnumerable<string> TypeInternal(string val, char state) {
    if(string.IsNullOrEmpty(val)) {
      yield break;
    }

    // if(Cache.ContainsKey(val)) {
    //   foreach(var res in Cache[val]) {
    //     yield return res;
    //   }
    //   yield break;
    // }

    // Cache[val] = Cache.ContainsKey(val) ? Cache[val] : new List<string>();

    var newState = val[0];

    if(state == newState) {
      foreach(var rest in TypeInternal(val.Substring(1), newState)) {
        // Cache[val].Add("A" + rest);
        yield return "A" + rest;
      }
    } else 
    {
      foreach(var path in StateMap[(state, newState)]) {
        if(val.Length == 1) {
          // Cache[val].Add(path);
          yield return path + "A";
        }
        foreach(var rest in TypeInternal(val.Substring(1), newState)) {
          // Cache[val].Add(path + rest);
          yield return path + "A" + rest;
        }
      }
    }
  }

  public IEnumerable<string> Type(string str) {
    foreach(var res in TypeInternal(str, State)) {
      yield return res;
    }
  }
}

