var program = new List<int> { 2, 4, 1, 7, 7, 5, 1, 7, 4, 6, 0, 3, 5, 5, 3, 0 };
// var program = new List<int> { 0, 3, 5, 4, 3, 0 };
string target = string.Join("", program);

  // Console.WriteLine(Solution.Solve(66245665, 0, 0));

  long completed = 0;

  long upperBound = long.MaxValue;
  long lowerBound = 2148296001543L;
  // long lowerBound = 2146196000086L;
  
  LongEnumerable.Range(lowerBound, upperBound)
  .AsParallel().WithDegreeOfParallelism(30).ForAll(i => {
    Interlocked.Increment(ref completed);
    if(completed % 100000000L == 0) {
      Console.WriteLine($"Completed: {completed} - {i} ({(((double)completed / (upperBound - lowerBound))):F2})");
    }
    try {
    if (Solution.Solve(program, i, 0, 0).ToString() == target) {
      Console.WriteLine($"Found: {i}");
      Console.Error.WriteLine($"Found: {i}");
    }
    } catch(Exception e) {
      Console.WriteLine($"Error: {i} - {e.Message}");
    }
  });

public static class LongEnumerable
{
    public static IEnumerable<long> Range(long start, long end)
    {
        for (long i = start; i <= end; i++)
            yield return i;
    }
}

public class Solution
{
    public static string Solve(List<int> program, long A, long B, long C)
    {

        long ReadCombo(int x) => x switch
        {
            4 => A,
            5 => B,
            6 => C,
            7 => throw new InvalidOperationException("unknown combo"),
            _ => x
        };

        var output = new List<int>();

        string GetResult() => string.Join("", output);
         // output.Aggregate(0L, (res, digit) => res * 10L + digit);

        int ip = 0;

        while (ip < program.Count)
        {
            var opcode = program[ip];
            ip++;
            if (ip > program.Count - 1)
                return GetResult();

            switch (opcode)
            {
                case 0:
                    {
                        A = (long) Math.Truncate(A /Math.Pow(2, ReadCombo(program[ip])));
                        ip++;
                        break;
                    }
                case 1:
                    {
                        B ^= program[ip];
                        ip++;
                        break;
                    }
                case 2:
                    {
                        B = ReadCombo(program[ip]) % 8;
                        ip++;
                        break;
                    }
                case 3:
                    {
                        var addr = program[ip];
                        if(A == 0) {
                          ip++;
                        } else {
                          ip = addr;
                        }
                        break;
                    }
                case 4:
                    {
                        B ^= C;
                        ip++;
                        break;
                    }
                case 5:
                    {
                        var r = ReadCombo(program[ip]) % 8;
                        ip++;
                        output.Add((int)r);
                        break;
                    }
                case 6:
                    {
                        B = (long)Math.Truncate(A /  Math.Pow(2, ReadCombo(program[ip])));
                        ip++;
                        break;
                    }
                case 7:
                    {
                        C = (long)Math.Truncate(A / Math.Pow(2, ReadCombo(program[ip])));
                        ip++;
                        break;
                    }
                default:
                    throw new InvalidOperationException($"unknown opcode: {opcode}");
            }
        }

        return GetResult();
    }
}

