let cols;
let rows;
let resolution = 10;
let temperature = 5.0;
var lattice;

function setup() {
  createCanvas(800, 600);
  cols = width / resolution;
  rows = height / resolution;

  lattice = createLattice(cols, rows);
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      lattice[i][j] = -1;
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
        // stroke(0);
        noStroke();
        rect(x, y, resolution, resolution);
      }
    }
  }


  // noLoop();

}
