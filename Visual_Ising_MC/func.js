function createLattice(cols, rows) {
  let arr = new Array(cols);
  for (var i = 0; i < arr.length; i++) {
    arr[i] = new Array(rows);
  }

  return arr;
}

function randomSpin() {
  if (floor(random(2)))
    return -1;
  return 1;
}

// declare pos as a local variable to use this in the draw() function after
var pos = new LatticePosition();
function fluctuateLattice() {
  pos.choseRandomPosition();

  let dE = deltaE(pos);
  if ((dE < 0) ^ (random() < exp(-beta*dE))) {
    E += dE;
    flip(pos);
    return 1;
  }

  return 0;
}

function flip(pos) {
  lattice[pos.x][pos.y] *= -1;
}

function LatticePosition(x, y) {
  this.x = x;
  this.y = y;
}

LatticePosition.prototype.choseRandomPosition = function() {
  this.x = floor(random(cols));
  this.y = floor(random(rows));
}

function deltaE(pos) {
  /* !Periodic boundary conditions!
   * in JavaScript -1 % 10 == -1. If pos.x (or y) is 0 then
   * I need to shift to something like (-1 + 10) % 10 to get
   * the right result for periodic boundary conditions.
   * this is why it's write (pos.x -1 + cols) % cols below.
   */
  var neigbSum  = lattice[(pos.x - 1 + cols) % cols][pos.y];
      neigbSum += lattice[(pos.x + 1) % cols][pos.y];
      neigbSum += lattice[pos.x][(pos.y - 1 + rows) % rows];
      neigbSum += lattice[pos.x][(pos.y + 1) % rows];

  return ( 2 * J * (-lattice[pos.x][pos.y]) * neigbSum);
}

function totalEnergy(cols, rows) {
  var H = 0;
  for (let i = 0; i < cols; i++) {
    for (let j = 0; j < rows; j++) {
      H += (-J) * lattice[i][j] * ( lattice[(i+1)%cols][j] + lattice[i][(j+1)%rows] );
    }
  }

  return H;
}
