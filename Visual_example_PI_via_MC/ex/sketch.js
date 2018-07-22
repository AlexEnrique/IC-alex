var m = 0, n = 0;

function setup() {
  let hw = 600;
  createCanvas(hw,hw);
  background(100);

}

function draw() {
  let seed = 31415926
  let radius = height;
  let maxiterations = 1000;

  translate(width/2, height/2);
  noStroke();
  var c = color(0, 126, 255, 5);
  fill(c)
  ellipse(0, 0, radius);

  var x = random(-height, height+1);
  var y = random(-height, height+1);

  if (x**2 + y**2 <= radius**2) {
    m += 1;
  }
  n += 1;

  c = color(0, 255, 70, 100);
  fill(c);
  ellipse(x, y, 3);

  console.log("PI: "+4*m/n);

  // noLoop();

}
