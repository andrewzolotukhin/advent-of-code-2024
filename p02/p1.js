const data = require('./data.js');

const res = data.filter(r => r[0] !== r[1])
  .filter(r => {
    if (r.length < 2) return true;
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
  });

console.log(res.length);
