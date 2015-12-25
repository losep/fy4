#include <ansi.h>
inherit "/d/taiping/npc/smart_npc"; 
int show_me(); 
void create()
{
    set_name("花满天",({"hua mantian","hua"}));
    set("title","白衣人");
    set("long","他在这里已经站了很久了，雪白的衣服上积满沙土，头发也已被染黄，可是他的脸
却是苍白的，苍白得全无一丝血色。\n");
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
                "花满天还站在昨夜同样的地方，甚至连姿势都没有改变过。\n"
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
        
        if (me->get_id()=="yekai" || me->get_id()=="fu hongxue") {
                command("puke");
                command("say 你以为名气是用面具戴出来的？");
                return 1;
        }
        
        if (me->query("wanma/声誉")<5) {
                command("hmm");
                command("say 我好像没听说过你，三老板请的人，个个都是有头有脸的人物。");
                command("say 你还是先想法子提高你的声誉再来找我吧。");
                tell_object(me,WHT"受万马堂邀请需要五点声誉，你现在在边城的声誉为"+chinese_number(me->query("wanma/声誉"))+"点。\n"NOR);
                return 1;
        }
        
        message_vision(CYN"$N对$n一拱手：“久仰阁下大名，请至北街口，万马堂有车接迎。”\n"NOR,ob,me);
        me->set("wanma/马车",1);
        return 1;
}
