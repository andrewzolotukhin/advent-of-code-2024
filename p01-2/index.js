// var data = [....]
// see prolem 01-1
// the same data

const f = new Map();
let r = 0;

for (let i = 0; i < data.length; i++) {
  const [, b] = data[i];

  if (f.has(b)) {
    f.set(b, f.get(b) + 1);
  } else {
    f.set(b, 1);
  }
}

for (let i = 0; i < data.length; i++) {
  const [a,] = data[i];
  const j = f.has(a) ? f.get(a) : 0;
  r += j * a;
}

console.log(r);

