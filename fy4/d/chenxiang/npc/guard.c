#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("青龙会弟子", ({ "guard" }) );
        set("long",
                "这是一位青龙会专门担任看守之责的弟子。\n");
        set("attitude", "killer"); 
        set("str", 30);
        set("cor", 30);
        set("cps", 25);
        
        set("combat_exp", random(200000)+500000);
        set_skill("sword", 100+random(50));
        set_skill("parry", 70+random(50));
        set_skill("dodge", 70+random(50));
        set_skill("move", 100+random(50));
        setup();
        carry_object("obj/armor/cloth")->wear();
        carry_object("obj/weapon/sword")->wield();
}   
