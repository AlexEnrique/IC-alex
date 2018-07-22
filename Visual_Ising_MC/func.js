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
  this.x = floor(random(rows));
  this.y = floor(random(cols));
}

function deltaE(pos) {
  // periodic boundary conditions
  var xUpper, xLower, yUpper, yLower;
  xUpper = pos.x + 1;
  xLower = pos.x - 1;
  yUpper = pos.y + 1;
  yLower = pos.y - 1;

  if (pos.x == 0) {
    xUpper = pos.x + 1;
    xLower = lattice.length-1;
  }
  else if (pos.x == lattice.length - 1) {
    xUpper = 0
    xLower = pos.x - 1;
  }

  if (pos.y == 0) {
    yUpper = pos.y + 1;
    yLower = lattice[0].length;
  }
  else if (pos.y == lattice[0].length - 1) {
    yUpper = 0;
    yLower = pos.y - 1;
  }

  // console.log(pos.x, xLower, xUpper, pos.y, yLower, yUpper);
  // console.log(lattice[(pos.x - 1) % rows][pos.y]);
  var sum = lattice[xUpper][pos.y];
  sum += lattice[xLower][pos.y];
  sum += lattice[pos.x][yUpper];
  sum += lattice[pos.x][yLower];

  return ((-2) * lattice[pos.x][pos.y] * sum);
}

function fluctuateLattice(lattice) {
  var pos = new LatticePosition();
  pos.choseRandomPosition();
  // console.log(pos.x);
  // console.log(pos.y);
  // console.table(lattice);
  // // console.log(lattice[pos.x][pos.y]);

  if (deltaE(pos) < 0) {
    flip(pos);
  }
  // else if ( random() < exp(-E/(bet*T)) ) {
  //   flip(pos);
  // }
}
