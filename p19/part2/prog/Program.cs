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
  result += Helper.TryMatch(s, prefixes);
  Console.WriteLine($"after \"{s}\": {result}");
}

Console.WriteLine(result);

internal static class Helper {
  public static Dictionary<string, long> dp = [];

  public static long TryMatch(string s, Dictionary<string, bool> prefixes) {
  if(s == string.Empty)  {
    return 1;
  };
  if(dp.ContainsKey(s)) {
    return dp[s]; 
  } 

  var lresult = 0L;

  foreach(var key in prefixes.Keys) {
    if(s.StartsWith(key)) {
      lresult+= TryMatch(s.Substring(key.Length), prefixes);
    }
  }
  dp.TryAdd(s, lresult);
  return lresult;
}
}
