 //Created by justdoit at May 2001
//All Rights Reserved ^_^ 
 
inherit ROOM; 
void create() 
{ 
        set("short", "潜龙泉");
        set("long", @LONG 
剑林西行，蜿蜒盘亘的是一条溪流，汩汩得冒着热气，千万年前白云本为火山，
千载而下，火山不再，但地热丰富，其中夹杂着许多世人不能参晓的物质，不过白
云岛的岛民和白云城的弟子倒也经常来这条形状宛如龙盘的泉水中沐浴，时日一久
更加发觉这汩汩热流着实功用非凡。
LONG 
           ); 
        set("exits",  
           ([  
       "eastup" : __DIR__"jianlin",
            ])); 
        set("objects",  
           ([  
//           __DIR__"obj/sand" : 1, 
            ])); 
        set("outdoors", "baiyun"); 
        set("coor/x",10); 
        set("coor/y",-1680); 
        set("coor/z",0); 
        setup(); 
        replace_program(ROOM); 
} 
