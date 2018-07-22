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
  // if (this.x == 0 || this.y == 0) {
  // }
}

function deltaE(pos) {
  /* !Periodic boundary conditions!
   * in JavaScript -1 % 10 == -1. If pos.x (or y) is 0 then
   * I need to shift to something like (-1 + 10) % 10 to get
   * the right result for periodic boundary conditions.
   * this is why is write (pos.x -1 + cols) % cols below.
   */
  var sum = lattice[(pos.x - 1 + cols) % cols][pos.y];
  sum += lattice[(pos.x + 1) % cols][pos.y];
  sum += lattice[pos.x][(pos.y - 1 + rows) % rows];
  sum += lattice[pos.x][(pos.y + 1) % rows];

  return  (-lattice[pos.x][pos.y]) * sum;
}

function fluctuateLattice(lattice) {
  var pos = new LatticePosition();
  pos.choseRandomPosition();
  // console.log(pos.x, pos.y);
  // console.table(lattice);
  // // console.log(lattice[pos.x][pos.y]);

  if (deltaE(pos) < 0) {
    flip(pos);
    // console.log(pos.x, pos.y);
  }
  // else if ( random() < exp(-E/(bet*T)) ) {
  //   flip(pos);
  // }
}
