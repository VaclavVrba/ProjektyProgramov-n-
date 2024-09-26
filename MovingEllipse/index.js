let bubles = [];

function setup(){
    createCanvas(600,400);
    for(let i = 0; i < 400; i++){ //Stačí změnit číslo pro počet kroužků
        bubles[i] = {
            x: random(0,width),
            y: random(0,height),
            display: function(){
                stroke(255,255,255);
                noFill();
                ellipse(this.x, this.y, 24, 24);
            },
            move: function(){
                this.x = this.x + random(-1,1);
                this.y = this.y + random(-1,1);
            }
        }
    }
}

function draw() {
  background(0); 
  for(let i = 0; i < bubles.length; i++){
    bubles[i].display();
    bubles[i].move();
  }
}