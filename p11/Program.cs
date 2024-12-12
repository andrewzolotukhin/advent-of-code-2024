/*
If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
*/


List<long> i1 = [0, 1, 10, 99, 999];
List<long> i2 = [125, 17];
List<long> i3 = [1750884, 193, 866395, 7, 1158, 31, 35216, 0];

var input = i3;
var steps = 75;

var res = 0L;

foreach (var i in input)
{
	res += Helper.Process(i, steps);
}

Console.WriteLine(res);

static class Helper
{

	public static Dictionary<(long v, int step), long> MEM = new();

	public static IList<long> Simulate(long stone)
	{
		var stones = new List<long>();
		var s = stone.ToString();
		if (stone == 0)
		{
			stones.Add(1);
		}
		else if (s.Length % 2 == 0)
		{
			var l = s.Substring(0, s.Length / 2);
			var r = s.Substring(s.Length / 2);
			stones.Add(long.Parse(l));
			stones.Add(long.Parse(r));
		}
		else
		{
			stones.Add(stone * 2024);
		}
		return stones;
	}

	public static long Process(long stone, int step)
	{
		if (step == 0)
		{
			return 1;
		}
		long result = 0;

		if (MEM.TryGetValue((stone, step), out var k))
		{
			return k;
		}
		else
		{
			var simulation = Simulate(stone);
			foreach (var s in simulation)
			{
				result += Process(s, step - 1);
			}
			MEM[(stone, step)] = result;
		}

		return result;
	}
}
