 // laoni.c
#include <ansi.h> 
inherit NPC;
void create()
{
        set_name("青衣老尼" , ({ "lao ni" }) );
        set("long", 
"一个瘦削苍老的青衣尼，垂眉敛目，盘膝坐在神案前的蒲团上，虽然是坐着，
犹可看出身材很高大。她的眼睛几乎全是灰色的，就彷佛死水中的寒冰，而
她的脸就像是一湖死水，冷酷中又带着出奇的宁静。。
"
);
        set("attitude", "friendly");
        set("class","shenshui");
        set_skill("unarmed", 150);
        set_skill("sword", 150);
        set_skill("force", 180);
        set_skill("parry", 140);
        set_skill("dodge", 140);
        set_skill("literate", 140);
        set_skill("move",140);
        set_skill("charm",150);
        set_skill("nine-moon-spirit", 200);     
        set_skill("nine-moon-steps", 150);
        set_skill("nine-moon-claw", 200);
        set_skill("nine-moon-force", 150);
        set_skill("nine-moon-sword", 200); 
        map_skill("dodge", "nine-moon-steps");
        map_skill("unarmed", "nine-moon-claw");
        map_skill("force", "nine-moon-force");
        map_skill("sword", "nine-moon-sword"); 
        set_temp("apply/parry", 100);
        set_temp("nine-moon-force_poison", 340);
        
        set("reward_npc", 1);
        set("difficulty", 25);  
        
        set("age", 65);
        set("gender", "女性" );
        set("combat_exp", 6500000);
   set("per", 2);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.polu" :),
        }) );
        
        setup();
        carry_object(__DIR__"obj/cyan_cloth")->wear();
}   
