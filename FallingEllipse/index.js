let bubles = [];

function setup(){
    createCanvas(displayWidth, displayHeight);
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
        positionY : mouseY,
        positionX : mouseX,
        direction: 2,
        speed : 0,
        gravity : 0.1,
        bounce : 0.8,
        display: function(){
            stroke(255,255,255);
            noFill();
            //fill(64, 224, 208);
            ellipse(this.x, this.y, 24, 24);
        },
        move: function(){
            this.speed = this.speed + this.gravity;
            this.y = this.y + this.speed;

            if(this.y >= displayHeight){
                this.speed = this.speed * (-this.bounce);
                this.y = displayHeight;
            }

            else if(this.y <= this.positionY){
                this.speed = this.speed * (-this.bounce);
            }
        }
    };
    bubles.push(buble);
}