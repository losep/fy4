#include <ansi.h>
inherit QUESTNPC; 
void create()
{
        set_name("李坏", ({ "li huai", "li" }) );
        set("long",
                "这少年满面风尘，衣衫褴褛，看上去十分落魄，但看上去却有种说不出的自信。
\n");
    set("attitude", "heroism");
        create_family("风云一刀",4,"人杰");
    set("str", 40);
    set("cor", 70);
    set("cps", 12);
        set("agi",32);
        set("int",20);
        set("per",31);
        set("con",25);
        set("dur",20);
        set("fle",25);
        set("tol",30);
        set("chat_chance",10);
        set("chat_msg", ({
"李坏时而目光呆滞，时而狂笑道：“为什么？为什么是我？为什么是可可？
只许生，不许死，只许胜，不许败，为什么？难道就因为我是小李飞刀的后人！”\n"
                                })  ); 
        set("chat_chance_combat", 97);
        set("chat_msg_combat", ({
                (: perform_action, "throwing.xiaoli-feidao" :),
        }) );
        set("combat_exp", 6000000);
                set("max_gin",800);
                set("max_kee",1500);
                set("max_sen",1000);
        set_skill("throwing", 280);
                set_skill("feidao",220);
                set_skill("force",70);
        set_skill("dodge", 280);
                set_skill("move",180);
                set_skill("parry",260);
        map_skill("throwing","feidao"); 
   setup(); 
        carry_object("/d/fugui/npc/obj/cloth")->wear();
                carry_object(__DIR__"obj/leaf")->wield();
} 
int accept_object(object me,object obj)
{
        if(obj->query("keke"))
        {
                message_vision("$N瞅了一眼战书，双目赤红，疯狂一般的笑了起来，拿起酒袋狂灌不止。\n",this_object());
                obj->destruct();
                call_out("obj_drunk",10+random(10),this_object(),0);
                return 1;
        }
        return 0;
} 
void do_drunk(object obj);
void obj_drunk(object obj,int i)
{       
        
        message_vision("$N拿起酒袋，发疯般的拼命往嘴中灌酒。\n",obj);
        i++;
        if (i<2) call_out("obj_drunk",10+random(10),obj,i);
        else do_drunk(obj);
} 
void do_drunk(object obj)
{       int busy_time;
        message_vision("$N醉了，$N并没有悲伤、潦倒、失意、失败，$N只不过遇到了一个$P所不能解决的问题，所以$N醉了，彻底地醉了。",obj);
        busy_time=6+random(4);
        obj->start_busy(100);
        call_out("obj_revive",busy_time,obj);
} 
void obj_revive(object obj)
{
        if (objectp(obj))
        {
                message_vision("$N终于清醒过来了。\n",obj);
                obj->stop_busy();
        } 
}   

// add empty implementation to avoid compiling time error.
int do_flee()
{
    return 0;
}
