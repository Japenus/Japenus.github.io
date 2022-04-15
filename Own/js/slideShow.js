//轮播图
$(function(){
    let index=0;
    let timer=setInterval(slideShow,3000);
      //动态添加移动标志（右箭头）
    for(let s=0;s<$('.ul-img li').length;s++){
        $('.ul-dot').prepend("<li></li>");
    }
    $('.slideshow').mouseenter(function(){
        clearInterval(timer);
    })
    $('.slideshow').mouseleave(function(){
        timer=setInterval(slideShow,3000);
    })
    function slideShow(){
        index==5?index=0:index++;
        $('.ul-dot li').eq(index).addClass('current').siblings().removeClass('current');
        $('.ul-img li').eq(index).fadeIn().siblings().fadeOut();
    }

    $('.ul-dot li').mouseover(function(){
        clearInterval(timer);
        let index=$(this).index();
        $('.ul-img li').eq(index).fadeIn().siblings().fadeOut();
    })
    $('.ul-dot li').mouseout(function(){
        timer=setInterval(slideShow,3000);
    })
})

window.addEventListener('load',function(){
    $('.bg').fadeIn(500);
    this.setTimeout(function(){
        $('.bg').fadeOut();
    },5000);
})
//返回顶部函数
$(function(){
    let top=$('.ul-dot').offset().top;
    // console.log(top);
    $(window).scroll(function(){
        if($(document).scrollTop()>=top){
            // console.log($(this).scrollTop());
            $(".gotop").fadeIn();
            $(".nav-list").slideUp();
        }
        else{
            $(".gotop").fadeOut();
            $(".nav-list").slideDown();
        }
        $(".gotop").on("click",function(){
            $("body,html").stop().animate({
                scrollTop:0
            })
        })
    }
  )
})
