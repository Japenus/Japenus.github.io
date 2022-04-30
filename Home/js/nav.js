function initNav(){
    var uls=document.querySelectorAll('.context');
        //影藏所有列表元素
        for(var k=0;k<uls.length;k++){
            uls[k].classList.add('hide');
        }
}
initNav();
window.addEventListener('load',function(){
    var lis=document.querySelector('.nav-list').children;
    var list=document.querySelector('.nav-list').querySelectorAll('li');
    var uls=document.querySelectorAll('.context');
    //每个列表元素添加鼠标悬停和离开事件
    for(var s=0;s<list.length;s++){
        list[s].classList.remove('effect');
        list[s].onmouseover=function(){
            this.classList.add('effect');
        }
        list[s].onmouseout=function(){
            this.classList.remove('effect');
        }
    }
    //遍历导航条，显示对应的列表项
    for(var i=0;i<lis.length;i++){
        //设置自定义索引
        lis[i].setAttribute('index',i);
            lis[i].onmouseover=function(){
                var index=this.getAttribute('index');
                for(var j=0;j<lis.length;j++){
                    lis[j].classList.remove('effect');
                }
                uls[index].classList.remove('hide');
                this.classList.add('effect');
            }
            lis[i].onmouseout=function(){
                var index=this.getAttribute('index');
                this.classList.remove('effect');
                uls[index].classList.add('hide');
            }
    }
    //欢迎文字动画
    function fontAnimate(){
    let wel=document.querySelector('.welcome h1');
    let tipFont=wel.nextElementSibling;
    let fadeAndshow=[
        {
            opacity:0,
            transform:`translateY(-20px)`,
        },
        {
            opacity:1,
            transform:`translateY(0px)`,
        }
    ];
    let animateFunction={
        duration:3000,
        easing:"ease-in-out",
    };
    let expandFont=[
        {
            opacity:0,
            letterSpacing:"-1rem",
        },
        {
            opacity:1,
            letterSpacing:"initial",
        }
    ];
    const welTime=wel.animate(fadeAndshow,animateFunction);
    let tipTime={
        duration:welTime.effect.getComputedTiming().duration/2,
        easing:"ease-in-out",
    };
    tipFont.animate(expandFont,tipTime);
    }
    fontAnimate();
    this.setTimeout(function(){
        $('.welcome').fadeOut(3000);
    },5000)
})