#include <ansi.h>
inherit NPC; 
void create()
{
        set_name(HIY"千年巨鳄"NOR, ({ "king gator" }) );
        set("race", "野兽");
        set("age", 400);
        set("long", "一条丈长的鳄鱼，不知在这暗河里已生活了多久。\n");
        set("limbs", ({ "头部", "身体", "尾巴", "眼睛" }) );
        set("verbs", ({ "bite" }) );
        set("attitude", "aggressive");
        set("combat_exp",5000000);
        set("gin",10000);
        set("kee",10000);
        set("sen",10000);
        set("cps",100);
        set("cor",50);
        set("str",100);
        add_temp("apply/dodge",300);
        add_temp("apply/attack",400);
        setup();
        carry_object(__DIR__"obj/gatorarmor");
}  
