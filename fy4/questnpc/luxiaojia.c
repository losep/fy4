 inherit QUESTNPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("路小佳", ({ "lu xiaojia", "lu" }) );
        set("gender", "男性" );
    set("age", 25);
    set("title", "独行客" );
    set("nickname", HIR"快意江湖"NOR );
        set("int", 35);
        set("per", 30);
        set("long",
                "他是个年轻人，一个奇怪的年轻人，有着双奇怪的眼睛，就连笑的时候，这双眼睛都
是冷冰的，就像是死人的眼睛，没有情感，也没有表情。
\n"
                );
        set("max_gin", 3000);
        set("max_kee", 3000);
        set("max_sen", 3000);
        set("eff_gin", 3000);
        set("eff_kee", 3000);
        set("eff_sen", 3000);
        set("gin", 3000);
        set("kee", 3000);
        set("sen", 3000);
        set("max_force", 4000);
        set("force", 4000);
        set("force_factor", 100);
        set("cor",80);
        set("str",50);
        set("combat_exp", 8000000);
        set("score", 3000);
        set_skill("sword", 150);
        set_skill("force", 70);
        set_skill("parry", 180);
        set_skill("literate", 90);
        set_skill("dodge", 280);
        set("agi",25);
        set("int",30);
           set("chat_chance",10);
                set("chat_msg",({
"路小佳拈起一颗花生，剥开，抛起，然后看着这颗花生落到自己嘴里，闭上眼睛，
长长的叹了口气，开始慢慢咀嚼。\n",
"路小佳忽然笑笑 ，说道：“杀人是件干净痛快的事情。”他顿了一顿，又说道：
“所以在杀人之前，我一定要洗个澡。”\n",
                })      );
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sharenruma" :),
        }) );
        set_skill("sharen-sword", 120);
        map_skill("sword", "sharen-sword");
        map_skill("parry","suiyuan-sword");
        setup();
    carry_object("/obj/armor/cloth")->wear();
        carry_object(__DIR__"obj/lusword")->wield();
}   
// add empty implementation to avoid compiling time error.
int do_flee()
{
    return 0;
}
