string prefixesStr = Console.ReadLine()!;

var prefixes = prefixesStr.Split(", ", 
    StringSplitOptions.RemoveEmptyEntries)
.ToDictionary(t => t, t => true);

var maxKeyLength = prefixes.Keys.Max(t => t.Length);

List<string> input = [];

// read until EOF
while (true)
{
    string? line = Console.ReadLine();
    if (line == null)
    {
        break;
    }
    if(!string.IsNullOrEmpty(line)) {
      input.Add(line);
    }
}

long result = 0;


foreach(var s in input) {
  if(Helper.TryMatch(s, prefixes)) {
    result++;
  }
}

Console.WriteLine(result);

internal static class Helper {
  public static Dictionary<string, bool> dp = [];

  public static bool TryMatch(string s, Dictionary<string, bool> prefixes) {
  if(s == string.Empty) return true;
  if(dp.ContainsKey(s)) return dp[s];
  foreach(var key in prefixes.Keys) {
    if(s.StartsWith(key)) {
      if(TryMatch(s.Substring(key.Length), prefixes)) {
        dp.Add(s, true);
        return true;
      }
    }
  }
        dp.Add(s, false);
  return false;
}
}
