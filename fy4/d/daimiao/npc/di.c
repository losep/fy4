 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
    set_name("地利老人", ({ "master di", "master"}) );
    set("nickname", HIW "地舵舵主"NOR);
    set("gender", "男性" );
        set("reward_npc", 1);
        set("difficulty", 2);
    set("age", 63);
    set("per", 3);
    set("agi",25);
    set("int",30);
    set("attitude","friendly");
    set("max_force", 7500);
    set("force", 7500);
    set("force_factor", 30);
    set("long",
        "地利老人在西方神教中的地位是仅次于天时老人的，"
        "地利老人统领着西方神教中的地舵。\n");
    create_family("西方神教", 3, "舵主");
    set("rank_nogen",1);
    set("ranks",({"教徒","副堂主","堂主","副坛主","坛主",
                      "副舵主","舵主","护法","大护法",
                      "长老","大长老","副帮主"}));
    set("rank_levels",({ 32000,64000,128000,256000,512000,
                             1024000,1536000,2304000,3456000,
                             5187000,26244000 })); 
    set("chat_chance_combat", 90);
    set("chat_msg_combat", ({
        (: perform_action, "unarmed.dimo" :),
            (: perform_action, "dodge.lianhuanbabu" :),
            (: perform_action, "unarmed.dimo" :),
            (: exert_function, "mihun" :)
            }) );
    set("combat_exp", 1200000);
    set("score", 200000); 
    set_skill("move", 70);
    set_skill("parry",70);
    set_skill("dodge", 70);
    set_skill("force", 70);
    set_skill("literate", 70);
    set_skill("unarmed",70);
    set_skill("demon-steps",70);
    set_skill("demon-strike",70);
    set_skill("demon-force",70);
    set_skill("perception",70);
    map_skill("dodge", "demon-steps");
    map_skill("force", "demon-force");
    map_skill("unarmed", "demon-strike");
    setup();
    carry_object(__DIR__"obj/duoyi2")->wear(); 
} 
void attempt_apprentice(object me)
{
        command("say 西方神教这个名字，休要再提了。。。");
        return ;
    if(me->query("family/family_name") == "西方神教")
    {
        command("say 你已是西方神教弟子，跟谁学都一样。\n");
        return;
    }
    command("smile");
    command("say 多加努力，你是一块不世之材！\n");
    command("recruit " + me->query("id") );
} 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "bandit");
}   
