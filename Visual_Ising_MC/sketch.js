let cols;
let rows;
let resolution = 1;

var countFlip = 0;
var total = 0;

// Physical variables
let J = -1.0;
let k = 1;
// let k = 1.38064852e-23;
let phaseTransitionTemp = -2*J/(k*Math.log(1+Math.sqrt(2))); // Kelvin
let temperature = phaseTransitionTemp-0.000001;
let beta = 1/(k*temperature);
var lattice;
var E;

function setup() {
  // console.log(phaseTransitionTemp);
  createCanvas(900, 600);
  cols = width / resolution;
  rows = height / resolution;

  lattice = createLattice(cols, rows);
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      lattice[i][j] = randomSpin();
      lattice[i][j] = -1;
      // lattice[i][j] = ((i+j) % 2) ? 1:-1;
    }
  }

  background(0);
  initializePicture();
  E = totalEnergy(cols, rows);
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
  if (lattice[pos.x][pos.y] == 1)
    fill(255);
  else
    fill(0);

  noStroke();
  rect(pos.x * resolution, pos.y * resolution, resolution, resolution);
  // console.log("E:"+E/(cols*rows));


  // noLoop();

}
