let bubles = [];

function setup(){
    createCanvas(600,400);
}

function draw() {
  background(0); 
  for(let i = 0; i < bubles.length; i++){
    bubles[i].display();
    bubles[i].move();
  }
}

function mousePressed(){
    buble = {
        x: mouseX,
        y: mouseY,
        direction: 2,
        display: function(){
            stroke(255,255,255);
            noFill();
            //fill(64, 224, 208);
            ellipse(this.x, this.y, 24, 24);
        },
        move: function(){
            //this.x = this.x + random(-1,1);
            this.y = this.y + this.direction;

            if(this.y > 400 || this.y < 0){
                this.direction = -this.direction;
            }
        }
    };
    bubles.push(buble);
}