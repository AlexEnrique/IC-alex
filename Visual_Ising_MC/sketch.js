let cols;
let rows;
let resolution = 10;

var countFlip = 0;
var total = 0;

// Physical variables
let J = 1.0;
let phaseTransitionTemp = Math.log(Math.sqrt(2) + 1)/2; // Kelvin
let temperature = 1.0E-50; // Kelvin
let k = 1.38064852e-23;
let beta = 1/(k*temperature);
var lattice;

function setup() {
  createCanvas(400, 300);
  cols = width / resolution;
  rows = height / resolution;

  lattice = createLattice(cols, rows);
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      lattice[i][j] = randomSpin();
      // lattice[i][j] = -1;
    }
  }

  background(0);
  initializePicture();
}

function initializePicture() {
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < cols; j++) {
      let x = i * resolution;
      let y = j * resolution;
      if (lattice[i][j] == 1)
        fill(255);
      else
        fill(0);
        // stroke(0);
        noStroke();
        rect(x, y, resolution, resolution);

    }
  }
}

function draw() {
  var fliped = fluctuateLattice();
  total++;
  if (fliped) {
    countFlip++;
    if (lattice[pos.x][pos.y] == 1)
      fill(255);
    else
      fill(0);

    noStroke();
    rect(pos.x * resolution, pos.y * resolution, resolution, resolution);
  }

  console.log("F:"+(countFlip/total));


  // noLoop();

}
