// import { field, steps } from "./data-tiny-problem2.js";
//import { field, steps } from './data-test.js';
import { field, steps } from "./data-problem2.js";

const N = field.length;
const M = field[0].length;
const dirs = [
  [0, 1],
  [1, 0],
  [0, -1],
  [-1, 0],
];
const orts = [
  [3, 1],
  [2, 0],
  [3, 1],
  [2, 0],
];
const stod = {
  "^": 3,
  v: 1,
  ">": 0,
  "<": 2,
};

const print = (step, m) => {
  console.log(`Step ${step}: ${m}`);
  for (let i = 0; i < N; i++) {
    console.log(field[i].join(""));
  }
};

let x = 0;
let y = 0;
for (let i = 0; i < N; i++) {
  for (let j = 0; j < M; j++) {
    if (field[i][j] === "@") {
      x = i;
      y = j;
    }
  }
}

const move = (x, y, dx, dy) => {
  let cx = x,
    cy = y;
  let found = false;
  let step = 0;
  while (
    cx > 0 &&
    cx < N - 1 &&
    cy > 0 &&
    cy < M - 1 &&
    field[cx][cy] !== "#"
  ) {
    step++;
    cx += dx;
    cy += dy;
    if (field[cx][cy] === ".") {
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
    field[x][y] = ".";
    x += dx;
    y += dy;
  }

  return { x, y };
};

const moveDoubled = (x, y, dirId, dry) => {
  const [dx, dy] = dirs[dirId];
  let nx = x + dx,
    ny = y + dy;

  const [o1, o2] = orts[dirId];
  const [o1dx, o1dy] = dirs[o1];
  const [o2dx, o2dy] = dirs[o2];

  const leftX = nx + o1dx;
  const leftY = ny + o1dy;
  const rightX = nx + o2dx;
  const rightY = ny + o2dy;

  if (field[nx][ny] === ".") {
    if (!dry) {
      const t = field[x][y];
      field[x][y] = ".";
      field[nx][ny] = t;
    }
    return true;
  }

  if (field[nx][ny] === "[") {
    if (
      moveDoubled(nx, ny, dirId, true) &&
      moveDoubled(rightX, rightY, dirId, true)
    ) {
      if (!dry) {
        moveDoubled(nx, ny, dirId, false);
        moveDoubled(rightX, rightY, dirId, false);
        const t = field[x][y];
        field[x][y] = ".";
        field[nx][ny] = t;
      }
      return true;
    }
    return false;
  }

  if (field[nx][ny] === "]") {
    if (
      moveDoubled(leftX, leftY, dirId, true) &&
      moveDoubled(nx, ny, dirId, true)
    ) {
      if (!dry) {
        moveDoubled(leftX, leftY, dirId, false);
        moveDoubled(nx, ny, dirId, false);
        const t = field[x][y];
        field[x][y] = ".";
        field[nx][ny] = t;
      }
      return true;
    }
    return false;
  }

  // if (field[nx][ny] === '#') {
  return false;
  // }
};

print(0);
for (let s = 0; s < steps.length; s++) {
  const d = stod[steps[s]];
  const [dx, dy] = dirs[d];
  const doubled = d == 1 || d == 3;

  if (doubled) {
    const canMove = moveDoubled(x, y, d, true);
    if (canMove) {
      moveDoubled(x, y, d, false);
      x += dx;
      y += dy;
    }
  } else {
    let t = move(x, y, dx, dy);
    x = t.x;
    y = t.y;
  }

  print(s + 1, steps[s]);
}

let result = 0;

for (let i = 1; i < N - 1; i++)
  for (let j = 1; j < M - 1; j++) {
    if (field[i][j] === "[") {
      result += 100 * i + j;
    }
  }

console.log(result);
