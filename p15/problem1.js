//import { field, steps } from './data-tiny.js';
//import { field, steps } from './data-test.js';
import { field, steps } from './data.js';

const N = field.length;
const M = field[0].length;
const dirs = [[0, 1], [1, 0], [0, -1], [-1, 0]];
const stod = {
  '^': 3,
  'v': 1,
  '>': 0,
  '<': 2
};
const dir = 0;

const print = (step, m) => {
  // console.log(`Step ${step}: ${m}`);
  //  for(let i = 0; i < M; i++) {
  //    console.log(field[i].join(''));
  //      }
};

let x = 0;
let y = 0;
for (let i = 0; i < M; i++) {
  for (let j = 0; j < N; j++) {
    if (field[i][j] === '@') {
      x = i;
      y = j;
    }
  }
}

print(0);
for (let s = 0; s < steps.length; s++) {
  const d = stod[steps[s]];
  const [dx, dy] = dirs[d];

  let cx = x, cy = y;
  let found = false;
  let step = 0;
  while (cx > 0 && cx < M - 1 && cy > 0 && cy < N - 1 && field[cx][cy] !== '#') {
    step++;
    cx += dx;
    cy += dy;
    if (field[cx][cy] === '.') {
      found = true;
      break;
    }
  }

  if (found) {
    cx = x + step * dx;
    cy = y + step * dy;
    while (step--) {
      field[cx][cy] = field[cx - dx][cy - dy];
      cx -= dx;
      cy -= dy;
    }
    field[x][y] = '.';
    x += dx;
    y += dy;
  }

  print(s + 1, steps[s]);
}

let result = 0;

for (let i = 1; i < M - 1; i++)
  for (let j = 1; j < N - 1; j++) {
    if (field[i][j] === 'O') {
      result += 100 * i + j;
    }
  }

console.log(result);

