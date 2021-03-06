 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
inherit F_MASTER;
#include <ansi.h> 
int kill_him();
int jian(); 
void create()
{
    set_name("圆灭", ({ "master yuan", "master"}) );
    set("nickname", HIG "茫为" NOR);
    set("vendetta_mark","shaolin");
    set("gender", "男性" );
    set("reward_npc", 1);
        set("difficulty", 1);
    
    set("age", 64);
    set("agi",30);
    set("per", 35);
    set("int",30);
    set("cor",20);
    set("str",30);
    set("cps",80);
    set("attitude","friendly");
    set("max_force", 500);
    set("force", 500);
    set("long","少林第二十二代的师傅，他专门传授少林俗家弟子武功。\n");
    create_family("少林寺", 22, "长老");
    set("student_title","俗家弟子");
        
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: perform_action, "staff.hequhecong" :),
        (: perform_action, "unarmed.qianshouqianbian" :)
            }) );
    set("combat_exp", 500000);
    set_skill("move", 90);
    set_skill("dodge", 90);
    set_skill("force", 90);
    set_skill("literate", 120);
    set_skill("unarmed",90);
    set_skill("puti-steps",90);
    set_skill("dabei-strike",90);
    set_skill("zen",110);
    set_skill("chanting",90);
    set_skill("xiaochengforce",90);
    set_skill("staff",90);
    set_skill("parry",90);
    set_skill("fumostaff",90);
    set_skill("blade", 90);
    set_skill("lianxin-blade",90);
    set_skill("liuxing-hammer",90);
    set_skill("hammer",90);
    map_skill("hammer","liuxing-hammer");
    map_skill("blade", "lianxin-blade");
    map_skill("staff","fumostaff");
    map_skill("parry","fumostaff");
    map_skill("dodge", "puti-steps");
    map_skill("force", "dachengforce");
    map_skill("unarmed", "dabei-strike");
    set("inquiry", ([
                "见方丈": (: jian()  :),
                "master": (: jian()  :),
        ]) );
    setup();
    carry_object(__DIR__"obj/monk22_cloth")->wear();
    carry_object(__DIR__"obj/staff")->wield(); 
} 
void attempt_apprentice(object me)
{
    if(me->query_temp("won_master_kong"))
    {
        command("smile");
        command("recruit " + me->query("id") );
        return;
    }
    else
    {
        command("shake");
    }
} 
void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "shaolin");
} 
int accept_fight(object me)
{
        if((me->query("family/family_name") == query("family/family_name") &&
           me->query("family/master_id") == query("id")) || 
        me->query_temp("won_master_kong"))
        {
        if (me->query("combat_exp")<150000) {
                command("say 徒儿，学武不能好高骛远啊！\n");    
                return 0;
                }
        command("say 好，你赢了我，你就可以去找少林中更高深的师傅了！\n");
        return 1;
        }
        else
        {
        command("say 阿弥陀佛！贫僧武功低微，施主不要开这种玩笑。\n");
        return 0;
        }
}
void win_enemy(object loser)
{
    command("say 阿弥陀佛！徒儿还要努力呀！\n");
} 
void lose_enemy(object winner)
{
    command("say 阿弥陀佛！你可以去找别的师傅去深造了。\n");
    winner->set_temp("won_master_yuan",1);
} 
void init() {
        ::init();
        add_action("do_killing", "kill");
        add_action("do_answer","answer");
}  
int jian() {
        object me;
        me=this_player();
        command("say 想见方丈....嗯....你有什么事吗？（answer）");
        me->set_temp("shaolin/ask_yuan",1);
        return 1;
} 
int do_answer(string arg)
{
        if(arg == "重要事" || arg =="emergency") {
                if (!this_player()->query_temp("shaolin/ask_yuan")) {
                        command("say 重要事？施主是在跟贫僧说话么？");
                        return 1;
                }
                command("say 好，方丈南院向北，你去吧！\n");
                this_player()->delete_temp("shaolin/ask_yuan");         
                this_player()->set_temp("see_fangzhang",1);
                return 1;
        }
}  
int do_killing(string arg)
{
    object player, victim;
    string id,id_class;
    player = this_player();
    if(!arg || arg == "") return 0;
    victim = present(arg, environment(player));
        if(!objectp(victim))
                return notify_fail("这里没有这个人。\n");
    if(living(victim))
    {
        id_class=victim->query("class");
        id=victim->query("id");
        if(id_class == "shaolin"&& userp(victim)&&player!=victim)
        {
            message_vision(HIW
"$N对$n喝道：阿弥陀佛,佛门清静之地,岂可妄起杀心?施主请恕老衲得罪了！\n"NOR, this_object(),player);
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
}      
