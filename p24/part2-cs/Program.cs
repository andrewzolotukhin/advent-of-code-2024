// using to have BitArray
using System.Collections;
using System.Text.RegularExpressions;


// Dictionary<string, Operation> registers = new Dictionary<string, Operation>();

// void MarkNoEvaluated(string name) {
//   var operation = registers[name];
//   if (operation.Type == OperationType.Constant) {
//     return;
//   }
//
//   operation.IsEvaluated = false;
//   if(operation.Operand1 != null) {
//     MarkNoEvaluated(operation.Operand1);
//   }
//
//   if(operation.Operand2 != null) {
//     MarkNoEvaluated(operation.Operand2);
//   }
//
//   registers[name] = operation;
// }
//
// void Evaluate(string name) {
//   var operation = registers[name];
//   if (operation.IsEvaluated) {
//     return;
//   }
//
//   if (operation.Type == OperationType.Constant) {
//     return;
//   } 
//
//   var leftRegister = registers[operation.Operand1!];
//   var rightRegister = registers[operation.Operand2!];
//
//   if (!leftRegister.IsEvaluated) {
//     Evaluate(operation.Operand1!);
//   }
//
//   if (!rightRegister.IsEvaluated) {
//     Evaluate(operation.Operand2!);
//   }
//
//   leftRegister = registers[operation.Operand1!];
//   rightRegister = registers[operation.Operand2!];
//
//   if (leftRegister.IsEvaluated && rightRegister.IsEvaluated) {
//     if (operation.Type == OperationType.And) {
//       operation.Value = leftRegister.Value & rightRegister.Value;
//     }
//
//     if (operation.Type == OperationType.Or) {
//       operation.Value = leftRegister.Value | rightRegister.Value;
//     }
//
//     if (operation.Type == OperationType.Xor) {
//       operation.Value = leftRegister.Value ^ rightRegister.Value;
//     }
//
//   } 
//
//   operation.IsEvaluated = true;
//   registers[name] = operation;
// }

// long CalculateSum(long x, long y,
//                                 List<string> zregisters,
//                                 List<string> xregisters,
//                                 List<string> yregisters) {
//   BitArray bx = new BitArray(BitConverter.GetBytes((x)));
//   BitArray by = new BitArray(BitConverter.GetBytes(y));
//   for (int i = 0; i < xregisters.Count; i++) {
//     var registerName = xregisters[xregisters.Count - 1 - i];
//     registers[registerName] = new Operation { Type = OperationType.Constant, Operand1 = registerName, Operand2 = null, Value = bx[i], IsEvaluated = true };
//   }
//
//   for (int i = 0; i < yregisters.Count; i++) {
//     var registerName = yregisters[yregisters.Count - 1 - i];
//     registers[registerName] =  new Operation { Type = OperationType.Constant, Operand1 = registerName, Operand2 = null, Value = by[i], IsEvaluated = true };
//   }
//
//   foreach (var reg in registers) {
//     if (reg.Value.Type != OperationType.Constant) {
//       registers[reg.Key].IsEvaluated = false;
//     }
//   }
//
//   foreach (var reg in registers) {
//     if (!reg.Value.IsEvaluated) {
//       Evaluate(reg.Key);
//     }
//   }

//   long result = 0L;
//   for (int i = 0; i < zregisters.Count; i++) {
//     var registerName = zregisters[i];
//     var operation = registers[registerName];
//     result <<= 1;
//     result |= (long)(operation.Value ? 1 : 0);
//   }
//
//   return result;
// }
//
Dictionary<string, Pin> pins = new();
Dictionary<string, Pin> zpins = new();
Dictionary<string, Pin> xpins = new();
Dictionary<string, Pin> ypins = new();
List<Joint> joints = new();


void AddAllDependentJoints(Pin pin, Dictionary<int, HashSet<Joint>> jointsFound, int level = 0) {
  foreach(var joint in pin.Using) {
    if(jointsFound.ContainsKey(level)) {
      jointsFound[level].Add(joint);
    } else {
      jointsFound[level] = new HashSet<Joint> { joint };
    }
    if(joint.Operand1 != null) {
      AddAllDependentJoints(joint.Operand1, jointsFound, level + 1);
    }
    if(joint.Operand2 != null) {
      AddAllDependentJoints(joint.Operand2, jointsFound, level + 1);
    }
  }
}

List<(Joint, Joint)> GeneratePairs(List<Joint> elements) {
  List<(Joint, Joint)> pairs = [];
  int n = elements.Count;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      pairs.Add((elements[i], elements[j]));
    }
  }
  return pairs;
}

