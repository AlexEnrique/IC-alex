// variables in the 'variables.js' file

function createLattice(cols, rows) {
  let arr = new Array(cols);
  for (var i = 0; i < arr.length; i++) {
    arr[i] = new Array(rows);
  }

  return arr;
}

function setup() {
  createCanvas(width, height);
  cols = width / resolution;
  rows = height / resolution;

  lattice = createLattice(cols, rows);
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < cols; j++) {
      lattice[i][j] = randomSpin();
    }
  }

  background(0);
}

function draw() {


  fluctuateLattice();

  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < cols; j++) {
      let x = i * resolution;
      let y = j * resolution;
      if (lattice[i][j] == 1) {
        fill(255);
        stroke(0);
        rect(x, y, resolution-1, resolution-1);
      }
    }
  }


  // noLoop();

}
