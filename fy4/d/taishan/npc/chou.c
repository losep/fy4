#include <ansi.h>
inherit NPC;
int wieldblade();
void create()
{
        set_name("仇二先生", ({ "mr er" }) );
        set("gender", "男性");
        set("age",35);
        set("str",30);
        set("combat_exp", 600000);
        set("long",
                "道装玄冠，长身玉立，背负长剑，苍白的脸上眼角上挑，带着种说不出的傲气，
两条几乎连接在一起的浓眉间，又仿佛充满了仇恨。\n"
        );
        set("max_force",2000);
        set("force",2000);
        set("force_factor",20);
        set_skill("move",100);
        set_skill("parry", 250);
        set_skill("sword",200);
        set_skill("dodge",1);
        set_skill("feixian-steps",150);
        map_skill("dodge","feixian-steps");
        set_skill("feixian-sword",100);
        map_skill("sword","feixian-sword");
        map_skill("parry","feixian-sword");
        set("chat_chance", 1);
        set("chat_msg", ({
        (: random_move :),
         }) );
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: wieldblade  :),
        }) );
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/sword");
}
int wieldblade()
{
command("wield sword");
perform_action("dodge.tianwaifeixian");
command("unwield sword");
return 1;
}  