List<(Joint, Joint)> GenerateCombinations(
    List<(Joint, Joint)> pairs,
    List<(Joint, Joint)> current, 
    int index, 
    int maxLength,
    Func<List<(Joint, Joint)>, bool> callback
    ) {
  // If the current combination length is within bounds, store it
  if (current.Count > 0 && current.Count <= maxLength) {
    if (callback(current)) {
      return current;
    }
  }

  // Stop recursion if we exceed bounds
  if (current.Count == maxLength || index >= pairs.Count) {
    return [];
  }

  for (int i = index; i < pairs.Count; ++i) {
    // Check if the current pair overlaps with existing pairs
    var overlaps = false;
    foreach (var p in current) {
      if (p.Item1 == pairs[i].Item1 || p.Item1 == pairs[i].Item2 ||
          p.Item2 == pairs[i].Item1 || p.Item2 == pairs[i].Item2) {
        overlaps = true;
        break;
      }
    }

    if (!overlaps) {
      // Add the current pair and recurse
      current.Add(pairs[i]);
      var r = GenerateCombinations(pairs, current, i + 1, maxLength, callback);
      if (r.Count > 0) {
        return r;
      }
      current.RemoveAt(current.Count - 1);
    }
  }

  return [];
}

List<(Joint, Joint)> GenerateAllPairCombinations(
    List<Joint> elements,
    Func<List<(Joint pin1, Joint pin2)>, bool> callback,
    int maxLength = 4) {

  // Generate all unique pairs
  var pairs = GeneratePairs(elements);

  // Generate all combinations of pairs
  List<(Joint, Joint)> current = [];
  return GenerateCombinations(pairs, current, 0, maxLength, callback);
}

// void InEvaluateRegister(string reg, HashSet<string> inevaluated) {
//   var operation = registers[reg];
//   // if registers contains `reg`
//   if (operation.Type == OperationType.Constant || inevaluated.Contains(reg)) {
//     return;
//   }
//   operation.IsEvaluated = false;
//   registers[reg] = operation;
//   inevaluated.Add(reg);
//   InEvaluateRegister(operation.Operand1!, inevaluated);
//   InEvaluateRegister(operation.Operand2!, inevaluated);
// }

// List<string> zregisters = [], xregisters = [], yregisters = [];

string line;

while (true) {
  line = Console.ReadLine()!;

  if(string.IsNullOrEmpty(line)) {
    break;
  }

  // parse string like "somestr: %d"
  var registryRegex = new Regex(@"(?<name>[^:]+): (?<value>\d+)");
  var parseResult = registryRegex.Match(line);

  var name = parseResult.Groups["name"].Value;
  var value = int.Parse(parseResult.Groups["value"].Value);

  // if(name.StartsWith("z")) {
  //   zregisters.Add(name);
  // } else if(name.StartsWith("x")) {
  //   xregisters.Add(name);
  // } else if(name.StartsWith("y")) {
  //   yregisters.Add(name);
  // }
  // registers[name] = new Operation { Type = OperationType.Constant, Operand1 = name, Operand2 = null, Value = value == 1, IsEvaluated = true };

  var pin = new Pin(name);
  pin.SetValue(value == 1);

  pins[name] = pin;
  if(name.StartsWith("z")) {
    zpins[name] = pin;
  } else if(name.StartsWith("x")) {
    xpins[name] = pin;
  } else if(name.StartsWith("y")) {
    ypins[name] = pin;
  }
}

// until EOF read dependant values
while(Console.In.Peek() > 0) {
  // parse string like "ntg XOR fgs -> mjb"
  
  var l = Console.ReadLine()!;
  var regex = new Regex(@"(?<operand1>[^ ]+) (?<operation>[^ ]+) (?<operand2>[^ ]+) -> (?<result>[^\n]+)");

  var r = regex.Match(l);
  var operand1 = r.Groups["operand1"].Value;
  var operand2 = r.Groups["operand2"].Value;
  var operation = r.Groups["operation"].Value switch {
    "AND" => OperationType.And,
    "OR" => OperationType.Or,
    "XOR" => OperationType.Xor,
    _ => OperationType.Constant
  };
  var res= r.Groups["result"].Value;


  // registers[res] = new Operation { Type = operation, Operand1 = operand1, Operand2 = operand2, Value = false, IsEvaluated = false };

  // if (res.StartsWith('z')) {
  //   zregisters.Add(res);
  // }
  
  if(!pins.ContainsKey(res)) {
    var pin = new Pin(res);
    pins.Add(res, pin);
  } 

  if(!pins.ContainsKey(operand1)) {
    var pin = new Pin(operand1);
    pins.Add(operand1, pin);
  }

  if(!pins.ContainsKey(operand2)) {
    var pin = new Pin(operand2);
    pins.Add(operand2, pin);
  }

  if(res.StartsWith("z")) {
    zpins.Add(res, pins[res]);
  }

  var joint = new Joint();
  joint.SetType(operation).SetOperand1(pins[operand1]).SetOperand2(pins[operand2]).SetOutput(pins[res]);
  joints.Add(joint);
}

