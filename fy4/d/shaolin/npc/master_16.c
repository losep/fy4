 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int kill_him();
void create()
{
    set_name("无花", ({ "master wu", "master"}) );
    set("nickname", HIM "妙僧"NOR);
    set("vendetta_mark","shaolin");
    set("gender", "男性" );
    set("age", 29);
    set("per", 55);
    set("int",30);
    set("attitude","friendly");
    set("max_force", 1500);
    set("force", 1500);
    set("cps",60);
    set("long", " 素衣白袜，一生不染，就连面上的微笑也有出尘之意\n");
    create_family("少林寺", 16, "大师");
    set("reward_npc", 1);
    set("difficulty", 10);   
    set("chat_chance_combat", 90);
    set("chat_msg_combat", ({
        (: perform_action, "unarmed.qiankun" :)
            }) );
    set("chat_chance", 1);
    set("chat_msg", ({
        name()+"正在一心一意地为大师煮茶。。。\n",
            name()+"道：你终于来了，当年我就说过，唯一能破坏这个计划的就是你。\n"
            }) );
    set("combat_exp", 5000000);
    set("reward_npc", 1);
    set("difficulty", 10);   
    set_skill("move", 200);
    set_skill("dodge", 200);
    set_skill("force", 200);
    set_skill("literate", 200);
    set_skill("unarmed",200);
    set_skill("puti-steps",200);
    set_skill("yiyangzhi",200);
    set_skill("buddhism",250);
    set_skill("chanting",200);
    set_skill("xiaochengforce",200);
    set_skill("staff",200);
    set_skill("parry",200);
    map_skill("parry","fumostaff");
    map_skill("dodge", "puti-steps");
    map_skill("force", "dachengforce");
    map_skill("unarmed", "yiyangzhi");
    set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
          (: perform_action, "unarmed.qiankun" :)
            }) );
    setup();
    carry_object(__DIR__"obj/monk_cloth")->wear();
} 
void attempt_apprentice(object me)
{
    command("shake");
    command("say 我常年云游在外，你还是去找方丈吧。\n");
}
void init()
{
    if(this_player()->query_temp("天一神水"))
        call_out("confess",13+random(3),this_player());
        ::init();
} 
int confess(object me)
{
    me->delete_temp("天一神水");
    command("say 看来你什么都知道了。。。\n");
    command("say 这世上有你没我。。。\n");
    message_vision("$N说罢，自断经脉，缓缓的到在地上。。。\n",this_object());
    if(!me->query("m_success/智平武林风波"))
    {
        me->set("m_success/智平武林风波",1);
        me->add("score",500);
    }
    this_object()->die();
}  
int accept_object(object who, object ob)
{
        string msg;
        
        if(ob->query("name")!="乌鞘长刀") return 0;
        if (who->query("天枫_quest2")=="成功")
        {
                msg=HIG"无花嘿嘿冷笑道：“那老鬼和那家伙都该死，谁阻了我和我母亲的霸业，
都得死。你也得死。”\n"NOR;
                who->set("天枫_quest3","成功");
        }
        else
                msg=HIM"无花眉梢扬了扬，冷笑一声：“就让你和那老鬼一同上黄泉吧。”\n"NOR;
        message_vision(msg,who);
        kill_ob(who);
        return 0;
}       
