var m = 0, n = 0;

function setup() {
  let hw = 600;
  createCanvas(hw,hw);
  background(100);

  var color1 = color(0, 126, 255, 5);
  var color2 = color(0, 255, 70, 100);
}

function draw() {
  let radius = height;

  translate(width/2, height/2);
  noStroke();
  fill(color1)
  ellipse(0, 0, radius);

  var x = random(-height, height+0.0000001); // [-height, height+1)
  var y = random(-height, height+0.0000001);

  if (x**2 + y**2 <= radius**2) {
    m += 1;
  }
  n += 1;

  fill(color2);
  ellipse(x, y, 3);

  console.log("PI: " + 4*m/n);

  // noLoop();

}
