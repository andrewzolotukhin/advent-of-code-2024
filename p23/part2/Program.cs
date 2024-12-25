var graph = new Dictionary<string, HashSet<string>>();

// read until EOF
while (Console.In.Peek() != -1)
{
    // read a line
    string line = Console.ReadLine()!;
    // write the line to the console
    
    var splitted = line.Split("-", StringSplitOptions.RemoveEmptyEntries);

    if(graph.ContainsKey(splitted[0]))
    {
        graph[splitted[0]].Add(splitted[1]);
    }
    else
    {
        graph.Add(splitted[0], [splitted[1]]);
    }

    if(graph.ContainsKey(splitted[1]))
    {
        graph[splitted[1]].Add(splitted[0]);
    }
    else
    {
        graph.Add(splitted[1], [splitted[0]]);
    }
}


int maxClique = 0;
var result = "";

void FindMaxClique(HashSet<string> current, HashSet<string> candidates, HashSet<string> others, ref int max) {
  if (candidates.Count == 0 && others.Count == 0) {
    if (current.Count > max) {
      max = current.Count;
      result = string.Join(",", current.Order());
    }
    return;
  }

  foreach (var candidate in candidates) {
    var newCurrent = new HashSet<string>(current);
    newCurrent.Add(candidate);

    var newCandidates = new HashSet<string>(candidates);
    newCandidates.IntersectWith(graph[candidate]);

    var newOthers = new HashSet<string>(others);
    newOthers.IntersectWith(graph[candidate]);

    FindMaxClique(newCurrent, newCandidates, newOthers, ref max);

    candidates.Remove(candidate);
    others.Add(candidate);
  }
}

FindMaxClique(new HashSet<string>(), new HashSet<string>(graph.Keys), new HashSet<string>(), ref maxClique);

Console.WriteLine(maxClique);
Console.WriteLine(result);