// foreach (var reg in registers) {
//   if (!reg.Value.IsEvaluated) {
//     Evaluate(reg.Key);
//   }
// }

ulong result = 0L;
ulong X = 0L, Y = 0L, Z = 0L;

// order xpins in descending order
var xPins = xpins.Keys.OrderByDescending(x => x).ToList();
var yPins = ypins.Keys.OrderByDescending(x => x).ToList();
var zPins = zpins.Keys.OrderByDescending(x => x).ToList();

foreach(var name in xPins) {
  var pin = xpins[name];
  X <<= 1;
  X |= (ulong)(pin.Value ? 1L : 0L);
}

foreach(var name in yPins) {
  var pin = ypins[name];
  Y <<= 1;
  Y |= (ulong)(pin.Value ? 1L : 0L);
}

foreach(var name in zPins) {
  var pin = zpins[name];
  Console.WriteLine($"{name} = {pin.Value}");
  Z <<= 1;
  Z |= (ulong)(pin.Value ? 1L : 0L);
}

Console.WriteLine($"{X} + {Y} = {Z}");

static string BitArrayToBinaryString(BitArray bitArray)
{
    char[] binaryChars = new char[bitArray.Count];
    for (int i = 0; i < bitArray.Count; i++)
    {
        binaryChars[i] = bitArray[i] ? '1' : '0';
    }
    return new string(binaryChars.Reverse().ToArray());
} 

ulong target = X + Y;

ulong diff = target ^ result;

BitArray bdiff = new BitArray(BitConverter.GetBytes(diff));
Console.WriteLine($"Diff (binary): {BitArrayToBinaryString(new BitArray(BitConverter.GetBytes(diff)))}");
Console.WriteLine($"Ress (binary): {BitArrayToBinaryString(new BitArray(BitConverter.GetBytes(result)))}");

HashSet<Pin> wrongZregisters = new(), correctZregisters = new();
for (int i = 0; i < zPins.Count; i++) {
  if (bdiff[i]) {
    wrongZregisters.Add(pins[zPins[^(i+1)]]);
  } else {
    correctZregisters.Add(pins[zPins[^(i+1)]]);
  }
}

Dictionary<int, HashSet<Joint>> possiblyWrongJoints = new(), correctJoints = new();

foreach (var wz in wrongZregisters) {
  AddAllDependentJoints(wz, possiblyWrongJoints);
}

foreach (var cr in correctZregisters) {
  AddAllDependentJoints(cr, correctJoints);
}

// Console.WriteLine($"possiblyWrongJoints: {correctJoints.Count}");

// foreach (var cr in correctJoints) {
//   possiblyWrongJoints.Remove(cr);
// }

 Console.WriteLine($"correctJoints: {correctJoints.Count}");
 Console.WriteLine($"possiblyWrongJoints: {possiblyWrongJoints.Count}");

var trySwap = (List<(Joint joint1, Joint joint2)> pairs) => {
  for (int i = 0; i < pairs.Count; i++) {
    var pair = pairs[i];

    if(pair.joint1.Output == pair.joint2.Output) {
      continue;
    }
    Console.Write($"({pair.joint1.Output!.Name}, {pair.joint2.Output!.Name}), ");

    Pin j1o = pair.joint1.Output!;
    Pin j2o = pair.joint2.Output!;
    pair.joint2.SetOutput(j1o);
    pair.joint1.SetOutput(j2o);
  }


  ulong newResult = 0L;

  foreach (var reg in zPins) {
    var pin = pins[reg];
    newResult <<= 1;
    newResult |= (ulong)(pin.Value ? 1L : 0L);
  }

  Console.WriteLine($" = {newResult}");

  if (newResult == target) {
    return true;
  }

  for (int i = 0; i < pairs.Count; i++) {
    var pair = pairs[i];

    if(pair.joint1.Output == pair.joint2.Output) {
      continue;
    }
    Console.Write($"({pair.joint1.Output!.Name}, {pair.joint2.Output!.Name}), ");

    Pin j1o = pair.joint1.Output!;
    Pin j2o = pair.joint2.Output!;
    pair.joint2.SetOutput(j1o);
    pair.joint1.SetOutput(j2o);
  }

  return false;
};

