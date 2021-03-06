#include <ansi.h>
inherit "/d/taiping/npc/smart_npc"; 
int show_me(); 
void create()
{
    set_name("云在天",({"yun zaitian","yun"}));
    set("title","烟中飞鹤");
    set("long","一身白衣如雪。这人年纪比花满天小些，但也有四十岁左右，圆圆的脸，面白微须，
不笑时已令人觉得很可亲。\n");
        set("gender","男性");
        set("age",42);
                
        set("int",22);
        set("cor",30);
        set("cps",20);
        set("str",40);
        
        set("force",1500);
        set("max_force",1500);
        set("force_factor",120);
        set("max_atman",500);
        set("atman",500);
        set("max_mana",500);
        set("mana",500);
        set("combat_exp",4000000);  
        set("attitude", "friendly");
        
        
        set("inquiry", ([
                "万马堂" :      (: show_me :),
                "马空群" :       (: show_me :),
                "马车"   :       (: show_me :),
                "花满天" :       (: show_me :),
        ]));
        
        set("death_msg",CYN"\n$N说：功亏一篑，我不甘心啊！ \n"NOR);             
        set("nb_chat_chance", 100);
        set("nb_chat_msg_combat", ([ 
        ]) );           
        set("chat_chance_combat", 100);
           set("chat_msg_combat", ({
             (: auto_smart_fight(20) :),
        }) );
        set("chat_chance",1);
        set("chat_msg",({
                name()+"道：“在下奉了三老板之命，请各位英雄今夜过去小酌。”\n"
        }) );                   
        
        CHAR_D->setup_char(this_object());
        auto_npc_setup("wang",200,160,0,"/obj/weapon/","fighter_w","lianxin-blade",2);
        
        setup();
        carry_object("/obj/armor/cloth")->wear();    
    
}  
int show_me(){
        object me,ob;
        
        me=this_player();
        ob=this_object();       
        
        if (!me->query("wanma/马车")){
                message_vision(CYN"$N盯着$n，那凌厉的目光似乎要把$n看穿。\n",ob,me);
                command("say 万马堂要请的客人，花场主自然会请到。");
                command("say 万马堂不请的客人，再问也是多余。");
                return 1;
        }
        
        message_vision(CYN"$N一拱手说：请上车，三老板在迎宾处恭候大驾。\n"NOR,ob);
        me->set("wanma/迎宾",1);
        return 1;
}    
