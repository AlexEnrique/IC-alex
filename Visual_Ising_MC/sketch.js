let cols;
let rows;
// let resolution = 25;
let resolution = 5;

let slider;
let stopButton;
let restartButton;
let tempButton;
let ptButton;

var countFlip = 0;
var total = 0;

// Physical variables
let J = -1.0;
let k = 1;
// let k = 1.38064852e-23;
let phaseTransitionTemp = -2*J/(k*Math.log(1+Math.sqrt(2))); // Kelvin
let temperature;
// let temperature = phaseTransitionTemp*3;
let beta;
var lattice;
var E;

function setup() {
  // console.log(phaseTransitionTemp);
  createCanvas(900, 600);
  background(100);

  cols = width / resolution;
  rows = (height-50) / resolution;

  lattice = createLattice(cols, rows);
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      lattice[i][j] = randomSpin();
      // lattice[i][j] = 1;
      // lattice[i][j] = ((i+j) % 2) ? 1:-1;
    }
  }

  initializePicture();
  E = totalEnergy(cols, rows);

  slider = createSlider(0, 5*phaseTransitionTemp, 0.0, 0.05);
  slider.position(100,550);

  tempButton = createButton('Set temperature');
  tempButton.position(100, 575);
  tempButton.mousePressed(function() {
    temperature = slider.value();
    beta = 1 / temperature;
    console.log("Temperature changed to: "+slider.value());
  });

  tempButton = createButton('Phase Transition');
  tempButton.position(250, 575);
  tempButton.mousePressed(function() {
    temperature = phaseTransitionTemp;
    beta = 1 / temperature;
    console.log("Phase Transition Temperature: "+temperature);
  });

  stopButton = createButton('Stop');
  stopButton.position(800, 550);
  stopButton.mousePressed(noLoop);

  restartButton = createButton('Restart');
  restartButton.position(800, 575);
  restartButton.mousePressed(loop);

}

function initializePicture() {
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
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
