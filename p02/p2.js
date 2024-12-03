const data = require('./data.js');

const isValid = r => {
  if (r.length < 2) return true;
  if (r[0] === r[1]) return false;
  for (let i = 1; i < r.length; i++) {
    if (r[0] < r[1] && r[i - 1] >= r[i]) {
      return false;
    }
    if (r[0] > r[1] && r[i - 1] <= r[i]) {
      return false;
    }
    const a = Math.abs(r[i] - r[i - 1]);
    if (a > 3 || a < 1) {
      return false;
    }
  }
  return true;
};

const res = data
  .filter(r => {
    if (isValid(r)) return true;

    for (let i = 0; i < r.length; i++) {
      const n = i == 0 ? r.slice(1) : [...r.slice(0, i), ...r.slice(i + 1)];
      if (isValid(n)) return true;
    }
    return false;
  });

console.log(res.length);