List<Joint> possiblyWrongRegistersVector = new();

foreach(var key in possiblyWrongJoints.Keys) {
  foreach(var joint in possiblyWrongJoints[key]) {
    possiblyWrongRegistersVector.Add(joint);
  }
  Console.WriteLine($"Level {key}: {possiblyWrongJoints[key].Count}");
  var permutation =
      GenerateAllPairCombinations(possiblyWrongRegistersVector, trySwap);

  if (permutation.Count == 0) {
    Console.WriteLine("No solution found");
  } else {
    foreach (var pair in permutation) {
      Console.Write($"({pair.Item1}, {pair.Item2}), ");
    }
    Console.WriteLine("Found!");
    break;
  }
}


enum OperationType {
  Constant = 0,
  And,
  Or,
  Xor
}

record Operation {
  public OperationType Type;
  public   string? Operand1;
  public   string? Operand2;
  public   bool Value;
  public   bool IsEvaluated;
};

delegate void PinValueChangeHandler(bool value);

class Pin {
  public readonly string Name;

  public bool Value { get; private set; }
  public Pin SetValue(bool value) {
    Value = value;
    if (OnChange != null) {
      OnChange(value);
    }
    return this;
  }

  private List<Joint> _consumedBy = new();
  public IReadOnlyList<Joint> ConsumedBy {get { return _consumedBy; }}

  public Pin AddConsumer(Joint consumer) {
    _consumedBy.Add(consumer);
    return this;
  }

  public List<Joint> _using = new();
  public IReadOnlyList<Joint> Using { get { return _using; }  }

  public Pin AddUser(Joint user) {
    _using.Add(user);
    return this;
  }

  public Pin RemoveUser(Joint user) {
    _using.Remove(user);
    return this;
  }

  public Pin RemoveConsumer(Joint consumer) {
    _consumedBy.Remove(consumer);
    return this;
  }

  public Pin(string name) {
    Name = name;
  }

  public event PinValueChangeHandler? OnChange;
}

class Joint {
  public OperationType Type { get; private set; }

  public Joint SetType(OperationType type) {
    Type = type;
    return this;
  }

  public Pin? Output {get; private set;}
  
  public Joint SetOutput(Pin output) {
    if(output is null) {
      throw new Exception("Output is not set");
    }
    if(Output != null) {
      Output.RemoveUser(this);
    }
    Output = output;
    Output.AddUser(this);
    if((Operand1 is not null) && (Operand2 is not null) && (Output is not null)) {
      Output.SetValue(GetValue());
    }
    return this;
  }

  private bool GetValue() {
    if(Operand1 == null) {
      throw new Exception("Operand1 is not set");
    }

    if(Operand2 == null) {
      throw new Exception("Operand2 is not set");
    }
    
    return Type switch {
      OperationType.And => Operand1.Value & Operand2.Value,
      OperationType.Or => Operand1.Value | Operand2.Value,
      OperationType.Xor => Operand1.Value ^ Operand2.Value,
      _ => false
    };
  }

  private void OnChange(bool value) {
      if(Output == null) {
        throw new Exception("Output is not set");
      }
      Output.SetValue(GetValue());
  }

  public Pin? Operand1 { get; private set; }

  public Joint SetOperand1(Pin operand1) {
    if(Operand1 != null) {
      Operand1.OnChange -= OnChange;
      Operand1.RemoveConsumer(this);
    }
    Operand1 = operand1;
    Operand1.OnChange += OnChange;
    Operand1.AddConsumer(this);
    if((Operand1 is not null) && (Operand2 is not null) && (Output is not null)) {
      Output.SetValue(GetValue());
    }
    return this;
  }

  public Pin? Operand2 { get; private set; }

  public Joint SetOperand2(Pin operand2) {
    if(Operand2 != null) {
      Operand2.OnChange -= OnChange;
      Operand2.RemoveConsumer(this);
    }
    Operand2 = operand2;
    Operand2.OnChange += OnChange;
    Operand2.AddConsumer(this);
    if((Operand1 is not null) && (Operand2 is not null) && (Output is not null)) {
      Output.SetValue(GetValue());
    }
    return this;
  }
}

