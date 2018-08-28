let cols;
let rows;
// let resolution = 25;
// let resolution = 5;
let resolution = 10;

// Slider, buttons, etc.
let slider;
let stopButton;
let restartButton;
let tempButton;
let ptButton;
let resetButton;
let startButton;
let inpT;
var sliderORbox;
let spinSelect;
// let

// var countFlip = 0;
// var total = 0;

// Physical variables
let J = 1.0;
let k = 1;
// let k = 1.38064852e-23;
let phaseTransitionTemp = 2*Math.abs(J)/(k*Math.log(1+Math.sqrt(2))); // Kelvin
let temperature = 0.0005;
// let temperature = phaseTransitionTemp*3;
let beta;
var lattice;
var E;
var B = 0;

function setup() {
  // console.log(phaseTransitionTemp);
  createCanvas(900, 620);
  background(50);

  cols = width / resolution;
  rows = (height-70) / resolution;

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


  // Temperature
  textSize(12);
  fill(255);
  text('Temperature box', 10, 600);
  text('Temperature slider', 10, 575);

  slider = createSlider(0.00005, 5*phaseTransitionTemp, 0.00005, 0.00005);
  slider.position(120,560);
  slider.changed(function() {
    sliderORbox = 0;
    console.log("Slider -- temperature: "+slider.value());
  });

  inpT = createInput('');
  inpT.size(110, 15);
  inpT.position(130,585);
  inpT.input(function() {
    sliderORbox = 1;
  });

  tempButton = createButton('Set temperature');
  tempButton.position(272.3, 560);
  tempButton.mousePressed(function() {
    if (sliderORbox) {
      temperature = float(inpT.value());
    } else {
      temperature = slider.value();
    }

    beta = 1 / temperature;
    console.log("Temperature changed to: "+temperature);
  });

  ptButton = createButton('Phase Transition');
  ptButton.position(270, 590);
  ptButton.mousePressed(function() {
    temperature = phaseTransitionTemp;
    beta = 1 / temperature;
    console.log("Phase transition. Temperature: "+temperature);
  });

  // Divide
  rect(400, 555, 1.5, 60);

  // Spins and magnetic field
  textSize(12);
  fill(255);
  text('Spins arrangement: ', 420, 572.5);

  spinSelect = createSelect();
  spinSelect.position(530, 560);
  spinSelect.option('Random');
  spinSelect.option('Paralel');
  spinSelect.option('Anti-paralel');
  spinSelect.changed(function() {
    var option = spinSelect.value();
    if (option == "Random") {
      for (let i = 0; i < cols; i++) {
        for (let j = 0; j < rows; j++) {
          lattice[i][j] = randomSpin();
        }
      }

    } else if (option == "Paralel") {
      for (let i = 0; i < cols; i++) {
        for (let j = 0; j < rows; j++) {
          lattice[i][j] = -1;
        }
      }

    } else if (option == "Anti-paralel") {
      for (let i = 0; i < cols; i++) {
        for (let j = 0; j < rows; j++) {
          lattice[i][j] = ((i+j) % 2) ? 1:-1;
        }
      }
    }

    initializePicture();
    loop();
    draw();

    console.log("Spins changed: \""+option+"\"");
  });


  text('Magnetic Field: ', 420, 599.5);

  magFieldSelect = createSelect();
  magFieldSelect.position(530, 587);
  magFieldSelect.option('Off');
  magFieldSelect.option('Very week');
  magFieldSelect.option('Week');
  magFieldSelect.option('Regular');
  magFieldSelect.option('Strong');
  magFieldSelect.option('Very strong');
  magFieldSelect.input(function() {
    var option = magFieldSelect.value();

    if (option == 'Off') {
      B = 0;
    } else if (option == 'Very week') {
      B = 0.05;
    } else if (option == 'Week') {
      B = 0.5;
    } else if (option == 'Regular') {
      B = 2.0;
    } else if (option == 'Strong') {
      B = 15.0;
    } else if (option == 'Very strong') {
      B = 350.0;
    }

    console.log('Magnetic field changed to \"'+option+'\"');
  });


  // Divide
  rect(635, 555, 1.5, 60);

  // Action buttons
  textSize(15);
  fill(255);
  text('Action buttons', 655, 587);

  startButton = createButton('Start');
  startButton.position(760, 557);
  startButton.mousePressed(function() {
    if (sliderORbox) {
      temperature = float(inpT.value());
    } else {
      temperature = slider.value();
    }
    beta = 1 / temperature;

    console.log("Visualization started!");
    console.log("Temperature: "+temperature);
    console.log("Magnetic field: \""+magFieldSelect.value()+"\"");

    loop();
  });

  stopButton = createButton('Stop');
  stopButton.position(760, 587);
  stopButton.mousePressed(function() {
    noLoop();
    console.log("Visualization stopped!");
  });

  resetButton = createButton('Reset');
  resetButton.position(820, 557);
  resetButton.mousePressed(function() {
    startButton.remove();
    restartButton.remove();
    stopButton.remove();
    resetButton.remove();
    magFieldSelect.remove();
    spinSelect.remove();
    ptButton.remove();
    tempButton.remove();
    inpT.remove();
    slider.remove();

    temperature = 0.0005;
    B = 0;
    sliderORbox = 0;

    setup();
    console.log("Visualization reseted!");
  });

  restartButton = createButton('Restart');
  restartButton.position(820, 587);
  restartButton.mousePressed(function() {
    loop();
    console.log("Visualization restarted");
  });

  noLoop();
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
  if (fliped) {
    if (lattice[pos.x][pos.y] == 1)
      fill(255);
    else
      fill(0);

    noStroke();
    rect(pos.x * resolution, pos.y * resolution, resolution, resolution);
  }
}
