let img=document.querySelector('img');
let input=document.getElementById('pwd');
let confirm=document.querySelector(".ensure");
let cancel=document.querySelector(".cancel");
let user=document.getElementById("username");
let flag=0;
//提示信息
let userName=document.querySelector('.m-1');
let passWord=document.querySelector('.m-2');
let sucessTip=document.querySelector('.m-3');
let feedBack=document.querySelector('.m-4');
img.onclick=function(){
    if(input.value){
            if(flag===0){
                input.type='text';
                flag=1;
                this.src='img/show.png';
            }
            else{  
                input.type='password';
                flag=0;
                this.src='img/hide.png';
            }
    }
    else{
        return 0;
    }
}
confirm.onclick=function(){
    if(!user.value){
        userName.style.display='block';
        setTimeout(function(){
            userName.style.display='none';
        },1000);
    }
    else if(!input.value){
        passWord.style.display='block';
        setTimeout(function(){
            passWord.style.display='none';
        },1000);
    }
    else{
        
        sucessTip.style.display='block';
        setTimeout(function(){
            sucessTip.style.display='none';
        },1000);
    }
}
cancel.onclick=function(){
    input.value='';
    user.value='';
    feedBack.style.display='block';
    setTimeout(function(){
        feedBack.style.display='none';
    },1000);
}