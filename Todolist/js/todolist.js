$(function(){
    //获取输入框中的值并返回，判断用户是否按下了回车键
    loadData();
    $("#send").on('keydown',function(e){
        if(e.keyCode===13){
            //调用getlocal()函数获取本地存储中的值
            if($(this).val()===""){
                $("body").append("<p class='add'>请填写内容！</p>")
                $(".add").fadeOut(1500);
            }
            else{
                let getData=getLocal();
                getData.push({
                    title:$(this).val(),
                    done:false
                })
                // console.log(getData);
                saveData(getData);
                loadData();
                $(this).val("");
            }
        }
    })
    //获取本地存储中的值
    function getLocal(){
        let data=localStorage.getItem("mylist");
        if(data!=null)
            {
                return JSON.parse(data);
            }
        else
            {
                return [];
            }
    }
    //将数据保存到localstorage.
    function saveData(data){
        //存储数据时要转换为字符串格式存储在localstorage中
        localStorage.setItem("mylist",JSON.stringify(data));
    }
    // 加载数据
    function loadData(){
        let todo=0;
        let done=0;
        let  data=getLocal();
        // console.log(data);
        $("ol,ul").empty();
        $.each(data,function(i,m){
            if(m.done){
                $("ul").prepend("<li><input type='checkbox' checked='checked' class='create'><text>"+m.title+"</text><button id="+i+">删除</button></li>");
                todo++;
            }
            else{
                $("ol").prepend("<li><input type='checkbox' class='create'><text>"+m.title+"</text><button id="+i+">删除</button></li>");
                done++;
            }
        })
        $("#todo").text(done);
        $("#done").text(todo);
    }
    //删除操作
    $("ol,ul").on("click","button",function(){
        let index=$(this).attr("id");
        // alert('!');
        let data=getLocal();
        // console.log(data);
        // alert(index);
        data.splice(index,1);
        saveData(data);
        loadData();
    })
    //修改属性
    $("ol,ul").on("click","input",function(){
        let data=getLocal();
        let num=$(this).siblings("button").attr("id");
        data[num].done=$(this).prop("checked");
        // console.log(data);
        // alert(data);
        saveData(data);
        loadData();
    })
})