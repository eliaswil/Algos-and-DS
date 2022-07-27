const fs = require('fs');

class Dijkstra{
    constructor(nodes, lines=[]){
        this.nodes = nodes;
        this.lines = lines;
    }

    readNodes(){
        fs.readFile('Nodes.txt', 'utf-8', (err, data) =>{
            if(err) throw err;
            console.log('readnodes():');
            data.split('\n').forEach((element) =>{
                if(!element.startsWith('//')){
                    this.lines.push(element);
                }
            });
            console.log(this.lines);
        });
        console.log(this.lines);    // call after the block above !!!!!!
    }

    

}


let test = new Dijkstra('Nodes.txt');
// test.read();
test.main();




