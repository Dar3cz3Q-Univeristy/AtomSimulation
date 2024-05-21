
element_name
mass_number
atomic_number
period_of_the_element
group_of_the_element

function elNameChange(){
    element_name=document.getElementById("element_name").value
    output()
}
function msNrChange(){
    mass_number=document.getElementById("mass_number").value
    output()
}
function atNrChange(){
    atomic_number=document.getElementById("atomic_number").value
    output()
}
function perNrChange(){
    period_of_the_element=document.getElementById("period_of_the_element").value
    output()
}
function grNrChange(){
    group_of_the_element=document.getElementById("group_of_the_element").value
    output()
}

function output(){
finalStr="#texture="+element_name+".png\n#particles\n"
min = -mass_number * 0.01;
max = mass_number * 0.01;

for(i=0;i<atomic_number;i++){
   
    neutronStr="type=PROTON x="+(Math.random() * (max - min) + min)+" y="+(Math.random() * (max - min) + min)+" z="+(Math.random() * (max - min) + min)+" scale=.1\n"
    finalStr+=neutronStr
}
for(i=0;i<mass_number-atomic_number;i++){
    neutronStr="type=NEUTRON x="+(Math.random() * (max - min) + min)+" y="+(Math.random() * (max - min) + min)+" z="+(Math.random() * (max - min) + min)+" scale=.1\n"
    finalStr+=neutronStr
}
let layers=[]
finalStr+="#electrons\n"
let electronCount=atomic_number
if(group_of_the_element==10){
    layers[period_of_the_element-1]=2
    electronCount-=2
}else{
    layers[period_of_the_element-1]=group_of_the_element%10
    electronCount-=group_of_the_element%10
}

for(i=0;i<period_of_the_element-1;i++){
    if(electronCount<2*(i+1)*(i+1)){
        layers[i]=electronCount
    }else{
        layers[i]=2*(i+1)*(i+1)
        electronCount-=2*(i+1)*(i+1)
    }
}
for(i=0;i<layers.length;i++){
    for(j=0;j<layers[i];j++){
        startPkt=Math.floor(Math.random() * 3) + 1;
        if(startPkt==1){
            finalStr+="x="+(i+1)+" y=0 z=0 scale=.1 speed="+(Math.floor(Math.random() * 20) + 1)+" axis_x="+Math.random()+" axis_y="+Math.random()+" axis_z="+Math.random()+"\n"
        }else if(startPkt==2){
            finalStr+="x=0 y="+(i+1)+" z=0 scale=.1 speed="+(Math.floor(Math.random() * 20) + 1)+" axis_x="+Math.random()+" axis_y="+Math.random()+" axis_z="+Math.random()+"\n"
        }else if(startPkt==3){
            finalStr+="x=0 y=0 z="+(i+1)+" scale=.1 speed="+(Math.floor(Math.random() * 20) + 1)+" axis_x="+Math.random()+" axis_y="+Math.random()+" axis_z="+Math.random()+"\n"
        }
        
    }
}

document.getElementById("output").innerText=finalStr
}
