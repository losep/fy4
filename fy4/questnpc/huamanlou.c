#include <ansi.h>
inherit QUESTNPC;
void create()
{
        set_name("花满楼", ({ "hua manlou","hua" }) );
        set("gender", "男性");
        set("age", 32);
    set("nickname",WHT"鲜花满楼"NOR);
    set("title","花家七倌");
        set("long",
"鲜花满楼。花满楼对鲜花总是有种强烈的热爱，正如他热爱所有的生命一样。
\n"
               );  
        set("attitude", "peaceful");
        set("combat_exp", 8000000);
        set("chat_chance", 10);
        set("chat_msg", ({
              "花满楼说道：“只要你肯去领略，就会发现人生本是多么可
爱，每个季节里都有很多足以让你忘记所有烦恼的赏心乐事。”\n",
"花满楼道“我有很充足的睡眠，有很好的胃口，有这间
很舒服的屋子，有一把声音很好的古琴，这些本已足够，何
况我还有个很好的朋友。”\n",
        }) );
                set("chat_chance_combat",40);
//              set("chat_msg_combat", ({
//                      (:perform_action,"unarmed.xinyoulingxi":)
//              })      );
        set("force", 5000);
        set("max_force", 5000);
        set("force_factor", 10);
                set("max_gin",1500);
                set("max_sen",1200);
                set("fle",30);
                set("int",41);
                set("cor",40);
        set_skill("force", 80);
        set_skill("unarmed", 120);
        set_skill("dodge", 220);
                set_skill("parry",220);
                set_skill("lingxi-zhi",120);
   set_skill("move", 120);
        map_skill("unarmed","lingxi-zhi");
        setup();
    carry_object("/obj/armor/cloth")->wear();
} 
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int myexp,hisexp;
        myexp=me->query("combat_exp");
        hisexp=victim->query("combat_exp"); 
        if (random(myexp+hisexp)>hisexp&&(!random(2)))
        {
                victim->start_busy(10+random(10));
                victim->remove_all_killer();
        return HIR "$n只觉得一麻，要穴被制，一动都不能动了。\n" NOR;
        }
}    

// add empty implementation to avoid compiling time error.
int do_flee()
{
    return 0;
}
