window.onload=function(){
    let qq=document.getElementById("Contact-img-qq");
    let weChat=document.getElementById("Contact-img-wechat");
    let QRqq=document.getElementById("QRqq");
    let QRweChat=document.getElementById("QRweChat");
    QRqq.classList.add('hide');
    QRweChat.classList.add('hide');
    qq.onmouseenter=function(){
        qq.src="img/Contact/colorfulQQ.png";
        QRqq.classList.remove("hide");
    }
    qq.onmouseleave=function(){
        qq.src="img/Contact/greyQQ.png";
        QRqq.classList.add("hide");
    }
    weChat.onmouseenter=function(){
        weChat.src="img/Contact/colorfulWechat.png";
        QRweChat.classList.remove("hide");
    }
    weChat.onmouseleave=function(){
        weChat.src="img/Contact/greyWechat.png";
        QRweChat.classList.add("hide");
    }
}