
var graph = new Dictionary<string, List<string>>();

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

HashSet<string> result = new HashSet<string>();

foreach(var vertex1 in graph.Keys)
{
    foreach(var vertex2 in graph[vertex1])
    {
        if(vertex1 == vertex2)
        {
            continue;
        }
        foreach(var vertex3 in graph[vertex2])
        {
            if(vertex3 == vertex1 || vertex3 == vertex2)
            {
                continue;
            }

            // if they are connected -> add to result
            if(graph[vertex3].Contains(vertex1) && (vertex1.StartsWith('t') || vertex2.StartsWith('t') || vertex3.StartsWith('t')))
            {
                var keys = ((List<string>)[vertex1, vertex2, vertex3]);
                keys.Sort();
                result.Add(string.Join("-", keys));
            }
        }
    }
}

Console.WriteLine(result.Count);

