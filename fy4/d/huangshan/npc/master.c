 // taolord.c
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
    set_name( "玉兰溪" , ({ "yu lanxi",  "yu" }) );
    set("gender", "女性");
    set("title", "松谷庵 主持");
    set("nickname", HIC"空谷幽居"NOR);
    set("age", 46);
    set("long", "一个小尼庵的主持．\n");
        set("reward_npc", 1);
        set("difficulty", 2); 
    set("combat_exp", 1000000);
    set("score", 200000); 
    set("class", "taoist"); 
    set("str", 20);
    set("int", 30);
    set("cor", 20);
    set("cps", 30);
    set("spi", 30); 
    set("force", 2000);
    set("max_force", 1000);
    set("force_factor", 30); 
    set("atman", 1400);
    set("max_atman", 1400); 
    set("mana", 4000);
    set("max_mana", 2000);
    set("mana_factor", 5); 
    set("student_title","尼姑"); 
    set_skill("literate", 150);
    set_skill("force", 180);
    set_skill("spells", 200);
    set_skill("mapo", 100);
    set_skill("move", 100);
    set_skill("unarmed", 200);
    set_skill("tenderzhi",150);
    set_skill("sword", 100);
    set_skill("siqi-sword", 120);
    set_skill("parry", 100);
    set_skill("dodge", 100);
    set_skill("lotusforce", 120);
    set_skill("liuquan-steps", 150); 
    map_skill("unarmed", "tenderzhi");
    map_skill("sword", "siqi-sword");
    map_skill("force", "lotusforce");
    map_skill("dodge", "liuquan-steps");  
    set_temp("apply/dodge", 200);
    set_temp("apply/armor", 20); 
    setup(); 
        carry_object("/obj/armor/cloth")->wear();
} 
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 贫道今天已经收了三个弟子，不想再收徒了。");
        }
} 
void do_recruit(object ob)
{
        if( (string)ob->query("gender") != "女性" )
                command("say 贫道是出家人，不便收男徒，得罪了。");
        else {
                command("say 嗯... 想入松谷庵？也好....");
                command("recruit " + ob->query("id") );
        }
} 
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
        add("apprentice_availavble", -1);
}      
