function press(){
    if(document.getElementById('form').style.display='none'){
        document.getElementById('form').style.display='block';
    } 
}
function finish(){
    if(document.getElementById('feedback').style.display='none'){
        document.getElementById('feedback').style.display='block';
        document.getElementById('error').style.display='none';
    } 
}
function operation(){
    var a=document.getElementById('input_1');
    var b=document.getElementById('input_2');
    var c=document.getElementById('input_3');
    var oa=a.value;
    var ob=b.value;
    var oc=c.value;
    var reg= /^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+((\.[a-zA-Z0-9_-]{2,3}){1,2})$/;
    var pass=reg.test(oc);
    // alert(pass);
    if(oa==""||ob==""||oc=="")
        {
            alert('请输入完整后再提交！');
        }
    else  if(pass==false){
            // alert('请输入正确的邮箱！');
            document.getElementById('error').style.display='block';
        }
    else
        {
            finish();
        }
}
  function scoll_1(){
      if(onclick=document.getElementById('c1')){
      document.getElementById('s1').style.display='block';
      document.getElementById('s2').style.display='block';
      document.getElementById('s3').style.display='block';
      document.getElementById('s4').style.display='block';
      document.getElementById('progress').value=25;
      }
  }
  function scoll_2(){
      if(document.getElementById('c2')){
      document.getElementById('s1').style.display='block';
      document.getElementById('s2').style.display='none';
      document.getElementById('s3').style.display='none';
      document.getElementById('s4').style.display='none';
      document.getElementById('progress').value=50;
      }
  }
  function scoll_3(){
      if(document.getElementById('c3')){
      document.getElementById('s1').style.display='none';
      document.getElementById('s2').style.display='block';
      document.getElementById('s3').style.display='none';
      document.getElementById('s4').style.display='none';
      document.getElementById('progress').value=75;
      }
  }
  function scoll_4(){
      if(document.getElementById('c4')){
      document.getElementById('s1').style.display='none';
      document.getElementById('s2').style.display='none';
      document.getElementById('s3').style.display='block';
      document.getElementById('s4').style.display='none';
      document.getElementById('progress').value=100;
      }
  }